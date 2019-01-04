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
//    Copyright 2011 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : ProgressiveIntRateList.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : ProgressiveIntRateList
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

class IFASTCBO_LINKAGE ProgressiveIntRateList : public MFCanBFCbo, private boost::noncopyable
{
public:
   ProgressiveIntRateList( BFAbstractCBO &parent );
   virtual ~ProgressiveIntRateList();

   SEVERITY init (const DString& dstrAccountNum,
                  const DString& dstrIntInvestId,
                  const BFDataGroupId& idDataGroup);

   SEVERITY init (const BFDataGroupId& idDataGroup);

   SEVERITY initForTrade (const DString& dstrAccountNum, 
                  const DString& dstrFund,
                  const DString& dstrClass,
                  const DString& dstrInquiry = NULL_STRING,
                  const DString& dstrInvHisInvestId = NULL_STRING, 
                  const DString& dstrInvHisIntRateType = NULL_STRING, 
                  const DString& dstrIInvHisIntCalcMthd = NULL_STRING, 
                  const DString& dstrInvHisTerm = NULL_STRING, 
                  const DString& dstrInvHisIntDate = NULL_STRING, 
                  const DString& dstrInvHisTradeAmt = NULL_STRING, 
                  const DString& dstrInvHisAddlAmt = NULL_STRING,
				      const DString& dstrCommRedRate = NULL_STRING,
                  const DString& dstrForcedRate = NULL_STRING,
                  const DString& dstrForcedRateAmt = NULL_STRING);

protected:

private:
   BFData m_requestData;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ProgressiveIntRateList.hpp-arc  $
//
//   Rev 1.3   Feb 23 2012 08:54:00   jankovii
//IN 2817781- P0186477FN03- Commission Reduction on GI Trading
//
//   Rev 1.2   Dec 03 2011 01:19:56   dchatcha
//P0186477/FN03 - GIA - Purchase
//
//   Rev 1.1   Dec 01 2011 19:06:10   wp040100
//P0186477/FN03 - GIA - Investment History Changes
//
//   Rev 1.0   Nov 27 2011 21:21:18   wp040100
//Initial revision.
//
*/
