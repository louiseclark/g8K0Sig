//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Oct  5 16:03:33 2015 by ROOT version 5.34/24
// from TTree PartTree/Tree of Particle 4-Vectors
// found on file: /home/bryanm/new/LPS/testwolam3375.root
//////////////////////////////////////////////////////////

#ifndef draw_h
#define draw_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include "THSOutput.h"

// Header file for the classes stored in the TTree if any.
#include <TLorentzVector.h>

// Fixed size dimensions of array or collections stored in the TTree if any.

class draw : public TSelector, public THSOutput {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   // Declaration of leaf types
   TLorentzVector  *lP;
   TLorentzVector  *lKplus;
   TLorentzVector  *lKminus;
   TLorentzVector  *lPhoton;
   TLorentzVector  *lTarget;
   TLorentzVector  *lMiss_id1;
   TLorentzVector  *lMiss_id2;
   TLorentzVector  *lMiss_id3;
   TLorentzVector  *lMiss_id4;
   TLorentzVector  *lMiss_id5;
   TLorentzVector  *lpkk;
   TLorentzVector  *lMissing_Neutron;
   TLorentzVector  *lMissing_Neutronb;
   TLorentzVector  *lPhi;
   TLorentzVector  *lLambda;
   TLorentzVector  *lmissmasspkm;
   TLorentzVector  *linvmasspkp;
   TLorentzVector  *lmissmasspkp;
   TLorentzVector  *lmainthing1;
   TLorentzVector  *lmainthing2;
   TLorentzVector  *lmainthing3;
   TLorentzVector  *lEcw;
   TLorentzVector  *lEcwo;
   TLorentzVector  *lbKinF;
   TLorentzVector  *lgKinF;
   TLorentzVector  *lN;
   TLorentzVector  *lSigma;
   TLorentzVector  *lLambdaMM;
   TLorentzVector  *lLambdaMMKF;
   TLorentzVector  *lnkp_cm;
   TLorentzVector  *lNeutTarg;
   TLorentzVector  *lnkp_cmneut;

   // List of branches
   TBranch        *b_lP;   //!
   TBranch        *b_lKplus;   //!
   TBranch        *b_lKminus;   //!
   TBranch        *b_lPhoton;   //!
   TBranch        *b_lTarget;   //!
   TBranch        *b_lMiss_id1;   //!
   TBranch        *b_lMiss_id2;   //!
   TBranch        *b_lMiss_id3;   //!
   TBranch        *b_lMiss_id4;   //!
   TBranch        *b_lMiss_id5;   //!
   TBranch        *b_lpkk;   //!
   TBranch        *b_lMissing_Neutron;   //!
   TBranch        *b_lMissing_Neutronb;   //!
   TBranch        *b_lPhi;   //!
   TBranch        *b_lLambda;   //!
   TBranch        *b_lmissmasspkm;   //!
   TBranch        *b_linvmasspkp;   //!
   TBranch        *b_lmissmasspkp;   //!
   TBranch        *b_lmainthing1;   //!
   TBranch        *b_lmainthing2;   //!
   TBranch        *b_lmainthing3;   //!
   TBranch        *b_lEcw;   //!
   TBranch        *b_lEcwo;   //!
   TBranch        *b_lbKinF;   //!
   TBranch        *b_lgKinF;   //!
   TBranch        *b_lN;   //!
   TBranch        *b_lSigma;   //!
   TBranch        *b_lLambdaMM;   //!
   TBranch        *b_lLambdaMMKF;   //!
   TBranch        *b_lnkp_cm;   //!
   TBranch        *b_lNeutTarg;   //!
   TBranch        *b_lnkp_cmneut;   //!

