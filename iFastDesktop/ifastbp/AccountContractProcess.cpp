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
// ^FILE   : AccountContractProcess.cpp
// ^AUTHOR : 
// ^DATE   : Jan 17, 2003
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : AccountContractProcess
//    This class manages the remarks information.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include <ifastcbo\accountcontractlist.hpp>
#include "accountcontractprocess.hpp"
#include "accountcontractprocessincludes.h"
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\mfaccountholdinglist.hpp>
#include <ifastcbo\fundmasterlist.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastdataimpl\dse_dstc0239_vw.hpp>
#include <ifastdataimpl\dse_dstc0239_vwrepeat_record.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_ACCOUNT_CONTRACT;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACCOUNT_CONTRACT;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< AccountContractProcess > processCreator( CMD_BPROC_ACCOUNT_CONTRACT );

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
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace AUDITTYPE
{
   extern CLASS_IMPORT I_CHAR * const PFC;
}

//******************************************************************************
// Constructor - Container and field details are initialized here.
//******************************************************************************

AccountContractProcess::AccountContractProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pAccountContractList( NULL )
, _pMFAccount (NULL)
, _pAccountHoldingList (NULL)
, _rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   //readonly
   addContainer( IFASTBP_PROC::ACCOUNT_CONTRACT_LIST, true,  BF::NullContainerId, false ); 
   addContainer( IFASTBP_PROC::ACCOUNT_HOLDINGS,      true,  BF::NullContainerId, false ); 
   addContainer( IFASTBP_PROC::MFACCOUNT,             false, BF::NullContainerId, false );    
   addContainer( IFASTBP_PROC::PROT_FUND_LIST,        true,  BF::NullContainerId, false );    

   addFieldDetails( ifds::FundNumber,             IFASTBP_PROC::ACCOUNT_CONTRACT_LIST, SUBCLASS_PROCESS );   
   addFieldDetails( ifds::FundCode,               IFASTBP_PROC::ACCOUNT_CONTRACT_LIST );
   addFieldDetails( ifds::ClassCode,              IFASTBP_PROC::ACCOUNT_CONTRACT_LIST );
   addFieldDetails( ifds::EffectiveDate,          IFASTBP_PROC::ACCOUNT_CONTRACT_LIST );
   addFieldDetails( ifds::MaturityDate,           IFASTBP_PROC::ACCOUNT_CONTRACT_LIST );
   addFieldDetails( ifds::GuarAmt,                IFASTBP_PROC::ACCOUNT_CONTRACT_LIST );
   addFieldDetails( ifds::GuarUnits,              IFASTBP_PROC::ACCOUNT_CONTRACT_LIST );   
   addFieldDetails( ifds::MktValue,               IFASTBP_PROC::ACCOUNT_CONTRACT_LIST );   
   addFieldDetails( ifds::GainOrLossAmt,          IFASTBP_PROC::ACCOUNT_CONTRACT_LIST );   
   addFieldDetails( ifds::ModUser,                IFASTBP_PROC::ACCOUNT_CONTRACT_LIST );   
   addFieldDetails( ifds::ModDate,                IFASTBP_PROC::ACCOUNT_CONTRACT_LIST );   
   addFieldDetails( ifds::Username,               IFASTBP_PROC::ACCOUNT_CONTRACT_LIST );   
   addFieldDetails( ifds::ProcessDate,            IFASTBP_PROC::ACCOUNT_CONTRACT_LIST );   
   addFieldDetails( ifds::ResetID,                IFASTBP_PROC::ACCOUNT_CONTRACT_LIST );   
   addFieldDetails( ifds::ResetExist,             IFASTBP_PROC::ACCOUNT_CONTRACT_LIST, SUBCLASS_PROCESS );   
   addFieldDetails( ACC_CONTRACT::FUNDDESC,       IFASTBP_PROC::ACCOUNT_CONTRACT_LIST, SUBCLASS_PROCESS );   
   addFieldDetails( ACC_CONTRACT::SEARCHFUNDDESC, IFASTBP_PROC::ACCOUNT_CONTRACT_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::ProtContractRId,        IFASTBP_PROC::ACCOUNT_CONTRACT_LIST );   

   addFieldDetails( ifds::rxFundCode,             IFASTBP_PROC::ACCOUNT_HOLDINGS );   
   addFieldDetails( ifds::rxClassCode,            IFASTBP_PROC::ACCOUNT_HOLDINGS );   
   addFieldDetails( ifds::FundCode,               IFASTBP_PROC::PROT_FUND_LIST );   
   addFieldDetails( ifds::ClassCode,              IFASTBP_PROC::PROT_FUND_LIST );   

   // General Account information.
   addFieldDetails( ifds::AccountNum,             IFASTBP_PROC::MFACCOUNT );
   addFieldDetails( ifds::ShrNum,                 IFASTBP_PROC::MFACCOUNT );
}

