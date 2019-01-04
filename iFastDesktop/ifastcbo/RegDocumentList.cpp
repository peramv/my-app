//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : RegDocumentList.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//********************************************************************************
#include "stdafx.h"
#include "entity.hpp"
#include "mfaccount.hpp"
#include "regdocument.hpp"
#include "regdocumentlist.hpp"
#include "regdocumenttypelist.hpp"
#include "worksessionentitylist.hpp"
#include "Demographics.hpp"
#include "DefaultRegulatoryStandard.hpp"
#include "Broker.hpp"

#include <ifastdataimpl\dse_dstc0389_vw.hpp>
#include <ifastdataimpl\dse_dstc0389_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0389_req.hpp>


namespace DSTC_REQUEST
{
	extern CLASS_IMPORT const DSTCRequest REG_DOCLIST_INQUIRY;
}

namespace
{
	const I_CHAR * const CLASSNAME			= I_("RegDocumentList");
	const I_CHAR * const REGDOCID			= I_("ifds::RegDoc");
	const I_CHAR * const OUTSTANDING		= I_("O");
	const I_CHAR * const WAIVED				= I_("W");
	const I_CHAR * const YES				= I_("Y");
	const I_CHAR * const NO					= I_("N");
	const I_CHAR * const JURS_UNASSIGNED	= I_("0000");
	const I_CHAR * const DATE9999	        = I_("12319999");
	const I_CHAR * const INTERMEDIARY_ACCT_DESIGNATION  = I_( "3" ); 
}

namespace ifds
{
	extern CLASS_IMPORT const BFTextFieldId IsDocStatusBlank;
	extern CLASS_IMPORT const BFTextFieldId EPABroker;
	extern CLASS_IMPORT const BFTextFieldId AutoDocTracking;
	extern CLASS_IMPORT const BFTextFieldId RegStandardId;
	extern CLASS_IMPORT const BFTextFieldId BrokerCode;
	extern CLASS_IMPORT const BFTextFieldId TaxImpact;
	extern CLASS_IMPORT const BFTextFieldId CRSEntityList;
	extern CLASS_IMPORT const BFTextFieldId TaxJuris;
	extern CLASS_IMPORT const BFTextFieldId RegDocJurisdiction;
	extern CLASS_IMPORT const BFDateFieldId RegEffectiveDate;
	extern CLASS_IMPORT const BFDateFieldId EntityType;
	extern CLASS_IMPORT const BFTextFieldId CRSActive;
	extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
	extern CLASS_IMPORT const BFTextFieldId TaxComplianceList;
	extern CLASS_IMPORT const BFTextFieldId TaxJurisAppl;
	extern CLASS_IMPORT const BFTextFieldId AcctType;
	extern CLASS_IMPORT const BFTextFieldId TaxType;
	extern CLASS_IMPORT const BFTextFieldId AcctDesignation;
	extern CLASS_IMPORT const BFTextFieldId BrokerCode;
	extern CLASS_IMPORT const BFTextFieldId InterCode;
	extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
}

namespace COMPLY_RULE
{
	extern CLASS_IMPORT const DString AcctRegistration;
	extern CLASS_IMPORT const DString DeathClaim;
	extern CLASS_IMPORT const DString TaxCompliant;
	extern CLASS_IMPORT const DString AccountholderRisk;
	extern CLASS_IMPORT const DString CRSComplyRule;
}

namespace CND
{  
	extern const long ERR_DOC_STATUS_BLANK;
	extern const long WARN_TAX_EXEMPT_AUTH_SHOULD_BE_UPDATED;
	extern const long WARN_REG_DOC_DEL_TAX_STAT_NEED_UPDATE;
}

namespace UAF 
{
	extern CLASS_IMPORT I_CHAR * const DOC_LIST;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
	// Field DD Id,				State Flags,		Group Flags 
	{ ifds::AccountNum,			BFCBO::NONE,			0 },
	{ ifds::EntityId,			BFCBO::NONE,			0 },
	{ ifds::ComplyRule,			BFCBO::NONE,			0 },
};

