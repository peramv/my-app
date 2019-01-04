//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 by International Financial.
//
//******************************************************************************
//
// ^FILE   : ReportProcess.cpp
// ^AUTHOR : 
// ^DATE   : Nov 20, 2002
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : ReportProcess
//    This class manages the remarks information.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "reportprocess.hpp"
#include "reportprocessincludes.h"
#include <ifastcbo\ifastcommonreportcriteria.hpp>
#include <ifastcbo\ifastreportcriterialist.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\dstcworksession.hpp>

#include <ifastcbo\amsmstrinfo.hpp>
#include <ifastcbo\RptAMSRebalancingCriteriaList.hpp>
#include <ifastcbo\RptAMSRebalancingCriteria.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_REPORT;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_REPORT;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< ReportProcess > processCreator( CMD_BPROC_REPORT );

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME               = I_( "ReportProcess" );
   const I_CHAR * const REPORT_GROUP            = I_( "ReportGroup" );
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
	extern CLASS_IMPORT const BFTextFieldId IsEnabledBtnAlloc;
}

//******************************************************************************
// Constructor - Container and field details are initialized here.
//******************************************************************************

//CP20030319ReportProcess::ReportProcess() : 
ReportProcess::ReportProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::REPORT_COMMON_INFO, false, BF::NullContainerId, true ); 
   addContainer( IFASTBP_PROC::REPORT_CRITERIA_LIST, true, BF::NullContainerId, true );

   addFieldDetails( ifds::ReportName, IFASTBP_PROC::REPORT_COMMON_INFO );   
   addFieldDetails( ifds::ReportMode, IFASTBP_PROC::REPORT_COMMON_INFO );
   addFieldDetails( ifds::ReportType, IFASTBP_PROC::REPORT_COMMON_INFO );
   addFieldDetails( ifds::ScheduleJob, IFASTBP_PROC::REPORT_COMMON_INFO );
   addFieldDetails( ifds::RunOnDate, IFASTBP_PROC::REPORT_COMMON_INFO );
   addFieldDetails( ifds::RunOnTime, IFASTBP_PROC::REPORT_COMMON_INFO );
   addFieldDetails( ifds::TimeZone, IFASTBP_PROC::REPORT_COMMON_INFO );   

   addFieldDetails( ifds::InclPending, IFASTBP_PROC::REPORT_CRITERIA_LIST );
   addFieldDetails( ifds::StartDate, IFASTBP_PROC::REPORT_CRITERIA_LIST );   

	addFieldDetails( ifds::LiveRunDate, IFASTBP_PROC::REPORT_CRITERIA_LIST );   
	addFieldDetails( ifds::UnsettleWithAMSFund, IFASTBP_PROC::REPORT_CRITERIA_LIST );   
	addFieldDetails( ifds::PendingWithAMSFund, IFASTBP_PROC::REPORT_CRITERIA_LIST );   

   addFieldDetails( ifds::Description, IFASTBP_PROC::REPORT_CRITERIA_LIST );
   addFieldDetails( ifds::AMSCode, IFASTBP_PROC::REPORT_CRITERIA_LIST );   
   addFieldDetails( ifds::BrokerCode, IFASTBP_PROC::REPORT_CRITERIA_LIST );
   addFieldDetails( ifds::GroupCode, IFASTBP_PROC::REPORT_CRITERIA_LIST );      
   addFieldDetails( ifds::AccountNum, IFASTBP_PROC::REPORT_CRITERIA_LIST );   
   addFieldDetails( ifds::IncludeExclude, IFASTBP_PROC::REPORT_CRITERIA_LIST );   
   addFieldDetails( ifds::CriteriaType, IFASTBP_PROC::REPORT_CRITERIA_LIST );
   addFieldDetails( ifds::CriteriaValue, IFASTBP_PROC::REPORT_CRITERIA_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::RecordType, IFASTBP_PROC::REPORT_CRITERIA_LIST );

   addFieldDetails( ifds::GlobalLevelRebal, IFASTBP_PROC::REPORT_CRITERIA_LIST);
   addFieldDetails( ifds::AccountLevelRebal, IFASTBP_PROC::REPORT_CRITERIA_LIST);

   addFieldDetails( ifds::IsEnabledBtnAlloc, IFASTBP_PROC::REPORT_CRITERIA_LIST, SUBCLASS_PROCESS);

   addFieldDetails ( CRITERIA_VAL::AMSCode, IFASTBP_PROC::REPORT_CRITERIA_LIST, SUBCLASS_PROCESS);
   addFieldDetails ( CRITERIA_VAL::AccountNum, IFASTBP_PROC::REPORT_CRITERIA_LIST, SUBCLASS_PROCESS);
   addFieldDetails ( CRITERIA_VAL::EffectiveDate, IFASTBP_PROC::REPORT_CRITERIA_LIST, SUBCLASS_PROCESS);
   
}

