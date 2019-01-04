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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : FundGroupProcess.cpp
// ^AUTHOR : 
// ^DATE   : 04
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : FundGroupProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0229_vw.hpp>
#include "FundGroupProcess.hpp"
#include "FundGroupProcessincludes.h"
#include <ifastcbo\FundGroupSubList.hpp>
#include <ifastcbo\mgmtco.hpp>
#include "mfcaninterprocparam.hpp"
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_FUNDGROUP;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FUNDGROUP;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< FundGroupProcess > processCreator( CMD_BPROC_FUNDGROUP );

namespace
{
   const I_CHAR * CLASSNAME = I_( "FundGroupProcess" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern CLASS_IMPORT const long BP_ERR_INVALID_METHOD_CALL;
}

namespace ifds
{
  	extern CLASS_IMPORT const BFTextFieldId FundGroupDesc;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

FundGroupProcess::FundGroupProcess ( GenericInterfaceContainer* pGIC, 
   GenericInterface* pGIParent, const Command& rCommand)
: AbstractProcess( pGIC, pGIParent, rCommand )
, m_pFundGroupSubList( NULL )
, m_rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   addContainer( IFASTBP_PROC::FUNDGROUP_LIST, true );
   addFieldDetails( ifds::FundGroup, IFASTBP_PROC::FUNDGROUP_LIST );
   addFieldDetails( ifds::GroupName, IFASTBP_PROC::FUNDGROUP_LIST );
	addFieldDetails( ifds::FundGroupDesc, IFASTBP_PROC::FUNDGROUP_LIST );
}

//******************************************************************************

FundGroupProcess::~FundGroupProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY FundGroupProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;
   try
   {
		getParameter( MFCAN_IP_PARAM::SPONSOR_GROUP, m_dstrSponsorGroup);
      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      MgmtCo &mgmtCoOut = dstcWorkSession->getMgmtCo();
		if ( m_dstrSponsorGroup == I_("GROUP") )
		{
			sevRtn = mgmtCoOut.getFundGroupSubList( m_pFundGroupSubList, I_("BANK") );
			if( WARNING >= sevRtn )
			{
				setContainer( IFASTBP_PROC::FUNDGROUP_LIST, m_pFundGroupSubList );
			}
		}
		else if ( m_dstrSponsorGroup == I_("SPONSOR") )
		{
			sevRtn = mgmtCoOut.getFundSponsorsList( m_pFundSponsorsList );
			if( WARNING >= sevRtn )
			{
				setContainer( IFASTBP_PROC::FUNDGROUP_LIST, m_pFundSponsorsList );
			}
		}
		
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

E_COMMANDRETURN FundGroupProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
		setParameter( MFCAN_IP_PARAM::SPONSOR_GROUP, m_dstrSponsorGroup);
      rtn = invokeCommand( this, CMD_GUI_FUNDGROUP, getProcessType(), isModal(), &m_rpChildGI );
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

void FundGroupProcess::doPostOk( GenericInterface *rpGICaller, bool bSuccessFlag )
{
   if( bSuccessFlag )
   {
      DString dstrFundGroup;
      getField( rpGICaller, IFASTBP_PROC::FUNDGROUP_LIST, ifds::FundGroup, dstrFundGroup );
		if (  m_dstrSponsorGroup == I_("GROUP")  )
		{
			setParameter( I_("FUNDGROUP"), dstrFundGroup );
		}
		else if ( m_dstrSponsorGroup == I_("SPONSOR") )
		{
			setParameter( I_("FUNDSPONSOR"), dstrFundGroup );

		}
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/*
 */
