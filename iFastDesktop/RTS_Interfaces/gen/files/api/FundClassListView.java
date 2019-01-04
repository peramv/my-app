
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Fund-Class List view.
 * For additional view information see <A HREF="../../../../viewspecs/FundClassList.doc">FundClassList.doc</A>.
 * 
 * @author RTS Generated
 */
public class FundClassListView extends IFastView implements Serializable
{

   private int _FundCount = 0;
   
   /**
    * Fund Code member array.
    */
   private String[] _FundCode = null;
   
   /**
    * Fund Type member array.
    */
   private String[] _FundType = null;
   
   /**
    * Price At Class member array.
    */
   private Boolean[] _PriceAtClass = null;
   
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = null;
   
   /**
    * Stop Date member array.
    */
   private Date[] _StopDate = null;
   
   /**
    * Start Index for Fund Classes member array.
    */
   private Integer[] _ClassStartIdx = null;
   
   /**
    * End Index for Fund Classes member array.
    */
   private Integer[] _ClassEndIdx = null;
   
   /**
    * English Short Name for Fund member array.
    */
   private String[] _EShortName = null;
   
   /**
    * Short Name for Fund in other language member array.
    */
   private String[] _OthShortName = null;
   
   private int _FndClassCount = 0;
   
   /**
    * Acquisition Fee Type member array.
    */
   private String[] _AcqFeeType = null;
   
   /**
    * Acquisition Fee Rate member array.
    */
   private String[] _AcqRate = null;
   
   /**
    * Redemption Fee Type member array.
    */
   private String[] _RedemFeeType = null;
   
   /**
    * Redemption Fee Rate member array.
    */
   private String[] _RedemFee = null;
   
   /**
    * Redemption Fee Currency member array.
    */
   private String[] _RedemFeeCurrency = null;
   
   /**
    * Load Type member array.
    */
   private String[] _LoadType = null;
   
   /**
    * Fund Currency member array.
    */
   private String[] _FundCurrency = null;
   
   /**
    * Class Index member array.
    */
   private Integer[] _ClassIndex = null;
   
   /**
    * Class Code member array.
    */
   private String[] _ClassCode = null;
   
   /**
    * Exchange Allowed member array.
    */
   private Boolean[] _ExchangeAllowed = null;
   

   /**
    * Constructs the FundClassListView object.
    * 
    */
   public FundClassListView()
   {
      super ( new FundClassListRequest() );
   }

   /**
    * Constructs the FundClassListView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public FundClassListView( String hostEncoding )
   {
      super ( new FundClassListRequest( hostEncoding ) );
   }

   /**
    * Gets the FundClassListRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The FundClassListRequest object.
    */
   public final FundClassListRequest getRequest()
   {
      return (FundClassListRequest)getIFastRequest();
   }
        
   /**
    * Gets the Record Count for the repeatable response.
    * 
    * @return The number of records in the repeating fields.
    */
   public int getRecordCount()
   {
      return _FundCount;
   }

   /**
    * Gets the Record Count for the repeatable response.
    * 
    * @return The number of records in the repeating fields.
    */
   public final int getFundCount()
   {
      return _FundCount;
   }

