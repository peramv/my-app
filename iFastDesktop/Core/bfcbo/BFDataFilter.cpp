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
//    Copyright 2000 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : BFDataFilter.cpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : April 12, 2000
//
// ^CLASS  : BFDataFilter
//
//******************************************************************************
#include <bfutil\RTRevisionDefines.hpp>
RT_SOURCE_REVISION( "$Archive:   Y:/VCS/BF Core/bfcbo/BFDataFilter.cpp-arc  $", "$Revision:   1.10  $" )

#include <srcprag.h>
#include "bfdatafilter.hpp"
#include <bfdata\bffieldid.hpp>

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME  = I_( "BFDataFilter" );
   const I_CHAR  CHAR_EQUAL   = I_CHAR('=');
   const I_CHAR  CHAR_LESS    = I_CHAR('<');
   const I_CHAR  CHAR_GREATER = I_CHAR('>');
   const I_CHAR  CHAR_NOT     = I_CHAR('!');
   const I_CHAR  CHAR_FIND    = I_CHAR('~');
   const I_CHAR  CHAR_SC      = I_CHAR(';');
}

//CP20021126namespace CND
//CP20021126{
//CP20021126   extern const I_CHAR *BFBASE_CONDITION;
//CP20021126}

//***************************************************************************************************
void BFDataFilter::clearFilter( )
{
   DATAFILTERVECTOR::iterator iter = vect.begin();
   while( iter != vect.end() )
   {
      delete *iter;
      iter++;
   };
   vect.clear();
}

//***************************************************************************************************
bool BFDataFilter::addElement( const DString & lFilterElement)
{
   bool success = true;

   DString  dstString     = lFilterElement;
   OPCODES  operation     = OP_NONE;
   DString  dstFieldValue = NULL_STRING;
   DataFilterElement * pDataFilterElement = NULL;

   int iFiltLen = lFilterElement.length();
   int pos = 0;
   I_CHAR * posChar;
   while( pos < iFiltLen )
   {
      posChar = &dstString[pos];
      if( *posChar == CHAR_EQUAL   ||
          *posChar == CHAR_LESS    ||
          *posChar == CHAR_GREATER  ||
          *posChar == CHAR_FIND    ||
          *posChar == CHAR_NOT )
         break;
      pos++;
   }

   if( !(pos < iFiltLen && pos > 0) )
      return(false);

   BFFieldId fieldId( dstString.left( pos ).asInteger() );

   dstString = dstString.substr( pos );

   pos      = 0;
   posChar  = &dstString[pos];

   pos++;
   switch( *posChar )
   {
      case CHAR_LESS :
         if( dstString[ pos ] == CHAR_EQUAL )
         {
            operation = OP_LESS_OR_EQUAL;
            pos++;
         }
         else
            operation = OP_LESS;
         break;
      case CHAR_GREATER :
         if( dstString[ pos ] == CHAR_EQUAL )
         {
            operation = OP_GREATER_OR_EQUAL;
            pos++;
         }
         else
            operation = OP_GREATER;
         break;
      case CHAR_NOT :
         if( dstString[ pos ] == CHAR_EQUAL )
         {
            operation = OP_NOT_EQUAL;
            pos++;
         }
         else if( dstString[ pos ] == CHAR_FIND )
         {   // !~ - Not Find
            operation = OP_NOT_FIND;
            pos++;
         }
         break;
      case CHAR_EQUAL :
         operation = OP_EQUAL;
         break;
      case CHAR_FIND :
         operation = OP_FIND;                      // ~ - Find
         break;
      default :
         {
            assert(0); //illegal character
            return(false);
         }
   }

   dstString = dstString.substr( pos );

   pos = dstString.find( CHAR_SC );

   dstFieldValue = dstString.substr( 0, pos );

   pDataFilterElement = new DataFilterElement( fieldId, operation, dstFieldValue );
   if( pDataFilterElement )
      vect.push_back( pDataFilterElement );
   else
      success = false;

   return(success);
}

//******************************************************************************
void BFDataFilter::getFilter( DString & dstFilter )
{

}

