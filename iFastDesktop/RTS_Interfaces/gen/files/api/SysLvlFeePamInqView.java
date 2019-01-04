
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * System Level Fee Parms Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/SysLvlFeePamInq.doc">SysLvlFeePamInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class SysLvlFeePamInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Fee ID member array.
    */
   private Integer[] _FeeID = null;
   
   /**
    * Fund member array.
    */
   private String[] _rxFundCode = null;
   
   /**
    * Class member array.
    */
   private String[] _rxClassCode = null;
   
   /**
    * Fund From member array.
    */
   private String[] _FundFromCode = null;
   
   /**
    * Class From member array.
    */
   private String[] _ClassFromCode = null;
   
   /**
    * Fee Code/ Fee Defn member array.
    */
   private Integer[] _rxFeeCode = null;
   
   /**
    * Fee Type - flat, prcnt, scale, tier member array.
    */
   private String[] _FeeType = null;
   
   /**
    * Rate member array.
    */
   private String[] _Rate = null;
   
   /**
    * Minimum Fee member array.
    */
   private String[] _MinFee = null;
   
   /**
    * Maximum Fee member array.
    */
   private String[] _MaxFee = null;
   
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = null;
   
   /**
    * Stop Date member array.
    */
   private Date[] _StopDate = null;
   
   /**
    * Freq Min/Max Applies member array.
    */
   private String[] _FreqMinMaxApp = null;
   
   /**
    * Charge on Partial Redemption member array.
    */
   private Boolean[] _ChrgOnPrtlRed = null;
   
   /**
    * Charge on Full Redemption member array.
    */
   private Boolean[] _ChrgOnFullRed = null;
   
   /**
    * Active member array.
    */
   private Boolean[] _Active = null;
   
   /**
    * Process Date member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * Mod Date member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * User Name member array.
    */
   private String[] _UserName = null;
   
   /**
    * Mod User member array.
    */
   private String[] _ModUser = null;
   
   /**
    * Commission Group member array.
    */
   private String[] _rxCommGroup = null;
   
   /**
    * Broker Code member array.
    */
   private String[] _rxBrokerCode = null;
   
   /**
    * Allow override type member array.
    */
   private String[] _AllowOverrideType = null;
   
   /**
    * How is fee calculated member array.
    */
   private String[] _BasedOn = null;
   
   /**
    * Fee/ Settlement Currency member array.
    */
   private String[] _Currency = null;
   
   /**
    * Who pays this fee ? member array.
    */
   private String[] _WhoPays = null;
   
   /**
    * Shareholder Group member array.
    */
   private String[] _rxShGroup = null;
   
   /**
    * FeeParameter Recid member array.
    */
   private Integer[] _FeeParmRId = null;
   
   /**
    * branch Code member array.
    */
   private String[] _rxBranchCode = null;
   
   /**
    * Sales Rep Code member array.
    */
   private String[] _rxSlsRepCode = null;
   
   /**
    * Family Code member array.
    */
   private String[] _rxFamilyCode = null;
   
   /**
    * Branch Name member array.
    */
   private String[] _BranchName = null;
   
   /**
    * Sales Rep Name member array.
    */
   private String[] _SlsRepName = null;
   
   /**
    * Family Name member array.
    */
   private String[] _FamilyName = null;
   
   /**
    * BrokerName member array.
    */
   private String[] _BrokerName = null;
   
   /**
    * Share Group Name member array.
    */
   private String[] _ShGroupName = null;
   
   /**
    * Fee Model Code member array.
    */
   private String[] _rxFeeModelCode = null;
   
   /**
    * Charge Option member array.
    */
   private String[] _ChargeOption = null;
   
   /**
    * Applied Method member array.
    */
   private String[] _AppliedMethod = null;
   
   /**
    * Fund List member array.
    */
   private String[] _FundList = null;
   
   /**
    * Threshold Amount member array.
    */
   private String[] _ThresholdAmt = null;
   
   /**
    * Threshold Currency member array.
    */
   private String[] _ThresholdCurrency = null;
   
   /**
    * Distribution Channel member array.
    */
   private String[] _DistribChannel = null;
   
   /**
    * Fund Link member array.
    */
   private String[] _FundLink = null;
   
   /**
    * Tax Inclusive flag member array.
    */
   private String[] _TaxInclusive = null;
   
   /**
    * FeeModel Last Process Date member array.
    */
   private Date[] _FMLastProcDate = null;
   
   /**
    * Thresholdrange recid member array.
    */
   private Integer[] _ThrshldRecID = null;
   

   /**
    * Constructs the SysLvlFeePamInqView object.
    * 
    */
   public SysLvlFeePamInqView()
   {
      super ( new SysLvlFeePamInqRequest() );
   }

   /**
    * Constructs the SysLvlFeePamInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public SysLvlFeePamInqView( String hostEncoding )
   {
      super ( new SysLvlFeePamInqRequest( hostEncoding ) );
   }

   /**
    * Gets the SysLvlFeePamInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The SysLvlFeePamInqRequest object.
    */
   public final SysLvlFeePamInqRequest getRequest()
   {
      return (SysLvlFeePamInqRequest)getIFastRequest();
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
    * Gets the Fee ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fee ID or null.
    */
   public final Integer getFeeID( int index )
   {
      return _FeeID[index];
   }
    
   /**
    * Gets the Fee ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee ID or the specified default value.
    */
   public final int getFeeID( int index, int defaultValue )
   {
      return _FeeID[index] == null ? defaultValue : _FeeID[index].intValue();
   }
    
   /**
    * Gets the array of Fee ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee ID values.
    */
   public final Integer[] getFeeIDArray()
   {
      return _FeeID;
   }
    
   /**
    * Gets the Fund field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund or null.
    */
   public final String getrxFundCode( int index )
   {
      return _rxFundCode[index];
   }
    
   /**
    * Gets the Fund field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund or the specified default value.
    */
   public final String getrxFundCode( int index, String defaultValue )
   {
      return _rxFundCode[index] == null ? defaultValue : _rxFundCode[index];
   }
    
   /**
    * Gets the array of Fund fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund values.
    */
   public final String[] getrxFundCodeArray()
   {
      return _rxFundCode;
   }
    
   /**
    * Gets the Class field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Class or null.
    */
   public final String getrxClassCode( int index )
   {
      return _rxClassCode[index];
   }
    
   /**
    * Gets the Class field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class or the specified default value.
    */
   public final String getrxClassCode( int index, String defaultValue )
   {
      return _rxClassCode[index] == null ? defaultValue : _rxClassCode[index];
   }
    
   /**
    * Gets the array of Class fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Class values.
    */
   public final String[] getrxClassCodeArray()
   {
      return _rxClassCode;
   }
    
   /**
    * Gets the Fund From field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund From or null.
    */
   public final String getFundFromCode( int index )
   {
      return _FundFromCode[index];
   }
    
   /**
    * Gets the Fund From field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund From or the specified default value.
    */
   public final String getFundFromCode( int index, String defaultValue )
   {
      return _FundFromCode[index] == null ? defaultValue : _FundFromCode[index];
   }
    
   /**
    * Gets the array of Fund From fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund From values.
    */
   public final String[] getFundFromCodeArray()
   {
      return _FundFromCode;
   }
    
   /**
    * Gets the Class From field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Class From or null.
    */
   public final String getClassFromCode( int index )
   {
      return _ClassFromCode[index];
   }
    
   /**
    * Gets the Class From field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class From or the specified default value.
    */
   public final String getClassFromCode( int index, String defaultValue )
   {
      return _ClassFromCode[index] == null ? defaultValue : _ClassFromCode[index];
   }
    
   /**
    * Gets the array of Class From fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Class From values.
    */
   public final String[] getClassFromCodeArray()
   {
      return _ClassFromCode;
   }
    
   /**
    * Gets the Fee Code/ Fee Defn field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fee Code/ Fee Defn or null.
    */
   public final Integer getrxFeeCode( int index )
   {
      return _rxFeeCode[index];
   }
    
   /**
    * Gets the Fee Code/ Fee Defn field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee Code/ Fee Defn or the specified default value.
    */
   public final int getrxFeeCode( int index, int defaultValue )
   {
      return _rxFeeCode[index] == null ? defaultValue : _rxFeeCode[index].intValue();
   }
    
   /**
    * Gets the array of Fee Code/ Fee Defn fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee Code/ Fee Defn values.
    */
   public final Integer[] getrxFeeCodeArray()
   {
      return _rxFeeCode;
   }
    
   /**
    * Gets the Fee Type - flat, prcnt, scale, tier field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fee Type - flat, prcnt, scale, tier or null.
    */
   public final String getFeeType( int index )
   {
      return _FeeType[index];
   }
    
   /**
    * Gets the Fee Type - flat, prcnt, scale, tier field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee Type - flat, prcnt, scale, tier or the specified default value.
    */
   public final String getFeeType( int index, String defaultValue )
   {
      return _FeeType[index] == null ? defaultValue : _FeeType[index];
   }
    
   /**
    * Gets the array of Fee Type - flat, prcnt, scale, tier fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee Type - flat, prcnt, scale, tier values.
    */
   public final String[] getFeeTypeArray()
   {
      return _FeeType;
   }
    
   /**
    * Gets the Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Rate or null.
    */
   public final String getRate( int index )
   {
      return _Rate[index];
   }
    
   /**
    * Gets the Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Rate or the specified default value.
    */
   public final String getRate( int index, String defaultValue )
   {
      return _Rate[index] == null ? defaultValue : _Rate[index];
   }
    
   /**
    * Gets the array of Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Rate values.
    */
   public final String[] getRateArray()
   {
      return _Rate;
   }
    
   /**
    * Gets the Minimum Fee field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Minimum Fee or null.
    */
   public final String getMinFee( int index )
   {
      return _MinFee[index];
   }
    
   /**
    * Gets the Minimum Fee field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Minimum Fee or the specified default value.
    */
   public final String getMinFee( int index, String defaultValue )
   {
      return _MinFee[index] == null ? defaultValue : _MinFee[index];
   }
    
   /**
    * Gets the array of Minimum Fee fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Minimum Fee values.
    */
   public final String[] getMinFeeArray()
   {
      return _MinFee;
   }
    
   /**
    * Gets the Maximum Fee field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Maximum Fee or null.
    */
   public final String getMaxFee( int index )
   {
      return _MaxFee[index];
   }
    
   /**
    * Gets the Maximum Fee field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Maximum Fee or the specified default value.
    */
   public final String getMaxFee( int index, String defaultValue )
   {
      return _MaxFee[index] == null ? defaultValue : _MaxFee[index];
   }
    
   /**
    * Gets the array of Maximum Fee fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Maximum Fee values.
    */
   public final String[] getMaxFeeArray()
   {
      return _MaxFee;
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
    * Gets the Freq Min/Max Applies field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Freq Min/Max Applies or null.
    */
   public final String getFreqMinMaxApp( int index )
   {
      return _FreqMinMaxApp[index];
   }
    
   /**
    * Gets the Freq Min/Max Applies field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Freq Min/Max Applies or the specified default value.
    */
   public final String getFreqMinMaxApp( int index, String defaultValue )
   {
      return _FreqMinMaxApp[index] == null ? defaultValue : _FreqMinMaxApp[index];
   }
    
   /**
    * Gets the array of Freq Min/Max Applies fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Freq Min/Max Applies values.
    */
   public final String[] getFreqMinMaxAppArray()
   {
      return _FreqMinMaxApp;
   }
    
   /**
    * Gets the Charge on Partial Redemption field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Charge on Partial Redemption or null.
    */
   public final Boolean getChrgOnPrtlRed( int index )
   {
      return _ChrgOnPrtlRed[index];
   }
    
   /**
    * Gets the Charge on Partial Redemption field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Charge on Partial Redemption or the specified default value.
    */
   public final boolean getChrgOnPrtlRed( int index, boolean defaultValue )
   {
      return _ChrgOnPrtlRed[index] == null ? defaultValue : _ChrgOnPrtlRed[index].booleanValue();
   }
    
   /**
    * Gets the array of Charge on Partial Redemption fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Charge on Partial Redemption values.
    */
   public final Boolean[] getChrgOnPrtlRedArray()
   {
      return _ChrgOnPrtlRed;
   }
    
   /**
    * Gets the Charge on Full Redemption field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Charge on Full Redemption or null.
    */
   public final Boolean getChrgOnFullRed( int index )
   {
      return _ChrgOnFullRed[index];
   }
    
   /**
    * Gets the Charge on Full Redemption field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Charge on Full Redemption or the specified default value.
    */
   public final boolean getChrgOnFullRed( int index, boolean defaultValue )
   {
      return _ChrgOnFullRed[index] == null ? defaultValue : _ChrgOnFullRed[index].booleanValue();
   }
    
   /**
    * Gets the array of Charge on Full Redemption fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Charge on Full Redemption values.
    */
   public final Boolean[] getChrgOnFullRedArray()
   {
      return _ChrgOnFullRed;
   }
    
   /**
    * Gets the Active field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Active or null.
    */
   public final Boolean getActive( int index )
   {
      return _Active[index];
   }
    
   /**
    * Gets the Active field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Active or the specified default value.
    */
   public final boolean getActive( int index, boolean defaultValue )
   {
      return _Active[index] == null ? defaultValue : _Active[index].booleanValue();
   }
    
   /**
    * Gets the array of Active fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Active values.
    */
   public final Boolean[] getActiveArray()
   {
      return _Active;
   }
    
   /**
    * Gets the Process Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Process Date or null.
    */
   public final Date getProcessDate( int index )
   {
      return _ProcessDate[index];
   }
    
   /**
    * Gets the Process Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Process Date or the specified default value.
    */
   public final Date getProcessDate( int index, Date defaultValue )
   {
      return _ProcessDate[index] == null ? defaultValue : _ProcessDate[index];
   }
    
   /**
    * Gets the array of Process Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Process Date values.
    */
   public final Date[] getProcessDateArray()
   {
      return _ProcessDate;
   }
    
   /**
    * Gets the Mod Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Mod Date or null.
    */
   public final Date getModDate( int index )
   {
      return _ModDate[index];
   }
    
   /**
    * Gets the Mod Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Mod Date or the specified default value.
    */
   public final Date getModDate( int index, Date defaultValue )
   {
      return _ModDate[index] == null ? defaultValue : _ModDate[index];
   }
    
   /**
    * Gets the array of Mod Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Mod Date values.
    */
   public final Date[] getModDateArray()
   {
      return _ModDate;
   }
    
   /**
    * Gets the User Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the User Name or null.
    */
   public final String getUserName( int index )
   {
      return _UserName[index];
   }
    
   /**
    * Gets the User Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the User Name or the specified default value.
    */
   public final String getUserName( int index, String defaultValue )
   {
      return _UserName[index] == null ? defaultValue : _UserName[index];
   }
    
   /**
    * Gets the array of User Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of User Name values.
    */
   public final String[] getUserNameArray()
   {
      return _UserName;
   }
    
   /**
    * Gets the Mod User field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Mod User or null.
    */
   public final String getModUser( int index )
   {
      return _ModUser[index];
   }
    
   /**
    * Gets the Mod User field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Mod User or the specified default value.
    */
   public final String getModUser( int index, String defaultValue )
   {
      return _ModUser[index] == null ? defaultValue : _ModUser[index];
   }
    
   /**
    * Gets the array of Mod User fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Mod User values.
    */
   public final String[] getModUserArray()
   {
      return _ModUser;
   }
    
   /**
    * Gets the Commission Group field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Commission Group or null.
    */
   public final String getrxCommGroup( int index )
   {
      return _rxCommGroup[index];
   }
    
   /**
    * Gets the Commission Group field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commission Group or the specified default value.
    */
   public final String getrxCommGroup( int index, String defaultValue )
   {
      return _rxCommGroup[index] == null ? defaultValue : _rxCommGroup[index];
   }
    
   /**
    * Gets the array of Commission Group fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Commission Group values.
    */
   public final String[] getrxCommGroupArray()
   {
      return _rxCommGroup;
   }
    
   /**
    * Gets the Broker Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Broker Code or null.
    */
   public final String getrxBrokerCode( int index )
   {
      return _rxBrokerCode[index];
   }
    
   /**
    * Gets the Broker Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker Code or the specified default value.
    */
   public final String getrxBrokerCode( int index, String defaultValue )
   {
      return _rxBrokerCode[index] == null ? defaultValue : _rxBrokerCode[index];
   }
    
   /**
    * Gets the array of Broker Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Broker Code values.
    */
   public final String[] getrxBrokerCodeArray()
   {
      return _rxBrokerCode;
   }
    
   /**
    * Gets the Allow override type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Allow override type or null.
    */
   public final String getAllowOverrideType( int index )
   {
      return _AllowOverrideType[index];
   }
    
   /**
    * Gets the Allow override type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Allow override type or the specified default value.
    */
   public final String getAllowOverrideType( int index, String defaultValue )
   {
      return _AllowOverrideType[index] == null ? defaultValue : _AllowOverrideType[index];
   }
    
   /**
    * Gets the array of Allow override type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Allow override type values.
    */
   public final String[] getAllowOverrideTypeArray()
   {
      return _AllowOverrideType;
   }
    
   /**
    * Gets the How is fee calculated field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the How is fee calculated or null.
    */
   public final String getBasedOn( int index )
   {
      return _BasedOn[index];
   }
    
   /**
    * Gets the How is fee calculated field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the How is fee calculated or the specified default value.
    */
   public final String getBasedOn( int index, String defaultValue )
   {
      return _BasedOn[index] == null ? defaultValue : _BasedOn[index];
   }
    
   /**
    * Gets the array of How is fee calculated fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of How is fee calculated values.
    */
   public final String[] getBasedOnArray()
   {
      return _BasedOn;
   }
    
   /**
    * Gets the Fee/ Settlement Currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fee/ Settlement Currency or null.
    */
   public final String getCurrency( int index )
   {
      return _Currency[index];
   }
    
   /**
    * Gets the Fee/ Settlement Currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee/ Settlement Currency or the specified default value.
    */
   public final String getCurrency( int index, String defaultValue )
   {
      return _Currency[index] == null ? defaultValue : _Currency[index];
   }
    
   /**
    * Gets the array of Fee/ Settlement Currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee/ Settlement Currency values.
    */
   public final String[] getCurrencyArray()
   {
      return _Currency;
   }
    
   /**
    * Gets the Who pays this fee ? field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Who pays this fee ? or null.
    */
   public final String getWhoPays( int index )
   {
      return _WhoPays[index];
   }
    
   /**
    * Gets the Who pays this fee ? field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Who pays this fee ? or the specified default value.
    */
   public final String getWhoPays( int index, String defaultValue )
   {
      return _WhoPays[index] == null ? defaultValue : _WhoPays[index];
   }
    
   /**
    * Gets the array of Who pays this fee ? fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Who pays this fee ? values.
    */
   public final String[] getWhoPaysArray()
   {
      return _WhoPays;
   }
    
   /**
    * Gets the Shareholder Group field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Shareholder Group or null.
    */
   public final String getrxShGroup( int index )
   {
      return _rxShGroup[index];
   }
    
   /**
    * Gets the Shareholder Group field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Shareholder Group or the specified default value.
    */
   public final String getrxShGroup( int index, String defaultValue )
   {
      return _rxShGroup[index] == null ? defaultValue : _rxShGroup[index];
   }
    
   /**
    * Gets the array of Shareholder Group fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Shareholder Group values.
    */
   public final String[] getrxShGroupArray()
   {
      return _rxShGroup;
   }
    
   /**
    * Gets the FeeParameter Recid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FeeParameter Recid or null.
    */
   public final Integer getFeeParmRId( int index )
   {
      return _FeeParmRId[index];
   }
    
   /**
    * Gets the FeeParameter Recid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FeeParameter Recid or the specified default value.
    */
   public final int getFeeParmRId( int index, int defaultValue )
   {
      return _FeeParmRId[index] == null ? defaultValue : _FeeParmRId[index].intValue();
   }
    
   /**
    * Gets the array of FeeParameter Recid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FeeParameter Recid values.
    */
   public final Integer[] getFeeParmRIdArray()
   {
      return _FeeParmRId;
   }
    
   /**
    * Gets the branch Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the branch Code or null.
    */
   public final String getrxBranchCode( int index )
   {
      return _rxBranchCode[index];
   }
    
   /**
    * Gets the branch Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the branch Code or the specified default value.
    */
   public final String getrxBranchCode( int index, String defaultValue )
   {
      return _rxBranchCode[index] == null ? defaultValue : _rxBranchCode[index];
   }
    
   /**
    * Gets the array of branch Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of branch Code values.
    */
   public final String[] getrxBranchCodeArray()
   {
      return _rxBranchCode;
   }
    
   /**
    * Gets the Sales Rep Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Sales Rep Code or null.
    */
   public final String getrxSlsRepCode( int index )
   {
      return _rxSlsRepCode[index];
   }
    
   /**
    * Gets the Sales Rep Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Sales Rep Code or the specified default value.
    */
   public final String getrxSlsRepCode( int index, String defaultValue )
   {
      return _rxSlsRepCode[index] == null ? defaultValue : _rxSlsRepCode[index];
   }
    
   /**
    * Gets the array of Sales Rep Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Sales Rep Code values.
    */
   public final String[] getrxSlsRepCodeArray()
   {
      return _rxSlsRepCode;
   }
    
   /**
    * Gets the Family Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Family Code or null.
    */
   public final String getrxFamilyCode( int index )
   {
      return _rxFamilyCode[index];
   }
    
   /**
    * Gets the Family Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Family Code or the specified default value.
    */
   public final String getrxFamilyCode( int index, String defaultValue )
   {
      return _rxFamilyCode[index] == null ? defaultValue : _rxFamilyCode[index];
   }
    
   /**
    * Gets the array of Family Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Family Code values.
    */
   public final String[] getrxFamilyCodeArray()
   {
      return _rxFamilyCode;
   }
    
   /**
    * Gets the Branch Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Branch Name or null.
    */
   public final String getBranchName( int index )
   {
      return _BranchName[index];
   }
    
   /**
    * Gets the Branch Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Branch Name or the specified default value.
    */
   public final String getBranchName( int index, String defaultValue )
   {
      return _BranchName[index] == null ? defaultValue : _BranchName[index];
   }
    
   /**
    * Gets the array of Branch Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Branch Name values.
    */
   public final String[] getBranchNameArray()
   {
      return _BranchName;
   }
    
   /**
    * Gets the Sales Rep Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Sales Rep Name or null.
    */
   public final String getSlsRepName( int index )
   {
      return _SlsRepName[index];
   }
    
   /**
    * Gets the Sales Rep Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Sales Rep Name or the specified default value.
    */
   public final String getSlsRepName( int index, String defaultValue )
   {
      return _SlsRepName[index] == null ? defaultValue : _SlsRepName[index];
   }
    
   /**
    * Gets the array of Sales Rep Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Sales Rep Name values.
    */
   public final String[] getSlsRepNameArray()
   {
      return _SlsRepName;
   }
    
   /**
    * Gets the Family Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Family Name or null.
    */
   public final String getFamilyName( int index )
   {
      return _FamilyName[index];
   }
    
   /**
    * Gets the Family Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Family Name or the specified default value.
    */
   public final String getFamilyName( int index, String defaultValue )
   {
      return _FamilyName[index] == null ? defaultValue : _FamilyName[index];
   }
    
   /**
    * Gets the array of Family Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Family Name values.
    */
   public final String[] getFamilyNameArray()
   {
      return _FamilyName;
   }
    
   /**
    * Gets the BrokerName field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the BrokerName or null.
    */
   public final String getBrokerName( int index )
   {
      return _BrokerName[index];
   }
    
   /**
    * Gets the BrokerName field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BrokerName or the specified default value.
    */
   public final String getBrokerName( int index, String defaultValue )
   {
      return _BrokerName[index] == null ? defaultValue : _BrokerName[index];
   }
    
   /**
    * Gets the array of BrokerName fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of BrokerName values.
    */
   public final String[] getBrokerNameArray()
   {
      return _BrokerName;
   }
    
   /**
    * Gets the Share Group Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Share Group Name or null.
    */
   public final String getShGroupName( int index )
   {
      return _ShGroupName[index];
   }
    
   /**
    * Gets the Share Group Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Share Group Name or the specified default value.
    */
   public final String getShGroupName( int index, String defaultValue )
   {
      return _ShGroupName[index] == null ? defaultValue : _ShGroupName[index];
   }
    
   /**
    * Gets the array of Share Group Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Share Group Name values.
    */
   public final String[] getShGroupNameArray()
   {
      return _ShGroupName;
   }
    
   /**
    * Gets the Fee Model Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fee Model Code or null.
    */
   public final String getrxFeeModelCode( int index )
   {
      return _rxFeeModelCode[index];
   }
    
   /**
    * Gets the Fee Model Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee Model Code or the specified default value.
    */
   public final String getrxFeeModelCode( int index, String defaultValue )
   {
      return _rxFeeModelCode[index] == null ? defaultValue : _rxFeeModelCode[index];
   }
    
   /**
    * Gets the array of Fee Model Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee Model Code values.
    */
   public final String[] getrxFeeModelCodeArray()
   {
      return _rxFeeModelCode;
   }
    
   /**
    * Gets the Charge Option field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Charge Option or null.
    */
   public final String getChargeOption( int index )
   {
      return _ChargeOption[index];
   }
    
   /**
    * Gets the Charge Option field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Charge Option or the specified default value.
    */
   public final String getChargeOption( int index, String defaultValue )
   {
      return _ChargeOption[index] == null ? defaultValue : _ChargeOption[index];
   }
    
   /**
    * Gets the array of Charge Option fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Charge Option values.
    */
   public final String[] getChargeOptionArray()
   {
      return _ChargeOption;
   }
    
   /**
    * Gets the Applied Method field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Applied Method or null.
    */
   public final String getAppliedMethod( int index )
   {
      return _AppliedMethod[index];
   }
    
   /**
    * Gets the Applied Method field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Applied Method or the specified default value.
    */
   public final String getAppliedMethod( int index, String defaultValue )
   {
      return _AppliedMethod[index] == null ? defaultValue : _AppliedMethod[index];
   }
    
   /**
    * Gets the array of Applied Method fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Applied Method values.
    */
   public final String[] getAppliedMethodArray()
   {
      return _AppliedMethod;
   }
    
   /**
    * Gets the Fund List field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund List or null.
    */
   public final String getFundList( int index )
   {
      return _FundList[index];
   }
    
   /**
    * Gets the Fund List field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund List or the specified default value.
    */
   public final String getFundList( int index, String defaultValue )
   {
      return _FundList[index] == null ? defaultValue : _FundList[index];
   }
    
   /**
    * Gets the array of Fund List fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund List values.
    */
   public final String[] getFundListArray()
   {
      return _FundList;
   }
    
   /**
    * Gets the Threshold Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Threshold Amount or null.
    */
   public final String getThresholdAmt( int index )
   {
      return _ThresholdAmt[index];
   }
    
   /**
    * Gets the Threshold Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Threshold Amount or the specified default value.
    */
   public final String getThresholdAmt( int index, String defaultValue )
   {
      return _ThresholdAmt[index] == null ? defaultValue : _ThresholdAmt[index];
   }
    
   /**
    * Gets the array of Threshold Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Threshold Amount values.
    */
   public final String[] getThresholdAmtArray()
   {
      return _ThresholdAmt;
   }
    
   /**
    * Gets the Threshold Currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Threshold Currency or null.
    */
   public final String getThresholdCurrency( int index )
   {
      return _ThresholdCurrency[index];
   }
    
   /**
    * Gets the Threshold Currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Threshold Currency or the specified default value.
    */
   public final String getThresholdCurrency( int index, String defaultValue )
   {
      return _ThresholdCurrency[index] == null ? defaultValue : _ThresholdCurrency[index];
   }
    
   /**
    * Gets the array of Threshold Currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Threshold Currency values.
    */
   public final String[] getThresholdCurrencyArray()
   {
      return _ThresholdCurrency;
   }
    
   /**
    * Gets the Distribution Channel field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Distribution Channel or null.
    */
   public final String getDistribChannel( int index )
   {
      return _DistribChannel[index];
   }
    
   /**
    * Gets the Distribution Channel field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Distribution Channel or the specified default value.
    */
   public final String getDistribChannel( int index, String defaultValue )
   {
      return _DistribChannel[index] == null ? defaultValue : _DistribChannel[index];
   }
    
   /**
    * Gets the array of Distribution Channel fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Distribution Channel values.
    */
   public final String[] getDistribChannelArray()
   {
      return _DistribChannel;
   }
    
   /**
    * Gets the Fund Link field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Link or null.
    */
   public final String getFundLink( int index )
   {
      return _FundLink[index];
   }
    
   /**
    * Gets the Fund Link field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Link or the specified default value.
    */
   public final String getFundLink( int index, String defaultValue )
   {
      return _FundLink[index] == null ? defaultValue : _FundLink[index];
   }
    
   /**
    * Gets the array of Fund Link fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Link values.
    */
   public final String[] getFundLinkArray()
   {
      return _FundLink;
   }
    
   /**
    * Gets the Tax Inclusive flag field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax Inclusive flag or null.
    */
   public final String getTaxInclusive( int index )
   {
      return _TaxInclusive[index];
   }
    
   /**
    * Gets the Tax Inclusive flag field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Inclusive flag or the specified default value.
    */
   public final String getTaxInclusive( int index, String defaultValue )
   {
      return _TaxInclusive[index] == null ? defaultValue : _TaxInclusive[index];
   }
    
   /**
    * Gets the array of Tax Inclusive flag fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax Inclusive flag values.
    */
   public final String[] getTaxInclusiveArray()
   {
      return _TaxInclusive;
   }
    
   /**
    * Gets the FeeModel Last Process Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FeeModel Last Process Date or null.
    */
   public final Date getFMLastProcDate( int index )
   {
      return _FMLastProcDate[index];
   }
    
   /**
    * Gets the FeeModel Last Process Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FeeModel Last Process Date or the specified default value.
    */
   public final Date getFMLastProcDate( int index, Date defaultValue )
   {
      return _FMLastProcDate[index] == null ? defaultValue : _FMLastProcDate[index];
   }
    
   /**
    * Gets the array of FeeModel Last Process Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FeeModel Last Process Date values.
    */
   public final Date[] getFMLastProcDateArray()
   {
      return _FMLastProcDate;
   }
    
   /**
    * Gets the Thresholdrange recid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Thresholdrange recid or null.
    */
   public final Integer getThrshldRecID( int index )
   {
      return _ThrshldRecID[index];
   }
    
   /**
    * Gets the Thresholdrange recid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Thresholdrange recid or the specified default value.
    */
   public final int getThrshldRecID( int index, int defaultValue )
   {
      return _ThrshldRecID[index] == null ? defaultValue : _ThrshldRecID[index].intValue();
   }
    
   /**
    * Gets the array of Thresholdrange recid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Thresholdrange recid values.
    */
   public final Integer[] getThrshldRecIDArray()
   {
      return _ThrshldRecID;
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
      
      _FeeID = resizeArray( _FeeID, _RepeatCount );
      _rxFundCode = resizeArray( _rxFundCode, _RepeatCount );
      _rxClassCode = resizeArray( _rxClassCode, _RepeatCount );
      _FundFromCode = resizeArray( _FundFromCode, _RepeatCount );
      _ClassFromCode = resizeArray( _ClassFromCode, _RepeatCount );
      _rxFeeCode = resizeArray( _rxFeeCode, _RepeatCount );
      _FeeType = resizeArray( _FeeType, _RepeatCount );
      _Rate = resizeArray( _Rate, _RepeatCount );
      _MinFee = resizeArray( _MinFee, _RepeatCount );
      _MaxFee = resizeArray( _MaxFee, _RepeatCount );
      _EffectiveDate = resizeArray( _EffectiveDate, _RepeatCount );
      _StopDate = resizeArray( _StopDate, _RepeatCount );
      _FreqMinMaxApp = resizeArray( _FreqMinMaxApp, _RepeatCount );
      _ChrgOnPrtlRed = resizeArray( _ChrgOnPrtlRed, _RepeatCount );
      _ChrgOnFullRed = resizeArray( _ChrgOnFullRed, _RepeatCount );
      _Active = resizeArray( _Active, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _UserName = resizeArray( _UserName, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _rxCommGroup = resizeArray( _rxCommGroup, _RepeatCount );
      _rxBrokerCode = resizeArray( _rxBrokerCode, _RepeatCount );
      _AllowOverrideType = resizeArray( _AllowOverrideType, _RepeatCount );
      _BasedOn = resizeArray( _BasedOn, _RepeatCount );
      _Currency = resizeArray( _Currency, _RepeatCount );
      _WhoPays = resizeArray( _WhoPays, _RepeatCount );
      _rxShGroup = resizeArray( _rxShGroup, _RepeatCount );
      _FeeParmRId = resizeArray( _FeeParmRId, _RepeatCount );
      _rxBranchCode = resizeArray( _rxBranchCode, _RepeatCount );
      _rxSlsRepCode = resizeArray( _rxSlsRepCode, _RepeatCount );
      _rxFamilyCode = resizeArray( _rxFamilyCode, _RepeatCount );
      _BranchName = resizeArray( _BranchName, _RepeatCount );
      _SlsRepName = resizeArray( _SlsRepName, _RepeatCount );
      _FamilyName = resizeArray( _FamilyName, _RepeatCount );
      _BrokerName = resizeArray( _BrokerName, _RepeatCount );
      _ShGroupName = resizeArray( _ShGroupName, _RepeatCount );
      _rxFeeModelCode = resizeArray( _rxFeeModelCode, _RepeatCount );
      _ChargeOption = resizeArray( _ChargeOption, _RepeatCount );
      _AppliedMethod = resizeArray( _AppliedMethod, _RepeatCount );
      _FundList = resizeArray( _FundList, _RepeatCount );
      _ThresholdAmt = resizeArray( _ThresholdAmt, _RepeatCount );
      _ThresholdCurrency = resizeArray( _ThresholdCurrency, _RepeatCount );
      _DistribChannel = resizeArray( _DistribChannel, _RepeatCount );
      _FundLink = resizeArray( _FundLink, _RepeatCount );
      _TaxInclusive = resizeArray( _TaxInclusive, _RepeatCount );
      _FMLastProcDate = resizeArray( _FMLastProcDate, _RepeatCount );
      _ThrshldRecID = resizeArray( _ThrshldRecID, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _FeeID[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _rxFundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundFromCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClassFromCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxFeeCode[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _FeeType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Rate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MinFee[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MaxFee[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _StopDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _FreqMinMaxApp[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ChrgOnPrtlRed[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ChrgOnFullRed[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _Active[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _UserName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxCommGroup[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxBrokerCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AllowOverrideType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BasedOn[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Currency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _WhoPays[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxShGroup[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FeeParmRId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _rxBranchCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxSlsRepCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxFamilyCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BranchName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SlsRepName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FamilyName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BrokerName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ShGroupName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxFeeModelCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ChargeOption[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AppliedMethod[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundList[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ThresholdAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ThresholdCurrency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DistribChannel[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundLink[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TaxInclusive[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FMLastProcDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ThrshldRecID[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
      }
      

   }

}
      
