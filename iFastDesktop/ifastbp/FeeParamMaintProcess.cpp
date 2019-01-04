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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : FeeParamMaintProcess.cpp
// ^AUTHOR : 
// ^DATE   : July 21, 2004  
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : FeeParamMaintProcess
//    This class manages the address book process.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "feeparammaintprocessinclude.h"
#include "feeparammaintprocess.hpp"
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\feeparamsyslist.hpp>
#include <ifastcbo\feeparamsys.hpp>
#include "mfcaninterprocparam.hpp"
#include <ifastcbo\mgmtco.hpp>
#include "confirmationprocessincludes.h"
#include <ifastcbo\feeparamsyssearchcriteria.hpp>
#include <ifastcbo\feethrshldsys.hpp>
#include <ifastcbo\feethrshldsyslist.hpp>
#include <ifastcbo\feethrshldsyslist.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_FEE_PARAM_MAINT;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FEE_PARAM_MAINT;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< FeeParamMaintProcess > processCreator( CMD_BPROC_FEE_PARAM_MAINT );

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "FeeParamMaintProcess" );
}

namespace FeeParamMaint
{
   const I_CHAR * const FROM_SCR = I_( "from_screen" );
   const I_CHAR * const SYSTEM = I_("System");
//   const I_CHAR * const FUNDSPONSOR_CODE = I_("FundSponsorCode");
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{   
   extern CLASS_IMPORT const BFTextFieldId Username;
   extern CLASS_IMPORT const BFTextFieldId ModUser;

   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFDateFieldId StopDate;
   extern CLASS_IMPORT const BFDateFieldId ProcessDate;
   extern CLASS_IMPORT const BFDateFieldId ModDate;
}

namespace FEETYPE
{
   extern IFASTBP_LINKAGE const I_CHAR * const FLAT                 = I_( "0" );
   extern IFASTBP_LINKAGE const I_CHAR * const PERCENTAGE           = I_( "1" );
   extern IFASTBP_LINKAGE const I_CHAR * const SCALE                = I_( "2" );
   extern IFASTBP_LINKAGE const I_CHAR * const TIER                 = I_( "3" );
   extern IFASTBP_LINKAGE const I_CHAR * const TIER_BY_THRESHOLD    = I_( "4" );
   extern IFASTBP_LINKAGE const I_CHAR * const SCALE_BY_THRESHOLD   = I_( "5" );
}

namespace AUDITTYPE
{
   extern CLASS_IMPORT I_CHAR * const FEP;
   extern CLASS_IMPORT I_CHAR * const SCD;
   extern CLASS_IMPORT I_CHAR * const FEE_PARM_THRESHOLD;
}


//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319FeeParamMaintProcess::FeeParamMaintProcess() 
FeeParamMaintProcess::FeeParamMaintProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
,  _rpChildGI( NULL )
,	m_FeeParamListKey(NULL)
, m_FeeType(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, I_( "FeeParamMaintProcess" ) );

  
}

