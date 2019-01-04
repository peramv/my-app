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
// ^FILE   : AcctSettlementRuleProcess.cpp
// ^AUTHOR : Chatchai Daecha
// ^DATE   : Febuary 2008
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : AcctLvlSttlmntRuleProcess
//
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"

#include "AcctSettlementRuleProcessIncludes.h"
#include "AcctSettlementRuleProcess.hpp"

#include <bfproc\genericinterfacecontainer.hpp>
#include <bfproc\concreteprocesscreator.hpp>

#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\shareholder.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\ErrMsgRulesList.hpp>
#include <ifastcbo\AcctSettlementRule.hpp>
#include <ifastcbo\AcctSettlementRuleList.hpp>
#include <ifastcbo\fundmgmtsettlementinstr.hpp>
#include <ifastcbo\fundmgmtsettlementinstrlist.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_ACCT_LEVEL_SETTLEMENT_RULE;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACCT_LEVEL_SETTLEMENT_RULE;

static ConcreteProcessCreator< AcctLvlSttlmntRuleProcess > processCreator( CMD_BPROC_ACCT_LEVEL_SETTLEMENT_RULE );

namespace 
{
    // Trace literals
    const I_CHAR * const CLASSNAME          = I_( "AcctLvlSttlmntRuleProcess" );
    const I_CHAR * const FULL_REFRESH       = I_( "FullRefresh" );
    const I_CHAR * const PARTIAL_REFRESH    = I_( "PartialRefresh" );

    const I_CHAR * const SETTLE_DAYS_ED     = I_( "24" );
    const I_CHAR * const SETTLE_DAYS_PW     = I_( "25" );
    const I_CHAR * const SETTLE_DAYS_TO     = I_( "26" );
    const I_CHAR * const SETTLE_DAYS_TI     = I_( "27" );
    const I_CHAR * const SETTLE_DAYS_EO     = I_( "28" );
    const I_CHAR * const SETTLE_DAYS_EI     = I_( "29" );

    const BFFieldId PRIMARY_ACCOUNT_OWNER(100L);
}

namespace CND
{
    extern CLASS_IMPORT const long BP_ERR_INVALID_METHOD_CALL;
    extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
    extern CLASS_IMPORT const BFTextFieldId SettleDays;
    extern CLASS_IMPORT const BFTextFieldId FundNumber;
    extern CLASS_IMPORT const BFTextFieldId AcctType;
    extern CLASS_IMPORT const BFTextFieldId TaxType;
    extern CLASS_IMPORT const BFTextFieldId BrokerCode;
    extern CLASS_IMPORT const BFTextFieldId BranchCode;
    extern CLASS_IMPORT const BFTextFieldId Slsrep;

    extern CLASS_IMPORT const BFNumericFieldId ShrNum;
}

namespace ACCSETTLRULELIT
{
    extern const I_CHAR* const ACCOUNT_NUM      = I_( "AccountNum" );
    extern const I_CHAR* const FUND_CODE        = I_( "FundCode" );
    extern const I_CHAR* const CLASS_CODE       = I_( "ClassCode" );
    extern const I_CHAR* const RULE_TYPE        = I_( "RuleType" );
    extern const I_CHAR* const EFFECTIVE_DATE   = I_( "EffectiveDate" );
    extern const I_CHAR* const STOP_DATE        = I_( "StopDate" );
}

namespace AUDITTYPE
{
    extern CLASS_IMPORT I_CHAR * const ACCTCONTROL;
}

namespace MFCAN_IP_PARAM
{
    extern const I_CHAR * const CALLER;
    extern const I_CHAR * const ACCOUNT_NUM;
    extern const I_CHAR * const RULE_TYPE;
    extern const I_CHAR * const FUND_CODE;
    extern const I_CHAR * const CLASS_CODE;
    extern const I_CHAR * const EFFECTIVE_DATE;
           const I_CHAR * const STOP_DATE        = I_("DATE");
}

