//-- Author :  Igor Kreslo, 2017


//////////////////////////////////////////////////////////////////////////
//                                                                      //
// CRTDisplay                                                           //
//                                                                      //
// Class to display CRT events in 3D                                    //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "TROOT.h"
#include "TStyle.h"
#include "TColor.h"
#include "TSystem.h"
#include "CRTDisplay.h"

ClassImp(CRTDisplay)


//________________________________________________________________________
CRTDisplay::~CRTDisplay() 
{
}


//________________________________________________________________________
CRTDisplay::CRTDisplay() 
{
   geom = new TGeoManager("CRT", "uBooNE CRT event display");
   //--- define some materials
   TGeoMaterial *matVacuum = new TGeoMaterial("Vacuum", 0,0,0);
   TGeoMaterial *matAl = new TGeoMaterial("Al", 26.98,13,2.7);
//   //--- define some media
   TGeoMedium *Vacuum = new TGeoMedium("Vacuum",1, matVacuum);
   TGeoMedium *Al = new TGeoMedium("Aluminium",2, matAl);
 //  TGeoMedium *LAr = new TGeoMedium("Liquid Argon",146,146,0,1,8,90,-1,-1,0.5,-1);
   //--- make the top container volume
   TGeoVolume *top = geom->MakeBox("TOP", Vacuum, 2000., 2000., 2000.);
   geom->SetTopVolume(top);

   // Make the elementary assembly of the whole structure
   TGeoVolume *crt = new TGeoVolumeAssembly("CRT");
   TGeoVolume *crt_top=geom->MakeBox("TOP", Al, 375, 2, 650);
   TGeoVolume *crt_bot=geom->MakeBox("BOT", Al, 275, 2, 260);
   TGeoVolume *crt_pipe=geom->MakeBox("PIPE", Al, 2, 260, 625);
   TGeoVolume *crt_ft=geom->MakeBox("FT", Al, 2, 175, 625);
  // roi->SetTransparency(0);
   crt_top->SetLineColor(kBlue);
   crt_bot->SetLineColor(kBlue);
   crt_pipe->SetLineColor(kBlue);
   crt_ft->SetLineColor(kBlue);
   crt_top->SetTransparency(70);
   crt_bot->SetTransparency(70);
   crt_pipe->SetTransparency(70);
   crt_ft->SetTransparency(70);


   TGeoVolume *cryo = geom->MakeTube("CRYO", Al, 187,170,550);
   cryo->SetTransparency(70);
   cryo->SetVisibility(kTRUE);
   cryo->SetLineColor(kYellow);

   crt->AddNode(crt_top, 0, new TGeoTranslation(125,658,550));
   crt->AddNode(crt_bot, 1, new TGeoTranslation(125,-262,535));
   crt->AddNode(crt_pipe, 2, new TGeoTranslation(390,40,525));
   crt->AddNode(crt_ft, 3, new TGeoTranslation(-142,-40,530));
 //  crt->AddNode(crt_ft, 3, new TGeoTranslation(-142,-105,550));
   crt->AddNode(cryo, 4, new TGeoTranslation(125,0,550));
   top->AddNode(crt, 0, new TGeoTranslation(0,0,0));
   //--- close the geometry
   geom->CloseGeometry();

  teve=TEveManager::Create();
   node = geom->GetTopNode();
   en = new TEveGeoTopNode(geom, node);
   en->SetVisLevel(4);

   en->GetNode()->GetVolume()->SetVisibility(kFALSE);


  teve->AddGlobalElement(en);
    Double_t cc[3]={0,0,0};
  teve->GetDefaultGLViewer()->SetOrthoCamera(TGLViewer::kCameraOrthoXOY, 1, 0,cc,0,90);
  teve->GetDefaultGLViewer()->SetClearColor(kWhite);
//  fb = new TEveFrameBox(); 
 // fb->SetFrameColor(kCyan);
 //  fb->SetBackColorRGBA(120,120,120,20);
 //  fb->SetDrawBack(kTRUE);
 // fb->SetAABox(-250,-260,-100,500+250,660+260,1150+100);
    const Int_t NRGBs = 5;
    const Int_t NCont = 255;

    Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
    Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
    Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
    Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
    TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
    gStyle->SetNumberContours(NCont);
    gStyle->SetOptStat(0);
    TColor(255,0,0,0.5);

    elist=0;

  qraw = new TEveBoxSet("CRTRawhits"); //raw ADC single hits  

  comp_h2d= new TEveCompound("CRT2DHits");//2d hit with children
  h2d = new TEveBoxSet("2DHits");//fitted 2D coord
  h2d_raw = new TEveBoxSet("CRTRawhits");//raw ADCs crossing at fitted 2D coord

  comp_trk= new TEveCompound("CRTTracks");
  trk_h2d = new TEveBoxSet("2DHits");//fitted 2D coord
  trk_h2d_raw = new TEveBoxSet("CRTRawhits");//raw ADCs crossing at fitted 2D coord
  lines = new TEveStraightLineSet("Tracks");
  lines->SetLineColor(kMagenta);
//  lines->SetLineColor(kYellow);
  lines->SetLineWidth(2);

  pal = new TEveRGBAPalette(0, 2*4096);


   qraw->SetPalette(pal);
   qraw->Reset(TEveBoxSet::kBT_AABox, kFALSE, 64);
   h2d->SetPalette(pal);
   h2d->Reset(TEveBoxSet::kBT_AABox, kFALSE, 64);
   h2d_raw->SetPalette(pal);
   h2d_raw->Reset(TEveBoxSet::kBT_AABox, kFALSE, 64);
   trk_h2d->SetPalette(pal);
   trk_h2d->Reset(TEveBoxSet::kBT_AABox, kFALSE, 64);
   trk_h2d_raw->SetPalette(pal);
   trk_h2d_raw->Reset(TEveBoxSet::kBT_AABox, kFALSE, 64);

   teve->AddElement(qraw);
 

   comp_h2d->AddElement(h2d);
   comp_h2d->AddElement(h2d_raw);
   teve->AddElement(comp_h2d);

   comp_trk->AddElement(lines);
   comp_trk->AddElement(trk_h2d);
   comp_trk->AddElement(trk_h2d_raw);


   teve->AddElement(comp_trk);   

   Verb=0;
   cal=0;
   run=0;
   curev=0;
   teve->Redraw3D(kTRUE);
}

