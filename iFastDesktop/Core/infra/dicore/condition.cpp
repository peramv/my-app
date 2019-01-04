//**********************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1997 by DST Systems, Inc.
//
//**********************************************************************
//
// ^FILE   : Condition.cpp
// ^AUTHOR : Jerry Leenerts
// ^DATE   : 5/6/97
//
// ----------------------------------------------------------
//
// ^CLASS    : Condition
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//**********************************************************************
#define DICORE_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#ifndef CONDITION_HPP
   #include "condition.hpp"
#endif

#ifndef IDISTRING_HPP
   #include "idistring.hpp"
#endif

#ifndef CLIENTLOCALE_HPP
   #include "clientlocale.hpp"
#endif

#ifndef LOCALE_H
   #include <locale.h>
#endif

#ifndef INCLUDED_FSTREAM
#define INCLUDED_FSTREAM
#include <fstream>
#endif

#include <assert.h>

#if defined( _RWSTDDLL )
typedef unsigned char  STREAM_READ_TYPE;

#else

   #if defined( _UNIX )

typedef unsigned char  STREAM_READ_TYPE;

   #else

typedef char  STREAM_READ_TYPE;

   #endif

#endif

const int Condition::TOKEN_NOT_FOUND = -1;

#include <map>
#include <deque>

class myCritSec
{
public:
   //creates a BFCritSec object
   myCritSec()
   {
      ::InitializeCriticalSection( &cs_ );
   }
   ~myCritSec()
   {
      leave();
      ::DeleteCriticalSection( &cs_ );
   }

   //enters the critical section
   void enter()
   {
      ::EnterCriticalSection( &cs_ );
   }
   //leaves the critical section
   void leave()
   {
      ::LeaveCriticalSection( &cs_ );
   }

private:
   CRITICAL_SECTION cs_;
};

class myGuard
{
public:
   myGuard( myCritSec& cs )
   : cs_( cs )
   {
      cs_.enter();
   }
   ~myGuard()
   {
      cs_.leave();
   }
private:
   myCritSec& cs_;
};

struct ConditionCacheKey
{
   public:
   ConditionCacheKey( long code, const DString& name, const ClientLocale* pLocale )
   : code_( code )
   , name_( name )
   {
      if( pLocale != NULL )
      {
         locale_ = *pLocale;
      }
   }
   ~ConditionCacheKey()
   {}

   bool operator<( const ConditionCacheKey& rhs ) const
   {
      if( code_ < rhs.code_ )
      {
         return( true );
      }
      else if( code_ > rhs.code_ )
      {
         return( false );
      }

      if( name_ < rhs.name_ )
      {
         return( true );
      }
      else if( name_ > rhs.name_ )
      {
         return( false );
      }

      if( locale_ < rhs.locale_ )
      {
         return( true );
      }
      return( false );
   }

   long     code_;
   DString  name_;
   ClientLocale locale_;
};

typedef std::map< ConditionCacheKey, Condition* >    ConditionCache;
typedef ConditionCache::iterator       ConditionCache_Iter;
typedef ConditionCache::const_iterator ConditionCache_ConstIter;

myCritSec g_cs_ConditionCache;
ConditionCache g_ConditionCache;

typedef std::deque< const Condition* > CONDITION_DECK;
typedef CONDITION_DECK::iterator CONDITION_DECK_ITER;
typedef CONDITION_DECK::reverse_iterator CONDITION_DECK_RITER;

static CONDITION_DECK s_ConditionDeck;
myCritSec s_csConditionDeck;
const int s_sizeConditionDeck = 20;

static void recordCondition( const Condition* pCondition )
{
   Condition* pRecord = new Condition(*pCondition);
   myGuard g(s_csConditionDeck);
   while( s_ConditionDeck.size() > s_sizeConditionDeck ) {
      CONDITION_DECK_ITER it = s_ConditionDeck.begin();
      if( it != s_ConditionDeck.end() ) {
         const Condition* pDelete = (*it);
         if( NULL != pDelete ) {
            delete pDelete;
         }
         s_ConditionDeck.pop_front();
      }
   }
   s_ConditionDeck.push_back(pRecord);
   return;
}

// last to first!
const Condition* Condition::getRecordedCondition(const Condition* pCondition ) {
   myGuard g(s_csConditionDeck);
   if( s_ConditionDeck.size() == 0 ) {
      return( NULL );
   }
   CONDITION_DECK_RITER it = s_ConditionDeck.rbegin();

   // if pCondition is NULL, then just return the first condition
   if( NULL == pCondition ) {
      return( *(it) );
   }

   // find requested condition
   for( ; it != s_ConditionDeck.rend(); ++it ) {
      const Condition* pCandidate = (*it);
      if( pCandidate == pCondition ) {
         // found requested condition ... get the previous one
         
         if( ++it != s_ConditionDeck.rend() ) {
            return( *it );
         }
         return(NULL);
      }
   }
   return( NULL );   
}

namespace
{
   // IDI literals
   const char * BASEFILE = "DICORE";
   const I_CHAR * const IDI_EMPTY_MARK = I_( "(null)" );
   const I_CHAR * const IDI_BREAK = I_( ";" );
   const I_CHAR * const IDI_EQUAL = I_( "=" );
   const I_CHAR * const IDI_MARKER = I_("%");
   const I_CHAR * const IDI_PERCENT_PARSE_ERROR = I_("Cannot find paired %");
}

// MsgPairs that have been implemented

Condition::mapCodePagesToLanguages Condition::languagesMap[] =
{
   {
      I_( "C" ), en_us
   },

   {
      I_( "enus" ), en_us
   },

};

MsgPair * getMsgPairFromCndCode( MsgPair * pair, long code );
I_CHAR MESSAGE1[] = I_( "The workstation locale corresponding" )
                    I_( " to ISO country code \"" );
I_CHAR MESSAGE2[] = I_( "\" is not supported by Condition.  " );
I_CHAR MESSAGE3[] = I_( "The current locale is not defined on this workstation.");
I_CHAR CORRECTION[] = I_( "Contact your support desk." );
I_CHAR PARSEERROR[] = I_( "Parsing error happened in message ");

//**********************************************************************
// CLASS: Condition
//**********************************************************************

// file constructor

Condition::Condition( const DString &componentName,
                      const DString &methodName,
                      long code,
                      const I_CHAR* codeStr,
                      const char * fileName,
                      unsigned lineNumber,

                      BOOL baseCondition,
                      const I_CHAR *path,
                      SEVERITY severity,
                      const DString & idiStr,
                      const ClientLocale *clientLocale,
                      const DString & context ) 
: _code( code )
, _codeStr( codeStr )
, _name( I_( "" ) )
, _componentName( componentName )
, _context( context )
, _currMsgPair( NULL )
, _fileName( fileName )
, _lineNumber( lineNumber )
, _methodName( methodName )
, _pathName( path )
, _severity( NO_SEVERITY )
, _Idi( idiStr )
, _baseCondition( baseCondition )
, _suppress( 0 )
, _clientLocale( 0 )
, _init( false )
{
   ::GetSystemTime(&_created);
   _clientLocale = new ClientLocale();

   // clientLocale can be null
   if( clientLocale )
      *_clientLocale = *clientLocale;
/*
   if ( fDoIdiSubstitutionNow )
      init( idiStr,
            baseCondition,
            severity,
            path );
   else
*/
   _severity = severity;
   recordCondition(this);
}

// used by frame

