//******************************************************************************
//
// COPYRIGHT:
//
//    Th* comput;
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2008 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : AcctRoundingRuleProcess.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// -----------------------------------------------------------------------------
//
// ^CLASS  : AcctRoundingRuleProcess
//
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"

#include <bfproc\genericinterfacecontainer.hpp>
#include <bfproc\concreteprocesscreator.hpp>
#include <ifastbp\AcctRoundingRuleProcess.hpp>
#include <ifastbp\AcctRoundingRuleProcessIncludes.h>
#include <ifastcbo\AcctRoundingRule.hpp>
#include <ifastcbo\AcctRoundingRuleList.hpp>
#include <ifastcbo\ErrMsgRulesList.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\shareholder.hpp>

extern IFASTBP_LINKAGE const I_CHAR *CMD_GUI_ACCT_ROUNDING_RULE;
extern IFASTBP_LINKAGE const I_CHAR *CMD_BPROC_ACCT_ROUNDING_RULE;

static ConcreteProcessCreator< AcctRoundingRuleProcess > processCreator( CMD_BPROC_ACCT_ROUNDING_RULE );

namespace 
{
    // Trace literals
    const I_CHAR * const CLASSNAME          = I_( "AcctRoundingRuleProcess" );
	const I_CHAR * const FULL_REFRESH       = I_( "FullRefresh" );
    const I_CHAR * const FULL				= I_( "Full" );
    const I_CHAR * const PARTIAL			= I_( "Partial" );  

    const BFFieldId PRIMARY_ACCOUNT_OWNER(100L);
}

namespace CND
{   
    extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{    
    extern CLASS_IMPORT const BFNumericFieldId ShrNum;
}

namespace AUDITTYPE
{
    extern CLASS_IMPORT I_CHAR * const ACTRDR;
}

namespace MFCAN_IP_PARAM
{    
    extern const I_CHAR * const ACCOUNT_NUM;      
}

//******************************************************************************
//              Public Methods
//******************************************************************************
AcctRoundingRuleProcess::AcctRoundingRuleProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
,  _rpChildGI(NULL)
, _dstrNewAccount(NULL_STRING)
, _dstrNewShareholder(NULL_STRING)
{
    TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

    addContainer( IFASTBP_PROC::MFACCOUNT_CBO, false, BF::NullContainerId, true  );
    addContainer( IFASTBP_PROC::SHAREHOLDER_CBO, false, BF::NullContainerId, true );
    addContainer( IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST, true, IFASTBP_PROC::MFACCOUNT_CBO, true, I_("AccountRoundingRule") );

    addFieldDetails( ifds::AccountNum,			IFASTBP_PROC::MFACCOUNT_CBO );   
    addFieldDetails( ifds::ShrNum,				BF::NullContainerId, SUBCLASS_PROCESS );
    addFieldDetails( PRIMARY_ACCOUNT_OWNER,		BF::NullContainerId, SUBCLASS_PROCESS );

    addFieldDetails( ifds::AccountNum,			IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST );	
    addFieldDetails( ifds::RoundFlg,			IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST );
    addFieldDetails( ifds::RecalcMthd,			IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST );
	addFieldDetails( ifds::UnitsPrecisionAcct,	IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST );   
    addFieldDetails( ifds::StartDate,			IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST );
    addFieldDetails( ifds::StopDate,			IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST );
    
    addFieldDetails( ifds::Username,			IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST );
    addFieldDetails( ifds::ModUser,				IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST );
    addFieldDetails( ifds::ModDate,				IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST );
	addFieldDetails( ifds::AcctRndRulesUUID,	IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST );

	addFieldDetails( IsAcctRoundingRulePendProcTrade, IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST, SUBCLASS_PROCESS );
}

//******************************************************************************
AcctRoundingRuleProcess::~AcctRoundingRuleProcess(void)
{
    TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY AcctRoundingRuleProcess::doInit()
{
    MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("doInit"));

   	DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *> (getBFWorkSession ());
	BFDataGroupId idDataGroup = getDataGroupId();

    try
    {
		getParameter (NASULIT::CREATING_SHAREHOLDER, _dstrNewShareholder);
		getParameter (NASULIT::CREATING_ACCOUNT, _dstrNewAccount);
		getParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, _accountNum);

		_dstrNewShareholder.strip().upperCase();
		_dstrNewAccount.strip().upperCase();

		if (_accountNum != NULL_STRING && !_accountNum.empty ())
		{			
			if ( pDSTCWorkSession->getMFAccount ( idDataGroup, 
												  _accountNum, 
												  _pMFAccount, 
												  I_ ("N"), 
												  NULL_STRING, 
												  true, 
												  true) <= WARNING && 
												  _pMFAccount)
			{
				;
			}
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

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
E_COMMANDRETURN AcctRoundingRuleProcess::doProcess()
{
    MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
    E_COMMANDRETURN rtn = CMD_FAILURE;

    try
    {
        if (!isXMLAPIContext() )
        {
            rtn = invokeCommand( this, CMD_GUI_ACCT_ROUNDING_RULE, getProcessType(), isModal(), &_rpChildGI );
        }
        else
        {
            rtn = CMD_MODELESS_INPROCESS;
        }
    }
    catch( ConditionException &ce )
    {
        assert( 0 );
        SETCONDITIONFROMEXCEPTION( ce );
    }
    catch( ... )
    {
        assert( 0 );
        THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS, CND::BP_ERR_UNKNOWN_EXCEPTION );
    }

    return(rtn);
}

//******************************************************************************
bool AcctRoundingRuleProcess::doModelessChildComplete( const Command &cmd )
{
    return( cmd.getKey() == CMD_GUI_ACCT_ROUNDING_RULE  );
}

//******************************************************************************
void *AcctRoundingRuleProcess::getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
    MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("getPtrForContainer") );

