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
//    Copyright 2000 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE      : MVAFee.hpp
// ^AUTHOR    : Serban Popescu
// ^DATE      : November 2004
//
// ^CLASS     : MVAFee
// ^SUBCLASS  :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <boost\utility.hpp>
#include "transfeecharge.hpp"
///#endif

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

//Forward declarations
class Trade;

class IFASTCBO_LINKAGE MVAFee : public TransFeeCharge
{
public:
   MVAFee (BFAbstractCBO &parent, const DString &feeCode);
   MVAFee (BFAbstractCBO &parent);
   virtual ~MVAFee();
   virtual bool isSystemApplicable (const BFDataGroupId &idDataGroup);
   virtual bool isContextApplicable (const BFDataGroupId &idDataGroup);
   virtual bool hasContextChanged (const BFDataGroupId &idDataGroup);
   virtual SEVERITY restore ( BFCBO &rpParent, 
                              const BFDataGroupId &idDataGroup);
   virtual SEVERITY setFeeDefault (const BFDataGroupId &idDataGroup);
   virtual SEVERITY init ( const BFDataGroupId &idDataGroup, bool bDelyaInit = false);
   virtual SEVERITY doApplyRelatedChanges ( const BFFieldId &idField, const BFDataGroupId &idDataGroup);
private:
   bool isApplicableForFund (const BFDataGroupId &idDataGroup);
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/MVAFee.hpp-arc  $
//
//   Rev 1.1   Mar 13 2012 17:38:26   if991250
//IN 2879297: Money Out
//
//   Rev 1.0   Mar 08 2012 15:09:18   if991250
//Initial revision.
//
//
 */