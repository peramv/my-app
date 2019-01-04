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
//    Copyright 2004 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : TradeVerificationProcess.cpp
// ^AUTHOR : Robbins Kuriakose  
// ^DATE   : July 22 1024
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : TradeVerificationProcess
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include <bfproc\concreteprocesscreator.hpp>
#include <ifastcbo\dstcworksession.hpp>
#include <ifastcbo\TradeVerification.hpp>
#include <ifastcbo\TradeVerificationList.hpp>
#include <ifastcbo\TradeVerificationSearch.hpp> 
#include <ifastcbo\TradeOverideRuleWarningsList.hpp>
#include "MFCANInterProcParam.hpp"   
#include "TradeVerificationProcess.hpp"
#ifndef TRADEVERIFICATIONSEARCHPROCESSINCLUDES_H
    #include <ifastbp\TradeVerificationsearchprocessincludes.h>
#endif

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_TRADE_VERIFICATION_SEARCH;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_TRADE_VERIFICATION_SEARCH;
static ConcreteProcessCreator< TradeVerificationProcess > processCreator( CMD_BPROC_TRADE_VERIFICATION_SEARCH );

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME                          = I_( "TradeVerificationProcess" );
   const I_CHAR * const PERFORMSEARCH               = I_( "performSearch" );   
   const I_CHAR * const YES                         = I_( "Y" );
   const I_CHAR * const NO                          = I_( "N" );
   const I_CHAR * const YES_STRING                  = I_( "Yes" );
   const I_CHAR * const NO_STRING                   = I_( "No" );
   const I_CHAR * const TRADE_VERIFICATION_LIST     = I_("TradeVerificationList");
   const I_CHAR * const IS_NEWSEARCH                = I_( "IsNewSearch" );
   const I_CHAR * const TRADE_OVERIDE_WARNINGS_LIST = I_("TradeOverideRuleWarningsList");
}

namespace ifds
{
   extern CLASS_IMPORT const BFDateFieldId TradeDate;
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFTextFieldId FundISIN; 
   extern CLASS_IMPORT const BFTextFieldId FundWKN;
   extern CLASS_IMPORT const BFTextFieldId FundNumber;
   extern CLASS_IMPORT const BFTextFieldId FundName; 
   extern CLASS_IMPORT const BFTextFieldId TradesSearchTransType;
   extern CLASS_IMPORT const BFTextFieldId CUSIP;
   extern CLASS_IMPORT const BFTextFieldId TDCC;
   extern CLASS_IMPORT const BFTextFieldId Valoren;
   extern CLASS_IMPORT const BFTextFieldId PricingCode;
   extern CLASS_IMPORT const BFTextFieldId PriceInCode;
   extern CLASS_IMPORT const BFTextFieldId GateOverrideIndicator;

}

