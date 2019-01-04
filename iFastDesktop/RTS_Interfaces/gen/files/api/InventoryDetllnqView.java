
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Inventory Detail Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/InventoryDetllnq.doc">InventoryDetllnq.doc</A>.
 * 
 * @author RTS Generated
 */
public class InventoryDetllnqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Transid member array.
    */
   private String[] _Transid = null;
   
   /**
    * Transnumber member array.
    */
   private Integer[] _Transnum = null;
   
   /**
    * Transaction type member array.
    */
   private String[] _TransType = null;
   
   /**
    * Trade Date member array.
    */
   private Date[] _TradeDate = null;
   
   /**
    * Settlement Date member array.
    */
   private Date[] _SettleDate = null;
   
   /**
    * Units member array.
    */
   private String[] _Units = null;
   
   /**
    * Rate member array.
    */
   private String[] _Rate = null;
   

   /**
    * Constructs the InventoryDetllnqView object.
    * 
    */
   public InventoryDetllnqView()
   {
      super ( new InventoryDetllnqRequest() );
   }

   /**
    * Constructs the InventoryDetllnqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public InventoryDetllnqView( String hostEncoding )
   {
      super ( new InventoryDetllnqRequest( hostEncoding ) );
   }

   /**
    * Gets the InventoryDetllnqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The InventoryDetllnqRequest object.
    */
   public final InventoryDetllnqRequest getRequest()
   {
      return (InventoryDetllnqRequest)getIFastRequest();
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
    * Gets the Transid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transid or null.
    */
   public final String getTransid( int index )
   {
      return _Transid[index];
   }
    
   /**
    * Gets the Transid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transid or the specified default value.
    */
   public final String getTransid( int index, String defaultValue )
   {
      return _Transid[index] == null ? defaultValue : _Transid[index];
   }
    
   /**
    * Gets the array of Transid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transid values.
    */
   public final String[] getTransidArray()
   {
      return _Transid;
   }
    
   /**
    * Gets the Transnumber field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transnumber or null.
    */
   public final Integer getTransnum( int index )
   {
      return _Transnum[index];
   }
    
   /**
    * Gets the Transnumber field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transnumber or the specified default value.
    */
   public final int getTransnum( int index, int defaultValue )
   {
      return _Transnum[index] == null ? defaultValue : _Transnum[index].intValue();
   }
    
   /**
    * Gets the array of Transnumber fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transnumber values.
    */
   public final Integer[] getTransnumArray()
   {
      return _Transnum;
   }
    
   /**
    * Gets the Transaction type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transaction type or null.
    */
   public final String getTransType( int index )
   {
      return _TransType[index];
   }
    
   /**
    * Gets the Transaction type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transaction type or the specified default value.
    */
   public final String getTransType( int index, String defaultValue )
   {
      return _TransType[index] == null ? defaultValue : _TransType[index];
   }
    
   /**
    * Gets the array of Transaction type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transaction type values.
    */
   public final String[] getTransTypeArray()
   {
      return _TransType;
   }
    
   /**
    * Gets the Trade Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Trade Date or null.
    */
   public final Date getTradeDate( int index )
   {
      return _TradeDate[index];
   }
    
   /**
    * Gets the Trade Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Trade Date or the specified default value.
    */
   public final Date getTradeDate( int index, Date defaultValue )
   {
      return _TradeDate[index] == null ? defaultValue : _TradeDate[index];
   }
    
   /**
    * Gets the array of Trade Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Trade Date values.
    */
   public final Date[] getTradeDateArray()
   {
      return _TradeDate;
   }
    
   /**
    * Gets the Settlement Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Settlement Date or null.
    */
   public final Date getSettleDate( int index )
   {
      return _SettleDate[index];
   }
    
   /**
    * Gets the Settlement Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settlement Date or the specified default value.
    */
   public final Date getSettleDate( int index, Date defaultValue )
   {
      return _SettleDate[index] == null ? defaultValue : _SettleDate[index];
   }
    
   /**
    * Gets the array of Settlement Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Settlement Date values.
    */
   public final Date[] getSettleDateArray()
   {
      return _SettleDate;
   }
    
   /**
    * Gets the Units field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Units or null.
    */
   public final String getUnits( int index )
   {
      return _Units[index];
   }
    
   /**
    * Gets the Units field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Units or the specified default value.
    */
   public final String getUnits( int index, String defaultValue )
   {
      return _Units[index] == null ? defaultValue : _Units[index];
   }
    
   /**
    * Gets the array of Units fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Units values.
    */
   public final String[] getUnitsArray()
   {
      return _Units;
   }
    
   /**
    * Gets the Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Rate or null.
    */
   public final String getRate( int index )
   {
      return _Rate[index];
   }
    
   /**
    * Gets the Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Rate or the specified default value.
    */
   public final String getRate( int index, String defaultValue )
   {
      return _Rate[index] == null ? defaultValue : _Rate[index];
   }
    
   /**
    * Gets the array of Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Rate values.
    */
   public final String[] getRateArray()
   {
      return _Rate;
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
      
      _Transid = resizeArray( _Transid, _RepeatCount );
      _Transnum = resizeArray( _Transnum, _RepeatCount );
      _TransType = resizeArray( _TransType, _RepeatCount );
      _TradeDate = resizeArray( _TradeDate, _RepeatCount );
      _SettleDate = resizeArray( _SettleDate, _RepeatCount );
      _Units = resizeArray( _Units, _RepeatCount );
      _Rate = resizeArray( _Rate, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _Transid[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Transnum[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _TransType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TradeDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _SettleDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _Units[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Rate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
