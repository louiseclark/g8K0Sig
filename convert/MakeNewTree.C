void MakeNewTree() {
	
	TFile *oldfile = new TFile("/w/work0/home/louise/g8K0Sig/convert_output/filepPi0_all.root");
	TTree *oldtree = (TTree*)oldfile->Get("HSParticles");
	Long64_t nentries = oldtree->GetEntries();
	
	Double_t MM_pip_pim;
	oldtree->SetBranchAddress("MM_pip_pim",&MM_pip_pim);
	
	// Create a new file + a clone of old tree in new file
	TFile *newfile = new TFile("/w/work0/home/louise/g8K0Sig/convert_output/filepPi0_st6.root","recreate");
	TTree *newtree = oldtree->CloneTree(0);
	
	for (Long64_t i=0;i<nentries; i++) {
		
		oldtree->GetEntry(i);
		if (MM_pip_pim > 1.16 && MM_pip_pim < 1.22) newtree->Fill();
		
	}
	
	newtree->Print();
	newtree->AutoSave();
	delete oldfile;
	delete newfile;

}

