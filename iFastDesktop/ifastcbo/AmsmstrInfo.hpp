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
//    Copyright 2002, By International Financial Data Service
//
//
//******************************************************************************
//
// ^FILE   : AmsMstrInfo.hpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Nov. 6,2002
//
// ^CLASS    : AmsMstrInfo
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif
class AmsFundAllocList;
class FundMasterList;
class AmsLmtOverrideList;
class ErrMsgRulesList;
class AMSDeltaAllocList;

class IFASTCBO_LINKAGE AmsMstrInfo : public MFCanBFCbo
{
public:
   AmsMstrInfo( BFAbstractCBO &parent );
   virtual ~AmsMstrInfo();

   SEVERITY init(const BFData&   data );
	void		initNew(const BFDataGroupId& idDataGroup );
	SEVERITY getAMSFundAllocList( AmsFundAllocList *&pAmsFundAllocList,
						const BFDataGroupId& idDataGroup,bool bCreate = true );
	SEVERITY getAMSDeltaAllocList(AMSDeltaAllocList *&pAMSDeltaAllocList,const BFDataGroupId& idDataGroup, bool bCreate = true);
	SEVERITY initAMSDeltaAllocList(AmsFundAllocList *pAMSFundAllocList, AMSDeltaAllocList *&pAMSDeltaAllocList, const BFDataGroupId& idDataGroup);

	void setAMSType(const DString& dstrAMSType,const BFDataGroupId& idDataGroup);
	SEVERITY getAmsLmtOverrideList( 
									  AmsLmtOverrideList *& pAmsLmtOverrideList
									, const BFDataGroupId& idDataGroup 
									, bool bInq = true 
									, bool bRemObj = false
									, bool nbCreateNew = false
									);
	void ModelAMS(AmsMstrInfo *Model, const BFDataGroupId& idDataGroup);

   SEVERITY canPurchase( const DString& dstrTaxJuris, const DString& dstrProvResid,
                          const DString& dstrAccountType, const DString& dstrTaxType,
                          const DString& dstrAcctDesign, const BFDataGroupId& idDataGroup );
   SEVERITY minPurchase( const DString& dstrTaxJuris, const DString& dstrProvResid,
                          const DString& dstrAccountType, const DString& dstrTaxType,
                          const DString& dstrAcctDesign, const DString& dstrAmount,
                          bool& bFundOverride, bool bInitialPurchase,
                          const BFDataGroupId& idDataGroup );
   SEVERITY maxRedeem( const DString& dstrTaxJuris, const DString& dstrProvResid,
                          const DString& dstrAccountType, const DString& dstrTaxType,
                          const DString& dstrAcctDesign, const double dPercent,
                          bool& bFundOverride, const BFDataGroupId& idDataGroup );
   SEVERITY canRedeem( const DString& dstrTaxJuris, const DString& dstrProvResid,
                          const DString& dstrAccountType, const DString& dstrTaxType,
                          const DString& dstrAcctDesign, const BFDataGroupId& idDataGroup );
   SEVERITY minPAC( const DString& dstrTaxJuris, const DString& dstrProvResid,
                          const DString& dstrAccountType, const DString& dstrTaxType,
                          const DString& dstrAcctDesign, const DString& dstrAmount,
                          bool& bFundOverride, const BFDataGroupId& idDataGroup );
   SEVERITY canPAC( const DString& dstrTaxJuris, const DString& dstrProvResid,
                          const DString& dstrAccountType, const DString& dstrTaxType,
                          const DString& dstrAcctDesign, const BFDataGroupId& idDataGroup );
   SEVERITY canSWP( const DString& dstrTaxJuris, const DString& dstrProvResid,
                          const DString& dstrAccountType, const DString& dstrTaxType,
                          const DString& dstrAcctDesign, const BFDataGroupId& idDataGroup );
   SEVERITY minSWP( const DString& dstrTaxJuris, const DString& dstrProvResid,
                          const DString& dstrAccountType, const DString& dstrTaxType,
                          const DString& dstrAcctDesign, const DString& dstrSWPAmt,
                          bool& bFundOverride, const BFDataGroupId& idDataGroup );
   SEVERITY canATIn( const DString& dstrTaxJuris, const DString& dstrProvResid,
                          const DString& dstrAccountType, const DString& dstrTaxType,
                          const DString& dstrAcctDesign, const BFDataGroupId& idDataGroup );
   SEVERITY canATOut( const DString& dstrTaxJuris, const DString& dstrProvResid,
                          const DString& dstrAccountType, const DString& dstrTaxType,
                          const DString& dstrAcctDesign, const BFDataGroupId& idDataGroup );
   SEVERITY canTransferIn( const DString& dstrTaxJuris, const DString& dstrProvResid,
                          const DString& dstrAccountType, const DString& dstrTaxType,
                          const DString& dstrAcctDesign, const BFDataGroupId& idDataGroup );
   SEVERITY canTransferOut( const DString& dstrTaxJuris, const DString& dstrProvResid,
                          const DString& dstrAccountType, const DString& dstrTaxType,
                          const DString& dstrAcctDesign, const BFDataGroupId& idDataGroup );
   SEVERITY checkGrandfatheredDate (const DString& dstrTradeDate, const BFDataGroupId& idDataGroup, bool bError = true );
	bool     isGrandFatherDateStamped(const BFDataGroupId& idDataGroup);
	bool canAMSCodeSetUpForAccount( const DString& dstrAccountNum,const BFDataGroupId& idDataGroup,unsigned int& uErrCode );
   bool isFundInAMS ( const DString& dstrFundCode, const DString dstrClassCode, const BFDataGroupId& idDataGroup );
   bool isAMSC(const BFDataGroupId& idDataGroup);


protected:
   virtual SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
	virtual void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );


