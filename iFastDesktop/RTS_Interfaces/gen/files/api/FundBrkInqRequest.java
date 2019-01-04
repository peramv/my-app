// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Fund Broker Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/FundBrkInq.doc">FundBrkInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class FundBrkInqRequest extends IFastRequest implements Serializable
{

   /**
    * Session ID member variable.
    */
   private String _SessionID = "";
            
   /**
    * User ID member variable.
    */
   private String _User_Id = "";
            
   /**
    * Language Code member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * Company ID member variable.
    */
   private String _CompanyID = "";
            
            
            
            
            
   /**
    * Fund Broker Last Name member variable.
    */
   private String _FundBrokerLastName = "";
            
   /**
    * Fund Broker First Name member variable.
    */
   private String _FundBrokerFirstName = "";
            
   /**
    * Fund Broker Code member variable.
    */
   private String _FundBrokerCode = "";
            

   /**
    * Constructs the FundBrkInqRequest object.
    * 
    */
   FundBrkInqRequest()
   {
      super ( 326 );
   }

   /**
    * Constructs the FundBrkInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   FundBrkInqRequest( String hostEncoding )
   {
      super ( 326, hostEncoding );
   }

   /**
    * Sets the Session ID field for the request.
    * 
    * @param value  Value that the Session ID will be set to.
    */
   public final void setSessionID( String value )
   {
      assertUnsent();
      _SessionID = value;
   }
	
   /**
    * Sets the User ID field for the request.
    * 
    * @param value  Value that the User ID will be set to.
    */
   public final void setUser_Id( String value )
   {
      assertUnsent();
      _User_Id = value;
   }
	
   /**
    * Sets the Language Code field for the request.
    * 
    * @param value  Value that the Language Code will be set to.
    */
   public final void setLanguageCode( String value )
   {
      assertUnsent();
      _LanguageCode = value;
   }
	
   /**
    * Sets the Company ID field for the request.
    * 
    * @param value  Value that the Company ID will be set to.
    */
   public final void setCompanyID( String value )
   {
      assertUnsent();
      _CompanyID = value;
   }
	
   /**
    * Sets the Fund Broker Last Name field for the request.
    * 
    * @param value  Value that the Fund Broker Last Name will be set to.
    */
   public final void setFundBrokerLastName( String value )
   {
      assertUnsent();
      _FundBrokerLastName = value;
   }
	
   /**
    * Sets the Fund Broker First Name field for the request.
    * 
    * @param value  Value that the Fund Broker First Name will be set to.
    */
   public final void setFundBrokerFirstName( String value )
   {
      assertUnsent();
      _FundBrokerFirstName = value;
   }
	
   /**
    * Sets the Fund Broker Code field for the request.
    * 
    * @param value  Value that the Fund Broker Code will be set to.
    */
   public final void setFundBrokerCode( String value )
   {
      assertUnsent();
      _FundBrokerCode = value;
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
      requestBuffer.appendField( _SessionID );
      requestBuffer.appendField( _User_Id );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyID );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      encodeOverrideRepeatsField( requestBuffer );
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _FundBrokerLastName );
      requestBuffer.appendField( _FundBrokerFirstName );
      requestBuffer.appendField( _FundBrokerCode );
   }

}

