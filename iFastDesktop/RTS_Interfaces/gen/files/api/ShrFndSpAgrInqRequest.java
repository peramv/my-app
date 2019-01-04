// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Shareholder - Fund Sponsor Agreement Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/ShrFndSpAgrInq.doc">ShrFndSpAgrInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class ShrFndSpAgrInqRequest extends IFastRequest implements Serializable
{

   /**
    * Session Id member variable.
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
    * Company Id member variable.
    */
   private String _CompanyId = "";
            
            
            
            
            
   /**
    * Shareholder Number member variable.
    */
   private String _ShrNum = "0";
            
   /**
    * Fund Group/ Sponsor member variable.
    */
   private String _FundGroup = "";
            

   /**
    * Constructs the ShrFndSpAgrInqRequest object.
    * 
    */
   ShrFndSpAgrInqRequest()
   {
      super ( 299 );
   }

   /**
    * Constructs the ShrFndSpAgrInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   ShrFndSpAgrInqRequest( String hostEncoding )
   {
      super ( 299, hostEncoding );
   }

   /**
    * Sets the Session Id field for the request.
    * 
    * @param value  Value that the Session Id will be set to.
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
    * Sets the Fund Group/ Sponsor field for the request.
    * 
    * @param value  Value that the Fund Group/ Sponsor will be set to.
    */
   public final void setFundGroup( String value )
   {
      assertUnsent();
      _FundGroup = value;
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
      encodeActivityField( requestBuffer );
      encodeOverrideRepeatsField( requestBuffer );
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _ShrNum );
      requestBuffer.appendField( _FundGroup );
   }

}

