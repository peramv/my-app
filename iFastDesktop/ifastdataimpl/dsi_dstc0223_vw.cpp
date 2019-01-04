// BFDataImpl implementation file for DataSet DSTC0223.VW
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0223_vw.h"


// This function creates an instance of dsi_DSTC0223_VW
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0223_VW() { return new dsi_DSTC0223_VW; }

dsi_DSTC0223_VW::dsi_DSTC0223_VW()
: BFDataImpl( 40003472 )
, AcctExists_( ifds::AcctExists, &ifds::s_FldProp_AcctExists )
, Name_( ifds::Name, &ifds::s_FldProp_Name )
, AMSAccount_( ifds::AMSAccount, &ifds::s_FldProp_AMSAccount )
, AccountDeleted_( ifds::AccountDeleted, &ifds::s_FldProp_AccountDeleted )
{
   cFields_ = 4;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0223_VW::~dsi_DSTC0223_VW()
{
}

BFDataImpl* dsi_DSTC0223_VW::clone()
{
   dsi_DSTC0223_VW* p = new dsi_DSTC0223_VW;
   p->AcctExists_ = AcctExists_;
   p->Name_ = Name_;
   p->AMSAccount_ = AMSAccount_;
   p->AccountDeleted_ = AccountDeleted_;
   return(p);
}

BFDataField* dsi_DSTC0223_VW::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40003475: return ( &AcctExists_ ); break; // AcctExists
      case 40001090: return ( &Name_ ); break; // Name
      case 40003722: return ( &AMSAccount_ ); break; // AMSAccount
      case 40003721: return ( &AccountDeleted_ ); break; // AccountDeleted
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0223_VW::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0223_VW* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0223_VW::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 4 )
   {
      BFDataField* pField = aFlds_[iField];
      if( NULL == pField )
      {
         switch(iField)
         {
            case 0: aFlds_[0] = &AcctExists_; break;
            case 1: aFlds_[1] = &Name_; break;
            case 2: aFlds_[2] = &AMSAccount_; break;
            case 3: aFlds_[3] = &AccountDeleted_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0223_VW::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0223_VW* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0223_VW::getLargestDefinedField( void ) const
{
   return( 60 );
}

unsigned long dsi_DSTC0223_VW::getDefinedByteLength( void ) const
{
   return( 63 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0223_VW::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0223_VW::fieldExists( id );
}

bool dsi_DSTC0223_VW::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40003475: return( true );
      case 40001090: return( true );
      case 40003722: return( true );
      case 40003721: return( true );
   }
   return false;
}

