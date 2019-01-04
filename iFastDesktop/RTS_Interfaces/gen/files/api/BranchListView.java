
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Branch List Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/BranchList.doc">BranchList.doc</A>.
 * 
 * @author RTS Generated
 */
public class BranchListView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * rxBranchCode member array.
    */
   private String[] _rxBranchCode = null;
   
   /**
    * Branch Name member array.
    */
   private String[] _BranchName = null;
   
   /**
    * Address Line 1 member array.
    */
   private String[] _AddrLine1 = null;
   
   /**
    * Address Line 2 member array.
    */
   private String[] _AddrLine2 = null;
   
   /**
    * Address Line 3 member array.
    */
   private String[] _AddrLine3 = null;
   
   /**
    * Address Line 4 member array.
    */
   private String[] _AddrLine4 = null;
   
   /**
    * Address Line 5 member array.
    */
   private String[] _AddrLine5 = null;
   
   /**
    * Country Code member array.
    */
   private String[] _AddrCntryCode = null;
   
   /**
    * PhoneNumber member array.
    */
   private String[] _PhoneNumber = null;
   
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = null;
   
   /**
    * Stop Date member array.
    */
   private Date[] _StopDate = null;
   
   /**
    * Payment Instructions for Trailers Avail member array.
    */
   private Boolean[] _PayInstrTrailer = null;
   
   /**
    * Payment Instructions for Comm Avail member array.
    */
   private Boolean[] _PayInstrComm = null;
   
   /**
    * Postal Code member array.
    */
   private String[] _PostalCode = null;
   

   /**
    * Constructs the BranchListView object.
    * 
    */
   public BranchListView()
   {
      super ( new BranchListRequest() );
   }

   /**
    * Constructs the BranchListView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public BranchListView( String hostEncoding )
   {
      super ( new BranchListRequest( hostEncoding ) );
   }

   /**
    * Gets the BranchListRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The BranchListRequest object.
    */
   public final BranchListRequest getRequest()
   {
      return (BranchListRequest)getIFastRequest();
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
    * Gets the rxBranchCode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the rxBranchCode or null.
    */
   public final String getrxBranchCode( int index )
   {
      return _rxBranchCode[index];
   }
    
   /**
    * Gets the rxBranchCode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the rxBranchCode or the specified default value.
    */
   public final String getrxBranchCode( int index, String defaultValue )
   {
      return _rxBranchCode[index] == null ? defaultValue : _rxBranchCode[index];
   }
    
   /**
    * Gets the array of rxBranchCode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of rxBranchCode values.
    */
   public final String[] getrxBranchCodeArray()
   {
      return _rxBranchCode;
   }
    
   /**
    * Gets the Branch Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Branch Name or null.
    */
   public final String getBranchName( int index )
   {
      return _BranchName[index];
   }
    
   /**
    * Gets the Branch Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Branch Name or the specified default value.
    */
   public final String getBranchName( int index, String defaultValue )
   {
      return _BranchName[index] == null ? defaultValue : _BranchName[index];
   }
    
   /**
    * Gets the array of Branch Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Branch Name values.
    */
   public final String[] getBranchNameArray()
   {
      return _BranchName;
   }
    
   /**
    * Gets the Address Line 1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Line 1 or null.
    */
   public final String getAddrLine1( int index )
   {
      return _AddrLine1[index];
   }
    
   /**
    * Gets the Address Line 1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line 1 or the specified default value.
    */
   public final String getAddrLine1( int index, String defaultValue )
   {
      return _AddrLine1[index] == null ? defaultValue : _AddrLine1[index];
   }
    
   /**
    * Gets the array of Address Line 1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Line 1 values.
    */
   public final String[] getAddrLine1Array()
   {
      return _AddrLine1;
   }
    
   /**
    * Gets the Address Line 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Line 2 or null.
    */
   public final String getAddrLine2( int index )
   {
      return _AddrLine2[index];
   }
    
   /**
    * Gets the Address Line 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line 2 or the specified default value.
    */
   public final String getAddrLine2( int index, String defaultValue )
   {
      return _AddrLine2[index] == null ? defaultValue : _AddrLine2[index];
   }
    
   /**
    * Gets the array of Address Line 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Line 2 values.
    */
   public final String[] getAddrLine2Array()
   {
      return _AddrLine2;
   }
    
   /**
    * Gets the Address Line 3 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Line 3 or null.
    */
   public final String getAddrLine3( int index )
   {
      return _AddrLine3[index];
   }
    
   /**
    * Gets the Address Line 3 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line 3 or the specified default value.
    */
   public final String getAddrLine3( int index, String defaultValue )
   {
      return _AddrLine3[index] == null ? defaultValue : _AddrLine3[index];
   }
    
   /**
    * Gets the array of Address Line 3 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Line 3 values.
    */
   public final String[] getAddrLine3Array()
   {
      return _AddrLine3;
   }
    
   /**
    * Gets the Address Line 4 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Line 4 or null.
    */
   public final String getAddrLine4( int index )
   {
      return _AddrLine4[index];
   }
    
   /**
    * Gets the Address Line 4 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line 4 or the specified default value.
    */
   public final String getAddrLine4( int index, String defaultValue )
   {
      return _AddrLine4[index] == null ? defaultValue : _AddrLine4[index];
   }
    
   /**
    * Gets the array of Address Line 4 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Line 4 values.
    */
   public final String[] getAddrLine4Array()
   {
      return _AddrLine4;
   }
    
   /**
    * Gets the Address Line 5 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Line 5 or null.
    */
   public final String getAddrLine5( int index )
   {
      return _AddrLine5[index];
   }
    
   /**
    * Gets the Address Line 5 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line 5 or the specified default value.
    */
   public final String getAddrLine5( int index, String defaultValue )
   {
      return _AddrLine5[index] == null ? defaultValue : _AddrLine5[index];
   }
    
   /**
    * Gets the array of Address Line 5 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Line 5 values.
    */
   public final String[] getAddrLine5Array()
   {
      return _AddrLine5;
   }
    
   /**
    * Gets the Country Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Country Code or null.
    */
   public final String getAddrCntryCode( int index )
   {
      return _AddrCntryCode[index];
   }
    
   /**
    * Gets the Country Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Country Code or the specified default value.
    */
   public final String getAddrCntryCode( int index, String defaultValue )
   {
      return _AddrCntryCode[index] == null ? defaultValue : _AddrCntryCode[index];
   }
    
   /**
    * Gets the array of Country Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Country Code values.
    */
   public final String[] getAddrCntryCodeArray()
   {
      return _AddrCntryCode;
   }
    
   /**
    * Gets the PhoneNumber field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the PhoneNumber or null.
    */
   public final String getPhoneNumber( int index )
   {
      return _PhoneNumber[index];
   }
    
   /**
    * Gets the PhoneNumber field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PhoneNumber or the specified default value.
    */
   public final String getPhoneNumber( int index, String defaultValue )
   {
      return _PhoneNumber[index] == null ? defaultValue : _PhoneNumber[index];
   }
    
   /**
    * Gets the array of PhoneNumber fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of PhoneNumber values.
    */
   public final String[] getPhoneNumberArray()
   {
      return _PhoneNumber;
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
    * Gets the Payment Instructions for Trailers Avail field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Payment Instructions for Trailers Avail or null.
    */
   public final Boolean getPayInstrTrailer( int index )
   {
      return _PayInstrTrailer[index];
   }
    
   /**
    * Gets the Payment Instructions for Trailers Avail field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payment Instructions for Trailers Avail or the specified default value.
    */
   public final boolean getPayInstrTrailer( int index, boolean defaultValue )
   {
      return _PayInstrTrailer[index] == null ? defaultValue : _PayInstrTrailer[index].booleanValue();
   }
    
   /**
    * Gets the array of Payment Instructions for Trailers Avail fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Payment Instructions for Trailers Avail values.
    */
   public final Boolean[] getPayInstrTrailerArray()
   {
      return _PayInstrTrailer;
   }
    
   /**
    * Gets the Payment Instructions for Comm Avail field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Payment Instructions for Comm Avail or null.
    */
   public final Boolean getPayInstrComm( int index )
   {
      return _PayInstrComm[index];
   }
    
   /**
    * Gets the Payment Instructions for Comm Avail field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payment Instructions for Comm Avail or the specified default value.
    */
   public final boolean getPayInstrComm( int index, boolean defaultValue )
   {
      return _PayInstrComm[index] == null ? defaultValue : _PayInstrComm[index].booleanValue();
   }
    
   /**
    * Gets the array of Payment Instructions for Comm Avail fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Payment Instructions for Comm Avail values.
    */
   public final Boolean[] getPayInstrCommArray()
   {
      return _PayInstrComm;
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
      
      _rxBranchCode = resizeArray( _rxBranchCode, _RepeatCount );
      _BranchName = resizeArray( _BranchName, _RepeatCount );
      _AddrLine1 = resizeArray( _AddrLine1, _RepeatCount );
      _AddrLine2 = resizeArray( _AddrLine2, _RepeatCount );
      _AddrLine3 = resizeArray( _AddrLine3, _RepeatCount );
      _AddrLine4 = resizeArray( _AddrLine4, _RepeatCount );
      _AddrLine5 = resizeArray( _AddrLine5, _RepeatCount );
      _AddrCntryCode = resizeArray( _AddrCntryCode, _RepeatCount );
      _PhoneNumber = resizeArray( _PhoneNumber, _RepeatCount );
      _EffectiveDate = resizeArray( _EffectiveDate, _RepeatCount );
      _StopDate = resizeArray( _StopDate, _RepeatCount );
      _PayInstrTrailer = resizeArray( _PayInstrTrailer, _RepeatCount );
      _PayInstrComm = resizeArray( _PayInstrComm, _RepeatCount );
      _PostalCode = resizeArray( _PostalCode, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxBranchCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BranchName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine3[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine4[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine5[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrCntryCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PhoneNumber[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _StopDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _PayInstrTrailer[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _PayInstrComm[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _PostalCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
