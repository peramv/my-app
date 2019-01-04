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
//    DATE   : Jan 2004
//
//
//    Copyright 2004 by International Financial Data Services
//
//******************************************************************************
//
// ^CLASS    : DailyTransactionFeesProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "DailyTransactionFeesProcess.hpp"
#include "DailyTransactionFeesProcessincludes.h"
#include "mfcaninterprocparam.hpp"

#include <ifastcbo\DailyTransactionsFeeList.hpp>
#include <ifastcbo\DailyTransactionsFeesRepository.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_DAILY_TRANSACTION_FEES;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_DAILY_TRANSACTION_FEES;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< DailyTransactionFeesProcess > processCreator( CMD_BPROC_DAILY_TRANSACTION_FEES );

namespace 
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_("DailyTransactionFeesProcess");
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace AUDITTYPE
{
   extern CLASS_IMPORT I_CHAR * const DAILY_FEE;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
DailyTransactionFeesProcess::DailyTransactionFeesProcess(GenericInterfaceContainer* pGIC, 
   GenericInterface* pGIParent, const Command& rCommand)
: AbstractProcess(pGIC, pGIParent, rCommand),
_rpChildGI(NULL),
_pDailyTransactionsFeeList( NULL )
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   
   addContainer( IFASTBP_PROC::DAILY_TRANSACTION_FEES_LIST, true,  BF::NullContainerId, true, I_("DailyTransactionFeesList"));
   
	addFieldDetails(ifds::RecordType,    IFASTBP_PROC::DAILY_TRANSACTION_FEES_LIST );
	addFieldDetails(ifds::FeeCode,       IFASTBP_PROC::DAILY_TRANSACTION_FEES_LIST );
	addFieldDetails(ifds::FundCode,      IFASTBP_PROC::DAILY_TRANSACTION_FEES_LIST );
	addFieldDetails(ifds::ClassCode,     IFASTBP_PROC::DAILY_TRANSACTION_FEES_LIST );
	addFieldDetails(ifds::FundName,      IFASTBP_PROC::DAILY_TRANSACTION_FEES_LIST );
	addFieldDetails(ifds::EffectiveDate, IFASTBP_PROC::DAILY_TRANSACTION_FEES_LIST );
	addFieldDetails(ifds::StopDate,      IFASTBP_PROC::DAILY_TRANSACTION_FEES_LIST );
	addFieldDetails(ifds::FeeRate,       IFASTBP_PROC::DAILY_TRANSACTION_FEES_LIST );	
	addFieldDetails(ifds::FeeType,       IFASTBP_PROC::DAILY_TRANSACTION_FEES_LIST );	
    addFieldDetails(ifds::DailyFeeRid,   IFASTBP_PROC::DAILY_TRANSACTION_FEES_LIST);

	// Show Admin Dates support
	addFieldDetails(ifds::ModUser,       IFASTBP_PROC::DAILY_TRANSACTION_FEES_LIST );	
	addFieldDetails(ifds::ModDate,       IFASTBP_PROC::DAILY_TRANSACTION_FEES_LIST );	
	addFieldDetails(ifds::ProcessDate,   IFASTBP_PROC::DAILY_TRANSACTION_FEES_LIST );	
	addFieldDetails(ifds::Username,      IFASTBP_PROC::DAILY_TRANSACTION_FEES_LIST );		
}

//******************************************************************************
DailyTransactionFeesProcess::~DailyTransactionFeesProcess()
{
   TRACE_DESTRUCTOR(CLASSNAME);
   _rpChildGI = NULL;   
}