//******************************************************************************
// Destructor 
//******************************************************************************

ReportProcess::~ReportProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
// Function which get the container pointer on demand.
// @param   const BFContainerId& idContainer - Id to the container.
//          const BFDataGroupId& idDataGroup - group id.
// @returns void.
//******************************************************************************

void *ReportProcess::getPtrForContainer(
                                       const BFContainerId& idContainer,
                                       const BFDataGroupId& idDataGroup
                                       )
{
   void *ptr = NULL;
   SEVERITY sevRtn = NO_CONDITION;
   try
   {
//CP20030319      switch( idContainer )
//CP20030319      {
      // RSP Contribution List
//CP20030319         case REPORT::REPORT_COMMON_INFO :
	  /*DString dstrRptName;
	  getField(this, ifds::ReportName, dstrRptName);*/

      if( IFASTBP_PROC::REPORT_COMMON_INFO == idContainer )
      {
         {            
            ifastCommonReportCriteria* pifastCommonReportCriteria = NULL;
            DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
            pDSTCWorkSession->getReports( pifastCommonReportCriteria, idDataGroup );
            if( pifastCommonReportCriteria )
               ptr = pifastCommonReportCriteria;
            else
            {
               pDSTCWorkSession->createReports( pifastCommonReportCriteria, idDataGroup );
               ptr = pifastCommonReportCriteria;
            }
         }
//CP20030319            break;
//CP20030319         case REPORT::REPORT_CRITERIA_LIST :
      }
      else if( IFASTBP_PROC::REPORT_CRITERIA_LIST == idContainer )
      {
         {
            ifastCommonReportCriteria* pifastCommonReportCriteria = NULL;
            DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
            pDSTCWorkSession->getReports( pifastCommonReportCriteria, idDataGroup );
            if( !pifastCommonReportCriteria )
               pDSTCWorkSession->createReports( pifastCommonReportCriteria, idDataGroup );
            if( pifastCommonReportCriteria )
            {
               ifastReportCriteriaList* pifastReportCriteriaList = pifastCommonReportCriteria->getCriteriaList();
               if( pifastReportCriteriaList )
                  ptr = pifastReportCriteriaList;
               else
               {
                  pifastCommonReportCriteria->createCriteriaList( pifastReportCriteriaList, idDataGroup );
                  ptr = pifastReportCriteriaList;
               }
            }
         }      
//CP20030319      }
      }
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( ... )
   {
      //Show we throw?
   }
   return(ptr);
}

//******************************************************************************
// @returns SEVERITY.
//******************************************************************************

SEVERITY ReportProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      getParameter( REPORT_GROUP, _dstrReportGroup );     

	  ifastCommonReportCriteria* pifastCommonReportCriteria = NULL;
	  DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      pDSTCWorkSession->createReports( pifastCommonReportCriteria, getDataGroupId() );
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
// Function which tells the generic interface container that the modeless child
// has been destroyed.
// @param   const Command &cmd - cmd indicating the child is destroyed.
// @returns bool - true when successful.
//******************************************************************************

bool ReportProcess::doModelessChildComplete( const Command &cmd )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOMODELESSCHILDCOMPLETE );

   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_REPORT );
}


//******************************************************************************
// Functions which brings the Report dialog to focus and top of the window 
// stack.  It also notifies Report to refresh in case account information 
// has changed.
// @param   GenericInterface *rpGICaller - pointer to parent object.
// @return bool - true when successful, false otherwise.
//******************************************************************************

bool ReportProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );

   bool bRtn = false;
   try
   {
      assert( _rpChildGI && isValidModelessInterface( _rpChildGI ) );

      if( isValidModelessInterface( _rpChildGI ) )
      {  // Only if child still exists
         bRtn = _rpChildGI->refresh( this, NULL );
         bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
      }
      return(bRtn);
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
   return(false);
}

//******************************************************************************
// This functions starts the Reports Dialog
// @returns E_COMMANDRETURN.
//******************************************************************************

