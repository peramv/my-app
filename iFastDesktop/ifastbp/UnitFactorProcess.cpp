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
// ^FILE   : UnitFactorProcess.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : UnitFactorProcess
//    This class manages the management company and profile selection.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "UnitFactorProcess.hpp"
#include <ifastcbo\funddetaillist.hpp>
#include "UnitFactorProcessincludes.h"
#include <ifastcbo\fundlist.hpp>
#include <ifastcbo\fundmasterlist.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\FundPrices.hpp>
#include <ifastcbo\UnitFactorList.hpp>
#include <ifastcbo\UnitFactor.hpp>
#include <ifastdataimpl\dse_dstc0313_req.hpp>
#include <ifastdataimpl\dse_dstc0313_vw.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_FUNDINFO;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_UNITFACTORS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_FUND_FACTORS;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< UnitFactorProcess > processCreator( CMD_BPROC_UNITFACTORS );

namespace
{
   // Trace literals
   const I_CHAR *       CLASSNAME      = I_( "UnitFactorProcess" );
   const I_CHAR * const PERFORMSEARCH  = I_( "performSearch" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern CLASS_IMPORT const long BP_ERR_INVALID_METHOD_CALL;
}


//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319UnitFactorProcess::UnitFactorProcess() : 
UnitFactorProcess::UnitFactorProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pFundInfoList( NULL ),
_rpChildGI( NULL )

{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::FI_PROC_GEN_LIST, false );
   addContainer( IFASTBP_PROC::FI_FUND_INFO_LIST, true, BF::NullContainerId, true, I_("Fund_Info_List") );
   addContainer( IFASTBP_PROC::FI_FUND_MASTER_LIST, true, BF::NullContainerId, true, I_("Fund_Master_List") );
   addContainer( IFASTBP_PROC::UNIT_FACTORS_LIST, true /*Repeatable*/, BF::NullContainerId, true /*Updateable*/, I_("Unit_Factors_List") );

   addFieldDetails( ifds::FundCode       , IFASTBP_PROC::FI_PROC_GEN_LIST, SUBCLASS_PROCESS ),
   addFieldDetails( ifds::FromDate       , IFASTBP_PROC::FI_PROC_GEN_LIST, SUBCLASS_PROCESS ),
   addFieldDetails( ifds::ToDate         , IFASTBP_PROC::FI_PROC_GEN_LIST, SUBCLASS_PROCESS ),
   addFieldDetails( ifds::PrevDatePressed, IFASTBP_PROC::FI_PROC_GEN_LIST, SUBCLASS_PROCESS ),
   addFieldDetails( ifds::NextDatePressed, IFASTBP_PROC::FI_PROC_GEN_LIST, SUBCLASS_PROCESS ),
   addFieldDetails( ifds::NextKey        , IFASTBP_PROC::FI_PROC_GEN_LIST, SUBCLASS_PROCESS ),
   addFieldDetails( ifds::ValueAsAt      , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::rxFundCode     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::rxClassCode    , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::TransType      , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::RecordDate     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::ProcessDate    , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::ProcessTime    , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::ModDate        , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::Username       , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::ModUser        , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::Currency       , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::UnitValue      , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::UnitValue2     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::UnitValue3     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::UnitValue4     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::UnitValue5     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::UnitValue6     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::UnitValue7     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::UnitValue8     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::UnitValue9     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::UnitValue10     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::UnitValue11     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::UnitValue12     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::UnitValue13     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::ChgFactor2     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::ChgFactor3     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::ChgFactor4     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::ChgFactor5     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::ChgFactor6     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::ChgFactor7     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::ChgFactor8     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::ChgFactor9     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::ChgFactor10     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::ChgFactor11     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::ChgFactor12     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::ChgFactor13     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::PriceCode2     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::PriceCode3     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::PriceCode4     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::PriceCode5     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::PriceCode6     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::PriceCode7     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::PriceCode8     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::PriceCode9     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::PriceCode10     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::PriceCode11     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::PriceCode12     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::PriceCode13     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::UnAllocIncome  , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::Notional       , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::SkeletonBusYr  , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::GoodBad        , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::CanDividend    , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::InelgDividend  , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::CanInterest    , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::ForeignInterest, IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::ForeignDividend, IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::AccrualIncome  , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::MgmtFee        , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::TaxCapGain     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::ForeignTax     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::OthIncome      , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::RealizeGain    , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::TrusteeFee     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::EqualizationAmt, IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::PaidAmt        , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::ChgFactor      , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::FundLoadGrp    , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::ROC            , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::FundCode       , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::ClassCode      , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::UnitId         , IFASTBP_PROC::FI_FUND_INFO_LIST );

