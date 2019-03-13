#define SWana_cxx
// The class definition in SWana.h has been generated automatically
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
// Root > T->Process("SWana.C")
// Root > T->Process("SWana.C","some options")
// Root > T->Process("SWana.C+")
//

#include "SWana.h"
#include <TH2.h>
#include <TStyle.h>


void SWana::Begin(TTree * /*tree*/)
{
   THSOutput::HSBegin(fInput,fOutput);
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

void SWana::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

   THSOutput::HSSlaveBegin(fInput,fOutput);
  //if you want kinematic bins you must define fHisbins here
   //fHisbins=new TH*()
   //if(fHisbins) fOutput->Add(fHisbins);
   //fHisbins->SetXTitle();//give useful axis name
   //fHisbins->SetYTitle();//give useful axis name
   THSHisto::ChangeNames();
   THSHisto::LoadCut("Cut1");
   THSHisto::LoadHistograms();
}

Bool_t SWana::Process(Long64_t entry)
{
   THSOutput::HSProcessStart(entry);
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either SWana::GetEntry() or TBranch::GetEntry()
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
   
   //Int_t kinBin=GetKinBin();//if fHisbins is defined need to give this meaningful arguments
   //FillHistograms("Cut1",kinBin);
   if(lppipi->M()>0.08) FillHistograms("Cut1",0);
   //EnterKinBinList(kinBin,entry);//save evente in kinematic bins entry lists
   THSOutput::HSProcessFill(); 


   return kTRUE;
}

void SWana::SlaveTerminate()
{
   THSOutput::HSSlaveTerminate();
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void SWana::Terminate()
{
   THSOutput::HSTerminate();
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

}
void SWana::HistogramList(TString sLabel){
  TDirectory::AddDirectory(kFALSE); //do not add to current directory
  //now define all histograms and add to Output
  //label includes kinematic bin and additional cut name
  // e.g fOutput->Add(MapHist(new TH1F("Mp1"+sLabel,"M_{p1}"+sLabel,100,0,2)));
  fOutput->Add(MapHist(new TH1F("proton"+sLabel,"M_{proton}"+sLabel,100,0,2)));
  fOutput->Add(MapHist(new TH1F("piplus"+sLabel,"M_{piplus}"+sLabel,100,0,2)));
  fOutput->Add(MapHist(new TH1F("piminus"+sLabel,"M_{piminus}"+sLabel,100,0,2)));
  fOutput->Add(MapHist(new TH1F("MMPpipi"+sLabel,"MM_{Ppipi}"+sLabel,100,0,2)));
  fOutput->Add(MapHist(new TH1F("Mpippim"+sLabel,"M_{pi+pi-}"+sLabel,100,0,2)));
  fOutput->Add(MapHist(new TH1F("Mpipipi"+sLabel,"M_{pipipi}"+sLabel,100,0,2)));
  fOutput->Add(MapHist(new TH1F("MPpi0"+sLabel,"M_{Ppi0}"+sLabel,100,0,2)));
  fOutput->Add(MapHist(new TH2F("MpippimvsMMpippim"+sLabel,"M_{pi+pi-} vs MM_{pi+pi-}"+sLabel,100,0,2,100,1,2)));
  fOutput->Add(MapHist(new TH2F("MpippimvsMPpi0"+sLabel,"M_{pi+pi-} vs M_{Ppi0}"+sLabel,100,0,2,100,1,2)));
  //end of histogram list
  TDirectory::AddDirectory(kTRUE); //back to normal
}
void SWana::FillHistograms(TString sCut,Int_t bin){
  fCurrCut=sCut;
  fCurrBin=bin;
  //Get histogram from list
  //Fill histogram
  TString sLabel;
  sLabel=sCut+fVecBinNames[bin];
  // e.g. FindHist("Mp1"+sLabel)->Fill(fp1->M());
  FindHist("proton"+sLabel)->Fill(lP->M());
  FindHist("piplus"+sLabel)->Fill(lPiplus->M());
  FindHist("piminus"+sLabel)->Fill(lPiminus->M());
  FindHist("MMPpipi"+sLabel)->Fill(lppipi->M());
  FindHist("Mpippim"+sLabel)->Fill(lKzero->M());
  FindHist("Mpipipi"+sLabel)->Fill(lpipipi->M());
  FindHist("MPpi0"+sLabel)->Fill(lSigma->M());
  ((TH2F*)FindHist("MpippimvsMMpippim"+sLabel))->Fill(lKzero->M(),lMissing_Sigma->M());
  ((TH2F*)FindHist("MpippimvsMPpi0"+sLabel))->Fill(lKzero->M(),lSigma->M());

}
