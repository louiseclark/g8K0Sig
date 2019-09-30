//Run with 
//root --hsfit FitObsBins.C > out.log
// or 
//root --hsfit FitObsBins.C | tee out.log
{
 
  Loader::Compile("ObsFit.cxx");
  
  //get the current directory where the data is (PROOF needs full path)
  TString pwd = TString(gSystem->Getenv("PWD"))+"/";
  
  FitManager RF;
  RF.SetUp().SetOutDir(pwd+"outBG/");
  ///////////////////////////////Load Variables  
  RF.SetUp().LoadVariable("phiK0[-3.14,3.14]");//going to fit this
  RF.SetUp().LoadVariable("cosX[-1.0,1.0]");
  RF.SetUp().LoadVariable("cosY[-1.0,1.0]");
  RF.SetUp().LoadVariable("cosZ[-1.0,1.0]");
  RF.SetUp().LoadVariable("pol[0,1]");
  RF.SetUp().LoadCategory("polState[Polp=1,Polm=-1]");//Load a category  
  //RF.SetUp().LoadAuxVar("AUX[0,300]"); //Load Aux Var, limits used as cut 
  RF.SetUp().SetIDBranchName("fgID");

  RF.SetUp().LoadFormula("r=sqrt(@a1Re[0.0,-1.0,1.0]*@a1Re[]+@a1Im[0.0,-1.0,1.0]*@a1Im[]+@a2Re[0.0,-1.0,1.0]*@a2Re[]+@a2Im[0.0,-1.0,1.0]*@a2Im[]+@a3Re[0.0,-1.0,1.0]*@a3Re[]+@a3Im[0.0,-1.0,1.0]*@a3Im[]+@a4Re[0.0,-1.0,1.0]*@a4Re[]+@a4Im[0.0,-1.0,1.0]*@a4Im[])");
  RF.SetUp().LoadFormula("B=((@a1Re[]*@a1Re[]+@a1Im[]*@a1Im[])+(@a2Re[]*@a2Re[]+@a2Im[]*@a2Im[])-(@a3Re[]*@a3Re[]+@a3Im[]*@a3Im[])-(@a4Re[]*@a4Re[]+@a4Im[]*@a4Im[]))/@r[]");
  RF.SetUp().LoadFormula("T=((@a1Re[]*@a1Re[]+@a1Im[]*@a1Im[])-(@a2Re[]*@a2Re[]+@a2Im[]*@a2Im[])-(@a3Re[]*@a3Re[]+@a3Im[]*@a3Im[])+(@a4Re[]*@a4Re[]+@a4Im[]*@a4Im[]))/@r[]");
  RF.SetUp().LoadFormula("Ox=2.0*((@a1Re[]*@a4Re[]+@a1Im[]*@a4Im[]+@a2Re[]*@a3Re[]+@a2Im[]*@a3Im[])/@r[])");
  RF.SetUp().LoadFormula("Oz=2.0*((@a1Im[]*@a4Re[]-@a1Re[]*@a4Im[]+@a2Re[]*@a3Im[]-@a2Im[]*@a3Re[])/@r[])");
  RF.SetUp().LoadFormula("R=((@a1Re[]*@a1Re[]+@a1Im[]*@a1Im[])-(@a2Re[]*@a2Re[]+@a2Im[]*@a2Im[])+(@a3Re[]*@a3Re[]+@a3Im[]*@a3Im[])-(@a4Re[]*@a4Re[]+@a4Im[]*@a4Im[]))/@r[]");
    
  /////////////////////////////Make Model Signal
  RF.SetUp().FactoryPDF("ObsFit::LinPolFit(phiK0,cosX,cosY,cosZ,pol,polState,B,T,Ox,Oz,R)");
  RF.SetUp().LoadSpeciesPDF("LinPolFit",1);

  ////////////////////////////Make Bins
  
  // Ewald bins
  RF.Bins().LoadBinVar("costhK0CMS",5,-1.0,1.0);
  RF.Bins().LoadBinVar("Egamma",3, 1.05, 1.65); 
   
  ///////////////////////////Load Data
  //RF.Data().BootStrap(2);
  RF.LoadData("HSParticles","/w/work0/home/louise/g8K0Sig/convert_output/filepPi0_all.root");
  RF.LoadSimulated("HSParticles","/w/work0/home/louise/g8K0Sig/convert_output_MC/filepPi0_all.root","LinPolFit");
  
  //////////////////////////Load Weights
  RF.Data().LoadWeights("BG","/home/louise/g8K0Sig/code/sWeights4/out_all_pi0K0_binned/Tweights.root");
  
  //RF.SetMinimiser(new RooMcmcUniform2Seq(2000,50,2)); // num of steps in final tree, burn in, inverse step size
  //use Minuit2(5) to run 5 fits and take the best likelihood
  //RF.SetMinimiser(new Minuit());
  RF.SetMinimiser(new Minuit2());
  
  Here::Go(&RF);
   
  //Proof::Go(&RF,6); // set to num bins for minuit fit
 
}
