// BFDataImpl implementation file for DataSet DSTC0405.REQ
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0405_req.h"


// This function creates an instance of dsi_DSTC0405_REQ
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0405_REQ() { return new dsi_DSTC0405_REQ; }

dsi_DSTC0405_REQ::dsi_DSTC0405_REQ()
: BFDataImpl( 40006156 )
, SessionId_( ifds::SessionId, &ifds::s_FldProp_SessionId )
, User_Id_( ifds::User_Id, &ifds::s_FldProp_User_Id )
, LanguageCode_( ifds::LanguageCode, &ifds::s_FldProp_LanguageCode )
, CompanyId_( ifds::CompanyId, &ifds::s_FldProp_CompanyId )
, Track_( ifds::Track, &ifds::s_FldProp_Track )
, Activity_( ifds::Activity, &ifds::s_FldProp_Activity )
, NextKey_( ifds::NextKey, &ifds::s_FldProp_NextKey )
, AccountNum_( ifds::AccountNum, &ifds::s_FldProp_AccountNum )
, TransType_( ifds::TransType, &ifds::s_FldProp_TransType )
, Fund_( ifds::Fund, &ifds::s_FldProp_Fund )
, Class_( ifds::Class, &ifds::s_FldProp_Class )
, DepositType_( ifds::DepositType, &ifds::s_FldProp_DepositType )
, RedCode_( ifds::RedCode, &ifds::s_FldProp_RedCode )
, TradeDate_( ifds::TradeDate, &ifds::s_FldProp_TradeDate )
, SettleDate_( ifds::SettleDate, &ifds::s_FldProp_SettleDate )
, AmountType_( ifds::AmountType, &ifds::s_FldProp_AmountType )
, Amount_( ifds::Amount, &ifds::s_FldProp_Amount )
, GrossOrNet_( ifds::GrossOrNet, &ifds::s_FldProp_GrossOrNet )
, RESPBenefId_( ifds::RESPBenefId, &ifds::s_FldProp_RESPBenefId )
, Fee_( ifds::Fee, &ifds::s_FldProp_Fee )
, FlatPrcnt_( ifds::FlatPrcnt, &ifds::s_FldProp_FlatPrcnt )
, OCRdmYear_( ifds::OCRdmYear, &ifds::s_FldProp_OCRdmYear )
, RESPContrDetlTaxYear_( ifds::RESPContrDetlTaxYear, &ifds::s_FldProp_RESPContrDetlTaxYear )
, AssistedContrAmt_( ifds::AssistedContrAmt, &ifds::s_FldProp_AssistedContrAmt )
{
   cFields_ = 24;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0405_REQ::~dsi_DSTC0405_REQ()
{
}

BFDataImpl* dsi_DSTC0405_REQ::clone()
{
   dsi_DSTC0405_REQ* p = new dsi_DSTC0405_REQ;
   p->SessionId_ = SessionId_;
   p->User_Id_ = User_Id_;
   p->LanguageCode_ = LanguageCode_;
   p->CompanyId_ = CompanyId_;
   p->Track_ = Track_;
   p->Activity_ = Activity_;
   p->NextKey_ = NextKey_;
   p->AccountNum_ = AccountNum_;
   p->TransType_ = TransType_;
   p->Fund_ = Fund_;
   p->Class_ = Class_;
   p->DepositType_ = DepositType_;
   p->RedCode_ = RedCode_;
   p->TradeDate_ = TradeDate_;
   p->SettleDate_ = SettleDate_;
   p->AmountType_ = AmountType_;
   p->Amount_ = Amount_;
   p->GrossOrNet_ = GrossOrNet_;
   p->RESPBenefId_ = RESPBenefId_;
   p->Fee_ = Fee_;
   p->FlatPrcnt_ = FlatPrcnt_;
   p->OCRdmYear_ = OCRdmYear_;
   p->RESPContrDetlTaxYear_ = RESPContrDetlTaxYear_;
   p->AssistedContrAmt_ = AssistedContrAmt_;
   return(p);
}

BFDataField* dsi_DSTC0405_REQ::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40000005: return ( &SessionId_ ); break; // SessionId
      case 40000002: return ( &User_Id_ ); break; // User_Id
      case 40000030: return ( &LanguageCode_ ); break; // LanguageCode
      case 40000031: return ( &CompanyId_ ); break; // CompanyId
      case 40002065: return ( &Track_ ); break; // Track
      case 40002066: return ( &Activity_ ); break; // Activity
      case 40000029: return ( &NextKey_ ); break; // NextKey
      case 40000040: return ( &AccountNum_ ); break; // AccountNum
      case 40000095: return ( &TransType_ ); break; // TransType
      case 40002227: return ( &Fund_ ); break; // Fund
      case 40002228: return ( &Class_ ); break; // Class
      case 40000433: return ( &DepositType_ ); break; // DepositType
      case 40000435: return ( &RedCode_ ); break; // RedCode
      case 40000097: return ( &TradeDate_ ); break; // TradeDate
      case 40000348: return ( &SettleDate_ ); break; // SettleDate
      case 40000232: return ( &AmountType_ ); break; // AmountType
      case 40000231: return ( &Amount_ ); break; // Amount
      case 40000234: return ( &GrossOrNet_ ); break; // GrossOrNet
      case 40006114: return ( &RESPBenefId_ ); break; // RESPBenefId
      case 40000235: return ( &Fee_ ); break; // Fee
      case 40002230: return ( &FlatPrcnt_ ); break; // FlatPrcnt
      case 40006142: return ( &OCRdmYear_ ); break; // OCRdmYear
      case 40006254: return ( &RESPContrDetlTaxYear_ ); break; // RESPContrDetlTaxYear
      case 40006268: return ( &AssistedContrAmt_ ); break; // AssistedContrAmt
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0405_REQ::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0405_REQ* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0405_REQ::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 24 )
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
            case 6: aFlds_[6] = &NextKey_; break;
            case 7: aFlds_[7] = &AccountNum_; break;
            case 8: aFlds_[8] = &TransType_; break;
            case 9: aFlds_[9] = &Fund_; break;
            case 10: aFlds_[10] = &Class_; break;
            case 11: aFlds_[11] = &DepositType_; break;
            case 12: aFlds_[12] = &RedCode_; break;
            case 13: aFlds_[13] = &TradeDate_; break;
            case 14: aFlds_[14] = &SettleDate_; break;
            case 15: aFlds_[15] = &AmountType_; break;
            case 16: aFlds_[16] = &Amount_; break;
            case 17: aFlds_[17] = &GrossOrNet_; break;
            case 18: aFlds_[18] = &RESPBenefId_; break;
            case 19: aFlds_[19] = &Fee_; break;
            case 20: aFlds_[20] = &FlatPrcnt_; break;
            case 21: aFlds_[21] = &OCRdmYear_; break;
            case 22: aFlds_[22] = &RESPContrDetlTaxYear_; break;
            case 23: aFlds_[23] = &AssistedContrAmt_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0405_REQ::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0405_REQ* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0405_REQ::getLargestDefinedField( void ) const
{
   return( 100 );
}

unsigned long dsi_DSTC0405_REQ::getDefinedByteLength( void ) const
{
   return( 918 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0405_REQ::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0405_REQ::fieldExists( id );
}

bool dsi_DSTC0405_REQ::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40000005: return( true );
      case 40000002: return( true );
      case 40000030: return( true );
      case 40000031: return( true );
      case 40002065: return( true );
      case 40002066: return( true );
      case 40000029: return( true );
      case 40000040: return( true );
      case 40000095: return( true );
      case 40002227: return( true );
      case 40002228: return( true );
      case 40000433: return( true );
      case 40000435: return( true );
      case 40000097: return( true );
      case 40000348: return( true );
      case 40000232: return( true );
      case 40000231: return( true );
      case 40000234: return( true );
      case 40006114: return( true );
      case 40000235: return( true );
      case 40002230: return( true );
      case 40006142: return( true );
      case 40006254: return( true );
      case 40006268: return( true );
   }
   return false;
}

