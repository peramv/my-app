// BFDataImpl implementation file for DataSet DSTC0217.REQ
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0217_req.h"


// This function creates an instance of dsi_DSTC0217_REQ
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0217_REQ() { return new dsi_DSTC0217_REQ; }

dsi_DSTC0217_REQ::dsi_DSTC0217_REQ()
: BFDataImpl( 40003398, 40003414 )
, SessionId_( ifds::SessionId, &ifds::s_FldProp_SessionId )
, User_Id_( ifds::User_Id, &ifds::s_FldProp_User_Id )
, LanguageCode_( ifds::LanguageCode, &ifds::s_FldProp_LanguageCode )
, CompanyId_( ifds::CompanyId, &ifds::s_FldProp_CompanyId )
, Track_( ifds::Track, &ifds::s_FldProp_Track )
, Activity_( ifds::Activity, &ifds::s_FldProp_Activity )
, AccountNum_( ifds::AccountNum, &ifds::s_FldProp_AccountNum )
, TradeDate_( ifds::TradeDate, &ifds::s_FldProp_TradeDate )
, GrossOrNet_( ifds::GrossOrNet, &ifds::s_FldProp_GrossOrNet )
, AmtType_( ifds::AmtType, &ifds::s_FldProp_AmtType )
, FullRed_( ifds::FullRed, &ifds::s_FldProp_FullRed )
, RedCode_( ifds::RedCode, &ifds::s_FldProp_RedCode )
, AcctLvlDSC_( ifds::AcctLvlDSC, &ifds::s_FldProp_AcctLvlDSC )
, NextKey_( ifds::NextKey, &ifds::s_FldProp_NextKey )
, RepeatCount_( ifds::RepeatCount, &ifds::s_FldProp_RepeatCount )
{
   cFields_ = 15;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0217_REQ::~dsi_DSTC0217_REQ()
{
}

BFDataImpl* dsi_DSTC0217_REQ::clone()
{
   dsi_DSTC0217_REQ* p = new dsi_DSTC0217_REQ;
   p->SessionId_ = SessionId_;
   p->User_Id_ = User_Id_;
   p->LanguageCode_ = LanguageCode_;
   p->CompanyId_ = CompanyId_;
   p->Track_ = Track_;
   p->Activity_ = Activity_;
   p->AccountNum_ = AccountNum_;
   p->TradeDate_ = TradeDate_;
   p->GrossOrNet_ = GrossOrNet_;
   p->AmtType_ = AmtType_;
   p->FullRed_ = FullRed_;
   p->RedCode_ = RedCode_;
   p->AcctLvlDSC_ = AcctLvlDSC_;
   p->NextKey_ = NextKey_;
   p->RepeatCount_ = RepeatCount_;
   return(p);
}

BFDataField* dsi_DSTC0217_REQ::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40000005: return ( &SessionId_ ); break; // SessionId
      case 40000002: return ( &User_Id_ ); break; // User_Id
      case 40000030: return ( &LanguageCode_ ); break; // LanguageCode
      case 40000031: return ( &CompanyId_ ); break; // CompanyId
      case 40002065: return ( &Track_ ); break; // Track
      case 40002066: return ( &Activity_ ); break; // Activity
      case 40000040: return ( &AccountNum_ ); break; // AccountNum
      case 40000097: return ( &TradeDate_ ); break; // TradeDate
      case 40000234: return ( &GrossOrNet_ ); break; // GrossOrNet
      case 40000726: return ( &AmtType_ ); break; // AmtType
      case 40003395: return ( &FullRed_ ); break; // FullRed
      case 40000435: return ( &RedCode_ ); break; // RedCode
      case 40003413: return ( &AcctLvlDSC_ ); break; // AcctLvlDSC
      case 40000029: return ( &NextKey_ ); break; // NextKey
      case 40000120: return ( &RepeatCount_ ); break; // RepeatCount
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0217_REQ::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0217_REQ* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0217_REQ::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 15 )
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
            case 6: aFlds_[6] = &AccountNum_; break;
            case 7: aFlds_[7] = &TradeDate_; break;
            case 8: aFlds_[8] = &GrossOrNet_; break;
            case 9: aFlds_[9] = &AmtType_; break;
            case 10: aFlds_[10] = &FullRed_; break;
            case 11: aFlds_[11] = &RedCode_; break;
            case 12: aFlds_[12] = &AcctLvlDSC_; break;
            case 13: aFlds_[13] = &NextKey_; break;
            case 14: aFlds_[14] = &RepeatCount_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0217_REQ::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0217_REQ* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0217_REQ::getLargestDefinedField( void ) const
{
   return( 100 );
}

unsigned long dsi_DSTC0217_REQ::getDefinedByteLength( void ) const
{
   return( 584 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0217_REQ::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0217_REQ::fieldExists( id );
}

bool dsi_DSTC0217_REQ::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40000005: return( true );
      case 40000002: return( true );
      case 40000030: return( true );
      case 40000031: return( true );
      case 40002065: return( true );
      case 40002066: return( true );
      case 40000040: return( true );
      case 40000097: return( true );
      case 40000234: return( true );
      case 40000726: return( true );
      case 40003395: return( true );
      case 40000435: return( true );
      case 40003413: return( true );
      case 40000029: return( true );
      case 40000120: return( true );
   }
   return false;
}

