// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Allowable Transfers request.
 * For additional view information see <A HREF="../../../../viewspecs/AllowableTransfers.doc">AllowableTransfers.doc</A>.
 * 
 * @author RTS Generated
 */
public class AllowableTransfersRequest extends IFastRequest implements Serializable
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
    * Request Fund member variable.
    */
   private String _FromFund = "";
            
   /**
    * Request Class member variable.
    */
   private String _FromClass = "";
            
   /**
    * Fund Sponsor member variable.
    */
   private String _FundSponsor = "";
            
   /**
    * Fund To member variable.
    */
   private String _ToFund = "";
            
   /**
    * Class To member variable.
    */
   private String _ToClass = "";
            
            

   /**
    * Constructs the AllowableTransfersRequest object.
    * 
    */
   AllowableTransfersRequest()
   {
      super ( 99 );
   }

   /**
    * Constructs the AllowableTransfersRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AllowableTransfersRequest( String hostEncoding )
   {
      super ( 99, hostEncoding );
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
    * Sets the Request Fund field for the request.
    * 
    * @param value  Value that the Request Fund will be set to.
    */
   public final void setFromFund( String value )
   {
      assertUnsent();
      _FromFund = value;
   }
	
   /**
    * Sets the Request Class field for the request.
    * 
    * @param value  Value that the Request Class will be set to.
    */
   public final void setFromClass( String value )
   {
      assertUnsent();
      _FromClass = value;
   }
	
   /**
    * Sets the Fund Sponsor field for the request.
    * 
    * @param value  Value that the Fund Sponsor will be set to.
    */
   public final void setFundSponsor( String value )
   {
      assertUnsent();
      _FundSponsor = value;
   }
	
   /**
    * Sets the Fund To field for the request.
    * 
    * @param value  Value that the Fund To will be set to.
    */
   public final void setToFund( String value )
   {
      assertUnsent();
      _ToFund = value;
   }
	
   /**
    * Sets the Class To field for the request.
    * 
    * @param value  Value that the Class To will be set to.
    */
   public final void setToClass( String value )
   {
      assertUnsent();
      _ToClass = value;
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
      requestBuffer.appendField( _FromFund );
      requestBuffer.appendField( _FromClass );
      requestBuffer.appendField( _FundSponsor );
      requestBuffer.appendField( _ToFund );
      requestBuffer.appendField( _ToClass );
      encodeOverrideRepeatsField( requestBuffer );
   }

}

