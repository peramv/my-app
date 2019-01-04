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
//    Copyright 2004 By International Financial Data Services.
//
//
//********************************************************************************
//
// ^FILE   : RegDocument.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//********************************************************************************
#include "stdafx.h"
#include "RegDocument.hpp"
#include "RegDocumentList.hpp"
#include "RegDocumentTypeList.hpp"
#include "mfaccount.hpp"
#include "Entity.hpp"
#include "AccountEntityXref.hpp"
#include "TranslationTable.hpp"
#include "mgmtco.hpp"

#include <ifastdataimpl\dse_dstc0389_vw.hpp>
#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_err_expire_date_lessthan_effective_date.h>

#include "entityregjurisdetailslist.hpp"
#include <ifastdataimpl/dse_dstc0458_vwrepeat_record.hpp>

namespace
{
	const I_CHAR * const CLASSNAME			= I_("RegDocument");
	const I_CHAR * const DATE9999			= I_("12319999");
	const I_CHAR * const RECEIVED			= I_("R");
	const I_CHAR * const WAIVED 			= I_("W");
	const I_CHAR * const OUTSTANDING		= I_("O");
	const I_CHAR * const YES				= I_("Y");
	const I_CHAR * const NO					= I_("N");
	const I_CHAR * const JURS_UNASSIGNED	= I_("0000");
	const I_CHAR * const ARIDS				= I_("ARIDS");
}

namespace UAF
{
	extern CLASS_IMPORT I_CHAR * const REG_DOCUMENT_WAVESTATUS;
}


namespace ifds
{  
	extern CLASS_IMPORT const BFTextFieldId IsDocStatusBlank;

	extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
	extern CLASS_IMPORT const BFDateFieldId ExpireDate;
	extern CLASS_IMPORT const BFDateFieldId RequestDate;
	extern CLASS_IMPORT const BFTextFieldId RefNum;
	extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
	extern CLASS_IMPORT const BFTextFieldId ComplyRule;
	extern CLASS_IMPORT const BFTextFieldId FieldCrossEdit2;
	extern CLASS_IMPORT const BFTextFieldId TaxExType;
	extern CLASS_IMPORT const BFNumericFieldId AccountNum;
	extern CLASS_IMPORT const BFTextFieldId AutoDocTracking;
	extern CLASS_IMPORT const BFTextFieldId TaxImpact;
	extern CLASS_IMPORT const BFTextFieldId JurisdictionAppl;
	extern CLASS_IMPORT const BFTextFieldId TaxComplianceList;
	extern CLASS_IMPORT const BFDateFieldId RegEffectiveDate;
	extern CLASS_IMPORT const BFTextFieldId TaxJuris;
	extern CLASS_IMPORT const BFTextFieldId TaxJurisAppl;
	extern CLASS_IMPORT const BFTextFieldId CRSEntityList;
	extern CLASS_IMPORT const BFTextFieldId EffExpDate;
	extern CLASS_IMPORT const BFNumericFieldId EntityId;
	extern CLASS_IMPORT const BFTextFieldId EntityType;   
}

namespace CND
{
	extern CLASS_IMPORT const long ERR_DOCUMENT_OVERLAPPED;
	extern CLASS_IMPORT const long WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_SICAV;
	extern CLASS_IMPORT const long WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_OEIC;
	extern CLASS_IMPORT const long ERR_DOCUMENT_DATE_RECEIVED_MANDATORY;
	CIFast_IFast_ifastcbo_err_expire_date_lessthan_effective_date;
	extern CLASS_IMPORT const long ERR_ERJD_EXISTS;
}

