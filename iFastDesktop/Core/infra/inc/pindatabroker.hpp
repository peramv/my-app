#ifndef PINDATABROKER_HPP
#define PINDATABROKER_HPP

#  pragma message( "including "__FILE__ )

/*
 * COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1999-2000 by DST Systems, Inc.
 */

/** @pkg DIPINDB */

#ifndef INCLUDED_IOSTREAM
#define INCLUDED_IOSTREAM
   #include <iostream>
#endif

#ifndef INCLUDED_MAP
#define INCLUDED_MAP
   #include <map>
#endif

#ifndef INCLUDED_STRING
#define INCLUDED_STRING
   #include <string>
#endif

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif

#ifndef DATAPROPERTIES_HPP
   #include "dataproperties.hpp"
#endif

#ifndef DATA_HPP
   #include "data.hpp"
#endif

#ifndef EVENTSEMAPHORE_HPP
   #include "eventsemaphore.hpp"
#endif

#ifndef BASEDBSECURITY_HPP
   #include "basedbsecurity.hpp"
#endif

#ifndef BASEDATABROKER_HPP
   #include "basedatabroker.hpp"
#endif

#undef DIPINDB_LINKAGE
#ifdef DIPINDB_DLL
   #define DIPINDB_LINKAGE CLASS_EXPORT
#else
   #define DIPINDB_LINKAGE CLASS_IMPORT
#endif

/**
 * A pinDataBroker handles requests to submit and receive Data 
 * objects.  The DataBroker encapsulates the source and format of 
 * the data which it sends and retrieves.  The data could
 * potentially be retrieved from a local file, a ViewManager view,
 * or a SQL call.
 *
 * The data broker will also bundle (or batch) multiple Data 
 * objects into one single submittal.  This will allow increased
 * efficiency and failure support for interdependent Data objects.
 *
 * The data broker will initially encapsulate the features of 
 * ViewManager.  By encapsulating ViewManager, the DataBroker
 * could potentially be reimplemented if ViewManager is replaced.
 *
 * The data broker is implemented using the "Singleton" pattern.
 * Therefore, there can only be one instance of PinDataBroker in 
 * existence at any time.  Also, getInstancePointer must be called
 * before the PinDataBroker can be used in any way.
 */
class DIPINDB_LINKAGE PinDataBroker : BaseDataBroker
{
   public:
      enum CONSTANTS {  LEN_OPERATOR_ID = 8,
                        LEN_SYSTEM      = 4,
                        LEN_VIEW_NAME   = 8,
                        LEN_PASSWORD    = 8,
                        LEN_NEWPASSWORD = 8,
                        DEFAULT_TIMEOUT = 90  };


   public:
      /**
       * Constructor
       * 
       * @param _operatorId
       * @param _systemId
       */
      PinDataBroker( const DString &_operatorId,
                     const DString &_systemId,
                     const DString & _password,
                     const DString & _newPassword );

      /**
       * Destructor
       */
      virtual ~PinDataBroker();

      /**
       * A request for a view call
       * 
       * @param sViewName - the name of the view on the host
       * @param parmsData - the input parameters
       * @param receivedData
       *                  - the location for the response data
       * @param overwriteFixedArea
       *                  - should the fixed area be read-only?
       * @param sHostName - the name of the host
       * @return 
       */
      SEVERITY receive( const DStringA &sViewName,
                    const Data &parmsData,
                    Data &receivedData,
                    bool overwriteFixedArea = true,
                    const DString &sHostName = NULL_STRING );

      /**
       * A request for a view call
       * 
       * @param sViewName - the name of the view on the host
       * @param parmsData - the input parameters
       * @param receivedData
       *                  - the location for the response data
       * @param pSecurity - a security object
       * @return 
       */
      SEVERITY receive( const DString &sViewName,
                        const Data &parmsData,
                        Data &receivedData,
                        BaseDBSecurity *pSecurity )
      {
         return receive( sViewName.asA(), parmsData, receivedData );
      }

#ifdef DST_UNICODE
      /**
       * A request for a view call
       * 
       * @param transId - the name of the view on the host
       * @param queryData - the input parameters
       * @param receivedData
       *                  - the location for the response data
       * @param pSecurity - a security object
       * @return 
       */
      virtual SEVERITY receive( const DStringA &transId,
                                const Data &queryData,
                                Data &receivedData,
                                BaseDBSecurity *pSecurity )
      {
         return receive( transId,
                         queryData,
                         receivedData );
      }
#endif
      
      /**
       * A request for a view call
       * 
       * @param sViewName - the name of the view on the host
       * @param receivedData
       *                  - the location for the response data
       * @param overwriteFixedArea
       *                  - should the fixed area be read-only?
       * @param sHostName - the name of the host
       * @return 
       */
      SEVERITY receive( const DStringA &sViewName,
                    Data &receivedData,
                    bool overwriteFixedArea = true,
                    const DString &sHostName = NULL_STRING );

      /**
       * Setter for operator Id
       * 
       * @param _operatorId
       */
      void setOperatorId( const DString &_operatorId );

