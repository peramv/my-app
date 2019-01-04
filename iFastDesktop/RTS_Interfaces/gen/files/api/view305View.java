
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Fee Model Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/view305.doc">view305.doc</A>.
 * 
 * @author RTS Generated
 */
public class view305View extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Fee Model Code member array.
    */
   private String[] _rxFeeModelCode = null;
   
   /**
    * Recid of fee model member array.
    */
   private Integer[] _FeeModelRecid = null;
   
   /**
    * Fee model description member array.
    */
   private String[] _rxFeeModelDesc = null;
   
   /**
    * Start date of fee model member array.
    */
   private Date[] _StartDate = null;
   
   /**
    * Stop date of fee model member array.
    */
   private Date[] _StopDate = null;
   
   /**
    * Process date of fee model member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * User who created the fee model member array.
    */
   private String[] _UserName = null;
   
   /**
    * The fee model modification date member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * The user modified the fee model member array.
    */
   private String[] _ModUser = null;
   
   /**
    * Version of the fee model record member array.
    */
   private Integer[] _FeeModelVer = null;
   
   /**
    * Fee Model Code In Use member array.
    */
   private Boolean[] _CodeInUse = null;
   
   /**
    * Fee Model Type member array.
    */
   private String[] _FeeModelType = null;
   
   /**
    * Holding Company Code member array.
    */
   private String[] _rxHoldCoCode = null;
   
   /**
    * Holding Company Name member array.
    */
   private String[] _rxHoldCoName = null;
   
   /**
    * Good /Bad record member array.
    */
   private Boolean[] _GBCD = null;
   
   /**
    * Calculation Currency member array.
    */
   private String[] _CalCurrency = null;
   
   /**
    * Calculation Rate Type member array.
    */
   private String[] _CalRateType = null;
   
   /**
    * Model Aggregation Method member array.
    */
   private String[] _ModelAggrMethod = null;
   
   /**
    * Eligible Fund By member array.
    */
   private String[] _FundGrpType = null;
   
   /**
    * Fee Model Option member array.
    */
   private String[] _Program = null;
   
   /**
    * Schedule member array.
    */
   private Integer[] _ScheduleSetup = null;
   
   /**
    * ShrAcctDeff member array.
    */
   private Date[] _ShrAcctDeff = null;
   
   /**
    * Fund Group member array.
    */
   private String[] _FundGroup = null;
   
   /**
    * Fund Sponsor recid member array.
    */
   private Integer[] _FundSponsorRID = null;
   
   /**
    * Fee Aggregation recid member array.
    */
   private Integer[] _FeeAggregationRID = null;
   
   /**
    * Fund Sponsor Fee Model Version member array.
    */
   private Integer[] _FundSponsorVer = null;
   
   /**
    * Flag that indicates if ShrAcctFeeConfig exist member array.
    */
   private Boolean[] _ShrAcctFeeExist = null;
   
   /**
    * FeeParm Exist flag member array.
    */
   private Boolean[] _FeeParmExist = null;
   
   /**
    * Last Process Date member array.
    */
   private Date[] _LastProcDate = null;
   
   /**
    * FeeOnFMO member array.
    */
   private Integer[] _FeeOnFMO = null;
   

   /**
    * Constructs the view305View object.
    * 
    */
   public view305View()
   {
      super ( new view305Request() );
   }

   /**
    * Constructs the view305View object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public view305View( String hostEncoding )
   {
      super ( new view305Request( hostEncoding ) );
   }

   /**
    * Gets the view305Request object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The view305Request object.
    */
   public final view305Request getRequest()
   {
      return (view305Request)getIFastRequest();
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
    * Gets the Fee Model Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fee Model Code or null.
    */
   public final String getrxFeeModelCode( int index )
   {
      return _rxFeeModelCode[index];
   }
    
   /**
    * Gets the Fee Model Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee Model Code or the specified default value.
    */
   public final String getrxFeeModelCode( int index, String defaultValue )
   {
      return _rxFeeModelCode[index] == null ? defaultValue : _rxFeeModelCode[index];
   }
    
   /**
    * Gets the array of Fee Model Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee Model Code values.
    */
   public final String[] getrxFeeModelCodeArray()
   {
      return _rxFeeModelCode;
   }
    
   /**
    * Gets the Recid of fee model field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Recid of fee model or null.
    */
   public final Integer getFeeModelRecid( int index )
   {
      return _FeeModelRecid[index];
   }
    
   /**
    * Gets the Recid of fee model field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Recid of fee model or the specified default value.
    */
   public final int getFeeModelRecid( int index, int defaultValue )
   {
      return _FeeModelRecid[index] == null ? defaultValue : _FeeModelRecid[index].intValue();
   }
    
   /**
    * Gets the array of Recid of fee model fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Recid of fee model values.
    */
   public final Integer[] getFeeModelRecidArray()
   {
      return _FeeModelRecid;
   }
    
   /**
    * Gets the Fee model description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fee model description or null.
    */
   public final String getrxFeeModelDesc( int index )
   {
      return _rxFeeModelDesc[index];
   }
    
   /**
    * Gets the Fee model description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee model description or the specified default value.
    */
   public final String getrxFeeModelDesc( int index, String defaultValue )
   {
      return _rxFeeModelDesc[index] == null ? defaultValue : _rxFeeModelDesc[index];
   }
    
   /**
    * Gets the array of Fee model description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee model description values.
    */
   public final String[] getrxFeeModelDescArray()
   {
      return _rxFeeModelDesc;
   }
    
   /**
    * Gets the Start date of fee model field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Start date of fee model or null.
    */
   public final Date getStartDate( int index )
   {
      return _StartDate[index];
   }
    
   /**
    * Gets the Start date of fee model field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Start date of fee model or the specified default value.
    */
   public final Date getStartDate( int index, Date defaultValue )
   {
      return _StartDate[index] == null ? defaultValue : _StartDate[index];
   }
    
   /**
    * Gets the array of Start date of fee model fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Start date of fee model values.
    */
   public final Date[] getStartDateArray()
   {
      return _StartDate;
   }
    
   /**
    * Gets the Stop date of fee model field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stop date of fee model or null.
    */
   public final Date getStopDate( int index )
   {
      return _StopDate[index];
   }
    
   /**
    * Gets the Stop date of fee model field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop date of fee model or the specified default value.
    */
   public final Date getStopDate( int index, Date defaultValue )
   {
      return _StopDate[index] == null ? defaultValue : _StopDate[index];
   }
    
   /**
    * Gets the array of Stop date of fee model fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stop date of fee model values.
    */
   public final Date[] getStopDateArray()
   {
      return _StopDate;
   }
    
   /**
    * Gets the Process date of fee model field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Process date of fee model or null.
    */
   public final Date getProcessDate( int index )
   {
      return _ProcessDate[index];
   }
    
   /**
    * Gets the Process date of fee model field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Process date of fee model or the specified default value.
    */
   public final Date getProcessDate( int index, Date defaultValue )
   {
      return _ProcessDate[index] == null ? defaultValue : _ProcessDate[index];
   }
    
   /**
    * Gets the array of Process date of fee model fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Process date of fee model values.
    */
   public final Date[] getProcessDateArray()
   {
      return _ProcessDate;
   }
    
   /**
    * Gets the User who created the fee model field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the User who created the fee model or null.
    */
   public final String getUserName( int index )
   {
      return _UserName[index];
   }
    
   /**
    * Gets the User who created the fee model field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the User who created the fee model or the specified default value.
    */
   public final String getUserName( int index, String defaultValue )
   {
      return _UserName[index] == null ? defaultValue : _UserName[index];
   }
    
   /**
    * Gets the array of User who created the fee model fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of User who created the fee model values.
    */
   public final String[] getUserNameArray()
   {
      return _UserName;
   }
    
   /**
    * Gets the The fee model modification date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the The fee model modification date or null.
    */
   public final Date getModDate( int index )
   {
      return _ModDate[index];
   }
    
   /**
    * Gets the The fee model modification date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the The fee model modification date or the specified default value.
    */
   public final Date getModDate( int index, Date defaultValue )
   {
      return _ModDate[index] == null ? defaultValue : _ModDate[index];
   }
    
   /**
    * Gets the array of The fee model modification date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of The fee model modification date values.
    */
   public final Date[] getModDateArray()
   {
      return _ModDate;
   }
    
   /**
    * Gets the The user modified the fee model field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the The user modified the fee model or null.
    */
   public final String getModUser( int index )
   {
      return _ModUser[index];
   }
    
   /**
    * Gets the The user modified the fee model field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the The user modified the fee model or the specified default value.
    */
   public final String getModUser( int index, String defaultValue )
   {
      return _ModUser[index] == null ? defaultValue : _ModUser[index];
   }
    
   /**
    * Gets the array of The user modified the fee model fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of The user modified the fee model values.
    */
   public final String[] getModUserArray()
   {
      return _ModUser;
   }
    
   /**
    * Gets the Version of the fee model record field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Version of the fee model record or null.
    */
   public final Integer getFeeModelVer( int index )
   {
      return _FeeModelVer[index];
   }
    
   /**
    * Gets the Version of the fee model record field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Version of the fee model record or the specified default value.
    */
   public final int getFeeModelVer( int index, int defaultValue )
   {
      return _FeeModelVer[index] == null ? defaultValue : _FeeModelVer[index].intValue();
   }
    
   /**
    * Gets the array of Version of the fee model record fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Version of the fee model record values.
    */
   public final Integer[] getFeeModelVerArray()
   {
      return _FeeModelVer;
   }
    
   /**
    * Gets the Fee Model Code In Use field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fee Model Code In Use or null.
    */
   public final Boolean getCodeInUse( int index )
   {
      return _CodeInUse[index];
   }
    
   /**
    * Gets the Fee Model Code In Use field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee Model Code In Use or the specified default value.
    */
   public final boolean getCodeInUse( int index, boolean defaultValue )
   {
      return _CodeInUse[index] == null ? defaultValue : _CodeInUse[index].booleanValue();
   }
    
   /**
    * Gets the array of Fee Model Code In Use fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee Model Code In Use values.
    */
   public final Boolean[] getCodeInUseArray()
   {
      return _CodeInUse;
   }
    
   /**
    * Gets the Fee Model Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fee Model Type or null.
    */
   public final String getFeeModelType( int index )
   {
      return _FeeModelType[index];
   }
    
   /**
    * Gets the Fee Model Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee Model Type or the specified default value.
    */
   public final String getFeeModelType( int index, String defaultValue )
   {
      return _FeeModelType[index] == null ? defaultValue : _FeeModelType[index];
   }
    
   /**
    * Gets the array of Fee Model Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee Model Type values.
    */
   public final String[] getFeeModelTypeArray()
   {
      return _FeeModelType;
   }
    
   /**
    * Gets the Holding Company Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Holding Company Code or null.
    */
   public final String getrxHoldCoCode( int index )
   {
      return _rxHoldCoCode[index];
   }
    
   /**
    * Gets the Holding Company Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Holding Company Code or the specified default value.
    */
   public final String getrxHoldCoCode( int index, String defaultValue )
   {
      return _rxHoldCoCode[index] == null ? defaultValue : _rxHoldCoCode[index];
   }
    
   /**
    * Gets the array of Holding Company Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Holding Company Code values.
    */
   public final String[] getrxHoldCoCodeArray()
   {
      return _rxHoldCoCode;
   }
    
   /**
    * Gets the Holding Company Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Holding Company Name or null.
    */
   public final String getrxHoldCoName( int index )
   {
      return _rxHoldCoName[index];
   }
    
   /**
    * Gets the Holding Company Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Holding Company Name or the specified default value.
    */
   public final String getrxHoldCoName( int index, String defaultValue )
   {
      return _rxHoldCoName[index] == null ? defaultValue : _rxHoldCoName[index];
   }
    
   /**
    * Gets the array of Holding Company Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Holding Company Name values.
    */
   public final String[] getrxHoldCoNameArray()
   {
      return _rxHoldCoName;
   }
    
   /**
    * Gets the Good /Bad record field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Good /Bad record or null.
    */
   public final Boolean getGBCD( int index )
   {
      return _GBCD[index];
   }
    
   /**
    * Gets the Good /Bad record field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Good /Bad record or the specified default value.
    */
   public final boolean getGBCD( int index, boolean defaultValue )
   {
      return _GBCD[index] == null ? defaultValue : _GBCD[index].booleanValue();
   }
    
   /**
    * Gets the array of Good /Bad record fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Good /Bad record values.
    */
   public final Boolean[] getGBCDArray()
   {
      return _GBCD;
   }
    
   /**
    * Gets the Calculation Currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Calculation Currency or null.
    */
   public final String getCalCurrency( int index )
   {
      return _CalCurrency[index];
   }
    
   /**
    * Gets the Calculation Currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Calculation Currency or the specified default value.
    */
   public final String getCalCurrency( int index, String defaultValue )
   {
      return _CalCurrency[index] == null ? defaultValue : _CalCurrency[index];
   }
    
   /**
    * Gets the array of Calculation Currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Calculation Currency values.
    */
   public final String[] getCalCurrencyArray()
   {
      return _CalCurrency;
   }
    
   /**
    * Gets the Calculation Rate Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Calculation Rate Type or null.
    */
   public final String getCalRateType( int index )
   {
      return _CalRateType[index];
   }
    
   /**
    * Gets the Calculation Rate Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Calculation Rate Type or the specified default value.
    */
   public final String getCalRateType( int index, String defaultValue )
   {
      return _CalRateType[index] == null ? defaultValue : _CalRateType[index];
   }
    
   /**
    * Gets the array of Calculation Rate Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Calculation Rate Type values.
    */
   public final String[] getCalRateTypeArray()
   {
      return _CalRateType;
   }
    
   /**
    * Gets the Model Aggregation Method field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Model Aggregation Method or null.
    */
   public final String getModelAggrMethod( int index )
   {
      return _ModelAggrMethod[index];
   }
    
   /**
    * Gets the Model Aggregation Method field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Model Aggregation Method or the specified default value.
    */
   public final String getModelAggrMethod( int index, String defaultValue )
   {
      return _ModelAggrMethod[index] == null ? defaultValue : _ModelAggrMethod[index];
   }
    
   /**
    * Gets the array of Model Aggregation Method fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Model Aggregation Method values.
    */
   public final String[] getModelAggrMethodArray()
   {
      return _ModelAggrMethod;
   }
    
   /**
    * Gets the Eligible Fund By field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Eligible Fund By or null.
    */
   public final String getFundGrpType( int index )
   {
      return _FundGrpType[index];
   }
    
   /**
    * Gets the Eligible Fund By field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Eligible Fund By or the specified default value.
    */
   public final String getFundGrpType( int index, String defaultValue )
   {
      return _FundGrpType[index] == null ? defaultValue : _FundGrpType[index];
   }
    
   /**
    * Gets the array of Eligible Fund By fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Eligible Fund By values.
    */
   public final String[] getFundGrpTypeArray()
   {
      return _FundGrpType;
   }
    
   /**
    * Gets the Fee Model Option field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fee Model Option or null.
    */
   public final String getProgram( int index )
   {
      return _Program[index];
   }
    
   /**
    * Gets the Fee Model Option field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee Model Option or the specified default value.
    */
   public final String getProgram( int index, String defaultValue )
   {
      return _Program[index] == null ? defaultValue : _Program[index];
   }
    
   /**
    * Gets the array of Fee Model Option fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee Model Option values.
    */
   public final String[] getProgramArray()
   {
      return _Program;
   }
    
   /**
    * Gets the Schedule field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Schedule or null.
    */
   public final Integer getScheduleSetup( int index )
   {
      return _ScheduleSetup[index];
   }
    
   /**
    * Gets the Schedule field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Schedule or the specified default value.
    */
   public final int getScheduleSetup( int index, int defaultValue )
   {
      return _ScheduleSetup[index] == null ? defaultValue : _ScheduleSetup[index].intValue();
   }
    
   /**
    * Gets the array of Schedule fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Schedule values.
    */
   public final Integer[] getScheduleSetupArray()
   {
      return _ScheduleSetup;
   }
    
   /**
    * Gets the ShrAcctDeff field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ShrAcctDeff or null.
    */
   public final Date getShrAcctDeff( int index )
   {
      return _ShrAcctDeff[index];
   }
    
   /**
    * Gets the ShrAcctDeff field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ShrAcctDeff or the specified default value.
    */
   public final Date getShrAcctDeff( int index, Date defaultValue )
   {
      return _ShrAcctDeff[index] == null ? defaultValue : _ShrAcctDeff[index];
   }
    
   /**
    * Gets the array of ShrAcctDeff fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ShrAcctDeff values.
    */
   public final Date[] getShrAcctDeffArray()
   {
      return _ShrAcctDeff;
   }
    
   /**
    * Gets the Fund Group field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Group or null.
    */
   public final String getFundGroup( int index )
   {
      return _FundGroup[index];
   }
    
   /**
    * Gets the Fund Group field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Group or the specified default value.
    */
   public final String getFundGroup( int index, String defaultValue )
   {
      return _FundGroup[index] == null ? defaultValue : _FundGroup[index];
   }
    
   /**
    * Gets the array of Fund Group fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Group values.
    */
   public final String[] getFundGroupArray()
   {
      return _FundGroup;
   }
    
   /**
    * Gets the Fund Sponsor recid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Sponsor recid or null.
    */
   public final Integer getFundSponsorRID( int index )
   {
      return _FundSponsorRID[index];
   }
    
   /**
    * Gets the Fund Sponsor recid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Sponsor recid or the specified default value.
    */
   public final int getFundSponsorRID( int index, int defaultValue )
   {
      return _FundSponsorRID[index] == null ? defaultValue : _FundSponsorRID[index].intValue();
   }
    
   /**
    * Gets the array of Fund Sponsor recid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Sponsor recid values.
    */
   public final Integer[] getFundSponsorRIDArray()
   {
      return _FundSponsorRID;
   }
    
   /**
    * Gets the Fee Aggregation recid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fee Aggregation recid or null.
    */
   public final Integer getFeeAggregationRID( int index )
   {
      return _FeeAggregationRID[index];
   }
    
   /**
    * Gets the Fee Aggregation recid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee Aggregation recid or the specified default value.
    */
   public final int getFeeAggregationRID( int index, int defaultValue )
   {
      return _FeeAggregationRID[index] == null ? defaultValue : _FeeAggregationRID[index].intValue();
   }
    
   /**
    * Gets the array of Fee Aggregation recid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee Aggregation recid values.
    */
   public final Integer[] getFeeAggregationRIDArray()
   {
      return _FeeAggregationRID;
   }
    
   /**
    * Gets the Fund Sponsor Fee Model Version field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Sponsor Fee Model Version or null.
    */
   public final Integer getFundSponsorVer( int index )
   {
      return _FundSponsorVer[index];
   }
    
   /**
    * Gets the Fund Sponsor Fee Model Version field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Sponsor Fee Model Version or the specified default value.
    */
   public final int getFundSponsorVer( int index, int defaultValue )
   {
      return _FundSponsorVer[index] == null ? defaultValue : _FundSponsorVer[index].intValue();
   }
    
   /**
    * Gets the array of Fund Sponsor Fee Model Version fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Sponsor Fee Model Version values.
    */
   public final Integer[] getFundSponsorVerArray()
   {
      return _FundSponsorVer;
   }
    
   /**
    * Gets the Flag that indicates if ShrAcctFeeConfig exist field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag that indicates if ShrAcctFeeConfig exist or null.
    */
   public final Boolean getShrAcctFeeExist( int index )
   {
      return _ShrAcctFeeExist[index];
   }
    
   /**
    * Gets the Flag that indicates if ShrAcctFeeConfig exist field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag that indicates if ShrAcctFeeConfig exist or the specified default value.
    */
   public final boolean getShrAcctFeeExist( int index, boolean defaultValue )
   {
      return _ShrAcctFeeExist[index] == null ? defaultValue : _ShrAcctFeeExist[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag that indicates if ShrAcctFeeConfig exist fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag that indicates if ShrAcctFeeConfig exist values.
    */
   public final Boolean[] getShrAcctFeeExistArray()
   {
      return _ShrAcctFeeExist;
   }
    
   /**
    * Gets the FeeParm Exist flag field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FeeParm Exist flag or null.
    */
   public final Boolean getFeeParmExist( int index )
   {
      return _FeeParmExist[index];
   }
    
   /**
    * Gets the FeeParm Exist flag field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FeeParm Exist flag or the specified default value.
    */
   public final boolean getFeeParmExist( int index, boolean defaultValue )
   {
      return _FeeParmExist[index] == null ? defaultValue : _FeeParmExist[index].booleanValue();
   }
    
   /**
    * Gets the array of FeeParm Exist flag fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FeeParm Exist flag values.
    */
   public final Boolean[] getFeeParmExistArray()
   {
      return _FeeParmExist;
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
    * Gets the FeeOnFMO field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FeeOnFMO or null.
    */
   public final Integer getFeeOnFMO( int index )
   {
      return _FeeOnFMO[index];
   }
    
   /**
    * Gets the FeeOnFMO field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FeeOnFMO or the specified default value.
    */
   public final int getFeeOnFMO( int index, int defaultValue )
   {
      return _FeeOnFMO[index] == null ? defaultValue : _FeeOnFMO[index].intValue();
   }
    
   /**
    * Gets the array of FeeOnFMO fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FeeOnFMO values.
    */
   public final Integer[] getFeeOnFMOArray()
   {
      return _FeeOnFMO;
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
      
      _rxFeeModelCode = resizeArray( _rxFeeModelCode, _RepeatCount );
      _FeeModelRecid = resizeArray( _FeeModelRecid, _RepeatCount );
      _rxFeeModelDesc = resizeArray( _rxFeeModelDesc, _RepeatCount );
      _StartDate = resizeArray( _StartDate, _RepeatCount );
      _StopDate = resizeArray( _StopDate, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _UserName = resizeArray( _UserName, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _FeeModelVer = resizeArray( _FeeModelVer, _RepeatCount );
      _CodeInUse = resizeArray( _CodeInUse, _RepeatCount );
      _FeeModelType = resizeArray( _FeeModelType, _RepeatCount );
      _rxHoldCoCode = resizeArray( _rxHoldCoCode, _RepeatCount );
      _rxHoldCoName = resizeArray( _rxHoldCoName, _RepeatCount );
      _GBCD = resizeArray( _GBCD, _RepeatCount );
      _CalCurrency = resizeArray( _CalCurrency, _RepeatCount );
      _CalRateType = resizeArray( _CalRateType, _RepeatCount );
      _ModelAggrMethod = resizeArray( _ModelAggrMethod, _RepeatCount );
      _FundGrpType = resizeArray( _FundGrpType, _RepeatCount );
      _Program = resizeArray( _Program, _RepeatCount );
      _ScheduleSetup = resizeArray( _ScheduleSetup, _RepeatCount );
      _ShrAcctDeff = resizeArray( _ShrAcctDeff, _RepeatCount );
      _FundGroup = resizeArray( _FundGroup, _RepeatCount );
      _FundSponsorRID = resizeArray( _FundSponsorRID, _RepeatCount );
      _FeeAggregationRID = resizeArray( _FeeAggregationRID, _RepeatCount );
      _FundSponsorVer = resizeArray( _FundSponsorVer, _RepeatCount );
      _ShrAcctFeeExist = resizeArray( _ShrAcctFeeExist, _RepeatCount );
      _FeeParmExist = resizeArray( _FeeParmExist, _RepeatCount );
      _LastProcDate = resizeArray( _LastProcDate, _RepeatCount );
      _FeeOnFMO = resizeArray( _FeeOnFMO, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxFeeModelCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FeeModelRecid[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _rxFeeModelDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _StartDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _StopDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _UserName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FeeModelVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _CodeInUse[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FeeModelType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxHoldCoCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxHoldCoName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GBCD[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _CalCurrency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CalRateType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModelAggrMethod[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundGrpType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Program[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ScheduleSetup[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ShrAcctDeff[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _FundGroup[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundSponsorRID[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _FeeAggregationRID[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _FundSponsorVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ShrAcctFeeExist[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FeeParmExist[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _LastProcDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _FeeOnFMO[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
      }
      

   }

}
      