   addFieldDetails( ifds::FundCode       , IFASTBP_PROC::FI_FUND_MASTER_LIST );
   addFieldDetails( ifds::ElongName1     , IFASTBP_PROC::FI_FUND_MASTER_LIST );
   addFieldDetails( ifds::FundType       , IFASTBP_PROC::FI_FUND_MASTER_LIST );
   addFieldDetails( ifds::CusipNum       , IFASTBP_PROC::FI_FUND_MASTER_LIST );
   addFieldDetails( ifds::EffectiveDate  , IFASTBP_PROC::FI_FUND_MASTER_LIST );

   addFieldDetails( ifds::UnitFactor     , IFASTBP_PROC::UNIT_FACTORS_LIST );
   addFieldDetails( ifds::FactorRate     , IFASTBP_PROC::UNIT_FACTORS_LIST );
}

//******************************************************************************

UnitFactorProcess::~UnitFactorProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   delete _pFundInfoList;
   _pFundInfoList = NULL;
   _rpChildGI = NULL;

}

//******************************************************************************
//              Protected Methods
//******************************************************************************

//******************************************************************************

SEVERITY UnitFactorProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

   try
   {
      getParameter( FUND_CODE_VALUE,       _pFundCode);
      getParameter( CLASS_CODE_VALUE,      _pClassCode);
      getParameter( PREV_DATE_PRESSED_VALUE, _pPrevDatePressed);
      getParameter( NEXT_DATE_PRESSED_VALUE, _pNextDatePressed);
      getParameter( FROM_DATE_VALUE,         _pFromDate);
      getParameter( TO_DATE_VALUE,           _pToDate);

      if( _pPrevDatePressed == NULL_STRING )
      {
         _pPrevDatePressed = I_( "Y" );
      }
      if( _pNextDatePressed == NULL_STRING )
      {
         _pNextDatePressed = I_( "N" );
      }

      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      if( _pFromDate == NULL_STRING )
      {
         dstcWorkSession->getDateInHostFormat( _pFromDate,DSTCWorkSession::CURRENT_SYSTEM_DAY, getDataGroupId() );
      }
      if( _pToDate == NULL_STRING )
      {
         dstcWorkSession->getDateInHostFormat( _pToDate, DSTCWorkSession::CURRENT_SYSTEM_DAY, getDataGroupId() );
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

bool UnitFactorProcess::doModelessChildComplete( const Command &cmd )
{
   return( cmd.getKey() == CMD_GUI_FUND_FACTORS );
}

//******************************************************************************

bool UnitFactorProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
/*
   bool bRtn = false;
   bool lNeedSearchAgain = false;
   DString dslFundCode;
   DString dslClassCode;
   DString dslPrevDatePressed;
   DString dslNextDatePressed;
   DString dslFromDate;
   DString dslToDate;

   getParameter( FUND_CODE_VALUE,      dslFundCode);
   getParameter( CLASS_CODE_VALUE,       dslClassCode);
   getParameter( PREV_DATE_PRESSED_VALUE, dslPrevDatePressed);
   getParameter( NEXT_DATE_PRESSED_VALUE, dslNextDatePressed);
   getParameter( FROM_DATE_VALUE,         dslFromDate);
   getParameter( TO_DATE_VALUE,           dslToDate);

   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   if( dslFromDate == NULL_STRING )
   {
      dstcWorkSession->getDateInHostFormat( dslFromDate, DSTCWorkSession::CURRENT_SYSTEM_DAY, getDataGroupId() );
   }
   if( dslToDate == NULL_STRING )
   {
      dstcWorkSession->getDateInHostFormat( dslToDate, DSTCWorkSession::CURRENT_SYSTEM_DAY, getDataGroupId() );
   }

   if( dslFundCode != _pFundCode )
   {
      _pFundCode = dslFundCode;
      _pFundInfoList->setParameter( I_( "FundCode" ), _pFundCode );
      lNeedSearchAgain = true;
   }
   if( dslClassCode != _pClassCode )
   {
      _pClassCode = dslClassCode;
      _pFundInfoList->setParameter( I_( "ClassCode" ), _pClassCode);
      lNeedSearchAgain = true;
   }
   if( dslPrevDatePressed != NULL_STRING && dslPrevDatePressed != _pPrevDatePressed )
   {
      _pPrevDatePressed = dslPrevDatePressed; 
      _pFundInfoList->setParameter( I_( "PrevDatePressed" ), _pPrevDatePressed );
      lNeedSearchAgain = true;
   }
   if( dslNextDatePressed != NULL_STRING && dslNextDatePressed != _pNextDatePressed )
   {
      _pToDate = dslToDate;
      _pFundInfoList->setParameter( I_( "NextDatePressed" ), _pNextDatePressed );
      lNeedSearchAgain = true;
   }
   if( dslFromDate != NULL_STRING && dslFromDate != _pFromDate )
   {
      _pFromDate = dslFromDate;
      _pFundInfoList->setParameter( I_( "FromDate" ), _pFromDate );
      lNeedSearchAgain = true;
   }
   if( dslToDate != NULL_STRING && dslToDate != _pToDate )
   {
      _pToDate = dslToDate;
      _pFundInfoList->setParameter( I_( "ToDate" ), _pToDate );
      lNeedSearchAgain = true;
   }

   if( lNeedSearchAgain )
   {
      performSearch( this, BF::AllContainerIds, SEARCH_START );
   }

   if( _rpChildGI && isValidModelessInterface( _rpChildGI ) )
   {
      bRtn = _rpChildGI->refresh( this, NULL );
      bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
   }
   return(bRtn);
*/
return true;
}

//******************************************************************************

E_COMMANDRETURN UnitFactorProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      if( !bfutil::isServerContext() )
      {
		 rtn = invokeCommand( this, CMD_GUI_FUND_FACTORS, PROC_NO_TYPE, isModal(), &_rpChildGI);
				 GETCURRENTHIGHESTSEVERITY();
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

void *UnitFactorProcess::getPtrForContainer(
                                         const BFContainerId& idContainer,
                                         const BFDataGroupId& idDataGroup
                                         )
{
   void *ptr = NULL;
   SEVERITY sevRtn = NO_CONDITION;

   try
   {
      if( IFASTBP_PROC::FI_FUND_INFO_LIST == idContainer )
      {
         if( !_pFundInfoList )
         {
            _pFundInfoList = new FundList( *getBFWorkSession() );
            //get first 25 records
            sevRtn = _pFundInfoList->init( _pFundCode,
                                           _pClassCode, _pFromDate, _pToDate, _pPrevDatePressed,
                                           _pNextDatePressed );
            if( WARNING >= sevRtn )
            {
               ptr = _pFundInfoList;
            }
         }
      }
      else if( IFASTBP_PROC::FI_FUND_MASTER_LIST == idContainer )
      {
         {
            DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
            sevRtn = dstcWorkSession->getMgmtCo().getFundMasterList( _pFundMasterList );
            if( WARNING >= sevRtn )
            {
               ptr = _pFundMasterList;
            }
         }
      }
      else if( IFASTBP_PROC::UNIT_FACTORS_LIST == idContainer )
      {
         FundPrices *pFundPrices = dynamic_cast< FundPrices * >( getCBOItem(IFASTBP_PROC::FI_FUND_INFO_LIST, idDataGroup ) );
         DString dstrUnitId;

         if( pFundPrices )
         {
            pFundPrices->getField( ifds::UnitId, dstrUnitId, idDataGroup, false );
         }
         m_pUnitFactorsList = new UnitFactorList( *getBFWorkSession() );
         //get first 25 records
         sevRtn = m_pUnitFactorsList->init( dstrUnitId );
         if( WARNING >= sevRtn )
         {
            ptr = m_pUnitFactorsList;
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
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/UnitFactorProcess.cpp-arc  $
// 
//    Rev 1.0   Sep 09 2004 10:40:42   HERNANDO
// Initial revision.
 */
