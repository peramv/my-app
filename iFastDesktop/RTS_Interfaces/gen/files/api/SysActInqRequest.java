// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * System Activity Report Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/SysActInq.doc">SysActInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class SysActInqRequest extends IFastRequest implements Serializable
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
    * For User ID member variable.
    */
   private String _ForUserID = "";
            
   /**
    * Start Date member variable.
    */
   private Date _StartDate = null;
            
   /**
    * End Date member variable.
    */
   private Date _EndDate = null;
            
   /**
    * For Company Code member variable.
    */
   private String _ForCompanyCode = "";
            
   /**
    * For Acivity member variable.
    */
   private String _ForActivity = "";
            
   /**
    * Exclude Unsuccessful Request member variable.
    */
   private Boolean _ExclUnsuccessfulRqst = new Boolean(false);
            
   /**
    * Exclude UserID member variable.
    */
   private String _ExcludeUserID = "";
            

   /**
    * Constructs the SysActInqRequest object.
    * 
    */
   SysActInqRequest()
   {
      super ( 362 );
   }

   /**
    * Constructs the SysActInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   SysActInqRequest( String hostEncoding )
   {
      super ( 362, hostEncoding );
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
    * Sets the For User ID field for the request.
    * 
    * @param value  Value that the For User ID will be set to.
    */
   public final void setForUserID( String value )
   {
      assertUnsent();
      _ForUserID = value;
   }
	
   /**
    * Sets the Start Date field for the request.
    * 
    * @param value  Value that the Start Date will be set to.
    */
   public final void setStartDate( Date value )
   {
      assertUnsent();
      _StartDate = value;
   }
	
   /**
    * Sets the End Date field for the request.
    * 
    * @param value  Value that the End Date will be set to.
    */
   public final void setEndDate( Date value )
   {
      assertUnsent();
      _EndDate = value;
   }
	
   /**
    * Sets the For Company Code field for the request.
    * 
    * @param value  Value that the For Company Code will be set to.
    */
   public final void setForCompanyCode( String value )
   {
      assertUnsent();
      _ForCompanyCode = value;
   }
	
   /**
    * Sets the For Acivity field for the request.
    * 
    * @param value  Value that the For Acivity will be set to.
    */
   public final void setForActivity( String value )
   {
      assertUnsent();
      _ForActivity = value;
   }
	
   /**
    * Sets the Exclude Unsuccessful Request field for the request.
    * 
    * @param value  Value that the Exclude Unsuccessful Request will be set to.
    */
   public final void setExclUnsuccessfulRqst( Boolean value )
   {
      assertUnsent();
      _ExclUnsuccessfulRqst = value;
   }
	
   /**
    * Sets the Exclude UserID field for the request.
    * 
    * @param value  Value that the Exclude UserID will be set to.
    */
   public final void setExcludeUserID( String value )
   {
      assertUnsent();
      _ExcludeUserID = value;
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
      encodeOverrideRepeatsField( requestBuffer );
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _ForUserID );
      requestBuffer.appendField( _StartDate );
      requestBuffer.appendField( _EndDate );
      requestBuffer.appendField( _ForCompanyCode );
      requestBuffer.appendField( _ForActivity );
      requestBuffer.appendField( _ExclUnsuccessfulRqst );
      requestBuffer.appendField( _ExcludeUserID );
   }

}

