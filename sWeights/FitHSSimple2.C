//Make data with
//root 'Model1.C( "Data.root" )'

{

  THSsPlot* RF=new THSsPlot("_all");
  RF->SetOutDir("out_all_pi0K0/");
 // RF->SetBinnedFit(); //For parameter fits do binned chi2
  
  ///////////////////////////////Load Variables
  
  // Fit the pi0 using previous weights from fitting the K0
  
  // pi0
  RF->LoadVariable("MM_p_pip_pim[0.08,0.22]");//should be same name as variable in tree  

  /////////////////////////////Make Model Signal
    
  // pi0
  RF->Factory("Gaussian::Signal( MM_p_pip_pim, SIMm[0.135,0.08,0.22], SIMw[0.01,0.001,0.02] )");
  RF->LoadSpeciesPDF("Signal");


  ////////////////////////////////Additional background
  RF->Factory("Chebychev::BG(MM_p_pip_pim,{a0[-0.1,-10,10],a1[0.1,-10,10],a2[0,-10,10]})");
  RF->LoadSpeciesPDF("BG");
  
   ///////////////////////////Load Data
  TChain chain("HSParticles");
  chain.Add("/w/work0/home/louise/g8K0Sig/convert_output/filepPi0_all.root");
  RF->SetIDBranchName("fgID");//This is not needed if all events from tree go into dataset, i.e. the variable ranges do not cut any events. It is safer to have it...
  //import to RooFit
  RF->LoadDataSet(&chain);

  // Weights from the K0 fit
  RF->LoadWeights("/home/louise/g8K0Sig/code/sWeights/out_all_K0/Weights_all.root","HSsWeights");
  RF->SetWeightName("Signal"); 
  RF->SetDataWeight();

  gBenchmark->Start("Simple");
  RF->FitAndStudy(1); //argument gives number of parameter fits to perform
  //Do some other stuff before saving weights
  RF->DrawTreeVar("M_p_pi0",100,0.8,1.8);
  RF->DrawTreeVar("MM_p_pip_pim",100,0.0,0.5);
  RF->DrawTreeVar("M_pip_pim",100,0.3,0.8);
  RF->DrawTreeVar("MM_p",100,0.0,1.7);
  gBenchmark->Stop("Simple");
  gBenchmark->Print("Simple");
  RF->GetWeights()->Save();
  RF->SaveHists("out_all_pi0K0/Hists_all.root");

}
