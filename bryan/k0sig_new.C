
//********************************* g8Ana_lite.C *****************************//
//                      A part of the rootbeer package                        //
//                                                                            //
//      Original:   Craig Paterson (c.paterson@physics,gla,ac,uk)             //
//      Mods:       Ken, Dave                                                 //
//                                                                            //
//                                                                            //
// ******************************** g8Ana_lite.C *****************************//

// ******** required headers ********************************************
//                                                                      *
#include "RootBeerUtil.h"	//gets everything for RootBeer scheme
#include "TFile.h"              // for root files

#include <ctype.h>              //For getopt to parse options
#include <stdio.h>              //
#include <stdlib.h>             //
#include <unistd.h>             //
//                                                                      *
// ******** end of required headers *************************************
// ******** my headers here *********************************************
//                                                                      *
#include "TCanvas.h"
#include "TH1.h"                // eg. for 1D Histogram                 
#include "TH2.h"                // eg. for 2D Histogram
#include "TH3.h"                // eg. for 3D Histogram
#include "TGraph2D.h"
#include "TROOT.h"
#include "TLorentzVector.h"     //For Lorentz Vectors
#include "TMath.h"
#include "particleDEF.h"        //Particle Definitions
#include "extra_packages/eloss_rb/eLoss.h"              //Correction for energy losses
#include "kinematics.h"
#include "g8b.h"

#include <iostream>
using namespace std;

#define PARA 0                  //defs for polarisation plane
#define PERP 1
#define AMO  2
#define CHANGING 3
#define ALUMINUM 0               //defs for radiators
#define AMORPHOUS 1
#define DIAMOND 2
#define UNKNOWN 3

#define MANUAL 0                //defs for kind of running
#define SWAP 1

//enumerator for the column names in the pol tables
enum {
  E_ID    = 0,
  ENERGY  = 1,
  ENH     = 2,
  ENHERR  = 3,
  ENHFIT  = 4,
  PFIT    = 5,
  PCOR    = 6,
  PCORERR = 7,
  PSMOOTH = 8,
  EDGE    = 9
};

//                                                                      *
// ******** end of my headers here **************************************



// ********** required global variables *********************************
//                                                                      *
// They are global to get easily filled by parseArgs()
int	nEventsTot=0;			// ie do all events in all
					// files
char  	InFileName[128];		// in file name parsed from args 
char  	OutFileName[128];		// out file name parsed from args


class TRootBeer *rootbeer;        	// The main class
//                                                                      *
// ********** end of required global variables **************************

// **************** my global variables *********************************
//                                                                      *
// Eg. my hists are global to be easily accessed from the 
// root> prompt after the function is called as a macro
class	TH1F *mult;
class 	TH1F *piplustofmass;
class	TH1F *piminustofmass;
class	TH1F *ptofmass;
class	TH1F *Photon_Energy;
class	TH1F *pzvertex;
class	TH1F *pipzvertex;
class	TH1F *pimzvertex;
class	TH1F *pippverttime;
class	TH1F *pippverttimea;
class	TH2F *pippverttime_pipmom;
class	TH2F *pippverttime_pipmoma;
class	TH1F *pimpverttime;
class	TH1F *pimpverttimea;
class	TH2F *pimpverttime_pimmom;
class	TH2F *pimpverttime_pimmoma;
class   TH1F *ptvertex_tgamma;
class   TH1F *ptvertex_tgammaa;   
class	TH2F *ptvtg_Pmom;
class	TH2F *ptvtg_Pmoma;
class   TH1F *piptvertex_tgamma; 
class   TH1F *piptvertex_tgammaa;
class	TH2F *piptvtg_pipmom;  
class	TH2F *piptvtg_pipmoma;  
class   TH1F *pimtvertex_tgamma; 
class   TH1F *pimtvertex_tgammaa; 
class	TH2F *pimtvtg_pimmom;  
class	TH2F *pimtvtg_pimmoma;  

class   TH1F *elossp;
class   TH1F *elosspip;
class   TH1F *elosspim;
class   TH2F *elossp_mom;
class   TH2F *elosspip_mom;
class   TH2F *elosspim_mom;

class	TH1F *taggerhits;
class	TH1F *proton;
class 	TH1F *piplus;
class 	TH1F *piminus;

class  	TH1F *MMPpipi;
class  	TH1F *MMPpipia;

class	TH1F *Mpippim;

class	TH1F *Mpi0;
class	TH1F *MPpi0;

class   TH2F *MpippimvsMMpippim;
class   TH2F *MpippimvsMPpi0;
class	TH1F *M3pi;

class   TFile *outFile;                 // the file to put the results


float firstTimeCut=1.0;
float n_min=0.8972196;
float n_max=0.9793404;
float l_min=1.49128907;
float l_max=1.54841093;



float pmin_p=0.3;

TLorentzVector *p_in,*p_out;			// momenta before and after eloss correction
TVector3	vert;			// the vertex


TLorentzVector *lP;
TLorentzVector *lPiplus;
TLorentzVector *lPiminus;
TLorentzVector *lPhoton;
TLorentzVector *lTarget;

TLorentzVector *lppipi;
TLorentzVector *lMissing_Pizero;
TLorentzVector *lKzero;
TLorentzVector *lSigma;

TLorentzVector *lMissing_Sigma;
TLorentzVector *lpipipi;

TTree *PartTree; 
float e_correction[769];

int firstInFile=1;						//flag for 1st event in file
int runNo=0;

//EPICs stuff
int nEpicEvent=0;               //Counter for EPICs events
int current_plane=0;            //Stor value of coherent plane
double current_edge=0;            //Stor value of coherent plane
float plane;
float epics;
				//for getting epics values
int	currentRadiator=UNKNOWN;    	// current rad, plane - init these to UNKNOWN
Int_t	currentPlane=UNKNOWN;
Int_t   currentMode=MANUAL;
Double_t  currentEdge=0.0;

//default values for command line args
Double_t polLeft=0.0; //Ken2 may alread be set like this - not sure
Double_t polRight=0.0; //Ken2
Double_t ELeft=200.0;
Double_t ERight=0.0;
Int_t Column=PSMOOTH;
Int_t  EgSetting=1300;

//Int_t EgSetting = 1500;
//float EgLow = 1.1;
//float EgHigh = 1.55;

//Asymmetry stuff
char hname[100];		    	//for constructing histogram names
char hnamet[100];


char	*planeNames[4]={"PARA","PERP","AMO","UNKNOWN"}; //strings for plane and rad. manes
char	*radiatorNames[4]={"ALUMINIUM","AMORPHOUS","DIAMOND","UNKNOWN"};




//Set Maximum and Minimum Photon Energies here.....
//These need to be changed for each coherent peak position
//Eg low should be coh peak - 0.4
//Eg High should be coh peak + 0.05
// const float EgLow= 1.3;
// const float EgHigh = 1.75;

float EgLow= 0.0;
float EgHigh = 0.0;

//Ken's additions to get event by event polarization fron the mean pol table
Float_t tagPolPara[2][385];
char *meanPolFileName;

Int_t Sim=0;

// and tree for pol observables
TTree *polTree; 
Float_t polDegree;


//variables to handle the photon polarization using full pol tables
Double_t polTable[2][500][385][10];  //where its [plane][edge][E_id][field]
Int_t polTableN[2]={0,0};            //No of entries for para and perp
Char_t polFirstLines[2][500][250];   //to keep the 1st lines if needed (info from files)

char *paraPolTable;
char *perpPolTable;
char edgeTable[200];

Int_t edgeEventLow[5000];            //hold the current table of edge positions for event ranges
Int_t edgeEventHigh[5000];
Double_t edgeEventEdge[5000];
Int_t edgeEventPlane[5000];
Int_t edgeEventN;
Int_t edgeIndex=0;
Int_t lastEdgeEvent=0;
Double_t lastCohEdge=0.0;
Int_t lastCohPlane=-1;

class TH1F *meanPol[2],*meanPolG[2],*eventsPol[2],*eventsPolG[2];
Double_t gBinsArray[385]; 

//To implement Mike Duggers further correction ot the poalrization
Double_t ldPar[6][2][2]={
  //For 1.3 Manual: (PARA0,PARA1, PERP0,PERP1)
  1.004337,  -.4986358E-02, 1.009058,  -.5687501E-02,
  //For 1.5 Manual:
  1.012704,  -.3850369E-02, 1.002215,  -.2256782E-02,
  //For 1.7 Manual:
  0.9888860, -.2256782E-02, 0.9924032, -.3019766E-02,
  //For 2.1 Manual:
  1.004469,  -.2188895E-01, 1.067167,  -.1876592E-01,
  //For 1.7 Auto:
  0.9844326, 0.7438295E-03, 1.032343,  -.1255454E-01,
  //For 1.9 Auto:
  1.008734,  -.1557868E-02, 0.9865551,  0.2070320E-02,
};

