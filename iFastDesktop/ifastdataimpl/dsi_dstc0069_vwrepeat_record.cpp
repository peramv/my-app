// BFDataImpl implementation file for DataSet DSTC0069.VWRepeat_Record
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0069_vwrepeat_record.h"


// This function creates an instance of dsi_DSTC0069_VWRepeat_Record
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0069_VWRepeat_Record() { return new dsi_DSTC0069_VWRepeat_Record; }

dsi_DSTC0069_VWRepeat_Record::dsi_DSTC0069_VWRepeat_Record()
: BFDataImpl( 40000794 )
, ShrNum_( ifds::ShrNum, &ifds::s_FldProp_ShrNum )
, Name1_( ifds::Name1, &ifds::s_FldProp_Name1 )
, Name2_( ifds::Name2, &ifds::s_FldProp_Name2 )
, TaxJurisCode_( ifds::TaxJurisCode, &ifds::s_FldProp_TaxJurisCode )
, TaxJurisName_( ifds::TaxJurisName, &ifds::s_FldProp_TaxJurisName )
, ResProvCode_( ifds::ResProvCode, &ifds::s_FldProp_ResProvCode )
, ResProvName_( ifds::ResProvName, &ifds::s_FldProp_ResProvName )
, GroupCode_( ifds::GroupCode, &ifds::s_FldProp_GroupCode )
, GroupName1_( ifds::GroupName1, &ifds::s_FldProp_GroupName1 )
, FamilyCode_( ifds::FamilyCode, &ifds::s_FldProp_FamilyCode )
, FamilyName_( ifds::FamilyName, &ifds::s_FldProp_FamilyName )
, FundRelnCode_( ifds::FundRelnCode, &ifds::s_FldProp_FundRelnCode )
, FundRelnDesc_( ifds::FundRelnDesc, &ifds::s_FldProp_FundRelnDesc )
, EffectiveDate_( ifds::EffectiveDate, &ifds::s_FldProp_EffectiveDate )
, ProcessDate_( ifds::ProcessDate, &ifds::s_FldProp_ProcessDate )
, Username_( ifds::Username, &ifds::s_FldProp_Username )
, ModUser_( ifds::ModUser, &ifds::s_FldProp_ModUser )
, GroupName2_( ifds::GroupName2, &ifds::s_FldProp_GroupName2 )
, ModDate_( ifds::ModDate, &ifds::s_FldProp_ModDate )
, PrimMstrVer_( ifds::PrimMstrVer, &ifds::s_FldProp_PrimMstrVer )
, PrimMstrRid_( ifds::PrimMstrRid, &ifds::s_FldProp_PrimMstrRid )
, AcctDesignation_( ifds::AcctDesignation, &ifds::s_FldProp_AcctDesignation )
, AcctDesignationDesc_( ifds::AcctDesignationDesc, &ifds::s_FldProp_AcctDesignationDesc )
, ConsolEFT_( ifds::ConsolEFT, &ifds::s_FldProp_ConsolEFT )
, Remarks_( ifds::Remarks, &ifds::s_FldProp_Remarks )
, BankingInstr_( ifds::BankingInstr, &ifds::s_FldProp_BankingInstr )
, FirstEffective_( ifds::FirstEffective, &ifds::s_FldProp_FirstEffective )
, Residency_( ifds::Residency, &ifds::s_FldProp_Residency )
, ShType_( ifds::ShType, &ifds::s_FldProp_ShType )
, FamilyCodeExist_( ifds::FamilyCodeExist, &ifds::s_FldProp_FamilyCodeExist )
, Confidential_( ifds::Confidential, &ifds::s_FldProp_Confidential )
, Channel_( ifds::Channel, &ifds::s_FldProp_Channel )
, DTAExist_( ifds::DTAExist, &ifds::s_FldProp_DTAExist )
, ShrFndSpAgrExists_( ifds::ShrFndSpAgrExists, &ifds::s_FldProp_ShrFndSpAgrExists )
, FeeModelCode_( ifds::FeeModelCode, &ifds::s_FldProp_FeeModelCode )
, ShrFndBrkExist_( ifds::ShrFndBrkExist, &ifds::s_FldProp_ShrFndBrkExist )
{
    cFields_ = 36;
    memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0069_VWRepeat_Record::~dsi_DSTC0069_VWRepeat_Record()
{
}

BFDataImpl* dsi_DSTC0069_VWRepeat_Record::clone()
{
   dsi_DSTC0069_VWRepeat_Record* p = new dsi_DSTC0069_VWRepeat_Record;
   p->ShrNum_ = ShrNum_;
   p->Name1_ = Name1_;
   p->Name2_ = Name2_;
   p->TaxJurisCode_ = TaxJurisCode_;
   p->TaxJurisName_ = TaxJurisName_;
   p->ResProvCode_ = ResProvCode_;
   p->ResProvName_ = ResProvName_;
   p->GroupCode_ = GroupCode_;
   p->GroupName1_ = GroupName1_;
   p->FamilyCode_ = FamilyCode_;
   p->FamilyName_ = FamilyName_;
   p->FundRelnCode_ = FundRelnCode_;
   p->FundRelnDesc_ = FundRelnDesc_;
   p->EffectiveDate_ = EffectiveDate_;
   p->ProcessDate_ = ProcessDate_;
   p->Username_ = Username_;
   p->ModUser_ = ModUser_;
   p->GroupName2_ = GroupName2_;
   p->ModDate_ = ModDate_;
   p->PrimMstrVer_ = PrimMstrVer_;
   p->PrimMstrRid_ = PrimMstrRid_;
   p->AcctDesignation_ = AcctDesignation_;
   p->AcctDesignationDesc_ = AcctDesignationDesc_;
   p->ConsolEFT_ = ConsolEFT_;
   p->Remarks_ = Remarks_;
   p->BankingInstr_ = BankingInstr_;
   p->FirstEffective_ = FirstEffective_;
   p->Residency_ = Residency_;
   p->ShType_ = ShType_;
   p->FamilyCodeExist_ = FamilyCodeExist_;
   p->Confidential_ = Confidential_;
   p->Channel_ = Channel_;
   p->DTAExist_ = DTAExist_;
   p->ShrFndSpAgrExists_ = ShrFndSpAgrExists_;
   p->FeeModelCode_ = FeeModelCode_;
   p->ShrFndBrkExist_ = ShrFndBrkExist_;
   return(p);
}

BFDataField* dsi_DSTC0069_VWRepeat_Record::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40000114: return ( &ShrNum_ ); break; // ShrNum
      case 40000542: return ( &Name1_ ); break; // Name1
      case 40000543: return ( &Name2_ ); break; // Name2
      case 40000796: return ( &TaxJurisCode_ ); break; // TaxJurisCode
      case 40000797: return ( &TaxJurisName_ ); break; // TaxJurisName
      case 40000798: return ( &ResProvCode_ ); break; // ResProvCode
      case 40000799: return ( &ResProvName_ ); break; // ResProvName
      case 40000800: return ( &GroupCode_ ); break; // GroupCode
      case 40000801: return ( &GroupName1_ ); break; // GroupName1
      case 40000802: return ( &FamilyCode_ ); break; // FamilyCode
      case 40000803: return ( &FamilyName_ ); break; // FamilyName
      case 40000804: return ( &FundRelnCode_ ); break; // FundRelnCode
      case 40000805: return ( &FundRelnDesc_ ); break; // FundRelnDesc
      case 40000327: return ( &EffectiveDate_ ); break; // EffectiveDate
      case 40000216: return ( &ProcessDate_ ); break; // ProcessDate
      case 40000117: return ( &Username_ ); break; // Username
      case 40000218: return ( &ModUser_ ); break; // ModUser
      case 40000806: return ( &GroupName2_ ); break; // GroupName2
      case 40000217: return ( &ModDate_ ); break; // ModDate
      case 40000914: return ( &PrimMstrVer_ ); break; // PrimMstrVer
      case 40000915: return ( &PrimMstrRid_ ); break; // PrimMstrRid
      case 40000178: return ( &AcctDesignation_ ); break; // AcctDesignation
      case 40000179: return ( &AcctDesignationDesc_ ); break; // AcctDesignationDesc
      case 40000975: return ( &ConsolEFT_ ); break; // ConsolEFT
      case 40000590: return ( &Remarks_ ); break; // Remarks
      case 40000955: return ( &BankingInstr_ ); break; // BankingInstr
      case 40001371: return ( &FirstEffective_ ); break; // FirstEffective
      case 40001954: return ( &Residency_ ); break; // Residency
      case 40002292: return ( &ShType_ ); break; // ShType
      case 40003594: return ( &FamilyCodeExist_ ); break; // FamilyCodeExist
      case 40004123: return ( &Confidential_ ); break; // Confidential
      case 40004140: return ( &Channel_ ); break; // Channel
      case 40004259: return ( &DTAExist_ ); break; // DTAExist
      case 40004574: return ( &ShrFndSpAgrExists_ ); break; // ShrFndSpAgrExists
      case 40004584: return ( &FeeModelCode_ ); break; // FeeModelCode
      case 40004801: return ( &ShrFndBrkExist_ ); break; // ShrFndBrkExist
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0069_VWRepeat_Record::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0069_VWRepeat_Record* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0069_VWRepeat_Record::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 36 )
   {
      BFDataField* pField = aFlds_[iField];
      if( NULL == pField )
      {
         switch(iField)
         {
            case 0: aFlds_[0] = &ShrNum_; break;
            case 1: aFlds_[1] = &Name1_; break;
            case 2: aFlds_[2] = &Name2_; break;
            case 3: aFlds_[3] = &TaxJurisCode_; break;
            case 4: aFlds_[4] = &TaxJurisName_; break;
            case 5: aFlds_[5] = &ResProvCode_; break;
            case 6: aFlds_[6] = &ResProvName_; break;
            case 7: aFlds_[7] = &GroupCode_; break;
            case 8: aFlds_[8] = &GroupName1_; break;
            case 9: aFlds_[9] = &FamilyCode_; break;
            case 10: aFlds_[10] = &FamilyName_; break;
            case 11: aFlds_[11] = &FundRelnCode_; break;
            case 12: aFlds_[12] = &FundRelnDesc_; break;
            case 13: aFlds_[13] = &EffectiveDate_; break;
            case 14: aFlds_[14] = &ProcessDate_; break;
            case 15: aFlds_[15] = &Username_; break;
            case 16: aFlds_[16] = &ModUser_; break;
            case 17: aFlds_[17] = &GroupName2_; break;
            case 18: aFlds_[18] = &ModDate_; break;
            case 19: aFlds_[19] = &PrimMstrVer_; break;
            case 20: aFlds_[20] = &PrimMstrRid_; break;
            case 21: aFlds_[21] = &AcctDesignation_; break;
            case 22: aFlds_[22] = &AcctDesignationDesc_; break;
            case 23: aFlds_[23] = &ConsolEFT_; break;
            case 24: aFlds_[24] = &Remarks_; break;
            case 25: aFlds_[25] = &BankingInstr_; break;
            case 26: aFlds_[26] = &FirstEffective_; break;
            case 27: aFlds_[27] = &Residency_; break;
            case 28: aFlds_[28] = &ShType_; break;
            case 29: aFlds_[29] = &FamilyCodeExist_; break;
            case 30: aFlds_[30] = &Confidential_; break;
            case 31: aFlds_[31] = &Channel_; break;
            case 32: aFlds_[32] = &DTAExist_; break;
            case 33: aFlds_[33] = &ShrFndSpAgrExists_; break;
            case 34: aFlds_[34] = &FeeModelCode_; break;
            case 35: aFlds_[35] = &ShrFndBrkExist_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0069_VWRepeat_Record::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0069_VWRepeat_Record* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0069_VWRepeat_Record::getLargestDefinedField( void ) const
{
   return( 250 );
}

unsigned long dsi_DSTC0069_VWRepeat_Record::getDefinedByteLength( void ) const
{
    return( 1551 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0069_VWRepeat_Record::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0069_VWRepeat_Record::fieldExists( id );
}

bool dsi_DSTC0069_VWRepeat_Record::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40000114: return( true );
      case 40000542: return( true );
      case 40000543: return( true );
      case 40000796: return( true );
      case 40000797: return( true );
      case 40000798: return( true );
      case 40000799: return( true );
      case 40000800: return( true );
      case 40000801: return( true );
      case 40000802: return( true );
      case 40000803: return( true );
      case 40000804: return( true );
      case 40000805: return( true );
      case 40000327: return( true );
      case 40000216: return( true );
      case 40000117: return( true );
      case 40000218: return( true );
      case 40000806: return( true );
      case 40000217: return( true );
      case 40000914: return( true );
      case 40000915: return( true );
      case 40000178: return( true );
      case 40000179: return( true );
      case 40000975: return( true );
      case 40000590: return( true );
      case 40000955: return( true );
      case 40001371: return( true );
      case 40001954: return( true );
      case 40002292: return( true );
      case 40003594: return( true );
      case 40004123: return( true );
      case 40004140: return( true );
      case 40004259: return( true );
      case 40004574: return( true );
      case 40004584: return( true );
      case 40004801: return( true );
   }
   return false;
}

