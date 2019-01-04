// BFDataImpl implementation file for DataSet DSTC0240.VWRepeat_Record
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0240_vwrepeat_record.h"


// This function creates an instance of dsi_DSTC0240_VWRepeat_Record
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0240_VWRepeat_Record() { return new dsi_DSTC0240_VWRepeat_Record; }

dsi_DSTC0240_VWRepeat_Record::dsi_DSTC0240_VWRepeat_Record()
: BFDataImpl( 40003656 )
, IndexCode_( ifds::IndexCode, &ifds::s_FldProp_IndexCode )
, IndexName_( ifds::IndexName, &ifds::s_FldProp_IndexName )
, MktIndexRid_( ifds::MktIndexRid, &ifds::s_FldProp_MktIndexRid )
, MktIndexVer_( ifds::MktIndexVer, &ifds::s_FldProp_MktIndexVer )
, ProcessDate_( ifds::ProcessDate, &ifds::s_FldProp_ProcessDate )
, Username_( ifds::Username, &ifds::s_FldProp_Username )
, ModDate_( ifds::ModDate, &ifds::s_FldProp_ModDate )
, ModUser_( ifds::ModUser, &ifds::s_FldProp_ModUser )
, DaysBasis_( ifds::DaysBasis, &ifds::s_FldProp_DaysBasis )
, InputDataType_( ifds::InputDataType, &ifds::s_FldProp_InputDataType )
{
   cFields_ = 10;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0240_VWRepeat_Record::~dsi_DSTC0240_VWRepeat_Record()
{
}

BFDataImpl* dsi_DSTC0240_VWRepeat_Record::clone()
{
   dsi_DSTC0240_VWRepeat_Record* p = new dsi_DSTC0240_VWRepeat_Record;
   p->IndexCode_ = IndexCode_;
   p->IndexName_ = IndexName_;
   p->MktIndexRid_ = MktIndexRid_;
   p->MktIndexVer_ = MktIndexVer_;
   p->ProcessDate_ = ProcessDate_;
   p->Username_ = Username_;
   p->ModDate_ = ModDate_;
   p->ModUser_ = ModUser_;
   p->DaysBasis_ = DaysBasis_;
   p->InputDataType_ = InputDataType_;
   return(p);
}

BFDataField* dsi_DSTC0240_VWRepeat_Record::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40003658: return ( &IndexCode_ ); break; // IndexCode
      case 40003659: return ( &IndexName_ ); break; // IndexName
      case 40003660: return ( &MktIndexRid_ ); break; // MktIndexRid
      case 40003661: return ( &MktIndexVer_ ); break; // MktIndexVer
      case 40000216: return ( &ProcessDate_ ); break; // ProcessDate
      case 40000117: return ( &Username_ ); break; // Username
      case 40000217: return ( &ModDate_ ); break; // ModDate
      case 40000218: return ( &ModUser_ ); break; // ModUser
      case 40006660: return ( &DaysBasis_ ); break; // DaysBasis
      case 40006659: return ( &InputDataType_ ); break; // InputDataType
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0240_VWRepeat_Record::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0240_VWRepeat_Record* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0240_VWRepeat_Record::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 10 )
   {
      BFDataField* pField = aFlds_[iField];
      if( NULL == pField )
      {
         switch(iField)
         {
            case 0: aFlds_[0] = &IndexCode_; break;
            case 1: aFlds_[1] = &IndexName_; break;
            case 2: aFlds_[2] = &MktIndexRid_; break;
            case 3: aFlds_[3] = &MktIndexVer_; break;
            case 4: aFlds_[4] = &ProcessDate_; break;
            case 5: aFlds_[5] = &Username_; break;
            case 6: aFlds_[6] = &ModDate_; break;
            case 7: aFlds_[7] = &ModUser_; break;
            case 8: aFlds_[8] = &DaysBasis_; break;
            case 9: aFlds_[9] = &InputDataType_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0240_VWRepeat_Record::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0240_VWRepeat_Record* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0240_VWRepeat_Record::getLargestDefinedField( void ) const
{
   return( 60 );
}

unsigned long dsi_DSTC0240_VWRepeat_Record::getDefinedByteLength( void ) const
{
   return( 320 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0240_VWRepeat_Record::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0240_VWRepeat_Record::fieldExists( id );
}

bool dsi_DSTC0240_VWRepeat_Record::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40003658: return( true );
      case 40003659: return( true );
      case 40003660: return( true );
      case 40003661: return( true );
      case 40000216: return( true );
      case 40000117: return( true );
      case 40000217: return( true );
      case 40000218: return( true );
      case 40006660: return( true );
      case 40006659: return( true );
   }
   return false;
}