E_COMMANDRETURN ReportProcess::doProcess()
{  
   MAKEFRAME2( CND::IFASTBP_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      rtn = invokeCommand( this, CMD_GUI_REPORT, getProcessType(),
                           isModal(), &_rpChildGI );
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(rtn);
}

void ReportProcess::doGetField(
                              const GenericInterface *rpGICaller,
                              const BFContainerId& idContainer,
                              const BFFieldId& idField,
                              const BFDataGroupId& idDataGroup,
                              DString &strValueOut,
                              bool bFormatted
                              ) const
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOGETFIELD );   
   if( idContainer == IFASTBP_PROC::REPORT_CRITERIA_LIST )
   {
	  DString dstrCriteriaType;
      if( idField == ifds::CriteriaValue )
      {
         DString dstrCriteriaType;
         const_cast <ReportProcess*> (this)->getField( rpGICaller, idContainer, ifds::CriteriaType, dstrCriteriaType, false ); 
         if( dstrCriteriaType != NULL_STRING )
         {
            const BFFieldId& fieldId = BFFieldId::getId ( dstrCriteriaType );
            const_cast <ReportProcess*> (this)->getField( rpGICaller, idContainer, fieldId, strValueOut );         
         }
         else
         {
            strValueOut = NULL_STRING;
         }
      }

	  else if(idField == ifds::IsEnabledBtnAlloc)
	  {
		  auto pContainer = static_cast<BFAbstractCBO*>(const_cast <ReportProcess*> (this)->getPtrForContainer(idContainer, idDataGroup));
		  pContainer->getField(idField, strValueOut, idDataGroup, bFormatted);
	  }
	  else if ( idField == CRITERIA_VAL::AMSCode )
	  {
		 DString dstrCriteriaType;
		 auto pContainer = static_cast<RptAMSRebalancingCriteriaList*>(const_cast <ReportProcess*> (this)->getPtrForContainer(idContainer, idDataGroup));
		 BFObjIter iter(*pContainer, idDataGroup, BFObjIter::ITERTYPE::NON_DELETED);
		 for(iter.begin(); !iter.end(); iter++)
		 {
			 RptAMSRebalancingCriteria* pRptAMSRebalancingCriteria = dynamic_cast <RptAMSRebalancingCriteria*> (iter.getObject());
			 if (!pRptAMSRebalancingCriteria)
				 continue;
			 pRptAMSRebalancingCriteria->getField(ifds::CriteriaType, dstrCriteriaType, idDataGroup);
			 if ( dstrCriteriaType == I_("AMSCode") )
			 {
				pRptAMSRebalancingCriteria->getField(ifds::AMSCode, strValueOut, idDataGroup);
				break;
			 }		 
		 }
	  }
	  else if ( idField == CRITERIA_VAL::AccountNum )
	  {
		 DString dstrValueOut;
		 auto pContainer = static_cast<RptAMSRebalancingCriteriaList*>(const_cast <ReportProcess*> (this)->getPtrForContainer(idContainer, idDataGroup));
		 BFObjIter iter(*pContainer, idDataGroup, BFObjIter::ITERTYPE::NON_DELETED);
		 for(iter.begin(); !iter.end(); iter++)
		 {
			 RptAMSRebalancingCriteria* pRptAMSRebalancingCriteria = dynamic_cast <RptAMSRebalancingCriteria*> (iter.getObject());
			 if (!pRptAMSRebalancingCriteria)
				 continue;
			 pRptAMSRebalancingCriteria->getField(ifds::CriteriaType, dstrCriteriaType, idDataGroup);
			 if ( dstrCriteriaType == I_("AccountNum") )
			 {
				 pRptAMSRebalancingCriteria->getField(ifds::AccountNum, dstrValueOut, idDataGroup);
				 break;
			 }
		 }
		 if (iter.end() && dstrValueOut == NULL_STRING)
			strValueOut = I_("0");
		 else
			strValueOut = dstrValueOut;
	  }
	  else if ( idField == CRITERIA_VAL::EffectiveDate )
	  {
		 auto pContainer = static_cast<RptAMSRebalancingCriteriaList*>(const_cast <ReportProcess*> (this)->getPtrForContainer(idContainer, idDataGroup));
		 BFObjIter iter(*pContainer, idDataGroup, BFObjIter::ITERTYPE::NON_DELETED);
		 for(iter.begin(); !iter.end(); iter++)
		 {
			 RptAMSRebalancingCriteria* pRptAMSRebalancingCriteria = dynamic_cast <RptAMSRebalancingCriteria*> (iter.getObject());
			 if (!pRptAMSRebalancingCriteria)
				 continue;
			 pRptAMSRebalancingCriteria->getField(ifds::CriteriaType, dstrCriteriaType, idDataGroup);
			 if ( dstrCriteriaType == I_("StartDate") )
			 {
				pRptAMSRebalancingCriteria->getField(ifds::StartDate, strValueOut, idDataGroup);
				break;
			 }
		 }
	  }
   }

}

