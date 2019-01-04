
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Seg Fund Validation Inquiry - NASU view.
 * For additional view information see <A HREF="../../../../viewspecs/SegFundValidInq.doc">SegFundValidInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class SegFundValidInqView extends IFastView implements Serializable
{

   /**
    * Fund  Contract Type member variable.
    */
   private Boolean _ContractExist = null;
   
   /**
    * Indicate if Deposit is allowed member variable.
    */
   private Boolean _DepAllowed = null;
   
   /**
    * Is Legal Maturity Date valid member variable.
    */
   private Boolean _LegMatDateValid = null;
   

   /**
    * Constructs the SegFundValidInqView object.
    * 
    */
   public SegFundValidInqView()
   {
      super ( new SegFundValidInqRequest() );
   }

   /**
    * Constructs the SegFundValidInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public SegFundValidInqView( String hostEncoding )
   {
      super ( new SegFundValidInqRequest( hostEncoding ) );
   }

   /**
    * Gets the SegFundValidInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The SegFundValidInqRequest object.
    */
   public final SegFundValidInqRequest getRequest()
   {
      return (SegFundValidInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Fund  Contract Type field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Fund  Contract Type or null.
    */
   public final Boolean getContractExist()
   {
      return _ContractExist;
   }
	
   /**
    * Gets the Fund  Contract Type field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund  Contract Type or the specified default value.
    */
   public final boolean getContractExist( boolean defaultValue )
   {
      return _ContractExist == null ? defaultValue : _ContractExist.booleanValue();
   }
                  
   /**
    * Gets the Indicate if Deposit is allowed field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Indicate if Deposit is allowed or null.
    */
   public final Boolean getDepAllowed()
   {
      return _DepAllowed;
   }
	
   /**
    * Gets the Indicate if Deposit is allowed field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Indicate if Deposit is allowed or the specified default value.
    */
   public final boolean getDepAllowed( boolean defaultValue )
   {
      return _DepAllowed == null ? defaultValue : _DepAllowed.booleanValue();
   }
                  
   /**
    * Gets the Is Legal Maturity Date valid field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Is Legal Maturity Date valid or null.
    */
   public final Boolean getLegMatDateValid()
   {
      return _LegMatDateValid;
   }
	
   /**
    * Gets the Is Legal Maturity Date valid field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Is Legal Maturity Date valid or the specified default value.
    */
   public final boolean getLegMatDateValid( boolean defaultValue )
   {
      return _LegMatDateValid == null ? defaultValue : _LegMatDateValid.booleanValue();
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
      _ContractExist = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _DepAllowed = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _LegMatDateValid = responseBuffer.decodeBoolean(responseBuffer.getNextField());
                  

   }

}
      