namespace COMPLY_RULE
{
	extern CLASS_EXPORT const DString AcctRegistration	= I_("0");
	extern CLASS_EXPORT const DString DeathClaim		= I_("1");
	extern CLASS_EXPORT const DString TaxCompliant		= I_("FA");
	extern CLASS_EXPORT const DString AccountholderRisk = I_("AR");
	extern CLASS_EXPORT const DString CRSComplyRule     = I_("CRS");
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
	// Field DD Id,				State Flags,                 Group Flags 
    { ifds::RegDocName,			BFCBO::NONE,                     0 },
    { ifds::RegDocId,			BFCBO::REQUIRED,                 0 },
    { ifds::RegDocStatus,		BFCBO::REQUIRED,                 0 },
    { ifds::DocReceivedDate,	BFCBO::NONE,                     0 },
    { ifds::RegDocRemarks,		BFCBO::NONE,                     0 },
    { ifds::IsDocStatusBlank,	BFCBO::NONE,                     0 },
    { ifds::EffectiveDate,		BFCBO::REQUIRED,                 0 },
    { ifds::RequestDate, 		BFCBO::REQUIRED,                 0 },
    { ifds::ExpireDate, 		BFCBO::NONE,                     0 },
    { ifds::RefNum,    			BFCBO::NONE,                     0 },
    { ifds::FieldCrossEdit2,	BFCBO::IMMEDIATE_VALIDATION,     0 },
    { ifds::RegDocJurisdiction,	BFCBO::NONE,                     0 },
    { ifds::RegDocComplyRule,	BFCBO::NONE,                     0 },
    { ifds::TaxJurisAppl,		BFCBO::CALCULATED_FIELD,         0 },
    { ifds::TransmitMode,		BFCBO::NONE,                     0 },
	{ ifds::EffExpDate,			BFCBO::IMMEDIATE_VALIDATION,	 0 },
    { ifds::CountryOfIssue,		BFCBO::NONE,                     0 },
    { ifds::VerifiedDate,		BFCBO::NONE,                     0 },
    { ifds::DocSource,			BFCBO::NONE,                     0 },
    { ifds::IDMethod,			BFCBO::NONE,                     0 },
};

static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);

const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = 
{
	//  Object Label,				State Flags,			Group Flags 
	{ I_("RegDocumentTypeList"),	BFCBO::NONE,				0 },
};

static const int NUM_OBJECTS = sizeof(classObjectInfo) / sizeof(BFCBO::CLASS_OBJECT_INFO);

//******************************************************************************
RegDocument::RegDocument(BFAbstractCBO &parent)
: MFCanBFCbo(parent)
{
	TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
	registerMemberData(NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL);	

	addCrossEdit(ifds::FieldCrossEdit2, ifds::EffectiveDate);
	addCrossEdit(ifds::FieldCrossEdit2, ifds::ExpireDate);
	addCrossEdit(ifds::FieldCrossEdit2, ifds::RegDocId);
	addCrossEdit(ifds::FieldCrossEdit2, ifds::RegDocComplyRule);
	addCrossEdit(ifds::FieldCrossEdit2, ifds::RegDocJurisdiction);
	addCrossEdit(ifds::EffExpDate, ifds::EffectiveDate);
	addCrossEdit(ifds::EffExpDate, ifds::ExpireDate);
}

//******************************************************************************
RegDocument::~RegDocument()
{
	TRACE_DESTRUCTOR(CLASSNAME);
}  

//*******************************************************************************
SEVERITY RegDocument::init(const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));
	
	commInit(idDataGroup);

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RegDocument::init(const BFData& data)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));	

	attachDataObject(const_cast<BFData&>(data), false); 

	commInit(BF::HOST);

	return(GETCURRENTHIGHESTSEVERITY());
}

