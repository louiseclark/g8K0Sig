{

  TString job=gSystem->Getenv("JOBNAME");
  TString fileDir=gSystem->Getenv("FILEDIR");
  TString prevFitDir=gSystem->Getenv("PREVFITNAME");
  TString weightsPath = fileDir + "/" + prevFitDir + "/Weights" + job + ".root";
  cout << " The weights from the previous fit that will be used for this fit are taken from " <<weightsPath <<endl; 
  
  THSsPlot* RF=new THSsPlot(job);
//  RF->LoadVariable("Coplanarity[-50,50]");//should be same name as variable in tree 
  RF->LoadVariable("MissMass[1850,2300]");//should be same name as variable in tree 
  RooRealVar * var=RF->GetWorkSpace()->var("MissMass");
  var->setBins(100); //number of bins used in PDF histogram
  RF->SetIDBranchName("UID");//this is needed if ID != "UID"

  RF->SetBinDir(fileDir+"/"+job);
//  RF->ConfigureSavedBins("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/Fitting/All3Binned1FilesProtonW10/");
 
  RF->Factory("RooHSEventsHistPDF::Sig(MissMass,alpha[0,0,50],off[0,-100,100],scale[1,0.8,1.2])");
  RooHSEventsHistPDF* pdf=dynamic_cast<RooHSEventsHistPDF*>(RF->GetWorkSpace()->pdf("Sig"));
  RF->LoadSpeciesPDF("Sig",1);



  RF->Factory("RooHSEventsHistPDF::NPipPi0(MissMass,alphaNPipPi0[0,0,20],offNPipPi0[0,-20,20],scaleNPipPi0[1,0.8,1.2])");
  RooHSEventsHistPDF* pdfNPipPi0=dynamic_cast<RooHSEventsHistPDF*>(RF->GetWorkSpace()->pdf("NPipPi0"));
  RF->LoadSpeciesPDF("NPipPi0",1);

  RF->Factory("RooHSEventsHistPDF::PPi0Pim(MissMass,alphaPPi0Pim[0,0,20],offPPi0Pim[0,-20,20],scalePPi0Pim[1,0.8,1.2])");
  RooHSEventsHistPDF* pdfPPi0Pim=dynamic_cast<RooHSEventsHistPDF*>(RF->GetWorkSpace()->pdf("PPi0Pim"));
  RF->LoadSpeciesPDF("PPi0Pim",1);

  RF->GetWorkSpace()->var("scaleNPipPi0")->setConstant();
  RF->GetWorkSpace()->var("alphaNPipPi0")->setConstant();
  RF->GetWorkSpace()->var("offNPipPi0")->setConstant();

  RF->GetWorkSpace()->var("scalePPi0Pim")->setConstant();
  RF->GetWorkSpace()->var("alphaPPi0Pim")->setConstant();
  RF->GetWorkSpace()->var("offPPi0Pim")->setConstant();


  cout << " Past the signal pdf3 "  <<endl; 
  RF->LoadWeights(weightsPath,"HSsWeights"); //Cp first to scratch or read from work? What is quicker? What is standard?
  RF->SetWeightName("Sig"); //Events in timing coincidence
 
  TString weightsPathPPi0Pim = fileDir + "/InvMassPPi0Pim/Weights" + job + ".root";

  pdfPPi0Pim->LoadWeights("Sig",weightsPathPPi0Pim,"HSsWeights"); //Cp first to scratch or read from work? What is quicker? What is standard?


  TString weightsPathNPipPi0 = fileDir + "/InvMassNPipPi0/Weights" + job + ".root";
  pdfNPipPi0->LoadWeights("Sig",weightsPathNPipPi0,"HSsWeights"); //Cp first to scratch or read from work? What is quicker? What is standard?


  cout << " Past the signal pdf4 "  <<endl; 
  gBenchmark->Start("Binned");
  RF->AddGausConstraint(pdf->AlphaConstraint());
  RF->AddGausConstraint(pdf->OffConstraint());
  RF->AddGausConstraint(pdf->ScaleConstraint());

  RF->AddGausConstraint(pdfNPipPi0->AlphaConstraint());
  RF->AddGausConstraint(pdfNPipPi0->OffConstraint());
  RF->AddGausConstraint(pdfNPipPi0->ScaleConstraint());

  RF->AddGausConstraint(pdfPPi0Pim->AlphaConstraint());
  RF->AddGausConstraint(pdfPPi0Pim->OffConstraint());
  RF->AddGausConstraint(pdfPPi0Pim->ScaleConstraint());


//  RF->FitSavedBins(2);
  RF->FitBatchBin(1,"Data");
  gBenchmark->Stop("Binned");
  gBenchmark->Print("Binned");

//  RF->GetWeights()->Save(); //Added Cam 4th Feb 2018, think this is now needed to be able to load weights later

}
