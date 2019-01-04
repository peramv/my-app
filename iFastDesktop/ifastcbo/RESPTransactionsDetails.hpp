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
//    Copyright 2000 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : RESPTransactionsDetails.hpp
// ^AUTHOR : Dan Petolescu
// ^DATE   : 20/01/2000
//
// ^CLASS    : RESPTransactionsDetails
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

class RESPBeneficiaryAllocationList;
class TransactionDetails;
class PendingTradeDetails;
class RESPTransferList;

class IFASTCBO_LINKAGE RESPTransactionsDetails : public MFCanBFCbo, private boost::noncopyable
{
public:
   RESPTransactionsDetails( BFAbstractCBO &parent );
   virtual ~RESPTransactionsDetails();

   SEVERITY init (const DString &accountNum, const BFData& InstData, const BFDataGroupId& idDataGroup = BF::HOST);
   SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );

   SEVERITY getTransactionDetails (TransactionDetails *&pTransactionDetails,
                                   const BFDataGroupId &idDataGroup);
   SEVERITY getPendingTransactionDetails ( PendingTradeDetails *&pPendingTradeDetails,
                                           const BFDataGroupId &idDataGroup);
   SEVERITY getRESPBenefAllocationList ( RESPBeneficiaryAllocationList *&pRESPBeneficiaryAllocationList, 
                                         const BFDataGroupId &idDataGroup,
										 const DString &tradeType = I_("Pend"));
   SEVERITY getRESPTransferList ( RESPTransferList *&pRESPTransferList, 
                                  const BFDataGroupId &idDataGroup,
								  const DString &tradeType = I_("Pend"));
   SEVERITY setConditions ( const BFFieldId& idField, 
							const DString& dstrTag, 
							const long lMsg, 
							const BFDataGroupId& idDataGroup);

private:
   DString _accountNum;

};

