// BFDataImpl implementation file for DataSet DSTC0088.VWRepeat_Record
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0088_vwrepeat_record.h"


// This function creates an instance of dsi_DSTC0088_VWRepeat_Record
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0088_VWRepeat_Record() { return new dsi_DSTC0088_VWRepeat_Record; }

dsi_DSTC0088_VWRepeat_Record::dsi_DSTC0088_VWRepeat_Record()
: BFDataImpl( 40001073 )
, GroupName_( ifds::GroupName, &ifds::s_FldProp_GroupName )
, rxGroupCode_( ifds::rxGroupCode, &ifds::s_FldProp_rxGroupCode )
, StopPurchase_( ifds::StopPurchase, &ifds::s_FldProp_StopPurchase )
, StopRed_( ifds::StopRed, &ifds::s_FldProp_StopRed )
, GroupType_( ifds::GroupType, &ifds::s_FldProp_GroupType )
, AccConfOverride_( ifds::AccConfOverride, &ifds::s_FldProp_AccConfOverride )
, StopXferIn_( ifds::StopXferIn, &ifds::s_FldProp_StopXferIn )
, StopXferOut_( ifds::StopXferOut, &ifds::s_FldProp_StopXferOut )
, AMS_( ifds::AMS, &ifds::s_FldProp_AMS )
, BrokerCode_( ifds::BrokerCode, &ifds::s_FldProp_BrokerCode )
, BranchCode_( ifds::BranchCode, &ifds::s_FldProp_BranchCode )
, SalesRepCode_( ifds::SalesRepCode, &ifds::s_FldProp_SalesRepCode )
, EffectiveDate_( ifds::EffectiveDate, &ifds::s_FldProp_EffectiveDate )
, TaxType_( ifds::TaxType, &ifds::s_FldProp_TaxType )
, FeeChrLevel_( ifds::FeeChrLevel, &ifds::s_FldProp_FeeChrLevel )
, SetupFee_( ifds::SetupFee, &ifds::s_FldProp_SetupFee )
, ContributionLimit_( ifds::ContributionLimit, &ifds::s_FldProp_ContributionLimit )
, SWPMinBal_( ifds::SWPMinBal, &ifds::s_FldProp_SWPMinBal )
, LockedInCode_( ifds::LockedInCode, &ifds::s_FldProp_LockedInCode )
, SuppConfirm_( ifds::SuppConfirm, &ifds::s_FldProp_SuppConfirm )
, HasGWOContract_( ifds::HasGWOContract, &ifds::s_FldProp_HasGWOContract )
{
   cFields_ = 21;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0088_VWRepeat_Record::~dsi_DSTC0088_VWRepeat_Record()
{
}

BFDataImpl* dsi_DSTC0088_VWRepeat_Record::clone()
{
   dsi_DSTC0088_VWRepeat_Record* p = new dsi_DSTC0088_VWRepeat_Record;
   p->GroupName_ = GroupName_;
   p->rxGroupCode_ = rxGroupCode_;
   p->StopPurchase_ = StopPurchase_;
   p->StopRed_ = StopRed_;
   p->GroupType_ = GroupType_;
   p->AccConfOverride_ = AccConfOverride_;
   p->StopXferIn_ = StopXferIn_;
   p->StopXferOut_ = StopXferOut_;
   p->AMS_ = AMS_;
   p->BrokerCode_ = BrokerCode_;
   p->BranchCode_ = BranchCode_;
   p->SalesRepCode_ = SalesRepCode_;
   p->EffectiveDate_ = EffectiveDate_;
   p->TaxType_ = TaxType_;
   p->FeeChrLevel_ = FeeChrLevel_;
   p->SetupFee_ = SetupFee_;
   p->ContributionLimit_ = ContributionLimit_;
   p->SWPMinBal_ = SWPMinBal_;
   p->LockedInCode_ = LockedInCode_;
   p->SuppConfirm_ = SuppConfirm_;
   p->HasGWOContract_ = HasGWOContract_;
   return(p);
}

BFDataField* dsi_DSTC0088_VWRepeat_Record::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40001075: return ( &GroupName_ ); break; // GroupName
      case 40001074: return ( &rxGroupCode_ ); break; // rxGroupCode
      case 40000699: return ( &StopPurchase_ ); break; // StopPurchase
      case 40000593: return ( &StopRed_ ); break; // StopRed
      case 40001076: return ( &GroupType_ ); break; // GroupType
      case 40001077: return ( &AccConfOverride_ ); break; // AccConfOverride
      case 40000197: return ( &StopXferIn_ ); break; // StopXferIn
      case 40000198: return ( &StopXferOut_ ); break; // StopXferOut
      case 40001078: return ( &AMS_ ); break; // AMS
      case 40000044: return ( &BrokerCode_ ); break; // BrokerCode
      case 40000045: return ( &BranchCode_ ); break; // BranchCode
      case 40000046: return ( &SalesRepCode_ ); break; // SalesRepCode
      case 40000327: return ( &EffectiveDate_ ); break; // EffectiveDate
      case 40000134: return ( &TaxType_ ); break; // TaxType
      case 40001102: return ( &FeeChrLevel_ ); break; // FeeChrLevel
      case 40001532: return ( &SetupFee_ ); break; // SetupFee
      case 40001886: return ( &ContributionLimit_ ); break; // ContributionLimit
      case 40002097: return ( &SWPMinBal_ ); break; // SWPMinBal
      case 40003685: return ( &LockedInCode_ ); break; // LockedInCode
      case 40005161: return ( &SuppConfirm_ ); break; // SuppConfirm
      case 40006288: return ( &HasGWOContract_ ); break; // HasGWOContract
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0088_VWRepeat_Record::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0088_VWRepeat_Record* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0088_VWRepeat_Record::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 21 )
   {
      BFDataField* pField = aFlds_[iField];
      if( NULL == pField )
      {
         switch(iField)
         {
            case 0: aFlds_[0] = &GroupName_; break;
            case 1: aFlds_[1] = &rxGroupCode_; break;
            case 2: aFlds_[2] = &StopPurchase_; break;
            case 3: aFlds_[3] = &StopRed_; break;
            case 4: aFlds_[4] = &GroupType_; break;
            case 5: aFlds_[5] = &AccConfOverride_; break;
            case 6: aFlds_[6] = &StopXferIn_; break;
            case 7: aFlds_[7] = &StopXferOut_; break;
            case 8: aFlds_[8] = &AMS_; break;
            case 9: aFlds_[9] = &BrokerCode_; break;
            case 10: aFlds_[10] = &BranchCode_; break;
            case 11: aFlds_[11] = &SalesRepCode_; break;
            case 12: aFlds_[12] = &EffectiveDate_; break;
            case 13: aFlds_[13] = &TaxType_; break;
            case 14: aFlds_[14] = &FeeChrLevel_; break;
            case 15: aFlds_[15] = &SetupFee_; break;
            case 16: aFlds_[16] = &ContributionLimit_; break;
            case 17: aFlds_[17] = &SWPMinBal_; break;
            case 18: aFlds_[18] = &LockedInCode_; break;
            case 19: aFlds_[19] = &SuppConfirm_; break;
            case 20: aFlds_[20] = &HasGWOContract_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0088_VWRepeat_Record::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0088_VWRepeat_Record* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0088_VWRepeat_Record::getLargestDefinedField( void ) const
{
   return( 60 );
}

unsigned long dsi_DSTC0088_VWRepeat_Record::getDefinedByteLength( void ) const
{
   return( 681 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0088_VWRepeat_Record::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0088_VWRepeat_Record::fieldExists( id );
}

bool dsi_DSTC0088_VWRepeat_Record::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40001075: return( true );
      case 40001074: return( true );
      case 40000699: return( true );
      case 40000593: return( true );
      case 40001076: return( true );
      case 40001077: return( true );
      case 40000197: return( true );
      case 40000198: return( true );
      case 40001078: return( true );
      case 40000044: return( true );
      case 40000045: return( true );
      case 40000046: return( true );
      case 40000327: return( true );
      case 40000134: return( true );
      case 40001102: return( true );
      case 40001532: return( true );
      case 40001886: return( true );
      case 40002097: return( true );
      case 40003685: return( true );
      case 40005161: return( true );
      case 40006288: return( true );
   }
   return false;
}

