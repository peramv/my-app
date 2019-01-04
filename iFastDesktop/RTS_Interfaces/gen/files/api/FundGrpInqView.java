
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Fund Group List view.
 * For additional view information see <A HREF="../../../../viewspecs/FundGrpInq.doc">FundGrpInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class FundGrpInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Fund Group member array.
    */
   private String[] _FundGroup = null;
   
   /**
    * Fund Group Name member array.
    */
   private String[] _FundGroupName = null;
   

   /**
    * Constructs the FundGrpInqView object.
    * 
    */
   public FundGrpInqView()
   {
      super ( new FundGrpInqRequest() );
   }

   /**
    * Constructs the FundGrpInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public FundGrpInqView( String hostEncoding )
   {
      super ( new FundGrpInqRequest( hostEncoding ) );
   }

   /**
    * Gets the FundGrpInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The FundGrpInqRequest object.
    */
   public final FundGrpInqRequest getRequest()
   {
      return (FundGrpInqRequest)getIFastRequest();
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
    * Gets the Fund Group field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Group or null.
    */
   public final String getFundGroup( int index )
   {
      return _FundGroup[index];
   }
    
   /**
    * Gets the Fund Group field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Group or the specified default value.
    */
   public final String getFundGroup( int index, String defaultValue )
   {
      return _FundGroup[index] == null ? defaultValue : _FundGroup[index];
   }
    
   /**
    * Gets the array of Fund Group fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Group values.
    */
   public final String[] getFundGroupArray()
   {
      return _FundGroup;
   }
    
   /**
    * Gets the Fund Group Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Group Name or null.
    */
   public final String getFundGroupName( int index )
   {
      return _FundGroupName[index];
   }
    
   /**
    * Gets the Fund Group Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Group Name or the specified default value.
    */
   public final String getFundGroupName( int index, String defaultValue )
   {
      return _FundGroupName[index] == null ? defaultValue : _FundGroupName[index];
   }
    
   /**
    * Gets the array of Fund Group Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Group Name values.
    */
   public final String[] getFundGroupNameArray()
   {
      return _FundGroupName;
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
      
      _FundGroup = resizeArray( _FundGroup, _RepeatCount );
      _FundGroupName = resizeArray( _FundGroupName, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _FundGroup[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundGroupName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
