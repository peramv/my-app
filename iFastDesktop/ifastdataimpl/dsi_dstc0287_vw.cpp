// BFDataImpl implementation file for DataSet DSTC0287.VW
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0287_vw.h"


// This function creates an instance of dsi_DSTC0287_VW
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0287_VW() { return new dsi_DSTC0287_VW; }

dsi_DSTC0287_VW::dsi_DSTC0287_VW()
: BFDataImpl( 40004391, 40004393 )
, MoreAvailable_( ifds::MoreAvailable, &ifds::s_FldProp_MoreAvailable )
, NextKey_( ifds::NextKey, &ifds::s_FldProp_NextKey )
, UnitsTotal_( ifds::UnitsTotal, &ifds::s_FldProp_UnitsTotal )
, TotalCBFFreeUnits_( ifds::TotalCBFFreeUnits, &ifds::s_FldProp_TotalCBFFreeUnits )
, Grp1Shares_( ifds::Grp1Shares, &ifds::s_FldProp_Grp1Shares )
, Grp2Shares_( ifds::Grp2Shares, &ifds::s_FldProp_Grp2Shares )
, RepeatCount_( ifds::RepeatCount, &ifds::s_FldProp_RepeatCount )
{
   cFields_ = 7;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0287_VW::~dsi_DSTC0287_VW()
{
}

BFDataImpl* dsi_DSTC0287_VW::clone()
{
   dsi_DSTC0287_VW* p = new dsi_DSTC0287_VW;
   p->MoreAvailable_ = MoreAvailable_;
   p->NextKey_ = NextKey_;
   p->UnitsTotal_ = UnitsTotal_;
   p->TotalCBFFreeUnits_ = TotalCBFFreeUnits_;
   p->Grp1Shares_ = Grp1Shares_;
   p->Grp2Shares_ = Grp2Shares_;
   p->RepeatCount_ = RepeatCount_;
   return(p);
}

BFDataField* dsi_DSTC0287_VW::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40000126: return ( &MoreAvailable_ ); break; // MoreAvailable
      case 40000029: return ( &NextKey_ ); break; // NextKey
      case 40004401: return ( &UnitsTotal_ ); break; // UnitsTotal
      case 40004448: return ( &TotalCBFFreeUnits_ ); break; // TotalCBFFreeUnits
      case 40002821: return ( &Grp1Shares_ ); break; // Grp1Shares
      case 40002825: return ( &Grp2Shares_ ); break; // Grp2Shares
      case 40000120: return ( &RepeatCount_ ); break; // RepeatCount
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0287_VW::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0287_VW* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0287_VW::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 7 )
   {
      BFDataField* pField = aFlds_[iField];
      if( NULL == pField )
      {
         switch(iField)
         {
            case 0: aFlds_[0] = &MoreAvailable_; break;
            case 1: aFlds_[1] = &NextKey_; break;
            case 2: aFlds_[2] = &UnitsTotal_; break;
            case 3: aFlds_[3] = &TotalCBFFreeUnits_; break;
            case 4: aFlds_[4] = &Grp1Shares_; break;
            case 5: aFlds_[5] = &Grp2Shares_; break;
            case 6: aFlds_[6] = &RepeatCount_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0287_VW::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0287_VW* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0287_VW::getLargestDefinedField( void ) const
{
   return( 100 );
}

unsigned long dsi_DSTC0287_VW::getDefinedByteLength( void ) const
{
   return( 207 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0287_VW::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0287_VW::fieldExists( id );
}

bool dsi_DSTC0287_VW::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40000126: return( true );
      case 40000029: return( true );
      case 40004401: return( true );
      case 40004448: return( true );
      case 40002821: return( true );
      case 40002825: return( true );
      case 40000120: return( true );
   }
   return false;
}

