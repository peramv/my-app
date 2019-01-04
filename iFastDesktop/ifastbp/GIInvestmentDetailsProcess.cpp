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
// ^FILE   : GIInvestmentDetailsProcess.cpp
// ^CLASS  : GIInvestmentDetailsProcess
//
//******************************************************************************

#include "stdafx.h"
#include "giinvestmentdetailsprocess.hpp"
#include "giinvestmentdetailsprocessincludes.h"

#include <ifastcbo\progressiveintratelist.hpp>
#include <ifastcbo\trade.hpp>
#include <ifastcbo\worksessiontradeslist.hpp>
#include <ifastcbo\giinvestmentdetailslist.hpp>
#include <ifastcbo\giinvestmentdetails.hpp>

#include <ifastcbo\transfeelist.hpp>
#include <ifastcbo\transfee.hpp>


extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_GI_INVESTMENT_DETAILS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_GI_INVESTMENT_DETAILS;

#include <bfproc\concreteprocesscreator.hpp>

static ConcreteProcessCreator< GIInvestmentDetailsProcess > processCreator( CMD_BPROC_GI_INVESTMENT_DETAILS);

namespace 
{
   const I_CHAR *CLASSNAME = I_("GIInvestmentDetailsProcess");
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern CLASS_IMPORT const long ERR_GI_SELECTED_AMOUNT_NOT_TRADE_AMOUNT;
   extern CLASS_IMPORT const long ERR_NO_INVESTMENT_SETUP;
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
GIInvestmentDetailsProcess::GIInvestmentDetailsProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand ) 
, _rpChildGI( NULL )
, m_Caller (NULL_STRING)
, m_TradeListKey (NULL_STRING)
, m_accountNum (NULL_STRING)
,_readOnly(false)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer (IFASTBP_PROC::TRADE, false, BF::NullContainerId, true, I_("Trade"));
   addContainer (IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST, true, IFASTBP_PROC::TRADE, true, I_("INVESTMENT_DETAILS"));
   addContainer (IFASTBP_PROC::GI_SELECTED_INVESTMENTS_LIST, true,  IFASTBP_PROC::TRADE, false, I_("SELECTED_INVESTMENTS"));
}

