void GraphObs() {
	

	TFile *infile = TFile::Open("/home/louise/g8K0Sig/code/toyMC/out1Toy/ResultsAFit.root");
	TTree *MCMCTree = (TTree*)infile->Get("MCMCTree");
	
	string vars[5] = {"B","Ox","R","T","Oz"};
	TCanvas *can = new TCanvas("can","can",800,600);
	int n = MCMCTree->GetEntries();
	
	for (int i=0; i<5; i++) {
		for (int j=0; j<5; j++) {
			
			if (i<=j) {
				// draw the hist zoomed in
				TH2F* histz = new TH2F("histz","",
							 100,MCMCTree->GetMinimum(vars[i].c_str()),MCMCTree->GetMaximum(vars[i].c_str()),
							 100,MCMCTree->GetMinimum(vars[j].c_str()),MCMCTree->GetMaximum(vars[j].c_str()));
				string drawText = vars[j] +":"+ vars[i] + ">>histz";
				MCMCTree->Draw(drawText.c_str());
				histz->GetXaxis()->SetTitle(vars[i].c_str());
				histz->GetYaxis()->SetTitle(vars[j].c_str());
				histz->SetStats(kFALSE);
				histz->Draw("colz");
				string fileName = vars[j]+"_vs_"+vars[i]+"z.png";
				can->SaveAs(fileName.c_str());
				histz->Delete();

				// draw the hist -1 to 1
				TH2F* hist = new TH2F("hist","",
							 100,-1.0,1.0,
							 100,-1.0,1.0);
				drawText = vars[j] +":"+ vars[i] + ">>hist";
				MCMCTree->Draw(drawText.c_str());
				hist->GetXaxis()->SetTitle(vars[i].c_str());
				hist->GetYaxis()->SetTitle(vars[j].c_str());
				hist->SetStats(kFALSE);
				hist->Draw("colz");
				fileName = vars[j]+"_vs_"+vars[i]+".png";
				can->SaveAs(fileName.c_str());
				hist->Delete();

			}
		}
		
		string drawText = vars[i] + ":Entry$";
		MCMCTree->Draw(drawText.c_str(),"Entry$<1000");
		
		TGraph *g = new TGraph(1000, MCMCTree->GetV2(), MCMCTree->GetV1()); // V1 and V2 are determined by previous tree draw
		g->GetHistogram()->SetMinimum(-1.0);
        g->GetHistogram()->SetMaximum(1.0);
		g->Draw();
		string fileName = vars[i] + "_graph.png";
		can->SaveAs(fileName.c_str());
		
		drawText = vars[i] + ":Entry$";
		MCMCTree->Draw(drawText.c_str());
		
		g = new TGraph(n, MCMCTree->GetV2(), MCMCTree->GetV1()); // V1 and V2 are determined by previous tree draw
		g->GetHistogram()->SetMinimum(-1.0);
        g->GetHistogram()->SetMaximum(1.0);
		g->Draw();
		fileName = vars[i] + "_graphAll.png";
		can->SaveAs(fileName.c_str());
		g->Delete();

		
		// draw the posterior zoomed in
		drawText = vars[i];
		MCMCTree->Draw(drawText.c_str());
		fileName = vars[i] + "z.png";
		can->SaveAs(fileName.c_str());
		
		// draw the posterior -1 to 1
		TH1F* hist = new TH1F("hist",vars[i].c_str(),200,-1.0,1.0);
		drawText = vars[i] + ">>hist";
		MCMCTree->Draw(drawText.c_str());
		hist->GetXaxis()->SetTitle(vars[i].c_str());
		fileName = vars[i] + ".png";
		can->SaveAs(fileName.c_str());
		
		hist->Delete();
		
	}
	//TH2F* hist = new TH2F("hist","hist",100,-0.03,0.65,100,-0.03,0.01);
	//MCMCTree->Draw("B:R>>hist","","colz");
	

}

