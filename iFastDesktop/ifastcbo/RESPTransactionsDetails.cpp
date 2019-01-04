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
//    Copyright 2000 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : RESPTransactionsDetails.cpp
// ^AUTHOR : Dan Petolescu
// ^DATE   : 11/01/2000
//
// ^CLASS    : RESPTransactionsDetails
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
#include "stdafx.h"
#include "mfaccount.hpp"
#include "resptransactionsdetails.hpp"
#include "respbeneficiaryallocationlist.hpp"
#include "resptransferlist.hpp"
#include "pendingtradelist.hpp"
#include "pendingtradedetails.hpp"
#include "transactionlist.hpp"
#include "transactiondetails.hpp"

#include <ifastdataimpl\dse_dstc0111_req.hpp>
#include <ifastdataimpl\dse_dstc0111_vw.hpp>
#include <ifastdataimpl\dse_dstc0111_vwrepeat_record.hpp>

namespace ifds
{   
   extern CLASS_IMPORT const BFDecimalFieldId Amount;
   extern CLASS_IMPORT const BFDecimalFieldId GrantRepayablePurch;
}

namespace CND
{
   extern const long INFO_CESG_UC_REASON;
   extern const long INFO_CESG_REJ_REASON;
   extern const long INFO_SAGES_UC_REASON;
   extern const long INFO_SAGES_REJ_REASON;
   extern const long INFO_SAGES_REPORTED;
   extern const long INFO_SAGES_TRANSORIGCODE;
}

