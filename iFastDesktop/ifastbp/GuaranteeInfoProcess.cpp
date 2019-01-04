//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2005 by International Financial Data Services
//
//*****************************************************************************
//
// ^FILE   : GuaranteeInfoProcess.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 01/18/2000
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : GuaranteeInfoProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"

#include "guaranteeinfoprocess.hpp"
#include "guaranteeinfoprocessincludes.h"
#include "contractinfoprocessincludes.h"

#include <ifastcbo\contractinfolist.hpp>
#include <ifastcbo\guaranteedetaillist.hpp>
#include <ifastcbo\guaranteesummary.hpp>
#include <ifastcbo\guaranteesummarylist.hpp>
#include <ifastcbo\guaranteeinfo.hpp>
#include <ifastcbo\guaranteeinfolist.hpp>
#include <ifastcbo\mfaccount.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_GUARANTEEINFO;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_GUARANTEEINFO;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< GuaranteeInfoProcess > processCreator( CMD_BPROC_GUARANTEEINFO );

namespace 
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "GuaranteeInfoProcess" );
}


namespace GUARANTEE
{
   const I_CHAR * const ACCOUNT_NUMBER   = I_( "AccountNum" );
   const I_CHAR * const SHAREHOLD_NUMBER = I_( "ShareholderNum" );
   const I_CHAR * const KEY_PARAM        = I_("Key");   
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const SEG_FUND_MULTI_CONTRACT;
}

namespace ifds
{   
   extern CLASS_IMPORT const BFTextFieldId GuaranteeAcctListHeading;
   extern CLASS_IMPORT const BFTextFieldId InqPerm;    
}

