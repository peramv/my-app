// BFDataImpl implementation file for DataSet DSTC0377.VW
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0377_vw.h"


// This function creates an instance of dsi_DSTC0377_VW
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0377_VW() { return new dsi_DSTC0377_VW; }

dsi_DSTC0377_VW::dsi_DSTC0377_VW()
: BFDataImpl( 40005559 )
, UpdateStatus_( ifds::UpdateStatus, &ifds::s_FldProp_UpdateStatus )
, ShrNum_( ifds::ShrNum, &ifds::s_FldProp_ShrNum )
, AccountNum_( ifds::AccountNum, &ifds::s_FldProp_AccountNum )
{
   cFields_ = 3;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0377_VW::~dsi_DSTC0377_VW()
{
}

BFDataImpl* dsi_DSTC0377_VW::clone()
{
   dsi_DSTC0377_VW* p = new dsi_DSTC0377_VW;
   p->UpdateStatus_ = UpdateStatus_;
   p->ShrNum_ = ShrNum_;
   p->AccountNum_ = AccountNum_;
   return(p);
}

BFDataField* dsi_DSTC0377_VW::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40000989: return ( &UpdateStatus_ ); break; // UpdateStatus
      case 40000114: return ( &ShrNum_ ); break; // ShrNum
      case 40000040: return ( &AccountNum_ ); break; // AccountNum
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0377_VW::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0377_VW* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0377_VW::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 3 )
   {
      BFDataField* pField = aFlds_[iField];
      if( NULL == pField )
      {
         switch(iField)
         {
            case 0: aFlds_[0] = &UpdateStatus_; break;
            case 1: aFlds_[1] = &ShrNum_; break;
            case 2: aFlds_[2] = &AccountNum_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0377_VW::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0377_VW* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0377_VW::getLargestDefinedField( void ) const
{
   return( 17 );
}

unsigned long dsi_DSTC0377_VW::getDefinedByteLength( void ) const
{
   return( 35 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0377_VW::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0377_VW::fieldExists( id );
}

bool dsi_DSTC0377_VW::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40000989: return( true );
      case 40000114: return( true );
      case 40000040: return( true );
   }
   return false;
}

