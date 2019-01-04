// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Account Reporting FFI Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/AcctRptFFIInq.doc">AcctRptFFIInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class AcctRptFFIInqRequest extends IFastRequest implements Serializable
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
    * Comply Rule member variable.
    */
   private String _rxComplyRule = "";
            
   /**
    * Account Number member variable.
    */
   private String _Account = "0";
            
   /**
    * Account Designation member variable.
    */
   private String _AcctDesignation = "";
            
   /**
    * Broker Code member variable.
    */
   private String _AgencyCode = "";
            
   /**
    * Intermediary Code member variable.
    */
   private String _RepLevel = "";
            

   /**
    * Constructs the AcctRptFFIInqRequest object.
    * 
    */
   AcctRptFFIInqRequest()
   {
      super ( 450 );
   }

   /**
    * Constructs the AcctRptFFIInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AcctRptFFIInqRequest( String hostEncoding )
   {
      super ( 450, hostEncoding );
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
    * Sets the Comply Rule field for the request.
    * 
    * @param value  Value that the Comply Rule will be set to.
    */
   public final void setrxComplyRule( String value )
   {
      assertUnsent();
      _rxComplyRule = value;
   }
	
   /**
    * Sets the Account Number field for the request.
    * 
    * @param value  Value that the Account Number will be set to.
    */
   public final void setAccount( String value )
   {
      assertUnsent();
      _Account = value;
   }
	
   /**
    * Sets the Account Designation field for the request.
    * 
    * @param value  Value that the Account Designation will be set to.
    */
   public final void setAcctDesignation( String value )
   {
      assertUnsent();
      _AcctDesignation = value;
   }
	
   /**
    * Sets the Broker Code field for the request.
    * 
    * @param value  Value that the Broker Code will be set to.
    */
   public final void setAgencyCode( String value )
   {
      assertUnsent();
      _AgencyCode = value;
   }
	
   /**
    * Sets the Intermediary Code field for the request.
    * 
    * @param value  Value that the Intermediary Code will be set to.
    */
   public final void setRepLevel( String value )
   {
      assertUnsent();
      _RepLevel = value;
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
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _rxComplyRule );
      requestBuffer.appendField( _Account );
      requestBuffer.appendField( _AcctDesignation );
      requestBuffer.appendField( _AgencyCode );
      requestBuffer.appendField( _RepLevel );
   }

}

