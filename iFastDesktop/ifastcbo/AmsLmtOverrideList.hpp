#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by Internation Financial Data Services
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2003 by Internation Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : AmsLmtOverrideList.hpp
// ^AUTHOR : May Lin
// ^DATE   : July 03, 2003
//
// ^CLASS    : AmsLmtOverrideList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

class AmsLmtOverride;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE AmsLmtOverrideList : public MFCanBFCbo, private boost::noncopyable
{

public:
   AmsLmtOverrideList( BFAbstractCBO &parent );
   virtual ~AmsLmtOverrideList( void );

   // Initialize function
   SEVERITY init(  const DString& dstrAmsCode 
				 , const DString& dstrEffectiveDate
				 , const DString& dstrAMSType
				 , const DString& dstrTrack = I_( "N" )
				 , const DString& dstrPageName = NULL_STRING
				 );

   SEVERITY getValueByType ( 
							  const DString& dstrLimitationCode
							, DString &dstrFieldValue
							, const BFDataGroupId& idDataGroup 
						   );
   SEVERITY getAmsLmtOverridebyType( const DString dstrRuleType
									,AmsLmtOverride *&pAmsLmtOverride
									,const BFDataGroupId& idDataGroup
									);
	void ModelAMS(AmsLmtOverrideList *Model, const BFDataGroupId& idDataGroup);
/*
   SEVERITY getAMSLmtOverride( AmsLmtOverride*& pAMSLmtOverride,
      const DString dstrRuleType, const DString& dstrTaxJuris, 
      const DString& dstrProvResid, const DString& dstrAccountType, 
      const DString& dstrTaxType, const DString& dstrAcctDesign, const BFDataGroupId& idDataGroup );
*/
   SEVERITY canPurchase( const DString& dstrTaxJuris, const DString& dstrProvResid,
                         const DString& dstrAccountType, const DString& dstrTaxType,
                         const DString& dstrAcctDesign, const BFDataGroupId& idDataGroup );

   bool isAMSRestrictionMet ( AmsLmtOverride*& pAMSLmtOverride, const DString& dstrTaxJuris, 
         const DString& dstrProvResid, const DString& dstrAccountType, const DString& dstrTaxType, 
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
   SEVERITY getMore();
	bool canAMSCodeSetUpForAccount( const DString& dstrAccountNum,
										     const BFDataGroupId& idDataGroup,unsigned int& uErrCode );

  /**
   * AMS Rule for Account Minimum Balance
   * 
   * @param dstrAccountNum
   * @param idDataGroup
   * @return 
   */
	SEVERITY canRebalanceAccount( const DString &dstrAccountNum, const BFDataGroupId &idDataGroup );

protected:
   SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
   SEVERITY doCreateNewObject(BFCBO *& pBase, DString & strKey, const BFDataGroupId& idDataGroup );
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );

private:
	BFData _requestData;
   DString _dstrAMSCode; // Use to store the AMS Code for the current AMS Limitations List.
	DString _dstrAMSType;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AmsLmtOverrideList.hpp-arc  $
//
//   Rev 1.7   Apr 09 2004 09:57:54   VADEANUM
//PET1005 FN11 - AMS Gaps.
//
//   Rev 1.6   Aug 14 2003 13:03:20   HSUCHIN
//Change the fund override from pass by copy to pass by reference.
//
//   Rev 1.5   Aug 12 2003 10:20:48   HSUCHIN
//added private variable to store AMSCode
//
//   Rev 1.4   Aug 11 2003 09:48:16   YINGBAOL
//add canAMSCodeSetUpForAccount method
//
//   Rev 1.3   Aug 11 2003 09:40:44   linmay
//added dovalidateall
//
//   Rev 1.2   Jul 30 2003 14:16:14   linmay
//modified init()
//
//   Rev 1.1   Jul 25 2003 17:05:38   HSUCHIN
//added support for limit override checks such as stop purchase, stop PAC etc. etc.
//
//   Rev 1.0   Jul 23 2003 09:24:06   linmay
//Initial Revision
//

*/