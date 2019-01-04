
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * RIF Allocations Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/RIFAllocations.doc">RIFAllocations.doc</A>.
 * 
 * @author RTS Generated
 */
public class RIFAllocationsView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Fund code member array.
    */
   private String[] _FundCode = null;
   
   /**
    * Class Code member array.
    */
   private String[] _ClassCode = null;
   
   /**
    * Percentage member array.
    */
   private String[] _Percentage = null;
   
   /**
    * Allocation amount member array.
    */
   private String[] _AllocAmount = null;
   
   /**
    * RRIF Allocation record ID member array.
    */
   private Integer[] _DistribDetlRid = null;
   

   /**
    * Constructs the RIFAllocationsView object.
    * 
    */
   public RIFAllocationsView()
   {
      super ( new RIFAllocationsRequest() );
   }

   /**
    * Constructs the RIFAllocationsView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public RIFAllocationsView( String hostEncoding )
   {
      super ( new RIFAllocationsRequest( hostEncoding ) );
   }

   /**
    * Gets the RIFAllocationsRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The RIFAllocationsRequest object.
    */
   public final RIFAllocationsRequest getRequest()
   {
      return (RIFAllocationsRequest)getIFastRequest();
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
    * Gets the Fund code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund code or null.
    */
   public final String getFundCode( int index )
   {
      return _FundCode[index];
   }
    
   /**
    * Gets the Fund code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund code or the specified default value.
    */
   public final String getFundCode( int index, String defaultValue )
   {
      return _FundCode[index] == null ? defaultValue : _FundCode[index];
   }
    
   /**
    * Gets the array of Fund code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund code values.
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
    * Gets the Percentage field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Percentage or null.
    */
   public final String getPercentage( int index )
   {
      return _Percentage[index];
   }
    
   /**
    * Gets the Percentage field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Percentage or the specified default value.
    */
   public final String getPercentage( int index, String defaultValue )
   {
      return _Percentage[index] == null ? defaultValue : _Percentage[index];
   }
    
   /**
    * Gets the array of Percentage fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Percentage values.
    */
   public final String[] getPercentageArray()
   {
      return _Percentage;
   }
    
   /**
    * Gets the Allocation amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Allocation amount or null.
    */
   public final String getAllocAmount( int index )
   {
      return _AllocAmount[index];
   }
    
   /**
    * Gets the Allocation amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Allocation amount or the specified default value.
    */
   public final String getAllocAmount( int index, String defaultValue )
   {
      return _AllocAmount[index] == null ? defaultValue : _AllocAmount[index];
   }
    
   /**
    * Gets the array of Allocation amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Allocation amount values.
    */
   public final String[] getAllocAmountArray()
   {
      return _AllocAmount;
   }
    
   /**
    * Gets the RRIF Allocation record ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RRIF Allocation record ID or null.
    */
   public final Integer getDistribDetlRid( int index )
   {
      return _DistribDetlRid[index];
   }
    
   /**
    * Gets the RRIF Allocation record ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RRIF Allocation record ID or the specified default value.
    */
   public final int getDistribDetlRid( int index, int defaultValue )
   {
      return _DistribDetlRid[index] == null ? defaultValue : _DistribDetlRid[index].intValue();
   }
    
   /**
    * Gets the array of RRIF Allocation record ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RRIF Allocation record ID values.
    */
   public final Integer[] getDistribDetlRidArray()
   {
      return _DistribDetlRid;
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
      _Percentage = resizeArray( _Percentage, _RepeatCount );
      _AllocAmount = resizeArray( _AllocAmount, _RepeatCount );
      _DistribDetlRid = resizeArray( _DistribDetlRid, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _FundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Percentage[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AllocAmount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DistribDetlRid[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
      }
      

   }

}
      
