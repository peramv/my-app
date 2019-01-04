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
// ^FILE      : HistoricalInfoSearchCriteria.hpp
// ^AUTHOR    : Serban Popescu
// ^DATE      : 01/08/2003
//
// ^CLASS     : HistoricalInfoSearchCriteria
// ^SUBCLASS  :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

//Forward declarations
class FundClassRules;

class IFASTCBO_LINKAGE HistoricalInfoSearchCriteria : public MFCanBFCbo, private boost::noncopyable
{
public:
   HistoricalInfoSearchCriteria( BFAbstractCBO &parent );
   virtual ~HistoricalInfoSearchCriteria();

   SEVERITY init(const BFDataGroupId& idDataGroup);
protected:
   virtual SEVERITY doApplyRelatedChanges(const BFFieldId& idField, 
      const BFDataGroupId& idDataGroup);
private:
   FundClassRules* m_pFundClassRules;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/HistoricalInfoSearchCriteria.hpp-arc  $
//
//   Rev 1.2   Nov 14 2004 14:44:06   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.1   Mar 21 2003 18:13:28   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.0   Feb 06 2003 11:54:26   popescu
//Initial revision.
 */