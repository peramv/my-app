#ifndef INFRAEXCEPTION_HPP
#define INFRAEXCEPTION_HPP

#pragma message( "including "__FILE__ )

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

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif

#ifndef PLATFORM_H
   #include "platform.h"
#endif

// Import/Export resolution
#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif

//usually this exceptions are related to some internal server failure
//in handling the MT issues
class DICORE_LINKAGE InfraException : public std::exception
{
protected:
   LPVOID _lpMsgBuf;
public:
   InfraException();
   ~InfraException();
   LPTSTR getErrorMessage();
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
// $Log:   Y:/VCS/iFastAWD/inc/InfraException.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:31:46   kovacsro
//Initial revision.
//
//   Rev 1.0   Jun 28 2001 16:31:26   DT11159
// 
//
//

#endif
