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
//    Copyright 2011 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : EstateAllocationProcess.cpp
// ^CLASS  : EstateAllocationProcess
//
//******************************************************************************

#include "stdafx.h"
#include "estateallocationprocess.hpp"
#include "estateallocationprocessincludes.h"

#include <ifastcbo\progressiveintratelist.hpp>
#include <ifastcbo\trade.hpp>
#include <ifastcbo\worksessiontradeslist.hpp>
#include <ifastcbo\estateallocationlist.hpp>
#include <ifastcbo\estateallocation.hpp>

#include <ifastcbo\transfeelist.hpp>
#include <ifastcbo\transfee.hpp>
#include <ifastcbo\transactionlist.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\transactiondetails.hpp>
#include <ifastcbo\accountentityxref.hpp>
#include <ifastcbo\accountentityxrefobject.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_ESTATE_ALLOCATION;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ESTATE_ALLOCATION;

#include <bfproc\concreteprocesscreator.hpp>

static ConcreteProcessCreator< EstateAllocationProcess > processCreator( CMD_BPROC_ESTATE_ALLOCATION);

namespace 
{
   const I_CHAR *CLASSNAME = I_("EstateAllocationProcess");
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern CLASS_IMPORT const long ERR_GI_SELECTED_AMOUNT_NOT_TRADE_AMOUNT;
}

namespace TRADE_VALIDATION_GROUP
{
   extern CLASS_IMPORT const long GIA_ATTRIB;
}

namespace FEES
{
   extern CLASS_IMPORT const I_CHAR * MVA;
   extern CLASS_IMPORT const I_CHAR * GIADMIN;
}

namespace ifds
{
   extern CLASS_IMPORT const BFDecimalFieldId ProgressiveIntRate;
   extern CLASS_IMPORT const BFNumericFieldId ProgressiveInvTerm;
   extern CLASS_IMPORT const BFDateFieldId GIMaturityDate;
   extern CLASS_IMPORT const BFDateFieldId InvestDate;
   extern CLASS_IMPORT const BFDateFieldId MaturDate;
   extern CLASS_IMPORT const BFDecimalFieldId InterestRate;
   extern CLASS_IMPORT const BFDecimalFieldId Principal;
   extern CLASS_IMPORT const BFDecimalFieldId MktValue;
   extern CLASS_IMPORT const BFDecimalFieldId ValueAtMaturity;
   extern CLASS_IMPORT const BFDecimalFieldId AccruedInterest;

//   extern CLASS_IMPORT const BFNumericFieldId Selected;
   extern CLASS_IMPORT const BFDecimalFieldId AdminFee;
   extern CLASS_IMPORT const BFTextFieldId AmountType;
   extern CLASS_IMPORT const BFDecimalFieldId PrincRedeemed;
   extern CLASS_IMPORT const BFDecimalFieldId InvHisMVA;
   extern CLASS_IMPORT const BFDecimalFieldId AmountNet;
   extern CLASS_IMPORT const BFTextFieldId GIRedemInvSelectAmountType;
   extern CLASS_IMPORT const BFTextFieldId ReadOnly;
   extern CLASS_IMPORT const BFTextFieldId FeeCharge;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFTextFieldId Address;

   extern CLASS_IMPORT const BFNumericFieldId EntityId;
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
   extern CLASS_IMPORT const BFTextFieldId EntityType;
   extern CLASS_IMPORT const BFNumericFieldId SeqNumber;
}
namespace TRADETYPE
{
   extern CLASS_EXPORT I_CHAR * const EXCHANGE;
   extern CLASS_IMPORT I_CHAR * const REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const TRANSFER;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
EstateAllocationProcess::EstateAllocationProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand ) 
, _rpChildGI( NULL )
, m_Caller (NULL_STRING)
, m_TradeListKey (NULL_STRING)
, m_accountNum (NULL_STRING)
,_readOnly(false)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer (IFASTBP_PROC::TRADE, false, BF::NullContainerId, true, I_("Trade"));
   addContainer (IFASTBP_PROC::ESTATE_ALLOCATION, true, IFASTBP_PROC::TRADE, true, I_("EstateAllocation"));
}

