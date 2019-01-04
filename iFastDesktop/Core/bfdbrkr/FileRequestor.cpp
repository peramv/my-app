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
// ^FILE   :  FileRequestor.cpp
// ^AUTHOR :  David Smith
// ^DATE   :  September 2000
//
// ----------------------------------------------------------
#define NOMINMAX
#include <srcprag.h>
#include "filerequestor.hpp"
#include "bfrequest.hpp"
#include "filerequestbuffer.hpp"
#include "fileresponsebuffer.hpp"
#include "filestorebuffer.hpp"
#include <bfutil\bfhrtimer.hpp>
#include <configmanager.hpp>
#include <assert.h>

#include <io.h>
#include <fstream>
#include <tchar.h>

#include <bfutil\bfguard.hpp>

HANDLE hMutex = ::CreateMutex( NULL, TRUE, NULL );

namespace
{
   const int MAX_FILE_NAME_CHARACTERS  = 60;
   const int DATA_BUFFER_LENGTH        = 65534;
}

namespace CND
{
   extern const I_CHAR *BFDBRKR_CONDITION;
   extern const long ERR_MALFORMED_FILE_RESPONSE_BUFFER;
}
FileRequestor::MAP_REQUESTS FileRequestor::s_mapRequests_;
BFCritSec FileRequestor::s_csInitMapRequests_;

//******************************************************************************
FileRequestor::FileRequestor(const DString &pathName, bool keyed, bool bOffline )
: _pathName( pathName )
, _fileName( I_( "" ) )
, _keyed( keyed )
, _bOffline( bOffline )
, _requestTime( 0 )
{
   checkPath();

   _dstrStubDataIni = _pathName;
   _dstrStubDataIni += ConfigManager::getApplication().asA();
   _dstrStubDataIni += "_stubdata.ini";

   _dstrViewIni = _pathName;
   _dstrViewIni += ConfigManager::getApplication().asA();
   _dstrViewIni += "_viewctl.ini";

   _dstrGlobalViewIni = _pathName;
   _dstrGlobalViewIni += ConfigManager::getApplication().asA();
   _dstrGlobalViewIni += "_globalviewctl.ini";
}

//******************************************************************************
FileRequestor::FileRequestor(const FileRequestor &copy)
: _pathName( copy._pathName )
, _fileName( copy._fileName )
, _dstrStubDataIni( copy._dstrStubDataIni )
, _dstrViewIni( copy._dstrViewIni )
, _keyed( copy._keyed )
, _bOffline( copy._bOffline )
, _requestTime( copy._requestTime )
{
   checkPath();
}

//******************************************************************************
FileRequestor::~FileRequestor()
{
}

//******************************************************************************
BFWriteBuffer *
FileRequestor::createRequestBuffer(const BFRequest &request) const
{
   return(new FileRequestBuffer(request));
}

//******************************************************************************
SEVERITY 
FileRequestor::receiveBuffer( const BFRequest &request, const BFWriteBuffer *queryBuffer, BFReadBuffer **receivedBuffer, const BFData* pQuery )
{

   if( _bOffline )
   {
      SEVERITY sev = getOfflineData( request, queryBuffer, receivedBuffer );
      return( sev );
   }

   DStringA astrFileName = getFileName( request, queryBuffer );

   //open the file only to see if exist
   std::ifstream inFileTest( astrFileName.c_str() );

   if( !inFileTest )
   {  //file don't exist
      //to avoid the Demo crash, we MUST read from another file with the name == first part of the original 
      //...file name (the part regarding the view name)
      DString strTemp;
      int iPosition = astrFileName.find( I_CHAR( '-' ) );
      if( iPosition == DString::npos )
      {  //the fileName has only the view part
         iPosition = astrFileName.find( I_CHAR( '.' ) );
         if( iPosition == DString::npos )
         {
            assert(0);
            //error : "The DOT is missing from file name
            return(NO_CONDITION);
         }
      }
      strTemp = astrFileName.substr( 0, iPosition );
      strTemp += I_CHAR( '*' ); //wildcard for search

      long hFile;
      struct _tfinddata_t c_file;   //Unicode

      if( ( hFile = _tfindfirst( strTemp.c_str(), &c_file ) ) == -1L ) //Unicode
      {
         assert(0);
         //error : "Don't exist any file for this view"
         return(NO_CONDITION);

      }
      strTemp = c_file.name;
      _findclose( hFile );

      DString strFileName = _pathName + strTemp;
      astrFileName = strFileName;
   }
   else
   {  //file exist
      //keep the same file name

      if( inFileTest.is_open() )
      {
         inFileTest.close();
      }
   }

   std::ifstream inFile( astrFileName.c_str() );
   if( !inFile )
   {
      assert(0);
      //error : "The file don't exist"
      return(NO_CONDITION);
   }
   if( !inFile.is_open() )
   {
      assert(0);
      //error : "The file cannot be open"
      return(NO_CONDITION);
   }

   char buffer[ DATA_BUFFER_LENGTH + 1 ];
   DString dataArea = I_("");;
   int buffLen;

   DStringA astrTemp = I_("");

   while( !inFile.eof() )
   {
      memset( buffer, 0, DATA_BUFFER_LENGTH + 1 );
      inFile.read( buffer, DATA_BUFFER_LENGTH );
      astrTemp += buffer;
      buffLen = astrTemp.size();
   }
   if( inFile.bad() )
   {
      // Read from data file failed
      inFile.close();
   }
   else
   {
      inFile.close();
   }

   *receivedBuffer = new FileResponseBuffer( astrTemp );
   BFHRTimer t;
   unsigned long delay = getDelay( request );
   if( 0 != delay ) Sleep( delay );
   _requestTime = t.elapsed();

   return(NO_SEVERITY);
}

