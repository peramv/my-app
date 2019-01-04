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
//    Copyright 2004 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : RESPTradeSearchCriteria.cpp
// ^AUTHOR :
// ^DATE   : 31/08/2010
//
// ^CLASS    : RESPTradeSearchCriteria
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "RESPTradeSearchCriteria.hpp"
#include "RESPTransactionTypesList.hpp"
#include "RESPBeneficiaryList.hpp"
#include "MFAccount.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "dstcworksession.hpp"

#include <ifastdataimpl\dse_dstc0111_req.hpp>

namespace  
{
   const I_CHAR * const CLASSNAME        = I_( "RESPTradeSearchCriteria" );
   const I_CHAR * const YES              = I_( "Y" );
   const I_CHAR * const NO               = I_( "N" );
   const I_CHAR * const ALL_BENEF        = I_( "ALL" );
   const I_CHAR * const ALL_RESP_TRANS   = I_( "ALL" );
   const I_CHAR * const ALL_TR_STATUS    = I_( "A" );
   const I_CHAR * const HISTORY          = I_( "H" );
   const I_CHAR * const NOT_REPORTED     = I_( "NR" );
   const I_CHAR * const ALL_REPORTED     = I_( "A" );
}

	
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId Pending;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFTextFieldId TransTypeDesc;
   extern CLASS_IMPORT const BFTextFieldId RepHRDC;
   extern CLASS_IMPORT const BFDateFieldId InceptionDate;
}

namespace  CND
{
   extern CLASS_IMPORT const I_CHAR *BFBASE_CONDITION;

   extern const long ERR_SECOND_DATE_EARLIER;
   extern CLASS_IMPORT const long ERR_FIELD_VALUE_NOT_VALID;
   extern const long ERR_FROMDATE_BEFORE_ACCT_EFFECTIVE_DATE;
   extern const long ERR_FROMDATE_BEFORE_ACCT_INCEPTION_DATE;
   extern const long ERR_TODATE_AFTER_CURBUS_DATE;
}

