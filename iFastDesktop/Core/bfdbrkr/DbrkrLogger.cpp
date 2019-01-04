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
// ^FILE   : DbrkrLogger.cpp
// ^AUTHOR : Chin Hsu
// ^DATE   : June 2001
//
// ^CLASS    : DbrkrLogger
// ^INHERITS FROM :          
//
// ^CLASS DESCRIPTION : 
//    
//
//******************************************************************************

#include <SrcPrag.h>
#include "BFReadBuffer.hpp"
#include "BFWriteBuffer.hpp"
#include <configmanager.hpp>
#include <bfdata\BFData.hpp>
#include "DbrkrLogger.hpp"

//const I_CHAR *const APPEND_FILE =      I_( "AppendFile" );
//const I_CHAR *const COMPLETE_LOG =     I_( "CompleteLog" );
//const I_CHAR *const DATABROKER =       I_( "DataBroker" );
//const I_CHAR *const DATAPATH =         I_( "DataPath" );
//const I_CHAR *const DEBUG =            I_( "Debug" );
//const I_CHAR *const DEBUG_OPTION =     I_( "DebugOptions");
//const I_CHAR *const DEBUG_PATH =       I_( "DebugPath" );
const I_CHAR* const ON =               I_( "1" );
const I_CHAR* const YES =              I_( "Y" );
//const I_CHAR *const RAW_REQUEST_LOG =  I_( "RawRequestLog" );
//const I_CHAR *const RAW_RESPONSE_LOG = I_( "RawResponseLog" );


bool s_bIsEnabled = false;
bool DbrkrLogger::isEnabled() {
   static bool bInit = false;
   if( !bInit ) {
      bInit = true;
      DString dstrDebug = GetConfigValueAsString( I_("MFDSTC") /*ConfigManager::getApplication()*/, I_("Support"), I_("ViewLog_Enable") );

      s_bIsEnabled = (dstrDebug == ON || dstrDebug == YES);
   }
   return( s_bIsEnabled );
}

void DbrkrLogger::enable( bool b )
{
   s_bIsEnabled = b;
}

DString s_strLogDir;
const DString& DbrkrLogger::getLogDir()
{
   static bool bInit = false;
   if( !bInit ) {
      bInit = true;
      setLogDir( GetConfigValueAsString( I_("MFDSTC") /*ConfigManager::getApplication()*/, I_("Support"), I_("ViewLog_Path") ) );
   }
   return( s_strLogDir );
}

void DbrkrLogger::setLogDir( const DString& s )
{
   s_strLogDir = s;
   if( s_strLogDir == I_("") ) {
      s_strLogDir = I_(".");
   }
}

bool s_bIsComplete;
bool DbrkrLogger::isCompleteLogging()
{
   static bool bInit = false;
   if( !bInit ) {
      bInit = true;
      DString dstrComplete = GetConfigValueAsString( I_("MFDSTC") /* ConfigManager::getApplication() */, I_("Support"), I_("ViewLog_Complete") );
      setCompleteLogging( dstrComplete == ON || dstrComplete == YES);
   }
   return( s_bIsComplete );
}

void DbrkrLogger::setCompleteLogging( bool b )
{
   s_bIsComplete = b;
}

bool s_bIsAppending;
bool DbrkrLogger::isAppending()
{
   static bool bInit = false;
   if( !bInit ) {
      bInit = true;
      DString dstrAppend = GetConfigValueAsString( I_("MFDSTC") /* ConfigManager::getApplication() */, I_("Support"), I_("ViewLog_Append") );
      setAppending( dstrAppend == ON || dstrAppend == YES );
   }
   return s_bIsAppending;
}

void DbrkrLogger::setAppending( bool b )
{
   s_bIsAppending = b;
}

bool s_bIsLogRequest;
bool DbrkrLogger::logRequest()
{
   static bool bInit = false;
   if( !bInit ) {
      bInit = true;
      DString s = GetConfigValueAsString( I_("MFDSTC") /* ConfigManager::getApplication() */, I_("Support"), I_("ViewLog_RawRequest") );
      setLogRequest(s == ON || s == YES);
   }
   return( s_bIsLogRequest );
}

void DbrkrLogger::setLogRequest( bool b )
{
   s_bIsLogRequest = b;
}

