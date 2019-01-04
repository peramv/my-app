// BFDataImpl implementation file for DataSet DSTC0197.VW
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0197_vw.h"


// This function creates an instance of dsi_DSTC0197_VW
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0197_VW() { return new dsi_DSTC0197_VW; }

dsi_DSTC0197_VW::dsi_DSTC0197_VW()
: BFDataImpl( 40002933, 40002934 )
, StopDate_( ifds::StopDate, &ifds::s_FldProp_StopDate )
, FeeType_( ifds::FeeType, &ifds::s_FldProp_FeeType )
, Rate_( ifds::Rate, &ifds::s_FldProp_Rate )
, MinFee_( ifds::MinFee, &ifds::s_FldProp_MinFee )
, MaxFee_( ifds::MaxFee, &ifds::s_FldProp_MaxFee )
, AllowOverwrite_( ifds::AllowOverwrite, &ifds::s_FldProp_AllowOverwrite )
, FeeParamRid_( ifds::FeeParamRid, &ifds::s_FldProp_FeeParamRid )
, MoreAvailable_( ifds::MoreAvailable, &ifds::s_FldProp_MoreAvailable )
, NextKey_( ifds::NextKey, &ifds::s_FldProp_NextKey )
, FundCode_( ifds::FundCode, &ifds::s_FldProp_FundCode )
, ClassCode_( ifds::ClassCode, &ifds::s_FldProp_ClassCode )
, FeeCode_( ifds::FeeCode, &ifds::s_FldProp_FeeCode )
, EffectiveDate_( ifds::EffectiveDate, &ifds::s_FldProp_EffectiveDate )
, CommGroup_( ifds::CommGroup, &ifds::s_FldProp_CommGroup )
, DuplicateExist_( ifds::DuplicateExist, &ifds::s_FldProp_DuplicateExist )
, FeeModelCode_( ifds::FeeModelCode, &ifds::s_FldProp_FeeModelCode )
, ChargeOption_( ifds::ChargeOption, &ifds::s_FldProp_ChargeOption )
, Currency_( ifds::Currency, &ifds::s_FldProp_Currency )
, DistributionChannel_( ifds::DistributionChannel, &ifds::s_FldProp_DistributionChannel )
, RepeatCount_( ifds::RepeatCount, &ifds::s_FldProp_RepeatCount )
{
   cFields_ = 20;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0197_VW::~dsi_DSTC0197_VW()
{
}

BFDataImpl* dsi_DSTC0197_VW::clone()
{
   dsi_DSTC0197_VW* p = new dsi_DSTC0197_VW;
   p->StopDate_ = StopDate_;
   p->FeeType_ = FeeType_;
   p->Rate_ = Rate_;
   p->MinFee_ = MinFee_;
   p->MaxFee_ = MaxFee_;
   p->AllowOverwrite_ = AllowOverwrite_;
   p->FeeParamRid_ = FeeParamRid_;
   p->MoreAvailable_ = MoreAvailable_;
   p->NextKey_ = NextKey_;
   p->FundCode_ = FundCode_;
   p->ClassCode_ = ClassCode_;
   p->FeeCode_ = FeeCode_;
   p->EffectiveDate_ = EffectiveDate_;
   p->CommGroup_ = CommGroup_;
   p->DuplicateExist_ = DuplicateExist_;
   p->FeeModelCode_ = FeeModelCode_;
   p->ChargeOption_ = ChargeOption_;
   p->Currency_ = Currency_;
   p->DistributionChannel_ = DistributionChannel_;
   p->RepeatCount_ = RepeatCount_;
   return(p);
}

BFDataField* dsi_DSTC0197_VW::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40000279: return ( &StopDate_ ); break; // StopDate
      case 40000728: return ( &FeeType_ ); break; // FeeType
      case 40002919: return ( &Rate_ ); break; // Rate
      case 40002899: return ( &MinFee_ ); break; // MinFee
      case 40001674: return ( &MaxFee_ ); break; // MaxFee
      case 40002935: return ( &AllowOverwrite_ ); break; // AllowOverwrite
      case 40002946: return ( &FeeParamRid_ ); break; // FeeParamRid
      case 40000126: return ( &MoreAvailable_ ); break; // MoreAvailable
      case 40000029: return ( &NextKey_ ); break; // NextKey
      case 40000049: return ( &FundCode_ ); break; // FundCode
      case 40000050: return ( &ClassCode_ ); break; // ClassCode
      case 40002917: return ( &FeeCode_ ); break; // FeeCode
      case 40000327: return ( &EffectiveDate_ ); break; // EffectiveDate
      case 40003519: return ( &CommGroup_ ); break; // CommGroup
      case 40003854: return ( &DuplicateExist_ ); break; // DuplicateExist
      case 40004584: return ( &FeeModelCode_ ); break; // FeeModelCode
      case 40004602: return ( &ChargeOption_ ); break; // ChargeOption
      case 40000180: return ( &Currency_ ); break; // Currency
      case 40006421: return ( &DistributionChannel_ ); break; // DistributionChannel
      case 40000120: return ( &RepeatCount_ ); break; // RepeatCount
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0197_VW::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0197_VW* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0197_VW::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 20 )
   {
      BFDataField* pField = aFlds_[iField];
      if( NULL == pField )
      {
         switch(iField)
         {
            case 0: aFlds_[0] = &StopDate_; break;
            case 1: aFlds_[1] = &FeeType_; break;
            case 2: aFlds_[2] = &Rate_; break;
            case 3: aFlds_[3] = &MinFee_; break;
            case 4: aFlds_[4] = &MaxFee_; break;
            case 5: aFlds_[5] = &AllowOverwrite_; break;
            case 6: aFlds_[6] = &FeeParamRid_; break;
            case 7: aFlds_[7] = &MoreAvailable_; break;
            case 8: aFlds_[8] = &NextKey_; break;
            case 9: aFlds_[9] = &FundCode_; break;
            case 10: aFlds_[10] = &ClassCode_; break;
            case 11: aFlds_[11] = &FeeCode_; break;
            case 12: aFlds_[12] = &EffectiveDate_; break;
            case 13: aFlds_[13] = &CommGroup_; break;
            case 14: aFlds_[14] = &DuplicateExist_; break;
            case 15: aFlds_[15] = &FeeModelCode_; break;
            case 16: aFlds_[16] = &ChargeOption_; break;
            case 17: aFlds_[17] = &Currency_; break;
            case 18: aFlds_[18] = &DistributionChannel_; break;
            case 19: aFlds_[19] = &RepeatCount_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0197_VW::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0197_VW* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0197_VW::getLargestDefinedField( void ) const
{
   return( 200 );
}

unsigned long dsi_DSTC0197_VW::getDefinedByteLength( void ) const
{
   return( 1132 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0197_VW::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0197_VW::fieldExists( id );
}

bool dsi_DSTC0197_VW::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40000279: return( true );
      case 40000728: return( true );
      case 40002919: return( true );
      case 40002899: return( true );
      case 40001674: return( true );
      case 40002935: return( true );
      case 40002946: return( true );
      case 40000126: return( true );
      case 40000029: return( true );
      case 40000049: return( true );
      case 40000050: return( true );
      case 40002917: return( true );
      case 40000327: return( true );
      case 40003519: return( true );
      case 40003854: return( true );
      case 40004584: return( true );
      case 40004602: return( true );
      case 40000180: return( true );
      case 40006421: return( true );
      case 40000120: return( true );
   }
   return false;
}

