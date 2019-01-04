
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Transaction External Ids view.
 * For additional view information see <A HREF="../../../../viewspecs/TransExtId.doc">TransExtId.doc</A>.
 * 
 * @author RTS Generated
 */
public class TransExtIdView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * External Id Type member array.
    */
   private String[] _ExtIdType = null;
   
   /**
    * External Id member array.
    */
   private String[] _ExternalId = null;
   

   /**
    * Constructs the TransExtIdView object.
    * 
    */
   public TransExtIdView()
   {
      super ( new TransExtIdRequest() );
   }

   /**
    * Constructs the TransExtIdView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public TransExtIdView( String hostEncoding )
   {
      super ( new TransExtIdRequest( hostEncoding ) );
   }

   /**
    * Gets the TransExtIdRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The TransExtIdRequest object.
    */
   public final TransExtIdRequest getRequest()
   {
      return (TransExtIdRequest)getIFastRequest();
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
    * Gets the External Id Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the External Id Type or null.
    */
   public final String getExtIdType( int index )
   {
      return _ExtIdType[index];
   }
    
   /**
    * Gets the External Id Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the External Id Type or the specified default value.
    */
   public final String getExtIdType( int index, String defaultValue )
   {
      return _ExtIdType[index] == null ? defaultValue : _ExtIdType[index];
   }
    
   /**
    * Gets the array of External Id Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of External Id Type values.
    */
   public final String[] getExtIdTypeArray()
   {
      return _ExtIdType;
   }
    
   /**
    * Gets the External Id field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the External Id or null.
    */
   public final String getExternalId( int index )
   {
      return _ExternalId[index];
   }
    
   /**
    * Gets the External Id field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the External Id or the specified default value.
    */
   public final String getExternalId( int index, String defaultValue )
   {
      return _ExternalId[index] == null ? defaultValue : _ExternalId[index];
   }
    
   /**
    * Gets the array of External Id fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of External Id values.
    */
   public final String[] getExternalIdArray()
   {
      return _ExternalId;
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
      
      _ExtIdType = resizeArray( _ExtIdType, _RepeatCount );
      _ExternalId = resizeArray( _ExternalId, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _ExtIdType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ExternalId[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
