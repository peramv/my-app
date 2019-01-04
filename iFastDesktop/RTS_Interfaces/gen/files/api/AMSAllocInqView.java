
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * AMS Allocation Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/AMSAllocInq.doc">AMSAllocInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class AMSAllocInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Fund Code member array.
    */
   private String[] _FundCode = null;
   
   /**
    * Class Code member array.
    */
   private String[] _ClassCode = null;
   
   /**
    * Fund Number member array.
    */
   private String[] _Baycom = null;
   
   /**
    * Percentage of allocation member array.
    */
   private String[] _PrcntAlloc = null;
   
   /**
    * AMS Allocation Record Id member array.
    */
   private Integer[] _AMSAllocRId = null;
   
   /**
    * AMS Allocation Version Number member array.
    */
   private Integer[] _AMSAllocVer = null;
   

   /**
    * Constructs the AMSAllocInqView object.
    * 
    */
   public AMSAllocInqView()
   {
      super ( new AMSAllocInqRequest() );
   }

   /**
    * Constructs the AMSAllocInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AMSAllocInqView( String hostEncoding )
   {
      super ( new AMSAllocInqRequest( hostEncoding ) );
   }

   /**
    * Gets the AMSAllocInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AMSAllocInqRequest object.
    */
   public final AMSAllocInqRequest getRequest()
   {
      return (AMSAllocInqRequest)getIFastRequest();
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
    * Gets the Fund Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Code or null.
    */
   public final String getFundCode( int index )
   {
      return _FundCode[index];
   }
    
   /**
    * Gets the Fund Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Code or the specified default value.
    */
   public final String getFundCode( int index, String defaultValue )
   {
      return _FundCode[index] == null ? defaultValue : _FundCode[index];
   }
    
   /**
    * Gets the array of Fund Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Code values.
    */
   public final String[] getFundCodeArray()
   {
      return _FundCode;
   }
    
   /**
    * Gets the Class Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Class Code or null.
    */
   public final String getClassCode( int index )
   {
      return _ClassCode[index];
   }
    
   /**
    * Gets the Class Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class Code or the specified default value.
    */
   public final String getClassCode( int index, String defaultValue )
   {
      return _ClassCode[index] == null ? defaultValue : _ClassCode[index];
   }
    
   /**
    * Gets the array of Class Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Class Code values.
    */
   public final String[] getClassCodeArray()
   {
      return _ClassCode;
   }
    
   /**
    * Gets the Fund Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Number or null.
    */
   public final String getBaycom( int index )
   {
      return _Baycom[index];
   }
    
   /**
    * Gets the Fund Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Number or the specified default value.
    */
   public final String getBaycom( int index, String defaultValue )
   {
      return _Baycom[index] == null ? defaultValue : _Baycom[index];
   }
    
   /**
    * Gets the array of Fund Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Number values.
    */
   public final String[] getBaycomArray()
   {
      return _Baycom;
   }
    
   /**
    * Gets the Percentage of allocation field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Percentage of allocation or null.
    */
   public final String getPrcntAlloc( int index )
   {
      return _PrcntAlloc[index];
   }
    
   /**
    * Gets the Percentage of allocation field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Percentage of allocation or the specified default value.
    */
   public final String getPrcntAlloc( int index, String defaultValue )
   {
      return _PrcntAlloc[index] == null ? defaultValue : _PrcntAlloc[index];
   }
    
   /**
    * Gets the array of Percentage of allocation fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Percentage of allocation values.
    */
   public final String[] getPrcntAllocArray()
   {
      return _PrcntAlloc;
   }
    
   /**
    * Gets the AMS Allocation Record Id field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AMS Allocation Record Id or null.
    */
   public final Integer getAMSAllocRId( int index )
   {
      return _AMSAllocRId[index];
   }
    
   /**
    * Gets the AMS Allocation Record Id field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AMS Allocation Record Id or the specified default value.
    */
   public final int getAMSAllocRId( int index, int defaultValue )
   {
      return _AMSAllocRId[index] == null ? defaultValue : _AMSAllocRId[index].intValue();
   }
    
   /**
    * Gets the array of AMS Allocation Record Id fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AMS Allocation Record Id values.
    */
   public final Integer[] getAMSAllocRIdArray()
   {
      return _AMSAllocRId;
   }
    
   /**
    * Gets the AMS Allocation Version Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AMS Allocation Version Number or null.
    */
   public final Integer getAMSAllocVer( int index )
   {
      return _AMSAllocVer[index];
   }
    
   /**
    * Gets the AMS Allocation Version Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AMS Allocation Version Number or the specified default value.
    */
   public final int getAMSAllocVer( int index, int defaultValue )
   {
      return _AMSAllocVer[index] == null ? defaultValue : _AMSAllocVer[index].intValue();
   }
    
   /**
    * Gets the array of AMS Allocation Version Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AMS Allocation Version Number values.
    */
   public final Integer[] getAMSAllocVerArray()
   {
      return _AMSAllocVer;
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
      
      _FundCode = resizeArray( _FundCode, _RepeatCount );
      _ClassCode = resizeArray( _ClassCode, _RepeatCount );
      _Baycom = resizeArray( _Baycom, _RepeatCount );
      _PrcntAlloc = resizeArray( _PrcntAlloc, _RepeatCount );
      _AMSAllocRId = resizeArray( _AMSAllocRId, _RepeatCount );
      _AMSAllocVer = resizeArray( _AMSAllocVer, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _FundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Baycom[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PrcntAlloc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AMSAllocRId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _AMSAllocVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
      }
      

   }

}
      
