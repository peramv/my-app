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
//    Copyright 2000 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : EntityRegDetailsProcess.cpp
// ^AUTHOR : 
// ^DATE   : 08 January 2014
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : EntityRegDetailsProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "EntityRegDetailsProcess.hpp"
#include "EntityRegDetailsProcessIncludes.h"
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\MFAccount.hpp>
#include <ifastcbo\AccountEntityXref.hpp>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastcbo\DSTCWorkSession.hpp>
#include <ifastcbo\Entity.hpp>
#include <ifastcbo\EntityRegDetailsList.hpp>
#include <ifastcbo\EntityRegDetails.hpp>
#include <ifastcbo\EntityRegJurisDetailsList.hpp>
#include <ifastcbo\EntityRegJurisDetails.hpp>
#include <ifastcbo\WhereUsedList.hpp>
#include <ifastbp\ifasthistoricalparameters.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_ENT_REG_MAINT;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ENT_REG_MAINT;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator<EntityRegDetailsProcess> processCreator(CMD_BPROC_ENT_REG_MAINT);

namespace 
{
	const I_CHAR * const CLASSNAME = I_( "EntityRegDetailsProcess" );
	const I_CHAR * const ACCOUNT_NUMBER   = I_( "AccountNum" );
	const I_CHAR * const Y = I_("Y");
	const I_CHAR * const N = I_("N");
	const I_CHAR * const FATCA = I_("FA");
}

namespace CND
{
	extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace UAF
{
	//extern CLASS_IMPORT I_CHAR * const ACCT_REGIS_MAINT;
}

namespace AUDITTYPE
{
	extern CLASS_IMPORT I_CHAR * const ENTREGDETAILS;
	extern CLASS_IMPORT I_CHAR * const ENTREGJURISDETAILS;
}

namespace ifds
{   
	extern CLASS_IMPORT const BFTextFieldId EntityName;
	extern CLASS_IMPORT const BFTextFieldId FirstName;
	extern CLASS_IMPORT const BFTextFieldId LastName;
	extern CLASS_IMPORT const BFTextFieldId FATCACode;
	extern CLASS_IMPORT const BFTextFieldId FFIClass;
	extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
	extern CLASS_IMPORT const BFDateFieldId StopDate;
	extern CLASS_IMPORT const BFTextFieldId FATCAConsent;
	extern CLASS_IMPORT const BFTextFieldId TaxJuris;
	extern CLASS_IMPORT const BFTextFieldId TaxPayerStat;
	extern CLASS_IMPORT const BFDateFieldId TaxPayerStartDate;
	extern CLASS_IMPORT const BFDateFieldId TaxPayerStopDate;
	extern CLASS_IMPORT const BFNumericFieldId AccountNum;
	extern CLASS_IMPORT const BFNumericFieldId ShrNum;
	extern CLASS_IMPORT const BFNumericFieldId EntityId;
	extern CLASS_IMPORT const BFTextFieldId AutoResetTaxPayerStat;
	extern CLASS_IMPORT const BFDecimalFieldId EntRegDetlRId;
	extern CLASS_IMPORT const BFDecimalFieldId EntRegJurisDetlRId;
	extern CLASS_IMPORT const BFTextFieldId Username;
	extern CLASS_IMPORT const BFDateFieldId ProcessDate;
	extern CLASS_IMPORT const BFTextFieldId ModUser;
	extern CLASS_IMPORT const BFDateFieldId ModDate;
	extern CLASS_IMPORT const BFTextFieldId EntityType;
    extern CLASS_IMPORT const BFTextFieldId EntRegDetlExist;
    extern CLASS_IMPORT const BFTextFieldId CurrentEntRegAcctNum;
    extern CLASS_IMPORT const BFTextFieldId TPSReason;
	
	extern CLASS_IMPORT const BFTextFieldId NoTINReason;
}


//****************************************************************
EntityRegDetailsProcess::EntityRegDetailsProcess(GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand)
: AbstractProcess(pGIC, pGIParent, rCommand), 
//_pAccountRegDetailsList(NULL),
_rpChildGI(NULL)
{
	TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING );

