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
// ^FILE   : EntityRegDetails.cpp
// ^AUTHOR : 
// ^DATE   : 08 January 2014
//
// ^CLASS    : EntityRegDetails
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "EntityRegDetails.hpp"

#include <bfutil\bfdate.hpp>
#include "AccountEntityXref.hpp"
#include "AccountEntityXrefObject.hpp"
#include "Entity.hpp"
#include "dstcommonfunction.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "FinInstRegDetlList.hpp"
#include "ErrMsgRulesList.hpp"
#include "entityregdetailslist.hpp"
#include "entityregjurisdetailslist.hpp"
#include "FATCAMasterList.hpp"
#include "translationtable.hpp"
#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_err_warn_includes.h>
#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_err_crs100series_for_acctowner.h>
#include <boost\regex.h>

namespace
{
	const I_CHAR * const CLASSNAME				= I_("EntityRegDetails");
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
	const I_CHAR * const CLASSIFICATION         = I_("FFI");
	const I_CHAR * const CLASSIFICATION_REQUIRED_REGULATIONS_LIST   =  I_("SIF");
	const I_CHAR * const ACCOUNT_OWNER			= I_("01");
}

namespace ENTITY_REGULATION
{
  const I_CHAR * const SIF   =     I_("SIF"); 
}

namespace ifds
{
	extern CLASS_IMPORT const BFNumericFieldId AccountNum;
	extern CLASS_IMPORT const BFNumericFieldId EntityId;
	extern CLASS_IMPORT const BFTextFieldId EntRegDetlUUID;	
	extern CLASS_IMPORT const BFTextFieldId EntityName;
	extern CLASS_IMPORT const BFTextFieldId FirstName;
	extern CLASS_IMPORT const BFTextFieldId LastName;
	extern CLASS_IMPORT const BFTextFieldId EntityType;
	extern CLASS_IMPORT const BFTextFieldId FATCACode;
	extern CLASS_IMPORT const BFTextFieldId FFIClass;
	extern CLASS_IMPORT const BFTextFieldId Consent;
	extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
	extern CLASS_IMPORT const BFDateFieldId StopDate;
	extern CLASS_IMPORT const BFDecimalFieldId Version;
	extern CLASS_IMPORT const BFDecimalFieldId EntRegDetlRId;
	extern CLASS_IMPORT const BFDateFieldId ProcessDate;
	extern CLASS_IMPORT const BFTextFieldId UserName;
	extern CLASS_IMPORT const BFDateFieldId ModDate;
	extern CLASS_IMPORT const BFTextFieldId ModUser;
	extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
	extern CLASS_IMPORT const BFTextFieldId Description;
    extern CLASS_IMPORT const BFTextFieldId EffectiveStopDate;
}

namespace CND
{  
	extern const long ERR_FIELD_VAL_REQUIRED_PLS_SELECT;
    extern const long ERR_EFFECTIVEDATE_MUST_BE_EARLIER_STOPDATE;
	CIFast_IFast_ifastcbo_err_crs100series_for_acctowner;
}

namespace IFASTERR
{
	extern CLASS_IMPORT I_CHAR * const START_STOP_DATE_MUST_BE_WITHIN_REGPORTING_FFI;
}


const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
	//  Field DD Id,              State Flags,    Group Flags 
	{ifds::AccountNum,          BFCBO::NONE,    	0 }, 
	{ifds::EntityId,            BFCBO::NONE,    	0 }, 
	{ifds::EntityName,			BFCBO::NONE,	    0 },
	{ifds::FirstName,			BFCBO::NONE,	    0 },
	{ifds::LastName,            BFCBO::NONE,		0 },
	{ifds::EntityType,          BFCBO::NONE,		0 },
	{ifds::FATCACode,           BFCBO::NONE,		0 },
	{ifds::FFIClass,            BFCBO::NONE,		0 },
	{ifds::Consent,             BFCBO::NONE,		0 },
	{ifds::EffectiveDate,       BFCBO::REQUIRED,	0 }, 
	{ifds::StopDate,            BFCBO::NONE,	    0 }, 
	{ifds::Version,             BFCBO::NONE,		0 },
	{ifds::EntRegDetlRId,       BFCBO::NONE,	    0 },
	{ifds::ProcessDate,         BFCBO::NONE,	    0 },
	/*{ifds::UserName,            BFCBO::NONE,	    0 },*/
	{ifds::ModDate,             BFCBO::NONE,	    0 },
	{ifds::ModUser,             BFCBO::NONE,	    0 },
	{ifds::EffectiveStopDate,   BFCBO::IMMEDIATE_VALIDATION, 0},
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//****************************************************************************
EntityRegDetails::EntityRegDetails (BFAbstractCBO &parent) :
MFCanBFCbo (parent)
{
	TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

	registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );

	addCrossEdit(ifds::EffectiveStopDate, ifds::EffectiveDate);
	addCrossEdit(ifds::EffectiveStopDate, ifds::StopDate);
}


