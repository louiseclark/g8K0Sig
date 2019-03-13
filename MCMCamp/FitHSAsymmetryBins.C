//Run with 
//root --hsfit FitHSAsymmetryBins.C --LinPolPDF.cxx
{
  //Create THSRooFit manager 
  THSRooFit* RF=new THSRooFit("AFit");
  string outdir = "out5";
  RF->SetOutDir(outdir); //give output directory
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

  RooRealVar a1Re("a1Re","a1Re",0.0,-1.0,1.0); // @0
  RooRealVar a1Im("a1Im","a1Im",0.0,-1.0,1.0); // @1
  RooRealVar a2Re("a2Re","a2Re",0.0,-1.0,1.0); // @2
  RooRealVar a2Im("a2Im","a2Im",0.0,-1.0,1.0); // @3
  RooRealVar a3Re("a3Re","a3Re",0.0,-1.0,1.0); // @4
  RooRealVar a3Im("a3Im","a3Im",0.0,-1.0,1.0); // @5
  RooRealVar a4Re("a4Re","a4Re",0.0,-1.0,1.0); // @6
  RooRealVar a4Im("a4Im","a4Im",0.0,-1.0,1.0); // @7

  // magnitude of the 8 vars for scaling
  RooFormulaVar r("r","r","sqrt(@0*@0+@1*@1+@2*@2+@3*@3+@4*@4+@5*@5+@6*@6+@7*@7)",RooArgList(a1Re,a1Im,a2Re,a2Im,a3Re,a3Im,a4Re,a4Im));
  //RooRealVar r("r","r",1.0,0.9,1.1);

  //            B =          r1^2        + r2^2        - r3^2        - r4^2
  RooFormulaVar B("B","B","((@0*@0+@1*@1)+(@2*@2+@3*@3)-(@4*@4+@5*@5)-(@6*@6+@7*@7))/@8",RooArgList(a1Re,a1Im,a2Re,a2Im,a3Re,a3Im,a4Re,a4Im,r));

  //            T =          r1^2        - r2^2        - r3^2        + r4^2
  RooFormulaVar T("T","T","((@0*@0+@1*@1)-(@2*@2+@3*@3)-(@4*@4+@5*@5)+(@6*@6+@7*@7))/@8",RooArgList(a1Re,a1Im,a2Re,a2Im,a3Re,a3Im,a4Re,a4Im,r));
 
  //            Ox = 2 Re(a1 a4* + a2 a3*) = 2 * (a1Re*a4Re + a1Im*a4Im + a2Re*a3Re + a2Im*a3Im)
  RooFormulaVar Ox("Ox","Ox","(2.0*(@0*@6+@1*@7+@2*@4+@3*@5))/@8",RooArgList(a1Re,a1Im,a2Re,a2Im,a3Re,a3Im,a4Re,a4Im,r));

  //            Oz = 2 Im(a1 a4* - a2 a3*) = 2 * (a1Im*a4Re - a1Re*a4Im + a2Re*a3Im - a2Im*a3Re)
  RooFormulaVar Oz("Oz","Oz","(2.0*(@1*@6-@0*@7+@2*@5-@3*@4))/@8",RooArgList(a1Re,a1Im,a2Re,a2Im,a3Re,a3Im,a4Re,a4Im,r));
  
  //       (P=) R =         r1^2         - r2^2        + r3^2        - r4^2
  RooFormulaVar R("R","R","((@0*@0+@1*@1)-(@2*@2+@3*@3)+(@4*@4+@5*@5)-(@6*@6+@7*@7))/@8",RooArgList(a1Re,a1Im,a2Re,a2Im,a3Re,a3Im,a4Re,a4Im,r));
  
  RF->GetWorkSpace()->import(r, RecycleConflictNodes());
  RF->GetWorkSpace()->import(B, RecycleConflictNodes());
  RF->GetWorkSpace()->import(T, RecycleConflictNodes());
  RF->GetWorkSpace()->import(Ox, RecycleConflictNodes());
  RF->GetWorkSpace()->import(Oz, RecycleConflictNodes());
  RF->GetWorkSpace()->import(R, RecycleConflictNodes());
  // Default starting values 
  RF->Factory("LinPolPDF::LinPolFit(phiK0,cosX,cosY,cosZ,pol,polState,B,T,Ox,Oz,R)");
 
  // Set some parameters to constant
  //RF->GetWorkSpace()->var("Ox")->setConstant();
  //RF->GetWorkSpace()->var("Oy")->setConstant();
  //RF->GetWorkSpace()->var("T")->setConstant();
 
  RooHSEventsPDF* PDF=dynamic_cast<RooHSEventsPDF*>(RF->GetWorkSpace()->pdf("LinPolFit"));
  
  cout<<"PDF "<<PDF<<endl;
  RF->LoadSpeciesPDF("LinPolFit");
  RF->TotalPDF();  
  
  // load weights for the simulation (importance sampling to make simulation like data)
  //PDF->LoadWeights("LikeData","/home/louise/g8_phi/ImportanceSampling/impWeights.root","impWeights"); 

  // load weights for the data (signal weights)
  RF->LoadWeights("/home/louise/g8K0Sig/code/sWeights/out_all_pi0K0/Weights_all.root","HSsWeights");
  RF->SetWeightName("Signal");
 
  int fitMethod = 2; // MCMC=2, default=0
  
  RF->SetFitMethod(fitMethod);
  
  if (fitMethod==2) { 
	RF->SetNMCMC(1000000,100);
  
    //RF->SetProposal(1); // uniform
  
    RF->SetProposal(0); // step
    RF->SetStepMCMC(0.1);
  }
  
  //AddFitOption(RooFit::SumW2Error(kTRUE));

  RF->FitSavedBins(1,kFALSE);
  
  // output the observable results to a text file
  ofstream outfile;
  outfile.open(outdir+"/obs_values.txt");

  auto result=((THSRooFit*)RF->GetFits()->At(0))->GetResult();
  
  
  if (fitMethod==2) {
	  // don't attempt to get propagated error if MCMC
	  auto v=(RooFormulaVar*)((THSRooFit*)RF->GetFits()->At(0))->GetWorkSpace()->function("B");
	  outfile << "B = " << v->getVal() << endl;
	  cout << "B = " << v->getVal() << endl;

	  v=(RooFormulaVar*)((THSRooFit*)RF->GetFits()->At(0))->GetWorkSpace()->function("Ox");
	  outfile << "Ox = " << v->getVal() << endl;
	  cout << "Ox = " << v->getVal() << endl;
	  
	  v=(RooFormulaVar*)((THSRooFit*)RF->GetFits()->At(0))->GetWorkSpace()->function("Oz");
	  outfile << "Oz = " << v->getVal() << endl;
	  cout << "Oz = " << v->getVal() << endl;

	  v=(RooFormulaVar*)((THSRooFit*)RF->GetFits()->At(0))->GetWorkSpace()->function("R");
	  outfile << "R = " << v->getVal() << endl;
	  cout << "R = " << v->getVal() << endl;

	  v=(RooFormulaVar*)((THSRooFit*)RF->GetFits()->At(0))->GetWorkSpace()->function("T");
	  outfile << "T = " << v->getVal() << endl;
	  cout << "T = " << v->getVal() << endl;
  }
  else {
	  auto v=(RooFormulaVar*)((THSRooFit*)RF->GetFits()->At(0))->GetWorkSpace()->function("B");
	  outfile << "B = " << v->getVal() << " +/- " << v->getPropagatedError(*result) << endl;
	  cout << "B = " << v->getVal() << " +/- " << v->getPropagatedError(*result) << endl;

	  v=(RooFormulaVar*)((THSRooFit*)RF->GetFits()->At(0))->GetWorkSpace()->function("Ox");
	  outfile << "Ox = " << v->getVal() << " +/- " << v->getPropagatedError(*result) << endl;
	  cout << "Ox = " << v->getVal() << " +/- " << v->getPropagatedError(*result) << endl;
	  
	  v=(RooFormulaVar*)((THSRooFit*)RF->GetFits()->At(0))->GetWorkSpace()->function("Oz");
	  outfile << "Oz = " << v->getVal() << " +/- " << v->getPropagatedError(*result) << endl;
	  cout << "Oz = " << v->getVal() << " +/- " << v->getPropagatedError(*result) << endl;

	  v=(RooFormulaVar*)((THSRooFit*)RF->GetFits()->At(0))->GetWorkSpace()->function("R");
	  outfile << "R = " << v->getVal() << " +/- " << v->getPropagatedError(*result) << endl;
	  cout << "R = " << v->getVal() << " +/- " << v->getPropagatedError(*result) << endl;

	  v=(RooFormulaVar*)((THSRooFit*)RF->GetFits()->At(0))->GetWorkSpace()->function("T");
	  outfile << "T = " << v->getVal() << " +/- " << v->getPropagatedError(*result) << endl;
	  cout << "T = " << v->getVal() << " +/- " << v->getPropagatedError(*result) << endl;
	  
  }	 

  outfile.close();
  
}