   draw(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~draw() { }
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

   ClassDef(draw,0);
};

#endif

#ifdef draw_cxx
void draw::Init(TTree *tree)
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
   lKplus = 0;
   lKminus = 0;
   lPhoton = 0;
   lTarget = 0;
   lMiss_id1 = 0;
   lMiss_id2 = 0;
   lMiss_id3 = 0;
   lMiss_id4 = 0;
   lMiss_id5 = 0;
   lpkk = 0;
   lMissing_Neutron = 0;
   lMissing_Neutronb = 0;
   lPhi = 0;
   lLambda = 0;
   lmissmasspkm = 0;
   linvmasspkp = 0;
   lmissmasspkp = 0;
   lmainthing1 = 0;
   lmainthing2 = 0;
   lmainthing3 = 0;
   lEcw = 0;
   lEcwo = 0;
   lbKinF = 0;
   lgKinF = 0;
   lN = 0;
   lSigma = 0;
   lLambdaMM = 0;
   lLambdaMMKF = 0;
   lnkp_cm = 0;
   lNeutTarg = 0;
   lnkp_cmneut = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("lP", &lP, &b_lP);
   fChain->SetBranchAddress("lKplus", &lKplus, &b_lKplus);
   fChain->SetBranchAddress("lKminus", &lKminus, &b_lKminus);
   fChain->SetBranchAddress("lPhoton", &lPhoton, &b_lPhoton);
   fChain->SetBranchAddress("lTarget", &lTarget, &b_lTarget);
   fChain->SetBranchAddress("lMiss_id1", &lMiss_id1, &b_lMiss_id1);
   fChain->SetBranchAddress("lMiss_id2", &lMiss_id2, &b_lMiss_id2);
   fChain->SetBranchAddress("lMiss_id3", &lMiss_id3, &b_lMiss_id3);
   fChain->SetBranchAddress("lMiss_id4", &lMiss_id4, &b_lMiss_id4);
   fChain->SetBranchAddress("lMiss_id5", &lMiss_id5, &b_lMiss_id5);
   fChain->SetBranchAddress("lpkk", &lpkk, &b_lpkk);
   fChain->SetBranchAddress("lMissing_Neutron", &lMissing_Neutron, &b_lMissing_Neutron);
   fChain->SetBranchAddress("lMissing_Neutronb", &lMissing_Neutronb, &b_lMissing_Neutronb);
   fChain->SetBranchAddress("lPhi", &lPhi, &b_lPhi);
   fChain->SetBranchAddress("lLambda", &lLambda, &b_lLambda);
   fChain->SetBranchAddress("lmissmasspkm", &lmissmasspkm, &b_lmissmasspkm);
   fChain->SetBranchAddress("linvmasspkp", &linvmasspkp, &b_linvmasspkp);
   fChain->SetBranchAddress("lmissmasspkp", &lmissmasspkp, &b_lmissmasspkp);
   fChain->SetBranchAddress("lmainthing1", &lmainthing1, &b_lmainthing1);
   fChain->SetBranchAddress("lmainthing2", &lmainthing2, &b_lmainthing2);
   fChain->SetBranchAddress("lmainthing3", &lmainthing3, &b_lmainthing3);
   fChain->SetBranchAddress("lEcw", &lEcw, &b_lEcw);
   fChain->SetBranchAddress("lEcwo", &lEcwo, &b_lEcwo);
   fChain->SetBranchAddress("lbKinF", &lbKinF, &b_lbKinF);
   fChain->SetBranchAddress("lgKinF", &lgKinF, &b_lgKinF);
   fChain->SetBranchAddress("lN", &lN, &b_lN);
   fChain->SetBranchAddress("lSigma", &lSigma, &b_lSigma);
   fChain->SetBranchAddress("lLambdaMM", &lLambdaMM, &b_lLambdaMM);
   fChain->SetBranchAddress("lLambdaMMKF", &lLambdaMMKF, &b_lLambdaMMKF);
   fChain->SetBranchAddress("lnkp_cm", &lnkp_cm, &b_lnkp_cm);
   fChain->SetBranchAddress("lNeutTarg", &lNeutTarg, &b_lNeutTarg);
   fChain->SetBranchAddress("lnkp_cmneut", &lnkp_cmneut, &b_lnkp_cmneut);
}

Bool_t draw::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.
   THSOutput::HSNotify(fChain);

   return kTRUE;
}

#endif // #ifdef draw_cxx
