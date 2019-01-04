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
// ^FILE   : AMSMstProcess.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Nov 5,2002
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : AMSMstProcess
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "AMSMstProcess.hpp"
#include "AMSMstProcessincludes.h"
#include <ifastcbo\amsmstrlist.hpp>
#include <ifastcbo\amsmstrinfo.hpp>
#include <ifastcbo\amsfundalloclist.hpp>
#include <ifastcbo\amsfundalloc.hpp>
#include <ifastcbo\amssearchcriteria.hpp>
#include "mfcaninterprocparam.hpp"
#include "confirmationprocessincludes.h"
#include <bfproc\AbstractProcess.hpp>
#include <ifastdataimpl\dse_dstcglob_vw.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_AMS_GLOBAL;
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_AMS_GLOBAL;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< AMSMstProcess > processCreator( CMD_BPROC_AMS_GLOBAL );

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace AMS_Para
{
   const I_CHAR * const AMS_CODE          = I_( "AMSCODE" );
   const I_CHAR * const FROM_SCR			   = I_( "FromScr" );
   const I_CHAR * const AMS_DETAIL			= I_( "AMSDetail" );  
   const I_CHAR * const AMS_TYPE			   = I_( "AMSType" );
   const I_CHAR * const DEFAULT_AMS_TYPE  = I_("defaultAMSType");
   const I_CHAR * const EFFECTIVE_DATE		= I_( "EffectiveDate" );

}

namespace 
{
   const I_CHAR * const CLASSNAME = I_( "AMSMstProcess" );
   const I_CHAR * const YES       = I_("Y");
   const I_CHAR * const NO        = I_("N");
}

namespace AUDITTYPE
{
   extern CLASS_IMPORT I_CHAR * const AMSMT;
}

namespace AMS_VALIDATION_GROUP
{
   const long AMS_MST_SEARCH = 0x0001;
}