static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);
//******************************************************************************
RegDocumentList::RegDocumentList(BFAbstractCBO &parent)
: MFCanBFCbo(parent)
, m_requestData(ifds::DSTC0389_REQ)
{
	TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
	
	registerMemberData(NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL);	

	setObjectAsList();  	
}

//******************************************************************************
RegDocumentList::~RegDocumentList()
{
	TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY RegDocumentList::initNew(const DString& dstrAccountNum,
                                  const DString& dstrEntityId,
                                  const DString& dstrRegulatoryStandard,                     
                                  const DString& dstrRule,
                                  const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("initNew"));

	setFieldNoValidate(ifds::AccountNum, dstrAccountNum, idDataGroup);
	setFieldNoValidate(ifds::EntityId, dstrEntityId, idDataGroup);
	setFieldNoValidate(ifds::ComplyRule, dstrRule, idDataGroup);

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RegDocumentList::init(const DString& dstrAccountNum,
							   const DString& dstrEntityId,
							   const DString& dstrRegulatoryStandard,                     
							   const DString& dstrRule,
							   const BFDataGroupId& idDataGroup,
							   const DString& dstrTrack,
							   const DString& dstrPageName,
							   bool  bAcctRegDocListForDeadEntity)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));	

	WorkSessionEntityList *pWorkEntityList(NULL);
	Entity *pEntity(NULL);
	MFAccount *pMFAccount(NULL);

	if(!dstrEntityId.empty())
	{
		getWorkSession().getWorkSessionEntityList(pWorkEntityList);
		if(pWorkEntityList)
		{
			pWorkEntityList->getEntity(idDataGroup, dstrEntityId, pEntity);
		}
	}

	if(!dstrAccountNum.empty() && 
	   getWorkSession().getMFAccount(idDataGroup, dstrAccountNum, pMFAccount) <= WARNING && 
	   pMFAccount)
	{
		;
	}

	if(pMFAccount && pEntity)
	{
		m_requestData.setElementValue(ifds::Activity, dstrPageName);
		//for dead entities and new accounts - send in '0'
      
		if(dstrRule != COMPLY_RULE::DeathClaim && !pMFAccount->isNew()) // Account Registration
		{
			m_requestData.setElementValue(ifds::AccountNum, dstrAccountNum);
		}
		//for new entities - send in '0'
		if(!pEntity->isNew())
		{
			m_requestData.setElementValue(ifds::EntityId, dstrEntityId);
		}
		m_requestData.setElementValue(ifds::ComplyRule, dstrRule);
		m_requestData.setElementValue(ifds::RegulatoryStandard, dstrRegulatoryStandard);
		m_requestData.setElementValue(ifds::NextKey, NULL_STRING);
		m_requestData.setElementValue(ifds::Track, dstrTrack);

		setFieldNoValidate(ifds::AccountNum, dstrAccountNum, idDataGroup);
		setFieldNoValidate(ifds::EntityId, dstrEntityId, idDataGroup);
		setFieldNoValidate(ifds::ComplyRule, dstrRule, idDataGroup);
		setFieldNoValidate(ifds::ComplyRule, dstrRule, BF::HOST);

		DString mgmtCoIdOut;
		m_requestData.setElementValue(ifds::CompanyId, getMgmtCoId(mgmtCoIdOut));
      
		//During Account Registration , all registration documents needs to be added systematicaly when comply rule is Account Registartion
		// only during maintennace give the option of More button
		bool bMoreAppl = false;
		if(!pMFAccount->isNew() && COMPLY_RULE::AcctRegistration == dstrRule)
		{
			bMoreAppl = true;
		}
      
		ReceiveData(DSTC_REQUEST::REG_DOCLIST_INQUIRY, 
					m_requestData, 
					ifds::DSTC0389_VW, 
					DSTCRequestor(getSecurity(), !bMoreAppl)); //Implementing more button  
   	
		setDummyFlag(idDataGroup);
		autoAttachDefaultCRSRegDocs(idDataGroup, dstrEntityId);
		setDefaultStatusForAllRegDocs(idDataGroup);
		forceRegDocStatusUpdatedforNewAccounts(idDataGroup);
	}
	return GETCURRENTHIGHESTSEVERITY();
}
//*************************************************************************************
SEVERITY RegDocumentList::doCreateObject(const BFData& data, BFCBO*& pObjOut)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateObject"));
   	
	pObjOut = new RegDocument(*this);
	((RegDocument*)pObjOut)->init(const_cast<BFData&>(data));

	return(GETCURRENTHIGHESTSEVERITY());
}

