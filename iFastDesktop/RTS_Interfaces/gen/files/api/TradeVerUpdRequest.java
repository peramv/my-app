// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Trade verification Update request.
 * For additional view information see <A HREF="../../../../viewspecs/TradeVerUpd.doc">TradeVerUpd.doc</A>.
 * 
 * @author RTS Generated
 */
public class TradeVerUpdRequest extends IFastRequest implements Serializable
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
    * RTransnumber member variable.
    */
   private Integer _RTransnumber = null;
            
   /**
    * ActionType member variable.
    */
   private String _ActionType = "";
            
   /**
    * Last TransNumber member variable.
    */
   private Integer _LastTransNumber = null;
            

   /**
    * Constructs the TradeVerUpdRequest object.
    * 
    */
   TradeVerUpdRequest()
   {
      super ( 463 );
   }

   /**
    * Constructs the TradeVerUpdRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   TradeVerUpdRequest( String hostEncoding )
   {
      super ( 463, hostEncoding );
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
    * Sets the RTransnumber field for the request.
    * 
    * @param value  Value that the RTransnumber will be set to.
    */
   public final void setRTransnumber( Integer value )
   {
      assertUnsent();
      _RTransnumber = value;
   }
	
   /**
    * Sets the ActionType field for the request.
    * 
    * @param value  Value that the ActionType will be set to.
    */
   public final void setActionType( String value )
   {
      assertUnsent();
      _ActionType = value;
   }
	
   /**
    * Sets the Last TransNumber field for the request.
    * 
    * @param value  Value that the Last TransNumber will be set to.
    */
   public final void setLastTransNumber( Integer value )
   {
      assertUnsent();
      _LastTransNumber = value;
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
      requestBuffer.appendField( _RTransnumber );
      requestBuffer.appendField( _ActionType );
      requestBuffer.appendField( _LastTransNumber );
   }

}

