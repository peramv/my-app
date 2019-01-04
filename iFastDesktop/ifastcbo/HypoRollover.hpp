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
// ^FILE   : HypoRollover.hpp
// ^AUTHOR : Yingbao Li
// ^DATE   : April, 2004
//
// ^CLASS    : HypoRollover
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include <ifastcbo\Rollover.hpp>
#include <ifastcbo\hypotradeacb.hpp>


#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE HypoRollover : public Rollover,public HypoTradeACBInterface
{

public:
   HypoRollover( BFAbstractCBO &parent );
   ~HypoRollover();		

	SEVERITY init (
         const DString &dstrAccountNum, 
         const BFDataGroupId& idDataGroup );

protected:	  
	virtual SEVERITY doValidateField( const BFFieldId &idField, 
			          	                const DString& strValue, 
				                         const BFDataGroupId& idDataGroup ); 
	
	virtual bool isHypo()	{ return true; }
	virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField, 
															const BFDataGroupId& idDataGroup );



};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//