//******************************************************************************
// Destructor - Since accruals are not held in the repository, we need to delete
// the cbos when we are finish with them.
//******************************************************************************

AccountContractProcess::~AccountContractProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   _pAccountContractList = NULL;   
   _pMFAccount = NULL;
   _pAccountHoldingList = NULL;
}

//******************************************************************************
// Function which get the container pointer on demand.
// @param   const BFContainerId& idContainer - Id to the container.
//          const BFDataGroupId& idDataGroup - group id.
// @returns void.
//******************************************************************************

void *AccountContractProcess::getPtrForContainer( const BFContainerId& idContainer,
                                                  const BFDataGroupId& idDataGroup )
{
   void *ptr = NULL;
   SEVERITY sevRtn = NO_CONDITION;
   try
   {
      if( IFASTBP_PROC::ACCOUNT_CONTRACT_LIST == idContainer )
      {
         {
            ptr = _pAccountContractList;                  
         }
      }
      else if( IFASTBP_PROC::ACCOUNT_HOLDINGS == idContainer )
      {
         {
            ptr = _pAccountHoldingList;
         }
      }
      else if( IFASTBP_PROC::MFACCOUNT == idContainer )
      {
         {            
            ptr = _pMFAccount;          
         }
      }
      else if( IFASTBP_PROC::PROT_FUND_LIST == idContainer )
      {
         {
            DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
            ProtectedFundList* pProtectedFundList;
            pDSTCWorkSession->getProtectedFundList ( pProtectedFundList );
            ptr = pProtectedFundList;
         }
      }
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( ... )
   {
      //Show we throw?
   }
   return(ptr);
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

void AccountContractProcess::doGetField( const GenericInterface *rpGICaller,
                                         const BFContainerId& idContainer,
                                         const BFFieldId& idField,
                                         const BFDataGroupId& idDataGroup,
                                         DString &strValueOut,
                                         bool bFormatted ) const
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOGETFIELD );
   if( idField == ifds::FundNumber )
   {
      DString dstrFundCode, dstrClassCode;
      const_cast <AccountContractProcess*> (this)->getField( rpGICaller, IFASTBP_PROC::ACCOUNT_CONTRACT_LIST, 
                                                             ifds::FundCode, dstrFundCode, false);
      const_cast <AccountContractProcess*> (this)->getField( rpGICaller, IFASTBP_PROC::ACCOUNT_CONTRACT_LIST, 
                                                             ifds::ClassCode, dstrClassCode, false);
      DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      pDSTCWorkSession->GetFundNumber ( dstrFundCode, dstrClassCode, strValueOut );      
   }
   else if( idField == ifds::ResetExist )
   {
      DString dstrResetID;
      const_cast <AccountContractProcess*> (this)->getField( rpGICaller, IFASTBP_PROC::ACCOUNT_CONTRACT_LIST, 
                                                             ifds::ResetID, dstrResetID, false);
      const BFDataFieldProperties* pProps = BFDataFieldProperties::get( ifds::ResetExist );
      const BFSubstitutionSet* pSubSet = pProps->getSubstitutionSet(ClientLocaleContext::get());
      strValueOut = dstrResetID != I_("0")?pSubSet->getValue( I_( "Y" ) ):pSubSet->getValue( I_( "N" ));
   }
   else if( idField == ACC_CONTRACT::FUNDDESC )
   {
      DString dstrFundCode, dstrClassCode;
      const_cast <AccountContractProcess*> (this)->getField( rpGICaller, IFASTBP_PROC::ACCOUNT_CONTRACT_LIST, 
                                                             ifds::FundCode, dstrFundCode, false);
      const_cast <AccountContractProcess*> (this)->getField( rpGICaller, IFASTBP_PROC::ACCOUNT_CONTRACT_LIST, 
                                                             ifds::ClassCode, dstrClassCode, false);
      _pFundMasterList->getFundName( dstrFundCode, strValueOut);
   }
   else if( idField == ACC_CONTRACT::SEARCHFUNDDESC )
   {
      // The key to account holdings is passed in through strValueOut.
      DString dstrFundCode;
      if( strValueOut == NULL_STRING )
      {
         strValueOut = NULL_STRING;
      }
      else
      {
         BFObjIter iter( *_pAccountHoldingList, getDataGroupId() );
         if( iter.positionByKey( strValueOut ) )
         {
            iter.getObject()->getField ( ifds::rxFundCode, dstrFundCode, getDataGroupId () );
            _pFundMasterList->getFundName ( dstrFundCode, strValueOut );
         }
      }
   }
}

