
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Broker/Interm Registered Addresses Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/BrokRegAddrInq.doc">BrokRegAddrInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class BrokRegAddrInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Broker/Intermediary  Code member array.
    */
   private String[] _rxBrokerCode = null;
   
   /**
    * Broker/Intermediary Name member array.
    */
   private String[] _BrokerName = null;
   
   /**
    * Broker/Interm Registered Address Code member array.
    */
   private String[] _RegAddrCode = null;
   
   /**
    * Broker/Interm Address Line 1 member array.
    */
   private String[] _AddrLine1 = null;
   
   /**
    * Broker/Interm Address Line 2 member array.
    */
   private String[] _AddrLine2 = null;
   
   /**
    * Broker/Interm Address Line 3 member array.
    */
   private String[] _AddrLine3 = null;
   
   /**
    * Broker/Interm Address Line 4 member array.
    */
   private String[] _AddrLine4 = null;
   
   /**
    * Broker/Interm Address Line 5 member array.
    */
   private String[] _AddrLine5 = null;
   
   /**
    * Broker/Interm Country Code member array.
    */
   private String[] _AddrCntryCode = null;
   
   /**
    * Broker/Interm Postal Code member array.
    */
   private String[] _PostalCode = null;
   
   /**
    * Adcd Flag member array.
    */
   private Boolean[] _AdcdFlag = null;
   
   /**
    * Tax Type member array.
    */
   private String[] _TaxType = null;
   

   /**
    * Constructs the BrokRegAddrInqView object.
    * 
    */
   public BrokRegAddrInqView()
   {
      super ( new BrokRegAddrInqRequest() );
   }

   /**
    * Constructs the BrokRegAddrInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public BrokRegAddrInqView( String hostEncoding )
   {
      super ( new BrokRegAddrInqRequest( hostEncoding ) );
   }

   /**
    * Gets the BrokRegAddrInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The BrokRegAddrInqRequest object.
    */
   public final BrokRegAddrInqRequest getRequest()
   {
      return (BrokRegAddrInqRequest)getIFastRequest();
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
    * Gets the Broker/Intermediary  Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Broker/Intermediary  Code or null.
    */
   public final String getrxBrokerCode( int index )
   {
      return _rxBrokerCode[index];
   }
    
   /**
    * Gets the Broker/Intermediary  Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker/Intermediary  Code or the specified default value.
    */
   public final String getrxBrokerCode( int index, String defaultValue )
   {
      return _rxBrokerCode[index] == null ? defaultValue : _rxBrokerCode[index];
   }
    
   /**
    * Gets the array of Broker/Intermediary  Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Broker/Intermediary  Code values.
    */
   public final String[] getrxBrokerCodeArray()
   {
      return _rxBrokerCode;
   }
    
   /**
    * Gets the Broker/Intermediary Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Broker/Intermediary Name or null.
    */
   public final String getBrokerName( int index )
   {
      return _BrokerName[index];
   }
    
   /**
    * Gets the Broker/Intermediary Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker/Intermediary Name or the specified default value.
    */
   public final String getBrokerName( int index, String defaultValue )
   {
      return _BrokerName[index] == null ? defaultValue : _BrokerName[index];
   }
    
   /**
    * Gets the array of Broker/Intermediary Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Broker/Intermediary Name values.
    */
   public final String[] getBrokerNameArray()
   {
      return _BrokerName;
   }
    
   /**
    * Gets the Broker/Interm Registered Address Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Broker/Interm Registered Address Code or null.
    */
   public final String getRegAddrCode( int index )
   {
      return _RegAddrCode[index];
   }
    
   /**
    * Gets the Broker/Interm Registered Address Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker/Interm Registered Address Code or the specified default value.
    */
   public final String getRegAddrCode( int index, String defaultValue )
   {
      return _RegAddrCode[index] == null ? defaultValue : _RegAddrCode[index];
   }
    
   /**
    * Gets the array of Broker/Interm Registered Address Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Broker/Interm Registered Address Code values.
    */
   public final String[] getRegAddrCodeArray()
   {
      return _RegAddrCode;
   }
    
   /**
    * Gets the Broker/Interm Address Line 1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Broker/Interm Address Line 1 or null.
    */
   public final String getAddrLine1( int index )
   {
      return _AddrLine1[index];
   }
    
   /**
    * Gets the Broker/Interm Address Line 1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker/Interm Address Line 1 or the specified default value.
    */
   public final String getAddrLine1( int index, String defaultValue )
   {
      return _AddrLine1[index] == null ? defaultValue : _AddrLine1[index];
   }
    
   /**
    * Gets the array of Broker/Interm Address Line 1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Broker/Interm Address Line 1 values.
    */
   public final String[] getAddrLine1Array()
   {
      return _AddrLine1;
   }
    
   /**
    * Gets the Broker/Interm Address Line 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Broker/Interm Address Line 2 or null.
    */
   public final String getAddrLine2( int index )
   {
      return _AddrLine2[index];
   }
    
   /**
    * Gets the Broker/Interm Address Line 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker/Interm Address Line 2 or the specified default value.
    */
   public final String getAddrLine2( int index, String defaultValue )
   {
      return _AddrLine2[index] == null ? defaultValue : _AddrLine2[index];
   }
    
   /**
    * Gets the array of Broker/Interm Address Line 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Broker/Interm Address Line 2 values.
    */
   public final String[] getAddrLine2Array()
   {
      return _AddrLine2;
   }
    
   /**
    * Gets the Broker/Interm Address Line 3 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Broker/Interm Address Line 3 or null.
    */
   public final String getAddrLine3( int index )
   {
      return _AddrLine3[index];
   }
    
   /**
    * Gets the Broker/Interm Address Line 3 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker/Interm Address Line 3 or the specified default value.
    */
   public final String getAddrLine3( int index, String defaultValue )
   {
      return _AddrLine3[index] == null ? defaultValue : _AddrLine3[index];
   }
    
   /**
    * Gets the array of Broker/Interm Address Line 3 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Broker/Interm Address Line 3 values.
    */
   public final String[] getAddrLine3Array()
   {
      return _AddrLine3;
   }
    
   /**
    * Gets the Broker/Interm Address Line 4 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Broker/Interm Address Line 4 or null.
    */
   public final String getAddrLine4( int index )
   {
      return _AddrLine4[index];
   }
    
   /**
    * Gets the Broker/Interm Address Line 4 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker/Interm Address Line 4 or the specified default value.
    */
   public final String getAddrLine4( int index, String defaultValue )
   {
      return _AddrLine4[index] == null ? defaultValue : _AddrLine4[index];
   }
    
   /**
    * Gets the array of Broker/Interm Address Line 4 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Broker/Interm Address Line 4 values.
    */
   public final String[] getAddrLine4Array()
   {
      return _AddrLine4;
   }
    
   /**
    * Gets the Broker/Interm Address Line 5 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Broker/Interm Address Line 5 or null.
    */
   public final String getAddrLine5( int index )
   {
      return _AddrLine5[index];
   }
    
   /**
    * Gets the Broker/Interm Address Line 5 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker/Interm Address Line 5 or the specified default value.
    */
   public final String getAddrLine5( int index, String defaultValue )
   {
      return _AddrLine5[index] == null ? defaultValue : _AddrLine5[index];
   }
    
   /**
    * Gets the array of Broker/Interm Address Line 5 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Broker/Interm Address Line 5 values.
    */
   public final String[] getAddrLine5Array()
   {
      return _AddrLine5;
   }
    
   /**
    * Gets the Broker/Interm Country Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Broker/Interm Country Code or null.
    */
   public final String getAddrCntryCode( int index )
   {
      return _AddrCntryCode[index];
   }
    
   /**
    * Gets the Broker/Interm Country Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker/Interm Country Code or the specified default value.
    */
   public final String getAddrCntryCode( int index, String defaultValue )
   {
      return _AddrCntryCode[index] == null ? defaultValue : _AddrCntryCode[index];
   }
    
   /**
    * Gets the array of Broker/Interm Country Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Broker/Interm Country Code values.
    */
   public final String[] getAddrCntryCodeArray()
   {
      return _AddrCntryCode;
   }
    
   /**
    * Gets the Broker/Interm Postal Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Broker/Interm Postal Code or null.
    */
   public final String getPostalCode( int index )
   {
      return _PostalCode[index];
   }
    
   /**
    * Gets the Broker/Interm Postal Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker/Interm Postal Code or the specified default value.
    */
   public final String getPostalCode( int index, String defaultValue )
   {
      return _PostalCode[index] == null ? defaultValue : _PostalCode[index];
   }
    
   /**
    * Gets the array of Broker/Interm Postal Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Broker/Interm Postal Code values.
    */
   public final String[] getPostalCodeArray()
   {
      return _PostalCode;
   }
    
   /**
    * Gets the Adcd Flag field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Adcd Flag or null.
    */
   public final Boolean getAdcdFlag( int index )
   {
      return _AdcdFlag[index];
   }
    
   /**
    * Gets the Adcd Flag field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Adcd Flag or the specified default value.
    */
   public final boolean getAdcdFlag( int index, boolean defaultValue )
   {
      return _AdcdFlag[index] == null ? defaultValue : _AdcdFlag[index].booleanValue();
   }
    
   /**
    * Gets the array of Adcd Flag fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Adcd Flag values.
    */
   public final Boolean[] getAdcdFlagArray()
   {
      return _AdcdFlag;
   }
    
   /**
    * Gets the Tax Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax Type or null.
    */
   public final String getTaxType( int index )
   {
      return _TaxType[index];
   }
    
   /**
    * Gets the Tax Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Type or the specified default value.
    */
   public final String getTaxType( int index, String defaultValue )
   {
      return _TaxType[index] == null ? defaultValue : _TaxType[index];
   }
    
   /**
    * Gets the array of Tax Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax Type values.
    */
   public final String[] getTaxTypeArray()
   {
      return _TaxType;
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
      
      _rxBrokerCode = resizeArray( _rxBrokerCode, _RepeatCount );
      _BrokerName = resizeArray( _BrokerName, _RepeatCount );
      _RegAddrCode = resizeArray( _RegAddrCode, _RepeatCount );
      _AddrLine1 = resizeArray( _AddrLine1, _RepeatCount );
      _AddrLine2 = resizeArray( _AddrLine2, _RepeatCount );
      _AddrLine3 = resizeArray( _AddrLine3, _RepeatCount );
      _AddrLine4 = resizeArray( _AddrLine4, _RepeatCount );
      _AddrLine5 = resizeArray( _AddrLine5, _RepeatCount );
      _AddrCntryCode = resizeArray( _AddrCntryCode, _RepeatCount );
      _PostalCode = resizeArray( _PostalCode, _RepeatCount );
      _AdcdFlag = resizeArray( _AdcdFlag, _RepeatCount );
      _TaxType = resizeArray( _TaxType, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxBrokerCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BrokerName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RegAddrCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine3[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine4[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine5[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrCntryCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PostalCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AdcdFlag[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TaxType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
