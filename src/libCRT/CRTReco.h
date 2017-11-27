#ifndef ROOT_CRTReco
#define ROOT_CRTReco

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// CRTReco                                                              //
//                                                                      //
//  Reconstruction classes for uBooNE/SBND CRT data                     //
// Igor Kreslo, LHEP Uni-Bern (Igor.Kreslo@cern.ch)                     //
//////////////////////////////////////////////////////////////////////////

#include "CRTEvent.h"
#include "TPCEvent.h"
#include "CRTRun.h"
#include "CRTBuffers.h"


//______________________________________________________________________________
class CRTReco : public TObject {

private:
public:

  TFile *ftpc;
  TTree *ttpc;
  CRTRun *crtrun;

  CRTReco();
  virtual ~CRTReco();

  Int_t ConvertDavidFlashTree(const char * fn1, const char *fno);
  Int_t ConvertChrisFlashTree(const char * fn1, const char *fno);
  Int_t MatchFlashestoCRT(const char * fncrt, const char *fntpc, const char *fno, Double_t dtns=100.0, Double_t offsetns=0.0);

  void Print(Int_t Verbosity=4);
  void Clear();
  void Dump(){Print(4);}
  ClassDef(CRTReco,1)  // CRT reconstructor object
};


#endif /* ROOT_CRTReco */



