#ifndef IDISTRING_HPP
#define IDISTRING_HPP

#  pragma message( "including "__FILE__ )

/*
 * COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1999-2000 by DST Systems, Inc.
 */

/** @pkg DICORE */

/**
 * This file contains function prototypes
 */


#ifndef COMMONPORT_H
#include "commonport.h"
#endif

#ifndef DSTRING_HPP
#include "DString.hpp"
#endif

// Forward reference
class MathString;

#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif


#define _IDI_BREAK ';'
#define _IDI_EQUAL '='


DICORE_LINKAGE DString & addIDITagValue(
   DString & strInOut,
   const DString & szTag,
   const I_CHAR * strValue,
   I_CHAR separator = _IDI_EQUAL,
   I_CHAR terminator = _IDI_BREAK
   );

DICORE_LINKAGE DString & addIDITagValue(
   DString & strInOut,
   const I_CHAR * szTag,
   const DString & strValue,
   I_CHAR separator = _IDI_EQUAL,
   I_CHAR terminator = _IDI_BREAK
   );

DICORE_LINKAGE DString & addIDITagValue(
   DString & strInOut,
   const DString & szTag,
   const DString & strValue,
   I_CHAR separator = _IDI_EQUAL,
   I_CHAR terminator = _IDI_BREAK
   );

DICORE_LINKAGE DString & addIDITagValue(
   DString & strInOut,
   const I_CHAR * szTag,
   const I_CHAR * szValue,
   I_CHAR separator = _IDI_EQUAL,
   I_CHAR terminator = _IDI_BREAK
   );

DICORE_LINKAGE DString & addIDITagValue(
   DString & strInOut,
   const I_CHAR * szTag,
   int iValue,
   I_CHAR separator = _IDI_EQUAL,
   I_CHAR terminator = _IDI_BREAK
   );

DICORE_LINKAGE DString & addIDITagValue(
   DString & strInOut,
   const DString & szTag,
   int iValue,
   I_CHAR separator = _IDI_EQUAL,
   I_CHAR terminator = _IDI_BREAK
   );

DICORE_LINKAGE DString & addIDITagValue(
   DString & strInOut,
   const I_CHAR * szTag,
   long lValue,
   I_CHAR separator = _IDI_EQUAL,
   I_CHAR terminator = _IDI_BREAK
   );

DICORE_LINKAGE DString & addIDITagValue(
   DString & strInOut,
   const DString & szTag,
   long lValue,
   I_CHAR separator = _IDI_EQUAL,
   I_CHAR terminator = _IDI_BREAK
   );

DICORE_LINKAGE DString & addIDITagValue(
   DString & strInOut,
   const I_CHAR * szTag,
   const MathString & mstrValue,
   I_CHAR separator = _IDI_EQUAL,
   I_CHAR terminator = _IDI_BREAK
   );

DICORE_LINKAGE DString & addIDITagValue(
   DString & strInOut,
   const DString & szTag,
   const MathString & mstrValue,
   I_CHAR separator = _IDI_EQUAL,
   I_CHAR terminator = _IDI_BREAK
   );


// requester is responsible for deleting the returned error buffer

inline I_CHAR * makeErrBuf( I_CHAR * tagName, const DString & strErr )
{
   const DString genericTagName = tagName;
   I_CHAR * generic = new I_CHAR [ genericTagName.length() +
                                   1 +                         // separator
                                   strErr.length() +
                                   1 ];                      // NULL terminator
   i_strcpy( generic, genericTagName.c_str() );
   generic[ genericTagName.length() ] = '=';
   i_strcpy( generic + genericTagName.length() + 1, strErr.c_str() );
   generic[ genericTagName.length() + 1 + strErr.length() ] = '\0';
   return generic;
}

// makeErrBufUsingGenericTags() is used for backward compatibility
// It inserts VAR1=, 2=, ... into an allocated string buffer ahead of 
//   the value string parameters. The last pointer must be NULL and
//   there is a limit of 256 tag-value pairs

DICORE_LINKAGE I_CHAR * makeErrBufUsingGenericTags( 
                                                  const I_CHAR * strErr,
                                                    ... );

DICORE_LINKAGE I_CHAR * makeErrBufUsingGenericTags( 
                                                 const DString * strErr,
                                                    ... );

DICORE_LINKAGE DString makeDStringUsingGenericTags( 
                                                  const I_CHAR * strErr,
                                                    ... );

DICORE_LINKAGE I_CHAR * parseIdiString( I_CHAR * idiString,
                         DString & tagName,
                         DString & value,
                         I_CHAR separator = _IDI_EQUAL,
                         I_CHAR terminator = _IDI_BREAK );


// getValue() will return the Value corresponding to the Tag 
// passed in.

DICORE_LINKAGE bool getIdiValue( const DString & idiString, 
                                 const DString & tagString, 
                                 DString & returnValue,
                                 I_CHAR separator = _IDI_EQUAL,
                                 I_CHAR terminator = _IDI_BREAK );


// If a value corresponding to the Tag passed in already exists
// in the idi string, setValue() will replace it with value;
// otherwise it will append the new tag/value pair to the idi 
// string if appendnew is true.

DICORE_LINKAGE bool setIdiValue( DString & idiString, 
                                 const DString & tagString, 
                                 const DString & value,
                                 bool appendNew = false,
                                 I_CHAR separator = _IDI_EQUAL,
                                 I_CHAR terminator = _IDI_BREAK );


// doesTagExist() will parse the idi string, looking for whether
// the tag is part of the string.

DICORE_LINKAGE bool doesIdiTagExist( const DString & idiString, 
                                     const DString & tagString, 
                                     I_CHAR separator = _IDI_EQUAL,
                                     I_CHAR terminator = _IDI_BREAK );


// removeTag() will remove the associated tag/value pair from 
// the idiString.

DICORE_LINKAGE bool removeIdiTag( DString & idiStringInOut,
                                  const DString &tagString,
                                  I_CHAR separator = _IDI_EQUAL,
                                  I_CHAR terminator = _IDI_BREAK );


#endif

//************************************************************************
//              Revision Control Entries
//************************************************************************
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
//
// $Log:   Y:/VCS/iFastAWD/inc/idistring.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:31:36   kovacsro
//Initial revision.
// 
//    Rev 1.6   23 Aug 2001 17:41:08   dt14177
// added makeDStringUsingGenericTags()
// 
//    Rev 1.5   26 Oct 2000 12:02:32   dt14177
// cleanup
// 
//    Rev 1.4   19 Sep 2000 10:58:10   DT14177
// added enhancements: getIdiValue()
// setIdiValue(), removeIdiTag(), 
// and doesIdiTagExist() .  I also changed
// IDI_BREAK and IDI_EQUAL from const
// ints to macros (so they could be used as
// defaults to parameters and added 
// parameters to the addIDITagValue()
// functions so that the equal/break
// values could be changed.
// 
//    Rev 1.3   Dec 29 1999 11:23:44   DT14177
// Added const DString parameter overload to generic tag function; made I_CHAR parameter a const for same
// 
//    Rev 1.2   Dec 20 1999 10:12:14   DT14177
// Made idistring changes for backward compatibility
// 