//_______________________________________________________________________
void CRTDisplay::AddRawhit(CRTRawhit * hit, Bool_t ShowAllADCs, Double_t X2D, Double_t Y2D, Double_t Z2D, Int_t Level )
{
  if(cal==0) return;
  Int_t max_nch=0, max_ach=0, ch, pl;
  Double_t x,y,z,sx,sy,sz,pulse;
  Double_t mx,my,mz;

  if(ShowAllADCs) for(int i=0;i<32;i++)
    {
  sx=3;
  sy=3;
  sz=3;
   if( cal->PositionExists[hit->mac5][i]==0 ) continue;

    mx=(cal->Xs[hit->mac5][i/2*2]+cal->Xs[hit->mac5][i/2*2+1])/2.;
    my=(cal->Ys[hit->mac5][i/2*2]+cal->Ys[hit->mac5][i/2*2+1])/2.;
    mz=(cal->Zs[hit->mac5][i/2*2]+cal->Zs[hit->mac5][i/2*2+1])/2.;


    x=(cal->Xs[hit->mac5][i]+mx)/2; if(cal->Xs[hit->mac5][0] == cal->Xs[hit->mac5][31] && X2D!=0 ) x=X2D;
    y=(cal->Ys[hit->mac5][i]+my)/2; if(cal->Ys[hit->mac5][0] == cal->Ys[hit->mac5][31] && Y2D!=0 ) y=Y2D;
    z=(cal->Zs[hit->mac5][i]+mz)/2; if(cal->Zs[hit->mac5][0] == cal->Zs[hit->mac5][31] && Z2D!=0 ) z=Z2D;

    if(cal->ADCCalibsExists[hit->mac5][i]>0) 
             if((cal->ADCGain[hit->mac5][i])!=0) pulse=8192.*(hit->adc[i] - cal->ADCPedestal[hit->mac5][i])/(1.*cal->ADCGain[hit->mac5][i]);
             else pulse=1.*(hit->adc[i] - cal->ADCPedestal[hit->mac5][i]);
    else pulse=( hit->adc[i] )*2.;
     
      if(Level==0) // Raw raw hit
      {
      pulse=( hit->adc[i] )*2.; //override for level-0 raw hits
      qraw->AddBox(x,y,z,sx,sy,sz);
      qraw->DigitValue(pulse);
      qraw->RefitPlex();
      }
      if(Level==1) // 2D hit child raw hit
      {
      h2d_raw->AddBox(x,y,z,sx,sy,sz);
      h2d_raw->DigitValue(pulse);
      h2d_raw->RefitPlex();
      }
      if(Level==2) // Track child raw hit
      {
      trk_h2d_raw->AddBox(x,y,z,sx,sy,sz);
      trk_h2d_raw->DigitValue(pulse);
      trk_h2d_raw->RefitPlex();
      }

    }
else
{
      
     for(int i=0;i<16;i++)
     { 
        ch=hit->adc[i*2]+hit->adc[i*2+1];
        if(ch>max_ach) {max_ach=ch; max_nch=i;}
     }
    pl=cal->getHitPlane(hit->mac5);
    if(Verb>0) printf("Displaying Rawhit pl=%d max_nch=%d max_ach=%d\n", pl, max_nch, max_ach);

  if(cal->PositionExists[hit->mac5][max_nch*2]==0 || cal->PositionExists[hit->mac5][max_nch*2+1]==0) return;
  
    x=(cal->Xs[hit->mac5][max_nch*2]+cal->Xs[hit->mac5][max_nch*2+1])/2.;
    y=(cal->Ys[hit->mac5][max_nch*2]+cal->Ys[hit->mac5][max_nch*2+1])/2.;
    z=(cal->Zs[hit->mac5][max_nch*2]+cal->Zs[hit->mac5][max_nch*2+1])/2.;

  sx=10;
  sy=10;
  sz=10;

/*  if(Xs[mac5][0]!=Xs[mac5][2]) L=Xs[mac2][strip2*2]-Xs[mac1][0]; //coord along the strip minus SiPM position
  if(Ys[mac5][0]!=Ys[mac5][2]) L=Ys[mac2][strip2*2]-Ys[mac1][0]; //coord along the strip minus SiPM position
  if(Zs[mac5][0]!=Zs[mac5][2]) L=Zs[mac2][strip2*2]-Zs[mac1][0]; //coord along the strip minus SiPM position
*/

  pulse=max_ach;


      if(Level==0) // Raw raw hit
      {
      qraw->AddBox(x,y,z,sx,sy,sz);
      qraw->DigitValue(pulse);
      qraw->RefitPlex();
      }
      if(Level==1) // 2D hit child raw hit
      {
      h2d_raw->AddBox(x,y,z,sx,sy,sz);
      h2d_raw->DigitValue(pulse);
      h2d_raw->RefitPlex();
      }
      if(Level==2) // Track child raw hit
      {
      trk_h2d_raw->AddBox(x,y,z,sx,sy,sz);
      trk_h2d_raw->DigitValue(pulse);
      trk_h2d_raw->RefitPlex();
      }
}

   teve->ElementChanged(qraw);
   teve->ElementChanged(comp_h2d);
   teve->ElementChanged(comp_trk);
   teve->Redraw3D(kFALSE);

}

