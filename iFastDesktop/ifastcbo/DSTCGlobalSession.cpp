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
//    Copyright 2000 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DSTCGlobalSession.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//******************************************************************************

#include "stdafx.h"
#include "dstcglobalsession.hpp"
#include "dstcusersession.hpp"
#include "mgmtco.hpp"
#include <bfutil\bfguard.hpp>
#include <ifastdataimpl\dse_dstcglob_vw.hpp>
#include <bf/log/log.hpp>

namespace
{
   const I_CHAR * const CLASSNAME    = I_( "DSTCGlobalSession" );
   const I_CHAR * const AQUIREMGMTCO = I_( "aquireMgmtCo" );
}

namespace CND
{  // Conditions used
   extern const long ERR_MGMT_CO_NOT_AVAILABLE;
}

//*****************************************************************
class MgmtCoGuard {
public:
   MgmtCoGuard( const DString& dstMgmtCo );
   ~MgmtCoGuard();

private:
   BFGuard _guard;

   static BFCritSec* getLock( const DString& dstMgmtCo );

   typedef std::map< DString, BFCritSec*>   LOCK_MAP;
   typedef LOCK_MAP::iterator               LOCK_MAP_ITER;
   typedef LOCK_MAP::value_type             LOCK_MAP_VALUE_TYPE;

   static LOCK_MAP s_locks;
   static BFCritSec s_lockMapLock;
};

//******************************************************************************
// static initializers.
MgmtCoGuard::LOCK_MAP MgmtCoGuard::s_locks;
BFCritSec MgmtCoGuard::s_lockMapLock;

MgmtCoGuard::MgmtCoGuard( const DString& dstMgmtCo )
: _guard(*getLock( dstMgmtCo ))
{
}

//******************************************************************************
MgmtCoGuard::~MgmtCoGuard() 
{
}

//******************************************************************************
BFCritSec* 
MgmtCoGuard::getLock( const DString& dstMgmtCo )
{
   BFGuard cs( s_lockMapLock );

   LOCK_MAP_ITER iter = s_locks.find( dstMgmtCo );

   if ( iter != s_locks.end() ) {
      return (*iter).second;
   }
   
   BFCritSec* newLock = new BFCritSec();
   s_locks.insert( LOCK_MAP_VALUE_TYPE(dstMgmtCo, newLock) );

   return newLock;

}

//*****************************************************************
DSTCGlobalSession::DSTCGlobalSession(DSTCUserSession &userSession)
: BFGlobalSession( userSession, ifds::DSTCGLOB_VW )
{
}

DSTCGlobalSession::~DSTCGlobalSession()
{
   BFGuard cs( _mgmtCoLock );

   {
      // destroy all current management companies
      MGMT_CO_MAP_ITER iter = _currentMgmtCoMap.begin();

      while( iter != _currentMgmtCoMap.end() )
      {

         MgmtCo *mgmtCo = (*iter).second;
         assert ( mgmtCo->referenceCount == 0 ); // should be unreference before destruction

         delete mgmtCo;
         iter = _currentMgmtCoMap.erase( iter );

      }
   }

   {
      MGMT_CO_SET_ITER iter = _retiredMgmtCoSet.begin();

      assert ( iter == _retiredMgmtCoSet.end() ); // _retiredMgmtCoSet should be empty

      while( iter != _retiredMgmtCoSet.end() )
      {

         delete (*iter);
         iter = _retiredMgmtCoSet.erase( iter );

      }


   }

}

