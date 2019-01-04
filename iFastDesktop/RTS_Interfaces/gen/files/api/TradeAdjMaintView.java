
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Trade Adjust Maint (Indivi. Cancellation & Rebook) view.
 * For additional view information see <A HREF="../../../../viewspecs/TradeAdjMaint.doc">TradeAdjMaint.doc</A>.
 * 
 * @author RTS Generated
 */
public class TradeAdjMaintView extends IFastView implements Serializable
{

   /**
    * Update Status member variable.
    */
   private Boolean _UpdateStatus = null;
   
   /**
    * Warning Number member variable.
    */
   private Integer _WarnCode1 = null;
   
   /**
    * Warning Description member variable.
    */
   private String _WarnDesc1 = null;
   
   /**
    * Warning Number member variable.
    */
   private Integer _WarnCode2 = null;
   
   /**
    * Warning Description member variable.
    */
   private String _WarnDesc2 = null;
   
   /**
    * Warning Number member variable.
    */
   private Integer _WarnCode3 = null;
   
   /**
    * Warning Description member variable.
    */
   private String _WarnDesc3 = null;
   
   /**
    * Warning Number member variable.
    */
   private Integer _WarnCode4 = null;
   
   /**
    * Warning Description member variable.
    */
   private String _WarnDesc4 = null;
   
   /**
    * Warning Number member variable.
    */
   private Integer _WarnCode5 = null;
   
   /**
    * Warning Description member variable.
    */
   private String _WarnDesc5 = null;
   
   /**
    * Warn Param member variable.
    */
   private String _WarnParam1 = null;
   
   /**
    * Warn Param member variable.
    */
   private String _WarnParam2 = null;
   
   /**
    * Warn Param member variable.
    */
   private String _WarnParam3 = null;
   
   /**
    * Warn Param member variable.
    */
   private String _WarnParam4 = null;
   
   /**
    * Warn Param member variable.
    */
   private String _WarnParam5 = null;
   

   /**
    * Constructs the TradeAdjMaintView object.
    * 
    */
   public TradeAdjMaintView()
   {
      super ( new TradeAdjMaintRequest() );
   }

