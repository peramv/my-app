#pragma once

//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : Shareholder.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : Shareholder
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif


class AccShrNumCheck;
class Address;
class AddressList;  //yingbao  move AddressList from MfAccount to Shareholder
class AccountMailingList;
class BankInstrList;
class Demographics;
class DirectTradingBankInstructionsList;
class MFAccount;
class MFAccountHoldingList;
class MFAccountList;
class RemarksList;
class ShareholderBankInstructionsList;
class ShrAllocTypeList;
class ShrFamilyList;
class ShrFundSponsorAgreementList;
class ShrFundBrokerList;
class FeeModelList;


namespace SHAREHOLDER_GROUPING
{
   extern IFASTCBO_LINKAGE const long SHAREHOLDER_INFO;
   extern IFASTCBO_LINKAGE const long SHAREHOLDER_ADDRESS;
}

namespace BANKLEVEL
{
   I_CHAR * const SHAREHOLDER = I_("Shareholder");;
   I_CHAR * const ACCOUNT = I_("Account");
}

class IFASTCBO_LINKAGE Shareholder : public MFCanBFCbo, private boost::noncopyable
{
public:
   static bool shareholderHasPACWithLSIF (
      DSTCWorkSession &rpDSTCWorkSession,
      const DString &strShrNum,
      const BFDataGroupId &idDataGroup);
   static SEVERITY validateShrNum (
      DSTCWorkSession &rpDSTCWorkSession, 
      const DString &strShrNum,
      const BFDataGroupId &idDataGroup);
public:
   //X-tructors
   Shareholder(BFAbstractCBO &parent);
   virtual ~Shareholder();

   //used to initialize the objects
   SEVERITY init(const DString& dstrShrhldrNum, 
      const DString& dstrTrack = I_("N"), const DString& dstrPageName = NULL_STRING);
   SEVERITY init(const BFDataGroupId& idDataGroup, const DString& dstrShrhldrNum);

   //the below getters use the private 'templat(-ed)' method
   //SEVERITY getDemographicsList(Demographics *&pDemographics,
   //   const BFDataGroupId& idDataGroup, bool inquireDatabase = true);
   SEVERITY getAccountMailingList(AccountMailingList *&pAccountMailingList,
      const BFDataGroupId& idDataGroup, bool inquireDatabase = true );
   SEVERITY getDirectTradingBankInstructionsList(
      DirectTradingBankInstructionsList *&pDirectTradingBankInstructionsList, 
      const BFDataGroupId& idDataGroup, bool inquireDatabase = true);
   SEVERITY getShareholderBankInstructionsList(
      ShareholderBankInstructionsList *&pShareholderBankInstructionsList, 
      const BFDataGroupId& idDataGroup, bool inquireDatabase = true, const DString dstrAcctNum = NULL_STRING );
   SEVERITY getRemarksList(RemarksList *&pRemarksList, 
      const BFDataGroupId& idDataGroup, bool inquireDatabase = true);
   SEVERITY getMFAccountList(MFAccountList *&pMFAccountList,
      const BFDataGroupId& idDataGroup, bool inquireDatabase = true);
      SEVERITY getAccountNumberList(AccShrNumCheck *&pAccShrNumCheck, 
      const BFDataGroupId& idDataGroup, bool inquireDatabase = true );
   SEVERITY getShrFamilyList(ShrFamilyList *&pShrFamilyList, 
      const BFDataGroupId& idDataGroup, bool inquireDatabase = true);	
   //end of the templat-ed getters

	SEVERITY getShrFundSponsorAgreementList( ShrFundSponsorAgreementList *&pShrFundSponsorAgreementList, 
														  const DString &dstrFundGroup, 
														  const BFDataGroupId& idDataGroup, 
														  bool bInquireDatabase /*= true*/	);

	SEVERITY getShrFundBrokerList( ShrFundBrokerList *&pShrFundBrokerList, 
									  	    const DString &dstrFund, 
											 const DString &dstrFundBroker,
											 const BFDataGroupId& idDataGroup, 
											 const DString &dstrDuplicateCheck = I_( "N" ), 											 
											 bool bInquireDatabase = true	);
   
