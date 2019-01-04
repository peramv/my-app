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
// ^FILE   : InventorySummaryprocess.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : Feb 20, 2004
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : InventorySummaryprocess
//    This class manages the remarks information.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include <ifastcbo\InventorySummary.hpp>
#include <ifastcbo\InventorySummaryList.hpp>
#include <ifastcbo\InventoryDetailsList.hpp>
#include "InventorySummaryProcess.hpp"
#include "InventorySummaryProcessincludes.h"
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\mfaccountholdinglist.hpp>
#include <ifastcbo\fundmasterlist.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastdataimpl\dse_dstc0287_vw.hpp>
#include <ifastdataimpl\dse_dstc0287_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0292_vwrepeat_record.hpp>  // Inventory Details List
#include <ifastdataimpl\dse_dstc0063_vwrepeat_record.hpp>  // Fund Master List
#include <ifastcbo\funddetaillist.hpp>
#include <ifastcbo\funddetail.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_INVENTORY_SUMMARY;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_INVENTORY_SUMMARY;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< InventorySummaryProcess > processCreator( CMD_BPROC_INVENTORY_SUMMARY );

//******************************************************************************
// MF - Management Fee
// MFR - Management Fee Rebate
//******************************************************************************

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME               = I_( "InventorySummaryProcess" );
   const I_CHAR * const PERFORMSEARCH           = I_( "performSearch" );   
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId rxFundCode;
   extern CLASS_IMPORT const BFTextFieldId rxClassCode;
   extern CLASS_IMPORT const BFTextFieldId InventorySummHeading;
   extern CLASS_IMPORT const BFTextFieldId SortBy;
   extern CLASS_IMPORT const BFIntegerFieldId SortByColumn;
   extern CLASS_IMPORT const BFTextFieldId SortOrder;
   extern CLASS_IMPORT const BFTextFieldId RDRAdvice;
   extern CLASS_IMPORT const BFTextFieldId G1G2TrackType;
   extern CLASS_IMPORT const BFTextFieldId DisplayRolloverQualificationDate;
}

//******************************************************************************
// Constructor - Container and field details are initialized here.
//******************************************************************************

