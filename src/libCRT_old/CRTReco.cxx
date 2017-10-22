//-- Author :  Igor Kreslo, 2017

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// CRTReco                                                              //
//                                                                      //
// Reconstruction classes for uBooNE/SBND CRT data                      //
// Igor Kreslo, LHEP Uni-Bern (Igor.Kreslo@cern.ch)                     //
//////////////////////////////////////////////////////////////////////////

#include "CRTReco.h"



ClassImp(PMTFlash)
ClassImp(TPCEvent)
ClassImp(CRTReco)


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
  printf("%lf P.E. at (%lf,%lf,%lf), t1=%lf, s=%d. Absolute %lf ns.\n",npe, x,y,z, t1, s, t0);
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
}



//______________________________________________________________________________
CRTReco::CRTReco()
{

}

Int_t CRTReco::ConvertDavidFlashTree(const char * fn1, const char *fno)
{
  PMTFlash fl;
  TPCEvent ev;

  Long64_t * ind=0; 
  Int_t event;
  Int_t beam;
  Int_t trig_t0;
  Int_t prevev=-1;
  Int_t s;
  //Double_t t1;
  ftpc=new TFile(fno,"RECREATE");
  ttpc=new TTree();
  ttpc->Branch("tr",&(ev.tr));
  ttpc->Branch("fl",&(ev.flar));
  ttpc->Branch("event",&(ev.event),"event/I");
  ttpc->Branch("BNB",&(ev.IsBNB),"IsBNB/I");
  ttpc->Branch("trig_t0",&(ev.trig_t0),"trig_t0/I");
  ttpc->Branch("trig_s",&(ev.s),"s/I");
  ttpc->Branch("Nflashes",&(ev.Nflashes),"Nflashes/I");



  TFile * f1=new TFile(fn1);
  if(!f1) return 0;
  TTree * t1=(TTree*)f1->Get("crt/flash_tree");
  if(!t1) return 0;
  Int_t N=t1->GetEntries();
  t1->SetBranchAddress("event",&event);
  t1->SetBranchAddress("beam",&beam);
  t1->SetBranchAddress("trigger_ts",&s);
  t1->SetBranchAddress("trigger_tns",&trig_t0);
  t1->SetBranchAddress("Y_reco",&(fl.y));
  t1->SetBranchAddress("Z_reco",&(fl.z));
  t1->SetBranchAddress("N_PE",&(fl.npe));
  t1->SetBranchAddress("T_flash",&(fl.t1));
  t1->SetBranchAddress("Abs_T_flash",&(fl.t0));

//  t1->BuildIndex("trigger_ts","T_flash");
  t1->BuildIndex("trigger_ts","event");
  ind=((TTreeIndex*)t1->GetTreeIndex())->GetIndex();
  if(ind==0) return 0;
  for(int i=0;i<N;i++)
   {
     t1->GetEntry(ind[i]);
     if(prevev==-1) {ev.event=event; prevev=event;} //init at first entry
     if(event!=prevev) { if(ev.s>0) ttpc->Fill(); ev.Clear(); ev.event=event; prevev=event;} //event changed, perform fill
     if(beam==0) ev.IsBNB=1; else  ev.IsBNB=0; //inverted logic in David's file
     ev.s=s;
     ev.trig_t0=trig_t0; 
     fl.t1=fl.t1*1000.; //convert us to ns 
     fl.s=s;
     if(s>0) ev.AddFlash(&fl);
   }
   ttpc->Fill(); //fill last event
  
  f1->Close();
  ftpc->cd();
  ttpc->Write("pmt",kOverwrite); 
  ftpc->Close();
  return N;
}

