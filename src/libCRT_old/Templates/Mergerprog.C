#define Merger_cxx
#include "Merger.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

/////////////////////////////////////////////////////////////////////////
#define MAXHPS 30000    // maximum hits per second per plane
#define MAXDT 1000   //maximum accepted time difference in coincidence
#define BUFNS 10     //number of seconds in the buffer
#define MAXENTRIES 10000000 //mux number of entries in input tree
Int_t     p_time[4][MAXHPS*BUFNS]; //average hit time stamps
Long64_t p_entry[4][MAXHPS*BUFNS]; //corresponding tree entries
//Int_t    p_evmult[4][MAXHPS*BUFNS]; //event multiplicity (number of XY-pairs or hits) for event where hit is a member
Int_t    p_used[4][MAXENTRIES]; //in how many XY-pairs the hit is a member
Int_t    p_time_ts1[4][MAXENTRIES]; //average hit time stamps
Double_t    p_tof[4][MAXENTRIES]; //average hit time stamps

/////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////

typedef struct {
		UShort_t mac5;
		UShort_t flags;
		Int_t ts0;
		Int_t ts1;
		UShort_t adc[32];
		Int_t s;
		Int_t ms;
		Int_t plane;
		Int_t maxnch;
		Int_t maxach;
		Int_t maxadc;
		Int_t nhits;

} EVENT_t;

Double_t Merger::getHitT1(int mac1, int strip1,  int t1, int mac2, int strip2, int t2)
{ 
  Double_t ret=0;
  Double_t L;
  if(Xs[mac2][0]!=Xs[mac2][2]) L=Xs[mac2][strip2*2]-Xs[mac1][0]; //coord along the strip minus SiPM position
  if(Ys[mac2][0]!=Ys[mac2][2]) L=Ys[mac2][strip2*2]-Ys[mac1][0]; //coord along the strip minus SiPM position
  if(Zs[mac2][0]!=Zs[mac2][2]) L=Zs[mac2][strip2*2]-Zs[mac1][0]; //coord along the strip minus SiPM position
  if(L<0) L=-L;
  ret=t1-L*6.2/100.; //propagation along the fiber correction, 6.2 ns/m
  ret=ret+Dts[mac1]; //ref PPS cable 
  return ret;
}

Double_t Merger::getHitT2(int mac1, int strip1,  int t1, int mac2, int strip2, int t2)
{ 
  Double_t ret=0; 
  Double_t L;
  if(Xs[mac1][0]!=Xs[mac1][2]) L=Xs[mac1][strip1*2]-Xs[mac2][0]; //coord along the strip minus SiPM position
  if(Ys[mac1][0]!=Ys[mac1][2]) L=Ys[mac1][strip1*2]-Ys[mac2][0]; //coord along the strip minus SiPM position
  if(Zs[mac1][0]!=Zs[mac1][2]) L=Zs[mac1][strip1*2]-Zs[mac2][0]; //coord along the strip minus SiPM position
  if(L<0) L=-L;
  ret=t2-L*6.2/100.; //protagation along the fiber correction,6.2 ns/m
  ret=ret+Dts[mac2];//ref PPS cable  
  return ret;
}
Double_t Merger::getHitDT(int mac1, int strip1,  int t1, int mac2, int strip2,int t2)
{ 
 return getHitT2(mac1,strip1,t1,mac2,strip2,t2)-getHitT1(mac1,strip1,t1,mac2,strip2,t2);
}

Double_t Merger::getHitT(int mac1, int strip1,  int t1, int mac2, int strip2,  int t2)
{ 
 return (getHitT2(mac1,strip1,t1,mac2,strip2,t2)+getHitT1(mac1,strip1,t1,mac2,strip2,t2))/2.;
}


