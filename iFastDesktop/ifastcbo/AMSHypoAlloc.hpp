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
//    Copyright 2002 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : AMSFundAlloc.hpp
// ^AUTHOR : Thanisorn Sangkrajang
// ^DATE   : Jul. 26, 2017
//
// ^CLASS    : AMSFundAlloc
// ^SUBCLASS :  AbstractFundAlloc
//
// ^CLASS DESCRIPTION : AMS Hypothetical report proposed fund allocation.
//
//******************************************************************************
#include <ifastcbo\FundAlloc.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE AMSHypoAlloc : public FundAlloc
{
public:
   // X-structors
   AMSHypoAlloc( BFAbstractCBO &parent );
   virtual ~AMSHypoAlloc( void );

   SEVERITY initNew( const BFDataGroupId& idDataGroup,
                     const DString& dstrTrack = I_("N"),
                     const DString& dstrPageName = NULL_STRING );
   SEVERITY initExisting(const BFData &data);

   SEVERITY getSplitCommissionList ( SplitCommissionList *&pSplitCommissionList, 
      const BFDataGroupId& idDataGroup, bool bCreate = true, bool bGetDefault = false  ){pSplitCommissionList = NULL;return NO_SEVERITY;};


protected:

   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
	SEVERITY validateFundClass( const BFDataGroupId& idDataGroup );

	bool isSegFundValidationReq(){return false;};
private :
	/*void checkUpdatePermission(const BFDataGroupId& idDataGroup);*/
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AmsFundAlloc.hpp-arc  $
//   Rev 1.0   Nov 13 2002 10:01:52   YINGBAOL
//Initial Revision
*/