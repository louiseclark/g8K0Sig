#include <dirent.h>
#include <string>

void GetValuesForGraph() {
	
	
	//std::string path = "/home/louise/g8K0Sig/code/AllObsAmp3/out1/";
	//std::string pref = "m";
	std::string path = "/home/louise/g8K0Sig/code/AllObsAmp3_test5/out1/";
	std::string pref = "st5";
	
	std::string burnIn = "50";
	
	string eBins[4] = {"1.23","1.48","1.73","1.98"};
	
	std::string obs[] = {"B","Ox","Oz","R","T","Cx","Cz"};
	
	for (int obsNum=0; obsNum<7; obsNum++) {
	
		ofstream outfile;
		outfile.open(pref+"ValuesForGraph"+obs[obsNum]+".txt");
		
		std::string xArrString = pref+obs[obsNum]+"x=[";
		std::string yArrString = pref+obs[obsNum]+"y=[";
		std::string yErrArrString = pref+obs[obsNum]+"y_err=[";
		
		for (int i=0; i<4; i++) {
		
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
					
					//std::string fileName = path + dirStr+ "/ResultsHSRooMcmcUniform2Seq.root";
					std::string fileName = path + dirStr+ "/ResultsHSRooMcmcSeq.root";
					TFile *infile = TFile::Open(fileName.c_str());
					TTree *MCMCTree = (TTree*)infile->Get("MCMCTree");
			
					TH1F* hist = new TH1F("hist","",100,-1.2,1.2);
					std::string drawStr = obs[obsNum]+">>hist";
					std::string entryStr = "Entry$>="+burnIn;
					MCMCTree->Draw(drawStr.c_str(),entryStr.c_str());
					
					xString = xString + binName + ",";
					yString = yString + hist->GetMean() + ",";
					yErrString = yErrString + hist->GetRMS() + ",";
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
		
		outfile.close();
		}
}
