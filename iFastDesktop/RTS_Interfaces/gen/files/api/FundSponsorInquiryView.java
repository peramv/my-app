
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Fund Sponsor Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/FundSponsorInquiry.doc">FundSponsorInquiry.doc</A>.
 * 
 * @author RTS Generated
 */
public class FundSponsorInquiryView extends IFastView implements Serializable
{

   /**
    * Client Level Exchange member variable.
    */
   private String _ClientLvlExch = null;
   
   private int _RepeatCount = 0;
   
   /**
    * Sponsor Code member array.
    */
   private String[] _FundGroup = null;
   
   /**
    * Sponsor Code Description member array.
    */
   private String[] _FundGroupDesc = null;
   
   /**
    * Unit Rounding Method member array.
    */
   private String[] _UnitRoundMethod = null;
   

   /**
    * Constructs the FundSponsorInquiryView object.
    * 
    */
   public FundSponsorInquiryView()
   {
      super ( new FundSponsorInquiryRequest() );
   }

   /**
    * Constructs the FundSponsorInquiryView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public FundSponsorInquiryView( String hostEncoding )
   {
      super ( new FundSponsorInquiryRequest( hostEncoding ) );
   }

   /**
    * Gets the FundSponsorInquiryRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The FundSponsorInquiryRequest object.
    */
   public final FundSponsorInquiryRequest getRequest()
   {
      return (FundSponsorInquiryRequest)getIFastRequest();
   }
        
   /**
    * Gets the Client Level Exchange field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Client Level Exchange or null.
    */
   public final String getClientLvlExch()
   {
      return _ClientLvlExch;
   }
	
   /**
    * Gets the Client Level Exchange field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Client Level Exchange or the specified default value.
    */
   public final String getClientLvlExch( String defaultValue )
   {
      return _ClientLvlExch == null ? defaultValue : _ClientLvlExch;
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
    * Gets the Sponsor Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Sponsor Code or null.
    */
   public final String getFundGroup( int index )
   {
      return _FundGroup[index];
   }
    
   /**
    * Gets the Sponsor Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Sponsor Code or the specified default value.
    */
   public final String getFundGroup( int index, String defaultValue )
   {
      return _FundGroup[index] == null ? defaultValue : _FundGroup[index];
   }
    
   /**
    * Gets the array of Sponsor Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Sponsor Code values.
    */
   public final String[] getFundGroupArray()
   {
      return _FundGroup;
   }
    
   /**
    * Gets the Sponsor Code Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Sponsor Code Description or null.
    */
   public final String getFundGroupDesc( int index )
   {
      return _FundGroupDesc[index];
   }
    
   /**
    * Gets the Sponsor Code Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Sponsor Code Description or the specified default value.
    */
   public final String getFundGroupDesc( int index, String defaultValue )
   {
      return _FundGroupDesc[index] == null ? defaultValue : _FundGroupDesc[index];
   }
    
   /**
    * Gets the array of Sponsor Code Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Sponsor Code Description values.
    */
   public final String[] getFundGroupDescArray()
   {
      return _FundGroupDesc;
   }
    
   /**
    * Gets the Unit Rounding Method field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Unit Rounding Method or null.
    */
   public final String getUnitRoundMethod( int index )
   {
      return _UnitRoundMethod[index];
   }
    
   /**
    * Gets the Unit Rounding Method field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Unit Rounding Method or the specified default value.
    */
   public final String getUnitRoundMethod( int index, String defaultValue )
   {
      return _UnitRoundMethod[index] == null ? defaultValue : _UnitRoundMethod[index];
   }
    
   /**
    * Gets the array of Unit Rounding Method fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Unit Rounding Method values.
    */
   public final String[] getUnitRoundMethodArray()
   {
      return _UnitRoundMethod;
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
      _ClientLvlExch = responseBuffer.decodeString(responseBuffer.getNextField());
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _FundGroup = resizeArray( _FundGroup, _RepeatCount );
      _FundGroupDesc = resizeArray( _FundGroupDesc, _RepeatCount );
      _UnitRoundMethod = resizeArray( _UnitRoundMethod, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _FundGroup[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundGroupDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UnitRoundMethod[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
