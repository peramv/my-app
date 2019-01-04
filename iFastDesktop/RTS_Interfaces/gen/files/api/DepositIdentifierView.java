
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Deposit Identifier List view.
 * For additional view information see <A HREF="../../../../viewspecs/DepositIdentifier.doc">DepositIdentifier.doc</A>.
 * 
 * @author RTS Generated
 */
public class DepositIdentifierView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * flag indicating if DepID is valid member array.
    */
   private Boolean[] _DepValid = null;
   
   /**
    * flag indicating that DepId is closed member array.
    */
   private Boolean[] _DepClosed = null;
   

   /**
    * Constructs the DepositIdentifierView object.
    * 
    */
   public DepositIdentifierView()
   {
      super ( new DepositIdentifierRequest() );
   }

   /**
    * Constructs the DepositIdentifierView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public DepositIdentifierView( String hostEncoding )
   {
      super ( new DepositIdentifierRequest( hostEncoding ) );
   }

   /**
    * Gets the DepositIdentifierRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The DepositIdentifierRequest object.
    */
   public final DepositIdentifierRequest getRequest()
   {
      return (DepositIdentifierRequest)getIFastRequest();
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
    * Gets the flag indicating if DepID is valid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the flag indicating if DepID is valid or null.
    */
   public final Boolean getDepValid( int index )
   {
      return _DepValid[index];
   }
    
   /**
    * Gets the flag indicating if DepID is valid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the flag indicating if DepID is valid or the specified default value.
    */
   public final boolean getDepValid( int index, boolean defaultValue )
   {
      return _DepValid[index] == null ? defaultValue : _DepValid[index].booleanValue();
   }
    
   /**
    * Gets the array of flag indicating if DepID is valid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of flag indicating if DepID is valid values.
    */
   public final Boolean[] getDepValidArray()
   {
      return _DepValid;
   }
    
   /**
    * Gets the flag indicating that DepId is closed field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the flag indicating that DepId is closed or null.
    */
   public final Boolean getDepClosed( int index )
   {
      return _DepClosed[index];
   }
    
   /**
    * Gets the flag indicating that DepId is closed field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the flag indicating that DepId is closed or the specified default value.
    */
   public final boolean getDepClosed( int index, boolean defaultValue )
   {
      return _DepClosed[index] == null ? defaultValue : _DepClosed[index].booleanValue();
   }
    
   /**
    * Gets the array of flag indicating that DepId is closed fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of flag indicating that DepId is closed values.
    */
   public final Boolean[] getDepClosedArray()
   {
      return _DepClosed;
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
      
      _DepValid = resizeArray( _DepValid, _RepeatCount );
      _DepClosed = resizeArray( _DepClosed, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _DepValid[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _DepClosed[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      }
      

   }

}
      