namespace ifds
{   
   extern CLASS_IMPORT const BFTextFieldId AssocFundNum;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
AMSMstProcess::AMSMstProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL )
,_pAmsMstrList(NULL)
,_pAMSSearchCriteria(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::AMS_MST_LIST,        true, BF::NullContainerId,        true, I_("AMSMasterList") );
   addContainer( IFASTBP_PROC::AMS_ALLOCATION_LIST, true, IFASTBP_PROC::AMS_MST_LIST, true, I_("AMSAllocationList") );
   addContainer( IFASTBP_PROC::AMS_MST_SEARCH,      false, BF::NullContainerId,       true, I_("AMSMasterSearch") );

   addSubstituteList(ifds::AMSGlobalHeading);
   addSubstituteList(ifds::AMSFundAllocHeading );

   //AMS_MST_SEARCH
   addFieldDetails( ifds::AMSSearchType,      IFASTBP_PROC::AMS_MST_SEARCH );
   addFieldDetails( ifds::AMSType,            IFASTBP_PROC::AMS_MST_SEARCH );
   addFieldDetails( ifds::AMSCode,            IFASTBP_PROC::AMS_MST_SEARCH );
   addFieldDetails( ifds::EffectiveDate,      IFASTBP_PROC::AMS_MST_SEARCH );

   //AMS_MST_List
   addFieldDetails( ifds::AMSRecId,           IFASTBP_PROC::AMS_MST_LIST );
   addFieldDetails( ifds::AMSType,            IFASTBP_PROC::AMS_MST_LIST );
   addFieldDetails( ifds::AMSCode,            IFASTBP_PROC::AMS_MST_LIST );
   addFieldDetails( ifds::Name,               IFASTBP_PROC::AMS_MST_LIST );
   addFieldDetails( ifds::EffectiveDate,      IFASTBP_PROC::AMS_MST_LIST );
   addFieldDetails( ifds::Percentage,         IFASTBP_PROC::AMS_MST_LIST );
   addFieldDetails( ifds::Currency,           IFASTBP_PROC::AMS_MST_LIST );
   addFieldDetails( ifds::FundAlloc,          IFASTBP_PROC::AMS_MST_LIST );
   addFieldDetails( ifds::DefaultAlloc,       IFASTBP_PROC::AMS_MST_LIST );
   addFieldDetails( ifds::EnglishShortName,   IFASTBP_PROC::AMS_MST_LIST );
   addFieldDetails( ifds::EnglishLongName,    IFASTBP_PROC::AMS_MST_LIST );
   addFieldDetails( ifds::EnglishName,        IFASTBP_PROC::AMS_MST_LIST );
   addFieldDetails( ifds::FrenchShortName,    IFASTBP_PROC::AMS_MST_LIST );
   addFieldDetails( ifds::FrenchLongName,     IFASTBP_PROC::AMS_MST_LIST );
   addFieldDetails( ifds::FrenchName,         IFASTBP_PROC::AMS_MST_LIST );
   addFieldDetails( ifds::ForeignRelFundNum,  IFASTBP_PROC::AMS_MST_LIST );
   addFieldDetails( ifds::ForeignRelFund,     IFASTBP_PROC::AMS_MST_LIST );
   addFieldDetails( ifds::ForeignRelClass,    IFASTBP_PROC::AMS_MST_LIST );
   addFieldDetails( ifds::AssocFundNum,       IFASTBP_PROC::AMS_MST_LIST );
   addFieldDetails( ifds::AssocFund,          IFASTBP_PROC::AMS_MST_LIST );
   addFieldDetails( ifds::AssocClass,         IFASTBP_PROC::AMS_MST_LIST );

   addFieldDetails( ifds::GrandFatheredDate,  IFASTBP_PROC::AMS_MST_LIST );
   addFieldDetails( ifds::NextRebDate,        IFASTBP_PROC::AMS_MST_LIST );
   addFieldDetails( ifds::LastRebDate,        IFASTBP_PROC::AMS_MST_LIST );
   addFieldDetails( ifds::ThresholdAmt,       IFASTBP_PROC::AMS_MST_LIST );
   addFieldDetails( ifds::WireEleg,			    IFASTBP_PROC::AMS_MST_LIST );
   addFieldDetails( ifds::ModUser,			    IFASTBP_PROC::AMS_MST_LIST );
   addFieldDetails( ifds::ProcessDate,        IFASTBP_PROC::AMS_MST_LIST );
   addFieldDetails( ifds::ModDate,			    IFASTBP_PROC::AMS_MST_LIST );
   addFieldDetails( ifds::Username,			    IFASTBP_PROC::AMS_MST_LIST );
   addFieldDetails( ifds::SchedSetupFreqID,   IFASTBP_PROC::AMS_MST_LIST );
   addFieldDetails( ifds::VerifyPrecreate,	 IFASTBP_PROC::AMS_MST_LIST );
   addFieldDetails( ifds::LastEffectiveDate,  IFASTBP_PROC::AMS_MST_LIST );
   addFieldDetails( ifds::GrandFatherStamped, IFASTBP_PROC::AMS_MST_LIST );
   addFieldDetails( ifds::AMSCodeInUse,		 IFASTBP_PROC::AMS_MST_LIST );
   addFieldDetails( ifds::ParentFndClsTrdg,   IFASTBP_PROC::AMS_MST_LIST );
   addFieldDetails( ifds::RebalReq,			  IFASTBP_PROC::AMS_MST_LIST );
   addFieldDetails( ifds::TargetMixOption,		  IFASTBP_PROC::AMS_MST_LIST );
   addFieldDetails( ifds::AMSDeltaRequestUUID, IFASTBP_PROC::AMS_MST_LIST );
   addFieldDetails( ifds::LastAMSModDate, IFASTBP_PROC::AMS_MST_LIST );
   //AMS_ALLOCATION_LIST
   addFieldDetails( ifds::FundCode,          IFASTBP_PROC::AMS_ALLOCATION_LIST );
   addFieldDetails( ifds::ClassCode,         IFASTBP_PROC::AMS_ALLOCATION_LIST );
   addFieldDetails( ifds::ToFundNumber,      IFASTBP_PROC::AMS_ALLOCATION_LIST );
   addFieldDetails( ifds::AllocPercentage,   IFASTBP_PROC::AMS_ALLOCATION_LIST );  
   addFieldDetails( ifds::TotPercentage,     BF::NullContainerId, SUBCLASS_PROCESS );
