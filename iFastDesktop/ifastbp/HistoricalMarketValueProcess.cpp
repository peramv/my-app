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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : HistoricalMarketValueProcess.cpp
// ^AUTHOR : 
// ^DATE   : 03/09/1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : HistoricalMarketValueProcess
//    This class manages the remarks information.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "historicalmarketvalueprocess.hpp"
#include <ifastcbo\historicalmarketvaluelist.hpp>
#include "historicalmarketvalueprocessincludes.h"
#include <ifastcbo\funddetaillist.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\mfaccountholdinglist.hpp>
#include <ifastcbo\HistoricalMarketValue.hpp>
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_HISTORICAL_MARKET_VALUE;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_HISTORICAL_MARKET_VALUE;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< HistoricalMarketValueProcess > processCreator(CMD_BPROC_HISTORICAL_MARKET_VALUE);

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_("HistoricalMarketValueProcess");
   const I_CHAR * const PERFORMSEARCH = I_("performSearch");
   const I_CHAR * const AS_OF_DATE = I_("AsofDate");
   const I_CHAR * const ACCOUNT_NUM = I_("AccountNum");
   const I_CHAR * const FUND_CODE = I_("FundCode");
   const I_CHAR * const CLASS_CODE = I_("ClassCode");
   const I_CHAR * const FULL_REFRESH = I_("FullRefresh");
   const I_CHAR * const PARTIAL_REFRESH = I_("PartialRefresh");
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern const long BP_ERR_ACCOUNT_WAS_NOT_ACTIVE;
   extern CLASS_IMPORT const long BP_ERR_INVALID_METHOD_CALL;
}


//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319HistoricalMarketValueProcess::HistoricalMarketValueProcess() : 
HistoricalMarketValueProcess::HistoricalMarketValueProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pHistoricalMarketValueList(0),
_rpChildGI(0)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);

   addContainer(IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, true);
   addContainer(IFASTBP_PROC::FUND_DETAIL_LIST, true);
   addContainer(IFASTBP_PROC::MFACCOUNT_CBO, false);
//repeat part
   addFieldDetails(ifds::rxFundCode, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST);
   addFieldDetails(ifds::rxClassCode, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST);
   addFieldDetails(ifds::SettledUnits, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST);
   addFieldDetails(ifds::SettledValue, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST);
   addFieldDetails(ifds::UnsettledUnits, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST);
   addFieldDetails(ifds::UnsettledValue, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST);
   addFieldDetails(ifds::FundNAV, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST);
   addFieldDetails(ifds::AsAtDate, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST);
   addFieldDetails(ifds::ACBSettl, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST);
   addFieldDetails(ifds::ACBTotal, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST);
   addFieldDetails(ifds::ACBSettlPrcnt, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST);
   addFieldDetails(ifds::ACBTotalPrcnt, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST);
   addFieldDetails(ifds::SettledValueAcctCurr, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST);
   addFieldDetails(ifds::CombValueAcctCurr, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST);
   addFieldDetails(ifds::MktValSettlPrcnt, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST);
   addFieldDetails(ifds::MktValTotalPrcnt, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST);
   addFieldDetails(ifds::FndClsACBAvailable, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST);
   addFieldDetails(ifds::FundGroup, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST);


//fix part
   addFieldDetails(ifds::AccountBalance, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST,SUBCLASS_PROCESS);
   addFieldDetails(ifds::TotalValueAcctCurr, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST,SUBCLASS_PROCESS);
   addFieldDetails(ifds::FrgnBalance, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, SUBCLASS_PROCESS);
   // addFieldDetails(DBR::FrgnACB, HISTORICAL_MARKET_VALUE_LIST, SUBCLASS_PROCESS);
   addFieldDetails(ifds::FrgnExcsACBUnsettl, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, SUBCLASS_PROCESS);
   addFieldDetails(ifds::TotalACBSettl, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, SUBCLASS_PROCESS);
   addFieldDetails(ifds::TotalACBUnSettl, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, SUBCLASS_PROCESS);
   addFieldDetails(ifds::FrgnACBSettl, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST,SUBCLASS_PROCESS);
   addFieldDetails(ifds::FrgnACBUnsettl, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, SUBCLASS_PROCESS);
   addFieldDetails(ifds::AcctACBAvailable, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, SUBCLASS_PROCESS);

   addFieldDetails(ifds::DomesticACBSettl, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST,SUBCLASS_PROCESS);
   addFieldDetails(ifds::DomesticACBUnSettl, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, SUBCLASS_PROCESS);
   addFieldDetails(ifds::FrgnAllowPrcnt, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, SUBCLASS_PROCESS);
   addFieldDetails(ifds::FrgnAllowACBSettl, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, SUBCLASS_PROCESS);
   addFieldDetails(ifds::FrgnAllowACBUnSettl, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, SUBCLASS_PROCESS);
   addFieldDetails(ifds::FrgnExcsPrcntUnSettl, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, SUBCLASS_PROCESS);
   addFieldDetails(ifds::FrgnExcsPrcntSettl, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, SUBCLASS_PROCESS);
   addFieldDetails(ifds::FrgnExcsACBSettl, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, SUBCLASS_PROCESS);
   addFieldDetails(ifds::Domestic, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, SUBCLASS_PROCESS);
   addFieldDetails(ifds::FundGroupTotalSettledValue, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, SUBCLASS_PROCESS);
   addFieldDetails(AMT_INV_APPL, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, SUBCLASS_PROCESS);

