// BFDataImpl implementation file for DataSet DSTC0092.VWRepeat_Record
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0092_vwrepeat_record.h"


// This function creates an instance of dsi_DSTC0092_VWRepeat_Record
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0092_VWRepeat_Record() { return new dsi_DSTC0092_VWRepeat_Record; }

dsi_DSTC0092_VWRepeat_Record::dsi_DSTC0092_VWRepeat_Record()
: BFDataImpl( 40001169 )
, Slsrep_( ifds::Slsrep, &ifds::s_FldProp_Slsrep )
, SlsrepName_( ifds::SlsrepName, &ifds::s_FldProp_SlsrepName )
, AddrLine1_( ifds::AddrLine1, &ifds::s_FldProp_AddrLine1 )
, AddrLine2_( ifds::AddrLine2, &ifds::s_FldProp_AddrLine2 )
, AddrLine3_( ifds::AddrLine3, &ifds::s_FldProp_AddrLine3 )
, AddrLine4_( ifds::AddrLine4, &ifds::s_FldProp_AddrLine4 )
, AddrLine5_( ifds::AddrLine5, &ifds::s_FldProp_AddrLine5 )
, AddrCntryCode_( ifds::AddrCntryCode, &ifds::s_FldProp_AddrCntryCode )
, PhoneNumber_( ifds::PhoneNumber, &ifds::s_FldProp_PhoneNumber )
, ModDate_( ifds::ModDate, &ifds::s_FldProp_ModDate )
, StopDate_( ifds::StopDate, &ifds::s_FldProp_StopDate )
, TrailEligible_( ifds::TrailEligible, &ifds::s_FldProp_TrailEligible )
, PayType_( ifds::PayType, &ifds::s_FldProp_PayType )
, PayTypeDesc_( ifds::PayTypeDesc, &ifds::s_FldProp_PayTypeDesc )
, Currency_( ifds::Currency, &ifds::s_FldProp_Currency )
, CurrencyName_( ifds::CurrencyName, &ifds::s_FldProp_CurrencyName )
, PayFreq_( ifds::PayFreq, &ifds::s_FldProp_PayFreq )
, PayFreqDesc_( ifds::PayFreqDesc, &ifds::s_FldProp_PayFreqDesc )
, BrokerCode_( ifds::BrokerCode, &ifds::s_FldProp_BrokerCode )
, BranchCode_( ifds::BranchCode, &ifds::s_FldProp_BranchCode )
, SlsrepType_( ifds::SlsrepType, &ifds::s_FldProp_SlsrepType )
, SlsrepTypeDesc_( ifds::SlsrepTypeDesc, &ifds::s_FldProp_SlsrepTypeDesc )
, EffectiveDate_( ifds::EffectiveDate, &ifds::s_FldProp_EffectiveDate )
, SlsrepAltName_( ifds::SlsrepAltName, &ifds::s_FldProp_SlsrepAltName )
, SegLicenseProvList_( ifds::SegLicenseProvList, &ifds::s_FldProp_SegLicenseProvList )
, NewBusiness_( ifds::NewBusiness, &ifds::s_FldProp_NewBusiness )
, BrokerName_( ifds::BrokerName, &ifds::s_FldProp_BrokerName )
, BranchName_( ifds::BranchName, &ifds::s_FldProp_BranchName )
, PostalCode_( ifds::PostalCode, &ifds::s_FldProp_PostalCode )
, Email_( ifds::Email, &ifds::s_FldProp_Email )
, FaxNumber_( ifds::FaxNumber, &ifds::s_FldProp_FaxNumber )
, AddrCntry_( ifds::AddrCntry, &ifds::s_FldProp_AddrCntry )
, SlsRepCntry_( ifds::SlsRepCntry, &ifds::s_FldProp_SlsRepCntry )
, SlsRepArea_( ifds::SlsRepArea, &ifds::s_FldProp_SlsRepArea )
, FaxCntryCode_( ifds::FaxCntryCode, &ifds::s_FldProp_FaxCntryCode )
, FaxAreaCode_( ifds::FaxAreaCode, &ifds::s_FldProp_FaxAreaCode )
, ValidationPassed_( ifds::ValidationPassed, &ifds::s_FldProp_ValidationPassed )
, PayInstrTrailer_( ifds::PayInstrTrailer, &ifds::s_FldProp_PayInstrTrailer )
, PayInstrComm_( ifds::PayInstrComm, &ifds::s_FldProp_PayInstrComm )
, RepLevel_( ifds::RepLevel, &ifds::s_FldProp_RepLevel )
, AgentStat_( ifds::AgentStat, &ifds::s_FldProp_AgentStat )
{
   cFields_ = 41;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0092_VWRepeat_Record::~dsi_DSTC0092_VWRepeat_Record()
{
}

BFDataImpl* dsi_DSTC0092_VWRepeat_Record::clone()
{
   dsi_DSTC0092_VWRepeat_Record* p = new dsi_DSTC0092_VWRepeat_Record;
   p->Slsrep_ = Slsrep_;
   p->SlsrepName_ = SlsrepName_;
   p->AddrLine1_ = AddrLine1_;
   p->AddrLine2_ = AddrLine2_;
   p->AddrLine3_ = AddrLine3_;
   p->AddrLine4_ = AddrLine4_;
   p->AddrLine5_ = AddrLine5_;
   p->AddrCntryCode_ = AddrCntryCode_;
   p->PhoneNumber_ = PhoneNumber_;
   p->ModDate_ = ModDate_;
   p->StopDate_ = StopDate_;
   p->TrailEligible_ = TrailEligible_;
   p->PayType_ = PayType_;
   p->PayTypeDesc_ = PayTypeDesc_;
   p->Currency_ = Currency_;
   p->CurrencyName_ = CurrencyName_;
   p->PayFreq_ = PayFreq_;
   p->PayFreqDesc_ = PayFreqDesc_;
   p->BrokerCode_ = BrokerCode_;
   p->BranchCode_ = BranchCode_;
   p->SlsrepType_ = SlsrepType_;
   p->SlsrepTypeDesc_ = SlsrepTypeDesc_;
   p->EffectiveDate_ = EffectiveDate_;
   p->SlsrepAltName_ = SlsrepAltName_;
   p->SegLicenseProvList_ = SegLicenseProvList_;
   p->NewBusiness_ = NewBusiness_;
   p->BrokerName_ = BrokerName_;
   p->BranchName_ = BranchName_;
   p->PostalCode_ = PostalCode_;
   p->Email_ = Email_;
   p->FaxNumber_ = FaxNumber_;
   p->AddrCntry_ = AddrCntry_;
   p->SlsRepCntry_ = SlsRepCntry_;
   p->SlsRepArea_ = SlsRepArea_;
   p->FaxCntryCode_ = FaxCntryCode_;
   p->FaxAreaCode_ = FaxAreaCode_;
   p->ValidationPassed_ = ValidationPassed_;
   p->PayInstrTrailer_ = PayInstrTrailer_;
   p->PayInstrComm_ = PayInstrComm_;
   p->RepLevel_ = RepLevel_;
   p->AgentStat_ = AgentStat_;
   return(p);
}

BFDataField* dsi_DSTC0092_VWRepeat_Record::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40000185: return ( &Slsrep_ ); break; // Slsrep
      case 40000212: return ( &SlsrepName_ ); break; // SlsrepName
      case 40000280: return ( &AddrLine1_ ); break; // AddrLine1
      case 40000281: return ( &AddrLine2_ ); break; // AddrLine2
      case 40000282: return ( &AddrLine3_ ); break; // AddrLine3
      case 40000283: return ( &AddrLine4_ ); break; // AddrLine4
      case 40000284: return ( &AddrLine5_ ); break; // AddrLine5
      case 40000299: return ( &AddrCntryCode_ ); break; // AddrCntryCode
      case 40000297: return ( &PhoneNumber_ ); break; // PhoneNumber
      case 40000217: return ( &ModDate_ ); break; // ModDate
      case 40000279: return ( &StopDate_ ); break; // StopDate
      case 40001178: return ( &TrailEligible_ ); break; // TrailEligible
      case 40000242: return ( &PayType_ ); break; // PayType
      case 40000243: return ( &PayTypeDesc_ ); break; // PayTypeDesc
      case 40000180: return ( &Currency_ ); break; // Currency
      case 40000181: return ( &CurrencyName_ ); break; // CurrencyName
      case 40001179: return ( &PayFreq_ ); break; // PayFreq
      case 40001180: return ( &PayFreqDesc_ ); break; // PayFreqDesc
      case 40000044: return ( &BrokerCode_ ); break; // BrokerCode
      case 40000045: return ( &BranchCode_ ); break; // BranchCode
      case 40001181: return ( &SlsrepType_ ); break; // SlsrepType
      case 40001182: return ( &SlsrepTypeDesc_ ); break; // SlsrepTypeDesc
      case 40000327: return ( &EffectiveDate_ ); break; // EffectiveDate
      case 40000213: return ( &SlsrepAltName_ ); break; // SlsrepAltName
      case 40001653: return ( &SegLicenseProvList_ ); break; // SegLicenseProvList
      case 40001795: return ( &NewBusiness_ ); break; // NewBusiness
      case 40000210: return ( &BrokerName_ ); break; // BrokerName
      case 40000211: return ( &BranchName_ ); break; // BranchName
      case 40000143: return ( &PostalCode_ ); break; // PostalCode
      case 40000629: return ( &Email_ ); break; // Email
      case 40000298: return ( &FaxNumber_ ); break; // FaxNumber
      case 40002938: return ( &AddrCntry_ ); break; // AddrCntry
      case 40002971: return ( &SlsRepCntry_ ); break; // SlsRepCntry
      case 40002972: return ( &SlsRepArea_ ); break; // SlsRepArea
      case 40002986: return ( &FaxCntryCode_ ); break; // FaxCntryCode
      case 40002987: return ( &FaxAreaCode_ ); break; // FaxAreaCode
      case 40003545: return ( &ValidationPassed_ ); break; // ValidationPassed
      case 40003991: return ( &PayInstrTrailer_ ); break; // PayInstrTrailer
      case 40003992: return ( &PayInstrComm_ ); break; // PayInstrComm
      case 40004134: return ( &RepLevel_ ); break; // RepLevel
      case 40004150: return ( &AgentStat_ ); break; // AgentStat
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0092_VWRepeat_Record::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0092_VWRepeat_Record* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0092_VWRepeat_Record::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 41 )
   {
      BFDataField* pField = aFlds_[iField];
      if( NULL == pField )
      {
         switch(iField)
         {
            case 0: aFlds_[0] = &Slsrep_; break;
            case 1: aFlds_[1] = &SlsrepName_; break;
            case 2: aFlds_[2] = &AddrLine1_; break;
            case 3: aFlds_[3] = &AddrLine2_; break;
            case 4: aFlds_[4] = &AddrLine3_; break;
            case 5: aFlds_[5] = &AddrLine4_; break;
            case 6: aFlds_[6] = &AddrLine5_; break;
            case 7: aFlds_[7] = &AddrCntryCode_; break;
            case 8: aFlds_[8] = &PhoneNumber_; break;
            case 9: aFlds_[9] = &ModDate_; break;
            case 10: aFlds_[10] = &StopDate_; break;
            case 11: aFlds_[11] = &TrailEligible_; break;
            case 12: aFlds_[12] = &PayType_; break;
            case 13: aFlds_[13] = &PayTypeDesc_; break;
            case 14: aFlds_[14] = &Currency_; break;
            case 15: aFlds_[15] = &CurrencyName_; break;
            case 16: aFlds_[16] = &PayFreq_; break;
            case 17: aFlds_[17] = &PayFreqDesc_; break;
            case 18: aFlds_[18] = &BrokerCode_; break;
            case 19: aFlds_[19] = &BranchCode_; break;
            case 20: aFlds_[20] = &SlsrepType_; break;
            case 21: aFlds_[21] = &SlsrepTypeDesc_; break;
            case 22: aFlds_[22] = &EffectiveDate_; break;
            case 23: aFlds_[23] = &SlsrepAltName_; break;
            case 24: aFlds_[24] = &SegLicenseProvList_; break;
            case 25: aFlds_[25] = &NewBusiness_; break;
            case 26: aFlds_[26] = &BrokerName_; break;
            case 27: aFlds_[27] = &BranchName_; break;
            case 28: aFlds_[28] = &PostalCode_; break;
            case 29: aFlds_[29] = &Email_; break;
            case 30: aFlds_[30] = &FaxNumber_; break;
            case 31: aFlds_[31] = &AddrCntry_; break;
            case 32: aFlds_[32] = &SlsRepCntry_; break;
            case 33: aFlds_[33] = &SlsRepArea_; break;
            case 34: aFlds_[34] = &FaxCntryCode_; break;
            case 35: aFlds_[35] = &FaxAreaCode_; break;
            case 36: aFlds_[36] = &ValidationPassed_; break;
            case 37: aFlds_[37] = &PayInstrTrailer_; break;
            case 38: aFlds_[38] = &PayInstrComm_; break;
            case 39: aFlds_[39] = &RepLevel_; break;
            case 40: aFlds_[40] = &AgentStat_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0092_VWRepeat_Record::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0092_VWRepeat_Record* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0092_VWRepeat_Record::getLargestDefinedField( void ) const
{
   return( 200 );
}

unsigned long dsi_DSTC0092_VWRepeat_Record::getDefinedByteLength( void ) const
{
   return( 2115 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0092_VWRepeat_Record::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0092_VWRepeat_Record::fieldExists( id );
}

bool dsi_DSTC0092_VWRepeat_Record::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40000185: return( true );
      case 40000212: return( true );
      case 40000280: return( true );
      case 40000281: return( true );
      case 40000282: return( true );
      case 40000283: return( true );
      case 40000284: return( true );
      case 40000299: return( true );
      case 40000297: return( true );
      case 40000217: return( true );
      case 40000279: return( true );
      case 40001178: return( true );
      case 40000242: return( true );
      case 40000243: return( true );
      case 40000180: return( true );
      case 40000181: return( true );
      case 40001179: return( true );
      case 40001180: return( true );
      case 40000044: return( true );
      case 40000045: return( true );
      case 40001181: return( true );
      case 40001182: return( true );
      case 40000327: return( true );
      case 40000213: return( true );
      case 40001653: return( true );
      case 40001795: return( true );
      case 40000210: return( true );
      case 40000211: return( true );
      case 40000143: return( true );
      case 40000629: return( true );
      case 40000298: return( true );
      case 40002938: return( true );
      case 40002971: return( true );
      case 40002972: return( true );
      case 40002986: return( true );
      case 40002987: return( true );
      case 40003545: return( true );
      case 40003991: return( true );
      case 40003992: return( true );
      case 40004134: return( true );
      case 40004150: return( true );
   }
   return false;
}

