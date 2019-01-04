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
// ^FILE   : EUSDValidation.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : EUSDValidation
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


class IFASTCBO_LINKAGE EUSDValidation : public MFCanBFCbo
{
public:
   EUSDValidation( BFAbstractCBO &parent );
   virtual ~EUSDValidation();

   SEVERITY init (const DString& accountNumber, const DString& fund, 
	              const DString& fundClass, const DString& tradeDate,
				  const DString& dstrTrack= I_("N"),
                  const DString& dstrPageName = NULL_STRING);

   bool isBackDatedTradeAllowed (const BFDataGroupId& idDataGroup);

protected:
};

