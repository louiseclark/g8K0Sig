{
  //optional Set input file directory, could be done with --hsin or setenv HSIN
  HSin("/w/work0/home/louise/g8K0Sig/convert_output3/");
  
  //optional set output directory or file.
  //Directory=>1 out file for every in file
  //file=> 1 total output file
  //HSout("out");
  // N.B. only need all files->directory as files have been merged in the convert_output step
  
  HSout("K0pi0_weights/out_Ecosthbins2/hists_all.root");
  
  //Set up the input chain to be analysed,could remove HSin() if you want
  TChain* tree=new TChain("HSParticles","datachain");
  tree->Add(HSin()+"filepPi0_all.root");
  //tree->Add(HSin()+"file_all.root");
  //tree->Add(HSin()+"file_KpKm.root");
  //tree->Add(HSin()+"file_pKm.root");
  //tree->Add(HSin()+"file_pKp.root");
  //tree->Add(HSin()+"file_pKpKm.root");

  //if using proof
  //Give proof destination file (env variables can't be read directly
  if(gProof) {gProof->AddInput(new TNamed("HSOUT",HSout().Data()));tree->SetProof();}


  tree->Process("histogrammer.C++");
  
  //Not actually sure if this is needed or not...
  if(gProof)gProof->ClearData(TProof::kUnregistered | TProof::kForceClear);
}
