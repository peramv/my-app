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
//    Copyright 2000 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE      : PaymentInstructions.hpp
// ^AUTHOR    : Serban Popescu
// ^DATE      : June 2003
//
// ^CLASS     : PaymentInstructions
// ^SUBCLASS  :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

#define EXTRACT_VALUE(s, val) \
      pos = s.find (I_(",")); \
      val = s.substr (0, pos);

#define CHOP_STRING(s) \
         pos = s.find (I_(",")); \
         pos = pos != DString::npos && pos + 1 <= s.length() ? pos + 1 : DString::npos; \
         if (pos != DString::npos) \
            s = s.substr (pos); \
         else \
            s = NULL_STRING;

class BankInstructionsList;
class AgencyNegComm;
class Broker;
class Branch;
class Agent;
class PaymentInstrValidation;

class IFASTCBO_LINKAGE PaymentInstructions : public MFCanBFCbo, private boost::noncopyable
{
public:
   PaymentInstructions (BFAbstractCBO &parent);
   virtual ~PaymentInstructions();

   SEVERITY init (const BFData &viewData, const DString &searchTypeMgmt );
   SEVERITY init ( const DString &dstrBrokerCode, 
                   const DString &dstrBranchCode, 
                   const DString &dstrSlsRepCode,
                   const DString &dstrPaymentFor,
                   const BFDataGroupId& idDataGroup,
						 const DString &searchTypeMgmt );
   bool isBankingAllowed (const BFDataGroupId &idDataGroup);
   bool isAddressInfoAllowed (const BFDataGroupId &idDataGroup);
   bool isSuppressAllowed (const BFDataGroupId &idDataGroup);
   bool isCreateTradeAllowed (const BFDataGroupId &idDataGroup);
   SEVERITY removeBankInstructionsList(const BFDataGroupId &idDataGroup);
   SEVERITY getBankInstructionsList( BankInstructionsList *&pBankInstructionsList, 
                                     const BFDataGroupId &idDataGroup);
   virtual SEVERITY setField ( const BFFieldId &idField, 
                               const DString &dstrValue,
                               const BFDataGroupId &idDataGroup, 
                               bool bFormatted = true, 
                               bool bSideEffect = false, 
                               bool bCheckCurrentValue = true); 
   bool hasAgencyNegCommission (const BFDataGroupId &idDataGroup);
protected:
   virtual SEVERITY doValidateField ( const BFFieldId& idField, 
                                      const DString& strValue, 
                                      const BFDataGroupId& idDataGroup);
   virtual SEVERITY doApplyRelatedChanges ( const BFFieldId& idField, 
                                            const BFDataGroupId& idDataGroup);
   virtual void doInitWithDefaultValues ( const BFDataGroupId& idDataGroup);
   virtual SEVERITY doValidateAll ( const BFDataGroupId& idDataGroup, 
                                    long lValidateGroup);
   virtual void doReset (const BFDataGroupId &idDataGroup);
   SEVERITY setPaymentForSubSet (const BFDataGroupId &idDataGroup);
   SEVERITY paymentForRelateChange (const BFDataGroupId &idDataGroup);
   SEVERITY setPayTypeSubSet (const BFDataGroupId &idDataGroup);
	SEVERITY CheckPair (const BFDataGroupId& idDataGroup);
	SEVERITY getPaymentInstrValidation(  const DString &dstrBrokerCode,
							    const DString &dstrBranchCode,
								 const DString &dstrSalesRepCode,
								 const DString &dstrPaymentFor,
								 const DString &dstrEffectiveDate,
								 const DString &dstrStopDate,
								 const BFDataGroupId& idDataGroup,
								 PaymentInstrValidation *&pPaymentInstrValidation,
								 bool  &bDataNotFound );
	SEVERITY buildPaymentRoutingSet(const BFDataGroupId &idDataGroup);
   void  initializeSubstitutionList (const BFFieldId& idField, const DString &dstrGroupCode, const BFDataGroupId& idDataGroup);

private:
   SEVERITY setBrokerName ( const DString &brokerCode,
                            const BFDataGroupId &idDataGroup,
                            bool checkEffective = false);
   SEVERITY setBranchName ( const DString &branchCode,
                            const BFDataGroupId &idDataGroup,
                            bool checkEffective = false);
   SEVERITY setSlsRepName ( const DString &slsRepCode,
                            const BFDataGroupId &idDataGroup,
                            bool checkEffective = false);
   SEVERITY commonInit ( const DString &dstrBrokerCode, 
                         const DString &dstrBranchCode, 
                         const DString &dstrSlsRepCode,
                         const DString &dstrPaymentFor,
                         const BFDataGroupId &idDataGroup);
   SEVERITY fillAddressInfo ( const BFDataGroupId &idDataGroup, 
                              bool bDataNotFound = false);
   SEVERITY payToEntityRelatedChanges (const BFDataGroupId &idDataGroup);
   SEVERITY addressInfoRelatedChanges (const BFDataGroupId &idDataGroup);
   SEVERITY currencyOptionRelatedChanges (const BFDataGroupId &idDataGroup);
   SEVERITY payTypeRelatedChanges ( const BFDataGroupId &idDataGroup, 
                                    bool bDataNotFound = false);
   SEVERITY validateCurrency (const BFDataGroupId &idDataGroup);
   SEVERITY loadCurrencySet (const BFDataGroupId &idDataGroup);
   SEVERITY loadPayMethodSet (const BFDataGroupId &idDataGroup);
   SEVERITY loadFileProcessorSet (const BFDataGroupId &idDataGroup);
   SEVERITY setAccountField (const BFDataGroupId &idDataGroup);
   SEVERITY loadShareholderGroupSet (const BFDataGroupId &idDataGroup);
   SEVERITY directToRelatedChanges( const BFDataGroupId &idDataGroup, bool bDataNotFound = false);
   SEVERITY getAgencyNegCommission ( const BFDataGroupId &idDataGroup,
	                                  AgencyNegComm *&pAgencyNegComm) ; 
	SEVERITY validatePaymentForConsolType (const BFDataGroupId& idDataGroup);
	SEVERITY validateConsolType (const BFDataGroupId& idDataGroup);
	bool getDefaultConsolType ( DString &dstrConsolTransType, 
										 DString &dstrConsolidation, 
										 DString &dstrConsolDefault,
										 const BFDataGroupId &idDataGroup);
	SEVERITY setConsolTypeSubstituteValues ( const BFDataGroupId &idDataGroup );
	SEVERITY initConsolidation ( const BFDataGroupId &idDataGroup );

