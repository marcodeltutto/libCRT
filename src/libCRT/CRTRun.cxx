//-- Author :  Igor Kreslo, 2017

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// CRTRun                                                           //
//                                                                      //
// Run container for uBooNE/SBND CRT data                              //
// Igor Kreslo, LHEP Uni-Bern (Igor.Kreslo@cern.ch)                     //
//////////////////////////////////////////////////////////////////////////

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

#include "CRTRun.h"



ClassImp(CRTRunHeader)
ClassImp(CRTRun)


//______________________________________________________________________________
CRTRunHeader::CRTRunHeader():TObject()
{
cal=0;
N=0; //Number of entries in the tree
NRawhits=0; //Number of raw hits in the run
N2Dhits=0; //Number of 2D hits in the run
NEvents=0; //Number of Events in the run
NTracks=0; //Number of Tracks in the run
NFlashes=0; //Number of TPC PMT flashes in the run
startSecondsUTC=0;
endSecondsUTC=0;
for(int i=0;i<NFEBS; i++) {Nt0refs[i]=0;Nt1refs[i]=0;}
}



//______________________________________________________________________________
CRTRunHeader::~CRTRunHeader()
{
  if(cal) {cal->Delete(); delete cal, cal=0;}
}


//______________________________________________________________________________
CRTRun::CRTRun():TObject()
{
t=0;
f=0;
hits=new TClonesArray("CRTRawhit",2000);// Array of CRTRawhits
h2d=new TClonesArray("CRT2Dhit",1000);; //Array of CRT2Dhits 
evs=new TClonesArray("CRTEvent",10);; //Array of CRTEvents
trk=new TClonesArray("CRTTrack",1000);; //Array of CRTTracks
fl=new TClonesArray("PMTFlash",1000);; //Array of TPC PMT flashes
//tpc_ev=new TPCEvent(); 
rheader= new CRTRunHeader(); //Meta info and calibrations
NRawhits=0; //! transient: Number of raw hits in current entry
N2Dhits=0;  //! transient: Number of 2D hits in current entry
NEvents=0;  //! transient: Number of Events in current entry
NTracks=0;  //! transient: Number of passing through trcaks in current entry
NFlashes=0;  //! transient: Number of passing through trcaks in current entry
}



//______________________________________________________________________________
CRTRun::~CRTRun()
{
    if(f) {delete f, f=0;}
    if(hits) {hits->Delete(); delete hits, hits=0;}
    if(h2d) {h2d->Delete(); delete h2d, h2d=0;}
    if(evs) {evs->Delete(); delete evs, evs=0;}
    if(trk) {trk->Delete(); delete trk, trk=0;}
    if(fl) {fl->Delete(); delete fl, fl=0;}
  //  if(tpc_ev) {tpc_ev->Delete(); delete tpc_ev, tpc_ev=0;}

}

//______________________________________________________________________________
void CRTRun::Fill() 
{ 
   if(t) {t->Fill();(rheader->N)++;}
}

//______________________________________________________________________________
void CRTRun::BuildIndex(const char *major,const char *minor)
{
  t->BuildIndex(major, minor);
  if(t->GetTreeIndex()) index=((TTreeIndex*)t->GetTreeIndex())->GetIndex();
  else index=0;
} 