//*
//******************************************************************************
//              Public Methods
//******************************************************************************
GuaranteeInfoProcess::GuaranteeInfoProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand ),
_rpChildGI( NULL ),
_pGuaranteeSummaryList( NULL ),
_pGuaranteeInfoList( NULL ),
_pGuaranteeDetailList( NULL ),
_pDummyGuaranteeInfoList (NULL),
_pDummyGuaranteeDetailList (NULL)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING );

   addSubstituteList( ifds::GuaranteeAcctListHeading );
   addSubstituteList( ifds::GuaranteeListHeading );
   addSubstituteList( ifds::GuarResetListHeading );
      
   addContainer( IFASTBP_PROC::GUARANTEE_SUMMARY_LIST, true, BF::NullContainerId,                  true, I_("ContractList") );  
   addContainer( IFASTBP_PROC::GUARANTEEINFO_LIST,     true, IFASTBP_PROC::GUARANTEE_SUMMARY_LIST, true, I_("TransactionsList") );
   addContainer( IFASTBP_PROC::GUARANTEE_DETAIL_LIST,  true, IFASTBP_PROC::GUARANTEEINFO_LIST,     true, I_("GuaranteeDetailsList") );         

   // Guaranteed account total - View 170, fixed part
   addFieldDetails( ifds::GuarAcctTotal,          IFASTBP_PROC::GUARANTEE_SUMMARY_LIST, SUBCLASS_PROCESS );
   // Account Guarantee Summary List 
   addFieldDetails( ifds::ContractType,           IFASTBP_PROC::GUARANTEE_SUMMARY_LIST );
   addFieldDetails( ifds::PolicyYear,             IFASTBP_PROC::GUARANTEE_SUMMARY_LIST );
   addFieldDetails( ifds::PolicyTerm,             IFASTBP_PROC::GUARANTEE_SUMMARY_LIST );
   addFieldDetails( ifds::EffectiveDate,          IFASTBP_PROC::GUARANTEE_SUMMARY_LIST );
   addFieldDetails( ifds::IssueDate,              IFASTBP_PROC::GUARANTEE_SUMMARY_LIST );
   addFieldDetails( ifds::GuarStatus,             IFASTBP_PROC::GUARANTEE_SUMMARY_LIST );
   addFieldDetails( ifds::MaturDate,              IFASTBP_PROC::GUARANTEE_SUMMARY_LIST );
   addFieldDetails( ifds::GuarSuspect,            IFASTBP_PROC::GUARANTEE_SUMMARY_LIST );
   addFieldDetails( ifds::RequiresGuarUnitAdjust, IFASTBP_PROC::GUARANTEE_SUMMARY_LIST );   
   addFieldDetails( ifds::SegGuarMatRecId,        IFASTBP_PROC::GUARANTEE_SUMMARY_LIST );   	
   
   // Contract Guarantee Total
   addFieldDetails( ifds::GuarContrTotal,         IFASTBP_PROC::GUARANTEE_SUMMARY_LIST ); 
      
   // Guarantee Info
   addFieldDetails( ifds::TransType,              IFASTBP_PROC::GUARANTEEINFO_LIST );
   addFieldDetails( ifds::TransactionId,          IFASTBP_PROC::GUARANTEEINFO_LIST );
   addFieldDetails( ifds::TradeDate,              IFASTBP_PROC::GUARANTEEINFO_LIST );
   addFieldDetails( ifds::FundCode,               IFASTBP_PROC::GUARANTEEINFO_LIST );
   addFieldDetails( ifds::ClassCode,              IFASTBP_PROC::GUARANTEEINFO_LIST );
   addFieldDetails( ifds::Baycom,                 IFASTBP_PROC::GUARANTEEINFO_LIST );
   addFieldDetails( ifds::AmountInUnit,           IFASTBP_PROC::GUARANTEEINFO_LIST );
   addFieldDetails( ifds::GuarAmount,             IFASTBP_PROC::GUARANTEEINFO_LIST );
   addFieldDetails( ifds::MaturityDate,           IFASTBP_PROC::GUARANTEEINFO_LIST );
   addFieldDetails( ifds::GuarAmtAtMatur,         IFASTBP_PROC::GUARANTEEINFO_LIST );
   addFieldDetails( ifds::SegGuarMatRecId,        IFASTBP_PROC::GUARANTEEINFO_LIST );       
   
   // Guarantee Details displayed based on Transaction Type    
   addFieldDetails( ifds::NAVBefRedPeriod,        IFASTBP_PROC::GUARANTEE_DETAIL_LIST );
   addFieldDetails( ifds::NAVBefRedAcct,          IFASTBP_PROC::GUARANTEE_DETAIL_LIST );
   addFieldDetails( ifds::RedAmountPeriod,        IFASTBP_PROC::GUARANTEE_DETAIL_LIST );
   addFieldDetails( ifds::RedAmountAcct,          IFASTBP_PROC::GUARANTEE_DETAIL_LIST );
   addFieldDetails( ifds::Percentage,             IFASTBP_PROC::GUARANTEE_DETAIL_LIST );
   addFieldDetails( ifds::NAVAftRedPeriod,        IFASTBP_PROC::GUARANTEE_DETAIL_LIST );
   addFieldDetails( ifds::NAVAftRedAcct,          IFASTBP_PROC::GUARANTEE_DETAIL_LIST );
   addFieldDetails( ifds::GuarBefRedPeriod,       IFASTBP_PROC::GUARANTEE_DETAIL_LIST );
   addFieldDetails( ifds::GuarBefRedAcct,         IFASTBP_PROC::GUARANTEE_DETAIL_LIST );
   addFieldDetails( ifds::GuarRedctnPeriod,       IFASTBP_PROC::GUARANTEE_DETAIL_LIST );
   addFieldDetails( ifds::GuarRedctnAct,          IFASTBP_PROC::GUARANTEE_DETAIL_LIST );
   addFieldDetails( ifds::GuarAftRedPeriod,       IFASTBP_PROC::GUARANTEE_DETAIL_LIST );
   addFieldDetails( ifds::GuarAftRedAcct,         IFASTBP_PROC::GUARANTEE_DETAIL_LIST );   
   addFieldDetails( ifds::ResetMaturDate,         IFASTBP_PROC::GUARANTEE_DETAIL_LIST );
   addFieldDetails( ifds::ResetNAV,               IFASTBP_PROC::GUARANTEE_DETAIL_LIST );
   addFieldDetails( ifds::PrevGuar,               IFASTBP_PROC::GUARANTEE_DETAIL_LIST );
   addFieldDetails( ifds::ResetGuarAmount,        IFASTBP_PROC::GUARANTEE_DETAIL_LIST );
   addFieldDetails( ifds::GuarTot,                IFASTBP_PROC::GUARANTEE_DETAIL_LIST );      
   addFieldDetails( ifds::ProcessDate,            IFASTBP_PROC::GUARANTEE_DETAIL_LIST );
}

