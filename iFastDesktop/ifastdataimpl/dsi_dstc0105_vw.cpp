// BFDataImpl implementation file for DataSet DSTC0105.VW
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0105_vw.h"


// This function creates an instance of dsi_DSTC0105_VW
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0105_VW() { return new dsi_DSTC0105_VW; }

dsi_DSTC0105_VW::dsi_DSTC0105_VW()
: BFDataImpl( 40001404, 40001403 )
, MoreAvailable_( ifds::MoreAvailable, &ifds::s_FldProp_MoreAvailable )
, NextKey_( ifds::NextKey, &ifds::s_FldProp_NextKey )
, AcctGroup_( ifds::AcctGroup, &ifds::s_FldProp_AcctGroup )
, AcctType_( ifds::AcctType, &ifds::s_FldProp_AcctType )
, FirstEffective_( ifds::FirstEffective, &ifds::s_FldProp_FirstEffective )
, AcctStatus_( ifds::AcctStatus, &ifds::s_FldProp_AcctStatus )
, TaxType_( ifds::TaxType, &ifds::s_FldProp_TaxType )
, RepeatCount_( ifds::RepeatCount, &ifds::s_FldProp_RepeatCount )
{
   cFields_ = 8;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0105_VW::~dsi_DSTC0105_VW()
{
}

BFDataImpl* dsi_DSTC0105_VW::clone()
{
   dsi_DSTC0105_VW* p = new dsi_DSTC0105_VW;
   p->MoreAvailable_ = MoreAvailable_;
   p->NextKey_ = NextKey_;
   p->AcctGroup_ = AcctGroup_;
   p->AcctType_ = AcctType_;
   p->FirstEffective_ = FirstEffective_;
   p->AcctStatus_ = AcctStatus_;
   p->TaxType_ = TaxType_;
   p->RepeatCount_ = RepeatCount_;
   return(p);
}

BFDataField* dsi_DSTC0105_VW::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40000126: return ( &MoreAvailable_ ); break; // MoreAvailable
      case 40000029: return ( &NextKey_ ); break; // NextKey
      case 40000208: return ( &AcctGroup_ ); break; // AcctGroup
      case 40000174: return ( &AcctType_ ); break; // AcctType
      case 40001371: return ( &FirstEffective_ ); break; // FirstEffective
      case 40000188: return ( &AcctStatus_ ); break; // AcctStatus
      case 40000134: return ( &TaxType_ ); break; // TaxType
      case 40000120: return ( &RepeatCount_ ); break; // RepeatCount
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0105_VW::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0105_VW* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0105_VW::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 8 )
   {
      BFDataField* pField = aFlds_[iField];
      if( NULL == pField )
      {
         switch(iField)
         {
            case 0: aFlds_[0] = &MoreAvailable_; break;
            case 1: aFlds_[1] = &NextKey_; break;
            case 2: aFlds_[2] = &AcctGroup_; break;
            case 3: aFlds_[3] = &AcctType_; break;
            case 4: aFlds_[4] = &FirstEffective_; break;
            case 5: aFlds_[5] = &AcctStatus_; break;
            case 6: aFlds_[6] = &TaxType_; break;
            case 7: aFlds_[7] = &RepeatCount_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0105_VW::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0105_VW* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0105_VW::getLargestDefinedField( void ) const
{
   return( 100 );
}

unsigned long dsi_DSTC0105_VW::getDefinedByteLength( void ) const
{
   return( 366 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0105_VW::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0105_VW::fieldExists( id );
}

bool dsi_DSTC0105_VW::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40000126: return( true );
      case 40000029: return( true );
      case 40000208: return( true );
      case 40000174: return( true );
      case 40001371: return( true );
      case 40000188: return( true );
      case 40000134: return( true );
      case 40000120: return( true );
   }
   return false;
}