InventorySummaryProcess::InventorySummaryProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pInventorySummaryList( NULL )
, _pMFAccount (NULL)
, _pAccountHoldingList (NULL)
, _rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addSubstituteList( ifds::InventorySummHeading );

   //readonly
   addContainer( IFASTBP_PROC::INVENTORY_SUMMARY_LIST, true,  BF::NullContainerId, true ); 
   addContainer( IFASTBP_PROC::INVENTORY_DETAILS_LIST, true,  BF::NullContainerId, true ); // Repeateable, updateable
   addContainer( IFASTBP_PROC::ACCOUNT_HOLDINGS,       true,  BF::NullContainerId, false ); 
   addContainer( IFASTBP_PROC::MFACCOUNT,              false, BF::NullContainerId, false ); 
   addContainer( IFASTBP_PROC::FUND_MASTER_LIST,       true,  BF::NullContainerId, false ); 

   addFieldDetails( ifds::FundNumber,                 IFASTBP_PROC::INVENTORY_SUMMARY_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::UnitsTotal,                 IFASTBP_PROC::INVENTORY_SUMMARY_LIST, SUBCLASS_PROCESS);
   addFieldDetails( ifds::TotalCBFFreeUnits,          IFASTBP_PROC::INVENTORY_SUMMARY_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::InvSummId,                  IFASTBP_PROC::INVENTORY_SUMMARY_LIST );
   addFieldDetails( ifds::Units,                      IFASTBP_PROC::INVENTORY_SUMMARY_LIST );
   addFieldDetails( ifds::InvStatus,                  IFASTBP_PROC::INVENTORY_SUMMARY_LIST );
   addFieldDetails( ifds::OrigEffectiveDate,          IFASTBP_PROC::INVENTORY_SUMMARY_LIST );
   addFieldDetails( ifds::MaturityDate,               IFASTBP_PROC::INVENTORY_SUMMARY_LIST );
   addFieldDetails( ifds::RollQualDate,               IFASTBP_PROC::INVENTORY_SUMMARY_LIST );
   addFieldDetails( ifds::LastActiveDate,             IFASTBP_PROC::INVENTORY_SUMMARY_LIST );
   addFieldDetails( ifds::FromFund,                   IFASTBP_PROC::INVENTORY_SUMMARY_LIST );
   addFieldDetails( ifds::FromClass,                  IFASTBP_PROC::INVENTORY_SUMMARY_LIST );
   addFieldDetails( ifds::TransType,                  IFASTBP_PROC::INVENTORY_SUMMARY_LIST );
   addFieldDetails( ifds::PartnerShip,                IFASTBP_PROC::INVENTORY_SUMMARY_LIST );
   addFieldDetails( ifds::OrigFundRate,               IFASTBP_PROC::INVENTORY_SUMMARY_LIST );
   addFieldDetails( ifds::Rate,                       IFASTBP_PROC::INVENTORY_SUMMARY_LIST );
   addFieldDetails( ifds::OrigFundUnits,              IFASTBP_PROC::INVENTORY_SUMMARY_LIST );
   addFieldDetails( ifds::Commissionable,             IFASTBP_PROC::INVENTORY_SUMMARY_LIST );
   addFieldDetails( ifds::RDRAdvice,                  IFASTBP_PROC::INVENTORY_SUMMARY_LIST );
   addFieldDetails( ifds::CommRate,                   IFASTBP_PROC::INVENTORY_SUMMARY_LIST );

   addFieldDetails( ifds::TraceNo,                    IFASTBP_PROC::INVENTORY_SUMMARY_LIST );
   addFieldDetails( ifds::MatureDate,                 IFASTBP_PROC::INVENTORY_SUMMARY_LIST );
   addFieldDetails( ifds::TaxJuris,                   IFASTBP_PROC::INVENTORY_SUMMARY_LIST );
   addFieldDetails( ifds::ReceiptStatus,              IFASTBP_PROC::INVENTORY_SUMMARY_LIST );
   addFieldDetails( ifds::ReceiptNumber,              IFASTBP_PROC::INVENTORY_SUMMARY_LIST );
   addFieldDetails( ifds::OriginalTotalUnits,         IFASTBP_PROC::INVENTORY_SUMMARY_LIST );
   addFieldDetails( ifds::UsedUnits,                  IFASTBP_PROC::INVENTORY_SUMMARY_LIST );

   addFieldDetails( ifds::SortBy,                     IFASTBP_PROC::INVENTORY_SUMMARY_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::SortOrder,                  IFASTBP_PROC::INVENTORY_SUMMARY_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::SortByColumn,               IFASTBP_PROC::INVENTORY_SUMMARY_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::InventorySummHeading,       IFASTBP_PROC::INVENTORY_SUMMARY_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::Grp1Shares,				  IFASTBP_PROC::INVENTORY_SUMMARY_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::Grp2Shares,				  IFASTBP_PROC::INVENTORY_SUMMARY_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::G1G2TrackType,			  IFASTBP_PROC::INVENTORY_SUMMARY_LIST,SUBCLASS_PROCESS );

   addFieldDetails( INV_SUMMARY::FUNDDESC,            IFASTBP_PROC::INVENTORY_SUMMARY_LIST, SUBCLASS_PROCESS );
   addFieldDetails( INV_SUMMARY::SEARCHFUNDDESC,      IFASTBP_PROC::INVENTORY_SUMMARY_LIST, SUBCLASS_PROCESS );

   // Account Holding fields
   addFieldDetails( ifds::rxFundCode,                 IFASTBP_PROC::ACCOUNT_HOLDINGS );
   addFieldDetails( ifds::rxClassCode,                IFASTBP_PROC::ACCOUNT_HOLDINGS );
  
   // General Account information.
   addFieldDetails( ifds::AccountNum,                 IFASTBP_PROC::MFACCOUNT );
   addFieldDetails( ifds::ShrNum,                     IFASTBP_PROC::MFACCOUNT );

   // Inventory Details List
   addFieldDetails( ifds::TransId,                    IFASTBP_PROC::INVENTORY_DETAILS_LIST );
   addFieldDetails( ifds::TransNum,                   IFASTBP_PROC::INVENTORY_DETAILS_LIST );
   addFieldDetails( ifds::TransType,                  IFASTBP_PROC::INVENTORY_DETAILS_LIST );
   addFieldDetails( ifds::TradeDate,                  IFASTBP_PROC::INVENTORY_DETAILS_LIST );
   addFieldDetails( ifds::SettleDate,                 IFASTBP_PROC::INVENTORY_DETAILS_LIST );
   addFieldDetails( ifds::Units,                      IFASTBP_PROC::INVENTORY_DETAILS_LIST );
   addFieldDetails( ifds::Rate,                       IFASTBP_PROC::INVENTORY_DETAILS_LIST );

   // Fund Master List
   addFieldDetails( ifds::FundCategory,               IFASTBP_PROC::FUND_MASTER_LIST );

   addFieldDetails( ifds::GroupOrigDate,			  IFASTBP_PROC::INVENTORY_SUMMARY_LIST); 
   addFieldDetails( ifds::DisplayRolloverQualificationDate, IFASTBP_PROC::INVENTORY_SUMMARY_LIST);
}

