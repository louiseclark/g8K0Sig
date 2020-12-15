#include <dirent.h>
#include <string.h>

void GetMCMCPdfPlots() {
	
	//std::string path = "/home/louise/g8K0Sig/code/AllObsAmp3/out1/";
	std::string path = "/home/louise/g8K0Sig/code/AllObsAmp3_test22/out1/";
	
	string burnIn = "50";
	
	auto topDir = opendir(path.c_str());
	struct dirent *binDir;
	
	TString outdir = "/home/louise/public_html/html/images/st22/MCMCPdfs/";
	gStyle->SetOptStat(0);
	string obs[7] = {"B","T","Ox","Oz","R","Cx","Cz"};
	string obsAx[7] = {"#Sigma","T","O_{x}","O_{z}","P","C_{x}","C_{z}"};
	
	std::string dirStr;
	std::string binPath;
	std::string fileName;
	std::string histName;
	std::string textName;
	TString outFilename;
	TCanvas* c1 = new TCanvas("c1","c1",800,600);
	
	gStyle->SetOptStat(1111);
	
	for (int i=0; i<7; i++) {
	
		topDir = opendir(path.c_str());
		
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
				TTree *MCMCTree = (TTree*)infile->Get("MCMCTree");
				
				TH1F* h= new TH1F("PDF","",100,-1.2,1.2);
				std::string drawStr = obs[i]+">>PDF";
				std::string burnStr = "Entry$>="+burnIn;
				cout << "drawStr " << drawStr << endl;
				cout << "burnStr " << burnStr << endl;
				MCMCTree->Draw(drawStr.c_str(),burnStr.c_str());
				
				h->GetXaxis()->SetTitle(obsAx[i].c_str());
				std::string titleStr = "cos(#theta_{K0}) = " + dirStr.substr(10,dirStr.length()-22) +
									   " E_{#gamma} = " + dirStr.substr(dirStr.length()-5,4);
				h->SetTitle(titleStr.c_str());
										
				h->Draw();
					
				outFilename = outdir+obs[i].c_str()+"_"+dirStr.c_str()+"Pdf.png";
				c1->SaveAs(outFilename);
				c1->Clear();
				
				// Plot Fierz identities
				//if (i==0) {
				//    Double_t id1 = 
				//}
				
				infile->Delete();
				closedir(dir);
					
			}
		}
		closedir(topDir);	
	}			
	
}	