//______________________________________________________________________________
void CRTRun::PrintSummary()
{
 Int_t maxt1s=0;
 Int_t maxt0s=0;
 Int_t mint1s=0;
 Int_t mint0s=0;
 printf("***********************************************************************\n");
 printf("CRTRun: from %d sec to %d sec, duration %d sec\n", rheader->startSecondsUTC, rheader->endSecondsUTC, rheader->endSecondsUTC-rheader->startSecondsUTC);
 printf("%d tree entries\n", rheader->N);
 printf("%d raw hits\n", rheader->NRawhits);
 printf("%d 2D hits\n", rheader->N2Dhits);
 printf("%d CRT multihit events\n", rheader->NEvents);
 printf("%d CRT passing through tracks\n", rheader->NTracks);
 printf("%d PMT flashes\n", rheader->NFlashes);
 if(rheader->cal) printf("Calibration object V%d present.\n", rheader->cal->GetVersion());
 else  printf("Calibration object is not found.\n");
 if(index) printf("Tree is indexed, GetEntrySortedByTime(Int_t en) to access events in -sorted- order.\n");
 else printf("Tree is not indexed, use GetEntry(Int_t en) to acess -unsorted- entries\n");
  for(int i=0;i<NFEBS; i++) 
    {
    if(rheader->Nt0refs[i] >0 )
      {
        if(rheader->Nt0refs[i] > maxt0s) maxt0s=rheader->Nt0refs[i];
        if(mint0s==0 && rheader->Nt0refs[i] >0) mint0s=rheader->Nt0refs[i];
        if(rheader->Nt0refs[i] < mint0s && rheader->Nt0refs[i] >0) mint0s=rheader->Nt0refs[i];       
      }
    if(rheader->Nt1refs[i] >0 )
      {
        if(rheader->Nt1refs[i] > maxt1s) maxt1s=rheader->Nt1refs[i];
        if(mint1s==0 && rheader->Nt1refs[i] >0) mint1s=rheader->Nt1refs[i];
        if(rheader->Nt1refs[i] < mint1s && rheader->Nt1refs[i] >0) mint1s=rheader->Nt1refs[i];       
      }
    }
    printf("Number of T0 REF signals per FEB ranges from %d to %d\n", mint0s, maxt0s);
    printf("Number of T1 REF signals per FEB ranges from %d to %d\n", mint1s, maxt1s);
 printf("***********************************************************************\n");

}



//______________________________________________________________________________
void CRTRun::CreateNewDataRun(const char *fname)
{
  f=new TFile(fname,"RECREATE");
  f->SetCompressionLevel(2);
  t=new TTree("t","CRT events and hits tree");
  t->SetAutoSave(100000000);                     // autosave each 100Mb
  t->SetMaxTreeSize(cstDefaultMaxTreeSize);              //set 15 Gb file size limit
  if(hits) t->Branch("h", &hits); 
  if(h2d) t->Branch("h2d", &h2d); 
  if(evs) t->Branch("e", &evs); 
  if(trk) t->Branch("t", &trk);
  if(fl) t->Branch("fl", &fl);
          t->Branch("NRawhits",&NRawhits,"NRawhits/I"); 
          t->Branch("N2Dhits",&N2Dhits,"N2Dhits/I"); 
          t->Branch("NEvents",&NEvents,"NEvents/I"); 
          t->Branch("NTracks",&NTracks,"NTracks/I"); 
          t->Branch("NFlashes",&NFlashes,"NFlashes/I"); 
rheader->N=0;
rheader->NRawhits=0; //Number of raw hits in current entry
rheader->N2Dhits=0; //Number of 2D hits in current entry
rheader->NEvents=0; //Number of Events in current entry
rheader->NTracks=0; //Number of Tracks in current entry
rheader->NFlashes=0; //Number of Flashes in current entry
rheader->startSecondsUTC=0;
rheader->endSecondsUTC=0;
index=0;
for(int i=0;i<NFEBS; i++) {rheader->Nt0refs[i]=0;rheader->Nt1refs[i]=0;}
NRawhits=0; //! transient: Number of raw hits in current entry
N2Dhits=0;  //! transient: Number of 2D hits in current entry
NEvents=0;  //! transient: Number of Events in current entry
NTracks=0;  //! transient: Number of passing through trcaks in current entry
NFlashes=0; //! transient:
}

//______________________________________________________________________________
Int_t CRTRun::OpenExistingDataRun(const char *fname, const char *Option)
{
  f=new TFile(fname,Option);
  if(!f) return 0;
  t=(TTree*)(f->Get("t"));
  if(!t) return 0;
  if(hits) t->SetBranchAddress("h", &hits); 
  if(h2d) t->SetBranchAddress("h2d", &h2d); 
  if(evs) t->SetBranchAddress("e", &evs);
  if(trk) t->SetBranchAddress("t", &trk);
  if(fl) t->SetBranchAddress("fl", &fl);
 //if(tpc_ev) t->SetBranchAddress("tpc_ev", &tpc_ev);
  // rheader=(CRTRunHeader*)(f->Get("Header")); 
  rheader->Copy((CRTRunHeader*)(f->Get("Header")));
  if(t->GetTreeIndex()) index=((TTreeIndex*)t->GetTreeIndex())->GetIndex();
  else index=0;
  PrintSummary();
  return t->GetEntries(); 
}

