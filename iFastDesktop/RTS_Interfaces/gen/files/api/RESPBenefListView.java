
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * RESP Beneficiary List view.
 * For additional view information see <A HREF="../../../../viewspecs/RESPBenefList.doc">RESPBenefList.doc</A>.
 * 
 * @author RTS Generated
 */
public class RESPBenefListView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Beneficiary Name member array.
    */
   private String[] _BeneName = null;
   
   /**
    * RESP Beneficiary ID member array.
    */
   private String[] _RESPBeneID = null;
   
   /**
    * Flag that indicates if Beneficiary is active member array.
    */
   private Boolean[] _Active = null;
   

   /**
    * Constructs the RESPBenefListView object.
    * 
    */
   public RESPBenefListView()
   {
      super ( new RESPBenefListRequest() );
   }

   /**
    * Constructs the RESPBenefListView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public RESPBenefListView( String hostEncoding )
   {
      super ( new RESPBenefListRequest( hostEncoding ) );
   }

   /**
    * Gets the RESPBenefListRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The RESPBenefListRequest object.
    */
   public final RESPBenefListRequest getRequest()
   {
      return (RESPBenefListRequest)getIFastRequest();
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
    * Gets the RESP Beneficiary ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RESP Beneficiary ID or null.
    */
   public final String getRESPBeneID( int index )
   {
      return _RESPBeneID[index];
   }
    
   /**
    * Gets the RESP Beneficiary ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RESP Beneficiary ID or the specified default value.
    */
   public final String getRESPBeneID( int index, String defaultValue )
   {
      return _RESPBeneID[index] == null ? defaultValue : _RESPBeneID[index];
   }
    
   /**
    * Gets the array of RESP Beneficiary ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RESP Beneficiary ID values.
    */
   public final String[] getRESPBeneIDArray()
   {
      return _RESPBeneID;
   }
    
   /**
    * Gets the Flag that indicates if Beneficiary is active field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag that indicates if Beneficiary is active or null.
    */
   public final Boolean getActive( int index )
   {
      return _Active[index];
   }
    
   /**
    * Gets the Flag that indicates if Beneficiary is active field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag that indicates if Beneficiary is active or the specified default value.
    */
   public final boolean getActive( int index, boolean defaultValue )
   {
      return _Active[index] == null ? defaultValue : _Active[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag that indicates if Beneficiary is active fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag that indicates if Beneficiary is active values.
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
      
      _BeneName = resizeArray( _BeneName, _RepeatCount );
      _RESPBeneID = resizeArray( _RESPBeneID, _RepeatCount );
      _Active = resizeArray( _Active, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _BeneName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RESPBeneID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Active[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      }
      

   }

}
      
