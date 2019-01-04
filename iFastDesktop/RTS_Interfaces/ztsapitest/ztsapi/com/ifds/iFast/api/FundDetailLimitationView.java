
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Fund Detail Limitation view.
 * For additional view information see <A HREF="../../../../viewspecs/FundDetailLimitation.doc">FundDetailLimitation.doc</A>.
 * 
 * @author RTS Generated
 */
public class FundDetailLimitationView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Fund Code member array.
    */
   private String[] _FundCode = null;
   
   /**
    * Class Code member array.
    */
   private String[] _ClassCode = null;
   
   /**
    * Class Name in English member array.
    */
   private String[] _ClassE = null;
   
   /**
    * Class Name in French member array.
    */
   private String[] _ClassF = null;
   
   /**
    * Number of trade delay days member array.
    */
   private Integer[] _AdditionalDays = null;
   
   /**
    * Minimum amount for initial purchase member array.
    */
   private String[] _MinInitPurAmt = null;
   
   /**
    * Minimum amt for subsequent purchase member array.
    */
   private String[] _MinSubPurAmt = null;
   
   /**
    * Minimum amount for initial redemption member array.
    */
   private String[] _MinInitRedAmt = null;
   
   /**
    * Minimum amt for subsequent redemption member array.
    */
   private String[] _MinSubRedAmt = null;
   
   /**
    * Minimum PAC amount member array.
    */
   private String[] _MinPAC = null;
   
   /**
    * Minimum SWP amount member array.
    */
   private String[] _MinSWP = null;
   
   /**
    * Minimum Fund/Class Balance member array.
    */
   private String[] _MinFndClsBal = null;
   
   /**
    * Minimum Account Balance member array.
    */
   private String[] _MinAcctBal = null;
   
   /**
    * Stop Purchase member array.
    */
   private Boolean[] _StopPurchase = null;
   
   /**
    * Stop Redemption member array.
    */
   private Boolean[] _StopRed = null;
   
   /**
    * Stop Transfer in to the fund and class member array.
    */
   private Boolean[] _StopXferIn = null;
   
   /**
    * Stop Transfer out of the fund and class member array.
    */
   private Boolean[] _StopXferOut = null;
   
   /**
    * Alllow Override Defer Sales Charge member array.
    */
   private Boolean[] _OverrideDSCAllow = null;
   
   /**
    * Fixed Price member array.
    */
   private Boolean[] _FixedPrice = null;
   
   /**
    * Fixed Rate member array.
    */
   private String[] _FixedRate = null;
   
   /**
    * Currency Code member array.
    */
   private String[] _Currency = null;
   
   /**
    * Currency Name member array.
    */
   private String[] _CurrencyName = null;
   
   /**
    * Last Valuation Date member array.
    */
   private Date[] _LastValDate = null;
   
   /**
    * Last Dividend Date member array.
    */
   private Date[] _LastDivDate = null;
   
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = null;
   
   /**
    * Created On member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * Cusip Number member array.
    */
   private String[] _CusipNum = null;
   
   /**
    * Baycom Tape Number member array.
    */
   private String[] _Baycom = null;
   
   /**
    * Is Fund Eligible for RRSP plan member array.
    */
   private Boolean[] _RSPflag = null;
   
   /**
    * Is Fund Eligible for RIF plan member array.
    */
   private Boolean[] _RIFflag = null;
   
   /**
    * Fund Stop Date member array.
    */
   private Date[] _StopDate = null;
   
   /**
    * Load Type member array.
    */
   private String[] _LoadType = null;
   
   /**
    * Deemed Domestic member array.
    */
   private Boolean[] _Domestic = null;
   
   /**
    * Wire Eligible member array.
    */
   private Boolean[] _WireElig = null;
   
   /**
    * Next Settlement Date member array.
    */
   private Date[] _NextSettleDate = null;
   
   /**
    * Next Valuation Date member array.
    */
   private Date[] _NextValDate = null;
   
   /**
    * Flag indicating if fund/class is listed as AMS fund member array.
    */
   private Boolean[] _AMSFund = null;
   
   /**
    * No. of decimal places for units member array.
    */
   private Integer[] _UnitsPrecision = null;
   
   /**
    * Default fee currency for Fund/Class from Fee setup (FeeParms) member array.
    */
   private String[] _FeeCurrency = null;
   
   /**
    * Inventory Track member array.
    */
   private Boolean[] _InventoryTrac = null;
   
   /**
    * Split Commissions Exist member array.
    */
   private Boolean[] _SplitComm = null;
   
   /**
    * Override DSC member array.
    */
   private Boolean[] _OverrideDSC = null;
   
   /**
    * ISIN Number member array.
    */
   private String[] _ISINNumber = null;
   
   /**
    * Split Commission - Purchase member array.
    */
   private Boolean[] _SplitCommPur = null;
   
   /**
    * Split Commission - PAC member array.
    */
   private Boolean[] _SplitCommPAC = null;
   
   /**
    * Split Commission - Redemption member array.
    */
   private Boolean[] _SplitCommRed = null;
   
   /**
    * Split Commission - SWP member array.
    */
   private Boolean[] _SplitCommSWP = null;
   
   /**
    * Split Commission -  Transfer In member array.
    */
   private Boolean[] _SplitCommTxIn = null;
   
   /**
    * Split Commission - Exchange In member array.
    */
   private Boolean[] _SplitCommExIn = null;
   
   /**
    * Exchange-In Fee Exists member array.
    */
   private Boolean[] _ExchInFeeExist = null;
   
   /**
    * Allowed Funds for 4th Quarter of AS Plan member array.
    */
   private Boolean[] _ASPensionEligibleQ4 = null;
   
   /**
    * Allowed Funds for first 3 quarters of AS Plan member array.
    */
   private Boolean[] _ASPensionEligibleOth = null;
   
   /**
    * Flag indicating if fund is ESoP eligible member array.
    */
   private Boolean[] _ESoPFlag = null;
   
   /**
    * Last Night Run Date member array.
    */
   private Date[] _LastNightRun = null;
   
   /**
    * Next Night Run Date member array.
    */
   private Date[] _NextNightRun = null;
   
   /**
    * Contract Type member array.
    */
   private String[] _ContractType = null;
   
   /**
    * Management Fee Eligible member array.
    */
   private Boolean[] _MgtFeeElig = null;
   
   /**
    * Management Fee Rebate Eligible member array.
    */
   private Boolean[] _MgtFeeRbtElig = null;
   
   /**
    * Company Code member array.
    */
   private String[] _CompanyCode = null;
   
   /**
    * Last Mgt Fee Date member array.
    */
   private Date[] _LastMFeeDate = null;
   
   /**
    * Last Mgt Fee Rebate Date member array.
    */
   private Date[] _LastMFRDate = null;
   
   /**
    * StopPAC member array.
    */
   private Boolean[] _StopPAC = null;
   
   /**
    * StopSWP member array.
    */
   private Boolean[] _StopSWP = null;
   
   /**
    * StopSysGenTrnfrIn member array.
    */
   private Boolean[] _StopSysGenTrnfrIn = null;
   
   /**
    * StopSysGenTrfrOut member array.
    */
   private Boolean[] _StopSysGenTrfrOut = null;
   
   /**
    * StopPACEWI member array.
    */
   private Boolean[] _StopPACEWI = null;
   
   /**
    * StopSWP member array.
    */
   private Boolean[] _StopSWPEWI = null;
   
   /**
    * StopSysGenTrnfrIn member array.
    */
   private Boolean[] _StopSysGenTrnfrInEWI = null;
   
   /**
    * StopSysGenTrfrOut member array.
    */
   private Boolean[] _StopSysGenTrfrOutEWI = null;
   
   /**
    * Is Fund Eligible for FC Tranfer member array.
    */
   private Boolean[] _FCTransferElig = null;
   
   /**
    * Is Fund Eligible for Margin member array.
    */
   private Boolean[] _MarginEligible = null;
   
   /**
    * Market Index Code member array.
    */
   private String[] _IndexCode = null;
   
   /**
    * flag indicating if Fund is DCAF fund member array.
    */
   private Boolean[] _DCAFFund = null;
   
   /**
    * Flag indicating if fund is Wrap Fund member array.
    */
   private Boolean[] _WrapFund = null;
   
   /**
    * Process Dividend member array.
    */
   private String[] _ProcessDiv = null;
   
   /**
    * Last Interest Accrual Date member array.
    */
   private Date[] _LastIntAccDate = null;
   
   /**
    * NSCCCompliant member array.
    */
   private Boolean[] _NSCCCompliant = null;
   
   /**
    * AMS Eligible member array.
    */
   private Boolean[] _AMSEligible = null;
   
   /**
    * Common Rebate Transactions member array.
    */
   private Boolean[] _CommRebStop = null;
   
   /**
    * Fund WKN member array.
    */
   private String[] _FundWKN = null;
   
   /**
    * Fund ISIN member array.
    */
   private String[] _FundISIN = null;
   
   /**
    * Valid Settle Currency member array.
    */
   private String[] _ValidSettleCurr = null;
   
   /**
    * UnitsCalc member array.
    */
   private String[] _UnitsCalc = null;
   
   /**
    * Date fund first became in scope member array.
    */
   private Date[] _FirstScopeDate = null;
   
   /**
    * Date fund first became lookthrough member array.
    */
   private Date[] _FirstLookthruDate = null;
   
   /**
    * List of transaction types eligible for custom schedule member array.
    */
   private String[] _SchedTransType = null;
   
   /**
    * Default Order Type member array.
    */
   private String[] _DftOrdType = null;
   
   /**
    * Fund Load Group member array.
    */
   private String[] _FundLoadGrp = null;
   
   /**
    * FOF Fund member array.
    */
   private Boolean[] _FOFFund = null;
   
   /**
    * Status member array.
    */
   private String[] _FundStat = null;
   
   /**
    * Status Date member array.
    */
   private Date[] _FundStatDate = null;
   
   /**
    * Unit Rounding Method member array.
    */
   private String[] _UnitRoundMethod = null;
   
   /**
    * Fund Subcategory List member array.
    */
   private String[] _FundSubCat = null;
   
   /**
    * ERISA Prohibited member array.
    */
   private Boolean[] _ERISAProhibited = null;
   
   /**
    * Combined Load Type member array.
    */
   private String[] _CombinedLoadType = null;
   
   /**
    * AMS Model Type member array.
    */
   private String[] _AMSModelType = null;
   
   /**
    * G1G2 Track Type member array.
    */
   private String[] _G1G2TrackType = null;
   
   /**
    * Fund Id Value member array.
    */
   private String[] _FundIdValue = null;
   
   /**
    * Rollover Applicable member array.
    */
   private String[] _RolloverApplicable = null;
   
   /**
    * Rollover To Fund Class member array.
    */
   private String[] _RolloverToFundClass = null;
   
   /**
    * Rollover Amount Type member array.
    */
   private String[] _RolloverAmtType = null;
   
   /**
    * GAV Price Applicable member array.
    */
   private String[] _GAVApply = null;
   
   /**
    * Round Flag member array.
    */
   private String[] _RoundFlag = null;
   
   /**
    * RecDtExists member array.
    */
   private Boolean[] _RecDtExists = null;
   

   /**
    * Constructs the FundDetailLimitationView object.
    * 
    */
   public FundDetailLimitationView()
   {
      super ( new FundDetailLimitationRequest() );
   }

   /**
    * Constructs the FundDetailLimitationView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public FundDetailLimitationView( String hostEncoding )
   {
      super ( new FundDetailLimitationRequest( hostEncoding ) );
   }

   /**
    * Gets the FundDetailLimitationRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The FundDetailLimitationRequest object.
    */
   public final FundDetailLimitationRequest getRequest()
   {
      return (FundDetailLimitationRequest)getIFastRequest();
   }
        
   /**
    * Gets the Record Count for the repeatable response.
    * 
    * @return The number of records in the repeating fields.
    */
   public int getRecordCount()
   {
      return _RepeatCount;
   }

   /**
    * Gets the Record Count for the repeatable response.
    * 
    * @return The number of records in the repeating fields.
    */
   public final int getRepeatCount()
   {
      return _RepeatCount;
   }

   /**
    * Decodes the repeat count value from the host 
    * respones.
    * 
    * @param response Host formatted response object.
    * @exception ParseException
    */
   private final void decodeRepeatCount( RTSResponseDecodeBuffer responseBuffer ) throws ParseException, UnsupportedEncodingException
   {
      int receivedRecordCount = responseBuffer.decodeInteger(responseBuffer.getNextField()).intValue();
      _RepeatCount += receivedRecordCount;
   }

   /**
    * Gets the Fund Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Code or null.
    */
   public final String getFundCode( int index )
   {
      return _FundCode[index];
   }
    
   /**
    * Gets the Fund Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Code or the specified default value.
    */
   public final String getFundCode( int index, String defaultValue )
   {
      return _FundCode[index] == null ? defaultValue : _FundCode[index];
   }
    
   /**
    * Gets the array of Fund Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Code values.
    */
   public final String[] getFundCodeArray()
   {
      return _FundCode;
   }
    
   /**
    * Gets the Class Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Class Code or null.
    */
   public final String getClassCode( int index )
   {
      return _ClassCode[index];
   }
    
   /**
    * Gets the Class Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class Code or the specified default value.
    */
   public final String getClassCode( int index, String defaultValue )
   {
      return _ClassCode[index] == null ? defaultValue : _ClassCode[index];
   }
    
   /**
    * Gets the array of Class Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Class Code values.
    */
   public final String[] getClassCodeArray()
   {
      return _ClassCode;
   }
    
   /**
    * Gets the Class Name in English field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Class Name in English or null.
    */
   public final String getClassE( int index )
   {
      return _ClassE[index];
   }
    
   /**
    * Gets the Class Name in English field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class Name in English or the specified default value.
    */
   public final String getClassE( int index, String defaultValue )
   {
      return _ClassE[index] == null ? defaultValue : _ClassE[index];
   }
    
   /**
    * Gets the array of Class Name in English fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Class Name in English values.
    */
   public final String[] getClassEArray()
   {
      return _ClassE;
   }
    
   /**
    * Gets the Class Name in French field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Class Name in French or null.
    */
   public final String getClassF( int index )
   {
      return _ClassF[index];
   }
    
   /**
    * Gets the Class Name in French field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class Name in French or the specified default value.
    */
   public final String getClassF( int index, String defaultValue )
   {
      return _ClassF[index] == null ? defaultValue : _ClassF[index];
   }
    
   /**
    * Gets the array of Class Name in French fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Class Name in French values.
    */
   public final String[] getClassFArray()
   {
      return _ClassF;
   }
    
   /**
    * Gets the Number of trade delay days field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Number of trade delay days or null.
    */
   public final Integer getAdditionalDays( int index )
   {
      return _AdditionalDays[index];
   }
    
   /**
    * Gets the Number of trade delay days field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Number of trade delay days or the specified default value.
    */
   public final int getAdditionalDays( int index, int defaultValue )
   {
      return _AdditionalDays[index] == null ? defaultValue : _AdditionalDays[index].intValue();
   }
    
   /**
    * Gets the array of Number of trade delay days fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Number of trade delay days values.
    */
   public final Integer[] getAdditionalDaysArray()
   {
      return _AdditionalDays;
   }
    
   /**
    * Gets the Minimum amount for initial purchase field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Minimum amount for initial purchase or null.
    */
   public final String getMinInitPurAmt( int index )
   {
      return _MinInitPurAmt[index];
   }
    
   /**
    * Gets the Minimum amount for initial purchase field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Minimum amount for initial purchase or the specified default value.
    */
   public final String getMinInitPurAmt( int index, String defaultValue )
   {
      return _MinInitPurAmt[index] == null ? defaultValue : _MinInitPurAmt[index];
   }
    
   /**
    * Gets the array of Minimum amount for initial purchase fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Minimum amount for initial purchase values.
    */
   public final String[] getMinInitPurAmtArray()
   {
      return _MinInitPurAmt;
   }
    
   /**
    * Gets the Minimum amt for subsequent purchase field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Minimum amt for subsequent purchase or null.
    */
   public final String getMinSubPurAmt( int index )
   {
      return _MinSubPurAmt[index];
   }
    
   /**
    * Gets the Minimum amt for subsequent purchase field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Minimum amt for subsequent purchase or the specified default value.
    */
   public final String getMinSubPurAmt( int index, String defaultValue )
   {
      return _MinSubPurAmt[index] == null ? defaultValue : _MinSubPurAmt[index];
   }
    
   /**
    * Gets the array of Minimum amt for subsequent purchase fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Minimum amt for subsequent purchase values.
    */
   public final String[] getMinSubPurAmtArray()
   {
      return _MinSubPurAmt;
   }
    
   /**
    * Gets the Minimum amount for initial redemption field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Minimum amount for initial redemption or null.
    */
   public final String getMinInitRedAmt( int index )
   {
      return _MinInitRedAmt[index];
   }
    
   /**
    * Gets the Minimum amount for initial redemption field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Minimum amount for initial redemption or the specified default value.
    */
   public final String getMinInitRedAmt( int index, String defaultValue )
   {
      return _MinInitRedAmt[index] == null ? defaultValue : _MinInitRedAmt[index];
   }
    
   /**
    * Gets the array of Minimum amount for initial redemption fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Minimum amount for initial redemption values.
    */
   public final String[] getMinInitRedAmtArray()
   {
      return _MinInitRedAmt;
   }
    
   /**
    * Gets the Minimum amt for subsequent redemption field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Minimum amt for subsequent redemption or null.
    */
   public final String getMinSubRedAmt( int index )
   {
      return _MinSubRedAmt[index];
   }
    
   /**
    * Gets the Minimum amt for subsequent redemption field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Minimum amt for subsequent redemption or the specified default value.
    */
   public final String getMinSubRedAmt( int index, String defaultValue )
   {
      return _MinSubRedAmt[index] == null ? defaultValue : _MinSubRedAmt[index];
   }
    
   /**
    * Gets the array of Minimum amt for subsequent redemption fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Minimum amt for subsequent redemption values.
    */
   public final String[] getMinSubRedAmtArray()
   {
      return _MinSubRedAmt;
   }
    
   /**
    * Gets the Minimum PAC amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Minimum PAC amount or null.
    */
   public final String getMinPAC( int index )
   {
      return _MinPAC[index];
   }
    
   /**
    * Gets the Minimum PAC amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Minimum PAC amount or the specified default value.
    */
   public final String getMinPAC( int index, String defaultValue )
   {
      return _MinPAC[index] == null ? defaultValue : _MinPAC[index];
   }
    
   /**
    * Gets the array of Minimum PAC amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Minimum PAC amount values.
    */
   public final String[] getMinPACArray()
   {
      return _MinPAC;
   }
    
   /**
    * Gets the Minimum SWP amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Minimum SWP amount or null.
    */
   public final String getMinSWP( int index )
   {
      return _MinSWP[index];
   }
    
   /**
    * Gets the Minimum SWP amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Minimum SWP amount or the specified default value.
    */
   public final String getMinSWP( int index, String defaultValue )
   {
      return _MinSWP[index] == null ? defaultValue : _MinSWP[index];
   }
    
   /**
    * Gets the array of Minimum SWP amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Minimum SWP amount values.
    */
   public final String[] getMinSWPArray()
   {
      return _MinSWP;
   }
    
   /**
    * Gets the Minimum Fund/Class Balance field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Minimum Fund/Class Balance or null.
    */
   public final String getMinFndClsBal( int index )
   {
      return _MinFndClsBal[index];
   }
    
   /**
    * Gets the Minimum Fund/Class Balance field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Minimum Fund/Class Balance or the specified default value.
    */
   public final String getMinFndClsBal( int index, String defaultValue )
   {
      return _MinFndClsBal[index] == null ? defaultValue : _MinFndClsBal[index];
   }
    
   /**
    * Gets the array of Minimum Fund/Class Balance fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Minimum Fund/Class Balance values.
    */
   public final String[] getMinFndClsBalArray()
   {
      return _MinFndClsBal;
   }
    
   /**
    * Gets the Minimum Account Balance field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Minimum Account Balance or null.
    */
   public final String getMinAcctBal( int index )
   {
      return _MinAcctBal[index];
   }
    
   /**
    * Gets the Minimum Account Balance field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Minimum Account Balance or the specified default value.
    */
   public final String getMinAcctBal( int index, String defaultValue )
   {
      return _MinAcctBal[index] == null ? defaultValue : _MinAcctBal[index];
   }
    
   /**
    * Gets the array of Minimum Account Balance fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Minimum Account Balance values.
    */
   public final String[] getMinAcctBalArray()
   {
      return _MinAcctBal;
   }
    
   /**
    * Gets the Stop Purchase field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stop Purchase or null.
    */
   public final Boolean getStopPurchase( int index )
   {
      return _StopPurchase[index];
   }
    
   /**
    * Gets the Stop Purchase field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Purchase or the specified default value.
    */
   public final boolean getStopPurchase( int index, boolean defaultValue )
   {
      return _StopPurchase[index] == null ? defaultValue : _StopPurchase[index].booleanValue();
   }
    
   /**
    * Gets the array of Stop Purchase fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stop Purchase values.
    */
   public final Boolean[] getStopPurchaseArray()
   {
      return _StopPurchase;
   }
    
   /**
    * Gets the Stop Redemption field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stop Redemption or null.
    */
   public final Boolean getStopRed( int index )
   {
      return _StopRed[index];
   }
    
   /**
    * Gets the Stop Redemption field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Redemption or the specified default value.
    */
   public final boolean getStopRed( int index, boolean defaultValue )
   {
      return _StopRed[index] == null ? defaultValue : _StopRed[index].booleanValue();
   }
    
   /**
    * Gets the array of Stop Redemption fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stop Redemption values.
    */
   public final Boolean[] getStopRedArray()
   {
      return _StopRed;
   }
    
   /**
    * Gets the Stop Transfer in to the fund and class field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stop Transfer in to the fund and class or null.
    */
   public final Boolean getStopXferIn( int index )
   {
      return _StopXferIn[index];
   }
    
   /**
    * Gets the Stop Transfer in to the fund and class field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Transfer in to the fund and class or the specified default value.
    */
   public final boolean getStopXferIn( int index, boolean defaultValue )
   {
      return _StopXferIn[index] == null ? defaultValue : _StopXferIn[index].booleanValue();
   }
    
   /**
    * Gets the array of Stop Transfer in to the fund and class fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stop Transfer in to the fund and class values.
    */
   public final Boolean[] getStopXferInArray()
   {
      return _StopXferIn;
   }
    
   /**
    * Gets the Stop Transfer out of the fund and class field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stop Transfer out of the fund and class or null.
    */
   public final Boolean getStopXferOut( int index )
   {
      return _StopXferOut[index];
   }
    
   /**
    * Gets the Stop Transfer out of the fund and class field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Transfer out of the fund and class or the specified default value.
    */
   public final boolean getStopXferOut( int index, boolean defaultValue )
   {
      return _StopXferOut[index] == null ? defaultValue : _StopXferOut[index].booleanValue();
   }
    
   /**
    * Gets the array of Stop Transfer out of the fund and class fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stop Transfer out of the fund and class values.
    */
   public final Boolean[] getStopXferOutArray()
   {
      return _StopXferOut;
   }
    
   /**
    * Gets the Alllow Override Defer Sales Charge field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Alllow Override Defer Sales Charge or null.
    */
   public final Boolean getOverrideDSCAllow( int index )
   {
      return _OverrideDSCAllow[index];
   }
    
   /**
    * Gets the Alllow Override Defer Sales Charge field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Alllow Override Defer Sales Charge or the specified default value.
    */
   public final boolean getOverrideDSCAllow( int index, boolean defaultValue )
   {
      return _OverrideDSCAllow[index] == null ? defaultValue : _OverrideDSCAllow[index].booleanValue();
   }
    
   /**
    * Gets the array of Alllow Override Defer Sales Charge fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Alllow Override Defer Sales Charge values.
    */
   public final Boolean[] getOverrideDSCAllowArray()
   {
      return _OverrideDSCAllow;
   }
    
   /**
    * Gets the Fixed Price field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fixed Price or null.
    */
   public final Boolean getFixedPrice( int index )
   {
      return _FixedPrice[index];
   }
    
   /**
    * Gets the Fixed Price field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fixed Price or the specified default value.
    */
   public final boolean getFixedPrice( int index, boolean defaultValue )
   {
      return _FixedPrice[index] == null ? defaultValue : _FixedPrice[index].booleanValue();
   }
    
   /**
    * Gets the array of Fixed Price fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fixed Price values.
    */
   public final Boolean[] getFixedPriceArray()
   {
      return _FixedPrice;
   }
    
   /**
    * Gets the Fixed Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fixed Rate or null.
    */
   public final String getFixedRate( int index )
   {
      return _FixedRate[index];
   }
    
   /**
    * Gets the Fixed Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fixed Rate or the specified default value.
    */
   public final String getFixedRate( int index, String defaultValue )
   {
      return _FixedRate[index] == null ? defaultValue : _FixedRate[index];
   }
    
   /**
    * Gets the array of Fixed Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fixed Rate values.
    */
   public final String[] getFixedRateArray()
   {
      return _FixedRate;
   }
    
   /**
    * Gets the Currency Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Currency Code or null.
    */
   public final String getCurrency( int index )
   {
      return _Currency[index];
   }
    
   /**
    * Gets the Currency Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Currency Code or the specified default value.
    */
   public final String getCurrency( int index, String defaultValue )
   {
      return _Currency[index] == null ? defaultValue : _Currency[index];
   }
    
   /**
    * Gets the array of Currency Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Currency Code values.
    */
   public final String[] getCurrencyArray()
   {
      return _Currency;
   }
    
   /**
    * Gets the Currency Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Currency Name or null.
    */
   public final String getCurrencyName( int index )
   {
      return _CurrencyName[index];
   }
    
   /**
    * Gets the Currency Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Currency Name or the specified default value.
    */
   public final String getCurrencyName( int index, String defaultValue )
   {
      return _CurrencyName[index] == null ? defaultValue : _CurrencyName[index];
   }
    
   /**
    * Gets the array of Currency Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Currency Name values.
    */
   public final String[] getCurrencyNameArray()
   {
      return _CurrencyName;
   }
    
   /**
    * Gets the Last Valuation Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Last Valuation Date or null.
    */
   public final Date getLastValDate( int index )
   {
      return _LastValDate[index];
   }
    
   /**
    * Gets the Last Valuation Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Last Valuation Date or the specified default value.
    */
   public final Date getLastValDate( int index, Date defaultValue )
   {
      return _LastValDate[index] == null ? defaultValue : _LastValDate[index];
   }
    
   /**
    * Gets the array of Last Valuation Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Last Valuation Date values.
    */
   public final Date[] getLastValDateArray()
   {
      return _LastValDate;
   }
    
   /**
    * Gets the Last Dividend Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Last Dividend Date or null.
    */
   public final Date getLastDivDate( int index )
   {
      return _LastDivDate[index];
   }
    
   /**
    * Gets the Last Dividend Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Last Dividend Date or the specified default value.
    */
   public final Date getLastDivDate( int index, Date defaultValue )
   {
      return _LastDivDate[index] == null ? defaultValue : _LastDivDate[index];
   }
    
   /**
    * Gets the array of Last Dividend Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Last Dividend Date values.
    */
   public final Date[] getLastDivDateArray()
   {
      return _LastDivDate;
   }
    
   /**
    * Gets the Effective Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Effective Date or null.
    */
   public final Date getEffectiveDate( int index )
   {
      return _EffectiveDate[index];
   }
    
   /**
    * Gets the Effective Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Effective Date or the specified default value.
    */
   public final Date getEffectiveDate( int index, Date defaultValue )
   {
      return _EffectiveDate[index] == null ? defaultValue : _EffectiveDate[index];
   }
    
   /**
    * Gets the array of Effective Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Effective Date values.
    */
   public final Date[] getEffectiveDateArray()
   {
      return _EffectiveDate;
   }
    
   /**
    * Gets the Created On field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Created On or null.
    */
   public final Date getProcessDate( int index )
   {
      return _ProcessDate[index];
   }
    
   /**
    * Gets the Created On field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Created On or the specified default value.
    */
   public final Date getProcessDate( int index, Date defaultValue )
   {
      return _ProcessDate[index] == null ? defaultValue : _ProcessDate[index];
   }
    
   /**
    * Gets the array of Created On fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Created On values.
    */
   public final Date[] getProcessDateArray()
   {
      return _ProcessDate;
   }
    
   /**
    * Gets the Cusip Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Cusip Number or null.
    */
   public final String getCusipNum( int index )
   {
      return _CusipNum[index];
   }
    
   /**
    * Gets the Cusip Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Cusip Number or the specified default value.
    */
   public final String getCusipNum( int index, String defaultValue )
   {
      return _CusipNum[index] == null ? defaultValue : _CusipNum[index];
   }
    
   /**
    * Gets the array of Cusip Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Cusip Number values.
    */
   public final String[] getCusipNumArray()
   {
      return _CusipNum;
   }
    
   /**
    * Gets the Baycom Tape Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Baycom Tape Number or null.
    */
   public final String getBaycom( int index )
   {
      return _Baycom[index];
   }
    
   /**
    * Gets the Baycom Tape Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Baycom Tape Number or the specified default value.
    */
   public final String getBaycom( int index, String defaultValue )
   {
      return _Baycom[index] == null ? defaultValue : _Baycom[index];
   }
    
   /**
    * Gets the array of Baycom Tape Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Baycom Tape Number values.
    */
   public final String[] getBaycomArray()
   {
      return _Baycom;
   }
    
   /**
    * Gets the Is Fund Eligible for RRSP plan field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Is Fund Eligible for RRSP plan or null.
    */
   public final Boolean getRSPflag( int index )
   {
      return _RSPflag[index];
   }
    
   /**
    * Gets the Is Fund Eligible for RRSP plan field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Is Fund Eligible for RRSP plan or the specified default value.
    */
   public final boolean getRSPflag( int index, boolean defaultValue )
   {
      return _RSPflag[index] == null ? defaultValue : _RSPflag[index].booleanValue();
   }
    
   /**
    * Gets the array of Is Fund Eligible for RRSP plan fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Is Fund Eligible for RRSP plan values.
    */
   public final Boolean[] getRSPflagArray()
   {
      return _RSPflag;
   }
    
   /**
    * Gets the Is Fund Eligible for RIF plan field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Is Fund Eligible for RIF plan or null.
    */
   public final Boolean getRIFflag( int index )
   {
      return _RIFflag[index];
   }
    
   /**
    * Gets the Is Fund Eligible for RIF plan field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Is Fund Eligible for RIF plan or the specified default value.
    */
   public final boolean getRIFflag( int index, boolean defaultValue )
   {
      return _RIFflag[index] == null ? defaultValue : _RIFflag[index].booleanValue();
   }
    
   /**
    * Gets the array of Is Fund Eligible for RIF plan fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Is Fund Eligible for RIF plan values.
    */
   public final Boolean[] getRIFflagArray()
   {
      return _RIFflag;
   }
    
   /**
    * Gets the Fund Stop Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Stop Date or null.
    */
   public final Date getStopDate( int index )
   {
      return _StopDate[index];
   }
    
   /**
    * Gets the Fund Stop Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Stop Date or the specified default value.
    */
   public final Date getStopDate( int index, Date defaultValue )
   {
      return _StopDate[index] == null ? defaultValue : _StopDate[index];
   }
    
   /**
    * Gets the array of Fund Stop Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Stop Date values.
    */
   public final Date[] getStopDateArray()
   {
      return _StopDate;
   }
    
   /**
    * Gets the Load Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Load Type or null.
    */
   public final String getLoadType( int index )
   {
      return _LoadType[index];
   }
    
   /**
    * Gets the Load Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Load Type or the specified default value.
    */
   public final String getLoadType( int index, String defaultValue )
   {
      return _LoadType[index] == null ? defaultValue : _LoadType[index];
   }
    
   /**
    * Gets the array of Load Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Load Type values.
    */
   public final String[] getLoadTypeArray()
   {
      return _LoadType;
   }
    
   /**
    * Gets the Deemed Domestic field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Deemed Domestic or null.
    */
   public final Boolean getDomestic( int index )
   {
      return _Domestic[index];
   }
    
   /**
    * Gets the Deemed Domestic field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Deemed Domestic or the specified default value.
    */
   public final boolean getDomestic( int index, boolean defaultValue )
   {
      return _Domestic[index] == null ? defaultValue : _Domestic[index].booleanValue();
   }
    
   /**
    * Gets the array of Deemed Domestic fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Deemed Domestic values.
    */
   public final Boolean[] getDomesticArray()
   {
      return _Domestic;
   }
    
   /**
    * Gets the Wire Eligible field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Wire Eligible or null.
    */
   public final Boolean getWireElig( int index )
   {
      return _WireElig[index];
   }
    
   /**
    * Gets the Wire Eligible field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Wire Eligible or the specified default value.
    */
   public final boolean getWireElig( int index, boolean defaultValue )
   {
      return _WireElig[index] == null ? defaultValue : _WireElig[index].booleanValue();
   }
    
   /**
    * Gets the array of Wire Eligible fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Wire Eligible values.
    */
   public final Boolean[] getWireEligArray()
   {
      return _WireElig;
   }
    
   /**
    * Gets the Next Settlement Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Next Settlement Date or null.
    */
   public final Date getNextSettleDate( int index )
   {
      return _NextSettleDate[index];
   }
    
   /**
    * Gets the Next Settlement Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Next Settlement Date or the specified default value.
    */
   public final Date getNextSettleDate( int index, Date defaultValue )
   {
      return _NextSettleDate[index] == null ? defaultValue : _NextSettleDate[index];
   }
    
   /**
    * Gets the array of Next Settlement Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Next Settlement Date values.
    */
   public final Date[] getNextSettleDateArray()
   {
      return _NextSettleDate;
   }
    
   /**
    * Gets the Next Valuation Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Next Valuation Date or null.
    */
   public final Date getNextValDate( int index )
   {
      return _NextValDate[index];
   }
    
   /**
    * Gets the Next Valuation Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Next Valuation Date or the specified default value.
    */
   public final Date getNextValDate( int index, Date defaultValue )
   {
      return _NextValDate[index] == null ? defaultValue : _NextValDate[index];
   }
    
   /**
    * Gets the array of Next Valuation Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Next Valuation Date values.
    */
   public final Date[] getNextValDateArray()
   {
      return _NextValDate;
   }
    
   /**
    * Gets the Flag indicating if fund/class is listed as AMS fund field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicating if fund/class is listed as AMS fund or null.
    */
   public final Boolean getAMSFund( int index )
   {
      return _AMSFund[index];
   }
    
   /**
    * Gets the Flag indicating if fund/class is listed as AMS fund field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if fund/class is listed as AMS fund or the specified default value.
    */
   public final boolean getAMSFund( int index, boolean defaultValue )
   {
      return _AMSFund[index] == null ? defaultValue : _AMSFund[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicating if fund/class is listed as AMS fund fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicating if fund/class is listed as AMS fund values.
    */
   public final Boolean[] getAMSFundArray()
   {
      return _AMSFund;
   }
    
   /**
    * Gets the No. of decimal places for units field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the No. of decimal places for units or null.
    */
   public final Integer getUnitsPrecision( int index )
   {
      return _UnitsPrecision[index];
   }
    
   /**
    * Gets the No. of decimal places for units field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the No. of decimal places for units or the specified default value.
    */
   public final int getUnitsPrecision( int index, int defaultValue )
   {
      return _UnitsPrecision[index] == null ? defaultValue : _UnitsPrecision[index].intValue();
   }
    
   /**
    * Gets the array of No. of decimal places for units fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of No. of decimal places for units values.
    */
   public final Integer[] getUnitsPrecisionArray()
   {
      return _UnitsPrecision;
   }
    
   /**
    * Gets the Default fee currency for Fund/Class from Fee setup (FeeParms) field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Default fee currency for Fund/Class from Fee setup (FeeParms) or null.
    */
   public final String getFeeCurrency( int index )
   {
      return _FeeCurrency[index];
   }
    
   /**
    * Gets the Default fee currency for Fund/Class from Fee setup (FeeParms) field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Default fee currency for Fund/Class from Fee setup (FeeParms) or the specified default value.
    */
   public final String getFeeCurrency( int index, String defaultValue )
   {
      return _FeeCurrency[index] == null ? defaultValue : _FeeCurrency[index];
   }
    
   /**
    * Gets the array of Default fee currency for Fund/Class from Fee setup (FeeParms) fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Default fee currency for Fund/Class from Fee setup (FeeParms) values.
    */
   public final String[] getFeeCurrencyArray()
   {
      return _FeeCurrency;
   }
    
   /**
    * Gets the Inventory Track field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Inventory Track or null.
    */
   public final Boolean getInventoryTrac( int index )
   {
      return _InventoryTrac[index];
   }
    
   /**
    * Gets the Inventory Track field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Inventory Track or the specified default value.
    */
   public final boolean getInventoryTrac( int index, boolean defaultValue )
   {
      return _InventoryTrac[index] == null ? defaultValue : _InventoryTrac[index].booleanValue();
   }
    
   /**
    * Gets the array of Inventory Track fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Inventory Track values.
    */
   public final Boolean[] getInventoryTracArray()
   {
      return _InventoryTrac;
   }
    
   /**
    * Gets the Split Commissions Exist field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Split Commissions Exist or null.
    */
   public final Boolean getSplitComm( int index )
   {
      return _SplitComm[index];
   }
    
   /**
    * Gets the Split Commissions Exist field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Split Commissions Exist or the specified default value.
    */
   public final boolean getSplitComm( int index, boolean defaultValue )
   {
      return _SplitComm[index] == null ? defaultValue : _SplitComm[index].booleanValue();
   }
    
   /**
    * Gets the array of Split Commissions Exist fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Split Commissions Exist values.
    */
   public final Boolean[] getSplitCommArray()
   {
      return _SplitComm;
   }
    
   /**
    * Gets the Override DSC field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Override DSC or null.
    */
   public final Boolean getOverrideDSC( int index )
   {
      return _OverrideDSC[index];
   }
    
   /**
    * Gets the Override DSC field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Override DSC or the specified default value.
    */
   public final boolean getOverrideDSC( int index, boolean defaultValue )
   {
      return _OverrideDSC[index] == null ? defaultValue : _OverrideDSC[index].booleanValue();
   }
    
   /**
    * Gets the array of Override DSC fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Override DSC values.
    */
   public final Boolean[] getOverrideDSCArray()
   {
      return _OverrideDSC;
   }
    
   /**
    * Gets the ISIN Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ISIN Number or null.
    */
   public final String getISINNumber( int index )
   {
      return _ISINNumber[index];
   }
    
   /**
    * Gets the ISIN Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ISIN Number or the specified default value.
    */
   public final String getISINNumber( int index, String defaultValue )
   {
      return _ISINNumber[index] == null ? defaultValue : _ISINNumber[index];
   }
    
   /**
    * Gets the array of ISIN Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ISIN Number values.
    */
   public final String[] getISINNumberArray()
   {
      return _ISINNumber;
   }
    
   /**
    * Gets the Split Commission - Purchase field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Split Commission - Purchase or null.
    */
   public final Boolean getSplitCommPur( int index )
   {
      return _SplitCommPur[index];
   }
    
   /**
    * Gets the Split Commission - Purchase field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Split Commission - Purchase or the specified default value.
    */
   public final boolean getSplitCommPur( int index, boolean defaultValue )
   {
      return _SplitCommPur[index] == null ? defaultValue : _SplitCommPur[index].booleanValue();
   }
    
   /**
    * Gets the array of Split Commission - Purchase fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Split Commission - Purchase values.
    */
   public final Boolean[] getSplitCommPurArray()
   {
      return _SplitCommPur;
   }
    
   /**
    * Gets the Split Commission - PAC field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Split Commission - PAC or null.
    */
   public final Boolean getSplitCommPAC( int index )
   {
      return _SplitCommPAC[index];
   }
    
   /**
    * Gets the Split Commission - PAC field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Split Commission - PAC or the specified default value.
    */
   public final boolean getSplitCommPAC( int index, boolean defaultValue )
   {
      return _SplitCommPAC[index] == null ? defaultValue : _SplitCommPAC[index].booleanValue();
   }
    
   /**
    * Gets the array of Split Commission - PAC fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Split Commission - PAC values.
    */
   public final Boolean[] getSplitCommPACArray()
   {
      return _SplitCommPAC;
   }
    
   /**
    * Gets the Split Commission - Redemption field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Split Commission - Redemption or null.
    */
   public final Boolean getSplitCommRed( int index )
   {
      return _SplitCommRed[index];
   }
    
   /**
    * Gets the Split Commission - Redemption field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Split Commission - Redemption or the specified default value.
    */
   public final boolean getSplitCommRed( int index, boolean defaultValue )
   {
      return _SplitCommRed[index] == null ? defaultValue : _SplitCommRed[index].booleanValue();
   }
    
   /**
    * Gets the array of Split Commission - Redemption fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Split Commission - Redemption values.
    */
   public final Boolean[] getSplitCommRedArray()
   {
      return _SplitCommRed;
   }
    
   /**
    * Gets the Split Commission - SWP field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Split Commission - SWP or null.
    */
   public final Boolean getSplitCommSWP( int index )
   {
      return _SplitCommSWP[index];
   }
    
   /**
    * Gets the Split Commission - SWP field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Split Commission - SWP or the specified default value.
    */
   public final boolean getSplitCommSWP( int index, boolean defaultValue )
   {
      return _SplitCommSWP[index] == null ? defaultValue : _SplitCommSWP[index].booleanValue();
   }
    
   /**
    * Gets the array of Split Commission - SWP fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Split Commission - SWP values.
    */
   public final Boolean[] getSplitCommSWPArray()
   {
      return _SplitCommSWP;
   }
    
   /**
    * Gets the Split Commission -  Transfer In field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Split Commission -  Transfer In or null.
    */
   public final Boolean getSplitCommTxIn( int index )
   {
      return _SplitCommTxIn[index];
   }
    
   /**
    * Gets the Split Commission -  Transfer In field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Split Commission -  Transfer In or the specified default value.
    */
   public final boolean getSplitCommTxIn( int index, boolean defaultValue )
   {
      return _SplitCommTxIn[index] == null ? defaultValue : _SplitCommTxIn[index].booleanValue();
   }
    
   /**
    * Gets the array of Split Commission -  Transfer In fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Split Commission -  Transfer In values.
    */
   public final Boolean[] getSplitCommTxInArray()
   {
      return _SplitCommTxIn;
   }
    
   /**
    * Gets the Split Commission - Exchange In field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Split Commission - Exchange In or null.
    */
   public final Boolean getSplitCommExIn( int index )
   {
      return _SplitCommExIn[index];
   }
    
   /**
    * Gets the Split Commission - Exchange In field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Split Commission - Exchange In or the specified default value.
    */
   public final boolean getSplitCommExIn( int index, boolean defaultValue )
   {
      return _SplitCommExIn[index] == null ? defaultValue : _SplitCommExIn[index].booleanValue();
   }
    
   /**
    * Gets the array of Split Commission - Exchange In fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Split Commission - Exchange In values.
    */
   public final Boolean[] getSplitCommExInArray()
   {
      return _SplitCommExIn;
   }
    
   /**
    * Gets the Exchange-In Fee Exists field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Exchange-In Fee Exists or null.
    */
   public final Boolean getExchInFeeExist( int index )
   {
      return _ExchInFeeExist[index];
   }
    
   /**
    * Gets the Exchange-In Fee Exists field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Exchange-In Fee Exists or the specified default value.
    */
   public final boolean getExchInFeeExist( int index, boolean defaultValue )
   {
      return _ExchInFeeExist[index] == null ? defaultValue : _ExchInFeeExist[index].booleanValue();
   }
    
   /**
    * Gets the array of Exchange-In Fee Exists fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Exchange-In Fee Exists values.
    */
   public final Boolean[] getExchInFeeExistArray()
   {
      return _ExchInFeeExist;
   }
    
   /**
    * Gets the Allowed Funds for 4th Quarter of AS Plan field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Allowed Funds for 4th Quarter of AS Plan or null.
    */
   public final Boolean getASPensionEligibleQ4( int index )
   {
      return _ASPensionEligibleQ4[index];
   }
    
   /**
    * Gets the Allowed Funds for 4th Quarter of AS Plan field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Allowed Funds for 4th Quarter of AS Plan or the specified default value.
    */
   public final boolean getASPensionEligibleQ4( int index, boolean defaultValue )
   {
      return _ASPensionEligibleQ4[index] == null ? defaultValue : _ASPensionEligibleQ4[index].booleanValue();
   }
    
   /**
    * Gets the array of Allowed Funds for 4th Quarter of AS Plan fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Allowed Funds for 4th Quarter of AS Plan values.
    */
   public final Boolean[] getASPensionEligibleQ4Array()
   {
      return _ASPensionEligibleQ4;
   }
    
   /**
    * Gets the Allowed Funds for first 3 quarters of AS Plan field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Allowed Funds for first 3 quarters of AS Plan or null.
    */
   public final Boolean getASPensionEligibleOth( int index )
   {
      return _ASPensionEligibleOth[index];
   }
    
   /**
    * Gets the Allowed Funds for first 3 quarters of AS Plan field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Allowed Funds for first 3 quarters of AS Plan or the specified default value.
    */
   public final boolean getASPensionEligibleOth( int index, boolean defaultValue )
   {
      return _ASPensionEligibleOth[index] == null ? defaultValue : _ASPensionEligibleOth[index].booleanValue();
   }
    
   /**
    * Gets the array of Allowed Funds for first 3 quarters of AS Plan fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Allowed Funds for first 3 quarters of AS Plan values.
    */
   public final Boolean[] getASPensionEligibleOthArray()
   {
      return _ASPensionEligibleOth;
   }
    
   /**
    * Gets the Flag indicating if fund is ESoP eligible field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicating if fund is ESoP eligible or null.
    */
   public final Boolean getESoPFlag( int index )
   {
      return _ESoPFlag[index];
   }
    
   /**
    * Gets the Flag indicating if fund is ESoP eligible field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if fund is ESoP eligible or the specified default value.
    */
   public final boolean getESoPFlag( int index, boolean defaultValue )
   {
      return _ESoPFlag[index] == null ? defaultValue : _ESoPFlag[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicating if fund is ESoP eligible fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicating if fund is ESoP eligible values.
    */
   public final Boolean[] getESoPFlagArray()
   {
      return _ESoPFlag;
   }
    
   /**
    * Gets the Last Night Run Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Last Night Run Date or null.
    */
   public final Date getLastNightRun( int index )
   {
      return _LastNightRun[index];
   }
    
   /**
    * Gets the Last Night Run Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Last Night Run Date or the specified default value.
    */
   public final Date getLastNightRun( int index, Date defaultValue )
   {
      return _LastNightRun[index] == null ? defaultValue : _LastNightRun[index];
   }
    
   /**
    * Gets the array of Last Night Run Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Last Night Run Date values.
    */
   public final Date[] getLastNightRunArray()
   {
      return _LastNightRun;
   }
    
   /**
    * Gets the Next Night Run Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Next Night Run Date or null.
    */
   public final Date getNextNightRun( int index )
   {
      return _NextNightRun[index];
   }
    
   /**
    * Gets the Next Night Run Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Next Night Run Date or the specified default value.
    */
   public final Date getNextNightRun( int index, Date defaultValue )
   {
      return _NextNightRun[index] == null ? defaultValue : _NextNightRun[index];
   }
    
   /**
    * Gets the array of Next Night Run Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Next Night Run Date values.
    */
   public final Date[] getNextNightRunArray()
   {
      return _NextNightRun;
   }
    
   /**
    * Gets the Contract Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contract Type or null.
    */
   public final String getContractType( int index )
   {
      return _ContractType[index];
   }
    
   /**
    * Gets the Contract Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contract Type or the specified default value.
    */
   public final String getContractType( int index, String defaultValue )
   {
      return _ContractType[index] == null ? defaultValue : _ContractType[index];
   }
    
   /**
    * Gets the array of Contract Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contract Type values.
    */
   public final String[] getContractTypeArray()
   {
      return _ContractType;
   }
    
   /**
    * Gets the Management Fee Eligible field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Management Fee Eligible or null.
    */
   public final Boolean getMgtFeeElig( int index )
   {
      return _MgtFeeElig[index];
   }
    
   /**
    * Gets the Management Fee Eligible field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Management Fee Eligible or the specified default value.
    */
   public final boolean getMgtFeeElig( int index, boolean defaultValue )
   {
      return _MgtFeeElig[index] == null ? defaultValue : _MgtFeeElig[index].booleanValue();
   }
    
   /**
    * Gets the array of Management Fee Eligible fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Management Fee Eligible values.
    */
   public final Boolean[] getMgtFeeEligArray()
   {
      return _MgtFeeElig;
   }
    
   /**
    * Gets the Management Fee Rebate Eligible field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Management Fee Rebate Eligible or null.
    */
   public final Boolean getMgtFeeRbtElig( int index )
   {
      return _MgtFeeRbtElig[index];
   }
    
   /**
    * Gets the Management Fee Rebate Eligible field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Management Fee Rebate Eligible or the specified default value.
    */
   public final boolean getMgtFeeRbtElig( int index, boolean defaultValue )
   {
      return _MgtFeeRbtElig[index] == null ? defaultValue : _MgtFeeRbtElig[index].booleanValue();
   }
    
   /**
    * Gets the array of Management Fee Rebate Eligible fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Management Fee Rebate Eligible values.
    */
   public final Boolean[] getMgtFeeRbtEligArray()
   {
      return _MgtFeeRbtElig;
   }
    
   /**
    * Gets the Company Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Company Code or null.
    */
   public final String getCompanyCode( int index )
   {
      return _CompanyCode[index];
   }
    
   /**
    * Gets the Company Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Company Code or the specified default value.
    */
   public final String getCompanyCode( int index, String defaultValue )
   {
      return _CompanyCode[index] == null ? defaultValue : _CompanyCode[index];
   }
    
   /**
    * Gets the array of Company Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Company Code values.
    */
   public final String[] getCompanyCodeArray()
   {
      return _CompanyCode;
   }
    
   /**
    * Gets the Last Mgt Fee Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Last Mgt Fee Date or null.
    */
   public final Date getLastMFeeDate( int index )
   {
      return _LastMFeeDate[index];
   }
    
   /**
    * Gets the Last Mgt Fee Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Last Mgt Fee Date or the specified default value.
    */
   public final Date getLastMFeeDate( int index, Date defaultValue )
   {
      return _LastMFeeDate[index] == null ? defaultValue : _LastMFeeDate[index];
   }
    
   /**
    * Gets the array of Last Mgt Fee Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Last Mgt Fee Date values.
    */
   public final Date[] getLastMFeeDateArray()
   {
      return _LastMFeeDate;
   }
    
   /**
    * Gets the Last Mgt Fee Rebate Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Last Mgt Fee Rebate Date or null.
    */
   public final Date getLastMFRDate( int index )
   {
      return _LastMFRDate[index];
   }
    
   /**
    * Gets the Last Mgt Fee Rebate Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Last Mgt Fee Rebate Date or the specified default value.
    */
   public final Date getLastMFRDate( int index, Date defaultValue )
   {
      return _LastMFRDate[index] == null ? defaultValue : _LastMFRDate[index];
   }
    
   /**
    * Gets the array of Last Mgt Fee Rebate Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Last Mgt Fee Rebate Date values.
    */
   public final Date[] getLastMFRDateArray()
   {
      return _LastMFRDate;
   }
    
   /**
    * Gets the StopPAC field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the StopPAC or null.
    */
   public final Boolean getStopPAC( int index )
   {
      return _StopPAC[index];
   }
    
   /**
    * Gets the StopPAC field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the StopPAC or the specified default value.
    */
   public final boolean getStopPAC( int index, boolean defaultValue )
   {
      return _StopPAC[index] == null ? defaultValue : _StopPAC[index].booleanValue();
   }
    
   /**
    * Gets the array of StopPAC fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of StopPAC values.
    */
   public final Boolean[] getStopPACArray()
   {
      return _StopPAC;
   }
    
   /**
    * Gets the StopSWP field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the StopSWP or null.
    */
   public final Boolean getStopSWP( int index )
   {
      return _StopSWP[index];
   }
    
   /**
    * Gets the StopSWP field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the StopSWP or the specified default value.
    */
   public final boolean getStopSWP( int index, boolean defaultValue )
   {
      return _StopSWP[index] == null ? defaultValue : _StopSWP[index].booleanValue();
   }
    
   /**
    * Gets the array of StopSWP fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of StopSWP values.
    */
   public final Boolean[] getStopSWPArray()
   {
      return _StopSWP;
   }
    
   /**
    * Gets the StopSysGenTrnfrIn field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the StopSysGenTrnfrIn or null.
    */
   public final Boolean getStopSysGenTrnfrIn( int index )
   {
      return _StopSysGenTrnfrIn[index];
   }
    
   /**
    * Gets the StopSysGenTrnfrIn field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the StopSysGenTrnfrIn or the specified default value.
    */
   public final boolean getStopSysGenTrnfrIn( int index, boolean defaultValue )
   {
      return _StopSysGenTrnfrIn[index] == null ? defaultValue : _StopSysGenTrnfrIn[index].booleanValue();
   }
    
   /**
    * Gets the array of StopSysGenTrnfrIn fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of StopSysGenTrnfrIn values.
    */
   public final Boolean[] getStopSysGenTrnfrInArray()
   {
      return _StopSysGenTrnfrIn;
   }
    
   /**
    * Gets the StopSysGenTrfrOut field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the StopSysGenTrfrOut or null.
    */
   public final Boolean getStopSysGenTrfrOut( int index )
   {
      return _StopSysGenTrfrOut[index];
   }
    
   /**
    * Gets the StopSysGenTrfrOut field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the StopSysGenTrfrOut or the specified default value.
    */
   public final boolean getStopSysGenTrfrOut( int index, boolean defaultValue )
   {
      return _StopSysGenTrfrOut[index] == null ? defaultValue : _StopSysGenTrfrOut[index].booleanValue();
   }
    
   /**
    * Gets the array of StopSysGenTrfrOut fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of StopSysGenTrfrOut values.
    */
   public final Boolean[] getStopSysGenTrfrOutArray()
   {
      return _StopSysGenTrfrOut;
   }
    
   /**
    * Gets the StopPACEWI field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the StopPACEWI or null.
    */
   public final Boolean getStopPACEWI( int index )
   {
      return _StopPACEWI[index];
   }
    
   /**
    * Gets the StopPACEWI field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the StopPACEWI or the specified default value.
    */
   public final boolean getStopPACEWI( int index, boolean defaultValue )
   {
      return _StopPACEWI[index] == null ? defaultValue : _StopPACEWI[index].booleanValue();
   }
    
   /**
    * Gets the array of StopPACEWI fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of StopPACEWI values.
    */
   public final Boolean[] getStopPACEWIArray()
   {
      return _StopPACEWI;
   }
    
   /**
    * Gets the StopSWP field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the StopSWP or null.
    */
   public final Boolean getStopSWPEWI( int index )
   {
      return _StopSWPEWI[index];
   }
    
   /**
    * Gets the StopSWP field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the StopSWP or the specified default value.
    */
   public final boolean getStopSWPEWI( int index, boolean defaultValue )
   {
      return _StopSWPEWI[index] == null ? defaultValue : _StopSWPEWI[index].booleanValue();
   }
    
   /**
    * Gets the array of StopSWP fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of StopSWP values.
    */
   public final Boolean[] getStopSWPEWIArray()
   {
      return _StopSWPEWI;
   }
    
   /**
    * Gets the StopSysGenTrnfrIn field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the StopSysGenTrnfrIn or null.
    */
   public final Boolean getStopSysGenTrnfrInEWI( int index )
   {
      return _StopSysGenTrnfrInEWI[index];
   }
    
   /**
    * Gets the StopSysGenTrnfrIn field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the StopSysGenTrnfrIn or the specified default value.
    */
   public final boolean getStopSysGenTrnfrInEWI( int index, boolean defaultValue )
   {
      return _StopSysGenTrnfrInEWI[index] == null ? defaultValue : _StopSysGenTrnfrInEWI[index].booleanValue();
   }
    
   /**
    * Gets the array of StopSysGenTrnfrIn fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of StopSysGenTrnfrIn values.
    */
   public final Boolean[] getStopSysGenTrnfrInEWIArray()
   {
      return _StopSysGenTrnfrInEWI;
   }
    
   /**
    * Gets the StopSysGenTrfrOut field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the StopSysGenTrfrOut or null.
    */
   public final Boolean getStopSysGenTrfrOutEWI( int index )
   {
      return _StopSysGenTrfrOutEWI[index];
   }
    
   /**
    * Gets the StopSysGenTrfrOut field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the StopSysGenTrfrOut or the specified default value.
    */
   public final boolean getStopSysGenTrfrOutEWI( int index, boolean defaultValue )
   {
      return _StopSysGenTrfrOutEWI[index] == null ? defaultValue : _StopSysGenTrfrOutEWI[index].booleanValue();
   }
    
   /**
    * Gets the array of StopSysGenTrfrOut fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of StopSysGenTrfrOut values.
    */
   public final Boolean[] getStopSysGenTrfrOutEWIArray()
   {
      return _StopSysGenTrfrOutEWI;
   }
    
   /**
    * Gets the Is Fund Eligible for FC Tranfer field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Is Fund Eligible for FC Tranfer or null.
    */
   public final Boolean getFCTransferElig( int index )
   {
      return _FCTransferElig[index];
   }
    
   /**
    * Gets the Is Fund Eligible for FC Tranfer field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Is Fund Eligible for FC Tranfer or the specified default value.
    */
   public final boolean getFCTransferElig( int index, boolean defaultValue )
   {
      return _FCTransferElig[index] == null ? defaultValue : _FCTransferElig[index].booleanValue();
   }
    
   /**
    * Gets the array of Is Fund Eligible for FC Tranfer fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Is Fund Eligible for FC Tranfer values.
    */
   public final Boolean[] getFCTransferEligArray()
   {
      return _FCTransferElig;
   }
    
   /**
    * Gets the Is Fund Eligible for Margin field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Is Fund Eligible for Margin or null.
    */
   public final Boolean getMarginEligible( int index )
   {
      return _MarginEligible[index];
   }
    
   /**
    * Gets the Is Fund Eligible for Margin field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Is Fund Eligible for Margin or the specified default value.
    */
   public final boolean getMarginEligible( int index, boolean defaultValue )
   {
      return _MarginEligible[index] == null ? defaultValue : _MarginEligible[index].booleanValue();
   }
    
   /**
    * Gets the array of Is Fund Eligible for Margin fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Is Fund Eligible for Margin values.
    */
   public final Boolean[] getMarginEligibleArray()
   {
      return _MarginEligible;
   }
    
   /**
    * Gets the Market Index Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Market Index Code or null.
    */
   public final String getIndexCode( int index )
   {
      return _IndexCode[index];
   }
    
   /**
    * Gets the Market Index Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Market Index Code or the specified default value.
    */
   public final String getIndexCode( int index, String defaultValue )
   {
      return _IndexCode[index] == null ? defaultValue : _IndexCode[index];
   }
    
   /**
    * Gets the array of Market Index Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Market Index Code values.
    */
   public final String[] getIndexCodeArray()
   {
      return _IndexCode;
   }
    
   /**
    * Gets the flag indicating if Fund is DCAF fund field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the flag indicating if Fund is DCAF fund or null.
    */
   public final Boolean getDCAFFund( int index )
   {
      return _DCAFFund[index];
   }
    
   /**
    * Gets the flag indicating if Fund is DCAF fund field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the flag indicating if Fund is DCAF fund or the specified default value.
    */
   public final boolean getDCAFFund( int index, boolean defaultValue )
   {
      return _DCAFFund[index] == null ? defaultValue : _DCAFFund[index].booleanValue();
   }
    
   /**
    * Gets the array of flag indicating if Fund is DCAF fund fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of flag indicating if Fund is DCAF fund values.
    */
   public final Boolean[] getDCAFFundArray()
   {
      return _DCAFFund;
   }
    
   /**
    * Gets the Flag indicating if fund is Wrap Fund field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicating if fund is Wrap Fund or null.
    */
   public final Boolean getWrapFund( int index )
   {
      return _WrapFund[index];
   }
    
   /**
    * Gets the Flag indicating if fund is Wrap Fund field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if fund is Wrap Fund or the specified default value.
    */
   public final boolean getWrapFund( int index, boolean defaultValue )
   {
      return _WrapFund[index] == null ? defaultValue : _WrapFund[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicating if fund is Wrap Fund fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicating if fund is Wrap Fund values.
    */
   public final Boolean[] getWrapFundArray()
   {
      return _WrapFund;
   }
    
   /**
    * Gets the Process Dividend field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Process Dividend or null.
    */
   public final String getProcessDiv( int index )
   {
      return _ProcessDiv[index];
   }
    
   /**
    * Gets the Process Dividend field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Process Dividend or the specified default value.
    */
   public final String getProcessDiv( int index, String defaultValue )
   {
      return _ProcessDiv[index] == null ? defaultValue : _ProcessDiv[index];
   }
    
   /**
    * Gets the array of Process Dividend fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Process Dividend values.
    */
   public final String[] getProcessDivArray()
   {
      return _ProcessDiv;
   }
    
   /**
    * Gets the Last Interest Accrual Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Last Interest Accrual Date or null.
    */
   public final Date getLastIntAccDate( int index )
   {
      return _LastIntAccDate[index];
   }
    
   /**
    * Gets the Last Interest Accrual Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Last Interest Accrual Date or the specified default value.
    */
   public final Date getLastIntAccDate( int index, Date defaultValue )
   {
      return _LastIntAccDate[index] == null ? defaultValue : _LastIntAccDate[index];
   }
    
   /**
    * Gets the array of Last Interest Accrual Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Last Interest Accrual Date values.
    */
   public final Date[] getLastIntAccDateArray()
   {
      return _LastIntAccDate;
   }
    
   /**
    * Gets the NSCCCompliant field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the NSCCCompliant or null.
    */
   public final Boolean getNSCCCompliant( int index )
   {
      return _NSCCCompliant[index];
   }
    
   /**
    * Gets the NSCCCompliant field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the NSCCCompliant or the specified default value.
    */
   public final boolean getNSCCCompliant( int index, boolean defaultValue )
   {
      return _NSCCCompliant[index] == null ? defaultValue : _NSCCCompliant[index].booleanValue();
   }
    
   /**
    * Gets the array of NSCCCompliant fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of NSCCCompliant values.
    */
   public final Boolean[] getNSCCCompliantArray()
   {
      return _NSCCCompliant;
   }
    
   /**
    * Gets the AMS Eligible field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AMS Eligible or null.
    */
   public final Boolean getAMSEligible( int index )
   {
      return _AMSEligible[index];
   }
    
   /**
    * Gets the AMS Eligible field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AMS Eligible or the specified default value.
    */
   public final boolean getAMSEligible( int index, boolean defaultValue )
   {
      return _AMSEligible[index] == null ? defaultValue : _AMSEligible[index].booleanValue();
   }
    
   /**
    * Gets the array of AMS Eligible fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AMS Eligible values.
    */
   public final Boolean[] getAMSEligibleArray()
   {
      return _AMSEligible;
   }
    
   /**
    * Gets the Common Rebate Transactions field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Common Rebate Transactions or null.
    */
   public final Boolean getCommRebStop( int index )
   {
      return _CommRebStop[index];
   }
    
   /**
    * Gets the Common Rebate Transactions field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Common Rebate Transactions or the specified default value.
    */
   public final boolean getCommRebStop( int index, boolean defaultValue )
   {
      return _CommRebStop[index] == null ? defaultValue : _CommRebStop[index].booleanValue();
   }
    
   /**
    * Gets the array of Common Rebate Transactions fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Common Rebate Transactions values.
    */
   public final Boolean[] getCommRebStopArray()
   {
      return _CommRebStop;
   }
    
   /**
    * Gets the Fund WKN field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund WKN or null.
    */
   public final String getFundWKN( int index )
   {
      return _FundWKN[index];
   }
    
   /**
    * Gets the Fund WKN field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund WKN or the specified default value.
    */
   public final String getFundWKN( int index, String defaultValue )
   {
      return _FundWKN[index] == null ? defaultValue : _FundWKN[index];
   }
    
   /**
    * Gets the array of Fund WKN fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund WKN values.
    */
   public final String[] getFundWKNArray()
   {
      return _FundWKN;
   }
    
   /**
    * Gets the Fund ISIN field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund ISIN or null.
    */
   public final String getFundISIN( int index )
   {
      return _FundISIN[index];
   }
    
   /**
    * Gets the Fund ISIN field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund ISIN or the specified default value.
    */
   public final String getFundISIN( int index, String defaultValue )
   {
      return _FundISIN[index] == null ? defaultValue : _FundISIN[index];
   }
    
   /**
    * Gets the array of Fund ISIN fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund ISIN values.
    */
   public final String[] getFundISINArray()
   {
      return _FundISIN;
   }
    
   /**
    * Gets the Valid Settle Currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Valid Settle Currency or null.
    */
   public final String getValidSettleCurr( int index )
   {
      return _ValidSettleCurr[index];
   }
    
   /**
    * Gets the Valid Settle Currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Valid Settle Currency or the specified default value.
    */
   public final String getValidSettleCurr( int index, String defaultValue )
   {
      return _ValidSettleCurr[index] == null ? defaultValue : _ValidSettleCurr[index];
   }
    
   /**
    * Gets the array of Valid Settle Currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Valid Settle Currency values.
    */
   public final String[] getValidSettleCurrArray()
   {
      return _ValidSettleCurr;
   }
    
   /**
    * Gets the UnitsCalc field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the UnitsCalc or null.
    */
   public final String getUnitsCalc( int index )
   {
      return _UnitsCalc[index];
   }
    
   /**
    * Gets the UnitsCalc field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the UnitsCalc or the specified default value.
    */
   public final String getUnitsCalc( int index, String defaultValue )
   {
      return _UnitsCalc[index] == null ? defaultValue : _UnitsCalc[index];
   }
    
   /**
    * Gets the array of UnitsCalc fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of UnitsCalc values.
    */
   public final String[] getUnitsCalcArray()
   {
      return _UnitsCalc;
   }
    
   /**
    * Gets the Date fund first became in scope field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Date fund first became in scope or null.
    */
   public final Date getFirstScopeDate( int index )
   {
      return _FirstScopeDate[index];
   }
    
   /**
    * Gets the Date fund first became in scope field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date fund first became in scope or the specified default value.
    */
   public final Date getFirstScopeDate( int index, Date defaultValue )
   {
      return _FirstScopeDate[index] == null ? defaultValue : _FirstScopeDate[index];
   }
    
   /**
    * Gets the array of Date fund first became in scope fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Date fund first became in scope values.
    */
   public final Date[] getFirstScopeDateArray()
   {
      return _FirstScopeDate;
   }
    
   /**
    * Gets the Date fund first became lookthrough field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Date fund first became lookthrough or null.
    */
   public final Date getFirstLookthruDate( int index )
   {
      return _FirstLookthruDate[index];
   }
    
   /**
    * Gets the Date fund first became lookthrough field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date fund first became lookthrough or the specified default value.
    */
   public final Date getFirstLookthruDate( int index, Date defaultValue )
   {
      return _FirstLookthruDate[index] == null ? defaultValue : _FirstLookthruDate[index];
   }
    
   /**
    * Gets the array of Date fund first became lookthrough fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Date fund first became lookthrough values.
    */
   public final Date[] getFirstLookthruDateArray()
   {
      return _FirstLookthruDate;
   }
    
   /**
    * Gets the List of transaction types eligible for custom schedule field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the List of transaction types eligible for custom schedule or null.
    */
   public final String getSchedTransType( int index )
   {
      return _SchedTransType[index];
   }
    
   /**
    * Gets the List of transaction types eligible for custom schedule field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the List of transaction types eligible for custom schedule or the specified default value.
    */
   public final String getSchedTransType( int index, String defaultValue )
   {
      return _SchedTransType[index] == null ? defaultValue : _SchedTransType[index];
   }
    
   /**
    * Gets the array of List of transaction types eligible for custom schedule fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of List of transaction types eligible for custom schedule values.
    */
   public final String[] getSchedTransTypeArray()
   {
      return _SchedTransType;
   }
    
   /**
    * Gets the Default Order Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Default Order Type or null.
    */
   public final String getDftOrdType( int index )
   {
      return _DftOrdType[index];
   }
    
   /**
    * Gets the Default Order Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Default Order Type or the specified default value.
    */
   public final String getDftOrdType( int index, String defaultValue )
   {
      return _DftOrdType[index] == null ? defaultValue : _DftOrdType[index];
   }
    
   /**
    * Gets the array of Default Order Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Default Order Type values.
    */
   public final String[] getDftOrdTypeArray()
   {
      return _DftOrdType;
   }
    
   /**
    * Gets the Fund Load Group field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Load Group or null.
    */
   public final String getFundLoadGrp( int index )
   {
      return _FundLoadGrp[index];
   }
    
   /**
    * Gets the Fund Load Group field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Load Group or the specified default value.
    */
   public final String getFundLoadGrp( int index, String defaultValue )
   {
      return _FundLoadGrp[index] == null ? defaultValue : _FundLoadGrp[index];
   }
    
   /**
    * Gets the array of Fund Load Group fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Load Group values.
    */
   public final String[] getFundLoadGrpArray()
   {
      return _FundLoadGrp;
   }
    
   /**
    * Gets the FOF Fund field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FOF Fund or null.
    */
   public final Boolean getFOFFund( int index )
   {
      return _FOFFund[index];
   }
    
   /**
    * Gets the FOF Fund field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FOF Fund or the specified default value.
    */
   public final boolean getFOFFund( int index, boolean defaultValue )
   {
      return _FOFFund[index] == null ? defaultValue : _FOFFund[index].booleanValue();
   }
    
   /**
    * Gets the array of FOF Fund fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FOF Fund values.
    */
   public final Boolean[] getFOFFundArray()
   {
      return _FOFFund;
   }
    
   /**
    * Gets the Status field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Status or null.
    */
   public final String getFundStat( int index )
   {
      return _FundStat[index];
   }
    
   /**
    * Gets the Status field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Status or the specified default value.
    */
   public final String getFundStat( int index, String defaultValue )
   {
      return _FundStat[index] == null ? defaultValue : _FundStat[index];
   }
    
   /**
    * Gets the array of Status fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Status values.
    */
   public final String[] getFundStatArray()
   {
      return _FundStat;
   }
    
   /**
    * Gets the Status Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Status Date or null.
    */
   public final Date getFundStatDate( int index )
   {
      return _FundStatDate[index];
   }
    
   /**
    * Gets the Status Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Status Date or the specified default value.
    */
   public final Date getFundStatDate( int index, Date defaultValue )
   {
      return _FundStatDate[index] == null ? defaultValue : _FundStatDate[index];
   }
    
   /**
    * Gets the array of Status Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Status Date values.
    */
   public final Date[] getFundStatDateArray()
   {
      return _FundStatDate;
   }
    
   /**
    * Gets the Unit Rounding Method field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Unit Rounding Method or null.
    */
   public final String getUnitRoundMethod( int index )
   {
      return _UnitRoundMethod[index];
   }
    
   /**
    * Gets the Unit Rounding Method field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Unit Rounding Method or the specified default value.
    */
   public final String getUnitRoundMethod( int index, String defaultValue )
   {
      return _UnitRoundMethod[index] == null ? defaultValue : _UnitRoundMethod[index];
   }
    
   /**
    * Gets the array of Unit Rounding Method fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Unit Rounding Method values.
    */
   public final String[] getUnitRoundMethodArray()
   {
      return _UnitRoundMethod;
   }
    
   /**
    * Gets the Fund Subcategory List field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Subcategory List or null.
    */
   public final String getFundSubCat( int index )
   {
      return _FundSubCat[index];
   }
    
   /**
    * Gets the Fund Subcategory List field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Subcategory List or the specified default value.
    */
   public final String getFundSubCat( int index, String defaultValue )
   {
      return _FundSubCat[index] == null ? defaultValue : _FundSubCat[index];
   }
    
   /**
    * Gets the array of Fund Subcategory List fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Subcategory List values.
    */
   public final String[] getFundSubCatArray()
   {
      return _FundSubCat;
   }
    
   /**
    * Gets the ERISA Prohibited field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ERISA Prohibited or null.
    */
   public final Boolean getERISAProhibited( int index )
   {
      return _ERISAProhibited[index];
   }
    
   /**
    * Gets the ERISA Prohibited field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ERISA Prohibited or the specified default value.
    */
   public final boolean getERISAProhibited( int index, boolean defaultValue )
   {
      return _ERISAProhibited[index] == null ? defaultValue : _ERISAProhibited[index].booleanValue();
   }
    
   /**
    * Gets the array of ERISA Prohibited fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ERISA Prohibited values.
    */
   public final Boolean[] getERISAProhibitedArray()
   {
      return _ERISAProhibited;
   }
    
   /**
    * Gets the Combined Load Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Combined Load Type or null.
    */
   public final String getCombinedLoadType( int index )
   {
      return _CombinedLoadType[index];
   }
    
   /**
    * Gets the Combined Load Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Combined Load Type or the specified default value.
    */
   public final String getCombinedLoadType( int index, String defaultValue )
   {
      return _CombinedLoadType[index] == null ? defaultValue : _CombinedLoadType[index];
   }
    
   /**
    * Gets the array of Combined Load Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Combined Load Type values.
    */
   public final String[] getCombinedLoadTypeArray()
   {
      return _CombinedLoadType;
   }
    
   /**
    * Gets the AMS Model Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AMS Model Type or null.
    */
   public final String getAMSModelType( int index )
   {
      return _AMSModelType[index];
   }
    
   /**
    * Gets the AMS Model Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AMS Model Type or the specified default value.
    */
   public final String getAMSModelType( int index, String defaultValue )
   {
      return _AMSModelType[index] == null ? defaultValue : _AMSModelType[index];
   }
    
   /**
    * Gets the array of AMS Model Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AMS Model Type values.
    */
   public final String[] getAMSModelTypeArray()
   {
      return _AMSModelType;
   }
    
   /**
    * Gets the G1G2 Track Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the G1G2 Track Type or null.
    */
   public final String getG1G2TrackType( int index )
   {
      return _G1G2TrackType[index];
   }
    
   /**
    * Gets the G1G2 Track Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the G1G2 Track Type or the specified default value.
    */
   public final String getG1G2TrackType( int index, String defaultValue )
   {
      return _G1G2TrackType[index] == null ? defaultValue : _G1G2TrackType[index];
   }
    
   /**
    * Gets the array of G1G2 Track Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of G1G2 Track Type values.
    */
   public final String[] getG1G2TrackTypeArray()
   {
      return _G1G2TrackType;
   }
    
   /**
    * Gets the Fund Id Value field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Id Value or null.
    */
   public final String getFundIdValue( int index )
   {
      return _FundIdValue[index];
   }
    
   /**
    * Gets the Fund Id Value field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Id Value or the specified default value.
    */
   public final String getFundIdValue( int index, String defaultValue )
   {
      return _FundIdValue[index] == null ? defaultValue : _FundIdValue[index];
   }
    
   /**
    * Gets the array of Fund Id Value fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Id Value values.
    */
   public final String[] getFundIdValueArray()
   {
      return _FundIdValue;
   }
    
   /**
    * Gets the Rollover Applicable field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Rollover Applicable or null.
    */
   public final String getRolloverApplicable( int index )
   {
      return _RolloverApplicable[index];
   }
    
   /**
    * Gets the Rollover Applicable field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Rollover Applicable or the specified default value.
    */
   public final String getRolloverApplicable( int index, String defaultValue )
   {
      return _RolloverApplicable[index] == null ? defaultValue : _RolloverApplicable[index];
   }
    
   /**
    * Gets the array of Rollover Applicable fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Rollover Applicable values.
    */
   public final String[] getRolloverApplicableArray()
   {
      return _RolloverApplicable;
   }
    
   /**
    * Gets the Rollover To Fund Class field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Rollover To Fund Class or null.
    */
   public final String getRolloverToFundClass( int index )
   {
      return _RolloverToFundClass[index];
   }
    
   /**
    * Gets the Rollover To Fund Class field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Rollover To Fund Class or the specified default value.
    */
   public final String getRolloverToFundClass( int index, String defaultValue )
   {
      return _RolloverToFundClass[index] == null ? defaultValue : _RolloverToFundClass[index];
   }
    
   /**
    * Gets the array of Rollover To Fund Class fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Rollover To Fund Class values.
    */
   public final String[] getRolloverToFundClassArray()
   {
      return _RolloverToFundClass;
   }
    
   /**
    * Gets the Rollover Amount Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Rollover Amount Type or null.
    */
   public final String getRolloverAmtType( int index )
   {
      return _RolloverAmtType[index];
   }
    
   /**
    * Gets the Rollover Amount Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Rollover Amount Type or the specified default value.
    */
   public final String getRolloverAmtType( int index, String defaultValue )
   {
      return _RolloverAmtType[index] == null ? defaultValue : _RolloverAmtType[index];
   }
    
   /**
    * Gets the array of Rollover Amount Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Rollover Amount Type values.
    */
   public final String[] getRolloverAmtTypeArray()
   {
      return _RolloverAmtType;
   }
    
   /**
    * Gets the GAV Price Applicable field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the GAV Price Applicable or null.
    */
   public final String getGAVApply( int index )
   {
      return _GAVApply[index];
   }
    
   /**
    * Gets the GAV Price Applicable field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the GAV Price Applicable or the specified default value.
    */
   public final String getGAVApply( int index, String defaultValue )
   {
      return _GAVApply[index] == null ? defaultValue : _GAVApply[index];
   }
    
   /**
    * Gets the array of GAV Price Applicable fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of GAV Price Applicable values.
    */
   public final String[] getGAVApplyArray()
   {
      return _GAVApply;
   }
    
   /**
    * Gets the Round Flag field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Round Flag or null.
    */
   public final String getRoundFlag( int index )
   {
      return _RoundFlag[index];
   }
    
   /**
    * Gets the Round Flag field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Round Flag or the specified default value.
    */
   public final String getRoundFlag( int index, String defaultValue )
   {
      return _RoundFlag[index] == null ? defaultValue : _RoundFlag[index];
   }
    
   /**
    * Gets the array of Round Flag fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Round Flag values.
    */
   public final String[] getRoundFlagArray()
   {
      return _RoundFlag;
   }
    
   /**
    * Gets the RecDtExists field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RecDtExists or null.
    */
   public final Boolean getRecDtExists( int index )
   {
      return _RecDtExists[index];
   }
    
   /**
    * Gets the RecDtExists field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RecDtExists or the specified default value.
    */
   public final boolean getRecDtExists( int index, boolean defaultValue )
   {
      return _RecDtExists[index] == null ? defaultValue : _RecDtExists[index].booleanValue();
   }
    
   /**
    * Gets the array of RecDtExists fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RecDtExists values.
    */
   public final Boolean[] getRecDtExistsArray()
   {
      return _RecDtExists;
   }
    
   /**
    * Implements the abstract base method to decode
    * the host formatted response.
    * 
    * @param response Host formatted response object.
    * @exception ParseException
    */
   protected void decodeFields( RTSResponseDecodeBuffer responseBuffer ) throws ParseException, UnsupportedEncodingException
   {
      
      // single-record section
      decodeMoreAvailableField( responseBuffer );
      decodeNextKeyField( responseBuffer );
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _FundCode = resizeArray( _FundCode, _RepeatCount );
      _ClassCode = resizeArray( _ClassCode, _RepeatCount );
      _ClassE = resizeArray( _ClassE, _RepeatCount );
      _ClassF = resizeArray( _ClassF, _RepeatCount );
      _AdditionalDays = resizeArray( _AdditionalDays, _RepeatCount );
      _MinInitPurAmt = resizeArray( _MinInitPurAmt, _RepeatCount );
      _MinSubPurAmt = resizeArray( _MinSubPurAmt, _RepeatCount );
      _MinInitRedAmt = resizeArray( _MinInitRedAmt, _RepeatCount );
      _MinSubRedAmt = resizeArray( _MinSubRedAmt, _RepeatCount );
      _MinPAC = resizeArray( _MinPAC, _RepeatCount );
      _MinSWP = resizeArray( _MinSWP, _RepeatCount );
      _MinFndClsBal = resizeArray( _MinFndClsBal, _RepeatCount );
      _MinAcctBal = resizeArray( _MinAcctBal, _RepeatCount );
      _StopPurchase = resizeArray( _StopPurchase, _RepeatCount );
      _StopRed = resizeArray( _StopRed, _RepeatCount );
      _StopXferIn = resizeArray( _StopXferIn, _RepeatCount );
      _StopXferOut = resizeArray( _StopXferOut, _RepeatCount );
      _OverrideDSCAllow = resizeArray( _OverrideDSCAllow, _RepeatCount );
      _FixedPrice = resizeArray( _FixedPrice, _RepeatCount );
      _FixedRate = resizeArray( _FixedRate, _RepeatCount );
      _Currency = resizeArray( _Currency, _RepeatCount );
      _CurrencyName = resizeArray( _CurrencyName, _RepeatCount );
      _LastValDate = resizeArray( _LastValDate, _RepeatCount );
      _LastDivDate = resizeArray( _LastDivDate, _RepeatCount );
      _EffectiveDate = resizeArray( _EffectiveDate, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _CusipNum = resizeArray( _CusipNum, _RepeatCount );
      _Baycom = resizeArray( _Baycom, _RepeatCount );
      _RSPflag = resizeArray( _RSPflag, _RepeatCount );
      _RIFflag = resizeArray( _RIFflag, _RepeatCount );
      _StopDate = resizeArray( _StopDate, _RepeatCount );
      _LoadType = resizeArray( _LoadType, _RepeatCount );
      _Domestic = resizeArray( _Domestic, _RepeatCount );
      _WireElig = resizeArray( _WireElig, _RepeatCount );
      _NextSettleDate = resizeArray( _NextSettleDate, _RepeatCount );
      _NextValDate = resizeArray( _NextValDate, _RepeatCount );
      _AMSFund = resizeArray( _AMSFund, _RepeatCount );
      _UnitsPrecision = resizeArray( _UnitsPrecision, _RepeatCount );
      _FeeCurrency = resizeArray( _FeeCurrency, _RepeatCount );
      _InventoryTrac = resizeArray( _InventoryTrac, _RepeatCount );
      _SplitComm = resizeArray( _SplitComm, _RepeatCount );
      _OverrideDSC = resizeArray( _OverrideDSC, _RepeatCount );
      _ISINNumber = resizeArray( _ISINNumber, _RepeatCount );
      _SplitCommPur = resizeArray( _SplitCommPur, _RepeatCount );
      _SplitCommPAC = resizeArray( _SplitCommPAC, _RepeatCount );
      _SplitCommRed = resizeArray( _SplitCommRed, _RepeatCount );
      _SplitCommSWP = resizeArray( _SplitCommSWP, _RepeatCount );
      _SplitCommTxIn = resizeArray( _SplitCommTxIn, _RepeatCount );
      _SplitCommExIn = resizeArray( _SplitCommExIn, _RepeatCount );
      _ExchInFeeExist = resizeArray( _ExchInFeeExist, _RepeatCount );
      _ASPensionEligibleQ4 = resizeArray( _ASPensionEligibleQ4, _RepeatCount );
      _ASPensionEligibleOth = resizeArray( _ASPensionEligibleOth, _RepeatCount );
      _ESoPFlag = resizeArray( _ESoPFlag, _RepeatCount );
      _LastNightRun = resizeArray( _LastNightRun, _RepeatCount );
      _NextNightRun = resizeArray( _NextNightRun, _RepeatCount );
      _ContractType = resizeArray( _ContractType, _RepeatCount );
      _MgtFeeElig = resizeArray( _MgtFeeElig, _RepeatCount );
      _MgtFeeRbtElig = resizeArray( _MgtFeeRbtElig, _RepeatCount );
      _CompanyCode = resizeArray( _CompanyCode, _RepeatCount );
      _LastMFeeDate = resizeArray( _LastMFeeDate, _RepeatCount );
      _LastMFRDate = resizeArray( _LastMFRDate, _RepeatCount );
      _StopPAC = resizeArray( _StopPAC, _RepeatCount );
      _StopSWP = resizeArray( _StopSWP, _RepeatCount );
      _StopSysGenTrnfrIn = resizeArray( _StopSysGenTrnfrIn, _RepeatCount );
      _StopSysGenTrfrOut = resizeArray( _StopSysGenTrfrOut, _RepeatCount );
      _StopPACEWI = resizeArray( _StopPACEWI, _RepeatCount );
      _StopSWPEWI = resizeArray( _StopSWPEWI, _RepeatCount );
      _StopSysGenTrnfrInEWI = resizeArray( _StopSysGenTrnfrInEWI, _RepeatCount );
      _StopSysGenTrfrOutEWI = resizeArray( _StopSysGenTrfrOutEWI, _RepeatCount );
      _FCTransferElig = resizeArray( _FCTransferElig, _RepeatCount );
      _MarginEligible = resizeArray( _MarginEligible, _RepeatCount );
      _IndexCode = resizeArray( _IndexCode, _RepeatCount );
      _DCAFFund = resizeArray( _DCAFFund, _RepeatCount );
      _WrapFund = resizeArray( _WrapFund, _RepeatCount );
      _ProcessDiv = resizeArray( _ProcessDiv, _RepeatCount );
      _LastIntAccDate = resizeArray( _LastIntAccDate, _RepeatCount );
      _NSCCCompliant = resizeArray( _NSCCCompliant, _RepeatCount );
      _AMSEligible = resizeArray( _AMSEligible, _RepeatCount );
      _CommRebStop = resizeArray( _CommRebStop, _RepeatCount );
      _FundWKN = resizeArray( _FundWKN, _RepeatCount );
      _FundISIN = resizeArray( _FundISIN, _RepeatCount );
      _ValidSettleCurr = resizeArray( _ValidSettleCurr, _RepeatCount );
      _UnitsCalc = resizeArray( _UnitsCalc, _RepeatCount );
      _FirstScopeDate = resizeArray( _FirstScopeDate, _RepeatCount );
      _FirstLookthruDate = resizeArray( _FirstLookthruDate, _RepeatCount );
      _SchedTransType = resizeArray( _SchedTransType, _RepeatCount );
      _DftOrdType = resizeArray( _DftOrdType, _RepeatCount );
      _FundLoadGrp = resizeArray( _FundLoadGrp, _RepeatCount );
      _FOFFund = resizeArray( _FOFFund, _RepeatCount );
      _FundStat = resizeArray( _FundStat, _RepeatCount );
      _FundStatDate = resizeArray( _FundStatDate, _RepeatCount );
      _UnitRoundMethod = resizeArray( _UnitRoundMethod, _RepeatCount );
      _FundSubCat = resizeArray( _FundSubCat, _RepeatCount );
      _ERISAProhibited = resizeArray( _ERISAProhibited, _RepeatCount );
      _CombinedLoadType = resizeArray( _CombinedLoadType, _RepeatCount );
      _AMSModelType = resizeArray( _AMSModelType, _RepeatCount );
      _G1G2TrackType = resizeArray( _G1G2TrackType, _RepeatCount );
      _FundIdValue = resizeArray( _FundIdValue, _RepeatCount );
      _RolloverApplicable = resizeArray( _RolloverApplicable, _RepeatCount );
      _RolloverToFundClass = resizeArray( _RolloverToFundClass, _RepeatCount );
      _RolloverAmtType = resizeArray( _RolloverAmtType, _RepeatCount );
      _GAVApply = resizeArray( _GAVApply, _RepeatCount );
      _RoundFlag = resizeArray( _RoundFlag, _RepeatCount );
      _RecDtExists = resizeArray( _RecDtExists, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _FundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClassE[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClassF[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AdditionalDays[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _MinInitPurAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MinSubPurAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MinInitRedAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MinSubRedAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MinPAC[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MinSWP[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MinFndClsBal[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MinAcctBal[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _StopPurchase[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _StopRed[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _StopXferIn[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _StopXferOut[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _OverrideDSCAllow[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FixedPrice[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FixedRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Currency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CurrencyName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LastValDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _LastDivDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _CusipNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Baycom[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RSPflag[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _RIFflag[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _StopDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _LoadType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Domestic[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _WireElig[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _NextSettleDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _NextValDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _AMSFund[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _UnitsPrecision[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _FeeCurrency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _InventoryTrac[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _SplitComm[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _OverrideDSC[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ISINNumber[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SplitCommPur[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _SplitCommPAC[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _SplitCommRed[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _SplitCommSWP[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _SplitCommTxIn[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _SplitCommExIn[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ExchInFeeExist[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ASPensionEligibleQ4[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ASPensionEligibleOth[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ESoPFlag[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _LastNightRun[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _NextNightRun[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ContractType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MgtFeeElig[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _MgtFeeRbtElig[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _CompanyCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LastMFeeDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _LastMFRDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _StopPAC[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _StopSWP[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _StopSysGenTrnfrIn[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _StopSysGenTrfrOut[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _StopPACEWI[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _StopSWPEWI[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _StopSysGenTrnfrInEWI[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _StopSysGenTrfrOutEWI[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FCTransferElig[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _MarginEligible[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _IndexCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DCAFFund[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _WrapFund[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ProcessDiv[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LastIntAccDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _NSCCCompliant[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _AMSEligible[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _CommRebStop[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FundWKN[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundISIN[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ValidSettleCurr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UnitsCalc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FirstScopeDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _FirstLookthruDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _SchedTransType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DftOrdType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundLoadGrp[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FOFFund[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FundStat[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundStatDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _UnitRoundMethod[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundSubCat[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ERISAProhibited[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _CombinedLoadType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AMSModelType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _G1G2TrackType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundIdValue[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RolloverApplicable[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RolloverToFundClass[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RolloverAmtType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GAVApply[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RoundFlag[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RecDtExists[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      }
      

   }

}
      
