// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Document List by Comply Rule Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/DocLComRuleInq.doc">DocLComRuleInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class DocLComRuleInqRequest extends IFastRequest implements Serializable
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
    * Comply Rule member variable.
    */
   private String _ComplyRule = "";
            
            
   /**
    * AccountType member variable.
    */
   private String _AcctType = "";
            
   /**
    * Tax Type member variable.
    */
   private String _TaxType = "";
            

   /**
    * Constructs the DocLComRuleInqRequest object.
    * 
    */
   DocLComRuleInqRequest()
   {
      super ( 443 );
   }

   /**
    * Constructs the DocLComRuleInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   DocLComRuleInqRequest( String hostEncoding )
   {
      super ( 443, hostEncoding );
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
    * Sets the Comply Rule field for the request.
    * 
    * @param value  Value that the Comply Rule will be set to.
    */
   public final void setComplyRule( String value )
   {
      assertUnsent();
      _ComplyRule = value;
   }
	
   /**
    * Sets the AccountType field for the request.
    * 
    * @param value  Value that the AccountType will be set to.
    */
   public final void setAcctType( String value )
   {
      assertUnsent();
      _AcctType = value;
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
      requestBuffer.appendField( _ComplyRule );
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _AcctType );
      requestBuffer.appendField( _TaxType );
   }

}

