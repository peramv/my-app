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
// ^FILE   : ManagementCompanyProcess.cpp
// ^AUTHOR : Jerry Leenerts
// ^DATE   : 02/09/1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : ManagementCompanyProcess
//    This class manages the management company and profile selection.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "managementcompanyprocess.hpp"
#include <ifastcbo\managementcompanieslist.hpp>
#include "usersessionprocess.hpp"
#include "usersessionprocessincludes.h"
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_MANAGEMENT_COMPANY;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_MANAGEMENT_COMPANY;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< ManagementCompanyProcess > processCreator( CMD_BPROC_MANAGEMENT_COMPANY );

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "ManagementCompanyProcess" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319ManagementCompanyProcess::ManagementCompanyProcess() : 
ManagementCompanyProcess::ManagementCompanyProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pMgmtCompaniesList( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::MGMT_COMPANIES_LIST, true );
   addFieldDetails( ifds::CompanyId, IFASTBP_PROC::MGMT_COMPANIES_LIST );
   addFieldDetails( ifds::ClientID, IFASTBP_PROC::MGMT_COMPANIES_LIST );
   addFieldDetails( ifds::CompanyName, IFASTBP_PROC::MGMT_COMPANIES_LIST );
   addFieldDetails( SYSTMGMTS, BF::NullContainerId, RELAY_TO_PARENT, I_( "CurrentCompanyId" ) );
   addFieldDetails( CLIENTID, BF::NullContainerId, RELAY_TO_PARENT, I_( "CurrentClientId" ) );
   addFieldDetails( MGMTCONAME, BF::NullContainerId, RELAY_TO_PARENT, I_( "MgmtCoName" ) );
   addFieldDetails( ACCESSALLSLSREP, BF::NullContainerId, RELAY_TO_PARENT, I_( "AccessAllSlsRep" ) );
   addFieldDetails( AWDPROFILE, BF::NullContainerId, RELAY_TO_PARENT, I_( "AwdProfile" ) );
   addFieldDetails( CHANGE_AWDPROFILE, BF::NullContainerId, RELAY_TO_PARENT, I_( "ChangeAwdProfile" ) );



}

//******************************************************************************

