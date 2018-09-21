#define Convert_cxx
// The class definition in Convert.h has been generated automatically
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
// Root > T->Process("Convert.C")
// Root > T->Process("Convert.C","some options")
// Root > T->Process("Convert.C+")
//

#include "Convert.h"
#include <TH2.h>
#include <TStyle.h>

void Convert::Begin(TTree * /*tree*/)
{
   THSOutput::HSBegin(fInput,fOutput);
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

void Convert::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

   THSOutput::HSSlaveBegin(fInput,fOutput);
  //Initialise the ouput tree
   Int_t buff=32000;
   Int_t split=0;//note split is important in the TSelector framework, if increased branches in subsequent selectors will be data members of the THSParticle object rather than the whole object (this can lead to name conflicts)
   //Only done once. THSOutput::FinishOutput Resets the tree before new files
   //If you want to save additional branches to a new file, do it here
   //If you are creating a HSParticle tree via fStrParticles then do not create a new tree here, just add the extra brasnches
   fOutTree=new TTree("HSParticles","A tree containing reconstructed particles");

   // Louise
   fOutTree->Branch("Egamma",&eGamma,"Egamma/D");
   fOutTree->Branch("t",&t,"t/D");

   fOutTree->Branch("MM_p_pip_pim",&MM_p_pip_pim,"MM_p_pip_pim/D");
   fOutTree->Branch("M_pip_pim",&M_pip_pim,"M_pip_pim/D");
   fOutTree->Branch("MM_p",&MM_p,"MM_p/D");
   fOutTree->Branch("MM_pip_pim",&MM_pip_pim,"MM_pip_pim/D");
   fOutTree->Branch("M_p_pi0",&M_p_pi0,"M_p_pi0/D");
   
   // For study of Sigma beam asymmetry
   fOutTree->Branch("phiSigma",&phiSigma,"phiSigma/D");
   fOutTree->Branch("phiK0",&phiK0,"phiK0/D");
   fOutTree->Branch("phiSigmamPhiK0",&phiSigmamPhiK0,"phiSigmamPhiK0/D");
   
   
   if (!(isSim)) {
      fOutTree->Branch("polState",&polState,"polState/I");
      fOutTree->Branch("pol",&pol,"pol/D");
   }

   lTarget = new TLorentzVector(1.0,1.0,1.0,1.0);
   lTarget->SetXYZM(0,0,0,0.938272046);


  //e.g. Make some objects to make branch with, these should be declared in the .h file
 //e.g. fp1=new TLorentzVector();
     //e.g.  fOutTree->Branch("p1",&fp1,buff,split);
  //e.g.  fOutTree->Branch("p1",&fp1,buff,split);
  //if you want kinematic bins you must define fHisbins here
   //fHisbins=new TH*()
   //if(fHisbins) fOutput->Add(fHisbins);
   //fHisbins->SetXTitle();//give useful axis name
   //fHisbins->SetYTitle();//give useful axis name
   THSHisto::ChangeNames();
   THSHisto::LoadCut("Cut_PID_only");
   THSHisto::LoadCut("Cut_pi0_mass");
   THSHisto::LoadCut("Cut_K0Sig_mass");
   THSHisto::LoadCut("Cut_all");
   THSHisto::LoadHistograms();
  // cout<<"Louise0"<<endl;
}

Bool_t Convert::Process(Long64_t entry)
{
   THSOutput::HSProcessStart(entry);
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either Convert::GetEntry() or TBranch::GetEntry()
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

   lProton = new TLorentzVector(1.0,1.0,1.0,1.0);
   lpip = new TLorentzVector(1.0,1.0,1.0,1.0);
   lpim = new TLorentzVector(1.0,1.0,1.0,1.0);
   lpi0 = new TLorentzVector(1.0,1.0,1.0,1.0);
   lSigma = new TLorentzVector(1.0,1.0,1.0,1.0);
   lK0 = new TLorentzVector(1.0,1.0,1.0,1.0);

   *lProton = proton->P4();
   *lpip = pip->P4();
   *lpim = pim->P4();

   *lSigma = (*lTarget + beam->P4()) - (*lpip + *lpim); 
   *lpi0 = (*lTarget + beam->P4()) - (*lProton + *lpip + *lpim); 
   lpi0->SetXYZM(lpi0->Px(), lpi0->Py(), lpi0->Pz(), 0.13498);
   *lK0 = *lpip + *lpim;

   eGamma = beam->P4().E();

   // 4-momentum transfer
   lt = new TLorentzVector(1.0,1.0,1.0,1.0);
   *lt = beam->P4() - *lSigma;
   t = -lt->M2();

   // Masses
   MM_p_pip_pim = ((*lTarget + beam->P4()) - (*lProton + *lpip + *lpim)).M(); 
   M_pip_pim = (*lpip + *lpim).M(); 
   MM_p = ((*lTarget + beam->P4()) - *lProton).M(); 
   MM_pip_pim = ((*lTarget + beam->P4()) - (*lpip + *lpim)).M(); 
   M_p_pi0 = (*lProton + *lpi0).M();

   // Angles
   phiSigma = lSigma->Phi();
   phiK0 = lK0->Phi();
   phiSigmamPhiK0 = TVector2::Phi_0_2pi(lSigma->Phi() - lK0->Phi());

   // cut events with polarisation not in (0,1)
   if (!(pol > 0.0 && pol <= 1.0) && !(isSim)) return false;

   //Int_t kinBin=0;//default to bins defined
   //Int_t kinBin=GetKinBin();//if fHisbins is defined need to give this meaningful arguments
   //EnterKinBinList(kinBin,entry);//save evente in kinematic bins entry lists
   FillHistograms("Cut_PID_only",0);
   bool pi0_massCut = (MM_p_pip_pim > 0.08 && MM_p_pip_pim < 0.25);
   bool K0Sig_massCut = (M_pip_pim > 0.450 && M_pip_pim < 0.550 && MM_pip_pim > 1.150 && MM_pip_pim < 1.250);
   if (pi0_massCut) FillHistograms("Cut_pi0_mass",0);
   if (K0Sig_massCut) FillHistograms("Cut_K0Sig_mass",0);
   if (pi0_massCut && K0Sig_massCut) FillHistograms("Cut_all",0);
   
   if (!(pi0_massCut && K0Sig_massCut)) return false;

   THSOutput::HSProcessFill();

   return kTRUE;
}

