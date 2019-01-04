/*
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 2001 by DST Systems, Inc.
 */

#define DIDBRKR_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#ifndef CLIENTORMARKETINDEX_HPP
   #include "clientormarketindex.hpp"
#endif

ClientOrMarketIndex::ClientOrMarketIndex() :
   ulClientId( 0 ), ulMarketId( 0 ), ulMaskOrSubId( 0 ),
   dstrLanguageCode( I_( "" ) )
{
}


ClientOrMarketIndex::ClientOrMarketIndex(
   unsigned long ulClientIdIn,
   unsigned long ulMarketIdIn,
   unsigned long ulMaskOrSubIdIn,
   const DString& dstrLanguageCodeIn ) :
      ulClientId( ulClientIdIn ),
      ulMarketId( ulMarketIdIn ),
      ulMaskOrSubId( ulMaskOrSubIdIn ),
      dstrLanguageCode( dstrLanguageCodeIn )
{
}


ClientOrMarketIndex::ClientOrMarketIndex( const ClientOrMarketIndex& copy )
{
   ( *this ) = copy;
}


ClientOrMarketIndex& ClientOrMarketIndex::operator=(
   const ClientOrMarketIndex& copy )
{
   ulClientId = copy.ulClientId;
   ulMarketId = copy.ulMarketId;
   ulMaskOrSubId = copy.ulMaskOrSubId;
   dstrLanguageCode = copy.dstrLanguageCode;
   return *this;
}


bool ClientOrMarketIndex::operator<(
   const ClientOrMarketIndex& compare ) const
{
   if ( ulClientId < compare.ulClientId )
   {
      return true;
   }

   if ( ulClientId > compare.ulClientId )
   {
      return false;
   }

   if ( ulMarketId < compare.ulMarketId )
   {
      return true;
   }

   if ( ulMarketId > compare.ulMarketId )
   {
      return false;
   }

   if ( ulMaskOrSubId < compare.ulMaskOrSubId )
   {
      return true;
   }

   if ( ulMaskOrSubId > compare.ulMaskOrSubId )
   {
      return false;
   }

   if ( dstrLanguageCode < compare.dstrLanguageCode )
   {
      return true;
   }

   return false;
}


//************************************************************************
//              Revision Control Entries
//************************************************************************
//
// Name:
//    %PM%
//    %PID%
//
// Description:
//    %PD%
//
// Design Parts:
//    %PIRP%
//
// Last Changed:
//    %PO%  -  %PRT%
//
// Changes:
//    %PLA%
//
//
// $Log:   Y:/VCS/iFastAWD/didbrkr/clientormarketindex.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:21:16   kovacsro
// Initial revision.
//
//   Rev 1.3   May 21 2001 13:50:04   DT21858
//Now includes srcprag.h correctly
//
//   Rev 1.2   Oct 05 2000 12:39:16   dt17817
//Fix for substitutions overrides not being found if more than one override
//
//   Rev 1.1   Sep 05 2000 06:19:40   dt17817
//- Remove Certificate/Authenticator
//- Fix threadsafety of client/market
//- Add "null" property value support
//
//
//   Rev 1.0   Aug 09 2000 08:36:40   dtwk
//
//

