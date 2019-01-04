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
// ^FILE   : MgmtFee.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : September, 2004
//
// ^CLASS    : MgmtFee
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

class MFAccount;
//Forward declarations

class IFASTCBO_LINKAGE MgmtFee : virtual public Redemption
{
public:
   MgmtFee (BFAbstractCBO &parent);
   virtual ~MgmtFee();
//whether tax rates are allowed
   virtual bool areTaxRatesAllowed (const BFDataGroupId &idDataGroup);
protected:
   virtual SEVERITY doInit (const BFDataGroupId &idDataGroup);
   virtual bool supportsAllocations (const BFDataGroupId &idDataGroup);
   virtual SEVERITY preInitWithDefaultValues (const BFDataGroupId &idDataGroup);
   virtual void doInitWithDefaultValues (const BFDataGroupId &idDataGroup);
   virtual SEVERITY doValidateField ( const BFFieldId &idField, 
                                      const DString &strValue, 
                                      const BFDataGroupId &idDataGroup
                                    );
   virtual SEVERITY transTypeRelatedChanges (const BFDataGroupId &idDataGroup);
   virtual SEVERITY canAccountTrade ( MFAccount *pMFAccount, 
                                      const BFDataGroupId &idDataGroup
                                    );
   virtual SEVERITY validateSettleType ( const DString &settleType,
                                         const BFDataGroupId &idDataGroup
                                       );
   virtual SEVERITY validateFundClass ( const DString &fundCode, 
                                        const DString &classCode, 
                                        const DString &accountNum, 
                                        const BFDataGroupId &idDataGroup
                                      );
   virtual SEVERITY payTypeRelatedChanges (const BFDataGroupId &idDataGroup);
   virtual SEVERITY fromFundClassRelatedChanges ( const DString &fundCode, 
                                                  const DString &classCode, 
                                                  const BFDataGroupId &idDataGroup
                                                );  
private:
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/MgmtFee.hpp-arc  $
//
//   Rev 1.16   Jul 14 2005 15:27:28   porteanm
//PET1171 EUSD 1B - Req change - removed  validateEUSDBackDates().
//
//   Rev 1.15   Jul 07 2005 11:39:52   porteanm
//PET1171 EUSD 1B - Added validateEUSDBackDates().
//
//   Rev 1.14   Dec 21 2004 12:11:28   popescu
//PTS 10037026, Management fee transactions for LSIF funds will call the LSIF available units module, to determine whether the user is able to place the trade. However, the user should not be able to change the LSIF Clawback code, therefore Desktop locks the corresponding field (missed validation of PTS 10031126)
//
//   Rev 1.13   Dec 07 2004 01:37:36   popescu
//PET 1117/56 trades processing/modify trade
//
//   Rev 1.12   Nov 29 2004 20:30:24   popescu
//PET 1117/06/56 fees/trades processing
//
//   Rev 1.11   Nov 14 2004 14:50:22   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.10   Nov 06 2004 00:42:10   popescu
//PET 1117/06, synch changes
//
//   Rev 1.5   Nov 04 2004 17:38:14   popescu
//PET 1117/06, Trade processing
//
//   Rev 1.4   Nov 02 2004 19:19:28   popescu
//PET 1117/06 Trade processing...
//
//   Rev 1.3   Oct 28 2004 18:23:46   popescu
//PET 1117/06
//
//   Rev 1.2   Oct 22 2004 19:58:46   popescu
//PET 1117/06, work in progress...
//
//   Rev 1.1   Oct 21 2004 06:29:06   popescu
//PET 1117/06 - Trade processing work in progress..
//
//   Rev 1.0   Oct 01 2004 19:29:50   popescu
//Initial revision.
 * 
 *    Rev 1.206   Sep 15 2004 15:35:34   popescu
// 
*/