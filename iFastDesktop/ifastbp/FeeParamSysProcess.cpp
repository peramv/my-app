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
// ^FILE   : FeeParamSysProcess.cpp
// ^AUTHOR : Yingbao  Li, May Lin
// ^DATE   : January 10, 2003  
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : FeeParamSysProcess
//    This class manages the address book process.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "feeparamsysprocessinclude.hpp"
#include "feeparamsysprocess.hpp"
#include <ifastcbo\feeparamsyslist.hpp>
#include <ifastcbo\feeparamsys.hpp>
#include <ifastcbo\feescalesyslist.hpp>
#include <ifastcbo\feescalesys.hpp>
#include <ifastcbo\FundCommGroupList.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\feeparamsyssearchcriteria.hpp>
#include <ifastcbo\feethrshldsys.hpp>
#include <bfproc\AbstractProcess.hpp>
#include <ifastcbo\mgmtcooptions.hpp>

#include "confirmationprocessincludes.h"
#include <bfproc\genericinterfacecontainer.hpp>
#include <bfcbo\validationcontrol.hpp>
#include <bfsessn\bfawdsession.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_FEE_PARAMETER_SYSTEM;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FEE_PARAMETER_SYSTEM;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< FeeParamSysProcess > processCreator( CMD_BPROC_FEE_PARAMETER_SYSTEM );

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "FeeParamSysProcess" );
   const I_CHAR *YES = I_( "Y" );
   const I_CHAR *NO  = I_( "N" );
   const I_CHAR *DEFAULT_DATE = I_( "01010001" ); 
}

namespace FEEPARAMSYS
{

}