bool s_bIsLogResponse;
bool DbrkrLogger::logResponse()
{
   static bool bInit = false;
   if( !bInit ) {
      bInit = true;
      DString s = GetConfigValueAsString( I_("MFDSTC") /* ConfigManager::getApplication() */, I_("Support"), I_("ViewLog_RawResponse") );
      setLogResponse(s == ON || s == YES);
   }
   return( s_bIsLogResponse );
}

void DbrkrLogger::setLogResponse( bool b )
{
   s_bIsLogResponse = b;
}




//******************************************************************************
DbrkrLogger::DbrkrLogger()
: _bLogging( false )
, _bFixedOutFile( false )
, _requestOut( false )
, _responseOut( false )
{
}

//******************************************************************************
DbrkrLogger::DbrkrLogger( const DString& fileName, bool bAppend )
: _bLogging( false )
, _bFixedOutFile ( false )
{
   openFile( fileName, bAppend );
}

//******************************************************************************
DbrkrLogger::~DbrkrLogger( ) 
{
   if( _bLogging )
   {
      _outFile << std::endl;
      _outFile << "********************************************************************" << std::endl;
      _outFile.close();
      if( _bFixedOutFile )
      {
         _fixedOutFile << std::endl;      
         _fixedOutFile.close();
      }
   }
}

//******************************************************************************
bool DbrkrLogger::setFileName( const DString &fileName, bool bAppend /* = false */ )
{
   return( openFile( fileName, bAppend ) );
}

//******************************************************************************
void DbrkrLogger::logData ( const BFData& data, const BFFieldId& idField )
{
   if( _outFile.is_open() )
   {
      DString dstrFieldName, dstrFieldValue;
      dstrFieldName = data.getFieldNameFromId ( idField );
      data.getElementValue ( idField, dstrFieldValue );
      writeData ( dstrFieldName + I_("=") + dstrFieldValue );
   }
}

//******************************************************************************
void DbrkrLogger::logData ( const DString& fieldName, const DString& fieldValue  )
{
   if( _outFile.is_open() )
   {
      writeData ( fieldName + I_("=") + fieldValue );
   }
}

//******************************************************************************
void DbrkrLogger::logData ( const DString& dstrOutput )
{
   if( _outFile.is_open() )
   {
      writeData ( dstrOutput );
   }
}

//******************************************************************************
void DbrkrLogger::logData ( const BFWriteBuffer* pRequestBuffer, const BFReadBuffer* pResponseBuffer, const DString& dstrLabel )
{
   if( _rawLog.is_open() )
   {
      if( _requestOut && _responseOut )
      {
         _rawLog << dstrLabel.asA().c_str() << std::endl << std::endl;
         _rawLog << pRequestBuffer->getString().c_str() << std::endl << std::endl;
         if( pResponseBuffer )
            _rawLog << pResponseBuffer->getString().c_str() << std::endl << std::endl;
         _rawLog.flush();
      }
      else if( _requestOut )
      {
         _rawLog << dstrLabel.asA().c_str() << std::endl << std::endl;
         _rawLog << pRequestBuffer->getString().c_str() << std::endl << std::endl;    
         _rawLog.flush();
      }
      else if( _responseOut )
      {
         _rawLog << dstrLabel.asA().c_str() << std::endl << std::endl;
         if( pResponseBuffer )
            _rawLog << pResponseBuffer->getString().c_str() << std::endl << std::endl;
         _rawLog.flush();
      }
   }
}

//******************************************************************************
void DbrkrLogger::writeData ( const DString& output )
{
   if( _bLogging && _outFile.is_open() )
   {
      if( output != NULL_STRING )
      {
         _outFile << output.asA().c_str() << std::endl;
         _outFile.flush();
      }
      if( _bFixedOutFile )
      {
         _fixedOutFile << output.asA().c_str() << std::endl;
         _fixedOutFile.flush();
      }
   }
}