//****************************************************************************
EntityRegDetails::~EntityRegDetails()
{
	TRACE_DESTRUCTOR( CLASSNAME );
}


//****************************************************************************
SEVERITY EntityRegDetails::init (const BFData &data)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

	attachDataObject( const_cast<BFData&>(data), false, true );

	commonInit(BF::HOST);

	return GETCURRENTHIGHESTSEVERITY();
}


//****************************************************************************
SEVERITY EntityRegDetails::initNew (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("initNew"));


	return GETCURRENTHIGHESTSEVERITY();
}


//****************************************************************************
SEVERITY EntityRegDetails::commonInit(const BFDataGroupId &idDataGroup)
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

	EntityRegDetailsList *pEntityRegDetailsList = dynamic_cast <EntityRegDetailsList*> ( getParent() );

	pEntityRegDetailsList->getField(ifds::AccountNum, dstrAccountNum, BF::HOST, false);
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

   //  FATCAMasterList *pFATCAMasterList = NULL;

	//if( getWorkSession ().getFATCAMasterList(pFATCAMasterList) <= WARNING &&
	//	pFATCAMasterList )  // get the BF::HOST group
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
	// set require field
	setFieldRequired (ifds::FATCACode, idDataGroup, true);

	if (!isNew())
	{
		// all keys should be readonly for existing.
		setFieldReadOnly(ifds::EntityName, idDataGroup, true);
		setFieldReadOnly(ifds::FATCACode, idDataGroup, true);
	}

   DString dstrClassificationSubList, dstrRegulation; 
   getClassifcationSubstitueValues(idDataGroup, dstrClassificationSubList);
   setFieldAllSubstituteValues(ifds::FFIClass, idDataGroup, dstrClassificationSubList );
   getField( ifds::FATCACode, dstrRegulation, idDataGroup, false);
   setFieldRequired(ifds::FFIClass, idDataGroup, isCodeInList( dstrRegulation ,CLASSIFICATION_REQUIRED_REGULATIONS_LIST));

	return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************
void EntityRegDetails::setDefaultEntityId(DString &dstrEntityId,
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
	
	setFieldNoValidate(ifds::EntityName, dstrEntityId, idDataGroup, false, false, true);

	setFieldReadOnly(ifds::EntityName, idDataGroup, true);
	
}
//****************************************************************************
void EntityRegDetails::doInitWithDefaultValues (const BFDataGroupId& idDataGroup)
{
	DString dstrCurrBusDate, dstrReportFFIType, defaultStopDate;

	getWorkSession().getMgmtCoOptions()->getField(ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);
	setFieldNoValidate(ifds::EffectiveDate, dstrCurrBusDate, idDataGroup, false, false, true);

	getWorkSession().getDateInHostFormat(defaultStopDate, DSTCWorkSession::DATE_TYPE::DAY12319999, idDataGroup);
    setFieldNoValidate(ifds::StopDate, defaultStopDate, idDataGroup, false, false, true);

	commonInit(idDataGroup);

	DString dstrDefaultEntityId;
	// If access from Entity screen, will set the entityid and read-only.
	EntityRegDetailsList *pEntityRegDetailsList = dynamic_cast <EntityRegDetailsList*> ( getParent() );
	pEntityRegDetailsList->getDefaultEntityId(dstrDefaultEntityId, idDataGroup);

	if( (dstrDefaultEntityId != NULL_STRING) && (dstrDefaultEntityId != I_("0")) )
	{
		setFieldNoValidate(ifds::EntityName, dstrDefaultEntityId, idDataGroup, false, false, true);
		setFieldReadOnly(ifds::EntityName, idDataGroup, true);
	}

}


//********************************************************************************************
SEVERITY EntityRegDetails::doValidateField(const BFFieldId& idField,
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
        DString dstrEffectiveDate, dstrStopDate;

        getField(ifds::EffectiveDate, dstrEffectiveDate, idDataGroup);
        getField(ifds::StopDate, dstrStopDate, idDataGroup);

        if (DSTCommonFunctions::CompareDates(dstrStopDate, dstrEffectiveDate) != DSTCommonFunctions::SECOND_EARLIER )
        {
            ADDCONDITIONFROMFILE(CND::ERR_EFFECTIVEDATE_MUST_BE_EARLIER_STOPDATE);
        }
    }
	else if(idField == ifds::FFIClass)
	{
		DString dstrFFIClass, dstrEntityType;

		getField(ifds::FFIClass, dstrFFIClass, idDataGroup);
		getField(ifds::EntityType, dstrEntityType, idDataGroup);

		boost::RegEx rgCRS100s("CRS1[0-9][0-9]");
		
		if(dstrEntityType.compare(ACCOUNT_OWNER) != 0 && (rgCRS100s.Match(DStringA(dstrFFIClass).c_str())))
		{
			CND::CIFast_IFast_ifastcbo_err_crs100series_for_acctowner err_crs100series_for_acctowner; 
			ADDCONDITIONFROMOBJECT( err_crs100series_for_acctowner );
		}
	}

    return GETCURRENTHIGHESTSEVERITY();
}


