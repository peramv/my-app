// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Message Event Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/MesgEventInq.doc">MesgEventInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class MesgEventInqRequest extends IFastRequest implements Serializable
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
    * Envelope ID member variable.
    */
   private String _EnvelopeID = "0";
            
   /**
    * Activity ID member variable.
    */
   private String _ActivityID = "0";
            

   /**
    * Constructs the MesgEventInqRequest object.
    * 
    */
   MesgEventInqRequest()
   {
      super ( 335 );
   }

   /**
    * Constructs the MesgEventInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   MesgEventInqRequest( String hostEncoding )
   {
      super ( 335, hostEncoding );
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
    * Sets the Envelope ID field for the request.
    * 
    * @param value  Value that the Envelope ID will be set to.
    */
   public final void setEnvelopeID( String value )
   {
      assertUnsent();
      _EnvelopeID = value;
   }
	
   /**
    * Sets the Activity ID field for the request.
    * 
    * @param value  Value that the Activity ID will be set to.
    */
   public final void setActivityID( String value )
   {
      assertUnsent();
      _ActivityID = value;
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
      requestBuffer.appendField( _EnvelopeID );
      requestBuffer.appendField( _ActivityID );
   }

}

