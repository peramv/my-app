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
// ^FILE   : FundInfoProcess.cpp
// ^AUTHOR : 
// ^DATE   : 03/08/1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : FundInfoProcess
//    This class manages the management company and profile selection.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "fundinfoprocess.hpp"
#include <ifastcbo\FundDetail.hpp>
#include <ifastcbo\funddetaillist.hpp>
#include "fundinfoprocessincludes.h"
#include <ifastcbo\fundlist.hpp>
#include <ifastcbo\fundmaster.hpp>
#include <ifastcbo\fundmasterlist.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\mgmtcooptions.hpp>
#include <ifastcbo\fundprices.hpp>
#include <ifastcbo\unitfactorlist.hpp>
#include <ifastcbo\unitfactor.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_FUNDINFO;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FUNDINFO;
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_FUND_FACTORS;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< FundInfoProcess > processCreator( CMD_BPROC_FUNDINFO );

namespace
{
   // Trace literals
   const I_CHAR *       CLASSNAME      = I_( "FundInfoProcess" );
   const I_CHAR * const PERFORMSEARCH  = I_( "performSearch" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern CLASS_IMPORT const long BP_ERR_INVALID_METHOD_CALL;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId PriceProcAtFndGrp;
   extern CLASS_IMPORT const BFTextFieldId UFactorCodes;
   extern CLASS_IMPORT const BFTextFieldId ZeroDistributionAppl;
   extern CLASS_IMPORT const BFNumericFieldId AltFndIdntfr;
    extern CLASS_IMPORT const BFTextFieldId HasMultiplePrices;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319FundInfoProcess::FundInfoProcess() : 
FundInfoProcess::FundInfoProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pFundInfoList( NULL ),
_rpChildGI( NULL )

{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   addContainer( IFASTBP_PROC::FI_PROC_GEN_LIST, false );
   addContainer( IFASTBP_PROC::FI_FUND_INFO_LIST, true, BF::NullContainerId, true, I_("Fund_Info_List") );
   addContainer( IFASTBP_PROC::FI_FUND_MASTER_LIST, true, BF::NullContainerId, true, I_("Fund_Master_List") );
   addContainer( IFASTBP_PROC::FI_FUND_DETAIL_LIST, true, BF::NullContainerId, true, I_("Fund_Detail_List") );
   addContainer( IFASTBP_PROC::UNIT_FACTORS_LIST, true /*Repeatable*/, IFASTBP_PROC::FI_FUND_INFO_LIST, true /*Updateable*/, I_("Unit_Factors_List") );

   addFieldDetails( ifds::FundCode       , IFASTBP_PROC::FI_PROC_GEN_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::FromDate       , IFASTBP_PROC::FI_PROC_GEN_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::ToDate         , IFASTBP_PROC::FI_PROC_GEN_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::PrevDatePressed, IFASTBP_PROC::FI_PROC_GEN_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::NextDatePressed, IFASTBP_PROC::FI_PROC_GEN_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::NextKey        , IFASTBP_PROC::FI_PROC_GEN_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::ClassCode      , IFASTBP_PROC::FI_PROC_GEN_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::FundWKN        , IFASTBP_PROC::FI_PROC_GEN_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::FundISIN       , IFASTBP_PROC::FI_PROC_GEN_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::UFactorCodes   , IFASTBP_PROC::FI_PROC_GEN_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::Baycom         , IFASTBP_PROC::FI_PROC_GEN_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::CUSIP      , IFASTBP_PROC::FI_PROC_GEN_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::ValueAsAt      , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::rxFundCode     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::rxClassCode    , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::TransType      , IFASTBP_PROC::FI_FUND_INFO_LIST, SUBCLASS_PROCESS );
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
   //addFieldDetails( ifds::ClassCode      , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::FundWKN        , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::FundISIN       , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::FactorAmt1     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::FactorAmt2     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::FactorAmt3     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::FactorAmt4     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::FactorAmt5     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::ExDate         , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::PayDate        , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::ReInvDate      , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::DistributionType, IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::CusipNum       , IFASTBP_PROC::FI_FUND_INFO_LIST  , SUBCLASS_PROCESS );
   addFieldDetails( ifds::HasMultiplePrices, IFASTBP_PROC::FI_FUND_INFO_LIST, SUBCLASS_PROCESS);
   addFieldDetails( ifds::PriceProcAtFndGrp, BF::NullContainerId,   SUBCLASS_PROCESS);
   addFieldDetails( ifds::ZeroDistributionAppl, IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::GAV		     , IFASTBP_PROC::FI_FUND_INFO_LIST );
   addFieldDetails( ifds::FundCode       , IFASTBP_PROC::FI_FUND_MASTER_LIST );
   addFieldDetails( ifds::ElongName1     , IFASTBP_PROC::FI_FUND_MASTER_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::FundType       , IFASTBP_PROC::FI_FUND_MASTER_LIST );
   addFieldDetails( ifds::EffectiveDate  , IFASTBP_PROC::FI_FUND_MASTER_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::UnitFactor     , IFASTBP_PROC::UNIT_FACTORS_LIST );
   addFieldDetails( ifds::FactorRate     , IFASTBP_PROC::UNIT_FACTORS_LIST );
   addFieldDetails ( ifds::AltFndIdntfr, BF::NullContainerId, SUBCLASS_PROCESS );
/*
   addFieldDetails( ifds::FundCode       , IFASTBP_PROC::FI_FUND_DETAIL_LIST );
///   addFieldDetails( ifds::ClassCode      , IFASTBP_PROC::FI_FUND_DETAIL_LIST );
   addFieldDetails( ifds::EffectiveDate  , IFASTBP_PROC::FI_FUND_DETAIL_LIST );
   addFieldDetails( ifds::CusipNum       , IFASTBP_PROC::FI_FUND_DETAIL_LIST );
   addFieldDetails( ifds::Baycom         , IFASTBP_PROC::FI_FUND_DETAIL_LIST );
*/
}

//******************************************************************************

FundInfoProcess::~FundInfoProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   delete _pFundInfoList;
   _pFundInfoList = NULL;
   _rpChildGI = NULL;

}

//******************************************************************************
//              Protected Methods
//******************************************************************************

void FundInfoProcess::cboSetParameter(const DString& elementName, const DString& value )
{
   TRACE_METHOD( CLASSNAME, I_("SetParameter") );
   _pFundInfoList->setParameter(elementName, value);
}

//******************************************************************************

void FundInfoProcess::doGetField(
                                const GenericInterface *rpGICaller,
                                const BFContainerId& idContainer,
                                const BFFieldId& idField,
                                const BFDataGroupId& idDataGroup,
                                DString &strValueOut,
                                bool bFormatted
                                ) const
{
   if( idContainer == IFASTBP_PROC::FI_PROC_GEN_LIST )
   {
      if( idField == ifds::FundCode )
      {
         strValueOut = m_dstrFundCode;
      }
      else if( idField == ifds::ClassCode )
      {
         strValueOut = m_dstrClassCode;
      }
      else if( idField == ifds::FundWKN )
      {
         strValueOut = m_dstrFundWKN;
      }
      else if( idField == ifds::FundISIN )
      {
         strValueOut = m_dstrFundISIN;
      }
      else if( idField == ifds::ToDate )
      {
         strValueOut = m_dstrToDate;
      }
      else if( idField == ifds::UFactorCodes )
      {
         MgmtCoOptions *pMgmtCoOptions = NULL;
         DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
         SEVERITY sevRtn = dstcWorkSession->getMgmtCo().getMgmtCoOptions( pMgmtCoOptions );
         if( pMgmtCoOptions )
         {
            pMgmtCoOptions->getField( ifds::UFactorCodes, strValueOut, getDataGroupId(), false );
         }
      }
      else if( idField == ifds::Baycom )
      {
         DString dstrFundCode, dstrClassCode;
         const_cast< FundInfoProcess* >( this )->getField( rpGICaller, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::rxFundCode, dstrFundCode );
         const_cast< FundInfoProcess* >( this )->getField( rpGICaller, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::rxClassCode, dstrClassCode );
         dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->GetFundNumber( dstrFundCode, dstrClassCode, strValueOut );
      }
	  else if( idField == ifds::CUSIP)
	  {
		  strValueOut = m_dstrFundCUSIP;
	  }
   }
   else if( idContainer == IFASTBP_PROC::FI_FUND_MASTER_LIST )
   {
      if( idField == ifds::ElongName1 || idField == ifds::CusipNum || idField == ifds::EffectiveDate )
      {
         DString dstrFundCode;
         const_cast< FundInfoProcess* >( this )->getField( rpGICaller, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::rxFundCode, dstrFundCode );

         DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
         FundMasterList *pFundMasterList = NULL;
         SEVERITY sevRtn = dstcWorkSession->getMgmtCo().getFundMasterList( pFundMasterList );
         if( WARNING >= sevRtn )
         {
            //pFundMasterList->getFundName( dstrFundCode, idField, strValueOut, idDataGroup, bFormatted) ;
            FundMaster *pFundMaster = NULL;
            if (pFundMasterList->getFundMaster (dstrFundCode, idDataGroup, pFundMaster))
            {
               pFundMaster->getField (idField, strValueOut, idDataGroup, bFormatted);
            }
         }
      }
   }
   else if( idContainer == IFASTBP_PROC::FI_FUND_INFO_LIST )
   {
       if( idField == ifds::TransType )
       {
            //const_cast< FundInfoProcess* >( this )->getField( rpGICaller, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::rxFundCode, dstrFundCode );
            FundPrices* pInfo =  
                dynamic_cast<FundPrices*>( const_cast< FundInfoProcess*>( this )->getCBOItem( 
                IFASTBP_PROC::FI_FUND_INFO_LIST, idDataGroup ) );
            if( pInfo != NULL )
            {
                pInfo->getField(ifds::TransType,strValueOut,idDataGroup,false );
            }
       }
      if ( idField == ifds::CusipNum )
      {
         // Check the Fund Load group is entered instead of the class or not
         DString dstrPriceProcessAtFndGrp;
         DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
         dstcWorkSession->getOption( ifds::PriceProcAtFndGrp, dstrPriceProcessAtFndGrp, idDataGroup, false);
   
         DString  dstrFundCode,
                  dstrCusipNum;
         
         const_cast< FundInfoProcess* >( this )->getField( rpGICaller, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::rxFundCode, dstrFundCode );
         // If the PriceProcAtFndGrp is NO, There are fund and class fields.
         // Get cusip number from Fund-Detl before, after that if it is BLANK, try to get from Fund-Mstr
         if( dstrPriceProcessAtFndGrp.strip().upperCase() == I_("N") )         
         {
            DString dstrClassCode;
            const_cast< FundInfoProcess* >( this )->getField( rpGICaller, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::rxClassCode, dstrClassCode );
           
            FundDetail *pFundDetail = NULL;
            // get Fund Detail from Fund Detail List
            if(dstcWorkSession->getFundDetail ( dstrFundCode, dstrClassCode, BF::HOST, pFundDetail ) && pFundDetail)
            {
               pFundDetail->getField(ifds::CusipNum, dstrCusipNum, idDataGroup, false);
            }
         }
         /* 
            There are 2 cases for next condition,
            case1 PriceProcAtFndGrp is YES. There are fund and group fields.
            case2 PriceProcAtFndGrp is NO but cusip number is BLANK at Fund-Detl.
         */
         if( ( dstrPriceProcessAtFndGrp.strip().upperCase() == I_("Y")) ||
               dstrCusipNum.strip().upperCase() == NULL_STRING
              )
         {
            FundMasterList *pFundMasterList = NULL;
      
            if( dstcWorkSession->getMgmtCo().getFundMasterList ( pFundMasterList ) <= WARNING )
            {
               FundMaster *pFundMaster = NULL;
               if (pFundMasterList->getFundMaster (dstrFundCode, idDataGroup, pFundMaster))
               {
                  // get cusip number from fund master
                  pFundMaster->getField (ifds::CusipNum, dstrCusipNum, idDataGroup, false);
               }         
            }         
         }
         strValueOut = dstrCusipNum;   // sent out the value
         
      }  // end cusip number
      else if (idField == ifds::HasMultiplePrices)
      {
          bool hasMultiplePrices = false;
          FundPrices *pFundPrices = NULL;
          
          pFundPrices = dynamic_cast<FundPrices*>(const_cast<FundInfoProcess*>(this)->getCBOItem(IFASTBP_PROC::FI_FUND_INFO_LIST, idDataGroup));
          
          if (pFundPrices)
              hasMultiplePrices = pFundPrices->hasMultiplePrices(idDataGroup);

          strValueOut = hasMultiplePrices ? I_("Y") : I_("N");
      }
      
   }  // end FI_FUND_INFO_LIST
   else if (idContainer == BF::NullContainerId && idField == ifds::AltFndIdntfr)
   {
	  DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *> (getBFWorkSession());
      DString dstrAltFndIdntfr;
      pDSTCWorkSession->getOption(ifds::AltFndIdntfr, dstrAltFndIdntfr, BF::HOST, false);
      
      strValueOut = dstrAltFndIdntfr == I_("") || dstrAltFndIdntfr == I_("0") ? I_("0") : dstrAltFndIdntfr;
   }
   else  // Null Container Id
   {
      if( idField == ifds::PriceProcAtFndGrp )
      {
         DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
         dstcWorkSession->getOption( idField, strValueOut, idDataGroup, bFormatted);
      }
      else
      {
         assert( 0 );   
         THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETFIELD,
                         CND::BP_ERR_INVALID_METHOD_CALL );
      }
   }
}

