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
//    Copyright 1997 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : DilutionProcess.cpp
// ^AUTHOR :  
// ^DATE   : 02/20/2005
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : DilutionProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"

#include "DilutionProcess.hpp"
#include "DilutionProcessincludes.h"
#include "mfcaninterprocparam.hpp"
#include <confirmationprocessincludes.h>
#include "TransCancelProcessIncludes.h"

#include <ifastcbo\DilutionAlloclist.hpp>
#include <ifastcbo\DilutionAlloc.hpp>
#include <ifastcbo\BulkCancellist.hpp>
#include <ifastcbo\BulkCancel.hpp>
#include <ifastcbo\TransCancellist.hpp>
#include <ifastcbo\TransCancel.hpp>
#include <ifastcbo\trade.hpp>
#include <ifastcbo\worksessiontradeslist.hpp>

#include <ifastdataimpl\dse_dstc0339_vw.hpp>
#include <ifastdataimpl\dse_dstc0339_vwRepeat_Record.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_DILUTION;
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_DILUTION;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< DilutionProcess > processCreator( CMD_BPROC_DILUTION );


namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "DilutionProcess" );

   const I_CHAR *Y               = I_( "Y" );
   const I_CHAR *N               = I_( "N" );
   
   const I_CHAR *pTRANSNUM       = I_( "TransNum" );
   const I_CHAR *pTRANSID        = I_( "TransId" );
   const I_CHAR *pFROMSCREEN     = I_( "FromScr" );   
   const I_CHAR *TRANSACTION     = I_( "Transaction" );
   const I_CHAR *VERIFIED        = I_("02");
   const I_CHAR *ACCOUNTABLE     = I_("Accountable");
   const I_CHAR *BACKDATEDREASON = I_("BackDatedReason");
   const I_CHAR *pLISTKEY        = I_("List_Key");
   const I_CHAR *pALLOW_MODIFY   = I_("AllowModify");
   const I_CHAR *SPLITDILUTION   = I_( "IsSplitDilution" );   
   const I_CHAR *SETTLENETWORK	 = I_("SettleNetwork");
   const I_CHAR *DILUTIONLINKNUM = I_("DilutionLinkNum");
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId TranStatus;
   extern CLASS_IMPORT const BFTextFieldId ModPermission;
   extern CLASS_IMPORT const BFTextFieldId ReadOnly;
	extern CLASS_IMPORT const BFTextFieldId IsDilutionNSMEligible;
	extern CLASS_IMPORT const BFTextFieldId IsNetworkSettleEligible;
	extern CLASS_IMPORT const BFDateFieldId ProcessDate;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId Username;
   extern CLASS_IMPORT const BFDateFieldId ModDate;
   extern CLASS_IMPORT const BFTextFieldId ModUser;
   extern CLASS_IMPORT const BFTextFieldId ShowExSysDilPymtNSM;
   extern CLASS_IMPORT const BFTextFieldId ShowDilution;
   extern CLASS_IMPORT const BFTextFieldId DilutionLinkNum;
   extern CLASS_IMPORT const BFTextFieldId MatchingKey;
}

namespace UAF
{
   //extern CLASS_IMPORT I_CHAR * const TRANSACTION_CANCELATION;
   //extern CLASS_IMPORT I_CHAR * const TRANSACTION_CANCELATION_VERIFICATION;
}

namespace MFCAN_IP_PARAM
{
   extern const I_CHAR * const CALLER;
}

namespace AUDITTYPE
{
   extern CLASS_IMPORT I_CHAR * const DILUTION_ALLOC;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319DilutionProcess::DilutionProcess() : 
DilutionProcess::DilutionProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pTransCancel( NULL )
, _pBulkCancel( NULL )
, _pDilutionList( NULL )
, _rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   
   addContainer( IFASTBP_PROC::DILUTION_LIST, true, BF::NullContainerId, true, I_("DilutionList") );
	
