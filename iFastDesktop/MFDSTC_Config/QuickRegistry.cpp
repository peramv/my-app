/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1997 by Joerg Koenig
// All rights reserved
//
// Distribute freely, except: don't remove my name from the source or
// documentation (don't take credit for my work), mark your changes (don't
// get me blamed for your possible bugs), don't alter or remove this
// notice.
// No warrantee of any kind, express or implied, is included with this
// software; use at your own risk, responsibility for damages (if any) to
// anyone resulting from the use of this software rests entirely with the
// user.
//
// Send bug reports, bug fixes, enhancements, requests, flames, etc., and
// I'll try to keep a version up to date.  I can be reached as follows:
//    J.Koenig@adg.de                 (company site)
//    Joerg.Koenig@rhein-neckar.de    (private site)
/////////////////////////////////////////////////////////////////////////////

// last revised $Date:   Oct 13 2010 08:07:16  $ $Revision:   1.1  $


// Modifications since revision 4:
//  o   Bug fixed in the RegTreeWalk-function
//      thanks to Pieter E. Roos (Pieter.E.Roos@siemenscom.com)
//
// Modifications since revision 3:
//  o   Some minor bug fixes for UNICODE use in several 
//      CRegVal::SetValue() methods.
//
// Modifications since revision 2:
//  o   The RegistryTreeWalk() method no longer reports a wrong
//      "depth" to the methods OnValueHit() and OnKeyHit().
//  o   The member "USORT m_usDepth" was deleted
//  o   eliminated a memory leak in DeleteKey()
//      (thanks to Tobias Krueger<tobias.krueger@giepa.de>)
//  o   several bugfixes in DeleteKey() (sent in by Tobias Krueger)

#include "stdafx.h"

#include <DString.hpp>
#include "stdlib.h"
#include <string.h>
#include "tchar.h"

#ifndef _WINDOWS_
    #include <windows.h>
#endif


#include "QuickRegistry.h"

/////////////////////////////////////////////////////////////////////////////
// class CRegistry  --  construction / destruction ...

CRegistry :: CRegistry( HKEY hOpenKey_p )
    : m_hCurrentKey(hOpenKey_p)
{
}


CRegistry :: CRegistry( const CRegistry & rReg_p )
    : m_hCurrentKey(rReg_p.m_hCurrentKey)
{
}


HKEY CRegistry :: SetKey( HKEY hOpenKey_p ) {
    HKEY hOld = m_hCurrentKey ;
    m_hCurrentKey = hOpenKey_p ;
    return hOld ;
}


CRegistry :: ~CRegistry() {
}


/////////////////////////////////////////////////////////////////////////////
// class CRegistry  --  public members ...

HKEY CRegistry :: GetKey() const {
    return m_hCurrentKey ;
}


BOOL CRegistry :: LoadKey(
                            LPCTSTR pszSubKey_p,
                            LPCTSTR pszValueName_p,
                            CRegVal & rData_p
                        ) const {
    return LoadKey( pszSubKey_p, pszValueName_p, rData_p, m_hCurrentKey ) ;
}


BOOL CRegistry :: LoadKey(
                            LPCTSTR pszSubKey_p,
                            LPCTSTR pszValueName_p,
                            DWORD & dwValue_p
                        ) const {
    CRegVal Data;
    if( LoadKey(pszSubKey_p, pszValueName_p, Data) )
        if( Data.GetValue(dwValue_p) )
            return TRUE;
    return FALSE;
}


BOOL CRegistry :: LoadKey(
                            LPCTSTR pszSubKey_p,
                            LPCTSTR pszValueName_p,
                            BYTE * pBuffer,
                            DWORD dwSize
                        ) const {
    CRegVal Data;
    if( LoadKey(pszSubKey_p, pszValueName_p, Data) )
        if( Data.GetValue(pBuffer, dwSize) )
            return TRUE;
    return FALSE;
}


BOOL CRegistry :: SaveKey(
                            LPCTSTR pszSubKey_p,
                            LPCTSTR pszValueName_p,
                            const CRegVal & rData_p
                        ) const {
    return SaveKey( pszSubKey_p, pszValueName_p, rData_p, m_hCurrentKey ) ;
}


