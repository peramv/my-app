
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * PAC Plan view.
 * For additional view information see <A HREF="../../../../viewspecs/PACPlanInq.doc">PACPlanInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class PACPlanInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Plan Code member array.
    */
   private String[] _rxPlanCode = null;
   
   /**
    * Plan Code Description member array.
    */
   private String[] _PlanCodeDesc = null;
   
   /**
    * Annual Maintenance Fee member array.
    */
   private String[] _AnnualFeeAmt = null;
   
   /**
    * Saving Plan Fee Type member array.
    */
   private String[] _VUBFeeType = null;
   
   /**
    * VUB Fee Fraction 1 member array.
    */
   private Integer[] _VUBFeeFrac1 = null;
   
   /**
    * VUB Fee Fraction 2 member array.
    */
   private Integer[] _VUBFeeFrac2 = null;
   
   /**
    * VUB Fee Rate member array.
    */
   private String[] _VUBFeeRate = null;
   
   /**
    * Index Amount member array.
    */
   private String[] _IndexAmt = null;
   
   /**
    * Index Type member array.
    */
   private String[] _IndexType = null;
   
   /**
    * Index Frequency member array.
    */
   private Integer[] _IndexFrequency = null;
   

   /**
    * Constructs the PACPlanInqView object.
    * 
    */
   public PACPlanInqView()
   {
      super ( new PACPlanInqRequest() );
   }

   /**
    * Constructs the PACPlanInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public PACPlanInqView( String hostEncoding )
   {
      super ( new PACPlanInqRequest( hostEncoding ) );
   }

   /**
    * Gets the PACPlanInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The PACPlanInqRequest object.
    */
   public final PACPlanInqRequest getRequest()
   {
      return (PACPlanInqRequest)getIFastRequest();
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
    * Gets the Plan Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Plan Code or null.
    */
   public final String getrxPlanCode( int index )
   {
      return _rxPlanCode[index];
   }
    
   /**
    * Gets the Plan Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Plan Code or the specified default value.
    */
   public final String getrxPlanCode( int index, String defaultValue )
   {
      return _rxPlanCode[index] == null ? defaultValue : _rxPlanCode[index];
   }
    
   /**
    * Gets the array of Plan Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Plan Code values.
    */
   public final String[] getrxPlanCodeArray()
   {
      return _rxPlanCode;
   }
    
   /**
    * Gets the Plan Code Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Plan Code Description or null.
    */
   public final String getPlanCodeDesc( int index )
   {
      return _PlanCodeDesc[index];
   }
    
   /**
    * Gets the Plan Code Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Plan Code Description or the specified default value.
    */
   public final String getPlanCodeDesc( int index, String defaultValue )
   {
      return _PlanCodeDesc[index] == null ? defaultValue : _PlanCodeDesc[index];
   }
    
   /**
    * Gets the array of Plan Code Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Plan Code Description values.
    */
   public final String[] getPlanCodeDescArray()
   {
      return _PlanCodeDesc;
   }
    
   /**
    * Gets the Annual Maintenance Fee field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Annual Maintenance Fee or null.
    */
   public final String getAnnualFeeAmt( int index )
   {
      return _AnnualFeeAmt[index];
   }
    
   /**
    * Gets the Annual Maintenance Fee field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Annual Maintenance Fee or the specified default value.
    */
   public final String getAnnualFeeAmt( int index, String defaultValue )
   {
      return _AnnualFeeAmt[index] == null ? defaultValue : _AnnualFeeAmt[index];
   }
    
   /**
    * Gets the array of Annual Maintenance Fee fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Annual Maintenance Fee values.
    */
   public final String[] getAnnualFeeAmtArray()
   {
      return _AnnualFeeAmt;
   }
    
   /**
    * Gets the Saving Plan Fee Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Saving Plan Fee Type or null.
    */
   public final String getVUBFeeType( int index )
   {
      return _VUBFeeType[index];
   }
    
   /**
    * Gets the Saving Plan Fee Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Saving Plan Fee Type or the specified default value.
    */
   public final String getVUBFeeType( int index, String defaultValue )
   {
      return _VUBFeeType[index] == null ? defaultValue : _VUBFeeType[index];
   }
    
   /**
    * Gets the array of Saving Plan Fee Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Saving Plan Fee Type values.
    */
   public final String[] getVUBFeeTypeArray()
   {
      return _VUBFeeType;
   }
    
   /**
    * Gets the VUB Fee Fraction 1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the VUB Fee Fraction 1 or null.
    */
   public final Integer getVUBFeeFrac1( int index )
   {
      return _VUBFeeFrac1[index];
   }
    
   /**
    * Gets the VUB Fee Fraction 1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the VUB Fee Fraction 1 or the specified default value.
    */
   public final int getVUBFeeFrac1( int index, int defaultValue )
   {
      return _VUBFeeFrac1[index] == null ? defaultValue : _VUBFeeFrac1[index].intValue();
   }
    
   /**
    * Gets the array of VUB Fee Fraction 1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of VUB Fee Fraction 1 values.
    */
   public final Integer[] getVUBFeeFrac1Array()
   {
      return _VUBFeeFrac1;
   }
    
   /**
    * Gets the VUB Fee Fraction 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the VUB Fee Fraction 2 or null.
    */
   public final Integer getVUBFeeFrac2( int index )
   {
      return _VUBFeeFrac2[index];
   }
    
   /**
    * Gets the VUB Fee Fraction 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the VUB Fee Fraction 2 or the specified default value.
    */
   public final int getVUBFeeFrac2( int index, int defaultValue )
   {
      return _VUBFeeFrac2[index] == null ? defaultValue : _VUBFeeFrac2[index].intValue();
   }
    
   /**
    * Gets the array of VUB Fee Fraction 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of VUB Fee Fraction 2 values.
    */
   public final Integer[] getVUBFeeFrac2Array()
   {
      return _VUBFeeFrac2;
   }
    
   /**
    * Gets the VUB Fee Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the VUB Fee Rate or null.
    */
   public final String getVUBFeeRate( int index )
   {
      return _VUBFeeRate[index];
   }
    
   /**
    * Gets the VUB Fee Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the VUB Fee Rate or the specified default value.
    */
   public final String getVUBFeeRate( int index, String defaultValue )
   {
      return _VUBFeeRate[index] == null ? defaultValue : _VUBFeeRate[index];
   }
    
   /**
    * Gets the array of VUB Fee Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of VUB Fee Rate values.
    */
   public final String[] getVUBFeeRateArray()
   {
      return _VUBFeeRate;
   }
    
   /**
    * Gets the Index Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Index Amount or null.
    */
   public final String getIndexAmt( int index )
   {
      return _IndexAmt[index];
   }
    
   /**
    * Gets the Index Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Index Amount or the specified default value.
    */
   public final String getIndexAmt( int index, String defaultValue )
   {
      return _IndexAmt[index] == null ? defaultValue : _IndexAmt[index];
   }
    
   /**
    * Gets the array of Index Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Index Amount values.
    */
   public final String[] getIndexAmtArray()
   {
      return _IndexAmt;
   }
    
   /**
    * Gets the Index Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Index Type or null.
    */
   public final String getIndexType( int index )
   {
      return _IndexType[index];
   }
    
   /**
    * Gets the Index Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Index Type or the specified default value.
    */
   public final String getIndexType( int index, String defaultValue )
   {
      return _IndexType[index] == null ? defaultValue : _IndexType[index];
   }
    
   /**
    * Gets the array of Index Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Index Type values.
    */
   public final String[] getIndexTypeArray()
   {
      return _IndexType;
   }
    
   /**
    * Gets the Index Frequency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Index Frequency or null.
    */
   public final Integer getIndexFrequency( int index )
   {
      return _IndexFrequency[index];
   }
    
   /**
    * Gets the Index Frequency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Index Frequency or the specified default value.
    */
   public final int getIndexFrequency( int index, int defaultValue )
   {
      return _IndexFrequency[index] == null ? defaultValue : _IndexFrequency[index].intValue();
   }
    
   /**
    * Gets the array of Index Frequency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Index Frequency values.
    */
   public final Integer[] getIndexFrequencyArray()
   {
      return _IndexFrequency;
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
      
      _rxPlanCode = resizeArray( _rxPlanCode, _RepeatCount );
      _PlanCodeDesc = resizeArray( _PlanCodeDesc, _RepeatCount );
      _AnnualFeeAmt = resizeArray( _AnnualFeeAmt, _RepeatCount );
      _VUBFeeType = resizeArray( _VUBFeeType, _RepeatCount );
      _VUBFeeFrac1 = resizeArray( _VUBFeeFrac1, _RepeatCount );
      _VUBFeeFrac2 = resizeArray( _VUBFeeFrac2, _RepeatCount );
      _VUBFeeRate = resizeArray( _VUBFeeRate, _RepeatCount );
      _IndexAmt = resizeArray( _IndexAmt, _RepeatCount );
      _IndexType = resizeArray( _IndexType, _RepeatCount );
      _IndexFrequency = resizeArray( _IndexFrequency, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxPlanCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PlanCodeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AnnualFeeAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _VUBFeeType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _VUBFeeFrac1[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _VUBFeeFrac2[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _VUBFeeRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IndexAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IndexType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IndexFrequency[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
      }
      

   }

}
      