   addFieldDetails( ifds::Accountable,     IFASTBP_PROC::DILUTION_LIST );
   addFieldDetails( ifds::AllocPercent,    IFASTBP_PROC::DILUTION_LIST );
   addFieldDetails( ifds::RespDate,        IFASTBP_PROC::DILUTION_LIST );
   addFieldDetails( ifds::BackDatedReason, IFASTBP_PROC::DILUTION_LIST );
   addFieldDetails( ifds::AssociatedAcctNum,IFASTBP_PROC::DILUTION_LIST );
   addFieldDetails( ifds::BillingToEntity,  IFASTBP_PROC::DILUTION_LIST );
   addFieldDetails( ifds::InterCode,       IFASTBP_PROC::DILUTION_LIST );
   addFieldDetails( ifds::BillingToEntityType,IFASTBP_PROC::DILUTION_LIST );
   addFieldDetails( ifds::ExSysDilPymtNSM,      IFASTBP_PROC::DILUTION_LIST );
   addFieldDetails( ifds::ShowExSysDilPymtNSM,  IFASTBP_PROC::DILUTION_LIST );
   addFieldDetails( ifds::ShowDilution,         IFASTBP_PROC::DILUTION_LIST );

   addFieldDetails( ifds::Username,             IFASTBP_PROC::DILUTION_LIST );
   addFieldDetails( ifds::ProcessDate,          IFASTBP_PROC::DILUTION_LIST );
   addFieldDetails( ifds::ModDate,              IFASTBP_PROC::DILUTION_LIST );
   addFieldDetails( ifds::ModUser,              IFASTBP_PROC::DILUTION_LIST );
   addFieldDetails( ifds::TransId,              IFASTBP_PROC::DILUTION_LIST );
   addFieldDetails( ifds::SplitAccCodeRID,      IFASTBP_PROC::DILUTION_LIST );
   addFieldDetails( ifds::DilVersion,           IFASTBP_PROC::DILUTION_LIST );
   addFieldDetails( ifds::ReadOnly,        IFASTBP_PROC::DILUTION_LIST, SUBCLASS_PROCESS );
 
   
   addFieldDetails( ifds::RefundPayType,	IFASTBP_PROC::DILUTION_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::RefundOption,		IFASTBP_PROC::DILUTION_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::RefundAmount,		IFASTBP_PROC::DILUTION_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::DilutionAmount,	IFASTBP_PROC::DILUTION_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::RefundFXRate,		IFASTBP_PROC::DILUTION_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::RefundCurrency,	IFASTBP_PROC::DILUTION_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::DilutionAvail,	IFASTBP_PROC::DILUTION_LIST, SUBCLASS_PROCESS );
   
   addFieldDetails( ifds::SettleNetwork,	IFASTBP_PROC::DILUTION_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::DilutionNSM,		IFASTBP_PROC::DILUTION_LIST );
   addFieldDetails( ifds::IsNetworkSettleEligible, IFASTBP_PROC::DILUTION_LIST, SUBCLASS_PROCESS);
   addFieldDetails( ifds::IsDilutionNSMEligible, IFASTBP_PROC::DILUTION_LIST,  SUBCLASS_PROCESS);
   addFieldDetails( ifds::DilutionLinkNum,	IFASTBP_PROC::DILUTION_LIST,  SUBCLASS_PROCESS );
   addFieldDetails( ifds::MatchingKey,	IFASTBP_PROC::DILUTION_LIST,  SUBCLASS_PROCESS );
 }

//******************************************************************************
DilutionProcess::~DilutionProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   _rpChildGI = NULL;
}

