
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Broker Remarks Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/BrkrRemarksInq.doc">BrkrRemarksInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class BrkrRemarksInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = null;
   
   /**
    * Agency Code member array.
    */
   private String[] _rxAgencyCode = null;
   
   /**
    * Branch Code member array.
    */
   private String[] _rxBranchCode = null;
   
   /**
    * Agent Code member array.
    */
   private String[] _rxAgentCode = null;
   
   /**
    * Remarks Line 1 member array.
    */
   private String[] _Remarks1 = null;
   
   /**
    * Remarks Line 2 member array.
    */
   private String[] _Remarks2 = null;
   
   /**
    * Remarks Line 3 member array.
    */
   private String[] _Remarks3 = null;
   
   /**
    * Remarks Line 4 member array.
    */
   private String[] _Remarks4 = null;
   
   /**
    * Remarks Line 5 member array.
    */
   private String[] _Remarks5 = null;
   
   /**
    * Remarks Line 6 member array.
    */
   private String[] _Remarks6 = null;
   
   /**
    * Remarks Line 7 member array.
    */
   private String[] _Remarks7 = null;
   
   /**
    * Remarks Line 8 member array.
    */
   private String[] _Remarks8 = null;
   
   /**
    * Remarks Line 9 member array.
    */
   private String[] _Remarks9 = null;
   
   /**
    * Remarks Line 10 member array.
    */
   private String[] _Remarks10 = null;
   
   /**
    * Remarks Recid member array.
    */
   private Integer[] _RemarksRId = null;
   

   /**
    * Constructs the BrkrRemarksInqView object.
    * 
    */
   public BrkrRemarksInqView()
   {
      super ( new BrkrRemarksInqRequest() );
   }

   /**
    * Constructs the BrkrRemarksInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public BrkrRemarksInqView( String hostEncoding )
   {
      super ( new BrkrRemarksInqRequest( hostEncoding ) );
   }

   /**
    * Gets the BrkrRemarksInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The BrkrRemarksInqRequest object.
    */
   public final BrkrRemarksInqRequest getRequest()
   {
      return (BrkrRemarksInqRequest)getIFastRequest();
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
    * Gets the Effective Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Effective Date or null.
    */
   public final Date getEffectiveDate( int index )
   {
      return _EffectiveDate[index];
   }
    
   /**
    * Gets the Effective Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Effective Date or the specified default value.
    */
   public final Date getEffectiveDate( int index, Date defaultValue )
   {
      return _EffectiveDate[index] == null ? defaultValue : _EffectiveDate[index];
   }
    
   /**
    * Gets the array of Effective Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Effective Date values.
    */
   public final Date[] getEffectiveDateArray()
   {
      return _EffectiveDate;
   }
    
   /**
    * Gets the Agency Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Agency Code or null.
    */
   public final String getrxAgencyCode( int index )
   {
      return _rxAgencyCode[index];
   }
    
   /**
    * Gets the Agency Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Agency Code or the specified default value.
    */
   public final String getrxAgencyCode( int index, String defaultValue )
   {
      return _rxAgencyCode[index] == null ? defaultValue : _rxAgencyCode[index];
   }
    
   /**
    * Gets the array of Agency Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Agency Code values.
    */
   public final String[] getrxAgencyCodeArray()
   {
      return _rxAgencyCode;
   }
    
   /**
    * Gets the Branch Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Branch Code or null.
    */
   public final String getrxBranchCode( int index )
   {
      return _rxBranchCode[index];
   }
    
   /**
    * Gets the Branch Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Branch Code or the specified default value.
    */
   public final String getrxBranchCode( int index, String defaultValue )
   {
      return _rxBranchCode[index] == null ? defaultValue : _rxBranchCode[index];
   }
    
   /**
    * Gets the array of Branch Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Branch Code values.
    */
   public final String[] getrxBranchCodeArray()
   {
      return _rxBranchCode;
   }
    
   /**
    * Gets the Agent Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Agent Code or null.
    */
   public final String getrxAgentCode( int index )
   {
      return _rxAgentCode[index];
   }
    
   /**
    * Gets the Agent Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Agent Code or the specified default value.
    */
   public final String getrxAgentCode( int index, String defaultValue )
   {
      return _rxAgentCode[index] == null ? defaultValue : _rxAgentCode[index];
   }
    
   /**
    * Gets the array of Agent Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Agent Code values.
    */
   public final String[] getrxAgentCodeArray()
   {
      return _rxAgentCode;
   }
    
   /**
    * Gets the Remarks Line 1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Remarks Line 1 or null.
    */
   public final String getRemarks1( int index )
   {
      return _Remarks1[index];
   }
    
   /**
    * Gets the Remarks Line 1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Remarks Line 1 or the specified default value.
    */
   public final String getRemarks1( int index, String defaultValue )
   {
      return _Remarks1[index] == null ? defaultValue : _Remarks1[index];
   }
    
   /**
    * Gets the array of Remarks Line 1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Remarks Line 1 values.
    */
   public final String[] getRemarks1Array()
   {
      return _Remarks1;
   }
    
   /**
    * Gets the Remarks Line 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Remarks Line 2 or null.
    */
   public final String getRemarks2( int index )
   {
      return _Remarks2[index];
   }
    
   /**
    * Gets the Remarks Line 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Remarks Line 2 or the specified default value.
    */
   public final String getRemarks2( int index, String defaultValue )
   {
      return _Remarks2[index] == null ? defaultValue : _Remarks2[index];
   }
    
   /**
    * Gets the array of Remarks Line 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Remarks Line 2 values.
    */
   public final String[] getRemarks2Array()
   {
      return _Remarks2;
   }
    
   /**
    * Gets the Remarks Line 3 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Remarks Line 3 or null.
    */
   public final String getRemarks3( int index )
   {
      return _Remarks3[index];
   }
    
   /**
    * Gets the Remarks Line 3 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Remarks Line 3 or the specified default value.
    */
   public final String getRemarks3( int index, String defaultValue )
   {
      return _Remarks3[index] == null ? defaultValue : _Remarks3[index];
   }
    
   /**
    * Gets the array of Remarks Line 3 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Remarks Line 3 values.
    */
   public final String[] getRemarks3Array()
   {
      return _Remarks3;
   }
    
   /**
    * Gets the Remarks Line 4 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Remarks Line 4 or null.
    */
   public final String getRemarks4( int index )
   {
      return _Remarks4[index];
   }
    
   /**
    * Gets the Remarks Line 4 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Remarks Line 4 or the specified default value.
    */
   public final String getRemarks4( int index, String defaultValue )
   {
      return _Remarks4[index] == null ? defaultValue : _Remarks4[index];
   }
    
   /**
    * Gets the array of Remarks Line 4 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Remarks Line 4 values.
    */
   public final String[] getRemarks4Array()
   {
      return _Remarks4;
   }
    
   /**
    * Gets the Remarks Line 5 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Remarks Line 5 or null.
    */
   public final String getRemarks5( int index )
   {
      return _Remarks5[index];
   }
    
   /**
    * Gets the Remarks Line 5 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Remarks Line 5 or the specified default value.
    */
   public final String getRemarks5( int index, String defaultValue )
   {
      return _Remarks5[index] == null ? defaultValue : _Remarks5[index];
   }
    
   /**
    * Gets the array of Remarks Line 5 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Remarks Line 5 values.
    */
   public final String[] getRemarks5Array()
   {
      return _Remarks5;
   }
    
   /**
    * Gets the Remarks Line 6 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Remarks Line 6 or null.
    */
   public final String getRemarks6( int index )
   {
      return _Remarks6[index];
   }
    
   /**
    * Gets the Remarks Line 6 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Remarks Line 6 or the specified default value.
    */
   public final String getRemarks6( int index, String defaultValue )
   {
      return _Remarks6[index] == null ? defaultValue : _Remarks6[index];
   }
    
   /**
    * Gets the array of Remarks Line 6 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Remarks Line 6 values.
    */
   public final String[] getRemarks6Array()
   {
      return _Remarks6;
   }
    
   /**
    * Gets the Remarks Line 7 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Remarks Line 7 or null.
    */
   public final String getRemarks7( int index )
   {
      return _Remarks7[index];
   }
    
   /**
    * Gets the Remarks Line 7 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Remarks Line 7 or the specified default value.
    */
   public final String getRemarks7( int index, String defaultValue )
   {
      return _Remarks7[index] == null ? defaultValue : _Remarks7[index];
   }
    
   /**
    * Gets the array of Remarks Line 7 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Remarks Line 7 values.
    */
   public final String[] getRemarks7Array()
   {
      return _Remarks7;
   }
    
   /**
    * Gets the Remarks Line 8 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Remarks Line 8 or null.
    */
   public final String getRemarks8( int index )
   {
      return _Remarks8[index];
   }
    
   /**
    * Gets the Remarks Line 8 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Remarks Line 8 or the specified default value.
    */
   public final String getRemarks8( int index, String defaultValue )
   {
      return _Remarks8[index] == null ? defaultValue : _Remarks8[index];
   }
    
   /**
    * Gets the array of Remarks Line 8 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Remarks Line 8 values.
    */
   public final String[] getRemarks8Array()
   {
      return _Remarks8;
   }
    
   /**
    * Gets the Remarks Line 9 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Remarks Line 9 or null.
    */
   public final String getRemarks9( int index )
   {
      return _Remarks9[index];
   }
    
   /**
    * Gets the Remarks Line 9 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Remarks Line 9 or the specified default value.
    */
   public final String getRemarks9( int index, String defaultValue )
   {
      return _Remarks9[index] == null ? defaultValue : _Remarks9[index];
   }
    
   /**
    * Gets the array of Remarks Line 9 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Remarks Line 9 values.
    */
   public final String[] getRemarks9Array()
   {
      return _Remarks9;
   }
    
   /**
    * Gets the Remarks Line 10 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Remarks Line 10 or null.
    */
   public final String getRemarks10( int index )
   {
      return _Remarks10[index];
   }
    
   /**
    * Gets the Remarks Line 10 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Remarks Line 10 or the specified default value.
    */
   public final String getRemarks10( int index, String defaultValue )
   {
      return _Remarks10[index] == null ? defaultValue : _Remarks10[index];
   }
    
   /**
    * Gets the array of Remarks Line 10 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Remarks Line 10 values.
    */
   public final String[] getRemarks10Array()
   {
      return _Remarks10;
   }
    
   /**
    * Gets the Remarks Recid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Remarks Recid or null.
    */
   public final Integer getRemarksRId( int index )
   {
      return _RemarksRId[index];
   }
    
   /**
    * Gets the Remarks Recid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Remarks Recid or the specified default value.
    */
   public final int getRemarksRId( int index, int defaultValue )
   {
      return _RemarksRId[index] == null ? defaultValue : _RemarksRId[index].intValue();
   }
    
   /**
    * Gets the array of Remarks Recid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Remarks Recid values.
    */
   public final Integer[] getRemarksRIdArray()
   {
      return _RemarksRId;
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
      
      _EffectiveDate = resizeArray( _EffectiveDate, _RepeatCount );
      _rxAgencyCode = resizeArray( _rxAgencyCode, _RepeatCount );
      _rxBranchCode = resizeArray( _rxBranchCode, _RepeatCount );
      _rxAgentCode = resizeArray( _rxAgentCode, _RepeatCount );
      _Remarks1 = resizeArray( _Remarks1, _RepeatCount );
      _Remarks2 = resizeArray( _Remarks2, _RepeatCount );
      _Remarks3 = resizeArray( _Remarks3, _RepeatCount );
      _Remarks4 = resizeArray( _Remarks4, _RepeatCount );
      _Remarks5 = resizeArray( _Remarks5, _RepeatCount );
      _Remarks6 = resizeArray( _Remarks6, _RepeatCount );
      _Remarks7 = resizeArray( _Remarks7, _RepeatCount );
      _Remarks8 = resizeArray( _Remarks8, _RepeatCount );
      _Remarks9 = resizeArray( _Remarks9, _RepeatCount );
      _Remarks10 = resizeArray( _Remarks10, _RepeatCount );
      _RemarksRId = resizeArray( _RemarksRId, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _rxAgencyCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxBranchCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxAgentCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Remarks1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Remarks2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Remarks3[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Remarks4[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Remarks5[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Remarks6[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Remarks7[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Remarks8[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Remarks9[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Remarks10[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RemarksRId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
      }
      

   }

}
      
