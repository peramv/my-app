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
//    Copyright 1997 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : CancellationInstrProcess.cpp
// ^AUTHOR :  
// ^DATE   : 10/31/2005
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : CancellationInstrProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"

#include "CancellationInstrProcess.hpp"
#include "CancellationInstrProcessincludes.h"
#include "confirmationprocessincludes.h"
#include <ifastcbo\TransCancellist.hpp>
#include <ifastcbo\CancelInstrSearchCriteria.hpp>

#include <ifastdataimpl\dse_dstc0337_vw.hpp>
#include <ifastdataimpl\dse_dstc0337_vw.hpp>
#include <ifastdataimpl\dse_dstc0337_vwRepeat_Record.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_CANCELLATION_INSTR;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_CANCELLATION_INSTR;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< CancellationInstrProcess > processCreator( CMD_BPROC_CANCELLATION_INSTR );


namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "CancellationInstrProcess" );

   const I_CHAR *Y = I_( "Y" );
   const I_CHAR *N = I_( "N" );
   
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId CancSearchType;
   extern CLASS_IMPORT const BFTextFieldId SearchUsing;
}

namespace CANCEL_INSTR
{
   const I_CHAR * const SEARCH_TYPE  = I_("SearchType");
   const I_CHAR * const TRANS_STATUS = I_("TransStat"); 
   const I_CHAR * const ADJUST_TYPE  = I_("AdjustType");
}


namespace UAF
{   
}

namespace MFCAN_IP_PARAM
{
   extern const I_CHAR * const CALLER;
}

extern CLASS_IMPORT BF_OBJ_TYPE OBJ_TYPE_TRANS_CANCEL;
extern CLASS_IMPORT BF_OBJ_TYPE OBJ_TYPE_BULK_CANCEL;


//******************************************************************************
//              Public Methods
//******************************************************************************
CancellationInstrProcess::CancellationInstrProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pTransCancellist( NULL )
, _pCancelInstrSearchCriteria( NULL )
, _rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::CRITERIA,                false, BF::NullContainerId,    true,  I_("Criteria") );
   addContainer( IFASTBP_PROC::CANCELLATION_INSTR_LIST, true,  IFASTBP_PROC::CRITERIA, false, I_("CancelInstrList") );      
	
// from list vw 337
   addFieldDetails( ifds::CancSearchType,   IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::SearchUsing,		IFASTBP_PROC::CRITERIA );

   addFieldDetails( ifds::CancellationType, IFASTBP_PROC::CANCELLATION_INSTR_LIST );
   addFieldDetails( ifds::TransNum,		    IFASTBP_PROC::CANCELLATION_INSTR_LIST );
   addFieldDetails( ifds::TransType,	    IFASTBP_PROC::CANCELLATION_INSTR_LIST );
   addFieldDetails( ifds::TradeDate,	    IFASTBP_PROC::CANCELLATION_INSTR_LIST );
   addFieldDetails( ifds::Fund,		        IFASTBP_PROC::CANCELLATION_INSTR_LIST );
   addFieldDetails( ifds::Class,		    IFASTBP_PROC::CANCELLATION_INSTR_LIST );
   addFieldDetails( ifds::FundISIN,		    IFASTBP_PROC::CANCELLATION_INSTR_LIST );
   addFieldDetails( ifds::FundWKN,		    IFASTBP_PROC::CANCELLATION_INSTR_LIST );
   addFieldDetails( ifds::TranStatus,	    IFASTBP_PROC::CANCELLATION_INSTR_LIST );
   addFieldDetails( ifds::VerifyDate,	    IFASTBP_PROC::CANCELLATION_INSTR_LIST );
   addFieldDetails( ifds::VerifiedBy,	    IFASTBP_PROC::CANCELLATION_INSTR_LIST );
   addFieldDetails( ifds::TradeAdjustID,    IFASTBP_PROC::CANCELLATION_INSTR_LIST );

   addFieldDetails( ifds::Username,		    IFASTBP_PROC::CANCELLATION_INSTR_LIST );
   addFieldDetails( ifds::ModUser,			IFASTBP_PROC::CANCELLATION_INSTR_LIST );
   addFieldDetails( ifds::ModDate,			IFASTBP_PROC::CANCELLATION_INSTR_LIST );
   addFieldDetails( ifds::ProcessDate,	    IFASTBP_PROC::CANCELLATION_INSTR_LIST );
}