namespace FEETYPE
{
   const I_CHAR * const FLAT                 = I_( "0" );
   const I_CHAR * const PERCENTAGE           = I_( "1" );
   const I_CHAR * const SCALE                = I_( "2" );
   const I_CHAR * const TIER                 = I_( "3" );
   const I_CHAR * const TIER_BY_THRESHOLD    = I_( "4" );
   const I_CHAR * const SCALE_BY_THRESHOLD   = I_( "5" );
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace AUDITTYPE
{
   extern CLASS_IMPORT I_CHAR * const FEP;
   extern CLASS_IMPORT I_CHAR * const SCD;
   extern CLASS_IMPORT I_CHAR * const FEE_PARM_THRESHOLD;
}

namespace FEE_PARAM_VALIDATION_GROUP
{
   const long FEE_PARAM_SEARCH = 0x0001;
}

namespace MFCAN_IP_PARAM
{
   extern IFASTBP_LINKAGE const I_CHAR * const FEE_MODEL_CODE;
   extern IFASTBP_LINKAGE const I_CHAR * const HOLDING_COMP_CODE;

}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319FeeParamSysProcess::FeeParamSysProcess() 
FeeParamSysProcess::FeeParamSysProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
,_pFeeParamSysSearchCriteria( NULL )
, _pFeeParamSysList(NULL)
, _rpChildGI( NULL ),
m_FeeModelCode(NULL)
//, m_dstrBaseFilter( NULL_STRING )
{
   TRACE_CONSTRUCTOR( CLASSNAME, I_( "FeeParamSysProcess" ) );

   addContainer( IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST,             true,  BF::NullContainerId, true, I_("FeeParamSys") );
   addContainer( IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST,       true,  IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, true );
   addContainer( IFASTBP_PROC::FUND_COMM_GROUP_LIST,              true,  BF::NullContainerId, true );
   addContainer( IFASTBP_PROC::FEE_PARAM_SYSTEM_THRESHOLD_LIST,   true,  IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, true );
   addContainer( IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_THR_LIST,   true,  IFASTBP_PROC::FEE_PARAM_SYSTEM_THRESHOLD_LIST, true );
   addContainer( IFASTBP_PROC::FEE_PARAM_SEARCH,                  false, BF::NullContainerId, true, I_("FeeParamSearch") );

   addFieldDetails( ifds::SysFeeSearchType,  IFASTBP_PROC::FEE_PARAM_SEARCH );
   addFieldDetails( ifds::BrokerCode,        IFASTBP_PROC::FEE_PARAM_SEARCH );
   addFieldDetails( ifds::FundCode,          IFASTBP_PROC::FEE_PARAM_SEARCH );
   addFieldDetails( ifds::ClassCode,         IFASTBP_PROC::FEE_PARAM_SEARCH );
   addFieldDetails( ifds::CommGroup,         IFASTBP_PROC::FEE_PARAM_SEARCH );
   addFieldDetails( ifds::FeeCode,           IFASTBP_PROC::FEE_PARAM_SEARCH );
   addFieldDetails( ifds::ShGroup,           IFASTBP_PROC::FEE_PARAM_SEARCH );
   addFieldDetails( ifds::BranchCode,        IFASTBP_PROC::FEE_PARAM_SEARCH );
   addFieldDetails( ifds::SlsrepCode,        IFASTBP_PROC::FEE_PARAM_SEARCH );
   addFieldDetails( ifds::FeeModelCode,      IFASTBP_PROC::FEE_PARAM_SEARCH );
   addFieldDetails( ifds::SearchAll,         IFASTBP_PROC::FEE_PARAM_SEARCH );
   addFieldDetails( ifds::AsofDate,          IFASTBP_PROC::FEE_PARAM_SEARCH );


   addFieldDetails( ifds::FeeID,             IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::FeeParamRid,       IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::SysFeeSearchType,  IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::FundCode,          IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::ClassCode,         IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::FundFromCode,      IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::ClassFromCode,     IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::FeeCode,           IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::ParamFeeType,      IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::Rate,              IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::MinFee,            IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::MaxFee,            IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::EffectiveDate,     IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::StopDate,          IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::FreqMinMaxApp,     IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::OnPW,              IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::OnFW,              IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::FundNumber,        IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::FromFundNumber,    IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::BranchCode,        IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::BranchName,        IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::SlsrepCode,        IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::SlsrepName,        IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::FamilyCode,        IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::FamilyName,        IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::ShGroupName,       IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );

   addFieldDetails( ifds::Active,            IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::ProcessDate,       IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::ModDate,           IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::Username,          IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::ModUser,           IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::CommGroup,         IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::BrokerCode,        IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::BrokerName,        IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, SUBCLASS_PROCESS );

   addFieldDetails( ifds::AllowOverrideType, IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::BasedOn,           IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::ThresholdAmt,      IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::ThresholdCurrency, IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );

   addFieldDetails( ifds::Currency,          IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::HowPaid,           IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::ShGroup,           IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::FundList,          IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::FundLink,          IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::TaxInclusive,      IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   addFieldDetails( ifds::FeeModelCode,      IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );

   addFieldDetails( ifds::AppliedMethod,     IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
	addFieldDetails( ifds::DistributionChannel, IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );

   addFieldDetails( ifds::FeeID,          IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST );
   addFieldDetails( ifds::ScaleRate,      IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST );
   addFieldDetails( ifds::UpperBound,     IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST  );
   addFieldDetails( ifds::LowerBound,     IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST  );
   addFieldDetails( ifds::FeeCode,        IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST  );
   addFieldDetails( ifds::Level,          IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST  );
   addFieldDetails( ifds::MinFee,         IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST );
   addFieldDetails( ifds::MaxFee,         IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST );
   addFieldDetails( ifds::ScaleDetlRid,   IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST );
   addFieldDetails( ifds::InvestTerm,     IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST );

   addFieldDetails( ifds::FeeID,          IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_THR_LIST);
   addFieldDetails( ifds::ScaleRate,      IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_THR_LIST);
   addFieldDetails( ifds::UpperBound,     IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_THR_LIST);
   addFieldDetails( ifds::LowerBound,     IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_THR_LIST);
   addFieldDetails( ifds::FeeCode,        IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_THR_LIST);
   addFieldDetails( ifds::Level,          IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_THR_LIST);
   addFieldDetails( ifds::MinFee,         IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_THR_LIST);
   addFieldDetails( ifds::MaxFee,         IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_THR_LIST);
   addFieldDetails( ifds::ScaleDetlRid,   IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_THR_LIST);
   addFieldDetails( ifds::InvestTerm,     IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_THR_LIST);

   addFieldDetails( ifds::ThrshldLevel,   IFASTBP_PROC::FEE_PARAM_SYSTEM_THRESHOLD_LIST);
   addFieldDetails( ifds::ThrshldLower,   IFASTBP_PROC::FEE_PARAM_SYSTEM_THRESHOLD_LIST);
   addFieldDetails( ifds::ThrshldUpper,   IFASTBP_PROC::FEE_PARAM_SYSTEM_THRESHOLD_LIST);
   addFieldDetails( ifds::ThrshldRangeID, IFASTBP_PROC::FEE_PARAM_SYSTEM_THRESHOLD_LIST);

   
   addFieldDetails( FEEPARAMSYS::CLEAR_SEARCH_CRITERIA,     IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, SUBCLASS_PROCESS );
   addFieldDetails( FEEPARAMSYS::HAS_OBJECT_UPDATE,         IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, SUBCLASS_PROCESS );
   addFieldDetails( FEEPARAMSYS::RELOAD_OBJECT,             IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, SUBCLASS_PROCESS );
   addFieldDetails( FEEPARAMSYS::IS_THE_SAME_BUSINESS_DATE, IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, SUBCLASS_PROCESS );
   addFieldDetails( FEEPARAMSYS::GET_DEFAULT_BRANCH_CODE,   IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, SUBCLASS_PROCESS );

   addFieldDetails( FEEPARAMSYS::ALLOW_NEG_RATE,   IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, SUBCLASS_PROCESS );

   addSubstituteList( ifds::FeeParamSysHeading);
   addSubstituteList( ifds::FeeScaleSysHeading);
   addSubstituteList( ifds::FeeScaleSysInvestTermHeading);
   addFieldDetails  ( ifds::TradingAttributesHeadingSet, IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST );

}

//******************************************************************************
FeeParamSysProcess::~FeeParamSysProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
//   delete _pFeeParamSysSearchCriteria;
//   _pFeeParamSysSearchCriteria = NULL;
   _rpChildGI = NULL;

}

//******************************************************************************
SEVERITY FeeParamSysProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

   try
   {
      const BFDataGroupId& idDataGroup = getDataGroupId();


      getParameter(MFCAN_IP_PARAM::FEE_MODEL_CODE, m_FeeModelCode);
      getParameter(MFCAN_IP_PARAM::HOLDING_COMP_CODE, m_HoldingCompCode);

      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

      if( dstcWorkSession->getFeeParamSysSearchCriteria( _pFeeParamSysSearchCriteria,idDataGroup, true ) <= WARNING )
      {
         setContainer( IFASTBP_PROC::FEE_PARAM_SEARCH, _pFeeParamSysSearchCriteria ); 
         _pFeeParamSysSearchCriteria->setField(ifds::SearchAll, I_("N"), BF::HOST, false, false);
         _pFeeParamSysSearchCriteria->setFieldUpdated(ifds::SearchAll, BF::HOST, false);


         bool bInq = false;
         if(m_FeeModelCode != I_(""))
         {
            _pFeeParamSysSearchCriteria->setField(ifds::SysFeeSearchType, I_("FeeModelFundClass"), idDataGroup, false, true);
            _pFeeParamSysSearchCriteria->setField(ifds::FeeModelCode, m_FeeModelCode, idDataGroup, false, true);

            _pFeeParamSysSearchCriteria->setFieldReadOnly(ifds::SysFeeSearchType, idDataGroup, true);
            _pFeeParamSysSearchCriteria->setFieldReadOnly(ifds::FeeModelCode, idDataGroup, true);
            bInq = true;
         }

         DString dstrCurBusDate;
         DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
	      dstWorkSession->getMgmtCoOptions()->getField(ifds::CurrBusDate, dstrCurBusDate, BF::HOST);
         dstrCurBusDate.strip();
         _pFeeParamSysSearchCriteria->setField(ifds::AsofDate, dstrCurBusDate, idDataGroup, false, false);
         _pFeeParamSysSearchCriteria->setFieldUpdated(ifds::AsofDate, idDataGroup, false);
         SEVERITY sevRtn1=_pFeeParamSysSearchCriteria->GetFeeParamSysList(_pFeeParamSysList, getDataGroupId(), bInq, bInq, !bInq );
         if( sevRtn1 <= WARNING && _pFeeParamSysList )
         {
            _pFeeParamSysList->setFromFeeModelCode(m_FeeModelCode);
            setContainer( IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, _pFeeParamSysList ); 
/*			DString dstrFilter;
			dstrFilter += asString( ifds::EffectiveDate.getId() );
			dstrFilter += I_( "!=" );
			dstrFilter += DEFAULT_DATE;
			m_dstrBaseFilter = dstrFilter;
*/
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
E_COMMANDRETURN FeeParamSysProcess::doProcess()
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
         setParameter(MFCAN_IP_PARAM::FEE_MODEL_CODE, m_FeeModelCode);
         rtn = invokeCommand( this, CMD_GUI_FEE_PARAMETER_SYSTEM, getProcessType(), isModal(), &_rpChildGI );
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
bool  FeeParamSysProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doModelessSetFocus") );

   bool bRtn = false;
   try
   {
      assert( _rpChildGI && isValidModelessInterface( _rpChildGI ) );
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
bool  FeeParamSysProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_FEE_PARAMETER_SYSTEM );
}
//******************************************************************************
void* FeeParamSysProcess::getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
   void *ptr = NULL;
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   try
   {
      if (idContainer == IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST ||
          idContainer == IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_THR_LIST)
      {
         FeeParamSys* pFeeParamSys = dynamic_cast<FeeParamSys*>(getCBOItem(IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, idDataGroup));
         if( pFeeParamSys )
         {
            DString dstrFeeType;
            pFeeParamSys->getField(ifds::ParamFeeType, dstrFeeType, idDataGroup, false);
            FeeScaleBaseList* pFeeScaleSysList = NULL;

            if(FEETYPE::TIER_BY_THRESHOLD == dstrFeeType ||
               FEETYPE::SCALE_BY_THRESHOLD == dstrFeeType)
            {
               FeeThrshldSys* pFeeThrshldSys = dynamic_cast<FeeThrshldSys*>(getCBOItem(IFASTBP_PROC::FEE_PARAM_SYSTEM_THRESHOLD_LIST, idDataGroup));
               pFeeThrshldSys->getFeeScaleSysList(pFeeScaleSysList, idDataGroup );
            }
            else
            {
               pFeeParamSys->getFeeScaleList( pFeeScaleSysList, idDataGroup,true );
            }
			
            ptr = pFeeScaleSysList;
         }
      }
      //if( IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST == idContainer )
      //{
      //   FeeParamSys *pFeeParamSys = dynamic_cast< FeeParamSys * >( getCBOItem( IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, idDataGroup ) );
      //   if( pFeeParamSys )
      //   {
      //      FeeScaleBaseList* pFeeScaleSysList;
      //      pFeeParamSys->getFeeScaleList( pFeeScaleSysList, idDataGroup,true );
      //      ptr = pFeeScaleSysList;
      //   }
      //}
      else if( IFASTBP_PROC::FEE_PARAM_SYSTEM_THRESHOLD_LIST == idContainer )
      {
         DString dstrFeeType;
         FeeParamSys *pFeeParamSys = dynamic_cast< FeeParamSys * >( getCBOItem( IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, idDataGroup ) );
         if( pFeeParamSys )
         {
            FeeThrshldSysList* pFeeThrshldSysList = NULL;
            pFeeParamSys->getField(ifds::ParamFeeType, dstrFeeType, idDataGroup, false);
            if(FEETYPE::TIER_BY_THRESHOLD == dstrFeeType ||
               FEETYPE::SCALE_BY_THRESHOLD == dstrFeeType)
            {
               pFeeParamSys->getFeeThresholdList(pFeeThrshldSysList, idDataGroup );
            }
            ptr = pFeeThrshldSysList;
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
bool FeeParamSysProcess::doRefresh(
                                  GenericInterface *rpGICaller,
                                  const I_CHAR *szOriginalCommand
                                  )
{
   return(_rpChildGI->refresh( this, NULL ));
}


//*****************************************************************************

SEVERITY FeeParamSysProcess::performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, 
                                            E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("performSearch") );
   SEVERITY sevRtn = SEVERE_ERROR;
   SEVERITY sevRtn1 = SEVERE_ERROR;

   try
   {
      if( eSearchAction == SEARCH_START && _pFeeParamSysSearchCriteria )
      {

		  sevRtn = _pFeeParamSysSearchCriteria->validateAll( getDataGroupId(), FEE_PARAM_VALIDATION_GROUP::FEE_PARAM_SEARCH  );

         if( sevRtn <= WARNING )
         {
            setContainer( IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST,NULL ); 
            sevRtn1=_pFeeParamSysSearchCriteria->GetFeeParamSysList(_pFeeParamSysList, getDataGroupId(),true,true,false,true );
            if( sevRtn1 <= WARNING && _pFeeParamSysList )
            {
                _pFeeParamSysList->setFromFeeModelCode(m_FeeModelCode);
                setContainer( IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, _pFeeParamSysList ); 
//				setDataFilter( IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, m_dstrBaseFilter);

            }
         }
      }
      else if( eSearchAction == SEARCH_NEXT_BLOCK )
      {

         sevRtn1 = _pFeeParamSysList->getMore();


      }
      sevRtn = sevRtn1 > sevRtn? sevRtn1:sevRtn;

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

bool FeeParamSysProcess::canUpdate()
{
   bool retVal = false;

   FeeParamSysList* pFeeParamSysList = dynamic_cast<FeeParamSysList*>(getCBOList(IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, getDataGroupId()));
   if(pFeeParamSysList)
   {
      const DString &crtKey = getCurrentListItemKey (this,IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST);
      retVal = pFeeParamSysList->canUpdateObject(crtKey, getDataGroupId());
   }

   return retVal;
}


//***********************************************************************************
bool FeeParamSysProcess::doMoreRecordsExist(GenericInterface *rpGICaller, const BFContainerId& idSearch)
{
   return(rpGICaller == NULL || _pFeeParamSysList == NULL ? false : 
          _pFeeParamSysList->doMoreRecordsExist());
}

//**************************************************************************************
bool FeeParamSysProcess::doOk(
                             GenericInterface *rpGICaller
                             )
{
   setParameter (CONFPROC::PARM_CALLED_FROM, I_("FeeParam"));
   if( _pFeeParamSysSearchCriteria )
      _pFeeParamSysSearchCriteria->clearUpdateFlags( getDataGroupId() );
   return(true);
}
//****************************************************************************************

void FeeParamSysProcess::doGetField(
                                   const GenericInterface *rpGICaller,
                                   const BFContainerId& idContainer,
                                   const BFFieldId& idField,
                                   const BFDataGroupId& idDataGroup,
                                   DString &strValueOut,
                                   bool bFormatted
                                   ) const
{

   if( idField ==  FEEPARAMSYS::HAS_OBJECT_UPDATE )
   {
      if( _pFeeParamSysList )
      {
         if( _pFeeParamSysList->isUpdatedForDataGroup( idDataGroup ) )
         {
            strValueOut = YES;
         }
         else
         {
            strValueOut = NO;
         }
      }
   }
   else if( idField == FEEPARAMSYS::IS_THE_SAME_BUSINESS_DATE )
   {

      FeeParamSys *pFeeParamSys = dynamic_cast< FeeParamSys * >(( const_cast < FeeParamSysProcess *> ( this ) )->getCBOItem( IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, idDataGroup ) );
      if( pFeeParamSys )
      {
         if( pFeeParamSys ->isTheSameBusinessDate(idDataGroup) )
            strValueOut = YES;
         else
            strValueOut = NO;
      }

   }
   else if( idField == FEEPARAMSYS::GET_DEFAULT_BRANCH_CODE )
   {
	  DString dstrBranchCode = NULL_STRING;	
      FeeParamSys *pFeeParamSys = dynamic_cast< FeeParamSys * >(( const_cast < FeeParamSysProcess *> ( this ) )->getCBOItem( IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, idDataGroup ) );
      if( pFeeParamSys )
      {
          pFeeParamSys ->getDefaultBranchCode(dstrBranchCode, idDataGroup);
          strValueOut = dstrBranchCode;
      }
	
   }
   else if( idField == FEEPARAMSYS::ALLOW_NEG_RATE )
   {
      FeeParamSys *pFeeParamSys = dynamic_cast< FeeParamSys * >(( const_cast < FeeParamSysProcess *> ( this ) )->getCBOItem( IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, idDataGroup ) );
      if( pFeeParamSys )
      {
          strValueOut = pFeeParamSys->allowNegRate(idDataGroup) ? I_("Y"):I_("N");
      }
   }
   else if( idField == ifds::BrokerName || idField == ifds::BranchName || idField == ifds::SlsrepName )
   {
      FeeParamSys *pFeeParamSys = dynamic_cast< FeeParamSys * >(( const_cast < FeeParamSysProcess *> ( this ) )->getCBOItem( IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, idDataGroup ) );
      if( pFeeParamSys )
      {
		 DString name;
         pFeeParamSys->getField(idField,   name, idDataGroup);
		 if(name.length() > 25 )
		 {
			name.stripAll('\n');
            strValueOut = name.left(25) + I_("\n");
			strValueOut += name.right( name.size() - 25 );
		 }
		 else
		 {
			strValueOut = name;
		 }
	  }
   }
   else
   {
      assert(0);
   }
}

//*****************************************************************************
SEVERITY  FeeParamSysProcess:: doSetField(
                                         const GenericInterface *rpGICaller,
                                         const BFContainerId& idContainer,
                                         const BFFieldId& idField,
                                         const BFDataGroupId& idDataGroup,
                                         const DString& strValue,
                                         bool bFormatted
                                         )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "doSetField" ) );

   if( idField == FEEPARAMSYS::RELOAD_OBJECT )
   {
      FeeParamSys *pFeeParamSys = dynamic_cast< FeeParamSys * >( getCBOItem( IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, idDataGroup ) );
      if( pFeeParamSys )
      {
         pFeeParamSys ->InitNew(idDataGroup);
      }

   }
   else
   {
      assert(0);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
SEVERITY FeeParamSysProcess::getHistoricalParameters(const BFContainerId& idContainer, 
                                                     BFFieldId &recordIdField, DString& tableId,
                                                     DString& dstrKeys) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS );

   if( idContainer == IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST )
   {
      recordIdField = ifds::FeeParamRid;
      tableId = AUDITTYPE::FEP;
      dstrKeys = NULL_STRING;
   }
   else if( idContainer == IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST )
   {
      recordIdField = ifds::ScaleDetlRid;
      tableId = AUDITTYPE::SCD;
      dstrKeys = NULL_STRING;
   }
   else if( idContainer == IFASTBP_PROC::FEE_PARAM_SYSTEM_THRESHOLD_LIST)
   {
      recordIdField = ifds::ThrshldRecID;
      tableId = AUDITTYPE::SCD;
      dstrKeys = NULL_STRING;
   }
   else if( idContainer == IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_THR_LIST)
   {
      recordIdField = ifds::ScaleDetlRid;
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

SEVERITY FeeParamSysProcess::getHistoricalParameters( 
   const BFContainerId& idContainer, 
   HISTORICAL_VECTOR &vectorHistorical )
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);
   return GETCURRENTHIGHESTSEVERITY();
}

bool FeeParamSysProcess::hasTransactionUpdates()
{
   BFDataGroupId idDataGroup = getDataGroupId();
   FeeParamSysList* pFeeParamSysList = dynamic_cast<FeeParamSysList*>(
      getCBOList(IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, idDataGroup));
   return pFeeParamSysList ? pFeeParamSysList->isUpdatedForDataGroup(idDataGroup) : false;
}

bool FeeParamSysProcess::doSend(GenericInterface *rpGICaller, const I_CHAR *szMessage) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "doSend" ) );

   DString str( szMessage );
   const BFDataGroupId& idDataGroup = getDataGroupId();

   if( str == I_("COPY_FEE_PARAM"))
   {
      const DString *crtKey = &getCurrentListItemKey (this,IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST);
      FeeParamSysList* pFeeParamSysList = dynamic_cast<FeeParamSysList*>(getCBOList(IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, idDataGroup));
      
      DString newKey;
      pFeeParamSysList->copyItem(*crtKey, idDataGroup,  newKey);
      setCurrentListItem(this,IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, newKey);
   }
   return  GETCURRENTHIGHESTSEVERITY() <= WARNING;
};

SEVERITY FeeParamSysProcess::ok2( GenericInterface *rpGICaller )
{
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, OK2 );
   //   BFSessionManager *rpBSM = BFSessionManager::getInstance();
   //   WorkSessionDetails *rpWSD =
   //      rpBSM->getWorkSessionDetails( getWorkSessionID() );
   BFWorkSession *bfWorkSession = getBFWorkSession();
   const BFDataGroupId& idDataGroup = getDataGroupId();
   bool bSuccessFlag = false;
   bool bNeedRefresh = false;
   bool bUpdated = false;
   // Allow subclass override if need to do other things prior to any ok2
   //  processing
   bool bContinue = true;
   if( doOk( rpGICaller ) )
   {
      if( bfWorkSession )
      {  // Only if work session details exists
         if( bfWorkSession->isUpdatedForDataGroup( idDataGroup ) )
         {
            bUpdated = true;
            //            if ( doValidateAll( bfWorkSession, idDataGroup ) <= WARNING )
            SEVERITY eRtn = doValidateAll( bfWorkSession, idDataGroup );
            if( eRtn == WARNING && !bfutil::isServerContext() )
            {
               bContinue = rpGICaller->send( rpGICaller, I_( "WarningConfirm" ) );
            }
            if( bContinue )
            {
               if( eRtn < WARNING || ( eRtn == WARNING && getIgnoreWarningsOnOk2() ) ) //ConfirmationProcess doesn't get launched if we got a warning
               {
                  //and bIgnoreWarningsOnOk2_ is set to false
                  bSuccessFlag = true;
               }
               else if( bfutil::isServerContext() )
               {  // for gui, errors get picked up directly from CBO's ?
                  PROMOTECONDITIONS();
               }
            } // if bContinue
         }
         else
         {  // Nothing happened - make sure and remove any dummy entries added
            bfWorkSession->deleteNonUpdatedAddedElements( idDataGroup );
            bSuccessFlag = true;
         }
      }
   }
   else
   {  // get doOK conditions, if any
      PROMOTECONDITIONS();
   }

