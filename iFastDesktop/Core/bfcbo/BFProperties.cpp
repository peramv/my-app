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
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : BFProperties.hpp
// ^AUTHOR : Mihai Virgil Buzila 
// ^DATE   : October 1999
//
// ^CLASS    : BFProperties
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************
#include <bfutil\rtrevisiondefines.hpp>
RT_SOURCE_REVISION( "$Archive:   Y:/VCS/BF iFAST/core/bfcbo/BFProperties.cpp-arc  $", "$Revision:   1.25  $" )

#include <srcprag.h>
#include "bfproperties.hpp"
#include <bfdata\bfdatafieldproperties.hpp>
#include <bfdata\bffieldid.hpp>
#include <bfutil\clientlocalecontext.hpp>
#include <idistring.hpp>

//******************************************************************************

BFProperties::BFProperties( const BFDataFieldProperties* pProps )
: pProps_( pProps )
, _mMinLength( pProps_->getMinLength() )
, _mMaxLength( pProps_->getLength() )
, _pMask( NULL )
, _pDefaultValue( NULL )
, _pSubstituteValues( NULL )
, _pAllSubstituteValues( new DString() )
, _pFieldLabel( NULL )
, _mRequired(true)
, _mReadOnly(false)
, _isSubstFormattedValueSet(false)
, _bDynamicCreatedSubst(false)
{
   pProps_->getAllSubstituteValues( *_pAllSubstituteValues, ClientLocaleContext::get(), true);
};

//******************************************************************************
BFProperties::BFProperties( const BFProperties& rhs )
: _pMask( NULL )
, _pDefaultValue( NULL )
, _pSubstituteValues( NULL )
, _pAllSubstituteValues( new DString() )
, _pFieldLabel( NULL )
{
   *this = rhs;
}

BFProperties& BFProperties::operator=( const BFProperties& rhs )
{
   if( this != &rhs )
   {
      _mMinLength = rhs._mMinLength;
      _mMaxLength = rhs._mMaxLength;
      if( NULL != rhs._pMask )
      {
         _pMask = new DString( *rhs._pMask );
      }
      if( NULL != rhs._pDefaultValue )
      {
         _pDefaultValue = new DString( *rhs._pDefaultValue );
      }
      if( NULL != rhs._pSubstituteValues )
      {
         _pSubstituteValues = new DString( *rhs._pSubstituteValues );
      }
      if( NULL != rhs._pAllSubstituteValues )
      {
         _pAllSubstituteValues = new DString( *rhs._pAllSubstituteValues );
      }
      if( NULL != rhs._pFieldLabel )
      {
         _pFieldLabel = new DString( *rhs._pFieldLabel );
      }
      _mRequired = rhs._mRequired;
      _mReadOnly = rhs._mReadOnly;
      _isSubstFormattedValueSet = rhs._isSubstFormattedValueSet;
      _bDynamicCreatedSubst = rhs._bDynamicCreatedSubst;
   }
   return( *this );
}

//******************************************************************************
void BFProperties::checkSubstValues()
{
   if( !_pAllSubstituteValues )
   {
      _pAllSubstituteValues = new DString;
      if( pProps_ ) pProps_->getAllSubstituteValues( *_pAllSubstituteValues, ClientLocaleContext::get(), true);
   }
}

//******************************************************************************
BFProperties::~BFProperties()
{
   delete _pDefaultValue;
   delete _pAllSubstituteValues;
   delete _pFieldLabel;
   delete _pMask;
};

//******************************************************************************
const DString & BFProperties::getDefaultValue( DString &strValueOut ) const
{
   if( _pDefaultValue == NULL )
      strValueOut = pProps_->getDefaultValue( ClientLocaleContext::get() );
   else
      strValueOut = *_pDefaultValue;

   return(strValueOut);
}

//******************************************************************************
bool  BFProperties::getMask( DString &strValueOut ) const
{
   if( _pMask == NULL )
      strValueOut = pProps_->getMask( ClientLocaleContext::get() )->getMask();
   else
      strValueOut = *_pMask;
   return(true);

} 

//******************************************************************************
bool  BFProperties::getAllSubstituteValues( DString &strValueOut ) const
{
   if( _pAllSubstituteValues == NULL )
   {
      pProps_->getAllSubstituteValues( strValueOut, ClientLocaleContext::get(), true );
   }
   else
   {
      strValueOut = *_pAllSubstituteValues;
   }
   return(true);
}

//******************************************************************************
const DString & BFProperties::getFieldLabel( DString &strValueOut ) const
{
   if( _pFieldLabel == NULL )
      strValueOut = pProps_->getLabel( ClientLocaleContext::get() );
   else
      strValueOut = *_pFieldLabel;
   return(strValueOut);
};

