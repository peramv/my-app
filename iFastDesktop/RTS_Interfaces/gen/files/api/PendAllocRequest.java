// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Pending Trade Allocation request.
 * For additional view information see <A HREF="../../../../viewspecs/PendAlloc.doc">PendAlloc.doc</A>.
 * 
 * @author RTS Generated
 */
public class PendAllocRequest extends IFastRequest implements Serializable
{

   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Transaction Number member variable.
    */
   private Integer _TransNum = null;
            
   /**
    * Effective Date member variable.
    */
   private Date _TradeDate = null;
            
   /**
    * Session ID member variable.
    */
   private String _SessionId = "";
            
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
   private String _CompanyId = "";
            
            
            
   /**
    * RecordType member variable.
    */
   private String _RecordType = "";
            

   /**
    * Constructs the PendAllocRequest object.
    * 
    */
   PendAllocRequest()
   {
      super ( 60 );
   }

   /**
    * Constructs the PendAllocRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   PendAllocRequest( String hostEncoding )
   {
      super ( 60, hostEncoding );
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
    * Sets the Transaction Number field for the request.
    * 
    * @param value  Value that the Transaction Number will be set to.
    */
   public final void setTransNum( Integer value )
   {
      assertUnsent();
      _TransNum = value;
   }
	
   /**
    * Sets the Effective Date field for the request.
    * 
    * @param value  Value that the Effective Date will be set to.
    */
   public final void setTradeDate( Date value )
   {
      assertUnsent();
      _TradeDate = value;
   }
	
   /**
    * Sets the Session ID field for the request.
    * 
    * @param value  Value that the Session ID will be set to.
    */
   public final void setSessionId( String value )
   {
      assertUnsent();
      _SessionId = value;
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
   public final void setCompanyId( String value )
   {
      assertUnsent();
      _CompanyId = value;
   }
	
   /**
    * Sets the RecordType field for the request.
    * 
    * @param value  Value that the RecordType will be set to.
    */
   public final void setRecordType( String value )
   {
      assertUnsent();
      _RecordType = value;
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
      requestBuffer.appendField( _TransNum );
      requestBuffer.appendField( _TradeDate );
      requestBuffer.appendField( _SessionId );
      requestBuffer.appendField( _User_Id );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyId );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _RecordType );
   }

}

