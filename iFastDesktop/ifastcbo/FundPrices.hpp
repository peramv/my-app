#pragma once
#define DISABLE_MACRO_REDEFINITION_WARNINGS 1
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
//    Copyright 1998 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : FundPrices.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : FundPrices
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

class DSTCWorkSession;
class UnitFactorList;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE FundPrices : public MFCanBFCbo, private boost::noncopyable
{

public:

   FundPrices( BFAbstractCBO &parent );
   virtual ~FundPrices();
   SEVERITY init (const BFData &viewData);
   SEVERITY getUnitFactorsList (UnitFactorList *&pUnitFactorList, const BFDataGroupId& idDataGroup);
   SEVERITY initNew (const BFDataGroupId& idDataGroup);
   bool hasMultiplePrices(const BFDataGroupId & idDataGroup);

private:
   UnitFactorList *m_pUnitFactorList;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundPrices.hpp-arc  $
//
//   Rev 1.2   Nov 14 2004 14:42:58   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.1   Sep 17 2004 13:39:04   popescu
//PET1117 FN22 - revert fund factors dialog display to old logic
//
//   Rev 1.0   Sep 09 2004 11:27:38   HERNANDO
//Initial revision.
*/