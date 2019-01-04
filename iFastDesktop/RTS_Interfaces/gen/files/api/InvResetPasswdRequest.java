// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * eInvestor Reset Password request.
 * For additional view information see <A HREF="../../../../viewspecs/InvResetPasswd.doc">InvResetPasswd.doc</A>.
 * 
 * @author RTS Generated
 */
public class InvResetPasswdRequest extends IFastRequest implements Serializable
{

   /**
    * UserId member variable.
    */
   private String _User_Id = "";
            
   /**
    * CompanyId member variable.
    */
   private String _CompanyId = "";
            
   /**
    * Language member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * Currency member variable.
    */
   private String _Currency = "";
            
            
            
   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Password member variable.
    */
   private String _Password = "";
            
   /**
    * MemorableDate member variable.
    */
   private Date _MemorableDate = null;
            
   /**
    * MemorableDateReln member variable.
    */
   private String _MemorableDateReln = "";
            

   /**
    * Constructs the InvResetPasswdRequest object.
    * 
    */
   InvResetPasswdRequest()
   {
      super ( 189 );
   }

   /**
    * Constructs the InvResetPasswdRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   InvResetPasswdRequest( String hostEncoding )
   {
      super ( 189, hostEncoding );
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
    * Sets the Language field for the request.
    * 
    * @param value  Value that the Language will be set to.
    */
   public final void setLanguageCode( String value )
   {
      assertUnsent();
      _LanguageCode = value;
   }
	
   /**
    * Sets the Currency field for the request.
    * 
    * @param value  Value that the Currency will be set to.
    */
   public final void setCurrency( String value )
   {
      assertUnsent();
      _Currency = value;
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
    * Sets the Password field for the request.
    * 
    * @param value  Value that the Password will be set to.
    */
   public final void setPassword( String value )
   {
      assertUnsent();
      _Password = value;
   }
	
   /**
    * Sets the MemorableDate field for the request.
    * 
    * @param value  Value that the MemorableDate will be set to.
    */
   public final void setMemorableDate( Date value )
   {
      assertUnsent();
      _MemorableDate = value;
   }
	
   /**
    * Sets the MemorableDateReln field for the request.
    * 
    * @param value  Value that the MemorableDateReln will be set to.
    */
   public final void setMemorableDateReln( String value )
   {
      assertUnsent();
      _MemorableDateReln = value;
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
      requestBuffer.appendField( _User_Id );
      requestBuffer.appendField( _CompanyId );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _Currency );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _Password );
      requestBuffer.appendField( _MemorableDate );
      requestBuffer.appendField( _MemorableDateReln );
   }

}

