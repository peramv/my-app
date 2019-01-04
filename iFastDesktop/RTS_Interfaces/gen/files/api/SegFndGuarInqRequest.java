// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Seg Fund Guarantee Detail Part 1 request.
 * For additional view information see <A HREF="../../../../viewspecs/SegFndGuarInq.doc">SegFndGuarInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class SegFndGuarInqRequest extends IFastRequest implements Serializable
{

            
   /**
    * SessionId member variable.
    */
   private String _SessionId = "";
            
   /**
    * UserId member variable.
    */
   private String _User_Id = "";
            
   /**
    * LanguageCode member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * CompanyId member variable.
    */
   private String _CompanyId = "";
            
   /**
    * Seg-Guar-Mat record Id member variable.
    */
   private Integer _SegGuarMatRecId = null;
            
            
            
            

   /**
    * Constructs the SegFndGuarInqRequest object.
    * 
    */
   SegFndGuarInqRequest()
   {
      super ( 106 );
   }

   /**
    * Constructs the SegFndGuarInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   SegFndGuarInqRequest( String hostEncoding )
   {
      super ( 106, hostEncoding );
   }

   /**
    * Sets the SessionId field for the request.
    * 
    * @param value  Value that the SessionId will be set to.
    */
   public final void setSessionId( String value )
   {
      assertUnsent();
      _SessionId = value;
   }
	
   /**
    * Sets the UserId field for the request.
    * 
    * @param value  Value that the UserId will be set to.
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
    * Sets the CompanyId field for the request.
    * 
    * @param value  Value that the CompanyId will be set to.
    */
   public final void setCompanyId( String value )
   {
      assertUnsent();
      _CompanyId = value;
   }
	
   /**
    * Sets the Seg-Guar-Mat record Id field for the request.
    * 
    * @param value  Value that the Seg-Guar-Mat record Id will be set to.
    */
   public final void setSegGuarMatRecId( Integer value )
   {
      assertUnsent();
      _SegGuarMatRecId = value;
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
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _SessionId );
      requestBuffer.appendField( _User_Id );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyId );
      requestBuffer.appendField( _SegGuarMatRecId );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      encodeOverrideRepeatsField( requestBuffer );
   }

}