//______________________________________________________________________________
Bool_t CRTRun::IsWritable()
{
  f = t->GetCurrentFile();
  const char *status = f->GetOption();	
  return strcmp(status,"READ");     
} 

//______________________________________________________________________________
void CRTRun::CopyEntryFromRun(CRTRun * run, Long64_t entry)
{
  if(!run) return;
      run->GetEntry(entry); 
      *(hits)=*(run->hits);
      *(h2d)=*(run->h2d);
      *(evs)=*(run->evs);
      *(trk)=*(run->trk);
      *(fl)=*(run->fl);
  //    *(tpc_ev)=*(run->tpc_ev);
NRawhits=run->NRawhits; //! transient: Number of raw hits in current entry
N2Dhits=run->N2Dhits;  //! transient: Number of 2D hits in current entry
NEvents=run->NEvents;  //! transient: Number of Events in current entry
NTracks=run->NTracks;  //! transient: Number of passing through trcaks in current entry
NFlashes=run->NFlashes;  //! transient: Number of PMT flashes

}

//______________________________________________________________________________
Int_t CRTRun::ExtractPassingTracks( CRTRun * run1, Double_t time_window_ns)
{
  CRTTrack tr;
  CRT2Dhit h1;
  CRT2Dhit h2;
  Double_t deltat0=0;
  Bool_t first=1;
  Int_t pairs=0;
    Long64_t * ind1; 
 // Long64_t * s1; 
  Long64_t * ns1; 
  Int_t en1=0;
  Int_t ens1; //Number of entries for input runs
  //sanity checks
  if(run1==this) {printf("Can't extract tracks from Run to itself!\n"); return 0;}
  if(!IsWritable()) {printf("Run is opened in Read Only mode! Can't proceed.\n"); return 0;}
  if(!run1->index) {printf("Input Run is not sorted! Can't proceed.\n"); return 0;}
  ens1=run1->t->GetEntries();   
  printf("Extracting passing tracks from run1 (%d entries) ..\n",ens1);
  run1->t->LoadBaskets();
  ind1=run1->index;
  //s1=((TTreeIndex*)(run1->t->GetTreeIndex()))->GetIndexValues();
  ns1=((TTreeIndex*)(run1->t->GetTreeIndex()))->GetIndexValuesMinor();
  while(en1<ens1-2)
  {
    deltat0=ns1[en1+1]-ns1[en1];
    if(abs(deltat0)<time_window_ns)
    {
    //  printf("%d-%d, deltat0=%lf\n",en1+1,en1,deltat0);
      run1->GetEntry(ind1[en1]);
      h1.Copy((CRT2Dhit*)(run1->h2d->At(0)));
      run1->GetEntry(ind1[en1+1]);
      h2.Copy((CRT2Dhit*)(run1->h2d->At(0)));
      if(first) first=0;//first event in a group 
      tr.SetHits(&h1,&h2);
     // tr.hit2d[0].Copy(&h1); 
     // tr.hit2d[1].Copy(&h2);
     // tr.tof=h2.t0-h1.t0;    
    //  printf("tof=%lf\n",tr.tof);
      if(tr.hit2d[0].plane1!=tr.hit2d[1].plane1) { AddTrack(&tr);  pairs++;}
      first=0;
    }
    else { if(pairs>0) {Fill(); ClearEntry(); pairs=0;} first=1; }//reset first flag 
    en1++;
  }
  rheader->cal=run1->rheader->cal; //set pointer to calibration object from run1
  index=0;
  rheader->startSecondsUTC=run1->rheader->startSecondsUTC;
  rheader->endSecondsUTC=run1->rheader->endSecondsUTC;

  for(int i=0;i<NFEBS; i++) 
    {
    rheader->Nt0refs[i]=run1->rheader->Nt0refs[i];
    rheader->Nt1refs[i]=run1->rheader->Nt1refs[i];
    }

  return rheader->N;
}


