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
//    Copyright 1999 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : ShrAllocType.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 24/03/02
//
// ^CLASS    : ShrAllocType
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : former shareholder level allocation
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

class FundDetail;
class DefAcctAllocList;
//class AbstractAllocList;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE ShrAllocType : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   ShrAllocType( BFAbstractCBO &parent );
   virtual ~ShrAllocType( void );

   SEVERITY initNew( const BFDataGroupId& idDataGroup,
                     const DString& dstrTrack = I_("N"),
                     const DString& dstrPageName = NULL_STRING );                
   SEVERITY initExisting(const BFData &data);
   //void modelOffer(AbstractAllocList *Model, const BFDataGroupId& idDataGroup);
   SEVERITY getAccountAllocationList(DefAcctAllocList *&pAcctAllocList, const BFDataGroupId& idDataGroup, bool bCreate = true); 
   //returns true if this ShrAllocType has allocations for the specified account number
   bool hasDefaultAllocations(const DString& strAccNum, const BFDataGroupId& idDataGroup);

   void clearAllocations(const BFDataGroupId& idDataGroup);
   void allowRBROEffectiveDateChange( bool blAllow );

protected:

   /**
    * returns a pointer to the Shareholder CBO
    */
   MFCanBFCbo *getTopLevelCBO();


   //overwritten inhereted protected methods 
   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   //SEVERITY  doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
   void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );

private :
   // copy constructor
   ShrAllocType( const ShrAllocType& copy );
   // = Operator
   ShrAllocType& operator= ( const ShrAllocType& copy );
   SEVERITY validateTransTypeEffDate( const BFDataGroupId& idDataGroup ) ;
   SEVERITY loadSubstitutions( const BFDataGroupId& idDataGroup );

   bool _allowRBROEffectiveDateChange;

};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/ShrAllocType.hpp-arc  $
//
//   Rev 1.8   19 Oct 2007 16:19:02   kovacsro
//IN#1038318 - added rej erros / hard edit to prevent users from entering future dated Stop dates on AMS and modifying Effective Date for RB/RO default allocations on Allocation screen
//
//   Rev 1.7   Nov 14 2004 14:55:32   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.6   Mar 21 2003 18:24:46   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.5   Dec 04 2002 17:34:26   HERNANDO
//Added clearAllocations.
//
//   Rev 1.4   Nov 18 2002 13:37:08   KOVACSRO
//Added hasDefaultAllocations for a particular Account number
//
//   Rev 1.3   Oct 09 2002 23:55:02   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.2   Aug 29 2002 12:53:40   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.1   22 May 2002 18:20:00   PURDYECH
//BFData Implementation
//
