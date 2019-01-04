
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * LSIF RollOver Rules view.
 * For additional view information see <A HREF="../../../../viewspecs/LSIFRollOver.doc">LSIFRollOver.doc</A>.
 * 
 * @author RTS Generated
 */
public class LSIFRollOverView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * ToFund member array.
    */
   private String[] _ToFund = null;
   
   /**
    * ToClass member array.
    */
   private String[] _ToClass = null;
   

   /**
    * Constructs the LSIFRollOverView object.
    * 
    */
   public LSIFRollOverView()
   {
      super ( new LSIFRollOverRequest() );
   }

   /**
    * Constructs the LSIFRollOverView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public LSIFRollOverView( String hostEncoding )
   {
      super ( new LSIFRollOverRequest( hostEncoding ) );
   }

   /**
    * Gets the LSIFRollOverRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The LSIFRollOverRequest object.
    */
   public final LSIFRollOverRequest getRequest()
   {
      return (LSIFRollOverRequest)getIFastRequest();
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
    * Gets the ToFund field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ToFund or null.
    */
   public final String getToFund( int index )
   {
      return _ToFund[index];
   }
    
   /**
    * Gets the ToFund field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ToFund or the specified default value.
    */
   public final String getToFund( int index, String defaultValue )
   {
      return _ToFund[index] == null ? defaultValue : _ToFund[index];
   }
    
   /**
    * Gets the array of ToFund fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ToFund values.
    */
   public final String[] getToFundArray()
   {
      return _ToFund;
   }
    
   /**
    * Gets the ToClass field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ToClass or null.
    */
   public final String getToClass( int index )
   {
      return _ToClass[index];
   }
    
   /**
    * Gets the ToClass field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ToClass or the specified default value.
    */
   public final String getToClass( int index, String defaultValue )
   {
      return _ToClass[index] == null ? defaultValue : _ToClass[index];
   }
    
   /**
    * Gets the array of ToClass fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ToClass values.
    */
   public final String[] getToClassArray()
   {
      return _ToClass;
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
      
      _ToFund = resizeArray( _ToFund, _RepeatCount );
      _ToClass = resizeArray( _ToClass, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _ToFund[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ToClass[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
