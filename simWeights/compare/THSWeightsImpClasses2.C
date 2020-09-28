
////////////////////////////////////////////////////////////
/// LC Jul 2018
/// Importance Sampling
/// Given a data tree and a simulation tree, output the weights required to adjust the simulated distribution 
/// to match the data distribution for the given variable
/// weightHist is a 1D/2D/3D histogram with the axes you require
/// var is the leaf name (separated by : for 2D/3D)
void THSWeights::ImportanceSampling2(TTree* MCTree, TTree* dataTree, TH1* weightHist, TString var) {

  // create sim and data hists based on weightHist (empty hist with appropriate axes and binning)
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
  
  // find the dimension of the histogram and set pointers to the values
  TObjArray *varArr = var.Tokenize(":");
  int dim = varArr->GetEntries();
  Double_t val[3] = {0.0,0.0,0.0};
  //for (int i=0; i < dim; i++) {
	//const char* addr = (*varArr)[i];
    //MCTree->SetBranchAddress(addr,&val[i]);
  //}
  
  varArr->GetEntriesFast();
  TIter varIter(varArr);
  TObjString* varSubstring;
  int i=0;
  while ((varSubstring=(TObjString*)varIter())) {
	 MCTree->SetBranchAddress(varSubstring->GetString().Data(),&val[i]); 
	 i++;
  }
  
  // loop around the MC tree filling weights
  Double_t  wID=0;
  MCTree->SetBranchAddress(fIDName,&wID);
  Int_t nentries = MCTree->GetEntries();
  for (int i=0; i<nentries; i++) {
    MCTree->GetEntry(i);
    if (dim==1) {
		FillWeight(wID, 
	       ratioHist->GetBinContent(ratioHist->GetXaxis()->FindBin(val[0])));	
	}
	else if (dim==2) {
		FillWeight(wID,
		   ratioHist->GetBinContent(ratioHist->GetXaxis()->FindBin(val[0]),
								    ratioHist->GetYaxis()->FindBin(val[1])));
		cout << "val[0] = " << val[0] << " val[1] = " << val[1] << endl;										
    }									
    else if (dim==3) {
		FillWeight(wID,
		   ratioHist->GetBinContent(ratioHist->GetXaxis()->FindBin(val[0]),
								    ratioHist->GetYaxis()->FindBin(val[1]),
								    ratioHist->GetZaxis()->FindBin(val[2])));    
    }								    
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