BOOL CRegistry :: SaveKey(
                            LPCTSTR pszSubKey_p,
                            LPCTSTR pszValueName_p,
                            const DWORD & dwValue_p
                        ) const {
    CRegVal Data(dwValue_p);
    return SaveKey(pszSubKey_p, pszValueName_p, Data);
}


BOOL CRegistry :: SaveKey(
                            LPCTSTR pszSubKey_p,
                            LPCTSTR pszValueName_p,
                            LPCTSTR pszValue_p
                        ) const {
    CRegVal Data(pszValue_p);
    return SaveKey(pszSubKey_p, pszValueName_p, Data);
}


BOOL CRegistry :: SaveKey(
                            LPCTSTR pszSubKey_p,
                            LPCTSTR pszValueName_p,
                            const LPBYTE pBuffer_p,
                            const DWORD dwSize_p
                        ) const {
    CRegVal Data;
    Data.SetValue(pBuffer_p, dwSize_p);
    return SaveKey(pszSubKey_p, pszValueName_p, Data);
}


BOOL CRegistry :: DeleteKey(
                            LPCTSTR pszSubKey_p,
                            LPCTSTR pszValueName_p
                        ) const {
    return DeleteKey( pszSubKey_p, pszValueName_p, m_hCurrentKey ) ;
}


BOOL CRegistry :: HasEntries(
                            LPCTSTR pszSubKey_p,
                            DWORD * pdwSubKeyCnt_p,
                            DWORD * pdwValueCnt_p
                        ) const {
    return HasEntries( pszSubKey_p, pdwSubKeyCnt_p, pdwValueCnt_p, m_hCurrentKey ) ;
}


BOOL CRegistry :: Connect( LPCTSTR pszRemote_p, HKEY hKey_p ) {
    HKEY hOld = m_hCurrentKey ;
    LPTSTR pszRemote = pszRemote_p ? new TCHAR [ _tcslen( pszRemote_p ) + 1 ] : 0 ;
    if( pszRemote )
       _tcscpy( pszRemote, pszRemote_p );
    LONG lRet = RegConnectRegistry( pszRemote, hKey_p, &m_hCurrentKey ) ;
    delete [] pszRemote ;
    if( lRet != ERROR_SUCCESS ) {
        m_hCurrentKey = hOld ;
        return FALSE ;
    }
    return TRUE ;
}



#ifndef _REG_NO_TREEWALK

BOOL CRegistry ::   RegistryTreeWalk( LPCTSTR pszSubKey_p, UINT uFlags_p ) {
    HKEY    hSubKey ;

    if( pszSubKey_p == 0 )
        hSubKey = m_hCurrentKey ;
    else {
        LONG lRet =     RegOpenKeyEx(
                            m_hCurrentKey,  // key handle at root level
                            pszSubKey_p,    // path name of child key
                            0,              // reserved
                            KEY_READ,       // requesting read access
                            &hSubKey        // address of key to be returned
                        ) ;
        
        if( lRet != ERROR_SUCCESS ) {
            return FALSE ;
        }
    }

    return RegTreeWalk( pszSubKey_p, hSubKey, uFlags_p, 0 ) ;
}


// default implementation of OnValueHit()
BOOL CRegistry ::   OnValueHit( LPCTSTR, LPCTSTR, const CRegVal &, USHORT ) {
    return FALSE ;
}


// default implementation of OnKeyHit()
BOOL CRegistry ::   OnKeyHit( LPCTSTR, USHORT ) {
    return FALSE ;
}


