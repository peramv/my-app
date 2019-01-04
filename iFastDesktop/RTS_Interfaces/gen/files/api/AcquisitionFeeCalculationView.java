
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Acquisition Fee Calculation Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/AcquisitionFeeCalculation.doc">AcquisitionFeeCalculation.doc</A>.
 * 
 * @author RTS Generated
 */
public class AcquisitionFeeCalculationView extends IFastView implements Serializable
{

   /**
    * Default aquisition fee member variable.
    */
   private String _AcqFee = null;
   
   /**
    * Default aquisition fee type member variable.
    */
   private String _AcqFeeType = null;
   
   /**
    * Maximum fee active member variable.
    */
   private Boolean _MaxFeeActive = null;
   
   /**
    * Maximum aquisition fee member variable.
    */
   private String _MaxFee = null;
   
   /**
    * Maximum aquisition fee type member variable.
    */
   private String _MaxFeeType = null;
   
   /**
    * Maximum percent (may be calculated) member variable.
    */
   private String _MaxPercent = null;
   
   /**
    * Maximum flat fee in fund currency member variable.
    */
   private String _MaxFlatFundCurr = null;
   
   /**
    * Minimum Fee member variable.
    */
   private String _MinFee = null;
   
   /**
    * Minimum Fee Percent member variable.
    */
   private String _MinPercent = null;
   

   /**
    * Constructs the AcquisitionFeeCalculationView object.
    * 
    */
   public AcquisitionFeeCalculationView()
   {
      super ( new AcquisitionFeeCalculationRequest() );
   }

   /**
    * Constructs the AcquisitionFeeCalculationView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AcquisitionFeeCalculationView( String hostEncoding )
   {
      super ( new AcquisitionFeeCalculationRequest( hostEncoding ) );
   }

   /**
    * Gets the AcquisitionFeeCalculationRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AcquisitionFeeCalculationRequest object.
    */
   public final AcquisitionFeeCalculationRequest getRequest()
   {
      return (AcquisitionFeeCalculationRequest)getIFastRequest();
   }
        
   /**
    * Gets the Default aquisition fee field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Default aquisition fee or null.
    */
   public final String getAcqFee()
   {
      return _AcqFee;
   }
	
   /**
    * Gets the Default aquisition fee field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Default aquisition fee or the specified default value.
    */
   public final String getAcqFee( String defaultValue )
   {
      return _AcqFee == null ? defaultValue : _AcqFee;
   }
                  
   /**
    * Gets the Default aquisition fee type field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Default aquisition fee type or null.
    */
   public final String getAcqFeeType()
   {
      return _AcqFeeType;
   }
	
   /**
    * Gets the Default aquisition fee type field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Default aquisition fee type or the specified default value.
    */
   public final String getAcqFeeType( String defaultValue )
   {
      return _AcqFeeType == null ? defaultValue : _AcqFeeType;
   }
                  
   /**
    * Gets the Maximum fee active field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Maximum fee active or null.
    */
   public final Boolean getMaxFeeActive()
   {
      return _MaxFeeActive;
   }
	
   /**
    * Gets the Maximum fee active field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Maximum fee active or the specified default value.
    */
   public final boolean getMaxFeeActive( boolean defaultValue )
   {
      return _MaxFeeActive == null ? defaultValue : _MaxFeeActive.booleanValue();
   }
                  
   /**
    * Gets the Maximum aquisition fee field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Maximum aquisition fee or null.
    */
   public final String getMaxFee()
   {
      return _MaxFee;
   }
	
   /**
    * Gets the Maximum aquisition fee field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Maximum aquisition fee or the specified default value.
    */
   public final String getMaxFee( String defaultValue )
   {
      return _MaxFee == null ? defaultValue : _MaxFee;
   }
                  
   /**
    * Gets the Maximum aquisition fee type field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Maximum aquisition fee type or null.
    */
   public final String getMaxFeeType()
   {
      return _MaxFeeType;
   }
	
   /**
    * Gets the Maximum aquisition fee type field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Maximum aquisition fee type or the specified default value.
    */
   public final String getMaxFeeType( String defaultValue )
   {
      return _MaxFeeType == null ? defaultValue : _MaxFeeType;
   }
                  
   /**
    * Gets the Maximum percent (may be calculated) field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Maximum percent (may be calculated) or null.
    */
   public final String getMaxPercent()
   {
      return _MaxPercent;
   }
	
   /**
    * Gets the Maximum percent (may be calculated) field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Maximum percent (may be calculated) or the specified default value.
    */
   public final String getMaxPercent( String defaultValue )
   {
      return _MaxPercent == null ? defaultValue : _MaxPercent;
   }
                  
   /**
    * Gets the Maximum flat fee in fund currency field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Maximum flat fee in fund currency or null.
    */
   public final String getMaxFlatFundCurr()
   {
      return _MaxFlatFundCurr;
   }
	
   /**
    * Gets the Maximum flat fee in fund currency field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Maximum flat fee in fund currency or the specified default value.
    */
   public final String getMaxFlatFundCurr( String defaultValue )
   {
      return _MaxFlatFundCurr == null ? defaultValue : _MaxFlatFundCurr;
   }
                  
   /**
    * Gets the Minimum Fee field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Minimum Fee or null.
    */
   public final String getMinFee()
   {
      return _MinFee;
   }
	
   /**
    * Gets the Minimum Fee field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Minimum Fee or the specified default value.
    */
   public final String getMinFee( String defaultValue )
   {
      return _MinFee == null ? defaultValue : _MinFee;
   }
                  
   /**
    * Gets the Minimum Fee Percent field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Minimum Fee Percent or null.
    */
   public final String getMinPercent()
   {
      return _MinPercent;
   }
	
   /**
    * Gets the Minimum Fee Percent field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Minimum Fee Percent or the specified default value.
    */
   public final String getMinPercent( String defaultValue )
   {
      return _MinPercent == null ? defaultValue : _MinPercent;
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
      _AcqFee = responseBuffer.decodeString(responseBuffer.getNextField());
      _AcqFeeType = responseBuffer.decodeString(responseBuffer.getNextField());
      _MaxFeeActive = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _MaxFee = responseBuffer.decodeString(responseBuffer.getNextField());
      _MaxFeeType = responseBuffer.decodeString(responseBuffer.getNextField());
      _MaxPercent = responseBuffer.decodeString(responseBuffer.getNextField());
      _MaxFlatFundCurr = responseBuffer.decodeString(responseBuffer.getNextField());
      _MinFee = responseBuffer.decodeString(responseBuffer.getNextField());
      _MinPercent = responseBuffer.decodeString(responseBuffer.getNextField());
                  

   }

}
      