	addContainer(IFASTBP_PROC::MFACCOUNT_CBO,                   false,BF::NullContainerId, false);
	addContainer(IFASTBP_PROC::ENTITY_LIST,                     false,BF::NullContainerId, false);

    getParent()->getParameter (I_("Caller"), _dstrCaller);

	if(_dstrCaller == I_("COA") || _dstrCaller == I_("NASU"))
	{
		addContainer(IFASTBP_PROC::ENTITY_REG_DETAILS_LIST,         true, IFASTBP_PROC::MFACCOUNT_CBO, true, I_("EntityRegDetailsList"));
		addContainer(IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST  , true, IFASTBP_PROC::MFACCOUNT_CBO, true, I_("EntityRegJurisDetailsList"));
	}
	else if(_dstrCaller == I_("Entity") || _dstrCaller == I_("AllEntity") )
	{
		addContainer(IFASTBP_PROC::ENTITY_REG_DETAILS_LIST,         true, IFASTBP_PROC::ENTITY_LIST, true, I_("EntityRegDetailsList"));
		addContainer(IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST  , true, IFASTBP_PROC::ENTITY_LIST, true, I_("EntityRegJurisDetailsList"));
	}

	addFieldDetails(ifds::EntityName,		    IFASTBP_PROC::ENTITY_REG_DETAILS_LIST);
	addFieldDetails(ifds::EntityType,		    IFASTBP_PROC::ENTITY_REG_DETAILS_LIST, SUBCLASS_PROCESS);
	addFieldDetails(ifds::FATCACode,			IFASTBP_PROC::ENTITY_REG_DETAILS_LIST);
	addFieldDetails(ifds::FFIClass,             IFASTBP_PROC::ENTITY_REG_DETAILS_LIST);
	addFieldDetails(ifds::EffectiveDate,		IFASTBP_PROC::ENTITY_REG_DETAILS_LIST);
	addFieldDetails(ifds::StopDate,		        IFASTBP_PROC::ENTITY_REG_DETAILS_LIST);
	addFieldDetails(ifds::EntRegDetlRId,        IFASTBP_PROC::ENTITY_REG_DETAILS_LIST);
	addFieldDetails(ifds::Username,				IFASTBP_PROC::ENTITY_REG_DETAILS_LIST);
	addFieldDetails(ifds::ProcessDate,			IFASTBP_PROC::ENTITY_REG_DETAILS_LIST);
	addFieldDetails(ifds::ModDate,				IFASTBP_PROC::ENTITY_REG_DETAILS_LIST);
	addFieldDetails(ifds::ModUser,				IFASTBP_PROC::ENTITY_REG_DETAILS_LIST);
	
	addFieldDetails(ifds::EntityName,		    IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST);
	addFieldDetails(ifds::EntityType,		    IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST, SUBCLASS_PROCESS);
	addFieldDetails(ifds::FATCACode,			IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST);
	addFieldDetails(ifds::TaxJuris,			    IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST);
	addFieldDetails(ifds::TaxPayerStat,			IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST);
	addFieldDetails(ifds::TaxPayerStartDate,	IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST);
	addFieldDetails(ifds::TaxPayerStopDate,		IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST);
	addFieldDetails(ifds::AutoResetTaxPayerStat,IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST);
	addFieldDetails(ifds::FATCAConsent,	        IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST);
	addFieldDetails(ifds::EntRegJurisDetlRId,	IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST);
	addFieldDetails(ifds::Username,				IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST);
	addFieldDetails(ifds::ProcessDate,			IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST);
	addFieldDetails(ifds::ModDate,				IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST);
	addFieldDetails(ifds::ModUser,				IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST);
    addFieldDetails(ifds::TPSReason,      IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST);

	addFieldDetails(ifds::NoTINReason,			IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST);

	//addFieldDetails(ifds::Regulatory,			IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST);
	//addFieldDetails(ifds::DefaultReportingFFI,	IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST);
	//addFieldDetails(ifds::AcctRegDetailRid,   	IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST);

