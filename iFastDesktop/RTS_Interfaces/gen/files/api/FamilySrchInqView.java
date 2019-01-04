
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Family Code Search view.
 * For additional view information see <A HREF="../../../../viewspecs/FamilySrchInq.doc">FamilySrchInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class FamilySrchInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Family Code member array.
    */
   private String[] _rxFamilyCode = null;
   
   /**
    * Family Name member array.
    */
   private String[] _rxFamilyName = null;
   
   /**
    * Family recid member array.
    */
   private Integer[] _FamilyRId = null;
   

   /**
    * Constructs the FamilySrchInqView object.
    * 
    */
   public FamilySrchInqView()
   {
      super ( new FamilySrchInqRequest() );
   }

   /**
    * Constructs the FamilySrchInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public FamilySrchInqView( String hostEncoding )
   {
      super ( new FamilySrchInqRequest( hostEncoding ) );
   }

   /**
    * Gets the FamilySrchInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The FamilySrchInqRequest object.
    */
   public final FamilySrchInqRequest getRequest()
   {
      return (FamilySrchInqRequest)getIFastRequest();
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
    * Gets the Family Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Family Code or null.
    */
   public final String getrxFamilyCode( int index )
   {
      return _rxFamilyCode[index];
   }
    
   /**
    * Gets the Family Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Family Code or the specified default value.
    */
   public final String getrxFamilyCode( int index, String defaultValue )
   {
      return _rxFamilyCode[index] == null ? defaultValue : _rxFamilyCode[index];
   }
    
   /**
    * Gets the array of Family Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Family Code values.
    */
   public final String[] getrxFamilyCodeArray()
   {
      return _rxFamilyCode;
   }
    
   /**
    * Gets the Family Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Family Name or null.
    */
   public final String getrxFamilyName( int index )
   {
      return _rxFamilyName[index];
   }
    
   /**
    * Gets the Family Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Family Name or the specified default value.
    */
   public final String getrxFamilyName( int index, String defaultValue )
   {
      return _rxFamilyName[index] == null ? defaultValue : _rxFamilyName[index];
   }
    
   /**
    * Gets the array of Family Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Family Name values.
    */
   public final String[] getrxFamilyNameArray()
   {
      return _rxFamilyName;
   }
    
   /**
    * Gets the Family recid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Family recid or null.
    */
   public final Integer getFamilyRId( int index )
   {
      return _FamilyRId[index];
   }
    
   /**
    * Gets the Family recid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Family recid or the specified default value.
    */
   public final int getFamilyRId( int index, int defaultValue )
   {
      return _FamilyRId[index] == null ? defaultValue : _FamilyRId[index].intValue();
   }
    
   /**
    * Gets the array of Family recid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Family recid values.
    */
   public final Integer[] getFamilyRIdArray()
   {
      return _FamilyRId;
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
      
      _rxFamilyCode = resizeArray( _rxFamilyCode, _RepeatCount );
      _rxFamilyName = resizeArray( _rxFamilyName, _RepeatCount );
      _FamilyRId = resizeArray( _FamilyRId, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxFamilyCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxFamilyName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FamilyRId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
      }
      

   }

}
      
