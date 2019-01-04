
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Default Split Commissions view.
 * For additional view information see <A HREF="../../../../viewspecs/DefaultSpltComm.doc">DefaultSpltComm.doc</A>.
 * 
 * @author RTS Generated
 */
public class DefaultSpltCommView extends IFastView implements Serializable
{

   /**
    * IFee member variable.
    */
   private String _IFee = null;
   
   /**
    * Maximum Fee Rate member variable.
    */
   private String _MaxFeeRate = null;
   
   private int _RepeatCount = 0;
   
   /**
    * Commission Level member array.
    */
   private Integer[] _CommLevel = null;
   
   /**
    * Description of CommLevel member array.
    */
   private String[] _CommLevelDesc = null;
   
   /**
    * Commission Entity Code member array.
    */
   private String[] _CommEntCode = null;
   
   /**
    * Commission Amount member array.
    */
   private String[] _CommAmount = null;
   
   /**
    * Currency member array.
    */
   private String[] _Currency = null;
   
   /**
    * PayType member array.
    */
   private String[] _PayType = null;
   
   /**
    * Fixed member array.
    */
   private Boolean[] _Fixed = null;
   
   /**
    * Gross or Net member array.
    */
   private Boolean[] _GrossNet = null;
   
   /**
    * Commission Percent member array.
    */
   private String[] _CommPrcnt = null;
   
   /**
    * Broker Code member array.
    */
   private String[] _BrokerCode = null;
   
   /**
    * Branch Code member array.
    */
   private String[] _BranchCode = null;
   
   /**
    * Sales Rep Code member array.
    */
   private String[] _SlsRepCode = null;
   
   /**
    * Commission Entity Name member array.
    */
   private String[] _CommEntName = null;
   
   /**
    * Commission Broker Name member array.
    */
   private String[] _CommBrokName = null;
   
   /**
    * Commission Branch Name member array.
    */
   private String[] _CommBranName = null;
   
   /**
    * Commission Rate member array.
    */
   private String[] _CommRate = null;
   
   /**
    * Commission Entity Type member array.
    */
   private String[] _CommEntType = null;
   

   /**
    * Constructs the DefaultSpltCommView object.
    * 
    */
   public DefaultSpltCommView()
   {
      super ( new DefaultSpltCommRequest() );
   }

   /**
    * Constructs the DefaultSpltCommView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public DefaultSpltCommView( String hostEncoding )
   {
      super ( new DefaultSpltCommRequest( hostEncoding ) );
   }

   /**
    * Gets the DefaultSpltCommRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The DefaultSpltCommRequest object.
    */
   public final DefaultSpltCommRequest getRequest()
   {
      return (DefaultSpltCommRequest)getIFastRequest();
   }
        
   /**
    * Gets the IFee field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the IFee or null.
    */
   public final String getIFee()
   {
      return _IFee;
   }
	
   /**
    * Gets the IFee field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the IFee or the specified default value.
    */
   public final String getIFee( String defaultValue )
   {
      return _IFee == null ? defaultValue : _IFee;
   }
                  
   /**
    * Gets the Maximum Fee Rate field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Maximum Fee Rate or null.
    */
   public final String getMaxFeeRate()
   {
      return _MaxFeeRate;
   }
	
