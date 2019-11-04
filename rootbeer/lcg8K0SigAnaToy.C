//************************************* rbtest.C *****************************//
//                      A part of the rootbeer package                        //
//                                                                            //
//                  Ken Livingstn (k.livingston@physics,gla,ac,uk)            //
//                                                                            //
//      Version         Date                    Comment                       //
//      1               21st Feb 2003                                         //
//      1.2d            23st Mar 2004           Simplified                    //
//      2.0             16th Sep 2005           All in root framework         //
//      2.1             20st Feb 2006           Buf fix edition               //
//                                                                            //
// ******************************* rbtest.C **********************************//

// A sample code to access BANKs in root.
// This code can be run as a root macro, or built as an executable:
// See http://nuclear.gla.ac.uk/~kl/rootbeer/manual/html/node5.php
// Or the tutorial in doc/manual.ps


// ******** required headers ********************************************
//                                                                      *
#include "RootBeerUtil.h"	//gets everything for RootBeer scheme
#include "TFile.h"              // for root files
//                                                                      *
// ******** end of required headers *************************************

// ******** my headers here *********************************************
//                                                                      *
#include "TH1.h"                // eg. for 1D Histogram                 
#include "TH2.h"                // eg. for 2D Histogram
#include "TLorentzVector.h"     //For Lorentz Vectors
#include "TMath.h"
#include "particleDEF.h"        //Particle Definitions
#include "TCanvas.h"
#include "TStyle.h"
#include "TSystem.h"
#include "TROOT.h"
#include "/home/louise/g8phi/haspect/Events/HaSpect/THSParticle.h"
#include "extra_packages/eloss_rb/eLoss.h"   

#include <iostream>
using namespace std;				// for debugging
//                                                                      *
// ******** end of my headers here **************************************

#define PARA 0                  //defs for polarisation plane
#define PERP 1
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

// ********** required global variables *********************************
//                                                                      *
// They are global to get easily filled by parseArgs()
int 	nEventsTot=0;			// ie do all events in all files
char  	InFileName[128];		// in file name parsed from args 
char  	OutFileName[128];		// out file name parsed from args

class TRootBeer *rootbeer;        	// The main class
//                                                                      *
// ********** end of required global variables **************************

// **************** my global variables *********************************
//                                                                      *
// Eg. my hists are global to be easily accessed from the 
// root> prompt after the function is called as a macro

class   TH1D *h0_massp;
class   TH1D *h0_massm;
class   TH1D *h0_massn;
class   TH1D *h0_momp;
class   TH1D *h0_momm;
class   TH1D *h0_zp;
class   TH1D *h0_zm;
class   TH1D *h0_betap;
class   TH1D *h0_betam;
class   TH2D *h0_betamomp;
class   TH2D *h0_betamomm;
class   TH2D *h0_yxp;
class   TH2D *h0_yxm;

class   TH1D *h1_multHist;

class   TH1D *h1_massp;
class   TH1D *h1_massm;
class   TH1D *h1_momp;
class   TH1D *h1_momm;
class   TH1D *h1_zProton;
class   TH1D *h1_zPip;
class   TH1D *h1_betap;
class   TH1D *h1_betam;
class   TH2D *h1_betamomp;
class   TH2D *h1_betamomm;
class   TH2D *h1_yxp;
class   TH2D *h1_yxm;

class   TH1F *h1_elossp;
class   TH2F *h1_elossp_mom;
class   TH1F *h1_elosspip;
class   TH2F *h1_elosspip_mom;
class   TH1F *h1_elosspim;
class   TH2F *h1_elosspim_mom;

class 	TH1D *h2_allPhotonTimeDiff;
class 	TH1D *h2_bestPhotonTimeDiff;
class 	TH1D *h2_photonEnergy;
class 	TH1D *h2_bestPhotonEnergy;

class 	TH1D *h3_bestPhotonTimeDiff;
class 	TH1D *h3_bestPhotonEnergy;
class 	TH1D *h3_MM_p_pip_pim; // pi0
class 	TH1D *h3_M_pip_pim;    // K0 or rho
class 	TH1D *h3_M_pip_pim_pi0; // omega
class 	TH1D *h3_M_p_pi0;  // Sigma
class 	TH2D *h3_MM_pip_pim_M_pip_pim; // Sigma vs K0

class   TH1D *h4_multHist;

class 	TH2D *h4_betamomp;
class	TH1D *h4_photonEnergy;

TLorentzVector *lPhoton;
TLorentzVector *lTarget;

// detected particles
TLorentzVector *lProtonDet;
TLorentzVector *lPipDet;
TLorentzVector *lPimDet;
// true particles
TLorentzVector *lTrueProton;
TLorentzVector *lTruePip;
TLorentzVector *lTruePim;
TLorentzVector *lTruePi0;

// eloss
TLorentzVector *p_in;  //,*p_out;			// momenta before and after eloss correction
TVector3	vert;			// the vertex


// p pi+ pi- with appropriate Det/MM assigned for topology
TLorentzVector *lProton;
TLorentzVector *lPip;
TLorentzVector *lPim;

TLorentzVector *lMM_p_pip_pim;		// pi0
TLorentzVector *lM_pip_pim;		    // K0 or rho
TLorentzVector *lM_pip_pim_pi0;		// omega
TLorentzVector *lM_p_pi0;		    // Sigma
TLorentzVector *lMM_pip_pim;	    // Sigma


// Polarization

//default values for command line args
Int_t  EgSetting=1300;
Double_t polLeft=0.0; //Ken2 may alread be set like this - not sure
Double_t polRight=0.0; //Ken2
Double_t ELeft=200.0;
Double_t ERight=0.0;
Int_t Column=PSMOOTH;

bool 	isSim = true;

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

Int_t	currentPlane=UNKNOWN;
Int_t   polPlane=0;
Double_t  currentEdge=0.0;
Double_t		polDegree;
Double_t		polDegreeOrig;
Int_t   currentMode=MANUAL;
char *paraPolTable;
char *perpPolTable;

// edge tables
int run;                 //run no, extracted from current file name
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
  
//variables to handle the photon polarization using full pol tables
Double_t 	polTable[2][500][385][10];  //where its [plane][edge][E_id][field]
Int_t 		polTableN[2]={0,0};            //No of entries for para and perp
Char_t 		polFirstLines[2][500][250];   //to keep the 1st lines if needed (info from files)

class TH1F *meanPol[2], *meanPolG[2],*eventsPol[2],*eventsPolG[2];
class TH1F *meanPolOrig[2], *eventsPolOrig[2], *meanPolGOrig[2], *eventsPolGOrig[2], *meanPolPhi[2], *eventsPolPhi[2], *meanPolGPhi[2], *eventsPolGPhi[2];
Double_t gBinsArray[385]; 

//                                                                      *
// **********************************************************************


// ********* required functions defined in this code ******************** 
//                                                                      *
void printUsage();			// print usage when run as exe       
int  parseArgs(int,char **);		// parse args when run as exe
//                                                                      *
// ********* end of required functions defined in this code ************* 

// ********* my functions defined in this code ************************** 
//                                                                      *
void lcg8K0SigAnaToy(int, char *,char *); // main func. (same name as this macro)