//******************************************************************************
SEVERITY 
DSTCGlobalSession::refreshMgmtCo( const DString& dstMgmtCo )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "refreshMgmtCo" ) );

   bf::log::LogStream ls( bf::log::cbo );
   ls << bf::log::information << I_( "Refreshing MgmtCo " ) << dstMgmtCo << bf::log::endlf;

   MgmtCo *pMgmtCo = new MgmtCo( *this );
   if( pMgmtCo->init( dstMgmtCo ) > WARNING )
   {
      delete pMgmtCo;
      pMgmtCo = NULL;

      ls << bf::log::severe << I_( "Failed to refresh MgmtCo " ) << dstMgmtCo << bf::log::endlf;

      PROMOTECONDITIONS();
      Frame *frame = MYFRAME();
      frame->packConditions();
      int count = frame->getCount(  );
      for( int i = 0; i < count; i++ )
      {
         Condition *cnd = frame->getCondition( i );
         cnd->prepareMessage( ClientLocaleContext::get() );
         ls << bf::log::severe << I_( "Error refreshing MgmtCo " ) 
                               << dstMgmtCo 
                               << I_( ": [" )
                               << cnd->getComponentName() 
                               << I_( " - " )
                               << cnd->getCode() 
                               << I_( "] " )
                               << cnd->getMessage()
                               << bf::log::endlf;
      }
      ls.flush();

   }
   else
   {
      BFGuard cs( _mgmtCoLock );

      MGMT_CO_MAP_ITER iter = _currentMgmtCoMap.find( dstMgmtCo );

      if( iter != _currentMgmtCoMap.end() )
      {

         MgmtCo *pOldMgmtCo = (*iter).second;

         if( pOldMgmtCo->referenceCount > 0 )
         {
            _retiredMgmtCoSet.insert( pOldMgmtCo );
         }
         else
         {
            delete pOldMgmtCo;
         }

         _currentMgmtCoMap.erase( iter );

      }

      _currentMgmtCoMap.insert( MGMT_CO_MAP_VALUE_TYPE( dstMgmtCo, pMgmtCo ) );

   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
MgmtCo *
DSTCGlobalSession::aquireMgmtCo( const DString& dstMgmtCo )
{
   bf::log::LogStream ls( bf::log::cbo );
   {
      MgmtCoGuard mcGuard( dstMgmtCo );
      {
         BFGuard cs( _mgmtCoLock );

         MGMT_CO_MAP_ITER iter = _currentMgmtCoMap.find( dstMgmtCo );
         if( iter != _currentMgmtCoMap.end() )
         {
            (*iter).second->referenceCount++;
            return(*iter).second;
         }
      }

      ls << bf::log::information << I_( "MgmtCo " ) << dstMgmtCo << I_( " not found. Will refresh and retry." ) << bf::log::endlf;

      // refresh and try again, done unlocked for performance sake.
      refreshMgmtCo( dstMgmtCo );
   }

   {
      BFGuard cs( _mgmtCoLock );

      MGMT_CO_MAP_ITER iter = _currentMgmtCoMap.find( dstMgmtCo );
      if( iter != _currentMgmtCoMap.end() )
      {
         (*iter).second->referenceCount++;
         return(*iter).second;
      }
   }

   ls << bf::log::information << I_( "MgmtCo " ) << dstMgmtCo << I_( " not found. Failed to aquire." ) << bf::log::endlf;

   DString strIDI;
   addIDITagValue( strIDI, I_("mgmtco"), dstMgmtCo );

   THROWFROMFILEIDI2( CND::IFASTCBO_CONDITION, 
                      CLASSNAME, 
                      AQUIREMGMTCO,
                      CND::ERR_MGMT_CO_NOT_AVAILABLE, 
                      strIDI );

}

//******************************************************************************
void 
DSTCGlobalSession::freeMgmtCo( MgmtCo *pMgmtCo )
{
   BFGuard cs( _mgmtCoLock );

   pMgmtCo->referenceCount--;
   if( pMgmtCo->referenceCount < 1 )
   {
      MGMT_CO_SET_ITER iter = _retiredMgmtCoSet.find( pMgmtCo );

      if( iter != _retiredMgmtCoSet.end() )
      {
         delete pMgmtCo;
         _retiredMgmtCoSet.erase( iter );
      }

   }

}
//******************************************************************************

SEVERITY 
DSTCGlobalSession::getMgmtCo( const DString& dstMgmtCo )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMgmtCo" ) );

   BFGuard cs( _mgmtCoLock );//we lock here for a very long time ;but only Desktop should call this method, so it doesn't matter

   MGMT_CO_MAP_ITER iter = _currentMgmtCoMap.find( dstMgmtCo );

   if( iter == _currentMgmtCoMap.end() )
   {
      MgmtCo *pMgmtCo = new MgmtCo(*this);
      if( pMgmtCo->init( dstMgmtCo ) > WARNING )
         delete pMgmtCo;
      else
         _currentMgmtCoMap.insert( MGMT_CO_MAP_VALUE_TYPE( dstMgmtCo, pMgmtCo ) );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

bool 
DSTCGlobalSession::findMgmtCo( const DString& dstMgmtCo )
{
	bool bRetVal = false;

	try
	{

		MGMT_CO_MAP_ITER iter = _currentMgmtCoMap.find( dstMgmtCo );

		if( iter != _currentMgmtCoMap.end() )
		{
		   bRetVal = true;		   
		}
	}
	catch(...)	{}

	return bRetVal;
}

//******************************************************************************

bool 
DSTCGlobalSession::findMgmtCo( const DString& dstMgmtCo, MgmtCo*& pMgmtCo )
{
	bool bRetVal = false;
	pMgmtCo = NULL;

	try
	{

		MGMT_CO_MAP_ITER iter = _currentMgmtCoMap.find( dstMgmtCo );

		if( iter != _currentMgmtCoMap.end() )
		{
		   bRetVal = true;
		   pMgmtCo = (*iter).second;
		}
	}
	catch(...)	{}

	return bRetVal;
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCGlobalSession.cpp-arc  $
// 
//    Rev 1.15   07 Mar 2008 14:06:26   kovacsro
// IN#1172388 - added an overloaded findMgmtCo method to also return the MgmtCo pointer
// 
//    Rev 1.14   22 Feb 2008 11:02:44   kovacsro
// IN#1191514 - added findMgmtCo
// 
//    Rev 1.13   Mar 29 2005 17:07:50   smithdav
// Promote conditions before writing to the log files.
// 
//    Rev 1.12   Mar 29 2005 12:26:22   smithdav
// Added logging of conditions if MgmtCoRefresh fails.
// 
//    Rev 1.11   Nov 14 2004 14:32:44   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.10   Sep 29 2004 15:17:30   SMITHDAV
// Add guard by company on the inital aquire code to avoid multiple refreshers. Also, changed DString value parameters to reference parameters.
// 
//    Rev 1.9   Sep 27 2004 11:16:30   SMITHDAV
// Added code to allow MgmtCo to be initialized "on the fly" if it failed to init at startup.
// 
//    Rev 1.8   May 27 2004 16:29:18   SMITHDAV
// Changes to InterProcessData to move "global data" to the session level.
// 
//    Rev 1.7   Oct 09 2002 23:54:20   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.6   Aug 29 2002 12:55:30   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.5   22 May 2002 18:27:56   PURDYECH
// BFData Implementation
// 
//    Rev 1.4   10 Jan 2002 12:15:34   KOVACSRO
// Added getMgmtCo method. Supposed to be used only by Desktop.
// 
//    Rev 1.3   30 Jul 2001 15:08:50   SMITHDAV
// Added "Management company not avaialble" condition in aquireMgmtCo().
// 
//    Rev 1.2   11 Jul 2001 12:20:42   SMITHDAV
// Fix Global Session cleanup problems.
// 
//    Rev 1.1   09 Jul 2001 15:25:10   SMITHDAV
// Mgmt company refresh related changes.
// 
//    Rev 1.0   03 May 2001 14:48:56   SMITHDAV
// Initial revision.
 *
 */