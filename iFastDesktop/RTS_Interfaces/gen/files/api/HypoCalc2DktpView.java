
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Hypothetical Redemption Detail view.
 * For additional view information see <A HREF="../../../../viewspecs/HypoCalc2Dktp.doc">HypoCalc2Dktp.doc</A>.
 * 
 * @author RTS Generated
 */
public class HypoCalc2DktpView extends IFastView implements Serializable
{

   /**
    * Update Status member variable.
    */
   private Boolean _UpdateStatus = null;
   
   private int _RepeatCount = 0;
   
   /**
    * Fund Code member array.
    */
   private String[] _FundCode = null;
   
   /**
    * Class Code member array.
    */
   private String[] _ClassCode = null;
   
   /**
    * Baycom member array.
    */
   private String[] _Baycom = null;
   
   /**
    * Fund Currency member array.
    */
   private String[] _FundCurrency = null;
   
   /**
    * Detail Amount member array.
    */
   private String[] _DetlAmt = null;
   
   /**
    * Detail Units member array.
    */
   private String[] _DetlUnits = null;
   
   /**
    * Fee Percent member array.
    */
   private String[] _FeePrcnt = null;
   
   /**
    * Detail DSC Amt member array.
    */
   private String[] _DetlDSCAmt = null;
   
   /**
    * Federal Clawback Detail member array.
    */
   private String[] _DetlFedClawback = null;
   
   /**
    * Provincial Clawback Detail member array.
    */
   private String[] _DetlProvClawback = null;
   
   /**
    * Additional Provincial Clawback Detail member array.
    */
   private String[] _DetlAddlProvClawback = null;
   

   /**
    * Constructs the HypoCalc2DktpView object.
    * 
    */
   public HypoCalc2DktpView()
   {
      super ( new HypoCalc2DktpRequest() );
   }

   /**
    * Constructs the HypoCalc2DktpView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public HypoCalc2DktpView( String hostEncoding )
   {
      super ( new HypoCalc2DktpRequest( hostEncoding ) );
   }

   /**
    * Gets the HypoCalc2DktpRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The HypoCalc2DktpRequest object.
    */
   public final HypoCalc2DktpRequest getRequest()
   {
      return (HypoCalc2DktpRequest)getIFastRequest();
   }
        
   /**
    * Gets the Update Status field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Update Status or null.
    */
   public final Boolean getUpdateStatus()
   {
      return _UpdateStatus;
   }
	
