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
//    Copyright 2000 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : SplitCommissionList.hpp
// ^AUTHOR : Zijian Ying
// ^DATE   : February  26, 2001
//
// ^CLASS    : SplitCommissionList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
#include <ifastdataimpl\dse_dstc0151_req.hpp>
#include <ifastdataimpl\dse_dstc0151_vw.hpp>
#include <ifastdataimpl\dse_dstc0158_req.hpp>
#include <ifastdataimpl\dse_dstc0158_vw.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class SplitCommission;

class IFASTCBO_LINKAGE SplitCommissionList : public MFCanBFCbo, private boost::noncopyable
{
public:
   static SEVERITY canFeeBeDiscounted (SplitCommissionList *pSplitCommissionList,
	                                    DSTCWorkSession &rpDSTCWorkSession, 
                                       const double &dFee,
                                       const double &dInitialTotalRate,
                                       const double &dMaxRate,
                                       const BFDataGroupId &idDataGroup);
   static DString calculateBaseCommission (const DString &feeDefaultRate_,
                                           const DString &sfacRate_);

   SplitCommissionList(BFAbstractCBO &parent);
   virtual ~SplitCommissionList();
   //to call view 151, for split commission
   SEVERITY init( const DString& dstrTransNum, 
                  const DString& dstrTransSeq,
                  const DString& dstrTransType, 
                  const DString& dstrAccountNum,
                  const DString& dstrFund, 
                  const DString& dstrClass,
                  const DString& dstrBrokerCode, 
                  const DString& dstrBranchCode,
                  const DString& dstrSlsRepCode, 
                  const DString& dstrEffectiveDate,
                  const DString& transId,
				  const DString& rdrAdvice = NULL_STRING,
                  const BFDataGroupId& idDataGroup = BF::HOST,
                  const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING);
   //to call view 158, the default split commission
   SEVERITY init( const DString& dstrAccount,
                  const DString& dstrAccountTo,
                  const DString& dstrFund,
                  const DString& dstrFundTo,
                  const DString& dstrClass,
                  const DString& dstrClassTo,
                  const DString& dstrPUD,
                  const DString& dstrFlatPrcnt,
                  const DString& dstrInPayType,
                  const DString& dstrIAmount,
                  const DString& dstrInTransType,
                  const DString& dstrEffectiveDate,
                  const DString& dstrInGrossNet,
                  const DString& dstrBrokerCode,
                  const DString& dstrBranchCode,
                  const DString& dstrSlsRepCode,
                  const DString& dstrSettleCurrency,
                  const DString& recordType,
                  const DString& exchRate,
                  const DString& investTerm,
				  const DString& rdrAdvice,
				  const DString& dstrTradeInDate = NULL_STRING,
                  const BFDataGroupId& idDataGroup = BF::HOST,
                  const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING);

   SEVERITY initDefaultFlatFeeData (const BFDataGroupId &idDataGroup);
   //SEVERITY init( const BFData& data );
   SEVERITY doCreateObject(const BFData& data, BFCBO*& pObjOut);
   SEVERITY doCreateNewObject(BFCBO*& pBase, DString &strKey, const BFDataGroupId& idDataGroup);
   SEVERITY doValidateAll(const BFDataGroupId& idDataGroup, long lValidateGroup);
   //double getInitTotal();
   void getRenunciationAmount(double &dblRenunciationAmount, const BFDataGroupId& idDataGroup);
   void getRenunciationAmount(DString &dstrRenunciationAmount, const BFDataGroupId& idDataGroup);
   void getSplitTotalAmount(double &dblSplitTotalAmount, const BFDataGroupId& idDataGroup);
   void getSplitTotalAmount(DString &dstrSplitTotalAmount, const BFDataGroupId& idDataGroup);
   void getSplitTotalRate(double &dblSplitTotalRate, const BFDataGroupId& idDataGroup);
   void getSplitTotalRate(DString &dstrSplitTotalRate, const BFDataGroupId& idDataGroup);
   void getSplitTotalPercent(double &dblSplitTotalPercent, const BFDataGroupId& idDataGroup);
   void getSplitTotalPercent(DString &dstrSplitTotalPercent, const BFDataGroupId& idDataGroup);
   void getInitialTotalRate (DString &dstrInitialTotalRate, const BFDataGroupId& idDataGroup);
   void deleteSplitCommList(const BFDataGroupId& idDataGroup);
   bool hasCBOObject();
   void calculateFieldsBasedOnCommissionType (const BFDataGroupId& idDataGroup);
   bool hasSplits ();
   void changeFieldsForRebook();
   SEVERITY isNonSharingDiscount(bool& isNonSharingDiscount, const BFDataGroupId& idDataGroup);
   SEVERITY calculateNonSharingSplitCommission(const BFDataGroupId& idDataGroup);
   SEVERITY calculateSharedDiscount(SplitCommission* pCurrentSplitCommission, 
                                    const BigDecimal& bdRate, BigDecimal& bdRateRemaining, 
                                    const BFDataGroupId& idDataGroup,
                                    bool useRemainingCommission);

