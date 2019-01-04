// BFDataImpl implementation file for DataSet DSTC0395.VWRepeat_Record
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0395_vwrepeat_record.h"


// This function creates an instance of dsi_DSTC0395_VWRepeat_Record
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0395_VWRepeat_Record() { return new dsi_DSTC0395_VWRepeat_Record; }

dsi_DSTC0395_VWRepeat_Record::dsi_DSTC0395_VWRepeat_Record()
: BFDataImpl( 40006005 )
, BrokerCode_( ifds::BrokerCode, &ifds::s_FldProp_BrokerCode )
, BranchCode_( ifds::BranchCode, &ifds::s_FldProp_BranchCode )
, SlsrepCode_( ifds::SlsrepCode, &ifds::s_FldProp_SlsrepCode )
, IAFundIndicator_( ifds::IAFundIndicator, &ifds::s_FldProp_IAFundIndicator )
, EffectiveDate_( ifds::EffectiveDate, &ifds::s_FldProp_EffectiveDate )
, StopDate_( ifds::StopDate, &ifds::s_FldProp_StopDate )
, ProcessDate_( ifds::ProcessDate, &ifds::s_FldProp_ProcessDate )
, Username_( ifds::Username, &ifds::s_FldProp_Username )
, ModDate_( ifds::ModDate, &ifds::s_FldProp_ModDate )
, ModUser_( ifds::ModUser, &ifds::s_FldProp_ModUser )
, AcctAuthVer_( ifds::AcctAuthVer, &ifds::s_FldProp_AcctAuthVer )
, AcctAuthRid_( ifds::AcctAuthRid, &ifds::s_FldProp_AcctAuthRid )
{
   cFields_ = 12;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0395_VWRepeat_Record::~dsi_DSTC0395_VWRepeat_Record()
{
}

BFDataImpl* dsi_DSTC0395_VWRepeat_Record::clone()
{
   dsi_DSTC0395_VWRepeat_Record* p = new dsi_DSTC0395_VWRepeat_Record;
   p->BrokerCode_ = BrokerCode_;
   p->BranchCode_ = BranchCode_;
   p->SlsrepCode_ = SlsrepCode_;
   p->IAFundIndicator_ = IAFundIndicator_;
   p->EffectiveDate_ = EffectiveDate_;
   p->StopDate_ = StopDate_;
   p->ProcessDate_ = ProcessDate_;
   p->Username_ = Username_;
   p->ModDate_ = ModDate_;
   p->ModUser_ = ModUser_;
   p->AcctAuthVer_ = AcctAuthVer_;
   p->AcctAuthRid_ = AcctAuthRid_;
   return(p);
}

BFDataField* dsi_DSTC0395_VWRepeat_Record::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40000044: return ( &BrokerCode_ ); break; // BrokerCode
      case 40000045: return ( &BranchCode_ ); break; // BranchCode
      case 40000656: return ( &SlsrepCode_ ); break; // SlsrepCode
      case 40005999: return ( &IAFundIndicator_ ); break; // IAFundIndicator
      case 40000327: return ( &EffectiveDate_ ); break; // EffectiveDate
      case 40000279: return ( &StopDate_ ); break; // StopDate
      case 40000216: return ( &ProcessDate_ ); break; // ProcessDate
      case 40000117: return ( &Username_ ); break; // Username
      case 40000217: return ( &ModDate_ ); break; // ModDate
      case 40000218: return ( &ModUser_ ); break; // ModUser
      case 40006009: return ( &AcctAuthVer_ ); break; // AcctAuthVer
      case 40006001: return ( &AcctAuthRid_ ); break; // AcctAuthRid
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0395_VWRepeat_Record::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0395_VWRepeat_Record* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0395_VWRepeat_Record::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 12 )
   {
      BFDataField* pField = aFlds_[iField];
      if( NULL == pField )
      {
         switch(iField)
         {
            case 0: aFlds_[0] = &BrokerCode_; break;
            case 1: aFlds_[1] = &BranchCode_; break;
            case 2: aFlds_[2] = &SlsrepCode_; break;
            case 3: aFlds_[3] = &IAFundIndicator_; break;
            case 4: aFlds_[4] = &EffectiveDate_; break;
            case 5: aFlds_[5] = &StopDate_; break;
            case 6: aFlds_[6] = &ProcessDate_; break;
            case 7: aFlds_[7] = &Username_; break;
            case 8: aFlds_[8] = &ModDate_; break;
            case 9: aFlds_[9] = &ModUser_; break;
            case 10: aFlds_[10] = &AcctAuthVer_; break;
            case 11: aFlds_[11] = &AcctAuthRid_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0395_VWRepeat_Record::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0395_VWRepeat_Record* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0395_VWRepeat_Record::getLargestDefinedField( void ) const
{
   return( 60 );
}

unsigned long dsi_DSTC0395_VWRepeat_Record::getDefinedByteLength( void ) const
{
   return( 425 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0395_VWRepeat_Record::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0395_VWRepeat_Record::fieldExists( id );
}

bool dsi_DSTC0395_VWRepeat_Record::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40000044: return( true );
      case 40000045: return( true );
      case 40000656: return( true );
      case 40005999: return( true );
      case 40000327: return( true );
      case 40000279: return( true );
      case 40000216: return( true );
      case 40000117: return( true );
      case 40000217: return( true );
      case 40000218: return( true );
      case 40006009: return( true );
      case 40006001: return( true );
   }
   return false;
}

