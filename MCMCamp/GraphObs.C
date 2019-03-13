void GraphObs() {
	

	TFile *infile = TFile::Open("/home/louise/g8K0Sig/code/MCMCamp/out3/ResultscosthK0CMS0.67_Egamma1.85_.root");
	TTree *MCMCTree = (TTree*)infile->Get("MCMCTree");
	
	TCanvas *can = new TCanvas("can","can",800,600);
	int n = MCMCTree->GetEntries();
	
	string obs[5] = {
		// B 
		"((a1Re*a1Re+a1Im*a1Im)+(a2Re*a2Re+a2Im*a2Im)-(a3Re*a3Re+a3Im*a3Im)-(a4Re*a4Re+a4Im*a4Im))/(sqrt(a1Re*a1Re+a1Im*a1Im+a2Re*a2Re+a2Im*a2Im+a3Re*a3Re+a3Im*a3Im+a4Re*a4Re+a4Im*a4Im))",
		// Ox
		"(2.0*(a1Re*a4Re+a1Im*a4Im+a2Re*a3Re+a2Im*a3Im))/(sqrt(a1Re*a1Re+a1Im*a1Im+a2Re*a2Re+a2Im*a2Im+a3Re*a3Re+a3Im*a3Im+a4Re*a4Re+a4Im*a4Im))",
		// R
		"((a1Re*a1Re+a1Im*a1Im)-(a2Re*a2Re+a2Im*a2Im)+(a3Re*a3Re+a3Im*a3Im)-(a4Re*a4Re+a4Im*a4Im))/(sqrt(a1Re*a1Re+a1Im*a1Im+a2Re*a2Re+a2Im*a2Im+a3Re*a3Re+a3Im*a3Im+a4Re*a4Re+a4Im*a4Im))"
		// T 
		"((a1Re*a1Re+a1Im*a1Im)-(a2Re*a2Re+a2Im*a2Im)-(a3Re*a3Re+a3Im*a3Im)+(a4Re*a4Re+a4Im*a4Im))/(sqrt(a1Re*a1Re+a1Im*a1Im+a2Re*a2Re+a2Im*a2Im+a3Re*a3Re+a3Im*a3Im+a4Re*a4Re+a4Im*a4Im))",
		// Oz
		"(2.0*(a1Im*a4Re-a1Re*a4Im+a2Re*a3Im-a2Im*a3Re))/(sqrt(a1Re*a1Re+a1Im*a1Im+a2Re*a2Re+a2Im*a2Im+a3Re*a3Re+a3Im*a3Im+a4Re*a4Re+a4Im*a4Im))"
		};
	string vars[5] = {"B","Ox","R","T","Oz"};
	
	// r
	MCMCTree->Draw("sqrt(a1Re*a1Re+a1Im*a1Im+a2Re*a2Re+a2Im*a2Im+a3Re*a3Re+a3Im*a3Im+a4Re*a4Re+a4Im*a4Im)");
	// B 
	MCMCTree->Draw("((a1Re*a1Re+a1Im*a1Im)+(a2Re*a2Re+a2Im*a2Im)-(a3Re*a3Re+a3Im*a3Im)-(a4Re*a4Re+a4Im*a4Im))/(sqrt(a1Re*a1Re+a1Im*a1Im+a2Re*a2Re+a2Im*a2Im+a3Re*a3Re+a3Im*a3Im+a4Re*a4Re+a4Im*a4Im))");
	// T 
	MCMCTree->Draw("((a1Re*a1Re+a1Im*a1Im)-(a2Re*a2Re+a2Im*a2Im)-(a3Re*a3Re+a3Im*a3Im)+(a4Re*a4Re+a4Im*a4Im))/(sqrt(a1Re*a1Re+a1Im*a1Im+a2Re*a2Re+a2Im*a2Im+a3Re*a3Re+a3Im*a3Im+a4Re*a4Re+a4Im*a4Im))");
	// Ox
	MCMCTree->Draw("(2.0*(a1Re*a4Re+a1Im*a4Im+a2Re*a3Re+a2Im*a3Im))/(sqrt(a1Re*a1Re+a1Im*a1Im+a2Re*a2Re+a2Im*a2Im+a3Re*a3Re+a3Im*a3Im+a4Re*a4Re+a4Im*a4Im))");
	// Oz
	MCMCTree->Draw("(2.0*(a1Im*a4Re-a1Re*a4Im+a2Re*a3Im-a2Im*a3Re))/(sqrt(a1Re*a1Re+a1Im*a1Im+a2Re*a2Re+a2Im*a2Im+a3Re*a3Re+a3Im*a3Im+a4Re*a4Re+a4Im*a4Im))");
	// R
	MCMCTree->Draw("((a1Re*a1Re+a1Im*a1Im)-(a2Re*a2Re+a2Im*a2Im)+(a3Re*a3Re+a3Im*a3Im)-(a4Re*a4Re+a4Im*a4Im))/(sqrt(a1Re*a1Re+a1Im*a1Im+a2Re*a2Re+a2Im*a2Im+a3Re*a3Re+a3Im*a3Im+a4Re*a4Re+a4Im*a4Im))");

	
	for (int i=0; i<5; i++) {
		for (int j=0; j<5; j++) {
			
			if (i<=j) {
				
				// draw the hist -1 to 1
				TH2F* hist = new TH2F("hist","",
							 100,-1.0,1.0,
							 100,-1.0,1.0);
				string drawText = obs[j] +":"+ obs[i] + ">>hist";
				MCMCTree->Draw(drawText.c_str());
				hist->GetXaxis()->SetTitle(vars[i].c_str());
				hist->GetYaxis()->SetTitle(vars[j].c_str());
				hist->SetStats(kFALSE);
				hist->Draw("colz");
				string fileName = vars[j]+"_vs_"+vars[i]+".png";
				can->SaveAs(fileName.c_str());
				hist->Delete();

			}
		}
		
		string drawText = obs[i] + ":Entry$";
		MCMCTree->Draw(drawText.c_str(),"Entry$<1000");
		
		TGraph *g = new TGraph(1000, MCMCTree->GetV2(), MCMCTree->GetV1()); // V1 and V2 are determined by previous tree draw
		g->GetHistogram()->SetMinimum(-1.0);
        g->GetHistogram()->SetMaximum(1.0);
		g->Draw();
		string fileName = vars[i] + "_graph.png";
		can->SaveAs(fileName.c_str());
		
		drawText = obs[i] + ":Entry$";
		MCMCTree->Draw(drawText.c_str());
		
		g = new TGraph(n, MCMCTree->GetV2(), MCMCTree->GetV1()); // V1 and V2 are determined by previous tree draw
		g->GetHistogram()->SetMinimum(-1.0);
        g->GetHistogram()->SetMaximum(1.0);
		g->Draw();
		fileName = vars[i] + "_graphAll.png";
		can->SaveAs(fileName.c_str());
		g->Delete();

		
		// draw the posterior zoomed in
		drawText = obs[i];
		MCMCTree->Draw(drawText.c_str());
		fileName = vars[i] + "z.png";
		can->SaveAs(fileName.c_str());
		
		// draw the posterior -1 to 1
		TH1F* hist = new TH1F("hist",vars[i].c_str(),200,-1.0,1.0);
		drawText = obs[i] + ">>hist";
		MCMCTree->Draw(drawText.c_str());
		hist->GetXaxis()->SetTitle(vars[i].c_str());
		fileName = vars[i] + ".png";
		can->SaveAs(fileName.c_str());
		
		hist->Delete();
		
	}	

}

