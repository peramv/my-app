// BFDataImpl implementation file for DataSet DSTC0003.VWRepeat_Record
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:58 2015


#include "stdafx.h"




#include <bfdata/bfdataimpl.hpp>
#include "dsi_dstc0003_vwrepeat_record.h"


// This function creates an instance of dsi_DSTC0003_VWRepeat_Record
// The function is required by the factory class as that class may choke the compiler
// with excessive symbols if all of the required header files needed to be #include'd
BFDataImpl* create_dsi_DSTC0003_VWRepeat_Record() { return new dsi_DSTC0003_VWRepeat_Record; }

dsi_DSTC0003_VWRepeat_Record::dsi_DSTC0003_VWRepeat_Record()
: BFDataImpl( 40000127 )
, AccountNum_( ifds::AccountNum, &ifds::s_FldProp_AccountNum )
, ShrNum_( ifds::ShrNum, &ifds::s_FldProp_ShrNum )
, LastName_( ifds::LastName, &ifds::s_FldProp_LastName )
, FirstName_( ifds::FirstName, &ifds::s_FldProp_FirstName )
, BirthLastName_( ifds::BirthLastName, &ifds::s_FldProp_BirthLastName )
, BirthFirstName_( ifds::BirthFirstName, &ifds::s_FldProp_BirthFirstName )
, SIN_( ifds::SIN, &ifds::s_FldProp_SIN )
, BirthDate_( ifds::BirthDate, &ifds::s_FldProp_BirthDate )
, TaxType_( ifds::TaxType, &ifds::s_FldProp_TaxType )
, TaxTypeDesc_( ifds::TaxTypeDesc, &ifds::s_FldProp_TaxTypeDesc )
, HomePhone_( ifds::HomePhone, &ifds::s_FldProp_HomePhone )
, MultipleReln_( ifds::MultipleReln, &ifds::s_FldProp_MultipleReln )
, EntityId_( ifds::EntityId, &ifds::s_FldProp_EntityId )
, Address1_( ifds::Address1, &ifds::s_FldProp_Address1 )
, Address2_( ifds::Address2, &ifds::s_FldProp_Address2 )
, Address3_( ifds::Address3, &ifds::s_FldProp_Address3 )
, Address4_( ifds::Address4, &ifds::s_FldProp_Address4 )
, Address5_( ifds::Address5, &ifds::s_FldProp_Address5 )
, PostalCode_( ifds::PostalCode, &ifds::s_FldProp_PostalCode )
, Addr11Line1_( ifds::Addr11Line1, &ifds::s_FldProp_Addr11Line1 )
, Addr11Line2_( ifds::Addr11Line2, &ifds::s_FldProp_Addr11Line2 )
, Addr11Line3_( ifds::Addr11Line3, &ifds::s_FldProp_Addr11Line3 )
, Addr11Line4_( ifds::Addr11Line4, &ifds::s_FldProp_Addr11Line4 )
, Addr11Line5_( ifds::Addr11Line5, &ifds::s_FldProp_Addr11Line5 )
, PostalCode11_( ifds::PostalCode11, &ifds::s_FldProp_PostalCode11 )
, IdType1_( ifds::IdType1, &ifds::s_FldProp_IdType1 )
, IdValue1_( ifds::IdValue1, &ifds::s_FldProp_IdValue1 )
, IdType2_( ifds::IdType2, &ifds::s_FldProp_IdType2 )
, IdValue2_( ifds::IdValue2, &ifds::s_FldProp_IdValue2 )
, IdType3_( ifds::IdType3, &ifds::s_FldProp_IdType3 )
, IdValue3_( ifds::IdValue3, &ifds::s_FldProp_IdValue3 )
, IdType4_( ifds::IdType4, &ifds::s_FldProp_IdType4 )
, IdValue4_( ifds::IdValue4, &ifds::s_FldProp_IdValue4 )
, IdType5_( ifds::IdType5, &ifds::s_FldProp_IdType5 )
, IdValue5_( ifds::IdValue5, &ifds::s_FldProp_IdValue5 )
, IdType6_( ifds::IdType6, &ifds::s_FldProp_IdType6 )
, IdValue6_( ifds::IdValue6, &ifds::s_FldProp_IdValue6 )
, IdType7_( ifds::IdType7, &ifds::s_FldProp_IdType7 )
, IdValue7_( ifds::IdValue7, &ifds::s_FldProp_IdValue7 )
, IdType8_( ifds::IdType8, &ifds::s_FldProp_IdType8 )
, IdValue8_( ifds::IdValue8, &ifds::s_FldProp_IdValue8 )
, IdType9_( ifds::IdType9, &ifds::s_FldProp_IdType9 )
, IdValue9_( ifds::IdValue9, &ifds::s_FldProp_IdValue9 )
, IdType10_( ifds::IdType10, &ifds::s_FldProp_IdType10 )
, IdValue10_( ifds::IdValue10, &ifds::s_FldProp_IdValue10 )
, EntityType_( ifds::EntityType, &ifds::s_FldProp_EntityType )
, EntityTypeSeq_( ifds::EntityTypeSeq, &ifds::s_FldProp_EntityTypeSeq )
, AcctType_( ifds::AcctType, &ifds::s_FldProp_AcctType )
, CountryCode_( ifds::CountryCode, &ifds::s_FldProp_CountryCode )
, SocialCode_( ifds::SocialCode, &ifds::s_FldProp_SocialCode )
, SocialCodeDesc_( ifds::SocialCodeDesc, &ifds::s_FldProp_SocialCodeDesc )
, AcctDesignation_( ifds::AcctDesignation, &ifds::s_FldProp_AcctDesignation )
, AcctStatus_( ifds::AcctStatus, &ifds::s_FldProp_AcctStatus )
, AltAccount_( ifds::AltAccount, &ifds::s_FldProp_AltAccount )
, InTrustJoint_( ifds::InTrustJoint, &ifds::s_FldProp_InTrustJoint )
, CompanyCode_( ifds::CompanyCode, &ifds::s_FldProp_CompanyCode )
, AcctGroup_( ifds::AcctGroup, &ifds::s_FldProp_AcctGroup )
, AcctTypeDesc_( ifds::AcctTypeDesc, &ifds::s_FldProp_AcctTypeDesc )
, StopPurchase_( ifds::StopPurchase, &ifds::s_FldProp_StopPurchase )
, StopXferIn_( ifds::StopXferIn, &ifds::s_FldProp_StopXferIn )
, StopXferOut_( ifds::StopXferOut, &ifds::s_FldProp_StopXferOut )
, StopRed_( ifds::StopRed, &ifds::s_FldProp_StopRed )
, EntityTypeDesc_( ifds::EntityTypeDesc, &ifds::s_FldProp_EntityTypeDesc )
, WrapAccount_( ifds::WrapAccount, &ifds::s_FldProp_WrapAccount )
, RegistrationInfo_( ifds::RegistrationInfo, &ifds::s_FldProp_RegistrationInfo )
, GoodBad_( ifds::GoodBad, &ifds::s_FldProp_GoodBad )
, ValidRATaxType_( ifds::ValidRATaxType, &ifds::s_FldProp_ValidRATaxType )
{
   cFields_ = 67;
   memset( &aFlds_[0], 0x00, sizeof( aFlds_ ) );
}

