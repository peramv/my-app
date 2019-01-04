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
// ^FILE   : DefFundAllocList.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 27/03/02
//
// ^CLASS    : DefFundAllocList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : default fund allocation list
//
//******************************************************************************

#include <ifastcbo\fundalloclist.hpp>

class ShrAllocTypeList;


#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE DefFundAllocList : public FundAllocList
{
public:

   // X-structors
   DefFundAllocList( BFAbstractCBO &parent );
   virtual ~DefFundAllocList( void );

   SEVERITY initExisting( const DString& dstrTrack = I_("N"),
                          const DString& dstrPageName = NULL_STRING );

   SEVERITY addNewAllocation( const DString& strKey, 
                              const BFDataGroupId& idDataGroup,
                              bool bGetDefault = true, 
                              bool bCopyParent = false,
                              bool bAddChildren = true);
   SEVERITY addExistingAllocation( const DString& strKey, 
                                   const BFDataGroupId& idDataGroup,
                                   bool bAddChildren = true);
   //IN2818924 - DSK_AMS Validation for CDIC
   bool isBankruptcyApplied(const BFDataGroupId& idDataGroup);

protected:

   SEVERITY initDefaultAllocationList(const BFDataGroupId& idDataGroup);
   SEVERITY doCreateNewObject( BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup );

   SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   SEVERITY setListFields(const BFDataGroupId& idDataGroup);

private :

   ShrAllocTypeList* getShrAllocTypeList();
   SEVERITY loadSubstitutions( const BFDataGroupId& idDataGroup );
  
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DefFundAllocList.hpp-arc  $
//
//   Rev 1.9   Jan 31 2012 07:16:50   panatcha
//IN2818924 - DSK_AMS Validation for CDIC
//
//   Rev 1.8   Nov 14 2004 14:30:34   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.7   Mar 21 2003 18:03:04   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.6   Jan 12 2003 18:40:08   KOVACSRO
//Override setListFields
//
//   Rev 1.5   Oct 09 2002 23:54:12   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.4   Aug 29 2002 12:52:08   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.3   22 May 2002 18:21:26   PURDYECH
//BFData Implementation
//
//   Rev 1.2   10 May 2002 10:27:58   KOVACSRO
//Added addExistingAllocation().
//
//   Rev 1.1   12 Apr 2002 17:03:22   KOVACSRO
//More implementation.
 * 
 *
*/