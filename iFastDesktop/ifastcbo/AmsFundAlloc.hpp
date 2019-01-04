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
// ^FILE   : AMSFundAlloc.hpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Nov. 7, 02
//
// ^CLASS    : AMSFundAlloc
// ^SUBCLASS :  AbstractFundAlloc
//
// ^CLASS DESCRIPTION : Ams fund allocation 
//
//******************************************************************************
#include <ifastcbo\FundAlloc.hpp>

class FundLmtOverrideList; //IN2818924 - DSK_AMS Validation for CDIC

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE AmsFundAlloc : public FundAlloc
{
public:
   // X-structors
   AmsFundAlloc( BFAbstractCBO &parent );
   virtual ~AmsFundAlloc( void );

   SEVERITY initNew( const BFDataGroupId& idDataGroup,
                     const DString& dstrTrack = I_("N"),
                     const DString& dstrPageName = NULL_STRING );
   SEVERITY initExisting(const BFData &data);

   SEVERITY getSplitCommissionList ( SplitCommissionList *&pSplitCommissionList, 
      const BFDataGroupId& idDataGroup, bool bCreate = true, bool bGetDefault = false  ){pSplitCommissionList = NULL;return NO_SEVERITY;};

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
    bool getBankruptcyAppliedFlag(){return m_bBankruptcyApplied; };   

protected:

   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
	SEVERITY validateFundClass( const BFDataGroupId& idDataGroup ); 
	bool isSegFundValidationReq(){return false;};

private :
	void checkUpdatePermission(const BFDataGroupId& idDataGroup);
	bool m_bBankruptcyApplied;//IN2818924 - DSK_AMS Validation for CDIC

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AmsFundAlloc.hpp-arc  $
//
//   Rev 1.7   Jan 31 2012 07:37:58   panatcha
//IN2818924 - DSK_AMS Validation for CDIC
//
//   Rev 1.6   Nov 06 2004 00:39:54   popescu
//PET 1117/06, synch changes
//
//   Rev 1.5   Mar 21 2003 17:59:04   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.4   Nov 29 2002 14:13:14   KOVACSRO
//Added isSegFundValidationReq.
//
//   Rev 1.3   Nov 29 2002 08:58:42   KOVACSRO
//made it work globally, rather than just for AMS screens.
//
//   Rev 1.2   Nov 22 2002 14:29:08   YINGBAOL
//add validateFundClass
//
//   Rev 1.1   Nov 19 2002 13:27:52   YINGBAOL
//add check permission
//
//   Rev 1.0   Nov 13 2002 10:01:52   YINGBAOL
//Initial Revision



*/