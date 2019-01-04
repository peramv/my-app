// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Fee Model Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/view305.doc">view305.doc</A>.
 * 
 * @author RTS Generated
 */
public class view305Request extends IFastRequest implements Serializable
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
    * Fee Model Code member variable.
    */
   private String _FeeModelCode = "";
            
   /**
    * Fee Model Description member variable.
    */
   private String _FeeModelDesc = "";
            
   /**
    * Holding Company Code member variable.
    */
   private String _HoldCoCode = "";
            
   /**
    * Holding Company Name member variable.
    */
   private String _HoldCoName = "";
            
   /**
    * As of Date member variable.
    */
   private Date _AsofDate = null;
            
   /**
    * Flag that indicates if all record will be returned member variable.
    */
   private Boolean _SearchAll = new Boolean(false);
            

   /**
    * Constructs the view305Request object.
    * 
    */
   view305Request()
   {
      super ( 305 );
   }

   /**
    * Constructs the view305Request object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   view305Request( String hostEncoding )
   {
      super ( 305, hostEncoding );
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
    * Sets the Fee Model Description field for the request.
    * 
    * @param value  Value that the Fee Model Description will be set to.
    */
   public final void setFeeModelDesc( String value )
   {
      assertUnsent();
      _FeeModelDesc = value;
   }
	
   /**
    * Sets the Holding Company Code field for the request.
    * 
    * @param value  Value that the Holding Company Code will be set to.
    */
   public final void setHoldCoCode( String value )
   {
      assertUnsent();
      _HoldCoCode = value;
   }
	
   /**
    * Sets the Holding Company Name field for the request.
    * 
    * @param value  Value that the Holding Company Name will be set to.
    */
   public final void setHoldCoName( String value )
   {
      assertUnsent();
      _HoldCoName = value;
   }
	
   /**
    * Sets the As of Date field for the request.
    * 
    * @param value  Value that the As of Date will be set to.
    */
   public final void setAsofDate( Date value )
   {
      assertUnsent();
      _AsofDate = value;
   }
	
   /**
    * Sets the Flag that indicates if all record will be returned field for the request.
    * 
    * @param value  Value that the Flag that indicates if all record will be returned will be set to.
    */
   public final void setSearchAll( Boolean value )
   {
      assertUnsent();
      _SearchAll = value;
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
      requestBuffer.appendField( _FeeModelCode );
      requestBuffer.appendField( _FeeModelDesc );
      requestBuffer.appendField( _HoldCoCode );
      requestBuffer.appendField( _HoldCoName );
      requestBuffer.appendField( _AsofDate );
      requestBuffer.appendField( _SearchAll );
   }

}