void BFProperties::reinitAllSubstValues()
{
   if( _pAllSubstituteValues )
   {
      delete _pAllSubstituteValues;
      _pAllSubstituteValues = NULL;
   }
   _pSubstituteValues = NULL;
   checkSubstValues();
};

//******************************************************************************
void BFProperties::setAllSubstituteValues( const DString &strValues )
{
   if( _pAllSubstituteValues )
      delete _pAllSubstituteValues;

   _pAllSubstituteValues = new DString( strValues );
   _bDynamicCreatedSubst = true;
}

//******************************************************************************
void BFProperties::setSubstituteValues( DString * substValues )
{
   _bDynamicCreatedSubst = true;
   _pSubstituteValues = substValues;
}

//******************************************************************************
void BFProperties::appendValueToSubst (const DString &strValue)
{
   DString strValueNC (strValue),
      strValueNCUppercase;

   strValueNC.stripTrailing();
   strValueNCUppercase = strValueNC;
   strValueNCUppercase.upperCase();

   if (!isValidKey (strValueNC) && 
       !isValidKey (strValueNCUppercase) &&
       !isValidValue (strValueNC)) //check for duplicates
   {
      if (_pAllSubstituteValues) 
      {
         addIDITagValue (*_pAllSubstituteValues, strValue, strValue);
         _bDynamicCreatedSubst = true;
      }
   }
}

//******************************************************************************
void BFProperties::getSubstituteValues( DString &strValueOut ) const
{
   if (_pSubstituteValues)
      strValueOut = *_pSubstituteValues;
   else
      strValueOut = *_pAllSubstituteValues;
}

//******************************************************************************
void BFProperties::initUnformattedSubstValues( const DString &allSubstString )
{
   typedef std::map< DString, DString, std::less< DString > > TRANSF_MAP;

   TRANSF_MAP fromMap;

   std::vector< item* > toVector;
   DString lTagName, lValue;


   I_CHAR * lFromString = const_cast < I_CHAR* > ( allSubstString.c_str());
   while( *lFromString != 0 )
   {
      lFromString = parseIdiString( lFromString, lTagName, lValue );
      fromMap.insert(TRANSF_MAP::value_type( lTagName, lValue ) );
   };

   lFromString = const_cast < I_CHAR* > ( _pAllSubstituteValues->c_str());
   while( *lFromString != 0 )
   {
      lFromString = parseIdiString( lFromString, lTagName, lValue );
      if( lValue == I_("xxx") )
         lValue = NULL_STRING;
      item * lItem = new item( lTagName, lValue );
      toVector.push_back( lItem );
   };

   TRANSF_MAP::iterator fromMapIter = fromMap.begin();
   std::vector< item* >::iterator toVectorIter = toVector.begin();

   *_pAllSubstituteValues = I_("");

   item * currItem = NULL;

   while( toVectorIter != toVector.end() )
   {
      currItem = *toVectorIter;
      fromMapIter = fromMap.find( currItem->m_key );
      if( fromMapIter != fromMap.end() && currItem->m_value == NULL_STRING )
         addIDITagValue( *_pAllSubstituteValues, currItem->m_key, (*fromMapIter).second );
      else
         addIDITagValue( *_pAllSubstituteValues, currItem->m_key, currItem->m_value );
      ++toVectorIter;
   }

   fromMap.clear();
   toVectorIter = toVector.begin();
   while( toVectorIter != toVector.end() )
   {
      delete *toVectorIter;
      ++toVectorIter;
   }
   toVector.clear();

};

//******************************************************************************
void BFProperties::setMask( const DString & mask )
{
   _pMask = new DString( mask );
}

//******************************************************************************
void BFProperties::setReadOnly( bool readonly )
{
   _mReadOnly = readonly;
}

//******************************************************************************
void BFProperties::setRequired( bool required )
{
   _mRequired = required;
}
//*******************************************************************************
bool BFProperties::isValidKey(const DString& strKeyIn)
{
   DString strSubListValue;
   getSubstituteValues(strSubListValue);
   // strSubListValue is an IDI string, so the key should be ;key=, unless it is the
   // first value, in which case it will be key=
   DString k = I_( ';' ) + strKeyIn + I_( '=' );
   if( strSubListValue.find( k ) != strSubListValue.npos )
   {
      return( true );
   }
   k = strKeyIn + I_( '=' );
   if( strSubListValue.substr( 0, strKeyIn.size() + 1 ) == k )
   {
      return( true );
   }
   return( false );

}
//*******************************************************************************
bool BFProperties::isValidValue(const DString& strValueIn)
{
   DString strSubListValue;
   getSubstituteValues(strSubListValue);
   // strSubListValue is an IDI string, so the value should be =value;, unless it is the
   // last value, in which case it will be =value\0
   DString v = I_( '=' ) + strValueIn + I_( ';' );
   if( strSubListValue.find( v ) != strSubListValue.npos )
   {
      return( true );
   }
   // that was the =value; case.  Now try the =value\0 case;
   v = v.substr( 0, v.size() - 1 );
   if( strSubListValue.find( v, strSubListValue.size() - v.size() ) != strSubListValue.npos )
   {
      return( true );
   }

   return( false );
}

