#include <string>

// Run with
// brufit DrawWithWeights.C

  // Baseline
  //TString weightsDir = "/home/louise/g8K0Sig/code/sWeights3/";
  //TString outdir = "/home/louise/public_html/html/images/weighted/";
  // Systematic tests
  TString weightsDir = "/home/louise/g8K0Sig/code/sWeights3_test4/";
  TString outdir = "/home/louise/public_html/html/images/st4/weighted/";
  
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
  
  TF1* massFunc[4][8];
  
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
  
  TH1F* sigHistEg[4][8];
  TH1F* bgHistEg[4][8];
  TH1F* sigHistEgAll;
  TH1F* bgHistEgAll;  
  
  TH1F* sigHistt[4][8];
  TH1F* bgHistt[4][8];
  TH1F* sigHisttAll;
  TH1F* bgHisttAll;  
    
  TH1F* sigHistCosth[4][8];
  TH1F* bgHistCosth[4][8];
  TH1F* sigHistCosthAll;
  TH1F* bgHistCosthAll;  
  
  
  TH1F* sigHistPhiK0Para[4][8];  
  TH1F* bgHistPhiK0Para[4][8];
  TH1F* sigHistPhiK0Perp[4][8];  
  TH1F* bgHistPhiK0Perp[4][8];
  TH1* sigHistPhiK0Asym[4][8];  
  TH1* bgHistPhiK0Asym[4][8];
  
  // correlation
  TH2F* allHistK0CosX[4][8];
  TH2F* sigHistK0CosX[4][8];
  TH2F* bgHistK0CosX[4][8];
  TH2F* allHistK0CosXAll;
  TH2F* sigHistK0CosXAll;
  TH2F* bgHistK0CosXAll;
  
  TH2F* allHistpi0CosX[4][8];
  TH2F* sigHistpi0CosX[4][8];
  TH2F* bgHistpi0CosX[4][8];
  TH2F* allHistpi0CosXAll;
  TH2F* sigHistpi0CosXAll;
  TH2F* bgHistpi0CosXAll;  
  
  TH2F* allHistK0CosY[4][8];
  TH2F* sigHistK0CosY[4][8];
  TH2F* bgHistK0CosY[4][8];
  TH2F* allHistK0CosYAll;
  TH2F* sigHistK0CosYAll;
  TH2F* bgHistK0CosYAll;
  
  TH2F* allHistpi0CosY[4][8];
  TH2F* sigHistpi0CosY[4][8];
  TH2F* bgHistpi0CosY[4][8];
  TH2F* allHistpi0CosYAll;
  TH2F* sigHistpi0CosYAll;
  TH2F* bgHistpi0CosYAll;   
  
  TH2F* allHistK0CosZ[4][8];
  TH2F* sigHistK0CosZ[4][8];
  TH2F* bgHistK0CosZ[4][8];
  TH2F* allHistK0CosZAll;
  TH2F* sigHistK0CosZAll;
  TH2F* bgHistK0CosZAll;
  
  TH2F* allHistpi0CosZ[4][8];
  TH2F* sigHistpi0CosZ[4][8];
  TH2F* bgHistpi0CosZ[4][8];
  TH2F* allHistpi0CosZAll;
  TH2F* sigHistpi0CosZAll;
  TH2F* bgHistpi0CosZAll;  
  
  TH2F* allHistK0phiK0[4][8];
  TH2F* sigHistK0phiK0[4][8];
  TH2F* bgHistK0phiK0[4][8];
  TH2F* allHistK0phiK0All;
  TH2F* sigHistK0phiK0All;
  TH2F* bgHistK0phiK0All;
  
  TH2F* allHistpi0phiK0[4][8];
  TH2F* sigHistpi0phiK0[4][8];
  TH2F* bgHistpi0phiK0[4][8];
  TH2F* allHistpi0phiK0All;
  TH2F* sigHistpi0phiK0All;
  TH2F* bgHistpi0phiK0All;
  
  TH2F* allHistK0pol[4][8];
  TH2F* sigHistK0pol[4][8];
  TH2F* bgHistK0pol[4][8];
  TH2F* allHistK0polAll;
  TH2F* sigHistK0polAll;
  TH2F* bgHistK0polAll;
  
  TH2F* allHistpi0pol[4][8];
  TH2F* sigHistpi0pol[4][8];
  TH2F* bgHistpi0pol[4][8];
  TH2F* allHistpi0polAll;
  TH2F* sigHistpi0polAll;
  TH2F* bgHistpi0polAll;   
     
   
  
  
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
  //cout << "Louise test currentEBin = " << currentEBin << " currentEBinCentre = " << currentEBinCentre << endl;
  //cout << "Louise test currentThBin = " << currentThBin << " currentThBinCentre = " << currentThBinCentre << endl;
  
  Weights* wts[]={new Weights("TotalWeights"),new Weights("TotalWeights"),new Weights("TotalWeights"),new Weights("TotalWeights")};
  wts[0]->Merge(weightsDir+"out_all_pi0K0_binned/Egamma1.23/Tweights.root","histWeights0.root","HSsWeights");
  wts[1]->Merge(weightsDir+"out_all_pi0K0_binned/Egamma1.48/Tweights.root","histWeights1.root","HSsWeights");
  wts[2]->Merge(weightsDir+"out_all_pi0K0_binned/Egamma1.73/Tweights.root","histWeights2.root","HSsWeights");
  wts[3]->Merge(weightsDir+"out_all_pi0K0_binned/Egamma1.98/Tweights.root","histWeights3.root","HSsWeights");
  //wts[3]->Merge("/home/louise/g8K0Sig/code/sWeights3/out_all_pi0K0_binned/Egamma1.98/Tweights.root","histWeights3.root","HSsWeights");

  TCanvas* c1=new TCanvas("c1","c1",800,600); // default canvas
  c1->cd(0); // set default canvas
 
  TChain chain("HSParticles");
  chain.AddFile("/w/work0/home/louise/g8K0Sig/convert_output/filepPi0_all.root");
  Double_t fgID,costhK0CMS, Egamma, t, MM_pip_pim, MM_p_pip_pim, M_pip_pim, MM_p, cosX, cosY, cosZ, phiK0, pol;
  Int_t polState;
  chain.SetBranchAddress("fgID",&fgID);
  chain.SetBranchAddress("costhK0CMS",&costhK0CMS);
  chain.SetBranchAddress("Egamma",&Egamma);
  chain.SetBranchAddress("t",&t);
  chain.SetBranchAddress("MM_pip_pim",&MM_pip_pim);
  chain.SetBranchAddress("MM_p_pip_pim",&MM_p_pip_pim);
  chain.SetBranchAddress("M_pip_pim",&M_pip_pim);
  chain.SetBranchAddress("MM_p",&MM_p);
  chain.SetBranchAddress("cosX",&cosX);
  chain.SetBranchAddress("cosY",&cosY);
  chain.SetBranchAddress("cosZ",&cosZ);
  chain.SetBranchAddress("phiK0",&phiK0);
  chain.SetBranchAddress("pol",&pol);
  chain.SetBranchAddress("polState",&polState);
    
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

		// Egamma
		sigHistEg[i][j] = new TH1F("Integrated Signal Weight",histTitle.str().c_str(), 100, 1.0, 2.2);
		sigHistEg[i][j]->GetXaxis()->SetTitle("E_{#gamma} (GeV)");
		sigHistEg[i][j]->SetLineWidth(2);
		bgHistEg[i][j] = new TH1F("Integrated BG Weight",histTitle.str().c_str(), 100, 1.0, 2.2);
		bgHistEg[i][j]->GetXaxis()->SetTitle("E_{#gamma} (GeV)");		
		bgHistEg[i][j]->SetLineWidth(2);			

		// t
		sigHistt[i][j] = new TH1F("Integrated Signal Weight",histTitle.str().c_str(), 100, -0.3, 2.2);
		sigHistt[i][j]->GetXaxis()->SetTitle("t (GeV/c)");
		sigHistt[i][j]->SetLineWidth(2);
		bgHistt[i][j] = new TH1F("Integrated BG Weight",histTitle.str().c_str(), 100, -0.3, 2.2);
		bgHistt[i][j]->GetXaxis()->SetTitle("t (GeV/c)");		
		bgHistt[i][j]->SetLineWidth(2);			

		// costh
		sigHistCosth[i][j] = new TH1F("Integrated Signal Weight",histTitle.str().c_str(), 75, -1.0, 1.0);
		sigHistCosth[i][j]->GetXaxis()->SetTitle("cos #theta_{K0}");
		sigHistCosth[i][j]->SetLineWidth(2);
		bgHistCosth[i][j] = new TH1F("Integrated BG Weight",histTitle.str().c_str(), 75, -1.0, 1.0);
		bgHistCosth[i][j]->GetXaxis()->SetTitle("cos #theta_{K0}");		
		bgHistCosth[i][j]->SetLineWidth(2);			

		
		// phiK0 PARA		
		sigHistPhiK0Para[i][j] = new TH1F("Integrated Signal Weight (PARA)",histTitle.str().c_str(), 75, -3.14, 3.14);		
		sigHistPhiK0Para[i][j]->GetXaxis()->SetTitle("#phi_{K0}");		
		sigHistPhiK0Para[i][j]->SetLineWidth(2);		
		bgHistPhiK0Para[i][j] = new TH1F("Integrated BG Weight  (PARA)",histTitle.str().c_str(), 75, -3.14, 3.14);		
		bgHistPhiK0Para[i][j]->GetXaxis()->SetTitle("#phi_{K0}");				
		bgHistPhiK0Para[i][j]->SetLineWidth(2);		
		
		// phiK0 PERP
		sigHistPhiK0Perp[i][j] = new TH1F("Integrated Signal Weight (PERP)",histTitle.str().c_str(), 75, -3.14, 3.14);		
		sigHistPhiK0Perp[i][j]->GetXaxis()->SetTitle("#phi_{K0}");		
		sigHistPhiK0Perp[i][j]->SetLineWidth(2);		
		bgHistPhiK0Perp[i][j] = new TH1F("Integrated BG Weight (PERP)",histTitle.str().c_str(), 75, -3.14, 3.14);		
		bgHistPhiK0Perp[i][j]->GetXaxis()->SetTitle("#phi_{K0}");				
		bgHistPhiK0Perp[i][j]->SetLineWidth(2);				

		// correlation
		allHistK0CosX[i][j] = new TH2F("All events",histTitle.str().c_str(), 75, 0.44, 0.56, 75, -1.0, 1.0);
		sigHistK0CosX[i][j] = new TH2F("Integrated Signal Weight",histTitle.str().c_str(), 75, 0.44, 0.56, 75, -1.0, 1.0);
		bgHistK0CosX[i][j] = new TH2F("Integrated Background Weight",histTitle.str().c_str(), 75, 0.44, 0.56, 75, -1.0, 1.0);
		allHistK0CosX[i][j]->GetXaxis()->SetTitle("Mass(#pi^{+} #pi^{-}) GeV");
	    allHistK0CosX[i][j]->GetYaxis()->SetTitle("cos #theta_{x}");
		sigHistK0CosX[i][j]->GetXaxis()->SetTitle("Mass(#pi^{+} #pi^{-}) GeV");
		sigHistK0CosX[i][j]->GetYaxis()->SetTitle("cos #theta_{x}");
		bgHistK0CosX[i][j]->GetXaxis()->SetTitle("Mass(#pi^{+} #pi^{-}) GeV");
		bgHistK0CosX[i][j]->GetYaxis()->SetTitle("cos #theta_{x}");

		allHistK0CosY[i][j] = new TH2F("All events",histTitle.str().c_str(), 75, 0.44, 0.56, 75, -1.0, 1.0);
		sigHistK0CosY[i][j] = new TH2F("Integrated Signal Weight",histTitle.str().c_str(), 75, 0.44, 0.56, 75, -1.0, 1.0);
		bgHistK0CosY[i][j] = new TH2F("Integrated Background Weight",histTitle.str().c_str(), 75, 0.44, 0.56, 75, -1.0, 1.0);
		allHistK0CosY[i][j]->GetXaxis()->SetTitle("Mass(#pi^{+} #pi^{-}) GeV");
	    allHistK0CosY[i][j]->GetYaxis()->SetTitle("cos #theta_{y}");
		sigHistK0CosY[i][j]->GetXaxis()->SetTitle("Mass(#pi^{+} #pi^{-}) GeV");
		sigHistK0CosY[i][j]->GetYaxis()->SetTitle("cos #theta_{y}");
		bgHistK0CosY[i][j]->GetXaxis()->SetTitle("Mass(#pi^{+} #pi^{-}) GeV");
		bgHistK0CosY[i][j]->GetYaxis()->SetTitle("cos #theta_{y}");

		allHistK0CosZ[i][j] = new TH2F("All events",histTitle.str().c_str(), 75, 0.44, 0.56, 75, -1.0, 1.0);
		sigHistK0CosZ[i][j] = new TH2F("Integrated Signal Weight",histTitle.str().c_str(), 75, 0.44, 0.56, 75, -1.0, 1.0);
		bgHistK0CosZ[i][j] = new TH2F("Integrated Background Weight",histTitle.str().c_str(), 75, 0.44, 0.56, 75, -1.0, 1.0);
		allHistK0CosZ[i][j]->GetXaxis()->SetTitle("Mass(#pi^{+} #pi^{-}) GeV");
	    allHistK0CosZ[i][j]->GetYaxis()->SetTitle("cos #theta_{z}");
		sigHistK0CosZ[i][j]->GetXaxis()->SetTitle("Mass(#pi^{+} #pi^{-}) GeV");
		sigHistK0CosZ[i][j]->GetYaxis()->SetTitle("cos #theta_{z}");
		bgHistK0CosZ[i][j]->GetXaxis()->SetTitle("Mass(#pi^{+} #pi^{-}) GeV");
		bgHistK0CosZ[i][j]->GetYaxis()->SetTitle("cos #theta_{z}");
		
		allHistK0phiK0[i][j] = new TH2F("All events",histTitle.str().c_str(), 75, 0.44, 0.56, 75, -3.14, 3.14);
		sigHistK0phiK0[i][j] = new TH2F("Integrated Signal Weight",histTitle.str().c_str(), 75, 0.44, 0.56, 75, -3.14, 3.14);
		bgHistK0phiK0[i][j] = new TH2F("Integrated Background Weight",histTitle.str().c_str(), 75, 0.44, 0.56, 75, -3.14, 3.14);
		allHistK0phiK0[i][j]->GetXaxis()->SetTitle("Mass(#pi^{+} #pi^{-}) GeV");
	    allHistK0phiK0[i][j]->GetYaxis()->SetTitle("#phi_{K0}");
		sigHistK0phiK0[i][j]->GetXaxis()->SetTitle("Mass(#pi^{+} #pi^{-}) GeV");
		sigHistK0phiK0[i][j]->GetYaxis()->SetTitle("#phi_{K0}");
		bgHistK0phiK0[i][j]->GetXaxis()->SetTitle("Mass(#pi^{+} #pi^{-}) GeV");
		bgHistK0phiK0[i][j]->GetYaxis()->SetTitle("#phi_{K0}");

		allHistK0pol[i][j] = new TH2F("All events",histTitle.str().c_str(), 75, 0.44, 0.56, 75, 0.6, 1.0);
		sigHistK0pol[i][j] = new TH2F("Integrated Signal Weight",histTitle.str().c_str(), 75, 0.44, 0.56, 75, 0.6, 1.0);
		bgHistK0pol[i][j] = new TH2F("Integrated Background Weight",histTitle.str().c_str(), 75, 0.44, 0.56, 75, 0.6, 1.0);
		allHistK0pol[i][j]->GetXaxis()->SetTitle("Mass(#pi^{+} #pi^{-}) GeV");
	    allHistK0pol[i][j]->GetYaxis()->SetTitle("Polarisation degree");
		sigHistK0pol[i][j]->GetXaxis()->SetTitle("Mass(#pi^{+} #pi^{-}) GeV");
		sigHistK0pol[i][j]->GetYaxis()->SetTitle("Polarisation degree");
		bgHistK0pol[i][j]->GetXaxis()->SetTitle("Mass(#pi^{+} #pi^{-}) GeV");
		bgHistK0pol[i][j]->GetYaxis()->SetTitle("Polarisation degree");

		allHistpi0CosX[i][j] = new TH2F("All events",histTitle.str().c_str(), 75, 0.05, 0.22, 75, -1.0, 1.0);
		sigHistpi0CosX[i][j] = new TH2F("Integrated Signal Weight",histTitle.str().c_str(), 75, 0.05, 0.22, 75, -1.0, 1.0);
		bgHistpi0CosX[i][j] = new TH2F("Integrated Background Weight",histTitle.str().c_str(), 75, 0.05, 0.22, 75, -1.0, 1.0);
		allHistpi0CosX[i][j]->GetXaxis()->SetTitle("Missing Mass (p #pi^{+} #pi^{-}) GeV");
	    allHistpi0CosX[i][j]->GetYaxis()->SetTitle("cos #theta_{x}");
		sigHistpi0CosX[i][j]->GetXaxis()->SetTitle("Missing Mass (p #pi^{+} #pi^{-}) GeV");
		sigHistpi0CosX[i][j]->GetYaxis()->SetTitle("cos #theta_{x}");
		bgHistpi0CosX[i][j]->GetXaxis()->SetTitle("Missing Mass (p #pi^{+} #pi^{-}) GeV");
		bgHistpi0CosX[i][j]->GetYaxis()->SetTitle("cos #theta_{x}");

		allHistpi0CosY[i][j] = new TH2F("All events",histTitle.str().c_str(), 75, 0.05, 0.22, 75, -1.0, 1.0);
		sigHistpi0CosY[i][j] = new TH2F("Integrated Signal Weight",histTitle.str().c_str(), 75, 0.05, 0.22, 75, -1.0, 1.0);
		bgHistpi0CosY[i][j] = new TH2F("Integrated Background Weight",histTitle.str().c_str(), 75, 0.05, 0.22, 75, -1.0, 1.0);
		allHistpi0CosY[i][j]->GetXaxis()->SetTitle("Missing Mass (p #pi^{+} #pi^{-}) GeV");
	    allHistpi0CosY[i][j]->GetYaxis()->SetTitle("cos #theta_{y}");
		sigHistpi0CosY[i][j]->GetXaxis()->SetTitle("Missing Mass (p #pi^{+} #pi^{-}) GeV");
		sigHistpi0CosY[i][j]->GetYaxis()->SetTitle("cos #theta_{y}");
		bgHistpi0CosY[i][j]->GetXaxis()->SetTitle("Missing Mass (p #pi^{+} #pi^{-}) GeV");
		bgHistpi0CosY[i][j]->GetYaxis()->SetTitle("cos #theta_{y}");

		allHistpi0CosZ[i][j] = new TH2F("All events",histTitle.str().c_str(), 75, 0.05, 0.22, 75, -1.0, 1.0);
		sigHistpi0CosZ[i][j] = new TH2F("Integrated Signal Weight",histTitle.str().c_str(), 75, 0.05, 0.22, 75, -1.0, 1.0);
		bgHistpi0CosZ[i][j] = new TH2F("Integrated Background Weight",histTitle.str().c_str(), 75, 0.05, 0.22, 75, -1.0, 1.0);
		allHistpi0CosZ[i][j]->GetXaxis()->SetTitle("Missing Mass (p #pi^{+} #pi^{-}) GeV");
	    allHistpi0CosZ[i][j]->GetYaxis()->SetTitle("cos #theta_{z}");
		sigHistpi0CosZ[i][j]->GetXaxis()->SetTitle("Missing Mass (p #pi^{+} #pi^{-}) GeV");
		sigHistpi0CosZ[i][j]->GetYaxis()->SetTitle("cos #theta_{z}");
		bgHistpi0CosZ[i][j]->GetXaxis()->SetTitle("Missing Mass (p #pi^{+} #pi^{-}) GeV");
		bgHistpi0CosZ[i][j]->GetYaxis()->SetTitle("cos #theta_{z}");
		
		allHistpi0phiK0[i][j] = new TH2F("All events",histTitle.str().c_str(), 75, 0.05, 0.22, 75, -3.14, 3.14);
		sigHistpi0phiK0[i][j] = new TH2F("Integrated Signal Weight",histTitle.str().c_str(), 75, 0.05, 0.22, 75, -3.14, 3.14);
		bgHistpi0phiK0[i][j] = new TH2F("Integrated Background Weight",histTitle.str().c_str(), 75, 0.05, 0.22, 75, -3.14, 3.14);
		allHistpi0phiK0[i][j]->GetXaxis()->SetTitle("Missing Mass (p #pi^{+} #pi^{-}) GeV");
	    allHistpi0phiK0[i][j]->GetYaxis()->SetTitle("#phi_{K0}");
		sigHistpi0phiK0[i][j]->GetXaxis()->SetTitle("Missing Mass (p #pi^{+} #pi^{-}) GeV");
		sigHistpi0phiK0[i][j]->GetYaxis()->SetTitle("#phi_{K0}");
		bgHistpi0phiK0[i][j]->GetXaxis()->SetTitle("Missing Mass (p #pi^{+} #pi^{-}) GeV");
		bgHistpi0phiK0[i][j]->GetYaxis()->SetTitle("#phi_{K0}");

		allHistpi0pol[i][j] = new TH2F("All events",histTitle.str().c_str(), 75, 0.05, 0.22, 75, 0.6, 1.0);
		sigHistpi0pol[i][j] = new TH2F("Integrated Signal Weight",histTitle.str().c_str(), 75, 0.05, 0.22, 75, 0.6, 1.0);
		bgHistpi0pol[i][j] = new TH2F("Integrated Background Weight",histTitle.str().c_str(), 75, 0.05, 0.22, 75, 0.6, 1.0);
		allHistpi0pol[i][j]->GetXaxis()->SetTitle("Missing Mass (p #pi^{+} #pi^{-}) GeV");
	    allHistpi0pol[i][j]->GetYaxis()->SetTitle("Polarisation degree");
		sigHistpi0pol[i][j]->GetXaxis()->SetTitle("Missing Mass (p #pi^{+} #pi^{-}) GeV");
		sigHistpi0pol[i][j]->GetYaxis()->SetTitle("Polarisation degree");
		bgHistpi0pol[i][j]->GetXaxis()->SetTitle("Missing Mass (p #pi^{+} #pi^{-}) GeV");
		bgHistpi0pol[i][j]->GetYaxis()->SetTitle("Polarisation degree");		


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
	
	// Egamma
	sigHistEgAll = new TH1F("Integrated Signal Weight","All events", 100, 1.0, 2.2);
	sigHistEgAll->GetXaxis()->SetTitle("E_{#gamma} (GeV)");
	sigHistEgAll->SetLineWidth(2);
	bgHistEgAll = new TH1F("Integrated BG Weight","All events", 100, 1.0, 2.2);
	bgHistEgAll->GetXaxis()->SetTitle("E_{#gamma} (GeV)");		
	bgHistEgAll->SetLineWidth(2);			

	// t
	sigHisttAll = new TH1F("Integrated Signal Weight","All events", 100, -0.3, 2.2);
	sigHisttAll->GetXaxis()->SetTitle("t (GeV/c)");
	sigHisttAll->SetLineWidth(2);
	bgHisttAll = new TH1F("Integrated BG Weight","All events", 100, -0.3, 2.2);
	bgHisttAll->GetXaxis()->SetTitle("t (GeV/c)");		
	bgHisttAll->SetLineWidth(2);			

	// costh
	sigHistCosthAll = new TH1F("Integrated Signal Weight","All events", 75, -1.0, 1.0);
	sigHistCosthAll->GetXaxis()->SetTitle("cos #theta_{K0}");
	sigHistCosthAll->SetLineWidth(2);
	bgHistCosthAll = new TH1F("Integrated BG Weight","All events", 75, -1.0, 1.0);
	bgHistCosthAll->GetXaxis()->SetTitle("cos #theta_{K0}");		
	bgHistCosthAll->SetLineWidth(2);			

  
  // correlation
	allHistK0CosXAll = new TH2F("All events","All events", 75, 0.44, 0.56, 75, -1.0, 1.0);
	sigHistK0CosXAll = new TH2F("Integrated Signal Weight","All events", 75, 0.44, 0.56, 75, -1.0, 1.0);
	bgHistK0CosXAll = new TH2F("Integrated Background Weight","All events", 75, 0.44, 0.56, 75, -1.0, 1.0);
	allHistK0CosXAll->GetXaxis()->SetTitle("Mass(#pi^{+} #pi^{-}) GeV");
	allHistK0CosXAll->GetYaxis()->SetTitle("cos #theta_{x}");
	sigHistK0CosXAll->GetXaxis()->SetTitle("Mass(#pi^{+} #pi^{-}) GeV");
	sigHistK0CosXAll->GetYaxis()->SetTitle("cos #theta_{x}");
	bgHistK0CosXAll->GetXaxis()->SetTitle("Mass(#pi^{+} #pi^{-}) GeV");
	bgHistK0CosXAll->GetYaxis()->SetTitle("cos #theta_{x}");

	allHistK0CosYAll = new TH2F("All events","All events", 75, 0.44, 0.56, 75, -1.0, 1.0);
	sigHistK0CosYAll = new TH2F("Integrated Signal Weight","All events", 75, 0.44, 0.56, 75, -1.0, 1.0);
	bgHistK0CosYAll = new TH2F("Integrated Background Weight","All events", 75, 0.44, 0.56, 75, -1.0, 1.0);
	allHistK0CosYAll->GetXaxis()->SetTitle("Mass(#pi^{+} #pi^{-}) GeV");
	allHistK0CosYAll->GetYaxis()->SetTitle("cos #theta_{y}");
	sigHistK0CosYAll->GetXaxis()->SetTitle("Mass(#pi^{+} #pi^{-}) GeV");
	sigHistK0CosYAll->GetYaxis()->SetTitle("cos #theta_{y}");
	bgHistK0CosYAll->GetXaxis()->SetTitle("Mass(#pi^{+} #pi^{-}) GeV");
	bgHistK0CosYAll->GetYaxis()->SetTitle("cos #theta_{y}");

	allHistK0CosZAll = new TH2F("All events","All events", 75, 0.44, 0.56, 75, -1.0, 1.0);
	sigHistK0CosZAll = new TH2F("Integrated Signal Weight","All events", 75, 0.44, 0.56, 75, -1.0, 1.0);
	bgHistK0CosZAll = new TH2F("Integrated Background Weight","All events", 75, 0.44, 0.56, 75, -1.0, 1.0);
	allHistK0CosZAll->GetXaxis()->SetTitle("Mass(#pi^{+} #pi^{-}) GeV");
	allHistK0CosZAll->GetYaxis()->SetTitle("cos #theta_{z}");
	sigHistK0CosZAll->GetXaxis()->SetTitle("Mass(#pi^{+} #pi^{-}) GeV");
	sigHistK0CosZAll->GetYaxis()->SetTitle("cos #theta_{z}");
	bgHistK0CosZAll->GetXaxis()->SetTitle("Mass(#pi^{+} #pi^{-}) GeV");
	bgHistK0CosZAll->GetYaxis()->SetTitle("cos #theta_{z}");
	
	allHistK0phiK0All = new TH2F("All events","All events", 75, 0.44, 0.56, 75, -3.14, 3.14);
	sigHistK0phiK0All = new TH2F("Integrated Signal Weight","All events", 75, 0.44, 0.56, 75, -3.14, 3.14);
	bgHistK0phiK0All = new TH2F("Integrated Background Weight","All events", 75, 0.44, 0.56, 75, -3.14, 3.14);
	allHistK0phiK0All->GetXaxis()->SetTitle("Mass(#pi^{+} #pi^{-}) GeV");
	allHistK0phiK0All->GetYaxis()->SetTitle("#phi_{K0}");
	sigHistK0phiK0All->GetXaxis()->SetTitle("Mass(#pi^{+} #pi^{-}) GeV");
	sigHistK0phiK0All->GetYaxis()->SetTitle("#phi_{K0}");
	bgHistK0phiK0All->GetXaxis()->SetTitle("Mass(#pi^{+} #pi^{-}) GeV");
	bgHistK0phiK0All->GetYaxis()->SetTitle("#phi_{K0}");

	allHistK0polAll = new TH2F("All events","All events", 75, 0.44, 0.56, 75, 0.6, 1.0);
	sigHistK0polAll = new TH2F("Integrated Signal Weight","All events", 75, 0.44, 0.56, 75, 0.6, 1.0);
	bgHistK0polAll = new TH2F("Integrated Background Weight","All events", 75, 0.44, 0.56, 75, 0.6, 1.0);
	allHistK0polAll->GetXaxis()->SetTitle("Mass(#pi^{+} #pi^{-}) GeV");
	allHistK0polAll->GetYaxis()->SetTitle("Polarisation degree");
	sigHistK0polAll->GetXaxis()->SetTitle("Mass(#pi^{+} #pi^{-}) GeV");
	sigHistK0polAll->GetYaxis()->SetTitle("Polarisation degree");
	bgHistK0polAll->GetXaxis()->SetTitle("Mass(#pi^{+} #pi^{-}) GeV");
	bgHistK0polAll->GetYaxis()->SetTitle("Polarisation degree");

	allHistpi0CosXAll = new TH2F("All events","All events", 75, 0.05, 0.22, 75, -1.0, 1.0);
	sigHistpi0CosXAll = new TH2F("Integrated Signal Weight","All events", 75, 0.05, 0.22, 75, -1.0, 1.0);
	bgHistpi0CosXAll = new TH2F("Integrated Background Weight","All events", 75, 0.05, 0.22, 75, -1.0, 1.0);
	allHistpi0CosXAll->GetXaxis()->SetTitle("Missing Mass (p #pi^{+} #pi^{-}) GeV");
	allHistpi0CosXAll->GetYaxis()->SetTitle("cos #theta_{x}");
	sigHistpi0CosXAll->GetXaxis()->SetTitle("Missing Mass (p #pi^{+} #pi^{-}) GeV");
	sigHistpi0CosXAll->GetYaxis()->SetTitle("cos #theta_{x}");
	bgHistpi0CosXAll->GetXaxis()->SetTitle("Missing Mass (p #pi^{+} #pi^{-}) GeV");
	bgHistpi0CosXAll->GetYaxis()->SetTitle("cos #theta_{x}");

	allHistpi0CosYAll = new TH2F("All events","All events", 75, 0.05, 0.22, 75, -1.0, 1.0);
	sigHistpi0CosYAll = new TH2F("Integrated Signal Weight","All events", 75, 0.05, 0.22, 75, -1.0, 1.0);
	bgHistpi0CosYAll = new TH2F("Integrated Background Weight","All events", 75, 0.05, 0.22, 75, -1.0, 1.0);
	allHistpi0CosYAll->GetXaxis()->SetTitle("Missing Mass (p #pi^{+} #pi^{-}) GeV");
	allHistpi0CosYAll->GetYaxis()->SetTitle("cos #theta_{y}");
	sigHistpi0CosYAll->GetXaxis()->SetTitle("Missing Mass (p #pi^{+} #pi^{-}) GeV");
	sigHistpi0CosYAll->GetYaxis()->SetTitle("cos #theta_{y}");
	bgHistpi0CosYAll->GetXaxis()->SetTitle("Missing Mass (p #pi^{+} #pi^{-}) GeV");
	bgHistpi0CosYAll->GetYaxis()->SetTitle("cos #theta_{y}");

	allHistpi0CosZAll = new TH2F("All events","All events", 75, 0.05, 0.22, 75, -1.0, 1.0);
	sigHistpi0CosZAll = new TH2F("Integrated Signal Weight","All events", 75, 0.05, 0.22, 75, -1.0, 1.0);
	bgHistpi0CosZAll = new TH2F("Integrated Background Weight","All events", 75, 0.05, 0.22, 75, -1.0, 1.0);
	allHistpi0CosZAll->GetXaxis()->SetTitle("Missing Mass (p #pi^{+} #pi^{-}) GeV");
	allHistpi0CosZAll->GetYaxis()->SetTitle("cos #theta_{z}");
	sigHistpi0CosZAll->GetXaxis()->SetTitle("Missing Mass (p #pi^{+} #pi^{-}) GeV");
	sigHistpi0CosZAll->GetYaxis()->SetTitle("cos #theta_{z}");
	bgHistpi0CosZAll->GetXaxis()->SetTitle("Missing Mass (p #pi^{+} #pi^{-}) GeV");
	bgHistpi0CosZAll->GetYaxis()->SetTitle("cos #theta_{z}");
	
	allHistpi0phiK0All = new TH2F("All events","All events", 75, 0.05, 0.22, 75, -3.14, 3.14);
	sigHistpi0phiK0All = new TH2F("Integrated Signal Weight","All events", 75, 0.05, 0.22, 75, -3.14, 3.14);
	bgHistpi0phiK0All = new TH2F("Integrated Background Weight","All events", 75, 0.05, 0.22, 75, -3.14, 3.14);
	allHistpi0phiK0All->GetXaxis()->SetTitle("Missing Mass (p #pi^{+} #pi^{-}) GeV");
	allHistpi0phiK0All->GetYaxis()->SetTitle("#phi_{K0}");
	sigHistpi0phiK0All->GetXaxis()->SetTitle("Missing Mass (p #pi^{+} #pi^{-}) GeV");
	sigHistpi0phiK0All->GetYaxis()->SetTitle("#phi_{K0}");
	bgHistpi0phiK0All->GetXaxis()->SetTitle("Missing Mass (p #pi^{+} #pi^{-}) GeV");
	bgHistpi0phiK0All->GetYaxis()->SetTitle("#phi_{K0}");

	allHistpi0polAll = new TH2F("All events","All events", 75, 0.05, 0.22, 75, 0.6, 1.0);
	sigHistpi0polAll = new TH2F("Integrated Signal Weight","All events", 75, 0.05, 0.22, 75, 0.6, 1.0);
	bgHistpi0polAll = new TH2F("Integrated Background Weight","All events", 75, 0.05, 0.22, 75, 0.6, 1.0);
	allHistpi0polAll->GetXaxis()->SetTitle("Missing Mass (p #pi^{+} #pi^{-}) GeV");
	allHistpi0polAll->GetYaxis()->SetTitle("Polarisation degree");
	sigHistpi0polAll->GetXaxis()->SetTitle("Missing Mass (p #pi^{+} #pi^{-}) GeV");
	sigHistpi0polAll->GetYaxis()->SetTitle("Polarisation degree");
	bgHistpi0polAll->GetXaxis()->SetTitle("Missing Mass (p #pi^{+} #pi^{-}) GeV");
	bgHistpi0polAll->GetYaxis()->SetTitle("Polarisation degree");		
  
  
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
      
      // Egamma
      sigHistEg[currentEBin][currentThBin]->Fill(Egamma,wts[currentEBin]->GetWeight("Signal"));
      bgHistEg[currentEBin][currentThBin]->Fill(Egamma,wts[currentEBin]->GetWeight("BG"));

      // t
      sigHistt[currentEBin][currentThBin]->Fill(t,wts[currentEBin]->GetWeight("Signal"));
      bgHistt[currentEBin][currentThBin]->Fill(t,wts[currentEBin]->GetWeight("BG"));

      // costh
      sigHistCosth[currentEBin][currentThBin]->Fill(costhK0CMS,wts[currentEBin]->GetWeight("Signal"));
      bgHistCosth[currentEBin][currentThBin]->Fill(costhK0CMS,wts[currentEBin]->GetWeight("BG"));
      
      
      // sigHistPhiK0Para
      if (polState==1) {
		sigHistPhiK0Para[currentEBin][currentThBin]->Fill(phiK0,wts[currentEBin]->GetWeight("Signal"));
		bgHistPhiK0Para[currentEBin][currentThBin]->Fill(phiK0,wts[currentEBin]->GetWeight("BG"));
	  }
      
      // sigHistPhiK0Perp
      if (polState==-1) {
		sigHistPhiK0Perp[currentEBin][currentThBin]->Fill(phiK0,wts[currentEBin]->GetWeight("Signal"));
		bgHistPhiK0Perp[currentEBin][currentThBin]->Fill(phiK0,wts[currentEBin]->GetWeight("BG"));
	  }
	  
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

      // Egamma
      sigHistEgAll->Fill(Egamma,wts[currentEBin]->GetWeight("Signal"));
      bgHistEgAll->Fill(Egamma,wts[currentEBin]->GetWeight("BG"));

      // t
      sigHisttAll->Fill(t,wts[currentEBin]->GetWeight("Signal"));
      bgHisttAll->Fill(t,wts[currentEBin]->GetWeight("BG"));

      // costh
      sigHistCosthAll->Fill(costhK0CMS,wts[currentEBin]->GetWeight("Signal"));
      bgHistCosthAll->Fill(costhK0CMS,wts[currentEBin]->GetWeight("BG"));

      
      // correlation
	  sigHistK0CosX[currentEBin][currentThBin]->Fill(M_pip_pim,cosX,wts[currentEBin]->GetWeight("Signal"));
      bgHistK0CosX[currentEBin][currentThBin]->Fill(M_pip_pim,cosX,wts[currentEBin]->GetWeight("BG"));
      allHistK0CosX[currentEBin][currentThBin]->Fill(M_pip_pim,cosX,wts[currentEBin]->GetWeight("All"));
	  sigHistK0CosXAll->Fill(M_pip_pim,cosX,wts[currentEBin]->GetWeight("Signal"));
      bgHistK0CosXAll->Fill(M_pip_pim,cosX,wts[currentEBin]->GetWeight("BG"));
      allHistK0CosXAll->Fill(M_pip_pim,cosX,wts[currentEBin]->GetWeight("All"));

	  sigHistK0CosY[currentEBin][currentThBin]->Fill(M_pip_pim,cosY,wts[currentEBin]->GetWeight("Signal"));
      bgHistK0CosY[currentEBin][currentThBin]->Fill(M_pip_pim,cosY,wts[currentEBin]->GetWeight("BG"));
      allHistK0CosY[currentEBin][currentThBin]->Fill(M_pip_pim,cosY,wts[currentEBin]->GetWeight("All"));
	  sigHistK0CosYAll->Fill(M_pip_pim,cosY,wts[currentEBin]->GetWeight("Signal"));
      bgHistK0CosYAll->Fill(M_pip_pim,cosY,wts[currentEBin]->GetWeight("BG"));
      allHistK0CosYAll->Fill(M_pip_pim,cosY,wts[currentEBin]->GetWeight("All"));
      
	  sigHistK0CosZ[currentEBin][currentThBin]->Fill(M_pip_pim,cosZ,wts[currentEBin]->GetWeight("Signal"));
      bgHistK0CosZ[currentEBin][currentThBin]->Fill(M_pip_pim,cosZ,wts[currentEBin]->GetWeight("BG"));
      allHistK0CosZ[currentEBin][currentThBin]->Fill(M_pip_pim,cosZ,wts[currentEBin]->GetWeight("All"));
	  sigHistK0CosZAll->Fill(M_pip_pim,cosZ,wts[currentEBin]->GetWeight("Signal"));
      bgHistK0CosZAll->Fill(M_pip_pim,cosZ,wts[currentEBin]->GetWeight("BG"));
      allHistK0CosZAll->Fill(M_pip_pim,cosZ,wts[currentEBin]->GetWeight("All"));
      
	  sigHistK0phiK0[currentEBin][currentThBin]->Fill(M_pip_pim,phiK0,wts[currentEBin]->GetWeight("Signal"));
      bgHistK0phiK0[currentEBin][currentThBin]->Fill(M_pip_pim,phiK0,wts[currentEBin]->GetWeight("BG"));
      allHistK0phiK0[currentEBin][currentThBin]->Fill(M_pip_pim,phiK0,wts[currentEBin]->GetWeight("All"));
	  sigHistK0phiK0All->Fill(M_pip_pim,phiK0,wts[currentEBin]->GetWeight("Signal"));
      bgHistK0phiK0All->Fill(M_pip_pim,phiK0,wts[currentEBin]->GetWeight("BG"));
      allHistK0phiK0All->Fill(M_pip_pim,phiK0,wts[currentEBin]->GetWeight("All"));
      
	  sigHistK0pol[currentEBin][currentThBin]->Fill(M_pip_pim,pol,wts[currentEBin]->GetWeight("Signal"));
      bgHistK0pol[currentEBin][currentThBin]->Fill(M_pip_pim,pol,wts[currentEBin]->GetWeight("BG"));
      allHistK0pol[currentEBin][currentThBin]->Fill(M_pip_pim,pol,wts[currentEBin]->GetWeight("All"));
	  sigHistK0polAll->Fill(M_pip_pim,pol,wts[currentEBin]->GetWeight("Signal"));
      bgHistK0polAll->Fill(M_pip_pim,pol,wts[currentEBin]->GetWeight("BG"));
      allHistK0polAll->Fill(M_pip_pim,pol,wts[currentEBin]->GetWeight("All"));
      
	  sigHistpi0CosX[currentEBin][currentThBin]->Fill(MM_p_pip_pim,cosX,wts[currentEBin]->GetWeight("Signal"));
      bgHistpi0CosX[currentEBin][currentThBin]->Fill(MM_p_pip_pim,cosX,wts[currentEBin]->GetWeight("BG"));
      allHistpi0CosX[currentEBin][currentThBin]->Fill(MM_p_pip_pim,cosX,wts[currentEBin]->GetWeight("All"));
	  sigHistpi0CosXAll->Fill(MM_p_pip_pim,cosX,wts[currentEBin]->GetWeight("Signal"));
      bgHistpi0CosXAll->Fill(MM_p_pip_pim,cosX,wts[currentEBin]->GetWeight("BG"));
      allHistpi0CosXAll->Fill(MM_p_pip_pim,cosX,wts[currentEBin]->GetWeight("All"));

	  sigHistpi0CosY[currentEBin][currentThBin]->Fill(MM_p_pip_pim,cosY,wts[currentEBin]->GetWeight("Signal"));
      bgHistpi0CosY[currentEBin][currentThBin]->Fill(MM_p_pip_pim,cosY,wts[currentEBin]->GetWeight("BG"));
      allHistpi0CosY[currentEBin][currentThBin]->Fill(MM_p_pip_pim,cosY,wts[currentEBin]->GetWeight("All"));
	  sigHistpi0CosYAll->Fill(MM_p_pip_pim,cosY,wts[currentEBin]->GetWeight("Signal"));
      bgHistpi0CosYAll->Fill(MM_p_pip_pim,cosY,wts[currentEBin]->GetWeight("BG"));
      allHistpi0CosYAll->Fill(MM_p_pip_pim,cosY,wts[currentEBin]->GetWeight("All"));
      
	  sigHistpi0CosZ[currentEBin][currentThBin]->Fill(MM_p_pip_pim,cosZ,wts[currentEBin]->GetWeight("Signal"));
      bgHistpi0CosZ[currentEBin][currentThBin]->Fill(MM_p_pip_pim,cosZ,wts[currentEBin]->GetWeight("BG"));
      allHistpi0CosZ[currentEBin][currentThBin]->Fill(MM_p_pip_pim,cosZ,wts[currentEBin]->GetWeight("All"));
	  sigHistpi0CosZAll->Fill(MM_p_pip_pim,cosZ,wts[currentEBin]->GetWeight("Signal"));
      bgHistpi0CosZAll->Fill(MM_p_pip_pim,cosZ,wts[currentEBin]->GetWeight("BG"));
      allHistpi0CosZAll->Fill(MM_p_pip_pim,cosZ,wts[currentEBin]->GetWeight("All"));
      
	  sigHistpi0phiK0[currentEBin][currentThBin]->Fill(MM_p_pip_pim,phiK0,wts[currentEBin]->GetWeight("Signal"));
      bgHistpi0phiK0[currentEBin][currentThBin]->Fill(MM_p_pip_pim,phiK0,wts[currentEBin]->GetWeight("BG"));
      allHistpi0phiK0[currentEBin][currentThBin]->Fill(MM_p_pip_pim,phiK0,wts[currentEBin]->GetWeight("All"));
	  sigHistpi0phiK0All->Fill(MM_p_pip_pim,phiK0,wts[currentEBin]->GetWeight("Signal"));
      bgHistpi0phiK0All->Fill(MM_p_pip_pim,phiK0,wts[currentEBin]->GetWeight("BG"));
      allHistpi0phiK0All->Fill(MM_p_pip_pim,phiK0,wts[currentEBin]->GetWeight("All"));
      
	  sigHistpi0pol[currentEBin][currentThBin]->Fill(MM_p_pip_pim,pol,wts[currentEBin]->GetWeight("Signal"));
      bgHistpi0pol[currentEBin][currentThBin]->Fill(MM_p_pip_pim,pol,wts[currentEBin]->GetWeight("BG"));
      allHistpi0pol[currentEBin][currentThBin]->Fill(MM_p_pip_pim,pol,wts[currentEBin]->GetWeight("All"));
	  sigHistpi0polAll->Fill(MM_p_pip_pim,pol,wts[currentEBin]->GetWeight("Signal"));
      bgHistpi0polAll->Fill(MM_p_pip_pim,pol,wts[currentEBin]->GetWeight("BG"));
      allHistpi0polAll->Fill(MM_p_pip_pim,pol,wts[currentEBin]->GetWeight("All"));      
    }
  }
  
  // Create asymmetries sigHistPhiK0Asym
  gStyle->SetOptFit(10111);
  gStyle->SetOptStat(0);
  
  // Signal
  std::string xArrString = "masx=[";
  std::string yArrString = "masy=[";
  std::string yErrArrString = "masy_err=[";
  // BG
  std::string xArrStringBG = "masbx=[";
  std::string yArrStringBG = "masby=[";
  std::string yErrArrStringBG = "masby_err=[";  
  
  for (Int_t i=0; i<4; i++) {
	  
	std::string xString = "[";
	std::string yString = "[";
	std::string yErrString = "[";
	std::string xStringBG = "[";
	std::string yStringBG = "[";
	std::string yErrStringBG = "[";
		  
	for (Int_t j=0; j<iBinNums[i]; j++) {
		
		int rebin_n = 8;
		
		std::stringstream histTitle;
		histTitle << "E_{#gamma} " << eBinLimits[i] << " to " << eBinLimits[i+1] << " GeV   cos(#theta_{K^{0}}) " << thBinLimits[i][j] << " to " << thBinLimits[i][j+1];
		
		sigHistPhiK0Para[i][j]->Sumw2();
		sigHistPhiK0Perp[i][j]->Sumw2();
		sigHistPhiK0Para[i][j]->Rebin(rebin_n);
		sigHistPhiK0Perp[i][j]->Rebin(rebin_n);
			
		sigHistPhiK0Asym[i][j] = sigHistPhiK0Para[i][j]->GetAsymmetry(sigHistPhiK0Perp[i][j]);
		sigHistPhiK0Asym[i][j]->SetTitle(histTitle.str().c_str());
		
		TF1* cos2phiSig=new TF1("cos2phiSig","[0]-[1]*0.7*cos(2*x)",-3.14,3.14); 
		sigHistPhiK0Asym[i][j]->Fit("cos2phiSig");
		
		double binCentre = (thBinLimits[i][j]+thBinLimits[i][j+1]) / 2.0;
		double graphValue = cos2phiSig->GetParameter(1);
		xString = xString + binCentre + ",";
		yString = yString + graphValue + ",";
		yErrString = yErrString + cos2phiSig->GetParError(1) + ",";		
		
		sigHistPhiK0Asym[i][j]->SetMinimum(-1.5);
		sigHistPhiK0Asym[i][j]->SetMaximum(1.5);
		sigHistPhiK0Asym[i][j]->Draw("");
		
		TString outFilename = outdir+"sigHistPhiK0Asym"+i+j+".png";
		c1->SaveAs(outFilename);		
		
		bgHistPhiK0Para[i][j]->Sumw2();
		bgHistPhiK0Perp[i][j]->Sumw2();
		bgHistPhiK0Para[i][j]->Rebin(rebin_n);
		bgHistPhiK0Perp[i][j]->Rebin(rebin_n);
			
		bgHistPhiK0Asym[i][j] = bgHistPhiK0Para[i][j]->GetAsymmetry(bgHistPhiK0Perp[i][j]);
		bgHistPhiK0Asym[i][j]->SetTitle(histTitle.str().c_str());
		
		TF1* cos2phiBg=new TF1("cos2phiBg","[0]-[1]*0.7*cos(2*x)",-3.14,3.14); 
		bgHistPhiK0Asym[i][j]->Fit("cos2phiBg");	
		
		double graphValueBG = cos2phiBg->GetParameter(1);
		xStringBG = xStringBG + binCentre + ",";
		yStringBG = yStringBG + graphValueBG + ",";
		yErrStringBG = yErrStringBG + cos2phiBg->GetParError(1) + ",";				
		
		bgHistPhiK0Asym[i][j]->SetMinimum(-1.0);
		bgHistPhiK0Asym[i][j]->SetMaximum(1.0);
		bgHistPhiK0Asym[i][j]->Draw("");
		outFilename = outdir+"bgHistPhiK0Asym"+i+j+".png";
		c1->SaveAs(outFilename);
		
	}
	
	yString = yString.substr(0, yString.length()-1) + "]";
	yErrString = yErrString.substr(0, yErrString.length()-1) + "]";
	xString = xString.substr(0, xString.length()-1) + "]";

	xArrString = xArrString + xString +",\n";
	yArrString = yArrString + yString +",\n";
	yErrArrString = yErrArrString + yErrString +",\n";
	
	yStringBG = yStringBG.substr(0, yStringBG.length()-1) + "]";
	yErrStringBG = yErrStringBG.substr(0, yErrStringBG.length()-1) + "]";
	xStringBG = xStringBG.substr(0, xStringBG.length()-1) + "]";

	xArrStringBG = xArrStringBG + xStringBG +",\n";
	yArrStringBG = yArrStringBG + yStringBG +",\n";
	yErrArrStringBG = yErrArrStringBG + yErrStringBG +",\n";	
  }

	yArrString = yArrString.substr(0, yArrString.length()-2) + "]";
	yErrArrString = yErrArrString.substr(0, yErrArrString.length()-2) + "]";
	xArrString = xArrString.substr(0, xArrString.length()-2) + "]";
	
	yArrStringBG = yArrStringBG.substr(0, yArrStringBG.length()-2) + "]";
	yErrArrStringBG = yErrArrStringBG.substr(0, yErrArrStringBG.length()-2) + "]";
	xArrStringBG = xArrStringBG.substr(0, xArrStringBG.length()-2) + "]";	
	
	ofstream outfile;
    outfile.open("ValuesForGraph.txt");
	outfile << xArrString << "\n" << endl;
	outfile << yArrString << "\n" << endl;
	outfile << yErrArrString << "\n" << endl;	
	outfile << "\n" << endl;	
	outfile << xArrStringBG << "\n" << endl;
	outfile << yArrStringBG << "\n" << endl;
	outfile << yErrArrStringBG << "\n" << endl;		
	outfile.close();



  // Save histograms
  gStyle->SetOptStat(1000001);
  // binned
  for (Int_t i=0; i<4; i++) {
	for (Int_t j=0; j<iBinNums[i]; j++) {
		
	  // Fit the Sigma+ mass with gaussian
	  massFunc[i][j] = new TF1("massFunc","gaus", 1.16,1.22);
	  sigHistMM_pip_pim[i][j]->Sumw2();
	  sigHistMM_pip_pim[i][j]->Fit(massFunc[i][j],"R");
		
	  // MM_pip_pim
	  sigHistMM_pip_pim[i][j]->Draw();
	  TString outFilename = outdir+"sigHistMM_pip_pim"+i+j+".png";
	  c1->SaveAs(outFilename);
	  bgHistMM_pip_pim[i][j]->Draw();
	  outFilename = outdir+"bgHistMM_pip_pim"+i+j+".png";
	  c1->SaveAs(outFilename);

	  // Fit the pi0 mass with gaussian
	  massFunc[i][j] = new TF1("massFunc","gaus", 0.09,0.16);
	  sigHistMM_p_pip_pim[i][j]->Sumw2();
	  sigHistMM_p_pip_pim[i][j]->Fit(massFunc[i][j],"R");
	  
	  // MM_p_pip_pim
	  sigHistMM_p_pip_pim[i][j]->Draw();
	  outFilename = outdir+"sigHistMM_p_pip_pim"+i+j+".png";
	  c1->SaveAs(outFilename);
	  bgHistMM_p_pip_pim[i][j]->Draw();
	  outFilename = outdir+"bgHistMM_p_pip_pim"+i+j+".png";
	  c1->SaveAs(outFilename);
	  
	  // Fit the K0 mass with gaussian
	  massFunc[i][j] = new TF1("massFunc","gaus", 0.49,0.505);
	  sigHistM_pip_pim[i][j]->Sumw2();
	  sigHistM_pip_pim[i][j]->Fit(massFunc[i][j],"R");

	  // M_pip_pim
	  sigHistM_pip_pim[i][j]->Draw();
	  outFilename = outdir+"sigHistM_pip_pim"+i+j+".png";
	  c1->SaveAs(outFilename);
	  bgHistM_pip_pim[i][j]->Draw();
	  outFilename = outdir+"bgHistM_pip_pim"+i+j+".png";
	  c1->SaveAs(outFilename);	  

	  // MM_p
	  sigHistMM_p[i][j]->Draw();
	  outFilename = outdir+"sigHistMM_p"+i+j+".png";
	  c1->SaveAs(outFilename);
	  bgHistMM_p[i][j]->Draw();
	  outFilename = outdir+"bgHistMM_p"+i+j+".png";
	  c1->SaveAs(outFilename);
	  
	  // cosX
	  sigHistCosX[i][j]->Draw();
	  outFilename = outdir+"sigHistCosX"+i+j+".png";
	  c1->SaveAs(outFilename);
	  bgHistCosX[i][j]->Draw();
	  outFilename = outdir+"bgHistCosX"+i+j+".png";
	  c1->SaveAs(outFilename);

	  // cosY
	  sigHistCosY[i][j]->Draw();
	  outFilename = outdir+"sigHistCosY"+i+j+".png";
	  c1->SaveAs(outFilename);
	  bgHistCosY[i][j]->Draw("");
	  outFilename = outdir+"bgHistCosY"+i+j+".png";
	  c1->SaveAs(outFilename);
	  
	  // cosZ
	  sigHistCosZ[i][j]->Draw("");
	  outFilename = outdir+"sigHistCosZ"+i+j+".png";
	  c1->SaveAs(outFilename);
	  bgHistCosZ[i][j]->Draw("");
	  outFilename = outdir+"bgHistCosZ"+i+j+".png";
	  c1->SaveAs(outFilename);	  

	  // Egamma
	  sigHistEg[i][j]->Draw("");
	  outFilename = outdir+"sigHistEg"+i+j+".png";
	  c1->SaveAs(outFilename);
	  bgHistEg[i][j]->Draw("");
	  outFilename = outdir+"bgHistEg"+i+j+".png";
	  c1->SaveAs(outFilename);	  

	  // t
	  sigHistt[i][j]->Draw("");
	  outFilename = outdir+"sigHistt"+i+j+".png";
	  c1->SaveAs(outFilename);
	  bgHistt[i][j]->Draw("");
	  outFilename = outdir+"bgHistt"+i+j+".png";
	  c1->SaveAs(outFilename);	  

	  // costh
	  sigHistCosth[i][j]->Draw("");
	  outFilename = outdir+"sigHistCosth"+i+j+".png";
	  c1->SaveAs(outFilename);
	  bgHistCosth[i][j]->Draw("");
	  outFilename = outdir+"bgHistCosth"+i+j+".png";
	  c1->SaveAs(outFilename);	  


	  // sigHistPhiK0Para
	  sigHistPhiK0Para[i][j]->Draw("");
	  outFilename = outdir+"sigHistPhiK0Para"+i+j+".png";
	  c1->SaveAs(outFilename);
	  bgHistPhiK0Para[i][j]->Draw("");
	  outFilename = outdir+"bgHistPhiK0Para"+i+j+".png";
	  c1->SaveAs(outFilename);	 
	  
	  // sigHistPhiK0Perp
	  sigHistPhiK0Perp[i][j]->Draw("");
	  outFilename = outdir+"sigHistPhiK0Perp"+i+j+".png";
	  c1->SaveAs(outFilename);
	  bgHistPhiK0Perp[i][j]->Draw("");
	  outFilename = outdir+"bgHistPhiK0Perp"+i+j+".png";
	  c1->SaveAs(outFilename);	
	  
	  // correlation
	  allHistK0CosX[i][j]->Draw("COLZ");	
	  outFilename = outdir+"allHistK0CosX"+i+j+".png";
	  c1->SaveAs(outFilename);
	  sigHistK0CosX[i][j]->Draw("COLZ");	
	  outFilename = outdir+"sigHistK0CosX"+i+j+".png";
	  c1->SaveAs(outFilename);
	  bgHistK0CosX[i][j]->Draw("COLZ");	
	  outFilename = outdir+"bgHistK0CosX"+i+j+".png";
	  c1->SaveAs(outFilename);

	  allHistK0CosY[i][j]->Draw("COLZ");	
	  outFilename = outdir+"allHistK0CosY"+i+j+".png";
	  c1->SaveAs(outFilename);
	  sigHistK0CosY[i][j]->Draw("COLZ");	
	  outFilename = outdir+"sigHistK0CosY"+i+j+".png";
	  c1->SaveAs(outFilename);
	  bgHistK0CosY[i][j]->Draw("COLZ");	
	  outFilename = outdir+"bgHistK0CosY"+i+j+".png";
	  c1->SaveAs(outFilename);
	  
	  allHistK0CosZ[i][j]->Draw("COLZ");	
	  outFilename = outdir+"allHistK0CosZ"+i+j+".png";
	  c1->SaveAs(outFilename);
	  sigHistK0CosZ[i][j]->Draw("COLZ");	
	  outFilename = outdir+"sigHistK0CosZ"+i+j+".png";
	  c1->SaveAs(outFilename);
	  bgHistK0CosZ[i][j]->Draw("COLZ");	
	  outFilename = outdir+"bgHistK0CosZ"+i+j+".png";
	  c1->SaveAs(outFilename);
	  
	  allHistK0phiK0[i][j]->Draw("COLZ");	
	  outFilename = outdir+"allHistK0phiK0"+i+j+".png";
	  c1->SaveAs(outFilename);
	  sigHistK0phiK0[i][j]->Draw("COLZ");	
	  outFilename = outdir+"sigHistK0phiK0"+i+j+".png";
	  c1->SaveAs(outFilename);
	  bgHistK0phiK0[i][j]->Draw("COLZ");	
	  outFilename = outdir+"bgHistK0phiK0"+i+j+".png";
	  c1->SaveAs(outFilename);

	  allHistK0pol[i][j]->Draw("COLZ");	
	  outFilename = outdir+"allHistK0pol"+i+j+".png";
	  c1->SaveAs(outFilename);
	  sigHistK0pol[i][j]->Draw("COLZ");	
	  outFilename = outdir+"sigHistK0pol"+i+j+".png";
	  c1->SaveAs(outFilename);
	  bgHistK0pol[i][j]->Draw("COLZ");	
	  outFilename = outdir+"bgHistK0pol"+i+j+".png";
	  c1->SaveAs(outFilename);
	  
	  allHistpi0CosX[i][j]->Draw("COLZ");	
	  outFilename = outdir+"allHistpi0CosX"+i+j+".png";
	  c1->SaveAs(outFilename);
	  sigHistpi0CosX[i][j]->Draw("COLZ");	
	  outFilename = outdir+"sigHistpi0CosX"+i+j+".png";
	  c1->SaveAs(outFilename);
	  bgHistpi0CosX[i][j]->Draw("COLZ");	
	  outFilename = outdir+"bgHistpi0CosX"+i+j+".png";
	  c1->SaveAs(outFilename);

	  allHistpi0CosY[i][j]->Draw("COLZ");	
	  outFilename = outdir+"allHistpi0CosY"+i+j+".png";
	  c1->SaveAs(outFilename);
	  sigHistpi0CosY[i][j]->Draw("COLZ");	
	  outFilename = outdir+"sigHistpi0CosY"+i+j+".png";
	  c1->SaveAs(outFilename);
	  bgHistpi0CosY[i][j]->Draw("COLZ");	
	  outFilename = outdir+"bgHistpi0CosY"+i+j+".png";
	  c1->SaveAs(outFilename);
	  
	  allHistpi0CosZ[i][j]->Draw("COLZ");	
	  outFilename = outdir+"allHistpi0CosZ"+i+j+".png";
	  c1->SaveAs(outFilename);
	  sigHistpi0CosZ[i][j]->Draw("COLZ");	
	  outFilename = outdir+"sigHistpi0CosZ"+i+j+".png";
	  c1->SaveAs(outFilename);
	  bgHistpi0CosZ[i][j]->Draw("COLZ");	
	  outFilename = outdir+"bgHistpi0CosZ"+i+j+".png";
	  c1->SaveAs(outFilename);
	  
	  allHistpi0phiK0[i][j]->Draw("COLZ");	
	  outFilename = outdir+"allHistpi0phiK0"+i+j+".png";
	  c1->SaveAs(outFilename);
	  sigHistpi0phiK0[i][j]->Draw("COLZ");	
	  outFilename = outdir+"sigHistpi0phiK0"+i+j+".png";
	  c1->SaveAs(outFilename);
	  bgHistpi0phiK0[i][j]->Draw("COLZ");	
	  outFilename = outdir+"bgHistpi0phiK0"+i+j+".png";
	  c1->SaveAs(outFilename);

	  allHistpi0pol[i][j]->Draw("COLZ");	
	  outFilename = outdir+"allHistpi0pol"+i+j+".png";
	  c1->SaveAs(outFilename);
	  sigHistpi0pol[i][j]->Draw("COLZ");	
	  outFilename = outdir+"sigHistpi0pol"+i+j+".png";
	  c1->SaveAs(outFilename);
	  bgHistpi0pol[i][j]->Draw("COLZ");	
	  outFilename = outdir+"bgHistpi0pol"+i+j+".png";
	  c1->SaveAs(outFilename);	  
	  
	}
  }
  // unbinned
  
  // Fit the Sigma+ mass with gaussian
  massFunc[0][0] = new TF1("massFunc","gaus", 1.16,1.22);
  sigHistMM_pip_pimAll->Sumw2();
  sigHistMM_pip_pimAll->Fit(massFunc[0][0],"R");
  
  // MM_pip_pim
  sigHistMM_pip_pimAll->Draw("");
  TString outFilename = outdir+"sigHistMM_pip_pimAll.png";
  c1->SaveAs(outFilename);
  bgHistMM_pip_pimAll->Draw("");
  outFilename = outdir+"bgHistMM_pip_pimAll.png";
  c1->SaveAs(outFilename);

  // Fit the pi0 mass with gaussian
  massFunc[0][0] = new TF1("massFunc","gaus", 0.09,0.16);
  sigHistMM_p_pip_pimAll->Sumw2();
  sigHistMM_p_pip_pimAll->Fit(massFunc[0][0],"R");

  // MM_p_pip_pim
  sigHistMM_p_pip_pimAll->Draw("");
  outFilename = outdir+"sigHistMM_p_pip_pimAll.png";
  c1->SaveAs(outFilename);
  bgHistMM_p_pip_pimAll->Draw("");
  outFilename = outdir+"bgHistMM_p_pip_pimAll.png";
  c1->SaveAs(outFilename);

  // Fit the K0 mass with gaussian
  massFunc[0][0] = new TF1("massFunc","gaus", 0.49,0.505);
  sigHistM_pip_pimAll->Sumw2();
  sigHistM_pip_pimAll->Fit(massFunc[0][0],"R");
  
  // M_pip_pim
  sigHistM_pip_pimAll->Draw("");
  outFilename = outdir+"sigHistM_pip_pimAll.png";
  c1->SaveAs(outFilename);
  bgHistM_pip_pimAll->Draw("");
  outFilename = outdir+"bgHistM_pip_pimAll.png";
  c1->SaveAs(outFilename);  

  // MM_p
  sigHistMM_pAll->Draw("");
  outFilename = outdir+"sigHistMM_pAll.png";
  c1->SaveAs(outFilename);
  bgHistMM_pAll->Draw("");
  outFilename = outdir+"bgHistMM_pAll.png";
  c1->SaveAs(outFilename);
  
  // cosX
  sigHistCosXAll->Draw("");
  outFilename = outdir+"sigHistCosXAll.png";
  c1->SaveAs(outFilename);
  bgHistCosXAll->Draw("");
  outFilename = outdir+"bgHistCosXAll.png";
  c1->SaveAs(outFilename);

  // cosY
  sigHistCosYAll->Draw("");
  outFilename = outdir+"sigHistCosYAll.png";
  c1->SaveAs(outFilename);
  bgHistCosYAll->Draw("");
  outFilename = outdir+"bgHistCosYAll.png";
  c1->SaveAs(outFilename);
  
  // cosZ
  sigHistCosZAll->Draw("");
  outFilename = outdir+"sigHistCosZAll.png";
  c1->SaveAs(outFilename);
  bgHistCosZAll->Draw("");
  outFilename = outdir+"bgHistCosZAll.png";
  c1->SaveAs(outFilename);	  

  // Egamma
  sigHistEgAll->Draw("");
  outFilename = outdir+"sigHistEgAll.png";
  c1->SaveAs(outFilename);
  bgHistEgAll->Draw("");
  outFilename = outdir+"bgHistEgAll.png";
  c1->SaveAs(outFilename);	  

  // t
  sigHisttAll->Draw("");
  outFilename = outdir+"sigHisttAll.png";
  c1->SaveAs(outFilename);
  bgHisttAll->Draw("");
  outFilename = outdir+"bgHisttAll.png";
  c1->SaveAs(outFilename);	  

  // costh
  sigHistCosthAll->Draw("");
  outFilename = outdir+"sigHistCosthAll.png";
  c1->SaveAs(outFilename);
  bgHistCosthAll->Draw("");
  outFilename = outdir+"bgHistCosthAll.png";
  c1->SaveAs(outFilename);	

  // correlation  
  allHistK0CosXAll->Draw("COLZ");	
  outFilename = outdir+"allHistK0CosXAll.png";
  c1->SaveAs(outFilename);
  sigHistK0CosXAll->Draw("COLZ");	
  outFilename = outdir+"sigHistK0CosXAll.png";
  c1->SaveAs(outFilename);
  bgHistK0CosXAll->Draw("COLZ");	
  outFilename = outdir+"bgHistK0CosXAll.png";
  c1->SaveAs(outFilename);

  allHistK0CosYAll->Draw("COLZ");	
  outFilename = outdir+"allHistK0CosYAll.png";
  c1->SaveAs(outFilename);
  sigHistK0CosYAll->Draw("COLZ");	
  outFilename = outdir+"sigHistK0CosYAll.png";
  c1->SaveAs(outFilename);
  bgHistK0CosYAll->Draw("COLZ");	
  outFilename = outdir+"bgHistK0CosYAll.png";
  c1->SaveAs(outFilename);
  
  allHistK0CosZAll->Draw("COLZ");	
  outFilename = outdir+"allHistK0CosZAll.png";
  c1->SaveAs(outFilename);
  sigHistK0CosZAll->Draw("COLZ");	
  outFilename = outdir+"sigHistK0CosZAll.png";
  c1->SaveAs(outFilename);
  bgHistK0CosZAll->Draw("COLZ");	
  outFilename = outdir+"bgHistK0CosZAll.png";
  c1->SaveAs(outFilename);
  
  allHistK0phiK0All->Draw("COLZ");	
  outFilename = outdir+"allHistK0phiK0All.png";
  c1->SaveAs(outFilename);
  sigHistK0phiK0All->Draw("COLZ");	
  outFilename = outdir+"sigHistK0phiK0All.png";
  c1->SaveAs(outFilename);
  bgHistK0phiK0All->Draw("COLZ");	
  outFilename = outdir+"bgHistK0phiK0All.png";
  c1->SaveAs(outFilename);
  
  allHistK0polAll->Draw("COLZ");	
  outFilename = outdir+"allHistK0polAll.png";
  c1->SaveAs(outFilename);
  sigHistK0polAll->Draw("COLZ");	
  outFilename = outdir+"sigHistK0polAll.png";
  c1->SaveAs(outFilename);
  bgHistK0polAll->Draw("COLZ");	
  outFilename = outdir+"bgHistK0polAll.png";
  c1->SaveAs(outFilename);
  
