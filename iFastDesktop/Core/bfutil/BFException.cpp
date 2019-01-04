#include "stdafx.h"

#include "BFException.hpp"

BFException::BFException()
{
   ::FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                    NULL, 
                    GetLastError(), 
                    MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ), // Default language
                    (LPTSTR)&_lpMsgBuf, 
                    0, 
                    NULL );
}

BFException::BFException( LPTSTR message )
{
   _lpMsgBuf = message;
}

BFException::~BFException()
{
   ::LocalFree( _lpMsgBuf );
}

LPTSTR BFException::getErrorMessage()
{
   return(_lpMsgBuf);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfutil/BFException.cpp-arc  $
// 
//    Rev 1.3   Oct 09 2002 17:41:12   PURDYECH
// New PVCS Database
// 
//    Rev 1.2   May 28 2002 12:15:52   PURDYECH
// BFData Implementation - Phase II
// 
//    Rev 1.1   03 Oct 2001 15:09:54   SMITHDAV
// Syncronization changes and Job Queue changes
// 
//    Rev 1.0   Jun 28 2001 09:48:00   PURDYECH
// Initial revision.
// 
//    Rev 1.0   Jun 26 2001 12:01:02   PURDYECH
// Initial revision.
 * 
 *    Rev 1.2   Feb 16 2000 13:09:46   POPESCUS
 * Initial revision
 * 
 * 
 */