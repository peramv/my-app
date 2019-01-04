
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Mgt Fee & Mgt Fee Rebate Accrual Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/MgtFeeAccrualInq.doc">MgtFeeAccrualInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class MgtFeeAccrualInqView extends IFastView implements Serializable
{

   /**
    * Accumulated Mgmt Fee member variable.
    */
   private String _RunTotal = null;
   
   private int _RepeatCount = 0;
   
   /**
    * Record Type member array.
    */
   private String[] _RecType = null;
   
   /**
    * Fund in response member array.
    */
   private String[] _rxFundCode = null;
   
   /**
    * Class in response member array.
    */
   private String[] _rxClassCode = null;
   
   /**
    * Reporting date for 'D' record, Start Date for 'S' record member array.
    */
   private Date[] _AsOfDate = null;
   
   /**
    * Eligible units for 'D' record, 0 for 'S' record member array.
    */
   private String[] _EligUnits = null;
   
   /**
    * Mgt Fee/ Rebate rate for 'D' record, 0 for 'S' record member array.
    */
   private String[] _Rate = null;
   
   /**
    * Mgt Fee / Rebate accrued for particular day in 'D' record or total Mgt Fee / Rebate for Fund/Class in 'S' record member array.
    */
   private String[] _Amount = null;
   
   /**
    * Mgt Fee/ Rebate Paid on a particular day in 'D' record or total Mgt Fee/ Rebate for Fund/Class in 'S' record member array.
    */
   private String[] _AmtPaid = null;
   
   /**
    * Accumulated Total Value member array.
    */
   private String[] _AccumTotal = null;
   
   /**
    * GST amount accrued per day ('D' record) or total GST accrued for Fund/Class ('S' record) member array.
    */
   private String[] _GSTAmt = null;
   
   /**
    * Non-Resident Tax amount accrued per day ('D' record) or total GST accrued for Fund/Class ('S' record) member array.
    */
   private String[] _NRTaxAmt = null;
   
   /**
    * Other Taxes member array.
    */
   private String[] _OtherTaxAmt = null;
   
   /**
    * Paid Include manual transaction , system generated transaction member array.
    */
   private Integer[] _PaidInclude = null;
   
   /**
    * GST Paid member array.
    */
   private String[] _GSTPaid = null;
   
   /**
    * GST outstanding member array.
    */
   private String[] _GSToutstanding = null;
   
   /**
    * NR tax  Paid member array.
    */
   private String[] _NRPaid = null;
   
   /**
    * NR tax outstanding member array.
    */
   private String[] _NRoutstanding = null;
   

   /**
    * Constructs the MgtFeeAccrualInqView object.
    * 
    */
   public MgtFeeAccrualInqView()
   {
      super ( new MgtFeeAccrualInqRequest() );
   }

   /**
    * Constructs the MgtFeeAccrualInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public MgtFeeAccrualInqView( String hostEncoding )
   {
      super ( new MgtFeeAccrualInqRequest( hostEncoding ) );
   }

   /**
    * Gets the MgtFeeAccrualInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The MgtFeeAccrualInqRequest object.
    */
   public final MgtFeeAccrualInqRequest getRequest()
   {
      return (MgtFeeAccrualInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Accumulated Mgmt Fee field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Accumulated Mgmt Fee or null.
    */
   public final String getRunTotal()
   {
      return _RunTotal;
   }
	
   /**
    * Gets the Accumulated Mgmt Fee field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Accumulated Mgmt Fee or the specified default value.
    */
   public final String getRunTotal( String defaultValue )
   {
      return _RunTotal == null ? defaultValue : _RunTotal;
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
    * Gets the Fund in response field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund in response or null.
    */
   public final String getrxFundCode( int index )
   {
      return _rxFundCode[index];
   }
    
   /**
    * Gets the Fund in response field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund in response or the specified default value.
    */
   public final String getrxFundCode( int index, String defaultValue )
   {
      return _rxFundCode[index] == null ? defaultValue : _rxFundCode[index];
   }
    
   /**
    * Gets the array of Fund in response fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund in response values.
    */
   public final String[] getrxFundCodeArray()
   {
      return _rxFundCode;
   }
    
   /**
    * Gets the Class in response field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Class in response or null.
    */
   public final String getrxClassCode( int index )
   {
      return _rxClassCode[index];
   }
    
   /**
    * Gets the Class in response field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class in response or the specified default value.
    */
   public final String getrxClassCode( int index, String defaultValue )
   {
      return _rxClassCode[index] == null ? defaultValue : _rxClassCode[index];
   }
    
   /**
    * Gets the array of Class in response fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Class in response values.
    */
   public final String[] getrxClassCodeArray()
   {
      return _rxClassCode;
   }
    
   /**
    * Gets the Reporting date for 'D' record, Start Date for 'S' record field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reporting date for 'D' record, Start Date for 'S' record or null.
    */
   public final Date getAsOfDate( int index )
   {
      return _AsOfDate[index];
   }
    
   /**
    * Gets the Reporting date for 'D' record, Start Date for 'S' record field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reporting date for 'D' record, Start Date for 'S' record or the specified default value.
    */
   public final Date getAsOfDate( int index, Date defaultValue )
   {
      return _AsOfDate[index] == null ? defaultValue : _AsOfDate[index];
   }
    
   /**
    * Gets the array of Reporting date for 'D' record, Start Date for 'S' record fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reporting date for 'D' record, Start Date for 'S' record values.
    */
   public final Date[] getAsOfDateArray()
   {
      return _AsOfDate;
   }
    
   /**
    * Gets the Eligible units for 'D' record, 0 for 'S' record field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Eligible units for 'D' record, 0 for 'S' record or null.
    */
   public final String getEligUnits( int index )
   {
      return _EligUnits[index];
   }
    
   /**
    * Gets the Eligible units for 'D' record, 0 for 'S' record field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Eligible units for 'D' record, 0 for 'S' record or the specified default value.
    */
   public final String getEligUnits( int index, String defaultValue )
   {
      return _EligUnits[index] == null ? defaultValue : _EligUnits[index];
   }
    
   /**
    * Gets the array of Eligible units for 'D' record, 0 for 'S' record fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Eligible units for 'D' record, 0 for 'S' record values.
    */
   public final String[] getEligUnitsArray()
   {
      return _EligUnits;
   }
    
   /**
    * Gets the Mgt Fee/ Rebate rate for 'D' record, 0 for 'S' record field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Mgt Fee/ Rebate rate for 'D' record, 0 for 'S' record or null.
    */
   public final String getRate( int index )
   {
      return _Rate[index];
   }
    
   /**
    * Gets the Mgt Fee/ Rebate rate for 'D' record, 0 for 'S' record field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Mgt Fee/ Rebate rate for 'D' record, 0 for 'S' record or the specified default value.
    */
   public final String getRate( int index, String defaultValue )
   {
      return _Rate[index] == null ? defaultValue : _Rate[index];
   }
    
   /**
    * Gets the array of Mgt Fee/ Rebate rate for 'D' record, 0 for 'S' record fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Mgt Fee/ Rebate rate for 'D' record, 0 for 'S' record values.
    */
   public final String[] getRateArray()
   {
      return _Rate;
   }
    
   /**
    * Gets the Mgt Fee / Rebate accrued for particular day in 'D' record or total Mgt Fee / Rebate for Fund/Class in 'S' record field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Mgt Fee / Rebate accrued for particular day in 'D' record or total Mgt Fee / Rebate for Fund/Class in 'S' record or null.
    */
   public final String getAmount( int index )
   {
      return _Amount[index];
   }
    
   /**
    * Gets the Mgt Fee / Rebate accrued for particular day in 'D' record or total Mgt Fee / Rebate for Fund/Class in 'S' record field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Mgt Fee / Rebate accrued for particular day in 'D' record or total Mgt Fee / Rebate for Fund/Class in 'S' record or the specified default value.
    */
   public final String getAmount( int index, String defaultValue )
   {
      return _Amount[index] == null ? defaultValue : _Amount[index];
   }
    
   /**
    * Gets the array of Mgt Fee / Rebate accrued for particular day in 'D' record or total Mgt Fee / Rebate for Fund/Class in 'S' record fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Mgt Fee / Rebate accrued for particular day in 'D' record or total Mgt Fee / Rebate for Fund/Class in 'S' record values.
    */
   public final String[] getAmountArray()
   {
      return _Amount;
   }
    
   /**
    * Gets the Mgt Fee/ Rebate Paid on a particular day in 'D' record or total Mgt Fee/ Rebate for Fund/Class in 'S' record field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Mgt Fee/ Rebate Paid on a particular day in 'D' record or total Mgt Fee/ Rebate for Fund/Class in 'S' record or null.
    */
   public final String getAmtPaid( int index )
   {
      return _AmtPaid[index];
   }
    
   /**
    * Gets the Mgt Fee/ Rebate Paid on a particular day in 'D' record or total Mgt Fee/ Rebate for Fund/Class in 'S' record field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Mgt Fee/ Rebate Paid on a particular day in 'D' record or total Mgt Fee/ Rebate for Fund/Class in 'S' record or the specified default value.
    */
   public final String getAmtPaid( int index, String defaultValue )
   {
      return _AmtPaid[index] == null ? defaultValue : _AmtPaid[index];
   }
    
   /**
    * Gets the array of Mgt Fee/ Rebate Paid on a particular day in 'D' record or total Mgt Fee/ Rebate for Fund/Class in 'S' record fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Mgt Fee/ Rebate Paid on a particular day in 'D' record or total Mgt Fee/ Rebate for Fund/Class in 'S' record values.
    */
   public final String[] getAmtPaidArray()
   {
      return _AmtPaid;
   }
    
   /**
    * Gets the Accumulated Total Value field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Accumulated Total Value or null.
    */
   public final String getAccumTotal( int index )
   {
      return _AccumTotal[index];
   }
    
   /**
    * Gets the Accumulated Total Value field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Accumulated Total Value or the specified default value.
    */
   public final String getAccumTotal( int index, String defaultValue )
   {
      return _AccumTotal[index] == null ? defaultValue : _AccumTotal[index];
   }
    
   /**
    * Gets the array of Accumulated Total Value fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Accumulated Total Value values.
    */
   public final String[] getAccumTotalArray()
   {
      return _AccumTotal;
   }
    
   /**
    * Gets the GST amount accrued per day ('D' record) or total GST accrued for Fund/Class ('S' record) field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the GST amount accrued per day ('D' record) or total GST accrued for Fund/Class ('S' record) or null.
    */
   public final String getGSTAmt( int index )
   {
      return _GSTAmt[index];
   }
    
   /**
    * Gets the GST amount accrued per day ('D' record) or total GST accrued for Fund/Class ('S' record) field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the GST amount accrued per day ('D' record) or total GST accrued for Fund/Class ('S' record) or the specified default value.
    */
   public final String getGSTAmt( int index, String defaultValue )
   {
      return _GSTAmt[index] == null ? defaultValue : _GSTAmt[index];
   }
    
   /**
    * Gets the array of GST amount accrued per day ('D' record) or total GST accrued for Fund/Class ('S' record) fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of GST amount accrued per day ('D' record) or total GST accrued for Fund/Class ('S' record) values.
    */
   public final String[] getGSTAmtArray()
   {
      return _GSTAmt;
   }
    
   /**
    * Gets the Non-Resident Tax amount accrued per day ('D' record) or total GST accrued for Fund/Class ('S' record) field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Non-Resident Tax amount accrued per day ('D' record) or total GST accrued for Fund/Class ('S' record) or null.
    */
   public final String getNRTaxAmt( int index )
   {
      return _NRTaxAmt[index];
   }
    
   /**
    * Gets the Non-Resident Tax amount accrued per day ('D' record) or total GST accrued for Fund/Class ('S' record) field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Non-Resident Tax amount accrued per day ('D' record) or total GST accrued for Fund/Class ('S' record) or the specified default value.
    */
   public final String getNRTaxAmt( int index, String defaultValue )
   {
      return _NRTaxAmt[index] == null ? defaultValue : _NRTaxAmt[index];
   }
    
   /**
    * Gets the array of Non-Resident Tax amount accrued per day ('D' record) or total GST accrued for Fund/Class ('S' record) fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Non-Resident Tax amount accrued per day ('D' record) or total GST accrued for Fund/Class ('S' record) values.
    */
   public final String[] getNRTaxAmtArray()
   {
      return _NRTaxAmt;
   }
    
   /**
    * Gets the Other Taxes field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Other Taxes or null.
    */
   public final String getOtherTaxAmt( int index )
   {
      return _OtherTaxAmt[index];
   }
    
   /**
    * Gets the Other Taxes field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Other Taxes or the specified default value.
    */
   public final String getOtherTaxAmt( int index, String defaultValue )
   {
      return _OtherTaxAmt[index] == null ? defaultValue : _OtherTaxAmt[index];
   }
    
   /**
    * Gets the array of Other Taxes fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Other Taxes values.
    */
   public final String[] getOtherTaxAmtArray()
   {
      return _OtherTaxAmt;
   }
    
   /**
    * Gets the Paid Include manual transaction , system generated transaction field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Paid Include manual transaction , system generated transaction or null.
    */
   public final Integer getPaidInclude( int index )
   {
      return _PaidInclude[index];
   }
    
   /**
    * Gets the Paid Include manual transaction , system generated transaction field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Paid Include manual transaction , system generated transaction or the specified default value.
    */
   public final int getPaidInclude( int index, int defaultValue )
   {
      return _PaidInclude[index] == null ? defaultValue : _PaidInclude[index].intValue();
   }
    
   /**
    * Gets the array of Paid Include manual transaction , system generated transaction fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Paid Include manual transaction , system generated transaction values.
    */
   public final Integer[] getPaidIncludeArray()
   {
      return _PaidInclude;
   }
    
   /**
    * Gets the GST Paid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the GST Paid or null.
    */
   public final String getGSTPaid( int index )
   {
      return _GSTPaid[index];
   }
    
   /**
    * Gets the GST Paid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the GST Paid or the specified default value.
    */
   public final String getGSTPaid( int index, String defaultValue )
   {
      return _GSTPaid[index] == null ? defaultValue : _GSTPaid[index];
   }
    
   /**
    * Gets the array of GST Paid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of GST Paid values.
    */
   public final String[] getGSTPaidArray()
   {
      return _GSTPaid;
   }
    
   /**
    * Gets the GST outstanding field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the GST outstanding or null.
    */
   public final String getGSToutstanding( int index )
   {
      return _GSToutstanding[index];
   }
    
   /**
    * Gets the GST outstanding field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the GST outstanding or the specified default value.
    */
   public final String getGSToutstanding( int index, String defaultValue )
   {
      return _GSToutstanding[index] == null ? defaultValue : _GSToutstanding[index];
   }
    
   /**
    * Gets the array of GST outstanding fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of GST outstanding values.
    */
   public final String[] getGSToutstandingArray()
   {
      return _GSToutstanding;
   }
    
   /**
    * Gets the NR tax  Paid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the NR tax  Paid or null.
    */
   public final String getNRPaid( int index )
   {
      return _NRPaid[index];
   }
    
   /**
    * Gets the NR tax  Paid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the NR tax  Paid or the specified default value.
    */
   public final String getNRPaid( int index, String defaultValue )
   {
      return _NRPaid[index] == null ? defaultValue : _NRPaid[index];
   }
    
   /**
    * Gets the array of NR tax  Paid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of NR tax  Paid values.
    */
   public final String[] getNRPaidArray()
   {
      return _NRPaid;
   }
    
   /**
    * Gets the NR tax outstanding field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the NR tax outstanding or null.
    */
   public final String getNRoutstanding( int index )
   {
      return _NRoutstanding[index];
   }
    
   /**
    * Gets the NR tax outstanding field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the NR tax outstanding or the specified default value.
    */
   public final String getNRoutstanding( int index, String defaultValue )
   {
      return _NRoutstanding[index] == null ? defaultValue : _NRoutstanding[index];
   }
    
   /**
    * Gets the array of NR tax outstanding fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of NR tax outstanding values.
    */
   public final String[] getNRoutstandingArray()
   {
      return _NRoutstanding;
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
      _RunTotal = responseBuffer.decodeString(responseBuffer.getNextField());
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _RecType = resizeArray( _RecType, _RepeatCount );
      _rxFundCode = resizeArray( _rxFundCode, _RepeatCount );
      _rxClassCode = resizeArray( _rxClassCode, _RepeatCount );
      _AsOfDate = resizeArray( _AsOfDate, _RepeatCount );
      _EligUnits = resizeArray( _EligUnits, _RepeatCount );
      _Rate = resizeArray( _Rate, _RepeatCount );
      _Amount = resizeArray( _Amount, _RepeatCount );
      _AmtPaid = resizeArray( _AmtPaid, _RepeatCount );
      _AccumTotal = resizeArray( _AccumTotal, _RepeatCount );
      _GSTAmt = resizeArray( _GSTAmt, _RepeatCount );
      _NRTaxAmt = resizeArray( _NRTaxAmt, _RepeatCount );
      _OtherTaxAmt = resizeArray( _OtherTaxAmt, _RepeatCount );
      _PaidInclude = resizeArray( _PaidInclude, _RepeatCount );
      _GSTPaid = resizeArray( _GSTPaid, _RepeatCount );
      _GSToutstanding = resizeArray( _GSToutstanding, _RepeatCount );
      _NRPaid = resizeArray( _NRPaid, _RepeatCount );
      _NRoutstanding = resizeArray( _NRoutstanding, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _RecType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxFundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AsOfDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _EligUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Rate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Amount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AmtPaid[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AccumTotal[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GSTAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _NRTaxAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _OtherTaxAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PaidInclude[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _GSTPaid[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GSToutstanding[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _NRPaid[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _NRoutstanding[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