private:
	void setFieldStates(const BFDataGroupId& idDataGroup);
	SEVERITY validateThreshold(const DString& strValue, const BFDataGroupId& idDataGroup );
	SEVERITY validateAMSCode(const DString& strValue, const BFDataGroupId& idDataGroup );
	SEVERITY validateFundAlloc(const DString& strValue, const BFDataGroupId& idDataGroup);
	SEVERITY validateEffectiveDate(const DString& strValue, const BFDataGroupId& idDataGroup );
	SEVERITY validateForeignRelFund(const DString& strValue, const BFDataGroupId& idDataGroup );
   SEVERITY validateAssocFund(const DString& strValue, const BFDataGroupId& idDataGroup );
 	SEVERITY validateRoundingFund(const DString& strValue, const BFDataGroupId& idDataGroup );
	SEVERITY validateFundCode( const DString& dstrFundCode, const BFDataGroupId& idDataGroup );
	SEVERITY validateFundClass( const DString& dstrFundCode, const DString& dstrClassCode, const BFDataGroupId& idDataGroup );
	SEVERITY validateRelFundClass( const DString& strValue, const BFDataGroupId& idDataGroup );
   SEVERITY validateAssocFundClass( const DString& strValue, const BFDataGroupId& idDataGroup );
	SEVERITY validateRoundingFundClass( const DString& strValue, const BFDataGroupId& idDataGroup );
	SEVERITY validateNextRebDate(const DString& strValue, const BFDataGroupId& idDataGroup );
	SEVERITY validateGrandFatherDate(const DString& strValue, const BFDataGroupId& idDataGroup );
	SEVERITY validateEffectiveGFDate(const DString& strValue, const BFDataGroupId& idDataGroup );
	SEVERITY DupCheck4AmsRec( const BFDataGroupId& idDataGroup );
	SEVERITY validateEffectiveNextRebDate(const DString& strValue, const BFDataGroupId& idDataGroup );
	bool getFundMasterList (); 
	bool isDomesticFund( const DString& dstrFundCode, const BFDataGroupId& idDataGroup );
	bool isBusinessDate ( const DString& strValue, const BFDataGroupId& idDataGroup );
	bool isLastBusDayOfWeek ( const DString& strValue, const BFDataGroupId& idDataGroup );
	void doRBFreqRelatedChanges(const BFDataGroupId& idDataGroup);
	void CalculateNextRebDate(const BFDataGroupId& idDataGroup);
	void doCurrencyRelatedChanges(const BFDataGroupId& idDataGroup);
	void isActiveRecord(const BFDataGroupId& idDataGroup);
	void getErrMsgValue( DString dstrErrNum,       
                         const BFDataGroupId& idDataGroup, 
                         DString& dstrErrValue );
   SEVERITY validateAMSRuleType(const DString& strValue, const BFDataGroupId& idDataGroup );

   SEVERITY setAMSFrequencySubstSet( const BFDataGroupId& idDataGroup );
   SEVERITY validateParentFundClassXEdit(const BFDataGroupId& idDataGroup);

	DString _initEffectiveDate;
	DString _initNextRebDate;
	DString _initGrandFatherDate;
	DString _initFreq;

    FundMasterList *_pFundMasterList;
	ErrMsgRulesList* _pErrMsgRulesList;

};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/AmsmstrInfo.hpp-arc  $
//
//   Rev 1.18   Jun 25 2007 11:57:52   porteanm
//PET 2360 FN02 - AMS - frequency.
//
//   Rev 1.17   Jun 22 2007 14:19:44   porteanm
//PET 2360 FN02 - AMS - work in progress.
//
//   Rev 1.16   Jun 18 2007 14:32:18   porteanm
//PET2360 FN02 - AIM AMS - Syst level.
//
//   Rev 1.15   Oct 03 2003 15:52:40   linmay
//PTS Ticket#10022366, schema change for view 260
//
//   Rev 1.14   Aug 16 2003 11:20:50   HSUCHIN
//added method isFundInAMS to check if fund/class passed in is in the AMS fund allocation list.
//
//   Rev 1.13   Aug 14 2003 13:03:28   HSUCHIN
//Change the fund override from pass by copy to pass by reference.
//
//   Rev 1.12   Aug 12 2003 10:23:18   HSUCHIN
//change checkGrandfatheredDate to have an additional parameter which determines whether or not a Error or warning message is raised.
//
//   Rev 1.11   Aug 11 2003 09:53:56   YINGBAOL
//add canAMSCodeSetUpForAccount method
//
//   Rev 1.10   Aug 09 2003 12:36:08   YINGBAOL
//add     isGrandFatherDateStamped.
//
//   Rev 1.9   Jul 30 2003 14:11:12   linmay
//added error etc.
//
//   Rev 1.8   Jul 25 2003 17:05:46   HSUCHIN
//added support for limit override checks such as stop purchase, stop PAC etc. etc.
//
//   Rev 1.7   Jul 23 2003 10:59:04   linmay
//added isActiveRecord
//
//   Rev 1.6   Jul 18 2003 11:35:22   linmay
//modified for CIBC AMS
//
//   Rev 1.5   Jun 06 2003 11:24:46   YINGBAOL
//add doinitwithdefaultvalue
//
//   Rev 1.4   Apr 21 2003 09:43:32   YINGBAOL
//reimpement AMSType logic.
//
//   Rev 1.3   Mar 21 2003 17:59:14   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.2   Dec 27 2002 12:45:06   linmay
//added ValidateFundAllocation function
//
//   Rev 1.1   Nov 19 2002 13:30:14   YINGBAOL
//added validation functions
//
//   Rev 1.0   Nov 13 2002 10:01:54   YINGBAOL
//Initial Revision
//

//