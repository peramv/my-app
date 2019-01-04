// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * OPC Confirm Reprint Maint request.
 * For additional view information see <A HREF="../../../../viewspecs/OPCReprintUpd.doc">OPCReprintUpd.doc</A>.
 * 
 * @author RTS Generated
 */
public class OPCReprintUpdRequest extends IFastRequest implements Serializable
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
    * Language Code member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * Company Id member variable.
    */
   private String _CompanyId = "";
            
            
            
   /**
    * RunMode member variable.
    */
   private String _RunMode = "";
            
   /**
    * Transaction Id member variable.
    */
   private Integer _TransId = null;
            
   /**
    * Client Copy member variable.
    */
   private Boolean _ClientCopy = new Boolean(false);
            
   /**
    * BrokerCopy member variable.
    */
   private Boolean _BrokerCopy = new Boolean(false);
            
   /**
    * SalesRepCopy member variable.
    */
   private Boolean _SalesRepCopy = new Boolean(false);
            

   /**
    * Constructs the OPCReprintUpdRequest object.
    * 
    */
   OPCReprintUpdRequest()
   {
      super ( 346 );
   }

   /**
    * Constructs the OPCReprintUpdRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   OPCReprintUpdRequest( String hostEncoding )
   {
      super ( 346, hostEncoding );
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
    * Sets the RunMode field for the request.
    * 
    * @param value  Value that the RunMode will be set to.
    */
   public final void setRunMode( String value )
   {
      assertUnsent();
      _RunMode = value;
   }
	
   /**
    * Sets the Transaction Id field for the request.
    * 
    * @param value  Value that the Transaction Id will be set to.
    */
   public final void setTransId( Integer value )
   {
      assertUnsent();
      _TransId = value;
   }
	
   /**
    * Sets the Client Copy field for the request.
    * 
    * @param value  Value that the Client Copy will be set to.
    */
   public final void setClientCopy( Boolean value )
   {
      assertUnsent();
      _ClientCopy = value;
   }
	
   /**
    * Sets the BrokerCopy field for the request.
    * 
    * @param value  Value that the BrokerCopy will be set to.
    */
   public final void setBrokerCopy( Boolean value )
   {
      assertUnsent();
      _BrokerCopy = value;
   }
	
   /**
    * Sets the SalesRepCopy field for the request.
    * 
    * @param value  Value that the SalesRepCopy will be set to.
    */
   public final void setSalesRepCopy( Boolean value )
   {
      assertUnsent();
      _SalesRepCopy = value;
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
      requestBuffer.appendField( _RunMode );
      requestBuffer.appendField( _TransId );
      requestBuffer.appendField( _ClientCopy );
      requestBuffer.appendField( _BrokerCopy );
      requestBuffer.appendField( _SalesRepCopy );
   }

}

