// BFDataImpl implementation file for DataSet DSTC0380.REQ
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0380_req.h"


// This function creates an instance of dsi_DSTC0380_REQ
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0380_REQ() { return new dsi_DSTC0380_REQ; }

dsi_DSTC0380_REQ::dsi_DSTC0380_REQ()
: BFDataImpl( 40005602 )
, SessionId_( ifds::SessionId, &ifds::s_FldProp_SessionId )
, User_Id_( ifds::User_Id, &ifds::s_FldProp_User_Id )
, LanguageCode_( ifds::LanguageCode, &ifds::s_FldProp_LanguageCode )
, CompanyId_( ifds::CompanyId, &ifds::s_FldProp_CompanyId )
, Track_( ifds::Track, &ifds::s_FldProp_Track )
, Activity_( ifds::Activity, &ifds::s_FldProp_Activity )
, NextKey_( ifds::NextKey, &ifds::s_FldProp_NextKey )
, AccountNum_( ifds::AccountNum, &ifds::s_FldProp_AccountNum )
, AMSType_( ifds::AMSType, &ifds::s_FldProp_AMSType )
, AMSCode_( ifds::AMSCode, &ifds::s_FldProp_AMSCode )
, Deff_( ifds::Deff, &ifds::s_FldProp_Deff )
, StopDate_( ifds::StopDate, &ifds::s_FldProp_StopDate )
, DuplicateCheck_( ifds::DuplicateCheck, &ifds::s_FldProp_DuplicateCheck )
{
   cFields_ = 13;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0380_REQ::~dsi_DSTC0380_REQ()
{
}

BFDataImpl* dsi_DSTC0380_REQ::clone()
{
   dsi_DSTC0380_REQ* p = new dsi_DSTC0380_REQ;
   p->SessionId_ = SessionId_;
   p->User_Id_ = User_Id_;
   p->LanguageCode_ = LanguageCode_;
   p->CompanyId_ = CompanyId_;
   p->Track_ = Track_;
   p->Activity_ = Activity_;
   p->NextKey_ = NextKey_;
   p->AccountNum_ = AccountNum_;
   p->AMSType_ = AMSType_;
   p->AMSCode_ = AMSCode_;
   p->Deff_ = Deff_;
   p->StopDate_ = StopDate_;
   p->DuplicateCheck_ = DuplicateCheck_;
   return(p);
}

BFDataField* dsi_DSTC0380_REQ::getElement( const BFFieldId& id )
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
      case 40003518: return ( &AMSType_ ); break; // AMSType
      case 40000193: return ( &AMSCode_ ); break; // AMSCode
      case 40000215: return ( &Deff_ ); break; // Deff
      case 40000279: return ( &StopDate_ ); break; // StopDate
      case 40003976: return ( &DuplicateCheck_ ); break; // DuplicateCheck
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0380_REQ::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0380_REQ* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0380_REQ::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 13 )
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
            case 8: aFlds_[8] = &AMSType_; break;
            case 9: aFlds_[9] = &AMSCode_; break;
            case 10: aFlds_[10] = &Deff_; break;
            case 11: aFlds_[11] = &StopDate_; break;
            case 12: aFlds_[12] = &DuplicateCheck_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0380_REQ::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0380_REQ* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0380_REQ::getLargestDefinedField( void ) const
{
   return( 100 );
}

unsigned long dsi_DSTC0380_REQ::getDefinedByteLength( void ) const
{
   return( 502 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0380_REQ::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0380_REQ::fieldExists( id );
}

bool dsi_DSTC0380_REQ::fieldExists( const BFFieldId& id )
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
      case 40003518: return( true );
      case 40000193: return( true );
      case 40000215: return( true );
      case 40000279: return( true );
      case 40003976: return( true );
   }
   return false;
}