//******************************************************************************
void DilutionProcess::doGetField( const GenericInterface *rpGICaller,
                                  const BFContainerId& idContainer,
                                  const BFFieldId& idField,
                                  const BFDataGroupId& idDataGroup,
                                  DString &strValueOut,
                                  bool bFormatted ) const
{  
	if( idField == ifds::ReadOnly )
    {
		strValueOut = N;
		if( _FromScreen == TRANSACTION ) 	
			strValueOut = N;
		else
		{
            if( _FromScreen == I_( "TransCancel" ) &&
				_dstrBulkCancel == I_( "Y" ) &&
				_pBulkCancel )
			{
				DString dstrTranStatus, dstrModPerm;
				_pBulkCancel->getField( ifds::ReadOnly, strValueOut, idDataGroup );
			}
			else if( _pTransCancel )
			{
				DString dstrTranStatus, dstrModPerm;
				_pTransCancel->getField( ifds::ReadOnly, strValueOut, idDataGroup );
			}
		}		
    }
	
	if (idContainer == IFASTBP_PROC::DILUTION_LIST && 
         ( idField == ifds::RefundPayType ||
           idField == ifds::RefundOption || 
           idField == ifds::RefundAmount || 
           idField == ifds::DilutionAmount || 
           idField == ifds::RefundFXRate || 
           idField == ifds::RefundCurrency || 
           idField == ifds::DilutionAvail ||
		   idField == ifds::SettleNetwork ||
		   idField == ifds::DilutionLinkNum ||
		   idField == ifds::MatchingKey
         ))
    {
      if (_pDilutionList)
      {
   		_pDilutionList->getField (idField, strValueOut, idDataGroup, bFormatted);
	  }
   }

	if (idContainer == IFASTBP_PROC::DILUTION_LIST && 
	   (idField == ifds::IsDilutionNSMEligible || idField == ifds::IsNetworkSettleEligible))
	{
		if (_pDilutionList)
		{
			_pDilutionList->refreshNSMEligibility(idField, idDataGroup);
			if(idField == ifds::IsNetworkSettleEligible) 
			{
				_pDilutionList->getField (ifds::IsNetworkSettleEligible, strValueOut, idDataGroup, bFormatted);
			}
			else if (idField == ifds::IsDilutionNSMEligible)
			{
				for(BFObjIter iter (*_pDilutionList, idDataGroup, false, BFObjIter::NON_DELETED);
					!iter.end();
					++iter)
				{
					DilutionAlloc * pDilutionAlloc = dynamic_cast<DilutionAlloc*>(iter.getObject());
					if(pDilutionAlloc)
					{
						pDilutionAlloc->getField (ifds::IsDilutionNSMEligible, strValueOut, idDataGroup, bFormatted);
					}
				}
			}
		}
	}
}

//****************************************************************************** shashi
SEVERITY DilutionProcess::doGetErrors ( const GenericInterface *rpGICaller,
                                        const BFContainerId &idContainer,
                                        const BFFieldId &idField,
                                        const BFDataGroupId &idDataGroup,
                                        CONDITIONVECTOR &conditions) const
{  
   SEVERITY sevRtn = NO_CONDITION;

    if (idContainer == IFASTBP_PROC::DILUTION_LIST)
	{
		 if (_pDilutionList)
		 {
			if (idField == ifds::RefundPayType ||
				idField == ifds::RefundOption || 
				idField == ifds::RefundAmount || 
				idField == ifds::DilutionAmount || 
				idField == ifds::RefundFXRate || 
				idField == ifds::RefundCurrency || 
				idField == ifds::DilutionAvail ||
				idField == ifds::SettleNetwork ||
				idField == ifds::DilutionLinkNum ||
				idField == ifds::MatchingKey)
			{
            sevRtn = _pDilutionList->getErrors ( idField, 
                                                 idDataGroup, 
                                                 conditions);
         }
      }
   }

   return sevRtn;   
}

//****************************************************************************** shashi
bool DilutionProcess::doRegisterObserver ( const GenericInterface *rpGICaller,
                                            const BFContainerId &idContainer,
                                            const BFFieldId &idField,
                                            const BFDataGroupId &idDataGroup,
                                            BFObserver &rpObserver) 
{
   bool bRegistered = false;

   if (idContainer == IFASTBP_PROC::DILUTION_LIST)
   {
      if ( idField == ifds::RefundPayType ||
           idField == ifds::RefundOption || 
           idField == ifds::RefundAmount || 
           idField == ifds::DilutionAmount || 
           idField == ifds::RefundFXRate || 
           idField == ifds::RefundCurrency || 
           idField == ifds::DilutionAvail ||
		   idField == ifds::SettleNetwork ||
		   idField == ifds::DilutionLinkNum ||
		   idField == ifds::MatchingKey)
      {
        
         if (_pDilutionList)
         {
            bRegistered = _pDilutionList->registerObserver ( idField, 
                                                                idDataGroup, 
                                                                &rpObserver, 
                                                                FIELD_NOTIFICATIONS, 
                                                                E_EVENT_ALL);
         }
      }
   }
   return bRegistered;
}

