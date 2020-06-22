#include <dirent.h>
#include <string>

void GetValuesForGraph() {
	
	
	std::string path = "/home/louise/g8K0Sig/code/AllObsAmp3/out1/";
	string eBins[4] = {"1.23","1.48","1.73","1.98"};
	
	std::string obs = "Oz";
	
	ofstream outfile;
    outfile.open("out1/ValuesForGraph"+obs+".txt");
    
	std::string xArrString = "mx=[";
	std::string yArrString = "my=[";
	std::string yErrArrString = "my_err=[";

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
				
				std::string fileName = path + dirStr+ "/ResultsHSRooMcmcUniform2Seq.root";
				TFile *infile = TFile::Open(fileName.c_str());
				TTree *MCMCTree = (TTree*)infile->Get("MCMCTree");
		
				TH1F* hist = new TH1F("hist","",100,-1.2,1.2);
				std::string drawStr = obs+">>hist";
				MCMCTree->Draw(drawStr.c_str(),"Entry$>50");
				
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
