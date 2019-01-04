
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Aggregated Orders Maintenance view.
 * For additional view information see <A HREF="../../../../viewspecs/AggrOrdMaint.doc">AggrOrdMaint.doc</A>.
 * 
 * @author RTS Generated
 */
public class AggrOrdMaintView extends IFastView implements Serializable
{

   /**
    * Warning Message Code member variable.
    */
   private Integer _WarnMsgCode = null;
   
   /**
    * Update Status member variable.
    */
   private Boolean _UpdateStatus = null;
   
   /**
    * Loss Warning Message member variable.
    */
   private String _LossWarnMsg = null;
   
   /**
    * Broker Settlement Amount member variable.
    */
   private String _BrkSettlAmt = null;
   
   /**
    * Broker Settlement Units member variable.
    */
   private String _BrkSettlUnits = null;
   

   /**
    * Constructs the AggrOrdMaintView object.
    * 
    */
   public AggrOrdMaintView()
   {
      super ( new AggrOrdMaintRequest() );
   }

   /**
    * Constructs the AggrOrdMaintView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AggrOrdMaintView( String hostEncoding )
   {
      super ( new AggrOrdMaintRequest( hostEncoding ) );
   }

   /**
    * Gets the AggrOrdMaintRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AggrOrdMaintRequest object.
    */
   public final AggrOrdMaintRequest getRequest()
   {
      return (AggrOrdMaintRequest)getIFastRequest();
   }
        
   /**
    * Gets the Warning Message Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Message Code or null.
    */
   public final Integer getWarnMsgCode()
   {
      return _WarnMsgCode;
   }
	
   /**
    * Gets the Warning Message Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Message Code or the specified default value.
    */
   public final int getWarnMsgCode( int defaultValue )
   {
      return _WarnMsgCode == null ? defaultValue : _WarnMsgCode.intValue();
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
    * Gets the Loss Warning Message field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Loss Warning Message or null.
    */
   public final String getLossWarnMsg()
   {
      return _LossWarnMsg;
   }
	
   /**
    * Gets the Loss Warning Message field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Loss Warning Message or the specified default value.
    */
   public final String getLossWarnMsg( String defaultValue )
   {
      return _LossWarnMsg == null ? defaultValue : _LossWarnMsg;
   }
                  
   /**
    * Gets the Broker Settlement Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Broker Settlement Amount or null.
    */
   public final String getBrkSettlAmt()
   {
      return _BrkSettlAmt;
   }
	
   /**
    * Gets the Broker Settlement Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker Settlement Amount or the specified default value.
    */
   public final String getBrkSettlAmt( String defaultValue )
   {
      return _BrkSettlAmt == null ? defaultValue : _BrkSettlAmt;
   }
                  
   /**
    * Gets the Broker Settlement Units field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Broker Settlement Units or null.
    */
   public final String getBrkSettlUnits()
   {
      return _BrkSettlUnits;
   }
	
   /**
    * Gets the Broker Settlement Units field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker Settlement Units or the specified default value.
    */
   public final String getBrkSettlUnits( String defaultValue )
   {
      return _BrkSettlUnits == null ? defaultValue : _BrkSettlUnits;
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
      _WarnMsgCode = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _UpdateStatus = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _LossWarnMsg = responseBuffer.decodeString(responseBuffer.getNextField());
      _BrkSettlAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _BrkSettlUnits = responseBuffer.decodeString(responseBuffer.getNextField());
                  

   }

}
      