//******************************************************************************
GIInvestmentDetailsProcess::~GIInvestmentDetailsProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   _rpChildGI = NULL;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************
SEVERITY GIInvestmentDetailsProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

   try
   {    
      getParameter (CALLER, m_Caller);
      getParameter (ACCOUNT_NUM, m_accountNum);
      getParameter (MFCAN_IP_PARAM::LIST_KEY, m_TradeListKey);

      addFieldDetails( ifds::Amount,            IFASTBP_PROC::TRADE);
      addFieldDetails( ifds::AmtType,           IFASTBP_PROC::TRADE);
      addFieldDetails( ifds::GrossOrNet,        IFASTBP_PROC::TRADE);
      addFieldDetails( ifds::RedemOrder,        IFASTBP_PROC::TRADE);

      addFieldDetails( ifds::IsInvSelected,     IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST);
      addFieldDetails( ifds::InvHisNumber,      IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST);
      addFieldDetails( ifds::InvHisDepDate,     IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST);
      addFieldDetails( ifds::InvHisMatDate,     IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST);
      addFieldDetails( ifds::InvHisIntRate,     IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST);
      addFieldDetails( ifds::InvHisPrincipal,   IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST);
      addFieldDetails( ifds::Principal,         IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST);
      addFieldDetails( ifds::InvHisCurMktVal,   IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST);
      addFieldDetails( ifds::ValueAtMaturity,   IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST);
      addFieldDetails( ifds::SelInvAmtType,     IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST);
      addFieldDetails( ifds::SelInvAmount,      IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST);
      addFieldDetails( ifds::PrincRedeemed,     IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST);
      addFieldDetails( ifds::AccruedInterest,   IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST);
      addFieldDetails( ifds::AdminFee,          IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST);
      addFieldDetails( ifds::MVA,               IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST);
      addFieldDetails( ifds::AmountNet,         IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST);

      addFieldDetails( ifds::PrincRedeemed,     IFASTBP_PROC::GI_SELECTED_INVESTMENTS_LIST);
      addFieldDetails( ifds::AccruedInterest,   IFASTBP_PROC::GI_SELECTED_INVESTMENTS_LIST);
      addFieldDetails( ifds::AdminFee,          IFASTBP_PROC::GI_SELECTED_INVESTMENTS_LIST);
      addFieldDetails( ifds::MVA,               IFASTBP_PROC::GI_SELECTED_INVESTMENTS_LIST);
      addFieldDetails( ifds::AmountNet,         IFASTBP_PROC::GI_SELECTED_INVESTMENTS_LIST);

      addFieldDetails( ifds::GIRedemInvSelectAmountType, IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST, SUBCLASS_PROCESS);




      const BFDataGroupId& idDataGroup = getDataGroupId();
      Trade *pTrade = dynamic_cast<Trade*> (getCBOItem(IFASTBP_PROC::TRADE, idDataGroup));
      //GIInvestmentDetailsList *pGIInvestmentDetailsList = dynamic_cast<GIInvestmentDetailsList*> 
      //                              (getCBOItem(IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST, idDataGroup));
      
      DString tradeAmount;
      DString tradeAmtType;
      DString grossNet;
      DString redemOrder;
      DString transType;


      pTrade->getField(ifds::Amount,      tradeAmount,   idDataGroup);
      pTrade->getField(ifds::AmtType,     tradeAmtType,  idDataGroup);
      pTrade->getField(ifds::GrossOrNet,  grossNet,      idDataGroup);
      pTrade->getField(ifds::RedemOrder,  redemOrder,    idDataGroup);
      pTrade->getField(ifds::TradesTransType, transType, idDataGroup);

		
      GIInvestmentDetailsList *pGIInvestmentDetailsList = 
         dynamic_cast<GIInvestmentDetailsList*> (getCBOList(IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST, idDataGroup));
      
      DString dstrGIRedemInvSelectAmountType;
      pGIInvestmentDetailsList->getField(ifds::GIRedemInvSelectAmountType, dstrGIRedemInvSelectAmountType, idDataGroup);
      
      if ( NULL != pGIInvestmentDetailsList && dstrGIRedemInvSelectAmountType == I_(""))
            pGIInvestmentDetailsList->changeAmtType(tradeAmtType, idDataGroup);

      pGIInvestmentDetailsList->setField(ifds::ReadOnly, I_("N"), idDataGroup, false);
      
      pGIInvestmentDetailsList->setFieldReadOnly(ifds::GIRedemInvSelectAmountType, idDataGroup, false);
      
      if(I_("FM") == redemOrder)
      {
         _readOnly = true;

		   if ( NULL != pGIInvestmentDetailsList )
         {
            pGIInvestmentDetailsList->setFieldReadOnly(ifds::GIRedemInvSelectAmountType, idDataGroup, true);
            pGIInvestmentDetailsList->setField(ifds::ReadOnly, I_("Y"), idDataGroup, false);
         }


      }
      
      if(I_("P") == tradeAmtType)
      {
         _readOnly = true;

		   if ( NULL != pGIInvestmentDetailsList )
         {
            pGIInvestmentDetailsList->setFieldReadOnly(ifds::GIRedemInvSelectAmountType, idDataGroup, true);
            pGIInvestmentDetailsList->setField(ifds::ReadOnly, I_("Y"), idDataGroup, false);
         }

      }

      if(I_("N") == grossNet)
      {
//         _readOnly = true;

		   if ( NULL != pGIInvestmentDetailsList )
         {
            pGIInvestmentDetailsList->changeAmtType( I_("D"), idDataGroup);
            pGIInvestmentDetailsList->setFieldReadOnly(ifds::GIRedemInvSelectAmountType, idDataGroup, true);
//            pGIInvestmentDetailsList->setField(ifds::ReadOnly, I_("Y"), idDataGroup, false);
         }

      }

      if(transType == TRADETYPE::TRANSFER)
      {
         pGIInvestmentDetailsList->setFieldReadOnly(ifds::GIRedemInvSelectAmountType, idDataGroup, true);
      }

      if(pTrade && pGIInvestmentDetailsList)
      {
         DString dstrAccountNum;
         DString dstrEffDate;
         DString dstrGrossNet;
         DString dstrRedemOrder;
         DString dstrSuppressMVA;
         DString dstrSuppressAdmin;

         TransFeeList* pTransFeeList = NULL;
         pTrade->getTransFeeList (pTransFeeList, idDataGroup); 
         TransFee *pMVATransFee = NULL;
         TransFee *pGIAdminTransFee = NULL;
         if(pTransFeeList)
         {
            pTransFeeList->getTransFee ( FEES::MVA,      pMVATransFee, idDataGroup);
            pTransFeeList->getTransFee ( FEES::GIADMIN,  pGIAdminTransFee, idDataGroup);    

            if(pMVATransFee)
               pMVATransFee->getField(ifds::FeeCharge, dstrSuppressMVA, idDataGroup);
            
            if(pGIAdminTransFee)
               pGIAdminTransFee->getField(ifds::FeeCharge, dstrSuppressAdmin, idDataGroup);

         }


         pTrade->getField(ifds::AccountNum,     dstrAccountNum,      idDataGroup);
         pTrade->getField(ifds::EffectiveDate,  dstrEffDate,         idDataGroup);
         pTrade->getField(ifds::GrossOrNet,     dstrGrossNet,        idDataGroup); 
         pTrade->getField(ifds::RedemOrder,     dstrRedemOrder,      idDataGroup); 

         pGIInvestmentDetailsList->setField(ifds::AccountNum,     dstrAccountNum,      idDataGroup, false);
         pGIInvestmentDetailsList->setField(ifds::EffectiveDate,  dstrEffDate,         idDataGroup, false);
         pGIInvestmentDetailsList->setField(ifds::GrossOrNet,     dstrGrossNet,        idDataGroup, false);
         pGIInvestmentDetailsList->setField(ifds::RedemOrder,     dstrRedemOrder,      idDataGroup, false);
         pGIInvestmentDetailsList->setField(ifds::SuppressMVA,    dstrSuppressMVA == I_("N") ? I_("Y") : I_("N"),     idDataGroup, false);
         pGIInvestmentDetailsList->setField(ifds::SuppressAdmin,  dstrSuppressAdmin == I_("N") ? I_("Y") : I_("N"),   idDataGroup, false);
         pGIInvestmentDetailsList->setField(ifds::TransType,      transType,           idDataGroup, false);
         pGIInvestmentDetailsList->setField(ifds::TradeAmount,    tradeAmount,         idDataGroup, false);
      }


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
bool GIInvestmentDetailsProcess::doModelessChildComplete( const Command &cmd )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_GI_INVESTMENT_DETAILS);
}