//******************************************************************************
bool BFDataFilter::isVisible( const BFAbstractCBO * const pObj, const BFDataGroupId& idDataGroup )
{
   DATAFILTERVECTOR::iterator iter = vect.begin();
   bool rtnVal = true;

   DString dstFieldValue = NULL_STRING;

   while( iter != vect.end() )
   {
      pObj->getField( (*iter)->m_fieldId, dstFieldValue, idDataGroup );
      dstFieldValue.strip();
      if( !filterCompare( dstFieldValue, (*iter)->m_operation, (*iter)->m_fieldValue ) )
      {
         rtnVal = false;
         break;
      };
      ++iter;
   };
   return(rtnVal);
}

//******************************************************************************
bool BFDataFilter::filterCompare( const DString & dstFieldValue, OPCODES lOperation, const DString & dstReferenceValue )
{
   bool rtnVal = false;

   switch( lOperation )
   {
      case OP_EQUAL:
         rtnVal = dstFieldValue == dstReferenceValue; 
         break;
      case OP_LESS:
         rtnVal = dstFieldValue < dstReferenceValue; 
         break;
      case OP_LESS_OR_EQUAL:
         rtnVal = dstFieldValue <= dstReferenceValue; 
         break;
      case OP_GREATER:
         rtnVal = dstFieldValue > dstReferenceValue; 
         break;
      case OP_GREATER_OR_EQUAL:
         rtnVal = dstFieldValue >= dstReferenceValue; 
         break;
      case OP_NOT_EQUAL:
         rtnVal = dstFieldValue != dstReferenceValue; 
         break;
      case OP_FIND:
      case OP_NOT_FIND:
         {
            DString dstrSource = dstFieldValue;
            DString dstrSubstring = dstReferenceValue;
            dstrSource.upperCase();
            dstrSubstring.upperCase();
            rtnVal = (lOperation == OP_FIND) ? (dstrSource.find(dstrSubstring) != -1) : (dstrSource.find(dstrSubstring) == -1);
         }
         break;
      default:
         assert(0); //invalid opcode
   };
   return(rtnVal);
}

//******************************************************************************
bool BFDataFilter::setFilter( const DString & lDataFilter )
{
   DString dstTemp = lDataFilter;
   bool rtnVal = false;
   int pos = 0;

   clearFilter( );

   while( (pos = dstTemp.find( CHAR_SC )) != DString::npos )
   {
      if( addElement( dstTemp.substr( 0, pos ) ) )
         rtnVal = true;
      dstTemp = dstTemp.substr( pos + 1);
   };
   if( dstTemp != NULL_STRING )
      if( addElement( dstTemp ) && !rtnVal )
         rtnVal = true;

   return(rtnVal);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfcbo/BFDataFilter.cpp-arc  $
 // 
 //    Rev 1.10   Jan 06 2003 16:40:26   PURDYECH
 // BFDataGroupId changeover
 // 
 //    Rev 1.9   Nov 27 2002 15:02:08   PURDYECH
 // Documentation Changes
 // 
 //    Rev 1.8   Oct 09 2002 17:40:02   PURDYECH
 // New PVCS Database
 // 
 //    Rev 1.7   Aug 29 2002 12:51:06   SMITHDAV
 // ClientLocale and typed field changes.
 // 
 //    Rev 1.6   Feb 25 2002 18:50:46   PURDYECH
 // Phase 1 of BFData Rollout - Base Component Compatibility
 // 
 //    Rev 1.5   03 Jul 2001 16:22:16   SMITHDAV
 // Add revision constants.
 // 
 //    Rev 1.4   03 May 2001 14:02:38   SMITHDAV
 // Session management restructuring.
 // 
 //    Rev 1.3   Aug 11 2000 13:21:30   HERNANDO
 // Modified Find/!Find op. to ignore case
 // 
 //    Rev 1.2   Jul 24 2000 09:33:10   HERNANDO
 // Added Find and Not Find filter operations.  Use ~ and !~
 // 
 //    Rev 1.1   May 11 2000 16:19:16   BUZILA
 // changed to ignore heading and trailing spaces inside field values on filter check
 // 
 //    Rev 1.0   Apr 13 2000 10:35:12   BUZILA
 // Initial revision.
 * 
 */


