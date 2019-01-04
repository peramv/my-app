//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2011 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : GIAInvAttribProcess.cpp
// ^CLASS  : GIAInvAttribProcess
//
//******************************************************************************

#include "stdafx.h"
#include "giainvattribprocess.hpp"
#include "giainvattribprocessincludes.h"

#include <ifastcbo\progressiveintratelist.hpp>
#include <ifastcbo\trade.hpp>
#include <ifastcbo\worksessiontradeslist.hpp>
#include <ifastcbo\transfeelist.hpp>


extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_GIA_INVEST_ATTRIBS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_GIA_INVEST_ATTRIBS;

#include <bfproc\concreteprocesscreator.hpp>

static ConcreteProcessCreator< GIAInvAttribProcess > processCreator( CMD_BPROC_GIA_INVEST_ATTRIBS );

namespace 
{
   const I_CHAR *CLASSNAME = I_("GIAInvestArrtribsProcess");
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace TRADE_VALIDATION_GROUP
{
   extern CLASS_IMPORT const long GIA_ATTRIB;
}

namespace ifds
{
   extern CLASS_IMPORT const BFDecimalFieldId ProgressiveIntRate;
   extern CLASS_IMPORT const BFNumericFieldId ProgressiveInvTerm;
   extern CLASS_IMPORT const BFDateFieldId GIMaturityDate;
   extern CLASS_IMPORT const BFDecimalFieldId ForcedRateAmt;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
GIAInvAttribProcess::GIAInvAttribProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand ) 
, _rpChildGI( NULL )
, m_Caller (NULL_STRING)
, m_TradeListKey (NULL_STRING)
, m_accountNum (NULL_STRING)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer (IFASTBP_PROC::TRADE, false, BF::NullContainerId, true, I_("Trade"));
   addContainer (IFASTBP_PROC::PROGRESSIVE_INTEREST_RATE_LIST, true,  BF::NullContainerId, false, I_("ProgIntList"));
}

