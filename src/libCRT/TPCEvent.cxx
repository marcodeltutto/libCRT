//-- Author :  Igor Kreslo, 2017

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TPCEvent                                                              //
//                                                                      //
// Reconstruction classes for uBooNE/SBND CRT data                      //
// Igor Kreslo, LHEP Uni-Bern (Igor.Kreslo@cern.ch)                     //
//////////////////////////////////////////////////////////////////////////

#include "TPCEvent.h"



ClassImp(PMTFlash)
ClassImp(TPCEvent)


//______________________________________________________________________________
TPCEvent::TPCEvent()
{
  flar=new TClonesArray("PMTFlash",10);
  tr=new CRTTrack();
  event=0;
  IsBNB=kFALSE;
  trig_t0=0;
  s=0;
  Nflashes=0;
}

//______________________________________________________________________________
void TPCEvent::Print(Int_t Verbosity) 
{
  for(int i=0; i<Nflashes; i++)
  ((PMTFlash*)(flar->At(i)))->Print(Verbosity);
  printf("%d flashes in Event triggered at %d s, %d ns.\n",Nflashes,s,trig_t0);
}


//______________________________________________________________________________
TPCEvent::~TPCEvent()
{
  if(flar) {flar->Delete(); delete flar, flar=0;}
}

//______________________________________________________________________________
void TPCEvent::Clear()
{
  flar->Clear();
  event=0;
  IsBNB=kFALSE;
  trig_t0=0;
  s=0;
  Nflashes=0;
}


//______________________________________________________________________________
void TPCEvent::AddFlash(PMTFlash * fl)
{
  PMTFlash* ht;
  ht=(PMTFlash*)(new((*flar)[flar->GetLast()+1])  PMTFlash());
  ht->Copy(fl);
  Nflashes++;
}


//______________________________________________________________________________
PMTFlash::PMTFlash()
{
t0=0; // t0 (UTC nanoseconds) ,ns (Abs_T_flash)
t1=0; // t1 (time w.r.t. Beam Trigger T1),ns (T_flash) 
s=0; //Timestamp: Second (linux seconds)
npe=0; //summed number of photoelectrons
x=0;
y=0;
z=0; //reconstructed flash coordinates
  IsBNB=0;
}


//______________________________________________________________________________
PMTFlash::PMTFlash(Double_t at0, Double_t at1, Int_t as, Double_t anpe, Double_t ax, Double_t ay, Double_t az)
{
t0=at0; // t0 (UTC nanoseconds) ,ns (Abs_T_flash)
t1=at1; // t1 (time w.r.t. Beam Trigger T1),ns (T_flash) 
s=as; //Timestamp: Second (linux seconds)
npe=anpe; //summed number of photoelectrons
x=ax;
y=ay;
z=az; //reconstructed flash coordinates
}


//______________________________________________________________________________
void PMTFlash::Print(Int_t Verbosity) 
{
  printf("TPC event %d : %lf P.E. at (%lf,%lf,%lf), t1=%lf, s=%d. Absolute %lf ns.\n",event,npe, x,y,z, t1, s, t0);
}


//______________________________________________________________________________
PMTFlash::~PMTFlash()
{
}

//______________________________________________________________________________
void PMTFlash::Clear()
{
t0=0; // t0 (UTC nanoseconds) ,ns (Abs_T_flash)
t1=0; // t1 (time w.r.t. Beam Trigger T1),ns (T_flash) 
s=0; //Timestamp: Second (linux seconds)
npe=0; //summed number of photoelectrons
x=0;
y=0;
z=0; //reconstructed flash coordinates
  IsBNB=0;
event=0;
}

