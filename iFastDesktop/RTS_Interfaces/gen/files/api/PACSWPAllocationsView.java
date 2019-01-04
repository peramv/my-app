
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Account PAC/SWP allocations view.
 * For additional view information see <A HREF="../../../../viewspecs/PACSWPAllocations.doc">PACSWPAllocations.doc</A>.
 * 
 * @author RTS Generated
 */
public class PACSWPAllocationsView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Transaction Type member array.
    */
   private String[] _TransType = null;
   
   /**
    * PACSWPID member array.
    */
   private Integer[] _PACSWPId = null;
   
   /**
    * Fund code member array.
    */
   private String[] _FundCode = null;
   
   /**
    * Class Code member array.
    */
   private String[] _ClassCode = null;
   
   /**
    * Percentage member array.
    */
   private String[] _Percentage = null;
   
   /**
    * Allocation amount member array.
    */
   private String[] _AllocAmount = null;
   
   /**
    * Settle Currency member array.
    */
   private String[] _SettleCurrency = null;
   
   /**
    * Distrib Detl Version Num member array.
    */
   private Integer[] _DistribDetlVer = null;
   
   /**
    * Distrib Detl Record Id member array.
    */
   private Integer[] _DistribDetlRid = null;
   
   /**
    * Allocation Level member array.
    */
   private Integer[] _Level = null;
   
   /**
    * Allocation Account To member array.
    */
   private String[] _AllocAccountNum = null;
   
   /**
    * Transaction Sequence member array.
    */
   private Integer[] _TransSeq = null;
   
   /**
    * Split Commissions Exist member array.
    */
   private Boolean[] _SplitComm = null;
   

   /**
    * Constructs the PACSWPAllocationsView object.
    * 
    */
   public PACSWPAllocationsView()
   {
      super ( new PACSWPAllocationsRequest() );
   }

   /**
    * Constructs the PACSWPAllocationsView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public PACSWPAllocationsView( String hostEncoding )
   {
      super ( new PACSWPAllocationsRequest( hostEncoding ) );
   }

   /**
    * Gets the PACSWPAllocationsRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The PACSWPAllocationsRequest object.
    */
   public final PACSWPAllocationsRequest getRequest()
   {
      return (PACSWPAllocationsRequest)getIFastRequest();
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
    * Gets the PACSWPID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the PACSWPID or null.
    */
   public final Integer getPACSWPId( int index )
   {
      return _PACSWPId[index];
   }
    
   /**
    * Gets the PACSWPID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PACSWPID or the specified default value.
    */
   public final int getPACSWPId( int index, int defaultValue )
   {
      return _PACSWPId[index] == null ? defaultValue : _PACSWPId[index].intValue();
   }
    
   /**
    * Gets the array of PACSWPID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of PACSWPID values.
    */
   public final Integer[] getPACSWPIdArray()
   {
      return _PACSWPId;
   }
    
   /**
    * Gets the Fund code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund code or null.
    */
   public final String getFundCode( int index )
   {
      return _FundCode[index];
   }
    
   /**
    * Gets the Fund code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund code or the specified default value.
    */
   public final String getFundCode( int index, String defaultValue )
   {
      return _FundCode[index] == null ? defaultValue : _FundCode[index];
   }
    
   /**
    * Gets the array of Fund code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund code values.
    */
   public final String[] getFundCodeArray()
   {
      return _FundCode;
   }
    
   /**
    * Gets the Class Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Class Code or null.
    */
   public final String getClassCode( int index )
   {
      return _ClassCode[index];
   }
    
   /**
    * Gets the Class Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class Code or the specified default value.
    */
   public final String getClassCode( int index, String defaultValue )
   {
      return _ClassCode[index] == null ? defaultValue : _ClassCode[index];
   }
    
   /**
    * Gets the array of Class Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Class Code values.
    */
   public final String[] getClassCodeArray()
   {
      return _ClassCode;
   }
    
   /**
    * Gets the Percentage field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Percentage or null.
    */
   public final String getPercentage( int index )
   {
      return _Percentage[index];
   }
    
   /**
    * Gets the Percentage field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Percentage or the specified default value.
    */
   public final String getPercentage( int index, String defaultValue )
   {
      return _Percentage[index] == null ? defaultValue : _Percentage[index];
   }
    
   /**
    * Gets the array of Percentage fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Percentage values.
    */
   public final String[] getPercentageArray()
   {
      return _Percentage;
   }
    
   /**
    * Gets the Allocation amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Allocation amount or null.
    */
   public final String getAllocAmount( int index )
   {
      return _AllocAmount[index];
   }
    
   /**
    * Gets the Allocation amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Allocation amount or the specified default value.
    */
   public final String getAllocAmount( int index, String defaultValue )
   {
      return _AllocAmount[index] == null ? defaultValue : _AllocAmount[index];
   }
    
   /**
    * Gets the array of Allocation amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Allocation amount values.
    */
   public final String[] getAllocAmountArray()
   {
      return _AllocAmount;
   }
    
   /**
    * Gets the Settle Currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Settle Currency or null.
    */
   public final String getSettleCurrency( int index )
   {
      return _SettleCurrency[index];
   }
    
   /**
    * Gets the Settle Currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settle Currency or the specified default value.
    */
   public final String getSettleCurrency( int index, String defaultValue )
   {
      return _SettleCurrency[index] == null ? defaultValue : _SettleCurrency[index];
   }
    
   /**
    * Gets the array of Settle Currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Settle Currency values.
    */
   public final String[] getSettleCurrencyArray()
   {
      return _SettleCurrency;
   }
    
   /**
    * Gets the Distrib Detl Version Num field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Distrib Detl Version Num or null.
    */
   public final Integer getDistribDetlVer( int index )
   {
      return _DistribDetlVer[index];
   }
    
   /**
    * Gets the Distrib Detl Version Num field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Distrib Detl Version Num or the specified default value.
    */
   public final int getDistribDetlVer( int index, int defaultValue )
   {
      return _DistribDetlVer[index] == null ? defaultValue : _DistribDetlVer[index].intValue();
   }
    
   /**
    * Gets the array of Distrib Detl Version Num fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Distrib Detl Version Num values.
    */
   public final Integer[] getDistribDetlVerArray()
   {
      return _DistribDetlVer;
   }
    
   /**
    * Gets the Distrib Detl Record Id field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Distrib Detl Record Id or null.
    */
   public final Integer getDistribDetlRid( int index )
   {
      return _DistribDetlRid[index];
   }
    
   /**
    * Gets the Distrib Detl Record Id field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Distrib Detl Record Id or the specified default value.
    */
   public final int getDistribDetlRid( int index, int defaultValue )
   {
      return _DistribDetlRid[index] == null ? defaultValue : _DistribDetlRid[index].intValue();
   }
    
   /**
    * Gets the array of Distrib Detl Record Id fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Distrib Detl Record Id values.
    */
   public final Integer[] getDistribDetlRidArray()
   {
      return _DistribDetlRid;
   }
    
   /**
    * Gets the Allocation Level field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Allocation Level or null.
    */
   public final Integer getLevel( int index )
   {
      return _Level[index];
   }
    
   /**
    * Gets the Allocation Level field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Allocation Level or the specified default value.
    */
   public final int getLevel( int index, int defaultValue )
   {
      return _Level[index] == null ? defaultValue : _Level[index].intValue();
   }
    
   /**
    * Gets the array of Allocation Level fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Allocation Level values.
    */
   public final Integer[] getLevelArray()
   {
      return _Level;
   }
    
   /**
    * Gets the Allocation Account To field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Allocation Account To or null.
    */
   public final String getAllocAccountNum( int index )
   {
      return _AllocAccountNum[index];
   }
    
   /**
    * Gets the Allocation Account To field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Allocation Account To or the specified default value.
    */
   public final String getAllocAccountNum( int index, String defaultValue )
   {
      return _AllocAccountNum[index] == null ? defaultValue : _AllocAccountNum[index];
   }
    
   /**
    * Gets the array of Allocation Account To fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Allocation Account To values.
    */
   public final String[] getAllocAccountNumArray()
   {
      return _AllocAccountNum;
   }
    
   /**
    * Gets the Transaction Sequence field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transaction Sequence or null.
    */
   public final Integer getTransSeq( int index )
   {
      return _TransSeq[index];
   }
    
   /**
    * Gets the Transaction Sequence field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transaction Sequence or the specified default value.
    */
   public final int getTransSeq( int index, int defaultValue )
   {
      return _TransSeq[index] == null ? defaultValue : _TransSeq[index].intValue();
   }
    
   /**
    * Gets the array of Transaction Sequence fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transaction Sequence values.
    */
   public final Integer[] getTransSeqArray()
   {
      return _TransSeq;
   }
    
   /**
    * Gets the Split Commissions Exist field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Split Commissions Exist or null.
    */
   public final Boolean getSplitComm( int index )
   {
      return _SplitComm[index];
   }
    
   /**
    * Gets the Split Commissions Exist field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Split Commissions Exist or the specified default value.
    */
   public final boolean getSplitComm( int index, boolean defaultValue )
   {
      return _SplitComm[index] == null ? defaultValue : _SplitComm[index].booleanValue();
   }
    
   /**
    * Gets the array of Split Commissions Exist fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Split Commissions Exist values.
    */
   public final Boolean[] getSplitCommArray()
   {
      return _SplitComm;
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
      _PACSWPId = resizeArray( _PACSWPId, _RepeatCount );
      _FundCode = resizeArray( _FundCode, _RepeatCount );
      _ClassCode = resizeArray( _ClassCode, _RepeatCount );
      _Percentage = resizeArray( _Percentage, _RepeatCount );
      _AllocAmount = resizeArray( _AllocAmount, _RepeatCount );
      _SettleCurrency = resizeArray( _SettleCurrency, _RepeatCount );
      _DistribDetlVer = resizeArray( _DistribDetlVer, _RepeatCount );
      _DistribDetlRid = resizeArray( _DistribDetlRid, _RepeatCount );
      _Level = resizeArray( _Level, _RepeatCount );
      _AllocAccountNum = resizeArray( _AllocAccountNum, _RepeatCount );
      _TransSeq = resizeArray( _TransSeq, _RepeatCount );
      _SplitComm = resizeArray( _SplitComm, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _TransType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PACSWPId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _FundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Percentage[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AllocAmount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SettleCurrency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DistribDetlVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _DistribDetlRid[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _Level[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _AllocAccountNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TransSeq[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _SplitComm[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      }
      

   }

}
      
