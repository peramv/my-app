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
//    AUTHOR : Monica Vadeanu
//    DATE   : June 2004
//
//
//    Copyright 2004 by International Financial Data Services
//
//******************************************************************************
//
// ^CLASS    : ShrFundBrokerProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"

#include "mfcaninterprocparam.hpp"
#include "ShrFundBrokerProcess.hpp"
#include "ShrFundBrokerProcessincludes.h"


#include <ifastcbo\shareholder.hpp>

#include <ifastcbo\ShrFundBrokerList.hpp>


extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_SHR_FUND_BROKER;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_SHR_FUND_BROKER;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< ShrFundBrokerProcess > processCreator( CMD_BPROC_SHR_FUND_BROKER );																							 

namespace 
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_("ShrFundBrokerProcess");
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
ShrFundBrokerProcess::ShrFundBrokerProcess( GenericInterfaceContainer* pGIC, 
														  GenericInterface* pGIParent, 
														  const Command& rCommand )
: AbstractProcess(pGIC, pGIParent, rCommand),
_rpChildGI(NULL),
_pShrFundBrokerList( NULL )
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   
   addContainer( IFASTBP_PROC::SHR_FUND_BROKER_LIST, true,  BF::NullContainerId, true, I_("ShrFundBrokerList"));	
   
	addFieldDetails(ifds::FundCode,       IFASTBP_PROC::SHR_FUND_BROKER_LIST );
	addFieldDetails(ifds::FundWKN,        IFASTBP_PROC::SHR_FUND_BROKER_LIST );
	addFieldDetails(ifds::FundISIN,       IFASTBP_PROC::SHR_FUND_BROKER_LIST );
	addFieldDetails(ifds::FundName,       IFASTBP_PROC::SHR_FUND_BROKER_LIST );
	addFieldDetails(ifds::FundBroker,     IFASTBP_PROC::SHR_FUND_BROKER_LIST );
	addFieldDetails(ifds::FundBrokerName, IFASTBP_PROC::SHR_FUND_BROKER_LIST );
		
	// Show Admin Dates support
	addFieldDetails(ifds::ProcessDate, IFASTBP_PROC::SHR_FUND_BROKER_LIST );	
	addFieldDetails(ifds::Username,    IFASTBP_PROC::SHR_FUND_BROKER_LIST );		
   // Not used for now as no modify is allowed...
   addFieldDetails(ifds::ModDate,     IFASTBP_PROC::SHR_FUND_BROKER_LIST );	
	addFieldDetails(ifds::ModUser,     IFASTBP_PROC::SHR_FUND_BROKER_LIST );		
}

//******************************************************************************
ShrFundBrokerProcess::~ShrFundBrokerProcess()
{
   TRACE_DESTRUCTOR(CLASSNAME);
   _rpChildGI = NULL;   
}

