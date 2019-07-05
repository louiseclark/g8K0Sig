void GetRootbeerPlots() {
	
	TString indir = "/w/work0/home/louise/rootbeer_output/g8K0Sig/";
	TString insubdir[] = {"1_3","1_5","1_7","1_9","2_1"};
	TString outdir = "/home/louise/g8K0Sig/AnalysisSummary/html/images/rootbeer/";
	TCanvas* c1=new TCanvas("c1","c1",800,600); // default canvas
	TCanvas* c2=new TCanvas("c2","c2",800,600); // mean pol canvas
	
	TString bMomPlots[] = {"h0_betamomp","h0_betamomm","h1_betamomp","h1_betamomm","h4_betamomp"};
	TString bMomTitles[] = {"Initial skim (+ve)","Initial skim (-ve)","After mass cuts (+ve)","After mass cuts (-ve)","All cuts applied (+ve)"};
	
	TString vzPlots[] = {"h0_zp","h0_zm","h1_zProton","h1_zPip"};
	TString vzTitles[] = {"Initial skim (+ve)","Initial skim (-ve)","After mass cuts and vertex z cut"};
	
	TString multPlots[] = {"h1_multiplicity","h4_multiplicity"};
	TString multTitles[] = {"After mass cuts","All cuts applied"};
	
	TString elossPlots[] = {"h1_elossp","h1_elossp_mom","h1_elosspip","h1_elosspip_mom","h1_elosspim","h1_elosspim_mom"};
	
	TString timeDiffPlots[] = {"h2_allPhotonTimeDiff","h2_bestPhotonTimeDiff","h3_bestPhotonTimeDiff"};
	TString timeDiffTitles[] = {"After mass cuts", "After best photon cut", "After vertex time cut"};
	
	TString ePlots[] = {"h2_photonEnergy","h2_bestPhotonEnergy","h3_bestPhotonEnergy","h4_photonEnergy"};
	TString eTitles[] = {"After mass cuts","After best photon cut","After vertex time cut","After polarization cut"};
	
	// event counts
	int countInitSkim = 0; // i.e. 3 or 4 particles in final state
	int countMassVz = 0; // after vertex z and mass cuts
	int countVt = 0; // after best photon vertex time cut
	int countPol = 0; // after polarization cut
	
	// text file for event counts
	ofstream outfile;
    outfile.open("/home/louise/g8K0Sig/AnalysisSummary/html/counts.txt");
	
	for (int i=0; i < 5; i++) {
		
		// Open each file for each coherent edge
		TString filename = indir+insubdir[i]+"/"+insubdir[i]+"_list.root";
		TFile* infile = TFile::Open(filename);
		c1->cd(0); // set default canvas
		
		// increment event counts
		TH1F* initHist = (TH1F*)infile->Get("h0_zm"); // approximate initial skim events = num -ve
		countInitSkim = countInitSkim + initHist->GetEntries();
		
		TH1F* massVzHist = (TH1F*)infile->Get("h1_zProton"); // vz plot after vz cut and mass cuts
		countMassVz = countMassVz + massVzHist->GetEntries();
		
		TH1F* vtHist = (TH1F*)infile->Get("h3_bestPhotonTimeDiff"); // after best photon time diff cut
		countVt = countVt + vtHist->GetEntries();
		
		TH1F* polHist = (TH1F*)infile->Get("h4_photonEnergy"); // after polarization cut
		countPol = countPol + polHist->GetEntries();		
		
		// Create beta momentum plots
		for (int j=0; j<5; j++) {
			TH2F* bMomHist = (TH2F*)infile->Get(bMomPlots[j]);
			bMomHist->GetXaxis()->SetRange(0,bMomHist->GetXaxis()->FindBin(2.3));
			bMomHist->GetYaxis()->SetRange(0,bMomHist->GetYaxis()->FindBin(1.0));
			bMomHist->SetTitle(bMomTitles[j]);
			bMomHist->GetXaxis()->SetTitle("p (GeV)");
			bMomHist->GetYaxis()->SetTitle("#beta");
			bMomHist->Draw("COLZ");

			TPaveStats *st=(TPaveStats*)bMomHist->FindObject("stats");
			c1->Modified();
			c1->Update();
			st->SetX1NDC(0.7);
			st->SetX2NDC(0.9);
			st->SetY1NDC(0.85);         
			st->SetY2NDC(0.9);
			gStyle->SetOptStat(10);

			TString outFilename = outdir+insubdir[i]+"/"+bMomPlots[j]+".png";
			c1->SaveAs(outFilename);
			
		}
		
		// vertex z plots
		for (int j=0; j<3; j++) {
			TH1F* vzHist = (TH1F*)infile->Get(vzPlots[j]);
			vzHist->GetXaxis()->SetRange(vzHist->GetXaxis()->FindBin(-90.0),vzHist->GetXaxis()->FindBin(50.0));
			vzHist->SetTitle(vzTitles[j]);
			vzHist->GetXaxis()->SetTitle("Vertex z (cm)");
			vzHist->Draw();

			TPaveStats *st=(TPaveStats*)vzHist->FindObject("stats");
			c1->Modified();
			c1->Update();
			st->SetX1NDC(0.7);
			st->SetX2NDC(0.9);
			st->SetY1NDC(0.85);         
			st->SetY2NDC(0.9);
			gStyle->SetOptStat(10);

			TString outFilename = outdir+insubdir[i]+"/"+vzPlots[j]+".png";
			c1->SaveAs(outFilename);
		}	
		
		// multiplicity plots
		for (int j=0; j<2; j++) {
			TH1F* hist = (TH1F*)infile->Get(multPlots[j]);
			hist->SetTitle(multTitles[j]);
			hist->GetXaxis()->SetTitle("Number of particles per event");
			hist->GetXaxis()->SetNdivisions(5);
			hist->Draw();

			TPaveStats *st=(TPaveStats*)hist->FindObject("stats");
			c1->Modified();
			c1->Update();
			st->SetX1NDC(0.7);
			st->SetX2NDC(0.9);
			st->SetY1NDC(0.85);         
			st->SetY2NDC(0.9);
			gStyle->SetOptStat(10);

			TString outFilename = outdir+insubdir[i]+"/"+multPlots[j]+".png";
			c1->SaveAs(outFilename);
		}
		
		// Create eloss plots
		for (int j=0; j<6; j++) {
			TH2F* hist = (TH2F*)infile->Get(elossPlots[j]);
			hist->Draw("COLZ");

			TPaveStats *st=(TPaveStats*)hist->FindObject("stats");
			c1->Modified();
			c1->Update();
			st->SetX1NDC(0.7);
			st->SetX2NDC(0.9);
			st->SetY1NDC(0.85);         
			st->SetY2NDC(0.9);
			gStyle->SetOptStat(10);

			TString outFilename = outdir+insubdir[i]+"/"+elossPlots[j]+".png";
			c1->SaveAs(outFilename);
		}
		
		// time diff plots
		for (int j=0; j<3; j++) {
			TH1F* hist = (TH1F*)infile->Get(timeDiffPlots[j]);
			hist->SetTitle(timeDiffTitles[j]);
			hist->GetXaxis()->SetRange(hist->GetXaxis()->FindBin(-10.0),hist->GetXaxis()->FindBin(10.0));
			hist->SetTitle(timeDiffTitles[j]);
			hist->GetXaxis()->SetTitle("Vertex time difference (ns)");
			hist->Draw();

			TPaveStats *st=(TPaveStats*)hist->FindObject("stats");
			c1->Modified();
			c1->Update();
			st->SetX1NDC(0.7);
			st->SetX2NDC(0.9);
			st->SetY1NDC(0.85);         
			st->SetY2NDC(0.9);
			gStyle->SetOptStat(10);

			TString outFilename = outdir+insubdir[i]+"/"+timeDiffPlots[j]+".png";
			c1->SaveAs(outFilename);
		}		
		
		// photon energy plots
		for (int j=0; j<4; j++) {
			TH1F* hist = (TH1F*)infile->Get(ePlots[j]);
			hist->Rebin(8);
			hist->SetTitle(eTitles[j]);
			//hist->GetXaxis()->SetRange(hist->GetXaxis()->FindBin(0.5),hist->GetXaxis()->FindBin(3.0));
			hist->SetTitle(eTitles[j]);
			hist->GetXaxis()->SetTitle("Photon Energy (GeV)");
			hist->Draw();

			if (j!=3) { // something funny with the stat box in the last histogram
				TPaveStats *st=(TPaveStats*)hist->FindObject("stats");
				c1->Modified();
				c1->Update();
				st->SetX1NDC(0.7);
				st->SetX2NDC(0.9);
				st->SetY1NDC(0.85);         
				st->SetY2NDC(0.9);
				gStyle->SetOptStat(10);
			}

			TString outFilename = outdir+insubdir[i]+"/"+ePlots[j]+".png";
			c1->SaveAs(outFilename);
		}	
		
		// mean polarization plots
		TH1F* paraHist = (TH1F*)infile->Get("meanPolGPARA");		
		TH1F* perpHist = (TH1F*)infile->Get("meanPolGPERP");		
		
		paraHist->SetTitle("");
		paraHist->GetXaxis()->SetRange(paraHist->GetXaxis()->FindBin(1.0),paraHist->GetXaxis()->FindBin(2.2));
		paraHist->GetXaxis()->SetTitle("Photon Energy (GeV)");
		paraHist->GetYaxis()->SetTitle("Polarization degree");
		paraHist->SetLineColor(kBlue);
		paraHist->Draw();
		perpHist->SetLineColor(kRed);
		perpHist->Draw("same");
		
		TLegend* leg = new TLegend(0.8,0.2,0.9,0.3);
		leg->AddEntry(paraHist,"PARA");
		leg->AddEntry(perpHist, "PERP");
		leg->Draw();

		TString outFilename = outdir+insubdir[i]+"/meanpol.png";
		c1->SaveAs(outFilename);
		
		// Draw all plots on to mean pol canvas
		c2->cd(0);
		paraHist->Draw("same");
		perpHist->Draw("same");
		leg->Draw();
		
	}
	
	c2->SaveAs(outdir+"meanpol.png");
	
	// output counts
	outfile << "After 3 or 4 particles in final state " << countInitSkim << endl;
	outfile << "After vertex z and mass cuts " << countMassVz << endl;
	outfile << "After best photon vertex time cut " << countVt << endl;
	outfile << "After polarization cut " << countPol << endl;
	outfile.close();
	
}	

