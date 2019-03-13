

{
  //
  //MACRO to extract asymmetry from CLAS g8b data
  //Author: Craig Paterson
  //
  
  TCanvas *plot = new TCanvas("plot","plot",10,10,810,810);
  plot->Divide(1,3);
  gStyle->SetPalette(1);
  gStyle->SetFrameFillColor(19);
  gStyle->SetNumberContours(30);

  f = new TFile("SWanaSWPARA.root");
  g = new TFile("SWanaSWPERP.root");
 
  TH1F *Para_phi_hist=(TH1F*)f->Get("MpippimPhiCut1_All")->Clone("Para_phi_hist");
  Para_phi_hist->SetTitle("PARA");
  Para_phi_hist->GetXaxis()->SetTitle("KZero Phi");
  TH1F *Perp_phi_hist=(TH1F*)g->Get("MpippimPhiCut1_All")->Clone("Perp_phi_hist");
  Perp_phi_hist->SetTitle("PERP");
  Perp_phi_hist->GetXaxis()->SetTitle("KZero Phi");

  plot->cd(1);
  Para_phi_hist->Draw();
  plot->cd(2);
  Perp_phi_hist->Draw();

  //Sumw2 just makes sure the errors will be computed properly
  //when we form sums and ratios below.
  Para_phi_hist->Sumw2();
  Perp_phi_hist->Sumw2();

  //Get PARA/PERP yields and mean polarizations for each orientation
  float  NPerp=Perp_phi_hist->GetEntries();
  float  NPara=Para_phi_hist->GetEntries();
  float  PPerp=0.8;
  float  PPara=0.8;

  //Scale the histograms
  //Para_phi_hist->Scale(NPerp*PPerp);
  Para_phi_hist->Scale(NPerp);
  //Perp_phi_hist->Scale(NPara*PPara);
  Perp_phi_hist->Scale(NPara);
  Para_phi_hist->Rebin(2);
  Perp_phi_hist->Rebin(2);


  //Use utility to get asymmetry
  TH1F *Asymmetry=Para_phi_hist->GetAsymmetry(Perp_phi_hist);
  Asymmetry->SetTitle("Asymmetry");
  plot->cd(3);
  Asymmetry->Draw();


//   // Create Fit
//   TF1 *fitcos2phi = new TF1("fitcos2phi","[0] *(1+ [1]*cos(2*(x*TMath::DegToRad()) +[2]*TMath::DegToRad()))",0,360);
//   Asymmetry->Fit("fitcos2phi");

//   //Now calculate Asymmetry
//   float Asym=fitcos2phi->GetParameter(1)/((2*PPerp*PPara)/(PPerp+PPara));
//   cout<<"*************"<<endl;
//   cout<<"*************"<<endl;
//   cout<<"*************"<<endl<<endl;
//   cout<<"Photon Asymmetry = "<<Asym<<endl<<endl;
//   cout<<"*************"<<endl;
//   cout<<"*************"<<endl;
//   cout<<"*************"<<endl;
  
  

}
