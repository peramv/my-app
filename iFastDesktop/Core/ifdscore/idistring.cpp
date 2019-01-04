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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : idistring.cpp
// ^AUTHOR : Tom Hogan
// ^DATE   : 01/20/99
//
// ----------------------------------------------------------
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#define DICORE_DLL

#include "srcprag.h"
#ifndef IDISTRING_HPP
   #include "idistring.hpp"
#endif

#ifndef CONDITIONMANAGER_HPP
   #include "conditionmanager.hpp"
#endif
#ifndef DICORE_H
   #include "dicore.h"
#endif
#ifndef MATHSTRING_HPP
   #include "MathString.hpp"
#endif
#ifndef STRINGFUNCTIONS_HPP
   #include "StringFunctions.hpp"
#endif

#ifndef INCLUDED_CTYPE_H
#define INCLUDED_CTYPE_H
#include <ctype.h>
#endif
#ifndef INCLUDED_STDLIB_H
#define INCLUDED_STDLIB_H
#include <stdlib.h>
#endif

namespace
{
   const I_CHAR * IDI_EMPTY_MARK = I_( "(null)" );
}

I_CHAR * makeErrBufUsingGenericTagsBase( const I_CHAR ** stackPtr );
I_CHAR * makeErrBufUsingGenericTagsBase( const DString ** stackPtr );

DString & addIDITagValue(
                        DString & strInOut,
                        const I_CHAR * szTag,
                        const DString & strValue,
                        I_CHAR separator,
                        I_CHAR terminator
                        )
{
   strInOut += szTag;
   strInOut += separator;
   strInOut += strValue;
   strInOut += terminator;
   return(strInOut);
}

DString & addIDITagValue(
                        DString & strInOut,
                        const DString & szTag,
                        const DString & strValue,
                        I_CHAR separator,
                        I_CHAR terminator
                        )
{
   strInOut += szTag;
   strInOut += separator;
   strInOut += strValue;
   strInOut += terminator;
   return(strInOut);
}

DString & addIDITagValue(
                        DString &strInOut,
                        const DString & szTag,
                        const I_CHAR * strValue,
                        I_CHAR separator,
                        I_CHAR terminator
                        )
{
   strInOut += szTag;
   strInOut += separator;
   strInOut += strValue;
   strInOut += terminator;
   return(strInOut);
}

DString & addIDITagValue(
                        DString & strInOut,
                        const I_CHAR * szTag,
                        const I_CHAR * strValue,
                        I_CHAR separator,
                        I_CHAR terminator
                        )
{
   strInOut += szTag;
   strInOut += separator;
   strInOut += strValue;
   strInOut += terminator;
   return(strInOut);
}

DString & addIDITagValue(
                        DString & strInOut,
                        const I_CHAR * szTag,
                        int iValue,
                        I_CHAR separator,
                        I_CHAR terminator
                        )
{
   return(addIDITagValue( strInOut, 
                          szTag, 
                          asString( iValue ),
                          separator,
                          terminator ));
}

DString & addIDITagValue(
                        DString & strInOut,
                        const DString & szTag,
                        int iValue,
                        I_CHAR separator,
                        I_CHAR terminator
                        )
{
   return(addIDITagValue( strInOut, 
                          szTag, 
                          asString( iValue ),
                          separator,
                          terminator ));
}

DString & addIDITagValue(
                        DString & strInOut,
                        const I_CHAR * szTag,
                        long lValue,
                        I_CHAR separator,
                        I_CHAR terminator
                        )
{
   return(addIDITagValue( strInOut, 
                          szTag, 
                          asString( lValue ),
                          separator,
                          terminator ));
}

DString & addIDITagValue(
                        DString & strInOut,
                        const DString & szTag,
                        long lValue,
                        I_CHAR separator,
                        I_CHAR terminator
                        )
{
   return(addIDITagValue( strInOut, 
                          szTag, 
                          asString( lValue ),
                          separator,
                          terminator ));
}

DString & addIDITagValue(
                        DString & strInOut,
                        const I_CHAR * szTag,
                        const MathString & mstrValue,
                        I_CHAR separator,
                        I_CHAR terminator
                        )
{
   return(addIDITagValue( strInOut, 
                          szTag, 
                          mstrValue.c_str(),
                          separator,
                          terminator ));
}

DString & addIDITagValue(
                        DString & strInOut,
                        const DString & szTag,
                        const MathString & mstrValue,
                        I_CHAR separator,
                        I_CHAR terminator
                        )
{
   return(addIDITagValue( strInOut, 
                          szTag, 
                          mstrValue.c_str(),
                          separator,
                          terminator ));
}


// return pointer to next IDI string component
//        NULL if I_CHAR pointed at is NULL (end)