// Generic Control	
   addFieldDetails( ifds::DispRBLSysThrshld, BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ifds::CommonCurrency,    BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( AMS_PROC::updated,       BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ifds::ClientAMSType,     BF::NullContainerId, SUBCLASS_PROCESS );

   addFieldDetails(  AMS_PROC::ORG_KEY,      BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails(  AMS_PROC::DEST_KEY,     BF::NullContainerId, SUBCLASS_PROCESS );
	 
   addFieldDetails(AMS_DELTA::IsAMSUpdate, BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails(AMS_DELTA::IsAMSFundUpdate, BF::NullContainerId, SUBCLASS_PROCESS);
}

//******************************************************************************
AMSMstProcess::~AMSMstProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
	if ( _pAMSSearchCriteria )
	{
		delete _pAMSSearchCriteria;
		_pAMSSearchCriteria = NULL;
	}
}

//******************************************************************************
SEVERITY AMSMstProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doInit") );
   SEVERITY sevRtn=NO_CONDITION;

   getParameter( AMS_Para::AMS_CODE, _dstrAmsCode );
   getParameter( AMS_Para::FROM_SCR,  _dstrFromScr );
   getParameter( AMS_Para::AMS_TYPE, _dstrAmsType );

   _dstrAmsCode.strip();

   try
   {  

        const BFDataGroupId& idDataGroup = getDataGroupId();
		_pAMSSearchCriteria = new AMSSearchCriteria( *getBFWorkSession() );
		if( _pAMSSearchCriteria->init(idDataGroup)<= WARNING )
      {
         setContainer( IFASTBP_PROC::AMS_MST_SEARCH, _pAMSSearchCriteria ); 
		 if ( !_dstrAmsCode.empty() ) 
		 {
			 _pAMSSearchCriteria->setField(ifds::AMSCode, _dstrAmsCode,idDataGroup,false);
		 }
		 if ( !_dstrAmsType.empty() )
		 {
			 _pAMSSearchCriteria->setField(ifds::AMSType, _dstrAmsType,idDataGroup,false);

		 }
      }
  

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
//              Protected Methods
//******************************************************************************
bool AMSMstProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_BPROC_AMS_GLOBAL );
}

//******************************************************************************
bool AMSMstProcess::doModelessSetFocus( GenericInterface *rpGICaller )
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
E_COMMANDRETURN AMSMstProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      if( !bfutil::isServerContext() )
      {
         setParameter( AMS_Para::FROM_SCR,  _dstrFromScr );

         rtn = invokeCommand( this, CMD_GUI_AMS_GLOBAL, getProcessType(), isModal(),
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
//****************************************************************************************************

bool AMSMstProcess::doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch )
{
   return(rpGICaller == NULL || _pAmsMstrList == NULL ? false : _pAmsMstrList->doMoreRecordsExist());
}

//****************************************************************************************************
SEVERITY AMSMstProcess::performSearch( GenericInterface *rpGI, 
                                       const BFContainerId& idSearch, E_SEARCHACTION eSearchAction )
{
   SEVERITY sevRtn = SEVERE_ERROR;
   try
   {
      if( SEARCH_START == eSearchAction && _pAMSSearchCriteria )
      {

		 sevRtn = _pAMSSearchCriteria->validateAll( getDataGroupId(), AMS_VALIDATION_GROUP::AMS_MST_SEARCH  );

         if( sevRtn <= WARNING )
         {
			 clearParameters();
			 const BFDataGroupId& idDataGroup = getDataGroupId();
			 _pAMSSearchCriteria->getField(ifds::EffectiveDate, _dstrEffectiveDate,idDataGroup);
			 _pAMSSearchCriteria->getField(ifds::AMSCode, _dstrAmsCode,idDataGroup);
			 _pAMSSearchCriteria->getField(ifds::AMSType, _dstrAmsType,idDataGroup);
			  _dstrAmsCode.strip().upperCase();
			  _dstrAmsType.strip().upperCase();

			 DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
			 dstcWorkSession->getAMSMstrList( _pAmsMstrList,_oldAmsType,_oldAmsCode,_oldEffectiveDate, idDataGroup,false,true,false );
			 dstcWorkSession->getAMSMstrList( _pAmsMstrList,_dstrAmsType,_dstrAmsCode,_dstrEffectiveDate, idDataGroup,true,true,true );
			 if( _pAmsMstrList )
			 {
				setContainer( IFASTBP_PROC::AMS_MST_LIST, _pAmsMstrList );  
				_oldAmsCode = _dstrAmsCode;
				_oldAmsType = _dstrAmsType;
				_oldEffectiveDate = _dstrEffectiveDate;
	
			 }
		 }
      }
      else if( SEARCH_NEXT_BLOCK == eSearchAction )
      {
         if( _pAmsMstrList )
             sevRtn = _pAmsMstrList->getMore();

      }
   }
   catch( ConditionException &ce )
   {
      MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "performSearch" ) );
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "performSearch" ), 
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(sevRtn); 
}

//******************************************************************************

