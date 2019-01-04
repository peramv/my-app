
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Recipient Info view.
 * For additional view information see <A HREF="../../../../viewspecs/RecipientInfolnq.doc">RecipientInfolnq.doc</A>.
 * 
 * @author RTS Generated
 */
public class RecipientInfolnqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Tax Type member array.
    */
   private String[] _TaxType = null;
   
   /**
    * Account Type member array.
    */
   private String[] _AccountType = null;
   
   /**
    * Recipient Type member array.
    */
   private String[] _RecipientType = null;
   
   /**
    * Tax Jurisdiction member array.
    */
   private String[] _TaxJuris = null;
   

   /**
    * Constructs the RecipientInfolnqView object.
    * 
    */
   public RecipientInfolnqView()
   {
      super ( new RecipientInfolnqRequest() );
   }

   /**
    * Constructs the RecipientInfolnqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public RecipientInfolnqView( String hostEncoding )
   {
      super ( new RecipientInfolnqRequest( hostEncoding ) );
   }

   /**
    * Gets the RecipientInfolnqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The RecipientInfolnqRequest object.
    */
   public final RecipientInfolnqRequest getRequest()
   {
      return (RecipientInfolnqRequest)getIFastRequest();
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
    * Gets the Account Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Type or null.
    */
   public final String getAccountType( int index )
   {
      return _AccountType[index];
   }
    
   /**
    * Gets the Account Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Type or the specified default value.
    */
   public final String getAccountType( int index, String defaultValue )
   {
      return _AccountType[index] == null ? defaultValue : _AccountType[index];
   }
    
   /**
    * Gets the array of Account Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Type values.
    */
   public final String[] getAccountTypeArray()
   {
      return _AccountType;
   }
    
   /**
    * Gets the Recipient Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Recipient Type or null.
    */
   public final String getRecipientType( int index )
   {
      return _RecipientType[index];
   }
    
   /**
    * Gets the Recipient Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Recipient Type or the specified default value.
    */
   public final String getRecipientType( int index, String defaultValue )
   {
      return _RecipientType[index] == null ? defaultValue : _RecipientType[index];
   }
    
   /**
    * Gets the array of Recipient Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Recipient Type values.
    */
   public final String[] getRecipientTypeArray()
   {
      return _RecipientType;
   }
    
   /**
    * Gets the Tax Jurisdiction field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax Jurisdiction or null.
    */
   public final String getTaxJuris( int index )
   {
      return _TaxJuris[index];
   }
    
   /**
    * Gets the Tax Jurisdiction field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Jurisdiction or the specified default value.
    */
   public final String getTaxJuris( int index, String defaultValue )
   {
      return _TaxJuris[index] == null ? defaultValue : _TaxJuris[index];
   }
    
   /**
    * Gets the array of Tax Jurisdiction fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax Jurisdiction values.
    */
   public final String[] getTaxJurisArray()
   {
      return _TaxJuris;
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
      
      _TaxType = resizeArray( _TaxType, _RepeatCount );
      _AccountType = resizeArray( _AccountType, _RepeatCount );
      _RecipientType = resizeArray( _RecipientType, _RepeatCount );
      _TaxJuris = resizeArray( _TaxJuris, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _TaxType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AccountType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RecipientType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TaxJuris[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
