//Run with 
//root --hsfit FitHSAsymmetryBins.C --LinPolPDF.cxx
{
  //Create THSRooFit manager 
  THSRooFit* RF=new THSRooFit("AFit");
  RF->SetOutDir("out12"); //give output directory
  //RF->SetBinnedFit();

  ///////////////////////////////Load Variables
  RF->LoadVariable("phiK0[-3.14,3.14]");//going to fit this
  RF->LoadVariable("cosX[-1.0,1.0]");
  RF->LoadVariable("cosY[-1.0,1.0]");
  RF->LoadVariable("cosZ[-1.0,1.0]");
  RF->LoadVariable("pol[0,1]");
  RF->LoadVariable("polState[Polp=1,Polm=-1]");//Load a category

  RF->SetIDBranchName("fgID");
  
  //RF->LoadBinVars("t",4,0,1.6);
  //Double_t binLimits[] = {0.1, 0.46, 0.58, 0.8, 1.6};
  //Double_t binLimits[] = {0.1, 0.4125, 0.4875, 0.5625, 0.6625, 0.8125, 1.6};
  //RF->LoadBinVars("t",4,binLimits);

  //RF->LoadBinVars("costhK0CMS",3,-1.0,1.0);
  RF->LoadBinVars("costhK0CMS",1,0.33,1.0);
  //Double_t binLimits[] = {-1.0, -0.15, 0.25, 0.51, 1.0};
  //RF->LoadBinVars("cosThetaPhiCm",4,binLimits);
  
  //RF->LoadBinVars("Egamma",2,1.1,2.1);
  RF->LoadBinVars("Egamma",1, 1.6, 2.1);
  //Double_t ebinLimits[] = {1.5, 1.94, 2.1};
  //Double_t ebinLimits[] = {1.5, 1.865, 2.1};
  //RF->LoadBinVars("Egamma",2,ebinLimits);

 
  TChain *chainData=new TChain("HSParticles");  
  chainData->Add("/w/work0/home/louise/g8K0Sig/convert_output/filepPi0_all.root");
  //////////////////////////////Split data into bins and load them 
  RF->MakeBinnedTrees(chainData,"Data");
  
  TChain *chainMC=new TChain("HSParticles");  
  chainMC->Add("/w/work0/home/louise/g8K0Sig/convert_output_MC/filepPi0_all.root");

 
  RF->MakeBinnedTrees(chainMC,"LinPolFit");
  
  
  RF->ConfigureSavedBins(RF->GetOutDir());

  
  // Default starting values 
  RF->Factory("LinPolPDF::LinPolFit(phiK0,cosX,cosY,cosZ,pol,polState,B[0.55,-1.0,1.0],T[0.248,-1.0,1.0],Ox[0.242,-1.0,1.0],Oz[-0.4755,-1.0,1.0],R[0.233,-1.0,1.0])");
 
  // Set some parameters to constant
  //RF->GetWorkSpace()->var("B")->setConstant();
  //RF->GetWorkSpace()->var("Ox")->setConstant();
  RF->GetWorkSpace()->var("Oz")->setConstant();
  RF->GetWorkSpace()->var("R")->setConstant();
  RF->GetWorkSpace()->var("T")->setConstant();
 
  RooHSEventsPDF* PDF=dynamic_cast<RooHSEventsPDF*>(RF->GetWorkSpace()->pdf("LinPolFit"));
  
  cout<<"PDF "<<PDF<<endl;
  RF->LoadSpeciesPDF("LinPolFit");
  RF->TotalPDF();  
  
  // load weights for the simulation (importance sampling to make simulation like data)
  //PDF->LoadWeights("LikeData","/home/louise/g8_phi/ImportanceSampling/impWeights.root","impWeights"); 

  // load weights for the data (signal weights)
  RF->LoadWeights("/home/louise/g8K0Sig/code/sWeights/out_all_pi0K0/Weights_all.root","HSsWeights");
  RF->SetWeightName("Signal");
 
  //RF->SetFitMethod(1); // this was causing issue, removing means default method 0 is used
  RF->SetFitMethod(2);  // MCMC
  RF->SetNMCMC(20000,0);
  
  // define proposal
  cout<<"Calling set proposal"<<endl;
  //RF->SetProposal(1); // uniform
  
  RF->SetProposal(0); // step
  RF->SetStepMCMC(0.1);
  
  RF->SetNStudyTrials(1);
  RF->FitSavedBins(1);
  
}
