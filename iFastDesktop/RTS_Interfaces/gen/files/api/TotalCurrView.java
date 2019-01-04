
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Settlement Totals by Currency view.
 * For additional view information see <A HREF="../../../../viewspecs/TotalCurr.doc">TotalCurr.doc</A>.
 * 
 * @author RTS Generated
 */
public class TotalCurrView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Currency member array.
    */
   private String[] _Currency = null;
   
   /**
    * Purchase Total member array.
    */
   private String[] _PurchaseTotal = null;
   
   /**
    * Redemption Total member array.
    */
   private String[] _RedemptTotal = null;
   
   /**
    * Net Total member array.
    */
   private String[] _NetTotal = null;
   
   /**
    * Count Total member array.
    */
   private String[] _CountTotal = null;
   
   /**
    * RedemptionTotal without StopRedSettle A/c's PW  trades member array.
    */
   private String[] _EligibleRedempTotal = null;
   
   /**
    * Net Total without StopRedSettle A/c's PW trades member array.
    */
   private String[] _EligibleNetTotal = null;
   
   /**
    * Trade Count without StopRedSettle A/c's PW trades member array.
    */
   private Integer[] _EligibleCount = null;
   
   /**
    * Exchange In  Total member array.
    */
   private String[] _ExchangeInTotal = null;
   
   /**
    * Exchange Out Total member array.
    */
   private String[] _ExchangeOutTotal = null;
   
   /**
    * Transfer In Total member array.
    */
   private String[] _TransferInTotal = null;
   
   /**
    * Transfer Out Total member array.
    */
   private String[] _TransferOutTotal = null;
   

   /**
    * Constructs the TotalCurrView object.
    * 
    */
   public TotalCurrView()
   {
      super ( new TotalCurrRequest() );
   }

   /**
    * Constructs the TotalCurrView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public TotalCurrView( String hostEncoding )
   {
      super ( new TotalCurrRequest( hostEncoding ) );
   }

   /**
    * Gets the TotalCurrRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The TotalCurrRequest object.
    */
   public final TotalCurrRequest getRequest()
   {
      return (TotalCurrRequest)getIFastRequest();
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
    * Gets the Purchase Total field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Purchase Total or null.
    */
   public final String getPurchaseTotal( int index )
   {
      return _PurchaseTotal[index];
   }
    
   /**
    * Gets the Purchase Total field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Purchase Total or the specified default value.
    */
   public final String getPurchaseTotal( int index, String defaultValue )
   {
      return _PurchaseTotal[index] == null ? defaultValue : _PurchaseTotal[index];
   }
    
   /**
    * Gets the array of Purchase Total fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Purchase Total values.
    */
   public final String[] getPurchaseTotalArray()
   {
      return _PurchaseTotal;
   }
    
   /**
    * Gets the Redemption Total field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Redemption Total or null.
    */
   public final String getRedemptTotal( int index )
   {
      return _RedemptTotal[index];
   }
    
   /**
    * Gets the Redemption Total field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Redemption Total or the specified default value.
    */
   public final String getRedemptTotal( int index, String defaultValue )
   {
      return _RedemptTotal[index] == null ? defaultValue : _RedemptTotal[index];
   }
    
   /**
    * Gets the array of Redemption Total fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Redemption Total values.
    */
   public final String[] getRedemptTotalArray()
   {
      return _RedemptTotal;
   }
    
   /**
    * Gets the Net Total field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Net Total or null.
    */
   public final String getNetTotal( int index )
   {
      return _NetTotal[index];
   }
    
   /**
    * Gets the Net Total field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Net Total or the specified default value.
    */
   public final String getNetTotal( int index, String defaultValue )
   {
      return _NetTotal[index] == null ? defaultValue : _NetTotal[index];
   }
    
   /**
    * Gets the array of Net Total fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Net Total values.
    */
   public final String[] getNetTotalArray()
   {
      return _NetTotal;
   }
    
   /**
    * Gets the Count Total field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Count Total or null.
    */
   public final String getCountTotal( int index )
   {
      return _CountTotal[index];
   }
    
   /**
    * Gets the Count Total field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Count Total or the specified default value.
    */
   public final String getCountTotal( int index, String defaultValue )
   {
      return _CountTotal[index] == null ? defaultValue : _CountTotal[index];
   }
    
   /**
    * Gets the array of Count Total fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Count Total values.
    */
   public final String[] getCountTotalArray()
   {
      return _CountTotal;
   }
    
   /**
    * Gets the RedemptionTotal without StopRedSettle A/c's PW  trades field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RedemptionTotal without StopRedSettle A/c's PW  trades or null.
    */
   public final String getEligibleRedempTotal( int index )
   {
      return _EligibleRedempTotal[index];
   }
    
   /**
    * Gets the RedemptionTotal without StopRedSettle A/c's PW  trades field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RedemptionTotal without StopRedSettle A/c's PW  trades or the specified default value.
    */
   public final String getEligibleRedempTotal( int index, String defaultValue )
   {
      return _EligibleRedempTotal[index] == null ? defaultValue : _EligibleRedempTotal[index];
   }
    
   /**
    * Gets the array of RedemptionTotal without StopRedSettle A/c's PW  trades fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RedemptionTotal without StopRedSettle A/c's PW  trades values.
    */
   public final String[] getEligibleRedempTotalArray()
   {
      return _EligibleRedempTotal;
   }
    
   /**
    * Gets the Net Total without StopRedSettle A/c's PW trades field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Net Total without StopRedSettle A/c's PW trades or null.
    */
   public final String getEligibleNetTotal( int index )
   {
      return _EligibleNetTotal[index];
   }
    
   /**
    * Gets the Net Total without StopRedSettle A/c's PW trades field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Net Total without StopRedSettle A/c's PW trades or the specified default value.
    */
   public final String getEligibleNetTotal( int index, String defaultValue )
   {
      return _EligibleNetTotal[index] == null ? defaultValue : _EligibleNetTotal[index];
   }
    
   /**
    * Gets the array of Net Total without StopRedSettle A/c's PW trades fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Net Total without StopRedSettle A/c's PW trades values.
    */
   public final String[] getEligibleNetTotalArray()
   {
      return _EligibleNetTotal;
   }
    
   /**
    * Gets the Trade Count without StopRedSettle A/c's PW trades field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Trade Count without StopRedSettle A/c's PW trades or null.
    */
   public final Integer getEligibleCount( int index )
   {
      return _EligibleCount[index];
   }
    
   /**
    * Gets the Trade Count without StopRedSettle A/c's PW trades field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Trade Count without StopRedSettle A/c's PW trades or the specified default value.
    */
   public final int getEligibleCount( int index, int defaultValue )
   {
      return _EligibleCount[index] == null ? defaultValue : _EligibleCount[index].intValue();
   }
    
   /**
    * Gets the array of Trade Count without StopRedSettle A/c's PW trades fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Trade Count without StopRedSettle A/c's PW trades values.
    */
   public final Integer[] getEligibleCountArray()
   {
      return _EligibleCount;
   }
    
   /**
    * Gets the Exchange In  Total field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Exchange In  Total or null.
    */
   public final String getExchangeInTotal( int index )
   {
      return _ExchangeInTotal[index];
   }
    
   /**
    * Gets the Exchange In  Total field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Exchange In  Total or the specified default value.
    */
   public final String getExchangeInTotal( int index, String defaultValue )
   {
      return _ExchangeInTotal[index] == null ? defaultValue : _ExchangeInTotal[index];
   }
    
   /**
    * Gets the array of Exchange In  Total fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Exchange In  Total values.
    */
   public final String[] getExchangeInTotalArray()
   {
      return _ExchangeInTotal;
   }
    
   /**
    * Gets the Exchange Out Total field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Exchange Out Total or null.
    */
   public final String getExchangeOutTotal( int index )
   {
      return _ExchangeOutTotal[index];
   }
    
   /**
    * Gets the Exchange Out Total field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Exchange Out Total or the specified default value.
    */
   public final String getExchangeOutTotal( int index, String defaultValue )
   {
      return _ExchangeOutTotal[index] == null ? defaultValue : _ExchangeOutTotal[index];
   }
    
   /**
    * Gets the array of Exchange Out Total fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Exchange Out Total values.
    */
   public final String[] getExchangeOutTotalArray()
   {
      return _ExchangeOutTotal;
   }
    
   /**
    * Gets the Transfer In Total field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transfer In Total or null.
    */
   public final String getTransferInTotal( int index )
   {
      return _TransferInTotal[index];
   }
    
   /**
    * Gets the Transfer In Total field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transfer In Total or the specified default value.
    */
   public final String getTransferInTotal( int index, String defaultValue )
   {
      return _TransferInTotal[index] == null ? defaultValue : _TransferInTotal[index];
   }
    
   /**
    * Gets the array of Transfer In Total fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transfer In Total values.
    */
   public final String[] getTransferInTotalArray()
   {
      return _TransferInTotal;
   }
    
   /**
    * Gets the Transfer Out Total field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transfer Out Total or null.
    */
   public final String getTransferOutTotal( int index )
   {
      return _TransferOutTotal[index];
   }
    
   /**
    * Gets the Transfer Out Total field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transfer Out Total or the specified default value.
    */
   public final String getTransferOutTotal( int index, String defaultValue )
   {
      return _TransferOutTotal[index] == null ? defaultValue : _TransferOutTotal[index];
   }
    
   /**
    * Gets the array of Transfer Out Total fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transfer Out Total values.
    */
   public final String[] getTransferOutTotalArray()
   {
      return _TransferOutTotal;
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
      _PurchaseTotal = resizeArray( _PurchaseTotal, _RepeatCount );
      _RedemptTotal = resizeArray( _RedemptTotal, _RepeatCount );
      _NetTotal = resizeArray( _NetTotal, _RepeatCount );
      _CountTotal = resizeArray( _CountTotal, _RepeatCount );
      _EligibleRedempTotal = resizeArray( _EligibleRedempTotal, _RepeatCount );
      _EligibleNetTotal = resizeArray( _EligibleNetTotal, _RepeatCount );
      _EligibleCount = resizeArray( _EligibleCount, _RepeatCount );
      _ExchangeInTotal = resizeArray( _ExchangeInTotal, _RepeatCount );
      _ExchangeOutTotal = resizeArray( _ExchangeOutTotal, _RepeatCount );
      _TransferInTotal = resizeArray( _TransferInTotal, _RepeatCount );
      _TransferOutTotal = resizeArray( _TransferOutTotal, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _Currency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PurchaseTotal[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RedemptTotal[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _NetTotal[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CountTotal[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EligibleRedempTotal[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EligibleNetTotal[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EligibleCount[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ExchangeInTotal[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ExchangeOutTotal[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TransferInTotal[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TransferOutTotal[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
