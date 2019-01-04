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
// ^CLASS    : ConfirmReprintProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"

#include "mfcaninterprocparam.hpp"
#include "ConfirmReprintProcess.hpp"
#include "ConfirmReprintProcessincludes.h"


#include <ifastcbo\shareholder.hpp>
#include <ifastcbo\ConfirmReprint.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_CONFIRM_REPRINT;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_CONFIRM_REPRINT;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< ConfirmReprintProcess > processCreator( CMD_BPROC_CONFIRM_REPRINT );

namespace 
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_("ConfirmReprintProcess");
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
ConfirmReprintProcess::ConfirmReprintProcess( GenericInterfaceContainer* pGIC, 
 										  	  GenericInterface* pGIParent, 
											  const Command& rCommand )
: AbstractProcess(pGIC, pGIParent, rCommand),
_rpChildGI(NULL)
, _pConfirmReprint( NULL )
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   
    addContainer( IFASTBP_PROC::CONFIRM_REPRINT, false,  BF::NullContainerId, true, I_("ConfirmReprint"));	
   
	/*
	addFieldDetails(ifds::, IFASTBP_PROC::OPC_ONLINE_CONFIRM_REPRINT );			
	*/
}

//******************************************************************************
ConfirmReprintProcess::~ConfirmReprintProcess()
{
   TRACE_DESTRUCTOR(CLASSNAME);
   _rpChildGI = NULL;   
}

//************************************************************************************
SEVERITY ConfirmReprintProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, DOINIT);

   try
   {
      processParameters();
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
E_COMMANDRETURN ConfirmReprintProcess::doProcess()
{  
   MAKEFRAME2(CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS);
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter( CONFIRM_REPRINT::TRANSID, _dstrTransId );
	  setParameter( CONFIRM_REPRINT::FUND,    _dstrFund );		            
	  setParameter( CONFIRM_REPRINT::FUND,    _dstrClass );		            

      rtn = invokeCommand( this, 
			               CMD_GUI_CONFIRM_REPRINT, 
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
SEVERITY ConfirmReprintProcess::doValidateAll(BFAbstractCBO *rpWSD,
   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("doValidateAll"));
	   
   if( NULL != _pConfirmReprint )
   {
      _pConfirmReprint->validateAll( idDataGroup );
   }   

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool ConfirmReprintProcess::doModelessSetFocus(GenericInterface *rpGICaller)
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
			setContainer( IFASTBP_PROC::CONFIRM_REPRINT, NULL );
            			
			setParameter( CONFIRM_REPRINT::TRANSID, _dstrTransId );
			setParameter( CONFIRM_REPRINT::FUND,     _dstrFund );
			setParameter( CONFIRM_REPRINT::CLASS,   _dstrClass );
				
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
bool ConfirmReprintProcess::doModelessChildComplete(const Command &cmd)
{
   // End when GUI ends
   return cmd.getKey() == CMD_GUI_CONFIRM_REPRINT;
}

//******************************************************************************
void *ConfirmReprintProcess::getPtrForContainer( const BFContainerId& idContainer,
																		    const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("getPtrForContainer"));
   
	void *ptr = NULL;
      
   try
   {      		
		if ( IFASTBP_PROC::CONFIRM_REPRINT == idContainer )
		{						
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
SEVERITY ConfirmReprintProcess::processParameters()
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTBP_CONDITION, CLASSNAME, I_("processParameters"));

   getParameter( CONFIRM_REPRINT::TRANSID, _dstrTransId );
   getParameter( CONFIRM_REPRINT::FUND,    _dstrFund );
   getParameter( CONFIRM_REPRINT::CLASS,   _dstrClass );

   _dstrTransId.stripAll();
   _dstrFund.stripAll();
   _dstrClass.stripAll();
	
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool ConfirmReprintProcess::setCommitDataGroupAsHost()
{
   return(true);
}

//************************************************************************************
bool ConfirmReprintProcess::doSend( GenericInterface *rpGICaller,
                                    const I_CHAR *szMessage )
{
   TRACE_METHOD( CLASSNAME, DOSEND );
   DString str( szMessage );
   
   if( str == I_("Reset") )
   {
		_pConfirmReprint->reprintReset( getDataGroupId() );	
   }
	
   return(true);
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/ConfirmReprintProcess.cpp-arc  $
// 
//    Rev 1.3   May 31 2005 15:59:12   porteanm
// PET OPC Confirm Reprint - Commit and Reset.
// 
//    Rev 1.2   May 26 2005 09:42:16   porteanm
// PET OPC Confirm Reprint - Cleanup.
// 
//    Rev 1.1   May 25 2005 14:58:58   porteanm
// PET OPC Confirm Reprint - Commit and Reset.
// 
//    Rev 1.0   May 24 2005 12:45:52   porteanm
// Initial revision.
// 
