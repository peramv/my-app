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
// ^FILE   : FreeUnitProcess.cpp
// ^AUTHOR : Chin Hsu
// ^DATE   : July 26, 1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : FreeUnitProcess
//    This class manages the Free Units Screen
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "freeunitprocess.hpp"
#include <ifastcbo\currencyclass.hpp>
#include <ifastcbo\freeunitlist.hpp>
#include <ifastcbo\MFAccountHoldingList.hpp>
#include "freeunitprocessincludes.h"
#include <ifastcbo\funddetaillist.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\mfaccount.hpp>
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_FREEUNIT;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FREEUNIT;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< FreeUnitProcess > processCreator( CMD_BPROC_FREEUNIT );

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "FreeUnitProcess" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace FREEUNITINFOLIT  
{
   const I_CHAR * const ACCOUNTNUM = I_( "AccountNum" );
   const I_CHAR * const ALLFUNDMODE = I_( "AllFundMode" );
   const I_CHAR * const FUNDCODE = I_( "FundCode" );
   const I_CHAR * const CLASSCODE = I_( "ClassCode" );
   const I_CHAR * const PRCNTHOLDING_LVL = I_( "PercentFreeHoldingLvl" );
}

namespace PERCENT_FREE_LVL
{
    const I_CHAR * const NOT_HOLDING            = I_("0");
    const I_CHAR * const ONLY_FUND_GROUP        = I_("1");
    const I_CHAR * const ONLY_FUND              = I_("2");
    const I_CHAR * const FUND_AND_FNDGRP        = I_("3");
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId Baycom;
   extern CLASS_IMPORT const BFTextFieldId PrcntFeeHolding;
   extern CLASS_IMPORT const BFTextFieldId PrcntFeeDipOpt;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319FreeUnitProcess::FreeUnitProcess() : 
FreeUnitProcess::FreeUnitProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pFreeUnitList( 0 )
, _pFreeAmountList (0)
,_rpChildGI( 0 )
, m_DSCFeeLevel( NULL_STRING )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::FREEUNIT_LIST, true );
   addContainer( IFASTBP_PROC::FREEUNIT_ACCT_LIST, true );
   addContainer( IFASTBP_PROC::MFACCOUNT_CBO, false, BF::NullContainerId, false );
   addContainer( IFASTBP_PROC::FREEAMOUNT_LIST, true, IFASTBP_PROC::FREEUNIT_LIST, true );
   addContainer( IFASTBP_PROC::FREEAMOUNT_ACCT_LIST, true, IFASTBP_PROC::FREEUNIT_ACCT_LIST, true );

   addFieldDetails( ifds::rxFundCode, IFASTBP_PROC::FREEUNIT_LIST );
   addFieldDetails( ifds::rxClassCode, IFASTBP_PROC::FREEUNIT_LIST );
   addFieldDetails( ifds::RecordType, IFASTBP_PROC::FREEUNIT_LIST );
   addFieldDetails( ifds::PShipCode, IFASTBP_PROC::FREEUNIT_LIST );
   addFieldDetails( ifds::FreeYear, IFASTBP_PROC::FREEUNIT_LIST );
   addFieldDetails( ifds::YearDesc, IFASTBP_PROC::FREEUNIT_LIST );
   addFieldDetails( ifds::EligibleAmt, IFASTBP_PROC::FREEUNIT_LIST );
   addFieldDetails( ifds::EligibleUnits, IFASTBP_PROC::FREEUNIT_LIST );
   addFieldDetails( ifds::UsedAmt, IFASTBP_PROC::FREEUNIT_LIST );
   addFieldDetails( ifds::UsedUnits, IFASTBP_PROC::FREEUNIT_LIST );
   addFieldDetails( ifds::LeftAmt, IFASTBP_PROC::FREEUNIT_LIST );
   addFieldDetails( ifds::LeftUnits, IFASTBP_PROC::FREEUNIT_LIST );
   addFieldDetails( ifds::Baycom, IFASTBP_PROC::FREEUNIT_LIST );
   addFieldDetails( ifds::AmountType, IFASTBP_PROC::FREEUNIT_LIST );
   addFieldDetails( ifds::CurrencyName, IFASTBP_PROC::FREEUNIT_LIST, SUBCLASS_PROCESS);

   addFieldDetails( ifds::rxFundCode, IFASTBP_PROC::FREEUNIT_ACCT_LIST );
   addFieldDetails( ifds::rxClassCode, IFASTBP_PROC::FREEUNIT_ACCT_LIST );
   addFieldDetails( ifds::RecordType, IFASTBP_PROC::FREEUNIT_ACCT_LIST );
   addFieldDetails( ifds::PShipCode, IFASTBP_PROC::FREEUNIT_ACCT_LIST );
   addFieldDetails( ifds::FreeYear, IFASTBP_PROC::FREEUNIT_ACCT_LIST );
   addFieldDetails( ifds::YearDesc, IFASTBP_PROC::FREEUNIT_ACCT_LIST );
   addFieldDetails( ifds::EligibleAmt, IFASTBP_PROC::FREEUNIT_ACCT_LIST );
   addFieldDetails( ifds::EligibleUnits, IFASTBP_PROC::FREEUNIT_ACCT_LIST );
   addFieldDetails( ifds::UsedAmt, IFASTBP_PROC::FREEUNIT_ACCT_LIST );
   addFieldDetails( ifds::UsedUnits, IFASTBP_PROC::FREEUNIT_ACCT_LIST );
   addFieldDetails( ifds::LeftAmt, IFASTBP_PROC::FREEUNIT_ACCT_LIST );
   addFieldDetails( ifds::LeftUnits, IFASTBP_PROC::FREEUNIT_ACCT_LIST );
   addFieldDetails( ifds::Baycom, IFASTBP_PROC::FREEUNIT_ACCT_LIST );
   addFieldDetails( ifds::AmountType, IFASTBP_PROC::FREEUNIT_ACCT_LIST );
   addFieldDetails( ifds::CurrencyName, IFASTBP_PROC::FREEUNIT_ACCT_LIST, SUBCLASS_PROCESS);
   addFieldDetails( ifds::rxFundGroup, IFASTBP_PROC::FREEUNIT_ACCT_LIST );
   
   addFieldDetails( LIST_FILTER, BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails( DSC_FEE_LEVEL, BF::NullContainerId, SUBCLASS_PROCESS );
   addSubstituteList( ifds::FreeUnitHeadingSet );

   addFieldDetails( ifds::ShrNum, IFASTBP_PROC::MFACCOUNT_CBO );   
   addFieldDetails( ifds::DSCFeeLevel, IFASTBP_PROC::MFACCOUNT_CBO );   

   addFieldDetails( ifds::RecordType, IFASTBP_PROC::FREEAMOUNT_LIST );
   addFieldDetails( ifds::EligibleAmt, IFASTBP_PROC::FREEAMOUNT_LIST );
   addFieldDetails( ifds::EligibleUnits, IFASTBP_PROC::FREEAMOUNT_LIST );
   addFieldDetails( ifds::UsedAmt, IFASTBP_PROC::FREEAMOUNT_LIST );
   addFieldDetails( ifds::UsedUnits, IFASTBP_PROC::FREEAMOUNT_LIST );
   addFieldDetails( ifds::LeftAmt, IFASTBP_PROC::FREEAMOUNT_LIST );
   addFieldDetails( ifds::LeftUnits, IFASTBP_PROC::FREEAMOUNT_LIST );

   addFieldDetails( ifds::RecordType, IFASTBP_PROC::FREEAMOUNT_ACCT_LIST );
   addFieldDetails( ifds::EligibleAmt, IFASTBP_PROC::FREEAMOUNT_ACCT_LIST );
   addFieldDetails( ifds::EligibleUnits, IFASTBP_PROC::FREEAMOUNT_ACCT_LIST );
   addFieldDetails( ifds::UsedAmt, IFASTBP_PROC::FREEAMOUNT_ACCT_LIST );
   addFieldDetails( ifds::UsedUnits, IFASTBP_PROC::FREEAMOUNT_ACCT_LIST );
   addFieldDetails( ifds::LeftAmt, IFASTBP_PROC::FREEAMOUNT_ACCT_LIST );
   addFieldDetails( ifds::LeftUnits, IFASTBP_PROC::FREEAMOUNT_ACCT_LIST );
   addFieldDetails( ifds::rxFundGroup, IFASTBP_PROC::FREEAMOUNT_ACCT_LIST );

   addSubstituteList( ifds::FreeAmountHeadingSet );

}

