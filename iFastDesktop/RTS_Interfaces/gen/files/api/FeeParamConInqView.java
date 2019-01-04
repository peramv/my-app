
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Fee Paramters Configuration Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/FeeParamConInq.doc">FeeParamConInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class FeeParamConInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Fee Code member array.
    */
   private Integer[] _FeeCode = null;
   
   /**
    * Indicate shareholder applicable to Fee member array.
    */
   private Boolean[] _ShGroupApplicable = null;
   
   /**
    * Broker Applicable member array.
    */
   private Boolean[] _BrokerApplicable = null;
   
   /**
    * Branch Applicable member array.
    */
   private Boolean[] _BranchApplicable = null;
   
   /**
    * Sales Rep Applicable member array.
    */
   private Boolean[] _SalesRepApplicable = null;
   
   /**
    * Fund Group Type member array.
    */
   private String[] _FundGroupType = null;
   
   /**
    * Fund Class Applicable member array.
    */
   private Boolean[] _FundClassApplicable = null;
   
   /**
    * FromFndClassApplicable member array.
    */
   private Boolean[] _FromFndClassApplicable = null;
   
   /**
    * FeeTypeList member array.
    */
   private String[] _FeeTypeList = null;
   
   /**
    * BasedOnList member array.
    */
   private String[] _BasedOnList = null;
   
   /**
    * HowPaidList member array.
    */
   private String[] _HowPaidList = null;
   
   /**
    * MinMaxFreqList member array.
    */
   private String[] _MinMaxFreqList = null;
   
   /**
    * Override List member array.
    */
   private String[] _OverrideList = null;
   
   /**
    * OnPWApplicable member array.
    */
   private Boolean[] _OnPWApplicable = null;
   
   /**
    * OnFWApplicable member array.
    */
   private Boolean[] _OnFWApplicable = null;
   
   /**
    * FeeSetupLevel member array.
    */
   private String[] _FeeSetupLevel = null;
   
   /**
    * FamilyCodeApplicable member array.
    */
   private Boolean[] _FamilyCodeApplicable = null;
   
   /**
    * Level member array.
    */
   private String[] _Level = null;
   
   /**
    * Trade Fee Type List member array.
    */
   private String[] _TradeFeeOptionList = null;
   
   /**
    * Charge Option List member array.
    */
   private String[] _ChargeOptionList = null;
   
   /**
    * Status member array.
    */
   private String[] _Stat = null;
   
   /**
    * Does Fee Exists member array.
    */
   private Boolean[] _FeeExists = null;
   
   /**
    * Does Fee Exists by Broker member array.
    */
   private Boolean[] _FeeExistsByBroker = null;
   
   /**
    * Does Fee Exists by Branch member array.
    */
   private Boolean[] _FeeExistsByBranch = null;
   
   /**
    * Does Fee Exists by Slsrep member array.
    */
   private Boolean[] _FeeExistsBySlsrep = null;
   
   /**
    * Does Fee Exists by Fund Com Grp member array.
    */
   private Boolean[] _FeeExistsByFundComGrp = null;
   
   /**
    * Applied Method List member array.
    */
   private String[] _AppliedMethodList = null;
   
   /**
    * FundList member array.
    */
   private String[] _FundList = null;
   
   /**
    * Indicates if Threshold Amount  applies member array.
    */
   private Boolean[] _ThresholdAmtApply = null;
   
   /**
    * UpdateRule member array.
    */
   private String[] _UpdateRule = null;
   
   /**
    * MaxRate member array.
    */
   private String[] _MaxRate = null;
   

   /**
    * Constructs the FeeParamConInqView object.
    * 
    */
   public FeeParamConInqView()
   {
      super ( new FeeParamConInqRequest() );
   }

   /**
    * Constructs the FeeParamConInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public FeeParamConInqView( String hostEncoding )
   {
      super ( new FeeParamConInqRequest( hostEncoding ) );
   }

   /**
    * Gets the FeeParamConInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The FeeParamConInqRequest object.
    */
   public final FeeParamConInqRequest getRequest()
   {
      return (FeeParamConInqRequest)getIFastRequest();
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
    * Gets the Fee Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fee Code or null.
    */
   public final Integer getFeeCode( int index )
   {
      return _FeeCode[index];
   }
    
   /**
    * Gets the Fee Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee Code or the specified default value.
    */
   public final int getFeeCode( int index, int defaultValue )
   {
      return _FeeCode[index] == null ? defaultValue : _FeeCode[index].intValue();
   }
    
   /**
    * Gets the array of Fee Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee Code values.
    */
   public final Integer[] getFeeCodeArray()
   {
      return _FeeCode;
   }
    
   /**
    * Gets the Indicate shareholder applicable to Fee field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Indicate shareholder applicable to Fee or null.
    */
   public final Boolean getShGroupApplicable( int index )
   {
      return _ShGroupApplicable[index];
   }
    
   /**
    * Gets the Indicate shareholder applicable to Fee field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Indicate shareholder applicable to Fee or the specified default value.
    */
   public final boolean getShGroupApplicable( int index, boolean defaultValue )
   {
      return _ShGroupApplicable[index] == null ? defaultValue : _ShGroupApplicable[index].booleanValue();
   }
    
   /**
    * Gets the array of Indicate shareholder applicable to Fee fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Indicate shareholder applicable to Fee values.
    */
   public final Boolean[] getShGroupApplicableArray()
   {
      return _ShGroupApplicable;
   }
    
   /**
    * Gets the Broker Applicable field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Broker Applicable or null.
    */
   public final Boolean getBrokerApplicable( int index )
   {
      return _BrokerApplicable[index];
   }
    
   /**
    * Gets the Broker Applicable field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker Applicable or the specified default value.
    */
   public final boolean getBrokerApplicable( int index, boolean defaultValue )
   {
      return _BrokerApplicable[index] == null ? defaultValue : _BrokerApplicable[index].booleanValue();
   }
    
   /**
    * Gets the array of Broker Applicable fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Broker Applicable values.
    */
   public final Boolean[] getBrokerApplicableArray()
   {
      return _BrokerApplicable;
   }
    
   /**
    * Gets the Branch Applicable field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Branch Applicable or null.
    */
   public final Boolean getBranchApplicable( int index )
   {
      return _BranchApplicable[index];
   }
    
   /**
    * Gets the Branch Applicable field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Branch Applicable or the specified default value.
    */
   public final boolean getBranchApplicable( int index, boolean defaultValue )
   {
      return _BranchApplicable[index] == null ? defaultValue : _BranchApplicable[index].booleanValue();
   }
    
   /**
    * Gets the array of Branch Applicable fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Branch Applicable values.
    */
   public final Boolean[] getBranchApplicableArray()
   {
      return _BranchApplicable;
   }
    
   /**
    * Gets the Sales Rep Applicable field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Sales Rep Applicable or null.
    */
   public final Boolean getSalesRepApplicable( int index )
   {
      return _SalesRepApplicable[index];
   }
    
   /**
    * Gets the Sales Rep Applicable field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Sales Rep Applicable or the specified default value.
    */
   public final boolean getSalesRepApplicable( int index, boolean defaultValue )
   {
      return _SalesRepApplicable[index] == null ? defaultValue : _SalesRepApplicable[index].booleanValue();
   }
    
   /**
    * Gets the array of Sales Rep Applicable fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Sales Rep Applicable values.
    */
   public final Boolean[] getSalesRepApplicableArray()
   {
      return _SalesRepApplicable;
   }
    
   /**
    * Gets the Fund Group Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Group Type or null.
    */
   public final String getFundGroupType( int index )
   {
      return _FundGroupType[index];
   }
    
   /**
    * Gets the Fund Group Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Group Type or the specified default value.
    */
   public final String getFundGroupType( int index, String defaultValue )
   {
      return _FundGroupType[index] == null ? defaultValue : _FundGroupType[index];
   }
    
   /**
    * Gets the array of Fund Group Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Group Type values.
    */
   public final String[] getFundGroupTypeArray()
   {
      return _FundGroupType;
   }
    
   /**
    * Gets the Fund Class Applicable field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Class Applicable or null.
    */
   public final Boolean getFundClassApplicable( int index )
   {
      return _FundClassApplicable[index];
   }
    
   /**
    * Gets the Fund Class Applicable field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Class Applicable or the specified default value.
    */
   public final boolean getFundClassApplicable( int index, boolean defaultValue )
   {
      return _FundClassApplicable[index] == null ? defaultValue : _FundClassApplicable[index].booleanValue();
   }
    
   /**
    * Gets the array of Fund Class Applicable fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Class Applicable values.
    */
   public final Boolean[] getFundClassApplicableArray()
   {
      return _FundClassApplicable;
   }
    
   /**
    * Gets the FromFndClassApplicable field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FromFndClassApplicable or null.
    */
   public final Boolean getFromFndClassApplicable( int index )
   {
      return _FromFndClassApplicable[index];
   }
    
   /**
    * Gets the FromFndClassApplicable field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FromFndClassApplicable or the specified default value.
    */
   public final boolean getFromFndClassApplicable( int index, boolean defaultValue )
   {
      return _FromFndClassApplicable[index] == null ? defaultValue : _FromFndClassApplicable[index].booleanValue();
   }
    
   /**
    * Gets the array of FromFndClassApplicable fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FromFndClassApplicable values.
    */
   public final Boolean[] getFromFndClassApplicableArray()
   {
      return _FromFndClassApplicable;
   }
    
   /**
    * Gets the FeeTypeList field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FeeTypeList or null.
    */
   public final String getFeeTypeList( int index )
   {
      return _FeeTypeList[index];
   }
    
   /**
    * Gets the FeeTypeList field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FeeTypeList or the specified default value.
    */
   public final String getFeeTypeList( int index, String defaultValue )
   {
      return _FeeTypeList[index] == null ? defaultValue : _FeeTypeList[index];
   }
    
   /**
    * Gets the array of FeeTypeList fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FeeTypeList values.
    */
   public final String[] getFeeTypeListArray()
   {
      return _FeeTypeList;
   }
    
   /**
    * Gets the BasedOnList field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the BasedOnList or null.
    */
   public final String getBasedOnList( int index )
   {
      return _BasedOnList[index];
   }
    
   /**
    * Gets the BasedOnList field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BasedOnList or the specified default value.
    */
   public final String getBasedOnList( int index, String defaultValue )
   {
      return _BasedOnList[index] == null ? defaultValue : _BasedOnList[index];
   }
    
   /**
    * Gets the array of BasedOnList fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of BasedOnList values.
    */
   public final String[] getBasedOnListArray()
   {
      return _BasedOnList;
   }
    
   /**
    * Gets the HowPaidList field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the HowPaidList or null.
    */
   public final String getHowPaidList( int index )
   {
      return _HowPaidList[index];
   }
    
   /**
    * Gets the HowPaidList field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the HowPaidList or the specified default value.
    */
   public final String getHowPaidList( int index, String defaultValue )
   {
      return _HowPaidList[index] == null ? defaultValue : _HowPaidList[index];
   }
    
   /**
    * Gets the array of HowPaidList fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of HowPaidList values.
    */
   public final String[] getHowPaidListArray()
   {
      return _HowPaidList;
   }
    
   /**
    * Gets the MinMaxFreqList field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the MinMaxFreqList or null.
    */
   public final String getMinMaxFreqList( int index )
   {
      return _MinMaxFreqList[index];
   }
    
   /**
    * Gets the MinMaxFreqList field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the MinMaxFreqList or the specified default value.
    */
   public final String getMinMaxFreqList( int index, String defaultValue )
   {
      return _MinMaxFreqList[index] == null ? defaultValue : _MinMaxFreqList[index];
   }
    
   /**
    * Gets the array of MinMaxFreqList fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of MinMaxFreqList values.
    */
   public final String[] getMinMaxFreqListArray()
   {
      return _MinMaxFreqList;
   }
    
   /**
    * Gets the Override List field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Override List or null.
    */
   public final String getOverrideList( int index )
   {
      return _OverrideList[index];
   }
    
   /**
    * Gets the Override List field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Override List or the specified default value.
    */
   public final String getOverrideList( int index, String defaultValue )
   {
      return _OverrideList[index] == null ? defaultValue : _OverrideList[index];
   }
    
   /**
    * Gets the array of Override List fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Override List values.
    */
   public final String[] getOverrideListArray()
   {
      return _OverrideList;
   }
    
   /**
    * Gets the OnPWApplicable field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the OnPWApplicable or null.
    */
   public final Boolean getOnPWApplicable( int index )
   {
      return _OnPWApplicable[index];
   }
    
   /**
    * Gets the OnPWApplicable field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the OnPWApplicable or the specified default value.
    */
   public final boolean getOnPWApplicable( int index, boolean defaultValue )
   {
      return _OnPWApplicable[index] == null ? defaultValue : _OnPWApplicable[index].booleanValue();
   }
    
   /**
    * Gets the array of OnPWApplicable fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of OnPWApplicable values.
    */
   public final Boolean[] getOnPWApplicableArray()
   {
      return _OnPWApplicable;
   }
    
   /**
    * Gets the OnFWApplicable field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the OnFWApplicable or null.
    */
   public final Boolean getOnFWApplicable( int index )
   {
      return _OnFWApplicable[index];
   }
    
   /**
    * Gets the OnFWApplicable field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the OnFWApplicable or the specified default value.
    */
   public final boolean getOnFWApplicable( int index, boolean defaultValue )
   {
      return _OnFWApplicable[index] == null ? defaultValue : _OnFWApplicable[index].booleanValue();
   }
    
   /**
    * Gets the array of OnFWApplicable fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of OnFWApplicable values.
    */
   public final Boolean[] getOnFWApplicableArray()
   {
      return _OnFWApplicable;
   }
    
   /**
    * Gets the FeeSetupLevel field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FeeSetupLevel or null.
    */
   public final String getFeeSetupLevel( int index )
   {
      return _FeeSetupLevel[index];
   }
    
   /**
    * Gets the FeeSetupLevel field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FeeSetupLevel or the specified default value.
    */
   public final String getFeeSetupLevel( int index, String defaultValue )
   {
      return _FeeSetupLevel[index] == null ? defaultValue : _FeeSetupLevel[index];
   }
    
   /**
    * Gets the array of FeeSetupLevel fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FeeSetupLevel values.
    */
   public final String[] getFeeSetupLevelArray()
   {
      return _FeeSetupLevel;
   }
    
   /**
    * Gets the FamilyCodeApplicable field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FamilyCodeApplicable or null.
    */
   public final Boolean getFamilyCodeApplicable( int index )
   {
      return _FamilyCodeApplicable[index];
   }
    
   /**
    * Gets the FamilyCodeApplicable field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FamilyCodeApplicable or the specified default value.
    */
   public final boolean getFamilyCodeApplicable( int index, boolean defaultValue )
   {
      return _FamilyCodeApplicable[index] == null ? defaultValue : _FamilyCodeApplicable[index].booleanValue();
   }
    
   /**
    * Gets the array of FamilyCodeApplicable fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FamilyCodeApplicable values.
    */
   public final Boolean[] getFamilyCodeApplicableArray()
   {
      return _FamilyCodeApplicable;
   }
    
   /**
    * Gets the Level field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Level or null.
    */
   public final String getLevel( int index )
   {
      return _Level[index];
   }
    
   /**
    * Gets the Level field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Level or the specified default value.
    */
   public final String getLevel( int index, String defaultValue )
   {
      return _Level[index] == null ? defaultValue : _Level[index];
   }
    
   /**
    * Gets the array of Level fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Level values.
    */
   public final String[] getLevelArray()
   {
      return _Level;
   }
    
   /**
    * Gets the Trade Fee Type List field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Trade Fee Type List or null.
    */
   public final String getTradeFeeOptionList( int index )
   {
      return _TradeFeeOptionList[index];
   }
    
   /**
    * Gets the Trade Fee Type List field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Trade Fee Type List or the specified default value.
    */
   public final String getTradeFeeOptionList( int index, String defaultValue )
   {
      return _TradeFeeOptionList[index] == null ? defaultValue : _TradeFeeOptionList[index];
   }
    
   /**
    * Gets the array of Trade Fee Type List fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Trade Fee Type List values.
    */
   public final String[] getTradeFeeOptionListArray()
   {
      return _TradeFeeOptionList;
   }
    
   /**
    * Gets the Charge Option List field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Charge Option List or null.
    */
   public final String getChargeOptionList( int index )
   {
      return _ChargeOptionList[index];
   }
    
   /**
    * Gets the Charge Option List field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Charge Option List or the specified default value.
    */
   public final String getChargeOptionList( int index, String defaultValue )
   {
      return _ChargeOptionList[index] == null ? defaultValue : _ChargeOptionList[index];
   }
    
   /**
    * Gets the array of Charge Option List fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Charge Option List values.
    */
   public final String[] getChargeOptionListArray()
   {
      return _ChargeOptionList;
   }
    
   /**
    * Gets the Status field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Status or null.
    */
   public final String getStat( int index )
   {
      return _Stat[index];
   }
    
   /**
    * Gets the Status field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Status or the specified default value.
    */
   public final String getStat( int index, String defaultValue )
   {
      return _Stat[index] == null ? defaultValue : _Stat[index];
   }
    
   /**
    * Gets the array of Status fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Status values.
    */
   public final String[] getStatArray()
   {
      return _Stat;
   }
    
   /**
    * Gets the Does Fee Exists field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Does Fee Exists or null.
    */
   public final Boolean getFeeExists( int index )
   {
      return _FeeExists[index];
   }
    
   /**
    * Gets the Does Fee Exists field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Does Fee Exists or the specified default value.
    */
   public final boolean getFeeExists( int index, boolean defaultValue )
   {
      return _FeeExists[index] == null ? defaultValue : _FeeExists[index].booleanValue();
   }
    
   /**
    * Gets the array of Does Fee Exists fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Does Fee Exists values.
    */
   public final Boolean[] getFeeExistsArray()
   {
      return _FeeExists;
   }
    
   /**
    * Gets the Does Fee Exists by Broker field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Does Fee Exists by Broker or null.
    */
   public final Boolean getFeeExistsByBroker( int index )
   {
      return _FeeExistsByBroker[index];
   }
    
   /**
    * Gets the Does Fee Exists by Broker field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Does Fee Exists by Broker or the specified default value.
    */
   public final boolean getFeeExistsByBroker( int index, boolean defaultValue )
   {
      return _FeeExistsByBroker[index] == null ? defaultValue : _FeeExistsByBroker[index].booleanValue();
   }
    
   /**
    * Gets the array of Does Fee Exists by Broker fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Does Fee Exists by Broker values.
    */
   public final Boolean[] getFeeExistsByBrokerArray()
   {
      return _FeeExistsByBroker;
   }
    
   /**
    * Gets the Does Fee Exists by Branch field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Does Fee Exists by Branch or null.
    */
   public final Boolean getFeeExistsByBranch( int index )
   {
      return _FeeExistsByBranch[index];
   }
    
   /**
    * Gets the Does Fee Exists by Branch field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Does Fee Exists by Branch or the specified default value.
    */
   public final boolean getFeeExistsByBranch( int index, boolean defaultValue )
   {
      return _FeeExistsByBranch[index] == null ? defaultValue : _FeeExistsByBranch[index].booleanValue();
   }
    
   /**
    * Gets the array of Does Fee Exists by Branch fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Does Fee Exists by Branch values.
    */
   public final Boolean[] getFeeExistsByBranchArray()
   {
      return _FeeExistsByBranch;
   }
    
   /**
    * Gets the Does Fee Exists by Slsrep field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Does Fee Exists by Slsrep or null.
    */
   public final Boolean getFeeExistsBySlsrep( int index )
   {
      return _FeeExistsBySlsrep[index];
   }
    
   /**
    * Gets the Does Fee Exists by Slsrep field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Does Fee Exists by Slsrep or the specified default value.
    */
   public final boolean getFeeExistsBySlsrep( int index, boolean defaultValue )
   {
      return _FeeExistsBySlsrep[index] == null ? defaultValue : _FeeExistsBySlsrep[index].booleanValue();
   }
    
   /**
    * Gets the array of Does Fee Exists by Slsrep fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Does Fee Exists by Slsrep values.
    */
   public final Boolean[] getFeeExistsBySlsrepArray()
   {
      return _FeeExistsBySlsrep;
   }
    
   /**
    * Gets the Does Fee Exists by Fund Com Grp field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Does Fee Exists by Fund Com Grp or null.
    */
   public final Boolean getFeeExistsByFundComGrp( int index )
   {
      return _FeeExistsByFundComGrp[index];
   }
    
   /**
    * Gets the Does Fee Exists by Fund Com Grp field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Does Fee Exists by Fund Com Grp or the specified default value.
    */
   public final boolean getFeeExistsByFundComGrp( int index, boolean defaultValue )
   {
      return _FeeExistsByFundComGrp[index] == null ? defaultValue : _FeeExistsByFundComGrp[index].booleanValue();
   }
    
   /**
    * Gets the array of Does Fee Exists by Fund Com Grp fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Does Fee Exists by Fund Com Grp values.
    */
   public final Boolean[] getFeeExistsByFundComGrpArray()
   {
      return _FeeExistsByFundComGrp;
   }
    
   /**
    * Gets the Applied Method List field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Applied Method List or null.
    */
   public final String getAppliedMethodList( int index )
   {
      return _AppliedMethodList[index];
   }
    
   /**
    * Gets the Applied Method List field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Applied Method List or the specified default value.
    */
   public final String getAppliedMethodList( int index, String defaultValue )
   {
      return _AppliedMethodList[index] == null ? defaultValue : _AppliedMethodList[index];
   }
    
   /**
    * Gets the array of Applied Method List fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Applied Method List values.
    */
   public final String[] getAppliedMethodListArray()
   {
      return _AppliedMethodList;
   }
    
   /**
    * Gets the FundList field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FundList or null.
    */
   public final String getFundList( int index )
   {
      return _FundList[index];
   }
    
   /**
    * Gets the FundList field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FundList or the specified default value.
    */
   public final String getFundList( int index, String defaultValue )
   {
      return _FundList[index] == null ? defaultValue : _FundList[index];
   }
    
   /**
    * Gets the array of FundList fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FundList values.
    */
   public final String[] getFundListArray()
   {
      return _FundList;
   }
    
   /**
    * Gets the Indicates if Threshold Amount  applies field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Indicates if Threshold Amount  applies or null.
    */
   public final Boolean getThresholdAmtApply( int index )
   {
      return _ThresholdAmtApply[index];
   }
    
   /**
    * Gets the Indicates if Threshold Amount  applies field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Indicates if Threshold Amount  applies or the specified default value.
    */
   public final boolean getThresholdAmtApply( int index, boolean defaultValue )
   {
      return _ThresholdAmtApply[index] == null ? defaultValue : _ThresholdAmtApply[index].booleanValue();
   }
    
   /**
    * Gets the array of Indicates if Threshold Amount  applies fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Indicates if Threshold Amount  applies values.
    */
   public final Boolean[] getThresholdAmtApplyArray()
   {
      return _ThresholdAmtApply;
   }
    
   /**
    * Gets the UpdateRule field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the UpdateRule or null.
    */
   public final String getUpdateRule( int index )
   {
      return _UpdateRule[index];
   }
    
   /**
    * Gets the UpdateRule field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the UpdateRule or the specified default value.
    */
   public final String getUpdateRule( int index, String defaultValue )
   {
      return _UpdateRule[index] == null ? defaultValue : _UpdateRule[index];
   }
    
   /**
    * Gets the array of UpdateRule fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of UpdateRule values.
    */
   public final String[] getUpdateRuleArray()
   {
      return _UpdateRule;
   }
    
   /**
    * Gets the MaxRate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the MaxRate or null.
    */
   public final String getMaxRate( int index )
   {
      return _MaxRate[index];
   }
    
   /**
    * Gets the MaxRate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the MaxRate or the specified default value.
    */
   public final String getMaxRate( int index, String defaultValue )
   {
      return _MaxRate[index] == null ? defaultValue : _MaxRate[index];
   }
    
   /**
    * Gets the array of MaxRate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of MaxRate values.
    */
   public final String[] getMaxRateArray()
   {
      return _MaxRate;
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
      
      _FeeCode = resizeArray( _FeeCode, _RepeatCount );
      _ShGroupApplicable = resizeArray( _ShGroupApplicable, _RepeatCount );
      _BrokerApplicable = resizeArray( _BrokerApplicable, _RepeatCount );
      _BranchApplicable = resizeArray( _BranchApplicable, _RepeatCount );
      _SalesRepApplicable = resizeArray( _SalesRepApplicable, _RepeatCount );
      _FundGroupType = resizeArray( _FundGroupType, _RepeatCount );
      _FundClassApplicable = resizeArray( _FundClassApplicable, _RepeatCount );
      _FromFndClassApplicable = resizeArray( _FromFndClassApplicable, _RepeatCount );
      _FeeTypeList = resizeArray( _FeeTypeList, _RepeatCount );
      _BasedOnList = resizeArray( _BasedOnList, _RepeatCount );
      _HowPaidList = resizeArray( _HowPaidList, _RepeatCount );
      _MinMaxFreqList = resizeArray( _MinMaxFreqList, _RepeatCount );
      _OverrideList = resizeArray( _OverrideList, _RepeatCount );
      _OnPWApplicable = resizeArray( _OnPWApplicable, _RepeatCount );
      _OnFWApplicable = resizeArray( _OnFWApplicable, _RepeatCount );
      _FeeSetupLevel = resizeArray( _FeeSetupLevel, _RepeatCount );
      _FamilyCodeApplicable = resizeArray( _FamilyCodeApplicable, _RepeatCount );
      _Level = resizeArray( _Level, _RepeatCount );
      _TradeFeeOptionList = resizeArray( _TradeFeeOptionList, _RepeatCount );
      _ChargeOptionList = resizeArray( _ChargeOptionList, _RepeatCount );
      _Stat = resizeArray( _Stat, _RepeatCount );
      _FeeExists = resizeArray( _FeeExists, _RepeatCount );
      _FeeExistsByBroker = resizeArray( _FeeExistsByBroker, _RepeatCount );
      _FeeExistsByBranch = resizeArray( _FeeExistsByBranch, _RepeatCount );
      _FeeExistsBySlsrep = resizeArray( _FeeExistsBySlsrep, _RepeatCount );
      _FeeExistsByFundComGrp = resizeArray( _FeeExistsByFundComGrp, _RepeatCount );
      _AppliedMethodList = resizeArray( _AppliedMethodList, _RepeatCount );
      _FundList = resizeArray( _FundList, _RepeatCount );
      _ThresholdAmtApply = resizeArray( _ThresholdAmtApply, _RepeatCount );
      _UpdateRule = resizeArray( _UpdateRule, _RepeatCount );
      _MaxRate = resizeArray( _MaxRate, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _FeeCode[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ShGroupApplicable[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _BrokerApplicable[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _BranchApplicable[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _SalesRepApplicable[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FundGroupType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundClassApplicable[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FromFndClassApplicable[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FeeTypeList[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BasedOnList[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _HowPaidList[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MinMaxFreqList[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _OverrideList[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _OnPWApplicable[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _OnFWApplicable[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FeeSetupLevel[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FamilyCodeApplicable[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _Level[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TradeFeeOptionList[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ChargeOptionList[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Stat[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FeeExists[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FeeExistsByBroker[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FeeExistsByBranch[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FeeExistsBySlsrep[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FeeExistsByFundComGrp[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _AppliedMethodList[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundList[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ThresholdAmtApply[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _UpdateRule[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MaxRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