   //no need to confirm and refresh if we've been used for support
   if( bfWorkSession && bSuccessFlag && getProcessType() != PROC_SUPPORT )
   {
      //if( ( bfutil::isServerContext() && !isModal() ) ||
      //   ( !bfutil::isServerContext() && (!getParent() || !getParent()->isModal() ) ) )
      {  // Possibly need confirmation if we are modeless, no parent, or our
      BFCPSession *pSession = getSession();
      BFAwdSession *rpAwdSession = NULL;

      if( pSession != NULL )
      {
         rpAwdSession = pSession->getAwdSession();
      }

      if( bUpdated && !ValidationControl::get().isValidateOnly() )
      {
         // this will commit *our* datagroup (i.e. this->getDataGroupId() )
         DString dstrCommitParentDataGroups;
         if(m_FeeModelCode != NULL_STRING)
         {
            if(m_HoldingCompCode != NULL_STRING)
            {
               dstrCommitParentDataGroups = I_("2");
            }
            else
            {
               dstrCommitParentDataGroups = I_("1");
            }
         }
         
         setParameter(CONFPROC::COMMIT_PARENT_DATA_GROUPS, dstrCommitParentDataGroups);
         if( CMD_OK != invokeCommand( this, CMD_BPROC_CONFIRMATION,
                                       PROC_NO_TYPE, true, NULL ) )
         {
            DString strOut;
            bSuccessFlag = false;
            PROMOTECONDITIONS();
            getParameter( I_( "TrxnsError" ), strOut );
            if( strOut == I_( "Y" ) )
            {  // Need to halt further activities in BaseMainDlg
               rpGICaller->send( this, I_( "TrxnsError" ) );
            }
         }
         else
         {  // Force refresh for now - but not needed for all cases
            bNeedRefresh = true;

            // if we are in "server mode" then make sure
            // that all errors get reported.
            if( bfutil::isServerContext() )
            {
               PROMOTECONDITIONS();
            }
         }
      }
      }
      if( bNeedRefresh )
      {
         getGIContainer()->refresh( this );
      }
   }

