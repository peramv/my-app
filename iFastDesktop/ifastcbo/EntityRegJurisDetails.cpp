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
//    Copyright 1999 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : EntityRegJurisDetails.cpp
// ^AUTHOR : 
// ^DATE   : 19 January 2014
//
// ^CLASS    : EntityRegJurisDetails
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "EntityRegJurisDetails.hpp"
#include "EntityRegJurisDetailsList.hpp"
#include "Entity.hpp"
#include <bfutil\bfdate.hpp>
#include "dstcommonfunction.hpp"
#include "mfaccount.hpp"
#include "accountentityxref.hpp"
#include "accountentityxrefobject.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "FinInstRegDetlList.hpp"
#include "ErrMsgRulesList.hpp"
#include "FATCAMasterList.hpp"
#include "translationtable.hpp"

namespace
{
	const I_CHAR * const CLASSNAME				= I_("EntityRegJurisDetails");
	const I_CHAR * const YES					= I_("Y"); 
	const I_CHAR * const NO						= I_("N");
	const I_CHAR * const FATCA					= I_("FA");
	const I_CHAR * const SINGLE_REPORT_FFI		= I_("02");
	const I_CHAR * const MULTIPLE_REPORT_FFI	= I_("03");
	const I_CHAR * const INDIVIDUAL_ACCOUNT		= I_("0,1,2");
	const I_CHAR * const REJERR_ERROR			= I_("E");
	const I_CHAR * const REJERR_WARNING			= I_("W");
	const I_CHAR * const REJERR_IGNORE			= I_("I");
	const I_CHAR * const TAG_FFI_STARTDATE      = I_("STARTDATE");
	const I_CHAR * const TAG_FFI_STOPDATE       = I_("STOPDATE");
	const I_CHAR * const TAG_REC_STARTDATE      = I_("STARTDATE");
	const I_CHAR * const TAG_REC_STOPDATE       = I_("STOPDATE");
   const I_CHAR * const ENT_REGULATION         = I_("ERG");  
}

namespace TAXPAYER_STAT
{
    const I_CHAR * const EXEMPTED               = I_("E");
}

namespace ifds
{
    extern CLASS_IMPORT const BFTextFieldId EntRegJurisDetlUUID;
	extern CLASS_IMPORT const BFNumericFieldId EntityId;
	extern CLASS_IMPORT const BFTextFieldId EntityType;
	extern CLASS_IMPORT const BFTextFieldId EntityName;
	extern CLASS_IMPORT const BFTextFieldId FirstName;
	extern CLASS_IMPORT const BFTextFieldId LastName;
	extern CLASS_IMPORT const BFTextFieldId FATCACode;
	extern CLASS_IMPORT const BFTextFieldId TaxJuris;
	extern CLASS_IMPORT const BFTextFieldId TaxPayerStat;
	extern CLASS_IMPORT const BFTextFieldId AutoResetTaxPayerStat;
	extern CLASS_IMPORT const BFDateFieldId TaxPayerStartDate;
	extern CLASS_IMPORT const BFDateFieldId TaxPayerStopDate;
	extern CLASS_IMPORT const BFDecimalFieldId Version;
	extern CLASS_IMPORT const BFDecimalFieldId EntRegJurisDetlRId;
	extern CLASS_IMPORT const BFDateFieldId ProcessDate;
	extern CLASS_IMPORT const BFTextFieldId Username;
	extern CLASS_IMPORT const BFDateFieldId ModDate;
	extern CLASS_IMPORT const BFTextFieldId ModUser;
	extern CLASS_IMPORT const BFDateFieldId CurrBusDate;	
	extern CLASS_IMPORT const BFTextFieldId FATCAConsent;
	extern CLASS_IMPORT const BFNumericFieldId AccountNum;
	extern CLASS_IMPORT const BFTextFieldId Description;
    extern CLASS_IMPORT const BFTextFieldId EffectiveStopDate;
    extern CLASS_IMPORT const BFTextFieldId TPSReason;
	
