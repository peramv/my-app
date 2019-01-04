
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Account Default Allocation view.
 * For additional view information see <A HREF="../../../../viewspecs/AccountDefaultAllocations.doc">AccountDefaultAllocations.doc</A>.
 * 
 * @author RTS Generated
 */
public class AccountDefaultAllocationsView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Transaction Type member array.
    */
   private String[] _rxTransType = null;
   
   /**
    * Transaction Type Description member array.
    */
   private String[] _TransTypeDesc = null;
   
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
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = null;
   
   /**
    * Distrib-Detl Version Number member array.
    */
   private Integer[] _DistribDetlVer = null;
   
   /**
    * Distrib-Detl Record Id member array.
    */
   private Integer[] _DistribDetlRid = null;
   
   /**
    * Allocation Level member array.
    */
   private Integer[] _Level = null;
   
   /**
    * Account Number member array.
    */
   private String[] _AccountNum = null;
   
   /**
    * Foreign Sweeps Excess Transfer Flag member array.
    */
   private Boolean[] _FrgnSweep = null;
   
   /**
    * Fund Group member array.
    */
   private String[] _FundGroup = null;
   
   /**
    * Rebalance Percent member array.
    */
   private String[] _RebalPrcnt = null;
   
   /**
    * Currency for AMSCode member array.
    */
   private String[] _AMSCurrency = null;
   
   /**
    * Commission amount if Commission Type is flat OR commission percentage if commission type is percent member array.
    */
   private String[] _FELComm = null;
   
   /**
    * Commission Type (Flat or Percent) member array.
    */
   private Boolean[] _FELCommType = null;
   

   /**
    * Constructs the AccountDefaultAllocationsView object.
    * 
    */
   public AccountDefaultAllocationsView()
   {
      super ( new AccountDefaultAllocationsRequest() );
   }

   /**
    * Constructs the AccountDefaultAllocationsView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AccountDefaultAllocationsView( String hostEncoding )
   {
      super ( new AccountDefaultAllocationsRequest( hostEncoding ) );
   }

   /**
    * Gets the AccountDefaultAllocationsRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AccountDefaultAllocationsRequest object.
    */
   public final AccountDefaultAllocationsRequest getRequest()
   {
      return (AccountDefaultAllocationsRequest)getIFastRequest();
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
   public final String getrxTransType( int index )
   {
      return _rxTransType[index];
   }
    
   /**
    * Gets the Transaction Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transaction Type or the specified default value.
    */
   public final String getrxTransType( int index, String defaultValue )
   {
      return _rxTransType[index] == null ? defaultValue : _rxTransType[index];
   }
    
   /**
    * Gets the array of Transaction Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transaction Type values.
    */
   public final String[] getrxTransTypeArray()
   {
      return _rxTransType;
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
    * Gets the Effective Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Effective Date or null.
    */
   public final Date getEffectiveDate( int index )
   {
      return _EffectiveDate[index];
   }
    
   /**
    * Gets the Effective Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Effective Date or the specified default value.
    */
   public final Date getEffectiveDate( int index, Date defaultValue )
   {
      return _EffectiveDate[index] == null ? defaultValue : _EffectiveDate[index];
   }
    
   /**
    * Gets the array of Effective Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Effective Date values.
    */
   public final Date[] getEffectiveDateArray()
   {
      return _EffectiveDate;
   }
    
   /**
    * Gets the Distrib-Detl Version Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Distrib-Detl Version Number or null.
    */
   public final Integer getDistribDetlVer( int index )
   {
      return _DistribDetlVer[index];
   }
    
   /**
    * Gets the Distrib-Detl Version Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Distrib-Detl Version Number or the specified default value.
    */
   public final int getDistribDetlVer( int index, int defaultValue )
   {
      return _DistribDetlVer[index] == null ? defaultValue : _DistribDetlVer[index].intValue();
   }
    
   /**
    * Gets the array of Distrib-Detl Version Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Distrib-Detl Version Number values.
    */
   public final Integer[] getDistribDetlVerArray()
   {
      return _DistribDetlVer;
   }
    
   /**
    * Gets the Distrib-Detl Record Id field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Distrib-Detl Record Id or null.
    */
   public final Integer getDistribDetlRid( int index )
   {
      return _DistribDetlRid[index];
   }
    
   /**
    * Gets the Distrib-Detl Record Id field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Distrib-Detl Record Id or the specified default value.
    */
   public final int getDistribDetlRid( int index, int defaultValue )
   {
      return _DistribDetlRid[index] == null ? defaultValue : _DistribDetlRid[index].intValue();
   }
    
   /**
    * Gets the array of Distrib-Detl Record Id fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Distrib-Detl Record Id values.
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
    * Gets the Account Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Number or null.
    */
   public final String getAccountNum( int index )
   {
      return _AccountNum[index];
   }
    
   /**
    * Gets the Account Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Number or the specified default value.
    */
   public final String getAccountNum( int index, String defaultValue )
   {
      return _AccountNum[index] == null ? defaultValue : _AccountNum[index];
   }
    
   /**
    * Gets the array of Account Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Number values.
    */
   public final String[] getAccountNumArray()
   {
      return _AccountNum;
   }
    
   /**
    * Gets the Foreign Sweeps Excess Transfer Flag field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Foreign Sweeps Excess Transfer Flag or null.
    */
   public final Boolean getFrgnSweep( int index )
   {
      return _FrgnSweep[index];
   }
    
   /**
    * Gets the Foreign Sweeps Excess Transfer Flag field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Foreign Sweeps Excess Transfer Flag or the specified default value.
    */
   public final boolean getFrgnSweep( int index, boolean defaultValue )
   {
      return _FrgnSweep[index] == null ? defaultValue : _FrgnSweep[index].booleanValue();
   }
    
   /**
    * Gets the array of Foreign Sweeps Excess Transfer Flag fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Foreign Sweeps Excess Transfer Flag values.
    */
   public final Boolean[] getFrgnSweepArray()
   {
      return _FrgnSweep;
   }
    
   /**
    * Gets the Fund Group field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Group or null.
    */
   public final String getFundGroup( int index )
   {
      return _FundGroup[index];
   }
    
   /**
    * Gets the Fund Group field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Group or the specified default value.
    */
   public final String getFundGroup( int index, String defaultValue )
   {
      return _FundGroup[index] == null ? defaultValue : _FundGroup[index];
   }
    
   /**
    * Gets the array of Fund Group fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Group values.
    */
   public final String[] getFundGroupArray()
   {
      return _FundGroup;
   }
    
   /**
    * Gets the Rebalance Percent field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Rebalance Percent or null.
    */
   public final String getRebalPrcnt( int index )
   {
      return _RebalPrcnt[index];
   }
    
   /**
    * Gets the Rebalance Percent field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Rebalance Percent or the specified default value.
    */
   public final String getRebalPrcnt( int index, String defaultValue )
   {
      return _RebalPrcnt[index] == null ? defaultValue : _RebalPrcnt[index];
   }
    
   /**
    * Gets the array of Rebalance Percent fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Rebalance Percent values.
    */
   public final String[] getRebalPrcntArray()
   {
      return _RebalPrcnt;
   }
    
   /**
    * Gets the Currency for AMSCode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Currency for AMSCode or null.
    */
   public final String getAMSCurrency( int index )
   {
      return _AMSCurrency[index];
   }
    
   /**
    * Gets the Currency for AMSCode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Currency for AMSCode or the specified default value.
    */
   public final String getAMSCurrency( int index, String defaultValue )
   {
      return _AMSCurrency[index] == null ? defaultValue : _AMSCurrency[index];
   }
    
   /**
    * Gets the array of Currency for AMSCode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Currency for AMSCode values.
    */
   public final String[] getAMSCurrencyArray()
   {
      return _AMSCurrency;
   }
    
   /**
    * Gets the Commission amount if Commission Type is flat OR commission percentage if commission type is percent field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Commission amount if Commission Type is flat OR commission percentage if commission type is percent or null.
    */
   public final String getFELComm( int index )
   {
      return _FELComm[index];
   }
    
   /**
    * Gets the Commission amount if Commission Type is flat OR commission percentage if commission type is percent field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commission amount if Commission Type is flat OR commission percentage if commission type is percent or the specified default value.
    */
   public final String getFELComm( int index, String defaultValue )
   {
      return _FELComm[index] == null ? defaultValue : _FELComm[index];
   }
    
   /**
    * Gets the array of Commission amount if Commission Type is flat OR commission percentage if commission type is percent fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Commission amount if Commission Type is flat OR commission percentage if commission type is percent values.
    */
   public final String[] getFELCommArray()
   {
      return _FELComm;
   }
    
   /**
    * Gets the Commission Type (Flat or Percent) field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Commission Type (Flat or Percent) or null.
    */
   public final Boolean getFELCommType( int index )
   {
      return _FELCommType[index];
   }
    
   /**
    * Gets the Commission Type (Flat or Percent) field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commission Type (Flat or Percent) or the specified default value.
    */
   public final boolean getFELCommType( int index, boolean defaultValue )
   {
      return _FELCommType[index] == null ? defaultValue : _FELCommType[index].booleanValue();
   }
    
   /**
    * Gets the array of Commission Type (Flat or Percent) fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Commission Type (Flat or Percent) values.
    */
   public final Boolean[] getFELCommTypeArray()
   {
      return _FELCommType;
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
      
      _rxTransType = resizeArray( _rxTransType, _RepeatCount );
      _TransTypeDesc = resizeArray( _TransTypeDesc, _RepeatCount );
      _FundCode = resizeArray( _FundCode, _RepeatCount );
      _ClassCode = resizeArray( _ClassCode, _RepeatCount );
      _Percentage = resizeArray( _Percentage, _RepeatCount );
      _EffectiveDate = resizeArray( _EffectiveDate, _RepeatCount );
      _DistribDetlVer = resizeArray( _DistribDetlVer, _RepeatCount );
      _DistribDetlRid = resizeArray( _DistribDetlRid, _RepeatCount );
      _Level = resizeArray( _Level, _RepeatCount );
      _AccountNum = resizeArray( _AccountNum, _RepeatCount );
      _FrgnSweep = resizeArray( _FrgnSweep, _RepeatCount );
      _FundGroup = resizeArray( _FundGroup, _RepeatCount );
      _RebalPrcnt = resizeArray( _RebalPrcnt, _RepeatCount );
      _AMSCurrency = resizeArray( _AMSCurrency, _RepeatCount );
      _FELComm = resizeArray( _FELComm, _RepeatCount );
      _FELCommType = resizeArray( _FELCommType, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxTransType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TransTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Percentage[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _DistribDetlVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _DistribDetlRid[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _Level[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _AccountNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FrgnSweep[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FundGroup[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RebalPrcnt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AMSCurrency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FELComm[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FELCommType[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      }
      

   }

}
      