I_CHAR * parseIdiString( I_CHAR * idiString,
                         DString & tagName,
                         DString & value,
                         I_CHAR separator,
                         I_CHAR terminator )
{
   CMFrame cmFrame( I_( "DICORE" ),
                    I_( "I_CHAR * parseIdiString( const I_CHAR" )
                    I_( " * idiString, " )
                    I_( "DString & tagName, DString & value, " )
                    I_( "I_CHAR separator, " )
                    I_( "I_CHAR terminator )" ),
                    __FILE__, 
                    __LINE__,
                    g_conditionManager.getPath() );

   if( NULL == idiString )
      return(NULL);

   int length = i_strlen( idiString );
   int index = 0;
   I_CHAR * tp;
   I_CHAR * idi;

   value = I_( "" );

   // if 0 == length, return NULL
   if( 0 == length )
      return(NULL);

   // look for separator
   //   if none => error
   if( !( tp = i_strchr( idiString, separator ) ) )
   {
      //!!!
      ADDCONDITIONFROMFILE( DICORE_PARSE_IDI_MISSING_SEPARATOR );
      return(NULL);
   }
   // are we at the end?
   if( ( tp - idiString ) == length )
   {
      //!!!
      ADDCONDITIONFROMFILE( DICORE_PARSE_IDI_MISSING_TAG_NAME );
      return(NULL);
   }
   *tp = '\0';

   // move chars from idiString to tagName
   tagName = idiString;

   // restore the separator
   *tp = separator;

   // increment past separator
   idiString = ++tp;

   // look for terminator
   tp = i_strchr( idiString, terminator );

   // are we missing a required terminator?
   if( tp )
   {
      I_CHAR * tmp = i_strchr( idiString, separator );
      // did we hit a separator before a required terminator?
      if( tmp && tmp < tp )
      {
         idi = makeErrBuf( I_( "TAG_NAME" ), tagName );

         ADDCONDITIONFROMFILEIDI( DICORE_PARSE_IDI_MISSING_TERMINATOR,
                                  idi );

         delete [] idi;
         return(NULL);
      }

      *tp = '\0';
   }
   else
   {
      I_CHAR * tmp = i_strchr( idiString, separator );
      // did we hit a separator before a required terminator?
      if( tmp )
      {
         idi = makeErrBuf( I_( "TAG_NAME" ), tagName );

         ADDCONDITIONFROMFILEIDI( DICORE_PARSE_IDI_MISSING_TERMINATOR,
                                  idi );

         delete [] idi;
         return(NULL);
      }
   }

   // move chars from idiString to value
   if( 0 == i_strlen( idiString ) )
   {
      value = IDI_EMPTY_MARK;
   }
   else
   {
      value = idiString;
   }

   if( tp )
   {
      // restore the terminator
      *tp = terminator;
      ++tp;
   }
   return(tp);
}


I_CHAR * makeErrBufUsingGenericTags( const DString * strErr, ... )
{
   return(makeErrBufUsingGenericTagsBase( &strErr ));
}


I_CHAR * makeErrBufUsingGenericTags( const I_CHAR * strErr, ... )
{
   return(makeErrBufUsingGenericTagsBase( &strErr ));
}


I_CHAR * makeErrBufUsingGenericTagsBase( const I_CHAR ** stackPtr )
{
   // Start with VAR1
   int counter = 1, totalLength = 0;
   const DString genericTagName = I_( "VAR" );
   DString ErrBuf;
   I_CHAR buf[ 17 ];

   for( ;
      ( *stackPtr != NULL ) && ( counter < 256 );
      ++counter, ++stackPtr )
   {
      // add the tag-value pair

      ErrBuf += genericTagName;
      i_itot( counter, buf, 10 );
      ErrBuf += buf;
      ErrBuf += _IDI_EQUAL;
      ErrBuf += *stackPtr;
      ErrBuf += _IDI_BREAK;
   }

   // allocate the buffer which will contain the error Idi string

   I_CHAR * idiErrString = new I_CHAR[ ErrBuf.length() + 1 ];
   i_strcpy( idiErrString, ErrBuf.c_str() );

   return(idiErrString);
}


I_CHAR * makeErrBufUsingGenericTagsBase( const DString ** stackPtr )
{
   // Start with VAR1
   int counter = 1, totalLength = 0;
   const DString genericTagName = I_( "VAR" );
   DString ErrBuf;
   I_CHAR buf[ 17 ];

   for( ;
      ( *stackPtr != NULL ) && ( counter < 256 );
      ++counter, ++stackPtr )
   {
      // add the tag-value pair

      ErrBuf += genericTagName;
      i_itot( counter, buf, 10 );
      ErrBuf += buf;
      ErrBuf += _IDI_EQUAL;
      ErrBuf += **stackPtr;
      ErrBuf += _IDI_BREAK;
   }

   // allocate the buffer which will contain the error Idi string

   I_CHAR * idiErrString = new I_CHAR[ ErrBuf.length() + 1 ];
   i_strcpy( idiErrString, ErrBuf.c_str() );

   return(idiErrString);
}


