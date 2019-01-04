// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Account Search request.
 * For additional view information see <A HREF="../../../../viewspecs/AcctSrch.doc">AcctSrch.doc</A>.
 * 
 * @author RTS Generated
 */
public class AcctSrchRequest extends IFastRequest implements Serializable
{

            
   /**
    * Session ID member variable.
    */
   private String _SessionId = "";
            
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
   private String _CompanyId = "";
            
            
            
            
   /**
    * Return Next or Previous record member variable.
    */
   private Boolean _NextOrPrevious = new Boolean(false);
            
   /**
    * Search for account with this Alt Account member variable.
    */
   private String _SrchAltAccount = "";
            
   /**
    * Search for account with this Broker member variable.
    */
   private String _SrchBrokerCode = "";
            
   /**
    * Return all accounts or single only  Y/N member variable.
    */
   private Boolean _OneAcctOnly = new Boolean(false);
            

   /**
    * Constructs the AcctSrchRequest object.
    * 
    */
   AcctSrchRequest()
   {
      super ( 198 );
   }

   /**
    * Constructs the AcctSrchRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AcctSrchRequest( String hostEncoding )
   {
      super ( 198, hostEncoding );
   }

   /**
    * Sets the Session ID field for the request.
    * 
    * @param value  Value that the Session ID will be set to.
    */
   public final void setSessionId( String value )
   {
      assertUnsent();
      _SessionId = value;
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
   public final void setCompanyId( String value )
   {
      assertUnsent();
      _CompanyId = value;
   }
	
   /**
    * Sets the Return Next or Previous record field for the request.
    * 
    * @param value  Value that the Return Next or Previous record will be set to.
    */
   public final void setNextOrPrevious( Boolean value )
   {
      assertUnsent();
      _NextOrPrevious = value;
   }
	
   /**
    * Sets the Search for account with this Alt Account field for the request.
    * 
    * @param value  Value that the Search for account with this Alt Account will be set to.
    */
   public final void setSrchAltAccount( String value )
   {
      assertUnsent();
      _SrchAltAccount = value;
   }
	
   /**
    * Sets the Search for account with this Broker field for the request.
    * 
    * @param value  Value that the Search for account with this Broker will be set to.
    */
   public final void setSrchBrokerCode( String value )
   {
      assertUnsent();
      _SrchBrokerCode = value;
   }
	
   /**
    * Sets the Return all accounts or single only  Y/N field for the request.
    * 
    * @param value  Value that the Return all accounts or single only  Y/N will be set to.
    */
   public final void setOneAcctOnly( Boolean value )
   {
      assertUnsent();
      _OneAcctOnly = value;
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
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _SessionId );
      requestBuffer.appendField( _User_Id );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyId );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      encodeOverrideRepeatsField( requestBuffer );
      requestBuffer.appendField( _NextOrPrevious );
      requestBuffer.appendField( _SrchAltAccount );
      requestBuffer.appendField( _SrchBrokerCode );
      requestBuffer.appendField( _OneAcctOnly );
   }

}

