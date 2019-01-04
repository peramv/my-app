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
// ^FILE   : HistoricalInfoProcess.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : Jan 2003
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : HistoricalInfoProcess
//    This class does the cleanup of the singletons
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "ifastcbo\HistoricalInfoList.hpp"
#include "ifastcbo\MFAccount.hpp"
#include "HistoricalInfoProcess.hpp"
#include "HistoricalInfoProcessIncludes.hpp"
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_HISTORICAL_INFO;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_HISTORICAL_INFO;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< HistoricalInfoProcess > processCreator( CMD_BPROC_HISTORICAL_INFO );
#include "mfcaninterprocparam.hpp"

#include "iFastHistoricalParameters.hpp"

namespace
{
    // Trace literals
    const I_CHAR * const CLASSNAME = I_( "HistoricalInfoProcess" );
    const I_CHAR * const PERFORMSEARCH = I_( "performSearch" );
}

namespace CND
{
    extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
    extern CLASS_IMPORT const BFNumericFieldId AccountNum;
    extern CLASS_IMPORT const BFNumericFieldId ShrNum;
    extern CLASS_IMPORT const BFTextFieldId BrokerCode;
    extern CLASS_IMPORT const BFTextFieldId BranchCode;
    extern CLASS_IMPORT const BFTextFieldId SalesRepCode;
}

