// BFDataImpl implementation file for DataSet DSTC0272.VWRepeat_Record
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0272_vwrepeat_record.h"


// This function creates an instance of dsi_DSTC0272_VWRepeat_Record
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0272_VWRepeat_Record() { return new dsi_DSTC0272_VWRepeat_Record; }

dsi_DSTC0272_VWRepeat_Record::dsi_DSTC0272_VWRepeat_Record()
: BFDataImpl( 40004183 )
, ExtTransferType_( ifds::ExtTransferType, &ifds::s_FldProp_ExtTransferType )
, Description_( ifds::Description, &ifds::s_FldProp_Description )
, FirstLetter_( ifds::FirstLetter, &ifds::s_FldProp_FirstLetter )
, FirstLetterDays_( ifds::FirstLetterDays, &ifds::s_FldProp_FirstLetterDays )
, SecondLetter_( ifds::SecondLetter, &ifds::s_FldProp_SecondLetter )
, SecondLetterDays_( ifds::SecondLetterDays, &ifds::s_FldProp_SecondLetterDays )
, ThirdLetter_( ifds::ThirdLetter, &ifds::s_FldProp_ThirdLetter )
, ThirdLetterDays_( ifds::ThirdLetterDays, &ifds::s_FldProp_ThirdLetterDays )
, SubsequentLetter_( ifds::SubsequentLetter, &ifds::s_FldProp_SubsequentLetter )
, SubsequentLetterFreq_( ifds::SubsequentLetterFreq, &ifds::s_FldProp_SubsequentLetterFreq )
, ProcessDate_( ifds::ProcessDate, &ifds::s_FldProp_ProcessDate )
, Username_( ifds::Username, &ifds::s_FldProp_Username )
, ModDate_( ifds::ModDate, &ifds::s_FldProp_ModDate )
, ModUser_( ifds::ModUser, &ifds::s_FldProp_ModUser )
, Version_( ifds::Version, &ifds::s_FldProp_Version )
{
   cFields_ = 15;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0272_VWRepeat_Record::~dsi_DSTC0272_VWRepeat_Record()
{
}

BFDataImpl* dsi_DSTC0272_VWRepeat_Record::clone()
{
   dsi_DSTC0272_VWRepeat_Record* p = new dsi_DSTC0272_VWRepeat_Record;
   p->ExtTransferType_ = ExtTransferType_;
   p->Description_ = Description_;
   p->FirstLetter_ = FirstLetter_;
   p->FirstLetterDays_ = FirstLetterDays_;
   p->SecondLetter_ = SecondLetter_;
   p->SecondLetterDays_ = SecondLetterDays_;
   p->ThirdLetter_ = ThirdLetter_;
   p->ThirdLetterDays_ = ThirdLetterDays_;
   p->SubsequentLetter_ = SubsequentLetter_;
   p->SubsequentLetterFreq_ = SubsequentLetterFreq_;
   p->ProcessDate_ = ProcessDate_;
   p->Username_ = Username_;
   p->ModDate_ = ModDate_;
   p->ModUser_ = ModUser_;
   p->Version_ = Version_;
   return(p);
}

BFDataField* dsi_DSTC0272_VWRepeat_Record::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40004186: return ( &ExtTransferType_ ); break; // ExtTransferType
      case 40002905: return ( &Description_ ); break; // Description
      case 40004187: return ( &FirstLetter_ ); break; // FirstLetter
      case 40004188: return ( &FirstLetterDays_ ); break; // FirstLetterDays
      case 40004189: return ( &SecondLetter_ ); break; // SecondLetter
      case 40004190: return ( &SecondLetterDays_ ); break; // SecondLetterDays
      case 40004191: return ( &ThirdLetter_ ); break; // ThirdLetter
      case 40004192: return ( &ThirdLetterDays_ ); break; // ThirdLetterDays
      case 40004193: return ( &SubsequentLetter_ ); break; // SubsequentLetter
      case 40004194: return ( &SubsequentLetterFreq_ ); break; // SubsequentLetterFreq
      case 40000216: return ( &ProcessDate_ ); break; // ProcessDate
      case 40000117: return ( &Username_ ); break; // Username
      case 40000217: return ( &ModDate_ ); break; // ModDate
      case 40000218: return ( &ModUser_ ); break; // ModUser
      case 40003739: return ( &Version_ ); break; // Version
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0272_VWRepeat_Record::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0272_VWRepeat_Record* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0272_VWRepeat_Record::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 15 )
   {
      BFDataField* pField = aFlds_[iField];
      if( NULL == pField )
      {
         switch(iField)
         {
            case 0: aFlds_[0] = &ExtTransferType_; break;
            case 1: aFlds_[1] = &Description_; break;
            case 2: aFlds_[2] = &FirstLetter_; break;
            case 3: aFlds_[3] = &FirstLetterDays_; break;
            case 4: aFlds_[4] = &SecondLetter_; break;
            case 5: aFlds_[5] = &SecondLetterDays_; break;
            case 6: aFlds_[6] = &ThirdLetter_; break;
            case 7: aFlds_[7] = &ThirdLetterDays_; break;
            case 8: aFlds_[8] = &SubsequentLetter_; break;
            case 9: aFlds_[9] = &SubsequentLetterFreq_; break;
            case 10: aFlds_[10] = &ProcessDate_; break;
            case 11: aFlds_[11] = &Username_; break;
            case 12: aFlds_[12] = &ModDate_; break;
            case 13: aFlds_[13] = &ModUser_; break;
            case 14: aFlds_[14] = &Version_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0272_VWRepeat_Record::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0272_VWRepeat_Record* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0272_VWRepeat_Record::getLargestDefinedField( void ) const
{
   return( 60 );
}

unsigned long dsi_DSTC0272_VWRepeat_Record::getDefinedByteLength( void ) const
{
   return( 559 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0272_VWRepeat_Record::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0272_VWRepeat_Record::fieldExists( id );
}

bool dsi_DSTC0272_VWRepeat_Record::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40004186: return( true );
      case 40002905: return( true );
      case 40004187: return( true );
      case 40004188: return( true );
      case 40004189: return( true );
      case 40004190: return( true );
      case 40004191: return( true );
      case 40004192: return( true );
      case 40004193: return( true );
      case 40004194: return( true );
      case 40000216: return( true );
      case 40000117: return( true );
      case 40000217: return( true );
      case 40000218: return( true );
      case 40003739: return( true );
   }
   return false;
}

