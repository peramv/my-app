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
//    Copyright 2003, By International Financial Data Service
//
//
//******************************************************************************
//
// ^FILE   : InventorySummary.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : InventorySummary
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class InventoryDetailsList;

class IFASTCBO_LINKAGE InventorySummary : public MFCanBFCbo
{
public:

   InventorySummary( BFAbstractCBO &parent );
   virtual ~InventorySummary();

   SEVERITY init(const BFData&   data );
	void		initNew(const BFDataGroupId& idDataGroup );
	SEVERITY getInventoryDetailsList( InventoryDetailsList *&pInventoryDetailsList,
						const BFDataGroupId& idDataGroup, const DString& dstrInvSummary, bool bCreate = true );

protected:

   virtual SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );

};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/InventorySummary.hpp-arc  $
//
//   Rev 1.1   Nov 14 2004 14:48:42   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.0   May 19 2004 17:41:10   HERNANDO
//Initial revision.
//
//   Rev 1.1   Mar 21 2003 18:19:24   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.0   Jan 23 2003 10:31:58   HERNANDO
//Initial Revision
//