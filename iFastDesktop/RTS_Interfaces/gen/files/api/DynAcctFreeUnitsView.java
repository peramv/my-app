
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Dynamic Account/fund free units view.
 * For additional view information see <A HREF="../../../../viewspecs/DynAcctFreeUnits.doc">DynAcctFreeUnits.doc</A>.
 * 
 * @author RTS Generated
 */
public class DynAcctFreeUnitsView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Fund Code member array.
    */
   private String[] _rxFundCode = null;
   
   /**
    * Class Code member array.
    */
   private String[] _rxClassCode = null;
   
   /**
    * Record Type member array.
    */
   private String[] _RecordType = null;
   
   /**
    * Eligible Amount member array.
    */
   private String[] _EligibleAmt = null;
   
   /**
    * Eligible Units member array.
    */
   private String[] _EligibleUnits = null;
   
   /**
    * Used Amount member array.
    */
   private String[] _UsedAmt = null;
   
   /**
    * Used Units member array.
    */
   private String[] _UsedUnits = null;
   
   /**
    * Left Amount member array.
    */
   private String[] _LeftAmt = null;
   
   /**
    * Left Units member array.
    */
   private String[] _LeftUnits = null;
   
   /**
    * MaturityDate member array.
    */
   private Date[] _MaturityDate = null;
   

   /**
    * Constructs the DynAcctFreeUnitsView object.
    * 
    */
   public DynAcctFreeUnitsView()
   {
      super ( new DynAcctFreeUnitsRequest() );
   }

   /**
    * Constructs the DynAcctFreeUnitsView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public DynAcctFreeUnitsView( String hostEncoding )
   {
      super ( new DynAcctFreeUnitsRequest( hostEncoding ) );
   }

   /**
    * Gets the DynAcctFreeUnitsRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The DynAcctFreeUnitsRequest object.
    */
   public final DynAcctFreeUnitsRequest getRequest()
   {
      return (DynAcctFreeUnitsRequest)getIFastRequest();
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
   public final String getrxFundCode( int index )
   {
      return _rxFundCode[index];
   }
    
   /**
    * Gets the Fund Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Code or the specified default value.
    */
   public final String getrxFundCode( int index, String defaultValue )
   {
      return _rxFundCode[index] == null ? defaultValue : _rxFundCode[index];
   }
    
   /**
    * Gets the array of Fund Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Code values.
    */
   public final String[] getrxFundCodeArray()
   {
      return _rxFundCode;
   }
    
   /**
    * Gets the Class Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Class Code or null.
    */
   public final String getrxClassCode( int index )
   {
      return _rxClassCode[index];
   }
    
   /**
    * Gets the Class Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class Code or the specified default value.
    */
   public final String getrxClassCode( int index, String defaultValue )
   {
      return _rxClassCode[index] == null ? defaultValue : _rxClassCode[index];
   }
    
   /**
    * Gets the array of Class Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Class Code values.
    */
   public final String[] getrxClassCodeArray()
   {
      return _rxClassCode;
   }
    
   /**
    * Gets the Record Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Record Type or null.
    */
   public final String getRecordType( int index )
   {
      return _RecordType[index];
   }
    
   /**
    * Gets the Record Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Record Type or the specified default value.
    */
   public final String getRecordType( int index, String defaultValue )
   {
      return _RecordType[index] == null ? defaultValue : _RecordType[index];
   }
    
   /**
    * Gets the array of Record Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Record Type values.
    */
   public final String[] getRecordTypeArray()
   {
      return _RecordType;
   }
    
   /**
    * Gets the Eligible Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Eligible Amount or null.
    */
   public final String getEligibleAmt( int index )
   {
      return _EligibleAmt[index];
   }
    
   /**
    * Gets the Eligible Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Eligible Amount or the specified default value.
    */
   public final String getEligibleAmt( int index, String defaultValue )
   {
      return _EligibleAmt[index] == null ? defaultValue : _EligibleAmt[index];
   }
    
   /**
    * Gets the array of Eligible Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Eligible Amount values.
    */
   public final String[] getEligibleAmtArray()
   {
      return _EligibleAmt;
   }
    
   /**
    * Gets the Eligible Units field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Eligible Units or null.
    */
   public final String getEligibleUnits( int index )
   {
      return _EligibleUnits[index];
   }
    
   /**
    * Gets the Eligible Units field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Eligible Units or the specified default value.
    */
   public final String getEligibleUnits( int index, String defaultValue )
   {
      return _EligibleUnits[index] == null ? defaultValue : _EligibleUnits[index];
   }
    
   /**
    * Gets the array of Eligible Units fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Eligible Units values.
    */
   public final String[] getEligibleUnitsArray()
   {
      return _EligibleUnits;
   }
    
   /**
    * Gets the Used Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Used Amount or null.
    */
   public final String getUsedAmt( int index )
   {
      return _UsedAmt[index];
   }
    
   /**
    * Gets the Used Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Used Amount or the specified default value.
    */
   public final String getUsedAmt( int index, String defaultValue )
   {
      return _UsedAmt[index] == null ? defaultValue : _UsedAmt[index];
   }
    
   /**
    * Gets the array of Used Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Used Amount values.
    */
   public final String[] getUsedAmtArray()
   {
      return _UsedAmt;
   }
    
   /**
    * Gets the Used Units field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Used Units or null.
    */
   public final String getUsedUnits( int index )
   {
      return _UsedUnits[index];
   }
    
   /**
    * Gets the Used Units field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Used Units or the specified default value.
    */
   public final String getUsedUnits( int index, String defaultValue )
   {
      return _UsedUnits[index] == null ? defaultValue : _UsedUnits[index];
   }
    
   /**
    * Gets the array of Used Units fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Used Units values.
    */
   public final String[] getUsedUnitsArray()
   {
      return _UsedUnits;
   }
    
   /**
    * Gets the Left Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Left Amount or null.
    */
   public final String getLeftAmt( int index )
   {
      return _LeftAmt[index];
   }
    
   /**
    * Gets the Left Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Left Amount or the specified default value.
    */
   public final String getLeftAmt( int index, String defaultValue )
   {
      return _LeftAmt[index] == null ? defaultValue : _LeftAmt[index];
   }
    
   /**
    * Gets the array of Left Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Left Amount values.
    */
   public final String[] getLeftAmtArray()
   {
      return _LeftAmt;
   }
    
   /**
    * Gets the Left Units field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Left Units or null.
    */
   public final String getLeftUnits( int index )
   {
      return _LeftUnits[index];
   }
    
   /**
    * Gets the Left Units field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Left Units or the specified default value.
    */
   public final String getLeftUnits( int index, String defaultValue )
   {
      return _LeftUnits[index] == null ? defaultValue : _LeftUnits[index];
   }
    
   /**
    * Gets the array of Left Units fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Left Units values.
    */
   public final String[] getLeftUnitsArray()
   {
      return _LeftUnits;
   }
    
   /**
    * Gets the MaturityDate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the MaturityDate or null.
    */
   public final Date getMaturityDate( int index )
   {
      return _MaturityDate[index];
   }
    
   /**
    * Gets the MaturityDate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the MaturityDate or the specified default value.
    */
   public final Date getMaturityDate( int index, Date defaultValue )
   {
      return _MaturityDate[index] == null ? defaultValue : _MaturityDate[index];
   }
    
   /**
    * Gets the array of MaturityDate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of MaturityDate values.
    */
   public final Date[] getMaturityDateArray()
   {
      return _MaturityDate;
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
      
      _rxFundCode = resizeArray( _rxFundCode, _RepeatCount );
      _rxClassCode = resizeArray( _rxClassCode, _RepeatCount );
      _RecordType = resizeArray( _RecordType, _RepeatCount );
      _EligibleAmt = resizeArray( _EligibleAmt, _RepeatCount );
      _EligibleUnits = resizeArray( _EligibleUnits, _RepeatCount );
      _UsedAmt = resizeArray( _UsedAmt, _RepeatCount );
      _UsedUnits = resizeArray( _UsedUnits, _RepeatCount );
      _LeftAmt = resizeArray( _LeftAmt, _RepeatCount );
      _LeftUnits = resizeArray( _LeftUnits, _RepeatCount );
      _MaturityDate = resizeArray( _MaturityDate, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxFundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RecordType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EligibleAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EligibleUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UsedAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UsedUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LeftAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LeftUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MaturityDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
      }
      

   }

}
      
