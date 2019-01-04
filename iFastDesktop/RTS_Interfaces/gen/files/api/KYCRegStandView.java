
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * KYC Regulatory Standards view.
 * For additional view information see <A HREF="../../../../viewspecs/KYCRegStand.doc">KYCRegStand.doc</A>.
 * 
 * @author RTS Generated
 */
public class KYCRegStandView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Regulatory Standard Description member array.
    */
   private String[] _Description = null;
   
   /**
    * ID of the Regulatory Standard member array.
    */
   private String[] _ComplyCodeID = null;
   

   /**
    * Constructs the KYCRegStandView object.
    * 
    */
   public KYCRegStandView()
   {
      super ( new KYCRegStandRequest() );
   }

   /**
    * Constructs the KYCRegStandView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public KYCRegStandView( String hostEncoding )
   {
      super ( new KYCRegStandRequest( hostEncoding ) );
   }

   /**
    * Gets the KYCRegStandRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The KYCRegStandRequest object.
    */
   public final KYCRegStandRequest getRequest()
   {
      return (KYCRegStandRequest)getIFastRequest();
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
    * Gets the Regulatory Standard Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Regulatory Standard Description or null.
    */
   public final String getDescription( int index )
   {
      return _Description[index];
   }
    
   /**
    * Gets the Regulatory Standard Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Regulatory Standard Description or the specified default value.
    */
   public final String getDescription( int index, String defaultValue )
   {
      return _Description[index] == null ? defaultValue : _Description[index];
   }
    
   /**
    * Gets the array of Regulatory Standard Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Regulatory Standard Description values.
    */
   public final String[] getDescriptionArray()
   {
      return _Description;
   }
    
   /**
    * Gets the ID of the Regulatory Standard field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ID of the Regulatory Standard or null.
    */
   public final String getComplyCodeID( int index )
   {
      return _ComplyCodeID[index];
   }
    
   /**
    * Gets the ID of the Regulatory Standard field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ID of the Regulatory Standard or the specified default value.
    */
   public final String getComplyCodeID( int index, String defaultValue )
   {
      return _ComplyCodeID[index] == null ? defaultValue : _ComplyCodeID[index];
   }
    
   /**
    * Gets the array of ID of the Regulatory Standard fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ID of the Regulatory Standard values.
    */
   public final String[] getComplyCodeIDArray()
   {
      return _ComplyCodeID;
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
      
      _Description = resizeArray( _Description, _RepeatCount );
      _ComplyCodeID = resizeArray( _ComplyCodeID, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _Description[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ComplyCodeID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