//*****************************************************************************
bool BFProperties::formatValue( const BFFieldId& idField, DString & InRetValue, bool bFormat )
{
   if( bFormat )
   {
      DString strKey,strValue; 
      DString strSubListValue;
      getSubstituteValues(strSubListValue);

      I_CHAR* iStringPtr = const_cast < I_CHAR* > ( strSubListValue.c_str());
      while( *iStringPtr != 0 )
      {
         iStringPtr = parseIdiString( iStringPtr, strKey, strValue );
         if( InRetValue == strKey )
         {
            InRetValue = strValue;
            return(true);
         }
      }
   }
   return(false);
}

//*****************************************************************************
bool BFProperties::unformatValue( const BFFieldId& idField, DString & InRetKey, bool bUnformat )
{
   if( bUnformat )
   {
      DString strKey,strValue; 
      DString strSubListValue;
      getSubstituteValues(strSubListValue);

      I_CHAR* iStringPtr = const_cast < I_CHAR* > ( strSubListValue.c_str());
      while( *iStringPtr != 0 )
      {
         iStringPtr = parseIdiString( iStringPtr, strKey, strValue );
         if( InRetKey == strValue )
         {
            InRetKey = strKey;
            return(true);
         }
      }
   }
   return(false);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/core/bfcbo/BFProperties.cpp-arc  $
//
//   Rev 1.25   May 12 2009 11:59:14   jankovii
//PET 159770 FN05 Auto Batching.
//
//   Rev 1.24   05 May 2009 10:10:46   popescu
//Check if the subst values are NULL before append
 * 
 *    Rev 1.22   Oct 09 2002 17:40:08   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.21   Sep 03 2002 11:05:04   PURDYECH
 * Further BFFieldId fixes
 * 
 *    Rev 1.20   Aug 29 2002 12:51:08   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.19   Aug 16 2002 14:07:32   PURDYECH
 * Added copy ctor and assignment operator
 * 
 *    Rev 1.18   Jun 05 2002 16:25:42   PURDYECH
 * FormatField/UnformatField changes
 * 
 *    Rev 1.17   22 May 2002 22:18:32   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.16   22 May 2002 17:54:22   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.15   25 Mar 2002 13:10:20   PURDYECH
 * bah...
 * 
 *    Rev 1.14   25 Mar 2002 13:02:48   PURDYECH
 * ...and another one
 * 
 *    Rev 1.13   25 Mar 2002 13:01:20   PURDYECH
 * Fixed silly bug in ctor
 * 
 *    Rev 1.12   22 Mar 2002 15:14:00   PURDYECH
 * Removed compile-time "including..." message
 * Use #pragma once as include guard
 * Include files with lower-case only names
 * 
 *    Rev 1.11   03 Jul 2001 16:22:20   SMITHDAV
 * Add revision constants.
 * 
 *    Rev 1.10   May 29 2001 10:20:54   YINGBAOL
 * add formatValue method
 * 
 *    Rev 1.9   03 May 2001 14:02:40   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.8   Nov 23 2000 10:19:10   YINGBAOL
 * more fix for subsitutelist checking
 * 
 *    Rev 1.7   Nov 21 2000 09:51:08   YINGBAOL
 * add isValidKey and isValidValue methods
 * 
 *    Rev 1.6   Nov 13 2000 10:01:12   HUANGSHA
 * more fixed in subst
 * 
 *    Rev 1.5   Nov 02 2000 16:26:10   HUANGSHA
 * added variable to indicate the dynamic created subst
 * 
 *    Rev 1.4   Sep 27 2000 15:10:42   VASILEAD
 * Added ClientLocale to BFProperties
 * 
 *    Rev 1.3   Jun 13 2000 17:37:40   DT24433
 * new Infra interfaces use ClientLocale
 * 
 *    Rev 1.2   May 31 2000 16:42:04   BUZILA
 * adding masks
 * 
 *    Rev 1.1   May 11 2000 16:18:00   BUZILA
 * reimplementation
 * 
 *    Rev 1.0   Feb 15 2000 10:57:30   SMITHDAV
 * Initial revision.
// 
//    Rev 1.5   Dec 23 1999 14:15:26   BUZILA
// m_substValues should be initialized
// 
//    Rev 1.4   Dec 19 1999 16:38:34   BUZILA
// changes related to substitutionLists handling
// 
//    Rev 1.3   Nov 20 1999 19:38:22   BUZILA
// added BFProperties repository
// 
//    Rev 1.2   Nov 10 1999 17:24:52   DT24433
// made get methods const and added revision area
 * 
 */


