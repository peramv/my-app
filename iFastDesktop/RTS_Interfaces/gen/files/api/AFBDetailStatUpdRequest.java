// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * AFB Order Detail Status Update request.
 * For additional view information see <A HREF="../../../../viewspecs/AFBDetailStatUpd.doc">AFBDetailStatUpd.doc</A>.
 * 
 * @author RTS Generated
 */
public class AFBDetailStatUpdRequest extends IFastRequest implements Serializable
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
    * NetworkID member variable.
    */
   private String _NetworkID = "";
            
   /**
    * Order File Name member variable.
    */
   private String _OrderFileName = "";
            
   /**
    * OrderCode member variable.
    */
   private String _OrderCode = "";
            
   /**
    * Reject Code member variable.
    */
   private String _RejCode = "";
            
   /**
    * Order Status member variable.
    */
   private String _OrderStatus = "";
            
   /**
    * Reject Reason member variable.
    */
   private String _RejectReason = "";
            

   /**
    * Constructs the AFBDetailStatUpdRequest object.
    * 
    */
   AFBDetailStatUpdRequest()
   {
      super ( 280 );
   }

   /**
    * Constructs the AFBDetailStatUpdRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AFBDetailStatUpdRequest( String hostEncoding )
   {
      super ( 280, hostEncoding );
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
    * Sets the NetworkID field for the request.
    * 
    * @param value  Value that the NetworkID will be set to.
    */
   public final void setNetworkID( String value )
   {
      assertUnsent();
      _NetworkID = value;
   }
	
   /**
    * Sets the Order File Name field for the request.
    * 
    * @param value  Value that the Order File Name will be set to.
    */
   public final void setOrderFileName( String value )
   {
      assertUnsent();
      _OrderFileName = value;
   }
	
   /**
    * Sets the OrderCode field for the request.
    * 
    * @param value  Value that the OrderCode will be set to.
    */
   public final void setOrderCode( String value )
   {
      assertUnsent();
      _OrderCode = value;
   }
	
   /**
    * Sets the Reject Code field for the request.
    * 
    * @param value  Value that the Reject Code will be set to.
    */
   public final void setRejCode( String value )
   {
      assertUnsent();
      _RejCode = value;
   }
	
   /**
    * Sets the Order Status field for the request.
    * 
    * @param value  Value that the Order Status will be set to.
    */
   public final void setOrderStatus( String value )
   {
      assertUnsent();
      _OrderStatus = value;
   }
	
   /**
    * Sets the Reject Reason field for the request.
    * 
    * @param value  Value that the Reject Reason will be set to.
    */
   public final void setRejectReason( String value )
   {
      assertUnsent();
      _RejectReason = value;
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
      requestBuffer.appendField( _NetworkID );
      requestBuffer.appendField( _OrderFileName );
      requestBuffer.appendField( _OrderCode );
      requestBuffer.appendField( _RejCode );
      requestBuffer.appendField( _OrderStatus );
      requestBuffer.appendField( _RejectReason );
   }

}

