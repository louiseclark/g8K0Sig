void CreateImpWeights2() {

	// t and Egamma
	TH2* weightHist = new TH2F("impWeights","impWeights",100,1.0,2.15, 100,-0.3,2.3);

	// Get the data and sim trees
	TFile *fileData=new TFile("/w/work0/home/louise/g8K0Sig/convert_output3/filepPi0_all.root");
	TTree *treeData= (TTree*) fileData->Get("HSParticles");

	TFile *fileMC=new TFile("/w/work0/home/louise/g8K0Sig/convert_output_MC/filepPi0_all.root");
	TTree *treeMC= (TTree*) fileMC->Get("HSParticles");

	// Create the importance weights
	Weights* impWeights = new Weights("impWeights");
	impWeights->SetSpecies("LikeData");
	impWeights->SetIDName("fgID");
	impWeights->SetFile("out/impWeights_tE.root");
		
	impWeights->ImportanceSampling2(treeMC, treeData, weightHist, "t:Egamma");
	impWeights->PrintWeight();

	//impWeights->Draw1DWithWeights(treeMC,weightHist,"Egamma","LikeData");
	//impWeights->Draw1DWithWeights(treeMC,weightHist,"t","LikeData");
	
	//weightHist->SetLineColor(2);
	//weightHist->Draw("hist");
	
	// t
	//treeData->Draw("t","","same");
	
	// Egamma
	//treeData->Draw("Egamma","","same");
	
	
	impWeights->Save();
}