//******************************************************************************
CancellationInstrProcess::~CancellationInstrProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   _rpChildGI = NULL;
}


//******************************************************************************
void CancellationInstrProcess::doGetField(
                                    const GenericInterface *rpGICaller,
                                    const BFContainerId& idContainer,
                                    const BFFieldId& idField,
                                    const BFDataGroupId& idDataGroup,
                                    DString &strValueOut,
                                    bool bFormatted ) const
{  

}

//******************************************************************************
SEVERITY CancellationInstrProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   
   processParameters();
	
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool CancellationInstrProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_CANCELLATION_INSTR );
}

//******************************************************************************
bool CancellationInstrProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   bool bRtn = false;  

   processParameters();
   
   if( isValidModelessInterface( _rpChildGI ) )
   {  // Only if child still exists
		setContainer (IFASTBP_PROC::CANCELLATION_INSTR_LIST, NULL);

      bRtn = _rpChildGI->refresh( this, I_("ReloadParams" ) );
      bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
		
   }

   return(bRtn);
}

//******************************************************************************
E_COMMANDRETURN CancellationInstrProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {     
      rtn = invokeCommand( this, 
		                   CMD_GUI_CANCELLATION_INSTR, 
						   PROC_NO_TYPE, 
						   isModal(),
                           &_rpChildGI );
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      throw EXCEPTIONFROMFILE(// CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
                              CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(rtn);
}

//******************************************************************************
SEVERITY CancellationInstrProcess::doSetField(
                                        const GenericInterface *rpGICaller,
                                        const BFContainerId& idContainer,
                                        const BFFieldId& idField,
                                        const BFDataGroupId& idDataGroup,
                                        const DString& strValue,
                                        bool bFormatted
                                        )
{  

   return(NO_CONDITION);
}

//******************************************************************************
void *CancellationInstrProcess::getPtrForContainer( const BFContainerId& idContainer, 
												    const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_("getPtrForContainer") );
    
	void *ptr = NULL;
    SEVERITY sevRtn = NO_CONDITION;
    DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
    try
    {
	  if (IFASTBP_PROC::CRITERIA == idContainer)
      {
         _pCancelInstrSearchCriteria = NULL;

         if (dstcWorkSession->getCancelInstrSearchCriteria (_pCancelInstrSearchCriteria) <= WARNING)
         {
            ptr = _pCancelInstrSearchCriteria;
         }
      }
	  else if( IFASTBP_PROC::CANCELLATION_INSTR_LIST == idContainer )
      {
			_pTransCancellist = NULL;
			DString strTransNum		 = NULL_STRING;
			DString cashDivPaidAfter = NULL_STRING;
			DString strTradeDate     = NULL_STRING;
			DString strFundCode      = NULL_STRING;
			DString strClassCode     = NULL_STRING;


		
			sevRtn = dstcWorkSession->getTransCancellist( _pTransCancellist, 
														  strTransNum, 
														  NULL_STRING, 
														  getDataGroupId(),
														  strTradeDate, 
														  strFundCode,
														  strClassCode,
														  m_dstrSearchType,
														  m_dstrTranStatus, 
														  m_dstrAdjustType );

			if ( sevRtn  <= WARNING && NULL != _pTransCancellist )
				ptr = _pTransCancellist;
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
SEVERITY CancellationInstrProcess::processParameters()
{

	MAKEFRAMEAUTOPROMOTE2(CND::IFASTBP_CONDITION, CLASSNAME, I_("processParameters"));

	getParameter( CANCEL_INSTR::SEARCH_TYPE,  m_dstrSearchType);
    getParameter( CANCEL_INSTR::TRANS_STATUS, m_dstrTranStatus);
	getParameter( CANCEL_INSTR::ADJUST_TYPE,  m_dstrAdjustType);

	return GETCURRENTHIGHESTSEVERITY();

}

//******************************************************************************

SEVERITY CancellationInstrProcess::performSearch( GenericInterface *rpGICaller, 
											      const BFContainerId& idSearch, 
												  E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_("performSearch"));

   const BFDataGroupId& idDataGroup = getDataGroupId ();
   try
   {
      switch (eSearchAction)
      {        
			case SEARCH_START:
				{
					if (idSearch == IFASTBP_PROC::CANCELLATION_INSTR_LIST)
					{
						processParameters();
                        _pTransCancellist = NULL;
					}

                    setContainer (idSearch, NULL);
				}
				break;
         case SEARCH_NEXT_BLOCK:
            {
               if (idSearch == IFASTBP_PROC::CANCELLATION_INSTR_LIST)
               {
				  processParameters();
                  if (_pTransCancellist)
                     _pTransCancellist->getMore ();
               }
            }
            break;
         default:
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
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, I_("PerformSearch"), CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool CancellationInstrProcess::doMoreRecordsExist( GenericInterface *rpGICaller,
                                                   const BFContainerId& idSearch )
{
   if (!rpGICaller)
      return(false);

   if (IFASTBP_PROC::CANCELLATION_INSTR_LIST == idSearch)
   {
      return _pTransCancellist == NULL ? false : _pTransCancellist->doMoreRecordsExist();
   }
  
   return false;
}

//******************************************************************************
bool CancellationInstrProcess::doOk(GenericInterface *rpGICaller)
{   

   setParameter( TRANSCANCEL::BULK_CANCEL,    I_( "Y" ) );
   setParameter( TRANSCANCEL::DISPLAY_REBOOK, I_( "N" ) );

   return true;
}

//******************************************************************************
bool CancellationInstrProcess::doSend ( GenericInterface* rpGICaller, 
	                                 const I_CHAR * szMessage
                                 )
{
    MAKEFRAME2 (CND::BPBASE_CONDITION, CLASSNAME, I_("doSend"));

    try
    {		
        if ( DString (szMessage) == I_( "ClearUpdatedFields" ) )
		{			
            _pCancelInstrSearchCriteria->clearUpdatedFlags( getDataGroupId() );
    
		}
        else if ( DString (szMessage) == I_("RefreshCancelData") )
		{				
			DSTCWorkSession* pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
			if ( NULL != pDSTCWorkSession )
			{				
				BFObjIter bfIter( *pDSTCWorkSession, 
                                  getDataGroupId(), 
                                  true,
                                  BFObjIter::ITERTYPE::NON_DELETED );				
                bfIter.begin();
				
				while( !bfIter.end() )
				{							
					const BFObjectKey &pKey = bfIter.getKey();

					//if it is bulk cancellation list, delete it, on refresh
					if (pKey.getType() == OBJ_TYPE_BULK_CANCEL)
					{
						bfIter.removeObjectFromMap (true);
		 				continue;
					}
					//if it is trans cancellation list, delete it, on refresh
					if (pKey.getType() == OBJ_TYPE_TRANS_CANCEL)
					{
						bfIter.removeObjectFromMap (true);
						continue;
					}					

					++bfIter;
				}
			}
		}            
    }
    catch (ConditionException &ce)
    {
        assert( 0 );
        SETCONDITIONFROMEXCEPTION( ce );
    }
    catch ( ... )
    {
        assert( 0 );
        THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS, CND::BP_ERR_UNKNOWN_EXCEPTION );
    }
	
	 return GETCURRENTHIGHESTSEVERITY() <= WARNING;
}

//*
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/CancellationInstrProcess.cpp-arc  $
// 
//    Rev 1.6   Dec 29 2005 13:16:40   porteanm
// Incident 501804 - Allow multiple Bulk Cancellation Instructions for the same Trade Date/Fund/Class.
// 
//    Rev 1.5   Nov 30 2005 13:13:02   porteanm
// PET1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.4   Nov 28 2005 10:33:12   porteanm
// PET1286 FN01 - Bulk Cancellation - Rebook always No on Confirmation
// 
//    Rev 1.3   Nov 24 2005 16:19:20   porteanm
// PET1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.2   Nov 11 2005 16:56:04   ZHANGCEL
// PET 1286 FN01 - Make it works properly for Cancellation Instruction
// 
//    Rev 1.1   Nov 09 2005 11:57:38   porteanm
// PET 1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.0   Nov 04 2005 11:39:52   ZHANGCEL
// Initial revision.
 */
