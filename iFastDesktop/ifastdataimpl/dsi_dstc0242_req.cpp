// BFDataImpl implementation file for DataSet DSTC0242.REQ
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0242_req.h"


// This function creates an instance of dsi_DSTC0242_REQ
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0242_REQ() { return new dsi_DSTC0242_REQ; }

dsi_DSTC0242_REQ::dsi_DSTC0242_REQ()
: BFDataImpl( 40003690, 40003691 )
, SessionId_( ifds::SessionId, &ifds::s_FldProp_SessionId )
, User_Id_( ifds::User_Id, &ifds::s_FldProp_User_Id )
, LanguageCode_( ifds::LanguageCode, &ifds::s_FldProp_LanguageCode )
, CompanyId_( ifds::CompanyId, &ifds::s_FldProp_CompanyId )
, Track_( ifds::Track, &ifds::s_FldProp_Track )
, Activity_( ifds::Activity, &ifds::s_FldProp_Activity )
, OverrideRepeats_( ifds::OverrideRepeats, &ifds::s_FldProp_OverrideRepeats )
, RunMode_( ifds::RunMode, &ifds::s_FldProp_RunMode )
, MktIndexVer_( ifds::MktIndexVer, &ifds::s_FldProp_MktIndexVer )
, MktIndexRid_( ifds::MktIndexRid, &ifds::s_FldProp_MktIndexRid )
, IndexCode_( ifds::IndexCode, &ifds::s_FldProp_IndexCode )
, IndexName_( ifds::IndexName, &ifds::s_FldProp_IndexName )
, DaysBasis_( ifds::DaysBasis, &ifds::s_FldProp_DaysBasis )
, InputDataType_( ifds::InputDataType, &ifds::s_FldProp_InputDataType )
, RepeatCount_( ifds::RepeatCount, &ifds::s_FldProp_RepeatCount )
{
   cFields_ = 15;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0242_REQ::~dsi_DSTC0242_REQ()
{
}

BFDataImpl* dsi_DSTC0242_REQ::clone()
{
   dsi_DSTC0242_REQ* p = new dsi_DSTC0242_REQ;
   p->SessionId_ = SessionId_;
   p->User_Id_ = User_Id_;
   p->LanguageCode_ = LanguageCode_;
   p->CompanyId_ = CompanyId_;
   p->Track_ = Track_;
   p->Activity_ = Activity_;
   p->OverrideRepeats_ = OverrideRepeats_;
   p->RunMode_ = RunMode_;
   p->MktIndexVer_ = MktIndexVer_;
   p->MktIndexRid_ = MktIndexRid_;
   p->IndexCode_ = IndexCode_;
   p->IndexName_ = IndexName_;
   p->DaysBasis_ = DaysBasis_;
   p->InputDataType_ = InputDataType_;
   p->RepeatCount_ = RepeatCount_;
   return(p);
}

BFDataField* dsi_DSTC0242_REQ::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40000005: return ( &SessionId_ ); break; // SessionId
      case 40000002: return ( &User_Id_ ); break; // User_Id
      case 40000030: return ( &LanguageCode_ ); break; // LanguageCode
      case 40000031: return ( &CompanyId_ ); break; // CompanyId
      case 40002065: return ( &Track_ ); break; // Track
      case 40002066: return ( &Activity_ ); break; // Activity
      case 40002139: return ( &OverrideRepeats_ ); break; // OverrideRepeats
      case 40000990: return ( &RunMode_ ); break; // RunMode
      case 40003661: return ( &MktIndexVer_ ); break; // MktIndexVer
      case 40003660: return ( &MktIndexRid_ ); break; // MktIndexRid
      case 40003658: return ( &IndexCode_ ); break; // IndexCode
      case 40003659: return ( &IndexName_ ); break; // IndexName
      case 40006660: return ( &DaysBasis_ ); break; // DaysBasis
      case 40006659: return ( &InputDataType_ ); break; // InputDataType
      case 40000120: return ( &RepeatCount_ ); break; // RepeatCount
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0242_REQ::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0242_REQ* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0242_REQ::getElementByIndex( unsigned int iField )
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
            case 6: aFlds_[6] = &OverrideRepeats_; break;
            case 7: aFlds_[7] = &RunMode_; break;
            case 8: aFlds_[8] = &MktIndexVer_; break;
            case 9: aFlds_[9] = &MktIndexRid_; break;
            case 10: aFlds_[10] = &IndexCode_; break;
            case 11: aFlds_[11] = &IndexName_; break;
            case 12: aFlds_[12] = &DaysBasis_; break;
            case 13: aFlds_[13] = &InputDataType_; break;
            case 14: aFlds_[14] = &RepeatCount_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0242_REQ::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0242_REQ* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0242_REQ::getLargestDefinedField( void ) const
{
   return( 60 );
}

unsigned long dsi_DSTC0242_REQ::getDefinedByteLength( void ) const
{
   return( 566 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0242_REQ::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0242_REQ::fieldExists( id );
}

bool dsi_DSTC0242_REQ::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40000005: return( true );
      case 40000002: return( true );
      case 40000030: return( true );
      case 40000031: return( true );
      case 40002065: return( true );
      case 40002066: return( true );
      case 40002139: return( true );
      case 40000990: return( true );
      case 40003661: return( true );
      case 40003660: return( true );
      case 40003658: return( true );
      case 40003659: return( true );
      case 40006660: return( true );
      case 40006659: return( true );
      case 40000120: return( true );
   }
   return false;
}

