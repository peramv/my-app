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
// ^FILE   : ACBProcess.cpp
// ^AUTHOR :  Zijian Ying
// ^DATE   : 04/19/1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : ACBProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include "acbprocess.hpp"
#include <ifastcbo\acblist.hpp>
#include "acbprocessincludes.h"
#include <ifastcbo\fundmasterlist.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\mfaccountholdinglist.hpp>
#include <ifastcbo\mgmtco.hpp>

#include <ifastcbo\dstcommonfunction.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_ACB;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACB;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< ACBProcess > processCreator( CMD_BPROC_ACB );

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "ACBProcess" );

   const I_CHAR *pALLFUND = I_( "AllFundMode" );
   const I_CHAR *pACCOUNTNUM = I_( "AccountNum" );
   const I_CHAR *pFUNDCODE = I_( "FundCode" );
   const I_CHAR *pCLASSCODE = I_( "ClassCode" );
   const I_CHAR *pCURRENCY = I_( "CurrencyName" );
   const I_CHAR *ACCCURRENCY = I_( "AccCurrency" );
   const I_CHAR *ACBOFFSET = I_( "ACBOffset"); //IN2684559(P0185327FN01)- ROC Design Change 
   const I_CHAR *YES = I_("Y");
   const I_CHAR *NO = I_("N");
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AcctACBAvailable;
   extern CLASS_IMPORT const BFTextFieldId FndClsACBAvailable;
   extern CLASS_IMPORT const BFDecimalFieldId ACBPlugAmt;
   extern CLASS_IMPORT const BFDateFieldId ACBPlugDate;
   extern CLASS_IMPORT const BFDateFieldId T5AnniversaryDate;
   extern CLASS_IMPORT const BFTextFieldId IsGIAFund;
   extern CLASS_IMPORT const BFDecimalFieldId GIAOpenMktValue;
}

namespace AUDITTYPE
{
   extern CLASS_IMPORT I_CHAR * const TRNDEC;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

ACBProcess::ACBProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pACBListList( NULL )
, _rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer (IFASTBP_PROC::MFACCOUNT_CBO,      false);
   addContainer (IFASTBP_PROC::ACB_LIST,           true, IFASTBP_PROC::MFACCOUNT_CBO, true,  I_("ACBList") );
   addContainer (IFASTBP_PROC::FUND_MASTER_LIST,   true );
   addContainer (IFASTBP_PROC::FUND_LIST,          true );

   addFieldDetails (ifds::rxFundCode      , IFASTBP_PROC::ACB_LIST );
   addFieldDetails (ifds::rxClassCode     , IFASTBP_PROC::ACB_LIST );
   addFieldDetails (ifds::TradeDate       , IFASTBP_PROC::ACB_LIST );
   addFieldDetails (ifds::TransAmount     , IFASTBP_PROC::ACB_LIST );
   addFieldDetails (ifds::Units           , IFASTBP_PROC::ACB_LIST );
   addFieldDetails (ifds::UnitsHeld       , IFASTBP_PROC::ACB_LIST );
   addFieldDetails (ifds::AdjustedCost    , IFASTBP_PROC::ACB_LIST );
   addFieldDetails (ifds::ACBPerUnit      , IFASTBP_PROC::ACB_LIST );
   addFieldDetails (ifds::GainOrLossAmt   , IFASTBP_PROC::ACB_LIST );
   addFieldDetails (ifds::GainOrLossCurrency   , IFASTBP_PROC::ACB_LIST );
   addFieldDetails (ifds::TransType       , IFASTBP_PROC::ACB_LIST );
   addFieldDetails (ifds::HistUnitACB     , IFASTBP_PROC::ACB_LIST );
   addFieldDetails (ifds::GIAOpenMktValue , IFASTBP_PROC::ACB_LIST);
   addFieldDetails (ifds::IsGIAFund       , IFASTBP_PROC::ACB_LIST, SUBCLASS_PROCESS);

   //--P0185327_FN01 - ROC Depleting ACB
   addFieldDetails (ifds::ACBOffset       , IFASTBP_PROC::ACB_LIST );
   addFieldDetails (ifds::ACBUnitOffset   , IFASTBP_PROC::ACB_LIST );
   addFieldDetails (ifds::TransId         , IFASTBP_PROC::ACB_LIST);
   addFieldDetails (ifds::TaxableAmount   , IFASTBP_PROC::ACB_LIST);

   addFieldDetails (ifds::ACBPlugAmt      , IFASTBP_PROC::ACB_LIST, SUBCLASS_PROCESS);
   addFieldDetails (ifds::ACBPlugDate     , IFASTBP_PROC::ACB_LIST, SUBCLASS_PROCESS);