//______________________________________________________________________________
void CRTRun::ClearEntry() {
  hits->Clear(); 
  h2d->Clear();
   
  //for(int i=0;i<evs->GetEntries(); i++) ((CRTEvent*)(evs->At(i))->hits->Clear();
  evs->Clear(); 
  trk->Clear();
  fl->Clear();
 // tpc_ev->Clear();
NRawhits=0; //! transient: Number of raw hits in current entry
N2Dhits=0;  //! transient: Number of 2D hits in current entry
NEvents=0;  //! transient: Number of Events in current entry
NTracks=0;  //! transient: Number of passing through trcaks in current entry
NFlashes=0;  //! transient: Number of PMT flashes

}


//______________________________________________________________________________
Int_t CRTRun::CleanDuplicateRawHits()
{
  Int_t removed=0;

  CRTRawhit * ht1;
  CRTRawhit * ht2;
  for(Int_t i=0; i < hits->GetEntriesFast()-1; i++) for(Int_t j=i+1; j < hits->GetEntriesFast(); j++)
  {
   ht1=(CRTRawhit *)hits->At(i);
   ht2=(CRTRawhit *)hits->At(j);
   if(ht1==0 || ht2==0) continue;
   if(ht1->mac5==ht2->mac5 && ht1->s==ht2->s && abs(ht1->ts0 - ht2->ts0)<1e3 ) {hits->RemoveAt(j); removed ++; rheader->NRawhits--;}
  }
  hits->Compress();
  NRawhits=hits->GetEntries();
  //if(removed>0) printf("Cleaned %d duplicates\n",removed);
  return removed;
}


//______________________________________________________________________________
Int_t CRTRun::GroupAndClassify( CRTRun * run1, Double_t time_window_ns)
{
  CRTTrack tr;
 // CRTEvent ev;
  CRT2Dhit h1;
  CRT2Dhit h2;
  Double_t deltat0=0;
//  Bool_t first=1;
//  Int_t pairs=0;
    Long64_t * ind1; 
 // Long64_t * s1; 
  Long64_t * ns1; 
  Long64_t en1=0;
  Long64_t ens1; //Number of entries for input runs
  //sanity checks
  if(run1==this) {printf("Can't extract tracks from Run to itself!\n"); return 0;}
  if(!IsWritable()) {printf("Run is opened in Read Only mode! Can't proceed.\n"); return 0;}
  if(!run1->index) {printf("Input Run is not sorted! Can't proceed.\n"); return 0;}
  ens1=run1->t->GetEntries();   
  printf("Extracting raw hits from run1 (%lld entries) into events  ..\n",ens1);
  run1->t->LoadBaskets();
  ind1=run1->index;
  //s1=((TTreeIndex*)(run1->t->GetTreeIndex()))->GetIndexValues();
  ns1=((TTreeIndex*)(run1->t->GetTreeIndex()))->GetIndexValuesMinor();
 
  run1->GetEntry(ind1[0]); //save very first 2d hit
  h1.Copy((CRT2Dhit*)(run1->h2d->At(0)));  
  AddRawhit(&(h1.rhit[0]));
  AddRawhit(&(h1.rhit[1]));
  Add2Dhit(&h1);
  
  for(en1=1;en1<ens1;en1++)
  {
    if(en1%10000==1) printf("Processing 2d hit #%lld..\n",en1);
    deltat0=ns1[en1]-ns1[en1-1];
    if(abs(deltat0)>time_window_ns) 
      {
       CleanDuplicateRawHits(); Fill(); ClearEntry();
      }
    run1->GetEntry(ind1[en1]); //save next hit
    h2.Copy((CRT2Dhit*)(run1->h2d->At(0)));  
    AddRawhit(&(h2.rhit[0]));
    AddRawhit(&(h2.rhit[1]));	
    Add2Dhit(&h2);
    tr.SetHits(&h1,&h2);
    if(N2Dhits>=2 && tr.hit2d[0].plane1!=tr.hit2d[1].plane1) AddTrack(&tr);
    h1.Copy(&h2);
  }
  CleanDuplicateRawHits(); Fill(); ClearEntry();
  

//      tr.SetHits(&h1,&h2);
//      if(tr.hit2d[0].plane1!=tr.hit2d[1].plane1) { AddTrack(&tr);  pairs++;}



 /* 
   while(en1<ens1-2)
  {
    deltat0=ns1[en1+1]-ns1[en1];
    if(abs(deltat0)<time_window_ns)
    {
    //  printf("%d-%d, deltat0=%lf\n",en1+1,en1,deltat0);
      run1->GetEntry(ind1[en1]);
      h1.Copy((CRT2Dhit*)(run1->h2d->At(0)));
      run1->GetEntry(ind1[en1+1]);
      h2.Copy((CRT2Dhit*)(run1->h2d->At(0)));
      if(first) first=0;//first event in a group 

      AddRawhit(&(h1.rhit[0]));
      AddRawhit(&(h1.rhit[1]));
      AddRawhit(&(h2.rhit[0]));
      AddRawhit(&(h2.rhit[1]));
      pairs++;
      first=0;
    }
 //   else { if(pairs>0) { AddEvent(&ev); Fill(); ClearEntry(); pairs=0;} first=1; }//reset first flag 
    else { if(pairs>0) { CleanDuplicateRawHits(); Fill(); ClearEntry(); pairs=0;} first=1; }//reset first flag 
    if(en1%1000==0) {printf("en1=%d\n",en1);}
    en1++;
  }
*/
  rheader->cal=run1->rheader->cal; //set pointer to calibration object from run1
  index=0;
  rheader->startSecondsUTC=run1->rheader->startSecondsUTC;
  rheader->endSecondsUTC=run1->rheader->endSecondsUTC;

  for(int i=0;i<NFEBS; i++) 
    {
    rheader->Nt0refs[i]=run1->rheader->Nt0refs[i];
    rheader->Nt1refs[i]=run1->rheader->Nt1refs[i];
    }

  return rheader->N;
}
 