//******************************************************************************
// Destructor - Since accruals are not held in the repository, we need to delete
// the cbos when we are finish with them.
//******************************************************************************

InventorySummaryProcess::~InventorySummaryProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
/*
   _pInventorySummaryList = NULL;   
   _pMFAccount = NULL;
   _pAccountHoldingList = NULL;*/
}

//******************************************************************************
// Function which get the container pointer on demand.
// @param   const BFContainerId& idContainer - Id to the container.
//          const BFDataGroupId& idDataGroup - group id.
// @returns void.
//******************************************************************************

void *InventorySummaryProcess::getPtrForContainer( const BFContainerId& idContainer,
                                                  const BFDataGroupId& idDataGroup )
{
   void *ptr = NULL;
   SEVERITY sevRtn = NO_CONDITION;
   try
   {/*
      if( IFASTBP_PROC::INVENTORY_SUMMARY_LIST == idContainer )
      {
         ptr = _pInventorySummaryList;                  
      }
      else */
      if( IFASTBP_PROC::ACCOUNT_HOLDINGS == idContainer )
      {
         ptr = _pAccountHoldingList;
      }
      else if( IFASTBP_PROC::MFACCOUNT == idContainer )
      {
         ptr = _pMFAccount;          
      }
      else if( IFASTBP_PROC::INVENTORY_DETAILS_LIST == idContainer )
      {
         if( _pInventorySummaryList )
         {
            InventoryDetailsList *pInventoryDetailsList = NULL;
            DString dstrInvSummId;
            getField( this, IFASTBP_PROC::INVENTORY_SUMMARY_LIST, ifds::InvSummId, dstrInvSummId, false );  // Container will contain at least one empty item
            if( !dstrInvSummId.empty() )
            {
               InventorySummary *pInventorySummary = dynamic_cast< InventorySummary * >( getCBOItem(IFASTBP_PROC::INVENTORY_SUMMARY_LIST, idDataGroup ) );
               if( pInventorySummary->getInventoryDetailsList( pInventoryDetailsList, idDataGroup, dstrInvSummId, true ) <= WARNING )
               {
                  ptr = pInventoryDetailsList;
               }
            }
         }
      }
      else if( IFASTBP_PROC::FUND_MASTER_LIST == idContainer )
      {
         FundMasterList* pFundMasterList = NULL;
         DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
         dstcWorkSession->getMgmtCo().getFundMasterList( pFundMasterList );
         ptr = pFundMasterList;
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

void InventorySummaryProcess::doGetField( const GenericInterface *rpGICaller,
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
      const_cast <InventorySummaryProcess*> (this)->getField( rpGICaller, IFASTBP_PROC::INVENTORY_SUMMARY_LIST, 
                                                             ifds::FromFund, dstrFundCode, false);
      const_cast <InventorySummaryProcess*> (this)->getField( rpGICaller, IFASTBP_PROC::INVENTORY_SUMMARY_LIST, 
                                                             ifds::FromClass, dstrClassCode, false);
      DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      pDSTCWorkSession->GetFundNumber ( dstrFundCode, dstrClassCode, strValueOut );      
   }
   else if( idField == INV_SUMMARY::FUNDDESC )
   {
      DString dstrFundCode;
      const_cast <InventorySummaryProcess*> (this)->getField( rpGICaller, IFASTBP_PROC::INVENTORY_SUMMARY_LIST, 
                                                             ifds::FromFund, dstrFundCode, false);
      if( !dstrFundCode.empty() )
         _pFundMasterList->getFundName( dstrFundCode, strValueOut);
   }
   else if( idField == INV_SUMMARY::SEARCHFUNDDESC )
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
            _pFundMasterList->getFundName ( dstrFundCode, strValueOut);
         }
      }
   }
   else if( idField == ifds::UnitsTotal )
   {
      strValueOut =_pInventorySummaryList->getUnitsTotal();
   }
   else if( idField == ifds::TotalCBFFreeUnits )
   {
      strValueOut = _pInventorySummaryList->getTotalCBFreeUnits();
   }
   else if( idField == ifds::SortBy || idField == ifds::SortOrder || 
	        idField == ifds::SortByColumn || idField == ifds::Grp1Shares || 
		    idField == ifds::Grp2Shares )
   {
      _pInventorySummaryList->getField(idField,strValueOut,idDataGroup,bFormatted);
   }
   else if( idField == ifds::G1G2TrackType )
   {
		DString dstrFundClass, dstrFundCode, dstrClassCode;
		getParameter( INV_SUMMARY::FUNDCLASS, dstrFundClass );   
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
		if(!dstrFundCode.stripAll().empty() && !dstrClassCode.stripAll().empty())
   		{
      		FundDetailList *_pFundDetailList = NULL;
      		DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession*>(getBFWorkSession());
  			if(dstcWorkSession && (dstcWorkSession->getMgmtCo().getFundDetailList(_pFundDetailList) <= WARNING))
   			{	   
	  			FundDetail *pFundDetail = NULL;
   				if( _pFundDetailList && _pFundDetailList->getFundDetail(dstrFundCode, dstrClassCode, BF::HOST, pFundDetail))
   				{
					if(pFundDetail)
	  				pFundDetail->getField( ifds::G1G2TrackType, strValueOut, BF::HOST, false);
   				}  
   			}
   	    }
   }
}

