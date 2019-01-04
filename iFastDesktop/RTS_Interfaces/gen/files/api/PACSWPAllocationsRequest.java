// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Account PAC/SWP allocations request.
 * For additional view information see <A HREF="../../../../viewspecs/PACSWPAllocations.doc">PACSWPAllocations.doc</A>.
 * 
 * @author RTS Generated
 */
public class PACSWPAllocationsRequest extends IFastRequest implements Serializable
{

   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
            
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
    * Allocation Type descriptor member variable.
    */
   private String _AllocType = "";
            
            
            

   /**
    * Constructs the PACSWPAllocationsRequest object.
    * 
    */
   PACSWPAllocationsRequest()
   {
      super ( 7 );
   }

   /**
    * Constructs the PACSWPAllocationsRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   PACSWPAllocationsRequest( String hostEncoding )
   {
      super ( 7, hostEncoding );
   }

   /**
    * Sets the Account Number field for the request.
    * 
    * @param value  Value that the Account Number will be set to.
    */
   public final void setAccountNum( String value )
   {
      assertUnsent();
      _AccountNum = value;
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
    * Sets the Allocation Type descriptor field for the request.
    * 
    * @param value  Value that the Allocation Type descriptor will be set to.
    */
   public final void setAllocType( String value )
   {
      assertUnsent();
      _AllocType = value;
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
      requestBuffer.appendField( _AccountNum );
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _SessionId );
      requestBuffer.appendField( _User_Id );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyId );
      requestBuffer.appendField( _AllocType );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
   }

}

