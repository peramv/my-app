// BFDataImpl implementation file for DataSet DSTC0349.REQRepeat_Record
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0349_reqrepeat_record.h"


// This function creates an instance of dsi_DSTC0349_REQRepeat_Record
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0349_REQRepeat_Record() { return new dsi_DSTC0349_REQRepeat_Record; }

dsi_DSTC0349_REQRepeat_Record::dsi_DSTC0349_REQRepeat_Record()
: BFDataImpl( 40005208 )
, RunMode_( ifds::RunMode, &ifds::s_FldProp_RunMode )
, FundGroup_( ifds::FundGroup, &ifds::s_FldProp_FundGroup )
, CutOffTimeType_( ifds::CutOffTimeType, &ifds::s_FldProp_CutOffTimeType )
, CutOffTime_( ifds::CutOffTime, &ifds::s_FldProp_CutOffTime )
, RecId_( ifds::RecId, &ifds::s_FldProp_RecId )
, VersionNum_( ifds::VersionNum, &ifds::s_FldProp_VersionNum )
, CutOffLevel_( ifds::CutOffLevel, &ifds::s_FldProp_CutOffLevel )
, TimeZoneCode_( ifds::TimeZoneCode, &ifds::s_FldProp_TimeZoneCode )
, CutOffDays_( ifds::CutOffDays, &ifds::s_FldProp_CutOffDays )
, FundCode_( ifds::FundCode, &ifds::s_FldProp_FundCode )
, ClassCode_( ifds::ClassCode, &ifds::s_FldProp_ClassCode )
{
   cFields_ = 11;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0349_REQRepeat_Record::~dsi_DSTC0349_REQRepeat_Record()
{
}

BFDataImpl* dsi_DSTC0349_REQRepeat_Record::clone()
{
   dsi_DSTC0349_REQRepeat_Record* p = new dsi_DSTC0349_REQRepeat_Record;
   p->RunMode_ = RunMode_;
   p->FundGroup_ = FundGroup_;
   p->CutOffTimeType_ = CutOffTimeType_;
   p->CutOffTime_ = CutOffTime_;
   p->RecId_ = RecId_;
   p->VersionNum_ = VersionNum_;
   p->CutOffLevel_ = CutOffLevel_;
   p->TimeZoneCode_ = TimeZoneCode_;
   p->CutOffDays_ = CutOffDays_;
   p->FundCode_ = FundCode_;
   p->ClassCode_ = ClassCode_;
   return(p);
}

BFDataField* dsi_DSTC0349_REQRepeat_Record::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40000990: return ( &RunMode_ ); break; // RunMode
      case 40002031: return ( &FundGroup_ ); break; // FundGroup
      case 40005201: return ( &CutOffTimeType_ ); break; // CutOffTimeType
      case 40005202: return ( &CutOffTime_ ); break; // CutOffTime
      case 40003737: return ( &RecId_ ); break; // RecId
      case 40000228: return ( &VersionNum_ ); break; // VersionNum
      case 40005478: return ( &CutOffLevel_ ); break; // CutOffLevel
      case 40005477: return ( &TimeZoneCode_ ); break; // TimeZoneCode
      case 40005479: return ( &CutOffDays_ ); break; // CutOffDays
      case 40000049: return ( &FundCode_ ); break; // FundCode
      case 40000050: return ( &ClassCode_ ); break; // ClassCode
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0349_REQRepeat_Record::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0349_REQRepeat_Record* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0349_REQRepeat_Record::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 11 )
   {
      BFDataField* pField = aFlds_[iField];
      if( NULL == pField )
      {
         switch(iField)
         {
            case 0: aFlds_[0] = &RunMode_; break;
            case 1: aFlds_[1] = &FundGroup_; break;
            case 2: aFlds_[2] = &CutOffTimeType_; break;
            case 3: aFlds_[3] = &CutOffTime_; break;
            case 4: aFlds_[4] = &RecId_; break;
            case 5: aFlds_[5] = &VersionNum_; break;
            case 6: aFlds_[6] = &CutOffLevel_; break;
            case 7: aFlds_[7] = &TimeZoneCode_; break;
            case 8: aFlds_[8] = &CutOffDays_; break;
            case 9: aFlds_[9] = &FundCode_; break;
            case 10: aFlds_[10] = &ClassCode_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0349_REQRepeat_Record::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0349_REQRepeat_Record* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0349_REQRepeat_Record::getLargestDefinedField( void ) const
{
   return( 200 );
}

unsigned long dsi_DSTC0349_REQRepeat_Record::getDefinedByteLength( void ) const
{
   return( 659 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0349_REQRepeat_Record::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0349_REQRepeat_Record::fieldExists( id );
}

bool dsi_DSTC0349_REQRepeat_Record::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40000990: return( true );
      case 40002031: return( true );
      case 40005201: return( true );
      case 40005202: return( true );
      case 40003737: return( true );
      case 40000228: return( true );
      case 40005478: return( true );
      case 40005477: return( true );
      case 40005479: return( true );
      case 40000049: return( true );
      case 40000050: return( true );
   }
   return false;
}