//******************************************************************************
void FileRequestor::store( const BFRequest &request, const BFData &storeData ) const
{
   FileStoreBuffer storeBuffer;
   formatBuffer(storeData, &storeBuffer );

   std::ofstream outFile;
   outFile.open( _fileName.asA().c_str(), std::ios_base::out | std::ios_base::trunc );
   if( outFile.is_open() )
   {
      outFile << storeBuffer.getString();
   }
   else
   {
      DString error;
   }
   outFile.close();
}

//******************************************************************************
const DString &
FileRequestor::getFileName( const BFRequest &request, const BFData &queryData ) const
{
   FileRequestBuffer requestBuffer(request);
   formatBuffer( queryData, &requestBuffer );
   return(getFileName( request, &requestBuffer ));
}

//******************************************************************************
const DString &
FileRequestor::getFileName( const BFRequest &request, const BFWriteBuffer *queryBuffer ) const
{
   if( _fileName == I_( "" ) )
   {

      DString strValue;
      bool bIsEndOfBuffer = false;

      DStringA dstrFile(I_( "" ));
      DStringA requestBuffer = queryBuffer->getString();

      char achFiles[8192];
      DWORD rc = GetPrivateProfileStringA( request.getId().asA().c_str(), 
                                           NULL,
                                           "",
                                           &achFiles[0],
                                           sizeof(achFiles),
                                           _dstrStubDataIni.c_str() );
      // get the size of the section, read the whole thing in
      if( rc != 0 )
      {
         char szBuffer[32768];
         char *pEnd = &achFiles[0] + rc;
         char *pFile = &achFiles[0];

         while( pFile < pEnd )
         {
            rc = GetPrivateProfileStringA( request.getId().asA().c_str(), 
                                           pFile,
                                           "",
                                           szBuffer,
                                           sizeof(szBuffer), 
                                           _dstrStubDataIni.c_str() );
            if( requestBuffer == szBuffer )
            {
               // found our match!
               dstrFile = _pathName;
               dstrFile += pFile;
               break;
            }
            pFile += strlen( pFile ) + 1;
         }
      }

      if( dstrFile == "" )
      {
         DStringA fName = genFileName();
         dstrFile = _pathName;
         dstrFile += fName;
         rc = WritePrivateProfileStringA( request.getId().asA().c_str(), fName.c_str(), requestBuffer.c_str(), _dstrStubDataIni.c_str() );
      }

      _fileName = dstrFile;
   }

   return(_fileName);
}

//*****************************************************************************************
BFRequestor *
FileRequestor::clone() const
{
   return(new FileRequestor(*this)); 
}


//******************************************************************************
bool 
FileRequestor::fileExists( const BFRequest &request, const BFData &queryData ) const
{
   FileRequestBuffer requestBuffer(request);
   formatBuffer(queryData, &requestBuffer );
   DStringA fileNameA = getFileName( request, &requestBuffer );

   std::ifstream inFile( fileNameA.c_str() );

   if( inFile )
      return(true);
   else
      return(false);
}