const Double_t diffFix = 0.135;
const Double_t width = 0.2;

TCanvas *c;                         //to draw any pics on for making gifs



//Some stuff for the tagger sag correction.
const Double_t sagA[3][3]={{-0.00599597, -0.0181293,   -0.0511162 },
		           { 0.0390912,   0.0675599,    0.138208  },
		           {-0.0573218,  -0.0541268,   -0.0867757 }};
const Double_t sagU = 0.0013404;
const Double_t sagB = -0.0035086;

Char_t **progArgv;
Int_t progArgc;

//                                                                      *
// **********************************************************************


// ********* required functions defined in this code ******************** 
//                                                                      *
void printUsage();			// print usage when run as exe       
int  parseArgs(int,char **);		// parse args when run as exe
int  parseArgs2(int,char **);		// parse args when run as exe
//                                                                      *
// ********* end of required functions defined in this code ************* 

// ********* my functions defined in this code ************************** 
//                                                                      *
void g10Ana(int, char *,char *);   // main function
int gettagcalib();
int firstPIDCut();
int kinematicCuts();

TLorentzVector *lab_to_cm(TLorentzVector*, TLorentzVector*, TLorentzVector*);
//int KinematicCuts();        // Kinematic cuts done here
int LoadPolTable(int plane, Char_t *PolTableList);
Double_t GetPol(Int_t plane, Double_t edge, Int_t eid, Int_t poltype, Double_t lowThresh, Double_t highThresh);
Double_t GetPol(Int_t plane, Double_t edge, Double_t eg, Int_t poltype, Double_t lowThresh, Double_t highThresh);
int LoadEdgeTable(Char_t *EdgeTable);
Int_t GetEdge(Int_t event, Double_t *edge, Int_t *plane);
Double_t sagCor(Double_t Eg);          // Function to correct the tagger sag
Double_t mikeTest(Double_t pol, Double_t egamma, Double_t cohEdge, Int_t Plane, Int_t setting); //Mikes pol correction
Double_t polFix0(Double_t xE, Int_t plane, Int_t parSet); //Mikes pol correction 


//                                                                      *
// ********* end of my functions defined in this code ******************* 


// ---------- FUNCTION DEFINITIONS BEGIN HERE ---------------------

// ---------- Required main() for making an executable -------------
#ifdef ROOTEXE
int main(int argc,char **argv){		
  if((parseArgs2(argc,argv))!=0) return(-1);	//parse input args
  g10Ana(nEventsTot,InFileName,OutFileName);	//call user function
  return(0);
}
#endif
// ---------- end of required main() for making an executable ------

// ---------- user main function  -----------------------------------------------
// This gets called by main() when running as an executable,
// or interactively from the root> prompt.
// should have the same name as this file (minus the .C suffix)
// customize the "non-required" sections
 
