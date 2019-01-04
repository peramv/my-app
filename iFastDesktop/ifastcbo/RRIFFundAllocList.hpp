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
// ^FILE   : RRIFFundAllocList.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 22/07/02
//
// ^CLASS    : RRIFFundAllocList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : trade fund allocation list
//
//******************************************************************************

#include <ifastcbo\fundalloclist.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE RRIFFundAllocList : public FundAllocList
{
public:

   // X-structors
   RRIFFundAllocList( BFAbstractCBO &parent );
   virtual ~RRIFFundAllocList( void );
   SEVERITY initExisting( const DString& dstrTrack = I_("N"),
                          const DString& dstrPageName = NULL_STRING );
   SEVERITY initNew( const BFDataGroupId& idDataGroup,
                     bool bGetDefault = true,
                     const DString& dstrTrack = I_("N"),
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

   SEVERITY doCreateNewObject( BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup );
   SEVERITY doCreateObject( const BFData &data, BFCBO *&pObjOut );

   SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   //no need to override base
   //void getFormattedAmount(const BFDataGroupId& idDataGroup, DString &dstrValue);
   SEVERITY setListFields(const BFDataGroupId& idDataGroup);
   SEVERITY loadSubstitutions( const BFDataGroupId& idDataGroup );

private :

   bool isAllDummy(const BFDataGroupId& idDataGroup);
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RRIFFundAllocList.hpp-arc  $
//
//   Rev 1.6   Nov 14 2004 14:53:30   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.5   Mar 21 2003 18:23:00   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.4   Jan 12 2003 15:57:28   KOVACSRO
//Added isAllDummy()
//
//   Rev 1.3   Oct 09 2002 23:54:54   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.2   Aug 29 2002 12:53:32   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.1   Aug 19 2002 15:23:38   KOVACSRO
//using base class getFormattedAmount.
//
//   Rev 1.0   Aug 06 2002 10:51:20   KOVACSRO
//Initial revision.
 * 
 *
*/