//******************************************************************************
//              Public Methods
//******************************************************************************
AcctLvlSttlmntRuleProcess::AcctLvlSttlmntRuleProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
,  _rpChildGI( NULL )
, _pAcctLvlSttlmntRuleList(NULL)
{
    TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

    addContainer( IFASTBP_PROC::MFACCOUNT_CBO, false, BF::NullContainerId, true  );
    addContainer( IFASTBP_PROC::SHAREHOLDER_CBO, false, BF::NullContainerId, true );
    addContainer( IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST, true, IFASTBP_PROC::MFACCOUNT_CBO, true, I_("AccountSettlementRule") );

    addFieldDetails( ifds::AccountNum,      IFASTBP_PROC::MFACCOUNT_CBO );
    addFieldDetails( ifds::AcctType,        IFASTBP_PROC::MFACCOUNT_CBO );
    addFieldDetails( ifds::TaxType,         IFASTBP_PROC::MFACCOUNT_CBO );
    addFieldDetails( ifds::BrokerCode,      IFASTBP_PROC::MFACCOUNT_CBO );
    addFieldDetails( ifds::BranchCode,      IFASTBP_PROC::MFACCOUNT_CBO );
    addFieldDetails( ifds::Slsrep,          IFASTBP_PROC::MFACCOUNT_CBO );
    addFieldDetails( ifds::ShrNum,          BF::NullContainerId, SUBCLASS_PROCESS );
    addFieldDetails( PRIMARY_ACCOUNT_OWNER, BF::NullContainerId, SUBCLASS_PROCESS );

    addFieldDetails( ifds::AccountNum,      IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST );

    addFieldDetails( ifds::RuleType,        IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST );
    addFieldDetails( ifds::FundCode,        IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST );
    addFieldDetails( ifds::ClassCode,       IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST );
    addFieldDetails( ifds::FundNumber,      IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST, SUBCLASS_PROCESS ); 
    addFieldDetails( ifds::SettleDays,      IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST, SUBCLASS_PROCESS ); 
    addFieldDetails( ifds::EffectiveDate,   IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST );
    addFieldDetails( ifds::StopDate,        IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST );

    addFieldDetails( ifds::ProcessDate,     IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST );
    addFieldDetails( ifds::Username,        IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST );
    addFieldDetails( ifds::ModUser,         IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST );
    addFieldDetails( ifds::ModDate,         IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST );

    addFieldDetails( ifds::DuplicateCheck,  IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST );
    addFieldDetails( ifds::DuplicateExist,  IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST );
    addFieldDetails( ifds::AcctControlsID,  IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST );
    addFieldDetails( ifds::AcctControlsRID, IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST );
    addFieldDetails( ifds::AcctControlsVer, IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST );

    addFieldDetails( ifds::rxAcctControlsRID,IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST );

    addFieldDetails( ifds::OverrideChar,    IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST );
    addFieldDetails( ifds::OverrideLogical, IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST );
    addFieldDetails( ifds::OverrideAmt,     IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST );
	addFieldDetails( ifds::FundGroup,       IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST );

	addFieldDetails( IsSettlementRulePendingTrade, IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST, SUBCLASS_PROCESS );
}