//*********************************************************************************
SEVERITY RegDocument::doValidateField(const BFFieldId& idField, 
									  const DString& dstrValue, 
									  const BFDataGroupId& idDataGroup)
{

	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField"));   

	if(idField == ifds::FieldCrossEdit2)
	{
		RegDocumentList *pRegDocumentList = dynamic_cast<RegDocumentList*>(getParent());

		DString dstrRegDocId, dstrEffectiveDate, dstrExpireDate, dstrJurisdiction;
      
		getField(ifds::RegDocId, dstrRegDocId, idDataGroup);
		getField(ifds::EffectiveDate, dstrEffectiveDate,idDataGroup);
		getField(ifds::ExpireDate, dstrExpireDate, idDataGroup);
		getField(ifds::RegDocJurisdiction, dstrJurisdiction, idDataGroup);

		for(BFObjIter iter(*pRegDocumentList, idDataGroup);
			!iter.end();
			++iter)
		{
			DString dstrIterRegDocId, dstrIterJurisdiction;
			iter.getObject()->getField(ifds::RegDocId, dstrIterRegDocId, idDataGroup);
			iter.getObject()->getField(ifds::RegDocJurisdiction, dstrIterJurisdiction, idDataGroup);
			if(dstrRegDocId != dstrIterRegDocId || dstrJurisdiction != dstrIterJurisdiction ||
			   iter.getObject() == this)
				continue;

			DString dstrIterEffectiveDate, dstrIterExpireDate;
			iter.getObject()->getField(ifds::EffectiveDate, dstrIterEffectiveDate,idDataGroup);
			iter.getObject()->getField(ifds::ExpireDate, dstrIterExpireDate, idDataGroup);
         
			if(DSTCommonFunctions::dateRangesOverlap(
				dstrEffectiveDate, dstrExpireDate,
				dstrIterEffectiveDate, dstrIterExpireDate))
			{
				ADDCONDITIONFROMFILE(CND::ERR_DOCUMENT_OVERLAPPED);
				break;
			}
		}      
	}
	else if(idField == ifds::DocReceivedDate) 
	{
		DString status, dateReceived;	
		getField(ifds::RegDocStatus, status, idDataGroup);	

		// FATCA 1B - ‘Date Received’ is mandatory when status was changed to 'Received'		
		if(status == RECEIVED) 
		{	
			getField(ifds::DocReceivedDate, dateReceived, idDataGroup);
			if(dateReceived == NULL_STRING || dateReceived.empty() || (DSTCommonFunctions::CompareDates(dateReceived,DATE9999) == DSTCommonFunctions::EQUAL))
				ADDCONDITIONFROMFILE(CND::ERR_DOCUMENT_DATE_RECEIVED_MANDATORY);   
		}	   	  
	}
	else if(idField == ifds::EffExpDate)
	{
		DString dstrEffectiveDate, dstrExpireDate;  
		getField(ifds::EffectiveDate, dstrEffectiveDate,idDataGroup);
		getField(ifds::ExpireDate, dstrExpireDate, idDataGroup);

		if(DSTCommonFunctions::CompareDates(dstrEffectiveDate, dstrExpireDate) != DSTCommonFunctions::FIRST_EARLIER) 
		{
			CND::CIFast_IFast_ifastcbo_err_expire_date_lessthan_effective_date err_expdate_lessthan_effdate; 
			ADDCONDITIONFROMOBJECT(err_expdate_lessthan_effdate);
		}
	}	
   	return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
void RegDocument::doInitWithDefaultValues(const BFDataGroupId& idDataGroup)
{
	DString currentBusinessDate;
	getWorkSession().getOption(ifds::CurrBusDate, 
							   currentBusinessDate, 
							   BF::HOST, 
							   false);
   
	setFieldNoValidate(ifds::EffectiveDate, currentBusinessDate, idDataGroup, false);
	setFieldNoValidate(ifds::RequestDate, currentBusinessDate, idDataGroup, false);
	setFieldNoValidate(ifds::ExpireDate, DATE9999, idDataGroup, false);
	setFieldNoValidate(ifds::RegDocStatus, OUTSTANDING, idDataGroup, false);
	setFieldNoValidate(ifds::RegDocJurisdiction, NULL_STRING, idDataGroup, false);
	setFieldValid(ifds::RegDocStatus, idDataGroup, false);
}

//****************************************************************************
SEVERITY RegDocument::initNew(const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("initNew"));
	commInit(idDataGroup);

	DString dstrComplyRule;
	getParent()->getField(ifds::ComplyRule, dstrComplyRule, idDataGroup);

	bool bReadOnly = dstrComplyRule != COMPLY_RULE::TaxCompliant && dstrComplyRule != COMPLY_RULE::CRSComplyRule;

	for(int i = 0; i<NUM_FIELDS; i++)
	{
		setFieldReadOnly(classFieldInfo[i].getFieldId(), idDataGroup, bReadOnly);
	}

	if(dstrComplyRule == COMPLY_RULE::AcctRegistration)
		setFieldReadOnly(ifds::RegDocId, idDataGroup, false);

	return(GETCURRENTHIGHESTSEVERITY());
}
//*******************************************************************************