//************************************************************************************
SEVERITY DailyTransactionFeesProcess::doInit()
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
E_COMMANDRETURN DailyTransactionFeesProcess::doProcess()
{  
   MAKEFRAME2(CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS);
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter( I_( "RecordType" ),    _dstrDailyTransFeeRecordType );
		setParameter( I_( "FeeCode" ),       _dstrFeeCode );
		setParameter( I_( "FundCode" ),      _dstrFundCode );
		setParameter( I_( "ClassCode" ),     _dstrClassCode );
		setParameter( I_( "EffectiveDate" ), _dstrEffectiveDate );	
      
      rtn = invokeCommand( this, 
			                  CMD_GUI_DAILY_TRANSACTION_FEES, 
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
SEVERITY DailyTransactionFeesProcess::doValidateAll(BFAbstractCBO *rpWSD,
   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("doValidateAll"));
	
   if( NULL != _pDailyTransactionsFeeList )
   {
      _pDailyTransactionsFeeList->validateAll( idDataGroup );
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool DailyTransactionFeesProcess::doModelessSetFocus(GenericInterface *rpGICaller)
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS);

   bool bRtn = false;
   try
   {
      assert(_rpChildGI && isValidModelessInterface(_rpChildGI));
      if (processParameters() <= WARNING)
      {
         if (isValidModelessInterface(_rpChildGI))
         {  
				// Only if child still exists            
				setContainer( IFASTBP_PROC::DAILY_TRANSACTION_FEES_LIST, NULL );
            			
				setParameter( I_( "RecordType" ),    _dstrDailyTransFeeRecordType );
				setParameter( I_( "FeeCode" ),       _dstrFeeCode );
				setParameter( I_( "FundCode" ),      _dstrFundCode );
				setParameter( I_( "ClassCode" ),     _dstrClassCode );
				setParameter( I_( "EffectiveDate" ), _dstrEffectiveDate );

            bRtn = _rpChildGI->refresh(this, I_("ReloadParams"));
            bRtn = _rpChildGI->modelessSetFocus(rpGICaller);
         }
      }
   }
   catch(ConditionException &ce)
   {
      SETCONDITIONFROMEXCEPTION(ce);
   }
   catch(...)
   {
      assert(0);
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return bRtn;
}

//******************************************************************************
bool DailyTransactionFeesProcess::doModelessChildComplete(const Command &cmd)
{
   // End when GUI ends
   return cmd.getKey() == CMD_GUI_DAILY_TRANSACTION_FEES;
}

//******************************************************************************
SEVERITY DailyTransactionFeesProcess::performSearch(GenericInterface *rpGI, 
   const BFContainerId &idSearch, E_SEARCHACTION eSearchAction)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("performSearch"));

   try
   {
      if( _pDailyTransactionsFeeList != NULL )
      {
         _pDailyTransactionsFeeList->getMore();
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
bool DailyTransactionFeesProcess::doMoreRecordsExist( GenericInterface *rpGICaller,
																		const BFContainerId &idSearch )
{
   return (rpGICaller == NULL || _pDailyTransactionsFeeList == NULL) ? false : _pDailyTransactionsFeeList->doMoreRecordsExist();		
}

//******************************************************************************
void *DailyTransactionFeesProcess::getPtrForContainer( const BFContainerId& idContainer,
																		 const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("getPtrForContainer"));
   void *ptr = NULL;
   DSTCWorkSession* pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   DistributorRepository *pDistributorRepository = NULL;

   try
   {      
		DSTCWorkSession* pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
		DailyTransactionsFeesRepository *pDailyTransactionsFeesRepository = NULL;
		//bool bCreate /*= true*/)
		if ( NULL != pDSTCWorkSession &&
			  pDSTCWorkSession->getDailyTransactionsFeesRepository( pDailyTransactionsFeesRepository, 
			                                                        idDataGroup ) <= WARNING &&  			 
			  NULL != pDailyTransactionsFeesRepository )
		{
			// Anti Dilution Levy Fee
			if (IFASTBP_PROC::DAILY_TRANSACTION_FEES_LIST == idContainer)
         {
				// If RecordType, FeeCode, and Effective Date are not blank, 
				// then search type is by Effective Date
				if ( !_dstrDailyTransFeeRecordType.empty() &&
					  !_dstrFeeCode.empty() &&
					  !_dstrEffectiveDate.empty() )
				{
					if( pDailyTransactionsFeesRepository->getDailyTransactionsFeeList( _dstrDailyTransFeeRecordType,
																			 								 _dstrFeeCode,
																										    _dstrEffectiveDate,
																											 _pDailyTransactionsFeeList, 
																											 idDataGroup )  <= WARNING &&
                   NULL != _pDailyTransactionsFeeList )
					{
						ptr = _pDailyTransactionsFeeList;

					}
				}
				else // search is by Fund/Class, which can be blank, meaning ALL
				{
					if( pDailyTransactionsFeesRepository->getDailyTransactionsFeeList( _dstrDailyTransFeeRecordType,
																						 					 _dstrFeeCode,
																											 _dstrFundCode,
																											 _dstrClassCode,
																											 _pDailyTransactionsFeeList, 
																											 idDataGroup ) <= WARNING &&
						 NULL != _pDailyTransactionsFeeList )
					{
						ptr = _pDailyTransactionsFeeList;
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
SEVERITY DailyTransactionFeesProcess::processParameters()
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTBP_CONDITION, CLASSNAME, I_("processParameters"));

   getParameter( I_( "RecordType" ),    _dstrDailyTransFeeRecordType );
	getParameter( I_( "FeeCode" ),       _dstrFeeCode );
	getParameter( I_( "FundCode" ),      _dstrFundCode );
	getParameter( I_( "ClassCode" ),     _dstrClassCode );
	getParameter( I_( "EffectiveDate" ), _dstrEffectiveDate );	

	_dstrDailyTransFeeRecordType.stripAll();
	_dstrFeeCode.stripAll();
	_dstrFundCode.stripAll();
	_dstrClassCode.stripAll();
	_dstrEffectiveDate.stripAll();

   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY DailyTransactionFeesProcess::getHistoricalParameters( const BFContainerId& idContainer, 
                                                               BFFieldId &recordIdField, 
                                                               DString& tableId, 
                                                               DString& dstrKey) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS );

   if (idContainer == IFASTBP_PROC::DAILY_TRANSACTION_FEES_LIST)
   {
      recordIdField = ifds::DailyFeeRid;
      tableId = AUDITTYPE::DAILY_FEE;
      dstrKey = NULL_STRING;
   }
   else
   {
      assert(0);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DailyTransactionFeesProcess::getHistoricalParameters( const BFContainerId& idContainer, 
                                                               HISTORICAL_VECTOR &vectorHistorical)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);
   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/DailyTransactionFeesProcess.cpp-arc  $
// 
//    Rev 1.4   Jul 14 2010 13:31:48   jankovii
// PET0170770_FN01_Anti Dilution Levy
// 
//    Rev 1.3   Feb 12 2004 13:24:32   VADEANUM
// PET859 FN23 - ADL - replaced FeePercent with FeeRate for correct display mask.
// 
//    Rev 1.2   Feb 11 2004 11:19:30   VADEANUM
// PET859 FN23 - ADL - Admin Dates support.
// 
//    Rev 1.1   Feb 10 2004 16:31:54   VADEANUM
// PET 859 FN23 - ADL - first working version.
// 
//    Rev 1.0   Feb 03 2004 16:38:24   VADEANUM
// Initial revision.
// 
*/
