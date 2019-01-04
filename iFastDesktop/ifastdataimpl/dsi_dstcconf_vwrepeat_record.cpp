// BFDataImpl implementation file for DataSet DSTCCONF.VWRepeat_Record
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstcconf_vwrepeat_record.h"


// This function creates an instance of dsi_DSTCCONF_VWRepeat_Record
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTCCONF_VWRepeat_Record() { return new dsi_DSTCCONF_VWRepeat_Record; }

dsi_DSTCCONF_VWRepeat_Record::dsi_DSTCCONF_VWRepeat_Record()
: BFDataImpl( 40001214 )
, ConfirmID_( ifds::ConfirmID, &ifds::s_FldProp_ConfirmID )
, ScreenDesc_( ifds::ScreenDesc, &ifds::s_FldProp_ScreenDesc )
, ShrNum_( ifds::ShrNum, &ifds::s_FldProp_ShrNum )
, AccountNum_( ifds::AccountNum, &ifds::s_FldProp_AccountNum )
, Name_( ifds::Name, &ifds::s_FldProp_Name )
, ConfirmRemark_( ifds::ConfirmRemark, &ifds::s_FldProp_ConfirmRemark )
, ConfirmAWD_( ifds::ConfirmAWD, &ifds::s_FldProp_ConfirmAWD )
, Remark1_( ifds::Remark1, &ifds::s_FldProp_Remark1 )
, Remark2_( ifds::Remark2, &ifds::s_FldProp_Remark2 )
, Remark3_( ifds::Remark3, &ifds::s_FldProp_Remark3 )
, Remark4_( ifds::Remark4, &ifds::s_FldProp_Remark4 )
, Remark5_( ifds::Remark5, &ifds::s_FldProp_Remark5 )
, Remark6_( ifds::Remark6, &ifds::s_FldProp_Remark6 )
, Remark7_( ifds::Remark7, &ifds::s_FldProp_Remark7 )
, Remark8_( ifds::Remark8, &ifds::s_FldProp_Remark8 )
, Remark9_( ifds::Remark9, &ifds::s_FldProp_Remark9 )
, Remark10_( ifds::Remark10, &ifds::s_FldProp_Remark10 )
{
   cFields_ = 17;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTCCONF_VWRepeat_Record::~dsi_DSTCCONF_VWRepeat_Record()
{
}

BFDataImpl* dsi_DSTCCONF_VWRepeat_Record::clone()
{
   dsi_DSTCCONF_VWRepeat_Record* p = new dsi_DSTCCONF_VWRepeat_Record;
   p->ConfirmID_ = ConfirmID_;
   p->ScreenDesc_ = ScreenDesc_;
   p->ShrNum_ = ShrNum_;
   p->AccountNum_ = AccountNum_;
   p->Name_ = Name_;
   p->ConfirmRemark_ = ConfirmRemark_;
   p->ConfirmAWD_ = ConfirmAWD_;
   p->Remark1_ = Remark1_;
   p->Remark2_ = Remark2_;
   p->Remark3_ = Remark3_;
   p->Remark4_ = Remark4_;
   p->Remark5_ = Remark5_;
   p->Remark6_ = Remark6_;
   p->Remark7_ = Remark7_;
   p->Remark8_ = Remark8_;
   p->Remark9_ = Remark9_;
   p->Remark10_ = Remark10_;
   return(p);
}

BFDataField* dsi_DSTCCONF_VWRepeat_Record::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40001207: return ( &ConfirmID_ ); break; // ConfirmID
      case 40001208: return ( &ScreenDesc_ ); break; // ScreenDesc
      case 40000114: return ( &ShrNum_ ); break; // ShrNum
      case 40000040: return ( &AccountNum_ ); break; // AccountNum
      case 40001090: return ( &Name_ ); break; // Name
      case 40001209: return ( &ConfirmRemark_ ); break; // ConfirmRemark
      case 40001210: return ( &ConfirmAWD_ ); break; // ConfirmAWD
      case 40000078: return ( &Remark1_ ); break; // Remark1
      case 40000079: return ( &Remark2_ ); break; // Remark2
      case 40000080: return ( &Remark3_ ); break; // Remark3
      case 40000081: return ( &Remark4_ ); break; // Remark4
      case 40000082: return ( &Remark5_ ); break; // Remark5
      case 40000083: return ( &Remark6_ ); break; // Remark6
      case 40000084: return ( &Remark7_ ); break; // Remark7
      case 40000085: return ( &Remark8_ ); break; // Remark8
      case 40000086: return ( &Remark9_ ); break; // Remark9
      case 40000087: return ( &Remark10_ ); break; // Remark10
   }
   return( NULL );
}

const BFDataField* dsi_DSTCCONF_VWRepeat_Record::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTCCONF_VWRepeat_Record* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTCCONF_VWRepeat_Record::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 17 )
   {
      BFDataField* pField = aFlds_[iField];
      if( NULL == pField )
      {
         switch(iField)
         {
            case 0: aFlds_[0] = &ConfirmID_; break;
            case 1: aFlds_[1] = &ScreenDesc_; break;
            case 2: aFlds_[2] = &ShrNum_; break;
            case 3: aFlds_[3] = &AccountNum_; break;
            case 4: aFlds_[4] = &Name_; break;
            case 5: aFlds_[5] = &ConfirmRemark_; break;
            case 6: aFlds_[6] = &ConfirmAWD_; break;
            case 7: aFlds_[7] = &Remark1_; break;
            case 8: aFlds_[8] = &Remark2_; break;
            case 9: aFlds_[9] = &Remark3_; break;
            case 10: aFlds_[10] = &Remark4_; break;
            case 11: aFlds_[11] = &Remark5_; break;
            case 12: aFlds_[12] = &Remark6_; break;
            case 13: aFlds_[13] = &Remark7_; break;
            case 14: aFlds_[14] = &Remark8_; break;
            case 15: aFlds_[15] = &Remark9_; break;
            case 16: aFlds_[16] = &Remark10_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTCCONF_VWRepeat_Record::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTCCONF_VWRepeat_Record* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTCCONF_VWRepeat_Record::getLargestDefinedField( void ) const
{
   return( 100 );
}

unsigned long dsi_DSTCCONF_VWRepeat_Record::getDefinedByteLength( void ) const
{
   return( 1176 * sizeof( I_CHAR ) );
}

bool dsi_DSTCCONF_VWRepeat_Record::exists( const BFFieldId& id ) const
{
   return dsi_DSTCCONF_VWRepeat_Record::fieldExists( id );
}

bool dsi_DSTCCONF_VWRepeat_Record::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40001207: return( true );
      case 40001208: return( true );
      case 40000114: return( true );
      case 40000040: return( true );
      case 40001090: return( true );
      case 40001209: return( true );
      case 40001210: return( true );
      case 40000078: return( true );
      case 40000079: return( true );
      case 40000080: return( true );
      case 40000081: return( true );
      case 40000082: return( true );
      case 40000083: return( true );
      case 40000084: return( true );
      case 40000085: return( true );
      case 40000086: return( true );
      case 40000087: return( true );
   }
   return false;
}