//**************************************************************************************
SEVERITY RegDocumentList::doCreateNewObject(BFCBO *&pObjOut, DString &strKey, const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateNewObject"));
   	
	pObjOut = new RegDocument(*this);
	((RegDocument*)pObjOut)->initNew(idDataGroup);

	return(GETCURRENTHIGHESTSEVERITY());
}

//*********************************************************************************
bool RegDocumentList::isAnyStatusBlank(const BFDataGroupId &idDataGroup)
{   
	RegDocument *pRegDocument = NULL;
	bool	found = false;

	BFObjIter iter(*this, idDataGroup);

	while(!iter.end())
	{
		pRegDocument = dynamic_cast < RegDocument * >(iter.getObject());

		if(pRegDocument)
		{
			DString regDocId,
			regDocStatus;

			pRegDocument->getField(ifds::RegDocStatus, regDocStatus, idDataGroup);
			pRegDocument->getField(ifds::RegDocId, regDocId, idDataGroup);
			
			if(!regDocId.empty() && regDocStatus.empty())
			{
				found = true;
				break;
			}
		}
		++iter;
	}	
	return found;
}

//*********************************************************************************
SEVERITY RegDocumentList::setDummyFlag(const BFDataGroupId &idDataGroup)
{   
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION,  CLASSNAME, I_("setDummyFlag"));

	RegDocument *pRegDocument = NULL;

	BFObjIter iter(*this, idDataGroup);

	while(!iter.end())
	{
		DString strRegDocStatus = NULL_STRING;

		pRegDocument = dynamic_cast<RegDocument *>(iter.getObject());

		if(pRegDocument)
		{
			pRegDocument->getField(ifds::RegDocStatus, strRegDocStatus, idDataGroup);
			
			if(strRegDocStatus == NULL_STRING || strRegDocStatus.empty())
			{
				pRegDocument->setField(ifds::IsDocStatusBlank, I_("Y"), idDataGroup);
				pRegDocument->setFieldValid(ifds::RegDocStatus, idDataGroup, false);
			}
		}

		++iter;
	}
		
	return GETCURRENTHIGHESTSEVERITY();
}
//*******************************************************************************
SEVERITY RegDocumentList::doValidateAll(const BFDataGroupId& idDataGroup, long lValidateGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"));

	if(isAnyStatusBlank(idDataGroup))
	{
		ADDCONDITIONFROMFILE(CND::ERR_DOC_STATUS_BLANK);
	}

	DString dstrAccountNum, dstrEntityId;
	getField(ifds::AccountNum, dstrAccountNum, idDataGroup);
	getField(ifds::EntityId, dstrEntityId, idDataGroup);

	MFAccount *pMFAccount;
	if(dstrAccountNum.empty() ||
		getWorkSession().getMFAccount(idDataGroup, dstrAccountNum, pMFAccount) > WARNING ||
		!pMFAccount)
	{
		return GETCURRENTHIGHESTSEVERITY();
	}
	dstrEntityId.stripAll();

	ENTITIES_VECTOR acctOwnerEntities;
	pMFAccount->getAcctOwnerEntities(acctOwnerEntities, idDataGroup);
	bool isAcctOwnerFound = false;
	for(int i = 0; i<(int)acctOwnerEntities.size(); i++)
	{
		if(acctOwnerEntities[i] == dstrEntityId)
		{
			isAcctOwnerFound = true;
			break;
		}
	}
	
	if(!isAcctOwnerFound)
		return GETCURRENTHIGHESTSEVERITY();

	for(BFObjIter iter(*this, idDataGroup); !iter.end(); ++iter)
	{
		RegDocument* pRegDocument = dynamic_cast<RegDocument*>(iter.getObject());
		if((!iter.getObject()->hasUpdatedFields()|| iter.getObject()->isNew()) &&
			iter.getKey().getActivity() != OBJ_ACTIVITY_DELETED)
			continue;
		else if(iter.getKey().getActivity() == OBJ_ACTIVITY_DELETED)
		{
			DString dstrComplyRule;
			// if delete and impact taxpayer status, raise warning to update tax status
			getField(ifds::ComplyRule, dstrComplyRule, idDataGroup, false);

			if(dstrComplyRule == I_("FA"))  // Tax Compliant
			{
				if(pRegDocument->isTaxImpactTaxPayerStatus(idDataGroup))
					ADDCONDITIONFROMFILE(CND::WARN_REG_DOC_DEL_TAX_STAT_NEED_UPDATE);
			}
		}
	}

	return GETCURRENTHIGHESTSEVERITY();
}
//*********************************************************************************
SEVERITY  RegDocumentList::forceRegDocStatusUpdatedforNewAccounts(const BFDataGroupId &idDataGroup)
{   
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION,  CLASSNAME, I_("forceRegDocStatusUpdatedforNewAccounts"));

	RegDocument *pRegDocument = NULL;
	BFObjIter iter(*this, idDataGroup);    
	while(!iter.end())
	{
		pRegDocument = dynamic_cast<RegDocument *>(iter.getObject());
		if(pRegDocument)
		{
			DString dstrRegDocStatus;
			DString dstrOrgRegDocStatus;
			pRegDocument->getField(ifds::RegDocStatus, dstrRegDocStatus, idDataGroup);
			pRegDocument->getFieldBeforeImage(ifds::RegDocStatus,dstrOrgRegDocStatus);
			if(dstrRegDocStatus == OUTSTANDING && 
				(getParent()->isNew() || dstrOrgRegDocStatus.stripAll().empty()))
			{
				bool bCreatePermission = getWorkSession().hasCreatePermission(UAF::DOC_LIST);
				bool bUpdatePermission = getWorkSession().hasUpdatePermission(UAF::DOC_LIST);
				
				if(bCreatePermission || bUpdatePermission)
				{
					pRegDocument->setFieldUpdated(ifds::RegDocStatus, idDataGroup, true);
				}
			}
		}  
		++iter;
	}//while
	return GETCURRENTHIGHESTSEVERITY();
}


