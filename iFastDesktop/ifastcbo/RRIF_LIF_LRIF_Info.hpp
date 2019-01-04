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
//******************************************************************************
//
// ^FILE   : RRIF_LIF_LRIF_Info.hpp
// ^AUTHOR : Yakov Prager
// ^DATE   : Feb 07, 2000
//
// ^CLASS  : RRIF_LIF_LRIF_Info
// ^PARENT : BFBase
//
// ^CLASS DESCRIPTION :
//    implements a map from the STL to hold fully instantiated BFBase objects
//    that are created from Data objects stored in the inherited ListBase class 
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
#include "ToFundAllocList.hpp"
class FromFundAllocList;
class RRIF_LIF_LRIF_PaymentsCalculation;
class MFAccount;
class Shareholder;
class RRIFBankInstructionsList;
class BankInstructions;
class TaxTypeRule;
class RRIFUnusedMaxAmt;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

namespace RRIF_GROUP
{
   extern  const long RRIF_INFO;
   extern  const long RRIF_ALLOCATION;
}

class IFASTCBO_LINKAGE RRIF_LIF_LRIF_Info : public MFCanBFCbo,public GetFromToFundAllocListInterFace,
	 private boost::noncopyable
{
public:
   // X-structors
   RRIF_LIF_LRIF_Info( BFAbstractCBO &parent );
   virtual ~RRIF_LIF_LRIF_Info( void );

   SEVERITY init( const BFData &data );
   SEVERITY init( const BFDataGroupId& idDataGroup );

	SEVERITY getFromFundAllocList(FromFundAllocList *&pFromFundAllocList, 
						const BFDataGroupId& idDataGroup, bool bCreate =  true );

	SEVERITY getToFundAllocList(ToFundAllocList *&pToFundAllocList, 
					const BFDataGroupId& idDataGroup, bool bCreate = true);
   SEVERITY getNetOfFeesApplicable(DString &dstrNetOfFees, const BFDataGroupId& idDataGroup);

   SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
   SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );

   void  setAddressLine(const BFDataGroupId& idDataGroup);
   SEVERITY ForceToDoCalculation(const BFDataGroupId& idDataGroup );
   SEVERITY ValidateAllocationList( const BFDataGroupId& idDataGroup );
   void ModelOffer(RRIF_LIF_LRIF_Info *Model, const BFDataGroupId& idDataGroup);

   int extractFieldFromDate( DString const &strField, DString strDateField = I_("yyyy") );
   SEVERITY getBankInstructionsList(RRIFBankInstructionsList *&pRRIFBankInstructionsList, 
      const BFDataGroupId& idDataGroup, bool bCreate = true);   
   SEVERITY populatedOrigPlanDeffApplied(const BFDataGroupId& idDataGroup );
   void setInitExistingFlag(bool bFlag);

   SEVERITY validateGMWB (const DString &fundCode, const DString &classCode, const BFDataGroupId& idDataGroup);

protected:
   SEVERITY updateAmountsForGrossPayTypeGEL(const BFDataGroupId& idDataGroup );
   virtual void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );
   /**
     * virtual function. Should be overwritten in order to do special processing in setField before the actual value is 
     * filled in into the CBO
     * @param idField      - the identifier of the field to be set
     * @param strValue      - the value to be set
     * @param idDataGroup  - the identifier of the data group with which the field should be set
     * @param bFormatted    - strValue is formatted or not
    */
   SEVERITY doPreSetField( const BFFieldId& idField, DString & strValue, const BFDataGroupId& idDataGroup, bool bFormatted );
   virtual void  doPopulateField( const BFFieldId& idField, DString & strValue, bool formattedReturn );
   void setAllocField(const BFFieldId& fromFieldID, const BFFieldId& toFieldID, const BFDataGroupId& idDataGroup);
   SEVERITY validatePreYrPercent(const BFDataGroupId& idDataGroup);
   SEVERITY getPaymentsCalculation( RRIF_LIF_LRIF_PaymentsCalculation *& pPaymentsCalc, 
	                                const BFDataGroupId& idDataGroup );
   SEVERITY getPaymentsCalculationForDefaultValues( RRIF_LIF_LRIF_PaymentsCalculation *& pPaymentsCalc, 
	                                                 const BFDataGroupId& idDataGroupconst, const DString& strCallNum );
   virtual void doReset( const BFDataGroupId& idDataGroup ); 
       
   SEVERITY sourceOfFundRelatedChanges (const BFDataGroupId &idDataGroup);//P0186486_FN15_The Source of Funds
   SEVERITY loadBusinessTypeSubslist( const BFDataGroupId &idDataGroup);
   void ValidateSourceOfAccount(const BFDataGroupId& idDataGroup);                                         

