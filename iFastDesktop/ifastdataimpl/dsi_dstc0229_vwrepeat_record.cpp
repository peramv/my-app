// BFDataImpl implementation file for DataSet DSTC0229.VWRepeat_Record
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0229_vwrepeat_record.h"


// This function creates an instance of dsi_DSTC0229_VWRepeat_Record
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0229_VWRepeat_Record() { return new dsi_DSTC0229_VWRepeat_Record; }

dsi_DSTC0229_VWRepeat_Record::dsi_DSTC0229_VWRepeat_Record()
: BFDataImpl( 40003555 )
, FundGroup_( ifds::FundGroup, &ifds::s_FldProp_FundGroup )
, GroupName_( ifds::GroupName, &ifds::s_FldProp_GroupName )
{
   cFields_ = 2;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0229_VWRepeat_Record::~dsi_DSTC0229_VWRepeat_Record()
{
}

BFDataImpl* dsi_DSTC0229_VWRepeat_Record::clone()
{
   dsi_DSTC0229_VWRepeat_Record* p = new dsi_DSTC0229_VWRepeat_Record;
   p->FundGroup_ = FundGroup_;
   p->GroupName_ = GroupName_;
   return(p);
}

BFDataField* dsi_DSTC0229_VWRepeat_Record::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40002031: return ( &FundGroup_ ); break; // FundGroup
      case 40001075: return ( &GroupName_ ); break; // GroupName
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0229_VWRepeat_Record::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0229_VWRepeat_Record* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0229_VWRepeat_Record::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 2 )
   {
      BFDataField* pField = aFlds_[iField];
      if( NULL == pField )
      {
         switch(iField)
         {
            case 0: aFlds_[0] = &FundGroup_; break;
            case 1: aFlds_[1] = &GroupName_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0229_VWRepeat_Record::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0229_VWRepeat_Record* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0229_VWRepeat_Record::getLargestDefinedField( void ) const
{
   return( 60 );
}

unsigned long dsi_DSTC0229_VWRepeat_Record::getDefinedByteLength( void ) const
{
   return( 120 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0229_VWRepeat_Record::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0229_VWRepeat_Record::fieldExists( id );
}

bool dsi_DSTC0229_VWRepeat_Record::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40002031: return( true );
      case 40001075: return( true );
   }
   return false;
}

