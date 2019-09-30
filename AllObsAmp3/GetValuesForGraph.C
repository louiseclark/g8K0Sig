#include <dirent.h>
#include <string>

void GetValuesForGraph() {
	
	std::string path = "/home/louise/g8K0Sig/code/MCMCamp2/out8/";
	auto topDir = opendir(path.c_str());
	struct dirent *eGammaDir;
	
	TString outdir = "/home/louise/g8K0Sig/AnalysisSummary/html/images/sWeights/";
	gStyle->SetOptStat(0);
	
	std::string obs = "R";
	
	ofstream outfile;
    outfile.open("out8/ValuesForGraph"+obs+".txt");
	
	// read the Egamma directories in the topDir
	while (eGammaDir=readdir(topDir)) {
		
		// does the directory listing start Egamma
		std::string dirStr = eGammaDir->d_name;
		if (dirStr.substr(0, 6) == "Egamma") {
			
			outfile << "# My "<< obs << dirStr << endl;
			//outfile << "x=[-0.8,-0.4,0.0,0.4,0.8]" << endl;
			std::string yString = "y=[";
			std::string yErrString = "y_err=[";
			
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
					TTree *MCMCTree = (TTree*)infile->Get("MCMCTree");
			
					TH1F* hist = new TH1F("hist","",100,-1.2,1.2);
					std::string drawStr = obs+">>hist";
					MCMCTree->Draw(drawStr.c_str());
					
					yString = yString + hist->GetMean() + ",";
					yErrString = yErrString + hist->GetRMS() + ",";
				}
			}
			yString = yString.substr(0, yString.length()-1) + "]";
			yErrString = yErrString.substr(0, yErrString.length()-1) + "]";
			outfile << yString << endl;
			//outfile << "x_err=[0.0,0.0,0.0,0.0,0.0]" << endl;
			outfile << yErrString << endl << endl;
		}
	}
	closedir(topDir);
	outfile.close();
}
