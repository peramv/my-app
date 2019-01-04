// BFDataImpl implementation file for DataSet DSTC0483.VWRepeat_Record
// ViewsGenerator: This file was generated by ViewsGenerator - Version 1.0.0.0
// ViewsGenerator: Generated on : Friday, January 19, 2018 07:16:59


#include "stdafx.h"
#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0483_vwrepeat_record.h"


// This function creates an instance of dsi_DSTC0483_VWRepeat_Record
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0483_VWRepeat_Record() { return new dsi_DSTC0483_VWRepeat_Record; }

dsi_DSTC0483_VWRepeat_Record::dsi_DSTC0483_VWRepeat_Record()
: BFDataImpl( 40007855 )
, FundCode_( ifds::FundCode, &ifds::s_FldProp_FundCode )
, ClassCode_( ifds::ClassCode, &ifds::s_FldProp_ClassCode )
, AMSAllocDelta_( ifds::AMSAllocDelta, &ifds::s_FldProp_AMSAllocDelta )
, AMSDeltaDetlUUID_( ifds::AMSDeltaDetlUUID, &ifds::s_FldProp_AMSDeltaDetlUUID )
, Version_( ifds::Version, &ifds::s_FldProp_Version )
, ProcessDate_( ifds::ProcessDate, &ifds::s_FldProp_ProcessDate )
, Username_( ifds::Username, &ifds::s_FldProp_Username )
, ModDate_( ifds::ModDate, &ifds::s_FldProp_ModDate )
, ModUser_( ifds::ModUser, &ifds::s_FldProp_ModUser )
{
    cFields_ = 9;
    memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0483_VWRepeat_Record::~dsi_DSTC0483_VWRepeat_Record()
{
}

BFDataImpl* dsi_DSTC0483_VWRepeat_Record::clone()
{
    dsi_DSTC0483_VWRepeat_Record* p = new dsi_DSTC0483_VWRepeat_Record;
    p->FundCode_ = FundCode_;
    p->ClassCode_ = ClassCode_;
    p->AMSAllocDelta_ = AMSAllocDelta_;
    p->AMSDeltaDetlUUID_ = AMSDeltaDetlUUID_;
    p->Version_ = Version_;
    p->ProcessDate_ = ProcessDate_;
    p->Username_ = Username_;
    p->ModDate_ = ModDate_;
    p->ModUser_ = ModUser_;
    return(p);
}

BFDataField* dsi_DSTC0483_VWRepeat_Record::getElement( const BFFieldId& id )
{
    switch( id.getId() ) {
        case 40000049: return ( &FundCode_ ); break; // FundCode
        case 40000050: return ( &ClassCode_ ); break; // ClassCode
        case 40007853: return ( &AMSAllocDelta_ ); break; // AMSAllocDelta
        case 40007854: return ( &AMSDeltaDetlUUID_ ); break; // AMSDeltaDetlUUID
        case 40003739: return ( &Version_ ); break; // Version
        case 40000216: return ( &ProcessDate_ ); break; // ProcessDate
        case 40000117: return ( &Username_ ); break; // Username
        case 40000217: return ( &ModDate_ ); break; // ModDate
        case 40000218: return ( &ModUser_ ); break; // ModUser
    }
    return( NULL );
}

const BFDataField* dsi_DSTC0483_VWRepeat_Record::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0483_VWRepeat_Record* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0483_VWRepeat_Record::getElementByIndex( unsigned int iField )
{
    if ( iField >=0 && iField < 9 )
    {
        BFDataField* pField = aFlds_[iField];
        if( NULL == pField )
        {
            switch(iField)
            {
                case 0: aFlds_[0] = &FundCode_; break;
                case 1: aFlds_[1] = &ClassCode_; break;
                case 2: aFlds_[2] = &AMSAllocDelta_; break;
                case 3: aFlds_[3] = &AMSDeltaDetlUUID_; break;
                case 4: aFlds_[4] = &Version_; break;
                case 5: aFlds_[5] = &ProcessDate_; break;
                case 6: aFlds_[6] = &Username_; break;
                case 7: aFlds_[7] = &ModDate_; break;
                case 8: aFlds_[8] = &ModUser_; break;
            }
            pField = aFlds_[iField];
            if( NULL == pField ) return( NULL );
        }
        return( pField );
    }
    return( NULL );
}

const BFDataField* dsi_DSTC0483_VWRepeat_Record::getElementByIndex( unsigned int iField ) const
{
    return( ( const_cast< dsi_DSTC0483_VWRepeat_Record* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0483_VWRepeat_Record::getLargestDefinedField( void ) const
{
    return( 200 );
}

unsigned long dsi_DSTC0483_VWRepeat_Record::getDefinedByteLength( void ) const
{
    return( 565 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0483_VWRepeat_Record::exists( const BFFieldId& id ) const
{
    return dsi_DSTC0483_VWRepeat_Record::fieldExists( id );
}

bool dsi_DSTC0483_VWRepeat_Record::fieldExists( const BFFieldId& id )
{
    switch( id.getId() )
    {
        case 40000049: return ( true );
        case 40000050: return ( true );
        case 40007853: return ( true );
        case 40007854: return ( true );
        case 40003739: return ( true );
        case 40000216: return ( true );
        case 40000117: return ( true );
        case 40000217: return ( true );
        case 40000218: return ( true );
    }
    return false;
}

