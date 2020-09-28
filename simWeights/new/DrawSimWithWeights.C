#include <string>

// Run with
// brufit DrawSimWithWeights.C

  // Simulation
  TString weightsDir = "/home/louise/g8K0Sig/code/simWeights/new/out/";
  TString outdir = "/home/louise/public_html/html/images/sim/weighted/";
  
  // Define bins
  Double_t eBinLimits[] = {1.1, 1.35, 1.6, 1.85, 2.1};
  int iBinNums[] = {6,8,5,2};
  Double_t thBinLimits[4][9] = { {-1.0, -0.622, -0.39, -0.146, 0.054, 0.298, 1.0},
								 {-1.0, -0.465, -0.275, -0.135, 0.005, 0.165, 0.345, 0.535, 1.0},
								 {-1.0, -0.175, 0.035, 0.295, 0.505, 1.0},
								 {-1.0, 0.155, 1.0}
							   };
							   
  // hists							   
  TH1F* wgtHistMM_pip_pim[4][8];
  TH1F* unwHistMM_pip_pim[4][8];
  TH1F* wgtHistMM_pip_pimAll;
  TH1F* unwHistMM_pip_pimAll;
  
  TF1* massFunc[4][8];
  
  TH1F* wgtHistMM_p_pip_pim[4][8];
  TH1F* unwHistMM_p_pip_pim[4][8];
  TH1F* wgtHistMM_p_pip_pimAll;
  TH1F* unwHistMM_p_pip_pimAll;

  TH1F* wgtHistM_pip_pim[4][8];
  TH1F* unwHistM_pip_pim[4][8];
  TH1F* wgtHistM_pip_pimAll;
  TH1F* unwHistM_pip_pimAll;
  
  TH1F* wgtHistMM_p[4][8];
  TH1F* unwHistMM_p[4][8];
  TH1F* wgtHistMM_pAll;
  TH1F* unwHistMM_pAll;
  
  TH1F* wgtHistCosX[4][8];
  TH1F* unwHistCosX[4][8];
  TH1F* wgtHistCosXAll;
  TH1F* unwHistCosXAll;  
  
  TH1F* wgtHistCosY[4][8];
  TH1F* unwHistCosY[4][8];
  TH1F* wgtHistCosYAll;
  TH1F* unwHistCosYAll;  
  
  TH1F* wgtHistCosZ[4][8];
  TH1F* unwHistCosZ[4][8];
  TH1F* wgtHistCosZAll;
  TH1F* unwHistCosZAll;  
  
  TH1F* wgtHistEg[4][8];
  TH1F* unwHistEg[4][8];
  TH1F* wgtHistEgAll;
  TH1F* unwHistEgAll;  
  
  TH1F* wgtHistt[4][8];
  TH1F* unwHistt[4][8];
  TH1F* wgtHisttAll;
  TH1F* unwHisttAll;  
    
  TH1F* wgtHistCosth[4][8];
  TH1F* unwHistCosth[4][8];
  TH1F* wgtHistCosthAll;
  TH1F* unwHistCosthAll;  
  
  
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

