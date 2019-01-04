
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Account Ownership Allocation Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/AcctOwnsAllocInq.doc">AcctOwnsAllocInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class AcctOwnsAllocInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Tax Jurisdiction member array.
    */
   private String[] _TaxJuris = null;
   
   /**
    * Comply Code member array.
    */
   private String[] _ComplyCode = null;
   
   /**
    * Effective Date member array.
    */
   private Date[] _Deff = null;
   
   /**
    * Ownership Percentage member array.
    */
   private String[] _OwnershipPrcnt = null;
   
   /**
    * Taxable Percentage member array.
    */
   private String[] _TaxablePrcnt = null;
   

   /**
    * Constructs the AcctOwnsAllocInqView object.
    * 
    */
   public AcctOwnsAllocInqView()
   {
      super ( new AcctOwnsAllocInqRequest() );
   }

   /**
    * Constructs the AcctOwnsAllocInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AcctOwnsAllocInqView( String hostEncoding )
   {
      super ( new AcctOwnsAllocInqRequest( hostEncoding ) );
   }

   /**
    * Gets the AcctOwnsAllocInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AcctOwnsAllocInqRequest object.
    */
   public final AcctOwnsAllocInqRequest getRequest()
   {
      return (AcctOwnsAllocInqRequest)getIFastRequest();
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
    * Gets the Comply Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Comply Code or null.
    */
   public final String getComplyCode( int index )
   {
      return _ComplyCode[index];
   }
    
   /**
    * Gets the Comply Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Comply Code or the specified default value.
    */
   public final String getComplyCode( int index, String defaultValue )
   {
      return _ComplyCode[index] == null ? defaultValue : _ComplyCode[index];
   }
    
   /**
    * Gets the array of Comply Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Comply Code values.
    */
   public final String[] getComplyCodeArray()
   {
      return _ComplyCode;
   }
    
   /**
    * Gets the Effective Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Effective Date or null.
    */
   public final Date getDeff( int index )
   {
      return _Deff[index];
   }
    
   /**
    * Gets the Effective Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Effective Date or the specified default value.
    */
   public final Date getDeff( int index, Date defaultValue )
   {
      return _Deff[index] == null ? defaultValue : _Deff[index];
   }
    
   /**
    * Gets the array of Effective Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Effective Date values.
    */
   public final Date[] getDeffArray()
   {
      return _Deff;
   }
    
   /**
    * Gets the Ownership Percentage field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Ownership Percentage or null.
    */
   public final String getOwnershipPrcnt( int index )
   {
      return _OwnershipPrcnt[index];
   }
    
   /**
    * Gets the Ownership Percentage field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Ownership Percentage or the specified default value.
    */
   public final String getOwnershipPrcnt( int index, String defaultValue )
   {
      return _OwnershipPrcnt[index] == null ? defaultValue : _OwnershipPrcnt[index];
   }
    
   /**
    * Gets the array of Ownership Percentage fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Ownership Percentage values.
    */
   public final String[] getOwnershipPrcntArray()
   {
      return _OwnershipPrcnt;
   }
    
   /**
    * Gets the Taxable Percentage field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Taxable Percentage or null.
    */
   public final String getTaxablePrcnt( int index )
   {
      return _TaxablePrcnt[index];
   }
    
   /**
    * Gets the Taxable Percentage field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Taxable Percentage or the specified default value.
    */
   public final String getTaxablePrcnt( int index, String defaultValue )
   {
      return _TaxablePrcnt[index] == null ? defaultValue : _TaxablePrcnt[index];
   }
    
   /**
    * Gets the array of Taxable Percentage fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Taxable Percentage values.
    */
   public final String[] getTaxablePrcntArray()
   {
      return _TaxablePrcnt;
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
      
      _TaxJuris = resizeArray( _TaxJuris, _RepeatCount );
      _ComplyCode = resizeArray( _ComplyCode, _RepeatCount );
      _Deff = resizeArray( _Deff, _RepeatCount );
      _OwnershipPrcnt = resizeArray( _OwnershipPrcnt, _RepeatCount );
      _TaxablePrcnt = resizeArray( _TaxablePrcnt, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _TaxJuris[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ComplyCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Deff[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _OwnershipPrcnt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TaxablePrcnt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
