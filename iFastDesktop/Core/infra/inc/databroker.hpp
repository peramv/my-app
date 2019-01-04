#ifndef DATABROKER_HPP
#define DATABROKER_HPP

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

#ifndef INCLUDED_MAP
#define INCLUDED_MAP
   #include <map>
#endif 

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif

#ifndef DSTRING_HPP
   #include "dstring.hpp"
#endif
   
#ifndef DATA_HPP
   #include "data.hpp"
#endif

#undef DIDBRKR_LINKAGE
#ifdef DIDBRKR_DLL
   #define DIDBRKR_LINKAGE CLASS_EXPORT
#else
   #define DIDBRKR_LINKAGE CLASS_IMPORT
#endif

/**
 * A data broker handles requests to submit and receive Data objects.  The
 * DataBroker encapsulates the source and format of the data which it sends
 * and retrieves.  The data could potentially be retrieved from a local file,
 * a ViewManager view, or a SQL call.
 * 
 * The data broker will also bundle (or batch) multiple Data objects into one
 * single submittal.  This will allow increased efficiency and failure support
 * for interdependent Data objects.
 * 
 * The data broker will initially encapsulate the features of ViewManager.  By
 * encapsulating ViewManager, the DataBroker could potentially be reimplemented
 * if ViewManager is replaced.
 * 
 * - stream operators????
 * - security link????
 * - carry standard header info (generate appname, etc.)????
 * - internal algorithms
 * - >32k handling, bundling
 * - avoid memory conflicts; support 1 or more instances of DB
 * 
 * @author DST Systems Inc
 * @deprecated This header is currently replaced by basedatabroker.hpp.
 */
class DIDBRKR_LINKAGE DataBroker
{
   public:
      DataBroker();
      virtual ~DataBroker();

      // buffer tells DB to buffer the received data
      bool receive( const Data &queryData,
                    Data &receivedData,
                    bool doBuffer = true );
      bool update( const Data &updateData );


   private:
      // Information placed in data headers???
      typedef std::map< DString, Data, std::less< DString > > DataMap;
      DataMap _buffers;

      DataBroker( const DataBroker &copy );
      DataBroker &operator=( const DataBroker &copy );
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
// $Log:   Y:/VCS/iFastAWD/inc/databroker.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:30:50   kovacsro
//Initial revision.
// 
//    Rev 1.5   Jan 16 2000 14:08:02   dtwk
// Update comments in JavaDoc format
// 
//    Rev 1.4   Dec 19 1999 09:28:18   dtwk
// Convert comments to JavaDoc format
// 
//    Rev 1.3   Mar 05 1999 10:20:54   DCYK
// Changes for I18N.
// 
// 
//    Rev 1.2   Jan 28 1999 14:05:52   DMUM
// Check in for VCPP 6.0
// 
//    Rev 1.1   Dec 09 1998 13:40:24   DMUM
// Check in for DICORE
// 
//    Rev 1.5   Nov 10 1997 15:00:00   dcyk
//  
// 
//    Rev 1.4   Jun 08 1997 18:47:34   DTWK
// Add Certificate Authentication / Remove dependencies on class Returncode.
//
//    Rev 1.3   Feb 11 1997 14:30:28   dcyk
// Added support for Rogue Wave's STL.
//
//
//    Rev 1.2   Nov 21 1996 14:37:02   DRUS
//
//
//    Rev 1.1   Nov 20 1996 17:07:10   DRUS
//
//
//    Rev 1.0   Nov 19 1996 10:03:08   DRUS
//
//

#endif // DataBroker_h
