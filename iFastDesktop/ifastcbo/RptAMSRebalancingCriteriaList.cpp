//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 by International Financial, Inc.
//
//*****************************************************************************
//
// ^FILE   : RptAMSRebalancingCriteriaList.cpp
// ^AUTHOR : 
// ^DATE   : Nov 15, 2002
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : RptAMSRebalancingCriteriaList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************

#include "stdafx.h"

#include "errmsgruleslist.hpp"
#include "mgmtco.hpp"
#include "rptAMSRebalancingCriteria.hpp"
#include "rptAMSRebalancingCriterialist.hpp"
#include "AMSHypoAllocList.hpp"
#include "AMSHypoAlloc.hpp"
#include "AmsFundAlloc.hpp"
#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_err_proposed_alloc_is_required.h>
#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_err_enter_valid_account_number.h>

namespace
{
   const I_CHAR * const CLASSNAME = I_( "RptAMSRebalancingCriteriaList" );
   const I_CHAR * const NO        = I_( "N" );
   const I_CHAR * const AMS_REBALANCING = I_( "IFAST.AMSREBAL" );
   const I_CHAR * const AMS_HYPOCALC_REBALANCING = I_( "IFAST.AMSHYPOCALCREBAL" );
};

namespace ifds
{
	extern CLASS_IMPORT const BFTextFieldId ReportMode;
	extern CLASS_IMPORT const BFTextFieldId ReportType;
	extern CLASS_IMPORT const BFTextFieldId ReportName;
	extern CLASS_IMPORT const BFTextFieldId InclPending;
	extern CLASS_IMPORT const BFDateFieldId StartDate;
	extern CLASS_IMPORT const BFTextFieldId CriteriaType;
	extern CLASS_IMPORT const BFTextFieldId CriteriaValue;
	extern CLASS_IMPORT const BFNumericFieldId AccountNum;

	extern CLASS_IMPORT const BFDateFieldId LiveRunDate;
	extern CLASS_IMPORT const BFTextFieldId UnsettleWithAMSFund;
	extern CLASS_IMPORT const BFTextFieldId PendingWithAMSFund;

	extern CLASS_IMPORT const BFTextFieldId AMSCode;
	extern CLASS_IMPORT const BFTextFieldId AMSType;
	extern CLASS_IMPORT const BFTextFieldId IsEnabledBtnAlloc;
	extern CLASS_IMPORT const BFTextFieldId FundAlloc;

	extern CLASS_IMPORT const BFTextFieldId FundCode;
	extern CLASS_IMPORT const BFTextFieldId ClassCode;
	extern CLASS_IMPORT const BFTextFieldId ToFundNumber;
	extern CLASS_IMPORT const BFDecimalFieldId AllocPercentage;
	extern CLASS_IMPORT const BFTextFieldId AccountLevelRebal;
}

namespace CND
{
	CIFast_IFast_ifastcbo_err_proposed_alloc_is_required;
	CIFast_IFast_ifastcbo_err_enter_valid_account_number;
}
struct CriteriaTypeCardinality
{
   const I_CHAR* CriteriaType;
   unsigned int min;
   unsigned int max;
};

const struct CriteriaTypeCardinality m_CriteriaTypeCardinality[] = 
{
   // Criteria Type             Min   Max   
   I_( "StartDate" ),           1,    1,
   I_( "InclPending" ),         1,    1,
   I_( "AccountNum" ),          0,    -1,      // -1 Represent infinte
   I_( "AMSCode" ),             0,    -1,
   I_( "BrokerCode" ),          0,    -1,
   I_( "GroupCode" ),           0,    -1,	
   I_( "LiveRunDate" ),         1,    1,
   I_( "UnsettleWithAMSFund" ), 1,    1,
   I_( "PendingWithAMSFund" ),  1,    1,
};

