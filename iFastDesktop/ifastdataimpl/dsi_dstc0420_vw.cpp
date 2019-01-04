// BFDataImpl implementation file for DataSet DSTC0420.VW
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0420_vw.h"


// This function creates an instance of dsi_DSTC0420_VW
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0420_VW() { return new dsi_DSTC0420_VW; }

dsi_DSTC0420_VW::dsi_DSTC0420_VW()
: BFDataImpl( 40006450 )
, IntCalcMthd_( ifds::IntCalcMthd, &ifds::s_FldProp_IntCalcMthd )
, SimpleTermList_( ifds::SimpleTermList, &ifds::s_FldProp_SimpleTermList )
, CompoundTermList_( ifds::CompoundTermList, &ifds::s_FldProp_CompoundTermList )
, SimpleCredFreqList_( ifds::SimpleCredFreqList, &ifds::s_FldProp_SimpleCredFreqList )
, CompoundCredFreqList_( ifds::CompoundCredFreqList, &ifds::s_FldProp_CompoundCredFreqList )
, MaturityDate_( ifds::MaturityDate, &ifds::s_FldProp_MaturityDate )
, NextIntCredDate_( ifds::NextIntCredDate, &ifds::s_FldProp_NextIntCredDate )
, CommRedRateList_( ifds::CommRedRateList, &ifds::s_FldProp_CommRedRateList )
, EstimatedRate_( ifds::EstimatedRate, &ifds::s_FldProp_EstimatedRate )
{
   cFields_ = 9;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0420_VW::~dsi_DSTC0420_VW()
{
}

BFDataImpl* dsi_DSTC0420_VW::clone()
{
   dsi_DSTC0420_VW* p = new dsi_DSTC0420_VW;
   p->IntCalcMthd_ = IntCalcMthd_;
   p->SimpleTermList_ = SimpleTermList_;
   p->CompoundTermList_ = CompoundTermList_;
   p->SimpleCredFreqList_ = SimpleCredFreqList_;
   p->CompoundCredFreqList_ = CompoundCredFreqList_;
   p->MaturityDate_ = MaturityDate_;
   p->NextIntCredDate_ = NextIntCredDate_;
   p->CommRedRateList_ = CommRedRateList_;
   p->EstimatedRate_ = EstimatedRate_;
   return(p);
}

BFDataField* dsi_DSTC0420_VW::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40006504: return ( &IntCalcMthd_ ); break; // IntCalcMthd
      case 40006518: return ( &SimpleTermList_ ); break; // SimpleTermList
      case 40006519: return ( &CompoundTermList_ ); break; // CompoundTermList
      case 40006520: return ( &SimpleCredFreqList_ ); break; // SimpleCredFreqList
      case 40006521: return ( &CompoundCredFreqList_ ); break; // CompoundCredFreqList
      case 40000679: return ( &MaturityDate_ ); break; // MaturityDate
      case 40006506: return ( &NextIntCredDate_ ); break; // NextIntCredDate
      case 40006522: return ( &CommRedRateList_ ); break; // CommRedRateList
      case 40006508: return ( &EstimatedRate_ ); break; // EstimatedRate
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0420_VW::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0420_VW* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0420_VW::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 9 )
   {
      BFDataField* pField = aFlds_[iField];
      if( NULL == pField )
      {
         switch(iField)
         {
            case 0: aFlds_[0] = &IntCalcMthd_; break;
            case 1: aFlds_[1] = &SimpleTermList_; break;
            case 2: aFlds_[2] = &CompoundTermList_; break;
            case 3: aFlds_[3] = &SimpleCredFreqList_; break;
            case 4: aFlds_[4] = &CompoundCredFreqList_; break;
            case 5: aFlds_[5] = &MaturityDate_; break;
            case 6: aFlds_[6] = &NextIntCredDate_; break;
            case 7: aFlds_[7] = &CommRedRateList_; break;
            case 8: aFlds_[8] = &EstimatedRate_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0420_VW::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0420_VW* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0420_VW::getLargestDefinedField( void ) const
{
   return( 200 );
}

unsigned long dsi_DSTC0420_VW::getDefinedByteLength( void ) const
{
   return( 530 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0420_VW::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0420_VW::fieldExists( id );
}

bool dsi_DSTC0420_VW::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40006504: return( true );
      case 40006518: return( true );
      case 40006519: return( true );
      case 40006520: return( true );
      case 40006521: return( true );
      case 40000679: return( true );
      case 40006506: return( true );
      case 40006522: return( true );
      case 40006508: return( true );
   }
   return false;
}

