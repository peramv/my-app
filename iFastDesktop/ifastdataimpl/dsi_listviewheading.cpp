// BFDataImpl implementation file for DataSet ListViewHeading
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_listviewheading.h"


// This function creates an instance of dsi_ListViewHeading
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_ListViewHeading() { return new dsi_ListViewHeading; }

dsi_ListViewHeading::dsi_ListViewHeading()
: BFDataImpl( 40000892 )
, EntityListViewHeading_( ifds::EntityListViewHeading, &ifds::s_FldProp_EntityListViewHeading )
, SelectEntityListHeading_( ifds::SelectEntityListHeading, &ifds::s_FldProp_SelectEntityListHeading )
, AccListHeading_( ifds::AccListHeading, &ifds::s_FldProp_AccListHeading )
, DistributionHeadingSet_( ifds::DistributionHeadingSet, &ifds::s_FldProp_DistributionHeadingSet )
, VerifySearchHeadingSet_( ifds::VerifySearchHeadingSet, &ifds::s_FldProp_VerifySearchHeadingSet )
, FreeUnitHeadingSet_( ifds::FreeUnitHeadingSet, &ifds::s_FldProp_FreeUnitHeadingSet )
, ACBListHeading_( ifds::ACBListHeading, &ifds::s_FldProp_ACBListHeading )
, TransactionHeading_( ifds::TransactionHeading, &ifds::s_FldProp_TransactionHeading )
, PendingHeading_( ifds::PendingHeading, &ifds::s_FldProp_PendingHeading )
, HistoricalAccountHeadingSet_( ifds::HistoricalAccountHeadingSet, &ifds::s_FldProp_HistoricalAccountHeadingSet )
, RemarksHeadingSet_( ifds::RemarksHeadingSet, &ifds::s_FldProp_RemarksHeadingSet )
, BankInstructionHeading_( ifds::BankInstructionHeading, &ifds::s_FldProp_BankInstructionHeading )
, SystematicListHeading_( ifds::SystematicListHeading, &ifds::s_FldProp_SystematicListHeading )
, SysAllocListHeading_( ifds::SysAllocListHeading, &ifds::s_FldProp_SysAllocListHeading )
, WhereUsedListHeading_( ifds::WhereUsedListHeading, &ifds::s_FldProp_WhereUsedListHeading )
, ConfirmAwdHeading_( ifds::ConfirmAwdHeading, &ifds::s_FldProp_ConfirmAwdHeading )
, ConfirmTransHeading_( ifds::ConfirmTransHeading, &ifds::s_FldProp_ConfirmTransHeading )
, ShareholderAddressHeadingSet_( ifds::ShareholderAddressHeadingSet, &ifds::s_FldProp_ShareholderAddressHeadingSet )
, EntityAddressHeadingSet_( ifds::EntityAddressHeadingSet, &ifds::s_FldProp_EntityAddressHeadingSet )
, AddressMailingHeadingSet_( ifds::AddressMailingHeadingSet, &ifds::s_FldProp_AddressMailingHeadingSet )
, BankListHeadingSet_( ifds::BankListHeadingSet, &ifds::s_FldProp_BankListHeadingSet )
, BranchListHeading_( ifds::BranchListHeading, &ifds::s_FldProp_BranchListHeading )
, SlsRepListHeading_( ifds::SlsRepListHeading, &ifds::s_FldProp_SlsRepListHeading )
, DistributionHeadingSet1_( ifds::DistributionHeadingSet1, &ifds::s_FldProp_DistributionHeadingSet1 )
, BrokerListHeading_( ifds::BrokerListHeading, &ifds::s_FldProp_BrokerListHeading )
, ContractListHeading_( ifds::ContractListHeading, &ifds::s_FldProp_ContractListHeading )
, CertificateHeadingSet_( ifds::CertificateHeadingSet, &ifds::s_FldProp_CertificateHeadingSet )
, IdentAcctAccountsHeadingSet_( ifds::IdentAcctAccountsHeadingSet, &ifds::s_FldProp_IdentAcctAccountsHeadingSet )
, IdentAcctEntitiesHeadingSet_( ifds::IdentAcctEntitiesHeadingSet, &ifds::s_FldProp_IdentAcctEntitiesHeadingSet )
, EntityIDSHeadingSet_( ifds::EntityIDSHeadingSet, &ifds::s_FldProp_EntityIDSHeadingSet )
, ChequesDetailHeadingSet_( ifds::ChequesDetailHeadingSet, &ifds::s_FldProp_ChequesDetailHeadingSet )
, ChequesListHeadingSet_( ifds::ChequesListHeadingSet, &ifds::s_FldProp_ChequesListHeadingSet )
, GuaranteeListHeading_( ifds::GuaranteeListHeading, &ifds::s_FldProp_GuaranteeListHeading )
, GuarResetListHeading_( ifds::GuarResetListHeading, &ifds::s_FldProp_GuarResetListHeading )
, LV_RRIF_AllocHeading_( ifds::LV_RRIF_AllocHeading, &ifds::s_FldProp_LV_RRIF_AllocHeading )
, LV_RRIF_Heading_( ifds::LV_RRIF_Heading, &ifds::s_FldProp_LV_RRIF_Heading )
, GuaranteeRedDetailLeft_( ifds::GuaranteeRedDetailLeft, &ifds::s_FldProp_GuaranteeRedDetailLeft )
, GuaranteeRedDetailTop_( ifds::GuaranteeRedDetailTop, &ifds::s_FldProp_GuaranteeRedDetailTop )
, TaxRatesHeadingSet_( ifds::TaxRatesHeadingSet, &ifds::s_FldProp_TaxRatesHeadingSet )
, RESPInfoHeadingSet_( ifds::RESPInfoHeadingSet, &ifds::s_FldProp_RESPInfoHeadingSet )
, RESPTransactionHeadingSet_( ifds::RESPTransactionHeadingSet, &ifds::s_FldProp_RESPTransactionHeadingSet )
, LV_OneTimeAllocFundHeading_( ifds::LV_OneTimeAllocFundHeading, &ifds::s_FldProp_LV_OneTimeAllocFundHeading )
, LV_OneTimeRRIFAllocHeading_( ifds::LV_OneTimeRRIFAllocHeading, &ifds::s_FldProp_LV_OneTimeRRIFAllocHeading )
, LV_OneTimeRRIFFundHeading_( ifds::LV_OneTimeRRIFFundHeading, &ifds::s_FldProp_LV_OneTimeRRIFFundHeading )
, MinMaxListLeft_( ifds::MinMaxListLeft, &ifds::s_FldProp_MinMaxListLeft )
, MinMaxListTop_( ifds::MinMaxListTop, &ifds::s_FldProp_MinMaxListTop )
, LV_OneTimeTradeAllocHeadingSet_( ifds::LV_OneTimeTradeAllocHeadingSet, &ifds::s_FldProp_LV_OneTimeTradeAllocHeadingSet )
, LV_OneTimeTradeHeadingSet_( ifds::LV_OneTimeTradeHeadingSet, &ifds::s_FldProp_LV_OneTimeTradeHeadingSet )
, SplitCommissionDetailsHeadingSet_( ifds::SplitCommissionDetailsHeadingSet, &ifds::s_FldProp_SplitCommissionDetailsHeadingSet )
, TradeAllocationDetailsHeadingSet_( ifds::TradeAllocationDetailsHeadingSet, &ifds::s_FldProp_TradeAllocationDetailsHeadingSet )
, MultiContractsListHeading_( ifds::MultiContractsListHeading, &ifds::s_FldProp_MultiContractsListHeading )
, HistoricalSysIndexHeadingSet_( ifds::HistoricalSysIndexHeadingSet, &ifds::s_FldProp_HistoricalSysIndexHeadingSet )
, AddressMailingColumnSet_( ifds::AddressMailingColumnSet, &ifds::s_FldProp_AddressMailingColumnSet )
, SlsRepListHeading1_( ifds::SlsRepListHeading1, &ifds::s_FldProp_SlsRepListHeading1 )
, VerifySearchSNAPHeadingSet_( ifds::VerifySearchSNAPHeadingSet, &ifds::s_FldProp_VerifySearchSNAPHeadingSet )
, AccountReviewHeadingSet_( ifds::AccountReviewHeadingSet, &ifds::s_FldProp_AccountReviewHeadingSet )
{
   cFields_ = 56;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_ListViewHeading::~dsi_ListViewHeading()
{
}

BFDataImpl* dsi_ListViewHeading::clone()
{
   dsi_ListViewHeading* p = new dsi_ListViewHeading;
   p->EntityListViewHeading_ = EntityListViewHeading_;
   p->SelectEntityListHeading_ = SelectEntityListHeading_;
   p->AccListHeading_ = AccListHeading_;
   p->DistributionHeadingSet_ = DistributionHeadingSet_;
   p->VerifySearchHeadingSet_ = VerifySearchHeadingSet_;
   p->FreeUnitHeadingSet_ = FreeUnitHeadingSet_;
   p->ACBListHeading_ = ACBListHeading_;
   p->TransactionHeading_ = TransactionHeading_;
   p->PendingHeading_ = PendingHeading_;
   p->HistoricalAccountHeadingSet_ = HistoricalAccountHeadingSet_;
   p->RemarksHeadingSet_ = RemarksHeadingSet_;
   p->BankInstructionHeading_ = BankInstructionHeading_;
   p->SystematicListHeading_ = SystematicListHeading_;
   p->SysAllocListHeading_ = SysAllocListHeading_;
   p->WhereUsedListHeading_ = WhereUsedListHeading_;
   p->ConfirmAwdHeading_ = ConfirmAwdHeading_;
   p->ConfirmTransHeading_ = ConfirmTransHeading_;
   p->ShareholderAddressHeadingSet_ = ShareholderAddressHeadingSet_;
   p->EntityAddressHeadingSet_ = EntityAddressHeadingSet_;
   p->AddressMailingHeadingSet_ = AddressMailingHeadingSet_;
   p->BankListHeadingSet_ = BankListHeadingSet_;
   p->BranchListHeading_ = BranchListHeading_;
   p->SlsRepListHeading_ = SlsRepListHeading_;
   p->DistributionHeadingSet1_ = DistributionHeadingSet1_;
   p->BrokerListHeading_ = BrokerListHeading_;
   p->ContractListHeading_ = ContractListHeading_;
   p->CertificateHeadingSet_ = CertificateHeadingSet_;
   p->IdentAcctAccountsHeadingSet_ = IdentAcctAccountsHeadingSet_;
   p->IdentAcctEntitiesHeadingSet_ = IdentAcctEntitiesHeadingSet_;
   p->EntityIDSHeadingSet_ = EntityIDSHeadingSet_;
   p->ChequesDetailHeadingSet_ = ChequesDetailHeadingSet_;
   p->ChequesListHeadingSet_ = ChequesListHeadingSet_;
   p->GuaranteeListHeading_ = GuaranteeListHeading_;
   p->GuarResetListHeading_ = GuarResetListHeading_;
   p->LV_RRIF_AllocHeading_ = LV_RRIF_AllocHeading_;
   p->LV_RRIF_Heading_ = LV_RRIF_Heading_;
   p->GuaranteeRedDetailLeft_ = GuaranteeRedDetailLeft_;
   p->GuaranteeRedDetailTop_ = GuaranteeRedDetailTop_;
   p->TaxRatesHeadingSet_ = TaxRatesHeadingSet_;
   p->RESPInfoHeadingSet_ = RESPInfoHeadingSet_;
   p->RESPTransactionHeadingSet_ = RESPTransactionHeadingSet_;
   p->LV_OneTimeAllocFundHeading_ = LV_OneTimeAllocFundHeading_;
   p->LV_OneTimeRRIFAllocHeading_ = LV_OneTimeRRIFAllocHeading_;
   p->LV_OneTimeRRIFFundHeading_ = LV_OneTimeRRIFFundHeading_;
   p->MinMaxListLeft_ = MinMaxListLeft_;
   p->MinMaxListTop_ = MinMaxListTop_;
   p->LV_OneTimeTradeAllocHeadingSet_ = LV_OneTimeTradeAllocHeadingSet_;
   p->LV_OneTimeTradeHeadingSet_ = LV_OneTimeTradeHeadingSet_;
   p->SplitCommissionDetailsHeadingSet_ = SplitCommissionDetailsHeadingSet_;
   p->TradeAllocationDetailsHeadingSet_ = TradeAllocationDetailsHeadingSet_;
   p->MultiContractsListHeading_ = MultiContractsListHeading_;
   p->HistoricalSysIndexHeadingSet_ = HistoricalSysIndexHeadingSet_;
   p->AddressMailingColumnSet_ = AddressMailingColumnSet_;
   p->SlsRepListHeading1_ = SlsRepListHeading1_;
   p->VerifySearchSNAPHeadingSet_ = VerifySearchSNAPHeadingSet_;
   p->AccountReviewHeadingSet_ = AccountReviewHeadingSet_;
   return(p);
}

BFDataField* dsi_ListViewHeading::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40000893: return ( &EntityListViewHeading_ ); break; // EntityListViewHeading
      case 40000894: return ( &SelectEntityListHeading_ ); break; // SelectEntityListHeading
      case 40000898: return ( &AccListHeading_ ); break; // AccListHeading
      case 40000971: return ( &DistributionHeadingSet_ ); break; // DistributionHeadingSet
      case 40000972: return ( &VerifySearchHeadingSet_ ); break; // VerifySearchHeadingSet
      case 40000974: return ( &FreeUnitHeadingSet_ ); break; // FreeUnitHeadingSet
      case 40000981: return ( &ACBListHeading_ ); break; // ACBListHeading
      case 40000982: return ( &TransactionHeading_ ); break; // TransactionHeading
      case 40000983: return ( &PendingHeading_ ); break; // PendingHeading
      case 40001094: return ( &HistoricalAccountHeadingSet_ ); break; // HistoricalAccountHeadingSet
      case 40001095: return ( &RemarksHeadingSet_ ); break; // RemarksHeadingSet
      case 40001101: return ( &BankInstructionHeading_ ); break; // BankInstructionHeading
      case 40001188: return ( &SystematicListHeading_ ); break; // SystematicListHeading
      case 40001189: return ( &SysAllocListHeading_ ); break; // SysAllocListHeading
      case 40001199: return ( &WhereUsedListHeading_ ); break; // WhereUsedListHeading
      case 40001200: return ( &ConfirmAwdHeading_ ); break; // ConfirmAwdHeading
      case 40001201: return ( &ConfirmTransHeading_ ); break; // ConfirmTransHeading
      case 40001202: return ( &ShareholderAddressHeadingSet_ ); break; // ShareholderAddressHeadingSet
      case 40001203: return ( &EntityAddressHeadingSet_ ); break; // EntityAddressHeadingSet
      case 40001204: return ( &AddressMailingHeadingSet_ ); break; // AddressMailingHeadingSet
      case 40001228: return ( &BankListHeadingSet_ ); break; // BankListHeadingSet
      case 40001313: return ( &BranchListHeading_ ); break; // BranchListHeading
      case 40001314: return ( &SlsRepListHeading_ ); break; // SlsRepListHeading
      case 40001317: return ( &DistributionHeadingSet1_ ); break; // DistributionHeadingSet1
      case 40001334: return ( &BrokerListHeading_ ); break; // BrokerListHeading
      case 40001405: return ( &ContractListHeading_ ); break; // ContractListHeading
      case 40001415: return ( &CertificateHeadingSet_ ); break; // CertificateHeadingSet
      case 40001417: return ( &IdentAcctAccountsHeadingSet_ ); break; // IdentAcctAccountsHeadingSet
      case 40001416: return ( &IdentAcctEntitiesHeadingSet_ ); break; // IdentAcctEntitiesHeadingSet
      case 40001206: return ( &EntityIDSHeadingSet_ ); break; // EntityIDSHeadingSet
      case 40001419: return ( &ChequesDetailHeadingSet_ ); break; // ChequesDetailHeadingSet
      case 40001418: return ( &ChequesListHeadingSet_ ); break; // ChequesListHeadingSet
      case 40001448: return ( &GuaranteeListHeading_ ); break; // GuaranteeListHeading
      case 40001447: return ( &GuarResetListHeading_ ); break; // GuarResetListHeading
      case 40001451: return ( &LV_RRIF_AllocHeading_ ); break; // LV_RRIF_AllocHeading
      case 40001450: return ( &LV_RRIF_Heading_ ); break; // LV_RRIF_Heading
      case 40001457: return ( &GuaranteeRedDetailLeft_ ); break; // GuaranteeRedDetailLeft
      case 40001456: return ( &GuaranteeRedDetailTop_ ); break; // GuaranteeRedDetailTop
      case 40001487: return ( &TaxRatesHeadingSet_ ); break; // TaxRatesHeadingSet
      case 40001488: return ( &RESPInfoHeadingSet_ ); break; // RESPInfoHeadingSet
      case 40001489: return ( &RESPTransactionHeadingSet_ ); break; // RESPTransactionHeadingSet
      case 40001187: return ( &LV_OneTimeAllocFundHeading_ ); break; // LV_OneTimeAllocFundHeading
      case 40001600: return ( &LV_OneTimeRRIFAllocHeading_ ); break; // LV_OneTimeRRIFAllocHeading
      case 40001601: return ( &LV_OneTimeRRIFFundHeading_ ); break; // LV_OneTimeRRIFFundHeading
      case 40001584: return ( &MinMaxListLeft_ ); break; // MinMaxListLeft
      case 40001583: return ( &MinMaxListTop_ ); break; // MinMaxListTop
      case 40001698: return ( &LV_OneTimeTradeAllocHeadingSet_ ); break; // LV_OneTimeTradeAllocHeadingSet
      case 40001699: return ( &LV_OneTimeTradeHeadingSet_ ); break; // LV_OneTimeTradeHeadingSet
      case 40002257: return ( &SplitCommissionDetailsHeadingSet_ ); break; // SplitCommissionDetailsHeadingSet
      case 40002258: return ( &TradeAllocationDetailsHeadingSet_ ); break; // TradeAllocationDetailsHeadingSet
      case 40002481: return ( &MultiContractsListHeading_ ); break; // MultiContractsListHeading
      case 40002578: return ( &HistoricalSysIndexHeadingSet_ ); break; // HistoricalSysIndexHeadingSet
      case 40002715: return ( &AddressMailingColumnSet_ ); break; // AddressMailingColumnSet
      case 40002736: return ( &SlsRepListHeading1_ ); break; // SlsRepListHeading1
      case 40002985: return ( &VerifySearchSNAPHeadingSet_ ); break; // VerifySearchSNAPHeadingSet
      case 40003061: return ( &AccountReviewHeadingSet_ ); break; // AccountReviewHeadingSet
   }
   return( NULL );
}