void g10Ana(int nEvents, char *file, char *outFileName){   // main user function

  // *****************variables which are required***********************
  //                                                                    *
  int	event=0;             	// Event counter for current file
  int	eventTot=0;	       	// Total event count
  class	TFile *outFile;         // the file to put the results
  char 	inFile[128];	       	// holds the current file name
  int 	fileNo=0;	       	// current file no if sorting though a list
  char hname[100];              // for constructing hist names       
  
  //                                                                    *
  // ********* end of variables which are required **********************


  // ******************* my variables ***********************************
  //                                                                    *

  // ******************* end of my variables ****************************
  
  // ************************* required init stuff **********************
  //                                                                    *
#ifdef ROOTEXE					//if running as an executable
  outFile=new TFile(outFileName,"recreate");	//open output file 

#endif
  eventTot=0;			 		// init the total event counter
  //
  //                                                                    *
  // ****************** end of required init stuff **********************

  // ******* User initialisation ****************************************
  //                                                                    *
  //
  // ** DONT FORGET TO DEFINE THE BANKS YOU WANT RIGHT HERE
  // This line can be generated by running:
  // >getbanks -Nevents <BosFile| rootDSTFile>
  char *mybanks[]={"HEAD","TAGR","CL01","HEVT","EVNT","DCPB","ECPB","ECHB","SCPB","CCPB","STPB","TGPB","TBER","TBTR","SCRC","STR ","PART","TBID","GPID","TDPL","EPIC","null"};	// make a list of the banks you want to use
  // ** DONT FORGET TO DEFINE THE BANKS YOU WANT RIGHT HERE
  //


  mult = new TH1F("mult","mult",10,0,10);
  piplustofmass = new  TH1F("piplustofmass","piplustofsmass",1000,0,2.0);
  piminustofmass = new  TH1F("piminustofmass","piminustofmass",1000,0,2.0);
  ptofmass = new  TH1F("ptofmass","ptofmass",1000,0,2.0);


  pzvertex = new TH1F("pzvertex","pzvertex",100,-50,50);
  pipzvertex = new TH1F("pipzvertex","pipzvertex",100,-50,50);
  pimzvertex = new TH1F("pimzvertex","pimzvertex",100,-50,50);

  pippverttime = new TH1F("pippverttime","pippverttime",100,-5.0,5.0);
  pippverttimea = new TH1F("pippverttimea","pippverttimea",100,-5.0,5.0);
  pippverttime_pipmom = new TH2F("pippverttime_pipmom","pippverttime_pipmom",300,0,3,100,-5.0,5.0);
  pippverttime_pipmoma = new TH2F("pippverttime_pipmoma","pippverttime_pipmoma",300,0,3,100,-5.0,5.0);
  pimpverttime = new TH1F("pimpverttime","pimpverttime",100,-5.0,5.0);
  pimpverttimea = new TH1F("pimpverttimea","pimpverttimea",100,-5.0,5.0); 
  pimpverttime_pimmom = new TH2F("pimpverttime_pimmom","pimpverttime_pimmom",300,0,3,100,-5.0,5.0); 
  pimpverttime_pimmoma = new TH2F("pimpverttime_pimmoma","pimpverttime_pimmoma",300,0,3,100,-5.0,5.0); 
  ptvertex_tgamma = new TH1F("ptvertex_tgamma","ptvertex_tgamma",300,-15.0,15.0);
  ptvertex_tgammaa = new TH1F("ptvertex_tgammaa","ptvertex_tgammaa",300,-15.0,15.0);
  ptvtg_Pmom = new TH2F("ptvtg_Pmom","ptvtg_Pmom",300,0,3,300,-15.0,15.0);
  ptvtg_Pmoma = new TH2F("ptvtg_Pmoma","ptvtg_Pmoma",300,0,3,300,-15.0,15.0);
  piptvertex_tgamma = new TH1F("piptvertex_tgamma","piptvertex_tgamma",300,-15.0,15.0);
  piptvertex_tgammaa = new TH1F("piptvertex_tgammaa","piptvertex_tgammaa",300,-15.0,15.0);
  piptvtg_pipmom = new TH2F("piptvtg_pipmom","piptvtg_pipmom",300,0,3,300,-15.0,15.0);
  piptvtg_pipmoma = new TH2F("piptvtg_pipmoma","piptvtg_pipmoma",300,0,3,300,-15.0,15.0);
  pimtvertex_tgamma = new TH1F("kmtvertex_tgamma","kmtvertex_tgamma",300,-15.0,15.0);
  pimtvertex_tgammaa = new TH1F("pimtvertex_tgammaa","pimtvertex_tgammaa",300,-15.0,15.0);
  pimtvtg_pimmom = new TH2F("pimtvtg_pimmom","pimtvtg_pimmom",300,0,3,300,-15.0,15.0);
  pimtvtg_pimmoma = new TH2F("pimtvtg_pimmoma","pimtvtg_pimmoma",300,0,3,300,-15.0,15.0);

  
  taggerhits = new TH1F("taggerhits","photons in TAGR bank",21,-0.5,20.5);
  Photon_Energy = new TH1F("Photon_Energy","Photon Energy",400,0,4); 
 
  proton = new TH1F("proton","Proton",1000,0,2);
  piplus  = new TH1F("piplus","PiPlus",1000,0,2);
  piminus = new TH1F("piminus","PiMinus",1000,0,2);

  Mpippim = new TH1F("MPipPim","M(pi+pi-)",100,0.0,2);
  MMPpipi = new TH1F("MMPpipi","MM(ppi+pi-)",100,0.0,3);
  MMPpipia = new TH1F("MMPpipia","MM(ppi+pi-)",100,0.0,3);

  Mpi0 = new TH1F("Mpi0","Pizero)",100,0.0,2);
  MPpi0 = new TH1F("MPpi0","M(ppi0)",100,0.0,2);

  MpippimvsMMpippim = new TH2F("MPipPimvsMMPipPim","M(pi+pi-) vs MM(pi+pi-)",100,0.0,1,100,1,2);
  MpippimvsMPpi0 = new TH2F("MPipPimvsMPpi0","M(pi+pi-) vs M(ppi0)",100,0.0,1,100,1,2);

  M3pi = new TH1F("MPipPimPizero","M(pi+pi-pi0)",100,0.0,2);


  elossp = new TH1F("elossp","Proton energy loss in target and start counter",500,0,50); //for hit rate of paddles
  elossp ->GetXaxis()->SetTitle("Energy loss (MeV)");
  elosspip = new TH1F("elosspip","pi+ energy loss in target and start counter",500,0,50); //for hit rate of paddles 
  elosspip ->GetXaxis()->SetTitle("Energy loss (MeV)");
  elosspim = new TH1F("elosspim","pi- energy loss in target and start counter",500,0,50); //for hit rate of paddles 
  elosspim ->GetXaxis()->SetTitle("Energy loss (MeV)");

  //Plot eloss vs mom
  //elossp_mom = new TH2F("elossp_mom","Proton energy loss in target and start counter",500,0,50,100,0,3);
  elossp_mom = new TH2F("elossp_mom","Proton energy loss in target and start counter",100,0,3,500,0,50);
  elosspip_mom = new TH2F("elosspip_mom","pi+ energy loss in target and start counter",100,0,3,500,0,50);
  elosspim_mom = new TH2F("elosspim_mom","pi- energy loss in target and start counter",100,0,3,500,0,50);



  //initialise eloss targ_X, targ_y, targ_z, st_offset
  //targ_X, targ_y, targ_z, st_offset
  initELoss(0.0,0.0,-20.0,-24.06);

  p_out=new TLorentzVector();
  



  lP = new TLorentzVector(1.0,1.0,1.0,1.0);
  lPiplus = new TLorentzVector(1.0,1.0,1.0,1.0);
  lPiminus = new TLorentzVector(1.0,1.0,1.0,1.0);
  lPhoton = new TLorentzVector(1.0,1.0,1.0,1.0);

  lTarget = new TLorentzVector(1.0,1.0,1.0,1.0);
  lTarget->SetXYZM(0,0,0,PROTON_MASS);

  lppipi = new TLorentzVector(1.0,1.0,1.0,1.0);
  lMissing_Pizero = new TLorentzVector(1.0,1.0,1.0,1.0);
  lKzero= new TLorentzVector(1.0,1.0,1.0,1.0);
  lSigma = new TLorentzVector(1.0,1.0,1.0,1.0);

  lMissing_Sigma = new TLorentzVector(1.0,1.0,1.0,1.0);
  lpipipi= new TLorentzVector(1.0,1.0,1.0,1.0);


  
  
  //	Settings based on commandline argument for energy setting...
  //These need to be changed for each coherent peak position
  //Eg low should be coh peak - 0.4
  //Eg High should be coh peak + 0.05
  //	add links to updated polarization tables here...
  switch(EgSetting){
  case 1300:
   EgLow = 0.9;
   EgHigh = 1.35;
   meanPolFileName="/home/craigp/rootbeer2.1/dat/pol/manual_1.3_runs_meanpol.dat";
   paraPolTable="/home/clasg8/rootbeer2.1/PolTables_1.3_Manual_PARA.dat";
   perpPolTable="/home/clasg8/rootbeer2.1/PolTables_1.3_Manual_PERP.dat";
      
   break;
  case 1500:
  
    EgLow = 1.1;
    EgHigh = 1.55;
    meanPolFileName="/home/craigp/rootbeer2.1/dat/pol/total_1.5_runs_meanpol.dat";
      paraPolTable="/home/clasg8/rootbeer2.1/PolTables_1.5_Manual_PARA.dat";
      perpPolTable="/home/clasg8/rootbeer2.1/PolTables_1.5_Manual_PERP.dat";
      break;
      case 1700: //manual
      EgLow = 1.3;
      EgHigh = 1.75;
      meanPolFileName="/home/craigp/rootbeer2.1/dat/pol/total_1.7_runs_meanpol.dat";
      paraPolTable="/home/clasg8/rootbeer2.1/PolTables_1.7_Manual_PARA.dat";
      perpPolTable="/home/clasg8/rootbeer2.1/PolTables_1.7_Manual_PERP.dat";
      break;
      case 1701: //auto
      EgLow = 1.3;
      EgHigh = 1.75;
      meanPolFileName="/home/craigp/rootbeer2.1/dat/pol/total_1.7_runs_meanpol.dat";
      paraPolTable="/home/clasg8/rootbeer2.1/PolTables_1.7_Auto_PARA.dat";
      perpPolTable="/home/clasg8/rootbeer2.1/PolTables_1.7_Auto_PERP.dat";
      currentMode=SWAP;
      break;
      case 1900:
      EgLow = 1.5;
      EgHigh = 1.95;
      meanPolFileName="/home/craigp/rootbeer2.1/dat/pol/auto_1.9_runs_meanpol.dat";
      paraPolTable="/home/clasg8/rootbeer2.1/PolTables_1.9_Auto_PARA.dat";
      perpPolTable="/home/clasg8/rootbeer2.1/PolTables_1.9_Auto_PERP.dat";
      currentMode=SWAP;
      break;
      case 2100:
      EgLow = 1.7;
      EgHigh = 2.15;
      meanPolFileName="/home/craigp/rootbeer2.1/dat/pol/manual_2.1_runs_meanpol.dat";
      paraPolTable="/home/clasg8/rootbeer2.1/PolTables_2.1_Manual_PARA.dat";
      perpPolTable="/home/clasg8/rootbeer2.1/PolTables_2.1_Manual_PERP.dat";
      break;
      default:
      EgLow = 0.0;
      EgHigh = 0.0;
      cerr << "Fatal Error: Unknown value on energy_setting " <<  EgSetting << endl;

      break;
      }

  if(!Sim){
    //load pol tables
    if((LoadPolTable(PARA,paraPolTable ))!=0) return;
    if((LoadPolTable(PERP,perpPolTable ))!=0) return;
  }


  //make an array of bin edges for the tagger based on the ecounter centres.
  for(int b=1;b<384;b++){
    gBinsArray[b]=0.0005*(polTable[PARA][0][385-b][ENERGY]+polTable[PARA][0][384-b][ENERGY]); //mean of centred conv to GeV
  }
  gBinsArray[0]=gBinsArray[1]-0.5*(gBinsArray[2]-gBinsArray[1]);
  gBinsArray[384]=gBinsArray[383]+0.5*(gBinsArray[383]-gBinsArray[382]);

  //hists for working out the mean pol.
  meanPol[PARA]=new TH1F("meanPolPARA","meanPolPARA",384,0,384);
  meanPol[PERP]=new TH1F("meanPolPERP","meanPolPERP",384,0,384);
  eventsPol[PARA]=new TH1F("eventsPolPARA","eventsPolPARA",384,0,384);
  eventsPol[PERP]=new TH1F("eventsPolPERP","eventsPolPERP",384,0,384);
  meanPolG[PARA]=new TH1F("meanPolGPARA","meanPolGPARA",384,gBinsArray);
  meanPolG[PERP]=new TH1F("meanPolGPERP","meanPolGPERP",384,gBinsArray);
  eventsPolG[PARA]=new TH1F("eventsPolGPARA","eventsPolGPARA",384,gBinsArray);
  eventsPolG[PERP]=new TH1F("eventsPolGPERP","eventsPolGPERP",384,gBinsArray);
  meanPol[PARA]->SetStats(kFALSE);
  meanPol[PARA]->GetXaxis()->SetTitle("E_ID");
  meanPolG[PARA]->SetStats(kFALSE);
  meanPolG[PARA]->GetXaxis()->SetTitle("E_{#gamma} (GeV)");



  gettagcalib();

  PartTree =  new TTree("PartTree","Tree of Particle 4-Vectors");
  PartTree->Branch("lP","TLorentzVector",&lP,32000,0); 
  PartTree->Branch("lPiplus","TLorentzVector",&lPiplus,32000,0); 
  PartTree->Branch("lPiminus","TLorentzVector",&lPiminus,32000,0); 
  PartTree->Branch("lPhoton","TLorentzVector",&lPhoton,32000,0); 
  PartTree->Branch("lTarget","TLorentzVector",&lTarget,32000,0); 
  PartTree->Branch("lppipi","TLorentzVector",&lppipi,32000,0); 
  PartTree->Branch("lMissing_Pizero","TLorentzVector",&lMissing_Pizero,32000,0); 
  PartTree->Branch("lKzero","TLorentzVector",&lKzero,32000,0); 
  PartTree->Branch("lSigma","TLorentzVector",&lSigma,32000,0); 
  PartTree->Branch("lMissing_Sigma","TLorentzVector",&lMissing_Sigma,32000,0); 
  PartTree->Branch("lpipipi","TLorentzVector",&lpipipi,32000,0); 
  PartTree->Branch("polPlane",&currentPlane,"currentPlane/I");
  PartTree->Branch("polRadiator",&currentRadiator,"currentRadiator/I");
  PartTree->Branch("polDegree",&polDegree,"polDegree/F");
  PartTree->Branch("cohEdge",&currentEdge,"cohEdge/D");
 

  
  //                                                                    *
  // ******* End of User initialisation  ********************************
  char tempfname[128]; 
  int nEpicEvent = 0;      //Epics event counter
  int nEpicEventTen = 0;
  int RunNum=0;            //File number counter   
  char *tempstr;
  int run;                 //run no, extracted from current file name
  int RunNos[1000];         //store the numbers of the runs
  int NRuns=0;
  for(int n=0;n<1000;n++)RunNos[n]=0;

  // ********************** main file loop **********************************************************
  //                                                                                                *
  while((fileNo=getNextFile(inFile,file))!=-1){  // loop while files are still avialable 

 
    // Start of user stuff to do before sorting each file  ---------------
    fprintf(stderr,"Sorting file - %s\n",inFile);

    //If not a simulation get the stuff per run.
    if(!Sim){
      //get the run number from the file name by finding the last _ and scanning remainder for an int
      //    sscanf(strrchr(inFile,'_')+1,"%d",&run);
      sscanf(strstr(inFile,"flist_0")+7,"%d",&run);
      if(!NRuns)RunNos[NRuns++]=run;
      else if(run!=RunNos[NRuns-1])RunNos[NRuns++]=run;
      
      

      //get all the values for the variables from the line in the table for that run.
      //if failure, delete skip to next file.
      if(g8bTable->GetAllForValue(run,"Run")<0) continue;         //if not found do next file
      
      if(strstr(g8b_Radiat,"AMO")) {
	currentRadiator=AMORPHOUS;     //if big table says AMO we use that
	currentPlane=AMO;     //if big table says AMO we use that
      }
      else{
	currentRadiator=DIAMOND;
	sprintf(edgeTable,"/home/clasg8/rootbeer2.1/dat/pol/run_%d_pol_edges.dat",run);
	LoadEdgeTable(edgeTable);
      }
      // return;
      // End of user stuff to do before sorting each file  ---------------
    }

    if((rootbeer=createBeerObject(inFile))==NULL){              // create rootbeer object
      fprintf(stdout,"WARNING. Unable to open %s, continuing to next file\n",inFile);
      continue;
    }
    rootbeer->SetBankStatus(mybanks,ON);			// switch on the banks required
    rootbeer->StartServer();                  			// start the server running
    rootbeer->ListServedBanks();			       	// list the banks which will be served

    event=0;		//zero the event counter for the file

    // ********************** main event loop ******************************************************
    //                                                                                             *

    while(event>=0){                                           	// do all events
      event = rootbeer->GetEvent();                            	// get next event

      // Start of user customized section ----------------------------


      if(currentRadiator!=AMORPHOUS){
	GetEdge(HEAD[0].NEVENT,&currentEdge,&currentPlane); //get the current edge position
      }

      if(firstPIDCut()!=0) continue;
      if(kinematicCuts()!=0) continue;

      outFile->cd();
      PartTree->Fill();
   

      // End of user customized section ----------------------------

      eventTot++;
      if(eventTot%1000 == 0) fprintf(stdout,"done %d\n",eventTot);
      if((nEvents>0)&&(eventTot >=nEvents)) break;		//break if nEvents done
    }
    //                                                                                             *
    // ********************** end of main event loop ***********************************************

    // Start of user stuff to do after sorting each file  ---------------
    fprintf(stdout,"sorted %d events from file: %s\n",abs(event),inFile);
    // End of user stuff to do after sorting each file  ---------------

    delete rootbeer;                              		//Call the class destructor
    if((nEvents>0)&&(eventTot >=nEvents)) break;		//break if nEvents done
  }
  //                                                                                                *
  // ********************** end of main file loop ***************************************************



  // ******** Do any final stuff here ***********************************
  //                                                                    *
  // Start of user stuff to do at the end  ------------------------

  //Divide the polarization totals by the no of events to get the mean
  meanPol[PARA]->Divide(eventsPol[PARA]);
  meanPol[PERP]->Divide(eventsPol[PERP]);
  meanPolG[PARA]->Divide(eventsPolG[PARA]);
  meanPolG[PERP]->Divide(eventsPolG[PERP]);

  Char_t ctitle[128];
  Char_t giftitle[128];
  Char_t Ctitle[128];
  Char_t dattitle[128];
  Char_t *FILELIST;
  Char_t *LABEL;
  FILE *fp;

  //We want to draw these on a canvas and save as gifs and .C files, and write out the mean pol tables.

  if((FILELIST=getenv("FILELIST"))&&(LABEL=getenv("LABEL"))){
  sprintf(ctitle,"MeanPol_%s_%s (PARA:Red, PERP:Blue)",LABEL,FILELIST);
  sprintf(giftitle,"MeanPol_%s_%s.gif",LABEL,FILELIST);
  sprintf(Ctitle,"MeanPol_%s_%s.C",LABEL,FILELIST);
  sprintf(dattitle,"MeanPol_%s_%s.dat",LABEL,FILELIST);
  }
  else{
  sprintf(ctitle,"MeanPol (PARA:Red, PERP:Blue)"); 
  sprintf(giftitle,"MeanPol.gif");
  sprintf(Ctitle,"MeanPol.C");
  sprintf(dattitle,"MeanPol.dat");
  }
  c = new TCanvas("c", ctitle, 50,50,800, 600);
  meanPolG[PARA]->SetLineColor(2);
  meanPolG[PERP]->SetLineColor(4);
  meanPolG[PARA]->SetTitle(ctitle);
  meanPolG[PERP]->SetTitle(ctitle);
  meanPolG[PARA]->SetMinimum(0);
  meanPolG[PARA]->SetMaximum(1);
  meanPolG[PERP]->SetMinimum(0);
  meanPolG[PERP]->SetMaximum(1);
  meanPolG[PARA]->GetXaxis()->SetRangeUser(0.9,2.5);
  meanPolG[PERP]->GetXaxis()->SetRangeUser(0.9,2.5);
  meanPolG[PARA]->Draw();
  meanPolG[PERP]->Draw("same");
  
  c->SaveAs(giftitle);
  c->SaveAs(Ctitle);
  
  fp=fopen(dattitle,"w");
  
  fprintf(fp,"#%s\n",ctitle);
  fprintf(fp,"#Prog command was: ");
  for(int n=0;n<progArgc;n++){
  fprintf(fp," %s",progArgv[n]);
  }
  fprintf(fp,"\n#Eg(MeV)\tE_ID\tPARA\tPERP\n");
  for(int n=1;n<385;n++){
  fprintf(fp,"%5.1f\t\t%d\t%5.3f\t%5.3f\n",polTable[PARA][0][385-n][ENERGY],n,
  	    meanPolG[PARA]->GetBinContent(n),meanPolG[PERP]->GetBinContent(n));
  }
  fprintf(fp,"#The following runs were used for this mean table\n");  
  for(int n=0;n<NRuns;n++){
  fprintf(fp,"#%d\n",RunNos[n]);
  }
  fclose(fp);


fprintf(stdout,"Sorted Total of  %d events\n",eventTot);
  // End of user stuff to do at the end  --------------------------

#ifdef ROOTEXE
  //if it's an executable, write to the output file
  outFile->Write();
  outFile->Close();
#endif
  //                                                                    *
  // ********************************************************************
}
// ---------- end of user main function  -----------------------------------------------

