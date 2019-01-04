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
// ^FILE   : MktIndexValues.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : MktIndexValues
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

class IFASTCBO_LINKAGE MktIndexValues : public MFCanBFCbo
{
public:

   MktIndexValues( BFAbstractCBO &parent );
   virtual ~MktIndexValues();

   SEVERITY init(const BFData& data, const DString&  );
	void     initNew(const BFDataGroupId& idDataGroup, const DString&, const DString& dstrIndexCode );
	SEVERITY getMktIndexFundsList( MktIndexFundsList *&pMktIndexFundsList,
						const BFDataGroupId& idDataGroup,bool bCreate = true );

protected:

   virtual SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );

private:

   SEVERITY duplicateCheck( const BFDataGroupId& idDataGroup );
	void setFieldStates(const BFDataGroupId& idDataGroup);

   DString getInputDataType(const BFDataGroupId& idDataGroup);
   SEVERITY validateClosingValue( const BFDataGroupId& idDataGroup,const DString& dstrValue );
   SEVERITY validateHurdleRate( const BFDataGroupId& idDataGroup,const DString& dstrValue );
   void clearRequiredFlags( const BFDataGroupId& idDataGroup );
   bool isBetweenTwoIndex( MktIndexValuesList* pMktIndexValuesListToCheck,
									    const BFDataGroupId& idDataGroup,
										DString &dstrDate1,
										DString &dstrDate2);
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/MktIndexValues.hpp-arc  $
//
//   Rev 1.6   Jan 16 2012 14:34:08   wp040027
//P0188394_Performance Fees - Benchmark Upload
//
//   Rev 1.5   Nov 14 2004 14:50:38   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.4   May 16 2003 17:33:14   HERNANDO
//Initialize IndexCode.
//
//   Rev 1.3   Mar 21 2003 18:19:34   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.2   Feb 06 2003 10:40:30   HERNANDO
//Added duplicate check.
//
//   Rev 1.1   Jan 29 2003 18:34:24   HERNANDO
//Revised.
//
//   Rev 1.0   Jan 29 2003 11:49:42   HERNANDO
//Initial Revision
//