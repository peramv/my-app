
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Review Detail Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/ReviewDetlInq.doc">ReviewDetlInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class ReviewDetlInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Acct Review Recid member array.
    */
   private Integer[] _AcctReviewRId = null;
   
   /**
    * Scheduled Review Date member array.
    */
   private Date[] _SchedReviewDate = null;
   
   /**
    * Actual Review Date member array.
    */
   private Date[] _ActualReviewDate = null;
   
   /**
    * Comments Line1 member array.
    */
   private String[] _Comments1 = null;
   
   /**
    * Overriden member array.
    */
   private Integer[] _Overriden = null;
   
   /**
    * Date Processed member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * Processed by  (user) member array.
    */
   private String[] _UserName = null;
   
   /**
    * Date Modified member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * Modified by (user) member array.
    */
   private String[] _ModUser = null;
   
   /**
    * Comments Line 2 member array.
    */
   private String[] _Comments2 = null;
   
   /**
    * Comments Line 3 member array.
    */
   private String[] _Comments3 = null;
   

   /**
    * Constructs the ReviewDetlInqView object.
    * 
    */
   public ReviewDetlInqView()
   {
      super ( new ReviewDetlInqRequest() );
   }

   /**
    * Constructs the ReviewDetlInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public ReviewDetlInqView( String hostEncoding )
   {
      super ( new ReviewDetlInqRequest( hostEncoding ) );
   }

   /**
    * Gets the ReviewDetlInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The ReviewDetlInqRequest object.
    */
   public final ReviewDetlInqRequest getRequest()
   {
      return (ReviewDetlInqRequest)getIFastRequest();
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
    * Gets the Acct Review Recid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Acct Review Recid or null.
    */
   public final Integer getAcctReviewRId( int index )
   {
      return _AcctReviewRId[index];
   }
    
   /**
    * Gets the Acct Review Recid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Acct Review Recid or the specified default value.
    */
   public final int getAcctReviewRId( int index, int defaultValue )
   {
      return _AcctReviewRId[index] == null ? defaultValue : _AcctReviewRId[index].intValue();
   }
    
   /**
    * Gets the array of Acct Review Recid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Acct Review Recid values.
    */
   public final Integer[] getAcctReviewRIdArray()
   {
      return _AcctReviewRId;
   }
    
   /**
    * Gets the Scheduled Review Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Scheduled Review Date or null.
    */
   public final Date getSchedReviewDate( int index )
   {
      return _SchedReviewDate[index];
   }
    
   /**
    * Gets the Scheduled Review Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Scheduled Review Date or the specified default value.
    */
   public final Date getSchedReviewDate( int index, Date defaultValue )
   {
      return _SchedReviewDate[index] == null ? defaultValue : _SchedReviewDate[index];
   }
    
   /**
    * Gets the array of Scheduled Review Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Scheduled Review Date values.
    */
   public final Date[] getSchedReviewDateArray()
   {
      return _SchedReviewDate;
   }
    
   /**
    * Gets the Actual Review Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Actual Review Date or null.
    */
   public final Date getActualReviewDate( int index )
   {
      return _ActualReviewDate[index];
   }
    
   /**
    * Gets the Actual Review Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Actual Review Date or the specified default value.
    */
   public final Date getActualReviewDate( int index, Date defaultValue )
   {
      return _ActualReviewDate[index] == null ? defaultValue : _ActualReviewDate[index];
   }
    
   /**
    * Gets the array of Actual Review Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Actual Review Date values.
    */
   public final Date[] getActualReviewDateArray()
   {
      return _ActualReviewDate;
   }
    
   /**
    * Gets the Comments Line1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Comments Line1 or null.
    */
   public final String getComments1( int index )
   {
      return _Comments1[index];
   }
    
   /**
    * Gets the Comments Line1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Comments Line1 or the specified default value.
    */
   public final String getComments1( int index, String defaultValue )
   {
      return _Comments1[index] == null ? defaultValue : _Comments1[index];
   }
    
   /**
    * Gets the array of Comments Line1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Comments Line1 values.
    */
   public final String[] getComments1Array()
   {
      return _Comments1;
   }
    
   /**
    * Gets the Overriden field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Overriden or null.
    */
   public final Integer getOverriden( int index )
   {
      return _Overriden[index];
   }
    
   /**
    * Gets the Overriden field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Overriden or the specified default value.
    */
   public final int getOverriden( int index, int defaultValue )
   {
      return _Overriden[index] == null ? defaultValue : _Overriden[index].intValue();
   }
    
   /**
    * Gets the array of Overriden fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Overriden values.
    */
   public final Integer[] getOverridenArray()
   {
      return _Overriden;
   }
    
   /**
    * Gets the Date Processed field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Date Processed or null.
    */
   public final Date getProcessDate( int index )
   {
      return _ProcessDate[index];
   }
    
   /**
    * Gets the Date Processed field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date Processed or the specified default value.
    */
   public final Date getProcessDate( int index, Date defaultValue )
   {
      return _ProcessDate[index] == null ? defaultValue : _ProcessDate[index];
   }
    
   /**
    * Gets the array of Date Processed fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Date Processed values.
    */
   public final Date[] getProcessDateArray()
   {
      return _ProcessDate;
   }
    
   /**
    * Gets the Processed by  (user) field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Processed by  (user) or null.
    */
   public final String getUserName( int index )
   {
      return _UserName[index];
   }
    
   /**
    * Gets the Processed by  (user) field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Processed by  (user) or the specified default value.
    */
   public final String getUserName( int index, String defaultValue )
   {
      return _UserName[index] == null ? defaultValue : _UserName[index];
   }
    
   /**
    * Gets the array of Processed by  (user) fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Processed by  (user) values.
    */
   public final String[] getUserNameArray()
   {
      return _UserName;
   }
    
   /**
    * Gets the Date Modified field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Date Modified or null.
    */
   public final Date getModDate( int index )
   {
      return _ModDate[index];
   }
    
   /**
    * Gets the Date Modified field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date Modified or the specified default value.
    */
   public final Date getModDate( int index, Date defaultValue )
   {
      return _ModDate[index] == null ? defaultValue : _ModDate[index];
   }
    
   /**
    * Gets the array of Date Modified fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Date Modified values.
    */
   public final Date[] getModDateArray()
   {
      return _ModDate;
   }
    
   /**
    * Gets the Modified by (user) field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Modified by (user) or null.
    */
   public final String getModUser( int index )
   {
      return _ModUser[index];
   }
    
   /**
    * Gets the Modified by (user) field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Modified by (user) or the specified default value.
    */
   public final String getModUser( int index, String defaultValue )
   {
      return _ModUser[index] == null ? defaultValue : _ModUser[index];
   }
    
   /**
    * Gets the array of Modified by (user) fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Modified by (user) values.
    */
   public final String[] getModUserArray()
   {
      return _ModUser;
   }
    
   /**
    * Gets the Comments Line 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Comments Line 2 or null.
    */
   public final String getComments2( int index )
   {
      return _Comments2[index];
   }
    
   /**
    * Gets the Comments Line 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Comments Line 2 or the specified default value.
    */
   public final String getComments2( int index, String defaultValue )
   {
      return _Comments2[index] == null ? defaultValue : _Comments2[index];
   }
    
   /**
    * Gets the array of Comments Line 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Comments Line 2 values.
    */
   public final String[] getComments2Array()
   {
      return _Comments2;
   }
    
   /**
    * Gets the Comments Line 3 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Comments Line 3 or null.
    */
   public final String getComments3( int index )
   {
      return _Comments3[index];
   }
    
   /**
    * Gets the Comments Line 3 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Comments Line 3 or the specified default value.
    */
   public final String getComments3( int index, String defaultValue )
   {
      return _Comments3[index] == null ? defaultValue : _Comments3[index];
   }
    
   /**
    * Gets the array of Comments Line 3 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Comments Line 3 values.
    */
   public final String[] getComments3Array()
   {
      return _Comments3;
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
      
      _AcctReviewRId = resizeArray( _AcctReviewRId, _RepeatCount );
      _SchedReviewDate = resizeArray( _SchedReviewDate, _RepeatCount );
      _ActualReviewDate = resizeArray( _ActualReviewDate, _RepeatCount );
      _Comments1 = resizeArray( _Comments1, _RepeatCount );
      _Overriden = resizeArray( _Overriden, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _UserName = resizeArray( _UserName, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _Comments2 = resizeArray( _Comments2, _RepeatCount );
      _Comments3 = resizeArray( _Comments3, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _AcctReviewRId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _SchedReviewDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ActualReviewDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _Comments1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Overriden[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _UserName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Comments2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Comments3[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