//******************************************************************************

FreeUnitProcess::~FreeUnitProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   delete _pFreeUnitList;
   if ( _pFreeAmountList )
		delete _pFreeAmountList;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY FreeUnitProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      // Get Account
      DString strAccountNumber;
      getParameter( FREEUNITINFOLIT::ACCOUNTNUM, strAccountNumber );
      AccountNumber = strAccountNumber;
      sevRtn = dstcWorkSession->getMFAccount( getDataGroupId(), AccountNumber, _pMFAccount );
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::MFACCOUNT_CBO, _pMFAccount );
      }
      _pMFAccount->getField( ifds::DSCFeeLevel, m_DSCFeeLevel, getDataGroupId(), false );

      // Get Fund Detail List
      sevRtn = dstcWorkSession->getMgmtCo().getFundDetailList( _pFundDetailList );
      _pFreeUnitList = new FreeUnitList( *dstcWorkSession );

      dstcWorkSession->getOption(ifds::PrcntFeeDipOpt, _dstrPrcntFeeDipOpt, BF::HOST, false);
      _dstrPrcntFeeDipOpt.stripAll();

      MFAccountHoldingList *pAcctHoldingList = NULL;
      MFAccount *pMFAccount = dynamic_cast<MFAccount*>(const_cast<FreeUnitProcess*>(this)->getCBOItem(IFASTBP_PROC::MFACCOUNT_CBO, getDataGroupId()));
        
      if (pMFAccount &&
          pMFAccount->getAccountHoldingList(pAcctHoldingList, getDataGroupId()) <= WARNING && pAcctHoldingList)
      {
          pAcctHoldingList->getField(ifds::PrcntFeeHolding, _prcntFeeHolding, getDataGroupId());
          _prcntFeeHolding.stripAll();
      }

      if ( (_dstrPrcntFeeDipOpt == I_("0") && (m_DSCFeeLevel == I_("0") || m_DSCFeeLevel == I_("2") || m_DSCFeeLevel == I_("3")) ) ||
           (_dstrPrcntFeeDipOpt == I_("1") && (_prcntFeeHolding == PERCENT_FREE_LVL::ONLY_FUND || _prcntFeeHolding == PERCENT_FREE_LVL::FUND_AND_FNDGRP)))
      {
          sevRtn = _pFreeUnitList->init( strAccountNumber, I_("N"), I_("Y") ); // AcctNum, AcctLvlDSCFund, AllFund
      }
      
      if( WARNING >= sevRtn )
      {
          setContainer( IFASTBP_PROC::FREEUNIT_LIST, _pFreeUnitList );
      }

      // 
      _FundCode = NULL_STRING;
      _ClassCode = NULL_STRING;
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

