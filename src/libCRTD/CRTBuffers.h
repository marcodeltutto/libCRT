#ifndef ROOT_CRTBuffers
#define ROOT_CRTBuffers

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// CRTBuffers                                                           //
//                                                                      //
// Buffer objects for uBooNE/SBND CRT data                              //
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

#define MAGICWORD8 0xa5 //marker for the buffer start in the file 
#define MAGICWORD16 0xaa55 //marker for the buffer start in the file 
#define MAGICWORD32 0xaa55aa55 //marker for the buffer start in the file 

#define NFEBS 200
#define EVLEN 80

class CRTRawhitBuffer;

//______________________________________________________________________________
class CRTRawhitBuffer : public TObject {

private:
public:
TClonesArray * hits; // Array of CRTRawhits
Int_t Nhits;
Int_t mac5;
  CRTRawhitBuffer();
  virtual ~CRTRawhitBuffer();
  void     Copy(CRTRawhitBuffer *h) { memcpy( (void*)this, (void*)h, sizeof(CRTRawhitBuffer) ); }
  void Print(Int_t Verbosity=4);
  void AddRawhit(CRTRawhit * hit);
  void Clear();
  ClassDef(CRTRawhitBuffer,1)  // CRT buffer for raw hits
};



#endif /* ROOT_CRTBuffers */



