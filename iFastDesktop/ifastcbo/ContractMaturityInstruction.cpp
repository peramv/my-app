//********************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2010 By International Financial Data Services.
//
//
//********************************************************************************
//
// ^FILE   : ContractMaturityInstruction.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//********************************************************************************
#include "stdafx.h"
#include "ContractMaturityInstruction.hpp"
#include "ContractMaturityInstructionList.hpp"
#include "ContractMatInstrBankList.hpp"
#include "MgmtCo.hpp"
#include "MFAccount.hpp"
#include "TaxTypeRule.hpp"
#include "dynamicsublistholder.hpp"

#include <ifastdataimpl\dse_dstc0430_req.hpp>
#include <ifastdataimpl\dse_dstc0430_vwrepeat_record.hpp> //reqrepeat_record
#include <ifastdataimpl\dse_dstc0430_vw.hpp>

#include <ifastdataimpl\dse_dstc0431_req.hpp>
#include <ifastdataimpl\dse_dstc0431_reqrepeat_record.hpp> //reqrepeat_record
#include <ifastdataimpl\dse_dstc0431_vw.hpp>

#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include <ifastdataimpl\dse_dstc0004_vwrepeat_record.hpp>

#include <ifastdataimpl\dse_dstc0006_vw.hpp>
#include <ifastdataimpl\dse_dstc0006_vwrepeat_record.hpp>

#include <ifastdataimpl\dse_dstc0043_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0043_vw.hpp>


namespace
{
	const I_CHAR * const CLASSNAME			  = I_( "ContractMaturityInstruction" );
	const I_CHAR * const BLANK_SUBSTITUTION   = I_( " = ;"); // substitution with only one element with tag = value = " " 
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const REDEMPTION;
}

