#ifndef BASEREQUEST_HPP
#define BASEREQUEST_HPP

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

// Import/Export resolution
#undef DIDBRKR_LINKAGE
#ifdef DIDBRKR_DLL
   #define DIDBRKR_LINKAGE CLASS_EXPORT
#else
   #define DIDBRKR_LINKAGE CLASS_IMPORT
#endif

class DString;

/**
 *  Common backend identification class
 */
class DIDBRKR_LINKAGE BaseRequest
{
public:
   virtual ~BaseRequest( ) {};

   /**
    * Class handles identification of backend request
    *
    * @returns DString - Identification name for request to backend
    */
   virtual const DString & getId( ) const = 0;
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
// $Log:   Y:/VCS/iFastAWD/inc/BaseRequest.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:30:04   kovacsro
//Initial revision.
//
//   Rev 1.0   May 18 2001 15:52:32   DT11159
// 
//
//

#endif
