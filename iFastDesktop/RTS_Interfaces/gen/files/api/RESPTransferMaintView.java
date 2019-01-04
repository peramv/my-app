
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * RESP Transfer Info Maint and Validation view.
 * For additional view information see <A HREF="../../../../viewspecs/RESPTransferMaint.doc">RESPTransferMaint.doc</A>.
 * 
 * @author RTS Generated
 */
public class RESPTransferMaintView extends IFastView implements Serializable
{

   /**
    * Update Status member variable.
    */
   private Boolean _UpdateStatus = null;
   
   /**
    * Warning Message Code for CallType validation member variable.
    */
   private Integer _WarnCode1 = null;
   
   /**
    * Warning Message Code for CallType validation member variable.
    */
   private Integer _WarnCode2 = null;
   
   /**
    * Warning Message Code for CallType validation member variable.
    */
   private Integer _WarnCode3 = null;
   
   /**
    * Warning Message Code for CallType validation member variable.
    */
   private Integer _WarnCode4 = null;
   
   /**
    * Warning Message Code for CallType validation member variable.
    */
   private Integer _WarnCode5 = null;
   
   /**
    * Warning Message Code for CallType validation member variable.
    */
   private Integer _WarnCode6 = null;
   
   /**
    * Warning Message Code for CallType validation member variable.
    */
   private Integer _WarnCode7 = null;
   
   /**
    * Warning Message Code for CallType validation member variable.
    */
   private Integer _WarnCode8 = null;
   
   /**
    * Warning Message Code for CallType validation member variable.
    */
   private Integer _WarnCode9 = null;
   
   /**
    * Warning Message Code for CallType validation member variable.
    */
   private Integer _WarnCode10 = null;
   
   /**
    * Warning Message Code for CallType validation member variable.
    */
   private Integer _WarnCode11 = null;
   
   /**
    * Warning Message Code for CallType validation member variable.
    */
   private Integer _WarnCode12 = null;
   
   /**
    * Warning Message Code for CallType validation member variable.
    */
   private Integer _WarnCode13 = null;
   
   /**
    * Warning Message Code for CallType validation member variable.
    */
   private Integer _WarnCode14 = null;
   
   /**
    * Warning Message Code for CallType validation member variable.
    */
   private Integer _WarnCode15 = null;
   
   /**
    * Warning Message Code for CallType validation member variable.
    */
   private Integer _WarnCode16 = null;
   
   /**
    * Warning Message Code for CallType validation member variable.
    */
   private Integer _WarnCode17 = null;
   
   /**
    * Warning Message parameter for validation member variable.
    */
   private String _WarnParam51 = null;
   
   /**
    * Warning Message parameter for validation member variable.
    */
   private String _WarnParam52 = null;
   
   /**
    * Warning Message parameter for validation member variable.
    */
   private String _WarnParam61 = null;
   
   /**
    * Warning Message parameter for validation member variable.
    */
   private String _WarnParam62 = null;
   
   /**
    * Warning Message parameter for validation member variable.
    */
   private String _WarnParam14 = null;
   
   /**
    * Warning Message parameter for validation member variable.
    */
   private String _WarnParam17 = null;
   

   /**
    * Constructs the RESPTransferMaintView object.
    * 
    */
   public RESPTransferMaintView()
   {
      super ( new RESPTransferMaintRequest() );
   }

