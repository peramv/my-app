
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Shr  Fund Broker  Default Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/ShrFundBrkInq.doc">ShrFundBrkInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class ShrFundBrkInqView extends IFastView implements Serializable
{

   /**
    * Duplicate Exists member variable.
    */
   private String _DuplicateExists = null;
   
   private int _RepeatCount = 0;
   
   /**
    * Fund Code member array.
    */
   private String[] _rxFundCode = null;
   
   /**
    * Fund Broker Code member array.
    */
   private String[] _rxFundBroker = null;
   
   /**
    * IsDefault member array.
    */
   private Boolean[] _IsDefault = null;
   
   /**
    * Fund Broker Elig ID member array.
    */
   private Integer[] _FundBrokerEligID = null;
   
   /**
    * FundBrokerVer member array.
    */
   private Integer[] _FundBrokerEligVer = null;
   
   /**
    * User Name member array.
    */
   private String[] _UserName = null;
   
   /**
    * ProcessDate member array.
    */
   private Date[] _ProcessDate = null;
   

   /**
    * Constructs the ShrFundBrkInqView object.
    * 
    */
   public ShrFundBrkInqView()
   {
      super ( new ShrFundBrkInqRequest() );
   }

   /**
    * Constructs the ShrFundBrkInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public ShrFundBrkInqView( String hostEncoding )
   {
      super ( new ShrFundBrkInqRequest( hostEncoding ) );
   }

   /**
    * Gets the ShrFundBrkInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The ShrFundBrkInqRequest object.
    */
   public final ShrFundBrkInqRequest getRequest()
   {
      return (ShrFundBrkInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Duplicate Exists field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Duplicate Exists or null.
    */
   public final String getDuplicateExists()
   {
      return _DuplicateExists;
   }
	
   /**
    * Gets the Duplicate Exists field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Duplicate Exists or the specified default value.
    */
   public final String getDuplicateExists( String defaultValue )
   {
      return _DuplicateExists == null ? defaultValue : _DuplicateExists;
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
    * Gets the Fund Broker Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Broker Code or null.
    */
   public final String getrxFundBroker( int index )
   {
      return _rxFundBroker[index];
   }
    
   /**
    * Gets the Fund Broker Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Broker Code or the specified default value.
    */
   public final String getrxFundBroker( int index, String defaultValue )
   {
      return _rxFundBroker[index] == null ? defaultValue : _rxFundBroker[index];
   }
    
   /**
    * Gets the array of Fund Broker Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Broker Code values.
    */
   public final String[] getrxFundBrokerArray()
   {
      return _rxFundBroker;
   }
    
   /**
    * Gets the IsDefault field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the IsDefault or null.
    */
   public final Boolean getIsDefault( int index )
   {
      return _IsDefault[index];
   }
    
   /**
    * Gets the IsDefault field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the IsDefault or the specified default value.
    */
   public final boolean getIsDefault( int index, boolean defaultValue )
   {
      return _IsDefault[index] == null ? defaultValue : _IsDefault[index].booleanValue();
   }
    
   /**
    * Gets the array of IsDefault fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of IsDefault values.
    */
   public final Boolean[] getIsDefaultArray()
   {
      return _IsDefault;
   }
    
   /**
    * Gets the Fund Broker Elig ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Broker Elig ID or null.
    */
   public final Integer getFundBrokerEligID( int index )
   {
      return _FundBrokerEligID[index];
   }
    
   /**
    * Gets the Fund Broker Elig ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Broker Elig ID or the specified default value.
    */
   public final int getFundBrokerEligID( int index, int defaultValue )
   {
      return _FundBrokerEligID[index] == null ? defaultValue : _FundBrokerEligID[index].intValue();
   }
    
   /**
    * Gets the array of Fund Broker Elig ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Broker Elig ID values.
    */
   public final Integer[] getFundBrokerEligIDArray()
   {
      return _FundBrokerEligID;
   }
    
   /**
    * Gets the FundBrokerVer field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FundBrokerVer or null.
    */
   public final Integer getFundBrokerEligVer( int index )
   {
      return _FundBrokerEligVer[index];
   }
    
   /**
    * Gets the FundBrokerVer field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FundBrokerVer or the specified default value.
    */
   public final int getFundBrokerEligVer( int index, int defaultValue )
   {
      return _FundBrokerEligVer[index] == null ? defaultValue : _FundBrokerEligVer[index].intValue();
   }
    
   /**
    * Gets the array of FundBrokerVer fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FundBrokerVer values.
    */
   public final Integer[] getFundBrokerEligVerArray()
   {
      return _FundBrokerEligVer;
   }
    
   /**
    * Gets the User Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the User Name or null.
    */
   public final String getUserName( int index )
   {
      return _UserName[index];
   }
    
   /**
    * Gets the User Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the User Name or the specified default value.
    */
   public final String getUserName( int index, String defaultValue )
   {
      return _UserName[index] == null ? defaultValue : _UserName[index];
   }
    
   /**
    * Gets the array of User Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of User Name values.
    */
   public final String[] getUserNameArray()
   {
      return _UserName;
   }
    
   /**
    * Gets the ProcessDate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ProcessDate or null.
    */
   public final Date getProcessDate( int index )
   {
      return _ProcessDate[index];
   }
    
   /**
    * Gets the ProcessDate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ProcessDate or the specified default value.
    */
   public final Date getProcessDate( int index, Date defaultValue )
   {
      return _ProcessDate[index] == null ? defaultValue : _ProcessDate[index];
   }
    
   /**
    * Gets the array of ProcessDate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ProcessDate values.
    */
   public final Date[] getProcessDateArray()
   {
      return _ProcessDate;
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
      _DuplicateExists = responseBuffer.decodeString(responseBuffer.getNextField());
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _rxFundCode = resizeArray( _rxFundCode, _RepeatCount );
      _rxFundBroker = resizeArray( _rxFundBroker, _RepeatCount );
      _IsDefault = resizeArray( _IsDefault, _RepeatCount );
      _FundBrokerEligID = resizeArray( _FundBrokerEligID, _RepeatCount );
      _FundBrokerEligVer = resizeArray( _FundBrokerEligVer, _RepeatCount );
      _UserName = resizeArray( _UserName, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxFundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxFundBroker[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IsDefault[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FundBrokerEligID[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _FundBrokerEligVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _UserName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
      }
      

   }

}
      
