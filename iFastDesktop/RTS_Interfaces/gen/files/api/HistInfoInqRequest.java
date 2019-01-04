// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Historical Info - Inq request.
 * For additional view information see <A HREF="../../../../viewspecs/HistInfoInq.doc">HistInfoInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class HistInfoInqRequest extends IFastRequest implements Serializable
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
    * Audit Type member variable.
    */
   private String _AuditType = "";
            
   /**
    * record id member variable.
    */
   private Integer _AuditRecId = null;
            
            
   /**
    * Record count member variable.
    */
   private int _ReqRepeatCount = 0;
   
   /**
    * Key String member array.
    */
   private String[] _KeyString = new String[25];
            

   /**
    * Constructs the HistInfoInqRequest object.
    * 
    */
   HistInfoInqRequest()
   {
      super ( 249 );
   }

   /**
    * Constructs the HistInfoInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   HistInfoInqRequest( String hostEncoding )
   {
      super ( 249, hostEncoding );
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
    * Sets the Audit Type field for the request.
    * 
    * @param value  Value that the Audit Type will be set to.
    */
   public final void setAuditType( String value )
   {
      assertUnsent();
      _AuditType = value;
   }
	
   /**
    * Sets the record id field for the request.
    * 
    * @param value  Value that the record id will be set to.
    */
   public final void setAuditRecId( Integer value )
   {
      assertUnsent();
      _AuditRecId = value;
   }
	
   /**
    * Sets the Record Count for the repeatable request.
    * 
    * @param value    Value that the Record Count will be set to.
    */
   public final void setReqRepeatCount( int value )
   {
      _ReqRepeatCount = value;
   }
         
   /**
    * Sets the Key String field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Key String will be set to.
    */
   public final void setKeyString( int index, String value )
   {
      assertUnsent();
      _KeyString[index] = value;
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
      encodeOverrideRepeatsField( requestBuffer );
      requestBuffer.appendField( _AuditType );
      requestBuffer.appendField( _AuditRecId );
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( new Integer(_ReqRepeatCount) );  // add record count
      for ( int x = 0; x < _ReqRepeatCount; x++ )
      {
         requestBuffer.appendField( _KeyString[x] );
      }
   }

}

