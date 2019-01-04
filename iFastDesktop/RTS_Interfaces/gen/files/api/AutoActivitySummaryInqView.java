
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * FundCom Auto Activity Summary Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/AutoActivitySummaryInq.doc">AutoActivitySummaryInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class AutoActivitySummaryInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Systematic Plan Indicator member array.
    */
   private String[] _rxSystematicIndicator = null;
   
   /**
    * Itermediary Code member array.
    */
   private String[] _IntermCode = null;
   
   /**
    * Auto Activity Status member array.
    */
   private String[] _ActivityStatus = null;
   
   /**
    * Fund Baycom Number member array.
    */
   private String[] _rxBaycom = null;
   
   /**
    * English Long Name of Fund member array.
    */
   private String[] _ElongName1 = null;
   
   /**
    * Transfer Account member array.
    */
   private String[] _AccountTo = null;
   
   /**
    * Transfer Fund Baycom Number member array.
    */
   private String[] _BaycomTo = null;
   
   /**
    * English Long Name of Fund To member array.
    */
   private String[] _ElongName2 = null;
   
   /**
    * Percentage, Units or Dollars member array.
    */
   private String[] _AmountType = null;
   
   /**
    * Amount member array.
    */
   private String[] _Amount = null;
   
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = null;
   
   /**
    * Frequency of Systematic member array.
    */
   private Integer[] _SystematicFreq = null;
   
   /**
    * Recid of Systematic member array.
    */
   private Integer[] _SystematicRid = null;
   

   /**
    * Constructs the AutoActivitySummaryInqView object.
    * 
    */
   public AutoActivitySummaryInqView()
   {
      super ( new AutoActivitySummaryInqRequest() );
   }

   /**
    * Constructs the AutoActivitySummaryInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AutoActivitySummaryInqView( String hostEncoding )
   {
      super ( new AutoActivitySummaryInqRequest( hostEncoding ) );
   }

   /**
    * Gets the AutoActivitySummaryInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AutoActivitySummaryInqRequest object.
    */
   public final AutoActivitySummaryInqRequest getRequest()
   {
      return (AutoActivitySummaryInqRequest)getIFastRequest();
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
    * Gets the Systematic Plan Indicator field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Systematic Plan Indicator or null.
    */
   public final String getrxSystematicIndicator( int index )
   {
      return _rxSystematicIndicator[index];
   }
    
   /**
    * Gets the Systematic Plan Indicator field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Systematic Plan Indicator or the specified default value.
    */
   public final String getrxSystematicIndicator( int index, String defaultValue )
   {
      return _rxSystematicIndicator[index] == null ? defaultValue : _rxSystematicIndicator[index];
   }
    
   /**
    * Gets the array of Systematic Plan Indicator fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Systematic Plan Indicator values.
    */
   public final String[] getrxSystematicIndicatorArray()
   {
      return _rxSystematicIndicator;
   }
    
   /**
    * Gets the Itermediary Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Itermediary Code or null.
    */
   public final String getIntermCode( int index )
   {
      return _IntermCode[index];
   }
    
   /**
    * Gets the Itermediary Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Itermediary Code or the specified default value.
    */
   public final String getIntermCode( int index, String defaultValue )
   {
      return _IntermCode[index] == null ? defaultValue : _IntermCode[index];
   }
    
   /**
    * Gets the array of Itermediary Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Itermediary Code values.
    */
   public final String[] getIntermCodeArray()
   {
      return _IntermCode;
   }
    
   /**
    * Gets the Auto Activity Status field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Auto Activity Status or null.
    */
   public final String getActivityStatus( int index )
   {
      return _ActivityStatus[index];
   }
    
   /**
    * Gets the Auto Activity Status field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Auto Activity Status or the specified default value.
    */
   public final String getActivityStatus( int index, String defaultValue )
   {
      return _ActivityStatus[index] == null ? defaultValue : _ActivityStatus[index];
   }
    
   /**
    * Gets the array of Auto Activity Status fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Auto Activity Status values.
    */
   public final String[] getActivityStatusArray()
   {
      return _ActivityStatus;
   }
    
   /**
    * Gets the Fund Baycom Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Baycom Number or null.
    */
   public final String getrxBaycom( int index )
   {
      return _rxBaycom[index];
   }
    
   /**
    * Gets the Fund Baycom Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Baycom Number or the specified default value.
    */
   public final String getrxBaycom( int index, String defaultValue )
   {
      return _rxBaycom[index] == null ? defaultValue : _rxBaycom[index];
   }
    
   /**
    * Gets the array of Fund Baycom Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Baycom Number values.
    */
   public final String[] getrxBaycomArray()
   {
      return _rxBaycom;
   }
    
   /**
    * Gets the English Long Name of Fund field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the English Long Name of Fund or null.
    */
   public final String getElongName1( int index )
   {
      return _ElongName1[index];
   }
    
   /**
    * Gets the English Long Name of Fund field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the English Long Name of Fund or the specified default value.
    */
   public final String getElongName1( int index, String defaultValue )
   {
      return _ElongName1[index] == null ? defaultValue : _ElongName1[index];
   }
    
   /**
    * Gets the array of English Long Name of Fund fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of English Long Name of Fund values.
    */
   public final String[] getElongName1Array()
   {
      return _ElongName1;
   }
    
   /**
    * Gets the Transfer Account field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transfer Account or null.
    */
   public final String getAccountTo( int index )
   {
      return _AccountTo[index];
   }
    
   /**
    * Gets the Transfer Account field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transfer Account or the specified default value.
    */
   public final String getAccountTo( int index, String defaultValue )
   {
      return _AccountTo[index] == null ? defaultValue : _AccountTo[index];
   }
    
   /**
    * Gets the array of Transfer Account fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transfer Account values.
    */
   public final String[] getAccountToArray()
   {
      return _AccountTo;
   }
    
   /**
    * Gets the Transfer Fund Baycom Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transfer Fund Baycom Number or null.
    */
   public final String getBaycomTo( int index )
   {
      return _BaycomTo[index];
   }
    
   /**
    * Gets the Transfer Fund Baycom Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transfer Fund Baycom Number or the specified default value.
    */
   public final String getBaycomTo( int index, String defaultValue )
   {
      return _BaycomTo[index] == null ? defaultValue : _BaycomTo[index];
   }
    
   /**
    * Gets the array of Transfer Fund Baycom Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transfer Fund Baycom Number values.
    */
   public final String[] getBaycomToArray()
   {
      return _BaycomTo;
   }
    
   /**
    * Gets the English Long Name of Fund To field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the English Long Name of Fund To or null.
    */
   public final String getElongName2( int index )
   {
      return _ElongName2[index];
   }
    
   /**
    * Gets the English Long Name of Fund To field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the English Long Name of Fund To or the specified default value.
    */
   public final String getElongName2( int index, String defaultValue )
   {
      return _ElongName2[index] == null ? defaultValue : _ElongName2[index];
   }
    
   /**
    * Gets the array of English Long Name of Fund To fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of English Long Name of Fund To values.
    */
   public final String[] getElongName2Array()
   {
      return _ElongName2;
   }
    
   /**
    * Gets the Percentage, Units or Dollars field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Percentage, Units or Dollars or null.
    */
   public final String getAmountType( int index )
   {
      return _AmountType[index];
   }
    
   /**
    * Gets the Percentage, Units or Dollars field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Percentage, Units or Dollars or the specified default value.
    */
   public final String getAmountType( int index, String defaultValue )
   {
      return _AmountType[index] == null ? defaultValue : _AmountType[index];
   }
    
   /**
    * Gets the array of Percentage, Units or Dollars fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Percentage, Units or Dollars values.
    */
   public final String[] getAmountTypeArray()
   {
      return _AmountType;
   }
    
   /**
    * Gets the Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Amount or null.
    */
   public final String getAmount( int index )
   {
      return _Amount[index];
   }
    
   /**
    * Gets the Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Amount or the specified default value.
    */
   public final String getAmount( int index, String defaultValue )
   {
      return _Amount[index] == null ? defaultValue : _Amount[index];
   }
    
   /**
    * Gets the array of Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Amount values.
    */
   public final String[] getAmountArray()
   {
      return _Amount;
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
    * Gets the Frequency of Systematic field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Frequency of Systematic or null.
    */
   public final Integer getSystematicFreq( int index )
   {
      return _SystematicFreq[index];
   }
    
   /**
    * Gets the Frequency of Systematic field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Frequency of Systematic or the specified default value.
    */
   public final int getSystematicFreq( int index, int defaultValue )
   {
      return _SystematicFreq[index] == null ? defaultValue : _SystematicFreq[index].intValue();
   }
    
   /**
    * Gets the array of Frequency of Systematic fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Frequency of Systematic values.
    */
   public final Integer[] getSystematicFreqArray()
   {
      return _SystematicFreq;
   }
    
   /**
    * Gets the Recid of Systematic field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Recid of Systematic or null.
    */
   public final Integer getSystematicRid( int index )
   {
      return _SystematicRid[index];
   }
    
   /**
    * Gets the Recid of Systematic field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Recid of Systematic or the specified default value.
    */
   public final int getSystematicRid( int index, int defaultValue )
   {
      return _SystematicRid[index] == null ? defaultValue : _SystematicRid[index].intValue();
   }
    
   /**
    * Gets the array of Recid of Systematic fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Recid of Systematic values.
    */
   public final Integer[] getSystematicRidArray()
   {
      return _SystematicRid;
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
      
      _rxSystematicIndicator = resizeArray( _rxSystematicIndicator, _RepeatCount );
      _IntermCode = resizeArray( _IntermCode, _RepeatCount );
      _ActivityStatus = resizeArray( _ActivityStatus, _RepeatCount );
      _rxBaycom = resizeArray( _rxBaycom, _RepeatCount );
      _ElongName1 = resizeArray( _ElongName1, _RepeatCount );
      _AccountTo = resizeArray( _AccountTo, _RepeatCount );
      _BaycomTo = resizeArray( _BaycomTo, _RepeatCount );
      _ElongName2 = resizeArray( _ElongName2, _RepeatCount );
      _AmountType = resizeArray( _AmountType, _RepeatCount );
      _Amount = resizeArray( _Amount, _RepeatCount );
      _EffectiveDate = resizeArray( _EffectiveDate, _RepeatCount );
      _SystematicFreq = resizeArray( _SystematicFreq, _RepeatCount );
      _SystematicRid = resizeArray( _SystematicRid, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxSystematicIndicator[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IntermCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ActivityStatus[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxBaycom[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ElongName1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AccountTo[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BaycomTo[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ElongName2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AmountType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Amount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _SystematicFreq[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _SystematicRid[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
      }
      

   }

}
      