	addFieldDetails( ifds::ShrNum,				IFASTBP_PROC::MFACCOUNT_CBO);
	addFieldDetails( ifds::AccountNum,			IFASTBP_PROC::MFACCOUNT_CBO);
    addFieldDetails( ifds::EntRegDetlExist,     IFASTBP_PROC::MFACCOUNT_CBO);
	addFieldDetails( EntityCaption,             BF::NullContainerId,            SUBCLASS_PROCESS);
	addFieldDetails( ShrCaption,                BF::NullContainerId,            SUBCLASS_PROCESS);
	addFieldDetails( AccountCaption,            BF::NullContainerId,            SUBCLASS_PROCESS);
	addFieldDetails( DefaultRadioBox,             BF::NullContainerId,            SUBCLASS_PROCESS);
	
}


//****************************************************************
EntityRegDetailsProcess::~EntityRegDetailsProcess()
{
	TRACE_DESTRUCTOR(CLASSNAME)
}


//****************************************************************
SEVERITY EntityRegDetailsProcess::doInit()
{
	MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
	SEVERITY sevRtn = SEVERE_ERROR;

	try
	{
		getParameter(ACCOUNT_NUMBER, _dstrAccountNum);
		getParameter(I_("EntityId"), _dstrEntityId);
		getParameter(I_("Caller"), _dstrCaller);

	}
	catch( ConditionException &ce )
	{
		SETCONDITIONFROMEXCEPTION( ce );
	}
	catch( ... )
	{
		throw EXCEPTIONFROMFILE( CND::BP_ERR_UNKNOWN_EXCEPTION );
	}
	return(GETCURRENTHIGHESTSEVERITY());
}


//****************************************************************
E_COMMANDRETURN EntityRegDetailsProcess::doProcess()
{  
	MAKEFRAME2(CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS);
	E_COMMANDRETURN rtn = CMD_FAILURE;

	try
	{
		if( isXMLAPIContext() )
		{
			rtn = CMD_MODELESS_INPROCESS;
		}
		else
		{
			getParent()->setParameter(ACCOUNT_NUMBER, _dstrAccountNum);
			rtn = invokeCommand(this, CMD_GUI_ENT_REG_MAINT, getProcessType(), isModal(), &_rpChildGI);
		}
	}
	catch( ConditionException &ce )
	{
		SETCONDITIONFROMEXCEPTION( ce );
	}
	catch( ... )
	{
		throw EXCEPTIONFROMFILE( CND::BP_ERR_UNKNOWN_EXCEPTION );
	}

	return(rtn);
}


//****************************************************************
bool EntityRegDetailsProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
	MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
	SEVERITY sevRtn = SEVERE_ERROR;

	bool bRtn = false;
	try
	{
		assert(_rpChildGI && isValidModelessInterface(_rpChildGI));

		if (isValidModelessInterface(_rpChildGI))
		{  
			setContainer(IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST, NULL);
			setContainer(IFASTBP_PROC::ENTITY_REG_DETAILS_LIST, NULL);
			setContainer(IFASTBP_PROC::MFACCOUNT_CBO, NULL);

			bRtn = _rpChildGI->refresh(this, NULL);
			bRtn = _rpChildGI->modelessSetFocus(rpGICaller);
		}

	}
	catch( ConditionException &ce )
	{
		SETCONDITIONFROMEXCEPTION( ce );
	}
	catch( ... )
	{
		assert( 0 );
		THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS,
			CND::BP_ERR_UNKNOWN_EXCEPTION );
	}

	return(bRtn);
}


//****************************************************************
bool EntityRegDetailsProcess::doModelessChildComplete( const Command &cmd )
{
	return( cmd.getKey() == CMD_GUI_ENT_REG_MAINT );
}


//****************************************************************
bool EntityRegDetailsProcess::doRefresh( GenericInterface *rpGICaller, const I_CHAR *szOriginalCommand )
{
	TRACE_METHOD(CLASSNAME, DOREFRESH);
	setParameter(ACCOUNT_NUMBER, _dstrAccountNum );	

	return(_rpChildGI->refresh( this, NULL ));
}


