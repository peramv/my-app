// BFDataImpl implementation file for DataSet DSTC0178.VWRepeat_Record
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0178_vwrepeat_record.h"


// This function creates an instance of dsi_DSTC0178_VWRepeat_Record
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0178_VWRepeat_Record() { return new dsi_DSTC0178_VWRepeat_Record; }

dsi_DSTC0178_VWRepeat_Record::dsi_DSTC0178_VWRepeat_Record()
: BFDataImpl( 40002797 )
, ModDate_( ifds::ModDate, &ifds::s_FldProp_ModDate )
, FieldName_( ifds::FieldName, &ifds::s_FldProp_FieldName )
, ModUser_( ifds::ModUser, &ifds::s_FldProp_ModUser )
, OldValue_( ifds::OldValue, &ifds::s_FldProp_OldValue )
, NewValue_( ifds::NewValue, &ifds::s_FldProp_NewValue )
{
   cFields_ = 5;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0178_VWRepeat_Record::~dsi_DSTC0178_VWRepeat_Record()
{
}

BFDataImpl* dsi_DSTC0178_VWRepeat_Record::clone()
{
   dsi_DSTC0178_VWRepeat_Record* p = new dsi_DSTC0178_VWRepeat_Record;
   p->ModDate_ = ModDate_;
   p->FieldName_ = FieldName_;
   p->ModUser_ = ModUser_;
   p->OldValue_ = OldValue_;
   p->NewValue_ = NewValue_;
   return(p);
}

BFDataField* dsi_DSTC0178_VWRepeat_Record::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40000217: return ( &ModDate_ ); break; // ModDate
      case 40002798: return ( &FieldName_ ); break; // FieldName
      case 40000218: return ( &ModUser_ ); break; // ModUser
      case 40002576: return ( &OldValue_ ); break; // OldValue
      case 40002577: return ( &NewValue_ ); break; // NewValue
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0178_VWRepeat_Record::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0178_VWRepeat_Record* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0178_VWRepeat_Record::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 5 )
   {
      BFDataField* pField = aFlds_[iField];
      if( NULL == pField )
      {
         switch(iField)
         {
            case 0: aFlds_[0] = &ModDate_; break;
            case 1: aFlds_[1] = &FieldName_; break;
            case 2: aFlds_[2] = &ModUser_; break;
            case 3: aFlds_[3] = &OldValue_; break;
            case 4: aFlds_[4] = &NewValue_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0178_VWRepeat_Record::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0178_VWRepeat_Record* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0178_VWRepeat_Record::getLargestDefinedField( void ) const
{
   return( 60 );
}

unsigned long dsi_DSTC0178_VWRepeat_Record::getDefinedByteLength( void ) const
{
   return( 250 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0178_VWRepeat_Record::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0178_VWRepeat_Record::fieldExists( id );
}

bool dsi_DSTC0178_VWRepeat_Record::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40000217: return( true );
      case 40002798: return( true );
      case 40000218: return( true );
      case 40002576: return( true );
      case 40002577: return( true );
   }
   return false;
}

