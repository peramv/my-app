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
// ^FILE   : RESPBeneficiaryValidation.hpp
// ^AUTHOR : 
// ^DATE   : March, 2010
//
// ^CLASS    : RESPBeneficiaryValidation
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

class IFASTCBO_LINKAGE RESPBeneficiaryValidation : public MFCanBFCbo, private boost::noncopyable
{
public:

   RESPBeneficiaryValidation( BFAbstractCBO &parent );
   virtual ~RESPBeneficiaryValidation();
   SEVERITY init (const DString &strTransId,
				  const DString &strAccountNum,
				  const DString &strTradeType,
				  const DString &strTradeDate,
				  const DString &strTradeAmount,
	              const DString &strEntityType, 
                  const DString &strEntityTypeSeq, 
                  const DString &strRESPBenefId, 
				  const DString &strRESPBenefName,
                  const DString &strRESPAllocAmount, 
                  const DString &strRESPAllocPercent, 
                  const DString &strRESPContrDetlVer,
				  const DString &strCallType,
				  const DString &strCreateEscrow,
                  bool ignoreDataNotFound = true);   

   SEVERITY validateBeneficiary (const BFDataGroupId &idDataGroup);

   static void buildKey (const DString &_strTransId,
	                     const DString &_strEntityType, 
                         const DString &_strEntityTypeSeq, 
                         const DString &_strRESPBenefId, 
                         const DString &_strRESPAllocAmount, 
                         const DString &_strRESPAllocPercent,
		                 DString &strKey);

private:
	SEVERITY displayErrorMessage (const DString &errorNumber,
								  const DString &param1,
								  const DString &param2,
								  const BFDataGroupId &idDataGroup);

	DString m_BenefName;
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log::   
//
