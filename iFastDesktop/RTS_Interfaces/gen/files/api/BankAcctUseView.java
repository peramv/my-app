
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Bank Account Usage Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/BankAcctUse.doc">BankAcctUse.doc</A>.
 * 
 * @author RTS Generated
 */
public class BankAcctUseView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Banking Transaction Type member array.
    */
   private String[] _AcctUsage = null;
   
   /**
    * Banking Transaction Type Description member array.
    */
   private String[] _AcctUsageDesc = null;
   

   /**
    * Constructs the BankAcctUseView object.
    * 
    */
   public BankAcctUseView()
   {
      super ( new BankAcctUseRequest() );
   }

   /**
    * Constructs the BankAcctUseView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public BankAcctUseView( String hostEncoding )
   {
      super ( new BankAcctUseRequest( hostEncoding ) );
   }

   /**
    * Gets the BankAcctUseRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The BankAcctUseRequest object.
    */
   public final BankAcctUseRequest getRequest()
   {
      return (BankAcctUseRequest)getIFastRequest();
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
    * Gets the Banking Transaction Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Banking Transaction Type or null.
    */
   public final String getAcctUsage( int index )
   {
      return _AcctUsage[index];
   }
    
   /**
    * Gets the Banking Transaction Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Banking Transaction Type or the specified default value.
    */
   public final String getAcctUsage( int index, String defaultValue )
   {
      return _AcctUsage[index] == null ? defaultValue : _AcctUsage[index];
   }
    
   /**
    * Gets the array of Banking Transaction Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Banking Transaction Type values.
    */
   public final String[] getAcctUsageArray()
   {
      return _AcctUsage;
   }
    
   /**
    * Gets the Banking Transaction Type Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Banking Transaction Type Description or null.
    */
   public final String getAcctUsageDesc( int index )
   {
      return _AcctUsageDesc[index];
   }
    
   /**
    * Gets the Banking Transaction Type Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Banking Transaction Type Description or the specified default value.
    */
   public final String getAcctUsageDesc( int index, String defaultValue )
   {
      return _AcctUsageDesc[index] == null ? defaultValue : _AcctUsageDesc[index];
   }
    
   /**
    * Gets the array of Banking Transaction Type Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Banking Transaction Type Description values.
    */
   public final String[] getAcctUsageDescArray()
   {
      return _AcctUsageDesc;
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
      
      _AcctUsage = resizeArray( _AcctUsage, _RepeatCount );
      _AcctUsageDesc = resizeArray( _AcctUsageDesc, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _AcctUsage[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctUsageDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
