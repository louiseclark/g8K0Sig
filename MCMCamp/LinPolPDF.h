/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/

#ifndef LINPOLPDF
#define LINPOLPDF

#include "RooAbsPdf.h"
#include "RooHSEventsPDF.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
 
class LinPolPDF : public RooHSEventsPDF {
public:
  LinPolPDF() {} ; 
  LinPolPDF(const char *name, const char *title,
	      RooAbsReal& _phiK0,
	      RooAbsReal& _cosX,
	      RooAbsReal& _cosY,
	      RooAbsReal& _cosZ,
	      RooAbsReal& _pol,
	      RooAbsCategory& _polState,
	      RooAbsReal& _B,
	      RooAbsReal& _T,
	      RooAbsReal& _Ox,
	      RooAbsReal& _Oz,
	      RooAbsReal& _R);
  LinPolPDF(const LinPolPDF& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new LinPolPDF(*this,newname); }
  inline virtual ~LinPolPDF() { }

protected:

  RooRealProxy phiK0 ;
  RooRealProxy cosX ;
  RooRealProxy cosY ;
  RooRealProxy cosZ ;
  RooRealProxy pol ;
  RooCategoryProxy polState ;
  RooRealProxy B ;
  RooRealProxy T ;
  RooRealProxy Ox ;
  RooRealProxy Oz ;
  RooRealProxy R ;
  
  Double_t evaluate() const ;
  Double_t evaluateMC(const vector<Float_t> *vars,const  vector<Int_t> *cats) const ;
  void MakeSets();

private:

  ClassDef(LinPolPDF,1) // Your description goes here...
};
 
#endif
