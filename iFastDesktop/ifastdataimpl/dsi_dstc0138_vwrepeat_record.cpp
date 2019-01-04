// BFDataImpl implementation file for DataSet DSTC0138.VWRepeat_Record
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0138_vwrepeat_record.h"


// This function creates an instance of dsi_DSTC0138_VWRepeat_Record
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0138_VWRepeat_Record() { return new dsi_DSTC0138_VWRepeat_Record; }

dsi_DSTC0138_VWRepeat_Record::dsi_DSTC0138_VWRepeat_Record()
: BFDataImpl( 40001742 )
, RedCode_( ifds::RedCode, &ifds::s_FldProp_RedCode )
, RedCodeDesc_( ifds::RedCodeDesc, &ifds::s_FldProp_RedCodeDesc )
, MaximumApplies_( ifds::MaximumApplies, &ifds::s_FldProp_MaximumApplies )
, MinimumApplies_( ifds::MinimumApplies, &ifds::s_FldProp_MinimumApplies )
, WDFeeDefn_( ifds::WDFeeDefn, &ifds::s_FldProp_WDFeeDefn )
, DTAEligible_( ifds::DTAEligible, &ifds::s_FldProp_DTAEligible )
{
   cFields_ = 6;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0138_VWRepeat_Record::~dsi_DSTC0138_VWRepeat_Record()
{
}

BFDataImpl* dsi_DSTC0138_VWRepeat_Record::clone()
{
   dsi_DSTC0138_VWRepeat_Record* p = new dsi_DSTC0138_VWRepeat_Record;
   p->RedCode_ = RedCode_;
   p->RedCodeDesc_ = RedCodeDesc_;
   p->MaximumApplies_ = MaximumApplies_;
   p->MinimumApplies_ = MinimumApplies_;
   p->WDFeeDefn_ = WDFeeDefn_;
   p->DTAEligible_ = DTAEligible_;
   return(p);
}

BFDataField* dsi_DSTC0138_VWRepeat_Record::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40000435: return ( &RedCode_ ); break; // RedCode
      case 40000436: return ( &RedCodeDesc_ ); break; // RedCodeDesc
      case 40001251: return ( &MaximumApplies_ ); break; // MaximumApplies
      case 40001250: return ( &MinimumApplies_ ); break; // MinimumApplies
      case 40004092: return ( &WDFeeDefn_ ); break; // WDFeeDefn
      case 40004170: return ( &DTAEligible_ ); break; // DTAEligible
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0138_VWRepeat_Record::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0138_VWRepeat_Record* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0138_VWRepeat_Record::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 6 )
   {
      BFDataField* pField = aFlds_[iField];
      if( NULL == pField )
      {
         switch(iField)
         {
            case 0: aFlds_[0] = &RedCode_; break;
            case 1: aFlds_[1] = &RedCodeDesc_; break;
            case 2: aFlds_[2] = &MaximumApplies_; break;
            case 3: aFlds_[3] = &MinimumApplies_; break;
            case 4: aFlds_[4] = &WDFeeDefn_; break;
            case 5: aFlds_[5] = &DTAEligible_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0138_VWRepeat_Record::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0138_VWRepeat_Record* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0138_VWRepeat_Record::getLargestDefinedField( void ) const
{
   return( 60 );
}

unsigned long dsi_DSTC0138_VWRepeat_Record::getDefinedByteLength( void ) const
{
   return( 133 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0138_VWRepeat_Record::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0138_VWRepeat_Record::fieldExists( id );
}

bool dsi_DSTC0138_VWRepeat_Record::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40000435: return( true );
      case 40000436: return( true );
      case 40001251: return( true );
      case 40001250: return( true );
      case 40004092: return( true );
      case 40004170: return( true );
   }
   return false;
}