//______________________________________________________________________________
Int_t CRTRun::AppendSortedByTime( CRTRun * run1)
{
  Long64_t * s1; 
  Long64_t * ns1; 
  Long64_t * ind1; 
  Int_t en1=0;
  Int_t ens1; //Number of entries for input run
  //sanity checks
   if(run1==this) {printf("Can't merge CRTRun with itself!\n"); return 0;}
  if(!IsWritable()) {printf("Run is opened in Read Only mode! Can't proceed.\n"); return 0;}
  if(!run1->index) {printf("Run is not sorted! Can't proceed.\n"); return 0;}
  //set pointer to the end
  GetEntry(t->GetEntries()-1);
  ens1=run1->t->GetEntries();   
  printf("Appending run with %d entries ..\n",ens1);
  run1->t->LoadBaskets();
  ind1=run1->index;
  s1=((TTreeIndex*)(run1->t->GetTreeIndex()))->GetIndexValues();
  ns1=((TTreeIndex*)(run1->t->GetTreeIndex()))->GetIndexValuesMinor();
  while (en1<ens1)
      {
      CopyEntryFromRun(run1,ind1[en1]);
      en1++;
      if(en1%1000==1)  printf("run1 en1=%d ind1=%lld s=%lld ns=%lld\n",en1, ind1[en1],s1[en1],ns1[en1]); 
      if(s1[en1]>0) Fill();
      }

  rheader->N = rheader->N + run1->rheader->N;
  rheader->NRawhits = rheader->NRawhits + run1->rheader->NRawhits; //Number of raw hits in current entry
  rheader->N2Dhits = rheader->N2Dhits + run1->rheader->N2Dhits; //Number of 2D hits in current entry
  rheader->NEvents = rheader->NEvents + run1->rheader->NEvents; //Number of Events in current entry
  rheader->NTracks = rheader->NTracks + run1->rheader->NTracks; //Number of Tracks in current entry
  rheader->NFlashes = rheader->NFlashes + run1->rheader->NFlashes; //Number of Tracks in current entry
 // rheader->cal=run1->rheader->cal; //set pointer to calibration object from run1
  index=0;
   rheader->endSecondsUTC=run1->rheader->endSecondsUTC;
   if(rheader->startSecondsUTC<1e6) rheader->startSecondsUTC=run1->rheader->startSecondsUTC;
  for(int i=0;i<NFEBS; i++) 
    {
    rheader->Nt0refs[i]=rheader->Nt0refs[i]+run1->rheader->Nt0refs[i];
    rheader->Nt1refs[i]=rheader->Nt1refs[i]+run1->rheader->Nt1refs[i];
    }

  return rheader->N;
}

