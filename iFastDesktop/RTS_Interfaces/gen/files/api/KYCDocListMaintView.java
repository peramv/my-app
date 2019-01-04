
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * KYC  Document List Maintenance view.
 * For additional view information see <A HREF="../../../../viewspecs/KYCDocListMaint.doc">KYCDocListMaint.doc</A>.
 * 
 * @author RTS Generated
 */
public class KYCDocListMaintView extends IFastView implements Serializable
{

   /**
    * Update Status member variable.
    */
   private Boolean _UpdateStatus = null;
   
   /**
    * Warning Message member variable.
    */
   private Integer _WarnMsgCode = null;
   
   /**
    * Warning Message Description member variable.
    */
   private String _WarnMsgDesc = null;
   

   /**
    * Constructs the KYCDocListMaintView object.
    * 
    */
   public KYCDocListMaintView()
   {
      super ( new KYCDocListMaintRequest() );
   }

   /**
    * Constructs the KYCDocListMaintView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public KYCDocListMaintView( String hostEncoding )
   {
      super ( new KYCDocListMaintRequest( hostEncoding ) );
   }

   /**
    * Gets the KYCDocListMaintRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The KYCDocListMaintRequest object.
    */
   public final KYCDocListMaintRequest getRequest()
   {
      return (KYCDocListMaintRequest)getIFastRequest();
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
    * Gets the Warning Message field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Message or null.
    */
   public final Integer getWarnMsgCode()
   {
      return _WarnMsgCode;
   }
	
   /**
    * Gets the Warning Message field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Message or the specified default value.
    */
   public final int getWarnMsgCode( int defaultValue )
   {
      return _WarnMsgCode == null ? defaultValue : _WarnMsgCode.intValue();
   }
                  
   /**
    * Gets the Warning Message Description field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Message Description or null.
    */
   public final String getWarnMsgDesc()
   {
      return _WarnMsgDesc;
   }
	
   /**
    * Gets the Warning Message Description field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Message Description or the specified default value.
    */
   public final String getWarnMsgDesc( String defaultValue )
   {
      return _WarnMsgDesc == null ? defaultValue : _WarnMsgDesc;
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
      _WarnMsgCode = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _WarnMsgDesc = responseBuffer.decodeString(responseBuffer.getNextField());
                  

   }

}
      
