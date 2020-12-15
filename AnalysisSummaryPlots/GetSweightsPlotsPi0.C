#include <dirent.h>
#include <string>

void GetSweightsPlotsPi0() {
	
	std::string path = "/home/louise/g8K0Sig/code/sWeights3_test19/out_all_pi0_binned/";
	auto topDir = opendir(path.c_str());
	struct dirent *eGammaDir;
	
	std::string outdir = "/home/louise/public_html/html/images/st19/sWeights/";
	gStyle->SetOptStat(0);
	int ebin = 0;
	int thbin = 0;
	
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
			thbin = 0;
					
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
					
					TCanvas* c1 = (TCanvas*) gPad->GetListOfPrimitives()->First();
					
					std::string textName = dirStr2+"TotalPDF_paramBox";
					TPaveText *st = (TPaveText*) c1->GetPrimitive(textName.c_str());
					st->Delete();
										
					//TPaveText* tit = (TPaveText*) c1->GetPrimitive("title");
					//tit->SetTextColor(kWhite);
					//tit->InsertText("Test 1"); //dirStr2.c_str());
					
					//TH1D* h1 = (TH1D*) c1->GetPrimitive("frame_a261eb0");
					//h1->GetXaxis()->SetTitle("test");
					
					gPad->Modified();
					gPad->Update();
					gPad->Draw();
					
					TString outFilename = outdir+dirStr2+"pi0.png";
					h->SaveAs(outFilename);
					thbin++;
					
				}
				ebin++;
			}
		}
	}
	closedir(topDir);	
	
}	