//******************************************************************************
EstateAllocationProcess::~EstateAllocationProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   _rpChildGI = NULL;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************
SEVERITY EstateAllocationProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

   try
   {    

      DString dstrEstateAllocationCurrentKey;

      getParameter (MFCAN_IP_PARAM::CALLER, m_Caller);
      getParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, m_accountNum);
//      getParameter (MFCAN_IP_PARAM::TRANS_ID, m_TransId);
      getParameter (MFCAN_IP_PARAM::LIST_KEY, m_TradeListKey);

      getParameter (MFCAN_IP_PARAM::SUB_LIST_KEY, dstrEstateAllocationCurrentKey);

      if(m_Caller == I_("TransHist"))
         _readOnly = true;

      addFieldDetails( ifds::Amount,            IFASTBP_PROC::TRADE);
      addFieldDetails( ifds::AmtType,           IFASTBP_PROC::TRADE);

      addFieldDetails( ifds::BenefEntityID,      IFASTBP_PROC::ESTATE_ALLOCATION);
      addFieldDetails( ifds::BenefName,          IFASTBP_PROC::ESTATE_ALLOCATION);
      addFieldDetails( ifds::BenefPrcnt,         IFASTBP_PROC::ESTATE_ALLOCATION);
      addFieldDetails( ifds::BenefAmount,        IFASTBP_PROC::ESTATE_ALLOCATION);
      addFieldDetails( ifds::BenefUnits,         IFASTBP_PROC::ESTATE_ALLOCATION);
      addFieldDetails( ifds::BenefAddrLevel,     IFASTBP_PROC::ESTATE_ALLOCATION);
      addFieldDetails( ifds::BenefAddrCode,      IFASTBP_PROC::ESTATE_ALLOCATION);
      addFieldDetails( ifds::Address,            IFASTBP_PROC::ESTATE_ALLOCATION);

      addFieldDetails( ifds::ShrNum,             IFASTBP_PROC::ESTATE_ALLOCATION, SUBCLASS_PROCESS );
      addFieldDetails( ifds::EntityType,         IFASTBP_PROC::ESTATE_ALLOCATION, SUBCLASS_PROCESS );
      addFieldDetails( ifds::SeqNumber,          IFASTBP_PROC::ESTATE_ALLOCATION, SUBCLASS_PROCESS );
      addFieldDetails( ifds::ReadOnly,           IFASTBP_PROC::ESTATE_ALLOCATION, SUBCLASS_PROCESS );

   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      throw EXCEPTIONFROMFILE( CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool EstateAllocationProcess::doModelessChildComplete( const Command &cmd )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_ESTATE_ALLOCATION);
}

