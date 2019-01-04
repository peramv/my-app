
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Pending Trade Allocation view.
 * For additional view information see <A HREF="../../../../viewspecs/PendAlloc.doc">PendAlloc.doc</A>.
 * 
 * @author RTS Generated
 */
public class PendAllocView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Fund Code member array.
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
    * Amount member array.
    */
   private String[] _Amount = null;
   
   /**
    * Settle Currency member array.
    */
   private String[] _SettleCurrency = null;
   
   /**
    * Split Commissions Exist member array.
    */
   private Boolean[] _SplitComm = null;
   
   /**
    * Transaction Sequence member array.
    */
   private Integer[] _TransSeq = null;
   
   /**
    * Allocation Account Number member array.
    */
   private String[] _AllocAccountNum = null;
   
   /**
    * Account Percent member array.
    */
   private String[] _AcctPrcnt = null;
   
   /**
    * Distribution Account Level Version Number member array.
    */
   private Integer[] _DistribAcctLvlVer = null;
   
   /**
    * Distribution Account Level Recid member array.
    */
   private Integer[] _DistribAcctLvlRId = null;
   
   /**
    * Distribution record Id at level 3 member array.
    */
   private Integer[] _DistribDetlRid = null;
   
   /**
    * Distrib-Detl vesion number at level 3 member array.
    */
   private Integer[] _DistribDetlVer = null;
   
   /**
    * Allocation Amount Type member array.
    */
   private String[] _AllocAmountType = null;
   
   /**
    * Transaction ID member array.
    */
   private String[] _Transid = null;
   

   /**
    * Constructs the PendAllocView object.
    * 
    */
   public PendAllocView()
   {
      super ( new PendAllocRequest() );
   }

   /**
    * Constructs the PendAllocView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public PendAllocView( String hostEncoding )
   {
      super ( new PendAllocRequest( hostEncoding ) );
   }

   /**
    * Gets the PendAllocRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The PendAllocRequest object.
    */
   public final PendAllocRequest getRequest()
   {
      return (PendAllocRequest)getIFastRequest();
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
    * Gets the Fund Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Code or null.
    */
   public final String getFundCode( int index )
   {
      return _FundCode[index];
   }
    
   /**
    * Gets the Fund Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Code or the specified default value.
    */
   public final String getFundCode( int index, String defaultValue )
   {
      return _FundCode[index] == null ? defaultValue : _FundCode[index];
   }
    
   /**
    * Gets the array of Fund Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Code values.
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
    * Gets the Allocation Account Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Allocation Account Number or null.
    */
   public final String getAllocAccountNum( int index )
   {
      return _AllocAccountNum[index];
   }
    
   /**
    * Gets the Allocation Account Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Allocation Account Number or the specified default value.
    */
   public final String getAllocAccountNum( int index, String defaultValue )
   {
      return _AllocAccountNum[index] == null ? defaultValue : _AllocAccountNum[index];
   }
    
   /**
    * Gets the array of Allocation Account Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Allocation Account Number values.
    */
   public final String[] getAllocAccountNumArray()
   {
      return _AllocAccountNum;
   }
    
   /**
    * Gets the Account Percent field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Percent or null.
    */
   public final String getAcctPrcnt( int index )
   {
      return _AcctPrcnt[index];
   }
    
   /**
    * Gets the Account Percent field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Percent or the specified default value.
    */
   public final String getAcctPrcnt( int index, String defaultValue )
   {
      return _AcctPrcnt[index] == null ? defaultValue : _AcctPrcnt[index];
   }
    
   /**
    * Gets the array of Account Percent fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Percent values.
    */
   public final String[] getAcctPrcntArray()
   {
      return _AcctPrcnt;
   }
    
   /**
    * Gets the Distribution Account Level Version Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Distribution Account Level Version Number or null.
    */
   public final Integer getDistribAcctLvlVer( int index )
   {
      return _DistribAcctLvlVer[index];
   }
    
   /**
    * Gets the Distribution Account Level Version Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Distribution Account Level Version Number or the specified default value.
    */
   public final int getDistribAcctLvlVer( int index, int defaultValue )
   {
      return _DistribAcctLvlVer[index] == null ? defaultValue : _DistribAcctLvlVer[index].intValue();
   }
    
   /**
    * Gets the array of Distribution Account Level Version Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Distribution Account Level Version Number values.
    */
   public final Integer[] getDistribAcctLvlVerArray()
   {
      return _DistribAcctLvlVer;
   }
    
   /**
    * Gets the Distribution Account Level Recid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Distribution Account Level Recid or null.
    */
   public final Integer getDistribAcctLvlRId( int index )
   {
      return _DistribAcctLvlRId[index];
   }
    
   /**
    * Gets the Distribution Account Level Recid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Distribution Account Level Recid or the specified default value.
    */
   public final int getDistribAcctLvlRId( int index, int defaultValue )
   {
      return _DistribAcctLvlRId[index] == null ? defaultValue : _DistribAcctLvlRId[index].intValue();
   }
    
   /**
    * Gets the array of Distribution Account Level Recid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Distribution Account Level Recid values.
    */
   public final Integer[] getDistribAcctLvlRIdArray()
   {
      return _DistribAcctLvlRId;
   }
    
   /**
    * Gets the Distribution record Id at level 3 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Distribution record Id at level 3 or null.
    */
   public final Integer getDistribDetlRid( int index )
   {
      return _DistribDetlRid[index];
   }
    
   /**
    * Gets the Distribution record Id at level 3 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Distribution record Id at level 3 or the specified default value.
    */
   public final int getDistribDetlRid( int index, int defaultValue )
   {
      return _DistribDetlRid[index] == null ? defaultValue : _DistribDetlRid[index].intValue();
   }
    
   /**
    * Gets the array of Distribution record Id at level 3 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Distribution record Id at level 3 values.
    */
   public final Integer[] getDistribDetlRidArray()
   {
      return _DistribDetlRid;
   }
    
   /**
    * Gets the Distrib-Detl vesion number at level 3 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Distrib-Detl vesion number at level 3 or null.
    */
   public final Integer getDistribDetlVer( int index )
   {
      return _DistribDetlVer[index];
   }
    
   /**
    * Gets the Distrib-Detl vesion number at level 3 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Distrib-Detl vesion number at level 3 or the specified default value.
    */
   public final int getDistribDetlVer( int index, int defaultValue )
   {
      return _DistribDetlVer[index] == null ? defaultValue : _DistribDetlVer[index].intValue();
   }
    
   /**
    * Gets the array of Distrib-Detl vesion number at level 3 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Distrib-Detl vesion number at level 3 values.
    */
   public final Integer[] getDistribDetlVerArray()
   {
      return _DistribDetlVer;
   }
    
   /**
    * Gets the Allocation Amount Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Allocation Amount Type or null.
    */
   public final String getAllocAmountType( int index )
   {
      return _AllocAmountType[index];
   }
    
   /**
    * Gets the Allocation Amount Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Allocation Amount Type or the specified default value.
    */
   public final String getAllocAmountType( int index, String defaultValue )
   {
      return _AllocAmountType[index] == null ? defaultValue : _AllocAmountType[index];
   }
    
   /**
    * Gets the array of Allocation Amount Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Allocation Amount Type values.
    */
   public final String[] getAllocAmountTypeArray()
   {
      return _AllocAmountType;
   }
    
   /**
    * Gets the Transaction ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transaction ID or null.
    */
   public final String getTransid( int index )
   {
      return _Transid[index];
   }
    
   /**
    * Gets the Transaction ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transaction ID or the specified default value.
    */
   public final String getTransid( int index, String defaultValue )
   {
      return _Transid[index] == null ? defaultValue : _Transid[index];
   }
    
   /**
    * Gets the array of Transaction ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transaction ID values.
    */
   public final String[] getTransidArray()
   {
      return _Transid;
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
      
      _FundCode = resizeArray( _FundCode, _RepeatCount );
      _ClassCode = resizeArray( _ClassCode, _RepeatCount );
      _Percentage = resizeArray( _Percentage, _RepeatCount );
      _Amount = resizeArray( _Amount, _RepeatCount );
      _SettleCurrency = resizeArray( _SettleCurrency, _RepeatCount );
      _SplitComm = resizeArray( _SplitComm, _RepeatCount );
      _TransSeq = resizeArray( _TransSeq, _RepeatCount );
      _AllocAccountNum = resizeArray( _AllocAccountNum, _RepeatCount );
      _AcctPrcnt = resizeArray( _AcctPrcnt, _RepeatCount );
      _DistribAcctLvlVer = resizeArray( _DistribAcctLvlVer, _RepeatCount );
      _DistribAcctLvlRId = resizeArray( _DistribAcctLvlRId, _RepeatCount );
      _DistribDetlRid = resizeArray( _DistribDetlRid, _RepeatCount );
      _DistribDetlVer = resizeArray( _DistribDetlVer, _RepeatCount );
      _AllocAmountType = resizeArray( _AllocAmountType, _RepeatCount );
      _Transid = resizeArray( _Transid, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _FundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Percentage[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Amount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SettleCurrency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SplitComm[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TransSeq[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _AllocAccountNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctPrcnt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DistribAcctLvlVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _DistribAcctLvlRId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _DistribDetlRid[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _DistribDetlVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _AllocAmountType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Transid[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
