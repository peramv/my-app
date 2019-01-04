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
//    Copyright 2000 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : AdminFee2.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : September, 2004
//
// ^CLASS    : AdminFee2
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\redemption.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

//Forward declarations
class BankInstructions;

class IFASTCBO_LINKAGE AdminFee : public Redemption
{
public:
   AdminFee (BFAbstractCBO &parent);
   virtual ~AdminFee ();
//whether tax rates are allowed
   virtual bool areTaxRatesAllowed (const BFDataGroupId &idDataGroup);
protected:
   virtual SEVERITY doInit (const BFDataGroupId &idDataGroup);
   virtual SEVERITY doInit (const BFData &data);
   virtual bool supportsAllocations (const BFDataGroupId &idDataGroup);
   virtual SEVERITY preInitWithDefaultValues (const BFDataGroupId &idDataGroup);
   virtual void doInitWithDefaultValues (const BFDataGroupId &idDataGroup);
   virtual SEVERITY transTypeRelatedChanges (const BFDataGroupId &idDataGroup);
   virtual SEVERITY getDefaultBankInstructions (
                                                 BankInstructions *&pBankInstructions, 
                                                 const BFDataGroupId &idDataGroup
                                               );
//validation methods
   virtual bool isACHApplicable (const BFDataGroupId &idDataGroup);
   virtual SEVERITY withholdingTaxRelatedChanges (const BFDataGroupId& idDataGroup);
   virtual SEVERITY validateSettleType ( const DString &settleType,
                                         const BFDataGroupId &idDataGroup
                                       );
   virtual SEVERITY validateAmountAmtType (const BFDataGroupId& idDataGroup);
   virtual SEVERITY validateMinFromFundAmount ( const DString &amtType,
                                                const DString &amount,
                                                const BFDataGroupId &idDataGroup
                                              );
   virtual SEVERITY validateAmount ( const DString &amount,  
                                     const BFDataGroupId &idDataGroup 
                                   );
   virtual SEVERITY validateAmountGrossNet (const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateRedCode ( const DString &redCode, 
                                      const BFDataGroupId &idDataGroup);   
   virtual SEVERITY validateSrcOfFund(const DString& strValue, const BFDataGroupId &idDataGroup);

private:
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AdminFee.hpp-arc  $
//
//   Rev 1.9   Mar 05 2012 11:40:34   dchatcha
//P0186484 FN05 - SEG Trade Processing.
//
//   Rev 1.8   Jul 14 2005 15:28:20   porteanm
//PET1171 EUSD 1B - Req change - removed  validateEUSDBackDates().
//
//   Rev 1.7   Jul 07 2005 11:38:50   porteanm
//PET1171 EUSD 1B - Added validateEUSDBackDates().
//
//   Rev 1.6   Dec 07 2004 01:37:26   popescu
//PET 1117/56 trades processing/modify trade
//
//   Rev 1.5   Nov 29 2004 20:30:12   popescu
//PET 1117/06/56 fees/trades processing
//
//   Rev 1.4   Nov 06 2004 00:39:50   popescu
//PET 1117/06, synch changes
//
//   Rev 1.6   Nov 04 2004 17:37:04   popescu
//PET 1117/06, Trade processing
//
//   Rev 1.5   Nov 02 2004 19:19:14   popescu
//PET 1117/06 Trade processing...
//
//   Rev 1.4   Oct 28 2004 18:23:44   popescu
//PET 1117/06
//
//   Rev 1.3   Oct 27 2004 11:26:48   popescu
//PET 1117/06
//
//   Rev 1.2   Oct 22 2004 19:58:44   popescu
//PET 1117/06, work in progress...
//
//   Rev 1.1   Oct 21 2004 06:29:00   popescu
//PET 1117/06 - Trade processing work in progress..
//
//   Rev 1.0   Oct 01 2004 19:29:46   popescu
//Initial revision.
 * 
 *    Rev 1.206   Sep 15 2004 15:35:34   popescu
// 
*/