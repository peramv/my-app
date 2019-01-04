#ifndef SRCPRAG_h
   #include <SrcPrag.h>
#endif

#include "BFReadBuffer.hpp"
#include "BFWriteBuffer.hpp"
#include <DString.hpp>
#include <conditionmanager.hpp>

#ifdef DST_UNICODE

namespace CND
{
   extern const I_CHAR *BFDBRKR_CONDITION;
   extern const long MULTYBYTE_TO_UNICODE_CONVERSION_ERROR;
   extern const long UNICODE_TO_MULTYBYTE_CONVERSION_ERROR;
}


DString &
BFReadBuffer::multiByteToUnicode(const DStringA &multiByteString, DString &outString)
{
#if 0
   mbstate_t mbState = {0}; 

   size_t destinationLength = (multiByteString.length()*2) + 2;
   wchar_t *destinationBuffer = new wchar_t[destinationLength];

   const char *sourceBuffer = multiByteString.c_str();

   size_t resultCount = mbsrtowcs(destinationBuffer, &sourceBuffer, destinationLength, &mbState);
   if( -1 == resultCount )
   {
      delete[] destinationBuffer;
      THROWFROMFILE2( CND::BFDBRKR_CONDITION, I_( "BFReadBuffer" ), I_("multiByteToUnicode"), CND::MULTYBYTE_TO_UNICODE_CONVERSION_ERROR);
   }
   destinationBuffer[resultCount] = (wchar_t)0; // null terminate

   outString.assign(destinationBuffer);
   delete[] destinationBuffer;
   return(outString);
#else
   wchar_t wszBuffer[ 61 ];
   wchar_t* pwsz = wszBuffer;
   int cb = 0;

   // first ... convert the string to codepage corresponding to current clientlocale
   // we assume (as the old code did) that this is the codepage of the thread
   LCID lcid = ::GetThreadLocale();
   wchar_t wszCodePage[ 7 ];
   ::GetLocaleInfoW( lcid, LOCALE_IDEFAULTANSICODEPAGE, wszCodePage, sizeof( wszCodePage ) / sizeof( wszCodePage[ 0 ] ) );
   wchar_t* pEnd = NULL;
   UINT codePage = wcstol( wszCodePage, &pEnd, 10 );

   cb = ::MultiByteToWideChar( codePage,
                               MB_PRECOMPOSED | MB_ERR_INVALID_CHARS,
                               multiByteString.c_str(),
                               -1,
                               NULL,
                               0 );
   if( cb != 0 )
   {
      if( cb > ( sizeof( wszBuffer ) / sizeof( wszBuffer[ 0 ] ) ) )
      {
         pwsz = new wchar_t[ cb + 1 ];
      }
      cb = MultiByteToWideChar( codePage,
                                MB_PRECOMPOSED | MB_ERR_INVALID_CHARS,
                                multiByteString.c_str(),
                                -1,
                                pwsz,
                                cb );
   }
   else
   {
      DString idiStr;
      DString strCodePage = DString::asString( codePage );
      addIDITagValue( idiStr, I_( "CODEPAGE" ), strCodePage );

      I_CHAR* lpszMessage = NULL;
      ::FormatMessageW( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                        NULL, 
                        GetLastError(), 
                        GetThreadLocale(),
                        (I_CHAR*)&lpszMessage,
                        0, 
                        NULL );

      addIDITagValue( idiStr, I_( "RC" ), lpszMessage );
      THROWFROMFILEIDI( CND::BFDBRKR_CONDITION, 
                        I_( "BFWriteBuffer::multiByteToUnicode()" ),
                        CND::UNICODE_TO_MULTYBYTE_CONVERSION_ERROR,
                        idiStr );
   }
   outString = pwsz;
   if( pwsz != wszBuffer )
   {
      delete[] pwsz;
   }

   return( outString );
#endif
}

DStringA &
BFWriteBuffer::unicodeToMultiByte(const DString &unicodeString, DStringA &outString)
{
#if 0
   mbstate_t mbState = {0}; 

   size_t destinationLength = unicodeString.length() * 2 + 1;
   char *destinationBuffer = new char[destinationLength];

   const wchar_t *sourceBuffer = unicodeString.c_str();

   size_t resultCount = wcsrtombs(destinationBuffer, &sourceBuffer, destinationLength, &mbState);
   if( -1 == resultCount )
   {
      delete[] destinationBuffer;
      THROWFROMFILE2( CND::BFDBRKR_CONDITION, I_( "BFWriteBuffer" ), I_("multiByteToUnicode"), CND::UNICODE_TO_MULTYBYTE_CONVERSION_ERROR);
   }
   destinationBuffer[resultCount] = (char)0; // null terminate

   outString.assign(destinationBuffer);
   delete[] destinationBuffer;
   return(outString);
#else
   char szBuffer[ 61 ];
   char* psz = szBuffer;
   int cb = 0;

   // first ... convert the string to codepage corresponding to current clientlocale
   // we assume (as the old code did) that this is the codepage of the thread

   cb = WideCharToMultiByte( CP_UTF8,
                             0,
                             unicodeString.c_str(),
                             -1,
                             NULL,
                             0,
                             NULL,
                             NULL );
   if( cb != 0 )
   {
      if( cb > ( sizeof( szBuffer ) / sizeof( szBuffer[ 0 ] ) ) )
      {
         psz = new char[ cb + 1 ];
      }
      cb = WideCharToMultiByte( CP_UTF8,
                                0,
                                unicodeString.c_str(),
                                -1,
                                psz,
                                cb,
                                NULL,
                                NULL );
   }
   else
   {
      DString idiStr;
      DString strCodePage = DString::asString( CP_UTF8 );
      addIDITagValue( idiStr, I_( "CODEPAGE" ), strCodePage );

      I_CHAR* lpszMessage = NULL;
      ::FormatMessageW( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                        NULL, 
                        GetLastError(), 
                        GetThreadLocale(),
                        (I_CHAR*)&lpszMessage,
                        0, 
                        NULL );

      addIDITagValue( idiStr, I_( "RC" ), lpszMessage );
      THROWFROMFILEIDI( CND::BFDBRKR_CONDITION, 
                        I_( "BFWriteBuffer::unicodeToMultiByte()" ),
                        CND::MULTYBYTE_TO_UNICODE_CONVERSION_ERROR,
                        idiStr );
   }
   outString = psz;
   if( psz != szBuffer )
   {
      delete[] psz;
   }

   return( outString );
#endif
}

#endif 