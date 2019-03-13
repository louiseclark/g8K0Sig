//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Nov 13 10:49:04 2015 by ROOT version 5.34/24
// from TTree PartTree/Tree of Particle 4-Vectors
// found on file: /home/bryanm/kstree_eloss.root
//////////////////////////////////////////////////////////

#ifndef SWanaPARA_h
#define SWanaPARA_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include "THSOutput.h"

// Header file for the classes stored in the TTree if any.
#include <TLorentzVector.h>

// Fixed size dimensions of array or collections stored in the TTree if any.

class SWanaPARA : public TSelector, public THSOutput {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   // Declaration of leaf types
   TLorentzVector  *lP;
   TLorentzVector  *lPiplus;
   TLorentzVector  *lPiminus;
   TLorentzVector  *lPhoton;
   TLorentzVector  *lTarget;
   TLorentzVector  *lppipi;
   TLorentzVector  *lMissing_Pizero;
   TLorentzVector  *lKzero;
   TLorentzVector  *lSigma;
   TLorentzVector  *lMissing_Sigma;
   TLorentzVector  *lpipipi;

   Float_t polDegree;
   Double_t cohEdge;
   Int_t polPlane;
   Int_t polRadiator;

   // Declaration of added TLorentzVectors
   TLorentzVector  lDipim;
   TLorentzVector  lDipip;
  
   TLorentzVector  lW;

   TLorentzVector lCM;
   TVector3 boost_cms;
  //data members for new branches
  //you must define how they are processed for each event
  //e.g.   TLorentzVector  *fp1;

   // List of branches
   TBranch        *b_lP;   //!
   TBranch        *b_lPiplus;   //!
   TBranch        *b_lPiminus;   //!
   TBranch        *b_lPhoton;   //!
   TBranch        *b_lTarget;   //!
   TBranch        *b_lppipi;   //!
   TBranch        *b_lMissing_Pizero;   //!
   TBranch        *b_lKzero;   //!
   TBranch        *b_lSigma;   //!
   TBranch        *b_lMissing_Sigma;   //!
   TBranch        *b_lpipipi;   //!

   TBranch        *b_polDegree;
   TBranch        *b_cohEdge;
   TBranch        *b_polPlane;
   TBranch        *b_polRadiator;
  
 
   Float_t Mpipi;
   Float_t Epipi;
   Float_t Phipipi;
   Float_t Cospipi;
   Float_t MPpi0;
   Float_t EPpi0;
   Float_t CosPpi0;
   Float_t M3pi;
   Float_t E3pi;
   Float_t Cos3pi;
   Float_t Egamma;
   Float_t INVMPpi0;
   Float_t INVEPpi0;
   Float_t INVCosPpi0;
   Float_t W;


   Float_t LinpolDegree;
   Double_t LincohEdge;
   Int_t LinpolPlane;
   Int_t LinpolRadiator;



   SWanaPARA(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~SWanaPARA() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();
//Add THSHisto functions
   virtual void HistogramList(TString sLabel);
   virtual void FillHistograms(TString sCut,Int_t bin);

   ClassDef(SWanaPARA,0);
};

#endif

#ifdef SWanaPARA_cxx
void SWanaPARA::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   lP = 0;
   lPiplus = 0;
   lPiminus = 0;
   lPhoton = 0;
   lTarget = 0;
   lppipi = 0;
   lMissing_Pizero = 0;
   lKzero = 0;
   lSigma = 0;
   lMissing_Sigma = 0;
   lpipipi = 0;
   polDegree = 0;
   cohEdge = 0;
   polPlane = 0;
   polRadiator = 0;

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("lP", &lP, &b_lP);
   fChain->SetBranchAddress("lPiplus", &lPiplus, &b_lPiplus);
   fChain->SetBranchAddress("lPiminus", &lPiminus, &b_lPiminus);
   fChain->SetBranchAddress("lPhoton", &lPhoton, &b_lPhoton);
   fChain->SetBranchAddress("lTarget", &lTarget, &b_lTarget);
   fChain->SetBranchAddress("lppipi", &lppipi, &b_lppipi);
   fChain->SetBranchAddress("lMissing_Pizero", &lMissing_Pizero, &b_lMissing_Pizero);
   fChain->SetBranchAddress("lKzero", &lKzero, &b_lKzero);
   fChain->SetBranchAddress("lSigma", &lSigma, &b_lSigma);
   fChain->SetBranchAddress("lMissing_Sigma", &lMissing_Sigma, &b_lMissing_Sigma);
   fChain->SetBranchAddress("lpipipi", &lpipipi, &b_lpipipi);
   fChain->SetBranchAddress("polDegree", &polDegree, &b_polDegree);
   fChain->SetBranchAddress("cohEdge", &cohEdge, &b_cohEdge);
   fChain->SetBranchAddress("polPlane", &polPlane, &b_polPlane);
   fChain->SetBranchAddress("polRadiator", &polRadiator, &b_polRadiator);
}

Bool_t SWanaPARA::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.
   THSOutput::HSNotify(fChain);
  THSOutput::InitOutTree();

   return kTRUE;
}

#endif // #ifdef SWanaPARA_cxx
