
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Seg Fund Guarantee Detail Part 1 view.
 * For additional view information see <A HREF="../../../../viewspecs/SegFndGuarInq.doc">SegFndGuarInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class SegFndGuarInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Transaction ID member array.
    */
   private String[] _TransId = null;
   
   /**
    * Transaction Type member array.
    */
   private String[] _TransType = null;
   
   /**
    * Transaction Type Description member array.
    */
   private String[] _TransTypeDesc = null;
   
   /**
    * Transaction Trade Date member array.
    */
   private Date[] _TradeDate = null;
   
   /**
    * Fund Code member array.
    */
   private String[] _Fund = null;
   
   /**
    * Class Code member array.
    */
   private String[] _Class = null;
   
   /**
    * Trade Amount in Units member array.
    */
   private String[] _UnitAmount = null;
   
   /**
    * Guarantee Amount member array.
    */
   private String[] _GuarAmount = null;
   
   /**
    * Maturity Date member array.
    */
   private Date[] _MaturDate = null;
   
   /**
    * Running Guarantee Amount at Maturity member array.
    */
   private String[] _GuarAmtAtMatur = null;
   
   /**
    * Fund  Number member array.
    */
   private String[] _Baycom = null;
   
   /**
    * Set-Guar-Det record id member array.
    */
   private Integer[] _GuarRecId = null;
   
   /**
    * Seg-Guar-Mat record id member array.
    */
   private Integer[] _rxSegGuarMatRecId = null;
   

   /**
    * Constructs the SegFndGuarInqView object.
    * 
    */
   public SegFndGuarInqView()
   {
      super ( new SegFndGuarInqRequest() );
   }

   /**
    * Constructs the SegFndGuarInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public SegFndGuarInqView( String hostEncoding )
   {
      super ( new SegFndGuarInqRequest( hostEncoding ) );
   }

   /**
    * Gets the SegFndGuarInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The SegFndGuarInqRequest object.
    */
   public final SegFndGuarInqRequest getRequest()
   {
      return (SegFndGuarInqRequest)getIFastRequest();
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
    * Gets the Transaction ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transaction ID or null.
    */
   public final String getTransId( int index )
   {
      return _TransId[index];
   }
    
   /**
    * Gets the Transaction ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transaction ID or the specified default value.
    */
   public final String getTransId( int index, String defaultValue )
   {
      return _TransId[index] == null ? defaultValue : _TransId[index];
   }
    
   /**
    * Gets the array of Transaction ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transaction ID values.
    */
   public final String[] getTransIdArray()
   {
      return _TransId;
   }
    
   /**
    * Gets the Transaction Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transaction Type or null.
    */
   public final String getTransType( int index )
   {
      return _TransType[index];
   }
    
   /**
    * Gets the Transaction Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transaction Type or the specified default value.
    */
   public final String getTransType( int index, String defaultValue )
   {
      return _TransType[index] == null ? defaultValue : _TransType[index];
   }
    
   /**
    * Gets the array of Transaction Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transaction Type values.
    */
   public final String[] getTransTypeArray()
   {
      return _TransType;
   }
    
   /**
    * Gets the Transaction Type Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transaction Type Description or null.
    */
   public final String getTransTypeDesc( int index )
   {
      return _TransTypeDesc[index];
   }
    
   /**
    * Gets the Transaction Type Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transaction Type Description or the specified default value.
    */
   public final String getTransTypeDesc( int index, String defaultValue )
   {
      return _TransTypeDesc[index] == null ? defaultValue : _TransTypeDesc[index];
   }
    
   /**
    * Gets the array of Transaction Type Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transaction Type Description values.
    */
   public final String[] getTransTypeDescArray()
   {
      return _TransTypeDesc;
   }
    
   /**
    * Gets the Transaction Trade Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transaction Trade Date or null.
    */
   public final Date getTradeDate( int index )
   {
      return _TradeDate[index];
   }
    
   /**
    * Gets the Transaction Trade Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transaction Trade Date or the specified default value.
    */
   public final Date getTradeDate( int index, Date defaultValue )
   {
      return _TradeDate[index] == null ? defaultValue : _TradeDate[index];
   }
    
   /**
    * Gets the array of Transaction Trade Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transaction Trade Date values.
    */
   public final Date[] getTradeDateArray()
   {
      return _TradeDate;
   }
    
   /**
    * Gets the Fund Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Code or null.
    */
   public final String getFund( int index )
   {
      return _Fund[index];
   }
    
   /**
    * Gets the Fund Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Code or the specified default value.
    */
   public final String getFund( int index, String defaultValue )
   {
      return _Fund[index] == null ? defaultValue : _Fund[index];
   }
    
   /**
    * Gets the array of Fund Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Code values.
    */
   public final String[] getFundArray()
   {
      return _Fund;
   }
    
   /**
    * Gets the Class Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Class Code or null.
    */
   public final String getClass( int index )
   {
      return _Class[index];
   }
    
   /**
    * Gets the Class Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class Code or the specified default value.
    */
   public final String getClass( int index, String defaultValue )
   {
      return _Class[index] == null ? defaultValue : _Class[index];
   }
    
   /**
    * Gets the array of Class Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Class Code values.
    */
   public final String[] getClassArray()
   {
      return _Class;
   }
    
   /**
    * Gets the Trade Amount in Units field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Trade Amount in Units or null.
    */
   public final String getUnitAmount( int index )
   {
      return _UnitAmount[index];
   }
    
   /**
    * Gets the Trade Amount in Units field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Trade Amount in Units or the specified default value.
    */
   public final String getUnitAmount( int index, String defaultValue )
   {
      return _UnitAmount[index] == null ? defaultValue : _UnitAmount[index];
   }
    
   /**
    * Gets the array of Trade Amount in Units fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Trade Amount in Units values.
    */
   public final String[] getUnitAmountArray()
   {
      return _UnitAmount;
   }
    
   /**
    * Gets the Guarantee Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Guarantee Amount or null.
    */
   public final String getGuarAmount( int index )
   {
      return _GuarAmount[index];
   }
    
   /**
    * Gets the Guarantee Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Guarantee Amount or the specified default value.
    */
   public final String getGuarAmount( int index, String defaultValue )
   {
      return _GuarAmount[index] == null ? defaultValue : _GuarAmount[index];
   }
    
   /**
    * Gets the array of Guarantee Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Guarantee Amount values.
    */
   public final String[] getGuarAmountArray()
   {
      return _GuarAmount;
   }
    
   /**
    * Gets the Maturity Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Maturity Date or null.
    */
   public final Date getMaturDate( int index )
   {
      return _MaturDate[index];
   }
    
   /**
    * Gets the Maturity Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Maturity Date or the specified default value.
    */
   public final Date getMaturDate( int index, Date defaultValue )
   {
      return _MaturDate[index] == null ? defaultValue : _MaturDate[index];
   }
    
   /**
    * Gets the array of Maturity Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Maturity Date values.
    */
   public final Date[] getMaturDateArray()
   {
      return _MaturDate;
   }
    
   /**
    * Gets the Running Guarantee Amount at Maturity field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Running Guarantee Amount at Maturity or null.
    */
   public final String getGuarAmtAtMatur( int index )
   {
      return _GuarAmtAtMatur[index];
   }
    
   /**
    * Gets the Running Guarantee Amount at Maturity field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Running Guarantee Amount at Maturity or the specified default value.
    */
   public final String getGuarAmtAtMatur( int index, String defaultValue )
   {
      return _GuarAmtAtMatur[index] == null ? defaultValue : _GuarAmtAtMatur[index];
   }
    
   /**
    * Gets the array of Running Guarantee Amount at Maturity fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Running Guarantee Amount at Maturity values.
    */
   public final String[] getGuarAmtAtMaturArray()
   {
      return _GuarAmtAtMatur;
   }
    
   /**
    * Gets the Fund  Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund  Number or null.
    */
   public final String getBaycom( int index )
   {
      return _Baycom[index];
   }
    
   /**
    * Gets the Fund  Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund  Number or the specified default value.
    */
   public final String getBaycom( int index, String defaultValue )
   {
      return _Baycom[index] == null ? defaultValue : _Baycom[index];
   }
    
   /**
    * Gets the array of Fund  Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund  Number values.
    */
   public final String[] getBaycomArray()
   {
      return _Baycom;
   }
    
   /**
    * Gets the Set-Guar-Det record id field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Set-Guar-Det record id or null.
    */
   public final Integer getGuarRecId( int index )
   {
      return _GuarRecId[index];
   }
    
   /**
    * Gets the Set-Guar-Det record id field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Set-Guar-Det record id or the specified default value.
    */
   public final int getGuarRecId( int index, int defaultValue )
   {
      return _GuarRecId[index] == null ? defaultValue : _GuarRecId[index].intValue();
   }
    
   /**
    * Gets the array of Set-Guar-Det record id fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Set-Guar-Det record id values.
    */
   public final Integer[] getGuarRecIdArray()
   {
      return _GuarRecId;
   }
    
   /**
    * Gets the Seg-Guar-Mat record id field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Seg-Guar-Mat record id or null.
    */
   public final Integer getrxSegGuarMatRecId( int index )
   {
      return _rxSegGuarMatRecId[index];
   }
    
   /**
    * Gets the Seg-Guar-Mat record id field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Seg-Guar-Mat record id or the specified default value.
    */
   public final int getrxSegGuarMatRecId( int index, int defaultValue )
   {
      return _rxSegGuarMatRecId[index] == null ? defaultValue : _rxSegGuarMatRecId[index].intValue();
   }
    
   /**
    * Gets the array of Seg-Guar-Mat record id fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Seg-Guar-Mat record id values.
    */
   public final Integer[] getrxSegGuarMatRecIdArray()
   {
      return _rxSegGuarMatRecId;
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
      
      _TransId = resizeArray( _TransId, _RepeatCount );
      _TransType = resizeArray( _TransType, _RepeatCount );
      _TransTypeDesc = resizeArray( _TransTypeDesc, _RepeatCount );
      _TradeDate = resizeArray( _TradeDate, _RepeatCount );
      _Fund = resizeArray( _Fund, _RepeatCount );
      _Class = resizeArray( _Class, _RepeatCount );
      _UnitAmount = resizeArray( _UnitAmount, _RepeatCount );
      _GuarAmount = resizeArray( _GuarAmount, _RepeatCount );
      _MaturDate = resizeArray( _MaturDate, _RepeatCount );
      _GuarAmtAtMatur = resizeArray( _GuarAmtAtMatur, _RepeatCount );
      _Baycom = resizeArray( _Baycom, _RepeatCount );
      _GuarRecId = resizeArray( _GuarRecId, _RepeatCount );
      _rxSegGuarMatRecId = resizeArray( _rxSegGuarMatRecId, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _TransId[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TransType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TransTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TradeDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _Fund[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Class[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UnitAmount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GuarAmount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MaturDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _GuarAmtAtMatur[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Baycom[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GuarRecId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _rxSegGuarMatRecId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
      }
      

   }

}
      
