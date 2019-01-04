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
// ^FILE      : WithdrawalFee.hpp
// ^AUTHOR    : Serban Popescu
// ^DATE      : November 2004
//
// ^CLASS     : WithdrawalFee
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

class IFASTCBO_LINKAGE WithdrawalFee : public TransFeeCharge
{
public:
   WithdrawalFee (BFAbstractCBO &parent);
   virtual ~WithdrawalFee();
   virtual bool isSystemApplicable (const BFDataGroupId &idDataGroup);
   virtual bool isContextApplicable (const BFDataGroupId &idDataGroup);
   virtual bool hasContextChanged (const BFDataGroupId &idDataGroup);
protected:
   virtual SEVERITY setFeeDefault (const BFDataGroupId &idDataGroup);
   virtual SEVERITY doValidateField ( const BFFieldId &idField, 
                                      const DString &strValue, 
                                      const BFDataGroupId &idDataGroup
                                    );
private:
   bool isApplicableForRedCode ( const BFDataGroupId &idDataGroup);
   bool withdrawalFeeExists (const BFDataGroupId &idDataGroup);
   bool shouldIgnoreSetup (const BFDataGroupId &idDataGroup);
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/WithdrawalFee.hpp-arc  $
//
//   Rev 1.3   Dec 08 2004 22:08:36   popescu
//PET 1117/06, more fees
//
//   Rev 1.2   Nov 17 2004 16:16:06   popescu
//PET 1117/06, Trade processing fees
//
//   Rev 1.1   Nov 15 2004 14:50:14   popescu
//PET 1117/06, .NET synch changes
//
//   Rev 1.0   Nov 15 2004 13:40:18   popescu
//Initial revision.
//
//   Rev 1.1   Nov 09 2004 16:49:12   popescu
//PET 1117/06, Trade processing
//
//   Rev 1.0   Nov 05 2004 17:06:46   popescu
//Initial Revision
//
//   Rev 1.1   Nov 04 2004 17:37:00   popescu
//PET 1117/06, Trade processing
//
//   Rev 1.0   Nov 04 2004 11:03:40   popescu
//Initial revision.
//
 */