//******************************************************************************

SEVERITY FundInfoProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

   try
   {
      DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   
      getParameter( FUND_CODE_VALUE,       m_dstrFundCode);
      getParameter( CLASS_CODE_VALUE,      m_dstrClassCode);
      getParameter( PREV_DATE_PRESSED_VALUE, m_dstrPrevDatePressed);
      getParameter( NEXT_DATE_PRESSED_VALUE, m_dstrNextDatePressed);
      getParameter( FROM_DATE_VALUE,         m_dstrFromDate);
      getParameter( TO_DATE_VALUE,           m_dstrToDate);

      if (m_dstrPrevDatePressed.empty())
      {
         m_dstrPrevDatePressed = I_("Y");
      }
      if (m_dstrNextDatePressed.empty())
      {
         m_dstrNextDatePressed = I_("N");
      }
      if (m_dstrFromDate.empty())
      {
         pDSTCWorkSession->getDateInHostFormat (
               m_dstrFromDate, 
               DSTCWorkSession::CURRENT_SYSTEM_DAY, 
               getDataGroupId());
      }
      if (m_dstrToDate.empty())
      {
         pDSTCWorkSession->getDateInHostFormat (
            m_dstrToDate, 
            DSTCWorkSession::CURRENT_SYSTEM_DAY, 
            getDataGroupId() );
      }
      _pFundInfoList = new FundList (*getBFWorkSession());
      if (_pFundInfoList->init( 
            m_dstrFundCode,
            m_dstrClassCode, 
            m_dstrFromDate, 
            m_dstrToDate, 
            m_dstrPrevDatePressed,
            m_dstrNextDatePressed) <= WARNING)
      {
         setContainer (IFASTBP_PROC::FI_FUND_INFO_LIST, 
            _pFundInfoList);
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
bool FundInfoProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_FUNDINFO );
}