SEVERITY RegDocument::commInit(const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("commInit"));
	
	DString status, dateReceived, dstRemarks;
	bool bReadOnly = true;	  

	getField(ifds::RegDocStatus, status, idDataGroup);
	getField(ifds::DocReceivedDate, dateReceived, idDataGroup);
	status.stripAll();
	if(status == RECEIVED || status == WAIVED)
	{
		bReadOnly = false;
	}
	if(status == NULL_STRING)//default to schema default "O"
	{
		setFieldNoValidate(ifds::RegDocStatus, OUTSTANDING, idDataGroup, false);
		setFieldValid(ifds::RegDocStatus, idDataGroup, false);
	}
	if(dateReceived == NULL_STRING || dateReceived.empty())
	{
		setFieldNoValidate(ifds::DocReceivedDate, DATE9999, idDataGroup, true, true, false, false); 
	}

	setFieldReadOnly(ifds::DocReceivedDate, idDataGroup, bReadOnly);   

	BFProperties *pBFRegStatus = getFieldProperties(ifds::RegDocStatus, idDataGroup);
	DString		 statusSet, dstrAutoDocTracking;

	getWorkSession().getOption(ifds::AutoDocTracking, dstrAutoDocTracking, idDataGroup);

	pBFRegStatus->getAllSubstituteValues(statusSet);
	if(!getWorkSession().hasUpdatePermission(UAF::REG_DOCUMENT_WAVESTATUS) && dstrAutoDocTracking == NO)
	{
		statusSet = removeItemFromSubtList(statusSet, WAIVED);
	}
	
	setFieldAllSubstituteValues(ifds::RegDocStatus, idDataGroup, statusSet);
	setDocIdSubstitution(idDataGroup);

	// for existing data the TaxJurisAppl if RegDocJurisdiction is not empty
	if(!isNew())
	{
		RegDocumentTypeList *pRegDocumentTypeList = NULL;
		DString  dstrDocumentJurisdiction, dstrPrntComplyRule;
		getParent()->getField(ifds::ComplyRule, dstrPrntComplyRule, idDataGroup);

		if(dstrPrntComplyRule == COMPLY_RULE::AcctRegistration)
			getRegDocumentTypeList(idDataGroup,  pRegDocumentTypeList, ARIDS); 
		else
			getRegDocumentTypeList(idDataGroup,  pRegDocumentTypeList); 

		if(pRegDocumentTypeList != NULL) 
		{	
			DString dstrRegDocId;
			getField(ifds::RegDocId, dstrRegDocId, idDataGroup);				
			DString strObjKey;
			pRegDocumentTypeList->buildStrKey(strObjKey, dstrRegDocId);
			BFObjIter iter(*pRegDocumentTypeList, idDataGroup);			
			iter.positionByKey(strObjKey);			
			if(!iter.end())
			{    
				iter.getObject()->getField(ifds::TaxJuris, dstrDocumentJurisdiction, idDataGroup);
			}
		}

		bool bJurisdictionAppl = JURS_UNASSIGNED == dstrDocumentJurisdiction || dstrDocumentJurisdiction.empty() ? true : false;
		DString dstrTaxJurisAppl = bJurisdictionAppl ? YES : NULL_STRING;
		setField(ifds::TaxJurisAppl, dstrTaxJurisAppl, idDataGroup, false);
	}

	TranslationTable *pTranslationTable = NULL;
	if(getMgmtCo().getTranslationTable(I_("IDM"), pTranslationTable) <= WARNING && pTranslationTable)
	{
		DString subList;
		pTranslationTable->getSubstitutionList(subList);
		setFieldAllSubstituteValues(ifds::IDMethod, idDataGroup, subList);
	}
	return GETCURRENTHIGHESTSEVERITY();
}
//*******************************************************************************

