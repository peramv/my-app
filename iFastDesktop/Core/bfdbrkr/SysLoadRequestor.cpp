//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   :  SysLoadRequestor.cpp
// ^AUTHOR :  David Smith
// ^DATE   :  September 2000
//
// ----------------------------------------------------------
#include <SrcPrag.h>
#include "SysLoadRequestor.hpp"
#include "FileRequestor.hpp"
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>




//******************************************************************************
SysLoadRequestor::SysLoadRequestor(FileRequestor &fileRequestor, BFRequestor &baseRequestor)
: _fileRequestor(fileRequestor),
_baseRequestor(baseRequestor)
{
}

//******************************************************************************
SysLoadRequestor::~SysLoadRequestor()
{
}

//******************************************************************************
SEVERITY 
SysLoadRequestor::receive( const BFRequest &request, BFData &queryData, BFData &receivedData, bool *outMoreAvailable /*= NULL*/ )
{
   SEVERITY severity;

   DString fileName;
   if( _fileRequestor.fileExists(request, queryData) && isArchiveValid( _fileRequestor.getFileName() ) )
      severity = _fileRequestor.receive( request, queryData, receivedData );
   else
   {
      severity = _baseRequestor.receive( request, queryData, receivedData );
      _fileRequestor.store(request, receivedData );
   }

   // never more records avaialble for sysload
   if( NULL != outMoreAvailable )
      outMoreAvailable = false;

   return(severity);
}

//******************************************************************************
bool 
SysLoadRequestor::isArchiveValid( const DString& fileName )
{

   int sysLoadFileHandle = i_open( fileName.c_str(), _O_RDONLY );

   bool sysLoadFileValid = false;
   if( sysLoadFileHandle != -1 )//File opened successfully
   {
      struct _stat fileStatusInfo;
      int result = _fstat( sysLoadFileHandle, &fileStatusInfo );
      if( result == 0 )//Status info successfully obtained
      {
         time_t currTime;
         time( &currTime );
         struct tm * pTmCurrTime = localtime( &currTime );
         //localtime returns a pointer to a STATIC struct, 
         //we have to save values before another call to localtime.
         int iCurrYear = pTmCurrTime->tm_year;
         int iCurrYDay = pTmCurrTime->tm_yday;
         struct tm * pTmFileChangeTime = localtime( &fileStatusInfo.st_mtime );

         if( pTmFileChangeTime->tm_yday == iCurrYDay
             && pTmFileChangeTime->tm_year == iCurrYear )
            sysLoadFileValid = true;
      }

      _close( sysLoadFileHandle );
   }

   return(sysLoadFileValid);
}