//******************************************************************************
SEVERITY InventorySummaryProcess::doSetField( const GenericInterface *rpGICaller, 
                                              const BFContainerId& idContainer, 
                                              const BFFieldId& idField,
                                              const BFDataGroupId& idDataGroup, 
                                              const DString& strValue, 
                                              bool bFormatted ) 
{  
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doSetField") );   

   DSTCWorkSession* pWkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   if (idField == ifds::SortBy)  
   {
      _pInventorySummaryList->setField(idField,strValue,idDataGroup,bFormatted);
   }
   else if(idField == ifds::SortOrder)
   {
      _pInventorySummaryList->setField(idField,strValue,idDataGroup,bFormatted);
   }
   
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
const BFProperties *InventorySummaryProcess::doGetFieldAttributes ( const GenericInterface *rpGICaller, 
                                                                    const BFContainerId &idContainer, 
                                                                    const BFFieldId &idField, 
                                                                    const BFDataGroupId &idDataGroup)
{
   const BFProperties *pBFProperties = NULL;

   if (idContainer == IFASTBP_PROC::INVENTORY_SUMMARY_LIST && 
      ( idField == ifds::SortBy || idField == ifds::SortOrder || idField == ifds::InventorySummHeading) )
   {
      pBFProperties = 
         _pInventorySummaryList->getFieldProperties (idField, idDataGroup);
   }

   return pBFProperties;
}

//******************************************************************************
// Initializes all the search criteria cbos and accrual list cbos.
// @returns SEVERITY.
//******************************************************************************

SEVERITY InventorySummaryProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOINIT );

   try
   {
//    DString dstrFundCode, dstrClassCode;
      const BFDataGroupId& idDataGroup = getDataGroupId();
      getParameter( INV_SUMMARY::ACCOUNT_NUM, _dstrAccountNum );
      getParameter( INV_SUMMARY::FUND_CODE, _dstrFundCode );
      getParameter( INV_SUMMARY::CLASS_CODE, _dstrClassCode );

      DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      if( pDSTCWorkSession->getMFAccount( idDataGroup, _dstrAccountNum, _pMFAccount) <= WARNING && _pMFAccount )
      {
         _pMFAccount->getInventorySummaryList( _pInventorySummaryList, _dstrAccountNum, _dstrFundCode, _dstrClassCode, I_("N"), idDataGroup );
         if( _pInventorySummaryList )
         {
            setContainer( IFASTBP_PROC::INVENTORY_SUMMARY_LIST, _pInventorySummaryList );
         }
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

bool InventorySummaryProcess::doModelessChildComplete( const Command &cmd )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOMODELESSCHILDCOMPLETE );

   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_INVENTORY_SUMMARY );
}


