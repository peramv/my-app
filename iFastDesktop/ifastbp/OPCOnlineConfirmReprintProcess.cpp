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
// ^CLASS    : OPCOnlineConfirmReprintProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"

#include "mfcaninterprocparam.hpp"
#include "OPCOnlineConfirmReprintProcess.hpp"
#include "OPCConfirmReprintProcessincludes.h"


#include <ifastcbo\shareholder.hpp>
#include <ifastcbo\OPCOnlineConfirmReprint.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_OPC_ONLINE_CONFIRM_REPRINT;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_OPC_ONLINE_CONFIRM_REPRINT;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< OPCOnlineConfirmReprintProcess > processCreator( CMD_BPROC_OPC_ONLINE_CONFIRM_REPRINT );

namespace 
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_("OPCOnlineConfirmReprintProcess");
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
OPCOnlineConfirmReprintProcess::OPCOnlineConfirmReprintProcess( GenericInterfaceContainer* pGIC, 
 										  		                GenericInterface* pGIParent, 
													            const Command& rCommand )
: OPCConfirmReprintProcess(pGIC, pGIParent, rCommand),
_rpChildGI(NULL)
, _pOPCOnlineConfirmReprint( NULL )
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   
    addContainer( IFASTBP_PROC::OPC_ONLINE_CONFIRM_REPRINT, true,  BF::NullContainerId, true, I_("OPCOnlineConfirmReprint"));	
   
	/*
	addFieldDetails(ifds::, IFASTBP_PROC::OPC_ONLINE_CONFIRM_REPRINT );			
	*/
}

//******************************************************************************
OPCOnlineConfirmReprintProcess::~OPCOnlineConfirmReprintProcess()
{
   TRACE_DESTRUCTOR(CLASSNAME);
   _rpChildGI = NULL;   
}

//************************************************************************************
SEVERITY OPCOnlineConfirmReprintProcess::doInit()
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
E_COMMANDRETURN OPCOnlineConfirmReprintProcess::doProcess()
{  
   MAKEFRAME2(CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS);
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter( OPC_ONLINE_CONFIRM_REPRINT::TRANSID, _dstrTransId );
	  setParameter( OPC_ONLINE_CONFIRM_REPRINT::FUND,    _dstrFund );		            
	  setParameter( OPC_ONLINE_CONFIRM_REPRINT::FUND,    _dstrClass );		            

      rtn = invokeCommand( this, 
			               CMD_GUI_OPC_ONLINE_CONFIRM_REPRINT, 
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
SEVERITY OPCOnlineConfirmReprintProcess::doValidateAll(BFAbstractCBO *rpWSD,
   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("doValidateAll"));
	
   /*
   if( NULL != _pOPCOnlineConfirmReprint )
   {
      _pOPCOnlineConfirmReprint->validateAll( idDataGroup );
   }
   */

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool OPCOnlineConfirmReprintProcess::doModelessSetFocus(GenericInterface *rpGICaller)
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
            			
			setParameter( OPC_ONLINE_CONFIRM_REPRINT::TRANSID, _dstrTransId );
			setParameter( OPC_ONLINE_CONFIRM_REPRINT::FUND,     _dstrFund );
			setParameter( OPC_ONLINE_CONFIRM_REPRINT::CLASS,   _dstrClass );
				
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
bool OPCOnlineConfirmReprintProcess::doModelessChildComplete(const Command &cmd)
{
   // End when GUI ends
   return cmd.getKey() == CMD_GUI_OPC_ONLINE_CONFIRM_REPRINT;
}

//******************************************************************************
void *OPCOnlineConfirmReprintProcess::getPtrForContainer( const BFContainerId& idContainer,
																		    const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("getPtrForContainer"));
   
	void *ptr = NULL;
      
   try
   {      		
		if ( IFASTBP_PROC::OPC_ONLINE_CONFIRM_REPRINT == idContainer )
		{			
			/*
			DSTCWorkSession* pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

			if( !_dstrShareholder.strip().empty() &&
				 NULL != pDSTCWorkSession )
         {
				Shareholder *pShareholder = NULL;
				if( pDSTCWorkSession->getShareholder( idDataGroup, 
										 						  _dstrShareholder, 
																  pShareholder ) <= WARNING &&
					 NULL != pShareholder )
				{					
					if ( pShareholder->getOPCOnlineConfirmReprintDlgList( _pOPCOnlineConfirmReprintDlgList, 
						                                                I_( "" ), 
																						idDataGroup, 
																						true ) < WARNING &&
						  NULL != _pOPCOnlineConfirmReprintDlgList )
					{
						ptr = _pOPCOnlineConfirmReprint;
					}
				}
                     
         }
		 */
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
SEVERITY OPCOnlineConfirmReprintProcess::processParameters()
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTBP_CONDITION, CLASSNAME, I_("processParameters"));

   getParameter( OPC_ONLINE_CONFIRM_REPRINT::TRANSID, _dstrTransId );
   getParameter( OPC_ONLINE_CONFIRM_REPRINT::FUND,    _dstrFund );
   getParameter( OPC_ONLINE_CONFIRM_REPRINT::CLASS,   _dstrClass );

   _dstrTransId.stripAll();
   _dstrFund.stripAll();
   _dstrClass.stripAll();
	
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool OPCOnlineConfirmReprintProcess::doOk( GenericInterface *rpGICaller )
{	   
	/*
	DString dstrShrFundSponsorAgrmntFlag = I_( "N" );

   const BFDataGroupId& idDataGroup = getDataGroupId();
   DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

	Shareholder *pShareholder = NULL;
   if( NULL != pDSTCWorkSession &&
		 pDSTCWorkSession->getShareholder( idDataGroup, _dstrShareholder, pShareholder ) <= WARNING &&
		 NULL != pShareholder )
   {      
		if ( NULL != _pOPCOnlineConfirmReprintDlgList )
      {
         BFObjIter iter( *_pOPCOnlineConfirmReprintDlgList, 
				             idDataGroup, 
								 false, 
								 BFObjIter::ITERTYPE::NON_DELETED );

         while( !iter.end() )
         {
            if( !iter.isDummy() )
            {
               dstrShrFundSponsorAgrmntFlag = I_( "Y" );
               break;
            }
            ++iter;
         }
         
			pShareholder->setField( ifds::ShrFndSpAgrExists, dstrShrFundSponsorAgrmntFlag, idDataGroup, false );
      }
   }
   */
   
   return(true);
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/OPCOnlineConfirmReprintProcess.cpp-arc  $
// 
//    Rev 1.0   May 06 2005 12:34:28   porteanm
// Initial revision.
// 
//    Rev 1.0   May 05 2005 13:54:06   porteanm
// Initial revision.
// 
