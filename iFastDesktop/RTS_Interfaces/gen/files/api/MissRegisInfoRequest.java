// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Missing Registration Information - Update request.
 * For additional view information see <A HREF="../../../../viewspecs/MissRegisInfo.doc">MissRegisInfo.doc</A>.
 * 
 * @author RTS Generated
 */
public class MissRegisInfoRequest extends IFastRequest implements Serializable
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
    * Memorable Date member variable.
    */
   private Date _MemorableDate = null;
            
   /**
    * Memorable Date Relation member variable.
    */
   private String _MemorableDateReln = "";
            

   /**
    * Constructs the MissRegisInfoRequest object.
    * 
    */
   MissRegisInfoRequest()
   {
      super ( 290 );
   }

   /**
    * Constructs the MissRegisInfoRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   MissRegisInfoRequest( String hostEncoding )
   {
      super ( 290, hostEncoding );
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
    * Sets the Memorable Date field for the request.
    * 
    * @param value  Value that the Memorable Date will be set to.
    */
   public final void setMemorableDate( Date value )
   {
      assertUnsent();
      _MemorableDate = value;
   }
	
   /**
    * Sets the Memorable Date Relation field for the request.
    * 
    * @param value  Value that the Memorable Date Relation will be set to.
    */
   public final void setMemorableDateReln( String value )
   {
      assertUnsent();
      _MemorableDateReln = value;
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
      requestBuffer.appendField( _MemorableDate );
      requestBuffer.appendField( _MemorableDateReln );
   }

}

