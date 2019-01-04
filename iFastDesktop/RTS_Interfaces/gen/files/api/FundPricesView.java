
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Fund prices view.
 * For additional view information see <A HREF="../../../../viewspecs/FundPrices.doc">FundPrices.doc</A>.
 * 
 * @author RTS Generated
 */
public class FundPricesView extends IFastView implements Serializable
{

   /**
    * FundCodeList member variable.
    */
   private String _FundCodeList = null;
   
   private int _RepeatCount = 0;
   
   /**
    * ValueAsAt member array.
    */
   private Date[] _ValueAsAt = null;
   
   /**
    * rx Fund Code member array.
    */
   private String[] _rxFundCode = null;
   
   /**
    * ClassCode member array.
    */
   private String[] _rxClassCode = null;
   
   /**
    * Transaction Type member array.
    */
   private String[] _TransType = null;
   
   /**
    * Record Date member array.
    */
   private Date[] _RecordDate = null;
   
   /**
    * Date of Creation member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * Time Entered member array.
    */
   private String[] _ProcessTime = null;
   
   /**
    * Modification Date member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * Created by UserID member array.
    */
   private String[] _Username = null;
   
   /**
    * Modified by UserID member array.
    */
   private String[] _ModUser = null;
   
   /**
    * Currency member array.
    */
   private String[] _Currency = null;
   
   /**
    * UnitValue member array.
    */
   private String[] _UnitValue = null;
   
   /**
    * Unallocated Income member array.
    */
   private String[] _UnAllocIncome = null;
   
   /**
    * Notional member array.
    */
   private Boolean[] _Notional = null;
   
   /**
    * Skeleton Business Year member array.
    */
   private Boolean[] _SkeletonBusYr = null;
   
   /**
    * Record Active member array.
    */
   private Boolean[] _GoodBad = null;
   
   /**
    * Canadian Dividend member array.
    */
   private String[] _CanDividend = null;
   
   /**
    * Ineligible Dividend member array.
    */
   private String[] _InelgDividend = null;
   
   /**
    * Canadian Interest member array.
    */
   private String[] _CanInterest = null;
   
   /**
    * Foreign Interest member array.
    */
   private String[] _ForeignInterest = null;
   
   /**
    * Foreign Dividend member array.
    */
   private String[] _ForeignDividend = null;
   
   /**
    * Accrual Income member array.
    */
   private String[] _AccrualIncome = null;
   
   /**
    * Management Fee member array.
    */
   private String[] _MgmtFee = null;
   
   /**
    * Taxable Capital Gain member array.
    */
   private String[] _TaxCapGain = null;
   
   /**
    * Foreign Withhold Tax member array.
    */
   private String[] _ForeignTax = null;
   
   /**
    * Other Income member array.
    */
   private String[] _OthIncome = null;
   
   /**
    * Realize Gain member array.
    */
   private String[] _RealizeGain = null;
   
   /**
    * Trustee Fee member array.
    */
   private String[] _TrusteeFee = null;
   
   /**
    * Equalization Amount member array.
    */
   private String[] _EqualizationAmt = null;
   
   /**
    * Paid Out Amount member array.
    */
   private String[] _PaidAmt = null;
   
   /**
    * Price Type 2 member array.
    */
   private String[] _PriceCode2 = null;
   
   /**
    * Price Type 2 Description member array.
    */
   private String[] _PriceDesc2 = null;
   
   /**
    * Unit Value 2 member array.
    */
   private String[] _UnitValue2 = null;
   
   /**
    * Change Factor 2 member array.
    */
   private String[] _ChgFactor2 = null;
   
   /**
    * Price Type 3 member array.
    */
   private String[] _PriceCode3 = null;
   
   /**
    * Price Type 3 Description member array.
    */
   private String[] _PriceDesc3 = null;
   
   /**
    * Unit Value 3 member array.
    */
   private String[] _UnitValue3 = null;
   
   /**
    * Change Factor 3 member array.
    */
   private String[] _ChgFactor3 = null;
   
   /**
    * Price Type 4 member array.
    */
   private String[] _PriceCode4 = null;
   
   /**
    * Price Type 4 Description member array.
    */
   private String[] _PriceDesc4 = null;
   
   /**
    * Unit Value 4 member array.
    */
   private String[] _UnitValue4 = null;
   
   /**
    * Change Factor 4 member array.
    */
   private String[] _ChgFactor4 = null;
   
   /**
    * Price Type 5 member array.
    */
   private String[] _PriceCode5 = null;
   
   /**
    * Price Type 5 Description member array.
    */
   private String[] _PriceDesc5 = null;
   
   /**
    * Unit Value 5 member array.
    */
   private String[] _UnitValue5 = null;
   
   /**
    * Change Factor 5 member array.
    */
   private String[] _ChgFactor5 = null;
   
   /**
    * Change Factor member array.
    */
   private String[] _ChgFactor = null;
   
   /**
    * Fund Load Group member array.
    */
   private String[] _FundLoadGrp = null;
   
   /**
    * Return Of Capital member array.
    */
   private String[] _ROC = null;
   
   /**
    * WKN in response member array.
    */
   private String[] _rxWKN = null;
   
   /**
    * ISIN in response member array.
    */
   private String[] _rxISIN = null;
   
   /**
    * Factor Amount 1 member array.
    */
   private String[] _FactorAmt1 = null;
   
   /**
    * Factor Amount 2 member array.
    */
   private String[] _FactorAmt2 = null;
   
   /**
    * Factor Amount 3 member array.
    */
   private String[] _FactorAmt3 = null;
   
   /**
    * Factor Amount 4 member array.
    */
   private String[] _FactorAmt4 = null;
   
   /**
    * Factor Amount 5 member array.
    */
   private String[] _FactorAmt5 = null;
   
   /**
    * Unit ID member array.
    */
   private Integer[] _UnitID = null;
   
   /**
    * Ex Date member array.
    */
   private Date[] _ExDate = null;
   
   /**
    * Payment Date member array.
    */
   private Date[] _PayDate = null;
   
   /**
    * Reinvest Date member array.
    */
   private Date[] _ReInvDate = null;
   
   /**
    * Distribution Type member array.
    */
   private String[] _DistribType = null;
   
   /**
    * Declaration member array.
    */
   private String[] _Declaration = null;
   
   /**
    * Rate Period member array.
    */
   private String[] _RatePeriod = null;
   
   /**
    * GAV Rate member array.
    */
   private String[] _GAV = null;
   
   /**
    * Latest Gross Unit Value for Transtype ID member array.
    */
   private String[] _LastIDRate = null;
   