//******************************************************************************
FeeParamMaintProcess::~FeeParamMaintProcess()
{
   //TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY FeeParamMaintProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

   try
   {

      DString feeParamKey;

      getParameter (MFCAN_IP_PARAM::LIST_KEY, m_FeeParamListKey);
      getParameter (MFCAN_IP_PARAM::FEE_TYPE, m_FeeType);



 addContainer( IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, false, BF::NullContainerId, true, I_("FeeParamSys") );
   if(m_FeeType == FEETYPE::TIER_BY_THRESHOLD || 
      m_FeeType == FEETYPE::SCALE_BY_THRESHOLD)
   {
      addContainer( IFASTBP_PROC::FEE_PARAM_SYSTEM_THRESHOLD_LIST, true, IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, true, I_("FeeParamSystemThrshld") );
      addContainer( IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST, true, IFASTBP_PROC::FEE_PARAM_SYSTEM_THRESHOLD_LIST, true, I_("FeeParamSystemScale") );
   }
   else
   {
      addContainer( IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST, true, IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, true, I_("FeeParamSystemScale") );
   }
   
   addFieldDetails( ifds::FeeID,                IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::FeeParamRid,          IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::SysFeeSearchType,     IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::FundCode,             IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::ClassCode,            IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::FundFromCode,         IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::ClassFromCode,        IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::FeeCode,              IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::ParamFeeType,         IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::Rate,                 IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::MinFee,               IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::MaxFee,               IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::EffectiveDate,        IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::StopDate,             IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::FreqMinMaxApp,        IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::OnPW,                 IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::OnFW,                 IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::FundNumber,           IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::FromFundNumber,       IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::BranchCode,           IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::BranchName,           IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::SlsrepCode,           IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::SlsrepName,           IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::FamilyCode,           IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::FamilyName,           IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::ShGroupName,          IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::Currency,             IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::CommGroup,            IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::FeeModelCode,         IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::TaxInclusive,         IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );

	addFieldDetails( ifds::AppliedMethod,        IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
	addFieldDetails( ifds::DistributionChannel,  IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );


   addFieldDetails( ifds::FeeID,          IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST);
   addFieldDetails( ifds::ScaleRate,      IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST);
   addFieldDetails( ifds::UpperBound,     IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST);
   addFieldDetails( ifds::LowerBound,     IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST);
   addFieldDetails( ifds::FeeCode,        IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST);
   addFieldDetails( ifds::Level,          IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST);
   addFieldDetails( ifds::MinFee,         IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST);
   addFieldDetails( ifds::MaxFee,         IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST);
   addFieldDetails( ifds::ScaleDetlRid,   IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST);
   addFieldDetails( ifds::InvestTerm,     IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST);
   
   addFieldDetails( ifds::ProcessDate,    IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST);
   addFieldDetails( ifds::ThrshldUserName,IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST);
   addFieldDetails( ifds::ThrshldModUser, IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST);
   addFieldDetails( ifds::ThrshldModDate, IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST);


   if(m_FeeType == FEETYPE::TIER_BY_THRESHOLD ||
      m_FeeType == FEETYPE::SCALE_BY_THRESHOLD)
   {
      addFieldDetails( ifds::ThrshldLevel,   IFASTBP_PROC::FEE_PARAM_SYSTEM_THRESHOLD_LIST);
      addFieldDetails( ifds::ThrshldLower,   IFASTBP_PROC::FEE_PARAM_SYSTEM_THRESHOLD_LIST);
      addFieldDetails( ifds::ThrshldUpper,   IFASTBP_PROC::FEE_PARAM_SYSTEM_THRESHOLD_LIST);
      addFieldDetails( ifds::ThrshldRangeID, IFASTBP_PROC::FEE_PARAM_SYSTEM_THRESHOLD_LIST);
      addFieldDetails( ifds::ThrshldRecID,   IFASTBP_PROC::FEE_PARAM_SYSTEM_THRESHOLD_LIST);

      addFieldDetails( ifds::ThrshldProcDate, IFASTBP_PROC::FEE_PARAM_SYSTEM_THRESHOLD_LIST);
      addFieldDetails( ifds::ThrshldUserName, IFASTBP_PROC::FEE_PARAM_SYSTEM_THRESHOLD_LIST);
      addFieldDetails( ifds::ThrshldModUser,  IFASTBP_PROC::FEE_PARAM_SYSTEM_THRESHOLD_LIST);
      addFieldDetails( ifds::ThrshldModDate,  IFASTBP_PROC::FEE_PARAM_SYSTEM_THRESHOLD_LIST);

   }
/*
      getParent()->getParameter( FeeParamMaint::MODEL_CODE, m_modelCode );
      m_modelCode.strip();
      getParent()->getParameter( FeeParamMaint::FUNDSPONSOR_CODE, m_fundsponsorCode );
      m_fundsponsorCode.strip();
*/
      //const BFDataGroupId& idDataGroup = getDataGroupId();
      //
      //DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      //if( dstcWorkSession->getFeeParamMaintList( _pFeeParamMaintList, idDataGroup ) <= WARNING )
      //{
      //   BFObjIter iterFeeParamMaintList( *_pFeeParamMaintList, idDataGroup );
      //   m_totalNum = iterFeeParamMaintList.getNumberOfItemsInList();
      //   if( m_totalNum > 25 ) m_dispNum = 25;
      //   else m_dispNum = m_totalNum;
      //   m_dstrEndKey = asString( static_cast< long >( m_dispNum + 512.0 - 1.0 ) );

      //   setContainer( IFASTBP_PROC::FEE_MODEL_LIST, _pFeeParamMaintList ); 
      //}
      //else
      //{
      //   //TODO
      //   //add condition
      //}
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
E_COMMANDRETURN FeeParamMaintProcess::doProcess()
{  
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      if( isXMLAPIContext() )
      {
         rtn = CMD_MODELESS_INPROCESS;
      }
      else
      {
         setParameter (MFCAN_IP_PARAM::FEE_TYPE, m_FeeType);
         rtn = invokeCommand( this, CMD_GUI_FEE_PARAM_MAINT, getProcessType(), isModal(), &_rpChildGI );
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(rtn);
}

//******************************************************************************
bool  FeeParamMaintProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
   bool bRtn = false;

   try
   {
      const BFDataGroupId& idDataGroup = getDataGroupId();

      //DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      //if( dstcWorkSession->getFeeParamMaintList( _pFeeParamMaintList, idDataGroup ) <= WARNING )
      //{
      //    setContainer( IFASTBP_PROC::FEE_MODEL_LIST, _pFeeParamMaintList ); 

      //}
      //if( !( bRtn = _rpChildGI->refresh( this, NULL ) ) )
      //{
      //   return(bRtn);  // false
      //}
      //bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
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
bool  FeeParamMaintProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_FEE_PARAM_MAINT);
}
//******************************************************************************

void* FeeParamMaintProcess::getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
   void *ptr = NULL;
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   try
   {
      if(idContainer == IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST)
      {

         DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
         FeeParamSysSearchCriteria* _pFeeParamSysSearchCriteria = NULL;
         if( dstcWorkSession->getFeeParamSysSearchCriteria( _pFeeParamSysSearchCriteria,idDataGroup, true ) <= WARNING )
         {
            FeeParamSysList* _pFeeParamSysList = NULL;
            if( _pFeeParamSysSearchCriteria->GetFeeParamSysList(_pFeeParamSysList, getDataGroupId(),false,false,true ) <= WARNING && 
               _pFeeParamSysList )
            {
               ptr = _pFeeParamSysList->getObject(m_FeeParamListKey, idDataGroup);
            }
         }
      }
      else if (idContainer == IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST)
      {
         FeeParamSys* pFeeParamSys = dynamic_cast<FeeParamSys*>(getCBOItem(IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, idDataGroup));
         if( pFeeParamSys )
         {
            DString dstrFeeType, dstrbasedOn;
            pFeeParamSys->getField(ifds::ParamFeeType, dstrFeeType, idDataGroup, false);
			pFeeParamSys->getField (ifds::BasedOn, dstrbasedOn, idDataGroup, false);
            FeeScaleBaseList* pFeeScaleSysList = NULL;
            if(FEETYPE::TIER_BY_THRESHOLD == dstrFeeType ||
               FEETYPE::SCALE_BY_THRESHOLD == dstrFeeType)
            {
               FeeThrshldSys* pFeeThrshldSys = dynamic_cast<FeeThrshldSys*>(getCBOItem(IFASTBP_PROC::FEE_PARAM_SYSTEM_THRESHOLD_LIST, idDataGroup));
               pFeeThrshldSys->getFeeScaleSysList(pFeeScaleSysList, idDataGroup );
            }
            else if (FEETYPE::SCALE == dstrFeeType || FEETYPE::TIER == dstrFeeType || (FEETYPE::PERCENTAGE && dstrbasedOn == I_("6")))
            {
               pFeeParamSys->getFeeScaleList( pFeeScaleSysList, idDataGroup,true );
            }
            ptr = pFeeScaleSysList;
         }
      }
      else if(idContainer == IFASTBP_PROC::FEE_PARAM_SYSTEM_THRESHOLD_LIST)
      {
         FeeParamSys* pFeeParamSys = dynamic_cast<FeeParamSys*>(getCBOItem(IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, idDataGroup));
         if( pFeeParamSys )
         {
            DString dstrFeeType;
            pFeeParamSys->getField(ifds::ParamFeeType, dstrFeeType, idDataGroup, false);
            FeeThrshldSysList* pFeeThrshldSysList = NULL;
            if(FEETYPE::TIER_BY_THRESHOLD == dstrFeeType||
               FEETYPE::SCALE_BY_THRESHOLD == dstrFeeType)
            {
               pFeeParamSys->getFeeThresholdList(pFeeThrshldSysList, idDataGroup );
            }
            ptr = pFeeThrshldSysList;
         }
      }
      else 
      {
         ptr = AbstractProcess::getPtrForContainer(idContainer, idDataGroup);
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
bool FeeParamMaintProcess::doRefresh(
                               GenericInterface *rpGICaller,
                               const I_CHAR *szOriginalCommand
                               )
{
   return(_rpChildGI->refresh( this, NULL ));
}

//******************************************************************************

void FeeParamMaintProcess::doGetField(
                                const GenericInterface *rpGICaller,
                                const BFContainerId& idContainer,
                                const BFFieldId& idField,
                                const BFDataGroupId& idDataGroup,
                                DString &strValueOut,
                                bool bFormatted
                                ) const
{
}


//******************************************************************************

bool FeeParamMaintProcess::doOk( GenericInterface *rpGICaller )
{
   return(true);
}

//******************************************************************************
const DString& FeeParamMaintProcess::getNextListItemKey( const GenericInterface *rpGICaller, const BFContainerId& idList )
{  
   TRACE_METHOD( CLASSNAME, GETNEXTLISTITEMKEY );

   try
   {
      //if( idList == IFASTBP_PROC::FEE_MODEL_LIST )
      //{
      //   return (AbstractProcess::getCurrentListItemKey( rpGICaller, idList ));
      //}
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETNEXTLISTITEMKEY,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return AbstractProcess::getNextListItemKey( rpGICaller, idList );
}

//******************************************************************************
const DString& FeeParamMaintProcess::getFirstListItemKey( const GenericInterface *rpGICaller, const BFContainerId& idList )
{  
   TRACE_METHOD( CLASSNAME, GETFIRSTLISTITEMKEY );

   DString key;
   try
   {
      //if( idList == IFASTBP_PROC::FEE_MODEL_LIST )
      //{
      //   return (AbstractProcess::getCurrentListItemKey( rpGICaller, idList ));
      //}
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETFIRSTLISTITEMKEY,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return AbstractProcess::getFirstListItemKey( rpGICaller, idList );;
}



//******************************************************************************
void FeeParamMaintProcess::doPostOk(GenericInterface *rpGICaller, bool bSuccessFlag)
{
   DString FeeParamMaintCode;
  // if( bSuccessFlag && isContainerValid(IFASTBP_PROC::FEE_MODEL_LIST) 
  //    && getNumberOfItemsInList(this, IFASTBP_PROC::FEE_MODEL_LIST) > 0 )
  // {
		//const DString curKey = getCurrentListItemKey( rpGICaller,IFASTBP_PROC::FEE_MODEL_LIST );
		//if(curKey != NULL_STRING) {
		//	//getField( rpGICaller, IFASTBP_PROC::FEE_MODEL_LIST, ifds::FeeParamMaintCode, FeeParamMaintCode,false );
		//	//setParameter(MFCAN_IP_PARAM::FEE_MODEL_CODE, FeeParamMaintCode);
		//}
  // }
}

//******************************************************************************
SEVERITY FeeParamMaintProcess::getHistoricalParameters(const BFContainerId& idContainer, 
                                                     BFFieldId &recordIdField, DString& tableId,
                                                     DString& dstrKeys) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS );

   if( idContainer == IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST )
   {
      recordIdField = ifds::ScaleDetlRid;
      tableId = AUDITTYPE::SCD;
      dstrKeys = NULL_STRING;
   }
   else if( idContainer == IFASTBP_PROC::FEE_PARAM_SYSTEM_THRESHOLD_LIST)
   {
      recordIdField = ifds::ThrshldRecID;
      tableId = AUDITTYPE::FEE_PARM_THRESHOLD;
      dstrKeys = NULL_STRING;
   }
   else
   {
      assert(0);
   }
   return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************
SEVERITY FeeParamMaintProcess::getHistoricalParameters( 
   const BFContainerId& idContainer, 
   HISTORICAL_VECTOR &vectorHistorical )
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);
   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
bool FeeParamMaintProcess::canUpdate()
{
   bool retVal = false;

   FeeParamSys* pFeeParamSys = dynamic_cast<FeeParamSys*>(getCBOItem(IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, getDataGroupId()));
   if(pFeeParamSys)
   {
//      const DString &crtKey = getCurrentListItemKey (this,IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST);
      retVal = pFeeParamSys->canUpdateObject(getDataGroupId());
   }

   return retVal;
}
 
//******************************************************************************
SEVERITY FeeParamMaintProcess::doValidateAll( BFAbstractCBO *bfWorkSession,
                                         const BFDataGroupId& idDataGroup )
{
   SEVERITY retVal = NO_SEVERITY;

   if(m_FeeType == FEETYPE::TIER_BY_THRESHOLD)
   {
      FeeThrshldSysList* pFeeThrshldSysList = dynamic_cast<FeeThrshldSysList*>(getCBOList(IFASTBP_PROC::FEE_PARAM_SYSTEM_THRESHOLD_LIST, idDataGroup));
      if(pFeeThrshldSysList)
      {
         retVal = pFeeThrshldSysList->validateAll(idDataGroup);
      }
   }
   else
   {
      FeeScaleBaseList* pFeeScaleBaseList = dynamic_cast<FeeScaleBaseList*>(getCBOList(IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST, idDataGroup));
      if(pFeeScaleBaseList)
      {
         retVal = pFeeScaleBaseList->validateAll(idDataGroup);
      }
   }
   
   return retVal;
}
