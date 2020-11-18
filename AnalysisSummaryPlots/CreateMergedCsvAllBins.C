#include <dirent.h>
#include <string>

void CreateMergedCsvAllBins() {
		
	std::string paths[] = {"/home/louise/g8K0Sig/code/AllObsAmp3_test13/out1/",
						 "/home/louise/g8K0Sig/code/AllObsAmp3_test14/out1/",
						 "/home/louise/g8K0Sig/code/AllObsAmp3_test15/out1/",
						 "/home/louise/g8K0Sig/code/AllObsAmp3_test16/out1/"};
						 
	ofstream outfile;
    outfile.open(paths[0]+"MergedCsvAllBins.csv");
    
    int burnIn = 50;

	for (int pathIdx=0; pathIdx<4; pathIdx++) {
		
		auto topDir = opendir(paths[pathIdx].c_str());
		struct dirent *binDir;

		// read the directories in the topDir
		while (binDir=readdir(topDir)) {
			
			// does the directory listing start costh
			std::string dirStr = binDir->d_name;
			if (dirStr.substr(0, 5) == "costh") {
				
				cout << binDir->d_name << endl;
				// get the path to the bin dir
				std::string binPath = paths[pathIdx] + binDir->d_name;
				auto dir = opendir(binPath.c_str());
						
				std::string fileName = paths[pathIdx] + dirStr +  "/ResultsHSRooMcmcSeq.root";
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
						
				for (int i=burnIn; i<nObs; i++) {
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
	}
		
	outfile.close();
	
}
