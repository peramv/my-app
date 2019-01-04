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
// FILE   : RDSPTransfersProcess.cpp
// AUTHOR : 
// DATE   : 
//
// -----------------------------------------------------------------------------
//
// CLASS  : RDSPTransfersProcess
//			This class manages the RDSP Transfer information.
//
// MEMBER VARIABLES :
//
// CODING COMMENTS  :
//
//******************************************************************************
//ifastbp
#include "stdafx.h"
#include "rdsptransfersprocess.hpp"
#include <ifastbp\rdsptransfersprocessincludes.h>
#include <ifastcbo\trade.hpp>
#include <ifastcbo\rdsptransfer.hpp>
#include <ifastcbo\worksessiontradeslist.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_RDSP_TRANSFER;
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_RDSP_TRANSFER;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< RDSPTransfersProcess > processCreator(CMD_BPROC_RDSP_TRANSFER);

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME             = I_( "RDSPTransfersProcess" ); 
   const I_CHAR * const TRADE_DATE     = I_( "EffectiveDate" );  
   const I_CHAR * const TRANSFER_LIKE  = I_( "TR,AFTR" ); 
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
	extern CLASS_IMPORT const BFNumericFieldId AccountNum;
	extern CLASS_IMPORT const BFTextFieldId GrantAmountNA;
	extern CLASS_IMPORT const BFTextFieldId ExtAccount;
	extern CLASS_IMPORT const BFTextFieldId ExtSpecimenPlanNo;
	extern CLASS_IMPORT const BFDecimalFieldId NontaxContrib;
	extern CLASS_IMPORT const BFDecimalFieldId Rollovers;
	extern CLASS_IMPORT const BFDecimalFieldId CDSGrant;
	extern CLASS_IMPORT const BFDecimalFieldId CDSBond;
	extern CLASS_IMPORT const BFDecimalFieldId CurrYrFMV;
	extern CLASS_IMPORT const BFDecimalFieldId PrevYrGrantBond;
	extern CLASS_IMPORT const BFDecimalFieldId PrevYrContrib;
	extern CLASS_IMPORT const BFDecimalFieldId PrevYrNonTaxRedAmt;
	extern CLASS_IMPORT const BFDecimalFieldId PrevYrTaxRedAmt;
	extern CLASS_IMPORT const BFDecimalFieldId CurrYrNonTaxRedAmt;
	extern CLASS_IMPORT const BFDecimalFieldId CurrYrTaxRedAmt;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
RDSPTransfersProcess::RDSPTransfersProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL )
, m_Caller (NULL_STRING)
, m_TradeListKey (NULL_STRING)
, m_RDSPTransListKey (NULL_STRING)
, m_AccountNum (NULL_STRING)
, m_DecimalDigits (NULL_STRING)
, m_TransType (NULL_STRING)
, m_DepositType (NULL_STRING)
, m_RedCode (NULL_STRING)
, _pRDSPTransfer( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer ( IFASTBP_PROC::TRADE, false, BF::NullContainerId, false, I_("Trade"));   
   addContainer ( IFASTBP_PROC::RDSP_TRANSFER, false, BF::NullContainerId, true, I_("RDSPTransfer"));

   addFieldDetails( ifds::AccountNum,			IFASTBP_PROC::RDSP_TRANSFER);
   addFieldDetails( ifds::GrantAmountNA,		IFASTBP_PROC::RDSP_TRANSFER);
   addFieldDetails( ifds::ExtAccount,			IFASTBP_PROC::RDSP_TRANSFER);
   addFieldDetails( ifds::ExtSpecimenPlanNo,	IFASTBP_PROC::RDSP_TRANSFER);   
   addFieldDetails( ifds::NontaxContrib,		IFASTBP_PROC::RDSP_TRANSFER);
   addFieldDetails( ifds::Rollovers,			IFASTBP_PROC::RDSP_TRANSFER);
   addFieldDetails( ifds::CDSGrant,				IFASTBP_PROC::RDSP_TRANSFER);
   addFieldDetails( ifds::CDSBond,				IFASTBP_PROC::RDSP_TRANSFER);
   addFieldDetails( ifds::CurrYrFMV,			IFASTBP_PROC::RDSP_TRANSFER);
   addFieldDetails( ifds::PrevYrGrantBond,		IFASTBP_PROC::RDSP_TRANSFER);
   addFieldDetails( ifds::PrevYrContrib,		IFASTBP_PROC::RDSP_TRANSFER);
   addFieldDetails( ifds::PrevYrNonTaxRedAmt,	IFASTBP_PROC::RDSP_TRANSFER);
   addFieldDetails( ifds::PrevYrTaxRedAmt,		IFASTBP_PROC::RDSP_TRANSFER);
   addFieldDetails( ifds::CurrYrNonTaxRedAmt,	IFASTBP_PROC::RDSP_TRANSFER);
   addFieldDetails( ifds::CurrYrTaxRedAmt,		IFASTBP_PROC::RDSP_TRANSFER);

   getParameter (CALLER, m_Caller);
}

