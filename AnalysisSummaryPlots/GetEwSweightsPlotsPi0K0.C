#include <dirent.h>
#include <string>

void GetEwSweightsPlotsPi0K0() {
	
	std::string path = "/home/louise/g8K0Sig/code/sWeights4/out_all_pi0K0_binned/";
	auto topDir = opendir(path.c_str());
	struct dirent *binDir;
	
	TString outdir = "/home/louise/g8K0Sig/AnalysisSummary/html/images/EwsWeights/";
	gStyle->SetOptStat(0);
	
			
	// read the bin directories
	while (binDir=readdir(topDir)) {
		// does the directory listing start costh
		std::string dirStr2 = binDir->d_name;
		if (dirStr2.substr(0, 5) == "costh") {
			
			std::string fileName = path + dirStr2 + "/ResultsHSMinuit2.root";
			TFile* infile = TFile::Open(fileName.c_str());
			std::string histName = dirStr2+"_M_pip_pim";
			TH1F* h = (TH1F*)infile->Get(histName.c_str());
			
			h->Draw();
			gPad->Update();

			TCanvas* c1 = (TCanvas*) gPad->GetListOfPrimitives()->First();
			std::string textName = dirStr2+"TotalPDF_paramBox";
			TPaveText *st = (TPaveText*) c1->GetPrimitive(textName.c_str());
			st->Delete();
			
			TPaveText* tit = (TPaveText*) c1->GetPrimitive("title");
			tit->InsertText(dirStr2.c_str());
			
			gPad->Modified();
			gPad->Update();
			gPad->Draw();
			
			TString outFilename = outdir+dirStr2+"K0.png";
			h->SaveAs(outFilename);
			
		}
	}
	closedir(topDir);	
	
}	

