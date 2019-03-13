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
   fBins->AddAxis("costhbins",3,-1.0,1.0);
   //fBins->AddAxis("top",4,-0.5,3.5);
   fBins->AddAxis("Ebins",2,1.1,2.1);
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
   THSHisto::LoadWeights("/home/louise/g8K0Sig/code/sWeights/out_all_pi0K0/Weights_all.root","HSsWeights");
   
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

	fOutput->Add(MapHist(new TH1F("MM_p_pip_pim","MM_p_pip_pim", 100, -0.2, 0.9)));
	fOutput->Add(MapHist(new TH1F("MM2_p_pip_pim","MM2_p_pip_pim", 100, -0.2, 0.9)));
	fOutput->Add(MapHist(new TH1F("MM_p_pip_pim_z","MM_p_pip_pim_z", 100, 0.02, 0.3)));
	fOutput->Add(MapHist(new TH1F("MM2_p_pip_pim_z","MM2_p_pip_pim_z", 100, 0.0, 0.1)));

	fOutput->Add(MapHist(new TH1F("M_pip_pim","M_pip_pim", 100, 0.2, 1.4)));
	fOutput->Add(MapHist(new TH1F("M2_pip_pim","M2_pip_pim", 100, 0.04, 1.96)));
	fOutput->Add(MapHist(new TH1F("M_pip_pim_z","M_pip_pim_z", 100, 0.3, 0.65)));
	fOutput->Add(MapHist(new TH1F("M2_pip_pim_z","M2_pip_pim_z", 100, 0.1, 0.45)));
	
	fOutput->Add(MapHist(new TH1F("MM_p","MM_p", 100, 0.0, 1.3)));
	fOutput->Add(MapHist(new TH1F("MM2_p","MM2_p", 100, 0.0, 1.7)));
	fOutput->Add(MapHist(new TH1F("MM_p_z","MM_p_z", 100, 0.45, 1.05)));
	fOutput->Add(MapHist(new TH1F("MM2_p_z","MM2_p_z", 100, 0.2, 1.1)));
	
	fOutput->Add(MapHist(new TH1F("M_3pi","M_3pi", 100, 0.0, 1.5)));
	fOutput->Add(MapHist(new TH1F("M2_3pi","M2_3pi", 100, 0.0, 2.0)));
	fOutput->Add(MapHist(new TH1F("M_3pi_z","M_3pi_z", 100, 0.45, 1.05)));
	fOutput->Add(MapHist(new TH1F("M2_3pi_z","M2_3pi_z", 100, 0.2, 1.1)));
	
	fOutput->Add(MapHist(new TH1F("MM_pip_pim","MM_pip_pim", 100, 0.6, 1.8)));
	fOutput->Add(MapHist(new TH1F("MM2_pip_pim","MM2_pip_pim", 100, 0.36, 3.24)));
	fOutput->Add(MapHist(new TH1F("MM_pip_pim_z","MM_pip_pim_z", 100, 1.0, 1.4)));
	fOutput->Add(MapHist(new TH1F("MM2_pip_pim_z","MM2_pip_pim_z", 100, 1.0, 1.8)));
	
	fOutput->Add(MapHist(new TH1F("M_p_pi0","M_p_pi0", 100, 1.0, 1.8)));
	fOutput->Add(MapHist(new TH1F("M2_p_pi0","M2_p_pi0", 100, 1.0, 3.24)));
	fOutput->Add(MapHist(new TH1F("M_p_pi0_z","M_p_pi0_z", 100, 1.0, 1.4)));
	fOutput->Add(MapHist(new TH1F("M2_p_pi0_z","M2_p_pi0_z", 100, 1.0, 1.8)));
	
	fOutput->Add(MapHist(new TH2F("MM_M_pip_pim","MM_M_pip_pim", 100, 0.2, 1.4, 100, 0.6, 1.8)));
	fOutput->Add(MapHist(new TH2F("MM2_M2_pip_pim","MM2_M2_pip_pim", 100, 0.04, 1.96, 100, 0.36, 3.24)));
	fOutput->Add(MapHist(new TH2F("MM_M_pip_pim_z","MM_M_pip_pim_z", 100, 0.3, 0.65, 100, 1.0, 1.4)));
	fOutput->Add(MapHist(new TH2F("MM2_M2_pip_pim_z","MM2_M2_pip_pim_z", 100, 0.1, 0.45, 100, 1.0, 1.8)));
    
    fOutput->Add(MapHist(new TH1F("t","t", 100, 0.0, 2.5)));
    fOutput->Add(MapHist(new TH1F("Egamma","Egamma", 100, 1.1, 2.1)));
    fOutput->Add(MapHist(new TH1F("costhK0CMS","costhK0CMS", 100, -1.0, 1.0)));
    
	
	// phi plots
	fOutput->Add(MapHist(new TH1F("phiSigPARA","phiSigPARA", 50, -3.2, 3.2)));
	fOutput->Add(MapHist(new TH1F("phiSigPERP","phiSigPERP", 50, -3.2, 3.2)));
	fOutput->Add(MapHist(new TH1F("phiK0PARA","phiK0PARA", 50, -3.2, 3.2)));
	fOutput->Add(MapHist(new TH1F("phiK0PERP","phiK0PERP", 50, -3.2, 3.2)));
	
	fOutput->Add(MapHist(new TH1F("cosXPARA","cosXPARA", 50, -1.0, 1.0)));
	fOutput->Add(MapHist(new TH1F("cosXPERP","cosXPERP", 50, -1.0, 1.0)));
	fOutput->Add(MapHist(new TH1F("cosYPARA","cosYPARA", 50, -1.0, 1.0)));
	fOutput->Add(MapHist(new TH1F("cosYPERP","cosYPERP", 50, -1.0, 1.0)));
	fOutput->Add(MapHist(new TH1F("cosZPARA","cosZPARA", 50, -1.0, 1.0)));
	fOutput->Add(MapHist(new TH1F("cosZPERP","cosZPERP", 50, -1.0, 1.0)));


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
  
  FindHist("MM_p_pip_pim")->Fill(*MM_p_pip_pim,fWeight);
  FindHist("MM2_p_pip_pim")->Fill(*MM2_p_pip_pim,fWeight);
  FindHist("MM_p_pip_pim_z")->Fill(*MM_p_pip_pim,fWeight);
  FindHist("MM2_p_pip_pim_z")->Fill(*MM2_p_pip_pim,fWeight);
  
  FindHist("M_pip_pim")->Fill(*M_pip_pim,fWeight);
  FindHist("M2_pip_pim")->Fill(*M2_pip_pim,fWeight);
  FindHist("M_pip_pim_z")->Fill(*M_pip_pim,fWeight);
  FindHist("M2_pip_pim_z")->Fill(*M2_pip_pim,fWeight);
  
  FindHist("MM_p")->Fill(*MM_p,fWeight);
  FindHist("MM2_p")->Fill(*MM2_p,fWeight);
  FindHist("MM_p_z")->Fill(*MM_p,fWeight);
  FindHist("MM2_p_z")->Fill(*MM2_p,fWeight);
  
  FindHist("M_3pi")->Fill(*M_3pi,fWeight);
  FindHist("M2_3pi")->Fill(*M2_3pi,fWeight);
  FindHist("M_3pi_z")->Fill(*M_3pi,fWeight);
  FindHist("M2_3pi_z")->Fill(*M2_3pi,fWeight);  
  
  FindHist("MM_pip_pim")->Fill(*MM_pip_pim,fWeight);
  FindHist("MM2_pip_pim")->Fill(*MM2_pip_pim,fWeight);
  FindHist("MM_pip_pim_z")->Fill(*MM_pip_pim,fWeight);
  FindHist("MM2_pip_pim_z")->Fill(*MM2_pip_pim,fWeight);
  
  FindHist("M_p_pi0")->Fill(*M_p_pi0,fWeight);
  FindHist("M2_p_pi0")->Fill(*M2_p_pi0,fWeight);
  FindHist("M_p_pi0_z")->Fill(*M_p_pi0,fWeight);
  FindHist("M2_p_pi0_z")->Fill(*M2_p_pi0,fWeight);

  ((TH2F*)FindHist("MM_M_pip_pim"))->Fill(*M_pip_pim, *MM_pip_pim, fWeight);
  ((TH2F*)FindHist("MM2_M2_pip_pim"))->Fill(*M2_pip_pim, *MM2_pip_pim, fWeight);
  ((TH2F*)FindHist("MM_M_pip_pim_z"))->Fill(*M_pip_pim, *MM_pip_pim, fWeight);
  ((TH2F*)FindHist("MM2_M2_pip_pim_z"))->Fill(*M2_pip_pim, *MM2_pip_pim, fWeight);

  FindHist("t")->Fill(*t,fWeight);
  FindHist("Egamma")->Fill(*Egamma,fWeight);
  FindHist("costhK0CMS")->Fill(*costhK0CMS,fWeight);

  FindHist("phiSigPARA")->Fill(*phiSigma,fWeight);
  FindHist("phiK0PARA")->Fill(*phiK0,fWeight);	  
  FindHist("cosXPARA")->Fill(*cosX,fWeight);
  FindHist("cosYPARA")->Fill(*cosY,fWeight);
  FindHist("cosZPARA")->Fill(*cosZ,fWeight);
  if (*polState==1) {
	  FindHist("phiSigPARA")->Fill(*phiSigma,fWeight);
	  FindHist("phiK0PARA")->Fill(*phiK0,fWeight);	  
	  FindHist("cosXPARA")->Fill(*cosX,fWeight);
	  FindHist("cosYPARA")->Fill(*cosY,fWeight);
	  FindHist("cosZPARA")->Fill(*cosZ,fWeight);
  }
  
  if (*polState==-1) {
	  FindHist("phiSigPERP")->Fill(*phiSigma,fWeight);
	  FindHist("phiK0PERP")->Fill(*phiK0,fWeight);	  
	  FindHist("cosXPERP")->Fill(*cosX,fWeight);
	  FindHist("cosYPERP")->Fill(*cosY,fWeight);
	  FindHist("cosZPERP")->Fill(*cosZ,fWeight);

  }
}

