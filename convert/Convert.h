//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Nov 11 13:51:56 2016 by ROOT version 5.34/24
// from TTree HSParticles/output tree
// found on file: /home/louise/rootbeer2.2/filepKpKm.root
//////////////////////////////////////////////////////////

#ifndef Convert_h
#define Convert_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TLorentzRotation.h>
#include "THSOutput.h"
//#include "particleDEF.h"        //Particle Definitions

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class Convert : public TSelector, public THSOutput {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   // Declaration of leaf types
   Double_t        fgID;
   Double_t        pol;
   Int_t           polState;
   THSParticle     *proton;
   THSParticle     *pip;
   THSParticle     *pim;
   THSParticle     *beam;

   // Louise
   bool		isSim = false;
   Double_t  eGamma;
   Double_t  t;
   
   Double_t MM_p_pip_pim;		// pi0
   Double_t MM2_p_pip_pim;		// pi0
   Double_t M_pip_pim;		    // K0 or rho
   Double_t M2_pip_pim;		    // K0 or rho
   Double_t MM_p;				// omega
   Double_t MM2_p;				// omega
   Double_t M_3pi;
   Double_t M2_3pi;
   Double_t MM_pip_pim;	        // Sigma
   Double_t MM2_pip_pim;	        // Sigma
   Double_t M_p_pi0;	        // Sigma
   Double_t M2_p_pi0;	        // Sigma
   
   Double_t  phiSigma; 
   Double_t  phiK0; // also angle of production plane wrt para polarization
   Double_t  phiSigmamPhiK0;
   // Direction cosines of the decay proton in rest frame of Sigma
   Double_t	 cosX;
   Double_t  cosY;
   Double_t  cosZ;
   
   Double_t costhK0CMS; // costh of K0 in CMS

   TLorentzVector *lTarget;
   TLorentzVector *lt;
   TLorentzVector *lProton;
   TLorentzVector *lpip;
   TLorentzVector *lpim;
   TLorentzVector *lpi0;
   TLorentzVector *lSigma;
   TLorentzVector *lK0;  

  //data members for new branches
  //you must define how they are processed for each event
  //e.g.   TLorentzVector  *fp1;

   // List of branches
   TBranch        *b_fgID;   //!
   TBranch        *b_pol;   //!
   TBranch        *b_polState;   //!
   TBranch        *b_proton;   //!
   TBranch        *b_pip;   //!
   TBranch        *b_pim;   //!
   TBranch        *b_beam;   //!

   Convert(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~Convert() { }
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

   ClassDef(Convert,0);
};

#endif

#ifdef Convert_cxx
void Convert::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   proton = 0;
   pip = 0;
   pim = 0;
   beam = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("fgID", &fgID, &b_fgID);
   fChain->SetBranchAddress("pol", &pol, &b_pol);
   fChain->SetBranchAddress("polState", &polState, &b_polState);
   fChain->SetBranchAddress("proton", &proton, &b_proton);
   fChain->SetBranchAddress("pip", &pip, &b_pip);
   fChain->SetBranchAddress("pim", &pim, &b_pim);
   fChain->SetBranchAddress("beam", &beam, &b_beam);
}

Bool_t Convert::Notify()
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

#endif // #ifdef Convert_cxx
   
