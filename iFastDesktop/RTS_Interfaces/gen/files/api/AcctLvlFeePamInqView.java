
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Account Level Fee Parms Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/AcctLvlFeePamInq.doc">AcctLvlFeePamInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class AcctLvlFeePamInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Account Fee Parm Recid member array.
    */
   private Integer[] _AcctFeeParmId = null;
   
   /**
    * Fund member array.
    */
   private String[] _FundCode = null;
   
   /**
    * Class member array.
    */
   private String[] _ClassCode = null;
   
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
   private Integer[] _FeeCode = null;
   
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
   private String[] _CommGroup = null;
   
   /**
    * Modify Permission member array.
    */
   private Boolean[] _ModPerm = null;
   
   /**
    * Broker Code member array.
    */
   private String[] _BrokerCode = null;
   
   /**
    * Based On member array.
    */
   private String[] _BasedOn = null;
   

   /**
    * Constructs the AcctLvlFeePamInqView object.
    * 
    */
   public AcctLvlFeePamInqView()
   {
      super ( new AcctLvlFeePamInqRequest() );
   }

   /**
    * Constructs the AcctLvlFeePamInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AcctLvlFeePamInqView( String hostEncoding )
   {
      super ( new AcctLvlFeePamInqRequest( hostEncoding ) );
   }

   /**
    * Gets the AcctLvlFeePamInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AcctLvlFeePamInqRequest object.
    */
   public final AcctLvlFeePamInqRequest getRequest()
   {
      return (AcctLvlFeePamInqRequest)getIFastRequest();
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
    * Gets the Account Fee Parm Recid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Fee Parm Recid or null.
    */
   public final Integer getAcctFeeParmId( int index )
   {
      return _AcctFeeParmId[index];
   }
    
   /**
    * Gets the Account Fee Parm Recid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Fee Parm Recid or the specified default value.
    */
   public final int getAcctFeeParmId( int index, int defaultValue )
   {
      return _AcctFeeParmId[index] == null ? defaultValue : _AcctFeeParmId[index].intValue();
   }
    
   /**
    * Gets the array of Account Fee Parm Recid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Fee Parm Recid values.
    */
   public final Integer[] getAcctFeeParmIdArray()
   {
      return _AcctFeeParmId;
   }
    
   /**
    * Gets the Fund field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund or null.
    */
   public final String getFundCode( int index )
   {
      return _FundCode[index];
   }
    
   /**
    * Gets the Fund field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund or the specified default value.
    */
   public final String getFundCode( int index, String defaultValue )
   {
      return _FundCode[index] == null ? defaultValue : _FundCode[index];
   }
    
   /**
    * Gets the array of Fund fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund values.
    */
   public final String[] getFundCodeArray()
   {
      return _FundCode;
   }
    
   /**
    * Gets the Class field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Class or null.
    */
   public final String getClassCode( int index )
   {
      return _ClassCode[index];
   }
    
   /**
    * Gets the Class field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class or the specified default value.
    */
   public final String getClassCode( int index, String defaultValue )
   {
      return _ClassCode[index] == null ? defaultValue : _ClassCode[index];
   }
    
   /**
    * Gets the array of Class fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Class values.
    */
   public final String[] getClassCodeArray()
   {
      return _ClassCode;
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
   public final Integer getFeeCode( int index )
   {
      return _FeeCode[index];
   }
    
   /**
    * Gets the Fee Code/ Fee Defn field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee Code/ Fee Defn or the specified default value.
    */
   public final int getFeeCode( int index, int defaultValue )
   {
      return _FeeCode[index] == null ? defaultValue : _FeeCode[index].intValue();
   }
    
   /**
    * Gets the array of Fee Code/ Fee Defn fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee Code/ Fee Defn values.
    */
   public final Integer[] getFeeCodeArray()
   {
      return _FeeCode;
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
   public final String getCommGroup( int index )
   {
      return _CommGroup[index];
   }
    
   /**
    * Gets the Commission Group field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commission Group or the specified default value.
    */
   public final String getCommGroup( int index, String defaultValue )
   {
      return _CommGroup[index] == null ? defaultValue : _CommGroup[index];
   }
    
   /**
    * Gets the array of Commission Group fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Commission Group values.
    */
   public final String[] getCommGroupArray()
   {
      return _CommGroup;
   }
    
   /**
    * Gets the Modify Permission field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Modify Permission or null.
    */
   public final Boolean getModPerm( int index )
   {
      return _ModPerm[index];
   }
    
   /**
    * Gets the Modify Permission field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Modify Permission or the specified default value.
    */
   public final boolean getModPerm( int index, boolean defaultValue )
   {
      return _ModPerm[index] == null ? defaultValue : _ModPerm[index].booleanValue();
   }
    
   /**
    * Gets the array of Modify Permission fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Modify Permission values.
    */
   public final Boolean[] getModPermArray()
   {
      return _ModPerm;
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
    * Gets the Based On field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Based On or null.
    */
   public final String getBasedOn( int index )
   {
      return _BasedOn[index];
   }
    
   /**
    * Gets the Based On field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Based On or the specified default value.
    */
   public final String getBasedOn( int index, String defaultValue )
   {
      return _BasedOn[index] == null ? defaultValue : _BasedOn[index];
   }
    
   /**
    * Gets the array of Based On fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Based On values.
    */
   public final String[] getBasedOnArray()
   {
      return _BasedOn;
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
      
      _AcctFeeParmId = resizeArray( _AcctFeeParmId, _RepeatCount );
      _FundCode = resizeArray( _FundCode, _RepeatCount );
      _ClassCode = resizeArray( _ClassCode, _RepeatCount );
      _FundFromCode = resizeArray( _FundFromCode, _RepeatCount );
      _ClassFromCode = resizeArray( _ClassFromCode, _RepeatCount );
      _FeeCode = resizeArray( _FeeCode, _RepeatCount );
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
      _CommGroup = resizeArray( _CommGroup, _RepeatCount );
      _ModPerm = resizeArray( _ModPerm, _RepeatCount );
      _BrokerCode = resizeArray( _BrokerCode, _RepeatCount );
      _BasedOn = resizeArray( _BasedOn, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _AcctFeeParmId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _FundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundFromCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClassFromCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FeeCode[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
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
         _CommGroup[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModPerm[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _BrokerCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BasedOn[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
