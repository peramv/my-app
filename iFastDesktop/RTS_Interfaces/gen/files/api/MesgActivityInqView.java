
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Message Activity Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/MesgActivityInq.doc">MesgActivityInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class MesgActivityInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Process ID member array.
    */
   private String[] _rxProcessID = null;
   
   /**
    * Activity ID member array.
    */
   private String[] _ActivityID = null;
   
   /**
    * Activity Type member array.
    */
   private String[] _ActivityType = null;
   
   /**
    * Senders Reference Number member array.
    */
   private String[] _SendersRefNum = null;
   
   /**
    * Message Date member array.
    */
   private Date[] _MsgDate = null;
   
   /**
    * Message Time member array.
    */
   private String[] _MsgTime = null;
   
   /**
    * Process Date member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * Process Time member array.
    */
   private String[] _ProcessTime = null;
   
   /**
    * Fund Broker Code member array.
    */
   private String[] _FundBrokerCode = null;
   
   /**
    * Omnibus ID member array.
    */
   private String[] _OmnibusID = null;
   
   /**
    * Account Number member array.
    */
   private String[] _AccountNum = null;
   
   /**
    * Transaction Number member array.
    */
   private Integer[] _TransNum = null;
   

   /**
    * Constructs the MesgActivityInqView object.
    * 
    */
   public MesgActivityInqView()
   {
      super ( new MesgActivityInqRequest() );
   }

   /**
    * Constructs the MesgActivityInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public MesgActivityInqView( String hostEncoding )
   {
      super ( new MesgActivityInqRequest( hostEncoding ) );
   }

   /**
    * Gets the MesgActivityInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The MesgActivityInqRequest object.
    */
   public final MesgActivityInqRequest getRequest()
   {
      return (MesgActivityInqRequest)getIFastRequest();
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
    * Gets the Process ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Process ID or null.
    */
   public final String getrxProcessID( int index )
   {
      return _rxProcessID[index];
   }
    
   /**
    * Gets the Process ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Process ID or the specified default value.
    */
   public final String getrxProcessID( int index, String defaultValue )
   {
      return _rxProcessID[index] == null ? defaultValue : _rxProcessID[index];
   }
    
   /**
    * Gets the array of Process ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Process ID values.
    */
   public final String[] getrxProcessIDArray()
   {
      return _rxProcessID;
   }
    
   /**
    * Gets the Activity ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Activity ID or null.
    */
   public final String getActivityID( int index )
   {
      return _ActivityID[index];
   }
    
   /**
    * Gets the Activity ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Activity ID or the specified default value.
    */
   public final String getActivityID( int index, String defaultValue )
   {
      return _ActivityID[index] == null ? defaultValue : _ActivityID[index];
   }
    
   /**
    * Gets the array of Activity ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Activity ID values.
    */
   public final String[] getActivityIDArray()
   {
      return _ActivityID;
   }
    
   /**
    * Gets the Activity Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Activity Type or null.
    */
   public final String getActivityType( int index )
   {
      return _ActivityType[index];
   }
    
   /**
    * Gets the Activity Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Activity Type or the specified default value.
    */
   public final String getActivityType( int index, String defaultValue )
   {
      return _ActivityType[index] == null ? defaultValue : _ActivityType[index];
   }
    
   /**
    * Gets the array of Activity Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Activity Type values.
    */
   public final String[] getActivityTypeArray()
   {
      return _ActivityType;
   }
    
   /**
    * Gets the Senders Reference Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Senders Reference Number or null.
    */
   public final String getSendersRefNum( int index )
   {
      return _SendersRefNum[index];
   }
    
   /**
    * Gets the Senders Reference Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Senders Reference Number or the specified default value.
    */
   public final String getSendersRefNum( int index, String defaultValue )
   {
      return _SendersRefNum[index] == null ? defaultValue : _SendersRefNum[index];
   }
    
   /**
    * Gets the array of Senders Reference Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Senders Reference Number values.
    */
   public final String[] getSendersRefNumArray()
   {
      return _SendersRefNum;
   }
    
   /**
    * Gets the Message Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Message Date or null.
    */
   public final Date getMsgDate( int index )
   {
      return _MsgDate[index];
   }
    
   /**
    * Gets the Message Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Message Date or the specified default value.
    */
   public final Date getMsgDate( int index, Date defaultValue )
   {
      return _MsgDate[index] == null ? defaultValue : _MsgDate[index];
   }
    
   /**
    * Gets the array of Message Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Message Date values.
    */
   public final Date[] getMsgDateArray()
   {
      return _MsgDate;
   }
    
   /**
    * Gets the Message Time field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Message Time or null.
    */
   public final String getMsgTime( int index )
   {
      return _MsgTime[index];
   }
    
   /**
    * Gets the Message Time field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Message Time or the specified default value.
    */
   public final String getMsgTime( int index, String defaultValue )
   {
      return _MsgTime[index] == null ? defaultValue : _MsgTime[index];
   }
    
   /**
    * Gets the array of Message Time fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Message Time values.
    */
   public final String[] getMsgTimeArray()
   {
      return _MsgTime;
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
    * Gets the Fund Broker Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Broker Code or null.
    */
   public final String getFundBrokerCode( int index )
   {
      return _FundBrokerCode[index];
   }
    
   /**
    * Gets the Fund Broker Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Broker Code or the specified default value.
    */
   public final String getFundBrokerCode( int index, String defaultValue )
   {
      return _FundBrokerCode[index] == null ? defaultValue : _FundBrokerCode[index];
   }
    
   /**
    * Gets the array of Fund Broker Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Broker Code values.
    */
   public final String[] getFundBrokerCodeArray()
   {
      return _FundBrokerCode;
   }
    
   /**
    * Gets the Omnibus ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Omnibus ID or null.
    */
   public final String getOmnibusID( int index )
   {
      return _OmnibusID[index];
   }
    
   /**
    * Gets the Omnibus ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Omnibus ID or the specified default value.
    */
   public final String getOmnibusID( int index, String defaultValue )
   {
      return _OmnibusID[index] == null ? defaultValue : _OmnibusID[index];
   }
    
   /**
    * Gets the array of Omnibus ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Omnibus ID values.
    */
   public final String[] getOmnibusIDArray()
   {
      return _OmnibusID;
   }
    
   /**
    * Gets the Account Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Number or null.
    */
   public final String getAccountNum( int index )
   {
      return _AccountNum[index];
   }
    
   /**
    * Gets the Account Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Number or the specified default value.
    */
   public final String getAccountNum( int index, String defaultValue )
   {
      return _AccountNum[index] == null ? defaultValue : _AccountNum[index];
   }
    
   /**
    * Gets the array of Account Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Number values.
    */
   public final String[] getAccountNumArray()
   {
      return _AccountNum;
   }
    
   /**
    * Gets the Transaction Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transaction Number or null.
    */
   public final Integer getTransNum( int index )
   {
      return _TransNum[index];
   }
    
   /**
    * Gets the Transaction Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transaction Number or the specified default value.
    */
   public final int getTransNum( int index, int defaultValue )
   {
      return _TransNum[index] == null ? defaultValue : _TransNum[index].intValue();
   }
    
   /**
    * Gets the array of Transaction Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transaction Number values.
    */
   public final Integer[] getTransNumArray()
   {
      return _TransNum;
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
      
      _rxProcessID = resizeArray( _rxProcessID, _RepeatCount );
      _ActivityID = resizeArray( _ActivityID, _RepeatCount );
      _ActivityType = resizeArray( _ActivityType, _RepeatCount );
      _SendersRefNum = resizeArray( _SendersRefNum, _RepeatCount );
      _MsgDate = resizeArray( _MsgDate, _RepeatCount );
      _MsgTime = resizeArray( _MsgTime, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _ProcessTime = resizeArray( _ProcessTime, _RepeatCount );
      _FundBrokerCode = resizeArray( _FundBrokerCode, _RepeatCount );
      _OmnibusID = resizeArray( _OmnibusID, _RepeatCount );
      _AccountNum = resizeArray( _AccountNum, _RepeatCount );
      _TransNum = resizeArray( _TransNum, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxProcessID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ActivityID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ActivityType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SendersRefNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MsgDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _MsgTime[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ProcessTime[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundBrokerCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _OmnibusID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AccountNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TransNum[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
      }
      

   }

}
      
