#include <string.h>

void DoFits(TDirectory *inDir, TDirectory *inDirMC, TDirectory *outDir){	
	
	
	TH1F* cosYPARA = (TH1F*)inDir->Get("cosYPARA");
	TH1F* cosYPARACorr = (TH1F*)inDir->Get("cosYPARA");
	TH1F* cosYMC = (TH1F*)inDirMC->Get("cosYPARA"); 
	TH1F* cosYMCNorm = (TH1F*)inDirMC->Get("cosYPARA"); 
	
	char newName[80];
	strcpy(newName, cosYMCNorm->GetName());
	strcat(newName, "Norm");
	cosYMCNorm->SetName(newName);
	cosYMCNorm->SetTitle(newName);
	
	strcpy(newName, cosYPARACorr->GetName());
	strcat(newName, "Corr");
	cosYPARACorr->SetName(newName);
	cosYPARACorr->SetTitle(newName);
	
	int meanBinContent = cosYMC->GetEntries()/cosYMC->GetNbinsX();
	for (int i=0; i < cosYMC->GetNbinsX(); i++) {
		cosYMCNorm->SetBinContent(i, cosYMC->GetBinContent(i)/meanBinContent);
		cosYMCNorm->SetBinError(i, cosYMC->GetBinError(i)/meanBinContent);
	}
	cosYMCNorm->GetYaxis()->SetRangeUser(0.0,2.0);
	cosYPARACorr->Sumw2();
	cosYPARACorr->Divide(cosYMCNorm);
	
	TF1* fPARA = new TF1("fPARA","[0]*(1+[1]*x)", -1.0,1.0);
	cosYPARACorr->Fit("fPARA");
	gStyle->SetOptFit();
	
	outDir->cd();
	cout << "Writing to outDir " << outDir->GetName() << endl;
	cosYPARA->Write();
	cosYPARACorr->Write();
	cosYMC->Write();
	cosYMCNorm->Write();
	
}
void Analyser() {
	

	TFile *infile = TFile::Open("/home/louise/g8K0Sig/code/sWeights/hist/K0pi0_weights/out_Ecosthbins/hists_all.root");
	TFile *infileMC = TFile::Open("/home/louise/g8K0Sig/code/sWeights/hist/K0_weights/out_EcosthbinsMC/hists_all.root");
	TFile* outfile = new TFile("out_K0pi0weights/analyseP.root","recreate");	

	string dirs[3] = {"Signal", "BG", "All"};

	TDirectory *dataDir = infile->GetDirectory("Signal");	
	TDirectory *mcDir = infileMC->GetDirectory("All");	

	TIter	nextBin1Dir(dataDir->GetListOfKeys());
	TKey 	*bin1Key;

	while ((bin1Key=(TKey*)nextBin1Dir())) {
	
		TDirectory *bin1Dir = dataDir->GetDirectory(bin1Key->GetName());
		TDirectory *bin1DirMC = mcDir->GetDirectory(bin1Key->GetName());
		
		TIter	nextBin2Dir(bin1Dir->GetListOfKeys());
		TKey 	*bin2Key;
		outfile->mkdir(bin1Key->GetName());
		TDirectory *bin1DirOut = outfile->GetDirectory(bin1Key->GetName());
		
		while ((bin2Key=(TKey*)nextBin2Dir())) {
			
			TDirectory *bin2Dir = bin1Dir->GetDirectory(bin2Key->GetName());
			TDirectory *bin2DirMC = bin1DirMC->GetDirectory(bin2Key->GetName());
			bin1DirOut->mkdir(bin2Key->GetName());
			TDirectory *bin2DirOut = bin1DirOut->GetDirectory(bin2Key->GetName());
			
			DoFits(bin2Dir, bin2DirMC, bin2DirOut);					
							
		}
	}

	outfile->Close();

}