//Fund detail
   addFieldDetails(ifds::FundCode, IFASTBP_PROC::FUND_DETAIL_LIST);
   addFieldDetails(ifds::ClassCode, IFASTBP_PROC::FUND_DETAIL_LIST);
   addFieldDetails(ifds::Currency, IFASTBP_PROC::FUND_DETAIL_LIST);
   addFieldDetails(ifds::Baycom, IFASTBP_PROC::FUND_DETAIL_LIST);
   addFieldDetails(ifds::AccountNum, IFASTBP_PROC::MFACCOUNT_CBO);
   addFieldDetails(ifds::CurrencyName, IFASTBP_PROC::MFACCOUNT_CBO);
   addFieldDetails(ifds::ShrNum, IFASTBP_PROC::MFACCOUNT_CBO);
}

//******************************************************************************

HistoricalMarketValueProcess::~HistoricalMarketValueProcess()
{
   TRACE_DESTRUCTOR(CLASSNAME);

   delete _pHistoricalMarketValueList;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY HistoricalMarketValueProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, DOINIT);
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      DString strAccountNumber;
      getParameter(ACCOUNT_NUM, strAccountNumber);
      //assert(_strInitFundCode == NULL_STRING && _strInitClassCode == NULL_STRING);
      getParameter(FUND_CODE, _strInitFundCode);
      //assert(_strInitFundCode != NULL_STRING);
      _strInitFundCode.stripLeading().stripTrailing().upperCase();
      getParameter(CLASS_CODE, _strInitClassCode);
      //assert(_strInitClassCode != NULL_STRING);
      _strInitClassCode.stripLeading().stripTrailing().upperCase();

      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

      dstcWorkSession->getMFAccount(getDataGroupId(), strAccountNumber, _pMFAccount);

      DString dstrShrNum;      
      _pMFAccount->getField(ifds::ShrNum,dstrShrNum,BF::HOST);

      //register CBO with base
      setContainer(IFASTBP_PROC::MFACCOUNT_CBO, _pMFAccount);

      dstcWorkSession->getMgmtCo().getFundDetailList(_pFundDetailList);
      //register list with base
      setContainer(IFASTBP_PROC::FUND_DETAIL_LIST, _pFundDetailList);

      //register NULL with base (the actual list has not been created yet)
      setContainer(IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, 0);
   }
   catch(ConditionException &ce)
   {
      SETCONDITIONFROMEXCEPTION(ce);
   }
   catch(...)
   {
      assert(0);
      THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

bool HistoricalMarketValueProcess::doModelessChildComplete(const Command &cmd)
{
   // End when GUI ends
   return(cmd.getKey() == CMD_GUI_HISTORICAL_MARKET_VALUE);
}

//******************************************************************************

bool HistoricalMarketValueProcess::doModelessSetFocus(
                                                     GenericInterface *rpGICaller)
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS);

   SEVERITY severity = SEVERE_ERROR;
   bool bRtn = false;
   try
   {
      assert(_rpChildGI && isValidModelessInterface(_rpChildGI));

      DString strOldAccountNumber, strNewAccountNumber;
      _pMFAccount->getField(ifds::AccountNum, strOldAccountNumber, BF::HOST);
      strOldAccountNumber.stripLeading().stripLeading(I_CHAR('0')).
      stripTrailing();
      getParameter(ACCOUNT_NUM, strNewAccountNumber);

      DString strNewInitFundCode, strNewInitClassCode;
      getParameter(FUND_CODE, strNewInitFundCode);
      strNewInitFundCode.stripLeading().stripTrailing().upperCase();
      getParameter(CLASS_CODE, strNewInitClassCode);
      strNewInitClassCode.stripLeading().stripTrailing().upperCase();

      if(strNewAccountNumber != strOldAccountNumber)
      {
         delete _pHistoricalMarketValueList;
         _pHistoricalMarketValueList = 0;
         //register NULL with base (the previous list has been destroyed)
         setContainer(IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, 0);

         DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
         severity = dstcWorkSession->getMFAccount(getDataGroupId(), strNewAccountNumber, _pMFAccount);

         DString dstrShrNum;      
         _pMFAccount->getField(ifds::ShrNum,dstrShrNum,BF::HOST);

         //register CBO with base
         setContainer(IFASTBP_PROC::MFACCOUNT_CBO, _pMFAccount);

         _strInitFundCode = strNewInitFundCode;
         _strInitClassCode = strNewInitClassCode;
         setParameter(FUND_CODE, _strInitFundCode);
         setParameter(CLASS_CODE, _strInitClassCode);

#ifdef _DEBUG
         FundDetailList *pFundDetailList;
         dstcWorkSession->getMgmtCo().getFundDetailList(pFundDetailList);
         assert(pFundDetailList == _pFundDetailList); 
#endif

         bRtn = _rpChildGI->refresh(this, FULL_REFRESH);
         //if(!(bRtn = _rpChildGI->refresh(this, FULL_REFRESH)))
         //	return bRtn;// false
      }
      else if(strNewInitFundCode != _strInitFundCode 
               || strNewInitClassCode != _strInitClassCode)
      {
         _strInitFundCode = strNewInitFundCode;
         _strInitClassCode = strNewInitClassCode;
         setParameter(FUND_CODE, _strInitFundCode);
         setParameter(CLASS_CODE, _strInitClassCode);

         if(!(bRtn = _rpChildGI->refresh(this, PARTIAL_REFRESH)))
            return(bRtn);// false
      }

      bRtn = _rpChildGI->modelessSetFocus(rpGICaller);
   }
   catch(ConditionException &ce)
   {
      SETCONDITIONFROMEXCEPTION(ce);
   }
   catch(...)
   {
      assert(0);
      THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS,
                      CND::BP_ERR_UNKNOWN_EXCEPTION);
   }

   return(bRtn);
}

