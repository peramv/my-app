
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * eInvestor Registration view.
 * For additional view information see <A HREF="../../../../viewspecs/InvRgstrn.doc">InvRgstrn.doc</A>.
 * 
 * @author RTS Generated
 */
public class InvRgstrnView extends IFastView implements Serializable
{

   /**
    * User Exists Flag Y/N member variable.
    */
   private Boolean _UserExists = null;
   
   /**
    * Entity ID member variable.
    */
   private String _EntityId = null;
   
   /**
    * Memorable Date for Security Validation member variable.
    */
   private Date _MemorableDate = null;
   
   /**
    * Relationship for Memorable Date member variable.
    */
   private String _MemorableDateReln = null;
   
   /**
    * rxAccountNum member variable.
    */
   private String _rxAccountNum = null;
   

   /**
    * Constructs the InvRgstrnView object.
    * 
    */
   public InvRgstrnView()
   {
      super ( new InvRgstrnRequest() );
   }

   /**
    * Constructs the InvRgstrnView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public InvRgstrnView( String hostEncoding )
   {
      super ( new InvRgstrnRequest( hostEncoding ) );
   }

   /**
    * Gets the InvRgstrnRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The InvRgstrnRequest object.
    */
   public final InvRgstrnRequest getRequest()
   {
      return (InvRgstrnRequest)getIFastRequest();
   }
        
   /**
    * Gets the User Exists Flag Y/N field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the User Exists Flag Y/N or null.
    */
   public final Boolean getUserExists()
   {
      return _UserExists;
   }
	
   /**
    * Gets the User Exists Flag Y/N field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the User Exists Flag Y/N or the specified default value.
    */
   public final boolean getUserExists( boolean defaultValue )
   {
      return _UserExists == null ? defaultValue : _UserExists.booleanValue();
   }
                  
   /**
    * Gets the Entity ID field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Entity ID or null.
    */
   public final String getEntityId()
   {
      return _EntityId;
   }
	
   /**
    * Gets the Entity ID field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity ID or the specified default value.
    */
   public final String getEntityId( String defaultValue )
   {
      return _EntityId == null ? defaultValue : _EntityId;
   }
                  
   /**
    * Gets the Memorable Date for Security Validation field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Memorable Date for Security Validation or null.
    */
   public final Date getMemorableDate()
   {
      return _MemorableDate;
   }
	
   /**
    * Gets the Memorable Date for Security Validation field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Memorable Date for Security Validation or the specified default value.
    */
   public final Date getMemorableDate( Date defaultValue )
   {
      return _MemorableDate == null ? defaultValue : _MemorableDate;
   }
                  
   /**
    * Gets the Relationship for Memorable Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Relationship for Memorable Date or null.
    */
   public final String getMemorableDateReln()
   {
      return _MemorableDateReln;
   }
	
   /**
    * Gets the Relationship for Memorable Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Relationship for Memorable Date or the specified default value.
    */
   public final String getMemorableDateReln( String defaultValue )
   {
      return _MemorableDateReln == null ? defaultValue : _MemorableDateReln;
   }
                  
   /**
    * Gets the rxAccountNum field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the rxAccountNum or null.
    */
   public final String getrxAccountNum()
   {
      return _rxAccountNum;
   }
	
   /**
    * Gets the rxAccountNum field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the rxAccountNum or the specified default value.
    */
   public final String getrxAccountNum( String defaultValue )
   {
      return _rxAccountNum == null ? defaultValue : _rxAccountNum;
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
      _UserExists = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _EntityId = responseBuffer.decodeString(responseBuffer.getNextField());
      _MemorableDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _MemorableDateReln = responseBuffer.decodeString(responseBuffer.getNextField());
      _rxAccountNum = responseBuffer.decodeString(responseBuffer.getNextField());
                  

   }

}
      
