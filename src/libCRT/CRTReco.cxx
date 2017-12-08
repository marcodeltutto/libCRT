//-- Author :  Igor Kreslo, 2017

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// CRTReco                                                              //
//                                                                      //
// Reconstruction classes for uBooNE/SBND CRT data                      //
// Igor Kreslo, LHEP Uni-Bern (Igor.Kreslo@cern.ch)                     //
//////////////////////////////////////////////////////////////////////////

#include "CRTReco.h"

ClassImp(CRTReco)



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
//  ttpc->Branch("tr",&(ev.tr));
  ttpc->Branch("fl",&(ev.flar));
  ttpc->Branch("event",&(ev.event),"event/I");
  ttpc->Branch("IsBNB",&(ev.IsBNB),"IsBNB/I");
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
   //  printf("Index %d Tree Entry %lld beam=%d t1=%lf\n",i,ind[i],beam,fl.t1);
     if(prevev==-1) {ev.event=event; prevev=event;} //init at first entry
     if(event!=prevev) { if(ev.s>0) ttpc->Fill(); ev.Clear(); ev.event=event; prevev=event;} //event changed, perform fill
 //    if(beam==0) ev.IsBNB=1; else  ev.IsBNB=0; //inverted logic in David's file
     ev.s=s;
     ev.trig_t0=trig_t0; 
     fl.t1=fl.t1*1000.; //convert us to ns 
     fl.s=s;
     fl.event=event;
     ev.IsBNB=1-beam;
     fl.IsBNB=1-beam;
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
  Int_t tssec;
  Int_t tsnsec;
  Int_t evnum;
  ftpc=new TFile(fno,"RECREATE");
  ttpc=new TTree();
//  ttpc->Branch("tr",&(ev.tr));
  
  ttpc->Branch("tsx",&(ev.tsx));
  ttpc->Branch("tsy",&(ev.tsy));
  ttpc->Branch("tsz",&(ev.tsz));
  ttpc->Branch("tex",&(ev.tex));
  ttpc->Branch("tey",&(ev.tey));
  ttpc->Branch("tez",&(ev.tez));
  ttpc->Branch("tL",&(ev.tL));
  ttpc->Branch("fl",&(ev.flar));
  ttpc->Branch("event",&(ev.event),"event/I");
  ttpc->Branch("IsBNB",&(ev.IsBNB),"IsBNB/I");
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
  //Version 2 of TPCEvent
  t1->SetBranchAddress("track_startX",&(ev.tsx));
  t1->SetBranchAddress("track_startY",&(ev.tsy));
  t1->SetBranchAddress("track_startZ",&(ev.tsz));
  t1->SetBranchAddress("track_endX",&(ev.tex));
  t1->SetBranchAddress("track_endY",&(ev.tey));
  t1->SetBranchAddress("track_endZ",&(ev.tez));
  t1->SetBranchAddress("track_length",&(ev.tL));