namespace ifds
{
	extern CLASS_IMPORT const BFTextFieldId AmountType1;
	extern CLASS_IMPORT const BFTextFieldId RedCodeList;
  extern CLASS_IMPORT const BFTextFieldId ACHRedemption;
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest CONTRACT_MATURITY_INSTR_INQUIRY;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
	// Field DD Id,							State Flags,		Group Flags 
	{ ifds::ContractType,					BFCBO::NONE,		0},
	{ ifds::InstId,							BFCBO::NONE,		0},
	{ ifds::AcctGroupName,					BFCBO::NONE,		0},
	{ ifds::BranchName,						BFCBO::NONE,		0},
	{ ifds::BrokerName,						BFCBO::NONE,		0},
	{ ifds::PolicyYear,						BFCBO::NONE,		0},
	{ ifds::PolicyTerm,						BFCBO::NONE,		0},
	{ ifds::MaturityDate,					BFCBO::NONE,		0},
	{ ifds::RedCode,						BFCBO::REQUIRED,	0},
	{ ifds::PayType3,						BFCBO::REQUIRED,	0},
	{ ifds::SourceOfFunds,					BFCBO::REQUIRED,	0},
	{ ifds::ADCD,							BFCBO::NONE,		0},
	{ ifds::AddrCode,						BFCBO::NONE,		0},
	{ ifds::AddrLine1,						BFCBO::NONE,		0},
	{ ifds::AddrLine2,						BFCBO::NONE,		0},
	{ ifds::AddrLine3,						BFCBO::NONE,		0},
	{ ifds::AddrLine4,						BFCBO::NONE,		0},
	{ ifds::AddrLine5,						BFCBO::NONE,		0},
	{ ifds::Amount,							BFCBO::REQUIRED,	0},
	{ ifds::PUD1,							BFCBO::REQUIRED,	0},
	{ ifds::BankAcctName,					BFCBO::NONE,		0},
	{ ifds::BankIdNum,						BFCBO::NONE,		0},
	{ ifds::TransitNum,						BFCBO::NONE,		0},
	{ ifds::BankAcctNum,					BFCBO::NONE,		0},
	{ ifds::RunMode,						BFCBO::NONE,		0},  //Run Mode
	//Bank Screen Related Fields
	{ifds::SwiftCode,              			BFCBO::NONE,		0}, 
	{ifds::RefNumber,              			BFCBO::NONE,		0}, 
	{ifds::BankAcctType,           			BFCBO::NONE,		0}, 
	{ifds::BankAcctCurrency,       			BFCBO::NONE,		0}, 
	{ifds::PayReason1,             			BFCBO::NONE,		0}, 
	{ifds::PayReason2,             			BFCBO::NONE,		0}, 
	{ifds::InstName,               			BFCBO::NONE,		0}, 
	{ifds::TransitNo,              			BFCBO::NONE,		0}, 
	{ifds::ACHProcessor,           			BFCBO::NONE,		0}, 
	{ifds::BankPstl,             			BFCBO::NONE,		0}, 
	{ifds::BankCntry,            			BFCBO::NONE,		0}, 
	{ifds::BankContact,            			BFCBO::NONE,		0}, 
	{ifds::BankAddr1,              			BFCBO::NONE,		0}, 
	{ifds::BankAddr2,              			BFCBO::NONE,		0}, 
	{ifds::BankAddr3,              			BFCBO::NONE,		0}, 
	{ifds::BankAddr4,              			BFCBO::NONE,		0}, 
	{ifds::BankAddr5,              			BFCBO::NONE,		0}, 
	{ifds::BankId,                 			BFCBO::NONE,		0}, 
	{ifds::PayMethod,              			BFCBO::NONE,		0}, 
	{ifds::CreditInfoLine1,             	BFCBO::NONE,		0}, 
	{ifds::CreditInfoLine2,             	BFCBO::NONE,		0}, 
	{ifds::BankType,                    	BFCBO::NONE,		0}, 
	{ifds::InstCode,                    	BFCBO::NONE,		0}, 
	{ifds::AcctUseCode,                    	BFCBO::NONE,		0},
	{ifds::AcctID,                    		BFCBO::NONE,		0},
	{ifds::Username,						BFCBO::NONE,		0}, 
	{ifds::ProcessDate,						BFCBO::NONE,		0}, 
	{ifds::ModUser,							BFCBO::NONE,		0}, 
	{ifds::ModDate,							BFCBO::NONE,		0},
	{ifds::StopDate,                    	BFCBO::NONE,		0},
	{ifds::EffectiveDate,                   BFCBO::NONE,		0},
	{ifds::BankAcctVer,						BFCBO::NONE,		0},
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
ContractMaturityInstruction::ContractMaturityInstruction( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//******************************************************************************
ContractMaturityInstruction::~ContractMaturityInstruction()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}  

//****************************************************************************

SEVERITY ContractMaturityInstruction::init( const BFDataGroupId& idDataGroup, const DString& dstrTrack /*= I_("N")*/,
											const DString& dstrPageName /*= NULL_STRING*/ )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

	doInitWithDefaultValues( idDataGroup );

	setObjectNew();

	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY ContractMaturityInstruction::init (const BFData &data)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );	

	attachDataObject (const_cast<BFData&>(data), false); 

	//set Redemption code substitution set
	loadRedCodeSubstList( BF::HOST );

	setFieldReadOnly (ifds::ContractType,	BF::HOST, true);
	setFieldReadOnly (ifds::AcctGroupName,	BF::HOST, true);
	setFieldReadOnly (ifds::BranchName,		BF::HOST, true);
	setFieldReadOnly (ifds::BrokerName,		BF::HOST, true);
	setFieldReadOnly (ifds::PolicyYear,		BF::HOST, true);
	setFieldReadOnly (ifds::PolicyTerm, 	BF::HOST, true);
	setFieldReadOnly (ifds::MaturityDate,	BF::HOST, true);
	setFieldReadOnly (ifds::AddrCode,		BF::HOST, true);
	setFieldReadOnly (ifds::AddrLine1,		BF::HOST, true);
	setFieldReadOnly (ifds::PUD1,			BF::HOST, true);

	return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
