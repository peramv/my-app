// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if _MSC_VER > 1000
   #pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN      // Exclude rarely-used stuff from Windows headers

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <process.h>
#include <winerror.h>
#include <winsock.h>
#include <iostream>
#include <assert.h>

#pragma warning( disable : 4018 4097 4146 4251 4663 4786 )
#pragma warning( disable : 4275 )

#ifndef COMMONPORT_H
   #include <CommonPort.h>
#endif
#ifndef CONDITIONMANAGER_HPP
   #include <ConditionManager.hpp>
#endif


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbps/stdafx.h-arc  $
//
//   Rev 1.4   Oct 05 2009 07:51:46   purdyech
//Get rid of warning messages
//
//   Rev 1.3   Nov 17 2004 15:03:28   PURDYECH
//PET910 - .NET Conversion
//
//   Rev 1.2   Oct 09 2002 23:53:48   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.1   04 Dec 2000 11:38:40   SMITHDAV
//Add console connection monitoring support.
//
//   Rev 1.0   Apr 04 2000 10:28:10   POPESCUS
//Initial revision.
 * 
 *    Rev 1.0   Feb 16 2000 12:49:56   POPESCUS
 * Initial revision.
 * 
 */