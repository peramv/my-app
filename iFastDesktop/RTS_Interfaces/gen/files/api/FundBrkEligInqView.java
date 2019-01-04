
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Fund Broker Elig Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/FundBrkEligInq.doc">FundBrkEligInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class FundBrkEligInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * rxBrokerCode member array.
    */
   private String[] _rxBrokerCode = null;
   
   /**
    * rxFundCode member array.
    */
   private String[] _rxFundCode = null;
   
   /**
    * IsDefault member array.
    */
   private Boolean[] _IsDefault = null;
   

   /**
    * Constructs the FundBrkEligInqView object.
    * 
    */
   public FundBrkEligInqView()
   {
      super ( new FundBrkEligInqRequest() );
   }

   /**
    * Constructs the FundBrkEligInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public FundBrkEligInqView( String hostEncoding )
   {
      super ( new FundBrkEligInqRequest( hostEncoding ) );
   }

   /**
    * Gets the FundBrkEligInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The FundBrkEligInqRequest object.
    */
   public final FundBrkEligInqRequest getRequest()
   {
      return (FundBrkEligInqRequest)getIFastRequest();
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
    * Gets the rxBrokerCode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the rxBrokerCode or null.
    */
   public final String getrxBrokerCode( int index )
   {
      return _rxBrokerCode[index];
   }
    
   /**
    * Gets the rxBrokerCode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the rxBrokerCode or the specified default value.
    */
   public final String getrxBrokerCode( int index, String defaultValue )
   {
      return _rxBrokerCode[index] == null ? defaultValue : _rxBrokerCode[index];
   }
    
   /**
    * Gets the array of rxBrokerCode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of rxBrokerCode values.
    */
   public final String[] getrxBrokerCodeArray()
   {
      return _rxBrokerCode;
   }
    
   /**
    * Gets the rxFundCode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the rxFundCode or null.
    */
   public final String getrxFundCode( int index )
   {
      return _rxFundCode[index];
   }
    
   /**
    * Gets the rxFundCode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the rxFundCode or the specified default value.
    */
   public final String getrxFundCode( int index, String defaultValue )
   {
      return _rxFundCode[index] == null ? defaultValue : _rxFundCode[index];
   }
    
   /**
    * Gets the array of rxFundCode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of rxFundCode values.
    */
   public final String[] getrxFundCodeArray()
   {
      return _rxFundCode;
   }
    
   /**
    * Gets the IsDefault field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the IsDefault or null.
    */
   public final Boolean getIsDefault( int index )
   {
      return _IsDefault[index];
   }
    
   /**
    * Gets the IsDefault field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the IsDefault or the specified default value.
    */
   public final boolean getIsDefault( int index, boolean defaultValue )
   {
      return _IsDefault[index] == null ? defaultValue : _IsDefault[index].booleanValue();
   }
    
   /**
    * Gets the array of IsDefault fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of IsDefault values.
    */
   public final Boolean[] getIsDefaultArray()
   {
      return _IsDefault;
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
      _rxFundCode = resizeArray( _rxFundCode, _RepeatCount );
      _IsDefault = resizeArray( _IsDefault, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxBrokerCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxFundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IsDefault[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      }
      

   }

}
      
