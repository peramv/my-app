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
// ^FILE   : FeeModelProcess.cpp
// ^AUTHOR : 
// ^DATE   : July 21, 2004  
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : FeeModelProcess
//    This class manages the address book process.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "FeeModelProcessinclude.h"
#include "FeeModelProcess.hpp"
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\feeModellist.hpp>
#include <ifastcbo\feeModel.hpp>
#include "mfcaninterprocparam.hpp"
#include <ifastcbo\mgmtco.hpp>
#include "confirmationprocessincludes.h"
#include <ifastcbo\feemodellist.hpp>
#include <ifastcbo\mgmtcooptions.hpp>
#include <ifastcbo\feemodelsearchcriteria.hpp>
#include <bfproc\genericinterfacecontainer.hpp>
#include <bfcbo\validationcontrol.hpp>
#include <ifastcbo\feemodelsetuplist.hpp>
#include <bfsessn\bfcpsession.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_FEE_MODEL;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FEE_MODEL;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< FeeModelProcess > processCreator( CMD_BPROC_FEE_MODEL );

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "FeeModelProcess" );
}

namespace FEEMODEL
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
   extern CLASS_IMPORT const BFTextFieldId FeeModelCode;
   extern CLASS_IMPORT const BFTextFieldId FeeModelDesc;
   extern CLASS_IMPORT const BFTextFieldId Username;
   extern CLASS_IMPORT const BFTextFieldId ModUser;

   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFDateFieldId StopDate;
   extern CLASS_IMPORT const BFDateFieldId ProcessDate;
   extern CLASS_IMPORT const BFDateFieldId ModDate;
   extern CLASS_IMPORT const BFTextFieldId FeeModelType;
   extern CLASS_IMPORT const BFTextFieldId FeeModelTypeCode;
   extern CLASS_IMPORT const BFDateFieldId LastProcDate;
   extern CLASS_IMPORT const BFTextFieldId AllowCopy;
   extern CLASS_IMPORT const BFTextFieldId SameDlrBrnRep;
   extern CLASS_IMPORT const BFIntegerFieldId FullMoneyOutApplicable;
}
namespace AUDITTYPE
{
   extern CLASS_IMPORT I_CHAR * const FEE_MODEL;
}

