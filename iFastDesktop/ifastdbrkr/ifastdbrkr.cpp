//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   :  ifastdbrkr.cpp
// ^AUTHOR :  Chris Purdye
// ^DATE   :  April 2010
//
// ----------------------------------------------------------
#include <srcprag.h>
#include "ifastdbrkr.hpp"
#include <bfutil/bfcritsec.hpp>
#include <bfutil/bfguard.hpp>
#include <map>
#include <dstring.hpp>
#include <configmanager.hpp>
#include <activemq/library/ActiveMQCPP.h>

static ifastdbrkr::MessageService s_service = ifastdbrkr::MessageService::ActiveMQ;
static bool s_isActiveMQInit = false;
static BFCritSec s_csSonicMQ;

typedef std::map<DStringA, DStringA>   VIEW_BATCH_MAP;
typedef VIEW_BATCH_MAP::iterator VIEW_BATCH_MAP_ITER;

namespace ifastdbrkr {
MessageService getMessageService()
{
  BFGuard g(s_csSonicMQ);
  return s_service;
}

void setMessageService(MessageService ms)
{
  BFGuard g(s_csSonicMQ);
  s_service = ms;
}

MessageService cycleMessageService()
{
  switch (getMessageService())
  {
    case ifastdbrkr::MessageService::ActiveMQ:
      setMessageService(MessageService::SonicMQ);
      return MessageService::SonicMQ;

    case ifastdbrkr::MessageService::SonicMQ:
      setMessageService(MessageService::ActiveMQ);
      return MessageService::ActiveMQ;
  }

  assert(0);

  return MessageService(-1);
}

void initialize()
{
	initializeActiveMQ();
}

void initializeActiveMQ()
{
  assert(!s_isActiveMQInit);

  activemq::library::ActiveMQCPP::initializeLibrary();
  s_isActiveMQInit = true;
}

   void shutdown() { shutdownActiveMQ(); }

   void shutdownActiveMQ()
   {
     assert(s_isActiveMQInit);
     activemq::library::ActiveMQCPP::shutdownLibrary();
     s_isActiveMQInit = false;
   }

   static VIEW_BATCH_MAP* getViewBatchMap() {
      static VIEW_BATCH_MAP* s_pViewBatchMap = NULL;
      static BFCritSec cs;
      BFGuard g(cs);
      if( NULL == s_pViewBatchMap ) {
         s_pViewBatchMap = new VIEW_BATCH_MAP;
         DString dstr = GetConfigValueAsString(I_("RTSHost"), I_("ViewBatch"));
         if( dstr != I_("") ) {
            I_CHAR* pszSaveTemp;
            I_CHAR* pszTemp;
            pszSaveTemp = pszTemp = new I_CHAR[dstr.size() + 1];
            i_strcpy(pszTemp, dstr.c_str());
            while( NULL != pszTemp ) {
               DString dstrKey, dstrValue;
               pszTemp = parseIdiString(pszTemp, dstrKey, dstrValue);
               DStringA strKey(dstrKey);
               DStringA strValue(dstrValue);
               if( strValue.asInteger() == 0 ) {
                  strValue = "1";
               }
               s_pViewBatchMap->insert( VIEW_BATCH_MAP::value_type(strKey,strValue) );
            }
            delete[] pszSaveTemp;
         }
      }
      return( s_pViewBatchMap );
   }

   IFASTDBRKR_LINKAGE const DStringA& getBatchSize( const DStringA& view ) {
      VIEW_BATCH_MAP* pViewBatchMap = getViewBatchMap();
      VIEW_BATCH_MAP_ITER it = pViewBatchMap->find(view);
      if( pViewBatchMap->end() != it ) {
         return( (*it).second );
      }
      static DStringA strDefault("1");
      return( strDefault );
   }

   bool getBatchSize( DStringA& view, DStringA& size ) {
      VIEW_BATCH_MAP* pViewBatchMap = getViewBatchMap();
      VIEW_BATCH_MAP_ITER it = pViewBatchMap->begin();
      for( ; it != pViewBatchMap->end(); ++it ) {
         if( view == "" ) {
            view = (*it).first;
            size = (*it).second;
            return(true);
         }
         if( view == (*it).first ) {
            ++it;
            if( it != pViewBatchMap->end() ) {
               view = (*it).first;
               size = (*it).second;
               return(true);
            }
            return(false);
         }
      }
      return( false );
   }
}