allHistpi0CosXAll->Draw("COLZ");	
  outFilename = outdir+"allHistpi0CosXAll.png";
  c1->SaveAs(outFilename);
  sigHistpi0CosXAll->Draw("COLZ");	
  outFilename = outdir+"sigHistpi0CosXAll.png";
  c1->SaveAs(outFilename);
  bgHistpi0CosXAll->Draw("COLZ");	
  outFilename = outdir+"bgHistpi0CosXAll.png";
  c1->SaveAs(outFilename);

  allHistpi0CosYAll->Draw("COLZ");	
  outFilename = outdir+"allHistpi0CosYAll.png";
  c1->SaveAs(outFilename);
  sigHistpi0CosYAll->Draw("COLZ");	
  outFilename = outdir+"sigHistpi0CosYAll.png";
  c1->SaveAs(outFilename);
  bgHistpi0CosYAll->Draw("COLZ");	
  outFilename = outdir+"bgHistpi0CosYAll.png";
  c1->SaveAs(outFilename);
  
  allHistpi0CosZAll->Draw("COLZ");	
  outFilename = outdir+"allHistpi0CosZAll.png";
  c1->SaveAs(outFilename);
  sigHistpi0CosZAll->Draw("COLZ");	
  outFilename = outdir+"sigHistpi0CosZAll.png";
  c1->SaveAs(outFilename);
  bgHistpi0CosZAll->Draw("COLZ");	
  outFilename = outdir+"bgHistpi0CosZAll.png";
  c1->SaveAs(outFilename);
  
  allHistpi0phiK0All->Draw("COLZ");	
  outFilename = outdir+"allHistpi0phiK0All.png";
  c1->SaveAs(outFilename);
  sigHistpi0phiK0All->Draw("COLZ");	
  outFilename = outdir+"sigHistpi0phiK0All.png";
  c1->SaveAs(outFilename);
  bgHistpi0phiK0All->Draw("COLZ");	
  outFilename = outdir+"bgHistpi0phiK0All.png";
  c1->SaveAs(outFilename);
  
  allHistpi0polAll->Draw("COLZ");	
  outFilename = outdir+"allHistpi0polAll.png";
  c1->SaveAs(outFilename);
  sigHistpi0polAll->Draw("COLZ");	
  outFilename = outdir+"sigHistpi0polAll.png";
  c1->SaveAs(outFilename);
  bgHistpi0polAll->Draw("COLZ");	
  outFilename = outdir+"bgHistpi0polAll.png";
  c1->SaveAs(outFilename);
    
}
