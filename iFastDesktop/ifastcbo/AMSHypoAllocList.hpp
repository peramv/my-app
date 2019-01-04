#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by Internation Financial Data Services
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2003 by Internation Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : AmsHypoAllocList.hpp
// ^AUTHOR : Thanisorn Sangkrajang
// ^DATE   : July 24, 2017
//
// ^CLASS    : AMSHypoAllocList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\fundalloclist.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE AMSHypoAllocList : public FundAllocList
{
public:
   // X-structors
   AMSHypoAllocList( BFAbstractCBO &parent );
   virtual ~AMSHypoAllocList( void );
   SEVERITY initNew( const BFDataGroupId& idDataGroup,
                             bool bGetDefault = true,
                             const DString& dstrTrack = I_("N"),
                             const DString& dstrPageName = NULL_STRING );
   SEVERITY initExisting( const DString& dstrTrack = I_("N"),
                                  const DString& dstrPageName = NULL_STRING);
   SEVERITY addNewAllocation( const DString& strKey, 
                              const BFDataGroupId& idDataGroup,
                              bool bGetDefault = true, 
                              bool bCopyParent = false,
                              bool bAddChildren = true){assert(0);return NO_CONDITION;};
   SEVERITY addExistingAllocation( const DString& strKey, 
                                   const BFDataGroupId& idDataGroup,
                                   bool bAddChildren = true){assert(0);return NO_CONDITION;};
   SEVERITY doCopyCurrAlloc( DString dstrToFundNumber,
							 DString dstrFundCode,
							 DString dstrClassCode,
							 DString dstrAllocPrcnt,
							 const BFDataGroupId& idDataGroup);	
protected:
   SEVERITY doCreateNewObject( BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup );
   SEVERITY doDeleteObject (const DString &strKey, const BFDataGroupId& idDataGroup, bool bIsObjectDestroyed);
   SEVERITY doCreateObject( const BFData &data, BFCBO *&pObjOut );
   SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   	
private :



};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AMSHypoAllocList.hpp-arc  $
//
//   Rev 1.0   Jul 23 2003 09:24:06   Thanisorn S.
//Initial Revision
//

*/