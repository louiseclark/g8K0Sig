{
  Weights* wts=new Weights("TotalWeights");
  wts->Merge("/home/louise/g8K0Sig/code/sWeights2/out_all_pi0K0_binned/Tweights","out1/histWeights.root","HSsWeights");
 
  TFile* file=new TFile("/w/work0/home/louise/g8K0Sig/convert_output/filepPi0_all.root");
  auto tree=(TTree*)file->Get("HSParticles");  
  wts->AddToTree(tree);
  
  tree->Draw("costhK0CMS_Egamma>>h_costhK0CMS_Egamma(100,-1,1)","Signal");

}
