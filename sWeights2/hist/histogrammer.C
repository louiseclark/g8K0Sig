#define histogrammer_cxx
// The class definition in histogrammer.h has been generated automatically
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
// root> T->Process("histogrammer.C")
// root> T->Process("histogrammer.C","some options")
// root> T->Process("histogrammer.C+")
//


#include "histogrammer.h"
#include <TH2.h>
#include <TStyle.h>

void histogrammer::Begin(TTree * /*tree*/)
{
   THSOutput::HSBegin(fInput,fOutput);
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
//If you want to split histograms into different kinematic bins, include and configure the lines below
   fBins=new THSBins("HSBins");
   fBins->AddAxis("costhbins",1,-1.0,1.0);
   //fBins->AddAxis("top",4,-0.5,3.5);
   fBins->AddAxis("Ebins",1,1.1,2.1);
   if(!fInput) fInput=new TList();
   fInput->Add(fBins);
}

void histogrammer::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
   THSOutput::HSSlaveBegin(fInput,fOutput);
   
   //Get weights from file
   THSHisto::LoadWeights("/home/louise/g8K0Sig/code/sWeights2/out_all_pi0K0_binned/Tweights.root","HSsWeights");
   
  //Initialise and configure histogramming
   THSHisto::InitialiseHisto(fInput);
   //Load histograms for each species that has a weight
   THSHisto::LoadCutsForWeights(); //Loop over weights species and make weighted histograms for each
   THSHisto::LoadCut("All");
   THSHisto::LoadHistograms();

}

Bool_t histogrammer::Process(Long64_t entry)
{
   THSOutput::HSProcessStart(entry);
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // When processing keyed objects with PROOF, the object is already loaded
   // and is available via the fObject pointer.
   //
   // This function should contain the \"body\" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.

   fReader.SetLocalEntry(entry);
 //below you can give vars corresponding to fBins axis
   fWeight=1; //For unweighted histograms
   //if(fBins) fCurrBin=fBins->FindBin(var1,var2,...);//if fBins is defined need to give this meaningful arguments
   //if(fBins) fCurrBin=fBins->FindBin(*Egamma);
   //if(fBins) fCurrBin=fBins->FindBin(*costhK0CMS);
   if(fBins) fCurrBin=fBins->FindBin(*costhK0CMS, *Egamma);
   FillHistograms("All");
   
   THSHisto::GetWeightEvent(*fgID); //get weights for this event, use fgID as works when permutating also
   THSHisto::FillCutsForWeights(); //Fill weighted hists
   
//	fWeight=fWeights->GetWeight("Signal");
//	if (PARA) FillHistograms("Para");
   
   THSOutput::HSProcessFill();
   return kTRUE;
}

void histogrammer::SlaveTerminate()
{
   THSOutput::HSSlaveTerminate();
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void histogrammer::Terminate()
{
   THSOutput::HSTerminate();
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

}
 
void histogrammer::HistogramList(TString sLabel){
  TDirectory::AddDirectory(kFALSE); //do not add to current directory
  
    //now define all histograms and add to Output

	fOutput->Add(MapHist(new TH2F("costhK0CMS_Egamma","costhK0CMS_Egamma", 100, -0.1, 0.1, 100, 1.1, 2.1)));
  

  //label includes kinematic bin and additional cut name
  // e.g fOutput->Add(MapHist(new TH1F("Mp1","M_{p1}",100,0,2)));
  //end of histogram list
  TDirectory::AddDirectory(kTRUE); //back to normal
}
void histogrammer::FillHistograms(TString sCut){ 
  if(fBins&&fCurrBin==-1) return; //Outwith bin limits so no hists
  fCurrCut=sCut;
  //Get histogram from list
  
  //Find and fill weighted hist below here
  //e.g. FindHist("Mp1")->Fill(fp1->M(),fWeight);
  //e.g. ((TH2F*)FindHist("Mp1VMmiss"))->Fill(fp1->M(),Mmiss,fWeight);
  

  ((TH2F*)FindHist("costhK0CMS_Egamma"))->Fill(*costhK0CMS, *Egamma, fWeight);

}

