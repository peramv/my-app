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
//    Copyright 1997 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : RESPTransferValidation.hpp
// ^AUTHOR : Unknown
// ^DATE   : March, 2010
//
// ^CLASS    : RESPTransferValidation
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <SrcPrag.h>
#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class RESPTransfer;

class IFASTCBO_LINKAGE RESPTransferValidation : public MFCanBFCbo, private boost::noncopyable
{
public:

   RESPTransferValidation( BFAbstractCBO &parent );
   virtual ~RESPTransferValidation();
   SEVERITY init (const DString &strCallType,
				  const DString &strTradeType,
				  const DString &strTransId,
				  const DString &strTransType,
                  const DString &strDepositType,
				  const DString &strRedCode,
                  const DString &strAccountNum,
				  const DString &strAccountTo,
				  const DString &strEffectiveDate,
				  const DString &strAmount,
				  const DString &strRESPBenefName,
				  const DString &strNEQ1,
				  const DString &strNEQ2,
				  const DString &strAcctLvlOverride,
				  const RESPTransfer *pRESPTransfer,
				  const BFDataGroupId &idDataGroup,
                  bool ignoreDataNotFound = true);   

   SEVERITY validateBeneficiary (const BFDataGroupId &idDataGroup);

   static void buildKey (const DString &_dstrRESPBenefId,
	                     const DString &_dstrTradeDate, 
                         const DString &_dstrAmount, 
						 const DString &strNEQ1,
					     const DString &strNEQ2,
						 const RESPTransfer *pRESPTransfer,
						 const BFDataGroupId &idDataGroup,
						 DString &strKey);

private:
	SEVERITY displayErrorMessage (const DString &errorNumber,
								  const DString &param1,
								  const DString &param2,
								  const BFDataGroupId &idDataGroup);

	DString m_BenefName;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log::   
 */
