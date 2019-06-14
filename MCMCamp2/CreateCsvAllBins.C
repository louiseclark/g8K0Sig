#include <dirent.h>
#include <string>

void CreateCsvAllBins() {
		
	std::string path = "/home/louise/g8K0Sig/code/MCMCamp2/out8/";
	auto topDir = opendir(path.c_str());
	struct dirent *eGammaDir;
	
	ofstream outfile;
    outfile.open(path+"CsvAllBins.csv");

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
					
					std::string fileName = path + dirStr+ "/" + dirStr2 + "/ResultsHSRooMcmcUniform2Seq.root";
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
						outfile << "B," << B << "," << dirStr2 << "\n";
						outfile << "Ox," << Ox << "," << dirStr2 << "\n";
						outfile << "Oz," << Oz << "," << dirStr2 << "\n";
						outfile << "R," << R << "," << dirStr2 << "\n";
						outfile << "T," << T << "," << dirStr2 << "\n";
					}
					
				}
			}
		}
	}
	closedir(topDir);
		
	outfile.close();
	
}