    void *ptr = NULL;

    DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
    MgmtCo &pMgmtCo = dstcWorkSession->getMgmtCo();
    assert(dstcWorkSession);

    try
    {
		if (_accountNum != NULL_STRING && !_accountNum.empty ())
		{
			if( IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST == idContainer )
			{
				MFAccount *pMFAccount = NULL;
				dstcWorkSession->getMFAccount( idDataGroup, _accountNum, pMFAccount );

				AcctRoundingRuleList* pAcctRoundingRuleList = NULL;			

				if ( pMFAccount && pMFAccount->getAcctRoundingRuleList( pAcctRoundingRuleList, idDataGroup ) <= WARNING &&
					( NULL != pAcctRoundingRuleList ) )
				{
					ptr = pAcctRoundingRuleList;
				} 			
			}
			else if( IFASTBP_PROC::MFACCOUNT_CBO == idContainer )
			{				
				if ( _pMFAccount )
				{
					ptr = _pMFAccount;
				}
			}
		}
    }
    catch( ConditionException & )
    {
        throw;
    }
    catch( ... )
    {
        assert( 0 );
        THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, I_("getPtrForContainer"),
                        CND::BP_ERR_UNKNOWN_EXCEPTION );
    }
    return(ptr);
}

//******************************************************************************
bool AcctRoundingRuleProcess::doRefresh( GenericInterface *rpGICaller,const I_CHAR *szOriginalCommand )
{
    TRACE_METHOD( CLASSNAME, I_("doRefresh") );

    return ( _rpChildGI->refresh(this, FULL_REFRESH) );
}

//******************************************************************************
void AcctRoundingRuleProcess::doGetField(  const GenericInterface *rpGICaller,
                                           const BFContainerId& idContainer,
                                           const BFFieldId& idField,
                                           const BFDataGroupId& idDataGroup,
                                           DString &strValueOut,
                                           bool bFormatted
                                         ) const
{
    TRACE_METHOD( CLASSNAME, I_("doGetField") );

    try
    {
        if( BF::NullContainerId == idContainer )
        {
            if( idField == ifds::ShrNum )
            {
                AcctRoundingRuleProcess* pThis = const_cast<AcctRoundingRuleProcess*>(this);
                Shareholder* pShareholder = NULL;

                pShareholder = dynamic_cast<Shareholder*>(pThis->getCBOItem( IFASTBP_PROC::SHAREHOLDER_CBO, idDataGroup ));

                if( pShareholder )
                    pShareholder->getField( ifds::ShrNum, strValueOut, idDataGroup, bFormatted);
            }
            else if( idField == PRIMARY_ACCOUNT_OWNER )
            {
                DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
                DString dstrAccountNum = _accountNum;
                dstcWorkSession->getFirstSequenced01AccountholderEntityName( getDataGroupId(), dstrAccountNum, strValueOut );
                strValueOut.strip();
            }
            else if( idField == ifds::AccountNum )
            {
                strValueOut = _accountNum;
            }
        }
        else if ( IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST == idContainer  )
        {
            AcctRoundingRuleProcess* pThis = const_cast<AcctRoundingRuleProcess*>(this);

            AcctRoundingRule* pCBO = dynamic_cast<AcctRoundingRule*>(pThis->getCBOItem( IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST, idDataGroup ));

            if( idField == ifds::AccountNum )
            {
                strValueOut = _accountNum;
            }
        }
        else if ( IFASTBP_PROC::MFACCOUNT_CBO == idContainer )
        {
            
        }
    }
    catch( ConditionException & )
    {
        throw;
    }
    catch( ... )
    {
        assert( 0 );
        THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doGetField"),
                        CND::BP_ERR_UNKNOWN_EXCEPTION );
    }
}