//********************************************************************************************
SEVERITY EntityRegDetails::doValidateAll(const BFDataGroupId& idDataGroup, long lValidateGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"));



	return GETCURRENTHIGHESTSEVERITY();
}


//****************************************************************************
SEVERITY EntityRegDetails::doApplyRelatedChanges (const BFFieldId &idField, 
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
      DString dstrRegulation, dstrClassificationSubList;
      getClassifcationSubstitueValues(idDataGroup, dstrClassificationSubList);
      setFieldAllSubstituteValues(ifds::FFIClass, idDataGroup, dstrClassificationSubList );
      getField( ifds::FATCACode, dstrRegulation, idDataGroup, false);
      setFieldRequired(ifds::FFIClass, idDataGroup, isCodeInList( dstrRegulation ,CLASSIFICATION_REQUIRED_REGULATIONS_LIST));
	  setValidFlag(ifds::FFIClass, idDataGroup, false);
	  setFieldNoValidate(ifds::EntityType, dstrEntityTypeSet, idDataGroup, false, false, true, true);
	}
   if (idField == ifds::FATCACode)
	{
      DString dstrRegulation, dstrClassificationSubList;
      getClassifcationSubstitueValues(idDataGroup, dstrClassificationSubList);
      setFieldAllSubstituteValues(ifds::FFIClass, idDataGroup, dstrClassificationSubList );
      getField( ifds::FATCACode, dstrRegulation, idDataGroup, false);
      setFieldRequired(ifds::FFIClass, idDataGroup, isCodeInList( dstrRegulation ,CLASSIFICATION_REQUIRED_REGULATIONS_LIST));
   }//if (idField == ifds::FATCACode)
   

	return GETCURRENTHIGHESTSEVERITY();
}


//****************************************************************************
void EntityRegDetails::doReset (const BFDataGroupId &idDataGroup)
{

}


//****************************************************************************
SEVERITY EntityRegDetails::setReportingFFISubstitution(const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("setReportingFFISubstitution"));



	return GETCURRENTHIGHESTSEVERITY();
}


//****************************************************************************
SEVERITY EntityRegDetails::setDefaultReportingFFI(const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("setReportingFFISubstitution"));



	return GETCURRENTHIGHESTSEVERITY();
}
/******************************************************************************
 Input: Fieldid,  groupcode, idataGroup, use viewdesc
 OutPut:None
 Return:None
 Functionality:Triggers a call to 254 view.Based on the return will set sub values
 ******************************************************************************/
void EntityRegDetails::initializeSubstitutionListFromMiscInfo ( const BFFieldId& idField, 
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
/******************************************************************************
 Input: datagroup
 OutPut:Subtitution List based on the catogory returned by the Miac Info
 Return:None
 Functionality:Returns Subtitution List based on the catogory based on the Misc Info
               filtered by the regulation selected
 ******************************************************************************/
void EntityRegDetails::getClassifcationSubstitueValues( const BFDataGroupId& idDataGroup,
                                                        DString& dstrClassificationSubList )
{
   DString dstrRegulation, dstrSubstitutionList, dstrRegualationCat, dstrClassificationCat;
   dstrClassificationSubList = NULL_STRING;
   getField( ifds::FATCACode, dstrRegulation, idDataGroup, false);

   TranslationTable* pTranslationTable = NULL;
   //get the catogory for regulation drop down first.
   if (getMgmtCo ().getTranslationTable (ENT_REGULATION, pTranslationTable) <= WARNING && pTranslationTable)
   {
    pTranslationTable->getCategory( dstrRegulation, dstrRegualationCat); 
    pTranslationTable = NULL;
   }  
   //get the catogory for regulation classification
   if (getMgmtCo ().getTranslationTable (CLASSIFICATION, pTranslationTable) <= WARNING && pTranslationTable)
   {
      pTranslationTable->getSubstitutionList (dstrSubstitutionList);
      if (!dstrSubstitutionList.empty())
      {
         I_CHAR *temp = const_cast<I_CHAR*> (dstrSubstitutionList.c_str ());
         do
         {
            DString dstrCode, dstrDescr;
            temp = parseIdiString (temp, dstrCode, dstrDescr); 
            pTranslationTable->getCategory( dstrCode, dstrClassificationCat);           
            
            if( dstrRegualationCat == dstrClassificationCat )  
            {
               dstrClassificationSubList += dstrCode + I_("=") + dstrDescr + I_(";");    
            }
         }while (temp && temp != NULL_STRING && *temp);
      }
   }
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/EntityRegDetails.cpp-arc  $
 *
 */