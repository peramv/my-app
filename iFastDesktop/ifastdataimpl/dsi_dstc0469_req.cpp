// BFDataImpl implementation file for DataSet DSTC0469.REQ
// ViewsGenerator: This file was generated by ViewsGenerator - Version 1.0.0.0
// ViewsGenerator: Generated on : Monday, September 21, 2015 10:01:51


#include "stdafx.h"
#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0469_req.h"


// This function creates an instance of dsi_DSTC0469_REQ
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0469_REQ() { return new dsi_DSTC0469_REQ; }

dsi_DSTC0469_REQ::dsi_DSTC0469_REQ()
: BFDataImpl( 40007576 )
, SessionId_( ifds::SessionId, &ifds::s_FldProp_SessionId )
, User_Id_( ifds::User_Id, &ifds::s_FldProp_User_Id )
, LanguageCode_( ifds::LanguageCode, &ifds::s_FldProp_LanguageCode )
, CompanyId_( ifds::CompanyId, &ifds::s_FldProp_CompanyId )
, Track_( ifds::Track, &ifds::s_FldProp_Track )
, Activity_( ifds::Activity, &ifds::s_FldProp_Activity )
, AccountNum_( ifds::AccountNum, &ifds::s_FldProp_AccountNum )
, Fund_( ifds::Fund, &ifds::s_FldProp_Fund )
, Date_( ifds::Date, &ifds::s_FldProp_Date )
, RegulatoryStandard_( ifds::RegulatoryStandard, &ifds::s_FldProp_RegulatoryStandard )
, TransType_( ifds::TransType, &ifds::s_FldProp_TransType )
{
    cFields_ = 11;
    memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0469_REQ::~dsi_DSTC0469_REQ()
{
}

BFDataImpl* dsi_DSTC0469_REQ::clone()
{
    dsi_DSTC0469_REQ* p = new dsi_DSTC0469_REQ;
    p->SessionId_ = SessionId_;
    p->User_Id_ = User_Id_;
    p->LanguageCode_ = LanguageCode_;
    p->CompanyId_ = CompanyId_;
    p->Track_ = Track_;
    p->Activity_ = Activity_;
    p->AccountNum_ = AccountNum_;
    p->Fund_ = Fund_;
    p->Date_ = Date_;
    p->RegulatoryStandard_ = RegulatoryStandard_;
    p->TransType_ = TransType_;
    return(p);
}

BFDataField* dsi_DSTC0469_REQ::getElement( const BFFieldId& id )
{
    switch( id.getId() ) {
        case 40000005: return ( &SessionId_ ); break; // SessionId
        case 40000002: return ( &User_Id_ ); break; // User_Id
        case 40000030: return ( &LanguageCode_ ); break; // LanguageCode
        case 40000031: return ( &CompanyId_ ); break; // CompanyId
        case 40002065: return ( &Track_ ); break; // Track
        case 40002066: return ( &Activity_ ); break; // Activity
        case 40000040: return ( &AccountNum_ ); break; // AccountNum
        case 40002227: return ( &Fund_ ); break; // Fund
        case 40003528: return ( &Date_ ); break; // Date
        case 40005798: return ( &RegulatoryStandard_ ); break; // RegulatoryStandard
        case 40000095: return ( &TransType_ ); break; // TransType
    }
    return( NULL );
}

const BFDataField* dsi_DSTC0469_REQ::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0469_REQ* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0469_REQ::getElementByIndex( unsigned int iField )
{
    if ( iField >=0 && iField < 11 )
    {
        BFDataField* pField = aFlds_[iField];
        if( NULL == pField )
        {
            switch(iField)
            {
                case 0: aFlds_[0] = &SessionId_; break;
                case 1: aFlds_[1] = &User_Id_; break;
                case 2: aFlds_[2] = &LanguageCode_; break;
                case 3: aFlds_[3] = &CompanyId_; break;
                case 4: aFlds_[4] = &Track_; break;
                case 5: aFlds_[5] = &Activity_; break;
                case 6: aFlds_[6] = &AccountNum_; break;
                case 7: aFlds_[7] = &Fund_; break;
                case 8: aFlds_[8] = &Date_; break;
                case 9: aFlds_[9] = &RegulatoryStandard_; break;
                case 10: aFlds_[10] = &TransType_; break;
            }
            pField = aFlds_[iField];
            if( NULL == pField ) return( NULL );
        }
        return( pField );
    }
    return( NULL );
}

const BFDataField* dsi_DSTC0469_REQ::getElementByIndex( unsigned int iField ) const
{
    return( ( const_cast< dsi_DSTC0469_REQ* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0469_REQ::getLargestDefinedField( void ) const
{
    return( 60 );
}

unsigned long dsi_DSTC0469_REQ::getDefinedByteLength( void ) const
{
    return( 508 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0469_REQ::exists( const BFFieldId& id ) const
{
    return dsi_DSTC0469_REQ::fieldExists( id );
}

bool dsi_DSTC0469_REQ::fieldExists( const BFFieldId& id )
{
    switch( id.getId() )
    {
        case 40000005: return ( true );
        case 40000002: return ( true );
        case 40000030: return ( true );
        case 40000031: return ( true );
        case 40002065: return ( true );
        case 40002066: return ( true );
        case 40000040: return ( true );
        case 40002227: return ( true );
        case 40003528: return ( true );
        case 40005798: return ( true );
        case 40000095: return ( true );
    }
    return false;
}

