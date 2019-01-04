// BFDataImpl implementation file for DataSet DSTC0059.VW
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0059_vw.h"


// This function creates an instance of dsi_DSTC0059_VW
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0059_VW() { return new dsi_DSTC0059_VW; }

dsi_DSTC0059_VW::dsi_DSTC0059_VW()
: BFDataImpl( 40000716, 40000717 )
, MoreAvailable_( ifds::MoreAvailable, &ifds::s_FldProp_MoreAvailable )
, RepeatCount_( ifds::RepeatCount, &ifds::s_FldProp_RepeatCount )
{
   cFields_ = 2;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0059_VW::~dsi_DSTC0059_VW()
{
}

BFDataImpl* dsi_DSTC0059_VW::clone()
{
   dsi_DSTC0059_VW* p = new dsi_DSTC0059_VW;
   p->MoreAvailable_ = MoreAvailable_;
   p->RepeatCount_ = RepeatCount_;
   return(p);
}

BFDataField* dsi_DSTC0059_VW::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40000126: return ( &MoreAvailable_ ); break; // MoreAvailable
      case 40000120: return ( &RepeatCount_ ); break; // RepeatCount
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0059_VW::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0059_VW* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0059_VW::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 2 )
   {
      BFDataField* pField = aFlds_[iField];
      if( NULL == pField )
      {
         switch(iField)
         {
            case 0: aFlds_[0] = &MoreAvailable_; break;
            case 1: aFlds_[1] = &RepeatCount_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0059_VW::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0059_VW* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0059_VW::getLargestDefinedField( void ) const
{
   return( 15 );
}

unsigned long dsi_DSTC0059_VW::getDefinedByteLength( void ) const
{
   return( 16 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0059_VW::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0059_VW::fieldExists( id );
}

bool dsi_DSTC0059_VW::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40000126: return( true );
      case 40000120: return( true );
   }
   return false;
}