//*****************************************************************************
bool ReportProcess::doSend( GenericInterface *rpGICaller, const I_CHAR *szMessage) 
{

   DString dstrTag(szMessage);
   BFDataGroupId idDataGroup = getDataGroupId();
   if( dstrTag == I_("CriteriaValidate") )
   {
      
	  bool bIsGlobalLevelRebal = false, bIsAccountLevelRebal = false;
	  DString dstrAMSCode, dstrAccountNum, dstrIsEnabledBtnAlloc;
	  auto pContainer = static_cast<RptAMSRebalancingCriteriaList*>(const_cast <ReportProcess*> (this)->getPtrForContainer(IFASTBP_PROC::REPORT_CRITERIA_LIST , idDataGroup));
	  pContainer->getField(ifds::IsEnabledBtnAlloc, dstrIsEnabledBtnAlloc, idDataGroup);

	  BFObjIter iter(*pContainer, idDataGroup, BFObjIter::ITERTYPE::NON_DELETED);
	  for(iter.begin(); !iter.end(); iter++)
	  {
		  DString dstrCriteriaType, dstrCriteriaValue;
		  RptAMSRebalancingCriteria* pRptAMSRebalancingCriteria = dynamic_cast <RptAMSRebalancingCriteria*> (iter.getObject());
		  if (!pRptAMSRebalancingCriteria)
			  continue;
		  pRptAMSRebalancingCriteria->getField(ifds::CriteriaType, dstrCriteriaType, idDataGroup);
		  if ( dstrCriteriaType == I_("AMSCode") )
		  {
			  pRptAMSRebalancingCriteria->getField(ifds::AMSCode, dstrAMSCode, idDataGroup);
		  }
		  else if ( dstrCriteriaType == I_("GlobalLevelRebal") )
		  {
			  pRptAMSRebalancingCriteria->getField(ifds::GlobalLevelRebal, dstrCriteriaValue, idDataGroup);
			  if ( dstrCriteriaValue == I_("Y") )
				  bIsGlobalLevelRebal = true;
		  }
		  else if ( dstrCriteriaType == I_("AccountLevelRebal") )
		  {
			  pRptAMSRebalancingCriteria->getField(ifds::AccountLevelRebal, dstrCriteriaValue, idDataGroup);
			  if ( dstrCriteriaValue == I_("Y") )
				  bIsAccountLevelRebal = true;
		  }
		  else if ( dstrCriteriaType == I_("AccountNum") )
		  {
			  pRptAMSRebalancingCriteria->getField(ifds::AccountNum, dstrAccountNum, idDataGroup);
		  }
	  }	

	  if ( bIsGlobalLevelRebal )
	  {
		  if ( dstrAMSCode == I_("0001") )
			  dstrIsEnabledBtnAlloc = I_("N");
	  }
	  else if ( bIsAccountLevelRebal || dstrAMSCode == I_("0001") )
	  {
		  if ( dstrAccountNum == NULL_STRING )
			  dstrIsEnabledBtnAlloc = I_("N");
	  }
	  
	  pContainer->setField(ifds::IsEnabledBtnAlloc, dstrIsEnabledBtnAlloc, idDataGroup);
	  AMSHypoAllocList* pAMSHypoAllocList = pContainer->getAMSHypoAllocList( idDataGroup );
	  DString dstrOrigAMSCode, dstrOrigAccountNum;
	  if ( pAMSHypoAllocList )
	  {
		  if ( dstrIsEnabledBtnAlloc == I_("N") )
			  pContainer->deleteAMSHypoAllocList( idDataGroup );
		  else
		  {
			  pAMSHypoAllocList->getField(ifds::AMSCode, dstrOrigAMSCode, idDataGroup);
			  pAMSHypoAllocList->getField(ifds::AccountNum, dstrOrigAccountNum, idDataGroup);

			  if ( (dstrOrigAMSCode != dstrAMSCode) || (dstrOrigAccountNum != dstrAccountNum) )
				  pContainer->deleteAMSHypoAllocList( idDataGroup );			  
		  }
	  }

	  
	  _rpChildGI->refresh( this, I_("AllocBtn") );
	  
      return(true);
   }
   return(false);
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ReportProcess.cpp-arc  $
// 
//    Rev 1.2   Apr 09 2004 10:07:04   VADEANUM
// PET1005 FN11 - AMS Gaps.
// 
//    Rev 1.1   Mar 21 2003 17:46:34   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.0   Nov 27 2002 11:57:44   HSUCHIN
// Initial Revision
 */