BOOL CRegistry ::   RegTreeWalk( LPCTSTR pszSubKey_p, HKEY hKey_p, UINT uFlags_p, USHORT usDepth ) {
    // first get an info about this subkey ...
    DWORD dwSubKeyCnt ;
    DWORD dwMaxSubKey ;
    DWORD dwValueCnt ;
    DWORD dwMaxValueName ;
    DWORD dwMaxValueData ;
    LONG lRet = RegQueryInfoKey(
                    hKey_p,
                    0,                  // buffer for class name
                    0,                  // length of class name string
                    0,                  // reserved
                    &dwSubKeyCnt,       // # of subkeys
                    &dwMaxSubKey,       // length of longest subkey
                    0,                  // length of longest class name string
                    &dwValueCnt,        // # of values
                    &dwMaxValueName,    // length of longest value name
                    &dwMaxValueData,    // length of longest value data
                    0,                  // security descriptor
                    0                   // last write time
                ) ;
    if( lRet != ERROR_SUCCESS ) {
        RegCloseKey( hKey_p ) ;
        return FALSE ;
    }

    // enumerating all of the values of a key is done only if the right
    // flag is set ...
    if( uFlags_p & RTW_NotifyValue ) {
        // enumerate the values and call the user-driven handler function on
        // each value ...
        CRegVal RegVal ;
        RegVal.AllocateDataBuffer( dwMaxValueData ) ;
        DWORD dwValueNameLen ;
        LPTSTR pszValueName = new TCHAR [ dwMaxValueName + 1 ] ;
        for( register DWORD i = 0 ; /*i < dwValueCnt*/ ; ++i ) {
            dwValueNameLen = dwMaxValueName + 1 ;
            lRet =  RegEnumValue(
                        hKey_p,
                        i,                  // index
                        pszValueName,       // address of buffer for value name
                        &dwValueNameLen,    // length of value name string
                        0,                  // reserved
                        &RegVal.m_dwType,   // address of buffer for type
                        RegVal.m_pbyteData, // address of data buffer
                        &RegVal.m_dwDataSize// address for size of data buffer
                    ) ;

            if( lRet == ERROR_SUCCESS ) {
                if( OnValueHit( pszSubKey_p, pszValueName, RegVal, usDepth ) == FALSE ) {
                    // User wants to abort ...
                    RegCloseKey( hKey_p ) ;
                    delete [] pszValueName ;
                    return FALSE ;
                }
            } else if( lRet == ERROR_NO_MORE_ITEMS ) {
                // end of enumeration reached ...
                break ;
            } else {
            }

            // Need to reset the data size, because it was set to the size
            // of the current value, so later values with a bigger size can't be
            // loaded. Thanks to Pieter E. Roos, who founds this bug.
            RegVal.m_dwDataSize = dwMaxValueData;
        }
        delete [] pszValueName ;
    }

    // enumerate the subkeys and call RegTreeWalk() recursivly. if such a call
    // fails we have to break the enumeration (i.e. the user's function wants so)
    LPTSTR pszKeyName = new TCHAR [ dwMaxSubKey + 1 ] ;
    DWORD dwKeyNameLen = dwMaxSubKey ;
    for( register DWORD i = 0 ; /*i < dwSubKeyCnt*/ ; ++i ) {
        lRet =  RegEnumKey(
                    hKey_p,
                    i,              // index
                    pszKeyName,     // address of buffer for key name string
                    dwKeyNameLen+1  // max. length of key name string
                ) ;

        if( lRet == ERROR_SUCCESS ) {
            // first call notification handler ...
            if( uFlags_p & RTW_NotifyKey ) {
                if( ! OnKeyHit( pszKeyName, usDepth ) ) {
                    // user function wants to abort ...
                    delete [] pszKeyName ;
                    return FALSE ;
                }
            }

            HKEY hNewKey ;
            lRet =  RegOpenKeyEx(
                        hKey_p,
                        pszKeyName,     // path name of child key
                        0,              // reserved
                        KEY_READ,       // requesting read access
                        &hNewKey        // address of key to be returned
                    ) ;
            if( lRet == ERROR_SUCCESS ) {
                LPTSTR pszPath = new TCHAR [_tcslen(pszSubKey_p)+_tcslen(pszKeyName)+2];
                _tcscpy(pszPath, pszSubKey_p);
                _tcscat(pszPath, I_("\\"));
                _tcscat(pszPath, pszKeyName);

                if( RegTreeWalk( pszPath, hNewKey, uFlags_p, usDepth+1 ) == FALSE ) {
                    // user wants to abort ...
                    RegCloseKey( hKey_p ) ;
                    delete [] pszKeyName;
                    delete [] pszPath;
                    return FALSE ;
                }
                delete [] pszPath;
            } else {
            }
        } else if( lRet == ERROR_NO_MORE_ITEMS ) {
            break;
        } else {
        }
    }
    delete [] pszKeyName ;

    RegCloseKey( hKey_p ) ;

    return TRUE ;
}

