// BFDataImpl implementation file for DataSet DSTC0298.REQ
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0298_req.h"


// This function creates an instance of dsi_DSTC0298_REQ
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0298_REQ() { return new dsi_DSTC0298_REQ; }

dsi_DSTC0298_REQ::dsi_DSTC0298_REQ()
: BFDataImpl( 40004599 )
, SessionId_( ifds::SessionId, &ifds::s_FldProp_SessionId )
, User_Id_( ifds::User_Id, &ifds::s_FldProp_User_Id )
, LanguageCode_( ifds::LanguageCode, &ifds::s_FldProp_LanguageCode )
, CompanyId_( ifds::CompanyId, &ifds::s_FldProp_CompanyId )
, Track_( ifds::Track, &ifds::s_FldProp_Track )
, Activity_( ifds::Activity, &ifds::s_FldProp_Activity )
, TransNum_( ifds::TransNum, &ifds::s_FldProp_TransNum )
, AccountNum_( ifds::AccountNum, &ifds::s_FldProp_AccountNum )
{
   cFields_ = 8;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0298_REQ::~dsi_DSTC0298_REQ()
{
}

BFDataImpl* dsi_DSTC0298_REQ::clone()
{
   dsi_DSTC0298_REQ* p = new dsi_DSTC0298_REQ;
   p->SessionId_ = SessionId_;
   p->User_Id_ = User_Id_;
   p->LanguageCode_ = LanguageCode_;
   p->CompanyId_ = CompanyId_;
   p->Track_ = Track_;
   p->Activity_ = Activity_;
   p->TransNum_ = TransNum_;
   p->AccountNum_ = AccountNum_;
   return(p);
}

BFDataField* dsi_DSTC0298_REQ::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40000005: return ( &SessionId_ ); break; // SessionId
      case 40000002: return ( &User_Id_ ); break; // User_Id
      case 40000030: return ( &LanguageCode_ ); break; // LanguageCode
      case 40000031: return ( &CompanyId_ ); break; // CompanyId
      case 40002065: return ( &Track_ ); break; // Track
      case 40002066: return ( &Activity_ ); break; // Activity
      case 40000096: return ( &TransNum_ ); break; // TransNum
      case 40000040: return ( &AccountNum_ ); break; // AccountNum
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0298_REQ::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0298_REQ* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0298_REQ::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 8 )
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
            case 6: aFlds_[6] = &TransNum_; break;
            case 7: aFlds_[7] = &AccountNum_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0298_REQ::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0298_REQ* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0298_REQ::getLargestDefinedField( void ) const
{
   return( 60 );
}

unsigned long dsi_DSTC0298_REQ::getDefinedByteLength( void ) const
{
   return( 335 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0298_REQ::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0298_REQ::fieldExists( id );
}

bool dsi_DSTC0298_REQ::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40000005: return( true );
      case 40000002: return( true );
      case 40000030: return( true );
      case 40000031: return( true );
      case 40002065: return( true );
      case 40002066: return( true );
      case 40000096: return( true );
      case 40000040: return( true );
   }
   return false;
}