	extern CLASS_IMPORT const BFTextFieldId NoTINReason;
}

namespace CND
{  
	extern const long ERR_FIELD_VAL_REQUIRED_PLS_SELECT;
    extern const long ERR_EFFECTIVEDATE_MUST_BE_EARLIER_STOPDATE;
    extern const long ERR_TAX_PAYER_STATUS_REASON_IS_MISSING;
    extern const long WARN_TAX_PAYER_STATUS_REASON_IS_MISSING;
	//extern const long ERR_START_STOP_DATE_MUST_BE_WITHIN_REGPORTING_FFI;
	//extern const long WARN_START_STOP_DATE_MUST_BE_WITHIN_REGPORTING_FFI;
}

namespace IFASTERR
{
	extern CLASS_IMPORT I_CHAR * const TAX_PAYER_STATUS_REASON_IS_MISSING;
}


const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
	//  Field DD Id,              State Flags,    Group Flags 
	{ifds::TaxPayerStartDate,       BFCBO::NONE,	0 }, 
	{ifds::EntRegJurisDetlUUID,     BFCBO::NONE,	0 }, 
	{ifds::EntityId,			    BFCBO::NONE,	0 }, 
	{ifds::EntityType,              BFCBO::NONE,	0 },
	{ifds::EntityName,              BFCBO::NONE,	0 },
	{ifds::FirstName,			    BFCBO::NONE,	0 },
	{ifds::LastName,		        BFCBO::NONE,	0 },
	{ifds::FATCACode,		        BFCBO::NONE,	0 },
	{ifds::TaxJuris,			    BFCBO::NONE,	0 },
	{ifds::TaxPayerStat,	        BFCBO::NONE,	0 },
	{ifds::AutoResetTaxPayerStat,	BFCBO::NONE,	0 },
	{ifds::TaxPayerStartDate,		BFCBO::NONE,	0 },
	{ifds::TaxPayerStopDate,		BFCBO::NONE,	0 },
	{ifds::Version,				    BFCBO::NONE,	0 },
	{ifds::EntRegJurisDetlRId,      BFCBO::NONE,    0 },
	{ifds::ProcessDate,             BFCBO::NONE,    0 },
	{ifds::Username,                BFCBO::NONE,    0 },
	{ifds::ModDate,                 BFCBO::NONE,    0 },
	{ifds::ModUser,                 BFCBO::NONE,    0 },
	{ifds::FATCAConsent,            BFCBO::NONE,    0 },
    {ifds::TaxPayerStartDate,       BFCBO::REQUIRED,0 }, 
	{ifds::TaxPayerStopDate,        BFCBO::NONE,    0 }, 
    {ifds::EffectiveStopDate,       BFCBO::IMMEDIATE_VALIDATION, 0},
    {ifds::TPSReason,               BFCBO::NONE,    0 },

	{ifds::NoTINReason,             BFCBO::NONE,    0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//****************************************************************************
EntityRegJurisDetails::EntityRegJurisDetails (BFAbstractCBO &parent) :
MFCanBFCbo (parent)
{
	TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

	registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );

    addCrossEdit(ifds::EffectiveStopDate, ifds::TaxPayerStartDate);
	addCrossEdit(ifds::EffectiveStopDate, ifds::TaxPayerStopDate);
}


//****************************************************************************
EntityRegJurisDetails::~EntityRegJurisDetails()
{
	TRACE_DESTRUCTOR( CLASSNAME );
}


//****************************************************************************
SEVERITY EntityRegJurisDetails::init (const BFData &data)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

	attachDataObject( const_cast<BFData&>(data), false, true );

	commonInit(BF::HOST);

    DString dstrTaxPayerStat;
    getField(ifds::TaxPayerStat, dstrTaxPayerStat, BF::HOST, false);

	DString dstrFATCACode;
	getField(ifds::FATCACode, dstrFATCACode, BF::HOST, false);
	if(dstrFATCACode != I_("CRS"))
	{
		DString dstrCRSTaxPayerStat = removeItemFromSubtList(ifds::TaxPayerStat, I_("U"), BF::HOST);
		setFieldAllSubstituteValues(ifds::TaxPayerStat,  BF::HOST, dstrCRSTaxPayerStat);
	}

	return GETCURRENTHIGHESTSEVERITY();
}