SEVERITY RegDocument::doApplyRelatedChanges(const BFFieldId& idField, const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));

	if(idField == ifds::RegDocStatus)
	{
		DString status, dateReceived;
		bool bReadOnly = false;	  

		getField(ifds::RegDocStatus, status, idDataGroup);

		if(status == OUTSTANDING)
		{
			bReadOnly = true;
			setFieldNoValidate(ifds::DocReceivedDate, DATE9999, idDataGroup, true, true, false, false); 
		}

		setFieldReadOnly(ifds::DocReceivedDate, idDataGroup, bReadOnly);  

		// FATCA 1B - ‘Date Received’ is mandatory when status was changed to 'Received'
		bool bRegDocStatusReceived = (status == RECEIVED);
		setFieldValid(ifds::DocReceivedDate, idDataGroup, !bRegDocStatusReceived);
	}

	if(idField == ifds::RegDocId)
	{  
		DString dstrRegDocName, dstrEntityJurisdiction, dstrEntityType, dstrRegDocComplyRule;
		getField(ifds::RegDocId, dstrRegDocName, idDataGroup, true);
		setField(ifds::RegDocName, dstrRegDocName, idDataGroup);
		RegDocumentTypeList *pRegDocumentTypeList = NULL;
		DString  dstrDocumentJurisdiction, dstrPrntComplyRule;
		getParent()->getField(ifds::ComplyRule, dstrPrntComplyRule, idDataGroup);

		if(dstrPrntComplyRule == COMPLY_RULE::AcctRegistration)
			getRegDocumentTypeList(idDataGroup,  pRegDocumentTypeList, ARIDS); 
		else
			getRegDocumentTypeList(idDataGroup,  pRegDocumentTypeList); 

		if(pRegDocumentTypeList != NULL) 
		{	
			DString dstrRegDocId;
			getField(ifds::RegDocId, dstrRegDocId, idDataGroup);				
			DString strObjKey;
			pRegDocumentTypeList->buildStrKey(strObjKey, dstrRegDocId);
			BFObjIter iter(*pRegDocumentTypeList, idDataGroup);			
			iter.positionByKey(strObjKey);			
			if(!iter.end())
			{    
				iter.getObject()->getField(ifds::TaxJuris, dstrDocumentJurisdiction, idDataGroup);
				iter.getObject()->getField(ifds::RegDocComplyRule, dstrRegDocComplyRule, idDataGroup);        
			}
		}
		setField(ifds::RegDocComplyRule, dstrRegDocComplyRule, idDataGroup, false);

		if(dstrRegDocComplyRule == ARIDS)
		{
			DString currentBusinessDate;
			getWorkSession().getOption(ifds::CurrBusDate, currentBusinessDate, BF::HOST, false);

			setField(ifds::RegDocStatus, RECEIVED, idDataGroup, true, true);
			setField(ifds::RequestDate, currentBusinessDate, idDataGroup, true, true);
			setField(ifds::DocReceivedDate, currentBusinessDate, idDataGroup, true, true);
			setField(ifds::VerifiedDate, currentBusinessDate, idDataGroup, true, true);

			for(int i = 0; i<NUM_FIELDS; i++)
			{
				if(classFieldInfo[i].getFieldId() != ifds::RegDocId)
					setFieldReadOnly(classFieldInfo[i].getFieldId(), idDataGroup, false);
			}
		}		
		RegDocumentList *pRegDocumentList = dynamic_cast<RegDocumentList*>(getParent());
		bool bJurisdictionAppl = JURS_UNASSIGNED == dstrDocumentJurisdiction || dstrDocumentJurisdiction.empty() ? true : false;
		DString dstrTaxJurisAppl = bJurisdictionAppl ? YES : NULL_STRING;
		setField(ifds::TaxJurisAppl, dstrTaxJurisAppl, idDataGroup, false);
		if(pRegDocumentList && bJurisdictionAppl)
		{
			DString dstrEntityID;
			getParent()->getField(ifds::EntityId, dstrEntityID, idDataGroup);
			pRegDocumentList->getCurrentEntityDetails(idDataGroup, dstrEntityID, dstrEntityJurisdiction, dstrEntityType);      
			setField(ifds::RegDocJurisdiction, dstrEntityJurisdiction, idDataGroup, false);               
		}
		else
		{
			setField(ifds::RegDocJurisdiction, dstrDocumentJurisdiction, idDataGroup, false);               
		}
		setFieldRequired(ifds::RegDocJurisdiction, idDataGroup, bJurisdictionAppl); 
	}

	if(idField == ifds::RegDocId || idField == ifds::EffectiveDate)
	{
		DString dstrExpireDate = DATE9999; 
		DString dstrTaxExType;

		RegDocumentTypeList *pRegDocumentTypeList = NULL;
		getRegDocumentTypeList(idDataGroup,  pRegDocumentTypeList); 
		//dynamic_cast<RegDocumentTypeList*>(getObject(I_("RegDocumentTypeList"), idDataGroup));  //moving this to a common function getRegDocumentTypeList

		if(pRegDocumentTypeList != NULL) 
		{	
			DString dstrRegDocId;
			getField(ifds::RegDocId, dstrRegDocId, idDataGroup);				
			DString strObjKey;
			pRegDocumentTypeList->buildStrKey(strObjKey, dstrRegDocId);

			BFObjIter iter(*pRegDocumentTypeList, idDataGroup);
			
			iter.positionByKey(strObjKey);
			
			if(!iter.end())
				iter.getObject()->getField(ifds::TaxExType, dstrTaxExType,idDataGroup);
		}

		// FATCA 1B - expire date is not mandatory
		/*if(dstrTaxExType == I_("W8"))
		{
			DString dstrEffectiveDate;
			getField(ifds::EffectiveDate, dstrEffectiveDate, idDataGroup);
			
			int year = DSTCommonFunctions::getYearFromUnFormattedDate(dstrEffectiveDate);
			year += 3;
			
			DSTCommonFunctions::getEndOfMonthUnFormattedDate(12, year, dstrExpireDate);
			
		}*/

		//setFieldNoValidate(ifds::ExpireDate, dstrExpireDate, idDataGroup, false, false, true, true);       
	}
	return(GETCURRENTHIGHESTSEVERITY());
}
//*******************************************************************************
SEVERITY RegDocument::setDocIdSubstitution(const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setDocIdSubstitution"));

	DString dstrSubListDocName, dstrComplyRule;  
	getParent()->getField(ifds::ComplyRule, dstrComplyRule, idDataGroup);
	DString dstrTaxComplianceList;
	//removal of harcoded FA..Now this can be FA,CRS,AAA,BBB,CCC,.....based on environment config
	getWorkSession().getOption(ifds::TaxComplianceList, dstrTaxComplianceList, idDataGroup, false);

	//if(dstrComplyRule != COMPLY_RULE::TaxCompliant)
	if(isCodeInList(dstrComplyRule, dstrTaxComplianceList))
	{	
		DString key = I_("RegDocumentTypeList");
		RegDocumentTypeList *pRegDocumentTypeList = NULL;
		//dynamic_cast<RegDocumentTypeList*>(getObject(key, idDataGroup));//moving this to a common function getRegDocumentTypeList
		getRegDocumentTypeList(idDataGroup,  pRegDocumentTypeList); 

		if(pRegDocumentTypeList == NULL) 
		{
			pRegDocumentTypeList = new RegDocumentTypeList(*this);
			pRegDocumentTypeList->init(dstrComplyRule);

			setObject(pRegDocumentTypeList, key);
		}

		if(pRegDocumentTypeList != NULL) 
		{
			DString subset, dstrEntityJurisdiction, dstrEntityType, dstrCRSEntityList, dstrExcludeComplyRule = NULL_STRING ;
			//Only CRS applicable entites can have the sub list for CRS 
			RegDocumentList *pRegDocumentList = dynamic_cast<RegDocumentList*>(getParent());
			getWorkSession().getOption(ifds::CRSEntityList, dstrCRSEntityList, idDataGroup, false); 
			
			DString dstrCurrentEntityId, dstrEntityId = NULL_STRING; 
			getParent()->getField(ifds::EntityId, dstrCurrentEntityId, idDataGroup);
			Entity *pEntity = NULL;
			if((getWorkSession().getEntity(idDataGroup, dstrCurrentEntityId, pEntity) <= WARNING) && pEntity)
			{
				/* Add documents to new entity */
				if(pEntity->isNew())
				{
					AccountEntityXref *pAccountEntityXref = NULL;
					if((getWorkSession().getAccountEntityXref(idDataGroup, pAccountEntityXref) <= WARNING) 
						&& pAccountEntityXref)
					{
						DString dstrEntityId = NULL_STRING;						
						for(BFObjIter iter(*pAccountEntityXref, idDataGroup); !iter.end(); ++iter)
						{
							iter.getObject()->getField(ifds::EntityId, dstrEntityId, idDataGroup);
							if(dstrCurrentEntityId == dstrEntityId)
							{
								iter.getObject()->getField(ifds::EntityType, dstrEntityType, idDataGroup);
								break;
							}
						}	  
					}
				}
				/* Add document to existing entity */
				else
				{
					if(pRegDocumentList)
					{
						pRegDocumentList->getCurrentEntityDetails(idDataGroup, NULL_STRING, dstrEntityJurisdiction, dstrEntityType);
					}
				}
				if(!isCodeInList(dstrEntityType, dstrCRSEntityList))
				{
					dstrExcludeComplyRule = COMPLY_RULE::CRSComplyRule;
				}
				subset = pRegDocumentTypeList->buildSubsitutionSet(dstrExcludeComplyRule);
				setFieldAllSubstituteValues(ifds::RegDocId, idDataGroup, subset);  
			}
		}
	}
	else if(dstrComplyRule == COMPLY_RULE::AcctRegistration)
	{
		RegDocumentTypeList *pRegDocTypeList = NULL;

		if(getRegDocumentTypeList(idDataGroup, pRegDocTypeList, ARIDS) <= WARNING && pRegDocTypeList)
		{
			setFieldAllSubstituteValues(ifds::RegDocId, idDataGroup, pRegDocTypeList->buildSubsitutionSet());
		}
	}

	return(GETCURRENTHIGHESTSEVERITY());
}

