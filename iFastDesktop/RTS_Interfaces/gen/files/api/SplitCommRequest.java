// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Split Commissions Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/SplitComm.doc">SplitComm.doc</A>.
 * 
 * @author RTS Generated
 */
public class SplitCommRequest extends IFastRequest implements Serializable
{

   /**
    * Session ID member variable.
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
    * Transaction Number member variable.
    */
   private Integer _TransNum = null;
            
   /**
    * Transaction Sequence member variable.
    */
   private Integer _TransSeq = null;
            
   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Transaction Type member variable.
    */
   private String _TransType = "";
            
   /**
    * Transaction ID member variable.
    */
   private String _Transid = "0";
            

   /**
    * Constructs the SplitCommRequest object.
    * 
    */
   SplitCommRequest()
   {
      super ( 151 );
   }

   /**
    * Constructs the SplitCommRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   SplitCommRequest( String hostEncoding )
   {
      super ( 151, hostEncoding );
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
    * Sets the Transaction Sequence field for the request.
    * 
    * @param value  Value that the Transaction Sequence will be set to.
    */
   public final void setTransSeq( Integer value )
   {
      assertUnsent();
      _TransSeq = value;
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
    * Sets the Transaction Type field for the request.
    * 
    * @param value  Value that the Transaction Type will be set to.
    */
   public final void setTransType( String value )
   {
      assertUnsent();
      _TransType = value;
   }
	
   /**
    * Sets the Transaction ID field for the request.
    * 
    * @param value  Value that the Transaction ID will be set to.
    */
   public final void setTransid( String value )
   {
      assertUnsent();
      _Transid = value;
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
      requestBuffer.appendField( _TransNum );
      requestBuffer.appendField( _TransSeq );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _TransType );
      requestBuffer.appendField( _Transid );
   }

}