   /**
    * Gets the Update Status field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Update Status or the specified default value.
    */
   public final boolean getUpdateStatus( boolean defaultValue )
   {
      return _UpdateStatus == null ? defaultValue : _UpdateStatus.booleanValue();
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
    * Gets the Class Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Class Code or null.
    */
   public final String getClassCode( int index )
   {
      return _ClassCode[index];
   }
    
   /**
    * Gets the Class Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class Code or the specified default value.
    */
   public final String getClassCode( int index, String defaultValue )
   {
      return _ClassCode[index] == null ? defaultValue : _ClassCode[index];
   }
    
   /**
    * Gets the array of Class Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Class Code values.
    */
   public final String[] getClassCodeArray()
   {
      return _ClassCode;
   }
    
   /**
    * Gets the Baycom field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Baycom or null.
    */
   public final String getBaycom( int index )
   {
      return _Baycom[index];
   }
    
   /**
    * Gets the Baycom field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Baycom or the specified default value.
    */
   public final String getBaycom( int index, String defaultValue )
   {
      return _Baycom[index] == null ? defaultValue : _Baycom[index];
   }
    
   /**
    * Gets the array of Baycom fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Baycom values.
    */
   public final String[] getBaycomArray()
   {
      return _Baycom;
   }
    
   /**
    * Gets the Fund Currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Currency or null.
    */
   public final String getFundCurrency( int index )
   {
      return _FundCurrency[index];
   }
    
   /**
    * Gets the Fund Currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Currency or the specified default value.
    */
   public final String getFundCurrency( int index, String defaultValue )
   {
      return _FundCurrency[index] == null ? defaultValue : _FundCurrency[index];
   }
    
   /**
    * Gets the array of Fund Currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Currency values.
    */
   public final String[] getFundCurrencyArray()
   {
      return _FundCurrency;
   }
    
   /**
    * Gets the Detail Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Detail Amount or null.
    */
   public final String getDetlAmt( int index )
   {
      return _DetlAmt[index];
   }
    
   /**
    * Gets the Detail Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Detail Amount or the specified default value.
    */
   public final String getDetlAmt( int index, String defaultValue )
   {
      return _DetlAmt[index] == null ? defaultValue : _DetlAmt[index];
   }
    
   /**
    * Gets the array of Detail Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Detail Amount values.
    */
   public final String[] getDetlAmtArray()
   {
      return _DetlAmt;
   }
    
   /**
    * Gets the Detail Units field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Detail Units or null.
    */
   public final String getDetlUnits( int index )
   {
      return _DetlUnits[index];
   }
    
   /**
    * Gets the Detail Units field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Detail Units or the specified default value.
    */
   public final String getDetlUnits( int index, String defaultValue )
   {
      return _DetlUnits[index] == null ? defaultValue : _DetlUnits[index];
   }
    
   /**
    * Gets the array of Detail Units fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Detail Units values.
    */
   public final String[] getDetlUnitsArray()
   {
      return _DetlUnits;
   }
    
   /**
    * Gets the Fee Percent field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fee Percent or null.
    */
   public final String getFeePrcnt( int index )
   {
      return _FeePrcnt[index];
   }
    
   /**
    * Gets the Fee Percent field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee Percent or the specified default value.
    */
   public final String getFeePrcnt( int index, String defaultValue )
   {
      return _FeePrcnt[index] == null ? defaultValue : _FeePrcnt[index];
   }
    
   /**
    * Gets the array of Fee Percent fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee Percent values.
    */
   public final String[] getFeePrcntArray()
   {
      return _FeePrcnt;
   }
    
   /**
    * Gets the Detail DSC Amt field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Detail DSC Amt or null.
    */
   public final String getDetlDSCAmt( int index )
   {
      return _DetlDSCAmt[index];
   }
    
   /**
    * Gets the Detail DSC Amt field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Detail DSC Amt or the specified default value.
    */
   public final String getDetlDSCAmt( int index, String defaultValue )
   {
      return _DetlDSCAmt[index] == null ? defaultValue : _DetlDSCAmt[index];
   }
    
   /**
    * Gets the array of Detail DSC Amt fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Detail DSC Amt values.
    */
   public final String[] getDetlDSCAmtArray()
   {
      return _DetlDSCAmt;
   }
    
   /**
    * Gets the Federal Clawback Detail field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Federal Clawback Detail or null.
    */
   public final String getDetlFedClawback( int index )
   {
      return _DetlFedClawback[index];
   }
    
   /**
    * Gets the Federal Clawback Detail field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Federal Clawback Detail or the specified default value.
    */
   public final String getDetlFedClawback( int index, String defaultValue )
   {
      return _DetlFedClawback[index] == null ? defaultValue : _DetlFedClawback[index];
   }
    
   /**
    * Gets the array of Federal Clawback Detail fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Federal Clawback Detail values.
    */
   public final String[] getDetlFedClawbackArray()
   {
      return _DetlFedClawback;
   }
    
   /**
    * Gets the Provincial Clawback Detail field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Provincial Clawback Detail or null.
    */
   public final String getDetlProvClawback( int index )
   {
      return _DetlProvClawback[index];
   }
    
   /**
    * Gets the Provincial Clawback Detail field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Provincial Clawback Detail or the specified default value.
    */
   public final String getDetlProvClawback( int index, String defaultValue )
   {
      return _DetlProvClawback[index] == null ? defaultValue : _DetlProvClawback[index];
   }
    
   /**
    * Gets the array of Provincial Clawback Detail fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Provincial Clawback Detail values.
    */
   public final String[] getDetlProvClawbackArray()
   {
      return _DetlProvClawback;
   }
    
   /**
    * Gets the Additional Provincial Clawback Detail field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Additional Provincial Clawback Detail or null.
    */
   public final String getDetlAddlProvClawback( int index )
   {
      return _DetlAddlProvClawback[index];
   }
    
   /**
    * Gets the Additional Provincial Clawback Detail field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Additional Provincial Clawback Detail or the specified default value.
    */
   public final String getDetlAddlProvClawback( int index, String defaultValue )
   {
      return _DetlAddlProvClawback[index] == null ? defaultValue : _DetlAddlProvClawback[index];
   }
    
   /**
    * Gets the array of Additional Provincial Clawback Detail fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Additional Provincial Clawback Detail values.
    */
   public final String[] getDetlAddlProvClawbackArray()
   {
      return _DetlAddlProvClawback;
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
      _UpdateStatus = responseBuffer.decodeBoolean(responseBuffer.getNextField());
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _FundCode = resizeArray( _FundCode, _RepeatCount );
      _ClassCode = resizeArray( _ClassCode, _RepeatCount );
      _Baycom = resizeArray( _Baycom, _RepeatCount );
      _FundCurrency = resizeArray( _FundCurrency, _RepeatCount );
      _DetlAmt = resizeArray( _DetlAmt, _RepeatCount );
      _DetlUnits = resizeArray( _DetlUnits, _RepeatCount );
      _FeePrcnt = resizeArray( _FeePrcnt, _RepeatCount );
      _DetlDSCAmt = resizeArray( _DetlDSCAmt, _RepeatCount );
      _DetlFedClawback = resizeArray( _DetlFedClawback, _RepeatCount );
      _DetlProvClawback = resizeArray( _DetlProvClawback, _RepeatCount );
      _DetlAddlProvClawback = resizeArray( _DetlAddlProvClawback, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _FundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Baycom[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundCurrency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DetlAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DetlUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FeePrcnt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DetlDSCAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DetlFedClawback[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DetlProvClawback[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DetlAddlProvClawback[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
