
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * System Level Fee Scale Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/SysLvlFeeSclInq.doc">SysLvlFeeSclInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class SysLvlFeeSclInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Fee ID member array.
    */
   private Integer[] _rxFeeID = null;
   
   /**
    * Scale Rate member array.
    */
   private String[] _ScaleRate = null;
   
   /**
    * Upper Bound member array.
    */
   private String[] _UpperBound = null;
   
   /**
    * Lower Bound member array.
    */
   private String[] _LowerBound = null;
   
   /**
    * Level member array.
    */
   private Integer[] _Level = null;
   
   /**
    * Scale Effective Date member array.
    */
   private Date[] _ScaleEffectiveDate = null;
   
   /**
    * Scale Detl Recid member array.
    */
   private Integer[] _ScaleDetlRid = null;
   
   /**
    * Minimum Fee member array.
    */
   private String[] _MinFee = null;
   
   /**
    * Maximum Fee member array.
    */
   private String[] _MaxFee = null;
   
   /**
    * Process Date member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * Fund member array.
    */
   private String[] _FundCode = null;
   
   /**
    * Class member array.
    */
   private String[] _ClassCode = null;
   
   /**
    * Fee Definition/ Code member array.
    */
   private Integer[] _FeeCode = null;
   
   /**
    * Group Code member array.
    */
   private String[] _GroupCode = null;
   
   /**
    * Investment Term member array.
    */
   private Integer[] _InvestTerm = null;
   
   /**
    * Record Type member array.
    */
   private String[] _RecType = null;
   
   /**
    * Threshold Range ID member array.
    */
   private Integer[] _ThrshldRangeID = null;
   
   /**
    * Threshold Upper member array.
    */
   private String[] _ThrshldUpper = null;
   
   /**
    * Threshold Lower member array.
    */
   private String[] _ThrshldLower = null;
   
   /**
    * Threshold Level member array.
    */
   private Integer[] _ThrshldLevel = null;
   
   /**
    * Thresholdrange recid member array.
    */
   private Integer[] _ThrshldRecID = null;
   
   /**
    * ThresholdRange Mod User member array.
    */
   private String[] _ThrshldModUser = null;
   
   /**
    * ThresholdRange Mod Date member array.
    */
   private Date[] _ThrshldModDate = null;
   
   /**
    * ThresholdRange Version Number member array.
    */
   private Integer[] _ThrshldVersion = null;
   
   /**
    * ThresholdRange Process Date member array.
    */
   private Date[] _ThrshldProcDate = null;
   
   /**
    * ThresholdRange Username member array.
    */
   private String[] _ThrshldUserName = null;
   

   /**
    * Constructs the SysLvlFeeSclInqView object.
    * 
    */
   public SysLvlFeeSclInqView()
   {
      super ( new SysLvlFeeSclInqRequest() );
   }

   /**
    * Constructs the SysLvlFeeSclInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public SysLvlFeeSclInqView( String hostEncoding )
   {
      super ( new SysLvlFeeSclInqRequest( hostEncoding ) );
   }

   /**
    * Gets the SysLvlFeeSclInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The SysLvlFeeSclInqRequest object.
    */
   public final SysLvlFeeSclInqRequest getRequest()
   {
      return (SysLvlFeeSclInqRequest)getIFastRequest();
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
   public final Integer getrxFeeID( int index )
   {
      return _rxFeeID[index];
   }
    
   /**
    * Gets the Fee ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee ID or the specified default value.
    */
   public final int getrxFeeID( int index, int defaultValue )
   {
      return _rxFeeID[index] == null ? defaultValue : _rxFeeID[index].intValue();
   }
    
   /**
    * Gets the array of Fee ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee ID values.
    */
   public final Integer[] getrxFeeIDArray()
   {
      return _rxFeeID;
   }
    
   /**
    * Gets the Scale Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Scale Rate or null.
    */
   public final String getScaleRate( int index )
   {
      return _ScaleRate[index];
   }
    
   /**
    * Gets the Scale Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Scale Rate or the specified default value.
    */
   public final String getScaleRate( int index, String defaultValue )
   {
      return _ScaleRate[index] == null ? defaultValue : _ScaleRate[index];
   }
    
   /**
    * Gets the array of Scale Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Scale Rate values.
    */
   public final String[] getScaleRateArray()
   {
      return _ScaleRate;
   }
    
   /**
    * Gets the Upper Bound field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Upper Bound or null.
    */
   public final String getUpperBound( int index )
   {
      return _UpperBound[index];
   }
    
   /**
    * Gets the Upper Bound field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Upper Bound or the specified default value.
    */
   public final String getUpperBound( int index, String defaultValue )
   {
      return _UpperBound[index] == null ? defaultValue : _UpperBound[index];
   }
    
   /**
    * Gets the array of Upper Bound fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Upper Bound values.
    */
   public final String[] getUpperBoundArray()
   {
      return _UpperBound;
   }
    
   /**
    * Gets the Lower Bound field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Lower Bound or null.
    */
   public final String getLowerBound( int index )
   {
      return _LowerBound[index];
   }
    
   /**
    * Gets the Lower Bound field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Lower Bound or the specified default value.
    */
   public final String getLowerBound( int index, String defaultValue )
   {
      return _LowerBound[index] == null ? defaultValue : _LowerBound[index];
   }
    
   /**
    * Gets the array of Lower Bound fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Lower Bound values.
    */
   public final String[] getLowerBoundArray()
   {
      return _LowerBound;
   }
    
   /**
    * Gets the Level field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Level or null.
    */
   public final Integer getLevel( int index )
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
   public final int getLevel( int index, int defaultValue )
   {
      return _Level[index] == null ? defaultValue : _Level[index].intValue();
   }
    
   /**
    * Gets the array of Level fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Level values.
    */
   public final Integer[] getLevelArray()
   {
      return _Level;
   }
    
   /**
    * Gets the Scale Effective Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Scale Effective Date or null.
    */
   public final Date getScaleEffectiveDate( int index )
   {
      return _ScaleEffectiveDate[index];
   }
    
   /**
    * Gets the Scale Effective Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Scale Effective Date or the specified default value.
    */
   public final Date getScaleEffectiveDate( int index, Date defaultValue )
   {
      return _ScaleEffectiveDate[index] == null ? defaultValue : _ScaleEffectiveDate[index];
   }
    
   /**
    * Gets the array of Scale Effective Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Scale Effective Date values.
    */
   public final Date[] getScaleEffectiveDateArray()
   {
      return _ScaleEffectiveDate;
   }
    
   /**
    * Gets the Scale Detl Recid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Scale Detl Recid or null.
    */
   public final Integer getScaleDetlRid( int index )
   {
      return _ScaleDetlRid[index];
   }
    
   /**
    * Gets the Scale Detl Recid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Scale Detl Recid or the specified default value.
    */
   public final int getScaleDetlRid( int index, int defaultValue )
   {
      return _ScaleDetlRid[index] == null ? defaultValue : _ScaleDetlRid[index].intValue();
   }
    
   /**
    * Gets the array of Scale Detl Recid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Scale Detl Recid values.
    */
   public final Integer[] getScaleDetlRidArray()
   {
      return _ScaleDetlRid;
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
    * Gets the Fee Definition/ Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fee Definition/ Code or null.
    */
   public final Integer getFeeCode( int index )
   {
      return _FeeCode[index];
   }
    
   /**
    * Gets the Fee Definition/ Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee Definition/ Code or the specified default value.
    */
   public final int getFeeCode( int index, int defaultValue )
   {
      return _FeeCode[index] == null ? defaultValue : _FeeCode[index].intValue();
   }
    
   /**
    * Gets the array of Fee Definition/ Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee Definition/ Code values.
    */
   public final Integer[] getFeeCodeArray()
   {
      return _FeeCode;
   }
    
   /**
    * Gets the Group Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Group Code or null.
    */
   public final String getGroupCode( int index )
   {
      return _GroupCode[index];
   }
    
   /**
    * Gets the Group Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Group Code or the specified default value.
    */
   public final String getGroupCode( int index, String defaultValue )
   {
      return _GroupCode[index] == null ? defaultValue : _GroupCode[index];
   }
    
   /**
    * Gets the array of Group Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Group Code values.
    */
   public final String[] getGroupCodeArray()
   {
      return _GroupCode;
   }
    
   /**
    * Gets the Investment Term field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Investment Term or null.
    */
   public final Integer getInvestTerm( int index )
   {
      return _InvestTerm[index];
   }
    
   /**
    * Gets the Investment Term field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Investment Term or the specified default value.
    */
   public final int getInvestTerm( int index, int defaultValue )
   {
      return _InvestTerm[index] == null ? defaultValue : _InvestTerm[index].intValue();
   }
    
   /**
    * Gets the array of Investment Term fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Investment Term values.
    */
   public final Integer[] getInvestTermArray()
   {
      return _InvestTerm;
   }
    
   /**
    * Gets the Record Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Record Type or null.
    */
   public final String getRecType( int index )
   {
      return _RecType[index];
   }
    
   /**
    * Gets the Record Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Record Type or the specified default value.
    */
   public final String getRecType( int index, String defaultValue )
   {
      return _RecType[index] == null ? defaultValue : _RecType[index];
   }
    
   /**
    * Gets the array of Record Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Record Type values.
    */
   public final String[] getRecTypeArray()
   {
      return _RecType;
   }
    
   /**
    * Gets the Threshold Range ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Threshold Range ID or null.
    */
   public final Integer getThrshldRangeID( int index )
   {
      return _ThrshldRangeID[index];
   }
    
   /**
    * Gets the Threshold Range ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Threshold Range ID or the specified default value.
    */
   public final int getThrshldRangeID( int index, int defaultValue )
   {
      return _ThrshldRangeID[index] == null ? defaultValue : _ThrshldRangeID[index].intValue();
   }
    
   /**
    * Gets the array of Threshold Range ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Threshold Range ID values.
    */
   public final Integer[] getThrshldRangeIDArray()
   {
      return _ThrshldRangeID;
   }
    
   /**
    * Gets the Threshold Upper field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Threshold Upper or null.
    */
   public final String getThrshldUpper( int index )
   {
      return _ThrshldUpper[index];
   }
    
   /**
    * Gets the Threshold Upper field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Threshold Upper or the specified default value.
    */
   public final String getThrshldUpper( int index, String defaultValue )
   {
      return _ThrshldUpper[index] == null ? defaultValue : _ThrshldUpper[index];
   }
    
   /**
    * Gets the array of Threshold Upper fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Threshold Upper values.
    */
   public final String[] getThrshldUpperArray()
   {
      return _ThrshldUpper;
   }
    
   /**
    * Gets the Threshold Lower field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Threshold Lower or null.
    */
   public final String getThrshldLower( int index )
   {
      return _ThrshldLower[index];
   }
    
   /**
    * Gets the Threshold Lower field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Threshold Lower or the specified default value.
    */
   public final String getThrshldLower( int index, String defaultValue )
   {
      return _ThrshldLower[index] == null ? defaultValue : _ThrshldLower[index];
   }
    
   /**
    * Gets the array of Threshold Lower fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Threshold Lower values.
    */
   public final String[] getThrshldLowerArray()
   {
      return _ThrshldLower;
   }
    
   /**
    * Gets the Threshold Level field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Threshold Level or null.
    */
   public final Integer getThrshldLevel( int index )
   {
      return _ThrshldLevel[index];
   }
    
   /**
    * Gets the Threshold Level field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Threshold Level or the specified default value.
    */
   public final int getThrshldLevel( int index, int defaultValue )
   {
      return _ThrshldLevel[index] == null ? defaultValue : _ThrshldLevel[index].intValue();
   }
    
   /**
    * Gets the array of Threshold Level fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Threshold Level values.
    */
   public final Integer[] getThrshldLevelArray()
   {
      return _ThrshldLevel;
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
    * Gets the ThresholdRange Mod User field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ThresholdRange Mod User or null.
    */
   public final String getThrshldModUser( int index )
   {
      return _ThrshldModUser[index];
   }
    
   /**
    * Gets the ThresholdRange Mod User field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ThresholdRange Mod User or the specified default value.
    */
   public final String getThrshldModUser( int index, String defaultValue )
   {
      return _ThrshldModUser[index] == null ? defaultValue : _ThrshldModUser[index];
   }
    
   /**
    * Gets the array of ThresholdRange Mod User fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ThresholdRange Mod User values.
    */
   public final String[] getThrshldModUserArray()
   {
      return _ThrshldModUser;
   }
    
   /**
    * Gets the ThresholdRange Mod Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ThresholdRange Mod Date or null.
    */
   public final Date getThrshldModDate( int index )
   {
      return _ThrshldModDate[index];
   }
    
   /**
    * Gets the ThresholdRange Mod Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ThresholdRange Mod Date or the specified default value.
    */
   public final Date getThrshldModDate( int index, Date defaultValue )
   {
      return _ThrshldModDate[index] == null ? defaultValue : _ThrshldModDate[index];
   }
    
   /**
    * Gets the array of ThresholdRange Mod Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ThresholdRange Mod Date values.
    */
   public final Date[] getThrshldModDateArray()
   {
      return _ThrshldModDate;
   }
    
   /**
    * Gets the ThresholdRange Version Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ThresholdRange Version Number or null.
    */
   public final Integer getThrshldVersion( int index )
   {
      return _ThrshldVersion[index];
   }
    
   /**
    * Gets the ThresholdRange Version Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ThresholdRange Version Number or the specified default value.
    */
   public final int getThrshldVersion( int index, int defaultValue )
   {
      return _ThrshldVersion[index] == null ? defaultValue : _ThrshldVersion[index].intValue();
   }
    
   /**
    * Gets the array of ThresholdRange Version Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ThresholdRange Version Number values.
    */
   public final Integer[] getThrshldVersionArray()
   {
      return _ThrshldVersion;
   }
    
   /**
    * Gets the ThresholdRange Process Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ThresholdRange Process Date or null.
    */
   public final Date getThrshldProcDate( int index )
   {
      return _ThrshldProcDate[index];
   }
    
   /**
    * Gets the ThresholdRange Process Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ThresholdRange Process Date or the specified default value.
    */
   public final Date getThrshldProcDate( int index, Date defaultValue )
   {
      return _ThrshldProcDate[index] == null ? defaultValue : _ThrshldProcDate[index];
   }
    
   /**
    * Gets the array of ThresholdRange Process Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ThresholdRange Process Date values.
    */
   public final Date[] getThrshldProcDateArray()
   {
      return _ThrshldProcDate;
   }
    
   /**
    * Gets the ThresholdRange Username field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ThresholdRange Username or null.
    */
   public final String getThrshldUserName( int index )
   {
      return _ThrshldUserName[index];
   }
    
   /**
    * Gets the ThresholdRange Username field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ThresholdRange Username or the specified default value.
    */
   public final String getThrshldUserName( int index, String defaultValue )
   {
      return _ThrshldUserName[index] == null ? defaultValue : _ThrshldUserName[index];
   }
    
   /**
    * Gets the array of ThresholdRange Username fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ThresholdRange Username values.
    */
   public final String[] getThrshldUserNameArray()
   {
      return _ThrshldUserName;
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
      
      _rxFeeID = resizeArray( _rxFeeID, _RepeatCount );
      _ScaleRate = resizeArray( _ScaleRate, _RepeatCount );
      _UpperBound = resizeArray( _UpperBound, _RepeatCount );
      _LowerBound = resizeArray( _LowerBound, _RepeatCount );
      _Level = resizeArray( _Level, _RepeatCount );
      _ScaleEffectiveDate = resizeArray( _ScaleEffectiveDate, _RepeatCount );
      _ScaleDetlRid = resizeArray( _ScaleDetlRid, _RepeatCount );
      _MinFee = resizeArray( _MinFee, _RepeatCount );
      _MaxFee = resizeArray( _MaxFee, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _FundCode = resizeArray( _FundCode, _RepeatCount );
      _ClassCode = resizeArray( _ClassCode, _RepeatCount );
      _FeeCode = resizeArray( _FeeCode, _RepeatCount );
      _GroupCode = resizeArray( _GroupCode, _RepeatCount );
      _InvestTerm = resizeArray( _InvestTerm, _RepeatCount );
      _RecType = resizeArray( _RecType, _RepeatCount );
      _ThrshldRangeID = resizeArray( _ThrshldRangeID, _RepeatCount );
      _ThrshldUpper = resizeArray( _ThrshldUpper, _RepeatCount );
      _ThrshldLower = resizeArray( _ThrshldLower, _RepeatCount );
      _ThrshldLevel = resizeArray( _ThrshldLevel, _RepeatCount );
      _ThrshldRecID = resizeArray( _ThrshldRecID, _RepeatCount );
      _ThrshldModUser = resizeArray( _ThrshldModUser, _RepeatCount );
      _ThrshldModDate = resizeArray( _ThrshldModDate, _RepeatCount );
      _ThrshldVersion = resizeArray( _ThrshldVersion, _RepeatCount );
      _ThrshldProcDate = resizeArray( _ThrshldProcDate, _RepeatCount );
      _ThrshldUserName = resizeArray( _ThrshldUserName, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxFeeID[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ScaleRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UpperBound[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LowerBound[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Level[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ScaleEffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ScaleDetlRid[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _MinFee[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MaxFee[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _FundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FeeCode[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _GroupCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _InvestTerm[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _RecType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ThrshldRangeID[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ThrshldUpper[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ThrshldLower[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ThrshldLevel[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ThrshldRecID[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ThrshldModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ThrshldModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ThrshldVersion[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ThrshldProcDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ThrshldUserName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