//******************************************************************************
unsigned long FileRequestor::getRequestTime() const
{
   return(_requestTime);
}

//******************************************************************************
void 
FileRequestor::checkPath()
{
   int iRet = 0;

   // add trailing path seperator if required
   if( _pathName[_pathName.length()] != I_CHAR('\\') )
      _pathName.padRight( _pathName.length() + 1, I_CHAR('\\') );

   // recursively make directory if required.
   DString strRemaining( _pathName );
   int iBackShlashPos = strRemaining.pos( I_("\\") );

   strRemaining = strRemaining.right( strRemaining.length() - iBackShlashPos - 1 );
   int iCurrentPos = iBackShlashPos;

   while( ( iBackShlashPos = strRemaining.pos( I_("\\") ) ) > 0 )
   {
      strRemaining = strRemaining.right( strRemaining.length() - iBackShlashPos - 1 );
      iCurrentPos += iBackShlashPos + 1;
      if( ( iRet = i_mkdir( _pathName.left( iCurrentPos ).c_str() ) ) != 0 && errno != EEXIST )
         return;
   }
}

//******************************************************************************
DStringA FileRequestor::genFileName() const
{
   int iLast = GetPrivateProfileIntA( "FileSequence",
                                      "NextIndex",
                                      0,
                                      _dstrStubDataIni.c_str() );
   char idx[9];
   sprintf( idx, "%06d", iLast + 1);
   WritePrivateProfileStringA( "FileSequence",
                               "NextIndex",
                               idx,
                               _dstrStubDataIni.c_str() );
   char buf[9];
   sprintf( buf, "sm%06d", iLast );
   return( buf );
}

SEVERITY FileRequestor::getOfflineData( const BFRequest &request, const BFWriteBuffer *queryBuffer, BFReadBuffer **receivedBuffer )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BFDBRKR_CONDITION,
                          I_( "FileRequestor" ),
                          I_( "getOfflineData( const BFRequest &, const BFWriteBuffer *, BFReadBuffer ** )" ) );

   // make sure that all sections are loaded from disk
   {
      // protect the loading of the map
      if( s_mapRequests_.empty() )
      {

         char achRequests[32768];

         // get all of the Request Sections ...
         DWORD rc = GetPrivateProfileStringA( NULL, 
                                              NULL,
                                              "",
                                              &achRequests[0],
                                              sizeof( achRequests ),
                                              _dstrStubDataIni.c_str() );

         if( rc != 0 )
         {
            char *pEndSection = &achRequests[0] + rc;
            char *pSection = &achRequests[0];
            char achFiles[8192];

            while( pSection < pEndSection )
            {
               rc = GetPrivateProfileStringA( pSection,
                                              NULL,
                                              "",
                                              &achFiles[0],
                                              sizeof(achFiles),
                                              _dstrStubDataIni.c_str() );


               // get the size of the section, read the whole thing in
               if( rc != 0 )
               {
                  MAP_STUBDATA *pMapStubData = new MAP_STUBDATA;
                  DStringA dstrRequest( pSection );
                  s_mapRequests_[ dstrRequest ] = pMapStubData;

                  char szBuffer[32768];
                  char *pEndFile = &achFiles[0] + rc;
                  char *pFile = &achFiles[0];

                  while( pFile < pEndFile )
                  {
                     rc = GetPrivateProfileStringA( pSection,
                                                    pFile,
                                                    "",
                                                    szBuffer,
                                                    sizeof(szBuffer), 
                                                    _dstrStubDataIni.c_str() );

                     // insert this into the MAP_STUBDATA
                     if( rc != 0 )
                     {
                        // read the file into memory to match request/response
                        DStringA dstrFile = _pathName;
                        dstrFile += pFile;

                        char buffer[ DATA_BUFFER_LENGTH + 1 ];
                        DString dataArea = I_("");;
                        int buffLen;

                        DStringA astrTemp = I_("");

                        std::ifstream inFile( dstrFile.c_str() );
                        if( inFile.is_open() )
                        {
                           while( !inFile.eof() )
                           {
                              memset( buffer, 0, DATA_BUFFER_LENGTH + 1 );
                              inFile.read( buffer, DATA_BUFFER_LENGTH );
                              astrTemp += buffer;
                              buffLen = astrTemp.size();
                           }
                           inFile.close();
                           (*pMapStubData)[ szBuffer ] = astrTemp;
                        }
                     }
                     pFile += strlen( pFile ) + 1;
                  }
               }
               pSection += strlen( pSection ) + 1;
            }
         }
      }
   }

   // find the request map entry
   ITER_REQUESTS iterR = s_mapRequests_.find( request.getId().asA() );
   if( iterR != s_mapRequests_.end() )
   {
      MAP_STUBDATA *pMapStubData = (*iterR).second;
      if( NULL != pMapStubData )
      {
         ITER_STUBDATA iterS = pMapStubData->find( queryBuffer->getString() );
         if( iterS != pMapStubData->end() )
         {
            *receivedBuffer = new FileResponseBuffer( (*iterS).second );
            BFHRTimer t;
            unsigned long delay = getDelay( request );
            if( 0 != delay ) Sleep( delay );
            _requestTime = t.elapsed();
         }
         else
         {
            ADDCONDITIONFROMFILE( CND::ERR_MALFORMED_FILE_RESPONSE_BUFFER );
         }
      }
      else
      {
         ADDCONDITIONFROMFILE( CND::ERR_MALFORMED_FILE_RESPONSE_BUFFER );
      }
   }
   else
   {
      ADDCONDITIONFROMFILE( CND::ERR_MALFORMED_FILE_RESPONSE_BUFFER );
   }
   return( GETCURRENTHIGHESTSEVERITY() );
}