Int_t CRTReco::ConvertChrisFlashTree(const char * fn1, const char *fno)
{
  PMTFlash fl;
  TPCEvent ev;
  CRTTrack tr;
 // Long64_t * ind=0; 
  UInt_t tssec;
  UInt_t tsnsec;
Double_t evnum;
  ftpc=new TFile(fno,"RECREATE");
  ttpc=new TTree();
  ttpc->Branch("tr",&(ev.tr));
  ttpc->Branch("fl",&(ev.flar));
  ttpc->Branch("event",&(ev.event),"event/I");
  ttpc->Branch("BNB",&(ev.IsBNB),"IsBNB/I");
  ttpc->Branch("trig_t0",&(ev.trig_t0),"trig_t0/I");
  ttpc->Branch("trig_s",&(ev.s),"s/I");
  ttpc->Branch("Nflashes",&(ev.Nflashes),"Nflashes/I");



  TFile * f1=new TFile(fn1);
  if(!f1) return 0;
  TTree * t1=(TTree*)f1->Get("SCEtree");
  if(!t1) return 0;
  Int_t N=t1->GetEntries();
  t1->SetBranchAddress("event_eventNum",&evnum);
  t1->SetBranchAddress("ts_seconds",&tssec);
  t1->SetBranchAddress("ts_nanoseconds",&tsnsec);
  t1->SetBranchAddress("track_startX",&(tr.hit2d[0].x));
  t1->SetBranchAddress("track_startY",&(tr.hit2d[0].y));
  t1->SetBranchAddress("track_startZ",&(tr.hit2d[0].z));
  t1->SetBranchAddress("track_endX",&(tr.hit2d[1].x));
  t1->SetBranchAddress("track_endY",&(tr.hit2d[1].y));
  t1->SetBranchAddress("track_endZ",&(tr.hit2d[1].z));
  t1->SetBranchAddress("track_length",&(tr.L));
   
  t1->SetBranchAddress("pe_flash",&(fl.npe));
  t1->SetBranchAddress("time_flash",&(fl.t1));
  t1->SetBranchAddress("t0",&(fl.t0));

//  t1->BuildIndex("trigger_ts","T_flash");
//  t1->BuildIndex("tr_seconds","event");
//  ind=((TTreeIndex*)t1->GetTreeIndex())->GetIndex();
//  if(ind==0) return 0;
  for(int i=0;i<N;i++)
   {
 //    t1->GetEntry(ind[i]);
     t1->GetEntry(i);
     ev.event=int(evnum);
     ev.s=tssec;
     ev.trig_t0=tsnsec;
     fl.t1=fl.t1*1000.; //convert us to ns 
     fl.t0=fl.t0*1000.; //convert us to ns 
     tr.L=tr.L/100.; //convert cm to meters
     fl.s=ev.s;
     ev.AddFlash(&fl);
     ev.tr->Copy(&tr); 
  //   if(beam==0) ev.IsBNB=1; else  ev.IsBNB=0; //inverted logic in David's file
     ev.IsBNB=0; 
     if(ev.s>0) ttpc->Fill(); 
     ev.Clear(); 
   }
  
  f1->Close();
  ftpc->cd();
  ttpc->Write("pmt",kOverwrite); 
  ftpc->Close();
  return N;
}

//______________________________________________________________________________
Int_t CRTReco::MatchFlashestoCRT(const char * fncrt, const char *fntpc, const char *fno)
{
//  PMTFlash fl;
  TPCEvent ev;
 // CRTTrack tr;
  Int_t retval=0;
  CRTRun *run=new CRTRun();
  if(run->OpenExistingDataRun(fncrt)==0) return 0;
  TFile * f2=new TFile(fntpc);
  if(!f2) return 0;
  TTree * tpmt=(TTree*)f2->Get("pmt");
  if(!tpmt) return 0;

  Long64_t * ind=0;
  Int_t firstentry, lastentry; 
  tpmt->BuildIndex("fl[0].s","fl[0].t1");
  ind=((TTreeIndex*)tpmt->GetTreeIndex())->GetIndex();

  Int_t N=tpmt->GetEntries();

  tpmt->SetBranchAddress("tr",&(ev.tr));
  tpmt->SetBranchAddress("fl",&(ev.flar));
  tpmt->SetBranchAddress("event",&(ev.event));
  tpmt->SetBranchAddress("BNB",&(ev.IsBNB));
  tpmt->SetBranchAddress("trig_t0",&(ev.trig_t0));
  tpmt->SetBranchAddress("trig_s",&(ev.s));
  tpmt->SetBranchAddress("Nflashes",&(ev.Nflashes));
  
  for(int entry=0; entry<N; entry++)
  {
    tpmt->GetEntry(ind[entry]);  
  }

  return retval;
}



//______________________________________________________________________________
void CRTReco::Print(Int_t Verbosity) 
{
 // printf("%lf P.E. at (%lf,%lf,%lf), t1=%lf, s=%d. Absolute %lf ns.\n",npe, x,y,z, t1, s, t0);
}


//______________________________________________________________________________
CRTReco::~CRTReco()
{
}

//______________________________________________________________________________
void CRTReco::Clear()
{

}





