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
// ^FILE   : MktIndexMaster.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : MktIndexMaster
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

class MktIndexFundsList;

class IFASTCBO_LINKAGE MktIndexMaster : public MFCanBFCbo
{
public:

   MktIndexMaster( BFAbstractCBO &parent );
   virtual ~MktIndexMaster();

   SEVERITY init(const BFData&   data );
	void		initNew(const BFDataGroupId& idDataGroup );
	SEVERITY getMktIndexFundsList( MktIndexFundsList *&pMktIndexFundsList,
						const BFDataGroupId& idDataGroup,bool bCreate = true );

protected:

   virtual SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );

private:

	void setFieldStates(const BFDataGroupId& idDataGroup);
	SEVERITY validateMktIndexCode(const DString& strValue,const BFDataGroupId& idDataGroup );
	SEVERITY validateMktIndexFunds(const DString& strValue, const BFDataGroupId& idDataGroup);
	SEVERITY validateDaysBasis(const BFDataGroupId& idDataGroup);
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/MktIndexMaster.hpp-arc  $
//
//   Rev 1.3   Jan 16 2012 14:33:16   wp040027
//P0188394_Performance Fees - Benchmark Upload
//
//   Rev 1.2   Nov 14 2004 14:50:34   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.1   Mar 21 2003 18:19:24   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.0   Jan 23 2003 10:31:58   HERNANDO
//Initial Revision
//