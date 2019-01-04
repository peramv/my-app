// BFDataImpl implementation file for DataSet DSTC0261.REQRepeat_Record
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0261_reqrepeat_record.h"


// This function creates an instance of dsi_DSTC0261_REQRepeat_Record
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0261_REQRepeat_Record() { return new dsi_DSTC0261_REQRepeat_Record; }

dsi_DSTC0261_REQRepeat_Record::dsi_DSTC0261_REQRepeat_Record()
: BFDataImpl( 40004103 )
, RunMode_( ifds::RunMode, &ifds::s_FldProp_RunMode )
, RuleType_( ifds::RuleType, &ifds::s_FldProp_RuleType )
, OverrideDecimal_( ifds::OverrideDecimal, &ifds::s_FldProp_OverrideDecimal )
, OverrideLogical_( ifds::OverrideLogical, &ifds::s_FldProp_OverrideLogical )
, OverrideFundLevel_( ifds::OverrideFundLevel, &ifds::s_FldProp_OverrideFundLevel )
, AMSTaxJurisCode_( ifds::AMSTaxJurisCode, &ifds::s_FldProp_AMSTaxJurisCode )
, AMSResProvCode_( ifds::AMSResProvCode, &ifds::s_FldProp_AMSResProvCode )
, AMSTaxType_( ifds::AMSTaxType, &ifds::s_FldProp_AMSTaxType )
, AMSAcctType_( ifds::AMSAcctType, &ifds::s_FldProp_AMSAcctType )
, AMSAcctDesignation_( ifds::AMSAcctDesignation, &ifds::s_FldProp_AMSAcctDesignation )
, OnLineEWI_( ifds::OnLineEWI, &ifds::s_FldProp_OnLineEWI )
, CycleEWI_( ifds::CycleEWI, &ifds::s_FldProp_CycleEWI )
, ESGEWI_( ifds::ESGEWI, &ifds::s_FldProp_ESGEWI )
, AMSRuleId_( ifds::AMSRuleId, &ifds::s_FldProp_AMSRuleId )
{
   cFields_ = 14;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0261_REQRepeat_Record::~dsi_DSTC0261_REQRepeat_Record()
{
}

BFDataImpl* dsi_DSTC0261_REQRepeat_Record::clone()
{
   dsi_DSTC0261_REQRepeat_Record* p = new dsi_DSTC0261_REQRepeat_Record;
   p->RunMode_ = RunMode_;
   p->RuleType_ = RuleType_;
   p->OverrideDecimal_ = OverrideDecimal_;
   p->OverrideLogical_ = OverrideLogical_;
   p->OverrideFundLevel_ = OverrideFundLevel_;
   p->AMSTaxJurisCode_ = AMSTaxJurisCode_;
   p->AMSResProvCode_ = AMSResProvCode_;
   p->AMSTaxType_ = AMSTaxType_;
   p->AMSAcctType_ = AMSAcctType_;
   p->AMSAcctDesignation_ = AMSAcctDesignation_;
   p->OnLineEWI_ = OnLineEWI_;
   p->CycleEWI_ = CycleEWI_;
   p->ESGEWI_ = ESGEWI_;
   p->AMSRuleId_ = AMSRuleId_;
   return(p);
}

BFDataField* dsi_DSTC0261_REQRepeat_Record::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40000990: return ( &RunMode_ ); break; // RunMode
      case 40003775: return ( &RuleType_ ); break; // RuleType
      case 40004072: return ( &OverrideDecimal_ ); break; // OverrideDecimal
      case 40004074: return ( &OverrideLogical_ ); break; // OverrideLogical
      case 40004075: return ( &OverrideFundLevel_ ); break; // OverrideFundLevel
      case 40004128: return ( &AMSTaxJurisCode_ ); break; // AMSTaxJurisCode
      case 40004129: return ( &AMSResProvCode_ ); break; // AMSResProvCode
      case 40004125: return ( &AMSTaxType_ ); break; // AMSTaxType
      case 40004126: return ( &AMSAcctType_ ); break; // AMSAcctType
      case 40004127: return ( &AMSAcctDesignation_ ); break; // AMSAcctDesignation
      case 40004076: return ( &OnLineEWI_ ); break; // OnLineEWI
      case 40004077: return ( &CycleEWI_ ); break; // CycleEWI
      case 40004079: return ( &ESGEWI_ ); break; // ESGEWI
      case 40004080: return ( &AMSRuleId_ ); break; // AMSRuleId
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0261_REQRepeat_Record::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0261_REQRepeat_Record* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0261_REQRepeat_Record::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 14 )
   {
      BFDataField* pField = aFlds_[iField];
      if( NULL == pField )
      {
         switch(iField)
         {
            case 0: aFlds_[0] = &RunMode_; break;
            case 1: aFlds_[1] = &RuleType_; break;
            case 2: aFlds_[2] = &OverrideDecimal_; break;
            case 3: aFlds_[3] = &OverrideLogical_; break;
            case 4: aFlds_[4] = &OverrideFundLevel_; break;
            case 5: aFlds_[5] = &AMSTaxJurisCode_; break;
            case 6: aFlds_[6] = &AMSResProvCode_; break;
            case 7: aFlds_[7] = &AMSTaxType_; break;
            case 8: aFlds_[8] = &AMSAcctType_; break;
            case 9: aFlds_[9] = &AMSAcctDesignation_; break;
            case 10: aFlds_[10] = &OnLineEWI_; break;
            case 11: aFlds_[11] = &CycleEWI_; break;
            case 12: aFlds_[12] = &ESGEWI_; break;
            case 13: aFlds_[13] = &AMSRuleId_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0261_REQRepeat_Record::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0261_REQRepeat_Record* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0261_REQRepeat_Record::getLargestDefinedField( void ) const
{
   return( 60 );
}

unsigned long dsi_DSTC0261_REQRepeat_Record::getDefinedByteLength( void ) const
{
   return( 462 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0261_REQRepeat_Record::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0261_REQRepeat_Record::fieldExists( id );
}

bool dsi_DSTC0261_REQRepeat_Record::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40000990: return( true );
      case 40003775: return( true );
      case 40004072: return( true );
      case 40004074: return( true );
      case 40004075: return( true );
      case 40004128: return( true );
      case 40004129: return( true );
      case 40004125: return( true );
      case 40004126: return( true );
      case 40004127: return( true );
      case 40004076: return( true );
      case 40004077: return( true );
      case 40004079: return( true );
      case 40004080: return( true );
   }
   return false;
}

