//-- Author :  Igor Kreslo, 2017

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// CRTBuffers                                                           //
//                                                                      //
// Buffer objects for uBooNE/SBND CRT data                              //
// Igor Kreslo, LHEP Uni-Bern (Igor.Kreslo@cern.ch)                     //
//////////////////////////////////////////////////////////////////////////
#define INCH 2.54


#include <iostream>
#include <fstream>
#include <stdio.h>

#include <TSystem.h>
#include <TObject.h>
#include <TClass.h>
#include <TRandom.h>
#include <TMath.h>
#include <TH3.h>
#include <TPolyLine3D.h>

#include "CRTBuffers.h"



ClassImp(CRTRawhitBuffer)


//______________________________________________________________________________
CRTRawhitBuffer::CRTRawhitBuffer():TObject()
{
  hits=new TClonesArray("CRTRawhit",1000);
  Nhits=0;
  mac5=0;
  hits->SetOwner(kTRUE);
}

//______________________________________________________________________________
void CRTRawhitBuffer::Print(Int_t Verbosity)
{
  for(int i=0; i<Nhits; i++)
  ((CRTRawhit*)(hits->At(i)))->Print(Verbosity);
  if(mac5>0) printf("mac5=%d, ",mac5);
  else if (mac5<0) printf("Multiple mac5's, ");
  printf("%d hits in the buffer.\n",Nhits);
   
}


//______________________________________________________________________________
CRTRawhitBuffer::~CRTRawhitBuffer()
{
  if(hits) {hits->Delete(); delete hits, hits=0;}
}
//______________________________________________________________________________
void CRTRawhitBuffer::Clear()
{
  hits->Clear();
  Nhits=0;
  mac5=0;
}


//______________________________________________________________________________
void CRTRawhitBuffer::AddRawhit(CRTRawhit * hit)
{
  CRTRawhit * ht;
  ht=(CRTRawhit*)(hits->ConstructedAt(Nhits));
  ht->Copy(hit);
  Nhits++;
  if(mac5==0) mac5=hit->mac5;
  else if(mac5!=hit->mac5) mac5=-1; //if mixed FEBS, set to -1
}




