
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Seg Fund Contract Validation Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/ContractValidInq.doc">ContractValidInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class ContractValidInqView extends IFastView implements Serializable
{

   /**
    * Allow Update member variable.
    */
   private Boolean _AllowUpdate = null;
   
   private int _RepeatCount = 0;
   
   /**
    * Warning Number member array.
    */
   private Integer[] _WarnCode = null;
   
   /**
    * Warning Message member array.
    */
   private String[] _WarnDesc = null;
   
   /**
    * Warning Params member array.
    */
   private String[] _WarnParam = null;
   
   /**
    * RetType member array.
    */
   private String[] _RetType = null;
   
   /**
    * RuleCode member array.
    */
   private String[] _RuleCode = null;
   
   /**
    * RuleValue member array.
    */
   private String[] _RuleValue = null;
   

   /**
    * Constructs the ContractValidInqView object.
    * 
    */
   public ContractValidInqView()
   {
      super ( new ContractValidInqRequest() );
   }

   /**
    * Constructs the ContractValidInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public ContractValidInqView( String hostEncoding )
   {
      super ( new ContractValidInqRequest( hostEncoding ) );
   }

   /**
    * Gets the ContractValidInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The ContractValidInqRequest object.
    */
   public final ContractValidInqRequest getRequest()
   {
      return (ContractValidInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Allow Update field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Allow Update or null.
    */
   public final Boolean getAllowUpdate()
   {
      return _AllowUpdate;
   }
	
   /**
    * Gets the Allow Update field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Allow Update or the specified default value.
    */
   public final boolean getAllowUpdate( boolean defaultValue )
   {
      return _AllowUpdate == null ? defaultValue : _AllowUpdate.booleanValue();
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
    * Gets the Warning Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Warning Number or null.
    */
   public final Integer getWarnCode( int index )
   {
      return _WarnCode[index];
   }
    
   /**
    * Gets the Warning Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Number or the specified default value.
    */
   public final int getWarnCode( int index, int defaultValue )
   {
      return _WarnCode[index] == null ? defaultValue : _WarnCode[index].intValue();
   }
    
   /**
    * Gets the array of Warning Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Warning Number values.
    */
   public final Integer[] getWarnCodeArray()
   {
      return _WarnCode;
   }
    
   /**
    * Gets the Warning Message field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Warning Message or null.
    */
   public final String getWarnDesc( int index )
   {
      return _WarnDesc[index];
   }
    
   /**
    * Gets the Warning Message field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Message or the specified default value.
    */
   public final String getWarnDesc( int index, String defaultValue )
   {
      return _WarnDesc[index] == null ? defaultValue : _WarnDesc[index];
   }
    
   /**
    * Gets the array of Warning Message fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Warning Message values.
    */
   public final String[] getWarnDescArray()
   {
      return _WarnDesc;
   }
    
   /**
    * Gets the Warning Params field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Warning Params or null.
    */
   public final String getWarnParam( int index )
   {
      return _WarnParam[index];
   }
    
   /**
    * Gets the Warning Params field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Params or the specified default value.
    */
   public final String getWarnParam( int index, String defaultValue )
   {
      return _WarnParam[index] == null ? defaultValue : _WarnParam[index];
   }
    
   /**
    * Gets the array of Warning Params fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Warning Params values.
    */
   public final String[] getWarnParamArray()
   {
      return _WarnParam;
   }
    
   /**
    * Gets the RetType field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RetType or null.
    */
   public final String getRetType( int index )
   {
      return _RetType[index];
   }
    
   /**
    * Gets the RetType field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RetType or the specified default value.
    */
   public final String getRetType( int index, String defaultValue )
   {
      return _RetType[index] == null ? defaultValue : _RetType[index];
   }
    
   /**
    * Gets the array of RetType fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RetType values.
    */
   public final String[] getRetTypeArray()
   {
      return _RetType;
   }
    
   /**
    * Gets the RuleCode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RuleCode or null.
    */
   public final String getRuleCode( int index )
   {
      return _RuleCode[index];
   }
    
   /**
    * Gets the RuleCode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RuleCode or the specified default value.
    */
   public final String getRuleCode( int index, String defaultValue )
   {
      return _RuleCode[index] == null ? defaultValue : _RuleCode[index];
   }
    
   /**
    * Gets the array of RuleCode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RuleCode values.
    */
   public final String[] getRuleCodeArray()
   {
      return _RuleCode;
   }
    
   /**
    * Gets the RuleValue field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RuleValue or null.
    */
   public final String getRuleValue( int index )
   {
      return _RuleValue[index];
   }
    
   /**
    * Gets the RuleValue field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RuleValue or the specified default value.
    */
   public final String getRuleValue( int index, String defaultValue )
   {
      return _RuleValue[index] == null ? defaultValue : _RuleValue[index];
   }
    
   /**
    * Gets the array of RuleValue fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RuleValue values.
    */
   public final String[] getRuleValueArray()
   {
      return _RuleValue;
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
      _AllowUpdate = responseBuffer.decodeBoolean(responseBuffer.getNextField());
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _WarnCode = resizeArray( _WarnCode, _RepeatCount );
      _WarnDesc = resizeArray( _WarnDesc, _RepeatCount );
      _WarnParam = resizeArray( _WarnParam, _RepeatCount );
      _RetType = resizeArray( _RetType, _RepeatCount );
      _RuleCode = resizeArray( _RuleCode, _RepeatCount );
      _RuleValue = resizeArray( _RuleValue, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _WarnCode[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _WarnDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _WarnParam[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RetType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RuleCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RuleValue[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
