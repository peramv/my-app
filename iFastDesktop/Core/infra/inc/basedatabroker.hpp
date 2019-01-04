#ifndef BASEDATABROKER_HPP
#define BASEDATABROKER_HPP

/** 
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1999 by DST Systems, Inc.
 */

/**@pkg DIDBRKR */ 

#pragma message( "including "__FILE__ )

#ifndef INCLUDED_STRING
#define INCLUDED_STRING
   #include <string>
#endif

#ifndef INCLUDED_MAP
#define INCLUDED_MAP
   #include <map>
#endif 

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif

#ifndef CONDITION_HPP
   #include "condition.hpp"
#endif

#ifndef DATA_HPP
   #include "data.hpp"
#endif

#ifndef BASEDBSECURITY_HPP
   #include "basedbsecurity.hpp"
#endif

#undef DIDBRKR_LINKAGE
#ifdef DIDBRKR_DLL
   #define DIDBRKR_LINKAGE CLASS_EXPORT
#else
   #define DIDBRKR_LINKAGE CLASS_IMPORT
#endif

/**
 * Implements a simple polymorphic interface for all DataBrokers. The idea is to
 * make it easy for an application to "swap out" communications methods (brokers)
 * with as little change to source code as possible
 * 
 * @author DST Systems Inc
 */
class DIDBRKR_LINKAGE BaseDataBroker
{
public:
   BaseDataBroker();
   virtual ~BaseDataBroker();

   /**
    * Basic communication method that all databrokers must support
    * 
    * @param transId - Text string specifying a transaction id (i.e. the view name
    *                for TA2000DataBroker)
    * @param queryData - The input parameters for the request
    * @param receivedData - Receives the response for the request
    * @param pSecurity - an object that contains security information needed to
    *                  make the request
    * @return implementation defined, but NO_CONDITION is generally assumed to
    *         be successful
    */
   virtual SEVERITY receive( const DString &transId,
                             const Data &queryData,
                             Data &receivedData,
                             BaseDBSecurity *pSecurity ) = 0;

#ifdef DST_UNICODE
   /**
    * Basic communication method that all databrokers must support
    * 
    * @param transId - text string specifying a transaction id (i.e. the view name
    *                for TA2000DataBroker)
    * @param queryData - the input parameters for the request
    * @param receivedData - receives the response for the request
    * @param pSecurity - an object that contains security information needed to
    *                  make the request
    * @return Implementation defined, but NO_CONDITION is generally assumed to
    *         be successful
    */
   virtual SEVERITY receive( const DStringA &transId,
                             const Data &queryData,
                             Data &receivedData,
                             BaseDBSecurity *pSecurity ) = 0;
#endif

private:

   BaseDataBroker( const BaseDataBroker &copy );
   BaseDataBroker &operator=( const BaseDataBroker &copy );
};



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
// $Log:   Y:/VCS/iFastAWD/inc/basedatabroker.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:30:00   kovacsro
//Initial revision.
// 
//    Rev 1.3   Jan 16 2000 14:07:50   dtwk
// Update comments in JavaDoc format
// 
//    Rev 1.2   Dec 19 1999 09:28:08   dtwk
// Convert comments to JavaDoc format
//

#endif
