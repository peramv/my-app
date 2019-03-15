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
// ^FILE   : TradeMinAmtCheck.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : July, 2001
//
// ^CLASS    : TradeMinAmtCheck
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

class IFASTCBO_LINKAGE TradeMinAmtCheck : public MFCanBFCbo, private boost::noncopyable
{
public:

   TradeMinAmtCheck( BFAbstractCBO &parent );
   virtual ~TradeMinAmtCheck();
   SEVERITY init( const DString &strAccountNum, 
                  const DString &strFundCode, 
                  const DString &strClassCode, 
                  const DString &strTransType, 
                  const DString &strAmountType, 
                  const DString &strAmount, 
                  const DString &strEffectiveDate, 
                  const DString &strSettleCurrency,
                  const DString &strExchRate, 
                  const DString &dstrBrokerCode, 
                  const DString &dstrBranchCode, 
                  const DString &dstrSalesRepCode,
                  const DString &dstrAMSCode     = NULL_STRING, 
                  const DString &dstrAMSType     = NULL_STRING,
                  const DString &dstrDepositType = NULL_STRING, //panutdar in1419539
                  const DString &dstrOrderType= NULL_STRING,
                  bool ignoreDataNotFound = true,
                  bool bFullExchPrntToPrnt = false,
                  const DString &Indc = I_(""),
                  const DString &adjForTransNum = I_(""),
				  const DString &transNum = I_(""));   

   SEVERITY addConditions();
private:
   DString _fundCode,
      _classCode,
	  _accountNum,
      _tradeDate;
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/TradeMinAmtCheck.hpp-arc  $
//
//   Rev 1.13   Dec 08 2011 21:50:52   wp040032
//P0183989 - Money Market Non Receipt
//
//   Rev 1.12   01 Oct 2008 12:12:24   popescu
//Check in for incident 1419539
//
//   Rev 1.11   01 May 2008 13:58:16   kovacsro
//PET2255 FN47 - New Ontario LIF - finalized
//
//   Rev 1.10   23 Jul 2007 16:50:22   popescu
//PET 2360 - FN 20 - GAP 20 Soft cap functionality
//
//   Rev 1.9   Oct 30 2006 17:07:48   jankovii
//PET 2185 FN04 - Trade restrictions.
//
//   Rev 1.8   Nov 14 2004 14:58:02   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.7   Aug 15 2003 15:31:00   HSUCHIN
//added support for AMS Initial purchase check
//
//   Rev 1.6   Mar 21 2003 18:27:22   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.5   Jan 21 2003 18:35:40   WINNIE
//assign new error # based on view changes; add logic to allow minimum amount edit check severity code to control warning or error
//
//   Rev 1.4   Oct 09 2002 23:55:12   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.3   Aug 29 2002 12:53:54   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.2   22 May 2002 18:18:50   PURDYECH
//BFData Implementation
//
