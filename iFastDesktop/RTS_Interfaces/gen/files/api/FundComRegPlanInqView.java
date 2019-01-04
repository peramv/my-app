
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * FUNDCom REG Plan Contrib Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/FundComRegPlanInq.doc">FundComRegPlanInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class FundComRegPlanInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Tax Year member array.
    */
   private Integer[] _TaxYear = null;
   
   /**
    * First 60 Amount member array.
    */
   private String[] _First60Amt = null;
   
   /**
    * Rest Year Amount member array.
    */
   private String[] _RestYearAmt = null;
   
   /**
    * Total Amount member array.
    */
   private String[] _TotalAmt = null;
   

   /**
    * Constructs the FundComRegPlanInqView object.
    * 
    */
   public FundComRegPlanInqView()
   {
      super ( new FundComRegPlanInqRequest() );
   }

   /**
    * Constructs the FundComRegPlanInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public FundComRegPlanInqView( String hostEncoding )
   {
      super ( new FundComRegPlanInqRequest( hostEncoding ) );
   }

   /**
    * Gets the FundComRegPlanInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The FundComRegPlanInqRequest object.
    */
   public final FundComRegPlanInqRequest getRequest()
   {
      return (FundComRegPlanInqRequest)getIFastRequest();
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
    * Gets the Tax Year field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax Year or null.
    */
   public final Integer getTaxYear( int index )
   {
      return _TaxYear[index];
   }
    
   /**
    * Gets the Tax Year field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Year or the specified default value.
    */
   public final int getTaxYear( int index, int defaultValue )
   {
      return _TaxYear[index] == null ? defaultValue : _TaxYear[index].intValue();
   }
    
   /**
    * Gets the array of Tax Year fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax Year values.
    */
   public final Integer[] getTaxYearArray()
   {
      return _TaxYear;
   }
    
   /**
    * Gets the First 60 Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the First 60 Amount or null.
    */
   public final String getFirst60Amt( int index )
   {
      return _First60Amt[index];
   }
    
   /**
    * Gets the First 60 Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the First 60 Amount or the specified default value.
    */
   public final String getFirst60Amt( int index, String defaultValue )
   {
      return _First60Amt[index] == null ? defaultValue : _First60Amt[index];
   }
    
   /**
    * Gets the array of First 60 Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of First 60 Amount values.
    */
   public final String[] getFirst60AmtArray()
   {
      return _First60Amt;
   }
    
   /**
    * Gets the Rest Year Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Rest Year Amount or null.
    */
   public final String getRestYearAmt( int index )
   {
      return _RestYearAmt[index];
   }
    
   /**
    * Gets the Rest Year Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Rest Year Amount or the specified default value.
    */
   public final String getRestYearAmt( int index, String defaultValue )
   {
      return _RestYearAmt[index] == null ? defaultValue : _RestYearAmt[index];
   }
    
   /**
    * Gets the array of Rest Year Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Rest Year Amount values.
    */
   public final String[] getRestYearAmtArray()
   {
      return _RestYearAmt;
   }
    
   /**
    * Gets the Total Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Total Amount or null.
    */
   public final String getTotalAmt( int index )
   {
      return _TotalAmt[index];
   }
    
   /**
    * Gets the Total Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Total Amount or the specified default value.
    */
   public final String getTotalAmt( int index, String defaultValue )
   {
      return _TotalAmt[index] == null ? defaultValue : _TotalAmt[index];
   }
    
   /**
    * Gets the array of Total Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Total Amount values.
    */
   public final String[] getTotalAmtArray()
   {
      return _TotalAmt;
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
      
      _TaxYear = resizeArray( _TaxYear, _RepeatCount );
      _First60Amt = resizeArray( _First60Amt, _RepeatCount );
      _RestYearAmt = resizeArray( _RestYearAmt, _RepeatCount );
      _TotalAmt = resizeArray( _TotalAmt, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _TaxYear[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _First60Amt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RestYearAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TotalAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