Condition::Condition( const I_CHAR * componentName,
                      const I_CHAR * methodName,
                      long code,
                      const I_CHAR* codeStr,
                      SEVERITY severity,
                      const char * fileName,
                      unsigned lineNumber,
                      const I_CHAR * message,
                      const I_CHAR * correction,
                      long suppression,
                      const DString & idi )
: _code( code )
, _codeStr( codeStr )
, _name( I_( "" ) )
, _componentName( componentName )
, _correction( correction )
, _fileName( fileName )
, _lineNumber( lineNumber )
, _message( message )
, _methodName( methodName )
, _severity( severity )
, _suppress( suppression )
, _Idi( idi )
, _baseCondition( -1 )
, _clientLocale( 0 )
, _init( true )
{
   ::GetSystemTime(&_created);
   _clientLocale = new ClientLocale();
   recordCondition(this);

}

Condition::Condition( const DString & componentName,
                      const DString & methodName,
                      long code,
                      const I_CHAR* codeStr,
                      const char * fileName,
                      unsigned lineNumber,
                      mapCodePagesToLanguages elementalTable[],
                      const DString & idiStr )
: _code( code )
, _codeStr( codeStr )
, _name( I_( "" ) )
, _componentName( componentName )
, _currMsgPair( NULL )
, _fileName( fileName )
, _lineNumber( lineNumber )
, _methodName( methodName )
, _severity( CRITICAL_ERROR )
, _suppress( 0 )
, _clientLocale( 0 )
{
   ::GetSystemTime(&_created);
   elementalInit( idiStr,
                  elementalTable);
   // Elemental conditions to not use the cnd files
   //   to mark the condition as already initialized
   _init = true;
   recordCondition(this);
}

// copy constructor

Condition::Condition( const Condition &copy ) 
: _baseCondition( copy._baseCondition)
, _code( copy._code )
, _codeStr( copy._codeStr )
, _name( copy._name )
, _componentName( copy._componentName )
, _context( copy._context )
, _correction( copy._correction )
, _currMsgPair( copy._currMsgPair )
, _fileName( copy._fileName )
, _Idi( copy._Idi )
, _lineNumber( copy._lineNumber )
, _message( copy._message )
, _methodName( copy._methodName )
, _pathName( copy._pathName )
, _severity( copy._severity )
, _suppress( copy._suppress )
, _clientLocale( 0 )
, _init( false )
{
   memcpy( &_created, &(copy._created), sizeof(_created) );
   _clientLocale = new ClientLocale();

   // clientLocale can be null
   if( copy._clientLocale )
      *_clientLocale = *(copy._clientLocale);
}

Condition::~Condition()
{
   if( _clientLocale )
      delete _clientLocale;
}

void Condition::idiElementalProcessing( DString &mainString,
                                        const DString &idiString )
{
   // idistring class uses conditions so that functionality
   //   cannot be used by the elemental conditions

   // Any errors in the parsing of the idi string to stop the parsing,
   //   The parse error will be recorded by adding a fixed English
   //   message to the end of the string.
   bool done = false;
   int replaceStartPos = 0;

   do
   {
      int keyPos = idiString.find(IDI_EQUAL, replaceStartPos);

      if( -1 == keyPos )
      {
         mainString += PARSEERROR;
         done = true;
         continue;
      }

      int valuePos = idiString.find(IDI_BREAK, replaceStartPos);

      if( -1 == valuePos )
      {
         valuePos = idiString.length();
         done = true;
      }

      DString keyStr = idiString.substr( replaceStartPos,
                                         (keyPos - replaceStartPos));
      keyStr = IDI_MARKER + keyStr + IDI_MARKER;

      DString valueStr = idiString.substr( keyPos + 1,
                                           (valuePos - keyPos - 1));

      int keyStrStart = mainString.find(keyStr);

      if( -1 != keyStrStart )
      {
         // The idi string contains tags for message
         //    and correction.  So not finding the key
         //    means that the tag is in the other message
         mainString.replace(keyStrStart, keyStr.length(), valueStr);
      }

      // Handle case of IDI string ending with ;
      if( (valuePos + 1) == idiString.length() )
         done = true;

      replaceStartPos = valuePos + 1;

   } while( false == done );
}

void Condition::elementalInit( const DString & strCondition,
                               Condition::mapCodePagesToLanguages elementalTable[])
{
   I_CHAR *cLocale = i_setlocale( LC_ALL, NULL );

   _currMsgPair = NULL;

   bool langFound = false;

   int i = 0;
   while( false == langFound )
   {
      if( NULL == elementalTable[i].isoCode )
      {
         // End of lang table
         langFound = true;
         break;
      }

      if( !i_stricmp( cLocale, elementalTable[i].isoCode) )
      {
         _currMsgPair = elementalTable[ i ].msgPair;
         langFound = true;
         break;
      }

      i++;
   }

   if( NULL == _currMsgPair )
   {
      _currMsgPair = elementalTable[ 0 ].msgPair;
   }

   // The replace function used assumes that _message has been set.
   //   So the assignment of the variable must be placed here
   _message = DString(getMsgPairFromCndCode( _currMsgPair,
                                             _code )->errMsg);

   _correction = DString( getMsgPairFromCndCode( _currMsgPair,
                                                 _code )->correctionMsg );

   // Verify that there is an IDI string to parse
   if( !strCondition.empty() )
   {
      idiElementalProcessing( _message, strCondition );
      idiElementalProcessing( _correction, strCondition );
   }
}

void Condition::idiProcessing( DString &mainString,
                               const DString &idiString )
{
   int len = _Idi.length();
   if( len )
   {
      I_CHAR * saveTemp, *temp;
      saveTemp = temp = new I_CHAR[ len + 1 ];
      i_strcpy( temp, _Idi.c_str() );

      // Any errors in the parsing of the idi string to stop the parsing,
      //   The parse error will be recorded by adding a fixed English
      //   message to the end of the string.
      bool done = false;
      int replaceStartPos = 0;

      do
      {
         DString keyStr;
         DString valueStr;

         temp = parseIdiString( temp, keyStr, valueStr );

         keyStr = IDI_MARKER + keyStr + IDI_MARKER;

         int keyStrStart = mainString.find(keyStr);

         if( -1 != keyStrStart )
         {
            // The idi string contains tags for message
            //    and correction.  So not finding the key
            //    means that the tag is in the other message
            mainString.replace(keyStrStart, keyStr.length(), valueStr);
         }

      } while( 0 != temp );

      delete [] saveTemp;

      // Process the resulting string for special percent characters
      //   and replace any unfilled tags
      int curPos = mainString.find( IDI_MARKER );

      while( -1 != curPos )
      {
         int tempCurPos = mainString.find( IDI_MARKER, curPos + 1 );

         if( -1 == tempCurPos )
         {
            // Mark error and exit loop
            // mainString += IDI_PERCENT_PARSE_ERROR;
            break;
         }

         // Check for %% market for normal % sign
         if( curPos == ( tempCurPos - 1 ) )
         {
            mainString.replace( curPos, 2, IDI_MARKER );
            curPos += 1;  // Advance past replaced segment
         }
         else
         {
            mainString.replace( curPos, ( tempCurPos - curPos ) + 1,
                                IDI_EMPTY_MARK );
            curPos += i_strlen( IDI_EMPTY_MARK );  // Advance past replaced segment
         }

         curPos = mainString.find( IDI_MARKER, curPos );
      }
   }
}

