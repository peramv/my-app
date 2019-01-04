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

#define DICORE_DLL

#ifndef INFRAEXCEPTION_HPP
   #include "infraexception.hpp"
#endif

InfraException::InfraException()
{
   ::FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                    NULL, GetLastError(), MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ), // Default language
                    (LPTSTR)&_lpMsgBuf, 0, NULL );
}

InfraException::~InfraException()
{
   ::LocalFree( _lpMsgBuf );
}

LPTSTR InfraException::getErrorMessage()
{
   return (LPTSTR)_lpMsgBuf;
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
// $Log:   Y:/VCS/iFastAWD/dicore/InfraException.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:19:56   kovacsro
// Initial revision.
//
//   Rev 1.0   Jun 28 2001 16:22:28   DT11159
// 
//
//
