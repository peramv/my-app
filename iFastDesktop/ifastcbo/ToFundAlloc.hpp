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
//    Copyright 2003 by Internatioanl Financial.
//
//
//******************************************************************************
//
// ^FILE   : ToFundAlloc.hpp
// ^AUTHOR : Yingbao Li
// ^DATE   : May 27, 2003
//
// ^CLASS    : ToFundAlloc
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

class IFASTCBO_LINKAGE ToFundAlloc : public FundAlloc
{
public:
   // X-structors
   ToFundAlloc( BFAbstractCBO &parent );
   virtual ~ToFundAlloc( void );
   SEVERITY initNew( const BFDataGroupId& idDataGroup,
                     const DString& dstrTrack = I_("N"),
                     const DString& dstrPageName = NULL_STRING );
   SEVERITY initExisting(const BFData &data);
   SEVERITY initDefault(BFAbstractCBO* pDefaultAlloc, const BFDataGroupId& idDataGroup);
   SEVERITY getSplitCommissionList ( SplitCommissionList *&pSplitCommissionList, const BFDataGroupId& idDataGroup, bool bCreate = true,bool bGetDefault = false  );

protected:

   virtual SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
   virtual void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );
   BFData *getDataForModelOffer();
   SEVERITY loadSubstitutions( const BFDataGroupId& idDataGroup );
	bool isSegFundValidationReq(){return true;};
	virtual SEVERITY doPreSetField( const BFFieldId& idField, DString & strValue, const BFDataGroupId& idDataGroup, bool bFormatted );
    SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );

private :

   //validations
   SEVERITY validateFundClass( const BFDataGroupId& idDataGroup ) ;
   SEVERITY validateToSoftCapCheck( const BFDataGroupId& idDataGroup );

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ToFundAlloc.hpp-arc  $
//
//   Rev 1.4   Jan 14 2009 17:16:28   wongsakw
//IN1550993 Invalid warning message when fund entered in lower case for LIF allocation
//
//   Rev 1.3   Nov 14 2004 14:57:14   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.2   Nov 06 2004 00:42:36   popescu
//PET 1117/06, synch changes
//
//   Rev 1.1   Jul 07 2003 11:36:54   YINGBAOL
//cosmetic changes
//
//   Rev 1.0   Jun 09 2003 11:04:58   YINGBAOL
//Initial revision.

 *
 *
*/