void Condition::prepareMessage()
{
   if( false == setCurrMsgPair( _clientLocale->getLocale() ) )
   {
      return;
   }

   SEVERITY severity = _severity;

   // baseConditions are always stored in dicore
   bool readError = readFromFile( false, false );

   // If the read failed assume looking for base condition
   if( true == readError )
   {
      // Save variables from first read
      Condition storedValues = *this;
      readError = readFromFile( true, false );

      // If still not found error, assume not a base conditions
      if( true == readError )
         *this = storedValues;
   }

   if( severity > _severity )
   {
      // Allow override
      _severity = severity;
   }
   if( _pathName.empty() )
   {
      _pathName = I_( ".\\" );
   }

   doIdiSubstitution();
}

void Condition::prepareMessage( const ClientLocale & pClientLocale )
{
   *_clientLocale = pClientLocale;
   prepareMessage( );
}

void Condition::prepareMessage( const DString & locale )
{
   _clientLocale->setLocale( locale );
   prepareMessage();
}

void Condition::doIdiSubstitution()
{
   // Verify that there is an IDI string to parse
   if( !_Idi.empty() )
   {
      idiProcessing( _message, _Idi );
      idiProcessing( _correction, _Idi );
   }
}

// uses new file format
#pragma pack( 1 )

typedef struct
{
   int endian;
   int version;
   int checksum;
} BINFILEHEADER;

typedef struct
{
   long totalSize;
   long totalBaseSize;
   long numBaseConditionCodes;

} BASESIZES;

typedef struct
{
   long totalMarketSize;
   long numMarketConditionCodes;

} MARKETSIZES;

typedef struct
{
   long totalClientSize;
   long numClientConditionCodes;

} CLIENTSIZES;

typedef struct
{
   wchar_t isoCode[ 4 ];
   int offset;
} COUNTRY_POINTER;

typedef struct
{
   long code;
   long severity;
} CONDITION_CODE;

typedef struct
{
   long overrideId;
   long code;
   int severity;
   int suppress;
} OVERRIDE_CONDITION_CODE;

#pragma pack()

typedef struct
{
   long overrideId;
   long code;
   std::wstring message;
   std::wstring correction;
} MESSAGE_SET;

void reverseEndian( char * tp, int count )
{
   char ch;
   int mid  = ( count + 1 ) >> 1;
   for( int i = 0; i <= mid; ++i )
   {
      ch = tp[ i ];
      tp[ i ] = tp[ count - i - 1 ];
      tp[ count - i - 1 ] = ch;
   }
}

unsigned int addChecksum( char * tp, int count )
{
   int rVal = 0;

   while( count-- )
      rVal += *tp;

   return(rVal);
}

SEVERITY readLine( std::ifstream & fCnd,
                   std::wstring & linebuf,
                   bool fBigEndian )
{
   // read an individual line
   wchar_t ch;
   int chCount = 0;
   while( 1 )
   {
      fCnd.read( ( char * ) &ch, sizeof( ch ) );
      ++chCount;
      if( fBigEndian )
      {
         reverseEndian( ( char * ) &ch, sizeof( ch ) );
      }
      if( 1000 == chCount )
      {
         return(SEVERE_ERROR);
      }
      if( 0 == ch )
      {
         break;
      }
      linebuf.append( 1, ch );
   }
   return(NO_SEVERITY);
}

void i_memlwr( I_CHAR buf[], int count )
{
   for( ; count; --count )
   {
      if( i_isupper( buf[ count - 1 ] ) )
      {
         buf[ count - 1 ] = i_tolower( buf[ count - 1 ] );
      }
   }
}

MsgPair * getMsgPairFromCndCode( MsgPair * pair, long code )
{
   int i = 0;
   for(i = 0; Condition::NO_CONDITION_CODE != pair[ i ].msgCode; ++i)
   {
      if( code == pair[ i ].msgCode )
         break;
   }
   return(&pair[ i ]);
}

SEVERITY readMessageSet( std::ifstream & fCnd,
                         MESSAGE_SET & msgSet,
                         int & tmpChecksum,
                         int & offset,
                         int & count,
                         bool fBigEndian,
                         bool fReadOverrides,
                         long & suppress,
                         enum SEVERITY & severity )
{
   long overrideId;
   long code;
   int messageSize, stringSize;
   SEVERITY sev;

   // The client and client sections have these extra flags
   if( true == fReadOverrides )
   {
      fCnd.read( ( char * ) &overrideId, sizeof( overrideId ) );
      messageSize = sizeof( overrideId );

      if( fBigEndian )
      {
         reverseEndian( ( char * ) &overrideId, sizeof( overrideId ) );
      }
      msgSet.overrideId = overrideId;
      tmpChecksum += addChecksum( ( char * ) &overrideId, sizeof( overrideId ) );
   }

   fCnd.read( ( char * ) &code, sizeof( code ) );
   messageSize = sizeof( code );

   if( fBigEndian )
   {
      reverseEndian( ( char * ) &code, sizeof( code ) );
   }
   msgSet.code = code;
   tmpChecksum += addChecksum( ( char * ) &code, sizeof( code ) );

   // read message
   sev = readLine( fCnd, msgSet.message, fBigEndian );
   if( NO_SEVERITY == sev )
   {
      tmpChecksum += addChecksum( ( char * ) msgSet.message.c_str(),
                                  msgSet.message.size() *
                                  sizeof( I_CHAR ) );
      stringSize = ( msgSet.message.size() + 1 ) * sizeof( wchar_t );
      messageSize += stringSize;

      // read correction
      sev = readLine( fCnd, msgSet.correction, fBigEndian );
      if( NO_SEVERITY == sev )
      {
         tmpChecksum += addChecksum( ( char * )
                                     msgSet.correction.c_str(),
                                     msgSet.correction.size() *
                                     sizeof( I_CHAR ) );
         stringSize = ( msgSet.correction.size() + 1 ) * sizeof( wchar_t );
         messageSize += stringSize;
      }
   }

   offset -= messageSize;
   count += messageSize;

   return(sev);
}