//****************************************************************************
SEVERITY EntityRegJurisDetails::initNew (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("initNew"));
    
	return GETCURRENTHIGHESTSEVERITY();
}


//****************************************************************************
SEVERITY EntityRegJurisDetails::commonInit(const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("commonInit"));

	// init Entity List
	DString dstrAccountNum, dstrEntityId;
	AccountEntityXref *pAccountEntityXref = NULL;
	DString fieldSubSetBgn = I_("0= ;");
    DString fieldSubSet,fieldSubSet1;
	DString dstrSetEntityId = I_("0"); // default to EntityId = 0 or Blank value
	int iNumberOfEntities = 0;
	bool bReadOnly = false;

	EntityRegJurisDetailsList *pEntityRegJurisDetailsList = dynamic_cast <EntityRegJurisDetailsList*>(getParent());

	pEntityRegJurisDetailsList->getField(ifds::AccountNum, dstrAccountNum, BF::HOST, false);
	dstrAccountNum.stripLeading('0');
	
	if (getWorkSession().getAccountEntityXref (idDataGroup, pAccountEntityXref ) <= WARNING &&
		pAccountEntityXref)
	{
		if( pAccountEntityXref->PopulateEntitiesList( idDataGroup, dstrAccountNum ) <= WARNING)
		{
			DString dstrKeyAccount, dstrKeyAccountValue;
		    AccountEntityXref::buildPartialKeyForAccount (dstrKeyAccount, dstrAccountNum);
			AccountEntityXref::getValueForTag (dstrKeyAccount, I_("AccountNum"), dstrKeyAccountValue);

			BFObjIter bfIter (*pAccountEntityXref, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED, false);

			while(!bfIter.end())
			{
				AccountEntityXrefObject* pAccountEntityXrefObject = 
									dynamic_cast<AccountEntityXrefObject*>(bfIter.getObject());
				if(pAccountEntityXrefObject)
				{
					DString dstrKeyTemp = bfIter.getStringKey();
					DString dstrKeyAccountValueTemp;
					AccountEntityXref::getValueForTag (dstrKeyTemp, I_("AccountNum"), dstrKeyAccountValueTemp);					

					if(dstrKeyAccountValue == dstrKeyAccountValueTemp)
					{
					DString dstrFirstName, dstrLastName, dstrEntityId, dstrEntityType;
					pAccountEntityXrefObject->getField(ifds::EntityType, dstrEntityType, idDataGroup, false);
					pAccountEntityXrefObject->getField(ifds::EntityId, dstrEntityId, idDataGroup, false);
					pAccountEntityXrefObject->getField(ifds::FirstName, dstrFirstName, idDataGroup, false);
					pAccountEntityXrefObject->getField(ifds::LastName, dstrLastName, idDataGroup, false);

					if( dstrLastName.strip() != NULL_STRING )
					{
						fieldSubSet1 += dstrEntityId.strip();
						fieldSubSet1 += I_("=");
						fieldSubSet1 += dstrLastName.strip();
						if ( dstrFirstName.strip() != NULL_STRING )
						{
							fieldSubSet1 += I_(", ");
							fieldSubSet1 += dstrFirstName.strip();
						}
						fieldSubSet1 += I_(";");

						}
						iNumberOfEntities++;
						// if there is only one entity id, this will be the one is set. Otherwise, will be default to zero.
						if(iNumberOfEntities == 1)
							dstrSetEntityId = dstrEntityId;
						else
							dstrSetEntityId = I_("0");
					}

				}
				++bfIter;
			}
		}

	}
	if (iNumberOfEntities == 0)
	{
		// in case of caller is AllEntity, so we ignore the Account.
		// There should no AccountEntityXref
		DString dstrFirstName_temp, dstrLastName_temp, dstrEntityId_temp;

		getParent()->getField(ifds::EntityId, dstrEntityId_temp, idDataGroup, false);

		Entity *pEntity = NULL;
		getWorkSession().getEntity( idDataGroup, dstrEntityId_temp, pEntity );
		if(pEntity)
		{
			pEntity->getField(ifds::FirstName, dstrFirstName_temp, idDataGroup, false);
			pEntity->getField(ifds::LastName, dstrLastName_temp, idDataGroup, false);
			
			if( dstrLastName_temp.strip() != NULL_STRING )
			{
				fieldSubSet1 += dstrEntityId_temp.stripLeading('0');
				fieldSubSet1 += I_("=");
				fieldSubSet1 += dstrLastName_temp.stripLeading('0');
				if ( dstrFirstName_temp.strip() != NULL_STRING )
				{
					fieldSubSet1 += I_(", ");
					fieldSubSet1 += dstrFirstName_temp.strip();
				}
				fieldSubSet1 += I_(";");
				bReadOnly = true;

			}
		}
	}
	else if (iNumberOfEntities == 1)
	{
		bReadOnly = true;
	}
    fieldSubSet = fieldSubSetBgn + fieldSubSet1;
	setFieldAllSubstituteValues( ifds::EntityName, idDataGroup, fieldSubSet );

	if(!isNew())
	{
		getField(ifds::EntityId, dstrSetEntityId, idDataGroup, false);
		setFieldNoValidate(ifds::EntityName, dstrSetEntityId, idDataGroup, false, true, true);
	}
	else
	{
		setFieldNoValidate(ifds::EntityName, dstrSetEntityId, idDataGroup, false, false, true);		
	}
	setFieldReadOnly(ifds::EntityName, idDataGroup, bReadOnly);

   //All regulation is based on MisInfo Going forward...
   //So commenting out the below code and using the initializeSubstitutionListFromMiscInfo instead.

	//FATCAMasterList *pFATCAMasterList = NULL;

	//if( getWorkSession ().getFATCAMasterList(pFATCAMasterList) <= WARNING &&
	//	pFATCAMasterList ) // get the BF::HOST group
	//{
	//	DString fatcaSubList;
	//	BFObjIter bfIter (*pFATCAMasterList, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED, false);	

	//	bfIter.begin();
	//	while(!bfIter.end())
	//	{
	//		DString dstrFATCACode, dstrFATCADesc;
	//		bfIter.getObject()->getField(ifds::FATCACode, dstrFATCACode, idDataGroup, false);
	//		bfIter.getObject()->getField(ifds::Description, dstrFATCADesc, idDataGroup, false);

	//		fatcaSubList = fatcaSubList + dstrFATCACode + I_("=") + dstrFATCADesc + I_(";");
	//		++bfIter;
	//	}

	//	setFieldAllSubstituteValues( ifds::FATCACode, idDataGroup, fatcaSubList );

	//}

   initializeSubstitutionListFromMiscInfo( ifds::FATCACode, ENT_REGULATION, idDataGroup, true);
	setFATCACodeRelatedChanges(idDataGroup);

	// set require field
	setFieldRequired (ifds::FATCACode, idDataGroup, true);
	setFieldRequired (ifds::TaxJuris, idDataGroup, true);
	//initConsent(idDataGroup);

	if (!isNew())
	{
		// all keys should be readonly for existing.
		setFieldReadOnly(ifds::EntityName, idDataGroup, true);
		setFieldReadOnly(ifds::FATCACode, idDataGroup, true);
		setFieldReadOnly(ifds::TaxJuris, idDataGroup, true);
	}

    //Blank Option
    DString dstrTPSReasonSet;
    BFProperties *pBFProperties = NULL;

    pBFProperties = getFieldProperties(ifds::TPSReason, idDataGroup);
    pBFProperties->getAllSubstituteValues(dstrTPSReasonSet);

    dstrTPSReasonSet = I_(" = ;") + dstrTPSReasonSet;
    setFieldAllSubstituteValues(ifds::TPSReason, idDataGroup, dstrTPSReasonSet);

	return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************