int parseArgs2(int argc,char **argv){
  char *cvalue = NULL;
  int index;
  int c;
  int haveInFile=0;
  
  progArgv=argv,
  progArgc=argc,

  opterr = 0;
  
  switch(argc){
  case 1:    			// 1, 2 args not enough
  case 2:
    printUsage();
    return(-1);
    break;
  default:
    break;
  }
  
  while ((c = getopt (argc, argv, "M:N:C:L:E:d:D:p:P:L:")) != -1){
    switch (c){
    case 'M': // Simulated data
      Sim=1;      
      currentRadiator=AMORPHOUS;
      currentPlane=AMO;
      currentEdge=-1.0;

      break;
    case 'N':
      sscanf(optarg,"%d",&nEventsTot);
      break;
    case 'C':
      sscanf(optarg,"%d",&Column);
      break;
    case 'E':
      sscanf(optarg,"%d",&EgSetting);
      break;
    case 'p':
      sscanf(optarg,"%lf",&polLeft);
      break;
    case 'P':
      sscanf(optarg,"%lf",&polRight);
      break;
    case 'd':
      sscanf(optarg,"%lf",&ELeft);
      break; 
    case 'D':
      sscanf(optarg,"%lf",&ERight);
      break;
    case 'L':
      sprintf(InFileName,"-L%s",optarg);
      haveInFile=1;
      break;
    case '?':
      fprintf (stderr,
	       "Unknown option character `\\x%x'.\n",
	       optopt);
      printUsage();
      return -1;
    default:
      printUsage();
      return -1;
    }
  }
  sprintf(OutFileName,"%s",argv[argc-1]);
  if(!haveInFile)sprintf(InFileName,"%s",argv[argc-2]);
  for (index = optind; index < argc; index++) printf ("Non-option argument %s\n", argv[index]);

  

  return 0;
}



