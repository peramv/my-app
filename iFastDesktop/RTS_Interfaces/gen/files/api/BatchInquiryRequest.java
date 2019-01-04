// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Batch Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/BatchInquiry.doc">BatchInquiry.doc</A>.
 * 
 * @author RTS Generated
 */
public class BatchInquiryRequest extends IFastRequest implements Serializable
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
    * Request Batch Name member variable.
    */
   private String _BatchName = "";
            
   /**
    * Batch Search Type member variable.
    */
   private String _BatchSrchType = "";
            
            
            

   /**
    * Constructs the BatchInquiryRequest object.
    * 
    */
   BatchInquiryRequest()
   {
      super ( 124 );
   }

   /**
    * Constructs the BatchInquiryRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   BatchInquiryRequest( String hostEncoding )
   {
      super ( 124, hostEncoding );
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
    * Sets the Request Batch Name field for the request.
    * 
    * @param value  Value that the Request Batch Name will be set to.
    */
   public final void setBatchName( String value )
   {
      assertUnsent();
      _BatchName = value;
   }
	
   /**
    * Sets the Batch Search Type field for the request.
    * 
    * @param value  Value that the Batch Search Type will be set to.
    */
   public final void setBatchSrchType( String value )
   {
      assertUnsent();
      _BatchSrchType = value;
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
      requestBuffer.appendField( _BatchName );
      requestBuffer.appendField( _BatchSrchType );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
   }

}

