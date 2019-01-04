//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2003 by International Financial.
//
//******************************************************************************
//
// ^FILE   : ResetInstrProcess.cpp
// ^AUTHOR : 
// ^DATE   : Jan 23, 2003
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : ResetInstrProcess
//    This class manages the remarks information.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include <ifastcbo\accountcontractlist.hpp>
#include "resetinstrprocess.hpp"
#include "resetinstrprocessincludes.h"
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\mfaccountholdinglist.hpp>
#include <ifastcbo\fundmasterlist.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\resetinstrlist.hpp>
#include <ifastcbo\resetinstrcriteria.hpp>
#include <ifastcbo\fundmasterlist.hpp>
#include <ifastdataimpl\dse_dstc0243_vwrepeat_record.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_RESET_INSTR;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_RESET_INSTR;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< ResetInstrProcess > processCreator( CMD_BPROC_RESET_INSTR );

//******************************************************************************
// MF - Management Fee
// MFR - Management Fee Rebate
//******************************************************************************

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME               = I_( "AccountContractProcess" );
   const I_CHAR * const PERFORMSEARCH           = I_( "performSearch" );   
   const I_CHAR * const ALL                     = I_( "All" );
   const I_CHAR * const YES                     = I_( "Y" );
   const I_CHAR * const NO                      = I_( "N" );
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace AUDITTYPE
{
   extern CLASS_IMPORT I_CHAR * const PFR;
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
}

//******************************************************************************
// Constructor - Container and field details are initialized here.
//******************************************************************************

//CP20030319ResetInstrProcess::ResetInstrProcess() 
ResetInstrProcess::ResetInstrProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
,  _pResetInstrList ( NULL )
, _pResetInstrCriteria ( NULL )
, _rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   //readonly
   addContainer( IFASTBP_PROC::RESET_INSTR_LIST, true, BF::NullContainerId, true );    
   addContainer( IFASTBP_PROC::RESET_INSTR_CRITERIA, false, BF::NullContainerId, true );
   addContainer( IFASTBP_PROC::MFACCOUNT, false, BF::NullContainerId, false );

   addFieldDetails( ifds::AccountNum, IFASTBP_PROC::RESET_INSTR_LIST );   
   addFieldDetails( ifds::FundNumber, IFASTBP_PROC::RESET_INSTR_LIST, SUBCLASS_PROCESS );
   addFieldDetails( RESET_INSTR::FUNDDESC, IFASTBP_PROC::RESET_INSTR_LIST, SUBCLASS_PROCESS );
//   addFieldDetails( ifds::Name, RESET_INSTR::RESET_INSTR_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::FundCode, IFASTBP_PROC::RESET_INSTR_LIST );
   addFieldDetails( ifds::ClassCode, IFASTBP_PROC::RESET_INSTR_LIST );
   addFieldDetails( ifds::ResetType, IFASTBP_PROC::RESET_INSTR_LIST );
   addFieldDetails( ifds::ResetDate, IFASTBP_PROC::RESET_INSTR_LIST );
   addFieldDetails( ifds::CompleteDate, IFASTBP_PROC::RESET_INSTR_LIST );
   addFieldDetails( ifds::BatchName, IFASTBP_PROC::RESET_INSTR_LIST );
   addFieldDetails( ifds::BatchEffective, IFASTBP_PROC::RESET_INSTR_LIST );
   addFieldDetails( ifds::Trace, IFASTBP_PROC::RESET_INSTR_LIST );
   addFieldDetails( ifds::CanResetId, IFASTBP_PROC::RESET_INSTR_LIST );   
   addFieldDetails( ifds::ProtContractRId, IFASTBP_PROC::RESET_INSTR_LIST );      
   addFieldDetails( RESET_INSTR::updated, IFASTBP_PROC::RESET_INSTR_LIST, SUBCLASS_PROCESS );   
   addFieldDetails( RESET_INSTR::ORIKEY, IFASTBP_PROC::RESET_INSTR_LIST, SUBCLASS_PROCESS );   
   addFieldDetails( RESET_INSTR::DESTKEY, IFASTBP_PROC::RESET_INSTR_LIST, SUBCLASS_PROCESS );   
   addFieldDetails( ifds::ResetInstrUsing, IFASTBP_PROC::RESET_INSTR_CRITERIA );
   addFieldDetails( ifds::AccountNum, IFASTBP_PROC::RESET_INSTR_CRITERIA );
   addFieldDetails( ifds::ResetDate, IFASTBP_PROC::RESET_INSTR_CRITERIA );
   addFieldDetails( ifds::AccountNum, IFASTBP_PROC::MFACCOUNT );
   addFieldDetails( ifds::ShrNum, IFASTBP_PROC::MFACCOUNT );
}

