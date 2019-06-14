// Run with
// root --hsdata DrawWithWeights.C
{
  Weights* wts=new Weights("TotalWeights");
  wts->Merge("/home/louise/g8K0Sig/code/sWeights2/out_all_pi0K0_binned/Tweights","histWeights.root","HSsWeights");
 
  TChain chain("HSParticles");
  chain.AddFile("/w/work0/home/louise/g8K0Sig/convert_output/filepPi0_all.root");
  Double_t fgID,costhK0CMS, Egamma;
  chain.SetBranchAddress("fgID",&fgID);
  chain.SetBranchAddress("costhK0CMS",&costhK0CMS);
  chain.SetBranchAddress("Egamma",&Egamma);
  
  //TH2F* hist=new TH2F("costhK0CMS_Egamma","costhK0CMS_Egamma",6, -1.0, 1.0, 3, 1.1, 2.1);
  TH2F* hist=new TH2F("costhK0CMS_Egamma","costhK0CMS_Egamma",50, -1.0, 1.0, 50, 1.1, 2.1);
  Double_t weight=0;
  
  for(Int_t i=0;i<chain.GetEntries();i++){
    chain.GetEntry(i);
    if(wts->GetEntryBinarySearch(fgID)){//find the weight for this event
      hist->Fill(costhK0CMS,Egamma,wts->GetWeight("Signal"));
    }
  }

  TFile* outfile = new TFile("costhK0CMS_Egamma2.root","recreate");

  hist->Draw("COLZ");
  hist->Write();
}
