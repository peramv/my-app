
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Foreign Content Group Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/ForConGrpInq.doc">ForConGrpInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class ForConGrpInqView extends IFastView implements Serializable
{

   /**
    * Foreign Content ACB Max Percent member variable.
    */
   private String _FrgnACBMax = null;
   
   /**
    * Default Fund member variable.
    */
   private String _FundCode = null;
   
   /**
    * Shareholder Group member variable.
    */
   private String _GroupCode = null;
   
   /**
    * Shareholder Group Name1 member variable.
    */
   private String _GroupName1 = null;
   
   /**
    * Shareholder Group Name2 member variable.
    */
   private String _GroupName2 = null;
   
   /**
    * Overrides member variable.
    */
   private Boolean _Overrides = null;
   
   /**
    * Allocation member variable.
    */
   private Boolean _Allocation = null;
   
   private int _RepeatCount = 0;
   
   /**
    * Tax Type member array.
    */
   private String[] _TaxType = null;
   
   /**
    * Tax Type Desc member array.
    */
   private String[] _TaxTypeDesc = null;
   

   /**
    * Constructs the ForConGrpInqView object.
    * 
    */
   public ForConGrpInqView()
   {
      super ( new ForConGrpInqRequest() );
   }

   /**
    * Constructs the ForConGrpInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public ForConGrpInqView( String hostEncoding )
   {
      super ( new ForConGrpInqRequest( hostEncoding ) );
   }

   /**
    * Gets the ForConGrpInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The ForConGrpInqRequest object.
    */
   public final ForConGrpInqRequest getRequest()
   {
      return (ForConGrpInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Foreign Content ACB Max Percent field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Foreign Content ACB Max Percent or null.
    */
   public final String getFrgnACBMax()
   {
      return _FrgnACBMax;
   }
	
   /**
    * Gets the Foreign Content ACB Max Percent field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Foreign Content ACB Max Percent or the specified default value.
    */
   public final String getFrgnACBMax( String defaultValue )
   {
      return _FrgnACBMax == null ? defaultValue : _FrgnACBMax;
   }
                  
   /**
    * Gets the Default Fund field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Default Fund or null.
    */
   public final String getFundCode()
   {
      return _FundCode;
   }
	
   /**
    * Gets the Default Fund field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Default Fund or the specified default value.
    */
   public final String getFundCode( String defaultValue )
   {
      return _FundCode == null ? defaultValue : _FundCode;
   }
                  
   /**
    * Gets the Shareholder Group field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Shareholder Group or null.
    */
   public final String getGroupCode()
   {
      return _GroupCode;
   }
	
   /**
    * Gets the Shareholder Group field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Shareholder Group or the specified default value.
    */
   public final String getGroupCode( String defaultValue )
   {
      return _GroupCode == null ? defaultValue : _GroupCode;
   }
                  
   /**
    * Gets the Shareholder Group Name1 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Shareholder Group Name1 or null.
    */
   public final String getGroupName1()
   {
      return _GroupName1;
   }
	
   /**
    * Gets the Shareholder Group Name1 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Shareholder Group Name1 or the specified default value.
    */
   public final String getGroupName1( String defaultValue )
   {
      return _GroupName1 == null ? defaultValue : _GroupName1;
   }
                  
   /**
    * Gets the Shareholder Group Name2 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Shareholder Group Name2 or null.
    */
   public final String getGroupName2()
   {
      return _GroupName2;
   }
	
   /**
    * Gets the Shareholder Group Name2 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Shareholder Group Name2 or the specified default value.
    */
   public final String getGroupName2( String defaultValue )
   {
      return _GroupName2 == null ? defaultValue : _GroupName2;
   }
                  
   /**
    * Gets the Overrides field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Overrides or null.
    */
   public final Boolean getOverrides()
   {
      return _Overrides;
   }
	
   /**
    * Gets the Overrides field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Overrides or the specified default value.
    */
   public final boolean getOverrides( boolean defaultValue )
   {
      return _Overrides == null ? defaultValue : _Overrides.booleanValue();
   }
                  
   /**
    * Gets the Allocation field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Allocation or null.
    */
   public final Boolean getAllocation()
   {
      return _Allocation;
   }
	
   /**
    * Gets the Allocation field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Allocation or the specified default value.
    */
   public final boolean getAllocation( boolean defaultValue )
   {
      return _Allocation == null ? defaultValue : _Allocation.booleanValue();
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
    * Gets the Tax Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax Type or null.
    */
   public final String getTaxType( int index )
   {
      return _TaxType[index];
   }
    
   /**
    * Gets the Tax Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Type or the specified default value.
    */
   public final String getTaxType( int index, String defaultValue )
   {
      return _TaxType[index] == null ? defaultValue : _TaxType[index];
   }
    
   /**
    * Gets the array of Tax Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax Type values.
    */
   public final String[] getTaxTypeArray()
   {
      return _TaxType;
   }
    
   /**
    * Gets the Tax Type Desc field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax Type Desc or null.
    */
   public final String getTaxTypeDesc( int index )
   {
      return _TaxTypeDesc[index];
   }
    
   /**
    * Gets the Tax Type Desc field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Type Desc or the specified default value.
    */
   public final String getTaxTypeDesc( int index, String defaultValue )
   {
      return _TaxTypeDesc[index] == null ? defaultValue : _TaxTypeDesc[index];
   }
    
   /**
    * Gets the array of Tax Type Desc fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax Type Desc values.
    */
   public final String[] getTaxTypeDescArray()
   {
      return _TaxTypeDesc;
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
      _FrgnACBMax = responseBuffer.decodeString(responseBuffer.getNextField());
      _FundCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _GroupCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _GroupName1 = responseBuffer.decodeString(responseBuffer.getNextField());
      _GroupName2 = responseBuffer.decodeString(responseBuffer.getNextField());
      _Overrides = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _Allocation = responseBuffer.decodeBoolean(responseBuffer.getNextField());
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _TaxType = resizeArray( _TaxType, _RepeatCount );
      _TaxTypeDesc = resizeArray( _TaxTypeDesc, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _TaxType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TaxTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
