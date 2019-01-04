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
// ^FILE   : LightTrade.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : September, 2004
//
// ^CLASS    : LightTrade
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\trade.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

//Forward declarations
class MFAccount;

class IFASTCBO_LINKAGE LightTrade : public Trade
{
public:
   LightTrade (BFAbstractCBO &parent, bool bManualTrades = false);
   virtual ~LightTrade();
//whether tax rates are allowed
   virtual bool areTaxRatesAllowed (const BFDataGroupId &idDataGroup);
//whether dilution is allowed	or not
	virtual bool isDilutionAllowed (const BFDataGroupId &idDataGroup);
protected:
   virtual SEVERITY doInit (const BFDataGroupId &idDataGroup);
   virtual bool supportsAllocations (const BFDataGroupId &idDataGroup);
   virtual bool supportsFromAllocations (const BFDataGroupId &idDataGroup);
   virtual bool isHypo ();
   virtual SEVERITY transTypeRelatedChanges (const BFDataGroupId &idDataGroup);
   virtual SEVERITY doApplyRelatedChanges ( const BFFieldId &idField, 
                                            const BFDataGroupId &idDataGroup);
   virtual void doInitWithDefaultValues (const BFDataGroupId &idDataGroup);
   virtual void getFundAndClassFieldIds ( BFFieldId &fundCodeFieldId, 
                                          BFFieldId &classCodeFieldId);
   virtual void getAccountFieldId (BFFieldId &accountFieldId);
   virtual SEVERITY canAccountTrade ( MFAccount *pMFAccount, 
                                      const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateAccount ( MFAccount *pMFAccount, 
                                      const BFDataGroupId &idDataGroup);
private:
   bool _bManualTrades;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/LightTrade.hpp-arc  $
//
//   Rev 1.6   Sep 06 2007 17:19:34   popescu
//GAP 18 - added manual management fee rebate to manual dividend screen
//
//   Rev 1.5   Jul 07 2005 12:17:52   AGUILAAM
//PET1235 : dilution, part of Rebook/Cancellation
//
//   Rev 1.4   Nov 29 2004 20:30:18   popescu
//PET 1117/06/56 fees/trades processing
//
//   Rev 1.3   Nov 14 2004 14:49:08   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.2   Nov 06 2004 00:41:40   popescu
//PET 1117/06, synch changes
//
//   Rev 1.1   Nov 04 2004 17:38:02   popescu
//PET 1117/06, Trade processing
//
//   Rev 1.0   Oct 01 2004 19:30:42   popescu
//Initial revision.
 * 
 *    Rev 1.206   Sep 15 2004 15:35:34   popescu
// 
*/