dsi_DSTC0003_VWRepeat_Record::~dsi_DSTC0003_VWRepeat_Record()
{
}

BFDataImpl* dsi_DSTC0003_VWRepeat_Record::clone()
{
   dsi_DSTC0003_VWRepeat_Record* p = new dsi_DSTC0003_VWRepeat_Record;
   p->AccountNum_ = AccountNum_;
   p->ShrNum_ = ShrNum_;
   p->LastName_ = LastName_;
   p->FirstName_ = FirstName_;
   p->BirthLastName_ = BirthLastName_;
   p->BirthFirstName_ = BirthFirstName_;
   p->SIN_ = SIN_;
   p->BirthDate_ = BirthDate_;
   p->TaxType_ = TaxType_;
   p->TaxTypeDesc_ = TaxTypeDesc_;
   p->HomePhone_ = HomePhone_;
   p->MultipleReln_ = MultipleReln_;
   p->EntityId_ = EntityId_;
   p->Address1_ = Address1_;
   p->Address2_ = Address2_;
   p->Address3_ = Address3_;
   p->Address4_ = Address4_;
   p->Address5_ = Address5_;
   p->PostalCode_ = PostalCode_;
   p->Addr11Line1_ = Addr11Line1_;
   p->Addr11Line2_ = Addr11Line2_;
   p->Addr11Line3_ = Addr11Line3_;
   p->Addr11Line4_ = Addr11Line4_;
   p->Addr11Line5_ = Addr11Line5_;
   p->PostalCode11_ = PostalCode11_;
   p->IdType1_ = IdType1_;
   p->IdValue1_ = IdValue1_;
   p->IdType2_ = IdType2_;
   p->IdValue2_ = IdValue2_;
   p->IdType3_ = IdType3_;
   p->IdValue3_ = IdValue3_;
   p->IdType4_ = IdType4_;
   p->IdValue4_ = IdValue4_;
   p->IdType5_ = IdType5_;
   p->IdValue5_ = IdValue5_;
   p->IdType6_ = IdType6_;
   p->IdValue6_ = IdValue6_;
   p->IdType7_ = IdType7_;
   p->IdValue7_ = IdValue7_;
   p->IdType8_ = IdType8_;
   p->IdValue8_ = IdValue8_;
   p->IdType9_ = IdType9_;
   p->IdValue9_ = IdValue9_;
   p->IdType10_ = IdType10_;
   p->IdValue10_ = IdValue10_;
   p->EntityType_ = EntityType_;
   p->EntityTypeSeq_ = EntityTypeSeq_;
   p->AcctType_ = AcctType_;
   p->CountryCode_ = CountryCode_;
   p->SocialCode_ = SocialCode_;
   p->SocialCodeDesc_ = SocialCodeDesc_;
   p->AcctDesignation_ = AcctDesignation_;
   p->AcctStatus_ = AcctStatus_;
   p->AltAccount_ = AltAccount_;
   p->InTrustJoint_ = InTrustJoint_;
   p->CompanyCode_ = CompanyCode_;
   p->AcctGroup_ = AcctGroup_;
   p->AcctTypeDesc_ = AcctTypeDesc_;
   p->StopPurchase_ = StopPurchase_;
   p->StopXferIn_ = StopXferIn_;
   p->StopXferOut_ = StopXferOut_;
   p->StopRed_ = StopRed_;
   p->EntityTypeDesc_ = EntityTypeDesc_;
   p->WrapAccount_ = WrapAccount_;
   p->RegistrationInfo_ = RegistrationInfo_;
   p->GoodBad_ = GoodBad_;
   p->ValidRATaxType_ = ValidRATaxType_;
   return(p);
}

