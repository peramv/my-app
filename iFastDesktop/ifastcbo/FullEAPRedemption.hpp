#pragma once

//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confIdential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2013 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE      : FullEAPRedemption.hpp
// ^AUTHOR    : 
// ^DATE      : Jan 2013
//
// ^CLASS     : FullEAPRedemption
// ^SUBCLASS  :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <boost\utility.hpp>
#include "redemption.hpp"
///#endif

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

//Forward declarations
class Trade;

class IFASTCBO_LINKAGE FullEAPRedemption : public Redemption
{
public:
   FullEAPRedemption (BFAbstractCBO &parent);
   virtual ~FullEAPRedemption();

protected:

   virtual SEVERITY doInit (const BFDataGroupId &idDataGroup);
   virtual SEVERITY doInit (const BFData &data);
   virtual SEVERITY preInitWithDefaultValues (const BFDataGroupId &idDataGroup);
   virtual void doInitWithDefaultValues (const BFDataGroupId &idDataGroup);
   virtual SEVERITY doValidateField (const BFFieldId &idField, const DString &strValue, const BFDataGroupId &idDataGroup);
   virtual SEVERITY doValidateAll (const BFDataGroupId &idDataGroup, long lValidateGroup);
   virtual SEVERITY doApplyRelatedChanges (const BFFieldId &idField, const BFDataGroupId &idDataGroup );
   virtual bool supportsAllocations (const BFDataGroupId &idDataGroup);
   virtual bool supportsFromAllocations (const BFDataGroupId &idDataGroup);
   virtual SEVERITY raiseFullRedemptionMessage( const BFDataGroupId &idDataGroup);

private:

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/FullEAPRedemption.hpp-arc  $
//
