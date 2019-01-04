
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * GIA Fund Attributes Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/GIAFundAttributesInquiry.doc">GIAFundAttributesInquiry.doc</A>.
 * 
 * @author RTS Generated
 */
public class GIAFundAttributesInquiryView extends IFastView implements Serializable
{

   /**
    * Type of Interest Calculation member variable.
    */
   private String _IntCalcMthd = null;
   
   /**
    * List of deposit term for Simple Calcualtion member variable.
    */
   private String _SimpleTermList = null;
   
   /**
    * List of deposit term for Compound Calculation member variable.
    */
   private String _CompoundTermList = null;
   
   /**
    * List of frequency for Simple Calculation member variable.
    */
   private String _SimpleCredFreqList = null;
   
   /**
    * List of frequency for Compound Calculation member variable.
    */
   private String _CompoundCredFreqList = null;
   
   /**
    * Maturity Date member variable.
    */
   private Date _MaturityDate = null;
   
   /**
    * Next Interest Date member variable.
    */
   private Date _NextIntCredDate = null;
   
   /**
    * Commission Reduction member variable.
    */
   private String _CommRedRate = null;
   
   /**
    * Estimated Rate member variable.
    */
   private String _EstimatedRate = null;
   

   /**
    * Constructs the GIAFundAttributesInquiryView object.
    * 
    */
   public GIAFundAttributesInquiryView()
   {
      super ( new GIAFundAttributesInquiryRequest() );
   }

   /**
    * Constructs the GIAFundAttributesInquiryView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public GIAFundAttributesInquiryView( String hostEncoding )
   {
      super ( new GIAFundAttributesInquiryRequest( hostEncoding ) );
   }

   /**
    * Gets the GIAFundAttributesInquiryRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The GIAFundAttributesInquiryRequest object.
    */
   public final GIAFundAttributesInquiryRequest getRequest()
   {
      return (GIAFundAttributesInquiryRequest)getIFastRequest();
   }
        
   /**
    * Gets the Type of Interest Calculation field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Type of Interest Calculation or null.
    */
   public final String getIntCalcMthd()
   {
      return _IntCalcMthd;
   }
	
   /**
    * Gets the Type of Interest Calculation field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Type of Interest Calculation or the specified default value.
    */
   public final String getIntCalcMthd( String defaultValue )
   {
      return _IntCalcMthd == null ? defaultValue : _IntCalcMthd;
   }
                  
   /**
    * Gets the List of deposit term for Simple Calcualtion field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the List of deposit term for Simple Calcualtion or null.
    */
   public final String getSimpleTermList()
   {
      return _SimpleTermList;
   }
	
   /**
    * Gets the List of deposit term for Simple Calcualtion field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the List of deposit term for Simple Calcualtion or the specified default value.
    */
   public final String getSimpleTermList( String defaultValue )
   {
      return _SimpleTermList == null ? defaultValue : _SimpleTermList;
   }
                  
   /**
    * Gets the List of deposit term for Compound Calculation field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the List of deposit term for Compound Calculation or null.
    */
   public final String getCompoundTermList()
   {
      return _CompoundTermList;
   }
	
   /**
    * Gets the List of deposit term for Compound Calculation field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the List of deposit term for Compound Calculation or the specified default value.
    */
   public final String getCompoundTermList( String defaultValue )
   {
      return _CompoundTermList == null ? defaultValue : _CompoundTermList;
   }
                  
   /**
    * Gets the List of frequency for Simple Calculation field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the List of frequency for Simple Calculation or null.
    */
   public final String getSimpleCredFreqList()
   {
      return _SimpleCredFreqList;
   }
	
   /**
    * Gets the List of frequency for Simple Calculation field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the List of frequency for Simple Calculation or the specified default value.
    */
   public final String getSimpleCredFreqList( String defaultValue )
   {
      return _SimpleCredFreqList == null ? defaultValue : _SimpleCredFreqList;
   }
                  
   /**
    * Gets the List of frequency for Compound Calculation field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the List of frequency for Compound Calculation or null.
    */
   public final String getCompoundCredFreqList()
   {
      return _CompoundCredFreqList;
   }
	
   /**
    * Gets the List of frequency for Compound Calculation field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the List of frequency for Compound Calculation or the specified default value.
    */
   public final String getCompoundCredFreqList( String defaultValue )
   {
      return _CompoundCredFreqList == null ? defaultValue : _CompoundCredFreqList;
   }
                  
   /**
    * Gets the Maturity Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Maturity Date or null.
    */
   public final Date getMaturityDate()
   {
      return _MaturityDate;
   }
	
   /**
    * Gets the Maturity Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Maturity Date or the specified default value.
    */
   public final Date getMaturityDate( Date defaultValue )
   {
      return _MaturityDate == null ? defaultValue : _MaturityDate;
   }
                  
   /**
    * Gets the Next Interest Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Next Interest Date or null.
    */
   public final Date getNextIntCredDate()
   {
      return _NextIntCredDate;
   }
	
   /**
    * Gets the Next Interest Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Next Interest Date or the specified default value.
    */
   public final Date getNextIntCredDate( Date defaultValue )
   {
      return _NextIntCredDate == null ? defaultValue : _NextIntCredDate;
   }
                  
   /**
    * Gets the Commission Reduction field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Commission Reduction or null.
    */
   public final String getCommRedRate()
   {
      return _CommRedRate;
   }
	
   /**
    * Gets the Commission Reduction field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commission Reduction or the specified default value.
    */
   public final String getCommRedRate( String defaultValue )
   {
      return _CommRedRate == null ? defaultValue : _CommRedRate;
   }
                  
   /**
    * Gets the Estimated Rate field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Estimated Rate or null.
    */
   public final String getEstimatedRate()
   {
      return _EstimatedRate;
   }
	
   /**
    * Gets the Estimated Rate field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Estimated Rate or the specified default value.
    */
   public final String getEstimatedRate( String defaultValue )
   {
      return _EstimatedRate == null ? defaultValue : _EstimatedRate;
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
      _IntCalcMthd = responseBuffer.decodeString(responseBuffer.getNextField());
      _SimpleTermList = responseBuffer.decodeString(responseBuffer.getNextField());
      _CompoundTermList = responseBuffer.decodeString(responseBuffer.getNextField());
      _SimpleCredFreqList = responseBuffer.decodeString(responseBuffer.getNextField());
      _CompoundCredFreqList = responseBuffer.decodeString(responseBuffer.getNextField());
      _MaturityDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _NextIntCredDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _CommRedRate = responseBuffer.decodeString(responseBuffer.getNextField());
      _EstimatedRate = responseBuffer.decodeString(responseBuffer.getNextField());
                  

   }

}
      