   addFieldDetails (ifds::ElongName1      , IFASTBP_PROC::FUND_MASTER_LIST );

   addFieldDetails (ifds::rxFundCode      , IFASTBP_PROC::FUND_LIST );
   addFieldDetails (ifds::rxClassCode     , IFASTBP_PROC::FUND_LIST );
   addFieldDetails (ifds::FundNAV         , IFASTBP_PROC::FUND_LIST );
   addFieldDetails (ifds::FundCurrency    , IFASTBP_PROC::FUND_LIST );
   addFieldDetails (ifds::SettledValue    , IFASTBP_PROC::FUND_LIST );
   addFieldDetails (ifds::ACBSettledValue , IFASTBP_PROC::FUND_LIST );
   
   //account level flag
   addFieldDetails (ifds::AcctACBAvailable,     IFASTBP_PROC::FUND_LIST, SUBCLASS_PROCESS );
   addFieldDetails (ifds::FndClsACBAvailable,   IFASTBP_PROC::FUND_LIST );

   addFieldDetails (ifds::ShrNum,               IFASTBP_PROC::MFACCOUNT_CBO);
   addFieldDetails (ifds::T5AnniversaryDate,    IFASTBP_PROC::MFACCOUNT_CBO);
}

//******************************************************************************
ACBProcess::~ACBProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   if(_pACBListList)
   {
      delete _pACBListList;
      _pACBListList = NULL;
   }
   _rpChildGI = NULL;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************
SEVERITY ACBProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      getParameter( pACCOUNTNUM, _AccountNum );
      getParameter( pFUNDCODE, _FundCode );
      getParameter( pCLASSCODE, _ClassCode );

      _FundCode=_FundCode.upperCase();
      _ClassCode=_ClassCode.upperCase();

      DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

      FundMasterList *_pFundMasterList;
      sevRtn = dstcWorkSession->getMgmtCo().getFundMasterList( _pFundMasterList );
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::FUND_MASTER_LIST, _pFundMasterList );
      }
      else
      {
         return(GETCURRENTHIGHESTSEVERITY());
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      throw EXCEPTIONFROMFILE( CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool ACBProcess::doGetData( GenericInterface * ,
                            BFData * 
                          ) const
{
   ACBProcess *pThis = const_cast<ACBProcess*>(this);
   ACBList* pACBList = NULL;

   pACBList = 
      dynamic_cast<ACBList*>(pThis->getCBOList (IFASTBP_PROC::ACB_LIST, getDataGroupId()));

   if(pACBList)
   {
      pACBList->getMore();
   }

   return(true);
}

//******************************************************************************
bool ACBProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_ACB );
}

//******************************************************************************
void ACBProcess::doGetField(const GenericInterface *rpGICaller, 
                            const BFContainerId& idContainer,
                            const BFFieldId& idField, 
                            const BFDataGroupId& idDataGroup, 
                            DString &strValueOut, 
                            bool bFormatted) const
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doGetField") );
   strValueOut = NULL_STRING;

   if(idField == ifds::AcctACBAvailable) //for the fixed area
   {
      MFAccount* mfAccount;
      DSTCWorkSession* dstcWorkSession = 
         dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

      if (dstcWorkSession->getMFAccount( idDataGroup, _AccountNum, mfAccount ) <= WARNING) 
      {
         MFAccountHoldingList *pMFAccountHoldingList;

         if (mfAccount->getAccountHoldingList( pMFAccountHoldingList, idDataGroup ) 
               <= WARNING)
         {
            pMFAccountHoldingList->getField(ifds::AcctACBAvailable, strValueOut, 
               idDataGroup, bFormatted);
         }
      }
   }
   else if (IFASTBP_PROC::ACB_LIST == idContainer)
   {
       if (idField == ifds::ACBPlugAmt || idField == ifds::ACBPlugDate) 
       {
           ACBProcess* pThis = const_cast<ACBProcess*>(this);

           ACBList* pObj =
               dynamic_cast<ACBList*>(pThis->getCBOList( idContainer, idDataGroup ));

           if(pObj)
           {
               pObj->getField (idField, strValueOut, idDataGroup, bFormatted );
           }  
       }
       else if (idField == ifds::IsGIAFund)
       {
           DString dstrRxFundCode;
           FundMasterList *pFundMasterList = NULL;
           BFAbstractCBO *rpPtr = NULL;
           
           ACBList* pObj =dynamic_cast<ACBList*>(const_cast<ACBProcess*>(this)->getCBOList( idContainer, idDataGroup ));

           if (pObj)
           {
               rpPtr = const_cast<ACBProcess*>(this)->getCBOItem(IFASTBP_PROC::ACB_LIST, idDataGroup);
               pFundMasterList = dynamic_cast<FundMasterList*>(const_cast<ACBProcess*>(this)->getCBOList(IFASTBP_PROC::FUND_MASTER_LIST, idDataGroup));

               if (rpPtr && pFundMasterList)
               {
                   rpPtr->getField(ifds::rxFundCode, dstrRxFundCode, idDataGroup, false);
                   strValueOut = pFundMasterList->isGIAFund(dstrRxFundCode) ? YES:NO;
               }
           }
       }
   }
}

