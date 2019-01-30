// BFDataImpl implementation file for DataSet DSTC0051.VW
// ViewsGenerator: This file was generated by ViewsGenerator - Version 1.0.0.0
// ViewsGenerator: Generated on : Friday, September 28, 2018 12:19:52


#include "stdafx.h"
#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0051_vw.h"


// This function creates an instance of dsi_DSTC0051_VW
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0051_VW() { return new dsi_DSTC0051_VW; }

dsi_DSTC0051_VW::dsi_DSTC0051_VW()
: BFDataImpl( 40000622, 40000632 )
, Salutation_( ifds::Salutation, &ifds::s_FldProp_Salutation )
, LastName_( ifds::LastName, &ifds::s_FldProp_LastName )
, FirstName_( ifds::FirstName, &ifds::s_FldProp_FirstName )
, BirthLastName_( ifds::BirthLastName, &ifds::s_FldProp_BirthLastName )
, BirthFirstName_( ifds::BirthFirstName, &ifds::s_FldProp_BirthFirstName )
, DofBirth_( ifds::DofBirth, &ifds::s_FldProp_DofBirth )
, Gender_( ifds::Gender, &ifds::s_FldProp_Gender )
, SIN_( ifds::SIN, &ifds::s_FldProp_SIN )
, OccupationCode_( ifds::OccupationCode, &ifds::s_FldProp_OccupationCode )
, OccupationDesc_( ifds::OccupationDesc, &ifds::s_FldProp_OccupationDesc )
, LanguageCode_( ifds::LanguageCode, &ifds::s_FldProp_LanguageCode )
, Language_( ifds::Language, &ifds::s_FldProp_Language )
, HomePhone_( ifds::HomePhone, &ifds::s_FldProp_HomePhone )
, BusinessPhone_( ifds::BusinessPhone, &ifds::s_FldProp_BusinessPhone )
, BusinessExt_( ifds::BusinessExt, &ifds::s_FldProp_BusinessExt )
, BusinessFax_( ifds::BusinessFax, &ifds::s_FldProp_BusinessFax )
, Telex_( ifds::Telex, &ifds::s_FldProp_Telex )
, Email_( ifds::Email, &ifds::s_FldProp_Email )
, DofDeath_( ifds::DofDeath, &ifds::s_FldProp_DofDeath )
, DofDeathNotice_( ifds::DofDeathNotice, &ifds::s_FldProp_DofDeathNotice )
, EffectiveDate_( ifds::EffectiveDate, &ifds::s_FldProp_EffectiveDate )
, ProcessDate_( ifds::ProcessDate, &ifds::s_FldProp_ProcessDate )
, ModDate_( ifds::ModDate, &ifds::s_FldProp_ModDate )
, Username_( ifds::Username, &ifds::s_FldProp_Username )
, ModUser_( ifds::ModUser, &ifds::s_FldProp_ModUser )
, HomeFax_( ifds::HomeFax, &ifds::s_FldProp_HomeFax )
, EntityIdentityVer_( ifds::EntityIdentityVer, &ifds::s_FldProp_EntityIdentityVer )
, EntityIdentityRid_( ifds::EntityIdentityRid, &ifds::s_FldProp_EntityIdentityRid )
, HomePhoneCntry_( ifds::HomePhoneCntry, &ifds::s_FldProp_HomePhoneCntry )
, HomePhoneArea_( ifds::HomePhoneArea, &ifds::s_FldProp_HomePhoneArea )
, BusinessPhoneCntry_( ifds::BusinessPhoneCntry, &ifds::s_FldProp_BusinessPhoneCntry )
, BusinessPhoneArea_( ifds::BusinessPhoneArea, &ifds::s_FldProp_BusinessPhoneArea )
, HomeFaxCntry_( ifds::HomeFaxCntry, &ifds::s_FldProp_HomeFaxCntry )
, HomeFaxArea_( ifds::HomeFaxArea, &ifds::s_FldProp_HomeFaxArea )
, BusFaxCntry_( ifds::BusFaxCntry, &ifds::s_FldProp_BusFaxCntry )
, BusFaxArea_( ifds::BusFaxArea, &ifds::s_FldProp_BusFaxArea )
, EmployeeClass_( ifds::EmployeeClass, &ifds::s_FldProp_EmployeeClass )
, Nationality_( ifds::Nationality, &ifds::s_FldProp_Nationality )
, OtherOccupation_( ifds::OtherOccupation, &ifds::s_FldProp_OtherOccupation )
, SpouseEntityID_( ifds::SpouseEntityID, &ifds::s_FldProp_SpouseEntityID )
, BirthPlace_( ifds::BirthPlace, &ifds::s_FldProp_BirthPlace )
, RiskLevel_( ifds::RiskLevel, &ifds::s_FldProp_RiskLevel )
, TaxJurisDeff_( ifds::TaxJurisDeff, &ifds::s_FldProp_TaxJurisDeff )
, TaxJuris_( ifds::TaxJuris, &ifds::s_FldProp_TaxJuris )
, EUSDTaxOption_( ifds::EUSDTaxOption, &ifds::s_FldProp_EUSDTaxOption )
, WhereUse_( ifds::WhereUse, &ifds::s_FldProp_WhereUse )
, GoodBad_( ifds::GoodBad, &ifds::s_FldProp_GoodBad )
, CountryOfBirth_( ifds::CountryOfBirth, &ifds::s_FldProp_CountryOfBirth )
, ContactName_( ifds::ContactName, &ifds::s_FldProp_ContactName )
, Email2_( ifds::Email2, &ifds::s_FldProp_Email2 )
, SecondPhoneNum_( ifds::SecondPhoneNum, &ifds::s_FldProp_SecondPhoneNum )
, SecondPhoneNumExt_( ifds::SecondPhoneNumExt, &ifds::s_FldProp_SecondPhoneNumExt )
, FATCAFFI_( ifds::FATCAFFI, &ifds::s_FldProp_FATCAFFI )
, CountryOfExposure_( ifds::CountryOfExposure, &ifds::s_FldProp_CountryOfExposure )
, VerifyStatDetails_( ifds::VerifyStatDetails, &ifds::s_FldProp_VerifyStatDetails )
, RepeatCount_( ifds::RepeatCount, &ifds::s_FldProp_RepeatCount )
{
    cFields_ = 56;
    memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0051_VW::~dsi_DSTC0051_VW()
{
}

BFDataImpl* dsi_DSTC0051_VW::clone()
{
    dsi_DSTC0051_VW* p = new dsi_DSTC0051_VW;
    p->Salutation_ = Salutation_;
    p->LastName_ = LastName_;
    p->FirstName_ = FirstName_;
    p->BirthLastName_ = BirthLastName_;
    p->BirthFirstName_ = BirthFirstName_;
    p->DofBirth_ = DofBirth_;
    p->Gender_ = Gender_;
    p->SIN_ = SIN_;
    p->OccupationCode_ = OccupationCode_;
    p->OccupationDesc_ = OccupationDesc_;
    p->LanguageCode_ = LanguageCode_;
    p->Language_ = Language_;
    p->HomePhone_ = HomePhone_;
    p->BusinessPhone_ = BusinessPhone_;
    p->BusinessExt_ = BusinessExt_;
    p->BusinessFax_ = BusinessFax_;
    p->Telex_ = Telex_;
    p->Email_ = Email_;
    p->DofDeath_ = DofDeath_;
    p->DofDeathNotice_ = DofDeathNotice_;
    p->EffectiveDate_ = EffectiveDate_;
    p->ProcessDate_ = ProcessDate_;
    p->ModDate_ = ModDate_;
    p->Username_ = Username_;
    p->ModUser_ = ModUser_;
    p->HomeFax_ = HomeFax_;
    p->EntityIdentityVer_ = EntityIdentityVer_;
    p->EntityIdentityRid_ = EntityIdentityRid_;
    p->HomePhoneCntry_ = HomePhoneCntry_;
    p->HomePhoneArea_ = HomePhoneArea_;
    p->BusinessPhoneCntry_ = BusinessPhoneCntry_;
    p->BusinessPhoneArea_ = BusinessPhoneArea_;
    p->HomeFaxCntry_ = HomeFaxCntry_;
    p->HomeFaxArea_ = HomeFaxArea_;
    p->BusFaxCntry_ = BusFaxCntry_;
    p->BusFaxArea_ = BusFaxArea_;
    p->EmployeeClass_ = EmployeeClass_;
    p->Nationality_ = Nationality_;
    p->OtherOccupation_ = OtherOccupation_;
    p->SpouseEntityID_ = SpouseEntityID_;
    p->BirthPlace_ = BirthPlace_;
    p->RiskLevel_ = RiskLevel_;
    p->TaxJurisDeff_ = TaxJurisDeff_;
    p->TaxJuris_ = TaxJuris_;
    p->EUSDTaxOption_ = EUSDTaxOption_;
    p->WhereUse_ = WhereUse_;
    p->GoodBad_ = GoodBad_;
    p->CountryOfBirth_ = CountryOfBirth_;
    p->ContactName_ = ContactName_;
    p->Email2_ = Email2_;
    p->SecondPhoneNum_ = SecondPhoneNum_;
    p->SecondPhoneNumExt_ = SecondPhoneNumExt_;
    p->FATCAFFI_ = FATCAFFI_;
    p->CountryOfExposure_ = CountryOfExposure_;
    p->VerifyStatDetails_ = VerifyStatDetails_;
    p->RepeatCount_ = RepeatCount_;
    return(p);
}

BFDataField* dsi_DSTC0051_VW::getElement( const BFFieldId& id )
{
    switch( id.getId() ) {
        case 40000416: return ( &Salutation_ ); break; // Salutation
        case 40000128: return ( &LastName_ ); break; // LastName
        case 40000129: return ( &FirstName_ ); break; // FirstName
        case 40000130: return ( &BirthLastName_ ); break; // BirthLastName
        case 40000131: return ( &BirthFirstName_ ); break; // BirthFirstName
        case 40000623: return ( &DofBirth_ ); break; // DofBirth
        case 40000301: return ( &Gender_ ); break; // Gender
        case 40000132: return ( &SIN_ ); break; // SIN
        case 40000308: return ( &OccupationCode_ ); break; // OccupationCode
        case 40000309: return ( &OccupationDesc_ ); break; // OccupationDesc
        case 40000030: return ( &LanguageCode_ ); break; // LanguageCode
        case 40000624: return ( &Language_ ); break; // Language
        case 40000136: return ( &HomePhone_ ); break; // HomePhone
        case 40000625: return ( &BusinessPhone_ ); break; // BusinessPhone
        case 40000626: return ( &BusinessExt_ ); break; // BusinessExt
        case 40000627: return ( &BusinessFax_ ); break; // BusinessFax
        case 40000628: return ( &Telex_ ); break; // Telex
        case 40000629: return ( &Email_ ); break; // Email
        case 40000630: return ( &DofDeath_ ); break; // DofDeath
        case 40000631: return ( &DofDeathNotice_ ); break; // DofDeathNotice
        case 40000327: return ( &EffectiveDate_ ); break; // EffectiveDate
        case 40000216: return ( &ProcessDate_ ); break; // ProcessDate
        case 40000217: return ( &ModDate_ ); break; // ModDate
        case 40000117: return ( &Username_ ); break; // Username
        case 40000218: return ( &ModUser_ ); break; // ModUser
        case 40000873: return ( &HomeFax_ ); break; // HomeFax
        case 40001019: return ( &EntityIdentityVer_ ); break; // EntityIdentityVer
        case 40001020: return ( &EntityIdentityRid_ ); break; // EntityIdentityRid
        case 40002014: return ( &HomePhoneCntry_ ); break; // HomePhoneCntry
        case 40002017: return ( &HomePhoneArea_ ); break; // HomePhoneArea
        case 40002018: return ( &BusinessPhoneCntry_ ); break; // BusinessPhoneCntry
        case 40002019: return ( &BusinessPhoneArea_ ); break; // BusinessPhoneArea
        case 40002020: return ( &HomeFaxCntry_ ); break; // HomeFaxCntry
        case 40002021: return ( &HomeFaxArea_ ); break; // HomeFaxArea
        case 40002022: return ( &BusFaxCntry_ ); break; // BusFaxCntry
        case 40002023: return ( &BusFaxArea_ ); break; // BusFaxArea
        case 40003040: return ( &EmployeeClass_ ); break; // EmployeeClass
        case 40003800: return ( &Nationality_ ); break; // Nationality
        case 40004106: return ( &OtherOccupation_ ); break; // OtherOccupation
        case 40004139: return ( &SpouseEntityID_ ); break; // SpouseEntityID
        case 40004304: return ( &BirthPlace_ ); break; // BirthPlace
        case 40004435: return ( &RiskLevel_ ); break; // RiskLevel
        case 40004986: return ( &TaxJurisDeff_ ); break; // TaxJurisDeff
        case 40004447: return ( &TaxJuris_ ); break; // TaxJuris
        case 40004987: return ( &EUSDTaxOption_ ); break; // EUSDTaxOption
        case 40004727: return ( &WhereUse_ ); break; // WhereUse
        case 40000496: return ( &GoodBad_ ); break; // GoodBad
        case 40005348: return ( &CountryOfBirth_ ); break; // CountryOfBirth
        case 40005349: return ( &ContactName_ ); break; // ContactName
        case 40005650: return ( &Email2_ ); break; // Email2
        case 40005651: return ( &SecondPhoneNum_ ); break; // SecondPhoneNum
        case 40005652: return ( &SecondPhoneNumExt_ ); break; // SecondPhoneNumExt
        case 40006947: return ( &FATCAFFI_ ); break; // FATCAFFI
        case 40007577: return ( &CountryOfExposure_ ); break; // CountryOfExposure
        case 40007934: return ( &VerifyStatDetails_ ); break; // VerifyStatDetails
        case 40000120: return ( &RepeatCount_ ); break; // RepeatCount
    }
    return( NULL );
}

const BFDataField* dsi_DSTC0051_VW::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0051_VW* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0051_VW::getElementByIndex( unsigned int iField )
{
    if ( iField >=0 && iField < 56 )
    {
        BFDataField* pField = aFlds_[iField];
        if( NULL == pField )
        {
            switch(iField)
            {
                case 0: aFlds_[0] = &Salutation_; break;
                case 1: aFlds_[1] = &LastName_; break;
                case 2: aFlds_[2] = &FirstName_; break;
                case 3: aFlds_[3] = &BirthLastName_; break;
                case 4: aFlds_[4] = &BirthFirstName_; break;
                case 5: aFlds_[5] = &DofBirth_; break;
                case 6: aFlds_[6] = &Gender_; break;
                case 7: aFlds_[7] = &SIN_; break;
                case 8: aFlds_[8] = &OccupationCode_; break;
                case 9: aFlds_[9] = &OccupationDesc_; break;
                case 10: aFlds_[10] = &LanguageCode_; break;
                case 11: aFlds_[11] = &Language_; break;
                case 12: aFlds_[12] = &HomePhone_; break;
                case 13: aFlds_[13] = &BusinessPhone_; break;
                case 14: aFlds_[14] = &BusinessExt_; break;
                case 15: aFlds_[15] = &BusinessFax_; break;
                case 16: aFlds_[16] = &Telex_; break;
                case 17: aFlds_[17] = &Email_; break;
                case 18: aFlds_[18] = &DofDeath_; break;
                case 19: aFlds_[19] = &DofDeathNotice_; break;
                case 20: aFlds_[20] = &EffectiveDate_; break;
                case 21: aFlds_[21] = &ProcessDate_; break;
                case 22: aFlds_[22] = &ModDate_; break;
                case 23: aFlds_[23] = &Username_; break;
                case 24: aFlds_[24] = &ModUser_; break;
                case 25: aFlds_[25] = &HomeFax_; break;
                case 26: aFlds_[26] = &EntityIdentityVer_; break;
                case 27: aFlds_[27] = &EntityIdentityRid_; break;
                case 28: aFlds_[28] = &HomePhoneCntry_; break;
                case 29: aFlds_[29] = &HomePhoneArea_; break;
                case 30: aFlds_[30] = &BusinessPhoneCntry_; break;
                case 31: aFlds_[31] = &BusinessPhoneArea_; break;
                case 32: aFlds_[32] = &HomeFaxCntry_; break;
                case 33: aFlds_[33] = &HomeFaxArea_; break;
                case 34: aFlds_[34] = &BusFaxCntry_; break;
                case 35: aFlds_[35] = &BusFaxArea_; break;
                case 36: aFlds_[36] = &EmployeeClass_; break;
                case 37: aFlds_[37] = &Nationality_; break;
                case 38: aFlds_[38] = &OtherOccupation_; break;
                case 39: aFlds_[39] = &SpouseEntityID_; break;
                case 40: aFlds_[40] = &BirthPlace_; break;
                case 41: aFlds_[41] = &RiskLevel_; break;
                case 42: aFlds_[42] = &TaxJurisDeff_; break;
                case 43: aFlds_[43] = &TaxJuris_; break;
                case 44: aFlds_[44] = &EUSDTaxOption_; break;
                case 45: aFlds_[45] = &WhereUse_; break;
                case 46: aFlds_[46] = &GoodBad_; break;
                case 47: aFlds_[47] = &CountryOfBirth_; break;
                case 48: aFlds_[48] = &ContactName_; break;
                case 49: aFlds_[49] = &Email2_; break;
                case 50: aFlds_[50] = &SecondPhoneNum_; break;
                case 51: aFlds_[51] = &SecondPhoneNumExt_; break;
                case 52: aFlds_[52] = &FATCAFFI_; break;
                case 53: aFlds_[53] = &CountryOfExposure_; break;
            	case 54: aFlds_[54] = &VerifyStatDetails_; break;
            	case 55: aFlds_[55] = &RepeatCount_; break;
            }
            pField = aFlds_[iField];
            if( NULL == pField ) return( NULL );
        }
        return( pField );
    }
    return( NULL );
}

const BFDataField* dsi_DSTC0051_VW::getElementByIndex( unsigned int iField ) const
{
    return( ( const_cast< dsi_DSTC0051_VW* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0051_VW::getLargestDefinedField( void ) const
{
    return( 80 );
}

unsigned long dsi_DSTC0051_VW::getDefinedByteLength( void ) const
{
    return( 2570 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0051_VW::exists( const BFFieldId& id ) const
{
    return dsi_DSTC0051_VW::fieldExists( id );
}

bool dsi_DSTC0051_VW::fieldExists( const BFFieldId& id )
{
    switch( id.getId() )
    {
        case 40000416: return ( true );
        case 40000128: return ( true );
        case 40000129: return ( true );
        case 40000130: return ( true );
        case 40000131: return ( true );
        case 40000623: return ( true );
        case 40000301: return ( true );
        case 40000132: return ( true );
        case 40000308: return ( true );
        case 40000309: return ( true );
        case 40000030: return ( true );
        case 40000624: return ( true );
        case 40000136: return ( true );
        case 40000625: return ( true );
        case 40000626: return ( true );
        case 40000627: return ( true );
        case 40000628: return ( true );
        case 40000629: return ( true );
        case 40000630: return ( true );
        case 40000631: return ( true );
        case 40000327: return ( true );
        case 40000216: return ( true );
        case 40000217: return ( true );
        case 40000117: return ( true );
        case 40000218: return ( true );
        case 40000873: return ( true );
        case 40001019: return ( true );
        case 40001020: return ( true );
        case 40002014: return ( true );
        case 40002017: return ( true );
        case 40002018: return ( true );
        case 40002019: return ( true );
        case 40002020: return ( true );
        case 40002021: return ( true );
        case 40002022: return ( true );
        case 40002023: return ( true );
        case 40003040: return ( true );
        case 40003800: return ( true );
        case 40004106: return ( true );
        case 40004139: return ( true );
        case 40004304: return ( true );
        case 40004435: return ( true );
        case 40004986: return ( true );
        case 40004447: return ( true );
        case 40004987: return ( true );
        case 40004727: return ( true );
        case 40000496: return ( true );
        case 40005348: return ( true );
        case 40005349: return ( true );
        case 40005650: return ( true );
        case 40005651: return ( true );
        case 40005652: return ( true );
        case 40006947: return ( true );
        case 40007577: return ( true );
        case 40007934: return ( true );
        case 40000120: return ( true );
    }
    return false;
}

