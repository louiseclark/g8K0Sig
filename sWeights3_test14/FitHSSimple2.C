//Run with 
//brufit FitHSSimple2.C
{
  TString pwd = TString(gSystem->Getenv("PWD"))+"/";
  sPlot RF;
  //RF.SetUp().SetOutDir(pwd+"out_all_pi0K0_binned/Egamma1.23/");
  //RF.SetUp().SetOutDir(pwd+"out_all_pi0K0_binned/Egamma1.48/");
  //RF.SetUp().SetOutDir(pwd+"out_all_pi0K0_binned/Egamma1.73/");
  RF.SetUp().SetOutDir(pwd+"out_all_pi0K0_binned/Egamma1.98/");
  
  ///////////////////////////////Load Variables
  RF.SetUp().LoadVariable("M_pip_pim[0.4625,0.535]"); // Test 3
  RF.SetUp().SetIDBranchName("fgID");

  /////////////////////////////Make Model Signal
  //RF.SetUp().FactoryPDF("Gaussian::Signal(M_pip_pim, SIMm[0.495,0.40,0.60], SIMw[0.01,0.001,0.02] )"); // test 3
  RF.SetUp().FactoryPDF("Gaussian::Signal(M_pip_pim, SIMm[0.495,0.40,0.60], SIMw[0.004,0.001,0.008] )"); // test 14
  RF.SetUp().LoadSpeciesPDF("Signal",1);


  ////////////////////////////////Additional background
  RF.SetUp().FactoryPDF("Chebychev::BG(M_pip_pim,{a0[-0.1,-1,1],a1[0.1,-1,1]})");
  RF.SetUp().LoadSpeciesPDF("BG",1);
  
  // Variable bins Egamma 1.1-1.35
  //Double_t binLimits[] = {-1.0, -0.622, -0.39, -0.146, 0.054, 0.298, 1.0};
  //RF.Bins().LoadBinVar("costhK0CMS",6,binLimits);
  //RF.Bins().LoadBinVar("Egamma",1, 1.1, 1.35);

  // Variable bins Egamma 1.35-1.6
  //Double_t binLimits[] = {-1.0, -0.465, -0.275, -0.135, 0.005, 0.165, 0.345, 0.535, 1.0}; // 0.785
  //RF.Bins().LoadBinVar("costhK0CMS",8,binLimits);
  //RF.Bins().LoadBinVar("Egamma",1, 1.35, 1.6);
  
  // Variable bins Egamma 1.6-1.85
  //Double_t binLimits[] = {-1.0, -0.175, 0.035, 0.295, 0.505, 1.0}; // 0.835
  //RF.Bins().LoadBinVar("costhK0CMS",5,binLimits);
  //RF.Bins().LoadBinVar("Egamma",1, 1.6, 1.85);  

  // Variable bins Egamma 1.85-2.1
  Double_t binLimits[] = {-1.0, 0.155, 1.0}; // 0.775
  RF.Bins().LoadBinVar("costhK0CMS",2,binLimits);
  RF.Bins().LoadBinVar("Egamma",1, 1.85, 2.1); 

  ///////////////////////////Load Data
  //RF.Data().BootStrap(4);//split the data in 4 seperate fits
  RF.LoadData("HSParticles","/w/work0/home/louise/g8K0Sig/convert_output/filepPi0_all.root");

  //RF.Data().LoadWeights("Signal","/home/louise/g8K0Sig/code/sWeights3/out_all_pi0_binned/Egamma1.23/Tweights.root");
  //RF.Data().LoadWeights("Signal","/home/louise/g8K0Sig/code/sWeights3/out_all_pi0_binned/Egamma1.48/Tweights.root");
  //RF.Data().LoadWeights("Signal","/home/louise/g8K0Sig/code/sWeights3/out_all_pi0_binned/Egamma1.73/Tweights.root");
  RF.Data().LoadWeights("Signal","/home/louise/g8K0Sig/code/sWeights3/out_all_pi0_binned/Egamma1.98/Tweights.root");
  
  //Do we want to try many fits and use the best?
  //This will randomise the parameters for each fit
  //  RF.SetRefit(2);

  //Run the fit here or on PROOF
  Here::Go(&RF);
  //Proof::Go(&RF,4); //run proof with 4 workers
 
  new TCanvas;
  RF.DrawWeighted("M_p_pi0>>(100,0.8,1.8)","Signal");
  RF.DrawWeighted("MM_p_pip_pim>>(100,0.0,0.5)","Signal");
  RF.DrawWeighted("M_pip_pim>>(100,0.3,0.8)","Signal");
  RF.DrawWeighted("MM_p>>(100,0.0,1.7)","Signal");
  
}
