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
//    Copyright 2000 by DST Systems, Inc.
//
//

#define DICORE_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#ifndef MUTEXSEMAPHORE_HPP
   #include "mutexsemaphore.hpp"
#endif

#ifndef CRITICALSECTION_HPP
   #include "criticalsection.hpp"
#endif

#ifndef BINFILEHEADER_HPP
   #include "binfileheader.hpp"
#endif

#ifndef CONDITION_HPP
   #include "condition.hpp"
#endif

#ifndef CONDITIONMANAGER_HPP
   #include "conditionmanager.hpp"
#endif

#ifndef CONFIGMANAGER_HPP
   #include "configmanager.hpp"
#endif

#include <iostream>
#include <memory>

static DString s_repoPath;

void SetGlobalRepositorySourcePath( const DString& path ) {
   s_repoPath = path;
}

const DString& GetGlobalRepositorySourcePath() {
   return s_repoPath;
}

using namespace std;

static const unsigned long VERSION_NUM_LENGTH = 6;
static const unsigned long CLIENT_LENGTH = 5;
static const unsigned long CRC_LENGTH = 6;

static const short CHAR_SIZE = sizeof( wchar_t );

static MutexSemaphore mutexInit;

BinFileHeader * BinFileHeader::s_pInstance = 0;
const I_CHAR * BINFILEHEADER_NAME = I_( "DICORE" );
const I_CHAR * ALLOWED_VERSION = I_( "000300" );


const I_CHAR BinFileHeader::s_achNoMarket[] = I_( "No Market" );
const I_CHAR BinFileHeader::s_achNoClient[] = I_( "No Client" );

const unsigned long BinFileHeader::s_ulNoMarket = 1;
const unsigned long BinFileHeader::s_ulNoClient = 1;


MsgPair en_usBinFileHeader[] =
{
   {
      BinFileHeader::BINFILEHEADER_UNABLE_TO_OPEN,
      I_( "Error opening bin file: %FILE%." ),
      I_( "Check to make sure file exists, file access permissions are " )
         I_( "correct, and path (in registry) is correct." )
   },

   {
      BinFileHeader::BINFILEHEADER_UNABLE_FIND_REPOSITORY_NAME,
      I_( "Error finding path and name of the repository file. " )
         I_( "Looking for DataBroker (ConfigManager), " )
         I_( "DataPath (Configuration), RepositorySource (Key)" ),
      I_( "Check to make sure the registry setup is correct." )
   },

   {
      BinFileHeader::BINFILEHEADER_MISSING_MARKET_FOR_CLIENT,
      I_( "Error reading bin file %FILE%.  The client with id, %CLIENT%, " )
         I_( "specifies a market with id, %MARKET%, but the market id does " )
         I_( "not exist in the bin file!" ),
      I_( "Check bin file for corruption." )
   },

   {
      BinFileHeader::BINFILEHEADER_READ_SIZE_FAILED,
      I_( "Error reading bin file %FILE%.  Expected to read %EXPECTED% bytes" )
         I_( " at offset %OFFSET%, but only was able to read " )
         I_( "%RECEIVED% bytes." ),
      I_( "Check bin file for corruption." )
   },

   {
      BinFileHeader::BINFILEHEADER_INVALID_BIN_VERSION,
      I_( "The version of the bin file, %FILE%, is incorrect. Expected " )
         I_( "version %EXPECTEDVERSION%, but found version %FILEVERSION%." ),
      I_( "Check bin file for corruption or regenerate the bin file." )
   },

   {
      BinFileHeader::BINFILEHEADER_MARKET_NOT_FOUND,
      I_( "The market requested, %MARKET%, was not found in the bin file." ),
      I_( "Check bin file for corruption or regenerate the bin file." )
   },

   {
      BinFileHeader::BINFILEHEADER_CLIENT_NOT_FOUND,
      I_( "The client requested, %CLIENT%, for market, %MARKET%, was not " )
         I_( "found in the bin file." ),
      I_( "Check bin file for corruption or regenerate the bin file." )
   } ,

   {
      BinFileHeader::BINFILEHEADER_DEFAULT_MARKET_NOT_FOUND,
      I_( "The default market specified in the bin file, %MARKET%, " )
         I_( "was not found in the bin file." ),
      I_( "Check bin file for corruption or regenerate the bin file." )
   },

   {
      BinFileHeader::BINFILEHEADER_DEFAULT_CLIENT_NOT_FOUND,
      I_( "The default client specified in the bin file, %CLIENT%, for " )
         I_( "market, %MARKET%, was not found in the bin file." ),
      I_( "Check bin file for corruption or regenerate the bin file." )
   }
};