//******************************************************************************

E_COMMANDRETURN HistoricalMarketValueProcess::doProcess()
{  
   MAKEFRAME2(CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS);
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter(FUND_CODE, _strInitFundCode);
      setParameter(CLASS_CODE, _strInitClassCode);

      rtn = invokeCommand(this, CMD_GUI_HISTORICAL_MARKET_VALUE, 
                           getProcessType(), isModal(), &_rpChildGI);
   }
   catch(ConditionException &ce)
   {
      SETCONDITIONFROMEXCEPTION(ce);
   }
   catch(...)
   {
      assert(0);
      THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS,
                      CND::BP_ERR_UNKNOWN_EXCEPTION);
   }

   return(rtn);
}

//******************************************************************************

/*const DString& HistoricalMarketValueProcess::getFirstListItemKey(
                              const GenericInterface *rpGICaller, int idList)
{
   TRACE_METHOD(CLASSNAME, GETFIRSTLISTITEMKEY);

  const DString *strKeyList = &AbstractProcess::getFirstListItemKey(rpGICaller, idList);
   if (idList == FUNDS_LIST)
   {
      try
      {
         //ListDetails &fundListDetails = findList(FUNDS_LIST);
         //DString keyFundsList = fundListDetails.getFirstKey(); 
         while(*strKeyList != NULL_STRING)
         {
        DString strFundCode;
        getField(this, FUNDS_LIST, FUND_CODE_, strFundCode);
            DString strMasterFundCode;
            _pFundMasterList->buildKey(strFundCode, strMasterFundCode);
            DString strFundType;
            _pFundMasterList->getField(strMasterFundCode, I_("FundType"), strFundType);
        stripLeading(strFundType);
        stripTrailing(strFundType);
            if (strFundType == I_("I"))
            {
               break;
            }
        strKeyList = &AbstractProcess::getNextListItemKey(rpGICaller, FUNDS_LIST);
         }
      }
      catch(ConditionException &)
      {
         throw;
      }
      catch(...)
      {  // Just to catch at earliest point
         assert(0);
         THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, GETFIRSTLISTITEMKEY,
            CND::BP_ERR_UNKNOWN_EXCEPTION);
      }
   }
  return *strKeyList;
}

//******************************************************************************

const DString& HistoricalMarketValueProcess::getNextListItemKey(
                              const GenericInterface *rpGICaller, int idList)
{
   TRACE_METHOD(CLASSNAME, GETNEXTLISTITEMKEY);

  const DString *strKeyList = &AbstractProcess::getNextListItemKey(rpGICaller, idList);
   if (idList == FUNDS_LIST)
   {
      try
      {
         while(*strKeyList != NULL_STRING)
         {
        DString strFundCode;
        getField(this, FUNDS_LIST, FUND_CODE_, strFundCode);

            DString strMasterFundCode;
            _pFundMasterList->buildKey(strFundCode, strMasterFundCode);
            DString strFundType;
            _pFundMasterList->getField(strMasterFundCode, I_("FundType"), strFundType);
        stripLeading(strFundType);
        stripTrailing(strFundType);
            if (strFundType == I_("I"))
            {
               break;
            }
        strKeyList = &AbstractProcess::getNextListItemKey(rpGICaller, FUNDS_LIST);
         }
      }
      catch(ConditionException &)
      {
         throw;
      }
      catch(...)
      {  // Just to catch at earliest point
         assert(0);
         THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, GETNEXTLISTITEMKEY,
            CND::BP_ERR_UNKNOWN_EXCEPTION);
      }
   }
  return *strKeyList;
}*/