//****************************************************************************** shashi
const BFProperties *DilutionProcess::doGetFieldAttributes ( const GenericInterface *rpGICaller, 
                                                            const BFContainerId &idContainer, 
                                                            const BFFieldId &idField, 
                                                            const BFDataGroupId &idDataGroup)
{
   const BFProperties *pBFProperties = NULL;

   if (idContainer == IFASTBP_PROC::DILUTION_LIST)
   {
		if (_pDilutionList)
		{
		if (idField == ifds::RefundPayType ||
			idField == ifds::RefundOption || 
			idField == ifds::RefundAmount || 
			idField == ifds::DilutionAmount || 
			idField == ifds::RefundFXRate || 
			idField == ifds::RefundCurrency || 
			idField == ifds::DilutionAvail ||
			idField == ifds::SettleNetwork ||
			idField == ifds::DilutionLinkNum ||
			idField == ifds::MatchingKey)
		{
         pBFProperties = _pDilutionList->getFieldProperties (idField, idDataGroup);
		}
      }
   }
   return pBFProperties;
}

//******************************************************************************
SEVERITY DilutionProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      DString cashDivPaidAfter;
      getParameter( pTRANSNUM,                        _TransNum);
	  getParameter( pTRANSID,                         _TransId);
      getParameter( pFROMSCREEN,                      _FromScreen);
      getParameter( TRANSCANCEL::CASH_DIV_PAID_AFTER, cashDivPaidAfter );
	  getParameter( I_("TRANSTYPE"),         _dstrTransType );     // Cancellation sets it in CAPS
	  if (_dstrTransType == NULL_STRING)      // TransactionHistoryDlg sets it differently
		  getParameter( I_("TransType"),         _dstrTransType);

	  if (_dstrTransType == NULL_STRING)      // it might come form Trade Entry screen, which has Dilution button
		  getParameter( I_("TransType4Dilution"), _dstrTransType);

      _TransNum.stripAll();

	  getParameter( pALLOW_MODIFY, _dstrAllowModify );
	  
	       // Bulk support
      if ( 0 == _TransNum.asInteger() )
	  {
			getParameter( TRANSCANCEL::BULK_CANCEL, _dstrBulkCancel );
	  }
	 
	  getParameter( TRANSCANCEL::TRADE_DATE,  _dstrTradeDate );
	  getParameter( TRANSCANCEL::FUND,        _dstrFund );
	  getParameter( TRANSCANCEL::CLASS,       _dstrClass );
	  _dstrBulkCancel.stripAll().upperCase();

      getParameter( I_( "TransTradeDate" ),  _dstrTransTradeDate );
	  getParameter( I_( "TransSettleDate" ), _dstrTransSettleDate );

	  DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
	  if ( NULL != dstcWorkSession )
	  {
		if( _FromScreen == I_( "TransCancel" ) )
		{				               
			TransCancellist *pTransCancellist = NULL;
			BulkCancellist *pBulkCancellist = NULL;
			if ( _dstrBulkCancel != I_( "Y" ) &&
				 dstcWorkSession->getTransCancellist( pTransCancellist, 
													 _TransNum,
			 										 cashDivPaidAfter, 
													 getDataGroupId(),
													 _dstrTradeDate,
													 _dstrFund,
													 _dstrClass,
													 I_( "" ),    // Search Type
													 I_( "" ),    // TransStatus
													 I_( "" ),    // AdjustType
													 I_( "" ),    // Trade Adjust ID
													 _dstrTransSettleDate,
													 _dstrTransType
													 ) <= WARNING &&
				NULL != pTransCancellist )
			{		  
        DString dstrTransId;
        pTransCancellist->getField (ifds::TransId, dstrTransId, getDataGroupId(), false);
				BFObjIter iter ( *pTransCancellist, 
								getDataGroupId(), 
								false, 
								BFObjIter::ITERTYPE::NON_DELETED );               

				if (!iter.end ())
				{
					_pTransCancel = dynamic_cast <TransCancel*> (iter.getObject() );
				}

				if ( NULL != _pTransCancel )
				{
					_pTransCancel->getDilutionAllocList( getDataGroupId(), _pDilutionList );   

					DString dstrReadOnly, dstrSettleNetwork;
					_pTransCancel->getField (ifds::ReadOnly,  dstrReadOnly, BF::HOST);
					_pDilutionList->setField( ifds::ReadOnly, dstrReadOnly, BF::HOST, false );

          DilutionAllocList* pDilutionAllocListClone = NULL; 
          if(dstcWorkSession->getTransHistDilutionAllocList(dstrTransId, pDilutionAllocListClone, getDataGroupId(), _dstrTradeDate, _dstrTransSettleDate, _TransNum) <= WARNING)
          {
            pDilutionAllocListClone->getField(ifds::SettleNetwork, dstrSettleNetwork, getDataGroupId(), false);
            if(dstrSettleNetwork == I_("FSRV"))
            {
              DString dstrIsSettleNetworkEligible;
              _pDilutionList->refreshIsSettleNetworkEligible(dstrIsSettleNetworkEligible, BF::HOST);
              _pDilutionList->setField(ifds::IsNetworkSettleEligible, dstrIsSettleNetworkEligible, BF::HOST);
              _pDilutionList->setField(ifds::SettleNetwork, dstrSettleNetwork, BF::HOST, false);
            }
          }
				}			
			}
			else if ( dstcWorkSession->getBulkCancellist( pBulkCancellist,
															getDataGroupId(),
															_dstrTradeDate,
															_dstrFund,
															_dstrClass ) <= WARNING &&
						NULL != pBulkCancellist )					
			{			
	            
				BFObjIter iter ( *pBulkCancellist, 
								getDataGroupId(), 
								false, 
								BFObjIter::ITERTYPE::NON_DELETED );               
				if (!iter.end ())
				{
					_pBulkCancel = dynamic_cast <BulkCancel*> (iter.getObject() );
				}
				
				if ( NULL != _pBulkCancel )
				{
					_pBulkCancel->getDilutionAllocList( getDataGroupId(), _pDilutionList );   

					DString dstrReadOnly;
					_pBulkCancel->getField (ifds::ReadOnly,  dstrReadOnly, BF::HOST);
					_pDilutionList->setField( ifds::ReadOnly, dstrReadOnly, BF::HOST, false );
				}
			}  	     	 
		}
		else if( _FromScreen == I_("TradeEntry"))
		{	
				WorksessionTradesList *pTradesList = NULL;

				if( dstcWorkSession->getTradesList(pTradesList, getDataGroupId()) <= WARNING
					&& pTradesList)
				{
					BFObjIter iter( *pTradesList, getDataGroupId(), false, BFObjIter::ITERTYPE::NON_DELETED );
					
					getParameter (MFCAN_IP_PARAM::LIST_KEY, _ListKey);
					iter.positionByKey (_ListKey);

					if( !iter.end())            
					{
						Trade* pTrade = dynamic_cast <Trade*>(iter.getObject());

						if (pTrade)
						{
							pTrade->getDilutionAllocList (_pDilutionList, getDataGroupId());
						}
					}										
				}
		}
		else      // TransHist Dilution
		{				
			if ( dstcWorkSession->getTransHistDilutionAllocList( _TransId, 
				                                                 _pDilutionList, 
																 getDataGroupId(),
																 _dstrTransTradeDate,
																 _dstrTransSettleDate,
                                                 _TransNum) <= WARNING )
			{
				_pDilutionList->setField( ifds::ReadOnly, N, BF::HOST, false );
			}
		}
	  }

	  if (GETCURRENTHIGHESTSEVERITY() <=  WARNING && _pDilutionList)
	  {
		  setContainer (IFASTBP_PROC::DILUTION_LIST, _pDilutionList);
	  }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      throw EXCEPTIONFROMFILE(// CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
                              CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
E_COMMANDRETURN DilutionProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter( pTRANSID,      _TransId );
      setParameter( pFROMSCREEN,   _FromScreen );
	  setParameter( pALLOW_MODIFY, _dstrAllowModify );
	  setParameter( I_("TransType"), _dstrTransType );

      rtn = invokeCommand( this, 
		                   CMD_GUI_DILUTION, 
						   PROC_NO_TYPE, 
						   isModal(),
                           &_rpChildGI );
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      throw EXCEPTIONFROMFILE(// CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
                              CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(rtn);
}

//******************************************************************************
SEVERITY DilutionProcess::doSetField( const GenericInterface *rpGICaller,
                                      const BFContainerId& idContainer,
                                      const BFFieldId& idField,
                                      const BFDataGroupId& idDataGroup,
                                      const DString& strValue,
                                      bool bFormatted )
{  
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, CLASSNAME, I_("doSetField"));
	
   SEVERITY sevRtn = NO_CONDITION;
   
   if (idContainer == IFASTBP_PROC::DILUTION_LIST )
	{
		 if (_pDilutionList)
		 {
			if (idField == ifds::RefundPayType ||
				idField == ifds::RefundOption || 
				idField == ifds::RefundAmount || 
				idField == ifds::DilutionAmount || 
				idField == ifds::RefundFXRate || 
				idField == ifds::RefundCurrency || 
				idField == ifds::DilutionAvail ||
				idField == ifds::SettleNetwork ||
				idField == ifds::DilutionLinkNum ||
				idField == ifds::MatchingKey)
			{
				sevRtn = _pDilutionList->setField (idField, strValue, idDataGroup, bFormatted, false);
			}
		 }
   }
   return sevRtn;
}

