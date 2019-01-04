// BFDataImpl implementation file for DataSet DSTC0285.REQRepeat_Record
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0285_reqrepeat_record.h"


// This function creates an instance of dsi_DSTC0285_REQRepeat_Record
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0285_REQRepeat_Record() { return new dsi_DSTC0285_REQRepeat_Record; }

dsi_DSTC0285_REQRepeat_Record::dsi_DSTC0285_REQRepeat_Record()
: BFDataImpl( 40004383 )
, RunMode_( ifds::RunMode, &ifds::s_FldProp_RunMode )
, RecordType_( ifds::RecordType, &ifds::s_FldProp_RecordType )
, FeeCode_( ifds::FeeCode, &ifds::s_FldProp_FeeCode )
, FundCode_( ifds::FundCode, &ifds::s_FldProp_FundCode )
, ClassCode_( ifds::ClassCode, &ifds::s_FldProp_ClassCode )
, EffectiveDate_( ifds::EffectiveDate, &ifds::s_FldProp_EffectiveDate )
, StopDate_( ifds::StopDate, &ifds::s_FldProp_StopDate )
, FeeRate_( ifds::FeeRate, &ifds::s_FldProp_FeeRate )
, DailyFeeRid_( ifds::DailyFeeRid, &ifds::s_FldProp_DailyFeeRid )
, Version_( ifds::Version, &ifds::s_FldProp_Version )
, FeeType_( ifds::FeeType, &ifds::s_FldProp_FeeType )
{
   cFields_ = 11;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0285_REQRepeat_Record::~dsi_DSTC0285_REQRepeat_Record()
{
}

BFDataImpl* dsi_DSTC0285_REQRepeat_Record::clone()
{
   dsi_DSTC0285_REQRepeat_Record* p = new dsi_DSTC0285_REQRepeat_Record;
   p->RunMode_ = RunMode_;
   p->RecordType_ = RecordType_;
   p->FeeCode_ = FeeCode_;
   p->FundCode_ = FundCode_;
   p->ClassCode_ = ClassCode_;
   p->EffectiveDate_ = EffectiveDate_;
   p->StopDate_ = StopDate_;
   p->FeeRate_ = FeeRate_;
   p->DailyFeeRid_ = DailyFeeRid_;
   p->Version_ = Version_;
   p->FeeType_ = FeeType_;
   return(p);
}

BFDataField* dsi_DSTC0285_REQRepeat_Record::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40000990: return ( &RunMode_ ); break; // RunMode
      case 40000951: return ( &RecordType_ ); break; // RecordType
      case 40002917: return ( &FeeCode_ ); break; // FeeCode
      case 40000049: return ( &FundCode_ ); break; // FundCode
      case 40000050: return ( &ClassCode_ ); break; // ClassCode
      case 40000327: return ( &EffectiveDate_ ); break; // EffectiveDate
      case 40000279: return ( &StopDate_ ); break; // StopDate
      case 40004370: return ( &FeeRate_ ); break; // FeeRate
      case 40004412: return ( &DailyFeeRid_ ); break; // DailyFeeRid
      case 40003739: return ( &Version_ ); break; // Version
      case 40000728: return ( &FeeType_ ); break; // FeeType
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0285_REQRepeat_Record::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0285_REQRepeat_Record* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0285_REQRepeat_Record::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 11 )
   {
      BFDataField* pField = aFlds_[iField];
      if( NULL == pField )
      {
         switch(iField)
         {
            case 0: aFlds_[0] = &RunMode_; break;
            case 1: aFlds_[1] = &RecordType_; break;
            case 2: aFlds_[2] = &FeeCode_; break;
            case 3: aFlds_[3] = &FundCode_; break;
            case 4: aFlds_[4] = &ClassCode_; break;
            case 5: aFlds_[5] = &EffectiveDate_; break;
            case 6: aFlds_[6] = &StopDate_; break;
            case 7: aFlds_[7] = &FeeRate_; break;
            case 8: aFlds_[8] = &DailyFeeRid_; break;
            case 9: aFlds_[9] = &Version_; break;
            case 10: aFlds_[10] = &FeeType_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0285_REQRepeat_Record::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0285_REQRepeat_Record* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0285_REQRepeat_Record::getLargestDefinedField( void ) const
{
   return( 200 );
}

unsigned long dsi_DSTC0285_REQRepeat_Record::getDefinedByteLength( void ) const
{
   return( 638 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0285_REQRepeat_Record::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0285_REQRepeat_Record::fieldExists( id );
}

bool dsi_DSTC0285_REQRepeat_Record::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40000990: return( true );
      case 40000951: return( true );
      case 40002917: return( true );
      case 40000049: return( true );
      case 40000050: return( true );
      case 40000327: return( true );
      case 40000279: return( true );
      case 40004370: return( true );
      case 40004412: return( true );
      case 40003739: return( true );
      case 40000728: return( true );
   }
   return false;
}

