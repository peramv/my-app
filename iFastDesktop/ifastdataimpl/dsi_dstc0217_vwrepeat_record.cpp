// BFDataImpl implementation file for DataSet DSTC0217.VWRepeat_Record
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0217_vwrepeat_record.h"


// This function creates an instance of dsi_DSTC0217_VWRepeat_Record
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0217_VWRepeat_Record() { return new dsi_DSTC0217_VWRepeat_Record; }

dsi_DSTC0217_VWRepeat_Record::dsi_DSTC0217_VWRepeat_Record()
: BFDataImpl( 40003420 )
, FundCode_( ifds::FundCode, &ifds::s_FldProp_FundCode )
, ClassCode_( ifds::ClassCode, &ifds::s_FldProp_ClassCode )
, Baycom_( ifds::Baycom, &ifds::s_FldProp_Baycom )
, FundCurrency_( ifds::FundCurrency, &ifds::s_FldProp_FundCurrency )
, Amount_( ifds::Amount, &ifds::s_FldProp_Amount )
, Units_( ifds::Units, &ifds::s_FldProp_Units )
, FreeAmount_( ifds::FreeAmount, &ifds::s_FldProp_FreeAmount )
, FreeUnits_( ifds::FreeUnits, &ifds::s_FldProp_FreeUnits )
, ApplicableAmt_( ifds::ApplicableAmt, &ifds::s_FldProp_ApplicableAmt )
, ApplicableUnits_( ifds::ApplicableUnits, &ifds::s_FldProp_ApplicableUnits )
, DSC_( ifds::DSC, &ifds::s_FldProp_DSC )
, WithHoldTax_( ifds::WithHoldTax, &ifds::s_FldProp_WithHoldTax )
, Fee_( ifds::Fee, &ifds::s_FldProp_Fee )
, ErrorCode_( ifds::ErrorCode, &ifds::s_FldProp_ErrorCode )
, ErrorDesc_( ifds::ErrorDesc, &ifds::s_FldProp_ErrorDesc )
, FedClawback_( ifds::FedClawback, &ifds::s_FldProp_FedClawback )
, ProvClawback_( ifds::ProvClawback, &ifds::s_FldProp_ProvClawback )
, AdditionalProvClawback_( ifds::AdditionalProvClawback, &ifds::s_FldProp_AdditionalProvClawback )
, FedTax_( ifds::FedTax, &ifds::s_FldProp_FedTax )
, ProvTax_( ifds::ProvTax, &ifds::s_FldProp_ProvTax )
{
   cFields_ = 20;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0217_VWRepeat_Record::~dsi_DSTC0217_VWRepeat_Record()
{
}

BFDataImpl* dsi_DSTC0217_VWRepeat_Record::clone()
{
   dsi_DSTC0217_VWRepeat_Record* p = new dsi_DSTC0217_VWRepeat_Record;
   p->FundCode_ = FundCode_;
   p->ClassCode_ = ClassCode_;
   p->Baycom_ = Baycom_;
   p->FundCurrency_ = FundCurrency_;
   p->Amount_ = Amount_;
   p->Units_ = Units_;
   p->FreeAmount_ = FreeAmount_;
   p->FreeUnits_ = FreeUnits_;
   p->ApplicableAmt_ = ApplicableAmt_;
   p->ApplicableUnits_ = ApplicableUnits_;
   p->DSC_ = DSC_;
   p->WithHoldTax_ = WithHoldTax_;
   p->Fee_ = Fee_;
   p->ErrorCode_ = ErrorCode_;
   p->ErrorDesc_ = ErrorDesc_;
   p->FedClawback_ = FedClawback_;
   p->ProvClawback_ = ProvClawback_;
   p->AdditionalProvClawback_ = AdditionalProvClawback_;
   p->FedTax_ = FedTax_;
   p->ProvTax_ = ProvTax_;
   return(p);
}

BFDataField* dsi_DSTC0217_VWRepeat_Record::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40000049: return ( &FundCode_ ); break; // FundCode
      case 40000050: return ( &ClassCode_ ); break; // ClassCode
      case 40000958: return ( &Baycom_ ); break; // Baycom
      case 40001948: return ( &FundCurrency_ ); break; // FundCurrency
      case 40000231: return ( &Amount_ ); break; // Amount
      case 40000332: return ( &Units_ ); break; // Units
      case 40002977: return ( &FreeAmount_ ); break; // FreeAmount
      case 40003402: return ( &FreeUnits_ ); break; // FreeUnits
      case 40003397: return ( &ApplicableAmt_ ); break; // ApplicableAmt
      case 40003403: return ( &ApplicableUnits_ ); break; // ApplicableUnits
      case 40001735: return ( &DSC_ ); break; // DSC
      case 40001767: return ( &WithHoldTax_ ); break; // WithHoldTax
      case 40000235: return ( &Fee_ ); break; // Fee
      case 40000586: return ( &ErrorCode_ ); break; // ErrorCode
      case 40000587: return ( &ErrorDesc_ ); break; // ErrorDesc
      case 40004441: return ( &FedClawback_ ); break; // FedClawback
      case 40004442: return ( &ProvClawback_ ); break; // ProvClawback
      case 40004462: return ( &AdditionalProvClawback_ ); break; // AdditionalProvClawback
      case 40000414: return ( &FedTax_ ); break; // FedTax
      case 40000415: return ( &ProvTax_ ); break; // ProvTax
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0217_VWRepeat_Record::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0217_VWRepeat_Record* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0217_VWRepeat_Record::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 20 )
   {
      BFDataField* pField = aFlds_[iField];
      if( NULL == pField )
      {
         switch(iField)
         {
            case 0: aFlds_[0] = &FundCode_; break;
            case 1: aFlds_[1] = &ClassCode_; break;
            case 2: aFlds_[2] = &Baycom_; break;
            case 3: aFlds_[3] = &FundCurrency_; break;
            case 4: aFlds_[4] = &Amount_; break;
            case 5: aFlds_[5] = &Units_; break;
            case 6: aFlds_[6] = &FreeAmount_; break;
            case 7: aFlds_[7] = &FreeUnits_; break;
            case 8: aFlds_[8] = &ApplicableAmt_; break;
            case 9: aFlds_[9] = &ApplicableUnits_; break;
            case 10: aFlds_[10] = &DSC_; break;
            case 11: aFlds_[11] = &WithHoldTax_; break;
            case 12: aFlds_[12] = &Fee_; break;
            case 13: aFlds_[13] = &ErrorCode_; break;
            case 14: aFlds_[14] = &ErrorDesc_; break;
            case 15: aFlds_[15] = &FedClawback_; break;
            case 16: aFlds_[16] = &ProvClawback_; break;
            case 17: aFlds_[17] = &AdditionalProvClawback_; break;
            case 18: aFlds_[18] = &FedTax_; break;
            case 19: aFlds_[19] = &ProvTax_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0217_VWRepeat_Record::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0217_VWRepeat_Record* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0217_VWRepeat_Record::getLargestDefinedField( void ) const
{
   return( 200 );
}

unsigned long dsi_DSTC0217_VWRepeat_Record::getDefinedByteLength( void ) const
{
   return( 921 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0217_VWRepeat_Record::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0217_VWRepeat_Record::fieldExists( id );
}

bool dsi_DSTC0217_VWRepeat_Record::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40000049: return( true );
      case 40000050: return( true );
      case 40000958: return( true );
      case 40001948: return( true );
      case 40000231: return( true );
      case 40000332: return( true );
      case 40002977: return( true );
      case 40003402: return( true );
      case 40003397: return( true );
      case 40003403: return( true );
      case 40001735: return( true );
      case 40001767: return( true );
      case 40000235: return( true );
      case 40000586: return( true );
      case 40000587: return( true );
      case 40004441: return( true );
      case 40004442: return( true );
      case 40004462: return( true );
      case 40000414: return( true );
      case 40000415: return( true );
   }
   return false;
}

