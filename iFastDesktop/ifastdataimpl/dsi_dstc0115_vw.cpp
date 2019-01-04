// BFDataImpl implementation file for DataSet DSTC0115.VW
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0115_vw.h"


// This function creates an instance of dsi_DSTC0115_VW
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0115_VW() { return new dsi_DSTC0115_VW; }

dsi_DSTC0115_VW::dsi_DSTC0115_VW()
: BFDataImpl( 40001357 )
, UpdateStatus_( ifds::UpdateStatus, &ifds::s_FldProp_UpdateStatus )
, BODate_( ifds::BODate, &ifds::s_FldProp_BODate )
, BOTime_( ifds::BOTime, &ifds::s_FldProp_BOTime )
, BOZone_( ifds::BOZone, &ifds::s_FldProp_BOZone )
, FIDate_( ifds::FIDate, &ifds::s_FldProp_FIDate )
, FITime_( ifds::FITime, &ifds::s_FldProp_FITime )
, FIZone_( ifds::FIZone, &ifds::s_FldProp_FIZone )
, ConfNum_( ifds::ConfNum, &ifds::s_FldProp_ConfNum )
, TradingAvailable_( ifds::TradingAvailable, &ifds::s_FldProp_TradingAvailable )
{
   cFields_ = 9;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0115_VW::~dsi_DSTC0115_VW()
{
}

BFDataImpl* dsi_DSTC0115_VW::clone()
{
   dsi_DSTC0115_VW* p = new dsi_DSTC0115_VW;
   p->UpdateStatus_ = UpdateStatus_;
   p->BODate_ = BODate_;
   p->BOTime_ = BOTime_;
   p->BOZone_ = BOZone_;
   p->FIDate_ = FIDate_;
   p->FITime_ = FITime_;
   p->FIZone_ = FIZone_;
   p->ConfNum_ = ConfNum_;
   p->TradingAvailable_ = TradingAvailable_;
   return(p);
}

BFDataField* dsi_DSTC0115_VW::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40000989: return ( &UpdateStatus_ ); break; // UpdateStatus
      case 40001823: return ( &BODate_ ); break; // BODate
      case 40001824: return ( &BOTime_ ); break; // BOTime
      case 40001825: return ( &BOZone_ ); break; // BOZone
      case 40001826: return ( &FIDate_ ); break; // FIDate
      case 40001827: return ( &FITime_ ); break; // FITime
      case 40001828: return ( &FIZone_ ); break; // FIZone
      case 40001829: return ( &ConfNum_ ); break; // ConfNum
      case 40002633: return ( &TradingAvailable_ ); break; // TradingAvailable
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0115_VW::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0115_VW* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0115_VW::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 9 )
   {
      BFDataField* pField = aFlds_[iField];
      if( NULL == pField )
      {
         switch(iField)
         {
            case 0: aFlds_[0] = &UpdateStatus_; break;
            case 1: aFlds_[1] = &BODate_; break;
            case 2: aFlds_[2] = &BOTime_; break;
            case 3: aFlds_[3] = &BOZone_; break;
            case 4: aFlds_[4] = &FIDate_; break;
            case 5: aFlds_[5] = &FITime_; break;
            case 6: aFlds_[6] = &FIZone_; break;
            case 7: aFlds_[7] = &ConfNum_; break;
            case 8: aFlds_[8] = &TradingAvailable_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0115_VW::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0115_VW* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0115_VW::getLargestDefinedField( void ) const
{
   return( 20 );
}

unsigned long dsi_DSTC0115_VW::getDefinedByteLength( void ) const
{
   return( 101 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0115_VW::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0115_VW::fieldExists( id );
}

bool dsi_DSTC0115_VW::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40000989: return( true );
      case 40001823: return( true );
      case 40001824: return( true );
      case 40001825: return( true );
      case 40001826: return( true );
      case 40001827: return( true );
      case 40001828: return( true );
      case 40001829: return( true );
      case 40002633: return( true );
   }
   return false;
}

