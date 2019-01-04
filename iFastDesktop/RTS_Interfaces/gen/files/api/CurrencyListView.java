
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Currency List Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/CurrencyList.doc">CurrencyList.doc</A>.
 * 
 * @author RTS Generated
 */
public class CurrencyListView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Currency member array.
    */
   private String[] _Currency = null;
   
   /**
    * EffectiveDate member array.
    */
   private Date[] _EffectiveDate = null;
   
   /**
    * Name member array.
    */
   private String[] _Name = null;
   
   /**
    * Precision member array.
    */
   private Integer[] _Precision = null;
   
   /**
    * RoundMethod member array.
    */
   private String[] _RoundMethod = null;
   
   /**
    * Currency Type member array.
    */
   private String[] _CurrencyType = null;
   

   /**
    * Constructs the CurrencyListView object.
    * 
    */
   public CurrencyListView()
   {
      super ( new CurrencyListRequest() );
   }

   /**
    * Constructs the CurrencyListView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public CurrencyListView( String hostEncoding )
   {
      super ( new CurrencyListRequest( hostEncoding ) );
   }

   /**
    * Gets the CurrencyListRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The CurrencyListRequest object.
    */
   public final CurrencyListRequest getRequest()
   {
      return (CurrencyListRequest)getIFastRequest();
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
    * Gets the Currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Currency or null.
    */
   public final String getCurrency( int index )
   {
      return _Currency[index];
   }
    
   /**
    * Gets the Currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Currency or the specified default value.
    */
   public final String getCurrency( int index, String defaultValue )
   {
      return _Currency[index] == null ? defaultValue : _Currency[index];
   }
    
   /**
    * Gets the array of Currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Currency values.
    */
   public final String[] getCurrencyArray()
   {
      return _Currency;
   }
    
   /**
    * Gets the EffectiveDate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the EffectiveDate or null.
    */
   public final Date getEffectiveDate( int index )
   {
      return _EffectiveDate[index];
   }
    
   /**
    * Gets the EffectiveDate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the EffectiveDate or the specified default value.
    */
   public final Date getEffectiveDate( int index, Date defaultValue )
   {
      return _EffectiveDate[index] == null ? defaultValue : _EffectiveDate[index];
   }
    
   /**
    * Gets the array of EffectiveDate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of EffectiveDate values.
    */
   public final Date[] getEffectiveDateArray()
   {
      return _EffectiveDate;
   }
    
   /**
    * Gets the Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Name or null.
    */
   public final String getName( int index )
   {
      return _Name[index];
   }
    
   /**
    * Gets the Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Name or the specified default value.
    */
   public final String getName( int index, String defaultValue )
   {
      return _Name[index] == null ? defaultValue : _Name[index];
   }
    
   /**
    * Gets the array of Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Name values.
    */
   public final String[] getNameArray()
   {
      return _Name;
   }
    
   /**
    * Gets the Precision field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Precision or null.
    */
   public final Integer getPrecision( int index )
   {
      return _Precision[index];
   }
    
   /**
    * Gets the Precision field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Precision or the specified default value.
    */
   public final int getPrecision( int index, int defaultValue )
   {
      return _Precision[index] == null ? defaultValue : _Precision[index].intValue();
   }
    
   /**
    * Gets the array of Precision fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Precision values.
    */
   public final Integer[] getPrecisionArray()
   {
      return _Precision;
   }
    
   /**
    * Gets the RoundMethod field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RoundMethod or null.
    */
   public final String getRoundMethod( int index )
   {
      return _RoundMethod[index];
   }
    
   /**
    * Gets the RoundMethod field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RoundMethod or the specified default value.
    */
   public final String getRoundMethod( int index, String defaultValue )
   {
      return _RoundMethod[index] == null ? defaultValue : _RoundMethod[index];
   }
    
   /**
    * Gets the array of RoundMethod fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RoundMethod values.
    */
   public final String[] getRoundMethodArray()
   {
      return _RoundMethod;
   }
    
   /**
    * Gets the Currency Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Currency Type or null.
    */
   public final String getCurrencyType( int index )
   {
      return _CurrencyType[index];
   }
    
   /**
    * Gets the Currency Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Currency Type or the specified default value.
    */
   public final String getCurrencyType( int index, String defaultValue )
   {
      return _CurrencyType[index] == null ? defaultValue : _CurrencyType[index];
   }
    
   /**
    * Gets the array of Currency Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Currency Type values.
    */
   public final String[] getCurrencyTypeArray()
   {
      return _CurrencyType;
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
      
      _Currency = resizeArray( _Currency, _RepeatCount );
      _EffectiveDate = resizeArray( _EffectiveDate, _RepeatCount );
      _Name = resizeArray( _Name, _RepeatCount );
      _Precision = resizeArray( _Precision, _RepeatCount );
      _RoundMethod = resizeArray( _RoundMethod, _RepeatCount );
      _CurrencyType = resizeArray( _CurrencyType, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _Currency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _Name[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Precision[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _RoundMethod[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CurrencyType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
