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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : KYCBrokerProcess.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : KYCBrokerProcess
//    This class manages the KYC Broker Info.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************
//ifastbp
#include "stdafx.h"
#include "KYCBrokerProcess.hpp"
#include "KYCBrokerProcessincludes.h"
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\BrokerList.hpp>
#include <ifastcbo\DSTCWorkSession.hpp>

#include <ifastdataimpl\dse_dstcglob_vw.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_KYC_BROKER;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_KYC_BROKER;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< KYCBrokerProcess > processCreator( CMD_BPROC_KYC_BROKER);

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "KYCBrokerProcess" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace
{
   const I_CHAR * const ACCOUNT_NUM = I_( "AccountNum" );
   const I_CHAR * const ENTITY_ID   = I_( "EntityId" );
   const I_CHAR * const CALLER      = I_( "Caller" );
   const I_CHAR * const ENTITY      = I_( "Entity" );
   const I_CHAR * const ACCTCOA     = I_( "AcctCOA" );
   const I_CHAR * const DEATHCLAIM  = I_( "1" );
   const I_CHAR * const ACCTREG     = I_( "0" );
   const I_CHAR * const REGSTANDARD = I_( "RegulatoryStandard" );
   const I_CHAR * const COMPLY_RULE = I_( "ComplyRule" );
}

namespace AUDITTYPE
{
   extern CLASS_IMPORT I_CHAR * const REGDOCUMENT;
}
//******************************************************************************
//              Public Methods
//******************************************************************************
KYCBrokerProcess::KYCBrokerProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL )
, m_strAcctNum(NULL_STRING)
{
	TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

	addContainer( IFASTBP_PROC::BROKER_LIST, true );

	addFieldDetails( ifds::BrokerCode,		IFASTBP_PROC::BROKER_LIST );
	addFieldDetails( ifds::BrokerName,		IFASTBP_PROC::BROKER_LIST );
	addFieldDetails( ifds::KYCRegulation,	IFASTBP_PROC::BROKER_LIST );
	addFieldDetails( ifds::AMLAgreement,		IFASTBP_PROC::BROKER_LIST );
	addFieldDetails( ifds::KYCSignture,		IFASTBP_PROC::BROKER_LIST );
	addFieldDetails( ifds::KYCStatus,		IFASTBP_PROC::BROKER_LIST );

}

//******************************************************************************
KYCBrokerProcess::~KYCBrokerProcess()
{
	TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

//******************************************************************************
SEVERITY KYCBrokerProcess::doInit()
{
	MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );


	SEVERITY sevRtn=NO_CONDITION;
	MFAccount * pMFAccount = NULL;
	BrokerList *pBrokerList = NULL;

	getParameter(ACCOUNT_NUM, m_strAcctNum );

	DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

	if( dstcWorkSession->getMFAccount( getDataGroupId(), m_strAcctNum, pMFAccount, I_("N"), NULL_STRING, true, true) 
       <= WARNING && pMFAccount )
	{
		if (pMFAccount)
		{
			DString dstrBrokerCode, dstrBrokerName;

			pMFAccount->getField(ifds::BrokerCode,	dstrBrokerCode, getDataGroupId(), false );
			pMFAccount->getField(ifds::BrokerName,	dstrBrokerName, getDataGroupId(), false );
			dstrBrokerCode.strip();

			pBrokerList = new BrokerList(*getBFWorkSession());
         
			if (pBrokerList->init(dstrBrokerCode, dstrBrokerName, I_("L")) <= WARNING && pBrokerList)
			{
				setContainer(IFASTBP_PROC::BROKER_LIST, pBrokerList);
			}
		}
	}

	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool KYCBrokerProcess::doModelessChildComplete( const Command &cmd )
{
	// End when GUI ends
	return( cmd.getKey() == CMD_GUI_KYC_BROKER);
}


//******************************************************************************
E_COMMANDRETURN KYCBrokerProcess::doProcess()
{  
	MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
	E_COMMANDRETURN rtn = CMD_FAILURE;

	try
	{
		rtn = invokeCommand( this, CMD_GUI_KYC_BROKER, getProcessType(), isModal(),
                           &_rpChildGI );
	}
	catch( ConditionException &ce )
	{
		assert( 0 );
		SETCONDITIONFROMEXCEPTION( ce );
	}
	catch( ... )
	{
		assert( 0 );
		THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
	}

	return(rtn);
}

//******************************************************************************

/* $Log::  
 */