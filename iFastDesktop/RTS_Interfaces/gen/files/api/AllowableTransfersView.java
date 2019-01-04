
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Allowable Transfers view.
 * For additional view information see <A HREF="../../../../viewspecs/AllowableTransfers.doc">AllowableTransfers.doc</A>.
 * 
 * @author RTS Generated
 */
public class AllowableTransfersView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Fund From Code member array.
    */
   private String[] _FundFromCode = null;
   
   /**
    * Class From Code member array.
    */
   private String[] _ClassFromCode = null;
   
   /**
    * Fund To Code member array.
    */
   private String[] _FundToCode = null;
   
   /**
    * Class To Code member array.
    */
   private String[] _ClassToCode = null;
   
   /**
    * Buy Sell member array.
    */
   private Boolean[] _BuySell = null;
   
   /**
    * on-line Transfer member array.
    */
   private Integer[] _OnLineTransfer = null;
   
   /**
    * Short Term Trading fee applicable (1 appl, 2 not appl, etc) member array.
    */
   private String[] _ShortTermFee = null;
   
   /**
    * Flag to indicate if the trade is alllowed or not member array.
    */
   private Integer[] _TradeAllowed = null;
   
   /**
    * ApplySrcOfFund member array.
    */
   private String[] _ApplySrcOfFund = null;
   

   /**
    * Constructs the AllowableTransfersView object.
    * 
    */
   public AllowableTransfersView()
   {
      super ( new AllowableTransfersRequest() );
   }

   /**
    * Constructs the AllowableTransfersView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AllowableTransfersView( String hostEncoding )
   {
      super ( new AllowableTransfersRequest( hostEncoding ) );
   }

   /**
    * Gets the AllowableTransfersRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AllowableTransfersRequest object.
    */
   public final AllowableTransfersRequest getRequest()
   {
      return (AllowableTransfersRequest)getIFastRequest();
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
    * Gets the Fund From Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund From Code or null.
    */
   public final String getFundFromCode( int index )
   {
      return _FundFromCode[index];
   }
    
   /**
    * Gets the Fund From Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund From Code or the specified default value.
    */
   public final String getFundFromCode( int index, String defaultValue )
   {
      return _FundFromCode[index] == null ? defaultValue : _FundFromCode[index];
   }
    
   /**
    * Gets the array of Fund From Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund From Code values.
    */
   public final String[] getFundFromCodeArray()
   {
      return _FundFromCode;
   }
    
   /**
    * Gets the Class From Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Class From Code or null.
    */
   public final String getClassFromCode( int index )
   {
      return _ClassFromCode[index];
   }
    
   /**
    * Gets the Class From Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class From Code or the specified default value.
    */
   public final String getClassFromCode( int index, String defaultValue )
   {
      return _ClassFromCode[index] == null ? defaultValue : _ClassFromCode[index];
   }
    
   /**
    * Gets the array of Class From Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Class From Code values.
    */
   public final String[] getClassFromCodeArray()
   {
      return _ClassFromCode;
   }
    
   /**
    * Gets the Fund To Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund To Code or null.
    */
   public final String getFundToCode( int index )
   {
      return _FundToCode[index];
   }
    
   /**
    * Gets the Fund To Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund To Code or the specified default value.
    */
   public final String getFundToCode( int index, String defaultValue )
   {
      return _FundToCode[index] == null ? defaultValue : _FundToCode[index];
   }
    
   /**
    * Gets the array of Fund To Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund To Code values.
    */
   public final String[] getFundToCodeArray()
   {
      return _FundToCode;
   }
    
   /**
    * Gets the Class To Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Class To Code or null.
    */
   public final String getClassToCode( int index )
   {
      return _ClassToCode[index];
   }
    
   /**
    * Gets the Class To Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class To Code or the specified default value.
    */
   public final String getClassToCode( int index, String defaultValue )
   {
      return _ClassToCode[index] == null ? defaultValue : _ClassToCode[index];
   }
    
   /**
    * Gets the array of Class To Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Class To Code values.
    */
   public final String[] getClassToCodeArray()
   {
      return _ClassToCode;
   }
    
   /**
    * Gets the Buy Sell field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Buy Sell or null.
    */
   public final Boolean getBuySell( int index )
   {
      return _BuySell[index];
   }
    
   /**
    * Gets the Buy Sell field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Buy Sell or the specified default value.
    */
   public final boolean getBuySell( int index, boolean defaultValue )
   {
      return _BuySell[index] == null ? defaultValue : _BuySell[index].booleanValue();
   }
    
   /**
    * Gets the array of Buy Sell fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Buy Sell values.
    */
   public final Boolean[] getBuySellArray()
   {
      return _BuySell;
   }
    
   /**
    * Gets the on-line Transfer field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the on-line Transfer or null.
    */
   public final Integer getOnLineTransfer( int index )
   {
      return _OnLineTransfer[index];
   }
    
   /**
    * Gets the on-line Transfer field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the on-line Transfer or the specified default value.
    */
   public final int getOnLineTransfer( int index, int defaultValue )
   {
      return _OnLineTransfer[index] == null ? defaultValue : _OnLineTransfer[index].intValue();
   }
    
   /**
    * Gets the array of on-line Transfer fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of on-line Transfer values.
    */
   public final Integer[] getOnLineTransferArray()
   {
      return _OnLineTransfer;
   }
    
   /**
    * Gets the Short Term Trading fee applicable (1 appl, 2 not appl, etc) field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Short Term Trading fee applicable (1 appl, 2 not appl, etc) or null.
    */
   public final String getShortTermFee( int index )
   {
      return _ShortTermFee[index];
   }
    
   /**
    * Gets the Short Term Trading fee applicable (1 appl, 2 not appl, etc) field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Short Term Trading fee applicable (1 appl, 2 not appl, etc) or the specified default value.
    */
   public final String getShortTermFee( int index, String defaultValue )
   {
      return _ShortTermFee[index] == null ? defaultValue : _ShortTermFee[index];
   }
    
   /**
    * Gets the array of Short Term Trading fee applicable (1 appl, 2 not appl, etc) fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Short Term Trading fee applicable (1 appl, 2 not appl, etc) values.
    */
   public final String[] getShortTermFeeArray()
   {
      return _ShortTermFee;
   }
    
   /**
    * Gets the Flag to indicate if the trade is alllowed or not field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag to indicate if the trade is alllowed or not or null.
    */
   public final Integer getTradeAllowed( int index )
   {
      return _TradeAllowed[index];
   }
    
   /**
    * Gets the Flag to indicate if the trade is alllowed or not field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag to indicate if the trade is alllowed or not or the specified default value.
    */
   public final int getTradeAllowed( int index, int defaultValue )
   {
      return _TradeAllowed[index] == null ? defaultValue : _TradeAllowed[index].intValue();
   }
    
   /**
    * Gets the array of Flag to indicate if the trade is alllowed or not fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag to indicate if the trade is alllowed or not values.
    */
   public final Integer[] getTradeAllowedArray()
   {
      return _TradeAllowed;
   }
    
   /**
    * Gets the ApplySrcOfFund field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ApplySrcOfFund or null.
    */
   public final String getApplySrcOfFund( int index )
   {
      return _ApplySrcOfFund[index];
   }
    
   /**
    * Gets the ApplySrcOfFund field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ApplySrcOfFund or the specified default value.
    */
   public final String getApplySrcOfFund( int index, String defaultValue )
   {
      return _ApplySrcOfFund[index] == null ? defaultValue : _ApplySrcOfFund[index];
   }
    
   /**
    * Gets the array of ApplySrcOfFund fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ApplySrcOfFund values.
    */
   public final String[] getApplySrcOfFundArray()
   {
      return _ApplySrcOfFund;
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
      
      _FundFromCode = resizeArray( _FundFromCode, _RepeatCount );
      _ClassFromCode = resizeArray( _ClassFromCode, _RepeatCount );
      _FundToCode = resizeArray( _FundToCode, _RepeatCount );
      _ClassToCode = resizeArray( _ClassToCode, _RepeatCount );
      _BuySell = resizeArray( _BuySell, _RepeatCount );
      _OnLineTransfer = resizeArray( _OnLineTransfer, _RepeatCount );
      _ShortTermFee = resizeArray( _ShortTermFee, _RepeatCount );
      _TradeAllowed = resizeArray( _TradeAllowed, _RepeatCount );
      _ApplySrcOfFund = resizeArray( _ApplySrcOfFund, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _FundFromCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClassFromCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundToCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClassToCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BuySell[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _OnLineTransfer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ShortTermFee[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TradeAllowed[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ApplySrcOfFund[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