//******************************************************************************
// Destructor - Since accruals are not held in the repository, we need to delete
// the cbos when we are finish with them.
//******************************************************************************

ResetInstrProcess::~ResetInstrProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
// Function which get the container pointer on demand.
// @param   const BFContainerId& idContainer - Id to the container.
//          const BFDataGroupId& idDataGroup - group id.
// @returns void.
//******************************************************************************
void *ResetInstrProcess::getPtrForContainer(const BFContainerId& idContainer,
   const BFDataGroupId& idDataGroup)
{
   void *ptr = NULL;
   DSTCWorkSession *pDSTCWorkSession = 
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   try
   {
      if( IFASTBP_PROC::RESET_INSTR_LIST == idContainer )
      {
         if (pDSTCWorkSession->getResetInstrList(_pResetInstrList, 
            idDataGroup) <= WARNING)
         {
            ptr = _pResetInstrList;
         }
      }
      else if( IFASTBP_PROC::RESET_INSTR_CRITERIA == idContainer )
      {
         {
            ptr = _pResetInstrCriteria;
         }
      }
   }
   catch(ConditionException &)
   {
      throw;
   }
   catch(...)
   {
      assert(0);
      THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, I_("getPtrForContainer"),
         CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return ptr;
}

//******************************************************************************
// @param   const GenericInterface *rpGICaller - pointer to parent object.
//          const BFContainerId& idContainer - container id.
//          const BFFieldId& idField - field requested.
//          const BFDataGroupId& idDataGroup - group id.
//          DString &strValueOut - Field value returned.
//          bool bFormatted - boolean indicating value to be formatted or not.
// @returns void.
//******************************************************************************

void ResetInstrProcess::doGetField(
                                  const GenericInterface *rpGICaller,
                                  const BFContainerId& idContainer,
                                  const BFFieldId& idField,
                                  const BFDataGroupId& idDataGroup,
                                  DString &strValueOut,
                                  bool bFormatted
                                  ) const
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOGETFIELD );
   if( idField == ifds::FundNumber )
   {
      DString dstrFundCode, dstrClassCode;
      const_cast <ResetInstrProcess*> (this)->getField( rpGICaller, IFASTBP_PROC::RESET_INSTR_LIST, 
                                                        ifds::FundCode, dstrFundCode, false);
      const_cast <ResetInstrProcess*> (this)->getField( rpGICaller, IFASTBP_PROC::RESET_INSTR_LIST, 
                                                        ifds::ClassCode, dstrClassCode, false);
      DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      dstrFundCode.upperCase();
      dstrClassCode.upperCase();
      if( ( dstrFundCode == NULL_STRING ) || ( dstrClassCode == NULL_STRING ) )
         strValueOut = NULL_STRING;
      else
         pDSTCWorkSession->GetFundNumber ( dstrFundCode, dstrClassCode, strValueOut );
   }
   else if( idField == RESET_INSTR::updated )
   {
      if( _pResetInstrList )
      {
         bool bUpdated = _pResetInstrList->isUpdatedForDataGroup(idDataGroup );
         strValueOut = bUpdated? YES:NO;
      }
   }
   else if( idField == RESET_INSTR::FUNDDESC )
   {
      DString dstrFundCode;
      const_cast <ResetInstrProcess*> (this)->getField( rpGICaller, IFASTBP_PROC::RESET_INSTR_LIST, 
                                                        ifds::FundCode, dstrFundCode, false);
      if( dstrFundCode != NULL_STRING )
         _pFundMasterList->getFundName (dstrFundCode, strValueOut);
      else
         strValueOut = NULL_STRING;
   }
}

//******************************************************************************
// Initializes all the search criteria cbos and accrual list cbos.
// @returns SEVERITY.
//******************************************************************************

SEVERITY ResetInstrProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      getParameter ( RESET_INSTR::ACCOUNT_NUM , _dstrAccountNum );
      getParameter( RESET_INSTR::PARENT, _dstrParent );
      const BFDataGroupId& idDataGroup = getDataGroupId();      
      DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      pDSTCWorkSession->getMgmtCo().getFundMasterList( _pFundMasterList );
      _pResetInstrCriteria = new ResetInstrCriteria (*getBFWorkSession());
      _pResetInstrCriteria->init ( _dstrAccountNum, idDataGroup );
      pDSTCWorkSession->createResetInstrList ( _pResetInstrList, idDataGroup );
      _pResetInstrList->init ( _dstrAccountNum, NULL_STRING );