//******************************************************************************
SEVERITY ACBProcess::doSetField( const GenericInterface *rpGICaller,
                                 const BFContainerId& idContainer,
                                 const BFFieldId& idField,
                                 const BFDataGroupId& idDataGroup,
                                 const DString& strValue,
                                 bool bFormatted)
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doSetField") );

   // If we try to set a field this should be overridden
   if (IFASTBP_PROC::ACB_LIST == idContainer)
   {
      if (idField == ifds::ACBPlugAmt || 
          idField == ifds::ACBPlugDate )
      {
         ACBProcess* pThis = const_cast<ACBProcess*>(this);

         ACBList* pObj =
            dynamic_cast<ACBList*>(pThis->getCBOList( IFASTBP_PROC::ACB_LIST, idDataGroup ));

         if(pObj)
         {
            pObj->setField (idField, strValue, idDataGroup, bFormatted );
         }
      }
   }

   return(NO_CONDITION);
}

//******************************************************************************
const BFProperties *ACBProcess::doGetFieldAttributes ( const GenericInterface *rpGICaller, 
                                                       const BFContainerId &idContainer, 
                                                       const BFFieldId &idField, 
                                                       const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, CLASSNAME, DOGETFIELDATTRIBUTES );

   const BFProperties *pBFProperties = NULL;

   if (idContainer == IFASTBP_PROC::ACB_LIST && 
      ( idField == ifds::ACBPlugAmt || idField == ifds::ACBPlugDate ) )
   {
      ACBProcess* pThis = const_cast<ACBProcess*>(this);

      ACBList* pObj =
         dynamic_cast<ACBList*>(pThis->getCBOList( IFASTBP_PROC::ACB_LIST, idDataGroup ));

      if(pObj)
      {
         pBFProperties = 
            pObj->getFieldProperties (idField, idDataGroup);
      }
   }

   return pBFProperties;
}

//******************************************************************************
bool ACBProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   bool bRtn = false;

   bool lNeedSearchAgain = false;

   DString AccountNum, FundCode, ClassCode;
   getParameter( pACCOUNTNUM, AccountNum );
   getParameter( pFUNDCODE, FundCode );
   getParameter( pCLASSCODE, ClassCode );

   _FundCode=_FundCode.upperCase();
   _ClassCode=_ClassCode.upperCase();

   if( AccountNum != _AccountNum )
   {
      _AccountNum=AccountNum;
      lNeedSearchAgain = true;
   }

   if( FundCode != _FundCode )
   {
      _FundCode=FundCode;
      lNeedSearchAgain = true;
   }

   if( ClassCode != _ClassCode )
   {
      _ClassCode=ClassCode;
      lNeedSearchAgain = true;
   }

   if( lNeedSearchAgain = true )
   {
      setParameter( pACCOUNTNUM, _AccountNum );
      setParameter( pFUNDCODE, _FundCode );
      setParameter( pCLASSCODE, _ClassCode );
      setParameter( ACCCURRENCY, _AccountCurrency);
      performSearch(this, BF::AllContainerIds, SEARCH_START);
   };

   if( _rpChildGI && isValidModelessInterface( _rpChildGI ) )
   {
      bRtn = _rpChildGI->refresh( this, NULL );
      bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
   }
   return(bRtn);
}

//******************************************************************************
bool ACBProcess::doMoreRecordsExist( GenericInterface *rpGICaller,
                                    const BFContainerId& idContainer )
{
   ACBProcess *pThis = const_cast<ACBProcess*>(this);
   ACBList* pACBList = NULL;

   pACBList = 
      dynamic_cast<ACBList*>(pThis->getCBOList (IFASTBP_PROC::ACB_LIST, getDataGroupId()));

   if(pACBList)
   {
      return(pACBList->doMoreRecordsExist());
   }
   else
   {
      return false;
   }
}

