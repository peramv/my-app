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
// ^FILE   : RESPInfoProcess.cpp
// ^AUTHOR : Dan Petolescu
// ^DATE   : 01/05/2000
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : RESPInfoProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "respinfoprocess.hpp"
#include "respinfoprocessincludes.h"
#include <ifastcbo\respinfo.hpp>
#include <ifastcbo\mfaccount.hpp>
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_RESPINFO;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_RESPINFO;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< RESPInfoProcess > processCreator( CMD_BPROC_RESPINFO );

namespace RESPINFONAMES
{
   const I_CHAR * const ACCOUNT_NUMBER_FIELD = I_( "AccountNum" );
   const I_CHAR * const SHAREHOLDER_FIELD = I_( "ShareholderNum" );
   const I_CHAR * const LAST_NAME_FIELD = I_( "LastName");
   const I_CHAR * const FIRST_NAME_FIELD = I_( "FirstName");
   const I_CHAR * const HISTORY_PENDING_FIELD = I_( "HistoryPending" );
   const I_CHAR * const HISTORY = I_( "H" );
   const I_CHAR * const PENDING = I_( "P" );
}

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "RESPInfoProcess" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

using namespace RESPINFONAMES;

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319RESPInfoProcess::RESPInfoProcess() : 
RESPInfoProcess::RESPInfoProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::RESPINFO_LIST, false );
   addContainer( IFASTBP_PROC::RESPINFOBENEFICIARY_LIST, true );

   addFieldDetails( ifds::TerminateDate, IFASTBP_PROC::RESPINFO_LIST );
   addFieldDetails( ifds::MaturityDate, IFASTBP_PROC::RESPINFO_LIST );
   addFieldDetails( ifds::ToDateContr, IFASTBP_PROC::RESPINFO_LIST );
   addFieldDetails( ifds::PlanNum, IFASTBP_PROC::RESPINFO_LIST );
   addFieldDetails( ifds::GrantRepayable, IFASTBP_PROC::RESPINFO_LIST );
   addFieldDetails( ifds::CESGEligible, IFASTBP_PROC::RESPINFO_LIST );
   addFieldDetails( ifds::TDRedEarning, IFASTBP_PROC::RESPINFO_LIST );
   addFieldDetails( ifds::GFathered, IFASTBP_PROC::RESPINFO_LIST );
   addFieldDetails( ifds::CurrEarning, IFASTBP_PROC::RESPINFO_LIST );
   addFieldDetails( ifds::RESPStatus, IFASTBP_PROC::RESPINFO_LIST );
   addFieldDetails( ifds::RESPStatDesc, IFASTBP_PROC::RESPINFO_LIST );
   addFieldDetails( ifds::RedLifeContr, IFASTBP_PROC::RESPINFO_LIST );
   addFieldDetails( ifds::RedUCAmt, IFASTBP_PROC::RESPINFO_LIST );
   addFieldDetails( ifds::RedACAmt, IFASTBP_PROC::RESPINFO_LIST );
   addFieldDetails( ifds::RedNetGrant, IFASTBP_PROC::RESPINFO_LIST );
   addFieldDetails( ifds::AcctLifeContr, IFASTBP_PROC::RESPINFO_LIST );
   addFieldDetails( ifds::AcctUCAmt, IFASTBP_PROC::RESPINFO_LIST );
   addFieldDetails( ifds::AcctACAmt, IFASTBP_PROC::RESPINFO_LIST );
   addFieldDetails( ifds::AcctNetGrant, IFASTBP_PROC::RESPINFO_LIST );
   addFieldDetails( ifds::AcctEAP, IFASTBP_PROC::RESPINFO_LIST );

   addFieldDetails( ifds::BeneName, IFASTBP_PROC::RESPINFOBENEFICIARY_LIST );
   addFieldDetails( ifds::YTDContr, IFASTBP_PROC::RESPINFOBENEFICIARY_LIST );
   addFieldDetails( ifds::LifeContr, IFASTBP_PROC::RESPINFOBENEFICIARY_LIST );
   addFieldDetails( ifds::UnAssisted, IFASTBP_PROC::RESPINFOBENEFICIARY_LIST );
   addFieldDetails( ifds::Assisted, IFASTBP_PROC::RESPINFOBENEFICIARY_LIST );
   addFieldDetails( ifds::NetGrant, IFASTBP_PROC::RESPINFOBENEFICIARY_LIST );
   addFieldDetails( ifds::EAPayment, IFASTBP_PROC::RESPINFOBENEFICIARY_LIST );
}

