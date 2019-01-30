// BFDataImpl implementation file for DataSet DSTC0143.VW
// ViewsGenerator: This file was generated by ViewsGenerator - Version 1.0.0.0
// ViewsGenerator: Generated on : Friday, January 18, 2019 14:49:33


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0143_vw.h"


// This function creates an instance of dsi_DSTC0143_VW
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0143_VW() { return new dsi_DSTC0143_VW; }

dsi_DSTC0143_VW::dsi_DSTC0143_VW()
: BFDataImpl( 40001905 )
, CurrLIPSetup_( ifds::CurrLIPSetup, &ifds::s_FldProp_CurrLIPSetup )
, MaxPensionEarning_( ifds::MaxPensionEarning, &ifds::s_FldProp_MaxPensionEarning )
, AmountOver_( ifds::AmountOver, &ifds::s_FldProp_AmountOver )
, UnitHeld_( ifds::UnitHeld, &ifds::s_FldProp_UnitHeld )
, FeeDfnExist_( ifds::FeeDfnExist, &ifds::s_FldProp_FeeDfnExist )
, MaxRedFee_( ifds::MaxRedFee, &ifds::s_FldProp_MaxRedFee )
, LLPValMsg_( ifds::LLPValMsg, &ifds::s_FldProp_LLPValMsg )
, TransExist_( ifds::TransExist, &ifds::s_FldProp_TransExist )
, MinWithAgeErr1_( ifds::MinWithAgeErr1, &ifds::s_FldProp_MinWithAgeErr1 )
, MinWithAgeErr2_( ifds::MinWithAgeErr2, &ifds::s_FldProp_MinWithAgeErr2 )
, PenInfoErr_( ifds::PenInfoErr, &ifds::s_FldProp_PenInfoErr )
, TaxTypeRulErr_( ifds::TaxTypeRulErr, &ifds::s_FldProp_TaxTypeRulErr )
, AmtSysCalc_( ifds::AmtSysCalc, &ifds::s_FldProp_AmtSysCalc )
, RRIFDetlErr_( ifds::RRIFDetlErr, &ifds::s_FldProp_RRIFDetlErr )
, LowRemainBal_( ifds::LowRemainBal, &ifds::s_FldProp_LowRemainBal )
, RemAmtPayFirst_( ifds::RemAmtPayFirst, &ifds::s_FldProp_RemAmtPayFirst )
, AmntOverMax_( ifds::AmntOverMax, &ifds::s_FldProp_AmntOverMax )
, EurCurrMstr_( ifds::EurCurrMstr, &ifds::s_FldProp_EurCurrMstr )
, RedCodesErr_( ifds::RedCodesErr, &ifds::s_FldProp_RedCodesErr )
, FundExist_( ifds::FundExist, &ifds::s_FldProp_FundExist )
, FundUnits_( ifds::FundUnits, &ifds::s_FldProp_FundUnits )
, ProvRate_( ifds::ProvRate, &ifds::s_FldProp_ProvRate )
, FedRate_( ifds::FedRate, &ifds::s_FldProp_FedRate )
, LSIFUnitsAvail_( ifds::LSIFUnitsAvail, &ifds::s_FldProp_LSIFUnitsAvail )
, AmtOverMin_( ifds::AmtOverMin, &ifds::s_FldProp_AmtOverMin )
, GrossNetType_( ifds::GrossNetType, &ifds::s_FldProp_GrossNetType )
{
    cFields_ = 26;
    memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0143_VW::~dsi_DSTC0143_VW()
{
}

BFDataImpl* dsi_DSTC0143_VW::clone()
{
    dsi_DSTC0143_VW* p = new dsi_DSTC0143_VW;
    p->CurrLIPSetup_ = CurrLIPSetup_;
    p->MaxPensionEarning_ = MaxPensionEarning_;
    p->AmountOver_ = AmountOver_;
    p->UnitHeld_ = UnitHeld_;
    p->FeeDfnExist_ = FeeDfnExist_;
    p->MaxRedFee_ = MaxRedFee_;
    p->LLPValMsg_ = LLPValMsg_;
    p->TransExist_ = TransExist_;
    p->MinWithAgeErr1_ = MinWithAgeErr1_;
    p->MinWithAgeErr2_ = MinWithAgeErr2_;
    p->PenInfoErr_ = PenInfoErr_;
    p->TaxTypeRulErr_ = TaxTypeRulErr_;
    p->AmtSysCalc_ = AmtSysCalc_;
    p->RRIFDetlErr_ = RRIFDetlErr_;
    p->LowRemainBal_ = LowRemainBal_;
    p->RemAmtPayFirst_ = RemAmtPayFirst_;
    p->AmntOverMax_ = AmntOverMax_;
    p->EurCurrMstr_ = EurCurrMstr_;
    p->RedCodesErr_ = RedCodesErr_;
    p->FundExist_ = FundExist_;
    p->FundUnits_ = FundUnits_;
    p->ProvRate_ = ProvRate_;
    p->FedRate_ = FedRate_;
    p->LSIFUnitsAvail_ = LSIFUnitsAvail_;
    p->AmtOverMin_ = AmtOverMin_;
    p->GrossNetType_ = GrossNetType_;
    return(p);
}

BFDataField* dsi_DSTC0143_VW::getElement( const BFFieldId& id )
{
    switch( id.getId() ) {
        case 40001909: return ( &CurrLIPSetup_ ); break; // CurrLIPSetup
        case 40001908: return ( &MaxPensionEarning_ ); break; // MaxPensionEarning
        case 40001910: return ( &AmountOver_ ); break; // AmountOver
        case 40001941: return ( &UnitHeld_ ); break; // UnitHeld
        case 40001962: return ( &FeeDfnExist_ ); break; // FeeDfnExist
        case 40001964: return ( &MaxRedFee_ ); break; // MaxRedFee
        case 40001966: return ( &LLPValMsg_ ); break; // LLPValMsg
        case 40001967: return ( &TransExist_ ); break; // TransExist
        case 40001968: return ( &MinWithAgeErr1_ ); break; // MinWithAgeErr1
        case 40001969: return ( &MinWithAgeErr2_ ); break; // MinWithAgeErr2
        case 40001970: return ( &PenInfoErr_ ); break; // PenInfoErr
        case 40001971: return ( &TaxTypeRulErr_ ); break; // TaxTypeRulErr
        case 40001972: return ( &AmtSysCalc_ ); break; // AmtSysCalc
        case 40001974: return ( &RRIFDetlErr_ ); break; // RRIFDetlErr
        case 40001975: return ( &LowRemainBal_ ); break; // LowRemainBal
        case 40001976: return ( &RemAmtPayFirst_ ); break; // RemAmtPayFirst
        case 40001977: return ( &AmntOverMax_ ); break; // AmntOverMax
        case 40002138: return ( &EurCurrMstr_ ); break; // EurCurrMstr
        case 40001973: return ( &RedCodesErr_ ); break; // RedCodesErr
        case 40001938: return ( &FundExist_ ); break; // FundExist
        case 40001611: return ( &FundUnits_ ); break; // FundUnits
        case 40000846: return ( &ProvRate_ ); break; // ProvRate
        case 40000844: return ( &FedRate_ ); break; // FedRate
        case 40004529: return ( &LSIFUnitsAvail_ ); break; // LSIFUnitsAvail
        case 40005974: return ( &AmtOverMin_ ); break; // AmtOverMin
        case 40007945: return ( &GrossNetType_ ); break; // GrossNetType
    }
    return( NULL );
}

const BFDataField* dsi_DSTC0143_VW::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0143_VW* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0143_VW::getElementByIndex( unsigned int iField )
{
    if ( iField >=0 && iField < 26 )
    {
        BFDataField* pField = aFlds_[iField];
        if( NULL == pField )
        {
            switch(iField)
            {
                case 0: aFlds_[0] = &CurrLIPSetup_; break;
                case 1: aFlds_[1] = &MaxPensionEarning_; break;
                case 2: aFlds_[2] = &AmountOver_; break;
                case 3: aFlds_[3] = &UnitHeld_; break;
                case 4: aFlds_[4] = &FeeDfnExist_; break;
                case 5: aFlds_[5] = &MaxRedFee_; break;
                case 6: aFlds_[6] = &LLPValMsg_; break;
                case 7: aFlds_[7] = &TransExist_; break;
                case 8: aFlds_[8] = &MinWithAgeErr1_; break;
                case 9: aFlds_[9] = &MinWithAgeErr2_; break;
                case 10: aFlds_[10] = &PenInfoErr_; break;
                case 11: aFlds_[11] = &TaxTypeRulErr_; break;
                case 12: aFlds_[12] = &AmtSysCalc_; break;
                case 13: aFlds_[13] = &RRIFDetlErr_; break;
                case 14: aFlds_[14] = &LowRemainBal_; break;
                case 15: aFlds_[15] = &RemAmtPayFirst_; break;
                case 16: aFlds_[16] = &AmntOverMax_; break;
                case 17: aFlds_[17] = &EurCurrMstr_; break;
                case 18: aFlds_[18] = &RedCodesErr_; break;
                case 19: aFlds_[19] = &FundExist_; break;
                case 20: aFlds_[20] = &FundUnits_; break;
                case 21: aFlds_[21] = &ProvRate_; break;
                case 22: aFlds_[22] = &FedRate_; break;
                case 23: aFlds_[23] = &LSIFUnitsAvail_; break;
                case 24: aFlds_[24] = &AmtOverMin_; break;
                case 25: aFlds_[25] = &GrossNetType_; break;
            }
            pField = aFlds_[iField];
            if( NULL == pField ) return( NULL );
        }
        return( pField );
    }
    return( NULL );
}

const BFDataField* dsi_DSTC0143_VW::getElementByIndex( unsigned int iField ) const
{
    return( ( const_cast< dsi_DSTC0143_VW* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0143_VW::getLargestDefinedField( void ) const
{
    return( 60 );
}

unsigned long dsi_DSTC0143_VW::getDefinedByteLength( void ) const
{
    return( 308 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0143_VW::exists( const BFFieldId& id ) const
{
    return dsi_DSTC0143_VW::fieldExists( id );
}

bool dsi_DSTC0143_VW::fieldExists( const BFFieldId& id )
{
    switch( id.getId() )
    {
        case 40001909: return ( true );
        case 40001908: return ( true );
        case 40001910: return ( true );
        case 40001941: return ( true );
        case 40001962: return ( true );
        case 40001964: return ( true );
        case 40001966: return ( true );
        case 40001967: return ( true );
        case 40001968: return ( true );
        case 40001969: return ( true );
        case 40001970: return ( true );
        case 40001971: return ( true );
        case 40001972: return ( true );
        case 40001974: return ( true );
        case 40001975: return ( true );
        case 40001976: return ( true );
        case 40001977: return ( true );
        case 40002138: return ( true );
        case 40001973: return ( true );
        case 40001938: return ( true );
        case 40001611: return ( true );
        case 40000846: return ( true );
        case 40000844: return ( true );
        case 40004529: return ( true );
        case 40005974: return ( true );
        case 40007945: return ( true );
    }
    return false;
}

