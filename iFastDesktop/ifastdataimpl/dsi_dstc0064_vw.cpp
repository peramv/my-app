// BFDataImpl implementation file for DataSet DSTC0064.VW
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0064_vw.h"


// This function creates an instance of dsi_DSTC0064_VW
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0064_VW() { return new dsi_DSTC0064_VW; }

dsi_DSTC0064_VW::dsi_DSTC0064_VW()
: BFDataImpl( 40000757, 40000758 )
, MoreAvailable_( ifds::MoreAvailable, &ifds::s_FldProp_MoreAvailable )
, NextKey_( ifds::NextKey, &ifds::s_FldProp_NextKey )
, ShrGrpAccessAll_( ifds::ShrGrpAccessAll, &ifds::s_FldProp_ShrGrpAccessAll )
, IDAccess_( ifds::IDAccess, &ifds::s_FldProp_IDAccess )
, AccessAllSlsRep_( ifds::AccessAllSlsRep, &ifds::s_FldProp_AccessAllSlsRep )
, RepeatCount_( ifds::RepeatCount, &ifds::s_FldProp_RepeatCount )
{
   cFields_ = 6;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0064_VW::~dsi_DSTC0064_VW()
{
}

BFDataImpl* dsi_DSTC0064_VW::clone()
{
   dsi_DSTC0064_VW* p = new dsi_DSTC0064_VW;
   p->MoreAvailable_ = MoreAvailable_;
   p->NextKey_ = NextKey_;
   p->ShrGrpAccessAll_ = ShrGrpAccessAll_;
   p->IDAccess_ = IDAccess_;
   p->AccessAllSlsRep_ = AccessAllSlsRep_;
   p->RepeatCount_ = RepeatCount_;
   return(p);
}

BFDataField* dsi_DSTC0064_VW::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40000126: return ( &MoreAvailable_ ); break; // MoreAvailable
      case 40000029: return ( &NextKey_ ); break; // NextKey
      case 40005432: return ( &ShrGrpAccessAll_ ); break; // ShrGrpAccessAll
      case 40004535: return ( &IDAccess_ ); break; // IDAccess
      case 40001834: return ( &AccessAllSlsRep_ ); break; // AccessAllSlsRep
      case 40000120: return ( &RepeatCount_ ); break; // RepeatCount
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0064_VW::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0064_VW* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0064_VW::getElementByIndex( unsigned int iField )
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
            case 2: aFlds_[2] = &ShrGrpAccessAll_; break;
            case 3: aFlds_[3] = &IDAccess_; break;
            case 4: aFlds_[4] = &AccessAllSlsRep_; break;
            case 5: aFlds_[5] = &RepeatCount_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0064_VW::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0064_VW* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0064_VW::getLargestDefinedField( void ) const
{
   return( 100 );
}

unsigned long dsi_DSTC0064_VW::getDefinedByteLength( void ) const
{
   return( 178 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0064_VW::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0064_VW::fieldExists( id );
}

bool dsi_DSTC0064_VW::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40000126: return( true );
      case 40000029: return( true );
      case 40005432: return( true );
      case 40004535: return( true );
      case 40001834: return( true );
      case 40000120: return( true );
   }
   return false;
}