   /**
    * Gets the Maximum Fee Rate field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Maximum Fee Rate or the specified default value.
    */
   public final String getMaxFeeRate( String defaultValue )
   {
      return _MaxFeeRate == null ? defaultValue : _MaxFeeRate;
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
    * Gets the Commission Level field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Commission Level or null.
    */
   public final Integer getCommLevel( int index )
   {
      return _CommLevel[index];
   }
    
   /**
    * Gets the Commission Level field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commission Level or the specified default value.
    */
   public final int getCommLevel( int index, int defaultValue )
   {
      return _CommLevel[index] == null ? defaultValue : _CommLevel[index].intValue();
   }
    
   /**
    * Gets the array of Commission Level fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Commission Level values.
    */
   public final Integer[] getCommLevelArray()
   {
      return _CommLevel;
   }
    
   /**
    * Gets the Description of CommLevel field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Description of CommLevel or null.
    */
   public final String getCommLevelDesc( int index )
   {
      return _CommLevelDesc[index];
   }
    
   /**
    * Gets the Description of CommLevel field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Description of CommLevel or the specified default value.
    */
   public final String getCommLevelDesc( int index, String defaultValue )
   {
      return _CommLevelDesc[index] == null ? defaultValue : _CommLevelDesc[index];
   }
    
   /**
    * Gets the array of Description of CommLevel fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Description of CommLevel values.
    */
   public final String[] getCommLevelDescArray()
   {
      return _CommLevelDesc;
   }
    
   /**
    * Gets the Commission Entity Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Commission Entity Code or null.
    */
   public final String getCommEntCode( int index )
   {
      return _CommEntCode[index];
   }
    
   /**
    * Gets the Commission Entity Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commission Entity Code or the specified default value.
    */
   public final String getCommEntCode( int index, String defaultValue )
   {
      return _CommEntCode[index] == null ? defaultValue : _CommEntCode[index];
   }
    
   /**
    * Gets the array of Commission Entity Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Commission Entity Code values.
    */
   public final String[] getCommEntCodeArray()
   {
      return _CommEntCode;
   }
    
   /**
    * Gets the Commission Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Commission Amount or null.
    */
   public final String getCommAmount( int index )
   {
      return _CommAmount[index];
   }
    
   /**
    * Gets the Commission Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commission Amount or the specified default value.
    */
   public final String getCommAmount( int index, String defaultValue )
   {
      return _CommAmount[index] == null ? defaultValue : _CommAmount[index];
   }
    
   /**
    * Gets the array of Commission Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Commission Amount values.
    */
   public final String[] getCommAmountArray()
   {
      return _CommAmount;
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
    * Gets the PayType field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the PayType or null.
    */
   public final String getPayType( int index )
   {
      return _PayType[index];
   }
    
   /**
    * Gets the PayType field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PayType or the specified default value.
    */
   public final String getPayType( int index, String defaultValue )
   {
      return _PayType[index] == null ? defaultValue : _PayType[index];
   }
    
   /**
    * Gets the array of PayType fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of PayType values.
    */
   public final String[] getPayTypeArray()
   {
      return _PayType;
   }
    
   /**
    * Gets the Fixed field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fixed or null.
    */
   public final Boolean getFixed( int index )
   {
      return _Fixed[index];
   }
    
   /**
    * Gets the Fixed field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fixed or the specified default value.
    */
   public final boolean getFixed( int index, boolean defaultValue )
   {
      return _Fixed[index] == null ? defaultValue : _Fixed[index].booleanValue();
   }
    
   /**
    * Gets the array of Fixed fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fixed values.
    */
   public final Boolean[] getFixedArray()
   {
      return _Fixed;
   }
    
   /**
    * Gets the Gross or Net field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Gross or Net or null.
    */
   public final Boolean getGrossNet( int index )
   {
      return _GrossNet[index];
   }
    
   /**
    * Gets the Gross or Net field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Gross or Net or the specified default value.
    */
   public final boolean getGrossNet( int index, boolean defaultValue )
   {
      return _GrossNet[index] == null ? defaultValue : _GrossNet[index].booleanValue();
   }
    
   /**
    * Gets the array of Gross or Net fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Gross or Net values.
    */
   public final Boolean[] getGrossNetArray()
   {
      return _GrossNet;
   }
    
   /**
    * Gets the Commission Percent field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Commission Percent or null.
    */
   public final String getCommPrcnt( int index )
   {
      return _CommPrcnt[index];
   }
    
   /**
    * Gets the Commission Percent field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commission Percent or the specified default value.
    */
   public final String getCommPrcnt( int index, String defaultValue )
   {
      return _CommPrcnt[index] == null ? defaultValue : _CommPrcnt[index];
   }
    
   /**
    * Gets the array of Commission Percent fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Commission Percent values.
    */
   public final String[] getCommPrcntArray()
   {
      return _CommPrcnt;
   }
    
   /**
    * Gets the Broker Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Broker Code or null.
    */
   public final String getBrokerCode( int index )
   {
      return _BrokerCode[index];
   }
    
   /**
    * Gets the Broker Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker Code or the specified default value.
    */
   public final String getBrokerCode( int index, String defaultValue )
   {
      return _BrokerCode[index] == null ? defaultValue : _BrokerCode[index];
   }
    
   /**
    * Gets the array of Broker Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Broker Code values.
    */
   public final String[] getBrokerCodeArray()
   {
      return _BrokerCode;
   }
    
   /**
    * Gets the Branch Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Branch Code or null.
    */
   public final String getBranchCode( int index )
   {
      return _BranchCode[index];
   }
    
   /**
    * Gets the Branch Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Branch Code or the specified default value.
    */
   public final String getBranchCode( int index, String defaultValue )
   {
      return _BranchCode[index] == null ? defaultValue : _BranchCode[index];
   }
    
   /**
    * Gets the array of Branch Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Branch Code values.
    */
   public final String[] getBranchCodeArray()
   {
      return _BranchCode;
   }
    
   /**
    * Gets the Sales Rep Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Sales Rep Code or null.
    */
   public final String getSlsRepCode( int index )
   {
      return _SlsRepCode[index];
   }
    
   /**
    * Gets the Sales Rep Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Sales Rep Code or the specified default value.
    */
   public final String getSlsRepCode( int index, String defaultValue )
   {
      return _SlsRepCode[index] == null ? defaultValue : _SlsRepCode[index];
   }
    
   /**
    * Gets the array of Sales Rep Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Sales Rep Code values.
    */
   public final String[] getSlsRepCodeArray()
   {
      return _SlsRepCode;
   }
    
   /**
    * Gets the Commission Entity Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Commission Entity Name or null.
    */
   public final String getCommEntName( int index )
   {
      return _CommEntName[index];
   }
    
   /**
    * Gets the Commission Entity Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commission Entity Name or the specified default value.
    */
   public final String getCommEntName( int index, String defaultValue )
   {
      return _CommEntName[index] == null ? defaultValue : _CommEntName[index];
   }
    
   /**
    * Gets the array of Commission Entity Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Commission Entity Name values.
    */
   public final String[] getCommEntNameArray()
   {
      return _CommEntName;
   }
    
   /**
    * Gets the Commission Broker Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Commission Broker Name or null.
    */
   public final String getCommBrokName( int index )
   {
      return _CommBrokName[index];
   }
    
   /**
    * Gets the Commission Broker Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commission Broker Name or the specified default value.
    */
   public final String getCommBrokName( int index, String defaultValue )
   {
      return _CommBrokName[index] == null ? defaultValue : _CommBrokName[index];
   }
    
   /**
    * Gets the array of Commission Broker Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Commission Broker Name values.
    */
   public final String[] getCommBrokNameArray()
   {
      return _CommBrokName;
   }
    
   /**
    * Gets the Commission Branch Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Commission Branch Name or null.
    */
   public final String getCommBranName( int index )
   {
      return _CommBranName[index];
   }
    
   /**
    * Gets the Commission Branch Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commission Branch Name or the specified default value.
    */
   public final String getCommBranName( int index, String defaultValue )
   {
      return _CommBranName[index] == null ? defaultValue : _CommBranName[index];
   }
    
   /**
    * Gets the array of Commission Branch Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Commission Branch Name values.
    */
   public final String[] getCommBranNameArray()
   {
      return _CommBranName;
   }
    
   /**
    * Gets the Commission Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Commission Rate or null.
    */
   public final String getCommRate( int index )
   {
      return _CommRate[index];
   }
    
   /**
    * Gets the Commission Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commission Rate or the specified default value.
    */
   public final String getCommRate( int index, String defaultValue )
   {
      return _CommRate[index] == null ? defaultValue : _CommRate[index];
   }
    
   /**
    * Gets the array of Commission Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Commission Rate values.
    */
   public final String[] getCommRateArray()
   {
      return _CommRate;
   }
    
   /**
    * Gets the Commission Entity Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Commission Entity Type or null.
    */
   public final String getCommEntType( int index )
   {
      return _CommEntType[index];
   }
    
   /**
    * Gets the Commission Entity Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commission Entity Type or the specified default value.
    */
   public final String getCommEntType( int index, String defaultValue )
   {
      return _CommEntType[index] == null ? defaultValue : _CommEntType[index];
   }
    
   /**
    * Gets the array of Commission Entity Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Commission Entity Type values.
    */
   public final String[] getCommEntTypeArray()
   {
      return _CommEntType;
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
      _IFee = responseBuffer.decodeString(responseBuffer.getNextField());
      _MaxFeeRate = responseBuffer.decodeString(responseBuffer.getNextField());
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _CommLevel = resizeArray( _CommLevel, _RepeatCount );
      _CommLevelDesc = resizeArray( _CommLevelDesc, _RepeatCount );
      _CommEntCode = resizeArray( _CommEntCode, _RepeatCount );
      _CommAmount = resizeArray( _CommAmount, _RepeatCount );
      _Currency = resizeArray( _Currency, _RepeatCount );
      _PayType = resizeArray( _PayType, _RepeatCount );
      _Fixed = resizeArray( _Fixed, _RepeatCount );
      _GrossNet = resizeArray( _GrossNet, _RepeatCount );
      _CommPrcnt = resizeArray( _CommPrcnt, _RepeatCount );
      _BrokerCode = resizeArray( _BrokerCode, _RepeatCount );
      _BranchCode = resizeArray( _BranchCode, _RepeatCount );
      _SlsRepCode = resizeArray( _SlsRepCode, _RepeatCount );
      _CommEntName = resizeArray( _CommEntName, _RepeatCount );
      _CommBrokName = resizeArray( _CommBrokName, _RepeatCount );
      _CommBranName = resizeArray( _CommBranName, _RepeatCount );
      _CommRate = resizeArray( _CommRate, _RepeatCount );
      _CommEntType = resizeArray( _CommEntType, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _CommLevel[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _CommLevelDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CommEntCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CommAmount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Currency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PayType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Fixed[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _GrossNet[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _CommPrcnt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BrokerCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BranchCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SlsRepCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CommEntName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CommBrokName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CommBranName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CommRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CommEntType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
