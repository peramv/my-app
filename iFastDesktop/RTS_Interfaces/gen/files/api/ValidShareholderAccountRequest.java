// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Valid Shareholder/Account request.
 * For additional view information see <A HREF="../../../../viewspecs/ValidShareholderAccount.doc">ValidShareholderAccount.doc</A>.
 * 
 * @author RTS Generated
 */
public class ValidShareholderAccountRequest extends IFastRequest implements Serializable
{

            
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
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Shareholder Number member variable.
    */
   private String _ShrNum = "0";
            
            
            
   /**
    * Called by Process member variable.
    */
   private String _CalledByProc = "";
            

   /**
    * Constructs the ValidShareholderAccountRequest object.
    * 
    */
   ValidShareholderAccountRequest()
   {
      super ( 120 );
   }

   /**
    * Constructs the ValidShareholderAccountRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   ValidShareholderAccountRequest( String hostEncoding )
   {
      super ( 120, hostEncoding );
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
    * Sets the Shareholder Number field for the request.
    * 
    * @param value  Value that the Shareholder Number will be set to.
    */
   public final void setShrNum( String value )
   {
      assertUnsent();
      _ShrNum = value;
   }
	
   /**
    * Sets the Called by Process field for the request.
    * 
    * @param value  Value that the Called by Process will be set to.
    */
   public final void setCalledByProc( String value )
   {
      assertUnsent();
      _CalledByProc = value;
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
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _ShrNum );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _CalledByProc );
   }

}

