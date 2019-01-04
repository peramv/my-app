// BFDataImpl implementation file for DataSet DSTC0256.REQ
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0256_req.h"


// This function creates an instance of dsi_DSTC0256_REQ
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0256_REQ() { return new dsi_DSTC0256_REQ; }

dsi_DSTC0256_REQ::dsi_DSTC0256_REQ()
: BFDataImpl( 40003975 )
, SessionId_( ifds::SessionId, &ifds::s_FldProp_SessionId )
, User_Id_( ifds::User_Id, &ifds::s_FldProp_User_Id )
, LanguageCode_( ifds::LanguageCode, &ifds::s_FldProp_LanguageCode )
, CompanyId_( ifds::CompanyId, &ifds::s_FldProp_CompanyId )
, Track_( ifds::Track, &ifds::s_FldProp_Track )
, Activity_( ifds::Activity, &ifds::s_FldProp_Activity )
, OverrideRepeats_( ifds::OverrideRepeats, &ifds::s_FldProp_OverrideRepeats )
, NextKey_( ifds::NextKey, &ifds::s_FldProp_NextKey )
, BrokerCode_( ifds::BrokerCode, &ifds::s_FldProp_BrokerCode )
, BranchCode_( ifds::BranchCode, &ifds::s_FldProp_BranchCode )
, SalesRepCode_( ifds::SalesRepCode, &ifds::s_FldProp_SalesRepCode )
, PaymentFor_( ifds::PaymentFor, &ifds::s_FldProp_PaymentFor )
, DuplicateCheck_( ifds::DuplicateCheck, &ifds::s_FldProp_DuplicateCheck )
, SearchTypeMgmt_( ifds::SearchTypeMgmt, &ifds::s_FldProp_SearchTypeMgmt )
, EffectiveDate_( ifds::EffectiveDate, &ifds::s_FldProp_EffectiveDate )
, PayInstructRID_( ifds::PayInstructRID, &ifds::s_FldProp_PayInstructRID )
, StopDate_( ifds::StopDate, &ifds::s_FldProp_StopDate )
{
   cFields_ = 17;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0256_REQ::~dsi_DSTC0256_REQ()
{
}

BFDataImpl* dsi_DSTC0256_REQ::clone()
{
   dsi_DSTC0256_REQ* p = new dsi_DSTC0256_REQ;
   p->SessionId_ = SessionId_;
   p->User_Id_ = User_Id_;
   p->LanguageCode_ = LanguageCode_;
   p->CompanyId_ = CompanyId_;
   p->Track_ = Track_;
   p->Activity_ = Activity_;
   p->OverrideRepeats_ = OverrideRepeats_;
   p->NextKey_ = NextKey_;
   p->BrokerCode_ = BrokerCode_;
   p->BranchCode_ = BranchCode_;
   p->SalesRepCode_ = SalesRepCode_;
   p->PaymentFor_ = PaymentFor_;
   p->DuplicateCheck_ = DuplicateCheck_;
   p->SearchTypeMgmt_ = SearchTypeMgmt_;
   p->EffectiveDate_ = EffectiveDate_;
   p->PayInstructRID_ = PayInstructRID_;
   p->StopDate_ = StopDate_;
   return(p);
}

BFDataField* dsi_DSTC0256_REQ::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40000005: return ( &SessionId_ ); break; // SessionId
      case 40000002: return ( &User_Id_ ); break; // User_Id
      case 40000030: return ( &LanguageCode_ ); break; // LanguageCode
      case 40000031: return ( &CompanyId_ ); break; // CompanyId
      case 40002065: return ( &Track_ ); break; // Track
      case 40002066: return ( &Activity_ ); break; // Activity
      case 40002139: return ( &OverrideRepeats_ ); break; // OverrideRepeats
      case 40000029: return ( &NextKey_ ); break; // NextKey
      case 40000044: return ( &BrokerCode_ ); break; // BrokerCode
      case 40000045: return ( &BranchCode_ ); break; // BranchCode
      case 40000046: return ( &SalesRepCode_ ); break; // SalesRepCode
      case 40003965: return ( &PaymentFor_ ); break; // PaymentFor
      case 40003976: return ( &DuplicateCheck_ ); break; // DuplicateCheck
      case 40005471: return ( &SearchTypeMgmt_ ); break; // SearchTypeMgmt
      case 40000327: return ( &EffectiveDate_ ); break; // EffectiveDate
      case 40004120: return ( &PayInstructRID_ ); break; // PayInstructRID
      case 40000279: return ( &StopDate_ ); break; // StopDate
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0256_REQ::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0256_REQ* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0256_REQ::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 17 )
   {
      BFDataField* pField = aFlds_[iField];
      if( NULL == pField )
      {
         switch(iField)
         {
            case 0: aFlds_[0] = &SessionId_; break;
            case 1: aFlds_[1] = &User_Id_; break;
            case 2: aFlds_[2] = &LanguageCode_; break;
            case 3: aFlds_[3] = &CompanyId_; break;
            case 4: aFlds_[4] = &Track_; break;
            case 5: aFlds_[5] = &Activity_; break;
            case 6: aFlds_[6] = &OverrideRepeats_; break;
            case 7: aFlds_[7] = &NextKey_; break;
            case 8: aFlds_[8] = &BrokerCode_; break;
            case 9: aFlds_[9] = &BranchCode_; break;
            case 10: aFlds_[10] = &SalesRepCode_; break;
            case 11: aFlds_[11] = &PaymentFor_; break;
            case 12: aFlds_[12] = &DuplicateCheck_; break;
            case 13: aFlds_[13] = &SearchTypeMgmt_; break;
            case 14: aFlds_[14] = &EffectiveDate_; break;
            case 15: aFlds_[15] = &PayInstructRID_; break;
            case 16: aFlds_[16] = &StopDate_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0256_REQ::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0256_REQ* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0256_REQ::getLargestDefinedField( void ) const
{
   return( 100 );
}

unsigned long dsi_DSTC0256_REQ::getDefinedByteLength( void ) const
{
   return( 747 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0256_REQ::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0256_REQ::fieldExists( id );
}

bool dsi_DSTC0256_REQ::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40000005: return( true );
      case 40000002: return( true );
      case 40000030: return( true );
      case 40000031: return( true );
      case 40002065: return( true );
      case 40002066: return( true );
      case 40002139: return( true );
      case 40000029: return( true );
      case 40000044: return( true );
      case 40000045: return( true );
      case 40000046: return( true );
      case 40003965: return( true );
      case 40003976: return( true );
      case 40005471: return( true );
      case 40000327: return( true );
      case 40004120: return( true );
      case 40000279: return( true );
   }
   return false;
}

