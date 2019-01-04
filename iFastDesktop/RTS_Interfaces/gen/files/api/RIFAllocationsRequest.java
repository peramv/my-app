// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * RIF Allocations Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/RIFAllocations.doc">RIFAllocations.doc</A>.
 * 
 * @author RTS Generated
 */
public class RIFAllocationsRequest extends IFastRequest implements Serializable
{

   /**
    * Account number member variable.
    */
   private String _AccountNum = "0";
            
            
   /**
    * Session Id member variable.
    */
   private String _SessionId = "";
            
   /**
    * User id member variable.
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
    * RRIF ID member variable.
    */
   private Integer _RRIFId = null;
            
            
   /**
    * Allocation Type TO/FROM member variable.
    */
   private String _RRIFAllocType = "";
            

   /**
    * Constructs the RIFAllocationsRequest object.
    * 
    */
   RIFAllocationsRequest()
   {
      super ( 68 );
   }

   /**
    * Constructs the RIFAllocationsRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   RIFAllocationsRequest( String hostEncoding )
   {
      super ( 68, hostEncoding );
   }

   /**
    * Sets the Account number field for the request.
    * 
    * @param value  Value that the Account number will be set to.
    */
   public final void setAccountNum( String value )
   {
      assertUnsent();
      _AccountNum = value;
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
    * Sets the User id field for the request.
    * 
    * @param value  Value that the User id will be set to.
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
    * Sets the RRIF ID field for the request.
    * 
    * @param value  Value that the RRIF ID will be set to.
    */
   public final void setRRIFId( Integer value )
   {
      assertUnsent();
      _RRIFId = value;
   }
	
   /**
    * Sets the Allocation Type TO/FROM field for the request.
    * 
    * @param value  Value that the Allocation Type TO/FROM will be set to.
    */
   public final void setRRIFAllocType( String value )
   {
      assertUnsent();
      _RRIFAllocType = value;
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
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _RRIFId );
      encodeOverrideRepeatsField( requestBuffer );
      requestBuffer.appendField( _RRIFAllocType );
   }

}

