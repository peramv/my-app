// BFDataImpl implementation file for DataSet DSTC0161.REQRepeat_Record
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0161_reqrepeat_record.h"


// This function creates an instance of dsi_DSTC0161_REQRepeat_Record
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0161_REQRepeat_Record() { return new dsi_DSTC0161_REQRepeat_Record; }

dsi_DSTC0161_REQRepeat_Record::dsi_DSTC0161_REQRepeat_Record()
: BFDataImpl( 40002616 )
, RunMode_( ifds::RunMode, &ifds::s_FldProp_RunMode )
, CotAcctRid_( ifds::CotAcctRid, &ifds::s_FldProp_CotAcctRid )
, PrevEffectiveDate_( ifds::PrevEffectiveDate, &ifds::s_FldProp_PrevEffectiveDate )
, EffectiveDate_( ifds::EffectiveDate, &ifds::s_FldProp_EffectiveDate )
, StopDate_( ifds::StopDate, &ifds::s_FldProp_StopDate )
, ContractType_( ifds::ContractType, &ifds::s_FldProp_ContractType )
, ContractTypeId_( ifds::ContractTypeId, &ifds::s_FldProp_ContractTypeId )
, PolicyNum_( ifds::PolicyNum, &ifds::s_FldProp_PolicyNum )
, ContractTerm_( ifds::ContractTerm, &ifds::s_FldProp_ContractTerm )
, AnnivMonth_( ifds::AnnivMonth, &ifds::s_FldProp_AnnivMonth )
, AnnivDay_( ifds::AnnivDay, &ifds::s_FldProp_AnnivDay )
, ProvinceCanada_( ifds::ProvinceCanada, &ifds::s_FldProp_ProvinceCanada )
, AgeBasedOn_( ifds::AgeBasedOn, &ifds::s_FldProp_AgeBasedOn )
, Status_( ifds::Status, &ifds::s_FldProp_Status )
, BailMaturityDate_( ifds::BailMaturityDate, &ifds::s_FldProp_BailMaturityDate )
, ContractMaturityDate_( ifds::ContractMaturityDate, &ifds::s_FldProp_ContractMaturityDate )
, LegalMaturityDate_( ifds::LegalMaturityDate, &ifds::s_FldProp_LegalMaturityDate )
, CDStartDate_( ifds::CDStartDate, &ifds::s_FldProp_CDStartDate )
, SuspectGuarType_( ifds::SuspectGuarType, &ifds::s_FldProp_SuspectGuarType )
, ContractVer_( ifds::ContractVer, &ifds::s_FldProp_ContractVer )
, ContractMatBasedOn_( ifds::ContractMatBasedOn, &ifds::s_FldProp_ContractMatBasedOn )
{
   cFields_ = 21;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0161_REQRepeat_Record::~dsi_DSTC0161_REQRepeat_Record()
{
}

BFDataImpl* dsi_DSTC0161_REQRepeat_Record::clone()
{
   dsi_DSTC0161_REQRepeat_Record* p = new dsi_DSTC0161_REQRepeat_Record;
   p->RunMode_ = RunMode_;
   p->CotAcctRid_ = CotAcctRid_;
   p->PrevEffectiveDate_ = PrevEffectiveDate_;
   p->EffectiveDate_ = EffectiveDate_;
   p->StopDate_ = StopDate_;
   p->ContractType_ = ContractType_;
   p->ContractTypeId_ = ContractTypeId_;
   p->PolicyNum_ = PolicyNum_;
   p->ContractTerm_ = ContractTerm_;
   p->AnnivMonth_ = AnnivMonth_;
   p->AnnivDay_ = AnnivDay_;
   p->ProvinceCanada_ = ProvinceCanada_;
   p->AgeBasedOn_ = AgeBasedOn_;
   p->Status_ = Status_;
   p->BailMaturityDate_ = BailMaturityDate_;
   p->ContractMaturityDate_ = ContractMaturityDate_;
   p->LegalMaturityDate_ = LegalMaturityDate_;
   p->CDStartDate_ = CDStartDate_;
   p->SuspectGuarType_ = SuspectGuarType_;
   p->ContractVer_ = ContractVer_;
   p->ContractMatBasedOn_ = ContractMatBasedOn_;
   return(p);
}

BFDataField* dsi_DSTC0161_REQRepeat_Record::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40000990: return ( &RunMode_ ); break; // RunMode
      case 40001402: return ( &CotAcctRid_ ); break; // CotAcctRid
      case 40001690: return ( &PrevEffectiveDate_ ); break; // PrevEffectiveDate
      case 40000327: return ( &EffectiveDate_ ); break; // EffectiveDate
      case 40000279: return ( &StopDate_ ); break; // StopDate
      case 40001385: return ( &ContractType_ ); break; // ContractType
      case 40001386: return ( &ContractTypeId_ ); break; // ContractTypeId
      case 40001387: return ( &PolicyNum_ ); break; // PolicyNum
      case 40001388: return ( &ContractTerm_ ); break; // ContractTerm
      case 40001390: return ( &AnnivMonth_ ); break; // AnnivMonth
      case 40001391: return ( &AnnivDay_ ); break; // AnnivDay
      case 40001731: return ( &ProvinceCanada_ ); break; // ProvinceCanada
      case 40001395: return ( &AgeBasedOn_ ); break; // AgeBasedOn
      case 40001399: return ( &Status_ ); break; // Status
      case 40001400: return ( &BailMaturityDate_ ); break; // BailMaturityDate
      case 40005101: return ( &ContractMaturityDate_ ); break; // ContractMaturityDate
      case 40001397: return ( &LegalMaturityDate_ ); break; // LegalMaturityDate
      case 40005108: return ( &CDStartDate_ ); break; // CDStartDate
      case 40005195: return ( &SuspectGuarType_ ); break; // SuspectGuarType
      case 40006627: return ( &ContractVer_ ); break; // ContractVer
      case 40006628: return ( &ContractMatBasedOn_ ); break; // ContractMatBasedOn
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0161_REQRepeat_Record::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0161_REQRepeat_Record* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0161_REQRepeat_Record::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 21 )
   {
      BFDataField* pField = aFlds_[iField];
      if( NULL == pField )
      {
         switch(iField)
         {
            case 0: aFlds_[0] = &RunMode_; break;
            case 1: aFlds_[1] = &CotAcctRid_; break;
            case 2: aFlds_[2] = &PrevEffectiveDate_; break;
            case 3: aFlds_[3] = &EffectiveDate_; break;
            case 4: aFlds_[4] = &StopDate_; break;
            case 5: aFlds_[5] = &ContractType_; break;
            case 6: aFlds_[6] = &ContractTypeId_; break;
            case 7: aFlds_[7] = &PolicyNum_; break;
            case 8: aFlds_[8] = &ContractTerm_; break;
            case 9: aFlds_[9] = &AnnivMonth_; break;
            case 10: aFlds_[10] = &AnnivDay_; break;
            case 11: aFlds_[11] = &ProvinceCanada_; break;
            case 12: aFlds_[12] = &AgeBasedOn_; break;
            case 13: aFlds_[13] = &Status_; break;
            case 14: aFlds_[14] = &BailMaturityDate_; break;
            case 15: aFlds_[15] = &ContractMaturityDate_; break;
            case 16: aFlds_[16] = &LegalMaturityDate_; break;
            case 17: aFlds_[17] = &CDStartDate_; break;
            case 18: aFlds_[18] = &SuspectGuarType_; break;
            case 19: aFlds_[19] = &ContractVer_; break;
            case 20: aFlds_[20] = &ContractMatBasedOn_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0161_REQRepeat_Record::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0161_REQRepeat_Record* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0161_REQRepeat_Record::getLargestDefinedField( void ) const
{
   return( 200 );
}

unsigned long dsi_DSTC0161_REQRepeat_Record::getDefinedByteLength( void ) const
{
   return( 749 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0161_REQRepeat_Record::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0161_REQRepeat_Record::fieldExists( id );
}

bool dsi_DSTC0161_REQRepeat_Record::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40000990: return( true );
      case 40001402: return( true );
      case 40001690: return( true );
      case 40000327: return( true );
      case 40000279: return( true );
      case 40001385: return( true );
      case 40001386: return( true );
      case 40001387: return( true );
      case 40001388: return( true );
      case 40001390: return( true );
      case 40001391: return( true );
      case 40001731: return( true );
      case 40001395: return( true );
      case 40001399: return( true );
      case 40001400: return( true );
      case 40005101: return( true );
      case 40001397: return( true );
      case 40005108: return( true );
      case 40005195: return( true );
      case 40006627: return( true );
      case 40006628: return( true );
   }
   return false;
}