void EntityRegJurisDetails::setDefaultEntityId(DString &dstrEntityId,
										  const BFDataGroupId &idDataGroup)
{
	
	// in case of caller is Entity and AllEntity, the EntityName list can have only 1 Entity.

	DString dstrFirstName_temp, dstrLastName_temp, fieldSubSet, fieldSubSet1;

	Entity *pEntity = NULL;
	getWorkSession().getEntity( idDataGroup, dstrEntityId, pEntity );
	if(pEntity)
	{
		pEntity->getField(ifds::FirstName, dstrFirstName_temp, idDataGroup, false);
		pEntity->getField(ifds::LastName, dstrLastName_temp, idDataGroup, false);

		if( dstrLastName_temp.strip() != NULL_STRING )
		{
			fieldSubSet1 += dstrEntityId.stripLeading('0');
			fieldSubSet1 += I_("=");
			fieldSubSet1 += dstrLastName_temp.stripLeading('0');
			if ( dstrFirstName_temp.strip() != NULL_STRING )
			{
				fieldSubSet1 += I_(", ");
				fieldSubSet1 += dstrFirstName_temp.strip();
			}
			fieldSubSet1 += I_(";");
		}
	}
    fieldSubSet = fieldSubSet1;
	setFieldAllSubstituteValues( ifds::EntityName, idDataGroup, fieldSubSet );
	
	setFieldNoValidate(ifds::EntityName, dstrEntityId, idDataGroup, false, true, true);

	setFieldReadOnly(ifds::EntityName, idDataGroup, true);
	
}

