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
// ^FILE   : FundAlloc.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 25/03/02
//
// ^CLASS    : FundAlloc
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : common interface for all fund allocations
//
//******************************************************************************

#include <ifastcbo\abstractalloc.hpp>

class AcctAlloc;
class SeqFundValidation;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE FundAlloc : public AbstractAlloc
{
public:
   // X-structors
   FundAlloc( BFAbstractCBO &parent );
   virtual ~FundAlloc( void );

   SEVERITY initDefault(BFAbstractCBO* pDefaultAlloc, const BFDataGroupId& idDataGroup);

   virtual SEVERITY getSplitCommissionList ( SplitCommissionList *&pSplitCommissionList, const BFDataGroupId& idDataGroup, bool bCreate = true, bool bGetDefault = false ) = 0;
   SEVERITY isInternationalWire(const DString& strSettleCurrency, const DString& strCountryCode,
                                bool &bIsInternationalWire, const BFDataGroupId& idDataGroup);
   bool isMarginEligible(const BFDataGroupId& idDataGroup);
   SEVERITY validateParentFundClass(const BFDataGroupId& idDataGroup);

protected:

   //overwritten inhereted public methods 
   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   virtual  SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
   virtual void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );

   SEVERITY getMFAccount( MFAccount *&pAcctOut, const BFDataGroupId& idDataGroup );
   const AcctAlloc* getParentAcctAlloc();

   SEVERITY setFundClassCode(const BFDataGroupId& idDataGroup);
   SEVERITY setFundNumber(const BFDataGroupId& idDataGroup);
   virtual SEVERITY getSeqFundValidation( SeqFundValidation *&pSeqFundValidation,
                                          const BFDataGroupId& idDataGroup);
   SEVERITY setAllocFields(const BFDataGroupId& idDataGroup);
   void setAllocFieldsReadOnly(const BFDataGroupId& idDataGroup, bool bReadOnly=true);
   //return true if seg fund validation is required for derived class, else false
   virtual bool isSegFundValidationReq() = 0;
   virtual bool isClassRequired(const BFDataGroupId& idDataGroup){return true;};

   SEVERITY validateFundCodeCash( const DString& strValue, const BFDataGroupId& idDataGroup,bool bCashValid ); 
   SEVERITY validateFractional(const DString& strValue, const BFDataGroupId& idDataGroup);
   SEVERITY validateAmount( const DString& strValue, const BFDataGroupId& idDataGroup );

   bool isSegCotClient();
   virtual SEVERITY validateFundClassAccNumDate ( const BFDataGroupId& idDataGroup );  
   SEVERITY validateFundClassCertificate  (const BFDataGroupId& idDataGroup);
   bool isSEGFund ( const DString& fundCode);

private :

   //validations
   SEVERITY validateFundCode( const DString& strValue, const BFDataGroupId& idDataGroup ) ;
   SEVERITY validateClassCode( const DString& strValue, const BFDataGroupId& idDataGroup ) ;
   SEVERITY validateFundClass( const BFDataGroupId& idDataGroup ) ;
   SEVERITY validateFundNumber( const DString& strValue, const BFDataGroupId& idDataGroup ) ;   
   
   bool m_bSettingFundClass;
   bool m_bSettingFundNumber;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundAlloc.hpp-arc  $
//
//   Rev 1.19   Mar 05 2012 11:56:32   dchatcha
//P0186484 FN05 - SEG Trade Processing.
//
//   Rev 1.18   Oct 26 2009 16:32:02   jankovii
//PET157825 FN08 FN11 FN14 AMS Gaps
//
//   Rev 1.17   Jun 15 2005 15:48:04   porteanm
//PET1024 FN40 - Guarantee Adjustments.
//
//   Rev 1.16   Nov 14 2004 14:41:18   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.15   Nov 06 2004 00:41:02   popescu
//PET 1117/06, synch changes
//
//   Rev 1.14   Jul 07 2003 11:36:40   YINGBAOL
//cosmetic changes
//
//   Rev 1.13   Mar 21 2003 18:10:28   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.12   Feb 12 2003 16:45:40   KOVACSRO
//Added isMarginEligible()
//
//   Rev 1.11   Jan 12 2003 18:54:42   KOVACSRO
//Added isClassRequired
//
//   Rev 1.10   Nov 12 2002 11:28:02   KOVACSRO
//Added isSegFundValidationReq() to clarify which allocations require this validation.
//
//   Rev 1.9   Oct 09 2002 23:54:30   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.8   Aug 29 2002 12:52:28   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.7   Aug 19 2002 15:20:24   KOVACSRO
//Added setAllocFieldsReadOnly;
//
//   Rev 1.6   Jun 07 2002 17:36:28   KOVACSRO
//Added International Wire.
//
//   Rev 1.5   24 May 2002 15:17:06   KOVACSRO
//Added some private members.
//
//   Rev 1.4   22 May 2002 18:21:04   PURDYECH
//BFData Implementation
//
//   Rev 1.3   08 May 2002 16:37:18   KOVACSRO
//Added setAllocFields()
//
//   Rev 1.2   29 Apr 2002 15:58:12   KOVACSRO
//Added initDefault()
//
//   Rev 1.1   12 Apr 2002 17:04:26   KOVACSRO
//More implementation.
 * 
 *
*/