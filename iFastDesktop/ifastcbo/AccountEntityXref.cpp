//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : AccountEntityXref.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//******************************************************************************
#include "stdafx.h"
#include "demographics.hpp"
#include "accountentityxref.hpp"
#include "accountentityxrefobject.hpp"
#include "entityids.hpp"
#include "entityidslist.hpp"
#include "entity.hpp"
#include "mfaccount.hpp"
#include "mfaccountlist.hpp"
#include "mgmtcooptions.hpp"
#include "regdocumentlist.hpp"
#include "shareholder.hpp"
#include "taxtyperule.hpp"
#include "worksessionentitylist.hpp"

#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include <ifastdataimpl\dse_dstc0011_vw.hpp>
#include <ifastdataimpl\dse_dstc0050_vw.hpp>
#include <ifastdataimpl\dse_dstc0050_req.hpp>
#include <ifastdataimpl\dse_dstc0051_vw.hpp>
#include <ifastdataimpl\dse_dstc0061_vw.hpp>
#include <ifastdataimpl\dse_dstc0061_req.hpp>
#include <ifastdataimpl\dse_dstc0083_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest WHERE_USED;
   extern CLASS_IMPORT const DSTCRequest ENTITY;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const ESCROW_BAND;
   extern CLASS_IMPORT I_CHAR * const ASSIGNEE_ENTITY_TYPE_SETUP;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId InqPerm;
   extern CLASS_IMPORT const BFTextFieldId AcctPurpose;
   extern CLASS_IMPORT const BFTextFieldId OwnerSpouseName;
   extern CLASS_IMPORT const BFNumericFieldId SpouseEntityID;
   extern CLASS_IMPORT const BFTextFieldId DeathClaimDocExist;
   extern CLASS_IMPORT const BFTextFieldId RegDocsExist;
   extern CLASS_IMPORT const BFTextFieldId LetterReq;
   extern CLASS_IMPORT const BFTextFieldId RES2ParentLglList;
   extern CLASS_IMPORT const BFTextFieldId RES2DesInstList;
   extern CLASS_IMPORT const BFTextFieldId RES2PCGList;
   extern CLASS_IMPORT const BFTextFieldId PorfolioIsRequried;
   extern CLASS_IMPORT const BFTextFieldId ValidRATaxType;
   extern CLASS_IMPORT const BFTextFieldId UpdShrTaxJuris;
   extern CLASS_IMPORT const BFTextFieldId MstrActActive;
   extern CLASS_IMPORT const BFTextFieldId CSSStopSINMatch;
   extern CLASS_IMPORT const BFTextFieldId CRSEntityList;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME                          = I_( "AccountEntityXref" );
   const I_CHAR * const ACCOUNT_NUMBER_FIELD               = I_( "AccountNum" );
   const I_CHAR * const ENTITY_ID_FIELD                    = I_( "EntityId" );
   const I_CHAR * const ENTITY_TYPE_FIELD                  = I_( "EntityType" );
   const I_CHAR * const ENTITY_SEQ_NUM_FIELD               = I_( "EntitySeq" );
   const I_CHAR * const GETVALUEFORTAG                     = I_( "getValueForTag" );

   const I_CHAR * const ACCOUNTHOLDER_ENTITY_TYPE          = I_( "01" );
   const I_CHAR * const ANNUITANT_ENTITY_TYPE              = I_( "05" );
   const I_CHAR * const SPOUSAL_CONTRIBUTOR_ENTITY_TYPE    = I_( "06" );
   const I_CHAR * const PRIMARY_BENEF_ENTITY_TYPE          = I_( "07" );
   const I_CHAR * const SECONDARY_BENEF_ENTITY_TYPE        = I_( "08" );
   const I_CHAR * const SUCCESSOR_ENTITY_TYPE              = I_( "09" );   
   const I_CHAR * const SPOUSE_NON_CONTRIBUTOR_ENTITY_TYPE = I_( "10" );
   const I_CHAR * const ESCROW_REPREZENTATIVE_ENTITY_TYPE  = I_( "11" );
   const I_CHAR * const TRUSTEE_ENTITY_TYPE                = I_( "13" );
   const I_CHAR * const ITF_INDIVIDUAL_ENTITY_TYPE         = I_( "14" );
   const I_CHAR * const SPOUSAL_TRANSFEREE_ENTITY_TYPE     = I_( "19" );
   const I_CHAR * const EMPLOYER_ENTITY_TYPE               = I_( "20" );
   const I_CHAR * const NOMINEE_OWNER_ENTITY_TYPE          = I_( "21" );
   const I_CHAR * const RESP_BENEFICIARY_ENTITY_TYPE       = I_( "50" );
   const I_CHAR * const PARENT_GUARDIAN_ENTITY_TYPE        = I_( "51" );
   const I_CHAR * const RESP_DESIGNATED_INSTIT_ENTITY_TYPE = I_( "52" );
   const I_CHAR * const ASSIGNEE_ENTITY_TYPE               = I_( "53" );
   const I_CHAR * const RESP_PCG_INDIV_ENTITY_TYPE         = I_( "55" );
   const I_CHAR * const RESP_PCG_INST_ENTITY_TYPE          = I_( "56" );
   const I_CHAR * const FORMER_SPOUSE_ENTITY_TYPE          = I_( "57" );
   const I_CHAR * const CLEARING_PLATFORM_ENTITY_TYPE      = I_( "58" );
   const I_CHAR * const NEW_COUNT_TAG                      = I_( "NewCountTag" );
   const I_CHAR * const CODE_CLEARING_PLATFORM_ID_VAL      = I_( "18" );
   const I_CHAR * const RELATED_PARTY_ENTITY_TYPE          = I_( "71" );
   const I_CHAR * const LEAD_ACCOUNT_MANAGER_ENTITY_TYPE   = I_( "76" );
   const I_CHAR * const ACCOUNT_MANAGER_ENTITY_TYPE        = I_( "77" );
   const I_CHAR * const RELATED_PARTY_AML_ENTITY_TYPE      = I_( "78" );

   const I_CHAR * const NON_REGISTERED_TAX_TYPE            = I_( "0" ); 
   const I_CHAR * const FAMILY_RESP_TAX_TYPE               = I_( "M" ); 
   const I_CHAR * const INDIVIDUAL_RESP_TAX_TYPE           = I_( "9" ); 
   const I_CHAR * const RRSP_TAX_TYPE                      = I_( "1" ); 
   const I_CHAR * const RRIF_TAX_TYPE                      = I_( "2" ); 
   const I_CHAR * const LRSP_TAX_TYPE                      = I_( "U" ); 
   const I_CHAR * const WILL_DEFIND_TAX_TYPE               = I_( "S" ); 
   const I_CHAR * const TFSA_TAX_TYPE                      = I_( "V" );

   const I_CHAR * const LRIF_TAX_TYPE                      = I_( "L" );   
   const I_CHAR * const DPSP_TAX_TYPE                      = I_( "7" );
   const I_CHAR * const RPP_TAX_TYPE                       = I_( "8" );
   const I_CHAR * const LIRA_TAX_TYPE                      = I_( "C" );
   const I_CHAR * const PRIF_TAX_TYPE                      = I_( "R" );
   const I_CHAR * const INDIVIDUAL_ACCT_TYPE               = I_( "0" ); 
   const I_CHAR * const SPOUSAL_ACCT_TYPE                  = I_( "1" ); 
   const I_CHAR * const JOINT_ACCT_TYPE                    = I_( "2" ); 
   const I_CHAR * const TRUST_ACCT_TYPE                    = I_( "3" ); 
   const I_CHAR * const ESOP_INVESTMENT                    = I_( "D" );
   const I_CHAR * const RIF_PLAN_TYPE                      = I_( "RIF" );

   const I_CHAR * const TAX_TYPE_OA                        = I_( "OA" ); 
   const I_CHAR * const TAX_TYPE_SA                        = I_( "SA" ); 
   const I_CHAR * const TAX_TYPE_SRS                       = I_( "SR" ); 

   const I_CHAR * const ESOP_PARTICIPATION                 = I_( "E" );

   const I_CHAR * const NOMINEE_ACCT_DESIGNATION           = I_( "2" );
   const I_CHAR * const INTERMEDIARY_ACCT_DESIGNATION      = I_( "3" );

   const I_CHAR * const CURRENT_BENEFICIARY                = I_( "00" );

   const I_CHAR * const EMPTY_STRING                       = I_( "" );
   const I_CHAR * const YES                                = I_( "Y" );
   const I_CHAR * const NO                                 = I_( "N" );
   const I_CHAR * const CFDS                               = I_( "Canada" );

   const I_CHAR * const ADMINFEE_CODE                      = I_( "AF" );
   const I_CHAR * const PURCHASE_CODE                      = I_( "ED" );     // trade trans type Purchase
   const I_CHAR * const REDEMPTION_CODE                    = I_( "PW" );     // trade trans type Redemption
   const I_CHAR * const EX_FER_OUT_CODE                    = I_( "XFOUT" );  // trade trans type Exchange Out
   const I_CHAR * const EXCHANGE_OUT_CODE                  = I_( "EXOUT" );  // trade trans type Exchange Out
   const I_CHAR * const TRANSFER_OUT_CODE                  = I_( "TFOUT" );  // trade trans type Transfer Out

   const I_CHAR * const TIK_TRF_OUT_CODE                   = I_( "TIKXFOUT" );  // trade trans type Exchange Out
   const I_CHAR * const RRIF_AWD                           = I_( "RIF_AWD" ); // RRIF,LIF,LRIF AWD
   const I_CHAR * const RRIF_OPT_AWD                       = I_( "RIF_OPT_AWD" ); // RRIF,LIF,LRIF Optional AWD
   const I_CHAR * const ADDR_CHG                           = I_( "ADDR_CHANGE" );
   const I_CHAR * const ADD_ENTITY                         = I_( "ADD_ENTITY" );
   const I_CHAR * const CHG_ENTITY                         = I_( "CHG_ENTITY" );
   const I_CHAR * const SWP_CHG                            = I_( "SWP_CHG" );
   const I_CHAR * const CHG_ADD_ESCROW                     = I_( "CHGADDESCROW" );

   const int ACCOUNT_OWNER                                 = 1;
   const int WHERE_USED                                    = 2;
   const I_CHAR * const CODE_SIN                           = I_( "06" );
   const I_CHAR * const YOUNTH_PORTFOLIO                   = I_("YP");
   const I_CHAR * OTHER                                    = I_( "99" );
   const I_CHAR * OWNER_SPOUSAL                            = I_( "98" );

   const I_CHAR * const BLANK_SUBSTITUTION                 = I_( " = ;"); // substitution with only one element with tag = value = " " 
   const I_CHAR *ACCOUNT_OWNER_ENTITY_TYPE                 = I_( "01" );
   const I_CHAR *REGISTRATION_AGENT_ENTITY_TYPE            = I_( "64" );

   const I_CHAR * const APPLICABLE_TO_ALL				   = I_( "*" );
   const I_CHAR * const RDSP_TAX_TYPE					   = I_( "RS" );
   const I_CHAR * const RDSP_BENEFICIARY				   = I_( "79" );
   const I_CHAR * const RDSP_PCG						   = I_( "80" );
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
   extern const long ERR_MULTIPLE_ACCT_OWNER;
   extern const long ERR_NO_ACCT_OWNER;
   extern const long ERR_MULTIPLE_ACCT_OWNER_NEEDED;
   extern const long ERR_MULTIPLE_ANNUITANT;
   extern const long ERR_MULTIPLE_SPOUSAL;
   extern const long ERR_NOMINEE_REQUIRED;
   extern const long ERR_PRIMARY_BENEF_PERCENT_SHOULD_ADD_UP_TO_100;
   extern const long ERR_SECONDARY_BENEF_PERCENT_SHOULD_ADD_UP_TO_100;
   extern const long ERR_MULTIPLE_NOMINEE_NOT_ALLOWED;
   extern const long ERR_ACCT_OWNER_SEQ_ONE_NEEDED;
   extern const long ERR_ACCT_OWNER_DUPLICATE;
   extern const long ERR_ID_TYPE_REQUIRED;
   extern const long ERR_DELETE_ENTITY;
   extern const long ERR_DELETE_RESP_ENTITY;
   extern const long ERR_EMPLOYER_ENTITY_MUST_BE_SETUP;


//   extern const long ERR_ACCOUNT_OWNER_ENTITY_MUST_BE_SETUP;
   extern const long ERR_RESP_BENEFICIARY_ENTITY_MUST_BE_SETUP;
   extern const long ERR_RESP_BENEFICIARY_ENTITY_IS_NOT_ALLOWED_FOR_THIS_TAX_TYPE;
   extern const long ERR_PARENT_ENTITY_SHOULD_BE_SETUP;
   extern const long ERR_ONLY_ONE_PARENT_ENTITY_IS_ALLOWED;
   extern const long ERR_RESP_DESIGNATED_INSTIT_ENTITY_SHOULD_BE_SETUP;
   extern const long ERR_ANNUITANT_ENTITY_SHOULD_BE_SETUP;
   extern const long ERR_ANNUITANT_ENTITY_IS_NOT_ALLOWED;
   extern const long ERR_SPOUSAL_CONTRIBUTOR_ENTITY_SHOULD_BE_SETUP;
//   extern const long ERR_ONLY_ONE_ACCOUNT_OWNER_ENTITY_IS_ALLOWED;
//   extern const long ERR_MULTIPLE_ACCOUNT_OWNER_ENTITY_SHOULD_SETUP;
   extern const long ERR_TRUSTEE_ENTITY_SHOULD_BE_SETUP;
   extern const long ERR_ITF_ENTITY_SHOULD_BE_SETUP;
   extern const long ERR_ESCROW_REPREZENTATIVE_ENTITY_MUST_BE_SETUP;
//   extern const long ERR_NOMINEE_OWNER_ENTITY_MUST_BE_SETUP;
   extern const long ERR_SECONDARY_BENEFICIARY_ENTITY_ONLY_ALLOWED_IF_PRIMARY_ENTITY_EXIST;
   extern const long ERR_W_ENTITY_AGE_OVER_69;
   extern const long ERR_E_ENTITY_AGE_OVER_69;

   extern const long ERR_WARN_ACCT_ASSIGNED_COMMITTEE_POWERATTNY;
   extern const long ERR_WARN_ENTIRE_ACCT_ASSIGNED;
   extern const long ERR_ENTIRE_ACCT_ASSIGNED;
   extern const long ERR_ASSIGNMENT_REDEEM_NOT_ALLOW;
   extern const long ERR_WARN_ASSIGNMENT_REDEEM_NOT_ALLOW;
   extern const long ERR_ESCROW_LOCKED_ALL_UNITS;
   extern const long ERR_ESCROW_LOCKED_PARTIAL_UNITS;
   extern const long ERR_NOMINEE_INVALID_FOR_ACCT_TYPE;
   extern const long ERR_WARN_PENDING_TRADE_EXISTS;
   extern const long ERR_WARN_PRIMARY_BENEFICIARY_NOT_ENTERED;
   extern const long ERR_WARN_SWP_STOP_FOR_ESCROW;
   extern const long ERR_ITF_ENTITY_SETUP_FOR_NON_ITF;
   extern const long ERR_ESCROW_ENTITY_SETUP_FOR_NON_ESCROW;
   extern const long ERR_RESP_ONLY_ONE_BENF_ALLOW;
   extern const long ERR_WARN_SCHEDULED_PAYMENT_NOT_ENTERED;
   extern const long ERR_WARN_ACCOUNT_TYPE_MUST_BE_INDIVIDUAL_SPOUSE;
   extern const long ERR_WARN_ACCOUNT_TYPE_MUST_BE_INDIVIDUAL_FOR_RIF_LRIF_ACCOUNT;
   extern const long ERR_DUPLICATE_SIN_DIFFERENT_ENTITY;
   extern const long WARN_DUPLICATE_SIN_DIFFERENT_ENTITY;

   extern const long WARN_ACCT_ASSIGNED_PAC_HOLDBACK;
   extern const long WARN_ACCT_ASSIGNED_CHEQUE_HOLDBACK;
   extern const long WARN_ACCT_ASSIGNED_CURATEL;
   extern const long ERR_ACCT_ASSIGNED_COURT_ORDER;
   extern const long WARN_ACCT_ASSIGNED_CONVERTED;
   extern const long WARN_ACCT_ASSIGNED_CQ;
   extern const long WARN_ACCT_ASSIGNED_VDAY;
   extern const long WARN_ACCT_ASSIGNED_MORTGAGE;
   extern const long WARN_ACCT_ASSIGNED_DPSP;
   extern const long WARN_ACCT_ASSIGNED_KEAN;
   extern const long WARN_ACCT_ASSIGNED_AMCU;
   extern const long WARN_ACCT_ASSIGNED_MEMO;
   extern const long ERR_ASSIGNMENT_TRANSFER_NOT_ALLOW;
   extern const long ERR_OTHER_ENTITY_TYPE_MUST_BE_SETUP;
   extern const long ERR_REMOVE_SPOUSE_LINK_BEFORE_DELETE_OWNER;
   extern const long ERR_FIELD_REQUIRED_PLS_ENTER;
   extern const long WARN_FIELD_REQUIRED_PLS_SELECT;
   extern const long ERR_RESP_ONLY_ACT_BENF_MISSING;
   extern const long ERR_SAME_ANNUITANT_AND_NOMINEE;
   extern const long ERR_DOC_STATUS_BLANK;
   extern const long ERR_MULTIPLE_SAME_CLEARING_PLATFORM_ENTITY_NOT_ALLOWED_FOR_ACCOUNT;
   extern const long ERR_ENITITY_NOT_ALLOWED_FOR_NON_RESP;
   extern const long ERR_ENITITY_NOT_ALLOWED_FOR_RESP_SIBLING_NOT_YES;
   extern const long ERR_SIN_NUMBER_SAME_ENTITY_1_ENTITY_2;
   extern const long WARN_SIN_NUMBER_SAME_ENTITY_1_ENTITY_2;
   extern const long ERR_CLEARING_ID_MUST_BELONG_TO_CLEARING_ENTITY;
   extern const long ERR_LOAN_NUMBER_FOR_ESCROW_ACCOUNT;
   extern const long WARN_LOAN_NUMBER_FOR_ESCROW_ACCOUNT;
   extern const long WARN_ACCT_ASSIGNED_CDIC_FULL_HOLD;
   extern const long WARN_ACCT_ASSIGNED_CDIC_PARTIAL_HOLD;
   extern const long WARN_ACCT_ASSIGNED_MI_FULL_HOLD;
   extern const long WARN_ACCT_ASSIGNED_MI_PARTIAL_HOLD;
   extern const long ERR_MULTIPLE_REGISTRATION_AGENT_ENTITIES; 
   extern const long ERR_NO_RA_SELECTED;
   extern const long ERR_NO_RA_MATCHING_TT;
   extern const long ERR_W_SIN_IS_MISSING;
   extern const long ERR_E_SIN_IS_MISSING;
   extern const long ERR_W_INVALID_SIN;
   extern const long ERR_E_INVALID_SIN;
   extern const long ERR_ID_TYPE_IS_REQUIRED_FOR_ENTITY_CATEGORY;
   extern const long WARN_ID_TYPE_IS_REQUIRED_FOR_ENTITY_CATEGORY;
   extern const long ERR_JURISDICTION_NOT_SAME_AS_SHRHLDR_JURISDICTION;
   extern const long WARN_JURISDICTION_NOT_SAME_AS_SHRHLDR_JURISDICTION;
   extern const long ERR_RDSP_BENEFICIARY_ENTITY_MUST_BE_SETUP;
   extern const long ERR_RDSP_BENEFICIARY_ENTITY_IS_NOT_ALLOWED_FOR_THIS_TAX_TYPE;
   extern const long ERR_RDSP_ONLY_ONE_BENF_ALLOW;
   extern const long WARN_RDSP_ONLY_ONE_BENF_ALLOW;
   extern const long ERR_RDSP_ONLY_TWO_PCG_ALLOW;
   extern const long WARN_RDSP_ONLY_TWO_PCG_ALLOW;
   extern const long ERR_RDSP_PCG_ENTITY_MUST_BE_SETUP;
   extern const long WARN_RDSP_PCG_ENTITY_MUST_BE_SETUP;
   extern const long ERR_RDSP_PCG_ENTITY_IS_NOT_ALLOWED_FOR_THIS_TAX_TYPE;
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const DUPLICATE_SIN; 
   extern CLASS_IMPORT I_CHAR * const ASSIGNMENT_REDEEM_NOT_ALLOW;
   extern CLASS_IMPORT I_CHAR * const LOAN_NUMBER_FOR_ESCROW_ACCOUNT;
   extern CLASS_IMPORT I_CHAR * const ID_TYPE_IS_REQUIRED_FOR_ENTITY_CATEGORY;
   extern CLASS_IMPORT I_CHAR * const JURISDICTION_NOT_SAME_AS_SHRHLDR_JURISDICTION;
   extern CLASS_IMPORT I_CHAR * const RDSP_ONLY_ONE_BENF_ALLOW;
   extern CLASS_IMPORT I_CHAR * const RDSP_ONLY_TWO_PCG_ALLOW;
   extern CLASS_IMPORT I_CHAR * const RDSP_PCG_ENTITY_MUST_BE_SETUP;
}

namespace IDS
{
   extern const I_CHAR * const LOAN_TYPE; 
   extern const I_CHAR * const LOAN_NUMBER;
}

namespace ENTITY_CATEGORY
{
   extern const I_CHAR * const INDIVIDUAL;
}

extern const I_CHAR * const NEW_PRFX;

//******************************************************************************
bool AccountEntityXref::getValueForTag( const DString& strBuffer, const I_CHAR* szTag, DString &strValue )
{
   TRACE_METHOD( CLASSNAME, GETVALUEFORTAG );

   //if tag found - remove value and insert new value
   DString strTag( szTag );
   strTag += I_( "=" );

   DString::size_type iPos = strBuffer.find( szTag );

   if( iPos != std::string::npos )
   {
      //tag exists
      DString::size_type iTagLen = strTag.size();
      DString::size_type iSemicolon = strBuffer.find( ';', iPos + iTagLen );
      if( iSemicolon == std::string::npos )
      {
         assert(0);
         return(false);
      }
      strValue = strBuffer.substr( iPos + iTagLen, iSemicolon - (iPos + iTagLen) );
      return(true);
   }
   return(false);
}

//******************************************************************************
void AccountEntityXref::buildPartialKeyForRetrievingEntity( DString& strKey, 
                                                            const DString& AccountNum,
                                                            const DString& EntityType,
                                                            const DString& SeqNumber )
{
   DString tempAccountNum = AccountNum;
   DString tempEntityType = EntityType;
   DString tempSeqNumber = SeqNumber;

   strKey = NULL_STRING;
   //adding the account number to the key
   tempAccountNum.stripLeading( '0' );
   tempAccountNum.strip();
   tempAccountNum = tempAccountNum.padLeft( 20, '0' );
   addIDITagValue( strKey, ACCOUNT_NUMBER_FIELD, tempAccountNum );

   //adding the entity type to the key
   tempEntityType.strip();
   addIDITagValue( strKey, ENTITY_TYPE_FIELD, tempEntityType );

   //adding the entity sequence to the key
   tempSeqNumber.stripLeading( '0' );
   tempSeqNumber = tempSeqNumber.padLeft( 4, '0' );
   addIDITagValue( strKey, ENTITY_SEQ_NUM_FIELD, tempSeqNumber );

}

//******************************************************************************
void AccountEntityXref::buildPartialKeyForAccount( DString &partialKey,
                                                   const DString& AccountNum )
{
   partialKey = NULL_STRING;
   DString tempAccountNum = AccountNum;
   //adding the account number to the key
   tempAccountNum.stripLeading( '0' );
   tempAccountNum.strip();
   tempAccountNum = tempAccountNum.padLeft( 20, '0' );
   addIDITagValue( partialKey, ACCOUNT_NUMBER_FIELD, tempAccountNum );
}

//******************************************************************************
void AccountEntityXref::buildPartialKeyForEntityType( DString &partialKey,
                                                      const DString& EntityType )
{
   partialKey = NULL_STRING;
   DString tempEntityType = EntityType;
   //adding the account number to the key
   //adding the entity type to the key
   tempEntityType.strip();
   addIDITagValue( partialKey, ENTITY_TYPE_FIELD, tempEntityType );
}

//******************************************************************************
void AccountEntityXref::buildPartialKeyForSequenceNumber( DString& partialKey,
                                                          const DString& SequenceNumber )
{
   partialKey = NULL_STRING;
   DString tempSeqNumber = SequenceNumber;

   //adding the entity sequence to the key
   tempSeqNumber.stripLeading( '0' );
   tempSeqNumber = tempSeqNumber.padLeft( 4, '0' );
   addIDITagValue( partialKey, ENTITY_SEQ_NUM_FIELD, tempSeqNumber );
}

//******************************************************************************
void AccountEntityXref::buildPartialKeyForEntityId( DString& partialKey,
                                                    const DString& EntityId )
{
   partialKey = NULL_STRING;
   DString tempEntityId = EntityId;

   //adding the entity id to the key
   tempEntityId.stripLeading( '0' );
   addIDITagValue( partialKey, ENTITY_ID_FIELD, tempEntityId );
}

//******************************************************************************
void AccountEntityXref::buildKey( DString &strKey,
                                  const DString& AccountNum,
                                  const DString& EntityType,
                                  const DString& SeqNumber,
                                  const DString& EntityId,
                                  const DString& NewCount)
{
   DString tempAccountNum = AccountNum;
   DString tempEntityId = EntityId;
   DString tempEntityType = EntityType;
   DString tempSeqNumber = SeqNumber;

   strKey = NULL_STRING;
   //adding the account number to the key
   tempAccountNum.stripLeading( '0' );
   tempAccountNum.strip();
   tempAccountNum = tempAccountNum.padLeft( 20, '0' );
   addIDITagValue( strKey, ACCOUNT_NUMBER_FIELD, tempAccountNum );

   //adding the entity type to the key
   tempEntityType.strip();
   addIDITagValue( strKey, ENTITY_TYPE_FIELD, tempEntityType );

   //adding the entity sequence to the key
   tempSeqNumber.stripLeading( '0' );
   tempSeqNumber = tempSeqNumber.padLeft( 4, '0' );
   addIDITagValue( strKey, ENTITY_SEQ_NUM_FIELD, tempSeqNumber );

   //adding the entity id to the key
   tempEntityId.stripLeading( '0' );
   addIDITagValue( strKey, ENTITY_ID_FIELD, tempEntityId );
   // add account for new object.
   if( NULL_STRING != NewCount )
   {
      addIDITagValue( strKey, NEW_COUNT_TAG, NewCount );
   }
}

//******************************************************************************
void AccountEntityXref::getStrKey (DString &strKey, const BFData *data)
{
   DString strTemp;

   if (flg_where_used)
   {

      DString accNumber, entityType, entitySeq, entityId;

      data->getElementValue( ifds::AccountNum, accNumber );
      data->getElementValue( ifds::EntityType, entityType );
      data->getElementValue( ifds::EntityTypeSeq, entitySeq );
      data->getElementValue( ifds::EntityId, entityId );
      AccountEntityXref::buildKey( strKey, accNumber, entityType, entitySeq, entityId );
      //AccountEntityXref::buildKey( strKey, accNumber, entityType, entitySeq, _entityId );
   }
   else if (data)
   {
      DString entityType, 
         entitySeq, 
         entityId;

      data->getElementValue (ifds::EntityType, entityType);
      data->getElementValue (ifds::SeqNumber, entitySeq);
      data->getElementValue (ifds::EntityId, entityId);

      AccountEntityXref::buildKey (strKey, _accountNum, entityType, entitySeq, entityId);
   }
   else
   {
      DString dstrCount = asString (getCurrentCount());
      AccountEntityXref::buildKey (strKey, _accountNum, _entityType, _entitySeq, _entityId, dstrCount);
   }
}