//******************************************************************************
bool FundInfoProcess::doSend (GenericInterface* rpGICaller, 
	const I_CHAR * szMessage)
{
    MAKEFRAME2(CND::BPBASE_CONDITION, CLASSNAME, I_("doSend") );
    bool bRtn = false;

    try
    {
        if (DString (szMessage) == I_("Factors"))
		{
			E_COMMANDRETURN rtn = invokeCommand (this, 
				CMD_GUI_FUND_FACTORS, 
				PROC_NO_TYPE, true, NULL);

            bRtn = rtn == CMD_OK || 
				rtn == CMD_CANCEL || 
				rtn == CMD_MODELESS_INPROCESS;
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
        THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
    }
	return bRtn;
}

//******************************************************************************
bool FundInfoProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
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

   if( dslFundCode != m_dstrFundCode )
   {
      m_dstrFundCode = dslFundCode;
      _pFundInfoList->setParameter( I_( "FundCode" ), m_dstrFundCode );
      lNeedSearchAgain = true;
   }
   if( dslClassCode != m_dstrClassCode )
   {
      m_dstrClassCode = dslClassCode;
      _pFundInfoList->setParameter( I_( "ClassCode" ), m_dstrClassCode);
      lNeedSearchAgain = true;
   }
   if( dslPrevDatePressed != NULL_STRING && dslPrevDatePressed != m_dstrPrevDatePressed )
   {
      m_dstrPrevDatePressed = dslPrevDatePressed; 
      _pFundInfoList->setParameter( I_( "PrevDatePressed" ), m_dstrPrevDatePressed );
      lNeedSearchAgain = true;
   }
   if( dslNextDatePressed != NULL_STRING && dslNextDatePressed != m_dstrNextDatePressed )
   {
      m_dstrToDate = dslToDate;
      _pFundInfoList->setParameter( I_( "NextDatePressed" ), m_dstrNextDatePressed );
      lNeedSearchAgain = true;
   }
   if( dslFromDate != NULL_STRING && dslFromDate != m_dstrFromDate )
   {
      m_dstrFromDate = dslFromDate;
      _pFundInfoList->setParameter( I_( "FromDate" ), m_dstrFromDate );
      lNeedSearchAgain = true;
   }
   if( dslToDate != NULL_STRING && dslToDate != m_dstrToDate )
   {
      m_dstrToDate = dslToDate;
      _pFundInfoList->setParameter( I_( "ToDate" ), m_dstrToDate );
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
}

//******************************************************************************

bool FundInfoProcess::doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch )
{
   return(rpGICaller == NULL || _pFundInfoList == NULL ? false : 
          _pFundInfoList->doMoreRecordsExist());
}