   if( bSuccessFlag )
   {
      return(NO_CONDITION);
   }
   return(SEVERE_ERROR);
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/FeeParamSysProcess.cpp-arc  $
// 
//    Rev 1.30   Dec 01 2011 00:17:48   popescu
// INA - Commission Work
// 
//    Rev 1.29   Oct 07 2011 07:49:48   kitticha
// PETP0186479 FN01 - IA Base Commission.
// 
//    Rev 1.28   Aug 13 2009 11:13:26   jankovii
// PET0164824 FN01 - Eiger iShares Orders and ETF Fields 
// 
//    Rev 1.27   Sep 01 2006 11:28:56   jankovii
// PET 2236 FN02 - Grandfathering Units for Trailer Purposes.
// 
//    Rev 1.26   Oct 25 2005 13:33:50   AGUILAAM
// PET1243_FN01_ABN AMRO Funds Trailer Fee Processing; additional enhancements (System Level Fee-Parms screen)
// 
//    Rev 1.25   Jun 10 2005 16:09:38   Fengyong
// #incident 288919 - show >40 chars broker name.
// 
//    Rev 1.24   Mar 10 2004 13:17:40   HERNANDO
// PET965 FN11 - Added getHistoricalParameters.
// 
//    Rev 1.23   Aug 18 2003 16:09:28   HERNANDO
// Added keys to getHistoricalParameters.
// 
//    Rev 1.22   Jun 20 2003 16:17:42   linmay
// sync with 1.19.1.2
// 
//    Rev 1.21   Jun 05 2003 14:49:50   linmay
// sync up with 1.19.1.1
// 
//    Rev 1.20   May 02 2003 14:42:26   linmay
// added field SlsRepCode, and BranchCode for search
// 
//    Rev 1.19   Mar 25 2003 14:49:26   linmay
// sync up
// 
//    Rev 1.18   Mar 25 2003 09:13:08   linmay
// fix bug
// 
//    Rev 1.17   Mar 21 2003 17:39:44   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.16   Mar 10 2003 15:05:34   linmay
// added new fields Branch...
// 
//    Rev 1.15   Mar 05 2003 11:22:36   PURDYECH
// IFastBaseProcess no longer exists.  Classes now derive from AbstractProcess (again) and the Protocol class IFastHistoricalParameters.
// 
//    Rev 1.14   Feb 07 2003 16:23:22   popescu
// Added the FeeParamRid fields to the scale list, as well
// 
//    Rev 1.13   Feb 05 2003 12:06:52   popescu
// Changes related to adding a new audit type id, for PAC/SWP and testing the FeeParam/Sys Historical button
// 
//    Rev 1.12   Jan 31 2003 09:32:52   linmay
// modified doSetField()
// 
//    Rev 1.11   Jan 29 2003 16:22:18   popescu
// Added the historical button for FeeParamSysDlg and FeeParamDlg
// 
//    Rev 1.10   Jan 21 2003 16:35:10   YINGBAOL
// do not delete pointer
// 
//    Rev 1.9   Jan 21 2003 16:18:46   linmay
// added fromfundnumber
// 
//    Rev 1.8   Jan 21 2003 16:10:02   YINGBAOL
// change getPtrforContainer
// 
//    Rev 1.7   Jan 19 2003 15:14:20   linmay
// modified getPtrForContainer
// 
//    Rev 1.6   Jan 18 2003 17:20:18   YINGBAOL
// implemet check update FeeParamSysList
// 
//    Rev 1.5   Jan 17 2003 18:06:12   linmay
// added feescalesysheadingset
// 
//    Rev 1.4   Jan 17 2003 14:14:38   YINGBAOL
// add FEE_PARAM_SEARCH and REMOVE FUND_GROUP_LIST
// 
//    Rev 1.3   Jan 15 2003 16:20:44   linmay
// added doOK(), modified performSearch()
// 
//    Rev 1.2   Jan 15 2003 11:53:18   linmay
// added log comment
// 
*/