//******************************************************************************
E_COMMANDRETURN GIInvestmentDetailsProcess::doProcess()
{  
   MAKEFRAME2( CND::IFASTBP_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter (CALLER, m_Caller);   
      setParameter (ACCOUNT_NUM, m_accountNum);   
      rtn = invokeCommand( this, CMD_GUI_GI_INVESTMENT_DETAILS, PROC_NO_TYPE, isModal(), &_rpChildGI );
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
void *GIInvestmentDetailsProcess::getPtrForContainer( const BFContainerId& idContainer,
                                               const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_( "getPtrForContainer" ) );
   
   void *ptr = NULL;
   DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   try
   {

      if (IFASTBP_PROC::TRADE == idContainer)
      {
         if (m_Caller == I_("TradeEntry"))
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
      }
      else if(IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST ==  idContainer)
      {
         Trade *pTrade = 
               dynamic_cast<Trade*> (getCBOItem(IFASTBP_PROC::TRADE, idDataGroup));
         if( pTrade)
         {
            GIInvestmentDetailsList *pGIInvestmentDetailsList;
            pTrade->getGIInvestmentDetails(pGIInvestmentDetailsList, idDataGroup);
            ptr = pGIInvestmentDetailsList;
         }
      }
      else if(IFASTBP_PROC::GI_SELECTED_INVESTMENTS_LIST == idContainer)
      {
         Trade *pTrade = 
               dynamic_cast<Trade*> (getCBOItem(IFASTBP_PROC::TRADE, idDataGroup));
         if( pTrade)
         {
            GIInvestmentDetailsList *pGIInvestmentDetailsList;
            pTrade->getGIInvestmentTotals(pGIInvestmentDetailsList, idDataGroup);
            ptr = pGIInvestmentDetailsList;
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
void GIInvestmentDetailsProcess::doGetField ( const GenericInterface *rpGICaller,
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

   if ( idField == ifds::GIRedemInvSelectAmountType )
   {
      GIInvestmentDetailsList *pGIInvestmentDetailsList = 
         dynamic_cast<GIInvestmentDetailsList*> (const_cast <GIInvestmentDetailsProcess*> (this)->getCBOList(IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST, idDataGroup));

		if ( NULL != pGIInvestmentDetailsList )
			pGIInvestmentDetailsList->getField( ifds::GIRedemInvSelectAmountType, strValueOut, idDataGroup );
   }
}

//******************************************************************************
SEVERITY GIInvestmentDetailsProcess::doSetField( const GenericInterface *rpGICaller, 
                                         const BFContainerId &idContainer, 
                                         const BFFieldId &idField, 
                                         const BFDataGroupId &idDataGroup, 
                                         const DString &strValue, 
                                         bool bFormatted)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTBP_CONDITION, CLASSNAME, I_("doSetField"));

   if (idField == ifds::GIRedemInvSelectAmountType)
   {
      GIInvestmentDetailsList *pGIInvestmentDetailsList = 
         dynamic_cast<GIInvestmentDetailsList*> (getCBOList(IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST, idDataGroup));

		if ( NULL != pGIInvestmentDetailsList )
			pGIInvestmentDetailsList->setField( idField, strValue, idDataGroup, bFormatted );
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
const BFProperties *GIInvestmentDetailsProcess::doGetFieldAttributes ( const GenericInterface *rpGICaller, 
                                                           const BFContainerId &idContainer, 
                                                           const BFFieldId &idField, 
                                                           const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, CLASSNAME, DOGETFIELDATTRIBUTES);

   const BFProperties *pBFProperties = NULL;

   if (idField == ifds::GIRedemInvSelectAmountType)
   {
      GIInvestmentDetailsList *pGIInvestmentDetailsList = 
         dynamic_cast<GIInvestmentDetailsList*> (getCBOList(IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST, idDataGroup));

		if ( NULL != pGIInvestmentDetailsList )
         pBFProperties = pGIInvestmentDetailsList->getFieldProperties ( idField, idDataGroup);
   }

   return pBFProperties;
}


//******************************************************************************
bool GIInvestmentDetailsProcess::doOk (GenericInterface *rpGICaller)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_( "doOk" ) );
   
   const BFDataGroupId &idDataGroup = getDataGroupId ();

   Trade *pTrade = dynamic_cast <Trade*> (getCBOItem (IFASTBP_PROC::TRADE, idDataGroup));
   
   GIInvestmentDetailsList *pGIInvestmentDetailsList = 
      dynamic_cast<GIInvestmentDetailsList*> (getCBOList(IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST, idDataGroup));
   
   DString dstrReadOnly;
   pGIInvestmentDetailsList->getField(ifds::ReadOnly, dstrReadOnly, idDataGroup, false);

   if(dstrReadOnly == I_("N"))
   {
      calculateTotals();
      
      GIInvestmentDetailsList* pTotals = NULL;
      GIInvestmentDetails* pTotalsCBO = NULL;

      GIInvestmentDetailsList* pGIInvestmentDetailsList = NULL;
      pTrade->getGIInvestmentDetails (pGIInvestmentDetailsList, idDataGroup, false);

      pTrade->getGIInvestmentTotals (pTotals, idDataGroup);

      if(pTrade && pTotals && pGIInvestmentDetailsList)
      {
         BFObjIter totalsIter (*pTotals, idDataGroup, true);
         while (!totalsIter.end())
         {
            pTotalsCBO = dynamic_cast <GIInvestmentDetails*> (totalsIter.getObject());
            break;
         }
         if(pTotalsCBO)
         {
			DString tradeAmount;
			pTrade->getField(ifds::Amount, tradeAmount, idDataGroup, false);
			BigDecimal bdTradeAmount(tradeAmount);
		    if (bdTradeAmount == BIGDEC_ZERO )
			{
			   DString dstAmtType;
				pGIInvestmentDetailsList->getField(ifds::GIRedemInvSelectAmountType, dstAmtType, idDataGroup, false);
				DString dstSelInvAmount;
				if(dstAmtType == I_("D"))
                    pTotalsCBO->getField(ifds::SelInvAmount, dstSelInvAmount, idDataGroup, false);
				else
                    pTotalsCBO->getField(ifds::PrincRedeemed, dstSelInvAmount, idDataGroup, false);
				pTrade->setField(ifds::Amount, dstSelInvAmount, idDataGroup, false);
			}

         }
      }
   };

   return GETCURRENTHIGHESTSEVERITY () <= WARNING;
}


//*****************************************************************************
SEVERITY GIInvestmentDetailsProcess::doValidateAll ( BFAbstractCBO *rpWSD, 
                                              const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOVALIDATEALL);
   
   if (m_Caller == I_("TradeEntry"))
   {
      Trade *pTrade = 
         dynamic_cast <Trade*> (getCBOItem (IFASTBP_PROC::TRADE, idDataGroup));

      if (pTrade)
      {
         GIInvestmentDetailsList* pGIInvestmentDetailsList = NULL;
   
         pTrade->getGIInvestmentDetails(pGIInvestmentDetailsList, idDataGroup, false);

         if(pGIInvestmentDetailsList)
            pGIInvestmentDetailsList->validateAll (idDataGroup);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

SEVERITY GIInvestmentDetailsProcess::calculateTotals()
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOSEND);

   const BFDataGroupId &idDataGroup = getDataGroupId ();
   Trade *pTrade = dynamic_cast <Trade*> (getCBOItem (IFASTBP_PROC::TRADE, idDataGroup));
   DString tradeAmount;
   if(pTrade)
      pTrade->getField(ifds::TradeAmount, tradeAmount, idDataGroup, false);

   GIInvestmentDetailsList* pGIInvestmentDetailsList = NULL;
   GIInvestmentDetailsList* pTotals = NULL;
   
   pTrade->getGIInvestmentDetails(pGIInvestmentDetailsList, idDataGroup, false);
   pTrade->getGIInvestmentTotals(pTotals, idDataGroup);

   if(pTrade && pGIInvestmentDetailsList && pTotals)
   {
      pGIInvestmentDetailsList->calculateTotals(*pTotals, idDataGroup);
   }

   GIInvestmentDetails* pGIInvestmentDetails = 
      dynamic_cast <GIInvestmentDetails*> (getCBOItem (IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST, idDataGroup));
   
   pGIInvestmentDetails->calculateFees(idDataGroup);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool GIInvestmentDetailsProcess::doSend ( GenericInterface *rpGICaller,
                                   const I_CHAR  *szMessage)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOSEND);
   DString dstrMessage( szMessage );
   if(dstrMessage == I_("CalculateTotals"))
   {
      calculateTotals();
   }
   return GETCURRENTHIGHESTSEVERITY() <= WARNING;
}

//******************************************************************************
void GIInvestmentDetailsProcess::setCurrentListItem(const GenericInterface *rpGICaller,
               const BFContainerId& idList, const DString& strListItemKey)
{  
   TRACE_METHOD( CLASSNAME, I_( "setCurrentListItem" ) );

   const BFDataGroupId &idDataGroup = getDataGroupId ();
/*
   if( IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST == idList )
   {
      GIInvestmentDetails *pGIInvestmentDetails = dynamic_cast<GIInvestmentDetails*> (getCBOItem(IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST, idDataGroup));
      if(pGIInvestmentDetails && pGIInvestmentDetails->hasFieldsUpdateForGroup(idDataGroup.getId()))
      {
         Trade *pTrade = dynamic_cast <Trade*> (getCBOItem (IFASTBP_PROC::TRADE, idDataGroup));

         DString dstrAccountNum;
         DString dstrEffDate;
         DString dstrGrossNet; 
         DString dstrRedemOrder; 
         DString dstrSuppressMVA = I_("N"); 
         DString dstrSuppressAdmin = I_("N");

         pTrade->getField(ifds::AccountNum,     dstrAccountNum,   idDataGroup, false);
         pTrade->getField(ifds::EffectiveDate,  dstrEffDate,      idDataGroup, false);
         pTrade->getField(ifds::GrossOrNet,     dstrGrossNet,     idDataGroup, false); 
         pTrade->getField(ifds::RedemOrder,     dstrRedemOrder,   idDataGroup, false); 
         //pTrade->getField(ifds::SuppressMVA; 
         //pTrade->getField(ifds::SuppressAdmin;

         pGIInvestmentDetails->calculate(dstrAccountNum, dstrEffDate, dstrGrossNet, dstrRedemOrder, dstrSuppressMVA, 
                                          dstrSuppressAdmin, idDataGroup);
      }
   }
  */ 
   AbstractProcess::setCurrentListItem(rpGICaller, idList, strListItemKey);
   return;
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/GIInvestmentDetailsProcess.cpp-arc  $
// 
//    Rev 1.14   Jun 08 2012 14:06:08   jankovii
// IN 2957854 - P0186477_FN05_03_Same transno. in distrib-delt to be used & changes to misc-info
// 
//    Rev 1.13   May 16 2012 11:18:36   if991250
// IN2951488 - GI Money out
// 
//    Rev 1.12   May 01 2012 09:24:06   if991250
// GI Money Out - clearing the calculated amounts when the Investment row is unselected.
// 
//    Rev 1.11   Apr 17 2012 11:00:50   if991250
// Showing Principat instead of InvHisPrincipal in Trade, GIInvest
// 
//    Rev 1.10   Mar 21 2012 16:11:50   if991250
// IN 2885623 - GI Money Out - Error handling
// 
//    Rev 1.9   Mar 20 2012 16:40:24   if991250
// IN 2885623 - GI Money Oout
// 
//    Rev 1.8   Mar 15 2012 17:56:12   if991250
// IN 2879297: Money Out
// 
//    Rev 1.7   Mar 12 2012 18:10:24   if991250
// GI Money Out
// 
//    Rev 1.6   Mar 09 2012 17:44:48   if991250
// GIInvestmentDetails
// 
//    Rev 1.5   Mar 08 2012 17:45:58   if991250
// GI Money Out
// 
//    Rev 1.4   Mar 08 2012 09:56:40   if991250
// GI Money Out
// 
//    Rev 1.3   Feb 17 2012 10:34:28   if991250
// GI Investment
// 
//    Rev 1.2   Jan 16 2012 15:41:38   if991250
// GI Investment Details
// 
//    Rev 1.1   Jan 12 2012 12:07:30   if991250
// fix GIInvestmentDetailsProcess.cpp
// 
//    Rev 1.0   Jan 12 2012 10:19:32   jankovii
// Initial revision.
 * 
*/