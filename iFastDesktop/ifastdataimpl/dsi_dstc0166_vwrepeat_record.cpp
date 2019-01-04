// BFDataImpl implementation file for DataSet DSTC0166.VWRepeat_Record
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0166_vwrepeat_record.h"


// This function creates an instance of dsi_DSTC0166_VWRepeat_Record
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0166_VWRepeat_Record() { return new dsi_DSTC0166_VWRepeat_Record; }

dsi_DSTC0166_VWRepeat_Record::dsi_DSTC0166_VWRepeat_Record()
: BFDataImpl( 40002618 )
, FundCode_( ifds::FundCode, &ifds::s_FldProp_FundCode )
, ClassCode_( ifds::ClassCode, &ifds::s_FldProp_ClassCode )
, FundCurrency_( ifds::FundCurrency, &ifds::s_FldProp_FundCurrency )
, SettledUnits_( ifds::SettledUnits, &ifds::s_FldProp_SettledUnits )
, SettledValue_( ifds::SettledValue, &ifds::s_FldProp_SettledValue )
, UnsettledUnits_( ifds::UnsettledUnits, &ifds::s_FldProp_UnsettledUnits )
, UnsettledValue_( ifds::UnsettledValue, &ifds::s_FldProp_UnsettledValue )
, SettledValueAcctCurr_( ifds::SettledValueAcctCurr, &ifds::s_FldProp_SettledValueAcctCurr )
, TradedUnits_( ifds::TradedUnits, &ifds::s_FldProp_TradedUnits )
, CombValueFundCurr_( ifds::CombValueFundCurr, &ifds::s_FldProp_CombValueFundCurr )
, CombValueAcctCurr_( ifds::CombValueAcctCurr, &ifds::s_FldProp_CombValueAcctCurr )
, ExchRate_( ifds::ExchRate, &ifds::s_FldProp_ExchRate )
, PendingTradesExist_( ifds::PendingTradesExist, &ifds::s_FldProp_PendingTradesExist )
, PYEUnits_( ifds::PYEUnits, &ifds::s_FldProp_PYEUnits )
, PYEValue_( ifds::PYEValue, &ifds::s_FldProp_PYEValue )
, LastEvent_( ifds::LastEvent, &ifds::s_FldProp_LastEvent )
, AsAtDate_( ifds::AsAtDate, &ifds::s_FldProp_AsAtDate )
, FundNAV_( ifds::FundNAV, &ifds::s_FldProp_FundNAV )
, SponsorName_( ifds::SponsorName, &ifds::s_FldProp_SponsorName )
, SponsorCode_( ifds::SponsorCode, &ifds::s_FldProp_SponsorCode )
, FundName_( ifds::FundName, &ifds::s_FldProp_FundName )
, DistribPayType_( ifds::DistribPayType, &ifds::s_FldProp_DistribPayType )
{
   cFields_ = 22;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0166_VWRepeat_Record::~dsi_DSTC0166_VWRepeat_Record()
{
}

BFDataImpl* dsi_DSTC0166_VWRepeat_Record::clone()
{
   dsi_DSTC0166_VWRepeat_Record* p = new dsi_DSTC0166_VWRepeat_Record;
   p->FundCode_ = FundCode_;
   p->ClassCode_ = ClassCode_;
   p->FundCurrency_ = FundCurrency_;
   p->SettledUnits_ = SettledUnits_;
   p->SettledValue_ = SettledValue_;
   p->UnsettledUnits_ = UnsettledUnits_;
   p->UnsettledValue_ = UnsettledValue_;
   p->SettledValueAcctCurr_ = SettledValueAcctCurr_;
   p->TradedUnits_ = TradedUnits_;
   p->CombValueFundCurr_ = CombValueFundCurr_;
   p->CombValueAcctCurr_ = CombValueAcctCurr_;
   p->ExchRate_ = ExchRate_;
   p->PendingTradesExist_ = PendingTradesExist_;
   p->PYEUnits_ = PYEUnits_;
   p->PYEValue_ = PYEValue_;
   p->LastEvent_ = LastEvent_;
   p->AsAtDate_ = AsAtDate_;
   p->FundNAV_ = FundNAV_;
   p->SponsorName_ = SponsorName_;
   p->SponsorCode_ = SponsorCode_;
   p->FundName_ = FundName_;
   p->DistribPayType_ = DistribPayType_;
   return(p);
}

BFDataField* dsi_DSTC0166_VWRepeat_Record::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40000049: return ( &FundCode_ ); break; // FundCode
      case 40000050: return ( &ClassCode_ ); break; // ClassCode
      case 40001948: return ( &FundCurrency_ ); break; // FundCurrency
      case 40000401: return ( &SettledUnits_ ); break; // SettledUnits
      case 40000402: return ( &SettledValue_ ); break; // SettledValue
      case 40000403: return ( &UnsettledUnits_ ); break; // UnsettledUnits
      case 40000404: return ( &UnsettledValue_ ); break; // UnsettledValue
      case 40001316: return ( &SettledValueAcctCurr_ ); break; // SettledValueAcctCurr
      case 40002070: return ( &TradedUnits_ ); break; // TradedUnits
      case 40002071: return ( &CombValueFundCurr_ ); break; // CombValueFundCurr
      case 40002072: return ( &CombValueAcctCurr_ ); break; // CombValueAcctCurr
      case 40000456: return ( &ExchRate_ ); break; // ExchRate
      case 40002075: return ( &PendingTradesExist_ ); break; // PendingTradesExist
      case 40000406: return ( &PYEUnits_ ); break; // PYEUnits
      case 40000407: return ( &PYEValue_ ); break; // PYEValue
      case 40000978: return ( &LastEvent_ ); break; // LastEvent
      case 40000408: return ( &AsAtDate_ ); break; // AsAtDate
      case 40000405: return ( &FundNAV_ ); break; // FundNAV
      case 40002626: return ( &SponsorName_ ); break; // SponsorName
      case 40002627: return ( &SponsorCode_ ); break; // SponsorCode
      case 40001841: return ( &FundName_ ); break; // FundName
      case 40002628: return ( &DistribPayType_ ); break; // DistribPayType
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0166_VWRepeat_Record::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0166_VWRepeat_Record* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0166_VWRepeat_Record::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 22 )
   {
      BFDataField* pField = aFlds_[iField];
      if( NULL == pField )
      {
         switch(iField)
         {
            case 0: aFlds_[0] = &FundCode_; break;
            case 1: aFlds_[1] = &ClassCode_; break;
            case 2: aFlds_[2] = &FundCurrency_; break;
            case 3: aFlds_[3] = &SettledUnits_; break;
            case 4: aFlds_[4] = &SettledValue_; break;
            case 5: aFlds_[5] = &UnsettledUnits_; break;
            case 6: aFlds_[6] = &UnsettledValue_; break;
            case 7: aFlds_[7] = &SettledValueAcctCurr_; break;
            case 8: aFlds_[8] = &TradedUnits_; break;
            case 9: aFlds_[9] = &CombValueFundCurr_; break;
            case 10: aFlds_[10] = &CombValueAcctCurr_; break;
            case 11: aFlds_[11] = &ExchRate_; break;
            case 12: aFlds_[12] = &PendingTradesExist_; break;
            case 13: aFlds_[13] = &PYEUnits_; break;
            case 14: aFlds_[14] = &PYEValue_; break;
            case 15: aFlds_[15] = &LastEvent_; break;
            case 16: aFlds_[16] = &AsAtDate_; break;
            case 17: aFlds_[17] = &FundNAV_; break;
            case 18: aFlds_[18] = &SponsorName_; break;
            case 19: aFlds_[19] = &SponsorCode_; break;
            case 20: aFlds_[20] = &FundName_; break;
            case 21: aFlds_[21] = &DistribPayType_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0166_VWRepeat_Record::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0166_VWRepeat_Record* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0166_VWRepeat_Record::getLargestDefinedField( void ) const
{
   return( 200 );
}

unsigned long dsi_DSTC0166_VWRepeat_Record::getDefinedByteLength( void ) const
{
   return( 971 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0166_VWRepeat_Record::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0166_VWRepeat_Record::fieldExists( id );
}

bool dsi_DSTC0166_VWRepeat_Record::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40000049: return( true );
      case 40000050: return( true );
      case 40001948: return( true );
      case 40000401: return( true );
      case 40000402: return( true );
      case 40000403: return( true );
      case 40000404: return( true );
      case 40001316: return( true );
      case 40002070: return( true );
      case 40002071: return( true );
      case 40002072: return( true );
      case 40000456: return( true );
      case 40002075: return( true );
      case 40000406: return( true );
      case 40000407: return( true );
      case 40000978: return( true );
      case 40000408: return( true );
      case 40000405: return( true );
      case 40002626: return( true );
      case 40002627: return( true );
      case 40001841: return( true );
      case 40002628: return( true );
   }
   return false;
}

