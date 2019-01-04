// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * AFB Order Header Status Update request.
 * For additional view information see <A HREF="../../../../viewspecs/AFBHeaderStatUpd.doc">AFBHeaderStatUpd.doc</A>.
 * 
 * @author RTS Generated
 */
public class AFBHeaderStatUpdRequest extends IFastRequest implements Serializable
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
    * NetworkID member variable.
    */
   private String _NetworkID = "";
            
   /**
    * Order File Name member variable.
    */
   private String _OrderFileName = "";
            
   /**
    * File Status member variable.
    */
   private String _FileStatus = "";
            

   /**
    * Constructs the AFBHeaderStatUpdRequest object.
    * 
    */
   AFBHeaderStatUpdRequest()
   {
      super ( 279 );
   }

   /**
    * Constructs the AFBHeaderStatUpdRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AFBHeaderStatUpdRequest( String hostEncoding )
   {
      super ( 279, hostEncoding );
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
    * Sets the NetworkID field for the request.
    * 
    * @param value  Value that the NetworkID will be set to.
    */
   public final void setNetworkID( String value )
   {
      assertUnsent();
      _NetworkID = value;
   }
	
   /**
    * Sets the Order File Name field for the request.
    * 
    * @param value  Value that the Order File Name will be set to.
    */
   public final void setOrderFileName( String value )
   {
      assertUnsent();
      _OrderFileName = value;
   }
	
   /**
    * Sets the File Status field for the request.
    * 
    * @param value  Value that the File Status will be set to.
    */
   public final void setFileStatus( String value )
   {
      assertUnsent();
      _FileStatus = value;
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
      requestBuffer.appendField( _NetworkID );
      requestBuffer.appendField( _OrderFileName );
      requestBuffer.appendField( _FileStatus );
   }

}

