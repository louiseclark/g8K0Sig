#include <dirent.h>
#include <string>

void GetValuesForGraph() {
	
	
	std::string path = "/home/louise/g8K0Sig/code/AllObsObs_toy/out11/";
	string eBins[4] = {"1.23","1.48","1.73","1.98"};
	
	std::string obsName = "T";
	std::string obsErrName = "T_err";
	double_t obsVal = 0.0;
	double_t obsErr = 0.0;
	
	ofstream outfile;
    outfile.open("out11/ValuesForGraph"+obsName+".txt");
    
	std::string xArrString = "m"+obsName+"x=[";
	std::string yArrString = "m"+obsName+"y=[";
	std::string yErrArrString = "m"+obsName+"y_err=[";

	for (int i=0; i<4; i++) { // egamma bins
	
		auto topDir = opendir(path.c_str());
		struct dirent *binDir;	
		
		std::string xString = "[";
		std::string yString = "[";
		std::string yErrString = "[";
		
		// read the directories in the topDir
		while (binDir=readdir(topDir)) {
			
			// just get relevant Egamma dirs
			std::string dirStr = binDir->d_name;
			if (dirStr.find(eBins[i]) != std::string::npos) {
				
				int posSubstr = 10;
				int lenSubstr = dirStr.find("_Egamma")-10;
				std::string binName = dirStr.substr(posSubstr, lenSubstr);
				cout << "directory " << dirStr << " bin name " << binName << endl;
				
				// MCMC fit results from real data
				std::string fileName = path + dirStr+ "/ResultsHSRooMcmcSeq.root";
				TFile *infile = TFile::Open(fileName.c_str());
				TTree *ResultTree = (TTree*)infile->Get("ResultTree");
		
				ResultTree->SetBranchAddress(obsName.c_str(), &obsVal);
				ResultTree->SetBranchAddress(obsErrName.c_str(), &obsErr);
				ResultTree->GetEntry(0);
				
				xString = xString + binName + ",";
				yString = yString + obsVal + ",";
				yErrString = yErrString + obsErr + ",";
			}
		}
		yString = yString.substr(0, yString.length()-1) + "]";
		yErrString = yErrString.substr(0, yErrString.length()-1) + "]";
		xString = xString.substr(0, xString.length()-1) + "]";
		
		xArrString = xArrString + xString +",\n";
		yArrString = yArrString + yString +",\n";
		yErrArrString = yErrArrString + yErrString +",\n";
		
		closedir(topDir);
	}

	yArrString = yArrString.substr(0, yArrString.length()-2) + "]";
	yErrArrString = yErrArrString.substr(0, yErrArrString.length()-2) + "]";
	xArrString = xArrString.substr(0, xArrString.length()-2) + "]";
	
	outfile << xArrString << "\n" << endl;
	outfile << yArrString << "\n" << endl;
	outfile << yErrArrString << "\n" << endl;
	
	// toy data x 5
	for (int toyidx=0; toyidx<5; toyidx++) {
		xArrString = "toy"+std::to_string(toyidx)+obsName+"x=[";
		yArrString = "toy"+std::to_string(toyidx)+obsName+"y=[";
		yErrArrString = "toy"+std::to_string(toyidx)+obsName+"y_err=[";

		for (int i=0; i<4; i++) { // egamma bins
		
			auto topDir = opendir(path.c_str());
			struct dirent *binDir;	
			
			std::string xString = "[";
			std::string yString = "[";
			std::string yErrString = "[";
			
			// read the directories in the topDir
			while (binDir=readdir(topDir)) {
				
				// just get relevant Egamma dirs
				std::string dirStr = binDir->d_name;
				if (dirStr.find(eBins[i]) != std::string::npos) {
					
					int posSubstr = 10;
					int lenSubstr = dirStr.find("_Egamma")-10;
					std::string binName = dirStr.substr(posSubstr, lenSubstr);
					cout << "directory " << dirStr << " bin name " << binName << endl;
					
					// toy fit results 
					std::string fileName = path + dirStr+ "/ResultsToy"+std::to_string(toyidx)+"HSMinuit2.root";
					TFile *infile = TFile::Open(fileName.c_str());
					TTree *ResultTree = (TTree*)infile->Get("ResultTree");
			
					ResultTree->SetBranchAddress(obsName.c_str(), &obsVal);
					ResultTree->SetBranchAddress(obsErrName.c_str(), &obsErr);
					ResultTree->GetEntry(0);
					
					xString = xString + binName + ",";
					yString = yString + obsVal + ",";
					yErrString = yErrString + obsErr + ",";
				}
			}
			yString = yString.substr(0, yString.length()-1) + "]";
			yErrString = yErrString.substr(0, yErrString.length()-1) + "]";
			xString = xString.substr(0, xString.length()-1) + "]";
			
			xArrString = xArrString + xString +",\n";
			yArrString = yArrString + yString +",\n";
			yErrArrString = yErrArrString + yErrString +",\n";
			
			closedir(topDir);
		}

		yArrString = yArrString.substr(0, yArrString.length()-2) + "]";
		yErrArrString = yErrArrString.substr(0, yErrArrString.length()-2) + "]";
		xArrString = xArrString.substr(0, xArrString.length()-2) + "]";
		
		outfile << xArrString << "\n" << endl;
		outfile << yArrString << "\n" << endl;
		outfile << yErrArrString << "\n" << endl;	
	}
	
	outfile.close();
}