private:

   SEVERITY setFieldsUpdates( );
   SEVERITY commonInit(const BFDataGroupId& idDataGroup);
   void setMonthIndicator(const BFDataGroupId& idDataGroup);
   bool isSameValueAsCalculatedDouble( const BFFieldId& idField, long lCalculatedFieldId, const BFDataGroupId& idDataGroup );
   SEVERITY callPaymentsCalculation( const BFDataGroupId& idDataGroup, bool mustCallView130, DString strCallNum = I_("2") );
   bool isEFT(const BFDataGroupId& idDataGroup);

   //RRIF_LIF_LRIF_AllocList *_pRRIF_LIF_LRIF_AllocList;
   int isEffectiveDateInCurrentYr(const BFDataGroupId& idDataGroup);
	SEVERITY  validateEffectiveStopMonthIndicator(  const BFDataGroupId& idDataGroup );


   //SEVERITY setAllocationAmount(const BFDataGroupId& idDataGroup);

   SEVERITY ValidateInstCode(const DString& InstCode,const BFDataGroupId& idDataGroup);
   SEVERITY ValidateTransNo(const DString& TransNo,const BFDataGroupId& idDataGroup);
   bool HaveToCheckBankPara(const BFDataGroupId& idDataGroup );
   void setAddCopy(bool bFlag = false){_bAddCopyFlag = bFlag;}
   bool isAddCopy(){return(_bAddCopyFlag == true);}
   SEVERITY validateAgainst130(const BFDataGroupId& idDataGroup);
   void  setBatchParam(const BFDataGroupId& idDataGroup );
   void  setFieldsAsReadOnly(const BFDataGroupId& idDataGroup);
   SEVERITY ValidateValueAgainstCalc( const BFFieldId& idField, const BFFieldId& calculatedFieldId, const BFDataGroupId& idDataGroup );
   SEVERITY callView130ForSetDefaultValue(const BFDataGroupId& idDataGroup);
   void setNetAmountReadOnly(bool bGood,const BFDataGroupId& idDataGroup);
   void setAmountReadOnly(bool bGood,const BFDataGroupId& idDataGroup);
   SEVERITY validateCrossInstTransit(const BFDataGroupId& idDataGroup);
   SEVERITY setMonthsFrequencyByIndicator(const BFDataGroupId& idDataGroup);
   bool isAnnualy(const DString& strMonthIndicator);
   bool isSemiAnnualy(const DString& strMonthIndicator);
   bool isQuarterly(const DString& strMonthIndicator);
   int getNoOfYes(const DString& strMonthIndicator);
   bool isOnlySpouseBirthDateUpdated(const BFDataGroupId& idDataGroup);
   SEVERITY ValidateTaxOnMinSuppFedAndProvTax(const BFDataGroupId& idDataGroup);
   SEVERITY validateRRIFAmount(const BFDataGroupId& idDataGroup);
   SEVERITY validateNetAmount(const BFDataGroupId& idDataGroup);
   SEVERITY getErrMsg( const DString& dstrErrNum, long lErrConditionId, 
                       long lWarnConditionId, const BFDataGroupId& idDataGroup );
	SEVERITY validateAcctTo( const BFDataGroupId& idDataGroup );
	SEVERITY validatePercent( const BFFieldId& idField,const BFDataGroupId& idDataGroup );
	SEVERITY validateTransfer( const BFDataGroupId& idDataGroup);
	SEVERITY validateSpouseDOB( const BFDataGroupId& idDataGroup);

   bool isOverrideUnusedAmtReadOnly( const BFDataGroupId& idDataGroup );

   SEVERITY setMonthlyIndicatorByDeffFreq( const BFDataGroupId& idDataGroup );
   SEVERITY setEOMandMonthIndicator( const BFDataGroupId& idDataGroup );
   SEVERITY buildPaymentCalcKey( DString &dstrKey, const BFDataGroupId& idDataGroup );
   SEVERITY getOrigPlanDeffApplied(DString &dstrOrigPlanDeffApplied,
                                   const BFDataGroupId& idDataGroup);

   bool     _bAddCopyFlag;
   DString _strOldMonthEnd;
   //DString _strCallNum;
   DString _strAccountNum;
   MFAccount *_pAccount;
   Shareholder *_pShareholder;
   int _effectiveDateYear;
   bool _bInitExisting;
   bool _bIsUserEnteredValidOrigPlanDeff;
   void  setGrossNetMethod(const BFDataGroupId& idDataGroup, bool bIsInit = false);
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RRIF_LIF_LRIF_Info.hpp-arc  $
 * 
 *    Rev 1.61   Jun 27 2012 12:31:08   if991250
 * IN2981340 : RRIF
 * 
 *    Rev 1.60   May 11 2012 13:52:06   jankovii
 * P0186481 FN07 - GWA LWA Payment Options for SWP RRIF
 * 
 *    Rev 1.59   Apr 20 2012 04:03:10   panatcha
 * P0186486_FN15_The Source of Funds
 * 
 *    Rev 1.58   Jan 19 2011 03:55:12   wutipong
 * IN2253366 The ‘Gross/Net Pretax’ field in RRIF payment screen is being updated incorrectly
 * 
 *    Rev 1.57   Oct 04 2010 06:43:18   kitticha
 * Cleaning dirty comment.
 * 
 *    Rev 1.56   Oct 04 2010 06:37:46   kitticha
 * PET0168176 FN01 Locked In Product Changes.
 * 
 *    Rev 1.55   Jan 27 2010 06:35:46   wichian
 * 1885614-NET of FEE on RIF Transfers
 * 
 *    Rev 1.54   Apr 02 2009 09:27:56   jankovii
 * IN 1643940 - Stop user change RIF deff of current year to next year
 * 
 *    Rev 1.53   19 Mar 2009 14:41:48   kovacsro
 * IN#1490538 - Error message when creating a LIF record with "Maximum" pay option (redesigned view 130 call and eliminated calls to view 375)
 * 
 *    Rev 1.52   05 May 2008 14:51:14   kovacsro
 * PET2255-FN47 New LIF - moved 'Gain/Loss' from RIF screen into COA
 * 
 *    Rev 1.51   24 Apr 2008 13:35:30   kovacsro
 * PET2255 FN47 - New Ontario LIF - added EligExtTrfGainLoss
 * 
 *    Rev 1.50   15 Apr 2008 12:09:58   kovacsro
 * PET2255 FN47 - New Ontario LIF
 * 
 *    Rev 1.49   Mar 25 2008 13:09:42   jankovii
 * IN 1222272 - Desktop does not check for ac owner's dob when setting up a RRIF.
 * 
 *    Rev 1.48   06 Dec 2007 11:50:10   kovacsro
 * IN#1058816 - fix for the new frequencies
 * 
 *    Rev 1.47   Aug 22 2007 17:09:12   smithdav
 * IN 982850,  IN    - Add DayOfMonth field conditions to RRIF.
 * 
 *    Rev 1.46   Sep 25 2006 15:13:06   porteanm
 * Incident 716157 - Monthly Indicator default.
 * 
 *    Rev 1.45   Sep 07 2006 17:44:44   porteanm
 * PET2216 FN35 - RRIF Locked-In products - RRIF Unused Amt.
 * 
 *    Rev 1.44   Nov 14 2004 14:53:14   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.43   Sep 12 2003 13:55:42   YINGBAOL
 * Add validateEffectiveStopMonthIndicator( ) mothed
 * 
 *    Rev 1.42   Sep 05 2003 11:05:46   ZHANGCEL
 * PTS ticket 10021399 : added a new function :getTaxTypeRule
 * 
 *    Rev 1.41   Jun 23 2003 10:03:48   YINGBAOL
 * implement FromToAllocationInterface
 * 
 *    Rev 1.40   Jun 13 2003 15:59:32   YINGBAOL
 * add validateTransfer
 * 
 *    Rev 1.39   Jun 09 2003 11:46:04   YINGBAOL
 * RRIF Enhancement
 * 
 *    Rev 1.38   May 31 2003 20:30:22   popescu
 * RRIF work part ||
 * 
 *    Rev 1.37   May 27 2003 13:14:08   popescu
 * RRIF Banking work
 * 
 *    Rev 1.36   Apr 17 2003 13:22:18   HERNANDO
 * Sync with 1.34.1.0 - 
 * PTS 10015081
 * PTS 10015554
 * PTS 10015338
 * PTS 10015839
 * 
 *    Rev 1.35   Mar 21 2003 18:22:38   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.34   Jan 12 2003 16:40:56   YINGBAOL
 * RRIF Enhancement for Dynamic
 * 
 *    Rev 1.33   Oct 09 2002 23:54:54   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.32   Aug 29 2002 12:53:30   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.31   Aug 06 2002 09:56:14   KOVACSRO
 * Release 48. Converted allocations.
 * 
 *    Rev 1.30   Jul 19 2002 11:45:22   YINGBAOL
 * code clean up
 * 
 *    Rev 1.29   24 May 2002 15:03:42   KOVACSRO
 * doPresetField changes.
 * 
 *    Rev 1.28   22 May 2002 18:20:04   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.27   May 09 2002 12:59:38   YINGBAOL
 * added  isOnlySpouseBirthDateUpdated;
 * 
 *    Rev 1.26   19 Mar 2002 13:18:16   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.25   Nov 01 2001 10:21:56   YINGBAOL
 * add dopopulateField Method
 * 
 *    Rev 1.24   Oct 01 2001 14:31:52   YINGBAOL
 * add isEffectiveDateInCurrentYr(..) method
 * 
 *    Rev 1.23   Aug 25 2001 14:09:12   YINGBAOL
 * add some method to support frequency change
 * 
 *    Rev 1.22   Jul 26 2001 16:38:22   ZHANGCEL
 * Move function extractFieldFromDate from private to public
 * 
 *    Rev 1.21   03 May 2001 14:04:46   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.20   Apr 03 2001 15:49:36   YINGBAOL
 * change banklist due to view100 has been changed
 * 
 *    Rev 1.19   Nov 02 2000 13:21:42   YINGBAOL
 * use new databroker
 * 
 *    Rev 1.18   Oct 27 2000 13:27:50   YINGBAOL
 * clean up
 * 
 *    Rev 1.17   Oct 20 2000 14:23:50   YINGBAOL
 * implement setamount logic
 * 
 *    Rev 1.16   Oct 19 2000 15:29:40   YINGBAOL
 * Introduce GROUPINFO
 * 
 *    Rev 1.15   Oct 17 2000 14:55:28   YINGBAOL
 * add addcopy function and fix ither issues
 * 
 *    Rev 1.14   Sep 28 2000 14:58:54   YINGBAOL
 * a lot of changes in order to make things to work...
 * 
 *    Rev 1.13   Sep 08 2000 11:26:36   PETOLESC
 * Concentrated the logic for calling view 130 in testIfCallingPaymentsCalculation().
 * 
 *    Rev 1.12   Aug 31 2000 11:04:44   PETOLESC
 * Modified crossedits and logic to call view 130.
 * 
 *    Rev 1.11   Aug 04 2000 09:42:44   PETOLESC
 * Moved call to view 124 in DoValidateAll().
 * 
 *    Rev 1.10   Jul 20 2000 14:58:32   PETOLESC
 * Fiddled once more with the call order for view 130.
 * 
 *    Rev 1.9   Jul 18 2000 13:49:04   PETOLESC
 * Modified order of calls for view 130.
 * 
 *    Rev 1.8   Jun 28 2000 15:00:36   PETOLESC
 * Added Frequency field, changed logic for view 130 call sequence and a BIG bunch of other changes.
 * 
 *    Rev 1.7   Jun 09 2000 18:01:48   PETOLESC
 * Save work.
 * 
 *    Rev 1.6   May 19 2000 17:29:44   PETOLESC
 * save work
 * 
 *    Rev 1.5   May 12 2000 16:03:20   PETOLESC
 * Updated validation rules.
 * 
 *    Rev 1.4   May 08 2000 11:54:00   PETOLESC
 * Added getRRIF_LIF_LRIF_AllocList().
 * 
 *    Rev 1.3   Apr 26 2000 10:05:16   PETOLESC
 * Added doValidateField().
 * 
 *    Rev 1.2   Mar 31 2000 16:20:32   YINGBAOL
 * chnage
 * 
 *    Rev 1.0   Feb 15 2000 11:00:04   SMITHDAV
 * Initial revision.
// 
*/


