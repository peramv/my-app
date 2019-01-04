
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Deduction Inventory Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/DeductInvInq.doc">DeductInvInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class DeductInvInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Inventory Detail ID member array.
    */
   private Integer[] _InvDetlID = null;
   
   /**
    * Deduction Code member array.
    */
   private String[] _DeductCode = null;
   
   /**
    * Based On Code member array.
    */
   private String[] _BasedOnCode = null;
   
   /**
    * Based On Value member array.
    */
   private String[] _BasedOnValue = null;
   
   /**
    * LSIF Code member array.
    */
   private String[] _LSIFCode = null;
   
   /**
    * Charged Amount member array.
    */
   private String[] _ChargedAmt = null;
   
   /**
    * Calculated Amount member array.
    */
   private String[] _CalculatedAmt = null;
   
   /**
    * Deducted Units member array.
    */
   private String[] _DeductedUnits = null;
   
   /**
    * Deduction Description member array.
    */
   private String[] _DeductDesc = null;
   
   /**
    * Inventory Summary ID member array.
    */
   private Integer[] _InvSummID = null;
   

   /**
    * Constructs the DeductInvInqView object.
    * 
    */
   public DeductInvInqView()
   {
      super ( new DeductInvInqRequest() );
   }

   /**
    * Constructs the DeductInvInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public DeductInvInqView( String hostEncoding )
   {
      super ( new DeductInvInqRequest( hostEncoding ) );
   }

   /**
    * Gets the DeductInvInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The DeductInvInqRequest object.
    */
   public final DeductInvInqRequest getRequest()
   {
      return (DeductInvInqRequest)getIFastRequest();
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
    * Gets the Inventory Detail ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Inventory Detail ID or null.
    */
   public final Integer getInvDetlID( int index )
   {
      return _InvDetlID[index];
   }
    
   /**
    * Gets the Inventory Detail ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Inventory Detail ID or the specified default value.
    */
   public final int getInvDetlID( int index, int defaultValue )
   {
      return _InvDetlID[index] == null ? defaultValue : _InvDetlID[index].intValue();
   }
    
   /**
    * Gets the array of Inventory Detail ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Inventory Detail ID values.
    */
   public final Integer[] getInvDetlIDArray()
   {
      return _InvDetlID;
   }
    
   /**
    * Gets the Deduction Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Deduction Code or null.
    */
   public final String getDeductCode( int index )
   {
      return _DeductCode[index];
   }
    
   /**
    * Gets the Deduction Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Deduction Code or the specified default value.
    */
   public final String getDeductCode( int index, String defaultValue )
   {
      return _DeductCode[index] == null ? defaultValue : _DeductCode[index];
   }
    
   /**
    * Gets the array of Deduction Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Deduction Code values.
    */
   public final String[] getDeductCodeArray()
   {
      return _DeductCode;
   }
    
   /**
    * Gets the Based On Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Based On Code or null.
    */
   public final String getBasedOnCode( int index )
   {
      return _BasedOnCode[index];
   }
    
   /**
    * Gets the Based On Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Based On Code or the specified default value.
    */
   public final String getBasedOnCode( int index, String defaultValue )
   {
      return _BasedOnCode[index] == null ? defaultValue : _BasedOnCode[index];
   }
    
   /**
    * Gets the array of Based On Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Based On Code values.
    */
   public final String[] getBasedOnCodeArray()
   {
      return _BasedOnCode;
   }
    
   /**
    * Gets the Based On Value field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Based On Value or null.
    */
   public final String getBasedOnValue( int index )
   {
      return _BasedOnValue[index];
   }
    
   /**
    * Gets the Based On Value field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Based On Value or the specified default value.
    */
   public final String getBasedOnValue( int index, String defaultValue )
   {
      return _BasedOnValue[index] == null ? defaultValue : _BasedOnValue[index];
   }
    
   /**
    * Gets the array of Based On Value fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Based On Value values.
    */
   public final String[] getBasedOnValueArray()
   {
      return _BasedOnValue;
   }
    
   /**
    * Gets the LSIF Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the LSIF Code or null.
    */
   public final String getLSIFCode( int index )
   {
      return _LSIFCode[index];
   }
    
   /**
    * Gets the LSIF Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the LSIF Code or the specified default value.
    */
   public final String getLSIFCode( int index, String defaultValue )
   {
      return _LSIFCode[index] == null ? defaultValue : _LSIFCode[index];
   }
    
   /**
    * Gets the array of LSIF Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of LSIF Code values.
    */
   public final String[] getLSIFCodeArray()
   {
      return _LSIFCode;
   }
    
   /**
    * Gets the Charged Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Charged Amount or null.
    */
   public final String getChargedAmt( int index )
   {
      return _ChargedAmt[index];
   }
    
   /**
    * Gets the Charged Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Charged Amount or the specified default value.
    */
   public final String getChargedAmt( int index, String defaultValue )
   {
      return _ChargedAmt[index] == null ? defaultValue : _ChargedAmt[index];
   }
    
   /**
    * Gets the array of Charged Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Charged Amount values.
    */
   public final String[] getChargedAmtArray()
   {
      return _ChargedAmt;
   }
    
   /**
    * Gets the Calculated Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Calculated Amount or null.
    */
   public final String getCalculatedAmt( int index )
   {
      return _CalculatedAmt[index];
   }
    
   /**
    * Gets the Calculated Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Calculated Amount or the specified default value.
    */
   public final String getCalculatedAmt( int index, String defaultValue )
   {
      return _CalculatedAmt[index] == null ? defaultValue : _CalculatedAmt[index];
   }
    
   /**
    * Gets the array of Calculated Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Calculated Amount values.
    */
   public final String[] getCalculatedAmtArray()
   {
      return _CalculatedAmt;
   }
    
   /**
    * Gets the Deducted Units field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Deducted Units or null.
    */
   public final String getDeductedUnits( int index )
   {
      return _DeductedUnits[index];
   }
    
   /**
    * Gets the Deducted Units field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Deducted Units or the specified default value.
    */
   public final String getDeductedUnits( int index, String defaultValue )
   {
      return _DeductedUnits[index] == null ? defaultValue : _DeductedUnits[index];
   }
    
   /**
    * Gets the array of Deducted Units fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Deducted Units values.
    */
   public final String[] getDeductedUnitsArray()
   {
      return _DeductedUnits;
   }
    
   /**
    * Gets the Deduction Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Deduction Description or null.
    */
   public final String getDeductDesc( int index )
   {
      return _DeductDesc[index];
   }
    
   /**
    * Gets the Deduction Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Deduction Description or the specified default value.
    */
   public final String getDeductDesc( int index, String defaultValue )
   {
      return _DeductDesc[index] == null ? defaultValue : _DeductDesc[index];
   }
    
   /**
    * Gets the array of Deduction Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Deduction Description values.
    */
   public final String[] getDeductDescArray()
   {
      return _DeductDesc;
   }
    
   /**
    * Gets the Inventory Summary ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Inventory Summary ID or null.
    */
   public final Integer getInvSummID( int index )
   {
      return _InvSummID[index];
   }
    
   /**
    * Gets the Inventory Summary ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Inventory Summary ID or the specified default value.
    */
   public final int getInvSummID( int index, int defaultValue )
   {
      return _InvSummID[index] == null ? defaultValue : _InvSummID[index].intValue();
   }
    
   /**
    * Gets the array of Inventory Summary ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Inventory Summary ID values.
    */
   public final Integer[] getInvSummIDArray()
   {
      return _InvSummID;
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
      
      _InvDetlID = resizeArray( _InvDetlID, _RepeatCount );
      _DeductCode = resizeArray( _DeductCode, _RepeatCount );
      _BasedOnCode = resizeArray( _BasedOnCode, _RepeatCount );
      _BasedOnValue = resizeArray( _BasedOnValue, _RepeatCount );
      _LSIFCode = resizeArray( _LSIFCode, _RepeatCount );
      _ChargedAmt = resizeArray( _ChargedAmt, _RepeatCount );
      _CalculatedAmt = resizeArray( _CalculatedAmt, _RepeatCount );
      _DeductedUnits = resizeArray( _DeductedUnits, _RepeatCount );
      _DeductDesc = resizeArray( _DeductDesc, _RepeatCount );
      _InvSummID = resizeArray( _InvSummID, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _InvDetlID[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _DeductCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BasedOnCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BasedOnValue[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LSIFCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ChargedAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CalculatedAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DeductedUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DeductDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _InvSummID[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
      }
      

   }

}
      