//****************************************************************************
void EntityRegJurisDetails::doInitWithDefaultValues (const BFDataGroupId& idDataGroup)
{
	DString dstrCurrBusDate, defaultStopDate;

	getWorkSession().getMgmtCoOptions()->getField(ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);
	setFieldNoValidate(ifds::TaxPayerStartDate, dstrCurrBusDate, idDataGroup, false, false, true);

	getWorkSession().getDateInHostFormat(defaultStopDate, DSTCWorkSession::DATE_TYPE::DAY12319999, idDataGroup);
    setFieldNoValidate(ifds::TaxPayerStopDate, defaultStopDate, idDataGroup, false, false, true);
	// Auto Reset set to YES that mean on screen, the checkbox NoSystemReset should be uncheck.
	setFieldNoValidate(ifds::AutoResetTaxPayerStat, YES, idDataGroup, false, false, true);

	commonInit(idDataGroup);

	DString dstrDefaultEntityId;
	// If access from Entity screen, will set the entityid and read-only.
	EntityRegJurisDetailsList *pEntityRegJurisDetailsList = dynamic_cast <EntityRegJurisDetailsList*> ( getParent() );
	pEntityRegJurisDetailsList->getDefaultEntityId(dstrDefaultEntityId, idDataGroup);

	if( (dstrDefaultEntityId != NULL_STRING) && (dstrDefaultEntityId != I_("0")) )
	{
		setFieldNoValidate(ifds::EntityName, dstrDefaultEntityId, idDataGroup, false, false, true);
		setFieldReadOnly(ifds::EntityName, idDataGroup, true);
	}
}


