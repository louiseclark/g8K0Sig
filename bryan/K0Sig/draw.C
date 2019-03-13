#define draw_cxx
// The class definition in draw.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// Root > T->Process("draw.C")
// Root > T->Process("draw.C","some options")
// Root > T->Process("draw.C+")
//

#include "draw.h"
#include <TH2.h>
#include <TStyle.h>


void draw::Begin(TTree * /*tree*/)
{
   THSOutput::HSBegin(fInput,fOutput);
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

void draw::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

   THSOutput::HSSlaveBegin(fInput,fOutput);
  //if you want kinematic bins you must define fHisbins here
   fHisbins=new TH2F("EgVCTH","EgVCTH",10,1,4,10,-1,1);
   if(fHisbins) fOutput->Add(fHisbins);
   fHisbins->SetXTitle("Eg");//give useful axis name
   fHisbins->SetYTitle("CTH");//give useful axis name
   THSHisto::ChangeNames();
   THSHisto::LoadCut("Cut1");
   THSHisto::LoadCut("Cut2");
   THSHisto::LoadHistograms();
}

Bool_t draw::Process(Long64_t entry)
{
   THSOutput::HSProcessStart(entry);
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either draw::GetEntry() or TBranch::GetEntry()
   // to read either all or the required parts of the data. When processing
   // keyed objects with PROOF, the object is already loaded and is available
   // via the fObject pointer.
   //
   // This function should contain the "body" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.
   GetEntry(entry); //lazy and slow, you can speed the code up by getting the branches you need to use instead
   //Ready to do some analysis here, before the Fill
   
   Int_t kinBin=GetKinBin(lPhoton->E(),lnkp_cm->CosTheta());//if fHisbins is defined need to give this meaningful arguments
   //FillHistograms("Cut1",kinBin);
   FillHistograms("Cut1",kinBin);
   if(lPhoton->E()>2) FillHistograms("Cut2",kinBin);
   EnterKinBinList(kinBin,entry);//save evente in kinematic bins entry lists
   THSOutput::HSProcessFill(); 


   return kTRUE;
}

void draw::SlaveTerminate()
{
   THSOutput::HSSlaveTerminate();
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void draw::Terminate()
{
   THSOutput::HSTerminate();
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

}
void draw::HistogramList(TString sLabel){
  TDirectory::AddDirectory(kFALSE); //do not add to current directory
  //now define all histograms and add to Output
  //label includes kinematic bin and additional cut name
  // e.g fOutput->Add(MapHist(new TH1F("Mp1"+sLabel,"M_{p1}"+sLabel,100,0,2)));
  fOutput->Add(MapHist(new TH1F("MLambda"+sLabel,"M_{#Lambda}"+sLabel,100,0,2)));
  fOutput->Add(MapHist(new TH2F("MLambdaVMM"+sLabel,"M_{#Lambda}V MM"+sLabel,100,0,2,100,0,2)));
  //end of histogram list
  TDirectory::AddDirectory(kTRUE); //back to normal
}
void draw::FillHistograms(TString sCut,Int_t bin){
  fCurrCut=sCut;
  fCurrBin=bin;
  //Get histogram from list
  //Fill histogramlLambda
  TString sLabel;
  sLabel=sCut+fVecBinNames[bin];
  FindHist("MLambda"+sLabel)->Fill(lLambda->M());
  ((TH2F*)FindHist("MLambdaVMM"+sLabel))->Fill(lLambda->M(),lLambdaMM->M());
}