   DString getTaxTypeMaxFee(const BFDataGroupId &idDataGroup);
   SEVERITY propagateTotalRate(DString &dstrTotalRate, const BFDataGroupId &idDataGroup);
   SEVERITY changeToRDRAdviceProvided( const BFDataGroupId& idDataGroup /*=BF::HOST*/);
   SEVERITY applyRateRelatedChanges (const BFDataGroupId &idDataGroup);
protected:
   SEVERITY doApplyRelatedChanges(const BFFieldId& idField, 
      const BFDataGroupId& idDataGroup);
   SEVERITY doDeleteObject (const DString &strKey, 
      const BFDataGroupId& idDataGroup, bool bIsObjectDestroyed);
   SEVERITY validateTotalSplitAmount (const BFDataGroupId& idDataGroup);

private:
   void getTotal(const BFFieldId& idField, DString &dstrTotal, const BFDataGroupId& idDataGroup);
   bool shouldSkipCalculatingRatesAmounts (const BFDataGroupId& idDataGroup);
   SEVERITY commonInit ( BFData& reqData, 
                         const DString& dstrTransType,
                         const DString& dstrAccountNum, 
                         const DString& dstrFund, 
                         const DString& dstrClass,
                         const DString& dstrBrokerCode, 
                         const DString& dstrBranchCode,
                         const DString& dstrSlsRepCode, 
                         const DString& dstrEffectiveDate,
						 const DString& dstrTradeInDate=NULL_STRING,
						 const DString& dstrRDRAdvice = NULL_STRING,
                         const BFDataGroupId& idDataGroup = BF::HOST);
   static bool commissionNotNegotiable (const DString &feeOverrideType);
   static bool commissionAllowsDiscount (const DString &feeOverrideType);
   static bool commissionFullyNegotiable (const DString &feeOverrideType);
   SEVERITY getTheTransTypeForFeeDefault( DString &dstrTransType, 
                                          const DString &fromFund, 
                                          const DString &fromClass, 
                                          const DString &toFund, 
                                          const DString &toClass, 
                                          const BFDataGroupId &idDataGroup);
   bool isROAApplicable (const BFDataGroupId &idDataGroup);
   double _maxRate; //this max is read based on view 158 or 151
   double _initialTotalRate; //this is the initial of the commission
   bool _callDefault, //used to know what view to call
      _hasSplits,
      _bSkipCal;
   DString _dstrAmount;

   private:
   static bool bIsTaxLevelOverride4MaxFeeNotAllowed(SplitCommissionList *pSplitCommissionList,
												  DSTCWorkSession &rpDSTCWorkSession,
												  const BFDataGroupId &idDataGroup);
   SEVERITY getNonSharingDiscountApplicable(DString& dstrNonSharingDiscountApplicable,
											DString dstrTransType,
											DString dstrFundCode,
											DString dstrClassCode,
											DString dstrBrokerCode,
											DString dstrEffectiveDate,
											DString dstrAccountNum,
											DString dstrAmountType,
											DString dstrAmount,
											const BFDataGroupId& idDataGroup);