// ---------- required parseArgs() function  -------------------------------------------
// parses the input args when running as an executable

// set up the no of events, and input and output file names in global variables
// or prints usage
int parseArgs(int argc,char **argv){
  switch(argc){
  case(1):				// 1, 2 or 3 args not enough
  case(2):
  case(3):
    printUsage();
    return(-1);
    break;
  case(4):				// 4 args g8Ana_exp_lite
					// <infile> <outfile> -E<energy>
    if((strstr(argv[1],"-N"))!=NULL){
      printUsage();
      return(-1);
    }
    else{
      strcpy(InFileName,argv[1]);
      strcpy(OutFileName,argv[2]);
      sscanf(argv[3]+2,"%d",&EgSetting);
    }
    break;
  case(5):				// 5 args must be "g8Ana -N# <infile> <outfile> -E<energy>" 
    if(strncmp(argv[1],"-N",2)!=0){  	//print usage then exit */
      printUsage();
      return(-1);
    }
    else{
      sscanf(argv[1]+2,"%d",&nEventsTot);	//get the required event no
      strcpy(InFileName,argv[2]);
      strcpy(OutFileName,argv[3]);
      sscanf(argv[4]+2,"%d",&EgSetting);
    }      
    break;
  default:
    printUsage();
    return(-1);
    break;
  }
  printf("Energy Setting: %d\n", EgSetting);
  return(0);
}
// ---------- end of required parseArgs() function  -------------------------------------

// ---------- required printUsage() function  -------------------------------------------
// When running as executable, gets called if no args, or silly args
void printUsage(){
  fprintf(stderr,"\nusage:\n\n");
  fprintf(stderr,"g8Ana -h   Print this message\n\n");
  fprintf(stderr,"g8Ana [options] <infile> <outfile.root> \n");
  fprintf(stderr,"g8Ana [options] <-Lfilelist> <outfile.root> \n");
  fprintf(stderr,"\nOptions are:\n");
  fprintf(stderr,"\t-E<edge>\tAllowed values for edge are:\n");
  fprintf(stderr,"\t\t\t1300: For 1300MeV Coherent Edge, Manual Data (Default)\n");
  fprintf(stderr,"\t\t\t1500: For 1500MeV Coherent Edge, Manual Data\n");
  fprintf(stderr,"\t\t\t1700: For 1700MeV Coherent Edge, Manual Data\n");
  fprintf(stderr,"\t\t\t1701: For 1700MeV Coherent Edge, Auto Data\n");
  fprintf(stderr,"\t\t\t1900: For 1900MeV Coherent Edge, Auto Data\n");
  fprintf(stderr,"\t\t\t2100: For 2100MeV Coherent Edge, Manual Data\n");
  fprintf(stderr,"\n\t-C<column>\tAllowed values for column are:\n");
  fprintf(stderr,"\t\t\t5,6,8 (= PFIT,PCOR(default),PSMOOTH)\n");
  fprintf(stderr,"\n\t-p<polLeft>\tAllowed values for polLeft are (0.0 - 1.0) default= 0.0\n");
  fprintf(stderr,"\t-P<polRight>\tAllowed values for polRight are (0.0 - 1.0)default= 0.0\n");
  fprintf(stderr,"\n\t-e<ELeft>\tAcceptable range to left of Coh Peak -  Allowed values for ELeft are 100.0 - 500.0 (default)\n");
  fprintf(stderr,"\t-E<ERight>\tAcceptable range to right of Coh Peak -  Allowed values for ERight are 0.0 - 200.0 (default)\n");
  
  
}
// ---------- end of required printUsage() function  -------------------------------------------




//////////////////////////////////////////////Extra Functions

//My functions
//limits for particle m^2 cuts;
const float piCutLow = 0.0;
const float piCutHigh = 0.1;
const float PCutLow = 0.49;
const float PCutHigh = 1.44;


const float vl = 29.9792458;


  //Get Tagger Energy Calibration

  int gettagcalib(){
  char line[100];
  // float e_correction[726];
  float blah=0.0;
  FILE *ffp; 

  if((ffp = fopen("/home/bryanm/g8/g10_PS_measured_taggEcorr.dat","r")) == NULL){    //open file
    fprintf(stderr,"couldn't open file: %s\n","g8/newegcor.dat");
    return -1;
  }

  for(int channel=1;channel<770;channel++){
    if(fgets(line,80,ffp) == NULL) break;          // check got a line from file
    if((line[0] == '*')||(line[0] == '#')) continue;
    sscanf(line,"%f%f",&blah,&e_correction[channel]);         // get chan and content
    //cout << blah << "::" << e_correction[channel] << endl;
  }

  fclose(ffp);

  return(0);

  }