//      pDSTCWorkSession->createResetInstrCriteria ( _pResetInstrCriteria, idDataGroup );
//      _pResetInstrCriteria->init( dstrAccountNum, idDataGroup );
      //_pResetInstrCriteria->createResetInstrList ( _pResetInstrList, idDataGroup, true );
      setContainer (  IFASTBP_PROC::RESET_INSTR_LIST, NULL );    

      // Set MFACCOUNT CBO
      MFAccount *_pMFAccount = NULL;
      pDSTCWorkSession->getMFAccount( getDataGroupId( ), _dstrAccountNum, _pMFAccount );
      setContainer( IFASTBP_PROC::MFACCOUNT, _pMFAccount );
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
// Function which tells the generic interface container that the modeless child
// has been destroyed.
// @param   const Command &cmd - cmd indicating the child is destroyed.
// @returns bool - true when successful.
//******************************************************************************

bool ResetInstrProcess::doModelessChildComplete( const Command &cmd )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOMODELESSCHILDCOMPLETE );

   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_RESET_INSTR );
}


//******************************************************************************
// @param   GenericInterface *rpGICaller - pointer to parent object.
// @return bool - true when successful, false otherwise.
//******************************************************************************

bool ResetInstrProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );

   bool bRtn = false;
   try
   {
      assert( _rpChildGI && isValidModelessInterface( _rpChildGI ) );

      if( isValidModelessInterface( _rpChildGI ) )
      {  // Only if child still exists
/*         DString dstrNewAccountNum;
         getParameter( ACC_CONTRACT::ACCOUNT_NUM, dstrNewAccountNum );
         if ( dstrNewAccountNum != _dstrAccountNum ) {
            _dstrAccountNum = dstrNewAccountNum;*/
         bRtn = _rpChildGI->refresh( this, NULL );
         bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
         /*       } else {
                   return true;
                }*/
      }

      return(bRtn);
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
   return(false);
}

//******************************************************************************
// @returns E_COMMANDRETURN.
//******************************************************************************

