
CRTRawhit *hit;
CRTRun * run;
FILE *data = 0;

#define EVENTLEN 92  //Thomas pair event has 92 bytes

char buf[EVENTLEN]; 
char ofname[256];
Int_t sec=0;
Int_t msec=0;
void ConvertTrigsToRun(char *fname="")
{
  if(strlen(fname)==0) return;
  rhbuf=new CRTRawhitBuffer();
  run=new CRTRun();
  sprintf(ofname,"%s.root",fname);
  run->CreateNewDataRun(ofname);
//  run->CreateNewDataRun("test.root");
  hit=new CRTRawhit(); 
//  cal=new CRTCalibs("FEB_CableDelay-V8.txt","CRTpositionsSiPM-V8.txt","AdcCalibration-V4.txt");
//  cal->SetVersion(8);
//  run->SetCalibs(cal); 
  int evsread=0;
  data = fopen(fname,"r");
  if(data<=0) return;	
  else printf("Opened triggers raw data file %s.\n",fname);
  int EndOfFile=0;
  int hitsinev=0;

  while(!EndOfFile)
 // while(evsread<200)
     {  
      if(fread(buf,EVENTLEN,1,data)<=0) {EndOfFile=1; break;};
      hit->ReadFromBuffer(buf);
    //  hit->Print(4);
      if(hit->mac5==0) { printf("mac5=0, skipping event!\n"); continue; }
      evsread++;
      hitsinev++;
      if(!hit->IsEOPEvent()) rhbuf->AddRawhit(hit);
      else 
      { 
       // hit->Print(4);
        sec=hit->ts0; 
        msec=hit->ts1; 
        if(sec==0) { printf("Special event: sec=0, skipping buffer!\n"); rhbuf->Clear(); continue; }
        for(int i=0; i<rhbuf->Nhits; i++)   
        { 
                    ((CRTRawhit*)(rhbuf->hits->At(i)))->s=sec;
                    ((CRTRawhit*)(rhbuf->hits->At(i)))->ms=msec;
        }
        run->AddRawhitBuffer(rhbuf); rhbuf->Clear();
      } 
 //     run->AddRawhit(hit); run->Fill();run->ClearEntry();
      
      if(hitsinev%10000==0) printf("%d events processed..\n",evsread);
      
     }
  run->BuildIndex("h.s","int(h.ts0)");
 run->PrintSummary();
 run->Close();
}