void Convert::SlaveTerminate()
{
   cout << "Dividing " << endl;
   //meanPolG->Divide(eventsPolG);
   
   THSOutput::HSSlaveTerminate();
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void Convert::Terminate()
		{
   THSOutput::HSTerminate();
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

}
void Convert::HistogramList(TString sLabel){
  TDirectory::AddDirectory(kFALSE); //do not add to current directory
  //now define all histograms and add to Output
  //label includes kinematic bin and additional cut name
  // e.g fOutput->Add(MapHist(new TH1F("Mp1"+sLabel,"M_{p1}"+sLabel,100,0,2)));

  fOutput->Add(MapHist(new TH1F("meanPolG"+sLabel,"meanPolG"+sLabel,100,1.2,2.2)));
  fOutput->Add(MapHist(new TH1F("eventsPolG"+sLabel,"eventsPolG"+sLabel,100,1.2,2.2)));
  fOutput->Add(MapHist(new TH1F("phiSigma"+sLabel,"phiSigma"+sLabel, 100, -3.2, 3.2)));
  fOutput->Add(MapHist(new TH1F("phiK0"+sLabel,"phiK0"+sLabel, 100, -3.2, 3.2)));
  fOutput->Add(MapHist(new TH1F("hphiSigmamPhiK0"+sLabel,"hphiSigmamPhiK0"+sLabel, 100, -1.0, 1.0)));

  fOutput->Add(MapHist(new TH1F("hMM_p_pip_pim"+sLabel,"hMM_p_pip_pim"+sLabel, 100, 0.0, 2.0)));
  fOutput->Add(MapHist(new TH1F("hM_pip_pim"+sLabel,"hM_pip_pim"+sLabel, 100, 0.0, 2.0)));
  fOutput->Add(MapHist(new TH1F("hMM_p"+sLabel,"hMM_p"+sLabel, 100, 0.0, 2.0)));
  fOutput->Add(MapHist(new TH1F("hMM_pip_pim"+sLabel,"hMM_pip_pim"+sLabel, 100, 0.0, 2.0)));
  fOutput->Add(MapHist(new TH1F("hM_p_pi0"+sLabel,"hM_p_pi0"+sLabel, 100, 0.0, 2.0)));
  fOutput->Add(MapHist(new TH2F("hMM_M_pip_pim"+sLabel,"hMM_M_pip_pim"+sLabel, 100, 0.0, 2.0, 100, 0.0, 2.0)));

  //end of histogram list
  TDirectory::AddDirectory(kTRUE); //back to normal
}
void Convert::FillHistograms(TString sCut,Int_t bin){
  fCurrCut=sCut;
  fCurrBin=bin;
  TString sLabel;
  sLabel=sCut+fVecBinNames[bin];
  //Get histogram from list
  //Fill histogram
   // fill mass hists
   FindHist("hMM_p_pip_pim")->Fill(MM_p_pip_pim);
   FindHist("hM_pip_pim")->Fill(M_pip_pim);
   FindHist("hMM_p")->Fill(MM_p);
   FindHist("hMM_pip_pim")->Fill(MM_pip_pim);
   FindHist("hM_p_pi0")->Fill(M_p_pi0);
   (TH2F*)FindHist("hMM_M_pip_pim")->Fill(M_pip_pim,MM_pip_pim);

   // Fill angle hists
   FindHist("hphiSigmamPhiK0")->Fill(phiSigmamPhiK0);
   if (!(isSim)) {
	 FindHist("meanPolG")->Fill(eGamma, pol);
	 FindHist("eventsPolG")->Fill(eGamma);
	 FindHist("phiSigma")->Fill(phiSigma);
	 FindHist("phiK0")->Fill(phiK0);

	}
}