   SEVERITY getAddressList(AddressList *&pAddressList, 
      const BFDataGroupId& idDataGroup, bool ignoreDataNotFound = true, 
      bool inquireDatabase = true);
   SEVERITY getAllocationList ( ShrAllocTypeList *&pAllocationList, 
                                const BFDataGroupId &idDataGroup, 
                                bool inquireDatabase = true, 
                                bool forceViewCall = false);
   SEVERITY attachAccountToMFAccountList(MFAccount *pMFAccount, const BFDataGroupId& idDataGroup);
   SEVERITY detachAccountFromMFAccountList(MFAccount *pMFAccount, const BFDataGroupId& idDataGroup);
   virtual BFAbstractCBO *getTopLevelAncestor();
   void refreshMe (bool bRefreshMe);

	SEVERITY validateModelCode( const BFDataGroupId& idDataGroup  );
   SEVERITY setFeeWaivedforEmployAgent(const BFDataGroupId& idDataGroup) ;
   bool hasBankingInstr(const BFDataGroupId& idDataGroup, const DString&  dstrAcctnum = NULL_STRING );   
   void setCurrentBankingSel(const DString& dstrSel){ m_dstrCurrentBankingSel = dstrSel ;}
   void getCurrentBankingSel(DString& dstrSel){ dstrSel = m_dstrCurrentBankingSel ;}
protected:
   virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   virtual SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
   //support for refresh
   virtual SEVERITY doPreClearFields();
   virtual SEVERITY reInit();
   virtual void donotifyResponse(SEVERITY severity, const Condition *condition, BFData *receivedData, bool moreAvailable, int callBackOption);
   virtual void doPopulateField (const BFFieldId& idField, DString &strValue, bool formattedReturn);
   virtual bool needsRefresh (const BFDataGroupId& idDataGroup) const;   
   virtual SEVERITY doValidateAll (const BFDataGroupId &idDataGroup, long lValidateGroup);

   SEVERITY getFeeModelInfo (FeeModelList *&pFeeModelList, 
						     const DString &dstrFeeModelCode,
							 const BFDataGroupId& idDataGroup);
private:
   //method to be used with the child lists getters
   template <class _X>
      SEVERITY getList_X(const I_CHAR* i_charname, _X *&pListOut, 
         const BFDataGroupId& idDataGroup, bool inquireDatabase);
   Address *getCurrentMailingAddress(DString &strAccountNum, const BFFieldId& mailFieldId, 
      const BFDataGroupId& idDataGroup );

   SEVERITY getShareholderBankInstructionsList ( const I_CHAR* i_charname, ShareholderBankInstructionsList *& pListOut, 
                                                 const BFDataGroupId& idDataGroup, const DString& dstrAcctNum,bool inquireDatabase = true
                                                );
   SEVERITY loadGroupSubstitutionList( const BFDataGroupId& idDataGroup );
   
   //validation helpers
   SEVERITY checkTheShareholderNumber( const DString& shrNum, const BFDataGroupId& idDataGroup, bool &found );
   SEVERITY initFieldsNotInInquiry( const BFDataGroupId& idDataGroup );
   SEVERITY checkForReadOnly( const BFDataGroupId& idDataGroup );

	bool isFundClassExit( MFAccount *pMFAccount, const DString& strGroupCode,
								 const DString& dstrFundCode, const DString& dstrClassCode,
								 const BFDataGroupId& idDataGroup );
	SEVERITY validateGroupCode( const DString& strValue, const BFDataGroupId& idDataGroup );
	//P0186486FN09 - Employee and Agent Account Gap#8A	
   bool isAccountBalance (const BFDataGroupId& idDataGroup); 
   SEVERITY validateEmployeeAgent(const BFDataGroupId& idDataGroup);
   void  setDefaultBankInstrSel( const BFDataGroupId& idDataGroup );

   DString _reinitShareholderNum,
      //this saves the initial shareholder number, that came in when creating a new shareholder
      _initShareholderNum,
      _initEffectiveDate,
      tempShr;
   BFData* _pResponseData;
   DString m_dstrCurrentBankingSel;
   bool _bRefresh;
};

//********************************************************************************
//              Revision Control Entries
//********************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/Shareholder.hpp-arc  $
 * 
 *    Rev 1.41   May 21 2012 14:21:32   dchatcha
 * Fix revision control entry.
 * 
 *    Rev 1.40   May 21 2012 14:13:26   dchatcha
 * P0186479 FN10 -Gap 14G - Block Service Unit Transfers, revise code.
 */  
