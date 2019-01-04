// BFDataImpl implementation file for DataSet DSTC0078.VW
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0078_vw.h"


// This function creates an instance of dsi_DSTC0078_VW
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0078_VW() { return new dsi_DSTC0078_VW; }

dsi_DSTC0078_VW::dsi_DSTC0078_VW()
: BFDataImpl( 40001110 )
, UpdateStatus_( ifds::UpdateStatus, &ifds::s_FldProp_UpdateStatus )
{
   cFields_ = 1;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0078_VW::~dsi_DSTC0078_VW()
{
}

BFDataImpl* dsi_DSTC0078_VW::clone()
{
   dsi_DSTC0078_VW* p = new dsi_DSTC0078_VW;
   p->UpdateStatus_ = UpdateStatus_;
   return(p);
}

BFDataField* dsi_DSTC0078_VW::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40000989: return ( &UpdateStatus_ ); break; // UpdateStatus
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0078_VW::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0078_VW* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0078_VW::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 1 )
   {
      BFDataField* pField = aFlds_[iField];
      if( NULL == pField )
      {
         switch(iField)
         {
            case 0: aFlds_[0] = &UpdateStatus_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0078_VW::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0078_VW* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0078_VW::getLargestDefinedField( void ) const
{
   return( 1 );
}

unsigned long dsi_DSTC0078_VW::getDefinedByteLength( void ) const
{
   return( 1 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0078_VW::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0078_VW::fieldExists( id );
}

bool dsi_DSTC0078_VW::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40000989: return( true );
   }
   return false;
}

