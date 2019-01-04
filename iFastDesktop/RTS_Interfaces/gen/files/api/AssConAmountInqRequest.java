// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Assisted Contribution Amount Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/AssConAmountInq.doc">AssConAmountInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class AssConAmountInqRequest extends IFastRequest implements Serializable
{

   /**
    * Session ID member variable.
    */
   private String _SessionID = "";
            
   /**
    * User ID member variable.
    */
   private String _User_ID = "";
            
   /**
    * Language Code member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * Company ID member variable.
    */
   private String _CompanyID = "";
            
            
            
   /**
    * iFast Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Tax Year member variable.
    */
   private Integer _TaxYear = null;
            
   /**
    * RESP Beneficairy ID member variable.
    */
   private String _RESPBenefID = "0";
            

   /**
    * Constructs the AssConAmountInqRequest object.
    * 
    */
   AssConAmountInqRequest()
   {
      super ( 416 );
   }

   /**
    * Constructs the AssConAmountInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AssConAmountInqRequest( String hostEncoding )
   {
      super ( 416, hostEncoding );
   }

   /**
    * Sets the Session ID field for the request.
    * 
    * @param value  Value that the Session ID will be set to.
    */
   public final void setSessionID( String value )
   {
      assertUnsent();
      _SessionID = value;
   }
	
   /**
    * Sets the User ID field for the request.
    * 
    * @param value  Value that the User ID will be set to.
    */
   public final void setUser_ID( String value )
   {
      assertUnsent();
      _User_ID = value;
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
   public final void setCompanyID( String value )
   {
      assertUnsent();
      _CompanyID = value;
   }
	
   /**
    * Sets the iFast Account Number field for the request.
    * 
    * @param value  Value that the iFast Account Number will be set to.
    */
   public final void setAccountNum( String value )
   {
      assertUnsent();
      _AccountNum = value;
   }
	
   /**
    * Sets the Tax Year field for the request.
    * 
    * @param value  Value that the Tax Year will be set to.
    */
   public final void setTaxYear( Integer value )
   {
      assertUnsent();
      _TaxYear = value;
   }
	
   /**
    * Sets the RESP Beneficairy ID field for the request.
    * 
    * @param value  Value that the RESP Beneficairy ID will be set to.
    */
   public final void setRESPBenefID( String value )
   {
      assertUnsent();
      _RESPBenefID = value;
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
      requestBuffer.appendField( _SessionID );
      requestBuffer.appendField( _User_ID );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyID );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _TaxYear );
      requestBuffer.appendField( _RESPBenefID );
   }

}

