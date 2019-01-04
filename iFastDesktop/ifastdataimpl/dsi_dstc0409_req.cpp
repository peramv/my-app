// BFDataImpl implementation file for DataSet DSTC0409.REQ
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0409_req.h"


// This function creates an instance of dsi_DSTC0409_REQ
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0409_REQ() { return new dsi_DSTC0409_REQ; }

dsi_DSTC0409_REQ::dsi_DSTC0409_REQ()
: BFDataImpl( 40006249 )
, SessionId_( ifds::SessionId, &ifds::s_FldProp_SessionId )
, User_Id_( ifds::User_Id, &ifds::s_FldProp_User_Id )
, LanguageCode_( ifds::LanguageCode, &ifds::s_FldProp_LanguageCode )
, CompanyId_( ifds::CompanyId, &ifds::s_FldProp_CompanyId )
, Track_( ifds::Track, &ifds::s_FldProp_Track )
, Activity_( ifds::Activity, &ifds::s_FldProp_Activity )
, TradeType_( ifds::TradeType, &ifds::s_FldProp_TradeType )
, TransId_( ifds::TransId, &ifds::s_FldProp_TransId )
, AccountNum_( ifds::AccountNum, &ifds::s_FldProp_AccountNum )
, RESPBenefId_( ifds::RESPBenefId, &ifds::s_FldProp_RESPBenefId )
, TransType_( ifds::TransType, &ifds::s_FldProp_TransType )
, EffectiveDate_( ifds::EffectiveDate, &ifds::s_FldProp_EffectiveDate )
, DepositType_( ifds::DepositType, &ifds::s_FldProp_DepositType )
, RedCode_( ifds::RedCode, &ifds::s_FldProp_RedCode )
, AccountTo_( ifds::AccountTo, &ifds::s_FldProp_AccountTo )
, TransferPercent_( ifds::TransferPercent, &ifds::s_FldProp_TransferPercent )
, RecordLevel_( ifds::RecordLevel, &ifds::s_FldProp_RecordLevel )
, IsResidualCESG_( ifds::IsResidualCESG, &ifds::s_FldProp_IsResidualCESG )
{
   cFields_ = 18;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0409_REQ::~dsi_DSTC0409_REQ()
{
}

BFDataImpl* dsi_DSTC0409_REQ::clone()
{
   dsi_DSTC0409_REQ* p = new dsi_DSTC0409_REQ;
   p->SessionId_ = SessionId_;
   p->User_Id_ = User_Id_;
   p->LanguageCode_ = LanguageCode_;
   p->CompanyId_ = CompanyId_;
   p->Track_ = Track_;
   p->Activity_ = Activity_;
   p->TradeType_ = TradeType_;
   p->TransId_ = TransId_;
   p->AccountNum_ = AccountNum_;
   p->RESPBenefId_ = RESPBenefId_;
   p->TransType_ = TransType_;
   p->EffectiveDate_ = EffectiveDate_;
   p->DepositType_ = DepositType_;
   p->RedCode_ = RedCode_;
   p->AccountTo_ = AccountTo_;
   p->TransferPercent_ = TransferPercent_;
   p->RecordLevel_ = RecordLevel_;
   p->IsResidualCESG_ = IsResidualCESG_;
   return(p);
}

BFDataField* dsi_DSTC0409_REQ::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40000005: return ( &SessionId_ ); break; // SessionId
      case 40000002: return ( &User_Id_ ); break; // User_Id
      case 40000030: return ( &LanguageCode_ ); break; // LanguageCode
      case 40000031: return ( &CompanyId_ ); break; // CompanyId
      case 40002065: return ( &Track_ ); break; // Track
      case 40002066: return ( &Activity_ ); break; // Activity
      case 40003162: return ( &TradeType_ ); break; // TradeType
      case 40000063: return ( &TransId_ ); break; // TransId
      case 40000040: return ( &AccountNum_ ); break; // AccountNum
      case 40006114: return ( &RESPBenefId_ ); break; // RESPBenefId
      case 40000095: return ( &TransType_ ); break; // TransType
      case 40000327: return ( &EffectiveDate_ ); break; // EffectiveDate
      case 40000433: return ( &DepositType_ ); break; // DepositType
      case 40000435: return ( &RedCode_ ); break; // RedCode
      case 40000646: return ( &AccountTo_ ); break; // AccountTo
      case 40006213: return ( &TransferPercent_ ); break; // TransferPercent
      case 40006190: return ( &RecordLevel_ ); break; // RecordLevel
      case 40007191: return ( &IsResidualCESG_ ); break; // IsResidualCESG
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0409_REQ::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0409_REQ* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0409_REQ::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 18 )
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
            case 6: aFlds_[6] = &TradeType_; break;
            case 7: aFlds_[7] = &TransId_; break;
            case 8: aFlds_[8] = &AccountNum_; break;
            case 9: aFlds_[9] = &RESPBenefId_; break;
            case 10: aFlds_[10] = &TransType_; break;
            case 11: aFlds_[11] = &EffectiveDate_; break;
            case 12: aFlds_[12] = &DepositType_; break;
            case 13: aFlds_[13] = &RedCode_; break;
            case 14: aFlds_[14] = &AccountTo_; break;
            case 15: aFlds_[15] = &TransferPercent_; break;
            case 16: aFlds_[16] = &RecordLevel_; break;
            case 17: aFlds_[17] = &IsResidualCESG_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0409_REQ::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0409_REQ* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0409_REQ::getLargestDefinedField( void ) const
{
   return( 60 );
}

unsigned long dsi_DSTC0409_REQ::getDefinedByteLength( void ) const
{
   return( 707 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0409_REQ::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0409_REQ::fieldExists( id );
}

bool dsi_DSTC0409_REQ::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40000005: return( true );
      case 40000002: return( true );
      case 40000030: return( true );
      case 40000031: return( true );
      case 40002065: return( true );
      case 40002066: return( true );
      case 40003162: return( true );
      case 40000063: return( true );
      case 40000040: return( true );
      case 40006114: return( true );
      case 40000095: return( true );
      case 40000327: return( true );
      case 40000433: return( true );
      case 40000435: return( true );
      case 40000646: return( true );
      case 40006213: return( true );
      case 40006190: return( true );
      case 40007191: return( true );
   }
   return false;
}

