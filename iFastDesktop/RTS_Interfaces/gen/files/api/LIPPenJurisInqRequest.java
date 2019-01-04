// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * LIP Pension Jurisdiction Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/LIPPenJurisInq.doc">LIPPenJurisInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class LIPPenJurisInqRequest extends IFastRequest implements Serializable
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
    * Tax Type member variable.
    */
   private String _TaxType = "";
            
            
   /**
    * TaxTypeSchedule member variable.
    */
   private String _rxTaxTypeSchedule = "";
            

   /**
    * Constructs the LIPPenJurisInqRequest object.
    * 
    */
   LIPPenJurisInqRequest()
   {
      super ( 211 );
   }

   /**
    * Constructs the LIPPenJurisInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   LIPPenJurisInqRequest( String hostEncoding )
   {
      super ( 211, hostEncoding );
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
    * Sets the Tax Type field for the request.
    * 
    * @param value  Value that the Tax Type will be set to.
    */
   public final void setTaxType( String value )
   {
      assertUnsent();
      _TaxType = value;
   }
	
   /**
    * Sets the TaxTypeSchedule field for the request.
    * 
    * @param value  Value that the TaxTypeSchedule will be set to.
    */
   public final void setrxTaxTypeSchedule( String value )
   {
      assertUnsent();
      _rxTaxTypeSchedule = value;
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
      requestBuffer.appendField( _TaxType );
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _rxTaxTypeSchedule );
   }

}

