// BFDataImpl implementation file for DataSet DSTC0254.VWRepeat_Record
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0254_vwrepeat_record.h"


// This function creates an instance of dsi_DSTC0254_VWRepeat_Record
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0254_VWRepeat_Record() { return new dsi_DSTC0254_VWRepeat_Record; }

dsi_DSTC0254_VWRepeat_Record::dsi_DSTC0254_VWRepeat_Record()
: BFDataImpl( 40003860 )
, GroupCode_( ifds::GroupCode, &ifds::s_FldProp_GroupCode )
, MiscCode_( ifds::MiscCode, &ifds::s_FldProp_MiscCode )
, MiscDesc_( ifds::MiscDesc, &ifds::s_FldProp_MiscDesc )
, MiscCategory_( ifds::MiscCategory, &ifds::s_FldProp_MiscCategory )
{
   cFields_ = 4;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0254_VWRepeat_Record::~dsi_DSTC0254_VWRepeat_Record()
{
}

BFDataImpl* dsi_DSTC0254_VWRepeat_Record::clone()
{
   dsi_DSTC0254_VWRepeat_Record* p = new dsi_DSTC0254_VWRepeat_Record;
   p->GroupCode_ = GroupCode_;
   p->MiscCode_ = MiscCode_;
   p->MiscDesc_ = MiscDesc_;
   p->MiscCategory_ = MiscCategory_;
   return(p);
}

BFDataField* dsi_DSTC0254_VWRepeat_Record::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40000800: return ( &GroupCode_ ); break; // GroupCode
      case 40003862: return ( &MiscCode_ ); break; // MiscCode
      case 40003863: return ( &MiscDesc_ ); break; // MiscDesc
      case 40003864: return ( &MiscCategory_ ); break; // MiscCategory
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0254_VWRepeat_Record::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0254_VWRepeat_Record* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0254_VWRepeat_Record::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 4 )
   {
      BFDataField* pField = aFlds_[iField];
      if( NULL == pField )
      {
         switch(iField)
         {
            case 0: aFlds_[0] = &GroupCode_; break;
            case 1: aFlds_[1] = &MiscCode_; break;
            case 2: aFlds_[2] = &MiscDesc_; break;
            case 3: aFlds_[3] = &MiscCategory_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0254_VWRepeat_Record::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0254_VWRepeat_Record* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0254_VWRepeat_Record::getLargestDefinedField( void ) const
{
   return( 60 );
}

unsigned long dsi_DSTC0254_VWRepeat_Record::getDefinedByteLength( void ) const
{
   return( 240 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0254_VWRepeat_Record::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0254_VWRepeat_Record::fieldExists( id );
}

bool dsi_DSTC0254_VWRepeat_Record::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40000800: return( true );
      case 40003862: return( true );
      case 40003863: return( true );
      case 40003864: return( true );
   }
   return false;
}

