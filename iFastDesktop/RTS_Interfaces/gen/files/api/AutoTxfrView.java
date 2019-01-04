
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Automatic Transfer view.
 * For additional view information see <A HREF="../../../../viewspecs/AutoTxfr.doc">AutoTxfr.doc</A>.
 * 
 * @author RTS Generated
 */
public class AutoTxfrView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Automatic Transfer  Record ID member array.
    */
   private Integer[] _AutoTrfId = null;
   
   /**
    * Transfer From Fund member array.
    */
   private String[] _FundCode = null;
   
   /**
    * Transfer From Class member array.
    */
   private String[] _ClassCode = null;
   
   /**
    * Transfer To Fund member array.
    */
   private String[] _FundToCode = null;
   
   /**
    * Transfer To Class member array.
    */
   private String[] _ClassToCode = null;
   
   /**
    * Transfer To Account member array.
    */
   private String[] _AccountTo = null;
   
   /**
    * Amount member array.
    */
   private String[] _Amount = null;
   
   /**
    * Amount Type member array.
    */
   private String[] _AmountType = null;
   
   /**
    * Fee Amount or Percentage member array.
    */
   private String[] _Fee = null;
   
   /**
    * Fee Type member array.
    */
   private Boolean[] _FeeType = null;
   
   /**
    * Back End Load Fee Applicable member array.
    */
   private Boolean[] _BELFee = null;
   
   /**
    * Frequency Code member array.
    */
   private String[] _Frequency = null;
   
   /**
    * Day in the week transfer occurs on member array.
    */
   private Integer[] _DayOfWeek = null;
   
   /**
    * Transfer occurs at end of month member array.
    */
   private Boolean[] _EndOfMonth = null;
   
   /**
    * January member array.
    */
   private Boolean[] _January = null;
   
   /**
    * February member array.
    */
   private Boolean[] _February = null;
   
   /**
    * March member array.
    */
   private Boolean[] _March = null;
   
   /**
    * April member array.
    */
   private Boolean[] _April = null;
   
   /**
    * May member array.
    */
   private Boolean[] _May = null;
   
   /**
    * June member array.
    */
   private Boolean[] _June = null;
   
   /**
    * July member array.
    */
   private Boolean[] _July = null;
   
   /**
    * August member array.
    */
   private Boolean[] _August = null;
   
   /**
    * September member array.
    */
   private Boolean[] _September = null;
   
   /**
    * October member array.
    */
   private Boolean[] _October = null;
   
   /**
    * November member array.
    */
   private Boolean[] _November = null;
   
   /**
    * December member array.
    */
   private Boolean[] _December = null;
   
   /**
    * Last Process Date member array.
    */
   private Date[] _LastProcDate = null;
   
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = null;
   
   /**
    * Stop Date member array.
    */
   private Date[] _StopDate = null;
   
   /**
    * Batch User member array.
    */
   private String[] _BatchUser = null;
   
   /**
    * Batch Name member array.
    */
   private String[] _Batch = null;
   
   /**
    * Batch Trace member array.
    */
   private Integer[] _BatchTrace = null;
   
   /**
    * Batch Date member array.
    */
   private Date[] _BatchDate = null;
   
   /**
    * Transfer Type member array.
    */
   private String[] _TransferType = null;
   
   /**
    * Created On member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * Last Modification date member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * Created by User member array.
    */
   private String[] _Username = null;
   
   /**
    * Modified by User member array.
    */
   private String[] _ModUser = null;
   
   /**
    * Amount Type Description member array.
    */
   private String[] _AmountTypeDesc = null;
   
   /**
    * Fee Type Description member array.
    */
   private String[] _FeeTypeDesc = null;
   
   /**
    * Frequency Type Description member array.
    */
   private String[] _FrequencyDesc = null;
   
   /**
    * Transfer Type Description member array.
    */
   private String[] _TransferTypeDesc = null;
   
   /**
    * Recur-Detl Version Number member array.
    */
   private Integer[] _RecurDetlVer = null;
   

   /**
    * Constructs the AutoTxfrView object.
    * 
    */
   public AutoTxfrView()
   {
      super ( new AutoTxfrRequest() );
   }

   /**
    * Constructs the AutoTxfrView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AutoTxfrView( String hostEncoding )
   {
      super ( new AutoTxfrRequest( hostEncoding ) );
   }

   /**
    * Gets the AutoTxfrRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AutoTxfrRequest object.
    */
   public final AutoTxfrRequest getRequest()
   {
      return (AutoTxfrRequest)getIFastRequest();
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
    * Gets the Automatic Transfer  Record ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Automatic Transfer  Record ID or null.
    */
   public final Integer getAutoTrfId( int index )
   {
      return _AutoTrfId[index];
   }
    
   /**
    * Gets the Automatic Transfer  Record ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Automatic Transfer  Record ID or the specified default value.
    */
   public final int getAutoTrfId( int index, int defaultValue )
   {
      return _AutoTrfId[index] == null ? defaultValue : _AutoTrfId[index].intValue();
   }
    
   /**
    * Gets the array of Automatic Transfer  Record ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Automatic Transfer  Record ID values.
    */
   public final Integer[] getAutoTrfIdArray()
   {
      return _AutoTrfId;
   }
    
   /**
    * Gets the Transfer From Fund field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transfer From Fund or null.
    */
   public final String getFundCode( int index )
   {
      return _FundCode[index];
   }
    
   /**
    * Gets the Transfer From Fund field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transfer From Fund or the specified default value.
    */
   public final String getFundCode( int index, String defaultValue )
   {
      return _FundCode[index] == null ? defaultValue : _FundCode[index];
   }
    
   /**
    * Gets the array of Transfer From Fund fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transfer From Fund values.
    */
   public final String[] getFundCodeArray()
   {
      return _FundCode;
   }
    
   /**
    * Gets the Transfer From Class field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transfer From Class or null.
    */
   public final String getClassCode( int index )
   {
      return _ClassCode[index];
   }
    
   /**
    * Gets the Transfer From Class field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transfer From Class or the specified default value.
    */
   public final String getClassCode( int index, String defaultValue )
   {
      return _ClassCode[index] == null ? defaultValue : _ClassCode[index];
   }
    
   /**
    * Gets the array of Transfer From Class fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transfer From Class values.
    */
   public final String[] getClassCodeArray()
   {
      return _ClassCode;
   }
    
   /**
    * Gets the Transfer To Fund field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transfer To Fund or null.
    */
   public final String getFundToCode( int index )
   {
      return _FundToCode[index];
   }
    
   /**
    * Gets the Transfer To Fund field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transfer To Fund or the specified default value.
    */
   public final String getFundToCode( int index, String defaultValue )
   {
      return _FundToCode[index] == null ? defaultValue : _FundToCode[index];
   }
    
   /**
    * Gets the array of Transfer To Fund fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transfer To Fund values.
    */
   public final String[] getFundToCodeArray()
   {
      return _FundToCode;
   }
    
   /**
    * Gets the Transfer To Class field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transfer To Class or null.
    */
   public final String getClassToCode( int index )
   {
      return _ClassToCode[index];
   }
    
   /**
    * Gets the Transfer To Class field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transfer To Class or the specified default value.
    */
   public final String getClassToCode( int index, String defaultValue )
   {
      return _ClassToCode[index] == null ? defaultValue : _ClassToCode[index];
   }
    
   /**
    * Gets the array of Transfer To Class fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transfer To Class values.
    */
   public final String[] getClassToCodeArray()
   {
      return _ClassToCode;
   }
    
   /**
    * Gets the Transfer To Account field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transfer To Account or null.
    */
   public final String getAccountTo( int index )
   {
      return _AccountTo[index];
   }
    
   /**
    * Gets the Transfer To Account field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transfer To Account or the specified default value.
    */
   public final String getAccountTo( int index, String defaultValue )
   {
      return _AccountTo[index] == null ? defaultValue : _AccountTo[index];
   }
    
   /**
    * Gets the array of Transfer To Account fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transfer To Account values.
    */
   public final String[] getAccountToArray()
   {
      return _AccountTo;
   }
    
   /**
    * Gets the Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Amount or null.
    */
   public final String getAmount( int index )
   {
      return _Amount[index];
   }
    
   /**
    * Gets the Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Amount or the specified default value.
    */
   public final String getAmount( int index, String defaultValue )
   {
      return _Amount[index] == null ? defaultValue : _Amount[index];
   }
    
   /**
    * Gets the array of Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Amount values.
    */
   public final String[] getAmountArray()
   {
      return _Amount;
   }
    
   /**
    * Gets the Amount Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Amount Type or null.
    */
   public final String getAmountType( int index )
   {
      return _AmountType[index];
   }
    
   /**
    * Gets the Amount Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Amount Type or the specified default value.
    */
   public final String getAmountType( int index, String defaultValue )
   {
      return _AmountType[index] == null ? defaultValue : _AmountType[index];
   }
    
   /**
    * Gets the array of Amount Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Amount Type values.
    */
   public final String[] getAmountTypeArray()
   {
      return _AmountType;
   }
    
   /**
    * Gets the Fee Amount or Percentage field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fee Amount or Percentage or null.
    */
   public final String getFee( int index )
   {
      return _Fee[index];
   }
    
   /**
    * Gets the Fee Amount or Percentage field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee Amount or Percentage or the specified default value.
    */
   public final String getFee( int index, String defaultValue )
   {
      return _Fee[index] == null ? defaultValue : _Fee[index];
   }
    
   /**
    * Gets the array of Fee Amount or Percentage fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee Amount or Percentage values.
    */
   public final String[] getFeeArray()
   {
      return _Fee;
   }
    
   /**
    * Gets the Fee Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fee Type or null.
    */
   public final Boolean getFeeType( int index )
   {
      return _FeeType[index];
   }
    
   /**
    * Gets the Fee Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee Type or the specified default value.
    */
   public final boolean getFeeType( int index, boolean defaultValue )
   {
      return _FeeType[index] == null ? defaultValue : _FeeType[index].booleanValue();
   }
    
   /**
    * Gets the array of Fee Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee Type values.
    */
   public final Boolean[] getFeeTypeArray()
   {
      return _FeeType;
   }
    
   /**
    * Gets the Back End Load Fee Applicable field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Back End Load Fee Applicable or null.
    */
   public final Boolean getBELFee( int index )
   {
      return _BELFee[index];
   }
    
   /**
    * Gets the Back End Load Fee Applicable field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Back End Load Fee Applicable or the specified default value.
    */
   public final boolean getBELFee( int index, boolean defaultValue )
   {
      return _BELFee[index] == null ? defaultValue : _BELFee[index].booleanValue();
   }
    
   /**
    * Gets the array of Back End Load Fee Applicable fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Back End Load Fee Applicable values.
    */
   public final Boolean[] getBELFeeArray()
   {
      return _BELFee;
   }
    
   /**
    * Gets the Frequency Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Frequency Code or null.
    */
   public final String getFrequency( int index )
   {
      return _Frequency[index];
   }
    
   /**
    * Gets the Frequency Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Frequency Code or the specified default value.
    */
   public final String getFrequency( int index, String defaultValue )
   {
      return _Frequency[index] == null ? defaultValue : _Frequency[index];
   }
    
   /**
    * Gets the array of Frequency Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Frequency Code values.
    */
   public final String[] getFrequencyArray()
   {
      return _Frequency;
   }
    
   /**
    * Gets the Day in the week transfer occurs on field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Day in the week transfer occurs on or null.
    */
   public final Integer getDayOfWeek( int index )
   {
      return _DayOfWeek[index];
   }
    
   /**
    * Gets the Day in the week transfer occurs on field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Day in the week transfer occurs on or the specified default value.
    */
   public final int getDayOfWeek( int index, int defaultValue )
   {
      return _DayOfWeek[index] == null ? defaultValue : _DayOfWeek[index].intValue();
   }
    
   /**
    * Gets the array of Day in the week transfer occurs on fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Day in the week transfer occurs on values.
    */
   public final Integer[] getDayOfWeekArray()
   {
      return _DayOfWeek;
   }
    
   /**
    * Gets the Transfer occurs at end of month field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transfer occurs at end of month or null.
    */
   public final Boolean getEndOfMonth( int index )
   {
      return _EndOfMonth[index];
   }
    
   /**
    * Gets the Transfer occurs at end of month field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transfer occurs at end of month or the specified default value.
    */
   public final boolean getEndOfMonth( int index, boolean defaultValue )
   {
      return _EndOfMonth[index] == null ? defaultValue : _EndOfMonth[index].booleanValue();
   }
    
   /**
    * Gets the array of Transfer occurs at end of month fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transfer occurs at end of month values.
    */
   public final Boolean[] getEndOfMonthArray()
   {
      return _EndOfMonth;
   }
    
   /**
    * Gets the January field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the January or null.
    */
   public final Boolean getJanuary( int index )
   {
      return _January[index];
   }
    
   /**
    * Gets the January field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the January or the specified default value.
    */
   public final boolean getJanuary( int index, boolean defaultValue )
   {
      return _January[index] == null ? defaultValue : _January[index].booleanValue();
   }
    
   /**
    * Gets the array of January fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of January values.
    */
   public final Boolean[] getJanuaryArray()
   {
      return _January;
   }
    
   /**
    * Gets the February field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the February or null.
    */
   public final Boolean getFebruary( int index )
   {
      return _February[index];
   }
    
   /**
    * Gets the February field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the February or the specified default value.
    */
   public final boolean getFebruary( int index, boolean defaultValue )
   {
      return _February[index] == null ? defaultValue : _February[index].booleanValue();
   }
    
   /**
    * Gets the array of February fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of February values.
    */
   public final Boolean[] getFebruaryArray()
   {
      return _February;
   }
    
   /**
    * Gets the March field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the March or null.
    */
   public final Boolean getMarch( int index )
   {
      return _March[index];
   }
    
   /**
    * Gets the March field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the March or the specified default value.
    */
   public final boolean getMarch( int index, boolean defaultValue )
   {
      return _March[index] == null ? defaultValue : _March[index].booleanValue();
   }
    
   /**
    * Gets the array of March fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of March values.
    */
   public final Boolean[] getMarchArray()
   {
      return _March;
   }
    
   /**
    * Gets the April field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the April or null.
    */
   public final Boolean getApril( int index )
   {
      return _April[index];
   }
    
   /**
    * Gets the April field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the April or the specified default value.
    */
   public final boolean getApril( int index, boolean defaultValue )
   {
      return _April[index] == null ? defaultValue : _April[index].booleanValue();
   }
    
   /**
    * Gets the array of April fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of April values.
    */
   public final Boolean[] getAprilArray()
   {
      return _April;
   }
    
   /**
    * Gets the May field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the May or null.
    */
   public final Boolean getMay( int index )
   {
      return _May[index];
   }
    
   /**
    * Gets the May field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the May or the specified default value.
    */
   public final boolean getMay( int index, boolean defaultValue )
   {
      return _May[index] == null ? defaultValue : _May[index].booleanValue();
   }
    
   /**
    * Gets the array of May fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of May values.
    */
   public final Boolean[] getMayArray()
   {
      return _May;
   }
    
   /**
    * Gets the June field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the June or null.
    */
   public final Boolean getJune( int index )
   {
      return _June[index];
   }
    
   /**
    * Gets the June field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the June or the specified default value.
    */
   public final boolean getJune( int index, boolean defaultValue )
   {
      return _June[index] == null ? defaultValue : _June[index].booleanValue();
   }
    
   /**
    * Gets the array of June fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of June values.
    */
   public final Boolean[] getJuneArray()
   {
      return _June;
   }
    
   /**
    * Gets the July field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the July or null.
    */
   public final Boolean getJuly( int index )
   {
      return _July[index];
   }
    
   /**
    * Gets the July field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the July or the specified default value.
    */
   public final boolean getJuly( int index, boolean defaultValue )
   {
      return _July[index] == null ? defaultValue : _July[index].booleanValue();
   }
    
   /**
    * Gets the array of July fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of July values.
    */
   public final Boolean[] getJulyArray()
   {
      return _July;
   }
    
   /**
    * Gets the August field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the August or null.
    */
   public final Boolean getAugust( int index )
   {
      return _August[index];
   }
    
   /**
    * Gets the August field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the August or the specified default value.
    */
   public final boolean getAugust( int index, boolean defaultValue )
   {
      return _August[index] == null ? defaultValue : _August[index].booleanValue();
   }
    
   /**
    * Gets the array of August fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of August values.
    */
   public final Boolean[] getAugustArray()
   {
      return _August;
   }
    
   /**
    * Gets the September field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the September or null.
    */
   public final Boolean getSeptember( int index )
   {
      return _September[index];
   }
    
   /**
    * Gets the September field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the September or the specified default value.
    */
   public final boolean getSeptember( int index, boolean defaultValue )
   {
      return _September[index] == null ? defaultValue : _September[index].booleanValue();
   }
    
   /**
    * Gets the array of September fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of September values.
    */
   public final Boolean[] getSeptemberArray()
   {
      return _September;
   }
    
   /**
    * Gets the October field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the October or null.
    */
   public final Boolean getOctober( int index )
   {
      return _October[index];
   }
    
   /**
    * Gets the October field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the October or the specified default value.
    */
   public final boolean getOctober( int index, boolean defaultValue )
   {
      return _October[index] == null ? defaultValue : _October[index].booleanValue();
   }
    
   /**
    * Gets the array of October fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of October values.
    */
   public final Boolean[] getOctoberArray()
   {
      return _October;
   }
    
   /**
    * Gets the November field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the November or null.
    */
   public final Boolean getNovember( int index )
   {
      return _November[index];
   }
    
   /**
    * Gets the November field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the November or the specified default value.
    */
   public final boolean getNovember( int index, boolean defaultValue )
   {
      return _November[index] == null ? defaultValue : _November[index].booleanValue();
   }
    
   /**
    * Gets the array of November fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of November values.
    */
   public final Boolean[] getNovemberArray()
   {
      return _November;
   }
    
   /**
    * Gets the December field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the December or null.
    */
   public final Boolean getDecember( int index )
   {
      return _December[index];
   }
    
   /**
    * Gets the December field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the December or the specified default value.
    */
   public final boolean getDecember( int index, boolean defaultValue )
   {
      return _December[index] == null ? defaultValue : _December[index].booleanValue();
   }
    
   /**
    * Gets the array of December fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of December values.
    */
   public final Boolean[] getDecemberArray()
   {
      return _December;
   }
    
   /**
    * Gets the Last Process Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Last Process Date or null.
    */
   public final Date getLastProcDate( int index )
   {
      return _LastProcDate[index];
   }
    
   /**
    * Gets the Last Process Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Last Process Date or the specified default value.
    */
   public final Date getLastProcDate( int index, Date defaultValue )
   {
      return _LastProcDate[index] == null ? defaultValue : _LastProcDate[index];
   }
    
   /**
    * Gets the array of Last Process Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Last Process Date values.
    */
   public final Date[] getLastProcDateArray()
   {
      return _LastProcDate;
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
    * Gets the Batch User field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Batch User or null.
    */
   public final String getBatchUser( int index )
   {
      return _BatchUser[index];
   }
    
   /**
    * Gets the Batch User field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Batch User or the specified default value.
    */
   public final String getBatchUser( int index, String defaultValue )
   {
      return _BatchUser[index] == null ? defaultValue : _BatchUser[index];
   }
    
   /**
    * Gets the array of Batch User fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Batch User values.
    */
   public final String[] getBatchUserArray()
   {
      return _BatchUser;
   }
    
   /**
    * Gets the Batch Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Batch Name or null.
    */
   public final String getBatch( int index )
   {
      return _Batch[index];
   }
    
   /**
    * Gets the Batch Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Batch Name or the specified default value.
    */
   public final String getBatch( int index, String defaultValue )
   {
      return _Batch[index] == null ? defaultValue : _Batch[index];
   }
    
   /**
    * Gets the array of Batch Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Batch Name values.
    */
   public final String[] getBatchArray()
   {
      return _Batch;
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
    * Gets the Batch Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Batch Date or null.
    */
   public final Date getBatchDate( int index )
   {
      return _BatchDate[index];
   }
    
   /**
    * Gets the Batch Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Batch Date or the specified default value.
    */
   public final Date getBatchDate( int index, Date defaultValue )
   {
      return _BatchDate[index] == null ? defaultValue : _BatchDate[index];
   }
    
   /**
    * Gets the array of Batch Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Batch Date values.
    */
   public final Date[] getBatchDateArray()
   {
      return _BatchDate;
   }
    
   /**
    * Gets the Transfer Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transfer Type or null.
    */
   public final String getTransferType( int index )
   {
      return _TransferType[index];
   }
    
   /**
    * Gets the Transfer Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transfer Type or the specified default value.
    */
   public final String getTransferType( int index, String defaultValue )
   {
      return _TransferType[index] == null ? defaultValue : _TransferType[index];
   }
    
   /**
    * Gets the array of Transfer Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transfer Type values.
    */
   public final String[] getTransferTypeArray()
   {
      return _TransferType;
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
    * Gets the Last Modification date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Last Modification date or null.
    */
   public final Date getModDate( int index )
   {
      return _ModDate[index];
   }
    
   /**
    * Gets the Last Modification date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Last Modification date or the specified default value.
    */
   public final Date getModDate( int index, Date defaultValue )
   {
      return _ModDate[index] == null ? defaultValue : _ModDate[index];
   }
    
   /**
    * Gets the array of Last Modification date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Last Modification date values.
    */
   public final Date[] getModDateArray()
   {
      return _ModDate;
   }
    
   /**
    * Gets the Created by User field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Created by User or null.
    */
   public final String getUsername( int index )
   {
      return _Username[index];
   }
    
   /**
    * Gets the Created by User field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Created by User or the specified default value.
    */
   public final String getUsername( int index, String defaultValue )
   {
      return _Username[index] == null ? defaultValue : _Username[index];
   }
    
   /**
    * Gets the array of Created by User fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Created by User values.
    */
   public final String[] getUsernameArray()
   {
      return _Username;
   }
    
   /**
    * Gets the Modified by User field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Modified by User or null.
    */
   public final String getModUser( int index )
   {
      return _ModUser[index];
   }
    
   /**
    * Gets the Modified by User field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Modified by User or the specified default value.
    */
   public final String getModUser( int index, String defaultValue )
   {
      return _ModUser[index] == null ? defaultValue : _ModUser[index];
   }
    
   /**
    * Gets the array of Modified by User fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Modified by User values.
    */
   public final String[] getModUserArray()
   {
      return _ModUser;
   }
    
   /**
    * Gets the Amount Type Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Amount Type Description or null.
    */
   public final String getAmountTypeDesc( int index )
   {
      return _AmountTypeDesc[index];
   }
    
   /**
    * Gets the Amount Type Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Amount Type Description or the specified default value.
    */
   public final String getAmountTypeDesc( int index, String defaultValue )
   {
      return _AmountTypeDesc[index] == null ? defaultValue : _AmountTypeDesc[index];
   }
    
   /**
    * Gets the array of Amount Type Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Amount Type Description values.
    */
   public final String[] getAmountTypeDescArray()
   {
      return _AmountTypeDesc;
   }
    
   /**
    * Gets the Fee Type Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fee Type Description or null.
    */
   public final String getFeeTypeDesc( int index )
   {
      return _FeeTypeDesc[index];
   }
    
   /**
    * Gets the Fee Type Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee Type Description or the specified default value.
    */
   public final String getFeeTypeDesc( int index, String defaultValue )
   {
      return _FeeTypeDesc[index] == null ? defaultValue : _FeeTypeDesc[index];
   }
    
   /**
    * Gets the array of Fee Type Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee Type Description values.
    */
   public final String[] getFeeTypeDescArray()
   {
      return _FeeTypeDesc;
   }
    
   /**
    * Gets the Frequency Type Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Frequency Type Description or null.
    */
   public final String getFrequencyDesc( int index )
   {
      return _FrequencyDesc[index];
   }
    
   /**
    * Gets the Frequency Type Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Frequency Type Description or the specified default value.
    */
   public final String getFrequencyDesc( int index, String defaultValue )
   {
      return _FrequencyDesc[index] == null ? defaultValue : _FrequencyDesc[index];
   }
    
   /**
    * Gets the array of Frequency Type Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Frequency Type Description values.
    */
   public final String[] getFrequencyDescArray()
   {
      return _FrequencyDesc;
   }
    
   /**
    * Gets the Transfer Type Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transfer Type Description or null.
    */
   public final String getTransferTypeDesc( int index )
   {
      return _TransferTypeDesc[index];
   }
    
   /**
    * Gets the Transfer Type Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transfer Type Description or the specified default value.
    */
   public final String getTransferTypeDesc( int index, String defaultValue )
   {
      return _TransferTypeDesc[index] == null ? defaultValue : _TransferTypeDesc[index];
   }
    
   /**
    * Gets the array of Transfer Type Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transfer Type Description values.
    */
   public final String[] getTransferTypeDescArray()
   {
      return _TransferTypeDesc;
   }
    
   /**
    * Gets the Recur-Detl Version Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Recur-Detl Version Number or null.
    */
   public final Integer getRecurDetlVer( int index )
   {
      return _RecurDetlVer[index];
   }
    
   /**
    * Gets the Recur-Detl Version Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Recur-Detl Version Number or the specified default value.
    */
   public final int getRecurDetlVer( int index, int defaultValue )
   {
      return _RecurDetlVer[index] == null ? defaultValue : _RecurDetlVer[index].intValue();
   }
    
   /**
    * Gets the array of Recur-Detl Version Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Recur-Detl Version Number values.
    */
   public final Integer[] getRecurDetlVerArray()
   {
      return _RecurDetlVer;
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
      
      _AutoTrfId = resizeArray( _AutoTrfId, _RepeatCount );
      _FundCode = resizeArray( _FundCode, _RepeatCount );
      _ClassCode = resizeArray( _ClassCode, _RepeatCount );
      _FundToCode = resizeArray( _FundToCode, _RepeatCount );
      _ClassToCode = resizeArray( _ClassToCode, _RepeatCount );
      _AccountTo = resizeArray( _AccountTo, _RepeatCount );
      _Amount = resizeArray( _Amount, _RepeatCount );
      _AmountType = resizeArray( _AmountType, _RepeatCount );
      _Fee = resizeArray( _Fee, _RepeatCount );
      _FeeType = resizeArray( _FeeType, _RepeatCount );
      _BELFee = resizeArray( _BELFee, _RepeatCount );
      _Frequency = resizeArray( _Frequency, _RepeatCount );
      _DayOfWeek = resizeArray( _DayOfWeek, _RepeatCount );
      _EndOfMonth = resizeArray( _EndOfMonth, _RepeatCount );
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
      _LastProcDate = resizeArray( _LastProcDate, _RepeatCount );
      _EffectiveDate = resizeArray( _EffectiveDate, _RepeatCount );
      _StopDate = resizeArray( _StopDate, _RepeatCount );
      _BatchUser = resizeArray( _BatchUser, _RepeatCount );
      _Batch = resizeArray( _Batch, _RepeatCount );
      _BatchTrace = resizeArray( _BatchTrace, _RepeatCount );
      _BatchDate = resizeArray( _BatchDate, _RepeatCount );
      _TransferType = resizeArray( _TransferType, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _Username = resizeArray( _Username, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _AmountTypeDesc = resizeArray( _AmountTypeDesc, _RepeatCount );
      _FeeTypeDesc = resizeArray( _FeeTypeDesc, _RepeatCount );
      _FrequencyDesc = resizeArray( _FrequencyDesc, _RepeatCount );
      _TransferTypeDesc = resizeArray( _TransferTypeDesc, _RepeatCount );
      _RecurDetlVer = resizeArray( _RecurDetlVer, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _AutoTrfId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _FundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundToCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClassToCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AccountTo[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Amount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AmountType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Fee[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FeeType[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _BELFee[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _Frequency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DayOfWeek[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _EndOfMonth[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
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
         _LastProcDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _StopDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _BatchUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Batch[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BatchTrace[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _BatchDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _TransferType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _Username[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AmountTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FeeTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FrequencyDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TransferTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RecurDetlVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
      }
      

   }

}
      
