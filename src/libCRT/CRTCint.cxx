// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME CRTCint

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "CRTEvent.h"
#include "TPCEvent.h"
#include "CRTBuffers.h"
#include "CRTDisplay.h"
#include "CRTRun.h"
#include "CRTReco.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_CRTEvent(void *p = 0);
   static void *newArray_CRTEvent(Long_t size, void *p);
   static void delete_CRTEvent(void *p);
   static void deleteArray_CRTEvent(void *p);
   static void destruct_CRTEvent(void *p);
   static void streamer_CRTEvent(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::CRTEvent*)
   {
      ::CRTEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::CRTEvent >(0);
      static ::ROOT::TGenericClassInfo 
         instance("CRTEvent", ::CRTEvent::Class_Version(), "CRTEvent.h", 35,
                  typeid(::CRTEvent), DefineBehavior(ptr, ptr),
                  &::CRTEvent::Dictionary, isa_proxy, 16,
                  sizeof(::CRTEvent) );
      instance.SetNew(&new_CRTEvent);
      instance.SetNewArray(&newArray_CRTEvent);
      instance.SetDelete(&delete_CRTEvent);
      instance.SetDeleteArray(&deleteArray_CRTEvent);
      instance.SetDestructor(&destruct_CRTEvent);
      instance.SetStreamerFunc(&streamer_CRTEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::CRTEvent*)
   {
      return GenerateInitInstanceLocal((::CRTEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::CRTEvent*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_CRTRawhit(void *p = 0);
   static void *newArray_CRTRawhit(Long_t size, void *p);
   static void delete_CRTRawhit(void *p);
   static void deleteArray_CRTRawhit(void *p);
   static void destruct_CRTRawhit(void *p);
   static void streamer_CRTRawhit(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::CRTRawhit*)
   {
      ::CRTRawhit *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::CRTRawhit >(0);
      static ::ROOT::TGenericClassInfo 
         instance("CRTRawhit", ::CRTRawhit::Class_Version(), "CRTEvent.h", 57,
                  typeid(::CRTRawhit), DefineBehavior(ptr, ptr),
                  &::CRTRawhit::Dictionary, isa_proxy, 16,
                  sizeof(::CRTRawhit) );
      instance.SetNew(&new_CRTRawhit);
      instance.SetNewArray(&newArray_CRTRawhit);
      instance.SetDelete(&delete_CRTRawhit);
      instance.SetDeleteArray(&deleteArray_CRTRawhit);
      instance.SetDestructor(&destruct_CRTRawhit);
      instance.SetStreamerFunc(&streamer_CRTRawhit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::CRTRawhit*)
   {
      return GenerateInitInstanceLocal((::CRTRawhit*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::CRTRawhit*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_CRT2Dhit(void *p = 0);
   static void *newArray_CRT2Dhit(Long_t size, void *p);
   static void delete_CRT2Dhit(void *p);
   static void deleteArray_CRT2Dhit(void *p);
   static void destruct_CRT2Dhit(void *p);
   static void streamer_CRT2Dhit(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::CRT2Dhit*)
   {
      ::CRT2Dhit *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::CRT2Dhit >(0);
      static ::ROOT::TGenericClassInfo 
         instance("CRT2Dhit", ::CRT2Dhit::Class_Version(), "CRTEvent.h", 108,
                  typeid(::CRT2Dhit), DefineBehavior(ptr, ptr),
                  &::CRT2Dhit::Dictionary, isa_proxy, 16,
                  sizeof(::CRT2Dhit) );
      instance.SetNew(&new_CRT2Dhit);
      instance.SetNewArray(&newArray_CRT2Dhit);
      instance.SetDelete(&delete_CRT2Dhit);
      instance.SetDeleteArray(&deleteArray_CRT2Dhit);
      instance.SetDestructor(&destruct_CRT2Dhit);
      instance.SetStreamerFunc(&streamer_CRT2Dhit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::CRT2Dhit*)
   {
      return GenerateInitInstanceLocal((::CRT2Dhit*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::CRT2Dhit*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_CRTTrack(void *p = 0);
   static void *newArray_CRTTrack(Long_t size, void *p);
   static void delete_CRTTrack(void *p);
   static void deleteArray_CRTTrack(void *p);
   static void destruct_CRTTrack(void *p);
   static void streamer_CRTTrack(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::CRTTrack*)
   {
      ::CRTTrack *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::CRTTrack >(0);
      static ::ROOT::TGenericClassInfo 
         instance("CRTTrack", ::CRTTrack::Class_Version(), "CRTEvent.h", 184,
                  typeid(::CRTTrack), DefineBehavior(ptr, ptr),
                  &::CRTTrack::Dictionary, isa_proxy, 16,
                  sizeof(::CRTTrack) );
      instance.SetNew(&new_CRTTrack);
      instance.SetNewArray(&newArray_CRTTrack);
      instance.SetDelete(&delete_CRTTrack);
      instance.SetDeleteArray(&deleteArray_CRTTrack);
      instance.SetDestructor(&destruct_CRTTrack);
      instance.SetStreamerFunc(&streamer_CRTTrack);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::CRTTrack*)
   {
      return GenerateInitInstanceLocal((::CRTTrack*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::CRTTrack*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_CRTCalibs(void *p = 0);
   static void *newArray_CRTCalibs(Long_t size, void *p);
   static void delete_CRTCalibs(void *p);
   static void deleteArray_CRTCalibs(void *p);
   static void destruct_CRTCalibs(void *p);
   static void streamer_CRTCalibs(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::CRTCalibs*)
   {
      ::CRTCalibs *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::CRTCalibs >(0);
      static ::ROOT::TGenericClassInfo 
         instance("CRTCalibs", ::CRTCalibs::Class_Version(), "CRTEvent.h", 140,
                  typeid(::CRTCalibs), DefineBehavior(ptr, ptr),
                  &::CRTCalibs::Dictionary, isa_proxy, 16,
                  sizeof(::CRTCalibs) );
      instance.SetNew(&new_CRTCalibs);
      instance.SetNewArray(&newArray_CRTCalibs);
      instance.SetDelete(&delete_CRTCalibs);
      instance.SetDeleteArray(&deleteArray_CRTCalibs);
      instance.SetDestructor(&destruct_CRTCalibs);
      instance.SetStreamerFunc(&streamer_CRTCalibs);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::CRTCalibs*)
   {
      return GenerateInitInstanceLocal((::CRTCalibs*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::CRTCalibs*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_CRTRawhitBuffer(void *p = 0);
   static void *newArray_CRTRawhitBuffer(Long_t size, void *p);
   static void delete_CRTRawhitBuffer(void *p);
   static void deleteArray_CRTRawhitBuffer(void *p);
   static void destruct_CRTRawhitBuffer(void *p);
   static void streamer_CRTRawhitBuffer(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::CRTRawhitBuffer*)
   {
      ::CRTRawhitBuffer *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::CRTRawhitBuffer >(0);
      static ::ROOT::TGenericClassInfo 
         instance("CRTRawhitBuffer", ::CRTRawhitBuffer::Class_Version(), "CRTBuffers.h", 31,
                  typeid(::CRTRawhitBuffer), DefineBehavior(ptr, ptr),
                  &::CRTRawhitBuffer::Dictionary, isa_proxy, 16,
                  sizeof(::CRTRawhitBuffer) );
      instance.SetNew(&new_CRTRawhitBuffer);
      instance.SetNewArray(&newArray_CRTRawhitBuffer);
      instance.SetDelete(&delete_CRTRawhitBuffer);
      instance.SetDeleteArray(&deleteArray_CRTRawhitBuffer);
      instance.SetDestructor(&destruct_CRTRawhitBuffer);
      instance.SetStreamerFunc(&streamer_CRTRawhitBuffer);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::CRTRawhitBuffer*)
   {
      return GenerateInitInstanceLocal((::CRTRawhitBuffer*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::CRTRawhitBuffer*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_CRTRunHeader(void *p = 0);
   static void *newArray_CRTRunHeader(Long_t size, void *p);
   static void delete_CRTRunHeader(void *p);
   static void deleteArray_CRTRunHeader(void *p);
   static void destruct_CRTRunHeader(void *p);
   static void streamer_CRTRunHeader(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::CRTRunHeader*)
   {
      ::CRTRunHeader *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::CRTRunHeader >(0);
      static ::ROOT::TGenericClassInfo 
         instance("CRTRunHeader", ::CRTRunHeader::Class_Version(), "CRTRun.h", 85,
                  typeid(::CRTRunHeader), DefineBehavior(ptr, ptr),
                  &::CRTRunHeader::Dictionary, isa_proxy, 16,
                  sizeof(::CRTRunHeader) );
      instance.SetNew(&new_CRTRunHeader);
      instance.SetNewArray(&newArray_CRTRunHeader);
      instance.SetDelete(&delete_CRTRunHeader);
      instance.SetDeleteArray(&deleteArray_CRTRunHeader);
      instance.SetDestructor(&destruct_CRTRunHeader);
      instance.SetStreamerFunc(&streamer_CRTRunHeader);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::CRTRunHeader*)
   {
      return GenerateInitInstanceLocal((::CRTRunHeader*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::CRTRunHeader*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_CRTRun(void *p = 0);
   static void *newArray_CRTRun(Long_t size, void *p);
   static void delete_CRTRun(void *p);
   static void deleteArray_CRTRun(void *p);
   static void destruct_CRTRun(void *p);
   static void streamer_CRTRun(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::CRTRun*)
   {
      ::CRTRun *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::CRTRun >(0);
      static ::ROOT::TGenericClassInfo 
         instance("CRTRun", ::CRTRun::Class_Version(), "CRTRun.h", 33,
                  typeid(::CRTRun), DefineBehavior(ptr, ptr),
                  &::CRTRun::Dictionary, isa_proxy, 16,
                  sizeof(::CRTRun) );
      instance.SetNew(&new_CRTRun);
      instance.SetNewArray(&newArray_CRTRun);
      instance.SetDelete(&delete_CRTRun);
      instance.SetDeleteArray(&deleteArray_CRTRun);
      instance.SetDestructor(&destruct_CRTRun);
      instance.SetStreamerFunc(&streamer_CRTRun);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::CRTRun*)
   {
      return GenerateInitInstanceLocal((::CRTRun*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::CRTRun*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_CRTDisplay(void *p = 0);
   static void *newArray_CRTDisplay(Long_t size, void *p);
   static void delete_CRTDisplay(void *p);
   static void deleteArray_CRTDisplay(void *p);
   static void destruct_CRTDisplay(void *p);
   static void streamer_CRTDisplay(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::CRTDisplay*)
   {
      ::CRTDisplay *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::CRTDisplay >(0);
      static ::ROOT::TGenericClassInfo 
         instance("CRTDisplay", ::CRTDisplay::Class_Version(), "CRTDisplay.h", 30,
                  typeid(::CRTDisplay), DefineBehavior(ptr, ptr),
                  &::CRTDisplay::Dictionary, isa_proxy, 16,
                  sizeof(::CRTDisplay) );
      instance.SetNew(&new_CRTDisplay);
      instance.SetNewArray(&newArray_CRTDisplay);
      instance.SetDelete(&delete_CRTDisplay);
      instance.SetDeleteArray(&deleteArray_CRTDisplay);
      instance.SetDestructor(&destruct_CRTDisplay);
      instance.SetStreamerFunc(&streamer_CRTDisplay);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::CRTDisplay*)
   {
      return GenerateInitInstanceLocal((::CRTDisplay*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::CRTDisplay*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PMTFlash(void *p = 0);
   static void *newArray_PMTFlash(Long_t size, void *p);
   static void delete_PMTFlash(void *p);
   static void deleteArray_PMTFlash(void *p);
   static void destruct_PMTFlash(void *p);
   static void streamer_PMTFlash(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PMTFlash*)
   {
      ::PMTFlash *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PMTFlash >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PMTFlash", ::PMTFlash::Class_Version(), "TPCEvent.h", 25,
                  typeid(::PMTFlash), DefineBehavior(ptr, ptr),
                  &::PMTFlash::Dictionary, isa_proxy, 16,
                  sizeof(::PMTFlash) );
      instance.SetNew(&new_PMTFlash);
      instance.SetNewArray(&newArray_PMTFlash);
      instance.SetDelete(&delete_PMTFlash);
      instance.SetDeleteArray(&deleteArray_PMTFlash);
      instance.SetDestructor(&destruct_PMTFlash);
      instance.SetStreamerFunc(&streamer_PMTFlash);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PMTFlash*)
   {
      return GenerateInitInstanceLocal((::PMTFlash*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::PMTFlash*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TPCEvent(void *p = 0);
   static void *newArray_TPCEvent(Long_t size, void *p);
   static void delete_TPCEvent(void *p);
   static void deleteArray_TPCEvent(void *p);
   static void destruct_TPCEvent(void *p);
   static void streamer_TPCEvent(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TPCEvent*)
   {
      ::TPCEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TPCEvent >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TPCEvent", ::TPCEvent::Class_Version(), "TPCEvent.h", 49,
                  typeid(::TPCEvent), DefineBehavior(ptr, ptr),
                  &::TPCEvent::Dictionary, isa_proxy, 16,
                  sizeof(::TPCEvent) );
      instance.SetNew(&new_TPCEvent);
      instance.SetNewArray(&newArray_TPCEvent);
      instance.SetDelete(&delete_TPCEvent);
      instance.SetDeleteArray(&deleteArray_TPCEvent);
      instance.SetDestructor(&destruct_TPCEvent);
      instance.SetStreamerFunc(&streamer_TPCEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TPCEvent*)
   {
      return GenerateInitInstanceLocal((::TPCEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TPCEvent*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_CRTReco(void *p = 0);
   static void *newArray_CRTReco(Long_t size, void *p);
   static void delete_CRTReco(void *p);
   static void deleteArray_CRTReco(void *p);
   static void destruct_CRTReco(void *p);
   static void streamer_CRTReco(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::CRTReco*)
   {
      ::CRTReco *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::CRTReco >(0);
      static ::ROOT::TGenericClassInfo 
         instance("CRTReco", ::CRTReco::Class_Version(), "CRTReco.h", 19,
                  typeid(::CRTReco), DefineBehavior(ptr, ptr),
                  &::CRTReco::Dictionary, isa_proxy, 16,
                  sizeof(::CRTReco) );
      instance.SetNew(&new_CRTReco);
      instance.SetNewArray(&newArray_CRTReco);
      instance.SetDelete(&delete_CRTReco);
      instance.SetDeleteArray(&deleteArray_CRTReco);
      instance.SetDestructor(&destruct_CRTReco);
      instance.SetStreamerFunc(&streamer_CRTReco);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::CRTReco*)
   {
      return GenerateInitInstanceLocal((::CRTReco*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::CRTReco*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
TClass *CRTEvent::fgIsA = 0;  // static to hold class pointer

//______________________________________________________________________________
const char *CRTEvent::Class_Name()
{
   return "CRTEvent";
}

//______________________________________________________________________________
const char *CRTEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CRTEvent*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int CRTEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CRTEvent*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
void CRTEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CRTEvent*)0x0)->GetClass();
}

//______________________________________________________________________________
TClass *CRTEvent::Class()
{
   if (!fgIsA) fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CRTEvent*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *CRTRawhit::fgIsA = 0;  // static to hold class pointer

//______________________________________________________________________________
const char *CRTRawhit::Class_Name()
{
   return "CRTRawhit";
}

//______________________________________________________________________________
const char *CRTRawhit::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CRTRawhit*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int CRTRawhit::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CRTRawhit*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
void CRTRawhit::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CRTRawhit*)0x0)->GetClass();
}

//______________________________________________________________________________
TClass *CRTRawhit::Class()
{
   if (!fgIsA) fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CRTRawhit*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *CRT2Dhit::fgIsA = 0;  // static to hold class pointer

//______________________________________________________________________________
const char *CRT2Dhit::Class_Name()
{
   return "CRT2Dhit";
}

//______________________________________________________________________________
const char *CRT2Dhit::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CRT2Dhit*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int CRT2Dhit::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CRT2Dhit*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
void CRT2Dhit::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CRT2Dhit*)0x0)->GetClass();
}

//______________________________________________________________________________
TClass *CRT2Dhit::Class()
{
   if (!fgIsA) fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CRT2Dhit*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *CRTTrack::fgIsA = 0;  // static to hold class pointer

//______________________________________________________________________________
const char *CRTTrack::Class_Name()
{
   return "CRTTrack";
}

//______________________________________________________________________________
const char *CRTTrack::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CRTTrack*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int CRTTrack::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CRTTrack*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
void CRTTrack::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CRTTrack*)0x0)->GetClass();
}

//______________________________________________________________________________
TClass *CRTTrack::Class()
{
   if (!fgIsA) fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CRTTrack*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *CRTCalibs::fgIsA = 0;  // static to hold class pointer

//______________________________________________________________________________
const char *CRTCalibs::Class_Name()
{
   return "CRTCalibs";
}

//______________________________________________________________________________
const char *CRTCalibs::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CRTCalibs*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int CRTCalibs::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CRTCalibs*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
void CRTCalibs::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CRTCalibs*)0x0)->GetClass();
}

//______________________________________________________________________________
TClass *CRTCalibs::Class()
{
   if (!fgIsA) fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CRTCalibs*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *CRTRawhitBuffer::fgIsA = 0;  // static to hold class pointer

//______________________________________________________________________________
const char *CRTRawhitBuffer::Class_Name()
{
   return "CRTRawhitBuffer";
}

//______________________________________________________________________________
const char *CRTRawhitBuffer::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CRTRawhitBuffer*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int CRTRawhitBuffer::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CRTRawhitBuffer*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
void CRTRawhitBuffer::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CRTRawhitBuffer*)0x0)->GetClass();
}

//______________________________________________________________________________
TClass *CRTRawhitBuffer::Class()
{
   if (!fgIsA) fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CRTRawhitBuffer*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *CRTRunHeader::fgIsA = 0;  // static to hold class pointer

//______________________________________________________________________________
const char *CRTRunHeader::Class_Name()
{
   return "CRTRunHeader";
}

//______________________________________________________________________________
const char *CRTRunHeader::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CRTRunHeader*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int CRTRunHeader::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CRTRunHeader*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
void CRTRunHeader::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CRTRunHeader*)0x0)->GetClass();
}

//______________________________________________________________________________
TClass *CRTRunHeader::Class()
{
   if (!fgIsA) fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CRTRunHeader*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *CRTRun::fgIsA = 0;  // static to hold class pointer

//______________________________________________________________________________
const char *CRTRun::Class_Name()
{
   return "CRTRun";
}

//______________________________________________________________________________
const char *CRTRun::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CRTRun*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int CRTRun::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CRTRun*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
void CRTRun::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CRTRun*)0x0)->GetClass();
}

//______________________________________________________________________________
TClass *CRTRun::Class()
{
   if (!fgIsA) fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CRTRun*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *CRTDisplay::fgIsA = 0;  // static to hold class pointer

//______________________________________________________________________________
const char *CRTDisplay::Class_Name()
{
   return "CRTDisplay";
}

//______________________________________________________________________________
const char *CRTDisplay::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CRTDisplay*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int CRTDisplay::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CRTDisplay*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
void CRTDisplay::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CRTDisplay*)0x0)->GetClass();
}

//______________________________________________________________________________
TClass *CRTDisplay::Class()
{
   if (!fgIsA) fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CRTDisplay*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PMTFlash::fgIsA = 0;  // static to hold class pointer

//______________________________________________________________________________
const char *PMTFlash::Class_Name()
{
   return "PMTFlash";
}

//______________________________________________________________________________
const char *PMTFlash::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PMTFlash*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PMTFlash::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PMTFlash*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
void PMTFlash::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PMTFlash*)0x0)->GetClass();
}

//______________________________________________________________________________
TClass *PMTFlash::Class()
{
   if (!fgIsA) fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PMTFlash*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TPCEvent::fgIsA = 0;  // static to hold class pointer

//______________________________________________________________________________
const char *TPCEvent::Class_Name()
{
   return "TPCEvent";
}

//______________________________________________________________________________
const char *TPCEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TPCEvent*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TPCEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TPCEvent*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
void TPCEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TPCEvent*)0x0)->GetClass();
}

//______________________________________________________________________________
TClass *TPCEvent::Class()
{
   if (!fgIsA) fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TPCEvent*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *CRTReco::fgIsA = 0;  // static to hold class pointer

//______________________________________________________________________________
const char *CRTReco::Class_Name()
{
   return "CRTReco";
}

//______________________________________________________________________________
const char *CRTReco::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CRTReco*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int CRTReco::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CRTReco*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
void CRTReco::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CRTReco*)0x0)->GetClass();
}

//______________________________________________________________________________
TClass *CRTReco::Class()
{
   if (!fgIsA) fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CRTReco*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
void CRTEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class CRTEvent.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      hits->Streamer(R__b);
      R__b >> mean_t0;
      R__b >> mean_t1;
      R__b >> Nhits;
      R__b >> s;
      R__b.CheckByteCount(R__s, R__c, CRTEvent::IsA());
   } else {
      R__c = R__b.WriteVersion(CRTEvent::IsA(), kTRUE);
      TObject::Streamer(R__b);
      hits->Streamer(R__b);
      R__b << mean_t0;
      R__b << mean_t1;
      R__b << Nhits;
      R__b << s;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_CRTEvent(void *p) {
      return  p ? new(p) ::CRTEvent : new ::CRTEvent;
   }
   static void *newArray_CRTEvent(Long_t nElements, void *p) {
      return p ? new(p) ::CRTEvent[nElements] : new ::CRTEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_CRTEvent(void *p) {
      delete ((::CRTEvent*)p);
   }
   static void deleteArray_CRTEvent(void *p) {
      delete [] ((::CRTEvent*)p);
   }
   static void destruct_CRTEvent(void *p) {
      typedef ::CRTEvent current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_CRTEvent(TBuffer &buf, void *obj) {
      ((::CRTEvent*)obj)->::CRTEvent::Streamer(buf);
   }
} // end of namespace ROOT for class ::CRTEvent

//______________________________________________________________________________
void CRTRawhit::Streamer(TBuffer &R__b)
{
   // Stream an object of class CRTRawhit.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b >> mac5;
      R__b >> flags;
      R__b >> lostcpu;
      R__b >> lostfpga;
      R__b >> ts0;
      R__b >> ts1;
      R__b.ReadStaticArray((unsigned short*)adc);
      R__b >> s;
      R__b >> ms;
      R__b >> cable;
      R__b.CheckByteCount(R__s, R__c, CRTRawhit::IsA());
   } else {
      R__c = R__b.WriteVersion(CRTRawhit::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b << mac5;
      R__b << flags;
      R__b << lostcpu;
      R__b << lostfpga;
      R__b << ts0;
      R__b << ts1;
      R__b.WriteArray(adc, 32);
      R__b << s;
      R__b << ms;
      R__b << cable;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_CRTRawhit(void *p) {
      return  p ? new(p) ::CRTRawhit : new ::CRTRawhit;
   }
   static void *newArray_CRTRawhit(Long_t nElements, void *p) {
      return p ? new(p) ::CRTRawhit[nElements] : new ::CRTRawhit[nElements];
   }
   // Wrapper around operator delete
   static void delete_CRTRawhit(void *p) {
      delete ((::CRTRawhit*)p);
   }
   static void deleteArray_CRTRawhit(void *p) {
      delete [] ((::CRTRawhit*)p);
   }
   static void destruct_CRTRawhit(void *p) {
      typedef ::CRTRawhit current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_CRTRawhit(TBuffer &buf, void *obj) {
      ((::CRTRawhit*)obj)->::CRTRawhit::Streamer(buf);
   }
} // end of namespace ROOT for class ::CRTRawhit

//______________________________________________________________________________
void CRT2Dhit::Streamer(TBuffer &R__b)
{
   // Stream an object of class CRT2Dhit.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b >> t0;
      R__b >> t1;
      R__b >> dt0;
      R__b >> dt1;
      R__b >> s;
      R__b >> x;
      R__b >> y;
      R__b >> z;
      R__b >> nhits1;
      R__b >> nhits2;
      R__b >> plane1;
      R__b >> plane2;
      int R__i;
      for (R__i = 0; R__i < 2; R__i++)
         rhit[R__i].Streamer(R__b);
      R__b >> calibrated;
      R__b >> Edep;
      R__b.CheckByteCount(R__s, R__c, CRT2Dhit::IsA());
   } else {
      R__c = R__b.WriteVersion(CRT2Dhit::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b << t0;
      R__b << t1;
      R__b << dt0;
      R__b << dt1;
      R__b << s;
      R__b << x;
      R__b << y;
      R__b << z;
      R__b << nhits1;
      R__b << nhits2;
      R__b << plane1;
      R__b << plane2;
      int R__i;
      for (R__i = 0; R__i < 2; R__i++)
         rhit[R__i].Streamer(R__b);
      R__b << calibrated;
      R__b << Edep;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_CRT2Dhit(void *p) {
      return  p ? new(p) ::CRT2Dhit : new ::CRT2Dhit;
   }
   static void *newArray_CRT2Dhit(Long_t nElements, void *p) {
      return p ? new(p) ::CRT2Dhit[nElements] : new ::CRT2Dhit[nElements];
   }
   // Wrapper around operator delete
   static void delete_CRT2Dhit(void *p) {
      delete ((::CRT2Dhit*)p);
   }
   static void deleteArray_CRT2Dhit(void *p) {
      delete [] ((::CRT2Dhit*)p);
   }
   static void destruct_CRT2Dhit(void *p) {
      typedef ::CRT2Dhit current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_CRT2Dhit(TBuffer &buf, void *obj) {
      ((::CRT2Dhit*)obj)->::CRT2Dhit::Streamer(buf);
   }
} // end of namespace ROOT for class ::CRT2Dhit

//______________________________________________________________________________
void CRTTrack::Streamer(TBuffer &R__b)
{
   // Stream an object of class CRTTrack.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      int R__i;
      for (R__i = 0; R__i < 2; R__i++)
         hit2d[R__i].Streamer(R__b);
      R__b >> tof;
      R__b >> L;
      R__b.CheckByteCount(R__s, R__c, CRTTrack::IsA());
   } else {
      R__c = R__b.WriteVersion(CRTTrack::IsA(), kTRUE);
      TObject::Streamer(R__b);
      int R__i;
      for (R__i = 0; R__i < 2; R__i++)
         hit2d[R__i].Streamer(R__b);
      R__b << tof;
      R__b << L;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_CRTTrack(void *p) {
      return  p ? new(p) ::CRTTrack : new ::CRTTrack;
   }
   static void *newArray_CRTTrack(Long_t nElements, void *p) {
      return p ? new(p) ::CRTTrack[nElements] : new ::CRTTrack[nElements];
   }
   // Wrapper around operator delete
   static void delete_CRTTrack(void *p) {
      delete ((::CRTTrack*)p);
   }
   static void deleteArray_CRTTrack(void *p) {
      delete [] ((::CRTTrack*)p);
   }
   static void destruct_CRTTrack(void *p) {
      typedef ::CRTTrack current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_CRTTrack(TBuffer &buf, void *obj) {
      ((::CRTTrack*)obj)->::CRTTrack::Streamer(buf);
   }
} // end of namespace ROOT for class ::CRTTrack

//______________________________________________________________________________
void CRTCalibs::Streamer(TBuffer &R__b)
{
   // Stream an object of class CRTCalibs.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b >> StripW;
      R__b >> Version;
      R__b >> FiberDelay;
      R__b.ReadStaticArray((int*)ModuleExists);
      R__b.ReadStaticArray((bool*)PositionExists);
      R__b.ReadStaticArray((double*)Xs);
      R__b.ReadStaticArray((double*)Ys);
      R__b.ReadStaticArray((double*)Zs);
      R__b.ReadStaticArray((int*)Plane);
      R__b.ReadStaticArray((bool*)CableDelayExists);
      R__b.ReadStaticArray((double*)Dts);
      R__b.ReadStaticArray((bool*)ADCCalibsExists);
      R__b.ReadStaticArray((int*)ADCPedestal);
      R__b.ReadStaticArray((int*)ADCGain);
      R__b.CheckByteCount(R__s, R__c, CRTCalibs::IsA());
   } else {
      R__c = R__b.WriteVersion(CRTCalibs::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b << StripW;
      R__b << Version;
      R__b << FiberDelay;
      R__b.WriteArray(ModuleExists, 200);
      R__b.WriteArray((bool*)PositionExists, 6400);
      R__b.WriteArray((double*)Xs, 6400);
      R__b.WriteArray((double*)Ys, 6400);
      R__b.WriteArray((double*)Zs, 6400);
      R__b.WriteArray((int*)Plane, 6400);
      R__b.WriteArray(CableDelayExists, 200);
      R__b.WriteArray(Dts, 200);
      R__b.WriteArray((bool*)ADCCalibsExists, 6400);
      R__b.WriteArray((int*)ADCPedestal, 6400);
      R__b.WriteArray((int*)ADCGain, 6400);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_CRTCalibs(void *p) {
      return  p ? new(p) ::CRTCalibs : new ::CRTCalibs;
   }
   static void *newArray_CRTCalibs(Long_t nElements, void *p) {
      return p ? new(p) ::CRTCalibs[nElements] : new ::CRTCalibs[nElements];
   }
   // Wrapper around operator delete
   static void delete_CRTCalibs(void *p) {
      delete ((::CRTCalibs*)p);
   }
   static void deleteArray_CRTCalibs(void *p) {
      delete [] ((::CRTCalibs*)p);
   }
   static void destruct_CRTCalibs(void *p) {
      typedef ::CRTCalibs current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_CRTCalibs(TBuffer &buf, void *obj) {
      ((::CRTCalibs*)obj)->::CRTCalibs::Streamer(buf);
   }
} // end of namespace ROOT for class ::CRTCalibs

//______________________________________________________________________________
void CRTRawhitBuffer::Streamer(TBuffer &R__b)
{
   // Stream an object of class CRTRawhitBuffer.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      hits->Streamer(R__b);
      R__b >> Nhits;
      R__b >> mac5;
      R__b.CheckByteCount(R__s, R__c, CRTRawhitBuffer::IsA());
   } else {
      R__c = R__b.WriteVersion(CRTRawhitBuffer::IsA(), kTRUE);
      TObject::Streamer(R__b);
      hits->Streamer(R__b);
      R__b << Nhits;
      R__b << mac5;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_CRTRawhitBuffer(void *p) {
      return  p ? new(p) ::CRTRawhitBuffer : new ::CRTRawhitBuffer;
   }
   static void *newArray_CRTRawhitBuffer(Long_t nElements, void *p) {
      return p ? new(p) ::CRTRawhitBuffer[nElements] : new ::CRTRawhitBuffer[nElements];
   }
   // Wrapper around operator delete
   static void delete_CRTRawhitBuffer(void *p) {
      delete ((::CRTRawhitBuffer*)p);
   }
   static void deleteArray_CRTRawhitBuffer(void *p) {
      delete [] ((::CRTRawhitBuffer*)p);
   }
   static void destruct_CRTRawhitBuffer(void *p) {
      typedef ::CRTRawhitBuffer current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_CRTRawhitBuffer(TBuffer &buf, void *obj) {
      ((::CRTRawhitBuffer*)obj)->::CRTRawhitBuffer::Streamer(buf);
   }
} // end of namespace ROOT for class ::CRTRawhitBuffer

//______________________________________________________________________________
void CRTRunHeader::Streamer(TBuffer &R__b)
{
   // Stream an object of class CRTRunHeader.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b >> cal;
      R__b >> N;
      R__b >> NRawhits;
      R__b >> N2Dhits;
      R__b >> NEvents;
      R__b >> NTracks;
      R__b >> NFlashes;
      R__b.ReadStaticArray((int*)Nt0refs);
      R__b.ReadStaticArray((int*)Nt1refs);
      R__b >> startSecondsUTC;
      R__b >> endSecondsUTC;
      R__b.CheckByteCount(R__s, R__c, CRTRunHeader::IsA());
   } else {
      R__c = R__b.WriteVersion(CRTRunHeader::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b << cal;
      R__b << N;
      R__b << NRawhits;
      R__b << N2Dhits;
      R__b << NEvents;
      R__b << NTracks;
      R__b << NFlashes;
      R__b.WriteArray(Nt0refs, 200);
      R__b.WriteArray(Nt1refs, 200);
      R__b << startSecondsUTC;
      R__b << endSecondsUTC;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_CRTRunHeader(void *p) {
      return  p ? new(p) ::CRTRunHeader : new ::CRTRunHeader;
   }
   static void *newArray_CRTRunHeader(Long_t nElements, void *p) {
      return p ? new(p) ::CRTRunHeader[nElements] : new ::CRTRunHeader[nElements];
   }
   // Wrapper around operator delete
   static void delete_CRTRunHeader(void *p) {
      delete ((::CRTRunHeader*)p);
   }
   static void deleteArray_CRTRunHeader(void *p) {
      delete [] ((::CRTRunHeader*)p);
   }
   static void destruct_CRTRunHeader(void *p) {
      typedef ::CRTRunHeader current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_CRTRunHeader(TBuffer &buf, void *obj) {
      ((::CRTRunHeader*)obj)->::CRTRunHeader::Streamer(buf);
   }
} // end of namespace ROOT for class ::CRTRunHeader

//______________________________________________________________________________
void CRTRun::Streamer(TBuffer &R__b)
{
   // Stream an object of class CRTRun.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b >> f;
      R__b >> t;
      hits->Streamer(R__b);
      h2d->Streamer(R__b);
      evs->Streamer(R__b);
      trk->Streamer(R__b);
      fl->Streamer(R__b);
      R__b >> rheader;
      R__b.CheckByteCount(R__s, R__c, CRTRun::IsA());
   } else {
      R__c = R__b.WriteVersion(CRTRun::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b << f;
      R__b << t;
      hits->Streamer(R__b);
      h2d->Streamer(R__b);
      evs->Streamer(R__b);
      trk->Streamer(R__b);
      fl->Streamer(R__b);
      R__b << rheader;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_CRTRun(void *p) {
      return  p ? new(p) ::CRTRun : new ::CRTRun;
   }
   static void *newArray_CRTRun(Long_t nElements, void *p) {
      return p ? new(p) ::CRTRun[nElements] : new ::CRTRun[nElements];
   }
   // Wrapper around operator delete
   static void delete_CRTRun(void *p) {
      delete ((::CRTRun*)p);
   }
   static void deleteArray_CRTRun(void *p) {
      delete [] ((::CRTRun*)p);
   }
   static void destruct_CRTRun(void *p) {
      typedef ::CRTRun current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_CRTRun(TBuffer &buf, void *obj) {
      ((::CRTRun*)obj)->::CRTRun::Streamer(buf);
   }
} // end of namespace ROOT for class ::CRTRun

//______________________________________________________________________________
void CRTDisplay::Streamer(TBuffer &R__b)
{
   // Stream an object of class CRTDisplay.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b >> teve;
      R__b >> pal;
      R__b >> geom;
      R__b >> en;
      R__b >> node;
      R__b >> cal;
      R__b >> Verb;
      R__b >> run;
      R__b >> curev;
      R__b >> elist;
      R__b >> qraw;
      R__b >> comp_h2d;
      R__b >> h2d;
      R__b >> h2d_raw;
      R__b >> comp_trk;
      R__b >> lines;
      R__b >> trk_h2d;
      R__b >> trk_h2d_raw;
      R__b.CheckByteCount(R__s, R__c, CRTDisplay::IsA());
   } else {
      R__c = R__b.WriteVersion(CRTDisplay::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b << teve;
      R__b << pal;
      R__b << geom;
      R__b << en;
      R__b << node;
      R__b << cal;
      R__b << Verb;
      R__b << run;
      R__b << curev;
      R__b << elist;
      R__b << qraw;
      R__b << comp_h2d;
      R__b << h2d;
      R__b << h2d_raw;
      R__b << comp_trk;
      R__b << lines;
      R__b << trk_h2d;
      R__b << trk_h2d_raw;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_CRTDisplay(void *p) {
      return  p ? new(p) ::CRTDisplay : new ::CRTDisplay;
   }
   static void *newArray_CRTDisplay(Long_t nElements, void *p) {
      return p ? new(p) ::CRTDisplay[nElements] : new ::CRTDisplay[nElements];
   }
   // Wrapper around operator delete
   static void delete_CRTDisplay(void *p) {
      delete ((::CRTDisplay*)p);
   }
   static void deleteArray_CRTDisplay(void *p) {
      delete [] ((::CRTDisplay*)p);
   }
   static void destruct_CRTDisplay(void *p) {
      typedef ::CRTDisplay current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_CRTDisplay(TBuffer &buf, void *obj) {
      ((::CRTDisplay*)obj)->::CRTDisplay::Streamer(buf);
   }
} // end of namespace ROOT for class ::CRTDisplay

//______________________________________________________________________________
void PMTFlash::Streamer(TBuffer &R__b)
{
   // Stream an object of class PMTFlash.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b >> t0;
      R__b >> t1;
      R__b >> s;
      R__b >> npe;
      R__b >> x;
      R__b >> y;
      R__b >> z;
      R__b >> IsBNB;
      R__b >> event;
      R__b.CheckByteCount(R__s, R__c, PMTFlash::IsA());
   } else {
      R__c = R__b.WriteVersion(PMTFlash::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b << t0;
      R__b << t1;
      R__b << s;
      R__b << npe;
      R__b << x;
      R__b << y;
      R__b << z;
      R__b << IsBNB;
      R__b << event;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PMTFlash(void *p) {
      return  p ? new(p) ::PMTFlash : new ::PMTFlash;
   }
   static void *newArray_PMTFlash(Long_t nElements, void *p) {
      return p ? new(p) ::PMTFlash[nElements] : new ::PMTFlash[nElements];
   }
   // Wrapper around operator delete
   static void delete_PMTFlash(void *p) {
      delete ((::PMTFlash*)p);
   }
   static void deleteArray_PMTFlash(void *p) {
      delete [] ((::PMTFlash*)p);
   }
   static void destruct_PMTFlash(void *p) {
      typedef ::PMTFlash current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_PMTFlash(TBuffer &buf, void *obj) {
      ((::PMTFlash*)obj)->::PMTFlash::Streamer(buf);
   }
} // end of namespace ROOT for class ::PMTFlash

//______________________________________________________________________________
void TPCEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class TPCEvent.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b >> event;
      R__b >> IsBNB;
      flar->Streamer(R__b);
      R__b >> tr;
      R__b >> trig_t0;
      R__b >> s;
      R__b >> Nflashes;
      R__b.CheckByteCount(R__s, R__c, TPCEvent::IsA());
   } else {
      R__c = R__b.WriteVersion(TPCEvent::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b << event;
      R__b << IsBNB;
      flar->Streamer(R__b);
      R__b << tr;
      R__b << trig_t0;
      R__b << s;
      R__b << Nflashes;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TPCEvent(void *p) {
      return  p ? new(p) ::TPCEvent : new ::TPCEvent;
   }
   static void *newArray_TPCEvent(Long_t nElements, void *p) {
      return p ? new(p) ::TPCEvent[nElements] : new ::TPCEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_TPCEvent(void *p) {
      delete ((::TPCEvent*)p);
   }
   static void deleteArray_TPCEvent(void *p) {
      delete [] ((::TPCEvent*)p);
   }
   static void destruct_TPCEvent(void *p) {
      typedef ::TPCEvent current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TPCEvent(TBuffer &buf, void *obj) {
      ((::TPCEvent*)obj)->::TPCEvent::Streamer(buf);
   }
} // end of namespace ROOT for class ::TPCEvent

//______________________________________________________________________________
void CRTReco::Streamer(TBuffer &R__b)
{
   // Stream an object of class CRTReco.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b >> ftpc;
      R__b >> ttpc;
      R__b >> crtrun;
      R__b.CheckByteCount(R__s, R__c, CRTReco::IsA());
   } else {
      R__c = R__b.WriteVersion(CRTReco::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b << ftpc;
      R__b << ttpc;
      R__b << crtrun;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_CRTReco(void *p) {
      return  p ? new(p) ::CRTReco : new ::CRTReco;
   }
   static void *newArray_CRTReco(Long_t nElements, void *p) {
      return p ? new(p) ::CRTReco[nElements] : new ::CRTReco[nElements];
   }
   // Wrapper around operator delete
   static void delete_CRTReco(void *p) {
      delete ((::CRTReco*)p);
   }
   static void deleteArray_CRTReco(void *p) {
      delete [] ((::CRTReco*)p);
   }
   static void destruct_CRTReco(void *p) {
      typedef ::CRTReco current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_CRTReco(TBuffer &buf, void *obj) {
      ((::CRTReco*)obj)->::CRTReco::Streamer(buf);
   }
} // end of namespace ROOT for class ::CRTReco

namespace {
  void TriggerDictionaryInitialization_CRTCint_Impl() {
    static const char* headers[] = {
"CRTEvent.h",
"TPCEvent.h",
"CRTBuffers.h",
"CRTDisplay.h",
"CRTRun.h",
"CRTReco.h",
0
    };
    static const char* includePaths[] = {
"../../include",
"/cernsoft/root_v6.00.02/root/include",
"/data/CRT_uBdata/V20_Analysis/libcrt/src/libCRT/",
0
    };
    static const char* fwdDeclCode = 
"class CRTEvent;"
"class CRTRawhit;"
"class CRT2Dhit;"
"class CRTTrack;"
"class CRTCalibs;"
"class CRTRawhitBuffer;"
"class CRTRunHeader;"
"class CRTRun;"
"class CRTDisplay;"
"class PMTFlash;"
"class TPCEvent;"
"class CRTReco;"
;
    static const char* payloadCode = 
"\n"
"#ifndef G__VECTOR_HAS_CLASS_ITERATOR\n"
"  #define G__VECTOR_HAS_CLASS_ITERATOR\n"
"#endif\n"
"\n"
"#define _BACKWARD_BACKWARD_WARNING_H\n"
"#include \"CRTEvent.h\"\n"
"#include \"TPCEvent.h\"\n"
"#include \"CRTBuffers.h\"\n"
"#include \"CRTDisplay.h\"\n"
"#include \"CRTRun.h\"\n"
"#include \"CRTReco.h\"\n"
"\n"
"#undef  _BACKWARD_BACKWARD_WARNING_H\n"
;
    static const char* classesHeaders[]={
"CRT2Dhit", payloadCode, "@",
"CRTCalibs", payloadCode, "@",
"CRTDisplay", payloadCode, "@",
"CRTEvent", payloadCode, "@",
"CRTRawhit", payloadCode, "@",
"CRTRawhitBuffer", payloadCode, "@",
"CRTReco", payloadCode, "@",
"CRTRun", payloadCode, "@",
"CRTRunHeader", payloadCode, "@",
"CRTTrack", payloadCode, "@",
"PMTFlash", payloadCode, "@",
"TPCEvent", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("CRTCint",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_CRTCint_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_CRTCint_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_CRTCint() {
  TriggerDictionaryInitialization_CRTCint_Impl();
}
