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
//    Copyright 2002 International Financial
//
//
//******************************************************************************
//
// ^FILE   :  FTPConnection.cpp
// ^AUTHOR :  
// ^DATE   :  
//
//******************************************************************************

#include "stdafx.h"

#include <uibase\conditionmessagedialog.h>
#include <afxinet.h>
#include "ftpconnection.hpp"

namespace
{
   const I_CHAR * const CLASSNAME = I_( "FTPConnection" );
   const int MAX_BUFFER = 4096;
   const int FTP_PORT = 21;
}

namespace CND
{
   extern const long ERR_CANNOT_RESOLVE_FTP_FROM_NAME;
   extern const long ERR_CONNECTING_TO_FTP;
   extern const long ERR_UNKNOWN_FTP_OPEN_FILE_ERROR;
   extern const long ERR_FTP_FILE_READ_FAILED;
   extern const long ERR_UNKNOWN_FTP_READ_ERROR;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

FTPConnection::FTPConnection( const DString& connectionName, const DString& hostAddress, int port, const DString& userId, const DString& pwd )
: _connected( false )
, _pCInternetSession( NULL )
, _pCFtpConnection( NULL )
, _pCInternetFile( NULL )
, _connectionName( connectionName )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING )
   connect(hostAddress, port, userId, pwd);
}

FTPConnection::~FTPConnection()
{
   if( _connected )
   {
      try
      {
         disconnect();
      }
      catch( ... )
      {
      }
   }
}

//////////////////////////////////////////////////////////////////////
// Methods
//////////////////////////////////////////////////////////////////////

void
FTPConnection::connect( const DString& hostAddress, int port, const DString& userId, const DString& pwd)
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("Connect") );
//CP20030425   CInternetSession* pCInternetSession = NULL;

   try
   {
      _pCInternetSession = new CInternetSession ( _connectionName.c_str() );
      _pCFtpConnection = _pCInternetSession->GetFtpConnection ( hostAddress.c_str(), userId.c_str(), pwd.c_str(), port );
      _connected = true;
   }
   catch( CInternetException* pEx )
   {
      TCHAR szErr[MAX_BUFFER];
      bool bMsgExists = false;
      if( pEx->GetErrorMessage(szErr, MAX_BUFFER) )
      {
         bMsgExists = true;
      }
      pEx->Delete();

      if( bMsgExists )
      {
         //Error Connecting to FTP HOST - %ERROR%.
         DString strIDI;
         addIDITagValue( strIDI, I_("ERROR"), DStringA ( szErr ) );         
         DISPLAYCONDITIONFROMFILEIDI( CND::ERR_CONNECTING_TO_FTP, strIDI );
      }
      else
      {
         //"Unable to resolve FTP host by name."
         DISPLAYCONDITIONFROMFILE( CND::ERR_CANNOT_RESOLVE_FTP_FROM_NAME );
      }
      _pCFtpConnection = NULL;
      _connected = false;      
   }
}

void
FTPConnection::disconnect()
{
   _pCFtpConnection->Close();
   _connected = false;
   delete _pCInternetSession;
}

void
FTPConnection::ReadFile( const DString& dstrFile, DString& dstrOutFile )
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OpenFile") );
   try
   {
      if( _pCInternetFile )
      {
         _pCInternetFile->Close();
      }
      _pCInternetFile = _pCFtpConnection->OpenFile( dstrFile.c_str(), GENERIC_READ, FTP_TRANSFER_TYPE_ASCII );
      if( !_pCInternetFile )
      {
         DISPLAYCONDITIONFROMFILE( CND::ERR_UNKNOWN_FTP_OPEN_FILE_ERROR);
         return;
      }

      unsigned int nRead = MAX_BUFFER;
      char buf [MAX_BUFFER];   
      DStringA d;
      while( nRead == MAX_BUFFER )
      {
         nRead = _pCInternetFile->Read ( buf, MAX_BUFFER );             
         d.append ( buf, nRead );
      }     

/* Can't get ReadString to work :(
   CString buf;   
   DStringA d;   
   char* ch;
   while ( _pCInternetFile->ReadString ( buf ) )
   {      
      if ( buf ) {
         buf.TrimRight ( _T("\r\n") );
         buf += _T("\r\n");
         ch = (char*)(LPCTSTR) buf;      
         d.append ( ch );
      }
   } */
      dstrOutFile = d;

      _pCInternetFile->Close ();
      _pCInternetFile = NULL;
   }
   catch( CInternetException *pEx )
   {
      I_CHAR szErr[1024];
      bool bMsgExists = false;
      if( pEx->GetErrorMessage(szErr, MAX_BUFFER) )
      {
         bMsgExists = true;
      }
      pEx->Delete();

      if( bMsgExists )
      {
         //FTP file read failed - %ERROR%.
         DString strIDI;
         addIDITagValue( strIDI, I_("ERROR"), DStringA ( szErr ) );         
         DISPLAYCONDITIONFROMFILEIDI( CND::ERR_FTP_FILE_READ_FAILED, strIDI);
      }
      else
      {
         //Unknown FTP file read error.
         DISPLAYCONDITIONFROMFILE( CND::ERR_UNKNOWN_FTP_READ_ERROR);
      }
   }
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/FTPConnection.cpp-arc  $
// 
//    Rev 1.3   Apr 25 2003 12:28:30   PURDYECH
// Fixed some memory leaks
// 
//    Rev 1.2   Mar 21 2003 18:36:44   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.1   Dec 10 2002 09:55:46   HSUCHIN
// bug fix for _connected flag
// 
//    Rev 1.0   Dec 08 2002 22:16:18   HSUCHIN
// Initial Revision
*/