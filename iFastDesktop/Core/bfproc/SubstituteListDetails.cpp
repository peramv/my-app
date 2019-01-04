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
// ^FILE   : SubstituteListDetails.cpp
// ^AUTHOR : Jerry Leenerts
// ^DATE   : 05/25/1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : SubstituteListDetails
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "bpglobal.h"
#include "substitutelistdetails.hpp"
#include "abstractprocess.hpp"
#include <idistring.hpp>
#include <bfdata\bffieldid.hpp>
#include <bfutil\clientlocalecontext.hpp>
#include <bfproc\bfcontainerid.hpp>

#include <assert.h>

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "SubstituteListDetails" );

   const I_CHAR * const GETCURRENTKEY = I_( "getCurrentKey" );
   const I_CHAR * const GETFIRSTKEY = I_( "getFirstKey" );
   const I_CHAR * const GETFIELD = I_( "getField" );
   const I_CHAR * const GETNEXTKEY = I_( "getNextKey" );
   const I_CHAR * const SETFIELD1 = I_( "setField" );

   // Literals
   const I_CHAR * const ID = I_( "ID" );
}

namespace CND
{  // Conditions used
   extern const long BP_ERR_ID_OUT_OF_RANGE;
   extern const long BP_ERR_INVALID_METHOD_CALL;
   extern const long BP_ERR_ITEM_NOT_VALID;
   extern const long BP_ERR_LIST_NOT_VALID;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

SubstituteListDetails::SubstituteListDetails( AbstractProcess*,
                                              const BFFieldId &idField, 
                                              const DString &name ) 
: AbstractListDetails( BFContainerId( idField.getId() ), BF::NullContainerId, true, false, name )
, _bItemValid( false )
, _currentIndex( -1 )
{  
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   _Substitute_Code = BFFieldId::getId( I_( "Substitute_Code" ) );
   _Substitute_Description = BFFieldId::getId( I_( "Substitute_Description" ) );
}

//******************************************************************************

SubstituteListDetails::~SubstituteListDetails()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   clear();
}

//******************************************************************************

void *SubstituteListDetails::getContainer()
{
   // Not valid - no pointer to get
   assert( 0 );
   return(NULL);
}

//******************************************************************************

const DString &SubstituteListDetails::getCurrentKey( const BFDataGroupId& idDataGroup )
{
   checkSubstitutes();
   return(*_rpStrCurrentKey);
}

//******************************************************************************

void SubstituteListDetails::getField( const BFFieldId &idField, 
                                      bool bFormatted,
                                      DString &strValueOut,
                                      const BFDataGroupId& idDataGroup )
{
   checkSubstitutes();

   if( idField == _Substitute_Code )
   {
      strValueOut = _substitutes[ _currentIndex ]->code;
   }
   else if( idField == _Substitute_Description )
   {
      strValueOut = _substitutes[ _currentIndex ]->description;
   }
   else
   {  // Invalid field
      assert( 0 );
      DString strIDI;
      addIDITagValue( strIDI, ID, idField.getId() );
      // Could get name for field (if exists) and add to condition
//      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, GETFIELD,
//         CND::BP_ERR_LIST_NOT_VALID, strIDI );
   }
}

//******************************************************************************

bool SubstituteListDetails::getFirstKey( const DString **rpStr,
                                         const BFDataGroupId& idDataGroup )
{
   *rpStr = setCurrentIndex( 0 );
   return(false);        // At this time we don't care about change return
}

//******************************************************************************

void *SubstituteListDetails::getItem( const BFDataGroupId& idDataGroup )
{
   // Not valid - no pointer to get
   assert( 0 );
   return(NULL);
}

//******************************************************************************

bool SubstituteListDetails::getNextKey( const DString **rpStr,
                                        const BFDataGroupId& idDataGroup )
{
   *rpStr = setCurrentIndex( _currentIndex + 1 );
   return(false);        // At this time we don't care about change return
}

//******************************************************************************

int SubstituteListDetails::getNumberOfItemsInList( const BFDataGroupId& idDataGroup )
{
   checkSubstitutes();
   return(_substitutes.size());
}

//******************************************************************************

bool SubstituteListDetails::loadSubstitutes( )
{
   bool bRtn = false;
   DString strValues;
   int idx;
   DString strEmpty;

   const BFDataFieldProperties* pProps = BFDataFieldProperties::get( BFFieldId( getContainerID().getId() ) );
   clear();
   if( NULL != pProps )
   {  // Found field
      if( pProps->getAllSubstituteValues( strValues, ClientLocaleContext::get(), true ) )
      {  // Got substitutes
         while( ( idx = strValues.find_first_of( I_( "=" ) ) )
                != DString::npos )
         {  // While more values to get
            ITEM *pItem = new ITEM;
            pItem->code = strValues.substr( 0, idx );
            strValues.erase( 0, idx + 1);   // Skip to description
            if( ( idx = strValues.find_first_of( I_( ";" ) ) )
                == DString::npos )
            {  // Couldn't find end of string
               // Trace message here ?
               break;
            }
            pItem->description = strValues.substr( 0, idx );
            strValues.erase( 0, idx + 1 );
            _substitutes.push_back( pItem );
         }
         bRtn = true;
      }
   }
   return(bRtn);
}

//******************************************************************************