//******************************************************************************

E_COMMANDRETURN FundInfoProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      if( !bfutil::isServerContext() )
      {  // invoke GUI command if not server context
		 rtn = invokeCommand( this, CMD_GUI_FUNDINFO, PROC_NO_TYPE, isModal(), &_rpChildGI);
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

SEVERITY  FundInfoProcess::doSetField(
                                     const GenericInterface *rpGICaller,
                                     const BFContainerId& idContainer,
                                     const BFFieldId& idField,
                                     const BFDataGroupId& idDataGroup,
                                     const DString& strValue,
                                     bool bFormatted
                                     )
{
   SEVERITY sevRtn = NO_CONDITION;

   if( idField == ifds::FundCode )
      cboSetParameter(I_( "FundCode" ), m_dstrFundCode = strValue);
   if( idField == ifds::FromDate )
      cboSetParameter(I_( "FromDate" ), m_dstrFromDate = strValue);
   if( idField == ifds::ToDate )
      cboSetParameter(I_( "ToDate" ), m_dstrToDate = strValue);
   if( idField == ifds::PrevDatePressed )
      cboSetParameter(I_( "PrevDatePressed" ), m_dstrPrevDatePressed = strValue);
   if( idField == ifds::NextDatePressed )
      cboSetParameter(I_( "NextDatePressed" ), m_dstrNextDatePressed = strValue);
   if( idField == ifds::NextKey )
      cboSetParameter(I_( "NextKey" ), strValue);
   if( idField == ifds::ClassCode )
      cboSetParameter(I_("ClassCode"), m_dstrClassCode = strValue);
   if( idField == ifds::FundISIN )
      cboSetParameter(I_("FundISIN"), m_dstrFundISIN = strValue);
   if( idField == ifds::FundWKN )
      cboSetParameter(I_("FundWKN"), m_dstrFundWKN = strValue);
   if( idField == ifds::CUSIP )
	   cboSetParameter(I_("CUSIP"), m_dstrFundCUSIP = strValue);
   return(sevRtn);
}

//******************************************************************************

SEVERITY FundInfoProcess::performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, 
                                         E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, PERFORMSEARCH );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
