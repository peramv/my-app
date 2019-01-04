// BFDataImpl implementation file for DataSet DSTC0474.REQRepeat_Record
// ViewsGenerator: This file was generated by ViewsGenerator - Version 1.0.0.0
// ViewsGenerator: Generated on : Friday, November 04, 2016 12:10:01


#include "stdafx.h"
#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0474_reqrepeat_record.h"


// This function creates an instance of dsi_DSTC0474_REQRepeat_Record
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0474_REQRepeat_Record() { return new dsi_DSTC0474_REQRepeat_Record; }

dsi_DSTC0474_REQRepeat_Record::dsi_DSTC0474_REQRepeat_Record()
: BFDataImpl( 40007692 )
, AllocRunMode_( ifds::AllocRunMode, &ifds::s_FldProp_AllocRunMode )
, RegTransferAllocUUID_( ifds::RegTransferAllocUUID, &ifds::s_FldProp_RegTransferAllocUUID )
, FundCode_( ifds::FundCode, &ifds::s_FldProp_FundCode )
, ClassCode_( ifds::ClassCode, &ifds::s_FldProp_ClassCode )
, AllocAmount_( ifds::AllocAmount, &ifds::s_FldProp_AllocAmount )
, Version_( ifds::Version, &ifds::s_FldProp_Version )
, Commission_( ifds::Commission, &ifds::s_FldProp_Commission )
{
    cFields_ = 7;
    memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0474_REQRepeat_Record::~dsi_DSTC0474_REQRepeat_Record()
{
}

BFDataImpl* dsi_DSTC0474_REQRepeat_Record::clone()
{
    dsi_DSTC0474_REQRepeat_Record* p = new dsi_DSTC0474_REQRepeat_Record;
    p->AllocRunMode_ = AllocRunMode_;
    p->RegTransferAllocUUID_ = RegTransferAllocUUID_;
    p->FundCode_ = FundCode_;
    p->ClassCode_ = ClassCode_;
    p->AllocAmount_ = AllocAmount_;
    p->Version_ = Version_;
    p->Commission_ = Commission_;
    return(p);
}

BFDataField* dsi_DSTC0474_REQRepeat_Record::getElement( const BFFieldId& id )
{
    switch( id.getId() ) {
        case 40001032: return ( &AllocRunMode_ ); break; // AllocRunMode
        case 40007685: return ( &RegTransferAllocUUID_ ); break; // RegTransferAllocUUID
        case 40000049: return ( &FundCode_ ); break; // FundCode
        case 40000050: return ( &ClassCode_ ); break; // ClassCode
        case 40000292: return ( &AllocAmount_ ); break; // AllocAmount
        case 40003739: return ( &Version_ ); break; // Version
        case 40000441: return ( &Commission_ ); break; // Commission
    }
    return( NULL );
}

const BFDataField* dsi_DSTC0474_REQRepeat_Record::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0474_REQRepeat_Record* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0474_REQRepeat_Record::getElementByIndex( unsigned int iField )
{
    if ( iField >=0 && iField < 7 )
    {
        BFDataField* pField = aFlds_[iField];
        if( NULL == pField )
        {
            switch(iField)
            {
                case 0: aFlds_[0] = &AllocRunMode_; break;
                case 1: aFlds_[1] = &RegTransferAllocUUID_; break;
                case 2: aFlds_[2] = &FundCode_; break;
                case 3: aFlds_[3] = &ClassCode_; break;
                case 4: aFlds_[4] = &AllocAmount_; break;
                case 5: aFlds_[5] = &Version_; break;
                case 6: aFlds_[6] = &Commission_; break;
            }
            pField = aFlds_[iField];
            if( NULL == pField ) return( NULL );
        }
        return( pField );
    }
    return( NULL );
}

const BFDataField* dsi_DSTC0474_REQRepeat_Record::getElementByIndex( unsigned int iField ) const
{
    return( ( const_cast< dsi_DSTC0474_REQRepeat_Record* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0474_REQRepeat_Record::getLargestDefinedField( void ) const
{
    return( 200 );
}

unsigned long dsi_DSTC0474_REQRepeat_Record::getDefinedByteLength( void ) const
{
    return( 498 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0474_REQRepeat_Record::exists( const BFFieldId& id ) const
{
    return dsi_DSTC0474_REQRepeat_Record::fieldExists( id );
}

bool dsi_DSTC0474_REQRepeat_Record::fieldExists( const BFFieldId& id )
{
    switch( id.getId() )
    {
        case 40001032: return ( true );
        case 40007685: return ( true );
        case 40000049: return ( true );
        case 40000050: return ( true );
        case 40000292: return ( true );
        case 40003739: return ( true );
        case 40000441: return ( true );
    }
    return false;
}

