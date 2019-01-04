// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * International Wire Validation request.
 * For additional view information see <A HREF="../../../../viewspecs/IntlWireVldn.doc">IntlWireVldn.doc</A>.
 * 
 * @author RTS Generated
 */
public class IntlWireVldnRequest extends IFastRequest implements Serializable
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
    * Fund Code member variable.
    */
   private String _FundCode = "";
            
   /**
    * Class Code member variable.
    */
   private String _ClassCode = "";
            
   /**
    * Settlement Currency member variable.
    */
   private String _SettleCurr = "";
            
   /**
    * Country Code member variable.
    */
   private String _CntryCode = "";
            

   /**
    * Constructs the IntlWireVldnRequest object.
    * 
    */
   IntlWireVldnRequest()
   {
      super ( 210 );
   }

   /**
    * Constructs the IntlWireVldnRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   IntlWireVldnRequest( String hostEncoding )
   {
      super ( 210, hostEncoding );
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
    * Sets the Fund Code field for the request.
    * 
    * @param value  Value that the Fund Code will be set to.
    */
   public final void setFundCode( String value )
   {
      assertUnsent();
      _FundCode = value;
   }
	
   /**
    * Sets the Class Code field for the request.
    * 
    * @param value  Value that the Class Code will be set to.
    */
   public final void setClassCode( String value )
   {
      assertUnsent();
      _ClassCode = value;
   }
	
   /**
    * Sets the Settlement Currency field for the request.
    * 
    * @param value  Value that the Settlement Currency will be set to.
    */
   public final void setSettleCurr( String value )
   {
      assertUnsent();
      _SettleCurr = value;
   }
	
   /**
    * Sets the Country Code field for the request.
    * 
    * @param value  Value that the Country Code will be set to.
    */
   public final void setCntryCode( String value )
   {
      assertUnsent();
      _CntryCode = value;
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
      requestBuffer.appendField( _FundCode );
      requestBuffer.appendField( _ClassCode );
      requestBuffer.appendField( _SettleCurr );
      requestBuffer.appendField( _CntryCode );
   }

}