//******************************************************************************
SEVERITY AcctRoundingRuleProcess::doSetField(  const GenericInterface *rpGICaller,
                                               const BFContainerId& idContainer,
                                               const BFFieldId& idField,
                                               const BFDataGroupId& idDataGroup,
                                               const DString& strValue,
                                               bool  bFormatted
                                             )
{
	MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doSetField") );

	if( BF::NullContainerId == idContainer )
	{
		return(GETCURRENTHIGHESTSEVERITY());
	}

	if ( IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST == idContainer )
	{
		AcctRoundingRuleProcess* pThis = const_cast<AcctRoundingRuleProcess*>(this);

		AcctRoundingRule* pCBO = dynamic_cast<AcctRoundingRule*>(pThis->getCBOItem( IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST, idDataGroup ));

		if (pCBO) 
		{
			if ( idField == ifds::RoundFlg ||
				 idField == ifds::RecalcMthd ||
				 idField == ifds::UnitsPrecisionAcct
				)
			{								
				pCBO->setField( idField, strValue, idDataGroup);
			}
			else if ( idField == IsAcctRoundingRulePendProcTrade )
			{				
				pCBO->validatePendingOrProcessedTrades (_accountNum, idDataGroup);
			}
		}
	}

	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool AcctRoundingRuleProcess::doOk( GenericInterface *rpGICaller )
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_("doOk") );

    MFAccount *pMFAccount = NULL;
    const BFDataGroupId& idDataGroup = getDataGroupId();
    DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

    if( NULL != dstcWorkSession &&
       dstcWorkSession->getMFAccount( idDataGroup, _accountNum, pMFAccount ) <= WARNING &&
       NULL != pMFAccount )
    {
        pMFAccount->refreshMe( true );
		
		if(_dstrNewAccount == I_("Y") || _dstrNewShareholder == I_("Y"))
		{
			AcctRoundingRuleProcess* pThis = const_cast<AcctRoundingRuleProcess*>(this);
			AcctRoundingRule* pCBO = dynamic_cast<AcctRoundingRule*>(pThis->getCBOItem( IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST, idDataGroup ));
			pCBO->validateAccountRoundingRule (idDataGroup);
		}
    }

    return ( GETCURRENTHIGHESTSEVERITY() <= WARNING );
}

//******************************************************************************
SEVERITY AcctRoundingRuleProcess::performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, 
                                                 E_SEARCHACTION eSearchAction )
{
    MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("performSearch"));
   
    try
    {
		AcctRoundingRuleList* pAcctRoundingRuleList = dynamic_cast<AcctRoundingRuleList*>(getCBOList(IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST, getDataGroupId()));

        switch( eSearchAction )
        {            
            case SEARCH_NEXT_BLOCK:
            {
                if( idSearch == IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST )
                {					
                    pAcctRoundingRuleList->getMore ();        
                }
            }
            break;
        }
    }
    catch( ConditionException &ce )
    {
        SETCONDITIONFROMEXCEPTION( ce );
    }
    catch( ... )
    {
        assert( 0 );
        THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, I_("performSearch"), CND::BP_ERR_UNKNOWN_EXCEPTION );
    }
    return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool AcctRoundingRuleProcess::doMoreRecordsExist( GenericInterface *rpGICaller,
                                                  const BFContainerId& idSearch )
{
	AcctRoundingRuleList* pAcctRoundingRuleList = dynamic_cast<AcctRoundingRuleList*>(getCBOList(IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST, getDataGroupId()));

    if( idSearch == IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST )
    {
        return ( rpGICaller == NULL || pAcctRoundingRuleList == NULL) ? false : pAcctRoundingRuleList->doMoreRecordsExist();      
    }

    return false;
}