const struct CriteriaTypeCardinality m_CriteriaTypeCardinality2[] = 
{
   // Criteria Type             Min   Max   
   I_( "StartDate" ),           1,    1,
   I_( "InclPending" ),         1,    1,
   I_( "AccountNum" ),          0,    1,
   I_( "AMSCode" ),             0,    1,
   I_( "GlobalLevelRebal" ),    0,    1,
   I_( "AccountLevelRebal" ),   0,    1,
};

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
//  Field DD Id,			     State Flags,   Group Flags 
	{ ifds::IsEnabledBtnAlloc,	 BFCBO::NONE, 0 },
	{ ifds::FundAlloc,			 BFCBO::NONE, 0 },

};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );
static const int numCriteriaTypeCardinality = sizeof( m_CriteriaTypeCardinality ) / sizeof( CriteriaTypeCardinality );
static const int numCriteriaTypeCardinality2 = sizeof( m_CriteriaTypeCardinality2 ) / sizeof( CriteriaTypeCardinality );
//*****************************************************************************
// Constructor
//*****************************************************************************

RptAMSRebalancingCriteriaList::RptAMSRebalancingCriteriaList( BFAbstractCBO &parent )
:  ifastReportCriteriaList( parent ),
_pAMSHypoAllocList(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );   
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
   setObjectAsList();
}

//*****************************************************************************
// Destructor
//*****************************************************************************

RptAMSRebalancingCriteriaList::~RptAMSRebalancingCriteriaList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*****************************************************************************
// The init will set up the cardinality rules.  Refer to the struct 
// m_CriteriaTypeCardinality for the rules.
// @param   void.
// @returns void.
//*****************************************************************************
void RptAMSRebalancingCriteriaList::init ( const BFDataGroupId& idDataGroup)
{
   addRequiredRecord ( ifds::StartDate,   idDataGroup );
   addRequiredRecord ( ifds::InclPending, idDataGroup );
   addRequiredRecord ( ifds::LiveRunDate, idDataGroup );

	ErrMsgRulesList *pErrMsgRulesList = NULL;
	if ( getMgmtCo().getErrMsgRulesList( pErrMsgRulesList ) <= WARNING &&
		  NULL != pErrMsgRulesList )
	{
		// For the fields below, if the corresponding Rej-Error is not set to ignore, then
		// add the record
		DString dstrErrValue;
		pErrMsgRulesList->getEWIValue( I_( "406" ), idDataGroup, dstrErrValue );
			
		dstrErrValue.strip().upperCase();
		if ( dstrErrValue != I_("I") )
		{			
			addRequiredRecord ( ifds::UnsettleWithAMSFund, idDataGroup );
		}
				
		pErrMsgRulesList->getEWIValue( I_( "405" ), idDataGroup, dstrErrValue );			
		dstrErrValue.strip().upperCase();
		if ( dstrErrValue != I_("I") )
		{			
			addRequiredRecord ( ifds::PendingWithAMSFund, idDataGroup );
		}		
	}	
}

