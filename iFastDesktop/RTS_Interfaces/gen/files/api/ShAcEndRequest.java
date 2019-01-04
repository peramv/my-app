// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Share/Acct Bus Group Upd end pers request.
 * For additional view information see <A HREF="../../../../viewspecs/ShAcEnd.doc">ShAcEnd.doc</A>.
 * 
 * @author RTS Generated
 */
public class ShAcEndRequest extends IFastRequest implements Serializable
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
    * Commit Flag member variable.
    */
   private Boolean _CommitFlag = new Boolean(false);
            
            
            
   /**
    * AWD Business Area member variable.
    */
   private String _AWDBusinessArea = "";
            
   /**
    * AWD Work Type member variable.
    */
   private String _AWDWorkType = "";
            
   /**
    * AWD Object Key member variable.
    */
   private String _AWDObjectKey = "";
            
   /**
    * AWD Obj Date Time member variable.
    */
   private String _AWDObjDateTime = "";
            

   /**
    * Constructs the ShAcEndRequest object.
    * 
    */
   ShAcEndRequest()
   {
      super ( 74 );
   }

   /**
    * Constructs the ShAcEndRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   ShAcEndRequest( String hostEncoding )
   {
      super ( 74, hostEncoding );
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
    * Sets the Commit Flag field for the request.
    * 
    * @param value  Value that the Commit Flag will be set to.
    */
   public final void setCommitFlag( Boolean value )
   {
      assertUnsent();
      _CommitFlag = value;
   }
	
   /**
    * Sets the AWD Business Area field for the request.
    * 
    * @param value  Value that the AWD Business Area will be set to.
    */
   public final void setAWDBusinessArea( String value )
   {
      assertUnsent();
      _AWDBusinessArea = value;
   }
	
   /**
    * Sets the AWD Work Type field for the request.
    * 
    * @param value  Value that the AWD Work Type will be set to.
    */
   public final void setAWDWorkType( String value )
   {
      assertUnsent();
      _AWDWorkType = value;
   }
	
   /**
    * Sets the AWD Object Key field for the request.
    * 
    * @param value  Value that the AWD Object Key will be set to.
    */
   public final void setAWDObjectKey( String value )
   {
      assertUnsent();
      _AWDObjectKey = value;
   }
	
   /**
    * Sets the AWD Obj Date Time field for the request.
    * 
    * @param value  Value that the AWD Obj Date Time will be set to.
    */
   public final void setAWDObjDateTime( String value )
   {
      assertUnsent();
      _AWDObjDateTime = value;
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
      requestBuffer.appendField( _CommitFlag );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _AWDBusinessArea );
      requestBuffer.appendField( _AWDWorkType );
      requestBuffer.appendField( _AWDObjectKey );
      requestBuffer.appendField( _AWDObjDateTime );
   }

}

