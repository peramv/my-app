
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Cot Legal Age Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/CotLegalAgeInquiry.doc">CotLegalAgeInquiry.doc</A>.
 * 
 * @author RTS Generated
 */
public class CotLegalAgeInquiryView extends IFastView implements Serializable
{

   /**
    * CriticalAge1 member variable.
    */
   private Integer _CriticalAge1 = null;
   
   /**
    * CriticalAge2 member variable.
    */
   private Integer _CriticalAge2 = null;
   
   /**
    * CriticalAge3 member variable.
    */
   private Integer _CriticalAge3 = null;
   
   /**
    * BailOutAge1 member variable.
    */
   private Integer _BailOutAge1 = null;
   
   /**
    * BailOutAge2 member variable.
    */
   private Integer _BailOutAge2 = null;
   
   /**
    * BailOutAge3 member variable.
    */
   private Integer _BailOutAge3 = null;
   
   /**
    * LegalAgeCalcType member variable.
    */
   private Integer _LegalAgeCalcType = null;
   
   /**
    * LegalMaxAge member variable.
    */
   private Integer _LegalMaxAge = null;
   
   /**
    * Number of Years member variable.
    */
   private Integer _NumOfYrs = null;
   
   /**
    * Alternate Numer of Years member variable.
    */
   private Integer _AltNumOfYrs = null;
   

   /**
    * Constructs the CotLegalAgeInquiryView object.
    * 
    */
   public CotLegalAgeInquiryView()
   {
      super ( new CotLegalAgeInquiryRequest() );
   }

   /**
    * Constructs the CotLegalAgeInquiryView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public CotLegalAgeInquiryView( String hostEncoding )
   {
      super ( new CotLegalAgeInquiryRequest( hostEncoding ) );
   }

   /**
    * Gets the CotLegalAgeInquiryRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The CotLegalAgeInquiryRequest object.
    */
   public final CotLegalAgeInquiryRequest getRequest()
   {
      return (CotLegalAgeInquiryRequest)getIFastRequest();
   }
        
   /**
    * Gets the CriticalAge1 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the CriticalAge1 or null.
    */
   public final Integer getCriticalAge1()
   {
      return _CriticalAge1;
   }
	
   /**
    * Gets the CriticalAge1 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the CriticalAge1 or the specified default value.
    */
   public final int getCriticalAge1( int defaultValue )
   {
      return _CriticalAge1 == null ? defaultValue : _CriticalAge1.intValue();
   }
                  
   /**
    * Gets the CriticalAge2 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the CriticalAge2 or null.
    */
   public final Integer getCriticalAge2()
   {
      return _CriticalAge2;
   }
	
   /**
    * Gets the CriticalAge2 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the CriticalAge2 or the specified default value.
    */
   public final int getCriticalAge2( int defaultValue )
   {
      return _CriticalAge2 == null ? defaultValue : _CriticalAge2.intValue();
   }
                  
   /**
    * Gets the CriticalAge3 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the CriticalAge3 or null.
    */
   public final Integer getCriticalAge3()
   {
      return _CriticalAge3;
   }
	
   /**
    * Gets the CriticalAge3 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the CriticalAge3 or the specified default value.
    */
   public final int getCriticalAge3( int defaultValue )
   {
      return _CriticalAge3 == null ? defaultValue : _CriticalAge3.intValue();
   }
                  
   /**
    * Gets the BailOutAge1 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the BailOutAge1 or null.
    */
   public final Integer getBailOutAge1()
   {
      return _BailOutAge1;
   }
	
   /**
    * Gets the BailOutAge1 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BailOutAge1 or the specified default value.
    */
   public final int getBailOutAge1( int defaultValue )
   {
      return _BailOutAge1 == null ? defaultValue : _BailOutAge1.intValue();
   }
                  
   /**
    * Gets the BailOutAge2 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the BailOutAge2 or null.
    */
   public final Integer getBailOutAge2()
   {
      return _BailOutAge2;
   }
	
   /**
    * Gets the BailOutAge2 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BailOutAge2 or the specified default value.
    */
   public final int getBailOutAge2( int defaultValue )
   {
      return _BailOutAge2 == null ? defaultValue : _BailOutAge2.intValue();
   }
                  
   /**
    * Gets the BailOutAge3 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the BailOutAge3 or null.
    */
   public final Integer getBailOutAge3()
   {
      return _BailOutAge3;
   }
	
   /**
    * Gets the BailOutAge3 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BailOutAge3 or the specified default value.
    */
   public final int getBailOutAge3( int defaultValue )
   {
      return _BailOutAge3 == null ? defaultValue : _BailOutAge3.intValue();
   }
                  
   /**
    * Gets the LegalAgeCalcType field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the LegalAgeCalcType or null.
    */
   public final Integer getLegalAgeCalcType()
   {
      return _LegalAgeCalcType;
   }
	
   /**
    * Gets the LegalAgeCalcType field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the LegalAgeCalcType or the specified default value.
    */
   public final int getLegalAgeCalcType( int defaultValue )
   {
      return _LegalAgeCalcType == null ? defaultValue : _LegalAgeCalcType.intValue();
   }
                  
   /**
    * Gets the LegalMaxAge field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the LegalMaxAge or null.
    */
   public final Integer getLegalMaxAge()
   {
      return _LegalMaxAge;
   }
	
   /**
    * Gets the LegalMaxAge field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the LegalMaxAge or the specified default value.
    */
   public final int getLegalMaxAge( int defaultValue )
   {
      return _LegalMaxAge == null ? defaultValue : _LegalMaxAge.intValue();
   }
                  
   /**
    * Gets the Number of Years field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Number of Years or null.
    */
   public final Integer getNumOfYrs()
   {
      return _NumOfYrs;
   }
	
   /**
    * Gets the Number of Years field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Number of Years or the specified default value.
    */
   public final int getNumOfYrs( int defaultValue )
   {
      return _NumOfYrs == null ? defaultValue : _NumOfYrs.intValue();
   }
                  
   /**
    * Gets the Alternate Numer of Years field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Alternate Numer of Years or null.
    */
   public final Integer getAltNumOfYrs()
   {
      return _AltNumOfYrs;
   }
	
   /**
    * Gets the Alternate Numer of Years field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Alternate Numer of Years or the specified default value.
    */
   public final int getAltNumOfYrs( int defaultValue )
   {
      return _AltNumOfYrs == null ? defaultValue : _AltNumOfYrs.intValue();
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
      _CriticalAge1 = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _CriticalAge2 = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _CriticalAge3 = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _BailOutAge1 = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _BailOutAge2 = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _BailOutAge3 = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _LegalAgeCalcType = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _LegalMaxAge = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _NumOfYrs = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _AltNumOfYrs = responseBuffer.decodeInteger(responseBuffer.getNextField());
                  

   }

}
      