// if we remove create from init do we need a separate method to create & init to be called
// here and from getPtrFromContainer?  (In other words, is it feasible to do a performSearch
// prior to any other list operations? I would think it's possible. )
      if (_pFundInfoList != NULL && rpGI != NULL)
      {
         setContainer (IFASTBP_PROC::FI_FUND_INFO_LIST, NULL);
         sevRtn = _pFundInfoList->search (eSearchAction == SEARCH_START);
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, PERFORMSEARCH, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(sevRtn); 
}

//******************************************************************************

void *FundInfoProcess::getPtrForContainer ( const BFContainerId& idContainer,
                                            const BFDataGroupId& idDataGroup)
{
   void *ptr = NULL;
   DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   try
   {  
      if (IFASTBP_PROC::FI_FUND_INFO_LIST == idContainer)
      {
         ptr = _pFundInfoList;
      }
      else if (IFASTBP_PROC::FI_FUND_MASTER_LIST == idContainer)
      {
         if (pDSTCWorkSession->getMgmtCo().getFundMasterList( _pFundMasterList ) <= WARNING)
         {
            ptr = _pFundMasterList;
         }
      }
      else if (IFASTBP_PROC::FI_FUND_DETAIL_LIST == idContainer)
      {
         if( pDSTCWorkSession->getMgmtCo().getFundDetailList( _pFundDetailList ) <= WARNING)
         {
            ptr = _pFundDetailList;
         }
      }
      else if (IFASTBP_PROC::UNIT_FACTORS_LIST == idContainer)
      {
         FundPrices *pFundPrices = 
               dynamic_cast< FundPrices * >(getCBOItem(IFASTBP_PROC::FI_FUND_INFO_LIST, idDataGroup));
         UnitFactorList *pUnitFactorsList = NULL;
         
         if (pFundPrices && 
            pFundPrices->getUnitFactorsList (pUnitFactorsList, idDataGroup) <= WARNING)
         {
            ptr = pUnitFactorsList;
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
   return ptr;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/FundInfoProcess.cpp-arc  $
 * 
 *    Rev 1.27   Aug 10 2012 20:26:32   wp040133
 * ESS_P01999461_FN01_ARROW_Distribution Enhancement
 * Adding new field got from vw 23 (DistributionType) to the FundInfo Process
 * 
 *    Rev 1.26   Oct 20 2009 06:41:18   kitticha
 * REL97 IN#1814672 - the CUSIP values are missing Ver3.
 * 
 *    Rev 1.23   Jan 03 2008 18:22:14   daechach
 * IN#1137953 - Issue # 2 - Fund Information Unit Value screen displayed TransType has to be consistence
 * 
 *    Rev 1.22   Dec 06 2007 19:41:00   smithdav
 * PET1200 FN02 - Dividend Processing enhancement.
 * 
 *    Rev 1.21   Mar 20 2007 10:53:04   popescu
 * Incident# 847324 - issue with the Fund info screen.
 * 
 *    Rev 1.20   Nov 17 2004 15:18:48   popescu
 * PET 1117/56, removed 'getField' method at the fund master list level, 
 * 
 *    Rev 1.19   Sep 17 2004 14:03:08   popescu
 * PET1117 FN22 - no need to reset and set the container, since the search is done in the CBO list itself.
 * 
 *    Rev 1.18   Sep 17 2004 13:38:36   popescu
 * PET1117 FN22 - revert fund factors dialog display to old logic
 * 
 *    Rev 1.17   Sep 09 2004 14:44:30   HERNANDO
 * PET1117 FN22 - Fund Number added to list display.
 * 
 *    Rev 1.16   Sep 09 2004 11:34:08   HERNANDO
 * PET1117 FN22 - WKN & ISIN Enhancement.
 * 
 *    Rev 1.15   Nov 20 2003 16:31:50   AGUILAAM
 * PET859_FN17: added factors screen - daily equalization.
 * 
 *    Rev 1.14   Oct 16 2003 16:31:44   FENGYONG
 * Inquiry API enhance
 * 
 *    Rev 1.13   Mar 21 2003 17:40:26   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.12   Oct 09 2002 23:53:16   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.11   Aug 29 2002 16:44:56   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.10   Aug 29 2002 12:54:22   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.9   22 May 2002 18:24:16   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.8   27 Mar 2002 19:54:52   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.7   Mar 21 2002 13:26:06   YINGBAOL
 * add Group logic
 * 
 *    Rev 1.6   03 May 2001 14:05:24   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.5   15 Dec 2000 12:43:30   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.4   Nov 03 2000 11:31:42   YINGBAOL
 * BFBase change sync.
 * 
 *    Rev 1.3   Aug 02 2000 15:32:02   BUZILA
 * "locale" changes
 * 
 *    Rev 1.2   Jun 13 2000 09:16:12   DT24433
 * use getDateInHostFormat, cleanup
 * 
 *    Rev 1.1   Mar 13 2000 17:27:44   HSUCHIN
 * C2 sync up
 * 
 *    Rev 1.0   Feb 15 2000 10:59:34   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.16   Dec 08 1999 12:16:10   BUZILA
 * added idDataGroup parameter to doGetField and doSetField
 * 
 *    Rev 1.15   Dec 04 1999 15:17:44   BUZILA
 * fix
 * 
 *    Rev 1.14   Dec 03 1999 20:33:26   BUZILA
 * fix search again
 * 
 *    Rev 1.13   Nov 06 1999 16:38:28   BUZILA
 * fix getPtrForContainer(...)
 * 
 *    Rev 1.12   Oct 29 1999 10:13:50   DT24433
 * removed doOk/doCancel
 * 
 *    Rev 1.11   Sep 30 1999 13:32:58   VASILEAD
 * Added fields in the process
 * 
 *    Rev 1.10   Aug 30 1999 19:03:06   DT24433
 * changed dogetfield/dosetfield parms
 * 
 *    Rev 1.9   Aug 26 1999 15:25:08   BUZILA
 * Fix date parameters
 * 
 *    Rev 1.8   Aug 09 1999 17:10:48   BUZILA
 * fixed list IDs
 * 
 *    Rev 1.7   Aug 06 1999 10:06:12   DT24433
 * handle ConditionException in getPtrForContainer
 * 
 *    Rev 1.6   Aug 05 1999 14:21:06   DT24433
 * container changes and lazy initialization
 * 
 *    Rev 1.5   Aug 04 1999 16:08:44   BUZILA
 * field ChgFactor introduced
 * 
 *    Rev 1.4   Aug 03 1999 17:19:10   BUZILA
 * init date
 * 
 *    Rev 1.3   Jul 20 1999 11:14:04   VASILEAD
 * New conditions update
 * 
 *    Rev 1.2   Jul 15 1999 16:39:26   BUZILA
 * Fixing Mgmt Detail
 * 
 *    Rev 1.1   Jul 08 1999 10:02:02   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