Condition::mapCodePagesToLanguages languagesMapForBinFileHeader[] =
{
   {
      I_( "C" ), en_usBinFileHeader
   },

   // End slot marger
   {
      NULL, NULL

   }
};


BinFileHeader * BinFileHeader::getInstance()
{
   if ( s_pInstance )
   {
      return s_pInstance;
   }

   CriticalSection crit( mutexInit );

   if ( s_pInstance )
   {
      return s_pInstance;
   }

   s_pInstance = new BinFileHeader();

   return s_pInstance;
}


BinFileHeader::BinFileHeader()
{
   m_dstraFileName =
       GetElementalConfigValueAsString( I_( "DataBroker" ),
                                        I_( "DataPath" ),
                                        I_( "RepositorySource" ) );

   if( m_dstraFileName == "" ) {
      m_dstraFileName = GetGlobalRepositorySourcePath().asA();
   }

   m_ulFileOffset = 0;

   if ( !m_dstraFileName.length() )
   {
      DString idiStr;

      THROWELEMENTALIDI(
         BINFILEHEADER_NAME,
         I_( "BinFileHeader::BinFileHeader()" ),
         BinFileHeader::BINFILEHEADER_UNABLE_FIND_REPOSITORY_NAME,
         languagesMapForBinFileHeader,
         idiStr );
   }

   FILE *infile = fopen( m_dstraFileName.c_str(), "rb" );

   if ( !infile )
   {
      DString idiStr = I_( "FILE=" );
      idiStr += DString( m_dstraFileName ).c_str();

      THROWELEMENTALIDI( BINFILEHEADER_NAME,
                         I_( "BinFileHeader::BinFileHeader()" ),
                         BinFileHeader::BINFILEHEADER_UNABLE_TO_OPEN,
                         languagesMapForBinFileHeader,
                         idiStr );
   }
   else
   {
      try
      {
         // get the byte-order flags
         _readString( infile, 1, m_dstrByteOrder );

         // get the version number flags
         _readString( infile, VERSION_NUM_LENGTH, m_dstrVersionNumber );

         // check to make sure the version is ok
         if ( m_dstrVersionNumber != ALLOWED_VERSION )
         {
            DString idiStr = I_( "FILE=" );
            idiStr += DString( m_dstraFileName ).c_str();
            idiStr += I_( ";FILEVERSION=" );
            idiStr += m_dstrVersionNumber;
            idiStr += I_( ";EXPECTEDVERSION=" );
            idiStr += ALLOWED_VERSION;

            THROWELEMENTALIDI( BINFILEHEADER_NAME,
                               I_( "BinFileHeader::BinFileHeader()" ),
                               BinFileHeader::BINFILEHEADER_INVALID_BIN_VERSION,
                               languagesMapForBinFileHeader,
                               idiStr );
         }

         // Get the crc text
         // Eventually check the crc when it's written out correctly by bin file
         _readString( infile, CRC_LENGTH, m_dstrCRC );

         // get the read-only flag
         _readString( infile, 1, m_dstrReadOnly );

         //////////////// Markets

         // Read in the number of markets
         long lNumMarkets = _readNum( infile, 5 );

         // Read in the markets
         long lIndex = 0; 
         for (lIndex = 0; lIndex < lNumMarkets; ++lIndex )
         {
            unsigned long ulMarketId = _readNum( infile, 10 );
            unsigned long ulMarketNameLength = _readNum( infile, 5 );
            DString dstrMarket;
            _readString( infile, ulMarketNameLength, dstrMarket );

            m_mapMarkets[ ulMarketId ] = dstrMarket;
         }

         // Get the default market and make sure it exists
         m_ulDefaultMarket = _readNum( infile, 10 );

         ulString_map::iterator iterMarkets =
            m_mapMarkets.find( m_ulDefaultMarket );

         if ( m_mapMarkets.end() == iterMarkets )
         {
            DString idiStr = I_( "MARKET=" );
            idiStr.appendULong( m_ulDefaultMarket );

            THROWELEMENTALIDI(
               BINFILEHEADER_NAME,
               I_( "BinFileHeader::BinFileHeader()" ),
               BinFileHeader::BINFILEHEADER_DEFAULT_MARKET_NOT_FOUND,
               languagesMapForBinFileHeader,
               idiStr );
         }

         //////////////// Clients

         // Read in the number of Clients
         long lNumClients = _readNum( infile, 5 );

         ClientMarketIndex cmIndex;

         // Read in the Clients
         for ( lIndex = 0; lIndex < lNumClients; ++lIndex )
         {
            cmIndex.ulClientId = _readNum( infile, 10 );
            cmIndex.ulMarketId = _readNum( infile, 10 );
            unsigned long ulClientNameLength = _readNum( infile, 5 );
            DString dstrClient;
            _readString( infile, ulClientNameLength, dstrClient );

            if ( m_mapMarkets.find( cmIndex.ulMarketId ) == m_mapMarkets.end() )
            {
               DString idiStr = I_( "FILE=" );
               idiStr += DString( m_dstraFileName ).c_str();
               idiStr += I_( ";CLIENT=" );
               idiStr.appendULong( cmIndex.ulClientId );
               idiStr += I_( ";MARKET=" );
               idiStr.appendULong( cmIndex.ulMarketId );

               THROWELEMENTALIDI(
                  BINFILEHEADER_NAME,
                  I_( "BinFileHeader::BinFileHeader()" ),
                  BinFileHeader::BINFILEHEADER_MISSING_MARKET_FOR_CLIENT,
                  languagesMapForBinFileHeader,
                  idiStr );
            }

            m_mapClients[ cmIndex ] = dstrClient;

//            m_mapClientToMarket[ ulClientId ] = ulMarketId;
         }

         // Read in the default client and make sure it is valid
         m_ulDefaultClient = _readNum( infile, 10 );

         ClientMarketIndex cmDefault( m_ulDefaultClient, m_ulDefaultMarket );

         client_market_map::iterator iterClients =
            m_mapClients.find( cmDefault );

         if ( m_mapClients.end() == iterClients )
         {
            DString idiStr = I_( "CLIENT=" );
            idiStr.appendULong( m_ulDefaultClient );
            idiStr += I_( ";MARKET=" );
            idiStr.appendULong( m_ulDefaultMarket );

            THROWELEMENTALIDI(
               BINFILEHEADER_NAME,
               I_( "BinFileHeader::BinFileHeader()" ),
               BinFileHeader::BINFILEHEADER_DEFAULT_CLIENT_NOT_FOUND,
               languagesMapForBinFileHeader,
               idiStr );
         }

         m_ulFileOffset = ftell( infile );

         fclose( infile );

         m_register.registerSingleton( _deregister, ( void * )this );
      }
      catch ( ... )
      {
         fclose( infile );
         throw;
      }
   }
}