  SEVERITY addRDRAdviceProvidedCommission( const DString& dstrRate, const BFDataGroupId& idDataGroup /*=BF::HOST*/);

};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/SplitCommissionList.hpp-arc  $
//
//   Rev 1.48   Jul 31 2012 16:46:06   wp040027
//Sync up: IN# 3006862-CPF-Enable Fee in PAC/Corrected default Fee in PAC and Trade screen/Max Fee Validation
//
//   Rev 1.47   Jul 30 2012 09:07:14   wp040027
//P0198518 - RDR Functionality - Review Comment incorporated
//
//   Rev 1.46   Jul 26 2012 10:41:28   wp040027
//P0198518 - RDR Functionality
//
//   Rev 1.45   Jun 04 2012 09:29:22   if991250
//CPF: PAC
//
//   Rev 1.44   May 18 2012 13:39:38   if991250
//CPF: P0187485_FN01_Discount Non-Sharing Enhancement
//
//   Rev 1.43   Apr 24 2012 21:17:50   wp040039
//PETP0187485 - Trade Entry And Processing
//
//   Rev 1.42   Feb 09 2012 19:34:24   popescu
//2821238 - Base Commission should be calculated on Overriding the default Acquisition Fee
//
//   Rev 1.41   Nov 28 2011 23:08:06   popescu
//INA Commission Work
//
//   Rev 1.40   Nov 27 2011 19:42:52   popescu
//INA Commission Work
//
//   Rev 1.39   Nov 23 2011 09:24:04   popescu
//INA Base Commission
//
//   Rev 1.38   Apr 15 2011 14:36:52   jankovii
//IN 2495248 - Split Commission Issues on DSK
//
//   Rev 1.37   Mar 04 2011 12:16:50   jankovii
//PET181943 FN01 - XMLPhase 2
//
//   Rev 1.36   Jul 08 2005 09:32:18   Yingbaol
//PET1235,FN01:transaction cancellation rebook
//
//   Rev 1.35   Jul 04 2005 19:05:06   popescu
//Incident # 347073 - split commission is charged on the To side for environments where ROA is applicable.
//
//   Rev 1.34   Jun 15 2005 18:41:36   popescu
//Incident # 333141- correctly displayed the split commission amount value for processed transactions
//
//   Rev 1.33   May 18 2005 09:03:28   yingbaol
//PET1203,FN01 Commission-Class A enhancement
//
//   Rev 1.32   Mar 30 2005 14:37:42   popescu
//Incident# 275373, added an extra parameter to view 151 (TransId), split commission trans history/pending trades inquiry
//
//   Rev 1.31   Feb 22 2005 14:04:56   popescu
//Incident #249310, validation of split commissions should be done against the initial total value, rather then 0 amount
//
//   Rev 1.30   Feb 17 2005 17:05:12   aguilaam
//incident # 239846 - pass and display RenunAmount (checked in for Serban)
//
//   Rev 1.29   Jan 20 2005 19:54:42   popescu
//PET 1117/06, fixed split comm calc issue for comm environment type 1
//
//   Rev 1.28   Nov 14 2004 14:56:12   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.27   Jan 21 2004 18:12:06   popescu
//PTS 10026237,
//For allocated purchases the acquisition fee should be zero and split commissions default values are displayed as they are returned by view 158.
//Also, if no repeated record is returned by 158 set the IFee to the Fee field value of the fixed section of view 158 and follow the same validation rules, as if split commissions would exist.
//
//   Rev 1.26   Dec 15 2003 11:55:08   popescu
//PTS 10023645, disable split commission button if 158 returns data not found, for various reasons
//
//   Rev 1.25   Dec 10 2003 12:19:28   popescu
//PTS 10024124, spcomm re-work
//
//   Rev 1.24   Dec 08 2003 15:28:28   popescu
//PTS 10023645, split commission re-work
//
//   Rev 1.23   Aug 20 2003 13:24:56   popescu
//PTS 10018618 fix; the code provided will not however, remain, it should be changed by getting the right fee code from the back-end
//
//   Rev 1.22   Aug 20 2003 11:27:22   popescu
//PTS 10018403
//The split commission percentage calculation was using a wrong total rate it should be using the initial total rate of the split
//
//   Rev 1.21   Aug 19 2003 09:02:30   popescu
//PTS 10020327
//Modified the signature of the calculate...method
//
//   Rev 1.20   May 13 2003 19:36:48   popescu
//PTS 10016228 & 10016241
//
//   Rev 1.19   May 13 2003 10:06:14   popescu
//Split commission re-work
//
//   Rev 1.18   May 07 2003 11:02:36   popescu
//fixed PTS 10016875
//
//   Rev 1.17   Apr 29 2003 17:05:58   popescu
//PTS 10016204
//
//   Rev 1.16   Apr 14 2003 16:27:34   popescu
//PTS 10011081- split commision amount is being calculated by the view side
//
//   Rev 1.15   Apr 04 2003 10:18:46   popescu
//split commsion work
//
//   Rev 1.14   Mar 21 2003 18:25:12   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.13   Oct 09 2002 23:55:02   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.12   Aug 29 2002 12:53:42   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.11   22 May 2002 18:19:40   PURDYECH
//BFData Implementation
//
//   Rev 1.10   19 Mar 2002 13:18:32   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.9   16 Nov 2001 16:34:04   HSUCHIN
//added missing logic for default split for commission type 2
//
//   Rev 1.8   07 Nov 2001 15:39:04   HSUCHIN
//added setSplitRateTotal, reCalculateCommRate, reCalculateCommPrcnt and getFELFee functions
//
//   Rev 1.7   09 May 2001 10:28:02   HSUCHIN
//Sync up with SSB
//
//   Rev 1.5.2.3   May 07 2001 13:53:28   YINGBAOL
//add hasCBOObject method
//
//   Rev 1.5.2.2   02 May 2001 13:02:50   HSUCHIN
//removed donotifyresponse
//
//   Rev 1.5.2.1   27 Apr 2001 13:37:40   HSUCHIN
//added function deleteSplitCommList
//
//   Rev 1.5.2.0   14 Apr 2001 11:00:36   HSUCHIN
//added  reCalculateCommAmount function
//
//   Rev 1.5   01 Apr 2001 09:49:56   HSUCHIN
//added Default Split Commission init
//
//   Rev 1.4   Mar 19 2001 15:04:10   HSUCHIN
//additional processing and validation
//
//   Rev 1.3   Mar 18 2001 11:52:04   HSUCHIN
//additioanl features and support
//
//   Rev 1.2   Mar 08 2001 15:33:10   YINGZ
//make it work
//
//   Rev 1.1   Feb 27 2001 15:49:46   YINGZ
//for robert
 * 
 */