//______________________________________________________________________________
Int_t CRTRun::MergeSortedByTime( CRTRun * run1, CRTRun * run2)
{
  
  Long64_t * ind1; 
  Long64_t * ind2; 
  Long64_t * s1; 
  Long64_t * s2; 
  Long64_t * ns1; 
  Long64_t * ns2; 
  Int_t en1=0, en2=0;
  Int_t ens1, ens2; //Number of entries for input runs
  //sanity checks
  if(run1==this) {printf("Can't merge CRTRun with itself!\n"); return 0;}
  if(run2==this) {printf("Can't merge CRTRun with itself!\n"); return 0;}
  if(!IsWritable()) {printf("Run is opened in Read Only mode! Can't proceed.\n"); return 0;}
  if(!run1->index) {printf("Run1 is not sorted! Can't proceed.\n"); return 0;}
  if(!run2->index) {printf("Run2 is not sorted! Can't proceed.\n"); return 0;}
  ens1=run1->t->GetEntries();   
  ens2=run2->t->GetEntries();   
  printf("Merging run1 (%d entries) with run2 (%d entries)..\n",ens1,ens2);
  run1->t->LoadBaskets();
  run2->t->LoadBaskets();
  ind1=run1->index;
  ind2=run2->index;
  s1=((TTreeIndex*)(run1->t->GetTreeIndex()))->GetIndexValues();
  s2=((TTreeIndex*)(run2->t->GetTreeIndex()))->GetIndexValues();
  ns1=((TTreeIndex*)(run1->t->GetTreeIndex()))->GetIndexValuesMinor();
  ns2=((TTreeIndex*)(run2->t->GetTreeIndex()))->GetIndexValuesMinor();

  while (en1<ens1 || en2<ens2)
  { 
    if(en1>=ens1) //run 1 exhausted, write run2 only
    {
      CopyEntryFromRun(run2,ind2[en2]);
 //     printf("A1: run2 en2=%d ind2=%lld s=%lld ns=%lld\n",en2, ind2[en2],s2[en2],ns2[en2]); 
      if(s2[en2]>0) Fill();
      en2++;
    } else 
    if(en2>=ens2) //run 2 exhausted, write run1 only
    {
      CopyEntryFromRun(run1,ind1[en1]);
  //    printf("A2: run1 en1=%d ind1=%lld s=%lld ns=%lld\n",en1, ind1[en1],s1[en1],ns1[en1]); 
      if(s1[en1]>0) Fill();
      en1++;
    } else
    if(s1[en1]>s2[en2]) 
    { //Write smaller one - en2
      CopyEntryFromRun(run2,ind2[en2]);
 //     printf("A3: run2 en2=%d ind2=%lld s=%lld ns=%lld\n",en2, ind2[en2],s2[en2],ns2[en2]); 
      if(s2[en2]>0) Fill();
      en2++;
    } else
    if(s1[en1]<s2[en2]) 
    { //Write smaller one - en1
      CopyEntryFromRun(run1,ind1[en1]);
 //     printf("A4: run1 en1=%d ind1=%lld s=%lld ns=%lld\n",en1, ind1[en1],s1[en1],ns1[en1]); 
      if(s1[en1]>0) Fill();
      en1++;
    } else

    if(ns1[en1]>ns2[en2]) 
    { //Write smaller one - en2
      CopyEntryFromRun(run2,ind2[en2]);
 //     printf("A5: run2 en2=%d ind2=%lld s=%lld ns=%lld\n",en2, ind2[en2],s2[en2],ns2[en2]); 
      if(s2[en2]>0) Fill();
      en2++;
    } else
    if(ns1[en1]<=ns2[en2]) 
    { //Write smaller one - en1
      CopyEntryFromRun(run1,ind1[en1]);
 //     printf("A6: run1 en1=%d ind1=%lld s=%lld ns=%lld\n",en1, ind1[en1],s1[en1],ns1[en1]); 
     if(s1[en1]>0) Fill();
      en1++;
    } 
    if(en1%1000==1)  printf("run1 en1=%d ind1=%lld s=%lld ns=%lld\n",en1, ind1[en1],s1[en1],ns1[en1]); 
    if(en2%1000==1)  printf("run2 en2=%d ind2=%lld s=%lld ns=%lld\n",en2, ind2[en2],s2[en2],ns2[en2]); 
  }
//  rheader->N = run1->rheader->N + run2->rheader->N;
  rheader->NRawhits = run1->rheader->NRawhits + run2->rheader->NRawhits; //Number of raw hits in current entry
  rheader->N2Dhits = run1->rheader->N2Dhits + run2->rheader->N2Dhits; //Number of 2D hits in current entry
  rheader->NEvents = run1->rheader->NEvents + run2->rheader->NEvents; //Number of Events in current entry
  rheader->NTracks = run1->rheader->NTracks + run2->rheader->NTracks; //Number of Tracks in current entry
  rheader->NFlashes = run1->rheader->NFlashes + run2->rheader->NFlashes; //Number of Tracks in current entry
  rheader->cal=run1->rheader->cal; //set pointer to calibration object from run1
  index=0;
  if(run1->rheader->startSecondsUTC > run2->rheader->startSecondsUTC) rheader->startSecondsUTC=run2->rheader->startSecondsUTC;
  else  rheader->startSecondsUTC=run1->rheader->startSecondsUTC;
  if(run1->rheader->endSecondsUTC > run2->rheader->endSecondsUTC) rheader->endSecondsUTC=run1->rheader->endSecondsUTC;
  else rheader->endSecondsUTC=run2->rheader->endSecondsUTC; 

  for(int i=0;i<NFEBS; i++) 
    {
    rheader->Nt0refs[i]=run1->rheader->Nt0refs[i]+run2->rheader->Nt0refs[i];
    rheader->Nt1refs[i]=run1->rheader->Nt1refs[i]+run2->rheader->Nt1refs[i];
    }

  return rheader->N;
} 

