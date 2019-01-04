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
//    Copyright 2002 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : AMSHypoAllocProcess.cpp
// ^AUTHOR : Thanisorn Sangkrajang
// ^DATE   : Jul 24,2017
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : AMSHypoAllocProcess
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "AMSHypoAllocProcess.hpp"
#include "AMSHypoAllocProcessIncludes.h"
#include <ifastcbo\AmsHypoAllocList.hpp>
#include <ifastcbo\AmsHypoAlloc.hpp>
#include <ifastcbo\AmsFundAllocList.hpp>
#include <ifastcbo\DefFundAllocList.hpp>
#include <ifastcbo\DefFundAlloc.hpp>
#include <ifastcbo\AMSAcctLvl.hpp>
#include <ifastcbo\AMSAcctLvlList.hpp>
#include <ifastcbo\RptAMSRebalancingCriteriaList.hpp>
#include "mfcaninterprocparam.hpp"
#include "confirmationprocessincludes.h"
#include <ifastcbo\AmsMstrlist.hpp>
#include <ifastcbo\AmsMstrInfo.hpp>
#include "AMSHypoAllocProcessincludes.h"
#include <ifastcbo\ifastCommonReportCriteria.hpp>
#include <ifastcbo\ifastReportCriteriaList.hpp>
#include <ifastcbo\mfaccount.hpp>

#include <ifastdataimpl\dse_dstcglob_vw.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_AMS_HYPO_ALLOC;
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_AMS_HYPO_ALLOC;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< AMSHypoAllocProcess > processCreator( CMD_BPROC_AMS_HYPO_ALLOC );

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace 
{
   const I_CHAR * const CLASSNAME      = I_( "AMSHypoAllocProcess" );
   const I_CHAR * const YES            = I_("Y");
   const I_CHAR * const NO             = I_("N");
}

namespace AMS_HYPO_ALLOC_Para
{
   const I_CHAR * const AMS_CODE          = I_( "AMSCODE" );  
   const I_CHAR * const AMS_TYPE			   = I_( "AMSType" );
   const I_CHAR * const EFFECTIVE_DATE		= I_( "EffectiveDate" );
   const I_CHAR * const ACCOUNT_NUM		  = I_( "AccountNum" );
}
   

//******************************************************************************
//              Public Methods
//******************************************************************************
AMSHypoAllocProcess::AMSHypoAllocProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL )
,_pAMSHypoAllocList(NULL)
,_pFundAllocList(NULL)
,_bFoundAlloc(false)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   
   addContainer( IFASTBP_PROC::AMS_FUND_ALLOC_LIST, true, BF::NullContainerId, true, I_("AMSFundAllocList") );
   addContainer( IFASTBP_PROC::AMS_HYPO_ALLOC_LIST, true, BF::NullContainerId, true, I_("AMSHypoAllocList") );

   addFieldDetails( ifds::AMSType,			BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ifds::AMSCode,			BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ifds::EffectiveDate,    BF::NullContainerId, SUBCLASS_PROCESS );

   //AMS_FUND_ALLOC_LIST
   addFieldDetails( ifds::ToFundNumber,      IFASTBP_PROC::AMS_FUND_ALLOC_LIST );
   addFieldDetails( ifds::FundCode,          IFASTBP_PROC::AMS_FUND_ALLOC_LIST );
   addFieldDetails( ifds::ClassCode,         IFASTBP_PROC::AMS_FUND_ALLOC_LIST );
   addFieldDetails( ifds::AllocPercentage,   IFASTBP_PROC::AMS_FUND_ALLOC_LIST );

   //AMS_HYPO_ALLOC_LIST
   addFieldDetails( ifds::ToFundNumber,      IFASTBP_PROC::AMS_HYPO_ALLOC_LIST );
   addFieldDetails( ifds::FundCode,          IFASTBP_PROC::AMS_HYPO_ALLOC_LIST );
   addFieldDetails( ifds::ClassCode,         IFASTBP_PROC::AMS_HYPO_ALLOC_LIST );
   addFieldDetails( ifds::AllocPercentage,   IFASTBP_PROC::AMS_HYPO_ALLOC_LIST );
   addFieldDetails( ifds::AMSCode,           IFASTBP_PROC::AMS_HYPO_ALLOC_LIST );
   addFieldDetails( ifds::AccountNum,	     IFASTBP_PROC::AMS_HYPO_ALLOC_LIST );
   addFieldDetails( ifds::AMSType,			 IFASTBP_PROC::AMS_HYPO_ALLOC_LIST );
   
   addFieldDetails( ifds::TotPercentage,     BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( LIST_CHK::HasCurrPrcntAlloc, BF::NullContainerId, SUBCLASS_PROCESS );
}

