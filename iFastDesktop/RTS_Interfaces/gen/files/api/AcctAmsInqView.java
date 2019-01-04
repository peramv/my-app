
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Acount AMS Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/AcctAmsInq.doc">AcctAmsInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class AcctAmsInqView extends IFastView implements Serializable
{

   /**
    * Duplicate Exist member variable.
    */
   private Boolean _DuplicateExist = null;
   
   private int _RepeatCount = 0;
   
   /**
    * AMS Code member array.
    */
   private String[] _rxAMSCode = null;
   
   /**
    * AMS Type member array.
    */
   private String[] _rxAMSType = null;
   
   /**
    * Effective Date member array.
    */
   private Date[] _rxDeff = null;
   
   /**
    * Stop Date member array.
    */
   private Date[] _rxStopDate = null;
   
   /**
    * Next Process Date member array.
    */
   private Date[] _NextProcDate = null;
   
   /**
    * Last Process Date member array.
    */
   private Date[] _LastProcDate = null;
   
   /**
    * Frequency Override member array.
    */
   private Integer[] _FreqOverride = null;
   
   /**
    * Sched SetUp Freq ID member array.
    */
   private Integer[] _SchedSetupFreqID = null;
   
   /**
    * AMS Stat member array.
    */
   private Integer[] _AMSStat = null;
   
   /**
    * AMS Activation Date member array.
    */
   private Date[] _ActivationDate = null;
   
   /**
    * Acct-AMS RID member array.
    */
   private Integer[] _AcctAMSRID = null;
   
   /**
    * Process Date member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * UserName member array.
    */
   private String[] _UserName = null;
   
   /**
    * Modification Date member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * Mod User member array.
    */
   private String[] _ModUser = null;
   
   /**
    * Threshold Percentage member array.
    */
   private String[] _ThresholdPrcnt = null;
   
   /**
    * Currency member array.
    */
   private String[] _Currency = null;
   

   /**
    * Constructs the AcctAmsInqView object.
    * 
    */
   public AcctAmsInqView()
   {
      super ( new AcctAmsInqRequest() );
   }

   /**
    * Constructs the AcctAmsInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AcctAmsInqView( String hostEncoding )
   {
      super ( new AcctAmsInqRequest( hostEncoding ) );
   }

   /**
    * Gets the AcctAmsInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AcctAmsInqRequest object.
    */
   public final AcctAmsInqRequest getRequest()
   {
      return (AcctAmsInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Duplicate Exist field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Duplicate Exist or null.
    */
   public final Boolean getDuplicateExist()
   {
      return _DuplicateExist;
   }
	
   /**
    * Gets the Duplicate Exist field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Duplicate Exist or the specified default value.
    */
   public final boolean getDuplicateExist( boolean defaultValue )
   {
      return _DuplicateExist == null ? defaultValue : _DuplicateExist.booleanValue();
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
    * Gets the AMS Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AMS Code or null.
    */
   public final String getrxAMSCode( int index )
   {
      return _rxAMSCode[index];
   }
    
   /**
    * Gets the AMS Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AMS Code or the specified default value.
    */
   public final String getrxAMSCode( int index, String defaultValue )
   {
      return _rxAMSCode[index] == null ? defaultValue : _rxAMSCode[index];
   }
    
   /**
    * Gets the array of AMS Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AMS Code values.
    */
   public final String[] getrxAMSCodeArray()
   {
      return _rxAMSCode;
   }
    
   /**
    * Gets the AMS Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AMS Type or null.
    */
   public final String getrxAMSType( int index )
   {
      return _rxAMSType[index];
   }
    
   /**
    * Gets the AMS Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AMS Type or the specified default value.
    */
   public final String getrxAMSType( int index, String defaultValue )
   {
      return _rxAMSType[index] == null ? defaultValue : _rxAMSType[index];
   }
    
   /**
    * Gets the array of AMS Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AMS Type values.
    */
   public final String[] getrxAMSTypeArray()
   {
      return _rxAMSType;
   }
    
   /**
    * Gets the Effective Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Effective Date or null.
    */
   public final Date getrxDeff( int index )
   {
      return _rxDeff[index];
   }
    
   /**
    * Gets the Effective Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Effective Date or the specified default value.
    */
   public final Date getrxDeff( int index, Date defaultValue )
   {
      return _rxDeff[index] == null ? defaultValue : _rxDeff[index];
   }
    
   /**
    * Gets the array of Effective Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Effective Date values.
    */
   public final Date[] getrxDeffArray()
   {
      return _rxDeff;
   }
    
   /**
    * Gets the Stop Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stop Date or null.
    */
   public final Date getrxStopDate( int index )
   {
      return _rxStopDate[index];
   }
    
   /**
    * Gets the Stop Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Date or the specified default value.
    */
   public final Date getrxStopDate( int index, Date defaultValue )
   {
      return _rxStopDate[index] == null ? defaultValue : _rxStopDate[index];
   }
    
   /**
    * Gets the array of Stop Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stop Date values.
    */
   public final Date[] getrxStopDateArray()
   {
      return _rxStopDate;
   }
    
   /**
    * Gets the Next Process Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Next Process Date or null.
    */
   public final Date getNextProcDate( int index )
   {
      return _NextProcDate[index];
   }
    
   /**
    * Gets the Next Process Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Next Process Date or the specified default value.
    */
   public final Date getNextProcDate( int index, Date defaultValue )
   {
      return _NextProcDate[index] == null ? defaultValue : _NextProcDate[index];
   }
    
   /**
    * Gets the array of Next Process Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Next Process Date values.
    */
   public final Date[] getNextProcDateArray()
   {
      return _NextProcDate;
   }
    
   /**
    * Gets the Last Process Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Last Process Date or null.
    */
   public final Date getLastProcDate( int index )
   {
      return _LastProcDate[index];
   }
    
   /**
    * Gets the Last Process Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Last Process Date or the specified default value.
    */
   public final Date getLastProcDate( int index, Date defaultValue )
   {
      return _LastProcDate[index] == null ? defaultValue : _LastProcDate[index];
   }
    
   /**
    * Gets the array of Last Process Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Last Process Date values.
    */
   public final Date[] getLastProcDateArray()
   {
      return _LastProcDate;
   }
    
   /**
    * Gets the Frequency Override field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Frequency Override or null.
    */
   public final Integer getFreqOverride( int index )
   {
      return _FreqOverride[index];
   }
    
   /**
    * Gets the Frequency Override field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Frequency Override or the specified default value.
    */
   public final int getFreqOverride( int index, int defaultValue )
   {
      return _FreqOverride[index] == null ? defaultValue : _FreqOverride[index].intValue();
   }
    
   /**
    * Gets the array of Frequency Override fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Frequency Override values.
    */
   public final Integer[] getFreqOverrideArray()
   {
      return _FreqOverride;
   }
    
   /**
    * Gets the Sched SetUp Freq ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Sched SetUp Freq ID or null.
    */
   public final Integer getSchedSetupFreqID( int index )
   {
      return _SchedSetupFreqID[index];
   }
    
   /**
    * Gets the Sched SetUp Freq ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Sched SetUp Freq ID or the specified default value.
    */
   public final int getSchedSetupFreqID( int index, int defaultValue )
   {
      return _SchedSetupFreqID[index] == null ? defaultValue : _SchedSetupFreqID[index].intValue();
   }
    
   /**
    * Gets the array of Sched SetUp Freq ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Sched SetUp Freq ID values.
    */
   public final Integer[] getSchedSetupFreqIDArray()
   {
      return _SchedSetupFreqID;
   }
    
   /**
    * Gets the AMS Stat field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AMS Stat or null.
    */
   public final Integer getAMSStat( int index )
   {
      return _AMSStat[index];
   }
    
   /**
    * Gets the AMS Stat field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AMS Stat or the specified default value.
    */
   public final int getAMSStat( int index, int defaultValue )
   {
      return _AMSStat[index] == null ? defaultValue : _AMSStat[index].intValue();
   }
    
   /**
    * Gets the array of AMS Stat fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AMS Stat values.
    */
   public final Integer[] getAMSStatArray()
   {
      return _AMSStat;
   }
    
   /**
    * Gets the AMS Activation Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AMS Activation Date or null.
    */
   public final Date getActivationDate( int index )
   {
      return _ActivationDate[index];
   }
    
   /**
    * Gets the AMS Activation Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AMS Activation Date or the specified default value.
    */
   public final Date getActivationDate( int index, Date defaultValue )
   {
      return _ActivationDate[index] == null ? defaultValue : _ActivationDate[index];
   }
    
   /**
    * Gets the array of AMS Activation Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AMS Activation Date values.
    */
   public final Date[] getActivationDateArray()
   {
      return _ActivationDate;
   }
    
   /**
    * Gets the Acct-AMS RID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Acct-AMS RID or null.
    */
   public final Integer getAcctAMSRID( int index )
   {
      return _AcctAMSRID[index];
   }
    
   /**
    * Gets the Acct-AMS RID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Acct-AMS RID or the specified default value.
    */
   public final int getAcctAMSRID( int index, int defaultValue )
   {
      return _AcctAMSRID[index] == null ? defaultValue : _AcctAMSRID[index].intValue();
   }
    
   /**
    * Gets the array of Acct-AMS RID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Acct-AMS RID values.
    */
   public final Integer[] getAcctAMSRIDArray()
   {
      return _AcctAMSRID;
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
    * Gets the UserName field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the UserName or null.
    */
   public final String getUserName( int index )
   {
      return _UserName[index];
   }
    
   /**
    * Gets the UserName field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the UserName or the specified default value.
    */
   public final String getUserName( int index, String defaultValue )
   {
      return _UserName[index] == null ? defaultValue : _UserName[index];
   }
    
   /**
    * Gets the array of UserName fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of UserName values.
    */
   public final String[] getUserNameArray()
   {
      return _UserName;
   }
    
   /**
    * Gets the Modification Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Modification Date or null.
    */
   public final Date getModDate( int index )
   {
      return _ModDate[index];
   }
    
   /**
    * Gets the Modification Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Modification Date or the specified default value.
    */
   public final Date getModDate( int index, Date defaultValue )
   {
      return _ModDate[index] == null ? defaultValue : _ModDate[index];
   }
    
   /**
    * Gets the array of Modification Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Modification Date values.
    */
   public final Date[] getModDateArray()
   {
      return _ModDate;
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
    * Gets the Threshold Percentage field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Threshold Percentage or null.
    */
   public final String getThresholdPrcnt( int index )
   {
      return _ThresholdPrcnt[index];
   }
    
   /**
    * Gets the Threshold Percentage field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Threshold Percentage or the specified default value.
    */
   public final String getThresholdPrcnt( int index, String defaultValue )
   {
      return _ThresholdPrcnt[index] == null ? defaultValue : _ThresholdPrcnt[index];
   }
    
   /**
    * Gets the array of Threshold Percentage fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Threshold Percentage values.
    */
   public final String[] getThresholdPrcntArray()
   {
      return _ThresholdPrcnt;
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
      _DuplicateExist = responseBuffer.decodeBoolean(responseBuffer.getNextField());
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _rxAMSCode = resizeArray( _rxAMSCode, _RepeatCount );
      _rxAMSType = resizeArray( _rxAMSType, _RepeatCount );
      _rxDeff = resizeArray( _rxDeff, _RepeatCount );
      _rxStopDate = resizeArray( _rxStopDate, _RepeatCount );
      _NextProcDate = resizeArray( _NextProcDate, _RepeatCount );
      _LastProcDate = resizeArray( _LastProcDate, _RepeatCount );
      _FreqOverride = resizeArray( _FreqOverride, _RepeatCount );
      _SchedSetupFreqID = resizeArray( _SchedSetupFreqID, _RepeatCount );
      _AMSStat = resizeArray( _AMSStat, _RepeatCount );
      _ActivationDate = resizeArray( _ActivationDate, _RepeatCount );
      _AcctAMSRID = resizeArray( _AcctAMSRID, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _UserName = resizeArray( _UserName, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _ThresholdPrcnt = resizeArray( _ThresholdPrcnt, _RepeatCount );
      _Currency = resizeArray( _Currency, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxAMSCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxAMSType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxDeff[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _rxStopDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _NextProcDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _LastProcDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _FreqOverride[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _SchedSetupFreqID[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _AMSStat[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ActivationDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _AcctAMSRID[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _UserName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ThresholdPrcnt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Currency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
