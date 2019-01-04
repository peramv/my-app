
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * LSIF Redemption Rules view.
 * For additional view information see <A HREF="../../../../viewspecs/LSIFRedRules.doc">LSIFRedRules.doc</A>.
 * 
 * @author RTS Generated
 */
public class LSIFRedRulesView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * LSIFCodes member array.
    */
   private String[] _LSIFCodes = null;
   
   /**
    * Description member array.
    */
   private String[] _Description = null;
   
   /**
    * AvailOnInput member array.
    */
   private Integer[] _AvailOnInput = null;
   
   /**
    * DSCOverrideCode member array.
    */
   private String[] _DSCOverrideCode = null;
   

   /**
    * Constructs the LSIFRedRulesView object.
    * 
    */
   public LSIFRedRulesView()
   {
      super ( new LSIFRedRulesRequest() );
   }

   /**
    * Constructs the LSIFRedRulesView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public LSIFRedRulesView( String hostEncoding )
   {
      super ( new LSIFRedRulesRequest( hostEncoding ) );
   }

   /**
    * Gets the LSIFRedRulesRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The LSIFRedRulesRequest object.
    */
   public final LSIFRedRulesRequest getRequest()
   {
      return (LSIFRedRulesRequest)getIFastRequest();
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
    * Gets the LSIFCodes field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the LSIFCodes or null.
    */
   public final String getLSIFCodes( int index )
   {
      return _LSIFCodes[index];
   }
    
   /**
    * Gets the LSIFCodes field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the LSIFCodes or the specified default value.
    */
   public final String getLSIFCodes( int index, String defaultValue )
   {
      return _LSIFCodes[index] == null ? defaultValue : _LSIFCodes[index];
   }
    
   /**
    * Gets the array of LSIFCodes fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of LSIFCodes values.
    */
   public final String[] getLSIFCodesArray()
   {
      return _LSIFCodes;
   }
    
   /**
    * Gets the Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Description or null.
    */
   public final String getDescription( int index )
   {
      return _Description[index];
   }
    
   /**
    * Gets the Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Description or the specified default value.
    */
   public final String getDescription( int index, String defaultValue )
   {
      return _Description[index] == null ? defaultValue : _Description[index];
   }
    
   /**
    * Gets the array of Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Description values.
    */
   public final String[] getDescriptionArray()
   {
      return _Description;
   }
    
   /**
    * Gets the AvailOnInput field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AvailOnInput or null.
    */
   public final Integer getAvailOnInput( int index )
   {
      return _AvailOnInput[index];
   }
    
   /**
    * Gets the AvailOnInput field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AvailOnInput or the specified default value.
    */
   public final int getAvailOnInput( int index, int defaultValue )
   {
      return _AvailOnInput[index] == null ? defaultValue : _AvailOnInput[index].intValue();
   }
    
   /**
    * Gets the array of AvailOnInput fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AvailOnInput values.
    */
   public final Integer[] getAvailOnInputArray()
   {
      return _AvailOnInput;
   }
    
   /**
    * Gets the DSCOverrideCode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the DSCOverrideCode or null.
    */
   public final String getDSCOverrideCode( int index )
   {
      return _DSCOverrideCode[index];
   }
    
   /**
    * Gets the DSCOverrideCode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the DSCOverrideCode or the specified default value.
    */
   public final String getDSCOverrideCode( int index, String defaultValue )
   {
      return _DSCOverrideCode[index] == null ? defaultValue : _DSCOverrideCode[index];
   }
    
   /**
    * Gets the array of DSCOverrideCode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of DSCOverrideCode values.
    */
   public final String[] getDSCOverrideCodeArray()
   {
      return _DSCOverrideCode;
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
      
      _LSIFCodes = resizeArray( _LSIFCodes, _RepeatCount );
      _Description = resizeArray( _Description, _RepeatCount );
      _AvailOnInput = resizeArray( _AvailOnInput, _RepeatCount );
      _DSCOverrideCode = resizeArray( _DSCOverrideCode, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _LSIFCodes[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Description[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AvailOnInput[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _DSCOverrideCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