//*******************************************************************************
bool RegDocument::isTaxExempAuthUpdateNeeded(const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("isTaxExempAuthUpdateNeeded"));

	DString dstrRegDocId, dstrTaxExType, dstrRegDocStatus;

	getFieldBeforeImage(ifds::RegDocStatus, dstrRegDocStatus);
	dstrRegDocStatus.stripAll();
	
	if(dstrRegDocStatus != RECEIVED)
		return false;

	getFieldBeforeImage(ifds::RegDocId, dstrRegDocId);
	dstrRegDocId.stripAll();

	RegDocumentTypeList *pRegDocumentTypeList = NULL;
	getRegDocumentTypeList(idDataGroup,  pRegDocumentTypeList); 
	//dynamic_cast<RegDocumentTypeList*>(getObject(I_("RegDocumentTypeList"), idDataGroup));//moving this to a common function getRegDocumentTypeList

	if(pRegDocumentTypeList != NULL) 
	{				
		DString strObjKey;
		pRegDocumentTypeList->buildStrKey(strObjKey, dstrRegDocId);

		BFObjIter iter(*pRegDocumentTypeList, BF::HOST);
		iter.begin(OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, strObjKey);
		
		if(iter.end())
			return false;

		DString dstrTaxExType;
		iter.getObject()->getField(ifds::TaxExType, dstrTaxExType, idDataGroup);
		
		if(dstrTaxExType == I_("W8") || I_("W9"))
			return true;
	}

	return false;
}

