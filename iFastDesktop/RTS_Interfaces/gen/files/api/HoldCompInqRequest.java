// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Holding Company Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/HoldCompInq.doc">HoldCompInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class HoldCompInqRequest extends IFastRequest implements Serializable
{

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
    * Holding Company Code member variable.
    */
   private String _HoldCoCode = "";
            
   /**
    * Holding Company Name member variable.
    */
   private String _HoldCoName = "";
            
   /**
    * As Of Date member variable.
    */
   private Date _AsOfDate = null;
            
   /**
    * Flag that indicates if all records will be returned member variable.
    */
   private Boolean _SearchAll = new Boolean(false);
            

   /**
    * Constructs the HoldCompInqRequest object.
    * 
    */
   HoldCompInqRequest()
   {
      super ( 448 );
   }

   /**
    * Constructs the HoldCompInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   HoldCompInqRequest( String hostEncoding )
   {
      super ( 448, hostEncoding );
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
    * Sets the As Of Date field for the request.
    * 
    * @param value  Value that the As Of Date will be set to.
    */
   public final void setAsOfDate( Date value )
   {
      assertUnsent();
      _AsOfDate = value;
   }
	
   /**
    * Sets the Flag that indicates if all records will be returned field for the request.
    * 
    * @param value  Value that the Flag that indicates if all records will be returned will be set to.
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
      requestBuffer.appendField( _User_ID );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyID );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _HoldCoCode );
      requestBuffer.appendField( _HoldCoName );
      requestBuffer.appendField( _AsOfDate );
      requestBuffer.appendField( _SearchAll );
   }

}

