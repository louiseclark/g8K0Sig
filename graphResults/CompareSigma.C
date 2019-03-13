void CompareSigma() {
	
	// input file for cos2phi binned beam asymmetry values
	TFile *infile = TFile::Open("/home/louise/g8K0Sig/code/analyseBeamAsym/out/analyse_Ecosth.root");
	TFile* outfile = new TFile("CompareSigma.root","recreate");	

	TCanvas* c1 = new TCanvas();

	// graphs for beam asymmetry
	TGraphErrors* beamGraphE[] = {new TGraphErrors(0), new TGraphErrors(0), new TGraphErrors(0)};
	TGraphErrors* beamGraphth[] = {new TGraphErrors(0), new TGraphErrors(0)};

	TMultiGraph*  beamE = new TMultiGraph();
	TMultiGraph*  beamth = new TMultiGraph();
	TLegend* leg = new TLegend(0.5,0.7,0.88,0.9); // x1,y1,x2,y2
	
	//beamE->SetMarkerStyle(24);
	//beamE->SetMarkerColor(4);
	//beamE->SetMarkerSize(1.6);
	//beamth->SetMarkerStyle(24);
	//beamth->SetMarkerColor(4);
	//beamth->SetMarkerSize(1.6);
	
	std::string ebinName = "Ebins";
	std::string tbinName = "costhbins";
	
	int mkStyles[] = {24, 28, 32};
	int mkColors[] = {4, 6, 8};
	int ebinIdx = 0;
	int tbinIdx = 0;

	// Get the cos2phi binned beam asymmetry values
	string dirs[3] = {"Signal", "BG", "All"};
				
	TDirectory *weightsDir = infile->GetDirectory(dirs[0].c_str());	
	TIter	nextTbinDir(weightsDir->GetListOfKeys());
	TKey 	*tbinKey;

	while ((tbinKey=(TKey*)nextTbinDir())) {

		TDirectory *tbinDir = weightsDir->GetDirectory(tbinKey->GetName());
		TIter	nextEbinDir(tbinDir->GetListOfKeys());
		TKey 	*ebinKey;
		
		beamGraphE[tbinIdx]->SetName(tbinKey->GetName());
		
		leg->AddEntry(tbinKey->GetName(),tbinKey->GetName());
		beamE->Add(beamGraphE[tbinIdx]);
		cout << "leg " << tbinKey->GetName();
				
		ebinIdx = 0;
		while ((ebinKey=(TKey*)nextEbinDir())) {
						
			TDirectory *ebinDir = tbinDir->GetDirectory(ebinKey->GetName());
			TIter	nextHist(ebinDir->GetListOfKeys());
			TKey	*histKey;
			
			if (tbinIdx==0) {
				beamGraphth[ebinIdx]->SetName(ebinKey->GetName());
				beamth->Add(beamGraphth[ebinIdx]);
			}

			histKey=(TKey*)nextHist();
			TH1F* hist = (TH1F*) histKey->ReadObj();
			float fitAmp = hist->GetFunction("cos2phiSig")->GetParameter(1) / -0.7;
			float fitAmpErr = hist->GetFunction("cos2phiSig")->GetParError(1);
			
			// add value to E graph			
			std::string ebinText = ebinKey->GetName();
			ebinText.replace(ebinText.find(ebinName), ebinName.length(), "");
			ebinText.replace(ebinText.find("_"), 1, "");
			Double_t ebinD = std::stod(ebinText);
			
			Int_t Npoint=beamGraphE[tbinIdx]->GetN();
			beamGraphE[tbinIdx]->SetMarkerStyle(mkStyles[tbinIdx]);
			beamGraphE[tbinIdx]->SetMarkerSize(1.2);
			beamGraphE[tbinIdx]->SetFillColor(0);
			beamGraphE[tbinIdx]->SetPoint(Npoint,ebinD,fitAmp);
			beamGraphE[tbinIdx]->SetPointError(Npoint,0.0,fitAmpErr);
			beamGraphE[tbinIdx]->Draw("P");
			
			// add value to costh graph			
			std::string tbinText = tbinKey->GetName();
			tbinText.replace(tbinText.find(tbinName), tbinName.length(), "");
			tbinText.replace(tbinText.find("_"), 1, "");
			Double_t tbinD = std::stod(tbinText);
			
			Npoint=beamGraphth[ebinIdx]->GetN();
			beamGraphth[ebinIdx]->SetMarkerStyle(mkStyles[ebinIdx]);
			beamGraphth[ebinIdx]->SetMarkerSize(1.2);
			beamGraphth[ebinIdx]->SetFillColor(0);
			beamGraphth[ebinIdx]->SetPoint(Npoint,tbinD,fitAmp);		
			beamGraphth[ebinIdx]->SetPointError(Npoint,0.0,fitAmpErr);
			beamGraphth[ebinIdx]->Draw("P");

			cout << tbinKey->GetName() << " " << tbinText << " " << tbinIdx << " " << ebinKey->GetName() << " " << ebinText << " " << ebinIdx << " " << fitAmp << " +/- " << fitAmpErr << endl;
					
			ebinIdx++;		
		}
		tbinIdx++;
	}

	// Add values from Bonn paper
	const Int_t n = 3;
    Float_t x[n]  = {1.15,1.35,1.55};
    Float_t y[n]  = {0.12,-0.08,-0.16};
    Float_t ex[n] = {0.0,0.0,0.0};
    Float_t ey[n] = {0.08,0.08,0.14};
    TGraphErrors *Eg1 = new TGraphErrors(n,x,y,ex,ey);
    Eg1->SetName("Bonn_costh=-0.8");
    Eg1->SetMarkerColor(4);
    Eg1->SetMarkerStyle(21);
    Eg1->SetFillColor(0);
    TLine *line = new TLine(1.1,0.0,2.1,0.0);
	line->SetLineStyle(3);
	line->Draw();
	Eg1->Draw("P");	
    beamE->Add(Eg1);
    
    Float_t y2[n]  = {-0.14,0.0,0.5};
    Float_t ey2[n] = {0.1,0.12,0.2};
    TGraphErrors *Eg2 = new TGraphErrors(n,x,y2,ex,ey2);
    Eg2->SetName("Bonn_costh=-0.4");
    Eg2->SetMarkerColor(6);
    Eg2->SetMarkerStyle(21);
    Eg2->SetFillColor(0);
    Eg2->Draw("P");	
    beamE->Add(Eg2);
    
    Float_t y3[n]  = {-0.34,-0.16,0.62};
    Float_t ey3[n] = {0.1,0.14,0.2};
    TGraphErrors *Eg3 = new TGraphErrors(n,x,y3,ex,ey3);
    Eg3->SetName("Bonn_costh=0.0");
    Eg3->SetMarkerColor(8);
    Eg3->SetMarkerStyle(21);
    Eg3->SetFillColor(0);
    Eg3->Draw("P");	
    beamE->Add(Eg3);
    
    Float_t y4[n]  = {-0.14,0.16,-0.1};
    Float_t ey4[n] = {0.1,0.14,0.2};
    TGraphErrors *Eg4 = new TGraphErrors(n,x,y4,ex,ey4);
    Eg4->SetName("Bonn_costh=0.4");
    Eg4->SetMarkerColor(12);
    Eg4->SetMarkerStyle(21);
    Eg4->SetFillColor(0);
    Eg4->Draw("P");	
    beamE->Add(Eg4);
    
    Float_t y5[n]  = {0.02,0.08,-0.7};
    Float_t ey5[n] = {0.08,0.08,0.15};
    TGraphErrors *Eg5 = new TGraphErrors(n,x,y5,ex,ey5);
    Eg5->SetName("Bonn_costh=0.8");
    Eg5->SetMarkerColor(14);
    Eg5->SetMarkerStyle(21);
    Eg5->SetFillColor(0);
    Eg5->Draw("P");	
    beamE->Add(Eg5);
    
	beamE->Draw("AP");
	beamE->GetXaxis()->SetTitle("E_{#gamma} (GeV)");
	beamE->GetYaxis()->SetTitle("#Sigma");
	
	TLegend* leg2 = new TLegend(0.6,0.2,0.78,0.45); // x1,y1,x2,y2
	leg2->AddEntry(beamGraphE[0]->GetName(),beamGraphE[0]->GetName());
	leg2->AddEntry(beamGraphE[1]->GetName(),beamGraphE[1]->GetName());
	leg2->AddEntry(beamGraphE[2]->GetName(),beamGraphE[2]->GetName());
	leg2->AddEntry("Bonn_costh=-0.8","Bonn_costh=-0.8");
	leg2->AddEntry("Bonn_costh=-0.4","Bonn_costh=-0.4");
	leg2->AddEntry("Bonn_costh=0.0","Bonn_costh=0.0");
	leg2->AddEntry("Bonn_costh=0.4","Bonn_costh=0.4");
	leg2->AddEntry("Bonn_costh=0.8","Bonn_costh=0.8");
	leg2->Draw();
	
	
	c1->SaveAs("beamGraphE.png");
	
	c1->Clear();
	
	// Add values from Bonn paper
	const Int_t n2 = 5;
    Float_t tx[n2]  = {-0.8,-0.4,0.0,0.4,0.8};
    Float_t tex[n2]  = {0.0,0.0,0.0,0.0,0.0};
    Float_t ty1[n2]  = {0.12,-0.14,-0.34,-0.14,0.02};
    Float_t tey1[n2] = {0.08,0.1,0.1,0.1,0.08};
    TGraphErrors *tg1 = new TGraphErrors(n2,tx,ty1,tex,tey1);
    tg1->SetName("Bonn_Eg=1.15GeV");
    tg1->SetMarkerColor(4);
    tg1->SetMarkerStyle(21);
    tg1->SetFillColor(0);
    tg1->Draw("P");	
    beamth->Add(tg1);
    
    Float_t ty2[n2]  = {-0.08,0.0,-0.16,0.16,0.08};
    Float_t tey2[n2] = {0.08,0.12,0.14,0.14,0.08};
    TGraphErrors *tg2 = new TGraphErrors(n2,tx,ty2,tex,tey2);
    tg2->SetName("Bonn_Eg=1.35GeV");
    tg2->SetMarkerColor(6);
    tg2->SetMarkerStyle(21);
    tg2->SetFillColor(0);
    tg2->Draw("P");	
    beamth->Add(tg2);
    
    Float_t ty3[n2]  = {-0.16,0.5,0.62,-0.1,-0.7};
    Float_t tey3[n2] = {0.14,0.2,0.2,0.2,0.15};
    TGraphErrors *tg3 = new TGraphErrors(n2,tx,ty3,tex,tey3);
    tg3->SetName("Bonn_Eg=1.55GeV");
    tg3->SetMarkerColor(8);
    tg3->SetMarkerStyle(21);
    tg3->SetFillColor(0);
    tg3->Draw("P");	
    beamth->Add(tg3);
    	
	beamth->Draw("AP");
	beamth->GetXaxis()->SetTitle("cos #theta_{K0,cms}");
	beamth->GetYaxis()->SetTitle("#Sigma");
	TLegend* leg3 = new TLegend(0.6,0.7,0.85,0.95); // x1,y1,x2,y2
	leg3->AddEntry(beamGraphth[0]->GetName(),beamGraphth[0]->GetName());
	leg3->AddEntry(beamGraphth[1]->GetName(),beamGraphth[1]->GetName());
	leg3->AddEntry("Bonn_Eg=1.15GeV","Bonn_Eg=1.15GeV");
	leg3->AddEntry("Bonn_Eg=1.35GeV","Bonn_Eg=1.35GeV");
	leg3->AddEntry("Bonn_Eg=1.55GeV","Bonn_Eg=1.55GeV");
	leg3->Draw();
	
	c1->SaveAs("beamGraphth.png");
	
	beamE->SetName("beamGraphE");
	beamE->Write();
	beamth->SetName("beamGraphth");
	beamth->Write();

	outfile->Close();

}