//******************************************************************************

SEVERITY HistoricalMarketValueProcess::performSearch(GenericInterface *rpGI, 
                                                      const BFContainerId& idSearch, E_SEARCHACTION eSearchAction)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTBP_CONDITION, CLASSNAME, PERFORMSEARCH);
   assert(eSearchAction == SEARCH_START);
   SEVERITY sevRtn = SEVERE_ERROR;
   SEVERITY sevRtn1 = SEVERE_ERROR;

   try
   {
      delete _pHistoricalMarketValueList; 
      //register NULL with base (the previous list has been destroyed)
      setContainer(IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, NULL);
      _pHistoricalMarketValueList = new HistoricalMarketValueList(*getBFWorkSession());

      DString strAccountNumber, strAsOfDate;
//		_pMFAccount->getField(MFAccount::ACCOUNT_NUMBER, strAccountNumber);
      _pMFAccount->getField(ifds::AccountNum, strAccountNumber, BF::HOST);
      strAccountNumber.stripLeading().stripLeading(I_CHAR('0')).
      stripTrailing();
      getParameter(AS_OF_DATE, strAsOfDate);

      DString tmpDate;
      _pMFAccount->getField(ifds::FirstEffective, tmpDate, BF::HOST, false);

      if(DSTCommonFunctions::CompareDates(strAsOfDate, tmpDate) == DSTCommonFunctions::FIRST_EARLIER)
      {
         setContainer(IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, NULL);
         sevRtn = SEVERE_ERROR;
         SEVERITY sevRtn1 = SEVERE_ERROR;
         ADDCONDITIONFROMFILE(CND::BP_ERR_ACCOUNT_WAS_NOT_ACTIVE); // Pune conditie: No search criteria has been found
      }
      else
      {
         sevRtn = _pHistoricalMarketValueList->init(strAccountNumber, strAsOfDate);
         if(WARNING >= sevRtn)
         {
            //register list with base
            setContainer(IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, _pHistoricalMarketValueList);
            /*sevRtn = _pHistoricalMarketValueList->search();*/
         }
      }
   }
   catch(ConditionException &ce)
   {
      SETCONDITIONFROMEXCEPTION(ce);
   }
   catch(...)
   {
      assert(0);
      THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, PERFORMSEARCH, 
                      CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return(sevRtn); 
}
//****************************************************************************
bool  HistoricalMarketValueProcess::doRefresh(
                                             GenericInterface *rpGICaller,
                                             const I_CHAR *szOriginalCommand
                                            )
{
   setParameter(FUND_CODE, _strInitFundCode);
   setParameter(CLASS_CODE, _strInitClassCode);
   return(_rpChildGI->refresh(this, FULL_REFRESH));
}
//****************************************************************************

