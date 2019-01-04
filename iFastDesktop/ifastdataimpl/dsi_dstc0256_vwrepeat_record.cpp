// BFDataImpl implementation file for DataSet DSTC0256.VWRepeat_Record
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0256_vwrepeat_record.h"


// This function creates an instance of dsi_DSTC0256_VWRepeat_Record
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0256_VWRepeat_Record() { return new dsi_DSTC0256_VWRepeat_Record; }

dsi_DSTC0256_VWRepeat_Record::dsi_DSTC0256_VWRepeat_Record()
: BFDataImpl( 40003978 )
, BrokerCode_( ifds::BrokerCode, &ifds::s_FldProp_BrokerCode )
, BranchCode_( ifds::BranchCode, &ifds::s_FldProp_BranchCode )
, SalesRepCode_( ifds::SalesRepCode, &ifds::s_FldProp_SalesRepCode )
, PaymentFor_( ifds::PaymentFor, &ifds::s_FldProp_PaymentFor )
, PayType_( ifds::PayType, &ifds::s_FldProp_PayType )
, PayMethod_( ifds::PayMethod, &ifds::s_FldProp_PayMethod )
, ACHProcessor_( ifds::ACHProcessor, &ifds::s_FldProp_ACHProcessor )
, BankChrgs_( ifds::BankChrgs, &ifds::s_FldProp_BankChrgs )
, CurrencyOption_( ifds::CurrencyOption, &ifds::s_FldProp_CurrencyOption )
, UseEntityAddress_( ifds::UseEntityAddress, &ifds::s_FldProp_UseEntityAddress )
, AddrLine1_( ifds::AddrLine1, &ifds::s_FldProp_AddrLine1 )
, AddrLine2_( ifds::AddrLine2, &ifds::s_FldProp_AddrLine2 )
, AddrLine3_( ifds::AddrLine3, &ifds::s_FldProp_AddrLine3 )
, AddrLine4_( ifds::AddrLine4, &ifds::s_FldProp_AddrLine4 )
, AddrLine5_( ifds::AddrLine5, &ifds::s_FldProp_AddrLine5 )
, PostalCode_( ifds::PostalCode, &ifds::s_FldProp_PostalCode )
, CountryCode_( ifds::CountryCode, &ifds::s_FldProp_CountryCode )
, ProcessDate_( ifds::ProcessDate, &ifds::s_FldProp_ProcessDate )
, Username_( ifds::Username, &ifds::s_FldProp_Username )
, ModDate_( ifds::ModDate, &ifds::s_FldProp_ModDate )
, ModUser_( ifds::ModUser, &ifds::s_FldProp_ModUser )
, PayInstructionsId_( ifds::PayInstructionsId, &ifds::s_FldProp_PayInstructionsId )
, Currency_( ifds::Currency, &ifds::s_FldProp_Currency )
, PayInstructUsed_( ifds::PayInstructUsed, &ifds::s_FldProp_PayInstructUsed )
, PayInstructRID_( ifds::PayInstructRID, &ifds::s_FldProp_PayInstructRID )
, AccountNum_( ifds::AccountNum, &ifds::s_FldProp_AccountNum )
, DirectTo_( ifds::DirectTo, &ifds::s_FldProp_DirectTo )
, DirectToShrGrp_( ifds::DirectToShrGrp, &ifds::s_FldProp_DirectToShrGrp )
, CompanyCode_( ifds::CompanyCode, &ifds::s_FldProp_CompanyCode )
, EffectiveDate_( ifds::EffectiveDate, &ifds::s_FldProp_EffectiveDate )
, StopDate_( ifds::StopDate, &ifds::s_FldProp_StopDate )
, ConsolType_( ifds::ConsolType, &ifds::s_FldProp_ConsolType )
, PaymentIdMethod_( ifds::PaymentIdMethod, &ifds::s_FldProp_PaymentIdMethod )
, SuppressionReasonCode_( ifds::SuppressionReasonCode, &ifds::s_FldProp_SuppressionReasonCode )
{
   cFields_ = 34;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0256_VWRepeat_Record::~dsi_DSTC0256_VWRepeat_Record()
{
}

BFDataImpl* dsi_DSTC0256_VWRepeat_Record::clone()
{
   dsi_DSTC0256_VWRepeat_Record* p = new dsi_DSTC0256_VWRepeat_Record;
   p->BrokerCode_ = BrokerCode_;
   p->BranchCode_ = BranchCode_;
   p->SalesRepCode_ = SalesRepCode_;
   p->PaymentFor_ = PaymentFor_;
   p->PayType_ = PayType_;
   p->PayMethod_ = PayMethod_;
   p->ACHProcessor_ = ACHProcessor_;
   p->BankChrgs_ = BankChrgs_;
   p->CurrencyOption_ = CurrencyOption_;
   p->UseEntityAddress_ = UseEntityAddress_;
   p->AddrLine1_ = AddrLine1_;
   p->AddrLine2_ = AddrLine2_;
   p->AddrLine3_ = AddrLine3_;
   p->AddrLine4_ = AddrLine4_;
   p->AddrLine5_ = AddrLine5_;
   p->PostalCode_ = PostalCode_;
   p->CountryCode_ = CountryCode_;
   p->ProcessDate_ = ProcessDate_;
   p->Username_ = Username_;
   p->ModDate_ = ModDate_;
   p->ModUser_ = ModUser_;
   p->PayInstructionsId_ = PayInstructionsId_;
   p->Currency_ = Currency_;
   p->PayInstructUsed_ = PayInstructUsed_;
   p->PayInstructRID_ = PayInstructRID_;
   p->AccountNum_ = AccountNum_;
   p->DirectTo_ = DirectTo_;
   p->DirectToShrGrp_ = DirectToShrGrp_;
   p->CompanyCode_ = CompanyCode_;
   p->EffectiveDate_ = EffectiveDate_;
   p->StopDate_ = StopDate_;
   p->ConsolType_ = ConsolType_;
   p->PaymentIdMethod_ = PaymentIdMethod_;
   p->SuppressionReasonCode_ = SuppressionReasonCode_;
   return(p);
}

BFDataField* dsi_DSTC0256_VWRepeat_Record::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40000044: return ( &BrokerCode_ ); break; // BrokerCode
      case 40000045: return ( &BranchCode_ ); break; // BranchCode
      case 40000046: return ( &SalesRepCode_ ); break; // SalesRepCode
      case 40003965: return ( &PaymentFor_ ); break; // PaymentFor
      case 40000242: return ( &PayType_ ); break; // PayType
      case 40003095: return ( &PayMethod_ ); break; // PayMethod
      case 40002150: return ( &ACHProcessor_ ); break; // ACHProcessor
      case 40003100: return ( &BankChrgs_ ); break; // BankChrgs
      case 40003980: return ( &CurrencyOption_ ); break; // CurrencyOption
      case 40003981: return ( &UseEntityAddress_ ); break; // UseEntityAddress
      case 40000280: return ( &AddrLine1_ ); break; // AddrLine1
      case 40000281: return ( &AddrLine2_ ); break; // AddrLine2
      case 40000282: return ( &AddrLine3_ ); break; // AddrLine3
      case 40000283: return ( &AddrLine4_ ); break; // AddrLine4
      case 40000284: return ( &AddrLine5_ ); break; // AddrLine5
      case 40000143: return ( &PostalCode_ ); break; // PostalCode
      case 40000344: return ( &CountryCode_ ); break; // CountryCode
      case 40000216: return ( &ProcessDate_ ); break; // ProcessDate
      case 40000117: return ( &Username_ ); break; // Username
      case 40000217: return ( &ModDate_ ); break; // ModDate
      case 40000218: return ( &ModUser_ ); break; // ModUser
      case 40003990: return ( &PayInstructionsId_ ); break; // PayInstructionsId
      case 40000180: return ( &Currency_ ); break; // Currency
      case 40004108: return ( &PayInstructUsed_ ); break; // PayInstructUsed
      case 40004120: return ( &PayInstructRID_ ); break; // PayInstructRID
      case 40000040: return ( &AccountNum_ ); break; // AccountNum
      case 40005413: return ( &DirectTo_ ); break; // DirectTo
      case 40005414: return ( &DirectToShrGrp_ ); break; // DirectToShrGrp
      case 40002245: return ( &CompanyCode_ ); break; // CompanyCode
      case 40000327: return ( &EffectiveDate_ ); break; // EffectiveDate
      case 40000279: return ( &StopDate_ ); break; // StopDate
      case 40005490: return ( &ConsolType_ ); break; // ConsolType
      case 40005668: return ( &PaymentIdMethod_ ); break; // PaymentIdMethod
      case 40007534: return ( &SuppressionReasonCode_ ); break; // SuppressionReasonCode
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0256_VWRepeat_Record::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0256_VWRepeat_Record* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0256_VWRepeat_Record::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 34 )
   {
      BFDataField* pField = aFlds_[iField];
      if( NULL == pField )
      {
         switch(iField)
         {
            case 0: aFlds_[0] = &BrokerCode_; break;
            case 1: aFlds_[1] = &BranchCode_; break;
            case 2: aFlds_[2] = &SalesRepCode_; break;
            case 3: aFlds_[3] = &PaymentFor_; break;
            case 4: aFlds_[4] = &PayType_; break;
            case 5: aFlds_[5] = &PayMethod_; break;
            case 6: aFlds_[6] = &ACHProcessor_; break;
            case 7: aFlds_[7] = &BankChrgs_; break;
            case 8: aFlds_[8] = &CurrencyOption_; break;
            case 9: aFlds_[9] = &UseEntityAddress_; break;
            case 10: aFlds_[10] = &AddrLine1_; break;
            case 11: aFlds_[11] = &AddrLine2_; break;
            case 12: aFlds_[12] = &AddrLine3_; break;
            case 13: aFlds_[13] = &AddrLine4_; break;
            case 14: aFlds_[14] = &AddrLine5_; break;
            case 15: aFlds_[15] = &PostalCode_; break;
            case 16: aFlds_[16] = &CountryCode_; break;
            case 17: aFlds_[17] = &ProcessDate_; break;
            case 18: aFlds_[18] = &Username_; break;
            case 19: aFlds_[19] = &ModDate_; break;
            case 20: aFlds_[20] = &ModUser_; break;
            case 21: aFlds_[21] = &PayInstructionsId_; break;
            case 22: aFlds_[22] = &Currency_; break;
            case 23: aFlds_[23] = &PayInstructUsed_; break;
            case 24: aFlds_[24] = &PayInstructRID_; break;
            case 25: aFlds_[25] = &AccountNum_; break;
            case 26: aFlds_[26] = &DirectTo_; break;
            case 27: aFlds_[27] = &DirectToShrGrp_; break;
            case 28: aFlds_[28] = &CompanyCode_; break;
            case 29: aFlds_[29] = &EffectiveDate_; break;
            case 30: aFlds_[30] = &StopDate_; break;
            case 31: aFlds_[31] = &ConsolType_; break;
            case 32: aFlds_[32] = &PaymentIdMethod_; break;
            case 33: aFlds_[33] = &SuppressionReasonCode_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0256_VWRepeat_Record::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0256_VWRepeat_Record* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0256_VWRepeat_Record::getLargestDefinedField( void ) const
{
   return( 200 );
}

unsigned long dsi_DSTC0256_VWRepeat_Record::getDefinedByteLength( void ) const
{
   return( 1628 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0256_VWRepeat_Record::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0256_VWRepeat_Record::fieldExists( id );
}

bool dsi_DSTC0256_VWRepeat_Record::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40000044: return( true );
      case 40000045: return( true );
      case 40000046: return( true );
      case 40003965: return( true );
      case 40000242: return( true );
      case 40003095: return( true );
      case 40002150: return( true );
      case 40003100: return( true );
      case 40003980: return( true );
      case 40003981: return( true );
      case 40000280: return( true );
      case 40000281: return( true );
      case 40000282: return( true );
      case 40000283: return( true );
      case 40000284: return( true );
      case 40000143: return( true );
      case 40000344: return( true );
      case 40000216: return( true );
      case 40000117: return( true );
      case 40000217: return( true );
      case 40000218: return( true );
      case 40003990: return( true );
      case 40000180: return( true );
      case 40004108: return( true );
      case 40004120: return( true );
      case 40000040: return( true );
      case 40005413: return( true );
      case 40005414: return( true );
      case 40002245: return( true );
      case 40000327: return( true );
      case 40000279: return( true );
      case 40005490: return( true );
      case 40005668: return( true );
      case 40007534: return( true );
   }
   return false;
}