//******************************************************************************
bool DbrkrLogger::openFile( const DString &fileName, bool bAppend )
{
   if( _outFile.is_open() )
   {
      // if either file is already open then we can't open them again!
      return( false );
   }

//   DString dstrDebug = GetConfigValueAsString( I_("MFDSTC") /* ConfigManager::getApplication() */, I_("Support"), I_("ViewLog_Enable") );
//   DString sysLoadPath = GetConfigValueAsString( I_("MFDSTC") /* ConfigManager::getApplication() */, I_("Support"), I_("ViewLog_Path") );

   _bLogging = isEnabled();
   if( _bLogging )
   {
      DString tempFile = fileName;
      int pos = tempFile.pos ( I_(".") );
      if( pos > 0 )
      {
         tempFile = tempFile.left ( pos );
      }
      else
      {
         tempFile = fileName;
      }
      DStringA fileNameA(getLogDir() + I_("\\") + tempFile + I_(".txt"));
      if( bAppend || isAppending() )
      {
         _outFile.open( fileNameA.data(), std::ios_base::app );   
      }
      else
      {
         _outFile.open( fileNameA.data(), std::ios_base::trunc );
      }
//      DString dstrComplete = GetConfigValueAsString( ConfigManager::getApplication(), I_("Support"), I_("ViewLog_Complete") );
      _bFixedOutFile = isCompleteLogging();

      if( _bFixedOutFile )
      {
         DStringA fileNameB = getLogDir() + I_("\\") + I_("Log.txt");
         _fixedOutFile.open ( fileNameB.data(), std::ios_base::app );
      }

      DString dstrRAWRequestLog = GetConfigValueAsString( I_("MFDSTC") /* ConfigManager::getApplication() */, I_("Support"), I_("ViewLog_RawRequest") );
      DString dstrRAWResponseLog = GetConfigValueAsString( I_("MFDSTC") /* ConfigManager::getApplication() */, I_("Support"), I_("ViewLog_RawResponse") );
      _requestOut = logRequest();
      _responseOut = logResponse();

      if( _requestOut || _responseOut )
      {
         DStringA fileNameB = getLogDir() + I_("\\") +  I_( "rawLog.txt" );
         _rawLog.open ( fileNameB.data(), std::ios_base::app ); 
      }
   }
   return( true );
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/core/bfdbrkr/DbrkrLogger.cpp-arc  $
//
//   Rev 1.17   Nov 03 2009 03:53:52   purdyech
//PTS1894529 - Couldn't use new GetConfigValueAs...() functions with non MFDSTC registry hives.  This only affected MFS Users in Toronto using XML configuration files.
//
//   Rev 1.16   Feb 20 2009 14:48:14   purdyech
//ZTS Revision 6
//
//   Rev 1.15   Feb 06 2009 14:52:06   purdyech
//Interim CheckIn for ZTS Support (Chris is goin' on vacation!)
// 
//    Rev 1.14   Oct 09 2002 17:40:42   PURDYECH
// New PVCS Database
// 
//    Rev 1.13   Aug 29 2002 12:49:26   PURDYECH
// ClientLocale and Field corrections
// 
//    Rev 1.12   May 28 2002 12:15:40   PURDYECH
// BFData Implementation - Phase II
// 
//    Rev 1.11   22 Mar 2002 15:17:10   PURDYECH
// BFData integration
// 
//    Rev 1.10   29 Nov 2001 13:19:30   HSUCHIN
// bug fix for null response buffer
// 
//    Rev 1.9   26 Oct 2001 12:10:42   HSUCHIN
// change RTSRequestLog to RawRequestLog etc.
// 
//    Rev 1.8   26 Oct 2001 11:04:36   HSUCHIN
// added support to log raw transaction request/response.  New logData function which takes BFWriteBuffer/BFReadBuffer as params.
// 
//    Rev 1.7   18 Sep 2001 15:20:46   PURDYECH
// Get STUB_DATA working again.
// 
//    Rev 1.6   19 Jul 2001 11:57:08   HSUCHIN
// added boolean flag in contructor to override append mode
// 
//    Rev 1.5   29 Jun 2001 13:36:32   HSUCHIN
// bug fix
// 
//    Rev 1.4   28 Jun 2001 14:23:28   HSUCHIN
// added fixed log capabilities and other enhancements
// 
//    Rev 1.3   Jun 26 2001 12:54:38   PURDYECH
// Infrastructure Release 1.9 Integration.
// 
//    Rev 1.2   14 Jun 2001 14:39:10   HSUCHIN
// new override and reduced number of output files
// 
//    Rev 1.1   13 Jun 2001 17:30:58   HSUCHIN
// changed to check registry for logging flag rather than environment
*/
