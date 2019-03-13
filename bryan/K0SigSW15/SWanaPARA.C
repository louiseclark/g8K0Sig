#define SWanaPARA_cxx
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

#include "SWanaPARA.h"
#include <TH2.h>
#include <TStyle.h>


void SWanaPARA::Begin(TTree * /*tree*/)
{
   THSOutput::HSBegin(fInput,fOutput);
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

void SWanaPARA::SlaveBegin(TTree * /*tree*/)
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
   //If you are creating a HSParticle tree via fStrParticles then do not create a new tree here, just add the extra branches
   fOutTree=new TTree("HSParticles","A tree containing reconstructed particles"); 
  //e.g. Make some objects to make branch with, these should be declared in the .h file 
 //e.g. fp1=new TLorentzVector();
   fOutTree->Branch("Mpipi",&Mpipi,"Mpipi/F");
   fOutTree->Branch("Epipi",&Epipi,"Epipi/F");
   fOutTree->Branch("Phipipi",&Phipipi,"Phipipi/F");
   fOutTree->Branch("Cospipi",&Cospipi,"Cospipi/F");
   fOutTree->Branch("MPpi0",&MPpi0,"MPpi0/F");
   fOutTree->Branch("EPpi0",&EPpi0,"EPpi0/F");
   fOutTree->Branch("CosPpi0",&CosPpi0,"CosPpi0/F");
   fOutTree->Branch("M3pi",&M3pi,"M3pi/F");
   fOutTree->Branch("E3pi",&E3pi,"E3pi/F");
   fOutTree->Branch("Cos3pi",&Cos3pi,"Cos3pi/F");
   fOutTree->Branch("Egamma",&Egamma,"Egamma/F");
   fOutTree->Branch("W",&W,"W/F");

   fOutTree->Branch("INVMPpi0",&INVMPpi0,"INVMPpi0/F");
   fOutTree->Branch("INVEPpi0",&INVEPpi0,"INVEPpi0/F");
   fOutTree->Branch("INVCosPpi0",&INVCosPpi0,"INVCosPpi0/F");

   fOutTree->Branch("LinpolDegree",&LinpolDegree,"LinpolDegree/F");
   fOutTree->Branch("LincohEdge",&LincohEdge,"LincohEdge/D");
   fOutTree->Branch("LinpolPlane",&LinpolPlane,"LinpolPlane/I");
   fOutTree->Branch("LinpolRadiator",&LinpolRadiator,"LinpolRadiator/I");


   //if you want kinematic bins you must define fHisbins here
   //fHisbins=new TH*()
   //if(fHisbins) fOutput->Add(fHisbins);
   //fHisbins->SetXTitle();//give useful axis name
   //fHisbins->SetYTitle();//give useful axis name
   THSHisto::ChangeNames();
   THSHisto::LoadCut("Cut1");
   THSHisto::LoadCut("Cut2");
   THSHisto::LoadCut("Cut3");
   THSHisto::LoadCut("Cut4");
   THSHisto::LoadHistograms();
}

Bool_t SWanaPARA::Process(Long64_t entry)
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
   FillHistograms("Cut1",0);
   if((lppipi->M()>0.08)&&(lppipi->M()<0.25)) FillHistograms("Cut2",0);
   if(((lKzero->M()>0.450)&&(lKzero->M()<0.550))&&((lMissing_Sigma->M()>1.150)&&(lMissing_Sigma->M()<1.250))) FillHistograms("Cut3",0);
  

   lDipim = *lPiminus + *lMissing_Pizero;
   lDipip = *lPiplus + *lMissing_Pizero;

   lW = *lPhoton + *lTarget;

   lCM = *lPhoton + *lTarget;
   boost_cms = lCM.BoostVector();
   
   LinpolDegree = polDegree;
   LincohEdge = cohEdge;
   LinpolPlane = polPlane;
   LinpolRadiator = polRadiator;

   //EnterKinBinList(kinBin,entry);//save evente in kinematic bins entry lists
   
   if((lppipi->M()<0.08)||(lppipi->M()>0.25)) return -1;
   if((lKzero->M()<0.450)||(lKzero->M()>0.550)) return -1;
   if((lMissing_Sigma->M()<1.150)||(lMissing_Sigma->M()>1.250)) return -1;
   if(LinpolRadiator !=2) return -1;
   if(LinpolPlane !=0) return -1;

   FillHistograms("Cut4",0);   

   Egamma = lPhoton->E();

   W = lW.M();

   Mpipi = lKzero->M();
   Epipi = lKzero->E();
   Phipipi = lKzero->Phi();
   if (Phipipi < 0.0000){
     Phipipi = Phipipi + 6.2831853;
   }
   lKzero->Boost(-boost_cms);
   Cospipi = lKzero->CosTheta();
   
   MPpi0 = lMissing_Sigma->M();
   EPpi0 = lMissing_Sigma->E();
   lMissing_Sigma->Boost(-boost_cms);
   CosPpi0 = lMissing_Sigma->CosTheta();

   M3pi = lpipipi->M();
   E3pi = lpipipi->E();
   lpipipi->Boost(-boost_cms);
   Cos3pi = lpipipi->CosTheta();

   INVMPpi0 = lSigma->M();
   INVEPpi0 = lSigma->E();
   lSigma->Boost(-boost_cms);
   INVCosPpi0 = lSigma->CosTheta();
  

   lKzero->Boost(boost_cms);
   lMissing_Sigma->Boost(boost_cms);
   lpipipi->Boost(boost_cms);
   lSigma->Boost(boost_cms);    

   
   THSOutput::HSProcessFill(); 


   return kTRUE;
}