void HistoricalMarketValueProcess::doGetField(
                                             const GenericInterface *rpGICaller,
                                             const BFContainerId& idContainer,
                                             const BFFieldId& idField,
                                             const BFDataGroupId& idDataGroup, 
                                             DString &strValueOut,
                                             bool bFormatted
                                            ) const
{  
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("doGetField"));
   strValueOut = NULL_STRING;

   if(isFixedPartField(idField))
   {
      if(_pHistoricalMarketValueList)
         _pHistoricalMarketValueList->getField(idField, strValueOut, idDataGroup, bFormatted);
   }
   else if(idField == ifds::Domestic)
   {
      DString dstrFundCode,dstrClassCode;
      const_cast< HistoricalMarketValueProcess * >(this)->
         getField(rpGICaller, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST,ifds::rxFundCode, dstrFundCode);  
      const_cast< HistoricalMarketValueProcess * >(this)->
         getField(rpGICaller, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST,ifds::rxClassCode, dstrClassCode);  
      dstrClassCode.strip().upperCase();
      dstrFundCode.strip().upperCase();
      _pFundDetailList->getField(dstrFundCode, dstrClassCode,idField, strValueOut, idDataGroup, bFormatted);
   } else if (idField == ifds::FundGroupTotalSettledValue)
   {
      if (_pHistoricalMarketValueList != NULL)
      {
         DString dstrFundGroup;
   
         const_cast< HistoricalMarketValueProcess * >(this)->
            getField(rpGICaller, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, 
            ifds::FundGroup, dstrFundGroup);
         _pHistoricalMarketValueList->calculateFundGroupTotal(dstrFundGroup, 
            strValueOut, idDataGroup);
      }
   } 
   else if (idContainer == IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST && idField == AMT_INV_APPL)
   {
       strValueOut = I_("N");

       if (_pHistoricalMarketValueList != NULL)
       {
           HistoricalMarketValue *pHistMktVal = NULL;
           HistoricalMarketValueProcess* pThis = const_cast<HistoricalMarketValueProcess*>(this);

           pHistMktVal = dynamic_cast<HistoricalMarketValue*>(pThis->getCBOItem(IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, idDataGroup));

           if (pHistMktVal)
           {
               strValueOut = pHistMktVal->amountInventoryAppl() ? I_("Y"):I_("N");
           }
       }
   }
   else
   {
      assert(0);   
      THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, GETFIELD, CND::BP_ERR_INVALID_METHOD_CALL);
   };
}

//****************************************************************************
SEVERITY HistoricalMarketValueProcess::doSetField(
                                                 const GenericInterface *rpGICaller, 
                                                 const BFContainerId& idContainer, 
                                                 const BFFieldId& idField,
                                                 const BFDataGroupId& idDataGroup, 
                                                 const DString& strValue, 
                                                 bool bFormatted
                                                ) 
{  
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("doSetField"));
   assert(0);
   THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, SETFIELD, CND::BP_ERR_INVALID_METHOD_CALL);

   return(GETCURRENTHIGHESTSEVERITY());
}
//************************************************************************************
bool  HistoricalMarketValueProcess::isFixedPartField(const BFFieldId& idField) const
{
   if(idField == ifds::AccountBalance 
       || idField == ifds::TotalValueAcctCurr 
       || idField == ifds::FrgnBalance
       || idField == ifds::FrgnExcsACBUnsettl 
       || idField == ifds::TotalACBSettl
       || idField == ifds::TotalACBUnSettl 
       || idField == ifds::FrgnACBSettl 
       || idField == ifds::DomesticACBSettl
       || idField == ifds::DomesticACBUnSettl 
       || idField == ifds::FrgnAllowPrcnt 
       || idField == ifds::FrgnAllowACBSettl
       || idField == ifds::FrgnAllowACBUnSettl 
       || idField == ifds::FrgnExcsPrcntUnSettl 
       || idField == ifds::FrgnExcsPrcntSettl
       || idField == ifds::FrgnExcsACBSettl 
       || idField == ifds::FrgnACBUnsettl
       || idField == ifds::AcctACBAvailable
    ) return(true);
   else return(false);
}



