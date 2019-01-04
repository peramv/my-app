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
//    Copyright 2003
//
//
//******************************************************************************
//
// ^FILE   : ManualDividend.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
#include <ifastcbo\trade.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE ManualDividend : public Trade
{
public:
   ManualDividend (BFAbstractCBO &parent);
   virtual ~ManualDividend();
//whether the shareholder address is needed
   virtual bool isShareholderAddressNeeded (const BFDataGroupId &idDataGroup);
protected:
   virtual SEVERITY doValidateField ( const BFFieldId &idField, 
                                      const DString &strValue, 
                                      const BFDataGroupId &idDataGroup);
   virtual void doInitWithDefaultValues (const BFDataGroupId &idDataGroup);
   virtual SEVERITY doInit (const BFDataGroupId &idDataGroup);
   virtual SEVERITY doApplyRelatedChanges (const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   virtual SEVERITY transTypeRelatedChanges (const BFDataGroupId &idDataGroup);
   virtual void getFundAndClassFieldIds ( BFFieldId &fundCodeFieldId,
                                          BFFieldId &classCodeFieldId);
//base class' virtual methods
   virtual bool isWireSupported (const BFDataGroupId &idDataGroup);
   virtual void getAccountFieldId (BFFieldId &accountFieldId);
   virtual bool supportsAllocations (const BFDataGroupId &idDataGroup);
   virtual bool supportsFromAllocations (const BFDataGroupId &idDataGroup);
   virtual SEVERITY canAccountTrade ( MFAccount *pMFAccount, 
                                      const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateFundClass ( const DString &fundCode, 
                                        const DString &classCode, 
                                        const DString &accountNum, 
                                        const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateToFundClass ( const DString &fundCode, 
                                          const DString &classCode, 
                                          const DString &accountNum, 
                                          const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateToFundClassAgainstFundEligible(const DString &fundCode,
                                                           const DString &classCode,
                                                           const BFDataGroupId &idDataGroup);

   virtual SEVERITY validateFromToFundClass ( const DString &fromCode,
                                              const DString &fromClass,
                                              const DString &toCode,
                                              const DString &toClass,
                                              const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateESGSettle (const DString &strValue, 
                                       const BFDataGroupId &idDataGroup);

   virtual SEVERITY validateMasterActAMS (const BFDataGroupId &idDataGroup);

   bool isManualDividendAllowed ( const DString &fundCode, 
                                  const DString &classCode, 
                                  const BFDataGroupId &idDataGroup);
   virtual SEVERITY payMethodPropertyChanges (const BFDataGroupId &idDataGroup);
   private:
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ManualDividend.hpp-arc  $
//
//   Rev 1.16   17 Aug 2009 10:38:24   popescu
//IN#1686644 - R92_PET5517_FN94D - cannot save manual FC in Desktop - revised the code a little bit
//
//   Rev 1.15   Aug 17 2009 08:33:40   dchatcha
//IN#1686644 - R92_PET5517_FN94D - cannot save manual FC in Desktop.
//
//   Rev 1.14   Jan 21 2009 11:25:44   jankovii
//PET5517_FN94_Foreign Exchange Allocated Capital Gains
//
//   Rev 1.13   Sep 06 2007 17:21:08   popescu
//GAP 18 - added manual management fee rebate to manual dividend screen
//
//   Rev 1.12   Mar 01 2006 13:59:36   ZHANGCEL
//PET1334 - FN01 -- Added logic for ESGSettle enhancement
//
//   Rev 1.11   May 27 2005 10:17:36   popescu
//Incident # 319459 - fixed the Manual Dividend reset issue - also used WorkSessionTradesList for manual dividends; use the TradesProcess instead of ManualDividendProcess
//
//   Rev 1.10   May 20 2005 14:09:46   popescu
//PET 1117/08 fixed reset of the trans type to 'ED'
//
//   Rev 1.9   Dec 09 2004 17:32:16   hernando
//PET910 - Returned validateFundCodeCash.
//
//   Rev 1.8   Nov 29 2004 20:30:20   popescu
//PET 1117/06/56 fees/trades processing
//
//   Rev 1.7   Nov 14 2004 14:49:20   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.6   Nov 06 2004 00:41:42   popescu
//PET 1117/06, synch changes
//
//   Rev 1.5   Jul 11 2003 13:50:10   YINGBAOL
//PTS10019497 add changeSettleCurrencyByFundClass
//
//   Rev 1.4   Jul 10 2003 16:43:06   HERNANDO
//Added ValidateAddressCodeEffectiveDate.
//
//   Rev 1.3   Jun 30 2003 16:31:36   popescu
//moved the ifast_fields include in the .cpp file
//
//   Rev 1.2   Jun 27 2003 15:55:08   HERNANDO
//Added ValidateEffectiveDate.
//
//   Rev 1.1   May 30 2003 17:37:46   HERNANDO
//Added validateToFundClass, validateFromFundClass, and IsManualDividendAllowed.
//
//   Rev 1.0   May 22 2003 16:52:44   HERNANDO
//Initial revision.
// 
*/