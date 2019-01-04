
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * GIA Investment Progressive Rate List Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/GIAInvestmentProgressiveRateListInquiry.doc">GIAInvestmentProgressiveRateListInquiry.doc</A>.
 * 
 * @author RTS Generated
 */
public class GIAInvestmentProgressiveRateListInquiryView extends IFastView implements Serializable
{

   /**
    * EstimatedRate member variable.
    */
   private String _EstimatedRate = null;
   
   private int _RepeatCount = 0;
   
   /**
    * IntInvestProgRateUUID member array.
    */
   private String[] _IntInvestProgRateUUID = null;
   
   /**
    * IntRate member array.
    */
   private String[] _IntRate = null;
   
   /**
    * InvestTerm member array.
    */
   private Integer[] _InvestTerm = null;
   

   /**
    * Constructs the GIAInvestmentProgressiveRateListInquiryView object.
    * 
    */
   public GIAInvestmentProgressiveRateListInquiryView()
   {
      super ( new GIAInvestmentProgressiveRateListInquiryRequest() );
   }

   /**
    * Constructs the GIAInvestmentProgressiveRateListInquiryView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public GIAInvestmentProgressiveRateListInquiryView( String hostEncoding )
   {
      super ( new GIAInvestmentProgressiveRateListInquiryRequest( hostEncoding ) );
   }

   /**
    * Gets the GIAInvestmentProgressiveRateListInquiryRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The GIAInvestmentProgressiveRateListInquiryRequest object.
    */
   public final GIAInvestmentProgressiveRateListInquiryRequest getRequest()
   {
      return (GIAInvestmentProgressiveRateListInquiryRequest)getIFastRequest();
   }
        
   /**
    * Gets the EstimatedRate field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the EstimatedRate or null.
    */
   public final String getEstimatedRate()
   {
      return _EstimatedRate;
   }
	
   /**
    * Gets the EstimatedRate field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the EstimatedRate or the specified default value.
    */
   public final String getEstimatedRate( String defaultValue )
   {
      return _EstimatedRate == null ? defaultValue : _EstimatedRate;
   }
                  
   /**
    * Gets the Record Count for the repeatable response.
    * 
    * @return The number of records in the repeating fields.
    */
   public int getRecordCount()
   {
      return _RepeatCount;
   }

   /**
    * Gets the Record Count for the repeatable response.
    * 
    * @return The number of records in the repeating fields.
    */
   public final int getRepeatCount()
   {
      return _RepeatCount;
   }

   /**
    * Decodes the repeat count value from the host 
    * respones.
    * 
    * @param response Host formatted response object.
    * @exception ParseException
    */
   private final void decodeRepeatCount( RTSResponseDecodeBuffer responseBuffer ) throws ParseException, UnsupportedEncodingException
   {
      int receivedRecordCount = responseBuffer.decodeInteger(responseBuffer.getNextField()).intValue();
      _RepeatCount += receivedRecordCount;
   }

   /**
    * Gets the IntInvestProgRateUUID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the IntInvestProgRateUUID or null.
    */
   public final String getIntInvestProgRateUUID( int index )
   {
      return _IntInvestProgRateUUID[index];
   }
    
   /**
    * Gets the IntInvestProgRateUUID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the IntInvestProgRateUUID or the specified default value.
    */
   public final String getIntInvestProgRateUUID( int index, String defaultValue )
   {
      return _IntInvestProgRateUUID[index] == null ? defaultValue : _IntInvestProgRateUUID[index];
   }
    
   /**
    * Gets the array of IntInvestProgRateUUID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of IntInvestProgRateUUID values.
    */
   public final String[] getIntInvestProgRateUUIDArray()
   {
      return _IntInvestProgRateUUID;
   }
    
   /**
    * Gets the IntRate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the IntRate or null.
    */
   public final String getIntRate( int index )
   {
      return _IntRate[index];
   }
    
   /**
    * Gets the IntRate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the IntRate or the specified default value.
    */
   public final String getIntRate( int index, String defaultValue )
   {
      return _IntRate[index] == null ? defaultValue : _IntRate[index];
   }
    
   /**
    * Gets the array of IntRate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of IntRate values.
    */
   public final String[] getIntRateArray()
   {
      return _IntRate;
   }
    
   /**
    * Gets the InvestTerm field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the InvestTerm or null.
    */
   public final Integer getInvestTerm( int index )
   {
      return _InvestTerm[index];
   }
    
   /**
    * Gets the InvestTerm field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the InvestTerm or the specified default value.
    */
   public final int getInvestTerm( int index, int defaultValue )
   {
      return _InvestTerm[index] == null ? defaultValue : _InvestTerm[index].intValue();
   }
    
   /**
    * Gets the array of InvestTerm fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of InvestTerm values.
    */
   public final Integer[] getInvestTermArray()
   {
      return _InvestTerm;
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
      decodeMoreAvailableField( responseBuffer );
      decodeNextKeyField( responseBuffer );
      _EstimatedRate = responseBuffer.decodeString(responseBuffer.getNextField());
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _IntInvestProgRateUUID = resizeArray( _IntInvestProgRateUUID, _RepeatCount );
      _IntRate = resizeArray( _IntRate, _RepeatCount );
      _InvestTerm = resizeArray( _InvestTerm, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _IntInvestProgRateUUID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IntRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _InvestTerm[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
      }
      

   }

}
      
