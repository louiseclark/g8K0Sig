//Run with 
//root --hsfit FitHSAsymmetryBins.C --BeamAsym.cxx
{
  //Create THSRooFit manager 
  THSRooFit* RF=new THSRooFit("AFit");
  RF->SetOutDir("out2"); //give output directory
  //RF->SetBinnedFit();

  ///////////////////////////////Load Variables
  RF->LoadVariable("phiK0[-3.14,3.14]");//going to fit this
  RF->LoadVariable("cosX[-1.0,1.0]");
  RF->LoadVariable("cosY[-1.0,1.0]");
  RF->LoadVariable("cosZ[-1.0,1.0]");
  RF->LoadVariable("pol[0,1]");
  RF->LoadVariable("polState[Polp=1]");//Load a category
 //RF->LoadVariable("polState[Polp=1,Polm=-1]");//Load a category

  RF->SetIDBranchName("fgID");
  
 
  TChain *chainData=new TChain("HSParticles");  
  chainData->Add("/w/work0/home/louise/g8K0Sig/convert_output/filepPi0_all.root");
  RF->LoadDataSet(chainData);
   
  TChain *chainMC=new TChain("HSParticles");  
  chainMC->Add("/w/work0/home/louise/g8K0Sig/convert_output_MC/filepPi0_all.root");

 
  
  // Default starting values 
  RF->Factory("LinPolPDF::LinPolFit(phiK0,cosX,cosY,cosZ,pol,polState,B[0.4,-1.2,1.2],T[0.0,-1.2,1.2],Ox[0.0,-1.2,1.2],Oz[0.0,-1.2,1.2],R[0.0,-1.2,1.2])");
 
  RooHSEventsPDF* PDF=dynamic_cast<RooHSEventsPDF*>(RF->GetWorkSpace()->pdf("LinPolFit"));
  PDF->SetEvTree(chainMC,RF->GetCut());
  PDF->AddProtoData(RF->GetDataSet());
  
  cout<<"PDF "<<PDF<<endl;
  RF->LoadSpeciesPDF("LinPolFit",10000);
  RF->TotalPDF();  
  PDF->SetUseWeightsGen(kFALSE);
  RF->GenerateToys(2);
}