   /**
    * Constructs the TradeAdjMaintView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public TradeAdjMaintView( String hostEncoding )
   {
      super ( new TradeAdjMaintRequest( hostEncoding ) );
   }

   /**
    * Gets the TradeAdjMaintRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The TradeAdjMaintRequest object.
    */
   public final TradeAdjMaintRequest getRequest()
   {
      return (TradeAdjMaintRequest)getIFastRequest();
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
    * Gets the Warning Number field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Number or null.
    */
   public final Integer getWarnCode1()
   {
      return _WarnCode1;
   }
	
   /**
    * Gets the Warning Number field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Number or the specified default value.
    */
   public final int getWarnCode1( int defaultValue )
   {
      return _WarnCode1 == null ? defaultValue : _WarnCode1.intValue();
   }
                  
   /**
    * Gets the Warning Description field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Description or null.
    */
   public final String getWarnDesc1()
   {
      return _WarnDesc1;
   }
	
   /**
    * Gets the Warning Description field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Description or the specified default value.
    */
   public final String getWarnDesc1( String defaultValue )
   {
      return _WarnDesc1 == null ? defaultValue : _WarnDesc1;
   }
                  
   /**
    * Gets the Warning Number field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Number or null.
    */
   public final Integer getWarnCode2()
   {
      return _WarnCode2;
   }
	
   /**
    * Gets the Warning Number field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Number or the specified default value.
    */
   public final int getWarnCode2( int defaultValue )
   {
      return _WarnCode2 == null ? defaultValue : _WarnCode2.intValue();
   }
                  
   /**
    * Gets the Warning Description field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Description or null.
    */
   public final String getWarnDesc2()
   {
      return _WarnDesc2;
   }
	
   /**
    * Gets the Warning Description field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Description or the specified default value.
    */
   public final String getWarnDesc2( String defaultValue )
   {
      return _WarnDesc2 == null ? defaultValue : _WarnDesc2;
   }
                  
   /**
    * Gets the Warning Number field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Number or null.
    */
   public final Integer getWarnCode3()
   {
      return _WarnCode3;
   }
	
   /**
    * Gets the Warning Number field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Number or the specified default value.
    */
   public final int getWarnCode3( int defaultValue )
   {
      return _WarnCode3 == null ? defaultValue : _WarnCode3.intValue();
   }
                  
   /**
    * Gets the Warning Description field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Description or null.
    */
   public final String getWarnDesc3()
   {
      return _WarnDesc3;
   }
	
   /**
    * Gets the Warning Description field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Description or the specified default value.
    */
   public final String getWarnDesc3( String defaultValue )
   {
      return _WarnDesc3 == null ? defaultValue : _WarnDesc3;
   }
                  
   /**
    * Gets the Warning Number field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Number or null.
    */
   public final Integer getWarnCode4()
   {
      return _WarnCode4;
   }
	
   /**
    * Gets the Warning Number field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Number or the specified default value.
    */
   public final int getWarnCode4( int defaultValue )
   {
      return _WarnCode4 == null ? defaultValue : _WarnCode4.intValue();
   }
                  
   /**
    * Gets the Warning Description field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Description or null.
    */
   public final String getWarnDesc4()
   {
      return _WarnDesc4;
   }
	
   /**
    * Gets the Warning Description field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Description or the specified default value.
    */
   public final String getWarnDesc4( String defaultValue )
   {
      return _WarnDesc4 == null ? defaultValue : _WarnDesc4;
   }
                  
   /**
    * Gets the Warning Number field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Number or null.
    */
   public final Integer getWarnCode5()
   {
      return _WarnCode5;
   }
	
   /**
    * Gets the Warning Number field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Number or the specified default value.
    */
   public final int getWarnCode5( int defaultValue )
   {
      return _WarnCode5 == null ? defaultValue : _WarnCode5.intValue();
   }
                  
   /**
    * Gets the Warning Description field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Description or null.
    */
   public final String getWarnDesc5()
   {
      return _WarnDesc5;
   }
	
   /**
    * Gets the Warning Description field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Description or the specified default value.
    */
   public final String getWarnDesc5( String defaultValue )
   {
      return _WarnDesc5 == null ? defaultValue : _WarnDesc5;
   }
                  
   /**
    * Gets the Warn Param field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warn Param or null.
    */
   public final String getWarnParam1()
   {
      return _WarnParam1;
   }
	
   /**
    * Gets the Warn Param field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warn Param or the specified default value.
    */
   public final String getWarnParam1( String defaultValue )
   {
      return _WarnParam1 == null ? defaultValue : _WarnParam1;
   }
                  
   /**
    * Gets the Warn Param field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warn Param or null.
    */
   public final String getWarnParam2()
   {
      return _WarnParam2;
   }
	
   /**
    * Gets the Warn Param field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warn Param or the specified default value.
    */
   public final String getWarnParam2( String defaultValue )
   {
      return _WarnParam2 == null ? defaultValue : _WarnParam2;
   }
                  
   /**
    * Gets the Warn Param field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warn Param or null.
    */
   public final String getWarnParam3()
   {
      return _WarnParam3;
   }
	
   /**
    * Gets the Warn Param field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warn Param or the specified default value.
    */
   public final String getWarnParam3( String defaultValue )
   {
      return _WarnParam3 == null ? defaultValue : _WarnParam3;
   }
                  
   /**
    * Gets the Warn Param field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warn Param or null.
    */
   public final String getWarnParam4()
   {
      return _WarnParam4;
   }
	
   /**
    * Gets the Warn Param field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warn Param or the specified default value.
    */
   public final String getWarnParam4( String defaultValue )
   {
      return _WarnParam4 == null ? defaultValue : _WarnParam4;
   }
                  
   /**
    * Gets the Warn Param field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warn Param or null.
    */
   public final String getWarnParam5()
   {
      return _WarnParam5;
   }
	
   /**
    * Gets the Warn Param field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warn Param or the specified default value.
    */
   public final String getWarnParam5( String defaultValue )
   {
      return _WarnParam5 == null ? defaultValue : _WarnParam5;
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
      _WarnCode1 = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _WarnDesc1 = responseBuffer.decodeString(responseBuffer.getNextField());
      _WarnCode2 = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _WarnDesc2 = responseBuffer.decodeString(responseBuffer.getNextField());
      _WarnCode3 = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _WarnDesc3 = responseBuffer.decodeString(responseBuffer.getNextField());
      _WarnCode4 = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _WarnDesc4 = responseBuffer.decodeString(responseBuffer.getNextField());
      _WarnCode5 = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _WarnDesc5 = responseBuffer.decodeString(responseBuffer.getNextField());
      _WarnParam1 = responseBuffer.decodeString(responseBuffer.getNextField());
      _WarnParam2 = responseBuffer.decodeString(responseBuffer.getNextField());
      _WarnParam3 = responseBuffer.decodeString(responseBuffer.getNextField());
      _WarnParam4 = responseBuffer.decodeString(responseBuffer.getNextField());
      _WarnParam5 = responseBuffer.decodeString(responseBuffer.getNextField());
                  

   }

}
      