//______________________________________________________________________________
void CRTRun::Close()
{
  f = t->GetCurrentFile();
  const char *status = f->GetOption();	
  f->cd();
 	  if( strcmp(status,"READ") ) {             // file is in "write" mode
 	    if(t)          t->Write("t",TObject::kOverwrite);
 	    if(rheader)        rheader->Write("Header",TObject::kOverwrite);
 	  }
 	  f->Purge();
 	  f->Close();
}

void CRTRun::SetCalibs(CRTCalibs * c){rheader->cal=c;}


//______________________________________________________________________________
void CRTRun::AddRawhit(CRTRawhit * h)
{  
  if(!hits) return;
  CRTRawhit * ht;
  ht=(CRTRawhit*)(new((*hits)[hits->GetLast()+1])  CRTRawhit());
  ht->Copy(h);
  rheader->NRawhits++;
  NRawhits++;
  if(ht->s > rheader->endSecondsUTC) rheader->endSecondsUTC=ht->s; 
  if(ht->s>0 && ht->s < rheader->startSecondsUTC) rheader->startSecondsUTC=ht->s;
  if(ht->s>0 && rheader->startSecondsUTC==0) rheader->startSecondsUTC=ht->s;
  if(ht->IsT0RefEvent() && ht->mac5>0 && ht->mac5<NFEBS) (rheader->Nt0refs[ht->mac5])++; 
  if(ht->IsT1RefEvent() && ht->mac5>0 && ht->mac5<NFEBS) (rheader->Nt1refs[ht->mac5])++; 
}
//______________________________________________________________________________
void CRTRun::AddRawhitBuffer(CRTRawhitBuffer *b)
{  
  if(!hits) return;
  CRTRawhit * ht;
  CRTRawhit * ht1;
  for(int i=0; i<b->Nhits;i++)
  {
  ClearEntry();
  ht1=(CRTRawhit*)(b->hits->At(i));
  ht=(CRTRawhit*)(new((*hits)[hits->GetLast()+1])  CRTRawhit());
  ht->Copy(ht1);
  rheader->NRawhits++;
  NRawhits=1;
  if(ht->s > rheader->endSecondsUTC) rheader->endSecondsUTC=ht->s; 
  if(ht->s>0 && ht->s < rheader->startSecondsUTC) rheader->startSecondsUTC=ht->s; 
  if(ht->s>0 && rheader->startSecondsUTC==0) rheader->startSecondsUTC=ht->s;
  if(ht->IsT0RefEvent() && ht->mac5>0 && ht->mac5<NFEBS) (rheader->Nt0refs[ht->mac5])++; 
  if(ht->IsT1RefEvent() && ht->mac5>0 && ht->mac5<NFEBS) (rheader->Nt1refs[ht->mac5])++; 
 
 Fill();
  }
}