BFDataField* dsi_DSTC0003_VWRepeat_Record::getElement( const BFFieldId& id )
{
   switch( id.getId() ) {
      case 40000040: return ( &AccountNum_ ); break; // AccountNum
      case 40000114: return ( &ShrNum_ ); break; // ShrNum
      case 40000128: return ( &LastName_ ); break; // LastName
      case 40000129: return ( &FirstName_ ); break; // FirstName
      case 40000130: return ( &BirthLastName_ ); break; // BirthLastName
      case 40000131: return ( &BirthFirstName_ ); break; // BirthFirstName
      case 40000132: return ( &SIN_ ); break; // SIN
      case 40000133: return ( &BirthDate_ ); break; // BirthDate
      case 40000134: return ( &TaxType_ ); break; // TaxType
      case 40000135: return ( &TaxTypeDesc_ ); break; // TaxTypeDesc
      case 40000136: return ( &HomePhone_ ); break; // HomePhone
      case 40000137: return ( &MultipleReln_ ); break; // MultipleReln
      case 40000033: return ( &EntityId_ ); break; // EntityId
      case 40000138: return ( &Address1_ ); break; // Address1
      case 40000139: return ( &Address2_ ); break; // Address2
      case 40000140: return ( &Address3_ ); break; // Address3
      case 40000141: return ( &Address4_ ); break; // Address4
      case 40000142: return ( &Address5_ ); break; // Address5
      case 40000143: return ( &PostalCode_ ); break; // PostalCode
      case 40000144: return ( &Addr11Line1_ ); break; // Addr11Line1
      case 40000145: return ( &Addr11Line2_ ); break; // Addr11Line2
      case 40000146: return ( &Addr11Line3_ ); break; // Addr11Line3
      case 40000147: return ( &Addr11Line4_ ); break; // Addr11Line4
      case 40000148: return ( &Addr11Line5_ ); break; // Addr11Line5
      case 40000149: return ( &PostalCode11_ ); break; // PostalCode11
      case 40000150: return ( &IdType1_ ); break; // IdType1
      case 40000151: return ( &IdValue1_ ); break; // IdValue1
      case 40000152: return ( &IdType2_ ); break; // IdType2
      case 40000153: return ( &IdValue2_ ); break; // IdValue2
      case 40000154: return ( &IdType3_ ); break; // IdType3
      case 40000155: return ( &IdValue3_ ); break; // IdValue3
      case 40000156: return ( &IdType4_ ); break; // IdType4
      case 40000157: return ( &IdValue4_ ); break; // IdValue4
      case 40000158: return ( &IdType5_ ); break; // IdType5
      case 40000159: return ( &IdValue5_ ); break; // IdValue5
      case 40000160: return ( &IdType6_ ); break; // IdType6
      case 40000161: return ( &IdValue6_ ); break; // IdValue6
      case 40000162: return ( &IdType7_ ); break; // IdType7
      case 40000163: return ( &IdValue7_ ); break; // IdValue7
      case 40000164: return ( &IdType8_ ); break; // IdType8
      case 40000165: return ( &IdValue8_ ); break; // IdValue8
      case 40000166: return ( &IdType9_ ); break; // IdType9
      case 40000167: return ( &IdValue9_ ); break; // IdValue9
      case 40000168: return ( &IdType10_ ); break; // IdType10
      case 40000169: return ( &IdValue10_ ); break; // IdValue10
      case 40000604: return ( &EntityType_ ); break; // EntityType
      case 40001103: return ( &EntityTypeSeq_ ); break; // EntityTypeSeq
      case 40000174: return ( &AcctType_ ); break; // AcctType
      case 40000344: return ( &CountryCode_ ); break; // CountryCode
      case 40002187: return ( &SocialCode_ ); break; // SocialCode
      case 40002189: return ( &SocialCodeDesc_ ); break; // SocialCodeDesc
      case 40000178: return ( &AcctDesignation_ ); break; // AcctDesignation
      case 40000188: return ( &AcctStatus_ ); break; // AcctStatus
      case 40000173: return ( &AltAccount_ ); break; // AltAccount
      case 40002190: return ( &InTrustJoint_ ); break; // InTrustJoint
      case 40002245: return ( &CompanyCode_ ); break; // CompanyCode
      case 40000208: return ( &AcctGroup_ ); break; // AcctGroup
      case 40000175: return ( &AcctTypeDesc_ ); break; // AcctTypeDesc
      case 40000699: return ( &StopPurchase_ ); break; // StopPurchase
      case 40000197: return ( &StopXferIn_ ); break; // StopXferIn
      case 40000198: return ( &StopXferOut_ ); break; // StopXferOut
      case 40000593: return ( &StopRed_ ); break; // StopRed
      case 40000605: return ( &EntityTypeDesc_ ); break; // EntityTypeDesc
      case 40003544: return ( &WrapAccount_ ); break; // WrapAccount
      case 40004572: return ( &RegistrationInfo_ ); break; // RegistrationInfo
      case 40000496: return ( &GoodBad_ ); break; // GoodBad
      case 40006891: return ( &ValidRATaxType_ ); break; // ValidRATaxType
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0003_VWRepeat_Record::getElement( const BFFieldId& id ) const
{
   return( ( const_cast< dsi_DSTC0003_VWRepeat_Record* >(this) )->getElement( id ) );
}

BFDataField* dsi_DSTC0003_VWRepeat_Record::getElementByIndex( unsigned int iField )
{
   if ( iField >=0 && iField < 67 )
   {
      BFDataField* pField = aFlds_[iField];
      if( NULL == pField )
      {
         switch(iField)
         {
            case 0: aFlds_[0] = &AccountNum_; break;
            case 1: aFlds_[1] = &ShrNum_; break;
            case 2: aFlds_[2] = &LastName_; break;
            case 3: aFlds_[3] = &FirstName_; break;
            case 4: aFlds_[4] = &BirthLastName_; break;
            case 5: aFlds_[5] = &BirthFirstName_; break;
            case 6: aFlds_[6] = &SIN_; break;
            case 7: aFlds_[7] = &BirthDate_; break;
            case 8: aFlds_[8] = &TaxType_; break;
            case 9: aFlds_[9] = &TaxTypeDesc_; break;
            case 10: aFlds_[10] = &HomePhone_; break;
            case 11: aFlds_[11] = &MultipleReln_; break;
            case 12: aFlds_[12] = &EntityId_; break;
            case 13: aFlds_[13] = &Address1_; break;
            case 14: aFlds_[14] = &Address2_; break;
            case 15: aFlds_[15] = &Address3_; break;
            case 16: aFlds_[16] = &Address4_; break;
            case 17: aFlds_[17] = &Address5_; break;
            case 18: aFlds_[18] = &PostalCode_; break;
            case 19: aFlds_[19] = &Addr11Line1_; break;
            case 20: aFlds_[20] = &Addr11Line2_; break;
            case 21: aFlds_[21] = &Addr11Line3_; break;
            case 22: aFlds_[22] = &Addr11Line4_; break;
            case 23: aFlds_[23] = &Addr11Line5_; break;
            case 24: aFlds_[24] = &PostalCode11_; break;
            case 25: aFlds_[25] = &IdType1_; break;
            case 26: aFlds_[26] = &IdValue1_; break;
            case 27: aFlds_[27] = &IdType2_; break;
            case 28: aFlds_[28] = &IdValue2_; break;
            case 29: aFlds_[29] = &IdType3_; break;
            case 30: aFlds_[30] = &IdValue3_; break;
            case 31: aFlds_[31] = &IdType4_; break;
            case 32: aFlds_[32] = &IdValue4_; break;
            case 33: aFlds_[33] = &IdType5_; break;
            case 34: aFlds_[34] = &IdValue5_; break;
            case 35: aFlds_[35] = &IdType6_; break;
            case 36: aFlds_[36] = &IdValue6_; break;
            case 37: aFlds_[37] = &IdType7_; break;
            case 38: aFlds_[38] = &IdValue7_; break;
            case 39: aFlds_[39] = &IdType8_; break;
            case 40: aFlds_[40] = &IdValue8_; break;
            case 41: aFlds_[41] = &IdType9_; break;
            case 42: aFlds_[42] = &IdValue9_; break;
            case 43: aFlds_[43] = &IdType10_; break;
            case 44: aFlds_[44] = &IdValue10_; break;
            case 45: aFlds_[45] = &EntityType_; break;
            case 46: aFlds_[46] = &EntityTypeSeq_; break;
            case 47: aFlds_[47] = &AcctType_; break;
            case 48: aFlds_[48] = &CountryCode_; break;
            case 49: aFlds_[49] = &SocialCode_; break;
            case 50: aFlds_[50] = &SocialCodeDesc_; break;
            case 51: aFlds_[51] = &AcctDesignation_; break;
            case 52: aFlds_[52] = &AcctStatus_; break;
            case 53: aFlds_[53] = &AltAccount_; break;
            case 54: aFlds_[54] = &InTrustJoint_; break;
            case 55: aFlds_[55] = &CompanyCode_; break;
            case 56: aFlds_[56] = &AcctGroup_; break;
            case 57: aFlds_[57] = &AcctTypeDesc_; break;
            case 58: aFlds_[58] = &StopPurchase_; break;
            case 59: aFlds_[59] = &StopXferIn_; break;
            case 60: aFlds_[60] = &StopXferOut_; break;
            case 61: aFlds_[61] = &StopRed_; break;
            case 62: aFlds_[62] = &EntityTypeDesc_; break;
            case 63: aFlds_[63] = &WrapAccount_; break;
            case 64: aFlds_[64] = &RegistrationInfo_; break;
            case 65: aFlds_[65] = &GoodBad_; break;
            case 66: aFlds_[66] = &ValidRATaxType_; break;
         }
         pField = aFlds_[iField];
         if( NULL == pField ) return( NULL );
      }
      return( pField );
   }
   return( NULL );
}

const BFDataField* dsi_DSTC0003_VWRepeat_Record::getElementByIndex( unsigned int iField ) const
{
   return( ( const_cast< dsi_DSTC0003_VWRepeat_Record* >(this) )->getElementByIndex( iField ) );
}

unsigned long dsi_DSTC0003_VWRepeat_Record::getLargestDefinedField( void ) const
{
   return( 80 );
}

unsigned long dsi_DSTC0003_VWRepeat_Record::getDefinedByteLength( void ) const
{
   return( 3219 * sizeof( I_CHAR ) );
}

bool dsi_DSTC0003_VWRepeat_Record::exists( const BFFieldId& id ) const
{
   return dsi_DSTC0003_VWRepeat_Record::fieldExists( id );
}

bool dsi_DSTC0003_VWRepeat_Record::fieldExists( const BFFieldId& id )
{
   switch( id.getId() )
   {
      case 40000040: return( true );
      case 40000114: return( true );
      case 40000128: return( true );
      case 40000129: return( true );
      case 40000130: return( true );
      case 40000131: return( true );
      case 40000132: return( true );
      case 40000133: return( true );
      case 40000134: return( true );
      case 40000135: return( true );
      case 40000136: return( true );
      case 40000137: return( true );
      case 40000033: return( true );
      case 40000138: return( true );
      case 40000139: return( true );
      case 40000140: return( true );
      case 40000141: return( true );
      case 40000142: return( true );
      case 40000143: return( true );
      case 40000144: return( true );
      case 40000145: return( true );
      case 40000146: return( true );
      case 40000147: return( true );
      case 40000148: return( true );
      case 40000149: return( true );
      case 40000150: return( true );
      case 40000151: return( true );
      case 40000152: return( true );
      case 40000153: return( true );
      case 40000154: return( true );
      case 40000155: return( true );
      case 40000156: return( true );
      case 40000157: return( true );
      case 40000158: return( true );
      case 40000159: return( true );
      case 40000160: return( true );
      case 40000161: return( true );
      case 40000162: return( true );
      case 40000163: return( true );
      case 40000164: return( true );
      case 40000165: return( true );
      case 40000166: return( true );
      case 40000167: return( true );
      case 40000168: return( true );
      case 40000169: return( true );
      case 40000604: return( true );
      case 40001103: return( true );
      case 40000174: return( true );
      case 40000344: return( true );
      case 40002187: return( true );
      case 40002189: return( true );
      case 40000178: return( true );
      case 40000188: return( true );
      case 40000173: return( true );
      case 40002190: return( true );
      case 40002245: return( true );
      case 40000208: return( true );
      case 40000175: return( true );
      case 40000699: return( true );
      case 40000197: return( true );
      case 40000198: return( true );
      case 40000593: return( true );
      case 40000605: return( true );
      case 40003544: return( true );
      case 40004572: return( true );
      case 40000496: return( true );
      case 40006891: return( true );
   }
   return false;
}

