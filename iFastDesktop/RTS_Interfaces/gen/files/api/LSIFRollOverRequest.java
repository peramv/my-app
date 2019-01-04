// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * LSIF RollOver Rules request.
 * For additional view information see <A HREF="../../../../viewspecs/LSIFRollOver.doc">LSIFRollOver.doc</A>.
 * 
 * @author RTS Generated
 */
public class LSIFRollOverRequest extends IFastRequest implements Serializable
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
    * From Fund member variable.
    */
   private String _FromFund = "";
            
   /**
    * From Class member variable.
    */
   private String _FromClass = "";
            

   /**
    * Constructs the LSIFRollOverRequest object.
    * 
    */
   LSIFRollOverRequest()
   {
      super ( 296 );
   }

   /**
    * Constructs the LSIFRollOverRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   LSIFRollOverRequest( String hostEncoding )
   {
      super ( 296, hostEncoding );
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
    * Sets the From Fund field for the request.
    * 
    * @param value  Value that the From Fund will be set to.
    */
   public final void setFromFund( String value )
   {
      assertUnsent();
      _FromFund = value;
   }
	
   /**
    * Sets the From Class field for the request.
    * 
    * @param value  Value that the From Class will be set to.
    */
   public final void setFromClass( String value )
   {
      assertUnsent();
      _FromClass = value;
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
      requestBuffer.appendField( _FromFund );
      requestBuffer.appendField( _FromClass );
   }

}