const BFDataField* dsi_ListViewHeading::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_ListViewHeading* >(this) )->getElement( id ) );
}

BFDataField* dsi_ListViewHeading::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 56 )
   {
      BFDataField* pField = aFlds_[iField];
      if( NULL == pField )
      {
         switch(iField)
         {
            case 0: aFlds_[0] = &EntityListViewHeading_; break;
            case 1: aFlds_[1] = &SelectEntityListHeading_; break;
            case 2: aFlds_[2] = &AccListHeading_; break;
            case 3: aFlds_[3] = &DistributionHeadingSet_; break;
            case 4: aFlds_[4] = &VerifySearchHeadingSet_; break;
            case 5: aFlds_[5] = &FreeUnitHeadingSet_; break;
            case 6: aFlds_[6] = &ACBListHeading_; break;
            case 7: aFlds_[7] = &TransactionHeading_; break;
            case 8: aFlds_[8] = &PendingHeading_; break;
            case 9: aFlds_[9] = &HistoricalAccountHeadingSet_; break;
            case 10: aFlds_[10] = &RemarksHeadingSet_; break;
            case 11: aFlds_[11] = &BankInstructionHeading_; break;
            case 12: aFlds_[12] = &SystematicListHeading_; break;
            case 13: aFlds_[13] = &SysAllocListHeading_; break;
            case 14: aFlds_[14] = &WhereUsedListHeading_; break;
            case 15: aFlds_[15] = &ConfirmAwdHeading_; break;
            case 16: aFlds_[16] = &ConfirmTransHeading_; break;
            case 17: aFlds_[17] = &ShareholderAddressHeadingSet_; break;
            case 18: aFlds_[18] = &EntityAddressHeadingSet_; break;
            case 19: aFlds_[19] = &AddressMailingHeadingSet_; break;
            case 20: aFlds_[20] = &BankListHeadingSet_; break;
            case 21: aFlds_[21] = &BranchListHeading_; break;
            case 22: aFlds_[22] = &SlsRepListHeading_; break;
            case 23: aFlds_[23] = &DistributionHeadingSet1_; break;
            case 24: aFlds_[24] = &BrokerListHeading_; break;
            case 25: aFlds_[25] = &ContractListHeading_; break;
            case 26: aFlds_[26] = &CertificateHeadingSet_; break;
            case 27: aFlds_[27] = &IdentAcctAccountsHeadingSet_; break;
            case 28: aFlds_[28] = &IdentAcctEntitiesHeadingSet_; break;
            case 29: aFlds_[29] = &EntityIDSHeadingSet_; break;
            case 30: aFlds_[30] = &ChequesDetailHeadingSet_; break;
            case 31: aFlds_[31] = &ChequesListHeadingSet_; break;
            case 32: aFlds_[32] = &GuaranteeListHeading_; break;
            case 33: aFlds_[33] = &GuarResetListHeading_; break;
            case 34: aFlds_[34] = &LV_RRIF_AllocHeading_; break;
            case 35: aFlds_[35] = &LV_RRIF_Heading_; break;
            case 36: aFlds_[36] = &GuaranteeRedDetailLeft_; break;
            case 37: aFlds_[37] = &GuaranteeRedDetailTop_; break;
            case 38: aFlds_[38] = &TaxRatesHeadingSet_; break;
            case 39: aFlds_[39] = &RESPInfoHeadingSet_; break;
            case 40: aFlds_[40] = &RESPTransactionHeadingSet_; break;
            case 41: aFlds_[41] = &LV_OneTimeAllocFundHeading_; break;
            case 42: aFlds_[42] = &LV_OneTimeRRIFAllocHeading_; break;
            case 43: aFlds_[43] = &LV_OneTimeRRIFFundHeading_; break;
            case 44: aFlds_[44] = &MinMaxListLeft_; break;
            case 45: aFlds_[45] = &MinMaxListTop_; break;
            case 46: aFlds_[46] = &LV_OneTimeTradeAllocHeadingSet_; break;
            case 47: aFlds_[47] = &LV_OneTimeTradeHeadingSet_; break;
            case 48: aFlds_[48] = &SplitCommissionDetailsHeadingSet_; break;
            case 49: aFlds_[49] = &TradeAllocationDetailsHeadingSet_; break;
            case 50: aFlds_[50] = &MultiContractsListHeading_; break;
            case 51: aFlds_[51] = &HistoricalSysIndexHeadingSet_; break;
            case 52: aFlds_[52] = &AddressMailingColumnSet_; break;
            case 53: aFlds_[53] = &SlsRepListHeading1_; break;
            case 54: aFlds_[54] = &VerifySearchSNAPHeadingSet_; break;
            case 55: aFlds_[55] = &AccountReviewHeadingSet_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_ListViewHeading::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_ListViewHeading* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_ListViewHeading::getLargestDefinedField( void ) const
{
   return( 60 );
}

unsigned long dsi_ListViewHeading::getDefinedByteLength( void ) const
{
   return( 2516 * sizeof( I_CHAR ) );
}

bool dsi_ListViewHeading::exists( const BFFieldId& id ) const
{
   return dsi_ListViewHeading::fieldExists( id );
}

bool dsi_ListViewHeading::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40000893: return( true );
      case 40000894: return( true );
      case 40000898: return( true );
      case 40000971: return( true );
      case 40000972: return( true );
      case 40000974: return( true );
      case 40000981: return( true );
      case 40000982: return( true );
      case 40000983: return( true );
      case 40001094: return( true );
      case 40001095: return( true );
      case 40001101: return( true );
      case 40001188: return( true );
      case 40001189: return( true );
      case 40001199: return( true );
      case 40001200: return( true );
      case 40001201: return( true );
      case 40001202: return( true );
      case 40001203: return( true );
      case 40001204: return( true );
      case 40001228: return( true );
      case 40001313: return( true );
      case 40001314: return( true );
      case 40001317: return( true );
      case 40001334: return( true );
      case 40001405: return( true );
      case 40001415: return( true );
      case 40001417: return( true );
      case 40001416: return( true );
      case 40001206: return( true );
      case 40001419: return( true );
      case 40001418: return( true );
      case 40001448: return( true );
      case 40001447: return( true );
      case 40001451: return( true );
      case 40001450: return( true );
      case 40001457: return( true );
      case 40001456: return( true );
      case 40001487: return( true );
      case 40001488: return( true );
      case 40001489: return( true );
      case 40001187: return( true );
      case 40001600: return( true );
      case 40001601: return( true );
      case 40001584: return( true );
      case 40001583: return( true );
      case 40001698: return( true );
      case 40001699: return( true );
      case 40002257: return( true );
      case 40002258: return( true );
      case 40002481: return( true );
      case 40002578: return( true );
      case 40002715: return( true );
      case 40002736: return( true );
      case 40002985: return( true );
      case 40003061: return( true );
   }
   return false;
}

