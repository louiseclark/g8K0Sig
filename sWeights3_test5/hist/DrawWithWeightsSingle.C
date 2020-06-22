// Run with
// root --hsdata DrawWithWeights.C

TString getHistForBin() {

  // Variable bins Egamma 1.1-1.35
  //Double_t binLimits[] = {-1.0, -0.622, -0.39, -0.146, 0.054, 0.298, 1.0};
  //RF.Bins().LoadBinVar("costhK0CMS",6,binLimits);
  //RF.Bins().LoadBinVar("Egamma",1, 1.1, 1.35);

  // Variable bins Egamma 1.35-1.6
  //Double_t binLimits[] = {-1.0, -0.465, -0.275, -0.135, 0.005, 0.165, 0.345, 0.535, 1.0}; // 0.785
  //RF.Bins().LoadBinVar("costhK0CMS",8,binLimits);
  //RF.Bins().LoadBinVar("Egamma",1, 1.35, 1.6);
  
  // Variable bins Egamma 1.6-1.85
  //Double_t binLimits[] = {-1.0, -0.175, 0.035, 0.295, 0.505, 1.0}; // 0.835
  //RF.Bins().LoadBinVar("costhK0CMS",5,binLimits);
  //RF.Bins().LoadBinVar("Egamma",1, 1.6, 1.85);  

  // Variable bins Egamma 1.85-2.1
  //Double_t binLimits[] = {-1.0, 0.155, 1.0}; // 0.775
  //RF.Bins().LoadBinVar("costhK0CMS",2,binLimits);
  //RF.Bins().LoadBinVar("Egamma",1, 1.85, 2.1); 
  
  
  
							
}

void DrawWithWeights() {
  Weights* wts=new Weights("TotalWeights");
  wts->Merge("/home/louise/g8K0Sig/code/sWeights3/out_all_pi0K0_binned/Egamma1.23/Tweights.root","histWeights.root","HSsWeights");
 
  TChain chain("HSParticles");
  chain.AddFile("/w/work0/home/louise/g8K0Sig/convert_output3/filepPi0_all.root");
  Double_t fgID,costhK0CMS, Egamma, MM_p_pip_pim, M_pip_pim, MM_pip_pim, MM_p, cosX, cosY, cosZ;
  chain.SetBranchAddress("fgID",&fgID);
  chain.SetBranchAddress("costhK0CMS",&costhK0CMS);
  chain.SetBranchAddress("Egamma",&Egamma);
  chain.SetBranchAddress("MM_p_pip_pim",&MM_p_pip_pim);
  chain.SetBranchAddress("M_pip_pim",&M_pip_pim);
  chain.SetBranchAddress("MM_pip_pim",&MM_pip_pim);
  chain.SetBranchAddress("MM_p",&MM_p);
  chain.SetBranchAddress("cosX",&cosX);
  chain.SetBranchAddress("cosY",&cosY);
  chain.SetBranchAddress("cosZ",&cosZ);
  
  TH2F* hist=new TH2F("costhK0CMS_Egamma","costhK0CMS_Egamma",50, -1.0, 1.0, 50, 1.1, 2.1);
  TH1F* h2 = new TH1F("MM_pip_pim","MM_pip_pim",100,0.8,1.5);
  Double_t weight=0;
  
  for(Int_t i=0;i<chain.GetEntries();i++){
    chain.GetEntry(i);
    if(wts->GetEntryBinarySearch(fgID)){//find the weight for this event
	  //cout << "Filling" << MM_pip_pim << " " << Egamma << " " << wts->GetWeight("Signal") << endl;
      hist->Fill(costhK0CMS,Egamma,wts->GetWeight("Signal"));
      h2->Fill(MM_pip_pim,wts->GetWeight("Signal"));
    }
  }

  TFile* outfile = new TFile("histOut.root","recreate");

  hist->Draw("COLZ");
  hist->Write();
  h2->Draw();
  h2->Write();
}
