
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * AS Plan Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/ASPlnInq.doc">ASPlnInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class ASPlnInqView extends IFastView implements Serializable
{

   /**
    * Start Date member variable.
    */
   private Date _StartDate = null;
   
   /**
    * End Date member variable.
    */
   private Date _EndDate = null;
   
   /**
    * AS Status member variable.
    */
   private String _ASStatus = null;
   
   /**
    * Maturity Date member variable.
    */
   private Date _MaturDate = null;
   
   /**
    * AS Status Description member variable.
    */
   private String _ASStatusDesc = null;
   

   /**
    * Constructs the ASPlnInqView object.
    * 
    */
   public ASPlnInqView()
   {
      super ( new ASPlnInqRequest() );
   }

   /**
    * Constructs the ASPlnInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public ASPlnInqView( String hostEncoding )
   {
      super ( new ASPlnInqRequest( hostEncoding ) );
   }

   /**
    * Gets the ASPlnInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The ASPlnInqRequest object.
    */
   public final ASPlnInqRequest getRequest()
   {
      return (ASPlnInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Start Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Start Date or null.
    */
   public final Date getStartDate()
   {
      return _StartDate;
   }
	
   /**
    * Gets the Start Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Start Date or the specified default value.
    */
   public final Date getStartDate( Date defaultValue )
   {
      return _StartDate == null ? defaultValue : _StartDate;
   }
                  
   /**
    * Gets the End Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the End Date or null.
    */
   public final Date getEndDate()
   {
      return _EndDate;
   }
	
   /**
    * Gets the End Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the End Date or the specified default value.
    */
   public final Date getEndDate( Date defaultValue )
   {
      return _EndDate == null ? defaultValue : _EndDate;
   }
                  
   /**
    * Gets the AS Status field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the AS Status or null.
    */
   public final String getASStatus()
   {
      return _ASStatus;
   }
	
   /**
    * Gets the AS Status field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AS Status or the specified default value.
    */
   public final String getASStatus( String defaultValue )
   {
      return _ASStatus == null ? defaultValue : _ASStatus;
   }
                  
   /**
    * Gets the Maturity Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Maturity Date or null.
    */
   public final Date getMaturDate()
   {
      return _MaturDate;
   }
	
   /**
    * Gets the Maturity Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Maturity Date or the specified default value.
    */
   public final Date getMaturDate( Date defaultValue )
   {
      return _MaturDate == null ? defaultValue : _MaturDate;
   }
                  
   /**
    * Gets the AS Status Description field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the AS Status Description or null.
    */
   public final String getASStatusDesc()
   {
      return _ASStatusDesc;
   }
	
   /**
    * Gets the AS Status Description field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AS Status Description or the specified default value.
    */
   public final String getASStatusDesc( String defaultValue )
   {
      return _ASStatusDesc == null ? defaultValue : _ASStatusDesc;
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
      _StartDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _EndDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _ASStatus = responseBuffer.decodeString(responseBuffer.getNextField());
      _MaturDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _ASStatusDesc = responseBuffer.decodeString(responseBuffer.getNextField());
                  

   }

}
      