bool Condition::readFromFile( BOOL baseFlag, bool bUseDefaultLang )
{
   // is the condition already in the cache?
   {
      myGuard g( g_cs_ConditionCache );
      ConditionCache_Iter itCache = g_ConditionCache.find( ConditionCacheKey( _code, _componentName, _clientLocale ) );
      if( itCache != g_ConditionCache.end() )
      {
         // must restore the original IDI string after the copy operation
         DString origIdi( _Idi );
         *this = *(*itCache).second;
         _Idi = origIdi;
         return( false );
      }
   }

   bool fProblem = true;


   DStringA fileName, tmpName;

   if( baseFlag )
   {
      fileName = BASEFILE;
   }
   else
   {
      fileName = _componentName;
   }

   fileName += ".CND";

   // kludge the pathname into an environment variable so we can call
   // _searchenv()
   DStringA cndTmp = "CONDITIONTEMP=";
   cndTmp += DStringA( _pathName );
   _putenv( cndTmp.c_str() );

   char buf[ 513 ];
   tmpName = fileName;
   _searchenv( fileName.c_str(), "CONDITIONTEMP", buf );
   fileName = buf;

   DString iso5 = bUseDefaultLang ? I_( "enUS" ) : _clientLocale->getLocale();
   long defaultMarket = _clientLocale->getMarketIndex();
   long defaultClient = _clientLocale->getClientIndex();

/*
   if ( locale.size() )
      iso5 = locale;
   else
   {
      const JavaLocale * defaultLcl = JavaLocale::getCurrentInstance();
      defaultLcl->getLCV( iso5 );
   }

*/

   if( iso5.empty() )
   {  // This must be hard-coded HERE!
      _severity = CRITICAL_ERROR;
      _message = I_( "Severe error.  " )
                 I_( "Locale could not be retrieved.  " );
      _correction = I_( "Contact your support desk." );
      return(fProblem);
   }

   if( fileName.empty() )
   {  // This must be hard-coded HERE!
      _severity = CRITICAL_ERROR;

      DString tmp = getMsgPairFromCndCode( _currMsgPair,
                                           Condition::CND_FILE_NOT_FOUND )->errMsg;
      _message = tmp;
      _message.append( I_( " " ) );
      _message.append( DString( tmpName ) );
      _message.append( I_( " .  " ) );

      _correction = DString( getMsgPairFromCndCode( _currMsgPair,
                                                    Condition::CND_FILE_NOT_FOUND )->correctionMsg );
      return(fProblem);
   }

   // Read from file based on _code
#if defined(_UNIX)

   std::ifstream fCnd( DStringA( fileName ).c_str(), ios::in |
                       ios::nocreate );

#elif defined(_RWSTDDLL)

   ifstream fCnd( DStringA( fileName ).c_str(), ios::in | ios::binary |
                  ios::nocreate );

#else

   std::ifstream fCnd( DStringA( fileName ).c_str(),
                       std::ios_base::in | std::ios_base::binary );

#endif

   // call rdbuf()->is_open since fstream.h in Visual Age on OS2 does
   // not have ifstream::is_open-- LP
   if( !fCnd.rdbuf()->is_open() )
   {
      _severity = CRITICAL_ERROR;

      DString tmp = getMsgPairFromCndCode( _currMsgPair,
                                           Condition::CND_FILE_NOT_FOUND )->errMsg;
      tmp += DString( fileName );

      _message = tmp;

      _correction = DString( getMsgPairFromCndCode( _currMsgPair,
                                                    Condition::CND_FILE_NOT_FOUND )->correctionMsg );
      return(fProblem);
   }

   bool found=false;
   bool foundMarketOverride = false;
   bool foundClientOverride = false;
   bool foundMarketLangOverride = false;
   bool foundClientLangOverride = false;
   int countMarketRead = 0;
   int countClientRead = 0;
   int i;
   int offset;
   bool fBigEndian = false;
   int conditionCode;
   BINFILEHEADER hdr;
   BASESIZES baseSizes;
   MARKETSIZES marketSizes;
   CLIENTSIZES clientSizes;

   CONDITION_CODE * conCode;
   OVERRIDE_CONDITION_CODE * conMarketCode = 0;
   OVERRIDE_CONDITION_CODE * conClientCode = 0;

   int count,  // used to determine the offset to the start of the
   // string tables
   tmp,
   numCountryCodes,
   numMarketCountryCodes,
   numClientCountryCodes,
   checksum = 0, tmpChecksum = 0,
   numBaseLanguageCodes,
   numMarketLanguageCodes,
   numClientLanguageCodes;

   enum SEVERITY minSeverity = NO_CONDITION;

   fCnd.read( ( char * ) &hdr, count = sizeof( BINFILEHEADER ) );

   // check endian code
   if( 1 != hdr.endian )
      fBigEndian = true;
   if( fBigEndian )
   {
      reverseEndian( ( char * ) &hdr, count );
   }

   // version 1000
   if( !isValidVersion( hdr.version ) )
   {
      _severity = CRITICAL_ERROR;
      DString version = I_( "Latest version is " );
      I_CHAR buf[18];
      i_itot( getLatestVersion(), buf, 10 );
      version += DString( buf );
      version += I_( ".  " );
      _message = getMsgPairFromCndCode( _currMsgPair,
                                        INVALID_VERSION )->errMsg;
      _correction = getMsgPairFromCndCode( _currMsgPair,
                                           INVALID_VERSION )->correctionMsg;
      _message += version;
      return(fProblem);
   }

   // Read base sizes
   count += sizeof( BASESIZES );
   fCnd.read( ( char * ) &baseSizes, sizeof( BASESIZES ) );

   if( fBigEndian )
   {
      reverseEndian( ( char * ) &baseSizes, sizeof( BASESIZES ) );
   }

   // read condition codes into buffer

   tmp = sizeof( CONDITION_CODE ) * baseSizes.numBaseConditionCodes;
   count += tmp;
   try
   {
      conCode = new CONDITION_CODE[ tmp ];
   }
   catch( ... )
   {
      _severity = CRITICAL_ERROR;
      _message = getMsgPairFromCndCode( _currMsgPair,
                                        ERROR_ON_NEW )->errMsg;
      _correction = getMsgPairFromCndCode( _currMsgPair,
                                           ERROR_ON_NEW )->correctionMsg;
      return(fProblem);
   }

   fCnd.read( ( char * ) conCode, tmp );

   if( fBigEndian )
   {
      reverseEndian( ( char * ) conCode, tmp );
   }

   // look for a match in the condition codes
   conditionCode = Condition::CODE_NOT_FOUND;
   for( i = 0; i < baseSizes.numBaseConditionCodes; ++i )
   {
      if( conCode[ i ].code == _code )
      {
         minSeverity = ( SEVERITY ) conCode[ i ].severity;
         fProblem = false;
         break;
      }
   }

   COUNTRY_POINTER * cp = ( COUNTRY_POINTER * ) NULL;

   if( false == fProblem )
   {
      // read in num country codes
      fCnd.read( ( char * ) &numCountryCodes,
                 sizeof( numCountryCodes ) );
      count += sizeof( numCountryCodes );

      if( fBigEndian )
      {
         reverseEndian( ( char * ) &numCountryCodes,
                        sizeof( numCountryCodes ) );
      }

      // read country table into buffer
      tmp = sizeof( COUNTRY_POINTER ) * numCountryCodes;
      count += tmp;

      cp = new COUNTRY_POINTER[ numCountryCodes ];
      fCnd.read( ( char * ) cp, tmp );

      if( fBigEndian )
      {
         reverseEndian( ( char * ) cp, tmp );
      }

      // look for a match for iso5
      fProblem = true;
      conditionCode = Condition::ISO_CODE_NOT_FOUND;
      for( i = 0; i < numCountryCodes; ++i )
      {
         I_CHAR isoCode[ sizeof( cp[ i ].isoCode ) /
                         sizeof( wchar_t ) ];
         isoCode[ 0 ] = ( I_CHAR ) cp[ i ].isoCode[ 0 ];
         isoCode[ 1 ] = ( I_CHAR ) cp[ i ].isoCode[ 1 ];
         isoCode[ 2 ] = ( I_CHAR ) cp[ i ].isoCode[ 2 ];
         isoCode[ 3 ] = ( I_CHAR ) cp[ i ].isoCode[ 3 ];
         i_memlwr( isoCode, sizeof( isoCode ) /
                   sizeof( I_CHAR ) );
         if( !_memicmp( isoCode, iso5.c_str(), sizeof( isoCode ) ) )
         {
            offset = cp[ i ].offset;
            fProblem = false;
            break;
         }
      }

      if( false == fProblem )
      {
         // Read the number of language conditions
         fCnd.read( ( char * ) &numBaseLanguageCodes,
                    sizeof( numBaseLanguageCodes ) );
         count += sizeof( numBaseLanguageCodes );

         if( fBigEndian )
         {
            reverseEndian( ( char * ) &numBaseLanguageCodes,
                           sizeof( numBaseLanguageCodes ) );
         }

         assert( offset >= count );
         offset -= count;
         MESSAGE_SET msgSet;

         // read offset bytes into buffer, checksum, and discard;
         while( offset )
         {
            if( SEVERE_ERROR == readMessageSet( fCnd,
                                                msgSet,
                                                tmpChecksum,
                                                offset,
                                                count,
                                                fBigEndian,
                                                false,
                                                _suppress,
                                                _severity ) )
            {
               conditionCode = Condition::SEVERE_ERROR_IN_FILE;
               fProblem = true;
               break;
            }
            msgSet.message.erase();
            msgSet.correction.erase();
         }
         // read individual lines
         if( false == fProblem )
         {
            do
            {
               msgSet.message.erase();
               msgSet.correction.erase();
               if( SEVERE_ERROR == readMessageSet( fCnd,
                                                   msgSet,
                                                   tmpChecksum,
                                                   offset,
                                                   count,
                                                   fBigEndian,
                                                   false,
                                                   _suppress,
                                                   _severity ) )
               {
                  conditionCode = Condition::SEVERE_ERROR_IN_FILE;
                  fProblem = true;
                  break;
               }
            } while( _code != msgSet.code );
         }
         if( false == fProblem )
         {
            _message = DString( msgSet.message );
            _correction = DString( msgSet.correction );

            // When the condition is found, the rest of the condition table
            //   is not read
            //  So need to position file point to start of market area

            int seekPos = ( (sizeof( BINFILEHEADER ) +
                             sizeof ( BASESIZES ) +
                             baseSizes.totalBaseSize ) -
                            4 - // Num conditions is included in both base sizes and total base size
                            count );

            fCnd.seekg( seekPos, std::ios::cur );

            // Update count based on seek
            count += seekPos;
            count -= 4;

            // Read market sizes

            if( false == fProblem )
            {
               count += sizeof( MARKETSIZES );
               fCnd.read( ( char * ) &marketSizes, sizeof( MARKETSIZES ) );

               if( fBigEndian )
               {
                  reverseEndian( ( char * ) &marketSizes, sizeof( MARKETSIZES ) );
               }

               // Read any market condition overrides
               if( marketSizes.numMarketConditionCodes > 0 )
               {
                  // read condition codes into buffer
                  tmp = sizeof( OVERRIDE_CONDITION_CODE ) * marketSizes.numMarketConditionCodes;
                  count += tmp;
                  OVERRIDE_CONDITION_CODE * conMarketCode;
                  try
                  {
                     conMarketCode = new OVERRIDE_CONDITION_CODE[ tmp ];
                  }
                  catch( ... )
                  {
                     _severity = CRITICAL_ERROR;
                     _message = getMsgPairFromCndCode( _currMsgPair,
                                                       ERROR_ON_NEW )->errMsg;
                     _correction = getMsgPairFromCndCode( _currMsgPair,
                                                          ERROR_ON_NEW )->correctionMsg;
                     return(fProblem);
                  }

                  fCnd.read( ( char * ) conMarketCode, tmp );

                  if( fBigEndian )
                  {
                     reverseEndian( ( char * ) conMarketCode, tmp );
                  }

                  // look for a match in the condition codes
                  for( i = 0; i < marketSizes.numMarketConditionCodes; ++i )
                  {
                     if( conMarketCode[ i ].overrideId == defaultMarket &&
                         conMarketCode[ i ].code == _code )
                     {
                        _severity = ( SEVERITY ) conMarketCode[ i ].severity;
                        _suppress = conMarketCode[ i ].suppress;
                        foundMarketOverride = true;
                        break;
                     }
                  }
               }

               COUNTRY_POINTER * cpMarket =
               ( COUNTRY_POINTER * ) NULL;

               // read in num country codes
               fCnd.read( ( char * ) &numMarketCountryCodes,
                          sizeof( numMarketCountryCodes ) );
               count += sizeof( numMarketCountryCodes );

               if( fBigEndian )
               {
                  reverseEndian( ( char * ) &numMarketCountryCodes,
                                 sizeof( numMarketCountryCodes ) );
               }

               // read country table into buffer
               tmp = sizeof( COUNTRY_POINTER ) * numMarketCountryCodes;
               count += tmp;

               cpMarket = new COUNTRY_POINTER[ numMarketCountryCodes ];
               fCnd.read( ( char * ) cpMarket, tmp );

               if( fBigEndian )
               {
                  reverseEndian( ( char * ) cpMarket, tmp );
               }

               // Check for zero languages
               if( numMarketCountryCodes > 0 )
               {
                  // look for a match for iso5
                  fProblem = true;
                  for( i = 0; i < numMarketCountryCodes; ++i )
                  {
                     I_CHAR isoCode[ sizeof( cpMarket[ i ].isoCode ) /
                                     sizeof( wchar_t ) ];
                     isoCode[ 0 ] = ( I_CHAR ) cpMarket[ i ].isoCode[ 0 ];
                     isoCode[ 1 ] = ( I_CHAR ) cpMarket[ i ].isoCode[ 1 ];
                     isoCode[ 2 ] = ( I_CHAR ) cpMarket[ i ].isoCode[ 2 ];
                     isoCode[ 3 ] = ( I_CHAR ) cpMarket[ i ].isoCode[ 3 ];
                     i_memlwr( isoCode, sizeof( isoCode ) /
                               sizeof( I_CHAR ) );
                     if( !_memicmp( isoCode, iso5.c_str(), sizeof( isoCode ) ) )
                     {
                        offset = cpMarket[ i ].offset;
                        fProblem = false;
                        break;
                     }
                  }
               }
               delete [] cpMarket;
               cpMarket = NULL;
            }

            if( false == fProblem )
            {
               // Read the number of language conditions
               fCnd.read( ( char * ) &numMarketLanguageCodes,
                          sizeof( numMarketLanguageCodes ) );
               count += sizeof( numMarketLanguageCodes );

               if( fBigEndian )
               {
                  reverseEndian( ( char * ) &numMarketLanguageCodes,
                                 sizeof( numMarketLanguageCodes ) );
               }

               // Handle the case of 0 market override language entries
               if( numMarketLanguageCodes > 0 )
               {
                  assert( offset >= count );
                  offset -= count;

                  // read offset bytes into buffer, checksum, and discard;
                  while( offset )
                  {
                     if( SEVERE_ERROR == readMessageSet( fCnd,
                                                         msgSet,
                                                         tmpChecksum,
                                                         offset,
                                                         count,
                                                         fBigEndian,
                                                         true,
                                                         _suppress,
                                                         _severity ) )
                     {
                        conditionCode = Condition::SEVERE_ERROR_IN_FILE;
                        fProblem = true;
                        break;
                     }
                     msgSet.message.erase();
                     msgSet.correction.erase();
                     countMarketRead++;
                  }

                  // read individual lines
                  if( false == fProblem )
                  {
                     do
                     {
                        msgSet.message.erase();
                        msgSet.correction.erase();
                        countMarketRead++;
                        if( SEVERE_ERROR == readMessageSet( fCnd,
                                                            msgSet,
                                                            tmpChecksum,
                                                            offset,
                                                            count,
                                                            fBigEndian,
                                                            true,
                                                            _suppress,
                                                            _severity ) )
                        {
                           conditionCode = Condition::SEVERE_ERROR_IN_FILE;
                           fProblem = true;
                           break;
                        }
                     } while( _code != msgSet.code &&
                              defaultMarket != msgSet.overrideId &&
                              countMarketRead < numMarketLanguageCodes );

                     // Check if market override was found
                     if( _code == msgSet.code &&
                         defaultMarket == msgSet.overrideId )
                        foundMarketLangOverride = true;
                  }
               }
            }

            // Continue if no problems and at least one market
            //    override was found
            if( ( false == fProblem ) &&
                ( ( true == foundMarketOverride ) ||
                  ( true == foundMarketLangOverride ) ) )
            {
               if( true == foundMarketLangOverride )
               {
                  _message = DString( msgSet.message );
                  _correction = DString( msgSet.correction );
               }

               // Need to check for client overrides

               // Read client sizes
               count += sizeof( CLIENTSIZES );
               fCnd.read( ( char * ) &clientSizes, sizeof( CLIENTSIZES ) );

               if( fBigEndian )
               {
                  reverseEndian( ( char * ) &clientSizes, sizeof( CLIENTSIZES ) );
               }

               // Read any client condition overrides
               if( clientSizes.numClientConditionCodes > 0 )
               {
                  // read condition codes into buffer
                  tmp = sizeof( OVERRIDE_CONDITION_CODE ) * clientSizes.numClientConditionCodes;
                  count += tmp;
                  OVERRIDE_CONDITION_CODE * conClientCode;
                  try
                  {
                     conClientCode = new OVERRIDE_CONDITION_CODE[ tmp ];
                  }
                  catch( ... )
                  {
                     _severity = CRITICAL_ERROR;
                     _message = getMsgPairFromCndCode( _currMsgPair,
                                                       ERROR_ON_NEW )->errMsg;
                     _correction = getMsgPairFromCndCode( _currMsgPair,
                                                          ERROR_ON_NEW )->correctionMsg;
                     return(fProblem);
                  }

                  fCnd.read( ( char * ) conClientCode, tmp );

                  if( fBigEndian )
                  {
                     reverseEndian( ( char * ) conClientCode, tmp );
                  }

                  // look for a match in the condition codes
                  for( i = 0; i < clientSizes.numClientConditionCodes; ++i )
                  {
                     if( conClientCode[ i ].overrideId == defaultClient &&
                         conClientCode[ i ].code == _code )
                     {
                        _severity = ( SEVERITY ) conClientCode[ i ].severity;
                        _suppress = conClientCode[ i ].suppress;
                        foundClientOverride = true;
                        break;
                     }
                  }
               }

               COUNTRY_POINTER * cpClient =
               ( COUNTRY_POINTER * ) NULL;

               // read in num country codes
               fCnd.read( ( char * ) &numClientCountryCodes,
                          sizeof( numClientCountryCodes ) );
               count += sizeof( numClientCountryCodes );

               if( fBigEndian )
               {
                  reverseEndian( ( char * ) &numClientCountryCodes,
                                 sizeof( numClientCountryCodes ) );
               }

               // read country table into buffer
               tmp = sizeof( COUNTRY_POINTER ) * numClientCountryCodes;
               count += tmp;

               cpClient = new COUNTRY_POINTER[ numClientCountryCodes ];
               fCnd.read( ( char * ) cpClient, tmp );

               if( fBigEndian )
               {
                  reverseEndian( ( char * ) cpClient, tmp );
               }

               // Check for zero languages
               if( numClientCountryCodes > 0 )
               {
                  // look for a match for iso5
                  fProblem = true;
                  for( i = 0; i < numClientCountryCodes; ++i )
                  {
                     I_CHAR isoCode[ sizeof( cpClient[ i ].isoCode ) /
                                     sizeof( wchar_t ) ];
                     isoCode[ 0 ] = ( I_CHAR ) cpClient[ i ].isoCode[ 0 ];
                     isoCode[ 1 ] = ( I_CHAR ) cpClient[ i ].isoCode[ 1 ];
                     isoCode[ 2 ] = ( I_CHAR ) cpClient[ i ].isoCode[ 2 ];
                     isoCode[ 3 ] = ( I_CHAR ) cpClient[ i ].isoCode[ 3 ];
                     i_memlwr( isoCode, sizeof( isoCode ) /
                               sizeof( I_CHAR ) );
                     if( !_memicmp( isoCode, iso5.c_str(), sizeof( isoCode ) ) )
                     {
                        offset = cpClient[ i ].offset;
                        fProblem = false;
                        break;
                     }
                  }
               }

               delete [] cpClient;
               cpClient = NULL;

               if( false == fProblem )
               {
                  // Read the number of language conditions
                  fCnd.read( ( char * ) &numClientLanguageCodes,
                             sizeof( numClientLanguageCodes ) );
                  count += sizeof( numClientLanguageCodes );

                  if( fBigEndian )
                  {
                     reverseEndian( ( char * ) &numClientLanguageCodes,
                                    sizeof( numClientLanguageCodes ) );
                  }

                  // Handle the case of 0 market override language entries
                  if( numClientLanguageCodes > 0 )
                  {
                     assert( offset >= count );
                     offset -= count;

                     // read offset bytes into buffer, checksum, and discard;
                     while( offset )
                     {
                        if( SEVERE_ERROR == readMessageSet( fCnd,
                                                            msgSet,
                                                            tmpChecksum,
                                                            offset,
                                                            count,
                                                            fBigEndian,
                                                            true,
                                                            _suppress,
                                                            _severity ) )
                        {
                           conditionCode = Condition::SEVERE_ERROR_IN_FILE;
                           fProblem = true;
                           break;
                        }
                        msgSet.message.erase();
                        msgSet.correction.erase();
                        countClientRead++;
                     }

                     // read individual lines
                     if( false == fProblem )
                     {
                        do
                        {
                           msgSet.message.erase();
                           msgSet.correction.erase();
                           countClientRead++;
                           if( SEVERE_ERROR == readMessageSet( fCnd,
                                                               msgSet,
                                                               tmpChecksum,
                                                               offset,
                                                               count,
                                                               fBigEndian,
                                                               true,
                                                               _suppress,
                                                               _severity ) )
                           {
                              conditionCode = Condition::SEVERE_ERROR_IN_FILE;
                              fProblem = true;
                              break;
                           }
                        } while( _code != msgSet.code&&
                                 defaultClient != msgSet.overrideId &&
                                 countClientRead < numClientLanguageCodes );

                        // Check if client override was found
                        if( _code == msgSet.code &&
                            defaultClient == msgSet.overrideId )
                           foundClientLangOverride = true;
                     }

                     if( ( false == fProblem ) &&
                         ( ( true == foundClientOverride ) ||
                           ( true == foundClientLangOverride ) ) )
                     {
                        if( true == foundClientLangOverride )
                        {
                           _message = DString( msgSet.message );
                           _correction = DString( msgSet.correction );
                        }
                     }
                  }
               }
            }
         }
      }

      delete [] cp;
      cp = NULL;
   }

   if( true == fProblem )
   {
      I_CHAR codeBuf[ 10 ];
      i_itot( _code, codeBuf, 10 );

      // do checksum
      if( NULL == _currMsgPair )
      {   // these messages MUST be hard-coded
         _severity = CRITICAL_ERROR;
         _message = MESSAGE1;
         _message.append( iso5 );
         _message.append( MESSAGE2 );
         _correction = CORRECTION;
      }
      else
      {
         // We couldn't find the condition.
         // If we are using the user language to find the condition we should
         // try the 'default' language for this language.  Typically this is enUS.
         // CP 16Oct2003
         if( !bUseDefaultLang ) {
            fProblem = readFromFile( baseFlag, true );
            if( true == fProblem ) {
               // we've tried to find the condition using the default language as well as
               // the user supplied one ... give up and give 'em the crap error message
               // CP 16Oct2003
               _severity = CRITICAL_ERROR;

               _message = getMsgPairFromCndCode( _currMsgPair,
                                                 conditionCode )->errMsg;
               _message.append( I_( " (ISO country code = " ) );
               _message.append( iso5 );
               _message.append( I_( ", condition code = " ) );
               _message.append( codeBuf );
               _message.append( I_( ", file name = " ) );
               _message.append( DString( fileName ) );
               _message.append( I_( ")" ) );
               _correction = getMsgPairFromCndCode( _currMsgPair,
                                                    conditionCode )->correctionMsg;
            }
         }

      }
   }
   if( minSeverity > _severity )
   {
      _severity = minSeverity;
   }

   if( NULL != cp )
      delete [] cp;

   delete [] conCode;
   delete [] conMarketCode;
   delete [] conClientCode;

   // add to cache as needed
   if( false == fProblem )
   {
      myGuard g( g_cs_ConditionCache );
      ConditionCache_Iter itCache = g_ConditionCache.find( ConditionCacheKey( _code, _componentName, _clientLocale ) );
      if( itCache == g_ConditionCache.end() )
      {
         // not added to the cache yet ...
         Condition* pCondition = new Condition( *this );
         g_ConditionCache[ ConditionCacheKey( _code, _componentName, _clientLocale ) ] = pCondition;
      }
   }

   return(fProblem);
}