E_COMMANDRETURN ResetInstrProcess::doProcess()
{  
   MAKEFRAME2( CND::IFASTBP_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter( RESET_INSTR::PARENT, _dstrParent );
      rtn = invokeCommand( this, CMD_GUI_RESET_INSTR, getProcessType(),
                           isModal(), &_rpChildGI );
   }
   catch( ConditionException &ce )
   {
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
// @param   GenericInterface *rpGICaller - pointer to parent object.
//          const BFContainerId& idSearch - Type of search is requested.
//          E_SEARCHACTION eSearchAction - SEARCH_START (new search)
//                                         SEARCH_NEXT_BLOCK ( get More )
//******************************************************************************

SEVERITY ResetInstrProcess::performSearch( GenericInterface *rpGICaller, 
                                           const BFContainerId& idSearch, E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, PERFORMSEARCH );
   SEVERITY sevRtn = SEVERE_ERROR;

   const BFDataGroupId& idDataGroup = getDataGroupId ();
   try
   {
      switch( eSearchAction )
      {
         case SEARCH_START:
            {
               const BFDataGroupId& idDataGroup = getDataGroupId();
               DString dstrResetDate;
               const_cast <ResetInstrProcess*> (this)->getField( rpGICaller, IFASTBP_PROC::RESET_INSTR_CRITERIA, 
                                                                 ifds::ResetDate, dstrResetDate, false);
               DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());               
               pDSTCWorkSession->createResetInstrList ( _pResetInstrList, idDataGroup );
               _pResetInstrList->init ( _dstrAccountNum, dstrResetDate );
               if( _pResetInstrList )
                  setContainer ( IFASTBP_PROC::RESET_INSTR_LIST, _pResetInstrList );
               else
                  setContainer ( IFASTBP_PROC::RESET_INSTR_LIST, NULL );
            }
            break;
         case SEARCH_NEXT_BLOCK:
            {
               _pResetInstrList->getMore ();
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
   return(sevRtn); 
}

//******************************************************************************
// @param   GenericInterface *rpGICaller - pointer to parent object.
//          in idSearch - Type of search is requested.
// @returns bool - true if there are more data
//                 false otherwise.
//******************************************************************************

bool ResetInstrProcess::doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch )
{
   if( rpGICaller == NULL )
      return(false);
   return( _pResetInstrList == NULL ) ? false : _pResetInstrList->doMoreRecordsExist();     
}


SEVERITY ResetInstrProcess::doSetField( const GenericInterface *rpGICaller,
                                        const BFContainerId& idContainer,
                                        const BFFieldId& fieldID,
                                        const BFDataGroupId& idDataGroup,
                                        const DString& strValue,
                                        bool bFormatted )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOSETFIELD );

   if( idContainer == IFASTBP_PROC::RESET_INSTR_LIST )
   {
      if( fieldID == ifds::FundNumber )
      {
         DString dstrCanResetId, dstrCompleteDate;
         const_cast <ResetInstrProcess*> (this)->setField( rpGICaller, IFASTBP_PROC::RESET_INSTR_LIST, 
                                                           ifds::CanResetId, dstrCanResetId, false);
         const_cast <ResetInstrProcess*> (this)->setField( rpGICaller, IFASTBP_PROC::RESET_INSTR_LIST, 
                                                           ifds::CompleteDate, dstrCompleteDate, false);

         if( ( dstrCanResetId != NULL_STRING ) || ( dstrCompleteDate != NULL_STRING ) )
            return(NO_CONDITION);

         DString dstrFundCode, dstrClassCode;
         if( strValue == NULL_STRING )
         {
            dstrFundCode = NULL_STRING;
            dstrClassCode = NULL_STRING;
         }
         else
         {

            DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
            pDSTCWorkSession->GetFundClassCode ( strValue, dstrFundCode, dstrClassCode );
         }
         const_cast <ResetInstrProcess*> (this)->setField( rpGICaller, IFASTBP_PROC::RESET_INSTR_LIST, 
                                                           ifds::FundCode, dstrFundCode, false);
         const_cast <ResetInstrProcess*> (this)->setField( rpGICaller, IFASTBP_PROC::RESET_INSTR_LIST, 
                                                           ifds::ClassCode, dstrClassCode, false);
      }
      else if( fieldID == RESET_INSTR::ORIKEY )
      {
         _OriKey = strValue;
      }
      else if( fieldID == RESET_INSTR::DESTKEY )
      {
         _pResetInstrList->Reversal ( _OriKey, strValue, idDataGroup );
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}


bool ResetInstrProcess::setCommitDataGroupAsHost()
{
   return(true);
};

//******************************************************************************
SEVERITY ResetInstrProcess::getHistoricalParameters(const BFContainerId& idContainer, 
                                                    BFFieldId &recordIdField, DString& tableId,
                                                    DString& dstrKeys) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS );

   if( idContainer == IFASTBP_PROC::RESET_INSTR_LIST )
   {
      recordIdField = ifds::ProtContractRId;
      tableId = AUDITTYPE::PFR;
      dstrKeys = NULL_STRING;
   }
   else
   {
      assert(0);
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY ResetInstrProcess::getHistoricalParameters( 
   const BFContainerId& idContainer, 
   HISTORICAL_VECTOR &vectorHistorical )
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ResetInstrProcess.cpp-arc  $
// 
//    Rev 1.12   Nov 17 2004 15:18:58   popescu
// PET 1117/56, removed 'getField' method at the fund master list level, 
// 
//    Rev 1.11   Mar 10 2004 13:19:28   HERNANDO
// PET965 FN11 - Added getHistoricalParameters.
// 
//    Rev 1.10   Aug 18 2003 16:10:26   HERNANDO
// Added keys to getHistoricalParameters.
// 
//    Rev 1.9   Jul 08 2003 15:02:24   HERNANDO
// PTS 10019155.
// 
//    Rev 1.8   May 28 2003 10:52:08   popescu
// Part of the cleaning of DSTCWorksession, not finalized yet, more to come....
// 
//    Rev 1.7   Mar 21 2003 17:46:58   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.6   Mar 09 2003 15:56:26   PURDYECH
// Small fixes around DataGroupIds and ContainerIds.
// 
//    Rev 1.5   Mar 05 2003 11:22:52   PURDYECH
// IFastBaseProcess no longer exists.  Classes now derive from AbstractProcess (again) and the Protocol class IFastHistoricalParameters.
// 
//    Rev 1.4   Jan 29 2003 16:25:58   HSUCHIN
// added support for historical
// 
//    Rev 1.3   Jan 29 2003 12:15:30   HSUCHIN
// bug fix to setting fund number
// 
//    Rev 1.2   Jan 27 2003 07:38:34   HSUCHIN
// added support for reversal
// 
//    Rev 1.1   Jan 26 2003 16:02:28   HSUCHIN
// added more support
// 
//    Rev 1.0   Jan 24 2003 16:10:26   HSUCHIN
// Initial Revision
 */