//******************************************************************************
E_COMMANDRETURN ACBProcess::doProcess()
{  
   MAKEFRAME2( CND::IFASTBP_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter( pACCOUNTNUM, _AccountNum );
      setParameter( pFUNDCODE, _FundCode );
      setParameter( pCLASSCODE, _ClassCode );
      setParameter( ACCCURRENCY, _AccountCurrency);
      rtn = invokeCommand( this, CMD_GUI_ACB, getProcessType(), isModal(), &_rpChildGI);
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      throw EXCEPTIONFROMFILE( CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(rtn);
}

//******************************************************************************
SEVERITY ACBProcess::performSearch( GenericInterface *rpGI, 
                                    const BFContainerId& idSearch, 
                                    E_SEARCHACTION eSearchAction)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_("performSearch") );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      if(eSearchAction == SEARCH_START)
      {
         getParameter( pACCOUNTNUM, _AccountNum );
         getParameter( pFUNDCODE, _FundCode );
         getParameter( pCLASSCODE, _ClassCode );

         _FundCode=_FundCode.upperCase();
         _ClassCode=_ClassCode.upperCase();

         DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

         MFAccount* mfAccount;
         dstcWorkSession->getMFAccount( getDataGroupId(), _AccountNum, mfAccount );

         ACBList* pACBList = NULL;
         if(mfAccount && 
            mfAccount->getACBList(pACBList, getDataGroupId(), _FundCode,_ClassCode ) <= WARNING &&
            pACBList != NULL )
         {
            setContainer( IFASTBP_PROC::ACB_LIST, pACBList );
            pACBList->getField(ifds::CurrencyName, _AccountCurrency, BF::HOST);
            _AccountCurrency.strip();
            setParameter( ACCCURRENCY, _AccountCurrency);  
         }
         else
         {
            return(GETCURRENTHIGHESTSEVERITY());
         }
      }
      else if (eSearchAction == SEARCH_NEXT_BLOCK)
      {
         if (idSearch == IFASTBP_PROC::ACB_LIST)
         {
            if( doMoreRecordsExist (this, idSearch))
            {
               ACBProcess *pThis = const_cast<ACBProcess*>(this);
               ACBList* pACBList = NULL;

               pACBList = 
                  dynamic_cast<ACBList*>(pThis->getCBOList (idSearch, getDataGroupId()));

               if(pACBList)
               {
                  pACBList->getMore();
               }
            }
         }
      }      
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      throw EXCEPTIONFROMFILE( CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool ACBProcess::doRefresh( GenericInterface *rpGICaller, 
                            const I_CHAR *szOriginalCommand )
{
   TRACE_METHOD( CLASSNAME, DOREFRESH );

   setParameter( pACCOUNTNUM, _AccountNum );
   setParameter( pFUNDCODE, _FundCode );
   setParameter( pCLASSCODE, _ClassCode );
   setParameter( ACCCURRENCY, _AccountCurrency);

   return(_rpChildGI->refresh( this, NULL ));
}

//******************************************************************************
//P0185327_FN01 - ROC Depleting ACB
SEVERITY ACBProcess::getHistoricalParameters ( const BFContainerId &idContainer, 
                                                        BFFieldId &recordIdField, 
                                                        DString &tableId, 
                                                        DString &dstrKeys) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           GETHISTORICALPARAMETERS);

   DString transId,
      keyStringIDI; 

   if (idContainer == IFASTBP_PROC::ACB_LIST)
   {
      recordIdField = ifds::NullFieldId;
      tableId = AUDITTYPE::TRNDEC;

      getField(this, IFASTBP_PROC::ACB_LIST, ifds::TransId, transId, false);

      addIDITagValue(keyStringIDI, I_("TransId"), transId );
      addIDITagValue(keyStringIDI, I_("ACBOffset"), ACBOFFSET ); //IN2684559(P0185327FN01)- ROC Design Change 
      dstrKeys = keyStringIDI;
   }
   else 
   {
      assert(0);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ACBProcess::getHistoricalParameters ( const BFContainerId& idContainer,
                                               HISTORICAL_VECTOR &vectorInput )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           GETHISTORICALPARAMETERS);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void *ACBProcess::getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
	if(idContainer == IFASTBP_PROC::FUND_LIST)
	{

		MFAccount* mfAccount;
		dynamic_cast<DSTCWorkSession*>(getBFWorkSession())->getMFAccount( getDataGroupId(), _AccountNum, mfAccount );

		DString dstrShrNum;
		mfAccount->getField(ifds::ShrNum, dstrShrNum, BF::HOST);
		setContainer(IFASTBP_PROC::MFACCOUNT_CBO, mfAccount);

		MFAccountHoldingList *pMFAccountHoldingList;
		auto sevRtn = mfAccount->getAccountHoldingList( pMFAccountHoldingList, getDataGroupId() );
		if( WARNING >= sevRtn )
		{
			return pMFAccountHoldingList;
		}
	}

	return AbstractProcess::getPtrForContainer(idContainer, idDataGroup);
}

