// BFDataImpl implementation file for DataSet DSTC0017.VWRepeat_Record
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:58 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0017_vwrepeat_record.h"


// This function creates an instance of dsi_DSTC0017_VWRepeat_Record
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0017_VWRepeat_Record() { return new dsi_DSTC0017_VWRepeat_Record; }

dsi_DSTC0017_VWRepeat_Record::dsi_DSTC0017_VWRepeat_Record()
: BFDataImpl( 40000347 )
, TransId_( ifds::TransId, &ifds::s_FldProp_TransId )
, TransType_( ifds::TransType, &ifds::s_FldProp_TransType )
, TransTypeDesc_( ifds::TransTypeDesc, &ifds::s_FldProp_TransTypeDesc )
, TransNum_( ifds::TransNum, &ifds::s_FldProp_TransNum )
, TradeDate_( ifds::TradeDate, &ifds::s_FldProp_TradeDate )
, SettleDate_( ifds::SettleDate, &ifds::s_FldProp_SettleDate )
, ModDate_( ifds::ModDate, &ifds::s_FldProp_ModDate )
, Settled_( ifds::Settled, &ifds::s_FldProp_Settled )
, GrossAmt_( ifds::GrossAmt, &ifds::s_FldProp_GrossAmt )
, NetAmt_( ifds::NetAmt, &ifds::s_FldProp_NetAmt )
, UnitPrice_( ifds::UnitPrice, &ifds::s_FldProp_UnitPrice )
, Units_( ifds::Units, &ifds::s_FldProp_Units )
, UnitBalance_( ifds::UnitBalance, &ifds::s_FldProp_UnitBalance )
, rxFundCode_( ifds::rxFundCode, &ifds::s_FldProp_rxFundCode )
, rxClassCode_( ifds::rxClassCode, &ifds::s_FldProp_rxClassCode )
, Cancelled_( ifds::Cancelled, &ifds::s_FldProp_Cancelled )
, Reversal_( ifds::Reversal, &ifds::s_FldProp_Reversal )
, PayType2_( ifds::PayType2, &ifds::s_FldProp_PayType2 )
, PayTypeDesc_( ifds::PayTypeDesc, &ifds::s_FldProp_PayTypeDesc )
, OrderBatch_( ifds::OrderBatch, &ifds::s_FldProp_OrderBatch )
, OrderTrace_( ifds::OrderTrace, &ifds::s_FldProp_OrderTrace )
, OrderUser_( ifds::OrderUser, &ifds::s_FldProp_OrderUser )
, CancelBatch_( ifds::CancelBatch, &ifds::s_FldProp_CancelBatch )
, CancelTrace_( ifds::CancelTrace, &ifds::s_FldProp_CancelTrace )
, CancelUser_( ifds::CancelUser, &ifds::s_FldProp_CancelUser )
, SettleBatch_( ifds::SettleBatch, &ifds::s_FldProp_SettleBatch )
, SettleTrace_( ifds::SettleTrace, &ifds::s_FldProp_SettleTrace )
, SettleUser_( ifds::SettleUser, &ifds::s_FldProp_SettleUser )
, VerifiedBy_( ifds::VerifiedBy, &ifds::s_FldProp_VerifiedBy )
, TfrAcct_( ifds::TfrAcct, &ifds::s_FldProp_TfrAcct )
, TfrFund_( ifds::TfrFund, &ifds::s_FldProp_TfrFund )
, TfrClass_( ifds::TfrClass, &ifds::s_FldProp_TfrClass )
, SettleCurrency_( ifds::SettleCurrency, &ifds::s_FldProp_SettleCurrency )
, Amount_( ifds::Amount, &ifds::s_FldProp_Amount )
, BrokerCode_( ifds::BrokerCode, &ifds::s_FldProp_BrokerCode )
, BranchCode_( ifds::BranchCode, &ifds::s_FldProp_BranchCode )
, SalesRepCode_( ifds::SalesRepCode, &ifds::s_FldProp_SalesRepCode )
, OfferPrice_( ifds::OfferPrice, &ifds::s_FldProp_OfferPrice )
, FirstName_( ifds::FirstName, &ifds::s_FldProp_FirstName )
, LastName_( ifds::LastName, &ifds::s_FldProp_LastName )
, SettledDesc_( ifds::SettledDesc, &ifds::s_FldProp_SettledDesc )
, SeqNum_( ifds::SeqNum, &ifds::s_FldProp_SeqNum )
, AMSTrade_( ifds::AMSTrade, &ifds::s_FldProp_AMSTrade )
, AccountNum_( ifds::AccountNum, &ifds::s_FldProp_AccountNum )
, ExistExternalId_( ifds::ExistExternalId, &ifds::s_FldProp_ExistExternalId )
, MsgExists_( ifds::MsgExists, &ifds::s_FldProp_MsgExists )
, TranStatus_( ifds::TranStatus, &ifds::s_FldProp_TranStatus )
, ReportingExchRate_( ifds::ReportingExchRate, &ifds::s_FldProp_ReportingExchRate )
, HRDCRespPending_( ifds::HRDCRespPending, &ifds::s_FldProp_HRDCRespPending )
{
   cFields_ = 49;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0017_VWRepeat_Record::~dsi_DSTC0017_VWRepeat_Record()
{
}

BFDataImpl* dsi_DSTC0017_VWRepeat_Record::clone()
{
   dsi_DSTC0017_VWRepeat_Record* p = new dsi_DSTC0017_VWRepeat_Record;
   p->TransId_ = TransId_;
   p->TransType_ = TransType_;
   p->TransTypeDesc_ = TransTypeDesc_;
   p->TransNum_ = TransNum_;
   p->TradeDate_ = TradeDate_;
   p->SettleDate_ = SettleDate_;
   p->ModDate_ = ModDate_;
   p->Settled_ = Settled_;
   p->GrossAmt_ = GrossAmt_;
   p->NetAmt_ = NetAmt_;
   p->UnitPrice_ = UnitPrice_;
   p->Units_ = Units_;
   p->UnitBalance_ = UnitBalance_;
   p->rxFundCode_ = rxFundCode_;
   p->rxClassCode_ = rxClassCode_;
   p->Cancelled_ = Cancelled_;
   p->Reversal_ = Reversal_;
   p->PayType2_ = PayType2_;
   p->PayTypeDesc_ = PayTypeDesc_;
   p->OrderBatch_ = OrderBatch_;
   p->OrderTrace_ = OrderTrace_;
   p->OrderUser_ = OrderUser_;
   p->CancelBatch_ = CancelBatch_;
   p->CancelTrace_ = CancelTrace_;
   p->CancelUser_ = CancelUser_;
   p->SettleBatch_ = SettleBatch_;
   p->SettleTrace_ = SettleTrace_;
   p->SettleUser_ = SettleUser_;
   p->VerifiedBy_ = VerifiedBy_;
   p->TfrAcct_ = TfrAcct_;
   p->TfrFund_ = TfrFund_;
   p->TfrClass_ = TfrClass_;
   p->SettleCurrency_ = SettleCurrency_;
   p->Amount_ = Amount_;
   p->BrokerCode_ = BrokerCode_;
   p->BranchCode_ = BranchCode_;
   p->SalesRepCode_ = SalesRepCode_;
   p->OfferPrice_ = OfferPrice_;
   p->FirstName_ = FirstName_;
   p->LastName_ = LastName_;
   p->SettledDesc_ = SettledDesc_;
   p->SeqNum_ = SeqNum_;
   p->AMSTrade_ = AMSTrade_;
   p->AccountNum_ = AccountNum_;
   p->ExistExternalId_ = ExistExternalId_;
   p->MsgExists_ = MsgExists_;
   p->TranStatus_ = TranStatus_;
   p->ReportingExchRate_ = ReportingExchRate_;
   p->HRDCRespPending_ = HRDCRespPending_;
   return(p);
}

BFDataField* dsi_DSTC0017_VWRepeat_Record::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40000063: return ( &TransId_ ); break; // TransId
      case 40000095: return ( &TransType_ ); break; // TransType
      case 40000337: return ( &TransTypeDesc_ ); break; // TransTypeDesc
      case 40000096: return ( &TransNum_ ); break; // TransNum
      case 40000097: return ( &TradeDate_ ); break; // TradeDate
      case 40000348: return ( &SettleDate_ ); break; // SettleDate
      case 40000217: return ( &ModDate_ ); break; // ModDate
      case 40000349: return ( &Settled_ ); break; // Settled
      case 40000350: return ( &GrossAmt_ ); break; // GrossAmt
      case 40000351: return ( &NetAmt_ ); break; // NetAmt
      case 40000352: return ( &UnitPrice_ ); break; // UnitPrice
      case 40000332: return ( &Units_ ); break; // Units
      case 40000353: return ( &UnitBalance_ ); break; // UnitBalance
      case 40000286: return ( &rxFundCode_ ); break; // rxFundCode
      case 40000287: return ( &rxClassCode_ ); break; // rxClassCode
      case 40000354: return ( &Cancelled_ ); break; // Cancelled
      case 40000355: return ( &Reversal_ ); break; // Reversal
      case 40002055: return ( &PayType2_ ); break; // PayType2
      case 40000243: return ( &PayTypeDesc_ ); break; // PayTypeDesc
      case 40000356: return ( &OrderBatch_ ); break; // OrderBatch
      case 40000357: return ( &OrderTrace_ ); break; // OrderTrace
      case 40000358: return ( &OrderUser_ ); break; // OrderUser
      case 40000359: return ( &CancelBatch_ ); break; // CancelBatch
      case 40000360: return ( &CancelTrace_ ); break; // CancelTrace
      case 40000361: return ( &CancelUser_ ); break; // CancelUser
      case 40000362: return ( &SettleBatch_ ); break; // SettleBatch
      case 40000363: return ( &SettleTrace_ ); break; // SettleTrace
      case 40000364: return ( &SettleUser_ ); break; // SettleUser
      case 40000365: return ( &VerifiedBy_ ); break; // VerifiedBy
      case 40000366: return ( &TfrAcct_ ); break; // TfrAcct
      case 40000367: return ( &TfrFund_ ); break; // TfrFund
      case 40000368: return ( &TfrClass_ ); break; // TfrClass
      case 40000455: return ( &SettleCurrency_ ); break; // SettleCurrency
      case 40000231: return ( &Amount_ ); break; // Amount
      case 40000044: return ( &BrokerCode_ ); break; // BrokerCode
      case 40000045: return ( &BranchCode_ ); break; // BranchCode
      case 40000046: return ( &SalesRepCode_ ); break; // SalesRepCode
      case 40002191: return ( &OfferPrice_ ); break; // OfferPrice
      case 40000129: return ( &FirstName_ ); break; // FirstName
      case 40000128: return ( &LastName_ ); break; // LastName
      case 40002859: return ( &SettledDesc_ ); break; // SettledDesc
      case 40000475: return ( &SeqNum_ ); break; // SeqNum
      case 40003787: return ( &AMSTrade_ ); break; // AMSTrade
      case 40000040: return ( &AccountNum_ ); break; // AccountNum
      case 40004680: return ( &ExistExternalId_ ); break; // ExistExternalId
      case 40005049: return ( &MsgExists_ ); break; // MsgExists
      case 40002273: return ( &TranStatus_ ); break; // TranStatus
      case 40005407: return ( &ReportingExchRate_ ); break; // ReportingExchRate
      case 40006124: return ( &HRDCRespPending_ ); break; // HRDCRespPending
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0017_VWRepeat_Record::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0017_VWRepeat_Record* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0017_VWRepeat_Record::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 49 )
   {
      BFDataField* pField = aFlds_[iField];
      if( NULL == pField )
      {
         switch(iField)
         {
            case 0: aFlds_[0] = &TransId_; break;
            case 1: aFlds_[1] = &TransType_; break;
            case 2: aFlds_[2] = &TransTypeDesc_; break;
            case 3: aFlds_[3] = &TransNum_; break;
            case 4: aFlds_[4] = &TradeDate_; break;
            case 5: aFlds_[5] = &SettleDate_; break;
            case 6: aFlds_[6] = &ModDate_; break;
            case 7: aFlds_[7] = &Settled_; break;
            case 8: aFlds_[8] = &GrossAmt_; break;
            case 9: aFlds_[9] = &NetAmt_; break;
            case 10: aFlds_[10] = &UnitPrice_; break;
            case 11: aFlds_[11] = &Units_; break;
            case 12: aFlds_[12] = &UnitBalance_; break;
            case 13: aFlds_[13] = &rxFundCode_; break;
            case 14: aFlds_[14] = &rxClassCode_; break;
            case 15: aFlds_[15] = &Cancelled_; break;
            case 16: aFlds_[16] = &Reversal_; break;
            case 17: aFlds_[17] = &PayType2_; break;
            case 18: aFlds_[18] = &PayTypeDesc_; break;
            case 19: aFlds_[19] = &OrderBatch_; break;
            case 20: aFlds_[20] = &OrderTrace_; break;
            case 21: aFlds_[21] = &OrderUser_; break;
            case 22: aFlds_[22] = &CancelBatch_; break;
            case 23: aFlds_[23] = &CancelTrace_; break;
            case 24: aFlds_[24] = &CancelUser_; break;
            case 25: aFlds_[25] = &SettleBatch_; break;
            case 26: aFlds_[26] = &SettleTrace_; break;
            case 27: aFlds_[27] = &SettleUser_; break;
            case 28: aFlds_[28] = &VerifiedBy_; break;
            case 29: aFlds_[29] = &TfrAcct_; break;
            case 30: aFlds_[30] = &TfrFund_; break;
            case 31: aFlds_[31] = &TfrClass_; break;
            case 32: aFlds_[32] = &SettleCurrency_; break;
            case 33: aFlds_[33] = &Amount_; break;
            case 34: aFlds_[34] = &BrokerCode_; break;
            case 35: aFlds_[35] = &BranchCode_; break;
            case 36: aFlds_[36] = &SalesRepCode_; break;
            case 37: aFlds_[37] = &OfferPrice_; break;
            case 38: aFlds_[38] = &FirstName_; break;
            case 39: aFlds_[39] = &LastName_; break;
            case 40: aFlds_[40] = &SettledDesc_; break;
            case 41: aFlds_[41] = &SeqNum_; break;
            case 42: aFlds_[42] = &AMSTrade_; break;
            case 43: aFlds_[43] = &AccountNum_; break;
            case 44: aFlds_[44] = &ExistExternalId_; break;
            case 45: aFlds_[45] = &MsgExists_; break;
            case 46: aFlds_[46] = &TranStatus_; break;
            case 47: aFlds_[47] = &ReportingExchRate_; break;
            case 48: aFlds_[48] = &HRDCRespPending_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0017_VWRepeat_Record::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0017_VWRepeat_Record* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0017_VWRepeat_Record::getLargestDefinedField( void ) const
{
   return( 80 );
}

unsigned long dsi_DSTC0017_VWRepeat_Record::getDefinedByteLength( void ) const
{
   return( 1848 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0017_VWRepeat_Record::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0017_VWRepeat_Record::fieldExists( id );
}

bool dsi_DSTC0017_VWRepeat_Record::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40000063: return( true );
      case 40000095: return( true );
      case 40000337: return( true );
      case 40000096: return( true );
      case 40000097: return( true );
      case 40000348: return( true );
      case 40000217: return( true );
      case 40000349: return( true );
      case 40000350: return( true );
      case 40000351: return( true );
      case 40000352: return( true );
      case 40000332: return( true );
      case 40000353: return( true );
      case 40000286: return( true );
      case 40000287: return( true );
      case 40000354: return( true );
      case 40000355: return( true );
      case 40002055: return( true );
      case 40000243: return( true );
      case 40000356: return( true );
      case 40000357: return( true );
      case 40000358: return( true );
      case 40000359: return( true );
      case 40000360: return( true );
      case 40000361: return( true );
      case 40000362: return( true );
      case 40000363: return( true );
      case 40000364: return( true );
      case 40000365: return( true );
      case 40000366: return( true );
      case 40000367: return( true );
      case 40000368: return( true );
      case 40000455: return( true );
      case 40000231: return( true );
      case 40000044: return( true );
      case 40000045: return( true );
      case 40000046: return( true );
      case 40002191: return( true );
      case 40000129: return( true );
      case 40000128: return( true );
      case 40002859: return( true );
      case 40000475: return( true );
      case 40003787: return( true );
      case 40000040: return( true );
      case 40004680: return( true );
      case 40005049: return( true );
      case 40002273: return( true );
      case 40005407: return( true );
      case 40006124: return( true );
   }
   return false;
}