int firstPIDCut(){
  //Function to do initial event selection
  //Some of this may be taken care of in dstmaker...
  
  Double_t W, CosT;
  
  float bcp=0.0;
  float bcpip=0.0;
  float bcpim=0.0;
  float vertp=0.0;
  float vertpip=0.0;
  float vertpim=0.0;
  float bestTime=10000.0;
  int bestPhoton=-1;
  float timeDif=0.0;
  float timeDifpip=0.0;
  float timeDifpim=0.0;


//   //cutting on p,k+,k- - also allowing 1 neutral 
  int nPiPlus=0;	//counters for no of each particle type in event
  int nPiMinus=0;
  int nProton=0;
  int nNeutral=0;
  int pID=0;	// for the id of the hit in the EVNT bank
  int piplusID=0;
  int piminusID=0;
  int nID=0;
  float mass=0.0;
  float pm=0.0;
  float pipm=0.0;
  float pimm=0.0;
  
  //Polarization info
  float pol_degree;
  float coh_edge;
  
  
  
  

  ///////////////////////////Event Loop////////////////////////////////////
  
  
  
  if(Sim){
    currentPlane=AMO;
    currentRadiator=AMORPHOUS;
  }
  if((currentRadiator==DIAMOND)&&(currentMode==SWAP)&&(EPIC_NS)){
    //Loop over EPICs events first to get info on coherent plane
    nEpicEvent++;
    getEpics("coh_plane",&plane);
    // cout<<"coh_plan = "<<plane<<endl;
    currentPlane=(int)plane;   
  }
  
  
  


  if((EVNT_NH<3)||(EVNT_NH>4)||(TAGR_NH==0)) return -1; //ret. if not 3 or 4 hits or no hit in tagger
  
  
  for(int nhit=0;nhit<EVNT_NH;nhit++){  //loop over all hist
    mass=(((1/pow(EVNT[nhit].Beta,2))-1)*(pow(EVNT[nhit].Cx*EVNT[nhit].Pmom,2)+pow(EVNT[nhit].Cy*EVNT[nhit].Pmom,2)+pow(EVNT[nhit].Cz*EVNT[nhit].Pmom,2)));
    if(EVNT[nhit].Charge == 0){ // neutral particle
      nNeutral++;
      nID=nhit;
    }
    else{			// charged particle
      //must have valid dc and either sc or ec
      if((EVNT[nhit].DCstat == 0)||((EVNT[nhit].ECstat == 0)&&(EVNT[nhit].SCstat == 0))) return -1;
      if(EVNT[nhit].Charge==1){	//look for p or k+
	if((mass>=piCutLow)&&(mass<piCutHigh)){
	  nPiPlus++;
	  piplusID=nhit;
	  pipm=mass;
	}
	else if((mass>=PCutLow)&&(mass<PCutHigh)){
	  nProton++;
	  pID=nhit;
	  pm=mass;
	}
	else return -1;
      }
      else if(EVNT[nhit].Charge==-1){ // look for k-
	if((mass>=piCutLow)&&(mass<piCutHigh)){
	  nPiMinus++;
	  piminusID=nhit;
	  pimm=mass;
	}
	else return -1;
      }
    }
  }
    if(EVNT_NH==3){	// if 3, must be p,k+,k-
    if(!((nPiPlus)&&(nPiMinus)&&(nProton)))  return -1;
  }
  else{			// if 4 must be p, k+, k- ,neutral
    if(!((nPiPlus)&&(nPiMinus)&&(nProton)&&(nNeutral))) return -1;
  }
  mult->Fill(EVNT_NH);

  pzvertex->Fill(EVNT[pID].Z);
  pipzvertex->Fill(EVNT[piplusID].Z);
  pimzvertex->Fill(EVNT[piminusID].Z);
  if((EVNT[pID].Z>0)||(EVNT[pID].Z<(-40))) return -1;



  lP->SetXYZM(EVNT[pID].Cx*EVNT[pID].Pmom,EVNT[pID].Cy*EVNT[pID].Pmom,EVNT[pID].Cz*EVNT[pID].Pmom,PROTON_MASS);
  lPiplus->SetXYZM(EVNT[piplusID].Cx*EVNT[piplusID].Pmom,EVNT[piplusID].Cy*EVNT[piplusID].Pmom,EVNT[piplusID].Cz*EVNT[piplusID].Pmom,PI_CHARGED_MASS);
  lPiminus->SetXYZM(EVNT[piminusID].Cx*EVNT[piminusID].Pmom,EVNT[piminusID].Cy*EVNT[piminusID].Pmom,EVNT[piminusID].Cz*EVNT[piminusID].Pmom,PI_CHARGED_MASS);


  bcp=(lP->Rho())/sqrt((lP->Rho()*lP->Rho())+(PROTON_MASS*PROTON_MASS));
  bcpip=(lPiplus->Rho())/sqrt((lPiplus->Rho()*lPiplus->Rho())+(PI_CHARGED_MASS*PI_CHARGED_MASS));
  bcpim=(lPiminus->Rho())/sqrt((lPiminus->Rho()*lPiminus->Rho())+(PI_CHARGED_MASS*PI_CHARGED_MASS));
  
  vertp=((SCPB[EVNT[pID].SCstat-1].Time)-((SCPB[EVNT[pID].SCstat-1].Path)/(vl*bcp)));
  vertpip=((SCPB[EVNT[piplusID].SCstat-1].Time)-((SCPB[EVNT[piplusID].SCstat-1].Path)/(vl*bcpip)));
  vertpim=((SCPB[EVNT[piminusID].SCstat-1].Time)-((SCPB[EVNT[piminusID].SCstat-1].Path)/(vl*bcpim)));
  
  
  
  

  for(int photon=0;photon<TAGR_NH;photon++){
    if((TAGR[photon].STAT!=15)&&(TAGR[photon].STAT!=7)) continue; //check good photon 

    timeDif=(((SCPB[EVNT[pID].SCstat-1].Time)-((SCPB[EVNT[pID].SCstat-1].Path)/(vl*bcp)))-((TAGR[photon].TPHO)+((EVNT[pID].Z)/vl))-0.907);
      if(pow(timeDif,2)<pow(bestTime,2)){
  	bestTime=timeDif;
	bestPhoton=photon;
	timeDifpip=(((SCPB[EVNT[piplusID].SCstat-1].Time)-((SCPB[EVNT[piplusID].SCstat-1].Path)/(vl*bcpip)))-((TAGR[bestPhoton].TPHO)+((EVNT[piplusID].Z)/vl))-0.907);
	timeDifpim=(((SCPB[EVNT[piminusID].SCstat-1].Time)-((SCPB[EVNT[piminusID].SCstat-1].Path)/(vl*bcpim)))-((TAGR[bestPhoton].TPHO)+((EVNT[piminusID].Z)/vl))-0.907);
      }
  }

  if(!Sim){
    
    //Extract the photon polarization information
    //Nothing in the photon pol stops the event going into the tree for likelihood, or other analysis.
    //However, if the photon pol does not meet the following criteria it is flagged as 99.9.
    //To fill histograms like phi distribs, where they will be fitted later, and mean polarizations used, 
    
    if(((currentPlane==PARA)||(currentPlane==PERP))&&((currentEdge>0.0)&&(1000.0*TAGR[bestPhoton].ERG >currentEdge-ELeft)&&(1000.0*TAGR[bestPhoton].ERG<currentEdge+ERight))){       
      //	polDegree=GetPol(currentPlane,currentEdge,(int)((TAGR[bestPhoton].E_id+0.5)/2.0),PSMOOTH,0.2,0.3);
      polDegree=GetPol(currentPlane,currentEdge,(int)((TAGR[bestPhoton].E_id+1.0)/2.0),Column,polLeft,polRight);
      
      //Now use Mikes correction
      polDegree=mikeTest(polDegree,1000.0*TAGR[bestPhoton].ERG,currentEdge,currentPlane,EgSetting);  //Ken2
      
      //cout << "Event:" << HEAD[0].NEVENT << "  Edge:" << currentEdge <<  " E_ID:" << (int)((TAGR[bestPhoton].E_id+0.5)/2.0) 
      //     << " Eg:" << TAGR[bestPhoton].ERG << " Pol:" << polDegree << endl;
      if((polDegree>0.0) && (polDegree<1.0)){
	meanPol[currentPlane]->Fill((int)((TAGR[bestPhoton].E_id+1.0)/2.0),polDegree);
	eventsPol[currentPlane]->Fill((int)((TAGR[bestPhoton].E_id+1.0)/2.0));
	meanPolG[currentPlane]->Fill(TAGR[bestPhoton].ERG,polDegree); 
	eventsPolG[currentPlane]->Fill(TAGR[bestPhoton].ERG);
      }
    }
    else{
      polDegree=99.9;
    }
    
  }


  lPhoton->SetPxPyPzE(0,0,(TAGR[bestPhoton].ERG*e_correction[TAGR[bestPhoton].E_id]),(TAGR[bestPhoton].ERG*e_correction[TAGR[bestPhoton].E_id]));
  //lPhoton->SetPxPyPzE(0,0,TAGR[bestPhoton].ERG,TAGR[bestPhoton].ERG);
  Photon_Energy->Fill(lPhoton->E());
  //epho_vs_tpho->Fill(TAGR[bestPhoton].ERG,TAGR[bestPhoton].TPHO);


  lP->SetXYZM(EVNT[pID].Cx*EVNT[pID].Pmom,EVNT[pID].Cy*EVNT[pID].Pmom,EVNT[pID].Cz*EVNT[pID].Pmom,PROTON_MASS);
  lPiplus->SetXYZM(EVNT[piplusID].Cx*EVNT[piplusID].Pmom,EVNT[piplusID].Cy*EVNT[piplusID].Pmom,EVNT[piplusID].Cz*EVNT[piplusID].Pmom,PI_CHARGED_MASS);
  lPiminus->SetXYZM(EVNT[piminusID].Cx*EVNT[piminusID].Pmom,EVNT[piminusID].Cy*EVNT[piminusID].Pmom,EVNT[piminusID].Cz*EVNT[piminusID].Pmom,PI_CHARGED_MASS);


  
  ptvertex_tgamma->Fill(bestTime);
  ptvtg_Pmom->Fill(lP->P(),bestTime);
  piptvertex_tgamma->Fill(timeDifpip);  
  piptvtg_pipmom->Fill(lPiplus->P(),timeDifpip);  
  pimtvertex_tgamma->Fill(timeDifpim);
  pimtvtg_pimmom->Fill(lPiminus->P(),timeDifpim);  


  if(pow(bestTime,2)>pow(firstTimeCut,2)) return -1; //remove for S Weights
  if(pow(timeDifpip,2)>pow(firstTimeCut,2)) return -1; //remove for S Weights
  if(pow(timeDifpim,2)>pow(firstTimeCut,2)) return -1; //remove for S Weights

  piplustofmass->Fill(pipm);	// fill the tof mass hists
  piminustofmass->Fill(pimm);
  ptofmass->Fill(pm);

  ptvtg_Pmoma->Fill(lP->P(),bestTime);
  piptvtg_pipmoma->Fill(lPiplus->P(),timeDifpip);
  pimtvtg_pimmoma->Fill(lPiminus->P(),timeDifpim);
  ptvertex_tgammaa->Fill(bestTime);
  piptvertex_tgammaa->Fill(timeDifpip);  
  pimtvertex_tgammaa->Fill(timeDifpim);



  //Do energy losses here
  //Run eLoss    
  //Proton
  //construct 4 vector 
  p_out->SetXYZM(EVNT[pID].Pmom*EVNT[pID].Cx,
		 EVNT[pID].Pmom*EVNT[pID].Cy,
		 EVNT[pID].Pmom*EVNT[pID].Cz,
		 PROTON_MASS);
  // make 3vector for vertex
  vert.SetXYZ(EVNT[pID].X,EVNT[pID].Y,EVNT[pID].Z);
  //call eloss
  p_in=eLoss(lP,PROTON_MASS,vert,ELOSS_TARG_LH2,ELOSS_CELL_g8b);
  //histogram out the eloss in MeV
  elossp->Fill(1000.0*(p_in->P()-lP->P()));
  //Plot vs mom...
  elossp_mom->Fill(lP->P(),1000.0*(p_in->P()-lP->P()));
  //fprintf(stderr,"p_loss=%5.2f \n",1000.0*(p_in.P()-p_out.P()));
  //Reset 4-Vector to eloss values
  lP->SetXYZM(p_in->X(),p_in->Y(),p_in->Z(),p_in->M());
       
     
     
  //pi+
  p_out->SetXYZM(EVNT[piplusID].Pmom*EVNT[piplusID].Cx,
		 EVNT[piplusID].Pmom*EVNT[piplusID].Cy,
		 EVNT[piplusID].Pmom*EVNT[piplusID].Cz,
		 PI_CHARGED_MASS);
  // make 3vector for vertex
  vert.SetXYZ(EVNT[piplusID].X,EVNT[piplusID].Y,EVNT[piplusID].Z);
  //call eloss
  p_in=eLoss(lPiplus,PI_CHARGED_MASS,vert,ELOSS_TARG_LH2,ELOSS_CELL_g8b);
  //histogram out the eloss in MeV
  elosspip->Fill(1000.0*(p_in->P()-lPiplus->P()));
  //plot vs mom...
  elosspip_mom->Fill(lPiplus->P(),1000.0*(p_in->P()-lPiplus->P()));
  //Reset 4-Vector to eloss values
  lPiplus->SetXYZM(p_in->X(),p_in->Y(),p_in->Z(),p_in->M());

  //pi-
  p_out->SetXYZM(EVNT[piminusID].Pmom*EVNT[piminusID].Cx,
		 EVNT[piminusID].Pmom*EVNT[piminusID].Cy,
		 EVNT[piminusID].Pmom*EVNT[piminusID].Cz,
		 PI_CHARGED_MASS);
  // make 3vector for vertex
  vert.SetXYZ(EVNT[piminusID].X,EVNT[piminusID].Y,EVNT[piminusID].Z);
  //call eloss
  p_in=eLoss(lPiminus,PI_CHARGED_MASS,vert,ELOSS_TARG_LH2,ELOSS_CELL_g8b);
  //histogram out the eloss in MeV
  elosspim->Fill(1000.0*(p_in->P()-lPiminus->P()));
  //plot vs mom...
  elosspim_mom->Fill(lPiminus->P(),1000.0*(p_in->P()-lPiminus->P()));
  //Reset 4-Vector to eloss values
  lPiminus->SetXYZM(p_in->X(),p_in->Y(),p_in->Z(),p_in->M());


  

  proton->Fill(lP->M());											
  piplus->Fill(lPiplus->M());											
  piminus->Fill(lPiminus->M());


  return(0); 
}

