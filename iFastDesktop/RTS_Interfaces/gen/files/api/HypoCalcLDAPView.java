
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Hypothetical Redemption (LDAP Clients) view.
 * For additional view information see <A HREF="../../../../viewspecs/HypoCalcLDAP.doc">HypoCalcLDAP.doc</A>.
 * 
 * @author RTS Generated
 */
public class HypoCalcLDAPView extends IFastView implements Serializable
{

   /**
    * Update Status member variable.
    */
   private Boolean _UpdateStatus = null;
   
   private int _RepeatCount = 0;
   
   /**
    * Fund Code member array.
    */
   private String[] _rxFundCode = null;
   
   /**
    * Class Code member array.
    */
   private String[] _rxClassCode = null;
   
   /**
    * Baycom member array.
    */
   private String[] _Baycom = null;
   
   /**
    * Fund Currency member array.
    */
   private String[] _FundCurrency = null;
   
   /**
    * Gross Redemption Amount member array.
    */
   private String[] _Amount = null;
   
   /**
    * Gross Redemption Units member array.
    */
   private String[] _Units = null;
   
   /**
    * DSC free amt portion of gross redemption amount member array.
    */
   private String[] _FreeAmt = null;
   
   /**
    * DSC free units portion of gross redemption amount member array.
    */
   private String[] _FreeUnits = null;
   
   /**
    * Portion of gross redemption amount charged with DSC - in amt member array.
    */
   private String[] _FeeApplAmt = null;
   
   /**
    * Portion of gross redemption amount Portion of gross redemption amount charged with DSC - in units member array.
    */
   private String[] _FeeApplUnits = null;
   
   /**
    * DSC fee charged to Fund/ Class member array.
    */
   private String[] _DSCAmt = null;
   
   /**
    * Withholding tax charged to the fund/ class member array.
    */
   private String[] _Tax = null;
   
   /**
    * Other fees charged to fund/ class member array.
    */
   private String[] _Fee = null;
   
   /**
    * Error  Code member array.
    */
   private Integer[] _ErrCode = null;
   
   /**
    * Error Description member array.
    */
   private String[] _ErrDesc = null;
   
   /**
    * Federal Clawback member array.
    */
   private String[] _FedClawback = null;
   
   /**
    * Provincial Clawback member array.
    */
   private String[] _ProvClawback = null;
   
   /**
    * Additional Clawback member array.
    */
   private String[] _AddlProvClawback = null;
   
   /**
    * Federal Tax member array.
    */
   private String[] _FedTax = null;
   
   /**
    * Provincial Tax member array.
    */
   private String[] _ProvTax = null;
   
   /**
    * Percemtage of Fee member array.
    */
   private String[] _FeePrcnt = null;
   
   /**
    * Record Type member array.
    */
   private String[] _RecordType = null;
   
   /**
    * TotCBAmount member array.
    */
   private String[] _TotCBAmount = null;
   

   /**
    * Constructs the HypoCalcLDAPView object.
    * 
    */
   public HypoCalcLDAPView()
   {
      super ( new HypoCalcLDAPRequest() );
   }

   /**
    * Constructs the HypoCalcLDAPView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public HypoCalcLDAPView( String hostEncoding )
   {
      super ( new HypoCalcLDAPRequest( hostEncoding ) );
   }

   /**
    * Gets the HypoCalcLDAPRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The HypoCalcLDAPRequest object.
    */
   public final HypoCalcLDAPRequest getRequest()
   {
      return (HypoCalcLDAPRequest)getIFastRequest();
   }
        
   /**
    * Gets the Update Status field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Update Status or null.
    */
   public final Boolean getUpdateStatus()
   {
      return _UpdateStatus;
   }
	
