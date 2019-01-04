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
// ^FILE      : XferOutFee.hpp
// ^AUTHOR    : Serban Popescu
// ^DATE      : November 2004
//
// ^CLASS     : XferOutFee
// ^SUBCLASS  :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "transfeerate.hpp"
///#endif

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class SplitCommissionList;
class IFASTCBO_LINKAGE XferOutFee : public TransFeeRate
{
public:
   XferOutFee (BFAbstractCBO &parent);
   virtual ~XferOutFee();
   virtual bool isSystemApplicable (const BFDataGroupId &idDataGroup);
   virtual bool isContextApplicable (const BFDataGroupId &idDataGroup);
   virtual bool hasContextChanged (const BFDataGroupId &idDataGroup);
   virtual SEVERITY restore ( BFCBO &rpParent, 
                              const BFDataGroupId &idDataGroup);
protected:
   virtual SEVERITY doValidateField ( const BFFieldId &idField, 
                                      const DString &strValue, 
                                      const BFDataGroupId &idDataGroup);
   virtual SEVERITY doApplyRelatedChanges ( const BFFieldId &idField, 
                                            const BFDataGroupId &idDataGroup);
   virtual SEVERITY setFeeMinMax (const BFDataGroupId &idDataGroup);
   virtual SEVERITY setFeeDefault (const BFDataGroupId &idDataGroup);
   virtual SEVERITY setFeeType (const BFDataGroupId &idDataGroup);
   virtual SEVERITY setFeeProperties (const BFDataGroupId &idDataGroup);
private:
   bool isApplicableForFund (const BFDataGroupId &idDataGroup);
   bool isNotROAXferEnvironment (const BFDataGroupId &idDataGroup);

   DString _acqFeeDefault;
   DString _side;
   SplitCommissionList *_pFromSideSplitCommissionList;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/XferOutFee.hpp-arc  $
//
//   Rev 1.7   Jul 04 2005 19:05:38   popescu
//Incident # 347073 - split commission is charged on the To side for environments where ROA is applicable.
//
//   Rev 1.6   May 18 2005 09:03:48   yingbaol
//PET1203,FN01 Commission-Class A enhancement
//
//   Rev 1.5   Mar 03 2005 08:14:06   popescu
//PET 1117/06 added restore functionality for fees, when modifying a pending trade, even if the TransFee table is not populated
//
//   Rev 1.4   Jan 31 2005 10:05:42   popescu
//PTS 10038324, set charge option field to read only, there is no set-up for it.
//
//   Rev 1.3   Jan 28 2005 11:08:04   popescu
//PTS 10038324, fees display issues
//
//   Rev 1.2   Jan 28 2005 06:58:18   aguilaam
//PTS 10038324, fees display issues
//
//   Rev 1.1   Jan 21 2005 16:55:52   popescu
//PTS 10038132, not show the fees if from fund/ and class are not entered
//
//   Rev 1.0   Nov 17 2004 15:56:10   popescu
//Initial revision.
//
//   Rev 1.2   Nov 15 2004 16:22:32   popescu
//PET 1117/06, more synch to .NET changes
//
//   Rev 1.0   Nov 10 2004 09:31:16   popescu
//Initial revision.
//
//   Rev 1.0   Nov 06 2004 00:35:10   popescu
//Initial revision.
//
//   Rev 1.0   Nov 04 2004 11:03:24   popescu
//Initial revision.
//
 */