SEVERITY ContractMaturityInstruction::initNew (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNew" ));

   return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************
void ContractMaturityInstruction::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
	//set Redemption code substitution set
	loadRedCodeSubstList(idDataGroup);
}

//****************************************************************************
SEVERITY ContractMaturityInstruction::loadRedCodeSubstList( const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "loadDepRedCodeSubstList" ) );

	MFAccount *pMFAccount = NULL;
	pMFAccount = dynamic_cast<MFAccount*>( getParent()->getParent() );

	if( !pMFAccount )
		pMFAccount = dynamic_cast<MFAccount*>( getParent()->getParent()->getParent() );
	
	//getWorkSession().getMFAccount (idDataGroup, dstrAccount, pMFAccount);

	if( !pMFAccount)
		return(GETCURRENTHIGHESTSEVERITY());

	bool bLoadedSubstList = false;
	TaxTypeRule* pTaxTypeRule = NULL;
	if( pMFAccount->getTaxTypeRule ( pTaxTypeRule, idDataGroup ) <= WARNING && pTaxTypeRule )
	{
		DString strCodesList;
		pTaxTypeRule->getField( ifds::RedCodeList, strCodesList, idDataGroup );

		if( strCodesList.strip().empty() )
		{
			assert(0);  //codes list is empty or different field
			bLoadedSubstList = false;
		}
		else
		{
			bool bStripLeadingZeros = false, bAddCodeToDescription = true;
			bLoadedSubstList = loadSubstitutionList( ifds::RedCode, idDataGroup, strCodesList, 
													 bStripLeadingZeros, bAddCodeToDescription );
		}

		if( !bLoadedSubstList )
		{
			setFieldAllSubstituteValues( ifds::RedCode, idDataGroup, BLANK_SUBSTITUTION );
			setFieldNoValidate( ifds::RedCode, NULL_STRING, idDataGroup, false );
		}

	}//if( pTaxTypeRule != NULL ...

   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************

SEVERITY ContractMaturityInstruction::doValidateField(  const BFFieldId& idField,
                                                   const DString& strValue,
                                                   const BFDataGroupId& idDataGroup)

