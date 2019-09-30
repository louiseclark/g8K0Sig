// Run with
// root --hsdata DrawWithWeights.C

  // Define bins
  Double_t eBinLimits[] = {1.1, 1.35, 1.6, 1.85, 2.1};
  int iBinNums[] = {6,8,5,2};
  Double_t thBinLimits[4][9] = { {-1.0, -0.622, -0.39, -0.146, 0.054, 0.298, 1.0},
								 {-1.0, -0.465, -0.275, -0.135, 0.005, 0.165, 0.345, 0.535, 1.0},
								 {-1.0, -0.175, 0.035, 0.295, 0.505, 1.0},
								 {-1.0, 0.155, 1.0}
							   };
							   
  // hists							   
  TH1F* sigHistMM_pip_pim[4][8];
  TH1F* bgHistMM_pip_pim[4][8];
  TH1F* sigHistMM_pip_pimAll;
  TH1F* bgHistMM_pip_pimAll;
  
  TH1F* sigHistMM_p_pip_pim[4][8];
  TH1F* bgHistMM_p_pip_pim[4][8];
  TH1F* sigHistMM_p_pip_pimAll;
  TH1F* bgHistMM_p_pip_pimAll;

  TH1F* sigHistM_pip_pim[4][8];
  TH1F* bgHistM_pip_pim[4][8];
  TH1F* sigHistM_pip_pimAll;
  TH1F* bgHistM_pip_pimAll;
  
  TH1F* sigHistMM_p[4][8];
  TH1F* bgHistMM_p[4][8];
  TH1F* sigHistMM_pAll;
  TH1F* bgHistMM_pAll;
  
  TH1F* sigHistCosX[4][8];
  TH1F* bgHistCosX[4][8];
  TH1F* sigHistCosXAll;
  TH1F* bgHistCosXAll;  
  
  TH1F* sigHistCosY[4][8];
  TH1F* bgHistCosY[4][8];
  TH1F* sigHistCosYAll;
  TH1F* bgHistCosYAll;  
  
  TH1F* sigHistCosZ[4][8];
  TH1F* bgHistCosZ[4][8];
  TH1F* sigHistCosZAll;
  TH1F* bgHistCosZAll;  
  
  TH1F* sigHistPhiK0Para[4][8];  
  TH1F* bgHistPhiK0Para[4][8];
  TH1F* sigHistPhiK0Perp[4][8];  
  TH1F* bgHistPhiK0Perp[4][8];
  
  int currentEBin = 0;
  Double_t currentEBinCentre = 0.0;
  int currentThBin = 0;
  Double_t currentThBinCentre = 0.0;

void getHistForBin(float eValue, float thValue) {
   
  currentEBin = 0;
  currentEBinCentre = (eBinLimits[0]+eBinLimits[1]) / 2.0;
  for (int i=1; i<4; i++) {
    if (eValue > eBinLimits[i]) {
		currentEBin = i;
		currentEBinCentre = (eBinLimits[i]+eBinLimits[i+1]) / 2.0;
	}
  }
  currentThBin = 0;
  currentThBinCentre = (thBinLimits[currentEBin][0]+thBinLimits[currentEBin][1]) / 2.0;
  for (int i=1; i<iBinNums[currentEBin]; i++) {
    if (thValue > thBinLimits[currentEBin][i]) {
		currentThBin = i;
		currentThBinCentre = (thBinLimits[currentEBin][i]+thBinLimits[currentEBin][i+1]) / 2.0;
	}
  
  }
  						
}

