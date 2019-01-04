// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Account Authorization Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/AcctAuthInq.doc">AcctAuthInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class AcctAuthInqRequest extends IFastRequest implements Serializable
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
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Effective Date member variable.
    */
   private Date _Deff = null;
            
   /**
    * Stop Date member variable.
    */
   private Date _StopDate = null;
            
   /**
    * Acct-Auth RID member variable.
    */
   private Integer _AcctAuthRID = null;
            
   /**
    * DuplicateCheck member variable.
    */
   private Boolean _DuplicateCheck = new Boolean(false);
            

   /**
    * Constructs the AcctAuthInqRequest object.
    * 
    */
   AcctAuthInqRequest()
   {
      super ( 395 );
   }

   /**
    * Constructs the AcctAuthInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AcctAuthInqRequest( String hostEncoding )
   {
      super ( 395, hostEncoding );
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
    * Sets the Effective Date field for the request.
    * 
    * @param value  Value that the Effective Date will be set to.
    */
   public final void setDeff( Date value )
   {
      assertUnsent();
      _Deff = value;
   }
	
   /**
    * Sets the Stop Date field for the request.
    * 
    * @param value  Value that the Stop Date will be set to.
    */
   public final void setStopDate( Date value )
   {
      assertUnsent();
      _StopDate = value;
   }
	
   /**
    * Sets the Acct-Auth RID field for the request.
    * 
    * @param value  Value that the Acct-Auth RID will be set to.
    */
   public final void setAcctAuthRID( Integer value )
   {
      assertUnsent();
      _AcctAuthRID = value;
   }
	
   /**
    * Sets the DuplicateCheck field for the request.
    * 
    * @param value  Value that the DuplicateCheck will be set to.
    */
   public final void setDuplicateCheck( Boolean value )
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
      requestBuffer.appendField( _SessionId );
      requestBuffer.appendField( _User_Id );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyId );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _Deff );
      requestBuffer.appendField( _StopDate );
      requestBuffer.appendField( _AcctAuthRID );
      requestBuffer.appendField( _DuplicateCheck );
   }

}

