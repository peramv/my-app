// BFDataImpl implementation file for DataSet DSTC0413.REQ
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0413_req.h"


// This function creates an instance of dsi_DSTC0413_REQ
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0413_REQ() { return new dsi_DSTC0413_REQ; }

dsi_DSTC0413_REQ::dsi_DSTC0413_REQ()
: BFDataImpl( 40006298 )
, SessionId_( ifds::SessionId, &ifds::s_FldProp_SessionId )
, User_Id_( ifds::User_Id, &ifds::s_FldProp_User_Id )
, LanguageCode_( ifds::LanguageCode, &ifds::s_FldProp_LanguageCode )
, CompanyId_( ifds::CompanyId, &ifds::s_FldProp_CompanyId )
, Track_( ifds::Track, &ifds::s_FldProp_Track )
, Activity_( ifds::Activity, &ifds::s_FldProp_Activity )
, RunMode_( ifds::RunMode, &ifds::s_FldProp_RunMode )
, AccountNum_( ifds::AccountNum, &ifds::s_FldProp_AccountNum )
, GuardOptCurrent_( ifds::GuardOptCurrent, &ifds::s_FldProp_GuardOptCurrent )
, GuardOptAfter_( ifds::GuardOptAfter, &ifds::s_FldProp_GuardOptAfter )
, DeffUntil_( ifds::DeffUntil, &ifds::s_FldProp_DeffUntil )
, SEGGuarGuardID_( ifds::SEGGuarGuardID, &ifds::s_FldProp_SEGGuarGuardID )
{
   cFields_ = 12;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0413_REQ::~dsi_DSTC0413_REQ()
{
}

BFDataImpl* dsi_DSTC0413_REQ::clone()
{
   dsi_DSTC0413_REQ* p = new dsi_DSTC0413_REQ;
   p->SessionId_ = SessionId_;
   p->User_Id_ = User_Id_;
   p->LanguageCode_ = LanguageCode_;
   p->CompanyId_ = CompanyId_;
   p->Track_ = Track_;
   p->Activity_ = Activity_;
   p->RunMode_ = RunMode_;
   p->AccountNum_ = AccountNum_;
   p->GuardOptCurrent_ = GuardOptCurrent_;
   p->GuardOptAfter_ = GuardOptAfter_;
   p->DeffUntil_ = DeffUntil_;
   p->SEGGuarGuardID_ = SEGGuarGuardID_;
   return(p);
}

BFDataField* dsi_DSTC0413_REQ::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40000005: return ( &SessionId_ ); break; // SessionId
      case 40000002: return ( &User_Id_ ); break; // User_Id
      case 40000030: return ( &LanguageCode_ ); break; // LanguageCode
      case 40000031: return ( &CompanyId_ ); break; // CompanyId
      case 40002065: return ( &Track_ ); break; // Track
      case 40002066: return ( &Activity_ ); break; // Activity
      case 40000990: return ( &RunMode_ ); break; // RunMode
      case 40000040: return ( &AccountNum_ ); break; // AccountNum
      case 40006293: return ( &GuardOptCurrent_ ); break; // GuardOptCurrent
      case 40006294: return ( &GuardOptAfter_ ); break; // GuardOptAfter
      case 40006295: return ( &DeffUntil_ ); break; // DeffUntil
      case 40006296: return ( &SEGGuarGuardID_ ); break; // SEGGuarGuardID
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0413_REQ::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0413_REQ* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0413_REQ::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 12 )
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
            case 6: aFlds_[6] = &RunMode_; break;
            case 7: aFlds_[7] = &AccountNum_; break;
            case 8: aFlds_[8] = &GuardOptCurrent_; break;
            case 9: aFlds_[9] = &GuardOptAfter_; break;
            case 10: aFlds_[10] = &DeffUntil_; break;
            case 11: aFlds_[11] = &SEGGuarGuardID_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0413_REQ::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0413_REQ* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0413_REQ::getLargestDefinedField( void ) const
{
   return( 60 );
}

unsigned long dsi_DSTC0413_REQ::getDefinedByteLength( void ) const
{
   return( 523 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0413_REQ::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0413_REQ::fieldExists( id );
}

bool dsi_DSTC0413_REQ::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40000005: return( true );
      case 40000002: return( true );
      case 40000030: return( true );
      case 40000031: return( true );
      case 40002065: return( true );
      case 40002066: return( true );
      case 40000990: return( true );
      case 40000040: return( true );
      case 40006293: return( true );
      case 40006294: return( true );
      case 40006295: return( true );
      case 40006296: return( true );
   }
   return false;
}

