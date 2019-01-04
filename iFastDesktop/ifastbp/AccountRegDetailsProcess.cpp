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
// ^FILE   : AccountRegDetailsProcess.cpp
// ^AUTHOR : Aurkarn Mongkonrat
// ^DATE   : 14/06/2013
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : AccountRegDetailsProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "AccountRegDetailsProcess.hpp"
#include "AccountRegDetailsProcessIncludes.h"
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\MFAccount.hpp>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastcbo\AcctRegDetailsList.hpp>
#include <ifastcbo\MFAccountList.hpp>
#include <ifastcbo\Shareholder.hpp>
#include <ifastcbo\WhereUsedList.hpp>
#include <ifastbp\ifasthistoricalparameters.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_ACCT_REGIS_MAINT;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACCT_REGIS_MAINT;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator<AccountRegDetailsProcess> processCreator(CMD_BPROC_ACCT_REGIS_MAINT);

namespace 
{
	const I_CHAR * const CLASSNAME = I_( "AccountRegDetailsProcess" );
	const I_CHAR * const ACCOUNT_NUMBER   = I_( "AccountNum" );
	const I_CHAR * const Y = I_("Y");
	const I_CHAR * const N = I_("N");
	const I_CHAR * const FATCA = I_("FA");
	const I_CHAR * const FATCA_CRSRP = I_("FA,CRSRP");
}

namespace CND
{
	extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace UAF
{
	extern CLASS_IMPORT I_CHAR * const ACCT_REGIS_MAINT;
}

namespace AUDITTYPE
{
	extern CLASS_IMPORT I_CHAR * const ACCTREGDETAILS;
}

namespace ifds
{   
	extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
	extern CLASS_IMPORT const BFDateFieldId StopDate;
	extern CLASS_IMPORT const BFTextFieldId FICategory;
	extern CLASS_IMPORT const BFTextFieldId FinInstRegDetlUUID;
	extern CLASS_IMPORT const BFTextFieldId AcctRegDetailsUUID;
	extern CLASS_IMPORT const BFTextFieldId ComplyAction;
	extern CLASS_IMPORT const BFTextFieldId Consented;
	extern CLASS_IMPORT const BFNumericFieldId VersionAcctRegDetl;
	extern CLASS_IMPORT const BFNumericFieldId ShrNum;
	extern CLASS_IMPORT const BFNumericFieldId AccountNum;
	extern CLASS_IMPORT const BFDateFieldId ProcessDate;
	extern CLASS_IMPORT const BFTextFieldId Username;
	extern CLASS_IMPORT const BFDateFieldId ModDate;
	extern CLASS_IMPORT const BFTextFieldId ModUser;
	extern CLASS_IMPORT const BFTextFieldId Regulatory;
	extern CLASS_IMPORT const BFTextFieldId DefaultReportingFFI;
	extern CLASS_IMPORT const BFDecimalFieldId AcctRegDetailRid;
	extern CLASS_IMPORT const BFDateFieldId LastReviewDate;
	extern CLASS_IMPORT const BFTextFieldId CountryCode;
	extern CLASS_IMPORT const BFTextFieldId RunMode;
	extern CLASS_IMPORT const BFTextFieldId EntityType;
	extern CLASS_IMPORT const BFTextFieldId EntityName;
	extern CLASS_IMPORT const BFTextFieldId FATCACode;
	extern CLASS_IMPORT const BFTextFieldId TaxJuris;
	extern CLASS_IMPORT const BFTextFieldId TaxPayerStat;
	extern CLASS_IMPORT const BFDateFieldId TaxPayerStartDate;
	extern CLASS_IMPORT const BFTextFieldId PendingFATCASrch;
	extern CLASS_IMPORT const BFTextFieldId ReqIndiciaSearch;
	extern CLASS_IMPORT const BFTextFieldId ComplyRuleDesc;
}


//****************************************************************
AccountRegDetailsProcess::AccountRegDetailsProcess(GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand)
: AbstractProcess(pGIC, pGIParent, rCommand), 
//_pAccountRegDetailsList(NULL),
_rpChildGI(NULL)
{
	TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING );

	addContainer(IFASTBP_PROC::MFACCOUNT_CBO				  , false,BF::NullContainerId, false);
	addContainer(IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST, true, IFASTBP_PROC::MFACCOUNT_CBO, true, I_("AcctRegDetailsList"));
	addContainer(IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST,   true, IFASTBP_PROC::MFACCOUNT_CBO, true, I_("EntityRegJurisDetailsList"));	