//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ACBProcess.cpp-arc  $
 * 
 *    Rev 1.22   May 14 2012 10:07:26   kitticha
 * P0186477 FN06 - T5 Processing.
 * 
 *    Rev 1.21   Oct 10 2011 06:03:04   panatcha
 * IN2684559(P0185327FN01)- ROC Design Change
 * 
 *    Rev 1.20   Oct 10 2011 05:51:12   panatcha
 * IN2684559(P0185327FN01)- ROC Design Change 
 * 
 *    Rev 1.19   Sep 14 2011 10:05:38   panatcha
 * P0185327_FN01 - ROC Depleting ACB
 * 
 *    Rev 1.18   Nov 30 2007 14:41:24   jankovii
 * Sync up. PET 5517 FN01B - Gap1.
 * 
 *    Rev 1.17   19 Nov 2007 12:16:34   kovacsro
 * PET 2313 FN11 - added  ACBSettledValue
 * 
 *    Rev 1.16   Jun 28 2004 16:39:04   AGUILAAM
 * PET1084_FN1 : display redirected transactions, applicable for ACB only
 * 
 *    Rev 1.15   Apr 12 2003 15:13:48   VADEANUM
 * PTS10009117 - Currency related calculations - Display Fund Currency for clarification.
 * 
 *    Rev 1.14   Apr 02 2003 12:18:56   PURDYECH
 * Code cleanup
 * 
 *    Rev 1.13   Mar 21 2003 17:33:30   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.12   Feb 05 2003 11:08:12   popescu
 * Displaying the ACB string when ACB cannot be calculated
 * 
 *    Rev 1.11   Oct 09 2002 23:52:54   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.10   Aug 29 2002 16:42:28   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.9   Aug 29 2002 12:54:06   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.8   22 May 2002 18:23:42   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.7   27 Mar 2002 19:54:24   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.6   Jun 05 2001 09:50:58   YINGBAOL
 * fix refresh issue---sync version 1.4.1.0
 * 
 *    Rev 1.5   03 May 2001 14:05:12   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.4   15 Dec 2000 12:43:10   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.3   30 Oct 2000 11:25:22   SMITHDAV
 * Change back to doMoreRecordsExist.
 * 
 *    Rev 1.2   Aug 02 2000 13:45:38   VADEANUM
 * Title Bar Standards
 * 
 *    Rev 1.1   Mar 07 2000 15:36:24   DT24433
 * removed substitute list
 * 
 *    Rev 1.0   Feb 15 2000 10:59:30   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.13   Jan 08 2000 14:32:52   POPESCUS
 * added the datagroupid when quering for children lists
 * 
 *    Rev 1.12   Jan 06 2000 09:57:54   POPESCUS
 * cleanup code and remove some unused methods
 * 
 *    Rev 1.11   Jan 05 2000 12:07:04   YINGZ
 * add process support
 * 
 *    Rev 1.10   Nov 01 1999 17:57:40   DT24433
 * removed doOk/doCancel
 * 
 *    Rev 1.9   Oct 29 1999 11:30:10   BUZILA
 * changing WorkSessionDetails into a BFBase descendant
 * 
 *    Rev 1.8   Sep 30 1999 09:53:50   YINGZ
 * use sub list
 * 
 *    Rev 1.7   Aug 17 1999 12:25:54   DT24433
 * changes to remove static FieldDetails array
 * 
 *    Rev 1.6   Aug 05 1999 17:20:40   YINGZ
 * ?
 * 
 *    Rev 1.5   Aug 04 1999 20:55:46   VASILEAD
 * Add support for multiple currency
 * 
 *    Rev 1.4   Jul 26 1999 14:28:42   YINGZ
 * doModelessChildComplete
 * 
 *    Rev 1.3   Jul 20 1999 14:25:32   YINGZ
 * fund list should also be refreshed
 * 
 *    Rev 1.2   Jul 20 1999 11:13:28   VASILEAD
 * New conditions update
 * 
 *    Rev 1.1   Jul 08 1999 10:01:46   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
