
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Sessions Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/SessionInq.doc">SessionInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class SessionInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * User Session Id member array.
    */
   private String[] _UsrSessionId = null;
   
   /**
    * rxSession Date member array.
    */
   private Date[] _rxSessionDate = null;
   
   /**
    * User Profile Id member array.
    */
   private String[] _UsrProfileId = null;
   

   /**
    * Constructs the SessionInqView object.
    * 
    */
   public SessionInqView()
   {
      super ( new SessionInqRequest() );
   }

   /**
    * Constructs the SessionInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public SessionInqView( String hostEncoding )
   {
      super ( new SessionInqRequest( hostEncoding ) );
   }

   /**
    * Gets the SessionInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The SessionInqRequest object.
    */
   public final SessionInqRequest getRequest()
   {
      return (SessionInqRequest)getIFastRequest();
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
    * Gets the User Session Id field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the User Session Id or null.
    */
   public final String getUsrSessionId( int index )
   {
      return _UsrSessionId[index];
   }
    
   /**
    * Gets the User Session Id field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the User Session Id or the specified default value.
    */
   public final String getUsrSessionId( int index, String defaultValue )
   {
      return _UsrSessionId[index] == null ? defaultValue : _UsrSessionId[index];
   }
    
   /**
    * Gets the array of User Session Id fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of User Session Id values.
    */
   public final String[] getUsrSessionIdArray()
   {
      return _UsrSessionId;
   }
    
   /**
    * Gets the rxSession Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the rxSession Date or null.
    */
   public final Date getrxSessionDate( int index )
   {
      return _rxSessionDate[index];
   }
    
   /**
    * Gets the rxSession Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the rxSession Date or the specified default value.
    */
   public final Date getrxSessionDate( int index, Date defaultValue )
   {
      return _rxSessionDate[index] == null ? defaultValue : _rxSessionDate[index];
   }
    
   /**
    * Gets the array of rxSession Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of rxSession Date values.
    */
   public final Date[] getrxSessionDateArray()
   {
      return _rxSessionDate;
   }
    
   /**
    * Gets the User Profile Id field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the User Profile Id or null.
    */
   public final String getUsrProfileId( int index )
   {
      return _UsrProfileId[index];
   }
    
   /**
    * Gets the User Profile Id field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the User Profile Id or the specified default value.
    */
   public final String getUsrProfileId( int index, String defaultValue )
   {
      return _UsrProfileId[index] == null ? defaultValue : _UsrProfileId[index];
   }
    
   /**
    * Gets the array of User Profile Id fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of User Profile Id values.
    */
   public final String[] getUsrProfileIdArray()
   {
      return _UsrProfileId;
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
      
      _UsrSessionId = resizeArray( _UsrSessionId, _RepeatCount );
      _rxSessionDate = resizeArray( _rxSessionDate, _RepeatCount );
      _UsrProfileId = resizeArray( _UsrProfileId, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _UsrSessionId[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxSessionDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _UsrProfileId[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
