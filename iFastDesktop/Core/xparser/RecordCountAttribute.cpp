/*******************************************************************************
 *
 * COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 2000 by DST Systems, Inc.
 *
*******************************************************************************/
#include "stdafx.h"
#include "RecordCountAttribute.hpp"

#include "xparsercommon.hpp"

using namespace xp;

namespace
{
   const I_CHAR * const CLASSNAME  = I_("RecordCountAttribute");

   const DString TAG_NAME         = I_( "recordCount" );

   const DString NONE_VALUE = I_( "none" );
   const DString ALL_RECORDS_VALUE  = I_( "allRecords" );

   const RecordCountAttribute::RecordCountType RCT_DEFAULT = RecordCountAttribute::RCT_NONE;
}

namespace CND
{
   extern const long ERR_INVALID_RECORD_COUNT_ATTRIBUTE;
   extern const long ERR_NEGATIVE_RECORD_COUNT_ATTRIBUTE;
}

//******************************************************************************
RecordCountAttribute::RecordCountAttribute( xercesc::AttributeList &attributes )
: _recordCount(0),
_strRecordCount(NULL_STRING)
{
   DString value = valueOf( TAG_NAME, attributes );

   if( value == NONE_VALUE )
   {
      _type = RCT_NONE;
   }
   else if( value == ALL_RECORDS_VALUE )
   {
      _type = RCT_ALL_RECORDS;
   }
   else if( value == NULL_STRING )
   {
      _type = RCT_DEFAULT;
   }
   else
   {
      _type = RCT_NUMERIC;
      _recordCount = value.asInteger();
      _strRecordCount.appendInt( _recordCount );

      if( _recordCount <= 0 )
      {
         DString strIDI;
         addIDITagValue( strIDI, I_("VALUE"), value );

         THROWFROMFILEIDI2( CND::XPARSER_CONDITION, CLASSNAME, CLASSNAME, CND::ERR_INVALID_RECORD_COUNT_ATTRIBUTE, strIDI );
      }
   }

}


//******************************************************************************
RecordCountAttribute::RecordCountAttribute( int recordCount )
: _type( RCT_NUMERIC ),
_recordCount( recordCount )
{
   if( _recordCount <= 0 )
      THROWFROMFILE2( CND::XPARSER_CONDITION, CLASSNAME, CLASSNAME, CND::ERR_NEGATIVE_RECORD_COUNT_ATTRIBUTE );

   _strRecordCount.appendInt( _recordCount );
}


//******************************************************************************
RecordCountAttribute::RecordCountAttribute( RecordCountType type )
: _type(type),
_recordCount( 1 )
{
   if( type == RCT_NUMERIC )
      _strRecordCount.appendInt( _recordCount );
}

//******************************************************************************
ElementAttribute *RecordCountAttribute::clone() const
{
   return(new RecordCountAttribute(*this));
}

//******************************************************************************
const DString &RecordCountAttribute::getTagName() const
{
   return(TAG_NAME);
}

//******************************************************************************
const DString &RecordCountAttribute::getValue() const
{
   switch( _type )
   {
      
      case RCT_NONE:
         return(NONE_VALUE);

      case RCT_ALL_RECORDS:
         return(ALL_RECORDS_VALUE);

      default:
         return(_strRecordCount);
   }
}

//******************************************************************************
bool RecordCountAttribute::hasDefaultValue() const
{
   return(_type == RCT_DEFAULT);
}
