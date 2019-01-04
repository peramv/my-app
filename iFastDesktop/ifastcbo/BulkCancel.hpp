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
//    Copyright 2005 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : BulkCancel.hpp
// ^AUTHOR : Monica Porteanu
// ^DATE   : November 2005
//
// ^CLASS    : BulkCancel
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <boost\utility.hpp>
#include <ifastcbo\mfcancbo.hpp>
#include <ifastcbo\transcancel.hpp>

// Forward references

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class DilutionAllocList;

class IFASTCBO_LINKAGE BulkCancel : public TransCancel
{
public:
   
public:
   // X-structors
   BulkCancel (BFAbstractCBO &parent);
   virtual ~BulkCancel();

   // virtual in base class
   SEVERITY init (const BFData& data);
   
   SEVERITY restore( const BFDataGroupId &idDataGroup );  
   
   // virtual in base class
   SEVERITY getDilutionAllocList ( const BFDataGroupId& idDataGroup, 
					               DilutionAllocList *&pDilutionAllocList);
protected:
   // virtual in base class
   SEVERITY getBatchNum ( const BFDataGroupId &idDataGroup,
                          const DString &track = I_("N"),
                          const DString &pageName = NULL_STRING); 
   // virtual in base class
   SEVERITY setTransNum( const BFDataGroupId &idDataGroup );
   // virtual in base class
   SEVERITY setNewTransStatus( const BFDataGroupId &idDataGroup );
   // virtual in base class
   bool isModifiableBasedOnStatus( const BFDataGroupId &idDataGroup );
   // virtual in base class
   bool isIndividualTransCancelAllowed();      

	SEVERITY doApplyRelatedChanges ( const BFFieldId &idField, 
                                            const BFDataGroupId &idDataGroup);

	SEVERITY setDefaultSuppressIndicators( const BFDataGroupId &idDataGroup );
	void setSuppressIndicatorsPerm(const BFDataGroupId &idDataGroup);
	bool areSuppressIndicatorsModifiableBasedOnStatus( const BFDataGroupId &idDataGroup);
	SEVERITY setSuppressIndicatorsReadOnlyFlags(const BFDataGroupId &idDataGroup);
	SEVERITY setSuppressIndicatorsInactive(const BFDataGroupId &idDataGroup, const bool isNew );
	SEVERITY setSuppressIndicatorsSet( const BFDataGroupId &idDataGroup );
	SEVERITY setRbkSuppressIndicatorsSet( const BFDataGroupId &idDataGroup );

};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/BulkCancel.hpp-arc  $
//
//   Rev 1.8   Jan 12 2006 15:55:06   zhengcon
//PET1295_FN01: Trade Suppress Indicator for MCH and SR Files -- Trade Cancellation: Individual and rebook 
//
//   Rev 1.7   Nov 26 2005 17:31:36   porteanm
//PET1286 FN01 - Bulk Cancellation.
//
//   Rev 1.6   Nov 23 2005 17:11:02   porteanm
//PET1286 FN01 - Bulk Cancellation.
//
//   Rev 1.5   Nov 12 2005 13:46:12   porteanm
//PET 1286 FN01 - Bulk Cancellation.
//
//   Rev 1.4   Nov 12 2005 11:55:10   porteanm
//PET 1286 FN01 - Bulk Cancellation.
//
//   Rev 1.3   Nov 11 2005 17:15:50   porteanm
//PET 1286 FN01 - Bulk Cancellation.
//
//   Rev 1.2   Nov 09 2005 19:50:30   porteanm
//PET 1286 FN01 - Bulk Cancellation.
//
//   Rev 1.1   Nov 06 2005 14:00:50   porteanm
//PET 1286 FN01 - Bulk Cancellation - work in progress.
//
//   Rev 1.0   Nov 05 2005 15:07:44   porteanm
//Initial revision.
// 
*/