   /**
    * Gets the Update Status field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Update Status or the specified default value.
    */
   public final boolean getUpdateStatus( boolean defaultValue )
   {
      return _UpdateStatus == null ? defaultValue : _UpdateStatus.booleanValue();
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
   public final String getrxFundCode( int index )
   {
      return _rxFundCode[index];
   }
    
   /**
    * Gets the Fund Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Code or the specified default value.
    */
   public final String getrxFundCode( int index, String defaultValue )
   {
      return _rxFundCode[index] == null ? defaultValue : _rxFundCode[index];
   }
    
   /**
    * Gets the array of Fund Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Code values.
    */
   public final String[] getrxFundCodeArray()
   {
      return _rxFundCode;
   }
    
   /**
    * Gets the Class Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Class Code or null.
    */
   public final String getrxClassCode( int index )
   {
      return _rxClassCode[index];
   }
    
   /**
    * Gets the Class Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class Code or the specified default value.
    */
   public final String getrxClassCode( int index, String defaultValue )
   {
      return _rxClassCode[index] == null ? defaultValue : _rxClassCode[index];
   }
    
   /**
    * Gets the array of Class Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Class Code values.
    */
   public final String[] getrxClassCodeArray()
   {
      return _rxClassCode;
   }
    
   /**
    * Gets the Baycom field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Baycom or null.
    */
   public final String getBaycom( int index )
   {
      return _Baycom[index];
   }
    
   /**
    * Gets the Baycom field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Baycom or the specified default value.
    */
   public final String getBaycom( int index, String defaultValue )
   {
      return _Baycom[index] == null ? defaultValue : _Baycom[index];
   }
    
   /**
    * Gets the array of Baycom fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Baycom values.
    */
   public final String[] getBaycomArray()
   {
      return _Baycom;
   }
    
   /**
    * Gets the Fund Currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Currency or null.
    */
   public final String getFundCurrency( int index )
   {
      return _FundCurrency[index];
   }
    
   /**
    * Gets the Fund Currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Currency or the specified default value.
    */
   public final String getFundCurrency( int index, String defaultValue )
   {
      return _FundCurrency[index] == null ? defaultValue : _FundCurrency[index];
   }
    
   /**
    * Gets the array of Fund Currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Currency values.
    */
   public final String[] getFundCurrencyArray()
   {
      return _FundCurrency;
   }
    
   /**
    * Gets the Gross Redemption Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Gross Redemption Amount or null.
    */
   public final String getAmount( int index )
   {
      return _Amount[index];
   }
    
   /**
    * Gets the Gross Redemption Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Gross Redemption Amount or the specified default value.
    */
   public final String getAmount( int index, String defaultValue )
   {
      return _Amount[index] == null ? defaultValue : _Amount[index];
   }
    
   /**
    * Gets the array of Gross Redemption Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Gross Redemption Amount values.
    */
   public final String[] getAmountArray()
   {
      return _Amount;
   }
    
   /**
    * Gets the Gross Redemption Units field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Gross Redemption Units or null.
    */
   public final String getUnits( int index )
   {
      return _Units[index];
   }
    
   /**
    * Gets the Gross Redemption Units field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Gross Redemption Units or the specified default value.
    */
   public final String getUnits( int index, String defaultValue )
   {
      return _Units[index] == null ? defaultValue : _Units[index];
   }
    
   /**
    * Gets the array of Gross Redemption Units fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Gross Redemption Units values.
    */
   public final String[] getUnitsArray()
   {
      return _Units;
   }
    
   /**
    * Gets the DSC free amt portion of gross redemption amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the DSC free amt portion of gross redemption amount or null.
    */
   public final String getFreeAmt( int index )
   {
      return _FreeAmt[index];
   }
    
   /**
    * Gets the DSC free amt portion of gross redemption amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the DSC free amt portion of gross redemption amount or the specified default value.
    */
   public final String getFreeAmt( int index, String defaultValue )
   {
      return _FreeAmt[index] == null ? defaultValue : _FreeAmt[index];
   }
    
   /**
    * Gets the array of DSC free amt portion of gross redemption amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of DSC free amt portion of gross redemption amount values.
    */
   public final String[] getFreeAmtArray()
   {
      return _FreeAmt;
   }
    
   /**
    * Gets the DSC free units portion of gross redemption amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the DSC free units portion of gross redemption amount or null.
    */
   public final String getFreeUnits( int index )
   {
      return _FreeUnits[index];
   }
    
   /**
    * Gets the DSC free units portion of gross redemption amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the DSC free units portion of gross redemption amount or the specified default value.
    */
   public final String getFreeUnits( int index, String defaultValue )
   {
      return _FreeUnits[index] == null ? defaultValue : _FreeUnits[index];
   }
    
   /**
    * Gets the array of DSC free units portion of gross redemption amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of DSC free units portion of gross redemption amount values.
    */
   public final String[] getFreeUnitsArray()
   {
      return _FreeUnits;
   }
    
   /**
    * Gets the Portion of gross redemption amount charged with DSC - in amt field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Portion of gross redemption amount charged with DSC - in amt or null.
    */
   public final String getFeeApplAmt( int index )
   {
      return _FeeApplAmt[index];
   }
    
   /**
    * Gets the Portion of gross redemption amount charged with DSC - in amt field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Portion of gross redemption amount charged with DSC - in amt or the specified default value.
    */
   public final String getFeeApplAmt( int index, String defaultValue )
   {
      return _FeeApplAmt[index] == null ? defaultValue : _FeeApplAmt[index];
   }
    
   /**
    * Gets the array of Portion of gross redemption amount charged with DSC - in amt fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Portion of gross redemption amount charged with DSC - in amt values.
    */
   public final String[] getFeeApplAmtArray()
   {
      return _FeeApplAmt;
   }
    
   /**
    * Gets the Portion of gross redemption amount Portion of gross redemption amount charged with DSC - in units field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Portion of gross redemption amount Portion of gross redemption amount charged with DSC - in units or null.
    */
   public final String getFeeApplUnits( int index )
   {
      return _FeeApplUnits[index];
   }
    
   /**
    * Gets the Portion of gross redemption amount Portion of gross redemption amount charged with DSC - in units field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Portion of gross redemption amount Portion of gross redemption amount charged with DSC - in units or the specified default value.
    */
   public final String getFeeApplUnits( int index, String defaultValue )
   {
      return _FeeApplUnits[index] == null ? defaultValue : _FeeApplUnits[index];
   }
    
   /**
    * Gets the array of Portion of gross redemption amount Portion of gross redemption amount charged with DSC - in units fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Portion of gross redemption amount Portion of gross redemption amount charged with DSC - in units values.
    */
   public final String[] getFeeApplUnitsArray()
   {
      return _FeeApplUnits;
   }
    
   /**
    * Gets the DSC fee charged to Fund/ Class field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the DSC fee charged to Fund/ Class or null.
    */
   public final String getDSCAmt( int index )
   {
      return _DSCAmt[index];
   }
    
   /**
    * Gets the DSC fee charged to Fund/ Class field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the DSC fee charged to Fund/ Class or the specified default value.
    */
   public final String getDSCAmt( int index, String defaultValue )
   {
      return _DSCAmt[index] == null ? defaultValue : _DSCAmt[index];
   }
    
   /**
    * Gets the array of DSC fee charged to Fund/ Class fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of DSC fee charged to Fund/ Class values.
    */
   public final String[] getDSCAmtArray()
   {
      return _DSCAmt;
   }
    
   /**
    * Gets the Withholding tax charged to the fund/ class field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Withholding tax charged to the fund/ class or null.
    */
   public final String getTax( int index )
   {
      return _Tax[index];
   }
    
   /**
    * Gets the Withholding tax charged to the fund/ class field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Withholding tax charged to the fund/ class or the specified default value.
    */
   public final String getTax( int index, String defaultValue )
   {
      return _Tax[index] == null ? defaultValue : _Tax[index];
   }
    
   /**
    * Gets the array of Withholding tax charged to the fund/ class fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Withholding tax charged to the fund/ class values.
    */
   public final String[] getTaxArray()
   {
      return _Tax;
   }
    
   /**
    * Gets the Other fees charged to fund/ class field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Other fees charged to fund/ class or null.
    */
   public final String getFee( int index )
   {
      return _Fee[index];
   }
    
   /**
    * Gets the Other fees charged to fund/ class field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Other fees charged to fund/ class or the specified default value.
    */
   public final String getFee( int index, String defaultValue )
   {
      return _Fee[index] == null ? defaultValue : _Fee[index];
   }
    
   /**
    * Gets the array of Other fees charged to fund/ class fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Other fees charged to fund/ class values.
    */
   public final String[] getFeeArray()
   {
      return _Fee;
   }
    
   /**
    * Gets the Error  Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Error  Code or null.
    */
   public final Integer getErrCode( int index )
   {
      return _ErrCode[index];
   }
    
   /**
    * Gets the Error  Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Error  Code or the specified default value.
    */
   public final int getErrCode( int index, int defaultValue )
   {
      return _ErrCode[index] == null ? defaultValue : _ErrCode[index].intValue();
   }
    
   /**
    * Gets the array of Error  Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Error  Code values.
    */
   public final Integer[] getErrCodeArray()
   {
      return _ErrCode;
   }
    
   /**
    * Gets the Error Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Error Description or null.
    */
   public final String getErrDesc( int index )
   {
      return _ErrDesc[index];
   }
    
   /**
    * Gets the Error Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Error Description or the specified default value.
    */
   public final String getErrDesc( int index, String defaultValue )
   {
      return _ErrDesc[index] == null ? defaultValue : _ErrDesc[index];
   }
    
   /**
    * Gets the array of Error Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Error Description values.
    */
   public final String[] getErrDescArray()
   {
      return _ErrDesc;
   }
    
   /**
    * Gets the Federal Clawback field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Federal Clawback or null.
    */
   public final String getFedClawback( int index )
   {
      return _FedClawback[index];
   }
    
   /**
    * Gets the Federal Clawback field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Federal Clawback or the specified default value.
    */
   public final String getFedClawback( int index, String defaultValue )
   {
      return _FedClawback[index] == null ? defaultValue : _FedClawback[index];
   }
    
   /**
    * Gets the array of Federal Clawback fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Federal Clawback values.
    */
   public final String[] getFedClawbackArray()
   {
      return _FedClawback;
   }
    
   /**
    * Gets the Provincial Clawback field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Provincial Clawback or null.
    */
   public final String getProvClawback( int index )
   {
      return _ProvClawback[index];
   }
    
   /**
    * Gets the Provincial Clawback field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Provincial Clawback or the specified default value.
    */
   public final String getProvClawback( int index, String defaultValue )
   {
      return _ProvClawback[index] == null ? defaultValue : _ProvClawback[index];
   }
    
   /**
    * Gets the array of Provincial Clawback fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Provincial Clawback values.
    */
   public final String[] getProvClawbackArray()
   {
      return _ProvClawback;
   }
    
   /**
    * Gets the Additional Clawback field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Additional Clawback or null.
    */
   public final String getAddlProvClawback( int index )
   {
      return _AddlProvClawback[index];
   }
    
   /**
    * Gets the Additional Clawback field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Additional Clawback or the specified default value.
    */
   public final String getAddlProvClawback( int index, String defaultValue )
   {
      return _AddlProvClawback[index] == null ? defaultValue : _AddlProvClawback[index];
   }
    
   /**
    * Gets the array of Additional Clawback fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Additional Clawback values.
    */
   public final String[] getAddlProvClawbackArray()
   {
      return _AddlProvClawback;
   }
    
   /**
    * Gets the Federal Tax field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Federal Tax or null.
    */
   public final String getFedTax( int index )
   {
      return _FedTax[index];
   }
    
   /**
    * Gets the Federal Tax field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Federal Tax or the specified default value.
    */
   public final String getFedTax( int index, String defaultValue )
   {
      return _FedTax[index] == null ? defaultValue : _FedTax[index];
   }
    
   /**
    * Gets the array of Federal Tax fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Federal Tax values.
    */
   public final String[] getFedTaxArray()
   {
      return _FedTax;
   }
    
   /**
    * Gets the Provincial Tax field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Provincial Tax or null.
    */
   public final String getProvTax( int index )
   {
      return _ProvTax[index];
   }
    
   /**
    * Gets the Provincial Tax field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Provincial Tax or the specified default value.
    */
   public final String getProvTax( int index, String defaultValue )
   {
      return _ProvTax[index] == null ? defaultValue : _ProvTax[index];
   }
    
   /**
    * Gets the array of Provincial Tax fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Provincial Tax values.
    */
   public final String[] getProvTaxArray()
   {
      return _ProvTax;
   }
    
   /**
    * Gets the Percemtage of Fee field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Percemtage of Fee or null.
    */
   public final String getFeePrcnt( int index )
   {
      return _FeePrcnt[index];
   }
    
   /**
    * Gets the Percemtage of Fee field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Percemtage of Fee or the specified default value.
    */
   public final String getFeePrcnt( int index, String defaultValue )
   {
      return _FeePrcnt[index] == null ? defaultValue : _FeePrcnt[index];
   }
    
   /**
    * Gets the array of Percemtage of Fee fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Percemtage of Fee values.
    */
   public final String[] getFeePrcntArray()
   {
      return _FeePrcnt;
   }
    
   /**
    * Gets the Record Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Record Type or null.
    */
   public final String getRecordType( int index )
   {
      return _RecordType[index];
   }
    
   /**
    * Gets the Record Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Record Type or the specified default value.
    */
   public final String getRecordType( int index, String defaultValue )
   {
      return _RecordType[index] == null ? defaultValue : _RecordType[index];
   }
    
   /**
    * Gets the array of Record Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Record Type values.
    */
   public final String[] getRecordTypeArray()
   {
      return _RecordType;
   }
    
   /**
    * Gets the TotCBAmount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the TotCBAmount or null.
    */
   public final String getTotCBAmount( int index )
   {
      return _TotCBAmount[index];
   }
    
   /**
    * Gets the TotCBAmount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TotCBAmount or the specified default value.
    */
   public final String getTotCBAmount( int index, String defaultValue )
   {
      return _TotCBAmount[index] == null ? defaultValue : _TotCBAmount[index];
   }
    
   /**
    * Gets the array of TotCBAmount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of TotCBAmount values.
    */
   public final String[] getTotCBAmountArray()
   {
      return _TotCBAmount;
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
      _UpdateStatus = responseBuffer.decodeBoolean(responseBuffer.getNextField());
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _rxFundCode = resizeArray( _rxFundCode, _RepeatCount );
      _rxClassCode = resizeArray( _rxClassCode, _RepeatCount );
      _Baycom = resizeArray( _Baycom, _RepeatCount );
      _FundCurrency = resizeArray( _FundCurrency, _RepeatCount );
      _Amount = resizeArray( _Amount, _RepeatCount );
      _Units = resizeArray( _Units, _RepeatCount );
      _FreeAmt = resizeArray( _FreeAmt, _RepeatCount );
      _FreeUnits = resizeArray( _FreeUnits, _RepeatCount );
      _FeeApplAmt = resizeArray( _FeeApplAmt, _RepeatCount );
      _FeeApplUnits = resizeArray( _FeeApplUnits, _RepeatCount );
      _DSCAmt = resizeArray( _DSCAmt, _RepeatCount );
      _Tax = resizeArray( _Tax, _RepeatCount );
      _Fee = resizeArray( _Fee, _RepeatCount );
      _ErrCode = resizeArray( _ErrCode, _RepeatCount );
      _ErrDesc = resizeArray( _ErrDesc, _RepeatCount );
      _FedClawback = resizeArray( _FedClawback, _RepeatCount );
      _ProvClawback = resizeArray( _ProvClawback, _RepeatCount );
      _AddlProvClawback = resizeArray( _AddlProvClawback, _RepeatCount );
      _FedTax = resizeArray( _FedTax, _RepeatCount );
      _ProvTax = resizeArray( _ProvTax, _RepeatCount );
      _FeePrcnt = resizeArray( _FeePrcnt, _RepeatCount );
      _RecordType = resizeArray( _RecordType, _RepeatCount );
      _TotCBAmount = resizeArray( _TotCBAmount, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxFundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Baycom[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundCurrency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Amount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Units[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FreeAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FreeUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FeeApplAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FeeApplUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DSCAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Tax[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Fee[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ErrCode[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ErrDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FedClawback[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProvClawback[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddlProvClawback[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FedTax[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProvTax[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FeePrcnt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RecordType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TotCBAmount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
