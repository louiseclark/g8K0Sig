void GetConvertPlots3() {
	
	TString inFileName = "/w/work0/home/louise/g8K0Sig/convert_output3/filepPi0_all.root";
	TFile* infile = TFile::Open(inFileName);
	TTree* tree = (TTree*)infile->Get("HSParticles");
	
	TString outdir = "/home/louise/g8K0Sig/AnalysisSummary/html/images/convert3/";
	TCanvas* c1=new TCanvas("c1","c1",800,600); // default canvas
	c1->cd(0); // set default canvas
	
	// NEXT
	// use convert_output3 and change to z% hists
	// redo weights / fits with convert_output3 as systematic check
	
	
	TString pi0Plots[] = {"hMM_p_pip_pimCut_PID_only_All","hMM_p_pip_pimCut_pi0_mass_All","hMM_p_pip_pimCut_K0Sig_mass_All", "hMM_p_pip_pimCut_all_All", // cuts
						  "hMM_p_pip_pimCut_not_all_All", "hMM_p_pip_pim_zCut_not_all_All"}; // anti cut
	TString K0Plots[] = {"hM_pip_pimCut_PID_only_All","hM_pip_pimCut_pi0_mass_All","hM_pip_pimCut_K0Sig_mass_All", "hM_pip_pimCut_all_All", // cuts
						  "hM_pip_pimCut_not_all_All","hM_pip_pim_zCut_not_all_All"}; // anti cut
	TString pi3Plots[] = {"hMM_pCut_PID_only_All","hMM_pCut_pi0_mass_All","hMM_pCut_K0Sig_mass_All", "hMM_pCut_all_All", // cuts
						  "hMM_pCut_not_all_All","hMM_p_zCut_not_all_All"}; // anti cut
	TString mmPiPiPlots[] = {"hMM_pip_pimCut_PID_only_All","hMM_pip_pimCut_pi0_mass_All","hMM_pip_pimCut_K0Sig_mass_All", "hMM_pip_pimCut_all_All", // cuts
							  "hMM_pip_pimCut_not_all_All","hMM_pip_pim_zCut_not_all_All"}; // anti cut
	TString pPi0Plots[] = {"hM_p_pi0Cut_PID_only_All","hM_p_pi0Cut_pi0_mass_All","hM_p_pi0Cut_K0Sig_mass_All", "hM_p_pi0Cut_all_All", // cuts
							"hM_p_pi0Cut_not_all_All","hM_p_pi0_zCut_not_all_All"}; // anti cut
	TString SigVK0Plots[] = {"hMM_M_pip_pimCut_PID_only_All","hMM_M_pip_pimCut_pi0_mass_All","hMM_M_pip_pimCut_K0Sig_mass_All", "hMM_M_pip_pimCut_all_All", // cuts
							  "hMM_M_pip_pimCut_not_all_All","hMM_M_pip_pim_zCut_not_all_All"}; // anti cut

	TString cutTitles[] = {"PID only","After #pi^{0} mass cut","After K^{0} #Sigma^{+} mass cuts","After all mass cuts",
							"Anti cut","Anti cut"};
	
	// text file for event counts
	ofstream outfile;
    outfile.open("/home/louise/g8K0Sig/AnalysisSummary/html/convertCounts3.txt");
    
    // Counts after cuts
    int countPIDonly = 0;
	TH1F* pidHist = (TH1F*)infile->Get("hMM_p_pip_pimCut_PID_only_All"); 
	countPIDonly = pidHist->GetEntries();
	
	int countpi0Cut = 0;
	TH1F* pi0Hist = (TH1F*)infile->Get("hMM_p_pip_pimCut_pi0_mass_All"); 
	countpi0Cut = pi0Hist->GetEntries();
	
	int countK0SigCut = 0;
	TH1F* k0SigHist = (TH1F*)infile->Get("hMM_p_pip_pimCut_K0Sig_mass_All"); 
	countK0SigCut = k0SigHist->GetEntries();	
	
	int countAllCut = 0;
	TH1F* allHist = (TH1F*)infile->Get("hMM_p_pip_pimCut_all_All"); 
	countAllCut = allHist->GetEntries();	
    
	// pi0 mass plots
	for (int j=0; j<6; j++) {
		TH1F* hist = (TH1F*)infile->Get(pi0Plots[j]);
		hist->GetXaxis()->SetRange(0.0,hist->GetXaxis()->FindBin(0.4));
		hist->SetTitle(cutTitles[j]);
		hist->GetXaxis()->SetTitle("Missing mass(p #pi^{+} #pi^{-}) GeV");
		hist->Draw("HIST");

		gStyle->SetOptStat(10);

		TString outFilename = outdir+"/"+pi0Plots[j]+".png";
		c1->SaveAs(outFilename);
	}	

	// K0 mass plots
	for (int j=0; j<6; j++) {
		TH1F* hist = (TH1F*)infile->Get(K0Plots[j]);
		hist->GetXaxis()->SetRange(hist->GetXaxis()->FindBin(0.2),hist->GetXaxis()->FindBin(1.3));
		hist->SetTitle(cutTitles[j]);
		hist->GetXaxis()->SetTitle("Mass(#pi^{+} #pi^{-}) GeV");
		hist->Draw("HIST");

		gStyle->SetOptStat(10);

		TString outFilename = outdir+"/"+K0Plots[j]+".png";
		c1->SaveAs(outFilename);
	}	

	// 3pi mass plots
	for (int j=0; j<6; j++) {
		TH1F* hist = (TH1F*)infile->Get(pi3Plots[j]);
		hist->GetXaxis()->SetRange(hist->GetXaxis()->FindBin(0.2),hist->GetXaxis()->FindBin(1.3));
		hist->SetTitle(cutTitles[j]);
		hist->GetXaxis()->SetTitle("Missing Mass(p) GeV");
		hist->Draw("HIST");

		gStyle->SetOptStat(10);

		TString outFilename = outdir+"/"+pi3Plots[j]+".png";
		c1->SaveAs(outFilename);
	}
	
	// mm(2pi) mass plots
	for (int j=0; j<6; j++) {
		TH1F* hist = (TH1F*)infile->Get(mmPiPiPlots[j]);
		hist->GetXaxis()->SetRange(hist->GetXaxis()->FindBin(0.7),hist->GetXaxis()->FindBin(1.7));
		hist->SetTitle(cutTitles[j]);
		hist->GetXaxis()->SetTitle("Missing mass(#pi^{+} #pi^{-}) GeV");
		hist->Draw("HIST");

		gStyle->SetOptStat(10);

		TString outFilename = outdir+"/"+mmPiPiPlots[j]+".png";
		c1->SaveAs(outFilename);
	}	
	
	// p pi0 mass plots
	for (int j=0; j<6; j++) {
		TH1F* hist = (TH1F*)infile->Get(pPi0Plots[j]);
		hist->GetXaxis()->SetRange(hist->GetXaxis()->FindBin(1.0),hist->GetXaxis()->FindBin(1.8));
		hist->SetTitle(cutTitles[j]);
		hist->GetXaxis()->SetTitle("Mass(p #pi^{0}) GeV");
		hist->Draw("HIST");

		gStyle->SetOptStat(10);

		TString outFilename = outdir+"/"+pPi0Plots[j]+".png";
		c1->SaveAs(outFilename);
	}	
	
	// Sig v K0 mass plots
	for (int j=0; j<6; j++) {
		TH2F* hist = (TH2F*)infile->Get(SigVK0Plots[j]);
		hist->GetXaxis()->SetRange(hist->GetXaxis()->FindBin(0.2),hist->GetXaxis()->FindBin(1.4));
		hist->GetYaxis()->SetRange(hist->GetYaxis()->FindBin(0.81),hist->GetYaxis()->FindBin(1.5));
		hist->SetTitle(cutTitles[j]);
		hist->GetXaxis()->SetTitle("Mass(#pi^{+} #pi^{-}) GeV");
		hist->GetYaxis()->SetTitle("Missing Mass(#pi^{+} #pi^{-}) GeV");
		hist->Draw("COLZ");

		gStyle->SetOptStat(10);

		TString outFilename = outdir+"/"+SigVK0Plots[j]+".png";
		c1->SaveAs(outFilename);
	}	
	
	// Get the zoomed in plots
	TH1F* hist = (TH1F*)infile->Get("hMM_p_pip_pim_zCut_all_All");
	hist->SetTitle(cutTitles[3]);
	hist->GetXaxis()->SetRange(hist->GetXaxis()->FindBin(0.04),hist->GetXaxis()->FindBin(0.23));
	hist->GetXaxis()->SetTitle("Missing mass(p #pi^{+} #pi^{-}) GeV");
	hist->Draw("HIST");
	TString outFilename = outdir+"/hMM_p_pip_pim_zCut_all_All.png";
	c1->SaveAs(outFilename);
	
	hist = (TH1F*)infile->Get("hM_pip_pim_zCut_all_All");
	hist->SetTitle(cutTitles[3]);
	hist->GetXaxis()->SetRange(hist->GetXaxis()->FindBin(0.44),hist->GetXaxis()->FindBin(0.56));
	hist->GetXaxis()->SetTitle("Mass(#pi^{+} #pi^{-}) GeV");
	hist->Draw("HIST");
	outFilename = outdir+"/hM_pip_pim_zCut_all_All.png";
	c1->SaveAs(outFilename);
	
	hist = (TH1F*)infile->Get("hMM_p_zCut_all_All");
	hist->SetTitle(cutTitles[3]);
	//hist->GetXaxis()->SetRange(hist->GetXaxis()->FindBin(0.44),hist->GetXaxis()->FindBin(0.56));
	hist->GetXaxis()->SetTitle("Missing Mass(p) GeV");
	hist->Draw("HIST");
	outFilename = outdir+"/hMM_p_zCut_all_All.png";
	c1->SaveAs(outFilename);
	
	hist = (TH1F*)infile->Get("hMM_pip_pim_zCut_all_All");
	hist->SetTitle(cutTitles[3]);
	//hist->GetXaxis()->SetRange(hist->GetXaxis()->FindBin(0.44),hist->GetXaxis()->FindBin(0.56));
	hist->GetXaxis()->SetTitle("Missing Mass(#pi^{+} #pi^{-}) GeV");
	hist->Draw("HIST");
	outFilename = outdir+"/hMM_pip_pim_zCut_all_All.png";
	c1->SaveAs(outFilename);

	hist = (TH1F*)infile->Get("hM_p_pi0_zCut_all_All");
	hist->SetTitle(cutTitles[3]);
	//hist->GetXaxis()->SetRange(hist->GetXaxis()->FindBin(0.44),hist->GetXaxis()->FindBin(0.56));
	hist->GetXaxis()->SetTitle("Mass(p #pi^{0}) GeV");
	hist->Draw("HIST");
	outFilename = outdir+"/hM_p_pi0_zCut_all_All.png";
	c1->SaveAs(outFilename);

	TH2F* h2 = (TH2F*)infile->Get("hMM_M_pip_pim_zCut_all_All");
	h2->GetXaxis()->SetRange(h2->GetXaxis()->FindBin(0.45),h2->GetXaxis()->FindBin(0.55));
	h2->GetYaxis()->SetRange(h2->GetYaxis()->FindBin(1.15),h2->GetYaxis()->FindBin(1.25));
	h2->SetTitle(cutTitles[3]);
	h2->GetXaxis()->SetTitle("Mass(#pi^{+} #pi^{-}) GeV");
	h2->GetYaxis()->SetTitle("Missing Mass(#pi^{+} #pi^{-}) GeV");
	h2->Draw("COLZ");
	outFilename = outdir+"hMM_M_pip_pim_zCut_all_All.png";
	c1->SaveAs(outFilename);
	
	// Get plots from the tree
	TString trVars[] = {"Egamma","t","phiSigma","cosX","cosY","cosZ","costhK0CMS","pol"};
	float     xMin[] = {1.0,    -0.3, -3.14,    -1.0,  -1.0,  -1.0,  -1.0,        0.52};
	float     xMax[] = {2.2,    2.2,  3.14,     1.0,   1.0,   1.0,   1.0,         0.91};
	TString xTitle[] = {"E_{#gamma} (GeV)", "t (GeV^{2})", "#phi_{#Sigma^{+}}","cos #theta_{x}","cos #theta_{y}","cos #theta_{z}","cos #theta_{K^{0}}","Polarisation degree"};
	
	for (int i=0; i<8; i++) {
		TH1F* h1 = new TH1F("h1","", 100,xMin[i],xMax[i]);
		h1->GetXaxis()->SetTitle(xTitle[i]);
		tree->Draw(trVars[i]+">>h1");
		TString outFilename = outdir+"/"+trVars[i]+".png";
		c1->SaveAs(outFilename);	
	
	}

	// output counts
	outfile << "PID only " << countPIDonly << endl;
	outfile << "After pi0 mass cut " << countpi0Cut << endl;
	outfile << "After K0 Sig+ mass cut " << countK0SigCut << endl;
	outfile << "After all cuts " << countAllCut << endl;
	outfile.close();
	
}	

