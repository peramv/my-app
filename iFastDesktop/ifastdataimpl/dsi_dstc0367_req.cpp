// BFDataImpl implementation file for DataSet DSTC0367.REQ
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0367_req.h"


// This function creates an instance of dsi_DSTC0367_REQ
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0367_REQ() { return new dsi_DSTC0367_REQ; }

dsi_DSTC0367_REQ::dsi_DSTC0367_REQ()
: BFDataImpl( 40005447 )
, SessionId_( ifds::SessionId, &ifds::s_FldProp_SessionId )
, User_Id_( ifds::User_Id, &ifds::s_FldProp_User_Id )
, LanguageCode_( ifds::LanguageCode, &ifds::s_FldProp_LanguageCode )
, CompanyId_( ifds::CompanyId, &ifds::s_FldProp_CompanyId )
, Track_( ifds::Track, &ifds::s_FldProp_Track )
, Activity_( ifds::Activity, &ifds::s_FldProp_Activity )
, ContractType_( ifds::ContractType, &ifds::s_FldProp_ContractType )
, TaxType_( ifds::TaxType, &ifds::s_FldProp_TaxType )
, ProvReg_( ifds::ProvReg, &ifds::s_FldProp_ProvReg )
, EffectiveDate_( ifds::EffectiveDate, &ifds::s_FldProp_EffectiveDate )
{
   cFields_ = 10;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0367_REQ::~dsi_DSTC0367_REQ()
{
}

BFDataImpl* dsi_DSTC0367_REQ::clone()
{
   dsi_DSTC0367_REQ* p = new dsi_DSTC0367_REQ;
   p->SessionId_ = SessionId_;
   p->User_Id_ = User_Id_;
   p->LanguageCode_ = LanguageCode_;
   p->CompanyId_ = CompanyId_;
   p->Track_ = Track_;
   p->Activity_ = Activity_;
   p->ContractType_ = ContractType_;
   p->TaxType_ = TaxType_;
   p->ProvReg_ = ProvReg_;
   p->EffectiveDate_ = EffectiveDate_;
   return(p);
}

BFDataField* dsi_DSTC0367_REQ::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40000005: return ( &SessionId_ ); break; // SessionId
      case 40000002: return ( &User_Id_ ); break; // User_Id
      case 40000030: return ( &LanguageCode_ ); break; // LanguageCode
      case 40000031: return ( &CompanyId_ ); break; // CompanyId
      case 40002065: return ( &Track_ ); break; // Track
      case 40002066: return ( &Activity_ ); break; // Activity
      case 40001385: return ( &ContractType_ ); break; // ContractType
      case 40000134: return ( &TaxType_ ); break; // TaxType
      case 40005448: return ( &ProvReg_ ); break; // ProvReg
      case 40000327: return ( &EffectiveDate_ ); break; // EffectiveDate
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0367_REQ::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0367_REQ* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0367_REQ::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 10 )
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
            case 6: aFlds_[6] = &ContractType_; break;
            case 7: aFlds_[7] = &TaxType_; break;
            case 8: aFlds_[8] = &ProvReg_; break;
            case 9: aFlds_[9] = &EffectiveDate_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0367_REQ::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0367_REQ* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0367_REQ::getLargestDefinedField( void ) const
{
   return( 60 );
}

unsigned long dsi_DSTC0367_REQ::getDefinedByteLength( void ) const
{
   return( 491 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0367_REQ::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0367_REQ::fieldExists( id );
}

bool dsi_DSTC0367_REQ::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40000005: return( true );
      case 40000002: return( true );
      case 40000030: return( true );
      case 40000031: return( true );
      case 40002065: return( true );
      case 40002066: return( true );
      case 40001385: return( true );
      case 40000134: return( true );
      case 40005448: return( true );
      case 40000327: return( true );
   }
   return false;
}

