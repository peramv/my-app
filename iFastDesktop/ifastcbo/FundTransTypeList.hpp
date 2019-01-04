#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by Internation Financial Data Services
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2003 by Internation Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : FundTransTypeList.hpp
// ^AUTHOR : Winnie Shiu
// ^DATE   : January 09, 2003
//
// ^CLASS    : FundTransTypeList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

class FundTransType;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE FundTransTypeList : public MFCanBFCbo, private boost::noncopyable
{

public:
   FundTransTypeList( BFAbstractCBO &parent );
   virtual ~FundTransTypeList( void );
   // Initialize function
   SEVERITY init();
   SEVERITY getFundTransType (
      const DString &transType, 
      FundTransType *&pFundTransType, 
      const BFDataGroupId &idDataGroup);
private :

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundTransTypeList.hpp-arc  $
//
//   Rev 1.5   Nov 14 2004 14:43:28   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.4   Nov 04 2004 17:37:52   popescu
//PET 1117/06, Trade processing
//
//   Rev 1.3   Jun 25 2004 16:38:28   popescu
//PST 10031525, fund limitation override issues
//
//   Rev 1.2   Mar 21 2003 19:52:14   PURDYECH
//Sync 1.0.1.0 back to trunk
//
//   Rev 1.0.1.0   Mar 21 2003 18:12:26   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.0   Jan 12 2003 16:05:46   WINNIE
//Initial revision.

*/