namespace  
{
   const I_CHAR * const CLASSNAME = I_( "RESPTransactionsDetails" );
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
//	Field DD Id,					State Flags,	Group Flags    
    {ifds::GrantRepayablePurch,		BFCBO::NONE,	0 },
	{ifds::UCReasonDesc,			BFCBO::NONE,	0 },
	{ifds::CESGInDetlErrorDesc,		BFCBO::NONE,	0 },
	{ifds::SAGESUCDesc,				BFCBO::NONE,	0 },
	{ifds::SAGESRejDesc,			BFCBO::NONE,	0 },
	{ifds::SAGESReported,			BFCBO::NONE,	0 },
	{ifds::SAGESTransOrigCode,		BFCBO::NONE,	0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//****************************************************************************
RESPTransactionsDetails::RESPTransactionsDetails( BFAbstractCBO &parent )
: MFCanBFCbo( parent),
_accountNum (NULL_STRING)
{
	TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
  	registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//****************************************************************************
RESPTransactionsDetails::~RESPTransactionsDetails()
{
   TRACE_DESTRUCTOR( CLASSNAME );

}     

//****************************************************************************
SEVERITY RESPTransactionsDetails::init( const DString &accountNum, 
                                        const BFData& InstData,
										const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast<BFData&>(InstData), false, true );
   _accountNum = accountNum;

   DString dstrGrantRepayable;

   getField (ifds::GrantRepayable, dstrGrantRepayable, BF::HOST);
   setFieldNoValidate (ifds::GrantRepayablePurch, dstrGrantRepayable, BF::HOST, false);

   setConditions (ifds::UCReasonDesc, I_("CESG_UC_REASON"), CND::INFO_CESG_UC_REASON, idDataGroup);
   setConditions (ifds::CESGInDetlErrorDesc, I_("CESG_REJ_REASON"), CND::INFO_CESG_REJ_REASON, idDataGroup);
   setConditions (ifds::SAGESUCDesc, I_("SAGES_UC_REASON"), CND::INFO_SAGES_UC_REASON, idDataGroup);
   setConditions (ifds::SAGESRejDesc, I_("SAGES_REJ_REASON"), CND::INFO_SAGES_REJ_REASON, idDataGroup);
   setConditions (ifds::SAGESReported, I_("SAGES_REPORTED"), CND::INFO_SAGES_REPORTED, idDataGroup);
   setConditions (ifds::SAGESTransOrigCode, I_("SAGES_TRANSORIGCODE"), CND::INFO_SAGES_TRANSORIGCODE, idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}


//****************************************************************************
SEVERITY RESPTransactionsDetails::doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   if( idField == ifds::BeneName )
   {

   }
   else if( idField == ifds::TransId )
   {

   }
   else
   {

   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY RESPTransactionsDetails::getRESPBenefAllocationList (RESPBeneficiaryAllocationList *&pRESPBeneficiaryAllocationList, 
                                                              const BFDataGroupId &idDataGroup,
															                 const DString &tradeType /*= I_("Pend")*/)

{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getRESPBenefAllocationList"));

   pRESPBeneficiaryAllocationList = NULL;
   MFAccount *pMFAccount (NULL);

   if ( getWorkSession ().getMFAccount ( idDataGroup, 
                                         _accountNum, 
                                         pMFAccount) <= WARNING && 
        pMFAccount)
   {
      DString transId (NULL_STRING);
      
      getField (ifds::TransId, transId, idDataGroup, false);
      if (pMFAccount->getRESPBenefAllocationList (pRESPBeneficiaryAllocationList, 
                                                  idDataGroup, 
                                                  transId, 
                                                  tradeType) <= WARNING &&
           pRESPBeneficiaryAllocationList)
      {
         DString amount,
            effectiveDate;

         getField (ifds::TradeGrossAmt, amount, idDataGroup, false);
         getField (ifds::EffectiveDate, effectiveDate, idDataGroup, false);
         pRESPBeneficiaryAllocationList->setField ( ifds::Amount, 
                                                    amount, 
                                                    idDataGroup, 
                                                    false);
         pRESPBeneficiaryAllocationList->setField ( ifds::EffectiveDate, 
                                                    effectiveDate, 
                                                    idDataGroup, 
                                                    false);
      }
   }
	return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY RESPTransactionsDetails::getRESPTransferList (RESPTransferList *&pRESPTransferList, 
                                                       const BFDataGroupId &idDataGroup,
													                const DString &tradeType /*= I_("Pend")*/)

{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getRESPTransferList"));

   pRESPTransferList = NULL;
   MFAccount *pMFAccount (NULL);

   if ( getWorkSession ().getMFAccount ( idDataGroup, 
                                         _accountNum, 
                                         pMFAccount) <= WARNING && 
        pMFAccount)
   {
      DString transId (NULL_STRING);
      DString accountNumTo (NULL_STRING);
      DString transType (NULL_STRING);
      DString tradeDate (NULL_STRING);
      DString depositType (NULL_STRING);
      DString redCode (NULL_STRING);
      DString amount (NULL_STRING);

	  //

      
      getField (ifds::TransId, transId, idDataGroup, false);
      getField (ifds::AccountTo, accountNumTo, idDataGroup, false);
      getField (ifds::TransType, transType, idDataGroup, false);
      getField (ifds::EffectiveDate, tradeDate, idDataGroup, false);
      getField (ifds::DepositType, depositType, idDataGroup, false);
      getField (ifds::RedCode, redCode, idDataGroup, false);
      getField (ifds::GrossAmt, amount, idDataGroup, false);

	  if (pMFAccount->getRESPTransferList ( pRESPTransferList, 
                                           idDataGroup, 
                                           accountNumTo, 
										             transId,
										             transType,
										             tradeDate,
										             depositType,
										             redCode,
										             amount,
                                           tradeType) <= WARNING &&
           pRESPTransferList)
      {
         DString amount,
            effectiveDate;

         getField (ifds::TradeGrossAmt, amount, idDataGroup, false);
         getField (ifds::EffectiveDate, effectiveDate, idDataGroup, false);
         pRESPTransferList->setField ( ifds::Amount, 
                                                    amount, 
                                                    idDataGroup, 
                                                    false);
         pRESPTransferList->setField ( ifds::EffectiveDate, 
                                                    effectiveDate, 
                                                    idDataGroup, 
                                                    false);
      }
   }
	return GETCURRENTHIGHESTSEVERITY ();
}
//******************************************************************************
SEVERITY RESPTransactionsDetails::getTransactionDetails ( TransactionDetails *&pTransactionDetails,
                                                          const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getTransactionDetails"));

   pTransactionDetails = NULL;
   DString transId (NULL_STRING);
   
   getField (ifds::TransId, transId, idDataGroup, false);
   DString strKey = I_("TransId=") + transId;
   
   TransactionList *pTransactionList = dynamic_cast <TransactionList*> (getObject (strKey, idDataGroup));
	if (!pTransactionList)
	{
		pTransactionList = new TransactionList (*this);
		if (pTransactionList->init ( _accountNum, 
                                   NULL_STRING, 
                                   NULL_STRING,
                                   NULL_STRING,
                                   I_("N"),
                                   transId) <= WARNING && 
          pTransactionList)
      {
         //here we should only get one hit...
         BFObjIter bfIter (*pTransactionList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
         
         if (!bfIter.end())
         {
            pTransactionDetails = pTransactionList ->getItem (bfIter.getStringKey (), idDataGroup);
         }
      }
      else
      {
         delete pTransactionList;
      }
	}
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RESPTransactionsDetails::getPendingTransactionDetails ( PendingTradeDetails *&pPendingTradeDetails,
                                                                 const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getPendingTransactionDetails"));

   pPendingTradeDetails = NULL;
   DString transNum (NULL_STRING);
   
   getField (ifds::TransNum, transNum, idDataGroup, false);
   DString strKey = I_("TransNum=") + transNum;
   
   PendingTradeList *pPendingTradeList = dynamic_cast <PendingTradeList*> (getObject (strKey, idDataGroup));
	if (!pPendingTradeList)
	{
		pPendingTradeList = new PendingTradeList (*this);
		if (pPendingTradeList->initSearch ( I_("TransNum"), 
                                          NULL_STRING, 
                                          transNum,
                                          NULL_STRING,
                                          NULL_STRING,
                                          NULL_STRING,
                                          NULL_STRING,
                                          NULL_STRING,
                                          NULL_STRING,
                                          NULL_STRING,
                                          NULL_STRING,
                                          NULL_STRING,
                                          NULL_STRING,
                                          NULL_STRING) <= WARNING && 
          pPendingTradeList)
      {
         //here we should only get one hit...
         BFObjIter bfIter (*pPendingTradeList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
         
         if (!bfIter.end())
         {
            pPendingTradeList ->getItem (bfIter.getStringKey (), idDataGroup);
            pPendingTradeDetails = dynamic_cast <PendingTradeDetails*> (bfIter.getObject ());
         }
      }
      else
      {
         delete pPendingTradeList;
      }
	}
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RESPTransactionsDetails::setConditions ( const BFFieldId& idField,
												  const DString& dstrTag,
												  const long lMsg,
												  const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setConditions"));

   DString dstrField, idiStr;

   getField (idField, dstrField, BF::HOST);
   dstrField.stripLeading();

   if (!dstrField.empty())
   {
	   addIDITagValue( idiStr, dstrTag, dstrField);
	   ADDCONDITIONFROMFILEIDI (lMsg, idiStr);
  
	   CONDITIONVECTOR* _pCond;
	   getFieldConditionVector(idField,idDataGroup,_pCond );

	   if( _pCond == NULL )
	   {
		   _pCond = new CONDITIONVECTOR;
	   }
	   int count = CURRENTCONDITIONCOUNT( );
	   Condition   *c = NULL;
	   for( int i = 0; i < count; i++ )
	   {
		   c = new Condition( *GETCURRENTCONDITION( i ));
		   _pCond->push_back( c );
	   };

	   setFieldConditionVector(idField,idDataGroup,_pCond );	
   }

   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RESPTransactionsDetails.cpp-arc  $
 * 
 *    Rev 1.20   Jun 09 2010 15:12:00   jankovii
 * IN 2131626 - PETP0165541 -  Mapping Issues on the RESP Trans History Screen.
 * 
 *    Rev 1.19   Jun 08 2010 11:29:42   jankovii
 * IN 2141202 - PET0165541-"To Beneficiary" fileld  display issue on Pending view.
 * 
 *    Rev 1.18   May 03 2010 19:40:34   popescu
 * PET165541_FN01_QESI - RESP Gap - small fixes
 * 
 *    Rev 1.17   Apr 23 2010 16:20:36   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.16   Apr 15 2010 11:02:30   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.15   Mar 31 2010 16:02:50   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.14   Mar 31 2010 00:25:10   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading - bene allocation updates
 * 
 *    Rev 1.13   Mar 30 2010 19:00:38   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.12   Mar 30 2010 16:35:24   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.11   Mar 29 2010 23:00:24   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.10   Mar 29 2010 10:52:58   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.9   Nov 14 2004 14:52:24   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.8   Mar 21 2003 18:22:14   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.7   Oct 09 2002 23:54:52   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.6   Aug 29 2002 12:56:30   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.5   22 May 2002 18:29:44   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.4   03 May 2001 14:07:02   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.3   Dec 17 2000 20:24:18   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.2   Sep 01 2000 15:25:44   HUANGSHA
 * added pClientLocale in setField(...)
 * 
 *    Rev 1.1   Mar 22 2000 09:02:48   PETOLESC
 * Added Tax Rates and RESP dialogs.
// 
//    Rev 1.1   Feb 07 2000 11:02:28   PETOLESC
// Minor corrections and code cleaning.
 * 
 *
 */