//****************************************************************
void EntityRegDetailsProcess::doPostOk( GenericInterface *rpGICaller, bool bSuccessFlag )
{
	setParameter(ACCOUNT_NUMBER, _dstrAccountNum);	
}


////****************************************************************
bool EntityRegDetailsProcess::doOk(GenericInterface *rpGICaller)
{
   SEVERITY sevReturn = NO_CONDITION;
   EntityRegDetailsList *pEntityRegDetailsList = NULL;
   EntityRegJurisDetailsList *pEntityRegJurisDetailsList = NULL;

   DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   MFAccount *pMFAccount = NULL;
   const BFDataGroupId& idDataGroup = getDataGroupId();

   // Anything under account, need to refresh.
   if(_dstrCaller == I_("COA") || _dstrCaller == I_("Entity"))
   {
	   pEntityRegDetailsList = dynamic_cast<EntityRegDetailsList*>(getCBOList(IFASTBP_PROC::ENTITY_REG_DETAILS_LIST, idDataGroup));
	   pEntityRegJurisDetailsList = dynamic_cast<EntityRegJurisDetailsList*>(getCBOList(IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST, idDataGroup));

	   // Loop EntityRegDetailList to find what record updated.
	   BFObjIter iterEntReg( *pEntityRegDetailsList, idDataGroup, false, BFObjIter::ITERTYPE::ALL );
	   iterEntReg.begin();

	   while(!iterEntReg.end())
	   {		   
		   BF_OBJ_ACTIVITY listObjActivity = iterEntReg.getKey().getActivity();

		   EntityRegDetails *pEntityRegDetails = NULL;
		   pEntityRegDetails = dynamic_cast<EntityRegDetails*>(iterEntReg.getObject());

		   // Add/Modify/Delete the MFAccount need to be refreshed to display option box.
		   if( (pEntityRegDetails->isUpdatedForDataGroup(idDataGroup) ) ||
			   (listObjActivity == BFObjIter::ITERTYPE::DELETED))
		   {
			   DString dstrEntityId = NULL_STRING;
			   // EntityName is actually EntityId, format is EntityId=EntityName; for Substitution set
			   pEntityRegDetails->getField(ifds::EntityName, dstrEntityId, idDataGroup, false);
			   dstrEntityId.stripLeading('0');

			   // getWhereUseList of Entity to see each account.
			   WhereUsedList *pWhereUsedList = NULL;
			   if (dstrEntityId != NULL_STRING)
			   {
				   if( dstcWorkSession->getWhereUsedList(pWhereUsedList, idDataGroup, true, dstrEntityId ) <= WARNING)
			   {
				   BFObjIter iterWhereUsed(*pWhereUsedList, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED);
				   iterWhereUsed.begin();

				   while (!iterWhereUsed.end())
				   {
					   DString dstrAccountNum;
					   iterWhereUsed.getObject()->getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);
					   MFAccount *pMFAccountTemp = NULL;
					   if (dstcWorkSession->getMFAccount(getDataGroupId(), dstrAccountNum, pMFAccountTemp) <= WARNING && pMFAccountTemp)
					   {
						   pMFAccountTemp->refreshMe(true);
					   }
					   ++iterWhereUsed;

				   }
			   }
		   }
		   }
		   
		   ++iterEntReg;
	   }

	   // Loop EntityRegJurisDetailList to find what record updated. 
	   // Logic should be same as above for EntityRegDetails
	   BFObjIter iterEntRegJuris( *pEntityRegJurisDetailsList, idDataGroup, false, BFObjIter::ITERTYPE::ALL );
	   iterEntRegJuris.begin();
	   while(!iterEntRegJuris.end())
	   {		   
		   BF_OBJ_ACTIVITY listObjActivity = iterEntRegJuris.getKey().getActivity();

		   EntityRegJurisDetails *pEntityRegJurisDetails = NULL;
		   pEntityRegJurisDetails = dynamic_cast<EntityRegJurisDetails*>(iterEntRegJuris.getObject());

		   // Add/Modify/Delete the MFAccount need to be refreshed to display option box.
		   if( (pEntityRegJurisDetails->isUpdatedForDataGroup(idDataGroup) ) ||
			   (listObjActivity == BFObjIter::ITERTYPE::DELETED))
		   {
			   DString dstrEntityId = NULL_STRING;
			   // EntityName is actually EntityId, format is EntityId=EntityName; for Substitution set
			   pEntityRegJurisDetails->getField(ifds::EntityName, dstrEntityId, idDataGroup, false);
			   dstrEntityId.stripLeading('0');
			  
			   // getWhereUseList of Entity to see each account.
			   WhereUsedList *pWhereUsedList = NULL;

			   if(dstrEntityId != NULL_STRING)
			   {
				   if( dstcWorkSession->getWhereUsedList(pWhereUsedList, idDataGroup, true, dstrEntityId ) <= WARNING)
			   {
				   BFObjIter iterWhereUsed(*pWhereUsedList, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED);
				   iterWhereUsed.begin();

				   while (!iterWhereUsed.end())
				   {
					   DString dstrAccountNum;
					   iterWhereUsed.getObject()->getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);
					   MFAccount *pMFAccountTemp = NULL;
					   if (dstcWorkSession->getMFAccount(getDataGroupId(), dstrAccountNum, pMFAccountTemp) <= WARNING && pMFAccountTemp)
					   {
						   pMFAccountTemp->refreshMe(true);
					   }
					   ++iterWhereUsed;

				   }
			   }
		   }
		   }
		   ++iterEntRegJuris;
	   }
   }

   return (sevReturn == NO_CONDITION);
}