// Polarization
int LoadPolTable(int plane, Char_t *PolTableList);
Double_t GetPol(Int_t plane, Double_t edge, Int_t eid, Int_t poltype, Double_t lowThresh, Double_t highThresh);
Double_t GetPol(Int_t plane, Double_t edge, Double_t eg, Int_t poltype, Double_t lowThresh, Double_t highThresh);
int LoadEdgeTable(Char_t *EdgeTable);
Int_t GetEdge(Int_t event, Double_t *edge, Int_t *plane);
Double_t mikeTest(Double_t pol, Double_t egamma, Double_t cohEdge, Int_t Plane, Int_t setting); //Mikes pol correction
Double_t polFix0(Double_t xE, Int_t plane, Int_t parSet); //Mikes pol correction 


//                                                                      *
// ********* end of my functions defined in this code ******************* 


// ---------- FUNCTION DEFINITIONS BEGIN HERE ---------------------

// ---------- Required main() for making an executable -------------
#ifdef ROOTEXE
int main(int argc,char **argv){		
  if((parseArgs(argc,argv))!=0) return(-1);	//parse input args
  lcg8K0SigAnaToy(nEventsTot,InFileName,OutFileName);	//call user function
  return(0);
}
#endif
// ---------- end of required main() for making an executable ------

// ---------- user main function  -----------------------------------------------
// This gets called by main() when running as an executable,
// or interactively from the root> prompt.
// should have the same name as this file (minus the .C suffix)
// customize the "non-required" sections
 
