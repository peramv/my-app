
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Intermediary List view.
 * For additional view information see <A HREF="../../../../viewspecs/IntermediaryDetails.doc">IntermediaryDetails.doc</A>.
 * 
 * @author RTS Generated
 */
public class IntermediaryDetailsView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Intermediary Name member array.
    */
   private String[] _IntermName = null;
   
   /**
    * Intermediary Code member array.
    */
   private String[] _IntermCode = null;
   
   /**
    * Allow Wire Order member array.
    */
   private Boolean[] _AllowWire = null;
   
   /**
    * Allow Money Market Wire Orders member array.
    */
   private Boolean[] _MMWire = null;
   
   /**
    * Volume Settlement Method member array.
    */
   private String[] _VolSettleType = null;
   
   /**
    * Flag indicating if intermediary is eligible to settle SWP through FUNDServ member array.
    */
   private Boolean[] _SWPSettleESGElig = null;
   
   /**
    * Flag indicating if intermediary is eligible to settle Cash ID through FUNDServ member array.
    */
   private Boolean[] _CashIDSettleESGElig = null;
   
   /**
    * Non Financial Update member array.
    */
   private String[] _NFUpdate = null;
   
   /**
    * CSS Clearing and Settlement member array.
    */
   private String[] _IntrCssStatus = null;
   

   /**
    * Constructs the IntermediaryDetailsView object.
    * 
    */
   public IntermediaryDetailsView()
   {
      super ( new IntermediaryDetailsRequest() );
   }

   /**
    * Constructs the IntermediaryDetailsView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public IntermediaryDetailsView( String hostEncoding )
   {
      super ( new IntermediaryDetailsRequest( hostEncoding ) );
   }

   /**
    * Gets the IntermediaryDetailsRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The IntermediaryDetailsRequest object.
    */
   public final IntermediaryDetailsRequest getRequest()
   {
      return (IntermediaryDetailsRequest)getIFastRequest();
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
    * Gets the Intermediary Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Intermediary Name or null.
    */
   public final String getIntermName( int index )
   {
      return _IntermName[index];
   }
    
   /**
    * Gets the Intermediary Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Intermediary Name or the specified default value.
    */
   public final String getIntermName( int index, String defaultValue )
   {
      return _IntermName[index] == null ? defaultValue : _IntermName[index];
   }
    
   /**
    * Gets the array of Intermediary Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Intermediary Name values.
    */
   public final String[] getIntermNameArray()
   {
      return _IntermName;
   }
    
   /**
    * Gets the Intermediary Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Intermediary Code or null.
    */
   public final String getIntermCode( int index )
   {
      return _IntermCode[index];
   }
    
   /**
    * Gets the Intermediary Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Intermediary Code or the specified default value.
    */
   public final String getIntermCode( int index, String defaultValue )
   {
      return _IntermCode[index] == null ? defaultValue : _IntermCode[index];
   }
    
   /**
    * Gets the array of Intermediary Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Intermediary Code values.
    */
   public final String[] getIntermCodeArray()
   {
      return _IntermCode;
   }
    
   /**
    * Gets the Allow Wire Order field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Allow Wire Order or null.
    */
   public final Boolean getAllowWire( int index )
   {
      return _AllowWire[index];
   }
    
   /**
    * Gets the Allow Wire Order field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Allow Wire Order or the specified default value.
    */
   public final boolean getAllowWire( int index, boolean defaultValue )
   {
      return _AllowWire[index] == null ? defaultValue : _AllowWire[index].booleanValue();
   }
    
   /**
    * Gets the array of Allow Wire Order fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Allow Wire Order values.
    */
   public final Boolean[] getAllowWireArray()
   {
      return _AllowWire;
   }
    
   /**
    * Gets the Allow Money Market Wire Orders field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Allow Money Market Wire Orders or null.
    */
   public final Boolean getMMWire( int index )
   {
      return _MMWire[index];
   }
    
   /**
    * Gets the Allow Money Market Wire Orders field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Allow Money Market Wire Orders or the specified default value.
    */
   public final boolean getMMWire( int index, boolean defaultValue )
   {
      return _MMWire[index] == null ? defaultValue : _MMWire[index].booleanValue();
   }
    
   /**
    * Gets the array of Allow Money Market Wire Orders fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Allow Money Market Wire Orders values.
    */
   public final Boolean[] getMMWireArray()
   {
      return _MMWire;
   }
    
   /**
    * Gets the Volume Settlement Method field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Volume Settlement Method or null.
    */
   public final String getVolSettleType( int index )
   {
      return _VolSettleType[index];
   }
    
   /**
    * Gets the Volume Settlement Method field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Volume Settlement Method or the specified default value.
    */
   public final String getVolSettleType( int index, String defaultValue )
   {
      return _VolSettleType[index] == null ? defaultValue : _VolSettleType[index];
   }
    
   /**
    * Gets the array of Volume Settlement Method fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Volume Settlement Method values.
    */
   public final String[] getVolSettleTypeArray()
   {
      return _VolSettleType;
   }
    
   /**
    * Gets the Flag indicating if intermediary is eligible to settle SWP through FUNDServ field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicating if intermediary is eligible to settle SWP through FUNDServ or null.
    */
   public final Boolean getSWPSettleESGElig( int index )
   {
      return _SWPSettleESGElig[index];
   }
    
   /**
    * Gets the Flag indicating if intermediary is eligible to settle SWP through FUNDServ field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if intermediary is eligible to settle SWP through FUNDServ or the specified default value.
    */
   public final boolean getSWPSettleESGElig( int index, boolean defaultValue )
   {
      return _SWPSettleESGElig[index] == null ? defaultValue : _SWPSettleESGElig[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicating if intermediary is eligible to settle SWP through FUNDServ fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicating if intermediary is eligible to settle SWP through FUNDServ values.
    */
   public final Boolean[] getSWPSettleESGEligArray()
   {
      return _SWPSettleESGElig;
   }
    
   /**
    * Gets the Flag indicating if intermediary is eligible to settle Cash ID through FUNDServ field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicating if intermediary is eligible to settle Cash ID through FUNDServ or null.
    */
   public final Boolean getCashIDSettleESGElig( int index )
   {
      return _CashIDSettleESGElig[index];
   }
    
   /**
    * Gets the Flag indicating if intermediary is eligible to settle Cash ID through FUNDServ field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if intermediary is eligible to settle Cash ID through FUNDServ or the specified default value.
    */
   public final boolean getCashIDSettleESGElig( int index, boolean defaultValue )
   {
      return _CashIDSettleESGElig[index] == null ? defaultValue : _CashIDSettleESGElig[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicating if intermediary is eligible to settle Cash ID through FUNDServ fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicating if intermediary is eligible to settle Cash ID through FUNDServ values.
    */
   public final Boolean[] getCashIDSettleESGEligArray()
   {
      return _CashIDSettleESGElig;
   }
    
   /**
    * Gets the Non Financial Update field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Non Financial Update or null.
    */
   public final String getNFUpdate( int index )
   {
      return _NFUpdate[index];
   }
    
   /**
    * Gets the Non Financial Update field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Non Financial Update or the specified default value.
    */
   public final String getNFUpdate( int index, String defaultValue )
   {
      return _NFUpdate[index] == null ? defaultValue : _NFUpdate[index];
   }
    
   /**
    * Gets the array of Non Financial Update fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Non Financial Update values.
    */
   public final String[] getNFUpdateArray()
   {
      return _NFUpdate;
   }
    
   /**
    * Gets the CSS Clearing and Settlement field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the CSS Clearing and Settlement or null.
    */
   public final String getIntrCssStatus( int index )
   {
      return _IntrCssStatus[index];
   }
    
   /**
    * Gets the CSS Clearing and Settlement field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the CSS Clearing and Settlement or the specified default value.
    */
   public final String getIntrCssStatus( int index, String defaultValue )
   {
      return _IntrCssStatus[index] == null ? defaultValue : _IntrCssStatus[index];
   }
    
   /**
    * Gets the array of CSS Clearing and Settlement fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of CSS Clearing and Settlement values.
    */
   public final String[] getIntrCssStatusArray()
   {
      return _IntrCssStatus;
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
      
      _IntermName = resizeArray( _IntermName, _RepeatCount );
      _IntermCode = resizeArray( _IntermCode, _RepeatCount );
      _AllowWire = resizeArray( _AllowWire, _RepeatCount );
      _MMWire = resizeArray( _MMWire, _RepeatCount );
      _VolSettleType = resizeArray( _VolSettleType, _RepeatCount );
      _SWPSettleESGElig = resizeArray( _SWPSettleESGElig, _RepeatCount );
      _CashIDSettleESGElig = resizeArray( _CashIDSettleESGElig, _RepeatCount );
      _NFUpdate = resizeArray( _NFUpdate, _RepeatCount );
      _IntrCssStatus = resizeArray( _IntrCssStatus, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _IntermName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IntermCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AllowWire[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _MMWire[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _VolSettleType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SWPSettleESGElig[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _CashIDSettleESGElig[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _NFUpdate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IntrCssStatus[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
