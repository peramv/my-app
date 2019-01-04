// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Protected Fund Reset Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/ProtFundResetInq.doc">ProtFundResetInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class ProtFundResetInqRequest extends IFastRequest implements Serializable
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
    * Reset Date member variable.
    */
   private Date _ResetDate = null;
            
   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Fund Code member variable.
    */
   private String _rxFundCode = "";
            
   /**
    * ClassCode member variable.
    */
   private String _rxClassCode = "";
            
   /**
    * Date of Reset member variable.
    */
   private Date _AsOfDate = null;
            

   /**
    * Constructs the ProtFundResetInqRequest object.
    * 
    */
   ProtFundResetInqRequest()
   {
      super ( 243 );
   }

   /**
    * Constructs the ProtFundResetInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   ProtFundResetInqRequest( String hostEncoding )
   {
      super ( 243, hostEncoding );
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
    * Sets the Reset Date field for the request.
    * 
    * @param value  Value that the Reset Date will be set to.
    */
   public final void setResetDate( Date value )
   {
      assertUnsent();
      _ResetDate = value;
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
    * Sets the Fund Code field for the request.
    * 
    * @param value  Value that the Fund Code will be set to.
    */
   public final void setrxFundCode( String value )
   {
      assertUnsent();
      _rxFundCode = value;
   }
	
   /**
    * Sets the ClassCode field for the request.
    * 
    * @param value  Value that the ClassCode will be set to.
    */
   public final void setrxClassCode( String value )
   {
      assertUnsent();
      _rxClassCode = value;
   }
	
   /**
    * Sets the Date of Reset field for the request.
    * 
    * @param value  Value that the Date of Reset will be set to.
    */
   public final void setAsOfDate( Date value )
   {
      assertUnsent();
      _AsOfDate = value;
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
      requestBuffer.appendField( _ResetDate );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _rxFundCode );
      requestBuffer.appendField( _rxClassCode );
      requestBuffer.appendField( _AsOfDate );
   }

}

