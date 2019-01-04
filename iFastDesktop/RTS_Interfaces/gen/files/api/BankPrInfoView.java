
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * BankFile Processor Information view.
 * For additional view information see <A HREF="../../../../viewspecs/BankPrInfo.doc">BankPrInfo.doc</A>.
 * 
 * @author RTS Generated
 */
public class BankPrInfoView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * File Proc Code member array.
    */
   private String[] _FileProcCode = null;
   
   /**
    * Transaction Type member array.
    */
   private String[] _TradeType = null;
   
   /**
    * Settlement Currency List member array.
    */
   private String[] _Currency = null;
   
   /**
    * Payment Method member array.
    */
   private String[] _PayMethod = null;
   

   /**
    * Constructs the BankPrInfoView object.
    * 
    */
   public BankPrInfoView()
   {
      super ( new BankPrInfoRequest() );
   }

   /**
    * Constructs the BankPrInfoView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public BankPrInfoView( String hostEncoding )
   {
      super ( new BankPrInfoRequest( hostEncoding ) );
   }

   /**
    * Gets the BankPrInfoRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The BankPrInfoRequest object.
    */
   public final BankPrInfoRequest getRequest()
   {
      return (BankPrInfoRequest)getIFastRequest();
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
    * Gets the File Proc Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the File Proc Code or null.
    */
   public final String getFileProcCode( int index )
   {
      return _FileProcCode[index];
   }
    
   /**
    * Gets the File Proc Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the File Proc Code or the specified default value.
    */
   public final String getFileProcCode( int index, String defaultValue )
   {
      return _FileProcCode[index] == null ? defaultValue : _FileProcCode[index];
   }
    
   /**
    * Gets the array of File Proc Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of File Proc Code values.
    */
   public final String[] getFileProcCodeArray()
   {
      return _FileProcCode;
   }
    
   /**
    * Gets the Transaction Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transaction Type or null.
    */
   public final String getTradeType( int index )
   {
      return _TradeType[index];
   }
    
   /**
    * Gets the Transaction Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transaction Type or the specified default value.
    */
   public final String getTradeType( int index, String defaultValue )
   {
      return _TradeType[index] == null ? defaultValue : _TradeType[index];
   }
    
   /**
    * Gets the array of Transaction Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transaction Type values.
    */
   public final String[] getTradeTypeArray()
   {
      return _TradeType;
   }
    
   /**
    * Gets the Settlement Currency List field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Settlement Currency List or null.
    */
   public final String getCurrency( int index )
   {
      return _Currency[index];
   }
    
   /**
    * Gets the Settlement Currency List field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settlement Currency List or the specified default value.
    */
   public final String getCurrency( int index, String defaultValue )
   {
      return _Currency[index] == null ? defaultValue : _Currency[index];
   }
    
   /**
    * Gets the array of Settlement Currency List fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Settlement Currency List values.
    */
   public final String[] getCurrencyArray()
   {
      return _Currency;
   }
    
   /**
    * Gets the Payment Method field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Payment Method or null.
    */
   public final String getPayMethod( int index )
   {
      return _PayMethod[index];
   }
    
   /**
    * Gets the Payment Method field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payment Method or the specified default value.
    */
   public final String getPayMethod( int index, String defaultValue )
   {
      return _PayMethod[index] == null ? defaultValue : _PayMethod[index];
   }
    
   /**
    * Gets the array of Payment Method fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Payment Method values.
    */
   public final String[] getPayMethodArray()
   {
      return _PayMethod;
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
      
      _FileProcCode = resizeArray( _FileProcCode, _RepeatCount );
      _TradeType = resizeArray( _TradeType, _RepeatCount );
      _Currency = resizeArray( _Currency, _RepeatCount );
      _PayMethod = resizeArray( _PayMethod, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _FileProcCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TradeType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Currency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PayMethod[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
