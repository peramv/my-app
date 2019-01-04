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
//    AUTHOR : Monica Porteanu
//    DATE   : May 2005
//
//
//    Copyright 2005 by International Financial Data Services
//
//******************************************************************************
//
// ^CLASS    : OPCConfirmReprintProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"

#include "mfcaninterprocparam.hpp"
#include "OPCConfirmReprintProcess.hpp"
#include "ConfirmReprintProcessincludes.h"


#include <ifastcbo\shareholder.hpp>
#include <ifastcbo\OPCConfirmReprint.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_OPC_CONFIRM_REPRINT;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_OPC_CONFIRM_REPRINT;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< OPCConfirmReprintProcess > processCreator( CMD_BPROC_OPC_CONFIRM_REPRINT );

namespace 
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_("OPCConfirmReprintProcess");
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
OPCConfirmReprintProcess::OPCConfirmReprintProcess( GenericInterfaceContainer* pGIC, 
										  		    GenericInterface* pGIParent, 
													const Command& rCommand )
: ConfirmReprintProcess(pGIC, pGIParent, rCommand),
_rpChildGI(NULL)
, _pOPCConfirmReprint( NULL )
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   
                  // container ID                  , repeatable, parent container ID, updateable, name 
    addContainer( IFASTBP_PROC::OPC_CONFIRM_REPRINT, false,      BF::NullContainerId, true,       I_("OPCConfirmReprint"));	
   
	addFieldDetails(ifds::OPCConfirmReprint, IFASTBP_PROC::OPC_CONFIRM_REPRINT );
	addFieldDetails(ifds::ClientCopy,        IFASTBP_PROC::OPC_CONFIRM_REPRINT );
	addFieldDetails(ifds::BrokerCopy,        IFASTBP_PROC::OPC_CONFIRM_REPRINT );
	addFieldDetails(ifds::SalesRepCopy,      IFASTBP_PROC::OPC_CONFIRM_REPRINT );		
	addFieldDetails(ifds::SchedReprintDate,  IFASTBP_PROC::OPC_CONFIRM_REPRINT );	
	addFieldDetails(ifds::RequestedBy,       IFASTBP_PROC::OPC_CONFIRM_REPRINT );				
} 

//******************************************************************************
OPCConfirmReprintProcess::~OPCConfirmReprintProcess()
{
   TRACE_DESTRUCTOR(CLASSNAME);
   _rpChildGI = NULL;   
}

