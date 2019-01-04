// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * User Access Security request.
 * For additional view information see <A HREF="../../../../viewspecs/UserAccessSecurity.doc">UserAccessSecurity.doc</A>.
 * 
 * @author RTS Generated
 */
public class UserAccessSecurityRequest extends IFastRequest implements Serializable
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
    * User Type member variable.
    */
   private String _UserType = "";
            
   /**
    * Record count member variable.
    */
   private int _ReqRepeatCount = 0;
   
   /**
    * Function Id member array.
    */
   private Integer[] _ReqFuncId = new Integer[100];
            

   /**
    * Constructs the UserAccessSecurityRequest object.
    * 
    */
   UserAccessSecurityRequest()
   {
      super ( 64 );
   }

   /**
    * Constructs the UserAccessSecurityRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   UserAccessSecurityRequest( String hostEncoding )
   {
      super ( 64, hostEncoding );
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
    * Sets the User Type field for the request.
    * 
    * @param value  Value that the User Type will be set to.
    */
   public final void setUserType( String value )
   {
      assertUnsent();
      _UserType = value;
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
    * Sets the Function Id field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Function Id will be set to.
    */
   public final void setReqFuncId( int index, Integer value )
   {
      assertUnsent();
      _ReqFuncId[index] = value;
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
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _UserType );
      requestBuffer.appendField( new Integer(_ReqRepeatCount) );  // add record count
      for ( int x = 0; x < _ReqRepeatCount; x++ )
      {
         requestBuffer.appendField( _ReqFuncId[x] );
      }
   }

}

