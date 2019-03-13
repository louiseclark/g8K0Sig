/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/ 

// Your description goes here... 

#include "Riostream.h" 

#include "LinPolPDF.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 

ClassImp(LinPolPDF) 

 LinPolPDF::LinPolPDF(const char *name, const char *title, 
		  RooAbsReal& _phiK0,
	      RooAbsReal& _cosX,
	      RooAbsReal& _cosY,
	      RooAbsReal& _cosZ,
	      RooAbsReal& _pol,
	      RooAbsCategory& _polState,
	      RooAbsReal& _B,
	      RooAbsReal& _T,
	      RooAbsReal& _Ox,
	      RooAbsReal& _Oz,
	      RooAbsReal& _R) :
   RooHSEventsPDF(name,title),
   phiK0("phiK0","phiK0",this,_phiK0),
   cosX("cosX","cosX",this,_cosX),
   cosY("cosY","cosY",this,_cosY),
   cosZ("cosZ","cosZ",this,_cosZ),
   pol("pol","pol",this,_pol),
   polState("polState","polState",this,_polState),
   B("B","B",this,_B),
   T("T","T",this,_T),
   Ox("Ox","Ox",this,_Ox),
   Oz("Oz","Oz",this,_Oz),
   R("R","R",this,_R)
 { 
   MakeSets();
   phiK0.SetName(_phiK0.GetName());
   pol.SetName(_pol.GetName());
   polState.SetName(_polState.GetName());
   B.SetName(B.GetName());
   T.SetName(T.GetName());
   Ox.SetName(Ox.GetName());
   Oz.SetName(Oz.GetName());
   R.SetName(R.GetName());
 } 


 LinPolPDF::LinPolPDF(const LinPolPDF& other, const char* name) :  
   RooHSEventsPDF(other,name),
   phiK0("phiK0",this,other.phiK0),
   cosX("cosX",this,other.cosX),
   cosY("cosY",this,other.cosY),
   cosZ("cosZ",this,other.cosZ),
   pol("pol",this,other.pol),
   polState("polState",this,other.polState),
   B("B",this,other.B),
   T("T",this,other.T),
   Ox("Ox",this,other.Ox),
   Oz("Oz",this,other.Oz),
   R("R",this,other.R)
 { 
   MakeSets();
   phiK0.SetName(other.phiK0.GetName());
   cosX.SetName(other.cosX.GetName());
   cosY.SetName(other.cosY.GetName());
   cosZ.SetName(other.cosZ.GetName());
   pol.SetName(other.pol.GetName());
   polState.SetName(other.polState.GetName());
   B.SetName(other.B.GetName());
   T.SetName(other.T.GetName());
   Ox.SetName(other.Ox.GetName());
   Oz.SetName(other.Oz.GetName());
   R.SetName(other.R.GetName());
   if(fEvTree) SetEvTree(fEvTree,fCut);//Needs fProxSet filled first
 } 
void LinPolPDF::MakeSets(){
   fProxSet.push_back(&phiK0);
   fProxSet.push_back(&cosX);
   fProxSet.push_back(&cosY);
   fProxSet.push_back(&cosZ);
   fProxSet.push_back(&pol);
   fCatSet.push_back(&polState);
   fParSet.push_back(&B);
   fParSet.push_back(&T);
   fParSet.push_back(&Ox);
   fParSet.push_back(&Oz);
   fParSet.push_back(&R);
   InitSets();
}



 Double_t LinPolPDF::evaluate() const 
 { 
   // ENTER EXPRESSION IN TERMS OF VARIABLE ARGUMENTS HERE 
   Double_t alpha=-0.980; 
   Double_t g=(B+alpha*cosY*T)*TMath::Cos(2*(phiK0))+alpha*(cosX*Ox+cosZ*Oz)*TMath::Sin(2*(phiK0));
   Double_t f=1+alpha*cosY*R;

   Double_t result=f-pol*polState*g;
   if (result<0) result=1.0e-12;
   return result;
 } 

Double_t LinPolPDF::evaluateMC(const vector<Float_t> *vars,const  vector<Int_t> *cats) const {
// ENTER IDENTICAL EXPRESSION TO evaluate() IN TERMS OF MC VARIABLE ARGUMENTS HERE
   Double_t mcPhi=(*vars)[fTreeEntry*fNvars+0];
   Double_t mcCosX=(*vars)[fTreeEntry*fNvars+1];
   Double_t mcCosY=(*vars)[fTreeEntry*fNvars+2];
   Double_t mcCosZ=(*vars)[fTreeEntry*fNvars+3];
   Double_t mcPol=(*vars)[fTreeEntry*fNvars+4];
   Int_t mcPolState=(*cats)[fTreeEntry*fNcats+0];
   
   Double_t alpha=-0.980;
   Double_t g=(B+alpha*mcCosY*T)*TMath::Cos(2*(mcPhi))+alpha*(mcCosX*Ox+mcCosZ*Oz)*TMath::Sin(2*(mcPhi));
   Double_t f=1+alpha*mcCosY*R;

   Double_t result = f-mcPol*mcPolState*g;
   if (result<0) result=1.0e-12;
   return result;

}


