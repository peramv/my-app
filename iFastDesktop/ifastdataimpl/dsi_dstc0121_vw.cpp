// BFDataImpl implementation file for DataSet DSTC0121.VW
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0121_vw.h"


// This function creates an instance of dsi_DSTC0121_VW
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0121_VW() { return new dsi_DSTC0121_VW; }

dsi_DSTC0121_VW::dsi_DSTC0121_VW()
: BFDataImpl( 40001670 )
, AcqFee_( ifds::AcqFee, &ifds::s_FldProp_AcqFee )
, AcqFeeType_( ifds::AcqFeeType, &ifds::s_FldProp_AcqFeeType )
, MaxFeeActive_( ifds::MaxFeeActive, &ifds::s_FldProp_MaxFeeActive )
, MaxFee_( ifds::MaxFee, &ifds::s_FldProp_MaxFee )
, MaxFeeType_( ifds::MaxFeeType, &ifds::s_FldProp_MaxFeeType )
, MaxPercent_( ifds::MaxPercent, &ifds::s_FldProp_MaxPercent )
, MaxFlatFundCurr_( ifds::MaxFlatFundCurr, &ifds::s_FldProp_MaxFlatFundCurr )
, MinFee_( ifds::MinFee, &ifds::s_FldProp_MinFee )
, MinPercent_( ifds::MinPercent, &ifds::s_FldProp_MinPercent )
{
   cFields_ = 9;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0121_VW::~dsi_DSTC0121_VW()
{
}

BFDataImpl* dsi_DSTC0121_VW::clone()
{
   dsi_DSTC0121_VW* p = new dsi_DSTC0121_VW;
   p->AcqFee_ = AcqFee_;
   p->AcqFeeType_ = AcqFeeType_;
   p->MaxFeeActive_ = MaxFeeActive_;
   p->MaxFee_ = MaxFee_;
   p->MaxFeeType_ = MaxFeeType_;
   p->MaxPercent_ = MaxPercent_;
   p->MaxFlatFundCurr_ = MaxFlatFundCurr_;
   p->MinFee_ = MinFee_;
   p->MinPercent_ = MinPercent_;
   return(p);
}

BFDataField* dsi_DSTC0121_VW::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40001671: return ( &AcqFee_ ); break; // AcqFee
      case 40001672: return ( &AcqFeeType_ ); break; // AcqFeeType
      case 40001673: return ( &MaxFeeActive_ ); break; // MaxFeeActive
      case 40001674: return ( &MaxFee_ ); break; // MaxFee
      case 40001675: return ( &MaxFeeType_ ); break; // MaxFeeType
      case 40001676: return ( &MaxPercent_ ); break; // MaxPercent
      case 40001677: return ( &MaxFlatFundCurr_ ); break; // MaxFlatFundCurr
      case 40002899: return ( &MinFee_ ); break; // MinFee
      case 40002900: return ( &MinPercent_ ); break; // MinPercent
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0121_VW::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0121_VW* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0121_VW::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 9 )
   {
      BFDataField* pField = aFlds_[iField];
      if( NULL == pField )
      {
         switch(iField)
         {
            case 0: aFlds_[0] = &AcqFee_; break;
            case 1: aFlds_[1] = &AcqFeeType_; break;
            case 2: aFlds_[2] = &MaxFeeActive_; break;
            case 3: aFlds_[3] = &MaxFee_; break;
            case 4: aFlds_[4] = &MaxFeeType_; break;
            case 5: aFlds_[5] = &MaxPercent_; break;
            case 6: aFlds_[6] = &MaxFlatFundCurr_; break;
            case 7: aFlds_[7] = &MinFee_; break;
            case 8: aFlds_[8] = &MinPercent_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0121_VW::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0121_VW* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0121_VW::getLargestDefinedField( void ) const
{
   return( 30 );
}

unsigned long dsi_DSTC0121_VW::getDefinedByteLength( void ) const
{
   return( 143 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0121_VW::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0121_VW::fieldExists( id );
}

bool dsi_DSTC0121_VW::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40001671: return( true );
      case 40001672: return( true );
      case 40001673: return( true );
      case 40001674: return( true );
      case 40001675: return( true );
      case 40001676: return( true );
      case 40001677: return( true );
      case 40002899: return( true );
      case 40002900: return( true );
   }
   return false;
}

