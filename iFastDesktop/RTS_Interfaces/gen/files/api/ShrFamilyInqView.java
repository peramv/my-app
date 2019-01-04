
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Shareholder Family Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/ShrFamilyInq.doc">ShrFamilyInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class ShrFamilyInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Family Code member array.
    */
   private String[] _FamilyCode = null;
   
   /**
    * Family Name member array.
    */
   private String[] _FamilyName = null;
   
   /**
    * Type member array.
    */
   private String[] _Type = null;
   
   /**
    * Role member array.
    */
   private String[] _Role = null;
   
   /**
    * Shareholder Family recid member array.
    */
   private Integer[] _ShrFamilyRId = null;
   

   /**
    * Constructs the ShrFamilyInqView object.
    * 
    */
   public ShrFamilyInqView()
   {
      super ( new ShrFamilyInqRequest() );
   }

   /**
    * Constructs the ShrFamilyInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public ShrFamilyInqView( String hostEncoding )
   {
      super ( new ShrFamilyInqRequest( hostEncoding ) );
   }

   /**
    * Gets the ShrFamilyInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The ShrFamilyInqRequest object.
    */
   public final ShrFamilyInqRequest getRequest()
   {
      return (ShrFamilyInqRequest)getIFastRequest();
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
   public final String getFamilyCode( int index )
   {
      return _FamilyCode[index];
   }
    
   /**
    * Gets the Family Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Family Code or the specified default value.
    */
   public final String getFamilyCode( int index, String defaultValue )
   {
      return _FamilyCode[index] == null ? defaultValue : _FamilyCode[index];
   }
    
   /**
    * Gets the array of Family Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Family Code values.
    */
   public final String[] getFamilyCodeArray()
   {
      return _FamilyCode;
   }
    
   /**
    * Gets the Family Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Family Name or null.
    */
   public final String getFamilyName( int index )
   {
      return _FamilyName[index];
   }
    
   /**
    * Gets the Family Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Family Name or the specified default value.
    */
   public final String getFamilyName( int index, String defaultValue )
   {
      return _FamilyName[index] == null ? defaultValue : _FamilyName[index];
   }
    
   /**
    * Gets the array of Family Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Family Name values.
    */
   public final String[] getFamilyNameArray()
   {
      return _FamilyName;
   }
    
   /**
    * Gets the Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Type or null.
    */
   public final String getType( int index )
   {
      return _Type[index];
   }
    
   /**
    * Gets the Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Type or the specified default value.
    */
   public final String getType( int index, String defaultValue )
   {
      return _Type[index] == null ? defaultValue : _Type[index];
   }
    
   /**
    * Gets the array of Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Type values.
    */
   public final String[] getTypeArray()
   {
      return _Type;
   }
    
   /**
    * Gets the Role field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Role or null.
    */
   public final String getRole( int index )
   {
      return _Role[index];
   }
    
   /**
    * Gets the Role field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Role or the specified default value.
    */
   public final String getRole( int index, String defaultValue )
   {
      return _Role[index] == null ? defaultValue : _Role[index];
   }
    
   /**
    * Gets the array of Role fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Role values.
    */
   public final String[] getRoleArray()
   {
      return _Role;
   }
    
   /**
    * Gets the Shareholder Family recid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Shareholder Family recid or null.
    */
   public final Integer getShrFamilyRId( int index )
   {
      return _ShrFamilyRId[index];
   }
    
   /**
    * Gets the Shareholder Family recid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Shareholder Family recid or the specified default value.
    */
   public final int getShrFamilyRId( int index, int defaultValue )
   {
      return _ShrFamilyRId[index] == null ? defaultValue : _ShrFamilyRId[index].intValue();
   }
    
   /**
    * Gets the array of Shareholder Family recid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Shareholder Family recid values.
    */
   public final Integer[] getShrFamilyRIdArray()
   {
      return _ShrFamilyRId;
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
      
      _FamilyCode = resizeArray( _FamilyCode, _RepeatCount );
      _FamilyName = resizeArray( _FamilyName, _RepeatCount );
      _Type = resizeArray( _Type, _RepeatCount );
      _Role = resizeArray( _Role, _RepeatCount );
      _ShrFamilyRId = resizeArray( _ShrFamilyRId, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _FamilyCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FamilyName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Type[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Role[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ShrFamilyRId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
      }
      

   }

}
      
