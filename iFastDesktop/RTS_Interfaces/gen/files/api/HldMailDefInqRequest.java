// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Hold-Mail Defaults request.
 * For additional view information see <A HREF="../../../../viewspecs/HldMailDefInq.doc">HldMailDefInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class HldMailDefInqRequest extends IFastRequest implements Serializable
{

   /**
    * SessionID member variable.
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
    * Fund Group member variable.
    */
   private String _FundGroup = "";
            
   /**
    * Return all records member variable.
    */
   private Boolean _AllGroups = new Boolean(false);
            

   /**
    * Constructs the HldMailDefInqRequest object.
    * 
    */
   HldMailDefInqRequest()
   {
      super ( 352 );
   }

   /**
    * Constructs the HldMailDefInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   HldMailDefInqRequest( String hostEncoding )
   {
      super ( 352, hostEncoding );
   }

   /**
    * Sets the SessionID field for the request.
    * 
    * @param value  Value that the SessionID will be set to.
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
    * Sets the Return all records field for the request.
    * 
    * @param value  Value that the Return all records will be set to.
    */
   public final void setAllGroups( Boolean value )
   {
      assertUnsent();
      _AllGroups = value;
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
      requestBuffer.appendField( _FundGroup );
      requestBuffer.appendField( _AllGroups );
   }

}

