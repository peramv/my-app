
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Account Reporting FFI Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/AcctRptFFIInq.doc">AcctRptFFIInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class AcctRptFFIInqView extends IFastView implements Serializable
{

   /**
    * Default Reporting FFI member variable.
    */
   private String _DefReportingFFI = null;
   
   private int _RepeatCount = 0;
   
   /**
    * FinInstRegDetlUUID member array.
    */
   private String[] _FinInstRegDetlUUID = null;
   
   /**
    * FILevel member array.
    */
   private String[] _FILevel = null;
   
   /**
    * FICode member array.
    */
   private String[] _FICode = null;
   
   /**
    * FICategory member array.
    */
   private String[] _FICategory = null;
   
   /**
    * ComplyRule member array.
    */
   private String[] _ComplyRule = null;
   
   /**
    * ComplyCode member array.
    */
   private String[] _ComplyCode = null;
   
   /**
    * Description member array.
    */
   private String[] _Description = null;
   
   /**
    * EffectiveDate member array.
    */
   private Date[] _EffectiveDate = null;
   
   /**
    * StopDate member array.
    */
   private Date[] _StopDate = null;
   

   /**
    * Constructs the AcctRptFFIInqView object.
    * 
    */
   public AcctRptFFIInqView()
   {
      super ( new AcctRptFFIInqRequest() );
   }

   /**
    * Constructs the AcctRptFFIInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AcctRptFFIInqView( String hostEncoding )
   {
      super ( new AcctRptFFIInqRequest( hostEncoding ) );
   }

   /**
    * Gets the AcctRptFFIInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AcctRptFFIInqRequest object.
    */
   public final AcctRptFFIInqRequest getRequest()
   {
      return (AcctRptFFIInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Default Reporting FFI field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Default Reporting FFI or null.
    */
   public final String getDefReportingFFI()
   {
      return _DefReportingFFI;
   }
	
   /**
    * Gets the Default Reporting FFI field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Default Reporting FFI or the specified default value.
    */
   public final String getDefReportingFFI( String defaultValue )
   {
      return _DefReportingFFI == null ? defaultValue : _DefReportingFFI;
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
    * Gets the FinInstRegDetlUUID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FinInstRegDetlUUID or null.
    */
   public final String getFinInstRegDetlUUID( int index )
   {
      return _FinInstRegDetlUUID[index];
   }
    
   /**
    * Gets the FinInstRegDetlUUID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FinInstRegDetlUUID or the specified default value.
    */
   public final String getFinInstRegDetlUUID( int index, String defaultValue )
   {
      return _FinInstRegDetlUUID[index] == null ? defaultValue : _FinInstRegDetlUUID[index];
   }
    
   /**
    * Gets the array of FinInstRegDetlUUID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FinInstRegDetlUUID values.
    */
   public final String[] getFinInstRegDetlUUIDArray()
   {
      return _FinInstRegDetlUUID;
   }
    
   /**
    * Gets the FILevel field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FILevel or null.
    */
   public final String getFILevel( int index )
   {
      return _FILevel[index];
   }
    
   /**
    * Gets the FILevel field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FILevel or the specified default value.
    */
   public final String getFILevel( int index, String defaultValue )
   {
      return _FILevel[index] == null ? defaultValue : _FILevel[index];
   }
    
   /**
    * Gets the array of FILevel fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FILevel values.
    */
   public final String[] getFILevelArray()
   {
      return _FILevel;
   }
    
   /**
    * Gets the FICode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FICode or null.
    */
   public final String getFICode( int index )
   {
      return _FICode[index];
   }
    
   /**
    * Gets the FICode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FICode or the specified default value.
    */
   public final String getFICode( int index, String defaultValue )
   {
      return _FICode[index] == null ? defaultValue : _FICode[index];
   }
    
   /**
    * Gets the array of FICode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FICode values.
    */
   public final String[] getFICodeArray()
   {
      return _FICode;
   }
    
   /**
    * Gets the FICategory field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FICategory or null.
    */
   public final String getFICategory( int index )
   {
      return _FICategory[index];
   }
    
   /**
    * Gets the FICategory field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FICategory or the specified default value.
    */
   public final String getFICategory( int index, String defaultValue )
   {
      return _FICategory[index] == null ? defaultValue : _FICategory[index];
   }
    
   /**
    * Gets the array of FICategory fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FICategory values.
    */
   public final String[] getFICategoryArray()
   {
      return _FICategory;
   }
    
   /**
    * Gets the ComplyRule field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ComplyRule or null.
    */
   public final String getComplyRule( int index )
   {
      return _ComplyRule[index];
   }
    
   /**
    * Gets the ComplyRule field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ComplyRule or the specified default value.
    */
   public final String getComplyRule( int index, String defaultValue )
   {
      return _ComplyRule[index] == null ? defaultValue : _ComplyRule[index];
   }
    
   /**
    * Gets the array of ComplyRule fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ComplyRule values.
    */
   public final String[] getComplyRuleArray()
   {
      return _ComplyRule;
   }
    
   /**
    * Gets the ComplyCode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ComplyCode or null.
    */
   public final String getComplyCode( int index )
   {
      return _ComplyCode[index];
   }
    
   /**
    * Gets the ComplyCode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ComplyCode or the specified default value.
    */
   public final String getComplyCode( int index, String defaultValue )
   {
      return _ComplyCode[index] == null ? defaultValue : _ComplyCode[index];
   }
    
   /**
    * Gets the array of ComplyCode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ComplyCode values.
    */
   public final String[] getComplyCodeArray()
   {
      return _ComplyCode;
   }
    
   /**
    * Gets the Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Description or null.
    */
   public final String getDescription( int index )
   {
      return _Description[index];
   }
    
   /**
    * Gets the Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Description or the specified default value.
    */
   public final String getDescription( int index, String defaultValue )
   {
      return _Description[index] == null ? defaultValue : _Description[index];
   }
    
   /**
    * Gets the array of Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Description values.
    */
   public final String[] getDescriptionArray()
   {
      return _Description;
   }
    
   /**
    * Gets the EffectiveDate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the EffectiveDate or null.
    */
   public final Date getEffectiveDate( int index )
   {
      return _EffectiveDate[index];
   }
    
   /**
    * Gets the EffectiveDate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the EffectiveDate or the specified default value.
    */
   public final Date getEffectiveDate( int index, Date defaultValue )
   {
      return _EffectiveDate[index] == null ? defaultValue : _EffectiveDate[index];
   }
    
   /**
    * Gets the array of EffectiveDate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of EffectiveDate values.
    */
   public final Date[] getEffectiveDateArray()
   {
      return _EffectiveDate;
   }
    
   /**
    * Gets the StopDate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the StopDate or null.
    */
   public final Date getStopDate( int index )
   {
      return _StopDate[index];
   }
    
   /**
    * Gets the StopDate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the StopDate or the specified default value.
    */
   public final Date getStopDate( int index, Date defaultValue )
   {
      return _StopDate[index] == null ? defaultValue : _StopDate[index];
   }
    
   /**
    * Gets the array of StopDate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of StopDate values.
    */
   public final Date[] getStopDateArray()
   {
      return _StopDate;
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
      _DefReportingFFI = responseBuffer.decodeString(responseBuffer.getNextField());
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _FinInstRegDetlUUID = resizeArray( _FinInstRegDetlUUID, _RepeatCount );
      _FILevel = resizeArray( _FILevel, _RepeatCount );
      _FICode = resizeArray( _FICode, _RepeatCount );
      _FICategory = resizeArray( _FICategory, _RepeatCount );
      _ComplyRule = resizeArray( _ComplyRule, _RepeatCount );
      _ComplyCode = resizeArray( _ComplyCode, _RepeatCount );
      _Description = resizeArray( _Description, _RepeatCount );
      _EffectiveDate = resizeArray( _EffectiveDate, _RepeatCount );
      _StopDate = resizeArray( _StopDate, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _FinInstRegDetlUUID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FILevel[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FICode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FICategory[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ComplyRule[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ComplyCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Description[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _StopDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
      }
      

   }

}
      