//****************************************************************************
AccountEntityXref::AccountEntityXref( BFAbstractCBO &parent ) 
:  MFCanBFCbo( parent ),m_bRefresh(false),
flg_where_used( false ),_iNewCount( 0 )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   setObjectAsList( );
   setupEscrowReasons();
}


//******************************************************************************
AccountEntityXref::~AccountEntityXref()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY AccountEntityXref::AEXrefCreateObjectForEachRepeat( const BFData &data )
{
   try
   {
      if( data.getRepeatCount() > 0 )
      {
         int cRepeats = data.getRepeatCount();
         BFCBO* pObj = NULL;
         BFObjectKey objKey;

         //for each repeat, call the derived class' doCreateObject
         for( int i = 0; i < cRepeats; i++ )
         {
            const BFData& rptData = data.getRepeat( i );
            doCreateObject( rptData, pObj );
            //if the object has already been created ( meaning pObj = NULL, set by the doCreateObject )
            //do not set it again in the list
            if( pObj )
            {
               getKey( objKey, &rptData );
               setObject( objKey, pObj );
               pObj->clearUpdatedFlags( BF::HOST );
               pObj->setAllFieldsValid( BF::HOST );
            }
         }
      }
   }
   catch( ... )
   {
      throw;
   }
   return(NO_CONDITION);
}

