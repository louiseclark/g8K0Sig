//Run with 
//root --hsfit FitHSAsymmetryBins.C --BeamAsym.cxx
{
  //Create THSRooFit manager 
  THSRooFit* RF=new THSRooFit("AFit");
  RF->SetOutDir("out2"); //give output directory
  //RF->SetBinnedFit();

  ///////////////////////////////Load Variables
  RF->LoadVariable("phiSigma[-3.14,3.14]");//going to fit this
  RF->LoadVariable("pol[0,1]");
  RF->LoadVariable("polState[Polp=1,Polm=-1]");//Load a category

  RF->SetIDBranchName("fgID");
  
  //RF->LoadBinVars("t",4,0,1.6);
  //Double_t binLimits[] = {0.1, 0.46, 0.58, 0.8, 1.6};
  //Double_t binLimits[] = {0.1, 0.4125, 0.4875, 0.5625, 0.6625, 0.8125, 1.6};
  //RF->LoadBinVars("t",4,binLimits);

  //RF->LoadBinVars("cosThetaPhiCm",4,-1.0,1.0);
  //Double_t binLimits[] = {-1.0, -0.15, 0.25, 0.51, 1.0};
  //RF->LoadBinVars("cosThetaPhiCm",4,binLimits);
  
  RF->LoadBinVars("Egamma",5,1.1,2.1);
  //Double_t ebinLimits[] = {1.5, 1.94, 2.1};
  //Double_t ebinLimits[] = {1.5, 1.865, 2.1};
  //RF->LoadBinVars("Egamma",2,ebinLimits);

 
  TChain *chainData=new TChain("HSParticles");  
  chainData->Add("/w/work0/home/louise/g8K0Sig/convert_output/filepPi0_all.root");
  //////////////////////////////Split data into bins and load them
  RF->MakeBinnedTrees(chainData,"Data");
  
  TChain *chainMC=new TChain("HSParticles");  
  //chainMC->Add("/w/work0/home/louise/g8K0Sig/convert_output_MC/filepPi0_MC.root");
  chainMC->Add("/home/louise/g8_phi/haspect/Events/Projects/g8phi/convert_output_MC10M/file_all.root");

 
  RF->MakeBinnedTrees(chainMC,"BeamAsymFit");
  
  
  RF->ConfigureSavedBins(RF->GetOutDir());

  
  // Default starting values 
  RF->Factory("BeamAsym::BeamAsymFit(phiSigma,pol,polState,beamAsym[0,-10.0,10.0])");
 
  RooHSEventsPDF* PDF=dynamic_cast<RooHSEventsPDF*>(RF->GetWorkSpace()->pdf("BeamAsymFit"));
  
  
  cout<<"PDF "<<PDF<<endl;
  RF->LoadSpeciesPDF("BeamAsymFit");
  RF->TotalPDF();  
  
  // load weights for the simulation (importance sampling to make simulation like data)
  //PDF->LoadWeights("LikeData","/home/louise/g8_phi/ImportanceSampling/impWeights.root","impWeights"); 

  // load weights for the data (signal weights)
  RF->LoadWeights("/home/louise/g8K0Sig/code/sWeights/out_all/Weights_all.root","HSsWeights");
  RF->SetWeightName("Signal");
 
  //RF->SetFitMethod(1); // this was causing issue, removing means default method 0 is used
  RF->FitSavedBins(1);
  
}
