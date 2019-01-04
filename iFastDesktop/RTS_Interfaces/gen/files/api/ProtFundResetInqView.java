
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Protected Fund Reset Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/ProtFundResetInq.doc">ProtFundResetInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class ProtFundResetInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Account Number member array.
    */
   private String[] _rxAccountNum = null;
   
   /**
    * Fund Code member array.
    */
   private String[] _FundCode = null;
   
   /**
    * Class Code member array.
    */
   private String[] _ClassCode = null;
   
   /**
    * Reset Date member array.
    */
   private Date[] _rxResetDate = null;
   
   /**
    * Reset Type member array.
    */
   private String[] _ResetType = null;
   
   /**
    * Complete Date member array.
    */
   private Date[] _CompleteDate = null;
   
   /**
    * Reset Id member array.
    */
   private Integer[] _ResetId = null;
   
   /**
    * Cancelled Reset Id member array.
    */
   private Integer[] _CanResetId = null;
   
   /**
    * Contract Id member array.
    */
   private Integer[] _ContractId = null;
   
   /**
    * Process Date member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * User Name member array.
    */
   private String[] _UserName = null;
   
   /**
    * Process Time member array.
    */
   private String[] _ProcessTime = null;
   
   /**
    * Batch Effective member array.
    */
   private Date[] _BatchEffective = null;
   
   /**
    * Batch Name member array.
    */
   private String[] _BatchName = null;
   
   /**
    * Trace member array.
    */
   private Integer[] _Trace = null;
   
   /**
    * Version member array.
    */
   private Integer[] _Version = null;
   
   /**
    * Protect Reset Rid member array.
    */
   private Integer[] _ProtectResetRid = null;
   
   /**
    * Number of Resets performed this year member array.
    */
   private Integer[] _NumOfResets = null;
   
   /**
    * Flag that indiciate if record is reversal member array.
    */
   private Boolean[] _Reversal = null;
   

   /**
    * Constructs the ProtFundResetInqView object.
    * 
    */
   public ProtFundResetInqView()
   {
      super ( new ProtFundResetInqRequest() );
   }

   /**
    * Constructs the ProtFundResetInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public ProtFundResetInqView( String hostEncoding )
   {
      super ( new ProtFundResetInqRequest( hostEncoding ) );
   }

   /**
    * Gets the ProtFundResetInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The ProtFundResetInqRequest object.
    */
   public final ProtFundResetInqRequest getRequest()
   {
      return (ProtFundResetInqRequest)getIFastRequest();
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
    * Gets the Account Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Number or null.
    */
   public final String getrxAccountNum( int index )
   {
      return _rxAccountNum[index];
   }
    
   /**
    * Gets the Account Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Number or the specified default value.
    */
   public final String getrxAccountNum( int index, String defaultValue )
   {
      return _rxAccountNum[index] == null ? defaultValue : _rxAccountNum[index];
   }
    
   /**
    * Gets the array of Account Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Number values.
    */
   public final String[] getrxAccountNumArray()
   {
      return _rxAccountNum;
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
    * Gets the Reset Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reset Date or null.
    */
   public final Date getrxResetDate( int index )
   {
      return _rxResetDate[index];
   }
    
   /**
    * Gets the Reset Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reset Date or the specified default value.
    */
   public final Date getrxResetDate( int index, Date defaultValue )
   {
      return _rxResetDate[index] == null ? defaultValue : _rxResetDate[index];
   }
    
   /**
    * Gets the array of Reset Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reset Date values.
    */
   public final Date[] getrxResetDateArray()
   {
      return _rxResetDate;
   }
    
   /**
    * Gets the Reset Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reset Type or null.
    */
   public final String getResetType( int index )
   {
      return _ResetType[index];
   }
    
   /**
    * Gets the Reset Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reset Type or the specified default value.
    */
   public final String getResetType( int index, String defaultValue )
   {
      return _ResetType[index] == null ? defaultValue : _ResetType[index];
   }
    
   /**
    * Gets the array of Reset Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reset Type values.
    */
   public final String[] getResetTypeArray()
   {
      return _ResetType;
   }
    
   /**
    * Gets the Complete Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Complete Date or null.
    */
   public final Date getCompleteDate( int index )
   {
      return _CompleteDate[index];
   }
    
   /**
    * Gets the Complete Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Complete Date or the specified default value.
    */
   public final Date getCompleteDate( int index, Date defaultValue )
   {
      return _CompleteDate[index] == null ? defaultValue : _CompleteDate[index];
   }
    
   /**
    * Gets the array of Complete Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Complete Date values.
    */
   public final Date[] getCompleteDateArray()
   {
      return _CompleteDate;
   }
    
   /**
    * Gets the Reset Id field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reset Id or null.
    */
   public final Integer getResetId( int index )
   {
      return _ResetId[index];
   }
    
   /**
    * Gets the Reset Id field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reset Id or the specified default value.
    */
   public final int getResetId( int index, int defaultValue )
   {
      return _ResetId[index] == null ? defaultValue : _ResetId[index].intValue();
   }
    
   /**
    * Gets the array of Reset Id fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reset Id values.
    */
   public final Integer[] getResetIdArray()
   {
      return _ResetId;
   }
    
   /**
    * Gets the Cancelled Reset Id field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Cancelled Reset Id or null.
    */
   public final Integer getCanResetId( int index )
   {
      return _CanResetId[index];
   }
    
   /**
    * Gets the Cancelled Reset Id field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Cancelled Reset Id or the specified default value.
    */
   public final int getCanResetId( int index, int defaultValue )
   {
      return _CanResetId[index] == null ? defaultValue : _CanResetId[index].intValue();
   }
    
   /**
    * Gets the array of Cancelled Reset Id fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Cancelled Reset Id values.
    */
   public final Integer[] getCanResetIdArray()
   {
      return _CanResetId;
   }
    
   /**
    * Gets the Contract Id field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contract Id or null.
    */
   public final Integer getContractId( int index )
   {
      return _ContractId[index];
   }
    
   /**
    * Gets the Contract Id field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contract Id or the specified default value.
    */
   public final int getContractId( int index, int defaultValue )
   {
      return _ContractId[index] == null ? defaultValue : _ContractId[index].intValue();
   }
    
   /**
    * Gets the array of Contract Id fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contract Id values.
    */
   public final Integer[] getContractIdArray()
   {
      return _ContractId;
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
    * Gets the Process Time field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Process Time or null.
    */
   public final String getProcessTime( int index )
   {
      return _ProcessTime[index];
   }
    
   /**
    * Gets the Process Time field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Process Time or the specified default value.
    */
   public final String getProcessTime( int index, String defaultValue )
   {
      return _ProcessTime[index] == null ? defaultValue : _ProcessTime[index];
   }
    
   /**
    * Gets the array of Process Time fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Process Time values.
    */
   public final String[] getProcessTimeArray()
   {
      return _ProcessTime;
   }
    
   /**
    * Gets the Batch Effective field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Batch Effective or null.
    */
   public final Date getBatchEffective( int index )
   {
      return _BatchEffective[index];
   }
    
   /**
    * Gets the Batch Effective field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Batch Effective or the specified default value.
    */
   public final Date getBatchEffective( int index, Date defaultValue )
   {
      return _BatchEffective[index] == null ? defaultValue : _BatchEffective[index];
   }
    
   /**
    * Gets the array of Batch Effective fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Batch Effective values.
    */
   public final Date[] getBatchEffectiveArray()
   {
      return _BatchEffective;
   }
    
   /**
    * Gets the Batch Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Batch Name or null.
    */
   public final String getBatchName( int index )
   {
      return _BatchName[index];
   }
    
   /**
    * Gets the Batch Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Batch Name or the specified default value.
    */
   public final String getBatchName( int index, String defaultValue )
   {
      return _BatchName[index] == null ? defaultValue : _BatchName[index];
   }
    
   /**
    * Gets the array of Batch Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Batch Name values.
    */
   public final String[] getBatchNameArray()
   {
      return _BatchName;
   }
    
   /**
    * Gets the Trace field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Trace or null.
    */
   public final Integer getTrace( int index )
   {
      return _Trace[index];
   }
    
   /**
    * Gets the Trace field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Trace or the specified default value.
    */
   public final int getTrace( int index, int defaultValue )
   {
      return _Trace[index] == null ? defaultValue : _Trace[index].intValue();
   }
    
   /**
    * Gets the array of Trace fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Trace values.
    */
   public final Integer[] getTraceArray()
   {
      return _Trace;
   }
    
   /**
    * Gets the Version field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Version or null.
    */
   public final Integer getVersion( int index )
   {
      return _Version[index];
   }
    
   /**
    * Gets the Version field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Version or the specified default value.
    */
   public final int getVersion( int index, int defaultValue )
   {
      return _Version[index] == null ? defaultValue : _Version[index].intValue();
   }
    
   /**
    * Gets the array of Version fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Version values.
    */
   public final Integer[] getVersionArray()
   {
      return _Version;
   }
    
   /**
    * Gets the Protect Reset Rid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Protect Reset Rid or null.
    */
   public final Integer getProtectResetRid( int index )
   {
      return _ProtectResetRid[index];
   }
    
   /**
    * Gets the Protect Reset Rid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Protect Reset Rid or the specified default value.
    */
   public final int getProtectResetRid( int index, int defaultValue )
   {
      return _ProtectResetRid[index] == null ? defaultValue : _ProtectResetRid[index].intValue();
   }
    
   /**
    * Gets the array of Protect Reset Rid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Protect Reset Rid values.
    */
   public final Integer[] getProtectResetRidArray()
   {
      return _ProtectResetRid;
   }
    
   /**
    * Gets the Number of Resets performed this year field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Number of Resets performed this year or null.
    */
   public final Integer getNumOfResets( int index )
   {
      return _NumOfResets[index];
   }
    
   /**
    * Gets the Number of Resets performed this year field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Number of Resets performed this year or the specified default value.
    */
   public final int getNumOfResets( int index, int defaultValue )
   {
      return _NumOfResets[index] == null ? defaultValue : _NumOfResets[index].intValue();
   }
    
   /**
    * Gets the array of Number of Resets performed this year fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Number of Resets performed this year values.
    */
   public final Integer[] getNumOfResetsArray()
   {
      return _NumOfResets;
   }
    
   /**
    * Gets the Flag that indiciate if record is reversal field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag that indiciate if record is reversal or null.
    */
   public final Boolean getReversal( int index )
   {
      return _Reversal[index];
   }
    
   /**
    * Gets the Flag that indiciate if record is reversal field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag that indiciate if record is reversal or the specified default value.
    */
   public final boolean getReversal( int index, boolean defaultValue )
   {
      return _Reversal[index] == null ? defaultValue : _Reversal[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag that indiciate if record is reversal fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag that indiciate if record is reversal values.
    */
   public final Boolean[] getReversalArray()
   {
      return _Reversal;
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
      
      _rxAccountNum = resizeArray( _rxAccountNum, _RepeatCount );
      _FundCode = resizeArray( _FundCode, _RepeatCount );
      _ClassCode = resizeArray( _ClassCode, _RepeatCount );
      _rxResetDate = resizeArray( _rxResetDate, _RepeatCount );
      _ResetType = resizeArray( _ResetType, _RepeatCount );
      _CompleteDate = resizeArray( _CompleteDate, _RepeatCount );
      _ResetId = resizeArray( _ResetId, _RepeatCount );
      _CanResetId = resizeArray( _CanResetId, _RepeatCount );
      _ContractId = resizeArray( _ContractId, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _UserName = resizeArray( _UserName, _RepeatCount );
      _ProcessTime = resizeArray( _ProcessTime, _RepeatCount );
      _BatchEffective = resizeArray( _BatchEffective, _RepeatCount );
      _BatchName = resizeArray( _BatchName, _RepeatCount );
      _Trace = resizeArray( _Trace, _RepeatCount );
      _Version = resizeArray( _Version, _RepeatCount );
      _ProtectResetRid = resizeArray( _ProtectResetRid, _RepeatCount );
      _NumOfResets = resizeArray( _NumOfResets, _RepeatCount );
      _Reversal = resizeArray( _Reversal, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxAccountNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxResetDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ResetType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CompleteDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ResetId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _CanResetId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ContractId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _UserName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProcessTime[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BatchEffective[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _BatchName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Trace[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _Version[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ProtectResetRid[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _NumOfResets[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _Reversal[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      }
      

   }

}
      
