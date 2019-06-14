// Run with
// root --hsdata DrawWithWeights.C
{
  Weights* wts=new Weights("TotalWeights");
  wts->Merge("/home/louise/g8K0Sig/code/sWeights3/out_all_pi0K0_binned/Egamma*/Tweights","histWeights.root","HSsWeights");
 
  TChain chain("HSParticles");
  chain.AddFile("/w/work0/home/louise/g8K0Sig/convert_output/filepPi0_all.root");
  Double_t fgID,costhK0CMS, Egamma;
  chain.SetBranchAddress("fgID",&fgID);
  chain.SetBranchAddress("costhK0CMS",&costhK0CMS);
  chain.SetBranchAddress("MM_p_pip_pim",&MM_p_pip_pim);
  chain.SetBranchAddress("M_pip_pim",&M_pip_pim);
  chain.SetBranchAddress("cosX",&cosX);
  chain.SetBranchAddress("cosY",&cosY);
  chain.SetBranchAddress("cosZ",&cosZ);
  
  TH2F* hist=new TH2F("costhK0CMS_Egamma","costhK0CMS_Egamma",50, -1.0, 1.0, 50, 1.1, 2.1);
  Double_t weight=0;
  
  for(Int_t i=0;i<chain.GetEntries();i++){
    chain.GetEntry(i);
    if(wts->GetEntryBinarySearch(fgID)){//find the weight for this event
      hist->Fill(costhK0CMS,Egamma,wts->GetWeight("Signal"));
    }
  }

  TFile* outfile = new TFile("histOut.root","recreate");

  hist->Draw("COLZ");
  hist->Write();
}
