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
// ^FILE   : HostTransactionContainer.cpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : September 1999
//
// ----------------------------------------------------------
//
// ^CLASS : HostTransactionContainer
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#define NOMINMAX

#include <bfutil\rtrevisiondefines.hpp>
RT_SOURCE_REVISION( "$Archive:   Y:/VCS/BF Core/bfcbo/HostTransactionContainer.cpp-arc  $", "$Revision:   1.9  $" )

#include <srcprag.h>
#include "hosttransactioncontainer.hpp"
#include <conditionmanager.hpp>
#include <bfutil\bfguard.hpp>
#include <limits>

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME   = I_( "HostTransactionContainer" );
   const I_CHAR * const GETINSTANCE = I_( "getInstance" );
}

namespace CND
{  // Conditions used
   extern const I_CHAR *BFBASE_CONDITION;
}

static std::map< DString, int >& getTrxnTypeMap()
{
   static std::map< DString, int > s_mapTrxnType;
   return( s_mapTrxnType );
}



int TRXN_TYPE::s_idNext_ = 1;
BFCritSec TRXN_TYPE::s_cs_;

TRXN_TYPE::TRXN_TYPE()
: id_( -1 )
, dstrName_( I_( "" ) )
{}

TRXN_TYPE::TRXN_TYPE( const I_CHAR* pszName )
: id_( -1 )
, dstrName_( pszName )
{
   BFGuard g( s_cs_ );

   // look in map of TRXN_TYPE names for an existing match
   std::map< DString, int >& rMap = getTrxnTypeMap();
   std::map< DString, int >::iterator it;
   if( ( it = rMap.find( dstrName_ ) ) == rMap.end() )
   {
      // no match.  Get a new id and add an entry to the map

      // the value of "NOT_PERSISTENT" should be the *highest* value.  this ensures that it will sort to the end
      // the value of "NO_TRXN" should be the *lowest* value.  this ensures that it will sort to the beginning
      if( I_( "NO_TRXN" ) == dstrName_ ) {
         id_ = 0;
      } else if( I_( "NOT_PERSISTENT" ) == dstrName_ ) {
         id_ = std::numeric_limits< int >::max();
      } else {
         id_ = ++s_idNext_;
      }
      rMap[ dstrName_ ] = id_;
   } 
   else
   {
      id_ = (*it).second;
   }
}

TRXN_TYPE::TRXN_TYPE( const TRXN_TYPE& rhs )
{
   *this = rhs;
}

TRXN_TYPE::~TRXN_TYPE()
{}

TRXN_TYPE& TRXN_TYPE::operator=( const TRXN_TYPE& rhs )
{
   if( this != &rhs )
   {
      id_ = rhs.id_;
      dstrName_ = rhs.dstrName_;
   }
   return( *this );
}

extern BFBASE_LINKAGE TRXN_TYPE NO_TRXN( I_( "NO_TRXN" ) );
extern BFBASE_LINKAGE TRXN_TYPE NOT_PERSISTENT( I_( "NOT_PERSISTENT" ) );


//******************************************************************************
HostTransactionContainer::HostTransactionContainer()
{
}

//******************************************************************************
HostTransactionContainer::~HostTransactionContainer()
{
   clearContainer();
}

//******************************************************************************
void HostTransactionContainer::addTransaction( const DString& strKey, 
                                               JData* jdata /*= NULL*/,
                                               BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/, 
                                               TRXN_TYPE trxnType /*= NO_TRXN*/,
                                               const DString& keyTypes /*=empty*/,
                                               long trxnGroup /*= NO_GROUP*/, 
                                               long trxnSubType /*= 0 */ )
{
   HostTransactionContainerIterator htcIter( this );

   if( jdata )
   {
      HTC_Key key( trxnGroup, trxnType, trxnSubType, objActivity, strKey, keyTypes );

      htcIter = std::make_pair( key, jdata );
   }
}

//******************************************************************************
HostTransactionContainerIterator HostTransactionContainer::getTransaction( const DString& dstrKey, 
                                                                           BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/, 
                                                                           TRXN_TYPE trxnType /*= NO_TRXN*/,
                                                                           const DString& keyTypes /*=empty*/,
                                                                           long trxnGroup /*= NO_GROUP*/, 
                                                                           long trxnSubType /*= 0*/ )
{
   HostTransactionContainerIterator htcIter( this );

   htcIter.begin();
   while( !htcIter.end() )
   {
      if( htcIter.strKey() == dstrKey &&
          htcIter.objActivity() == objActivity &&
          htcIter.trxnType() == trxnType &&
          htcIter.keyTypes() == keyTypes &&
          htcIter.trxnGroup() == trxnGroup &&
          htcIter.trxnSubType() == trxnSubType )
      {
         return(htcIter);
      }
      else
      {
         ++htcIter;
      }
   }
   return(NULL);
}

//******************************************************************************
void HostTransactionContainer::clearUncommitedTransactions()
{
   HostTransactionContainerIterator htcIter( this );

   htcIter.begin();
   while( !htcIter.end() )
   {
      if( !htcIter.isCommited() )
      {
         htcIter.remove();
      }
      else
      {
         ++htcIter;
      }
   }
}

//******************************************************************************
void HostTransactionContainer::clearContainer()
{
   HostTransactionContainerIterator htcIter( this );

   htcIter.begin();
   while( !htcIter.end() )
   {
      htcIter.remove();
   }
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfcbo/HostTransactionContainer.cpp-arc  $
//
//   Rev 1.9   Apr 23 2003 13:48:48   PURDYECH
//The "NO_TRXN" transaction type should always get an internal ID of 0 and the "NOT_PERSISTENT" transaction type should always get an internal ID of <max int>.  This will guarantee proper sorting of these transaction types.
 * 
 *    Rev 1.8   Feb 07 2003 10:48:44   PURDYECH
 * Changed TRXN_TYPE from enum to class so that projects can define unique ones in the application classes.
 * 
 *    Rev 1.7   Oct 09 2002 17:40:12   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.6   03 Jul 2001 16:23:10   SMITHDAV
 * Add revision constants.
 * 
 *    Rev 1.5   03 May 2001 16:35:18   SMITHDAV
 * Session restructuring.
 * 
 *    Rev 1.4   Mar 07 2001 16:04:34   MCNABBGL
 * added getTransaction method (based on key)
 * 
 *    Rev 1.3   Jan 16 2001 13:44:46   OLTEANCR
 * changed addTransaction( ) to use jdata
 * 
 *    Rev 1.2   Aug 10 2000 09:00:20   DT24433
 * changed to not be a singleton - hosted by WorkSessionDetails now
 * 
 *    Rev 1.1   Apr 12 2000 19:47:44   DT24433
 * removed base_conditions.hpp
 * 
 *    Rev 1.0   Feb 15 2000 10:57:32   SMITHDAV
 * Initial revision.
// 
//    Rev 1.12   Jan 14 2000 09:35:26   POPESCUS
// added a clear uncommited trxn method
// 
//    Rev 1.11   Jan 07 2000 15:54:22   POPESCUS
// just checking in...
// 
//    Rev 1.10   Jan 07 2000 07:55:04   BUZILA
// fix
// 
//    Rev 1.9   Jan 07 2000 07:49:20   BUZILA
// added clearContainer() method
// 
//    Rev 1.8   Dec 19 1999 17:15:40   BUZILA
// added revision area
 * 
 */