BinFileHeader::~BinFileHeader()
{
}


long BinFileHeader::_readNum( FILE* infile, int iSize )
{
   if ( iSize > 30 )
   {
      // throw if size too large? - should never be necessary
      iSize = 30;
   }

   wchar_t readBuffer[ 31 ];
   char charBuffer[ 31 ];

   long lOffset = ftell( infile );
   memset( readBuffer, 0, ( iSize + 1 ) * CHAR_SIZE );
   size_t count = fread( readBuffer, CHAR_SIZE, iSize, infile );

   if ( count != iSize )
   {
      DString idiStr = I_( "FILE=" );
      idiStr += DString( m_dstraFileName ).c_str();
      idiStr += I_( ";OFFSET=" );
      idiStr.appendLong( lOffset );
      idiStr += I_( ";EXPECTED=" );
      idiStr.appendLong( CHAR_SIZE * iSize );
      idiStr += I_( ";RECEIVED=" );
      idiStr.appendLong( CHAR_SIZE * count );

      THROWELEMENTALIDI(
         BINFILEHEADER_NAME,
         I_( "BinFileHeader::_readNum( FILE* infile, int iSize )" ),
         BinFileHeader::BINFILEHEADER_READ_SIZE_FAILED,
         languagesMapForBinFileHeader,
         idiStr );
   }

   wcstombs( charBuffer, readBuffer, ( iSize + 1 ) );
   return atol( charBuffer );
}