//******************************************************************************
//              Public Methods
//******************************************************************************
TradeVerificationProcess::TradeVerificationProcess (GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand)
                                                    : AbstractProcess( pGIC, pGIParent, rCommand),
                                                     _rpChildGI( NULL ), _pTradeVerificationList(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

   //Containers
   addContainer( IFASTBP_PROC::CRITERIA, false, BF::NullContainerId, true, I_("Criteria") );
   addContainer( IFASTBP_PROC::TRADE_VERIFICATION_LIST, true,  IFASTBP_PROC::CRITERIA, true, TRADE_VERIFICATION_LIST );
   addContainer( IFASTBP_PROC::TRADE_OVERIDE_WARNINGS_LIST, true, IFASTBP_PROC::TRADE_VERIFICATION_LIST, false, TRADE_OVERIDE_WARNINGS_LIST); 
   //Fields
   addSubstituteList(ifds::TradeVerificationSearchHeading);

   //CRITERIA fields
   addFieldDetails( ifds::SearchType,          IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::TransNum,            IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::WireOrdNum,          IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::NetworkID,           IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::ExtTransNum,         IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::SendRefNum,          IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::PartRefNum,          IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::MasterRefNum,        IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::AccountNum,          IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::ExternalIdType,      IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::ExternalId,          IFASTBP_PROC::CRITERIA );   
   addFieldDetails( ifds::FundCode,            IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::ClassCode,		   IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::FundNumber,          IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::FundName,            IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::FundWKN,             IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::FundISIN,            IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::NSCCControlNumber,   IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::TradesSearchTransType, IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::TDCC,				   IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::Valoren,			   IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::SearchUserID,		   IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::CUSIP,			   IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::SponsorCode,         IFASTBP_PROC::CRITERIA);
   addFieldDetails( ifds::Platform,            IFASTBP_PROC::CRITERIA);
   
   //TRADE_VERIFICATION_LIST fields
   addFieldDetails( ifds::rxAcctNum,          IFASTBP_PROC::TRADE_VERIFICATION_LIST );
   addFieldDetails( ifds::rxFundCode,         IFASTBP_PROC::TRADE_VERIFICATION_LIST );
   addFieldDetails( ifds::rxClassCode,        IFASTBP_PROC::TRADE_VERIFICATION_LIST );
   addFieldDetails( ifds::TradeDate,          IFASTBP_PROC::TRADE_VERIFICATION_LIST );
   addFieldDetails( ifds::TransType,          IFASTBP_PROC::TRADE_VERIFICATION_LIST );
   addFieldDetails( ifds::TransNum,           IFASTBP_PROC::TRADE_VERIFICATION_LIST );
   addFieldDetails( ifds::Amount,             IFASTBP_PROC::TRADE_VERIFICATION_LIST );
   addFieldDetails( ifds::AmountType,         IFASTBP_PROC::TRADE_VERIFICATION_LIST );
   addFieldDetails( ifds::MsgExists,          IFASTBP_PROC::TRADE_VERIFICATION_LIST );
   addFieldDetails( ifds::VerifyPerm,         IFASTBP_PROC::TRADE_VERIFICATION_LIST );
   addFieldDetails( ifds::DeletePerm,         IFASTBP_PROC::TRADE_VERIFICATION_LIST );
   addFieldDetails( ifds::NetworkID,          IFASTBP_PROC::TRADE_VERIFICATION_LIST );
   addFieldDetails( ifds::UserAction,         IFASTBP_PROC::TRADE_VERIFICATION_LIST );
   addFieldDetails( ifds::VerifyTrade,        IFASTBP_PROC::TRADE_VERIFICATION_LIST ); 
   addFieldDetails( ifds::DeleteTrade,        IFASTBP_PROC::TRADE_VERIFICATION_LIST );
   addFieldDetails( ifds::GoodBad,            IFASTBP_PROC::TRADE_VERIFICATION_LIST );
   addFieldDetails( ifds::SponsorCode,        IFASTBP_PROC::TRADE_VERIFICATION_LIST );
   addFieldDetails( ifds::FundGroup,          IFASTBP_PROC::TRADE_VERIFICATION_LIST );
   addFieldDetails( ifds::Platform,           IFASTBP_PROC::TRADE_VERIFICATION_LIST );
   addFieldDetails( ifds::PricingCode,        IFASTBP_PROC::TRADE_VERIFICATION_LIST);
   addFieldDetails( ifds::PriceInCode,        IFASTBP_PROC::TRADE_VERIFICATION_LIST);
   addFieldDetails( ifds::ErrorCode,          IFASTBP_PROC::TRADE_OVERIDE_WARNINGS_LIST );
   addFieldDetails( ifds::GateOverrideIndicator,        IFASTBP_PROC::TRADE_VERIFICATION_LIST);
   

   //VERIFIACTION LIST..Keping this for case of    
   // addFieldDetails( ifds::ErrorCode,          IFASTBP_PROC::TRADE_VERIFICATION_LIST );
   //addFieldDetails( ifds::ErrMsg,             IFASTBP_PROC::TRADE_VERIFICATION_LIST );

   //SUBCLASS Fields    
   addFieldDetails( ifds::VerifyAll,          IFASTBP_PROC::TRADE_VERIFICATION_LIST,  SUBCLASS_PROCESS ); 
   addFieldDetails( ifds::DeleteAll,          IFASTBP_PROC::TRADE_VERIFICATION_LIST,  SUBCLASS_PROCESS );
   addFieldDetails( ifds::ErrMsg,             IFASTBP_PROC::TRADE_OVERIDE_WARNINGS_LIST,  SUBCLASS_PROCESS);   
   //addFieldDetails( ifds::ErrorCode,          IFASTBP_PROC::TRADE_VERIFICATION_LIST , SUBCLASS_PROCESS );
   //addFieldDetails( ifds::ErrMsg,             IFASTBP_PROC::TRADE_VERIFICATION_LIST , SUBCLASS_PROCESS );
   //dummy fields
   addFieldDetails( ifds::ValidTradeCriteria,   BF::NullContainerId, SUBCLASS_PROCESS);

}
//******************************************************************************
TradeVerificationProcess::~TradeVerificationProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}
//******************************************************************************
//              Protected Methods
//******************************************************************************
SEVERITY TradeVerificationProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
E_COMMANDRETURN TradeVerificationProcess::doProcess()
{  
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );

   E_COMMANDRETURN rtn = CMD_FAILURE;
   try
   {
      rtn = invokeCommand( this, CMD_GUI_TRADE_VERIFICATION_SEARCH, getProcessType(), isModal(), &_rpChildGI );
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
   return(rtn);
}
//******************************************************************************
void *TradeVerificationProcess::getPtrForContainer (const BFContainerId& idContainer, 
                                                    const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_("getPtrForContainer") );

   void *ptr = NULL;
   DSTCWorkSession* dstcWorkSession =  dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   TradeVerificationSearch* pTradeVerificationSearch = NULL;
   try
   {
      if ( idContainer == IFASTBP_PROC::CRITERIA)
      {
          if (dstcWorkSession->getTradeVerificationSearchCriteria (pTradeVerificationSearch) <= WARNING &&
              pTradeVerificationSearch)
              ptr = pTradeVerificationSearch;
      }
      else if( idContainer == IFASTBP_PROC::TRADE_VERIFICATION_LIST )
      {
         DString dstrNewSearch;
         getParameter( IS_NEWSEARCH , dstrNewSearch );
         if( YES ==  dstrNewSearch )
         {
             setContainer( IFASTBP_PROC::TRADE_VERIFICATION_LIST, NULL );
             _pTradeVerificationList = NULL;
             pTradeVerificationSearch = dynamic_cast<TradeVerificationSearch *>(getCBOItem (IFASTBP_PROC::CRITERIA, idDataGroup));            
             if(pTradeVerificationSearch->getTradeVerificationList(_pTradeVerificationList, idDataGroup) && _pTradeVerificationList)
                ptr = _pTradeVerificationList;
         }
         else
         {
           ptr = _pTradeVerificationList;
           //setContainer( IFASTBP_PROC::TRADE_VERIFICATION_LIST, _pTradeVerificationList ); SP
         }
      }  
      else if( idContainer == IFASTBP_PROC::TRADE_OVERIDE_WARNINGS_LIST )
      {
          _pTradeVerificationList = dynamic_cast<TradeVerificationList *>(getCBOItem (IFASTBP_PROC::TRADE_VERIFICATION_LIST, idDataGroup));
         if(_pTradeVerificationList)
         {
             setContainer( IFASTBP_PROC::TRADE_OVERIDE_WARNINGS_LIST, NULL );
             _pTradeOverideRuleWarningsList = NULL;
             if( dstcWorkSession->getTradeOverideRuleWarningsList(_pTradeOverideRuleWarningsList) && 
                _pTradeOverideRuleWarningsList)             
                  ptr = _pTradeVerificationList;
             else
                  ptr =  _pTradeVerificationList;
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
SEVERITY TradeVerificationProcess::performSearch (  GenericInterface *rpGICaller, 
                                                    const BFContainerId& idSearch, 
                                                    E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, PERFORMSEARCH );

   const BFDataGroupId& idDataGroup = getDataGroupId ();
   try
   {
      switch (eSearchAction)
      {
         case SEARCH_START:
            {
               if (idSearch == IFASTBP_PROC::TRADE_VERIFICATION_LIST)
                   _pTradeVerificationList = NULL;
                   _pTradeOverideRuleWarningsList = NULL;
                   setContainer (idSearch, NULL);
                   setContainer(IFASTBP_PROC::TRADE_OVERIDE_WARNINGS_LIST, NULL);
            }
            break;
         case SEARCH_NEXT_BLOCK:
            {
               if (idSearch == IFASTBP_PROC::TRADE_VERIFICATION_LIST)
               {
                  if (_pTradeVerificationList)
                     _pTradeVerificationList->getMore ();
               }               
            }
            break;
         default:
            break;
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
   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
bool TradeVerificationProcess::doOk( GenericInterface *rpGICaller )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doOk") );

   DString dstrAccountNum;
   bool bVerifyMoreThanOne = false;
   if( _pTradeVerificationList )
   {
     _pTradeVerificationList->clearUserActionFlag( getDataGroupId());
   }	
   if( _pTradeVerificationList )
   {
      bVerifyMoreThanOne = _pTradeVerificationList->bMoreThanOne( getDataGroupId() ); 
   }
   DString dstrDisableRemark = bVerifyMoreThanOne ? I_("Y"):I_("N");
   setParameter( MFCAN_IP_PARAM::DISABLE_REMARKS, dstrDisableRemark );
   return (true);
}

//******************************************************************************
void TradeVerificationProcess::doGetField(
                                   const GenericInterface *rpGICaller,
                                   const BFContainerId& idContainer,
                                   const BFFieldId& fieldID,
                                   const BFDataGroupId& idDataGroup,
                                   DString &strValueOut,
                                   bool bFormatted
                                   ) const
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, CLASSNAME, I_("doGetField"));

   DSTCWorkSession* pDSTCWorkSession = 
   dynamic_cast<DSTCWorkSession *> (getBFWorkSession());
   strValueOut = NULL_STRING;
   if( fieldID == ifds::ValidTradeCriteria )
   {
      strValueOut = NO;
      TradeVerificationSearch* pSearchCrt = NULL;
      DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      if( dstcWorkSession->getTradeVerificationSearchCriteria(pSearchCrt)<=WARNING )
         if( pSearchCrt->isValidForInquiry(idDataGroup) )
            strValueOut = YES;
   }
   else if (idContainer == IFASTBP_PROC::TRADE_VERIFICATION_LIST)
   {
    DString tradeKey = const_cast<TradeVerificationProcess*> (this)->getCurrentListItemKey 
                                                            ( this, IFASTBP_PROC::TRADE_VERIFICATION_LIST);
    if ( !tradeKey.empty())
     {
       BFAbstractCBO *rpPtr = const_cast<TradeVerificationProcess*> (this)->
                              getCBOItem ( IFASTBP_PROC::TRADE_VERIFICATION_LIST, 
                              idDataGroup);   
       if (rpPtr)
       { 
             if ( fieldID == ifds::DeleteTrade || 
                  fieldID == ifds::VerifyTrade ||
                  fieldID == ifds::VerifyAll   ||
                  fieldID == ifds::DeleteAll   )
             {
                rpPtr->getField ( fieldID, strValueOut, idDataGroup, bFormatted);
             }
        }
     }
   }
   else if (idContainer == IFASTBP_PROC::TRADE_OVERIDE_WARNINGS_LIST)
   {

    if( fieldID == ifds::ErrMsg ) //call the 464 view if the trade has briching rules.. 
    {
      
       DString tradeKey = const_cast<TradeVerificationProcess*> (this)->getCurrentListItemKey 
                                                                ( this, IFASTBP_PROC::TRADE_VERIFICATION_LIST);
       if ( !tradeKey.empty())
       {
         BFAbstractCBO *rpPtr = const_cast<TradeVerificationProcess*> (this)->
                                getCBOItem ( IFASTBP_PROC::TRADE_VERIFICATION_LIST, 
                                idDataGroup);   
          if (rpPtr)
          {
            DString dstrTradeHasWarning , dstrTransNum, dstrOldTransNum;
            TradeVerificationSearch* pSearchCrt = NULL;
            TradeOverideRuleWarningsList*  pTradeOverideRuleWarningsList = NULL;
            DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
            rpPtr->getField(ifds::MessageExits, dstrTradeHasWarning, idDataGroup, bFormatted);
            rpPtr->getField(ifds::TransNum, dstrTransNum , idDataGroup, false);
            bool bCreate = (YES == dstrTradeHasWarning);
            if(!bCreate ) 
                 return ;
            TradeVerification* pTradeVerification = dynamic_cast <TradeVerification*> ( rpPtr);
            if( pTradeVerification)
            {
              pTradeVerification->getTradeOverideRuleWarningsList( pTradeOverideRuleWarningsList, dstrTransNum );
              if( pTradeOverideRuleWarningsList ) 
                  pTradeOverideRuleWarningsList->buildErrorMessage(strValueOut, idDataGroup);
            }
         }          
      }
    }
  }
  else
      assert(0);

   if( bFormatted )
   {
      if(  YES == strValueOut )
         strValueOut = YES_STRING;
      else if( NO  == strValueOut ) 
         strValueOut = NO_STRING;
   }
}

//******************************************************************************
SEVERITY TradeVerificationProcess::doSetField(
                                       const GenericInterface *rpGICaller,
                                       const BFContainerId& idContainer,
                                       const BFFieldId& fieldID,
                                       const BFDataGroupId& idDataGroup,
                                       const DString& strValue,
                                       bool bFormatted
                                       )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "doSetField" ) );

   BFAbstractCBO *rpPtr = getCBOList (idContainer, idDataGroup);
   if( ifds::VerifyAll == fieldID )
   {
     if (rpPtr)
     {
         rpPtr->setField ( ifds::VerifyAll, strValue, idDataGroup, bFormatted, false );
         if ( _pTradeVerificationList )
             _pTradeVerificationList->markAllTradeToVerifyOrReject(idDataGroup);
     }
     else
     {
       assert(rpPtr);
     }
   }
   else if( ifds::DeleteAll == fieldID)
   {
     if (rpPtr)
     {
         rpPtr->setField ( ifds::DeleteAll, strValue, idDataGroup, bFormatted, false );
         if( _pTradeVerificationList )
             _pTradeVerificationList->markAllTradeToVerifyOrReject(idDataGroup);
     }
     else 
     {
      assert(rpPtr);
     }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
bool TradeVerificationProcess::doMoreRecordsExist( GenericInterface *rpGICaller,
                                             const BFContainerId& idSearch )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "doMoreRecordsExist" ) );

   if (!rpGICaller)
      return(false);

   if (IFASTBP_PROC::TRADE_VERIFICATION_LIST == idSearch)
      return _pTradeVerificationList == NULL ? false : _pTradeVerificationList->doMoreRecordsExist();
   else return false;
}

//******************************************************************************
bool TradeVerificationProcess::doModelessChildComplete( const Command &cmd )
{
  MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "doModelessChildComplete" ) );
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_TRADE_VERIFICATION_SEARCH );
}

//******************************************************************************
bool TradeVerificationProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
  
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "doModelessSetFocus" ) );

   bool bRtn = false; 
   
   if( isValidModelessInterface( _rpChildGI ) )
   {  // Only if child still exists
      bRtn = _rpChildGI->refresh( this, NULL );
      bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
   }

   return(bRtn);
}
//******************************************************************************
bool TradeVerificationProcess::isMoreThanOne()
{
  MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "isMoreThanOne" ) );

  if( _pTradeVerificationList )
  {
      return( _pTradeVerificationList->bMoreThanOne( getDataGroupId() )); 
  }
  return false;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/TradeVerificationProcess.cpp-arc  $
// 
//    Rev 1.0   Mar 03 2003 09:52:16   KOVACSRO
// Initial revision.
*/