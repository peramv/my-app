
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Shareholder's  Addresses view.
 * For additional view information see <A HREF="../../../../viewspecs/ShareholderAddress.doc">ShareholderAddress.doc</A>.
 * 
 * @author RTS Generated
 */
public class ShareholderAddressView extends IFastView implements Serializable
{

   /**
    * Shareholder Name 2 member variable.
    */
   private String _ShrName2 = null;
   
   private int _RepeatCount = 0;
   
   /**
    * AddressCode member array.
    */
   private String[] _AddrCode = null;
   
   /**
    * AddressCodeDesc member array.
    */
   private String[] _AddrCodeDesc = null;
   
   /**
    * Name1 member array.
    */
   private String[] _Name1 = null;
   
   /**
    * Name2 member array.
    */
   private String[] _Name2 = null;
   
   /**
    * AddrLine1 member array.
    */
   private String[] _AddrLine1 = null;
   
   /**
    * AddrLine2 member array.
    */
   private String[] _AddrLine2 = null;
   
   /**
    * AddrLine3 member array.
    */
   private String[] _AddrLine3 = null;
   
   /**
    * AddrLine4 member array.
    */
   private String[] _AddrLine4 = null;
   
   /**
    * AddrLine5 member array.
    */
   private String[] _AddrLine5 = null;
   
   /**
    * Postal Code member array.
    */
   private String[] _PostalCode = null;
   
   /**
    * Country Code member array.
    */
   private String[] _CountryCode = null;
   
   /**
    * Country Name member array.
    */
   private String[] _CountryName = null;
   
   /**
    * Address Change Confirmation member array.
    */
   private Boolean[] _Confirm = null;
   
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = null;
   
   /**
    * Stop Date member array.
    */
   private Date[] _StopDate = null;
   
   /**
    * Date of Creation member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * Modification Date member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * Created By User member array.
    */
   private String[] _Username = null;
   
   /**
    * Modified by User ID member array.
    */
   private String[] _ModUser = null;
   
   /**
    * City member array.
    */
   private String[] _City = null;
   
   /**
    * Salutation member array.
    */
   private String[] _Salutation = null;
   
   /**
    * Address-File Version Number member array.
    */
   private Integer[] _AddressFileVer = null;
   
   /**
    * Address-File Record Id member array.
    */
   private Integer[] _AddressFileRid = null;
   
   /**
    * Address Status member array.
    */
   private Integer[] _AddrStatus = null;
   
   /**
    * Default Registered Address Code member array.
    */
   private String[] _RegAddrCode = null;
   
   /**
    * Province member array.
    */
   private String[] _Province = null;
   
   /**
    * Returned Mail Date member array.
    */
   private Date[] _RetMailDate = null;
   
   /**
    * Returned Mail Flag member array.
    */
   private Boolean[] _RetMailFlag = null;
   
   /**
    * Reason of returned mail member array.
    */
   private String[] _RetMailReasonCode = null;
   
   /**
    * Stage of returned mail member array.
    */
   private String[] _UnclmStage = null;
   
   /**
    * Date that government report is generated member array.
    */
   private Date[] _UnclmStmtDate = null;
   
   /**
    * Date that property is remitted to the government member array.
    */
   private Date[] _UnclmRemitDate = null;
   
   /**
    * Date that stage is changed to unclaimed member array.
    */
   private Date[] _StageDate = null;
   
   /**
    * Free format comment member array.
    */
   private String[] _Comments = null;
   
   /**
    * Indicates if stage was overridden member array.
    */
   private String[] _StageAssignBy = null;
   
   /**
    * Skips Address Validation member array.
    */
   private String[] _SkipValidate = null;
   
   /**
    * Verify Status member array.
    */
   private String[] _VerifyStat = null;
   

   /**
    * Constructs the ShareholderAddressView object.
    * 
    */
   public ShareholderAddressView()
   {
      super ( new ShareholderAddressRequest() );
   }

   /**
    * Constructs the ShareholderAddressView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public ShareholderAddressView( String hostEncoding )
   {
      super ( new ShareholderAddressRequest( hostEncoding ) );
   }

   /**
    * Gets the ShareholderAddressRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The ShareholderAddressRequest object.
    */
   public final ShareholderAddressRequest getRequest()
   {
      return (ShareholderAddressRequest)getIFastRequest();
   }
        
   /**
    * Gets the Shareholder Name 2 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Shareholder Name 2 or null.
    */
   public final String getShrName2()
   {
      return _ShrName2;
   }
	
