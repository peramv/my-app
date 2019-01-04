// BFDataImpl implementation file for DataSet DSTC0471.VWRepeat_Record
// ViewsGenerator: This file was generated by ViewsGenerator - Version 1.0.0.0
// ViewsGenerator: Generated on : Friday, June 17, 2016 00:59:41


#include "stdafx.h"
#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0471_vwrepeat_record.h"


// This function creates an instance of dsi_DSTC0471_VWRepeat_Record
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0471_VWRepeat_Record() { return new dsi_DSTC0471_VWRepeat_Record; }

dsi_DSTC0471_VWRepeat_Record::dsi_DSTC0471_VWRepeat_Record()
: BFDataImpl( 40007632 )
, FundRuleType_( ifds::FundRuleType, &ifds::s_FldProp_FundRuleType )
, FundRuleLevel_( ifds::FundRuleLevel, &ifds::s_FldProp_FundRuleLevel )
, FundGroupCode_( ifds::FundGroupCode, &ifds::s_FldProp_FundGroupCode )
, FundCode_( ifds::FundCode, &ifds::s_FldProp_FundCode )
, ClassCode_( ifds::ClassCode, &ifds::s_FldProp_ClassCode )
, StartDate_( ifds::StartDate, &ifds::s_FldProp_StartDate )
, StopDate_( ifds::StopDate, &ifds::s_FldProp_StopDate )
{
    cFields_ = 7;
    memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0471_VWRepeat_Record::~dsi_DSTC0471_VWRepeat_Record()
{
}

BFDataImpl* dsi_DSTC0471_VWRepeat_Record::clone()
{
    dsi_DSTC0471_VWRepeat_Record* p = new dsi_DSTC0471_VWRepeat_Record;
    p->FundRuleType_ = FundRuleType_;
    p->FundRuleLevel_ = FundRuleLevel_;
    p->FundGroupCode_ = FundGroupCode_;
    p->FundCode_ = FundCode_;
    p->ClassCode_ = ClassCode_;
    p->StartDate_ = StartDate_;
    p->StopDate_ = StopDate_;
    return(p);
}

BFDataField* dsi_DSTC0471_VWRepeat_Record::getElement( const BFFieldId& id )
{
    switch( id.getId() ) {
        case 40007625: return ( &FundRuleType_ ); break; // FundRuleType
        case 40007626: return ( &FundRuleLevel_ ); break; // FundRuleLevel
        case 40001479: return ( &FundGroupCode_ ); break; // FundGroupCode
        case 40000049: return ( &FundCode_ ); break; // FundCode
        case 40000050: return ( &ClassCode_ ); break; // ClassCode
        case 40000107: return ( &StartDate_ ); break; // StartDate
        case 40000279: return ( &StopDate_ ); break; // StopDate
    }
    return( NULL );
}

const BFDataField* dsi_DSTC0471_VWRepeat_Record::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0471_VWRepeat_Record* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0471_VWRepeat_Record::getElementByIndex( unsigned int iField )
{
    if ( iField >=0 && iField < 7 )
    {
        BFDataField* pField = aFlds_[iField];
        if( NULL == pField )
        {
            switch(iField)
            {
                case 0: aFlds_[0] = &FundRuleType_; break;
                case 1: aFlds_[1] = &FundRuleLevel_; break;
                case 2: aFlds_[2] = &FundGroupCode_; break;
                case 3: aFlds_[3] = &FundCode_; break;
                case 4: aFlds_[4] = &ClassCode_; break;
                case 5: aFlds_[5] = &StartDate_; break;
                case 6: aFlds_[6] = &StopDate_; break;
            }
            pField = aFlds_[iField];
            if( NULL == pField ) return( NULL );
        }
        return( pField );
    }
    return( NULL );
}

const BFDataField* dsi_DSTC0471_VWRepeat_Record::getElementByIndex( unsigned int iField ) const
{
    return( ( const_cast< dsi_DSTC0471_VWRepeat_Record* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0471_VWRepeat_Record::getLargestDefinedField( void ) const
{
    return( 200 );
}

unsigned long dsi_DSTC0471_VWRepeat_Record::getDefinedByteLength( void ) const
{
    return( 520 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0471_VWRepeat_Record::exists( const BFFieldId& id ) const
{
    return dsi_DSTC0471_VWRepeat_Record::fieldExists( id );
}

bool dsi_DSTC0471_VWRepeat_Record::fieldExists( const BFFieldId& id )
{
    switch( id.getId() )
    {
        case 40007625: return ( true );
        case 40007626: return ( true );
        case 40001479: return ( true );
        case 40000049: return ( true );
        case 40000050: return ( true );
        case 40000107: return ( true );
        case 40000279: return ( true );
    }
    return false;
}