//******************************************************************************
RESPInfoProcess::~RESPInfoProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   _rpChildGI = NULL;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

bool RESPInfoProcess::doCancel( GenericInterface *rpGI )
{
   TRACE_METHOD( CLASSNAME, DOCANCEL );
   bool bRtn = true;

   return(bRtn); 
}


SEVERITY RESPInfoProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR, sevRtn1 = SEVERE_ERROR;

   try
   {
      getParent()->getParameter( ACCOUNT_NUMBER_FIELD, _strAccountNum );
      getParent()->getParameter( SHAREHOLDER_FIELD, _strShareholderNum );
      getParent()->getParameter( LAST_NAME_FIELD, _strLastName );
      getParent()->getParameter( FIRST_NAME_FIELD, _strFirstName );

      MFAccount* mfAccount;
      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      if( WARNING >= dstcWorkSession->getMFAccount( getDataGroupId(), _strAccountNum, mfAccount ) )
      {
         sevRtn = mfAccount->getRESPInfo( _pRESPInfo, getDataGroupId() );
         sevRtn1 = mfAccount->getRESPInfo( _pRESPInfoBeneficiaryList, getDataGroupId() );
         if( (WARNING >= sevRtn) && (WARNING >= sevRtn1) )
         {
            setContainer( IFASTBP_PROC::RESPINFO_LIST, _pRESPInfo );
            setContainer( IFASTBP_PROC::RESPINFOBENEFICIARY_LIST, _pRESPInfoBeneficiaryList );
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
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

bool RESPInfoProcess::doOk( GenericInterface *rpGI )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOOK );

   return(true);
}

//******************************************************************************

E_COMMANDRETURN RESPInfoProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter( ACCOUNT_NUMBER_FIELD, _strAccountNum );
      setParameter( SHAREHOLDER_FIELD, _strShareholderNum );
      setParameter( LAST_NAME_FIELD, _strLastName );
      setParameter( FIRST_NAME_FIELD, _strFirstName );

      rtn = invokeCommand( this, CMD_GUI_RESPINFO, PROC_NO_TYPE, isModal(), &_rpChildGI );
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

//******************************************************************************
bool RESPInfoProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.

   bool bRtn = false;
   if( _rpChildGI && isValidModelessInterface( _rpChildGI ) )
   {
      bRtn = _rpChildGI->refresh( this, NULL );
      bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
   }
   return(bRtn);
}
//******************************************************************************

bool RESPInfoProcess::doModelessChildComplete( const Command &cmd )
{
   DString dslCommandKey;
   dslCommandKey = cmd.getKey();
   if( dslCommandKey == CMD_GUI_RESPINFO )
      return(true);           // We do not want to be destroyed by a son process
   else
      return(false);          // All done, ready to be self destructed
}



//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/RESPInfoProcess.cpp-arc  $
 * 
 *    Rev 1.11   Mar 21 2003 17:47:16   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.10   Oct 09 2002 23:53:34   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.9   Aug 29 2002 16:45:12   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.8   22 May 2002 18:25:00   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.7   27 Mar 2002 19:55:36   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.6   Jun 07 2001 11:10:02   YINGBAOL
 * remove refresh
 * 
 *    Rev 1.5   15 May 2001 15:38:52   YINGZ
 * data group id clean up
 * 
 *    Rev 1.4   03 May 2001 14:05:38   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.3   15 Dec 2000 12:43:48   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.2   Mar 22 2000 09:48:16   PETOLESC
 * Small correction.
 * 
 *    Rev 1.1   Mar 22 2000 09:02:46   PETOLESC
 * Added Tax Rates and RESP dialogs.
 * 
 *    Rev 1.0   Feb 15 2000 10:59:36   SMITHDAV
 * Initial revision.
// 
//    Rev 1.0   Jan 17 2000 14:45:52   PETOLESC
// Initial revision.
 */ 
