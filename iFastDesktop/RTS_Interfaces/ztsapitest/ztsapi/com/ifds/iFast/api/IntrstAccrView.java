
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Interest Accrual Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/IntrstAccr.doc">IntrstAccr.doc</A>.
 * 
 * @author RTS Generated
 */
public class IntrstAccrView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Record Type member array.
    */
   private String[] _RecType = null;
   
   /**
    * Fund Code member array.
    */
   private String[] _rxFundCode = null;
   
   /**
    * Class Code member array.
    */
   private String[] _rxClassCode = null;
   
   /**
    * As of Date member array.
    */
   private Date[] _AsofDate = null;
   
   /**
    * Eligible Units member array.
    */
   private String[] _EligibleUnits = null;
   
   /**
    * Interest Rate member array.
    */
   private String[] _IntRate = null;
   
   /**
    * Interest Value member array.
    */
   private String[] _IntValue = null;
   
   /**
    * Interest Paid member array.
    */
   private String[] _IntPaid = null;
   
   /**
    * Accumulated Unpaid Interest Total member array.
    */
   private String[] _AccumTotal = null;
   
   /**
    * Market Value member array.
    */
   private String[] _MktValue = null;
   

   /**
    * Constructs the IntrstAccrView object.
    * 
    */
   public IntrstAccrView()
   {
      super ( new IntrstAccrRequest() );
   }

   /**
    * Constructs the IntrstAccrView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public IntrstAccrView( String hostEncoding )
   {
      super ( new IntrstAccrRequest( hostEncoding ) );
   }

   /**
    * Gets the IntrstAccrRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The IntrstAccrRequest object.
    */
   public final IntrstAccrRequest getRequest()
   {
      return (IntrstAccrRequest)getIFastRequest();
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
    * Gets the Record Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Record Type or null.
    */
   public final String getRecType( int index )
   {
      return _RecType[index];
   }
    
   /**
    * Gets the Record Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Record Type or the specified default value.
    */
   public final String getRecType( int index, String defaultValue )
   {
      return _RecType[index] == null ? defaultValue : _RecType[index];
   }
    
   /**
    * Gets the array of Record Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Record Type values.
    */
   public final String[] getRecTypeArray()
   {
      return _RecType;
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
    * Gets the As of Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the As of Date or null.
    */
   public final Date getAsofDate( int index )
   {
      return _AsofDate[index];
   }
    
   /**
    * Gets the As of Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the As of Date or the specified default value.
    */
   public final Date getAsofDate( int index, Date defaultValue )
   {
      return _AsofDate[index] == null ? defaultValue : _AsofDate[index];
   }
    
   /**
    * Gets the array of As of Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of As of Date values.
    */
   public final Date[] getAsofDateArray()
   {
      return _AsofDate;
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
    * Gets the Interest Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Interest Rate or null.
    */
   public final String getIntRate( int index )
   {
      return _IntRate[index];
   }
    
   /**
    * Gets the Interest Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Interest Rate or the specified default value.
    */
   public final String getIntRate( int index, String defaultValue )
   {
      return _IntRate[index] == null ? defaultValue : _IntRate[index];
   }
    
   /**
    * Gets the array of Interest Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Interest Rate values.
    */
   public final String[] getIntRateArray()
   {
      return _IntRate;
   }
    
   /**
    * Gets the Interest Value field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Interest Value or null.
    */
   public final String getIntValue( int index )
   {
      return _IntValue[index];
   }
    
   /**
    * Gets the Interest Value field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Interest Value or the specified default value.
    */
   public final String getIntValue( int index, String defaultValue )
   {
      return _IntValue[index] == null ? defaultValue : _IntValue[index];
   }
    
   /**
    * Gets the array of Interest Value fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Interest Value values.
    */
   public final String[] getIntValueArray()
   {
      return _IntValue;
   }
    
   /**
    * Gets the Interest Paid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Interest Paid or null.
    */
   public final String getIntPaid( int index )
   {
      return _IntPaid[index];
   }
    
   /**
    * Gets the Interest Paid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Interest Paid or the specified default value.
    */
   public final String getIntPaid( int index, String defaultValue )
   {
      return _IntPaid[index] == null ? defaultValue : _IntPaid[index];
   }
    
   /**
    * Gets the array of Interest Paid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Interest Paid values.
    */
   public final String[] getIntPaidArray()
   {
      return _IntPaid;
   }
    
   /**
    * Gets the Accumulated Unpaid Interest Total field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Accumulated Unpaid Interest Total or null.
    */
   public final String getAccumTotal( int index )
   {
      return _AccumTotal[index];
   }
    
   /**
    * Gets the Accumulated Unpaid Interest Total field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Accumulated Unpaid Interest Total or the specified default value.
    */
   public final String getAccumTotal( int index, String defaultValue )
   {
      return _AccumTotal[index] == null ? defaultValue : _AccumTotal[index];
   }
    
   /**
    * Gets the array of Accumulated Unpaid Interest Total fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Accumulated Unpaid Interest Total values.
    */
   public final String[] getAccumTotalArray()
   {
      return _AccumTotal;
   }
    
   /**
    * Gets the Market Value field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Market Value or null.
    */
   public final String getMktValue( int index )
   {
      return _MktValue[index];
   }
    
   /**
    * Gets the Market Value field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Market Value or the specified default value.
    */
   public final String getMktValue( int index, String defaultValue )
   {
      return _MktValue[index] == null ? defaultValue : _MktValue[index];
   }
    
   /**
    * Gets the array of Market Value fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Market Value values.
    */
   public final String[] getMktValueArray()
   {
      return _MktValue;
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
      
      _RecType = resizeArray( _RecType, _RepeatCount );
      _rxFundCode = resizeArray( _rxFundCode, _RepeatCount );
      _rxClassCode = resizeArray( _rxClassCode, _RepeatCount );
      _AsofDate = resizeArray( _AsofDate, _RepeatCount );
      _EligibleUnits = resizeArray( _EligibleUnits, _RepeatCount );
      _IntRate = resizeArray( _IntRate, _RepeatCount );
      _IntValue = resizeArray( _IntValue, _RepeatCount );
      _IntPaid = resizeArray( _IntPaid, _RepeatCount );
      _AccumTotal = resizeArray( _AccumTotal, _RepeatCount );
      _MktValue = resizeArray( _MktValue, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _RecType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxFundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AsofDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _EligibleUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IntRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IntValue[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IntPaid[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AccumTotal[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MktValue[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