//******************************************************************************
E_COMMANDRETURN EstateAllocationProcess::doProcess()
{  
   MAKEFRAME2( CND::IFASTBP_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter (CALLER, m_Caller);   
      setParameter (ACCOUNT_NUM, m_accountNum);   
      rtn = invokeCommand( this, CMD_GUI_ESTATE_ALLOCATION, PROC_NO_TYPE, isModal(), &_rpChildGI );
   }
   catch( ConditionException &ce )
   {
      assert( 0 );
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return( rtn );
}
//******************************************************************************
void *EstateAllocationProcess::getPtrForContainer( const BFContainerId& idContainer,
                                               const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_( "getPtrForContainer" ) );
   
   void *ptr = NULL;
   DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   try
   {

      if (IFASTBP_PROC::TRADE == idContainer)
      {
         if (m_Caller == I_("Trade"))
         {
            WorksessionTradesList *pTradesList (NULL);

            if( pDSTCWorkSession->getTradesList (pTradesList, idDataGroup) <= WARNING && 
                pTradesList)
            {
               BFObjIter iter (*pTradesList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

               iter.positionByKey (m_TradeListKey);
               if (!iter.end())
               {
                  ptr = dynamic_cast <Trade*>(iter.getObject());
               }
            }
         }
         else if(m_Caller == I_("TransHist"))
         {
            MFAccount* pMFAccount = NULL;
            pDSTCWorkSession->getMFAccount(idDataGroup, m_accountNum, pMFAccount);
            TransactionList *pTransactionList;
            pMFAccount->getLastActiveTransactionHistoryList( pTransactionList, idDataGroup);
            if (pTransactionList)
            {
               BFObjIter iter (*pTransactionList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

               iter.positionByKey (m_TradeListKey);
               if (!iter.end())
               {
                  ptr = dynamic_cast <TransactionDetails*>(iter.getObject());
               }
            }

         }

      }
      else if(IFASTBP_PROC::ESTATE_ALLOCATION == idContainer)
      {
         if(m_Caller == I_("Trade"))
         {
            Trade *pTrade = dynamic_cast<Trade*> (getCBOItem(IFASTBP_PROC::TRADE, idDataGroup));
            EstateAllocationList* pEstateAllocationList = NULL;
            pTrade->getEstateAllocationList ( pEstateAllocationList, idDataGroup);
            if(pEstateAllocationList)
               ptr = pEstateAllocationList;
         }
         else if(m_Caller == I_("TransHist"))
         {
            TransactionDetails* pTransactionDetails = dynamic_cast<TransactionDetails*> 
               (getCBOItem(IFASTBP_PROC::TRADE, idDataGroup));
            EstateAllocationList* pEstateAllocationList = NULL;
            pTransactionDetails->getEstateAllocationList ( pEstateAllocationList, idDataGroup, true);
            if(pEstateAllocationList)
               ptr = pEstateAllocationList;
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
   return ptr;  
}

//******************************************************************************
void EstateAllocationProcess::doGetField ( const GenericInterface *rpGICaller,
                                        const BFContainerId &idContainer,
                                        const BFFieldId &idField,
                                        const BFDataGroupId &idDataGroup, 
                                        DString &strValueOut,
                                        bool bFormatted) const
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           I_("doGetField"));   

   strValueOut = NULL_STRING;
   if (idField == ifds::ShrNum)
   {
      MFAccount *pMFAccount = NULL;
      DSTCWorkSession* pDSTCWorkSession = dynamic_cast<DSTCWorkSession *> (getBFWorkSession ());
      pDSTCWorkSession->getMFAccount(idDataGroup, m_accountNum, pMFAccount); 
      DString dstrShrNum;
      pMFAccount->getField( ifds::ShrNum, dstrShrNum, idDataGroup, false);
      strValueOut = dstrShrNum;
   }
   else if(idField == ifds::EntityType || idField == ifds::SeqNumber) 
   {
      DSTCWorkSession* pDSTCWorkSession = dynamic_cast<DSTCWorkSession *> (getBFWorkSession ());
      EstateAllocation* pEstateAllocation = dynamic_cast<EstateAllocation*> 
         (const_cast<EstateAllocationProcess*> (this)->getCBOItem(IFASTBP_PROC::ESTATE_ALLOCATION, idDataGroup));
     
      DString dstrBenefEntityID;
      pEstateAllocation->getField(ifds::BenefEntityID, dstrBenefEntityID, idDataGroup, false);

      AccountEntityXref* pAccountEntityXrefOut = NULL;
      pDSTCWorkSession->getAccountEntityXref(idDataGroup, pAccountEntityXrefOut);
      
      ACCTENTITYOBJ_VECTOR vBenefEntities;
      pAccountEntityXrefOut->getBeneficiaries(vBenefEntities, m_accountNum, idDataGroup);
      ACCTENTITYOBJ_VECTOR::iterator iter = vBenefEntities.begin();
      while(iter != vBenefEntities.end())
      {
         DString dstrEntityId;
         (*iter)->getField (ifds::EntityId, dstrEntityId, idDataGroup, false);
         if(dstrBenefEntityID == dstrEntityId)
         {
            DString dstrValue;
            (*iter)->getField (idField, dstrValue, idDataGroup, false);
            strValueOut = dstrValue;
            break;
         }
      }
   }
   else if(idField == ifds::ReadOnly) 
   {
      strValueOut = _readOnly ? I_("Y") :  I_("N");
   }
   
}

//******************************************************************************
SEVERITY EstateAllocationProcess::doSetField( const GenericInterface *rpGICaller, 
                                         const BFContainerId &idContainer, 
                                         const BFFieldId &idField, 
                                         const BFDataGroupId &idDataGroup, 
                                         const DString &strValue, 
                                         bool bFormatted)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTBP_CONDITION, CLASSNAME, I_("doSetField"));

   if (idField == ifds::GIRedemInvSelectAmountType)
   {
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
const BFProperties *EstateAllocationProcess::doGetFieldAttributes ( const GenericInterface *rpGICaller, 
                                                           const BFContainerId &idContainer, 
                                                           const BFFieldId &idField, 
                                                           const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, CLASSNAME, DOGETFIELDATTRIBUTES);

   const BFProperties *pBFProperties = NULL;

   if (idField == ifds::GIRedemInvSelectAmountType)
   {
   }

   return pBFProperties;
}


//******************************************************************************
bool EstateAllocationProcess::doOk (GenericInterface *rpGICaller)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_( "doOk" ) );
   
   if(m_Caller == I_("Trade"))
   {
      const BFDataGroupId &idDataGroup = getDataGroupId ();

      Trade *pTrade = dynamic_cast <Trade*> (getCBOItem (IFASTBP_PROC::TRADE, idDataGroup));
      
      EstateAllocationList* pEstateAllocationList = NULL;
      pTrade->getEstateAllocationList (pEstateAllocationList, idDataGroup);
      //if(pEstateAllocationList)
      //{
      //   DString dstrTotalBenefAmount;
      //   pEstateAllocationList->getBenefAmount(idDataGroup, dstrTotalBenefAmount);
      //   pTrade->setField(ifds::Amount, dstrTotalBenefAmount, idDataGroup);
      //}
   }
   return GETCURRENTHIGHESTSEVERITY () <= WARNING;
}