//*********************************************************************************
SEVERITY RegDocumentList::setDefaultStatusForAllRegDocs(const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION,  CLASSNAME, I_("setDefaultStatusForAllRegDocs"));

	DString dstrAutoDocTracking;
	getWorkSession().getOption(ifds::AutoDocTracking,  dstrAutoDocTracking, idDataGroup);
	MFAccount *pMFAccount = dynamic_cast<MFAccount*>(getParent());
	Demographics *pDemographics = NULL;
	Broker *pBroker = NULL;

	if(pMFAccount && dstrAutoDocTracking == YES)
	{
		DString dstrEPABroker, dstrBrokerCode, dstrBeforeRegulatoryStandard, dstrCurrentRegulatoryStandard;

		pMFAccount->getField(ifds::BrokerCode, dstrBrokerCode, idDataGroup);
		BFObjIter iter(*this, idDataGroup);

		if(pMFAccount->getBroker(pBroker, dstrBrokerCode, idDataGroup) <= WARNING && pBroker &&
			pMFAccount->getDemographicsList(pDemographics, idDataGroup) <= WARNING && pDemographics)
		{
			pBroker->getField(ifds::EPABroker, dstrEPABroker, idDataGroup);
			pDemographics->getFieldBeforeImage(ifds::RegulatoryStandard, dstrBeforeRegulatoryStandard);
			pDemographics->getField(ifds::RegulatoryStandard, dstrCurrentRegulatoryStandard, idDataGroup);

			//Only default document status when Regulatory Standard has been changed.
			while(!iter.end() && dstrBeforeRegulatoryStandard.stripAll() != dstrCurrentRegulatoryStandard.stripAll())
			{
				iter.getObject()->setField(ifds::RegDocStatus, dstrEPABroker == YES ? WAIVED:OUTSTANDING, idDataGroup);
				++iter;
			}
		}
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
SEVERITY RegDocumentList::autoAttachDefaultCRSRegDocs(const BFDataGroupId &idDataGroup, const DString& dstrEntityID)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION,  CLASSNAME, I_("autoAttachDefaultCRSRegDocs"));
    
	DString dstrCurrComplyRule,dstrTaxComplianceList;
	getField(ifds::ComplyRule, dstrCurrComplyRule, idDataGroup);
	getWorkSession().getOption(ifds::TaxComplianceList, dstrTaxComplianceList, idDataGroup, false);
	bool bAutoAttachDocuments = false;
	//if the current comply rule is not TaxComplyRule(TaxCompliance Radio button) return
	if(!isCodeInList(dstrCurrComplyRule, dstrTaxComplianceList))
		return GETCURRENTHIGHESTSEVERITY();
     
	// if the entity taxJurisdiction is not updated just return 
	if(!isEntityTaxJurisdictionUpdated(idDataGroup))
		return GETCURRENTHIGHESTSEVERITY();  
  
	RegDocument  *pAutoAttchedRegDoc = NULL;
	WorkSessionEntityList *pWorkEntityList = NULL;
	Entity *pEntity = NULL;
	DString dstrEntityId, dstrComplyRule, dstrEntityTaxJuris , dstrEntityType, 
			dstrRegEffectiveDate, dstrRegJurisdiction, dstrRegDocId;
	getCurrentEntityDetails(idDataGroup, dstrEntityID, dstrEntityTaxJuris, dstrEntityType);
	DString dstrCRSEntityList, dstrCRSActive;
	getWorkSession().getOption(ifds::CRSEntityList, dstrCRSEntityList, idDataGroup, false);
	getWorkSession().getOption(ifds::CRSActive, dstrCRSActive, idDataGroup, false);
	dstrCRSActive.upperCase();

	if(YES != dstrCRSActive ||                              // if the env is not CRS active
	   !isCodeInList(dstrEntityType, dstrCRSEntityList)) //if the current entity is not applicable return.
		return GETCURRENTHIGHESTSEVERITY();  

	BFObjIter iterRegDocumentList(*this, idDataGroup);
	RegDocumentTypeList *pRegDocumentTypeList = NULL; 
     
	//Step 1: Figure out how many dcouments to be attached.
	bool bAttachAll = true;
	//check if the TAX compalint document for CRS is alreday available
	DString dstrRegDocComplyRule;
	for(iterRegDocumentList; !iterRegDocumentList.end(); ++iterRegDocumentList)
	{
		iterRegDocumentList.getObject()->getField(ifds::RegDocComplyRule, dstrRegDocComplyRule, idDataGroup , false);
		if(COMPLY_RULE ::CRSComplyRule == dstrRegDocComplyRule)
		{
			bAttachAll = false;
			break;
		}
	}

	//Step 2: get the default documet list and attach the CRS document.
	getRegDocumentTypeList(idDataGroup, pRegDocumentTypeList);
	BFObjIter iterDefaultDocumentsList(*pRegDocumentTypeList, idDataGroup);   
	DString currentBusinessDate;
	getWorkSession().getOption(ifds::CurrBusDate, currentBusinessDate, BF::HOST, false);
	for(iterDefaultDocumentsList ; !iterDefaultDocumentsList.end();  ++iterDefaultDocumentsList)
	{
		iterDefaultDocumentsList.getObject()->getField(ifds::RegDocComplyRule, dstrComplyRule, idDataGroup , false);
		iterDefaultDocumentsList.getObject()->getField(ifds::TaxJuris, dstrRegJurisdiction, idDataGroup , false);
		iterDefaultDocumentsList.getObject()->getField(ifds::RegDocId, dstrRegDocId, idDataGroup , false);  

		if(COMPLY_RULE::CRSComplyRule != dstrComplyRule)
			continue;
		bool bAttachDocument = false;
		bAttachDocument = bAttachAll ? true : !(isDuplicateDocument(dstrComplyRule, dstrRegDocId, dstrEntityTaxJuris, 
																		currentBusinessDate, DATE9999, idDataGroup));
		if(bAttachDocument)
		{
			DString dstrKey;
			BFObjectKey objKey(dstrKey, idDataGroup);
			pAutoAttchedRegDoc = dynamic_cast<RegDocument*>(getNewListItem(objKey));          
			if(pAutoAttchedRegDoc)
			{
				pAutoAttchedRegDoc->setField(ifds::RegDocId, dstrRegDocId, idDataGroup, false);
				pAutoAttchedRegDoc->setField(ifds::EffectiveDate, currentBusinessDate, idDataGroup, false);
				pAutoAttchedRegDoc->setField(ifds::RegDocComplyRule, COMPLY_RULE ::CRSComplyRule, idDataGroup, false);
				bool bJurisdictionAppl = JURS_UNASSIGNED == dstrRegJurisdiction || dstrRegJurisdiction.empty() ? true : false;
				DString dstrTaxJurisAppl = bJurisdictionAppl ? YES : NULL_STRING;
				pAutoAttchedRegDoc->setField(ifds::TaxJurisAppl, dstrTaxJurisAppl, idDataGroup, false);
				if(bJurisdictionAppl)
				{
					pAutoAttchedRegDoc->setField(ifds::RegDocJurisdiction, dstrEntityTaxJuris, idDataGroup, false);
				}
				else
				{
					pAutoAttchedRegDoc->setField(ifds::RegDocJurisdiction, dstrRegJurisdiction, idDataGroup, false);
				}
				setObject(objKey, pAutoAttchedRegDoc);
				bAutoAttachDocuments = true;
			}            
		} //bAttachDocument    
	}//for
    //remove the dummy 
    // 1 if document list is empty = bAttachAll mostly during NASU 
    // 2 AND atleast one CRS document has been auto attached to the system.
    //
	if(bAttachAll && bAutoAttachDocuments)
	{
		DString dstrRegDocName, dstrRegDocStatus;
		iterRegDocumentList.begin();
		for(iterRegDocumentList ; !iterRegDocumentList.end();  ++iterRegDocumentList)
		{
			iterRegDocumentList.getObject()->getField(ifds::RegDocName, dstrRegDocName, idDataGroup, false);
			iterRegDocumentList.getObject()->getField(ifds::RegDocStatus, dstrRegDocStatus, idDataGroup, false);
			if(dstrRegDocComplyRule.empty() && dstrRegDocStatus.empty()) 
			{
				iterRegDocumentList.removeObjectFromMap();
				break;
			}
		} 
	}  
	return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
