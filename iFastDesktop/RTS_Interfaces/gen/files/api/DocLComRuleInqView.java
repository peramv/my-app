
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Document List by Comply Rule Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/DocLComRuleInq.doc">DocLComRuleInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class DocLComRuleInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Document Code member array.
    */
   private String[] _DocCode = null;
   
   /**
    * Description member array.
    */
   private String[] _Description = null;
   
   /**
    * Tax Impact member array.
    */
   private String[] _TaxImpact = null;
   
   /**
    * Tax Jurisdiction member array.
    */
   private String[] _TaxJuris = null;
   
   /**
    * Tax Exempt Type member array.
    */
   private String[] _TaxExType = null;
   

   /**
    * Constructs the DocLComRuleInqView object.
    * 
    */
   public DocLComRuleInqView()
   {
      super ( new DocLComRuleInqRequest() );
   }

   /**
    * Constructs the DocLComRuleInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public DocLComRuleInqView( String hostEncoding )
   {
      super ( new DocLComRuleInqRequest( hostEncoding ) );
   }

   /**
    * Gets the DocLComRuleInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The DocLComRuleInqRequest object.
    */
   public final DocLComRuleInqRequest getRequest()
   {
      return (DocLComRuleInqRequest)getIFastRequest();
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
    * Gets the Document Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Document Code or null.
    */
   public final String getDocCode( int index )
   {
      return _DocCode[index];
   }
    
   /**
    * Gets the Document Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Document Code or the specified default value.
    */
   public final String getDocCode( int index, String defaultValue )
   {
      return _DocCode[index] == null ? defaultValue : _DocCode[index];
   }
    
   /**
    * Gets the array of Document Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Document Code values.
    */
   public final String[] getDocCodeArray()
   {
      return _DocCode;
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
    * Gets the Tax Impact field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax Impact or null.
    */
   public final String getTaxImpact( int index )
   {
      return _TaxImpact[index];
   }
    
   /**
    * Gets the Tax Impact field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Impact or the specified default value.
    */
   public final String getTaxImpact( int index, String defaultValue )
   {
      return _TaxImpact[index] == null ? defaultValue : _TaxImpact[index];
   }
    
   /**
    * Gets the array of Tax Impact fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax Impact values.
    */
   public final String[] getTaxImpactArray()
   {
      return _TaxImpact;
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
    * Gets the Tax Exempt Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax Exempt Type or null.
    */
   public final String getTaxExType( int index )
   {
      return _TaxExType[index];
   }
    
   /**
    * Gets the Tax Exempt Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Exempt Type or the specified default value.
    */
   public final String getTaxExType( int index, String defaultValue )
   {
      return _TaxExType[index] == null ? defaultValue : _TaxExType[index];
   }
    
   /**
    * Gets the array of Tax Exempt Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax Exempt Type values.
    */
   public final String[] getTaxExTypeArray()
   {
      return _TaxExType;
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
      
      _DocCode = resizeArray( _DocCode, _RepeatCount );
      _Description = resizeArray( _Description, _RepeatCount );
      _TaxImpact = resizeArray( _TaxImpact, _RepeatCount );
      _TaxJuris = resizeArray( _TaxJuris, _RepeatCount );
      _TaxExType = resizeArray( _TaxExType, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _DocCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Description[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TaxImpact[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TaxJuris[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TaxExType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
