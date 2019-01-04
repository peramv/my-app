
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Account Categories Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/AcctCatInq.doc">AcctCatInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class AcctCatInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Category Type member array.
    */
   private String[] _CategoryType = null;
   
   /**
    * Process Date member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * User Name member array.
    */
   private String[] _UserName = null;
   
   /**
    * AcctCategory Record ID member array.
    */
   private Integer[] _AcctCatRId = null;
   
   /**
    * Category Value member array.
    */
   private String[] _CatValue = null;
   

   /**
    * Constructs the AcctCatInqView object.
    * 
    */
   public AcctCatInqView()
   {
      super ( new AcctCatInqRequest() );
   }

   /**
    * Constructs the AcctCatInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AcctCatInqView( String hostEncoding )
   {
      super ( new AcctCatInqRequest( hostEncoding ) );
   }

   /**
    * Gets the AcctCatInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AcctCatInqRequest object.
    */
   public final AcctCatInqRequest getRequest()
   {
      return (AcctCatInqRequest)getIFastRequest();
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
    * Gets the Category Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Category Type or null.
    */
   public final String getCategoryType( int index )
   {
      return _CategoryType[index];
   }
    
   /**
    * Gets the Category Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Category Type or the specified default value.
    */
   public final String getCategoryType( int index, String defaultValue )
   {
      return _CategoryType[index] == null ? defaultValue : _CategoryType[index];
   }
    
   /**
    * Gets the array of Category Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Category Type values.
    */
   public final String[] getCategoryTypeArray()
   {
      return _CategoryType;
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
    * Gets the AcctCategory Record ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AcctCategory Record ID or null.
    */
   public final Integer getAcctCatRId( int index )
   {
      return _AcctCatRId[index];
   }
    
   /**
    * Gets the AcctCategory Record ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AcctCategory Record ID or the specified default value.
    */
   public final int getAcctCatRId( int index, int defaultValue )
   {
      return _AcctCatRId[index] == null ? defaultValue : _AcctCatRId[index].intValue();
   }
    
   /**
    * Gets the array of AcctCategory Record ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AcctCategory Record ID values.
    */
   public final Integer[] getAcctCatRIdArray()
   {
      return _AcctCatRId;
   }
    
   /**
    * Gets the Category Value field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Category Value or null.
    */
   public final String getCatValue( int index )
   {
      return _CatValue[index];
   }
    
   /**
    * Gets the Category Value field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Category Value or the specified default value.
    */
   public final String getCatValue( int index, String defaultValue )
   {
      return _CatValue[index] == null ? defaultValue : _CatValue[index];
   }
    
   /**
    * Gets the array of Category Value fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Category Value values.
    */
   public final String[] getCatValueArray()
   {
      return _CatValue;
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
      
      _CategoryType = resizeArray( _CategoryType, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _UserName = resizeArray( _UserName, _RepeatCount );
      _AcctCatRId = resizeArray( _AcctCatRId, _RepeatCount );
      _CatValue = resizeArray( _CatValue, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _CategoryType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _UserName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctCatRId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _CatValue[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
