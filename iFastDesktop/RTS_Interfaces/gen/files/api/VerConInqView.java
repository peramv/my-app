
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Verify Config Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/VerConInq.doc">VerConInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class VerConInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Verify Category member array.
    */
   private String[] _VerifyCategory = null;
   
   /**
    * Verify Level member array.
    */
   private String[] _VerifyLevel = null;
   
   /**
    * Field to be verified member array.
    */
   private String[] _VerifyField = null;
   
   /**
    * Active member array.
    */
   private Boolean[] _Active = null;
   

   /**
    * Constructs the VerConInqView object.
    * 
    */
   public VerConInqView()
   {
      super ( new VerConInqRequest() );
   }

   /**
    * Constructs the VerConInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public VerConInqView( String hostEncoding )
   {
      super ( new VerConInqRequest( hostEncoding ) );
   }

   /**
    * Gets the VerConInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The VerConInqRequest object.
    */
   public final VerConInqRequest getRequest()
   {
      return (VerConInqRequest)getIFastRequest();
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
    * Gets the Verify Category field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Verify Category or null.
    */
   public final String getVerifyCategory( int index )
   {
      return _VerifyCategory[index];
   }
    
   /**
    * Gets the Verify Category field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Verify Category or the specified default value.
    */
   public final String getVerifyCategory( int index, String defaultValue )
   {
      return _VerifyCategory[index] == null ? defaultValue : _VerifyCategory[index];
   }
    
   /**
    * Gets the array of Verify Category fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Verify Category values.
    */
   public final String[] getVerifyCategoryArray()
   {
      return _VerifyCategory;
   }
    
   /**
    * Gets the Verify Level field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Verify Level or null.
    */
   public final String getVerifyLevel( int index )
   {
      return _VerifyLevel[index];
   }
    
   /**
    * Gets the Verify Level field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Verify Level or the specified default value.
    */
   public final String getVerifyLevel( int index, String defaultValue )
   {
      return _VerifyLevel[index] == null ? defaultValue : _VerifyLevel[index];
   }
    
   /**
    * Gets the array of Verify Level fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Verify Level values.
    */
   public final String[] getVerifyLevelArray()
   {
      return _VerifyLevel;
   }
    
   /**
    * Gets the Field to be verified field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Field to be verified or null.
    */
   public final String getVerifyField( int index )
   {
      return _VerifyField[index];
   }
    
   /**
    * Gets the Field to be verified field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Field to be verified or the specified default value.
    */
   public final String getVerifyField( int index, String defaultValue )
   {
      return _VerifyField[index] == null ? defaultValue : _VerifyField[index];
   }
    
   /**
    * Gets the array of Field to be verified fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Field to be verified values.
    */
   public final String[] getVerifyFieldArray()
   {
      return _VerifyField;
   }
    
   /**
    * Gets the Active field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Active or null.
    */
   public final Boolean getActive( int index )
   {
      return _Active[index];
   }
    
   /**
    * Gets the Active field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Active or the specified default value.
    */
   public final boolean getActive( int index, boolean defaultValue )
   {
      return _Active[index] == null ? defaultValue : _Active[index].booleanValue();
   }
    
   /**
    * Gets the array of Active fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Active values.
    */
   public final Boolean[] getActiveArray()
   {
      return _Active;
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
      
      _VerifyCategory = resizeArray( _VerifyCategory, _RepeatCount );
      _VerifyLevel = resizeArray( _VerifyLevel, _RepeatCount );
      _VerifyField = resizeArray( _VerifyField, _RepeatCount );
      _Active = resizeArray( _Active, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _VerifyCategory[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _VerifyLevel[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _VerifyField[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Active[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      }
      

   }

}
      