DString& BinFileHeader::_readString( FILE* infile, int iSize,
                                     DString& dstr )
{
   wchar_t *readBuffer = new wchar_t[ iSize +1 ];
   auto_ptr< wchar_t > autoPtr( readBuffer );

   long lOffset = ftell( infile );

   memset( readBuffer, 0, ( iSize + 1 ) * CHAR_SIZE );
   size_t count = fread( readBuffer, CHAR_SIZE, iSize, infile );

   if ( count != iSize )
   {
      DString idiStr = I_( "FILE=" );
      idiStr += DString( m_dstraFileName ).c_str();
      idiStr += I_( ";OFFSET=" );
      idiStr.appendLong( lOffset );
      idiStr += I_( ";EXPECTED=" );
      idiStr.appendLong( CHAR_SIZE * iSize );
      idiStr += I_( ";RECEIVED=" );
      idiStr.appendLong( CHAR_SIZE * count );

      THROWELEMENTALIDI(
         BINFILEHEADER_NAME,
         I_( "BinFileHeader::BinFileHeader::" )
            I_( "_readString( FILE* infile, int iSize, DString& dstr )" ),
         BinFileHeader::BINFILEHEADER_READ_SIZE_FAILED,
         languagesMapForBinFileHeader,
         idiStr );
   }

#ifdef DST_UNICODE
   dstr = readBuffer;
#else
   char *charBuffer = new char[ iSize + 1 ];
   auto_ptr< char > autoPtr2( charBuffer );
   wcstombs( charBuffer, readBuffer, ( iSize + 1 ) );
   dstr = charBuffer;
#endif
   return dstr;
}


void BinFileHeader::getMarkets( ul_vector& vecMarkets ) const
{
   vecMarkets.erase( vecMarkets.begin(), vecMarkets.end() );

   ulString_map::const_iterator iter = m_mapMarkets.begin();

   while ( m_mapMarkets.end() != iter )
   {
      vecMarkets.push_back( ( *iter ).first );
      ++iter;
   }
}


unsigned long BinFileHeader::getMarketIndex( const DString& dstrMarket ) const
{
   ulString_map::const_iterator iter =
      findInValueInMap< ulString_map, DString >( m_mapMarkets, dstrMarket );

   if ( m_mapMarkets.end() == iter )
   {
      DString idiStr = I_( "MARKET=" );
      idiStr += dstrMarket;

      THROWELEMENTALIDI(
         BINFILEHEADER_NAME,
         I_( "BinFileHeader::getMarketIndex( const DString& dstrMarket )" ),
         BinFileHeader::BINFILEHEADER_MARKET_NOT_FOUND,
         languagesMapForBinFileHeader,
         idiStr );
   }

   return ( *iter ).first;
}


DString& BinFileHeader::getMarketName( unsigned long ulMarket,
                                       DString& dstrMarket ) const
{
   ulString_map::const_iterator iter = m_mapMarkets.find( ulMarket );

   if ( m_mapMarkets.end() == iter )
   {
      dstrMarket = I_( "Unknown market (" );
      dstrMarket.appendULong( ulMarket );
      dstrMarket.append( I_( ")" ) );
   }
   else
   {
      dstrMarket = ( *iter ).second;
   }
   return dstrMarket;
}


unsigned long BinFileHeader::getDefaultMarket() const
{
   return m_ulDefaultMarket;
}


