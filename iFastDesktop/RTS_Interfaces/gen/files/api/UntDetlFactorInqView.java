
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Unit Detail Factor Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/UntDetlFactorInq.doc">UntDetlFactorInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class UntDetlFactorInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Unit ID in response member array.
    */
   private Integer[] _rxUnitID = null;
   
   /**
    * Factor Code member array.
    */
   private String[] _FactorCode = null;
   
   /**
    * Factor Description member array.
    */
   private String[] _FactorDesc = null;
   
   /**
    * Factor Amount member array.
    */
   private String[] _FactorAmount = null;
   
   /**
    * Rate Period member array.
    */
   private String[] _RatePeriod = null;
   

   /**
    * Constructs the UntDetlFactorInqView object.
    * 
    */
   public UntDetlFactorInqView()
   {
      super ( new UntDetlFactorInqRequest() );
   }

   /**
    * Constructs the UntDetlFactorInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public UntDetlFactorInqView( String hostEncoding )
   {
      super ( new UntDetlFactorInqRequest( hostEncoding ) );
   }

   /**
    * Gets the UntDetlFactorInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The UntDetlFactorInqRequest object.
    */
   public final UntDetlFactorInqRequest getRequest()
   {
      return (UntDetlFactorInqRequest)getIFastRequest();
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
    * Gets the Unit ID in response field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Unit ID in response or null.
    */
   public final Integer getrxUnitID( int index )
   {
      return _rxUnitID[index];
   }
    
   /**
    * Gets the Unit ID in response field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Unit ID in response or the specified default value.
    */
   public final int getrxUnitID( int index, int defaultValue )
   {
      return _rxUnitID[index] == null ? defaultValue : _rxUnitID[index].intValue();
   }
    
   /**
    * Gets the array of Unit ID in response fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Unit ID in response values.
    */
   public final Integer[] getrxUnitIDArray()
   {
      return _rxUnitID;
   }
    
   /**
    * Gets the Factor Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Factor Code or null.
    */
   public final String getFactorCode( int index )
   {
      return _FactorCode[index];
   }
    
   /**
    * Gets the Factor Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Factor Code or the specified default value.
    */
   public final String getFactorCode( int index, String defaultValue )
   {
      return _FactorCode[index] == null ? defaultValue : _FactorCode[index];
   }
    
   /**
    * Gets the array of Factor Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Factor Code values.
    */
   public final String[] getFactorCodeArray()
   {
      return _FactorCode;
   }
    
   /**
    * Gets the Factor Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Factor Description or null.
    */
   public final String getFactorDesc( int index )
   {
      return _FactorDesc[index];
   }
    
   /**
    * Gets the Factor Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Factor Description or the specified default value.
    */
   public final String getFactorDesc( int index, String defaultValue )
   {
      return _FactorDesc[index] == null ? defaultValue : _FactorDesc[index];
   }
    
   /**
    * Gets the array of Factor Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Factor Description values.
    */
   public final String[] getFactorDescArray()
   {
      return _FactorDesc;
   }
    
   /**
    * Gets the Factor Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Factor Amount or null.
    */
   public final String getFactorAmount( int index )
   {
      return _FactorAmount[index];
   }
    
   /**
    * Gets the Factor Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Factor Amount or the specified default value.
    */
   public final String getFactorAmount( int index, String defaultValue )
   {
      return _FactorAmount[index] == null ? defaultValue : _FactorAmount[index];
   }
    
   /**
    * Gets the array of Factor Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Factor Amount values.
    */
   public final String[] getFactorAmountArray()
   {
      return _FactorAmount;
   }
    
   /**
    * Gets the Rate Period field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Rate Period or null.
    */
   public final String getRatePeriod( int index )
   {
      return _RatePeriod[index];
   }
    
   /**
    * Gets the Rate Period field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Rate Period or the specified default value.
    */
   public final String getRatePeriod( int index, String defaultValue )
   {
      return _RatePeriod[index] == null ? defaultValue : _RatePeriod[index];
   }
    
   /**
    * Gets the array of Rate Period fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Rate Period values.
    */
   public final String[] getRatePeriodArray()
   {
      return _RatePeriod;
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
      
      _rxUnitID = resizeArray( _rxUnitID, _RepeatCount );
      _FactorCode = resizeArray( _FactorCode, _RepeatCount );
      _FactorDesc = resizeArray( _FactorDesc, _RepeatCount );
      _FactorAmount = resizeArray( _FactorAmount, _RepeatCount );
      _RatePeriod = resizeArray( _RatePeriod, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxUnitID[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _FactorCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FactorDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FactorAmount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RatePeriod[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
