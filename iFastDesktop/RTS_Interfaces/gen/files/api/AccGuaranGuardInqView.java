
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Account Guarantee Guard Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/AccGuaranGuardInq.doc">AccGuaranGuardInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class AccGuaranGuardInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Current Guard Option member array.
    */
   private String[] _GuardOptCurrent = null;
   
   /**
    * Future Guard Option member array.
    */
   private String[] _GuardOptAfter = null;
   
   /**
    * Effective Until member array.
    */
   private Date[] _DeffUntil = null;
   
   /**
    * Status member array.
    */
   private Boolean[] _GBCD = null;
   
   /**
    * SEG Guard ID member array.
    */
   private String[] _SEGGuarGuardID = null;
   
   /**
    * Created By member array.
    */
   private String[] _CreatedBy = null;
   
   /**
    * Created Date member array.
    */
   private Date[] _CreatedOn = null;
   
   /**
    * Modify Date member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * Modify User member array.
    */
   private String[] _ModUser = null;
   

   /**
    * Constructs the AccGuaranGuardInqView object.
    * 
    */
   public AccGuaranGuardInqView()
   {
      super ( new AccGuaranGuardInqRequest() );
   }

   /**
    * Constructs the AccGuaranGuardInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AccGuaranGuardInqView( String hostEncoding )
   {
      super ( new AccGuaranGuardInqRequest( hostEncoding ) );
   }

   /**
    * Gets the AccGuaranGuardInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AccGuaranGuardInqRequest object.
    */
   public final AccGuaranGuardInqRequest getRequest()
   {
      return (AccGuaranGuardInqRequest)getIFastRequest();
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
    * Gets the Current Guard Option field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Current Guard Option or null.
    */
   public final String getGuardOptCurrent( int index )
   {
      return _GuardOptCurrent[index];
   }
    
   /**
    * Gets the Current Guard Option field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Current Guard Option or the specified default value.
    */
   public final String getGuardOptCurrent( int index, String defaultValue )
   {
      return _GuardOptCurrent[index] == null ? defaultValue : _GuardOptCurrent[index];
   }
    
   /**
    * Gets the array of Current Guard Option fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Current Guard Option values.
    */
   public final String[] getGuardOptCurrentArray()
   {
      return _GuardOptCurrent;
   }
    
   /**
    * Gets the Future Guard Option field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Future Guard Option or null.
    */
   public final String getGuardOptAfter( int index )
   {
      return _GuardOptAfter[index];
   }
    
   /**
    * Gets the Future Guard Option field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Future Guard Option or the specified default value.
    */
   public final String getGuardOptAfter( int index, String defaultValue )
   {
      return _GuardOptAfter[index] == null ? defaultValue : _GuardOptAfter[index];
   }
    
   /**
    * Gets the array of Future Guard Option fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Future Guard Option values.
    */
   public final String[] getGuardOptAfterArray()
   {
      return _GuardOptAfter;
   }
    
   /**
    * Gets the Effective Until field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Effective Until or null.
    */
   public final Date getDeffUntil( int index )
   {
      return _DeffUntil[index];
   }
    
   /**
    * Gets the Effective Until field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Effective Until or the specified default value.
    */
   public final Date getDeffUntil( int index, Date defaultValue )
   {
      return _DeffUntil[index] == null ? defaultValue : _DeffUntil[index];
   }
    
   /**
    * Gets the array of Effective Until fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Effective Until values.
    */
   public final Date[] getDeffUntilArray()
   {
      return _DeffUntil;
   }
    
   /**
    * Gets the Status field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Status or null.
    */
   public final Boolean getGBCD( int index )
   {
      return _GBCD[index];
   }
    
   /**
    * Gets the Status field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Status or the specified default value.
    */
   public final boolean getGBCD( int index, boolean defaultValue )
   {
      return _GBCD[index] == null ? defaultValue : _GBCD[index].booleanValue();
   }
    
   /**
    * Gets the array of Status fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Status values.
    */
   public final Boolean[] getGBCDArray()
   {
      return _GBCD;
   }
    
   /**
    * Gets the SEG Guard ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SEG Guard ID or null.
    */
   public final String getSEGGuarGuardID( int index )
   {
      return _SEGGuarGuardID[index];
   }
    
   /**
    * Gets the SEG Guard ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SEG Guard ID or the specified default value.
    */
   public final String getSEGGuarGuardID( int index, String defaultValue )
   {
      return _SEGGuarGuardID[index] == null ? defaultValue : _SEGGuarGuardID[index];
   }
    
   /**
    * Gets the array of SEG Guard ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SEG Guard ID values.
    */
   public final String[] getSEGGuarGuardIDArray()
   {
      return _SEGGuarGuardID;
   }
    
   /**
    * Gets the Created By field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Created By or null.
    */
   public final String getCreatedBy( int index )
   {
      return _CreatedBy[index];
   }
    
   /**
    * Gets the Created By field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Created By or the specified default value.
    */
   public final String getCreatedBy( int index, String defaultValue )
   {
      return _CreatedBy[index] == null ? defaultValue : _CreatedBy[index];
   }
    
   /**
    * Gets the array of Created By fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Created By values.
    */
   public final String[] getCreatedByArray()
   {
      return _CreatedBy;
   }
    
   /**
    * Gets the Created Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Created Date or null.
    */
   public final Date getCreatedOn( int index )
   {
      return _CreatedOn[index];
   }
    
   /**
    * Gets the Created Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Created Date or the specified default value.
    */
   public final Date getCreatedOn( int index, Date defaultValue )
   {
      return _CreatedOn[index] == null ? defaultValue : _CreatedOn[index];
   }
    
   /**
    * Gets the array of Created Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Created Date values.
    */
   public final Date[] getCreatedOnArray()
   {
      return _CreatedOn;
   }
    
   /**
    * Gets the Modify Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Modify Date or null.
    */
   public final Date getModDate( int index )
   {
      return _ModDate[index];
   }
    
   /**
    * Gets the Modify Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Modify Date or the specified default value.
    */
   public final Date getModDate( int index, Date defaultValue )
   {
      return _ModDate[index] == null ? defaultValue : _ModDate[index];
   }
    
   /**
    * Gets the array of Modify Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Modify Date values.
    */
   public final Date[] getModDateArray()
   {
      return _ModDate;
   }
    
   /**
    * Gets the Modify User field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Modify User or null.
    */
   public final String getModUser( int index )
   {
      return _ModUser[index];
   }
    
   /**
    * Gets the Modify User field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Modify User or the specified default value.
    */
   public final String getModUser( int index, String defaultValue )
   {
      return _ModUser[index] == null ? defaultValue : _ModUser[index];
   }
    
   /**
    * Gets the array of Modify User fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Modify User values.
    */
   public final String[] getModUserArray()
   {
      return _ModUser;
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
      
      _GuardOptCurrent = resizeArray( _GuardOptCurrent, _RepeatCount );
      _GuardOptAfter = resizeArray( _GuardOptAfter, _RepeatCount );
      _DeffUntil = resizeArray( _DeffUntil, _RepeatCount );
      _GBCD = resizeArray( _GBCD, _RepeatCount );
      _SEGGuarGuardID = resizeArray( _SEGGuarGuardID, _RepeatCount );
      _CreatedBy = resizeArray( _CreatedBy, _RepeatCount );
      _CreatedOn = resizeArray( _CreatedOn, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _GuardOptCurrent[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GuardOptAfter[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DeffUntil[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _GBCD[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _SEGGuarGuardID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CreatedBy[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CreatedOn[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
