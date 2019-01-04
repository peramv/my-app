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
// ^FILE   : AcctCategoryProcess.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 01/23/2003
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : AcctCategoryProcess
//    This class manages the Account Category information.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************
//ifastbp
#include "stdafx.h"
#include "acctcategoryprocessincludes.h"
#include "acctcategoryprocess.hpp"
#include <ifastdataimpl\dse_dstcglob_vw.hpp>
#include "mfcaninterprocparam.hpp"
#include <ifastcbo\acctcategory.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\acctcategorylist.hpp>
#include <ifastcbo\acctcategory.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_ACCT_CATEGORY;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACCT_CATEGORY;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< AcctCategoryProcess > processCreator( CMD_BPROC_ACCT_CATEGORY );

namespace
{
   // Trace literals
   extern I_CHAR *CLASSNAME = I_( "AcctCategoryProcess" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace ACCTCATEGORYLIST
{
   const I_CHAR * const ACCOUNT_NUM = I_( "AccountNum" );

}

//fund on fund
namespace ACCOUNT_CATEGORY
{
   extern CLASS_IMPORT I_CHAR * const FUND_ON_FUND;
}

namespace AUDITTYPE
{
   extern CLASS_IMPORT I_CHAR * const ACT_CATEGORY;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
AcctCategoryProcess::AcctCategoryProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL )
, m_strAcctNum(NULL_STRING)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::MFACCOUNT,     false, BF::NullContainerId,     false, I_("MFAccount") );
   addContainer( IFASTBP_PROC::CATEGORY_LIST, true,  IFASTBP_PROC::MFACCOUNT, true,  I_("CategoryList") );

   addFieldDetails( ifds::AcctCategory,      IFASTBP_PROC::CATEGORY_LIST );
   addFieldDetails( ifds::PaymentIdMethod,   IFASTBP_PROC::CATEGORY_LIST );
   addFieldDetails( ifds::ProcessDate,       IFASTBP_PROC::CATEGORY_LIST );
   addFieldDetails( ifds::Username,          IFASTBP_PROC::CATEGORY_LIST );
   addFieldDetails( ifds::ModUser,           IFASTBP_PROC::CATEGORY_LIST );
   addFieldDetails( ifds::ModDate,           IFASTBP_PROC::CATEGORY_LIST );

   addFieldDetails( ifds::AccountNum,        IFASTBP_PROC::MFACCOUNT );
   addFieldDetails( ifds::CatValue,          IFASTBP_PROC::CATEGORY_LIST ); //fund on fund
   addFieldDetails( ifds::AcctCatRId,        IFASTBP_PROC::CATEGORY_LIST );
}

//******************************************************************************
AcctCategoryProcess::~AcctCategoryProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

}

//******************************************************************************
//              Protected Methods
//******************************************************************************

//******************************************************************************
SEVERITY AcctCategoryProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

   getParameter( ACCTCATEGORYLIST::ACCOUNT_NUM, m_strAcctNum );

   SEVERITY sevRtn=NO_CONDITION;
   MFAccount * pMFAccount = NULL;
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   if( dstcWorkSession->getMFAccount( getDataGroupId(), m_strAcctNum, pMFAccount, I_("N"), NULL_STRING, true, true) 
       <= WARNING && pMFAccount )
   {
      setContainer( IFASTBP_PROC::MFACCOUNT, pMFAccount );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool AcctCategoryProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_ACCT_CATEGORY);
}

