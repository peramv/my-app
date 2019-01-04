
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Default Fund Broker Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/DefFundBrkInq.doc">DefFundBrkInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class DefFundBrkInqView extends IFastView implements Serializable
{

   /**
    * Fund Broker Code member variable.
    */
   private String _FundBroker = null;
   
   /**
    * IsDefault member variable.
    */
   private Boolean _IsDefault = null;
   
   /**
    * Level member variable.
    */
   private String _Level = null;
   

   /**
    * Constructs the DefFundBrkInqView object.
    * 
    */
   public DefFundBrkInqView()
   {
      super ( new DefFundBrkInqRequest() );
   }

   /**
    * Constructs the DefFundBrkInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public DefFundBrkInqView( String hostEncoding )
   {
      super ( new DefFundBrkInqRequest( hostEncoding ) );
   }

   /**
    * Gets the DefFundBrkInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The DefFundBrkInqRequest object.
    */
   public final DefFundBrkInqRequest getRequest()
   {
      return (DefFundBrkInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Fund Broker Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Fund Broker Code or null.
    */
   public final String getFundBroker()
   {
      return _FundBroker;
   }
	
   /**
    * Gets the Fund Broker Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Broker Code or the specified default value.
    */
   public final String getFundBroker( String defaultValue )
   {
      return _FundBroker == null ? defaultValue : _FundBroker;
   }
                  
   /**
    * Gets the IsDefault field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the IsDefault or null.
    */
   public final Boolean getIsDefault()
   {
      return _IsDefault;
   }
	
   /**
    * Gets the IsDefault field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the IsDefault or the specified default value.
    */
   public final boolean getIsDefault( boolean defaultValue )
   {
      return _IsDefault == null ? defaultValue : _IsDefault.booleanValue();
   }
                  
   /**
    * Gets the Level field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Level or null.
    */
   public final String getLevel()
   {
      return _Level;
   }
	
   /**
    * Gets the Level field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Level or the specified default value.
    */
   public final String getLevel( String defaultValue )
   {
      return _Level == null ? defaultValue : _Level;
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
      _FundBroker = responseBuffer.decodeString(responseBuffer.getNextField());
      _IsDefault = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _Level = responseBuffer.decodeString(responseBuffer.getNextField());
                  

   }

}
      