void RegDocumentList::getCurrentEntityDetails(const BFDataGroupId &idDataGroup, const DString& dstrEntityID,  DString& dstrEntityTaxJuris , DString& dstrEntityType)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION,  CLASSNAME, I_("getEntityTaxJuris"));

	DString  dstrEntityId = dstrEntityID;
	WorkSessionEntityList *pWorkEntityList = NULL;
	Entity *pEntity = NULL;
	if(dstrEntityId.empty())
	   m_requestData.getElementValue(ifds::EntityId, dstrEntityId);   
	if(!dstrEntityId.empty())
	{
		if(WARNING >= getWorkSession().getWorkSessionEntityList(pWorkEntityList) && pWorkEntityList)
		{
			pWorkEntityList->getEntity(idDataGroup, dstrEntityId, pEntity);
			if(pEntity)
			{
				pEntity->getField(ifds::TaxJuris, dstrEntityTaxJuris, idDataGroup, false);
				dstrEntityType = pEntity->getEntityType();
			}
		}
	}    
}
//*********************************************************************************
bool RegDocumentList::isDuplicateDocument(DString& dstrRegDocId, DString& dstrComplyRule, DString& dstrJurisdiction,  DString& dstrEffectiveDate, 
                                          DString dstrExpireDate, const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION,  CLASSNAME, I_("isDocumentAlreadyAttached"));

	bool bDuplicateDocument = false;
	for(BFObjIter iter(*this, idDataGroup); !iter.end(); ++iter)
	{
		DString dstrIterRegDocId, dstrIterJurisdiction;
		iter.getObject()->getField(ifds::RegDocId, dstrIterRegDocId, idDataGroup);
		iter.getObject()->getField(ifds::RegDocJurisdiction, dstrIterJurisdiction, idDataGroup);
		if(dstrRegDocId != dstrIterRegDocId ||  dstrJurisdiction != dstrIterJurisdiction)
			continue;

		DString dstrIterEffectiveDate, dstrIterExpireDate;
		iter.getObject()->getField(ifds::EffectiveDate, dstrIterEffectiveDate,idDataGroup);
		iter.getObject()->getField(ifds::ExpireDate, dstrIterExpireDate, idDataGroup);
       
		bDuplicateDocument= DSTCommonFunctions::dateRangesOverlap(dstrEffectiveDate, dstrExpireDate, dstrIterEffectiveDate, dstrIterExpireDate) ?
							true:false;     
	}
	return bDuplicateDocument;
}

