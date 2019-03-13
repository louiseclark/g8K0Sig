//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Sep 22 11:56:55 2017 by ROOT version 6.08/06
// from TTree HSParticles/A tree containing reconstructed particles
// found on file: /home/louise/g8_phi/haspect/Events/Projects/g8phi/convert_output1/filepKp_all.root
//////////////////////////////////////////////////////////

#ifndef histogrammer_h
#define histogrammer_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include "THSOutput.h"
#include "THSWeights.h"
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector


class histogrammer : public TSelector, public THSOutput {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain
   
  //data members for reading weights
   THSWeights* fWeights=0;
   // Readers to access the data (delete the ones you do not need).
   TTreeReaderValue<Double_t> Egamma = {fReader, "Egamma"};
   TTreeReaderValue<Double_t> t = {fReader, "t"};
   TTreeReaderValue<Double_t> MM_p_pip_pim = {fReader, "MM_p_pip_pim"};
   TTreeReaderValue<Double_t> MM2_p_pip_pim = {fReader, "MM2_p_pip_pim"};
   TTreeReaderValue<Double_t> M_pip_pim = {fReader, "M_pip_pim"};
   TTreeReaderValue<Double_t> M2_pip_pim = {fReader, "M2_pip_pim"};
   TTreeReaderValue<Double_t> MM_p = {fReader, "MM_p"};
   TTreeReaderValue<Double_t> MM2_p = {fReader, "MM2_p"};
   TTreeReaderValue<Double_t> M_3pi = {fReader, "M_3pi"};
   TTreeReaderValue<Double_t> M2_3pi = {fReader, "M2_3pi"};
   TTreeReaderValue<Double_t> MM_pip_pim = {fReader, "MM_pip_pim"};
   TTreeReaderValue<Double_t> MM2_pip_pim = {fReader, "MM2_pip_pim"};
   TTreeReaderValue<Double_t> M_p_pi0 = {fReader, "M_p_pi0"};
   TTreeReaderValue<Double_t> M2_p_pi0 = {fReader, "M2_p_pi0"};
   TTreeReaderValue<Double_t> phiSigma = {fReader, "phiSigma"};
   TTreeReaderValue<Double_t> phiK0 = {fReader, "phiK0"};
   TTreeReaderValue<Double_t> cosX = {fReader, "cosX"};
   TTreeReaderValue<Double_t> cosY = {fReader, "cosY"};
   TTreeReaderValue<Double_t> cosZ = {fReader, "cosZ"};
   TTreeReaderValue<Double_t> costhK0CMS = {fReader, "costhK0CMS"};
   
   TTreeReaderValue<Int_t> polState = {fReader, "polState"};
   TTreeReaderValue<Double_t> pol = {fReader, "pol"};
   TTreeReaderValue<Double_t> fgID = {fReader, "fgID"};


   histogrammer(TTree * /*tree*/ =0) { }
   virtual ~histogrammer() {SafeDelete(fWeights);  }
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
   virtual void FillHistograms(TString sCut);

   ClassDef(histogrammer,0);

};

#endif

#ifdef histogrammer_cxx
void histogrammer::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
}

Bool_t histogrammer::Notify()
{
   fChain=fReader.GetTree();
   THSOutput::HSNotify(fChain);
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}


#endif // #ifdef histogrammer_cxx
