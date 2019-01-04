// BFDataImpl implementation file for DataSet DSTC0058.VWRepeat_Record
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0058_vwrepeat_record.h"


// This function creates an instance of dsi_DSTC0058_VWRepeat_Record
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0058_VWRepeat_Record() { return new dsi_DSTC0058_VWRepeat_Record; }

dsi_DSTC0058_VWRepeat_Record::dsi_DSTC0058_VWRepeat_Record()
: BFDataImpl( 40000715 )
, TransType_( ifds::TransType, &ifds::s_FldProp_TransType )
, TransTypeDesc_( ifds::TransTypeDesc, &ifds::s_FldProp_TransTypeDesc )
, FundCode_( ifds::FundCode, &ifds::s_FldProp_FundCode )
, ClassCode_( ifds::ClassCode, &ifds::s_FldProp_ClassCode )
, AllocPercentage_( ifds::AllocPercentage, &ifds::s_FldProp_AllocPercentage )
, EffectiveDate_( ifds::EffectiveDate, &ifds::s_FldProp_EffectiveDate )
, DistribDetlVer_( ifds::DistribDetlVer, &ifds::s_FldProp_DistribDetlVer )
, DistribDetlRid_( ifds::DistribDetlRid, &ifds::s_FldProp_DistribDetlRid )
, Level_( ifds::Level, &ifds::s_FldProp_Level )
, AccountNum_( ifds::AccountNum, &ifds::s_FldProp_AccountNum )
, FrngSweep_( ifds::FrngSweep, &ifds::s_FldProp_FrngSweep )
, FundGroup_( ifds::FundGroup, &ifds::s_FldProp_FundGroup )
, RebalPrcnt_( ifds::RebalPrcnt, &ifds::s_FldProp_RebalPrcnt )
, AMSCurrency_( ifds::AMSCurrency, &ifds::s_FldProp_AMSCurrency )
, FELComm_( ifds::FELComm, &ifds::s_FldProp_FELComm )
, FELCommType_( ifds::FELCommType, &ifds::s_FldProp_FELCommType )
{
   cFields_ = 16;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0058_VWRepeat_Record::~dsi_DSTC0058_VWRepeat_Record()
{
}

BFDataImpl* dsi_DSTC0058_VWRepeat_Record::clone()
{
   dsi_DSTC0058_VWRepeat_Record* p = new dsi_DSTC0058_VWRepeat_Record;
   p->TransType_ = TransType_;
   p->TransTypeDesc_ = TransTypeDesc_;
   p->FundCode_ = FundCode_;
   p->ClassCode_ = ClassCode_;
   p->AllocPercentage_ = AllocPercentage_;
   p->EffectiveDate_ = EffectiveDate_;
   p->DistribDetlVer_ = DistribDetlVer_;
   p->DistribDetlRid_ = DistribDetlRid_;
   p->Level_ = Level_;
   p->AccountNum_ = AccountNum_;
   p->FrngSweep_ = FrngSweep_;
   p->FundGroup_ = FundGroup_;
   p->RebalPrcnt_ = RebalPrcnt_;
   p->AMSCurrency_ = AMSCurrency_;
   p->FELComm_ = FELComm_;
   p->FELCommType_ = FELCommType_;
   return(p);
}

BFDataField* dsi_DSTC0058_VWRepeat_Record::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40000095: return ( &TransType_ ); break; // TransType
      case 40000337: return ( &TransTypeDesc_ ); break; // TransTypeDesc
      case 40000049: return ( &FundCode_ ); break; // FundCode
      case 40000050: return ( &ClassCode_ ); break; // ClassCode
      case 40001035: return ( &AllocPercentage_ ); break; // AllocPercentage
      case 40000327: return ( &EffectiveDate_ ); break; // EffectiveDate
      case 40000949: return ( &DistribDetlVer_ ); break; // DistribDetlVer
      case 40000950: return ( &DistribDetlRid_ ); break; // DistribDetlRid
      case 40000977: return ( &Level_ ); break; // Level
      case 40000040: return ( &AccountNum_ ); break; // AccountNum
      case 40001778: return ( &FrngSweep_ ); break; // FrngSweep
      case 40002031: return ( &FundGroup_ ); break; // FundGroup
      case 40003815: return ( &RebalPrcnt_ ); break; // RebalPrcnt
      case 40003816: return ( &AMSCurrency_ ); break; // AMSCurrency
      case 40005949: return ( &FELComm_ ); break; // FELComm
      case 40005950: return ( &FELCommType_ ); break; // FELCommType
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0058_VWRepeat_Record::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0058_VWRepeat_Record* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0058_VWRepeat_Record::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 16 )
   {
      BFDataField* pField = aFlds_[iField];
      if( NULL == pField )
      {
         switch(iField)
         {
            case 0: aFlds_[0] = &TransType_; break;
            case 1: aFlds_[1] = &TransTypeDesc_; break;
            case 2: aFlds_[2] = &FundCode_; break;
            case 3: aFlds_[3] = &ClassCode_; break;
            case 4: aFlds_[4] = &AllocPercentage_; break;
            case 5: aFlds_[5] = &EffectiveDate_; break;
            case 6: aFlds_[6] = &DistribDetlVer_; break;
            case 7: aFlds_[7] = &DistribDetlRid_; break;
            case 8: aFlds_[8] = &Level_; break;
            case 9: aFlds_[9] = &AccountNum_; break;
            case 10: aFlds_[10] = &FrngSweep_; break;
            case 11: aFlds_[11] = &FundGroup_; break;
            case 12: aFlds_[12] = &RebalPrcnt_; break;
            case 13: aFlds_[13] = &AMSCurrency_; break;
            case 14: aFlds_[14] = &FELComm_; break;
            case 15: aFlds_[15] = &FELCommType_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0058_VWRepeat_Record::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0058_VWRepeat_Record* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0058_VWRepeat_Record::getLargestDefinedField( void ) const
{
   return( 200 );
}

unsigned long dsi_DSTC0058_VWRepeat_Record::getDefinedByteLength( void ) const
{
   return( 751 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0058_VWRepeat_Record::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0058_VWRepeat_Record::fieldExists( id );
}

bool dsi_DSTC0058_VWRepeat_Record::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40000095: return( true );
      case 40000337: return( true );
      case 40000049: return( true );
      case 40000050: return( true );
      case 40001035: return( true );
      case 40000327: return( true );
      case 40000949: return( true );
      case 40000950: return( true );
      case 40000977: return( true );
      case 40000040: return( true );
      case 40001778: return( true );
      case 40002031: return( true );
      case 40003815: return( true );
      case 40003816: return( true );
      case 40005949: return( true );
      case 40005950: return( true );
   }
   return false;
}

