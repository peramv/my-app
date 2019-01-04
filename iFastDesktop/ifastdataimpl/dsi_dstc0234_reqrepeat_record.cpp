// BFDataImpl implementation file for DataSet DSTC0234.REQRepeat_Record
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0234_reqrepeat_record.h"


// This function creates an instance of dsi_DSTC0234_REQRepeat_Record
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0234_REQRepeat_Record() { return new dsi_DSTC0234_REQRepeat_Record; }

dsi_DSTC0234_REQRepeat_Record::dsi_DSTC0234_REQRepeat_Record()
: BFDataImpl( 40003618 )
, RunMode_( ifds::RunMode, &ifds::s_FldProp_RunMode )
, ShrFamilyRid_( ifds::ShrFamilyRid, &ifds::s_FldProp_ShrFamilyRid )
, FamilyCode_( ifds::FamilyCode, &ifds::s_FldProp_FamilyCode )
, FamilyType_( ifds::FamilyType, &ifds::s_FldProp_FamilyType )
, Role_( ifds::Role, &ifds::s_FldProp_Role )
, FamilyName_( ifds::FamilyName, &ifds::s_FldProp_FamilyName )
{
   cFields_ = 6;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0234_REQRepeat_Record::~dsi_DSTC0234_REQRepeat_Record()
{
}

BFDataImpl* dsi_DSTC0234_REQRepeat_Record::clone()
{
   dsi_DSTC0234_REQRepeat_Record* p = new dsi_DSTC0234_REQRepeat_Record;
   p->RunMode_ = RunMode_;
   p->ShrFamilyRid_ = ShrFamilyRid_;
   p->FamilyCode_ = FamilyCode_;
   p->FamilyType_ = FamilyType_;
   p->Role_ = Role_;
   p->FamilyName_ = FamilyName_;
   return(p);
}

BFDataField* dsi_DSTC0234_REQRepeat_Record::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40000990: return ( &RunMode_ ); break; // RunMode
      case 40003614: return ( &ShrFamilyRid_ ); break; // ShrFamilyRid
      case 40000802: return ( &FamilyCode_ ); break; // FamilyCode
      case 40003627: return ( &FamilyType_ ); break; // FamilyType
      case 40003615: return ( &Role_ ); break; // Role
      case 40000803: return ( &FamilyName_ ); break; // FamilyName
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0234_REQRepeat_Record::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0234_REQRepeat_Record* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0234_REQRepeat_Record::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 6 )
   {
      BFDataField* pField = aFlds_[iField];
      if( NULL == pField )
      {
         switch(iField)
         {
            case 0: aFlds_[0] = &RunMode_; break;
            case 1: aFlds_[1] = &ShrFamilyRid_; break;
            case 2: aFlds_[2] = &FamilyCode_; break;
            case 3: aFlds_[3] = &FamilyType_; break;
            case 4: aFlds_[4] = &Role_; break;
            case 5: aFlds_[5] = &FamilyName_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0234_REQRepeat_Record::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0234_REQRepeat_Record* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0234_REQRepeat_Record::getLargestDefinedField( void ) const
{
   return( 60 );
}

unsigned long dsi_DSTC0234_REQRepeat_Record::getDefinedByteLength( void ) const
{
   return( 300 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0234_REQRepeat_Record::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0234_REQRepeat_Record::fieldExists( id );
}

bool dsi_DSTC0234_REQRepeat_Record::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40000990: return( true );
      case 40003614: return( true );
      case 40000802: return( true );
      case 40003627: return( true );
      case 40003615: return( true );
      case 40000803: return( true );
   }
   return false;
}

