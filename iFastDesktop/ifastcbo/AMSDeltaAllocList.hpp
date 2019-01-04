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
// ^FILE   : AMSDeltaAllocList.hpp
// ^AUTHOR : Thanisorn Sangkrajang
// ^DATE   : January 10, 2018
//
// ^CLASS    : AMSDeltaAllocList
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

class IFASTCBO_LINKAGE AMSDeltaAllocList : public MFCanBFCbo/*: public FundAllocList*/
{
public:
   // X-structors
   AMSDeltaAllocList( BFAbstractCBO &parent );
   virtual ~AMSDeltaAllocList( void );
   SEVERITY init(  const DString& dstrAmsCode 
				 , const DString& dstrEffectiveDate
				 , const DString& dstrAccountNum
				 , const DString& dstrAMSDeltaReqUUID
				 , const DString& dstrTrack = I_( "N" )
				 , const DString& dstrPageName = NULL_STRING
				 );

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
   void getTotalDeltaPrcnt(DString &strTotalDeltaPrcnt, const BFDataGroupId& idDataGroup, bool bFormatted = true);

protected:
   SEVERITY doCreateNewObject( BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup );
   SEVERITY doDeleteObject (const DString &strKey, const BFDataGroupId& idDataGroup, bool bIsObjectDestroyed);
   SEVERITY doCreateObject( const BFData &data, BFCBO *&pObjOut );
   SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   	
private :
   BFData _requestData;


};