#endif  // _REG_NO_TREEWALK

/////////////////////////////////////////////////////////////////////////////
// class CRegistry  --  static members ...
BOOL CRegistry ::   LoadKey(
                        LPCTSTR pszSubKey_p,
                        LPCTSTR pszValueName_p,
                        CRegVal & rData_p,
                        HKEY hKey_p
                    ) {
    HKEY hSubKey ;
    LONG lRet =     RegOpenKeyEx(
                        hKey_p,         // key handle at root level
                        pszSubKey_p,    // path name of child key
                        0,              // reserved
                        KEY_READ,       // requesting read access
                        &hSubKey        // address of key to be returned
                    ) ;
    
    if( lRet != ERROR_SUCCESS ) {
        return FALSE ;
    }

    DWORD dwMaxValueData ;
    DWORD dwType ;

    lRet =  RegQueryValueEx(
                    hSubKey,            // handle of key to query 
                    pszValueName_p,     // address of name of value to query 
                    0,                  // reserved 
                    &dwType,            // address of buffer for value type 
                    0,                  // address of data buffer 
                    &dwMaxValueData     // address of data buffer size 
            );

    if( lRet != ERROR_SUCCESS ) {
        RegCloseKey( hSubKey ) ;
        return FALSE ;
    }
    
    BYTE * pbyteData = rData_p.AllocateDataBuffer( dwMaxValueData ) ;
    
    lRet =  RegQueryValueEx(
                    hSubKey,            // handle of key to query 
                    pszValueName_p,     // address of name of value to query 
                    0,                  // reserved 
                    &dwType,            // address of buffer for value type 
                    pbyteData,          // address of data buffer 
                    &dwMaxValueData     // address of data buffer size 
            );

    if( lRet != ERROR_SUCCESS ) {
        RegCloseKey( hSubKey ) ;
        RegCloseKey( hKey_p ) ;
        rData_p.FreeDataBuffer() ;
        return FALSE ;
    }

    rData_p.SetType( dwType ) ;

    RegCloseKey( hSubKey ) ;
    RegCloseKey( hKey_p ) ;

    return TRUE ;
}


BOOL CRegistry ::   SaveKey(
                        LPCTSTR pszSubKey_p,
                        LPCTSTR pszValueName_p,
                        const CRegVal & rData_p,
                        HKEY hKey_p
                    ) {
    HKEY hSubKey ;
    DWORD dwDisposition ;

    LONG lRet = RegCreateKeyEx(
                    hKey_p,                 // handle of an open key 
                    pszSubKey_p,            // address of subkey name 
                    0,                      // reserved 
                    0,                      // address of class string 
                    REG_OPTION_NON_VOLATILE,// special options flag 
                    KEY_WRITE,              // desired security access 
                    0,                      // address of key security structure 
                    & hSubKey,              // address of buffer for opened handle  
                    & dwDisposition         // address of disposition value buffer 
                ) ;

    if( lRet != ERROR_SUCCESS ) {
        return FALSE ;
    }
    
    lRet =  RegSetValueEx(
                hSubKey,                // handle of key to set value for
                pszValueName_p,         // address of value to set
                0,                      // reserved
                rData_p.m_dwType,       // flag for value type
                rData_p.m_pbyteData,    // address of value data
                rData_p.m_dwDataSize    // size of value data
            ) ;


    RegCloseKey( hSubKey ) ;
    RegCloseKey( hKey_p ) ;

    if( lRet != ERROR_SUCCESS ) {
        return FALSE ;
    }

    return TRUE ;
}