//******************************************************************************
AMSHypoAllocProcess::~AMSHypoAllocProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY AMSHypoAllocProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doInit") );
   SEVERITY sevRtn=NO_CONDITION;

   getParameter( AMS_HYPO_ALLOC_Para::EFFECTIVE_DATE, _dstrEffectiveDate );
   getParameter( AMS_HYPO_ALLOC_Para::AMS_CODE, _dstrAmsCode );
   getParameter( AMS_HYPO_ALLOC_Para::AMS_TYPE, _dstrAmsType );
   getParameter (AMS_HYPO_ALLOC_Para::ACCOUNT_NUM, _dstrAccountNum );

   _dstrEffectiveDate.strip();
   _dstrAmsCode.strip().upperCase();
   _dstrAccountNum.strip();
   
   DString tmp;
   DSTCommonFunctions::UnformatDate( _dstrEffectiveDate, tmp );
   _dstrEffectiveDate = tmp;


   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Protected Methods
//******************************************************************************
bool AMSHypoAllocProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_BPROC_AMS_HYPO_ALLOC );
}

//******************************************************************************
bool AMSHypoAllocProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.

   bool bRtn = false;
   try
   {
      assert( _rpChildGI && isValidModelessInterface( _rpChildGI ) );
   }
   catch( ConditionException &ce )
   {
      MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doModelessSetFocus") );
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
E_COMMANDRETURN AMSHypoAllocProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      if( !bfutil::isServerContext() )
      {
		 setParameter( AMS_HYPO_ALLOC_Para::AMS_CODE, _dstrAmsCode );
         setParameter( AMS_HYPO_ALLOC_Para::AMS_TYPE, _dstrAmsType );
		 setParameter( AMS_HYPO_ALLOC_Para::EFFECTIVE_DATE, _dstrEffectiveDate );
		 setParameter( AMS_HYPO_ALLOC_Para::ACCOUNT_NUM, _dstrAccountNum );

         rtn = invokeCommand( this, CMD_GUI_AMS_HYPO_ALLOC, getProcessType(), isModal(),
                              &_rpChildGI );
      }
      else
      {
         rtn = CMD_MODELESS_INPROCESS;
      }
   }
   catch( ConditionException &ce )
   {
      assert( 0 );
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
//******************************************************************************
void AMSHypoAllocProcess::doGetField( const GenericInterface *rpGICaller,
                                const BFContainerId& idContainer,
                                const BFFieldId& idField,
                                const BFDataGroupId& idDataGroup,
                                DString &strValueOut,
                                bool bFormatted ) const
{
   if( idField == ifds::TotPercentage )
   {
      AMSHypoAllocList* pAMSHypoAllocList = NULL;
      pAMSHypoAllocList = (AMSHypoAllocList* )(
		  ( const_cast < AMSHypoAllocProcess *> ( this ) )->getPtrForContainer( IFASTBP_PROC::AMS_HYPO_ALLOC_LIST,idDataGroup ) );
      if( pAMSHypoAllocList )
         pAMSHypoAllocList->getTotalPercentage(strValueOut, idDataGroup);
	  
   }
   else if ( idField == LIST_CHK::HasCurrPrcntAlloc )
      strValueOut = (_bFoundAlloc ? I_("Y") : I_("N"));
}

//******************************************************************************
void* AMSHypoAllocProcess::getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
   void *ptr = NULL;
   SEVERITY sevRtn = NO_CONDITION;
   DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   AMSMstrList * pAmsMstrList = NULL;
   AmsMstrInfo * pAmsMstrInfo = NULL;   
   MFAccount *pMFAccount = NULL;
   AMSHypoAllocList* pAMSHypoAllocList = NULL;

   DString dstrAmsCode, dstrAmsType, dstrEffectiveDate, dstrIdentifyType, dstrIdentifyCode;

   try
   {
	  if ( _dstrAmsCode != I_("0001") )
	  {
		  dstrIdentifyType = I_("AMSCode");
		  dstrIdentifyCode = _dstrAmsCode;
	  }else
	  {
		  dstrIdentifyType = I_("AccountNum");
		  dstrIdentifyCode = _dstrAccountNum;
	  }
	  
	  if( IFASTBP_PROC::AMS_FUND_ALLOC_LIST == idContainer )
      {
		if( bfutil::isServerContext() || !_pFundAllocList )
		{
			DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
			if( _dstrAccountNum != I_("0") && _dstrAmsCode == I_("0001") )
			{
				dstcWorkSession->getMFAccount(idDataGroup,_dstrAccountNum,pMFAccount);
				if ( NULL != pMFAccount )
				{
					AMSAcctLvlList *pAMSAcctLvlList = NULL;
					if ( pMFAccount->getAMSAcctLvlList( idDataGroup, pAMSAcctLvlList, true ) &&
					NULL != pAMSAcctLvlList )
					{
						BFObjIter iter(*pAMSAcctLvlList, idDataGroup);
						AMSAcctLvl *pAMSAcctLvl = dynamic_cast <AMSAcctLvl*> (iter.getObject());
						DefFundAllocList *pFundAllocList = NULL;
						if (pAMSAcctLvl)
						{
							if ( pAMSAcctLvl->getAMSAcctLvlAllocation ( pFundAllocList, idDataGroup, true) <= WARNING && 
																		pFundAllocList)
							{
								_pFundAllocList = dynamic_cast<FundAllocList*> (pFundAllocList);
								BFObjIter iter(*pFundAllocList, idDataGroup);
								for( iter.begin();!iter.end();iter++)
								{
									auto *pFundAlloc = dynamic_cast<DefFundAlloc*> (iter.getObject());
									DString dstrFundCode;
									pFundAlloc->getField(ifds::FundCode, dstrFundCode, idDataGroup);
									if ( dstrFundCode != NULL_STRING )
									{
										_bFoundAlloc = true;
										break;
									}
								}
								if( _bFoundAlloc )
									ptr = pFundAllocList;
								else 
									ptr = NULL;
							}
						}
					   
					}
				}
			}
			else
			{
				sevRtn = dstcWorkSession->getAMSMstrList( pAmsMstrList,_dstrAmsType, _dstrAmsCode,_dstrEffectiveDate, idDataGroup,true,false );
				pAmsMstrList->getAMSMstrInfo(_dstrAmsType,_dstrAmsCode,_dstrEffectiveDate,pAmsMstrInfo,idDataGroup);
				AmsFundAllocList* pAMSFundAllocList;
				if( sevRtn <= WARNING && pAmsMstrList )
			    {
					BFObjIter iter( *pAmsMstrList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
					for(iter.begin();!iter.end();iter++)
				    {
						pAmsMstrInfo = dynamic_cast<AmsMstrInfo*>(iter.getObject());
						DString dstrEffectiveDate;
						pAmsMstrInfo->getField(ifds::EffectiveDate, dstrEffectiveDate, idDataGroup);

						if (pAmsMstrInfo)
						{
							if( pAmsMstrInfo->getAMSFundAllocList(pAMSFundAllocList, idDataGroup) <= WARNING )
							{
								_pFundAllocList = dynamic_cast<FundAllocList*> (pAMSFundAllocList);
								_bFoundAlloc = true;
								ptr = pAMSFundAllocList;
							}
						}
				  }
			   }
			}
		}

      }
	  else if( IFASTBP_PROC::AMS_HYPO_ALLOC_LIST == idContainer )
	  {
		  ifastCommonReportCriteria* pifastCommonReportCriteria = NULL;
          DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
          pDSTCWorkSession->getReports( pifastCommonReportCriteria, idDataGroup );
          ifastReportCriteriaList* pifastReportCriteriaList = pifastCommonReportCriteria->getCriteriaList();
		  _pAMSHypoAllocList = pifastReportCriteriaList->getAMSHypoAllocList(idDataGroup);

          if(_pAMSHypoAllocList)
		  {
			ptr = _pAMSHypoAllocList;
		  }
		  else
		  {	
			  FundAllocList* pFundAllocList = (_bFoundAlloc ? _pFundAllocList : NULL);
			
			pifastReportCriteriaList->createAMSHypoAllocList(_pAMSHypoAllocList, dstrIdentifyType, dstrIdentifyCode,pFundAllocList, idDataGroup);
			ptr = _pAMSHypoAllocList;
		  } 
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
SEVERITY AMSHypoAllocProcess::doValidateAll( BFAbstractCBO *rpWSD, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doValidateAll") );  
   SEVERITY sevReturn = NO_CONDITION;
   if( _pAMSHypoAllocList )
		sevReturn = _pAMSHypoAllocList->validateAll( idDataGroup );

   return(GETCURRENTHIGHESTSEVERITY());
}
//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/AMSHypoAllocProcess.cpp-arc  $
//
//    Rev 1.0   Jul 23 2017 09:24:40   Thanisorn S.
// Initial Revision
// 