   /**
    * Gets the Shareholder Name 2 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Shareholder Name 2 or the specified default value.
    */
   public final String getShrName2( String defaultValue )
   {
      return _ShrName2 == null ? defaultValue : _ShrName2;
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
    * Gets the AddressCode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AddressCode or null.
    */
   public final String getAddrCode( int index )
   {
      return _AddrCode[index];
   }
    
   /**
    * Gets the AddressCode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AddressCode or the specified default value.
    */
   public final String getAddrCode( int index, String defaultValue )
   {
      return _AddrCode[index] == null ? defaultValue : _AddrCode[index];
   }
    
   /**
    * Gets the array of AddressCode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AddressCode values.
    */
   public final String[] getAddrCodeArray()
   {
      return _AddrCode;
   }
    
   /**
    * Gets the AddressCodeDesc field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AddressCodeDesc or null.
    */
   public final String getAddrCodeDesc( int index )
   {
      return _AddrCodeDesc[index];
   }
    
   /**
    * Gets the AddressCodeDesc field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AddressCodeDesc or the specified default value.
    */
   public final String getAddrCodeDesc( int index, String defaultValue )
   {
      return _AddrCodeDesc[index] == null ? defaultValue : _AddrCodeDesc[index];
   }
    
   /**
    * Gets the array of AddressCodeDesc fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AddressCodeDesc values.
    */
   public final String[] getAddrCodeDescArray()
   {
      return _AddrCodeDesc;
   }
    
   /**
    * Gets the Name1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Name1 or null.
    */
   public final String getName1( int index )
   {
      return _Name1[index];
   }
    
   /**
    * Gets the Name1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Name1 or the specified default value.
    */
   public final String getName1( int index, String defaultValue )
   {
      return _Name1[index] == null ? defaultValue : _Name1[index];
   }
    
   /**
    * Gets the array of Name1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Name1 values.
    */
   public final String[] getName1Array()
   {
      return _Name1;
   }
    
   /**
    * Gets the Name2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Name2 or null.
    */
   public final String getName2( int index )
   {
      return _Name2[index];
   }
    
   /**
    * Gets the Name2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Name2 or the specified default value.
    */
   public final String getName2( int index, String defaultValue )
   {
      return _Name2[index] == null ? defaultValue : _Name2[index];
   }
    
   /**
    * Gets the array of Name2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Name2 values.
    */
   public final String[] getName2Array()
   {
      return _Name2;
   }
    
   /**
    * Gets the AddrLine1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AddrLine1 or null.
    */
   public final String getAddrLine1( int index )
   {
      return _AddrLine1[index];
   }
    
   /**
    * Gets the AddrLine1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AddrLine1 or the specified default value.
    */
   public final String getAddrLine1( int index, String defaultValue )
   {
      return _AddrLine1[index] == null ? defaultValue : _AddrLine1[index];
   }
    
   /**
    * Gets the array of AddrLine1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AddrLine1 values.
    */
   public final String[] getAddrLine1Array()
   {
      return _AddrLine1;
   }
    
   /**
    * Gets the AddrLine2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AddrLine2 or null.
    */
   public final String getAddrLine2( int index )
   {
      return _AddrLine2[index];
   }
    
   /**
    * Gets the AddrLine2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AddrLine2 or the specified default value.
    */
   public final String getAddrLine2( int index, String defaultValue )
   {
      return _AddrLine2[index] == null ? defaultValue : _AddrLine2[index];
   }
    
   /**
    * Gets the array of AddrLine2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AddrLine2 values.
    */
   public final String[] getAddrLine2Array()
   {
      return _AddrLine2;
   }
    
   /**
    * Gets the AddrLine3 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AddrLine3 or null.
    */
   public final String getAddrLine3( int index )
   {
      return _AddrLine3[index];
   }
    
   /**
    * Gets the AddrLine3 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AddrLine3 or the specified default value.
    */
   public final String getAddrLine3( int index, String defaultValue )
   {
      return _AddrLine3[index] == null ? defaultValue : _AddrLine3[index];
   }
    
   /**
    * Gets the array of AddrLine3 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AddrLine3 values.
    */
   public final String[] getAddrLine3Array()
   {
      return _AddrLine3;
   }
    
   /**
    * Gets the AddrLine4 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AddrLine4 or null.
    */
   public final String getAddrLine4( int index )
   {
      return _AddrLine4[index];
   }
    
   /**
    * Gets the AddrLine4 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AddrLine4 or the specified default value.
    */
   public final String getAddrLine4( int index, String defaultValue )
   {
      return _AddrLine4[index] == null ? defaultValue : _AddrLine4[index];
   }
    
   /**
    * Gets the array of AddrLine4 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AddrLine4 values.
    */
   public final String[] getAddrLine4Array()
   {
      return _AddrLine4;
   }
    
   /**
    * Gets the AddrLine5 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AddrLine5 or null.
    */
   public final String getAddrLine5( int index )
   {
      return _AddrLine5[index];
   }
    
   /**
    * Gets the AddrLine5 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AddrLine5 or the specified default value.
    */
   public final String getAddrLine5( int index, String defaultValue )
   {
      return _AddrLine5[index] == null ? defaultValue : _AddrLine5[index];
   }
    
   /**
    * Gets the array of AddrLine5 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AddrLine5 values.
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
    * Gets the Country Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Country Code or null.
    */
   public final String getCountryCode( int index )
   {
      return _CountryCode[index];
   }
    
   /**
    * Gets the Country Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Country Code or the specified default value.
    */
   public final String getCountryCode( int index, String defaultValue )
   {
      return _CountryCode[index] == null ? defaultValue : _CountryCode[index];
   }
    
   /**
    * Gets the array of Country Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Country Code values.
    */
   public final String[] getCountryCodeArray()
   {
      return _CountryCode;
   }
    
   /**
    * Gets the Country Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Country Name or null.
    */
   public final String getCountryName( int index )
   {
      return _CountryName[index];
   }
    
   /**
    * Gets the Country Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Country Name or the specified default value.
    */
   public final String getCountryName( int index, String defaultValue )
   {
      return _CountryName[index] == null ? defaultValue : _CountryName[index];
   }
    
   /**
    * Gets the array of Country Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Country Name values.
    */
   public final String[] getCountryNameArray()
   {
      return _CountryName;
   }
    
   /**
    * Gets the Address Change Confirmation field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Change Confirmation or null.
    */
   public final Boolean getConfirm( int index )
   {
      return _Confirm[index];
   }
    
   /**
    * Gets the Address Change Confirmation field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Change Confirmation or the specified default value.
    */
   public final boolean getConfirm( int index, boolean defaultValue )
   {
      return _Confirm[index] == null ? defaultValue : _Confirm[index].booleanValue();
   }
    
   /**
    * Gets the array of Address Change Confirmation fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Change Confirmation values.
    */
   public final Boolean[] getConfirmArray()
   {
      return _Confirm;
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
    * Gets the Created By User field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Created By User or null.
    */
   public final String getUsername( int index )
   {
      return _Username[index];
   }
    
   /**
    * Gets the Created By User field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Created By User or the specified default value.
    */
   public final String getUsername( int index, String defaultValue )
   {
      return _Username[index] == null ? defaultValue : _Username[index];
   }
    
   /**
    * Gets the array of Created By User fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Created By User values.
    */
   public final String[] getUsernameArray()
   {
      return _Username;
   }
    
   /**
    * Gets the Modified by User ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Modified by User ID or null.
    */
   public final String getModUser( int index )
   {
      return _ModUser[index];
   }
    
   /**
    * Gets the Modified by User ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Modified by User ID or the specified default value.
    */
   public final String getModUser( int index, String defaultValue )
   {
      return _ModUser[index] == null ? defaultValue : _ModUser[index];
   }
    
   /**
    * Gets the array of Modified by User ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Modified by User ID values.
    */
   public final String[] getModUserArray()
   {
      return _ModUser;
   }
    
   /**
    * Gets the City field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the City or null.
    */
   public final String getCity( int index )
   {
      return _City[index];
   }
    
   /**
    * Gets the City field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the City or the specified default value.
    */
   public final String getCity( int index, String defaultValue )
   {
      return _City[index] == null ? defaultValue : _City[index];
   }
    
   /**
    * Gets the array of City fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of City values.
    */
   public final String[] getCityArray()
   {
      return _City;
   }
    
   /**
    * Gets the Salutation field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Salutation or null.
    */
   public final String getSalutation( int index )
   {
      return _Salutation[index];
   }
    
   /**
    * Gets the Salutation field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Salutation or the specified default value.
    */
   public final String getSalutation( int index, String defaultValue )
   {
      return _Salutation[index] == null ? defaultValue : _Salutation[index];
   }
    
   /**
    * Gets the array of Salutation fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Salutation values.
    */
   public final String[] getSalutationArray()
   {
      return _Salutation;
   }
    
   /**
    * Gets the Address-File Version Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address-File Version Number or null.
    */
   public final Integer getAddressFileVer( int index )
   {
      return _AddressFileVer[index];
   }
    
   /**
    * Gets the Address-File Version Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address-File Version Number or the specified default value.
    */
   public final int getAddressFileVer( int index, int defaultValue )
   {
      return _AddressFileVer[index] == null ? defaultValue : _AddressFileVer[index].intValue();
   }
    
   /**
    * Gets the array of Address-File Version Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address-File Version Number values.
    */
   public final Integer[] getAddressFileVerArray()
   {
      return _AddressFileVer;
   }
    
   /**
    * Gets the Address-File Record Id field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address-File Record Id or null.
    */
   public final Integer getAddressFileRid( int index )
   {
      return _AddressFileRid[index];
   }
    
   /**
    * Gets the Address-File Record Id field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address-File Record Id or the specified default value.
    */
   public final int getAddressFileRid( int index, int defaultValue )
   {
      return _AddressFileRid[index] == null ? defaultValue : _AddressFileRid[index].intValue();
   }
    
   /**
    * Gets the array of Address-File Record Id fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address-File Record Id values.
    */
   public final Integer[] getAddressFileRidArray()
   {
      return _AddressFileRid;
   }
    
   /**
    * Gets the Address Status field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Status or null.
    */
   public final Integer getAddrStatus( int index )
   {
      return _AddrStatus[index];
   }
    
   /**
    * Gets the Address Status field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Status or the specified default value.
    */
   public final int getAddrStatus( int index, int defaultValue )
   {
      return _AddrStatus[index] == null ? defaultValue : _AddrStatus[index].intValue();
   }
    
   /**
    * Gets the array of Address Status fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Status values.
    */
   public final Integer[] getAddrStatusArray()
   {
      return _AddrStatus;
   }
    
   /**
    * Gets the Default Registered Address Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Default Registered Address Code or null.
    */
   public final String getRegAddrCode( int index )
   {
      return _RegAddrCode[index];
   }
    
   /**
    * Gets the Default Registered Address Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Default Registered Address Code or the specified default value.
    */
   public final String getRegAddrCode( int index, String defaultValue )
   {
      return _RegAddrCode[index] == null ? defaultValue : _RegAddrCode[index];
   }
    
   /**
    * Gets the array of Default Registered Address Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Default Registered Address Code values.
    */
   public final String[] getRegAddrCodeArray()
   {
      return _RegAddrCode;
   }
    
   /**
    * Gets the Province field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Province or null.
    */
   public final String getProvince( int index )
   {
      return _Province[index];
   }
    
   /**
    * Gets the Province field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Province or the specified default value.
    */
   public final String getProvince( int index, String defaultValue )
   {
      return _Province[index] == null ? defaultValue : _Province[index];
   }
    
   /**
    * Gets the array of Province fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Province values.
    */
   public final String[] getProvinceArray()
   {
      return _Province;
   }
    
   /**
    * Gets the Returned Mail Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Returned Mail Date or null.
    */
   public final Date getRetMailDate( int index )
   {
      return _RetMailDate[index];
   }
    
   /**
    * Gets the Returned Mail Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Returned Mail Date or the specified default value.
    */
   public final Date getRetMailDate( int index, Date defaultValue )
   {
      return _RetMailDate[index] == null ? defaultValue : _RetMailDate[index];
   }
    
   /**
    * Gets the array of Returned Mail Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Returned Mail Date values.
    */
   public final Date[] getRetMailDateArray()
   {
      return _RetMailDate;
   }
    
   /**
    * Gets the Returned Mail Flag field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Returned Mail Flag or null.
    */
   public final Boolean getRetMailFlag( int index )
   {
      return _RetMailFlag[index];
   }
    
   /**
    * Gets the Returned Mail Flag field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Returned Mail Flag or the specified default value.
    */
   public final boolean getRetMailFlag( int index, boolean defaultValue )
   {
      return _RetMailFlag[index] == null ? defaultValue : _RetMailFlag[index].booleanValue();
   }
    
   /**
    * Gets the array of Returned Mail Flag fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Returned Mail Flag values.
    */
   public final Boolean[] getRetMailFlagArray()
   {
      return _RetMailFlag;
   }
    
   /**
    * Gets the Reason of returned mail field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reason of returned mail or null.
    */
   public final String getRetMailReasonCode( int index )
   {
      return _RetMailReasonCode[index];
   }
    
   /**
    * Gets the Reason of returned mail field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reason of returned mail or the specified default value.
    */
   public final String getRetMailReasonCode( int index, String defaultValue )
   {
      return _RetMailReasonCode[index] == null ? defaultValue : _RetMailReasonCode[index];
   }
    
   /**
    * Gets the array of Reason of returned mail fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reason of returned mail values.
    */
   public final String[] getRetMailReasonCodeArray()
   {
      return _RetMailReasonCode;
   }
    
   /**
    * Gets the Stage of returned mail field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stage of returned mail or null.
    */
   public final String getUnclmStage( int index )
   {
      return _UnclmStage[index];
   }
    
   /**
    * Gets the Stage of returned mail field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stage of returned mail or the specified default value.
    */
   public final String getUnclmStage( int index, String defaultValue )
   {
      return _UnclmStage[index] == null ? defaultValue : _UnclmStage[index];
   }
    
   /**
    * Gets the array of Stage of returned mail fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stage of returned mail values.
    */
   public final String[] getUnclmStageArray()
   {
      return _UnclmStage;
   }
    
   /**
    * Gets the Date that government report is generated field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Date that government report is generated or null.
    */
   public final Date getUnclmStmtDate( int index )
   {
      return _UnclmStmtDate[index];
   }
    
   /**
    * Gets the Date that government report is generated field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date that government report is generated or the specified default value.
    */
   public final Date getUnclmStmtDate( int index, Date defaultValue )
   {
      return _UnclmStmtDate[index] == null ? defaultValue : _UnclmStmtDate[index];
   }
    
   /**
    * Gets the array of Date that government report is generated fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Date that government report is generated values.
    */
   public final Date[] getUnclmStmtDateArray()
   {
      return _UnclmStmtDate;
   }
    
   /**
    * Gets the Date that property is remitted to the government field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Date that property is remitted to the government or null.
    */
   public final Date getUnclmRemitDate( int index )
   {
      return _UnclmRemitDate[index];
   }
    
   /**
    * Gets the Date that property is remitted to the government field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date that property is remitted to the government or the specified default value.
    */
   public final Date getUnclmRemitDate( int index, Date defaultValue )
   {
      return _UnclmRemitDate[index] == null ? defaultValue : _UnclmRemitDate[index];
   }
    
   /**
    * Gets the array of Date that property is remitted to the government fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Date that property is remitted to the government values.
    */
   public final Date[] getUnclmRemitDateArray()
   {
      return _UnclmRemitDate;
   }
    
   /**
    * Gets the Date that stage is changed to unclaimed field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Date that stage is changed to unclaimed or null.
    */
   public final Date getStageDate( int index )
   {
      return _StageDate[index];
   }
    
   /**
    * Gets the Date that stage is changed to unclaimed field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date that stage is changed to unclaimed or the specified default value.
    */
   public final Date getStageDate( int index, Date defaultValue )
   {
      return _StageDate[index] == null ? defaultValue : _StageDate[index];
   }
    
   /**
    * Gets the array of Date that stage is changed to unclaimed fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Date that stage is changed to unclaimed values.
    */
   public final Date[] getStageDateArray()
   {
      return _StageDate;
   }
    
   /**
    * Gets the Free format comment field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Free format comment or null.
    */
   public final String getComments( int index )
   {
      return _Comments[index];
   }
    
   /**
    * Gets the Free format comment field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Free format comment or the specified default value.
    */
   public final String getComments( int index, String defaultValue )
   {
      return _Comments[index] == null ? defaultValue : _Comments[index];
   }
    
   /**
    * Gets the array of Free format comment fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Free format comment values.
    */
   public final String[] getCommentsArray()
   {
      return _Comments;
   }
    
   /**
    * Gets the Indicates if stage was overridden field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Indicates if stage was overridden or null.
    */
   public final String getStageAssignBy( int index )
   {
      return _StageAssignBy[index];
   }
    
   /**
    * Gets the Indicates if stage was overridden field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Indicates if stage was overridden or the specified default value.
    */
   public final String getStageAssignBy( int index, String defaultValue )
   {
      return _StageAssignBy[index] == null ? defaultValue : _StageAssignBy[index];
   }
    
   /**
    * Gets the array of Indicates if stage was overridden fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Indicates if stage was overridden values.
    */
   public final String[] getStageAssignByArray()
   {
      return _StageAssignBy;
   }
    
   /**
    * Gets the Skips Address Validation field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Skips Address Validation or null.
    */
   public final String getSkipValidate( int index )
   {
      return _SkipValidate[index];
   }
    
   /**
    * Gets the Skips Address Validation field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Skips Address Validation or the specified default value.
    */
   public final String getSkipValidate( int index, String defaultValue )
   {
      return _SkipValidate[index] == null ? defaultValue : _SkipValidate[index];
   }
    
   /**
    * Gets the array of Skips Address Validation fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Skips Address Validation values.
    */
   public final String[] getSkipValidateArray()
   {
      return _SkipValidate;
   }
    
   /**
    * Gets the Verify Status field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Verify Status or null.
    */
   public final String getVerifyStat( int index )
   {
      return _VerifyStat[index];
   }
    
   /**
    * Gets the Verify Status field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Verify Status or the specified default value.
    */
   public final String getVerifyStat( int index, String defaultValue )
   {
      return _VerifyStat[index] == null ? defaultValue : _VerifyStat[index];
   }
    
   /**
    * Gets the array of Verify Status fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Verify Status values.
    */
   public final String[] getVerifyStatArray()
   {
      return _VerifyStat;
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
      _ShrName2 = responseBuffer.decodeString(responseBuffer.getNextField());
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _AddrCode = resizeArray( _AddrCode, _RepeatCount );
      _AddrCodeDesc = resizeArray( _AddrCodeDesc, _RepeatCount );
      _Name1 = resizeArray( _Name1, _RepeatCount );
      _Name2 = resizeArray( _Name2, _RepeatCount );
      _AddrLine1 = resizeArray( _AddrLine1, _RepeatCount );
      _AddrLine2 = resizeArray( _AddrLine2, _RepeatCount );
      _AddrLine3 = resizeArray( _AddrLine3, _RepeatCount );
      _AddrLine4 = resizeArray( _AddrLine4, _RepeatCount );
      _AddrLine5 = resizeArray( _AddrLine5, _RepeatCount );
      _PostalCode = resizeArray( _PostalCode, _RepeatCount );
      _CountryCode = resizeArray( _CountryCode, _RepeatCount );
      _CountryName = resizeArray( _CountryName, _RepeatCount );
      _Confirm = resizeArray( _Confirm, _RepeatCount );
      _EffectiveDate = resizeArray( _EffectiveDate, _RepeatCount );
      _StopDate = resizeArray( _StopDate, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _Username = resizeArray( _Username, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _City = resizeArray( _City, _RepeatCount );
      _Salutation = resizeArray( _Salutation, _RepeatCount );
      _AddressFileVer = resizeArray( _AddressFileVer, _RepeatCount );
      _AddressFileRid = resizeArray( _AddressFileRid, _RepeatCount );
      _AddrStatus = resizeArray( _AddrStatus, _RepeatCount );
      _RegAddrCode = resizeArray( _RegAddrCode, _RepeatCount );
      _Province = resizeArray( _Province, _RepeatCount );
      _RetMailDate = resizeArray( _RetMailDate, _RepeatCount );
      _RetMailFlag = resizeArray( _RetMailFlag, _RepeatCount );
      _RetMailReasonCode = resizeArray( _RetMailReasonCode, _RepeatCount );
      _UnclmStage = resizeArray( _UnclmStage, _RepeatCount );
      _UnclmStmtDate = resizeArray( _UnclmStmtDate, _RepeatCount );
      _UnclmRemitDate = resizeArray( _UnclmRemitDate, _RepeatCount );
      _StageDate = resizeArray( _StageDate, _RepeatCount );
      _Comments = resizeArray( _Comments, _RepeatCount );
      _StageAssignBy = resizeArray( _StageAssignBy, _RepeatCount );
      _SkipValidate = resizeArray( _SkipValidate, _RepeatCount );
      _VerifyStat = resizeArray( _VerifyStat, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _AddrCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrCodeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Name1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Name2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine3[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine4[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine5[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PostalCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CountryCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CountryName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Confirm[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _StopDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _Username[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _City[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Salutation[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddressFileVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _AddressFileRid[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _AddrStatus[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _RegAddrCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Province[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RetMailDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _RetMailFlag[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _RetMailReasonCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UnclmStage[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UnclmStmtDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _UnclmRemitDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _StageDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _Comments[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _StageAssignBy[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SkipValidate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _VerifyStat[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