//******************************************************************************
// @param   GenericInterface *rpGICaller - pointer to parent object.
// @return bool - true when successful, false otherwise.
//******************************************************************************

bool InventorySummaryProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );

   bool bRtn = false;
   try
   {
      assert( _rpChildGI && isValidModelessInterface( _rpChildGI ) );

      if( isValidModelessInterface( _rpChildGI ) )
      {  // Only if child still exists
         _pInventorySummaryList = NULL;   
         _pMFAccount = NULL;
         _pAccountHoldingList = NULL;

         const BFDataGroupId& idDataGroup = getDataGroupId();
         getParameter( INV_SUMMARY::ACCOUNT_NUM, _dstrAccountNum );
         getParameter( INV_SUMMARY::FUND_CODE, _dstrFundCode );
         getParameter( INV_SUMMARY::CLASS_CODE, _dstrClassCode );

         setContainer( IFASTBP_PROC::MFACCOUNT, NULL );
         setContainer( IFASTBP_PROC::INVENTORY_SUMMARY_LIST, NULL );
         setContainer( IFASTBP_PROC::ACCOUNT_HOLDINGS, NULL );

         DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
         if( pDSTCWorkSession->getMFAccount( idDataGroup, _dstrAccountNum, _pMFAccount) <= WARNING && _pMFAccount )
         {
            _pMFAccount->getInventorySummaryList( _pInventorySummaryList, _dstrAccountNum, _dstrFundCode, _dstrClassCode , I_("N"), idDataGroup );
            _pMFAccount->getAccountHoldingList( _pAccountHoldingList, idDataGroup );
         }
         pDSTCWorkSession->getMgmtCo().getFundMasterList( _pFundMasterList );
         setContainer( IFASTBP_PROC::MFACCOUNT, _pMFAccount);
         setContainer( IFASTBP_PROC::INVENTORY_SUMMARY_LIST, _pInventorySummaryList );
         setContainer( IFASTBP_PROC::ACCOUNT_HOLDINGS, _pAccountHoldingList);


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

E_COMMANDRETURN InventorySummaryProcess::doProcess()
{
   MAKEFRAME2( CND::IFASTBP_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter( INV_SUMMARY::FUND_CODE, _dstrFundCode );
      setParameter( INV_SUMMARY::CLASS_CODE, _dstrClassCode );
      rtn = invokeCommand( this, CMD_GUI_INVENTORY_SUMMARY, getProcessType(),
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

SEVERITY InventorySummaryProcess::performSearch( GenericInterface *rpGICaller, 
                                                const BFContainerId& idSearch, E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, PERFORMSEARCH );

   const BFDataGroupId& idDataGroup = getDataGroupId ();
   try
   {
      switch( eSearchAction )
      {
         case SEARCH_START:
            {
               DString dstrFundClass, dstrFundCode, dstrClassCode, dstrActiveOnly;
               getParameter( INV_SUMMARY::FUNDCLASS, dstrFundClass );
               getParameter( INV_SUMMARY::ACTIVEONLY, dstrActiveOnly );
               dstrActiveOnly = ( dstrActiveOnly.empty() ) ? I_("N") : dstrActiveOnly;

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
                  _pMFAccount->getInventorySummaryList( _pInventorySummaryList, _dstrAccountNum, dstrFundCode, dstrClassCode, dstrActiveOnly, getDataGroupId() );
               }
               if( _pInventorySummaryList )
                  setContainer ( IFASTBP_PROC::INVENTORY_SUMMARY_LIST, _pInventorySummaryList );
               else
                  setContainer ( IFASTBP_PROC::INVENTORY_SUMMARY_LIST, NULL );
               setContainer( IFASTBP_PROC::INVENTORY_DETAILS_LIST, NULL );    // Reset Container

            }
            break;
         case SEARCH_NEXT_BLOCK:
            {
               if (idSearch == IFASTBP_PROC::INVENTORY_SUMMARY_LIST)
               {
                  if (_pInventorySummaryList)
                  {
                     _pInventorySummaryList->getMore ();
                  }
               }
               else if (idSearch == IFASTBP_PROC::INVENTORY_DETAILS_LIST)
               {
                  InventoryDetailsList *pInventoryDetailsList = 
                        dynamic_cast <InventoryDetailsList *> (getCBOList (IFASTBP_PROC::INVENTORY_DETAILS_LIST, getDataGroupId ()));
                  
                  if (pInventoryDetailsList)
                  {
                     pInventoryDetailsList->getMore ();
                  }
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
   return(GETCURRENTHIGHESTSEVERITY()); 
}

//******************************************************************************
// @param   GenericInterface *rpGICaller - pointer to parent object.
//          in idSearch - Type of search is requested.
// @returns bool - true if there are more data
//                 false otherwise.
//******************************************************************************

bool InventorySummaryProcess::doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch )
{
   if (rpGICaller != NULL)
   {
      if (idSearch == IFASTBP_PROC::INVENTORY_SUMMARY_LIST)
      {
         return _pInventorySummaryList == NULL  ? false : _pInventorySummaryList->doMoreRecordsExist();
      }
      else if (idSearch == IFASTBP_PROC::INVENTORY_DETAILS_LIST)
      {
         InventoryDetailsList *pInventoryDetailsList = 
               dynamic_cast <InventoryDetailsList *> (getCBOList (IFASTBP_PROC::INVENTORY_DETAILS_LIST, getDataGroupId ()));
      
         return pInventoryDetailsList == NULL  ? false : pInventoryDetailsList->doMoreRecordsExist();
      }
   }
   return false;
}

//******************************************************************************
bool InventorySummaryProcess::doSend(GenericInterface *rpGICaller, const I_CHAR *szMessage ) 
{
   DString dstrMessage( szMessage );
   if( dstrMessage == I_("CLEAR DETAILS") )
   {
      setContainer( IFASTBP_PROC::INVENTORY_DETAILS_LIST, NULL );
      return( true );
   }
   return( false );
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/InventorySummaryProcess.cpp-arc  $
// 
//    Rev 1.12   May 29 2008 06:00:26   daechach
// PET0006862 Fn02 - Roll Over Qualification Period Enhancement
// 
//    Rev 1.11   06 Jan 2008 17:45:26   popescu
// Fixed the More button for the inventory details list
// 
//    Rev 1.10   Jul 14 2005 17:16:06   popescu
// Incident 357000 - fixed call of inventory screen from transaction history - make it modeless
// 
//    Rev 1.9   Nov 17 2004 15:18:50   popescu
// PET 1117/56, removed 'getField' method at the fund master list level, 
// 
//    Rev 1.8   Jun 08 2004 13:58:30   HERNANDO
// PET1046 FN01 - Passing Fund and Class codes.
// 
//    Rev 1.7   May 25 2004 20:11:08   HERNANDO
// PET1046 FN01 - Changed use of TotalCBFreeUnits.
// 
//    Rev 1.6   May 22 2004 16:19:16   HERNANDO
// PET1046 FN01 - Fix the fund description display (temporarily) until the rule is determined.  If no summary records, the fund description will be blank.  Before the change, a fund description is returned for a blank fund code.
// 
//    Rev 1.5   May 19 2004 17:43:48   HERNANDO
// PET1046 FN01 - Added LSIF/Inventory Details.
// 
//    Rev 1.4   May 06 2004 11:26:38   HERNANDO
// PET1046 FN01 - Added parameter to call to pMFAccount->getInventorySummaryList to include Active Only value.  (Checked in for compiling issues)
// 
//    Rev 1.3   Mar 10 2004 17:51:46   ZHANGCEL
// PET 1001 - FN01: fix crash when click F11
// 
//    Rev 1.1   Feb 26 2004 17:15:52   ZHANGCEL
// PET1001 - FN01 Added logic to cope with the UnitsTatol issue
// 
//    Rev 1.0   Feb 24 2004 10:27:20   ZHANGCEL
// Initial revision.
// 
//  
 */
