// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Broker AMS Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/BrokerAMSInq.doc">BrokerAMSInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class BrokerAMSInqRequest extends IFastRequest implements Serializable
{

   /**
    * Session Id member variable.
    */
   private String _SessionId = "";
            
   /**
    * User Id member variable.
    */
   private String _User_Id = "";
            
   /**
    * LanguageCode member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * Company Id member variable.
    */
   private String _CompanyId = "";
            
            
            
            
            
   /**
    * Broker Code member variable.
    */
   private String _BrokerCode = "";
            
   /**
    * AMSCode member variable.
    */
   private String _AMSCode = "";
            
   /**
    * ExactMatch member variable.
    */
   private Boolean _ExactMatch = new Boolean(false);
            

   /**
    * Constructs the BrokerAMSInqRequest object.
    * 
    */
   BrokerAMSInqRequest()
   {
      super ( 250 );
   }

   /**
    * Constructs the BrokerAMSInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   BrokerAMSInqRequest( String hostEncoding )
   {
      super ( 250, hostEncoding );
   }

   /**
    * Sets the Session Id field for the request.
    * 
    * @param value  Value that the Session Id will be set to.
    */
   public final void setSessionId( String value )
   {
      assertUnsent();
      _SessionId = value;
   }
	
   /**
    * Sets the User Id field for the request.
    * 
    * @param value  Value that the User Id will be set to.
    */
   public final void setUser_Id( String value )
   {
      assertUnsent();
      _User_Id = value;
   }
	
   /**
    * Sets the LanguageCode field for the request.
    * 
    * @param value  Value that the LanguageCode will be set to.
    */
   public final void setLanguageCode( String value )
   {
      assertUnsent();
      _LanguageCode = value;
   }
	
   /**
    * Sets the Company Id field for the request.
    * 
    * @param value  Value that the Company Id will be set to.
    */
   public final void setCompanyId( String value )
   {
      assertUnsent();
      _CompanyId = value;
   }
	
   /**
    * Sets the Broker Code field for the request.
    * 
    * @param value  Value that the Broker Code will be set to.
    */
   public final void setBrokerCode( String value )
   {
      assertUnsent();
      _BrokerCode = value;
   }
	
   /**
    * Sets the AMSCode field for the request.
    * 
    * @param value  Value that the AMSCode will be set to.
    */
   public final void setAMSCode( String value )
   {
      assertUnsent();
      _AMSCode = value;
   }
	
   /**
    * Sets the ExactMatch field for the request.
    * 
    * @param value  Value that the ExactMatch will be set to.
    */
   public final void setExactMatch( Boolean value )
   {
      assertUnsent();
      _ExactMatch = value;
   }
	
   /**
    * Implements the abstract base method to encode
    * the host formatted request.
    * 
    * @param transaction
    *               Host formatted request object.
    */
   protected final void encodeFields( RTSRequestEncodeBuffer requestBuffer ) throws UnsupportedEncodingException
   {
      requestBuffer.appendField( _SessionId );
      requestBuffer.appendField( _User_Id );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyId );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      encodeOverrideRepeatsField( requestBuffer );
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _BrokerCode );
      requestBuffer.appendField( _AMSCode );
      requestBuffer.appendField( _ExactMatch );
   }

}

