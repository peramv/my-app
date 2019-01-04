// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * AMS Rules Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/AMSRulesInq.doc">AMSRulesInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class AMSRulesInqRequest extends IFastRequest implements Serializable
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
    * AMSCode member variable.
    */
   private String _AMSCode = "";
            
   /**
    * Effective date member variable.
    */
   private Date _EffectiveDate = null;
            
   /**
    * AMS Type member variable.
    */
   private String _AMSType = "";
            

   /**
    * Constructs the AMSRulesInqRequest object.
    * 
    */
   AMSRulesInqRequest()
   {
      super ( 262 );
   }

   /**
    * Constructs the AMSRulesInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AMSRulesInqRequest( String hostEncoding )
   {
      super ( 262, hostEncoding );
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
    * Sets the Effective date field for the request.
    * 
    * @param value  Value that the Effective date will be set to.
    */
   public final void setEffectiveDate( Date value )
   {
      assertUnsent();
      _EffectiveDate = value;
   }
	
   /**
    * Sets the AMS Type field for the request.
    * 
    * @param value  Value that the AMS Type will be set to.
    */
   public final void setAMSType( String value )
   {
      assertUnsent();
      _AMSType = value;
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
      requestBuffer.appendField( _AMSCode );
      requestBuffer.appendField( _EffectiveDate );
      requestBuffer.appendField( _AMSType );
   }

}

