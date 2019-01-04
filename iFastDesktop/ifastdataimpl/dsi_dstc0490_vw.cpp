// BFDataImpl implementation file for DataSet DSTC0490.VW
// ViewsGenerator: This file was generated by ViewsGenerator - Version 1.0.0.0
// ViewsGenerator: Generated on : Friday, November 09, 2018 10:44:05


#include "stdafx.h"
#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0490_vw.h"


// This function creates an instance of dsi_DSTC0490_VW
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0490_VW() { return new dsi_DSTC0490_VW; }

dsi_DSTC0490_VW::dsi_DSTC0490_VW()
: BFDataImpl( 40007927 )
, ErrorCode_( ifds::ErrorCode, &ifds::s_FldProp_ErrorCode )
, ErrorDesc_( ifds::ErrorDesc, &ifds::s_FldProp_ErrorDesc )
, EWI_( ifds::EWI, &ifds::s_FldProp_EWI )
{
    cFields_ = 3;
    memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0490_VW::~dsi_DSTC0490_VW()
{
}

BFDataImpl* dsi_DSTC0490_VW::clone()
{
    dsi_DSTC0490_VW* p = new dsi_DSTC0490_VW;
    p->ErrorCode_ = ErrorCode_;
    p->ErrorDesc_ = ErrorDesc_;
    p->EWI_ = EWI_;
    return(p);
}

BFDataField* dsi_DSTC0490_VW::getElement( const BFFieldId& id )
{
    switch( id.getId() ) {
        case 40000586: return ( &ErrorCode_ ); break; // ErrorCode
        case 40000587: return ( &ErrorDesc_ ); break; // ErrorDesc
        case 40001802: return ( &EWI_ ); break; // EWI
    }
    return( NULL );
}

const BFDataField* dsi_DSTC0490_VW::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0490_VW* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0490_VW::getElementByIndex( unsigned int iField )
{
    if ( iField >=0 && iField < 3 )
    {
        BFDataField* pField = aFlds_[iField];
        if( NULL == pField )
        {
            switch(iField)
            {
                case 0: aFlds_[0] = &ErrorCode_; break;
                case 1: aFlds_[1] = &ErrorDesc_; break;
                case 2: aFlds_[2] = &EWI_; break;
            }
            pField = aFlds_[iField];
            if( NULL == pField ) return( NULL );
        }
        return( pField );
    }
    return( NULL );
}

const BFDataField* dsi_DSTC0490_VW::getElementByIndex( unsigned int iField ) const
{
    return( ( const_cast< dsi_DSTC0490_VW* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0490_VW::getLargestDefinedField( void ) const
{
    return( 60 );
}

unsigned long dsi_DSTC0490_VW::getDefinedByteLength( void ) const
{
    return( 130 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0490_VW::exists( const BFFieldId& id ) const
{
    return dsi_DSTC0490_VW::fieldExists( id );
}

bool dsi_DSTC0490_VW::fieldExists( const BFFieldId& id )
{
    switch( id.getId() )
    {
        case 40000586: return ( true );
        case 40000587: return ( true );
        case 40001802: return ( true );
    }
    return false;
}