//********************************************************************************************
SEVERITY EntityRegJurisDetails::doValidateField(const BFFieldId& idField,
										 const DString& strValue,
										 const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField"));

	if(idField == ifds::EntityName)
	{
		DString dstrEntityName;
		dstrEntityName = strValue;

		if( dstrEntityName.stripLeading('0') == NULL_STRING )
		{
			 
			ADDCONDITIONFROMFILE( CND::ERR_FIELD_VAL_REQUIRED_PLS_SELECT );
		}
	}
    else if (idField == ifds::EffectiveStopDate)
    {
        DString dstrTaxPayerStartDate, dstrTaxPayerStoptDate;

        getField(ifds::TaxPayerStartDate, dstrTaxPayerStartDate, idDataGroup);
        getField(ifds::TaxPayerStopDate, dstrTaxPayerStoptDate, idDataGroup);

        if (DSTCommonFunctions::CompareDates(dstrTaxPayerStoptDate, dstrTaxPayerStartDate) != DSTCommonFunctions::SECOND_EARLIER )
        {
            ADDCONDITIONFROMFILE(CND::ERR_EFFECTIVEDATE_MUST_BE_EARLIER_STOPDATE);
        }
    }
    else if (idField == ifds::TPSReason)
    {
        DString dstrTaxPayerStat, dstrTPSReason;

        getField(ifds::TaxPayerStat, dstrTaxPayerStat, idDataGroup);
        getField(ifds::TPSReason, dstrTPSReason, idDataGroup);

        if (dstrTaxPayerStat == TAXPAYER_STAT::EXEMPTED && dstrTPSReason.empty())
        {
            getErrMsg(IFASTERR::TAX_PAYER_STATUS_REASON_IS_MISSING, 
                      CND::ERR_TAX_PAYER_STATUS_REASON_IS_MISSING, 
                      CND::WARN_TAX_PAYER_STATUS_REASON_IS_MISSING,
                      idDataGroup);
        }
    }

	return GETCURRENTHIGHESTSEVERITY();
}


//********************************************************************************************
SEVERITY EntityRegJurisDetails::doValidateAll(const BFDataGroupId& idDataGroup, long lValidateGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"));

	return GETCURRENTHIGHESTSEVERITY();
}


//****************************************************************************
SEVERITY EntityRegJurisDetails::doApplyRelatedChanges (const BFFieldId &idField, 
												const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));

	if (idField == ifds::EntityName)
	{
		DString dstrEntityId, dstrAccountNum, dstrEntityTypeSet(I_(""));
		getField(ifds::EntityName, dstrEntityId, idDataGroup, false);
		setFieldNoValidate(ifds::EntityId, dstrEntityId, idDataGroup, false, false, true);

		AccountEntityXref *pAccountEntityXref  = NULL;
		getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);

		if (getWorkSession().getAccountEntityXref (idDataGroup, pAccountEntityXref ) <= WARNING &&
			pAccountEntityXref)
		{
			if( pAccountEntityXref->PopulateEntitiesList( idDataGroup, dstrAccountNum ) <= WARNING)
			{
				BFObjIter bfIter (*pAccountEntityXref, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED, false);
				bfIter.begin();

				while(!bfIter.end())
				{
					AccountEntityXrefObject* pAccountEntityXrefObject = 
												dynamic_cast<AccountEntityXrefObject*>(bfIter.getObject());
					if(pAccountEntityXrefObject)
					{
						DString dstrEntityId_temp, dstrEntityType_temp;
						pAccountEntityXrefObject->getField(ifds::EntityType, dstrEntityType_temp, idDataGroup, false);
						pAccountEntityXrefObject->getField(ifds::EntityId, dstrEntityId_temp, idDataGroup, false);
						
						if (dstrEntityId_temp == dstrEntityId)
						{
							dstrEntityTypeSet = dstrEntityType_temp;
							break;
						}						

					}
					++bfIter;
				}
			}
		}

		setFieldNoValidate(ifds::EntityType, dstrEntityTypeSet, idDataGroup, false, false, true, true);
	}
	else if (idField == ifds::FATCACode)
	{
		setFATCACodeRelatedChanges(idDataGroup);
	}
    else if (idField == ifds::TaxPayerStat)
    {
        setFieldNoValidate(ifds::TPSReason, NULL_STRING, idDataGroup, false, false, true, true);
        setFieldValid(ifds::TPSReason, idDataGroup, false);
    }

	return GETCURRENTHIGHESTSEVERITY();
}


//****************************************************************************
void EntityRegJurisDetails::doReset (const BFDataGroupId &idDataGroup)
{

}


