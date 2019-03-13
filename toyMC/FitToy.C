{

	//gROOT->LoadMacro("CreateModel.C");
	//Create THSRooFit manager 
  THSRooFit* RF=new THSRooFit("AFit");
  RF->SetOutDir("out1Toy"); //give output directory
  //RF->SetBinnedFit();

  ///////////////////////////////Load Variables
  RF->LoadVariable("phiK0[-3.14,3.14]");//going to fit this
  RF->LoadVariable("cosX[-1.0,1.0]");
  RF->LoadVariable("cosY[-1.0,1.0]");
  RF->LoadVariable("cosZ[-1.0,1.0]");
  RF->LoadVariable("pol[0,1]");
  RF->LoadVariable("polState[Polp=1,Polm=-1]");//Load a category

  RF->SetIDBranchName("fgID");
  //RF->SetOutDir("./");
  
	TDirectory* savedir=gDirectory;
	TFile* datafile=new TFile("out2/Toy_1.root");
	RooDataSet* ds = dynamic_cast<RooDataSet*>( datafile->Get("ToyData"));
	savedir->cd();
	gDirectory=savedir;
  
	RF->LoadDataSet(ds);
	
	TChain *chainMC=new TChain("HSParticles");  
    chainMC->Add("/w/work0/home/louise/g8K0Sig/convert_output_MC/filepPi0_all.root");

 
  
  // Default starting values 
  RF->Factory("LinPolPDF::LinPolFit(phiK0,cosX,cosY,cosZ,pol,polState,B[0.4,-1.2,1.2],T[0.0,-1.2,1.2],Ox[0.0,-1.2,1.2],Oz[0.0,-1.2,1.2],R[0.0,-1.2,1.2])");
 
  RooHSEventsPDF* PDF=dynamic_cast<RooHSEventsPDF*>(RF->GetWorkSpace()->pdf("LinPolFit"));
  PDF->SetEvTree(chainMC,RF->GetCut());
  PDF->AddProtoData(ds);
   RF->LoadSpeciesPDF("LinPolFit");
  RF->TotalPDF();  
 
    RF->SetFitMethod(2);  // MCMC
	RF->SetNMCMC(10000,100);
 
	RF->FitAndStudy(1);
}
