// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * GIA Date Calculation Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/GIADateCalculationInquiry.doc">GIADateCalculationInquiry.doc</A>.
 * 
 * @author RTS Generated
 */
public class GIADateCalculationInquiryRequest extends IFastRequest implements Serializable
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
    * Investment Term member variable.
    */
   private Integer _InvestTerm = null;
            
   /**
    * Interest Credit Frequency member variable.
    */
   private String _IntCredFreq = "";
            
   /**
    * Trade Date member variable.
    */
   private Date _TradeDate = null;
            
   /**
    * Last Interest Date member variable.
    */
   private Date _LastIntCredDate = null;
            

   /**
    * Constructs the GIADateCalculationInquiryRequest object.
    * 
    */
   GIADateCalculationInquiryRequest()
   {
      super ( 426 );
   }

   /**
    * Constructs the GIADateCalculationInquiryRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   GIADateCalculationInquiryRequest( String hostEncoding )
   {
      super ( 426, hostEncoding );
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
    * Sets the Investment Term field for the request.
    * 
    * @param value  Value that the Investment Term will be set to.
    */
   public final void setInvestTerm( Integer value )
   {
      assertUnsent();
      _InvestTerm = value;
   }
	
   /**
    * Sets the Interest Credit Frequency field for the request.
    * 
    * @param value  Value that the Interest Credit Frequency will be set to.
    */
   public final void setIntCredFreq( String value )
   {
      assertUnsent();
      _IntCredFreq = value;
   }
	
   /**
    * Sets the Trade Date field for the request.
    * 
    * @param value  Value that the Trade Date will be set to.
    */
   public final void setTradeDate( Date value )
   {
      assertUnsent();
      _TradeDate = value;
   }
	
   /**
    * Sets the Last Interest Date field for the request.
    * 
    * @param value  Value that the Last Interest Date will be set to.
    */
   public final void setLastIntCredDate( Date value )
   {
      assertUnsent();
      _LastIntCredDate = value;
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
      requestBuffer.appendField( _InvestTerm );
      requestBuffer.appendField( _IntCredFreq );
      requestBuffer.appendField( _TradeDate );
      requestBuffer.appendField( _LastIntCredDate );
   }

}