//****************************************************************************
void EntityRegJurisDetails::setFATCACodeRelatedChanges(const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("setReportingFFISubstitution"));

	DString dstrFATCACode;
	getField(ifds::FATCACode, dstrFATCACode, idDataGroup, false);

	if( dstrFATCACode != I_("USFATCA") )
	{
		setFieldNoValidate(ifds::FATCAConsent, I_(" "), idDataGroup, false, true, true);
		setFieldReadOnly(ifds::FATCAConsent, idDataGroup, true);
	}
	else
	{
		setFieldReadOnly(ifds::FATCAConsent, idDataGroup, false);
		//initConsent(idDataGroup);
	}

	if(dstrFATCACode == I_("CRS"))
	{
		DString dstrTaxPayerStat;
		BFProperties *pProperties = getFieldProperties (ifds::TaxPayerStat, BF::HOST);

		pProperties->getAllSubstituteValues (dstrTaxPayerStat);

		setFieldAllSubstituteValues (ifds::TaxPayerStat, idDataGroup, dstrTaxPayerStat);
	}
	else
	{		
		DString dstrCRSTaxPayerStat = removeItemFromSubtList(ifds::TaxPayerStat, I_("U"), idDataGroup);
		setFieldAllSubstituteValues(ifds::TaxPayerStat, idDataGroup, dstrCRSTaxPayerStat);
	}

}
/******************************************************************************
 Input: Fieldid,  groupcode, idataGroup, use viewdesc
 OutPut:None
 Return:None
 Functionality:Triggers a call to 254 view.Based on the return will set sub values
 ******************************************************************************/
void EntityRegJurisDetails::initializeSubstitutionListFromMiscInfo ( const BFFieldId& idField, 
                                                                     const DString &dstrGroupCode, 
                                                                     const BFDataGroupId& idDataGroup, 
                                                                     const bool bUseViewDesc /*=false*/ )
{
  TranslationTable* pTranslationTable = NULL;
  DString dstrSubstitutionList;
  if (getMgmtCo ().getTranslationTable (dstrGroupCode, pTranslationTable) <= WARNING && pTranslationTable)
  {
      pTranslationTable->getSubstitutionList (dstrSubstitutionList, bUseViewDesc);
      setFieldAllSubstituteValues (idField, idDataGroup, dstrSubstitutionList);    
  }
}


//****************************************************************************
//void EntityRegJurisDetails::initConsent(const BFDataGroupId &idDataGroup)
//{
//	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("initFATCAConsent"));
//
//	// add Blank on the fly for FATCAConsent.
//	DString dstrFATCAConsentSet;
//	BFProperties *pBFProperties = getFieldProperties (ifds::FATCAConsent, idDataGroup );
//	pBFProperties->getAllSubstituteValues( dstrFATCAConsentSet );
//	/******************* we need to send blank not space to the host.  *******/
//	// need to determine this again...**********
//	dstrFATCAConsentSet = I_(" = ;Y=Yes;N=No;") ;
//    setFieldAllSubstituteValues( ifds::FATCAConsent, idDataGroup, dstrFATCAConsentSet );   
//	//pBFProperties->setAllSubstituteValues (dstrFATCAConsentSet);
//
//	if(isNew())
//	{
//		setFieldNoValidate(ifds::FATCAConsent, I_(" "), idDataGroup, false, false, true);
//	}
//	else
//	{
//		DString dstrFATCAConsent;
//		getField(ifds::FATCAConsent, dstrFATCAConsent, idDataGroup, false);
//		if(dstrFATCAConsent.strip() == NULL_STRING)
//		{
//			setFieldNoValidate(ifds::FATCAConsent, I_(" "), idDataGroup, false, false, true);
//		}
//	}
//
//}

//****************************************************************************
//void EntityRegJurisDetails::setConsentForHOST(const BFDataGroupId &idDataGroup)
//{
//	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("setFATCAConsentForHOST"));
//
//	DString dstrFATCAConsent;
//	getField(ifds::FATCAConsent, dstrFATCAConsent, idDataGroup, false);
//
//	setFieldNoValidate(ifds::FATCAConsent, dstrFATCAConsent.strip(), idDataGroup, false, true, true, false);
//
//}