E_COMMANDRETURN FreeUnitProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter(FREEUNITINFOLIT::ACCOUNTNUM, AccountNumber);
      setParameter(FREEUNITINFOLIT::PRCNTHOLDING_LVL, _prcntFeeHolding);

      rtn = invokeCommand( this, CMD_GUI_FREEUNIT, getProcessType(),
                           isModal(), &_rpChildGI );
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

bool FreeUnitProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_FREEUNIT );
}

//******************************************************************************

bool FreeUnitProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );

   SEVERITY severity = SEVERE_ERROR;
   bool bRtn = false;
   try
   {
      assert( _rpChildGI && isValidModelessInterface( _rpChildGI ) );

      DString strNewAccountNumber;
      getParameter( FREEUNITINFOLIT::ACCOUNTNUM, strNewAccountNumber );
      setParameter( FREEUNITINFOLIT::ACCOUNTNUM, strNewAccountNumber );
      if( strNewAccountNumber != AccountNumber )
      {
         delete _pFreeUnitList;
         AccountNumber = strNewAccountNumber;
         _pFreeUnitList = new FreeUnitList( *getBFWorkSession() );
         severity = _pFreeUnitList->init( strNewAccountNumber );
         if( WARNING >= severity )
         {
            //register list with base
            setContainer( IFASTBP_PROC::FREEUNIT_LIST, _pFreeUnitList );
         }

         if( !( bRtn = _rpChildGI->refresh( this, I_( "FullRefresh" ) ) ) )
            return(bRtn);// false
      }
      else
      {
         if( !( bRtn = _rpChildGI->refresh( this, I_( "PartialRefresh" ) ) ) )
            return(bRtn);// false
      }

      bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
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

SEVERITY FreeUnitProcess::performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, 
                                         E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "doMore" ));

   DString NextKey;
   SEVERITY severity = SEVERE_ERROR;

   try
   {
      if( _pFreeUnitList != NULL && rpGI != NULL )
      {
         severity = _pFreeUnitList->search(eSearchAction == SEARCH_START);
         if( WARNING >= severity )
         {
            //register list with base
            setContainer( IFASTBP_PROC::FREEUNIT_LIST, _pFreeUnitList );
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
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

bool FreeUnitProcess::doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch )
{
   return(rpGICaller == NULL || _pFreeUnitList == NULL ? false : 
          _pFreeUnitList->doMoreRecordsExist());
}

//******************************************************************************

const DString& FreeUnitProcess::getFirstListItemKey(
                                                   const GenericInterface *rpGICaller,
                                                   const BFContainerId& idList
                                                   )
{
   if( idList == IFASTBP_PROC::FREEUNIT_LIST )
   {
      const DString *key=&AbstractProcess::getFirstListItemKey(rpGICaller,idList);
      DString dstrUpperKey( *key ), dstrUpperListViewFilter( ListViewFilter );
      dstrUpperKey.upperCase();
      dstrUpperListViewFilter.upperCase();
      if( !dstrUpperKey.empty() && dstrUpperKey.find(dstrUpperListViewFilter)==-1 && ( (dstrUpperListViewFilter.compare( I_("TOTAL") ) == 0) || 
                                                                                       (dstrUpperKey.find(I_("MAT"))==-1 && dstrUpperKey.find( I_("ID") )==-1) ) )
      {
         key=&getNextListItemKey(rpGICaller,idList);
      }

      return(*key);
   }
   else
   {
      return(AbstractProcess::getFirstListItemKey(rpGICaller,idList));
   }
}

//******************************************************************************

const DString& FreeUnitProcess::getNextListItemKey(
                                                  const GenericInterface *rpGICaller,
                                                  const BFContainerId& idList
                                                  )
{  
   TRACE_METHOD( CLASSNAME, GETNEXTLISTITEMKEY );

   if( idList == IFASTBP_PROC::FREEUNIT_LIST )
   {
      const DString *key;
      DString dstrUpperKey, dstrUpperListViewFilter( ListViewFilter );
      dstrUpperListViewFilter.upperCase();
      do
      {
         key=&AbstractProcess::getNextListItemKey(rpGICaller,idList);
         dstrUpperKey = *key;
         dstrUpperKey.upperCase();
      }
      while( !dstrUpperKey.empty() && dstrUpperKey.find(dstrUpperListViewFilter)==-1 && ( ( dstrUpperListViewFilter.compare( I_("TOTAL") ) == 0) ||
                                                                                          (dstrUpperKey.find(I_("MAT"))==-1 && dstrUpperKey.find(I_("ID"))==-1) ) );

      return(*key);
   }
   else
   {
      return(AbstractProcess::getNextListItemKey(rpGICaller,idList));
   }
}

//******************************************************************************

SEVERITY FreeUnitProcess::doSetField(
                                    const GenericInterface *rpGICaller,
                                    const BFContainerId& idContainer,
                                    const BFFieldId& idField,
                                    const BFDataGroupId& idDataGroup,
                                    const DString& strValue,
                                    bool bFormatted
                                    )
{  
   if( BF::NullContainerId == idContainer && idField == LIST_FILTER )
   {
      ListViewFilter=strValue;
   }

   return(NO_CONDITION);
}

//******************************************************************************
void FreeUnitProcess::doGetField(
                                const GenericInterface *rpGICaller,
                                const BFContainerId &idContainer,
                                const BFFieldId &idField,
                                const BFDataGroupId &idDataGroup,
                                DString &strValueOut, 
                                bool bFormatted
                                ) const
{   
    strValueOut = NULL_STRING;

    if (idField == ifds::CurrencyName)
    {
        if (idContainer == IFASTBP_PROC::FREEUNIT_ACCT_LIST || idContainer == IFASTBP_PROC::FREEUNIT_LIST)
        {
            DString fundCode, classCode;

            const_cast <FreeUnitProcess*> (this)->getField (rpGICaller, 
                idContainer, ifds::rxFundCode, fundCode, false);
            const_cast <FreeUnitProcess*> (this)->getField (rpGICaller, 
                idContainer, ifds::rxClassCode, classCode, false);
            if (fundCode.stripAll() != NULL_STRING && classCode.stripAll() != NULL_STRING)
            {
                _pFundDetailList->getField (fundCode, classCode, ifds::CurrencyName, 
                    strValueOut, idDataGroup, true);
            }
        }
    }
}
//*****************************************************************************
bool FreeUnitProcess::doRefresh(
                               GenericInterface *rpGICaller,
                               const I_CHAR *szOriginalCommand
                               )
{
   setParameter( FREEUNITINFOLIT::ACCOUNTNUM, AccountNumber );
   return(_rpChildGI->refresh( this, NULL ));
}

//******************************************************************************
void*  FreeUnitProcess::getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
   void *ptr = NULL;

   try
   {
      if( IFASTBP_PROC::FREEAMOUNT_LIST == idContainer && _pFreeUnitList )
      {
         int noOfEntities = getNumberOfItemsInList( this, IFASTBP_PROC::FREEUNIT_LIST );
		 if( noOfEntities >= 1 )
		 {
		    DString dstrFundCode, dstrClassCode;

			DString crtKey = getCurrentListItemKey( this, IFASTBP_PROC::FREEUNIT_LIST );
            
			if ( NULL_STRING != crtKey )
			{
				getField(this, IFASTBP_PROC::FREEUNIT_LIST, ifds::rxFundCode, dstrFundCode, false);
				getField(this, IFASTBP_PROC::FREEUNIT_LIST, ifds::rxClassCode, dstrClassCode, false);
			}

			if ( _FundCode != dstrFundCode || _ClassCode != dstrClassCode )
			{
				_FundCode = dstrFundCode;
				_ClassCode = dstrClassCode;
				DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

				if ( _pFreeAmountList )
					delete _pFreeAmountList;
				_pFreeAmountList = new FreeUnitList( *dstcWorkSession );


				_pFreeAmountList->init2( AccountNumber, dstrFundCode, dstrClassCode );
			}
            if( dstrFundCode.empty() && dstrClassCode.empty() )
            {
               if( _pFreeAmountList )
                  delete _pFreeAmountList;
		  	 	DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
               _pFreeAmountList = new FreeUnitList( *dstcWorkSession );
               _pFreeAmountList->init( AccountNumber, I_("N"), I_("Y") ); // AcctNum, AcctLvlDSCFund, AllFund
            }

            if( _pFreeAmountList )
			{
				ptr = _pFreeAmountList;
			}
		 }
	  }
      else if (idContainer == IFASTBP_PROC::FREEUNIT_ACCT_LIST)
      {
          FreeUnitList *pFreeUnitListAccount = NULL;
          MFAccount *pMFAccount = dynamic_cast<MFAccount*>(getCBOItem(IFASTBP_PROC::MFACCOUNT_CBO, getDataGroupId()));
          DString allFunds = _dstrPrcntFeeDipOpt == I_("0") ? I_("Y"):I_("N"),
                  allFundGroups = _dstrPrcntFeeDipOpt == I_("0") ? I_("N"):I_("Y");

          if (pMFAccount && 
              pMFAccount->getFreeUnitList(pFreeUnitListAccount, getDataGroupId(), I_("Y"), allFunds, allFundGroups) <= WARNING &&
              pFreeUnitListAccount)
          {
              ptr = pFreeUnitListAccount;
          }
      }
      else if (idContainer == IFASTBP_PROC::FREEAMOUNT_ACCT_LIST)
      {
          if (getCurrentListItemKey(this, IFASTBP_PROC::FREEUNIT_ACCT_LIST) == NULL_STRING)
              return NULL;

          BFAbstractCBO *pCBO = getCBOItem(IFASTBP_PROC::FREEUNIT_ACCT_LIST, getDataGroupId());

          if (pCBO)
          {
              DString dstrFundGroup, dstrFund, dstrClass;
              FreeUnitList *pFreeAmountListAccount = NULL;
              MFAccount *pMFAccount = dynamic_cast<MFAccount*>(getCBOItem(IFASTBP_PROC::MFACCOUNT_CBO, getDataGroupId()));

              pCBO->getField(ifds::rxFundCode, dstrFund, getDataGroupId());
              pCBO->getField(ifds::rxClassCode, dstrClass, getDataGroupId());
              pCBO->getField(ifds::rxFundGroup, dstrFundGroup, getDataGroupId());

              if (pMFAccount)
              {
                  if (_dstrPrcntFeeDipOpt == I_("1") &&
                      pMFAccount->getFreeUnitListBy(pFreeAmountListAccount, getDataGroupId(), NULL_STRING, NULL_STRING, dstrFundGroup) <= WARNING && pFreeAmountListAccount)
                  {
                      ptr = pFreeAmountListAccount;
                  }
                  else if (_dstrPrcntFeeDipOpt == I_("0") &&
                          pMFAccount->getFreeUnitList(pFreeAmountListAccount, getDataGroupId(), I_("Y"), I_("Y"), I_("N")) <= WARNING &&
                          pFreeAmountListAccount)
                  {
                      ptr = pFreeAmountListAccount;
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
   return(ptr);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/FreeUnitProcess.cpp-arc  $
 * 
 *    Rev 1.22   Oct 05 2005 12:42:32   porteanm
 * Incident 421401 - Extra check for the case when 0 Total records are returned without any Detail record.
 * 
 *    Rev 1.21   May 02 2005 08:37:58   hernando
 * PET1024 FN10 - Acct Level/Fund Level DSC Enhancement.
 * 
 *    Rev 1.20   Jan 21 2004 17:42:28   AGUILAAM
 * PTS 10025931 - incorrect  currency is displayed. Modified code to get currency from funddetaillist based on active/current fund/class
 * 
 *    Rev 1.19   Nov 05 2003 16:20:22   linmay
 * P843_FN251
 * 
 *    Rev 1.18   Mar 21 2003 17:40:04   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.17   Mar 07 2003 14:50:32   PURDYECH
 * Corrected some idContainers
 * 
 *    Rev 1.16   Oct 09 2002 23:53:14   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.15   Sep 30 2002 11:01:02   PURDYECH
 * BFFieldId no longer has operator long(), so explicit getId() calls are needed in places.
 * 
 *    Rev 1.14   Aug 29 2002 16:44:54   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.13   Aug 29 2002 12:54:20   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.12   22 May 2002 22:23:00   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.11   18 Apr 2002 13:24:46   HERNANDO
 * Bug fix for rev. 1.10
 * 
 *    Rev 1.10   17 Apr 2002 18:19:50   HERNANDO
 * Added support for Unit Types 'Mature' and 'ID'.
 * 
 *    Rev 1.9   27 Mar 2002 19:54:52   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.8   Jun 07 2001 10:49:44   YINGBAOL
 * fix refresh
 * 
 *    Rev 1.7   15 May 2001 15:38:42   YINGZ
 * data group id clean up
 * 
 *    Rev 1.6   03 May 2001 14:05:24   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.5   15 Dec 2000 12:43:28   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.4   Nov 03 2000 11:31:40   YINGBAOL
 * BFBase change sync.
 * 
 *    Rev 1.3   Aug 02 2000 15:32:00   BUZILA
 * "locale" changes
 * 
 *    Rev 1.2   Jul 26 2000 11:09:20   ZHANGCEL
 * deal with the fund code problem
 * 
 *    Rev 1.1   May 10 2000 10:07:06   YINGZ
 * check in
 * 
 *    Rev 1.0   Feb 15 2000 10:59:34   SMITHDAV
 * Initial revision.
// 
//    Rev 1.8   Dec 08 1999 16:27:56   HSUCHIN
// changed doGetField and doSetField to include groupid
// 
//    Rev 1.7   Oct 29 1999 09:57:04   DT24433
// removed doOk/doCancel
// 
//    Rev 1.6   26 Sep 1999 13:01:44   HICKSBR
// Add #include "srcprag.h"
// 
//    Rev 1.5   Sep 24 1999 17:01:32   HSUCHIN
// final version for C1A.  Many fixes
// 
//    Rev 1.4   Sep 21 1999 17:53:54   HSUCHIN
// bug fixes
// 
//    Rev 1.3   Sep 20 1999 17:37:16   HSUCHIN
// Free Unit added
// 
//    Rev 1.2   Aug 26 1999 10:30:48   DT24433
// added ending comment line
// 
//    Rev 1.1   Aug 26 1999 10:03:12   DT24433
// removed static fielddetails array
// 
*/