void Condition::doTrace( int level )
{
   TRACE_METHOD( I_( "Condition" ), I_( "doTrace( int )" ) );

   // Add timestamp when we have date routines available
   DStringA timestamp = " TIMESTAMP ";
   DString padding;

   const int minLevel = 0;
   const int maxLevel = 999;

   if( ( level > minLevel ) && ( level < maxLevel ) )
   {
      // Set indentation
      padLeft( padding, level * 3 );
   }
   else
   {
      // Trace with no frame
      padding = I_( "***" );
   }

   I_CHAR txt[ 2048 ];

   i_sprintf( txt,
              I_( "%s:%s at %s:%d--%d(%d): %s" ),
              _componentName.c_str(),
              _methodName.c_str(),

              DString( _fileName ).c_str(),
              _lineNumber,
              _code,
              (int)_severity,
              _message.c_str() );

   TRACE_MSG( txt );
}

const int preMarketVersion = 1000;
const int latestVersion = 3000;

int Condition::getLatestVersion( void )
{
   return(latestVersion);
}

bool Condition::isValidVersion( int version )
{
   bool retVal = false;

   switch( version )
   {
      // put older versions last
      case latestVersion:
         retVal = true;
         break;
      default:
         break;
   }
   return(retVal);
}

bool Condition::setCurrMsgPair( const DString & locale )
{
   bool retVal = false;
   DString llcc;
   if( locale.size() )
   {
      llcc = locale;
   }
   else
   {
      // JavaLocale::getLCV( llcc );
      llcc = I_("enUS"); //TODO: must fix this!

   }

   if( !llcc.empty() )
   {
      // default to en_us
      //  if we cannot find element language for current locale
      //     continue to use English
      _currMsgPair = languagesMap[ 0 ].msgPair;
      retVal = true;

      int i = 0;
      for( ; i < ( sizeof( languagesMap ) / sizeof( languagesMap[0] ) ); ++i )
      {
         if( !i_stricmp( llcc.c_str(), languagesMap[ i ].isoCode ) )
         {
            _currMsgPair = languagesMap[ i ].msgPair;
            break;
         }
      }
   }
   if( false == retVal )
   {
      _severity = CRITICAL_ERROR;
      _message = MESSAGE3;
      _correction = CORRECTION;
   }
   return(retVal);
}

