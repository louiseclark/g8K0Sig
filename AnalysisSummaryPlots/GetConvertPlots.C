void GetConvertPlots() {
	
	TString inFileName = "/w/work0/home/louise/g8K0Sig/convert_output/filepPi0_all.root";
	TFile* infile = TFile::Open(inFileName);
	TTree* tree = (TTree*)infile->Get("HSParticles");
	
	TString outdir = "/home/louise/g8K0Sig/AnalysisSummary/html/images/convert/";
	TCanvas* c1=new TCanvas("c1","c1",800,600); // default canvas
	c1->cd(0); // set default canvas
	
	// NEXT
	// use convert_output3 and change to z% hists
	// redo weights / fits with convert_output3 as systematic check
	
	
	TString pi0Plots[] = {"hMM_p_pip_pimCut_PID_only_All","hMM_p_pip_pimCut_pi0_mass_All","hMM_p_pip_pimCut_K0Sig_mass_All", "hMM_p_pip_pimCut_all_All"};
	TString K0Plots[] = {"hM_pip_pimCut_PID_only_All","hM_pip_pimCut_pi0_mass_All","hM_pip_pimCut_K0Sig_mass_All", "hM_pip_pimCut_all_All"};
	TString pi3Plots[] = {"hMM_pCut_PID_only_All","hMM_pCut_pi0_mass_All","hMM_pCut_K0Sig_mass_All", "hMM_pCut_all_All"};
	TString mmPiPiPlots[] = {"hMM_pip_pimCut_PID_only_All","hMM_pip_pimCut_pi0_mass_All","hMM_pip_pimCut_K0Sig_mass_All", "hMM_pip_pimCut_all_All"};
	TString pPi0Plots[] = {"hM_p_pi0Cut_PID_only_All","hM_p_pi0Cut_pi0_mass_All","hM_p_pi0Cut_K0Sig_mass_All", "hM_p_pi0Cut_all_All"};
	TString SigVK0Plots[] = {"hMM_M_pip_pimCut_PID_only_All","hMM_M_pip_pimCut_pi0_mass_All","hMM_M_pip_pimCut_K0Sig_mass_All", "hMM_M_pip_pimCut_all_All"};

	TString cutTitles[] = {"PID only","After #pi^{0} mass cut","After K^{0} #Sigma^{+} mass cuts","After all mass cuts"};
	
	// text file for event counts
	ofstream outfile;
    outfile.open("/home/louise/g8K0Sig/AnalysisSummary/html/convertCounts.txt");
    
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
	for (int j=0; j<4; j++) {
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
	for (int j=0; j<4; j++) {
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
	for (int j=0; j<4; j++) {
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
	for (int j=0; j<4; j++) {
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
	for (int j=0; j<4; j++) {
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
	for (int j=0; j<4; j++) {
		TH2F* hist = (TH2F*)infile->Get(SigVK0Plots[j]);
		hist->GetXaxis()->SetRange(hist->GetXaxis()->FindBin(0.2),hist->GetXaxis()->FindBin(1.4));
		hist->GetYaxis()->SetRange(hist->GetXaxis()->FindBin(0.8),hist->GetYaxis()->FindBin(1.5));
		hist->SetTitle(SigVK0Plots[j]);
		hist->GetXaxis()->SetTitle("Mass(#pi^{+} #pi^{-}) GeV");
		hist->GetYaxis()->SetTitle("Missing Mass(#pi^{+} #pi^{-}) GeV");
		hist->Draw("COLZ");

		gStyle->SetOptStat(10);

		TString outFilename = outdir+"/"+SigVK0Plots[j]+".png";
		c1->SaveAs(outFilename);
	}	
	
	// Draw better hists from the trees
	TH1F* h1 = new TH1F("h1","After all mass cuts", 100,0.04,0.26);
	h1->GetXaxis()->SetTitle("Missing mass(p #pi^{+} #pi^{-}) GeV");
	tree->Draw("MM_p_pip_pim>>h1");
	TString outFilename = outdir+"/hMM_p_pip_pimCut_all_Tree.png";
	c1->SaveAs(outFilename);
	
	TH1F* h2 = new TH1F("h2","After all mass cuts", 100,0.44,0.56);
	h2->GetXaxis()->SetTitle("Mass(#pi^{+} #pi^{-}) GeV");
	tree->Draw("M_pip_pim>>h2");
	outFilename = outdir+"/hM_pip_pimCut_all_Tree.png";
	c1->SaveAs(outFilename);
	
	TH1F* h3 = new TH1F("h3","After all mass cuts", 100,0.5,1.2);
	h3->GetXaxis()->SetTitle("Missing Mass(p) GeV");
	tree->Draw("MM_p>>h3");
	outFilename = outdir+"/hMM_pCut_all_Tree.png";
	c1->SaveAs(outFilename);	

	TH1F* h4 = new TH1F("h4","After all mass cuts", 100,1.14,1.26);
	h4->GetXaxis()->SetTitle("Missing Mass(#pi^{+} #pi^{-}) GeV");
	tree->Draw("MM_pip_pim>>h4");
	outFilename = outdir+"/hMM_pip_pimCut_all_Tree.png";
	c1->SaveAs(outFilename);	
	
	TH1F* h5 = new TH1F("h5","After all mass cuts", 100,1.15,1.23);
	h5->GetXaxis()->SetTitle("Mass(p #pi^{0}) GeV");
	tree->Draw("M_p_pi0>>h5");
	outFilename = outdir+"/hM_p_pi0Cut_all_Tree.png";
	c1->SaveAs(outFilename);	
	
	TH2F* h6 = new TH2F("h6","After all mass cuts", 100,0.48,0.52, 100,1.16,1.2);
	h6->GetXaxis()->SetTitle("Mass(#pi^{+} #pi^{-}) GeV");
	h6->GetYaxis()->SetTitle("Missing Mass(#pi^{+} #pi^{-}) GeV");
	tree->Draw("MM_pip_pim:M_pip_pim>>h6");
	h6->Draw("COLZ");
	outFilename = outdir+"/hMM_M_pip_pimCut_all_Tree.png";
	c1->SaveAs(outFilename);	

	
	// output counts
	outfile << "PID only " << countPIDonly << endl;
	outfile << "After pi0 mass cut " << countpi0Cut << endl;
	outfile << "After K0 Sig+ mass cut " << countK0SigCut << endl;
	outfile << "After all cuts " << countAllCut << endl;
	outfile.close();
	
}	

