
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * AMS Allowable Transfers Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/AllowTfrInq.doc">AllowTfrInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class AllowTfrInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * To Fund member array.
    */
   private String[] _ToFund = null;
   
   /**
    * To Class member array.
    */
   private String[] _ToClass = null;
   
   /**
    * Rebalance member array.
    */
   private String[] _Rebalancing = null;
   
   /**
    * From Fund member array.
    */
   private String[] _FromFund = null;
   
   /**
    * From Class member array.
    */
   private String[] _FromClass = null;
   

   /**
    * Constructs the AllowTfrInqView object.
    * 
    */
   public AllowTfrInqView()
   {
      super ( new AllowTfrInqRequest() );
   }

   /**
    * Constructs the AllowTfrInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AllowTfrInqView( String hostEncoding )
   {
      super ( new AllowTfrInqRequest( hostEncoding ) );
   }

   /**
    * Gets the AllowTfrInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AllowTfrInqRequest object.
    */
   public final AllowTfrInqRequest getRequest()
   {
      return (AllowTfrInqRequest)getIFastRequest();
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
    * Gets the To Fund field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the To Fund or null.
    */
   public final String getToFund( int index )
   {
      return _ToFund[index];
   }
    
   /**
    * Gets the To Fund field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the To Fund or the specified default value.
    */
   public final String getToFund( int index, String defaultValue )
   {
      return _ToFund[index] == null ? defaultValue : _ToFund[index];
   }
    
   /**
    * Gets the array of To Fund fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of To Fund values.
    */
   public final String[] getToFundArray()
   {
      return _ToFund;
   }
    
   /**
    * Gets the To Class field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the To Class or null.
    */
   public final String getToClass( int index )
   {
      return _ToClass[index];
   }
    
   /**
    * Gets the To Class field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the To Class or the specified default value.
    */
   public final String getToClass( int index, String defaultValue )
   {
      return _ToClass[index] == null ? defaultValue : _ToClass[index];
   }
    
   /**
    * Gets the array of To Class fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of To Class values.
    */
   public final String[] getToClassArray()
   {
      return _ToClass;
   }
    
   /**
    * Gets the Rebalance field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Rebalance or null.
    */
   public final String getRebalancing( int index )
   {
      return _Rebalancing[index];
   }
    
   /**
    * Gets the Rebalance field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Rebalance or the specified default value.
    */
   public final String getRebalancing( int index, String defaultValue )
   {
      return _Rebalancing[index] == null ? defaultValue : _Rebalancing[index];
   }
    
   /**
    * Gets the array of Rebalance fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Rebalance values.
    */
   public final String[] getRebalancingArray()
   {
      return _Rebalancing;
   }
    
   /**
    * Gets the From Fund field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the From Fund or null.
    */
   public final String getFromFund( int index )
   {
      return _FromFund[index];
   }
    
   /**
    * Gets the From Fund field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the From Fund or the specified default value.
    */
   public final String getFromFund( int index, String defaultValue )
   {
      return _FromFund[index] == null ? defaultValue : _FromFund[index];
   }
    
   /**
    * Gets the array of From Fund fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of From Fund values.
    */
   public final String[] getFromFundArray()
   {
      return _FromFund;
   }
    
   /**
    * Gets the From Class field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the From Class or null.
    */
   public final String getFromClass( int index )
   {
      return _FromClass[index];
   }
    
   /**
    * Gets the From Class field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the From Class or the specified default value.
    */
   public final String getFromClass( int index, String defaultValue )
   {
      return _FromClass[index] == null ? defaultValue : _FromClass[index];
   }
    
   /**
    * Gets the array of From Class fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of From Class values.
    */
   public final String[] getFromClassArray()
   {
      return _FromClass;
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
      _Rebalancing = resizeArray( _Rebalancing, _RepeatCount );
      _FromFund = resizeArray( _FromFund, _RepeatCount );
      _FromClass = resizeArray( _FromClass, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _ToFund[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ToClass[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Rebalancing[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FromFund[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FromClass[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
