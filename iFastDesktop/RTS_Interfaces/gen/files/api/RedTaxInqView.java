
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Redemption Code by Tax Type Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/RedTaxInq.doc">RedTaxInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class RedTaxInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Redemption Code member array.
    */
   private String[] _RedCode = null;
   
   /**
    * Redemption Code Description member array.
    */
   private String[] _RedCodeDesc = null;
   
   /**
    * Flag indicating if Maximum applies member array.
    */
   private Boolean[] _MaximumApplies = null;
   
   /**
    * Flag indicating if Mimimum applies member array.
    */
   private Boolean[] _MinimumApplies = null;
   
   /**
    * WDFeeDefn member array.
    */
   private Integer[] _WDFeeDefn = null;
   
   /**
    * DTAEligible member array.
    */
   private String[] _DTAEligible = null;
   

   /**
    * Constructs the RedTaxInqView object.
    * 
    */
   public RedTaxInqView()
   {
      super ( new RedTaxInqRequest() );
   }

   /**
    * Constructs the RedTaxInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public RedTaxInqView( String hostEncoding )
   {
      super ( new RedTaxInqRequest( hostEncoding ) );
   }

   /**
    * Gets the RedTaxInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The RedTaxInqRequest object.
    */
   public final RedTaxInqRequest getRequest()
   {
      return (RedTaxInqRequest)getIFastRequest();
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
    * Gets the Redemption Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Redemption Code or null.
    */
   public final String getRedCode( int index )
   {
      return _RedCode[index];
   }
    
   /**
    * Gets the Redemption Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Redemption Code or the specified default value.
    */
   public final String getRedCode( int index, String defaultValue )
   {
      return _RedCode[index] == null ? defaultValue : _RedCode[index];
   }
    
   /**
    * Gets the array of Redemption Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Redemption Code values.
    */
   public final String[] getRedCodeArray()
   {
      return _RedCode;
   }
    
   /**
    * Gets the Redemption Code Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Redemption Code Description or null.
    */
   public final String getRedCodeDesc( int index )
   {
      return _RedCodeDesc[index];
   }
    
   /**
    * Gets the Redemption Code Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Redemption Code Description or the specified default value.
    */
   public final String getRedCodeDesc( int index, String defaultValue )
   {
      return _RedCodeDesc[index] == null ? defaultValue : _RedCodeDesc[index];
   }
    
   /**
    * Gets the array of Redemption Code Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Redemption Code Description values.
    */
   public final String[] getRedCodeDescArray()
   {
      return _RedCodeDesc;
   }
    
   /**
    * Gets the Flag indicating if Maximum applies field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicating if Maximum applies or null.
    */
   public final Boolean getMaximumApplies( int index )
   {
      return _MaximumApplies[index];
   }
    
   /**
    * Gets the Flag indicating if Maximum applies field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if Maximum applies or the specified default value.
    */
   public final boolean getMaximumApplies( int index, boolean defaultValue )
   {
      return _MaximumApplies[index] == null ? defaultValue : _MaximumApplies[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicating if Maximum applies fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicating if Maximum applies values.
    */
   public final Boolean[] getMaximumAppliesArray()
   {
      return _MaximumApplies;
   }
    
   /**
    * Gets the Flag indicating if Mimimum applies field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicating if Mimimum applies or null.
    */
   public final Boolean getMinimumApplies( int index )
   {
      return _MinimumApplies[index];
   }
    
   /**
    * Gets the Flag indicating if Mimimum applies field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if Mimimum applies or the specified default value.
    */
   public final boolean getMinimumApplies( int index, boolean defaultValue )
   {
      return _MinimumApplies[index] == null ? defaultValue : _MinimumApplies[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicating if Mimimum applies fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicating if Mimimum applies values.
    */
   public final Boolean[] getMinimumAppliesArray()
   {
      return _MinimumApplies;
   }
    
   /**
    * Gets the WDFeeDefn field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the WDFeeDefn or null.
    */
   public final Integer getWDFeeDefn( int index )
   {
      return _WDFeeDefn[index];
   }
    
   /**
    * Gets the WDFeeDefn field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the WDFeeDefn or the specified default value.
    */
   public final int getWDFeeDefn( int index, int defaultValue )
   {
      return _WDFeeDefn[index] == null ? defaultValue : _WDFeeDefn[index].intValue();
   }
    
   /**
    * Gets the array of WDFeeDefn fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of WDFeeDefn values.
    */
   public final Integer[] getWDFeeDefnArray()
   {
      return _WDFeeDefn;
   }
    
   /**
    * Gets the DTAEligible field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the DTAEligible or null.
    */
   public final String getDTAEligible( int index )
   {
      return _DTAEligible[index];
   }
    
   /**
    * Gets the DTAEligible field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the DTAEligible or the specified default value.
    */
   public final String getDTAEligible( int index, String defaultValue )
   {
      return _DTAEligible[index] == null ? defaultValue : _DTAEligible[index];
   }
    
   /**
    * Gets the array of DTAEligible fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of DTAEligible values.
    */
   public final String[] getDTAEligibleArray()
   {
      return _DTAEligible;
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
      
      _RedCode = resizeArray( _RedCode, _RepeatCount );
      _RedCodeDesc = resizeArray( _RedCodeDesc, _RepeatCount );
      _MaximumApplies = resizeArray( _MaximumApplies, _RepeatCount );
      _MinimumApplies = resizeArray( _MinimumApplies, _RepeatCount );
      _WDFeeDefn = resizeArray( _WDFeeDefn, _RepeatCount );
      _DTAEligible = resizeArray( _DTAEligible, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _RedCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RedCodeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MaximumApplies[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _MinimumApplies[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _WDFeeDefn[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _DTAEligible[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