//******************************************************************************
AcctLvlSttlmntRuleProcess::~AcctLvlSttlmntRuleProcess(void)
{
    TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY AcctLvlSttlmntRuleProcess::doInit()
{
    MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("doInit"));

    getParameter( MFCAN_IP_PARAM::ACCOUNT_NUM, _accountNum );

    try
    {
        const BFDataGroupId& idDataGroup = getDataGroupId();

        DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

        MFAccount *pMFAccount;

        if( dstcWorkSession->getMFAccount( idDataGroup, _accountNum, pMFAccount ) <= WARNING &&
                NULL != pMFAccount )
        {
            if ( pMFAccount->getAcctSettlementRuleList( _pAcctLvlSttlmntRuleList, idDataGroup ) <= WARNING &&
                ( NULL != _pAcctLvlSttlmntRuleList ) )
            {
                setContainer( IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST, _pAcctLvlSttlmntRuleList );
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
E_COMMANDRETURN AcctLvlSttlmntRuleProcess::doProcess()
{
    MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
    E_COMMANDRETURN rtn = CMD_FAILURE;

    try
    {
        if (!isXMLAPIContext() )
        {
            rtn = invokeCommand( this, CMD_GUI_ACCT_LEVEL_SETTLEMENT_RULE, getProcessType(), isModal(), &_rpChildGI );
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
SEVERITY AcctLvlSttlmntRuleProcess::getHistoricalParameters( const BFContainerId& idContainer, 
                                                             BFFieldId &recordIdField, 
                                                             DString& tableId, 
                                                             DString& dstrKeys ) 
{
    MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("getHistoricalParameters"));

    try
    {
        if ( idContainer == IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST )
        {
            recordIdField = ifds::AcctControlsRID;
            tableId       = AUDITTYPE::ACCTCONTROL;
            dstrKeys      = NULL_STRING;
        }
        else
        {
                throw;
                //assert(0);
        }
    }
    catch( ConditionException &ce )
    {
        SETCONDITIONFROMEXCEPTION( ce );
    }
    catch( ... )
    {
        assert(0);
        THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, I_("getHistoricalParameters"),
                        CND::BP_ERR_UNKNOWN_EXCEPTION );
    }

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AcctLvlSttlmntRuleProcess::getHistoricalParameters( const BFContainerId& idContainer, 
                                                             HISTORICAL_VECTOR &vectorHistorical )
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("getHistoricalParameters"));

    try
    {
        DString keyStringIDI( NULL_STRING ), dstrRecord;
        DString dstrFundCode, dstrClassCode, dstrEffectiveDate;
        DString dstrRuleType, dstrStopDate,dstrSettleDays, dstrFundGroup;

        getField( this, IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST, ifds::AcctControlsRID, dstrRecord, false );

        // Account Number, From Fund, From Class, Effective Date.
        getField(this, IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST, ifds::FundCode, dstrFundCode, false);
        getField(this, IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST, ifds::ClassCode, dstrClassCode, false);
        getField(this, IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST, ifds::RuleType, dstrRuleType, false);
        getField(this, IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST, ifds::StopDate, dstrStopDate, false);
        getField(this, IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST, ifds::EffectiveDate, dstrEffectiveDate, false);
        getField(this, IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST, ifds::SettleDays, dstrSettleDays, false);
		getField(this, IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST, ifds::FundGroup, dstrFundGroup, false);

        addIDITagValue(keyStringIDI, MFCAN_IP_PARAM::ACCOUNT_NUM, _accountNum );
        addIDITagValue(keyStringIDI, I_("RuleType"), dstrRuleType );
        addIDITagValue(keyStringIDI, MFCAN_IP_PARAM::FUND_CODE, dstrFundCode );
        addIDITagValue(keyStringIDI, MFCAN_IP_PARAM::CLASS_CODE, dstrClassCode );
        addIDITagValue(keyStringIDI, MFCAN_IP_PARAM::STOP_DATE, dstrStopDate );
        addIDITagValue(keyStringIDI, MFCAN_IP_PARAM::EFFECTIVE_DATE, dstrEffectiveDate );
        addIDITagValue(keyStringIDI, I_("SettleDays"), dstrSettleDays );
		addIDITagValue(keyStringIDI, I_("FundGroup"), dstrFundGroup );

        HistoricalElement historicalElement( dstrRecord, AUDITTYPE::ACCTCONTROL, keyStringIDI );
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

//******************************************************************************
bool AcctLvlSttlmntRuleProcess::doModelessChildComplete( const Command &cmd )
{
    return( cmd.getKey() == CMD_GUI_ACCT_LEVEL_SETTLEMENT_RULE  );
}

//******************************************************************************
void *AcctLvlSttlmntRuleProcess::getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
    MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("getPtrForContainer") );

    void *ptr = NULL;

    DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
    MgmtCo &pMgmtCo = dstcWorkSession->getMgmtCo();
    assert(dstcWorkSession);

    try
    {
        if( IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST == idContainer )
        {
            MFAccount *pMFAccount = NULL;
            dstcWorkSession->getMFAccount( idDataGroup, _accountNum, pMFAccount );

            AcctLvlSttlmntRuleList*  pAcctLvlSttlmntRuleList = NULL;

            if ( pMFAccount->getAcctSettlementRuleList( pAcctLvlSttlmntRuleList, idDataGroup ) <= WARNING &&
                  ( NULL != pAcctLvlSttlmntRuleList ) )
            {
                ptr = pAcctLvlSttlmntRuleList;
            }             
        }
        else if( IFASTBP_PROC::MFACCOUNT_CBO == idContainer )
        {
            if( dstcWorkSession->getMFAccount( idDataGroup, _accountNum, _pMFAccount )<=WARNING )
            {
                ptr = _pMFAccount;
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
bool AcctLvlSttlmntRuleProcess::doRefresh( GenericInterface *rpGICaller,const I_CHAR *szOriginalCommand )
{
    TRACE_METHOD( CLASSNAME, I_("doRefresh") );

    return ( _rpChildGI->refresh(this, FULL_REFRESH) );
}

//******************************************************************************
void AcctLvlSttlmntRuleProcess::doGetField(
                                            const GenericInterface *rpGICaller,
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
                AcctLvlSttlmntRuleProcess* pThis = const_cast<AcctLvlSttlmntRuleProcess*>(this);
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

        else if ( IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST == idContainer  )
        {
            AcctLvlSttlmntRuleProcess* pThis = const_cast<AcctLvlSttlmntRuleProcess*>(this);

            AcctLvlSttlmntRule* pCBO = 
                dynamic_cast<AcctLvlSttlmntRule*>(pThis->getCBOItem( IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST, idDataGroup ));

            if ( idField == ifds::SettleDays )
            {
                DString dstrRuleType;

                pCBO->getField(ifds::RuleType,dstrRuleType,idDataGroup,false);

                if ( dstrRuleType == SETTLE_DAYS_ED || 
                     dstrRuleType == SETTLE_DAYS_PW ||
                     dstrRuleType == SETTLE_DAYS_TO ||
                     dstrRuleType == SETTLE_DAYS_TI ||
                     dstrRuleType == SETTLE_DAYS_EO ||
                     dstrRuleType == SETTLE_DAYS_EI )
                {
                    DString dstrOverrideAmt;
                    pCBO->getField(ifds::OverrideAmt,dstrOverrideAmt,idDataGroup,false);

                    double dOverrideAmt = DSTCommonFunctions::convertToDouble(dstrOverrideAmt);
                    int iOverrideAmt = (int)dOverrideAmt;

                    if ( iOverrideAmt < 0 ) iOverrideAmt *= -1;

                    char szNumBuffer[200];

                    sprintf( szNumBuffer,"%d",iOverrideAmt );

                    strValueOut = szNumBuffer;
                }
            }
            else if ( idField == ifds::FundNumber )
            {
                DString dstrFundCode,dstrClassCode;

                pCBO->getField(ifds::FundCode,dstrFundCode,idDataGroup,false);
                pCBO->getField(ifds::ClassCode,dstrClassCode,idDataGroup,false);

                DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
                dstcWorkSession->GetFundNumber (dstrFundCode, dstrClassCode, strValueOut);        
            }
            else if( idField == ifds::AccountNum )
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
SEVERITY AcctLvlSttlmntRuleProcess::doSetField(
                                                const GenericInterface *rpGICaller,
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

    if ( IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST == idContainer /*&& idField == ifds::SettleDays*/ )
    {
        AcctLvlSttlmntRuleProcess* pThis = const_cast<AcctLvlSttlmntRuleProcess*>(this);

        AcctLvlSttlmntRule* pCBO = 
            dynamic_cast<AcctLvlSttlmntRule*>(pThis->getCBOItem( IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST, idDataGroup ));

		if (pCBO) 
		{
			if ( idField == ifds::SettleDays )
			{
				/*DString dstrRuleType;

				pCBO->getField(ifds::RuleType,dstrRuleType,idDataGroup,false);

				if ( dstrRuleType == SETTLE_DAYS_ED || 
				dstrRuleType == SETTLE_DAYS_PW ||
				dstrRuleType == SETTLE_DAYS_TO ||
				dstrRuleType == SETTLE_DAYS_TI ||
				dstrRuleType == SETTLE_DAYS_EO ||
				dstrRuleType == SETTLE_DAYS_EI )
				{*/
				DString dstrSettleDays;

				double dOverrideAmt = DSTCommonFunctions::convertToDouble(strValue);
				int iOverrideAmt = (int)dOverrideAmt;

				if ( iOverrideAmt < 0 ) iOverrideAmt *= -1;

				char szNumBuffer[200];

				sprintf( szNumBuffer,"%d",iOverrideAmt );

				dstrSettleDays = szNumBuffer;
				pCBO->setField( ifds::SettleDays, dstrSettleDays, idDataGroup, false, false, false );
				//}
			}
			else if ( idField == IsSettlementRulePendingTrade )
			{
				DString dstrRuleType,dstrFundCode,dstrClassCode;

				pCBO->getField(ifds::RuleType,dstrRuleType,idDataGroup,false);
				pCBO->getField(ifds::FundCode,dstrFundCode,idDataGroup,false);
				pCBO->getField(ifds::ClassCode,dstrClassCode,idDataGroup,false);

				pCBO->validateTransTypePendingTrades(_accountNum, dstrRuleType, dstrFundCode, dstrClassCode, idDataGroup);	
			}
		}
    }

    return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool AcctLvlSttlmntRuleProcess::doOk( GenericInterface *rpGICaller )
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
    }

    return ( GETCURRENTHIGHESTSEVERITY() <= WARNING );
}

//******************************************************************************
SEVERITY AcctLvlSttlmntRuleProcess::performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, 
                                                   E_SEARCHACTION eSearchAction )
{
    MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("performSearch"));

    const BFDataGroupId& idDataGroup = getDataGroupId ();
    DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
    MgmtCo &pMgmtCo = dstcWorkSession->getMgmtCo();

    try
    {
        switch( eSearchAction )
        {
            case SEARCH_START:
            {
                if( idSearch == IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST )
                {
                    if (_pAcctLvlSttlmntRuleList != NULL )
                    {
                        delete _pAcctLvlSttlmntRuleList;
                        _pAcctLvlSttlmntRuleList = NULL;
                    }

                    setContainer(IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST, NULL);

                    MFAccount *pMFAccount = NULL;
                    dstcWorkSession->getMFAccount( idDataGroup, _accountNum, pMFAccount );

                    if( pMFAccount->getAcctSettlementRuleList( _pAcctLvlSttlmntRuleList, 
                                                               idDataGroup, 
                                                               !bfutil::isServerContext()) <= WARNING )
                    {
                        setContainer(IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST, _pAcctLvlSttlmntRuleList);
                    }
                }
            }
            break;
            case SEARCH_NEXT_BLOCK:
            {
                if( idSearch == IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST )
                {
                    _pAcctLvlSttlmntRuleList->getMore ();        
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
bool AcctLvlSttlmntRuleProcess::doMoreRecordsExist( GenericInterface *rpGICaller,
                                                    const BFContainerId& idSearch )
{
    if( idSearch == IFASTBP_PROC::ACCT_SETTLEMENT_RULE_LIST )
    {
        return ( rpGICaller == NULL || _pAcctLvlSttlmntRuleList == NULL) ? 
                 false : _pAcctLvlSttlmntRuleList->doMoreRecordsExist();      
    }

    return false;
}

//******************************************************************************
bool AcctLvlSttlmntRuleProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{
    MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doModelessSetFocus") );

    bool bRtn = false;
    try
    {
        assert( _rpChildGI );

        if( isValidModelessInterface( _rpChildGI ) )
        {
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
SEVERITY AcctLvlSttlmntRuleProcess::doValidateAll( BFAbstractCBO *rpWSD,
                                                   const BFDataGroupId& idDataGroup )
{
    MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("doValidateAll"));

    if ( _pAcctLvlSttlmntRuleList )
         _pAcctLvlSttlmntRuleList->validateAll (idDataGroup);
         
    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AcctSettlementRuleProcess.cpp-arc  $
// 
//    Rev 1.1   Apr 16 2008 18:26:12   daechach
// PET2385 FN02&07 - Modified code regarding code review.
*
*/
