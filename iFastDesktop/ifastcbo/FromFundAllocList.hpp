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
// ^FILE   : FromFundAllocList.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 22/07/02
//
// ^CLASS    : FromFundAllocList
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

class IFASTCBO_LINKAGE FromFundAllocList : public FundAllocList
{
public:

   // X-structors
   FromFundAllocList( BFAbstractCBO &parent );
   virtual ~FromFundAllocList( void );
   SEVERITY initExisting( const DString& dstrTrack = I_("N"),
                          const DString& dstrPageName = NULL_STRING );
   SEVERITY initNew( const BFDataGroupId& idDataGroup,
                     bool bGetDefault = true,
                     const DString& dstrTrack = I_("N"),
                     const DString& dstrPageName = NULL_STRING );
	SEVERITY validateTransOut( const BFDataGroupId& idDataGroup );
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
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FromFundAllocList.hpp-arc  $
//
//   Rev 1.2   Nov 14 2004 14:41:16   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.1   Jun 13 2003 15:55:20   YINGBAOL
//add validateTransOut
//
//   Rev 1.0   Jun 09 2003 11:03:14   YINGBAOL
//Initial revision.
//

 * 
 *
*/