ManagementCompanyProcess::~ManagementCompanyProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   delete _pMgmtCompaniesList;
   _pMgmtCompaniesList = NULL;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY ManagementCompanyProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

   try
   {
      _pMgmtCompaniesList = new ManagementCompaniesList( getBFSession()->getUserSession() );
      if( _pMgmtCompaniesList->init() <= WARNING )
      {
         setContainer( IFASTBP_PROC::MGMT_COMPANIES_LIST, _pMgmtCompaniesList );
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY ManagementCompanyProcess::ok2( GenericInterface *rpGI )
{
	MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOOK );
	DString dstrChangeProfile;
	getField(this,CHANGE_AWDPROFILE,dstrChangeProfile,false);  
	try
	{
		if(dstrChangeProfile == USERSESSION::YES )
		{
			try
			{
				DSTCUserSession &session = dynamic_cast<DSTCUserSession& >(getBFSession()->getUserSession());

				session.fireFighterLogon(_dstCurrentCompanyId);
			}
			catch( ... )
			{
				// we catch the exception, ignore it and continue
			}

			getParent()->send( this, STARTSESSION );
		}
		dynamic_cast<DSTCGlobalSession& >(getBFSession()->getGlobalSession()).refreshMgmtCo( _dstCurrentCompanyId );
	}
	catch( ConditionException &ce )
	{
		SETCONDITIONFROMEXCEPTION( ce );
	}
	catch( ... )
	{
		assert( 0 );
		THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOOK,
			CND::BP_ERR_UNKNOWN_EXCEPTION );
	}
	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

E_COMMANDRETURN ManagementCompanyProcess::doProcess()
{  
   TRACE_METHOD( CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      rtn = invokeCommand( this, CMD_GUI_MANAGEMENT_COMPANY, getProcessType(), isModal(), NULL );
   }
   catch( ConditionException & )
   {
      throw;
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

void ManagementCompanyProcess::setCurrentListItem( const GenericInterface *rpGICaller, 
                                                   const BFContainerId& idList, const DString& strListItemKey )
{
   TRACE_METHOD( CLASSNAME, SETCURRENTLISTITEM );

   //call the parent AbstractProcess
   AbstractProcess::setCurrentListItem( rpGICaller, idList, strListItemKey );

   if( idList == IFASTBP_PROC::MGMT_COMPANIES_LIST )
   {
      setCurrentCompany(rpGICaller);
   }

}

//******************************************************************************

void ManagementCompanyProcess::setCurrentCompany(const GenericInterface *rpGICaller)
{
   getField( rpGICaller, IFASTBP_PROC::MGMT_COMPANIES_LIST,ifds::CompanyId, _dstCurrentCompanyId );
   _dstCurrentCompanyId.strip();

   setField( this, SYSTMGMTS, _dstCurrentCompanyId );
}

//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ManagementCompanyProcess.cpp-arc  $
 * 
 *    Rev 1.28   Jan 08 2010 11:55:30   yingz
 * delay view 276 for inc#1936007
 * 
 *    Rev 1.27   May 08 2004 13:28:00   YINGBAOL
 * PTS10029514:AWD Container disappears when Mgmt Co changed
 * 
 *    Rev 1.26   Mar 21 2003 17:44:40   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.25   Mar 07 2003 12:00:02   PURDYECH
 * MGMT_COMPANIES_LIST was changed from a BFFieldId to a const int.  The symbol is used as a idContainer, not a field.
 * 
 *    Rev 1.24   Oct 09 2002 23:53:28   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.23   Sep 30 2002 11:01:06   PURDYECH
 * BFFieldId no longer has operator long(), so explicit getId() calls are needed in places.
 * 
 *    Rev 1.22   Aug 29 2002 16:45:04   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.21   Aug 29 2002 12:54:30   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.20   22 May 2002 18:24:38   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.19   27 Mar 2002 19:55:18   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.18   Sep 20 2001 10:52:52   HUANGSHA
 * Added the ClientID in the list
 * 
 *    Rev 1.17   11 Jul 2001 10:47:40   SMITHDAV
 * Refresh management company on doOk.
 * 
 *    Rev 1.16   05 Jun 2001 13:13:22   HSUCHIN
 * minor clean up
 * 
 *    Rev 1.15   03 May 2001 14:05:34   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.14   15 Dec 2000 12:43:44   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.13   Nov 08 2000 15:18:48   HSUCHIN
 * removed assert (!getSession) since the Session may exist when change of management company is called
 * 
 *    Rev 1.12   Oct 20 2000 15:58:02   HUANGSHA
 * set the client in UserSessionDetail when the management company is changed
 * 
 *    Rev 1.11   Sep 15 2000 17:13:04   VASILEAD
 * Fixes for the new infra release
 * 
 *    Rev 1.10   Sep 14 2000 17:28:02   VASILEAD
 * Modified to accomodate the new infra from Sept 12
 * 
 *    Rev 1.9   Sep 06 2000 14:51:00   YINGBAOL
 * change sync.
 * 
 *    Rev 1.8   Aug 04 2000 14:04:04   YINGBAOL
 * put enquiry bank list at background
 * 
 *    Rev 1.7   Jul 27 2000 17:37:48   BUZILA
 * ClientLocale changes
 * 
 *    Rev 1.6   Jul 26 2000 11:45:50   VASILEAD
 * Added AccessAllSlsRep field in logon transaction
 * 
 *    Rev 1.5   May 08 2000 13:47:22   YINGBAOL
 * get current managementCompanyId from recent selection one instead of using first company... This is the cooment for fix bug
 * 
 *    Rev 1.4   May 08 2000 13:42:34   YINGBAOL
 * change comment according to Brian's requirement
 * 
 *    Rev 1.3   May 05 2000 16:49:22   YINGBAOL
 * fix bug
 * 
 *    Rev 1.2   Apr 20 2000 16:38:42   BUZILA
 * changed to MgmtCoId
 * 
 *    Rev 1.1   Apr 04 2000 17:10:44   DT24433
 * changed to use getGIContainer
 * 
 *    Rev 1.0   Feb 15 2000 10:59:36   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.11   Dec 13 1999 14:24:12   DT24433
 * changed to use send instead of refresh to usersession to start new session
 * 
 *    Rev 1.10   Nov 29 1999 14:03:16   POPESCUS
 * If the useraccess list comes with an error promote the condition already added into the condition frame; don't know if this screwed up refreshing the usersession process; I think we should deal with the error that came back from the useraccess list and then see if we can refresh the usp
 * 
 *    Rev 1.9   Oct 29 1999 10:48:20   DT24433
 * removed doCancel and changed doOk to ok2
 * 
 *    Rev 1.8   Oct 23 1999 15:39:54   HSUCHIN
 * doOk now issues a refresh request to UserSessionProcess to renew the master session hence closing or opening the awd container based on user input.
 * 
 *    Rev 1.7   Sep 16 1999 12:38:44   POPESCUS
 * Set the usersessionprocess as parent for the useraccessprocess
 * 
 *    Rev 1.6   Aug 25 1999 14:52:06   POPESCUS
 * Set the management company name field
 * 
 *    Rev 1.5   Aug 11 1999 13:34:22   POPESCUS
 * ?
 * 
 *    Rev 1.4   Aug 04 1999 12:29:26   DT24433
 * Updated for field details changes
 * 
 *    Rev 1.3   Jul 20 1999 11:14:10   VASILEAD
 * New conditions update
 * 
 *    Rev 1.2   Jul 19 1999 10:27:08   POPESCUS
 * Destroy useraccessprocess before invokeing it
 * 
 *    Rev 1.1   Jul 08 1999 10:02:08   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
