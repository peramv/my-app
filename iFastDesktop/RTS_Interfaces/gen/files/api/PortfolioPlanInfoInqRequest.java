// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Portfolio Plan Information Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/PortfolioPlanInfoInq.doc">PortfolioPlanInfoInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class PortfolioPlanInfoInqRequest extends IFastRequest implements Serializable
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
    * ProdPortfolio UUID member variable.
    */
   private String _ProdPortfolioUUID = "";
            

   /**
    * Constructs the PortfolioPlanInfoInqRequest object.
    * 
    */
   PortfolioPlanInfoInqRequest()
   {
      super ( 419 );
   }

   /**
    * Constructs the PortfolioPlanInfoInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   PortfolioPlanInfoInqRequest( String hostEncoding )
   {
      super ( 419, hostEncoding );
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
    * Sets the ProdPortfolio UUID field for the request.
    * 
    * @param value  Value that the ProdPortfolio UUID will be set to.
    */
   public final void setProdPortfolioUUID( String value )
   {
      assertUnsent();
      _ProdPortfolioUUID = value;
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
      requestBuffer.appendField( _ProdPortfolioUUID );
   }

}

