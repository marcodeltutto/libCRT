#ifndef ROOT_CRTRun
#define ROOT_CRTRun

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// CRTRun                                                           //
//                                                                      //
// Run container for uBooNE/SBND CRT data                              //
// Igor Kreslo, LHEP Uni-Bern (Igor.Kreslo@cern.ch)                     //
//////////////////////////////////////////////////////////////////////////

#include "TObject.h"
#include "TClonesArray.h"
#include "TObjArray.h"
#include "TFile.h"
#include "TTree.h"
#include "TTreeIndex.h"
#include "TPolyMarker3D.h"
#include "TArrayF.h"
#include "TArrayS.h"
#include "CRTEvent.h"
#include "CRTBuffers.h"


const Long64_t cstDefaultMaxTreeSize = 15000000000LL;


class CRTRun;
class CRTRunHeader;

//______________________________________________________________________________
class CRTRun : public TObject {

private:
public:
TFile *f;
TTree *t;
TClonesArray * hits; // Array of CRTRawhits
TClonesArray * h2d; //Array of CRT2Dhits 
TClonesArray * evs; //Array of CRTEvents
TClonesArray * trk; //Array of CRTTracks
Int_t NRawhits; //! transient: Number of raw hits in current entry
Int_t N2Dhits;  //! transient: Number of 2D hits in current entry
Int_t NEvents;  //! transient: Number of Events in current entry
Int_t NTracks;  //! transient: Number of passing through trcaks in current entry

CRTRunHeader * rheader; //Meta info
Long64_t * index; //! transient Tree index array, where entries are sorted by time
  CRTRun();
  virtual ~CRTRun();
void CreateNewDataRun(const char *fname); 
Int_t MergeSortedByTime( CRTRun * run1, CRTRun * run2);
Int_t ExtractPassingTracks( CRTRun * run1, Double_t time_window_ns=100.); //input file - run with CRT2D hits, fills CRTTracks
Int_t GroupAndClassify( CRTRun * run1, Double_t time_window_ns=100.); //input file - run with CRT2D hits, fills CRT2D, CRTRawhits, CRTTracks
 
Int_t OpenExistingDataRun(const char *fname, const char *Option="READ");
Bool_t IsWritable(); 
void SetCalibs(CRTCalibs * c);
void Close();
void AddRawhit(CRTRawhit * h);
void AddRawhitBuffer(CRTRawhitBuffer *b);
void Add2Dhit(CRT2Dhit * h);
void AddEvent(CRTEvent * e);
void AddTrack(CRTTrack * e);
void ClearEntry();
Int_t CleanDuplicateRawHits();
void PrintSummary();
void CopyEntryFromRun(CRTRun * run, Long64_t entry);
void Fill(); 
void BuildIndex(const char *major,const char *minor); 
Int_t GetEntry(Int_t en){return t->GetEntry(en);};
Int_t GetEntrySortedByTime(Int_t en);
  ClassDef(CRTRun,1)  // CRT run
};

//______________________________________________________________________________
class CRTRunHeader : public TObject {

private:
public:
CRTCalibs * cal; //CRT calibration object
Int_t N; //Number of entries in the tree
Int_t NRawhits; //Number of raw hits in run
Int_t N2Dhits; //Number of 2D hits in run
Int_t NEvents; //Number of Events in run
Int_t NTracks; //Number of passing through tracks run
Int_t Nt0refs[NFEBS]; //Number of T0REF events per FEB
Int_t Nt1refs[NFEBS]; //Number of T1REF events per FEB

Int_t startSecondsUTC;
Int_t endSecondsUTC;
  CRTRunHeader();
  virtual ~CRTRunHeader();
void SetCalibs(CRTCalibs * c){cal=c;}
void     Copy(CRTRunHeader *h) { memcpy( (void*)this, (void*)h, sizeof(CRTRunHeader) ); }

ClassDef(CRTRunHeader,1)  // CRT run header
};



#endif /* ROOT_CRTRun */



