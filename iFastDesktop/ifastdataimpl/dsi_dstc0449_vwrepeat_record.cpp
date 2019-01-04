// BFDataImpl implementation file for DataSet DSTC0449.VWRepeat_Record
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0449_vwrepeat_record.h"


// This function creates an instance of dsi_DSTC0449_VWRepeat_Record
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0449_VWRepeat_Record() { return new dsi_DSTC0449_VWRepeat_Record; }

dsi_DSTC0449_VWRepeat_Record::dsi_DSTC0449_VWRepeat_Record()
: BFDataImpl( 40007079 )
, FeeModelType_( ifds::FeeModelType, &ifds::s_FldProp_FeeModelType )
, HoldingEntityAppl_( ifds::HoldingEntityAppl, &ifds::s_FldProp_HoldingEntityAppl )
, CalcCurrencyAppl_( ifds::CalcCurrencyAppl, &ifds::s_FldProp_CalcCurrencyAppl )
, FundGroupType_( ifds::FundGroupType, &ifds::s_FldProp_FundGroupType )
, FundGrpTypeList_( ifds::FundGrpTypeList, &ifds::s_FldProp_FundGrpTypeList )
, AggregationMethodList_( ifds::AggregationMethodList, &ifds::s_FldProp_AggregationMethodList )
, CalcRateTypeList_( ifds::CalcRateTypeList, &ifds::s_FldProp_CalcRateTypeList )
, FeeModelOptionList_( ifds::FeeModelOptionList, &ifds::s_FldProp_FeeModelOptionList )
, SchedSetupFreqAppl_( ifds::SchedSetupFreqAppl, &ifds::s_FldProp_SchedSetupFreqAppl )
, PrefixCode_( ifds::PrefixCode, &ifds::s_FldProp_PrefixCode )
, AutoGenOverride_( ifds::AutoGenOverride, &ifds::s_FldProp_AutoGenOverride )
, AllowCopy_( ifds::AllowCopy, &ifds::s_FldProp_AllowCopy )
, SameDlrBrnRep_( ifds::SameDlrBrnRep, &ifds::s_FldProp_SameDlrBrnRep )
{
   cFields_ = 13;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0449_VWRepeat_Record::~dsi_DSTC0449_VWRepeat_Record()
{
}

BFDataImpl* dsi_DSTC0449_VWRepeat_Record::clone()
{
   dsi_DSTC0449_VWRepeat_Record* p = new dsi_DSTC0449_VWRepeat_Record;
   p->FeeModelType_ = FeeModelType_;
   p->HoldingEntityAppl_ = HoldingEntityAppl_;
   p->CalcCurrencyAppl_ = CalcCurrencyAppl_;
   p->FundGroupType_ = FundGroupType_;
   p->FundGrpTypeList_ = FundGrpTypeList_;
   p->AggregationMethodList_ = AggregationMethodList_;
   p->CalcRateTypeList_ = CalcRateTypeList_;
   p->FeeModelOptionList_ = FeeModelOptionList_;
   p->SchedSetupFreqAppl_ = SchedSetupFreqAppl_;
   p->PrefixCode_ = PrefixCode_;
   p->AutoGenOverride_ = AutoGenOverride_;
   p->AllowCopy_ = AllowCopy_;
   p->SameDlrBrnRep_ = SameDlrBrnRep_;
   return(p);
}

BFDataField* dsi_DSTC0449_VWRepeat_Record::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40007025: return ( &FeeModelType_ ); break; // FeeModelType
      case 40007080: return ( &HoldingEntityAppl_ ); break; // HoldingEntityAppl
      case 40007081: return ( &CalcCurrencyAppl_ ); break; // CalcCurrencyAppl
      case 40001477: return ( &FundGroupType_ ); break; // FundGroupType
      case 40007082: return ( &FundGrpTypeList_ ); break; // FundGrpTypeList
      case 40007083: return ( &AggregationMethodList_ ); break; // AggregationMethodList
      case 40007084: return ( &CalcRateTypeList_ ); break; // CalcRateTypeList
      case 40007085: return ( &FeeModelOptionList_ ); break; // FeeModelOptionList
      case 40007086: return ( &SchedSetupFreqAppl_ ); break; // SchedSetupFreqAppl
      case 40007250: return ( &PrefixCode_ ); break; // PrefixCode
      case 40007249: return ( &AutoGenOverride_ ); break; // AutoGenOverride
      case 40007571: return ( &AllowCopy_ ); break; // AllowCopy
      case 40007572: return ( &SameDlrBrnRep_ ); break; // SameDlrBrnRep
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0449_VWRepeat_Record::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0449_VWRepeat_Record* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0449_VWRepeat_Record::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 13 )
   {
      BFDataField* pField = aFlds_[iField];
      if( NULL == pField )
      {
         switch(iField)
         {
            case 0: aFlds_[0] = &FeeModelType_; break;
            case 1: aFlds_[1] = &HoldingEntityAppl_; break;
            case 2: aFlds_[2] = &CalcCurrencyAppl_; break;
            case 3: aFlds_[3] = &FundGroupType_; break;
            case 4: aFlds_[4] = &FundGrpTypeList_; break;
            case 5: aFlds_[5] = &AggregationMethodList_; break;
            case 6: aFlds_[6] = &CalcRateTypeList_; break;
            case 7: aFlds_[7] = &FeeModelOptionList_; break;
            case 8: aFlds_[8] = &SchedSetupFreqAppl_; break;
            case 9: aFlds_[9] = &PrefixCode_; break;
            case 10: aFlds_[10] = &AutoGenOverride_; break;
            case 11: aFlds_[11] = &AllowCopy_; break;
            case 12: aFlds_[12] = &SameDlrBrnRep_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0449_VWRepeat_Record::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0449_VWRepeat_Record* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0449_VWRepeat_Record::getLargestDefinedField( void ) const
{
   return( 90 );
}

unsigned long dsi_DSTC0449_VWRepeat_Record::getDefinedByteLength( void ) const
{
   return( 600 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0449_VWRepeat_Record::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0449_VWRepeat_Record::fieldExists( id );
}

bool dsi_DSTC0449_VWRepeat_Record::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40007025: return( true );
      case 40007080: return( true );
      case 40007081: return( true );
      case 40001477: return( true );
      case 40007082: return( true );
      case 40007083: return( true );
      case 40007084: return( true );
      case 40007085: return( true );
      case 40007086: return( true );
      case 40007250: return( true );
      case 40007249: return( true );
      case 40007571: return( true );
      case 40007572: return( true );
   }
   return false;
}

