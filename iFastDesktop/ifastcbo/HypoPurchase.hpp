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
// ^FILE   : HypoPurchase.hpp
// ^AUTHOR : Monica Vadeanu
// ^DATE   : April, 2004
//
// ^CLASS    : HypoPurchase
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include <ifastcbo\Purchase.hpp>
#include <ifastcbo\hypotradeacb.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE HypoPurchase : public Purchase, public HypoTradeACBInterface
{

public:
   HypoPurchase( BFAbstractCBO &parent );
   ~HypoPurchase();		

	SEVERITY init( const DString &dstrAccountNum, const BFDataGroupId& idDataGroup );

protected:	   
	virtual SEVERITY doValidateField( const BFFieldId &idField, 
			          	                const DString& strValue, 
				                         const BFDataGroupId& idDataGroup ); 

	virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField, 
															const BFDataGroupId& idDataGroup );

	virtual bool isHypo()	{ return true; }


};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/HypoPurchase.hpp-arc  $
//
//   Rev 1.3   Nov 14 2004 14:44:26   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.2   May 25 2004 10:04:58   YINGBAOL
//PET985:implement FundName
//
//   Rev 1.1   May 19 2004 17:39:12   YINGBAOL
//PET985: make hypo work
//
//   Rev 1.0   Apr 26 2004 13:44:10   VADEANUM
//Initial revision.
//
