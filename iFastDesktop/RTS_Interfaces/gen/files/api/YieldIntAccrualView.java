
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Yield Interest Accural view.
 * For additional view information see <A HREF="../../../../viewspecs/YieldIntAccrual.doc">YieldIntAccrual.doc</A>.
 * 
 * @author RTS Generated
 */
public class YieldIntAccrualView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * FundCode member array.
    */
   private String[] _rxFundCode = null;
   
   /**
    * Class Code member array.
    */
   private String[] _rxClassCode = null;
   
   /**
    * ValueAsof member array.
    */
   private Date[] _ValueAsOF = null;
   
   /**
    * Factor Code member array.
    */
   private String[] _FactorCode = null;
   
   /**
    * Factor Amount member array.
    */
   private String[] _FactorAmount = null;
   
   /**
    * Transtype member array.
    */
   private String[] _rxTransType = null;
   

   /**
    * Constructs the YieldIntAccrualView object.
    * 
    */
   public YieldIntAccrualView()
   {
      super ( new YieldIntAccrualRequest() );
   }

   /**
    * Constructs the YieldIntAccrualView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public YieldIntAccrualView( String hostEncoding )
   {
      super ( new YieldIntAccrualRequest( hostEncoding ) );
   }

   /**
    * Gets the YieldIntAccrualRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The YieldIntAccrualRequest object.
    */
   public final YieldIntAccrualRequest getRequest()
   {
      return (YieldIntAccrualRequest)getIFastRequest();
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
    * Gets the FundCode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FundCode or null.
    */
   public final String getrxFundCode( int index )
   {
      return _rxFundCode[index];
   }
    
   /**
    * Gets the FundCode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FundCode or the specified default value.
    */
   public final String getrxFundCode( int index, String defaultValue )
   {
      return _rxFundCode[index] == null ? defaultValue : _rxFundCode[index];
   }
    
   /**
    * Gets the array of FundCode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FundCode values.
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
    * Gets the ValueAsof field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ValueAsof or null.
    */
   public final Date getValueAsOF( int index )
   {
      return _ValueAsOF[index];
   }
    
   /**
    * Gets the ValueAsof field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ValueAsof or the specified default value.
    */
   public final Date getValueAsOF( int index, Date defaultValue )
   {
      return _ValueAsOF[index] == null ? defaultValue : _ValueAsOF[index];
   }
    
   /**
    * Gets the array of ValueAsof fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ValueAsof values.
    */
   public final Date[] getValueAsOFArray()
   {
      return _ValueAsOF;
   }
    
   /**
    * Gets the Factor Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Factor Code or null.
    */
   public final String getFactorCode( int index )
   {
      return _FactorCode[index];
   }
    
   /**
    * Gets the Factor Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Factor Code or the specified default value.
    */
   public final String getFactorCode( int index, String defaultValue )
   {
      return _FactorCode[index] == null ? defaultValue : _FactorCode[index];
   }
    
   /**
    * Gets the array of Factor Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Factor Code values.
    */
   public final String[] getFactorCodeArray()
   {
      return _FactorCode;
   }
    
   /**
    * Gets the Factor Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Factor Amount or null.
    */
   public final String getFactorAmount( int index )
   {
      return _FactorAmount[index];
   }
    
   /**
    * Gets the Factor Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Factor Amount or the specified default value.
    */
   public final String getFactorAmount( int index, String defaultValue )
   {
      return _FactorAmount[index] == null ? defaultValue : _FactorAmount[index];
   }
    
   /**
    * Gets the array of Factor Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Factor Amount values.
    */
   public final String[] getFactorAmountArray()
   {
      return _FactorAmount;
   }
    
   /**
    * Gets the Transtype field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transtype or null.
    */
   public final String getrxTransType( int index )
   {
      return _rxTransType[index];
   }
    
   /**
    * Gets the Transtype field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transtype or the specified default value.
    */
   public final String getrxTransType( int index, String defaultValue )
   {
      return _rxTransType[index] == null ? defaultValue : _rxTransType[index];
   }
    
   /**
    * Gets the array of Transtype fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transtype values.
    */
   public final String[] getrxTransTypeArray()
   {
      return _rxTransType;
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
      _ValueAsOF = resizeArray( _ValueAsOF, _RepeatCount );
      _FactorCode = resizeArray( _FactorCode, _RepeatCount );
      _FactorAmount = resizeArray( _FactorAmount, _RepeatCount );
      _rxTransType = resizeArray( _rxTransType, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxFundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ValueAsOF[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _FactorCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FactorAmount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxTransType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
