// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * RESP Transaction Type List request.
 * For additional view information see <A HREF="../../../../viewspecs/RESPTranTypeList.doc">RESPTranTypeList.doc</A>.
 * 
 * @author RTS Generated
 */
public class RESPTranTypeListRequest extends IFastRequest implements Serializable
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
    * Transaction ID member variable.
    */
   private String _TransID = "0";
            
   /**
    * Flag that indicates if search will be done from Historical or Pending trades member variable.
    */
   private String _HistoryPending = "";
            

   /**
    * Constructs the RESPTranTypeListRequest object.
    * 
    */
   RESPTranTypeListRequest()
   {
      super ( 410 );
   }

   /**
    * Constructs the RESPTranTypeListRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   RESPTranTypeListRequest( String hostEncoding )
   {
      super ( 410, hostEncoding );
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
    * Sets the Transaction ID field for the request.
    * 
    * @param value  Value that the Transaction ID will be set to.
    */
   public final void setTransID( String value )
   {
      assertUnsent();
      _TransID = value;
   }
	
   /**
    * Sets the Flag that indicates if search will be done from Historical or Pending trades field for the request.
    * 
    * @param value  Value that the Flag that indicates if search will be done from Historical or Pending trades will be set to.
    */
   public final void setHistoryPending( String value )
   {
      assertUnsent();
      _HistoryPending = value;
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
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _TransID );
      requestBuffer.appendField( _HistoryPending );
   }

}

