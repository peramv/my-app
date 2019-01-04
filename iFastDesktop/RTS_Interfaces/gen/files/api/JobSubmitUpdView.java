
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Job Submission view.
 * For additional view information see <A HREF="../../../../viewspecs/JobSubmitUpd.doc">JobSubmitUpd.doc</A>.
 * 
 * @author RTS Generated
 */
public class JobSubmitUpdView extends IFastView implements Serializable
{

   /**
    * Update Status member variable.
    */
   private Boolean _UpdateStatus = null;
   
   /**
    * Scheduled Job Id member variable.
    */
   private Integer _SchedJobId = null;
   

   /**
    * Constructs the JobSubmitUpdView object.
    * 
    */
   public JobSubmitUpdView()
   {
      super ( new JobSubmitUpdRequest() );
   }

   /**
    * Constructs the JobSubmitUpdView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public JobSubmitUpdView( String hostEncoding )
   {
      super ( new JobSubmitUpdRequest( hostEncoding ) );
   }

   /**
    * Gets the JobSubmitUpdRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The JobSubmitUpdRequest object.
    */
   public final JobSubmitUpdRequest getRequest()
   {
      return (JobSubmitUpdRequest)getIFastRequest();
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
    * Gets the Scheduled Job Id field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Scheduled Job Id or null.
    */
   public final Integer getSchedJobId()
   {
      return _SchedJobId;
   }
	
   /**
    * Gets the Scheduled Job Id field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Scheduled Job Id or the specified default value.
    */
   public final int getSchedJobId( int defaultValue )
   {
      return _SchedJobId == null ? defaultValue : _SchedJobId.intValue();
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
      _SchedJobId = responseBuffer.decodeInteger(responseBuffer.getNextField());
                  

   }

}
      
