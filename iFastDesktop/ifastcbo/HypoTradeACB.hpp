#pragma once
#define DISABLE_MACRO_REDEFINITION_WARNINGS 1
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
//    Copyright 2004 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : HypoTradeACB.hpp
// ^AUTHOR : Monica Vadeanu
// ^DATE   : April, 2004
//
// ^CLASS    : HypoTradeACB
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include <ifastcbo\Purchase.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class Trade;

class IFASTCBO_LINKAGE HypoTradeACB : public MFCanBFCbo, private boost::noncopyable
{
public:
   HypoTradeACB( BFAbstractCBO &parent );
   ~HypoTradeACB();		
	SEVERITY init(		
		const BFDataGroupId& idDataGroup,
		const DString& dstrTrack = I_("N"),
      const DString& dstrPageName = NULL_STRING  );       	
};

class IFASTCBO_LINKAGE HypoTradeACBInterface
{
public:  
   HypoTradeACBInterface(){}
   ~HypoTradeACBInterface(){}
	SEVERITY	getHypoTradeACB( Trade* pTrade, 
				 HypoTradeACB* &pAcb, const BFDataGroupId& idDataGroup,bool bInquiry );
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/HypoTradeACB.hpp-arc  $
//
//   Rev 1.2   Nov 14 2004 14:45:00   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.1   May 19 2004 17:39:40   YINGBAOL
//PET985: make hypo work
//
//   Rev 1.0   Apr 26 2004 13:41:32   VADEANUM
//Initial revision.
//
