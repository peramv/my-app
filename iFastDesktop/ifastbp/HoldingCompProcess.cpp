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
// ^FILE   : HoldingCompProcess.cpp
// ^AUTHOR : 
// ^DATE   : July 21, 2004  
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : HoldingCompProcess
//    This class manages the address book process.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "holdingcompprocessinclude.h"
#include "holdingcompprocess.hpp"
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\holdingcomplist.hpp>
#include <ifastcbo\holdingcomp.hpp>
#include "mfcaninterprocparam.hpp"
#include <ifastcbo\mgmtco.hpp>
#include "confirmationprocessincludes.h"
#include <ifastcbo\mgmtcooptions.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_HOLDING_COMP;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_HOLDING_COMP;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< HoldingCompProcess > processCreator( CMD_BPROC_HOLDING_COMP );

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "HoldingCompProcess" );
}

namespace HOLDINGCOMP
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

namespace AUDITTYPE
{
   extern CLASS_IMPORT I_CHAR * const HOLDING_COMPANY;
   extern CLASS_IMPORT I_CHAR * const ENTIDT;
   extern CLASS_IMPORT I_CHAR * const WHERE_USED;
}


//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319HoldingCompProcess::HoldingCompProcess() 
HoldingCompProcess::HoldingCompProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
,  _rpChildGI( NULL )
,  m_dispNum( 0 )
,  m_More( 0 )
,  m_totalNum( 0 )
,  m_dstrEndKey( NULL )
,	m_dstrEmptykey(NULL)
,  m_bHasMore(false)
{
   TRACE_CONSTRUCTOR( CLASSNAME, I_( "HoldingCompProcess" ) );

   isProcSupport = getProcessType() == PROC_SUPPORT;
   m_SearchAll = I_("N");

   DString dstrCurBusDate;
   DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
	dstWorkSession->getMgmtCoOptions()->getField(ifds::CurrBusDate, dstrCurBusDate, BF::HOST);
   dstrCurBusDate.strip();
   m_AsofDate = dstrCurBusDate;


   addFieldDetails( ifds::SrcHoldingCompCode, BF::NullContainerId, SUBCLASS_PROCESS   );
   addFieldDetails( ifds::SrcHoldingCompName, BF::NullContainerId, SUBCLASS_PROCESS   );
   addFieldDetails( ifds::SearchAll,       BF::NullContainerId, SUBCLASS_PROCESS   );
   addFieldDetails( ifds::AsofDate,        BF::NullContainerId, SUBCLASS_PROCESS   );


   addContainer( IFASTBP_PROC::HOLDING_COMP_LIST, true, BF::NullContainerId, true, I_("HoldingComp") );

   addFieldDetails( ifds::EntityId,           IFASTBP_PROC::HOLDING_COMP_LIST);
   addFieldDetails( ifds::WhereUseKey,        IFASTBP_PROC::HOLDING_COMP_LIST);
   addFieldDetails( ifds::HoldingCompName,    IFASTBP_PROC::HOLDING_COMP_LIST);
   addFieldDetails( ifds::Deff,               IFASTBP_PROC::HOLDING_COMP_LIST);
   addFieldDetails( ifds::StopDate,           IFASTBP_PROC::HOLDING_COMP_LIST);
   addFieldDetails( ifds::AggregationMethod,  IFASTBP_PROC::HOLDING_COMP_LIST);
   addFieldDetails( ifds::ProcessDate,        IFASTBP_PROC::HOLDING_COMP_LIST);
   addFieldDetails( ifds::Username,           IFASTBP_PROC::HOLDING_COMP_LIST);
   addFieldDetails( ifds::ModDate,            IFASTBP_PROC::HOLDING_COMP_LIST);
   addFieldDetails( ifds::ModUser,            IFASTBP_PROC::HOLDING_COMP_LIST);
   addFieldDetails( ifds::GBCD,               IFASTBP_PROC::HOLDING_COMP_LIST);
   addFieldDetails( ifds::CompanyUsage,       IFASTBP_PROC::HOLDING_COMP_LIST);
   addFieldDetails( ifds::Language,           IFASTBP_PROC::HOLDING_COMP_LIST);
   addFieldDetails( ifds::EntityWhereUseRid,  IFASTBP_PROC::HOLDING_COMP_LIST);
   addFieldDetails( ifds::EntityWhereUseVer,  IFASTBP_PROC::HOLDING_COMP_LIST);
   addFieldDetails( ifds::FeeModelExist,      IFASTBP_PROC::HOLDING_COMP_LIST);
   addFieldDetails( ifds::FeeAggregationExist,IFASTBP_PROC::HOLDING_COMP_LIST);
   addFieldDetails( ifds::BillingInstrExist,  IFASTBP_PROC::HOLDING_COMP_LIST);
   addFieldDetails( ifds::ReportGroupExist,   IFASTBP_PROC::HOLDING_COMP_LIST);
   addFieldDetails( ifds::FirstChildRecDeff,  IFASTBP_PROC::HOLDING_COMP_LIST);
   addFieldDetails( ifds::ShrAcctLastProcDate,IFASTBP_PROC::HOLDING_COMP_LIST);
   
   
   //addFieldDetails( ifds::EffectiveDate,  IFASTBP_PROC::HOLDING_COMP_LIST );
   //addFieldDetails( ifds::StopDate,       IFASTBP_PROC::FEE_MODEL_LIST );
   //addFieldDetails( ifds::ProcessDate,    IFASTBP_PROC::FEE_MODEL_LIST );
   //addFieldDetails( ifds::ModDate,        IFASTBP_PROC::FEE_MODEL_LIST );
   //addFieldDetails( ifds::Username,       IFASTBP_PROC::FEE_MODEL_LIST );
   //addFieldDetails( ifds::ModUser,        IFASTBP_PROC::FEE_MODEL_LIST );

}

