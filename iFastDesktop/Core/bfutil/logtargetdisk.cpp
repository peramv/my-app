#include "stdafx.h"
#include <bf/log/logtargetdisk.hpp>

using namespace bf::log;


DString LogTargetDisk::getRealFileName() const
{
   DString d;
   d = dstrPath_;
   d += I_("\\");
   d += dstrFile_;
   return d;
}

void LogTargetDisk::setFileName( const DString& dstrFile )
{
   if( dstrFile != dstrFile_ ) {
      dstrFile_ = dstrFile;
      badFileName_ = false;
      if( !isSuspended() ) {
         suspend();
         restart();
      }
   }
}

void LogTargetDisk::setPathName( const DString& dstrPath )
{
   if( dstrPath != dstrPath_ ) {
      dstrPath_ = dstrPath;
      badFileName_ = false;
      if( !isSuspended() ) {
         suspend();
         restart();
      }
   }
}

void LogTargetDisk::setFilePath( const DString& dstrPath, const DString& dstrFile )
{
   if( dstrFile != dstrFile_ ||
       dstrPath != dstrPath_ ) {
      dstrFile_ = dstrFile;
      dstrPath_ = dstrPath;
      badFileName_ = false;
      //dstrFQP_ = I_("");
      if( !isSuspended() ) {
         suspend();
         restart();
      }
   }
}

FILE* LogTargetDisk::getFile() {
   if( NULL == pFile_ && !badFileName_ && !bSuspend_)
   {
      if( dstrFile_.empty() ) {
         dstrFile_ = getFileName( NULL );
      }
      if( dstrPath_.empty() ) {
         dstrPath_ = I_(".");
      }
      DString dstrFQP = dstrPath_;
      dstrFQP += I_("\\");
      dstrFQP += dstrFile_;

      const I_CHAR* pszOpenMode = getOpenMode( dstrFQP, bAppend_, bUnicode_ );
      pFile_ = _wfopen( dstrFQP.c_str(), pszOpenMode );
      if( NULL == pFile_ ) {
         badFileName_ = true;
      }
   }
   return( pFile_ );
}


const I_CHAR* LogTargetDisk::getOpenMode( const DString& dstrFQP, bool bAppend, bool bUnicode ) const
{
   static I_CHAR* apszOpenMode[][2] = 
   { 
      { I_("w"), I_("wb")},
      { I_("a"), I_("ab")}
   };
   return( apszOpenMode[ bAppend ][ bUnicode ] );
}


LogTargetDisk* LogTargetDisk::create( const I_CHAR* pszPath, const I_CHAR* pszFile ) {
   return( new LogTargetDisk( pszPath, pszFile, false ) );
}
LogTargetDisk* LogTargetDisk::createUnicode( const I_CHAR* pszPath, const I_CHAR* pszFile ) 
{
   return( new LogTargetDisk( pszPath, pszFile, true ) );
}

LogTargetDisk::~LogTargetDisk()
{
   if( NULL != pFile_ )
   {
      fclose( pFile_ );
      pFile_ = NULL;
   }
}

void LogTargetDisk::write( const DString& str )
{
   if( true == bSuspend_ ) return;
   getFile();
   if( NULL != pFile_ ) {
      i_fputs( str.c_str(), pFile_ );
      flush();
   }
}

void LogTargetDisk::suspend()
{
   bSuspend_ = true;
   if( NULL != pFile_ )
   {
      flush();
      fclose( pFile_ );
      pFile_ = NULL;
      bAppend_ = true;     // next time we will use the 'append' mode to reopen the file
   }
}

void LogTargetDisk::restart() 
{
   bSuspend_ = false;
   getFile();  
}


DString LogTargetDisk::getFileName( const I_CHAR* pszHint ) const
{
   I_CHAR* pszUser = i_getenv(I_("USERNAME"));
   I_CHAR* pszComputer = i_getenv(I_("COMPUTERNAME"));

   // default name of log file is name of .exe file with .log instead
   I_CHAR szBuf[ _MAX_PATH ];
   I_CHAR szFName[ _MAX_FNAME ] = I_("");
   if( 0 != ::GetModuleFileNameW( NULL, szBuf, sizeof( szBuf ) / sizeof( szBuf[0] ) ) ) {
      I_CHAR szDrive[ _MAX_DRIVE ];
      I_CHAR szDir[ _MAX_DIR ];
      I_CHAR szExt[ _MAX_EXT ];
      _wsplitpath( szBuf, szDrive, szDir, szFName, szExt );
   }
   SYSTEMTIME st;
   GetLocalTime(&st);
   i_sprintf(szBuf,I_("%s_%s_%s_%04d%02d%02d_%02d%02d%02d.log"),
                   szFName,
                   pszUser == NULL ? I_("Anon") : pszUser,
                   pszComputer == NULL ? I_("NoMachine") : pszComputer,
                   st.wYear,st.wMonth,st.wDay,
                   st.wHour,st.wMinute,st.wSecond );

   return( DString( szBuf ) );
}

void LogTargetDisk::flush() { 
   if( false == bSuspend_ )
   {
      fflush( pFile_ );
   }
}




