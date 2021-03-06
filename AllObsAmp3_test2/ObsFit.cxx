/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/ 

// Your description goes here... 

#include "Riostream.h" 

#include "ObsFit.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 

ClassImp(ObsFit); 

 ObsFit::ObsFit(const char *name, const char *title, 
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
   HS::FIT::RooHSEventsPDF(name,title),
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
   cosX.SetName(_cosX.GetName());
   cosY.SetName(_cosY.GetName());
   cosZ.SetName(_cosZ.GetName());
   pol.SetName(_pol.GetName());
   polState.SetName(_polState.GetName());
   B.SetName(_B.GetName());
   T.SetName(_T.GetName());
   Ox.SetName(_Ox.GetName());
   Oz.SetName(_Oz.GetName());
   R.SetName(_R.GetName());
 } 


 ObsFit::ObsFit(const ObsFit& other, const char* name) :  
   HS::FIT::RooHSEventsPDF(other,name),
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
void ObsFit::MakeSets(){
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



 Double_t ObsFit::evaluate() const 
 { 
  Double_t alpha=-0.980; 
   Double_t g=(B+alpha*cosY*T)*TMath::Cos(2*(phiK0))+alpha*(cosX*Ox+cosZ*Oz)*TMath::Sin(2*(phiK0));
   Double_t f=1+alpha*cosY*R;

   Double_t result=f-pol*polState*g;
   //if (result<0) result=1.0; //1.0e-12;
   return result;  // ENTER EXPRESSION IN TERMS OF VARIABLE ARGUMENTS HERE 

 } 

Double_t ObsFit::evaluateMC(const vector<Float_t> *vars,const  vector<Int_t> *cats) const {
// ENTER IDENTICAL EXPRESSION TO evaluate() IN TERMS OF MC VARIABLE ARGUMENTS HERE
  Double_t mcphiK0=(*vars)[fTreeEntry*fNvars+0];
  Double_t mccosX=(*vars)[fTreeEntry*fNvars+1];
  Double_t mccosY=(*vars)[fTreeEntry*fNvars+2];
  Double_t mccosZ=(*vars)[fTreeEntry*fNvars+3];
  Double_t mcpol=(*vars)[fTreeEntry*fNvars+4];
  Int_t mcpolState=(*cats)[fTreeEntry*fNcats+0];
  
   Double_t alpha=-0.980;
   Double_t g=(B+alpha*mccosY*T)*TMath::Cos(2*(mcphiK0))+alpha*(mccosX*Ox+mccosZ*Oz)*TMath::Sin(2*(mcphiK0));
   Double_t f=1+alpha*mccosY*R;

   Double_t result = f-mcpol*mcpolState*g;
   return result; 
}