//******************************************************************************
HoldingCompProcess::~HoldingCompProcess()
{
   //TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY HoldingCompProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

   try
   {
      const BFDataGroupId& idDataGroup = getDataGroupId();
      
      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
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
E_COMMANDRETURN HoldingCompProcess::doProcess()
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
         setParameter( HOLDINGCOMP::FROM_SCR, m_frSCR );
         rtn = invokeCommand( this, CMD_GUI_HOLDING_COMP, getProcessType(), isModal(), &_rpChildGI );
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
bool  HoldingCompProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
   bool bRtn = false;

   try
   {
      const BFDataGroupId& idDataGroup = getDataGroupId();
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
bool  HoldingCompProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_HOLDING_COMP );
}
//******************************************************************************

void* HoldingCompProcess::getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
   void *ptr = NULL;
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   try
   {
      if (IFASTBP_PROC::HOLDING_COMP_LIST == idContainer)
      {
         DString dstrHoldingCompCode;
         DString dstrHoldingCompName;
         DString dstrSearchAll = I_("Y");
         DString dstrAsofDate = I_("12319999");

         
         
         getField( this, BF::NullContainerId, ifds::SrcHoldingCompCode, dstrHoldingCompCode, false);
         getField( this, BF::NullContainerId, ifds::SrcHoldingCompName, dstrHoldingCompName, false);
         getField( this, BF::NullContainerId, ifds::SearchAll, dstrSearchAll, false);
         getField( this, BF::NullContainerId, ifds::AsofDate, dstrAsofDate, false);

         HoldingCompList* pHoldingCompList = NULL;
         SEVERITY sevRtn = dstcWorkSession->getHoldingCompList(pHoldingCompList, idDataGroup, dstrHoldingCompCode, 
            dstrHoldingCompName, dstrSearchAll, dstrAsofDate, true, isProcSupport);
         if(pHoldingCompList)
         {
            m_bHasMore = pHoldingCompList->doMoreRecordsExist();
         }
         else
         {
            m_bHasMore = false;
         }
         ptr = pHoldingCompList;
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
bool HoldingCompProcess::doRefresh(
                               GenericInterface *rpGICaller,
                               const I_CHAR *szOriginalCommand
                               )
{
   return(_rpChildGI->refresh( this, NULL ));
}

//*****************************************************************************

SEVERITY HoldingCompProcess::performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, 
                                         E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("performSearch") );
   SEVERITY sevRtn = NO_CONDITION;

   try
   {
      if( eSearchAction == SEARCH_START)
      {
         HoldingCompList* pHoldingCompList = NULL;
         pHoldingCompList = (HoldingCompList*)getPtrForContainer(IFASTBP_PROC::HOLDING_COMP_LIST, getDataGroupId() );
         if(pHoldingCompList)
         {
            m_bHasMore = pHoldingCompList->doMoreRecordsExist();
         }
      }
      else if( eSearchAction == SEARCH_NEXT_BLOCK )
      {
         HoldingCompList* pHoldingCompList = NULL;
         pHoldingCompList = dynamic_cast<HoldingCompList*>(getCBOList(IFASTBP_PROC::HOLDING_COMP_LIST, getDataGroupId()));
         if(pHoldingCompList)
         {
            pHoldingCompList->getMore();
            m_bHasMore = pHoldingCompList->doMoreRecordsExist();
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
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, I_("performSearch"), CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(sevRtn); 
}
//***********************************************************************************
bool HoldingCompProcess::doMoreRecordsExist(
                                        GenericInterface *rpGICaller,
                                        const BFContainerId& idSearch
                                        )
{
   return m_bHasMore;
}


//******************************************************************************

bool HoldingCompProcess::doOk( GenericInterface *rpGICaller )
{
   setParameter( CONFPROC::PARM_CALLED_FROM, I_("HoldingComp") );
   return(true);
}

//******************************************************************************
const DString& HoldingCompProcess::getNextListItemKey( const GenericInterface *rpGICaller, const BFContainerId& idList )
{  
   TRACE_METHOD( CLASSNAME, GETNEXTLISTITEMKEY );

   try
   {
      if( idList == IFASTBP_PROC::HOLDING_COMP_LIST )
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
const DString& HoldingCompProcess::getFirstListItemKey( const GenericInterface *rpGICaller, const BFContainerId& idList )
{  
   TRACE_METHOD( CLASSNAME, GETFIRSTLISTITEMKEY );

   DString key;
   try
   {
      if( idList == IFASTBP_PROC::HOLDING_COMP_LIST )
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
void HoldingCompProcess::adjustKey( )
{  
   if( m_totalNum > m_dispNum + m_More * 25 )
   {
      m_dispNum = m_dispNum  + 25;
      m_More++;
   }
   else
   {
      m_dispNum = m_totalNum;
   }

   BFObjIter iter( *_pHoldingCompList, getDataGroupId(), true, BFObjIter::ITERTYPE::NON_DELETED, false, true );
   int i=0;
	DString dstrKey;

   while (i<m_dispNum && !iter.end())
   {
		dstrKey = iter.getStringKey();
      ++iter;
      i++;
   }

   m_dstrEndKey = dstrKey;
   
   return;
}

//******************************************************************************
void HoldingCompProcess::doPostOk(GenericInterface *rpGICaller, bool bSuccessFlag)
{
   DString dstrHoldingCompCode;
   if( isProcSupport && bSuccessFlag && isContainerValid(IFASTBP_PROC::HOLDING_COMP_LIST) 
      && getNumberOfItemsInList(this, IFASTBP_PROC::HOLDING_COMP_LIST) > 0 )
   {
		const DString curKey = getCurrentListItemKey( rpGICaller,IFASTBP_PROC::HOLDING_COMP_LIST );
		if(curKey != NULL_STRING) {
			getField( rpGICaller, IFASTBP_PROC::HOLDING_COMP_LIST, ifds::WhereUseKey, dstrHoldingCompCode,false );
			setParameter(MFCAN_IP_PARAM::HOLDING_COMP_CODE, dstrHoldingCompCode);
		}
   }
}

//******************************************************************************
SEVERITY HoldingCompProcess::doSetField(
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
void HoldingCompProcess::doGetField(
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
      else if( idField == ifds::SearchAll )
      {
         strValueOut = m_SearchAll;
      }
      else if( idField == ifds::AsofDate)
      {
         strValueOut = m_AsofDate;
      }
   }
}

//******************************************************************************
SEVERITY HoldingCompProcess::getHistoricalParameters(const BFContainerId &idContainer, BFFieldId &recordIdField, DString &tableId, DString &dstrKeys) 
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);
   
   if (idContainer == IFASTBP_PROC::HOLDING_COMP_LIST)
   {
      recordIdField = ifds::EntityWhereUseRid;
      tableId = AUDITTYPE::HOLDING_COMPANY;
   }
   else 
   {
      assert(0);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************

SEVERITY HoldingCompProcess::getHistoricalParameters(const BFContainerId& idContainer, HISTORICAL_VECTOR &vectorHistorical)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);
   
   DString keyStringIDI( NULL_STRING );
   DString dstrShrFamilyRecord;
   DString dstrFamilyRecord;
   DString dstrFamilyCode;
   DString dstrFamilyType;
   DString dstrShrNum;

   DString dstrHoldingEntityCode;
   DString dstrEntityId;
   getField ( this, IFASTBP_PROC::HOLDING_COMP_LIST, ifds::WhereUseKey, dstrHoldingEntityCode, false );
   getField ( this, IFASTBP_PROC::HOLDING_COMP_LIST, ifds::EntityId, dstrEntityId, false );

   addIDITagValue (keyStringIDI, I_("HoldingEntityCode"), dstrHoldingEntityCode);
   addIDITagValue (keyStringIDI, I_("EntityId"), dstrEntityId);
   HistoricalElement historicalElementHoldingEntity( I_(""), AUDITTYPE::HOLDING_COMPANY, keyStringIDI );
   vectorHistorical.push_back(historicalElementHoldingEntity);

   return GETCURRENTHIGHESTSEVERITY();
}