//*****************************************************************************
SEVERITY EstateAllocationProcess::doValidateAll ( BFAbstractCBO *rpWSD, 
                                              const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOVALIDATEALL);
   
   if (m_Caller == I_("Trade"))
   {
      Trade *pTrade = 
         dynamic_cast <Trade*> (getCBOItem (IFASTBP_PROC::TRADE, idDataGroup));

      if (pTrade)
      {
         EstateAllocationList* pEstateAllocationList = NULL;
   
         pTrade->getEstateAllocationList(pEstateAllocationList, idDataGroup, false);

         if(pEstateAllocationList)
            pEstateAllocationList->validateAll (idDataGroup);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
bool EstateAllocationProcess::doSend ( GenericInterface *rpGICaller,
                                   const I_CHAR  *szMessage)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOSEND);
   DString dstrMessage( szMessage );
   if(I_("RefereshAddress") == dstrMessage)
   {
      BFDataGroupId idDataGroup = getDataGroupId();
      EstateAllocation* pEstateAllocation = dynamic_cast<EstateAllocation*> 
         (const_cast<EstateAllocationProcess*> (this)->getCBOItem(IFASTBP_PROC::ESTATE_ALLOCATION, idDataGroup));
      pEstateAllocation->updateAddress(idDataGroup);

   }
   return GETCURRENTHIGHESTSEVERITY() <= WARNING;
}

//******************************************************************************
void EstateAllocationProcess::setCurrentListItem(const GenericInterface *rpGICaller,
               const BFContainerId& idList, const DString& strListItemKey)
{  
   TRACE_METHOD( CLASSNAME, I_( "setCurrentListItem" ) );

   const BFDataGroupId &idDataGroup = getDataGroupId ();
   AbstractProcess::setCurrentListItem(rpGICaller, idList, strListItemKey);
   return;
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/EstateAllocationProcess.cpp-arc  $
// 
//    Rev 1.0   25 Jul 2012 15:27:22   if991250
// Initial revision.
// 
*/