// BFDataImpl implementation file for DataSet DSTC0428.VWRepeat_Record
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0428_vwrepeat_record.h"


// This function creates an instance of dsi_DSTC0428_VWRepeat_Record
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0428_VWRepeat_Record() { return new dsi_DSTC0428_VWRepeat_Record; }

dsi_DSTC0428_VWRepeat_Record::dsi_DSTC0428_VWRepeat_Record()
: BFDataImpl( 40006568 )
, DistribDetlUUID_( ifds::DistribDetlUUID, &ifds::s_FldProp_DistribDetlUUID )
, IntInvestId_( ifds::IntInvestId, &ifds::s_FldProp_IntInvestId )
, RolloverType_( ifds::RolloverType, &ifds::s_FldProp_RolloverType )
, AccountTo_( ifds::AccountTo, &ifds::s_FldProp_AccountTo )
, FundTo_( ifds::FundTo, &ifds::s_FldProp_FundTo )
, ClassTo_( ifds::ClassTo, &ifds::s_FldProp_ClassTo )
, RemainingFleg_( ifds::RemainingFleg, &ifds::s_FldProp_RemainingFleg )
, Currency_( ifds::Currency, &ifds::s_FldProp_Currency )
, Percentage_( ifds::Percentage, &ifds::s_FldProp_Percentage )
, PayType_( ifds::PayType, &ifds::s_FldProp_PayType )
, PayTypeDesc_( ifds::PayTypeDesc, &ifds::s_FldProp_PayTypeDesc )
, CommReduction_( ifds::CommReduction, &ifds::s_FldProp_CommReduction )
, IntInvestType_( ifds::IntInvestType, &ifds::s_FldProp_IntInvestType )
, FELAmt_( ifds::FELAmt, &ifds::s_FldProp_FELAmt )
, IntInvestTerm_( ifds::IntInvestTerm, &ifds::s_FldProp_IntInvestTerm )
, IntCalcMthd_( ifds::IntCalcMthd, &ifds::s_FldProp_IntCalcMthd )
, ForcedRate_( ifds::ForcedRate, &ifds::s_FldProp_ForcedRate )
, ForcedRateAmt_( ifds::ForcedRateAmt, &ifds::s_FldProp_ForcedRateAmt )
, IntCredFreq_( ifds::IntCredFreq, &ifds::s_FldProp_IntCredFreq )
, BusinessType_( ifds::BusinessType, &ifds::s_FldProp_BusinessType )
, RefNum_( ifds::RefNum, &ifds::s_FldProp_RefNum )
, AddlAmt_( ifds::AddlAmt, &ifds::s_FldProp_AddlAmt )
, BankAcctId_( ifds::BankAcctId, &ifds::s_FldProp_BankAcctId )
, BankAcctUse_( ifds::BankAcctUse, &ifds::s_FldProp_BankAcctUse )
, BankIdType_( ifds::BankIdType, &ifds::s_FldProp_BankIdType )
, BankIdValue_( ifds::BankIdValue, &ifds::s_FldProp_BankIdValue )
, BankTransitNo_( ifds::BankTransitNo, &ifds::s_FldProp_BankTransitNo )
, BankSwiftCode_( ifds::BankSwiftCode, &ifds::s_FldProp_BankSwiftCode )
, BankRefNumber_( ifds::BankRefNumber, &ifds::s_FldProp_BankRefNumber )
, InstName_( ifds::InstName, &ifds::s_FldProp_InstName )
, BankAddr1_( ifds::BankAddr1, &ifds::s_FldProp_BankAddr1 )
, BankAddr2_( ifds::BankAddr2, &ifds::s_FldProp_BankAddr2 )
, BankAddr3_( ifds::BankAddr3, &ifds::s_FldProp_BankAddr3 )
, BankAddr4_( ifds::BankAddr4, &ifds::s_FldProp_BankAddr4 )
, BankAddr5_( ifds::BankAddr5, &ifds::s_FldProp_BankAddr5 )
, BankPostal_( ifds::BankPostal, &ifds::s_FldProp_BankPostal )
, BankCountry_( ifds::BankCountry, &ifds::s_FldProp_BankCountry )
, BankAcctType_( ifds::BankAcctType, &ifds::s_FldProp_BankAcctType )
, BankAcctTypeDesc_( ifds::BankAcctTypeDesc, &ifds::s_FldProp_BankAcctTypeDesc )
, BankAcctCurrency_( ifds::BankAcctCurrency, &ifds::s_FldProp_BankAcctCurrency )
, BankAcctCurrDesc_( ifds::BankAcctCurrDesc, &ifds::s_FldProp_BankAcctCurrDesc )
, BankEffectiveDate_( ifds::BankEffectiveDate, &ifds::s_FldProp_BankEffectiveDate )
, BankStopDate_( ifds::BankStopDate, &ifds::s_FldProp_BankStopDate )
, PayMethod_( ifds::PayMethod, &ifds::s_FldProp_PayMethod )
, ACHProcessor_( ifds::ACHProcessor, &ifds::s_FldProp_ACHProcessor )
, BankContact_( ifds::BankContact, &ifds::s_FldProp_BankContact )
, BankCorrespondent_( ifds::BankCorrespondent, &ifds::s_FldProp_BankCorrespondent )
, MatInstrAddrCode_( ifds::MatInstrAddrCode, &ifds::s_FldProp_MatInstrAddrCode )
, BankId_( ifds::BankId, &ifds::s_FldProp_BankId )
, BankAcctNum_( ifds::BankAcctNum, &ifds::s_FldProp_BankAcctNum )
, BankAcctName_( ifds::BankAcctName, &ifds::s_FldProp_BankAcctName )
, IntInvestUUID_( ifds::IntInvestUUID, &ifds::s_FldProp_IntInvestUUID )
, DistribDetlVersion_( ifds::DistribDetlVersion, &ifds::s_FldProp_DistribDetlVersion )
, BankAcctVersion_( ifds::BankAcctVersion, &ifds::s_FldProp_BankAcctVersion )
, IntInvestVer_( ifds::IntInvestVer, &ifds::s_FldProp_IntInvestVer )
{
   cFields_ = 55;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0428_VWRepeat_Record::~dsi_DSTC0428_VWRepeat_Record()
{
}

BFDataImpl* dsi_DSTC0428_VWRepeat_Record::clone()
{
   dsi_DSTC0428_VWRepeat_Record* p = new dsi_DSTC0428_VWRepeat_Record;
   p->DistribDetlUUID_ = DistribDetlUUID_;
   p->IntInvestId_ = IntInvestId_;
   p->RolloverType_ = RolloverType_;
   p->AccountTo_ = AccountTo_;
   p->FundTo_ = FundTo_;
   p->ClassTo_ = ClassTo_;
   p->RemainingFleg_ = RemainingFleg_;
   p->Currency_ = Currency_;
   p->Percentage_ = Percentage_;
   p->PayType_ = PayType_;
   p->PayTypeDesc_ = PayTypeDesc_;
   p->CommReduction_ = CommReduction_;
   p->IntInvestType_ = IntInvestType_;
   p->FELAmt_ = FELAmt_;
   p->IntInvestTerm_ = IntInvestTerm_;
   p->IntCalcMthd_ = IntCalcMthd_;
   p->ForcedRate_ = ForcedRate_;
   p->ForcedRateAmt_ = ForcedRateAmt_;
   p->IntCredFreq_ = IntCredFreq_;
   p->BusinessType_ = BusinessType_;
   p->RefNum_ = RefNum_;
   p->AddlAmt_ = AddlAmt_;
   p->BankAcctId_ = BankAcctId_;
   p->BankAcctUse_ = BankAcctUse_;
   p->BankIdType_ = BankIdType_;
   p->BankIdValue_ = BankIdValue_;
   p->BankTransitNo_ = BankTransitNo_;
   p->BankSwiftCode_ = BankSwiftCode_;
   p->BankRefNumber_ = BankRefNumber_;
   p->InstName_ = InstName_;
   p->BankAddr1_ = BankAddr1_;
   p->BankAddr2_ = BankAddr2_;
   p->BankAddr3_ = BankAddr3_;
   p->BankAddr4_ = BankAddr4_;
   p->BankAddr5_ = BankAddr5_;
   p->BankPostal_ = BankPostal_;
   p->BankCountry_ = BankCountry_;
   p->BankAcctType_ = BankAcctType_;
   p->BankAcctTypeDesc_ = BankAcctTypeDesc_;
   p->BankAcctCurrency_ = BankAcctCurrency_;
   p->BankAcctCurrDesc_ = BankAcctCurrDesc_;
   p->BankEffectiveDate_ = BankEffectiveDate_;
   p->BankStopDate_ = BankStopDate_;
   p->PayMethod_ = PayMethod_;
   p->ACHProcessor_ = ACHProcessor_;
   p->BankContact_ = BankContact_;
   p->BankCorrespondent_ = BankCorrespondent_;
   p->MatInstrAddrCode_ = MatInstrAddrCode_;
   p->BankId_ = BankId_;
   p->BankAcctNum_ = BankAcctNum_;
   p->BankAcctName_ = BankAcctName_;
   p->IntInvestUUID_ = IntInvestUUID_;
   p->DistribDetlVersion_ = DistribDetlVersion_;
   p->BankAcctVersion_ = BankAcctVersion_;
   p->IntInvestVer_ = IntInvestVer_;
   return(p);
}

BFDataField* dsi_DSTC0428_VWRepeat_Record::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40006547: return ( &DistribDetlUUID_ ); break; // DistribDetlUUID
      case 40006548: return ( &IntInvestId_ ); break; // IntInvestId
      case 40006541: return ( &RolloverType_ ); break; // RolloverType
      case 40000646: return ( &AccountTo_ ); break; // AccountTo
      case 40000648: return ( &FundTo_ ); break; // FundTo
      case 40000649: return ( &ClassTo_ ); break; // ClassTo
      case 40006540: return ( &RemainingFleg_ ); break; // RemainingFleg
      case 40000180: return ( &Currency_ ); break; // Currency
      case 40000291: return ( &Percentage_ ); break; // Percentage
      case 40000242: return ( &PayType_ ); break; // PayType
      case 40000243: return ( &PayTypeDesc_ ); break; // PayTypeDesc
      case 40006433: return ( &CommReduction_ ); break; // CommReduction
      case 40006509: return ( &IntInvestType_ ); break; // IntInvestType
      case 40006549: return ( &FELAmt_ ); break; // FELAmt
      case 40006550: return ( &IntInvestTerm_ ); break; // IntInvestTerm
      case 40006504: return ( &IntCalcMthd_ ); break; // IntCalcMthd
      case 40006434: return ( &ForcedRate_ ); break; // ForcedRate
      case 40006538: return ( &ForcedRateAmt_ ); break; // ForcedRateAmt
      case 40006511: return ( &IntCredFreq_ ); break; // IntCredFreq
      case 40006542: return ( &BusinessType_ ); break; // BusinessType
      case 40004585: return ( &RefNum_ ); break; // RefNum
      case 40006512: return ( &AddlAmt_ ); break; // AddlAmt
      case 40006587: return ( &BankAcctId_ ); break; // BankAcctId
      case 40006588: return ( &BankAcctUse_ ); break; // BankAcctUse
      case 40002119: return ( &BankIdType_ ); break; // BankIdType
      case 40002123: return ( &BankIdValue_ ); break; // BankIdValue
      case 40006589: return ( &BankTransitNo_ ); break; // BankTransitNo
      case 40006590: return ( &BankSwiftCode_ ); break; // BankSwiftCode
      case 40006591: return ( &BankRefNumber_ ); break; // BankRefNumber
      case 40000285: return ( &InstName_ ); break; // InstName
      case 40002167: return ( &BankAddr1_ ); break; // BankAddr1
      case 40002168: return ( &BankAddr2_ ); break; // BankAddr2
      case 40002169: return ( &BankAddr3_ ); break; // BankAddr3
      case 40002170: return ( &BankAddr4_ ); break; // BankAddr4
      case 40002171: return ( &BankAddr5_ ); break; // BankAddr5
      case 40002142: return ( &BankPostal_ ); break; // BankPostal
      case 40002144: return ( &BankCountry_ ); break; // BankCountry
      case 40000253: return ( &BankAcctType_ ); break; // BankAcctType
      case 40000254: return ( &BankAcctTypeDesc_ ); break; // BankAcctTypeDesc
      case 40000251: return ( &BankAcctCurrency_ ); break; // BankAcctCurrency
      case 40003144: return ( &BankAcctCurrDesc_ ); break; // BankAcctCurrDesc
      case 40002713: return ( &BankEffectiveDate_ ); break; // BankEffectiveDate
      case 40006592: return ( &BankStopDate_ ); break; // BankStopDate
      case 40003095: return ( &PayMethod_ ); break; // PayMethod
      case 40002150: return ( &ACHProcessor_ ); break; // ACHProcessor
      case 40002146: return ( &BankContact_ ); break; // BankContact
      case 40006593: return ( &BankCorrespondent_ ); break; // BankCorrespondent
      case 40006725: return ( &MatInstrAddrCode_ ); break; // MatInstrAddrCode
      case 40002283: return ( &BankId_ ); break; // BankId
      case 40000248: return ( &BankAcctNum_ ); break; // BankAcctNum
      case 40000249: return ( &BankAcctName_ ); break; // BankAcctName
      case 40006498: return ( &IntInvestUUID_ ); break; // IntInvestUUID
      case 40006647: return ( &DistribDetlVersion_ ); break; // DistribDetlVersion
      case 40006648: return ( &BankAcctVersion_ ); break; // BankAcctVersion
      case 40006645: return ( &IntInvestVer_ ); break; // IntInvestVer
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0428_VWRepeat_Record::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0428_VWRepeat_Record* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0428_VWRepeat_Record::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 55 )
   {
      BFDataField* pField = aFlds_[iField];
      if( NULL == pField )
      {
         switch(iField)
         {
            case 0: aFlds_[0] = &DistribDetlUUID_; break;
            case 1: aFlds_[1] = &IntInvestId_; break;
            case 2: aFlds_[2] = &RolloverType_; break;
            case 3: aFlds_[3] = &AccountTo_; break;
            case 4: aFlds_[4] = &FundTo_; break;
            case 5: aFlds_[5] = &ClassTo_; break;
            case 6: aFlds_[6] = &RemainingFleg_; break;
            case 7: aFlds_[7] = &Currency_; break;
            case 8: aFlds_[8] = &Percentage_; break;
            case 9: aFlds_[9] = &PayType_; break;
            case 10: aFlds_[10] = &PayTypeDesc_; break;
            case 11: aFlds_[11] = &CommReduction_; break;
            case 12: aFlds_[12] = &IntInvestType_; break;
            case 13: aFlds_[13] = &FELAmt_; break;
            case 14: aFlds_[14] = &IntInvestTerm_; break;
            case 15: aFlds_[15] = &IntCalcMthd_; break;
            case 16: aFlds_[16] = &ForcedRate_; break;
            case 17: aFlds_[17] = &ForcedRateAmt_; break;
            case 18: aFlds_[18] = &IntCredFreq_; break;
            case 19: aFlds_[19] = &BusinessType_; break;
            case 20: aFlds_[20] = &RefNum_; break;
            case 21: aFlds_[21] = &AddlAmt_; break;
            case 22: aFlds_[22] = &BankAcctId_; break;
            case 23: aFlds_[23] = &BankAcctUse_; break;
            case 24: aFlds_[24] = &BankIdType_; break;
            case 25: aFlds_[25] = &BankIdValue_; break;
            case 26: aFlds_[26] = &BankTransitNo_; break;
            case 27: aFlds_[27] = &BankSwiftCode_; break;
            case 28: aFlds_[28] = &BankRefNumber_; break;
            case 29: aFlds_[29] = &InstName_; break;
            case 30: aFlds_[30] = &BankAddr1_; break;
            case 31: aFlds_[31] = &BankAddr2_; break;
            case 32: aFlds_[32] = &BankAddr3_; break;
            case 33: aFlds_[33] = &BankAddr4_; break;
            case 34: aFlds_[34] = &BankAddr5_; break;
            case 35: aFlds_[35] = &BankPostal_; break;
            case 36: aFlds_[36] = &BankCountry_; break;
            case 37: aFlds_[37] = &BankAcctType_; break;
            case 38: aFlds_[38] = &BankAcctTypeDesc_; break;
            case 39: aFlds_[39] = &BankAcctCurrency_; break;
            case 40: aFlds_[40] = &BankAcctCurrDesc_; break;
            case 41: aFlds_[41] = &BankEffectiveDate_; break;
            case 42: aFlds_[42] = &BankStopDate_; break;
            case 43: aFlds_[43] = &PayMethod_; break;
            case 44: aFlds_[44] = &ACHProcessor_; break;
            case 45: aFlds_[45] = &BankContact_; break;
            case 46: aFlds_[46] = &BankCorrespondent_; break;
            case 47: aFlds_[47] = &MatInstrAddrCode_; break;
            case 48: aFlds_[48] = &BankId_; break;
            case 49: aFlds_[49] = &BankAcctNum_; break;
            case 50: aFlds_[50] = &BankAcctName_; break;
            case 51: aFlds_[51] = &IntInvestUUID_; break;
            case 52: aFlds_[52] = &DistribDetlVersion_; break;
            case 53: aFlds_[53] = &BankAcctVersion_; break;
            case 54: aFlds_[54] = &IntInvestVer_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0428_VWRepeat_Record::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0428_VWRepeat_Record* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0428_VWRepeat_Record::getLargestDefinedField( void ) const
{
   return( 200 );
}

unsigned long dsi_DSTC0428_VWRepeat_Record::getDefinedByteLength( void ) const
{
   return( 2334 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0428_VWRepeat_Record::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0428_VWRepeat_Record::fieldExists( id );
}

bool dsi_DSTC0428_VWRepeat_Record::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40006547: return( true );
      case 40006548: return( true );
      case 40006541: return( true );
      case 40000646: return( true );
      case 40000648: return( true );
      case 40000649: return( true );
      case 40006540: return( true );
      case 40000180: return( true );
      case 40000291: return( true );
      case 40000242: return( true );
      case 40000243: return( true );
      case 40006433: return( true );
      case 40006509: return( true );
      case 40006549: return( true );
      case 40006550: return( true );
      case 40006504: return( true );
      case 40006434: return( true );
      case 40006538: return( true );
      case 40006511: return( true );
      case 40006542: return( true );
      case 40004585: return( true );
      case 40006512: return( true );
      case 40006587: return( true );
      case 40006588: return( true );
      case 40002119: return( true );
      case 40002123: return( true );
      case 40006589: return( true );
      case 40006590: return( true );
      case 40006591: return( true );
      case 40000285: return( true );
      case 40002167: return( true );
      case 40002168: return( true );
      case 40002169: return( true );
      case 40002170: return( true );
      case 40002171: return( true );
      case 40002142: return( true );
      case 40002144: return( true );
      case 40000253: return( true );
      case 40000254: return( true );
      case 40000251: return( true );
      case 40003144: return( true );
      case 40002713: return( true );
      case 40006592: return( true );
      case 40003095: return( true );
      case 40002150: return( true );
      case 40002146: return( true );
      case 40006593: return( true );
      case 40006725: return( true );
      case 40002283: return( true );
      case 40000248: return( true );
      case 40000249: return( true );
      case 40006498: return( true );
      case 40006647: return( true );
      case 40006648: return( true );
      case 40006645: return( true );
   }
   return false;
}