//******************************************************************************
unsigned long FileRequestor::getDelay( const BFRequest &request ) const
{
   // assume a default delay time of 25ms if no time is found

   int delayTime = GetPrivateProfileIntA( request.getId().asA().c_str(), 
                                          "DelayTime",
                                          25,
                                          _dstrViewIni.c_str() );


   char achScale[256];
   DWORD rc = GetPrivateProfileStringA( "GlobalViewControl", 
                                        "TimeScale",
                                        "",
                                        &achScale[0],
                                        sizeof(achScale),
                                        _dstrGlobalViewIni.c_str() );
   // get the size of the section, read the whole thing in
   if( rc != 0 )
   {
      // we found our scale factor!
      DStringA dstrScale( achScale );
      dstrScale.stripAll();

      double dblScale = atof( dstrScale.c_str() );
      dblScale = std::max( 0.0, dblScale ); // scale factor must be at least 0
      delayTime = static_cast< int >( static_cast< double >(delayTime) * dblScale );
   }

   return( delayTime );   
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/core/bfdbrkr/FileRequestor.cpp-arc  $
//
//   Rev 1.15   Mar 27 2009 10:17:04   purdyech
//Added more JMSProperties to ZTS request messages.
//
//   Rev 1.14   Oct 22 2004 08:56:48   PURDYECH
//PET910 - .NET Conversion Fixes
// 
//    Rev 1.13   Mar 11 2003 10:14:48   PURDYECH
// Changes for general use of boost libraries.
// 
//    Rev 1.12   Oct 09 2002 17:40:44   PURDYECH
// New PVCS Database
// 
//    Rev 1.11   Aug 29 2002 12:49:28   PURDYECH
// ClientLocale and Field corrections
// 
//    Rev 1.10   Jul 05 2002 08:53:22   PURDYECH
// Fixed include files
// Removed commented-out code.
// 
//    Rev 1.9   22 May 2002 17:56:08   PURDYECH
// BFData Implementation
// 
//    Rev 1.8   22 Mar 2002 15:17:12   PURDYECH
// BFData integration
// 
//    Rev 1.7   Oct 05 2001 10:09:22   PURDYECH
// Added the TimeScale .ini entry to alter the delay time for a view by an arbitrary factor.
// 
//    Rev 1.6   27 Sep 2001 09:06:34   PURDYECH
// ERR_MALFORMED_FILE_RESPONSE_BUFFER is not an imported symbol.
// 
//    Rev 1.5   25 Sep 2001 13:22:48   PURDYECH
// Stub File Fixes.
// 
//    Rev 1.4   18 Sep 2001 15:20:44   PURDYECH
// Get STUB_DATA working again.
// 
//    Rev 1.3   Jun 12 2001 16:38:06   DINACORN
// Sync. up with SSB (1.0.1.1)
// 
//    Rev 1.2   10 May 2001 12:12:58   SMITHDAV
// Sync-up 1.0.1.0.
// 
 */