//*********************************************************************************
bool RegDocumentList::isEntityTaxJurisdictionUpdated(const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION,  CLASSNAME, I_("isEntityTaxJurisdictionUpdated"));

	bool bEntityTaxJurisdictionUpdated = false;
	DString  dstrEntityId, dstrEntityCurrTaxJuris, dstrEntityTaxJuris;
	WorkSessionEntityList *pWorkEntityList = NULL;
	Entity *pEntity = NULL;
	getField(ifds::EntityId, dstrEntityId, idDataGroup); 
	if(!dstrEntityId.empty())
	{
		if(WARNING >= getWorkSession().getWorkSessionEntityList(pWorkEntityList) && pWorkEntityList)
			{
				pWorkEntityList->getEntity(idDataGroup, dstrEntityId, pEntity);
				if(pEntity)
				{
					if(pEntity->isNew()) //new entity added or NASU
					{
						bEntityTaxJurisdictionUpdated = true;
					}
					else
					{
						pEntity->getField(ifds::TaxJuris, dstrEntityCurrTaxJuris, idDataGroup, false);
						pEntity->getFieldBeforeImage(ifds::TaxJuris, dstrEntityTaxJuris,false);
						bEntityTaxJurisdictionUpdated = (dstrEntityTaxJuris.stripAll() != dstrEntityCurrTaxJuris.stripAll());
					} 
				}
			}
	}    
	return bEntityTaxJurisdictionUpdated;
}
//************************************************************************************
SEVERITY RegDocumentList::getRegDocumentTypeList(const BFDataGroupId &idDataGroup, RegDocumentTypeList *&pRegDocumentTypeList)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getRegDocumentTypeList"));

	DString dstrTaxComplianceList;
	//removal of harcoded FA..Now this can be FA,CRS,AAA,BBB,CCC,.....based on environment config
	getWorkSession().getOption(ifds::TaxComplianceList, dstrTaxComplianceList, idDataGroup, false);

	MFAccount *pMFAccount = NULL ;
	pRegDocumentTypeList = new RegDocumentTypeList(*this);
	/* Getting TaxJuris and Entity.EffectiveDate at Entity */
	DString dstrEntityId, dstrTaxJuris, dstrEntityType, dstrEffectiveDate; 
	getField(ifds::EntityId, dstrEntityId, idDataGroup);
	WorkSessionEntityList *pWorkEntityList = NULL;
	Entity *pEntity = NULL;
	if(dstrEntityId.empty())
		m_requestData.getElementValue(ifds::EntityId, dstrEntityId);   
	if(!dstrEntityId.empty())
	{
		if(WARNING >= getWorkSession().getWorkSessionEntityList(pWorkEntityList) && pWorkEntityList)
		{
			pWorkEntityList->getEntity(idDataGroup, dstrEntityId, pEntity);
			if(pEntity)
			{
				pEntity->getField(ifds::TaxJuris, dstrTaxJuris, idDataGroup, false);
				pEntity->getField(ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false);
			}
		}
	}   

	/* Getting AcctType and TaxType at Account */
	DString dstrAccountNum, dstrAcctType, dstrTaxType, dstrAcctDesignation, dstrBrokerCode, dstrInterCode;
	getField(ifds::AccountNum, dstrAccountNum, idDataGroup);
	if(!dstrAccountNum.empty() && 
		getWorkSession().getMFAccount(idDataGroup, dstrAccountNum, pMFAccount) <= WARNING && 
		pMFAccount)
	{
		pMFAccount->getField(ifds::AcctType, dstrAcctType, idDataGroup);
		pMFAccount->getField(ifds::TaxType, dstrTaxType, idDataGroup);
		pMFAccount->getField(ifds::AcctDesignation, dstrAcctDesignation, idDataGroup);
		if(dstrAcctDesignation == INTERMEDIARY_ACCT_DESIGNATION)
			pMFAccount->getField(ifds::InterCode, dstrInterCode, idDataGroup);
		else
			pMFAccount->getField(ifds::BrokerCode, dstrBrokerCode, idDataGroup);
	}

	if(WARNING < pRegDocumentTypeList->init(dstrTaxComplianceList, dstrAcctType, dstrTaxType, dstrTaxJuris, 
											dstrAcctDesignation, dstrBrokerCode, dstrInterCode, dstrEffectiveDate, I_("N"), NULL_STRING ) && pRegDocumentTypeList)
	{
		delete pRegDocumentTypeList;
		pRegDocumentTypeList = NULL;
	}
	return GETCURRENTHIGHESTSEVERITY();	
}
//******************************************************************************
SEVERITY RegDocumentList::getMore()
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getMore"));

	if(doMoreRecordsExist())
	{
		ReceiveData(DSTC_REQUEST::REG_DOCLIST_INQUIRY, m_requestData, ifds::DSTC0389_VW, DSTCRequestor(getSecurity(), false));
	}

	return(GETCURRENTHIGHESTSEVERITY());
}