//******************************************************************************
SEVERITY AccountEntityXref::PopulateAccountOwner( const BFDataGroupId& idDataGroup,
                                                  const DString& EntityId,
                                                  const DString& InputAcctNum,
                                                  const DString& InputShrNum,
                                                  const DString& NumEntry )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "PopulateAccountOwner" ) );

   SEVERITY sev = SEVERE_ERROR;
   DString tempEntity( EntityId );
   DString tempAccount( InputAcctNum );

   tempEntity.stripLeading( '0' );
   tempAccount.stripLeading( '0' );

   if( tempEntity != NULL_STRING )
   {
      OBJ_USAGE_MAP_ITER iter;
      if( ( iter = _entityMap.find( tempEntity ) ) != _entityMap.end() )
      {
         if( (*iter).second == ACCOUNT_OWNER )
            return(GETCURRENTHIGHESTSEVERITY());
      }
   }

   if( tempAccount != NULL_STRING )
   {
      OBJ_USAGE_MAP_ITER iter;
      if( ( iter = _accountMap.find( tempAccount ) ) != _accountMap.end() )
      {
         return(GETCURRENTHIGHESTSEVERITY());
      }
   }

   //if input account number was provided, get the account from the repository
   //we should call this method only with valid account numbers
   if( !tempAccount.empty() )
   {
      MFAccount* pMFAccount;
      if( getWorkSession().getMFAccount( idDataGroup, tempAccount, pMFAccount )<=WARNING )
         PopulateEntitiesList( idDataGroup, tempAccount );
   }
   //else make the view call
   else
   {
      MFAccountList mfAccountList( *this );
      if( mfAccountList.init( EntityId, InputAcctNum, InputShrNum, NumEntry ) <= WARNING )
      {

         BFObjIter iterMFAccountList( mfAccountList, BF::HOST );

         flg_where_used = false;
         while( !iterMFAccountList.end() )
         {

            MFAccount* pMFAcc = static_cast <MFAccount *>( iterMFAccountList.getObject() );

            DString dstrAccountNum;
            pMFAcc->getField( ifds::AccountNum, dstrAccountNum, BF::HOST );

            //create the list of entities for each account
            PopulateEntitiesList( idDataGroup, dstrAccountNum );

            ++iterMFAccountList;
         }
         _entityMap.insert( std::make_pair( tempEntity, ACCOUNT_OWNER ) );
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AccountEntityXref::PopulateEntitiesList( const BFDataGroupId& idDataGroup,
                                                  const DString& AccountNum,                              
                                                  const DString& dstrTrack,
                                                  const DString& dstrPageName                                     
                                                )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "PopulateEntitiesList" ) );

   DString dstrAccountNum( AccountNum );
   if (dstrAccountNum.stripLeading( '0' ).empty())
      return GETCURRENTHIGHESTSEVERITY();

   if( _accountMap.find( dstrAccountNum ) != _accountMap.end() )
   {
      return(GETCURRENTHIGHESTSEVERITY());
   }

   flg_where_used = false;

   MFAccount* pMFAcc;
   getWorkSession().getMFAccount( idDataGroup, dstrAccountNum, pMFAcc );

   BFData queryData(ifds::DSTC0050_REQ);
   BFData *response = new BFData(ifds::DSTC0050_VW);

   _accountNum = dstrAccountNum;

   DString mgmtCoIdOut;
   queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   queryData.setElementValue( ifds::AccountNum, dstrAccountNum  );
   queryData.setElementValue( ifds::Track, dstrTrack );
   queryData.setElementValue( ifds::Activity, dstrPageName );

   if( BFDataBroker::getInstance()->receive( DSTC_REQUEST::ENTITY, 
                                             queryData, 
                                             *response, 
                                             DSTCRequestor( getSecurity() ) ) <= WARNING )
   {
      attachDataObject( *response, true, false );
      AEXrefCreateObjectForEachRepeat( *response);

      DString temp( _accountNum );
      temp.stripLeading( '0' );
      _accountMap.insert( std::make_pair( temp, ACCOUNT_OWNER ) );
   }
   else
   {
      delete response;
      response = NULL;
   }
   SetChildrenSpousalNameSubSet( idDataGroup );

   setRESPSelectableFieldSubSet( RESP_PCG_INDIV_ENTITY_TYPE, NULL_STRING, idDataGroup );
   setRESPSelectableFieldSubSet( RESP_PCG_INST_ENTITY_TYPE, NULL_STRING, idDataGroup );
   setRESPSelectableFieldSubSet( PARENT_GUARDIAN_ENTITY_TYPE, NULL_STRING, idDataGroup );
   setRESPSelectableFieldSubSet( RESP_DESIGNATED_INSTIT_ENTITY_TYPE, NULL_STRING, idDataGroup );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AccountEntityXref::PopulateWhereUsed( const DString &EntityId, 
                                               const DString &EntityType,
                                               const DString &dstrTrack,
                                               const DString &dstrPageName,
                                               const DString &retSameCIFAcct /*=I_("N")*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "PopulateWhereUsed()" ) );

   DString temp( EntityId );
   temp.stripLeading( '0' );

   OBJ_USAGE_MAP_ITER iter;
   if( ( iter = _entityMap.find( temp ) ) != _entityMap.end() )
   {
      if ((*iter).second == WHERE_USED)
         return(GETCURRENTHIGHESTSEVERITY());
   }

   DString dstrAccountNum;
   BFData queryData(ifds::DSTC0061_REQ);
   BFData *response = new BFData(ifds::DSTC0061_VW);

   flg_where_used = true;
   _entityId = temp;

   DString mgmtCoIdOut;
   queryData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   queryData.setElementValue (ifds::EntityId, EntityId); 
   queryData.setElementValue (ifds::EntityType, EntityType); 
   queryData.setElementValue (ifds::RetSameCIFAcct, retSameCIFAcct);
   queryData.setElementValue (ifds::Track, dstrTrack);
   queryData.setElementValue (ifds::Activity, dstrPageName);


   if( BFDataBroker::getInstance()->receive( DSTC_REQUEST::WHERE_USED, 
                                             queryData, 
                                             *response, 
                                             DSTCRequestor( getSecurity() ) ) <= WARNING )
   {
      attachDataObject( *response, true, false );
      AEXrefCreateObjectForEachRepeat( *response );

      _entityMap.insert( std::make_pair( temp, WHERE_USED ) );
   }
   else
   {
      delete response;
      response = NULL;
   }

   flg_where_used = false;
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AccountEntityXref::UnlinkEntity( const DString& AccountNum,
                                          const DString& EntityId,
                                          const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "UnlinkEntity" ) );

   DString tmpEntityId( EntityId );
   DString tmpAccountNum( AccountNum );
   DString partialKey;
   SEVERITY severity = SEVERE_ERROR;

   tmpEntityId.stripLeading( '0' );
   tmpAccountNum.stripLeading( '0' );
   tmpAccountNum.strip();
   tmpAccountNum = tmpAccountNum.padLeft( 20, '0' );
   addIDITagValue( partialKey, ACCOUNT_NUMBER_FIELD, tmpAccountNum );

   BFObjIter bfIter( *this, idDataGroup, true );

   bfIter.positionByKey( partialKey );
   for( ; !bfIter.end(); ++bfIter )
   {
      DString key = bfIter.getStringKey();
      DString strEntityId;
      DString entityTag;

      I_CHAR *temp = const_cast < I_CHAR* > ( key.c_str() );
      do
      {
         temp = parseIdiString( temp, entityTag, strEntityId );
      } while( entityTag != ENTITY_ID_FIELD && temp );

      if( strEntityId == tmpEntityId )
      {
         severity = deleteObject( key, idDataGroup );

         DString tmpEntityType;
         bfIter.getObject()->getField( ifds::EntityType, tmpEntityType, idDataGroup, false );

         if ( tmpEntityType == RESP_PCG_INDIV_ENTITY_TYPE || tmpEntityType == RESP_PCG_INST_ENTITY_TYPE ||
              tmpEntityType == PARENT_GUARDIAN_ENTITY_TYPE || tmpEntityType == RESP_DESIGNATED_INSTIT_ENTITY_TYPE )
         {
            setRESPSelectableFieldSubSet( tmpEntityType, NULL_STRING, idDataGroup );
         }

         break;
      }
   }

   SetChildrenSpousalNameSubSet( idDataGroup );

   return(GETCURRENTHIGHESTSEVERITY());
}

//*********************************************************************************************
SEVERITY AccountEntityXref::GetEntityIdForAccountOwnerSequence1( const DString& accountNum, 
                                                                 const BFDataGroupId& idDataGroup, DString& entityId )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "GetEntityIdForAccountOwnerSequence1" ) );

   PopulateEntitiesList(idDataGroup, accountNum);
   BFObjIter iterAccount( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );
   DString strKey;

   buildPartialKeyForRetrievingEntity( strKey, accountNum, I_( "01" ), I_( "1" ) );
   if( iterAccount.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, strKey ) )
   {
      if( !iterAccount.end() )
      {
         iterAccount.getObject()->getField( ifds::EntityId, entityId, idDataGroup ); 
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//*********************************************************************************************
SEVERITY AccountEntityXref::GetAcctOwnerEntityInfo( const DString& accountNum, 
                                                    const DString& seqNumber, 
                                                    const BFDataGroupId& idDataGroup, 
                                                    DString& entityId,
                                                    DString& firstName,
                                                    DString& lastName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "GetEntityIds" ) );

   PopulateEntitiesList(idDataGroup, accountNum);
   BFObjIter iterAccount( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );
   DString strKey;
   DString strFirstName, strLastName;

   buildPartialKeyForRetrievingEntity( strKey, accountNum, I_( "01" ), seqNumber);

   if (iterAccount.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, strKey))
   {
      if (!iterAccount.end())
      {
         iterAccount.getObject()->getField (ifds::EntityId, entityId, idDataGroup); 
         iterAccount.getObject()->getField (ifds::FirstName, firstName, idDataGroup);
         iterAccount.getObject()->getField ( ifds::LastName, lastName, idDataGroup);
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************************
int AccountEntityXref::GetNumberOfAccountHolders( const DString& AccountNum, const BFDataGroupId& idDataGroup )
{
   BFObjIter iterAccountEntityXrefOut( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );
   DString strKey, str;
   int count = 0;

   buildPartialKeyForAccount( str, AccountNum );
   strKey += str;
   buildPartialKeyForEntityType( str, I_( "01" ) );
   strKey += str;
   for( iterAccountEntityXrefOut.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, strKey );
      !iterAccountEntityXrefOut.end(); ++iterAccountEntityXrefOut, ++count )
      ;
   return(count);
}
//******************************************************************************
int AccountEntityXref::GetNumberOfEntityByType( 
      const DString& dstrAccountNum, 
      const DString& dstrEntityType, 
      const BFDataGroupId& idDataGroup )
{
   BFObjIter iterAccountEntityXrefOut( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );
   DString strKey, str;
   int count = 0;

   buildPartialKeyForAccount( str, dstrAccountNum );
   strKey += str;
   buildPartialKeyForEntityType( str, dstrEntityType );
   strKey += str;
   for( iterAccountEntityXrefOut.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, strKey );
      !iterAccountEntityXrefOut.end(); 
      ++iterAccountEntityXrefOut, ++count )
      ;
   return count;
}
//******************************************************************************
SEVERITY AccountEntityXref::GetAccountEntityXrefObjectByType(  
      const DString& dstrAccountNum, 
      const DString& dstrEntityType, 
      const int& index, 
      const BFDataGroupId& idDataGroup, 
      AccountEntityXrefObject*& pAccountEntityXrefObject)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "GetAccountEntityXrefObjectByType" ) );
   BFObjIter iterAccountEntityXrefOut( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );
   DString strKey, str;

   int current = 0;

   buildPartialKeyForAccount( str, dstrAccountNum );
   strKey += str;
   buildPartialKeyForEntityType( str, dstrEntityType );
   strKey += str;
   
   for( iterAccountEntityXrefOut.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, strKey );
      !iterAccountEntityXrefOut.end(); 
      ++iterAccountEntityXrefOut, ++current )
   {
      if(current == index)
         pAccountEntityXrefObject = dynamic_cast<AccountEntityXrefObject*>(iterAccountEntityXrefOut.getObject());
   }

   return GETHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AccountEntityXref::GetNextSeqNumber( const BFDataGroupId& idDataGroup,
                                              const DString& AccountNum,
                                              const DString& entType,
                                              DString& seqNumber )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "GetNextSeqNumber" ) );

   BFObjIter iterAccountEntityXrefOut( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );
   DString accNum, entityType, searchKey;
   buildPartialKeyForAccount( accNum, AccountNum );
   buildPartialKeyForEntityType( entityType, entType ); // Account owners
   searchKey = accNum;// + entityType;
   typedef std::list<int >   SeqNum;
   SeqNum seqNum;
   SeqNum::iterator iter;
   int seq = 0;
   DString temp;
   if( iterAccountEntityXrefOut.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey ) )
   {
      do
      {
         DString dstrEntityType;
         ( iterAccountEntityXrefOut.getObject() )->getField( ifds::SeqNumber, temp, idDataGroup, true );
         ( iterAccountEntityXrefOut.getObject() )->getField( ifds::EntityType, dstrEntityType, idDataGroup, false );
         if( dstrEntityType == entType )
            seqNum.insert(seqNum.begin(), asInteger( temp));
      }
      while( ++iterAccountEntityXrefOut );
      seqNum.sort();  
      bool bFound;
      do
      {
         bFound = false;
         seq++;  
         for( iter = seqNum.begin();iter != seqNum.end();++iter )
         {
            if( seq == *iter )
            {
               bFound = true;
               break;
            }
         }   
      }while( bFound );   

   }
   if( seq == 0 )seq = 1;
   seqNumber = asString( seq );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AccountEntityXref::LinkEntity( const DString& AccountNum, const DString& EntityType, 
                                        const DString& SeqNumber, const DString& EntityId, 
                                        const BFDataGroupId& idDataGroup, 
                                        AccountEntityXrefObject*& pAccountEntityXrefObject, 
                                        bool isCopyEntity /*=false*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "LinkEntity" ) );

   DString strKey;
   _entitySeq = NULL_STRING;
   if( EntityType == NULL_STRING )
      _entityType = ACCOUNTHOLDER_ENTITY_TYPE; // new entities -> default to account owners
   else
      _entityType = EntityType;
   if( SeqNumber == NULL_STRING )
      if( isCopyEntity )
         GetNextSeqNumber( idDataGroup, AccountNum, EntityType, _entitySeq );
      else
         GetNextSeqNumber( idDataGroup, AccountNum, ACCOUNTHOLDER_ENTITY_TYPE, _entitySeq );
   else
      _entitySeq = SeqNumber;

   _accountNum = AccountNum;
   _entityId = EntityId;
   //build key
   getStrKey( strKey, NULL );
   BFObjIter bfIter( *this, idDataGroup, false, BFObjIter::ITERTYPE::ALL, false );
   bfIter.begin();
   bool found = bfIter.positionByKey( strKey );
   if( found )
   {
      BFObjectKey objKey = bfIter.getKey();
      if( objKey.getActivity() == OBJ_ACTIVITY_DELETED )
      {
         bfIter.removeObjectFromMap( false );   // the new object that we are trying to add has been 
                                                // deleted with the same group id. We will just remove
                                                // the entry on the map with OBJ_ACTIVITY_DELETED
         pAccountEntityXrefObject = NULL;
         return(GETCURRENTHIGHESTSEVERITY()); 
      }
   }

   flg_where_used = false;
   Entity* pEntity;

   if( getWorkSession().getEntity( idDataGroup, _entityId, pEntity ) <= WARNING )
   {
      pAccountEntityXrefObject = new AccountEntityXrefObject( *this );
      if( pAccountEntityXrefObject->init( idDataGroup ) <= WARNING )
      {
         //set the data elements accordingly
         pAccountEntityXrefObject->setObjectNew();
         pAccountEntityXrefObject->setCountNum (getCurrentCount());
         pAccountEntityXrefObject->setInitialStrKey (strKey);
         setObject (pAccountEntityXrefObject, strKey, OBJ_ACTIVITY_ADDED, idDataGroup);

         pAccountEntityXrefObject->setField( ifds::AccountNum, _accountNum, idDataGroup );
         pAccountEntityXrefObject->setField( ifds::EntityId, _entityId, idDataGroup );
         pAccountEntityXrefObject->setField( ifds::EntityType, _entityType, idDataGroup );
         pAccountEntityXrefObject->setField( ifds::SeqNumber, _entitySeq, idDataGroup );
         pAccountEntityXrefObject->initWithDefaultValues( idDataGroup );
         pAccountEntityXrefObject->clearUpdatedFlags( idDataGroup );

         //if the account number is new signal that we do not need to do a view call for it
         MFAccount * pMFAccount;
         DString temp( _accountNum );
         temp.strip().stripLeading( '0' );

         getWorkSession().getMFAccount( idDataGroup , temp, pMFAccount );
         if( _accountMap.find( temp) == _accountMap.end() && pMFAccount && pMFAccount->isNew() )
            _accountMap.insert( std::make_pair( temp, ACCOUNT_OWNER ) );

         if( _entityType == RESP_BENEFICIARY_ENTITY_TYPE )
         {
            setRESPSelectableFieldSubSet( RESP_PCG_INDIV_ENTITY_TYPE, NULL_STRING, idDataGroup );
            setRESPSelectableFieldSubSet( RESP_PCG_INST_ENTITY_TYPE, NULL_STRING, idDataGroup );
            setRESPSelectableFieldSubSet( PARENT_GUARDIAN_ENTITY_TYPE, NULL_STRING, idDataGroup );
            setRESPSelectableFieldSubSet( RESP_DESIGNATED_INSTIT_ENTITY_TYPE, NULL_STRING, idDataGroup );
         }
      }
   }

   SetChildrenSpousalNameSubSet( idDataGroup );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AccountEntityXref::init()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   _bEscrowBand = ( getWorkSession().hasReadPermission( UAF::ESCROW_BAND ) ||
                    getWorkSession().hasReadPermission( UAF::ASSIGNEE_ENTITY_TYPE_SETUP) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//support for refresh
//******************************************************************************
SEVERITY AccountEntityXref::doPreClearFields()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doPreClearFields" ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AccountEntityXref::refresh( bool bNewObject )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "reInit" ) );

   std::set< DString > setAccountNumNeedToRefresh;
   DString accountNum;

   BFObjIter bfIter( *this, BF::HOST, false, BFObjIter::ITERTYPE::ALL, false );
   bfIter.begin();
   m_bRefresh = true;
   // delete obj marked as deleted or updated
   // remember the account that need to be refreshed
   
   while( !bfIter.end() )
   {
      BFObjectKey objKey = bfIter.getKey();
      if( objKey.getActivity() == OBJ_ACTIVITY_DELETED )
      {
         bfIter.getObject()->getField( ifds::AccountNum, accountNum, BF::HOST, false );
         accountNum.stripLeading( '0' );
         setAccountNumNeedToRefresh.insert(accountNum);
         bfIter.removeObjectFromMap();
      }
      else if( bfIter.getObject()->isUpdatedForDataGroup( BF::HOST, false ) )
      {
         bfIter.getObject()->getField( ifds::AccountNum, accountNum, BF::HOST, false );
         accountNum.stripLeading( '0' );
         setAccountNumNeedToRefresh.insert(accountNum);
         bfIter.removeObjectFromMap();
      }
      else
         ++bfIter;
   }

   std::set< DString >::iterator iter = setAccountNumNeedToRefresh.begin();
   MFAccount *pMFAccount;

   // update accounts
   while( iter != setAccountNumNeedToRefresh.end() )
   {
      //retrieve the host account number
      getWorkSession().getHostAccountNum( *iter, accountNum );
      accountNum.stripLeading( '0' );
      //we do not have anything from host,
      //we probably had an entity added, not a new account
      if( accountNum == NULL_STRING )
         accountNum = *iter;

      getWorkSession().getMFAccount( BF::HOST, accountNum, pMFAccount );
      pMFAccount->refreshDataObject();
      //erase the old entry in map and populate the cross-reference with the entities for the 
      //new account number
      _accountMap.erase( *iter );
      PopulateEntitiesList( BF::HOST, accountNum );
      ++iter;
   }


   /*
    BFObjIter bfIter( *this, BF::HOST, false, BFObjIter::ITERTYPE::ALL, false );
 
    bfIter.begin();
    while( !bfIter.end() )
    {
       BFObjectKey objKey = bfIter.getKey();
       if( objKey.getActivity() == OBJ_ACTIVITY_DELETED )
       {
          bfIter.removeObjectFromMap();
       }
       else if( ( objKey.getActivity() == OBJ_ACTIVITY_NONE && bfIter.getObject()->isUpdatedForDataGroup( BF::HOST, false ) ) || 
                  objKey.getActivity() == OBJ_ACTIVITY_ADDED )
       {
          //create the list of entities for each account( any existent acct-entity pair in the list won't be replaced );
          //it is done this way because there is no view that retrieves only one acct-entity specific pair
          DString accountNum, entityId, tmpAccountNum;
          bfIter.getObject()->getField( DBR::AccountNum, accountNum, BF::HOST, false );
          accountNum.stripLeading( '0' );
          do
          {
             if( objKey.getActivity() == OBJ_ACTIVITY_DELETED || objKey.getActivity() == OBJ_ACTIVITY_ADDED ||
                 ( objKey.getActivity() == OBJ_ACTIVITY_NONE && bfIter.getObject()->isUpdatedForDataGroup( BF::HOST, false ) ) )
                bfIter.removeObjectFromMap();
             else
                ++bfIter;
             if( bfIter.end() )
                break;
             bfIter.getObject()->getField( DBR::AccountNum, tmpAccountNum, BF::HOST, false );
             tmpAccountNum.stripLeading( '0' );
          }
          while( tmpAccountNum == accountNum );
          
          MFAccount *pMFAccount = NULL;
          DString hostAccountNum;
          
          //retrieve the host account number
          getWorkSession().getHostAccountNum( accountNum, hostAccountNum );
          hostAccountNum.stripLeading( '0' );
          //we do not have anything from host,
          //we probably had an entity added, not a new account
          if( hostAccountNum == NULL_STRING ) 
          {
             hostAccountNum = accountNum;
          }
          getWorkSession().getMFAccount( BF::HOST, hostAccountNum, pMFAccount );
          //erase the old entry in map and populate the cross-reference with the entities for the 
          //new account number
          _accountMap.erase( accountNum );
          PopulateEntitiesList( BF::HOST, hostAccountNum );
 
          if( !bfIter.end() )
          {
             DString key = bfIter.getStringKey();
             bfIter.positionByKey( key );
          }
          else
             break;
       }
       else
       {
          ++bfIter;
          continue;
       }
    }
   */
   m_bRefresh = false;
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AccountEntityXref::doCreateObject (const BFData& data, BFCBO *&pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_ ("doCreateObject"));

   DString key;

   getStrKey (key, &data);
   const DString constKey (key);

   BFAbstractCBO* pBFCBO = getObject (constKey, BF::HOST);
   AccountEntityXrefObject* pAccountEntityXrefObject;

   if (!pBFCBO)
   {
      pAccountEntityXrefObject = new AccountEntityXrefObject (*this);
      if (!flg_where_used)
      {
         pAccountEntityXrefObject->setField (ifds::AccountNum, _accountNum, BF::HOST) ;
      }
      else
      {
         DString entityId;

         data.getElementValue (ifds::EntityId, entityId);
         entityId.strip ();
         entityId.stripLeading ('0');
         //pAccountEntityXrefObject->setField (ifds::EntityId, _entityId, BF::HOST);
         pAccountEntityXrefObject->setField (ifds::EntityId, entityId, BF::HOST);
      }

      pAccountEntityXrefObject->init (key, data, flg_where_used);
      pObjOut = pAccountEntityXrefObject;
   }
   else
   {
      pAccountEntityXrefObject = dynamic_cast < AccountEntityXrefObject* > (pBFCBO);
      pAccountEntityXrefObject->init (key, data, flg_where_used);
      pObjOut = NULL;
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AccountEntityXref::doCreateNewObject( BFCBO*& pBase, DString& strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   AccountEntityXrefObject* pAccountEntityXrefObject;
   BFData data1( ifds::DSTC0050_VW );
   BFData *data = new BFData( ifds::DSTC0050_VWRepeat_Record );

   pAccountEntityXrefObject = new AccountEntityXrefObject( *this );

   DString strEntityId;
   Entity* pEntity;

   getWorkSession().getNewEntity( idDataGroup, pEntity );
   pEntity->getEntityId( strEntityId );
   data->setElementValue( ifds::EntityId, strEntityId, false, false );
   pAccountEntityXrefObject->setField( ifds::EntityId, strEntityId, idDataGroup );
   pAccountEntityXrefObject->init( strEntityId, *data, true, true );
   strKey = strEntityId;
   pBase = pAccountEntityXrefObject;
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void AccountEntityXref::doCommitDataGroup( const BFDataGroupId& idDataGroup )
{
/*
   BFObjIter bfIter( *this, idDataGroup, false, BFObjIter::ITERTYPE::ALL, false );
   bfIter.begin();
   while( !bfIter.end() )
   {
      if( bfIter.getKey().getDataGroupId() == idDataGroup )
      {
         DString newStrKey;

         bfIter.getObject()->getField( ifds::AccountNum, _accountNum, idDataGroup, false );
         bfIter.getObject()->getField( ifds::EntityType, _entityType, idDataGroup, false );
         bfIter.getObject()->getField( ifds::SeqNumber, _entitySeq, idDataGroup, false );
         bfIter.getObject()->getField( ifds::EntityId, _entityId, idDataGroup, false );
         getStrKey( newStrKey, NULL );
         ( dynamic_cast < AccountEntityXrefObject * > ( bfIter.getObject() ) )->setInitialStrKey( newStrKey );
         const BFObjectKey & oldKey = bfIter.getKey();
         if( oldKey.getStringKey() != newStrKey )
            setObject( bfIter.getObject(), newStrKey, oldKey.getActivity(), idDataGroup, oldKey.getType() );
         //insert the account number in the map if it doesn't exist
         if( _accountMap.find( _accountNum ) == _accountMap.end() )
         {
            DString temp( _accountNum );
            temp.stripLeading( '0' );

            _accountMap.insert( std::make_pair( temp, ACCOUNT_OWNER ) );
         }
      }
      ++bfIter;
   }
*/
}

//******************************************************************************
bool AccountEntityXref::getAvailablePercentForBenef( const DString& benefType,
                                                     DString& percent,
                                                     const BFDataGroupId& idDataGroup ) 
{
   double tmpDouble = 0;
   bool avail = false, flg_benef_type_exist = false;

   percent = NULL_STRING;
   BFObjIter bfIter( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED, false, true );
   DString searchKey, accNum( currAccountNum );
   buildPartialKeyForAccount( searchKey, accNum );
   if( bfIter.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey ) )
   {
      DString entityType, str;
      while( !bfIter.end() )
      {
         bfIter.getObject()->getField( ifds::EntityType, entityType, idDataGroup );
         if( entityType == benefType )
         {
            flg_benef_type_exist = true;
            bfIter.getObject()->getField( ifds::BenPercentage, str, idDataGroup );
            tmpDouble += DSTCommonFunctions::convertToDouble( str );
         }
         ++bfIter;
      }
   }

   if( tmpDouble > 100 || !flg_benef_type_exist )
   {
      if( !flg_benef_type_exist )
         tmpDouble = 100;
      else
         tmpDouble = 0;
      percent = DSTCommonFunctions::doubleToDString( ifds::BenPercentage, tmpDouble );
      avail = false;
   }
   else
   {
      tmpDouble = 100 - tmpDouble;
      percent = DSTCommonFunctions::doubleToDString( ifds::BenPercentage, tmpDouble );
      avail = true;
   }


   BFDataField::formatValue( ifds::BenPercentage, percent, false );
   return(avail);
}

//******************************************************************************
bool AccountEntityXref::verifyDuplicityOfAcctOwnerEntities( const DString& entityId,
                                                            const int current_index )
{
   int nrElem = acctOwnerEntities.size();
   if( entityId == NULL_STRING )
   {
      for( int i = 0; i < nrElem; i++ )
      {
         if( verifyDuplicityOfAcctOwnerEntities( acctOwnerEntities[ i ], i ) )
            return(true); // duplicate found
      }
   }
   else
   {
      assert( current_index != -1 );
      for( int i = 0; i < nrElem; i++ )
      {
         if( i != current_index && acctOwnerEntities[ i ] == entityId )
            return(true); // duplicate found
      }
   }

   return(false);
}

//******************************************************************************
SEVERITY AccountEntityXref::validateOneAccount( const DString& strAcctNum, const BFDataGroupId& idDataGroup ) 
{
   //Rule· When adding a new account or modifing to/from TaxType-4 to '9' or 'M' 
   //   user must update RESP entities ('50'-RESP beneficiary, '52'-RESP Designated 
   //   Institution and '51'- Parent/Legal Guardian if RESP Beneficiary is below  
   //   19 years old or RESP beneficiary's Date of Birth is unknown). At least one 
   //   Entity Type '50' must be entered. If Entitytype '51' is not setup, warning 
   //   must be issued: 'Parent/Legal Guardian has not been setup' if RESP 
   //   beneficiary is below 19 years old or Beneficiary's Date of Birth is unknown,
   //   If entity '52' is not setup, warning must be issued 'Designation Institutioin 
   //   has not been setup'.
   //   
   //   vGuardian =  Entity-Identity.DofB = ? OR Entity-Identity.DofB  >  vGuardian-date1.
   //   If vGuardian is Yes it means, Parent/Legal Guardian (EntityType '51') should 
   //   be created/updated depending wheather this is new 'M' /'9' account.
   //   
   //   Also, user has to access RESP Beneficiary Relationship screen to Add/Modify 
   //   links between RESP beneficiaries with Parent/Legal Guardian ('51' entity) and 
   //   Designated Institution ('52' entity)
   //
   //   Summary for entity type rule based on the MFAccount value :
   //   Nr.crt.	MFAccount Field          Value Entity Type     Error/Warning
   //   1	TaxType = Any Value	                        01	Error : Must exist 
   //   2	TaxType = 9 or M	                           50	Error : Must exist 
   //   3	TaxType != 9 and != M	                     50	Error : This entity is not allowed
   //   4	TaxType = 9 or M and Age of Entity '50' < 19	51	Warning : Entity should be set up. Only one entry is allowed when ReasonCode (view 50) = '00' if Taxtype = 9
   //   5	TaxType = 9 or M	                           52	Warning : Entity should be set up 
   //   6	TaxType = 0 and CotClient (view 83) = Y	   05	Warning : Entity should be set up and only one entry is allowed
   //   6 amended for TFSA TaxType = V Annuitant must be setup and it should be the same person (compare SIN)
   //   7	TaxType != 0	                              05	Error : This entity Type is not allowed
   //   8	AccountType = 1	                           06	Warning : Entity should be set up and only one entry is allowed
   //   9	AccountType != 2	                           01	Error : Only one is allow
   //   10	AccountType = 2	                           01	Warning : Should set up multiple Entity Type 01
   //   11	AccountType = 3	                           13	Warning : Entity should be set up
   //   12	InTrustFor = Y	                              14	Warning : Entity should be set up
   //   13	Escrow = Y	                                 11	Error : Must exist
   //   14	AccountDesignation = 2 or 3	               21	Error : Must exist and only one entry is allowed
   //   15	TaxType = Any Value	                        08	Error : This entity only allowed if EntityType '07' exist and BenPercentage -50 total up to 100%
   //   16  TaxType = E or D (ESoP)                      20 Error : Entity should be set up
   //	17	Account Purpose = Youth Portfolio,  InTrustFor = No, EntityType !='Other' Error : Entity Type must be Other.
   //   Rules should only be applied to MFAccount for Modification mode and Add mode to existing shareholder. 
   //   Rules applicable to Entity always
   //  18  Account Purpose = Youth Portfolio,  InTrustFor = Yes, EntityType = ITF, lastname, firstname and SIN must be entered

   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateOneAccount" ) );

   MFAccount *pMFAccount = NULL;
   getWorkSession().getMFAccount( idDataGroup, strAcctNum, pMFAccount );

   DString strTaxType, strAcctType, strAcctDesignation, strAcctPurpose, strInTrustFor;

   pMFAccount->getField( ifds::TaxType, strTaxType, idDataGroup );
   strTaxType.strip().upperCase();

   pMFAccount->getField( ifds::AcctType, strAcctType, idDataGroup );
   strAcctType.strip().upperCase();

   pMFAccount->getField( ifds::AcctDesignation, strAcctDesignation, idDataGroup );
   strAcctDesignation.strip().upperCase();    
   
   pMFAccount->getField( ifds::AcctPurpose, strAcctPurpose, idDataGroup );
   strAcctPurpose.strip().upperCase();

   pMFAccount->getField( ifds::InTrustFor, strInTrustFor, idDataGroup );
   strInTrustFor.strip().upperCase();

   int count_Accountholder_entities = 0,
      count_Annuitant_entities = 0,
      count_Spousal_Contributor_entities = 0,
      count_Nominee_Owner_entities = 0,
      count_Primary_Beneficiary_entities = 0,
      count_Secondary_Beneficiary_entities = 0,
      count_Escrow_Representative_entities = 0,
      count_Assignee_entities = 0,
      count_Trustee_entities = 0,
      count_ITF_Individual_entities = 0,
      count_Other_entities = 0,
      count_RESP_Beneficiary_entities = 0,
      count_Parent_Legal_Guardian_entities = 0,
      count_RESP_Design_Instit_entities = 0,
      count_Active_RESP_Beneficiary_entities = 0,
      count_Employer_entities = 0,
      resp_beneficiary_iAge = 0,
      RRSP_LIRA_Owner_iAge = 0,
      count_resp_pcg_entity_type = 0,
	  count_RDSP_Beneficiary_entities = 0,
	  count_RDSP_PCG_entities = 0;

   int numRegistrationAgentEntities = 0;
   bool foundIncorrectTaxTypeRA = false;

   DString strBenPercentage,
      strReasonCode,
      strEntityType,
      strOwnerEntityId,
      strLastOwnerSIN,
      strLastAnnuitantSIN;
   double lPrimBenPercentage = 0,
      lSecondBenPercentage = 0;
   SEVERITY sevRtn = NO_CONDITION;
   bool flg_acc_owner_seq1 = false;

   BFObjIter bfIter (*this, idDataGroup, true, 
      BFObjIter::ITERTYPE::NON_DELETED);
   DString searchKey;

   buildPartialKeyForAccount( searchKey, strAcctNum );
   bfIter.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey);
   if (bfIter.end())
   {
      sevRtn = PopulateEntitiesList (idDataGroup, strAcctNum);
   }
   acctOwnerEntities.clear();

   bfIter.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey );
   while( !bfIter.end() )
   {
      if( !bfIter.isDummy() )
      {
         DString strEntityType, strSeqNumber, strEntityId, strEntityTypeFmt;
         AccountEntityXrefObject* pAccountEntityXrefObject = dynamic_cast<AccountEntityXrefObject*>( bfIter.getObject() );

         pAccountEntityXrefObject->getField( ifds::EntityId, strEntityId, idDataGroup );
         pAccountEntityXrefObject->getField( ifds::EntityType, strEntityType, idDataGroup );
         pAccountEntityXrefObject->getField( ifds::EntityType, strEntityTypeFmt, idDataGroup, true );
         pAccountEntityXrefObject->getField( ifds::SeqNumber, strSeqNumber, idDataGroup );
         strEntityId.stripLeading( '0' );
         if( strEntityType == ACCOUNTHOLDER_ENTITY_TYPE && asInteger( strSeqNumber ) == 1 )
         {
            flg_acc_owner_seq1 = true;
            strOwnerEntityId = strEntityId;
         }
         if( strEntityType == ACCOUNTHOLDER_ENTITY_TYPE )
         {
            count_Accountholder_entities++;
            acctOwnerEntities.push_back( strEntityId );
            Entity *pEntity;
            getWorkSession().getEntity (idDataGroup, strEntityId, pEntity);
            pEntity->getField (ifds::SIN, strLastOwnerSIN, idDataGroup, false);
         }
         else if (strEntityType == ANNUITANT_ENTITY_TYPE)
         {
            count_Annuitant_entities++;
            Entity *pEntity;
            getWorkSession().getEntity (idDataGroup, strEntityId, pEntity);
            pEntity->getField (ifds::SIN, strLastAnnuitantSIN, idDataGroup, false);
            if( strTaxType == TFSA_TAX_TYPE )
            {
               EntityIds::validateSIN (getWorkSession(), 
                                       strTaxType, 
                                       ANNUITANT_ENTITY_TYPE, 
                                       strLastAnnuitantSIN,
                                       strEntityId,
                                       idDataGroup);

            }
         }
         else if( strEntityType == SPOUSAL_CONTRIBUTOR_ENTITY_TYPE )
         {
            count_Spousal_Contributor_entities++;

            if (strAcctType == I_("1")) // spousal tax type
            {
               if (strTaxType == RRIF_TAX_TYPE || 
                   strTaxType == RRSP_TAX_TYPE || 
                   strTaxType == RPP_TAX_TYPE  || 
                   strTaxType == PRIF_TAX_TYPE)
               {
                  Entity *pEntity;
                  DString sin;

                  getWorkSession().getEntity (idDataGroup, strEntityId, pEntity);
                  pEntity->getField (ifds::SIN, sin, idDataGroup, false);
                  EntityIds::validateSIN (getWorkSession(), 
                                          strTaxType, 
                                          strEntityType, 
                                          sin,
                                          strEntityId,
                                          idDataGroup);
               }
            }  // spousal tax type
         }
         else if( strEntityType == NOMINEE_OWNER_ENTITY_TYPE )
         {
            count_Nominee_Owner_entities++;
         }
         else if( strEntityType == EMPLOYER_ENTITY_TYPE ) count_Employer_entities++;
         else if( strEntityType == OTHER ) count_Other_entities++;
         else if( PRIMARY_BENEF_ENTITY_TYPE == strEntityType )
         {
            count_Primary_Beneficiary_entities++;
            //get strBenPercentage - view 50
            pAccountEntityXrefObject->getField( ifds::BenPercentage, strBenPercentage, idDataGroup );
            lPrimBenPercentage += DSTCommonFunctions::convertToDouble( strBenPercentage );
         }
         else if( SECONDARY_BENEF_ENTITY_TYPE == strEntityType )
         {
            count_Secondary_Beneficiary_entities++;
            pAccountEntityXrefObject->getField( ifds::BenPercentage, strBenPercentage, idDataGroup );
            lSecondBenPercentage += DSTCommonFunctions::convertToDouble( strBenPercentage );
         }

         if( SUCCESSOR_ENTITY_TYPE == strEntityType ||
             ACCOUNTHOLDER_ENTITY_TYPE == strEntityType ||
             SECONDARY_BENEF_ENTITY_TYPE == strEntityType ||
             PRIMARY_BENEF_ENTITY_TYPE == strEntityType )
         {
            if( !pAccountEntityXrefObject->isNew() && 
                pAccountEntityXrefObject->isUpdatedForDataGroup( idDataGroup, true ) )
            {
               // compare the current date (modification date) with the effective date of the escrow entity,

               DString dstrDate; 
               getWorkSession().getOption( ifds::CurrBusDate, dstrDate, idDataGroup, false );

               //bfIter.getObject()->getField( DBR::EffectiveDate, dstrDate, idDataGroup );
               escrowAccount( strAcctNum, CHG_ENTITY, strEntityType, dstrDate, idDataGroup, NULL_STRING, NULL_STRING);
            }
         }
         else if( ESCROW_REPREZENTATIVE_ENTITY_TYPE == strEntityType || ASSIGNEE_ENTITY_TYPE == strEntityType )
         {
            // Check Stop Date
            DString dstrEscrowStopDate, dstrCurrBusDate;
            pAccountEntityXrefObject->getField( ifds::EscrowStopDate, dstrEscrowStopDate, idDataGroup );
            getWorkSession().getOption( ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false );
            if( DSTCommonFunctions::CompareDates( dstrEscrowStopDate, dstrCurrBusDate ) == DSTCommonFunctions::SECOND_EARLIER )
            {
               if ( ESCROW_REPREZENTATIVE_ENTITY_TYPE == strEntityType )
                  count_Escrow_Representative_entities++;
               else if ( ASSIGNEE_ENTITY_TYPE == strEntityType )
                  count_Assignee_entities++;
            }

            if ( pAccountEntityXrefObject->isUpdatedForDataGroup( idDataGroup, true )  ) 
            {
               // compare the current date (modification date) with the effective date of the escrow entity,
               DString dstrDate; 
               getWorkSession().getOption( ifds::CurrBusDate, dstrDate, idDataGroup, false );

               //bfIter.getObject()->getField( DBR::EffectiveDate, dstrDate, idDataGroup );
               escrowAccount( strAcctNum, CHG_ADD_ESCROW, strEntityType, dstrDate, idDataGroup, NULL_STRING, NULL_STRING);
            }
         }
         else if( TRUSTEE_ENTITY_TYPE == strEntityType ) 
         {
            count_Trustee_entities++;
         }
         else if( ITF_INDIVIDUAL_ENTITY_TYPE == strEntityType )
         {
            count_ITF_Individual_entities++;
            //rule 18:
            if( strAcctPurpose == YOUNTH_PORTFOLIO && strInTrustFor == YES )
            {
               Entity *pEntity;
               getWorkSession().getEntity( idDataGroup, strEntityId, pEntity );
               DString dstrSIN, dstrFirstName, dstrLastName;
               pEntity->getField ( ifds::SIN, dstrSIN, idDataGroup, false );
               pEntity->getField ( ifds::FirstName, dstrFirstName, idDataGroup, false );
               if( dstrFirstName.strip() == NULL_STRING )
               {
                  long warningConID(0),errorConID(0);
                  errorConID = CND::ERR_FIELD_REQUIRED_PLS_ENTER;
                  warningConID = CND::WARN_FIELD_REQUIRED_PLS_SELECT;
                  pMFAccount->getErrMsg( I_("372"), errorConID, warningConID, idDataGroup ); 
               }
               if( dstrSIN == NULL_STRING )
               {
                  long warningConID(0),errorConID(0);
                  errorConID = CND::ERR_FIELD_REQUIRED_PLS_ENTER;
                  warningConID = CND::WARN_FIELD_REQUIRED_PLS_SELECT;
                  pMFAccount->getErrMsg( I_("371"), errorConID, warningConID, idDataGroup ); 
               }
               //last name always required, can not be controled by the error number.
            }
         }
         else if (RESP_BENEFICIARY_ENTITY_TYPE == strEntityType)
         {
            /*** This logic is to be *****/
            count_RESP_Beneficiary_entities++;

            pAccountEntityXrefObject->getField( ifds::RESPReasonCode, strReasonCode, idDataGroup );
            if( strReasonCode == I_( "00" ) )
               count_Active_RESP_Beneficiary_entities++;

            Entity *pEntity;
            getWorkSession().getEntity( idDataGroup, strEntityId, pEntity );
            if( pEntity )
            {
               TaxTypeRule *pTaxTypeRule = NULL;
               pMFAccount->getTaxTypeRule(pTaxTypeRule, idDataGroup);

               int ageCalcBasedOn = 0;

               if( pTaxTypeRule )
               {
                  DString dstrJurisdiction;

                  pMFAccount->getField( ifds::PensionJuris, dstrJurisdiction, idDataGroup );
                  pTaxTypeRule->getAgeCalcBasedOn (ageCalcBasedOn, dstrJurisdiction, idDataGroup);
               }

               resp_beneficiary_iAge = pEntity->getEntityAge( ageCalcBasedOn, idDataGroup );
            }
         }
         else if( PARENT_GUARDIAN_ENTITY_TYPE == strEntityType )
         {
            count_Parent_Legal_Guardian_entities++;
         }
         else if( RESP_DESIGNATED_INSTIT_ENTITY_TYPE == strEntityType )
         {
            count_RESP_Design_Instit_entities++;
         }
         else if ( RESP_PCG_INDIV_ENTITY_TYPE == strEntityType || 
                   RESP_PCG_INST_ENTITY_TYPE == strEntityType )
         {
            count_resp_pcg_entity_type++;
         }
         else if(strEntityType == REGISTRATION_AGENT_ENTITY_TYPE)
         {
            numRegistrationAgentEntities++;
            if(strTaxType == TAX_TYPE_OA ||
               strTaxType == TAX_TYPE_SA ||
               strTaxType == TAX_TYPE_SRS)
            {
               DString dstrEntityTaxType;
               pAccountEntityXrefObject->getField(ifds::ValidRATaxType, dstrEntityTaxType, idDataGroup);
               if(dstrEntityTaxType != strTaxType)
               {
                  foundIncorrectTaxTypeRA = true;
               }
            }
         }
		 else if (RDSP_BENEFICIARY == strEntityType)
		 {
			 count_RDSP_Beneficiary_entities++;
		 }
		 else if (RDSP_PCG == strEntityType)
		 {
			 count_RDSP_PCG_entities++;
		 }
         // if any fields of the entity list is changed, EntityIdsList must be validated to 
         // prevent wrongly close the dlg
         if (strEntityId != NULL_STRING)
         {
            Entity *pEntity;
            getWorkSession().getEntity( idDataGroup, strEntityId, pEntity );
            if( pEntity )
            {
               EntityIdsList *pEntityIdsList = NULL;
               pEntity->getEntityIdsList( pEntityIdsList, idDataGroup, true );
               if( pEntityIdsList )
                  sevRtn = pEntityIdsList->validateAll (idDataGroup, 0);
            }
         }
      }
      ++bfIter;
   }

   if (verifyDuplicityOfAcctOwnerEntities())
   {
      ADDCONDITIONFROMFILE( CND::ERR_ACCT_OWNER_DUPLICATE );
   }
   if( !flg_acc_owner_seq1 )
   {
	  bool bAcctOwnerSeq1Needed = true;

	  if (RDSP_TAX_TYPE == strTaxType && count_Accountholder_entities > 0)
		 bAcctOwnerSeq1Needed = false;

	  if (bAcctOwnerSeq1Needed)
	  {
      ADDCONDITIONFROMFILE( CND::ERR_ACCT_OWNER_SEQ_ONE_NEEDED );
   }
   }
   if( strAcctType != JOINT_ACCT_TYPE && count_Accountholder_entities > 1 )
   {
      ADDCONDITIONFROMFILE( CND::ERR_MULTIPLE_ACCT_OWNER );
   }
   if( strAcctType == JOINT_ACCT_TYPE && count_Accountholder_entities == 1 )
   {
      ADDCONDITIONFROMFILE( CND::ERR_MULTIPLE_ACCT_OWNER_NEEDED );
   }
   if( count_Accountholder_entities == 0 )
   {
      ADDCONDITIONFROMFILE( CND::ERR_NO_ACCT_OWNER ); 
   }
   if( count_Spousal_Contributor_entities > 1 )
   {
      ADDCONDITIONFROMFILE( CND::ERR_MULTIPLE_SPOUSAL );
   }

   //Registration Agent Entity
   if( numRegistrationAgentEntities > 1 )
   {
      ADDCONDITIONFROMFILE( CND::ERR_MULTIPLE_REGISTRATION_AGENT_ENTITIES );
   }
   else if( (strTaxType == TAX_TYPE_OA || strTaxType == TAX_TYPE_SA || strTaxType == TAX_TYPE_SRS ) && 
      numRegistrationAgentEntities == 0 )
   {
      ADDCONDITIONFROMFILE( CND::ERR_NO_RA_SELECTED );
   }
   if(foundIncorrectTaxTypeRA)
   {
      ADDCONDITIONFROMFILE( CND::ERR_NO_RA_MATCHING_TT);
   }

   if( strAcctDesignation == NOMINEE_ACCT_DESIGNATION || strAcctDesignation == INTERMEDIARY_ACCT_DESIGNATION )
   {
      if( count_Nominee_Owner_entities > 1 )
      {
         ADDCONDITIONFROMFILE( CND::ERR_MULTIPLE_NOMINEE_NOT_ALLOWED );
      }
      else if( count_Nominee_Owner_entities == 0 )
      {
         ADDCONDITIONFROMFILE( CND::ERR_NOMINEE_REQUIRED );
      }
   }
   else
   {
      if( count_Nominee_Owner_entities > 0 )
         ADDCONDITIONFROMFILE( CND::ERR_NOMINEE_INVALID_FOR_ACCT_TYPE );
   }
   if( count_Primary_Beneficiary_entities > 0 && fabs(lPrimBenPercentage - 100) > 0.0000000001 )
   {
      ADDCONDITIONFROMFILE( CND::ERR_PRIMARY_BENEF_PERCENT_SHOULD_ADD_UP_TO_100 );
   }

   if( count_Secondary_Beneficiary_entities > 0 && fabs(lSecondBenPercentage - 100) > 0.0000000001 )
   {
      ADDCONDITIONFROMFILE( CND::ERR_SECONDARY_BENEF_PERCENT_SHOULD_ADD_UP_TO_100 );
   }
   if( ESOP_INVESTMENT == strTaxType || ESOP_PARTICIPATION == strTaxType && count_Employer_entities == 0 )
   {
      ADDCONDITIONFROMFILE( CND::ERR_EMPLOYER_ENTITY_MUST_BE_SETUP );
   }

   // RESP Account
   if (INDIVIDUAL_RESP_TAX_TYPE == strTaxType || FAMILY_RESP_TAX_TYPE == strTaxType)
   {
      if (count_RESP_Beneficiary_entities == 0)
      {
         ADDCONDITIONFROMFILE( CND::ERR_RESP_BENEFICIARY_ENTITY_MUST_BE_SETUP );
      }
      else if (count_Active_RESP_Beneficiary_entities > 1 && INDIVIDUAL_RESP_TAX_TYPE == strTaxType)
      {
         ADDCONDITIONFROMFILE (CND::ERR_RESP_ONLY_ONE_BENF_ALLOW);
      }
      else if (count_Active_RESP_Beneficiary_entities == 0 && INDIVIDUAL_RESP_TAX_TYPE == strTaxType)
      {
         ADDCONDITIONFROMFILE (CND::ERR_RESP_ONLY_ACT_BENF_MISSING);
      }
      else
      {  // if RESP beneficiary has been set up then check if parent and designated institute set up exist
         // Logic to be fixed to handle multiple RESP beneficiary

         if (resp_beneficiary_iAge < 19) //Rule 4
         {
            if (0 == count_Parent_Legal_Guardian_entities)
            {
               ADDCONDITIONFROMFILE (CND::ERR_PARENT_ENTITY_SHOULD_BE_SETUP);
            }
            if (count_Parent_Legal_Guardian_entities > 1 && 
                INDIVIDUAL_RESP_TAX_TYPE == strTaxType)
            {
               ADDCONDITIONFROMFILE (CND::ERR_ONLY_ONE_PARENT_ENTITY_IS_ALLOWED);
            }
         }
         if (count_RESP_Design_Instit_entities == 0) //Rule 5
         {
            if (pMFAccount->isNew ())
            {
               ADDCONDITIONFROMFILE (CND::ERR_RESP_DESIGNATED_INSTIT_ENTITY_SHOULD_BE_SETUP);
            }
         }
         if (count_resp_pcg_entity_type > 0)
         {
            DString siblingOnly;

            pMFAccount->getField (ifds::SiblingOnly, siblingOnly, idDataGroup, false);
            if ( getWorkSession ().isRES2Client() && 
                 (siblingOnly == N || siblingOnly.empty()))
            {
               DString dstrTemp;

               addIDITagValue( dstrTemp, I_("ENTITY_TYPE"), I_("Primary Care Giver") );
               ADDCONDITIONFROMFILEIDI (CND::ERR_ENITITY_NOT_ALLOWED_FOR_RESP_SIBLING_NOT_YES, dstrTemp);
            }
         }
      }
   }
   //Rule 3 : Non RESP should not have RESP Beneficiary 
   else if (count_RESP_Beneficiary_entities > 0)
   {
      ADDCONDITIONFROMFILE (CND::ERR_RESP_BENEFICIARY_ENTITY_IS_NOT_ALLOWED_FOR_THIS_TAX_TYPE);
   }
   else if (count_resp_pcg_entity_type > 0)
   {
      DString strTaxTypeFmt;
      
      pMFAccount->getField (ifds::TaxType, strTaxTypeFmt, idDataGroup, true);
      DString idiStr;
      addIDITagValue (idiStr, I_("TAXTYPE"), strTaxTypeFmt);
      ADDCONDITIONFROMFILEIDI( CND::ERR_ENITITY_NOT_ALLOWED_FOR_NON_RESP, idiStr);
   }

   DString strCotClient;
   getWorkSession().getOption( ifds::CotClient, strCotClient, idDataGroup, true );
   strCotClient.strip().upperCase();

   DString strEscrow;
   pMFAccount->getField( ifds::Escrow, strEscrow, idDataGroup );
   strEscrow.strip().upperCase();

   //Rule 6
   if (strCotClient == YES)
   {
      DString dstrPorfolioIsRequried;

      getWorkSession().getOption (ifds::PorfolioIsRequried, dstrPorfolioIsRequried, BF::HOST, false);
      if ( dstrPorfolioIsRequried == I_("N") || 
           pMFAccount->hasSegFundsWithinPortfolio (idDataGroup))
      {
         if (count_Annuitant_entities == 0)
         {
            ADDCONDITIONFROMFILE (CND::ERR_ANNUITANT_ENTITY_SHOULD_BE_SETUP);
         }

         //exactly one annuitant
         if (count_Annuitant_entities > 1)
         {
            ADDCONDITIONFROMFILE (CND::ERR_MULTIPLE_ANNUITANT);
         }

         if (strTaxType == TFSA_TAX_TYPE || !getWorkSession().isNonRegLike (strTaxType))
         {
            // The annuitant and the account holder must be the same person; 
            // compare SIN and issue hard edit, if they are not the same
            if( !strLastAnnuitantSIN.strip().empty() /*&& 
                !strLastOwnerSIN.strip().empty() && 
                strLastAnnuitantSIN != strLastOwnerSIN*/)
            {
               validateAnnuitant (strLastAnnuitantSIN, idDataGroup); 
               //ADDCONDITIONFROMFILE (CND::ERR_SAME_ANNUITANT_AND_NOMINEE);
            }
         }
      }
   }

   /*** /Rule 7 This is not 
   if( !getWorkSession().isNonRegLike( strTaxType ) && count_Annuitant_entities > 0 )
   {
      ADDCONDITIONFROMFILE( CND::ERR_ANNUITANT_ENTITY_IS_NOT_ALLOWED );
   }****/

   //Rule 8
   if( SPOUSAL_ACCT_TYPE == strAcctType && count_Spousal_Contributor_entities == 0 )
   {
      ADDCONDITIONFROMFILE( CND::ERR_SPOUSAL_CONTRIBUTOR_ENTITY_SHOULD_BE_SETUP );
   }
   //Rule 11
   if( TRUST_ACCT_TYPE == strAcctType && 0 == count_Trustee_entities )
   {
      ADDCONDITIONFROMFILE( CND::ERR_TRUSTEE_ENTITY_SHOULD_BE_SETUP );
   }
   //Rule 12
   if( YES == strInTrustFor && 0 == count_ITF_Individual_entities )
   {
      ADDCONDITIONFROMFILE( CND::ERR_ITF_ENTITY_SHOULD_BE_SETUP );
   }
   if( NO == strInTrustFor && 0 < count_ITF_Individual_entities )
   {
      ADDCONDITIONFROMFILE( CND::ERR_ITF_ENTITY_SETUP_FOR_NON_ITF );
   }
   //Rule 13
   if( YES == strEscrow && 0 == count_Escrow_Representative_entities )
   {
      ADDCONDITIONFROMFILE( CND::ERR_ESCROW_REPREZENTATIVE_ENTITY_MUST_BE_SETUP );
   }
   if (NO == strEscrow && 0 < count_Escrow_Representative_entities)
   {
      ADDCONDITIONFROMFILE( CND::ERR_ESCROW_ENTITY_SETUP_FOR_NON_ESCROW );
   }

   //Rule 15
   if ( count_Primary_Beneficiary_entities > 0 && count_Secondary_Beneficiary_entities > 0 &&
        lPrimBenPercentage < 100L)
   {
      ADDCONDITIONFROMFILE( CND::ERR_SECONDARY_BENEFICIARY_ENTITY_ONLY_ALLOWED_IF_PRIMARY_ENTITY_EXIST );
   }

   DString TAXTYPELIST = I_("0,1,7,8,V");
   DString strMarket = DSTCommonFunctions::getMarket();
   bool bIntRIFPlan = getWorkSession ().isIntRIFPlan (strTaxType);// 2, B, BR, L, R
   bool bIsLIRALike = getWorkSession ().isLIRALike (strTaxType); // C, CR, U

   if( flg_acc_owner_seq1 && strMarket == MARKET_IDS::CANADA &&
       (bIntRIFPlan || bIsLIRALike || DSTCommonFunctions::codeInList( strTaxType, TAXTYPELIST )) )
   {
      Entity *pEntity;

      getWorkSession().getEntity(idDataGroup, 
         strOwnerEntityId.stripLeading( '0' ), pEntity);
      if (pEntity)
      {
         //Rule: if TaxType is 1 ( RRSP ) or C/CR ( LIRA ) or S ( ???? ), the age of the account owner cannot be >=70 

         if( strTaxType == RRSP_TAX_TYPE || strTaxType == LIRA_TAX_TYPE || strTaxType == LRSP_TAX_TYPE ) // || strTaxType == WILL_DEFIND_TAX_TYPE )
         {
            TaxTypeRule *pTaxTypeRule = NULL;
            pMFAccount->getTaxTypeRule(pTaxTypeRule, idDataGroup);

            int ageCalcBasedOn = 0;

            if( pTaxTypeRule )
            {
               DString dstrJurisdiction;

               pMFAccount->getField( ifds::PensionJuris, dstrJurisdiction, idDataGroup );
               pTaxTypeRule->getAgeCalcBasedOn (ageCalcBasedOn, dstrJurisdiction, idDataGroup);
            }

            RRSP_LIRA_Owner_iAge = pEntity->getEntityAge( ageCalcBasedOn, idDataGroup );
            if( RRSP_LIRA_Owner_iAge >= 72 )
            {
               DString idiStr, strTaxTypeDes;
               pMFAccount->getField ( ifds::TaxType, strTaxTypeDes, idDataGroup, true );
               addIDITagValue( idiStr, I_("RRSPLIRA"), strTaxTypeDes );
               pMFAccount->getErrMsg( I_( "233" ), CND::ERR_E_ENTITY_AGE_OVER_69, 
                                      CND::ERR_W_ENTITY_AGE_OVER_69, idDataGroup, idiStr );
            }
         }

         DString sin;

         pEntity->getField (ifds::SIN, sin, idDataGroup, false);
         EntityIds::validateSIN (getWorkSession(), 
                                 strTaxType, 
                                 ACCOUNTHOLDER_ENTITY_TYPE, 
                                 sin, 
                                 strOwnerEntityId,
                                 idDataGroup);
      } // if entity is not null
   }   
   //Rule: If PlanType_87 for TaxType_4/76jis "RIF" and can't find Primary Beneficiary with the seq1
   // Iss warning "Premary Beneficiary was not entered"

   //  if ( strTaxType == RRIF_TAX_TYPE )   // we don't need to check TaxType
//   {
   TaxTypeRule *pTaxTypeRule = NULL;
   sevRtn = pMFAccount->getTaxTypeRule ( pTaxTypeRule, idDataGroup );
   if( pTaxTypeRule )
   {
      DString dstrPlanType,dstrSelfDirected;
      pTaxTypeRule->getField(ifds::PlanType, dstrPlanType, idDataGroup,false );
      pTaxTypeRule->getField(ifds::SelfDirected, dstrSelfDirected, idDataGroup,false );
      dstrSelfDirected.strip().upperCase();
      dstrPlanType.strip().upperCase();
      if( dstrPlanType == RIF_PLAN_TYPE && dstrSelfDirected == NO )
      {
         if( count_Primary_Beneficiary_entities == 0 )
         {
            ADDCONDITIONFROMFILE( CND::ERR_WARN_PRIMARY_BENEFICIARY_NOT_ENTERED );
         }

         // No warning during NASU since user does not have access to RIF screen until after NASU finished and refreshed
         if( !pMFAccount->isNew() )
         {
            DString dstrRIFExist;
            pMFAccount->getField(ifds::RIFExist,dstrRIFExist,idDataGroup,false);
            if( dstrRIFExist.strip().upperCase() == NO )
            {
               ADDCONDITIONFROMFILE( CND::ERR_WARN_SCHEDULED_PAYMENT_NOT_ENTERED );
            }
         }
         if( strTaxType ==  RRIF_TAX_TYPE || strTaxType == PRIF_TAX_TYPE )
         {
            if( strAcctType != INDIVIDUAL_ACCT_TYPE && strAcctType != SPOUSAL_ACCT_TYPE )
            {
               ADDCONDITIONFROMFILE( CND::ERR_WARN_ACCOUNT_TYPE_MUST_BE_INDIVIDUAL_SPOUSE);
            }
         } // RIF tax type
        /* else if( strTaxType ==  LIF_TAX_TYPE || strTaxType ==  LRIF_TAX_TYPE )
         {
            if( strAcctType != INDIVIDUAL_ACCT_TYPE )
            {
               ADDCONDITIONFROMFILE( CND::ERR_WARN_ACCOUNT_TYPE_MUST_BE_INDIVIDUAL_FOR_RIF_LRIF_ACCOUNT );
            }
         } // LIF Tax type */
      }
   }

   //IN2952546 - INA Primary Beneficiary needed for all tax types
   DString dstrSegClient, dstrCotClient;
   getWorkSession().getOption (ifds::SegClient, dstrSegClient, BF::HOST);
   getWorkSession().getOption (ifds::CotClient, dstrCotClient, BF::HOST);

   bool isSegClient = ( dstrSegClient.strip() == YES && dstrCotClient.strip() == YES );
   if( isSegClient && (count_Primary_Beneficiary_entities == 0) )
   {
      ADDCONDITIONFROMFILE( CND::ERR_WARN_PRIMARY_BENEFICIARY_NOT_ENTERED );
   }
   
   //---IN2952546 --END
   //Rule 17:
   if( strAcctPurpose == YOUNTH_PORTFOLIO && strInTrustFor == NO && count_Other_entities == 0 )//strEntityType != OTHER )
   {
      ADDCONDITIONFROMFILE( CND::ERR_OTHER_ENTITY_TYPE_MUST_BE_SETUP );      
   }

   if (INDIVIDUAL_RESP_TAX_TYPE == strTaxType || FAMILY_RESP_TAX_TYPE == strTaxType)
   {
      //validate SIN for the entities involved
      AccountEntityXref *pAEXref = NULL;

      if (getWorkSession().getAccountEntityXref (idDataGroup, 
         pAEXref) <= WARNING)
      {
         DString searchKey;
         BFObjIter iter (*pAEXref, idDataGroup, true, 
            BFObjIter::ITERTYPE::NON_DELETED);

         buildPartialKeyForAccount (searchKey, strAcctNum);
         if (bfIter.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey))
         {
            while (!iter.end())
            {
               Entity *pEntity = NULL;
               DString entityType, 
                  entityId,
                  sin; 

               iter.getObject()->getField (ifds::EntityType, entityType, 
                  idDataGroup, false);
               iter.getObject()->getField (ifds::EntityId, entityId, 
                  idDataGroup, false);
               if (getWorkSession().getEntity (idDataGroup, 
                   entityId, pEntity) <= WARNING && pEntity)
               {
                  DString sin;

                  pEntity->getField (ifds::SIN, sin, idDataGroup, false);
                  EntityIds::validateSIN (getWorkSession(), 
                                          strTaxType, 
                                          entityType, 
                                          sin, 
                                          entityId,
                                          idDataGroup);
               }
               ++iter;
            }
         }
      }
   }

   BFObjIter iterAccountEntityXrefOut (*this, 
                                        idDataGroup, 
                                        true, 
                                        BFObjIter::ITERTYPE::NON_DELETED);

   AccountEntityXref::buildPartialKeyForAccount (searchKey, strAcctNum);
   iterAccountEntityXrefOut.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey);
   while (!iterAccountEntityXrefOut.end())
   {
      DString key = iterAccountEntityXrefOut.getStringKey ();
      
      DString entityId,
         entityType;
      
      AccountEntityXref::getValueForTag (key, I_("EntityId"), entityId);
      iterAccountEntityXrefOut.getObject ()->getField (ifds::EntityType, entityType, idDataGroup);
      DString  dstrRegDocExist, dstrDeathClaimDocExist;
      getWorkSession ().getOption (ifds::DeathClaimDocExist, dstrDeathClaimDocExist, idDataGroup, false);
      getWorkSession ().getOption (ifds::RegDocsExist, dstrRegDocExist, idDataGroup, false);

      //only for account owners and if enviroment supports regulatory standards.
      if (entityType == I_("01") && (dstrRegDocExist == I_("Y") || dstrDeathClaimDocExist == I_("Y"))) 
      {
         RegDocumentList *pRegDocumentList = NULL;
         if ( pMFAccount->getRegDocumentsList (pRegDocumentList, entityId, idDataGroup, true) <= WARNING &&
            pRegDocumentList)
         {
            if (pRegDocumentList->isAnyStatusBlank (idDataGroup))
            {
               ADDCONDITIONFROMFILE (CND::ERR_DOC_STATUS_BLANK);
            }
         }
      }
      else if (entityType != I_("01") && ((dstrRegDocExist == I_("Y") || dstrDeathClaimDocExist == I_("Y")) ) )
      {
          /*
           * INC0020970 : When the user creates a new entity with entity type 'AccountHolder' and later changed the entity type to
           *  some other entity type before Confirming the changes, then RegDocumentList will get created for the new entity even if its not an accountholder.
           * The below code will delete the RegDocumentList, if the user changed the entity type from account holder.
           */
           pMFAccount->removeRegDocumentList(entityId,idDataGroup);  
       }

      
      ++iterAccountEntityXrefOut;
   }

   // RDSP Account
   if (RDSP_TAX_TYPE == strTaxType)
   {
	   if (count_RDSP_Beneficiary_entities == 0)
	   {
		   // RDSP Beneficiary Entity must be setup
		   ADDCONDITIONFROMFILE( CND::ERR_RDSP_BENEFICIARY_ENTITY_MUST_BE_SETUP );
	   }
	   else if (count_RDSP_Beneficiary_entities > 1)
	   {
		   // 2118 - RDSP Beneficiary can not be more than one		  
		   getErrMsg ( IFASTERR::RDSP_ONLY_ONE_BENF_ALLOW, 
								 CND::ERR_RDSP_ONLY_ONE_BENF_ALLOW, 
								 CND::WARN_RDSP_ONLY_ONE_BENF_ALLOW,
								 idDataGroup); 		    
	   }
	   
	   if (count_RDSP_PCG_entities > 2)
	   {
		   // 2117 - Only 2 RDSP Primary Caregivers are allowed		 
		   getErrMsg ( IFASTERR::RDSP_ONLY_TWO_PCG_ALLOW, 
								 CND::ERR_RDSP_ONLY_TWO_PCG_ALLOW, 
								 CND::WARN_RDSP_ONLY_TWO_PCG_ALLOW,
								 idDataGroup); 
	   }

	   if (count_RDSP_Beneficiary_entities > 0 && count_RDSP_PCG_entities == 0)
	   {		  
		   DString dstrEntityId, dstrCurrentDate, dstrDofBirth, dstrAsOfDec31, dstrDate, dstrAge, dstrMonth;          

		   ENTITIES_VECTOR rdspBeneficiaryEntities;
		   getRDSPBeneficiaryEntity (rdspBeneficiaryEntities, strAcctNum, idDataGroup);

		   for (ENTITIES_VECTOR::size_type i = 0; i < rdspBeneficiaryEntities.size(); ++i)
		   {
			   dstrEntityId = rdspBeneficiaryEntities [i];
			   Entity *pEntity = NULL;
			   if  (getWorkSession().getEntity (idDataGroup, dstrEntityId, pEntity) <= WARNING && pEntity)
			   {					
				   pEntity->getField (ifds::DofBirth, dstrDofBirth, idDataGroup, false);

				   getWorkSession ().getOption (ifds::CurrSysDate, dstrCurrentDate, idDataGroup, false);				  

				   int nEffectiveYear = DSTCommonFunctions::getYearFromUnFormattedDate(dstrCurrentDate);
				   convertIntToString (nEffectiveYear, dstrCurrentDate);

				   dstrAsOfDec31 = I_("1231");
				   dstrDate = dstrAsOfDec31 + dstrCurrentDate;
				
				   DSTCommonFunctions::BuildAge (dstrDofBirth, dstrDate, dstrAge, dstrMonth);
				   int age = convertToULong (dstrAge);

				   if( age <= 18)
				   {				
					   // 2051 - RDSP Primary Care Giver is mandatory as beneficiary is age 18 years or less (by December 31 of the calendar year).            
					   getErrMsg ( IFASTERR::RDSP_PCG_ENTITY_MUST_BE_SETUP, 
								   CND::ERR_RDSP_PCG_ENTITY_MUST_BE_SETUP, 
								   CND::WARN_RDSP_PCG_ENTITY_MUST_BE_SETUP,
								   idDataGroup);
   }
			   }
		   }
	   }
   }
   else 
   {
	   if (count_RDSP_Beneficiary_entities > 0)
	   {
		   // RDSP Beneficiary Entity is not allowed for this tax type
		   ADDCONDITIONFROMFILE( CND::ERR_RDSP_BENEFICIARY_ENTITY_IS_NOT_ALLOWED_FOR_THIS_TAX_TYPE );
	   }

	   if (count_RDSP_PCG_entities > 0)
	   {
		   // RDSP Primary Care Giver Entity is not allowed for this tax type
		   ADDCONDITIONFROMFILE( CND::ERR_RDSP_PCG_ENTITY_IS_NOT_ALLOWED_FOR_THIS_TAX_TYPE );
	   }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AccountEntityXref::validateAnnuitant (const DString &dstrAnnuitantSIN, const BFDataGroupId& idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAnnuitant" ) );

   BFObjIter iterAccountEntityXref (*this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED);
   iterAccountEntityXref.begin ();

   DString dstrEntityId, dstrSIN, dstrEntityType;
   bool bFound = false;

   while (!iterAccountEntityXref.end())
   {
      AccountEntityXrefObject* pAccountEntityXrefObject = dynamic_cast<AccountEntityXrefObject*>(iterAccountEntityXref.getObject());

      pAccountEntityXrefObject->getField( ifds::EntityId, dstrEntityId, idDataGroup );
      pAccountEntityXrefObject->getField( ifds::EntityType, dstrEntityType, idDataGroup );
      dstrEntityId.stripLeading( '0' );

      Entity *pEntity;
      getWorkSession().getEntity (idDataGroup, dstrEntityId, pEntity);
      pEntity->getField (ifds::SIN, dstrSIN, idDataGroup, false);

      if (dstrAnnuitantSIN == dstrSIN && dstrEntityType == ACCOUNTHOLDER_ENTITY_TYPE)
      {
         bFound = true;
         break;
      }

      ++iterAccountEntityXref;
   }

   if (!bFound)
   {
      ADDCONDITIONFROMFILE (CND::ERR_SAME_ANNUITANT_AND_NOMINEE);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AccountEntityXref::validateDateOfBirth(const DString &accountNumber, const BFDataGroupId& idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateDateOfBirth" ) );

   BFObjIter bfIter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED, false, true );
   bfIter.begin();

   while (!bfIter.end())
   {
      AccountEntityXrefObject* pAccountEntityXrefObject = 
         dynamic_cast<AccountEntityXrefObject*>( bfIter.getObject() );

      DString dstrTaxType;
      MFAccount *pMFAccount = NULL;

      SEVERITY sevRtn = getWorkSession().getMFAccount( idDataGroup, accountNumber, pMFAccount ); 

      if( sevRtn <= WARNING && pMFAccount )
      {
         pMFAccount->getField( ifds::TaxType, dstrTaxType, idDataGroup, false );
         dstrTaxType.strip().upperCase();

         if (dstrTaxType == RRSP_TAX_TYPE || dstrTaxType == DPSP_TAX_TYPE || 
             dstrTaxType == RPP_TAX_TYPE  || dstrTaxType == INDIVIDUAL_RESP_TAX_TYPE || 
             getWorkSession().isIntRIFPlan (dstrTaxType) ||
             getWorkSession().isLIRALike (dstrTaxType) || 
             dstrTaxType == FAMILY_RESP_TAX_TYPE || dstrTaxType == TFSA_TAX_TYPE  ||
			 dstrTaxType == RDSP_TAX_TYPE)
         {
            pAccountEntityXrefObject->validateEntityTypeDofB( idDataGroup );
         }
      }

      ++bfIter;
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AccountEntityXref::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   BFObjIter bfIter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED, false, true );
   bfIter.begin();
   DString accNum, oldAccNum = NULL_STRING;
   typedef std::map< DString, DString, std::less< DString > > SIN_MAP;
   typedef std::map< DString, DString, std::less< DString > > CLEARING_PLATFORM_MAP;

   SIN_MAP sinMap;
   SIN_MAP::iterator sinMapIter;

   CLEARING_PLATFORM_MAP clearingPlatformMap;
   CLEARING_PLATFORM_MAP::iterator clearingPlatformMapIter;
   int iEscrowCount = 0; //P0186486_FN01 - IN2738162 Loan Number vs shareholder
   bool bOwnerSameTaxWithShr = false;
 
   while( !bfIter.end() )
   {
      AccountEntityXrefObject* pAccountEntityXrefObject = 
      dynamic_cast<AccountEntityXrefObject*>( bfIter.getObject() );

      pAccountEntityXrefObject->getField( ifds::AccountNum, accNum, idDataGroup, false );
      accNum.stripLeading( '0' );

      if( oldAccNum != accNum && currAccountNum == accNum )
      {
         validateOneAccount( accNum, idDataGroup ); // this method also validate the EntityIdList
         oldAccNum = accNum;
      }

      DString dstrTaxType, dstrShrNum, dstrShrTaxJuris;
      MFAccount *pMfAccount = NULL;
      SEVERITY sevRtn = getWorkSession().getMFAccount( idDataGroup, accNum, pMfAccount ); 

      if( sevRtn <= WARNING && pMfAccount )
      {
         pMfAccount->getField( ifds::TaxType, dstrTaxType, idDataGroup, false );
         dstrTaxType.strip().upperCase();
         if( dstrTaxType == RRSP_TAX_TYPE || dstrTaxType == DPSP_TAX_TYPE || 
             dstrTaxType == RPP_TAX_TYPE  || dstrTaxType == INDIVIDUAL_RESP_TAX_TYPE || 
             getWorkSession().isIntRIFPlan (dstrTaxType) ||
             getWorkSession().isLIRALike (dstrTaxType) || 
             dstrTaxType == FAMILY_RESP_TAX_TYPE || dstrTaxType == TFSA_TAX_TYPE || 
			 dstrTaxType == RDSP_TAX_TYPE )
         {
            pAccountEntityXrefObject->validateEntityTypeDofB( idDataGroup );
         }

         if( dstrTaxType == TAX_TYPE_OA || dstrTaxType == TAX_TYPE_SA || dstrTaxType == TAX_TYPE_SRS)
         {
            pAccountEntityXrefObject->validateEntityRegistrationAgentType(dstrTaxType, idDataGroup );
            pAccountEntityXrefObject->validateAll(idDataGroup);
         }
		 // get shareholder for the account
		 pMfAccount->getField( ifds::ShrNum, dstrShrNum, idDataGroup );
		 Shareholder* pShareholder = NULL;

		 if( getWorkSession().getShareholder( idDataGroup, dstrShrNum, pShareholder ) <= WARNING )
		 {
			 pShareholder->getField( ifds::TaxJurisCode, dstrShrTaxJuris, idDataGroup );
		 }
      }

      //for Canadian market have to check SIN duplicity (if same SIN for different EntityIds, issue error)
      Entity *pEntity = NULL;
      if (DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA)
      {
         DString strEntityId;

         pAccountEntityXrefObject->getField (ifds::EntityId, 
            strEntityId, idDataGroup, false);
         if (!strEntityId.strip().empty())
         {

            if (getWorkSession().getEntity (idDataGroup, 
               strEntityId.strip(), pEntity) <= WARNING && 
               pEntity)
            {

               EntityIdsList* pEntityIdsList = NULL;

               pEntity->getEntityIdsList (pEntityIdsList, idDataGroup, false);
               if (pEntityIdsList)
               {
                  BFObjIter bfIterIds (*pEntityIdsList, idDataGroup, false, 
                     BFObjIter::ITERTYPE::NON_DELETED);

                  bfIterIds.begin();
                  while (!bfIterIds.end())
                  {
                     DString strIdType, 
                        strSIN;

                     bfIterIds.getObject()->getField (ifds::IdType, strIdType, 
                        idDataGroup, false);
                     if (strIdType == CODE_SIN)
                     {
                        bfIterIds.getObject()->getField (ifds::IdValue, strSIN, 
                           idDataGroup, false);
                     }
                     if (!strSIN.strip().empty())
                     {
                        sinMapIter = sinMap.begin();
                        sinMapIter = sinMap.find (strSIN);
                        if (sinMapIter == sinMap.end())
                        {
                           sinMap.insert (SIN_MAP::value_type (strSIN, strEntityId));
                        }
                        else
                        {
                           do 
                           {
                              if ((*sinMapIter).second != strEntityId &&
                                 !EntityIds::isSINExcepted (getWorkSession(), strSIN, idDataGroup))
                              {
                                 bool bUseOldError = true;
                                 if ( getWorkSession ().isRES2Client() && 
                                      (dstrTaxType == INDIVIDUAL_RESP_TAX_TYPE ||
                                       dstrTaxType == FAMILY_RESP_TAX_TYPE) )
                                 {
                                    bUseOldError = false;
                                 }

                                 if (!bUseOldError)
                                 {
                                    //duplicateSINErrorWarning((*sinMapIter).second,
                                    //                         strEntityId,
                                    //                         idDataGroup );
                                 }
                                 else
                                 {
                                    // Duplicate SIN found in the entity list.
                                    getErrMsg ( IFASTERR::DUPLICATE_SIN, 
                                                CND::ERR_DUPLICATE_SIN_DIFFERENT_ENTITY, 
                                                CND::WARN_DUPLICATE_SIN_DIFFERENT_ENTITY, 
                                                idDataGroup); 
                                 }
                                 break;
                              }
                           }
                           while (sinMapIter == sinMap.end());
                        }
                     }
                     ++bfIterIds;
                  }
               }
            }	// end getentity
         }
      }	// end Market is Canada

      //MT535/MT536
      if ( DSTCommonFunctions::getMarket() == MARKET_IDS::LUXEMBOURG )
      {
         // only international client would have clearing platform entity
         // hence we should validate duplicity of them
         DString strEntityId;

         pAccountEntityXrefObject->getField (ifds::EntityId, 
            strEntityId, idDataGroup, false);
         if (!strEntityId.strip().empty())
         {

            if (getWorkSession().getEntity (idDataGroup, 
               strEntityId.strip(), pEntity) <= WARNING && 
               pEntity)
            {
               EntityIdsList* pEntityIdsList = NULL;

               pEntity->getEntityIdsList (pEntityIdsList, idDataGroup, false);
               if (pEntityIdsList)
               {
                  BFObjIter bfIterIds (*pEntityIdsList, idDataGroup, false, 
                     BFObjIter::ITERTYPE::NON_DELETED);

                  bfIterIds.begin();
                  while (!bfIterIds.end())
                  {
                     DString strIdType, 
                             strClearingPlatformIdValue = NULL_STRING;

                     bfIterIds.getObject()->getField (ifds::IdType, strIdType, 
                        idDataGroup, false);
                     if (strIdType == CODE_CLEARING_PLATFORM_ID_VAL)
                     {
                        bfIterIds.getObject()->getField (ifds::IdValue, 
                           strClearingPlatformIdValue, 
                           idDataGroup, false);

                        DString dstrEntityType;
                        pAccountEntityXrefObject->getField(ifds::EntityType, dstrEntityType, idDataGroup, false);
                        
                        if(dstrEntityType != CLEARING_PLATFORM_ENTITY_TYPE)
                        {
                           ADDCONDITIONFROMFILE (CND::ERR_CLEARING_ID_MUST_BELONG_TO_CLEARING_ENTITY);
                        }
                     }
                     if (!strClearingPlatformIdValue.strip().empty())
                     {
                        clearingPlatformMapIter = clearingPlatformMap.begin();
                        clearingPlatformMapIter = 
                           clearingPlatformMap.find (strClearingPlatformIdValue);
                        if (clearingPlatformMapIter == clearingPlatformMap.end())
                        {
                           clearingPlatformMap.insert (
                              CLEARING_PLATFORM_MAP::value_type (
                              strClearingPlatformIdValue, strEntityId));
                        }
                        else
                        {
                           ADDCONDITIONFROMFILE (
                              CND::ERR_MULTIPLE_SAME_CLEARING_PLATFORM_ENTITY_NOT_ALLOWED_FOR_ACCOUNT);
                        }
                     }
                     ++bfIterIds;
                  }
               }
            }
         }
      }
	  //
	  //INC0012472(3352448) - Unable to update contact information in the Entity tab
	  //
	  DString dstrEntityType, dstrUpdShrTaxJuris, dstrEntityTaxJuris;
      pAccountEntityXrefObject->getField(ifds::EntityType, dstrEntityType, idDataGroup, false);
	  /*******************************************************************
	   * For AcctOwner entities (Individual and Joint), 
	   * at least 1 entity's taxjuris must be same as shareholder.
	   * It can be different if the checkbox to sync to shareholder checked
	   * because view program will synch shareholder to be same as entity.
	   *******************************************************************/
	  if( (dstrEntityType == ACCOUNTHOLDER_ENTITY_TYPE) &&  (!bOwnerSameTaxWithShr) && pEntity != NULL)
	  {
		  pEntity->getField (ifds::UpdShrTaxJuris, dstrUpdShrTaxJuris, idDataGroup, false);
		  dstrUpdShrTaxJuris.strip().upperCase();
		  pEntity->getField (ifds::TaxJuris, dstrEntityTaxJuris, idDataGroup, false);				   

		  if(dstrUpdShrTaxJuris == YES || (dstrEntityTaxJuris == dstrShrTaxJuris))
			bOwnerSameTaxWithShr = true;  

	  }

      // check Allocation percent for RESP Beneficiary.
      pAccountEntityXrefObject->validateRESPBenefAlloc( idDataGroup );
      // To ensure the method is called whenever DOFB or SIN date changed.
      pAccountEntityXrefObject->validateDofBirthAgainstSINIdDateForRESPBenf( idDataGroup );

	  if( dstrEntityType == RESP_BENEFICIARY_ENTITY_TYPE && !pMfAccount->isNew() && pAccountEntityXrefObject->isNew()) 
	  {
		  pAccountEntityXrefObject->validateAcctSAGESBalance( idDataGroup ); //check SAGES balance at the account level when a beneficiary is added on an account
		  pAccountEntityXrefObject->validateAcctBCTESGBalance( idDataGroup ); //check BCTESG balance at the account level when a beneficiary is added on an account
	  }

	  if( dstrEntityType == LEAD_ACCOUNT_MANAGER_ENTITY_TYPE || dstrEntityType == ACCOUNT_MANAGER_ENTITY_TYPE )
	  {
		  pEntity->validationForCRM(idDataGroup);
	  }

	  pEntity->validationForEmailPhone(idDataGroup);

      ++bfIter;
   }

   //IN3308549
   //if (DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA)
   //{
   if (!bOwnerSameTaxWithShr)	  
   {
	   //ADDCONDITIONFROMFILE (CND::ERR_JURISDICTION_NOT_SAME_AS_SHRHLDR_JURISDICTION);
	   getErrMsg ( IFASTERR::JURISDICTION_NOT_SAME_AS_SHRHLDR_JURISDICTION,
		   CND::ERR_JURISDICTION_NOT_SAME_AS_SHRHLDR_JURISDICTION,
		   CND::WARN_JURISDICTION_NOT_SAME_AS_SHRHLDR_JURISDICTION,
		   idDataGroup);
   }
   //}

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void AccountEntityXref::setCurrentAccounNum( const DString& accountNum ) 
{
   currAccountNum = accountNum;
   currAccountNum.stripLeading( '0' );
}

//*****************************************************************************
void AccountEntityXref::setrefreshflag(bool relreshflag)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setrefreshflag" ) );
   m_bRefresh = relreshflag;
}

//*****************************************************************************
bool AccountEntityXref::getrefreshflag()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getrefreshflag" ) );
   return m_bRefresh;
}

//*****************************************************************************
bool AccountEntityXref::IsDeleteAllowed(const DString&  strKey, const BFDataGroupId& idDataGroup,bool bAddCond )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "IsDeleteAllowed" ) );

   DString dstrEntityType;
   AccountEntityXrefObject* _pObj = dynamic_cast<AccountEntityXrefObject*>( getObject(strKey, idDataGroup) );
   _pObj->getField(ifds::EntityType,dstrEntityType,idDataGroup);

   if( dstrEntityType == RESP_BENEFICIARY_ENTITY_TYPE )
   {
      DString dstrReasonCode;
      _pObj->getField(ifds::RESPReasonCode, dstrReasonCode, idDataGroup);
      if( dstrReasonCode == CURRENT_BENEFICIARY )
      {
         if( bAddCond )
         {
            ADDCONDITIONFROMFILE( CND::ERR_DELETE_RESP_ENTITY );
            return(false);
         }
      }
   }
   else if ( dstrEntityType == RESP_PCG_INDIV_ENTITY_TYPE || 
             dstrEntityType == RESP_PCG_INST_ENTITY_TYPE )
   {
      BFObjIter iterAccountEntityXref (*this, 
                                       idDataGroup, 
                                       true, 
                                       BFObjIter::ITERTYPE::NON_DELETED);

      DString strObjEntityType, strEntityId, strObjEntityId;
      iterAccountEntityXref.begin ();

      _pObj->getField( ifds::EntityId, strEntityId, idDataGroup, false);
      while (!iterAccountEntityXref.end())
      {
         AccountEntityXrefObject* pObj = 
            dynamic_cast<AccountEntityXrefObject*>(iterAccountEntityXref.getObject());

         pObj->getField (ifds::EntityType, strObjEntityType, idDataGroup, false);
         pObj->getField (ifds::EntityId, strObjEntityId, idDataGroup, false);
         strObjEntityId.strip().upperCase();

         if ( strObjEntityType == RESP_BENEFICIARY_ENTITY_TYPE )
         {
            DString strPCG;
            pObj->getField( ifds::RES2PCGList, strPCG, idDataGroup, false );
            strPCG.strip().upperCase();

            if ( strPCG == strEntityId )
            {
               if( bAddCond )
               {
                  ADDCONDITIONFROMFILE( CND::ERR_DELETE_RESP_ENTITY );
               }

               return(false);
            }
         }

         ++iterAccountEntityXref;
      }
   }

   return(true);
}

