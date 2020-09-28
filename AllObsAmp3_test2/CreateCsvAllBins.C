#include <dirent.h>
#include <string>

void CreateCsvAllBins() {
		
	std::string path = "/home/louise/g8K0Sig/code/AllObsAmp3_test2/out1/";
	auto topDir = opendir(path.c_str());
	struct dirent *binDir;
	
	ofstream outfile;
    outfile.open(path+"CsvAllBins.csv");

	// read the directories in the topDir
	while (binDir=readdir(topDir)) {
		
		// does the directory listing start costh
		std::string dirStr = binDir->d_name;
		if (dirStr.substr(0, 5) == "costh") {
			
			cout << binDir->d_name << endl;
			// get the path to the bin dir
			std::string binPath = path + binDir->d_name;
			auto dir = opendir(binPath.c_str());
					
			std::string fileName = path + dirStr +  "/ResultsHSRooMcmcUniform2Seq.root";
			cout << fileName << endl;
			TFile *infileObs = TFile::Open(fileName.c_str());
			TTree *MCMCTreeObs = (TTree*)infileObs->Get("MCMCTree");
			int nObs = MCMCTreeObs->GetEntries();
			Double_t	B,Ox,Oz,R,T;
					
			MCMCTreeObs->SetBranchAddress("B",&B);
			MCMCTreeObs->SetBranchAddress("Ox",&Ox);
			MCMCTreeObs->SetBranchAddress("Oz",&Oz);
			MCMCTreeObs->SetBranchAddress("R",&R);
			MCMCTreeObs->SetBranchAddress("T",&T);
					
			for (int i=0; i<nObs; i++) {
				MCMCTreeObs->GetEntry(i);
				outfile << "B," << B << "," << dirStr << "\n";
				outfile << "Ox," << Ox << "," << dirStr << "\n";
				outfile << "Oz," << Oz << "," << dirStr << "\n";
				outfile << "R," << R << "," << dirStr << "\n";
				outfile << "T," << T << "," << dirStr << "\n";
			}
			
		}
	}
	closedir(topDir);
		
	outfile.close();
	
}
