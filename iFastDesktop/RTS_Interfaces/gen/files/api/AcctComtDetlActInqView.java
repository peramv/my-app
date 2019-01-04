
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Account Commitment Details&Activity Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/AcctComtDetlActInq.doc">AcctComtDetlActInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class AcctComtDetlActInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Record Type member array.
    */
   private String[] _RecType = null;
   
   /**
    * AcctCommitDetlUUID member array.
    */
   private String[] _AcctCommitDetlUUID = null;
   
   /**
    * Commitment Effective Date member array.
    */
   private Date[] _DetlDeff = null;
   
   /**
    * Commitment Amount member array.
    */
   private String[] _DetlAmt = null;
   
   /**
    * Commitment Stop Date member array.
    */
   private Date[] _DetlStopDate = null;
   
   /**
    * Commitment Commission/Clawback member array.
    */
   private String[] _DetlCommClawBack = null;
   
   /**
    * AcctCommitActivityUUID member array.
    */
   private String[] _AcctCommitActivityUUID = null;
   
   /**
    * Commitment Activity Amount member array.
    */
   private String[] _ActivityAmt = null;
   
   /**
    * Commitment Activity Effective Date member array.
    */
   private Date[] _ActivityDeff = null;
   
   /**
    * Commitment Activity Commission/Clawback member array.
    */
   private String[] _ActivityCommClawBack = null;
   
   /**
    * Expected Amount member array.
    */
   private String[] _ExpectedAmt = null;
   
   /**
    * Bonus Percentage member array.
    */
   private String[] _BonusPercentage = null;
   

   /**
    * Constructs the AcctComtDetlActInqView object.
    * 
    */
   public AcctComtDetlActInqView()
   {
      super ( new AcctComtDetlActInqRequest() );
   }

   /**
    * Constructs the AcctComtDetlActInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AcctComtDetlActInqView( String hostEncoding )
   {
      super ( new AcctComtDetlActInqRequest( hostEncoding ) );
   }

   /**
    * Gets the AcctComtDetlActInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AcctComtDetlActInqRequest object.
    */
   public final AcctComtDetlActInqRequest getRequest()
   {
      return (AcctComtDetlActInqRequest)getIFastRequest();
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
    * Gets the AcctCommitDetlUUID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AcctCommitDetlUUID or null.
    */
   public final String getAcctCommitDetlUUID( int index )
   {
      return _AcctCommitDetlUUID[index];
   }
    
   /**
    * Gets the AcctCommitDetlUUID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AcctCommitDetlUUID or the specified default value.
    */
   public final String getAcctCommitDetlUUID( int index, String defaultValue )
   {
      return _AcctCommitDetlUUID[index] == null ? defaultValue : _AcctCommitDetlUUID[index];
   }
    
   /**
    * Gets the array of AcctCommitDetlUUID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AcctCommitDetlUUID values.
    */
   public final String[] getAcctCommitDetlUUIDArray()
   {
      return _AcctCommitDetlUUID;
   }
    
   /**
    * Gets the Commitment Effective Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Commitment Effective Date or null.
    */
   public final Date getDetlDeff( int index )
   {
      return _DetlDeff[index];
   }
    
   /**
    * Gets the Commitment Effective Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commitment Effective Date or the specified default value.
    */
   public final Date getDetlDeff( int index, Date defaultValue )
   {
      return _DetlDeff[index] == null ? defaultValue : _DetlDeff[index];
   }
    
   /**
    * Gets the array of Commitment Effective Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Commitment Effective Date values.
    */
   public final Date[] getDetlDeffArray()
   {
      return _DetlDeff;
   }
    
   /**
    * Gets the Commitment Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Commitment Amount or null.
    */
   public final String getDetlAmt( int index )
   {
      return _DetlAmt[index];
   }
    
   /**
    * Gets the Commitment Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commitment Amount or the specified default value.
    */
   public final String getDetlAmt( int index, String defaultValue )
   {
      return _DetlAmt[index] == null ? defaultValue : _DetlAmt[index];
   }
    
   /**
    * Gets the array of Commitment Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Commitment Amount values.
    */
   public final String[] getDetlAmtArray()
   {
      return _DetlAmt;
   }
    
   /**
    * Gets the Commitment Stop Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Commitment Stop Date or null.
    */
   public final Date getDetlStopDate( int index )
   {
      return _DetlStopDate[index];
   }
    
   /**
    * Gets the Commitment Stop Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commitment Stop Date or the specified default value.
    */
   public final Date getDetlStopDate( int index, Date defaultValue )
   {
      return _DetlStopDate[index] == null ? defaultValue : _DetlStopDate[index];
   }
    
   /**
    * Gets the array of Commitment Stop Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Commitment Stop Date values.
    */
   public final Date[] getDetlStopDateArray()
   {
      return _DetlStopDate;
   }
    
   /**
    * Gets the Commitment Commission/Clawback field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Commitment Commission/Clawback or null.
    */
   public final String getDetlCommClawBack( int index )
   {
      return _DetlCommClawBack[index];
   }
    
   /**
    * Gets the Commitment Commission/Clawback field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commitment Commission/Clawback or the specified default value.
    */
   public final String getDetlCommClawBack( int index, String defaultValue )
   {
      return _DetlCommClawBack[index] == null ? defaultValue : _DetlCommClawBack[index];
   }
    
   /**
    * Gets the array of Commitment Commission/Clawback fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Commitment Commission/Clawback values.
    */
   public final String[] getDetlCommClawBackArray()
   {
      return _DetlCommClawBack;
   }
    
   /**
    * Gets the AcctCommitActivityUUID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AcctCommitActivityUUID or null.
    */
   public final String getAcctCommitActivityUUID( int index )
   {
      return _AcctCommitActivityUUID[index];
   }
    
   /**
    * Gets the AcctCommitActivityUUID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AcctCommitActivityUUID or the specified default value.
    */
   public final String getAcctCommitActivityUUID( int index, String defaultValue )
   {
      return _AcctCommitActivityUUID[index] == null ? defaultValue : _AcctCommitActivityUUID[index];
   }
    
   /**
    * Gets the array of AcctCommitActivityUUID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AcctCommitActivityUUID values.
    */
   public final String[] getAcctCommitActivityUUIDArray()
   {
      return _AcctCommitActivityUUID;
   }
    
   /**
    * Gets the Commitment Activity Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Commitment Activity Amount or null.
    */
   public final String getActivityAmt( int index )
   {
      return _ActivityAmt[index];
   }
    
   /**
    * Gets the Commitment Activity Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commitment Activity Amount or the specified default value.
    */
   public final String getActivityAmt( int index, String defaultValue )
   {
      return _ActivityAmt[index] == null ? defaultValue : _ActivityAmt[index];
   }
    
   /**
    * Gets the array of Commitment Activity Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Commitment Activity Amount values.
    */
   public final String[] getActivityAmtArray()
   {
      return _ActivityAmt;
   }
    
   /**
    * Gets the Commitment Activity Effective Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Commitment Activity Effective Date or null.
    */
   public final Date getActivityDeff( int index )
   {
      return _ActivityDeff[index];
   }
    
   /**
    * Gets the Commitment Activity Effective Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commitment Activity Effective Date or the specified default value.
    */
   public final Date getActivityDeff( int index, Date defaultValue )
   {
      return _ActivityDeff[index] == null ? defaultValue : _ActivityDeff[index];
   }
    
   /**
    * Gets the array of Commitment Activity Effective Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Commitment Activity Effective Date values.
    */
   public final Date[] getActivityDeffArray()
   {
      return _ActivityDeff;
   }
    
   /**
    * Gets the Commitment Activity Commission/Clawback field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Commitment Activity Commission/Clawback or null.
    */
   public final String getActivityCommClawBack( int index )
   {
      return _ActivityCommClawBack[index];
   }
    
   /**
    * Gets the Commitment Activity Commission/Clawback field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commitment Activity Commission/Clawback or the specified default value.
    */
   public final String getActivityCommClawBack( int index, String defaultValue )
   {
      return _ActivityCommClawBack[index] == null ? defaultValue : _ActivityCommClawBack[index];
   }
    
   /**
    * Gets the array of Commitment Activity Commission/Clawback fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Commitment Activity Commission/Clawback values.
    */
   public final String[] getActivityCommClawBackArray()
   {
      return _ActivityCommClawBack;
   }
    
   /**
    * Gets the Expected Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Expected Amount or null.
    */
   public final String getExpectedAmt( int index )
   {
      return _ExpectedAmt[index];
   }
    
   /**
    * Gets the Expected Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Expected Amount or the specified default value.
    */
   public final String getExpectedAmt( int index, String defaultValue )
   {
      return _ExpectedAmt[index] == null ? defaultValue : _ExpectedAmt[index];
   }
    
   /**
    * Gets the array of Expected Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Expected Amount values.
    */
   public final String[] getExpectedAmtArray()
   {
      return _ExpectedAmt;
   }
    
   /**
    * Gets the Bonus Percentage field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bonus Percentage or null.
    */
   public final String getBonusPercentage( int index )
   {
      return _BonusPercentage[index];
   }
    
   /**
    * Gets the Bonus Percentage field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bonus Percentage or the specified default value.
    */
   public final String getBonusPercentage( int index, String defaultValue )
   {
      return _BonusPercentage[index] == null ? defaultValue : _BonusPercentage[index];
   }
    
   /**
    * Gets the array of Bonus Percentage fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bonus Percentage values.
    */
   public final String[] getBonusPercentageArray()
   {
      return _BonusPercentage;
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
      
      _RecType = resizeArray( _RecType, _RepeatCount );
      _AcctCommitDetlUUID = resizeArray( _AcctCommitDetlUUID, _RepeatCount );
      _DetlDeff = resizeArray( _DetlDeff, _RepeatCount );
      _DetlAmt = resizeArray( _DetlAmt, _RepeatCount );
      _DetlStopDate = resizeArray( _DetlStopDate, _RepeatCount );
      _DetlCommClawBack = resizeArray( _DetlCommClawBack, _RepeatCount );
      _AcctCommitActivityUUID = resizeArray( _AcctCommitActivityUUID, _RepeatCount );
      _ActivityAmt = resizeArray( _ActivityAmt, _RepeatCount );
      _ActivityDeff = resizeArray( _ActivityDeff, _RepeatCount );
      _ActivityCommClawBack = resizeArray( _ActivityCommClawBack, _RepeatCount );
      _ExpectedAmt = resizeArray( _ExpectedAmt, _RepeatCount );
      _BonusPercentage = resizeArray( _BonusPercentage, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _RecType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctCommitDetlUUID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DetlDeff[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _DetlAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DetlStopDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _DetlCommClawBack[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctCommitActivityUUID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ActivityAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ActivityDeff[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ActivityCommClawBack[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ExpectedAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BonusPercentage[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