//******************************************************************************
bool AcctRoundingRuleProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{
    MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doModelessSetFocus") );

    bool bRtn = false;
    try
    {
        assert( _rpChildGI );

		if( isValidModelessInterface( _rpChildGI ) )
		{			
			setContainer(IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST, NULL);
			setContainer(IFASTBP_PROC::MFACCOUNT_CBO, NULL);

			bRtn = _rpChildGI->refresh( this, NULL );
			bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
		}
    }
    catch( ConditionException &ce )
    {
        SETCONDITIONFROMEXCEPTION( ce );
    }
    catch( ... )
    {
        assert( 0 );
        THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doModelessSetFocus"),
                        CND::BP_ERR_UNKNOWN_EXCEPTION );
    }

    return bRtn;
}

//******************************************************************************
SEVERITY AcctRoundingRuleProcess::doValidateAll( BFAbstractCBO *rpWSD,
                                                 const BFDataGroupId& idDataGroup )
{
    MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("doValidateAll"));

	AcctRoundingRuleList* pAcctRoundingRuleList = dynamic_cast<AcctRoundingRuleList*>(getCBOList(IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST, idDataGroup));

	if ( pAcctRoundingRuleList )
         pAcctRoundingRuleList->validateAll (idDataGroup);
         
    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AcctRoundingRuleProcess::getHistoricalParameters( const BFContainerId& idContainer, 
                                                           BFFieldId &recordIdField, 
                                                           DString& tableId, 
                                                           DString& dstrKeys ) 
{
    MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("getHistoricalParameters"));    
    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AcctRoundingRuleProcess::getHistoricalParameters( const BFContainerId& idContainer, 
                                                           HISTORICAL_VECTOR &vectorHistorical )
{
	MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("getHistoricalParameters"));

	try
	{
		DString keyStringIDI( NULL_STRING ), dstrRecord;
		DString dstrRoundFlg, dstrRecalcMthd, dstrUnitsPrecisionAcct, dstrStartDate, dstrStopDate;      

		getField( this, IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST, ifds::AccountNum, dstrRecord, false );

		getField(this, IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST, ifds::RoundFlg, dstrRoundFlg, false);
		getField(this, IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST, ifds::RecalcMthd, dstrRecalcMthd, false);
		getField(this, IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST, ifds::UnitsPrecisionAcct, dstrUnitsPrecisionAcct, false);
		getField(this, IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST, ifds::StartDate, dstrStartDate, false);
		getField(this, IFASTBP_PROC::ACCT_ROUNDING_RULE_LIST, ifds::StopDate, dstrStopDate, false);       

		addIDITagValue(keyStringIDI, MFCAN_IP_PARAM::ACCOUNT_NUM, _accountNum );
		addIDITagValue(keyStringIDI, I_("RoundFlag"), dstrRoundFlg );
		addIDITagValue(keyStringIDI, I_("RecalcMthd"), dstrRecalcMthd );
		addIDITagValue(keyStringIDI, I_("UnitsPrecisionAcct"), dstrUnitsPrecisionAcct );
		addIDITagValue(keyStringIDI, I_("StartDate"), dstrStartDate );
		addIDITagValue(keyStringIDI, I_("StopDate"), dstrStopDate );  

		HistoricalElement historicalElement( dstrRecord, AUDITTYPE::ACTRDR, keyStringIDI );
		vectorHistorical.push_back( historicalElement );
	}
	catch( ConditionException &ce )
	{
		SETCONDITIONFROMEXCEPTION( ce );
	}
	catch( ... )
	{
		assert( 0 );
		THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, I_("getHistoricalParameters"),
			CND::BP_ERR_UNKNOWN_EXCEPTION );
	}

	return GETCURRENTHIGHESTSEVERITY();
}