	addFieldDetails(ifds::EffectiveDate,		IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST);
	addFieldDetails(ifds::StopDate,				IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST);
	addFieldDetails(ifds::FinInstRegDetlUUID,   IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST);
	addFieldDetails(ifds::FICategory,			IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST);
	addFieldDetails(ifds::AcctRegDetailsUUID,	IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST);
	addFieldDetails(ifds::ComplyAction,			IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST);
	addFieldDetails(ifds::Consented,			IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST);
	addFieldDetails(ifds::VersionAcctRegDetl,	IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST);
	addFieldDetails(ifds::ProcessDate,			IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST);
	addFieldDetails(ifds::Username,				IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST);
	addFieldDetails(ifds::ModDate,				IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST);
	addFieldDetails(ifds::ModUser,				IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST);
	addFieldDetails(ifds::Regulatory,			IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST);
	addFieldDetails(ifds::DefaultReportingFFI,	IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST);
	addFieldDetails(ifds::AcctRegDetailRid,   	IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST);
	addFieldDetails(ifds::ComplyRuleDesc,   	IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST);

	addFieldDetails(ifds::ReqIndiciaSearch,   	IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST, SUBCLASS_PROCESS);

	addFieldDetails(ifds::LastReviewDate,      	IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST, SUBCLASS_PROCESS);
	addFieldDetails(ifds::CountryCode,      	IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST);
	addFieldDetails(ifds::RunMode,      	    IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST);

	addFieldDetails(ifds::ShrNum,				IFASTBP_PROC::MFACCOUNT_CBO);
	addFieldDetails(ifds::AccountNum,			IFASTBP_PROC::MFACCOUNT_CBO);
	addFieldDetails(ifds::PendingFATCASrch,		IFASTBP_PROC::MFACCOUNT_CBO);

	addFieldDetails(ifds::EntityType,			IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST);
	addFieldDetails(ifds::EntityName,			IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST);
	addFieldDetails(ifds::FATCACode,			IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST);
	addFieldDetails(ifds::TaxJuris,			    IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST);	
	addFieldDetails(ifds::TaxPayerStat,		    IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST);	
	addFieldDetails(ifds::TaxPayerStartDate,	IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST);
}


//****************************************************************
AccountRegDetailsProcess::~AccountRegDetailsProcess()
{
	TRACE_DESTRUCTOR(CLASSNAME)
}


