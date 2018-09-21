TCanvas *c2=new TCanvas("c2","c2",800,600);
bool doHist = true;

void DoFits(TDirectory *inDir, TDirectory *outDir){	
	
	int rebin_n = 4;
	
	// beam asymmetry all events
	
	TH1F* phiSigPARA = (TH1F*)inDir->Get("phiSigPARA");
	TH1F* phiSigPERP = (TH1F*)inDir->Get("phiSigPERP"); 
	
	phiSigPARA->Sumw2();
	phiSigPERP->Sumw2();
	phiSigPARA->Rebin(rebin_n);
	phiSigPERP->Rebin(rebin_n);
		
	TH1 *phiSigAsym = phiSigPARA->GetAsymmetry(phiSigPERP);
	phiSigAsym->SetTitle("phiSigAsym");
	phiSigAsym->SetName("phiSigAsym");
	
	TF1* cos2phiSig=new TF1("cos2phiSig","[0]+[1]*cos((2*x+[2]))",-3.2,3.2); 
	phiSigAsym->Fit("cos2phiSig");
	
	outDir->cd();
	cout << "Writing to outDir " << outDir->GetName() << endl;
	phiSigAsym->Write();
	
	TCanvas *can = new TCanvas("can","can",800,600);
	phiSigAsym->Draw();
	can->SaveAs((TString)outDir->GetName()+"phiSigAsym.gif");
	can->Clear();
	
	
}
void Analyser() {
	
//	DIR *pdir = NULL; 
//	pdir = opendir ("/home/louise/g8_phi/sWeights/hist/out"); 
//	struct dirent *pent = NULL;
//	while (pent = readdir (pdir)) {
//		cout << pent->d_name << endl;
//	}
//	closedir (pdir);

	bool doBins = false;	
	
	if (doBins) {
		
		TFile *infile = TFile::Open("/home/louise/g8_phi/sWeights/hist/out/hists_costh_top.root");
		TFile* outfile = new TFile("out/analyse_costh_top.root","recreate");	
		
		//TIter 	nextWeightsDir(infile->GetListOfKeys());
		//TKey	*weightsKey;
		string dirs[3] = {"Signal", "BG", "All"};
		
		//while ((weightsKey=(TKey*)nextWeightsDir())) {
		for (int i=0; i<3; i++) {
					
			//TDirectory *weightsDir = infile->GetDirectory(weightsKey->GetName());	
			TDirectory *weightsDir = infile->GetDirectory(dirs[i].c_str());	
			TIter	nextTbinDir(weightsDir->GetListOfKeys());
			TKey 	*tbinKey;
			//outfile->mkdir(weightsKey->GetName());
			//TDirectory *weightsDirOut = outfile->GetDirectory(weightsKey->GetName());
			outfile->mkdir(dirs[i].c_str());
			TDirectory *weightsDirOut = outfile->GetDirectory(dirs[i].c_str());
			
			while ((tbinKey=(TKey*)nextTbinDir())) {
			
				TDirectory *tbinDir = weightsDir->GetDirectory(tbinKey->GetName());
				TIter	nextEbinDir(tbinDir->GetListOfKeys());
				TKey 	*ebinKey;
				weightsDirOut->mkdir(tbinKey->GetName());
				TDirectory *tbinDirOut = weightsDirOut->GetDirectory(tbinKey->GetName());
				
				while ((ebinKey=(TKey*)nextEbinDir())) {
					
					TDirectory *ebinDir = tbinDir->GetDirectory(ebinKey->GetName());
					tbinDirOut->mkdir(ebinKey->GetName());
					TDirectory *ebinDirOut = tbinDirOut->GetDirectory(ebinKey->GetName());
					
					//DoFits(ebinDir, ebinDirOut);					
									
				}
			}
		}
		
		// sum the t bins, i.e. binned only in E
		//TDirectory *signalDir = infile->GetDirectory("Signal");
		//TIter	nextTbinDir(signalDir->GetListOfKeys());
		//TKey 	*tbinKey;
		//outfile->cd("Signal");
		//outfile->GetDirectory("Signal")->mkdir("Summed_tBins");
		//TDirectory *sumtBinsDir = outfile->GetDirectory("Signal")->GetDirectory("Summed_tBins");
		
		//while ((tbinKey=(TKey*)nextTbinDir())) {
			
			//TDirectory *tbinDir = signalDir->GetDirectory(tbinKey->GetName());
			//TIter	nextEbinDir(tbinDir->GetListOfKeys());
			//TKey 	*ebinKey;
			
			//// Get the first hist to start adding to
			//ebinKey=(TKey*)nextEbinDir();
			//TDirectory *ebinDir = tbinDir->GetDirectory(ebinKey->GetName());
			//TH1F* phiPhiCmPARA = (TH1F*)ebinDir->Get("phiPhiCmPARA");
			
			//while ((ebinKey=(TKey*)nextEbinDir())) {
			
				//ebinDir = tbinDir->GetDirectory(ebinKey->GetName());
				//phiPhiCmPARA->Add((TH1F*)ebinDir->Get("phiPhiCmPARA"));
			//}
						
			//sumtBinsDir->cd();
			//phiPhiCmPARA->Write();

		//}
		
		outfile->Close();
	}
	else {
		
		TFile *infile = TFile::Open("/home/louise/g8K0Sig/code/sWeights/hist/out/hists21.root");
		TFile* outfile = new TFile("out/analyse21.root","recreate");	
		string dirs[3] = {"Signal", "BG", "All"};
		
		for (int i=0; i<3; i++) {
			
			TDirectory *inDir = infile->GetDirectory(dirs[i].c_str());
			cout << dirs[i].c_str() << endl;
			outfile->mkdir(dirs[i].c_str());
			TDirectory *outDir = outfile->GetDirectory(dirs[i].c_str());
			DoFits(inDir, outDir);
			//outfile->cd("..");
			
			//if (i==0) {
				//TCanvas *c2=new TCanvas("c2","c2",800,600);
				//c2->Divide(4,3);
				//c2->cd(1);
				//TH1F* sig1 = (TH1F*)outfile->GetDirectory(dirs[i].c_str())->Get("phiPhiAsym");
				//sig1->Draw();
				//c2->cd(2);
				//TH1F* sig2 = (TH1F*)outfile->GetDirectory(dirs[i].c_str())->Get("phiProtonAsym");
				//sig2->Draw();
				//c2->cd(3);
				//c2->SaveAs("sigHists.gif");
				////c1->Clear();
			//}
			
		}
		outfile->Close();
		
	}
	//c2->SaveAs("sigHists.gif");
}

