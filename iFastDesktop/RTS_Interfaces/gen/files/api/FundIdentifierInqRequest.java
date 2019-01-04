// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Fund Identifier Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/FundIdentifierInq.doc">FundIdentifierInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class FundIdentifierInqRequest extends IFastRequest implements Serializable
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
    * ID Type member variable.
    */
   private String _IDType = "";
            
   /**
    * ID Code member variable.
    */
   private String _IDCode = "";
            

   /**
    * Constructs the FundIdentifierInqRequest object.
    * 
    */
   FundIdentifierInqRequest()
   {
      super ( 281 );
   }

   /**
    * Constructs the FundIdentifierInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   FundIdentifierInqRequest( String hostEncoding )
   {
      super ( 281, hostEncoding );
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
    * Sets the ID Type field for the request.
    * 
    * @param value  Value that the ID Type will be set to.
    */
   public final void setIDType( String value )
   {
      assertUnsent();
      _IDType = value;
   }
	
   /**
    * Sets the ID Code field for the request.
    * 
    * @param value  Value that the ID Code will be set to.
    */
   public final void setIDCode( String value )
   {
      assertUnsent();
      _IDCode = value;
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
      requestBuffer.appendField( _IDType );
      requestBuffer.appendField( _IDCode );
   }

}