namespace FEEMOD_FLDS
{
   extern CLASS_EXPORT const BFFieldId FROM_HOLDCOMP (101);
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319FeeModelProcess::FeeModelProcess() 
FeeModelProcess::FeeModelProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand ),
_rpChildGI( NULL ),
m_dispNum( 0 ),  
m_More( 0 ),  
m_totalNum( 0 ),  
m_dstrEndKey( NULL ),	
m_dstrEmptykey(NULL),  
m_pFeeModelSearchCriteria(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, I_( "FeeModelProcess" ) );

   addFieldDetails( FEEMOD_FLDS::FROM_HOLDCOMP, BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails( ifds::HoldingCompCode,      BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails( ifds::SchedSetupFreqAppl,   BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails( ifds::CalcRateTypeList,     BF::NullContainerId, SUBCLASS_PROCESS);

   addFieldDetails( ifds::HoldingEntityAppl,    BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails( ifds::CalcCurrencyAppl,     BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails( ifds::FundGroupType,        BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails( ifds::FundGrpTypeList,      BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails( ifds::AggregationMethodList, BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails( ifds::FeeModelOptionList,   BF::NullContainerId, SUBCLASS_PROCESS);



   addContainer( IFASTBP_PROC::FEE_MODEL_LIST, true, BF::NullContainerId, true, I_("FeeModel") );
   addContainer( IFASTBP_PROC::FEE_MODEL_SEARCH, false, BF::NullContainerId, true, I_("FeeModelSearch") );

   addFieldDetails( ifds::SrcHoldingCompCode, IFASTBP_PROC::FEE_MODEL_SEARCH);
   addFieldDetails( ifds::SrcHoldingCompName, IFASTBP_PROC::FEE_MODEL_SEARCH);
   addFieldDetails( ifds::SrcFeeModelCode,    IFASTBP_PROC::FEE_MODEL_SEARCH);
   addFieldDetails( ifds::SrcFeeModelDesc,    IFASTBP_PROC::FEE_MODEL_SEARCH);
   addFieldDetails( ifds::AsofDate,           IFASTBP_PROC::FEE_MODEL_SEARCH);
   addFieldDetails( ifds::SearchAll,          IFASTBP_PROC::FEE_MODEL_SEARCH);
   addFieldDetails( ifds::HoldingCompCode,    IFASTBP_PROC::FEE_MODEL_SEARCH);
   addFieldDetails( ifds::HoldingCompName,    IFASTBP_PROC::FEE_MODEL_SEARCH);

   addFieldDetails( ifds::FeeModelCode,   IFASTBP_PROC::FEE_MODEL_LIST );
   addFieldDetails( ifds::FeeModelDesc,   IFASTBP_PROC::FEE_MODEL_LIST );
   addFieldDetails( ifds::FeeModelType,   IFASTBP_PROC::FEE_MODEL_LIST );
   addFieldDetails( ifds::EffectiveDate,  IFASTBP_PROC::FEE_MODEL_LIST );
   addFieldDetails( ifds::StopDate,       IFASTBP_PROC::FEE_MODEL_LIST );
   addFieldDetails( ifds::ProcessDate,    IFASTBP_PROC::FEE_MODEL_LIST );
   addFieldDetails( ifds::ModDate,        IFASTBP_PROC::FEE_MODEL_LIST );
   addFieldDetails( ifds::Username,       IFASTBP_PROC::FEE_MODEL_LIST );
   addFieldDetails( ifds::ModUser,        IFASTBP_PROC::FEE_MODEL_LIST );

   addFieldDetails( ifds::HoldingCompCode,   IFASTBP_PROC::FEE_MODEL_LIST );     
   addFieldDetails( ifds::Program,           IFASTBP_PROC::FEE_MODEL_LIST );     
   addFieldDetails( ifds::CalcCurrency,      IFASTBP_PROC::FEE_MODEL_LIST );     
   addFieldDetails( ifds::EligibleFundBy,    IFASTBP_PROC::FEE_MODEL_LIST );     
   addFieldDetails( ifds::FeeModelFundGroup, IFASTBP_PROC::FEE_MODEL_LIST );     
   addFieldDetails( ifds::ModelAggregationMethod, IFASTBP_PROC::FEE_MODEL_LIST );     
   addFieldDetails( ifds::ScheduleFreqID,    IFASTBP_PROC::FEE_MODEL_LIST );     
   addFieldDetails( ifds::CalcRateType,      IFASTBP_PROC::FEE_MODEL_LIST );     
   addFieldDetails( ifds::FeeModelRecid,     IFASTBP_PROC::FEE_MODEL_LIST );     
   addFieldDetails( ifds::FeeModelTypeCode,  IFASTBP_PROC::FEE_MODEL_LIST );     
   addFieldDetails( ifds::LastProcDate,      IFASTBP_PROC::FEE_MODEL_LIST );     
   addFieldDetails( ifds::FullMoneyOutApplicable, IFASTBP_PROC::FEE_MODEL_LIST );
   addFieldDetails( ifds::AllowCopy,         IFASTBP_PROC::FEE_MODEL_LIST );
   addFieldDetails( ifds::SameDlrBrnRep,     IFASTBP_PROC::FEE_MODEL_LIST );
}

//******************************************************************************
FeeModelProcess::~FeeModelProcess()
{
   //TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY FeeModelProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

   try
   {
      getParent()->getParameter( MFCAN_IP_PARAM::SEARCH_TYPE, m_frSCR );
      m_frSCR.strip();
      
      getParameter(MFCAN_IP_PARAM::HOLDING_COMP_CODE, m_HoldingCompCode);
      getParameter(MFCAN_IP_PARAM::HOLDING_COMP_NAME, m_HoldingCompName);
      m_SrcHoldingCompCode = m_HoldingCompCode;
      m_SrcHoldingCompName = m_HoldingCompName;

      if(!m_pFeeModelSearchCriteria)
      {
         m_pFeeModelSearchCriteria = new FeeModelSearchCriteria(*getBFWorkSession());
         if(m_HoldingCompCode != I_(""))
         {
            m_pFeeModelSearchCriteria->setFieldReadOnly(ifds::SrcHoldingCompCode, BF::HOST, true);
            m_pFeeModelSearchCriteria->setFieldReadOnly(ifds::SrcHoldingCompName, BF::HOST, true);
         }
         setContainer( IFASTBP_PROC::FEE_MODEL_SEARCH, m_pFeeModelSearchCriteria);
      }
      //      setContainer( IFASTBP_PROC::FEE_MODEL_LIST, new FeeModelList(*getBFWorkSession()) ); 

      m_pFeeModelSearchCriteria->setField(ifds::SearchAll, I_("N"), BF::HOST, false);

      DString dstrCurBusDate;
      DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
	   dstWorkSession->getMgmtCoOptions()->getField(ifds::CurrBusDate, dstrCurBusDate, BF::HOST);
      dstrCurBusDate.strip();
      m_AsofDate = dstrCurBusDate;
      m_pFeeModelSearchCriteria->setField(ifds::AsofDate, dstrCurBusDate, BF::HOST, false);


      m_pFeeModelSearchCriteria->setField(ifds::SrcHoldingCompCode, m_HoldingCompCode, BF::HOST, false);
      m_pFeeModelSearchCriteria->setField(ifds::SrcHoldingCompName, m_HoldingCompName, BF::HOST, false); 
         
      DString dstrSrcHoldingCompCode;
      DString dstrSrcHoldingCompName; 
      DString dstrSrcFeeModelCode; 
      DString dstrSrcFeeModelDesc; 
      DString dstrSearchAll; 
      DString dstrAsofDate;

      m_pFeeModelSearchCriteria->getField(ifds::SrcHoldingCompCode, dstrSrcHoldingCompCode, BF::HOST, false);
      m_pFeeModelSearchCriteria->getField(ifds::SrcHoldingCompName, dstrSrcHoldingCompName, BF::HOST, false);
      m_pFeeModelSearchCriteria->getField(ifds::SrcFeeModelCode   , dstrSrcFeeModelCode   , BF::HOST, false);
      m_pFeeModelSearchCriteria->getField(ifds::SrcFeeModelDesc   , dstrSrcFeeModelDesc   , BF::HOST, false);
      m_pFeeModelSearchCriteria->getField(ifds::SearchAll         , dstrSearchAll         , BF::HOST, false);
      m_pFeeModelSearchCriteria->getField(ifds::AsofDate          , dstrAsofDate          , BF::HOST, false);

      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      if( dstcWorkSession->getFeeModelList( _pFeeModelList, getDataGroupId(), 
               dstrSrcHoldingCompCode, dstrSrcHoldingCompName, dstrSrcFeeModelCode, 
               dstrSrcFeeModelDesc, dstrSearchAll, dstrAsofDate, true, false) <= WARNING )
      {
         if(m_HoldingCompCode != I_(""))
         {
            _pFeeModelList->setFromHoldingCompany(m_HoldingCompCode, BF::HOST);
         }
         setContainer( IFASTBP_PROC::FEE_MODEL_LIST, _pFeeModelList ); 
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
E_COMMANDRETURN FeeModelProcess::doProcess()
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
         setParameter( FEEMODEL::FROM_SCR, m_frSCR );
         rtn = invokeCommand( this, CMD_GUI_FEE_MODEL, getProcessType(), isModal(), &_rpChildGI );
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
bool  FeeModelProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
   bool bRtn = false;

   try
   {
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
bool  FeeModelProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_FEE_MODEL );
}
//******************************************************************************
/*
void* FeeModelProcess::getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
   void *ptr = NULL;
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   try
   {
      ptr = AbstractProcess::getPtrForContainer(idContainer, idDataGroup);
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
*/
//******************************************************************************
bool FeeModelProcess::doRefresh(
                               GenericInterface *rpGICaller,
                               const I_CHAR *szOriginalCommand
                               )
{
   return(_rpChildGI->refresh( this, NULL ));
}

//*****************************************************************************
SEVERITY FeeModelProcess::performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, 
                                         E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("performSearch") );
   SEVERITY sevRtn = NO_CONDITION;

   switch( eSearchAction )
   {
      case SEARCH_START:
         {

//            setContainer( IFASTBP_PROC::FEE_MODEL_LIST, NULL); 
            BFDataGroupId dataGroupId = getDataGroupId();
            DString dstrSrcHoldingCompCode;
            DString dstrSrcHoldingCompName; 
            DString dstrSrcFeeModelCode; 
            DString dstrSrcFeeModelDesc; 
            DString dstrSearchAll; 
            DString dstrAsofDate;

            m_pFeeModelSearchCriteria->getField(ifds::SrcHoldingCompCode, dstrSrcHoldingCompCode, dataGroupId, false);
            m_pFeeModelSearchCriteria->getField(ifds::SrcHoldingCompName, dstrSrcHoldingCompName, dataGroupId, false);
            m_pFeeModelSearchCriteria->getField(ifds::SrcFeeModelCode   , dstrSrcFeeModelCode   , dataGroupId, false);
            m_pFeeModelSearchCriteria->getField(ifds::SrcFeeModelDesc   , dstrSrcFeeModelDesc   , dataGroupId, false);
            m_pFeeModelSearchCriteria->getField(ifds::SearchAll         , dstrSearchAll         , dataGroupId, false);
            m_pFeeModelSearchCriteria->getField(ifds::AsofDate          , dstrAsofDate          , dataGroupId, false);

            DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
            dstcWorkSession->getFeeModelList( _pFeeModelList, dataGroupId, dstrSrcHoldingCompCode, 
               dstrSrcHoldingCompName, dstrSrcFeeModelCode, dstrSrcFeeModelDesc, dstrSearchAll, dstrAsofDate, true, false);
            setContainer( IFASTBP_PROC::FEE_MODEL_LIST, _pFeeModelList ); 
            if(m_HoldingCompCode != I_(""))
            {
               _pFeeModelList->setFromHoldingCompany(m_HoldingCompCode, dataGroupId);
            }
         }
         break;
      case SEARCH_NEXT_BLOCK:
         {
            FeeModelList* pFeeModelList = dynamic_cast<FeeModelList*>(getCBOList(IFASTBP_PROC::FEE_MODEL_LIST, getDataGroupId()));

            if(pFeeModelList)
               pFeeModelList->getMore();
         }
         break;
      default:
         break;
   }

   return(sevRtn); 
}
//***********************************************************************************
bool FeeModelProcess::doMoreRecordsExist(
                                        GenericInterface *rpGICaller,
                                        const BFContainerId& idSearch
                                        )
{
   FeeModelList* pFeeModelList = dynamic_cast<FeeModelList*>(getCBOList(IFASTBP_PROC::FEE_MODEL_LIST, getDataGroupId()));

   return pFeeModelList ? pFeeModelList->doMoreRecordsExist() : false;
}


//******************************************************************************

bool FeeModelProcess::doOk( GenericInterface *rpGICaller )
{
   if( m_frSCR == FEEMODEL::SYSTEM )
   {
      setParameter( CONFPROC::PARM_CALLED_FROM, I_("FeeModel") );
   }
   return(true);
}

//******************************************************************************
const DString& FeeModelProcess::getNextListItemKey( const GenericInterface *rpGICaller, const BFContainerId& idList )
{  
   TRACE_METHOD( CLASSNAME, GETNEXTLISTITEMKEY );

   try
   {
      if( idList == IFASTBP_PROC::FEE_MODEL_LIST )
      {
         if( m_dstrPrevKey == m_dstrEndKey ) 
         {
            return m_dstrEmptykey;
         }
         m_dstrPrevKey = AbstractProcess::getNextListItemKey( rpGICaller, idList );
         return (AbstractProcess::getCurrentListItemKey( rpGICaller, idList ));
      }
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
const DString& FeeModelProcess::getFirstListItemKey( const GenericInterface *rpGICaller, const BFContainerId& idList )
{  
   TRACE_METHOD( CLASSNAME, GETFIRSTLISTITEMKEY );

   DString key;
   try
   {
      if( idList == IFASTBP_PROC::FEE_MODEL_LIST )
      {
         m_dstrPrevKey = AbstractProcess::getFirstListItemKey( rpGICaller, idList );
         return (AbstractProcess::getCurrentListItemKey( rpGICaller, idList ));
      }
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
void FeeModelProcess::doPostOk(GenericInterface *rpGICaller, bool bSuccessFlag)
{
   DString feeModelCode;
   if( bSuccessFlag && isContainerValid(IFASTBP_PROC::FEE_MODEL_LIST) 
      && getNumberOfItemsInList(this, IFASTBP_PROC::FEE_MODEL_LIST) > 0 )
   {
      const DString curKey = getCurrentListItemKey( rpGICaller,IFASTBP_PROC::FEE_MODEL_LIST );
      if(curKey != NULL_STRING) {
         getField( rpGICaller, IFASTBP_PROC::FEE_MODEL_LIST, ifds::FeeModelCode, feeModelCode,false );
         setParameter(MFCAN_IP_PARAM::FEE_MODEL_CODE, feeModelCode);
      }
   }
}

//******************************************************************************
SEVERITY FeeModelProcess::doSetField(
                                    const GenericInterface *rpGICaller,
                                    const BFContainerId& idContainer,
                                    const BFFieldId& idField,
                                    const BFDataGroupId& idDataGroup,
                                    const DString& strValue,
                                    bool bFormatted
                                    )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOSETFIELD );

   if( BF::NullContainerId == idContainer )
   {
      if( idField == ifds::SrcHoldingCompCode )
      {
         m_SrcHoldingCompCode = strValue;
      }
      else if( idField == ifds::SrcHoldingCompName )
      {
         m_SrcHoldingCompName = strValue;
      }
      else if( idField == ifds::SrcFeeModelCode )
      {
         m_SrcFeeModelCode = strValue;
      }
      else if( idField == ifds::SrcFeeModelDesc)
      {
         m_SrcFeeModelDesc = strValue;
      }
      else if( idField == ifds::SearchAll )
      {
         m_SearchAll = strValue;
      }
      else if( idField == ifds::AsofDate)
      {
         m_AsofDate = strValue;
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void FeeModelProcess::doGetField(
               const GenericInterface *rpGICaller,
               const BFContainerId& idContainer,
               const BFFieldId& idField,
               const BFDataGroupId& idDataGroup, 
               DString &strValueOut,
               bool bFormatted
               ) const
{  
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOGETFIELD );

   if(BF::NullContainerId == idContainer)
   {
      if( idField == ifds::SrcHoldingCompCode )
      {
         strValueOut = m_SrcHoldingCompCode;
      }
      else if( idField == ifds::SrcHoldingCompName )
      {
         strValueOut = m_SrcHoldingCompName;
      }
      else if( idField == ifds::SrcFeeModelCode )
      {
         strValueOut = m_SrcFeeModelCode;
      }
      else if( idField == ifds::SrcFeeModelDesc)
      {
         strValueOut = m_SrcFeeModelDesc;
      }
      else if( idField == ifds::SearchAll )
      {
         strValueOut = m_SearchAll;
      }
      else if( idField == ifds::AsofDate)
      {
         strValueOut = m_AsofDate;
      }
      else if( idField == ifds::HoldingCompCode )
      {
         strValueOut = m_HoldingCompCode;
      }
      else if( idField == ifds::HoldingCompName )
      {
         strValueOut = m_HoldingCompName;
      }
      else if(idField == FEEMOD_FLDS::FROM_HOLDCOMP)
      {
         strValueOut = m_HoldingCompCode == I_("") ? I_("N") : I_("Y");
      }
      else if(idField == ifds::SchedSetupFreqAppl    || 
              idField == ifds::HoldingEntityAppl     ||
              idField == ifds::CalcCurrencyAppl      ||
              idField == ifds::FundGroupType         ||
              idField == ifds::FundGrpTypeList       ||
              idField == ifds::AggregationMethodList ||
              idField == ifds::CalcRateTypeList      ||
              idField == ifds::FeeModelOptionList)
      {
         FeeModel *pFeeModel = dynamic_cast<FeeModel*>(const_cast<FeeModelProcess*>(this)->getCBOItem(IFASTBP_PROC::FEE_MODEL_LIST, idDataGroup));
         if(pFeeModel)
         {
            BFAbstractCBO* pFeeModelSetup = NULL;
            pFeeModel->getFeeModelSetup(idDataGroup, pFeeModelSetup);
            if(pFeeModelSetup)
            {
               DString dstrFieldValue;
               pFeeModelSetup->getField(idField, dstrFieldValue, idDataGroup, false);
               strValueOut = dstrFieldValue;
            }
         }
      }
   }
}
//******************************************************************************
SEVERITY FeeModelProcess::getHistoricalParameters(const BFContainerId &idContainer, BFFieldId &recordIdField, DString &tableId, DString &dstrKeys) 
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);
   
   if (idContainer == IFASTBP_PROC::FEE_MODEL_LIST)
   {
      recordIdField = ifds::FeeModelRecid;
      tableId = AUDITTYPE::FEE_MODEL;
   }
   else 
   {
      assert(0);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************

SEVERITY FeeModelProcess::getHistoricalParameters(const BFContainerId& idContainer, HISTORICAL_VECTOR &vectorHistorical)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
const BFProperties *FeeModelProcess::doGetFieldAttributes( const GenericInterface *rpGICaller,
                                                           const BFContainerId& idContainer,
                                                           const BFFieldId &idField,
                                                           const BFDataGroupId& idDataGroup )
{  
   const BFProperties *props = NULL;
   props = AbstractProcess::doGetFieldAttributes(rpGICaller, idContainer, idField, idDataGroup);

   //if(BF::NullContainerId == idContainer)
   //{
   //   if( idField == ifds::HoldingCompCode )
   //   {
   //      props = m_pReadOnlyHldCompCodeProps;
   //   }
   //   else if( idField == ifds::HoldingCompName )
   //   {
   //      props = m_pReadOnlyHldCompDescProps;
   //   }
   //}   

   return props;
}

//******************************************************************************
SEVERITY FeeModelProcess::ok2( GenericInterface *rpGICaller )
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
         setParameter(CONFPROC::COMMIT_PARENT_DATA_GROUPS, I_("1"));
         setParameter (CONFPROC::PARM_CALLED_FROM, I_("FeeModel"));
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

   doPostOk( rpGICaller, bSuccessFlag );

   if( bSuccessFlag )
   {
      return(NO_CONDITION);
   }
   return(SEVERE_ERROR);
}
//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/FeeModelProcess.cpp-arc  $
// 
//    Rev 1.9   Nov 14 2004 19:25:40   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.8   Oct 15 2004 16:04:14   FENGYONG
// PTS10034766 - disable add and delete when access FeeModel from fundsponsor fee model screen.
// 
//    Rev 1.7   Sep 22 2004 10:40:00   FENGYONG
// Only disable refresh button for system level FeeModel screen.
// 
//    Rev 1.6   Sep 21 2004 16:55:10   FENGYONG
// disable refresh button on confirmation screen
// 
//    Rev 1.5   Sep 20 2004 16:25:56   YINGBAOL
// PET1117:FN05 Fix more than 25 records issue.
// 
//    Rev 1.4   Sep 09 2004 17:14:36   FENGYONG
// fix post ok problem
// 
//    Rev 1.3   Aug 31 2004 17:32:12   FENGYONG
// change field name
// 
//    Rev 1.2   Aug 11 2004 18:40:12   FENGYONG
// PET 1117 FN05 Syncup after get files resource 
// 
//    Rev 1.1   Aug 10 2004 11:11:30   FENGYONG
// PET117 FN5 - Client Condition Fee
// 
//    Rev 1.0   Aug 09 2004 10:00:50   FENGYONG
// Initial revision.
// 
 *
 */
