
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Fund Serv Broker Validation view.
 * For additional view information see <A HREF="../../../../viewspecs/FndSrvBrkVal.doc">FndSrvBrkVal.doc</A>.
 * 
 * @author RTS Generated
 */
public class FndSrvBrkValView extends IFastView implements Serializable
{

   /**
    * Error / Warning code from rej-error member variable.
    */
   private Integer _WarnCode = null;
   
   /**
    * Error / Warning description from rej-error member variable.
    */
   private String _WarnDesc = null;
   
   /**
    * Value to be displayed in the error message 1 member variable.
    */
   private String _WarnValue1 = null;
   
   /**
    * Value to be displayed in the error message 2 member variable.
    */
   private String _WarnValue2 = null;
   
   /**
    * Value to be displayed in the error message 3 member variable.
    */
   private String _WarnValue3 = null;
   
   /**
    * Value to be displayed in the error message 4 member variable.
    */
   private String _WarnValue4 = null;
   
   /**
    * Auto Update Service Agent member variable.
    */
   private Boolean _AutoUpdServiceAgent = null;
   

   /**
    * Constructs the FndSrvBrkValView object.
    * 
    */
   public FndSrvBrkValView()
   {
      super ( new FndSrvBrkValRequest() );
   }

   /**
    * Constructs the FndSrvBrkValView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public FndSrvBrkValView( String hostEncoding )
   {
      super ( new FndSrvBrkValRequest( hostEncoding ) );
   }

   /**
    * Gets the FndSrvBrkValRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The FndSrvBrkValRequest object.
    */
   public final FndSrvBrkValRequest getRequest()
   {
      return (FndSrvBrkValRequest)getIFastRequest();
   }
        
   /**
    * Gets the Error / Warning code from rej-error field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Error / Warning code from rej-error or null.
    */
   public final Integer getWarnCode()
   {
      return _WarnCode;
   }
	
   /**
    * Gets the Error / Warning code from rej-error field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Error / Warning code from rej-error or the specified default value.
    */
   public final int getWarnCode( int defaultValue )
   {
      return _WarnCode == null ? defaultValue : _WarnCode.intValue();
   }
                  
   /**
    * Gets the Error / Warning description from rej-error field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Error / Warning description from rej-error or null.
    */
   public final String getWarnDesc()
   {
      return _WarnDesc;
   }
	
   /**
    * Gets the Error / Warning description from rej-error field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Error / Warning description from rej-error or the specified default value.
    */
   public final String getWarnDesc( String defaultValue )
   {
      return _WarnDesc == null ? defaultValue : _WarnDesc;
   }
                  
   /**
    * Gets the Value to be displayed in the error message 1 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Value to be displayed in the error message 1 or null.
    */
   public final String getWarnValue1()
   {
      return _WarnValue1;
   }
	
   /**
    * Gets the Value to be displayed in the error message 1 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Value to be displayed in the error message 1 or the specified default value.
    */
   public final String getWarnValue1( String defaultValue )
   {
      return _WarnValue1 == null ? defaultValue : _WarnValue1;
   }
                  
   /**
    * Gets the Value to be displayed in the error message 2 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Value to be displayed in the error message 2 or null.
    */
   public final String getWarnValue2()
   {
      return _WarnValue2;
   }
	
   /**
    * Gets the Value to be displayed in the error message 2 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Value to be displayed in the error message 2 or the specified default value.
    */
   public final String getWarnValue2( String defaultValue )
   {
      return _WarnValue2 == null ? defaultValue : _WarnValue2;
   }
                  
   /**
    * Gets the Value to be displayed in the error message 3 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Value to be displayed in the error message 3 or null.
    */
   public final String getWarnValue3()
   {
      return _WarnValue3;
   }
	
   /**
    * Gets the Value to be displayed in the error message 3 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Value to be displayed in the error message 3 or the specified default value.
    */
   public final String getWarnValue3( String defaultValue )
   {
      return _WarnValue3 == null ? defaultValue : _WarnValue3;
   }
                  
   /**
    * Gets the Value to be displayed in the error message 4 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Value to be displayed in the error message 4 or null.
    */
   public final String getWarnValue4()
   {
      return _WarnValue4;
   }
	
   /**
    * Gets the Value to be displayed in the error message 4 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Value to be displayed in the error message 4 or the specified default value.
    */
   public final String getWarnValue4( String defaultValue )
   {
      return _WarnValue4 == null ? defaultValue : _WarnValue4;
   }
                  
   /**
    * Gets the Auto Update Service Agent field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Auto Update Service Agent or null.
    */
   public final Boolean getAutoUpdServiceAgent()
   {
      return _AutoUpdServiceAgent;
   }
	
   /**
    * Gets the Auto Update Service Agent field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Auto Update Service Agent or the specified default value.
    */
   public final boolean getAutoUpdServiceAgent( boolean defaultValue )
   {
      return _AutoUpdServiceAgent == null ? defaultValue : _AutoUpdServiceAgent.booleanValue();
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
      _WarnCode = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _WarnDesc = responseBuffer.decodeString(responseBuffer.getNextField());
      _WarnValue1 = responseBuffer.decodeString(responseBuffer.getNextField());
      _WarnValue2 = responseBuffer.decodeString(responseBuffer.getNextField());
      _WarnValue3 = responseBuffer.decodeString(responseBuffer.getNextField());
      _WarnValue4 = responseBuffer.decodeString(responseBuffer.getNextField());
      _AutoUpdServiceAgent = responseBuffer.decodeBoolean(responseBuffer.getNextField());
                  

   }

}
      
