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
// ^FILE   : HypoExchange.hpp
// ^AUTHOR : Monica Vadeanu
// ^DATE   : April, 2004
//
// ^CLASS    : HypoExchange
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include <ifastcbo\exchange.hpp>
#include <ifastcbo\hypotradeacb.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif
class IFASTCBO_LINKAGE HypoExchange : public Exchange,public HypoTradeACBInterface
{

public:
   HypoExchange( BFAbstractCBO &parent );
   ~HypoExchange();		

	SEVERITY init (
         const DString &dstrAccountNum, 
         const BFDataGroupId& idDataGroup );
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
// $Log:   Y:/VCS/BF iFAST/ifastcbo/HypoExchange.hpp-arc  $
//
//   Rev 1.4   Nov 14 2004 14:44:24   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.3   May 25 2004 10:04:48   YINGBAOL
//PET985:implement FundName
//
//   Rev 1.2   May 19 2004 17:39:06   YINGBAOL
//PET985: make hypo work
//
//   Rev 1.1   May 10 2004 20:27:54   popescu
//PET 985, FN 01, LSIF Trade Entry
//
//   Rev 1.0   Apr 26 2004 13:52:26   VADEANUM
//Initial revision.
//
