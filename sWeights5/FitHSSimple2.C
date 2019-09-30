//Run with 
//root --hsfit FitHSSimple2.C
{
  TString pwd = TString(gSystem->Getenv("PWD"))+"/";
  sPlot RF;
  RF.SetUp().SetOutDir(pwd+"out_all_pi0K0_binned/");
  ///////////////////////////////Load Variables
  RF.SetUp().LoadVariable("M_pip_pim[0.45,0.55]");//should be same name as variable in tree  
  RF.SetUp().SetIDBranchName("fgID");

  /////////////////////////////Make Model Signal
  RF.SetUp().FactoryPDF("Gaussian::Signal(M_pip_pim, SIMm[0.495,0.45,0.55], SIMw[0.01,0.001,0.02] )");
  RF.SetUp().LoadSpeciesPDF("Signal",1);


  ////////////////////////////////Additional background
  RF.SetUp().FactoryPDF("Chebychev::BG(M_pip_pim,{a0[-0.1,-1,1],a1[0.1,-1,1]})");
  RF.SetUp().LoadSpeciesPDF("BG",1);
  
  // Ewald bins for P
  RF.Bins().LoadBinVar("costhK0CMS",6,-1.0,1.0);
  RF.Bins().LoadBinVar("Egamma",4, 1.05, 2.25);  

  ///////////////////////////Load Data
  //RF.Data().BootStrap(4);//split the data in 4 seperate fits
  RF.LoadData("HSParticles","/w/work0/home/louise/g8K0Sig/convert_output/filepPi0_all.root");

  RF.Data().LoadWeights("Signal","/home/louise/g8K0Sig/code/sWeights4/out_all_pi0_binned/Tweights.root");
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
