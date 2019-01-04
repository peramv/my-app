// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Shr  Fund Broker  Default Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/ShrFundBrkInq.doc">ShrFundBrkInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class ShrFundBrkInqRequest extends IFastRequest implements Serializable
{

   /**
    * Session ID member variable.
    */
   private String _SessionID = "";
            
   /**
    * User ID member variable.
    */
   private String _User_Id = "";
            
   /**
    * Language Code member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * Company ID member variable.
    */
   private String _CompanyID = "";
            
            
            
            
            
   /**
    * Shareholder Number member variable.
    */
   private String _ShrNum = "0";
            
   /**
    * Fund Broker member variable.
    */
   private String _FundBroker = "";
            
   /**
    * FundCode member variable.
    */
   private String _FundCode = "";
            
   /**
    * DuplicateCheck member variable.
    */
   private String _DuplicateCheck = "";
            

   /**
    * Constructs the ShrFundBrkInqRequest object.
    * 
    */
   ShrFundBrkInqRequest()
   {
      super ( 327 );
   }

   /**
    * Constructs the ShrFundBrkInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   ShrFundBrkInqRequest( String hostEncoding )
   {
      super ( 327, hostEncoding );
   }

   /**
    * Sets the Session ID field for the request.
    * 
    * @param value  Value that the Session ID will be set to.
    */
   public final void setSessionID( String value )
   {
      assertUnsent();
      _SessionID = value;
   }
	
   /**
    * Sets the User ID field for the request.
    * 
    * @param value  Value that the User ID will be set to.
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
    * Sets the Company ID field for the request.
    * 
    * @param value  Value that the Company ID will be set to.
    */
   public final void setCompanyID( String value )
   {
      assertUnsent();
      _CompanyID = value;
   }
	
   /**
    * Sets the Shareholder Number field for the request.
    * 
    * @param value  Value that the Shareholder Number will be set to.
    */
   public final void setShrNum( String value )
   {
      assertUnsent();
      _ShrNum = value;
   }
	
   /**
    * Sets the Fund Broker field for the request.
    * 
    * @param value  Value that the Fund Broker will be set to.
    */
   public final void setFundBroker( String value )
   {
      assertUnsent();
      _FundBroker = value;
   }
	
   /**
    * Sets the FundCode field for the request.
    * 
    * @param value  Value that the FundCode will be set to.
    */
   public final void setFundCode( String value )
   {
      assertUnsent();
      _FundCode = value;
   }
	
   /**
    * Sets the DuplicateCheck field for the request.
    * 
    * @param value  Value that the DuplicateCheck will be set to.
    */
   public final void setDuplicateCheck( String value )
   {
      assertUnsent();
      _DuplicateCheck = value;
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
      requestBuffer.appendField( _CompanyID );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      encodeOverrideRepeatsField( requestBuffer );
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _ShrNum );
      requestBuffer.appendField( _FundBroker );
      requestBuffer.appendField( _FundCode );
      requestBuffer.appendField( _DuplicateCheck );
   }

}

