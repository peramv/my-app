// BFDataImpl implementation file for DataSet DSTC0039.VW
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:58 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0039_vw.h"


// This function creates an instance of dsi_DSTC0039_VW
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0039_VW() { return new dsi_DSTC0039_VW; }

dsi_DSTC0039_VW::dsi_DSTC0039_VW()
: BFDataImpl( 40000537 )
, ValidPasswd_( ifds::ValidPasswd, &ifds::s_FldProp_ValidPasswd )
{
   cFields_ = 1;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0039_VW::~dsi_DSTC0039_VW()
{
}

BFDataImpl* dsi_DSTC0039_VW::clone()
{
   dsi_DSTC0039_VW* p = new dsi_DSTC0039_VW;
   p->ValidPasswd_ = ValidPasswd_;
   return(p);
}

BFDataField* dsi_DSTC0039_VW::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40000538: return ( &ValidPasswd_ ); break; // ValidPasswd
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0039_VW::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0039_VW* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0039_VW::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 1 )
   {
      BFDataField* pField = aFlds_[iField];
      if( NULL == pField )
      {
         switch(iField)
         {
            case 0: aFlds_[0] = &ValidPasswd_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0039_VW::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0039_VW* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0039_VW::getLargestDefinedField( void ) const
{
   return( 1 );
}

unsigned long dsi_DSTC0039_VW::getDefinedByteLength( void ) const
{
   return( 1 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0039_VW::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0039_VW::fieldExists( id );
}

bool dsi_DSTC0039_VW::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40000538: return( true );
   }
   return false;
}

