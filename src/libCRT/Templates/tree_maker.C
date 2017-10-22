///////////////////////////////////////////////////////////////////////////////////////////////////////
//    This program rewrittes stored raw data in a root tree
//    Note: it generates tx trees with x events in it
//    It works for singles and pairs
//    Written by Thomas Mettler
///////////////////////////////////////////////////////////////////////////////////////////////////////

#include <TH2.h>
#include <TH1F.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TFile.h>
#include <time.h>
#include <unistd.h>

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
		uint16_t mac5;
		uint16_t flags;
    uint16_t lostcpu;
    uint16_t lostfpga;
		uint32_t ts0;
		int32_t ts1;
		uint16_t adc[32];
		uint32_t s;
    uint32_t ms;
} one_event;

typedef struct {
		uint16_t mac5;
		uint16_t flags;
    uint16_t lostcpu;
    uint16_t lostfpga;
		uint32_t ts0;
		uint32_t ts1;
		uint16_t adc[32];
    int s;
    int ms;
    uint16_t recover;
    uint32_t nrtrigger;
    uint32_t nrtrigger_11;
} EVENT_t;

typedef struct {
		uint16_t mac5;
		uint16_t flags;
    uint16_t lostcpu;
    uint16_t lostfpga;
		uint32_t ts0;
		uint32_t ts1;
		uint16_t adc[32];
} EVENT_traw;

typedef struct {
		uint16_t mac5;
		uint16_t flags;
    uint16_t lostcpu;
    uint16_t lostfpga;
		uint32_t ts0;
		uint32_t ts1;
		uint16_t adc[32];
    //int s;
    //int ms;
    //int nrtrack;
    //int XY;
    //double tof;
    //int nhit;
    uint16_t recover;
    uint32_t nrtrigger;
    uint32_t nrtrigger_11;
} EVENT_t_pac;


EVENT_t_pac evbuf[5];
long size_ev=0;
TTree *t1;
TTree *t2;

long ev_counter=0;

int delta12, deltai;
int max1_ach=0, max2_ach=0, max1_nch, max2_nch;
int max3_ach=0, max4_ach=0, max3_nch, max4_nch, max5_ach, max5_nch;
int ch[16];
int max1_adc=0, max2_adc=0;
int max3_adc=0, max4_adc=0, max5_adc=0;
int tmp1, tmp2,tmp3,tmp4, tmp5;
int sec, msec;
int n1=0, n2=0, n3=0, n4=0, n5=0;
int nrwm1, nrwm01;
int nrwm2, nrwm02;
one_event event1, event2, event3, event4, event5;
int XY=0, track=0;

#define EVENTLEN 92
int fill_single();
int fill_pair();