bool SubstituteListDetails::setCurrentKey( const DString &strKey,
                                           const BFDataGroupId& idDataGroup )
{
   int idx = findIndexByKey( strKey );
   if( ( *setCurrentIndex( idx ) ) == NULL_STRING )
   {  // Could not set key
      assert( 0 );
   }
   return(false);        // At this time we don't care about change return
}

//******************************************************************************

bool SubstituteListDetails::trySetCurrentKey( const DString &strKey,
                                              const BFDataGroupId& idDataGroup )
{
   return(setCurrentKey( strKey, idDataGroup ));
}

//******************************************************************************

SEVERITY SubstituteListDetails::setField( const BFFieldId &idField,
                                          bool bFormatted,
                                          const DString &strValue,
                                          const BFDataGroupId& idDataGroup )
{  // We fail because this is a read-only class
   assert( 0 );   
   THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, SETFIELD1,
                   CND::BP_ERR_INVALID_METHOD_CALL );
}

//******************************************************************************
//              Private Methods
//******************************************************************************

void SubstituteListDetails::checkSubstitutes( const BFDataGroupId& idDataGroup )
{
   if( !_bItemValid )
   {  // Try to load substitutes
      if( loadSubstitutes() )
      {
         const DString *strTmp = NULL;
         _bItemValid = true;
         getFirstKey( &strTmp, idDataGroup );
      }
      else
      {
         assert( 0 );
         // throw condition here
      }
   }
}

//******************************************************************************

void SubstituteListDetails::clear()
{
   for( int i = 0; i < _substitutes.size(); i++ )
   {
      delete _substitutes[i];
      _substitutes[i] = NULL;
   }
   _substitutes.clear();
   _bItemValid = false;
   _currentIndex = -1;
}

//******************************************************************************

int SubstituteListDetails::findIndexByKey( const DString &strKey,
                                           const BFDataGroupId& idDataGroup )
{
   // Note that we are not optimized for this search.  This is based on 
   // assumption that this will not happen often, or the lists will be small to 
   // traverse anyway.
   int count = getNumberOfItemsInList( idDataGroup );
   int i;

   for( i = 0; i < count; i++ )
   {
      if( _substitutes[i]->code == strKey )
      {
         return(i);
      }
   }
   // Didn't find
   return(-1);
}

//******************************************************************************

const DString *SubstituteListDetails::setCurrentIndex( int idx, 
                                                       const BFDataGroupId& idDataGroup )
{
   checkSubstitutes();
   if( idx < 0 || idx >= getNumberOfItemsInList( idDataGroup ) )
   {
      _currentIndex = -1;
      _rpStrCurrentKey = &_strEmpty;
   }
   else
   {
      _currentIndex = idx;
      _rpStrCurrentKey = &_substitutes[idx]->code;
   }
   return(_rpStrCurrentKey);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfproc/SubstituteListDetails.cpp-arc  $
 * 
 *    Rev 1.15   Jan 06 2003 16:44:14   PURDYECH
 * BFDataGroupId and BFContainerId changeover
 * 
 *    Rev 1.14   Nov 27 2002 15:04:52   PURDYECH
 * Documentation Changes
 * 
 *    Rev 1.13   Oct 09 2002 17:41:00   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.12   Sep 03 2002 11:07:14   PURDYECH
 * Further BFFieldId fixes
 * 
 *    Rev 1.11   Aug 29 2002 14:05:24   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.10   Aug 29 2002 12:51:12   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.9   05 Jun 2002 13:55:16   SMITHDAV
 * Fix grid refresh bug. Added trySetCurrentKey functions.
 * 
 *    Rev 1.8   May 28 2002 12:16:14   PURDYECH
 * BFData Implementation - Phase II
 * 
 *    Rev 1.7   May 08 2001 11:13:06   FENGYONG
 * Add name for API
 * 
 *    Rev 1.6   03 May 2001 14:03:14   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.5   Nov 08 2000 19:59:04   DT24433
 * added list name support
 * 
 *    Rev 1.4   Aug 15 2000 14:01:04   YINGZ
 * multi locale support
 * 
 *    Rev 1.3   Aug 02 2000 15:31:34   BUZILA
 * "locale" changes
 * 
 *    Rev 1.2   Jun 13 2000 17:53:00   DT24433
 * new Infra interfaces use ClientLocale
 * 
 *    Rev 1.1   Mar 08 2000 11:34:42   DT24433
 * removed dependency on ddinclude file
 * 
 *    Rev 1.0   Feb 15 2000 10:57:36   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.10   Oct 28 1999 13:48:24   VASILEAD
 * add/delete/reset & group processing
 * 
 *    Rev 1.9   Sep 14 1999 11:07:48   YINGZ
 * prevent sorting code when load list
 * 
 *    Rev 1.8   Aug 11 1999 14:01:36   DT24433
 * key string returned is now unique
 * 
 *    Rev 1.7   Aug 11 1999 10:56:06   DT24433
 * changed key from index to host code
 * 
 *    Rev 1.6   Aug 06 1999 10:19:46   DT24433
 * support change item detection
 * 
 *    Rev 1.5   Aug 03 1999 14:53:20   DT24433
 * container changes
 * 
 *    Rev 1.4   Jul 28 1999 18:03:36   VASILEAD
 * Fixed enUS to USen for locale
 * 
 *    Rev 1.3   Jul 21 1999 11:11:14   VASILEAD
 * Fix by Jerry
 * 
 *    Rev 1.2   Jul 20 1999 11:14:14   VASILEAD
 * New conditions update
 * 
 *    Rev 1.1   Jul 08 1999 10:02:12   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
