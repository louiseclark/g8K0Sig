//Run with 
//root --hsfit FitObsBins.C > out1.log
// or 
//root --hsfit FitObsBins.C | tee out1.log
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

  RF.SetUp().LoadParameter("alpha[-0.980]");
  RF.SetUp().LoadFormula("COS2=@pol[]*@polState[]*cos(2*@phiK0[])*-1.0");
  RF.SetUp().LoadFormula("SIN2=@pol[]*@polState[]*sin(2*@phiK0[])*-1.0");
  RF.SetUp().LoadFormula("COSX=@cosX[]");
  RF.SetUp().LoadFormula("COSY=@cosY[]");
  RF.SetUp().LoadFormula("COSZ=@cosZ[]");

  // Use these to step around in observable space
  RF.SetUp().LoadParameter("B[0,-1,1]");
  RF.SetUp().LoadParameter("R[0,-1,1]");
  RF.SetUp().LoadParameter("T[0,-1,1]");
  RF.SetUp().LoadParameter("Ox[0,-1,1]");
  RF.SetUp().LoadParameter("Oz[0,-1,1]");
    
  /////////////////////////////Make Model Signal
  RF.SetUp().FactoryPDF("RooComponentsPDF::LinPolFit(1,{phiK0,cosX,cosY,cosZ,pol,polState},=R;alpha;COSY:B;COS2:T;alpha;COSY;COS2:SIN2;alpha;COSX;Ox:SIN2;alpha;COSZ;Oz)");
  RF.SetUp().LoadSpeciesPDF("LinPolFit",1);

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
  //RF.Data().LoadWeights("Signal","/home/louise/g8K0Sig/code/sWeights3_test7/out_all_pi0K0_binned/Egamma1.23/Tweights.root");
  //RF.Data().LoadWeights("Signal","/home/louise/g8K0Sig/code/sWeights3_test7/out_all_pi0K0_binned/Egamma1.48/Tweights.root");
  //RF.Data().LoadWeights("Signal","/home/louise/g8K0Sig/code/sWeights3_test7/out_all_pi0K0_binned/Egamma1.73/Tweights.root");
  RF.Data().LoadWeights("Signal","/home/louise/g8K0Sig/code/sWeights3_test7/out_all_pi0K0_binned/Egamma1.98/Tweights.root");

  RF.SetMinimiser(new RooMcmcSeq(2000,50,2)); // num of steps in final tree, burn in, inverse step size
  //RF.SetMinimiser(new RooMcmcUniform2Seq(2000,50,2)); // num of steps in final tree, burn in, inverse step size
  
  Here::Go(&RF);
   
  //Proof::Go(&RF,6); // set to num bins for minuit fit
 
}
