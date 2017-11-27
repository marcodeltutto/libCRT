CRTRawhit *hit;
CRTEvent *evt;
CRT2Dhit *e2d;
CRTRawhitBuffer *rhbuf;
CRTCalibs*  cal;
CRTRun * run;
CRTRun * run1;
CRTRun * run2;
CRTReco *reco;


void TPCMatch(const char *fncrt="",const char *fntpc="",const char *ofname="")
{
  reco=new CRTReco();
  run=new CRTRun();
  if(strlen(fncrt)==0) {printf("CRT data: No input file name is given.\n");return;};
  if(strlen(fntpc)==0) {printf("TPC data: No input file name is given.\n");return;};
  if(strlen(ofname)==0) {printf("No output file name is given.\n");return;};
  reco->MatchFlashestoCRT(fncrt, fntpc, ofname,700);
  
}