void SWanaPARA::SlaveTerminate()
{
   THSOutput::HSSlaveTerminate();
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void SWanaPARA::Terminate()
{
   THSOutput::HSTerminate();
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

}
void SWanaPARA::HistogramList(TString sLabel){
  TDirectory::AddDirectory(kFALSE); //do not add to currentx directory
  //now define all histograms and add to Output
  //label includes kinematic bin and additional cut name
  // e.g fOutput->Add(MapHist(new TH1F("Mp1"+sLabel,"M_{p1}"+sLabel,100,0,2)));
  fOutput->Add(MapHist(new TH1F("proton"+sLabel,"M_{proton}"+sLabel,100,0,2)));
  fOutput->Add(MapHist(new TH1F("piplus"+sLabel,"M_{piplus}"+sLabel,100,0,2)));
  fOutput->Add(MapHist(new TH1F("piminus"+sLabel,"M_{piminus}"+sLabel,100,0,2)));
  fOutput->Add(MapHist(new TH1F("EGamma"+sLabel,"E_{gamma}"+sLabel,150,0,3)));

  fOutput->Add(MapHist(new TH1F("MMPpipi"+sLabel,"MM_{Ppipi}"+sLabel,100,0,2)));
  fOutput->Add(MapHist(new TH1F("Mpippim"+sLabel,"M_{pi+pi-}"+sLabel,100,0,2)));
  fOutput->Add(MapHist(new TH1F("Mpipipi"+sLabel,"M_{pipipi}"+sLabel,100,0,2)));
  fOutput->Add(MapHist(new TH1F("MPpi0"+sLabel,"M_{Ppi0}"+sLabel,100,0,2)));
  fOutput->Add(MapHist(new TH2F("MpippimvsMMpippim"+sLabel,"M_{pi+pi-} vs MM_{pi+pi-}"+sLabel,100,0,2,100,1,2)));
  fOutput->Add(MapHist(new TH2F("MpippimvsMPpi0"+sLabel,"M_{pi+pi-} vs M_{Ppi0}"+sLabel,100,0,2,100,1,2)));

  fOutput->Add(MapHist(new TH2F("MMPpipivsMpippim"+sLabel,"MM_{Ppi+pi-} vs M_{pi+pi-}"+sLabel,100,0,2,100,0,2)));
  fOutput->Add(MapHist(new TH2F("MEPpipivsMpippim"+sLabel,"ME_{Ppi+pi-} vs M_{pi+pi-}"+sLabel,100,0,2,100,0,4)));
  fOutput->Add(MapHist(new TH2F("MpipipivsMpippim"+sLabel,"M_{pipipi} vs M_{pi+pi-}"+sLabel,100,0,2,100,0,2)));
  fOutput->Add(MapHist(new TH2F("MEPpipivsMpipipi"+sLabel,"ME_{Ppi+pi-} vs M_{pipipi}"+sLabel,100,0,2,100,0,4)));
  fOutput->Add(MapHist(new TH2F("Mpimpi0vsMpippim"+sLabel,"M_{pi-pi0} vs M_{pi+pi-}"+sLabel,100,0,2,100,0,2)));
  fOutput->Add(MapHist(new TH2F("Mpimpi0vsMEPpipi"+sLabel,"M_{pi-pi0} vs ME_{Ppi+pi-}"+sLabel,100,0,4,100,0,2)));
  fOutput->Add(MapHist(new TH2F("Mpippi0vsMpippim"+sLabel,"M_{pi+pi0} vs M_{pi+pi-}"+sLabel,100,0,2,100,0,2)));
  fOutput->Add(MapHist(new TH2F("Mpippi0vsMEPpipi"+sLabel,"M_{pi+pi0} vs ME_{Ppi+pi-}"+sLabel,100,0,4,100,0,2)));


  fOutput->Add(MapHist(new TH1F("Cospipi"+sLabel,"Cos_{pipi}"+sLabel,100,-1,1)));
  fOutput->Add(MapHist(new TH1F("Phipipirad"+sLabel,"Phi_{pipi}rad"+sLabel,100,-3.2,3.2)));
  fOutput->Add(MapHist(new TH1F("Phipipi"+sLabel,"Phi_{pipi}"+sLabel,100,0,360)));
  fOutput->Add(MapHist(new TH1F("CosPpi0"+sLabel,"Cos_{Ppi0}"+sLabel,100,-1,1)));
  fOutput->Add(MapHist(new TH1F("INVCosPpi0"+sLabel,"INVCos_{Ppi0}"+sLabel,100,-1,1)));

  fOutput->Add(MapHist(new TH1F("W"+sLabel,"W"+sLabel,100,1.5,2.5)));
  fOutput->Add(MapHist(new TH2F("WvsCospipi"+sLabel,"WvsCospipi"+sLabel,100,-1,1,100,1.5,2.5)));

  //end of histogram list
  TDirectory::AddDirectory(kTRUE); //back to normal
}
void SWanaPARA::FillHistograms(TString sCut,Int_t bin){
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
  FindHist("EGamma"+sLabel)->Fill(lPhoton->E());
  FindHist("MMPpipi"+sLabel)->Fill(lppipi->M());
  FindHist("Mpippim"+sLabel)->Fill(lKzero->M());
  FindHist("Mpipipi"+sLabel)->Fill(lpipipi->M());
  FindHist("MPpi0"+sLabel)->Fill(lSigma->M());
  ((TH2F*)FindHist("MpippimvsMMpippim"+sLabel))->Fill(lKzero->M(),lMissing_Sigma->M());
  ((TH2F*)FindHist("MpippimvsMPpi0"+sLabel))->Fill(lKzero->M(),lSigma->M());

  ((TH2F*)FindHist("MMPpipivsMpippim"+sLabel))->Fill(lKzero->M(),lppipi->M());
  ((TH2F*)FindHist("MEPpipivsMpippim"+sLabel))->Fill(lKzero->M(),lppipi->E());
  ((TH2F*)FindHist("MpipipivsMpippim"+sLabel))->Fill(lKzero->M(),lpipipi->M());
  ((TH2F*)FindHist("MEPpipivsMpipipi"+sLabel))->Fill(lpipipi->M(),lppipi->E());
  ((TH2F*)FindHist("Mpimpi0vsMpippim"+sLabel))->Fill(lKzero->M(),lDipim.M());
  ((TH2F*)FindHist("Mpippi0vsMpippim"+sLabel))->Fill(lKzero->M(),lDipip.M());
  ((TH2F*)FindHist("Mpimpi0vsMEPpipi"+sLabel))->Fill(lppipi->E(),lDipim.M());
  ((TH2F*)FindHist("Mpippi0vsMEPpipi"+sLabel))->Fill(lppipi->E(),lDipip.M());
  FindHist("Cospipi"+sLabel)->Fill(Cospipi);
  FindHist("Phipipirad"+sLabel)->Fill(Phipipi);
  FindHist("Phipipi"+sLabel)->Fill(Phipipi*TMath::RadToDeg());
  FindHist("CosPpi0"+sLabel)->Fill(CosPpi0);
  FindHist("INVCosPpi0"+sLabel)->Fill(INVCosPpi0);
  
  FindHist("W"+sLabel)->Fill(W);
  ((TH2F*)FindHist("WvsCospipi"+sLabel))->Fill(Cospipi,W);

}
