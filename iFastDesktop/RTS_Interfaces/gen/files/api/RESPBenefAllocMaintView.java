
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * RESP Beneficiary Allocaion Maint and Validation view.
 * For additional view information see <A HREF="../../../../viewspecs/RESPBenefAllocMaint.doc">RESPBenefAllocMaint.doc</A>.
 * 
 * @author RTS Generated
 */
public class RESPBenefAllocMaintView extends IFastView implements Serializable
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
    * Constructs the RESPBenefAllocMaintView object.
    * 
    */
   public RESPBenefAllocMaintView()
   {
      super ( new RESPBenefAllocMaintRequest() );
   }

   /**
    * Constructs the RESPBenefAllocMaintView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public RESPBenefAllocMaintView( String hostEncoding )
   {
      super ( new RESPBenefAllocMaintRequest( hostEncoding ) );
   }

   /**
    * Gets the RESPBenefAllocMaintRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The RESPBenefAllocMaintRequest object.
    */
   public final RESPBenefAllocMaintRequest getRequest()
   {
      return (RESPBenefAllocMaintRequest)getIFastRequest();
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
      _WarnParam51 = responseBuffer.decodeString(responseBuffer.getNextField());
      _WarnParam52 = responseBuffer.decodeString(responseBuffer.getNextField());
      _WarnParam61 = responseBuffer.decodeString(responseBuffer.getNextField());
      _WarnParam62 = responseBuffer.decodeString(responseBuffer.getNextField());
                  

   }

}
      
