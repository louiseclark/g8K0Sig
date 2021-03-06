/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/

#ifndef OBSFIT
#define OBSFIT

#include "RooAbsPdf.h"
#include "RooHSEventsPDF.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
 
class ObsFit : public HS::FIT::RooHSEventsPDF {
public:
  ObsFit() {} ; 
  ObsFit(const char *name, const char *title,
	      RooAbsReal& _phiK0,
	      RooAbsReal& _pol,
	      RooAbsCategory& _polState,
	      RooAbsReal& _B);
  ObsFit(const ObsFit& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new ObsFit(*this,newname); }
  inline virtual ~ObsFit() { }

protected:

  RooRealProxy phiK0 ;
  RooRealProxy pol ;
  RooCategoryProxy polState ;
  RooRealProxy B ;
  
  Double_t evaluate() const ;
  Double_t evaluateMC(const vector<Float_t> *vars,const  vector<Int_t> *cats) const ;
  void MakeSets();

private:

  ClassDef(ObsFit,1) // Your description goes here...
};
 
#endif