int kinematicCuts(){

  //////////////////////////////////Full Egamma

  if(lPhoton->E()>0){
  *lppipi=(*lTarget + *lPhoton)-(*lP + *lPiplus + *lPiminus);

  //*lMissing_Pizero=(*lTarget + *lPhoton)-(*lP + *lPiplus + *lPiminus);						
  MMPpipi->Fill(lppipi->M());	

  //cout << lMissing_Pizero->M() << endl;

  //if((lppipi->M()<0.08)||(lppipi->M()>0.2)) return -1; remove for S Weights
  *lKzero=(*lPiplus + *lPiminus);
  Mpippim->Fill(lKzero->M());

  lMissing_Pizero->SetXYZM(lppipi->X(),lppipi->Y(),lppipi->Z(),PI_ZERO_MASS);
  Mpi0->Fill(lMissing_Pizero->M());

  *lpipipi=(*lPiplus + *lPiminus + *lMissing_Pizero);
  M3pi->Fill(lpipipi->M());

  *lSigma=(*lP + *lMissing_Pizero);
  MPpi0->Fill(lSigma->M());

  *lMissing_Sigma=(*lTarget + *lPhoton)-(*lPiplus + *lPiminus);

  MpippimvsMMpippim->Fill(lKzero->M(),lMissing_Sigma->M());
  MpippimvsMPpi0->Fill(lKzero->M(),lSigma->M());

  }			
  return(0);													
}


TLorentzVector* lab_to_cm(TLorentzVector *lab_part1, TLorentzVector *lab_part2, TLorentzVector *v4part3)
{
  // Add particles 1 and 2 in the lab frame to define the cms frame 
//   TLorentzVector v4lab = lab_part1 + lab_part2;

//   TVector3 boost_cms = v4lab.BoostVector();

//   v4part3.Boost(boost_cms);

//   return v4part3;

  TLorentzVector v4lab = *lab_part1 + *lab_part2;

  TVector3 v3part3 = v4part3->Vect();

  // Get the beta and boost vector for the cms frame of part1 and part2
  double beta_cms =  v4lab.Beta();
  TVector3 boost_cms = v4lab.BoostVector();
  
  // Transform v3part3 into the cms frame of part1 and part2
  TVector3 cms_v3part3 = v3part3 + boost_cms*(((v4lab.Gamma()-1)/(beta_cms*beta_cms))*v3part3.Dot(boost_cms) - v4lab.Gamma()*v4part3->E());

  // Get the energy for the cms 4-vector
  double cms_part3_E = sqrt(v4part3->M()*v4part3->M() + cms_v3part3.Px()*cms_v3part3.Px() + cms_v3part3.Py()*cms_v3part3.Py() + cms_v3part3.Pz()*cms_v3part3.Pz());

  TLorentzVector *cms_v4part3=new TLorentzVector(cms_v3part3.Px(), cms_v3part3.Py(), cms_v3part3.Pz(), cms_part3_E);
  return cms_v4part3;

}



