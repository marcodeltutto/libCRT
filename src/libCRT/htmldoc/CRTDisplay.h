#ifndef ROOT_CRTDisplay
#define ROOT_CRTDisplay

#include "TObject.h"
#include "TGeoManager.h"
#include "TEveManager.h"
#include "TEveBoxSet.h"
#include "TEveCompound.h"
#include "TEveRGBAPalette.h"
#include "CRTEvent.h"
#include "CRTRun.h"
#include "CRTBuffers.h"
#include "TGeoNode.h"
#include "TEveGeoNode.h"
#include "TGLViewer.h"
#include "TEveStraightLineSet.h"
#include "TEventList.h"


//////////////////////////////////////////////////////////////////////////
//                                                                      //
// CRTDisplay                                                           //
//                                                                      //
// Class to display CRT events in 3D                                    //
//                                                                      //
//////////////////////////////////////////////////////////////////////////


//_________________________________________________________________________
class CRTDisplay: public TObject {

 private:
 TEveManager * teve;
 TEveFrameBox *fb;
 TEveRGBAPalette *pal;
 TGeoManager *geom;
 TEveGeoTopNode* en;
 TGeoNode* node;
 CRTCalibs * cal;
 Int_t Verb;
 CRTRun * run;
 Int_t curev;
 TEventList * elist;

 public:

 TEveBoxSet *qraw; //raw ADC single hits  

 TEveCompound *comp_h2d; //2d hit with children
 TEveBoxSet *h2d; //fitted 2D coord
 TEveBoxSet *h2d_raw; //raw ADCs crossing at fitted 2D coord

 TEveCompound *comp_trk; //tracks
 TEveStraightLineSet *lines; //track lines
 TEveBoxSet *trk_h2d; //2d hits of track
 TEveBoxSet *trk_h2d_raw; //raw ADC for 2d hits
 
  CRTDisplay();
  virtual ~CRTDisplay();
  TEveManager * GetEve(){return teve;};
  void AddRawhit(CRTRawhit * hit, Bool_t ShowAllADCs=0, Double_t X2D=0, Double_t Y2D=0, Double_t Z2D=0, Int_t Level=0 );
  void Add2Dhit(CRT2Dhit * hit, Bool_t ShowAllADCs=0, Int_t Level=0);
  void AddEvent(CRTEvent * evt, Bool_t ShowAllADCs=0, Int_t Level=0);
  void AddTrack(CRTTrack * evt, Bool_t ShowAllADCs=0, Int_t Level=0);
  void AddMarker(Double_t x,Double_t y,Double_t z,Double_t sx,Double_t sy,Double_t sz,Double_t ph);
  void SetCalibs(CRTCalibs * c){cal=c;};
  void SetRun(CRTRun * r){run=r; SetCalibs(r->rheader->cal);};
  void Clear();
  void Refresh();
  void SetVerb(Int_t v){Verb=v;};
  void SetCut(const char * scut);
  void ShowRunEvents(Int_t se, Int_t ee, Bool_t ShowAllADCs=0); //Display events from the attached run: from se to ee.

  
  ClassDef(CRTDisplay,1) //CRT Event Display
};


#endif /* ROOT_CRTDisplay */
