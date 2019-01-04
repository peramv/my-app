
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * eInvestor Reset Password view.
 * For additional view information see <A HREF="../../../../viewspecs/InvResetPasswd.doc">InvResetPasswd.doc</A>.
 * 
 * @author RTS Generated
 */
public class InvResetPasswdView extends IFastView implements Serializable
{

   /**
    * Update Status member variable.
    */
   private Boolean _UpdateStatus = null;
   
   /**
    * Date of Registration member variable.
    */
   private Date _EffectiveDate = null;
   
   /**
    * Time of Registration member variable.
    */
   private String _EffectiveTime = null;
   

   /**
    * Constructs the InvResetPasswdView object.
    * 
    */
   public InvResetPasswdView()
   {
      super ( new InvResetPasswdRequest() );
   }

   /**
    * Constructs the InvResetPasswdView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public InvResetPasswdView( String hostEncoding )
   {
      super ( new InvResetPasswdRequest( hostEncoding ) );
   }

   /**
    * Gets the InvResetPasswdRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The InvResetPasswdRequest object.
    */
   public final InvResetPasswdRequest getRequest()
   {
      return (InvResetPasswdRequest)getIFastRequest();
   }
        
   /**
    * Gets the Update Status field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Update Status or null.
    */
   public final Boolean getUpdateStatus()
   {
      return _UpdateStatus;
   }
	
   /**
    * Gets the Update Status field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Update Status or the specified default value.
    */
   public final boolean getUpdateStatus( boolean defaultValue )
   {
      return _UpdateStatus == null ? defaultValue : _UpdateStatus.booleanValue();
   }
                  
   /**
    * Gets the Date of Registration field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Date of Registration or null.
    */
   public final Date getEffectiveDate()
   {
      return _EffectiveDate;
   }
	
   /**
    * Gets the Date of Registration field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date of Registration or the specified default value.
    */
   public final Date getEffectiveDate( Date defaultValue )
   {
      return _EffectiveDate == null ? defaultValue : _EffectiveDate;
   }
                  
   /**
    * Gets the Time of Registration field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Time of Registration or null.
    */
   public final String getEffectiveTime()
   {
      return _EffectiveTime;
   }
	
   /**
    * Gets the Time of Registration field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Time of Registration or the specified default value.
    */
   public final String getEffectiveTime( String defaultValue )
   {
      return _EffectiveTime == null ? defaultValue : _EffectiveTime;
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
      _UpdateStatus = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _EffectiveDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _EffectiveTime = responseBuffer.decodeString(responseBuffer.getNextField());
                  

   }

}
      
