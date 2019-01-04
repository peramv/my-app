
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Fee Model Setup Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/FeeModSetInq.doc">FeeModSetInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class FeeModSetInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Fee Model Type member array.
    */
   private String[] _FeeModelType = null;
   
   /**
    * Holding Entity Applicable flag member array.
    */
   private Boolean[] _HoldingEntityAppl = null;
   
   /**
    * Calculation Currency Applicable flag member array.
    */
   private Boolean[] _CalcCurrencyAppl = null;
   
   /**
    * Fund GroupType member array.
    */
   private String[] _FundGrpType = null;
   
   /**
    * Fund Group Type List member array.
    */
   private String[] _FundGrpTypeList = null;
   
   /**
    * Aggregation Method List member array.
    */
   private String[] _AggrMethodList = null;
   
   /**
    * Calculation Rate Type List member array.
    */
   private String[] _CalcRateTypeList = null;
   
   /**
    * FeeModelOptionList member array.
    */
   private String[] _FeeModelOptionList = null;
   
   /**
    * Schedule Setup Frequency applicable flag member array.
    */
   private Boolean[] _SchedSetupFreqAppl = null;
   
   /**
    * PrefixCode member array.
    */
   private String[] _PrefixCode = null;
   
   /**
    * AutoGenOverride member array.
    */
   private Boolean[] _AutoGenOverride = null;
   

   /**
    * Constructs the FeeModSetInqView object.
    * 
    */
   public FeeModSetInqView()
   {
      super ( new FeeModSetInqRequest() );
   }

   /**
    * Constructs the FeeModSetInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public FeeModSetInqView( String hostEncoding )
   {
      super ( new FeeModSetInqRequest( hostEncoding ) );
   }

   /**
    * Gets the FeeModSetInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The FeeModSetInqRequest object.
    */
   public final FeeModSetInqRequest getRequest()
   {
      return (FeeModSetInqRequest)getIFastRequest();
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
    * Gets the Fee Model Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fee Model Type or null.
    */
   public final String getFeeModelType( int index )
   {
      return _FeeModelType[index];
   }
    
   /**
    * Gets the Fee Model Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee Model Type or the specified default value.
    */
   public final String getFeeModelType( int index, String defaultValue )
   {
      return _FeeModelType[index] == null ? defaultValue : _FeeModelType[index];
   }
    
   /**
    * Gets the array of Fee Model Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee Model Type values.
    */
   public final String[] getFeeModelTypeArray()
   {
      return _FeeModelType;
   }
    
   /**
    * Gets the Holding Entity Applicable flag field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Holding Entity Applicable flag or null.
    */
   public final Boolean getHoldingEntityAppl( int index )
   {
      return _HoldingEntityAppl[index];
   }
    
   /**
    * Gets the Holding Entity Applicable flag field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Holding Entity Applicable flag or the specified default value.
    */
   public final boolean getHoldingEntityAppl( int index, boolean defaultValue )
   {
      return _HoldingEntityAppl[index] == null ? defaultValue : _HoldingEntityAppl[index].booleanValue();
   }
    
   /**
    * Gets the array of Holding Entity Applicable flag fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Holding Entity Applicable flag values.
    */
   public final Boolean[] getHoldingEntityApplArray()
   {
      return _HoldingEntityAppl;
   }
    
   /**
    * Gets the Calculation Currency Applicable flag field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Calculation Currency Applicable flag or null.
    */
   public final Boolean getCalcCurrencyAppl( int index )
   {
      return _CalcCurrencyAppl[index];
   }
    
   /**
    * Gets the Calculation Currency Applicable flag field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Calculation Currency Applicable flag or the specified default value.
    */
   public final boolean getCalcCurrencyAppl( int index, boolean defaultValue )
   {
      return _CalcCurrencyAppl[index] == null ? defaultValue : _CalcCurrencyAppl[index].booleanValue();
   }
    
   /**
    * Gets the array of Calculation Currency Applicable flag fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Calculation Currency Applicable flag values.
    */
   public final Boolean[] getCalcCurrencyApplArray()
   {
      return _CalcCurrencyAppl;
   }
    
   /**
    * Gets the Fund GroupType field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund GroupType or null.
    */
   public final String getFundGrpType( int index )
   {
      return _FundGrpType[index];
   }
    
   /**
    * Gets the Fund GroupType field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund GroupType or the specified default value.
    */
   public final String getFundGrpType( int index, String defaultValue )
   {
      return _FundGrpType[index] == null ? defaultValue : _FundGrpType[index];
   }
    
   /**
    * Gets the array of Fund GroupType fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund GroupType values.
    */
   public final String[] getFundGrpTypeArray()
   {
      return _FundGrpType;
   }
    
   /**
    * Gets the Fund Group Type List field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Group Type List or null.
    */
   public final String getFundGrpTypeList( int index )
   {
      return _FundGrpTypeList[index];
   }
    
   /**
    * Gets the Fund Group Type List field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Group Type List or the specified default value.
    */
   public final String getFundGrpTypeList( int index, String defaultValue )
   {
      return _FundGrpTypeList[index] == null ? defaultValue : _FundGrpTypeList[index];
   }
    
   /**
    * Gets the array of Fund Group Type List fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Group Type List values.
    */
   public final String[] getFundGrpTypeListArray()
   {
      return _FundGrpTypeList;
   }
    
   /**
    * Gets the Aggregation Method List field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Aggregation Method List or null.
    */
   public final String getAggrMethodList( int index )
   {
      return _AggrMethodList[index];
   }
    
   /**
    * Gets the Aggregation Method List field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Aggregation Method List or the specified default value.
    */
   public final String getAggrMethodList( int index, String defaultValue )
   {
      return _AggrMethodList[index] == null ? defaultValue : _AggrMethodList[index];
   }
    
   /**
    * Gets the array of Aggregation Method List fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Aggregation Method List values.
    */
   public final String[] getAggrMethodListArray()
   {
      return _AggrMethodList;
   }
    
   /**
    * Gets the Calculation Rate Type List field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Calculation Rate Type List or null.
    */
   public final String getCalcRateTypeList( int index )
   {
      return _CalcRateTypeList[index];
   }
    
   /**
    * Gets the Calculation Rate Type List field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Calculation Rate Type List or the specified default value.
    */
   public final String getCalcRateTypeList( int index, String defaultValue )
   {
      return _CalcRateTypeList[index] == null ? defaultValue : _CalcRateTypeList[index];
   }
    
   /**
    * Gets the array of Calculation Rate Type List fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Calculation Rate Type List values.
    */
   public final String[] getCalcRateTypeListArray()
   {
      return _CalcRateTypeList;
   }
    
   /**
    * Gets the FeeModelOptionList field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FeeModelOptionList or null.
    */
   public final String getFeeModelOptionList( int index )
   {
      return _FeeModelOptionList[index];
   }
    
   /**
    * Gets the FeeModelOptionList field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FeeModelOptionList or the specified default value.
    */
   public final String getFeeModelOptionList( int index, String defaultValue )
   {
      return _FeeModelOptionList[index] == null ? defaultValue : _FeeModelOptionList[index];
   }
    
   /**
    * Gets the array of FeeModelOptionList fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FeeModelOptionList values.
    */
   public final String[] getFeeModelOptionListArray()
   {
      return _FeeModelOptionList;
   }
    
   /**
    * Gets the Schedule Setup Frequency applicable flag field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Schedule Setup Frequency applicable flag or null.
    */
   public final Boolean getSchedSetupFreqAppl( int index )
   {
      return _SchedSetupFreqAppl[index];
   }
    
   /**
    * Gets the Schedule Setup Frequency applicable flag field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Schedule Setup Frequency applicable flag or the specified default value.
    */
   public final boolean getSchedSetupFreqAppl( int index, boolean defaultValue )
   {
      return _SchedSetupFreqAppl[index] == null ? defaultValue : _SchedSetupFreqAppl[index].booleanValue();
   }
    
   /**
    * Gets the array of Schedule Setup Frequency applicable flag fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Schedule Setup Frequency applicable flag values.
    */
   public final Boolean[] getSchedSetupFreqApplArray()
   {
      return _SchedSetupFreqAppl;
   }
    
   /**
    * Gets the PrefixCode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the PrefixCode or null.
    */
   public final String getPrefixCode( int index )
   {
      return _PrefixCode[index];
   }
    
   /**
    * Gets the PrefixCode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PrefixCode or the specified default value.
    */
   public final String getPrefixCode( int index, String defaultValue )
   {
      return _PrefixCode[index] == null ? defaultValue : _PrefixCode[index];
   }
    
   /**
    * Gets the array of PrefixCode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of PrefixCode values.
    */
   public final String[] getPrefixCodeArray()
   {
      return _PrefixCode;
   }
    
   /**
    * Gets the AutoGenOverride field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AutoGenOverride or null.
    */
   public final Boolean getAutoGenOverride( int index )
   {
      return _AutoGenOverride[index];
   }
    
   /**
    * Gets the AutoGenOverride field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AutoGenOverride or the specified default value.
    */
   public final boolean getAutoGenOverride( int index, boolean defaultValue )
   {
      return _AutoGenOverride[index] == null ? defaultValue : _AutoGenOverride[index].booleanValue();
   }
    
   /**
    * Gets the array of AutoGenOverride fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AutoGenOverride values.
    */
   public final Boolean[] getAutoGenOverrideArray()
   {
      return _AutoGenOverride;
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
      
      _FeeModelType = resizeArray( _FeeModelType, _RepeatCount );
      _HoldingEntityAppl = resizeArray( _HoldingEntityAppl, _RepeatCount );
      _CalcCurrencyAppl = resizeArray( _CalcCurrencyAppl, _RepeatCount );
      _FundGrpType = resizeArray( _FundGrpType, _RepeatCount );
      _FundGrpTypeList = resizeArray( _FundGrpTypeList, _RepeatCount );
      _AggrMethodList = resizeArray( _AggrMethodList, _RepeatCount );
      _CalcRateTypeList = resizeArray( _CalcRateTypeList, _RepeatCount );
      _FeeModelOptionList = resizeArray( _FeeModelOptionList, _RepeatCount );
      _SchedSetupFreqAppl = resizeArray( _SchedSetupFreqAppl, _RepeatCount );
      _PrefixCode = resizeArray( _PrefixCode, _RepeatCount );
      _AutoGenOverride = resizeArray( _AutoGenOverride, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _FeeModelType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _HoldingEntityAppl[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _CalcCurrencyAppl[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FundGrpType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundGrpTypeList[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AggrMethodList[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CalcRateTypeList[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FeeModelOptionList[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SchedSetupFreqAppl[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _PrefixCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AutoGenOverride[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      }
      

   }

}
      