//******************************************************************************
// Initializes all the search criteria cbos and accrual list cbos.
// @returns SEVERITY.
//******************************************************************************

SEVERITY AccountContractProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      const BFDataGroupId& idDataGroup = getDataGroupId();
      getParameter( ACC_CONTRACT::ACCOUNT_NUM, _dstrAccountNum );           
      DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      if( pDSTCWorkSession->getMFAccount( idDataGroup, _dstrAccountNum, _pMFAccount) <= WARNING && _pMFAccount )
      {
         _pMFAccount->getAccountContractList( _pAccountContractList, _dstrAccountNum, NULL_STRING, NULL_STRING, idDataGroup );
         _pMFAccount->getAccountHoldingList( _pAccountHoldingList, idDataGroup );
      }
      pDSTCWorkSession->getMgmtCo().getFundMasterList( _pFundMasterList );
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

bool AccountContractProcess::doModelessChildComplete( const Command &cmd )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOMODELESSCHILDCOMPLETE );

   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_ACCOUNT_CONTRACT );
}


//******************************************************************************
// @param   GenericInterface *rpGICaller - pointer to parent object.
// @return bool - true when successful, false otherwise.
//******************************************************************************

bool AccountContractProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );

   bool bRtn = false;
   try
   {
      assert( _rpChildGI && isValidModelessInterface( _rpChildGI ) );

      if( isValidModelessInterface( _rpChildGI ) )
      {  // Only if child still exists
         _pAccountContractList = NULL;   
         _pMFAccount = NULL;
         _pAccountHoldingList = NULL;

         const BFDataGroupId& idDataGroup = getDataGroupId();
         getParameter( ACC_CONTRACT::ACCOUNT_NUM, _dstrAccountNum );           
         DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
         if( pDSTCWorkSession->getMFAccount( idDataGroup, _dstrAccountNum, _pMFAccount) <= WARNING && _pMFAccount )
         {
            _pMFAccount->getAccountContractList( _pAccountContractList, _dstrAccountNum, NULL_STRING, NULL_STRING, idDataGroup );
            _pMFAccount->getAccountHoldingList( _pAccountHoldingList, idDataGroup );
         }
         pDSTCWorkSession->getMgmtCo().getFundMasterList( _pFundMasterList );

         setContainer( IFASTBP_PROC::MFACCOUNT, NULL );
         setContainer( IFASTBP_PROC::ACCOUNT_CONTRACT_LIST, NULL );
         setContainer( IFASTBP_PROC::ACCOUNT_HOLDINGS, NULL );
         setContainer( IFASTBP_PROC::PROT_FUND_LIST, NULL );

         bRtn = _rpChildGI->refresh( this, NULL );
         bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
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

E_COMMANDRETURN AccountContractProcess::doProcess()
{  
   MAKEFRAME2( CND::IFASTBP_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      rtn = invokeCommand( this, CMD_GUI_ACCOUNT_CONTRACT, getProcessType(),
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

SEVERITY AccountContractProcess::performSearch( GenericInterface *rpGICaller, 
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
               DString dstrFundClass, dstrFundCode, dstrClassCode;
               getParameter( ACC_CONTRACT::FUNDCLASS, dstrFundClass );
               if( dstrFundClass == NULL_STRING )
               {
                  dstrFundCode = NULL_STRING;
                  dstrClassCode = NULL_STRING;
               }
               else
               {

                  BFObjIter iter( *_pAccountHoldingList, getDataGroupId() );
                  if( iter.positionByKey( dstrFundClass ) )
                  {
                     iter.getObject()->getField ( ifds::rxFundCode, dstrFundCode, getDataGroupId () );
                     iter.getObject()->getField ( ifds::rxClassCode, dstrClassCode, getDataGroupId () );
                  }
               }
               if( _pMFAccount )
               {
                  _pMFAccount->getAccountContractList( _pAccountContractList, _dstrAccountNum, dstrFundCode, dstrClassCode, getDataGroupId() );
               }
               if( _pAccountContractList )
                  setContainer ( IFASTBP_PROC::ACCOUNT_CONTRACT_LIST, _pAccountContractList );
               else
                  setContainer ( IFASTBP_PROC::ACCOUNT_CONTRACT_LIST, NULL );

            }
            break;
         case SEARCH_NEXT_BLOCK:
            {
               _pAccountContractList->getMore ();
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

bool AccountContractProcess::doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch )
{
   if( rpGICaller == NULL )
      return(false);
   return( _pAccountContractList == NULL ) ? false : _pAccountContractList->doMoreRecordsExist();     
}

//******************************************************************************

SEVERITY AccountContractProcess::getHistoricalParameters( const BFContainerId& idContainer, HISTORICAL_VECTOR &vectorHistorical )
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);

   DString keyStringIDI( NULL_STRING ), dstrRecord;
   getField( this, IFASTBP_PROC::ACCOUNT_CONTRACT_LIST, ifds::ProtContractRId, dstrRecord, false );
   HistoricalElement historicalElement( dstrRecord, AUDITTYPE::PFC, keyStringIDI );
   vectorHistorical.push_back( historicalElement );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AccountContractProcess.cpp-arc  $
// 
//    Rev 1.12   Nov 17 2004 15:18:26   popescu
// PET 1117/56, removed 'getField' method at the fund master list level, 
// 
//    Rev 1.11   Mar 10 2004 13:02:36   HERNANDO
// PET965 FN11 - Changed getHistoricalParameters.
// 
//    Rev 1.10   Aug 18 2003 16:07:58   HERNANDO
// Added keys to getHistoricalParameters.
// 
//    Rev 1.9   Jul 29 2003 14:30:14   HERNANDO
// PTS 10016740 - Changed doModelessSetFocus to reflect currently selected Account.
// 
//    Rev 1.8   Apr 02 2003 12:19:08   PURDYECH
// Code cleanup
// 
//    Rev 1.7   Mar 21 2003 17:34:06   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.6   Mar 11 2003 13:49:40   PURDYECH
// Fixes to help the DataGroupId source code converters work more smoothly.
// 
//    Rev 1.5   Mar 05 2003 11:22:26   PURDYECH
// IFastBaseProcess no longer exists.  Classes now derive from AbstractProcess (again) and the Protocol class IFastHistoricalParameters.
// 
//    Rev 1.4   Jan 29 2003 15:50:26   HSUCHIN
// added historical functionality
// 
//    Rev 1.3   Jan 26 2003 14:44:48   HSUCHIN
// bug fix for empty list
// 
//    Rev 1.2   Jan 22 2003 18:00:04   HSUCHIN
// fixed bug in refresh
// 
//    Rev 1.1   Jan 21 2003 13:44:34   HSUCHIN
// added support to protected fund list and a couple bug fixes
// 
//    Rev 1.0   Jan 20 2003 17:20:08   HSUCHIN
// Initial Revision
 */
