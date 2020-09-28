/// LC Jul 2018
/// Importance Sampling
/// Given a data tree and a simulation tree, output the weights required to adjust the simulated distribution 
/// to match the data distribution for the given variable
void THSWeights::ImportanceSampling(TTree* MCTree, TTree* dataTree, TH1* weightHist, TString var) {

  // create sim and data hists based on weightHist (empty hist with appropriate ax	is and binning)
  TH1* mcHist = (TH1*) weightHist->Clone();
  mcHist->SetName("mcHist");
  TH1* dataHist = (TH1*) weightHist->Clone();
  dataHist->SetName("dataHist");
  
  // fill the histograms from the trees with the quantity specified by var parameter
  MCTree->Draw(var+">>mcHist","","goff");
  dataTree->Draw(var+">>dataHist","","goff");
  
  // create hist with ratio of data to MC
  TH1* ratioHist = (TH1*) dataHist->Clone();
  ratioHist->Divide(mcHist);
  
  // loop around the MC tree filling weights
  Double_t  wID=0;
  Double_t val=0;
  MCTree->SetBranchAddress(fIDName,&wID);
  MCTree->SetBranchAddress(var,&val);
  Int_t nentries = MCTree->GetEntries();
  for (int i=0; i<nentries; i++) {
    MCTree->GetEntry(i);
    FillWeight(wID, 
	       ratioHist->GetBinContent( ratioHist->GetXaxis()->FindBin(val)));	
    //  cout << var << " value is " << val << " weight is " << ratioHist->GetBinContent(ratioHist->GetXaxis()->FindBin(val)) << endl;
    
  }
//  cout << "nentries is " << nentries << endl;
	
}

void  THSWeights::Draw1DWithWeights(TTree* tree,TH1* his,TString var,TString species){
  TLeaf *leafVar=tree->GetLeaf(var);
  TLeaf *leafID=tree->GetLeaf(fIDName);
  Int_t ispecies=0;
  if(!(species==TString("")))
    ispecies=fSpecies[species];

  for(Int_t i=0;i<tree->GetEntries();i++){
    tree->GetEntry(i);
    
    if(GetEntryBinarySearch(leafID->GetValue())){//find the weight for this event
      his->Fill(leafVar->GetValue(),GetWeight(ispecies));
    }
  }
}