{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField"));
   
   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
SEVERITY ContractMaturityInstruction::doApplyRelatedChanges ( const BFFieldId &idField, 
															  const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ));

	bool bEnable = false;
	if ( idField == ifds::PayType3 )
	{
		DString dstrPayType;
		getField(ifds::PayType3, dstrPayType, idDataGroup, false);

		//Banking fields are only valid for PayType E
		if ( dstrPayType == I_("E") ) 
		{
			bEnable = true;
      loadFileProcessor(idDataGroup);
		}

    setFieldRequired(ifds::InstName, idDataGroup, bEnable);
    setFieldRequired(ifds::BankIdNum, idDataGroup, bEnable);
    setFieldRequired(ifds::TransitNum, idDataGroup, bEnable);
    setFieldRequired(ifds::BankAcctNum, idDataGroup, bEnable);
    setFieldRequired(ifds::ACHProcessor, idDataGroup, bEnable);

    //ifds::PayType needs to be invalidated, to trigger validation
    setFieldValid(ifds::InstName, idDataGroup, !bEnable);
    setFieldValid(ifds::BankIdNum, idDataGroup, !bEnable);
    setFieldValid(ifds::TransitNum, idDataGroup, !bEnable);
    setFieldValid(ifds::BankAcctNum, idDataGroup, !bEnable);
    setFieldValid(ifds::ACHProcessor, idDataGroup, !bEnable);
	}
	else if( idField == ifds::ContractType )
	{
		DString dstrContractType;
		getField (ifds::ContractType, dstrContractType, idDataGroup, false);
		setFieldUpdated (ifds::ContractType, idDataGroup, false);

		if( !dstrContractType.empty() )
			setFieldNoValidate (ifds::ContractType, dstrContractType, idDataGroup, false, true, true, false);
	}
	else if( idField == ifds::AddrCode )
	{
		DString dstrAddrCode;
		getField (ifds::AddrCode, dstrAddrCode, idDataGroup, false);
		setFieldUpdated (ifds::AddrCode, idDataGroup, false);
		setFieldUpdated (ifds::ADCD, idDataGroup, false);

		if( !dstrAddrCode.empty() )
		{
			setFieldNoValidate (ifds::AddrCode, dstrAddrCode, idDataGroup, false, true, true, false);
			setFieldNoValidate (ifds::ADCD, dstrAddrCode, idDataGroup, false, true, true, false);
		}
	}
	else if( idField == ifds::AddrLine1 || (idField == ifds::AddrLine2) || (idField == ifds::AddrLine3) || (idField == ifds::AddrLine4) )
	{
		DString dstrAddrLine1;
		getField (ifds::AddrLine1, dstrAddrLine1, idDataGroup, false);
		setFieldUpdated (idField, idDataGroup, false);

		if( !dstrAddrLine1.empty() )
			setFieldNoValidate (ifds::AddrLine1, dstrAddrLine1, idDataGroup, false, true, true, false);
	}
	else if( idField == ifds::PolicyYear )
	{
		DString dstrPolicyYear;
		getField (ifds::PolicyYear, dstrPolicyYear, idDataGroup, false);
		setFieldUpdated (ifds::PolicyYear, idDataGroup, false);

		if( !dstrPolicyYear.empty() )
			setFieldNoValidate (ifds::PolicyYear, dstrPolicyYear, idDataGroup, false, true, true, false);
	}
	else if( idField == ifds::PolicyTerm )
	{
		DString dstrPolicyTerm;
		getField (ifds::PolicyTerm, dstrPolicyTerm, idDataGroup, false);
		setFieldUpdated (ifds::PolicyTerm, idDataGroup, false); 

		if( !dstrPolicyTerm.empty() )
			setFieldNoValidate (ifds::PolicyTerm, dstrPolicyTerm, idDataGroup, false, true, true, false);
	}
	else if( idField == ifds::MaturityDate )
	{
		DString dstrMaturityDate;
		getField (ifds::MaturityDate, dstrMaturityDate, idDataGroup, false);
		setFieldUpdated (ifds::MaturityDate, idDataGroup, false);

		if( !dstrMaturityDate.empty() )
			setFieldNoValidate (ifds::MaturityDate, dstrMaturityDate, idDataGroup, false, true, true, false);
	}
	
	return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************
SEVERITY ContractMaturityInstruction::loadFileProcessor(const BFDataGroupId& idDataGroup)
{
  MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("loadFileProcessor"));
  DString dstrPayType, dstrAchControl;

  getField(ifds::PayType3, dstrPayType, idDataGroup, false);
  getWorkSession().getOption(ifds::ACHRedemption, dstrAchControl, idDataGroup, false);

  if(dstrPayType == I_("E") && dstrAchControl == I_("Y"))
  {
    DynamicSubListHolder* pDynamicSubListHolder = getMgmtCo().getDynamicSubListHolder();
    
    DString dstrPayMethod, dstrCurrency, dstrSubsList;

    if(DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA)
      dstrPayMethod = I_("EFT");

    getField (ifds::BankAcctCurrency, dstrCurrency, idDataGroup, false);
    dstrCurrency.strip();

    dstrSubsList = pDynamicSubListHolder->getFileProcSubList(TRADETYPE::REDEMPTION, dstrPayMethod, dstrCurrency);
    setFieldAllSubstituteValues (ifds::ACHProcessor, idDataGroup, dstrSubsList);
  }
  return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
