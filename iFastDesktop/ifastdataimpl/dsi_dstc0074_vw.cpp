// BFDataImpl implementation file for DataSet DSTC0074.VW
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0074_vw.h"


// This function creates an instance of dsi_DSTC0074_VW
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0074_VW() { return new dsi_DSTC0074_VW; }

dsi_DSTC0074_VW::dsi_DSTC0074_VW()
: BFDataImpl( 40000997, 40001195 )
, UpdateStatus_( ifds::UpdateStatus, &ifds::s_FldProp_UpdateStatus )
, WarnCode1_( ifds::WarnCode1, &ifds::s_FldProp_WarnCode1 )
, WarnDesc1_( ifds::WarnDesc1, &ifds::s_FldProp_WarnDesc1 )
, WarnCode2_( ifds::WarnCode2, &ifds::s_FldProp_WarnCode2 )
, WarnDesc2_( ifds::WarnDesc2, &ifds::s_FldProp_WarnDesc2 )
, WarnCode3_( ifds::WarnCode3, &ifds::s_FldProp_WarnCode3 )
, WarnDesc3_( ifds::WarnDesc3, &ifds::s_FldProp_WarnDesc3 )
, WarnCode4_( ifds::WarnCode4, &ifds::s_FldProp_WarnCode4 )
, WarnDesc4_( ifds::WarnDesc4, &ifds::s_FldProp_WarnDesc4 )
, WarnCode5_( ifds::WarnCode5, &ifds::s_FldProp_WarnCode5 )
, WarnDesc5_( ifds::WarnDesc5, &ifds::s_FldProp_WarnDesc5 )
, RepeatCount_( ifds::RepeatCount, &ifds::s_FldProp_RepeatCount )
{
   cFields_ = 12;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0074_VW::~dsi_DSTC0074_VW()
{
}

BFDataImpl* dsi_DSTC0074_VW::clone()
{
   dsi_DSTC0074_VW* p = new dsi_DSTC0074_VW;
   p->UpdateStatus_ = UpdateStatus_;
   p->WarnCode1_ = WarnCode1_;
   p->WarnDesc1_ = WarnDesc1_;
   p->WarnCode2_ = WarnCode2_;
   p->WarnDesc2_ = WarnDesc2_;
   p->WarnCode3_ = WarnCode3_;
   p->WarnDesc3_ = WarnDesc3_;
   p->WarnCode4_ = WarnCode4_;
   p->WarnDesc4_ = WarnDesc4_;
   p->WarnCode5_ = WarnCode5_;
   p->WarnDesc5_ = WarnDesc5_;
   p->RepeatCount_ = RepeatCount_;
   return(p);
}

BFDataField* dsi_DSTC0074_VW::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40000989: return ( &UpdateStatus_ ); break; // UpdateStatus
      case 40005185: return ( &WarnCode1_ ); break; // WarnCode1
      case 40005190: return ( &WarnDesc1_ ); break; // WarnDesc1
      case 40005186: return ( &WarnCode2_ ); break; // WarnCode2
      case 40005191: return ( &WarnDesc2_ ); break; // WarnDesc2
      case 40005187: return ( &WarnCode3_ ); break; // WarnCode3
      case 40005192: return ( &WarnDesc3_ ); break; // WarnDesc3
      case 40005188: return ( &WarnCode4_ ); break; // WarnCode4
      case 40005193: return ( &WarnDesc4_ ); break; // WarnDesc4
      case 40005189: return ( &WarnCode5_ ); break; // WarnCode5
      case 40005194: return ( &WarnDesc5_ ); break; // WarnDesc5
      case 40000120: return ( &RepeatCount_ ); break; // RepeatCount
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0074_VW::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0074_VW* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0074_VW::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 12 )
   {
      BFDataField* pField = aFlds_[iField];
      if( NULL == pField )
      {
         switch(iField)
         {
            case 0: aFlds_[0] = &UpdateStatus_; break;
            case 1: aFlds_[1] = &WarnCode1_; break;
            case 2: aFlds_[2] = &WarnDesc1_; break;
            case 3: aFlds_[3] = &WarnCode2_; break;
            case 4: aFlds_[4] = &WarnDesc2_; break;
            case 5: aFlds_[5] = &WarnCode3_; break;
            case 6: aFlds_[6] = &WarnDesc3_; break;
            case 7: aFlds_[7] = &WarnCode4_; break;
            case 8: aFlds_[8] = &WarnDesc4_; break;
            case 9: aFlds_[9] = &WarnCode5_; break;
            case 10: aFlds_[10] = &WarnDesc5_; break;
            case 11: aFlds_[11] = &RepeatCount_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0074_VW::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0074_VW* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0074_VW::getLargestDefinedField( void ) const
{
   return( 60 );
}

unsigned long dsi_DSTC0074_VW::getDefinedByteLength( void ) const
{
   return( 351 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0074_VW::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0074_VW::fieldExists( id );
}

bool dsi_DSTC0074_VW::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40000989: return( true );
      case 40005185: return( true );
      case 40005190: return( true );
      case 40005186: return( true );
      case 40005191: return( true );
      case 40005187: return( true );
      case 40005192: return( true );
      case 40005188: return( true );
      case 40005193: return( true );
      case 40005189: return( true );
      case 40005194: return( true );
      case 40000120: return( true );
   }
   return false;
}