//************************************************************************************
SEVERITY OPCConfirmReprintProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, DOINIT);

   try
   {
      processParameters();

	  DSTCWorkSession* pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
	  if ( NULL != pDSTCWorkSession )
	  {
		 
		  if ( pDSTCWorkSession->getOPCConfirmReprint( _dstrTransId, 
			                                           _dstrAccountNum, 
													   _pOPCConfirmReprint, 
													   BF::HOST ) <= WARNING )													   
		  {				
			setContainer( IFASTBP_PROC::OPC_CONFIRM_REPRINT, _pOPCConfirmReprint );
		  }		                 
	  }
   }
   catch(ConditionException& ce)
   {
      SETCONDITIONFROMEXCEPTION(ce);
   }
   catch(...)
   {
      assert(0);
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
E_COMMANDRETURN OPCConfirmReprintProcess::doProcess()
{  
   MAKEFRAME2(CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS);
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter( CONFIRM_REPRINT::ACCOUNTNUM, _dstrAccountNum );
      setParameter( CONFIRM_REPRINT::TRANSID,    _dstrTransId );
	  setParameter( CONFIRM_REPRINT::FUND,       _dstrFund );		            
	  setParameter( CONFIRM_REPRINT::CLASS,      _dstrClass );		            

      rtn = invokeCommand( this, 
			               CMD_GUI_OPC_CONFIRM_REPRINT, 
                           PROC_NO_TYPE, 
						   isModal(), 
						   &_rpChildGI);
   }
   catch(ConditionException &ce)
   {
      assert(0);
      SETCONDITIONFROMEXCEPTION(ce);
   }
   catch(...)
   {
      assert(0);
      THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS, 
         CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return rtn;
}

//******************************************************************************
SEVERITY OPCConfirmReprintProcess::doValidateAll(BFAbstractCBO *rpWSD,
   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("doValidateAll"));
	
   if( NULL != _pOPCConfirmReprint )
   {
      _pOPCConfirmReprint->validateAll( idDataGroup );
   }   

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool OPCConfirmReprintProcess::doModelessSetFocus(GenericInterface *rpGICaller)
{  
	// This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS);

   bool bRtn = false;
   try
   {
      assert(_rpChildGI && isValidModelessInterface(_rpChildGI));
      if( processParameters() <= WARNING )
      {
         if( isValidModelessInterface( _rpChildGI ) )
         {  
			// Only if child still exists            
			setContainer( IFASTBP_PROC::OPC_CONFIRM_REPRINT, NULL );
            			
			setParameter( CONFIRM_REPRINT::ACCOUNTNUM, _dstrAccountNum );
			setParameter( CONFIRM_REPRINT::TRANSID,    _dstrTransId );
			setParameter( CONFIRM_REPRINT::FUND,       _dstrFund );
			setParameter( CONFIRM_REPRINT::CLASS,      _dstrClass );
				
            bRtn = _rpChildGI->refresh( this, I_("ReloadParams" ) );
            bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
         }
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch(...)
   {
      assert(0);
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return bRtn;
}

//******************************************************************************
bool OPCConfirmReprintProcess::doModelessChildComplete(const Command &cmd)
{
   // End when GUI ends
   return cmd.getKey() == CMD_GUI_OPC_CONFIRM_REPRINT;
}

//******************************************************************************
void *OPCConfirmReprintProcess::getPtrForContainer( const BFContainerId& idContainer,
																		    const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("getPtrForContainer"));
   
	void *ptr = NULL;
      
   try
   {      		
		if ( IFASTBP_PROC::OPC_CONFIRM_REPRINT == idContainer )
		{			
			ptr = _pOPCConfirmReprint;										
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

//******************************************************************************
SEVERITY OPCConfirmReprintProcess::processParameters()
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTBP_CONDITION, CLASSNAME, I_("processParameters"));

   getParameter( CONFIRM_REPRINT::ACCOUNTNUM, _dstrAccountNum );
   getParameter( CONFIRM_REPRINT::TRANSID,    _dstrTransId );
   getParameter( CONFIRM_REPRINT::FUND,       _dstrFund );
   getParameter( CONFIRM_REPRINT::CLASS,      _dstrClass );

   _dstrAccountNum.stripAll();
   _dstrTransId.stripAll();
   _dstrFund.stripAll();
   _dstrClass.stripAll();
	
   return GETCURRENTHIGHESTSEVERITY();
}

//************************************************************************************
bool OPCConfirmReprintProcess::doSend( GenericInterface *rpGICaller,
                                       const I_CHAR *szMessage )
{
   TRACE_METHOD( CLASSNAME, DOSEND );
   DString str( szMessage );
   
   if( str == I_("Reset") )
   {
		_pOPCConfirmReprint->reprintReset( getDataGroupId() );	
   }
	
   return(true);
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/OPCConfirmReprintProcess.cpp-arc  $
// 
//    Rev 1.5   May 31 2005 15:59:32   porteanm
// PET OPC Confirm Reprint - Commit and Reset.
// 
//    Rev 1.4   May 26 2005 09:42:56   porteanm
// PET OPC Confirm Reprint - Cleanup.
// 
//    Rev 1.3   May 25 2005 17:25:36   porteanm
// OPC Confirm Reprint - Title bar.
// 
//    Rev 1.2   May 25 2005 14:57:44   porteanm
// PET OPC Confirm Reprint - Reset.
// 
//    Rev 1.1   May 24 2005 12:50:46   porteanm
// PET OPC Confirm Reprint - Renamed OPC files. Changed class hierarchy.
// 
//    Rev 1.0   May 05 2005 13:54:06   porteanm
// Initial revision.
// 
