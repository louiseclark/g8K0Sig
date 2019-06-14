// Run with
// root --hsdata DrawWithWeights.C
{
	Weights* wts=new Weights("TotalWeights");
	wts->Merge("/home/louise/g8K0Sig/code/sWeights2/out_all_pi0K0_binned/Tweights","histWeights.root","HSsWeights");

	TChain chain("HSParticles");
	chain.AddFile("/w/work0/home/louise/g8K0Sig/convert_output/filepPi0_all.root");
	Double_t fgID,costhK0CMS, Egamma;
	chain.SetBranchAddress("fgID",&fgID);
	chain.SetBranchAddress("costhK0CMS",&costhK0CMS);
	chain.SetBranchAddress("Egamma",&Egamma);

	TH2F* hist=new TH2F("hist","hist",200, -1.0, 1.0, 3, 1.1, 2.1);
	Double_t weight=0;

	for(Int_t i=0;i<chain.GetEntries();i++){
	chain.GetEntry(i);
	if(wts->GetEntryBinarySearch(fgID)){//find the weight for this event  
	  hist->Fill(costhK0CMS,Egamma,wts->GetWeight("Signal"));
	}
	}

	TFile* outfile = new TFile("costhBins.root","recreate");

	hist->Draw("");
	hist->Write();

	// Find bins
	Int_t numBins = 6;
	Double_t min = -1.0;
	Double_t max = 1.0;
	
	Int_t startBin = hist->GetXaxis()->FindBin(min);
	Int_t endBin = hist->GetXaxis()->FindBin(max);

	Double_t totInt = hist->Integral(startBin, endBin);
	Double_t binInt = totInt / numBins;

	cout << "totInt " << totInt << endl;
	cout << "binInt " << binInt << endl;

	Double_t runInt = 0.0;
	Double_t prevBinLimit = min;
	Int_t prevBin = startBin;

	for (int i=startBin; i<endBin; i++) {

		runInt = runInt + hist->Integral(i,i,0,0);
		
		cout << "bin "<< i << " runInt " << runInt << " binCenter " <<  hist->GetXaxis()->GetBinCenter(i) <<endl;
		cout << "bin "<< i << " binContent " <<  hist->Integral(i,i,0,0) <<endl;
		
		if (runInt > binInt) {
		
			cout << endl;
			cout << "bin limits are " << prevBinLimit << " to " << hist->GetXaxis()->GetBinCenter(i) << endl;
			cout << "Integral " << hist->Integral(prevBin, i-1, 0, 0) << endl;
			cout << endl;
			
			runInt = hist->Integral(i,i,0,0);
			prevBinLimit = hist->GetXaxis()->GetBinCenter(i);
			prevBin = i;
		}
		
	}  
  
}
