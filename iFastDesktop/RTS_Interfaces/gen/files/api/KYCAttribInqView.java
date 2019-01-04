
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * KYC Attribute List Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/KYCAttribInq.doc">KYCAttribInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class KYCAttribInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * AttribType member array.
    */
   private String[] _AttribType = null;
   
   /**
    * AttribCode member array.
    */
   private String[] _AttribCode = null;
   
   /**
    * AttribStat member array.
    */
   private String[] _AttribStat = null;
   
   /**
    * AttribDesc member array.
    */
   private String[] _AttribDesc = null;
   

   /**
    * Constructs the KYCAttribInqView object.
    * 
    */
   public KYCAttribInqView()
   {
      super ( new KYCAttribInqRequest() );
   }

   /**
    * Constructs the KYCAttribInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public KYCAttribInqView( String hostEncoding )
   {
      super ( new KYCAttribInqRequest( hostEncoding ) );
   }

   /**
    * Gets the KYCAttribInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The KYCAttribInqRequest object.
    */
   public final KYCAttribInqRequest getRequest()
   {
      return (KYCAttribInqRequest)getIFastRequest();
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
    * Gets the AttribType field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AttribType or null.
    */
   public final String getAttribType( int index )
   {
      return _AttribType[index];
   }
    
   /**
    * Gets the AttribType field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AttribType or the specified default value.
    */
   public final String getAttribType( int index, String defaultValue )
   {
      return _AttribType[index] == null ? defaultValue : _AttribType[index];
   }
    
   /**
    * Gets the array of AttribType fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AttribType values.
    */
   public final String[] getAttribTypeArray()
   {
      return _AttribType;
   }
    
   /**
    * Gets the AttribCode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AttribCode or null.
    */
   public final String getAttribCode( int index )
   {
      return _AttribCode[index];
   }
    
   /**
    * Gets the AttribCode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AttribCode or the specified default value.
    */
   public final String getAttribCode( int index, String defaultValue )
   {
      return _AttribCode[index] == null ? defaultValue : _AttribCode[index];
   }
    
   /**
    * Gets the array of AttribCode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AttribCode values.
    */
   public final String[] getAttribCodeArray()
   {
      return _AttribCode;
   }
    
   /**
    * Gets the AttribStat field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AttribStat or null.
    */
   public final String getAttribStat( int index )
   {
      return _AttribStat[index];
   }
    
   /**
    * Gets the AttribStat field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AttribStat or the specified default value.
    */
   public final String getAttribStat( int index, String defaultValue )
   {
      return _AttribStat[index] == null ? defaultValue : _AttribStat[index];
   }
    
   /**
    * Gets the array of AttribStat fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AttribStat values.
    */
   public final String[] getAttribStatArray()
   {
      return _AttribStat;
   }
    
   /**
    * Gets the AttribDesc field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AttribDesc or null.
    */
   public final String getAttribDesc( int index )
   {
      return _AttribDesc[index];
   }
    
   /**
    * Gets the AttribDesc field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AttribDesc or the specified default value.
    */
   public final String getAttribDesc( int index, String defaultValue )
   {
      return _AttribDesc[index] == null ? defaultValue : _AttribDesc[index];
   }
    
   /**
    * Gets the array of AttribDesc fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AttribDesc values.
    */
   public final String[] getAttribDescArray()
   {
      return _AttribDesc;
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
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _AttribType = resizeArray( _AttribType, _RepeatCount );
      _AttribCode = resizeArray( _AttribCode, _RepeatCount );
      _AttribStat = resizeArray( _AttribStat, _RepeatCount );
      _AttribDesc = resizeArray( _AttribDesc, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _AttribType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AttribCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AttribStat[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AttribDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
