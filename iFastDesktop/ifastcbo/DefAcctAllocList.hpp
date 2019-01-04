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
// ^FILE   : DefAcctAllocList.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 25/03/02
//
// ^CLASS    : DefAcctAllocList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : Default account allocation list
//
//******************************************************************************

#include <ifastcbo\acctalloclist.hpp>

class ShrAllocTypeList;
class ShrAllocType;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE DefAcctAllocList : public AcctAllocList
{
public:

   // X-structors
   DefAcctAllocList( BFAbstractCBO &parent );
   virtual ~DefAcctAllocList( void );

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
protected:
   SEVERITY initDefaultAllocationList(const BFDataGroupId& idDataGroup);

   SEVERITY doCreateNewObject( BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup );
   SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );

private:

   ShrAllocTypeList* getShrAllocTypeList();
   SEVERITY loadSubstitutions( const BFDataGroupId& idDataGroup );

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DefAcctAllocList.hpp-arc  $
//
//   Rev 1.7   Nov 14 2004 14:30:28   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.6   Mar 21 2003 18:02:48   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.5   Oct 09 2002 23:54:12   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.4   Aug 29 2002 12:52:06   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.3   22 May 2002 18:21:30   PURDYECH
//BFData Implementation
//
//   Rev 1.2   10 May 2002 10:26:12   KOVACSRO
//Added addExistingAllocation().
//
//   Rev 1.1   12 Apr 2002 17:02:36   KOVACSRO
//More implementation.
 * 
 *
*/
