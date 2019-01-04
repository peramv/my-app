// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Redemption Code by Tax Type Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/RedTaxInq.doc">RedTaxInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class RedTaxInqRequest extends IFastRequest implements Serializable
{

   /**
    * Tax Type member variable.
    */
   private String _TaxType = "";
            
   /**
    * Code Type member variable.
    */
   private String _CodeType = "";
            
            
   /**
    * Session ID member variable.
    */
   private String _SessionID = "";
            
   /**
    * User ID member variable.
    */
   private String _User_ID = "";
            
   /**
    * Language Code member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * Company ID member variable.
    */
   private String _CompanyID = "";
            
            
            

   /**
    * Constructs the RedTaxInqRequest object.
    * 
    */
   RedTaxInqRequest()
   {
      super ( 138 );
   }

   /**
    * Constructs the RedTaxInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   RedTaxInqRequest( String hostEncoding )
   {
      super ( 138, hostEncoding );
   }

   /**
    * Sets the Tax Type field for the request.
    * 
    * @param value  Value that the Tax Type will be set to.
    */
   public final void setTaxType( String value )
   {
      assertUnsent();
      _TaxType = value;
   }
	
   /**
    * Sets the Code Type field for the request.
    * 
    * @param value  Value that the Code Type will be set to.
    */
   public final void setCodeType( String value )
   {
      assertUnsent();
      _CodeType = value;
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
   public final void setUser_ID( String value )
   {
      assertUnsent();
      _User_ID = value;
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
    * Implements the abstract base method to encode
    * the host formatted request.
    * 
    * @param transaction
    *               Host formatted request object.
    */
   protected final void encodeFields( RTSRequestEncodeBuffer requestBuffer ) throws UnsupportedEncodingException
   {
      requestBuffer.appendField( _TaxType );
      requestBuffer.appendField( _CodeType );
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _SessionID );
      requestBuffer.appendField( _User_ID );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyID );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
   }

}