//*****************************************************************************
bool AccountEntityXref::canDeleteObject( const DString&  strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "canDeleteObject" ) );
   if(m_bRefresh) return true;

   AccountEntityXrefObject* _pObj = dynamic_cast<AccountEntityXrefObject*>( getObject(strKey, idDataGroup) );

   DString dstrEntityType, dstrSeq, dstrSpouseEntityID, dstrEntityId;
   _pObj->getField(ifds::EntityType, dstrEntityType, idDataGroup, false);
   _pObj->getField(ifds::EntityId, dstrEntityId, idDataGroup, false);

   Entity *pEntity;
   getWorkSession().getEntity( idDataGroup, dstrEntityId, pEntity );              
   pEntity->getField ( ifds::SpouseEntityID, dstrSpouseEntityID, idDataGroup, false ); 

   if( dstrEntityType.strip() == ACCOUNTHOLDER_ENTITY_TYPE && dstrSpouseEntityID.strip().stripAll('0') != NULL_STRING )
   {
      ADDCONDITIONFROMFILE( CND::ERR_REMOVE_SPOUSE_LINK_BEFORE_DELETE_OWNER );
      return false;
   }
   else if( dstrEntityType.strip() == OWNER_SPOUSAL && IsSpouselinkedtoOwner(dstrEntityId, idDataGroup) )
   {
      ADDCONDITIONFROMFILE( CND::ERR_REMOVE_SPOUSE_LINK_BEFORE_DELETE_OWNER );
      return false;
   }

   if( _pObj->isNew() )  // user is allow to delete a new record and replace it with another
   {
      return(true);
   }
   else // only existing record need validation before deletion
   {
      return(IsDeleteAllowed(strKey,idDataGroup ));
   }
}

