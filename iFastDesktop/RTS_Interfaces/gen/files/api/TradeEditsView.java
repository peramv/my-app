
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Trade Edits view.
 * For additional view information see <A HREF="../../../../viewspecs/TradeEdits.doc">TradeEdits.doc</A>.
 * 
 * @author RTS Generated
 */
public class TradeEditsView extends IFastView implements Serializable
{

   /**
    * Initial Purchase member variable.
    */
   private Boolean _InitPurch = null;
   
   /**
    * Broker Overide Amount member variable.
    */
   private String _BrkOverideAmt = null;
   
   private int _RepeatCount = 0;
   
   /**
    * Error Number member array.
    */
   private Integer[] _ErrorNum = null;
   
   /**
    * Amount member array.
    */
   private String[] _rxAmount = null;
   
   /**
    * Error Message member array.
    */
   private String[] _ErrorMsg = null;
   
   /**
    * Error Severity member array.
    */
   private String[] _EWI = null;
   

   /**
    * Constructs the TradeEditsView object.
    * 
    */
   public TradeEditsView()
   {
      super ( new TradeEditsRequest() );
   }

   /**
    * Constructs the TradeEditsView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public TradeEditsView( String hostEncoding )
   {
      super ( new TradeEditsRequest( hostEncoding ) );
   }

   /**
    * Gets the TradeEditsRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The TradeEditsRequest object.
    */
   public final TradeEditsRequest getRequest()
   {
      return (TradeEditsRequest)getIFastRequest();
   }
        
   /**
    * Gets the Initial Purchase field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Initial Purchase or null.
    */
   public final Boolean getInitPurch()
   {
      return _InitPurch;
   }
	
   /**
    * Gets the Initial Purchase field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Initial Purchase or the specified default value.
    */
   public final boolean getInitPurch( boolean defaultValue )
   {
      return _InitPurch == null ? defaultValue : _InitPurch.booleanValue();
   }
                  
   /**
    * Gets the Broker Overide Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Broker Overide Amount or null.
    */
   public final String getBrkOverideAmt()
   {
      return _BrkOverideAmt;
   }
	
   /**
    * Gets the Broker Overide Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker Overide Amount or the specified default value.
    */
   public final String getBrkOverideAmt( String defaultValue )
   {
      return _BrkOverideAmt == null ? defaultValue : _BrkOverideAmt;
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
    * Gets the Error Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Error Number or null.
    */
   public final Integer getErrorNum( int index )
   {
      return _ErrorNum[index];
   }
    
   /**
    * Gets the Error Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Error Number or the specified default value.
    */
   public final int getErrorNum( int index, int defaultValue )
   {
      return _ErrorNum[index] == null ? defaultValue : _ErrorNum[index].intValue();
   }
    
   /**
    * Gets the array of Error Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Error Number values.
    */
   public final Integer[] getErrorNumArray()
   {
      return _ErrorNum;
   }
    
   /**
    * Gets the Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Amount or null.
    */
   public final String getrxAmount( int index )
   {
      return _rxAmount[index];
   }
    
   /**
    * Gets the Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Amount or the specified default value.
    */
   public final String getrxAmount( int index, String defaultValue )
   {
      return _rxAmount[index] == null ? defaultValue : _rxAmount[index];
   }
    
   /**
    * Gets the array of Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Amount values.
    */
   public final String[] getrxAmountArray()
   {
      return _rxAmount;
   }
    
   /**
    * Gets the Error Message field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Error Message or null.
    */
   public final String getErrorMsg( int index )
   {
      return _ErrorMsg[index];
   }
    
   /**
    * Gets the Error Message field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Error Message or the specified default value.
    */
   public final String getErrorMsg( int index, String defaultValue )
   {
      return _ErrorMsg[index] == null ? defaultValue : _ErrorMsg[index];
   }
    
   /**
    * Gets the array of Error Message fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Error Message values.
    */
   public final String[] getErrorMsgArray()
   {
      return _ErrorMsg;
   }
    
   /**
    * Gets the Error Severity field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Error Severity or null.
    */
   public final String getEWI( int index )
   {
      return _EWI[index];
   }
    
   /**
    * Gets the Error Severity field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Error Severity or the specified default value.
    */
   public final String getEWI( int index, String defaultValue )
   {
      return _EWI[index] == null ? defaultValue : _EWI[index];
   }
    
   /**
    * Gets the array of Error Severity fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Error Severity values.
    */
   public final String[] getEWIArray()
   {
      return _EWI;
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
      _InitPurch = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _BrkOverideAmt = responseBuffer.decodeString(responseBuffer.getNextField());
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _ErrorNum = resizeArray( _ErrorNum, _RepeatCount );
      _rxAmount = resizeArray( _rxAmount, _RepeatCount );
      _ErrorMsg = resizeArray( _ErrorMsg, _RepeatCount );
      _EWI = resizeArray( _EWI, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _ErrorNum[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _rxAmount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ErrorMsg[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EWI[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
