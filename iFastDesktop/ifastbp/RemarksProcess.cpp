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
// ^FILE   : RemarksProcess.cpp
// ^AUTHOR : 
// ^DATE   : 03/09/1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : RemarksProcess
//    This class manages the remarks information.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "remarksprocess.hpp"
#include <ifastdataimpl\dse_dstcglob_vw.hpp>
#include <ifastcbo\mfaccount.hpp>
#include "mfcaninterprocparam.hpp"
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\mgmtcooptions.hpp>
#include <ifastcbo\remarkslist.hpp>
#include <ifastcbo\remarks.hpp>
#include "remarksprocessincludes.h"
#include <ifastcbo\shareholder.hpp>
#include <ifastcbo\MFAccountList.hpp>
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_REMARKS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_REMARKS;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< RemarksProcess > processCreator( CMD_BPROC_REMARKS );

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "RemarksProcess" );
   const I_CHAR * const PERFORMSEARCH = I_( "performSearch" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace REMARKSLIT
{
   const I_CHAR * const ACCOUNT_NUM = I_( "AccountNum" );
   const I_CHAR * const NAME = I_( "Name" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId MoreThanOneAccount;
   extern CLASS_IMPORT const BFTextFieldId RemarkFilterBy;
}
//******************************************************************************
//              Public Methods
//******************************************************************************
//CP20030319RemarksProcess::RemarksProcess() : 
RemarksProcess::RemarksProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL ), _pRemarksList(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::REMARKS_LIST,   true,  BF::NullContainerId, true, I_("Remarks") );

   addFieldDetails( ifds::TransNote, IFASTBP_PROC::REMARKS_LIST );
   addFieldDetails( ifds::Remark1, IFASTBP_PROC::REMARKS_LIST );
   addFieldDetails( ifds::Remark2, IFASTBP_PROC::REMARKS_LIST );
   addFieldDetails( ifds::Remark3, IFASTBP_PROC::REMARKS_LIST );
   addFieldDetails( ifds::Remark4, IFASTBP_PROC::REMARKS_LIST );
   addFieldDetails( ifds::Remark5, IFASTBP_PROC::REMARKS_LIST );
   addFieldDetails( ifds::Remark6, IFASTBP_PROC::REMARKS_LIST );
   addFieldDetails( ifds::Remark7, IFASTBP_PROC::REMARKS_LIST );
   addFieldDetails( ifds::Remark8, IFASTBP_PROC::REMARKS_LIST );
   addFieldDetails( ifds::Remark9, IFASTBP_PROC::REMARKS_LIST );
   addFieldDetails( ifds::Remark10, IFASTBP_PROC::REMARKS_LIST );
   addFieldDetails( ifds::Active, IFASTBP_PROC::REMARKS_LIST );
   addFieldDetails( ifds::EffectiveDate, IFASTBP_PROC::REMARKS_LIST );
   addFieldDetails( ifds::ProcessDate, IFASTBP_PROC::REMARKS_LIST );
   addFieldDetails( ifds::Username, IFASTBP_PROC::REMARKS_LIST );
   addFieldDetails( ifds::ModDate, IFASTBP_PROC::REMARKS_LIST );
   addFieldDetails( ifds::ModUser, IFASTBP_PROC::REMARKS_LIST );
   addFieldDetails( ifds::RemarkType, IFASTBP_PROC::REMARKS_LIST );
   addFieldDetails( ifds::RemarkAlert, IFASTBP_PROC::REMARKS_LIST );
   addFieldDetails( ifds::AccountNum, IFASTBP_PROC::REMARKS_LIST );

   addFieldDetails( ifds::AccountNum, BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails( ifds::RemarkFilterBy, BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails( ifds::ShrNum,     BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails( ifds::CurrBusDate, BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails( ifds::MoreThanOneAccount, BF::NullContainerId, SUBCLASS_PROCESS);
}

//******************************************************************************
RemarksProcess::~RemarksProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   _rpChildGI = NULL;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************
void RemarksProcess::doGetField(
                               const GenericInterface *rpGICaller,
                               const BFContainerId& idContainer,
                               const BFFieldId& idField,
                               const BFDataGroupId& idDataGroup,
                               DString &strValueOut,
                               bool bFormatted
                               ) const
{
   if( idField == ifds::CurrBusDate )
   {
      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      dstcWorkSession->getMgmtCoOptions()->getField(idField, strValueOut, getDataGroupId(), bFormatted );
   }
   else if( idField == ifds::AccountNum )
   {
      strValueOut = _strAccountNumber;

   }
   else if( idField == ifds::ShrNum )
   {
      strValueOut = _strShrNum;
   }
   else if ( ifds::MoreThanOneAccount == idField)
   {
     strValueOut = getNumberOfAccountsInRemarksList() ? I_("Y") : I_("N");
   }

   if (idContainer == BF::NullContainerId)
   {
       if (idField == ifds::RemarkFilterBy)
       {
           strValueOut = m_filterBy;
       }
   }
}

//******************************************************************************
SEVERITY RemarksProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

   getParameter( REMARKSLIT::ACCOUNT_NUM, _strAccountNumber );
   getParameter( REMARKSLIT::NAME, _strName);

   SEVERITY sevRtn=NO_CONDITION;
   MFAccount* mfAccount;
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   if( dstcWorkSession->getMFAccount( getDataGroupId(), _strAccountNumber, mfAccount ) <= WARNING )
   {
      mfAccount->getField( ifds::ShrNum, _strShrNum, getDataGroupId());

      if( sevRtn <= WARNING )
      {
         Shareholder *pShareholder = NULL;
         sevRtn = dstcWorkSession->getShareholder( getDataGroupId(), _strShrNum, pShareholder ) ;

         if( sevRtn <= WARNING && pShareholder != NULL )
         {
            pShareholder->getRemarksList( _pRemarksList, getDataGroupId() );
            setContainer( IFASTBP_PROC::REMARKS_LIST, _pRemarksList );
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool RemarksProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_REMARKS );
}

//******************************************************************************
bool RemarksProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
   DString                 strNewAccountNumber;
   bool bRtn = false;

   try
   {
      assert( _rpChildGI && isValidModelessInterface( _rpChildGI ) );

      getParameter( REMARKSLIT::ACCOUNT_NUM, strNewAccountNumber );
      if( strNewAccountNumber != _strAccountNumber )
      {
         _strAccountNumber = strNewAccountNumber;
         getParameter (REMARKSLIT::NAME, _strName);
         setContainer( IFASTBP_PROC::REMARKS_LIST, NULL );
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
E_COMMANDRETURN RemarksProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   setParameter (REMARKSLIT::NAME, _strName);
   try
   {
      if( !isXMLAPIContext() )
         rtn = invokeCommand( this, CMD_GUI_REMARKS, getProcessType(), isModal(),
                              &_rpChildGI );
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
bool RemarksProcess::doOk( GenericInterface *rpGICaller )
{
   Shareholder *pShareholder = NULL;
   DString remarksFlag = I_( "N" );
   const BFDataGroupId& idDataGroup = getDataGroupId();
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   if( dstcWorkSession->getShareholder( idDataGroup, _strShrNum, pShareholder ) <= WARNING )
   {
      RemarksList *pRemarksList;

      if( pShareholder->getRemarksList( pRemarksList, idDataGroup ) <= WARNING )
      {
         BFObjIter iter( *pRemarksList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );

         while( !iter.end() )
         {
            if( !iter.isDummy() )
            {
               remarksFlag = I_( "Y" );
               break;
            }
            ++iter;
         }
         pShareholder->setField( ifds::Remarks, remarksFlag, idDataGroup, false );
      }
   }
   setParameter( MFCAN_IP_PARAM::FROM_REMARKS, I_("Y"));

   return(true);
}

//******************************************************************************
void RemarksProcess::doPostOk(GenericInterface *rpGICaller, bool bSuccessFlag)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("doPostOk"));

   if (bSuccessFlag)
   {
       DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
       MFAccount *pMFAccount = NULL;

       if (dstcWorkSession->getMFAccount(getDataGroupId(), _strAccountNumber, pMFAccount ) <= WARNING && pMFAccount)
       {
           pMFAccount->discardAlertMessageList();
       }
   }
}

//******************************************************************************
void *RemarksProcess::getPtrForContainer(
                                        const BFContainerId& idContainer,
                                        const BFDataGroupId& idDataGroup
                                        )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "getPtrForContainer" ) );
   void *ptr = NULL;
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   try
   {
//CP20030319      switch( idContainer )
//CP20030319      {
//CP20030319         case REMARKS_LIST:
      if( IFASTBP_PROC::REMARKS_LIST == idContainer )
      {
         {
            MFAccount   *rpMFAccount;
            RemarksList *rpRemarksList;
            Shareholder *rpShareholder;

            if( dstcWorkSession->getMFAccount( idDataGroup, _strAccountNumber, rpMFAccount ) <= WARNING )
            {
               rpMFAccount->getField( ifds::ShrNum, _strShrNum, idDataGroup );
               _strShrNum.stripLeading().stripTrailing();

               if( dstcWorkSession->getShareholder( idDataGroup, _strShrNum, rpShareholder ) <= WARNING )
               {
                  setGlobal( WORK_GLOBAL, ifds::LastActiveShrNum, _strShrNum );
                  if( rpShareholder->getRemarksList( rpRemarksList, idDataGroup ) <=
                      WARNING )
                  {
                     ptr = rpRemarksList;
                  }
               }
            }
         }
//CP20030319         default:
      }
      else
      {
//CP20030319            break;
//CP20030319      }
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
SEVERITY RemarksProcess::performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, PERFORMSEARCH );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      if( _pRemarksList != NULL )
      {
         sevRtn = _pRemarksList->getMore();
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

bool RemarksProcess::doMoreRecordsExist( GenericInterface *rpGICaller,  const BFContainerId& idSearch )
{
   return( rpGICaller == NULL || _pRemarksList == NULL ) ? 
   false : _pRemarksList->doMoreRecordsExist();
}

//*****************************************************************************
bool  RemarksProcess::getNumberOfAccountsInRemarksList( ) const 
{
  MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("getNumberOfAccountsInRemarksList") );

  DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
  Shareholder* pShareholder = NULL;
  int number_of_accts = 0;;
  if( dstcWorkSession->getShareholder( getDataGroupId(), _strShrNum, pShareholder ) <= WARNING && 
      pShareholder )
   {
      MFAccountList *pMFAccountList;
      if( pShareholder->getMFAccountList(pMFAccountList, getDataGroupId(), true) <= WARNING &&
          pMFAccountList)
       {
         BFObjIter bfIter( *pMFAccountList, getDataGroupId(), false ,BFObjIter::ITERTYPE::NON_DELETED );
         number_of_accts = bfIter.getNumberOfItemsInList();
       }
   }
  return( number_of_accts >1 ? true : false );
}

//******************************************************************************
SEVERITY RemarksProcess::doSetField(const GenericInterface *rpGICaller, 
                                    const BFContainerId &idContainer, 
                                    const BFFieldId &idField,
                                    const BFDataGroupId &idDataGroup, 
                                    const DString &strValue, 
                                    bool bFormatted) 
{  
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("doSetField"));

   if (idContainer == BF::NullContainerId)
   {
       if (idField == ifds::RemarkFilterBy)
       {
            m_filterBy = strValue;
       }
   }

   return GETHIGHESTSEVERITY();
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/RemarksProcess.cpp-arc  $
 * 
 *    Rev 1.24   May 27 2004 17:20:14   HERNANDO
 * PET1017 FN01- Remarks-Confirmation change.   Allow Confirmation to view the Added Remark and allow copying it to the AWD object.
 * 
 *    Rev 1.23   Oct 03 2003 12:21:52   VADEANUM
 * PTS 10022545 - Record created when no Remark entered on the Remarks dialog - removed getKeyForNewListItem().
 * 
 *    Rev 1.22   Oct 03 2003 09:57:32   VADEANUM
 * PTS 10022399 - Wrong Account # assigned to Remark - replaced RefAccount with AccountNum in order to have the fieldid picked up in DSTCWorkSession::commit() after including the field in the transaction key.
 * 
 *    Rev 1.21   Sep 11 2003 09:57:24   FENGYONG
 * Add comment to the refaccount default setting
 * 
 *    Rev 1.20   Jul 30 2003 11:26:58   FENGYONG
 * CIBC enhancement PET809_FN46
 * 
 *    Rev 1.19   Jul 17 2003 10:40:24   FENGYONG
 * Add fields
 * 
 *    Rev 1.18   Mar 21 2003 17:46:28   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.17   Oct 09 2002 23:53:32   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.16   Aug 29 2002 16:45:12   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.15   Aug 29 2002 12:54:38   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.14   Jul 10 2002 16:43:44   FENGYONG
 * make API work
 * 
 *    Rev 1.13   Jun 03 2002 13:55:04   FENGYONG
 * Add name for api
 * 
 *    Rev 1.12   22 May 2002 18:25:00   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.11   27 Mar 2002 19:55:36   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.10   15 May 2001 15:38:52   YINGZ
 * data group id clean up
 * 
 *    Rev 1.9   03 May 2001 14:05:36   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.8   Mar 02 2001 14:05:22   HSUCHIN
 * diable remarks in confirmation
 * 
 *    Rev 1.7   Jan 17 2001 12:08:12   VASILEAD
 * Added workSessionId param for MgmtCo::getMgmtCoOptions()
 * 
 *    Rev 1.6   15 Dec 2000 12:43:46   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.5   Oct 25 2000 12:22:10   KOVACSRO
 * bug fixed.
 * 
 *    Rev 1.4   Aug 02 2000 15:32:02   BUZILA
 * "locale" changes
 * 
 *    Rev 1.3   Jul 26 2000 17:49:50   HUDAVID
 * added performSearch(...), doMoreRecordsExist(...)
 * 
 *    Rev 1.2   Mar 29 2000 13:04:46   DT24433
 * combined CBO initialization logic from doInit,doModelessSetFocus & getPtrForContainer in getPtrForContainer
 * 
 *    Rev 1.1   Mar 07 2000 13:32:24   DT24433
 * removed substitute lists and unused headers
 * 
 *    Rev 1.0   Feb 15 2000 10:59:36   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.21   Jan 26 2000 19:40:08   POPESCUS
 * fixes related to a crash
 * 
 *    Rev 1.20   Jan 21 2000 15:45:44   HSUCHIN
 * removed settting entity name to global
 * 
 *    Rev 1.19   Jan 21 2000 14:33:04   HSUCHIN
 * add into global account number, shareholder number and  entity name
 * 
 *    Rev 1.18   Jan 19 2000 10:11:58   BUZILA
 * refresh stuf
 * 
 *    Rev 1.17   Jan 08 2000 15:02:42   POPESCUS
 * added the datagroupid
 * 
 *    Rev 1.16   08 Jan 2000 14:54:52   HSUCHIN
 * modified so that effective date now defaults to next business date when new remarks is added.
 * 
 *    Rev 1.15   Dec 22 1999 18:12:48   BUZILA
 * changes due to COA flags movament
 * 
 *    Rev 1.14   Dec 14 1999 11:37:50   BUZILA
 * change because of BFBase
 * 
 *    Rev 1.13   12 Dec 1999 12:40:24   HSUCHIN
 * no change (i think)
 * 
 *    Rev 1.12   Dec 10 1999 18:46:32   BUZILA
 * setting remarks flag in COANavig CBO
 * 
 *    Rev 1.11   Nov 10 1999 11:19:18   HSUCHIN
 * modified to update transactions and using the new basedlg and controls
 * 
 *    Rev 1.10   Nov 06 1999 15:18:56   VASILEAD
 * Modified view 5,6,11,16,51 and 85
 * 
 *    Rev 1.9   Nov 02 1999 18:38:36   DT24433
 * removed doOk/doCancel
 * 
 *    Rev 1.8   Oct 29 1999 11:30:16   BUZILA
 * changing WorkSessionDetails into a BFBase descendant
 * 
 *    Rev 1.7   Oct 29 1999 10:15:26   HSUCHIN
 * changed to use the new list control
 * 
 *    Rev 1.6   Oct 24 1999 11:11:06   POPESCUS
 * Added namespace for the string param
 * 
 *    Rev 1.5   Aug 26 1999 10:46:26   DT24433
 * changed setList to setContainer
 * 
 *    Rev 1.4   Aug 26 1999 10:41:40   DT24433
 * changed setCBOInstance to setContainer
 * 
 *    Rev 1.3   Aug 19 1999 15:18:48   DT24433
 * removed static FieldDetails array
 * 
 *    Rev 1.2   Jul 20 1999 11:14:12   VASILEAD
 * New conditions update
 * 
 *    Rev 1.1   Jul 08 1999 10:02:10   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
