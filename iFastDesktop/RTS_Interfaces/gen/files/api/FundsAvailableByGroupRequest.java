// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Funds available by Group request.
 * For additional view information see <A HREF="../../../../viewspecs/FundsAvailableByGroup.doc">FundsAvailableByGroup.doc</A>.
 * 
 * @author RTS Generated
 */
public class FundsAvailableByGroupRequest extends IFastRequest implements Serializable
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
    * Group Code member variable.
    */
   private String _GroupCode = "";
            
   /**
    * rxFundCode member variable.
    */
   private String _rxFundCode = "";
            
   /**
    * rxClassCode member variable.
    */
   private String _rxClassCode = "";
            
   /**
    * rxProdPortfolioUUID member variable.
    */
   private String _rxProdPortfolioUUID = "";
            

   /**
    * Constructs the FundsAvailableByGroupRequest object.
    * 
    */
   FundsAvailableByGroupRequest()
   {
      super ( 98 );
   }

   /**
    * Constructs the FundsAvailableByGroupRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   FundsAvailableByGroupRequest( String hostEncoding )
   {
      super ( 98, hostEncoding );
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
    * Sets the Group Code field for the request.
    * 
    * @param value  Value that the Group Code will be set to.
    */
   public final void setGroupCode( String value )
   {
      assertUnsent();
      _GroupCode = value;
   }
	
   /**
    * Sets the rxFundCode field for the request.
    * 
    * @param value  Value that the rxFundCode will be set to.
    */
   public final void setrxFundCode( String value )
   {
      assertUnsent();
      _rxFundCode = value;
   }
	
   /**
    * Sets the rxClassCode field for the request.
    * 
    * @param value  Value that the rxClassCode will be set to.
    */
   public final void setrxClassCode( String value )
   {
      assertUnsent();
      _rxClassCode = value;
   }
	
   /**
    * Sets the rxProdPortfolioUUID field for the request.
    * 
    * @param value  Value that the rxProdPortfolioUUID will be set to.
    */
   public final void setrxProdPortfolioUUID( String value )
   {
      assertUnsent();
      _rxProdPortfolioUUID = value;
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
      requestBuffer.appendField( _GroupCode );
      requestBuffer.appendField( _rxFundCode );
      requestBuffer.appendField( _rxClassCode );
      requestBuffer.appendField( _rxProdPortfolioUUID );
   }

}