/*
SEVERITY ContractMaturityInstruction::loadRedCodeSubstList( const DString &account,		const DString &codeType,
															const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "loadRedCodeSubstList" ));

	if ( getWorkSession().getMFAccount (idDataGroup, account, pMFAccount) <= WARNING && pMFAccount )
	{
		BFFieldId idField = ifds::NullFieldId;
		DString dstrCodesList, dstrRedCodesByTaxTypeList;

		TaxTypeRule *pTaxTypeRule = NULL;
		if (pMFAccount->getTaxTypeRule( pTaxTypeRule, idDataGroup ) <= WARNING && pTaxTypeRule )
		{
			if (codeType == I_("R")) //redemption code type
			{
				idField = ifds::RedCode;
				pTaxTypeRule->getField (ifds::RedCodeList, dstrRedCodesByTaxTypeList, idDataGroup);

				DString redCodeSubList;
				TranslationTable* pTranslationTable = NULL;
				if ( getMgmtCo().getTranslationTable(I_("RD"), pTranslationTable) <= WARNING && pTranslationTable )
				{
					if ( !isAdminFee(idDataGroup) )
					{
						 pTranslationTable->getRedCodeSubList( dstrRedCodesByTaxTypeList, redCodeSubList );
					}
				}

				DString dstrShrNum;
				pMFAccount->getField( ifds::ShrNum, dstrShrNum, idDataGroup );
				assert(!dstrShrNum.empty());

				Shareholder* pShareholder = NULL;
				if( getWorkSession().getShareholder( idDataGroup, dstrShrNum, pShareholder ) <= WARNING )
				{
					DString dstrTaxJuris;
					pShareholder->getField(ifds::TaxJurisCode, dstrTaxJuris, idDataGroup, false);

					DString dstrResidency1, dstrResidency2, dstrResidency3;
					getWorkSession().getOption (ifds::Residency1, dstrResidency1, idDataGroup, false);
					getWorkSession().getOption (ifds::Residency2, dstrResidency2, idDataGroup, false);
					getWorkSession().getOption (ifds::Residency3, dstrResidency3, idDataGroup, false);

					if( !(	DSTCommonFunctions::codeInList (dstrTaxJuris, dstrResidency1)	||
							DSTCommonFunctions::codeInList (dstrTaxJuris, dstrResidency2)	||
							DSTCommonFunctions::codeInList (dstrTaxJuris, dstrResidency3) ) ||
							dstrTaxJuris == UNASSIGNED_TAX_JURIS)
					{
					
						size_t start = redCodeSubList.find( I_("15"));
						if(start != DString::npos)
						{
							size_t end = redCodeSubList.find( I_(","), start);

							DString str1 = redCodeSubList.substr(0, start);
							DString str2 = redCodeSubList.substr(end+1);

							redCodeSubList = str1 + str2;
						}

					}//- if( !(	DSTCommonFunctions::codeInList (dstrTaxJuris, dstrResidency1)	||

				}//- if( getWorkSession().getShareholder( idDataGroup, dstrShrNum, pShareholder ) <= WARNING )

				dstrCodesList = redCodeSubList;

			}//- if (codeType == I_("R")) //redemption code type

			bool bLoadedSubstList = !dstrCodesList.empty () &&	idField != ifds::NullFieldId;
			assert (idField != ifds::NullFieldId);
         
			if (bLoadedSubstList)
			{
				bLoadedSubstList = loadSubstitutionList ( idField, idDataGroup, dstrCodesList, codeType == I_("D"), true);
			}

			if (!bLoadedSubstList)
			{
				setFieldAllSubstituteValues (idField, idDataGroup, NULL_STRING);
				setFieldNoValidate (idField, NULL_STRING, idDataGroup, false);
				setFieldReadOnly (idField, idDataGroup, true);
			}

		}//- if (pMFAccount->getTaxTypeRule( pTaxTypeRule, idDataGroup ) <= WARNING && pTaxTypeRule )

	}//- if ( getWorkSession().getMFAccount (idDataGroup, account, pMFAccount) <= WARNING && pMFAccount )

	return GETCURRENTHIGHESTSEVERITY();
}
*/

//******************************************************************************
SEVERITY ContractMaturityInstruction::init(const DString& dstrAccountNum)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );   

	BFData requestData (ifds::DSTC0430_REQ);

	DString mgmtCoIdOut;
	requestData.setElementValue(ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
	requestData.setElementValue (ifds::AccountNum, dstrAccountNum);

	ReceiveData (DSTC_REQUEST::CONTRACT_MATURITY_INSTR_INQUIRY, requestData, ifds::DSTC0430_VW, DSTCRequestor (getSecurity(), true));

	if(isNew())
	{
		setFieldNoValidate(ifds::RunMode, I_("Add"), BF::HOST, false);
	}
	else
	{
		setFieldNoValidate(ifds::RunMode, I_("Mod"), BF::HOST, false);
	}

   return( GETCURRENTHIGHESTSEVERITY() );
}

