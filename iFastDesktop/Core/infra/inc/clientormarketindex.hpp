#ifndef CLIENTORMARKETINDEX_HPP
#define CLIENTORMARKETINDEX_HPP

#  pragma message( "including "__FILE__ )


/** 
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1996-2000 by DST Systems, Inc.
 */

/**@pkg DICORE */    

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif

#ifndef DSTRING_HPP
   #include "dstring.hpp"
#endif

#ifndef CLIENTLOCALE_HPP
   #include "clientlocale.hpp"
#endif

#undef DIDBRKR_LINKAGE
#ifdef DIDBRKR_DLL
   #define DIDBRKR_LINKAGE CLASS_EXPORT
#else
   #define DIDBRKR_LINKAGE CLASS_IMPORT
#endif

class ClientOrMarketIndex
{
public:

   unsigned long ulClientId;
   unsigned long ulMarketId;
   unsigned long ulMaskOrSubId;
   DString dstrLanguageCode;

   ClientOrMarketIndex();

   ClientOrMarketIndex( unsigned long ulClientIdIn,
                        unsigned long ulMarketIdIn,
                        unsigned long ulMaskOrSubIdIn, 
                        const DString& dstrLanguageCodeIn );

   ClientOrMarketIndex( const ClientOrMarketIndex& copy );

   ClientOrMarketIndex& operator=( 
      const ClientOrMarketIndex& copy );

   bool operator<( const ClientOrMarketIndex& compare ) const;

};


#endif

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
// $Log:   Y:/VCS/iFastAWD/inc/clientormarketindex.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:30:24   kovacsro
//Initial revision.
//
//   Rev 1.2   23 Oct 2000 13:03:00   dt14177
//cleanup
//
//   Rev 1.1   Sep 05 2000 06:05:34   dt17817
//- Remove Certificate/Authenticator
//- Fix threadsafety of client/market
//- Add "null" property value support
//
//
//   Rev 1.0   Aug 09 2000 08:35:58   dtwk
// 
// 

