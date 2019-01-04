
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Interest Paid Per Investment Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/InterestPaidPerInvestmentInquiry.doc">InterestPaidPerInvestmentInquiry.doc</A>.
 * 
 * @author RTS Generated
 */
public class InterestPaidPerInvestmentInquiryView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * IntInvestIncomeUUID member array.
    */
   private String[] _IntInvestIncomeUUID = null;
   
   /**
    * InterestDate member array.
    */
   private Date[] _InterestDate = null;
   
   /**
    * Amount member array.
    */
   private String[] _Amount = null;
   
   /**
    * InvestStatus member array.
    */
   private String[] _InvestStatus = null;
   

   /**
    * Constructs the InterestPaidPerInvestmentInquiryView object.
    * 
    */
   public InterestPaidPerInvestmentInquiryView()
   {
      super ( new InterestPaidPerInvestmentInquiryRequest() );
   }

   /**
    * Constructs the InterestPaidPerInvestmentInquiryView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public InterestPaidPerInvestmentInquiryView( String hostEncoding )
   {
      super ( new InterestPaidPerInvestmentInquiryRequest( hostEncoding ) );
   }

   /**
    * Gets the InterestPaidPerInvestmentInquiryRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The InterestPaidPerInvestmentInquiryRequest object.
    */
   public final InterestPaidPerInvestmentInquiryRequest getRequest()
   {
      return (InterestPaidPerInvestmentInquiryRequest)getIFastRequest();
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
    * Gets the IntInvestIncomeUUID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the IntInvestIncomeUUID or null.
    */
   public final String getIntInvestIncomeUUID( int index )
   {
      return _IntInvestIncomeUUID[index];
   }
    
   /**
    * Gets the IntInvestIncomeUUID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the IntInvestIncomeUUID or the specified default value.
    */
   public final String getIntInvestIncomeUUID( int index, String defaultValue )
   {
      return _IntInvestIncomeUUID[index] == null ? defaultValue : _IntInvestIncomeUUID[index];
   }
    
   /**
    * Gets the array of IntInvestIncomeUUID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of IntInvestIncomeUUID values.
    */
   public final String[] getIntInvestIncomeUUIDArray()
   {
      return _IntInvestIncomeUUID;
   }
    
   /**
    * Gets the InterestDate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the InterestDate or null.
    */
   public final Date getInterestDate( int index )
   {
      return _InterestDate[index];
   }
    
   /**
    * Gets the InterestDate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the InterestDate or the specified default value.
    */
   public final Date getInterestDate( int index, Date defaultValue )
   {
      return _InterestDate[index] == null ? defaultValue : _InterestDate[index];
   }
    
   /**
    * Gets the array of InterestDate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of InterestDate values.
    */
   public final Date[] getInterestDateArray()
   {
      return _InterestDate;
   }
    
   /**
    * Gets the Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Amount or null.
    */
   public final String getAmount( int index )
   {
      return _Amount[index];
   }
    
   /**
    * Gets the Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Amount or the specified default value.
    */
   public final String getAmount( int index, String defaultValue )
   {
      return _Amount[index] == null ? defaultValue : _Amount[index];
   }
    
   /**
    * Gets the array of Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Amount values.
    */
   public final String[] getAmountArray()
   {
      return _Amount;
   }
    
   /**
    * Gets the InvestStatus field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the InvestStatus or null.
    */
   public final String getInvestStatus( int index )
   {
      return _InvestStatus[index];
   }
    
   /**
    * Gets the InvestStatus field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the InvestStatus or the specified default value.
    */
   public final String getInvestStatus( int index, String defaultValue )
   {
      return _InvestStatus[index] == null ? defaultValue : _InvestStatus[index];
   }
    
   /**
    * Gets the array of InvestStatus fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of InvestStatus values.
    */
   public final String[] getInvestStatusArray()
   {
      return _InvestStatus;
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
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _IntInvestIncomeUUID = resizeArray( _IntInvestIncomeUUID, _RepeatCount );
      _InterestDate = resizeArray( _InterestDate, _RepeatCount );
      _Amount = resizeArray( _Amount, _RepeatCount );
      _InvestStatus = resizeArray( _InvestStatus, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _IntInvestIncomeUUID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _InterestDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _Amount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _InvestStatus[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