void RptAMSRebalancingCriteriaList::initWithRptName( const BFDataGroupId& idDataGroup, DString dstrRptName)
{
	if ( dstrRptName == AMS_REBALANCING)
	{
		for ( int i = 0; i < numCriteriaTypeCardinality; i++ ) {
		  addFieldCardinality ( DString (m_CriteriaTypeCardinality[i].CriteriaType),
								m_CriteriaTypeCardinality[i].min,
								m_CriteriaTypeCardinality[i].max );
		}
		init ( idDataGroup );
	}
	else if (dstrRptName == AMS_HYPOCALC_REBALANCING )
	{
		for ( int i = 0; i < numCriteriaTypeCardinality2; i++ ) {
		  addFieldCardinality ( DString (m_CriteriaTypeCardinality2[i].CriteriaType),
								m_CriteriaTypeCardinality2[i].min,
								m_CriteriaTypeCardinality2[i].max );
		}
		addRequiredRecord ( ifds::StartDate,   idDataGroup );
	    addRequiredRecord ( ifds::InclPending, idDataGroup );
		addRequiredRecord ( ifds::AMSCode, idDataGroup );
    }
}
//*****************************************************************************
// This method will create a new rptAMSRebalancingCriteria cbo.
// @param   BFCBO*& pBase - pointer to new AMSRebalancing cbo.
//          DString& strKey - key of new AMSRebalacing cbo.
//          const BFDataGroupId& idDataGroup - current data group id.
// @returns SEVERITY - NO_CONDITION most of the time.
//*****************************************************************************
SEVERITY RptAMSRebalancingCriteriaList::doCreateNewObject( BFCBO*& pBase, DString & strKey, const BFDataGroupId& idDataGroup  )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );
   DString dstrRptName;
   getParent()->getField(ifds::ReportName, dstrRptName, idDataGroup);
   pBase = new RptAMSRebalancingCriteria ( dstrRptName, *this, idDataGroup );
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
// This method creates a rptAMSRebalancingCriteria cbo and sets it up to the 
// criteria type passed in marking it required and with default values.
// @param   BFFieldId criteriaType - required criteria type to add to list.
// @returns SEVERITY.
//*****************************************************************************
SEVERITY RptAMSRebalancingCriteriaList::addRequiredRecord( BFFieldId criteriaType, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "addRequiredRecord" ) );   
   DString dstrRptName;
   getParent()->getField(ifds::ReportName, dstrRptName, idDataGroup);
   RptAMSRebalancingCriteria *pRptAMSRebalancingCriteria = new RptAMSRebalancingCriteria ( dstrRptName,*this, idDataGroup );   
   pRptAMSRebalancingCriteria->setupRequiredRecord ( criteriaType, idDataGroup );
   DString dstrKey;
   getStrKey ( dstrKey );     
   pRptAMSRebalancingCriteria->setNonDummyFlag();
   setObject( pRptAMSRebalancingCriteria, dstrKey, OBJ_ACTIVITY_ADDED, idDataGroup );
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
// This method is invoked by the ifastCommonReportCriteria to apply rules when the 
// Report Type switches between online/cycle.  AMS requires that the Incl Pending
// Trades to be set to No when the Report Type is cycle.
// @param   bool bOnline - boolean to indicate whether it is online or cycle.
//          const BFDataGroupId& idDataGroup - current data group id.
//*****************************************************************************
void RptAMSRebalancingCriteriaList::doReportTypeRelatedChanges ( bool bOnline, const BFDataGroupId& idDataGroup )
{
   DString dstrCriteriaType;
   BFFieldId curFieldId;
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   while ( !iter.end() ) 
	{
      iter.getObject()->getField ( ifds::CriteriaType, dstrCriteriaType, idDataGroup );
      curFieldId = BFFieldId::getId ( dstrCriteriaType );
      if ( curFieldId == ifds::InclPending ) 
		{
         break;
      }
      ++iter;
   }

   if ( !bOnline ) {      
      iter.getObject()->setField ( curFieldId, NO, idDataGroup, true, true, true );
      iter.getObject()->setFieldReadOnly ( curFieldId, idDataGroup, true );
   } else  {
      iter.getObject()->setFieldReadOnly ( curFieldId, idDataGroup, false );
   }
}

