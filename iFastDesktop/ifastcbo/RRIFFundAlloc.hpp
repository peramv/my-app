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
// ^FILE   : RRIFFundAlloc.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 08/04/02
//
// ^CLASS    : RRIFFundAlloc
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : default fund allocation 
//
//******************************************************************************

#ifndef FUNDALLOC_HPP
   #include <ifastcbo\FundAlloc.hpp>
#endif 

class AcqFeeInquiry;
class SplitCommissionList;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE RRIFFundAlloc : public FundAlloc
{
public:
   // X-structors
   RRIFFundAlloc( BFAbstractCBO &parent );
   virtual ~RRIFFundAlloc( void );
   SEVERITY initNew( const BFDataGroupId& idDataGroup,
                     const DString& dstrTrack = I_("N"),
                     const DString& dstrPageName = NULL_STRING );
   SEVERITY initExisting(const BFData &data);
   SEVERITY initDefault(BFAbstractCBO* pDefaultAlloc, const BFDataGroupId& idDataGroup);
   SEVERITY getSplitCommissionList ( SplitCommissionList *&pSplitCommissionList, const BFDataGroupId& idDataGroup, bool bCreate = true,bool bGetDefault = false  );
   SEVERITY copyDataFromParent(const BFDataGroupId& idDataGroup);

protected:

   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
   void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );
   BFData *getDataForModelOffer();
   SEVERITY loadSubstitutions( const BFDataGroupId& idDataGroup );
	bool isSegFundValidationReq(){return true;};

private :

   //validations
   SEVERITY validateFundCode( const DString& strValue, const BFDataGroupId& idDataGroup ) ;
   SEVERITY validateClassCode( const DString& strValue, const BFDataGroupId& idDataGroup ) ;
   SEVERITY validateFundClass( const BFDataGroupId& idDataGroup ) ;
   SEVERITY validateAmount( const DString& strValue, const BFDataGroupId& idDataGroup );
   SEVERITY validatePercentage(const DString& strValue, const BFDataGroupId& idDataGroup);
   SEVERITY validateFractional(const DString& strValue, const BFDataGroupId& idDataGroup);

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RRIFFundAlloc.hpp-arc  $
//
//   Rev 1.7   Nov 14 2004 14:53:28   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.6   Nov 06 2004 00:42:34   popescu
//PET 1117/06, synch changes
//
//   Rev 1.5   Mar 21 2003 18:22:54   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.4   Nov 21 2002 17:29:40   KOVACSRO
//small clean-up
//
//   Rev 1.3   Nov 12 2002 11:28:32   KOVACSRO
//Added isSegFundValidationReq() to clarify which allocations require this validation.
//
//   Rev 1.2   Oct 09 2002 23:54:54   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.1   Aug 29 2002 12:53:32   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.0   Aug 06 2002 10:51:18   KOVACSRO
//Initial revision.
 *
 *
*/