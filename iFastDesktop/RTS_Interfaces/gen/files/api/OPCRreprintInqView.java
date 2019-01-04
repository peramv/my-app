
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * OPC Confirm Reprint Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/OPCRreprintInq.doc">OPCRreprintInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class OPCRreprintInqView extends IFastView implements Serializable
{

   /**
    * Client Copy member variable.
    */
   private Boolean _ClientCopy = null;
   
   /**
    * Broker Copy member variable.
    */
   private Boolean _BrokerCopy = null;
   
   /**
    * SalesRepCopy member variable.
    */
   private Boolean _SalesRepCopy = null;
   
   /**
    * Schedule Reprint Date member variable.
    */
   private Date _SchedReprintDate = null;
   
   /**
    * Requested By member variable.
    */
   private String _RequestedBy = null;
   

   /**
    * Constructs the OPCRreprintInqView object.
    * 
    */
   public OPCRreprintInqView()
   {
      super ( new OPCRreprintInqRequest() );
   }

   /**
    * Constructs the OPCRreprintInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public OPCRreprintInqView( String hostEncoding )
   {
      super ( new OPCRreprintInqRequest( hostEncoding ) );
   }

   /**
    * Gets the OPCRreprintInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The OPCRreprintInqRequest object.
    */
   public final OPCRreprintInqRequest getRequest()
   {
      return (OPCRreprintInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Client Copy field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Client Copy or null.
    */
   public final Boolean getClientCopy()
   {
      return _ClientCopy;
   }
	
   /**
    * Gets the Client Copy field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Client Copy or the specified default value.
    */
   public final boolean getClientCopy( boolean defaultValue )
   {
      return _ClientCopy == null ? defaultValue : _ClientCopy.booleanValue();
   }
                  
   /**
    * Gets the Broker Copy field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Broker Copy or null.
    */
   public final Boolean getBrokerCopy()
   {
      return _BrokerCopy;
   }
	
   /**
    * Gets the Broker Copy field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker Copy or the specified default value.
    */
   public final boolean getBrokerCopy( boolean defaultValue )
   {
      return _BrokerCopy == null ? defaultValue : _BrokerCopy.booleanValue();
   }
                  
   /**
    * Gets the SalesRepCopy field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the SalesRepCopy or null.
    */
   public final Boolean getSalesRepCopy()
   {
      return _SalesRepCopy;
   }
	
   /**
    * Gets the SalesRepCopy field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SalesRepCopy or the specified default value.
    */
   public final boolean getSalesRepCopy( boolean defaultValue )
   {
      return _SalesRepCopy == null ? defaultValue : _SalesRepCopy.booleanValue();
   }
                  
   /**
    * Gets the Schedule Reprint Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Schedule Reprint Date or null.
    */
   public final Date getSchedReprintDate()
   {
      return _SchedReprintDate;
   }
	
   /**
    * Gets the Schedule Reprint Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Schedule Reprint Date or the specified default value.
    */
   public final Date getSchedReprintDate( Date defaultValue )
   {
      return _SchedReprintDate == null ? defaultValue : _SchedReprintDate;
   }
                  
   /**
    * Gets the Requested By field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Requested By or null.
    */
   public final String getRequestedBy()
   {
      return _RequestedBy;
   }
	
   /**
    * Gets the Requested By field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Requested By or the specified default value.
    */
   public final String getRequestedBy( String defaultValue )
   {
      return _RequestedBy == null ? defaultValue : _RequestedBy;
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
      _ClientCopy = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _BrokerCopy = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _SalesRepCopy = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _SchedReprintDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _RequestedBy = responseBuffer.decodeString(responseBuffer.getNextField());
                  

   }

}
      
