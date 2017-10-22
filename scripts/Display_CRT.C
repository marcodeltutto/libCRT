#define EVLEN 80
CRTRawhit *hit;
CRTEvent *evt;
CRT2Dhit *e2d;
CRTRawhitBuffer *rhbuf;
CRTDisplay*  ds;
CRTCalibs*  cal;
CRTRun * run;
char buf[EVLEN];
Int_t curev=0;



void ShowEntry(Int_t en) {ds->ShowRunEvents(en,en);gSystem->ProcessEvents();}

void Next( Bool_t ShowADC=kFALSE){ if(curev < run->rheader->N-1) {curev++; ds->ShowRunEvents(curev,curev,ShowADC);gSystem->ProcessEvents();}}
void Prev( Bool_t ShowADC=kFALSE){ if(curev >0) {curev--; ds->ShowRunEvents(curev,curev,ShowADC);gSystem->ProcessEvents();}}



void Display_CRT(const char *fname="", Bool_t ShowADC=kFALSE)
{
  ds=new CRTDisplay(); //has to be called before opening the run!!
//  ds->SetVerb(4);
  ds->SetVerb(0);
  run=new CRTRun();
  if(strlen(fname)==0) {printf("No input file name is given.\n");return;};
  if(run->OpenExistingDataRun(fname)==0){printf("Extracting CRTRun object is failed.\n");return;};
  ds->SetRun(run);
  int evsread=0;
  int EndOfFile=0;
  int hitsinev=0;
  ds->GetEve()->SetStatusLine(fname);
  ds->ShowRunEvents(0,10,ShowADC);
  ds->Refresh();

}




