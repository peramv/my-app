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
// ^FILE   : FundAllocList.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 25/03/02
//
// ^CLASS    : FundAllocList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : common interface for all the fund allocation lists
//
//******************************************************************************

#ifndef ABSTRACTALLOCLIST_HPP
   #include <ifastcbo\AbstractAllocList.hpp>
#endif

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE FundAllocList : public AbstractAllocList
{
public:
   // ctor/dtor
   FundAllocList( BFAbstractCBO &parent );
   virtual ~FundAllocList( void );

   SEVERITY initNew( const BFDataGroupId& idDataGroup,
                     bool bGetDefault = true,
                     const DString& dstrTrack = I_("N"),
                     const DString& dstrPageName = NULL_STRING );
   SEVERITY clearAllocations( const BFDataGroupId& idDataGroup );
   SEVERITY createSplitCommLists ( const BFDataGroupId& idDataGroup );
   void setDefaultSplitCommFlags( const BFDataGroupId& idDataGroup );
   void getAllocCurrency( DString& dstrFundAllocCurrency, const BFDataGroupId& idDataGroup);
   SEVERITY hasInternationalWireAlloc(const DString& strSettleCurrency, const DString& strCountryCode,
                                      bool &bIsInternationalWire, const BFDataGroupId& idDataGroup);
   bool isMarginEligible(const BFDataGroupId& idDataGroup);
protected:

   SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup, bool bSkip100PercentValidation = false );
   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   SEVERITY setListFields(const BFDataGroupId& idDataGroup);
   //calls getShrDefAllocList, but can be overriten by derived class
   SEVERITY getDefaultAllocList(AbstractAllocList*& pDefaultAllocationList, const BFDataGroupId& idDataGroup);
   //gets the default allocation list using shareholder default allocations for the specified TransType
   SEVERITY getShrDefAllocList(AbstractAllocList* &pDefaultAllocationList, const BFDataGroupId& idDataGroup);
   //gets the default allocation list using shareholder default allocations for AMS rebalancing TransType
   SEVERITY getRebalDefAllocList(AbstractAllocList* &pDefaultAllocationList, const BFDataGroupId& idDataGroup);
   //gets the default allocation list using account AMS allocations
   SEVERITY getAMSDefAllocList(AbstractAllocList* &pDefaultAllocationList, const BFDataGroupId& idDataGroup);

   SEVERITY validateMulticurrency(const BFDataGroupId& idDataGroup);

private :

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundAllocList.hpp-arc  $
//
//   Rev 1.14   Nov 14 2004 14:41:22   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.13   Aug 25 2003 18:19:24   WINNIE
//Full Redemption Code enhancement : Add new input parameter to indicate skipping the validation in AbstractAllocList which perform the total percentage validation 
//
//   Rev 1.12   Mar 21 2003 18:10:32   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.11   Feb 12 2003 16:39:22   KOVACSRO
//Added isMarginEligible()
//
//   Rev 1.10   Dec 31 2002 13:50:56   KOVACSRO
//validateMultiCurrency is not virtual anymore.
//
//   Rev 1.9   Nov 29 2002 10:47:28   KOVACSRO
//Added support for different kind of default allocations.
//
//   Rev 1.7   Oct 09 2002 23:54:32   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.6   Aug 29 2002 12:52:30   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.5   Jun 07 2002 17:36:42   KOVACSRO
//International Wire modifications.
//
//   Rev 1.4   22 May 2002 18:21:04   PURDYECH
//BFData Implementation
//
//   Rev 1.3   08 May 2002 16:37:46   KOVACSRO
//Added getAllocCurrency().
//
//   Rev 1.2   29 Apr 2002 15:59:50   KOVACSRO
//more implementation.
//
//   Rev 1.1   12 Apr 2002 17:04:50   KOVACSRO
//More implementation.
 * 
 *
*/