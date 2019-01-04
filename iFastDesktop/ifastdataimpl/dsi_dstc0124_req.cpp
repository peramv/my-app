// BFDataImpl implementation file for DataSet DSTC0124.REQ
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0124_req.h"


// This function creates an instance of dsi_DSTC0124_REQ
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0124_REQ() { return new dsi_DSTC0124_REQ; }

dsi_DSTC0124_REQ::dsi_DSTC0124_REQ()
: BFDataImpl( 40001454 )
, SessionId_( ifds::SessionId, &ifds::s_FldProp_SessionId )
, User_Id_( ifds::User_Id, &ifds::s_FldProp_User_Id )
, LanguageCode_( ifds::LanguageCode, &ifds::s_FldProp_LanguageCode )
, CompanyId_( ifds::CompanyId, &ifds::s_FldProp_CompanyId )
, BatchName_( ifds::BatchName, &ifds::s_FldProp_BatchName )
, BatchSrchType_( ifds::BatchSrchType, &ifds::s_FldProp_BatchSrchType )
, Track_( ifds::Track, &ifds::s_FldProp_Track )
, Activity_( ifds::Activity, &ifds::s_FldProp_Activity )
{
   cFields_ = 8;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0124_REQ::~dsi_DSTC0124_REQ()
{
}

BFDataImpl* dsi_DSTC0124_REQ::clone()
{
   dsi_DSTC0124_REQ* p = new dsi_DSTC0124_REQ;
   p->SessionId_ = SessionId_;
   p->User_Id_ = User_Id_;
   p->LanguageCode_ = LanguageCode_;
   p->CompanyId_ = CompanyId_;
   p->BatchName_ = BatchName_;
   p->BatchSrchType_ = BatchSrchType_;
   p->Track_ = Track_;
   p->Activity_ = Activity_;
   return(p);
}

BFDataField* dsi_DSTC0124_REQ::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40000005: return ( &SessionId_ ); break; // SessionId
      case 40000002: return ( &User_Id_ ); break; // User_Id
      case 40000030: return ( &LanguageCode_ ); break; // LanguageCode
      case 40000031: return ( &CompanyId_ ); break; // CompanyId
      case 40000653: return ( &BatchName_ ); break; // BatchName
      case 40001452: return ( &BatchSrchType_ ); break; // BatchSrchType
      case 40002065: return ( &Track_ ); break; // Track
      case 40002066: return ( &Activity_ ); break; // Activity
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0124_REQ::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0124_REQ* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0124_REQ::getElementByIndex( unsigned int iField )
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
            case 4: aFlds_[4] = &BatchName_; break;
            case 5: aFlds_[5] = &BatchSrchType_; break;
            case 6: aFlds_[6] = &Track_; break;
            case 7: aFlds_[7] = &Activity_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0124_REQ::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0124_REQ* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0124_REQ::getLargestDefinedField( void ) const
{
   return( 60 );
}

unsigned long dsi_DSTC0124_REQ::getDefinedByteLength( void ) const
{
   return( 421 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0124_REQ::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0124_REQ::fieldExists( id );
}

bool dsi_DSTC0124_REQ::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40000005: return( true );
      case 40000002: return( true );
      case 40000030: return( true );
      case 40000031: return( true );
      case 40000653: return( true );
      case 40001452: return( true );
      case 40002065: return( true );
      case 40002066: return( true );
   }
   return false;
}

