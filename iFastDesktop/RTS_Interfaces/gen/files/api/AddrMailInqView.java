
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Address Mailing by Document Type view.
 * For additional view information see <A HREF="../../../../viewspecs/AddrMailInq.doc">AddrMailInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class AddrMailInqView extends IFastView implements Serializable
{

   private int _RspRepeatCount = 0;
   
   /**
    * Document Type member array.
    */
   private String[] _rxDocumentType = null;
   
   /**
    * Address Code member array.
    */
   private String[] _AddrCode = null;
   
   /**
    * Address Code Description member array.
    */
   private String[] _AddrCodeDesc = null;
   
   /**
    * Name 1 member array.
    */
   private String[] _Name1 = null;
   
   /**
    * Name 2 member array.
    */
   private String[] _Name2 = null;
   
   /**
    * Address line 1 member array.
    */
   private String[] _AddrLine1 = null;
   
   /**
    * Address line 2 member array.
    */
   private String[] _AddrLine2 = null;
   
   /**
    * Address line 3 member array.
    */
   private String[] _AddrLine3 = null;
   
   /**
    * Address line 4 member array.
    */
   private String[] _AddrLine4 = null;
   
   /**
    * Address line 5 member array.
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
    * Confirm member array.
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
    * Process Date member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * Modify Date member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * User Name member array.
    */
   private String[] _UserName = null;
   
   /**
    * ModUser member array.
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
    * Address File Version member array.
    */
   private Integer[] _AddressFileVer = null;
   
   /**
    * Address File RID member array.
    */
   private Integer[] _AddressFileRID = null;
   
   /**
    * Address Status member array.
    */
   private Integer[] _AddrStatus = null;
   
   /**
    * RegAddrCode member array.
    */
   private String[] _RegAddrCode = null;
   
   /**
    * Province member array.
    */
   private String[] _Province = null;
   
   /**
    * Ret Mail Date member array.
    */
   private Date[] _RetMailDate = null;
   
   /**
    * Ret Mail Flag member array.
    */
   private Boolean[] _RetMailFlag = null;
   
   /**
    * On Hold member array.
    */
   private Boolean[] _OnHold = null;
   
   /**
    * Suppress member array.
    */
   private String[] _Suppress = null;
   
   /**
    * Waive member array.
    */
   private String[] _Waive = null;
   
   /**
    * Mail member array.
    */
   private String[] _Mail = null;
   
   /**
    * Fax member array.
    */
   private String[] _Fax = null;
   
   /**
    * CD member array.
    */
   private String[] _CD = null;
   
   /**
    * EMail member array.
    */
   private String[] _Email = null;
   
   /**
    * EPost member array.
    */
   private String[] _Epost = null;
   
   /**
    * Auth member array.
    */
   private String[] _Auth = null;
   
   /**
    * Number of Copies member array.
    */
   private Integer[] _Copies = null;
   
   /**
    * SA Code member array.
    */
   private String[] _SACode = null;
   
   /**
    * SA Description member array.
    */
   private String[] _SADesc = null;
   

   /**
    * Constructs the AddrMailInqView object.
    * 
    */
   public AddrMailInqView()
   {
      super ( new AddrMailInqRequest() );
   }

   /**
    * Constructs the AddrMailInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AddrMailInqView( String hostEncoding )
   {
      super ( new AddrMailInqRequest( hostEncoding ) );
   }

   /**
    * Gets the AddrMailInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AddrMailInqRequest object.
    */
   public final AddrMailInqRequest getRequest()
   {
      return (AddrMailInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Record Count for the repeatable response.
    * 
    * @return The number of records in the repeating fields.
    */
   public int getRecordCount()
   {
      return _RspRepeatCount;
   }

   /**
    * Gets the Record Count for the repeatable response.
    * 
    * @return The number of records in the repeating fields.
    */
   public final int getRspRepeatCount()
   {
      return _RspRepeatCount;
   }

   /**
    * Decodes the repeat count value from the host 
    * respones.
    * 
    * @param response Host formatted response object.
    * @exception ParseException
    */
   private final void decodeRspRepeatCount( RTSResponseDecodeBuffer responseBuffer ) throws ParseException, UnsupportedEncodingException
   {
      int receivedRecordCount = responseBuffer.decodeInteger(responseBuffer.getNextField()).intValue();
      _RspRepeatCount += receivedRecordCount;
   }

   /**
    * Gets the Document Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Document Type or null.
    */
   public final String getrxDocumentType( int index )
   {
      return _rxDocumentType[index];
   }
    
   /**
    * Gets the Document Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Document Type or the specified default value.
    */
   public final String getrxDocumentType( int index, String defaultValue )
   {
      return _rxDocumentType[index] == null ? defaultValue : _rxDocumentType[index];
   }
    
   /**
    * Gets the array of Document Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Document Type values.
    */
   public final String[] getrxDocumentTypeArray()
   {
      return _rxDocumentType;
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
    * Gets the Address Code Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Code Description or null.
    */
   public final String getAddrCodeDesc( int index )
   {
      return _AddrCodeDesc[index];
   }
    
   /**
    * Gets the Address Code Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Code Description or the specified default value.
    */
   public final String getAddrCodeDesc( int index, String defaultValue )
   {
      return _AddrCodeDesc[index] == null ? defaultValue : _AddrCodeDesc[index];
   }
    
   /**
    * Gets the array of Address Code Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Code Description values.
    */
   public final String[] getAddrCodeDescArray()
   {
      return _AddrCodeDesc;
   }
    
   /**
    * Gets the Name 1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Name 1 or null.
    */
   public final String getName1( int index )
   {
      return _Name1[index];
   }
    
   /**
    * Gets the Name 1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Name 1 or the specified default value.
    */
   public final String getName1( int index, String defaultValue )
   {
      return _Name1[index] == null ? defaultValue : _Name1[index];
   }
    
   /**
    * Gets the array of Name 1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Name 1 values.
    */
   public final String[] getName1Array()
   {
      return _Name1;
   }
    
   /**
    * Gets the Name 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Name 2 or null.
    */
   public final String getName2( int index )
   {
      return _Name2[index];
   }
    
   /**
    * Gets the Name 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Name 2 or the specified default value.
    */
   public final String getName2( int index, String defaultValue )
   {
      return _Name2[index] == null ? defaultValue : _Name2[index];
   }
    
   /**
    * Gets the array of Name 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Name 2 values.
    */
   public final String[] getName2Array()
   {
      return _Name2;
   }
    
   /**
    * Gets the Address line 1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address line 1 or null.
    */
   public final String getAddrLine1( int index )
   {
      return _AddrLine1[index];
   }
    
   /**
    * Gets the Address line 1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address line 1 or the specified default value.
    */
   public final String getAddrLine1( int index, String defaultValue )
   {
      return _AddrLine1[index] == null ? defaultValue : _AddrLine1[index];
   }
    
   /**
    * Gets the array of Address line 1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address line 1 values.
    */
   public final String[] getAddrLine1Array()
   {
      return _AddrLine1;
   }
    
   /**
    * Gets the Address line 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address line 2 or null.
    */
   public final String getAddrLine2( int index )
   {
      return _AddrLine2[index];
   }
    
   /**
    * Gets the Address line 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address line 2 or the specified default value.
    */
   public final String getAddrLine2( int index, String defaultValue )
   {
      return _AddrLine2[index] == null ? defaultValue : _AddrLine2[index];
   }
    
   /**
    * Gets the array of Address line 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address line 2 values.
    */
   public final String[] getAddrLine2Array()
   {
      return _AddrLine2;
   }
    
   /**
    * Gets the Address line 3 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address line 3 or null.
    */
   public final String getAddrLine3( int index )
   {
      return _AddrLine3[index];
   }
    
   /**
    * Gets the Address line 3 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address line 3 or the specified default value.
    */
   public final String getAddrLine3( int index, String defaultValue )
   {
      return _AddrLine3[index] == null ? defaultValue : _AddrLine3[index];
   }
    
   /**
    * Gets the array of Address line 3 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address line 3 values.
    */
   public final String[] getAddrLine3Array()
   {
      return _AddrLine3;
   }
    
   /**
    * Gets the Address line 4 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address line 4 or null.
    */
   public final String getAddrLine4( int index )
   {
      return _AddrLine4[index];
   }
    
   /**
    * Gets the Address line 4 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address line 4 or the specified default value.
    */
   public final String getAddrLine4( int index, String defaultValue )
   {
      return _AddrLine4[index] == null ? defaultValue : _AddrLine4[index];
   }
    
   /**
    * Gets the array of Address line 4 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address line 4 values.
    */
   public final String[] getAddrLine4Array()
   {
      return _AddrLine4;
   }
    
   /**
    * Gets the Address line 5 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address line 5 or null.
    */
   public final String getAddrLine5( int index )
   {
      return _AddrLine5[index];
   }
    
   /**
    * Gets the Address line 5 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address line 5 or the specified default value.
    */
   public final String getAddrLine5( int index, String defaultValue )
   {
      return _AddrLine5[index] == null ? defaultValue : _AddrLine5[index];
   }
    
   /**
    * Gets the array of Address line 5 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address line 5 values.
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
    * Gets the Confirm field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Confirm or null.
    */
   public final Boolean getConfirm( int index )
   {
      return _Confirm[index];
   }
    
   /**
    * Gets the Confirm field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Confirm or the specified default value.
    */
   public final boolean getConfirm( int index, boolean defaultValue )
   {
      return _Confirm[index] == null ? defaultValue : _Confirm[index].booleanValue();
   }
    
   /**
    * Gets the array of Confirm fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Confirm values.
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
    * Gets the Modify Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Modify Date or null.
    */
   public final Date getModDate( int index )
   {
      return _ModDate[index];
   }
    
   /**
    * Gets the Modify Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Modify Date or the specified default value.
    */
   public final Date getModDate( int index, Date defaultValue )
   {
      return _ModDate[index] == null ? defaultValue : _ModDate[index];
   }
    
   /**
    * Gets the array of Modify Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Modify Date values.
    */
   public final Date[] getModDateArray()
   {
      return _ModDate;
   }
    
   /**
    * Gets the User Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the User Name or null.
    */
   public final String getUserName( int index )
   {
      return _UserName[index];
   }
    
   /**
    * Gets the User Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the User Name or the specified default value.
    */
   public final String getUserName( int index, String defaultValue )
   {
      return _UserName[index] == null ? defaultValue : _UserName[index];
   }
    
   /**
    * Gets the array of User Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of User Name values.
    */
   public final String[] getUserNameArray()
   {
      return _UserName;
   }
    
   /**
    * Gets the ModUser field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ModUser or null.
    */
   public final String getModUser( int index )
   {
      return _ModUser[index];
   }
    
   /**
    * Gets the ModUser field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ModUser or the specified default value.
    */
   public final String getModUser( int index, String defaultValue )
   {
      return _ModUser[index] == null ? defaultValue : _ModUser[index];
   }
    
   /**
    * Gets the array of ModUser fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ModUser values.
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
    * Gets the Address File Version field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address File Version or null.
    */
   public final Integer getAddressFileVer( int index )
   {
      return _AddressFileVer[index];
   }
    
   /**
    * Gets the Address File Version field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address File Version or the specified default value.
    */
   public final int getAddressFileVer( int index, int defaultValue )
   {
      return _AddressFileVer[index] == null ? defaultValue : _AddressFileVer[index].intValue();
   }
    
   /**
    * Gets the array of Address File Version fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address File Version values.
    */
   public final Integer[] getAddressFileVerArray()
   {
      return _AddressFileVer;
   }
    
   /**
    * Gets the Address File RID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address File RID or null.
    */
   public final Integer getAddressFileRID( int index )
   {
      return _AddressFileRID[index];
   }
    
   /**
    * Gets the Address File RID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address File RID or the specified default value.
    */
   public final int getAddressFileRID( int index, int defaultValue )
   {
      return _AddressFileRID[index] == null ? defaultValue : _AddressFileRID[index].intValue();
   }
    
   /**
    * Gets the array of Address File RID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address File RID values.
    */
   public final Integer[] getAddressFileRIDArray()
   {
      return _AddressFileRID;
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
    * Gets the RegAddrCode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RegAddrCode or null.
    */
   public final String getRegAddrCode( int index )
   {
      return _RegAddrCode[index];
   }
    
   /**
    * Gets the RegAddrCode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RegAddrCode or the specified default value.
    */
   public final String getRegAddrCode( int index, String defaultValue )
   {
      return _RegAddrCode[index] == null ? defaultValue : _RegAddrCode[index];
   }
    
   /**
    * Gets the array of RegAddrCode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RegAddrCode values.
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
    * Gets the Ret Mail Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Ret Mail Date or null.
    */
   public final Date getRetMailDate( int index )
   {
      return _RetMailDate[index];
   }
    
   /**
    * Gets the Ret Mail Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Ret Mail Date or the specified default value.
    */
   public final Date getRetMailDate( int index, Date defaultValue )
   {
      return _RetMailDate[index] == null ? defaultValue : _RetMailDate[index];
   }
    
   /**
    * Gets the array of Ret Mail Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Ret Mail Date values.
    */
   public final Date[] getRetMailDateArray()
   {
      return _RetMailDate;
   }
    
   /**
    * Gets the Ret Mail Flag field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Ret Mail Flag or null.
    */
   public final Boolean getRetMailFlag( int index )
   {
      return _RetMailFlag[index];
   }
    
   /**
    * Gets the Ret Mail Flag field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Ret Mail Flag or the specified default value.
    */
   public final boolean getRetMailFlag( int index, boolean defaultValue )
   {
      return _RetMailFlag[index] == null ? defaultValue : _RetMailFlag[index].booleanValue();
   }
    
   /**
    * Gets the array of Ret Mail Flag fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Ret Mail Flag values.
    */
   public final Boolean[] getRetMailFlagArray()
   {
      return _RetMailFlag;
   }
    
   /**
    * Gets the On Hold field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the On Hold or null.
    */
   public final Boolean getOnHold( int index )
   {
      return _OnHold[index];
   }
    
   /**
    * Gets the On Hold field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the On Hold or the specified default value.
    */
   public final boolean getOnHold( int index, boolean defaultValue )
   {
      return _OnHold[index] == null ? defaultValue : _OnHold[index].booleanValue();
   }
    
   /**
    * Gets the array of On Hold fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of On Hold values.
    */
   public final Boolean[] getOnHoldArray()
   {
      return _OnHold;
   }
    
   /**
    * Gets the Suppress field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Suppress or null.
    */
   public final String getSuppress( int index )
   {
      return _Suppress[index];
   }
    
   /**
    * Gets the Suppress field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Suppress or the specified default value.
    */
   public final String getSuppress( int index, String defaultValue )
   {
      return _Suppress[index] == null ? defaultValue : _Suppress[index];
   }
    
   /**
    * Gets the array of Suppress fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Suppress values.
    */
   public final String[] getSuppressArray()
   {
      return _Suppress;
   }
    
   /**
    * Gets the Waive field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Waive or null.
    */
   public final String getWaive( int index )
   {
      return _Waive[index];
   }
    
   /**
    * Gets the Waive field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Waive or the specified default value.
    */
   public final String getWaive( int index, String defaultValue )
   {
      return _Waive[index] == null ? defaultValue : _Waive[index];
   }
    
   /**
    * Gets the array of Waive fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Waive values.
    */
   public final String[] getWaiveArray()
   {
      return _Waive;
   }
    
   /**
    * Gets the Mail field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Mail or null.
    */
   public final String getMail( int index )
   {
      return _Mail[index];
   }
    
   /**
    * Gets the Mail field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Mail or the specified default value.
    */
   public final String getMail( int index, String defaultValue )
   {
      return _Mail[index] == null ? defaultValue : _Mail[index];
   }
    
   /**
    * Gets the array of Mail fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Mail values.
    */
   public final String[] getMailArray()
   {
      return _Mail;
   }
    
   /**
    * Gets the Fax field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fax or null.
    */
   public final String getFax( int index )
   {
      return _Fax[index];
   }
    
   /**
    * Gets the Fax field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fax or the specified default value.
    */
   public final String getFax( int index, String defaultValue )
   {
      return _Fax[index] == null ? defaultValue : _Fax[index];
   }
    
   /**
    * Gets the array of Fax fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fax values.
    */
   public final String[] getFaxArray()
   {
      return _Fax;
   }
    
   /**
    * Gets the CD field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the CD or null.
    */
   public final String getCD( int index )
   {
      return _CD[index];
   }
    
   /**
    * Gets the CD field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the CD or the specified default value.
    */
   public final String getCD( int index, String defaultValue )
   {
      return _CD[index] == null ? defaultValue : _CD[index];
   }
    
   /**
    * Gets the array of CD fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of CD values.
    */
   public final String[] getCDArray()
   {
      return _CD;
   }
    
   /**
    * Gets the EMail field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the EMail or null.
    */
   public final String getEmail( int index )
   {
      return _Email[index];
   }
    
   /**
    * Gets the EMail field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the EMail or the specified default value.
    */
   public final String getEmail( int index, String defaultValue )
   {
      return _Email[index] == null ? defaultValue : _Email[index];
   }
    
   /**
    * Gets the array of EMail fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of EMail values.
    */
   public final String[] getEmailArray()
   {
      return _Email;
   }
    
   /**
    * Gets the EPost field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the EPost or null.
    */
   public final String getEpost( int index )
   {
      return _Epost[index];
   }
    
   /**
    * Gets the EPost field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the EPost or the specified default value.
    */
   public final String getEpost( int index, String defaultValue )
   {
      return _Epost[index] == null ? defaultValue : _Epost[index];
   }
    
   /**
    * Gets the array of EPost fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of EPost values.
    */
   public final String[] getEpostArray()
   {
      return _Epost;
   }
    
   /**
    * Gets the Auth field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Auth or null.
    */
   public final String getAuth( int index )
   {
      return _Auth[index];
   }
    
   /**
    * Gets the Auth field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Auth or the specified default value.
    */
   public final String getAuth( int index, String defaultValue )
   {
      return _Auth[index] == null ? defaultValue : _Auth[index];
   }
    
   /**
    * Gets the array of Auth fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Auth values.
    */
   public final String[] getAuthArray()
   {
      return _Auth;
   }
    
   /**
    * Gets the Number of Copies field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Number of Copies or null.
    */
   public final Integer getCopies( int index )
   {
      return _Copies[index];
   }
    
   /**
    * Gets the Number of Copies field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Number of Copies or the specified default value.
    */
   public final int getCopies( int index, int defaultValue )
   {
      return _Copies[index] == null ? defaultValue : _Copies[index].intValue();
   }
    
   /**
    * Gets the array of Number of Copies fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Number of Copies values.
    */
   public final Integer[] getCopiesArray()
   {
      return _Copies;
   }
    
   /**
    * Gets the SA Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SA Code or null.
    */
   public final String getSACode( int index )
   {
      return _SACode[index];
   }
    
   /**
    * Gets the SA Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SA Code or the specified default value.
    */
   public final String getSACode( int index, String defaultValue )
   {
      return _SACode[index] == null ? defaultValue : _SACode[index];
   }
    
   /**
    * Gets the array of SA Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SA Code values.
    */
   public final String[] getSACodeArray()
   {
      return _SACode;
   }
    
   /**
    * Gets the SA Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SA Description or null.
    */
   public final String getSADesc( int index )
   {
      return _SADesc[index];
   }
    
   /**
    * Gets the SA Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SA Description or the specified default value.
    */
   public final String getSADesc( int index, String defaultValue )
   {
      return _SADesc[index] == null ? defaultValue : _SADesc[index];
   }
    
   /**
    * Gets the array of SA Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SA Description values.
    */
   public final String[] getSADescArray()
   {
      return _SADesc;
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
      int oldRspRepeatCount = _RspRepeatCount;
      decodeRspRepeatCount( responseBuffer );
      
      _rxDocumentType = resizeArray( _rxDocumentType, _RspRepeatCount );
      _AddrCode = resizeArray( _AddrCode, _RspRepeatCount );
      _AddrCodeDesc = resizeArray( _AddrCodeDesc, _RspRepeatCount );
      _Name1 = resizeArray( _Name1, _RspRepeatCount );
      _Name2 = resizeArray( _Name2, _RspRepeatCount );
      _AddrLine1 = resizeArray( _AddrLine1, _RspRepeatCount );
      _AddrLine2 = resizeArray( _AddrLine2, _RspRepeatCount );
      _AddrLine3 = resizeArray( _AddrLine3, _RspRepeatCount );
      _AddrLine4 = resizeArray( _AddrLine4, _RspRepeatCount );
      _AddrLine5 = resizeArray( _AddrLine5, _RspRepeatCount );
      _PostalCode = resizeArray( _PostalCode, _RspRepeatCount );
      _CountryCode = resizeArray( _CountryCode, _RspRepeatCount );
      _CountryName = resizeArray( _CountryName, _RspRepeatCount );
      _Confirm = resizeArray( _Confirm, _RspRepeatCount );
      _EffectiveDate = resizeArray( _EffectiveDate, _RspRepeatCount );
      _StopDate = resizeArray( _StopDate, _RspRepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RspRepeatCount );
      _ModDate = resizeArray( _ModDate, _RspRepeatCount );
      _UserName = resizeArray( _UserName, _RspRepeatCount );
      _ModUser = resizeArray( _ModUser, _RspRepeatCount );
      _City = resizeArray( _City, _RspRepeatCount );
      _Salutation = resizeArray( _Salutation, _RspRepeatCount );
      _AddressFileVer = resizeArray( _AddressFileVer, _RspRepeatCount );
      _AddressFileRID = resizeArray( _AddressFileRID, _RspRepeatCount );
      _AddrStatus = resizeArray( _AddrStatus, _RspRepeatCount );
      _RegAddrCode = resizeArray( _RegAddrCode, _RspRepeatCount );
      _Province = resizeArray( _Province, _RspRepeatCount );
      _RetMailDate = resizeArray( _RetMailDate, _RspRepeatCount );
      _RetMailFlag = resizeArray( _RetMailFlag, _RspRepeatCount );
      _OnHold = resizeArray( _OnHold, _RspRepeatCount );
      _Suppress = resizeArray( _Suppress, _RspRepeatCount );
      _Waive = resizeArray( _Waive, _RspRepeatCount );
      _Mail = resizeArray( _Mail, _RspRepeatCount );
      _Fax = resizeArray( _Fax, _RspRepeatCount );
      _CD = resizeArray( _CD, _RspRepeatCount );
      _Email = resizeArray( _Email, _RspRepeatCount );
      _Epost = resizeArray( _Epost, _RspRepeatCount );
      _Auth = resizeArray( _Auth, _RspRepeatCount );
      _Copies = resizeArray( _Copies, _RspRepeatCount );
      _SACode = resizeArray( _SACode, _RspRepeatCount );
      _SADesc = resizeArray( _SADesc, _RspRepeatCount );
        
      for (int x = oldRspRepeatCount ; x < _RspRepeatCount; x++)
      {
         _rxDocumentType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
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
         _UserName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _City[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Salutation[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddressFileVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _AddressFileRID[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _AddrStatus[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _RegAddrCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Province[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RetMailDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _RetMailFlag[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _OnHold[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _Suppress[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Waive[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Mail[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Fax[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CD[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Email[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Epost[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Auth[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Copies[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _SACode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SADesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
