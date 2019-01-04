#ifndef CONFIGMACRO_H
#define CONFIGMACRO_H

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

#ifndef CONFIGMANAGER_HPP
   #include "configmanager.hpp"
#endif

#define CONFIG_MGR( n ) ( ConfigManager::getManager( n ) )


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
// $Log:   Y:/VCS/iFastAWD/inc/configmacro.h-arc  $
//
//   Rev 1.0   28 Jan 2008 13:30:40   kovacsro
//Initial revision.
// 
//    Rev 1.3   20 Oct 2000 17:41:06   dt14177
// cleanup
// 
//    Rev 1.2   Jan 28 1999 14:05:42   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.1   Dec 09 1998 13:40:10   DMUM
// Check in for DICORE
//
//    Rev 1.3   Nov 10 1997 13:58:28   DSZD
// CHANGE INCLUSION GUARD TO UPPERCASE.
//
//    Rev 1.2   Nov 10 1997 12:59:44   DSZD
// Configuration extension. IMPORT/EXPORT.
// MACRO inclusion
//
//    Rev 1.1   27 Aug 1997 10:43:24   dmum
// Changed how the application is treated
//
//    Rev 1.0   13 Jun 1997 10:08:08   dmum
//
//
//

#endif // CONFIGMACRO_H