void tree_maker(char* filename, int event_size){
  int MAXEV=10000;
  FILE *data = 0;
  FILE *text = 0; 
  
  data=fopen(filename,"r");
  char filename2[120];
  strcpy(filename2, filename);
  strcat(filename2, ".root");
  TFile f(filename2,"RECREATE");
  //printf(filename);
  //printf("\n \n");
  //TFile f("ProdRun20170101_011005-crt04.1.pairs.root","RECREATE");
  
  //data = fopen("/home/thmettler/Desktop/MuTOF/atCERN/cern1.bin","r");	
  fseek(data, 0, SEEK_END); // seek to end of file
  long size = ftell(data); // get current file pointer
  fseek(data, 0, SEEK_SET); // seek back to beginning of file

  size_ev=size/sizeof(EVENT_t_pac);		//=198957 events
  printf("Total Number of events: %ld\nWritting data to text...(%ld), set: %d \n",size_ev,sizeof(EVENT_t_pac), 92);

  t1 = new TTree("t1","Single");
  t2 = new TTree("t2","Pairs");

  //initalize the variavles
  t1->Branch("event1",&event1,"mac5/s:flags/s:lost1/s:lost2/s:ts0/I:ts1/I:adc[32]/s:s/I:ms/I");
	t1->Branch("nrwm1", &nrwm1, "nrwm1/i");
  t1->Branch("nrwm01", &nrwm01, "nrwm01/i");
  t1->Branch("max1_adc",&max1_adc,"max1_adc/s");//+max+index of max
  t1->Branch("max1_ach", &max1_ach, "max1_ach/i");
  t1->Branch("max1_nch", &max1_nch, "max1_nch/i");
  t1->Branch("nhits1",&n1,"nhits1/i");

  t2->Branch("event1",&event1,"mac5/s:flags/s:lost1/s:lost2/s:ts0/I:ts1/I:adc[32]/s:s/I:ms/I");
	t2->Branch("event2",&event2,"mac5/s:flags/s:lost1/s:lost2/s:ts0/I:ts1/I:adc[32]/s:s/I:ms/I");
	t2->Branch("delta12", &delta12, "delta12/I");
	t2->Branch("deltai", &deltai, "deltai/I");
	t2->Branch("max1_adc", &max1_adc, "max1_adc/i");
	t2->Branch("max2_adc", &max2_adc, "max2_adc/i");
	t2->Branch("max1_ach", &max1_ach, "max1_ach/i");
	t2->Branch("max2_ach", &max2_ach, "max2_ach/i");
	t2->Branch("max1_nch", &max1_nch, "max1_nch/i");
	t2->Branch("max2_nch", &max2_nch, "max2_nch/i");
	t2->Branch("nhits1", &n1, "nhits1/i");
	t2->Branch("nhits2", &n1, "nhits2/i");
	t2->Branch("nrwm1", &nrwm1, "nrwm1/i");
	t2->Branch("nrwm2", &nrwm2, "nrwm2/i");
  t2->Branch("nrwm01", &nrwm01, "nrwm01/i");
  t2->Branch("nrwm02", &nrwm02, "nrwm02/i");
  t2->Branch("sec", &sec, "sec/I");
  t2->Branch("msec", &msec, "msec/I");
  //t2->Branch("sec",&sec,"sec/i");
  //t2->Branch("msec",&msec,"msec/i");
  //t2->Branch("track",&track,"track/i");
  //t2->Branch("XY",&XY,"XY/i");

  //going into the loop over all hits and make an event of 2
  int EndOfFile=0;
  long counter_old=0;
  
  if(event_size==2){
    while(!EndOfFile){
      //if(ev_counter>MAXEV){EndOfFile=1; break;}
      if((ev_counter-counter_old)>1000){
        printf("\r writting event: %ld/%ld  (%ld%%)",ev_counter, size_ev, 100*ev_counter/size_ev);
        counter_old=ev_counter;
      }
      for (int counter=0; counter < event_size+1; counter++)
        {
          if(fread(&evbuf[counter],EVENTLEN,1,data)<=0){EndOfFile=1; break;}
        }
      fill_pair();
    }
  }
  
  if(event_size==1){
    while(!EndOfFile){
      //if(ev_counter>MAXEV){EndOfFile=1; break;}
      if((ev_counter-counter_old)>1000){
        printf("\r writting event: %ld/%ld  (%ld%%)",ev_counter, size_ev, 100*ev_counter/size_ev);
        counter_old=ev_counter;
      }
      for (int counter=0; counter < event_size; counter++)
        {
         if(fread(&evbuf[counter],EVENTLEN,1,data)<=0){EndOfFile=1; break;}
          //if(ev_counter>10000){EndOfFile=1; break;}
          counter=fill_single();
      }
    }
  }
  printf("\n");
  t1->Write("t1",TObject::kOverwrite);
  t2->Write("t2",TObject::kOverwrite);
  f.Close();
  fclose(data);
  printf("finished\n");
  //fclose(text);
}
int fill_single(){
  event1.mac5=evbuf[0].mac5;
  event1.flags=evbuf[0].flags;
  event1.ts0=evbuf[0].ts0;
  if(evbuf[0].ts1>4e9){ event1.ts1=-(evbuf[0].ts1-4e9);}
  else event1.ts1=evbuf[0].ts1;
  event1.lostcpu=evbuf[0].lostcpu;
  event1.lostfpga=evbuf[0].lostfpga;
  for(int i=0;i<32;i++) event1.adc[i]=evbuf[0].adc[i];
  event1.s=0;
  event1.ms=0;

  nrwm1=evbuf[0].nrtrigger;
  nrwm01=evbuf[0].nrtrigger_11;

  max1_adc=0;
  max1_ach=0;
  n1=0;

  for(int j=0;j<16;j++){ //set max_ach + max__nch
    ch[j]=0;
    ch[j]=evbuf[0].adc[j*2]+evbuf[0].adc[j*2+1];
    if(ch[j]>max1_ach) {max1_ach=ch[j]; max1_nch=j;}
  }

  for(int j=0;j<32;j++){  //set max_adc
    tmp1=evbuf[0].adc[j];
    if(tmp1>max1_adc) max1_adc=tmp1;
  }
  for(int j=0;j<16;j++){
    ch[j]=0;
    ch[j]=evbuf[0].adc[j*2]+evbuf[0].adc[j*2+1];
    if(ch[j]>(max1_ach/2)) {n1++;}
  }
  t1->Fill();
  ev_counter+=1;
 return 2; 
}
  
