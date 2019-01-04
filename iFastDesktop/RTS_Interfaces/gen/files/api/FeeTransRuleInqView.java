
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Fee Trans Rules Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/FeeTransRuleInq.doc">FeeTransRuleInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class FeeTransRuleInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Fee Code member array.
    */
   private Integer[] _FeeCode = null;
   
   /**
    * Transaction Type member array.
    */
   private String[] _TransType = null;
   
   /**
    * Redemption Code member array.
    */
   private String[] _RedCodeDecl = null;
   
   /**
    * Deposit Type member array.
    */
   private String[] _DepTypeDecl = null;
   
   /**
    * INDC Decl member array.
    */
   private String[] _INDCDecl = null;
   
   /**
    * Tax Jurisdiction Decl member array.
    */
   private String[] _TaxJurisDecl = null;
   
   /**
    * Override Allowed member array.
    */
   private Boolean[] _OverrideAllowed = null;
   

   /**
    * Constructs the FeeTransRuleInqView object.
    * 
    */
   public FeeTransRuleInqView()
   {
      super ( new FeeTransRuleInqRequest() );
   }

   /**
    * Constructs the FeeTransRuleInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public FeeTransRuleInqView( String hostEncoding )
   {
      super ( new FeeTransRuleInqRequest( hostEncoding ) );
   }

   /**
    * Gets the FeeTransRuleInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The FeeTransRuleInqRequest object.
    */
   public final FeeTransRuleInqRequest getRequest()
   {
      return (FeeTransRuleInqRequest)getIFastRequest();
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
    * Gets the Fee Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fee Code or null.
    */
   public final Integer getFeeCode( int index )
   {
      return _FeeCode[index];
   }
    
   /**
    * Gets the Fee Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee Code or the specified default value.
    */
   public final int getFeeCode( int index, int defaultValue )
   {
      return _FeeCode[index] == null ? defaultValue : _FeeCode[index].intValue();
   }
    
   /**
    * Gets the array of Fee Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee Code values.
    */
   public final Integer[] getFeeCodeArray()
   {
      return _FeeCode;
   }
    
   /**
    * Gets the Transaction Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transaction Type or null.
    */
   public final String getTransType( int index )
   {
      return _TransType[index];
   }
    
   /**
    * Gets the Transaction Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transaction Type or the specified default value.
    */
   public final String getTransType( int index, String defaultValue )
   {
      return _TransType[index] == null ? defaultValue : _TransType[index];
   }
    
   /**
    * Gets the array of Transaction Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transaction Type values.
    */
   public final String[] getTransTypeArray()
   {
      return _TransType;
   }
    
   /**
    * Gets the Redemption Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Redemption Code or null.
    */
   public final String getRedCodeDecl( int index )
   {
      return _RedCodeDecl[index];
   }
    
   /**
    * Gets the Redemption Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Redemption Code or the specified default value.
    */
   public final String getRedCodeDecl( int index, String defaultValue )
   {
      return _RedCodeDecl[index] == null ? defaultValue : _RedCodeDecl[index];
   }
    
   /**
    * Gets the array of Redemption Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Redemption Code values.
    */
   public final String[] getRedCodeDeclArray()
   {
      return _RedCodeDecl;
   }
    
   /**
    * Gets the Deposit Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Deposit Type or null.
    */
   public final String getDepTypeDecl( int index )
   {
      return _DepTypeDecl[index];
   }
    
   /**
    * Gets the Deposit Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Deposit Type or the specified default value.
    */
   public final String getDepTypeDecl( int index, String defaultValue )
   {
      return _DepTypeDecl[index] == null ? defaultValue : _DepTypeDecl[index];
   }
    
   /**
    * Gets the array of Deposit Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Deposit Type values.
    */
   public final String[] getDepTypeDeclArray()
   {
      return _DepTypeDecl;
   }
    
   /**
    * Gets the INDC Decl field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the INDC Decl or null.
    */
   public final String getINDCDecl( int index )
   {
      return _INDCDecl[index];
   }
    
   /**
    * Gets the INDC Decl field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the INDC Decl or the specified default value.
    */
   public final String getINDCDecl( int index, String defaultValue )
   {
      return _INDCDecl[index] == null ? defaultValue : _INDCDecl[index];
   }
    
   /**
    * Gets the array of INDC Decl fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of INDC Decl values.
    */
   public final String[] getINDCDeclArray()
   {
      return _INDCDecl;
   }
    
   /**
    * Gets the Tax Jurisdiction Decl field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax Jurisdiction Decl or null.
    */
   public final String getTaxJurisDecl( int index )
   {
      return _TaxJurisDecl[index];
   }
    
   /**
    * Gets the Tax Jurisdiction Decl field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Jurisdiction Decl or the specified default value.
    */
   public final String getTaxJurisDecl( int index, String defaultValue )
   {
      return _TaxJurisDecl[index] == null ? defaultValue : _TaxJurisDecl[index];
   }
    
   /**
    * Gets the array of Tax Jurisdiction Decl fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax Jurisdiction Decl values.
    */
   public final String[] getTaxJurisDeclArray()
   {
      return _TaxJurisDecl;
   }
    
   /**
    * Gets the Override Allowed field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Override Allowed or null.
    */
   public final Boolean getOverrideAllowed( int index )
   {
      return _OverrideAllowed[index];
   }
    
   /**
    * Gets the Override Allowed field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Override Allowed or the specified default value.
    */
   public final boolean getOverrideAllowed( int index, boolean defaultValue )
   {
      return _OverrideAllowed[index] == null ? defaultValue : _OverrideAllowed[index].booleanValue();
   }
    
   /**
    * Gets the array of Override Allowed fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Override Allowed values.
    */
   public final Boolean[] getOverrideAllowedArray()
   {
      return _OverrideAllowed;
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
      
      _FeeCode = resizeArray( _FeeCode, _RepeatCount );
      _TransType = resizeArray( _TransType, _RepeatCount );
      _RedCodeDecl = resizeArray( _RedCodeDecl, _RepeatCount );
      _DepTypeDecl = resizeArray( _DepTypeDecl, _RepeatCount );
      _INDCDecl = resizeArray( _INDCDecl, _RepeatCount );
      _TaxJurisDecl = resizeArray( _TaxJurisDecl, _RepeatCount );
      _OverrideAllowed = resizeArray( _OverrideAllowed, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _FeeCode[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _TransType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RedCodeDecl[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DepTypeDecl[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _INDCDecl[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TaxJurisDecl[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _OverrideAllowed[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      }
      

   }

}
      