//******************************************************************************
void *DilutionProcess::getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
   void *ptr = NULL;
   SEVERITY sevRtn = NO_CONDITION;

   try
   {
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

//*****************************************************************************
bool DilutionProcess::doOk (GenericInterface *rpGICaller)
{
	if ( _FromScreen != I_( "TransCancel" ) &&
		 _FromScreen != I_( "TradeEntry") )
	{
		setParameter (CONFPROC::PARM_CALLED_FROM, I_("TransHistDilution"));
	}
	return true;

}

//******************************************************************************
void DilutionProcess::doPostOk (GenericInterface *rpGICaller, bool bSuccessFlag)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("doPostOk"));

	if (bSuccessFlag)
   {
      DString accountable,
		      backDatedReason,
			  splitDilution,
			  settleNetwork,
			  dilutionLinkNum;

      //Incindent# 524855
      //if the dilution is modified in trans history screen - list is blown away in worksession for refresh 
      if (_FromScreen != I_("Transaction")) 
      {
         //check if only one record, setparameter Accountable and BackDatedReason
         //if >=2 records, then set accountable and BackDatedReason parameters to be empty.	   
         BFObjIter iter (*_pDilutionList, getDataGroupId(), true, BFObjIter::ITERTYPE::NON_DELETED);	   
         int numOfItem = iter.getNumberOfItemsInList();
         
         if (numOfItem == 1)
         {
            iter.getObject()->getField (ifds::Accountable, accountable, getDataGroupId ());
            iter.getObject()->getField (ifds::BackDatedReason, backDatedReason, getDataGroupId ());
         }
		 else if (numOfItem > 1)
		 {
			 splitDilution = I_("Yes");
		 }
         _pDilutionList->getField(ifds::SettleNetwork, settleNetwork, getDataGroupId());
         _pDilutionList->getField(ifds::DilutionLinkNum, dilutionLinkNum, getDataGroupId());

      }

      setParameter (ACCOUNTABLE, accountable);
      setParameter (BACKDATEDREASON, backDatedReason);
      setParameter (SPLITDILUTION, splitDilution);
	  setParameter (SETTLENETWORK, settleNetwork);
	  setParameter (DILUTIONLINKNUM, dilutionLinkNum);
   }
}

