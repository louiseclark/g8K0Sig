void CreateCsvAmp() {

	TFile *infile = TFile::Open("/home/louise/g8K0Sig/code/MCMCamp2/out4/costhK0CMS0.67_Egamma1.85_/ResultsHSRooMcmcUniform2Seq.root");
	TTree *MCMCTree = (TTree*)infile->Get("MCMCTree");
	int n = MCMCTree->GetEntries();

    ofstream outfile;
    outfile.open("/home/louise/g8K0Sig/code/MCMCamp2/out4/costhK0CMS0.67_Egamma1.85_/MCMCTreeAmp.csv");
    
    Double_t	a1Re,a1Im,a2Re,a2Im,a3Re,a3Im,a4Re,a4Im,B,Ox,Oz,R,T;
    
    MCMCTree->SetBranchAddress("a1Re",&a1Re);
    MCMCTree->SetBranchAddress("a1Im",&a1Im);
    MCMCTree->SetBranchAddress("a2Re",&a2Re);
    MCMCTree->SetBranchAddress("a2Im",&a2Im);
    MCMCTree->SetBranchAddress("a3Re",&a3Re);
    MCMCTree->SetBranchAddress("a3Im",&a3Im);
    MCMCTree->SetBranchAddress("a4Re",&a4Re);
    MCMCTree->SetBranchAddress("a4Im",&a4Im);
	MCMCTree->SetBranchAddress("B",&B);
    MCMCTree->SetBranchAddress("Ox",&Ox);
    MCMCTree->SetBranchAddress("Oz",&Oz);
    MCMCTree->SetBranchAddress("R",&R);
    MCMCTree->SetBranchAddress("T",&T);
    
    for (int i=0; i<n; i++) {
		MCMCTree->GetEntry(i);
		outfile << a1Re << "," << a1Im << "," << a2Re << "," << a2Im << "," << a3Re << "," << a3Im << "," << a4Re << "," << a4Im << "," 
				<< B << "," << Ox << "," << Oz << "," << R << "," << T << "\n";
	}

	outfile.close();
	
}
