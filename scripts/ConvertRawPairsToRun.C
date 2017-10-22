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

EVENT_t_pac evbufr[4];

CRTRawhit evbuf[4];
//CRTRawhit *hit2;
//CRTRawhit *hit3;
CRT2Dhit *h2d;
CRTRun * run;
FILE *data = 0;
//char buf[EVLEN]; //EVLEN is defined in libCRT headers
#define EVENTLEN 92  //Thomas pair event has 92 bytes


char buf[EVENTLEN]; 
char ofname[256];
Int_t sec=0;
int32_t tts1;
void ConvertRawPairsToRun(const char *fname="")
{
  if(strlen(fname)==0) return;
  rhbuf=new CRTRawhitBuffer();
  run=new CRTRun();
  sprintf(ofname,"%s.libcrt.root",fname);
  run->CreateNewDataRun(ofname);
  hit=new CRTRawhit(); 
  cal=new CRTCalibs("FEB_CableDelay-V8.txt","CRTpositionsSiPM-V8.txt","AdcCalibration-V4.txt");
  cal->SetVersion(8);
  run->SetCalibs(cal); 
  int evsread=0;
  data = fopen(fname,"r");
  if(data<=0) return;	
  else printf("Opened raw data file %s.\n",fname);
  int EndOfFile=0;
  int hitsinev=0;

  while(!EndOfFile)
 // while(evsread<20000)
     {  
      if(fread(&(evbufr[0]),EVENTLEN,1,data)<=0) {EndOfFile=1; break;};
      if(fread(&(evbufr[1]),EVENTLEN,1,data)<=0) {EndOfFile=1; break;};
      if(fread(&(evbufr[2]),EVENTLEN,1,data)<=0) {EndOfFile=1; break;};

      for(int i=0;i<3;i++)
       {
         evbuf[i].mac5=evbufr[i].mac5;
         evbuf[i].flags=evbufr[i].flags;
         evbuf[i].lostcpu=evbufr[i].lostcpu;
         evbuf[i].lostfpga=evbufr[i].lostfpga;
         evbuf[i].ts0=evbufr[i].ts0;
 
  if(evbufr[i].ts1>4e9){ evbuf[i].ts1=-(evbufr[i].ts1-4e9);}  
  else evbuf[i].ts1=evbufr[i].ts1;
//        printf("t1=%d t1=%d\n",evbufr[i].ts1,evbuf[i].ts1); 

         memcpy(&(evbuf[i].adc[0]),&(evbufr[i].adc[0]),32*2);
       }

      evsread++;
      hitsinev++;

       	if(evbuf[1].mac5<evbuf[0].mac5){
		evbuf[3].Copy(&(evbuf[1]));
		evbuf[1].Copy(&(evbuf[0]));
		evbuf[0].Copy(&(evbuf[3]));
	}

      evbuf[0].s=evbuf[2].ts0;
      evbuf[0].ms=evbuf[2].adc[0];
      evbuf[1].s=evbuf[2].ts1;
      evbuf[1].ms=evbuf[2].adc[1];
      
       
      h2d=new CRT2Dhit(&(evbuf[0]),&(evbuf[1]),cal);
      run->Add2Dhit(h2d);
      if(evbufr[0].nrtrigger>run->rheader->Nt1refs[evbufr[0].mac5]) run->rheader->Nt1refs[evbufr[0].mac5]=evbufr[0].nrtrigger;
      if(evbufr[1].nrtrigger>run->rheader->Nt1refs[evbufr[1].mac5]) run->rheader->Nt1refs[evbufr[1].mac5]=evbufr[1].nrtrigger;
      if(evbufr[0].nrtrigger_11>run->rheader->Nt0refs[evbufr[0].mac5]) run->rheader->Nt0refs[evbufr[0].mac5]=evbufr[0].nrtrigger_11;
      if(evbufr[1].nrtrigger_11>run->rheader->Nt0refs[evbufr[1].mac5]) run->rheader->Nt0refs[evbufr[1].mac5]=evbufr[1].nrtrigger_11;
      run->Fill();
      run->ClearEntry();
      if(hitsinev%1000==0) printf("%d events processed..\n",evsread);
     }
 run->BuildIndex("h2d.s","int(h2d.t0)");
 run->PrintSummary();
 run->Close();
}

/*
{
  std::cout<< "Entries:" <<  ptree->GetEntries()<< std::endl;
  ptree->BuildIndex("time");
  TTreeIndex *I=(TTreeIndex*)ptree->GetTreeIndex(); // get the tree index
  Long64_t* index=I->GetIndex(); //create an array of entries in sorted order
  TLeaf* time=ptree->GetBranch("event")->GetLeaf("time");
  for (int i=0;i<ptree->GetEntries();i++){
    ptree->GetEntry(index[i]); 
    std::cout <<time->GetValue() << std::endl; //print the (hopefully sorted) time
  }
}
*/