//*****************************************************************************
SEVERITY RptAMSRebalancingCriteriaList::doAllReportModeRelatedChanges ( const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doReportModeRelatedChanges" ) );   
	
	DString dstrCriteriaType;
	BFFieldId curFieldId;
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   while ( !iter.end() ) 
	{
		RptAMSRebalancingCriteria *pRptAMSRebalancingCriteria = dynamic_cast < RptAMSRebalancingCriteria *> (iter.getObject ());

		if ( NULL != pRptAMSRebalancingCriteria )
		{
			pRptAMSRebalancingCriteria->getField ( ifds::CriteriaType, dstrCriteriaType, idDataGroup );
			curFieldId = BFFieldId::getId ( dstrCriteriaType );
			if ( curFieldId == ifds::UnsettleWithAMSFund ) 
			{
				pRptAMSRebalancingCriteria->doReportModeRelatedChanges( curFieldId, idDataGroup );   
			
				DString dstrUnsettledWithAMSFunds;
				getField( ifds::UnsettleWithAMSFund, dstrUnsettledWithAMSFunds, idDataGroup );
				// If field value is Yes and we are in report mode, make sure there is no Account with 
				// unsettled AMS trades
				if ( I_( "Y") == dstrUnsettledWithAMSFunds.strip().upperCase() )
				{		
					DString dstrReportMode;
					getParent()->getField( ifds::ReportMode, dstrReportMode, idDataGroup );	

					if ( I_( "N" ) == dstrReportMode.strip().upperCase() )   // Report Mode
					{
						// Now validate all accounts
						RptAMSRebalancingCriteriaList *ppRptAMSRebalancingCriteriaList = dynamic_cast<RptAMSRebalancingCriteriaList*>( getParent( ) );      
						BFObjIter iiter( *ppRptAMSRebalancingCriteriaList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
						while ( !iiter.end() ) 
						{
							RptAMSRebalancingCriteria *ppRptAMSRebalancingCriteria = dynamic_cast<RptAMSRebalancingCriteria *> (iiter.getObject ());
							if ( NULL != ppRptAMSRebalancingCriteria )
							{
								DString   dstrCriteriaType;
								BFFieldId curFieldId;
								ppRptAMSRebalancingCriteria->getField ( ifds::CriteriaType, dstrCriteriaType, idDataGroup );
								curFieldId = BFFieldId::getId ( dstrCriteriaType );
								if ( curFieldId == ifds::AccountNum ) 
								{
									ppRptAMSRebalancingCriteria->doReportModeRelatedChanges( ifds::AccountNum, idDataGroup );	
								}
							}
							++iiter;
						}
					}
				}			
				// Don't break here as there can be several account records 
			}

			if ( curFieldId == ifds::PendingWithAMSFund ) 
			{
				pRptAMSRebalancingCriteria->doReportModeRelatedChanges( curFieldId, idDataGroup );  
								
				DString dstrPendingWithAMSFund;
				getField( ifds::PendingWithAMSFund, dstrPendingWithAMSFund, idDataGroup );
				// If field value is Yes and we are in report mode, make sure there is no Account with 
				// pending AMS trades
				if ( I_( "Y") == dstrPendingWithAMSFund.strip().upperCase() )
				{		
					DString dstrReportMode;
					getParent()->getField( ifds::ReportMode, dstrReportMode, idDataGroup );	

					if ( I_( "N" ) == dstrReportMode.strip().upperCase() )   // Report Mode
					{
						// Now validate all accounts
						RptAMSRebalancingCriteriaList *ppRptAMSRebalancingCriteriaList = dynamic_cast<RptAMSRebalancingCriteriaList*>( getParent( ) );      
						BFObjIter iiter( *ppRptAMSRebalancingCriteriaList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
						while ( !iiter.end() ) 
						{
							RptAMSRebalancingCriteria *ppRptAMSRebalancingCriteria = dynamic_cast<RptAMSRebalancingCriteria *> (iiter.getObject ());
							if ( NULL != ppRptAMSRebalancingCriteria )
							{
								DString   dstrCriteriaType;
								BFFieldId curFieldId;
								ppRptAMSRebalancingCriteria->getField ( ifds::CriteriaType, dstrCriteriaType, idDataGroup );
								curFieldId = BFFieldId::getId ( dstrCriteriaType );
								if ( curFieldId == ifds::AccountNum ) 
								{
									ppRptAMSRebalancingCriteria->doReportModeRelatedChanges( ifds::AccountNum, idDataGroup );						
								}
							}
							++iiter;
						}
					}
				}			

				// Don't break here as there can be several account records 
			}

			if ( curFieldId == ifds::AccountNum ) 
			{
				pRptAMSRebalancingCriteria->doReportModeRelatedChanges( curFieldId, idDataGroup );   				
				// Don't break here as there can be several account records 
			}
		}		

      ++iter;
   }
	

	return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
SEVERITY RptAMSRebalancingCriteriaList::doInitPendingModeRelatedChanges ( const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doInitPendingModeRelatedChanges" ) );   

	DString dstrCriteriaType;
	BFFieldId curFieldId;
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   while ( !iter.end() ) 
	{
		RptAMSRebalancingCriteria *pRptAMSRebalancingCriteria = dynamic_cast < RptAMSRebalancingCriteria *> (iter.getObject ());

		if ( NULL != pRptAMSRebalancingCriteria )
		{
			pRptAMSRebalancingCriteria->getField ( ifds::CriteriaType, dstrCriteriaType, idDataGroup );
			curFieldId = BFFieldId::getId ( dstrCriteriaType );
			if ( curFieldId == ifds::InclPending ) 
			{
				pRptAMSRebalancingCriteria->doReportModeRelatedChanges( curFieldId, idDataGroup );   				
				break;
			}			
		}	
      ++iter;
   }
	

	return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
SEVERITY RptAMSRebalancingCriteriaList::doAllReportNameRelatedChanges( const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doAllReportNameRelatedChanges" ) );   
	setFieldReadOnly( ifds::ReportName, idDataGroup, true );

	return GETCURRENTHIGHESTSEVERITY();
}


//*****************************************************************************
SEVERITY RptAMSRebalancingCriteriaList::createAMSHypoAllocList ( AMSHypoAllocList*& pAMSHypoAllocList, DString identifyType, DString identifyCode ,FundAllocList* pFundAllocList, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "createAMSHypoALlocList" ) );
   _pAMSHypoAllocList = new AMSHypoAllocList( *this );
   _pAMSHypoAllocList->setField(ifds::AMSType, I_("RB"), idDataGroup);
   if ( pFundAllocList )
   {
	   BFObjIter iter(*pFundAllocList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
	   for( iter.begin();!iter.end();iter++)
	   {
		   DString dstrFundCode, dstrClassCode, dstrToFundNumber,dstrAllocPrcnt;
		   FundAlloc* pFundAlloc = dynamic_cast<FundAlloc*> (iter.getObject());
		   pFundAlloc->getField(ifds::FundCode, dstrFundCode, idDataGroup);
		   pFundAlloc->getField(ifds::ClassCode, dstrClassCode, idDataGroup);
		   pFundAlloc->getField(ifds::ToFundNumber, dstrToFundNumber, idDataGroup);
		   pFundAlloc->getField(ifds::AllocPercentage, dstrAllocPrcnt, idDataGroup);
	   
		   _pAMSHypoAllocList->doCopyCurrAlloc(dstrToFundNumber, dstrFundCode, dstrClassCode, dstrAllocPrcnt, idDataGroup);	   
	   }
   }
   if ( identifyType == I_("AMSCode") )
	   _pAMSHypoAllocList->setField(ifds::AMSCode, identifyCode, idDataGroup);
   else if ( identifyType == I_("AccountNum") )
   {
	   _pAMSHypoAllocList->setField(ifds::AMSCode, I_("0001"), idDataGroup);
	   _pAMSHypoAllocList->setField(ifds::AccountNum, identifyCode, idDataGroup); 
   }
   
   pAMSHypoAllocList = _pAMSHypoAllocList;   
   setObject(pAMSHypoAllocList, I_("AMSHypoAllocList"), OBJ_ACTIVITY_ADDED, idDataGroup );
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
AMSHypoAllocList* RptAMSRebalancingCriteriaList::getAMSHypoAllocList( const BFDataGroupId& idDataGroup)
{
	AMSHypoAllocList* getAMSHypoAllocList( const BFDataGroupId& idDataGroup );
	return dynamic_cast<AMSHypoAllocList*>(getObject(I_("AMSHypoAllocList"),idDataGroup));
}

//******************************************************************************
SEVERITY RptAMSRebalancingCriteriaList::deleteAMSHypoAllocList ( const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "deleteAMSHypoAllocList" ) );
	setObject(NULL, I_("AMSHypoAllocList"), OBJ_ACTIVITY_ADDED, idDataGroup );
	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY RptAMSRebalancingCriteriaList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );
	DString dstrRptName;
	getParent()->getField(ifds::ReportName, dstrRptName, idDataGroup);

	//Those validation below are use only AMS Hypothetical Rebalancing.
	if ( dstrRptName == AMS_HYPOCALC_REBALANCING )
	{
		DString dstrIsEnableBtnAlloc;
		bool bRequireAlloc = false;
		getField(ifds::IsEnabledBtnAlloc, dstrIsEnableBtnAlloc, idDataGroup);
	
		if (dstrIsEnableBtnAlloc == I_("Y") && _pAMSHypoAllocList == NULL)
			bRequireAlloc = true;
		else if ( _pAMSHypoAllocList )
		{
			BFObjIter iter(*_pAMSHypoAllocList, idDataGroup);
			AMSHypoAlloc* pAMSHypoAlloc = NULL;
			for( iter.begin();!iter.end();iter++ )
			{
				pAMSHypoAlloc = dynamic_cast<AMSHypoAlloc*> (iter.getObject());
				break;
			}
			if (!pAMSHypoAlloc)
				bRequireAlloc = true;
		}

		if ( bRequireAlloc )
		{     
		   CND::CIFast_IFast_ifastcbo_err_proposed_alloc_is_required ERR_PROPOSED_ALLOC_IS_REQUIRED;
		   ADDCONDITIONFROMOBJECT ( ERR_PROPOSED_ALLOC_IS_REQUIRED );
		   return(GETCURRENTHIGHESTSEVERITY());
		}

		DString dstrAMSCode, dstrCriteriaVal;
		bool bAccountLevelRebal = false, bHasAccountNum = false;

		BFObjIter iter(*this, idDataGroup);
		for(iter.begin();!iter.end();iter++)
		{
			auto pRptAMSRebalancingCriteria = dynamic_cast<RptAMSRebalancingCriteria*> (iter.getObject());
			if( pRptAMSRebalancingCriteria == NULL)
				continue;
		
			DString dstrCriteriaType;
			pRptAMSRebalancingCriteria->getField(ifds::CriteriaType, dstrCriteriaType, idDataGroup);
			if ( dstrCriteriaType == I_("AMSCode") )
				pRptAMSRebalancingCriteria->getField(ifds::AMSCode, dstrAMSCode, idDataGroup);
			else if ( dstrCriteriaType == I_("AccountLevelRebal") )
			{
				pRptAMSRebalancingCriteria->getField(ifds::AccountLevelRebal, dstrCriteriaVal, idDataGroup);
				if ( dstrCriteriaVal == I_("Y") )
					bAccountLevelRebal = true;
			}
			else if ( dstrCriteriaType == I_("AccountNum") )
			{
				pRptAMSRebalancingCriteria->getField(ifds::AccountNum, dstrCriteriaVal, idDataGroup);
				if ( dstrCriteriaVal != NULL_STRING )
					bHasAccountNum = true;
			}
		}

		if ( dstrAMSCode == I_("0001") || bAccountLevelRebal )
			if ( !bHasAccountNum )
			{
				CND::CIFast_IFast_ifastcbo_err_enter_valid_account_number ERR_ENTER_VALID_ACCOUNT_NUMBER;
				ADDCONDITIONFROMOBJECT ( ERR_ENTER_VALID_ACCOUNT_NUMBER );
				return(GETCURRENTHIGHESTSEVERITY());
			}
	}
	ifastReportCriteriaList::doValidateAll(idDataGroup, lValidateGroup);
	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RptAMSRebalancingCriteriaList.cpp-arc  $
// 
//    Rev 1.12   Nov 14 2004 14:53:10   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.11   Jul 08 2004 13:43:08   VADEANUM
// PTS 10032106 - Accounts validation when in Report Mode and Include AMS Pending or Unsettled Trades.
// 
//    Rev 1.10   Jun 29 2004 17:16:48   VADEANUM
// PTS 10031151 - InclPending validation.
// 
//    Rev 1.9   Jun 29 2004 17:04:54   VADEANUM
// PTS 10031437 - Exclude edit check for errors 405 and 406 for Account Validation - backed out changes for PTS 10031151 - InclPending.
// 
//    Rev 1.8   Jun 21 2004 12:26:38   VADEANUM
// PTS 10031151 - InclPending validation.
// 
//    Rev 1.7   Jun 21 2004 11:22:30   VADEANUM
// PTS 10031437 - Backed out changes for PTS ticket 10031151.
// 
//    Rev 1.6   Jun 21 2004 10:24:14   VADEANUM
// PTS 10031437 - Excluded the edit check for error number 405 and 406 when user is running the option in 'Report' mode. Backed out changes for PTS ticket 10031151.
// 
//    Rev 1.5   Jun 09 2004 15:12:12   VADEANUM
// PTS 10031151 - Include Pending Trades in Report mode, Online.
// 
//    Rev 1.4   Apr 09 2004 11:02:52   VADEANUM
// PET1005 FN11 - AMS Gaps.
// 
//    Rev 1.3   Mar 21 2003 18:22:30   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.2   Dec 08 2002 21:51:38   HSUCHIN
// added doReportTypeRelatedChanges changes
// 
//    Rev 1.1   Nov 29 2002 14:19:30   HSUCHIN
// rename cbo name
// 
//    Rev 1.0   Nov 29 2002 13:38:36   HSUCHIN
// Initial revision.
// 
//    Rev 1.1   Nov 29 2002 13:16:20   HSUCHIN
// clean up
// 
//    Rev 1.0   Nov 27 2002 11:39:14   HSUCHIN
// Initial Revision
*/
