
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Target Allocation Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/TargetAllocInq.doc">TargetAllocInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class TargetAllocInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Fund Pool Code member array.
    */
   private String[] _FundPool = null;
   
   /**
    * Fund Pool Description member array.
    */
   private String[] _FundPoolDesc = null;
   
   /**
    * Target Alloc fund member array.
    */
   private String[] _TargetAllocFund = null;
   
   /**
    * Target Alloc class member array.
    */
   private String[] _TargetAllocClass = null;
   

   /**
    * Constructs the TargetAllocInqView object.
    * 
    */
   public TargetAllocInqView()
   {
      super ( new TargetAllocInqRequest() );
   }

   /**
    * Constructs the TargetAllocInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public TargetAllocInqView( String hostEncoding )
   {
      super ( new TargetAllocInqRequest( hostEncoding ) );
   }

   /**
    * Gets the TargetAllocInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The TargetAllocInqRequest object.
    */
   public final TargetAllocInqRequest getRequest()
   {
      return (TargetAllocInqRequest)getIFastRequest();
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
    * Gets the Fund Pool Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Pool Code or null.
    */
   public final String getFundPool( int index )
   {
      return _FundPool[index];
   }
    
   /**
    * Gets the Fund Pool Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Pool Code or the specified default value.
    */
   public final String getFundPool( int index, String defaultValue )
   {
      return _FundPool[index] == null ? defaultValue : _FundPool[index];
   }
    
   /**
    * Gets the array of Fund Pool Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Pool Code values.
    */
   public final String[] getFundPoolArray()
   {
      return _FundPool;
   }
    
   /**
    * Gets the Fund Pool Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Pool Description or null.
    */
   public final String getFundPoolDesc( int index )
   {
      return _FundPoolDesc[index];
   }
    
   /**
    * Gets the Fund Pool Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Pool Description or the specified default value.
    */
   public final String getFundPoolDesc( int index, String defaultValue )
   {
      return _FundPoolDesc[index] == null ? defaultValue : _FundPoolDesc[index];
   }
    
   /**
    * Gets the array of Fund Pool Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Pool Description values.
    */
   public final String[] getFundPoolDescArray()
   {
      return _FundPoolDesc;
   }
    
   /**
    * Gets the Target Alloc fund field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Target Alloc fund or null.
    */
   public final String getTargetAllocFund( int index )
   {
      return _TargetAllocFund[index];
   }
    
   /**
    * Gets the Target Alloc fund field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Target Alloc fund or the specified default value.
    */
   public final String getTargetAllocFund( int index, String defaultValue )
   {
      return _TargetAllocFund[index] == null ? defaultValue : _TargetAllocFund[index];
   }
    
   /**
    * Gets the array of Target Alloc fund fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Target Alloc fund values.
    */
   public final String[] getTargetAllocFundArray()
   {
      return _TargetAllocFund;
   }
    
   /**
    * Gets the Target Alloc class field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Target Alloc class or null.
    */
   public final String getTargetAllocClass( int index )
   {
      return _TargetAllocClass[index];
   }
    
   /**
    * Gets the Target Alloc class field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Target Alloc class or the specified default value.
    */
   public final String getTargetAllocClass( int index, String defaultValue )
   {
      return _TargetAllocClass[index] == null ? defaultValue : _TargetAllocClass[index];
   }
    
   /**
    * Gets the array of Target Alloc class fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Target Alloc class values.
    */
   public final String[] getTargetAllocClassArray()
   {
      return _TargetAllocClass;
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
      
      _FundPool = resizeArray( _FundPool, _RepeatCount );
      _FundPoolDesc = resizeArray( _FundPoolDesc, _RepeatCount );
      _TargetAllocFund = resizeArray( _TargetAllocFund, _RepeatCount );
      _TargetAllocClass = resizeArray( _TargetAllocClass, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _FundPool[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundPoolDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TargetAllocFund[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TargetAllocClass[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