//**********************************************************************
SEVERITY DilutionProcess::doValidateAll(BFAbstractCBO *rpWSD, 
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("doValidateAll"));

   if ( _pDilutionList )
		_pDilutionList->validateAll (idDataGroup);
         
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool DilutionProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_DILUTION );
}

//******************************************************************************
bool DilutionProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   
   bool bRtn = false; 

   getParameter( pTRANSNUM,   _TransNum);
   getParameter( pTRANSID,    _TransId);
   getParameter( pFROMSCREEN, _FromScreen);   
   _TransNum.stripAll();

   getParameter( pALLOW_MODIFY, _dstrAllowModify );

   // Bulk support
   if ( 0 == _TransNum.asInteger() )
   {
		getParameter( TRANSCANCEL::BULK_CANCEL, _dstrBulkCancel );
   }
	 
   getParameter( TRANSCANCEL::TRADE_DATE,  _dstrTradeDate );
   getParameter( TRANSCANCEL::FUND,        _dstrFund );
   getParameter( TRANSCANCEL::CLASS,       _dstrClass );
   getParameter( I_( "TransSettleDate" ),  _dstrTransSettleDate );
   getParameter( I_( "TransTradeDate" ),   _dstrTransTradeDate );
   _dstrBulkCancel.stripAll().upperCase();


   if( isValidModelessInterface( _rpChildGI ) )
   {  // Only if child still exists
      bRtn = _rpChildGI->refresh( this, NULL );
      bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
   }

   return(bRtn);
}