void AMSMstProcess::doGetField( const GenericInterface *rpGICaller,
                                const BFContainerId& idContainer,
                                const BFFieldId& idField,
                                const BFDataGroupId& idDataGroup,
                                DString &strValueOut,
                                bool bFormatted ) const
{
   if( idField == ifds::DispRBLSysThrshld || idField == ifds::CommonCurrency || idField == ifds::ClientAMSType )
   {
      const BFDataGroupId& idDataGroup = getDataGroupId();
      DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      if( dstcWorkSession )
         dstcWorkSession->getOption( idField, strValueOut, idDataGroup, bFormatted);
   }
   else if( idField == ifds::TotPercentage )
   {
      AmsFundAllocList* pAmsFundAllocList = NULL;
      pAmsFundAllocList = (AmsFundAllocList* )(
                                              ( const_cast < AMSMstProcess *> ( this ) )->getPtrForContainer( IFASTBP_PROC::AMS_ALLOCATION_LIST,
                                                                                                              idDataGroup ) );
      if( pAmsFundAllocList )

         pAmsFundAllocList->getTotalPercentage(strValueOut, idDataGroup);

   }
   else if( idField == AMS_PROC::updated )
   {
      if( _pAmsMstrList )
      {
         bool bUpdated = _pAmsMstrList->isUpdatedForDataGroup(idDataGroup );
         strValueOut = bUpdated? YES:NO;
      }
   }
   else if(idField == AMS_DELTA::IsAMSFundUpdate)
   {
     AmsFundAllocList* pAmsFundAllocList = NULL;
     pAmsFundAllocList = (AmsFundAllocList*)((const_cast< AMSMstProcess*>(this))->getPtrForContainer(IFASTBP_PROC::AMS_ALLOCATION_LIST,
                                                                                                     idDataGroup));
     if(pAmsFundAllocList)
     {
       bool bUpdated = pAmsFundAllocList->isUpdatedForDataGroup(idDataGroup);
       strValueOut = bUpdated? YES:NO;
     }
   }
   else if(idField == AMS_DELTA::IsAMSUpdate)
   {
     AMSMstProcess *rp = const_cast < AMSMstProcess*> ( this );
     AmsMstrInfo *pAMSMstrInfo = dynamic_cast<AmsMstrInfo*>(rp->getCBOItem(IFASTBP_PROC::AMS_MST_LIST, idDataGroup ));
     if(pAMSMstrInfo)
     {
       bool bUpdated = pAMSMstrInfo->isUpdated(false);
       strValueOut = bUpdated? YES:NO;
     }
   }
   else
   {
      assert(0);  
   }
}
//**************************************************************************************
bool AMSMstProcess::doOk( GenericInterface *rpGICaller )
{

   setParameter( CONFPROC::PARM_CALLED_FROM,I_("AmsGlobal") );
 
   if( _pAMSSearchCriteria )
      _pAMSSearchCriteria->clearUpdateFlags( getDataGroupId() );


   return(true);
}

//**************************************************************************************
void AMSMstProcess::doPostOk( GenericInterface *rpGICaller, bool bSuccessFlag )
{
   DString dstrAMSCode;
   if( bSuccessFlag && getNumberOfItemsInList(this, IFASTBP_PROC::AMS_MST_LIST) > 0 )
   {
		const DString curKey = getCurrentListItemKey( rpGICaller,IFASTBP_PROC::AMS_MST_LIST );
		if(curKey != NULL_STRING) {
			getField( rpGICaller, IFASTBP_PROC::AMS_MST_LIST, ifds::AMSCode, dstrAMSCode,false );
			setParameter( AMS_Para::AMS_CODE, dstrAMSCode );
		}
   }
}

