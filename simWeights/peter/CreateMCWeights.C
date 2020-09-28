void CreateMCWeights() {
	TH1* weightHist = new TH1F("impWeights","impWeights",50,0,2);
	
	TFile *fileData=new TFile("/w/work5/home/pauli/Lambda1520/data/spring17_ver20/trees/data_cuts/hs_tree_Lambda1520_all.root");
	TTree *treeData= (TTree*) fileData->Get("haspect");
	
	TFile *fileMC=new TFile("/w/work5/home/pauli/Lambda1520/data/spring17_ver20/trees/sig_cuts/hs_tree_Lambda1520_realbeam.root");
	TTree *treeMC= (TTree*) fileMC->Get("haspect");
	
	Weights* sWeights = new Weights("sweights");
	sWeights->LoadSaved("/w/work5/home/pauli/Lambda1520/data/spring17_ver20/outsPlot_cheb2_nomultcombos_tmin_realbeam/Tweights.root","HSsWeights");
	sWeights->PrintWeight();
	
	Weights* MCSidebandWeights = new Weights("mcsideband");
	MCSidebandWeights->LoadSaved("/w/work5/home/pauli/Lambda1520/data/spring17_ver20/outsPlot_cheb2_nomultcombos_tmin_realbeam/SideBandSig.root","RndTime");
	MCSidebandWeights->PrintWeight();
	
	Weights* impWeights = new Weights("impWeights");
	impWeights->SetSpecies("LikeData");
	impWeights->SetIDName("uniqueComboID");
	impWeights->SetFile("impWeights.root");
	
	impWeights->ImportanceSampling(treeMC, treeData, weightHist, "momentumTransferMinustmin",MCSidebandWeights,"SideBand",sWeights,"Sig");
	impWeights->PrintWeight();
	
	impWeights->Draw1DWithWeights(treeMC,weightHist,"momentumTransferMinustmin","LikeData");
	
	weightHist->SetLineColor(2);
	weightHist->Draw("hist");
	TH1F* dataHist = (TH1F*)weightHist->Clone("data");
	dataHist->Reset();
	sWeights->Draw1DWithWeights(treeData,dataHist,"momentumTransferMinustmin","Sig");
	dataHist->SetLineColor(1);
	dataHist->Draw("same");
	
	impWeights->Save();
}