//************************************************************************************
SEVERITY ShrFundBrokerProcess::doInit()
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
E_COMMANDRETURN ShrFundBrokerProcess::doProcess()
{  
   MAKEFRAME2(CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS);
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter( SHR_FUND_BROKER::ACCOUNT_NUMBER,     _dstrAccount );
		setParameter( SHR_FUND_BROKER::SHAREHOLDER_NUMBER, _dstrShareholder );		            

      rtn = invokeCommand( this, 
			                  CMD_GUI_SHR_FUND_BROKER, 
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
SEVERITY ShrFundBrokerProcess::doValidateAll(BFAbstractCBO *rpWSD,
   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("doValidateAll"));
	
   if( NULL != _pShrFundBrokerList )
   {
      _pShrFundBrokerList->validateAll( idDataGroup );
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool ShrFundBrokerProcess::doModelessSetFocus(GenericInterface *rpGICaller)
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
				setContainer( IFASTBP_PROC::SHR_FUND_BROKER_LIST, NULL );
            			
				setParameter( SHR_FUND_BROKER::ACCOUNT_NUMBER,     _dstrAccount );
				setParameter( SHR_FUND_BROKER::SHAREHOLDER_NUMBER, _dstrShareholder );
				
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
bool ShrFundBrokerProcess::doModelessChildComplete(const Command &cmd)
{
   // End when GUI ends
   return cmd.getKey() == CMD_GUI_SHR_FUND_BROKER;
}

//******************************************************************************
SEVERITY ShrFundBrokerProcess::performSearch(GenericInterface *rpGI, 
   const BFContainerId &idSearch, E_SEARCHACTION eSearchAction)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("performSearch"));

   try
   {
      if( _pShrFundBrokerList != NULL )
      {
         _pShrFundBrokerList->getMore();
      }		
   }
   catch(ConditionException &ce)
   {
      SETCONDITIONFROMEXCEPTION(ce);
   }
   catch(...)
   {
      assert(0);
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, I_("performSearch"), CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool ShrFundBrokerProcess::doMoreRecordsExist( GenericInterface *rpGICaller,
															  const BFContainerId &idSearch )
{
   return (rpGICaller == NULL || _pShrFundBrokerList == NULL) ? false : _pShrFundBrokerList->doMoreRecordsExist();		
}

//******************************************************************************
void *ShrFundBrokerProcess::getPtrForContainer( const BFContainerId& idContainer,
																		    const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("getPtrForContainer"));
   
	void *ptr = NULL;
      
   try
   {      		
		if ( IFASTBP_PROC::SHR_FUND_BROKER_LIST == idContainer )
		{			
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
					if ( pShareholder->getShrFundBrokerList( _pShrFundBrokerList, 
						                                      I_( "" ),    // Fund -> All Funds
																		  I_( "" ),    // FundBroker -> All Fund Brokers
																		  idDataGroup ) < WARNING &&

						  NULL != _pShrFundBrokerList )
					{
						ptr = _pShrFundBrokerList;
					}					
				}
                     
         }
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
SEVERITY ShrFundBrokerProcess::processParameters()
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTBP_CONDITION, CLASSNAME, I_("processParameters"));

   getParameter( SHR_FUND_BROKER::ACCOUNT_NUMBER,     _dstrAccount );
	getParameter( SHR_FUND_BROKER::SHAREHOLDER_NUMBER, _dstrShareholder );
	
	_dstrAccount.stripAll();
	_dstrShareholder.stripAll();
	
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool ShrFundBrokerProcess::doOk( GenericInterface *rpGICaller )
{	   
	DString dstrShrFundBrokerFlag = I_( "N" );

   const BFDataGroupId& idDataGroup = getDataGroupId();
   DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

	Shareholder *pShareholder = NULL;
   if( NULL != pDSTCWorkSession &&
		 pDSTCWorkSession->getShareholder( idDataGroup, _dstrShareholder, pShareholder ) <= WARNING &&
		 NULL != pShareholder )
   {      
		if ( NULL != _pShrFundBrokerList )
      {
         BFObjIter iter( *_pShrFundBrokerList, 
				             idDataGroup, 
								 false, 
								 BFObjIter::ITERTYPE::NON_DELETED );

         while( !iter.end() )
         {
            if( !iter.isDummy() )
            {
               dstrShrFundBrokerFlag = I_( "Y" );
               break;
            }
            ++iter;
         }
         
			pShareholder->setField( ifds::ShrFndBrkExist, dstrShrFundBrokerFlag, idDataGroup, false );
      }
   }
   
   return(true);
}


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/ShrFundBrokerProcess.cpp-arc  $
// 
//    Rev 1.2   Nov 28 2004 14:08:20   vadeanum
// PET1117 FN08 - Shareholder Fund Broker support 
// 
//    Rev 1.1   Nov 11 2004 16:27:32   vadeanum
// PET1117 FN08 - Shareholder Fund Broker support.
// 
//    Rev 1.0   Nov 04 2004 10:33:58   VADEANUM
// Initial revision.
//