//******************************************************************************
bool AccountEntityXref::IsSpouselinkedtoOwner( const DString &SpouseEntityId, const BFDataGroupId& idDataGroup )
{   
   DString strEntityType, tmp, strEntityId;
   bool flg_found = false;

   BFObjIter bfIter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED, false );
   bfIter.begin();
   while( !bfIter.end() )
   {
      bfIter.getObject()->getField( ifds::EntityType, strEntityType, idDataGroup, false );
      bfIter.getObject()->getField( ifds::EntityId, strEntityId, idDataGroup, false );
      if( strEntityType.strip() == ACCOUNT_OWNER_ENTITY_TYPE )
      {
         Entity *pEntity;
         getWorkSession().getEntity( idDataGroup, strEntityId, pEntity );
         pEntity->getField ( ifds::SpouseEntityID, tmp, idDataGroup, false );

         if( tmp.strip() != NULL_STRING && tmp.strip() != I_("0") && tmp == SpouseEntityId )
         {
            flg_found = true;
            break;
         }
      }

      ++bfIter;
   }
   return flg_found;
}
//******************************************************************************
SEVERITY AccountEntityXref::escrowAccountFundClass( const DString& strAcctNum, const DString& strFund, const DString& strClass,
                                                    const DString& dstrDate, const BFDataGroupId& idDataGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "escrowAccountFundClass" ) );
   SEVERITY sevRtn = NO_CONDITION;

   sevRtn = PopulateEntitiesList( idDataGroup, strAcctNum);

   DString searchKey;
   buildPartialKeyForAccount( searchKey, strAcctNum );
   BFObjIter bfIter( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED);//, false, true );
   bfIter.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey );

   while( !bfIter.end() )
   {
      AccountEntityXrefObject* pAccountEntityXrefObject = dynamic_cast<AccountEntityXrefObject*>( bfIter.getObject() );

      if( !pAccountEntityXrefObject )
      {
         ++bfIter;
         continue;
      }

      DString entityType, escrowFund, escrowClass;

      pAccountEntityXrefObject->getField( ifds::EntityType,     entityType, idDataGroup );
      pAccountEntityXrefObject->getField( ifds::EscrowFund,     escrowFund, idDataGroup );
      pAccountEntityXrefObject->getField( ifds::EscrowClass,    escrowClass,idDataGroup );
      escrowFund.strip().upperCase();
      escrowClass.strip().upperCase();

      if( ( entityType == ESCROW_REPREZENTATIVE_ENTITY_TYPE /* Escrow */ ||
            entityType == ASSIGNEE_ENTITY_TYPE ) &&
          ( escrowFund == strFund && escrowClass == strClass ) )
      {
         DString escrowStart, escrowEnd;

         pAccountEntityXrefObject->getField( ifds::EscrowDeff,     escrowStart,idDataGroup, false  );
         pAccountEntityXrefObject->getField( ifds::EscrowStopDate, escrowEnd,  idDataGroup, false  );

         escrowStart.strip();
         escrowEnd.strip();

         if( escrowStart != NULL_STRING && escrowEnd != NULL_STRING )
         {
            if( DSTCommonFunctions::IsDateBetween(escrowStart, escrowEnd, dstrDate) )
            {
               DString dstrAmtAssigned;
               pAccountEntityXrefObject->getField( ifds::AmtAssigned, dstrAmtAssigned,  idDataGroup, false  );

               double dec_amount=DSTCommonFunctions::convertToDouble ( dstrAmtAssigned );

               if( dec_amount == 0 )
               {
                  ADDCONDITIONFROMFILE( CND::ERR_ESCROW_LOCKED_ALL_UNITS );
               }
               else
               {
                  ADDCONDITIONFROMFILE( CND::ERR_ESCROW_LOCKED_PARTIAL_UNITS );
               }
               return(GETCURRENTHIGHESTSEVERITY());
            }
         }

      } // if

      ++bfIter;
   } // while
   return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************
SEVERITY AccountEntityXref::escrowAccount( const DString& strAcctNum, 
                                           const DString& dstrTransType, 
                                           const DString& dstrEntityType, 
                                           const DString& dstrDate, 
                                           const BFDataGroupId& idDataGroup, 
                                           const DString& dstrInReason, 
                                           const DString& dstrSeqenceNum ) 
{

   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "escrowAccount" ) );

   MFAccount *pMFAccount = NULL;
   getWorkSession().getMFAccount( idDataGroup, strAcctNum, pMFAccount );

   DString dstrTitleRestrict, searchKey;
   getWorkSession().getOption( ifds::TitleRestrict, dstrTitleRestrict, idDataGroup, false );

   SEVERITY sevRtn = PopulateEntitiesList( idDataGroup, strAcctNum);

   buildPartialKeyForAccount( searchKey, strAcctNum );
   BFObjIter bfIter( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED);//, false, true );
   bfIter.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey );

   while( !bfIter.end() )
   {
      AccountEntityXrefObject* pAccountEntityXrefObject = dynamic_cast<AccountEntityXrefObject*>( bfIter.getObject() );

      if( !pAccountEntityXrefObject )
      {
         ++bfIter;
         continue;
      }

      DString strEntityType; //, dstrExistEscrow, dstrExistAssignee;
      pAccountEntityXrefObject->getField( ifds::EntityType, strEntityType, idDataGroup, false );

      //pMFAccount->getField( ifds::Escrow, dstrExistEscrow, idDataGroup, false );
      //pMFAccount->getField( ifds::ExistAssignee, dstrExistAssignee, idDataGroup, false );

      //if ( dstrExistEscrow.strip().upperCase() == YES  )
      //{

      if( ! (ESCROW_REPREZENTATIVE_ENTITY_TYPE == strEntityType  || ASSIGNEE_ENTITY_TYPE == strEntityType ) )
      {
         ++bfIter;
         continue;
      }

      if( pAccountEntityXrefObject->isEntityEffective( dstrDate, idDataGroup ) )
      {
         DString dstrEscrowFund(NULL_STRING), dstrReasonCode;
         pAccountEntityXrefObject->getField( ifds::EscrowFund, dstrEscrowFund, idDataGroup );
         pAccountEntityXrefObject->getField( ifds::ReasonCode, dstrReasonCode, idDataGroup );

         dstrEscrowFund.strip();

         /**** Escrow Reason
         01     Bankruptcy
         02     Requirement_to_Pay
         03     Garnishment
         04     Writ_of_Seizure
         05     RSP_Loan
         06     Collateral Assignment
         07     Power of Attorney
         08     Committee
         09     Loan
         10     TD Loan
         11     CESG Return
         *************************/
         DString REASONCODELIST01TO06  = I_( "01,02,03,04,05,06");
         DString REASONCODELIST07TO08  = I_( "07,08");
         DString REASONCODELIST01AND04 = I_( "01,04");
         DString REASONCODELIST02AND03 = I_( "02,03");
         DString REASONCODELIST02030506 = I_( "02,03,05,06");


         // Address Change
         if( dstrTitleRestrict == YES && dstrTransType == ADDR_CHG )
         {
            if( DSTCommonFunctions::codeInList( dstrReasonCode, REASONCODELIST07TO08) )
            {
               ADDCONDITIONFROMFILE( CND::ERR_WARN_ACCT_ASSIGNED_COMMITTEE_POWERATTNY );
            }
         }

         // Add entity type Escrow Representive with reason code 01 - 06
         if( dstrTitleRestrict == YES && dstrTransType == ADD_ENTITY )
         {
            DString dstrCurrSeqNumber;
            pAccountEntityXrefObject->getField( ifds::SeqNumber, dstrCurrSeqNumber, idDataGroup );

            // if not the one for edit check
            if( DSTCommonFunctions::codeInList( dstrInReason, REASONCODELIST01TO06) 
                && dstrSeqenceNum != dstrCurrSeqNumber.stripLeading( '0' ) )
            {
               if( DSTCommonFunctions::codeInList( dstrReasonCode, REASONCODELIST01AND04) )
               {
                  ADDCONDITIONFROMFILE( CND::ERR_ENTIRE_ACCT_ASSIGNED );
               }

               if( DSTCommonFunctions::codeInList( dstrReasonCode, REASONCODELIST02030506 ) )
               {
                  ADDCONDITIONFROMFILE( CND::ERR_WARN_ENTIRE_ACCT_ASSIGNED );
               }

               if( DSTCommonFunctions::codeInList( dstrReasonCode, REASONCODELIST07TO08 ) &&
                   DSTCommonFunctions::codeInList( dstrInReason, I_( "05,06")) )
               {
                  ADDCONDITIONFROMFILE( CND::ERR_WARN_ACCT_ASSIGNED_COMMITTEE_POWERATTNY );
               }
            }

            DString strPendingTrade;
            pMFAccount->getField( ifds::PendingTrade, strPendingTrade, idDataGroup, false );
            if( strPendingTrade.strip().upperCase() == YES )
            {
               ADDCONDITIONFROMFILE( CND::ERR_WARN_PENDING_TRADE_EXISTS );
            }

         }

         // change Successor or Beneficiary
         else if( dstrTitleRestrict == YES && dstrTransType == CHG_ENTITY )
         {
            if( DSTCommonFunctions::codeInList( dstrReasonCode, REASONCODELIST01AND04) )
            {
               ADDCONDITIONFROMFILE( CND::ERR_ENTIRE_ACCT_ASSIGNED );
            }
            if( DSTCommonFunctions::codeInList( dstrReasonCode, REASONCODELIST07TO08 ) )
            {
               ADDCONDITIONFROMFILE( CND::ERR_WARN_ACCT_ASSIGNED_COMMITTEE_POWERATTNY );
            }
         }
         else if( dstrTitleRestrict == NO && dstrTransType == CHG_ADD_ESCROW )
         {
            DString strSWPExists;
            pMFAccount->getField( ifds::SWP, strSWPExists, idDataGroup, false );

            if( strSWPExists.strip().upperCase() == YES && DSTCommonFunctions::codeInList( dstrReasonCode, REASONCODELIST01TO06) )
            {
               ADDCONDITIONFROMFILE( CND::ERR_WARN_SWP_STOP_FOR_ESCROW );
            }
         }
         else // Trading, Systematic setup, RRIF set up
         {

            if( dstrTitleRestrict == YES && dstrEscrowFund == NULL_STRING )
            {
               escrowTitleRestrict ( dstrReasonCode, dstrTransType, idDataGroup );   
            }
            else  // non Title Restrict set up or escrow fund is not blank
            {
               if( DSTCommonFunctions::codeInList( dstrReasonCode, REASONCODELIST01TO06) )
               {
                  escrowReason01To06( dstrEscrowFund, dstrTransType, dstrReasonCode, idDataGroup );
               }
               else if( DSTCommonFunctions::codeInList( dstrReasonCode, REASONCODELIST07TO08) )
               {
                  escrowReason07To08( dstrEscrowFund, dstrTransType, idDataGroup );
               }
               else if( dstrReasonCode == I_( "09" ) )
               {
                  escrowReason09( dstrEscrowFund, dstrTransType, idDataGroup );
               }
               else if( dstrEscrowFund == NULL_STRING && _bEscrowBand )
               {
                  // Warning
               }
               escrowReason12To23 (dstrReasonCode, dstrTransType, idDataGroup );
            }
         }
      }

      if( GETCURRENTHIGHESTSEVERITY() > WARNING )
      {
         break;
      }

      ++bfIter;

   } // while

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AccountEntityXref::escrowTitleRestrict( const DString& dstrReasonCode, 
                                                 const DString& dstrTransType, 
                                                 const BFDataGroupId& idDataGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "escrowTitleRestrict" ) );

   /**** Escrow Reason
   01     Bankruptcy
   02     Requirement_to_Pay
   03     Garnishment
   04     Writ_of_Seizure
   05     RSP_Loan
   06     Collateral Assignment
   07     Power of Attorney
   08     Committee
   09     Loan
   10     TD Loan
   11     CESG Return
   *************************/
   DString REASONCODELIST01TO06 = I_( "01,02,03,04,05,06");
   DString REASONCODELIST01TO05 = I_( "01,02,03,04,05");
   DString REASONCODELIST07TO08 = I_( "07,08");
   DString REASONCODELIST01AND04 = I_( "01,04");
   DString REASONCODELIST02AND03 = I_( "02,03");

   if( dstrTransType == REDEMPTION_CODE ||
       dstrTransType == ADMINFEE_CODE ) //allocation only // ALSO FOR SWP
   {
      if( DSTCommonFunctions::codeInList( dstrReasonCode, REASONCODELIST01TO06) )
      {
         ADDCONDITIONFROMFILE( CND::ERR_ENTIRE_ACCT_ASSIGNED );
      }
      else if( DSTCommonFunctions::codeInList( dstrReasonCode, REASONCODELIST07TO08) )
      {
         ADDCONDITIONFROMFILE( CND::ERR_WARN_ACCT_ASSIGNED_COMMITTEE_POWERATTNY );
      }
   }
   if( dstrTransType == PURCHASE_CODE ) // allocation only // ALSO FOR PAC
   {
      if( DSTCommonFunctions::codeInList( dstrReasonCode, REASONCODELIST01AND04) )
      {
         ADDCONDITIONFROMFILE( CND::ERR_ENTIRE_ACCT_ASSIGNED );
      }
      else if( DSTCommonFunctions::codeInList( dstrReasonCode, REASONCODELIST02AND03) )
      {
         ADDCONDITIONFROMFILE( CND::ERR_WARN_ENTIRE_ACCT_ASSIGNED );
      }
   }

   if( dstrTransType == EXCHANGE_OUT_CODE ) // ALSO for automatic transfer
   {
      // Exchange or Auto transfer within the same account
      if( DSTCommonFunctions::codeInList( dstrReasonCode, REASONCODELIST01AND04) )
      {
         ADDCONDITIONFROMFILE( CND::ERR_WARN_ENTIRE_ACCT_ASSIGNED );
      }
      // Feb 25, 2004 - PTS 10017714, as per Title Restrictions Table, the rules are:
      // Event Code = 05 (for Account From = Account To, i.e. Exchange )
      // For Reason Code 01 and 04 -> Warning: Entire Account is restricted
      // For all other Reason Codes, it's informational, with no message
   }

   if( dstrTransType == TRANSFER_OUT_CODE ) // ALSO Transfer
   {
      // Feb 25, 2004 - PTS 10017714, as per Title Restrictions Table, the rules are:
      // Event Code = 25 (for Account From != Account To, i.e. Transfer )
      // For Reason Code 01 and 06 -> Error: Entire Account is restricted
      // For Reason Code 07 and 08 -> Warning: 'To' policy has a Titles Restriction 

      // Transfer give warning for account with Power of Attorney and Committee
      if( DSTCommonFunctions::codeInList( dstrReasonCode, REASONCODELIST07TO08) )
      {
         ADDCONDITIONFROMFILE( CND::ERR_WARN_ACCT_ASSIGNED_COMMITTEE_POWERATTNY );
      }
      else if ( DSTCommonFunctions::codeInList( dstrReasonCode, REASONCODELIST01TO06) )
      {
         ADDCONDITIONFROMFILE( CND::ERR_ENTIRE_ACCT_ASSIGNED );
      }
   }

   if( dstrTransType == TIK_TRF_OUT_CODE ) // ALSO for TIK Transfer
   {
      // Exchange or Auto transfer within the same account
      if( DSTCommonFunctions::codeInList( dstrReasonCode, REASONCODELIST01AND04) )
      {
         ADDCONDITIONFROMFILE( CND::ERR_WARN_ENTIRE_ACCT_ASSIGNED );
      }
   }

   if( dstrTransType == SWP_CHG ) // SWP changed: give warning
   {
      // Exchange or Auto transfer within the same account
      if( DSTCommonFunctions::codeInList( dstrReasonCode, REASONCODELIST01TO06) )
      {
         ADDCONDITIONFROMFILE( CND::ERR_WARN_ENTIRE_ACCT_ASSIGNED );
      }
   }

   if( dstrTransType == RRIF_AWD ) //RRIF, LIF, LRIF automatic withdraw
   {
      if( DSTCommonFunctions::codeInList( dstrReasonCode, REASONCODELIST01TO06) )
      {
         ADDCONDITIONFROMFILE( CND::ERR_WARN_ENTIRE_ACCT_ASSIGNED );
      }
      else if( DSTCommonFunctions::codeInList( dstrReasonCode, REASONCODELIST07TO08) )
      {
         ADDCONDITIONFROMFILE( CND::ERR_WARN_ACCT_ASSIGNED_COMMITTEE_POWERATTNY );
      }
   }

   if( dstrTransType == RRIF_OPT_AWD ) //RRIF, LIF, LRIF Optional withdraw
   {
      if( DSTCommonFunctions::codeInList( dstrReasonCode, REASONCODELIST01TO05 ) )
      {
         ADDCONDITIONFROMFILE( CND::ERR_ENTIRE_ACCT_ASSIGNED );
      }
      else if( DSTCommonFunctions::codeInList( dstrReasonCode, REASONCODELIST07TO08) )
      {
         ADDCONDITIONFROMFILE( CND::ERR_WARN_ACCT_ASSIGNED_COMMITTEE_POWERATTNY );
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AccountEntityXref::escrowReason01To06 ( const DString& dstrEscrowFund, 
                                                 const DString& dstrTransType, 
                                                 const DString& dstrReasonCode, 
                                                 const BFDataGroupId& idDataGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "escrowReason01To06" ) );

   // Incident 728172 -- Raise error or warning base on RejError code 946 when reason code is 01

   if( ( !_bEscrowBand && ( dstrTransType == REDEMPTION_CODE || dstrTransType == ADMINFEE_CODE) ) ||
       ( dstrTransType == REDEMPTION_CODE &&  dstrReasonCode == I_("01") ) )
   {
      getErrMsg ( IFASTERR::ASSIGNMENT_REDEEM_NOT_ALLOW, 
                     CND::ERR_ASSIGNMENT_REDEEM_NOT_ALLOW, 
                     CND::ERR_WARN_ASSIGNMENT_REDEEM_NOT_ALLOW, 
                     idDataGroup); 
      //ADDCONDITIONFROMFILE( CND::ERR_ASSIGNMENT_REDEEM_NOT_ALLOW );
   }
   else
      if( dstrEscrowFund == NULL_STRING && _bEscrowBand )
   {
      ADDCONDITIONFROMFILE( CND::ERR_WARN_ENTIRE_ACCT_ASSIGNED );
   }
   else
      if( _bEscrowBand && dstrTransType == REDEMPTION_CODE )
   {
      ADDCONDITIONFROMFILE( CND::ERR_WARN_ASSIGNMENT_REDEEM_NOT_ALLOW );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AccountEntityXref::escrowReason07To08 (const DString& dstrEscrowFund, 
                                                const DString& dstrTransType, 
                                                const BFDataGroupId& idDataGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "escrowReason07To08" ) );

   if( dstrEscrowFund == NULL_STRING && _bEscrowBand )
   {
      ADDCONDITIONFROMFILE( CND::ERR_WARN_ACCT_ASSIGNED_COMMITTEE_POWERATTNY );
   }
   else
      if( dstrTransType == REDEMPTION_CODE || dstrTransType == ADMINFEE_CODE)
   {
      ADDCONDITIONFROMFILE( CND::ERR_WARN_ASSIGNMENT_REDEEM_NOT_ALLOW );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AccountEntityXref::escrowReason09 (const DString& dstrEscrowFund, 
                                            const DString& dstrTransType, 
                                            const BFDataGroupId& idDataGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "escrowReason09" ) );

   if( dstrEscrowFund == NULL_STRING && _bEscrowBand && 
       ( dstrTransType == REDEMPTION_CODE || dstrTransType == EXCHANGE_OUT_CODE || 
         dstrTransType == TRANSFER_OUT_CODE || dstrTransType == ADMINFEE_CODE ) )
   {
      ADDCONDITIONFROMFILE( CND::ERR_ASSIGNMENT_REDEEM_NOT_ALLOW );
   }
   else if( dstrEscrowFund == NULL_STRING && _bEscrowBand && 
            dstrTransType != REDEMPTION_CODE && dstrTransType != EXCHANGE_OUT_CODE && 
            dstrTransType != TRANSFER_OUT_CODE && dstrTransType != ADMINFEE_CODE)
   {
      ADDCONDITIONFROMFILE( CND::ERR_WARN_ENTIRE_ACCT_ASSIGNED );		
   }
   else if( dstrTransType == REDEMPTION_CODE || dstrTransType == EXCHANGE_OUT_CODE ||
            dstrTransType == TRANSFER_OUT_CODE || dstrTransType == ADMINFEE_CODE)
   {
      ADDCONDITIONFROMFILE( CND::ERR_WARN_ASSIGNMENT_REDEEM_NOT_ALLOW );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AccountEntityXref::escrowReason12To23 (const DString& dstrReasonCode, 
                                                const DString& dstrTransType, 
                                                const BFDataGroupId& idDataGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "escrowReason10" ) );

   DString dstrKey;
   dstrKey = dstrReasonCode + dstrTransType;
   ESCROW_REASON_MAP_ITER iter = _escrowReasonMap.find(dstrKey);
   if ( iter != _escrowReasonMap.end() ) {
      long conditionId = iter->second;
      ADDCONDITIONFROMFILE( conditionId );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void AccountEntityXref::setupEscrowReasons( ) 
{
/* 
   WARN_ACCT_ASSIGNED_PAC_HOLDBACK
   WARN_ACCT_ASSIGNED_CHEQUE_HOLDBACK
   WARN_ACCT_ASSIGNED_CURATEL
   ERR_ACCT_ASSIGNED_COURT_ORDER
   WARN_ACCT_ASSIGNED_CONVERTED
   WARN_ACCT_ASSIGNED_CQ
   WARN_ACCT_ASSIGNED_VDAY
   WARN_ACCT_ASSIGNED_MORTGAGE
   WARN_ACCT_ASSIGNED_DPSP
   WARN_ACCT_ASSIGNED_KEAN
   WARN_ACCT_ASSIGNED_AMCU
   WARN_ACCT_ASSIGNED_MEMO
*/

   // Keyed by Reason code and transaction type.  This key may change in the future.

   _escrowReasonMap.insert ( ESCROW_REASON_MAP_VALUE_TYPE ( I_("12PW"), CND::WARN_ACCT_ASSIGNED_PAC_HOLDBACK ) );
   _escrowReasonMap.insert ( ESCROW_REASON_MAP_VALUE_TYPE ( I_("12TFOUT"), CND::WARN_ACCT_ASSIGNED_PAC_HOLDBACK ) );
   _escrowReasonMap.insert ( ESCROW_REASON_MAP_VALUE_TYPE ( I_("13PW"), CND::WARN_ACCT_ASSIGNED_CHEQUE_HOLDBACK ) );
   _escrowReasonMap.insert ( ESCROW_REASON_MAP_VALUE_TYPE ( I_("13TFOUT"), CND::WARN_ACCT_ASSIGNED_CHEQUE_HOLDBACK ) );
   _escrowReasonMap.insert ( ESCROW_REASON_MAP_VALUE_TYPE ( I_("14PW"), CND::WARN_ACCT_ASSIGNED_CURATEL ) );
   _escrowReasonMap.insert ( ESCROW_REASON_MAP_VALUE_TYPE ( I_("14TFOUT"), CND::WARN_ACCT_ASSIGNED_CURATEL ) );
   _escrowReasonMap.insert ( ESCROW_REASON_MAP_VALUE_TYPE ( I_("15PW"), CND::ERR_ACCT_ASSIGNED_COURT_ORDER ) );
   _escrowReasonMap.insert ( ESCROW_REASON_MAP_VALUE_TYPE ( I_("15TFOUT"), CND::ERR_ACCT_ASSIGNED_COURT_ORDER ) );
   _escrowReasonMap.insert ( ESCROW_REASON_MAP_VALUE_TYPE ( I_("16PW"), CND::WARN_ACCT_ASSIGNED_CONVERTED ) );
   _escrowReasonMap.insert ( ESCROW_REASON_MAP_VALUE_TYPE ( I_("16TFOUT"), CND::WARN_ACCT_ASSIGNED_CONVERTED ) );
   _escrowReasonMap.insert ( ESCROW_REASON_MAP_VALUE_TYPE ( I_("17PW"), CND::WARN_ACCT_ASSIGNED_CQ ) );
   _escrowReasonMap.insert ( ESCROW_REASON_MAP_VALUE_TYPE ( I_("17TFOUT"), CND::WARN_ACCT_ASSIGNED_CQ ) );
   _escrowReasonMap.insert ( ESCROW_REASON_MAP_VALUE_TYPE ( I_("18PW"), CND::WARN_ACCT_ASSIGNED_VDAY ) );
   _escrowReasonMap.insert ( ESCROW_REASON_MAP_VALUE_TYPE ( I_("18TFOUT"), CND::WARN_ACCT_ASSIGNED_VDAY ) );
   _escrowReasonMap.insert ( ESCROW_REASON_MAP_VALUE_TYPE ( I_("19PW"), CND::WARN_ACCT_ASSIGNED_MORTGAGE ) );
   _escrowReasonMap.insert ( ESCROW_REASON_MAP_VALUE_TYPE ( I_("19TFOUT"), CND::WARN_ACCT_ASSIGNED_MORTGAGE ) );
   _escrowReasonMap.insert ( ESCROW_REASON_MAP_VALUE_TYPE ( I_("20PW"), CND::WARN_ACCT_ASSIGNED_DPSP ) );
   _escrowReasonMap.insert ( ESCROW_REASON_MAP_VALUE_TYPE ( I_("20TFOUT"), CND::WARN_ACCT_ASSIGNED_DPSP ) );
   _escrowReasonMap.insert ( ESCROW_REASON_MAP_VALUE_TYPE ( I_("21PW"), CND::WARN_ACCT_ASSIGNED_KEAN ) );
   _escrowReasonMap.insert ( ESCROW_REASON_MAP_VALUE_TYPE ( I_("21TFOUT"), CND::WARN_ACCT_ASSIGNED_KEAN ) );
   _escrowReasonMap.insert ( ESCROW_REASON_MAP_VALUE_TYPE ( I_("22PW"), CND::WARN_ACCT_ASSIGNED_AMCU ) );
   _escrowReasonMap.insert ( ESCROW_REASON_MAP_VALUE_TYPE ( I_("22TFOUT"), CND::WARN_ACCT_ASSIGNED_AMCU ) );
   _escrowReasonMap.insert ( ESCROW_REASON_MAP_VALUE_TYPE ( I_("23PW"), CND::WARN_ACCT_ASSIGNED_MEMO ) );
   _escrowReasonMap.insert ( ESCROW_REASON_MAP_VALUE_TYPE ( I_("23TFOUT"), CND::WARN_ACCT_ASSIGNED_MEMO ) );
   _escrowReasonMap.insert ( ESCROW_REASON_MAP_VALUE_TYPE ( I_("25PW"), CND::WARN_ACCT_ASSIGNED_CDIC_FULL_HOLD ) );
   _escrowReasonMap.insert ( ESCROW_REASON_MAP_VALUE_TYPE ( I_("25TFOUT"), CND::WARN_ACCT_ASSIGNED_CDIC_FULL_HOLD ) );
   _escrowReasonMap.insert ( ESCROW_REASON_MAP_VALUE_TYPE ( I_("26PW"), CND::WARN_ACCT_ASSIGNED_CDIC_PARTIAL_HOLD ) );
   _escrowReasonMap.insert ( ESCROW_REASON_MAP_VALUE_TYPE ( I_("26TFOUT"), CND::WARN_ACCT_ASSIGNED_CDIC_PARTIAL_HOLD ) );
   _escrowReasonMap.insert ( ESCROW_REASON_MAP_VALUE_TYPE ( I_("27PW"), CND::WARN_ACCT_ASSIGNED_MI_FULL_HOLD ) );
   _escrowReasonMap.insert ( ESCROW_REASON_MAP_VALUE_TYPE ( I_("27TFOUT"), CND::WARN_ACCT_ASSIGNED_MI_FULL_HOLD ) );
   _escrowReasonMap.insert ( ESCROW_REASON_MAP_VALUE_TYPE ( I_("28PW"), CND::WARN_ACCT_ASSIGNED_MI_PARTIAL_HOLD ) );
   _escrowReasonMap.insert ( ESCROW_REASON_MAP_VALUE_TYPE ( I_("28TFOUT"), CND::WARN_ACCT_ASSIGNED_MI_PARTIAL_HOLD ) );
}

//******************************************************************************
void AccountEntityXref::AddCopy(DString &orgKey, DString &destKey, const BFDataGroupId& idDataGroup)
{
   AccountEntityXrefObject *pOrgObj = NULL, *pDestObj = NULL;

   for( BFObjIter Iter( *this, idDataGroup ); !Iter.end(); ++Iter )
   {
      if( Iter.getStringKey() == orgKey )
      {
         pOrgObj = dynamic_cast< AccountEntityXrefObject * >( Iter.getObject( ) );
      }
      else if( Iter.getStringKey() == destKey )
      {
         pDestObj = dynamic_cast< AccountEntityXrefObject * >( Iter.getObject( ) );
      }
   }

   if( pOrgObj && pDestObj )
   {

      DString strSeqNum; 
      getValueForTag( destKey, ENTITY_SEQ_NUM_FIELD, strSeqNum );
      pDestObj->ModelOffer(pOrgObj, strSeqNum,  idDataGroup);
   }

}

//******************************************************************************
void AccountEntityXref::getAcctOwnerEntities( ENTITIES_VECTOR & acctOwnerEntities, DString dstrAcctNum, const BFDataGroupId& idDataGroup )
{
   DString strEntityId, strEntityType, searchKey;
   acctOwnerEntities.clear();

   PopulateEntitiesList(idDataGroup, dstrAcctNum);
   BFObjIter bfIter( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED);//, false, true );

   buildPartialKeyForAccount( searchKey, dstrAcctNum );
   bfIter.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey );
   while( !bfIter.end() )
   {
      bfIter.getObject()->getField( ifds::EntityId, strEntityId, idDataGroup );
      bfIter.getObject()->getField( ifds::EntityType, strEntityType, idDataGroup );
      if( strEntityType == ACCOUNTHOLDER_ENTITY_TYPE )
      {
         acctOwnerEntities.push_back( strEntityId );
      }
      ++bfIter;
   }
}

//******************************************************************************
void AccountEntityXref::getClearingPlatformEntities( ENTITIES_VECTOR & clearingPlatformEntities, DString dstrAcctNum, const BFDataGroupId& idDataGroup )
{
   DString strEntityId, strEntityType, searchKey;
   clearingPlatformEntities.clear();

   PopulateEntitiesList(idDataGroup, dstrAcctNum);
   BFObjIter bfIter( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED);//, false, true );

   buildPartialKeyForAccount( searchKey, dstrAcctNum );
   bfIter.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey );
   while( !bfIter.end() )
   {
      bfIter.getObject()->getField( ifds::EntityId, strEntityId, idDataGroup );
      bfIter.getObject()->getField( ifds::EntityType, strEntityType, idDataGroup );
      if( strEntityType == CLEARING_PLATFORM_ENTITY_TYPE )
      {
         clearingPlatformEntities.push_back( strEntityId );
      }
      ++bfIter;
   }
}
//******************************************************************************
void AccountEntityXref::getRESPBeneficiaryEntities( ENTITIES_VECTOR & respBeneficiaryEntities, DString dstrAcctNum, const BFDataGroupId& idDataGroup )
{
   DString strEntityId, strEntityType, searchKey;
   respBeneficiaryEntities.clear();

   PopulateEntitiesList(idDataGroup, dstrAcctNum);
   BFObjIter bfIter( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED);//, false, true );

   buildPartialKeyForAccount( searchKey, dstrAcctNum );
   bfIter.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey );

   while( !bfIter.end() )
   {
      bfIter.getObject()->getField (ifds::EntityId, strEntityId, idDataGroup);
      bfIter.getObject()->getField (ifds::EntityType, strEntityType, idDataGroup);

      if( strEntityType == RESP_BENEFICIARY_ENTITY_TYPE )
      {
         respBeneficiaryEntities.push_back (strEntityId);
      }

      ++bfIter;
   }
}