      /**
       * Setter for CICS region
       * 
       * @param _systemId
       */
      void setSystem( const DString &_systemId );

   private: // attributes

      DString m_operatorId;
      DString m_systemId, m_password;

   private: // methods

      unsigned long getErrorCode( unsigned short viewRC );

      SEVERITY receive( const DStringA &sViewName,
                    const DString &sParms,
                    Data &receivedData,
                    bool overwriteFixedArea = true,
                    const DString &sHostName = NULL_STRING );

      SEVERITY receive( const DStringA &sViewName,
                        const char *uchParms,
                        unsigned long parmLength,
                        Data &receivedData,
                        bool overwriteFixedArea = true,
                        const DString &sHostName = NULL_STRING );

      PinDataBroker( const PinDataBroker &copy );
      PinDataBroker &operator=( const PinDataBroker &copy );
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
// $Log:   Y:/VCS/iFastAWD/inc/pindatabroker.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:32:26   kovacsro
//Initial revision.
// 
//    Rev 1.7   28 Jan 2002 16:45:12   dt14177
// added password/new password support
// 
//    Rev 1.6   Mar 05 2001 12:31:56   dt24433
// Fixes for UNICODE build compile.
// 
//    Rev 1.5   Mar 03 2001 15:16:58   dt24433
// Fixes for UNICODE build.
// 
//    Rev 1.4   30 Oct 2000 13:38:36   dt14177
// cleanup
// 
//    Rev 1.3   Sep 05 2000 08:25:26   dt17817
// Remove Certificate / Authentication
// 
//    Rev 1.2   Jul 06 2000 12:27:56   DT14177
// added 1.9 support
// 
//    Rev 1.0.1.1   Dec 14 1999 15:47:54   dtwk
// Polymorphic interface
// 
//    Rev 1.0.1.0   Jul 14 1999 16:09:56   DMUM
// Adapted for 1.7
// 
//    Rev 1.4   Feb 11 1999 15:42:00   DCYK
// Add support for binary DataElements.
// 
// 
//    Rev 1.3   Jan 28 1999 14:07:02   DMUM
// Check in for VCPP 6.0
// 
//    Rev 1.1   Dec 09 1998 13:43:30   DMUM
// Check in for DICORE
// 
//    Rev 1.17   May 20 1998 14:07:56   dcyk
// Change default timeout.
// 
// 
//    Rev 1.16   Nov 10 1997 15:02:44   dcyk
//  
// 
//    Rev 1.15   01 Oct 1997 15:24:22   dcyk
// Additional PlanTrac changes for callbacks
// and getting severity.
// 
// 
//    Rev 1.14   24 Sep 1997 13:43:44   dcyk
// Added additional PlanTrac functionality.
// 
// 
//    Rev 1.13   10 Sep 1997 12:10:58   dcyk
// Made changes for PlanTrac.
// Async view calls & more processing.
// 
// 
//    Rev 1.12   07 Aug 1997 15:09:36   dcyk
// Change USHORT, ULONG, UCHAR & UINT
// back to long forms for compatability.
// 
// 
//    Rev 1.11   24 Jul 1997 10:54:58   dcyk
// Removed coutErrorCode function.
// 
// 
//    Rev 1.10   08 Jul 1997 09:16:38   dcyk
// Updated documentation.
// 
// 
//    Rev 1.9   13 Jun 1997 18:24:54   dcyk
// Made receive return a bool.
// Added condition stuff.
// 
// 
//    Rev 1.8   Jun 08 1997 18:47:42   DTWK
// Add Certificate Authentication / Remove dependencies on class Returncode.
// 
//    Rev 1.7   05 Jun 1997 18:07:02   dcyk
// Changed default behavior of receive
// function to overwrite the fixed area of
// data objects passed in that already have
// repeat records.
// 
// 
//    Rev 1.6   May 29 1997 09:57:52   dcyk
// Add support for appending newly received
// repeats to the repeat area of the Data object
// passed in to the receive functions.
// 
// 
//    Rev 1.5   May 01 1997 08:47:42   dcyk
// Removed extra receive & update methods.
// 
// Added documentation.
// 
// 
//    Rev 1.4   Mar 14 1997 15:29:12   DPQD
// Made destructor private since it's a singleton.
//
//    Rev 1.3   Feb 11 1997 17:20:50   dcyk
// Added support for Rogue Wave STL.
//
//
//    Rev 1.2   Jan 15 1997 17:28:32   dcyk
// Modified receive functions to return a long,
// that is -1 on failure to communicate with
// VM, 0 on success, or > 0 if the view return
// code is between 900 and 1000.
//
// COUT on view call errors ( 900 < rc < 1000 ).
//
//
//    Rev 1.1   Jan 07 1997 09:34:08   dcyk
// Added overloaded receive function
// that takes a string view name and
// a Data object that holds the parms.
//
//
//    Rev 1.0   Dec 31 1996 11:39:34   DRUS
//
//

#endif // PinDataBroker_hpp
