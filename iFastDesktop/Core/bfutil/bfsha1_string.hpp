#pragma once

#undef BFUTIL_LINKAGE
#ifdef BFUTIL_DLL
   #define BFUTIL_LINKAGE CLASS_EXPORT
#else
   #define BFUTIL_LINKAGE CLASS_IMPORT
#endif

#include <dstring.hpp>

class BFUTIL_LINKAGE BFSHA1_String
{
public:
   /**
    * Construct an SHA-1 encoded value.  The constructor requires a UNICODE
    * string (UTF-16) and the host's codepage.  The string will be encoded
    * with respect to the specified codepage.  The get() method will return
    * a UNICODE string which represents the bytes.
    * 
    * @param pszUnencodedString
    *               The string to encode.  Must be less than 56 characters.
    * @param hostCodepage
    *               The target machine's codepage.  Common values are<br>
    *               <table>
    *               <tr>
    *               <td>CP_ANSI</td>
    *               <td>ISO-8859-1 (aka Latin-1)</td>
    *               </tr>
    *               <tr>
    *               <td>932</td>
    *               <td>Japanese</td>
    *               </tr>
    *               </table>
    */
   BFSHA1_String( const wchar_t* pszUnencodedString, UINT hostCodepage );
   BFSHA1_String( const wchar_t* pszUnencodedString );
   ~BFSHA1_String();

   const DString& get() const { return(encodedValue_);}
private:
   void encode( const wchar_t* pszUnencodedString, UINT hostCodepage );

   DString encodedValue_;
};