BOOL CRegistry ::   DeleteKey(
                        LPCTSTR pszSubKey_p,
                        LPCTSTR pszValueName_p,
                        HKEY hKey_p
                    ) {
    HKEY hSubKey ;
    LONG lRet =     RegOpenKeyEx(
                        hKey_p,         // key handle at root level
                        pszSubKey_p,    // path name of child key
                        0,              // reserved
                        KEY_WRITE | KEY_READ,   // requesting access
                        &hSubKey        // address of key to be returned
                    ) ;
    
    if( lRet != ERROR_SUCCESS ) {
        return FALSE ;
    }

    if( pszValueName_p ) {
        // delete the given value only.
        lRet = RegDeleteValue( hSubKey, pszValueName_p ) ;
        RegCloseKey( hSubKey ) ;
        RegCloseKey( hKey_p ) ;
        if( lRet != ERROR_SUCCESS ) {
            return FALSE ;
        }
    } else {
        // delete the entire key. NOTE: Windows NT cannot delete
        // subkeys of the key, so we have to handle it ourself, so
        // the code will work on both: NT and 95.

        DWORD dwSubKeyCnt = 0 ;
        do {    // loop until all subkeys are removed ...
                // Do not use the number of subkeys for the enumeration
                // (as in the RegistryTreeWalk() function),
                // because it changes, if a subkey is deleted !!!

            // first get an info about this subkey ...
            DWORD dwMaxSubKey ;
            LONG lRet = RegQueryInfoKey(
                            hSubKey,
                            0,                  // buffer for class name
                            0,                  // length of class name string
                            0,                  // reserved
                            &dwSubKeyCnt,       // # of subkeys
                            &dwMaxSubKey,       // length of longest subkey
                            0,                  // length of longest class name string
                            0,                  // # of values
                            0,                  // length of longest value name
                            0,                  // length of longest value data
                            0,                  // security descriptor
                            0                   // last write time
                        ) ;
            if( lRet != ERROR_SUCCESS ) {
                RegCloseKey( hSubKey ) ;
                return FALSE ;
            }

            if( dwSubKeyCnt > 0 ) {
                // retrieve the first subkey and call DeleteKey() recursivly.
                // if such a call fails we have to break the deletion !
                // NOTE: that the initially key may stay "half removed" ...
                LPTSTR pszKeyName = new TCHAR [ dwMaxSubKey + 1 ] ;
                DWORD dwKeyNameLen = dwMaxSubKey ;
                lRet =  RegEnumKey(
                            hSubKey,
                            0,              // index
                            pszKeyName,     // address of buffer for key name string
                            dwKeyNameLen+1  // max. length of key name string
                        ) ;

                if( lRet != ERROR_SUCCESS ) {
                    delete [] pszKeyName ;
                    RegCloseKey( hSubKey ) ;
                    return FALSE ;
                }
                if( ! DeleteKey( pszKeyName, pszValueName_p, hSubKey ) ) {
                    delete [] pszKeyName ;
                    RegCloseKey( hSubKey ) ;
                    return FALSE ;
                }
                delete [] pszKeyName ;
            }
        } while( dwSubKeyCnt > 0 ) ;
        
        RegCloseKey( hSubKey ) ;

        lRet = RegDeleteKey( hKey_p, pszSubKey_p ) ;
        //RegCloseKey( hKey_p ) ;

        if( lRet != ERROR_SUCCESS ) {
            return FALSE ;
        }
    }

    return TRUE ;
}