//******************************************************************************
SEVERITY ContractMaturityInstruction::getBankInstructionsList(	ContractMatInstrBankList *&pContractMatInstrBankList, const BFDataGroupId& idDataGroup, bool bCreate /*= true*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getBankInstructionsList"));

   DString dstrPayType;
   getField( ifds::PayType3, dstrPayType, idDataGroup);

   //check whether PayType is EFT, only in this case we have banking
   if ( dstrPayType == I_("E") /*EFT*/ )
   {
      BFObjectKey objKey(I_("ContractMatInstrBankList"), idDataGroup, OBJ_ACTIVITY_NONE, OBJ_TYPE_NONE);

      pContractMatInstrBankList = NULL;
      pContractMatInstrBankList = dynamic_cast<ContractMatInstrBankList*>(findObject(objKey));
      if (!pContractMatInstrBankList && bCreate)
      {
         pContractMatInstrBankList = new ContractMatInstrBankList(*this);
         if (pContractMatInstrBankList)
         {
            DString dstrAccountNum;

            getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);

			SEVERITY severity = isNew() ?   pContractMatInstrBankList->initNew(dstrAccountNum, idDataGroup) : 
											pContractMatInstrBankList->init(dstrAccountNum, idDataGroup);

            if (severity <= WARNING)
            {
               setObject(objKey, pContractMatInstrBankList);
            }
            else
            {
               delete pContractMatInstrBankList;
               pContractMatInstrBankList = NULL;
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ContractMaturityInstruction.cpp-arc  $
// 
//    Rev 1.12   Mar 28 2012 17:52:40   wp040100
// P0186484 FN05 - Contract Maturity Instruction - Changed the the field in V431 from BankAcctVersion to BankAcctVer - Banking Screen Update Fix
// 
//    Rev 1.11   Mar 22 2012 18:37:34   wp040100
// P0186484 FN05 - Contract Maturity Instruction Changes
// 
//    Rev 1.10   Mar 19 2012 21:43:12   wp040100
// P0186484 FN05 - Contract Maturity Instruction Changes
// 
//    Rev 1.9   Mar 16 2012 17:44:48   wp040100
// P0186484 FN05 - Contract Maturity Instruction Changes
// 
//    Rev 1.8   Mar 15 2012 19:32:26   wp040100
// IN 2874666 - P0186484 FN05 - Contract Maturity Instruction Changes
// 
//    Rev 1.7   Mar 13 2012 12:05:36   wp040100
// P0186484 FN05 - Contract Maturity Instructions Validation for PayType - EFT
// 
//    Rev 1.6   Mar 05 2012 20:36:36   wp040100
// P0186484 FN05 - Contract Maturity Instruction Changes
// 
//    Rev 1.5   Mar 02 2012 16:38:20   wp040100
// P0186484 FN05 - Contract Maturity Instruction - Banking Screen Integration
// 
//    Rev 1.4   Feb 27 2012 20:20:30   wp040100
// P0186484 FN05 - Contract Maturity Instruction Changes
// 
//    Rev 1.3   Feb 23 2012 14:39:30   wp040100
// P0186484 FN05 - Contract Maturity Instruction Changes
// 
//    Rev 1.2   Feb 22 2012 15:58:10   wp040100
// P0186484 FN05 - Contract Maturity Instruction Changes
// 
//    Rev 1.1   Feb 21 2012 15:53:22   wp040100
// P0186484 FN05 - Contract Maturity Instruction Changes.
// 
//    Rev 1.0   Feb 21 2012 15:33:20   wp040100
// Initial revision.
// 
//
//
 * 
 * 
// 
*/