//*****************************************************************************
SEVERITY  AMSMstProcess:: doSetField( const GenericInterface *rpGICaller,
                                      const BFContainerId& idContainer,
                                      const BFFieldId& idField,
                                      const BFDataGroupId& idDataGroup,
                                      const DString& strValue,
                                      bool bFormatted )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "doSetField" ) );

   if( BF::NullContainerId == idContainer && idField == AMS_PROC::ORG_KEY )
   {
      _dstrOrgKey = strValue;
   }
   else if( BF::NullContainerId == idContainer && idField == AMS_PROC::DEST_KEY )
   {
      _dstrDestKey = strValue;

      DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      dstcWorkSession->getAMSMstrList( _pAmsMstrList,_dstrAmsType,_dstrAmsCode,_dstrEffectiveDate, idDataGroup,true,false );

      _pAmsMstrList->AddCopy(_dstrOrgKey, _dstrDestKey, idDataGroup);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void* AMSMstProcess::getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
   void *ptr = NULL;
   SEVERITY sevRtn = SEVERE_ERROR;

   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   try
   {
      if( IFASTBP_PROC::AMS_ALLOCATION_LIST == idContainer )
      {
         {
            AmsMstrInfo *pAmsMstrInfo = dynamic_cast< AmsMstrInfo * >( getCBOItem(IFASTBP_PROC::AMS_MST_LIST, idDataGroup ) );
            AmsFundAllocList* pAmsFundAllocList = NULL;
            if( pAmsMstrInfo->getAMSFundAllocList( pAmsFundAllocList,idDataGroup ) <= WARNING )
            {
               ptr = pAmsFundAllocList;
            }
         }
      }
      else if( IFASTBP_PROC::AMS_MST_LIST == idContainer )
      {
         {
            if( bfutil::isServerContext() || !_pAmsMstrList )
            {
               clearParameters();
               const BFDataGroupId& idDataGroup = getDataGroupId();
               DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
               sevRtn = dstcWorkSession->getAMSMstrList( _pAmsMstrList,_dstrAmsType,_dstrAmsCode,_dstrEffectiveDate, idDataGroup,true,false );
               if( sevRtn <= WARNING && _pAmsMstrList )
               {
                  setContainer( IFASTBP_PROC::AMS_MST_LIST, _pAmsMstrList );
                  ptr = _pAmsMstrList;
               }
            }
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

//*****************************************************************************
bool AMSMstProcess::doSend( GenericInterface * rpGICaller,
                        const I_CHAR * szMessage )
{
	if(szMessage == AMS_Para::DEFAULT_AMS_TYPE )
	{
		DString dstrAmsType;
		getParameter( AMS_Para::AMS_TYPE, dstrAmsType );
		if(_pAmsMstrList)
		{
			_pAmsMstrList->setCurrentAMSType(dstrAmsType);
			return true;
		}
	}		
	return false;
}

//******************************************************************************
SEVERITY AMSMstProcess::getHistoricalParameters( const BFContainerId& idContainer, HISTORICAL_VECTOR &vectorHistorical )
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);

   DString keyStringIDI( NULL_STRING ), dstrRecord;
   getField( this, IFASTBP_PROC::AMS_MST_LIST, ifds::AMSRecId, dstrRecord, false );
   HistoricalElement historicalElement( dstrRecord, AUDITTYPE::AMSMT, keyStringIDI );
   vectorHistorical.push_back( historicalElement );

   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/AMSMstProcess.cpp-arc  $
// 
//    Rev 1.27   Aug 27 2009 22:20:24   wutipong
// UTP_DSK_IN1720999_WO414172_ Can not change an AMS in Desktop -- 'More' button issue.
// 
//    Rev 1.26   Aug 03 2007 09:34:46   smithdav
// PET 2360 FN02
// 
//    Rev 1.25   Jul 18 2007 09:35:18   smithdav
// PET2360 FN02
// 
//    Rev 1.24   Jun 22 2007 14:17:20   porteanm
// PET 2360 FN02 - AMS - work in progress.
// 
//    Rev 1.23   Jun 18 2007 14:33:10   porteanm
// PET2360 FN02 - AIM AMS - Syst level.
// 
//    Rev 1.22   Mar 10 2004 12:10:58   HERNANDO
// PET965 FN11 - Changed getHistoricalParameters.
// 
//    Rev 1.21   Aug 22 2003 13:26:58   linmay
// added logic for ams search
// 
//    Rev 1.20   Aug 18 2003 16:08:34   HERNANDO
// Added keys to getHistoricalParameters.
// 
//    Rev 1.19   Aug 18 2003 11:47:48   linmay
// modified performSearch()
// 
//    Rev 1.18   Aug 11 2003 09:43:38   linmay
// fix bug
// 
//    Rev 1.17   Jul 31 2003 14:57:26   linmay
// changed to amsmt for audit type
// 
//    Rev 1.16   Jul 23 2003 10:51:18   linmay
// modified for cibc
// 
//    Rev 1.15   Jul 18 2003 11:18:04   linmay
// modified for CIBC AMS
// 
//    Rev 1.14   Apr 21 2003 09:39:58   YINGBAOL
// reimplemt AMSType 
// 
//    Rev 1.13   Apr 05 2003 11:28:10   YINGBAOL
// GetPtrforContainer should not delete the list
// 
//    Rev 1.12   Apr 02 2003 12:19:34   PURDYECH
// Code cleanup
//
