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
// ^FILE   : DefFundAlloc.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 27/03/02
//
// ^CLASS    : DefFundAlloc
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : default fund allocation 
//
//******************************************************************************

#ifndef FUNDALLOC_HPP
   #include <ifastcbo\FundAlloc.hpp>
#endif 

class DefAccAlloc;
class FundLmtOverrideList; //IN2818924 - DSK_AMS Validation for CDIC

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class AcqFeeInquiry;

class IFASTCBO_LINKAGE DefFundAlloc : public FundAlloc
{
public:
   // X-structors
   DefFundAlloc( BFAbstractCBO &parent );
   virtual ~DefFundAlloc( void );
   SEVERITY initNew( const BFDataGroupId& idDataGroup,
                     const DString& dstrTrack = I_("N"),
                     const DString& dstrPageName = NULL_STRING );
   SEVERITY getSplitCommissionList ( SplitCommissionList *&pSplitCommissionList, const BFDataGroupId& idDataGroup, bool bCreate = true,bool bGetDefault = false  );
   SEVERITY initExisting(const BFData &data);
   //for default allocations it doesn't make sense to initDefault (they ARE default)
   SEVERITY initDefault(BFAbstractCBO* pDefaultAlloc, const BFDataGroupId& idDataGroup){assert(0);return(NO_SEVERITY);};

   //IN2818924 - DSK_AMS Validation for CDIC
    bool getBankruptcyAppliedFlag(){return m_bBankruptcyApplied; };  

protected:

   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
   void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );
   SEVERITY loadSubstitutions( const BFDataGroupId& idDataGroup );
	bool isSegFundValidationReq(){return true;};
   SEVERITY setAllocFields(const BFDataGroupId& idDataGroup);
   bool isClassRequired(const BFDataGroupId& idDataGroup);

   //IN2818924 - DSK_AMS Validation for CDIC
    bool isFieldsDisabledBaseOnRuleType( const DString& fundCode,
											    const DString& classCode,
												const DString& ruleType, 
                                                const BFDataGroupId &idDataGroup);
   SEVERITY getFundLmtOverrideList ( FundLmtOverrideList *&pFundLmtOverrideList,
                                              const DString& transType,
                                              const DString& fundCode,
                                              const DString& classCode,
                                              const BFDataGroupId &idDataGroup);

private :

   //validations
   SEVERITY validateFundCode( const DString& strValue, const BFDataGroupId& idDataGroup ) ;
   SEVERITY validateClassCode( const DString& strValue, const BFDataGroupId& idDataGroup ) ;
   SEVERITY validateFeeFund( const BFDataGroupId& idDataGroup ) ;
   //cross edit validations
   SEVERITY validateFundClass( const BFDataGroupId& idDataGroup ) ;
   SEVERITY validateTransTypeFundClass( const BFDataGroupId& idDataGroup );
   SEVERITY validateFundClassInGroup(const BFDataGroupId& idDataGroup);
   SEVERITY validateFundInGroup(const BFDataGroupId& idDataGroup);
   SEVERITY validateClassType(const BFDataGroupId& idDataGroup);
   SEVERITY validateFundType(const BFDataGroupId& idDataGroup);
   SEVERITY validateFundClassType(const BFDataGroupId& idDataGroup);
   SEVERITY validateAllocPercentage(const BFDataGroupId& idDataGroup);

   //related changes
   SEVERITY transTypeRelChanges(const BFDataGroupId& idDataGroup);

   //other
   bool isFundGroupApplicable(const BFDataGroupId& idDataGroup);
   bool isBrokerAllowed       (const DString &dstrTransType,
                               const DString &dstrAccountNum,
                               const DString &dstrFundCode, 
                               const DString &dstrClassCode,
                               const BFDataGroupId &idDataGroup );
   bool isFELCommGCOn(const BFDataGroupId& idDataGroup);
   bool isRESPFELCommApplicable(const BFDataGroupId& idDataGroup);
   bool isBrokerFundValidationApplicable(const DString &dstrTransType, const BFDataGroupId& idDataGroup);
   SEVERITY validateBrokerFund(const DString &dstrBroker,
                               const DString &dstrTransType,
                               const DString &dstrAccountNum,
                               const DString &dstrFundCode, 
                               const DString &dstrClassCode, 
                               const BFDataGroupId &idDataGroup );

   SEVERITY getAcqFeeInquiry  (AcqFeeInquiry *&pAcqFeeInquiry, const BFDataGroupId& idDataGroup);
   SEVERITY validateTransType( const BFDataGroupId& idDataGroup );

   bool m_bBankruptcyApplied; //IN2818924 - DSK_AMS Validation for CDIC
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DefFundAlloc.hpp-arc  $
//
//   Rev 1.17   Jan 31 2012 07:18:04   panatcha
//IN2818924 - DSK_AMS Validation for CDIC
//
//   Rev 1.16   Apr 30 2010 17:34:40   popescu
//PET165541_FN01_QESI - RESP Gap_Dsk_NASU - Fixed FEL Comm fee applicable
//
//   Rev 1.15   16 Dec 2008 09:34:22   kovacsro
//PET22486 - FN03 - RESP Grant Commission - code review
//
//   Rev 1.14   Dec 11 2008 09:28:46   sopitwek
//PET22486 - FN03 - RESP Grant Commission
//
//   Rev 1.13   Nov 14 2004 14:30:32   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.12   Nov 06 2004 00:40:12   popescu
//PET 1117/06, synch changes
//
//   Rev 1.11   Apr 25 2003 14:25:46   HERNANDO
//Prudential Broker Level Fee - PET792.FN07.2 - Added validateAllocPercentage.
//
//   Rev 1.10   Mar 21 2003 18:02:58   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.9   Jan 14 2003 17:27:24   KOVACSRO
//Added validateFundClassType
//
//   Rev 1.8   Jan 12 2003 18:38:12   KOVACSRO
//Added FundGroup related methods for FC rebalancing
//
//   Rev 1.7   Nov 12 2002 11:27:10   KOVACSRO
//Added isSegFundValidationReq() to clarify which allocations require this validation.
//
//   Rev 1.6   Oct 09 2002 23:54:12   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.5   Aug 29 2002 12:52:08   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.4   Aug 06 2002 09:55:12   KOVACSRO
//loadSubstitutions protected
//
//   Rev 1.3   22 May 2002 18:21:30   PURDYECH
//BFData Implementation
//
//   Rev 1.2   29 Apr 2002 15:57:38   KOVACSRO
//Added initDefault()
//
//   Rev 1.1   12 Apr 2002 17:03:02   KOVACSRO
//More implementation.
 * 
 *
*/