//****************************************************************
SEVERITY AccountRegDetailsProcess::doInit()
{
	MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
	SEVERITY sevRtn = SEVERE_ERROR;

	try
	{
		getParent()->getParameter(ACCOUNT_NUMBER, _dstrAccountNum);
		_dstrAccountNum.stripAll();
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
E_COMMANDRETURN AccountRegDetailsProcess::doProcess()
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
			rtn = invokeCommand(this, CMD_GUI_ACCT_REGIS_MAINT, getProcessType(), isModal(), &_rpChildGI);
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
bool AccountRegDetailsProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
	MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
	SEVERITY sevRtn = SEVERE_ERROR;

	bool bRtn = false;
	try
	{
		assert(_rpChildGI && isValidModelessInterface(_rpChildGI));

		if (isValidModelessInterface(_rpChildGI))
		{  
			setContainer(IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST, NULL);
         setContainer(IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST, NULL);
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
bool AccountRegDetailsProcess::doModelessChildComplete( const Command &cmd )
{
	return( cmd.getKey() == CMD_GUI_ACCT_REGIS_MAINT );
}


//****************************************************************
bool AccountRegDetailsProcess::doRefresh( GenericInterface *rpGICaller, const I_CHAR *szOriginalCommand )
{
	TRACE_METHOD(CLASSNAME, DOREFRESH);
	setParameter(ACCOUNT_NUMBER, _dstrAccountNum );

	return(_rpChildGI->refresh( this, NULL ));
}


//****************************************************************
void AccountRegDetailsProcess::doPostOk( GenericInterface *rpGICaller, bool bSuccessFlag )
{
	setParameter(ACCOUNT_NUMBER, _dstrAccountNum);
}


////****************************************************************
bool AccountRegDetailsProcess::doOk(GenericInterface *rpGICaller)
{
   SEVERITY sevReturn = NO_CONDITION;

   /*
       We need to refresh every MFAccount where the Owner of this account own
	   That mean we need to call WhereUseList where the Owner related and get that MFAccount
	   then refresh them.
   */
   AcctRegDetailsList *pAcctRegDetailsList = NULL;
   MFAccount *pMFAccount = NULL;

   DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   const BFDataGroupId& idDataGroup = getDataGroupId();

   pMFAccount = dynamic_cast<MFAccount*>(getCBOItem(IFASTBP_PROC::MFACCOUNT_CBO, idDataGroup));
   pAcctRegDetailsList = dynamic_cast<AcctRegDetailsList*>(getCBOList(IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST, idDataGroup));

   if (pMFAccount && pAcctRegDetailsList && pAcctRegDetailsList->isUpdatedForDataGroup(getDataGroupId()))
   {
	   // to support multiple account environment, 
	   // we need to loop all MFAccount Related as they are appeared on Account Detail.
	        
       ENTITIES_VECTOR acctOwnerEntities;	  
       pMFAccount->getAcctOwnerEntities (acctOwnerEntities, idDataGroup);
	   
	   int iNumOfEntities = acctOwnerEntities.size();

	   bool isEntityAccountOwner (false);

	   for (int i = 0; i < iNumOfEntities; ++i)
	   {
		   DString entityId = acctOwnerEntities [i];
		   DString dstrAccountNum;
		   WhereUsedList *pWhereUsedList = NULL;
		   
		   if( dstcWorkSession->getWhereUsedList(pWhereUsedList, idDataGroup, true, entityId ) <= WARNING )
		   {
			   BFObjIter iterWhereUsed(*pWhereUsedList, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED);
			   iterWhereUsed.begin();

			   while (!iterWhereUsed.end())
			   {
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

   return (sevReturn == NO_CONDITION);
}


//****************************************************************
void AccountRegDetailsProcess::doGetField( const GenericInterface *rpGICaller,
										  const BFContainerId& idContainer,
										  const BFFieldId& idField,
										  const BFDataGroupId& idDataGroup,
										  DString &strValueOut,
										  bool bFormatted
										  ) const
{
	if (IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST == idContainer)
	{
		if (idField == ifds::LastReviewDate)
		{
			DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
			MFAccount *pMFAccount = NULL;
			AcctRegDetailsList *pAcctRegDetailsList = NULL;

			if (dstcWorkSession->getMFAccount(getDataGroupId(), _dstrAccountNum, pMFAccount) <= WARNING && pMFAccount)
			{
				if (pMFAccount->getAcctRegDetailsList(pAcctRegDetailsList, getDataGroupId(), FATCA_CRSRP) <= WARNING &&
					pAcctRegDetailsList)
				{
					pAcctRegDetailsList->getField(idField, strValueOut, idDataGroup, bFormatted);
				}
			}

	}
}
}


//****************************************************************
void *AccountRegDetailsProcess::getPtrForContainer(const BFContainerId& idContainer,
												   const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("getPtrForContainer"));

	void *ptr = NULL;
	SEVERITY sevRtn = SEVERE_ERROR;

	DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

	try
	{  
		if (IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST == idContainer)
		{
			MFAccount *pMFAccount = NULL;
			pMFAccount = dynamic_cast<MFAccount*> (getCBOItem(IFASTBP_PROC::MFACCOUNT_CBO, idDataGroup));
			AcctRegDetailsList *pAcctRegDetailsList = NULL;

			if (pMFAccount && pMFAccount->getAcctRegDetailsList(pAcctRegDetailsList, getDataGroupId(), FATCA_CRSRP) <= WARNING &&
				pAcctRegDetailsList)
			{
				ptr = pAcctRegDetailsList;
			}

		}	
		else if (IFASTBP_PROC::MFACCOUNT_CBO == idContainer)
		{
			MFAccount *pMFAccount = NULL;			

			if (dstcWorkSession->getMFAccount(getDataGroupId(), _dstrAccountNum, pMFAccount) <= WARNING && pMFAccount)
			{
				ptr = pMFAccount;
			}
		}
		else if (IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST == idContainer)
		{
			MFAccount *pMFAccount = NULL;
			pMFAccount = dynamic_cast<MFAccount*> (getCBOItem(IFASTBP_PROC::MFACCOUNT_CBO, idDataGroup));

			if (pMFAccount)
			{
				EntityRegJurisDetailsList *pEntityRegJurisDetailsList = NULL;
				if (pMFAccount->getAccountLvlEntityRegJurisDetailsList(pEntityRegJurisDetailsList, _dstrAccountNum, I_("0"), I_(""), idDataGroup) <= WARNING &&
					pEntityRegJurisDetailsList)
				{
					ptr = pEntityRegJurisDetailsList;
				}				
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
SEVERITY AccountRegDetailsProcess::getHistoricalParameters (const BFContainerId &idContainer, 
											  BFFieldId &recordIdField, 
											  DString &tableId, 
											  DString &dstrKey) 
{
	MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);


	if (idContainer == IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST)
	{
		recordIdField = ifds::AcctRegDetailRid;
		tableId = AUDITTYPE::ACCTREGDETAILS;
		dstrKey = NULL_STRING;
	}
	else
	{
		assert(0);
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************
SEVERITY AccountRegDetailsProcess::getHistoricalParameters(const BFContainerId& idContainer, 
														   HISTORICAL_VECTOR &vectorHistorical)
{
	MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AccountRegDetailsProcess::doSetField( const GenericInterface* rpGICaller,
                                               const BFContainerId& idContainer,
                                               const BFFieldId &fieldID,
                                               const BFDataGroupId& idDataGroup,
                                               const DString &strValue,
                                               bool bFormatted )
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, DOSETFIELD);

   if ( fieldID == ifds::ReqIndiciaSearch &&
        idContainer == IFASTBP_PROC::ACCOUNT_REGULATORY_DETAILS_LIST )
   {
      AccountRegDetailsProcess *pThis = dynamic_cast<AccountRegDetailsProcess*>(this);

      if(pThis)
      {
         BFAbstractCBO *rpPtr = getCBOList (idContainer, idDataGroup);
         if (rpPtr)
         {
            rpPtr->setField ( fieldID, strValue, idDataGroup, bFormatted, false );
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}