//****************************************************************
void EntityRegDetailsProcess::doGetField( const GenericInterface *rpGICaller,
										   const BFContainerId& idContainer,
										   const BFFieldId& idField,
										   const BFDataGroupId& idDataGroup,
										   DString &strValueOut,
										   bool bFormatted
										   ) const
{
	if(IFASTBP_PROC::ENTITY_REG_DETAILS_LIST == idContainer)
	{	
		EntityRegDetailsProcess* pThis = const_cast<EntityRegDetailsProcess*>(this);
		if (idField == ifds::EntityType)
		{
			EntityRegDetails *pEntityRegDetails = NULL;

			pEntityRegDetails = dynamic_cast<EntityRegDetails*> (pThis->getCBOItem(IFASTBP_PROC::ENTITY_REG_DETAILS_LIST, idDataGroup));

			if (pEntityRegDetails)
			{
				pEntityRegDetails->getField(idField, strValueOut, idDataGroup, bFormatted);
	
			}

		}
	}

	else if(IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST == idContainer)
	{
		EntityRegDetailsProcess* pThis = const_cast<EntityRegDetailsProcess*>(this);
		if (idField == ifds::EntityType)
		{
			EntityRegJurisDetails *pEntityRegJurisDetails = NULL;

			pEntityRegJurisDetails = dynamic_cast<EntityRegJurisDetails*> (pThis->getCBOItem(IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST, idDataGroup));

			if (pEntityRegJurisDetails)
			{
				pEntityRegJurisDetails->getField(idField, strValueOut, idDataGroup, bFormatted);
	
			}

		}	
	}
	else if(BF::NullContainerId == idContainer)
	{
		EntityRegDetailsProcess* pThis = const_cast<EntityRegDetailsProcess*>(this);
		if(idField == ShrCaption || 
		   idField == AccountCaption ||
		   idField == EntityCaption )
		{
			if(_dstrCaller == I_("AllEntity"))
			{
				strValueOut = NULL_STRING;
				return;
			}
			
			DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
			MFAccount *pMFAccount = NULL;
			// it should always have MFAccount here
			dstcWorkSession->getMFAccount(getDataGroupId(), _dstrAccountNum, pMFAccount);
			
			if (idField == ShrCaption)
			{
				if(pMFAccount)
					pMFAccount->getField(ifds::ShrNum, strValueOut, idDataGroup, false);				
			}
			else if (idField == AccountCaption)
			{
				strValueOut = _dstrAccountNum;
			}
			else if (idField == EntityCaption)
				{
				DString dstrAccountNum;
				
				if(pMFAccount)
					pMFAccount->getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);

				dstcWorkSession->getFirstSequenced01AccountholderEntityName(getDataGroupId(), dstrAccountNum, strValueOut);
			}
		}
		else if(idField == DefaultRadioBox)
		{
			if(_dstrCaller == I_("COA"))
			{
				MFAccount *pMFAccount = NULL;
				pMFAccount = dynamic_cast<MFAccount*>(pThis->getCBOItem(IFASTBP_PROC::MFACCOUNT_CBO, idDataGroup));

				if(pMFAccount)
				{
					pMFAccount->getField(ifds::EntRegDetlExist, strValueOut, idDataGroup, false);
				}
			}
			else if(_dstrCaller == I_("Entity") || _dstrCaller == I_("AllEntity"))
			{
				int iRegDetl = 0, iRegDetlJuris = 0;

				Entity *pEntity = NULL;
				EntityRegDetailsList *pEntityRegDetailsList = NULL;
				EntityRegJurisDetailsList *pEntityRegJurisDetailsList = NULL;

				pEntity = dynamic_cast<Entity*>(pThis->getCBOItem(IFASTBP_PROC::ENTITY_LIST, idDataGroup));

				if(pEntity)
				{
					strValueOut = I_("0");

					if( pEntity->getEntityRegDetailsList(pEntityRegDetailsList, idDataGroup) <= WARNING &&
						pEntityRegDetailsList )
					{
						BFObjIter iter( *pEntityRegDetailsList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
						
						iRegDetl = iter.getNumberOfItemsInList();
						if( (iter.getNumberOfItemsInList() > 0) && (!iter.isDummy()) )
						{
							strValueOut = I_("1");
						}
					}
					
					if( strValueOut == I_("0") && pEntity->getEntityRegJurisDetailsList(pEntityRegJurisDetailsList, idDataGroup) <= WARNING &&
						pEntityRegJurisDetailsList )
					{
						BFObjIter iter( *pEntityRegJurisDetailsList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
						
						iRegDetlJuris = iter.getNumberOfItemsInList();
						if( (iter.getNumberOfItemsInList() > 0) && (!iter.isDummy()))
							strValueOut = I_("2");				
					}					

					
				}	

			}
		}
	}


}


//****************************************************************
void *EntityRegDetailsProcess::getPtrForContainer(const BFContainerId& idContainer,
												   const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("getPtrForContainer"));

	void *ptr = NULL;
	SEVERITY sevRtn = SEVERE_ERROR;

	DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

	try
	{  
		if (IFASTBP_PROC::ENTITY_REG_DETAILS_LIST == idContainer)
		{

			EntityRegDetailsList *pEntityRegDetailsList = NULL;

			if(_dstrCaller == I_("COA") || _dstrCaller == I_("NASU"))
			{
				MFAccount *pMFAccount = NULL;
				pMFAccount = dynamic_cast<MFAccount*> (getCBOItem(IFASTBP_PROC::MFACCOUNT_CBO, idDataGroup));

				if (pMFAccount && pMFAccount->getEntityRegDetailsList(pEntityRegDetailsList, _dstrEntityId, idDataGroup) <= WARNING &&
					pEntityRegDetailsList)
				{
					ptr = pEntityRegDetailsList;
				}
			}
			else if(_dstrCaller == I_("Entity") || _dstrCaller == I_("AllEntity"))
			{
				Entity *pEntity = NULL;

				if( dstcWorkSession->getEntity( getDataGroupId(), _dstrEntityId, pEntity ) <= WARNING &&
					pEntity)
				{
					/* 
						Identify Account is needed as there could be 1 entity under multiple account,
						Process layer know which account is point to at the time. So send it to CBO.
					*/
					if(pEntity->getEntityRegDetailsList(pEntityRegDetailsList, idDataGroup, _dstrAccountNum) <= WARNING &&
					   pEntityRegDetailsList)
					{			
                        pEntity->setField(ifds::CurrentEntRegAcctNum, _dstrAccountNum, idDataGroup);
						pEntityRegDetailsList->setDefaultEntityId(_dstrEntityId, idDataGroup);
						ptr = pEntityRegDetailsList;
					}
				}

			}

		}	
		if (IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST == idContainer)
		{			
			EntityRegJurisDetailsList *pEntityRegJurisDetailsList = NULL;

			if(_dstrCaller == I_("COA") || _dstrCaller == I_("NASU"))
			{
				MFAccount *pMFAccount = NULL;
				pMFAccount = dynamic_cast<MFAccount*> (getCBOItem(IFASTBP_PROC::MFACCOUNT_CBO, idDataGroup));

				if (pMFAccount && pMFAccount->getEntityRegJurisDetailsList(pEntityRegJurisDetailsList, _dstrEntityId, idDataGroup) <= WARNING &&
					pEntityRegJurisDetailsList)
				{
					ptr = pEntityRegJurisDetailsList;
				}
			}
			else if(_dstrCaller == I_("Entity") || _dstrCaller == I_("AllEntity"))
			{
				Entity *pEntity = NULL;

				if( dstcWorkSession->getEntity( getDataGroupId(), _dstrEntityId, pEntity ) <= WARNING &&
					pEntity)
				{
					if(pEntity->getEntityRegJurisDetailsList(pEntityRegJurisDetailsList, idDataGroup, _dstrAccountNum) <= WARNING &&
					   pEntityRegJurisDetailsList)
					{
                        pEntity->setField(ifds::CurrentEntRegAcctNum, _dstrAccountNum, idDataGroup);
						pEntityRegJurisDetailsList->setDefaultEntityId(_dstrEntityId, idDataGroup);
						ptr = pEntityRegJurisDetailsList;
					}
				}

			}			


		}
		else if (IFASTBP_PROC::MFACCOUNT_CBO == idContainer)
		{
			MFAccount *pMFAccount = NULL;;

			if (dstcWorkSession->getMFAccount(getDataGroupId(), _dstrAccountNum, pMFAccount) <= WARNING && pMFAccount)
			{
				ptr = pMFAccount;
			}
		}
		else if (IFASTBP_PROC::ENTITY_LIST == idContainer)
		{
			Entity *pEntity = NULL;

			if( dstcWorkSession->getEntity( getDataGroupId(), _dstrEntityId, pEntity ) <= WARNING &&
				pEntity)
			{
				ptr = pEntity;
			}
		}

	}
	catch (ConditionException &)
	{
		throw;
	}
	catch (...)
	{
		assert(0);
		THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, I_("getPtrForContainer"),
			CND::BP_ERR_UNKNOWN_EXCEPTION);
	}

	return ptr;
}


//****************************************************************
SEVERITY EntityRegDetailsProcess::getHistoricalParameters (const BFContainerId &idContainer, 
											  BFFieldId &recordIdField, 
											  DString &tableId, 
											  DString &dstrKey) 
{
	MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);


	if (idContainer == IFASTBP_PROC::ENTITY_REG_DETAILS_LIST)
	{
		recordIdField = ifds::EntRegDetlRId;
		tableId = AUDITTYPE::ENTREGDETAILS;
		dstrKey = NULL_STRING;
	}
	else if (idContainer == IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST)
	{
		recordIdField = ifds::EntRegJurisDetlRId;
		tableId = AUDITTYPE::ENTREGJURISDETAILS;
		dstrKey = NULL_STRING;
	}
	else
	{
		assert(0);
	}

	return GETCURRENTHIGHESTSEVERITY();
}


SEVERITY EntityRegDetailsProcess::getHistoricalParameters(const BFContainerId& idContainer, 
														   HISTORICAL_VECTOR &vectorHistorical)
{
	MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);

	return GETCURRENTHIGHESTSEVERITY();
}