DString BinFileHeader::getDefaultMarketName() const
{
   DString dstrRet;

   getMarketName( m_ulDefaultMarket, dstrRet );

   return dstrRet;
}


void BinFileHeader::getClients( cmi_vector& vecClients ) const
{
   vecClients.clear();

   client_market_map::const_iterator iter = m_mapClients.begin();

   while ( m_mapClients.end() != iter )
   {
      vecClients.push_back( ( *iter ).first );
      ++iter;
   }
}


unsigned long BinFileHeader::getClientIndex( unsigned long ulMarket,
                                             const DString& dstrClient ) const
{
   client_market_map::const_iterator iter =
      findInValueInMap< client_market_map, DString >( m_mapClients, dstrClient );

   if ( m_mapClients.end() == iter )
   {
      DString idiStr = I_( "CLIENT=" );
      idiStr += dstrClient;
      idiStr += I_( ";MARKET=" );
      idiStr.appendULong( ulMarket );

      THROWELEMENTALIDI(
         BINFILEHEADER_NAME,
         I_( "BinFileHeader::getClientIndex( const DString& dstrClient )" ),
         BinFileHeader::BINFILEHEADER_CLIENT_NOT_FOUND,
         languagesMapForBinFileHeader,
         idiStr );
   }

   return ( *iter ).first.ulClientId;
}


DString& BinFileHeader::getClientName( unsigned long ulMarket,
                                       unsigned long ulClient,
                                       DString& dstrClient ) const
{
   client_market_map::const_iterator iter =
      m_mapClients.find( ClientMarketIndex( ulClient, ulMarket ) );

   if ( m_mapClients.end() == iter )
   {
      dstrClient = I_( "Unknown client (" );
      dstrClient.appendULong( ulClient );
      dstrClient.append( I_( ")" ) );
   }
   else
   {
      dstrClient = ( *iter ).second;
   }
   return dstrClient;
}


unsigned long BinFileHeader::getDefaultClient() const
{
   return m_ulDefaultClient;
}


DString BinFileHeader::getDefaultClientName() const
{
   DString dstrRet;

   getClientName( m_ulDefaultMarket, m_ulDefaultClient, dstrRet );

   return dstrRet;
}

/*
unsigned long BinFileHeader::getMarketForClient( unsigned long ulClient ) const
{
   ulul_map::iterator iter = m_mapClientToMarket.find( ulClient );

   if ( m_mapClientToMarket.end() == iter )
   {
      DString idiStr = I_( "CLIENT=" );
      idiStr.appendULong( ulClient );

      THROWELEMENTALIDI(
         BINFILEHEADER_NAME,
         I_( "BinFileHeader::getMarketForClient( unsigned long ulClient )" ),
         BinFileHeader::BINFILEHEADER_CLIENT_NOT_FOUND,
         languagesMapForBinFileHeader,
         idiStr );
   }

   return ( *iter ).first;
}
*/


unsigned long BinFileHeader::getHeaderSize() const
{
   return m_ulFileOffset;
}


const DStringA& BinFileHeader::getFileName() const
{
   return m_dstraFileName;
}


const DString& BinFileHeader::getVersionNumber() const
{
   return m_dstrVersionNumber;
}


/*******************************************************************************
//              Revision Control Entries
//******************************************************************************
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
// $Log:   Y:/VCS/iFastAWD/dicore/binfileheader.cpp-arc  $
// 
//    Rev 1.1   Nov 02 2011 04:42:48   purdyech
// Registry Cleanup
//
//    Rev 1.0   28 Jan 2008 13:19:18   kovacsro
// Initial revision.
//
//   Rev 1.3   Sep 21 2001 16:19:14   DT11159
//Made changes to support the new bin file format.
//
//   Rev 1.2   Sep 20 2001 15:58:30   dt39990
//Change BINFILEHEADER_NAME from
//BinFileHeader to DICORE
//
//   Rev 1.1   Sep 05 2000 06:19:00   dt17817
//- Remove Certificate/Authenticator
//- Fix threadsafety of client/market
//- Add "null" property value support
//
//
//   Rev 1.0   Aug 09 2000 08:25:48   dtwk
//
//
//
//
*/


