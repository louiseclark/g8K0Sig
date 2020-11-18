//Run with 
//brufit FitObsBins.C > out1.log
// or 
//brufit FitObsBins.C | tee out1.log
{
 
  Loader::Compile("ObsFit.cxx");
  
  //get the current directory where the data is (PROOF needs full path)
  TString pwd = TString(gSystem->Getenv("PWD"))+"/";
  
  FitManager RF;
  RF.SetUp().SetOutDir(pwd+"out1/");
  ///////////////////////////////Load Variables  
  RF.SetUp().LoadVariable("phiK0[-3.14,3.14]");//going to fit this
  RF.SetUp().LoadVariable("cosX[-1.0,1.0]");
  RF.SetUp().LoadVariable("cosY[-1.0,1.0]");
  RF.SetUp().LoadVariable("cosZ[-1.0,1.0]");
  RF.SetUp().LoadVariable("pol[0,1]");
  RF.SetUp().LoadCategory("polState[Polp=1,Polm=-1]");//Load a category  
  //RF.SetUp().LoadAuxVar("AUX[0,300]"); //Load Aux Var, limits used as cut 
  RF.SetUp().SetIDBranchName("fgID");

  RF.SetUp().LoadFormula("r2=@a1Re[0.5,-1.0,1.0]*a1Re+@a1Im[0.0,-1.0,1.0]*a1Im+@a2Re[0.0,-1.0,1.0]*a2Re+@a2Im[0.0,-1.0,1.0]*a2Im+@a3Re[0.0,-1.0,1.0]*a3Re+@a3Im[0.0,-1.0,1.0]*a3Im+@a4Re[0.0,-1.0,1.0]*a4Re+@a4Im[0.0,-1.0,1.0]*a4Im");
  RF.SetUp().LoadFormula("B=((@a1Re[]*@a1Re[]+@a1Im[]*@a1Im[])+(@a2Re[]*@a2Re[]+@a2Im[]*@a2Im[])-(@a3Re[]*@a3Re[]+@a3Im[]*@a3Im[])-(@a4Re[]*@a4Re[]+@a4Im[]*@a4Im[]))/@r2[]");
  RF.SetUp().LoadFormula("T=((@a1Re[]*@a1Re[]+@a1Im[]*@a1Im[])-(@a2Re[]*@a2Re[]+@a2Im[]*@a2Im[])-(@a3Re[]*@a3Re[]+@a3Im[]*@a3Im[])+(@a4Re[]*@a4Re[]+@a4Im[]*@a4Im[]))/@r2[]");
  RF.SetUp().LoadFormula("Ox=2.0*((@a1Re[]*@a4Re[]+@a1Im[]*@a4Im[]+@a2Re[]*@a3Re[]+@a2Im[]*@a3Im[])/@r2[])");
  RF.SetUp().LoadFormula("Oz=2.0*((@a1Im[]*@a4Re[]-@a1Re[]*@a4Im[]+@a2Re[]*@a3Im[]-@a2Im[]*@a3Re[])/@r2[])");
  RF.SetUp().LoadFormula("R=((@a1Re[]*@a1Re[]+@a1Im[]*@a1Im[])-(@a2Re[]*@a2Re[]+@a2Im[]*@a2Im[])+(@a3Re[]*@a3Re[]+@a3Im[]*@a3Im[])-(@a4Re[]*@a4Re[]+@a4Im[]*@a4Im[]))/@r2[]");

  RF.SetUp().LoadFormula("Cx=2.0*((@a1Im[]*@a4Re[]-@a1Re[]*@a4Im[]-@a2Re[]*@a3Im[]+@a2Im[]*@a3Re[])/@r2[])");
  RF.SetUp().LoadFormula("Cz=2.0*((@a1Re[]*@a4Re[]+@a1Im[]*@a4Im[]-@a2Re[]*@a3Re[]-@a2Im[]*@a3Im[])/@r2[])");
  
  /////////////////////////////Make Model Signal
  //RF.SetUp().FactoryPDF("ObsFit::LinPolFit(phiK0,cosX,cosY,cosZ,pol,polState,B,T,Ox,Oz,R)");
  //RF.SetUp().FactoryPDF("ObsFit::LinPolFit(phiK0,cosX,cosY,cosZ,pol,polState,B,T,Ox,Oz,R)WEIGHTS@LikeData,fullpath and name.root,name of weights objects");
  RF.SetUp().FactoryPDF("ObsFit::LinPolFit(phiK0,cosX,cosY,cosZ,pol,polState,B,T,Ox,Oz,R)WEIGHTS@LikeData,/home/louise/g8K0Sig/code/simWeights/new/out/impWeights_tE.root,impWeights");
  RF.SetUp().LoadSpeciesPDF("LinPolFit",1);
  
  // Peter's sample code
  //
  //RF.SetUp().FactoryPDF("RooComponentsPDF::SDMES(0,{Theta_GJ_KMinus,phiAngle_GJ_KMinus,phiAngle_KPlus,polarisationAngle,polarisationDegree},=A:B;Rho011:C;Rho031:D;Rho03m1:E;Rho133:F;Rho111:G;Rho131:H;Rho13m1:I;Rho231:J;Rho23m1)WEIGHTS@LikeData,"+weightsDir+"/impWeights.root,impWeights");


  ////////////////////////////Make Bins
    
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
  //RF.Data().BootStrap(2);
  RF.LoadData("HSParticles","/w/work0/home/louise/g8K0Sig/convert_output3/filepPi0_all.root");
  RF.LoadSimulated("HSParticles","/w/work0/home/louise/g8K0Sig/convert_output_MC/filepPi0_all.root","LinPolFit");
  
  //////////////////////////Load Weights
  //RF.Data().LoadWeights("Signal","/home/louise/g8K0Sig/code/sWeights3_test15/out_all_pi0K0_binned/Egamma1.23/Tweights.root");
  //RF.Data().LoadWeights("Signal","/home/louise/g8K0Sig/code/sWeights3_test15/out_all_pi0K0_binned/Egamma1.48/Tweights.root");
  //RF.Data().LoadWeights("Signal","/home/louise/g8K0Sig/code/sWeights3_test15/out_all_pi0K0_binned/Egamma1.73/Tweights.root");
  RF.Data().LoadWeights("Signal","/home/louise/g8K0Sig/code/sWeights3_test15/out_all_pi0K0_binned/Egamma1.98/Tweights.root");

  RF.SetMinimiser(new RooMcmcSeq(2000,50,2)); // num of steps in final tree, burn in, inverse step size
  //RF.SetMinimiser(new RooMcmcUniform2Seq(2000,50,2)); // num of steps in final tree, burn in, inverse step size
  //use Minuit2(5) to run 5 fits and take the best likelihood
  //RF.SetMinimiser(new Minuit());
  //RF.SetMinimiser(new Minuit2());
  
  RF.SetUp().AddFitOption(RooFit::Optimize(1));
  
  Here::Go(&RF);
   
  //Proof::Go(&RF,6); // set to num bins for minuit fit
 
}
