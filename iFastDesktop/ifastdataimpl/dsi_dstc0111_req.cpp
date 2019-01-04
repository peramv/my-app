// BFDataImpl implementation file for DataSet DSTC0111.REQ
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0111_req.h"


// This function creates an instance of dsi_DSTC0111_REQ
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0111_REQ() { return new dsi_DSTC0111_REQ; }

dsi_DSTC0111_REQ::dsi_DSTC0111_REQ()
: BFDataImpl( 40001506 )
, NextKey_( ifds::NextKey, &ifds::s_FldProp_NextKey )
, SessionId_( ifds::SessionId, &ifds::s_FldProp_SessionId )
, User_Id_( ifds::User_Id, &ifds::s_FldProp_User_Id )
, LanguageCode_( ifds::LanguageCode, &ifds::s_FldProp_LanguageCode )
, CompanyId_( ifds::CompanyId, &ifds::s_FldProp_CompanyId )
, AccountNum_( ifds::AccountNum, &ifds::s_FldProp_AccountNum )
, HistoryPending_( ifds::HistoryPending, &ifds::s_FldProp_HistoryPending )
, Track_( ifds::Track, &ifds::s_FldProp_Track )
, Activity_( ifds::Activity, &ifds::s_FldProp_Activity )
, ReqTransid_( ifds::ReqTransid, &ifds::s_FldProp_ReqTransid )
, TransType_( ifds::TransType, &ifds::s_FldProp_TransType )
, DepositType_( ifds::DepositType, &ifds::s_FldProp_DepositType )
, RedCode_( ifds::RedCode, &ifds::s_FldProp_RedCode )
, BeneName_( ifds::BeneName, &ifds::s_FldProp_BeneName )
, RESPBenefId_( ifds::RESPBenefId, &ifds::s_FldProp_RESPBenefId )
, FromDate_( ifds::FromDate, &ifds::s_FldProp_FromDate )
, ToDate_( ifds::ToDate, &ifds::s_FldProp_ToDate )
, TfrStat_( ifds::TfrStat, &ifds::s_FldProp_TfrStat )
, RepHRDC_( ifds::RepHRDC, &ifds::s_FldProp_RepHRDC )
{
   cFields_ = 19;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0111_REQ::~dsi_DSTC0111_REQ()
{
}

BFDataImpl* dsi_DSTC0111_REQ::clone()
{
   dsi_DSTC0111_REQ* p = new dsi_DSTC0111_REQ;
   p->NextKey_ = NextKey_;
   p->SessionId_ = SessionId_;
   p->User_Id_ = User_Id_;
   p->LanguageCode_ = LanguageCode_;
   p->CompanyId_ = CompanyId_;
   p->AccountNum_ = AccountNum_;
   p->HistoryPending_ = HistoryPending_;
   p->Track_ = Track_;
   p->Activity_ = Activity_;
   p->ReqTransid_ = ReqTransid_;
   p->TransType_ = TransType_;
   p->DepositType_ = DepositType_;
   p->RedCode_ = RedCode_;
   p->BeneName_ = BeneName_;
   p->RESPBenefId_ = RESPBenefId_;
   p->FromDate_ = FromDate_;
   p->ToDate_ = ToDate_;
   p->TfrStat_ = TfrStat_;
   p->RepHRDC_ = RepHRDC_;
   return(p);
}

BFDataField* dsi_DSTC0111_REQ::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40000029: return ( &NextKey_ ); break; // NextKey
      case 40000005: return ( &SessionId_ ); break; // SessionId
      case 40000002: return ( &User_Id_ ); break; // User_Id
      case 40000030: return ( &LanguageCode_ ); break; // LanguageCode
      case 40000031: return ( &CompanyId_ ); break; // CompanyId
      case 40000040: return ( &AccountNum_ ); break; // AccountNum
      case 40001508: return ( &HistoryPending_ ); break; // HistoryPending
      case 40002065: return ( &Track_ ); break; // Track
      case 40002066: return ( &Activity_ ); break; // Activity
      case 40003187: return ( &ReqTransid_ ); break; // ReqTransid
      case 40000095: return ( &TransType_ ); break; // TransType
      case 40000433: return ( &DepositType_ ); break; // DepositType
      case 40000435: return ( &RedCode_ ); break; // RedCode
      case 40000786: return ( &BeneName_ ); break; // BeneName
      case 40006114: return ( &RESPBenefId_ ); break; // RESPBenefId
      case 40000067: return ( &FromDate_ ); break; // FromDate
      case 40000068: return ( &ToDate_ ); break; // ToDate
      case 40006282: return ( &TfrStat_ ); break; // TfrStat
      case 40006283: return ( &RepHRDC_ ); break; // RepHRDC
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0111_REQ::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0111_REQ* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0111_REQ::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 19 )
   {
      BFDataField* pField = aFlds_[iField];
      if( NULL == pField )
      {
         switch(iField)
         {
            case 0: aFlds_[0] = &NextKey_; break;
            case 1: aFlds_[1] = &SessionId_; break;
            case 2: aFlds_[2] = &User_Id_; break;
            case 3: aFlds_[3] = &LanguageCode_; break;
            case 4: aFlds_[4] = &CompanyId_; break;
            case 5: aFlds_[5] = &AccountNum_; break;
            case 6: aFlds_[6] = &HistoryPending_; break;
            case 7: aFlds_[7] = &Track_; break;
            case 8: aFlds_[8] = &Activity_; break;
            case 9: aFlds_[9] = &ReqTransid_; break;
            case 10: aFlds_[10] = &TransType_; break;
            case 11: aFlds_[11] = &DepositType_; break;
            case 12: aFlds_[12] = &RedCode_; break;
            case 13: aFlds_[13] = &BeneName_; break;
            case 14: aFlds_[14] = &RESPBenefId_; break;
            case 15: aFlds_[15] = &FromDate_; break;
            case 16: aFlds_[16] = &ToDate_; break;
            case 17: aFlds_[17] = &TfrStat_; break;
            case 18: aFlds_[18] = &RepHRDC_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0111_REQ::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0111_REQ* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0111_REQ::getLargestDefinedField( void ) const
{
   return( 100 );
}

unsigned long dsi_DSTC0111_REQ::getDefinedByteLength( void ) const
{
   return( 849 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0111_REQ::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0111_REQ::fieldExists( id );
}

bool dsi_DSTC0111_REQ::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40000029: return( true );
      case 40000005: return( true );
      case 40000002: return( true );
      case 40000030: return( true );
      case 40000031: return( true );
      case 40000040: return( true );
      case 40001508: return( true );
      case 40002065: return( true );
      case 40002066: return( true );
      case 40003187: return( true );
      case 40000095: return( true );
      case 40000433: return( true );
      case 40000435: return( true );
      case 40000786: return( true );
      case 40006114: return( true );
      case 40000067: return( true );
      case 40000068: return( true );
      case 40006282: return( true );
      case 40006283: return( true );
   }
   return false;
}