//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/HistoricalMarketValueProcess.cpp-arc  $
 * 
 *    Rev 1.30   Jun 12 2003 17:32:58   ZHANGCEL
 * Bug fix for the screen failed to display value because logic checking the MFAccount Effective Date. It should check the ifds::FirstEffective instead. 
 * 
 *    Rev 1.29   Mar 21 2003 17:41:12   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.28   Feb 17 2003 14:23:42   popescu
 * Added a field for th calculation of the total market value by FundGroup
 * 
 *    Rev 1.27   Feb 17 2003 11:12:00   popescu
 * Displayed the Fund Group in the HistoricalMarketValue dialog
 * 
 *    Rev 1.26   Feb 07 2003 09:40:08   popescu
 * Changes related to the FndClassACBAvailable flag for Historical Market Value/ ACB
 * 
 *    Rev 1.25   Feb 05 2003 11:08:18   popescu
 * Displaying the ACB string when ACB cannot be calculated
 * 
 *    Rev 1.24   Oct 09 2002 23:53:18   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.23   Oct 08 2002 11:57:20   HSUCHIN
 * sync up with 1.18.1.0
 * 
 *    Rev 1.22   Oct 07 2002 16:46:52   PURDYECH
 * It took a week for somebody to notice a simple compile bug!
 * 
 *    Rev 1.21   Sep 30 2002 14:56:56   PURDYECH
 * Oopsy doopsy
 * 
 *    Rev 1.20   Sep 30 2002 14:56:16   PURDYECH
 * Oopsy
 * 
 *    Rev 1.19   Sep 30 2002 11:01:04   PURDYECH
 * BFFieldId no longer has operator long(), so explicit getId() calls are needed in places.
 * 
 *    Rev 1.18   Sep 04 2002 15:45:46   PURDYECH
 * Condition, comment and formatting cleanup
 * 
 *    Rev 1.17   Aug 29 2002 16:44:56   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.16   Aug 29 2002 12:54:22   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.15   22 May 2002 18:24:18   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.14   27 Mar 2002 19:54:56   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.13   Feb 18 2002 10:32:36   YINGBAOL
 * foreign content enhancement
 * 
 *    Rev 1.12   Feb 05 2002 10:38:20   YINGBAOL
 * add more fields
 * 
 *    Rev 1.11   28 Dec 2001 14:58:30   KOVACSRO
 * Removed HISTORICAL_MARKET_VALUE container. Treated FrgnACB field as SUBCLASS_PROCESS using the existing container rather than create a new container containing the same data. View 20 is called only once now (it used to be called twice before). In a word, did some tuneup.
 * 
 *    Rev 1.9   Jun 07 2001 11:00:46   YINGBAOL
 * fix refresh
 * 
 *    Rev 1.8   03 May 2001 14:05:26   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.7   15 Dec 2000 12:43:32   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.6   Aug 02 2000 13:43:32   VADEANUM
 * Title Bar Standards
 * 
 *    Rev 1.5   Jul 31 2000 14:47:22   VADEANUM
 * Title Bar Standards
 * 
 *    Rev 1.4   Jul 07 2000 10:24:08   ZHANGCEL
 * Deal with the leap year problem
 * 
 *    Rev 1.3   Mar 08 2000 18:43:44   HSUCHIN
 * C2 stuff
 * 
 *    Rev 1.2   Feb 21 2000 17:29:12   MCNABBGL
 * changed CND to import linkage
 * 
 *    Rev 1.1   Feb 16 2000 16:17:56   YINGZ
 * fix date earlier than account active date problem
 * 
 *    Rev 1.0   Feb 15 2000 10:59:34   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.10   Nov 02 1999 11:17:10   DT24433
 * removed doOk/doCancel
 * 
 *    Rev 1.9   Oct 29 1999 11:30:16   BUZILA
 * changing WorkSessionDetails into a BFBase descendant
 * 
 *    Rev 1.8   Aug 26 1999 10:07:46   DT24433
 * changed getFieldFromCurrentListItem to getField
 * 
 *    Rev 1.7   Aug 19 1999 10:03:48   DT24433
 * finished removing FieldDetails array
 * 
 *    Rev 1.6   Aug 17 1999 18:15:24   DT24433
 * removed static FieldDetails array
 * 
 *    Rev 1.5   Aug 11 1999 16:07:56   VASILEAD
 * Refresh bug fixed
 * 
 *    Rev 1.4   Aug 06 1999 16:15:32   VASILEAD
 * Delete the cbo list in process destructor
 * 
 *    Rev 1.3   Aug 04 1999 20:55:18   VASILEAD
 * Add support for multiple currency
 * 
 *    Rev 1.2   Jul 20 1999 11:14:06   VASILEAD
 * New conditions update
 * 
 *    Rev 1.1   Jul 08 1999 10:02:04   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