//*******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RegDocumentList.cpp-arc  $
// 
//    Rev 1.12   Aug 17 2012 19:21:52   wutipong
// IN3058961 P179630FN01 FATCA - Acct Doc List and Tax Exempt Auth screens issues
// 
//    Rev 1.11   Jul 23 2012 12:45:12   wutipong
// PETP0179630_FN01 FATCA Account Entity Document Tracking
// 
//    Rev 1.10   Dec 09 2008 15:25:56   jankovii
// IN 1498625 - error message s/b add and specified
// 
//    Rev 1.9   04 Nov 2008 13:11:46   popescu
// KYC-AML fixes after system integrated testing
// 
//    Rev 1.8   03 Nov 2008 17:32:50   popescu
// KYC/AML - Joint accounts feature - after System Integrated Testing
// 
//    Rev 1.7   31 Oct 2008 16:19:00   popescu
// KYC/AML - joint accounts feature
// 
//    Rev 1.6   Oct 28 2008 08:33:46   jankovii
// PET 59888 FN03 AML KYC.
// 
//    Rev 1.5   Aug 29 2008 14:34:42   jankovii
// IN 1388930.
// 
//    Rev 1.4   Aug 28 2008 14:29:16   jankovii
// IN 1388930 - NASU flow does not update document list unless at least one document.
// 
//    Rev 1.3   Aug 22 2008 16:03:56   jankovii
// IN 1386917 - PET59888FN01-Add KYCCountryCode that will be used by AWD.
// 
//    Rev 1.2   Aug 01 2008 11:43:54   jankovii
// PET 59888 FN01 AML Enhancement.
 */