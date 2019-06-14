//Run with 
//root --hsfit FitObsBins.C > out.txt
{
 
  Loader::Compile("ObsFit.cxx");
  
  //get the current directory where the data is (PROOF needs full path)
  TString pwd = TString(gSystem->Getenv("PWD"))+"/";
  
  FitManager RF;
  RF.SetUp().SetOutDir(pwd+"out9.6/");
  ///////////////////////////////Load Variables  
  RF.SetUp().LoadVariable("phiK0[-3.14,3.14]");//going to fit this
  RF.SetUp().LoadVariable("cosX[-1.0,1.0]");
  RF.SetUp().LoadVariable("cosY[-1.0,1.0]");
  RF.SetUp().LoadVariable("cosZ[-1.0,1.0]");
  RF.SetUp().LoadVariable("pol[0,1]");
  RF.SetUp().LoadCategory("polState[Polp=1,Polm=-1]");//Load a category  
  //RF.SetUp().LoadAuxVar("AUX[0,300]"); //Load Aux Var, limits used as cut 
  RF.SetUp().SetIDBranchName("fgID");

  ///////////////////////////////Make additional cut on an AuxVar
  //RF.SetUp().AddCut("AUX>2"); //Additional cut based on vars or aux vars

  /////////////////////////////Make Model Signal
  //RF.SetUp().FactoryPDF("ObsFit::LinPolFit(phiK0,cosX,cosY,cosZ,pol,polState,B[0.556,-1.0,1.0],T[0.248,-1.0,1.0],Ox[0.242,-1.0,1.0],Oz[-0.4755,-1.0,1.0],R[0.233,-1.0,1.0])");
  RF.SetUp().FactoryPDF("ObsFit::LinPolFit(phiK0,cosX,cosY,cosZ,pol,polState,B[0.0,-1.0,1.0],T[0.0,-1.0,1.0],Ox[0.0,-1.0,1.0],Oz[-0.0,-1.0,1.0],R[0.0,-1.0,1.0])");
  RF.SetUp().LoadSpeciesPDF("LinPolFit",1);

  ////////////////////////////Make Bins
  RF.Bins().LoadBinVar("costhK0CMS",1,0.33,1.0);
  RF.Bins().LoadBinVar("Egamma",1, 1.6, 2.1);
   
  ///////////////////////////Load Data
  //RF.Data().BootStrap(2);
  RF.LoadData("HSParticles","/w/work0/home/louise/g8K0Sig/convert_output/filepPi0_all.root");
  RF.LoadSimulated("HSParticles","/w/work0/home/louise/g8K0Sig/convert_output_MC/filepPi0_all.root","LinPolFit");
  
  //////////////////////////Load Weights
  RF.Data().LoadWeights("Signal","/home/louise/g8K0Sig/code/sWeights2/out_all_pi0K0/Weights.root");

  RF.SetMinimiser(new RooMcmcUniform2Seq(2000,50,2)); // num of steps in final tree, burn in, inverse step size
  //use Minuit2(5) to run 5 fits and take the best likelihood
  //RF.SetMinimiser(new Minuit());
  //RF.SetMinimiser(new Minuit2());
  
  Here::Go(&RF);
   
  //Proof::Go(&RF,6); // set to num bins for minuit fit
 
}
