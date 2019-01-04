
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Product Group Code List Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/ProdCodeInq.doc">ProdCodeInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class ProdCodeInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Product Code member array.
    */
   private String[] _rxProdCode = null;
   
   /**
    * Product Code Description member array.
    */
   private String[] _ProdCodeDesc = null;
   
   /**
    * Product Code Effective Date member array.
    */
   private Date[] _EffectiveDate = null;
   
   /**
    * Tax types eligible for the product code member array.
    */
   private String[] _TaxTypeList = null;
   
   /**
    * Product code Stop Date member array.
    */
   private Date[] _StopDate = null;
   

   /**
    * Constructs the ProdCodeInqView object.
    * 
    */
   public ProdCodeInqView()
   {
      super ( new ProdCodeInqRequest() );
   }

   /**
    * Constructs the ProdCodeInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public ProdCodeInqView( String hostEncoding )
   {
      super ( new ProdCodeInqRequest( hostEncoding ) );
   }

   /**
    * Gets the ProdCodeInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The ProdCodeInqRequest object.
    */
   public final ProdCodeInqRequest getRequest()
   {
      return (ProdCodeInqRequest)getIFastRequest();
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
    * Gets the Product Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Product Code or null.
    */
   public final String getrxProdCode( int index )
   {
      return _rxProdCode[index];
   }
    
   /**
    * Gets the Product Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Product Code or the specified default value.
    */
   public final String getrxProdCode( int index, String defaultValue )
   {
      return _rxProdCode[index] == null ? defaultValue : _rxProdCode[index];
   }
    
   /**
    * Gets the array of Product Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Product Code values.
    */
   public final String[] getrxProdCodeArray()
   {
      return _rxProdCode;
   }
    
   /**
    * Gets the Product Code Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Product Code Description or null.
    */
   public final String getProdCodeDesc( int index )
   {
      return _ProdCodeDesc[index];
   }
    
   /**
    * Gets the Product Code Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Product Code Description or the specified default value.
    */
   public final String getProdCodeDesc( int index, String defaultValue )
   {
      return _ProdCodeDesc[index] == null ? defaultValue : _ProdCodeDesc[index];
   }
    
   /**
    * Gets the array of Product Code Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Product Code Description values.
    */
   public final String[] getProdCodeDescArray()
   {
      return _ProdCodeDesc;
   }
    
   /**
    * Gets the Product Code Effective Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Product Code Effective Date or null.
    */
   public final Date getEffectiveDate( int index )
   {
      return _EffectiveDate[index];
   }
    
   /**
    * Gets the Product Code Effective Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Product Code Effective Date or the specified default value.
    */
   public final Date getEffectiveDate( int index, Date defaultValue )
   {
      return _EffectiveDate[index] == null ? defaultValue : _EffectiveDate[index];
   }
    
   /**
    * Gets the array of Product Code Effective Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Product Code Effective Date values.
    */
   public final Date[] getEffectiveDateArray()
   {
      return _EffectiveDate;
   }
    
   /**
    * Gets the Tax types eligible for the product code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax types eligible for the product code or null.
    */
   public final String getTaxTypeList( int index )
   {
      return _TaxTypeList[index];
   }
    
   /**
    * Gets the Tax types eligible for the product code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax types eligible for the product code or the specified default value.
    */
   public final String getTaxTypeList( int index, String defaultValue )
   {
      return _TaxTypeList[index] == null ? defaultValue : _TaxTypeList[index];
   }
    
   /**
    * Gets the array of Tax types eligible for the product code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax types eligible for the product code values.
    */
   public final String[] getTaxTypeListArray()
   {
      return _TaxTypeList;
   }
    
   /**
    * Gets the Product code Stop Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Product code Stop Date or null.
    */
   public final Date getStopDate( int index )
   {
      return _StopDate[index];
   }
    
   /**
    * Gets the Product code Stop Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Product code Stop Date or the specified default value.
    */
   public final Date getStopDate( int index, Date defaultValue )
   {
      return _StopDate[index] == null ? defaultValue : _StopDate[index];
   }
    
   /**
    * Gets the array of Product code Stop Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Product code Stop Date values.
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
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _rxProdCode = resizeArray( _rxProdCode, _RepeatCount );
      _ProdCodeDesc = resizeArray( _ProdCodeDesc, _RepeatCount );
      _EffectiveDate = resizeArray( _EffectiveDate, _RepeatCount );
      _TaxTypeList = resizeArray( _TaxTypeList, _RepeatCount );
      _StopDate = resizeArray( _StopDate, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxProdCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProdCodeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _TaxTypeList[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _StopDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
      }
      

   }

}
      