//*******************************************************************************
bool RegDocument::isTaxImpactTaxPayerStatus(const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("isTaxExempAuthUpdateNeeded"));

	DString key = I_("RegDocumentTypeList");
	RegDocumentTypeList *pRegDocumentTypeList = NULL;
	//dynamic_cast<RegDocumentTypeList*>(getObject(key, idDataGroup));//moving this to a common function getRegDocumentTypeList
	getRegDocumentTypeList(idDataGroup,  pRegDocumentTypeList); 

	if(pRegDocumentTypeList == NULL) 
	{
		pRegDocumentTypeList = new RegDocumentTypeList(*this);
		pRegDocumentTypeList->init(COMPLY_RULE::TaxCompliant);

		setObject(pRegDocumentTypeList, key);
	}

	if(pRegDocumentTypeList != NULL) 
	{
		DString dstrRegDocId, strObjKey, dstrTaxImpact;
		getField(ifds::RegDocId, dstrRegDocId, idDataGroup, false);
		
		pRegDocumentTypeList->buildStrKey(strObjKey, dstrRegDocId);

		BFObjIter iter(*pRegDocumentTypeList, idDataGroup);

		iter.positionByKey(strObjKey);

		if(!iter.end())
		{
			iter.getObject()->getField(ifds::TaxImpact, dstrTaxImpact, idDataGroup, false);
			return dstrTaxImpact == I_("04");
		}
	}

	return false;
}
//************************************************************************************
SEVERITY RegDocument::doValidateAll(const BFDataGroupId &idDataGroup, long lValidateGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"));
	DString dstrAccountNum;
	getParent()->getField(ifds::AccountNum, dstrAccountNum, idDataGroup);
	dstrAccountNum.strip().stripLeading('0');

	DString dstrEntityID, dstrRegDocStatus, dstrRegDocId, dstrEffectiveDate, dstrExpireDate, dstrJurisdiction;

	MFAccount *pMFAccount = NULL;
	if (getWorkSession().getMFAccount(idDataGroup, dstrAccountNum,pMFAccount) <= WARNING && pMFAccount)
	{	
		if (!isNew() && isUpdatedForDataGroup(idDataGroup))
		{
			bool bDisplyWarnSICAV, bDisplyWarnOEIC;

			pMFAccount->displayEnvXrefWarningOnUpdate(idDataGroup, bDisplyWarnSICAV, bDisplyWarnOEIC);
			if(bDisplyWarnSICAV)
				ADDCONDITIONFROMFILE(CND::WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_SICAV);
			if(bDisplyWarnOEIC)
				ADDCONDITIONFROMFILE(CND::WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_OEIC);
		}

		getField(ifds::RegDocStatus, dstrRegDocStatus, idDataGroup);
		getField(ifds::RegDocId, dstrRegDocId, idDataGroup);

		if (dstrRegDocStatus == I_("V") && dstrRegDocId == I_("SCCRS")) 
		{
			// When Self Cert CRS is added for any account with status Outstanding over 90 days  
			getParent()->getField(ifds::EntityId, dstrEntityID, idDataGroup);
			getField(ifds::EffectiveDate, dstrEffectiveDate,idDataGroup);
			getField(ifds::ExpireDate, dstrExpireDate, idDataGroup);
			getField(ifds::RegDocJurisdiction, dstrJurisdiction, idDataGroup);

			EntityRegJurisDetailsList *pEntityRegJurisDetailsList = NULL;		

			if (pMFAccount->getEntityRegJurisDetailsList(pEntityRegJurisDetailsList, dstrEntityID, idDataGroup) <= WARNING && pEntityRegJurisDetailsList)
			{	
				DString entRegJurStartDate1, entRegJurStopDate1, entRegJurEntityId1, entRegJurRegulation1, entRegJurTaxJuris1, entRegJurTaxPayerStat;

				BFObjIter iter1(*pEntityRegJurisDetailsList, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);

				iter1.begin();

				while(!iter1.end())
				{					
					iter1.getObject()->getField(ifds::TaxPayerStartDate, entRegJurStartDate1, idDataGroup);
					iter1.getObject()->getField(ifds::TaxPayerStopDate, entRegJurStopDate1, idDataGroup);
					iter1.getObject()->getField(ifds::EntityId, entRegJurEntityId1, idDataGroup);
					iter1.getObject()->getField(ifds::FATCACode, entRegJurRegulation1, idDataGroup);
					iter1.getObject()->getField(ifds::TaxJuris, entRegJurTaxJuris1, idDataGroup);
					iter1.getObject()->getField(ifds::TaxPayerStat, entRegJurTaxPayerStat, idDataGroup);

					if(	entRegJurTaxPayerStat == I_("R") && // Reportable ERJD
						entRegJurRegulation1 == I_("CRS") &&
						entRegJurTaxJuris1 == dstrJurisdiction && 
						(DSTCommonFunctions::dateRangesOverlap(dstrEffectiveDate, dstrExpireDate, entRegJurStartDate1, entRegJurStopDate1)) )
					{
						ADDCONDITIONFROMFILE(CND::ERR_ERJD_EXISTS);
						break;
					}
				}	// while(!iter1.end())
			}			
		}  // When Self Cert CRS is added/updated for any account with status Outstanding over 90 days
	}  	return GETCURRENTHIGHESTSEVERITY();	
}
//************************************************************************************
SEVERITY RegDocument::getRegDocumentTypeList(const BFDataGroupId &idDataGroup, RegDocumentTypeList *&pRegDocumentTypeList, const DString &complyRules)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getRegDocumentTypeList"));

	DString key = I_("RegDocumentTypeList;ComplyRule=") + complyRules;
	DString reqComplyRules;
	pRegDocumentTypeList = dynamic_cast<RegDocumentTypeList*>(getObject(key, idDataGroup));

	if(pRegDocumentTypeList == NULL) 
	{
		pRegDocumentTypeList = new RegDocumentTypeList(*this);
		DString dstrTaxComplianceList;
		//removal of harcoded FA..Now this can be FA,CRS,AAA,BBB,CCC,.....based on environment config
		getWorkSession().getOption(ifds::TaxComplianceList, dstrTaxComplianceList, idDataGroup, false);

		reqComplyRules = complyRules.empty() ? dstrTaxComplianceList:complyRules;

		if(WARNING >= pRegDocumentTypeList->init(reqComplyRules) && pRegDocumentTypeList) 
		{
			setObject(pRegDocumentTypeList, key);  
		}
		else
		{
			delete pRegDocumentTypeList;
			pRegDocumentTypeList = NULL;
		}
	}
	return GETCURRENTHIGHESTSEVERITY();	
}

//*******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RegDocument.cpp-arc  $
// 
//    Rev 1.5   Aug 17 2012 19:21:36   wutipong
// IN3058961 P179630FN01 FATCA - Acct Doc List and Tax Exempt Auth screens issues
// 
//    Rev 1.4   Jul 23 2012 12:32:44   wutipong
// PETP0179630_FN01 FATCA Account Entity Document Tracking
// 
//    Rev 1.3   Aug 28 2008 14:28:36   jankovii
// IN 1388930 - NASU flow does not update document list unless at least one document.
// 
//    Rev 1.2   Aug 01 2008 09:29:02   jankovii
// PET 59888 FN01 AML Enhancement.
 */