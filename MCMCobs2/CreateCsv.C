void CreateCsv() {

	TFile *infile = TFile::Open("/home/louise/g8K0Sig/code/MCMCobs2/out12/costhK0CMS0.67_Egamma1.85_/ResultsHSRooMcmcUniform2Seq.root");
	TTree *MCMCTree = (TTree*)infile->Get("MCMCTree");
	int n = MCMCTree->GetEntries();

    ofstream outfile;
    outfile.open("/home/louise/g8K0Sig/code/MCMCobs2/out12/costhK0CMS0.67_Egamma1.85_/MCMCTree.csv");
    
    Double_t	B,Ox,Oz,R,T;
    
    MCMCTree->SetBranchAddress("B",&B);
    MCMCTree->SetBranchAddress("Ox",&Ox);
    MCMCTree->SetBranchAddress("Oz",&Oz);
    MCMCTree->SetBranchAddress("R",&R);
    MCMCTree->SetBranchAddress("T",&T);
    
    for (int i=0; i<n; i++) {
		MCMCTree->GetEntry(i);
		outfile << B << "," << Ox << "," << Oz << "," << R << "," << T << "\n";
	}

	outfile.close();
	
}
