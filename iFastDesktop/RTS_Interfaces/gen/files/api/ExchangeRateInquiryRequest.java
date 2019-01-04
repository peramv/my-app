// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Exchange Rate Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/ExchangeRateInquiry.doc">ExchangeRateInquiry.doc</A>.
 * 
 * @author RTS Generated
 */
public class ExchangeRateInquiryRequest extends IFastRequest implements Serializable
{

   /**
    * From Currency member variable.
    */
   private String _FromCurrency = "";
            
   /**
    * To Currency member variable.
    */
   private String _ToCurrency = "";
            
   /**
    * Effective Date member variable.
    */
   private Date _EffectiveDate = null;
            
            
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
    * Exact Date or Most Recent Date member variable.
    */
   private Boolean _ExactDate = new Boolean(false);
            

   /**
    * Constructs the ExchangeRateInquiryRequest object.
    * 
    */
   ExchangeRateInquiryRequest()
   {
      super ( 134 );
   }

   /**
    * Constructs the ExchangeRateInquiryRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   ExchangeRateInquiryRequest( String hostEncoding )
   {
      super ( 134, hostEncoding );
   }

   /**
    * Sets the From Currency field for the request.
    * 
    * @param value  Value that the From Currency will be set to.
    */
   public final void setFromCurrency( String value )
   {
      assertUnsent();
      _FromCurrency = value;
   }
	
   /**
    * Sets the To Currency field for the request.
    * 
    * @param value  Value that the To Currency will be set to.
    */
   public final void setToCurrency( String value )
   {
      assertUnsent();
      _ToCurrency = value;
   }
	
   /**
    * Sets the Effective Date field for the request.
    * 
    * @param value  Value that the Effective Date will be set to.
    */
   public final void setEffectiveDate( Date value )
   {
      assertUnsent();
      _EffectiveDate = value;
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
    * Sets the Exact Date or Most Recent Date field for the request.
    * 
    * @param value  Value that the Exact Date or Most Recent Date will be set to.
    */
   public final void setExactDate( Boolean value )
   {
      assertUnsent();
      _ExactDate = value;
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
      requestBuffer.appendField( _FromCurrency );
      requestBuffer.appendField( _ToCurrency );
      requestBuffer.appendField( _EffectiveDate );
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _SessionId );
      requestBuffer.appendField( _User_Id );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyId );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _ExactDate );
   }

}

