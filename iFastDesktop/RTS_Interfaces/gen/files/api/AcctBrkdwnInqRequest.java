// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Account Breakdown Per Fund request.
 * For additional view information see <A HREF="../../../../viewspecs/AcctBrkdwnInq.doc">AcctBrkdwnInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class AcctBrkdwnInqRequest extends IFastRequest implements Serializable
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
    * ReqFund member variable.
    */
   private String _ReqFund = "";
            
   /**
    * ReqClass member variable.
    */
   private String _ReqClass = "";
            
   /**
    * AsOfDate member variable.
    */
   private Date _AsOfDate = null;
            
   /**
    * Request Fund Group member variable.
    */
   private String _ReqFundGroup = "";
            

   /**
    * Constructs the AcctBrkdwnInqRequest object.
    * 
    */
   AcctBrkdwnInqRequest()
   {
      super ( 283 );
   }

   /**
    * Constructs the AcctBrkdwnInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AcctBrkdwnInqRequest( String hostEncoding )
   {
      super ( 283, hostEncoding );
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
    * Sets the ReqFund field for the request.
    * 
    * @param value  Value that the ReqFund will be set to.
    */
   public final void setReqFund( String value )
   {
      assertUnsent();
      _ReqFund = value;
   }
	
   /**
    * Sets the ReqClass field for the request.
    * 
    * @param value  Value that the ReqClass will be set to.
    */
   public final void setReqClass( String value )
   {
      assertUnsent();
      _ReqClass = value;
   }
	
   /**
    * Sets the AsOfDate field for the request.
    * 
    * @param value  Value that the AsOfDate will be set to.
    */
   public final void setAsOfDate( Date value )
   {
      assertUnsent();
      _AsOfDate = value;
   }
	
   /**
    * Sets the Request Fund Group field for the request.
    * 
    * @param value  Value that the Request Fund Group will be set to.
    */
   public final void setReqFundGroup( String value )
   {
      assertUnsent();
      _ReqFundGroup = value;
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
      requestBuffer.appendField( _ReqFund );
      requestBuffer.appendField( _ReqClass );
      requestBuffer.appendField( _AsOfDate );
      requestBuffer.appendField( _ReqFundGroup );
   }

}