//******************************************************************************
GIAInvAttribProcess::~GIAInvAttribProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   _rpChildGI = NULL;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************
SEVERITY GIAInvAttribProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

   try
   {    
      getParameter (CALLER, m_Caller);
      getParameter (ACCOUNT_NUM, m_accountNum);
      getParameter (MFCAN_IP_PARAM::LIST_KEY, m_TradeListKey);
      if (m_Caller == I_("TradeEntry"))
      {
         addFieldDetails( ifds::IntInvestType,        IFASTBP_PROC::TRADE );
         addFieldDetails( ifds::AddlAmt,              IFASTBP_PROC::TRADE );
         addFieldDetails( ifds::IntCalcMthd,          IFASTBP_PROC::TRADE );
         addFieldDetails( ifds::InvestTerm,           IFASTBP_PROC::TRADE );
         addFieldDetails( ifds::EffectiveDate,        IFASTBP_PROC::TRADE );
         addFieldDetails( ifds::GIMaturityDate,       IFASTBP_PROC::TRADE );
         addFieldDetails( ifds::IntCredFreq,          IFASTBP_PROC::TRADE );
         addFieldDetails( ifds::NextIntCredDate,      IFASTBP_PROC::TRADE );
         addFieldDetails( ifds::ForcedRate,           IFASTBP_PROC::TRADE );
         addFieldDetails( ifds::ForcedRateAmt,           IFASTBP_PROC::TRADE );
         addFieldDetails( ifds::IntRate,              IFASTBP_PROC::TRADE );
         addFieldDetails( ifds::CommRedRate,          IFASTBP_PROC::TRADE );

         addFieldDetails( ifds::ProgressiveInvTerm,   IFASTBP_PROC::PROGRESSIVE_INTEREST_RATE_LIST );
         addFieldDetails( ifds::ProgressiveIntRate,   IFASTBP_PROC::PROGRESSIVE_INTEREST_RATE_LIST );
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      throw EXCEPTIONFROMFILE( CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool GIAInvAttribProcess::doModelessChildComplete( const Command &cmd )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_GIA_INVEST_ATTRIBS);
}

//******************************************************************************
E_COMMANDRETURN GIAInvAttribProcess::doProcess()
{  
   MAKEFRAME2( CND::IFASTBP_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter (CALLER, m_Caller);   
      setParameter (ACCOUNT_NUM, m_accountNum);   
      rtn = invokeCommand( this, CMD_GUI_GIA_INVEST_ATTRIBS, PROC_NO_TYPE, isModal(), &_rpChildGI );
   }
   catch( ConditionException &ce )
   {
      assert( 0 );
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return( rtn );
}
//******************************************************************************
void *GIAInvAttribProcess::getPtrForContainer( const BFContainerId& idContainer,
                                               const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_( "getPtrForContainer" ) );
   
   void *ptr = NULL;
   DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   try
   {
      if (IFASTBP_PROC::TRADE == idContainer)
      {
         if (m_Caller == I_("TradeEntry"))
         {
            WorksessionTradesList *pTradesList (NULL);

            if( pDSTCWorkSession->getTradesList (pTradesList, idDataGroup) <= WARNING && 
                pTradesList)
            {
               BFObjIter iter (*pTradesList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

               iter.positionByKey (m_TradeListKey);
               if (!iter.end())
               {
                  ptr = dynamic_cast <Trade*>(iter.getObject());
               }
            }
         }
      }
      else if(IFASTBP_PROC::PROGRESSIVE_INTEREST_RATE_LIST == idContainer)
      {
         if (m_Caller == I_("TradeEntry"))
         {
            Trade *pTrade = 
               dynamic_cast <Trade*> (getCBOItem (IFASTBP_PROC::TRADE, idDataGroup));

            if (pTrade)
            {
               ProgressiveIntRateList *pProgressiveIntRateList = NULL;
               if( pTrade->getProgressiveIntRateListForDisplay(pProgressiveIntRateList,idDataGroup) <= WARNING )
               {
                  ptr = pProgressiveIntRateList;
               }
            }
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
bool GIAInvAttribProcess::doOk (GenericInterface *rpGICaller)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_( "doOk" ) );

   return GETCURRENTHIGHESTSEVERITY () <= WARNING;
}

//*****************************************************************************
SEVERITY GIAInvAttribProcess::doValidateAll ( BFAbstractCBO *rpWSD, 
                                              const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOVALIDATEALL);
   
   if (m_Caller == I_("TradeEntry"))
   {
      Trade *pTrade = 
         dynamic_cast <Trade*> (getCBOItem (IFASTBP_PROC::TRADE, idDataGroup));

      if (pTrade)
      {
//validate only the GI attrib group
         pTrade->validateAll (idDataGroup, TRADE_VALIDATION_GROUP::GIA_ATTRIB);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool GIAInvAttribProcess::doSend ( GenericInterface *rpGICaller,
                                   const I_CHAR  *szMessage)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOSEND);

   DString message (szMessage);
   const BFDataGroupId &idDataGroup = getDataGroupId ();
   Trade *pTrade = 
      dynamic_cast <Trade*> (getCBOItem (IFASTBP_PROC::TRADE, idDataGroup));
   
   //reset settle location values, only for new trades
   if (m_Caller == I_("TradeEntry") && pTrade)
   {
      if (message == I_("Cancel")) 
      {
         pTrade->resetGIAAttrib (idDataGroup);
      }
   }
   return GETCURRENTHIGHESTSEVERITY() <= WARNING;
}

//******************************************************************************
bool GIAInvAttribProcess::doRefresh( GenericInterface *rpGICaller,
                           const I_CHAR *szOriginalCommand )
{
   setContainer(IFASTBP_PROC::PROGRESSIVE_INTEREST_RATE_LIST, NULL);

   return true;
}

//******************************************************************************
void GIAInvAttribProcess::doPostOk ( GenericInterface *rpGICaller, 
                                    bool bSuccessFlag
                                  )
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, I_("doPostOk"));
   if (m_Caller == I_("TradeEntry"))
      {
		  const BFDataGroupId& idDataGroup = getDataGroupId();
		  Trade* pTrade = dynamic_cast <Trade*>(getCBOItem (IFASTBP_PROC::TRADE, idDataGroup));
		  //notify the trans fee list of the change
		  TransFeeList *pTransFeeList = NULL;
		  if ( pTrade->getTransFeeList (pTransFeeList, idDataGroup, false) <= WARNING && pTransFeeList)
		  {
			  pTransFeeList->setForcingRefresh(true);
			  pTransFeeList->onNotify (FIELD_NOTIFICATIONS, E_EVENT_VALUE_CHANGE, I_("ForceRefresh"));
		  }
   }
   
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/GIAInvAttribProcess.cpp-arc  $
// 
//    Rev 1.7   Dec 07 2011 16:06:06   dchatcha
// P0186477/FN03 - GIA - Purchase, rewrite logic on modify pending trade by using view 54 instead call to view 241
// 
//    Rev 1.6   Dec 03 2011 10:55:48   dchatcha
// P0186477/FN03 - GIA - Purchase, make sure that only return with valid CBO list to display
// 
//    Rev 1.5   Dec 03 2011 01:29:26   dchatcha
// P0186477/FN03 - GIA - Purchase
// 
//    Rev 1.4   Dec 01 2011 11:27:34   dchatcha
// P0186477/FN03 - GIA - Purchase, removed estimated rate field from screen.
// 
//    Rev 1.3   Nov 30 2011 17:54:24   dchatcha
// P0186477/FN03 - GIA - Purchase, no need proxy fields anymore
// 
//    Rev 1.2   Nov 30 2011 00:26:02   dchatcha
// P0186477/FN03 - GIA - Purchase
// 
//    Rev 1.1   Nov 27 2011 19:33:32   popescu
// INA Commission Work
// 
// Initial revision.
 * 
*/