BOOL CRegistry ::   HasEntries(
                        LPCTSTR pszSubKey_p,
                        DWORD * pdwSubKeyCnt_p,
                        DWORD * pdwValueCnt_p,
                        HKEY hKey_p
                    ) {
    if( pdwSubKeyCnt_p ) * pdwSubKeyCnt_p = 0 ;
    if( pdwValueCnt_p ) * pdwValueCnt_p = 0 ;

    HKEY hSubKey ;
    LONG lRet =     RegOpenKeyEx(
                        hKey_p,         // key handle at root level
                        pszSubKey_p,    // path name of child key
                        0,              // reserved
                        KEY_READ,       // requesting read access
                        &hSubKey        // address of key to be returned
                    ) ;
    
    if( lRet != ERROR_SUCCESS ) {
        return FALSE ;
    }
    
    DWORD dwSubKeyCnt ;
    DWORD dwValueCnt ;
    lRet =  RegQueryInfoKey(
                hSubKey,
                0,                  // buffer for class name
                0,                  // length of class name string
                0,                  // reserved
                &dwSubKeyCnt,       // # of subkeys
                0,                  // length of longest subkey
                0,                  // length of longest class name string
                &dwValueCnt,        // # of values
                0,                  // length of longest value name
                0,                  // length of longest value data
                0,                  // security descriptor
                0                   // last write time
            ) ;
    
    RegCloseKey( hSubKey ) ;
    
    if( lRet != ERROR_SUCCESS ) {
        return FALSE ;
    }

    if( pdwSubKeyCnt_p )
        * pdwSubKeyCnt_p = dwSubKeyCnt ;

    if( pdwValueCnt_p )
        * pdwValueCnt_p = dwValueCnt ;

    return (dwSubKeyCnt > 0 || dwValueCnt > 0) ? TRUE : FALSE ;
}





/////////////////////////////////////////////////////////////////////////////
// class CRegVal    --  construction / destruction ...

CRegVal :: CRegVal()
    : m_hHeap( HeapCreate( 0, 0, 0) )
    , m_pbyteData( 0 )
    , m_dwDataSize( 0 )
    , m_dwType( REG_NONE ) {
}


CRegVal :: CRegVal( DWORD dwInitial_p )
    : m_hHeap( HeapCreate( 0, 0, 0) )
    , m_pbyteData( 0 )
    , m_dwDataSize( 0 )
    , m_dwType( REG_NONE ) {
    SetValue( dwInitial_p ) ;
}


CRegVal :: CRegVal( LPCTSTR pszInitial_p )
    : m_hHeap( HeapCreate( 0, 0, 0) )
    , m_pbyteData( 0 )
    , m_dwDataSize( 0 )
    , m_dwType( REG_NONE ) {
    SetValue( pszInitial_p ) ;
}


CRegVal :: CRegVal( const LPBYTE pbyteInitial_p, DWORD dwSize_p )
    : m_hHeap( HeapCreate( 0, 0, 0) )
    , m_pbyteData( 0 )
    , m_dwDataSize( 0 )
    , m_dwType( REG_NONE ) {
    SetValue( pbyteInitial_p, dwSize_p ) ;
}


CRegVal :: ~CRegVal() {
    if( m_pbyteData )
        HeapFree( m_hHeap, 0, m_pbyteData ) ;
    HeapDestroy( m_hHeap ) ;
}


/////////////////////////////////////////////////////////////////////////////
// class CRegVal    --  public members ...


void CRegVal :: SetType( DWORD dwType_p ) { m_dwType = dwType_p ; }
DWORD CRegVal :: GetType() const { return m_dwType ; }
DWORD CRegVal :: GetSize() const { return m_dwDataSize ; }


BOOL CRegVal :: GetValue( DWORD & rNum_p ) const {
    if( m_dwType != REG_DWORD
        && m_dwType != REG_DWORD_LITTLE_ENDIAN
        && m_dwType != REG_DWORD_BIG_ENDIAN ) {
        return FALSE ;
    }
    
    rNum_p = *((DWORD *) m_pbyteData) ;

    return TRUE ;
}


BOOL CRegVal :: GetValue( LPCTSTR & rpString_p ) const {
    if( m_dwType != REG_SZ
        && m_dwType != REG_EXPAND_SZ
        && m_dwType != REG_LINK
        && m_dwType != REG_MULTI_SZ ) {
        return FALSE ;
    }
    
    rpString_p = LPCTSTR(m_pbyteData);

    return TRUE ;
}


