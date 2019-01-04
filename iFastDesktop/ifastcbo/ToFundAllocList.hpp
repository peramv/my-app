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
// ^FILE   : ToFundAllocList.hpp
// ^AUTHOR : Yingbao  Li 
// ^DATE   : 22/05/03
//
// ^CLASS    : ToFundAllocList
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

class ToFundAllocList;
class FromFundAllocList;
class IFASTCBO_LINKAGE GetFromToFundAllocListInterFace
{
public:
	GetFromToFundAllocListInterFace(){} //no implementation
	virtual SEVERITY getToFundAllocList(ToFundAllocList *&pToFundAllocList, 
					const BFDataGroupId& idDataGroup, bool bCreate = true) = 0;

	virtual SEVERITY getFromFundAllocList(FromFundAllocList *&pFromFundAllocList, 
						const BFDataGroupId& idDataGroup, bool bCreate =  true ) = 0;

};

class IFASTCBO_LINKAGE ToFundAllocList : public FundAllocList
{
public:

   // X-structors
   ToFundAllocList( BFAbstractCBO &parent );
   virtual ~ToFundAllocList( void );
   SEVERITY initExisting( const DString& dstrTrack = I_("N"),
                          const DString& dstrPageName = NULL_STRING );
   SEVERITY initNew( const BFDataGroupId& idDataGroup,
                     bool bGetDefault = true,
                     const DString& dstrTrack = I_("N"),
                     const DString& dstrPageName = NULL_STRING );

   virtual void setAllAllocsFndClsValidFlag(bool isValid, const BFDataGroupId& idDataGroup);

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
	SEVERITY validateFundTransfer( const BFDataGroupId& idDataGroup );
	SEVERITY validateFundClassTransferAllowed(const BFDataGroupId& idDataGroup);

   bool isAllDummy(const BFDataGroupId& idDataGroup);
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ToFundAllocList.hpp-arc  $
//
//   Rev 1.3   Nov 14 2004 14:57:16   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.2   Jun 24 2003 09:43:46   YINGBAOL
//implement FundClass Transfer allowed
//
//   Rev 1.1   Jun 13 2003 16:02:22   YINGBAOL
//add validateFundTransfer
//
//   Rev 1.0   Jun 09 2003 11:05:06   YINGBAOL
//Initial revision.
//
 *
*/