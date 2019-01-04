
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Fund Level Fee Parms Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/FundLvlFeeInq.doc">FundLvlFeeInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class FundLvlFeeInqView extends IFastView implements Serializable
{

   /**
    * Stop Date member variable.
    */
   private Date _StopDate = null;
   
   /**
    * Fee Type member variable.
    */
   private String _FeeType = null;
   
   /**
    * Fee / Rate member variable.
    */
   private String _Rate = null;
   
   /**
    * Minimum Fee member variable.
    */
   private String _MinFee = null;
   
   /**
    * Maximum Fee member variable.
    */
   private String _MaxFee = null;
   
   /**
    * Allow overwrite at account level member variable.
    */
   private String _AllowOverwrite = null;
   
   /**
    * Recid of Fee Parameter record member variable.
    */
   private Integer _FeeParmRId = null;
   
   /**
    * Fund member variable.
    */
   private String _rxFundCode = null;
   
   /**
    * Class member variable.
    */
   private String _rxClassCode = null;
   
   /**
    * Fee Code member variable.
    */
   private Integer _rxFeeCode = null;
   
   /**
    * Effective Date member variable.
    */
   private Date _rxEffectiveDate = null;
   
   /**
    * Commission Group member variable.
    */
   private String _rxCommGroup = null;
   
   /**
    * flag indicating if overlapping records exist for the specific date range member variable.
    */
   private Boolean _DuplicateExist = null;
   
   /**
    * Fee Model Code member variable.
    */
   private String _rxFeeModelCode = null;
   
   /**
    * Charge Option member variable.
    */
   private String _ChargeOption = null;
   
   /**
    * Fee Currency member variable.
    */
   private String _FeeCurrency = null;
   
   /**
    * Distribution Channel member variable.
    */
   private String _rxDistribChannel = null;
   
   private int _RepeatCount = 0;
   
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
    * Recid of fee-parm record member array.
    */
   private Integer[] _ScaleFeeParmRId = null;
   
   /**
    * Effective Date member array.
    */
   private Date[] _ScaleEffectiveDate = null;
   
   /**
    * Minimum Fee member array.
    */
   private String[] _ScaleMinFee = null;
   
   /**
    * Maximum Fee member array.
    */
   private String[] _ScaleMaxFee = null;
   

   /**
    * Constructs the FundLvlFeeInqView object.
    * 
    */
   public FundLvlFeeInqView()
   {
      super ( new FundLvlFeeInqRequest() );
   }

   /**
    * Constructs the FundLvlFeeInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public FundLvlFeeInqView( String hostEncoding )
   {
      super ( new FundLvlFeeInqRequest( hostEncoding ) );
   }

   /**
    * Gets the FundLvlFeeInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The FundLvlFeeInqRequest object.
    */
   public final FundLvlFeeInqRequest getRequest()
   {
      return (FundLvlFeeInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Stop Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Stop Date or null.
    */
   public final Date getStopDate()
   {
      return _StopDate;
   }
	
   /**
    * Gets the Stop Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Date or the specified default value.
    */
   public final Date getStopDate( Date defaultValue )
   {
      return _StopDate == null ? defaultValue : _StopDate;
   }
                  
   /**
    * Gets the Fee Type field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Fee Type or null.
    */
   public final String getFeeType()
   {
      return _FeeType;
   }
	
   /**
    * Gets the Fee Type field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee Type or the specified default value.
    */
   public final String getFeeType( String defaultValue )
   {
      return _FeeType == null ? defaultValue : _FeeType;
   }
                  
   /**
    * Gets the Fee / Rate field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Fee / Rate or null.
    */
   public final String getRate()
   {
      return _Rate;
   }
	
   /**
    * Gets the Fee / Rate field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee / Rate or the specified default value.
    */
   public final String getRate( String defaultValue )
   {
      return _Rate == null ? defaultValue : _Rate;
   }
                  
   /**
    * Gets the Minimum Fee field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Minimum Fee or null.
    */
   public final String getMinFee()
   {
      return _MinFee;
   }
	
   /**
    * Gets the Minimum Fee field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Minimum Fee or the specified default value.
    */
   public final String getMinFee( String defaultValue )
   {
      return _MinFee == null ? defaultValue : _MinFee;
   }
                  
   /**
    * Gets the Maximum Fee field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Maximum Fee or null.
    */
   public final String getMaxFee()
   {
      return _MaxFee;
   }
	
   /**
    * Gets the Maximum Fee field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Maximum Fee or the specified default value.
    */
   public final String getMaxFee( String defaultValue )
   {
      return _MaxFee == null ? defaultValue : _MaxFee;
   }
                  
   /**
    * Gets the Allow overwrite at account level field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Allow overwrite at account level or null.
    */
   public final String getAllowOverwrite()
   {
      return _AllowOverwrite;
   }
	
   /**
    * Gets the Allow overwrite at account level field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Allow overwrite at account level or the specified default value.
    */
   public final String getAllowOverwrite( String defaultValue )
   {
      return _AllowOverwrite == null ? defaultValue : _AllowOverwrite;
   }
                  
   /**
    * Gets the Recid of Fee Parameter record field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Recid of Fee Parameter record or null.
    */
   public final Integer getFeeParmRId()
   {
      return _FeeParmRId;
   }
	
   /**
    * Gets the Recid of Fee Parameter record field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Recid of Fee Parameter record or the specified default value.
    */
   public final int getFeeParmRId( int defaultValue )
   {
      return _FeeParmRId == null ? defaultValue : _FeeParmRId.intValue();
   }
                  
   /**
    * Gets the Fund field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Fund or null.
    */
   public final String getrxFundCode()
   {
      return _rxFundCode;
   }
	
   /**
    * Gets the Fund field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund or the specified default value.
    */
   public final String getrxFundCode( String defaultValue )
   {
      return _rxFundCode == null ? defaultValue : _rxFundCode;
   }
                  
   /**
    * Gets the Class field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Class or null.
    */
   public final String getrxClassCode()
   {
      return _rxClassCode;
   }
	
   /**
    * Gets the Class field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class or the specified default value.
    */
   public final String getrxClassCode( String defaultValue )
   {
      return _rxClassCode == null ? defaultValue : _rxClassCode;
   }
                  
   /**
    * Gets the Fee Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Fee Code or null.
    */
   public final Integer getrxFeeCode()
   {
      return _rxFeeCode;
   }
	
   /**
    * Gets the Fee Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee Code or the specified default value.
    */
   public final int getrxFeeCode( int defaultValue )
   {
      return _rxFeeCode == null ? defaultValue : _rxFeeCode.intValue();
   }
                  
   /**
    * Gets the Effective Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Effective Date or null.
    */
   public final Date getrxEffectiveDate()
   {
      return _rxEffectiveDate;
   }
	
   /**
    * Gets the Effective Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Effective Date or the specified default value.
    */
   public final Date getrxEffectiveDate( Date defaultValue )
   {
      return _rxEffectiveDate == null ? defaultValue : _rxEffectiveDate;
   }
                  
   /**
    * Gets the Commission Group field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Commission Group or null.
    */
   public final String getrxCommGroup()
   {
      return _rxCommGroup;
   }
	
   /**
    * Gets the Commission Group field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commission Group or the specified default value.
    */
   public final String getrxCommGroup( String defaultValue )
   {
      return _rxCommGroup == null ? defaultValue : _rxCommGroup;
   }
                  
   /**
    * Gets the flag indicating if overlapping records exist for the specific date range field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the flag indicating if overlapping records exist for the specific date range or null.
    */
   public final Boolean getDuplicateExist()
   {
      return _DuplicateExist;
   }
	
   /**
    * Gets the flag indicating if overlapping records exist for the specific date range field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the flag indicating if overlapping records exist for the specific date range or the specified default value.
    */
   public final boolean getDuplicateExist( boolean defaultValue )
   {
      return _DuplicateExist == null ? defaultValue : _DuplicateExist.booleanValue();
   }
                  
   /**
    * Gets the Fee Model Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Fee Model Code or null.
    */
   public final String getrxFeeModelCode()
   {
      return _rxFeeModelCode;
   }
	
   /**
    * Gets the Fee Model Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee Model Code or the specified default value.
    */
   public final String getrxFeeModelCode( String defaultValue )
   {
      return _rxFeeModelCode == null ? defaultValue : _rxFeeModelCode;
   }
                  
   /**
    * Gets the Charge Option field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Charge Option or null.
    */
   public final String getChargeOption()
   {
      return _ChargeOption;
   }
	
   /**
    * Gets the Charge Option field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Charge Option or the specified default value.
    */
   public final String getChargeOption( String defaultValue )
   {
      return _ChargeOption == null ? defaultValue : _ChargeOption;
   }
                  
   /**
    * Gets the Fee Currency field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Fee Currency or null.
    */
   public final String getFeeCurrency()
   {
      return _FeeCurrency;
   }
	
   /**
    * Gets the Fee Currency field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee Currency or the specified default value.
    */
   public final String getFeeCurrency( String defaultValue )
   {
      return _FeeCurrency == null ? defaultValue : _FeeCurrency;
   }
                  
   /**
    * Gets the Distribution Channel field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Distribution Channel or null.
    */
   public final String getrxDistribChannel()
   {
      return _rxDistribChannel;
   }
	
   /**
    * Gets the Distribution Channel field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Distribution Channel or the specified default value.
    */
   public final String getrxDistribChannel( String defaultValue )
   {
      return _rxDistribChannel == null ? defaultValue : _rxDistribChannel;
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
    * Gets the Recid of fee-parm record field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Recid of fee-parm record or null.
    */
   public final Integer getScaleFeeParmRId( int index )
   {
      return _ScaleFeeParmRId[index];
   }
    
   /**
    * Gets the Recid of fee-parm record field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Recid of fee-parm record or the specified default value.
    */
   public final int getScaleFeeParmRId( int index, int defaultValue )
   {
      return _ScaleFeeParmRId[index] == null ? defaultValue : _ScaleFeeParmRId[index].intValue();
   }
    
   /**
    * Gets the array of Recid of fee-parm record fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Recid of fee-parm record values.
    */
   public final Integer[] getScaleFeeParmRIdArray()
   {
      return _ScaleFeeParmRId;
   }
    
   /**
    * Gets the Effective Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Effective Date or null.
    */
   public final Date getScaleEffectiveDate( int index )
   {
      return _ScaleEffectiveDate[index];
   }
    
   /**
    * Gets the Effective Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Effective Date or the specified default value.
    */
   public final Date getScaleEffectiveDate( int index, Date defaultValue )
   {
      return _ScaleEffectiveDate[index] == null ? defaultValue : _ScaleEffectiveDate[index];
   }
    
   /**
    * Gets the array of Effective Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Effective Date values.
    */
   public final Date[] getScaleEffectiveDateArray()
   {
      return _ScaleEffectiveDate;
   }
    
   /**
    * Gets the Minimum Fee field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Minimum Fee or null.
    */
   public final String getScaleMinFee( int index )
   {
      return _ScaleMinFee[index];
   }
    
   /**
    * Gets the Minimum Fee field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Minimum Fee or the specified default value.
    */
   public final String getScaleMinFee( int index, String defaultValue )
   {
      return _ScaleMinFee[index] == null ? defaultValue : _ScaleMinFee[index];
   }
    
   /**
    * Gets the array of Minimum Fee fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Minimum Fee values.
    */
   public final String[] getScaleMinFeeArray()
   {
      return _ScaleMinFee;
   }
    
   /**
    * Gets the Maximum Fee field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Maximum Fee or null.
    */
   public final String getScaleMaxFee( int index )
   {
      return _ScaleMaxFee[index];
   }
    
   /**
    * Gets the Maximum Fee field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Maximum Fee or the specified default value.
    */
   public final String getScaleMaxFee( int index, String defaultValue )
   {
      return _ScaleMaxFee[index] == null ? defaultValue : _ScaleMaxFee[index];
   }
    
   /**
    * Gets the array of Maximum Fee fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Maximum Fee values.
    */
   public final String[] getScaleMaxFeeArray()
   {
      return _ScaleMaxFee;
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
      _StopDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _FeeType = responseBuffer.decodeString(responseBuffer.getNextField());
      _Rate = responseBuffer.decodeString(responseBuffer.getNextField());
      _MinFee = responseBuffer.decodeString(responseBuffer.getNextField());
      _MaxFee = responseBuffer.decodeString(responseBuffer.getNextField());
      _AllowOverwrite = responseBuffer.decodeString(responseBuffer.getNextField());
      _FeeParmRId = responseBuffer.decodeInteger(responseBuffer.getNextField());
      decodeMoreAvailableField( responseBuffer );
      decodeNextKeyField( responseBuffer );
      _rxFundCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _rxClassCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _rxFeeCode = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _rxEffectiveDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _rxCommGroup = responseBuffer.decodeString(responseBuffer.getNextField());
      _DuplicateExist = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _rxFeeModelCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _ChargeOption = responseBuffer.decodeString(responseBuffer.getNextField());
      _FeeCurrency = responseBuffer.decodeString(responseBuffer.getNextField());
      _rxDistribChannel = responseBuffer.decodeString(responseBuffer.getNextField());
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _ScaleRate = resizeArray( _ScaleRate, _RepeatCount );
      _UpperBound = resizeArray( _UpperBound, _RepeatCount );
      _LowerBound = resizeArray( _LowerBound, _RepeatCount );
      _Level = resizeArray( _Level, _RepeatCount );
      _ScaleFeeParmRId = resizeArray( _ScaleFeeParmRId, _RepeatCount );
      _ScaleEffectiveDate = resizeArray( _ScaleEffectiveDate, _RepeatCount );
      _ScaleMinFee = resizeArray( _ScaleMinFee, _RepeatCount );
      _ScaleMaxFee = resizeArray( _ScaleMaxFee, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _ScaleRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UpperBound[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LowerBound[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Level[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ScaleFeeParmRId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ScaleEffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ScaleMinFee[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ScaleMaxFee[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