void DrawWithWeights() {
	
  getHistForBin(1.48,0.6);
  cout << "Louise test currentEBin = " << currentEBin << " currentEBinCentre = " << currentEBinCentre << endl;
  cout << "Louise test currentThBin = " << currentThBin << " currentThBinCentre = " << currentThBinCentre << endl;
  
  Weights* wts[]={new Weights("TotalWeights"),new Weights("TotalWeights"),new Weights("TotalWeights"),new Weights("TotalWeights")};
  wts[0]->Merge("/home/louise/g8K0Sig/code/sWeights3/out_all_pi0K0_binned/Egamma1.23/Tweights.root","histWeights0.root","HSsWeights");
  wts[1]->Merge("/home/louise/g8K0Sig/code/sWeights3/out_all_pi0K0_binned/Egamma1.48/Tweights.root","histWeights1.root","HSsWeights");
  wts[2]->Merge("/home/louise/g8K0Sig/code/sWeights3/out_all_pi0K0_binned/Egamma1.73/Tweights.root","histWeights2.root","HSsWeights");
  wts[3]->Merge("/home/louise/g8K0Sig/code/sWeights3/out_all_pi0K0_binned/Egamma1.98/Tweights.root","histWeights3.root","HSsWeights");

  TString outdir = "/home/louise/g8K0Sig/AnalysisSummary/html/images/weighted/";
  TCanvas* c1=new TCanvas("c1","c1",800,600); // default canvas
  c1->cd(0); // set default canvas
 
  TChain chain("HSParticles");
  chain.AddFile("/w/work0/home/louise/g8K0Sig/convert_output/filepPi0_all.root");
  Double_t fgID,costhK0CMS, Egamma, MM_pip_pim, MM_p_pip_pim, M_pip_pim, MM_p, cosX, cosY, cosZ;
  chain.SetBranchAddress("fgID",&fgID);
  chain.SetBranchAddress("costhK0CMS",&costhK0CMS);
  chain.SetBranchAddress("Egamma",&Egamma);
  chain.SetBranchAddress("MM_pip_pim",&MM_pip_pim);
  chain.SetBranchAddress("MM_p_pip_pim",&MM_p_pip_pim);
  chain.SetBranchAddress("M_pip_pim",&M_pip_pim);
  chain.SetBranchAddress("MM_p",&MM_p);
  chain.SetBranchAddress("cosX",&cosX);
  chain.SetBranchAddress("cosY",&cosY);
  chain.SetBranchAddress("cosZ",&cosZ);
  chain.SetBranchAddress("phiK0",&phiK0);
  chain.SetBranchAddress("polState",&polState);
    
  gStyle->SetOptStat(1000001);
  // Create histograms
  // binned
  for (Int_t i=0; i<4; i++) {
	for (Int_t j=0; j<iBinNums[i]; j++) {
		std::stringstream histTitle;
		histTitle << "E_{#gamma} " << eBinLimits[i] << " to " << eBinLimits[i+1] << " GeV   cos(#theta_{K^{0}}) " << thBinLimits[i][j] << " to " << thBinLimits[i][j+1];
		
		// MM_pip_pim
		sigHistMM_pip_pim[i][j] = new TH1F("Integrated Signal Weight",histTitle.str().c_str(), 75, 1.14, 1.26);
		sigHistMM_pip_pim[i][j]->GetXaxis()->SetTitle("Missing mass(#pi^{+} #pi^{-}) GeV");
		sigHistMM_pip_pim[i][j]->SetLineWidth(2);
		bgHistMM_pip_pim[i][j] = new TH1F("Integrated BG Weight",histTitle.str().c_str(), 75, 1.14, 1.26);
		bgHistMM_pip_pim[i][j]->GetXaxis()->SetTitle("Missing mass(#pi^{+} #pi^{-}) GeV");		
		bgHistMM_pip_pim[i][j]->SetLineWidth(2);

		// MM_p_pip_pim
		sigHistMM_p_pip_pim[i][j] = new TH1F("Integrated Signal Weight",histTitle.str().c_str(), 75, 0.0, 0.25);
		sigHistMM_p_pip_pim[i][j]->GetXaxis()->SetTitle("Missing mass(p #pi^{+} #pi^{-}) GeV");
		sigHistMM_p_pip_pim[i][j]->SetLineWidth(2);
		bgHistMM_p_pip_pim[i][j] = new TH1F("Integrated BG Weight",histTitle.str().c_str(), 75, 0.0, 0.25);
		bgHistMM_p_pip_pim[i][j]->GetXaxis()->SetTitle("Missing mass(p #pi^{+} #pi^{-}) GeV");		
		bgHistMM_p_pip_pim[i][j]->SetLineWidth(2);
		
		// M_pip_pim
		sigHistM_pip_pim[i][j] = new TH1F("Integrated Signal Weight",histTitle.str().c_str(), 75, 0.44, 0.56);
		sigHistM_pip_pim[i][j]->GetXaxis()->SetTitle("Mass(#pi^{+} #pi^{-}) GeV");
		sigHistM_pip_pim[i][j]->SetLineWidth(2);
		bgHistM_pip_pim[i][j] = new TH1F("Integrated BG Weight",histTitle.str().c_str(), 75, 0.44, 0.56);
		bgHistM_pip_pim[i][j]->GetXaxis()->SetTitle("Mass(#pi^{+} #pi^{-}) GeV");		
		bgHistM_pip_pim[i][j]->SetLineWidth(2);		
		
		// MM_p
		sigHistMM_p[i][j] = new TH1F("Integrated Signal Weight",histTitle.str().c_str(), 75, 0.5, 1.2);
		sigHistMM_p[i][j]->GetXaxis()->SetTitle("Missing Mass(p) GeV");
		sigHistMM_p[i][j]->SetLineWidth(2);
		bgHistMM_p[i][j] = new TH1F("Integrated BG Weight",histTitle.str().c_str(), 75, 0.5, 1.2);
		bgHistMM_p[i][j]->GetXaxis()->SetTitle("Missing Mass(p) GeV");		
		bgHistMM_p[i][j]->SetLineWidth(2);			
		
		// cosX
		sigHistCosX[i][j] = new TH1F("Integrated Signal Weight",histTitle.str().c_str(), 75, -1.0, 1.0);
		sigHistCosX[i][j]->GetXaxis()->SetTitle("cos #theta_{x}");
		sigHistCosX[i][j]->SetLineWidth(2);
		bgHistCosX[i][j] = new TH1F("Integrated BG Weight",histTitle.str().c_str(), 75, -1.0, 1.0);
		bgHistCosX[i][j]->GetXaxis()->SetTitle("cos #theta_{x}");		
		bgHistCosX[i][j]->SetLineWidth(2);		
		
		// cosY
		sigHistCosY[i][j] = new TH1F("Integrated Signal Weight",histTitle.str().c_str(), 75, -1.0, 1.0);
		sigHistCosY[i][j]->GetXaxis()->SetTitle("cos #theta_{y}");
		sigHistCosY[i][j]->SetLineWidth(2);
		bgHistCosY[i][j] = new TH1F("Integrated BG Weight",histTitle.str().c_str(), 75, -1.0, 1.0);
		bgHistCosY[i][j]->GetXaxis()->SetTitle("cos #theta_{y}");		
		bgHistCosY[i][j]->SetLineWidth(2);	
		
		// cosZ
		sigHistCosZ[i][j] = new TH1F("Integrated Signal Weight",histTitle.str().c_str(), 75, -1.0, 1.0);
		sigHistCosZ[i][j]->GetXaxis()->SetTitle("cos #theta_{z}");
		sigHistCosZ[i][j]->SetLineWidth(2);
		bgHistCosZ[i][j] = new TH1F("Integrated BG Weight",histTitle.str().c_str(), 75, -1.0, 1.0);
		bgHistCosZ[i][j]->GetXaxis()->SetTitle("cos #theta_{z}");		
		bgHistCosZ[i][j]->SetLineWidth(2);			
		
		// phiK0 PARA		
		sigHistPhiK0Para[i][j] = new TH1F("Integrated Signal Weight",histTitle.str().c_str(), 75, -3.14, 3.14);		
		sigHistPhiK0Para[i][j]->GetXaxis()->SetTitle("#phi_{K0}");		
		sigHistCosZ[i][j]->SetLineWidth(2);		
		bgHistCosZ[i][j] = new TH1F("Integrated BG Weight",histTitle.str().c_str(), 75, -1.0, 1.0);		
		bgHistCosZ[i][j]->GetXaxis()->SetTitle("cos #theta_{z}");				
		bgHistCosZ[i][j]->SetLineWidth(2);			

	}
  }
  // unbinned
  // MM_pip_pim
  sigHistMM_pip_pimAll = new TH1F("Integrated Signal Weight","All events", 75, 1.14, 1.26);
  sigHistMM_pip_pimAll->GetXaxis()->SetTitle("Missing mass(#pi^{+} #pi^{-}) GeV");
  sigHistMM_pip_pimAll->SetLineWidth(2);
  bgHistMM_pip_pimAll = new TH1F("Integrated BG Weight","All events", 75, 1.14, 1.26);
  bgHistMM_pip_pimAll->GetXaxis()->SetTitle("Missing mass(#pi^{+} #pi^{-}) GeV");		
  bgHistMM_pip_pimAll->SetLineWidth(2);  
  
  // MM_p_pip_pim
  sigHistMM_p_pip_pimAll = new TH1F("Integrated Signal Weight","All events", 75, 0.0, 0.25);
  sigHistMM_p_pip_pimAll->GetXaxis()->SetTitle("Missing mass(p #pi^{+} #pi^{-}) GeV");
  sigHistMM_p_pip_pimAll->SetLineWidth(2);
  bgHistMM_p_pip_pimAll = new TH1F("Integrated BG Weight","All events", 75, 0.0, 0.25);
  bgHistMM_p_pip_pimAll->GetXaxis()->SetTitle("Missing mass(p #pi^{+} #pi^{-}) GeV");		
  bgHistMM_p_pip_pimAll->SetLineWidth(2);  
  
  // M_pip_pim
  sigHistM_pip_pimAll = new TH1F("Integrated Signal Weight","All events", 75, 0.44, 0.56);
  sigHistM_pip_pimAll->GetXaxis()->SetTitle("Mass(#pi^{+} #pi^{-}) GeV");
  sigHistM_pip_pimAll->SetLineWidth(2);
  bgHistM_pip_pimAll = new TH1F("Integrated BG Weight","All events", 75, 0.44, 0.56);
  bgHistM_pip_pimAll->GetXaxis()->SetTitle("Mass(#pi^{+} #pi^{-}) GeV");		
  bgHistM_pip_pimAll->SetLineWidth(2);   

  // MM_p
  sigHistMM_pAll = new TH1F("Integrated Signal Weight","All events", 75, 0.5, 1.2);
  sigHistMM_pAll->GetXaxis()->SetTitle("Missing mass(p) GeV");
  sigHistMM_pAll->SetLineWidth(2);
  bgHistMM_pAll = new TH1F("Integrated BG Weight","All events", 75, 0.5, 1.2);
  bgHistMM_pAll->GetXaxis()->SetTitle("Missing mass(p) GeV");		
  bgHistMM_pAll->SetLineWidth(2); 
  
   		
	// cosX
	sigHistCosXAll = new TH1F("Integrated Signal Weight","All events", 75, -1.0, 1.0);
	sigHistCosXAll->GetXaxis()->SetTitle("cos #theta_{x}");
	sigHistCosXAll->SetLineWidth(2);
	bgHistCosXAll = new TH1F("Integrated BG Weight","All events", 75, -1.0, 1.0);
	bgHistCosXAll->GetXaxis()->SetTitle("cos #theta_{x}");		
	bgHistCosXAll->SetLineWidth(2);		

	// cosY
	sigHistCosYAll = new TH1F("Integrated Signal Weight","All events", 75, -1.0, 1.0);
	sigHistCosYAll->GetXaxis()->SetTitle("cos #theta_{y}");
	sigHistCosYAll->SetLineWidth(2);
	bgHistCosYAll = new TH1F("Integrated BG Weight","All events", 75, -1.0, 1.0);
	bgHistCosYAll->GetXaxis()->SetTitle("cos #theta_{y}");		
	bgHistCosYAll->SetLineWidth(2);	

	// cosZ
	sigHistCosZAll = new TH1F("Integrated Signal Weight","All events", 75, -1.0, 1.0);
	sigHistCosZAll->GetXaxis()->SetTitle("cos #theta_{z}");
	sigHistCosZAll->SetLineWidth(2);
	bgHistCosZAll = new TH1F("Integrated BG Weight","All events", 75, -1.0, 1.0);
	bgHistCosZAll->GetXaxis()->SetTitle("cos #theta_{z}");		
	bgHistCosZAll->SetLineWidth(2);	
  
  // Fill the histograms  
  for(Int_t i=0;i<chain.GetEntries();i++){
    chain.GetEntry(i);
    getHistForBin(Egamma, costhK0CMS);
    if(wts[currentEBin]->GetEntryBinarySearch(fgID)){//find the weight for this event
      //cout << "Louise test currentEBin = " << currentEBin << " currentEBinCentre = " << currentEBinCentre << endl;
      //cout << "Louise test currentThBin = " << currentThBin << " currentThBinCentre = " << currentThBinCentre << endl;
	  //cout << "Louise test Egamma = " << Egamma << " costhK0CMS = " << costhK0CMS << endl;	
      
      // binned
      // MM_pip_pim
      sigHistMM_pip_pim[currentEBin][currentThBin]->Fill(MM_pip_pim,wts[currentEBin]->GetWeight("Signal"));
      bgHistMM_pip_pim[currentEBin][currentThBin]->Fill(MM_pip_pim,wts[currentEBin]->GetWeight("BG"));

      // MM_p_pip_pim
      sigHistMM_p_pip_pim[currentEBin][currentThBin]->Fill(MM_p_pip_pim,wts[currentEBin]->GetWeight("Signal"));
      bgHistMM_p_pip_pim[currentEBin][currentThBin]->Fill(MM_p_pip_pim,wts[currentEBin]->GetWeight("BG"));

      // M_pip_pim
      sigHistM_pip_pim[currentEBin][currentThBin]->Fill(M_pip_pim,wts[currentEBin]->GetWeight("Signal"));
      bgHistM_pip_pim[currentEBin][currentThBin]->Fill(M_pip_pim,wts[currentEBin]->GetWeight("BG"));
      
      // MM_p
      sigHistMM_p[currentEBin][currentThBin]->Fill(MM_p,wts[currentEBin]->GetWeight("Signal"));
      bgHistMM_p[currentEBin][currentThBin]->Fill(MM_p,wts[currentEBin]->GetWeight("BG"));

      // cosX
      sigHistCosX[currentEBin][currentThBin]->Fill(cosX,wts[currentEBin]->GetWeight("Signal"));
      bgHistCosX[currentEBin][currentThBin]->Fill(cosX,wts[currentEBin]->GetWeight("BG"));

      // cosY
      sigHistCosY[currentEBin][currentThBin]->Fill(cosY,wts[currentEBin]->GetWeight("Signal"));
      bgHistCosY[currentEBin][currentThBin]->Fill(cosY,wts[currentEBin]->GetWeight("BG"));

      // cosZ
      sigHistCosZ[currentEBin][currentThBin]->Fill(cosZ,wts[currentEBin]->GetWeight("Signal"));
      bgHistCosZ[currentEBin][currentThBin]->Fill(cosZ,wts[currentEBin]->GetWeight("BG"));

      // unbinned
      // MM_pip_pim
      sigHistMM_pip_pimAll->Fill(MM_pip_pim,wts[currentEBin]->GetWeight("Signal"));
      bgHistMM_pip_pimAll->Fill(MM_pip_pim,wts[currentEBin]->GetWeight("BG"));
      
      // MM_p_pip_pim
      sigHistMM_p_pip_pimAll->Fill(MM_p_pip_pim,wts[currentEBin]->GetWeight("Signal"));
      bgHistMM_p_pip_pimAll->Fill(MM_p_pip_pim,wts[currentEBin]->GetWeight("BG"));

      // M_pip_pim
      sigHistM_pip_pimAll->Fill(M_pip_pim,wts[currentEBin]->GetWeight("Signal"));
      bgHistM_pip_pimAll->Fill(M_pip_pim,wts[currentEBin]->GetWeight("BG"));

      // MM_p
      sigHistMM_pAll->Fill(MM_p,wts[currentEBin]->GetWeight("Signal"));
      bgHistMM_pAll->Fill(MM_p,wts[currentEBin]->GetWeight("BG"));
      
      // cosX
      sigHistCosXAll->Fill(cosX,wts[currentEBin]->GetWeight("Signal"));
      bgHistCosXAll->Fill(cosX,wts[currentEBin]->GetWeight("BG"));
	  
      // cosY
      sigHistCosYAll->Fill(cosY,wts[currentEBin]->GetWeight("Signal"));
      bgHistCosYAll->Fill(cosY,wts[currentEBin]->GetWeight("BG"));

      // cosZ
      sigHistCosZAll->Fill(cosZ,wts[currentEBin]->GetWeight("Signal"));
      bgHistCosZAll->Fill(cosZ,wts[currentEBin]->GetWeight("BG"));
    }
  }

  // Save histograms
  // binned
  for (Int_t i=0; i<4; i++) {
	for (Int_t j=0; j<iBinNums[i]; j++) {
	  // MM_pip_pim
	  sigHistMM_pip_pim[i][j]->Draw("HIST");
	  TString outFilename = outdir+"sigHistMM_pip_pim"+i+j+".png";
	  c1->SaveAs(outFilename);
	  bgHistMM_pip_pim[i][j]->Draw("HIST");
	  outFilename = outdir+"bgHistMM_pip_pim"+i+j+".png";
	  c1->SaveAs(outFilename);

	  // MM_p_pip_pim
	  sigHistMM_p_pip_pim[i][j]->Draw("HIST");
	  outFilename = outdir+"sigHistMM_p_pip_pim"+i+j+".png";
	  c1->SaveAs(outFilename);
	  bgHistMM_p_pip_pim[i][j]->Draw("HIST");
	  outFilename = outdir+"bgHistMM_p_pip_pim"+i+j+".png";
	  c1->SaveAs(outFilename);
	  
	  // M_pip_pim
	  sigHistM_pip_pim[i][j]->Draw("HIST");
	  outFilename = outdir+"sigHistM_pip_pim"+i+j+".png";
	  c1->SaveAs(outFilename);
	  bgHistM_pip_pim[i][j]->Draw("HIST");
	  outFilename = outdir+"bgHistM_pip_pim"+i+j+".png";
	  c1->SaveAs(outFilename);	  

	  // MM_p
	  sigHistMM_p[i][j]->Draw("HIST");
	  outFilename = outdir+"sigHistMM_p"+i+j+".png";
	  c1->SaveAs(outFilename);
	  bgHistMM_p[i][j]->Draw("HIST");
	  outFilename = outdir+"bgHistMM_p"+i+j+".png";
	  c1->SaveAs(outFilename);
	  
	  // cosX
	  sigHistCosX[i][j]->Draw("HIST");
	  outFilename = outdir+"sigHistCosX"+i+j+".png";
	  c1->SaveAs(outFilename);
	  bgHistCosX[i][j]->Draw("HIST");
	  outFilename = outdir+"bgHistCosX"+i+j+".png";
	  c1->SaveAs(outFilename);

	  // cosY
	  sigHistCosY[i][j]->Draw("HIST");
	  outFilename = outdir+"sigHistCosY"+i+j+".png";
	  c1->SaveAs(outFilename);
	  bgHistCosY[i][j]->Draw("HIST");
	  outFilename = outdir+"bgHistCosY"+i+j+".png";
	  c1->SaveAs(outFilename);
	  
	  // cosZ
	  sigHistCosZ[i][j]->Draw("HIST");
	  outFilename = outdir+"sigHistCosZ"+i+j+".png";
	  c1->SaveAs(outFilename);
	  bgHistCosZ[i][j]->Draw("HIST");
	  outFilename = outdir+"bgHistCosZ"+i+j+".png";
	  c1->SaveAs(outFilename);	  
	}
  }
  // unbinned
  // MM_pip_pim
  sigHistMM_pip_pimAll->Draw("HIST");
  TString outFilename = outdir+"sigHistMM_pip_pimAll.png";
  c1->SaveAs(outFilename);
  bgHistMM_pip_pimAll->Draw("HIST");
  outFilename = outdir+"bgHistMM_pip_pimAll.png";
  c1->SaveAs(outFilename);

  // MM_p_pip_pim
  sigHistMM_p_pip_pimAll->Draw("HIST");
  outFilename = outdir+"sigHistMM_p_pip_pimAll.png";
  c1->SaveAs(outFilename);
  bgHistMM_p_pip_pimAll->Draw("HIST");
  outFilename = outdir+"bgHistMM_p_pip_pimAll.png";
  c1->SaveAs(outFilename);
  
  // M_pip_pim
  sigHistM_pip_pimAll->Draw("HIST");
  outFilename = outdir+"sigHistM_pip_pimAll.png";
  c1->SaveAs(outFilename);
  bgHistM_pip_pimAll->Draw("HIST");
  outFilename = outdir+"bgHistM_pip_pimAll.png";
  c1->SaveAs(outFilename);  

  // MM_p
  sigHistMM_pAll->Draw("HIST");
  outFilename = outdir+"sigHistMM_pAll.png";
  c1->SaveAs(outFilename);
  bgHistMM_pAll->Draw("HIST");
  outFilename = outdir+"bgHistMM_pAll.png";
  c1->SaveAs(outFilename);
  
  // cosX
  sigHistCosXAll->Draw("HIST");
  outFilename = outdir+"sigHistCosXAll.png";
  c1->SaveAs(outFilename);
  bgHistCosXAll->Draw("HIST");
  outFilename = outdir+"bgHistCosXAll.png";
  c1->SaveAs(outFilename);

  // cosY
  sigHistCosYAll->Draw("HIST");
  outFilename = outdir+"sigHistCosYAll.png";
  c1->SaveAs(outFilename);
  bgHistCosYAll->Draw("HIST");
  outFilename = outdir+"bgHistCosYAll.png";
  c1->SaveAs(outFilename);
  
  // cosZ
  sigHistCosZAll->Draw("HIST");
  outFilename = outdir+"sigHistCosZAll.png";
  c1->SaveAs(outFilename);
  bgHistCosZAll->Draw("HIST");
  outFilename = outdir+"bgHistCosZAll.png";
  c1->SaveAs(outFilename);	  
  
}