void lcg8K0SigAnaToy(int nEvents, char *file, char *outFileName){   // main user function

  // *****************variables which are required***********************
  //                                                                    *
  int	event=0;             	// Event counter for current file
  int	eventTot=0;	       	// Total event count
  class	TFile *outFile;         // the file to put the results
  char 	inFile[128];	       	// holds the current file name
  int 	fileNo=0;	       	// current file no if sorting though a list
  //                                                                    *
  // ********* end of variables which are required **********************


  // ******************* my variables ***********************************
  //                                                                    *
  int 	sect_no=0;			// hold the number of a bank sector
  char 	name[100];			// hold temp names for hists 
  //                                                                    *
  // ******************* end of my variables ****************************
  
  // THSParticle trees
  Double_t  fgID=0;
  
  // Macro loading moved to RootBeerSetup.cxx
  //TString HSANA=gSystem->Getenv("HSANA");
  //gInterpreter->AddIncludePath(HSANA);
  //gROOT->LoadMacro(HSANA+"/THSParticle.C++");
  
  THSParticle* hsProton=new THSParticle(2212);
  THSParticle* hsPip=new THSParticle(211);
  THSParticle* hsPim=new THSParticle(-211);
  THSParticle* hsBeam=new THSParticle(22);
  THSParticle* hsTrueProton=new THSParticle(2212);
  THSParticle* hsTruePip=new THSParticle(211);
  THSParticle* hsTruePim=new THSParticle(-211);
  THSParticle* hsTruePi0=new THSParticle(111);
 
  Int_t buff=32000;
  Int_t split=0;
  
  // Haspect file and tree
  TFile* hsfile=new TFile("filepPi0.root","recreate");
  TTree* tree=new TTree("HSParticles","output tree",0);
  tree->Branch("fgID",&fgID,"fgID/D");
  tree->Branch("pol",&polDegree,"pol/D");
  tree->Branch("polState",&polPlane,"polState/I");
  tree->Branch("proton",&hsProton,buff,split);
  tree->Branch("pip",&hsPip,buff,split);
  tree->Branch("pim",&hsPim,buff,split);
  tree->Branch("beam",&hsBeam,buff,split);
  tree->Branch("trueProton",&hsTrueProton,buff,split);
  tree->Branch("truePip",&hsTruePip,buff,split);
  tree->Branch("truePim",&hsTruePim,buff,split);
  tree->Branch("truePi0",&hsTruePi0,buff,split);
    
 
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
 
  const  char *mybanks[]={"EVNT","TAGR","SCPB","MCTK","MCVX","null"};	// make a list of the banks you want to use
  //const  char *mybanks[]={"SCR ","TAGR","null"};	// make a list of the banks you want to use
  // ** DONT FORGET TO DEFINE THE BANKS YOU WANT RIGHT HERE
  //
  //Set up my histograms (variables already defined as globals above)
 
  // Some sample hists with raw data
  h0_massp = new TH1D("h0_massp", "Event mass +", 1000, 0.0, 1.2);
  h0_massm = new TH1D("h0_massm", "Event mass -", 1000, 0.0, 1.2);
  h0_massn = new TH1D("h0_massn", "Event mass 0", 1000, 0.0, 1.2);
  
  h0_momp = new TH1D("h0_momp", "Event p +", 1000, 0.0, 4.0);
  h0_momm = new TH1D("h0_momm", "Event p -", 1000, 0.0, 4.0);

  h0_zp = new TH1D("h0_zp", "Event z +", 1000, -100.0, 100.0);
  h0_zm = new TH1D("h0_zm", "Event z -", 1000, -100.0, 100.0);
  
  h0_betap = new TH1D("h0_betap", "Event beta +", 1000, 0.0, 1.5);
  h0_betam = new TH1D("h0_betam", "Event beta -", 1000, 0.0, 1.5);  
  
  h0_betamomp = new TH2D("h0_betamomp", "Event beta vs p +", 500, 0.0, 4.0, 500, 0.0, 1.5);
  h0_betamomp->GetXaxis()->SetTitle("p");
  h0_betamomp->GetYaxis()->SetTitle("beta");
  h0_betamomm = new TH2D("h0_betamomm", "Event beta vs p -", 500, 0.0, 4.0, 500, 0.0, 1.5);
  h0_betamomm->GetXaxis()->SetTitle("p");
  h0_betamomm->GetYaxis()->SetTitle("beta");
  
  h0_yxp = new TH2D("h0_yxp", "Event y vs x +", 500, -100.0, 100.0, 500, -100.0, 100.0);
  h0_yxp->GetXaxis()->SetTitle("x");
  h0_yxp->GetYaxis()->SetTitle("y");
  h0_yxm = new TH2D("h0_yxm", "Event y vs x -", 500, -100.0, 100.0, 500, -100.0, 100.0);
  h0_yxm->GetXaxis()->SetTitle("x");
  h0_yxm->GetYaxis()->SetTitle("y");  
  		     
  // After particle ID
  h1_multHist = new TH1D("h1_multiplicity", "Multiplicity - initial PID", 5, 0, 5);  	
  
  h1_massp = new TH1D("h1_massp", "Event mass +", 1000, 0.0, 1.2);
  h1_massm = new TH1D("h1_massm", "Event mass -", 1000, 0.0, 1.2);

  h1_momp = new TH1D("h1_momp", "Event p +", 1000, 0.0, 4.0);
  h1_momm = new TH1D("h1_momm", "Event p -", 1000, 0.0, 4.0);

  h1_zProton = new TH1D("h1_zProton", "Event z proton", 1000, -100.0, 100.0);
  h1_zPip = new TH1D("h1_zPip", "Event z pi+", 1000, -100.0, 100.0);
  
  h1_betap = new TH1D("h1_betap", "Event beta +", 1000, 0.0, 1.5);
  h1_betam = new TH1D("h1_betam", "Event beta -", 1000, 0.0, 1.5);  
  
  h1_betamomp = new TH2D("h1_betamomp", "Event beta vs p +", 500, 0.0, 4.0, 500, 0.0, 1.5);
  h1_betamomp->GetXaxis()->SetTitle("p");
  h1_betamomp->GetYaxis()->SetTitle("beta");
  h1_betamomm = new TH2D("h1_betamomm", "Event beta vs p -", 500, 0.0, 4.0, 500, 0.0, 1.5);
  h1_betamomm->GetXaxis()->SetTitle("p");
  h1_betamomm->GetYaxis()->SetTitle("beta");
  
  h1_yxp = new TH2D("h1_yxp", "Event y vs x +", 500, -100.0, 100.0, 500, -100.0, 100.0);
  h1_yxp->GetXaxis()->SetTitle("x");
  h1_yxp->GetYaxis()->SetTitle("y");
  h1_yxm = new TH2D("h1_yxm", "Event y vs x -", 500, -100.0, 100.0, 500, -100.0, 100.0);
  h1_yxm->GetXaxis()->SetTitle("x");
  h1_yxm->GetYaxis()->SetTitle("y");  

  h1_elossp = new TH1F("h1_elossp","Proton energy loss in target and start counter",500,0,50); 
  h1_elossp ->GetXaxis()->SetTitle("Energy loss (MeV)");
  h1_elossp_mom = new TH2F("h1_elossp_mom","Proton energy loss in target and start counter",100,0,3,500,0,50);
  h1_elossp_mom->GetXaxis()->SetTitle("Proton momentum (GeV)");
  h1_elossp_mom->GetYaxis()->SetTitle("Energy loss (MeV)");
  
  h1_elosspip = new TH1F("h1_elosspip","pi+ energy loss in target and start counter",500,0,50); 
  h1_elosspip ->GetXaxis()->SetTitle("Energy loss (MeV)");
  h1_elosspip_mom = new TH2F("h1_elosspip_mom","pi+ energy loss in target and start counter",100,0,3,500,0,50);
  h1_elosspip_mom->GetXaxis()->SetTitle("pi+ momentum (GeV)");
  h1_elosspip_mom->GetYaxis()->SetTitle("Energy loss (MeV)");
  
  h1_elosspim = new TH1F("h1_elosspim","pi- energy loss in target and start counter",500,0,50); 
  h1_elosspim ->GetXaxis()->SetTitle("Energy loss (MeV)");
  h1_elosspim_mom = new TH2F("h1_elosspim_mom","pi- energy loss in target and start counter",100,0,3,500,0,50);
  h1_elosspim_mom->GetXaxis()->SetTitle("pi- momentum (GeV)");
  h1_elosspim_mom->GetYaxis()->SetTitle("Energy loss (MeV)");
  
  //initialise eloss targ_X, targ_y, targ_z, st_offset
  //targ_X, targ_y, targ_z, st_offset
  initELoss(0.0,0.0,-20.0,-24.06);
  
  h2_allPhotonTimeDiff = new TH1D("h2_allPhotonTimeDiff", "Proton - photon time diff - all photons", 1000, -50.0, 50.0);  
  h2_bestPhotonTimeDiff = new TH1D("h2_bestPhotonTimeDiff", "Proton - photon time diff - best photons", 1000, -50.0, 50.0);  		     
  
  h2_photonEnergy = new TH1D("h2_photonEnergy", "Photon Energy", 1000, 0.0, 3.0);
  h2_bestPhotonEnergy = new TH1D("h2_bestPhotonEnergy", "Best Photon Energy", 1000, 0.0, 3.0);
  
  h3_bestPhotonTimeDiff = new TH1D("h3_bestPhotonTimeDiff", "Proton - photon time diff - best photons", 1000, -50.0, 50.0);  		     
  h3_bestPhotonEnergy = new TH1D("h3_bestPhotonEnergy", "Best Photon Energy", 1000, 0.0, 3.0);
  
  h3_MM_p_pip_pim = new TH1D("h3_MM_p_pip_pim", "h3_MM_p_pip_pim", 200, -0.3,1.0);
  h3_M_pip_pim = new TH1D("h3_M_pip_pim", "h3_M_pip_pim", 200, 0.0, 1.6);
  h3_M_pip_pim_pi0 = new TH1D("h3_M_pip_pim_pi0", "h3_M_pip_pim_pi0", 200, 0.0, 1.6);
  h3_M_p_pi0 = new TH1D("h3_M_p_pi0", "h3_M_p_pi0", 200, 0.0, 1.6);
  
  h3_MM_pip_pim_M_pip_pim = new TH2D("h3_MM_pip_pim_M_pip_pim", "h3_MM_pip_pim_M_pip_pim", 200, 0.0, 1.2, 200, 0.0, 1.6);
  
  h4_multHist = new TH1D("h4_multiplicity", "Multiplicity - after cuts", 5, 0, 5);  	  
 
  h4_betamomp = new TH2D("h4_betamomp", "Beta vs p +", 500, 0.0, 4.0, 500, 0.0, 1.5);
  h4_betamomp->GetXaxis()->SetTitle("p");
  h4_betamomp->GetYaxis()->SetTitle("beta");

  h4_photonEnergy = new TH1D("h4_photonEnergy", "Photon Energy", 1000, 0.0, 3.0);

  // 4 vectors
  lPhoton = new TLorentzVector(1.0,1.0,1.0,1.0);
  lTarget = new TLorentzVector(1.0,1.0,1.0,1.0);
  lTarget->SetXYZM(0,0,0,PROTON_MASS);

  // detected particles
  lProtonDet = new TLorentzVector(1.0,1.0,1.0,1.0);
  lPipDet = new TLorentzVector(1.0,1.0,1.0,1.0);
  lPimDet = new TLorentzVector(1.0,1.0,1.0,1.0);
  
  // true particles
  lTrueProton = new TLorentzVector(1.0,1.0,1.0,1.0);
  lTruePip = new TLorentzVector(1.0,1.0,1.0,1.0);
  lTruePim = new TLorentzVector(1.0,1.0,1.0,1.0);
  lTruePi0 = new TLorentzVector(1.0,1.0,1.0,1.0);
  
  
  // eloss
  p_in = new TLorentzVector(1.0,1.0,1.0,1.0);

  // p pi+ pi- with appropriate Det/MM assigned for topology
  lProton = new TLorentzVector(1.0,1.0,1.0,1.0);
  lPip = new TLorentzVector(1.0,1.0,1.0,1.0);
  lPim = new TLorentzVector(1.0,1.0,1.0,1.0);
  
  lMM_p_pip_pim = new TLorentzVector(1.0,1.0,1.0,1.0);
  lM_pip_pim = new TLorentzVector(1.0,1.0,1.0,1.0);
  lM_pip_pim_pi0 = new TLorentzVector(1.0,1.0,1.0,1.0);
  lM_p_pi0 = new TLorentzVector(1.0,1.0,1.0,1.0);
  lMM_pip_pim = new TLorentzVector(1.0,1.0,1.0,1.0);  
  
  const float vl = 29.9792458;                     //Speed of light in cm/ns

  // Polarization
  // Settings based on commandline argument (EgSetting) for energy setting...
  //These need to be changed for each coherent peak position
  //Eg low should be coh peak - 0.4
  //Eg High should be coh peak + 0.05
  //	add links to updated polarization tables here...
  switch(EgSetting){
  case 1300:
      //EgLow = 0.9;
      //EgHigh = 1.35;
      //meanPolFileName="/home/clasg8/rootbeer2.1/poltabs/manual_1.3_runs_meanpol.dat";
      paraPolTable="/home/clasg8/rootbeer2.1/poltabs/PolTables_1.3_Manual_PARA.dat";
      perpPolTable="/home/clasg8/rootbeer2.1/poltabs/PolTables_1.3_Manual_PERP.dat";
      
      break;
  case 1500:
      //EgLow = 1.1;
      //EgHigh = 1.55;
      //meanPolFileName="/home/clasg8/rootbeer2.1/poltabs/total_1.5_runs_meanpol.dat";
      paraPolTable="/home/clasg8/rootbeer2.1/poltabs/PolTables_1.5_Manual_PARA.dat";
      perpPolTable="/home/clasg8/rootbeer2.1/poltabs/PolTables_1.5_Manual_PERP.dat";
      break;
  case 1700: //manual
      //EgLow = 1.3;
      //EgHigh = 1.75;
      //meanPolFileName="/home/clasg8/rootbeer2.1/poltabs/total_1.7_runs_meanpol.dat";
      paraPolTable="/home/clasg8/rootbeer2.1/poltabs/PolTables_1.7_Manual_PARA.dat";
      perpPolTable="/home/clasg8/rootbeer2.1/poltabs/PolTables_1.7_Manual_PERP.dat";
      break;
  case 1701: //auto
      //EgLow = 1.3;
      //EgHigh = 1.75;
      //meanPolFileName="/home/clasg8/rootbeer2.1/poltabs/total_1.7_runs_meanpol.dat";
      paraPolTable="/home/clasg8/rootbeer2.1/poltabs/PolTables_1.7_Auto_PARA.dat";
      perpPolTable="/home/clasg8/rootbeer2.1/poltabs/PolTables_1.7_Auto_PERP.dat";
      currentMode=SWAP;
      break;
  case 1900:
      //EgLow = 1.5;
      //EgHigh = 1.95;
      //meanPolFileName="/home/clasg8/rootbeer2.1/poltabs/auto_1.9_runs_meanpol.dat";
      paraPolTable="/home/clasg8/rootbeer2.1/poltabs/PolTables_1.9_Auto_PARA.dat";
      perpPolTable="/home/clasg8/rootbeer2.1/poltabs/PolTables_1.9_Auto_PERP.dat";
      currentMode=SWAP;
      break;
  case 2100:
      //EgLow = 1.7;
      //EgHigh = 2.15;
      //meanPolFileName="/home/clasg8/rootbeer2.1/poltabs/manual_2.1_runs_meanpol.dat";
      paraPolTable="/home/clasg8/rootbeer2.1/poltabs/PolTables_2.1_Manual_PARA.dat";
      perpPolTable="/home/clasg8/rootbeer2.1/poltabs/PolTables_2.1_Manual_PERP.dat";
      break;
  default:
      //EgLow = 0.0;
      //EgHigh = 0.0;
      cerr << "Fatal Error: Unknown value on energy_setting " <<  EgSetting << endl;

      break;
  }  

  // Load the polarization tables
  if((LoadPolTable(PARA,paraPolTable ))!=0) return;
  if((LoadPolTable(PERP,perpPolTable ))!=0) return;

  //hists for working out the mean pol.
  
  //make an array of bin edges for the tagger based on the ecounter centres.
  for(int b=1;b<384;b++){
    gBinsArray[b]=0.0005*(polTable[PARA][0][385-b][ENERGY]+polTable[PARA][0][384-b][ENERGY]); //mean of centred conv to GeV
  }
  gBinsArray[0]=gBinsArray[1]-0.5*(gBinsArray[2]-gBinsArray[1]);
  gBinsArray[384]=gBinsArray[383]+0.5*(gBinsArray[383]-gBinsArray[382]);
  
  meanPol[PARA]=new TH1F("meanPolPARA","meanPolPARA",384,0,384);
  meanPol[PERP]=new TH1F("meanPolPERP","meanPolPERP",384,0,384);
  meanPolOrig[PARA]=new TH1F("meanPolOrigPARA","meanPolOrigPARA",384,0,384);
  meanPolOrig[PERP]=new TH1F("meanPolOrigPERP","meanPolOrigPERP",384,0,384);
  eventsPol[PARA]=new TH1F("eventsPolPARA","eventsPolPARA",384,0,384);
  eventsPol[PERP]=new TH1F("eventsPolPERP","eventsPolPERP",384,0,384);
  eventsPolOrig[PARA]=new TH1F("eventsPolOrigPARA","eventsPolOrigPARA",384,0,384);
  eventsPolOrig[PERP]=new TH1F("eventsPolOrigPERP","eventsPolOrigPERP",384,0,384);
  meanPolG[PARA]=new TH1F("meanPolGPARA","meanPolGPARA",384,gBinsArray);
  meanPolG[PERP]=new TH1F("meanPolGPERP","meanPolGPERP",384,gBinsArray);
  meanPolGOrig[PARA]=new TH1F("meanPolGOrigPARA","meanPolGOrigPARA",384,gBinsArray);
  meanPolGOrig[PERP]=new TH1F("meanPolGOrigPERP","meanPolGOrigPERP",384,gBinsArray);
  eventsPolG[PARA]=new TH1F("eventsPolGPARA","eventsPolGPARA",384,gBinsArray);
  eventsPolG[PERP]=new TH1F("eventsPolGPERP","eventsPolGPERP",384,gBinsArray);
  eventsPolGOrig[PARA]=new TH1F("eventsPolGOrigPARA","eventsPolGOrigPARA",384,gBinsArray);
  eventsPolGOrig[PERP]=new TH1F("eventsPolGOrigPERP","eventsPolGOrigPERP",384,gBinsArray);
  meanPol[PARA]->SetStats(kFALSE);
  meanPol[PARA]->GetXaxis()->SetTitle("E_ID");
  meanPolOrig[PARA]->SetStats(kFALSE);
  meanPolOrig[PARA]->GetXaxis()->SetTitle("E_ID");
  meanPolG[PARA]->SetStats(kFALSE);
  meanPolG[PARA]->GetXaxis()->SetTitle("E_{#gamma} (GeV)");
  meanPolGOrig[PARA]->SetStats(kFALSE);
  meanPolGOrig[PARA]->GetXaxis()->SetTitle("E_{#gamma} (GeV)");

  meanPolPhi[PARA]=new TH1F("meanPolPhiPARA","meanPolPhiPARA",384,0,384);
  meanPolPhi[PERP]=new TH1F("meanPolPhiPERP","meanPolPhiPERP",384,0,384);
  eventsPolPhi[PARA]=new TH1F("eventsPolPhiPARA","eventsPolPhiPARA",384,0,384);
  eventsPolPhi[PERP]=new TH1F("eventsPolPhiPERP","eventsPolPhiPERP",384,0,384);
  meanPolGPhi[PARA]=new TH1F("meanPolGPhiPARA","meanPolGPhiPARA",384,gBinsArray);
  meanPolGPhi[PERP]=new TH1F("meanPolGPhiPERP","meanPolGPhiPERP",384,gBinsArray);
  eventsPolGPhi[PARA]=new TH1F("eventsPolGPhiPARA","eventsPolGPhiPARA",384,gBinsArray);
  eventsPolGPhi[PERP]=new TH1F("eventsPolGPhiPERP","eventsPolGPhiPERP",384,gBinsArray);

		     
  //                                                                    *
  // ******* End of User initialisation  ********************************


  // ********************** main file loop **********************************************************
  //                                                                                                *
  while((fileNo=getNextFile(inFile,file))!=-1){  // loop while files are still avialable 

    // Start of user stuff to do before sorting each file  ---------------
    fprintf(stderr,"Sorting file - %s\n",inFile);
    
    // get the table of coherent edges and polarization planes per event number range for this run
    if (!(isSim)) {
		sscanf(strstr(inFile,"flist_0")+7,"%d",&run);
		sprintf(edgeTable,"/home/clasg8/rootbeer2.1/dat/pol/run_%d_pol_edges.dat",run);
		LoadEdgeTable(edgeTable);
	}
    
    // End of user stuff to do before sorting each file  ---------------

    if((rootbeer=createBeerObject(inFile))==NULL) return; 	// create rootbeer object
    rootbeer->SetBankStatus(mybanks,ON);			// switch on the banks required
    rootbeer->StartServer();                  			// start the server running
    rootbeer->ListServedBanks();			       	// list the banks which will be served

    event=0;		//zero the event counter for the file

    // ********************** main event loop ******************************************************
    //                                                                                             *

    while(event>=0){                                           	// do all events
      event = rootbeer->GetEvent();                            	// get next event
	  
	  
      // Start of user customized section ----------------------------
	  // CUT 1
	  if (EVNT_NH != 3 && EVNT_NH != 4) continue;

	  // Count the number of particles of each type
	  // Need 1 proton, 1 Pi+, 1 Pi-, optional neutral
	  int numProton = 0;
	  int numPip = 0;
	  int numPim = 0;
	  int numNeutral = 0;
	  int rowProton = -1;
	  int rowPip = -1;
	  int rowPim = -1;	  
	  
      for(int row=0;row<EVNT_NH;row++){ 		      	// loop over rows in EVNT bank
		
		// initial hists with raw data
		if((EVNT[row].Charge == 1) && (EVNT[row].Mass > 0.0)){
			
			h0_massp->Fill(EVNT[row].Mass);       
			h0_momp->Fill(EVNT[row].Pmom);         
			h0_zp->Fill(EVNT[row].Z);         
			h0_betap->Fill(EVNT[row].Beta); 
			h0_betamomp->Fill(EVNT[row].Pmom, EVNT[row].Beta);
			h0_yxp->Fill(EVNT[row].X, EVNT[row].Y);
		}
		if((EVNT[row].Charge == -1) && (EVNT[row].Mass > 0.0)){
			
			h0_massm->Fill(EVNT[row].Mass);       
			h0_momm->Fill(EVNT[row].Pmom);         
			h0_zm->Fill(EVNT[row].Z);         
			h0_betam->Fill(EVNT[row].Beta); 
			h0_betamomm->Fill(EVNT[row].Pmom, EVNT[row].Beta);
			h0_yxm->Fill(EVNT[row].X, EVNT[row].Y);         
		}      
		if(EVNT[row].Charge == 0){
			
			h0_massn->Fill(EVNT[row].Mass);     
		}
		
		// CUT 2
		// remove anything outside the z of the target
		if ((EVNT[row].Z < -40.0) || (EVNT[row].Z >0.0)) continue;
		
		// Proton
		if ((EVNT[row].Charge == 1) && 
		    (EVNT[row].Mass > 0.49) && (EVNT[row].Mass < 1.44)) {
		
			numProton++;
			rowProton = row;
		}		
		
		// Pi+
		if ((EVNT[row].Charge == 1) && 
		    (EVNT[row].Mass < 0.09)) {
		
			numPip++;
			rowPip = row;
		}

		// Pi-
		if ((EVNT[row].Charge == -1) && 
		    (EVNT[row].Mass < 0.09)) {
		
			numPim++;
			rowPim = row;
		}
		
		// Neutral
		if (EVNT[row].Charge == 0) {
		
			numNeutral++;
		}		
		
		
	  } // end of single event loop

	  // CUT 3
	  // Check if correct particles in event

	  bool includePID = false;
	  if (EVNT_NH == 3 && numProton == 1 && numPip ==1 && numPim == 1) {
	     includePID = true;
      }
	  if (EVNT_NH == 4 && numProton == 1 && numPip ==1 && numPim == 1 && numNeutral == 1) {
	     includePID = true;
      }
 	  if (!(includePID)) continue;

	  h1_multHist->Fill(EVNT_NH);	  
	  
	  // Create the same histograms as before, but with just these events

	  if (numProton != 0) {
		  h1_massp->Fill(EVNT[rowProton].Mass);       
		  h1_momp->Fill(EVNT[rowProton].Pmom);         
		  h1_zProton->Fill(EVNT[rowProton].Z);         
		  h1_betap->Fill(EVNT[rowProton].Beta); 
		  h1_betamomp->Fill(EVNT[rowProton].Pmom, EVNT[rowProton].Beta);
		  h1_yxp->Fill(EVNT[rowProton].X, EVNT[rowProton].Y);
	  }
	  if (numPip != 0) {
		  h1_massp->Fill(EVNT[rowPip].Mass);       
		  h1_momp->Fill(EVNT[rowPip].Pmom);         
		  h1_zPip->Fill(EVNT[rowPip].Z);         
		  h1_betap->Fill(EVNT[rowPip].Beta); 
		  h1_betamomp->Fill(EVNT[rowPip].Pmom, EVNT[rowPip].Beta);
		  h1_yxp->Fill(EVNT[rowPip].X, EVNT[rowPip].Y);
	  }
	  
	  if (numPim != 0) {
		  h1_massm->Fill(EVNT[rowPim].Mass);       
		  h1_momm->Fill(EVNT[rowPim].Pmom);    
		  h1_betam->Fill(EVNT[rowPim].Beta); 
		  h1_betamomm->Fill(EVNT[rowPim].Pmom, EVNT[rowPim].Beta);
		  h1_yxm->Fill(EVNT[rowPim].X, EVNT[rowPim].Y);
	  }
	  
      // Create 4-vectors for each of the detected particles
      // Since we've now ID'd these particles, give them an exact mass
      // We trust the momentum from the EVNT but we don't trust the mass

	  if (numProton != 0) {

		  lProtonDet->SetXYZM(EVNT[rowProton].Cx*EVNT[rowProton].Pmom,EVNT[rowProton].Cy*EVNT[rowProton].Pmom,EVNT[rowProton].Cz*EVNT[rowProton].Pmom,PROTON_MASS);
		  
		  // apply eloss to proton
		  // make 3vector for vertex
		  vert.SetXYZ(EVNT[rowProton].X,EVNT[rowProton].Y,EVNT[rowProton].Z);
		  // call eloss
		  p_in=eLoss(lProtonDet,PROTON_MASS,vert,ELOSS_TARG_LH2,ELOSS_CELL_g8b);
		  // histogram the eloss in MeV
		  h1_elossp->Fill(1000.0*(p_in->P()-lProtonDet->P()));
		  h1_elossp_mom->Fill(lProtonDet->P(),1000.0*(p_in->P()-lProtonDet->P()));
		  //Reset 4-Vector to eloss values
		  lProtonDet->SetXYZM(p_in->X(),p_in->Y(),p_in->Z(),p_in->M());
		  
	  }
		  
	  if (numPip != 0) {
		  
		  lPipDet->SetXYZM(EVNT[rowPip].Cx*EVNT[rowPip].Pmom,EVNT[rowPip].Cy*EVNT[rowPip].Pmom,EVNT[rowPip].Cz*EVNT[rowPip].Pmom,PI_CHARGED_MASS);

		  // apply eloss to Pi+
		  // make 3vector for vertex
		  vert.SetXYZ(EVNT[rowPip].X,EVNT[rowPip].Y,EVNT[rowPip].Z);
		  // call eloss
		  p_in=eLoss(lPipDet,PI_CHARGED_MASS,vert,ELOSS_TARG_LH2,ELOSS_CELL_g8b);
		  // histogram the eloss in MeV
		  h1_elosspip->Fill(1000.0*(p_in->P()-lPipDet->P()));
		  h1_elosspip_mom->Fill(lPipDet->P(),1000.0*(p_in->P()-lPipDet->P()));
		  //Reset 4-Vector to eloss values
		  lPipDet->SetXYZM(p_in->X(),p_in->Y(),p_in->Z(),p_in->M());
		  
	  }
	  
	  if (numPim != 0) {
		  
		  lPimDet->SetXYZM(EVNT[rowPim].Cx*EVNT[rowPim].Pmom,EVNT[rowPim].Cy*EVNT[rowPim].Pmom,EVNT[rowPim].Cz*EVNT[rowPim].Pmom,PI_CHARGED_MASS);
		  
		  // apply eloss to Pi-
		  // make 3vector for vertex
		  vert.SetXYZ(EVNT[rowPim].X,EVNT[rowPim].Y,EVNT[rowPim].Z);
		  // call eloss
		  p_in=eLoss(lPimDet,PI_CHARGED_MASS,vert,ELOSS_TARG_LH2,ELOSS_CELL_g8b);
		  // histogram the eloss in MeV
		  h1_elosspim->Fill(1000.0*(p_in->P()-lPimDet->P()));
		  h1_elosspim_mom->Fill(lPimDet->P(),1000.0*(p_in->P()-lPimDet->P()));
		  //Reset 4-Vector to eloss values
		  lPimDet->SetXYZM(p_in->X(),p_in->Y(),p_in->Z(),p_in->M());		  
		  
	  }

	  // Get properties of the particle to be used for photon selection
	  // use proton
	  // Calculate the beta
	  float betaTimingParticle = 0.0;
	  int rowTimingParticle = -1;
	  betaTimingParticle=(lProtonDet->Rho())/sqrt((lProtonDet->Rho()*lProtonDet->Rho())+(PROTON_MASS*PROTON_MASS));
	  rowTimingParticle = rowProton;
      // Why not take from 4-vector?
	  //betaProton = lProton->Beta();

  	  // Find the best photon based on the proton timing
	  int bestPhotonRow = -1;
	  float bestTimeDiff = 1000.0;
	  float timeDiff = 0.0;
		  
	  for (int row=0; row<TAGR_NH; row++) {
			
		if((TAGR[row].STAT!=15)&&(TAGR[row].STAT!=7)) continue; //check good photon 

			//Calculate the time difference
			            // time on start counter         -  time to travel from vertex position in target = vertex time for proton
			timeDiff=(((SCPB[EVNT[rowTimingParticle].SCstat-1].Time)-((SCPB[EVNT[rowTimingParticle].SCstat-1].Path)/(vl*betaTimingParticle)))
					  -((TAGR[row].TPHO)+((EVNT[rowTimingParticle].Z)/vl))-0.667);
                        // photon time from tagger   + time to travel to z position in target - offset since target centred at -20cm = vertex for photon
			            //                                                                      0.667 = 20cm / vl
			h2_allPhotonTimeDiff->Fill(timeDiff);
			h2_photonEnergy->Fill(TAGR[row].ERG);

			// Check if this is the minimum time difference so far
			if (fabs(timeDiff) < fabs(bestTimeDiff)) {
			
				bestPhotonRow = row;
				bestTimeDiff = timeDiff;
			}
			
	  }
	
	  // Plot the time difference for the best photons
	  h2_bestPhotonTimeDiff->Fill(bestTimeDiff);	
	  h2_bestPhotonEnergy->Fill(TAGR[bestPhotonRow].ERG);
	  
	  // CUT 4
	  // drop anything with time difference > 1 i.e. best photon is best of a bad lot
	  if (fabs(bestTimeDiff)>1.0) continue; 

	  // Plot the time difference after the cut
	  h3_bestPhotonTimeDiff->Fill(bestTimeDiff);	
	  h3_bestPhotonEnergy->Fill(TAGR[bestPhotonRow].ERG);
	  
	  // get the polarization
	  
	  //if(currentRadiator!=AMORPHOUS){ // do I need to check radiator?
		GetEdge(HEAD[0].NEVENT,&currentEdge,&currentPlane); //get the current edge position
      //}

	  //Extract the photon polarization information
      //Nothing in the photon pol stops the event going into the tree for likelihood, or other analysis.
      //However, if the photon pol does not meet the following criteria it is flagged as 99.9.
      //To fill histograms like phi distribs, where they will be fitted later, and mean polarizations used, 
    
      if (!(isSim)) {
		  if(((currentPlane==PARA)||(currentPlane==PERP))&&
			((currentEdge>0.0)&&(1000.0*TAGR[bestPhotonRow].ERG >currentEdge-ELeft)&&(1000.0*TAGR[bestPhotonRow].ERG<currentEdge+ERight))){       
			//	polDegree=GetPol(currentPlane,currentEdge,(int)((TAGR[bestPhoton].E_id+0.5)/2.0),PSMOOTH,0.2,0.3);
			polDegree=GetPol(currentPlane,currentEdge,(int)((TAGR[bestPhotonRow].E_id+1.0)/2.0),Column,polLeft,polRight);
			polDegreeOrig=GetPol(currentPlane,currentEdge,(int)((TAGR[bestPhotonRow].E_id+1.0)/2.0),Column,polLeft,polRight);      
		  
			//Now use Mikes correction (but not for 2.1)
			if (EgSetting!=2100) {
				polDegree=mikeTest(polDegree,1000.0*TAGR[bestPhotonRow].ERG,currentEdge,currentPlane,EgSetting);  //Ken2
			}
		  
			//cout << "Event:" << HEAD[0].NEVENT << "  Edge:" << currentEdge <<  " E_ID:" << (int)((TAGR[bestPhotonRow].E_id+0.5)/2.0) 
			//     << " Eg:" << TAGR[bestPhotonRow].ERG << " Pol:" << polDegree << endl;
			if((polDegree>0.0) && (polDegree<1.0)){
				meanPol[currentPlane]->Fill((int)((TAGR[bestPhotonRow].E_id+1.0)/2.0),polDegree);
				eventsPol[currentPlane]->Fill((int)((TAGR[bestPhotonRow].E_id+1.0)/2.0));
				meanPolG[currentPlane]->Fill(TAGR[bestPhotonRow].ERG,polDegree); 
				eventsPolG[currentPlane]->Fill(TAGR[bestPhotonRow].ERG);
			}
			
			if((polDegreeOrig>0.0) && (polDegreeOrig<1.0)){
				meanPolOrig[currentPlane]->Fill((int)((TAGR[bestPhotonRow].E_id+1.0)/2.0),polDegreeOrig);
				eventsPolOrig[currentPlane]->Fill((int)((TAGR[bestPhotonRow].E_id+1.0)/2.0));
				meanPolGOrig[currentPlane]->Fill(TAGR[bestPhotonRow].ERG,polDegreeOrig); 
				eventsPolGOrig[currentPlane]->Fill(TAGR[bestPhotonRow].ERG);
			}
			
		  }
		  else {
			continue;
			//polDegree=99.9;
		  }
		  
		  if (currentPlane==PARA) {
			  polPlane = 1;
		  }
		  else if (currentPlane==PERP) {
			  polPlane = -1;
		  }
	  }
	  
	  // Now assign the 4 vectors to use depending on the channel
	  lPhoton->SetPxPyPzE(0,0,TAGR[bestPhotonRow].ERG,TAGR[bestPhotonRow].ERG);
	  *lProton = *lProtonDet;
	  *lPip = *lPipDet;
	  *lPim = *lPimDet;
	  
	  *lMM_p_pip_pim = (*lTarget + *lPhoton) - (*lProton + *lPip + *lPim);
	  *lM_pip_pim = *lPip + *lPim;
	  *lM_pip_pim_pi0 = *lPip + *lPim + *lMM_p_pip_pim;
	  *lM_p_pi0 = *lProton + *lMM_p_pip_pim;
	  *lMM_pip_pim = (*lTarget + *lPhoton) - (*lPip + *lPim);

	  h3_MM_p_pip_pim->Fill(lMM_p_pip_pim->M());
	  h3_M_pip_pim->Fill(lM_pip_pim->M());
	  h3_M_pip_pim_pi0->Fill(lM_pip_pim_pi0->M());
	  h3_M_p_pi0->Fill(lM_p_pi0->M());
	  
	  h3_MM_pip_pim_M_pip_pim->Fill(lMM_pip_pim->M(),lM_pip_pim->M());
		  	      
	  // Fill HSParticles
	  // Detected particles
	  hsProton->SetP4(*lProton);
	  hsPip->SetP4(*lPip);
	  hsPim->SetP4(*lPim);
	  hsBeam->SetP4(*lPhoton);
	  // True particles
	  for (int i=0; i<4 ;i++) {
	      if (MCTK[i].id == 2212) {
		      lTrueProton->SetXYZM(MCTK[i].cx*MCTK[i].pmom,MCTK[i].cy*MCTK[i].pmom,MCTK[i].cz*MCTK[i].pmom,PROTON_MASS);
	      }
	      if (MCTK[i].id == 211) {
		      lTruePip->SetXYZM(MCTK[i].cx*MCTK[i].pmom,MCTK[i].cy*MCTK[i].pmom,MCTK[i].cz*MCTK[i].pmom,PROTON_MASS);
	      }
	      if (MCTK[i].id == -211) {
		      lTruePim->SetXYZM(MCTK[i].cx*MCTK[i].pmom,MCTK[i].cy*MCTK[i].pmom,MCTK[i].cz*MCTK[i].pmom,PROTON_MASS);
	      }
	      if (MCTK[i].id == 111) {
		      lTruePi0->SetXYZM(MCTK[i].cx*MCTK[i].pmom,MCTK[i].cy*MCTK[i].pmom,MCTK[i].cz*MCTK[i].pmom,PROTON_MASS);
	      }
	  }
	  hsTrueProton->SetP4(*lTrueProton);
	  hsTruePip->SetP4(*lTruePip);
	  hsTruePim->SetP4(*lTruePim);
	  hsTruePi0->SetP4(*lTruePi0);
	  tree->Fill();
		
      if((polDegree>0.0) && (polDegree<1.0)){
        meanPolPhi[currentPlane]->Fill((int)((TAGR[bestPhotonRow].E_id+1.0)/2.0),polDegree);
        eventsPolPhi[currentPlane]->Fill((int)((TAGR[bestPhotonRow].E_id+1.0)/2.0));
        meanPolGPhi[currentPlane]->Fill(TAGR[bestPhotonRow].ERG,polDegree); 
        eventsPolGPhi[currentPlane]->Fill(TAGR[bestPhotonRow].ERG);
      }
	  
	  h4_multHist->Fill(EVNT_NH);
	  
	  // Replot beta vs p for proton and K+
   	  h4_betamomp->Fill(EVNT[rowProton].Pmom, EVNT[rowProton].Beta);
 	  h4_betamomp->Fill(EVNT[rowPip].Pmom, EVNT[rowPip].Beta);

 	  
 	  // Check photon energy now
 	  // Should only be photons > 1.05 GeV
 	  h4_photonEnergy->Fill(TAGR[bestPhotonRow].ERG);


      //eg of handling of multiple sector bank SCR
//      for(int sector=0; sector<SCR_NS;sector++){              	// for all sectors
//	sect_no=SCR_S[sector];                                 	// get the number of the sector 
//	for(int row=0;row<SCR_NH[sector];row++){            	// for all hits in that sector
//	  scr_hist[sect_no]->Fill(SCR[sector][row].id);       	// fill  hist
//	} 
 //     }   
      /**********************************************************************
       *  End of user customized section ----------------------------
	  */
      eventTot++;
      fgID++;
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
  
  //Divide the polarization totals by the no of events to get the mean
  meanPol[PARA]->Divide(eventsPol[PARA]);
  meanPol[PERP]->Divide(eventsPol[PERP]);
  meanPolG[PARA]->Divide(eventsPolG[PARA]);
  meanPolG[PERP]->Divide(eventsPolG[PERP]);
  meanPolOrig[PARA]->Divide(eventsPolOrig[PARA]);
  meanPolOrig[PERP]->Divide(eventsPolOrig[PERP]);
  meanPolGOrig[PARA]->Divide(eventsPolGOrig[PARA]);
  meanPolGOrig[PERP]->Divide(eventsPolGOrig[PERP]);
  meanPolPhi[PARA]->Divide(eventsPolPhi[PARA]);
  meanPolPhi[PERP]->Divide(eventsPolPhi[PERP]);
  meanPolGPhi[PARA]->Divide(eventsPolGPhi[PARA]);
  meanPolGPhi[PERP]->Divide(eventsPolGPhi[PERP]);

  
  // write out the trees for sWeights
  hsfile->cd();
  tree->Write();
  hsfile->Close();
  delete hsfile;
  
  
// Write out the plots
TCanvas *c1=new TCanvas("c1","c1",800,600);

h0_massp->Draw();
c1->SaveAs("h0_massp.gif");
c1->Clear();

h0_massm->Draw();
c1->SaveAs("h0_massm.gif");
c1->Clear();

h0_massn->Draw();
c1->SaveAs("h0_massn.gif");
c1->Clear();

h0_momp->Draw();
c1->SaveAs("h0_momp.gif");
c1->Clear();

h0_momm->Draw();
c1->SaveAs("h0_momm.gif");
c1->Clear();

h0_zp->Draw();
c1->SaveAs("h0_zp.gif");
c1->Clear();

h0_zm->Draw();
c1->SaveAs("h0_zm.gif");
c1->Clear();

h0_betap->Draw();
c1->SaveAs("h0_betap.gif");
c1->Clear();

h0_betam->Draw();
c1->SaveAs("h0_betam.gif");
c1->Clear();

gStyle->SetPalette(1);
h0_betamomp->Draw("COLZ");
c1->SaveAs("h0_betamomp.gif");
c1->Clear();

gStyle->SetPalette(53);
h0_betamomp->Draw("COLZ");
c1->SaveAs("h0_betamomp2.gif");
c1->Clear();

gStyle->SetPalette(1);
h0_betamomm->Draw("COLZ");
c1->SaveAs("h0_betamomm.gif");
c1->Clear();

gStyle->SetPalette(53);
h0_betamomm->Draw("COLZ");
c1->SaveAs("h0_betamomm2.gif");
c1->Clear();

h0_yxp->Draw();
c1->SaveAs("h0_yxp.gif");
c1->Clear();

h0_yxm->Draw();
c1->SaveAs("h0_yxm.gif");
c1->Clear();

h1_multHist->Draw();
c1->SaveAs("h1_multHist.gif");
c1->Clear();

h1_massp->Draw();
c1->SaveAs("h1_massp.gif");
c1->Clear();

h1_massm->Draw();
c1->SaveAs("h1_massm.gif");
c1->Clear();

h1_momp->Draw();
c1->SaveAs("h1_momp.gif");
c1->Clear();

h1_momm->Draw();
c1->SaveAs("h1_momm.gif");
c1->Clear();

h1_zProton->Draw();
c1->SaveAs("h1_zProton.gif");
c1->Clear();

c1->SaveAs("h1_zPip.gif");
h1_zPip->Draw();
c1->Clear();

h1_betap->Draw();
c1->SaveAs("h1_betap.gif");
c1->Clear();

h1_betam->Draw();
c1->SaveAs("h1_betam.gif");
c1->Clear();

gStyle->SetPalette(1);
h1_betamomp->Draw("COLZ");
c1->SaveAs("h1_betamomp.gif");
c1->Clear();

gStyle->SetPalette(1);
h1_betamomm->Draw("COLZ");
c1->SaveAs("h1_betamomm.gif");
c1->Clear();

h1_yxp->Draw();
c1->SaveAs("h1_yxp.gif");
c1->Clear();

h1_yxm->Draw();
c1->SaveAs("h1_yxm.gif");
c1->Clear();

h1_elossp->Draw();
c1->SaveAs("h1_elossp.gif");
c1->Clear();

gStyle->SetPalette(1);
h1_elossp_mom->Draw("COLZ");
c1->SaveAs("h1_elossp_mom.gif");
c1->Clear();

h1_elosspip->Draw();
c1->SaveAs("h1_elosspip.gif");
c1->Clear();

gStyle->SetPalette(1);
h1_elosspip_mom->Draw("COLZ");
c1->SaveAs("h1_elosspip_mom.gif");
c1->Clear();

h1_elosspim->Draw();
c1->SaveAs("h1_elosspim.gif");
c1->Clear();

gStyle->SetPalette(1);
h1_elosspim_mom->Draw("COLZ");
c1->SaveAs("h1_elosspim_mom.gif");
c1->Clear();

h2_allPhotonTimeDiff->Draw();
c1->SaveAs("h2_allPhotonTimeDiff.gif");
c1->Clear();

h2_bestPhotonTimeDiff->Draw();
c1->SaveAs("h2_bestPhotonTimeDiff.gif");
c1->Clear();

h2_photonEnergy->Draw();
c1->SaveAs("h2_photonEnergy.gif");
c1->Clear();

h2_bestPhotonEnergy->Draw();
c1->SaveAs("h2_bestPhotonEnergy.gif");
c1->Clear();

h3_bestPhotonTimeDiff->Draw();
c1->SaveAs("h3_bestPhotonTimeDiff.gif");
c1->Clear();

h3_bestPhotonEnergy->Draw();
c1->SaveAs("h3_bestPhotonEnergy.gif");
c1->Clear();

h3_MM_p_pip_pim->Draw();
c1->SaveAs("h3_MM_p_pip_pim.gif");
c1->Clear();

h3_M_pip_pim->Draw();
c1->SaveAs("h3_M_pip_pim.gif");
c1->Clear();

h3_M_pip_pim_pi0->Draw();
c1->SaveAs("h3_M_pip_pim_pi0.gif");
c1->Clear();

h3_M_p_pi0->Draw();
c1->SaveAs("h3_M_p_pi0.gif");
c1->Clear();

gStyle->SetPalette(1);
h3_MM_pip_pim_M_pip_pim->Draw("COLZ");
c1->SaveAs("h3_MM_pip_pim_M_pip_pim.gif");
c1->Clear();

h4_multHist->Draw();
c1->SaveAs("h4_multHist.gif");
c1->Clear();

gStyle->SetPalette(1);
h4_betamomp->Draw("COLZ");
c1->SaveAs("h4_betamomp.gif");
c1->Clear();

gStyle->SetOptStat(0);
gStyle->SetPalette(1);

h4_photonEnergy->Draw();
c1->SaveAs("h4_photonEnergy.gif");
c1->Clear();

meanPolG[PARA]->Draw();
c1->SaveAs("meanPolGPara.gif");
c1->Clear();

meanPolG[PERP]->Draw();
c1->SaveAs("meanPolGPerp.gif");
c1->Clear();

meanPolGOrig[PARA]->Draw();
c1->SaveAs("meanPolGOrigPara.gif");
c1->Clear();

meanPolGOrig[PERP]->Draw();
c1->SaveAs("meanPolGOrigPerp.gif");
c1->Clear();

meanPolGPhi[PARA]->Draw();
c1->SaveAs("meanPolGPhiPara.gif");
c1->Clear();

meanPolGPhi[PERP]->Draw();
c1->SaveAs("meanPolGPhiPerp.gif");
c1->Clear();
  
  
  // Start of user stuff to do at the end  ------------------------
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



// ---------- required parseArgs() function  -------------------------------------------
// parses the input args when running as an executable
// set up the no of events, and input and output file names in global variables
// or prints usage
int parseArgs(int argc,char **argv){
  switch(argc){
  case(1):				// 1 or 2 args not enough
  case(2):
    printUsage();
    return(-1);
    break;
  case(3):				// 3 args rbtest <infile> <outfile>
    if((strstr(argv[1],"-N"))!=NULL){
      printUsage();
      return(-1);
    }
    else{
      strcpy(InFileName,argv[1]);
      strcpy(OutFileName,argv[2]);
    }
    break;
  case(4):				// 4 args must be "rbtest -N# <infile> <outfile>" 
    if(strncmp(argv[1],"-N",2)!=0){  	//print usage then exit */
      printUsage();
      return(-1);
    }
    else{
      sscanf(argv[1]+2,"%d",&nEventsTot);	//get the required event no
      strcpy(InFileName,argv[2]);
      strcpy(OutFileName,argv[3]);
    }      
    break;
  default:
    printUsage();
    return(-1);
    break;
  }
  return(0);
}
// ---------- end of required parseArgs() function  -------------------------------------

// ---------- required printUsage() function  -------------------------------------------
// When running as executable, gets called if no args, or silly args
void printUsage(){
  fprintf(stderr,"\nusage:\n\n");
  fprintf(stderr,"lcg8K0SigAnaToy -h   Print this message\n\n");
  fprintf(stderr,"lcg8K0SigAnaToy [-Nevents] <infile> <outfile.root> \n");
  fprintf(stderr,"lcg8K0SigAnaToy [-Nevents] <-Lfilelist> <outfile.root> \n");
}
// ---------- end of required printUsage() function  -------------------------------------------




// Polarization

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