bool getIdiValue( const DString & idiString,
                  const DString & tagString,
                  DString & returnValue,
                  I_CHAR separator,
                  I_CHAR terminator )
{
   bool retVal = false;
   DString tmpTagName;
   DString tmpValue;
   I_CHAR * buf = new I_CHAR[ idiString.size() + 1 ];
   idiString.copy( buf, idiString.size() );
   buf[ idiString.size() ] = '\0';
   I_CHAR * tp = buf;

   while( tp = parseIdiString( tp,
                               tmpTagName,
                               tmpValue,
                               separator,
                               terminator ) )
   {
      if( tmpTagName == tagString )
      {
         retVal = true;
         returnValue = tmpValue;
         break;
      }
   }

   delete buf;
   return(retVal);
}



bool doesIdiTagExist( const DString & idiString, 
                      const DString & tagString, 
                      I_CHAR separator,
                      I_CHAR terminator )
{
   DString tmpValue;

   return(getIdiValue( idiString,
                       tagString,
                       tmpValue,
                       separator,
                       terminator ));
}


bool idiValueWasReplaced( DString & idiString, 
                          const DString & tagString, 
                          const DString & value,
                          I_CHAR separator,
                          I_CHAR terminator )
{
   bool retVal = false;
   DString tmpTagName;
   DString tmpValue;
   DString newIdiString;
   I_CHAR * buf = new I_CHAR[ idiString.size() + 1 ];
   I_CHAR * start = buf, * save_tp;
   idiString.copy( buf, idiString.size() );
   buf[ idiString.size() ] = '\0';
   I_CHAR * tp = buf;

   while( tp = parseIdiString( save_tp = tp,
                               tmpTagName,
                               tmpValue,
                               separator,
                               terminator ) )
   {
      if( tmpTagName == tagString )
      {  // we found the tag, so slice out the old tag/value
         // pair
         newIdiString.assign( idiString.c_str(), 
                              ( save_tp - start ) );
         newIdiString += tagString;
         newIdiString += separator;
         newIdiString += value;
         newIdiString += terminator;
         newIdiString += tp;
         idiString = newIdiString;

         retVal = true;
         break;
      }
   }
   delete buf;
   return(retVal);
}


bool setIdiValue( DString & idiString, 
                  const DString & tagString, 
                  const DString & value,
                  bool appendNew,
                  I_CHAR separator,
                  I_CHAR terminator )
{
   bool retVal = false;

   retVal = idiValueWasReplaced( idiString,
                                 tagString,
                                 value,
                                 separator,
                                 terminator );

   if( ( false == retVal )
       && appendNew )
   {
      addIDITagValue( idiString,
                      tagString,
                      value,
                      separator,
                      terminator );
      retVal = true;
   }

   return(retVal);
}


bool removeIdiTag( DString & idiStringInOut,
                   const DString & tagString,
                   I_CHAR separator,
                   I_CHAR terminator )
{
   bool retVal = false;
   DString tmpTagName;
   DString tmpValue;
   DString newIdiString;
   I_CHAR * buf = new I_CHAR[ idiStringInOut.size() + 1 ];
   I_CHAR * start = buf, * save_tp;
   idiStringInOut.copy( buf, idiStringInOut.size() );
   buf[ idiStringInOut.size() ] = '\0';
   I_CHAR * tp = buf;

   while( tp = parseIdiString( save_tp = tp,
                               tmpTagName,
                               tmpValue,
                               separator,
                               terminator ) )
   {
      if( tmpTagName == tagString )
      {  // we found the tag, so slice out the old tag/value
         // pair
         newIdiString.assign( idiStringInOut.c_str(), 
                              ( save_tp - start ) );
         newIdiString += tp;
         idiStringInOut = newIdiString;

         // we have to be sure to add the new value to the end
         retVal = true;
         break;
      }
   }
   delete buf;
   return(retVal);
}


//************************************************************************
//              Revision Control Entries
//************************************************************************
//
// $Log:   //db3n5j11/d/scc/ifds/core/archives/ifdscore/idistring.cpp-arc  $
// 
//    Rev 1.1   Oct 09 2002 17:42:04   PURDYECH
// New PVCS Database
// 
//    Rev 1.0   Jul 05 2002 10:14:16   SMITHDAV
// Initial revision.
// 
//    Rev 1.10   19 Sep 2000 10:58:08   DT14177
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
//    Rev 1.9   14 Apr 2000 08:35:48   dt20842
// Changed from strlen to i_strlen
// 
//    Rev 1.8   13 Apr 2000 09:26:56   dt20842
// Mark empty values with (null)
// 
//    Rev 1.7   11 Apr 2000 19:23:12   dt20842
// parseIdi will not crash on passed in NULL idiString
// 
//    Rev 1.6   19 Jan 2000 05:25:18   dt20842
// Change to start generic tags at VAR1 and not VAR0
// 
//    Rev 1.5   Dec 29 1999 11:23:42   DT14177
// Added const DString parameter overload to generic tag function; made I_CHAR parameter a const for same
// 
//    Rev 1.4   Dec 20 1999 10:12:02   DT14177
// Made idistring changes for backward compatibility
// 

