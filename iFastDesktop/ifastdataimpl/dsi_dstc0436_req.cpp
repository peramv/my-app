// BFDataImpl implementation file for DataSet DSTC0436.REQ
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0436_req.h"


// This function creates an instance of dsi_DSTC0436_REQ
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0436_REQ() { return new dsi_DSTC0436_REQ; }

dsi_DSTC0436_REQ::dsi_DSTC0436_REQ()
: BFDataImpl( 40006800 )
, SessionId_( ifds::SessionId, &ifds::s_FldProp_SessionId )
, User_Id_( ifds::User_Id, &ifds::s_FldProp_User_Id )
, LanguageCode_( ifds::LanguageCode, &ifds::s_FldProp_LanguageCode )
, CompanyId_( ifds::CompanyId, &ifds::s_FldProp_CompanyId )
, Track_( ifds::Track, &ifds::s_FldProp_Track )
, Activity_( ifds::Activity, &ifds::s_FldProp_Activity )
, AccountNum_( ifds::AccountNum, &ifds::s_FldProp_AccountNum )
, FundCode_( ifds::FundCode, &ifds::s_FldProp_FundCode )
, ClassCode_( ifds::ClassCode, &ifds::s_FldProp_ClassCode )
, TradeDate_( ifds::TradeDate, &ifds::s_FldProp_TradeDate )
, ValidateType_( ifds::ValidateType, &ifds::s_FldProp_ValidateType )
, TransType_( ifds::TransType, &ifds::s_FldProp_TransType )
, TransId_( ifds::TransId, &ifds::s_FldProp_TransId )
, AccountTo_( ifds::AccountTo, &ifds::s_FldProp_AccountTo )
, FundTo_( ifds::FundTo, &ifds::s_FldProp_FundTo )
, ClassTo_( ifds::ClassTo, &ifds::s_FldProp_ClassTo )
{
   cFields_ = 16;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0436_REQ::~dsi_DSTC0436_REQ()
{
}

BFDataImpl* dsi_DSTC0436_REQ::clone()
{
   dsi_DSTC0436_REQ* p = new dsi_DSTC0436_REQ;
   p->SessionId_ = SessionId_;
   p->User_Id_ = User_Id_;
   p->LanguageCode_ = LanguageCode_;
   p->CompanyId_ = CompanyId_;
   p->Track_ = Track_;
   p->Activity_ = Activity_;
   p->AccountNum_ = AccountNum_;
   p->FundCode_ = FundCode_;
   p->ClassCode_ = ClassCode_;
   p->TradeDate_ = TradeDate_;
   p->ValidateType_ = ValidateType_;
   p->TransType_ = TransType_;
   p->TransId_ = TransId_;
   p->AccountTo_ = AccountTo_;
   p->FundTo_ = FundTo_;
   p->ClassTo_ = ClassTo_;
   return(p);
}

BFDataField* dsi_DSTC0436_REQ::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40000005: return ( &SessionId_ ); break; // SessionId
      case 40000002: return ( &User_Id_ ); break; // User_Id
      case 40000030: return ( &LanguageCode_ ); break; // LanguageCode
      case 40000031: return ( &CompanyId_ ); break; // CompanyId
      case 40002065: return ( &Track_ ); break; // Track
      case 40002066: return ( &Activity_ ); break; // Activity
      case 40000040: return ( &AccountNum_ ); break; // AccountNum
      case 40000049: return ( &FundCode_ ); break; // FundCode
      case 40000050: return ( &ClassCode_ ); break; // ClassCode
      case 40000097: return ( &TradeDate_ ); break; // TradeDate
      case 40003549: return ( &ValidateType_ ); break; // ValidateType
      case 40000095: return ( &TransType_ ); break; // TransType
      case 40000063: return ( &TransId_ ); break; // TransId
      case 40000646: return ( &AccountTo_ ); break; // AccountTo
      case 40000648: return ( &FundTo_ ); break; // FundTo
      case 40000649: return ( &ClassTo_ ); break; // ClassTo
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0436_REQ::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0436_REQ* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0436_REQ::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 16 )
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
            case 7: aFlds_[7] = &FundCode_; break;
            case 8: aFlds_[8] = &ClassCode_; break;
            case 9: aFlds_[9] = &TradeDate_; break;
            case 10: aFlds_[10] = &ValidateType_; break;
            case 11: aFlds_[11] = &TransType_; break;
            case 12: aFlds_[12] = &TransId_; break;
            case 13: aFlds_[13] = &AccountTo_; break;
            case 14: aFlds_[14] = &FundTo_; break;
            case 15: aFlds_[15] = &ClassTo_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0436_REQ::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0436_REQ* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0436_REQ::getLargestDefinedField( void ) const
{
   return( 200 );
}

unsigned long dsi_DSTC0436_REQ::getDefinedByteLength( void ) const
{
   return( 928 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0436_REQ::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0436_REQ::fieldExists( id );
}

bool dsi_DSTC0436_REQ::fieldExists( const BFFieldId& id )
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
      case 40000049: return( true );
      case 40000050: return( true );
      case 40000097: return( true );
      case 40003549: return( true );
      case 40000095: return( true );
      case 40000063: return( true );
      case 40000646: return( true );
      case 40000648: return( true );
      case 40000649: return( true );
   }
   return false;
}

