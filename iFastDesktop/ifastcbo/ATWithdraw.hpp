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
//    Copyright 2005 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : ATWithdraw.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : Redemption
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


class IFASTCBO_LINKAGE ATWithdraw :  public Redemption
{
public:
   ATWithdraw (BFAbstractCBO &parent);
   virtual ~ATWithdraw();
protected:
  virtual SEVERITY doInit (const BFDataGroupId &idDataGroup);
  virtual SEVERITY validateESGSettle (const DString &strValue, const BFDataGroupId &idDataGroup);
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ATWithdraw.hpp-arc  $
//
//   Rev 1.2   Mar 01 2006 13:58:10   ZHANGCEL
//PET1334 - FN01 -- Added logic for ESGSettle enhancement
//
//   Rev 1.1   Aug 11 2005 10:26:30   popescu
//PET 1235 - Reeebok, few changes
//
//   Rev 1.0   Jul 09 2005 13:02:08   Yingbaol
//Initial revision.
//
 
*/