//******************************************************************************
SEVERITY AccountEntityXref::GetEntitySeqNumber( const BFDataGroupId& idDataGroup, 
                                                const DString& AccountNum, 
                                                const DString& EntityId,  
                                                DString& seqNumber)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("GetEntitySeqNumber"));

   DString searchKey, strEntityId;

   PopulateEntitiesList(idDataGroup, AccountNum);
   BFObjIter bfIter( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED);

   buildPartialKeyForAccount( searchKey, AccountNum );
   bfIter.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey );

   while( !bfIter.end() )
   {
      bfIter.getObject()->getField (ifds::EntityId, strEntityId, idDataGroup);

      if( strEntityId ==  EntityId)
      {

         bfIter.getObject()->getField (ifds::SeqNumber, seqNumber, idDataGroup);

         break;
      }

      ++bfIter;
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AccountEntityXref::GetRESPEntityInfo( const DString& dstrAcctNum, 
                                               const BFDataGroupId& idDataGroup, 
                                               const DString& dstrEntityId,
                                               DString& dstrRESPAllocPrcnt,
                                               DString& dstrBenefDofBirth,
                                               DString& dstrHRDCRelateCode,
                                               DString& dstrTaxJuris,
                                               DString& dstrEffectiveDate)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("GetRESPEntityInfo"));

   DString searchKey, strEntityId;

   PopulateEntitiesList(idDataGroup, dstrAcctNum);
   BFObjIter bfIter (*this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED);

   buildPartialKeyForAccount( searchKey, dstrAcctNum );
   bfIter.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey );

   while( !bfIter.end() )
   {
      bfIter.getObject()->getField (ifds::EntityId, strEntityId, idDataGroup);

      if (strEntityId == dstrEntityId)
      {
         Entity *pEntity (NULL);
         if ( getWorkSession().getEntity (idDataGroup, strEntityId, pEntity) <= WARNING && 
              pEntity)
         {
            bfIter.getObject()->getField (ifds::BenPercentage, dstrRESPAllocPrcnt, idDataGroup);
            bfIter.getObject()->getField (ifds::HRDCRelateCode, dstrHRDCRelateCode, idDataGroup);
            pEntity->getField (ifds::DofBirth, dstrBenefDofBirth, idDataGroup);
            pEntity->getField (ifds::TaxJuris, dstrTaxJuris, idDataGroup);
            pEntity->getField (ifds::EffectiveDate, dstrEffectiveDate, idDataGroup);
         }
         break;
      }

      ++bfIter;
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AccountEntityXref::getEntityTaxJuris (const DString& dstrAcctNum, 
                                               const BFDataGroupId& idDataGroup, 
                                               const DString& dstrEntityId,
                                               DString& dstrTaxJuris)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getEntityTaxJuris"));

   DString searchKey, strEntityId;

   PopulateEntitiesList(idDataGroup, dstrAcctNum);
   BFObjIter bfIter (*this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED);

   buildPartialKeyForAccount( searchKey, dstrAcctNum );
   bfIter.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey );

   while( !bfIter.end() )
   {
      bfIter.getObject()->getField (ifds::EntityId, strEntityId, idDataGroup);

      if (strEntityId == dstrEntityId)
      {
         Entity *pEntity (NULL);
         if ( getWorkSession().getEntity (idDataGroup, strEntityId, pEntity) <= WARNING && 
              pEntity)
         {
            pEntity->getField (ifds::TaxJuris, dstrTaxJuris, idDataGroup);
         }
         break;
      }

      ++bfIter;
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void AccountEntityXref::getFormerSpouses( ENTITIES_VECTOR & formerSpouseEntities, 
                                          DString dstrAcctNum, 
                                          const BFDataGroupId& idDataGroup )
{
   DString strEntityId, strEntityType, searchKey;
   formerSpouseEntities.clear();

   PopulateEntitiesList(idDataGroup, dstrAcctNum);
   BFObjIter bfIter( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED);//, false, true );

   buildPartialKeyForAccount( searchKey, dstrAcctNum );
   bfIter.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey );
   while( !bfIter.end() )
   {
      bfIter.getObject()->getField( ifds::EntityId, strEntityId, idDataGroup );
      bfIter.getObject()->getField( ifds::EntityType, strEntityType, idDataGroup );
      if( strEntityType == FORMER_SPOUSE_ENTITY_TYPE )
      {
         formerSpouseEntities.push_back( strEntityId );
      }
      ++bfIter;
   }
}

//******************************************************************************
void AccountEntityXref::getBeneficiaries(  ACCTENTITYOBJ_VECTOR & vBenefEntities, DString dstrAcctNum, const BFDataGroupId& idDataGroup )
{
   AccountEntityXrefObject *pAccountEntityXrefObject = NULL;
   DString strEntityId, strEntityType, searchKey;
   vBenefEntities.clear();

   PopulateEntitiesList(idDataGroup, dstrAcctNum);
   BFObjIter bfIter( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED);//, false, true );

   buildPartialKeyForAccount( searchKey, dstrAcctNum );
   bfIter.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey );
   while( !bfIter.end() )
   {
      bfIter.getObject()->getField( ifds::EntityType, strEntityType, idDataGroup );
      if( strEntityType == PRIMARY_BENEF_ENTITY_TYPE || strEntityType == SECONDARY_BENEF_ENTITY_TYPE )
      {
         pAccountEntityXrefObject = dynamic_cast < AccountEntityXrefObject * > ( bfIter.getObject() );
         vBenefEntities.push_back( pAccountEntityXrefObject );
      }
      ++bfIter;
   }
}

//******************************************************************************
void AccountEntityXref::getAnnitants( ACCTENTITYOBJ_VECTOR & vAnnitantEntities, 
                                      DString dstrAcctNum, 
                                      const BFDataGroupId& idDataGroup )
{
   AccountEntityXrefObject *pAccountEntityXrefObject = NULL;
   DString strEntityId, strEntityType, searchKey;
   vAnnitantEntities.clear();

   PopulateEntitiesList(idDataGroup, dstrAcctNum);
   BFObjIter bfIter( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED);//, false, true );

   buildPartialKeyForAccount( searchKey, dstrAcctNum );
   bfIter.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey );
   while( !bfIter.end() )
   {
      bfIter.getObject()->getField( ifds::EntityType, strEntityType, idDataGroup );
      if( strEntityType == ANNUITANT_ENTITY_TYPE )
      {
         pAccountEntityXrefObject = dynamic_cast < AccountEntityXrefObject * > ( bfIter.getObject() );
         vAnnitantEntities.push_back( pAccountEntityXrefObject );
      }
      ++bfIter;
   }
}

//******************************************************************************
void AccountEntityXref::getAcctOwners( ACCTENTITYOBJ_VECTOR & vAcctOwnerEntities, 
                                       DString dstrAcctNum, 
                                       const BFDataGroupId& idDataGroup )
{
   AccountEntityXrefObject *pAccountEntityXrefObject = NULL;
   DString strEntityId, strEntityType, searchKey;
   vAcctOwnerEntities.clear();

   PopulateEntitiesList(idDataGroup, dstrAcctNum);
   BFObjIter bfIter( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED);//, false, true );

   buildPartialKeyForAccount( searchKey, dstrAcctNum );
   bfIter.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey );
   while( !bfIter.end() )
   {
      bfIter.getObject()->getField( ifds::EntityType, strEntityType, idDataGroup );
      if( strEntityType == ACCOUNTHOLDER_ENTITY_TYPE )
      {
         pAccountEntityXrefObject = dynamic_cast < AccountEntityXrefObject * > ( bfIter.getObject() );
         vAcctOwnerEntities.push_back( pAccountEntityXrefObject );
      }
      ++bfIter;
   }
}


//******************************************************************************

void AccountEntityXref::cloneAcctEntityXrefFromModel( const DString& modelAccountNum, 
                                                      const DString& newAccountNum, 
                                                      const BFDataGroupId& idDataGroup )
{
   // Clone Entity 01 and 21 of the matching account

   BFObjIter xrefIter( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );

   //build the key to retrieve the account holder sequence 1 for the model account

   DString strKey;
   buildPartialKeyForAccount( strKey, modelAccountNum );

   //If system supports Master Account - AMS Model C, copy all of AccountEntityXrefObject belong to model account
   //to new account (all of entitytypes and sequences) - except ESCROW_REPREZENTATIVE_ENTITY_TYPE.
   DString dstrMstrActActive, dstrCSSStopSINMatch;
   bool doesSupportMstrActAMSC = false;
   if (getWorkSession().getOption(ifds::MstrActActive, dstrMstrActActive, BF::HOST, false) <= WARNING &&
	   getWorkSession().getOption(ifds::CSSStopSINMatch, dstrCSSStopSINMatch, BF::HOST, false) <= WARNING)
   { 
       doesSupportMstrActAMSC = dstrMstrActActive == Y && dstrCSSStopSINMatch == Y;
   }
   //

   MFAccount *pModelAccount = NULL; 
   bool modelAccountAttachedAMSC = false;

   for( xrefIter.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, strKey ); !xrefIter.end(); ++xrefIter )
   {
	   DString copyAcctNum = modelAccountNum;
	   DString dstrEntityAcct = NULL_STRING;

	   // check if the object belongs to the account that is to cloned
	   xrefIter.getObject()->getField( ifds::AccountNum, dstrEntityAcct, idDataGroup );
	   if( dstrEntityAcct.strip().stripLeading('0')  == copyAcctNum.strip().stripLeading('0') )
	   {
		   DString dstrEntityType = NULL_STRING;
		   xrefIter.getObject()->getField( ifds::EntityType, dstrEntityType, idDataGroup );

		   if (doesSupportMstrActAMSC && dstrEntityType != ESCROW_REPREZENTATIVE_ENTITY_TYPE)
		   {
			   DString entityId, strFirstName, strLastName, seqNumber;
			   Entity* pEntity = NULL;

			   xrefIter.getObject()->getField( ifds::EntityId, entityId, idDataGroup ); 

			   if( getWorkSession().getEntity( idDataGroup, entityId, pEntity ) <= WARNING && pEntity)
			   {
				   AccountEntityXrefObject* pAccountEntityXrefObject = NULL;

				   xrefIter.getObject()->getField( ifds::EntityId, entityId, idDataGroup );
				   xrefIter.getObject()->getField( ifds::SeqNumber, seqNumber, idDataGroup );
				   xrefIter.getObject()->getField( ifds::FirstName, strFirstName, idDataGroup );
				   xrefIter.getObject()->getField( ifds::LastName, strLastName, idDataGroup );

				   setCurrentAccounNum( newAccountNum );
				   LinkEntity( newAccountNum, dstrEntityType, seqNumber, 
					   entityId, idDataGroup, pAccountEntityXrefObject );

				   pAccountEntityXrefObject->setField( ifds::AccountNum, newAccountNum, idDataGroup );
				   pAccountEntityXrefObject->setField( ifds::EntityType, dstrEntityType, idDataGroup );
				   pAccountEntityXrefObject->setField( ifds::SeqNumber, seqNumber, idDataGroup );
				   pAccountEntityXrefObject->setField( ifds::FirstName, strFirstName, idDataGroup );
				   pAccountEntityXrefObject->setField( ifds::LastName, strLastName, idDataGroup );

				   // *These three fields below will not be linked to the new account - just copy.
				   if (dstrEntityType == PRIMARY_BENEF_ENTITY_TYPE || 
					   dstrEntityType == SECONDARY_BENEF_ENTITY_TYPE || 
					   dstrEntityType == SUCCESSOR_ENTITY_TYPE)
				   {
						DString dstrRelateCode, dstrBenPercentage, dstrIrrevocable;

						xrefIter.getObject()->getField( ifds::RelateCode,    dstrRelateCode,    idDataGroup);
						xrefIter.getObject()->getField( ifds::BenPercentage, dstrBenPercentage, idDataGroup);
						xrefIter.getObject()->getField( ifds::Irrevocable,   dstrIrrevocable,   idDataGroup);

						pAccountEntityXrefObject->setField( ifds::RelateCode,    dstrRelateCode,    idDataGroup);
						pAccountEntityXrefObject->setField( ifds::BenPercentage, dstrBenPercentage, idDataGroup);
						pAccountEntityXrefObject->setField( ifds::Irrevocable,   dstrIrrevocable,   idDataGroup);
				   }
			   }
		   }
		   else if( dstrEntityType == ACCOUNTHOLDER_ENTITY_TYPE || dstrEntityType == NOMINEE_OWNER_ENTITY_TYPE )
		   {// if account owner or nominee owner, then clone
			   DString entityId, seqNumber;
			   Entity* entity;
			   xrefIter.getObject()->getField( ifds::EntityId, entityId, idDataGroup );           
			   if( getWorkSession().getEntity( idDataGroup, entityId, entity ) <= WARNING )
			   {
				   //deal with rule number one
				   AccountEntityXrefObject* pAccountEntityXrefObject = NULL;

				   xrefIter.getObject()->getField( ifds::EntityId, entityId, idDataGroup );
				   xrefIter.getObject()->getField( ifds::SeqNumber, seqNumber, idDataGroup );

				   if ( seqNumber == I_("1") ) // Only the entity with the seqNumber 1 should be set as the new account's owner
				   {
					   DString strFirstName, strLastName;
					   xrefIter.getObject()->getField( ifds::FirstName, strFirstName, idDataGroup );
					   xrefIter.getObject()->getField( ifds::LastName, strLastName, idDataGroup );

					   //link the initial enity to the new account as account owner
					   setCurrentAccounNum( newAccountNum );
					   LinkEntity( newAccountNum, NULL_STRING, NULL_STRING, 
						   entityId, idDataGroup, pAccountEntityXrefObject );
					   //although it looks odd, we need this for having the object updated so the trxn builder will built it
					   pAccountEntityXrefObject->setField( ifds::AccountNum, newAccountNum, idDataGroup );
					   pAccountEntityXrefObject->setField( ifds::EntityType, dstrEntityType, idDataGroup );
					   pAccountEntityXrefObject->setField( ifds::SeqNumber, seqNumber, idDataGroup );

					   pAccountEntityXrefObject->setField( ifds::FirstName, strFirstName, idDataGroup );
					   pAccountEntityXrefObject->setField( ifds::LastName, strLastName, idDataGroup );
				   }
			   }  // if getEntity successful
		   }     // if entity is account owner or nominee
	   }
   }        // for
}


//******************************************************************************
void AccountEntityXref::getSpouse(  ACCTENTITYOBJ_VECTOR & vSpouseEntitiesVector, DString dstrAcctNum, bool bSpouse, const BFDataGroupId& idDataGroup )
{
   AccountEntityXrefObject *pAccountEntityXrefObject = NULL;
   DString strEntityId, strEntityType, searchKey;
   vSpouseEntitiesVector.clear();

   PopulateEntitiesList(idDataGroup, dstrAcctNum);
   BFObjIter bfIter( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED);//, false, true );

   buildPartialKeyForAccount( searchKey, dstrAcctNum );
   bfIter.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey );
   while( !bfIter.end() )
   {
      bfIter.getObject()->getField( ifds::EntityType, strEntityType, idDataGroup );
      if( bSpouse && (strEntityType == SPOUSAL_CONTRIBUTOR_ENTITY_TYPE || strEntityType == SPOUSE_NON_CONTRIBUTOR_ENTITY_TYPE) )
      {
         pAccountEntityXrefObject = dynamic_cast < AccountEntityXrefObject * > ( bfIter.getObject() );
         vSpouseEntitiesVector.push_back( pAccountEntityXrefObject );
         return;
      }
      else
         if( !bSpouse && strEntityType == SPOUSAL_TRANSFEREE_ENTITY_TYPE )
      {
         pAccountEntityXrefObject = dynamic_cast < AccountEntityXrefObject * > ( bfIter.getObject() );
         vSpouseEntitiesVector.push_back( pAccountEntityXrefObject );
         return;
      }
      ++bfIter;
   }
}

