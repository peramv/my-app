// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Fund Sponsor Fee Model Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/FundSpFMInq.doc">FundSpFMInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class FundSpFMInqRequest extends IFastRequest implements Serializable
{

   /**
    * SessionId member variable.
    */
   private String _SessionID = "";
            
   /**
    * User Id member variable.
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
    * Activity member variable.
    */
   private String _Acitivity = "";
            
            
            
   /**
    * Fund Group member variable.
    */
   private String _FundGroup = "";
            
   /**
    * Fee Model Code member variable.
    */
   private String _FeeModelCode = "";
            

   /**
    * Constructs the FundSpFMInqRequest object.
    * 
    */
   FundSpFMInqRequest()
   {
      super ( 307 );
   }

   /**
    * Constructs the FundSpFMInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   FundSpFMInqRequest( String hostEncoding )
   {
      super ( 307, hostEncoding );
   }

   /**
    * Sets the SessionId field for the request.
    * 
    * @param value  Value that the SessionId will be set to.
    */
   public final void setSessionID( String value )
   {
      assertUnsent();
      _SessionID = value;
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
    * Sets the Activity field for the request.
    * 
    * @param value  Value that the Activity will be set to.
    */
   public final void setAcitivity( String value )
   {
      assertUnsent();
      _Acitivity = value;
   }
	
   /**
    * Sets the Fund Group field for the request.
    * 
    * @param value  Value that the Fund Group will be set to.
    */
   public final void setFundGroup( String value )
   {
      assertUnsent();
      _FundGroup = value;
   }
	
   /**
    * Sets the Fee Model Code field for the request.
    * 
    * @param value  Value that the Fee Model Code will be set to.
    */
   public final void setFeeModelCode( String value )
   {
      assertUnsent();
      _FeeModelCode = value;
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
      requestBuffer.appendField( _SessionID );
      requestBuffer.appendField( _User_Id );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyId );
      encodeTrackField( requestBuffer );
      requestBuffer.appendField( _Acitivity );
      encodeOverrideRepeatsField( requestBuffer );
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _FundGroup );
      requestBuffer.appendField( _FeeModelCode );
   }

}

