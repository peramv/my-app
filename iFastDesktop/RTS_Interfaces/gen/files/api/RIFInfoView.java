
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * RIF Plan Setup Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/RIFInfo.doc">RIFInfo.doc</A>.
 * 
 * @author RTS Generated
 */
public class RIFInfoView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Plan Type member array.
    */
   private String[] _PlanType = null;
   
   /**
    * Record ID member array.
    */
   private Integer[] _RIFId = null;
   
   /**
    * Record Type member array.
    */
   private String[] _RecType = null;
   
   /**
    * Record Type Description member array.
    */
   private String[] _RecTypeDesc = null;
   
   /**
    * Suppress Federal Tax member array.
    */
   private Boolean[] _SuppFedTax = null;
   
   /**
    * Suppress Provincial Tax member array.
    */
   private Boolean[] _SuppProvTax = null;
   
   /**
    * Federal Tax Rate member array.
    */
   private String[] _FedRate = null;
   
   /**
    * Federal Tax Rate Unit member array.
    */
   private String[] _FedRatePUD = null;
   
   /**
    * Provincial Tax Rate member array.
    */
   private String[] _ProvRate = null;
   
   /**
    * Provincial Tax Rate Unit member array.
    */
   private String[] _ProvRatePUD = null;
   
   /**
    * Gross Payment Amount member array.
    */
   private String[] _Amount = null;
   
   /**
    * Amount is expressed as Gross or Net member array.
    */
   private String[] _GrossOrNet = null;
   
   /**
    * Net Amount of Taxes member array.
    */
   private String[] _NetAmount = null;
   
   /**
    * Current Plan Value member array.
    */
   private String[] _NowPlanValue = null;
   
   /**
    * Previous Year End Plan Value member array.
    */
   private String[] _PYEPlanValue = null;
   
   /**
    * Calc Mandatory Payment per Year member array.
    */
   private String[] _CalcMandYr = null;
   
   /**
    * Calc Maximum Payment per Year member array.
    */
   private String[] _CalcMaxYr = null;
   
   /**
    * Mandatory Amount per Payment member array.
    */
   private String[] _MadAmtPay = null;
   
   /**
    * Mandatory Amount per Year member array.
    */
   private String[] _MandAmtYr = null;
   
   /**
    * RIF Payment type code member array.
    */
   private String[] _RIFPayType = null;
   
   /**
    * RIF Pay type description member array.
    */
   private String[] _RIFPayTypeDesc = null;
   
   /**
    * Instution code to debit member array.
    */
   private Integer[] _InstCode = null;
   
   /**
    * Institution Name member array.
    */
   private String[] _InstName = null;
   
   /**
    * Transit code member array.
    */
   private Integer[] _TransitNo = null;
   
   /**
    * Bank account to debit member array.
    */
   private String[] _BankAcctNum = null;
   
   /**
    * Payment Option member array.
    */
   private String[] _PayOption = null;
   
   /**
    * Payment Option Description member array.
    */
   private String[] _PayOptionDesc = null;
   
   /**
    * Maximum Payment Amount per Year member array.
    */
   private String[] _MaxAmtYr = null;
   
   /**
    * Tax calculation on Minimum Payment member array.
    */
   private Boolean[] _TaxOnMin = null;
   
   /**
    * Override Yearly Mandatory Amount member array.
    */
   private Boolean[] _OverrideAmtYr = null;
   
   /**
    * RIF Source of Fund member array.
    */
   private String[] _RIFSrcOfFund = null;
   
   /**
    * RIF Source of Fund Description member array.
    */
   private String[] _RIFSrcOfFundDesc = null;
   
   /**
    * Debit in January member array.
    */
   private Boolean[] _January = null;
   
   /**
    * Debit in February member array.
    */
   private Boolean[] _February = null;
   
   /**
    * Debit in March member array.
    */
   private Boolean[] _March = null;
   
   /**
    * Debit in April member array.
    */
   private Boolean[] _April = null;
   
   /**
    * Debit in May member array.
    */
   private Boolean[] _May = null;
   
   /**
    * Debit in June member array.
    */
   private Boolean[] _June = null;
   
   /**
    * Debit in July member array.
    */
   private Boolean[] _July = null;
   
   /**
    * Debit in August member array.
    */
   private Boolean[] _August = null;
   
   /**
    * Debit in September member array.
    */
   private Boolean[] _September = null;
   
   /**
    * Debit in October member array.
    */
   private Boolean[] _October = null;
   
   /**
    * Debit in November member array.
    */
   private Boolean[] _November = null;
   
   /**
    * Debit in December member array.
    */
   private Boolean[] _December = null;
   
   /**
    * RIF occurs at end of month member array.
    */
   private Boolean[] _EndOfMonth = null;
   
   /**
    * Last Process Date member array.
    */
   private Date[] _LastProcessDate = null;
   
   /**
    * Address Code member array.
    */
   private String[] _AddrCode = null;
   
   /**
    * Status code member array.
    */
   private Boolean[] _GoodBad = null;
   
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = null;
   
   /**
    * Modification Date member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * Stop Date member array.
    */
   private Date[] _StopDate = null;
   
   /**
    * Address Line1 member array.
    */
   private String[] _AddrLine1 = null;
   
   /**
    * Address Line2 member array.
    */
   private String[] _AddrLine2 = null;
   
   /**
    * Address Line3 member array.
    */
   private String[] _AddrLine3 = null;
   
   /**
    * Address Line4 member array.
    */
   private String[] _AddrLine4 = null;
   
   /**
    * Address Line5 member array.
    */
   private String[] _AddrLine5 = null;
   
   /**
    * Postal Code member array.
    */
   private String[] _PostalCode = null;
   
   /**
    * Index Rate member array.
    */
   private String[] _IndexRate = null;
   
   /**
    * Account registered before 1993 member array.
    */
   private Boolean[] _Qualified = null;
   
   /**
    * UserId who created the batch member array.
    */
   private String[] _Username = null;
   
   /**
    * Batch effective date member array.
    */
   private Date[] _BatchEffective = null;
   
   /**
    * Batch Name member array.
    */
   private String[] _BatchName = null;
   
   /**
    * Batch Trace member array.
    */
   private Integer[] _BatchTrace = null;
   
   /**
    * Spouse's Date of Birth member array.
    */
   private Date[] _SpouseBirth = null;
   
   /**
    * Payment period member array.
    */
   private Integer[] _PayTerm = null;
   
   /**
    * Payment period label member array.
    */
   private String[] _PayTermDesc = null;
   
   /**
    * Factor member array.
    */
   private String[] _Factor = null;
   
   /**
    * Cansim Rate member array.
    */
   private String[] _CansimRate = null;
   
   /**
    * Modification User member array.
    */
   private String[] _ModUser = null;
   
   /**
    * Process Date member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * Version Number member array.
    */
   private Integer[] _RRIFDetlVer = null;
   
   /**
    * Allocations Flag member array.
    */
   private Boolean[] _Allocations = null;
   
   /**
    * Transfer Account member array.
    */
   private String[] _TranAccount = null;
   
   /**
    * Previous Year Balance Percent Rate member array.
    */
   private String[] _PrevYrBalPct = null;
   
   /**
    * "TO" Allocations member array.
    */
   private Boolean[] _ToAllocations = null;
   
   /**
    * Override Unused Max member array.
    */
   private Boolean[] _OverrideUnusedMax = null;
   
   /**
    * PY Unused Max member array.
    */
   private String[] _PYUnusedMax = null;
   
   /**
    * Frequency member array.
    */
   private String[] _Frequency = null;
   
   /**
    * DayOfWeek member array.
    */
   private String[] _DayOfWeek = null;
   
   /**
    * Days Of Month member array.
    */
   private String[] _DaysOfMonth = null;
   
   /**
    * Reference Temporary Income member array.
    */
   private String[] _RefTempInc = null;
   
   /**
    * AdjustedTemporary Income member array.
    */
   private String[] _AdjLifeInc = null;
   
   /**
    * Bank Type member array.
    */
   private String[] _BankType = null;
   
   /**
    * Date to determine year of plan member array.
    */
   private Date[] _OrigPlanDeff = null;
   
   /**
    * Flag indicates if the original plan date is enable member array.
    */
   private Boolean[] _OrigPlanDeffApplied = null;
   
   /**
    * External Assets member array.
    */
   private String[] _ExternalAssets = null;
   
   /**
    * Source Of Fund member array.
    */
   private String[] _SrcOfFund = null;
   
   /**
    * Source Of Account member array.
    */
   private String[] _SrcOfAccount = null;
   

   /**
    * Constructs the RIFInfoView object.
    * 
    */
   public RIFInfoView()
   {
      super ( new RIFInfoRequest() );
   }

   /**
    * Constructs the RIFInfoView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public RIFInfoView( String hostEncoding )
   {
      super ( new RIFInfoRequest( hostEncoding ) );
   }

   /**
    * Gets the RIFInfoRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The RIFInfoRequest object.
    */
   public final RIFInfoRequest getRequest()
   {
      return (RIFInfoRequest)getIFastRequest();
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
    * Gets the Plan Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Plan Type or null.
    */
   public final String getPlanType( int index )
   {
      return _PlanType[index];
   }
    
   /**
    * Gets the Plan Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Plan Type or the specified default value.
    */
   public final String getPlanType( int index, String defaultValue )
   {
      return _PlanType[index] == null ? defaultValue : _PlanType[index];
   }
    
   /**
    * Gets the array of Plan Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Plan Type values.
    */
   public final String[] getPlanTypeArray()
   {
      return _PlanType;
   }
    
   /**
    * Gets the Record ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Record ID or null.
    */
   public final Integer getRIFId( int index )
   {
      return _RIFId[index];
   }
    
   /**
    * Gets the Record ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Record ID or the specified default value.
    */
   public final int getRIFId( int index, int defaultValue )
   {
      return _RIFId[index] == null ? defaultValue : _RIFId[index].intValue();
   }
    
   /**
    * Gets the array of Record ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Record ID values.
    */
   public final Integer[] getRIFIdArray()
   {
      return _RIFId;
   }
    
   /**
    * Gets the Record Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Record Type or null.
    */
   public final String getRecType( int index )
   {
      return _RecType[index];
   }
    
   /**
    * Gets the Record Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Record Type or the specified default value.
    */
   public final String getRecType( int index, String defaultValue )
   {
      return _RecType[index] == null ? defaultValue : _RecType[index];
   }
    
   /**
    * Gets the array of Record Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Record Type values.
    */
   public final String[] getRecTypeArray()
   {
      return _RecType;
   }
    
   /**
    * Gets the Record Type Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Record Type Description or null.
    */
   public final String getRecTypeDesc( int index )
   {
      return _RecTypeDesc[index];
   }
    
   /**
    * Gets the Record Type Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Record Type Description or the specified default value.
    */
   public final String getRecTypeDesc( int index, String defaultValue )
   {
      return _RecTypeDesc[index] == null ? defaultValue : _RecTypeDesc[index];
   }
    
   /**
    * Gets the array of Record Type Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Record Type Description values.
    */
   public final String[] getRecTypeDescArray()
   {
      return _RecTypeDesc;
   }
    
   /**
    * Gets the Suppress Federal Tax field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Suppress Federal Tax or null.
    */
   public final Boolean getSuppFedTax( int index )
   {
      return _SuppFedTax[index];
   }
    
   /**
    * Gets the Suppress Federal Tax field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Suppress Federal Tax or the specified default value.
    */
   public final boolean getSuppFedTax( int index, boolean defaultValue )
   {
      return _SuppFedTax[index] == null ? defaultValue : _SuppFedTax[index].booleanValue();
   }
    
   /**
    * Gets the array of Suppress Federal Tax fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Suppress Federal Tax values.
    */
   public final Boolean[] getSuppFedTaxArray()
   {
      return _SuppFedTax;
   }
    
   /**
    * Gets the Suppress Provincial Tax field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Suppress Provincial Tax or null.
    */
   public final Boolean getSuppProvTax( int index )
   {
      return _SuppProvTax[index];
   }
    
   /**
    * Gets the Suppress Provincial Tax field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Suppress Provincial Tax or the specified default value.
    */
   public final boolean getSuppProvTax( int index, boolean defaultValue )
   {
      return _SuppProvTax[index] == null ? defaultValue : _SuppProvTax[index].booleanValue();
   }
    
   /**
    * Gets the array of Suppress Provincial Tax fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Suppress Provincial Tax values.
    */
   public final Boolean[] getSuppProvTaxArray()
   {
      return _SuppProvTax;
   }
    
   /**
    * Gets the Federal Tax Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Federal Tax Rate or null.
    */
   public final String getFedRate( int index )
   {
      return _FedRate[index];
   }
    
   /**
    * Gets the Federal Tax Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Federal Tax Rate or the specified default value.
    */
   public final String getFedRate( int index, String defaultValue )
   {
      return _FedRate[index] == null ? defaultValue : _FedRate[index];
   }
    
   /**
    * Gets the array of Federal Tax Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Federal Tax Rate values.
    */
   public final String[] getFedRateArray()
   {
      return _FedRate;
   }
    
   /**
    * Gets the Federal Tax Rate Unit field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Federal Tax Rate Unit or null.
    */
   public final String getFedRatePUD( int index )
   {
      return _FedRatePUD[index];
   }
    
   /**
    * Gets the Federal Tax Rate Unit field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Federal Tax Rate Unit or the specified default value.
    */
   public final String getFedRatePUD( int index, String defaultValue )
   {
      return _FedRatePUD[index] == null ? defaultValue : _FedRatePUD[index];
   }
    
   /**
    * Gets the array of Federal Tax Rate Unit fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Federal Tax Rate Unit values.
    */
   public final String[] getFedRatePUDArray()
   {
      return _FedRatePUD;
   }
    
   /**
    * Gets the Provincial Tax Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Provincial Tax Rate or null.
    */
   public final String getProvRate( int index )
   {
      return _ProvRate[index];
   }
    
   /**
    * Gets the Provincial Tax Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Provincial Tax Rate or the specified default value.
    */
   public final String getProvRate( int index, String defaultValue )
   {
      return _ProvRate[index] == null ? defaultValue : _ProvRate[index];
   }
    
   /**
    * Gets the array of Provincial Tax Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Provincial Tax Rate values.
    */
   public final String[] getProvRateArray()
   {
      return _ProvRate;
   }
    
   /**
    * Gets the Provincial Tax Rate Unit field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Provincial Tax Rate Unit or null.
    */
   public final String getProvRatePUD( int index )
   {
      return _ProvRatePUD[index];
   }
    
   /**
    * Gets the Provincial Tax Rate Unit field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Provincial Tax Rate Unit or the specified default value.
    */
   public final String getProvRatePUD( int index, String defaultValue )
   {
      return _ProvRatePUD[index] == null ? defaultValue : _ProvRatePUD[index];
   }
    
   /**
    * Gets the array of Provincial Tax Rate Unit fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Provincial Tax Rate Unit values.
    */
   public final String[] getProvRatePUDArray()
   {
      return _ProvRatePUD;
   }
    
   /**
    * Gets the Gross Payment Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Gross Payment Amount or null.
    */
   public final String getAmount( int index )
   {
      return _Amount[index];
   }
    
   /**
    * Gets the Gross Payment Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Gross Payment Amount or the specified default value.
    */
   public final String getAmount( int index, String defaultValue )
   {
      return _Amount[index] == null ? defaultValue : _Amount[index];
   }
    
   /**
    * Gets the array of Gross Payment Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Gross Payment Amount values.
    */
   public final String[] getAmountArray()
   {
      return _Amount;
   }
    
   /**
    * Gets the Amount is expressed as Gross or Net field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Amount is expressed as Gross or Net or null.
    */
   public final String getGrossOrNet( int index )
   {
      return _GrossOrNet[index];
   }
    
   /**
    * Gets the Amount is expressed as Gross or Net field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Amount is expressed as Gross or Net or the specified default value.
    */
   public final String getGrossOrNet( int index, String defaultValue )
   {
      return _GrossOrNet[index] == null ? defaultValue : _GrossOrNet[index];
   }
    
   /**
    * Gets the array of Amount is expressed as Gross or Net fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Amount is expressed as Gross or Net values.
    */
   public final String[] getGrossOrNetArray()
   {
      return _GrossOrNet;
   }
    
   /**
    * Gets the Net Amount of Taxes field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Net Amount of Taxes or null.
    */
   public final String getNetAmount( int index )
   {
      return _NetAmount[index];
   }
    
   /**
    * Gets the Net Amount of Taxes field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Net Amount of Taxes or the specified default value.
    */
   public final String getNetAmount( int index, String defaultValue )
   {
      return _NetAmount[index] == null ? defaultValue : _NetAmount[index];
   }
    
   /**
    * Gets the array of Net Amount of Taxes fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Net Amount of Taxes values.
    */
   public final String[] getNetAmountArray()
   {
      return _NetAmount;
   }
    
   /**
    * Gets the Current Plan Value field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Current Plan Value or null.
    */
   public final String getNowPlanValue( int index )
   {
      return _NowPlanValue[index];
   }
    
   /**
    * Gets the Current Plan Value field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Current Plan Value or the specified default value.
    */
   public final String getNowPlanValue( int index, String defaultValue )
   {
      return _NowPlanValue[index] == null ? defaultValue : _NowPlanValue[index];
   }
    
   /**
    * Gets the array of Current Plan Value fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Current Plan Value values.
    */
   public final String[] getNowPlanValueArray()
   {
      return _NowPlanValue;
   }
    
   /**
    * Gets the Previous Year End Plan Value field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Previous Year End Plan Value or null.
    */
   public final String getPYEPlanValue( int index )
   {
      return _PYEPlanValue[index];
   }
    
   /**
    * Gets the Previous Year End Plan Value field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Previous Year End Plan Value or the specified default value.
    */
   public final String getPYEPlanValue( int index, String defaultValue )
   {
      return _PYEPlanValue[index] == null ? defaultValue : _PYEPlanValue[index];
   }
    
   /**
    * Gets the array of Previous Year End Plan Value fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Previous Year End Plan Value values.
    */
   public final String[] getPYEPlanValueArray()
   {
      return _PYEPlanValue;
   }
    
   /**
    * Gets the Calc Mandatory Payment per Year field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Calc Mandatory Payment per Year or null.
    */
   public final String getCalcMandYr( int index )
   {
      return _CalcMandYr[index];
   }
    
   /**
    * Gets the Calc Mandatory Payment per Year field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Calc Mandatory Payment per Year or the specified default value.
    */
   public final String getCalcMandYr( int index, String defaultValue )
   {
      return _CalcMandYr[index] == null ? defaultValue : _CalcMandYr[index];
   }
    
   /**
    * Gets the array of Calc Mandatory Payment per Year fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Calc Mandatory Payment per Year values.
    */
   public final String[] getCalcMandYrArray()
   {
      return _CalcMandYr;
   }
    
   /**
    * Gets the Calc Maximum Payment per Year field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Calc Maximum Payment per Year or null.
    */
   public final String getCalcMaxYr( int index )
   {
      return _CalcMaxYr[index];
   }
    
   /**
    * Gets the Calc Maximum Payment per Year field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Calc Maximum Payment per Year or the specified default value.
    */
   public final String getCalcMaxYr( int index, String defaultValue )
   {
      return _CalcMaxYr[index] == null ? defaultValue : _CalcMaxYr[index];
   }
    
   /**
    * Gets the array of Calc Maximum Payment per Year fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Calc Maximum Payment per Year values.
    */
   public final String[] getCalcMaxYrArray()
   {
      return _CalcMaxYr;
   }
    
   /**
    * Gets the Mandatory Amount per Payment field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Mandatory Amount per Payment or null.
    */
   public final String getMadAmtPay( int index )
   {
      return _MadAmtPay[index];
   }
    
   /**
    * Gets the Mandatory Amount per Payment field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Mandatory Amount per Payment or the specified default value.
    */
   public final String getMadAmtPay( int index, String defaultValue )
   {
      return _MadAmtPay[index] == null ? defaultValue : _MadAmtPay[index];
   }
    
   /**
    * Gets the array of Mandatory Amount per Payment fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Mandatory Amount per Payment values.
    */
   public final String[] getMadAmtPayArray()
   {
      return _MadAmtPay;
   }
    
   /**
    * Gets the Mandatory Amount per Year field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Mandatory Amount per Year or null.
    */
   public final String getMandAmtYr( int index )
   {
      return _MandAmtYr[index];
   }
    
   /**
    * Gets the Mandatory Amount per Year field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Mandatory Amount per Year or the specified default value.
    */
   public final String getMandAmtYr( int index, String defaultValue )
   {
      return _MandAmtYr[index] == null ? defaultValue : _MandAmtYr[index];
   }
    
   /**
    * Gets the array of Mandatory Amount per Year fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Mandatory Amount per Year values.
    */
   public final String[] getMandAmtYrArray()
   {
      return _MandAmtYr;
   }
    
   /**
    * Gets the RIF Payment type code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RIF Payment type code or null.
    */
   public final String getRIFPayType( int index )
   {
      return _RIFPayType[index];
   }
    
   /**
    * Gets the RIF Payment type code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RIF Payment type code or the specified default value.
    */
   public final String getRIFPayType( int index, String defaultValue )
   {
      return _RIFPayType[index] == null ? defaultValue : _RIFPayType[index];
   }
    
   /**
    * Gets the array of RIF Payment type code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RIF Payment type code values.
    */
   public final String[] getRIFPayTypeArray()
   {
      return _RIFPayType;
   }
    
   /**
    * Gets the RIF Pay type description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RIF Pay type description or null.
    */
   public final String getRIFPayTypeDesc( int index )
   {
      return _RIFPayTypeDesc[index];
   }
    
   /**
    * Gets the RIF Pay type description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RIF Pay type description or the specified default value.
    */
   public final String getRIFPayTypeDesc( int index, String defaultValue )
   {
      return _RIFPayTypeDesc[index] == null ? defaultValue : _RIFPayTypeDesc[index];
   }
    
   /**
    * Gets the array of RIF Pay type description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RIF Pay type description values.
    */
   public final String[] getRIFPayTypeDescArray()
   {
      return _RIFPayTypeDesc;
   }
    
   /**
    * Gets the Instution code to debit field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Instution code to debit or null.
    */
   public final Integer getInstCode( int index )
   {
      return _InstCode[index];
   }
    
   /**
    * Gets the Instution code to debit field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Instution code to debit or the specified default value.
    */
   public final int getInstCode( int index, int defaultValue )
   {
      return _InstCode[index] == null ? defaultValue : _InstCode[index].intValue();
   }
    
   /**
    * Gets the array of Instution code to debit fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Instution code to debit values.
    */
   public final Integer[] getInstCodeArray()
   {
      return _InstCode;
   }
    
   /**
    * Gets the Institution Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Institution Name or null.
    */
   public final String getInstName( int index )
   {
      return _InstName[index];
   }
    
   /**
    * Gets the Institution Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Institution Name or the specified default value.
    */
   public final String getInstName( int index, String defaultValue )
   {
      return _InstName[index] == null ? defaultValue : _InstName[index];
   }
    
   /**
    * Gets the array of Institution Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Institution Name values.
    */
   public final String[] getInstNameArray()
   {
      return _InstName;
   }
    
   /**
    * Gets the Transit code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transit code or null.
    */
   public final Integer getTransitNo( int index )
   {
      return _TransitNo[index];
   }
    
   /**
    * Gets the Transit code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transit code or the specified default value.
    */
   public final int getTransitNo( int index, int defaultValue )
   {
      return _TransitNo[index] == null ? defaultValue : _TransitNo[index].intValue();
   }
    
   /**
    * Gets the array of Transit code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transit code values.
    */
   public final Integer[] getTransitNoArray()
   {
      return _TransitNo;
   }
    
   /**
    * Gets the Bank account to debit field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank account to debit or null.
    */
   public final String getBankAcctNum( int index )
   {
      return _BankAcctNum[index];
   }
    
   /**
    * Gets the Bank account to debit field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank account to debit or the specified default value.
    */
   public final String getBankAcctNum( int index, String defaultValue )
   {
      return _BankAcctNum[index] == null ? defaultValue : _BankAcctNum[index];
   }
    
   /**
    * Gets the array of Bank account to debit fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank account to debit values.
    */
   public final String[] getBankAcctNumArray()
   {
      return _BankAcctNum;
   }
    
   /**
    * Gets the Payment Option field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Payment Option or null.
    */
   public final String getPayOption( int index )
   {
      return _PayOption[index];
   }
    
   /**
    * Gets the Payment Option field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payment Option or the specified default value.
    */
   public final String getPayOption( int index, String defaultValue )
   {
      return _PayOption[index] == null ? defaultValue : _PayOption[index];
   }
    
   /**
    * Gets the array of Payment Option fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Payment Option values.
    */
   public final String[] getPayOptionArray()
   {
      return _PayOption;
   }
    
   /**
    * Gets the Payment Option Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Payment Option Description or null.
    */
   public final String getPayOptionDesc( int index )
   {
      return _PayOptionDesc[index];
   }
    
   /**
    * Gets the Payment Option Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payment Option Description or the specified default value.
    */
   public final String getPayOptionDesc( int index, String defaultValue )
   {
      return _PayOptionDesc[index] == null ? defaultValue : _PayOptionDesc[index];
   }
    
   /**
    * Gets the array of Payment Option Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Payment Option Description values.
    */
   public final String[] getPayOptionDescArray()
   {
      return _PayOptionDesc;
   }
    
   /**
    * Gets the Maximum Payment Amount per Year field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Maximum Payment Amount per Year or null.
    */
   public final String getMaxAmtYr( int index )
   {
      return _MaxAmtYr[index];
   }
    
   /**
    * Gets the Maximum Payment Amount per Year field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Maximum Payment Amount per Year or the specified default value.
    */
   public final String getMaxAmtYr( int index, String defaultValue )
   {
      return _MaxAmtYr[index] == null ? defaultValue : _MaxAmtYr[index];
   }
    
   /**
    * Gets the array of Maximum Payment Amount per Year fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Maximum Payment Amount per Year values.
    */
   public final String[] getMaxAmtYrArray()
   {
      return _MaxAmtYr;
   }
    
   /**
    * Gets the Tax calculation on Minimum Payment field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax calculation on Minimum Payment or null.
    */
   public final Boolean getTaxOnMin( int index )
   {
      return _TaxOnMin[index];
   }
    
   /**
    * Gets the Tax calculation on Minimum Payment field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax calculation on Minimum Payment or the specified default value.
    */
   public final boolean getTaxOnMin( int index, boolean defaultValue )
   {
      return _TaxOnMin[index] == null ? defaultValue : _TaxOnMin[index].booleanValue();
   }
    
   /**
    * Gets the array of Tax calculation on Minimum Payment fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax calculation on Minimum Payment values.
    */
   public final Boolean[] getTaxOnMinArray()
   {
      return _TaxOnMin;
   }
    
   /**
    * Gets the Override Yearly Mandatory Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Override Yearly Mandatory Amount or null.
    */
   public final Boolean getOverrideAmtYr( int index )
   {
      return _OverrideAmtYr[index];
   }
    
   /**
    * Gets the Override Yearly Mandatory Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Override Yearly Mandatory Amount or the specified default value.
    */
   public final boolean getOverrideAmtYr( int index, boolean defaultValue )
   {
      return _OverrideAmtYr[index] == null ? defaultValue : _OverrideAmtYr[index].booleanValue();
   }
    
   /**
    * Gets the array of Override Yearly Mandatory Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Override Yearly Mandatory Amount values.
    */
   public final Boolean[] getOverrideAmtYrArray()
   {
      return _OverrideAmtYr;
   }
    
   /**
    * Gets the RIF Source of Fund field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RIF Source of Fund or null.
    */
   public final String getRIFSrcOfFund( int index )
   {
      return _RIFSrcOfFund[index];
   }
    
   /**
    * Gets the RIF Source of Fund field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RIF Source of Fund or the specified default value.
    */
   public final String getRIFSrcOfFund( int index, String defaultValue )
   {
      return _RIFSrcOfFund[index] == null ? defaultValue : _RIFSrcOfFund[index];
   }
    
   /**
    * Gets the array of RIF Source of Fund fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RIF Source of Fund values.
    */
   public final String[] getRIFSrcOfFundArray()
   {
      return _RIFSrcOfFund;
   }
    
   /**
    * Gets the RIF Source of Fund Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RIF Source of Fund Description or null.
    */
   public final String getRIFSrcOfFundDesc( int index )
   {
      return _RIFSrcOfFundDesc[index];
   }
    
   /**
    * Gets the RIF Source of Fund Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RIF Source of Fund Description or the specified default value.
    */
   public final String getRIFSrcOfFundDesc( int index, String defaultValue )
   {
      return _RIFSrcOfFundDesc[index] == null ? defaultValue : _RIFSrcOfFundDesc[index];
   }
    
   /**
    * Gets the array of RIF Source of Fund Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RIF Source of Fund Description values.
    */
   public final String[] getRIFSrcOfFundDescArray()
   {
      return _RIFSrcOfFundDesc;
   }
    
   /**
    * Gets the Debit in January field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Debit in January or null.
    */
   public final Boolean getJanuary( int index )
   {
      return _January[index];
   }
    
   /**
    * Gets the Debit in January field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Debit in January or the specified default value.
    */
   public final boolean getJanuary( int index, boolean defaultValue )
   {
      return _January[index] == null ? defaultValue : _January[index].booleanValue();
   }
    
   /**
    * Gets the array of Debit in January fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Debit in January values.
    */
   public final Boolean[] getJanuaryArray()
   {
      return _January;
   }
    
   /**
    * Gets the Debit in February field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Debit in February or null.
    */
   public final Boolean getFebruary( int index )
   {
      return _February[index];
   }
    
   /**
    * Gets the Debit in February field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Debit in February or the specified default value.
    */
   public final boolean getFebruary( int index, boolean defaultValue )
   {
      return _February[index] == null ? defaultValue : _February[index].booleanValue();
   }
    
   /**
    * Gets the array of Debit in February fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Debit in February values.
    */
   public final Boolean[] getFebruaryArray()
   {
      return _February;
   }
    
   /**
    * Gets the Debit in March field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Debit in March or null.
    */
   public final Boolean getMarch( int index )
   {
      return _March[index];
   }
    
   /**
    * Gets the Debit in March field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Debit in March or the specified default value.
    */
   public final boolean getMarch( int index, boolean defaultValue )
   {
      return _March[index] == null ? defaultValue : _March[index].booleanValue();
   }
    
   /**
    * Gets the array of Debit in March fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Debit in March values.
    */
   public final Boolean[] getMarchArray()
   {
      return _March;
   }
    
   /**
    * Gets the Debit in April field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Debit in April or null.
    */
   public final Boolean getApril( int index )
   {
      return _April[index];
   }
    
   /**
    * Gets the Debit in April field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Debit in April or the specified default value.
    */
   public final boolean getApril( int index, boolean defaultValue )
   {
      return _April[index] == null ? defaultValue : _April[index].booleanValue();
   }
    
   /**
    * Gets the array of Debit in April fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Debit in April values.
    */
   public final Boolean[] getAprilArray()
   {
      return _April;
   }
    
   /**
    * Gets the Debit in May field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Debit in May or null.
    */
   public final Boolean getMay( int index )
   {
      return _May[index];
   }
    
   /**
    * Gets the Debit in May field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Debit in May or the specified default value.
    */
   public final boolean getMay( int index, boolean defaultValue )
   {
      return _May[index] == null ? defaultValue : _May[index].booleanValue();
   }
    
   /**
    * Gets the array of Debit in May fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Debit in May values.
    */
   public final Boolean[] getMayArray()
   {
      return _May;
   }
    
   /**
    * Gets the Debit in June field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Debit in June or null.
    */
   public final Boolean getJune( int index )
   {
      return _June[index];
   }
    
   /**
    * Gets the Debit in June field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Debit in June or the specified default value.
    */
   public final boolean getJune( int index, boolean defaultValue )
   {
      return _June[index] == null ? defaultValue : _June[index].booleanValue();
   }
    
   /**
    * Gets the array of Debit in June fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Debit in June values.
    */
   public final Boolean[] getJuneArray()
   {
      return _June;
   }
    
   /**
    * Gets the Debit in July field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Debit in July or null.
    */
   public final Boolean getJuly( int index )
   {
      return _July[index];
   }
    
   /**
    * Gets the Debit in July field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Debit in July or the specified default value.
    */
   public final boolean getJuly( int index, boolean defaultValue )
   {
      return _July[index] == null ? defaultValue : _July[index].booleanValue();
   }
    
   /**
    * Gets the array of Debit in July fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Debit in July values.
    */
   public final Boolean[] getJulyArray()
   {
      return _July;
   }
    
   /**
    * Gets the Debit in August field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Debit in August or null.
    */
   public final Boolean getAugust( int index )
   {
      return _August[index];
   }
    
   /**
    * Gets the Debit in August field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Debit in August or the specified default value.
    */
   public final boolean getAugust( int index, boolean defaultValue )
   {
      return _August[index] == null ? defaultValue : _August[index].booleanValue();
   }
    
   /**
    * Gets the array of Debit in August fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Debit in August values.
    */
   public final Boolean[] getAugustArray()
   {
      return _August;
   }
    
   /**
    * Gets the Debit in September field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Debit in September or null.
    */
   public final Boolean getSeptember( int index )
   {
      return _September[index];
   }
    
   /**
    * Gets the Debit in September field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Debit in September or the specified default value.
    */
   public final boolean getSeptember( int index, boolean defaultValue )
   {
      return _September[index] == null ? defaultValue : _September[index].booleanValue();
   }
    
   /**
    * Gets the array of Debit in September fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Debit in September values.
    */
   public final Boolean[] getSeptemberArray()
   {
      return _September;
   }
    
   /**
    * Gets the Debit in October field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Debit in October or null.
    */
   public final Boolean getOctober( int index )
   {
      return _October[index];
   }
    
   /**
    * Gets the Debit in October field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Debit in October or the specified default value.
    */
   public final boolean getOctober( int index, boolean defaultValue )
   {
      return _October[index] == null ? defaultValue : _October[index].booleanValue();
   }
    
   /**
    * Gets the array of Debit in October fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Debit in October values.
    */
   public final Boolean[] getOctoberArray()
   {
      return _October;
   }
    
   /**
    * Gets the Debit in November field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Debit in November or null.
    */
   public final Boolean getNovember( int index )
   {
      return _November[index];
   }
    
   /**
    * Gets the Debit in November field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Debit in November or the specified default value.
    */
   public final boolean getNovember( int index, boolean defaultValue )
   {
      return _November[index] == null ? defaultValue : _November[index].booleanValue();
   }
    
   /**
    * Gets the array of Debit in November fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Debit in November values.
    */
   public final Boolean[] getNovemberArray()
   {
      return _November;
   }
    
   /**
    * Gets the Debit in December field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Debit in December or null.
    */
   public final Boolean getDecember( int index )
   {
      return _December[index];
   }
    
   /**
    * Gets the Debit in December field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Debit in December or the specified default value.
    */
   public final boolean getDecember( int index, boolean defaultValue )
   {
      return _December[index] == null ? defaultValue : _December[index].booleanValue();
   }
    
   /**
    * Gets the array of Debit in December fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Debit in December values.
    */
   public final Boolean[] getDecemberArray()
   {
      return _December;
   }
    
   /**
    * Gets the RIF occurs at end of month field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RIF occurs at end of month or null.
    */
   public final Boolean getEndOfMonth( int index )
   {
      return _EndOfMonth[index];
   }
    
   /**
    * Gets the RIF occurs at end of month field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RIF occurs at end of month or the specified default value.
    */
   public final boolean getEndOfMonth( int index, boolean defaultValue )
   {
      return _EndOfMonth[index] == null ? defaultValue : _EndOfMonth[index].booleanValue();
   }
    
   /**
    * Gets the array of RIF occurs at end of month fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RIF occurs at end of month values.
    */
   public final Boolean[] getEndOfMonthArray()
   {
      return _EndOfMonth;
   }
    
   /**
    * Gets the Last Process Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Last Process Date or null.
    */
   public final Date getLastProcessDate( int index )
   {
      return _LastProcessDate[index];
   }
    
   /**
    * Gets the Last Process Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Last Process Date or the specified default value.
    */
   public final Date getLastProcessDate( int index, Date defaultValue )
   {
      return _LastProcessDate[index] == null ? defaultValue : _LastProcessDate[index];
   }
    
   /**
    * Gets the array of Last Process Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Last Process Date values.
    */
   public final Date[] getLastProcessDateArray()
   {
      return _LastProcessDate;
   }
    
   /**
    * Gets the Address Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Code or null.
    */
   public final String getAddrCode( int index )
   {
      return _AddrCode[index];
   }
    
   /**
    * Gets the Address Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Code or the specified default value.
    */
   public final String getAddrCode( int index, String defaultValue )
   {
      return _AddrCode[index] == null ? defaultValue : _AddrCode[index];
   }
    
   /**
    * Gets the array of Address Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Code values.
    */
   public final String[] getAddrCodeArray()
   {
      return _AddrCode;
   }
    
   /**
    * Gets the Status code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Status code or null.
    */
   public final Boolean getGoodBad( int index )
   {
      return _GoodBad[index];
   }
    
   /**
    * Gets the Status code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Status code or the specified default value.
    */
   public final boolean getGoodBad( int index, boolean defaultValue )
   {
      return _GoodBad[index] == null ? defaultValue : _GoodBad[index].booleanValue();
   }
    
   /**
    * Gets the array of Status code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Status code values.
    */
   public final Boolean[] getGoodBadArray()
   {
      return _GoodBad;
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
    * Gets the Stop Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stop Date or null.
    */
   public final Date getStopDate( int index )
   {
      return _StopDate[index];
   }
    
   /**
    * Gets the Stop Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Date or the specified default value.
    */
   public final Date getStopDate( int index, Date defaultValue )
   {
      return _StopDate[index] == null ? defaultValue : _StopDate[index];
   }
    
   /**
    * Gets the array of Stop Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stop Date values.
    */
   public final Date[] getStopDateArray()
   {
      return _StopDate;
   }
    
   /**
    * Gets the Address Line1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Line1 or null.
    */
   public final String getAddrLine1( int index )
   {
      return _AddrLine1[index];
   }
    
   /**
    * Gets the Address Line1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line1 or the specified default value.
    */
   public final String getAddrLine1( int index, String defaultValue )
   {
      return _AddrLine1[index] == null ? defaultValue : _AddrLine1[index];
   }
    
   /**
    * Gets the array of Address Line1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Line1 values.
    */
   public final String[] getAddrLine1Array()
   {
      return _AddrLine1;
   }
    
   /**
    * Gets the Address Line2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Line2 or null.
    */
   public final String getAddrLine2( int index )
   {
      return _AddrLine2[index];
   }
    
   /**
    * Gets the Address Line2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line2 or the specified default value.
    */
   public final String getAddrLine2( int index, String defaultValue )
   {
      return _AddrLine2[index] == null ? defaultValue : _AddrLine2[index];
   }
    
   /**
    * Gets the array of Address Line2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Line2 values.
    */
   public final String[] getAddrLine2Array()
   {
      return _AddrLine2;
   }
    
   /**
    * Gets the Address Line3 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Line3 or null.
    */
   public final String getAddrLine3( int index )
   {
      return _AddrLine3[index];
   }
    
   /**
    * Gets the Address Line3 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line3 or the specified default value.
    */
   public final String getAddrLine3( int index, String defaultValue )
   {
      return _AddrLine3[index] == null ? defaultValue : _AddrLine3[index];
   }
    
   /**
    * Gets the array of Address Line3 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Line3 values.
    */
   public final String[] getAddrLine3Array()
   {
      return _AddrLine3;
   }
    
   /**
    * Gets the Address Line4 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Line4 or null.
    */
   public final String getAddrLine4( int index )
   {
      return _AddrLine4[index];
   }
    
   /**
    * Gets the Address Line4 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line4 or the specified default value.
    */
   public final String getAddrLine4( int index, String defaultValue )
   {
      return _AddrLine4[index] == null ? defaultValue : _AddrLine4[index];
   }
    
   /**
    * Gets the array of Address Line4 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Line4 values.
    */
   public final String[] getAddrLine4Array()
   {
      return _AddrLine4;
   }
    
   /**
    * Gets the Address Line5 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Line5 or null.
    */
   public final String getAddrLine5( int index )
   {
      return _AddrLine5[index];
   }
    
   /**
    * Gets the Address Line5 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line5 or the specified default value.
    */
   public final String getAddrLine5( int index, String defaultValue )
   {
      return _AddrLine5[index] == null ? defaultValue : _AddrLine5[index];
   }
    
   /**
    * Gets the array of Address Line5 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Line5 values.
    */
   public final String[] getAddrLine5Array()
   {
      return _AddrLine5;
   }
    
   /**
    * Gets the Postal Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Postal Code or null.
    */
   public final String getPostalCode( int index )
   {
      return _PostalCode[index];
   }
    
   /**
    * Gets the Postal Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Postal Code or the specified default value.
    */
   public final String getPostalCode( int index, String defaultValue )
   {
      return _PostalCode[index] == null ? defaultValue : _PostalCode[index];
   }
    
   /**
    * Gets the array of Postal Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Postal Code values.
    */
   public final String[] getPostalCodeArray()
   {
      return _PostalCode;
   }
    
   /**
    * Gets the Index Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Index Rate or null.
    */
   public final String getIndexRate( int index )
   {
      return _IndexRate[index];
   }
    
   /**
    * Gets the Index Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Index Rate or the specified default value.
    */
   public final String getIndexRate( int index, String defaultValue )
   {
      return _IndexRate[index] == null ? defaultValue : _IndexRate[index];
   }
    
   /**
    * Gets the array of Index Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Index Rate values.
    */
   public final String[] getIndexRateArray()
   {
      return _IndexRate;
   }
    
   /**
    * Gets the Account registered before 1993 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account registered before 1993 or null.
    */
   public final Boolean getQualified( int index )
   {
      return _Qualified[index];
   }
    
   /**
    * Gets the Account registered before 1993 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account registered before 1993 or the specified default value.
    */
   public final boolean getQualified( int index, boolean defaultValue )
   {
      return _Qualified[index] == null ? defaultValue : _Qualified[index].booleanValue();
   }
    
   /**
    * Gets the array of Account registered before 1993 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account registered before 1993 values.
    */
   public final Boolean[] getQualifiedArray()
   {
      return _Qualified;
   }
    
   /**
    * Gets the UserId who created the batch field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the UserId who created the batch or null.
    */
   public final String getUsername( int index )
   {
      return _Username[index];
   }
    
   /**
    * Gets the UserId who created the batch field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the UserId who created the batch or the specified default value.
    */
   public final String getUsername( int index, String defaultValue )
   {
      return _Username[index] == null ? defaultValue : _Username[index];
   }
    
   /**
    * Gets the array of UserId who created the batch fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of UserId who created the batch values.
    */
   public final String[] getUsernameArray()
   {
      return _Username;
   }
    
   /**
    * Gets the Batch effective date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Batch effective date or null.
    */
   public final Date getBatchEffective( int index )
   {
      return _BatchEffective[index];
   }
    
   /**
    * Gets the Batch effective date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Batch effective date or the specified default value.
    */
   public final Date getBatchEffective( int index, Date defaultValue )
   {
      return _BatchEffective[index] == null ? defaultValue : _BatchEffective[index];
   }
    
   /**
    * Gets the array of Batch effective date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Batch effective date values.
    */
   public final Date[] getBatchEffectiveArray()
   {
      return _BatchEffective;
   }
    
   /**
    * Gets the Batch Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Batch Name or null.
    */
   public final String getBatchName( int index )
   {
      return _BatchName[index];
   }
    
   /**
    * Gets the Batch Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Batch Name or the specified default value.
    */
   public final String getBatchName( int index, String defaultValue )
   {
      return _BatchName[index] == null ? defaultValue : _BatchName[index];
   }
    
   /**
    * Gets the array of Batch Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Batch Name values.
    */
   public final String[] getBatchNameArray()
   {
      return _BatchName;
   }
    
   /**
    * Gets the Batch Trace field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Batch Trace or null.
    */
   public final Integer getBatchTrace( int index )
   {
      return _BatchTrace[index];
   }
    
   /**
    * Gets the Batch Trace field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Batch Trace or the specified default value.
    */
   public final int getBatchTrace( int index, int defaultValue )
   {
      return _BatchTrace[index] == null ? defaultValue : _BatchTrace[index].intValue();
   }
    
   /**
    * Gets the array of Batch Trace fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Batch Trace values.
    */
   public final Integer[] getBatchTraceArray()
   {
      return _BatchTrace;
   }
    
   /**
    * Gets the Spouse's Date of Birth field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Spouse's Date of Birth or null.
    */
   public final Date getSpouseBirth( int index )
   {
      return _SpouseBirth[index];
   }
    
   /**
    * Gets the Spouse's Date of Birth field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Spouse's Date of Birth or the specified default value.
    */
   public final Date getSpouseBirth( int index, Date defaultValue )
   {
      return _SpouseBirth[index] == null ? defaultValue : _SpouseBirth[index];
   }
    
   /**
    * Gets the array of Spouse's Date of Birth fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Spouse's Date of Birth values.
    */
   public final Date[] getSpouseBirthArray()
   {
      return _SpouseBirth;
   }
    
   /**
    * Gets the Payment period field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Payment period or null.
    */
   public final Integer getPayTerm( int index )
   {
      return _PayTerm[index];
   }
    
   /**
    * Gets the Payment period field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payment period or the specified default value.
    */
   public final int getPayTerm( int index, int defaultValue )
   {
      return _PayTerm[index] == null ? defaultValue : _PayTerm[index].intValue();
   }
    
   /**
    * Gets the array of Payment period fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Payment period values.
    */
   public final Integer[] getPayTermArray()
   {
      return _PayTerm;
   }
    
   /**
    * Gets the Payment period label field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Payment period label or null.
    */
   public final String getPayTermDesc( int index )
   {
      return _PayTermDesc[index];
   }
    
   /**
    * Gets the Payment period label field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payment period label or the specified default value.
    */
   public final String getPayTermDesc( int index, String defaultValue )
   {
      return _PayTermDesc[index] == null ? defaultValue : _PayTermDesc[index];
   }
    
   /**
    * Gets the array of Payment period label fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Payment period label values.
    */
   public final String[] getPayTermDescArray()
   {
      return _PayTermDesc;
   }
    
   /**
    * Gets the Factor field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Factor or null.
    */
   public final String getFactor( int index )
   {
      return _Factor[index];
   }
    
   /**
    * Gets the Factor field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Factor or the specified default value.
    */
   public final String getFactor( int index, String defaultValue )
   {
      return _Factor[index] == null ? defaultValue : _Factor[index];
   }
    
   /**
    * Gets the array of Factor fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Factor values.
    */
   public final String[] getFactorArray()
   {
      return _Factor;
   }
    
   /**
    * Gets the Cansim Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Cansim Rate or null.
    */
   public final String getCansimRate( int index )
   {
      return _CansimRate[index];
   }
    
   /**
    * Gets the Cansim Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Cansim Rate or the specified default value.
    */
   public final String getCansimRate( int index, String defaultValue )
   {
      return _CansimRate[index] == null ? defaultValue : _CansimRate[index];
   }
    
   /**
    * Gets the array of Cansim Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Cansim Rate values.
    */
   public final String[] getCansimRateArray()
   {
      return _CansimRate;
   }
    
   /**
    * Gets the Modification User field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Modification User or null.
    */
   public final String getModUser( int index )
   {
      return _ModUser[index];
   }
    
   /**
    * Gets the Modification User field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Modification User or the specified default value.
    */
   public final String getModUser( int index, String defaultValue )
   {
      return _ModUser[index] == null ? defaultValue : _ModUser[index];
   }
    
   /**
    * Gets the array of Modification User fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Modification User values.
    */
   public final String[] getModUserArray()
   {
      return _ModUser;
   }
    
   /**
    * Gets the Process Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Process Date or null.
    */
   public final Date getProcessDate( int index )
   {
      return _ProcessDate[index];
   }
    
   /**
    * Gets the Process Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Process Date or the specified default value.
    */
   public final Date getProcessDate( int index, Date defaultValue )
   {
      return _ProcessDate[index] == null ? defaultValue : _ProcessDate[index];
   }
    
   /**
    * Gets the array of Process Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Process Date values.
    */
   public final Date[] getProcessDateArray()
   {
      return _ProcessDate;
   }
    
   /**
    * Gets the Version Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Version Number or null.
    */
   public final Integer getRRIFDetlVer( int index )
   {
      return _RRIFDetlVer[index];
   }
    
   /**
    * Gets the Version Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Version Number or the specified default value.
    */
   public final int getRRIFDetlVer( int index, int defaultValue )
   {
      return _RRIFDetlVer[index] == null ? defaultValue : _RRIFDetlVer[index].intValue();
   }
    
   /**
    * Gets the array of Version Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Version Number values.
    */
   public final Integer[] getRRIFDetlVerArray()
   {
      return _RRIFDetlVer;
   }
    
   /**
    * Gets the Allocations Flag field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Allocations Flag or null.
    */
   public final Boolean getAllocations( int index )
   {
      return _Allocations[index];
   }
    
   /**
    * Gets the Allocations Flag field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Allocations Flag or the specified default value.
    */
   public final boolean getAllocations( int index, boolean defaultValue )
   {
      return _Allocations[index] == null ? defaultValue : _Allocations[index].booleanValue();
   }
    
   /**
    * Gets the array of Allocations Flag fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Allocations Flag values.
    */
   public final Boolean[] getAllocationsArray()
   {
      return _Allocations;
   }
    
   /**
    * Gets the Transfer Account field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transfer Account or null.
    */
   public final String getTranAccount( int index )
   {
      return _TranAccount[index];
   }
    
   /**
    * Gets the Transfer Account field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transfer Account or the specified default value.
    */
   public final String getTranAccount( int index, String defaultValue )
   {
      return _TranAccount[index] == null ? defaultValue : _TranAccount[index];
   }
    
   /**
    * Gets the array of Transfer Account fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transfer Account values.
    */
   public final String[] getTranAccountArray()
   {
      return _TranAccount;
   }
    
   /**
    * Gets the Previous Year Balance Percent Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Previous Year Balance Percent Rate or null.
    */
   public final String getPrevYrBalPct( int index )
   {
      return _PrevYrBalPct[index];
   }
    
   /**
    * Gets the Previous Year Balance Percent Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Previous Year Balance Percent Rate or the specified default value.
    */
   public final String getPrevYrBalPct( int index, String defaultValue )
   {
      return _PrevYrBalPct[index] == null ? defaultValue : _PrevYrBalPct[index];
   }
    
   /**
    * Gets the array of Previous Year Balance Percent Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Previous Year Balance Percent Rate values.
    */
   public final String[] getPrevYrBalPctArray()
   {
      return _PrevYrBalPct;
   }
    
   /**
    * Gets the "TO" Allocations field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the "TO" Allocations or null.
    */
   public final Boolean getToAllocations( int index )
   {
      return _ToAllocations[index];
   }
    
   /**
    * Gets the "TO" Allocations field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the "TO" Allocations or the specified default value.
    */
   public final boolean getToAllocations( int index, boolean defaultValue )
   {
      return _ToAllocations[index] == null ? defaultValue : _ToAllocations[index].booleanValue();
   }
    
   /**
    * Gets the array of "TO" Allocations fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of "TO" Allocations values.
    */
   public final Boolean[] getToAllocationsArray()
   {
      return _ToAllocations;
   }
    
   /**
    * Gets the Override Unused Max field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Override Unused Max or null.
    */
   public final Boolean getOverrideUnusedMax( int index )
   {
      return _OverrideUnusedMax[index];
   }
    
   /**
    * Gets the Override Unused Max field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Override Unused Max or the specified default value.
    */
   public final boolean getOverrideUnusedMax( int index, boolean defaultValue )
   {
      return _OverrideUnusedMax[index] == null ? defaultValue : _OverrideUnusedMax[index].booleanValue();
   }
    
   /**
    * Gets the array of Override Unused Max fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Override Unused Max values.
    */
   public final Boolean[] getOverrideUnusedMaxArray()
   {
      return _OverrideUnusedMax;
   }
    
   /**
    * Gets the PY Unused Max field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the PY Unused Max or null.
    */
   public final String getPYUnusedMax( int index )
   {
      return _PYUnusedMax[index];
   }
    
   /**
    * Gets the PY Unused Max field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PY Unused Max or the specified default value.
    */
   public final String getPYUnusedMax( int index, String defaultValue )
   {
      return _PYUnusedMax[index] == null ? defaultValue : _PYUnusedMax[index];
   }
    
   /**
    * Gets the array of PY Unused Max fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of PY Unused Max values.
    */
   public final String[] getPYUnusedMaxArray()
   {
      return _PYUnusedMax;
   }
    
   /**
    * Gets the Frequency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Frequency or null.
    */
   public final String getFrequency( int index )
   {
      return _Frequency[index];
   }
    
   /**
    * Gets the Frequency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Frequency or the specified default value.
    */
   public final String getFrequency( int index, String defaultValue )
   {
      return _Frequency[index] == null ? defaultValue : _Frequency[index];
   }
    
   /**
    * Gets the array of Frequency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Frequency values.
    */
   public final String[] getFrequencyArray()
   {
      return _Frequency;
   }
    
   /**
    * Gets the DayOfWeek field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the DayOfWeek or null.
    */
   public final String getDayOfWeek( int index )
   {
      return _DayOfWeek[index];
   }
    
   /**
    * Gets the DayOfWeek field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the DayOfWeek or the specified default value.
    */
   public final String getDayOfWeek( int index, String defaultValue )
   {
      return _DayOfWeek[index] == null ? defaultValue : _DayOfWeek[index];
   }
    
   /**
    * Gets the array of DayOfWeek fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of DayOfWeek values.
    */
   public final String[] getDayOfWeekArray()
   {
      return _DayOfWeek;
   }
    
   /**
    * Gets the Days Of Month field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Days Of Month or null.
    */
   public final String getDaysOfMonth( int index )
   {
      return _DaysOfMonth[index];
   }
    
   /**
    * Gets the Days Of Month field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Days Of Month or the specified default value.
    */
   public final String getDaysOfMonth( int index, String defaultValue )
   {
      return _DaysOfMonth[index] == null ? defaultValue : _DaysOfMonth[index];
   }
    
   /**
    * Gets the array of Days Of Month fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Days Of Month values.
    */
   public final String[] getDaysOfMonthArray()
   {
      return _DaysOfMonth;
   }
    
   /**
    * Gets the Reference Temporary Income field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reference Temporary Income or null.
    */
   public final String getRefTempInc( int index )
   {
      return _RefTempInc[index];
   }
    
   /**
    * Gets the Reference Temporary Income field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reference Temporary Income or the specified default value.
    */
   public final String getRefTempInc( int index, String defaultValue )
   {
      return _RefTempInc[index] == null ? defaultValue : _RefTempInc[index];
   }
    
   /**
    * Gets the array of Reference Temporary Income fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reference Temporary Income values.
    */
   public final String[] getRefTempIncArray()
   {
      return _RefTempInc;
   }
    
   /**
    * Gets the AdjustedTemporary Income field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AdjustedTemporary Income or null.
    */
   public final String getAdjLifeInc( int index )
   {
      return _AdjLifeInc[index];
   }
    
   /**
    * Gets the AdjustedTemporary Income field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AdjustedTemporary Income or the specified default value.
    */
   public final String getAdjLifeInc( int index, String defaultValue )
   {
      return _AdjLifeInc[index] == null ? defaultValue : _AdjLifeInc[index];
   }
    
   /**
    * Gets the array of AdjustedTemporary Income fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AdjustedTemporary Income values.
    */
   public final String[] getAdjLifeIncArray()
   {
      return _AdjLifeInc;
   }
    
   /**
    * Gets the Bank Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Type or null.
    */
   public final String getBankType( int index )
   {
      return _BankType[index];
   }
    
   /**
    * Gets the Bank Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Type or the specified default value.
    */
   public final String getBankType( int index, String defaultValue )
   {
      return _BankType[index] == null ? defaultValue : _BankType[index];
   }
    
   /**
    * Gets the array of Bank Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Type values.
    */
   public final String[] getBankTypeArray()
   {
      return _BankType;
   }
    
   /**
    * Gets the Date to determine year of plan field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Date to determine year of plan or null.
    */
   public final Date getOrigPlanDeff( int index )
   {
      return _OrigPlanDeff[index];
   }
    
   /**
    * Gets the Date to determine year of plan field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date to determine year of plan or the specified default value.
    */
   public final Date getOrigPlanDeff( int index, Date defaultValue )
   {
      return _OrigPlanDeff[index] == null ? defaultValue : _OrigPlanDeff[index];
   }
    
   /**
    * Gets the array of Date to determine year of plan fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Date to determine year of plan values.
    */
   public final Date[] getOrigPlanDeffArray()
   {
      return _OrigPlanDeff;
   }
    
   /**
    * Gets the Flag indicates if the original plan date is enable field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicates if the original plan date is enable or null.
    */
   public final Boolean getOrigPlanDeffApplied( int index )
   {
      return _OrigPlanDeffApplied[index];
   }
    
   /**
    * Gets the Flag indicates if the original plan date is enable field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicates if the original plan date is enable or the specified default value.
    */
   public final boolean getOrigPlanDeffApplied( int index, boolean defaultValue )
   {
      return _OrigPlanDeffApplied[index] == null ? defaultValue : _OrigPlanDeffApplied[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicates if the original plan date is enable fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicates if the original plan date is enable values.
    */
   public final Boolean[] getOrigPlanDeffAppliedArray()
   {
      return _OrigPlanDeffApplied;
   }
    
   /**
    * Gets the External Assets field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the External Assets or null.
    */
   public final String getExternalAssets( int index )
   {
      return _ExternalAssets[index];
   }
    
   /**
    * Gets the External Assets field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the External Assets or the specified default value.
    */
   public final String getExternalAssets( int index, String defaultValue )
   {
      return _ExternalAssets[index] == null ? defaultValue : _ExternalAssets[index];
   }
    
   /**
    * Gets the array of External Assets fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of External Assets values.
    */
   public final String[] getExternalAssetsArray()
   {
      return _ExternalAssets;
   }
    
   /**
    * Gets the Source Of Fund field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Source Of Fund or null.
    */
   public final String getSrcOfFund( int index )
   {
      return _SrcOfFund[index];
   }
    
   /**
    * Gets the Source Of Fund field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Source Of Fund or the specified default value.
    */
   public final String getSrcOfFund( int index, String defaultValue )
   {
      return _SrcOfFund[index] == null ? defaultValue : _SrcOfFund[index];
   }
    
   /**
    * Gets the array of Source Of Fund fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Source Of Fund values.
    */
   public final String[] getSrcOfFundArray()
   {
      return _SrcOfFund;
   }
    
   /**
    * Gets the Source Of Account field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Source Of Account or null.
    */
   public final String getSrcOfAccount( int index )
   {
      return _SrcOfAccount[index];
   }
    
   /**
    * Gets the Source Of Account field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Source Of Account or the specified default value.
    */
   public final String getSrcOfAccount( int index, String defaultValue )
   {
      return _SrcOfAccount[index] == null ? defaultValue : _SrcOfAccount[index];
   }
    
   /**
    * Gets the array of Source Of Account fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Source Of Account values.
    */
   public final String[] getSrcOfAccountArray()
   {
      return _SrcOfAccount;
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
      
      _PlanType = resizeArray( _PlanType, _RepeatCount );
      _RIFId = resizeArray( _RIFId, _RepeatCount );
      _RecType = resizeArray( _RecType, _RepeatCount );
      _RecTypeDesc = resizeArray( _RecTypeDesc, _RepeatCount );
      _SuppFedTax = resizeArray( _SuppFedTax, _RepeatCount );
      _SuppProvTax = resizeArray( _SuppProvTax, _RepeatCount );
      _FedRate = resizeArray( _FedRate, _RepeatCount );
      _FedRatePUD = resizeArray( _FedRatePUD, _RepeatCount );
      _ProvRate = resizeArray( _ProvRate, _RepeatCount );
      _ProvRatePUD = resizeArray( _ProvRatePUD, _RepeatCount );
      _Amount = resizeArray( _Amount, _RepeatCount );
      _GrossOrNet = resizeArray( _GrossOrNet, _RepeatCount );
      _NetAmount = resizeArray( _NetAmount, _RepeatCount );
      _NowPlanValue = resizeArray( _NowPlanValue, _RepeatCount );
      _PYEPlanValue = resizeArray( _PYEPlanValue, _RepeatCount );
      _CalcMandYr = resizeArray( _CalcMandYr, _RepeatCount );
      _CalcMaxYr = resizeArray( _CalcMaxYr, _RepeatCount );
      _MadAmtPay = resizeArray( _MadAmtPay, _RepeatCount );
      _MandAmtYr = resizeArray( _MandAmtYr, _RepeatCount );
      _RIFPayType = resizeArray( _RIFPayType, _RepeatCount );
      _RIFPayTypeDesc = resizeArray( _RIFPayTypeDesc, _RepeatCount );
      _InstCode = resizeArray( _InstCode, _RepeatCount );
      _InstName = resizeArray( _InstName, _RepeatCount );
      _TransitNo = resizeArray( _TransitNo, _RepeatCount );
      _BankAcctNum = resizeArray( _BankAcctNum, _RepeatCount );
      _PayOption = resizeArray( _PayOption, _RepeatCount );
      _PayOptionDesc = resizeArray( _PayOptionDesc, _RepeatCount );
      _MaxAmtYr = resizeArray( _MaxAmtYr, _RepeatCount );
      _TaxOnMin = resizeArray( _TaxOnMin, _RepeatCount );
      _OverrideAmtYr = resizeArray( _OverrideAmtYr, _RepeatCount );
      _RIFSrcOfFund = resizeArray( _RIFSrcOfFund, _RepeatCount );
      _RIFSrcOfFundDesc = resizeArray( _RIFSrcOfFundDesc, _RepeatCount );
      _January = resizeArray( _January, _RepeatCount );
      _February = resizeArray( _February, _RepeatCount );
      _March = resizeArray( _March, _RepeatCount );
      _April = resizeArray( _April, _RepeatCount );
      _May = resizeArray( _May, _RepeatCount );
      _June = resizeArray( _June, _RepeatCount );
      _July = resizeArray( _July, _RepeatCount );
      _August = resizeArray( _August, _RepeatCount );
      _September = resizeArray( _September, _RepeatCount );
      _October = resizeArray( _October, _RepeatCount );
      _November = resizeArray( _November, _RepeatCount );
      _December = resizeArray( _December, _RepeatCount );
      _EndOfMonth = resizeArray( _EndOfMonth, _RepeatCount );
      _LastProcessDate = resizeArray( _LastProcessDate, _RepeatCount );
      _AddrCode = resizeArray( _AddrCode, _RepeatCount );
      _GoodBad = resizeArray( _GoodBad, _RepeatCount );
      _EffectiveDate = resizeArray( _EffectiveDate, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _StopDate = resizeArray( _StopDate, _RepeatCount );
      _AddrLine1 = resizeArray( _AddrLine1, _RepeatCount );
      _AddrLine2 = resizeArray( _AddrLine2, _RepeatCount );
      _AddrLine3 = resizeArray( _AddrLine3, _RepeatCount );
      _AddrLine4 = resizeArray( _AddrLine4, _RepeatCount );
      _AddrLine5 = resizeArray( _AddrLine5, _RepeatCount );
      _PostalCode = resizeArray( _PostalCode, _RepeatCount );
      _IndexRate = resizeArray( _IndexRate, _RepeatCount );
      _Qualified = resizeArray( _Qualified, _RepeatCount );
      _Username = resizeArray( _Username, _RepeatCount );
      _BatchEffective = resizeArray( _BatchEffective, _RepeatCount );
      _BatchName = resizeArray( _BatchName, _RepeatCount );
      _BatchTrace = resizeArray( _BatchTrace, _RepeatCount );
      _SpouseBirth = resizeArray( _SpouseBirth, _RepeatCount );
      _PayTerm = resizeArray( _PayTerm, _RepeatCount );
      _PayTermDesc = resizeArray( _PayTermDesc, _RepeatCount );
      _Factor = resizeArray( _Factor, _RepeatCount );
      _CansimRate = resizeArray( _CansimRate, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _RRIFDetlVer = resizeArray( _RRIFDetlVer, _RepeatCount );
      _Allocations = resizeArray( _Allocations, _RepeatCount );
      _TranAccount = resizeArray( _TranAccount, _RepeatCount );
      _PrevYrBalPct = resizeArray( _PrevYrBalPct, _RepeatCount );
      _ToAllocations = resizeArray( _ToAllocations, _RepeatCount );
      _OverrideUnusedMax = resizeArray( _OverrideUnusedMax, _RepeatCount );
      _PYUnusedMax = resizeArray( _PYUnusedMax, _RepeatCount );
      _Frequency = resizeArray( _Frequency, _RepeatCount );
      _DayOfWeek = resizeArray( _DayOfWeek, _RepeatCount );
      _DaysOfMonth = resizeArray( _DaysOfMonth, _RepeatCount );
      _RefTempInc = resizeArray( _RefTempInc, _RepeatCount );
      _AdjLifeInc = resizeArray( _AdjLifeInc, _RepeatCount );
      _BankType = resizeArray( _BankType, _RepeatCount );
      _OrigPlanDeff = resizeArray( _OrigPlanDeff, _RepeatCount );
      _OrigPlanDeffApplied = resizeArray( _OrigPlanDeffApplied, _RepeatCount );
      _ExternalAssets = resizeArray( _ExternalAssets, _RepeatCount );
      _SrcOfFund = resizeArray( _SrcOfFund, _RepeatCount );
      _SrcOfAccount = resizeArray( _SrcOfAccount, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _PlanType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RIFId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _RecType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RecTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SuppFedTax[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _SuppProvTax[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FedRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FedRatePUD[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProvRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProvRatePUD[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Amount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GrossOrNet[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _NetAmount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _NowPlanValue[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PYEPlanValue[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CalcMandYr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CalcMaxYr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MadAmtPay[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MandAmtYr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RIFPayType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RIFPayTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _InstCode[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _InstName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TransitNo[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _BankAcctNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PayOption[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PayOptionDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MaxAmtYr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TaxOnMin[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _OverrideAmtYr[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _RIFSrcOfFund[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RIFSrcOfFundDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _January[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _February[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _March[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _April[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _May[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _June[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _July[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _August[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _September[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _October[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _November[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _December[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _EndOfMonth[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _LastProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _AddrCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GoodBad[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _StopDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _AddrLine1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine3[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine4[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine5[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PostalCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IndexRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Qualified[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _Username[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BatchEffective[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _BatchName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BatchTrace[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _SpouseBirth[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _PayTerm[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _PayTermDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Factor[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CansimRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _RRIFDetlVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _Allocations[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TranAccount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PrevYrBalPct[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ToAllocations[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _OverrideUnusedMax[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _PYUnusedMax[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Frequency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DayOfWeek[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DaysOfMonth[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RefTempInc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AdjLifeInc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _OrigPlanDeff[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _OrigPlanDeffApplied[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ExternalAssets[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SrcOfFund[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SrcOfAccount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