//******************************************************************************
void AccountEntityXref::SetChildrenSpousalNameSubSet( const BFDataGroupId& idDataGroup, bool setdefault )
{
   DString strEntityType, strFirstName, strLastName, strEntityID;
   DString SpousalNameSubSet = I_("0= ;");   
   
   DString FSpouseEntity=NULL_STRING;

   BFObjIter bfIter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED, false );
   bfIter.begin();
   while( !bfIter.end() )
   {         
         bfIter.getObject()->getField( ifds::EntityType, strEntityType, idDataGroup, false );
         bfIter.getObject()->getField( ifds::EntityId, strEntityID, idDataGroup, false );
		 if(strEntityType.strip() == OWNER_SPOUSAL) 
		 {
		     Entity* pEntity;
		     if( getWorkSession().getEntity( idDataGroup, strEntityID, pEntity ) <= WARNING )
			 {
				 pEntity->getField( ifds::FirstName, strFirstName, idDataGroup, false );
				 pEntity->getField( ifds::LastName, strLastName, idDataGroup, false );
			 }			 

			 if( strLastName.strip() != NULL_STRING )
			 {				 
				 SpousalNameSubSet += strEntityID.strip();
				 SpousalNameSubSet += I_("=");
				 SpousalNameSubSet += strFirstName.strip();
				 SpousalNameSubSet += I_(" ");
				 SpousalNameSubSet += strLastName.strip();
				 SpousalNameSubSet += I_(";");

				 if(FSpouseEntity == NULL_STRING) 
					 FSpouseEntity = strEntityID;
			 }
		 }

      ++bfIter;
   }

   bfIter.begin();
   while( !bfIter.end() )
   {
      bfIter.getObject()->getField( ifds::EntityType, strEntityType, idDataGroup, false );
      if(strEntityType.strip() == I_( "01" )) 
      {
         dynamic_cast < AccountEntityXrefObject* > (bfIter.getObject())->SetSpousalEntityNameSubSet( idDataGroup, SpousalNameSubSet, FSpouseEntity, setdefault );
      }

      ++bfIter;
   }

}

//******************************************************************************
DString AccountEntityXref::getNextCount()
{
   return asString( ++_iNewCount );
}

//******************************************************************************
DString AccountEntityXref::getPrevCount()
{
   return asString( --_iNewCount );
}

//*******************************************************************************
int AccountEntityXref::getCurrentCount()
{
   return _iNewCount;
}

//********************************************************************************
DString AccountEntityXref::getStrCurrentCount()
{
   return asString( _iNewCount );
}

//******************************************************************************
SEVERITY AccountEntityXref::doDeleteObject ( const DString & strKey, const BFDataGroupId& idDataGroup, bool bIsObjectDestroyed ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "doDeleteObject" ) );

   AccountEntityXrefObject* pObjDelete = 
                           dynamic_cast<AccountEntityXrefObject*>(getObject(strKey, idDataGroup) );

   if (pObjDelete)
   {
      DString dstrEntityType, dstrEntityID, dstrSeqNumber;

      pObjDelete->getField( ifds::EntityType, dstrEntityType, idDataGroup, false );
      pObjDelete->getField( ifds::EntityId, dstrEntityID, idDataGroup, false );
      pObjDelete->getField(ifds::SeqNumber, dstrSeqNumber, idDataGroup, false);

      dstrEntityType.strip();
      dstrEntityID.stripLeading('0');

      if ( getWorkSession ().isRES2Client() )
      { 
         if ( dstrEntityType == RESP_PCG_INDIV_ENTITY_TYPE || dstrEntityType == RESP_PCG_INST_ENTITY_TYPE ||
              dstrEntityType == PARENT_GUARDIAN_ENTITY_TYPE || dstrEntityType == RESP_DESIGNATED_INSTIT_ENTITY_TYPE )
         {
            setRESPSelectableFieldSubSet(dstrEntityType, strKey, idDataGroup);
         }
      }

      if (dstrEntityType == ACCOUNT_OWNER || dstrEntityType == ITF_INDIVIDUAL_ENTITY_TYPE)
      {
          updateAssociateEntityForAllRelatedPartyEntities(idDataGroup, dstrEntityType, dstrSeqNumber);
      }
	  updateVerifyStatForDeletion(idDataGroup);

   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void AccountEntityXref::setRESPSelectableFieldSubSet( const DString& entityType,
                                                      const DString& strDeletedKey,
                                                      const BFDataGroupId& idDataGroup )
{
   DString strEntityType, strFirstName, strLastName, strEntityID, strSeqNumber;
   DString fieldSubSetBgn = I_("0= ;");
   DString fieldSubSet,fieldSubSet1,fieldSubSet2;

   BFObjIter bfIter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED, false );
   //BFObjIter bfIter( *this, idDataGroup );   

   if ( entityType == RESP_PCG_INDIV_ENTITY_TYPE || entityType == RESP_PCG_INST_ENTITY_TYPE )
   {
      bfIter.begin();
      while( !bfIter.end() )
      {
         BFObjectKey objKey = bfIter.getKey();
         bfIter.getObject()->getField( ifds::EntityType, strEntityType, idDataGroup, false );
         bfIter.getObject()->getField( ifds::EntityId, strEntityID, idDataGroup, false );
         bfIter.getObject()->getField( ifds::SeqNumber, strSeqNumber, idDataGroup, false );
         strEntityType.strip().upperCase();
         
         bool isDeleted = ( objKey.getActivity() == OBJ_ACTIVITY_DELETED );

         if(strEntityType.strip() == RESP_PCG_INDIV_ENTITY_TYPE /* && !isDeleted */) 
         {
            Entity* pEntity;
            if( getWorkSession().getEntity( idDataGroup, strEntityID, pEntity ) <= WARNING )
            {
               pEntity->getField( ifds::FirstName, strFirstName, idDataGroup, false );
               pEntity->getField( ifds::LastName, strLastName, idDataGroup, false );
            }

            if( strLastName.strip() != NULL_STRING )
            {
               fieldSubSet1 += strEntityID.strip();
               fieldSubSet1 += I_("=");
               fieldSubSet1 += strLastName.strip();
               if ( strFirstName.strip() != NULL_STRING )
               {
                  fieldSubSet1 += I_(", ");
                  fieldSubSet1 += strFirstName.strip();
               }
               fieldSubSet1 += I_(";");
            }
         }

         ++bfIter;
      }

      bfIter.begin();
      while( !bfIter.end() )
      {
         BFObjectKey objKey = bfIter.getKey();
         bfIter.getObject()->getField( ifds::EntityType, strEntityType, idDataGroup, false );
         bfIter.getObject()->getField( ifds::EntityId, strEntityID, idDataGroup, false );
         bfIter.getObject()->getField( ifds::SeqNumber, strSeqNumber, idDataGroup, false );
         strEntityType.strip().upperCase();

         bool isDeleted = ( objKey.getActivity() == OBJ_ACTIVITY_DELETED );

         if(strEntityType.strip() == RESP_PCG_INST_ENTITY_TYPE /* && !isDeleted */ ) 
         {
            Entity* pEntity;
            if( getWorkSession().getEntity( idDataGroup, strEntityID, pEntity ) <= WARNING )
            {
               pEntity->getField( ifds::FirstName, strFirstName, idDataGroup, false );
               pEntity->getField( ifds::LastName, strLastName, idDataGroup, false );
            }

            if( strLastName.strip() != NULL_STRING )
            {
               fieldSubSet2 += strEntityID.strip();
               fieldSubSet2 += I_("=");
               fieldSubSet2 += strLastName.strip();
               if ( strFirstName.strip() != NULL_STRING )
               {
                  fieldSubSet2 += I_(", ");
                  fieldSubSet2 += strFirstName.strip();
               }
               fieldSubSet2 += I_(";");
            }
         }

         ++bfIter;
      }

      fieldSubSet1 = fieldSubSet1 + fieldSubSet2;
   }
   else
   {
      bfIter.begin();
      while( !bfIter.end() )
      {
         BFObjectKey objKey = bfIter.getKey();      
         bfIter.getObject()->getField( ifds::EntityType, strEntityType, idDataGroup, false );
         bfIter.getObject()->getField( ifds::EntityId, strEntityID, idDataGroup, false );
         bfIter.getObject()->getField( ifds::SeqNumber, strSeqNumber, idDataGroup, false );
         strEntityType.strip().upperCase();
         
         if(strEntityType.strip() == entityType) 
         {
            Entity* pEntity;
            if( getWorkSession().getEntity( idDataGroup, strEntityID, pEntity ) <= WARNING )
            {
               pEntity->getField( ifds::FirstName, strFirstName, idDataGroup, false );
               pEntity->getField( ifds::LastName, strLastName, idDataGroup, false );
            }

            if( strLastName.strip() != NULL_STRING )
            {
               if ( strEntityType == PARENT_GUARDIAN_ENTITY_TYPE || 
                    strEntityType == RESP_DESIGNATED_INSTIT_ENTITY_TYPE )
               {
                  fieldSubSet1 += strSeqNumber.strip();
                  fieldSubSet1 += I_("=");
                  fieldSubSet1 += strLastName.strip();
                  if ( strFirstName.strip() != NULL_STRING )
                  {
                     fieldSubSet1 += I_(", ");
                     fieldSubSet1 += strFirstName.strip();
                  }
                  fieldSubSet1 += I_(";");
               }
            }
         }

         ++bfIter;
      }
   }

   fieldSubSet = fieldSubSetBgn + fieldSubSet1;

   // If there is deleted entity, delete it from list
   if ( strDeletedKey != NULL_STRING )
   {
      // get entity list to find RESP entity
      BFObjIter iterRESPFind ( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED ); 
      
      iterRESPFind.begin();
      while ( !iterRESPFind.end() )
      {
         AccountEntityXrefObject* pRESPFindXrefObj = NULL;
         DString dstrRESPFindEnityType;
         pRESPFindXrefObj = dynamic_cast<AccountEntityXrefObject*>(iterRESPFind.getObject());
         pRESPFindXrefObj->getField(ifds::EntityType, dstrRESPFindEnityType, idDataGroup);

         if ( dstrRESPFindEnityType.strip() == RESP_BENEFICIARY_ENTITY_TYPE )
         {
            // create deleted object
            BFObjIter iterDelete ( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED ); 
            iterDelete.positionByKey( strDeletedKey );
            AccountEntityXrefObject* pDeletedXrefObj = dynamic_cast<AccountEntityXrefObject*>(iterDelete.getObject());
            
            DString dstrRESPLinkTo, dstrDeletedEntityId, dstrSeqNumber;
            pDeletedXrefObj->getField(ifds::EntityId, dstrDeletedEntityId, idDataGroup);
            pDeletedXrefObj->getField(ifds::SeqNumber, dstrSeqNumber, idDataGroup);
            
            // check the deleted entitytype
            if( entityType == PARENT_GUARDIAN_ENTITY_TYPE )
            {
               pRESPFindXrefObj->getField(ifds::RES2ParentLglList, dstrRESPLinkTo, idDataGroup, false);
               if ( dstrSeqNumber == dstrRESPLinkTo.strip() )
               {
                  pRESPFindXrefObj->setField(ifds::RES2ParentLglList, 0, idDataGroup, true);
               }        
               
               // delete item from sublist
               fieldSubSet = removeItemFromSubtList( fieldSubSet, dstrSeqNumber );
                  
            }
            else if ( entityType == RESP_DESIGNATED_INSTIT_ENTITY_TYPE )
            {
               pRESPFindXrefObj->getField(ifds::RES2DesInstList, dstrRESPLinkTo, idDataGroup, false);
               if ( dstrSeqNumber == dstrRESPLinkTo.strip() )
               {
                  pRESPFindXrefObj->setField(ifds::RES2DesInstList, 0, idDataGroup, true);
               }           
               // delete item from sublist
               fieldSubSet = removeItemFromSubtList( fieldSubSet, dstrSeqNumber );
            }
            else if ( entityType == RESP_PCG_INDIV_ENTITY_TYPE ||
                      entityType == RESP_PCG_INST_ENTITY_TYPE )
            {
               // do nothing
               // delete item from sublist
               fieldSubSet = removeItemFromSubtList( fieldSubSet, dstrDeletedEntityId );
            }

         
         }
         ++iterRESPFind;
      }      

   }

   //bool bSubstitutionSetEmpty = true;
   //I_CHAR *temp = const_cast < I_CHAR* > ( fieldSubSet.c_str() );
   //while( *temp != '\0' )
   //{
   //   DString strTag, strValue;
   //   temp = parseIdiString( temp, strTag, strValue );

   //   if ( strTag == I_("0"))
   //   {
   //      continue;
   //   }
   //   else
   //   {
   //      bSubstitutionSetEmpty = false;
   //   }
   //}

   bfIter.begin();
   while( !bfIter.end() )
   {
      bfIter.getObject()->getField( ifds::EntityType, strEntityType, idDataGroup, false );
      if(strEntityType.strip() == RESP_BENEFICIARY_ENTITY_TYPE /*&& !bSubstitutionSetEmpty*/ ) 
      {
         AccountEntityXrefObject* pObj = 
            dynamic_cast < AccountEntityXrefObject* > (bfIter.getObject());
         pObj->setFieldSubSetForRESPEntity( entityType, fieldSubSet, idDataGroup);

         DString strGrantExists;
         pObj->getField( ifds::GrantExists, strGrantExists, idDataGroup, false );
         strGrantExists.strip().upperCase();
   
         if (strGrantExists == I_("Y"))
         {
            pObj->setFieldReadOnly( ifds::RES2PCGList, idDataGroup, true );
         }
         else
         {
            pObj->setFieldReadOnly( ifds::RES2PCGList, idDataGroup, false );
         }
      }

      ++bfIter;
   }
}

//******************************************************************************
SEVERITY AccountEntityXref::duplicateSINErrorWarning(const DString& strEntityID1,
                                                     const DString& strEntityID2,
                                                     const BFDataGroupId&  idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "duplicateSINErrorWarning" ) );

   AccountEntityXref *pAccountEntityXref = dynamic_cast < AccountEntityXref * > ( this );

   if (pAccountEntityXref)
   {
      BFObjIter iterAccountEntityXrefOut (*pAccountEntityXref, 
                                           idDataGroup, 
                                           true, 
                                           BFObjIter::ITERTYPE::NON_DELETED);

      DString strEntityTypeFrm, strEntityTypeFrmFmt, strEntityIdFrm;
      DString strEntityTypeTo, strEntityTypeToFmt, strEntityIdTo;

      iterAccountEntityXrefOut.begin ();
      while (!iterAccountEntityXrefOut.end())
      {
         AccountEntityXrefObject* pObj = 
            dynamic_cast<AccountEntityXrefObject*>(iterAccountEntityXrefOut.getObject());

         pObj->getField (ifds::EntityType, strEntityTypeFrm, idDataGroup, false);
         pObj->getField (ifds::EntityType, strEntityTypeFrmFmt, idDataGroup, true);
         pObj->getField (ifds::EntityId, strEntityIdFrm, idDataGroup, false);
         strEntityIdFrm.strip().upperCase();

         if (strEntityIdFrm == strEntityID1)
         {
            break;
         }
         ++iterAccountEntityXrefOut;
      }

      iterAccountEntityXrefOut.begin ();
      while (!iterAccountEntityXrefOut.end())
      {
         AccountEntityXrefObject* pObj = 
            dynamic_cast<AccountEntityXrefObject*>(iterAccountEntityXrefOut.getObject());

         pObj->getField (ifds::EntityType, strEntityTypeTo, idDataGroup, false);
         pObj->getField (ifds::EntityType, strEntityTypeToFmt, idDataGroup, true);
         pObj->getField (ifds::EntityId, strEntityIdTo, idDataGroup, false);
         strEntityIdTo.strip().upperCase();

         if (strEntityIdTo == strEntityID2)
         {
            break;
         }
         ++iterAccountEntityXrefOut;
      }


      DString dstrTemp;
      addIDITagValue( dstrTemp, I_("ENTITY_1"), strEntityTypeFrmFmt );
      addIDITagValue( dstrTemp, I_("ENTITY_2"), strEntityTypeToFmt );

      getErrMsg ( IFASTERR::DUPLICATE_SIN, 
                  CND::ERR_SIN_NUMBER_SAME_ENTITY_1_ENTITY_2, 
                  CND::WARN_SIN_NUMBER_SAME_ENTITY_1_ENTITY_2, 
                  idDataGroup,
                  dstrTemp); 
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//**********************************************************************************************************************
SEVERITY AccountEntityXref::getEntityMasterListAsOfDate (DString &entityAsOfDateList,
                                                         const DString &entityType,
                                                         const BFDataGroupId &idDataGroup,                                                                                                                 
                                                         const DString &strAsOfDate,
                                                         const bool &formatComma,
                                                         const DString &accountNum)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getEntityMasterListAsOfDate" ) );   	

   // This method is created for create entity list for put into substitution set by on the fly
   // Default of strAsOfDate is NULL_STRING, default of format is 0(zero)
   // if strAsOfDate is NULL_STRING, meaning is get all entity
   // if formatComma is true, name string will be Lastname, Firstname
   // if formatComma is false, name string will be Firstname Lastname  
   // account num can be NULL_STRING if we can ensure that threre is only AcctEntXref for only 1 account
   // but some screen, eg. trade. Some scenario it hold AcctEntXref for many accounts

   ENTITIES_VECTOR entityList;
   BFObjIter bfIter( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );
   // build partial key for entitytype
   DString searchKey;

   buildPartialKeyForEntityType( searchKey, entityType );

	bfIter.begin(OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey);

   while(!bfIter.end())
   {
      DString dstrEntityType;
      bfIter.getObject()->getField(ifds::EntityType, dstrEntityType, idDataGroup, false);
      dstrEntityType.strip();
      // ensure the entitytype
      if( dstrEntityType == entityType )
      {         
                  // do not get the effective date in this loop, 
         // because not sure effectivedate is set to AcctXrefObj but It's set to Entity for sure.
         DString dstrEntityId;
         bfIter.getObject()->getField(ifds::EntityId, dstrEntityId, idDataGroup, false);
         if (accountNum != NULL_STRING)
         {
            DString dstrAccountNum;
            bfIter.getObject()->getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);
            dstrAccountNum.stripLeading('0');
            if( accountNum == dstrAccountNum )
            {
               entityList.push_back (dstrEntityId);
            }
         }
         else
            entityList.push_back (dstrEntityId);
      }
      ++bfIter;
   }
   // create entity as of date list
   for (ENTITIES_VECTOR::size_type i = 0; i < entityList.size(); ++i)
   {
      DString dstrEntityId, 
              dstrFirstName, 
              dstrLastName;

      dstrEntityId = entityList [i];
      Entity *pEntity = NULL;

      if  (getWorkSession().getEntity (idDataGroup, dstrEntityId, pEntity) <= WARNING && pEntity)
      {
         bool bPutInList = false;
         if (strAsOfDate != NULL_STRING)
         {
            // check as of date
            DString dstrEntityEffectiveDate;
            pEntity->getField(ifds::EffectiveDate, dstrEntityEffectiveDate, idDataGroup, false);
            if( DSTCommonFunctions::CompareDates( strAsOfDate, dstrEntityEffectiveDate ) == DSTCommonFunctions::EQUAL ||
                DSTCommonFunctions::CompareDates( strAsOfDate, dstrEntityEffectiveDate ) == DSTCommonFunctions::SECOND_EARLIER )
            {
               bPutInList = true;
               pEntity->getField( ifds::LastName, dstrLastName, idDataGroup, false );
               pEntity->getField( ifds::FirstName, dstrFirstName, idDataGroup, false );
            }
         }
         else
         {
            bPutInList = true;
            pEntity->getField( ifds::LastName, dstrLastName, idDataGroup, false );
            pEntity->getField( ifds::FirstName, dstrFirstName, idDataGroup, false );
         }
         dstrEntityId.stripLeading().stripTrailing();
         dstrLastName.stripLeading().stripTrailing();
         dstrFirstName.stripLeading().stripTrailing();	  

         if ( bPutInList )
         {
            if( formatComma )
            {
               // put entity info to substitution list
               entityAsOfDateList += dstrEntityId + I_("=") + dstrLastName + I_(", ") + dstrFirstName + I_(";");
            }
            else 
            {
               // put entity info to substitution list
               entityAsOfDateList += dstrEntityId + I_("=") + dstrFirstName + I_(" ") + dstrLastName + I_(";");
            }
         }
      }   

   }  // end for
   return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************************************************************
bool AccountEntityXref::isRESPBeneficiaryDeleted (const DString& accountNum, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getEntityAge"));

   bool bIsRESPBenDeleted = false;

   // get deleted list in memory
   BFObjIter iterDeleted (*this, idDataGroup, false, BFObjIter::ITERTYPE::DELETED);   
   DString dstrEntityType;
   AccountEntityXrefObject* pXrefObj = NULL;

   iterDeleted.begin();
   while (!iterDeleted.end())
   {
      DString dstrIterAcct;
      pXrefObj = dynamic_cast<AccountEntityXrefObject*> (iterDeleted.getObject());
      pXrefObj->getField (ifds::EntityType, dstrEntityType, idDataGroup);
      pXrefObj->getField (ifds::AccountNum, dstrIterAcct, idDataGroup);
      if (dstrEntityType == I_("50") && dstrIterAcct == accountNum) //resp bene
      {
         bIsRESPBenDeleted = true;
         break;
      }
      ++iterDeleted;
   }

   if (!bIsRESPBenDeleted)
   {
      MFAccount *pMFAccount (NULL);
      if ( getWorkSession().getMFAccount (idDataGroup, accountNum, pMFAccount) <= WARNING &&
           pMFAccount)
      {
         DString respBenefDeleted;

         pMFAccount->getField (ifds::RESPBenefDeleted, respBenefDeleted, idDataGroup, false);

         bIsRESPBenDeleted = respBenefDeleted == I_("Y");
      }
   }

   return bIsRESPBenDeleted;
}

//*********************************************************************************************
SEVERITY AccountEntityXref::GetEntityIdForEntityType( const DString& accountNum, 
                                                      const DString& entityType,
                                                      const DString& seqNumber,
                                                      const BFDataGroupId& idDataGroup, 
                                                      DString& entityId )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "GetEntityIdForEntityTypeSequence1" ) );

   PopulateEntitiesList(idDataGroup, accountNum);
   BFObjIter iterAccount( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );
   DString strKey;

   buildPartialKeyForRetrievingEntity( strKey, accountNum, entityType, seqNumber );
   if( iterAccount.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, strKey ) )
   {
      if( !iterAccount.end() )
      {
         iterAccount.getObject()->getField( ifds::EntityId, entityId, idDataGroup ); 
      }
   }
   
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AccountEntityXref::GetEntityIdForEntityType( const DString& accountNum, 
													  const DString& entityType,
													  const BFDataGroupId& idDataGroup, 
													  DString& entityId ) //New method added for INC0033364
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "GetEntityIdForEntityType" ) );

	PopulateEntitiesList(idDataGroup, accountNum);
	BFObjIter iterAccount( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );
	DString strKey,str;

	//Below logic modified for INC0037834
	buildPartialKeyForAccount( str, accountNum );
	strKey += str;
	buildPartialKeyForEntityType (str, entityType );
	strKey += str;
	if( iterAccount.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, strKey ) )
	{
		if( !iterAccount.end() )
		{
			iterAccount.getObject()->getField( ifds::EntityId, entityId, idDataGroup ); 
		}
	}
	return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