const BFFieldId criteriaFields[]=
{
   ifds::RESPBenefId,
   ifds::FromDate,
   ifds::ToDate,
   ifds::TransTypeDesc,
   ifds::TfrStat,
   ifds::RepHRDC
};
static const int numCriteriaFields = sizeof( criteriaFields ) / sizeof( BFFieldId );

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
	//   Field DD Id,       State Flags,    Group Flags 
   	{ ifds::RESPBenefId,	BFCBO::NONE,    0 }, 
	{ ifds::FromDate,		BFCBO::NONE,    0 }, 
	{ ifds::ToDate,			BFCBO::NONE,    0 }, 
	{ ifds::TransTypeDesc,	BFCBO::NONE,    0 }, 
	{ ifds::TfrStat,		BFCBO::NONE,    0 }, 
	{ ifds::RepHRDC,		BFCBO::NONE,    0 }, 
    { ifds::HistoryPending,	BFCBO::NONE,    0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = 
{
	//  Object Label,               State Flags,      Group Flags 
	{ I_( "RESPTransactionList" ),	BFCBO::NONE,      0},
};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

//****************************************************************************
RESPTradeSearchCriteria::RESPTradeSearchCriteria( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
	TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
	registerMemberData( NUM_FIELDS,(const CLASS_FIELD_INFO *)&classFieldInfo, NUM_OBJECTS, (const CLASS_OBJECT_INFO *)&classObjectInfo );
}

//****************************************************************************
RESPTradeSearchCriteria::~RESPTradeSearchCriteria()
{
	TRACE_DESTRUCTOR( CLASSNAME );
}   

//****************************************************************************

SEVERITY RESPTradeSearchCriteria::init(const DString& dstrAccountNum,
									   const DString &dstrTransId,
									   const DString &dstrTradeDate,
									   const DString &dstrHistoryPending,
									   const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

	m_dstrAccountNum = dstrAccountNum;
	m_dstrTransId = dstrTransId;
	m_dstrTradeDate = dstrTradeDate;
	m_dstrHistoryPending = dstrHistoryPending;
	
	doInitWithDefaultValues(idDataGroup);
	setObjectNew();

	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

void RESPTradeSearchCriteria::doInitWithDefaultValues(const BFDataGroupId& idDataGroup)
{
	loadRESPBenefSubstList (idDataGroup);
	loadRESPTransactionsSubstList (idDataGroup);

	if (m_dstrTransId.empty ())
	{
		initWithDefaultValuesAll (idDataGroup);
	}
	else
	{
		initWithDefaultValuesOne (idDataGroup);
	}
}

//******************************************************************************

void RESPTradeSearchCriteria::initWithDefaultValuesAll(const BFDataGroupId& idDataGroup)
{
	MFAccount* pMFAccount (NULL);
   
	if ( getWorkSession().getMFAccount (idDataGroup, m_dstrAccountNum, pMFAccount) <= WARNING &&
         pMFAccount)
    {
		pMFAccount->getField(ifds::EffectiveDate, m_dstrAcctEffectiveDate, idDataGroup, false );
		pMFAccount->getField(ifds::InceptionDate, m_dstrAcctInceptionDate, idDataGroup, false );
	}

	DString dstrCurrBusDate = getCurrentBusDate();

	setFieldNoValidate(ifds::FromDate, m_dstrAcctInceptionDate, idDataGroup, false, true, true);
	setFieldNoValidate(ifds::ToDate, dstrCurrBusDate, idDataGroup, false, true, true);
	setFieldNoValidate(ifds::RESPBenefId,  ALL_BENEF, idDataGroup, false, true, true);
	setFieldNoValidate(ifds::TransTypeDesc, ALL_RESP_TRANS, idDataGroup, false, true, true);
	setFieldNoValidate(ifds::TfrStat, ALL_TR_STATUS, idDataGroup, false, true, true);
	setFieldNoValidate(ifds::RepHRDC, ALL_REPORTED, idDataGroup, false, true, true);
}
//******************************************************************************
void RESPTradeSearchCriteria::initWithDefaultValuesOne (const BFDataGroupId& idDataGroup)
{

	setFieldNoValidate(ifds::FromDate, m_dstrTradeDate, idDataGroup, false, true, true);
	setFieldNoValidate(ifds::ToDate, m_dstrTradeDate, idDataGroup, false, true, true);
	setFieldNoValidate(ifds::RESPBenefId,  ALL_BENEF, idDataGroup, false, true, true);

	// get description, transfer status & Reported to HRDC from view:
	MFAccount*	pMFAccount = NULL;
	DString		dstrTransTypeDesc;
	DString		dstrTfrStat;
	DString		dstrRepHRDC;

	if (getWorkSession().getMFAccount (idDataGroup, m_dstrAccountNum, pMFAccount) <= WARNING  && pMFAccount)
	{
		RESPTransactionTypesList	*pRESPTransactionTypesList = NULL;
		
		if (pMFAccount->getRESPTransactionTypesList (pRESPTransactionTypesList, m_dstrTransId, m_dstrHistoryPending, idDataGroup) &&
			pRESPTransactionTypesList) 
		{
			DString dstrApplicable;

			pRESPTransactionTypesList->getDescStatHRDCInfo (dstrTransTypeDesc, dstrTfrStat, dstrRepHRDC, idDataGroup);			

			pRESPTransactionTypesList->isTransferStatusApplicable (dstrTransTypeDesc, dstrApplicable, idDataGroup);

			if (dstrApplicable == I_("N"))
			{
				dstrTfrStat = ALL_TR_STATUS;
			}
		}
	}

	setFieldNoValidate(ifds::TransTypeDesc, dstrTransTypeDesc, idDataGroup, false, true, true);
	setFieldNoValidate(ifds::TfrStat, dstrTfrStat, idDataGroup, false, true, true);
	setFieldNoValidate(ifds::RepHRDC, ALL_REPORTED, idDataGroup, false, true, true);

}
//****************************************************************************
SEVERITY RESPTradeSearchCriteria::getRESPTransactionsList (RESPTransactionsList *&pRESPTransactionsList,
														   const DString& accountNum,
                                                           const DString& historyPending,
                                                           const DString& transId,
                                                           const BFDataGroupId& idDataGroup,
                                                           bool inquireDatabase )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getTransactionList" ) );

    MFAccount* pMFAccount (NULL);
         
	if ( getWorkSession().getMFAccount (idDataGroup, accountNum, pMFAccount) <= WARNING &&
         pMFAccount)
    {
		DString dstrRESPBenefId;
		DString dstrRESPBenefName;
		DString dstrFromDate;
		DString dstrToDate;
		DString dstrTransTypeDesc;
		DString dstrTfrStat;
		DString dstrRepHRDC;

		getField(ifds::RESPBenefId, dstrRESPBenefId, idDataGroup, false );
        getField(ifds::FromDate, dstrFromDate, idDataGroup, false );
        getField(ifds::ToDate, dstrToDate, idDataGroup, false );
        getField(ifds::TransTypeDesc, dstrTransTypeDesc,     idDataGroup, false );
        getField(ifds::TfrStat, dstrTfrStat, idDataGroup, false );
		getField(ifds::RepHRDC, dstrRepHRDC, idDataGroup, false );
  		
		if (dstrRESPBenefId == I_("ALL") || dstrRESPBenefId == I_("ACCTLVL"))
		{
			dstrRESPBenefName = dstrRESPBenefId;
			dstrRESPBenefId = I_("0");
		}
		else
		{
			getField(ifds::RESPBenefId, dstrRESPBenefName, idDataGroup, true );
		}

		pMFAccount->getRESPTransactionsList (pRESPTransactionsList, 
                                             m_dstrHistoryPending/*historyPending*/, 
                                             transId, 
											 dstrRESPBenefId,
											 dstrRESPBenefName,
											 dstrFromDate,
											 dstrToDate,
											 dstrTransTypeDesc,
                                             dstrTfrStat,
											 dstrRepHRDC,
                                             idDataGroup, 
											 inquireDatabase);
	}

	return(GETCURRENTHIGHESTSEVERITY());
}

////////////////////////////////VALIDATIONS////////////////////////////////////
//******************************************************************************
SEVERITY RESPTradeSearchCriteria::doValidateField(const BFFieldId& idField, 
                                                  const DString& strValue, 
												  const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

	if (idField == ifds::FromDate)
	{
	   validateFromDate (strValue, idDataGroup);
	}
	else if (idField == ifds::ToDate)
	{
		validateToDate (strValue, idDataGroup);
	}
   
	return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************

SEVERITY RESPTradeSearchCriteria::validateFromDate (const DString &dstrFromDate, const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFromDate" ) );

	DString dstrToDate;

	getField(ifds::ToDate, dstrToDate, idDataGroup, false);
   
	if (DSTCommonFunctions::CompareDates(dstrFromDate, m_dstrAcctInceptionDate) == DSTCommonFunctions::FIRST_EARLIER)
	{
		ADDCONDITIONFROMFILE(CND::ERR_FROMDATE_BEFORE_ACCT_INCEPTION_DATE); 
	}
	
	else if (DSTCommonFunctions::CompareDates (dstrFromDate, dstrToDate) == DSTCommonFunctions::SECOND_EARLIER)
	{
		ADDCONDITIONFROMFILE(CND::ERR_SECOND_DATE_EARLIER); 
	}

	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY RESPTradeSearchCriteria::validateToDate (const DString &dstrToDate, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateToDate" ) );

 	DString dstrFromDate;
	DString dstrCurrentBusDate = getCurrentBusDate ();

	getField(ifds::FromDate, dstrFromDate, idDataGroup, false);
   
	if (DSTCommonFunctions::CompareDates (dstrToDate, dstrFromDate) == DSTCommonFunctions::FIRST_EARLIER)
	{
		ADDCONDITIONFROMFILE(CND::ERR_SECOND_DATE_EARLIER); 
	}
	else if (DSTCommonFunctions::CompareDates (dstrCurrentBusDate, dstrToDate) == DSTCommonFunctions::FIRST_EARLIER)
	{
		ADDCONDITIONFROMFILE(CND::ERR_TODATE_AFTER_CURBUS_DATE); 
	}

   return(GETCURRENTHIGHESTSEVERITY());
}

////////////////////////////////END VALIDATIONS////////////////////////////////
//******************************************************************************
////////////////////////////////RELATED CHANGES////////////////////////////////

//******************************************************************************
SEVERITY RESPTradeSearchCriteria::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

	if( idField == ifds::HistoryPending )
	{      
		getField(ifds::HistoryPending, m_dstrHistoryPending, idDataGroup, false);
      
		if (m_dstrHistoryPending == HISTORY )
		{
			setFieldReadOnly (ifds::RepHRDC, idDataGroup, false);
		}
		else
		{
			setFieldNoValidate(ifds::RepHRDC, NOT_REPORTED, idDataGroup, false, true, true,  false);
			setFieldReadOnly (ifds::RepHRDC, idDataGroup, true);
		}

		loadRESPTransactionsSubstList (idDataGroup);
	}
	else if (idField == ifds::TransTypeDesc)
	{
		DString dstrTransTypeDesc;

		getField(ifds::TransTypeDesc, dstrTransTypeDesc, idDataGroup, false);

		transTypeRelatedChanges (dstrTransTypeDesc, idDataGroup);
	}
   
	setFieldUpdated (idField, idDataGroup, false);
   
	return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
////////////////////////////////END RELATED CHANGES////////////////////////////////
//******************************************************************************
SEVERITY RESPTradeSearchCriteria::loadRESPBenefSubstList( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "loadRESPBenefSubstList" ) );

   MFAccount* pMFAccount = NULL;

   if (getWorkSession().getMFAccount (idDataGroup, m_dstrAccountNum, pMFAccount) <= WARNING  && pMFAccount)
   {
		RESPBeneficiaryList			*pRESPBeneficiaryList = NULL;
		
		if (pMFAccount->getRESPBeneficiaryList (pRESPBeneficiaryList, idDataGroup) &&
			pRESPBeneficiaryList) 
		{
			DString dstrRESPBenefSubList;

			pRESPBeneficiaryList->getSubstitionList (dstrRESPBenefSubList, idDataGroup);

			setFieldAllSubstituteValues( ifds::RESPBenefId, BF::HOST, dstrRESPBenefSubList ); 
		}
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY RESPTradeSearchCriteria::transTypeRelatedChanges (const DString &dstrTransId, 
														   const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "transTypeRelatedChanges" ) );

   MFAccount* pMFAccount = NULL;

   if (getWorkSession().getMFAccount (idDataGroup, m_dstrAccountNum, pMFAccount) <= WARNING  && pMFAccount)
   {
		RESPTransactionTypesList	*pRESPTransactionTypesList = NULL;
		
		if (pMFAccount->getRESPTransactionTypesList (pRESPTransactionTypesList, m_dstrTransId, m_dstrHistoryPending, idDataGroup) &&
			pRESPTransactionTypesList) 
		{
			DString dstrApplicable;
			bool	bReadOnly = false;

			pRESPTransactionTypesList->isTransferStatusApplicable (dstrTransId, dstrApplicable, idDataGroup);

			if (dstrApplicable == I_("N"))
			{
				setFieldNoValidate(ifds::TfrStat, ALL_TR_STATUS, idDataGroup, false, true, true);
				bReadOnly = true;
			}

			setFieldReadOnly (ifds::TfrStat, idDataGroup, bReadOnly);
		}
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY RESPTradeSearchCriteria::loadRESPTransactionsSubstList( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "loadRESPTransactionsSubstList" ) );

   MFAccount* pMFAccount = NULL;

   if (getWorkSession().getMFAccount (idDataGroup, m_dstrAccountNum, pMFAccount) <= WARNING  && pMFAccount)
   {
		RESPTransactionTypesList	*pRESPTransactionTypesList = NULL;
		
		if (pMFAccount->getRESPTransactionTypesList (pRESPTransactionTypesList, m_dstrTransId, m_dstrHistoryPending, idDataGroup) &&
			pRESPTransactionTypesList) 
		{
			DString dstrTransTypeSubList;

			pRESPTransactionTypesList->getSubstitionList (dstrTransTypeSubList, idDataGroup);

			//setFieldAllSubstituteValues( ifds::TransTypeDesc, BF::HOST, dstrTransTypeSubList ); 
			setFieldAllSubstituteValues( ifds::TransTypeDesc, idDataGroup, dstrTransTypeSubList ); 
		}
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
DString RESPTradeSearchCriteria::getCurrentBusDate()
{
	MgmtCoOptions *pMgmtCoOptions = NULL;
	
	getMgmtCo().getMgmtCoOptions( pMgmtCoOptions );
	DString dstrCurrBusDate(NULL_STRING);
   
	if( pMgmtCoOptions )
		pMgmtCoOptions->getField( ifds::CurrBusDate, dstrCurrBusDate, BF::HOST, false );
   
	return dstrCurrBusDate.strip();
}

//******************************************************************************
SEVERITY RESPTradeSearchCriteria::setField( const BFFieldId& fieldId,
                              const DString& strValue,
                              const BFDataGroupId& idDataGroup, 
                              bool  lFormatted,
                              bool  lSideEffect,
                              bool  bCheckCurrentValue)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setField" ) );

   //DSTDateTime does some fancy things with a 9999 date; therefore, translate a 9999 date 
   //into a NULL_STRING, which means the date is NOT specified
   
   DString strFancyDate(strValue);
   if (fieldId == ifds::FromDate || fieldId == ifds::ToDate)
   {
      if (strFancyDate.find( I_("9999") ) != DString::npos)//9999 is part of the date
         strFancyDate = NULL_STRING;
   }
   BFCBO::setField(fieldId, strFancyDate, idDataGroup, lFormatted, lSideEffect, bCheckCurrentValue);  

   return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:: 
*/