//******************************************************************************
bool AcctCategoryProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
   DString  strAcctNum;
   bool bRtn = false;

   try
   {
      getParameter( ACCTCATEGORYLIST::ACCOUNT_NUM, strAcctNum );
      if( strAcctNum != m_strAcctNum )
      {
         m_strAcctNum = strAcctNum;
         setContainer( IFASTBP_PROC::MFACCOUNT, NULL );

         if( isValidModelessInterface( _rpChildGI ) )
         {  // Only if child still exists
            bRtn = _rpChildGI->refresh( this, NULL );
         }
      }

      if( isValidModelessInterface( _rpChildGI ) )
      {  // Only if child still exists
         bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
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

   return(bRtn);
}

//******************************************************************************
E_COMMANDRETURN AcctCategoryProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   setParameter (ACCTCATEGORYLIST::ACCOUNT_NUM, m_strAcctNum);

   try
   {
      rtn = invokeCommand( this, CMD_GUI_ACCT_CATEGORY, getProcessType(), isModal(),
                           &_rpChildGI );
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
bool AcctCategoryProcess::doOk( GenericInterface *rpGICaller )
{
   SEVERITY sevReturn = NO_CONDITION;
   MFAccount *pMFAccount = NULL;
   DString strAcctCategFlag = I_( "N" );
   const BFDataGroupId& idDataGroup = getDataGroupId();
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   if( dstcWorkSession->getMFAccount( idDataGroup, m_strAcctNum, pMFAccount ) <= WARNING )
   {
      AcctCategoryList *pAcctCategoryList = NULL;
      if( pMFAccount->getAcctCategoryList( pAcctCategoryList, idDataGroup ) <= WARNING )
      {
         if ( pAcctCategoryList && pAcctCategoryList->isUpdatedForDataGroup( getDataGroupId() ) )
            pMFAccount->refreshMe ( true );
         else
         {
            sevReturn = pAcctCategoryList->doValidateAll( idDataGroup, 0 );
         }
      }
   }
   return( sevReturn == NO_CONDITION );
}

//******************************************************************************
void *AcctCategoryProcess::getPtrForContainer( const BFContainerId& idContainer,
                                               const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "getPtrForContainer" ) );
   void *ptr = NULL;
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   try
   {
      if( IFASTBP_PROC::MFACCOUNT == idContainer )
      {
         {
            MFAccount *pMFAccount = NULL;
            if( dstcWorkSession->getMFAccount( getDataGroupId(), m_strAcctNum, pMFAccount ) 
                <= WARNING && pMFAccount )
               ptr = pMFAccount;
         }
      }
      else if( IFASTBP_PROC::CATEGORY_LIST == idContainer )
      {
         {
            MFAccount *pMFAccount = NULL;
            AcctCategoryList *pAcctCategList = NULL;
            if( dstcWorkSession->getMFAccount( getDataGroupId(), m_strAcctNum, pMFAccount ) 
                <= WARNING && pMFAccount )
            {
               if( pMFAccount->getAcctCategoryList( pAcctCategList, idDataGroup ) <=
                   WARNING && pAcctCategList )
               {
                  ptr = pAcctCategList;
               }
            }
         }
      }
      else
      {
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
SEVERITY AcctCategoryProcess::deleteItemFromList( const GenericInterface *rpGICaller,
                                                  const BFContainerId& idList )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("deleteItemFromList") );
   //actually this logic should be in AbstractProcess::deleteItemFromList and 
   //validateUserDelete should be in BFAbstractCBO - RK - Jan. 25, 2003
   if( IFASTBP_PROC::CATEGORY_LIST == idList )
   {
      {
         AcctCategory * pAcctCategory = dynamic_cast < AcctCategory *> 
                                        (getCBOItem( IFASTBP_PROC::CATEGORY_LIST, getDataGroupId() ));
         if( pAcctCategory )
         {
            if( pAcctCategory->validateUserDelete(getDataGroupId()) > WARNING )
               return(GETCURRENTHIGHESTSEVERITY());
         }
      }
   }
   AbstractProcess::deleteItemFromList(rpGICaller, idList);
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AcctCategoryProcess::getHistoricalParameters ( const BFContainerId &idContainer, 
                                                        BFFieldId &recordIdField, 
                                                        DString &tableId, 
                                                        DString &dstrKeys) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           GETHISTORICALPARAMETERS);

   DString dstrAccountNum,
      keyStringIDI; 

   getField(this,IFASTBP_PROC::MFACCOUNT,ifds::AccountNum,dstrAccountNum,false);
   dstrAccountNum.strip().upperCase();

   if (idContainer == IFASTBP_PROC::CATEGORY_LIST)
   {
      recordIdField = ifds::AcctCatRId;
      tableId = AUDITTYPE::ACT_CATEGORY;
      addIDITagValue(keyStringIDI, MFCAN_IP_PARAM::ACCOUNT_NUM, dstrAccountNum);
      dstrKeys = keyStringIDI;
   }
   else 
   {
      assert(0);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AcctCategoryProcess::getHistoricalParameters ( const BFContainerId& idContainer,
                                                        HISTORICAL_VECTOR &vectorInput )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           GETHISTORICALPARAMETERS);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AcctCategoryProcess.cpp-arc  $
// 
//    Rev 1.10   Dec 01 2010 04:21:02   dchatcha
// P0175716 FN02 - Client Name Redemption - EPA Auto Settlement.
// 
//    Rev 1.9   Oct 28 2008 03:12:46   phiwponp
// PET22486FN45 - Fund on Funds Account Report.
// 
//    Rev 1.8   Aug 09 2007 14:00:02   jankovii
// PET 2388 FN01 - Swift Payment Method ID.
// 
//    Rev 1.7   Sep 15 2004 15:54:30   HERNANDO
// PET1117 FN02 - In doOk, call doValidateAll in AcctCategoryList.
// 
//    Rev 1.6   Mar 03 2004 16:21:08   popescu
// PTS 10027578, refresh the account information after updating the mailing address info and demographics info; changed the name of the refreshMe method, to be consistent with the shareholder object
// 
//    Rev 1.5   Dec 08 2003 15:40:26   HSUCHIN
// PTS 10024902 - bug fix with mfaccount refresh to show updated cautions list.
// 
//    Rev 1.4   Apr 02 2003 12:19:24   PURDYECH
// Code cleanup
// 
//    Rev 1.3   Mar 21 2003 17:34:58   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.2   Jan 26 2003 16:04:40   KOVACSRO
// OOPS ... a bug
// 
//    Rev 1.1   Jan 25 2003 16:59:36   KOVACSRO
// Added deleteItemFromList
// 
//    Rev 1.0   Jan 23 2003 17:02:00   KOVACSRO
// Initial revision.

 */