/* //Version 1 of TPCEvent
  t1->SetBranchAddress("track_startX",&(tr.hit2d[0].x));
  t1->SetBranchAddress("track_startY",&(tr.hit2d[0].y));
  t1->SetBranchAddress("track_startZ",&(tr.hit2d[0].z));
  t1->SetBranchAddress("track_endX",&(tr.hit2d[1].x));
  t1->SetBranchAddress("track_endY",&(tr.hit2d[1].y));
  t1->SetBranchAddress("track_endZ",&(tr.hit2d[1].z));
  t1->SetBranchAddress("track_length",&(tr.L));
*/ 
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
 //    tr.L=tr.L/100.; //convert cm to meters
     ev.tL=ev.tL/100.; //convert cm to meters
     fl.s=ev.s;
     ev.AddFlash(&fl);
    // ev.tr->Copy(&tr); 
   //  ev.IsBNB=1-beam;
  //   fl.IsBNB=1-beam;
     ev.IsBNB=1; 
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
Int_t CRTReco::MatchFlashestoCRT(const char * fncrt, const char *fntpc, const char *fno, Double_t dtns, Double_t offsetns)
{
  PMTFlash *fl;
  Int_t matched=0;
  TPCEvent ev;
  CRTEvent cev;
 // CRTTrack tr;
  TTreeIndex *tind;
  Int_t retval=0;
  CRTRun *run=new CRTRun();
  if(run->OpenExistingDataRun(fncrt)==0) return 0;
  run->PrintSummary(); 
  TFile * f2=new TFile(fntpc);
  if(!f2) return 0;
  TTree * tpmt=(TTree*)f2->Get("pmt");
  if(!tpmt) return 0;

  CRTRun *orun=new CRTRun();
  orun->CreateNewDataRun(fno);
    orun->t->Branch("tsx",&(ev.tsx),"tsx/D"); 
    orun->t->Branch("tsy",&(ev.tsy),"tsy/D"); 
    orun->t->Branch("tsz",&(ev.tsz),"tsz/D"); 
    orun->t->Branch("tex",&(ev.tex),"tex/D"); 
    orun->t->Branch("tey",&(ev.tey),"tey/D"); 
    orun->t->Branch("tez",&(ev.tez),"tez/D"); 
    orun->t->Branch("tL",&(ev.tL),"tL/D"); 
 // orun->t->SetAlias("matched","abs(1.*fl[].t1-h2d[].t1-535)<55&&fl[].s-h2d[].s>=-1&&fl[].s-h2d[].s<=0");
  Long64_t * ind=0;
  Int_t sec;
  Double_t flash_t1=0;
  //Double_t crt_t1;
  Long64_t firstentry, lastentry; 
  tpmt->BuildIndex("fl[0].s","fl[0].t1");
   ind=((TTreeIndex*)tpmt->GetTreeIndex())->GetIndex();
   tind=(TTreeIndex*)(run->t->GetTreeIndex());
   if(tind<=0) { printf("Input CRT run has no index! Exiting.\n"); return 0; }

  Int_t N=tpmt->GetEntries();
/*
  tpmt->SetBranchAddress("tr",&(ev.tr));
  tpmt->SetBranchAddress("fl",&(ev.flar));
  tpmt->SetBranchAddress("event",&(ev.event));
  tpmt->SetBranchAddress("IsBNB",&(ev.IsBNB));
  tpmt->SetBranchAddress("trig_t0",&(ev.trig_t0));
  tpmt->SetBranchAddress("trig_s",&(ev.s));
  tpmt->SetBranchAddress("Nflashes",&(ev.Nflashes));
*/
  tpmt->SetBranchAddress("tsx",&(ev.tsx));
  tpmt->SetBranchAddress("tsy",&(ev.tsy));
  tpmt->SetBranchAddress("tsz",&(ev.tsz));
  tpmt->SetBranchAddress("tex",&(ev.tex));
  tpmt->SetBranchAddress("tey",&(ev.tey));
  tpmt->SetBranchAddress("tez",&(ev.tez));
  tpmt->SetBranchAddress("tL",&(ev.tL));
  tpmt->SetBranchAddress("fl",&(ev.flar));
  tpmt->SetBranchAddress("event",&(ev.event));
  tpmt->SetBranchAddress("IsBNB",&(ev.IsBNB));
  tpmt->SetBranchAddress("trig_t0",&(ev.trig_t0));
  tpmt->SetBranchAddress("trig_s",&(ev.s));
  tpmt->SetBranchAddress("Nflashes",&(ev.Nflashes));
  
  printf("Scanning TPC flashes file with %d entries.",N); 
  for(int entry=0; entry<N; entry++)
  {
    tpmt->GetEntry(ind[entry]); 
    sec=ev.s;
    firstentry=tind->GetEntryNumberWithBestIndex(sec-1,0); if(firstentry<0) firstentry=0;
    lastentry=tind->GetEntryNumberWithBestIndex(sec+3,0); if(lastentry<0) lastentry=0;
 //   printf("TPC sec %d, searching between entries %lld and %lld\n",sec,firstentry, lastentry);
 //   printf("-----------------------------------------------------------\n");
    for(int ren=firstentry; ren<=lastentry; ren++)
    {
       run->GetEntry(ren);
     //  orun->CopyEntryFromRun(run,ren);
       for(int fli=0; fli<ev.flar->GetEntries(); fli++) //loop on flashes
       {
        fl=(PMTFlash*)(ev.flar->At(fli));
        flash_t1=fl->t1 - offsetns;
	 
       for(int i=0; i<run->hits->GetEntries(); i++)  //check with raw hits
	 if(abs ( ((CRTRawhit*)(run->hits->At(i)))->ts1  - flash_t1)<dtns ) 
	 if(abs ( ((CRTRawhit*)(run->hits->At(i)))->s  - sec)<3 ) 
          { 
	    matched=1; 
            orun->AddRawhit((CRTRawhit*)(run->hits->At(i)));
	 //   ((CRTRawhit*)(run->hits->At(i)))->Print();
	   // break; 
	  } 
     //  printf("Looping on 2dhits, h2d->GetEntries()=%d \n", run->h2d->GetEntries()); 
       for(int i=0; i<run->h2d->GetEntries(); i++) //check with 2d hits
	 if(abs ( ((CRT2Dhit*)(run->h2d->At(i)))->t1  - flash_t1)<dtns ) 
	 if(abs ( ((CRT2Dhit*)(run->h2d->At(i)))->s  - sec)<3 ) 
          { 
	    matched=1; 
            orun->Add2Dhit((CRT2Dhit*)(run->h2d->At(i)));
	// printf("Added 2dhit, NTracks=%d N2Dhits=%d \n", orun->NTracks,orun->N2Dhits);
	//    ((CRT2Dhit*)(run->h2d->At(i)))->Print();
	 //   break; 
	  }  
       for(int i=0; i<run->trk->GetEntries(); i++) //check with tracks (only one 2d hit)
	 if(abs ( ((CRTTrack*)(run->trk->At(i)))->hit2d[0].t1  - flash_t1)<dtns ) 
	 if(abs ( ((CRTTrack*)(run->trk->At(i)))->hit2d[0].s  - sec)<3 ) 
          { 
	    matched=1;
            orun->AddTrack((CRTTrack*)(run->trk->At(i))); 
	// printf("Added track, NTracks=%d N2Dhits=%d \n", orun->NTracks,orun->N2Dhits);
	//    ((CRTTrack*)(run->trk->At(i)))->Print();
	 //   break;
	  }  
       if(matched) 
         {
	 printf("Match: TPC event %d: s=%d ns=%lf CRT entry %d!\n", ev.event, ev.s, flash_t1, ren);
	// printf("NTracks=%d N2Dhits=%d \n\n", orun->NTracks,orun->N2Dhits);
        // fl->IsBNB=ev.IsBNB;
         fl->event=ev.event;
         orun->AddFlash(fl);
         cev.s=ev.s;
         cev.mean_t0=ev.trig_t0;
         cev.mean_t1=fl->t1;
         orun->AddEvent(&cev);
	 matched=0;
         }	 
       }
       if(orun->NFlashes>0) 
          { 
            orun->rheader->NRawhits += orun->NRawhits;
            orun->rheader->N2Dhits += orun->N2Dhits;
            orun->rheader->NTracks += orun->NTracks;
            orun->rheader->NEvents += orun->NEvents;
            orun->Fill(); 
            orun->ClearEntry();
          }

    }
    
  }
  orun->SetCalibs(run->rheader->cal);
  orun->PrintSummary();
  orun->Close();
  run->Close();
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





