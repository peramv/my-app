/*
 *
 * COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 2001 by DST Systems, Inc.
 *
 *
 */
 
#define DIVIEW_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#include <stdlib.h>
#include <windows.h>
#include <wincon.h>
#include <time.h>

#include <rpc.h>

#ifndef CRITICALSECTION_HPP
#include "criticalsection.hpp"
#endif

#ifndef VMV002REQUEST_HPP
#include "vmv002request.hpp"
#endif

static MutexSemaphore sema4;

static char szMACAddress[ 20 ] = "";

typedef struct _ASTAT_
{
    ADAPTER_STATUS adapt;
    NAME_BUFFER    NameBuff [30];
}ASTAT, * PASTAT;

ASTAT Adapter;


const char * VMV002Request::getMACAddress()
{
   CriticalSection cs( sema4 );
   if ( 0 == szMACAddress[ 0 ] )
   {
      NCB ncb;
      UCHAR uRetCode;
   
      memset( &ncb, 0, sizeof(ncb) );
      ncb.ncb_command = NCBRESET;
      ncb.ncb_lana_num = 0;
   
      uRetCode = Netbios( &ncb );
   
      memset( &ncb, 0, sizeof(ncb) );
      ncb.ncb_command = NCBASTAT;
      ncb.ncb_lana_num = 0;
   
      memcpy( ( char * ) ncb.ncb_callname,  
              "*               ", NCBNAMSZ );
      ncb.ncb_buffer = (unsigned char *) &Adapter;
      ncb.ncb_length = sizeof(Adapter);
   
      uRetCode = Netbios( &ncb );
      if ( uRetCode == 0 )
      {
          sprintf( szMACAddress, 
                   "%02X-%02X-%02X-%02X-%02X-%02X",
                  Adapter.adapt.adapter_address[0],
                  Adapter.adapt.adapter_address[1],
                  Adapter.adapt.adapter_address[2],
                  Adapter.adapt.adapter_address[3],
                  Adapter.adapt.adapter_address[4],
                  Adapter.adapt.adapter_address[5] );
      }
   }
   return szMACAddress;
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
// $Log:   Y:/VCS/iFastAWD/diview/vmv002requesthelpers.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:24:16   kovacsro
// Initial revision.
//
//   Rev 1.4   02 Aug 2001 16:01:24   DT14177
//fixed revision comment block
//
//   Rev 1.3   30 Jul 2001 14:01:36   DT14177
//fixed buffer size and changed strcpy to
//memcpy
//
//
//   Rev 1.1.1.1   30 Jul 2001 13:28:38   DT14177
//fixed buffer size and changed strcpy to
//memcpy
// 