Condition &Condition::operator=( const Condition &copy )
{
   if( this == &copy )
   {
      return(*this);
   }

   _baseCondition = copy._baseCondition;
   _code = copy._code;
   _componentName = copy._componentName;
   _context = copy._context;

   _correction = copy._correction;
   // Point to static structure
   _currMsgPair = copy._currMsgPair;
   _fileName = copy._fileName;
   _Idi = copy._Idi;

   _lineNumber = copy._lineNumber;
   _message = copy._message;
   _methodName = copy._methodName;
   _pathName = copy._pathName;
   _severity = copy._severity;

   _suppress = copy._suppress;

   *_clientLocale = *(copy._clientLocale);
   _init = copy._init;

   return(*this);
}

void Condition::initCondition() const
{
   if( false == _init )
   {
      ((Condition*)this)->prepareMessage();
      _init = true;
   }
}

long Condition::getCode() const
{
   initCondition();
   return(_code);
}

const I_CHAR* Condition::getCodeString() const
{
   initCondition();
   return(_codeStr);
}

const I_CHAR * Condition::getCorrection() const
{
   initCondition();
   return(_correction.c_str());
}

const I_CHAR * Condition::getComponentName() const
{
   initCondition();
   return(_componentName.c_str());
}

const char * Condition::getFileName() const
{
   initCondition();
   return(_fileName.c_str());
}

