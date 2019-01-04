
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Update Incomplete RESP Transfer  Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/RESUpInc.doc">RESUpInc.doc</A>.
 * 
 * @author RTS Generated
 */
public class RESUpIncView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Transaction ID member array.
    */
   private String[] _TransId = null;
   
   /**
    * Contribution Status member array.
    */
   private String[] _StatusCode = null;
   
   /**
    * Beneficiary Name member array.
    */
   private String[] _BeneName = null;
   
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = null;
   
   /**
    * RESP Letter member array.
    */
   private Boolean[] _RESPLetter = null;
   
   /**
    * Termination Date of the Plan member array.
    */
   private Date[] _TerminateDate = null;
   
   /**
    * Annual Contribution To Date member array.
    */
   private String[] _YTDContr = null;
   
   /**
    * Life Time Contribution To Date member array.
    */
   private String[] _LifeContr = null;
   
   /**
    * Redemption To Date member array.
    */
   private String[] _RedLifeContr = null;
   
   /**
    * Unassited Amount member array.
    */
   private String[] _UnAssisted = null;
   
   /**
    * Assisted Amount member array.
    */
   private String[] _Assisted = null;
   
   /**
    * Grant Amount member array.
    */
   private String[] _GrantAmount = null;
   
   /**
    * Information Completed member array.
    */
   private Boolean[] _InfoCompleted = null;
   

   /**
    * Constructs the RESUpIncView object.
    * 
    */
   public RESUpIncView()
   {
      super ( new RESUpIncRequest() );
   }

   /**
    * Constructs the RESUpIncView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public RESUpIncView( String hostEncoding )
   {
      super ( new RESUpIncRequest( hostEncoding ) );
   }

   /**
    * Gets the RESUpIncRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The RESUpIncRequest object.
    */
   public final RESUpIncRequest getRequest()
   {
      return (RESUpIncRequest)getIFastRequest();
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
    * Gets the Transaction ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transaction ID or null.
    */
   public final String getTransId( int index )
   {
      return _TransId[index];
   }
    
   /**
    * Gets the Transaction ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transaction ID or the specified default value.
    */
   public final String getTransId( int index, String defaultValue )
   {
      return _TransId[index] == null ? defaultValue : _TransId[index];
   }
    
   /**
    * Gets the array of Transaction ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transaction ID values.
    */
   public final String[] getTransIdArray()
   {
      return _TransId;
   }
    
   /**
    * Gets the Contribution Status field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contribution Status or null.
    */
   public final String getStatusCode( int index )
   {
      return _StatusCode[index];
   }
    
   /**
    * Gets the Contribution Status field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contribution Status or the specified default value.
    */
   public final String getStatusCode( int index, String defaultValue )
   {
      return _StatusCode[index] == null ? defaultValue : _StatusCode[index];
   }
    
   /**
    * Gets the array of Contribution Status fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contribution Status values.
    */
   public final String[] getStatusCodeArray()
   {
      return _StatusCode;
   }
    
   /**
    * Gets the Beneficiary Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Beneficiary Name or null.
    */
   public final String getBeneName( int index )
   {
      return _BeneName[index];
   }
    
   /**
    * Gets the Beneficiary Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Beneficiary Name or the specified default value.
    */
   public final String getBeneName( int index, String defaultValue )
   {
      return _BeneName[index] == null ? defaultValue : _BeneName[index];
   }
    
   /**
    * Gets the array of Beneficiary Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Beneficiary Name values.
    */
   public final String[] getBeneNameArray()
   {
      return _BeneName;
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
    * Gets the RESP Letter field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RESP Letter or null.
    */
   public final Boolean getRESPLetter( int index )
   {
      return _RESPLetter[index];
   }
    
   /**
    * Gets the RESP Letter field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RESP Letter or the specified default value.
    */
   public final boolean getRESPLetter( int index, boolean defaultValue )
   {
      return _RESPLetter[index] == null ? defaultValue : _RESPLetter[index].booleanValue();
   }
    
   /**
    * Gets the array of RESP Letter fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RESP Letter values.
    */
   public final Boolean[] getRESPLetterArray()
   {
      return _RESPLetter;
   }
    
   /**
    * Gets the Termination Date of the Plan field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Termination Date of the Plan or null.
    */
   public final Date getTerminateDate( int index )
   {
      return _TerminateDate[index];
   }
    
   /**
    * Gets the Termination Date of the Plan field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Termination Date of the Plan or the specified default value.
    */
   public final Date getTerminateDate( int index, Date defaultValue )
   {
      return _TerminateDate[index] == null ? defaultValue : _TerminateDate[index];
   }
    
   /**
    * Gets the array of Termination Date of the Plan fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Termination Date of the Plan values.
    */
   public final Date[] getTerminateDateArray()
   {
      return _TerminateDate;
   }
    
   /**
    * Gets the Annual Contribution To Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Annual Contribution To Date or null.
    */
   public final String getYTDContr( int index )
   {
      return _YTDContr[index];
   }
    
   /**
    * Gets the Annual Contribution To Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Annual Contribution To Date or the specified default value.
    */
   public final String getYTDContr( int index, String defaultValue )
   {
      return _YTDContr[index] == null ? defaultValue : _YTDContr[index];
   }
    
   /**
    * Gets the array of Annual Contribution To Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Annual Contribution To Date values.
    */
   public final String[] getYTDContrArray()
   {
      return _YTDContr;
   }
    
   /**
    * Gets the Life Time Contribution To Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Life Time Contribution To Date or null.
    */
   public final String getLifeContr( int index )
   {
      return _LifeContr[index];
   }
    
   /**
    * Gets the Life Time Contribution To Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Life Time Contribution To Date or the specified default value.
    */
   public final String getLifeContr( int index, String defaultValue )
   {
      return _LifeContr[index] == null ? defaultValue : _LifeContr[index];
   }
    
   /**
    * Gets the array of Life Time Contribution To Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Life Time Contribution To Date values.
    */
   public final String[] getLifeContrArray()
   {
      return _LifeContr;
   }
    
   /**
    * Gets the Redemption To Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Redemption To Date or null.
    */
   public final String getRedLifeContr( int index )
   {
      return _RedLifeContr[index];
   }
    
   /**
    * Gets the Redemption To Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Redemption To Date or the specified default value.
    */
   public final String getRedLifeContr( int index, String defaultValue )
   {
      return _RedLifeContr[index] == null ? defaultValue : _RedLifeContr[index];
   }
    
   /**
    * Gets the array of Redemption To Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Redemption To Date values.
    */
   public final String[] getRedLifeContrArray()
   {
      return _RedLifeContr;
   }
    
   /**
    * Gets the Unassited Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Unassited Amount or null.
    */
   public final String getUnAssisted( int index )
   {
      return _UnAssisted[index];
   }
    
   /**
    * Gets the Unassited Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Unassited Amount or the specified default value.
    */
   public final String getUnAssisted( int index, String defaultValue )
   {
      return _UnAssisted[index] == null ? defaultValue : _UnAssisted[index];
   }
    
   /**
    * Gets the array of Unassited Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Unassited Amount values.
    */
   public final String[] getUnAssistedArray()
   {
      return _UnAssisted;
   }
    
   /**
    * Gets the Assisted Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Assisted Amount or null.
    */
   public final String getAssisted( int index )
   {
      return _Assisted[index];
   }
    
   /**
    * Gets the Assisted Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Assisted Amount or the specified default value.
    */
   public final String getAssisted( int index, String defaultValue )
   {
      return _Assisted[index] == null ? defaultValue : _Assisted[index];
   }
    
   /**
    * Gets the array of Assisted Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Assisted Amount values.
    */
   public final String[] getAssistedArray()
   {
      return _Assisted;
   }
    
   /**
    * Gets the Grant Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Grant Amount or null.
    */
   public final String getGrantAmount( int index )
   {
      return _GrantAmount[index];
   }
    
   /**
    * Gets the Grant Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Grant Amount or the specified default value.
    */
   public final String getGrantAmount( int index, String defaultValue )
   {
      return _GrantAmount[index] == null ? defaultValue : _GrantAmount[index];
   }
    
   /**
    * Gets the array of Grant Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Grant Amount values.
    */
   public final String[] getGrantAmountArray()
   {
      return _GrantAmount;
   }
    
   /**
    * Gets the Information Completed field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Information Completed or null.
    */
   public final Boolean getInfoCompleted( int index )
   {
      return _InfoCompleted[index];
   }
    
   /**
    * Gets the Information Completed field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Information Completed or the specified default value.
    */
   public final boolean getInfoCompleted( int index, boolean defaultValue )
   {
      return _InfoCompleted[index] == null ? defaultValue : _InfoCompleted[index].booleanValue();
   }
    
   /**
    * Gets the array of Information Completed fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Information Completed values.
    */
   public final Boolean[] getInfoCompletedArray()
   {
      return _InfoCompleted;
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
      
      _TransId = resizeArray( _TransId, _RepeatCount );
      _StatusCode = resizeArray( _StatusCode, _RepeatCount );
      _BeneName = resizeArray( _BeneName, _RepeatCount );
      _EffectiveDate = resizeArray( _EffectiveDate, _RepeatCount );
      _RESPLetter = resizeArray( _RESPLetter, _RepeatCount );
      _TerminateDate = resizeArray( _TerminateDate, _RepeatCount );
      _YTDContr = resizeArray( _YTDContr, _RepeatCount );
      _LifeContr = resizeArray( _LifeContr, _RepeatCount );
      _RedLifeContr = resizeArray( _RedLifeContr, _RepeatCount );
      _UnAssisted = resizeArray( _UnAssisted, _RepeatCount );
      _Assisted = resizeArray( _Assisted, _RepeatCount );
      _GrantAmount = resizeArray( _GrantAmount, _RepeatCount );
      _InfoCompleted = resizeArray( _InfoCompleted, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _TransId[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _StatusCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BeneName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _RESPLetter[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TerminateDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _YTDContr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LifeContr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RedLifeContr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UnAssisted[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Assisted[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GrantAmount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _InfoCompleted[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      }
      

   }

}
      
