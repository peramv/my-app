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
// ^FILE   : DefAcctAlloc.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 25/03/02
//
// ^CLASS    : DefAcctAlloc
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : common interface for all account allocations
//
//******************************************************************************

#include <ifastcbo\acctalloc.hpp>

class ShrAllocType;
class FundAllocList;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE DefAcctAlloc : public AcctAlloc
{
public:
   // X-structors
   DefAcctAlloc( BFAbstractCBO &parent );
   virtual ~DefAcctAlloc( void );

   SEVERITY initNew( const BFDataGroupId& idDataGroup,
                     const DString& dstrTrack = I_("N"),
                     const DString& dstrPageName = NULL_STRING );
   SEVERITY initExisting(const BFData &data);
   //for default allocations it doesn't make sense to initDefault (they ARE default)
   SEVERITY initDefault(BFAbstractCBO* pDefaultAlloc, const BFDataGroupId& idDataGroup){assert(0);return(NO_SEVERITY);};

protected:

   void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );
   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
   SEVERITY loadSubstitutions( const BFDataGroupId& idDataGroup );

private :

   //validations
   SEVERITY validateAccountNum( const DString& strValue, const BFDataGroupId& idDataGroup ) ;

   SEVERITY validateFundGroupType( const BFDataGroupId& idDataGroup );
   SEVERITY validateAccountNumTransType(const BFDataGroupId& idDataGroup);
   SEVERITY validateAllocPercentage( const BFDataGroupId& idDataGroup );
   SEVERITY validateRebalancePercent( const BFDataGroupId& idDataGroup );

   //related changes
   SEVERITY transTypeRelChanges(const BFDataGroupId& idDataGroup);

   //other
   bool isFundGroupApplicable(const BFDataGroupId& idDataGroup);
   SEVERITY loadFundGroupSubst(const BFDataGroupId& idDataGroup);
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DefAcctAlloc.hpp-arc  $
//
//   Rev 1.11   Nov 14 2004 14:30:24   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.10   Apr 28 2003 15:10:04   HERNANDO
//PTS 10016054 - Added validatedRebalancePercent.
//
//   Rev 1.9   Apr 12 2003 18:48:02   HERNANDO
//PTS 10015905 - Validation for Alloc Percentages for Foreign Content Rebalancing.
//
//   Rev 1.8   Mar 21 2003 18:02:44   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.7   Jan 12 2003 18:35:28   KOVACSRO
//Added FundGroup related methods.
//
//   Rev 1.6   Oct 09 2002 23:54:12   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.5   Aug 29 2002 12:52:06   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.4   Aug 06 2002 09:54:46   KOVACSRO
//load substitutions protected
//
//   Rev 1.3   22 May 2002 18:21:30   PURDYECH
//BFData Implementation
//
//   Rev 1.2   29 Apr 2002 15:57:06   KOVACSRO
//Added initDefault()
//
//   Rev 1.1   12 Apr 2002 17:01:32   KOVACSRO
//More implementation.
 * 
 *
*/
