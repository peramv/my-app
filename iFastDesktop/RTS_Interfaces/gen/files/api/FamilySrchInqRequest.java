// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Family Code Search request.
 * For additional view information see <A HREF="../../../../viewspecs/FamilySrchInq.doc">FamilySrchInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class FamilySrchInqRequest extends IFastRequest implements Serializable
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
    * LanguageCode member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * Company Id member variable.
    */
   private String _CompanyId = "";
            
            
            
            
            
   /**
    * Family Code member variable.
    */
   private String _FamilyCode = "";
            
   /**
    * Familt Name member variable.
    */
   private String _FamilyName = "";
            
   /**
    * Exact Match flag member variable.
    */
   private Boolean _ExactMatch = new Boolean(false);
            

   /**
    * Constructs the FamilySrchInqRequest object.
    * 
    */
   FamilySrchInqRequest()
   {
      super ( 235 );
   }

   /**
    * Constructs the FamilySrchInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   FamilySrchInqRequest( String hostEncoding )
   {
      super ( 235, hostEncoding );
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
    * Sets the Family Code field for the request.
    * 
    * @param value  Value that the Family Code will be set to.
    */
   public final void setFamilyCode( String value )
   {
      assertUnsent();
      _FamilyCode = value;
   }
	
   /**
    * Sets the Familt Name field for the request.
    * 
    * @param value  Value that the Familt Name will be set to.
    */
   public final void setFamilyName( String value )
   {
      assertUnsent();
      _FamilyName = value;
   }
	
   /**
    * Sets the Exact Match flag field for the request.
    * 
    * @param value  Value that the Exact Match flag will be set to.
    */
   public final void setExactMatch( Boolean value )
   {
      assertUnsent();
      _ExactMatch = value;
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
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _FamilyCode );
      requestBuffer.appendField( _FamilyName );
      requestBuffer.appendField( _ExactMatch );
   }

}

