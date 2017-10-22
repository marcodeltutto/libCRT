//////////////////////////////////////////////////////////
//   This class merges up to four CoincScale pair trees  (Bot, sides, top)into global hit coinc tree.
//////////////////////////////////////////////////////////

#ifndef Merger_h
#define Merger_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <unistd.h>

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
		UShort_t mac5;
		UShort_t flags;
   UShort_t       lost1;
   UShort_t       lost2;
		Int_t ts0;
		Int_t ts1;
		UShort_t adc[32];
		Int_t s;
		Int_t ms;
} RAWEVENT_t;


// Header file for the classes stored in the TTree if any.


// Fixed size dimensions of array or collections stored in the TTree if any.

class Merger {
public :
   TTree          *fChain[4];   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

  
   // Declaration of leaf types
   RAWEVENT_t      ev1;
   RAWEVENT_t      ev2;
   Int_t           delta12;
   Int_t           deltai;
   UInt_t          max1_adc;
   UInt_t          max2_adc;
   UInt_t          max1_ach;
   UInt_t          max2_ach;
   UInt_t          max1_nch;
   UInt_t          max2_nch;
   Int_t           sec;
   Int_t           msec;


   Int_t           sec1;
   Int_t           msec1;
   Int_t           sec2;
   Int_t           msec2;
 //  Int_t           dt;
   Int_t           plane1,plane2;

Int_t Exists[200];
Double_t Dts[200];
Double_t Xs[200][32];
Double_t Ys[200][32];
Double_t Zs[200][32];



 //  Merger(char *fn1, char *fn2, int seconds=10);
           Merger(char *fn1, char *fn2, char *fn3, char *fn4);
   virtual ~Merger();
   virtual Int_t    GetEntry(int p=0, Long64_t entry=0);
   virtual void     Init();
   virtual void     Loop(int seconds=10);
   virtual void     Show(Long64_t entry = -1);
   virtual Double_t getHitT1(int mac1, int strip1,  int t1, int mac2, int strip2, int t2);
   virtual Double_t getHitT2(int mac1, int strip1,  int t1, int mac2, int strip2, int t2);
   virtual Double_t getHitT(int mac1, int strip1,  int t1, int mac2, int strip2, int t2);
   virtual Double_t getHitDT(int mac1, int strip1,  int t1, int mac2, int strip2, int t2);

};

#endif




#ifdef Merger_cxx
Merger::Merger(char *fn1, char *fn2, char *fn3, char *fn4) 
{
int numfiles=0;
TFile *f1=0;TFile *f2=0;TFile *f3=0;TFile *f4=0;
      fChain[0]=0;
      if(strlen(fn1)>0) f1 = new TFile(fn1);
      if(f1!=0) fChain[0]=(TTree*)f1->Get("t2");
      if(fChain[0]) printf("Opened hit tree from %s.\n",fn1); 
      fChain[1]=0;
      if(strlen(fn2)>0) f2 = new TFile(fn2);
      if(f2!=0) fChain[1]=(TTree*)f2->Get("t2");
      if(fChain[1]) printf("Opened hit tree from %s.\n",fn2); 
      fChain[2]=0;
//      printf("1\n");
      if(strlen(fn3)>0) f3 = new TFile(fn3);
 //     printf("2\n");
      if(f3!=0) fChain[2]=(TTree*)f3->Get("t2");
 //     printf("3\n");
      if(fChain[2]) printf("Opened hit tree from %s.\n",fn3); 
      fChain[3]=0;
      if(strlen(fn4)>0) f4 = new TFile(fn4);
      if(f4!=0) fChain[3]=(TTree*)f4->Get("t2");
      if(fChain[3]) printf("Opened hit tree from %s.\n",fn4); 
      
numfiles=(fChain[0]!=0) + (fChain[1]!=0) + (fChain[2]!=0) + (fChain[3]!=0);
  if(numfiles>1) { Init();}
  else {printf("Opened %d<2 trees. Not enough to proceed.\n",numfiles); return;}

 Double_t x, y, z;
 Int_t id;
 Int_t pl,ch,a,b,c1;
   printf("Initializing geometry tables from  CRTpositionsSiPM-V8.txt\n");
  for(int m=0;m<200;m++) for(int c=0;c<32;c++) {Xs[m][c]=0;Ys[m][c]=0;Zs[m][c]=0;Dts[m]=0;Exists[m]=0;} 
  std::ifstream in;
  in.open("CRTpositionsSiPM-V8.txt");
//  in.open("SBND_CRTpositionsSiPM-nogaps.txt");
  while (!in.eof()) {
    in>>id>>x>>y>>z>>a>>b>>c1;
    pl=id/100; ch=(id-100*int(pl));
    Xs[pl][ch]=x;
    Ys[pl][ch]=y;
    Zs[pl][ch]=z;
  }      
  in.close();


    printf("Initializing cable delays from  FEB_CableDelay-V8.txt\n");
    Double_t dti;
    std::ifstream in1;
  in1.open("FEB_CableDelay-V8.txt");
  while (!in1.eof()) {
    in1>>pl>>dti;
    Dts[pl]=dti;
    Exists[pl]=1;
  }      
  in1.close();



}

Merger::~Merger()
{
  
   if(fChain[0]) delete fChain[0]->GetCurrentFile();
   if(fChain[1]) delete fChain[1]->GetCurrentFile();
   if(fChain[2]) delete fChain[2]->GetCurrentFile();
   if(fChain[3]) delete fChain[3]->GetCurrentFile();
}

Int_t Merger::GetEntry(int plane, Long64_t entry)
{
// Read contents of entry.
   if(plane>3) return 0;
   if (!fChain[plane]) return 0;
   return fChain[plane]->GetEntry(entry);
}


void Merger::Init()
{
   printf("Initializing trees branches.\n");
   // Set branch addresses and branch pointers
   fCurrent = -1;
for(int plane=0;plane<4;plane++) if( fChain[plane]!=0)
{
   fChain[plane]->SetMakeClass(1);
   fChain[plane]->SetBranchAddress("event1", &ev2);
   fChain[plane]->SetBranchAddress("event2", &ev1);
   fChain[plane]->SetBranchAddress("delta12", &delta12);
   fChain[plane]->SetBranchAddress("deltai", &deltai);
   fChain[plane]->SetBranchAddress("max1_adc", &max2_adc);
   fChain[plane]->SetBranchAddress("max2_adc", &max1_adc);
   fChain[plane]->SetBranchAddress("max1_ach", &max2_ach);
   fChain[plane]->SetBranchAddress("max2_ach", &max1_ach);
   fChain[plane]->SetBranchAddress("max1_nch", &max2_nch);
   fChain[plane]->SetBranchAddress("max2_nch", &max1_nch);
   fChain[plane]->SetBranchAddress("sec", &sec);
   fChain[plane]->SetBranchAddress("msec", &msec);
}

   

}


void Merger::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry

for(int plane=0;plane<4;plane++) if (fChain[plane]!=0) fChain[plane]->Show(entry);
 
}

#endif // #ifdef Merger_cxx