//_______________________________________________________________________
void CRTDisplay::Add2Dhit(CRT2Dhit * hit, Bool_t ShowAllADCs, Int_t Level)
{
  if(cal==0) return;
  if(hit->rhit[0].IsEOPEvent()) return;
  if(hit->rhit[1].IsEOPEvent()) return;
  Double_t x,y,z,sx,sy,sz,pulse;
    x=hit->x;
    y=hit->y;
    z=hit->z;
  if(ShowAllADCs) {AddRawhit(&(hit->rhit[0]),1,x,y,z,Level+1);AddRawhit(&(hit->rhit[1]),1,x,y,z,Level+1);}

  sx=10;
  sy=10;
  sz=10;
  pulse=hit->rhit[0].GetMaxStripValue() + hit->rhit[1].GetMaxStripValue();
  pulse=pulse/2.;


  if(Level==0) // H2D hit
   {
   h2d->AddBox(x,y,z,sx,sy,sz);
   h2d->DigitValue(pulse);
   h2d->RefitPlex();
   }
  if(Level==1) // Track child H2D hit
   {
   trk_h2d->AddBox(x,y,z,sx,sy,sz);
   trk_h2d->DigitValue(pulse);
   trk_h2d->RefitPlex();
   }
   teve->ElementChanged(qraw);
   teve->ElementChanged(comp_h2d);
   teve->ElementChanged(comp_trk);
   teve->Redraw3D(kFALSE);
 
}

