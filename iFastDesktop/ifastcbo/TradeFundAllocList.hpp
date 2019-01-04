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
// ^FILE   : TradeFundAllocList.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 08/04/02
//
// ^CLASS    : TradeFundAllocList
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

class IFASTCBO_LINKAGE TradeFundAllocList : public FundAllocList
{
public:

   // X-structors
   TradeFundAllocList( BFAbstractCBO &parent );
   virtual ~TradeFundAllocList( void );
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
   void getStrKey( DString &strKey, const BFData *data = NULL );
   void setFullRedemption ( const BFDataGroupId& idDataGroup, bool isFullRedeem  );
   void changeFieldsForRebook();
   virtual void setAllAllocsFndClsValidFlag(bool isValid, const BFDataGroupId& idDataGroup);

protected:

   SEVERITY doCreateNewObject( BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup );

   SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   void getFormattedAmount(const BFDataGroupId& idDataGroup, DString &dstrValue);
   SEVERITY getDefaultAllocList(AbstractAllocList*& pDefaultAllocationList, const BFDataGroupId& idDataGroup);
   
private :

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TradeFundAllocList.hpp-arc  $
//
//   Rev 1.10   Jul 08 2005 09:33:44   Yingbaol
//PET1235,FN01:transaction cancellation rebook
//
//   Rev 1.9   Nov 14 2004 14:58:00   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.8   Aug 25 2003 18:32:58   WINNIE
//Full Redemption code for not closing account : add new field FullRedem to indicate if a non close account redemption code is indicated. New method SetFullRedemption to invoke TradeFundAlloc to disable AllocPercentage and set to 100%; change doValidateAll to skip the total percentage validation if non close account full redemption code is indicated.
//
//   Rev 1.7   Mar 21 2003 18:27:16   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.6   Feb 18 2003 10:36:06   FENGYONG
//Add getStrKey
//
//   Rev 1.5   Nov 29 2002 10:54:20   KOVACSRO
//overrite getDefaultAllocList
//
//   Rev 1.4   Oct 09 2002 23:55:10   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.3   Aug 29 2002 12:53:54   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.2   22 May 2002 18:19:14   PURDYECH
//BFData Implementation
//
//   Rev 1.1   08 May 2002 16:41:56   KOVACSRO
//More implementation.
//
//   Rev 1.0   29 Apr 2002 16:56:24   KOVACSRO
//Initial revision.
 * 
 *
*/