void Mergerprog(char *fn1, char *fn2, char *fn3, char *fn4, int hours=4)
{
//  memset(p_evmult,0,4*4*MAXHPS*BUFNS);
  memset(p_used,0,4*MAXENTRIES);
  memset(p_time_ts1,0,4*MAXENTRIES);
  memset(p_tof,0,sizeof(Double_t)*MAXENTRIES);
  Merger t(fn1, fn2, fn3, fn4);
  t.Loop(3600*hours);
}
void Merger::Loop(int seconds)
{
//   In a ROOT session, you can do:
//      Root > .L Merger.C
//      Root > Merger t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

Int_t startsec=0;
Int_t cursec=0;
Int_t curentry[4];
Int_t secentries[4];
Int_t maxsecentries[4];
Int_t p;
Int_t prsinsec=0;
TDirectory *outDir;
TFile *outFile=new TFile("t4.root","RECREATE");
   TTree          *ft4=0;   //!pointer to the analyzed TTree  containing all hit pair combinations
   TTree          *ftev=0;   //!pointer to the analyzed TTree containing grouped event summary
   TTree          *ffr[4];   // array of pointers to friend trees

   static    EVENT_t         outev1;  
   static    EVENT_t         outev2;  
   static    EVENT_t         outev3;  
   static    EVENT_t         outev4;


        Double_t mdt,edt,ets1,medep,tedep,  ts00, ts11;
        Int_t nxyhits, curts0, curedep;
        Int_t firsthitentry;
        Double_t  mts1;
        Double_t dt;

   	if(!ft4) 
        ft4 = new TTree("t4","Event hit pairs from whole CRT");
   	ft4->Branch("event1",&outev1,"mac5/s:flags/s:ts0/I:ts1/I:adc[32]/s:s/I:ms/I:plane/I:maxnch/I:maxach/I:maxadc/I:nhits/I");
	ft4->Branch("event2",&outev2,"mac5/s:flags/s:ts0/I:ts1/I:adc[32]/s:s/I:ms/I:plane/I:maxnch/I:maxach/I:maxadc/I:nhits/I");
	ft4->Branch("event3",&outev3,"mac5/s:flags/s:ts0/I:ts1/I:adc[32]/s:s/I:ms/I:plane/I:maxnch/I:maxach/I:maxadc/I:nhits/I");
	ft4->Branch("event4",&outev4,"mac5/s:flags/s:ts0/I:ts1/I:adc[32]/s:s/I:ms/I:plane/I:maxnch/I:maxach/I:maxadc/I:nhits/I");
        ft4->Branch("dt", &dt, "dt/D");
        ft4->Branch("sec1", &sec1, "sec1/I");
        ft4->Branch("msec1", &msec1, "msec1/I");
        ft4->Branch("sec2", &sec2, "sec2/I");
        ft4->Branch("msec2", &msec2, "msec2/I");
        ft4->SetAlias("tnhits","event1.nhits+event2.nhits+event3.nhits+event4.nhits");
        ft4->SetAlias("nosat","event1.maxadc+event2.maxadc+event3.maxadc+event4.maxadc<4000*4");
	ft4->SetAlias("Amp","event1.maxach*event3.maxach>3.5e6");
	ft4->SetAlias("NoSat","event1.maxach<8170&&event2.maxach<8170&&event3.maxach<8170&&event4.maxach<8170");
	ft4->SetAlias("BNB","abs(event1.ts1+34800)<800");
	ft4->SetAlias("Cosmics","abs(event1.ts1+50800)<800");
	ft4->SetAlias("beta","9.46/dt/0.3");
	ft4->SetAlias("gamma","1./sqrt(1-beta*beta)");

        ftev = new TTree("tev","Merged Events summary from whole CRT");
        ftev->Branch("mdt", &mdt, "mdt/D"); //mean dt
        ftev->Branch("edt", &edt, "edt/D"); //RMS dt
        ftev->Branch("mts1", &mts1, "mts1/D"); //mean ts1
        ftev->Branch("ets1", &ets1, "ets1/D"); //RMS ts1
        ftev->Branch("medep", &medep, "medep/D"); //mean ADC per plane
        ftev->Branch("tedep", &tedep, "tedep/D"); //sum of all event ADC
        ftev->Branch("nxyhits", &nxyhits, "nxyhits/I"); //number of X-Y hits
        ftev->Branch("firsthitentry", &firsthitentry, "firsthitentry/I"); //entry in ft4 tree for the first xy hit
	ftev->SetAlias("BNB","abs(mts1+36500)<800");
	ftev->SetAlias("Cosmics","abs(mts1+50800)<800");
	ftev->SetAlias("beta","9.46/mdt/0.3");
	ftev->SetAlias("gamma","1./sqrt(1-beta*beta)");



        
if(GetEntry(0,1)) { if(sec<startsec || startsec==0) startsec=sec; printf("plane %d: starts from %d seconds\n",0,sec); } 
if(GetEntry(1,1)) { if(sec<startsec || startsec==0) startsec=sec; printf("plane %d: starts from %d seconds\n",1,sec); }
if(GetEntry(2,1)) { if(sec<startsec || startsec==0) startsec=sec; printf("plane %d: starts from %d seconds\n",2,sec); }
if(GetEntry(3,1)) { if(sec<startsec || startsec==0) startsec=sec; printf("plane %d: starts from %d seconds\n",3,sec); }
printf("Earliest second is %d\n",startsec); 
cursec=startsec;

for(p=0;p<4;p++) curentry[p]=0;
for(p=0;p<4;p++) maxsecentries[p]=0;
//for(p=0;p<4;p++) secentries[p]=0;
while(cursec-startsec<seconds)
{
//printf("Filling proc buffer for sec=%d..", cursec); 
for(p=0;p<4;p++) {
secentries[p]=0;
/*
  do{
    if(GetEntry(p,curentry[p])<=0) break ;
    if(sec==0) continue; //skip some bad events
    printf("plane %d, cursec =%d, sec=%d\n",p,cursec,sec);
    if(sec>cursec) break;
    if(ev1.ts1==0 || ev2.ts1==0 || sec<cursec) {curentry[p]++; continue;} // ts1==0 represent TS1 ref events
    if (secentries[p]>MAXHPS-1) {curentry[p]++; continue;}    //Skip events not fitting to buffer
    p_entry[p][secentries[p]]=curentry[p]; //record tree entry
    p_time[p][secentries[p]]=getHitT(ev1.mac5, max1_nch,  ev1.ts0, ev2.mac5, max2_nch,  ev2.ts0);
//(ev1.ts0+Dts[ev1.mac5]+ev2.ts0+Dts[ev2.mac5])/2; //record hit mean time
    p_time_ts1[p][curentry[p]]=getHitT(ev1.mac5, max1_nch,  ev1.ts1, ev2.mac5, max2_nch,  ev2.ts1);
//(ev1.ts1+Dts[ev1.mac5]+ev2.ts1+Dts[ev2.mac5])/2; //record hit mean time in ts1 scale
 //   printf("plane %d cursec=%d sec=%d ns1=%d ns2=%d <ns>=%d\n",p,cursec,sec,ev1.ts0,ev2.ts0, p_time[p][secentries[p]]);
    secentries[p]++;
    curentry[p]++;
  } while(sec==cursec);
*/
//  if(secentries[p] > maxsecentries[p]) {
//      maxsecentries[p]=secentries[p];
 //     printf("New Max: Sec %ld entries %d, %d, %d, %d\n",cursec,maxsecentries[0],maxsecentries[1],maxsecentries[2],maxsecentries[3]);
  //}
printf("Going backward in buffer for 2s..\n");
  do{ //going backward in time 2 s or 
    if(curentry[p]<=0) break;
    if(GetEntry(p,curentry[p])<=0) break ;    
    if(sec==0) { curentry[p]--; continue;} //skip some bad events
    curentry[p]--;    
    } while (cursec-sec<=2);

printf("Going forward in buffer for 4 s..\n");
  do{ //going forward in time 4s
//    if(curentry[p]<=0) break;
    if(GetEntry(p,curentry[p])<=0) break ;    
    if(sec==0) { curentry[p]++; continue;} //skip some bad events
    if(sec!=cursec) { curentry[p]++; continue;}
    if (secentries[p]>MAXHPS-1)  { curentry[p]++; continue;}   //Skip events not fitting to buffer
  //  printf("plane %d, cursec =%d, sec=%d\n",p,cursec,sec);
    p_entry[p][secentries[p]]=curentry[p]; //record tree entry
    p_time[p][secentries[p]]=getHitT(ev1.mac5, max1_nch,  ev1.ts0, ev2.mac5, max2_nch,  ev2.ts0);
    p_time_ts1[p][curentry[p]]=getHitT(ev1.mac5, max1_nch,  ev1.ts1, ev2.mac5, max2_nch,  ev2.ts1);
    secentries[p]++;
    curentry[p]++;    
    } while (sec-cursec<=2);
}
if(secentries[0]+secentries[1]+secentries[2]+secentries[3] >0 )
            printf("Done filling: %d %d %d %d\n", secentries[0],secentries[1],secentries[2],secentries[3]); 
//// Process 1s buffers
prsinsec=0;
 mdt=0;edt=0;mts1=0;ets1=0;medep=0;tedep=0; nxyhits=0;curedep=0; curts0=-1;


if(secentries[0]+secentries[1]+secentries[2]+secentries[3] ==0 ) {cursec++; continue;}
printf("Processing buffer for sec=%d..\n", cursec); 
for(int pl1=0;pl1<3;pl1++) for(int pl2=pl1+1;pl2<4;pl2++) //loop on plane pairs
for( int pi1=0;pi1<secentries[pl1]; pi1++)  //loop on indices-pairs in a given plane pair
for( int pi2=pi1;pi2<secentries[pl2]; pi2++)
  {
   dt=p_time[pl1][pi1]-p_time[pl2][pi2];
   if(abs(dt)>MAXDT) continue;
   //pair is found, fill up results
   printf("Pair: planes %d-%d, entries %ld,%ld, dt=%lf\n",pl1,pl2,p_entry[pl1][pi1],p_entry[pl2][pi2],dt); 
    printf("p_time1 %d p_time2 %d\n",p_time[pl1][pi1],p_time[pl2][pi2]); 
 //  GetEntry(pl1,secentries[pl1]);
 //    fChain[pl1]->Show(p_entry[pl1][pi1]); 
 //  GetEntry(p21,secentries[pl2]); 
 //    fChain[pl2]->Show(p_entry[pl2][pi2]);
     p_used[pl1][p_entry[pl1][pi1]]++;
     p_used[pl2][p_entry[pl2][pi2]]++;
     p_tof[pl1][p_entry[pl1][pi1]]=dt;
     p_tof[pl2][p_entry[pl2][pi2]]=dt;

     fChain[pl1]->GetEntry(p_entry[pl1][pi1]);

     outev1.mac5=ev1.mac5;
     outev1.flags=ev1.flags;
//     outev1.ts0=ev1.ts0+Dts[ev1.mac5];
//     outev1.ts1=ev1.ts1+Dts[ev1.mac5];
     outev1.ts0=getHitT1(ev1.mac5, max1_nch,  ev1.ts0, ev2.mac5, max2_nch,  ev2.ts0);
     outev1.ts1=getHitT1(ev1.mac5, max1_nch,  ev1.ts1, ev2.mac5, max2_nch,  ev2.ts1);
     memcpy(&(outev1.adc[0]),&(ev1.adc[0]),32*2);
     outev1.s=ev1.s;
     outev1.ms=ev1.ms;
     outev1.plane=pl1+1;
     outev1.maxnch=max1_nch;
     outev1.maxach=max1_ach;
     outev1.maxadc=max1_adc;

     outev2.mac5=ev2.mac5;
     outev2.flags=ev2.flags;
 //    outev2.ts0=ev2.ts0+Dts[ev2.mac5];
 //    outev2.ts1=ev2.ts1+Dts[ev2.mac5];
     outev2.ts0=getHitT2(ev1.mac5, max1_nch,  ev1.ts0, ev2.mac5, max2_nch,  ev2.ts0);
     outev2.ts1=getHitT2(ev1.mac5, max1_nch,  ev1.ts1, ev2.mac5, max2_nch,  ev2.ts1);
     memcpy(&(outev2.adc[0]),&(ev2.adc[0]),32*2);
     outev2.s=ev2.s;
     outev2.ms=ev2.ms;
     outev2.plane=pl1+1;
     outev2.maxnch=max2_nch;
     outev2.maxach=max2_ach;
     outev2.maxadc=max2_adc;

     sec1=sec;
     msec1=msec;
     ts00=getHitT(ev1.mac5, max1_nch,  ev1.ts0, ev2.mac5, max2_nch,  ev2.ts0);

     fChain[pl2]->GetEntry(p_entry[pl2][pi2]);

     outev3.mac5=ev1.mac5;
     outev3.flags=ev1.flags;
//     outev3.ts0=ev1.ts0+Dts[ev1.mac5];
//     outev3.ts1=ev1.ts1+Dts[ev1.mac5];
     outev3.ts0=getHitT1(ev1.mac5, max1_nch,  ev1.ts0, ev2.mac5, max2_nch,  ev2.ts0);
     outev3.ts1=getHitT1(ev1.mac5, max1_nch,  ev1.ts1, ev2.mac5, max2_nch,  ev2.ts1);
     ts11=getHitDT(ev1.mac5, max1_nch,  ev1.ts0, ev2.mac5, max2_nch,  ev2.ts0);
     memcpy(&(outev3.adc[0]),&(ev1.adc[0]),32*2);
     outev3.s=ev1.s;
     outev3.ms=ev1.ms;
     outev3.plane=pl2+1;
     outev3.maxnch=max1_nch;
     outev3.maxach=max1_ach;
     outev3.maxadc=max1_adc;
     

     outev4.mac5=ev2.mac5;
     outev4.flags=ev2.flags;
//     outev4.ts0=ev2.ts0+Dts[ev2.mac5];
//     outev4.ts1=ev2.ts1+Dts[ev2.mac5];
     outev4.ts0=getHitT2(ev1.mac5, max1_nch,  ev1.ts0, ev2.mac5, max2_nch,  ev2.ts0);
     outev4.ts1=getHitT2(ev1.mac5, max1_nch,  ev1.ts1, ev2.mac5, max2_nch,  ev2.ts1);
     memcpy(&(outev4.adc[0]),&(ev2.adc[0]),32*2);
     outev4.s=ev2.s;
     outev4.ms=ev2.ms;
     sec2=sec;
     msec2=msec;
     outev4.plane=pl2+1;
     outev4.maxnch=max2_nch;
     outev4.maxach=max2_ach;
     outev4.maxadc=max2_adc;


     ts11=getHitT(ev1.mac5, max1_nch,  ev1.ts0, ev2.mac5, max2_nch,  ev2.ts0);
     dt=ts11-ts00;
     outev1.nhits=0;
     curedep=0;
     for(int ai=0;ai<32;ai++) {if(outev1.adc[ai]>outev1.maxadc/2.) outev1.nhits++; curedep=curedep+outev1.adc[ai];} 
     outev2.nhits=0;
     for(int ai=0;ai<32;ai++) {if(outev2.adc[ai]>outev2.maxadc/2.) outev2.nhits++; curedep=curedep+outev2.adc[ai];} 
     outev3.nhits=0;
     for(int ai=0;ai<32;ai++) {if(outev3.adc[ai]>outev3.maxadc/2.) outev3.nhits++; curedep=curedep+outev3.adc[ai];} 
     outev4.nhits=0;
     for(int ai=0;ai<32;ai++) {if(outev4.adc[ai]>outev4.maxadc/2.) outev4.nhits++; curedep=curedep+outev4.adc[ai];} 

     ft4->Fill();
     
     prsinsec++;
 
     if(curts0==-1) { //init xy hits count for event summary
       mdt=ts11-ts00; edt=0; 
       mts1=(outev1.ts1+outev2.ts1+outev3.ts1+outev4.ts1)/4.;ets1=0;
       curts0=outev1.ts0/4+outev2.ts0/4+outev3.ts0/4+outev4.ts0/4;
       medep=curedep; tedep=curedep; nxyhits=1;
       firsthitentry=ft4->GetEntriesFast()-1;
       printf("P1: mts1=%lf; curts0 %d outev1.ts0 %d\n",mts1, curts0, outev1.ts0);
     }
     else if(abs(curts0-outev1.ts0)<100 && abs(curts0-outev2.ts0)<100 && abs(curts0-outev3.ts0)<100 && abs(curts0-outev4.ts0)<100){ //still the same event
      mdt=mdt+ts11-ts00;
      mts1=mts1+((outev1.ts1+outev2.ts1+outev3.ts1+outev4.ts1)/4.);
      medep=medep+curedep; tedep=tedep+curedep; nxyhits++;
       printf("P2: mts1=%lf mts1/nxyhits=%lf; curts0 %d outev1.ts0 %d\n",mts1,1.*mts1/nxyhits, curts0, outev1.ts0);
     }
     else { //next event started
       //calc mean values for previous event
       mdt=mdt/nxyhits;
       mts1=mts1/nxyhits;
       medep=medep/nxyhits;
       ftev->Fill();
       curts0=outev1.ts0/4+outev2.ts0/4+outev3.ts0/4+outev4.ts0/4;
       mdt=ts11-ts00; edt=0; 
       mts1=(outev1.ts1+outev2.ts1+outev3.ts1+outev4.ts1)/4.;ets1=0;
       medep=curedep; tedep=curedep; nxyhits=1;
       firsthitentry=ft4->GetEntriesFast()-1;
       printf("P3: mts1=%lf mts1/nxyhits=%lf; curts0 %d outev1.ts0 %d\n",mts1,1.*mts1/nxyhits, curts0, outev1.ts0);
     }        

  }

if(prsinsec>0)
{
       mdt=mdt/nxyhits;
       mts1=mts1/nxyhits;
       medep=medep/nxyhits;
       ftev->Fill();
       printf("P4 (end of buffer loop): mts1=%d  curts0 %d outev1.ts0 %d prsinsec=%d\n",mts1, curts0, outev1.ts0,prsinsec);
      if(mdt==-32) printf("That one! -----------------------------------\n");
}

//if(secentries[0]+secentries[1]+secentries[2]+secentries[3]>0)
if(prsinsec>0)
printf("Done processing,sursec=%d buffers %d %d %d %d => %d pairs.\n",cursec,secentries[0],secentries[1],secentries[2],secentries[3],prsinsec); 
cursec++;

//outFile->cd();
//ft4->Write("t4",TObject::kOverwrite);
//outFile->Write();

}//end while on seconds
printf("End while on seconds.\n");

//loop on all entries and produce friend trees



Int_t used, hitts1, tmult;
Double_t tof;
for(int pl1=0; pl1<4; pl1++)
       {
        ffr[pl1] = new TTree("t2","Hits usage branch");
        ffr[pl1]->Branch("used", &used, "used/I"); //mean dt
        ffr[pl1]->Branch("ts1", &hitts1, "ts1/I"); //ts1
        ffr[pl1]->Branch("tof", &tof, "tof/D"); //TOF in case of used>0
        ffr[pl1]->Branch("tmult", &tmult, "tmult/I"); //total multiplicity X+Y planes
       }

for(int pl1=0; pl1<4; pl1++) if(fChain[pl1]>0) for(int pe=0; pe<fChain[pl1]->GetEntries(); pe++)
{
fChain[pl1]->GetEntry(pe);
used=p_used[pl1][pe];
hitts1=p_time_ts1[pl1][pe];
tof=p_tof[pl1][pe];
tmult=0;
for(int ai=0;ai<32;ai++) {if(ev1.adc[ai]>max1_adc/2.) tmult++; } 
for(int ai=0;ai<32;ai++) {if(ev2.adc[ai]>max2_adc/2.) tmult++; } 

ffr[pl1]->Fill();
}

printf("Saving results..\n");
outFile->cd();

ft4->Write("t4");
ffr[0]->Write("t2_crt1");
ffr[1]->Write("t2_crt2");
ffr[2]->Write("t2_crt3");
ffr[3]->Write("t2_crt4");


ftev->Write("tev");
outFile->Close();
}
