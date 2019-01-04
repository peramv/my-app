// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * AMSCode request.
 * For additional view information see <A HREF="../../../../viewspecs/AMSCodeInq.doc">AMSCodeInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class AMSCodeInqRequest extends IFastRequest implements Serializable
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
    * AMS Code member variable.
    */
   private String _AMSCode = "";
            
            
            
   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * AMS Type member variable.
    */
   private String _AMSType = "";
            
            
   /**
    * As of Date member variable.
    */
   private Date _ASofDate = null;
            
   /**
    * AMS Duplicate Check member variable.
    */
   private Boolean _AMSDuplicate = new Boolean(false);
            

   /**
    * Constructs the AMSCodeInqRequest object.
    * 
    */
   AMSCodeInqRequest()
   {
      super ( 179 );
   }

   /**
    * Constructs the AMSCodeInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AMSCodeInqRequest( String hostEncoding )
   {
      super ( 179, hostEncoding );
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
    * Sets the AMS Code field for the request.
    * 
    * @param value  Value that the AMS Code will be set to.
    */
   public final void setAMSCode( String value )
   {
      assertUnsent();
      _AMSCode = value;
   }
	
   /**
    * Sets the Account Number field for the request.
    * 
    * @param value  Value that the Account Number will be set to.
    */
   public final void setAccountNum( String value )
   {
      assertUnsent();
      _AccountNum = value;
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
    * Sets the As of Date field for the request.
    * 
    * @param value  Value that the As of Date will be set to.
    */
   public final void setASofDate( Date value )
   {
      assertUnsent();
      _ASofDate = value;
   }
	
   /**
    * Sets the AMS Duplicate Check field for the request.
    * 
    * @param value  Value that the AMS Duplicate Check will be set to.
    */
   public final void setAMSDuplicate( Boolean value )
   {
      assertUnsent();
      _AMSDuplicate = value;
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
      requestBuffer.appendField( _AMSCode );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _AMSType );
      encodeOverrideRepeatsField( requestBuffer );
      requestBuffer.appendField( _ASofDate );
      requestBuffer.appendField( _AMSDuplicate );
   }

}

