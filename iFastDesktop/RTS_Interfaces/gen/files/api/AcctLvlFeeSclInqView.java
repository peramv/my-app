
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Account Level Fee Scale Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/AcctLvlFeeSclInq.doc">AcctLvlFeeSclInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class AcctLvlFeeSclInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Account Fee Parm Recid member array.
    */
   private Integer[] _AcctFeeParmId = null;
   
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
    * Constructs the AcctLvlFeeSclInqView object.
    * 
    */
   public AcctLvlFeeSclInqView()
   {
      super ( new AcctLvlFeeSclInqRequest() );
   }

   /**
    * Constructs the AcctLvlFeeSclInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AcctLvlFeeSclInqView( String hostEncoding )
   {
      super ( new AcctLvlFeeSclInqRequest( hostEncoding ) );
   }

   /**
    * Gets the AcctLvlFeeSclInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AcctLvlFeeSclInqRequest object.
    */
   public final AcctLvlFeeSclInqRequest getRequest()
   {
      return (AcctLvlFeeSclInqRequest)getIFastRequest();
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
    * Gets the Account Fee Parm Recid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Fee Parm Recid or null.
    */
   public final Integer getAcctFeeParmId( int index )
   {
      return _AcctFeeParmId[index];
   }
    
   /**
    * Gets the Account Fee Parm Recid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Fee Parm Recid or the specified default value.
    */
   public final int getAcctFeeParmId( int index, int defaultValue )
   {
      return _AcctFeeParmId[index] == null ? defaultValue : _AcctFeeParmId[index].intValue();
   }
    
   /**
    * Gets the array of Account Fee Parm Recid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Fee Parm Recid values.
    */
   public final Integer[] getAcctFeeParmIdArray()
   {
      return _AcctFeeParmId;
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
      
      _AcctFeeParmId = resizeArray( _AcctFeeParmId, _RepeatCount );
      _ScaleRate = resizeArray( _ScaleRate, _RepeatCount );
      _UpperBound = resizeArray( _UpperBound, _RepeatCount );
      _LowerBound = resizeArray( _LowerBound, _RepeatCount );
      _Level = resizeArray( _Level, _RepeatCount );
      _ScaleEffectiveDate = resizeArray( _ScaleEffectiveDate, _RepeatCount );
      _ScaleDetlRid = resizeArray( _ScaleDetlRid, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _AcctFeeParmId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ScaleRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UpperBound[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LowerBound[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Level[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ScaleEffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ScaleDetlRid[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
      }
      

   }

}
      
