TH1* weightHist = new TH1F("impWeights","impWeights",50,1.5,2.1);

void CreateImpWeights() {

	// Get the data and sim trees
	TFile *fileData=new TFile("/home/louise/g8_phi/haspect/Events/Projects/g8phi/convert_output/file_all.root");
	TTree *treeData= (TTree*) fileData->Get("HSParticles");
	
	TFile *fileMC=new TFile("/home/louise/g8_phi/haspect/Events/Projects/g8phi/convert_output_MC10M/file_all.root");
	TTree *treeMC= (TTree*) fileMC->Get("HSParticles");

	// Create the importance weights
	THSWeights* impWeights = new THSWeights("impWeights");
	impWeights->SetSpecies("LikeData");
	impWeights->SetIDName("fgID");
	impWeights->SetFile("impWeights.root");
	
	// t
	//TH1* weightHist = new TH1F("impWeights","impWeights",100,0.0,2.0);
	//impWeights->ImportanceSampling(treeMC, treeData, weightHist, "t");

	// Egamma
	impWeights->ImportanceSampling(treeMC, treeData, weightHist, "Egamma");
	impWeights->PrintWeight();

	impWeights->Draw1DWithWeights(treeMC,weightHist,"Egamma");
	
	weightHist->SetLineColor(2);
	weightHist->Draw("hist");
	treeData->Draw("Egamma","","same");
	//impWeights->Save();
}