SEVERITY AccountEntityXref::validateLoanNumberForNonEscrowAccount(const DString& accountNum,
                                                                  const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateLoanNumberForNonEscrowAccount" ) );

   // For non escrow account, no loan number is allowed to account holder

   DString searchKey, strAcctNum;
   MFAccount *pMFAccount = NULL;
   getWorkSession().getMFAccount( idDataGroup, strAcctNum, pMFAccount );

   BFObjIter bfIter( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );

   buildPartialKeyForAccount( searchKey, accountNum );
   if( bfIter.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey ) )
   {
      //check if the entity's holding loan number
      DString dstrEntityType;

      while( !bfIter.end() )
      {
         bfIter.getObject()->getField( ifds::EntityType, dstrEntityType, idDataGroup );
         if( (dstrEntityType == ACCOUNTHOLDER_ENTITY_TYPE))
         {
            //check if the entity's holding loan number
            DString dstrEntityId;
            Entity *pEntity;

            bfIter.getObject()->getField( ifds::EntityId, dstrEntityId, idDataGroup );

            if( getWorkSession().getEntity( idDataGroup, dstrEntityId, pEntity ) <= WARNING &&
               pEntity )
            {
               if( pEntity->hasIDSByType(IDS::LOAN_NUMBER, idDataGroup) )
               {
                  // raise the error.
                  getErrMsg ( IFASTERR::LOAN_NUMBER_FOR_ESCROW_ACCOUNT,
                              CND::ERR_LOAN_NUMBER_FOR_ESCROW_ACCOUNT,
                              CND::WARN_LOAN_NUMBER_FOR_ESCROW_ACCOUNT,
                              idDataGroup );
               }
            }
         }
         ++bfIter;
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
SEVERITY AccountEntityXref::getAssociateEntitySubList(DString &subList, 
                                                      const BFDataGroupId &idDataGroup,
                                                      const DString &excludeEntityTypeFromSubList, 
                                                      const DString &excludeSeqNumbeFromSubList)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getAssociateEntitySubList"));

    subList = NULL_STRING;

    BFObjIter iterAccountEntityXref(*this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED);
    iterAccountEntityXref.begin();

    while (!iterAccountEntityXref.end())
    {
        AccountEntityXrefObject *pObj = dynamic_cast<AccountEntityXrefObject*>(iterAccountEntityXref.getObject());
        DString dstrObjEntityType , dstrObjEntityId, dstrObjSeqNumber;

        pObj->getField (ifds::EntityType, dstrObjEntityType, idDataGroup, false);
        pObj->getField (ifds::EntityId, dstrObjEntityId, idDataGroup, false);
        pObj->getField (ifds::SeqNumber, dstrObjSeqNumber, idDataGroup, false);

        dstrObjEntityType.strip().upperCase();

        //If an entity is exactly the same as excludeEntityType and excludeSeqNumber, it will not be included into the sublist.
        if ((dstrObjEntityType == ACCOUNT_OWNER || dstrObjEntityType == ITF_INDIVIDUAL_ENTITY_TYPE) && 
            subList.find(dstrObjEntityId) == -1 && 
            !(dstrObjEntityType == excludeEntityTypeFromSubList && dstrObjSeqNumber == excludeSeqNumbeFromSubList))
        {
            DString dstrObjLastName, dstrObjFirstName;

            pObj->getField(ifds::LastName, dstrObjLastName, idDataGroup, false);
            pObj->getField(ifds::FirstName, dstrObjFirstName, idDataGroup, false);

            subList = subList + dstrObjEntityId + I_("=") + dstrObjLastName + I_(", ") + dstrObjFirstName +  I_(";");
        }

        ++iterAccountEntityXref;
    }

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AccountEntityXref::updateAssociateEntityForAllRelatedPartyEntities(const BFDataGroupId &idDataGroup,
                                                                            const DString &excludeEntityTypeFromSubList, 
                                                                            const DString &excludeSeqNumbeFromSubList)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("updateAssociateEntityForAllRelatedPartyEntities"));

    DString dstrAssociateEntitySubList;
    BFObjIter iterAccountEntityXref(*this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED);
    
    getAssociateEntitySubList(dstrAssociateEntitySubList, idDataGroup, excludeEntityTypeFromSubList, excludeSeqNumbeFromSubList);
    iterAccountEntityXref.begin();

	/* Getting CRSEntityList */
	DString dstrCRSEntityList;
	getWorkSession().getOption(ifds::CRSEntityList, dstrCRSEntityList, idDataGroup, false);    

    while (!iterAccountEntityXref.end())
    {
        DString dstrEntityType;
        AccountEntityXrefObject *pObj = dynamic_cast<AccountEntityXrefObject*>(iterAccountEntityXref.getObject());
        
        pObj->getField(ifds::EntityType, dstrEntityType, idDataGroup, false);

		/* Removed RELATED_PARTY. Using CRSEntityList instead. */
		if (dstrEntityType != ACCOUNTHOLDER_ENTITY_TYPE && (DSTCommonFunctions::codeInList(dstrEntityType, dstrCRSEntityList) || dstrCRSEntityList == APPLICABLE_TO_ALL || dstrEntityType == RELATED_PARTY_AML_ENTITY_TYPE))
        {
            pObj->updateAssociateEntity(dstrAssociateEntitySubList, idDataGroup);
        }

        ++iterAccountEntityXref;
    }
    
    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AccountEntityXref::updateVerifyStatForDeletion(const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("updateVerifyStatForDeletion"));

	BFObjIter iterAccountEntityXref (*this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED);
	iterAccountEntityXref.begin ();

	while (!iterAccountEntityXref.end())
	{
		AccountEntityXrefObject* pAccountEntityXrefObject = dynamic_cast<AccountEntityXrefObject*>(iterAccountEntityXref.getObject());
		pAccountEntityXrefObject->updateVerifyStatFlag(idDataGroup);
		++iterAccountEntityXref;
	}
	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void AccountEntityXref::getRDSPBeneficiaryEntity( ENTITIES_VECTOR & rdspBeneficiaryEntity, DString dstrAcctNum, const BFDataGroupId& idDataGroup )
{
   DString strEntityId, strEntityType, searchKey;
   rdspBeneficiaryEntity.clear();
	
   PopulateEntitiesList(idDataGroup, dstrAcctNum);
   BFObjIter bfIter( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED);//, false, true );

   buildPartialKeyForAccount( searchKey, dstrAcctNum );
   bfIter.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey );

   while( !bfIter.end() )
   {
      bfIter.getObject()->getField (ifds::EntityId, strEntityId, idDataGroup);
      bfIter.getObject()->getField (ifds::EntityType, strEntityType, idDataGroup);

      if( strEntityType == RDSP_BENEFICIARY )
      {
         rdspBeneficiaryEntity.push_back (strEntityId);
      }

      ++bfIter;
   }
}	


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AccountEntityXref.cpp-arc  $
 * 
 *    Rev 1.169   Jul 24 2012 18:51:38   dchatcha
 * P0179630 FN01 FATCA Project - Entity level
 * 
 *    Rev 1.168   Jun 27 2012 14:28:36   if991250
 * Synch: CPF: Force validateAll of AccountEntityXrefObj for CPF accounts
 * 
 *    Rev 1.167   Jun 05 2012 05:16:54   panatcha
 * IN2952546 – Primary Beneficary warning message needed for all Tax Types
 * 
 *    Rev 1.165   Jun 01 2012 03:55:40   panatcha
 * IN2952546 – Primary Beneficary warning message needed for all Tax Types
 * 
 *    Rev 1.164   May 01 2012 09:25:18   if991250
 * CPF - validating that the Registration agent has the appropriate tax type for the CPF account
 * 
 *    Rev 1.163   Apr 27 2012 09:52:48   if991250
 * CPF - Account Setup & Settlement 
 * 
 *    Rev 1.162   Mar 21 2012 12:09:34   jankovii
 * IN 2873391 - Cannot set up Joint RESP in iFAST
 * 
 *    Rev 1.161   Feb 06 2012 04:21:10   panatcha
 * IN2780013 - SOC Loan Number and Loan Type
 * 
 *    Rev 1.160   Dec 19 2011 23:32:10   popescu
 * P0186484 - FN 05 - work on Contract Information Screen
 * 
 *    Rev 1.159   Dec 13 2011 16:09:48   dchatcha
 * P0184543 FN01 - CDIC Fast Insurance Determination
 * 
 *    Rev 1.158   Dec 01 2011 00:15:20   panatcha
 * IN2738162 Loan Number vs shareholder
 * 
 *    Rev 1.157   Nov 09 2011 20:07:02   dchatcha
 * PETP0186486 FN01 IN2707425 - RRSP Loan Issues - build error.
 * 
 *    Rev 1.156   Nov 09 2011 01:58:16   kitticha
 * PETP0186486 FN01 IN2707425 - RRSP Loan Issues - Modify validation for RRSP Loan when delete.
 * 
 *    Rev 1.155   Nov 08 2011 22:14:00   kitticha
 * PETP0186486 FN01 IN2707425 - RRSP Loan Issues.
 * 
 *    Rev 1.154   Nov 04 2011 07:56:16   kitticha
 * PETP0186486 FN01 IN2707425 - RRSP Loan issues2 - Modify message to 'Loan Number is missing'.
 * 
 *    Rev 1.153   Jul 20 2011 17:55:46   dchatcha
 * P0180786 FN01 - TFSA Estate and Right of Rescission Tax Reporting.
 * 
 *    Rev 1.152   Jan 10 2011 03:51:30   wutipong
 * IN2311277 - Unable to access FDP accounts in Desktop
 * 
 *    Rev 1.151   Nov 25 2010 11:13:36   kitticha
 * PET165541_FN03_QESI_Phase3_Non_Finance - revise.
 * 
 *    Rev 1.150   Oct 15 2010 02:46:30   dchatcha
 * PETP0172931_FN01_IN#2283060, clearing platform ID will be for clearing platform entity only.
 * 
 *    Rev 1.149   Sep 29 2010 11:37:54   jankovii
 * PET0175377 FN01 - AIP for Joint RESP Account
 * 
 *    Rev 1.148   May 12 2010 23:51:32   popescu
 * RESP/QESI fix - "RESP Designated Institution should be set up" occurs only for new accounts
 * 
 *    Rev 1.147   May 06 2010 23:35:14   popescu
 * RESP/QESI fixes
 * 
 *    Rev 1.146   May 03 2010 17:44:32   popescu
 * PET0165541 FN01 QESI RESP Trading - New account set-up fixes
 * 
 *    Rev 1.145   Apr 28 2010 13:07:12   jankovii
 * PET0165541 FN01 QESI RESP Trading
 * 
 *    Rev 1.144   Apr 23 2010 16:06:32   jankovii
 * PET0165541 FN01 QESI RESP Trading
 * 
 *    Rev 1.143   Apr 19 2010 15:54:30   popescu
 * PET0165541-FN01 QESI Fixed bene allocation issue related to the effective date
 * 
 *    Rev 1.142   Apr 14 2010 02:08:08   kitticha
 * PET0165541-FN01 QESI RESP Trading.
 * 
 *    Rev 1.141   Apr 03 2010 02:23:04   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.140   Mar 31 2010 15:18:34   jankovii
 * 12695042
 * 
 *    Rev 1.139   Mar 31 2010 08:30:28   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.138   Mar 29 2010 07:18:10   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.137   Mar 26 2010 09:26:34   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.136   Mar 25 2010 13:54:36   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.135   Mar 23 2010 13:59:44   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.134   Mar 22 2010 15:08:34   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.133   Mar 17 2010 06:34:22   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.132   Mar 12 2010 14:56:38   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.131   Mar 08 2010 13:16:14   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_TRADING 
 * 
 *    Rev 1.130   Nov 03 2009 20:50:00   wutipong
 * Inc#1869064 -- R95- Multiple annuitant can be assigned to registered accounts
 * 
 *    Rev 1.129   Sep 10 2009 15:10:04   wutipong
 * IN1816633 -- R95 - Issues with Annuitant Entity- Incorrect error message
 * 
 *    Rev 1.128   Jul 29 2009 17:17:22   wutipong
 * IIN1764677 - Issues with Annuitant Entity- ECF
 * 
 *    Rev 1.127   Feb 05 2009 15:56:16   jankovii
 * IN 1578637 - Project PBSA - Issue on Non Financial Update in Desktop - MMF#007
 * 
 *    Rev 1.126   Jan 27 2009 06:23:28   daechach
 * IN 1548019 - New CBO level error codes for MT535/536.
 * 
 *    Rev 1.125   23 Jan 2009 16:32:08   popescu
 * Incident 	1548019 - reset button on entitymaintenance dlg, BIC Code can be valid/invalid for entitytype 58
 * 
 *    Rev 1.124   16 Jan 2009 17:22:56   popescu
 * Incident 1544134 - various fixes
 * 
 *    Rev 1.123   Dec 15 2008 14:44:36   jankovii
 * Sync up: IN 1519506 - Error Message on iFAST Desktop saving Death Date
 * 
 *    Rev 1.122   Dec 15 2008 01:33:58   phiwponp
 * PET0007773_FN01_MT535-MT536 Enhancement.
 * 
 *    Rev 1.121   Nov 28 2008 14:31:04   jankovii
 * PET 142196 FN01 Federal Restricted LIF and LIRA.
 * 
 *    Rev 1.120   Nov 25 2008 11:12:16   jankovii
 * PET 142196 FN01 Federal Restricted LIF and LIRA.
 * 
 *    Rev 1.119   06 Nov 2008 17:10:02   popescu
 * KYC/AML - Joint accounts feature - after System Integrated Testing
 * 
 *    Rev 1.118   03 Nov 2008 17:32:28   popescu
 * KYC/AML - Joint accounts feature - after System Integrated Testing
 * 
 *    Rev 1.117   Oct 28 2008 08:28:40   jankovii
 * PET 59888 FN03 AML KYC.
 * 
 *    Rev 1.116   06 Oct 2008 13:16:22   kovacsro
 * PET142007  FN01 TFSA
 * 
 *    Rev 1.115   15 Sep 2008 14:08:16   kovacsro
 * IN# 1408829 - removed warning
 * 
 *    Rev 1.114   12 Sep 2008 15:40:32   kovacsro
 * PET142007.FN01 Tax Free Saving Account - code cleanup for taxType=0
 * 
 *    Rev 1.113   23 Nov 2007 11:30:42   kovacsro
 * PET5685FN25 - age71 changes for RRSP&RIF
 * 
 *    Rev 1.112   Oct 08 2007 12:15:44   smithdav
 * IN  1005517,1020252 - LRSP logic
 * 
 *    Rev 1.111   27 Aug 2007 17:08:42   popescu
 * GAP 2 - 2360 - when search by CIF return all the accounts where entities share the same number, and display them.
 * 
 *    Rev 1.110   22 Aug 2007 13:37:24   popescu
 * GAP 6 - search by CIF should return all the entities linked by CIF
 * 
 *    Rev 1.109   Feb 27 2007 15:07:38   ZHANGCEL
 * Incident #728172 -- Change logic to raise error or warning base on the RejError code 946.
 * 
 *    Rev 1.108   Feb 15 2007 16:39:20   ZHANGCEL
 * Incident #728172 -- Change logic to raise an error rather than warning for reason code 01.
 * 
 *    Rev 1.107   Aug 25 2006 16:04:56   ZHANGCEL
 * Incident #694914 -- Add permission check for "Assignee Entity Type Setup"
 * 
 *    Rev 1.106   Jul 04 2006 13:47:26   ZHANGCEL
 * PET2145 FN01 -- Change logic to handle Assignee entity type
 * 
 *    Rev 1.105   Feb 01 2006 18:13:54   popescu
 * Incident# 530756 - call view 61 - where used for entity type '01' to display the list of accounts on the account details screen
 * 
 *    Rev 1.104   Aug 17 2005 12:08:26   Fengyong
 * Incident 381605 - benificial percentage available calculation.
 * 
 *    Rev 1.103   Jun 23 2005 14:49:48   porteanm
 * Incident 332074 - Duplicate SIN rej-error.
 * 
 *    Rev 1.102   Apr 04 2005 10:43:20   yingbaol
 * PET1171,FN01:Fix null pointer issue( The issue exists for a long time I think ).
 * 
 *    Rev 1.101   Nov 14 2004 14:24:30   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.100   Sep 08 2004 17:51:04   ZHANGCEL
 * PET1094-FN8 -- AdminFee related changes
 * 
 *    Rev 1.99   Feb 26 2004 15:14:56   VADEANUM
 * PTS 10017714 - Transfer allowed on restricted account.
 * 
 *    Rev 1.98   Jan 12 2004 18:48:02   popescu
 * PTS 10024062, fixed fail on joint account duplicate SIN; (sin values part of the exception list should be checked as duplicates)
 * 
 *    Rev 1.97   Jan 02 2004 15:11:54   popescu
 * PTS 10025696, NASU flow crash 
 * 
 *    Rev 1.96   Dec 22 2003 14:13:24   linmay
 * fix format problem for Ticket#10025389
 * 
 *    Rev 1.95   Nov 19 2003 10:55:56   popescu
 * Synch-up Rel 54, PTS 10023438
 * 
 *    Rev 1.94   Nov 10 2003 10:23:22   HERNANDO
 * Sync'd with 1.89.1.0; PTS 10023301 - Added additional Error Condition.
 * 
 *    Rev 1.93   Nov 10 2003 09:43:16   HERNANDO
 * Sync'd with 1.92.1.0
 * 
 *    Rev 1.92.1.0   Nov 08 2003 21:45:52   popescu
 * PTS 10023438, performance issues fixes, do not call PopulateWhereUsed anymore, data is in memory
 * 
 *    Rev 1.92   Nov 05 2003 14:25:40   popescu
 * PTS 10023438, SIN should be required and valid if acct is RESP or family RESP and  entity is acct owner or beneficiary
 * 
 *    Rev 1.91   Oct 30 2003 16:30:12   popescu
 * PTS 10023438, RESP SIN legislative requirement
 * 
 *    Rev 1.90   Oct 22 2003 11:40:52   YINGBAOL
 * PTS10022062,PTS10022418( item 1 ) 
 * 
 *    Rev 1.86   Sep 08 2003 11:41:28   ZHANGCEL
 * PTS ticket 10020948 :Only the entity with the seqNum 1should be set as the new account's owner
 * 
 *    Rev 1.85   Aug 28 2003 16:42:30   FENGYONG
 * move the firstname, sin number validation for YP, ITF to validateOneAccount
 * 
 *    Rev 1.84   Aug 26 2003 11:33:46   FENGYONG
 * fill the spouse combo, getname from entity 
 * 
 *    Rev 1.83   Aug 25 2003 17:25:58   FENGYONG
 * set refresh flag to control if need check can delete Or not.
 * 
 *    Rev 1.82   Aug 22 2003 14:53:20   FENGYONG
 * Add delete brn relate rules to cbo
 * 
 *    Rev 1.81   Aug 21 2003 19:52:32   FENGYONG
 * KYC Joint info enhancement
 * 
 *    Rev 1.80   Aug 15 2003 14:24:12   FENGYONG
 * Add rules 17 
 * 
 *    Rev 1.79   Aug 11 2003 16:45:50   YINGBAOL
 * remove the logic setfield to HOST
 * 
 *    Rev 1.78   Jul 30 2003 11:26:28   FENGYONG
 * CIBC enhancement PET809_FN46
 * 
 *    Rev 1.77   Jun 04 2003 10:46:20   VADEANUM
 * Fix for escrowReason09().
 * 
 *    Rev 1.76   Jun 03 2003 17:03:06   VADEANUM
 * PTS 10008364 - modified escrowReason09()
 * 
 *    Rev 1.75   Jun 02 2003 17:42:04   HERNANDO
 * PTS 10017640 - Check Escrow Stop Dates to determine whether valid Escrow Entities exist.  If the Escrow Stop Date > Current Business Date, then increment counter.
 * 
 *    Rev 1.74   Mar 21 2003 17:54:08   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.73   Feb 17 2003 13:15:50   HSUCHIN
 * removed escrow band check for reasons 12 to 23
 * 
 *    Rev 1.72   Feb 17 2003 12:10:28   HSUCHIN
 * added 2 new methods setupEscrowReasons and escrowReason12To23 to handle new assignment codes
 * 
 *    Rev 1.71   Jan 14 2003 15:39:14   ZHANGCEL
 * Sync up to R49 1.70 -- PTS Ticket 10008006 : bug fix -- added logic to get the mfaccount refreshing when ever deleting a entity
 * 
 *    Rev 1.70   Dec 06 2002 09:31:54   YINGBAOL
 * PRIF Enhancement
 * 
 *    Rev 1.69   Oct 18 2002 15:54:46   KOVACSRO
 * synced-up ver. 1.68 and 1.69
 * 
 *    Rev 1.68   Oct 09 2002 23:53:52   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.67   Sep 24 2002 15:33:28   KOVACSRO
 * Added (new) logic to stop the user to submit multiple (different) entities having the same SIN - logic applies only for Canadian market.
 * 
 *    Rev 1.66   Aug 29 2002 19:06:18   SMITHDAV
 * Sync-up with branches.
 * 
 *    Rev 1.65   Aug 29 2002 18:46:20   SMITHDAV
 * Sync-up branches.
 * 
 *    Rev 1.64   Aug 29 2002 12:54:52   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.63   Aug 12 2002 18:07:04   YINGBAOL
 * do not remove data objetc at list level
 * 
 *    Rev 1.62   Aug 02 2002 16:54:46   WINNIE
 * Bug fix for validateOneAccount; PTS 10009290 - give Spouse SIN missing message, spouse sin invalid and account owner sin invalid
 * 
 *    Rev 1.61   Aug 02 2002 09:59:16   YINGBAOL
 * add more validation for plantype RIF
 * 
 *    Rev 1.60   Jul 26 2002 18:17:32   WINNIE
 * 10008072 : Add condition of missing SIN for owner
 * 
 *    Rev 1.59   Jul 26 2002 14:52:50   YINGBAOL
 * fix refersh issue---PTS10009183
 * 
 *    Rev 1.58   Jul 26 2002 09:54:34   YINGBAOL
 * Fix Validation for LRIF Account----PTS10009146
 * 
 *    Rev 1.57   Jul 10 2002 17:45:50   ZHANGCEL
 * Get TaxType from MFAccount instead of from AccountEntityXferObject
 * 
 *    Rev 1.56   Jul 02 2002 11:10:04   WINNIE
 * Tax legislation enhancement to check spouse SIN for marriage break down redemption and transfer
 * 
 *    Rev 1.55   Jun 28 2002 17:33:16   ZHANGCEL
 * Added logic in the ValidateAll() in order to validateEntityTypeDofB( idDataGroup ) can be got trigger when user modify an existing entity 
 * 
 *    Rev 1.54   22 May 2002 18:26:10   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.53   12 Apr 2002 16:02:40   HERNANDO
 * Changed condition.  Now using ERR_RESP_ONLY_ONE_BENF_ALLOW.
 * 
 *    Rev 1.52   Apr 10 2002 14:19:12   HERNANDO
 * PTS 10007492 - Added extra checks for an existence of ITF/Escrow entities and the flags in the Account.
 * 
 *    Rev 1.51   05 Mar 2002 16:27:28   KOVACSRO
 * refreshing MFAccount data object in refresh.
 * 
 *    Rev 1.50   Feb 25 2002 19:10:58   PURDYECH
 * Phase 1 of BFData Rollout - Base Component Compatibility
 * 
 *    Rev 1.49   18 Feb 2002 16:13:12   WINNIE
 * PTS 10007100: add logic to give warning if SWP exists for the escrow rep and reason code between 1 to 6
 * 
 *    Rev 1.48   Feb 08 2002 11:12:40   ZHANGCEL
 * Bug Fix of PTS 10006914: Added logic to validate Primary Beneficiary for a  RRIF account
 * 
 *    Rev 1.47   12 Dec 2001 16:18:16   KOVACSRO
 * Added a new condition for employer entity.
 * 
 *    Rev 1.46   28 Nov 2001 14:37:14   KOVACSRO
 * If populateAccountOwner() was called with an input account num, get MFAccount from the repository (it might save a view call 4, if already there)
 * 
 *    Rev 1.45   05 Nov 2001 14:55:42   KOVACSRO
 * hasPermission() changes.
 * 
 *    Rev 1.44   30 Oct 2001 11:54:42   WINNIE
 * title restriction for transfer out, adding new owner, add escrow when pending trade exists;  compare effective date of escrow record with current business date rather than the effective date of the entity; 
 * 
 *    Rev 1.43   26 Sep 2001 14:03:52   WINNIE
 * escrow title restriction enhancement
 * 
 *    Rev 1.42   17 Sep 2001 11:50:00   WINNIE
 * Title restriction escrow enhancement for systematic, address changes, transfer and exchange
 * 
 *    Rev 1.41   Sep 12 2001 10:58:06   ZHANGCEL
 * Added a new method: cloneAcctEntityXrefFromModel()
 * 
 *    Rev 1.40   Aug 27 2001 17:05:08   ZHANGCEL
 * Fixed the bug that causes crash when user hit entitiy copy button more than one times.
 * 
 *    Rev 1.39   03 Aug 2001 16:17:30   HSUCHIN
 * sync up with 1.32.1.2 to fix Beneficiary Percentage error problem
 * 
 *    Rev 1.38   02 Aug 2001 15:16:44   YINGZ
 * fix delete problem
 * 
 *    Rev 1.37   Jul 23 2001 15:25:30   YINGBAOL
 * The modification have not been checked in, check in again.
 * 
 *    Rev 1.35   19 Jun 2001 11:27:52   YINGZ
 * add comments
 * 
 *    Rev 1.34   18 Jun 2001 14:29:34   YINGZ
 * fix refresh 
 * 
 *    Rev 1.33   03 May 2001 14:05:50   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.32   Feb 27 2001 16:12:52   ZHANGCEL
 * Fixed the bugs in four new functions those were added in version 1.31
 * 
 *    Rev 1.31   Feb 19 2001 15:13:04   ZHANGCEL
 * Adde new functions: getAcctOwnerEntities(), getBeneficiaries(), getAnnitants() and getAcctOwners()
 * 
 *    Rev 1.30   Jan 18 2001 16:03:24   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.29   Jan 04 2001 16:48:42   ZHANGCEL
 * Synchronization to C2/C3: Added logic for Entity Copy requirement
 * 
 *    Rev 1.28   Dec 17 2000 20:21:30   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.27   Dec 05 2000 17:15:38   DINACORN
 * Synchronization to C2/C3: Added logic for RESP entity age checking
 * 
 *    Rev 1.26   Nov 24 2000 12:09:48   WINNIE
 * add ecrowaccount and escrowaccountFundClass method
 * 
 *    Rev 1.25   Nov 16 2000 14:09:52   WINNIE
 * missing assignment for _accountnum
 * 
 *    Rev 1.24   Nov 16 2000 12:29:12   WINNIE
 * bug fix for entity assignment
 * 
 *    Rev 1.23   15 Nov 2000 15:30:04   SMITHDAV
 * Use new ReceiveData and do some cleanup.
 * 
 *    Rev 1.22   Nov 07 2000 17:42:20   OLTEANCR
 * new data broker
 * 
 *    Rev 1.21   Oct 22 2000 15:40:08   WINNIE
 * check delete
 * 
 *    Rev 1.20   Oct 03 2000 17:04:06   YINGBAOL
 * fix new object problem
 * 
 *    Rev 1.19   Oct 03 2000 16:27:28   WINNIE
 * Temparory remove logic that check RESP reason code before delete
 * 
 *    Rev 1.18   Oct 03 2000 13:56:30   WINNIE
 * bug fix for RESP validation; move entity Ids list validation to validateOneAccount; remove validation for entity type 05
 * 
 *    Rev 1.17   Sep 29 2000 13:27:04   YINGZ
 * change market from cfds - canada to canada
 * 
 *    Rev 1.16   Sep 27 2000 17:19:58   WINNIE
 * Bug fixes for Age calculation;Deletion of account entity; active parent entity error etc.
 * 
 *    Rev 1.15   Sep 25 2000 16:51:28   WINNIE
 * Calculation age for RESP beneificary
 * 
 *    Rev 1.14   Sep 20 2000 09:06:36   KOVACSRO
 * Added RESP Ben. deletion logic.
 * 
 *    Rev 1.13   Sep 15 2000 11:05:06   WINNIE
 * Bug fix for number on edit check for  RESP parent entity
 * 
 *    Rev 1.12   Sep 05 2000 10:45:46   WINNIE
 * Bug fixes and code clean up
 * 
 *    Rev 1.11   Aug 31 2000 14:33:32   DINACORN
 * Modified the method validateOneAccount(); added more constants in namespace
 * 
 *    Rev 1.10   Aug 29 2000 17:13:14   DINACORN
 * Modified the method validateOneAccount()
 * 
 *    Rev 1.9   Aug 15 2000 11:42:18   PETOLESC
 * Moved logic from MFAccount::ValidateEntityType() to AccountEntityXref::ValidateOneAccount().
 * 
 *    Rev 1.8   Aug 11 2000 15:52:42   WINNIE
 * Correction for doValidateAll to only validate the current account
 * 
 *    Rev 1.7   Aug 10 2000 13:45:04   YINGBAOL
 * change getNextSeq and fix bug
 * 
 *    Rev 1.6   Aug 01 2000 09:34:16   YINGBAOL
 * add delete logic
 * 
 *    Rev 1.5   Jul 28 2000 16:52:58   HUANGSHA
 * Fixed the bug for validate ids list, moved getMandatoryIdsDesc() to EntityIdsList.cpp
 * 
 *    Rev 1.4   Jul 27 2000 14:44:58   DINACORN
 * Modified function doCreateObject
 * 
 *    Rev 1.3   Jul 20 2000 14:09:56   HUANGSHA
 * Added routine getMandatoryIdsDesc(...), validate the IDS based on the system feature: madatoryID
 * 
 *    Rev 1.2   May 04 2000 14:10:16   BUZILA
 * we  want to clear updated flag for acctNum and EntityId for existing relations
 * 
 *    Rev 1.1   Mar 10 2000 14:53:12   YINGZ
 * code sync
 * 
 *    Rev 1.0   Feb 15 2000 10:59:48   SMITHDAV
 * Initial revision.
// 
//    Rev 1.48   Feb 02 2000 18:09:54   BUZILA
// changes
// 
//    Rev 1.47   Feb 02 2000 14:00:12   BUZILA
// default dataGroup for BFBase::getObject taken out
// 
//    Rev 1.46   Feb 01 2000 14:36:22   BUZILA
// added lValidateGroup parameter to doValidateAll method
// 
//    Rev 1.45   Jan 26 2000 19:43:04   VASILEAD
// Fixes
// 
//    Rev 1.44   Jan 23 2000 19:34:24   VASILEAD
// Reset functionality
// 
//    Rev 1.43   Jan 23 2000 16:44:46   VASILEAD
// Reset functionality
// 
//    Rev 1.42   Jan 22 2000 15:22:32   POPESCUS
// fix in refresh
// 
//    Rev 1.41   Jan 21 2000 17:49:40   VASILEAD
// Refresh stuff
// 
//    Rev 1.40   Jan 18 2000 18:38:14   VASILEAD
// Updates fix
// 
//    Rev 1.39   Jan 17 2000 10:12:02   POPESCUS
// added support for refresh
// 
//    Rev 1.38   Jan 16 2000 17:00:14   POPESCUS
// new method to get the entity id for the account owner sequence 1
// 
//    Rev 1.37   Jan 14 2000 18:08:54   POPESCUS
// set the last active account num
// 
//    Rev 1.36   Jan 14 2000 15:59:18   VASILEAD
// Where used fixes
// 
//    Rev 1.35   Jan 13 2000 17:39:38   VASILEAD
// Added support for catching errors
// 
//    Rev 1.34   Jan 12 2000 08:58:22   POPESCUS
// changes related to cloning an account and fixing some validation, adding subst sets
// 
//    Rev 1.33   Jan 07 2000 17:02:46   VASILEAD
// Validations for Entity screen
// 
//    Rev 1.32   Jan 06 2000 16:38:38   VASILEAD
// Added  setObjectAsList
// 
//    Rev 1.31   Jan 06 2000 16:21:08   VASILEAD
// Business edits for Entity screen
// 
//    Rev 1.30   Dec 24 1999 15:18:22   VASILEAD
// Fixed transactions
// 
//    Rev 1.29   Dec 23 1999 14:18:00   VASILEAD
// Added validation for ids
// 
//    Rev 1.28   Dec 21 1999 13:41:10   VASILEAD
// fixed error during create new object
// 
//    Rev 1.27   Dec 21 1999 10:42:12   VASILEAD
// Added Entity list iteration based on the string keys and not on the ObjectKey, added background search support
// 
//    Rev 1.26   Dec 17 1999 14:05:54   POPESCUS
// made DString const in getValueForTag
// 
//    Rev 1.25   Dec 15 1999 07:28:14   POPESCUS
// the overriden receive method doesn't need to delete the xchgdata object
// 
//    Rev 1.24   Dec 12 1999 16:25:06   POPESCUS
// Xchgdata issue; create and delete the object in the CBO
// 
*/
