// BFDataImpl implementation file for DataSet DSTC0015.VW
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:58 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0015_vw.h"


// This function creates an instance of dsi_DSTC0015_VW
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0015_VW() { return new dsi_DSTC0015_VW; }

dsi_DSTC0015_VW::dsi_DSTC0015_VW()
: BFDataImpl( 40000329, 40000330 )
, MoreAvailable_( ifds::MoreAvailable, &ifds::s_FldProp_MoreAvailable )
, NextKey_( ifds::NextKey, &ifds::s_FldProp_NextKey )
, CurrencyName_( ifds::CurrencyName, &ifds::s_FldProp_CurrencyName )
, ACBPlugAmt_( ifds::ACBPlugAmt, &ifds::s_FldProp_ACBPlugAmt )
, ACBPlugDate_( ifds::ACBPlugDate, &ifds::s_FldProp_ACBPlugDate )
, RepeatCount_( ifds::RepeatCount, &ifds::s_FldProp_RepeatCount )
{
   cFields_ = 6;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0015_VW::~dsi_DSTC0015_VW()
{
}

BFDataImpl* dsi_DSTC0015_VW::clone()
{
   dsi_DSTC0015_VW* p = new dsi_DSTC0015_VW;
   p->MoreAvailable_ = MoreAvailable_;
   p->NextKey_ = NextKey_;
   p->CurrencyName_ = CurrencyName_;
   p->ACBPlugAmt_ = ACBPlugAmt_;
   p->ACBPlugDate_ = ACBPlugDate_;
   p->RepeatCount_ = RepeatCount_;
   return(p);
}

BFDataField* dsi_DSTC0015_VW::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40000126: return ( &MoreAvailable_ ); break; // MoreAvailable
      case 40000029: return ( &NextKey_ ); break; // NextKey
      case 40000181: return ( &CurrencyName_ ); break; // CurrencyName
      case 40007006: return ( &ACBPlugAmt_ ); break; // ACBPlugAmt
      case 40007007: return ( &ACBPlugDate_ ); break; // ACBPlugDate
      case 40000120: return ( &RepeatCount_ ); break; // RepeatCount
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0015_VW::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0015_VW* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0015_VW::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 6 )
   {
      BFDataField* pField = aFlds_[iField];
      if( NULL == pField )
      {
         switch(iField)
         {
            case 0: aFlds_[0] = &MoreAvailable_; break;
            case 1: aFlds_[1] = &NextKey_; break;
            case 2: aFlds_[2] = &CurrencyName_; break;
            case 3: aFlds_[3] = &ACBPlugAmt_; break;
            case 4: aFlds_[4] = &ACBPlugDate_; break;
            case 5: aFlds_[5] = &RepeatCount_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0015_VW::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0015_VW* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0015_VW::getLargestDefinedField( void ) const
{
   return( 100 );
}

unsigned long dsi_DSTC0015_VW::getDefinedByteLength( void ) const
{
   return( 206 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0015_VW::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0015_VW::fieldExists( id );
}

bool dsi_DSTC0015_VW::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40000126: return( true );
      case 40000029: return( true );
      case 40000181: return( true );
      case 40007006: return( true );
      case 40007007: return( true );
      case 40000120: return( true );
   }
   return false;
}

