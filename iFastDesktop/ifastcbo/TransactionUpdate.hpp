#pragma once

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
//    Copyright 2004, By International Financial Data Service
//
//
//******************************************************************************
//
// ^FILE   : TransactionUpdate.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : TransactionUpdate
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class BatchInfoList;

class IFASTCBO_LINKAGE TransactionUpdate : public MFCanBFCbo
{
public:

   TransactionUpdate( BFAbstractCBO &parent );
   virtual ~TransactionUpdate();

   SEVERITY init(const BFData& data );
   
   SEVERITY init(const DString &recordType,
	             const DString &transNum,
				 const DString &transId,
				 const DString &authorization,
				 const DString &originalBatch,
				 const DString &settleUser,
				 const DString &caller,
				 const DString &paymentInfo,
				 const DString &dstrEnableTradeAuthorization,
				 const BFDataGroupId& idDataGroup,
				 const DString &tradeRestriction = NULL_STRING,
				 const DString &tradeRestrictionReason = NULL_STRING,
                 const DString &dstrSourceOfFundsChecked = NULL_STRING );

   SEVERITY initNew( const BFDataGroupId& idDataGroup );

protected:

	virtual SEVERITY doValidateField( const BFFieldId& idField, 
		                               const DString& strValue, 
												 const BFDataGroupId& idDataGroup );   
	virtual void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );

	virtual SEVERITY doApplyRelatedChanges (const BFFieldId &idField, const BFDataGroupId &idDataGroup);

	void canUserModifyBatch (const DString &batchUser, const BFDataGroupId &idDataGroup);
    SEVERITY addBlankToSubSet(const BFFieldId &idField ,const BFDataGroupId &idDataGroup, bool dstrUseNotApplicableAsDesc = false );

private:
	SEVERITY setPaymentStatusSubstList (const BFDataGroupId& idDataGroup);
	SEVERITY commonInit(const BFDataGroupId& idDataGroup);

private:

	DString			m_dstrPendProcRecordType;
	BatchInfoList	*pBatchInfoList;
	DString			_caller;
};

/* $Log::   
 */