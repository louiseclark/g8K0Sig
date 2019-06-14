void CreateCsvCombined() {

	TFile *infileObs = TFile::Open("/home/louise/g8K0Sig/code/MCMCobs2/out12/costhK0CMS0.67_Egamma1.85_/ResultsHSRooMcmcUniform2Seq.root");
	TFile *infileAmp = TFile::Open("/home/louise/g8K0Sig/code/MCMCamp2/out3/costhK0CMS0.67_Egamma1.85_/ResultsHSRooMcmcUniform2Seq.root");
	TTree *MCMCTreeObs = (TTree*)infileObs->Get("MCMCTree");
	TTree *MCMCTreeAmp = (TTree*)infileAmp->Get("MCMCTree");
	int nObs = MCMCTreeObs->GetEntries();
	int nAmp = MCMCTreeAmp->GetEntries();

    ofstream outfile;
    outfile.open("/home/louise/g8K0Sig/code/MCMCobs2/out12/costhK0CMS0.67_Egamma1.85_/MCMCTreeComb.csv");
    
    Double_t	B,Ox,Oz,R,T;
    
    MCMCTreeObs->SetBranchAddress("B",&B);
    MCMCTreeObs->SetBranchAddress("Ox",&Ox);
    MCMCTreeObs->SetBranchAddress("Oz",&Oz);
    MCMCTreeObs->SetBranchAddress("R",&R);
    MCMCTreeObs->SetBranchAddress("T",&T);
    
    for (int i=0; i<nObs; i++) {
		MCMCTreeObs->GetEntry(i);
		outfile << "B," << B << ",Obs" << "\n";
		outfile << "Ox," << Ox << ",Obs" << "\n";
		outfile << "Oz," << Oz << ",Obs" << "\n";
		outfile << "R," << R << ",Obs" << "\n";
		outfile << "T," << T << ",Obs" << "\n";
	}

    MCMCTreeAmp->SetBranchAddress("B",&B);
    MCMCTreeAmp->SetBranchAddress("Ox",&Ox);
    MCMCTreeAmp->SetBranchAddress("Oz",&Oz);
    MCMCTreeAmp->SetBranchAddress("R",&R);
    MCMCTreeAmp->SetBranchAddress("T",&T);
    
    for (int i=0; i<nAmp; i++) {
		MCMCTreeAmp->GetEntry(i);
		outfile << "B," << B << ",Amp" << "\n";
		outfile << "Ox," << Ox << ",Amp" << "\n";
		outfile << "Oz," << Oz << ",Amp" << "\n";
		outfile << "R," << R << ",Amp" << "\n";
		outfile << "T," << T << ",Amp" << "\n";
	}

	outfile.close();
	
}