int Condition::getLineNumber() const
{
   initCondition();
   return(_lineNumber);
}

const I_CHAR * Condition::getMessage() const
{
   initCondition();
   return(_message.c_str());
}

#include <sstream>

DString Condition::getDiagnosticMessage() const
{
   initCondition();
   std::wstringstream wss;
   wss << getCodeString() << std::endl;
   wss << DString( DStringA(getFileName()) ).c_str() << I_(" [") << getLineNumber() << I_("]") << std::endl;
   return(wss.str());
}

const I_CHAR * Condition::getMethodName() const
{
   initCondition();
   return(_methodName.c_str());
}

SEVERITY Condition::getSeverity() const
{
   initCondition();
   return(_severity);
}

bool Condition::getSuppress() const
{
   initCondition();
   return(0 != _suppress);
}

//************************************************************************
//              Revision Control Entries
//************************************************************************
//
// $Log:   Y:/VCS/iFastAWD/dicore/condition.cpp-arc  $
// 
//    Rev 1.1   Nov 02 2011 04:42:52   purdyech
// Registry Cleanup
//
//   Rev 1.13   May 03 2010 05:01:14   purdyech
//IN2107238 - Condition HIstory list is now last 20 conditions.
//
//   Rev 1.12   May 03 2010 04:41:14   purdyech
//IN2107238 - Condition History added for Diagnostic Report
//
//   Rev 1.11   Sep 23 2009 01:27:34   purdyech
//Track Condition Name as well as Code.
//Add "Display Details" option to system menu on Error Popup.
//
//   Rev 1.10   Feb 09 2009 14:36:56   purdyech
//minSeverity was not given an initial value in Condition::readFromFile().  This would cause runtime problems when the condition didn't exist in the condition file.
//
//   Rev 1.9   Aug 30 2004 16:00:54   popescu
//PET 991, FN 02, added support for Dutch and Italian
//
//   Rev 1.8   May 07 2004 14:41:04   PURDYECH
//Match recent KC Infrastructure Files
//
//   Rev 1.7   Oct 16 2003 11:01:06   PURDYECH
//readFromFile has been changed to allow recursive calls.  A recursive call is made if the condition is not found.  In this case the language is set to enUS and another search is made.  Under iFAST the language is set after logon so many messages are not displayed properly if the user's machine has a regional setting other than enUS.
//
//   Rev 1.6   Aug 12 2003 10:05:56   PURDYECH
//Added Spanish as a valid language.
// 
//    Rev 1.5   Apr 02 2003 13:22:42   PURDYECH
// Added German, French, and French Canadian as known languages.
// 
//    Rev 1.4   Oct 09 2002 17:41:46   PURDYECH
// New PVCS Database
// 
//    Rev 1.3   Sep 02 2002 17:34:18   PURDYECH
// Remove getDefaultClientLocale
// 
//    Rev 1.2   Aug 13 2002 12:44:16   PURDYECH
// Condition cache now uses ClientLocale as a part of the key.
// 
//    Rev 1.1   Jul 29 2002 11:08:12   PURDYECH
// Cached conditions were restoring the first IDI string.  The current IDI string should be used instead.
// 
//    Rev 1.0   Jul 05 2002 10:12:44   SMITHDAV
// Initial revision.
// 
//    Rev 1.41   May 23 2001 13:09:22   DT11159
// Changed to remove all assignments within conditional expressions.
// Two of these changes fixed bugs.
//
//    Rev 1.40   05 Apr 2001 10:06:26   DT14177
// fixed memory leaks in
// condition::readFromFile() and
// idiProcessing()
//
//    Rev 1.39   Feb 21 2001 16:28:08   DT21858
// Cleaned up a call to a static method.
//
//    Rev 1.38   04 Sep 2000 13:09:50   dt20842
// Replace unmatched tags in message/correction with (null)
// Replace %% with %
//
//    Rev 1.37   30 Aug 2000 18:22:20   dt20842
// Correct parse functionality
//
//    Rev 1.36   28 Aug 2000 17:35:10   dt20842
// Condition getters const again
//
//    Rev 1.35   23 Aug 2000 21:18:08   dt20842
// Added ability to pass clientLocale through macros.
// Added lazy initialization.
//
//    Rev 1.34   09 Aug 2000 00:57:34   dt20842
// Added ability to read market and client data from
// new condition cnd format
//
//    Rev 1.33   May 26 2000 20:26:16   DT14177
// Added ClientLocale support
//
//    Rev 1.32   04 May 2000 17:27:06   dt20842
// Removed recursion check
//
//    Rev 1.31   Feb 26 2000 16:31:36   DT20842
// Base conditions are any contained in dicore
//
//    Rev 1.30   Jan 04 2000 12:10:12   DT20842
// Added semi-colon to end of TRACE macros
//
//    Rev 1.29   Dec 06 1999 10:55:12   DT20842
// Updated copy constructor to copy all member variables
//
//    Rev 1.28   Nov 05 1999 07:59:18   DT20842
// Fixed bug to support languages other than defined elemental conditions
//
//    Rev 1.27   Oct 05 1999 16:54:06   DT14177
// Added suppression and language severity enhancements; fixed multi-threading issues
//
//    Rev 1.26   Sep 28 1999 14:29:44   DT14177
// fixed multi-threading bug
//
//    Rev 1.25   Aug 06 1999 11:29:10   DT14177
// Fixed getLCV and bogus recursion report
//
//    Rev 1.24   Aug 02 1999 15:12:42   DT14177
// Fixed _currMessage NULL pointer problem
//
//    Rev 1.23   Jul 07 1999 16:09:14   DT14177
// Fixed a locale bug and improved meaning of condition error messages.
//
//    Rev 1.22   Jun 22 1999 11:09:58   DT14177
// Changed type for condition code from int to long.
//
//    Rev 1.21   Jun 11 1999 15:42:06   DT14177
// fixed bug caused by lack of initialization of _baseCondition
//
//    Rev 1.20   Jun 08 1999 16:17:40   DT14177
// added context, delayed condition message preparation, and locale override.
//
//    Rev 1.19   May 27 1999 08:27:24   DT20842
// Fixed handling of blank IDI string
//
//    Rev 1.18   May 14 1999 10:21:58   DT20842
// Changed setlocale to i_setlocale
//
//    Rev 1.17   May 12 1999 09:20:06   DT20842
// Added elemental conditions
//
//    Rev 1.16   Apr 27 1999 14:22:56   DT14177
// Fixed problem when file doesn't exist and buffer length problem(2nd try)
//
//    Rev 1.15   Apr 21 1999 16:51:30   DT14177
// Fixed trap due to insufficient allocation
//
//    Rev 1.14   Apr 15 1999 14:15:42   DT14177
// Recursion fix, memory link fix, and removed hard-coding
//
//    Rev 1.12   Apr 14 1999 07:02:28   DT20842
// changed getDefault -> getDefaultInstance
//
//    Rev 1.11   Apr 12 1999 17:57:34   DT14177
// add versioning and JavaLocale stuff
//
//    Rev 1.10   29 Mar 1999 11:03:16   DT14177
// Condition Constructor uses DString for IDI parameter
// Changed locale from IS03166 3 character code to combination of ISO 639 and ISO3166 two-character codes (LL_CC)
//
//    Rev 1.9   04 Mar 1999 09:28:48   DT14177
// Fixed conditionException NULL pointer bug, duplicate SEVERE_ERROR definition bug, and the ASCII Condition file read bug.
//
//    Rev 1.8   03 Mar 1999 10:05:20   DT14177
// Fixed wrong iso5 code match problem
//
//    Rev 1.7   02 Mar 1999 13:37:36   DT14177
// Added proper locale handling for Condition file problem state.
//
//    Rev 1.6   01 Mar 1999 15:43:02   DT14177
// fixed stack problem getFileName()
//
//    Rev 1.5   26 Feb 1999 18:12:04   DT14177
// Added .CND file problem error-handling
//
//    Rev 1.4   24 Feb 1999 10:43:54   DT14177
// sync up with tracer
//
//    Rev 1.3   22 Feb 1999 13:57:10   DT14177
// more UNICODE stuff
//
//    Rev 1.2   18 Feb 1999 10:30:38   DT14177
// UNICODE
//
//    Rev 1.0   Dec 09 1998 13:50:50   DMUM
//
//
//    Rev 1.12   Jun 17 1998 15:56:28   dt27994
// Commented out doTrace in both constructors.
//
//    Rev 1.11   Jun 16 1998 16:11:02   dt27994
//
//
//    Rev 1.10   Dec 12 1997 14:49:54   dkaw
// change replace function to substitute into correction string
//
//    Rev 1.9   Nov 09 1997 15:35:34   DTWK
// Add inclusion guards for faster compiles.
// Add guards so that class is flagged as exported only when compiling
// the output that actually exports the class.
//
//    Rev 1.8   Oct 21 1997 14:06:50   dkaw
// use TRACE_MSG_FORMATTED; remove padding
//
//    Rev 1.7   Sep 26 1997 15:40:02   dkaw
// append directory separator to end of path if necessary
//
//    Rev 1.6   Sep 10 1997 16:08:36   dkaw
// get out of loop if condition code is found in readFromFile
//
//    Rev 1.5   Sep 08 1997 15:58:08   dkaw
//
//
//    Rev 1.4   Sep 08 1997 13:22:40   dkaw
// use read not get in ReadFromFile
//
//    Rev 1.3   Aug 28 1997 14:01:24   dkaw
// rename ERR to SEVERE_ERROR, CRITICAL to CRITICAL_ERROR
//
//    Rev 1.2   Aug 25 1997 15:57:34   dkaw
// use "" not <> for stringfunctions.hpp
//
//    Rev 1.1   Jul 22 1997 16:18:26   dkaw
// add trace filtering, use ditrace
//
//    Rev 1.0   Jun 13 1997 12:55:00   DTWK
//

