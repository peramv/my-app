
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Funds Per Sponsor List view.
 * For additional view information see <A HREF="../../../../viewspecs/FundsPerSponsor.doc">FundsPerSponsor.doc</A>.
 * 
 * @author RTS Generated
 */
public class FundsPerSponsorView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Fund Code member array.
    */
   private String[] _FundCode = null;
   
   /**
    * Fund Name member array.
    */
   private String[] _FundName = null;
   
   /**
    * Fund Index member array.
    */
   private Integer[] _FundIdx = null;
   

   /**
    * Constructs the FundsPerSponsorView object.
    * 
    */
   public FundsPerSponsorView()
   {
      super ( new FundsPerSponsorRequest() );
   }

   /**
    * Constructs the FundsPerSponsorView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public FundsPerSponsorView( String hostEncoding )
   {
      super ( new FundsPerSponsorRequest( hostEncoding ) );
   }

   /**
    * Gets the FundsPerSponsorRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The FundsPerSponsorRequest object.
    */
   public final FundsPerSponsorRequest getRequest()
   {
      return (FundsPerSponsorRequest)getIFastRequest();
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
    * Gets the Fund Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Name or null.
    */
   public final String getFundName( int index )
   {
      return _FundName[index];
   }
    
   /**
    * Gets the Fund Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Name or the specified default value.
    */
   public final String getFundName( int index, String defaultValue )
   {
      return _FundName[index] == null ? defaultValue : _FundName[index];
   }
    
   /**
    * Gets the array of Fund Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Name values.
    */
   public final String[] getFundNameArray()
   {
      return _FundName;
   }
    
   /**
    * Gets the Fund Index field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Index or null.
    */
   public final Integer getFundIdx( int index )
   {
      return _FundIdx[index];
   }
    
   /**
    * Gets the Fund Index field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Index or the specified default value.
    */
   public final int getFundIdx( int index, int defaultValue )
   {
      return _FundIdx[index] == null ? defaultValue : _FundIdx[index].intValue();
   }
    
   /**
    * Gets the array of Fund Index fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Index values.
    */
   public final Integer[] getFundIdxArray()
   {
      return _FundIdx;
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
      _FundName = resizeArray( _FundName, _RepeatCount );
      _FundIdx = resizeArray( _FundIdx, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _FundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundIdx[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
      }
      

   }

}
      
