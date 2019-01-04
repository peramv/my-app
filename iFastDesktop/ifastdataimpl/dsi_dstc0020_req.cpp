// BFDataImpl implementation file for DataSet DSTC0020.REQ
// ViewsGenerator: This file was generated by ViewsGenerator - Version 1.0.0.0
// ViewsGenerator: Generated on : Thursday, September 17, 2015 09:44:44


#include "stdafx.h"
#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0020_req.h"


// This function creates an instance of dsi_DSTC0020_REQ
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0020_REQ() { return new dsi_DSTC0020_REQ; }

dsi_DSTC0020_REQ::dsi_DSTC0020_REQ()
: BFDataImpl( 40000060 )
, AccountNum_( ifds::AccountNum, &ifds::s_FldProp_AccountNum )
, AsofDate_( ifds::AsofDate, &ifds::s_FldProp_AsofDate )
, NextKey_( ifds::NextKey, &ifds::s_FldProp_NextKey )
, SessionId_( ifds::SessionId, &ifds::s_FldProp_SessionId )
, User_Id_( ifds::User_Id, &ifds::s_FldProp_User_Id )
, LanguageCode_( ifds::LanguageCode, &ifds::s_FldProp_LanguageCode )
, CompanyId_( ifds::CompanyId, &ifds::s_FldProp_CompanyId )
, Track_( ifds::Track, &ifds::s_FldProp_Track )
, Activity_( ifds::Activity, &ifds::s_FldProp_Activity )
, OverrideRepeats_( ifds::OverrideRepeats, &ifds::s_FldProp_OverrideRepeats )
, CalculateACB_( ifds::CalculateACB, &ifds::s_FldProp_CalculateACB )
, ActiveOnly_( ifds::ActiveOnly, &ifds::s_FldProp_ActiveOnly )
, FundCode_( ifds::FundCode, &ifds::s_FldProp_FundCode )
, ClassCode_( ifds::ClassCode, &ifds::s_FldProp_ClassCode )
, ReportingCurrency_( ifds::ReportingCurrency, &ifds::s_FldProp_ReportingCurrency )
, ConvertAmount_( ifds::ConvertAmount, &ifds::s_FldProp_ConvertAmount )
, AccBalMode_( ifds::AccBalMode, &ifds::s_FldProp_AccBalMode )
, TotalOnly_( ifds::TotalOnly, &ifds::s_FldProp_TotalOnly )
{
    cFields_ = 18;
    memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0020_REQ::~dsi_DSTC0020_REQ()
{
}

BFDataImpl* dsi_DSTC0020_REQ::clone()
{
    dsi_DSTC0020_REQ* p = new dsi_DSTC0020_REQ;
    p->AccountNum_ = AccountNum_;
    p->AsofDate_ = AsofDate_;
    p->NextKey_ = NextKey_;
    p->SessionId_ = SessionId_;
    p->User_Id_ = User_Id_;
    p->LanguageCode_ = LanguageCode_;
    p->CompanyId_ = CompanyId_;
    p->Track_ = Track_;
    p->Activity_ = Activity_;
    p->OverrideRepeats_ = OverrideRepeats_;
    p->CalculateACB_ = CalculateACB_;
    p->ActiveOnly_ = ActiveOnly_;
    p->FundCode_ = FundCode_;
    p->ClassCode_ = ClassCode_;
    p->ReportingCurrency_ = ReportingCurrency_;
    p->ConvertAmount_ = ConvertAmount_;
    p->AccBalMode_ = AccBalMode_;
    p->TotalOnly_ = TotalOnly_;
    return(p);
}

BFDataField* dsi_DSTC0020_REQ::getElement( const BFFieldId& id )
{
    switch( id.getId() ) {
        case 40000040: return ( &AccountNum_ ); break; // AccountNum
        case 40000061: return ( &AsofDate_ ); break; // AsofDate
        case 40000029: return ( &NextKey_ ); break; // NextKey
        case 40000005: return ( &SessionId_ ); break; // SessionId
        case 40000002: return ( &User_Id_ ); break; // User_Id
        case 40000030: return ( &LanguageCode_ ); break; // LanguageCode
        case 40000031: return ( &CompanyId_ ); break; // CompanyId
        case 40002065: return ( &Track_ ); break; // Track
        case 40002066: return ( &Activity_ ); break; // Activity
        case 40002139: return ( &OverrideRepeats_ ); break; // OverrideRepeats
        case 40002848: return ( &CalculateACB_ ); break; // CalculateACB
        case 40004452: return ( &ActiveOnly_ ); break; // ActiveOnly
        case 40000049: return ( &FundCode_ ); break; // FundCode
        case 40000050: return ( &ClassCode_ ); break; // ClassCode
        case 40005406: return ( &ReportingCurrency_ ); break; // ReportingCurrency
        case 40005587: return ( &ConvertAmount_ ); break; // ConvertAmount
        case 40007380: return ( &AccBalMode_ ); break; // AccBalMode
        case 40007574: return ( &TotalOnly_ ); break; // TotalOnly
    }
    return( NULL );
}

const BFDataField* dsi_DSTC0020_REQ::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0020_REQ* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0020_REQ::getElementByIndex( unsigned int iField )
{
    if ( iField >=0 && iField < 18 )
    {
        BFDataField* pField = aFlds_[iField];
        if( NULL == pField )
        {
            switch(iField)
            {
                case 0: aFlds_[0] = &AccountNum_; break;
                case 1: aFlds_[1] = &AsofDate_; break;
                case 2: aFlds_[2] = &NextKey_; break;
                case 3: aFlds_[3] = &SessionId_; break;
                case 4: aFlds_[4] = &User_Id_; break;
                case 5: aFlds_[5] = &LanguageCode_; break;
                case 6: aFlds_[6] = &CompanyId_; break;
                case 7: aFlds_[7] = &Track_; break;
                case 8: aFlds_[8] = &Activity_; break;
                case 9: aFlds_[9] = &OverrideRepeats_; break;
                case 10: aFlds_[10] = &CalculateACB_; break;
                case 11: aFlds_[11] = &ActiveOnly_; break;
                case 12: aFlds_[12] = &FundCode_; break;
                case 13: aFlds_[13] = &ClassCode_; break;
                case 14: aFlds_[14] = &ReportingCurrency_; break;
                case 15: aFlds_[15] = &ConvertAmount_; break;
                case 16: aFlds_[16] = &AccBalMode_; break;
                case 17: aFlds_[17] = &TotalOnly_; break;
            }
            pField = aFlds_[iField];
            if( NULL == pField ) return( NULL );
        }
        return( pField );
    }
    return( NULL );
}

const BFDataField* dsi_DSTC0020_REQ::getElementByIndex( unsigned int iField ) const
{
    return( ( const_cast< dsi_DSTC0020_REQ* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0020_REQ::getLargestDefinedField( void ) const
{
    return( 200 );
}

unsigned long dsi_DSTC0020_REQ::getDefinedByteLength( void ) const
{
    return( 876 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0020_REQ::exists( const BFFieldId& id ) const
{
    return dsi_DSTC0020_REQ::fieldExists( id );
}

bool dsi_DSTC0020_REQ::fieldExists( const BFFieldId& id )
{
    switch( id.getId() )
    {
        case 40000040: return ( true );
        case 40000061: return ( true );
        case 40000029: return ( true );
        case 40000005: return ( true );
        case 40000002: return ( true );
        case 40000030: return ( true );
        case 40000031: return ( true );
        case 40002065: return ( true );
        case 40002066: return ( true );
        case 40002139: return ( true );
        case 40002848: return ( true );
        case 40004452: return ( true );
        case 40000049: return ( true );
        case 40000050: return ( true );
        case 40005406: return ( true );
        case 40005587: return ( true );
        case 40007380: return ( true );
        case 40007574: return ( true );
    }
    return false;
}