   /**
    * Usage ID Rate for Multiple Pricing member array.
    */
   private String[] _MultiPriceUsageID = null;
   

   /**
    * Constructs the FundPricesView object.
    * 
    */
   public FundPricesView()
   {
      super ( new FundPricesRequest() );
   }

   /**
    * Constructs the FundPricesView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public FundPricesView( String hostEncoding )
   {
      super ( new FundPricesRequest( hostEncoding ) );
   }

   /**
    * Gets the FundPricesRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The FundPricesRequest object.
    */
   public final FundPricesRequest getRequest()
   {
      return (FundPricesRequest)getIFastRequest();
   }
        
   /**
    * Gets the FundCodeList field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the FundCodeList or null.
    */
   public final String getFundCodeList()
   {
      return _FundCodeList;
   }
	
   /**
    * Gets the FundCodeList field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FundCodeList or the specified default value.
    */
   public final String getFundCodeList( String defaultValue )
   {
      return _FundCodeList == null ? defaultValue : _FundCodeList;
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
    * Gets the ValueAsAt field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ValueAsAt or null.
    */
   public final Date getValueAsAt( int index )
   {
      return _ValueAsAt[index];
   }
    
   /**
    * Gets the ValueAsAt field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ValueAsAt or the specified default value.
    */
   public final Date getValueAsAt( int index, Date defaultValue )
   {
      return _ValueAsAt[index] == null ? defaultValue : _ValueAsAt[index];
   }
    
   /**
    * Gets the array of ValueAsAt fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ValueAsAt values.
    */
   public final Date[] getValueAsAtArray()
   {
      return _ValueAsAt;
   }
    
   /**
    * Gets the rx Fund Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the rx Fund Code or null.
    */
   public final String getrxFundCode( int index )
   {
      return _rxFundCode[index];
   }
    
   /**
    * Gets the rx Fund Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the rx Fund Code or the specified default value.
    */
   public final String getrxFundCode( int index, String defaultValue )
   {
      return _rxFundCode[index] == null ? defaultValue : _rxFundCode[index];
   }
    
   /**
    * Gets the array of rx Fund Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of rx Fund Code values.
    */
   public final String[] getrxFundCodeArray()
   {
      return _rxFundCode;
   }
    
   /**
    * Gets the ClassCode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ClassCode or null.
    */
   public final String getrxClassCode( int index )
   {
      return _rxClassCode[index];
   }
    
   /**
    * Gets the ClassCode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ClassCode or the specified default value.
    */
   public final String getrxClassCode( int index, String defaultValue )
   {
      return _rxClassCode[index] == null ? defaultValue : _rxClassCode[index];
   }
    
   /**
    * Gets the array of ClassCode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ClassCode values.
    */
   public final String[] getrxClassCodeArray()
   {
      return _rxClassCode;
   }
    
   /**
    * Gets the Transaction Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transaction Type or null.
    */
   public final String getTransType( int index )
   {
      return _TransType[index];
   }
    
   /**
    * Gets the Transaction Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transaction Type or the specified default value.
    */
   public final String getTransType( int index, String defaultValue )
   {
      return _TransType[index] == null ? defaultValue : _TransType[index];
   }
    
   /**
    * Gets the array of Transaction Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transaction Type values.
    */
   public final String[] getTransTypeArray()
   {
      return _TransType;
   }
    
   /**
    * Gets the Record Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Record Date or null.
    */
   public final Date getRecordDate( int index )
   {
      return _RecordDate[index];
   }
    
   /**
    * Gets the Record Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Record Date or the specified default value.
    */
   public final Date getRecordDate( int index, Date defaultValue )
   {
      return _RecordDate[index] == null ? defaultValue : _RecordDate[index];
   }
    
   /**
    * Gets the array of Record Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Record Date values.
    */
   public final Date[] getRecordDateArray()
   {
      return _RecordDate;
   }
    
   /**
    * Gets the Date of Creation field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Date of Creation or null.
    */
   public final Date getProcessDate( int index )
   {
      return _ProcessDate[index];
   }
    
   /**
    * Gets the Date of Creation field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date of Creation or the specified default value.
    */
   public final Date getProcessDate( int index, Date defaultValue )
   {
      return _ProcessDate[index] == null ? defaultValue : _ProcessDate[index];
   }
    
   /**
    * Gets the array of Date of Creation fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Date of Creation values.
    */
   public final Date[] getProcessDateArray()
   {
      return _ProcessDate;
   }
    
   /**
    * Gets the Time Entered field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Time Entered or null.
    */
   public final String getProcessTime( int index )
   {
      return _ProcessTime[index];
   }
    
   /**
    * Gets the Time Entered field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Time Entered or the specified default value.
    */
   public final String getProcessTime( int index, String defaultValue )
   {
      return _ProcessTime[index] == null ? defaultValue : _ProcessTime[index];
   }
    
   /**
    * Gets the array of Time Entered fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Time Entered values.
    */
   public final String[] getProcessTimeArray()
   {
      return _ProcessTime;
   }
    
   /**
    * Gets the Modification Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Modification Date or null.
    */
   public final Date getModDate( int index )
   {
      return _ModDate[index];
   }
    
   /**
    * Gets the Modification Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Modification Date or the specified default value.
    */
   public final Date getModDate( int index, Date defaultValue )
   {
      return _ModDate[index] == null ? defaultValue : _ModDate[index];
   }
    
   /**
    * Gets the array of Modification Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Modification Date values.
    */
   public final Date[] getModDateArray()
   {
      return _ModDate;
   }
    
   /**
    * Gets the Created by UserID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Created by UserID or null.
    */
   public final String getUsername( int index )
   {
      return _Username[index];
   }
    
   /**
    * Gets the Created by UserID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Created by UserID or the specified default value.
    */
   public final String getUsername( int index, String defaultValue )
   {
      return _Username[index] == null ? defaultValue : _Username[index];
   }
    
   /**
    * Gets the array of Created by UserID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Created by UserID values.
    */
   public final String[] getUsernameArray()
   {
      return _Username;
   }
    
   /**
    * Gets the Modified by UserID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Modified by UserID or null.
    */
   public final String getModUser( int index )
   {
      return _ModUser[index];
   }
    
   /**
    * Gets the Modified by UserID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Modified by UserID or the specified default value.
    */
   public final String getModUser( int index, String defaultValue )
   {
      return _ModUser[index] == null ? defaultValue : _ModUser[index];
   }
    
   /**
    * Gets the array of Modified by UserID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Modified by UserID values.
    */
   public final String[] getModUserArray()
   {
      return _ModUser;
   }
    
   /**
    * Gets the Currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Currency or null.
    */
   public final String getCurrency( int index )
   {
      return _Currency[index];
   }
    
   /**
    * Gets the Currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Currency or the specified default value.
    */
   public final String getCurrency( int index, String defaultValue )
   {
      return _Currency[index] == null ? defaultValue : _Currency[index];
   }
    
   /**
    * Gets the array of Currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Currency values.
    */
   public final String[] getCurrencyArray()
   {
      return _Currency;
   }
    
   /**
    * Gets the UnitValue field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the UnitValue or null.
    */
   public final String getUnitValue( int index )
   {
      return _UnitValue[index];
   }
    
   /**
    * Gets the UnitValue field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the UnitValue or the specified default value.
    */
   public final String getUnitValue( int index, String defaultValue )
   {
      return _UnitValue[index] == null ? defaultValue : _UnitValue[index];
   }
    
   /**
    * Gets the array of UnitValue fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of UnitValue values.
    */
   public final String[] getUnitValueArray()
   {
      return _UnitValue;
   }
    
   /**
    * Gets the Unallocated Income field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Unallocated Income or null.
    */
   public final String getUnAllocIncome( int index )
   {
      return _UnAllocIncome[index];
   }
    
   /**
    * Gets the Unallocated Income field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Unallocated Income or the specified default value.
    */
   public final String getUnAllocIncome( int index, String defaultValue )
   {
      return _UnAllocIncome[index] == null ? defaultValue : _UnAllocIncome[index];
   }
    
   /**
    * Gets the array of Unallocated Income fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Unallocated Income values.
    */
   public final String[] getUnAllocIncomeArray()
   {
      return _UnAllocIncome;
   }
    
   /**
    * Gets the Notional field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Notional or null.
    */
   public final Boolean getNotional( int index )
   {
      return _Notional[index];
   }
    
   /**
    * Gets the Notional field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Notional or the specified default value.
    */
   public final boolean getNotional( int index, boolean defaultValue )
   {
      return _Notional[index] == null ? defaultValue : _Notional[index].booleanValue();
   }
    
   /**
    * Gets the array of Notional fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Notional values.
    */
   public final Boolean[] getNotionalArray()
   {
      return _Notional;
   }
    
   /**
    * Gets the Skeleton Business Year field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Skeleton Business Year or null.
    */
   public final Boolean getSkeletonBusYr( int index )
   {
      return _SkeletonBusYr[index];
   }
    
   /**
    * Gets the Skeleton Business Year field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Skeleton Business Year or the specified default value.
    */
   public final boolean getSkeletonBusYr( int index, boolean defaultValue )
   {
      return _SkeletonBusYr[index] == null ? defaultValue : _SkeletonBusYr[index].booleanValue();
   }
    
   /**
    * Gets the array of Skeleton Business Year fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Skeleton Business Year values.
    */
   public final Boolean[] getSkeletonBusYrArray()
   {
      return _SkeletonBusYr;
   }
    
   /**
    * Gets the Record Active field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Record Active or null.
    */
   public final Boolean getGoodBad( int index )
   {
      return _GoodBad[index];
   }
    
   /**
    * Gets the Record Active field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Record Active or the specified default value.
    */
   public final boolean getGoodBad( int index, boolean defaultValue )
   {
      return _GoodBad[index] == null ? defaultValue : _GoodBad[index].booleanValue();
   }
    
   /**
    * Gets the array of Record Active fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Record Active values.
    */
   public final Boolean[] getGoodBadArray()
   {
      return _GoodBad;
   }
    
   /**
    * Gets the Canadian Dividend field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Canadian Dividend or null.
    */
   public final String getCanDividend( int index )
   {
      return _CanDividend[index];
   }
    
   /**
    * Gets the Canadian Dividend field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Canadian Dividend or the specified default value.
    */
   public final String getCanDividend( int index, String defaultValue )
   {
      return _CanDividend[index] == null ? defaultValue : _CanDividend[index];
   }
    
   /**
    * Gets the array of Canadian Dividend fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Canadian Dividend values.
    */
   public final String[] getCanDividendArray()
   {
      return _CanDividend;
   }
    
   /**
    * Gets the Ineligible Dividend field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Ineligible Dividend or null.
    */
   public final String getInelgDividend( int index )
   {
      return _InelgDividend[index];
   }
    
   /**
    * Gets the Ineligible Dividend field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Ineligible Dividend or the specified default value.
    */
   public final String getInelgDividend( int index, String defaultValue )
   {
      return _InelgDividend[index] == null ? defaultValue : _InelgDividend[index];
   }
    
   /**
    * Gets the array of Ineligible Dividend fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Ineligible Dividend values.
    */
   public final String[] getInelgDividendArray()
   {
      return _InelgDividend;
   }
    
   /**
    * Gets the Canadian Interest field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Canadian Interest or null.
    */
   public final String getCanInterest( int index )
   {
      return _CanInterest[index];
   }
    
   /**
    * Gets the Canadian Interest field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Canadian Interest or the specified default value.
    */
   public final String getCanInterest( int index, String defaultValue )
   {
      return _CanInterest[index] == null ? defaultValue : _CanInterest[index];
   }
    
   /**
    * Gets the array of Canadian Interest fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Canadian Interest values.
    */
   public final String[] getCanInterestArray()
   {
      return _CanInterest;
   }
    
   /**
    * Gets the Foreign Interest field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Foreign Interest or null.
    */
   public final String getForeignInterest( int index )
   {
      return _ForeignInterest[index];
   }
    
   /**
    * Gets the Foreign Interest field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Foreign Interest or the specified default value.
    */
   public final String getForeignInterest( int index, String defaultValue )
   {
      return _ForeignInterest[index] == null ? defaultValue : _ForeignInterest[index];
   }
    
   /**
    * Gets the array of Foreign Interest fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Foreign Interest values.
    */
   public final String[] getForeignInterestArray()
   {
      return _ForeignInterest;
   }
    
   /**
    * Gets the Foreign Dividend field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Foreign Dividend or null.
    */
   public final String getForeignDividend( int index )
   {
      return _ForeignDividend[index];
   }
    
   /**
    * Gets the Foreign Dividend field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Foreign Dividend or the specified default value.
    */
   public final String getForeignDividend( int index, String defaultValue )
   {
      return _ForeignDividend[index] == null ? defaultValue : _ForeignDividend[index];
   }
    
   /**
    * Gets the array of Foreign Dividend fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Foreign Dividend values.
    */
   public final String[] getForeignDividendArray()
   {
      return _ForeignDividend;
   }
    
   /**
    * Gets the Accrual Income field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Accrual Income or null.
    */
   public final String getAccrualIncome( int index )
   {
      return _AccrualIncome[index];
   }
    
   /**
    * Gets the Accrual Income field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Accrual Income or the specified default value.
    */
   public final String getAccrualIncome( int index, String defaultValue )
   {
      return _AccrualIncome[index] == null ? defaultValue : _AccrualIncome[index];
   }
    
   /**
    * Gets the array of Accrual Income fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Accrual Income values.
    */
   public final String[] getAccrualIncomeArray()
   {
      return _AccrualIncome;
   }
    
   /**
    * Gets the Management Fee field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Management Fee or null.
    */
   public final String getMgmtFee( int index )
   {
      return _MgmtFee[index];
   }
    
   /**
    * Gets the Management Fee field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Management Fee or the specified default value.
    */
   public final String getMgmtFee( int index, String defaultValue )
   {
      return _MgmtFee[index] == null ? defaultValue : _MgmtFee[index];
   }
    
   /**
    * Gets the array of Management Fee fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Management Fee values.
    */
   public final String[] getMgmtFeeArray()
   {
      return _MgmtFee;
   }
    
   /**
    * Gets the Taxable Capital Gain field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Taxable Capital Gain or null.
    */
   public final String getTaxCapGain( int index )
   {
      return _TaxCapGain[index];
   }
    
   /**
    * Gets the Taxable Capital Gain field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Taxable Capital Gain or the specified default value.
    */
   public final String getTaxCapGain( int index, String defaultValue )
   {
      return _TaxCapGain[index] == null ? defaultValue : _TaxCapGain[index];
   }
    
   /**
    * Gets the array of Taxable Capital Gain fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Taxable Capital Gain values.
    */
   public final String[] getTaxCapGainArray()
   {
      return _TaxCapGain;
   }
    
   /**
    * Gets the Foreign Withhold Tax field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Foreign Withhold Tax or null.
    */
   public final String getForeignTax( int index )
   {
      return _ForeignTax[index];
   }
    
   /**
    * Gets the Foreign Withhold Tax field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Foreign Withhold Tax or the specified default value.
    */
   public final String getForeignTax( int index, String defaultValue )
   {
      return _ForeignTax[index] == null ? defaultValue : _ForeignTax[index];
   }
    
   /**
    * Gets the array of Foreign Withhold Tax fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Foreign Withhold Tax values.
    */
   public final String[] getForeignTaxArray()
   {
      return _ForeignTax;
   }
    
   /**
    * Gets the Other Income field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Other Income or null.
    */
   public final String getOthIncome( int index )
   {
      return _OthIncome[index];
   }
    
   /**
    * Gets the Other Income field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Other Income or the specified default value.
    */
   public final String getOthIncome( int index, String defaultValue )
   {
      return _OthIncome[index] == null ? defaultValue : _OthIncome[index];
   }
    
   /**
    * Gets the array of Other Income fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Other Income values.
    */
   public final String[] getOthIncomeArray()
   {
      return _OthIncome;
   }
    
   /**
    * Gets the Realize Gain field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Realize Gain or null.
    */
   public final String getRealizeGain( int index )
   {
      return _RealizeGain[index];
   }
    
   /**
    * Gets the Realize Gain field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Realize Gain or the specified default value.
    */
   public final String getRealizeGain( int index, String defaultValue )
   {
      return _RealizeGain[index] == null ? defaultValue : _RealizeGain[index];
   }
    
   /**
    * Gets the array of Realize Gain fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Realize Gain values.
    */
   public final String[] getRealizeGainArray()
   {
      return _RealizeGain;
   }
    
   /**
    * Gets the Trustee Fee field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Trustee Fee or null.
    */
   public final String getTrusteeFee( int index )
   {
      return _TrusteeFee[index];
   }
    
   /**
    * Gets the Trustee Fee field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Trustee Fee or the specified default value.
    */
   public final String getTrusteeFee( int index, String defaultValue )
   {
      return _TrusteeFee[index] == null ? defaultValue : _TrusteeFee[index];
   }
    
   /**
    * Gets the array of Trustee Fee fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Trustee Fee values.
    */
   public final String[] getTrusteeFeeArray()
   {
      return _TrusteeFee;
   }
    
   /**
    * Gets the Equalization Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Equalization Amount or null.
    */
   public final String getEqualizationAmt( int index )
   {
      return _EqualizationAmt[index];
   }
    
   /**
    * Gets the Equalization Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Equalization Amount or the specified default value.
    */
   public final String getEqualizationAmt( int index, String defaultValue )
   {
      return _EqualizationAmt[index] == null ? defaultValue : _EqualizationAmt[index];
   }
    
   /**
    * Gets the array of Equalization Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Equalization Amount values.
    */
   public final String[] getEqualizationAmtArray()
   {
      return _EqualizationAmt;
   }
    
   /**
    * Gets the Paid Out Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Paid Out Amount or null.
    */
   public final String getPaidAmt( int index )
   {
      return _PaidAmt[index];
   }
    
   /**
    * Gets the Paid Out Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Paid Out Amount or the specified default value.
    */
   public final String getPaidAmt( int index, String defaultValue )
   {
      return _PaidAmt[index] == null ? defaultValue : _PaidAmt[index];
   }
    
   /**
    * Gets the array of Paid Out Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Paid Out Amount values.
    */
   public final String[] getPaidAmtArray()
   {
      return _PaidAmt;
   }
    
   /**
    * Gets the Price Type 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Price Type 2 or null.
    */
   public final String getPriceCode2( int index )
   {
      return _PriceCode2[index];
   }
    
   /**
    * Gets the Price Type 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Price Type 2 or the specified default value.
    */
   public final String getPriceCode2( int index, String defaultValue )
   {
      return _PriceCode2[index] == null ? defaultValue : _PriceCode2[index];
   }
    
   /**
    * Gets the array of Price Type 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Price Type 2 values.
    */
   public final String[] getPriceCode2Array()
   {
      return _PriceCode2;
   }
    
   /**
    * Gets the Price Type 2 Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Price Type 2 Description or null.
    */
   public final String getPriceDesc2( int index )
   {
      return _PriceDesc2[index];
   }
    
   /**
    * Gets the Price Type 2 Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Price Type 2 Description or the specified default value.
    */
   public final String getPriceDesc2( int index, String defaultValue )
   {
      return _PriceDesc2[index] == null ? defaultValue : _PriceDesc2[index];
   }
    
   /**
    * Gets the array of Price Type 2 Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Price Type 2 Description values.
    */
   public final String[] getPriceDesc2Array()
   {
      return _PriceDesc2;
   }
    
   /**
    * Gets the Unit Value 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Unit Value 2 or null.
    */
   public final String getUnitValue2( int index )
   {
      return _UnitValue2[index];
   }
    
   /**
    * Gets the Unit Value 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Unit Value 2 or the specified default value.
    */
   public final String getUnitValue2( int index, String defaultValue )
   {
      return _UnitValue2[index] == null ? defaultValue : _UnitValue2[index];
   }
    
   /**
    * Gets the array of Unit Value 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Unit Value 2 values.
    */
   public final String[] getUnitValue2Array()
   {
      return _UnitValue2;
   }
    
   /**
    * Gets the Change Factor 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Change Factor 2 or null.
    */
   public final String getChgFactor2( int index )
   {
      return _ChgFactor2[index];
   }
    
   /**
    * Gets the Change Factor 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Change Factor 2 or the specified default value.
    */
   public final String getChgFactor2( int index, String defaultValue )
   {
      return _ChgFactor2[index] == null ? defaultValue : _ChgFactor2[index];
   }
    
   /**
    * Gets the array of Change Factor 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Change Factor 2 values.
    */
   public final String[] getChgFactor2Array()
   {
      return _ChgFactor2;
   }
    
   /**
    * Gets the Price Type 3 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Price Type 3 or null.
    */
   public final String getPriceCode3( int index )
   {
      return _PriceCode3[index];
   }
    
   /**
    * Gets the Price Type 3 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Price Type 3 or the specified default value.
    */
   public final String getPriceCode3( int index, String defaultValue )
   {
      return _PriceCode3[index] == null ? defaultValue : _PriceCode3[index];
   }
    
   /**
    * Gets the array of Price Type 3 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Price Type 3 values.
    */
   public final String[] getPriceCode3Array()
   {
      return _PriceCode3;
   }
    
   /**
    * Gets the Price Type 3 Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Price Type 3 Description or null.
    */
   public final String getPriceDesc3( int index )
   {
      return _PriceDesc3[index];
   }
    
   /**
    * Gets the Price Type 3 Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Price Type 3 Description or the specified default value.
    */
   public final String getPriceDesc3( int index, String defaultValue )
   {
      return _PriceDesc3[index] == null ? defaultValue : _PriceDesc3[index];
   }
    
   /**
    * Gets the array of Price Type 3 Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Price Type 3 Description values.
    */
   public final String[] getPriceDesc3Array()
   {
      return _PriceDesc3;
   }
    
   /**
    * Gets the Unit Value 3 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Unit Value 3 or null.
    */
   public final String getUnitValue3( int index )
   {
      return _UnitValue3[index];
   }
    
   /**
    * Gets the Unit Value 3 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Unit Value 3 or the specified default value.
    */
   public final String getUnitValue3( int index, String defaultValue )
   {
      return _UnitValue3[index] == null ? defaultValue : _UnitValue3[index];
   }
    
   /**
    * Gets the array of Unit Value 3 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Unit Value 3 values.
    */
   public final String[] getUnitValue3Array()
   {
      return _UnitValue3;
   }
    
   /**
    * Gets the Change Factor 3 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Change Factor 3 or null.
    */
   public final String getChgFactor3( int index )
   {
      return _ChgFactor3[index];
   }
    
   /**
    * Gets the Change Factor 3 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Change Factor 3 or the specified default value.
    */
   public final String getChgFactor3( int index, String defaultValue )
   {
      return _ChgFactor3[index] == null ? defaultValue : _ChgFactor3[index];
   }
    
   /**
    * Gets the array of Change Factor 3 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Change Factor 3 values.
    */
   public final String[] getChgFactor3Array()
   {
      return _ChgFactor3;
   }
    
   /**
    * Gets the Price Type 4 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Price Type 4 or null.
    */
   public final String getPriceCode4( int index )
   {
      return _PriceCode4[index];
   }
    
   /**
    * Gets the Price Type 4 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Price Type 4 or the specified default value.
    */
   public final String getPriceCode4( int index, String defaultValue )
   {
      return _PriceCode4[index] == null ? defaultValue : _PriceCode4[index];
   }
    
   /**
    * Gets the array of Price Type 4 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Price Type 4 values.
    */
   public final String[] getPriceCode4Array()
   {
      return _PriceCode4;
   }
    
   /**
    * Gets the Price Type 4 Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Price Type 4 Description or null.
    */
   public final String getPriceDesc4( int index )
   {
      return _PriceDesc4[index];
   }
    
   /**
    * Gets the Price Type 4 Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Price Type 4 Description or the specified default value.
    */
   public final String getPriceDesc4( int index, String defaultValue )
   {
      return _PriceDesc4[index] == null ? defaultValue : _PriceDesc4[index];
   }
    
   /**
    * Gets the array of Price Type 4 Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Price Type 4 Description values.
    */
   public final String[] getPriceDesc4Array()
   {
      return _PriceDesc4;
   }
    
   /**
    * Gets the Unit Value 4 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Unit Value 4 or null.
    */
   public final String getUnitValue4( int index )
   {
      return _UnitValue4[index];
   }
    
   /**
    * Gets the Unit Value 4 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Unit Value 4 or the specified default value.
    */
   public final String getUnitValue4( int index, String defaultValue )
   {
      return _UnitValue4[index] == null ? defaultValue : _UnitValue4[index];
   }
    
   /**
    * Gets the array of Unit Value 4 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Unit Value 4 values.
    */
   public final String[] getUnitValue4Array()
   {
      return _UnitValue4;
   }
    
   /**
    * Gets the Change Factor 4 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Change Factor 4 or null.
    */
   public final String getChgFactor4( int index )
   {
      return _ChgFactor4[index];
   }
    
   /**
    * Gets the Change Factor 4 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Change Factor 4 or the specified default value.
    */
   public final String getChgFactor4( int index, String defaultValue )
   {
      return _ChgFactor4[index] == null ? defaultValue : _ChgFactor4[index];
   }
    
   /**
    * Gets the array of Change Factor 4 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Change Factor 4 values.
    */
   public final String[] getChgFactor4Array()
   {
      return _ChgFactor4;
   }
    
   /**
    * Gets the Price Type 5 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Price Type 5 or null.
    */
   public final String getPriceCode5( int index )
   {
      return _PriceCode5[index];
   }
    
   /**
    * Gets the Price Type 5 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Price Type 5 or the specified default value.
    */
   public final String getPriceCode5( int index, String defaultValue )
   {
      return _PriceCode5[index] == null ? defaultValue : _PriceCode5[index];
   }
    
   /**
    * Gets the array of Price Type 5 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Price Type 5 values.
    */
   public final String[] getPriceCode5Array()
   {
      return _PriceCode5;
   }
    
   /**
    * Gets the Price Type 5 Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Price Type 5 Description or null.
    */
   public final String getPriceDesc5( int index )
   {
      return _PriceDesc5[index];
   }
    
   /**
    * Gets the Price Type 5 Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Price Type 5 Description or the specified default value.
    */
   public final String getPriceDesc5( int index, String defaultValue )
   {
      return _PriceDesc5[index] == null ? defaultValue : _PriceDesc5[index];
   }
    
   /**
    * Gets the array of Price Type 5 Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Price Type 5 Description values.
    */
   public final String[] getPriceDesc5Array()
   {
      return _PriceDesc5;
   }
    
   /**
    * Gets the Unit Value 5 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Unit Value 5 or null.
    */
   public final String getUnitValue5( int index )
   {
      return _UnitValue5[index];
   }
    
   /**
    * Gets the Unit Value 5 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Unit Value 5 or the specified default value.
    */
   public final String getUnitValue5( int index, String defaultValue )
   {
      return _UnitValue5[index] == null ? defaultValue : _UnitValue5[index];
   }
    
   /**
    * Gets the array of Unit Value 5 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Unit Value 5 values.
    */
   public final String[] getUnitValue5Array()
   {
      return _UnitValue5;
   }
    
   /**
    * Gets the Change Factor 5 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Change Factor 5 or null.
    */
   public final String getChgFactor5( int index )
   {
      return _ChgFactor5[index];
   }
    
   /**
    * Gets the Change Factor 5 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Change Factor 5 or the specified default value.
    */
   public final String getChgFactor5( int index, String defaultValue )
   {
      return _ChgFactor5[index] == null ? defaultValue : _ChgFactor5[index];
   }
    
   /**
    * Gets the array of Change Factor 5 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Change Factor 5 values.
    */
   public final String[] getChgFactor5Array()
   {
      return _ChgFactor5;
   }
    
   /**
    * Gets the Change Factor field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Change Factor or null.
    */
   public final String getChgFactor( int index )
   {
      return _ChgFactor[index];
   }
    
   /**
    * Gets the Change Factor field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Change Factor or the specified default value.
    */
   public final String getChgFactor( int index, String defaultValue )
   {
      return _ChgFactor[index] == null ? defaultValue : _ChgFactor[index];
   }
    
   /**
    * Gets the array of Change Factor fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Change Factor values.
    */
   public final String[] getChgFactorArray()
   {
      return _ChgFactor;
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
    * Gets the Return Of Capital field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Return Of Capital or null.
    */
   public final String getROC( int index )
   {
      return _ROC[index];
   }
    
   /**
    * Gets the Return Of Capital field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Return Of Capital or the specified default value.
    */
   public final String getROC( int index, String defaultValue )
   {
      return _ROC[index] == null ? defaultValue : _ROC[index];
   }
    
   /**
    * Gets the array of Return Of Capital fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Return Of Capital values.
    */
   public final String[] getROCArray()
   {
      return _ROC;
   }
    
   /**
    * Gets the WKN in response field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the WKN in response or null.
    */
   public final String getrxWKN( int index )
   {
      return _rxWKN[index];
   }
    
   /**
    * Gets the WKN in response field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the WKN in response or the specified default value.
    */
   public final String getrxWKN( int index, String defaultValue )
   {
      return _rxWKN[index] == null ? defaultValue : _rxWKN[index];
   }
    
   /**
    * Gets the array of WKN in response fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of WKN in response values.
    */
   public final String[] getrxWKNArray()
   {
      return _rxWKN;
   }
    
   /**
    * Gets the ISIN in response field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ISIN in response or null.
    */
   public final String getrxISIN( int index )
   {
      return _rxISIN[index];
   }
    
   /**
    * Gets the ISIN in response field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ISIN in response or the specified default value.
    */
   public final String getrxISIN( int index, String defaultValue )
   {
      return _rxISIN[index] == null ? defaultValue : _rxISIN[index];
   }
    
   /**
    * Gets the array of ISIN in response fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ISIN in response values.
    */
   public final String[] getrxISINArray()
   {
      return _rxISIN;
   }
    
   /**
    * Gets the Factor Amount 1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Factor Amount 1 or null.
    */
   public final String getFactorAmt1( int index )
   {
      return _FactorAmt1[index];
   }
    
   /**
    * Gets the Factor Amount 1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Factor Amount 1 or the specified default value.
    */
   public final String getFactorAmt1( int index, String defaultValue )
   {
      return _FactorAmt1[index] == null ? defaultValue : _FactorAmt1[index];
   }
    
   /**
    * Gets the array of Factor Amount 1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Factor Amount 1 values.
    */
   public final String[] getFactorAmt1Array()
   {
      return _FactorAmt1;
   }
    
   /**
    * Gets the Factor Amount 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Factor Amount 2 or null.
    */
   public final String getFactorAmt2( int index )
   {
      return _FactorAmt2[index];
   }
    
   /**
    * Gets the Factor Amount 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Factor Amount 2 or the specified default value.
    */
   public final String getFactorAmt2( int index, String defaultValue )
   {
      return _FactorAmt2[index] == null ? defaultValue : _FactorAmt2[index];
   }
    
   /**
    * Gets the array of Factor Amount 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Factor Amount 2 values.
    */
   public final String[] getFactorAmt2Array()
   {
      return _FactorAmt2;
   }
    
   /**
    * Gets the Factor Amount 3 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Factor Amount 3 or null.
    */
   public final String getFactorAmt3( int index )
   {
      return _FactorAmt3[index];
   }
    
   /**
    * Gets the Factor Amount 3 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Factor Amount 3 or the specified default value.
    */
   public final String getFactorAmt3( int index, String defaultValue )
   {
      return _FactorAmt3[index] == null ? defaultValue : _FactorAmt3[index];
   }
    
   /**
    * Gets the array of Factor Amount 3 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Factor Amount 3 values.
    */
   public final String[] getFactorAmt3Array()
   {
      return _FactorAmt3;
   }
    
   /**
    * Gets the Factor Amount 4 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Factor Amount 4 or null.
    */
   public final String getFactorAmt4( int index )
   {
      return _FactorAmt4[index];
   }
    
   /**
    * Gets the Factor Amount 4 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Factor Amount 4 or the specified default value.
    */
   public final String getFactorAmt4( int index, String defaultValue )
   {
      return _FactorAmt4[index] == null ? defaultValue : _FactorAmt4[index];
   }
    
   /**
    * Gets the array of Factor Amount 4 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Factor Amount 4 values.
    */
   public final String[] getFactorAmt4Array()
   {
      return _FactorAmt4;
   }
    
   /**
    * Gets the Factor Amount 5 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Factor Amount 5 or null.
    */
   public final String getFactorAmt5( int index )
   {
      return _FactorAmt5[index];
   }
    
   /**
    * Gets the Factor Amount 5 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Factor Amount 5 or the specified default value.
    */
   public final String getFactorAmt5( int index, String defaultValue )
   {
      return _FactorAmt5[index] == null ? defaultValue : _FactorAmt5[index];
   }
    
   /**
    * Gets the array of Factor Amount 5 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Factor Amount 5 values.
    */
   public final String[] getFactorAmt5Array()
   {
      return _FactorAmt5;
   }
    
   /**
    * Gets the Unit ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Unit ID or null.
    */
   public final Integer getUnitID( int index )
   {
      return _UnitID[index];
   }
    
   /**
    * Gets the Unit ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Unit ID or the specified default value.
    */
   public final int getUnitID( int index, int defaultValue )
   {
      return _UnitID[index] == null ? defaultValue : _UnitID[index].intValue();
   }
    
   /**
    * Gets the array of Unit ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Unit ID values.
    */
   public final Integer[] getUnitIDArray()
   {
      return _UnitID;
   }
    
   /**
    * Gets the Ex Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Ex Date or null.
    */
   public final Date getExDate( int index )
   {
      return _ExDate[index];
   }
    
   /**
    * Gets the Ex Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Ex Date or the specified default value.
    */
   public final Date getExDate( int index, Date defaultValue )
   {
      return _ExDate[index] == null ? defaultValue : _ExDate[index];
   }
    
   /**
    * Gets the array of Ex Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Ex Date values.
    */
   public final Date[] getExDateArray()
   {
      return _ExDate;
   }
    
   /**
    * Gets the Payment Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Payment Date or null.
    */
   public final Date getPayDate( int index )
   {
      return _PayDate[index];
   }
    
   /**
    * Gets the Payment Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payment Date or the specified default value.
    */
   public final Date getPayDate( int index, Date defaultValue )
   {
      return _PayDate[index] == null ? defaultValue : _PayDate[index];
   }
    
   /**
    * Gets the array of Payment Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Payment Date values.
    */
   public final Date[] getPayDateArray()
   {
      return _PayDate;
   }
    
   /**
    * Gets the Reinvest Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reinvest Date or null.
    */
   public final Date getReInvDate( int index )
   {
      return _ReInvDate[index];
   }
    
   /**
    * Gets the Reinvest Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reinvest Date or the specified default value.
    */
   public final Date getReInvDate( int index, Date defaultValue )
   {
      return _ReInvDate[index] == null ? defaultValue : _ReInvDate[index];
   }
    
   /**
    * Gets the array of Reinvest Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reinvest Date values.
    */
   public final Date[] getReInvDateArray()
   {
      return _ReInvDate;
   }
    
   /**
    * Gets the Distribution Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Distribution Type or null.
    */
   public final String getDistribType( int index )
   {
      return _DistribType[index];
   }
    
   /**
    * Gets the Distribution Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Distribution Type or the specified default value.
    */
   public final String getDistribType( int index, String defaultValue )
   {
      return _DistribType[index] == null ? defaultValue : _DistribType[index];
   }
    
   /**
    * Gets the array of Distribution Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Distribution Type values.
    */
   public final String[] getDistribTypeArray()
   {
      return _DistribType;
   }
    
   /**
    * Gets the Declaration field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Declaration or null.
    */
   public final String getDeclaration( int index )
   {
      return _Declaration[index];
   }
    
   /**
    * Gets the Declaration field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Declaration or the specified default value.
    */
   public final String getDeclaration( int index, String defaultValue )
   {
      return _Declaration[index] == null ? defaultValue : _Declaration[index];
   }
    
   /**
    * Gets the array of Declaration fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Declaration values.
    */
   public final String[] getDeclarationArray()
   {
      return _Declaration;
   }
    
   /**
    * Gets the Rate Period field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Rate Period or null.
    */
   public final String getRatePeriod( int index )
   {
      return _RatePeriod[index];
   }
    
   /**
    * Gets the Rate Period field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Rate Period or the specified default value.
    */
   public final String getRatePeriod( int index, String defaultValue )
   {
      return _RatePeriod[index] == null ? defaultValue : _RatePeriod[index];
   }
    
   /**
    * Gets the array of Rate Period fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Rate Period values.
    */
   public final String[] getRatePeriodArray()
   {
      return _RatePeriod;
   }
    
   /**
    * Gets the GAV Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the GAV Rate or null.
    */
   public final String getGAV( int index )
   {
      return _GAV[index];
   }
    
   /**
    * Gets the GAV Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the GAV Rate or the specified default value.
    */
   public final String getGAV( int index, String defaultValue )
   {
      return _GAV[index] == null ? defaultValue : _GAV[index];
   }
    
   /**
    * Gets the array of GAV Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of GAV Rate values.
    */
   public final String[] getGAVArray()
   {
      return _GAV;
   }
    
   /**
    * Gets the Latest Gross Unit Value for Transtype ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Latest Gross Unit Value for Transtype ID or null.
    */
   public final String getLastIDRate( int index )
   {
      return _LastIDRate[index];
   }
    
   /**
    * Gets the Latest Gross Unit Value for Transtype ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Latest Gross Unit Value for Transtype ID or the specified default value.
    */
   public final String getLastIDRate( int index, String defaultValue )
   {
      return _LastIDRate[index] == null ? defaultValue : _LastIDRate[index];
   }
    
   /**
    * Gets the array of Latest Gross Unit Value for Transtype ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Latest Gross Unit Value for Transtype ID values.
    */
   public final String[] getLastIDRateArray()
   {
      return _LastIDRate;
   }
    
   /**
    * Gets the Usage ID Rate for Multiple Pricing field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Usage ID Rate for Multiple Pricing or null.
    */
   public final String getMultiPriceUsageID( int index )
   {
      return _MultiPriceUsageID[index];
   }
    
   /**
    * Gets the Usage ID Rate for Multiple Pricing field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Usage ID Rate for Multiple Pricing or the specified default value.
    */
   public final String getMultiPriceUsageID( int index, String defaultValue )
   {
      return _MultiPriceUsageID[index] == null ? defaultValue : _MultiPriceUsageID[index];
   }
    
   /**
    * Gets the array of Usage ID Rate for Multiple Pricing fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Usage ID Rate for Multiple Pricing values.
    */
   public final String[] getMultiPriceUsageIDArray()
   {
      return _MultiPriceUsageID;
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
      _FundCodeList = responseBuffer.decodeString(responseBuffer.getNextField());
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _ValueAsAt = resizeArray( _ValueAsAt, _RepeatCount );
      _rxFundCode = resizeArray( _rxFundCode, _RepeatCount );
      _rxClassCode = resizeArray( _rxClassCode, _RepeatCount );
      _TransType = resizeArray( _TransType, _RepeatCount );
      _RecordDate = resizeArray( _RecordDate, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _ProcessTime = resizeArray( _ProcessTime, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _Username = resizeArray( _Username, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _Currency = resizeArray( _Currency, _RepeatCount );
      _UnitValue = resizeArray( _UnitValue, _RepeatCount );
      _UnAllocIncome = resizeArray( _UnAllocIncome, _RepeatCount );
      _Notional = resizeArray( _Notional, _RepeatCount );
      _SkeletonBusYr = resizeArray( _SkeletonBusYr, _RepeatCount );
      _GoodBad = resizeArray( _GoodBad, _RepeatCount );
      _CanDividend = resizeArray( _CanDividend, _RepeatCount );
      _InelgDividend = resizeArray( _InelgDividend, _RepeatCount );
      _CanInterest = resizeArray( _CanInterest, _RepeatCount );
      _ForeignInterest = resizeArray( _ForeignInterest, _RepeatCount );
      _ForeignDividend = resizeArray( _ForeignDividend, _RepeatCount );
      _AccrualIncome = resizeArray( _AccrualIncome, _RepeatCount );
      _MgmtFee = resizeArray( _MgmtFee, _RepeatCount );
      _TaxCapGain = resizeArray( _TaxCapGain, _RepeatCount );
      _ForeignTax = resizeArray( _ForeignTax, _RepeatCount );
      _OthIncome = resizeArray( _OthIncome, _RepeatCount );
      _RealizeGain = resizeArray( _RealizeGain, _RepeatCount );
      _TrusteeFee = resizeArray( _TrusteeFee, _RepeatCount );
      _EqualizationAmt = resizeArray( _EqualizationAmt, _RepeatCount );
      _PaidAmt = resizeArray( _PaidAmt, _RepeatCount );
      _PriceCode2 = resizeArray( _PriceCode2, _RepeatCount );
      _PriceDesc2 = resizeArray( _PriceDesc2, _RepeatCount );
      _UnitValue2 = resizeArray( _UnitValue2, _RepeatCount );
      _ChgFactor2 = resizeArray( _ChgFactor2, _RepeatCount );
      _PriceCode3 = resizeArray( _PriceCode3, _RepeatCount );
      _PriceDesc3 = resizeArray( _PriceDesc3, _RepeatCount );
      _UnitValue3 = resizeArray( _UnitValue3, _RepeatCount );
      _ChgFactor3 = resizeArray( _ChgFactor3, _RepeatCount );
      _PriceCode4 = resizeArray( _PriceCode4, _RepeatCount );
      _PriceDesc4 = resizeArray( _PriceDesc4, _RepeatCount );
      _UnitValue4 = resizeArray( _UnitValue4, _RepeatCount );
      _ChgFactor4 = resizeArray( _ChgFactor4, _RepeatCount );
      _PriceCode5 = resizeArray( _PriceCode5, _RepeatCount );
      _PriceDesc5 = resizeArray( _PriceDesc5, _RepeatCount );
      _UnitValue5 = resizeArray( _UnitValue5, _RepeatCount );
      _ChgFactor5 = resizeArray( _ChgFactor5, _RepeatCount );
      _ChgFactor = resizeArray( _ChgFactor, _RepeatCount );
      _FundLoadGrp = resizeArray( _FundLoadGrp, _RepeatCount );
      _ROC = resizeArray( _ROC, _RepeatCount );
      _rxWKN = resizeArray( _rxWKN, _RepeatCount );
      _rxISIN = resizeArray( _rxISIN, _RepeatCount );
      _FactorAmt1 = resizeArray( _FactorAmt1, _RepeatCount );
      _FactorAmt2 = resizeArray( _FactorAmt2, _RepeatCount );
      _FactorAmt3 = resizeArray( _FactorAmt3, _RepeatCount );
      _FactorAmt4 = resizeArray( _FactorAmt4, _RepeatCount );
      _FactorAmt5 = resizeArray( _FactorAmt5, _RepeatCount );
      _UnitID = resizeArray( _UnitID, _RepeatCount );
      _ExDate = resizeArray( _ExDate, _RepeatCount );
      _PayDate = resizeArray( _PayDate, _RepeatCount );
      _ReInvDate = resizeArray( _ReInvDate, _RepeatCount );
      _DistribType = resizeArray( _DistribType, _RepeatCount );
      _Declaration = resizeArray( _Declaration, _RepeatCount );
      _RatePeriod = resizeArray( _RatePeriod, _RepeatCount );
      _GAV = resizeArray( _GAV, _RepeatCount );
      _LastIDRate = resizeArray( _LastIDRate, _RepeatCount );
      _MultiPriceUsageID = resizeArray( _MultiPriceUsageID, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _ValueAsAt[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _rxFundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TransType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RecordDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ProcessTime[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _Username[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Currency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UnitValue[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UnAllocIncome[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Notional[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _SkeletonBusYr[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _GoodBad[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _CanDividend[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _InelgDividend[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CanInterest[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ForeignInterest[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ForeignDividend[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AccrualIncome[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MgmtFee[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TaxCapGain[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ForeignTax[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _OthIncome[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RealizeGain[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TrusteeFee[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EqualizationAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PaidAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PriceCode2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PriceDesc2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UnitValue2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ChgFactor2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PriceCode3[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PriceDesc3[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UnitValue3[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ChgFactor3[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PriceCode4[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PriceDesc4[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UnitValue4[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ChgFactor4[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PriceCode5[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PriceDesc5[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UnitValue5[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ChgFactor5[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ChgFactor[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundLoadGrp[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ROC[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxWKN[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxISIN[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FactorAmt1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FactorAmt2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FactorAmt3[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FactorAmt4[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FactorAmt5[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UnitID[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ExDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _PayDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ReInvDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _DistribType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Declaration[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RatePeriod[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GAV[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LastIDRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MultiPriceUsageID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
