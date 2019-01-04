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
// ^FILE   : AMSFundAllocList.hpp
// ^AUTHOR : Yingbao Li	
// ^DATE   : Nov. 6/02
//
// ^CLASS    : AMSFundAllocList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : Ams fund allocation list
//
//******************************************************************************

#include <ifastcbo\fundalloclist.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE AmsFundAllocList : public FundAllocList
{
public:
   // X-structors
   AmsFundAllocList( BFAbstractCBO &parent );
   virtual ~AmsFundAllocList( void );
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
   //IN2818924 - DSK_AMS Validation for CDIC
   bool isBankruptcyApplied( const BFDataGroupId &idDataGroup);
   bool isBankruptcyApplied( DString& fundCode,
							 DString& classCode,
							 const BFDataGroupId &idDataGroup);
   

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
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AmsFundAllocList.hpp-arc  $
//
//   Rev 1.6   Jan 31 2012 07:39:16   panatcha
//IN2818924 - DSK_AMS Validation for CDIC
//
//   Rev 1.5   Feb 22 2004 19:11:38   HERNANDO
//PTS10026642 - Added doDeleteObject.
//
//   Rev 1.4   Mar 21 2003 17:59:10   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.3   Dec 31 2002 13:48:32   KOVACSRO
//removed unused methods.
//
//   Rev 1.2   Nov 29 2002 08:59:12   KOVACSRO
//made it work globally, rather than just for AMS screens.
//
//   Rev 1.1   Nov 27 2002 11:47:54   YINGBAOL
//add getTotalPercentage
//
//   Rev 1.0   Nov 13 2002 10:01:52   YINGBAOL
//Initial Revision
//

 * 
 *
*/