//******************************************************************************
SEVERITY DilutionProcess::getHistoricalParameters ( const BFContainerId &idContainer, 
                                                        BFFieldId &recordIdField, 
                                                        DString &tableId, 
                                                        DString &dstrKeys) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           GETHISTORICALPARAMETERS);

   DString dstrTransId,
      keyStringIDI; 

   getField(this,idContainer,ifds::TransId,dstrTransId,false);
   dstrTransId.strip().upperCase();

   if (idContainer == IFASTBP_PROC::DILUTION_LIST)
   {
      recordIdField = ifds::SplitAccCodeRID;
      tableId = AUDITTYPE::DILUTION_ALLOC;
      addIDITagValue(keyStringIDI, I_("TransId"), dstrTransId);
      dstrKeys = keyStringIDI;
   }
   else 
   {
      assert(0);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DilutionProcess::getHistoricalParameters ( const BFContainerId& idContainer,
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
/* $Log:   Y:/VCS/BF iFAST/ifastbp/DilutionProcess.cpp-arc  $
// 
//    Rev 1.23   May 11 2012 15:18:58   wp040027
// PETP0187485-CPF-Dilution
// 
//    Rev 1.22   Nov 02 2007 11:26:52   jankovii
// IN #1057653 - trade cancellation using split dilution.
// 
//    Rev 1.21   Aug 30 2007 15:16:24   jankovii
// PET 2360 FN11 & IN #990810 - Dilution.
// 
//    Rev 1.20   Mar 10 2006 14:00:18   porteanm
// Incident 563764 - TradeDate/SettleDate validation support for a cancelled transaction.
// 
//    Rev 1.19   Jan 24 2006 12:36:44   popescu
// Incident# 524855 - enable 'refresh' button on confirmation dialog screen after dilution is modified
// 
//    Rev 1.18   Jan 09 2006 17:15:26   porteanm
// Incident 424704 - gap - TranshistDilutionAlloc update support.
// 
//    Rev 1.17   Dec 18 2005 14:50:50   porteanm
// Incident 421704 - gap - TranshistDilutionAlloc update support.
// 
//    Rev 1.16   Dec 16 2005 20:48:40   porteanm
// Incident 421704 - gap - TranshistDilutionAlloc update support.
// 
//    Rev 1.15   Dec 14 2005 11:12:00   porteanm
// Incident 421704 - gap - TranshistDilutionAlloc update support.
// 
//    Rev 1.14   Dec 13 2005 19:33:42   porteanm
// Incident 421704 - gap - TranshistDilutionAlloc update support.
// 
//    Rev 1.13   Nov 26 2005 16:31:30   porteanm
// PET 1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.12   Nov 13 2005 15:57:56   porteanm
// PET 1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.11   Oct 18 2005 14:18:22   AGUILAAM
// IN 432022 - allow single dilution record (100%); validateall on dilution only
// 
//    Rev 1.10   Sep 15 2005 18:07:16   popescu
// Incident# 388632 - trans cancel screen code overhaul
// 
//    Rev 1.9   Jul 11 2005 20:13:16   AGUILAAM
// PET1235_FN01: dilution, part of Rebook/Cancellation
// 
//    Rev 1.8   Jul 08 2005 09:37:50   Yingbaol
// PET1235,FN01:cancellation rebook
// 
//    Rev 1.7   Jul 07 2005 12:17:20   AGUILAAM
// PET1235 : dilution, part of Rebook/Cancellation
// 
//    Rev 1.6   Jun 15 2005 14:48:42   ZHANGCEL
// Incident #322193 - Add logic to set RvCode into BackDatedReason fields
// 
//    Rev 1.5   Jun 01 2005 15:51:34   ZHANGCEL
// Incident #323301 and #322193 : Change ReasonCode to BackDatedReason
// 
//    Rev 1.4   Mar 16 2005 15:46:16   Fengyong
// PET1190 FN05 - change view 337 to repeatable
// 
//    Rev 1.3   Mar 08 2005 13:40:10   Fengyong
// PET1190 FN04 - Readonly relate change
// 
//    Rev 1.2   Mar 07 2005 14:05:42   Fengyong
// PET1190FN04 - Add AccountableCode rules
// 
//    Rev 1.1   Mar 04 2005 17:06:50   Fengyong
// PET1190 FN04 - TransCancel Tempery check in for other coder
// 
//    Rev 1.0   Mar 03 2005 18:57:02   Fengyong
// Initial revision.
 */
