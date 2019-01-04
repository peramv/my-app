#pragma once

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
//    Copyright 2003 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : TransSettleLoc.hpp
// ^AUTHOR : Monica Vadeanu
// ^DATE   : November 10, 2003
//
// ^CLASS    : TransSettleLoc
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

#include <dataimpl\dse_dstc0004_vw.hpp>
#include <dataimpl\dse_dstc0022_vw.hpp>
#include <dataimpl\dse_dstc0054_vw.hpp>
#include <dataimpl\dse_dstc0115_req.hpp>

class IFASTCBO_LINKAGE TransSettleLoc : public MFCanBFCbo, private boost::noncopyable
{
public:

   TransSettleLoc( BFAbstractCBO &parent );
   virtual ~TransSettleLoc();

   /**
    * 
    * @param blFrom Yes when Object called for From Account
    *               No else
    * @param pTrade Pointer to Trade, or TransactionList Item, or PendingTradeDetail
    * @param dstrAccountNum
    *               Could be Account From or Account To, which has different field name
    *               in Trade (From is AccountNum, To is AccountTo) then in
    *               in History (From - no, To is TfrAcct) or in Pending (From - no, is only part of the
    *               Request, To is Account To)
    * @param dstrTransType
    *               Although we have the pointer to the Trade object, the Transaction Type field
    *               is named differently in Trade (TradesTransType) than in the History or Pending object (TransType)
    * @param blUpdateableLocation
    * @param idDataGroup
    * @return 
    */
   SEVERITY init( bool blFrom, 					   
						BFAbstractCBO *pTrade, 
						const DString &dstrAccountNum,
						const DString &dstrTransType,
						bool blUpdateableLocation,
						const BFDataGroupId& idDataGroup );

protected:
     
	SEVERITY doValidateField( const BFFieldId& idField,
                             const DString& strValue,
                             const BFDataGroupId& idDataGroup );  
		
	SEVERITY doApplyRelatedChanges( const BFFieldId &fieldId,
                                   const BFDataGroupId& idDataGroup );  
	
	void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );

	void doReset ( const BFDataGroupId& idDataGroup );

private:
	SEVERITY validateClearingMethod( const DString &dstrClearingMethod, 
		                              const BFFieldId& idField,
		                              const BFDataGroupId& idDataGroup );
	
	SEVERITY setSettlementLocationSubstList( const BFDataGroupId& idDataGroup, 
		                                      const BFFieldId& idField );

	SEVERITY setSettleLocationDescription( const BFFieldId& idFieldCode, 
														const BFDataGroupId& idDataGroup,
														const BFFieldId& idFieldDescription );

	SEVERITY setDefaultSettlementLocation( const BFFieldId& idFieldCode, 
														const BFDataGroupId& idDataGroup );

	DString _dstrAccountNum;
	DString _dstrTransType;	

	BFAbstractCBO *_pTrade;

	bool _blFrom;	
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/TransSettleLoc.hpp-arc  $
//
//   Rev 1.2   Nov 14 2004 14:58:58   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.1   Nov 27 2003 12:58:50   VADEANUM
//PET859 FN1 - Settlement Location at Trade Level support.
//
//   Rev 1.0   Nov 10 2003 16:07:00   VADEANUM
//Initial revision.
//
