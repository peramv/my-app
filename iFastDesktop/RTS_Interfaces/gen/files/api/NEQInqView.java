
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * NEQ Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/NEQInq.doc">NEQInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class NEQInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * NEQ ID member array.
    */
   private String[] _NEQID = null;
   
   /**
    * FirstName and LastName member array.
    */
   private String[] _Name = null;
   
   /**
    * Where use member array.
    */
   private String[] _WhereUse = null;
   

   /**
    * Constructs the NEQInqView object.
    * 
    */
   public NEQInqView()
   {
      super ( new NEQInqRequest() );
   }

   /**
    * Constructs the NEQInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public NEQInqView( String hostEncoding )
   {
      super ( new NEQInqRequest( hostEncoding ) );
   }

   /**
    * Gets the NEQInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The NEQInqRequest object.
    */
   public final NEQInqRequest getRequest()
   {
      return (NEQInqRequest)getIFastRequest();
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
    * Gets the NEQ ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the NEQ ID or null.
    */
   public final String getNEQID( int index )
   {
      return _NEQID[index];
   }
    
   /**
    * Gets the NEQ ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the NEQ ID or the specified default value.
    */
   public final String getNEQID( int index, String defaultValue )
   {
      return _NEQID[index] == null ? defaultValue : _NEQID[index];
   }
    
   /**
    * Gets the array of NEQ ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of NEQ ID values.
    */
   public final String[] getNEQIDArray()
   {
      return _NEQID;
   }
    
   /**
    * Gets the FirstName and LastName field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FirstName and LastName or null.
    */
   public final String getName( int index )
   {
      return _Name[index];
   }
    
   /**
    * Gets the FirstName and LastName field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FirstName and LastName or the specified default value.
    */
   public final String getName( int index, String defaultValue )
   {
      return _Name[index] == null ? defaultValue : _Name[index];
   }
    
   /**
    * Gets the array of FirstName and LastName fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FirstName and LastName values.
    */
   public final String[] getNameArray()
   {
      return _Name;
   }
    
   /**
    * Gets the Where use field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Where use or null.
    */
   public final String getWhereUse( int index )
   {
      return _WhereUse[index];
   }
    
   /**
    * Gets the Where use field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Where use or the specified default value.
    */
   public final String getWhereUse( int index, String defaultValue )
   {
      return _WhereUse[index] == null ? defaultValue : _WhereUse[index];
   }
    
   /**
    * Gets the array of Where use fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Where use values.
    */
   public final String[] getWhereUseArray()
   {
      return _WhereUse;
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
      
      _NEQID = resizeArray( _NEQID, _RepeatCount );
      _Name = resizeArray( _Name, _RepeatCount );
      _WhereUse = resizeArray( _WhereUse, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _NEQID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Name[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _WhereUse[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