//_______________________________________________________________________
void CRTDisplay::AddEvent(CRTEvent * evt, Bool_t ShowAllADCs, Int_t Level)
{
  CRTRawhit *hit;
  if(cal==0) return;
 if(Verb>0) printf("CRTDisplay::AddEvent with %d hits.\n",evt->Nhits); 
  for( int i=0; i<evt->Nhits; i++)  
   {
      hit= (CRTRawhit*)(evt->hits->At(i));
      if(!hit->IsEOPEvent()) AddRawhit(hit,ShowAllADCs,Level );
   }
}
//_______________________________________________________________________
void CRTDisplay::AddTrack(CRTTrack * evt, Bool_t ShowAllADCs, Int_t Level)
{
  if(cal==0) return;
 if(Verb>0) printf("CRTDisplay::AddTrack %lf m long with tof=%lf. v=%lf m/ns\n",evt->L, evt->tof,evt->L/evt->tof); 
 Add2Dhit(&(evt->hit2d[0]),ShowAllADCs, Level+1); 
 Add2Dhit(&(evt->hit2d[1]),ShowAllADCs, Level+1); 
 lines->AddLine(evt->hit2d[0].x,evt->hit2d[0].y,evt->hit2d[0].z,evt->hit2d[1].x,evt->hit2d[1].y,evt->hit2d[1].z);
   teve->ElementChanged(qraw);
   teve->ElementChanged(comp_h2d);
   teve->ElementChanged(comp_trk);
   teve->Redraw3D(kFALSE);

}

//_______________________________________________________________________
void CRTDisplay::AddMarker(Double_t x,Double_t y,Double_t z,Double_t sx,Double_t sy,Double_t sz,Double_t ph)
{
   qraw->AddBox(x,y,z,sx,sy,sz);
   qraw->DigitValue(ph);
   qraw->RefitPlex();
   teve->ElementChanged(qraw);
   teve->ElementChanged(comp_h2d);
   teve->ElementChanged(comp_trk);
   teve->Redraw3D(kFALSE);
}


//_______________________________________________________________________
void CRTDisplay::Clear()
{
   
   qraw->Reset();
   h2d_raw->Reset();
   trk_h2d_raw->Reset();
   h2d->Reset();
   trk_h2d->Reset();
   teve->ElementChanged(qraw);
   teve->ElementChanged(comp_h2d);
   teve->ElementChanged(comp_trk);
   lines->GetLinePlex().Reset(sizeof(TEveStraightLineSet::Line_t),4);
   teve->ElementChanged(lines);
   teve->Redraw3D(kFALSE);

}

//_______________________________________________________________________
void CRTDisplay::Refresh()
{
   teve->ElementChanged(qraw);
   teve->ElementChanged(comp_h2d);
   teve->ElementChanged(comp_trk);
   teve->Redraw3D(kFALSE);
}

//_______________________________________________________________________
void CRTDisplay::ShowRunEvents(Int_t se, Int_t ee, Bool_t ShowAllADCs)
{
CRTRawhit *hit;
CRTEvent *evt;
CRT2Dhit *e2d;
CRTTrack *tra;
Long64_t ien=0;

  if(!run) {printf("Run is not set! Use SetRun(CRTRun *).\n"); return;}

    Clear();
   for(int en=se;en<=ee;en++)
  {

   if(elist) {ien=elist->GetEntry(en); printf("Cut is set. ");}
   else ien=en;
   if(run->GetEntry(ien)==0) return;
   printf("Showing tree entry #%lld\n",ien);
   for(int i=0; i<run->hits->GetEntries(); i++) 
     { 
      hit=((CRTRawhit*)(run->hits->At(i)));
     if(Verb>0) hit->Print();
      AddRawhit(hit,ShowAllADCs);
     }
   for(int i=0; i<run->h2d->GetEntries(); i++) 
     { 
      e2d=((CRT2Dhit*)(run->h2d->At(i)));
     if(Verb>0) e2d->Print();
      Add2Dhit(e2d,ShowAllADCs);
     }
   for(int i=0; i<run->evs->GetEntries(); i++) 
     { 
      evt=((CRTEvent*)(run->evs->At(i)));
     if(Verb>0) evt->Print();
      AddEvent(evt,ShowAllADCs);
     }
   for(int i=0; i<run->trk->GetEntries(); i++) 
     { 
      tra=((CRTTrack*)(run->trk->At(i)));
      if(Verb>0) tra->Print();
      AddTrack(tra,ShowAllADCs);
     }
  }
 
}

//_______________________________________________________________________
void CRTDisplay::SetCut(const char * scut)
{
  if(!run) {printf("Run is not set! Use SetRun(CRTRun *).\n"); return;}
  run->t->Draw(">>elist",scut);
  elist=(TEventList*)gDirectory->Get("elist");
  printf("%d events left for listing after the cut.\n", elist->GetN());
}




