
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * RESP Transaction Type List view.
 * For additional view information see <A HREF="../../../../viewspecs/RESPTranTypeList.doc">RESPTranTypeList.doc</A>.
 * 
 * @author RTS Generated
 */
public class RESPTranTypeListView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * RESP Transaction Type member array.
    */
   private String[] _TransType = null;
   
   /**
    * Redemption Code member array.
    */
   private String[] _RedCode = null;
   
   /**
    * Deposit Type member array.
    */
   private Integer[] _DepositType = null;
   
   /**
    * TransType Description member array.
    */
   private String[] _TransTypeDesc = null;
   
   /**
    * Transaction Rec ID member array.
    */
   private Integer[] _TransRecID = null;
   
   /**
    * Transfer Status member array.
    */
   private String[] _TfrStat = null;
   
   /**
    * Reported HRDC member array.
    */
   private Boolean[] _RepHRDC = null;
   

   /**
    * Constructs the RESPTranTypeListView object.
    * 
    */
   public RESPTranTypeListView()
   {
      super ( new RESPTranTypeListRequest() );
   }

   /**
    * Constructs the RESPTranTypeListView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public RESPTranTypeListView( String hostEncoding )
   {
      super ( new RESPTranTypeListRequest( hostEncoding ) );
   }

   /**
    * Gets the RESPTranTypeListRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The RESPTranTypeListRequest object.
    */
   public final RESPTranTypeListRequest getRequest()
   {
      return (RESPTranTypeListRequest)getIFastRequest();
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
    * Gets the RESP Transaction Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RESP Transaction Type or null.
    */
   public final String getTransType( int index )
   {
      return _TransType[index];
   }
    
   /**
    * Gets the RESP Transaction Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RESP Transaction Type or the specified default value.
    */
   public final String getTransType( int index, String defaultValue )
   {
      return _TransType[index] == null ? defaultValue : _TransType[index];
   }
    
   /**
    * Gets the array of RESP Transaction Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RESP Transaction Type values.
    */
   public final String[] getTransTypeArray()
   {
      return _TransType;
   }
    
   /**
    * Gets the Redemption Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Redemption Code or null.
    */
   public final String getRedCode( int index )
   {
      return _RedCode[index];
   }
    
   /**
    * Gets the Redemption Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Redemption Code or the specified default value.
    */
   public final String getRedCode( int index, String defaultValue )
   {
      return _RedCode[index] == null ? defaultValue : _RedCode[index];
   }
    
   /**
    * Gets the array of Redemption Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Redemption Code values.
    */
   public final String[] getRedCodeArray()
   {
      return _RedCode;
   }
    
   /**
    * Gets the Deposit Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Deposit Type or null.
    */
   public final Integer getDepositType( int index )
   {
      return _DepositType[index];
   }
    
   /**
    * Gets the Deposit Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Deposit Type or the specified default value.
    */
   public final int getDepositType( int index, int defaultValue )
   {
      return _DepositType[index] == null ? defaultValue : _DepositType[index].intValue();
   }
    
   /**
    * Gets the array of Deposit Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Deposit Type values.
    */
   public final Integer[] getDepositTypeArray()
   {
      return _DepositType;
   }
    
   /**
    * Gets the TransType Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the TransType Description or null.
    */
   public final String getTransTypeDesc( int index )
   {
      return _TransTypeDesc[index];
   }
    
   /**
    * Gets the TransType Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TransType Description or the specified default value.
    */
   public final String getTransTypeDesc( int index, String defaultValue )
   {
      return _TransTypeDesc[index] == null ? defaultValue : _TransTypeDesc[index];
   }
    
   /**
    * Gets the array of TransType Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of TransType Description values.
    */
   public final String[] getTransTypeDescArray()
   {
      return _TransTypeDesc;
   }
    
   /**
    * Gets the Transaction Rec ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transaction Rec ID or null.
    */
   public final Integer getTransRecID( int index )
   {
      return _TransRecID[index];
   }
    
   /**
    * Gets the Transaction Rec ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transaction Rec ID or the specified default value.
    */
   public final int getTransRecID( int index, int defaultValue )
   {
      return _TransRecID[index] == null ? defaultValue : _TransRecID[index].intValue();
   }
    
   /**
    * Gets the array of Transaction Rec ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transaction Rec ID values.
    */
   public final Integer[] getTransRecIDArray()
   {
      return _TransRecID;
   }
    
   /**
    * Gets the Transfer Status field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transfer Status or null.
    */
   public final String getTfrStat( int index )
   {
      return _TfrStat[index];
   }
    
   /**
    * Gets the Transfer Status field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transfer Status or the specified default value.
    */
   public final String getTfrStat( int index, String defaultValue )
   {
      return _TfrStat[index] == null ? defaultValue : _TfrStat[index];
   }
    
   /**
    * Gets the array of Transfer Status fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transfer Status values.
    */
   public final String[] getTfrStatArray()
   {
      return _TfrStat;
   }
    
   /**
    * Gets the Reported HRDC field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reported HRDC or null.
    */
   public final Boolean getRepHRDC( int index )
   {
      return _RepHRDC[index];
   }
    
   /**
    * Gets the Reported HRDC field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reported HRDC or the specified default value.
    */
   public final boolean getRepHRDC( int index, boolean defaultValue )
   {
      return _RepHRDC[index] == null ? defaultValue : _RepHRDC[index].booleanValue();
   }
    
   /**
    * Gets the array of Reported HRDC fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reported HRDC values.
    */
   public final Boolean[] getRepHRDCArray()
   {
      return _RepHRDC;
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
      
      _TransType = resizeArray( _TransType, _RepeatCount );
      _RedCode = resizeArray( _RedCode, _RepeatCount );
      _DepositType = resizeArray( _DepositType, _RepeatCount );
      _TransTypeDesc = resizeArray( _TransTypeDesc, _RepeatCount );
      _TransRecID = resizeArray( _TransRecID, _RepeatCount );
      _TfrStat = resizeArray( _TfrStat, _RepeatCount );
      _RepHRDC = resizeArray( _RepHRDC, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _TransType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RedCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DepositType[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _TransTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TransRecID[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _TfrStat[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RepHRDC[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      }
      

   }

}
      