BOOL CRegVal :: GetValue( LPBYTE & rpbyteBuffer_p, DWORD dwBufferSize_p ) const {
    if( (m_dwType != REG_BINARY
        && m_dwType != REG_RESOURCE_LIST
        && m_dwType != REG_FULL_RESOURCE_DESCRIPTOR)
        || dwBufferSize_p != m_dwDataSize ) {
        return FALSE ;
    }
    
    for( register DWORD i = 0 ; i < m_dwDataSize ; ++i )
        rpbyteBuffer_p[i] = m_pbyteData[i] ;

    return TRUE ;
}


CRegVal& CRegVal :: SetValue( DWORD dwValue_p ) {
    AllocateDataBuffer( sizeof( dwValue_p ) ) ;
    m_dwType = REG_DWORD ;
    *((DWORD *)m_pbyteData) = dwValue_p ;
    return(*this);
}


CRegVal& CRegVal :: SetValue( LPCTSTR pszValue_p, BOOL bExpanded_p ) {
    const DWORD dwSize = pszValue_p ? ((_tcslen(pszValue_p) + 1) * sizeof(I_CHAR)) : 0 ;
    AllocateDataBuffer( dwSize + sizeof(I_CHAR) ) ;
    m_dwType = bExpanded_p ? REG_EXPAND_SZ : REG_SZ ;
    if( pszValue_p )
        ::CopyMemory(PVOID(m_pbyteData), pszValue_p, dwSize);
    return(*this);
}


CRegVal& CRegVal :: SetValue( LPCTSTR pszValue_p [], const DWORD nArray_p ) {
    // first step: calculate size ...
    register DWORD i ;
    DWORD nSize = 0 ;
    for( i = 0 ; i < nArray_p ; ++i )
        nSize += (_tcslen( pszValue_p[i] ) * sizeof(I_CHAR)) + sizeof(I_CHAR);
    nSize += sizeof(I_CHAR); // for the trailing '\0' !

    AllocateDataBuffer( nSize + (nArray_p ? 0 : sizeof(I_CHAR)) ) ;
    m_dwType = REG_MULTI_SZ ;

    register LPTSTR p = (LPTSTR)m_pbyteData;

    if( ! nArray_p )
        *p++ = I_('\0');

    // last step: copy the strings together
    for( i = 0 ; i < nArray_p ; ++i ) {
        register LPCTSTR c = pszValue_p[i] ;
        while( *p++ = *c++ );
    }
    *p = I_('\0');
    return(*this);
}

CRegVal& CRegVal :: SetValue( const LPBYTE pBuffer_p, const DWORD nSize_p ) {
    AllocateDataBuffer( nSize_p ) ;
    m_dwType = REG_BINARY ;
    CopyMemory(m_pbyteData, pBuffer_p, nSize_p);
    return(*this);
}



/////////////////////////////////////////////////////////////////////////////
// class CRegVal    --  private members (for use in friend classes only)

BYTE * CRegVal :: AllocateDataBuffer( DWORD dwSize_p ) {
    if( m_pbyteData )
        HeapFree( m_hHeap, 0, m_pbyteData ) ;
    m_pbyteData = (BYTE *) HeapAlloc( m_hHeap, 0, dwSize_p ) ;
    if( ! m_pbyteData ) {
    }
    m_dwDataSize = dwSize_p ;
    return m_pbyteData ;
}


void CRegVal :: FreeDataBuffer() {
    if( m_pbyteData )
        HeapFree( m_hHeap, 0, m_pbyteData ) ;
    m_pbyteData = 0 ;
    m_dwDataSize = 0 ;
}

#include <sstream>

DString CRegVal::asString() const {
   DString dstr;
   switch( GetType() ) {
      case REG_SZ:
         {
            LPCTSTR psz = NULL;
            GetValue(psz); 
            dstr = DString(psz);
         }
         break;
      case REG_DWORD:
      case REG_DWORD_BIG_ENDIAN:
         {
            DWORD dw;
            GetValue(dw);
            std::ostringstream oss;
            oss << dw;
            dstr = oss.str();
         }
      default:
         break;
   }
   return dstr;
}