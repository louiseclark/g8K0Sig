// Run with
// brufit DrawSimWithWeightsSingle.C

void DrawSimWithWeightsSingle() {
  Weights* wts=new Weights("TotalWeights");
  wts->Merge("/home/louise/g8K0Sig/code/simWeights/new/out/impWeights_tE.root","histWeights.root","impWeights");
 
  //TChain chain("HSParticles");
  //chain.AddFile("/w/work0/home/louise/g8K0Sig/convert_output_MC/filepPi0_all.root");

  TFile *mcFile = new TFile("/w/work0/home/louise/g8K0Sig/convert_output_MC/filepPi0_all.root");
  TTree *mcTree = (TTree*)mcFile->Get("HSParticles");


  Double_t fgID,costhK0CMS, Egamma, MM_p_pip_pim, M_pip_pim, MM_pip_pim, MM_p, cosX, cosY, cosZ;
  mcTree->SetBranchAddress("fgID",&fgID);
  mcTree->SetBranchAddress("costhK0CMS",&costhK0CMS);
  mcTree->SetBranchAddress("Egamma",&Egamma);
  mcTree->SetBranchAddress("MM_p_pip_pim",&MM_p_pip_pim);
  mcTree->SetBranchAddress("M_pip_pim",&M_pip_pim);
  mcTree->SetBranchAddress("MM_pip_pim",&MM_pip_pim);
  mcTree->SetBranchAddress("MM_p",&MM_p);
  mcTree->SetBranchAddress("cosX",&cosX);
  mcTree->SetBranchAddress("cosY",&cosY);
  mcTree->SetBranchAddress("cosZ",&cosZ);
  
  TH2F* hist=new TH2F("costhK0CMS_Egamma","costhK0CMS_Egamma",50, -1.0, 1.0, 50, 1.1, 2.1);
  TH1F* h2 = new TH1F("t","t",100,-0.3,2.3);
  
  //for(Int_t i=0;i<chain.GetEntries();i++){
    //chain.GetEntry(i);
    //if(wts->GetEntryBinarySearch(fgID)){//find the weight for this event
      //hist->Fill(costhK0CMS,Egamma,wts->GetWeight("LikeData"));
      //h2->Fill(MM_pip_pim,wts->GetWeight("LikeData"));
    //}
  //}
  
  wts->Draw1DWithWeights(mcTree, h2, "t", "LikeData");

  TFile* outfile = new TFile("out/histOut.root","recreate");

  //hist->Draw("COLZ");
  //hist->Write();
  h2->Draw();
  h2->Write();
}
