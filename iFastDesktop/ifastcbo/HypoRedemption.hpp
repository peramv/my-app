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
// ^FILE   : HypoRedemption.hpp
// ^AUTHOR : Monica Vadeanu
// ^DATE   : April, 2004
//
// ^CLASS    : HypoRedemption
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include <ifastcbo\redemption.hpp>
#include <ifastcbo\hypotradeacb.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE HypoRedemption : public Redemption,public HypoTradeACBInterface
{

public:
   HypoRedemption( BFAbstractCBO &parent );
   ~HypoRedemption();		

	SEVERITY init( const DString &dstrAccountNum, const BFDataGroupId& idDataGroup );
protected:	   
	virtual SEVERITY doValidateField( const BFFieldId &idField, 
			          	                const DString& strValue, 
				                         const BFDataGroupId& idDataGroup );     

	virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField, 
															const BFDataGroupId& idDataGroup );

	virtual bool isHypo()	{ return true; }

   virtual SEVERITY transTypeRelatedChanges (
         const BFDataGroupId &idDataGroup)
			{ return NO_CONDITION;}



};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/HypoRedemption.hpp-arc  $
//
//   Rev 1.5   Nov 14 2004 14:44:44   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.4   Nov 06 2004 00:41:12   popescu
//PET 1117/06, synch changes
//
//   Rev 1.3   Jun 02 2004 16:04:44   YINGBAOL
//PTS10030671:Add transtyperelatedchange method
//
//   Rev 1.2   May 25 2004 10:05:02   YINGBAOL
//PET985:implement FundName
//
//   Rev 1.1   May 19 2004 17:39:20   YINGBAOL
//PET985: make hypo work
//
//   Rev 1.0   Apr 26 2004 13:48:42   VADEANUM
//Initial revision.
//