int LoadPolTable(int plane, Char_t *PolTableList){
  FILE *fplist,*fpfile;              //file pointers for filelist and each file therein
  Char_t lline[250];                 //for reading in lines from filelist
  Char_t fline[250];                 //for reading in lines from file
  Char_t filename[250];              //file
  Int_t  fcount=0;                   //counter for no of files read in
  Int_t  chancount=0;                //counter for no of channels read in
  Int_t  eid=0;
  Double_t edge=0.0;                 
  
  if((fplist=fopen(PolTableList,"r"))==NULL){ //open filelist
    cerr << "Error Couldn't open file: " << PolTableList << endl;
    return -1;
  }

  fcount=0; 
  //for each file in the list
  while(fgets(lline,240,fplist) != NULL){
    if((lline[0] == '*')||(lline[0] == '#')) continue; //skip comments
    sscanf(lline,"%s",filename);                       //read in filename
     
    cout << "opening " << filename << "   " << endl;
    if((fpfile=fopen(filename,"r"))==NULL){              //open file
      cerr << "Error Couldn't open file: " << filename << endl;
      return -1;
    }
        
    fgets(polFirstLines[plane][polTableN[plane]],240,fpfile ); //save the 1st line

    //scan the bit after the last "_" in the filename to get the edge energy
    sscanf(strrchr(filename,'_')+1,"%lg",&polTable[plane][fcount][0][EDGE]);

    chancount=0;                                             //starting array at 1 for consistency with E_ID
    while((fgets(fline,240,fpfile)) != NULL){
      if((fline[0] == '*')||(fline[0] == '#')) continue;     //skip comments    
      sscanf(fline,"%d",&eid);                               //first get the E_ID
      sscanf(fline,"%*d%lg%lg%lg%lg%lg%lg%lg%lg",
	     &polTable[plane][fcount][eid][ENERGY],
	     &polTable[plane][fcount][eid][ENH],
	     &polTable[plane][fcount][eid][ENHERR],
	     &polTable[plane][fcount][eid][ENHFIT],
	     &polTable[plane][fcount][eid][PFIT],
	     &polTable[plane][fcount][eid][PCOR],
	     &polTable[plane][fcount][eid][PCORERR],
	     &polTable[plane][fcount][eid][PSMOOTH]);
      chancount++; 
    }
    fclose(fpfile); //close the file
    if(chancount!=384){
      cerr << "Should be 384 lines in " << filename << " - only got " << chancount << endl;
      return -1;
    }
    polTableN[plane]++;
    
    fcount++;
  }

  fclose(fplist);

  return(0);
}

		
Double_t GetPol(Int_t plane, Double_t edge, Int_t eid, Int_t poltype = PSMOOTH, Double_t lowThresh=0.2, Double_t highThresh=0.3){
  //get polarization based on eid and edge position

  Int_t eIndex=0;
  Double_t pol=-1.0;
  
  //Check edge in in range of tables
  if((edge<polTable[plane][1][0][EDGE])||(edge>polTable[plane][polTableN[plane]-1][0][EDGE])) return -1.0;
  
  //  cout << "In range" << endl;

  //find index
  for(eIndex=0;eIndex<polTableN[plane];eIndex++){
    if(polTable[plane][eIndex][0][EDGE]>=edge) break;
  }
  //  cout << "Index = " << eIndex << endl;

  pol=polTable[plane][eIndex][eid][poltype];
  if((polTable[plane][eIndex][0][ENERGY]<edge)&&(pol<lowThresh)) pol = -1.0;
  if((polTable[plane][eIndex][0][ENERGY]>edge)&&(pol<highThresh)) pol = -1.0;

  return pol;
}


Double_t GetPol(Int_t plane, Double_t edge, Double_t eg, Int_t poltype = PSMOOTH, Double_t lowThresh=0.2, Double_t highThresh=0.3){
  //get polarization based on ephoton energy and edge position

  Int_t eIndex=0;
  Double_t pol=-1.0;
  Int_t eid=0;
  
  //Check edge in range of tables
  if((edge<polTable[plane][1][0][EDGE])||(edge>polTable[plane][polTableN[plane]-1][0][EDGE])) return -1.0;


  //find index
  for(int eIndex=0;eIndex<polTableN[plane];eIndex++){
    if(polTable[plane][eIndex][0][EDGE]>=edge) break;
  }
  cout << "Index = " << eIndex << endl;

  //find eid
  for(eid=1;eid<=384;eid++){
    if(polTable[plane][eIndex][eid][ENERGY]<=eg) break;
  }
  cout << "eid = " << eid <<endl;

  pol=polTable[plane][eIndex][eid][poltype];
  if((polTable[plane][eIndex][0][ENERGY]<edge)&&(pol<lowThresh)) pol = -1.0;
  if((polTable[plane][eIndex][0][ENERGY]>edge)&&(pol<highThresh)) pol = -1.0;

  return pol;
}


int LoadEdgeTable(Char_t *EdgeTable){
  FILE *fpfile;                      //file pointers for filelist and each file therein
  Char_t fline[250];                 //for reading in lines from file

  cout << "opening " << EdgeTable << "   " << endl;
  if((fpfile=fopen(EdgeTable,"r"))==NULL){              //open file
    cerr << "Error Couldn't open file: " << EdgeTable << endl;
    return -1;
  }


  edgeEventN=0;                      //initialize the counter
  edgeIndex=0;                       //and index for current table
  lastEdgeEvent=0;                   //etc
  lastCohEdge=0.0;
  lastCohPlane=-1;
  
  while((fgets(fline,240,fpfile)) != NULL){
    if((fline[0] == '*')||(fline[0] == '#')) continue;     //skip comments
    sscanf(fline,"%d%d%lg%d",        //scan in the tables
	   &edgeEventLow[edgeEventN],
	   &edgeEventHigh[edgeEventN],
	   &edgeEventEdge[edgeEventN],
	   &edgeEventPlane[edgeEventN]);
    edgeEventN++;                    //inc the counter fo the no of lines in the table
  }
  fclose(fpfile);
  return 0;
}

Int_t GetEdge(Int_t event, Double_t *edge, Int_t *plane){

  //check event no >= previous event
  
  if(event<lastEdgeEvent){
    cerr << "Warning: event (= " << event << ") is earlier than previous event (= " <<  lastEdgeEvent << ") - ignoring" << endl;
    return -1;
  }
  lastEdgeEvent=event;

  //keep going until we're in range or don't find a range 
  while((!((event >= edgeEventLow[edgeIndex])&&(event <= edgeEventHigh[edgeIndex])))&&(edgeIndex<edgeEventN)) edgeIndex++;
  if(edgeIndex>=edgeEventN){
    cerr << "Error: event (= " << event << ") is not in the range of this table" << endl;    
    edgeIndex=0; //reset to zero
    return -1;
  }
  *edge = edgeEventEdge[edgeIndex];
  *plane = edgeEventPlane[edgeIndex];
  return 0;
}


Double_t sagCor(Double_t Eg){
  
  Double_t Eb = 4.55;
  Double_t Ec = 0.0;
  Double_t T=0.0;
  Double_t Tc=0.0;
  Int_t  i = 0;


  T = (Eg/Eb) + sagU;

  if(T<0.401) i=0;
  else if((0.401<=T)&&(T<=0.674)) i=1;
  else if((0.647 < T)&& (T < 1.0)) i = 2;
  else{
    cerr << "Warning Eg out of range ( = " << Eg << " GeV)"  << endl;
    return -1.0;
  }

  Tc = T + sagA[0][i] + (sagA[1][i]*T) + (sagA[2][i]*T*T);
  Ec = Tc*Eb + sagB*Eg;
  
  return Ec;
}

  
Double_t mikeTest(Double_t pol, Double_t egamma, Double_t cohEdge, Int_t Plane, Int_t setting){
  //where pol is from lookup tables
  //egamma = photon energy in MeV
  //cohEdge = current coherent edge pos
  //plane = PARA (0), PERP (1)
  //setting = 1300,1500,1700,1701,1900,2100  (1701 = 1700 auto)

  Int_t paramSet=-1;
  Double_t eDiff=0.0;
  Double_t pF=1.0;
  Double_t norm=0.0;

  eDiff=(cohEdge-egamma)/1000.0;
  if((eDiff>width)||(eDiff<0.0)) return -1; //return if outwith width

  //get the param set from the setting

  switch(setting){
  case 1300:
    paramSet=0;
    break;
  case 1500:
    paramSet=1;
    break;
  case 1700:
    paramSet=2;
    break;
  case 2100:
    paramSet=3;
    break;
  case 1701:
    paramSet=4;
    break;
  case 1900:
    paramSet=5;
    break;
  default:
    cerr << "Fatal Error: Unknown value on energy_setting " <<  setting << endl;
    return -1.0;
    break;
  }
  
  
  pF=polFix0(eDiff,Plane,paramSet);
  norm=polFix0(diffFix,Plane,paramSet);
  pF /= norm;
  if (pF>0.0) pF=pol/pF;
  else pF=pol;
  
  return pF;
}

Double_t polFix0(Double_t xE, Int_t plane, Int_t parSet){
 
  Double_t yVal=0.0;
  Double_t tmpFun=1.0;
  Int_t region=-1;
  Double_t pF=-1.0;
  
  region=(int)(8.0*(xE)/width); //region 0-8
  
  yVal = (1.0/0.025)*xE-0.5;
  
  tmpFun = 1.0;
  if(region>=1){
    for(int r=1;r<=region;r++){
      tmpFun = tmpFun*(ldPar[parSet][plane][0] + ldPar[parSet][plane][1]*yVal);
      yVal = yVal - 1.0;
    }
  }
  pF = tmpFun;
  if (tmpFun==0.0) pF = 1.0;
  return pF;
}



