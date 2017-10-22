#ifndef ROOT_TPCEvent
#define ROOT_TPCEvent

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TPCEvent                                                             //
//                                                                      //
//  Reconstruction classes for uBooNE/SBND CRT data                     //
// Igor Kreslo, LHEP Uni-Bern (Igor.Kreslo@cern.ch)                     //
//////////////////////////////////////////////////////////////////////////
#include "TObject.h"
#include "TClonesArray.h"
#include "TObjArray.h"
#include "TList.h"
#include "TPolyMarker3D.h"
#include "TArrayF.h"
#include "TArrayS.h"
#include "CRTEvent.h"


class PMTFlash;
class TPCEvent;

//______________________________________________________________________________
class PMTFlash : public TObject {

private:
public:
Double_t t0; // t0 (UTC nanoseconds) ,ns (Abs_T_flash)
Double_t t1; // t1 (time w.r.t. Beam Trigger T1),ns (T_flash) 
Int_t s; //Timestamp: Second (linux seconds)
Double_t npe; //summed number of photoelectrons
Double_t x,y,z; //reconstructed flash coordinates
Int_t IsBNB; // flag, marking event, triggered by BNB BES

  PMTFlash();
  PMTFlash(Double_t at0, Double_t at1, Int_t as, Double_t anpe, Double_t ax, Double_t ay, Double_t az);
  virtual ~PMTFlash();
  void     Copy(PMTFlash *h) { memcpy( (void*)this, (void*)h, sizeof(PMTFlash) ); }
  void Print(Int_t Verbosity=4);
  void Clear();
  void Dump(){Print(4);}
  ClassDef(PMTFlash,1)  // PMT flash
};


//______________________________________________________________________________
class TPCEvent : public TObject {

private:

public:
Int_t event; //TPC event number
Int_t IsBNB; // flag, marking event, triggered by BNB BES
TClonesArray * flar; // Array of PMTFlashes
CRTTrack * tr; // reconstructed TPC track (muon)
Int_t trig_t0; // Trigger UTC nanoseconds (supposed to be GPS time, but not clear!)
Int_t    s; //Trigger Timestamp: Second (linux seconds)
Int_t Nflashes;
  TPCEvent();
  virtual ~TPCEvent();
  void     Copy(TPCEvent *h) { memcpy( (void*)this, (void*)h, sizeof(TPCEvent) ); }
  void Print(Int_t Verbosity=4);
  void AddFlash(PMTFlash * fl);
  void Clear();
  void Dump(){Print(4);}
  ClassDef(TPCEvent,1)  // TPC combined event: flashes and reconstructed track (optional)
};




#endif /* ROOT_TPCEvent */



