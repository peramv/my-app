// BFDataImpl implementation file for DataSet DSTC0251.REQRepeat_Record
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0251_reqrepeat_record.h"


// This function creates an instance of dsi_DSTC0251_REQRepeat_Record
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0251_REQRepeat_Record() { return new dsi_DSTC0251_REQRepeat_Record; }

dsi_DSTC0251_REQRepeat_Record::dsi_DSTC0251_REQRepeat_Record()
: BFDataImpl( 40003813 )
, RunMode_( ifds::RunMode, &ifds::s_FldProp_RunMode )
, AMSCode_( ifds::AMSCode, &ifds::s_FldProp_AMSCode )
, EffectiveDate_( ifds::EffectiveDate, &ifds::s_FldProp_EffectiveDate )
, GoodBad_( ifds::GoodBad, &ifds::s_FldProp_GoodBad )
, BrokerAMSRId_( ifds::BrokerAMSRId, &ifds::s_FldProp_BrokerAMSRId )
, BrokerAMSVer_( ifds::BrokerAMSVer, &ifds::s_FldProp_BrokerAMSVer )
{
   cFields_ = 6;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0251_REQRepeat_Record::~dsi_DSTC0251_REQRepeat_Record()
{
}

BFDataImpl* dsi_DSTC0251_REQRepeat_Record::clone()
{
   dsi_DSTC0251_REQRepeat_Record* p = new dsi_DSTC0251_REQRepeat_Record;
   p->RunMode_ = RunMode_;
   p->AMSCode_ = AMSCode_;
   p->EffectiveDate_ = EffectiveDate_;
   p->GoodBad_ = GoodBad_;
   p->BrokerAMSRId_ = BrokerAMSRId_;
   p->BrokerAMSVer_ = BrokerAMSVer_;
   return(p);
}

BFDataField* dsi_DSTC0251_REQRepeat_Record::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40000990: return ( &RunMode_ ); break; // RunMode
      case 40000193: return ( &AMSCode_ ); break; // AMSCode
      case 40000327: return ( &EffectiveDate_ ); break; // EffectiveDate
      case 40000496: return ( &GoodBad_ ); break; // GoodBad
      case 40003806: return ( &BrokerAMSRId_ ); break; // BrokerAMSRId
      case 40003805: return ( &BrokerAMSVer_ ); break; // BrokerAMSVer
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0251_REQRepeat_Record::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0251_REQRepeat_Record* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0251_REQRepeat_Record::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 6 )
   {
      BFDataField* pField = aFlds_[iField];
      if( NULL == pField )
      {
         switch(iField)
         {
            case 0: aFlds_[0] = &RunMode_; break;
            case 1: aFlds_[1] = &AMSCode_; break;
            case 2: aFlds_[2] = &EffectiveDate_; break;
            case 3: aFlds_[3] = &GoodBad_; break;
            case 4: aFlds_[4] = &BrokerAMSRId_; break;
            case 5: aFlds_[5] = &BrokerAMSVer_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0251_REQRepeat_Record::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0251_REQRepeat_Record* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0251_REQRepeat_Record::getLargestDefinedField( void ) const
{
   return( 60 );
}

unsigned long dsi_DSTC0251_REQRepeat_Record::getDefinedByteLength( void ) const
{
   return( 174 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0251_REQRepeat_Record::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0251_REQRepeat_Record::fieldExists( id );
}

bool dsi_DSTC0251_REQRepeat_Record::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40000990: return( true );
      case 40000193: return( true );
      case 40000327: return( true );
      case 40000496: return( true );
      case 40003806: return( true );
      case 40003805: return( true );
   }
   return false;
}

