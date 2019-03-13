//--Author      DI Glazier 30/06/2014
//--Rev
//--Update
//--Description
//HASPECT Event Reconstruction
//THSHisto
//Facilitates histogram declaration and filling
//Users must implement :
//HistogramList to declare which types of histogram they need
//FillHistogram to fill the histogram with datamembers of their selector class
//If the histogram fHisbins is defined it will be used to split
//the histograms into different (kinematic) bins

#ifndef THSHisto_h
#define THSHisto_h

#include <TSelector.h>
#include <TH2.h>
#include <TKey.h>
#include <TString.h>
#include <TFile.h>
#include <iostream>
#include <map>

using namespace std;

typedef map< TString , TH1* > StrTH1_Map;  //make a type connecting strings to TH1
typedef vector< StrTH1_Map > Vec_StrTH1; //make a type which is a vector of StrTH1_Maps

class THSHisto {
 public :
  
 THSHisto(TTree * /*tree*/ =0) : fHisbins(0) { }
  virtual ~THSHisto() {}
  
  ///Additional for histogramming
  //Here we can divide the data into 3 dimensions of kinematic bin
  //by using up to TH3
  TH1* fHisbins; //histogram defining the kinematics bins
  TString GetStrBin(Float_t ev1, Float_t ev2);
  Int_t GetKinBin(Float_t ev1,Float_t ev2=0,Float_t ev3=0);
  virtual void LoadCut(TString sCut);
  virtual void LoadHistograms();
  virtual void ChangeNames(/*TFile* list*/);
  virtual TH1* MapHist(TH1* hist);
  virtual TH1* FindHist(TString hname);

  //Users will need to declare and define the following functions
  virtual void HistogramList(TString ){};// =0; 
  virtual void FillHistograms(TString ,Int_t ){};// =0;
  
 protected:
  StrTH1_Map fHistNameMap; //connect hist names to TH1* objects
  Vec_StrTH1 fVecHistCut; //a vector with elements for each cut
  vector< Vec_StrTH1 > fVecHistBin; //a vector with elements for each bin
  
  TString fCurrCut; //For passing cut names between funcions
  Int_t fCurrBin; //for passing bin number
  vector< TString > fVecCuts; // list of defined cuts
  vector< TString > fVecBinNames; // list of histogram bin names
  map< TString, Int_t > fMapCuts; // map of defined cuts to fVecHistCut element
  map< TString,TString > fBinMap; //bin (kinmematic) name to number map
   
};


#endif 