//______________________________________________________________________________
void CRTRun::Add2Dhit(CRT2Dhit * h)
{
  if(!h2d) return;
  CRT2Dhit * ht;
  ht=(CRT2Dhit*)(new((*h2d)[h2d->GetLast()+1])  CRT2Dhit());
  ht->Copy(h);
  rheader->N2Dhits++;
  N2Dhits++;
  if(ht->s > rheader->endSecondsUTC) rheader->endSecondsUTC=ht->s; 
  if(ht->s>0 && ht->s < rheader->startSecondsUTC) rheader->startSecondsUTC=ht->s;
  if(ht->s>0 && rheader->startSecondsUTC==0) rheader->startSecondsUTC=ht->s;
 // printf("start %d end %d h %d ht %d\n",  rheader->startSecondsUTC, rheader->endSecondsUTC, h->s, ht->s);
}

//______________________________________________________________________________
void CRTRun::AddEvent(CRTEvent * e)
{
  if(!evs) return;
  CRTEvent *ev;
  ev=(CRTEvent*)(new((*evs)[evs->GetLast()+1])  CRTEvent());
  ev->Copy(e);
  rheader->NEvents++;
  NEvents++;
  if(ev->s > rheader->endSecondsUTC) rheader->endSecondsUTC=ev->s; 
  if(ev->s>0 && ev->s < rheader->startSecondsUTC) rheader->startSecondsUTC=ev->s; 
  if(ev->s>0 && rheader->startSecondsUTC==0) rheader->startSecondsUTC=ev->s;
}

//______________________________________________________________________________
void CRTRun::AddTrack(CRTTrack * e)
{
  if(!trk) return;
  CRTTrack *ev;
  ev=(CRTTrack*)(new((*trk)[trk->GetLast()+1])  CRTTrack());
  ev->Copy(e);
  rheader->NTracks++;
  NTracks++;
  if(ev->hit2d[0].s > rheader->endSecondsUTC) rheader->endSecondsUTC=ev->hit2d[0].s; 
  if(ev->hit2d[0].s>0 && ev->hit2d[0].s < rheader->startSecondsUTC) rheader->startSecondsUTC=ev->hit2d[0].s; 
  if(ev->hit2d[0].s>0 && rheader->startSecondsUTC==0) rheader->startSecondsUTC=ev->hit2d[0].s;
}


//______________________________________________________________________________
void CRTRun::AddFlash(PMTFlash * e)
{
  if(!fl) return;
  PMTFlash *ev;
  ev=(PMTFlash*)(new((*fl)[fl->GetLast()+1])  PMTFlash());
  ev->Copy(e);
  rheader->NFlashes++;
  NFlashes++;
}


//______________________________________________________________________________
Int_t CRTRun::GetEntrySortedByTime(Int_t en)
{
  if(index==0) return 0;
  if(en<0 || en>=t->GetEntries()) return 0;
  return t->GetEntry(index[en]);
}




