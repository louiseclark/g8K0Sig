void GetSweightsPlotsSingle() {
	
	gStyle->SetOptStat(0);
		
	TString inFileName = "/home/louise/g8K0Sig/code/sWeights3/out_all_pi0K0_binned/Egamma1.23/costhK0CMS-0.05_Egamma1.23_/ResultsHSMinuit2.root";
	TFile* infile = TFile::Open(inFileName);
	TH1F* h = (TH1F*)infile->Get("costhK0CMS-0.05_Egamma1.23__M_pip_pim");
	
	//TCanvas* can = (TCanvas*)infile->Get("costhK0CMS-0.05_Egamma1.23__M_pip_pim");
	//TH1F* h = (TH1F*) can->GetListOfPrimitives()->First();
	
	h->Draw();
	gPad->Update();
	
	//TPaveText *st = (TPaveText*)gPad->GetPrimitive("costhK0CMS-0.05_Egamma1.23_TotalPDF_paramBox");
	TCanvas* c1 = (TCanvas*) gPad->GetListOfPrimitives()->First();
	TPaveText *st = (TPaveText*) c1->GetPrimitive("costhK0CMS-0.05_Egamma1.23_TotalPDF_paramBox");
	st->Delete();
	//st->SetX1NDC(0.5); //new x start position
	//st->SetX2NDC(0.5); //new x end position
	
	//h->SetStats(0);
	
	gPad->Modified();
	gPad->Update();
	gPad->Draw();
	
	TString outdir = "/home/louise/g8K0Sig/AnalysisSummary/html/images/sWeights/";

	TString outFilename = outdir+"test3"+".png";
	h->SaveAs(outFilename);	
	
}	

