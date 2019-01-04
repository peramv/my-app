#include "stdafx.h"
#include "bfsha1_string.hpp"
#include "sha-1.h"
#include <configmanager.hpp>
#include <condition.hpp>
#include "clientlocalecontext.hpp"

namespace CND
{
   extern const long BFUTIL_ENCODE_TO_CODEPAGE_FAILURE;
   extern const long BFUTIL_NO_HOST_CODEPAGE;
}

BFSHA1_String::BFSHA1_String( const wchar_t* pszUnencodedString )
{
   UINT hostCodepage = GetConfigValueAsInteger( ConfigManager::getApplication(),  I_( "RTSHost" ), I_( "CodePage" ) );
   if( hostCodepage == 0 )
   {
      THROWFROMFILE( CND::BFUTIL_CONDITION, I_( "BFSHA1_String::BFSHA1_String" ), CND::BFUTIL_NO_HOST_CODEPAGE);
   }
   encode( pszUnencodedString, hostCodepage );

}

BFSHA1_String::BFSHA1_String( const wchar_t* pszUnencodedString, UINT hostCodepage )
{
   encode( pszUnencodedString, hostCodepage );
}

BFSHA1_String::~BFSHA1_String()
{
}

void BFSHA1_String::encode( const wchar_t* pszUnencodedString, UINT hostCodePage )
{
   // use Ram Singaram's SHA-1 code (shared source with other IFDS projects) to
   // do the actual encoding
   Byte* pB = NULL;
   int cb = 0;

   // first ... convert the string to ISO-8859-1 (Windows CP_ANSI)
   cb = WideCharToMultiByte( hostCodePage, 
                             WC_COMPOSITECHECK | WC_SEPCHARS,
                             pszUnencodedString,
                             -1,
                             NULL,
                             0,
                             NULL,
                             NULL );
   if( cb != 0 )
   {
      pB = new Byte[ cb + 1 ];
      cb = WideCharToMultiByte( hostCodePage, 
                                WC_COMPOSITECHECK | WC_SEPCHARS,
                                pszUnencodedString,
                                -1,
                                reinterpret_cast< char*>( pB ),
                                cb,
                                NULL,
                                NULL );
   }
   else
   {
      DString idiStr;
      DString codePage = DString::asString( hostCodePage );
      addIDITagValue( idiStr, I_( "CODEPAGE" ), codePage );

      I_CHAR* lpszMessage = NULL;
      ::FormatMessageW( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                        NULL, 
                        GetLastError(), 
                        ClientLocaleContext::get().getLCID(),
                        (I_CHAR*)&lpszMessage,
                        0, 
                        NULL );

      addIDITagValue( idiStr, I_( "RC" ), lpszMessage );
      THROWFROMFILEIDI( CND::BFUTIL_CONDITION, 
                        I_( "BFSHA1_String::encode" ),
                        CND::BFUTIL_ENCODE_TO_CODEPAGE_FAILURE,
                        idiStr );
   }
   Byte* pEncodedValue = DigestMessage( pB, cb );
   // at this point pEncodedValue is a terminated string of characters.  Assign this 
   // to encodedValue_ and go away
   encodedValue_ = DStringA( reinterpret_cast< char * >( pEncodedValue ) );

   free( pEncodedValue );
   delete[] pB;
}