   /**
    * Decodes the repeat count value from the host 
    * respones.
    * 
    * @param response Host formatted response object.
    * @exception ParseException
    */
   private final void decodeFundCount( RTSResponseDecodeBuffer responseBuffer ) throws ParseException, UnsupportedEncodingException
   {
      int receivedRecordCount = responseBuffer.decodeInteger(responseBuffer.getNextField()).intValue();
      _FundCount += receivedRecordCount;
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
    * Gets the Fund Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Type or null.
    */
   public final String getFundType( int index )
   {
      return _FundType[index];
   }
    
   /**
    * Gets the Fund Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Type or the specified default value.
    */
   public final String getFundType( int index, String defaultValue )
   {
      return _FundType[index] == null ? defaultValue : _FundType[index];
   }
    
   /**
    * Gets the array of Fund Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Type values.
    */
   public final String[] getFundTypeArray()
   {
      return _FundType;
   }
    
   /**
    * Gets the Price At Class field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Price At Class or null.
    */
   public final Boolean getPriceAtClass( int index )
   {
      return _PriceAtClass[index];
   }
    
   /**
    * Gets the Price At Class field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Price At Class or the specified default value.
    */
   public final boolean getPriceAtClass( int index, boolean defaultValue )
   {
      return _PriceAtClass[index] == null ? defaultValue : _PriceAtClass[index].booleanValue();
   }
    
   /**
    * Gets the array of Price At Class fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Price At Class values.
    */
   public final Boolean[] getPriceAtClassArray()
   {
      return _PriceAtClass;
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
    * Gets the Stop Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stop Date or null.
    */
   public final Date getStopDate( int index )
   {
      return _StopDate[index];
   }
    
   /**
    * Gets the Stop Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Date or the specified default value.
    */
   public final Date getStopDate( int index, Date defaultValue )
   {
      return _StopDate[index] == null ? defaultValue : _StopDate[index];
   }
    
   /**
    * Gets the array of Stop Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stop Date values.
    */
   public final Date[] getStopDateArray()
   {
      return _StopDate;
   }
    
   /**
    * Gets the Start Index for Fund Classes field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Start Index for Fund Classes or null.
    */
   public final Integer getClassStartIdx( int index )
   {
      return _ClassStartIdx[index];
   }
    
   /**
    * Gets the Start Index for Fund Classes field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Start Index for Fund Classes or the specified default value.
    */
   public final int getClassStartIdx( int index, int defaultValue )
   {
      return _ClassStartIdx[index] == null ? defaultValue : _ClassStartIdx[index].intValue();
   }
    
   /**
    * Gets the array of Start Index for Fund Classes fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Start Index for Fund Classes values.
    */
   public final Integer[] getClassStartIdxArray()
   {
      return _ClassStartIdx;
   }
    
   /**
    * Gets the End Index for Fund Classes field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the End Index for Fund Classes or null.
    */
   public final Integer getClassEndIdx( int index )
   {
      return _ClassEndIdx[index];
   }
    
   /**
    * Gets the End Index for Fund Classes field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the End Index for Fund Classes or the specified default value.
    */
   public final int getClassEndIdx( int index, int defaultValue )
   {
      return _ClassEndIdx[index] == null ? defaultValue : _ClassEndIdx[index].intValue();
   }
    
   /**
    * Gets the array of End Index for Fund Classes fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of End Index for Fund Classes values.
    */
   public final Integer[] getClassEndIdxArray()
   {
      return _ClassEndIdx;
   }
    
   /**
    * Gets the English Short Name for Fund field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the English Short Name for Fund or null.
    */
   public final String getEShortName( int index )
   {
      return _EShortName[index];
   }
    
   /**
    * Gets the English Short Name for Fund field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the English Short Name for Fund or the specified default value.
    */
   public final String getEShortName( int index, String defaultValue )
   {
      return _EShortName[index] == null ? defaultValue : _EShortName[index];
   }
    
   /**
    * Gets the array of English Short Name for Fund fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of English Short Name for Fund values.
    */
   public final String[] getEShortNameArray()
   {
      return _EShortName;
   }
    
   /**
    * Gets the Short Name for Fund in other language field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Short Name for Fund in other language or null.
    */
   public final String getOthShortName( int index )
   {
      return _OthShortName[index];
   }
    
   /**
    * Gets the Short Name for Fund in other language field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Short Name for Fund in other language or the specified default value.
    */
   public final String getOthShortName( int index, String defaultValue )
   {
      return _OthShortName[index] == null ? defaultValue : _OthShortName[index];
   }
    
   /**
    * Gets the array of Short Name for Fund in other language fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Short Name for Fund in other language values.
    */
   public final String[] getOthShortNameArray()
   {
      return _OthShortName;
   }
    
   /**
    * Gets the Record Count for the repeatable response.
    * 
    * @return The number of records in the repeating fields.
    */
   public final int getFndClassCount()
   {
      return _FndClassCount;
   }

   /**
    * Decodes the repeat count value from the host 
    * respones.
    * 
    * @param response Host formatted response object.
    * @exception ParseException
    */
   private final void decodeFndClassCount( RTSResponseDecodeBuffer responseBuffer ) throws ParseException, UnsupportedEncodingException
   {
      int receivedRecordCount = responseBuffer.decodeInteger(responseBuffer.getNextField()).intValue();
      _FndClassCount += receivedRecordCount;
   }

   /**
    * Gets the Acquisition Fee Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Acquisition Fee Type or null.
    */
   public final String getAcqFeeType( int index )
   {
      return _AcqFeeType[index];
   }
    
   /**
    * Gets the Acquisition Fee Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Acquisition Fee Type or the specified default value.
    */
   public final String getAcqFeeType( int index, String defaultValue )
   {
      return _AcqFeeType[index] == null ? defaultValue : _AcqFeeType[index];
   }
    
   /**
    * Gets the array of Acquisition Fee Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Acquisition Fee Type values.
    */
   public final String[] getAcqFeeTypeArray()
   {
      return _AcqFeeType;
   }
    
   /**
    * Gets the Acquisition Fee Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Acquisition Fee Rate or null.
    */
   public final String getAcqRate( int index )
   {
      return _AcqRate[index];
   }
    
   /**
    * Gets the Acquisition Fee Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Acquisition Fee Rate or the specified default value.
    */
   public final String getAcqRate( int index, String defaultValue )
   {
      return _AcqRate[index] == null ? defaultValue : _AcqRate[index];
   }
    
   /**
    * Gets the array of Acquisition Fee Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Acquisition Fee Rate values.
    */
   public final String[] getAcqRateArray()
   {
      return _AcqRate;
   }
    
   /**
    * Gets the Redemption Fee Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Redemption Fee Type or null.
    */
   public final String getRedemFeeType( int index )
   {
      return _RedemFeeType[index];
   }
    
   /**
    * Gets the Redemption Fee Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Redemption Fee Type or the specified default value.
    */
   public final String getRedemFeeType( int index, String defaultValue )
   {
      return _RedemFeeType[index] == null ? defaultValue : _RedemFeeType[index];
   }
    
   /**
    * Gets the array of Redemption Fee Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Redemption Fee Type values.
    */
   public final String[] getRedemFeeTypeArray()
   {
      return _RedemFeeType;
   }
    
   /**
    * Gets the Redemption Fee Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Redemption Fee Rate or null.
    */
   public final String getRedemFee( int index )
   {
      return _RedemFee[index];
   }
    
   /**
    * Gets the Redemption Fee Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Redemption Fee Rate or the specified default value.
    */
   public final String getRedemFee( int index, String defaultValue )
   {
      return _RedemFee[index] == null ? defaultValue : _RedemFee[index];
   }
    
   /**
    * Gets the array of Redemption Fee Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Redemption Fee Rate values.
    */
   public final String[] getRedemFeeArray()
   {
      return _RedemFee;
   }
    
   /**
    * Gets the Redemption Fee Currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Redemption Fee Currency or null.
    */
   public final String getRedemFeeCurrency( int index )
   {
      return _RedemFeeCurrency[index];
   }
    
   /**
    * Gets the Redemption Fee Currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Redemption Fee Currency or the specified default value.
    */
   public final String getRedemFeeCurrency( int index, String defaultValue )
   {
      return _RedemFeeCurrency[index] == null ? defaultValue : _RedemFeeCurrency[index];
   }
    
   /**
    * Gets the array of Redemption Fee Currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Redemption Fee Currency values.
    */
   public final String[] getRedemFeeCurrencyArray()
   {
      return _RedemFeeCurrency;
   }
    
   /**
    * Gets the Load Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Load Type or null.
    */
   public final String getLoadType( int index )
   {
      return _LoadType[index];
   }
    
   /**
    * Gets the Load Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Load Type or the specified default value.
    */
   public final String getLoadType( int index, String defaultValue )
   {
      return _LoadType[index] == null ? defaultValue : _LoadType[index];
   }
    
   /**
    * Gets the array of Load Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Load Type values.
    */
   public final String[] getLoadTypeArray()
   {
      return _LoadType;
   }
    
   /**
    * Gets the Fund Currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Currency or null.
    */
   public final String getFundCurrency( int index )
   {
      return _FundCurrency[index];
   }
    
   /**
    * Gets the Fund Currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Currency or the specified default value.
    */
   public final String getFundCurrency( int index, String defaultValue )
   {
      return _FundCurrency[index] == null ? defaultValue : _FundCurrency[index];
   }
    
   /**
    * Gets the array of Fund Currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Currency values.
    */
   public final String[] getFundCurrencyArray()
   {
      return _FundCurrency;
   }
    
   /**
    * Gets the Class Index field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Class Index or null.
    */
   public final Integer getClassIndex( int index )
   {
      return _ClassIndex[index];
   }
    
   /**
    * Gets the Class Index field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class Index or the specified default value.
    */
   public final int getClassIndex( int index, int defaultValue )
   {
      return _ClassIndex[index] == null ? defaultValue : _ClassIndex[index].intValue();
   }
    
   /**
    * Gets the array of Class Index fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Class Index values.
    */
   public final Integer[] getClassIndexArray()
   {
      return _ClassIndex;
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
    * Gets the Exchange Allowed field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Exchange Allowed or null.
    */
   public final Boolean getExchangeAllowed( int index )
   {
      return _ExchangeAllowed[index];
   }
    
   /**
    * Gets the Exchange Allowed field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Exchange Allowed or the specified default value.
    */
   public final boolean getExchangeAllowed( int index, boolean defaultValue )
   {
      return _ExchangeAllowed[index] == null ? defaultValue : _ExchangeAllowed[index].booleanValue();
   }
    
   /**
    * Gets the array of Exchange Allowed fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Exchange Allowed values.
    */
   public final Boolean[] getExchangeAllowedArray()
   {
      return _ExchangeAllowed;
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
      int oldFundCount = _FundCount;
      decodeFundCount( responseBuffer );
      
      _FundCode = resizeArray( _FundCode, _FundCount );
      _FundType = resizeArray( _FundType, _FundCount );
      _PriceAtClass = resizeArray( _PriceAtClass, _FundCount );
      _EffectiveDate = resizeArray( _EffectiveDate, _FundCount );
      _StopDate = resizeArray( _StopDate, _FundCount );
      _ClassStartIdx = resizeArray( _ClassStartIdx, _FundCount );
      _ClassEndIdx = resizeArray( _ClassEndIdx, _FundCount );
      _EShortName = resizeArray( _EShortName, _FundCount );
      _OthShortName = resizeArray( _OthShortName, _FundCount );
        
      for (int x = oldFundCount ; x < _FundCount; x++)
      {
         _FundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PriceAtClass[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _StopDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ClassStartIdx[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ClassEndIdx[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _EShortName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _OthShortName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      
      // multi-record section
      int oldFndClassCount = _FndClassCount;
      decodeFndClassCount( responseBuffer );
      
      _AcqFeeType = resizeArray( _AcqFeeType, _FndClassCount );
      _AcqRate = resizeArray( _AcqRate, _FndClassCount );
      _RedemFeeType = resizeArray( _RedemFeeType, _FndClassCount );
      _RedemFee = resizeArray( _RedemFee, _FndClassCount );
      _RedemFeeCurrency = resizeArray( _RedemFeeCurrency, _FndClassCount );
      _LoadType = resizeArray( _LoadType, _FndClassCount );
      _FundCurrency = resizeArray( _FundCurrency, _FndClassCount );
      _ClassIndex = resizeArray( _ClassIndex, _FndClassCount );
      _ClassCode = resizeArray( _ClassCode, _FndClassCount );
      _ExchangeAllowed = resizeArray( _ExchangeAllowed, _FndClassCount );
        
      for (int x = oldFndClassCount ; x < _FndClassCount; x++)
      {
         _AcqFeeType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcqRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RedemFeeType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RedemFee[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RedemFeeCurrency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LoadType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundCurrency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClassIndex[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ExchangeAllowed[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      }
      

   }

}
      
