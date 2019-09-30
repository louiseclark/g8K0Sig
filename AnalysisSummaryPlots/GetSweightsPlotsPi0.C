#include <dirent.h>
#include <string>

void GetSweightsPlotsPi0() {
	
	std::string path = "/home/louise/g8K0Sig/code/sWeights3/out_all_pi0_binned/";
	auto topDir = opendir(path.c_str());
	struct dirent *eGammaDir;
	
	TString outdir = "/home/louise/g8K0Sig/AnalysisSummary/html/images/sWeights/";
	gStyle->SetOptStat(0);
	
	// read the Egamma directories in the topDir
	while (eGammaDir=readdir(topDir)) {
		
		// does the directory listing start Egamma
		std::string dirStr = eGammaDir->d_name;
		if (dirStr.substr(0, 6) == "Egamma") {
			
			cout << eGammaDir->d_name << endl;
			// get the path to the Egamma dir
			std::string eGammaPath = path + eGammaDir->d_name;
			auto dir = opendir(eGammaPath.c_str());
			struct dirent *costhDir;
					
			// read the costh directories in the Egamma dir
			while (costhDir=readdir(dir)) {
				// does the directory listing start costh
				std::string dirStr2 = costhDir->d_name;
				if (dirStr2.substr(0, 5) == "costh") {
					cout << costhDir->d_name << endl;
					
					std::string fileName = path + dirStr+ "/" + dirStr2 + "/ResultsHSMinuit2.root";
					cout << fileName << endl;
					TFile* infile = TFile::Open(fileName.c_str());
					std::string histName = dirStr2+"_MM_p_pip_pim";
					TH1F* h = (TH1F*)infile->Get(histName.c_str());
					
					//h->SetTitle("Test");
					//h->GetXaxis()->SetTitle("Missing mass(p #pi^{+} #pi^{-}) GeV");
					
					h->Draw();
					gPad->Update();
					
					//TPaveText *st = (TPaveText*)gPad->GetPrimitive("costhK0CMS-0.05_Egamma1.23_TotalPDF_paramBox");
					TCanvas* c1 = (TCanvas*) gPad->GetListOfPrimitives()->First();
					std::string textName = dirStr2+"TotalPDF_paramBox";
					TPaveText *st = (TPaveText*) c1->GetPrimitive(textName.c_str());
					st->Delete();
					//st->SetX1NDC(0.5); //new x start position
					//st->SetX2NDC(0.5); //new x end position

					TPaveText* tit = (TPaveText*) c1->GetPrimitive("title");
					tit->InsertText(dirStr2.c_str());
					
					gPad->Modified();
					gPad->Update();
					gPad->Draw();
					
					TString outFilename = outdir+dirStr2+"pi0.png";
					h->SaveAs(outFilename);
					
				}
			}
		}
	}
	closedir(topDir);	
	
}	