namespace AUDITTYPE
{
    extern CLASS_IMPORT I_CHAR * const ACCTCONTROL;
	extern CLASS_IMPORT I_CHAR * const ACTRDR;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
//CP20030319HistoricalInfoProcess::HistoricalInfoProcess() :
HistoricalInfoProcess::HistoricalInfoProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, m_rpChildGI( NULL )
, _pHistoricalInfoList(NULL)

{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //not updatable list
   addContainer(IFASTBP_PROC::HISTORICAL_INFO_LIST, true, BF::NullContainerId );

   addFieldDetails(ifds::FieldLabel, IFASTBP_PROC::HISTORICAL_INFO_LIST);
   addFieldDetails(ifds::PreviousDisp, IFASTBP_PROC::HISTORICAL_INFO_LIST);
   addFieldDetails(ifds::NewDisp, IFASTBP_PROC::HISTORICAL_INFO_LIST);
   addFieldDetails(ifds::ModDate, IFASTBP_PROC::HISTORICAL_INFO_LIST);
   addFieldDetails(ifds::ModTime, IFASTBP_PROC::HISTORICAL_INFO_LIST);
   addFieldDetails(ifds::ModUser, IFASTBP_PROC::HISTORICAL_INFO_LIST);
   addFieldDetails(ifds::WorkType, IFASTBP_PROC::HISTORICAL_INFO_LIST);
   addFieldDetails(ifds::AWDObjectId, IFASTBP_PROC::HISTORICAL_INFO_LIST);
   addFieldDetails(ifds::AccountNum, BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails(ifds::ShrNum, BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails(ifds::BrokerCode, BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails(ifds::BranchCode, BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails(ifds::SalesRepCode, BF::NullContainerId, SUBCLASS_PROCESS );

}

//******************************************************************************
HistoricalInfoProcess::~HistoricalInfoProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   if (_pHistoricalInfoList) 
   {
      delete _pHistoricalInfoList;
      _pHistoricalInfoList = NULL;
   }
   m_rpChildGI = NULL;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY HistoricalInfoProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   getParameter( MFCAN_IP_PARAM::ACCOUNT_NUM, m_dstrAccountNumber );           
   getParameter( MFCAN_IP_PARAM::SHR_NUM, m_dstrShareholderNumber);

   try
   {
      DString recId, tableId, keyStringIDI, dstrType;
      DString dstrBrokerCode, dstrBranchCode, dstrSalesRepCode;
      HISTORICAL_VECTOR *pHistoricalVector = NULL;
      DSTCWorkSession *dstcWorkSession = 
         dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

      getParameter(I_("BROKER"), m_dstrBrokerCode );
      getParameter(I_("BRANCH"), m_dstrBranchCode );
      getParameter(I_("SALESREP"), m_dstrSalesRepCode );
      getParameter(I_("TYPE"), dstrType );
      if( dstrType == I_("SINGLE") || dstrType == I_("MAIL") )
      {
         getParameter(MFCAN_IP_PARAM::RECID, recId);
         getParameter(MFCAN_IP_PARAM::TABLEID, tableId);
         getParameter(MFCAN_IP_PARAM::KEYS, keyStringIDI);
      }
      else if( dstrType == I_("MULTI") || dstrType == AUDITTYPE::ACTRDR)
      {
         getParameter(I_("HISTORICAL_VECTOR"), m_dstrHistoricalVectorPtr );
         pHistoricalVector = (HISTORICAL_VECTOR *) m_dstrHistoricalVectorPtr.asInteger();
      }

      _pHistoricalInfoList = new HistoricalInfoList(*dstcWorkSession);

      if( dstrType == I_("MULTI") )
      {
         sevRtn = _pHistoricalInfoList->init( pHistoricalVector );
      }
      else if( dstrType == I_("SINGLE") )
      {
         sevRtn = _pHistoricalInfoList->init( recId, tableId, keyStringIDI );
      }
      else if( dstrType == I_("SHRINFO") )
      {
         sevRtn = _pHistoricalInfoList->initShareholderInfo( m_dstrShareholderNumber );
      }
      else if( dstrType == I_("KYC") )
      {
         sevRtn = _pHistoricalInfoList->initKYC( dstrType, m_dstrShareholderNumber, m_dstrAccountNumber );
      }
      else if( dstrType == I_("MAIL") )
      {
         sevRtn = _pHistoricalInfoList->initMail( recId, tableId, keyStringIDI, m_dstrAccountNumber );
      }
      else if( dstrType == I_("ACCT") )
      {
         sevRtn = _pHistoricalInfoList->initAcct( m_dstrAccountNumber );
      }
      else if( dstrType == AUDITTYPE::ACCTCONTROL )
      {
         sevRtn = _pHistoricalInfoList->initAcctControl( m_dstrAccountNumber );
      }
	  else if( dstrType == AUDITTYPE::ACTRDR )
      {
         sevRtn = _pHistoricalInfoList->initAcctRoundingRule( pHistoricalVector, m_dstrAccountNumber );
      }
      if (sevRtn <= WARNING)
      {
         setContainer(IFASTBP_PROC::HISTORICAL_INFO_LIST, _pHistoricalInfoList);
      }
   }
   catch( ConditionException& ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT, 
         CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return sevRtn;
}

//******************************************************************************
E_COMMANDRETURN HistoricalInfoProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      rtn = invokeCommand( this, CMD_GUI_HISTORICAL_INFO, 
            getProcessType(), isModal(), &m_rpChildGI );
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
   return rtn;
}

//******************************************************************************
SEVERITY HistoricalInfoProcess::performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, 
   E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, PERFORMSEARCH );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      if( _pHistoricalInfoList != NULL )
      {
         sevRtn = _pHistoricalInfoList->getMore();
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, 
         PERFORMSEARCH, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(sevRtn); 
}

//******************************************************************************
bool HistoricalInfoProcess::doMoreRecordsExist( GenericInterface *rpGICaller,  const BFContainerId& idSearch )
{
   return( rpGICaller == NULL || _pHistoricalInfoList == NULL ) ? 
      false : _pHistoricalInfoList->doMoreHistoricalRecordsExist();
}

//******************************************************************************

void HistoricalInfoProcess::doGetField(
                                  const GenericInterface *rpGICaller,
                                  const BFContainerId& idContainer,
                                  const BFFieldId& idField,
                                  const BFDataGroupId& idDataGroup,
                                  DString &strValueOut,
                                  bool bFormatted ) const
{  
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   

   if( idField == ifds::AccountNum )
   {
      strValueOut = m_dstrAccountNumber;
   }
   else if( idField == ifds::ShrNum )
   {
      if( m_dstrShareholderNumber.empty() )
      {
         MFAccount *pMFAccount;
         if( !m_dstrAccountNumber.empty() )
         {
            if( dstcWorkSession->getMFAccount( idDataGroup, m_dstrAccountNumber, pMFAccount ) <= WARNING )
            {
               if( pMFAccount != NULL )
               {
                  pMFAccount->getField(ifds::ShrNum, strValueOut, BF::HOST);
               }
            }
         }
      }
      else
      {
         strValueOut = m_dstrShareholderNumber;
      }
   }
   else if( idField == ifds::BrokerCode )
   {
      strValueOut = m_dstrBrokerCode;
   }
   else if( idField == ifds::BranchCode )
   {
      strValueOut = m_dstrBranchCode;
   }
   else if( idField == ifds::SalesRepCode )
   {
      strValueOut = m_dstrSalesRepCode;
   }

}

//******************************************************************************

bool HistoricalInfoProcess::doModelessSetFocus(
                                                 GenericInterface *rpGICaller )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doModelessSetFocus") );
   SEVERITY sevRtn = SEVERE_ERROR;
   bool bRtn = false;
   try
   {
      assert( m_rpChildGI && isValidModelessInterface( m_rpChildGI ) );

      DString dstrNewAccountNumber;
      getParameter( MFCAN_IP_PARAM::ACCOUNT_NUM, dstrNewAccountNumber );

      if( dstrNewAccountNumber != m_dstrAccountNumber )
      {
         delete _pHistoricalInfoList;
         m_dstrAccountNumber = dstrNewAccountNumber.stripAll();
         _pHistoricalInfoList = new HistoricalInfoList( *getBFWorkSession() );
         sevRtn = _pHistoricalInfoList->initAcct( m_dstrAccountNumber );

         if( WARNING >= sevRtn )
         {
            setContainer(IFASTBP_PROC::HISTORICAL_INFO_LIST, _pHistoricalInfoList);
         }
         bRtn = m_rpChildGI->refresh( this, NULL_STRING );
      }
      else
      {
         if( !( bRtn = m_rpChildGI->refresh( this, NULL_STRING ) ) )
         {
            return(bRtn);  // false
         }
      }

      bRtn = m_rpChildGI->modelessSetFocus( rpGICaller );

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

   return( bRtn );
}

//******************************************************************************

bool HistoricalInfoProcess::doModelessChildComplete(const Command &cmd)
{
   return( cmd.getKey() == CMD_GUI_HISTORICAL_INFO );
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/HistoricalInfoProcess.cpp-arc  $
// 
//    Rev 1.17   Sep 15 2008 03:30:26   phiwponp
// IN 1394896    Inconsistence of Historical screen title under pending trade - clean code
// 
//    Rev 1.16   Sep 10 2008 05:53:20   phiwponp
// IN 1394896  - Inconsistence of Historical screen title under pending trade
// 
//    Rev 1.15   Apr 16 2008 18:30:12   daechach
// PET2385 FN02&07 - Modified code regarding code review.
// 
//    Rev 1.14   07 Nov 2007 00:18:08   popescu
// InternlAudit Project - 5563/01 added code for handling the AWD lookup button on the Historical Screen
// 
//    Rev 1.13   Aug 06 2007 16:22:22   kovacsro
// PET2372 FN02 FDP-AIM KYC
// 
//    Rev 1.12   Mar 16 2004 09:26:32   HERNANDO
// PET965 FN11 - Added parameter to initKYC call.
// 
//    Rev 1.11   Mar 08 2004 17:54:42   HERNANDO
// PET965 FN11 - Change doGetField to return m_dstrShareholderNumber if we have it.
// 
//    Rev 1.10   Mar 04 2004 11:00:38   HERNANDO
// PET965 FN11 - Added doModelessSetFocus and doModelessChildComplete.
// 
//    Rev 1.9   Feb 28 2004 16:00:44   HERNANDO
// PET965 FN11 - Additional historical enhancement.
// 
//    Rev 1.8   Oct 31 2003 16:06:08   HERNANDO
// PTS 10022670 - Support displaying Broker Code, Branch Code, and Sales Rep Code.
// 
//    Rev 1.7   Oct 10 2003 16:16:44   HERNANDO
// PTS 10022670 - Supporting Account Num and Shareholder Num for Title display from Historical through Account.
// 
//    Rev 1.6   Jun 30 2003 16:56:10   popescu
// added historical info search to the Broker Features search;
// moved some param names to the mfcaniterprocparam namespace
// 
//    Rev 1.5   Mar 21 2003 17:40:56   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.4   Feb 06 2003 12:03:00   popescu
// Checking in for Historical Info Search screen
// 
//    Rev 1.3   Feb 03 2003 11:53:24   popescu
// Changed to support the KeyString field of the 249 view
// 
//    Rev 1.2   Jan 29 2003 14:58:08   popescu
// FIxes related to view layout change and error reporting
// 
//    Rev 1.1   Jan 28 2003 16:56:30   popescu
// Fixes for the More button in the Historical Info dialog
// 
//    Rev 1.0   Jan 28 2003 13:13:44   popescu
// Initial revision.
 * 
 */