//******************************************************************************
RDSPTransfersProcess::~RDSPTransfersProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   _pRDSPTransfer = NULL; 
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

//******************************************************************************
SEVERITY RDSPTransfersProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

   getParameter (ACCOUNT_NUM, m_AccountNum);
   getParameter (TRADE_LIST_KEY, m_TradeListKey); 
   getParameter (DECIMAL_DIGITS, m_DecimalDigits);
   getParameter (TRANS_TYPE, m_TransType);
   getParameter (DEPOSIT_TYPE, m_DepositType);
   getParameter (RED_CODE, m_RedCode); 

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool RDSPTransfersProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_RDSP_TRANSFER);
}

//******************************************************************************
bool RDSPTransfersProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{
   // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );

   bool bRtn = false;

   try
   {
      getParameter (CALLER, m_Caller);
      getParameter (ACCOUNT_NUM, m_AccountNum);
      getParameter (TRADE_LIST_KEY, m_TradeListKey);     
      getParameter (DECIMAL_DIGITS, m_DecimalDigits);   
      getParameter (TRANS_TYPE, m_TransType);
      getParameter (DEPOSIT_TYPE, m_DepositType);
      getParameter (RED_CODE, m_RedCode);	 

      setContainer (IFASTBP_PROC::RDSP_TRANSFER, NULL);

      if (isValidModelessInterface (_rpChildGI))
      {  // Only if child still exists
         bRtn = _rpChildGI->refresh (this, NULL);
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
void RDSPTransfersProcess::doGetField ( const GenericInterface *rpGICaller,
                                        const BFContainerId &idContainer,
                                        const BFFieldId &idField,
                                        const BFDataGroupId &idDataGroup, 
                                        DString &strValueOut,
                                        bool bFormatted) const
{
   if (idContainer == IFASTBP_PROC::RDSP_TRANSFER)
   {
      RDSPTransfer *pRDSPTransfer = dynamic_cast <RDSPTransfer *> (const_cast<RDSPTransfersProcess*> (this)->getCBOItem (IFASTBP_PROC::RDSP_TRANSFER, idDataGroup));

	  if (pRDSPTransfer)
	  {        
		  pRDSPTransfer->getField (idField, strValueOut, idDataGroup, bFormatted);        
	  }
   }
}

//******************************************************************************
SEVERITY RDSPTransfersProcess::doSetField ( const GenericInterface *rpGICaller, 
                                            const BFContainerId &idContainer, 
                                            const BFFieldId &idField,
                                            const BFDataGroupId &idDataGroup, 
                                            const DString &strValue, 
                                            bool bFormatted) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, CLASSNAME, I_("doSetField"));

   if (idContainer == IFASTBP_PROC::RDSP_TRANSFER)
   {
      RDSPTransfer *pRDSPTransfer = dynamic_cast <RDSPTransfer *> (getCBOItem (IFASTBP_PROC::RDSP_TRANSFER, idDataGroup));

	  if (pRDSPTransfer)
	  {        
		  pRDSPTransfer->setField (idField, strValue, idDataGroup, bFormatted, false);                 
	  }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
const BFProperties *RDSPTransfersProcess::doGetFieldAttributes ( const GenericInterface *rpGICaller, 
                                                                 const BFContainerId &idContainer, 
                                                                 const BFFieldId &idField, 
                                                                 const BFDataGroupId &idDataGroup)
{
	const BFProperties *pBFProperties = NULL;

	if (idContainer == IFASTBP_PROC::RDSP_TRANSFER)
	{
		RDSPTransfer *pRDSPTransfer = dynamic_cast <RDSPTransfer *> (getCBOItem (IFASTBP_PROC::RDSP_TRANSFER, idDataGroup));

		if (pRDSPTransfer)
		{        
			pBFProperties = pRDSPTransfer->getFieldProperties (idField, idDataGroup);
		}
	}

	return pBFProperties;
}

//******************************************************************************
SEVERITY RDSPTransfersProcess::doGetErrors ( const GenericInterface *rpGICaller,
                                             const BFContainerId &idContainer,
                                             const BFFieldId &idField,
                                             const BFDataGroupId &idDataGroup,
                                             CONDITIONVECTOR &conditions) const
{  
	SEVERITY sevRtn = NO_CONDITION;

	if (idContainer == IFASTBP_PROC::RDSP_TRANSFER)
	{
		RDSPTransfer *pRDSPTransfer = dynamic_cast <RDSPTransfer *> (const_cast<RDSPTransfersProcess*> (this)->getCBOItem (IFASTBP_PROC::RDSP_TRANSFER, idDataGroup));

		if (pRDSPTransfer)
		{         
			sevRtn = pRDSPTransfer->getErrors ( idField, idDataGroup, conditions);         
		}
	}

	return sevRtn;   
}

//******************************************************************************
E_COMMANDRETURN RDSPTransfersProcess::doProcess()
{
	MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
	E_COMMANDRETURN rtn = CMD_FAILURE;

	setParameter (ACCOUNT_NUM, m_AccountNum);
	setParameter (CALLER, m_Caller);
	setParameter (DECIMAL_DIGITS, m_DecimalDigits);	
	setParameter (TRANS_TYPE, m_TransType);
	setParameter (DEPOSIT_TYPE, m_DepositType);
	setParameter (RED_CODE, m_RedCode);	

	DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

	try
	{
		rtn = invokeCommand( this, CMD_GUI_RDSP_TRANSFER, getProcessType(), isModal(), &_rpChildGI );		
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

	return(rtn);
}

//******************************************************************************
void *RDSPTransfersProcess::getPtrForContainer( const BFContainerId& idContainer,
                                                const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "getPtrForContainer" ) );

   void *ptr = NULL;
   DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   try
   {
	   if (IFASTBP_PROC::TRADE == idContainer)
	   {
		   if (m_Caller == I_("TradeEntry"))
		   {
			   WorksessionTradesList *pTradesList (NULL);

			   if( pDSTCWorkSession->getTradesList (pTradesList, idDataGroup) <= WARNING && pTradesList)
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
	   else if (IFASTBP_PROC::RDSP_TRANSFER == idContainer)
	   {
		   if (m_Caller == I_("TradeEntry"))
		   {
			   Trade *pTrade = dynamic_cast <Trade*> (getCBOItem (IFASTBP_PROC::TRADE, idDataGroup));

			   if (pTrade)
			   {
				   RDSPTransfer *pRDSPTransfer = NULL;

				   if (pTrade->getRDSPTransfer (pRDSPTransfer, idDataGroup) <= WARNING && pRDSPTransfer)
				   {
					   ptr = pRDSPTransfer;
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
	   THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(ptr);
}

//******************************************************************************
SEVERITY RDSPTransfersProcess::doValidateAll ( BFAbstractCBO *rpWSD, 
											   const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTBP_CONDITION, CLASSNAME, DOVALIDATEALL);

	RDSPTransfer *pRDSPTransfer = dynamic_cast <RDSPTransfer *> (getCBOItem (IFASTBP_PROC::RDSP_TRANSFER, idDataGroup));

	if (pRDSPTransfer)
	{
		pRDSPTransfer->validateAll (idDataGroup);
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool RDSPTransfersProcess::doOk (GenericInterface *rpGICaller)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_( "doOk" ) );

	return GETCURRENTHIGHESTSEVERITY () <= WARNING;
}

//******************************************************************************
void RDSPTransfersProcess::doPostOk ( GenericInterface *rpGICaller, 
									  bool bSuccessFlag)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, I_("doPostOk"));
	const BFDataGroupId& idDataGroup = getDataGroupId();

	if (bSuccessFlag)
	{
		if (m_Caller == I_("TradeEntry"))
		{
			RDSPTransfer *pRDSPTransfer = dynamic_cast <RDSPTransfer *> (getCBOItem (IFASTBP_PROC::RDSP_TRANSFER, idDataGroup));			

			if (pRDSPTransfer)
			{
				Trade *pTrade = dynamic_cast <Trade*> (getCBOItem (IFASTBP_PROC::TRADE, idDataGroup));

				if (pTrade)
				{
					struct fields_mapping
					{
						BFFieldId _transfer;
						BFFieldId _trade;
					} 
					a_fields_mapping [] = 
					{
						{ifds::AccountNum,			ifds::AccountNum		 },
						{ifds::ExtAccount,			ifds::ExtAccount		 },
						{ifds::ExtSpecimenPlanNo,	ifds::ExtSpecimenPlanNo	 },
						{ifds::NontaxContrib,		ifds::NontaxContrib		 },
						{ifds::Rollovers,			ifds::Rollovers			 },
						{ifds::CDSGrant,			ifds::CDSGrant			 },
						{ifds::CDSBond,				ifds::CDSBond			 },
						{ifds::CurrYrFMV,			ifds::CurrYrFMV			 },
						{ifds::PrevYrGrantBond,		ifds::PrevYrGrantBond	 },
						{ifds::PrevYrContrib,		ifds::PrevYrContrib		 },
						{ifds::PrevYrNonTaxRedAmt,  ifds::PrevYrNonTaxRedAmt },
						{ifds::PrevYrTaxRedAmt,		ifds::PrevYrTaxRedAmt	 },
						{ifds::CurrYrNonTaxRedAmt,  ifds::CurrYrNonTaxRedAmt },
						{ifds::CurrYrTaxRedAmt,		ifds::CurrYrTaxRedAmt    },
					};

					int num_fields = sizeof (a_fields_mapping) / sizeof (fields_mapping);

					for (int i = 0; i < num_fields; i++)
					{
						DString str;

						pRDSPTransfer->getField (a_fields_mapping [i]._transfer, str, idDataGroup, false);
						pTrade->setField (a_fields_mapping [i]._trade, str, idDataGroup.getParent(), false);
					}
				}
			}
		}
	}
}




