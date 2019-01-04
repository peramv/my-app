#ifndef ABSTRACTREQUEST_HPP
#define ABSTRACTREQUEST_HPP

#pragma message( "including "__FILE__ )

/******************************************************************************
 *
 * COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1999-2001 by DST Systems, Inc.
 *
 *
 *******************************************************************************/

#ifndef PLATFORM_H
   #include "platform.h"
#endif

#ifndef BASEREQUEST_HPP
   #include "baserequest.hpp"
#endif

#ifndef DSTRING_HPP
   #include "dstring.hpp"
#endif

// Import/Export resolution
#undef DIDBRKR_LINKAGE
#ifdef DIDBRKR_DLL
   #define DIDBRKR_LINKAGE CLASS_EXPORT
#else
   #define DIDBRKR_LINKAGE CLASS_IMPORT
#endif

/**
 *  Standard backend identification class
 */
class DIDBRKR_LINKAGE AbstractRequest : public BaseRequest
{
public:

   /**
    * Creates class with passed in identification string
    *
    * @param id - Name of backend request
    */
   AbstractRequest( const DString & id );
   virtual ~AbstractRequest( ) { };

   /**
    * Class handles identification of backend request
    *
    * @returns DString - Identification name for request to backend
    */
   virtual const DString & getId() const { return m_id; };

private:
   const DString m_id;
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
// $Log:   Y:/VCS/iFastAWD/inc/AbstractRequest.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:29:40   kovacsro
//Initial revision.
//
//   Rev 1.0   May 18 2001 15:51:52   DT11159
// 
//
//

#endif
