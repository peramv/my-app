// BFDataImpl implementation file for DataSet DSTC0079.REQRepeat_Record
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0079_reqrepeat_record.h"


// This function creates an instance of dsi_DSTC0079_REQRepeat_Record
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0079_REQRepeat_Record() { return new dsi_DSTC0079_REQRepeat_Record; }

dsi_DSTC0079_REQRepeat_Record::dsi_DSTC0079_REQRepeat_Record()
: BFDataImpl( 40001190 )
, RunMode_( ifds::RunMode, &ifds::s_FldProp_RunMode )
, EntityId_( ifds::EntityId, &ifds::s_FldProp_EntityId )
, IdType_( ifds::IdType, &ifds::s_FldProp_IdType )
, IdValue_( ifds::IdValue, &ifds::s_FldProp_IdValue )
, IdDate_( ifds::IdDate, &ifds::s_FldProp_IdDate )
, EntitySearchIdVer_( ifds::EntitySearchIdVer, &ifds::s_FldProp_EntitySearchIdVer )
, EntitySearchRid_( ifds::EntitySearchRid, &ifds::s_FldProp_EntitySearchRid )
, IdStatus_( ifds::IdStatus, &ifds::s_FldProp_IdStatus )
, CountryOfIssue_( ifds::CountryOfIssue, &ifds::s_FldProp_CountryOfIssue )
, IdExpireDate_( ifds::IdExpireDate, &ifds::s_FldProp_IdExpireDate )
, VerifyStat_( ifds::VerifyStat, &ifds::s_FldProp_VerifyStat )
{
    cFields_ = 11;
    memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0079_REQRepeat_Record::~dsi_DSTC0079_REQRepeat_Record()
{
}

BFDataImpl* dsi_DSTC0079_REQRepeat_Record::clone()
{
   dsi_DSTC0079_REQRepeat_Record* p = new dsi_DSTC0079_REQRepeat_Record;
   p->RunMode_ = RunMode_;
   p->EntityId_ = EntityId_;
   p->IdType_ = IdType_;
   p->IdValue_ = IdValue_;
   p->IdDate_ = IdDate_;
   p->EntitySearchIdVer_ = EntitySearchIdVer_;
   p->EntitySearchRid_ = EntitySearchRid_;
   p->IdStatus_ = IdStatus_;
   p->CountryOfIssue_ = CountryOfIssue_;
   p->IdExpireDate_ = IdExpireDate_;
   p->VerifyStat_ = VerifyStat_;
   return(p);
}

BFDataField* dsi_DSTC0079_REQRepeat_Record::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40000990: return ( &RunMode_ ); break; // RunMode
      case 40000033: return ( &EntityId_ ); break; // EntityId
      case 40000633: return ( &IdType_ ); break; // IdType
      case 40000635: return ( &IdValue_ ); break; // IdValue
      case 40000636: return ( &IdDate_ ); break; // IdDate
      case 40000907: return ( &EntitySearchIdVer_ ); break; // EntitySearchIdVer
      case 40000908: return ( &EntitySearchRid_ ); break; // EntitySearchRid
      case 40005630: return ( &IdStatus_ ); break; // IdStatus
      case 40006831: return ( &CountryOfIssue_ ); break; // CountryOfIssue
      case 40006945: return ( &IdExpireDate_ ); break; // IdExpireDate
      case 40006046: return ( &VerifyStat_ ); break; // VerifyStat
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0079_REQRepeat_Record::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0079_REQRepeat_Record* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0079_REQRepeat_Record::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 11 )
   {
      BFDataField* pField = aFlds_[iField];
      if( NULL == pField )
      {
         switch(iField)
         {
            case 0: aFlds_[0] = &RunMode_; break;
            case 1: aFlds_[1] = &EntityId_; break;
            case 2: aFlds_[2] = &IdType_; break;
            case 3: aFlds_[3] = &IdValue_; break;
            case 4: aFlds_[4] = &IdDate_; break;
            case 5: aFlds_[5] = &EntitySearchIdVer_; break;
            case 6: aFlds_[6] = &EntitySearchRid_; break;
            case 7: aFlds_[7] = &IdStatus_; break;
            case 8: aFlds_[8] = &CountryOfIssue_; break;
            case 9: aFlds_[9] = &IdExpireDate_; break;
            case 10: aFlds_[10] = &VerifyStat_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0079_REQRepeat_Record::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0079_REQRepeat_Record* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0079_REQRepeat_Record::getLargestDefinedField( void ) const
{
   return( 60 );
}

unsigned long dsi_DSTC0079_REQRepeat_Record::getDefinedByteLength( void ) const
{
    return( 425 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0079_REQRepeat_Record::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0079_REQRepeat_Record::fieldExists( id );
}

bool dsi_DSTC0079_REQRepeat_Record::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40000990: return( true );
      case 40000033: return( true );
      case 40000633: return( true );
      case 40000635: return( true );
      case 40000636: return( true );
      case 40000907: return( true );
      case 40000908: return( true );
      case 40005630: return( true );
      case 40006831: return( true );
      case 40006945: return( true );
      case 40006046: return ( true );
   }
   return false;
}