int fill_pair(){
	if(evbuf[1].mac5<evbuf[0].mac5){
		evbuf[3]=evbuf[1];
		evbuf[1]=evbuf[0];
		evbuf[0]=evbuf[3];
	}
	
  event1.mac5=evbuf[0].mac5;
  event1.flags=evbuf[0].flags;
  event1.ts0=evbuf[0].ts0;
  if(evbuf[0].ts1>4e9){ event1.ts1=-(evbuf[0].ts1-4e9);}
  else event1.ts1=evbuf[0].ts1;
         printf("t1=%d t1=%d\n",evbuf[0].ts1,event1.ts1); 
  event1.lostcpu=evbuf[0].lostcpu;
  event1.lostfpga=evbuf[0].lostfpga;
  for(int i=0;i<32;i++) event1.adc[i]=evbuf[0].adc[i];
  event1.s=evbuf[2].ts0;
  event1.ms=evbuf[2].adc[0];
  
  event2.mac5=evbuf[1].mac5;
  event2.flags=evbuf[1].flags;
  event2.ts0=evbuf[1].ts0;
  if(evbuf[1].ts1>4e9){ event2.ts1=-(evbuf[1].ts1-4e9);}
  else event2.ts1=evbuf[1].ts1;
  event2.lostcpu=evbuf[1].lostcpu;
  event2.lostfpga=evbuf[1].lostfpga;
  for(int i=0;i<32;i++) event2.adc[i]=evbuf[1].adc[i];
  event2.s=evbuf[2].ts1;
  event2.ms=evbuf[2].adc[1];
    
  delta12=evbuf[0].ts0-evbuf[1].ts0;
  deltai=evbuf[2].recover;
    
    max1_adc=0, max2_adc=0;
    max1_ach=0, max2_ach=0;
    n1=0, n2=0;

    for(int j=0;j<16;j++){ //set max_ach + max__nch
      ch[j]=0;
      ch[j]=evbuf[0].adc[j*2]+evbuf[0].adc[j*2+1];
      if(ch[j]>max1_ach) {max1_ach=ch[j]; max1_nch=j;}
      ch[j]=0;
      ch[j]=evbuf[1].adc[j*2]+evbuf[1].adc[j*2+1];
      if(ch[j]>max2_ach) {max2_ach=ch[j]; max2_nch=j;}
    }
    
    for(int j=0;j<32;j++){  //set max_adc
      tmp1=evbuf[0].adc[j];
      tmp2=evbuf[1].adc[j];
      if(tmp1>max1_adc) max1_adc=tmp1;
      if(tmp2>max2_adc) max2_adc=tmp2;
    }
    for(int j=0;j<16;j++){
      ch[j]=0;
      ch[j]=evbuf[0].adc[j*2]+evbuf[0].adc[j*2+1];
      if(ch[j]>(max1_ach/2)) {n1++;}
      ch[j]=0;
      ch[j]=evbuf[1].adc[j*2]+evbuf[1].adc[j*2+1];
      if(ch[j]>(max2_ach/2)) {n2++;}
    }
  
  nrwm1=evbuf[0].nrtrigger;
  nrwm2=evbuf[1].nrtrigger;
  nrwm01=evbuf[0].nrtrigger_11;
  nrwm02=evbuf[1].nrtrigger_11;
  
  sec=evbuf[2].ts0;
  msec=evbuf[2].adc[0];

    t2->Fill();
    ev_counter+=2;
  
 return 6; 
}