//******************************************************************************
GuaranteeInfoProcess::~GuaranteeInfoProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   _rpChildGI = NULL;    
   if (_pDummyGuaranteeInfoList)
   {
      delete _pDummyGuaranteeInfoList;
      _pDummyGuaranteeInfoList = NULL;
   }
   if (_pDummyGuaranteeDetailList)
   {
      delete _pDummyGuaranteeDetailList;
      _pDummyGuaranteeDetailList = NULL;
   }
}

//******************************************************************************
//              Protected Methods
//******************************************************************************
SEVERITY GuaranteeInfoProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      getParameter( GUARANTEE::KEY_PARAM,        strKey);
      getParameter( GUARANTEE::SHAREHOLD_NUMBER, strShareholdNum);
      getParameter( GUARANTEE::ACCOUNT_NUMBER,   strAccountNum );
      strAccountNum.stripLeading(I_CHAR('0')).stripTrailing();

      DSTCWorkSession* pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
	  if ( NULL != pDSTCWorkSession )
	  {
		_pGuaranteeSummaryList = new GuaranteeSummaryList( *pDSTCWorkSession );
		if ( _pGuaranteeSummaryList->init( strAccountNum ) <= WARNING )
		{
			setContainer( IFASTBP_PROC::GUARANTEE_SUMMARY_LIST, _pGuaranteeSummaryList );
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
E_COMMANDRETURN GuaranteeInfoProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter( GUARANTEE::KEY_PARAM,        strKey);
      setParameter( GUARANTEE::SHAREHOLD_NUMBER, strShareholdNum );
      setParameter( GUARANTEE::ACCOUNT_NUMBER,   strAccountNum );      

      //bool bPermMultiContract= hasReadPermission( UAF::SEG_FUND_MULTI_CONTRACT );
      //if( bPermMultiContract )
      //{
         rtn = invokeCommand( this, CMD_GUI_GUARANTEEINFO, PROC_NO_TYPE, isModal(), &_rpChildGI );
      //}      
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
bool GuaranteeInfoProcess::doMoreRecordsExist( GenericInterface *rpGICaller,
                                               const BFContainerId& idContainer )
{
	if ( IFASTBP_PROC::GUARANTEEINFO_LIST == idContainer )
		return( _pGuaranteeInfoList->doMoreRecordsExist() );
	////else if ( IFASTBP_PROC::GUARANTEE_DETAIL_LIST == idContainer )
		////return( _pGuaranteeInfoList->doMoreRecordsExist() );
	else
		return false;	
}

//******************************************************************************
bool GuaranteeInfoProcess::doGetData( GenericInterface * ,
                                      BFData * ) const
{	
   _pGuaranteeInfoList->getMore();

   return(true);
}

//******************************************************************************
bool GuaranteeInfoProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.

   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
   SEVERITY sevRtn = SEVERE_ERROR, sevRtn1 = SEVERE_ERROR;

   bool bRtn = false;
   try
   {
      getParameter( GUARANTEE::KEY_PARAM,        strKey);
      getParameter( GUARANTEE::SHAREHOLD_NUMBER, strShareholdNum);
      getParameter( GUARANTEE::ACCOUNT_NUMBER,   strAccountNum );

      strAccountNum.stripLeading(I_CHAR('0')).stripTrailing();

      _pGuaranteeSummaryList= NULL ;	  

	  setContainer (IFASTBP_PROC::GUARANTEE_SUMMARY_LIST, NULL);
	  //setContainer (IFASTBP_PROC::GUARANTEEINFO_LIST, NULL);
	  //setContainer (IFASTBP_PROC::GUARANTEE_DETAIL_LIST, NULL);
      
      DSTCWorkSession* pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
	  if ( NULL != pDSTCWorkSession )
	  {
		_pGuaranteeSummaryList = new GuaranteeSummaryList( *pDSTCWorkSession );
		if ( _pGuaranteeSummaryList->init( strAccountNum ) <= WARNING )
		{
			setContainer( IFASTBP_PROC::GUARANTEE_SUMMARY_LIST, _pGuaranteeSummaryList );
		}	
	  }  
      
      setParameter( GUARANTEE::KEY_PARAM,        strKey);
      setParameter( GUARANTEE::SHAREHOLD_NUMBER, strShareholdNum);
      setParameter( GUARANTEE::ACCOUNT_NUMBER,   strAccountNum );

      if( !( bRtn = _rpChildGI->refresh( this, NULL ) ) )
      {
         return(bRtn);// false
      }

	  bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(bRtn);
}

//******************************************************************************
bool GuaranteeInfoProcess::doModelessChildComplete( const Command &cmd )
{
   /////bool bPermMultiContract= hasReadPermission( UAF::SEG_FUND_MULTI_CONTRACT );
   /////if( bPermMultiContract )
   /////{
      return( cmd.getKey() == CMD_GUI_GUARANTEEINFO );
   /////}
   
   // All done, ready to be self destructed
}

//******************************************************************************
bool GuaranteeInfoProcess::doRefresh( GenericInterface *rpGICaller, const I_CHAR *szOriginalCommand )
{
   TRACE_METHOD( CLASSNAME, DOREFRESH );

   setParameter( GUARANTEE::SHAREHOLD_NUMBER, strShareholdNum );
   setParameter( GUARANTEE::ACCOUNT_NUMBER,   strAccountNum );
   
   return(_rpChildGI->refresh( this, NULL )); 
}

//******************************************************************************
void *GuaranteeInfoProcess::getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           I_("getPtrForContainer"));

   void *ptr = NULL;
   DSTCWorkSession* pDSTCWorkSession = 
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   try
   {
      const BFDataGroupId &idDataGroup = getDataGroupId ();

	  if( IFASTBP_PROC::GUARANTEE_SUMMARY_LIST == idContainer )
      {          
         ptr = _pGuaranteeSummaryList;       
      }
	  else if( IFASTBP_PROC::GUARANTEEINFO_LIST == idContainer )
      {         
		 GuaranteeSummary *pGuaranteeSummary = dynamic_cast<GuaranteeSummary*>(getCBOItem ( IFASTBP_PROC::GUARANTEE_SUMMARY_LIST, idDataGroup));
		 if ( NULL != pGuaranteeSummary )
		 {			
			DString dstrContractType;
			pGuaranteeSummary->getField( ifds::ContractType, dstrContractType, idDataGroup );

			if ( !dstrContractType.empty())
         {
              if (_pGuaranteeSummaryList->getGuaranteeInfoListByContract( dstrContractType, 
				                                                              idDataGroup, 
															                            _pGuaranteeInfoList ) <= WARNING &&
			         NULL != _pGuaranteeInfoList )
			   {
				   ptr = _pGuaranteeInfoList;        	
			   }
         }
         else 
         {
            if (!_pDummyGuaranteeInfoList)
            {
               _pDummyGuaranteeInfoList = 
                  new GuaranteeInfoList (*pDSTCWorkSession);
            }
            ptr = _pDummyGuaranteeInfoList;
         }
		 }          
      }
      else if ( IFASTBP_PROC::GUARANTEE_DETAIL_LIST == idContainer )
      {         
		   if (_pGuaranteeInfoList)
         {
            GuaranteeInfo *pGuaranteeInfo = dynamic_cast<GuaranteeInfo*>(getCBOItem ( IFASTBP_PROC::GUARANTEEINFO_LIST, idDataGroup));
		      if (NULL != pGuaranteeInfo)
		      {			
			      if ( pGuaranteeInfo->getGuaranteeDetailList( idDataGroup,
							 				                          _pGuaranteeDetailList ) <= WARNING &&
			            NULL != _pGuaranteeDetailList )
			      {
				      ptr = _pGuaranteeDetailList;        	
			      }
		      }
         }
         else
         {
            if (!_pDummyGuaranteeDetailList)
            {
               _pDummyGuaranteeDetailList = 
                  new GuaranteeDetailList (*pDSTCWorkSession);
            }
            ptr = _pDummyGuaranteeDetailList;
         }
      }
	  else
      {
      }
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(ptr);
}

//******************************************************************************
void GuaranteeInfoProcess::doGetField ( const GenericInterface *rpGICaller,
                                        const BFContainerId &idContainer,
                                        const BFFieldId &idField,
                                        const BFDataGroupId &idDataGroup, 
                                        DString &strValueOut,
                                        bool bFormatted) const
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           I_("doGetField"));   

   strValueOut = NULL_STRING;

   if ( idField == ifds::GuarAcctTotal  )
   {
		GuaranteeSummaryList *pGuaranteeSummaryList = dynamic_cast <GuaranteeSummaryList*>(const_cast<GuaranteeInfoProcess*> (this)->getCBOList (IFASTBP_PROC::GUARANTEE_SUMMARY_LIST, idDataGroup));		

		if ( NULL != pGuaranteeSummaryList )
			pGuaranteeSummaryList->getField( ifds::GuarAcctTotal, strValueOut, idDataGroup );
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/GuaranteeInfoProcess.cpp-arc  $
 * 
 *    Rev 1.30   Jun 29 2006 17:32:52   popescu
 * Incident# 655992 - fixed crash in GuaranteeInfo screen when resizing
 * 
 *    Rev 1.29   Jun 28 2006 19:52:48   popescu
 * Incident# 655992 - fixed crash in GuaranteeInfo screen when resizing
 * 
 *    Rev 1.28   Jun 05 2006 16:55:02   porteanm
 * Incident 635750 - Crash when no record available.
 * 
 *    Rev 1.27   Aug 17 2005 16:58:30   porteanm
 * Incident 351033 - Details support.
 * 
 *    Rev 1.26   Jun 14 2005 15:31:36   porteanm
 * PET1024 FN40 - Guarantee Adjustments.
 * 
 *    Rev 1.25   Feb 27 2004 13:56:54   AGUILAAM
 * PET877_FN07: add new field GuarStatus to display description mapping for status per GuarStatusSet
 * 
 *    Rev 1.24   Feb 17 2004 15:25:26   AGUILAAM
 * PET877_FN07: changed Active to GuarActive to display Status correctly (previously, display is blank)
 * 
 *    Rev 1.23   Mar 21 2003 17:40:42   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.22   Oct 09 2002 23:53:16   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.21   Aug 29 2002 16:44:56   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.20   Aug 29 2002 12:54:22   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.19   22 May 2002 18:24:18   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.18   27 Mar 2002 19:54:54   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.17   Dec 13 2001 17:19:26   ZHANGCEL
 * Added setContainer for GUARANTEEINFO_LIST
 * 
 *    Rev 1.16   25 Oct 2001 14:02:46   SMITHDAV
 * hasPermission changes...
 * 
 *    Rev 1.15   Aug 23 2001 12:07:08   OLTEANCR
 * added fields: Active, MaturDate
 * 
 *    Rev 1.14   Aug 21 2001 16:52:22   OLTEANCR
 * set value for Guarantee Account Total
 * 
 *    Rev 1.13   Jul 30 2001 09:29:38   OLTEANCR
 * added new container GUARANTEE_SUMMARY & modif. logic
 * 
 *    Rev 1.12   Jul 17 2001 09:38:10   OLTEANCR
 * added logic for multicontracts
 * 
 *    Rev 1.11   Jun 07 2001 10:52:46   YINGBAOL
 * fix refresh issues
 * 
 *    Rev 1.10   14 May 2001 13:58:14   YINGZ
 * code sync up
 * 
 *    Rev 1.9   May 14 2001 10:54:24   OLTEANCR
 *  unchanged
 * 
 *    Rev 1.8   15 Dec 2000 12:43:30   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.7   Nov 30 2000 10:15:00   ZHANGCEL
 * added " const " for variables in the namespace and clean code up
 * 
 *    Rev 1.6   Oct 18 2000 10:58:28   KOVACSRO
 * Modified parameter name to make it work from NASU.
 * 
 *    Rev 1.5   Jul 28 2000 16:41:08   ZHANGCEL
 * Bug fixed
 * 
 *    Rev 1.4   Mar 17 2000 16:46:08   ZHANGCEL
 * Checked in for release
 * 
 *    Rev 1.3   Mar 15 2000 10:03:04   ZHANGCEL
 * Fix some bugs
 * 
 *    Rev 1.2   Mar 10 2000 12:57:08   ZHANGCEL
 * updated
// 
//    Rev 1.1   Mar 03 2000 15:49:34   ZHANGCEL
// Bug fixed
// 
//    Rev 1.0   Jan 28 2000 14:32:46   ZHANGCEL
// Initial revision.
 * 
 *
 */
