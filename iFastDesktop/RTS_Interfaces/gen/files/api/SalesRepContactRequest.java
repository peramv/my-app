// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Sales representative contact details request.
 * For additional view information see <A HREF="../../../../viewspecs/SalesRepContact.doc">SalesRepContact.doc</A>.
 * 
 * @author RTS Generated
 */
public class SalesRepContactRequest extends IFastRequest implements Serializable
{

   /**
    * Broker/dealer/agency code member variable.
    */
   private String _BrokerCode = "";
            
   /**
    * Branch code member variable.
    */
   private String _BranchCode = "";
            
   /**
    * Sales representative code member variable.
    */
   private String _SalesRepCode = "";
            
   /**
    * SessionId member variable.
    */
   private String _SessionId = "";
            
   /**
    * UserId member variable.
    */
   private String _User_Id = "";
            
   /**
    * LanguageCode member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * CompanyId member variable.
    */
   private String _CompanyId = "";
            
            
            

   /**
    * Constructs the SalesRepContactRequest object.
    * 
    */
   SalesRepContactRequest()
   {
      super ( 10 );
   }

   /**
    * Constructs the SalesRepContactRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   SalesRepContactRequest( String hostEncoding )
   {
      super ( 10, hostEncoding );
   }

   /**
    * Sets the Broker/dealer/agency code field for the request.
    * 
    * @param value  Value that the Broker/dealer/agency code will be set to.
    */
   public final void setBrokerCode( String value )
   {
      assertUnsent();
      _BrokerCode = value;
   }
	
   /**
    * Sets the Branch code field for the request.
    * 
    * @param value  Value that the Branch code will be set to.
    */
   public final void setBranchCode( String value )
   {
      assertUnsent();
      _BranchCode = value;
   }
	
   /**
    * Sets the Sales representative code field for the request.
    * 
    * @param value  Value that the Sales representative code will be set to.
    */
   public final void setSalesRepCode( String value )
   {
      assertUnsent();
      _SalesRepCode = value;
   }
	
   /**
    * Sets the SessionId field for the request.
    * 
    * @param value  Value that the SessionId will be set to.
    */
   public final void setSessionId( String value )
   {
      assertUnsent();
      _SessionId = value;
   }
	
   /**
    * Sets the UserId field for the request.
    * 
    * @param value  Value that the UserId will be set to.
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
    * Sets the CompanyId field for the request.
    * 
    * @param value  Value that the CompanyId will be set to.
    */
   public final void setCompanyId( String value )
   {
      assertUnsent();
      _CompanyId = value;
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
      requestBuffer.appendField( _BrokerCode );
      requestBuffer.appendField( _BranchCode );
      requestBuffer.appendField( _SalesRepCode );
      requestBuffer.appendField( _SessionId );
      requestBuffer.appendField( _User_Id );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyId );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
   }

}

