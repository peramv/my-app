// BFDataImpl implementation file for DataSet DSTC0274.REQRepeat_Record
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0274_reqrepeat_record.h"


// This function creates an instance of dsi_DSTC0274_REQRepeat_Record
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0274_REQRepeat_Record() { return new dsi_DSTC0274_REQRepeat_Record; }

dsi_DSTC0274_REQRepeat_Record::dsi_DSTC0274_REQRepeat_Record()
: BFDataImpl( 40004293 )
, RunMode_( ifds::RunMode, &ifds::s_FldProp_RunMode )
, Version_( ifds::Version, &ifds::s_FldProp_Version )
, SettleLocationCode_( ifds::SettleLocationCode, &ifds::s_FldProp_SettleLocationCode )
, Default_( ifds::Default, &ifds::s_FldProp_Default )
, RecId_( ifds::RecId, &ifds::s_FldProp_RecId )
{
   cFields_ = 5;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0274_REQRepeat_Record::~dsi_DSTC0274_REQRepeat_Record()
{
}

BFDataImpl* dsi_DSTC0274_REQRepeat_Record::clone()
{
   dsi_DSTC0274_REQRepeat_Record* p = new dsi_DSTC0274_REQRepeat_Record;
   p->RunMode_ = RunMode_;
   p->Version_ = Version_;
   p->SettleLocationCode_ = SettleLocationCode_;
   p->Default_ = Default_;
   p->RecId_ = RecId_;
   return(p);
}

BFDataField* dsi_DSTC0274_REQRepeat_Record::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40000990: return ( &RunMode_ ); break; // RunMode
      case 40003739: return ( &Version_ ); break; // Version
      case 40004261: return ( &SettleLocationCode_ ); break; // SettleLocationCode
      case 40001891: return ( &Default_ ); break; // Default
      case 40003737: return ( &RecId_ ); break; // RecId
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0274_REQRepeat_Record::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0274_REQRepeat_Record* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0274_REQRepeat_Record::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 5 )
   {
      BFDataField* pField = aFlds_[iField];
      if( NULL == pField )
      {
         switch(iField)
         {
            case 0: aFlds_[0] = &RunMode_; break;
            case 1: aFlds_[1] = &Version_; break;
            case 2: aFlds_[2] = &SettleLocationCode_; break;
            case 3: aFlds_[3] = &Default_; break;
            case 4: aFlds_[4] = &RecId_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0274_REQRepeat_Record::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0274_REQRepeat_Record* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0274_REQRepeat_Record::getLargestDefinedField( void ) const
{
   return( 60 );
}

unsigned long dsi_DSTC0274_REQRepeat_Record::getDefinedByteLength( void ) const
{
   return( 94 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0274_REQRepeat_Record::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0274_REQRepeat_Record::fieldExists( id );
}

bool dsi_DSTC0274_REQRepeat_Record::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40000990: return( true );
      case 40003739: return( true );
      case 40004261: return( true );
      case 40001891: return( true );
      case 40003737: return( true );
   }
   return false;
}