   /**
    * Constructs the RESPTransferMaintView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public RESPTransferMaintView( String hostEncoding )
   {
      super ( new RESPTransferMaintRequest( hostEncoding ) );
   }

   /**
    * Gets the RESPTransferMaintRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The RESPTransferMaintRequest object.
    */
   public final RESPTransferMaintRequest getRequest()
   {
      return (RESPTransferMaintRequest)getIFastRequest();
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
    * Gets the Warning Message Code for CallType validation field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Message Code for CallType validation or null.
    */
   public final Integer getWarnCode1()
   {
      return _WarnCode1;
   }
	
   /**
    * Gets the Warning Message Code for CallType validation field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Message Code for CallType validation or the specified default value.
    */
   public final int getWarnCode1( int defaultValue )
   {
      return _WarnCode1 == null ? defaultValue : _WarnCode1.intValue();
   }
                  
   /**
    * Gets the Warning Message Code for CallType validation field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Message Code for CallType validation or null.
    */
   public final Integer getWarnCode2()
   {
      return _WarnCode2;
   }
	
   /**
    * Gets the Warning Message Code for CallType validation field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Message Code for CallType validation or the specified default value.
    */
   public final int getWarnCode2( int defaultValue )
   {
      return _WarnCode2 == null ? defaultValue : _WarnCode2.intValue();
   }
                  
   /**
    * Gets the Warning Message Code for CallType validation field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Message Code for CallType validation or null.
    */
   public final Integer getWarnCode3()
   {
      return _WarnCode3;
   }
	
   /**
    * Gets the Warning Message Code for CallType validation field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Message Code for CallType validation or the specified default value.
    */
   public final int getWarnCode3( int defaultValue )
   {
      return _WarnCode3 == null ? defaultValue : _WarnCode3.intValue();
   }
                  
   /**
    * Gets the Warning Message Code for CallType validation field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Message Code for CallType validation or null.
    */
   public final Integer getWarnCode4()
   {
      return _WarnCode4;
   }
	
   /**
    * Gets the Warning Message Code for CallType validation field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Message Code for CallType validation or the specified default value.
    */
   public final int getWarnCode4( int defaultValue )
   {
      return _WarnCode4 == null ? defaultValue : _WarnCode4.intValue();
   }
                  
   /**
    * Gets the Warning Message Code for CallType validation field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Message Code for CallType validation or null.
    */
   public final Integer getWarnCode5()
   {
      return _WarnCode5;
   }
	
   /**
    * Gets the Warning Message Code for CallType validation field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Message Code for CallType validation or the specified default value.
    */
   public final int getWarnCode5( int defaultValue )
   {
      return _WarnCode5 == null ? defaultValue : _WarnCode5.intValue();
   }
                  
   /**
    * Gets the Warning Message Code for CallType validation field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Message Code for CallType validation or null.
    */
   public final Integer getWarnCode6()
   {
      return _WarnCode6;
   }
	
   /**
    * Gets the Warning Message Code for CallType validation field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Message Code for CallType validation or the specified default value.
    */
   public final int getWarnCode6( int defaultValue )
   {
      return _WarnCode6 == null ? defaultValue : _WarnCode6.intValue();
   }
                  
   /**
    * Gets the Warning Message Code for CallType validation field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Message Code for CallType validation or null.
    */
   public final Integer getWarnCode7()
   {
      return _WarnCode7;
   }
	
   /**
    * Gets the Warning Message Code for CallType validation field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Message Code for CallType validation or the specified default value.
    */
   public final int getWarnCode7( int defaultValue )
   {
      return _WarnCode7 == null ? defaultValue : _WarnCode7.intValue();
   }
                  
   /**
    * Gets the Warning Message Code for CallType validation field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Message Code for CallType validation or null.
    */
   public final Integer getWarnCode8()
   {
      return _WarnCode8;
   }
	
   /**
    * Gets the Warning Message Code for CallType validation field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Message Code for CallType validation or the specified default value.
    */
   public final int getWarnCode8( int defaultValue )
   {
      return _WarnCode8 == null ? defaultValue : _WarnCode8.intValue();
   }
                  
   /**
    * Gets the Warning Message Code for CallType validation field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Message Code for CallType validation or null.
    */
   public final Integer getWarnCode9()
   {
      return _WarnCode9;
   }
	
   /**
    * Gets the Warning Message Code for CallType validation field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Message Code for CallType validation or the specified default value.
    */
   public final int getWarnCode9( int defaultValue )
   {
      return _WarnCode9 == null ? defaultValue : _WarnCode9.intValue();
   }
                  
   /**
    * Gets the Warning Message Code for CallType validation field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Message Code for CallType validation or null.
    */
   public final Integer getWarnCode10()
   {
      return _WarnCode10;
   }
	
   /**
    * Gets the Warning Message Code for CallType validation field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Message Code for CallType validation or the specified default value.
    */
   public final int getWarnCode10( int defaultValue )
   {
      return _WarnCode10 == null ? defaultValue : _WarnCode10.intValue();
   }
                  
   /**
    * Gets the Warning Message Code for CallType validation field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Message Code for CallType validation or null.
    */
   public final Integer getWarnCode11()
   {
      return _WarnCode11;
   }
	
   /**
    * Gets the Warning Message Code for CallType validation field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Message Code for CallType validation or the specified default value.
    */
   public final int getWarnCode11( int defaultValue )
   {
      return _WarnCode11 == null ? defaultValue : _WarnCode11.intValue();
   }
                  
   /**
    * Gets the Warning Message Code for CallType validation field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Message Code for CallType validation or null.
    */
   public final Integer getWarnCode12()
   {
      return _WarnCode12;
   }
	
   /**
    * Gets the Warning Message Code for CallType validation field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Message Code for CallType validation or the specified default value.
    */
   public final int getWarnCode12( int defaultValue )
   {
      return _WarnCode12 == null ? defaultValue : _WarnCode12.intValue();
   }
                  
   /**
    * Gets the Warning Message Code for CallType validation field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Message Code for CallType validation or null.
    */
   public final Integer getWarnCode13()
   {
      return _WarnCode13;
   }
	
   /**
    * Gets the Warning Message Code for CallType validation field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Message Code for CallType validation or the specified default value.
    */
   public final int getWarnCode13( int defaultValue )
   {
      return _WarnCode13 == null ? defaultValue : _WarnCode13.intValue();
   }
                  
   /**
    * Gets the Warning Message Code for CallType validation field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Message Code for CallType validation or null.
    */
   public final Integer getWarnCode14()
   {
      return _WarnCode14;
   }
	
   /**
    * Gets the Warning Message Code for CallType validation field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Message Code for CallType validation or the specified default value.
    */
   public final int getWarnCode14( int defaultValue )
   {
      return _WarnCode14 == null ? defaultValue : _WarnCode14.intValue();
   }
                  
   /**
    * Gets the Warning Message Code for CallType validation field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Message Code for CallType validation or null.
    */
   public final Integer getWarnCode15()
   {
      return _WarnCode15;
   }
	
   /**
    * Gets the Warning Message Code for CallType validation field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Message Code for CallType validation or the specified default value.
    */
   public final int getWarnCode15( int defaultValue )
   {
      return _WarnCode15 == null ? defaultValue : _WarnCode15.intValue();
   }
                  
   /**
    * Gets the Warning Message Code for CallType validation field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Message Code for CallType validation or null.
    */
   public final Integer getWarnCode16()
   {
      return _WarnCode16;
   }
	
   /**
    * Gets the Warning Message Code for CallType validation field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Message Code for CallType validation or the specified default value.
    */
   public final int getWarnCode16( int defaultValue )
   {
      return _WarnCode16 == null ? defaultValue : _WarnCode16.intValue();
   }
                  
   /**
    * Gets the Warning Message Code for CallType validation field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Message Code for CallType validation or null.
    */
   public final Integer getWarnCode17()
   {
      return _WarnCode17;
   }
	
   /**
    * Gets the Warning Message Code for CallType validation field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Message Code for CallType validation or the specified default value.
    */
   public final int getWarnCode17( int defaultValue )
   {
      return _WarnCode17 == null ? defaultValue : _WarnCode17.intValue();
   }
                  
   /**
    * Gets the Warning Message parameter for validation field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Message parameter for validation or null.
    */
   public final String getWarnParam51()
   {
      return _WarnParam51;
   }
	
   /**
    * Gets the Warning Message parameter for validation field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Message parameter for validation or the specified default value.
    */
   public final String getWarnParam51( String defaultValue )
   {
      return _WarnParam51 == null ? defaultValue : _WarnParam51;
   }
                  
   /**
    * Gets the Warning Message parameter for validation field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Message parameter for validation or null.
    */
   public final String getWarnParam52()
   {
      return _WarnParam52;
   }
	
   /**
    * Gets the Warning Message parameter for validation field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Message parameter for validation or the specified default value.
    */
   public final String getWarnParam52( String defaultValue )
   {
      return _WarnParam52 == null ? defaultValue : _WarnParam52;
   }
                  
   /**
    * Gets the Warning Message parameter for validation field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Message parameter for validation or null.
    */
   public final String getWarnParam61()
   {
      return _WarnParam61;
   }
	
   /**
    * Gets the Warning Message parameter for validation field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Message parameter for validation or the specified default value.
    */
   public final String getWarnParam61( String defaultValue )
   {
      return _WarnParam61 == null ? defaultValue : _WarnParam61;
   }
                  
   /**
    * Gets the Warning Message parameter for validation field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Message parameter for validation or null.
    */
   public final String getWarnParam62()
   {
      return _WarnParam62;
   }
	
   /**
    * Gets the Warning Message parameter for validation field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Message parameter for validation or the specified default value.
    */
   public final String getWarnParam62( String defaultValue )
   {
      return _WarnParam62 == null ? defaultValue : _WarnParam62;
   }
                  
   /**
    * Gets the Warning Message parameter for validation field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Message parameter for validation or null.
    */
   public final String getWarnParam14()
   {
      return _WarnParam14;
   }
	
   /**
    * Gets the Warning Message parameter for validation field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Message parameter for validation or the specified default value.
    */
   public final String getWarnParam14( String defaultValue )
   {
      return _WarnParam14 == null ? defaultValue : _WarnParam14;
   }
                  
   /**
    * Gets the Warning Message parameter for validation field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Message parameter for validation or null.
    */
   public final String getWarnParam17()
   {
      return _WarnParam17;
   }
	
   /**
    * Gets the Warning Message parameter for validation field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Message parameter for validation or the specified default value.
    */
   public final String getWarnParam17( String defaultValue )
   {
      return _WarnParam17 == null ? defaultValue : _WarnParam17;
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
      _WarnCode2 = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _WarnCode3 = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _WarnCode4 = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _WarnCode5 = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _WarnCode6 = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _WarnCode7 = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _WarnCode8 = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _WarnCode9 = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _WarnCode10 = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _WarnCode11 = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _WarnCode12 = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _WarnCode13 = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _WarnCode14 = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _WarnCode15 = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _WarnCode16 = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _WarnCode17 = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _WarnParam51 = responseBuffer.decodeString(responseBuffer.getNextField());
      _WarnParam52 = responseBuffer.decodeString(responseBuffer.getNextField());
      _WarnParam61 = responseBuffer.decodeString(responseBuffer.getNextField());
      _WarnParam62 = responseBuffer.decodeString(responseBuffer.getNextField());
      _WarnParam14 = responseBuffer.decodeString(responseBuffer.getNextField());
      _WarnParam17 = responseBuffer.decodeString(responseBuffer.getNextField());
                  

   }

}
      
