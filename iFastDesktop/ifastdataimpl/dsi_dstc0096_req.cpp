// BFDataImpl implementation file for DataSet DSTC0096.REQ
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0096_req.h"


// This function creates an instance of dsi_DSTC0096_REQ
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0096_REQ() { return new dsi_DSTC0096_REQ; }

dsi_DSTC0096_REQ::dsi_DSTC0096_REQ()
: BFDataImpl( 40001050, 40001051 )
, SessionId_( ifds::SessionId, &ifds::s_FldProp_SessionId )
, User_Id_( ifds::User_Id, &ifds::s_FldProp_User_Id )
, LanguageCode_( ifds::LanguageCode, &ifds::s_FldProp_LanguageCode )
, CompanyId_( ifds::CompanyId, &ifds::s_FldProp_CompanyId )
, AccountNum_( ifds::AccountNum, &ifds::s_FldProp_AccountNum )
, Track_( ifds::Track, &ifds::s_FldProp_Track )
, Activity_( ifds::Activity, &ifds::s_FldProp_Activity )
, BusinessArea_( ifds::BusinessArea, &ifds::s_FldProp_BusinessArea )
, WorkType_( ifds::WorkType, &ifds::s_FldProp_WorkType )
, AWDObjectId_( ifds::AWDObjectId, &ifds::s_FldProp_AWDObjectId )
, AWDCrda_( ifds::AWDCrda, &ifds::s_FldProp_AWDCrda )
, RepeatCount_( ifds::RepeatCount, &ifds::s_FldProp_RepeatCount )
{
   cFields_ = 12;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0096_REQ::~dsi_DSTC0096_REQ()
{
}

BFDataImpl* dsi_DSTC0096_REQ::clone()
{
   dsi_DSTC0096_REQ* p = new dsi_DSTC0096_REQ;
   p->SessionId_ = SessionId_;
   p->User_Id_ = User_Id_;
   p->LanguageCode_ = LanguageCode_;
   p->CompanyId_ = CompanyId_;
   p->AccountNum_ = AccountNum_;
   p->Track_ = Track_;
   p->Activity_ = Activity_;
   p->BusinessArea_ = BusinessArea_;
   p->WorkType_ = WorkType_;
   p->AWDObjectId_ = AWDObjectId_;
   p->AWDCrda_ = AWDCrda_;
   p->RepeatCount_ = RepeatCount_;
   return(p);
}

BFDataField* dsi_DSTC0096_REQ::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40000005: return ( &SessionId_ ); break; // SessionId
      case 40000002: return ( &User_Id_ ); break; // User_Id
      case 40000030: return ( &LanguageCode_ ); break; // LanguageCode
      case 40000031: return ( &CompanyId_ ); break; // CompanyId
      case 40000040: return ( &AccountNum_ ); break; // AccountNum
      case 40002065: return ( &Track_ ); break; // Track
      case 40002066: return ( &Activity_ ); break; // Activity
      case 40001211: return ( &BusinessArea_ ); break; // BusinessArea
      case 40001212: return ( &WorkType_ ); break; // WorkType
      case 40005715: return ( &AWDObjectId_ ); break; // AWDObjectId
      case 40005718: return ( &AWDCrda_ ); break; // AWDCrda
      case 40000120: return ( &RepeatCount_ ); break; // RepeatCount
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0096_REQ::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0096_REQ* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0096_REQ::getElementByIndex( unsigned int iField )
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
            case 4: aFlds_[4] = &AccountNum_; break;
            case 5: aFlds_[5] = &Track_; break;
            case 6: aFlds_[6] = &Activity_; break;
            case 7: aFlds_[7] = &BusinessArea_; break;
            case 8: aFlds_[8] = &WorkType_; break;
            case 9: aFlds_[9] = &AWDObjectId_; break;
            case 10: aFlds_[10] = &AWDCrda_; break;
            case 11: aFlds_[11] = &RepeatCount_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0096_REQ::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0096_REQ* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0096_REQ::getLargestDefinedField( void ) const
{
   return( 60 );
}

unsigned long dsi_DSTC0096_REQ::getDefinedByteLength( void ) const
{
   return( 573 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0096_REQ::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0096_REQ::fieldExists( id );
}

bool dsi_DSTC0096_REQ::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40000005: return( true );
      case 40000002: return( true );
      case 40000030: return( true );
      case 40000031: return( true );
      case 40000040: return( true );
      case 40002065: return( true );
      case 40002066: return( true );
      case 40001211: return( true );
      case 40001212: return( true );
      case 40005715: return( true );
      case 40005718: return( true );
      case 40000120: return( true );
   }
   return false;
}

