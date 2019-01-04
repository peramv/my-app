
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Validations for Tax Type view.
 * For additional view information see <A HREF="../../../../viewspecs/ValTaxType.doc">ValTaxType.doc</A>.
 * 
 * @author RTS Generated
 */
public class ValTaxTypeView extends IFastView implements Serializable
{

   /**
    * Flag indicating if tax jurisdiction is valid member variable.
    */
   private Boolean _TaxJurisValid = null;
   
   /**
    * Flag indicating if trade date is valid member variable.
    */
   private Boolean _TradeDateValid = null;
   

   /**
    * Constructs the ValTaxTypeView object.
    * 
    */
   public ValTaxTypeView()
   {
      super ( new ValTaxTypeRequest() );
   }

   /**
    * Constructs the ValTaxTypeView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public ValTaxTypeView( String hostEncoding )
   {
      super ( new ValTaxTypeRequest( hostEncoding ) );
   }

   /**
    * Gets the ValTaxTypeRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The ValTaxTypeRequest object.
    */
   public final ValTaxTypeRequest getRequest()
   {
      return (ValTaxTypeRequest)getIFastRequest();
   }
        
   /**
    * Gets the Flag indicating if tax jurisdiction is valid field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Flag indicating if tax jurisdiction is valid or null.
    */
   public final Boolean getTaxJurisValid()
   {
      return _TaxJurisValid;
   }
	
   /**
    * Gets the Flag indicating if tax jurisdiction is valid field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if tax jurisdiction is valid or the specified default value.
    */
   public final boolean getTaxJurisValid( boolean defaultValue )
   {
      return _TaxJurisValid == null ? defaultValue : _TaxJurisValid.booleanValue();
   }
                  
   /**
    * Gets the Flag indicating if trade date is valid field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Flag indicating if trade date is valid or null.
    */
   public final Boolean getTradeDateValid()
   {
      return _TradeDateValid;
   }
	
   /**
    * Gets the Flag indicating if trade date is valid field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if trade date is valid or the specified default value.
    */
   public final boolean getTradeDateValid( boolean defaultValue )
   {
      return _TradeDateValid == null ? defaultValue : _TradeDateValid.booleanValue();
   }
                  
   /**
    * Implements the abstract base method to decode
    * the host formatted response.
    * 
    * @param response Host formatted response object.
    * @exception ParseException
    */
   protected void decodeFields( RTSResponseDecodeBuffer responseBuffer ) throws ParseException, UnsupportedEncodingException
   {
      
      // single-record section
      _TaxJurisValid = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _TradeDateValid = responseBuffer.decodeBoolean(responseBuffer.getNextField());
                  

   }

}
      
