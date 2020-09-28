#include <dirent.h>
#include <string>

void GetMCMCFitPlotsBru() {
	
	std::string path = "/home/louise/g8K0Sig/code/AllObsAmp3_test13/out1/";
	auto topDir = opendir(path.c_str());
	struct dirent *binDir;
	
	std::string outdir = "/home/louise/public_html/html/images/st13/MCMCFits/";
	gStyle->SetOptStat(0);
	string vars[5] = {"_cosX","_cosY","_cosZ","_phiK0","_pol"};
	
	std::string dirStr;
	std::string binPath;
	std::string fileName;
	std::string histName;
	std::string textName;
	TString outFilename;
	TCanvas* c1;
	
	for (int i=0; i<5; i++) {
	
		topDir = opendir(path.c_str());
		cout << "topDir is " << topDir << endl;
		
		// read the Egamma directories in the topDir
		while (binDir=readdir(topDir)) {
			
			// does the directory listing start Egamma
			dirStr = binDir->d_name;
			if (dirStr.substr(0, 5) == "costh") {
				
				cout << binDir->d_name << endl;
				// get the path to the bin dir
				binPath = path + binDir->d_name;
				auto dir = opendir(binPath.c_str());
						
				//fileName = path + dirStr+ "/ResultsHSRooMcmcUniform2Seq.root";
				fileName = path + dirStr+ "/ResultsHSRooMcmcSeq.root";
				cout << fileName << endl;
				TFile* infile = TFile::Open(fileName.c_str());
				histName = dirStr+vars[i];
				TH1F* h = (TH1F*)infile->Get(histName.c_str());
										
				h->Draw();
				gPad->Update();
					
				//~ c1 = (TCanvas*) gPad->GetListOfPrimitives()->First();
				//~ textName = dirStr+"TotalPDF_paramBox";
				//~ TPaveText *st = (TPaveText*) c1->GetPrimitive(textName.c_str());
				//~ st->Delete();
					
				//~ TPaveText* tit = (TPaveText*) c1->GetPrimitive("title");
				//~ tit->SetTextSize(0.055);
				//~ tit->InsertText("");				
				//~ tit->InsertText(dirStr.c_str());
					
				gPad->Modified();
				gPad->Update();
				gPad->Draw();
					
				outFilename = outdir+histName+".png";
				h->SaveAs(outFilename);
				h->Delete();
				//~ tit->Delete();
				infile->Delete();
				closedir(dir);
					
			}
		}
		closedir(topDir);	
	}			
	
}	

