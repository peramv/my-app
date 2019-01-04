
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Shareholder summary information view.
 * For additional view information see <A HREF="../../../../viewspecs/ShareholderSummary.doc">ShareholderSummary.doc</A>.
 * 
 * @author RTS Generated
 */
public class ShareholderSummaryView extends IFastView implements Serializable
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
    * Valuation Date member array.
    */
   private Date[] _ValueAsAt = null;
   
   /**
    * Currency member array.
    */
   private String[] _Currency = null;
   
   /**
    * Unit Price member array.
    */
   private String[] _UnitValue = null;
   
   /**
    * Total Units in fund member array.
    */
   private String[] _FundUnits = null;
   
   /**
    * Percentage of product in fund member array.
    */
   private String[] _FundPercent = null;
   
   /**
    * Total amount in fund member array.
    */
   private String[] _FundAmount = null;
   
   /**
    * Product ( tax Type) member array.
    */
   private String[] _TaxType = null;
   
   /**
    * Product ( tax type) desc member array.
    */
   private String[] _TaxTypeDesc = null;
   
   /**
    * Percentage of portfolio in product member array.
    */
   private String[] _ProductPercent = null;
   
   /**
    * Total amount in product member array.
    */
   private String[] _ProductAmount = null;
   
   /**
    * Shareholder balance member array.
    */
   private String[] _ShrBalance = null;
   

   /**
    * Constructs the ShareholderSummaryView object.
    * 
    */
   public ShareholderSummaryView()
   {
      super ( new ShareholderSummaryRequest() );
   }

   /**
    * Constructs the ShareholderSummaryView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public ShareholderSummaryView( String hostEncoding )
   {
      super ( new ShareholderSummaryRequest( hostEncoding ) );
   }

   /**
    * Gets the ShareholderSummaryRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The ShareholderSummaryRequest object.
    */
   public final ShareholderSummaryRequest getRequest()
   {
      return (ShareholderSummaryRequest)getIFastRequest();
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
    * Gets the Valuation Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Valuation Date or null.
    */
   public final Date getValueAsAt( int index )
   {
      return _ValueAsAt[index];
   }
    
   /**
    * Gets the Valuation Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Valuation Date or the specified default value.
    */
   public final Date getValueAsAt( int index, Date defaultValue )
   {
      return _ValueAsAt[index] == null ? defaultValue : _ValueAsAt[index];
   }
    
   /**
    * Gets the array of Valuation Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Valuation Date values.
    */
   public final Date[] getValueAsAtArray()
   {
      return _ValueAsAt;
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
    * Gets the Unit Price field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Unit Price or null.
    */
   public final String getUnitValue( int index )
   {
      return _UnitValue[index];
   }
    
   /**
    * Gets the Unit Price field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Unit Price or the specified default value.
    */
   public final String getUnitValue( int index, String defaultValue )
   {
      return _UnitValue[index] == null ? defaultValue : _UnitValue[index];
   }
    
   /**
    * Gets the array of Unit Price fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Unit Price values.
    */
   public final String[] getUnitValueArray()
   {
      return _UnitValue;
   }
    
   /**
    * Gets the Total Units in fund field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Total Units in fund or null.
    */
   public final String getFundUnits( int index )
   {
      return _FundUnits[index];
   }
    
   /**
    * Gets the Total Units in fund field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Total Units in fund or the specified default value.
    */
   public final String getFundUnits( int index, String defaultValue )
   {
      return _FundUnits[index] == null ? defaultValue : _FundUnits[index];
   }
    
   /**
    * Gets the array of Total Units in fund fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Total Units in fund values.
    */
   public final String[] getFundUnitsArray()
   {
      return _FundUnits;
   }
    
   /**
    * Gets the Percentage of product in fund field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Percentage of product in fund or null.
    */
   public final String getFundPercent( int index )
   {
      return _FundPercent[index];
   }
    
   /**
    * Gets the Percentage of product in fund field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Percentage of product in fund or the specified default value.
    */
   public final String getFundPercent( int index, String defaultValue )
   {
      return _FundPercent[index] == null ? defaultValue : _FundPercent[index];
   }
    
   /**
    * Gets the array of Percentage of product in fund fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Percentage of product in fund values.
    */
   public final String[] getFundPercentArray()
   {
      return _FundPercent;
   }
    
   /**
    * Gets the Total amount in fund field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Total amount in fund or null.
    */
   public final String getFundAmount( int index )
   {
      return _FundAmount[index];
   }
    
   /**
    * Gets the Total amount in fund field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Total amount in fund or the specified default value.
    */
   public final String getFundAmount( int index, String defaultValue )
   {
      return _FundAmount[index] == null ? defaultValue : _FundAmount[index];
   }
    
   /**
    * Gets the array of Total amount in fund fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Total amount in fund values.
    */
   public final String[] getFundAmountArray()
   {
      return _FundAmount;
   }
    
   /**
    * Gets the Product ( tax Type) field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Product ( tax Type) or null.
    */
   public final String getTaxType( int index )
   {
      return _TaxType[index];
   }
    
   /**
    * Gets the Product ( tax Type) field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Product ( tax Type) or the specified default value.
    */
   public final String getTaxType( int index, String defaultValue )
   {
      return _TaxType[index] == null ? defaultValue : _TaxType[index];
   }
    
   /**
    * Gets the array of Product ( tax Type) fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Product ( tax Type) values.
    */
   public final String[] getTaxTypeArray()
   {
      return _TaxType;
   }
    
   /**
    * Gets the Product ( tax type) desc field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Product ( tax type) desc or null.
    */
   public final String getTaxTypeDesc( int index )
   {
      return _TaxTypeDesc[index];
   }
    
   /**
    * Gets the Product ( tax type) desc field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Product ( tax type) desc or the specified default value.
    */
   public final String getTaxTypeDesc( int index, String defaultValue )
   {
      return _TaxTypeDesc[index] == null ? defaultValue : _TaxTypeDesc[index];
   }
    
   /**
    * Gets the array of Product ( tax type) desc fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Product ( tax type) desc values.
    */
   public final String[] getTaxTypeDescArray()
   {
      return _TaxTypeDesc;
   }
    
   /**
    * Gets the Percentage of portfolio in product field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Percentage of portfolio in product or null.
    */
   public final String getProductPercent( int index )
   {
      return _ProductPercent[index];
   }
    
   /**
    * Gets the Percentage of portfolio in product field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Percentage of portfolio in product or the specified default value.
    */
   public final String getProductPercent( int index, String defaultValue )
   {
      return _ProductPercent[index] == null ? defaultValue : _ProductPercent[index];
   }
    
   /**
    * Gets the array of Percentage of portfolio in product fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Percentage of portfolio in product values.
    */
   public final String[] getProductPercentArray()
   {
      return _ProductPercent;
   }
    
   /**
    * Gets the Total amount in product field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Total amount in product or null.
    */
   public final String getProductAmount( int index )
   {
      return _ProductAmount[index];
   }
    
   /**
    * Gets the Total amount in product field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Total amount in product or the specified default value.
    */
   public final String getProductAmount( int index, String defaultValue )
   {
      return _ProductAmount[index] == null ? defaultValue : _ProductAmount[index];
   }
    
   /**
    * Gets the array of Total amount in product fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Total amount in product values.
    */
   public final String[] getProductAmountArray()
   {
      return _ProductAmount;
   }
    
   /**
    * Gets the Shareholder balance field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Shareholder balance or null.
    */
   public final String getShrBalance( int index )
   {
      return _ShrBalance[index];
   }
    
   /**
    * Gets the Shareholder balance field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Shareholder balance or the specified default value.
    */
   public final String getShrBalance( int index, String defaultValue )
   {
      return _ShrBalance[index] == null ? defaultValue : _ShrBalance[index];
   }
    
   /**
    * Gets the array of Shareholder balance fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Shareholder balance values.
    */
   public final String[] getShrBalanceArray()
   {
      return _ShrBalance;
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
      _ValueAsAt = resizeArray( _ValueAsAt, _RepeatCount );
      _Currency = resizeArray( _Currency, _RepeatCount );
      _UnitValue = resizeArray( _UnitValue, _RepeatCount );
      _FundUnits = resizeArray( _FundUnits, _RepeatCount );
      _FundPercent = resizeArray( _FundPercent, _RepeatCount );
      _FundAmount = resizeArray( _FundAmount, _RepeatCount );
      _TaxType = resizeArray( _TaxType, _RepeatCount );
      _TaxTypeDesc = resizeArray( _TaxTypeDesc, _RepeatCount );
      _ProductPercent = resizeArray( _ProductPercent, _RepeatCount );
      _ProductAmount = resizeArray( _ProductAmount, _RepeatCount );
      _ShrBalance = resizeArray( _ShrBalance, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _FundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ValueAsAt[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _Currency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UnitValue[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundPercent[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundAmount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TaxType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TaxTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProductPercent[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProductAmount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ShrBalance[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