   SEVERITY getPayEntityDates ( DString &effectiveDate, 
                                DString &stopDate, 
                                DString &efDtFmt, 
                                DString &stpDtFmt, 
                                const BFDataGroupId &idDataGroup);
   bool doesTransTypeHasDefault( const DString &dstrConsolTransType, const BFDataGroupId& idDataGroup );

   bool isMgtCoPayInstruct ();
   SEVERITY getBroker (Broker *&broker,
                       const BFDataGroupId &idDataGroup);
   SEVERITY getBranch (Branch *&branch,
                       const BFDataGroupId &idDataGroup);
   SEVERITY getAgent (Agent *&agent,
                      const BFDataGroupId &idDataGroup);
   SEVERITY setDefaultPayment(const BFDataGroupId& idDataGroup);

   bool _isNoSplitCommissionEnvironment;
   DString _dstrBankChargeDefault,
           _hostCurrenciesSet,
			  _searchType;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/PaymentInstructions.hpp-arc  $
//
//   Rev 1.31   Aug 16 2007 11:03:26   kovacsro
//PET2388FN01 - Swift Payment Method Id
//
//   Rev 1.30   Jan 24 2007 16:51:34   ZHANGCEL
//PET2306 FN02 -- Add logic for the enhancement
//
//   Rev 1.29   Nov 03 2006 16:18:10   ZHANGCEL
//Incident 731541 -- Add logice to check Pair
//
//   Rev 1.28   Oct 20 2006 18:14:50   popescu
//Incident# 731541 reviewed the way related changes for  fields is working in paym instruct
//
//   Rev 1.27   Oct 19 2006 16:24:58   ZHANGCEL
//STP PET 2213/17 -- Added Redemption/Distribution pair validation logic
//
//   Rev 1.26   Oct 06 2006 14:22:12   popescu
//Incident# 651066 - fixed crash if salesrep/broker/branch are not found - synch from 72 
//
//   Rev 1.25   Sep 30 2006 00:54:32   popescu
//Incident 720294 - pay entity eff. dates
//
//   Rev 1.24   Sep 10 2006 17:59:08   popescu
//STP 2192/12
//
//   Rev 1.23   Aug 28 2006 15:39:34   ZHANGCEL
//PET2212 FN10 -- Added new logic for Netting Bulking Redemption and Distribution Payment
//
//   Rev 1.22   Jul 27 2006 18:00:30   ZHANGCEL
//PET2192 FN11 - Commission Payments to MgmtCo related changes
//
//   Rev 1.21   May 31 2006 17:56:30   porteanm
//PET2132 FN03 - Edit check for Negative Commission.
//
//   Rev 1.20   Jan 25 2006 10:19:24   AGUILAAM
//PET2016_FN05: AXA Office Trailer Fee Indicator
//
//   Rev 1.19   Jan 06 2006 14:41:34   popescu
//Incident# 513119 - reinvest added to payment type instead of payment method
//
//   Rev 1.17.1.0   Jan 06 2006 14:04:54   popescu
//Incident# 513119 - reinvest added to payment type instead of payment method
//
//   Rev 1.17   Nov 01 2005 09:17:38   AGUILAAM
//PET1243_FN00_ABN AMRO Trailer Fee Processing - additional enhancements
//
//   Rev 1.16   Oct 19 2005 17:16:30   AGUILAAM
//PET1243_FN00: ABN AMRO Trailer Fee Processing
//
//   Rev 1.15   Nov 14 2004 14:50:52   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.14   May 20 2004 13:46:02   FENGYONG
//PET 944 FN01 - NSCC new reqirement, default currency option
//
//   Rev 1.13   Apr 07 2004 18:38:18   FENGYONG
//PET944FN01 rel56.1 NSCC Broker
//
//   Rev 1.12   Apr 05 2004 17:29:46   FENGYONG
//PET944 FN01, release 56.1 NSCC Broker Matrix
//
//   Rev 1.11   Mar 04 2004 17:48:58   popescu
//PTS 10027865, fixed crash in Pay to entity search for inactive brokers. Disabled 'Instructions' button in pay to entity dialog if broker is inactive/not effective
//
//   Rev 1.10   Feb 18 2004 18:01:18   popescu
//PTS 10027184; - moved the ownership of the payment instructions banking list at the payment instructions CBO level.
//- clean-up the work session every time user hits 'Search' on the Features Search Dialog
//- do not add payment instructions/ pay to entity records, when refreshing the respective CBO lists in DistributorRepository, always read them from back-end. Now, this is possible since the work session is cleaned-up all the time.
//- fixed crash that happens when a new record is added to the payment instructions bank list. The scenario to get this crash is: go to pay to entity screen, then click the 'instructions' button, modify an existing payment instructions record with bank information. Hit okay, commit the changes in the parent. Go back to the payment instructions (you will notice that the previous changes are not saved -  another issue that has been fixed with this ticket), and then click the Bank button. Add a new bank record. Desktop reports an internal error.
//- use new IFDSListCtrl, for the PayToEntity list and PaymentInstructions list.
//
//   Rev 1.9   Feb 11 2004 18:45:26   popescu
//PTS 10026899, reloaded currency set for Suppress pay type in Payment Instructions, loaded banking currency dynamically based on the file processor value if not empty
//
//   Rev 1.8   Feb 10 2004 12:29:16   popescu
//PTS 10026204, payment instructions is loading the file processor dynamicaly; set the correct substitution set for file processor for a modified trade (copied from 'Pending Trade')
//
//   Rev 1.7   Aug 26 2003 13:56:00   HERNANDO
//PTS 10021007 - Added _dstrACHProcessor.
//
//   Rev 1.6   Aug 18 2003 11:18:40   popescu
//PTS 10020750
//Reset the currency set to the 'ALL' currencies if the user changes the value of the file processor to an empty string
//
//   Rev 1.5   Jul 31 2003 21:59:06   popescu
//Added support for PayType 'X' and support for Historical Info at the process level
//
//   Rev 1.4   Jul 11 2003 13:46:56   popescu
//fixes related to the confirmation screen showing up even if there are no changes for the payment instructions screen, added validation for the Currency if BAAF is selected as the file processor
//
//   Rev 1.3   Jul 10 2003 22:21:02   popescu
//check in for payment instruct, used mfcan_ip_param for some interporcess param passing
//
//   Rev 1.2   Jul 09 2003 21:56:56   popescu
//Payment Instructiuons work, business rules implementation SSB_PET_821_FN17
//
//   Rev 1.1   Jul 02 2003 17:49:36   popescu
//work for payment instructions feature 
//
//   Rev 1.0   Jul 01 2003 18:17:16   popescu
//Initial revision.
 */