void DrawSimWithWeights() {
	  
  Weights* wts[]={new Weights("TotalWeights"),new Weights("TotalWeights"),new Weights("TotalWeights"),new Weights("TotalWeights")};
  // copied from sWeights code which is binned in Egamma - so will just put the same weights file in for all Egamma
  wts[0]->Merge(weightsDir+"impWeights_tE.root","histWeights0.root","impWeights");
  wts[1]->Merge(weightsDir+"impWeights_tE.root","histWeights1.root","impWeights");
  wts[2]->Merge(weightsDir+"impWeights_tE.root","histWeights2.root","impWeights");
  wts[3]->Merge(weightsDir+"impWeights_tE.root","histWeights3.root","impWeights");
  
  cout << weightsDir+"impWeights_tE.root" << endl;

  TCanvas* c1=new TCanvas("c1","c1",800,600); // default canvas
  c1->cd(0); // set default canvas
 
  TChain chain("HSParticles");
  chain.AddFile("/w/work0/home/louise/g8K0Sig/convert_output_MC/filepPi0_all.root");
  Double_t fgID,costhK0CMS, Egamma, t, MM_pip_pim, MM_p_pip_pim, M_pip_pim, MM_p, cosX, cosY, cosZ, phiK0;
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
    
  // Create histograms
  // binned
  for (Int_t i=0; i<4; i++) {
	for (Int_t j=0; j<iBinNums[i]; j++) {
		std::stringstream histTitle;
		histTitle << "E_{#gamma} " << eBinLimits[i] << " to " << eBinLimits[i+1] << " GeV   cos(#theta_{K^{0}}) " << thBinLimits[i][j] << " to " << thBinLimits[i][j+1];
		
		// MM_pip_pim
		wgtHistMM_pip_pim[i][j] = new TH1F("Weighted Simulation",histTitle.str().c_str(), 75, 1.14, 1.26);
		wgtHistMM_pip_pim[i][j]->GetXaxis()->SetTitle("Missing mass(#pi^{+} #pi^{-}) GeV");
		wgtHistMM_pip_pim[i][j]->SetLineWidth(2);
		unwHistMM_pip_pim[i][j] = new TH1F("Unweighted Simulation",histTitle.str().c_str(), 75, 1.14, 1.26);
		unwHistMM_pip_pim[i][j]->GetXaxis()->SetTitle("Missing mass(#pi^{+} #pi^{-}) GeV");		
		unwHistMM_pip_pim[i][j]->SetLineWidth(2);

		// MM_p_pip_pim
		wgtHistMM_p_pip_pim[i][j] = new TH1F("Weighted Simulation",histTitle.str().c_str(), 75, 0.0, 0.25);
		wgtHistMM_p_pip_pim[i][j]->GetXaxis()->SetTitle("Missing mass(p #pi^{+} #pi^{-}) GeV");
		wgtHistMM_p_pip_pim[i][j]->SetLineWidth(2);
		unwHistMM_p_pip_pim[i][j] = new TH1F("Unweighted Simulation",histTitle.str().c_str(), 75, 0.0, 0.25);
		unwHistMM_p_pip_pim[i][j]->GetXaxis()->SetTitle("Missing mass(p #pi^{+} #pi^{-}) GeV");		
		unwHistMM_p_pip_pim[i][j]->SetLineWidth(2);
		
		// M_pip_pim
		wgtHistM_pip_pim[i][j] = new TH1F("Weighted Simulation",histTitle.str().c_str(), 75, 0.44, 0.56);
		wgtHistM_pip_pim[i][j]->GetXaxis()->SetTitle("Mass(#pi^{+} #pi^{-}) GeV");
		wgtHistM_pip_pim[i][j]->SetLineWidth(2);
		unwHistM_pip_pim[i][j] = new TH1F("Unweighted Simulation",histTitle.str().c_str(), 75, 0.44, 0.56);
		unwHistM_pip_pim[i][j]->GetXaxis()->SetTitle("Mass(#pi^{+} #pi^{-}) GeV");		
		unwHistM_pip_pim[i][j]->SetLineWidth(2);		
		
		// MM_p
		wgtHistMM_p[i][j] = new TH1F("Weighted Simulation",histTitle.str().c_str(), 75, 0.5, 1.2);
		wgtHistMM_p[i][j]->GetXaxis()->SetTitle("Missing Mass(p) GeV");
		wgtHistMM_p[i][j]->SetLineWidth(2);
		unwHistMM_p[i][j] = new TH1F("Unweighted Simulation",histTitle.str().c_str(), 75, 0.5, 1.2);
		unwHistMM_p[i][j]->GetXaxis()->SetTitle("Missing Mass(p) GeV");		
		unwHistMM_p[i][j]->SetLineWidth(2);			
		
		// cosX
		wgtHistCosX[i][j] = new TH1F("Weighted Simulation",histTitle.str().c_str(), 75, -1.0, 1.0);
		wgtHistCosX[i][j]->GetXaxis()->SetTitle("cos #theta_{x}");
		wgtHistCosX[i][j]->SetLineWidth(2);
		unwHistCosX[i][j] = new TH1F("Unweighted Simulation",histTitle.str().c_str(), 75, -1.0, 1.0);
		unwHistCosX[i][j]->GetXaxis()->SetTitle("cos #theta_{x}");		
		unwHistCosX[i][j]->SetLineWidth(2);		
		
		// cosY
		wgtHistCosY[i][j] = new TH1F("Weighted Simulation",histTitle.str().c_str(), 75, -1.0, 1.0);
		wgtHistCosY[i][j]->GetXaxis()->SetTitle("cos #theta_{y}");
		wgtHistCosY[i][j]->SetLineWidth(2);
		unwHistCosY[i][j] = new TH1F("Unweighted Simulation",histTitle.str().c_str(), 75, -1.0, 1.0);
		unwHistCosY[i][j]->GetXaxis()->SetTitle("cos #theta_{y}");		
		unwHistCosY[i][j]->SetLineWidth(2);	
		
		// cosZ
		wgtHistCosZ[i][j] = new TH1F("Weighted Simulation",histTitle.str().c_str(), 75, -1.0, 1.0);
		wgtHistCosZ[i][j]->GetXaxis()->SetTitle("cos #theta_{z}");
		wgtHistCosZ[i][j]->SetLineWidth(2);
		unwHistCosZ[i][j] = new TH1F("Unweighted Simulation",histTitle.str().c_str(), 75, -1.0, 1.0);
		unwHistCosZ[i][j]->GetXaxis()->SetTitle("cos #theta_{z}");		
		unwHistCosZ[i][j]->SetLineWidth(2);			
		
		// Egamma
		wgtHistEg[i][j] = new TH1F("Weighted Simulation",histTitle.str().c_str(), 100, 1.0, 2.2);
		wgtHistEg[i][j]->GetXaxis()->SetTitle("E_{#gamma} (GeV)");
		wgtHistEg[i][j]->SetLineWidth(2);
		unwHistEg[i][j] = new TH1F("Unweighted Simulation",histTitle.str().c_str(), 100, 1.0, 2.2);
		unwHistEg[i][j]->GetXaxis()->SetTitle("E_{#gamma} (GeV)");		
		unwHistEg[i][j]->SetLineWidth(2);			

		// t
		wgtHistt[i][j] = new TH1F("Weighted Simulation",histTitle.str().c_str(), 100, -0.3, 2.2);
		wgtHistt[i][j]->GetXaxis()->SetTitle("t (GeV/c)");
		wgtHistt[i][j]->SetLineWidth(2);
		unwHistt[i][j] = new TH1F("Unweighted Simulation",histTitle.str().c_str(), 100, -0.3, 2.2);
		unwHistt[i][j]->GetXaxis()->SetTitle("t (GeV/c)");		
		unwHistt[i][j]->SetLineWidth(2);			

		// costh
		wgtHistCosth[i][j] = new TH1F("Weighted Simulation",histTitle.str().c_str(), 75, -1.0, 1.0);
		wgtHistCosth[i][j]->GetXaxis()->SetTitle("cos #theta_{K0}");
		wgtHistCosth[i][j]->SetLineWidth(2);
		unwHistCosth[i][j] = new TH1F("Unweighted Simulation",histTitle.str().c_str(), 75, -1.0, 1.0);
		unwHistCosth[i][j]->GetXaxis()->SetTitle("cos #theta_{K0}");		
		unwHistCosth[i][j]->SetLineWidth(2);			

	}
  }
  // unbinned
  // MM_pip_pim
  wgtHistMM_pip_pimAll = new TH1F("Weighted Simulation","All events", 75, 1.14, 1.26);
  wgtHistMM_pip_pimAll->GetXaxis()->SetTitle("Missing mass(#pi^{+} #pi^{-}) GeV");
  wgtHistMM_pip_pimAll->SetLineWidth(2);
  unwHistMM_pip_pimAll = new TH1F("Unweighted Simulation","All events", 75, 1.14, 1.26);
  unwHistMM_pip_pimAll->GetXaxis()->SetTitle("Missing mass(#pi^{+} #pi^{-}) GeV");		
  unwHistMM_pip_pimAll->SetLineWidth(2);  
  
  // MM_p_pip_pim
  wgtHistMM_p_pip_pimAll = new TH1F("Weighted Simulation","All events", 75, 0.0, 0.25);
  wgtHistMM_p_pip_pimAll->GetXaxis()->SetTitle("Missing mass(p #pi^{+} #pi^{-}) GeV");
  wgtHistMM_p_pip_pimAll->SetLineWidth(2);
  unwHistMM_p_pip_pimAll = new TH1F("Unweighted Simulation","All events", 75, 0.0, 0.25);
  unwHistMM_p_pip_pimAll->GetXaxis()->SetTitle("Missing mass(p #pi^{+} #pi^{-}) GeV");		
  unwHistMM_p_pip_pimAll->SetLineWidth(2);  
  
  // M_pip_pim
  wgtHistM_pip_pimAll = new TH1F("Weighted Simulation","All events", 75, 0.44, 0.56);
  wgtHistM_pip_pimAll->GetXaxis()->SetTitle("Mass(#pi^{+} #pi^{-}) GeV");
  wgtHistM_pip_pimAll->SetLineWidth(2);
  unwHistM_pip_pimAll = new TH1F("Unweighted Simulation","All events", 75, 0.44, 0.56);
  unwHistM_pip_pimAll->GetXaxis()->SetTitle("Mass(#pi^{+} #pi^{-}) GeV");		
  unwHistM_pip_pimAll->SetLineWidth(2);   

  // MM_p
  wgtHistMM_pAll = new TH1F("Weighted Simulation","All events", 75, 0.5, 1.2);
  wgtHistMM_pAll->GetXaxis()->SetTitle("Missing mass(p) GeV");
  wgtHistMM_pAll->SetLineWidth(2);
  unwHistMM_pAll = new TH1F("Unweighted Simulation","All events", 75, 0.5, 1.2);
  unwHistMM_pAll->GetXaxis()->SetTitle("Missing mass(p) GeV");		
  unwHistMM_pAll->SetLineWidth(2); 
  
   		
	// cosX
	wgtHistCosXAll = new TH1F("Weighted Simulation","All events", 75, -1.0, 1.0);
	wgtHistCosXAll->GetXaxis()->SetTitle("cos #theta_{x}");
	wgtHistCosXAll->SetLineWidth(2);
	unwHistCosXAll = new TH1F("Unweighted Simulation","All events", 75, -1.0, 1.0);
	unwHistCosXAll->GetXaxis()->SetTitle("cos #theta_{x}");		
	unwHistCosXAll->SetLineWidth(2);		

	// cosY
	wgtHistCosYAll = new TH1F("Weighted Simulation","All events", 75, -1.0, 1.0);
	wgtHistCosYAll->GetXaxis()->SetTitle("cos #theta_{y}");
	wgtHistCosYAll->SetLineWidth(2);
	unwHistCosYAll = new TH1F("Unweighted Simulation","All events", 75, -1.0, 1.0);
	unwHistCosYAll->GetXaxis()->SetTitle("cos #theta_{y}");		
	unwHistCosYAll->SetLineWidth(2);	

	// cosZ
	wgtHistCosZAll = new TH1F("Weighted Simulation","All events", 75, -1.0, 1.0);
	wgtHistCosZAll->GetXaxis()->SetTitle("cos #theta_{z}");
	wgtHistCosZAll->SetLineWidth(2);
	unwHistCosZAll = new TH1F("Unweighted Simulation","All events", 75, -1.0, 1.0);
	unwHistCosZAll->GetXaxis()->SetTitle("cos #theta_{z}");		
	unwHistCosZAll->SetLineWidth(2);	

	// Egamma
	wgtHistEgAll = new TH1F("Weighted Simulation","All events", 100, 1.0, 2.2);
	wgtHistEgAll->GetXaxis()->SetTitle("E_{#gamma} (GeV)");
	wgtHistEgAll->SetLineWidth(2);
	unwHistEgAll = new TH1F("Unweighted Simulation","All events", 100, 1.0, 2.2);
	unwHistEgAll->GetXaxis()->SetTitle("E_{#gamma} (GeV)");		
	unwHistEgAll->SetLineWidth(2);			

	// t
	wgtHisttAll = new TH1F("Weighted Simulation","All events", 100, -0.3, 2.2);
	wgtHisttAll->GetXaxis()->SetTitle("t (GeV/c)");
	wgtHisttAll->SetLineWidth(2);
	unwHisttAll = new TH1F("Unweighted Simulation","All events", 100, -0.3, 2.2);
	unwHisttAll->GetXaxis()->SetTitle("t (GeV/c)");		
	unwHisttAll->SetLineWidth(2);			

	// costh
	wgtHistCosthAll = new TH1F("Weighted Simulation","All events", 75, -1.0, 1.0);
	wgtHistCosthAll->GetXaxis()->SetTitle("cos #theta_{K0}");
	wgtHistCosthAll->SetLineWidth(2);
	unwHistCosthAll = new TH1F("Unweighted Simulation","All events", 75, -1.0, 1.0);
	unwHistCosthAll->GetXaxis()->SetTitle("cos #theta_{K0}");		
	unwHistCosthAll->SetLineWidth(2);			
  
  
  // Fill the histograms  
  for(Int_t i=0;i<chain.GetEntries();i++){
    chain.GetEntry(i);
    getHistForBin(Egamma, costhK0CMS);
    if(wts[currentEBin]->GetEntryBinarySearch(fgID)){//find the weight for this event
		      
      // binned
      // MM_pip_pim
      wgtHistMM_pip_pim[currentEBin][currentThBin]->Fill(MM_pip_pim,wts[currentEBin]->GetWeight("LikeData"));
      unwHistMM_pip_pim[currentEBin][currentThBin]->Fill(MM_pip_pim);

      // MM_p_pip_pim
      wgtHistMM_p_pip_pim[currentEBin][currentThBin]->Fill(MM_p_pip_pim,wts[currentEBin]->GetWeight("LikeData"));
      unwHistMM_p_pip_pim[currentEBin][currentThBin]->Fill(MM_p_pip_pim);

      // M_pip_pim
      wgtHistM_pip_pim[currentEBin][currentThBin]->Fill(M_pip_pim,wts[currentEBin]->GetWeight("LikeData"));
      unwHistM_pip_pim[currentEBin][currentThBin]->Fill(M_pip_pim);
      
      // MM_p
      wgtHistMM_p[currentEBin][currentThBin]->Fill(MM_p,wts[currentEBin]->GetWeight("LikeData"));
      unwHistMM_p[currentEBin][currentThBin]->Fill(MM_p);

      // cosX
      wgtHistCosX[currentEBin][currentThBin]->Fill(cosX,wts[currentEBin]->GetWeight("LikeData"));
      unwHistCosX[currentEBin][currentThBin]->Fill(cosX);

      // cosY
      wgtHistCosY[currentEBin][currentThBin]->Fill(cosY,wts[currentEBin]->GetWeight("LikeData"));
      unwHistCosY[currentEBin][currentThBin]->Fill(cosY);

      // cosZ
      wgtHistCosZ[currentEBin][currentThBin]->Fill(cosZ,wts[currentEBin]->GetWeight("LikeData"));
      unwHistCosZ[currentEBin][currentThBin]->Fill(cosZ);

      // Egamma
      wgtHistEg[currentEBin][currentThBin]->Fill(Egamma,wts[currentEBin]->GetWeight("LikeData"));
      unwHistEg[currentEBin][currentThBin]->Fill(Egamma);

      // t
      wgtHistt[currentEBin][currentThBin]->Fill(t,wts[currentEBin]->GetWeight("LikeData"));
      unwHistt[currentEBin][currentThBin]->Fill(t);

      // costh
      wgtHistCosth[currentEBin][currentThBin]->Fill(costhK0CMS,wts[currentEBin]->GetWeight("LikeData"));
      unwHistCosth[currentEBin][currentThBin]->Fill(costhK0CMS);
      
      // unbinned
      // MM_pip_pim
      wgtHistMM_pip_pimAll->Fill(MM_pip_pim,wts[currentEBin]->GetWeight("LikeData"));
      unwHistMM_pip_pimAll->Fill(MM_pip_pim);
      
      // MM_p_pip_pim
      wgtHistMM_p_pip_pimAll->Fill(MM_p_pip_pim,wts[currentEBin]->GetWeight("LikeData"));
      unwHistMM_p_pip_pimAll->Fill(MM_p_pip_pim);

      // M_pip_pim
      wgtHistM_pip_pimAll->Fill(M_pip_pim,wts[currentEBin]->GetWeight("LikeData"));
      unwHistM_pip_pimAll->Fill(M_pip_pim);

      // MM_p
      wgtHistMM_pAll->Fill(MM_p,wts[currentEBin]->GetWeight("LikeData"));
      unwHistMM_pAll->Fill(MM_p);
      
      // cosX
      wgtHistCosXAll->Fill(cosX,wts[currentEBin]->GetWeight("LikeData"));
      unwHistCosXAll->Fill(cosX);
	  
      // cosY
      wgtHistCosYAll->Fill(cosY,wts[currentEBin]->GetWeight("LikeData"));
      unwHistCosYAll->Fill(cosY);

      // cosZ
      wgtHistCosZAll->Fill(cosZ,wts[currentEBin]->GetWeight("LikeData"));
      unwHistCosZAll->Fill(cosZ);

      // Egamma
      wgtHistEgAll->Fill(Egamma,wts[currentEBin]->GetWeight("LikeData"));
      unwHistEgAll->Fill(Egamma);

      // t
      wgtHisttAll->Fill(t,wts[currentEBin]->GetWeight("LikeData"));
      unwHisttAll->Fill(t);

      // costh
      wgtHistCosthAll->Fill(costhK0CMS,wts[currentEBin]->GetWeight("LikeData"));
      unwHistCosthAll->Fill(costhK0CMS);

    }
  }
  
  // Create asymmetries wgtHistPhiK0Asym
  gStyle->SetOptFit(10111);
  gStyle->SetOptStat(0);
  

  // Save histograms
  gStyle->SetOptStat(1000001);
  // binned
  for (Int_t i=0; i<4; i++) {
	for (Int_t j=0; j<iBinNums[i]; j++) {
		
	  // Fit the Sigma+ mass with gaussian
	  massFunc[i][j] = new TF1("massFunc","gaus", 1.16,1.22);
	  wgtHistMM_pip_pim[i][j]->Sumw2();
	  wgtHistMM_pip_pim[i][j]->Fit(massFunc[i][j],"R");
		
	  // MM_pip_pim
	  wgtHistMM_pip_pim[i][j]->Draw();
	  TString outFilename = outdir+"wgtHistMM_pip_pim"+i+j+".png";
	  c1->SaveAs(outFilename);
	  unwHistMM_pip_pim[i][j]->Draw();
	  outFilename = outdir+"unwHistMM_pip_pim"+i+j+".png";
	  c1->SaveAs(outFilename);

	  // Fit the pi0 mass with gaussian
	  massFunc[i][j] = new TF1("massFunc","gaus", 0.09,0.16);
	  wgtHistMM_p_pip_pim[i][j]->Sumw2();
	  wgtHistMM_p_pip_pim[i][j]->Fit(massFunc[i][j],"R");
	  
	  // MM_p_pip_pim
	  wgtHistMM_p_pip_pim[i][j]->Draw();
	  outFilename = outdir+"wgtHistMM_p_pip_pim"+i+j+".png";
	  c1->SaveAs(outFilename);
	  unwHistMM_p_pip_pim[i][j]->Draw();
	  outFilename = outdir+"unwHistMM_p_pip_pim"+i+j+".png";
	  c1->SaveAs(outFilename);
	  
	  // Fit the K0 mass with gaussian
	  massFunc[i][j] = new TF1("massFunc","gaus", 0.49,0.505);
	  wgtHistM_pip_pim[i][j]->Sumw2();
	  wgtHistM_pip_pim[i][j]->Fit(massFunc[i][j],"R");

	  // M_pip_pim
	  wgtHistM_pip_pim[i][j]->Draw();
	  outFilename = outdir+"wgtHistM_pip_pim"+i+j+".png";
	  c1->SaveAs(outFilename);
	  unwHistM_pip_pim[i][j]->Draw();
	  outFilename = outdir+"unwHistM_pip_pim"+i+j+".png";
	  c1->SaveAs(outFilename);	  

	  // MM_p
	  wgtHistMM_p[i][j]->Draw();
	  outFilename = outdir+"wgtHistMM_p"+i+j+".png";
	  c1->SaveAs(outFilename);
	  unwHistMM_p[i][j]->Draw();
	  outFilename = outdir+"unwHistMM_p"+i+j+".png";
	  c1->SaveAs(outFilename);
	  
	  // cosX
	  wgtHistCosX[i][j]->Draw();
	  outFilename = outdir+"wgtHistCosX"+i+j+".png";
	  c1->SaveAs(outFilename);
	  unwHistCosX[i][j]->Draw();
	  outFilename = outdir+"unwHistCosX"+i+j+".png";
	  c1->SaveAs(outFilename);

	  // cosY
	  wgtHistCosY[i][j]->Draw();
	  outFilename = outdir+"wgtHistCosY"+i+j+".png";
	  c1->SaveAs(outFilename);
	  unwHistCosY[i][j]->Draw("");
	  outFilename = outdir+"unwHistCosY"+i+j+".png";
	  c1->SaveAs(outFilename);
	  
	  // cosZ
	  wgtHistCosZ[i][j]->Draw("");
	  outFilename = outdir+"wgtHistCosZ"+i+j+".png";
	  c1->SaveAs(outFilename);
	  unwHistCosZ[i][j]->Draw("");
	  outFilename = outdir+"unwHistCosZ"+i+j+".png";
	  c1->SaveAs(outFilename);	  

	  // Egamma
	  wgtHistEg[i][j]->Draw("");
	  outFilename = outdir+"wgtHistEg"+i+j+".png";
	  c1->SaveAs(outFilename);
	  unwHistEg[i][j]->Draw("");
	  outFilename = outdir+"unwHistEg"+i+j+".png";
	  c1->SaveAs(outFilename);	  

	  // t
	  wgtHistt[i][j]->Draw("");
	  outFilename = outdir+"wgtHistt"+i+j+".png";
	  c1->SaveAs(outFilename);
	  unwHistt[i][j]->Draw("");
	  outFilename = outdir+"unwHistt"+i+j+".png";
	  c1->SaveAs(outFilename);	  

	  // costh
	  wgtHistCosth[i][j]->Draw("");
	  outFilename = outdir+"wgtHistCosth"+i+j+".png";
	  c1->SaveAs(outFilename);
	  unwHistCosth[i][j]->Draw("");
	  outFilename = outdir+"unwHistCosth"+i+j+".png";
	  c1->SaveAs(outFilename);	  
	  
	}
  }
  // unbinned
  
  // Fit the Sigma+ mass with gaussian
  massFunc[0][0] = new TF1("massFunc","gaus", 1.16,1.22);
  wgtHistMM_pip_pimAll->Sumw2();
  wgtHistMM_pip_pimAll->Fit(massFunc[0][0],"R");
  
  // MM_pip_pim
  wgtHistMM_pip_pimAll->Draw("");
  TString outFilename = outdir+"wgtHistMM_pip_pimAll.png";
  c1->SaveAs(outFilename);
  unwHistMM_pip_pimAll->Draw("");
  outFilename = outdir+"unwHistMM_pip_pimAll.png";
  c1->SaveAs(outFilename);

  // Fit the pi0 mass with gaussian
  massFunc[0][0] = new TF1("massFunc","gaus", 0.09,0.16);
  wgtHistMM_p_pip_pimAll->Sumw2();
  wgtHistMM_p_pip_pimAll->Fit(massFunc[0][0],"R");

  // MM_p_pip_pim
  wgtHistMM_p_pip_pimAll->Draw("");
  outFilename = outdir+"wgtHistMM_p_pip_pimAll.png";
  c1->SaveAs(outFilename);
  unwHistMM_p_pip_pimAll->Draw("");
  outFilename = outdir+"unwHistMM_p_pip_pimAll.png";
  c1->SaveAs(outFilename);

  // Fit the K0 mass with gaussian
  massFunc[0][0] = new TF1("massFunc","gaus", 0.49,0.505);
  wgtHistM_pip_pimAll->Sumw2();
  wgtHistM_pip_pimAll->Fit(massFunc[0][0],"R");
  
  // M_pip_pim
  wgtHistM_pip_pimAll->Draw("");
  outFilename = outdir+"wgtHistM_pip_pimAll.png";
  c1->SaveAs(outFilename);
  unwHistM_pip_pimAll->Draw("");
  outFilename = outdir+"unwHistM_pip_pimAll.png";
  c1->SaveAs(outFilename);  

  // MM_p
  wgtHistMM_pAll->Draw("");
  outFilename = outdir+"wgtHistMM_pAll.png";
  c1->SaveAs(outFilename);
  unwHistMM_pAll->Draw("");
  outFilename = outdir+"unwHistMM_pAll.png";
  c1->SaveAs(outFilename);
  
  // cosX
  wgtHistCosXAll->Draw("");
  outFilename = outdir+"wgtHistCosXAll.png";
  c1->SaveAs(outFilename);
  unwHistCosXAll->Draw("");
  outFilename = outdir+"unwHistCosXAll.png";
  c1->SaveAs(outFilename);

  // cosY
  wgtHistCosYAll->Draw("");
  outFilename = outdir+"wgtHistCosYAll.png";
  c1->SaveAs(outFilename);
  unwHistCosYAll->Draw("");
  outFilename = outdir+"unwHistCosYAll.png";
  c1->SaveAs(outFilename);
  
  // cosZ
  wgtHistCosZAll->Draw("");
  outFilename = outdir+"wgtHistCosZAll.png";
  c1->SaveAs(outFilename);
  unwHistCosZAll->Draw("");
  outFilename = outdir+"unwHistCosZAll.png";
  c1->SaveAs(outFilename);	  

  // Egamma
  wgtHistEgAll->Draw("");
  outFilename = outdir+"wgtHistEgAll.png";
  c1->SaveAs(outFilename);
  unwHistEgAll->Draw("");
  outFilename = outdir+"unwHistEgAll.png";
  c1->SaveAs(outFilename);	  

  // t
  wgtHisttAll->Draw("");
  outFilename = outdir+"wgtHisttAll.png";
  c1->SaveAs(outFilename);
  unwHisttAll->Draw("");
  outFilename = outdir+"unwHisttAll.png";
  c1->SaveAs(outFilename);	  

  // costh
  wgtHistCosthAll->Draw("");
  outFilename = outdir+"wgtHistCosthAll.png";
  c1->SaveAs(outFilename);
  unwHistCosthAll->Draw("");
  outFilename = outdir+"unwHistCosthAll.png";
  c1->SaveAs(outFilename);	  
    
}
