
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Delivery Options per Document Type List view.
 * For additional view information see <A HREF="../../../../viewspecs/DelivOptPerDocLst.doc">DelivOptPerDocLst.doc</A>.
 * 
 * @author RTS Generated
 */
public class DelivOptPerDocLstView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Document Type member array.
    */
   private String[] _DocumentType = null;
   
   /**
    * Delivery List member array.
    */
   private String[] _DeliveryList = null;
   

   /**
    * Constructs the DelivOptPerDocLstView object.
    * 
    */
   public DelivOptPerDocLstView()
   {
      super ( new DelivOptPerDocLstRequest() );
   }

   /**
    * Constructs the DelivOptPerDocLstView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public DelivOptPerDocLstView( String hostEncoding )
   {
      super ( new DelivOptPerDocLstRequest( hostEncoding ) );
   }

   /**
    * Gets the DelivOptPerDocLstRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The DelivOptPerDocLstRequest object.
    */
   public final DelivOptPerDocLstRequest getRequest()
   {
      return (DelivOptPerDocLstRequest)getIFastRequest();
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
    * Gets the Document Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Document Type or null.
    */
   public final String getDocumentType( int index )
   {
      return _DocumentType[index];
   }
    
   /**
    * Gets the Document Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Document Type or the specified default value.
    */
   public final String getDocumentType( int index, String defaultValue )
   {
      return _DocumentType[index] == null ? defaultValue : _DocumentType[index];
   }
    
   /**
    * Gets the array of Document Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Document Type values.
    */
   public final String[] getDocumentTypeArray()
   {
      return _DocumentType;
   }
    
   /**
    * Gets the Delivery List field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Delivery List or null.
    */
   public final String getDeliveryList( int index )
   {
      return _DeliveryList[index];
   }
    
   /**
    * Gets the Delivery List field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Delivery List or the specified default value.
    */
   public final String getDeliveryList( int index, String defaultValue )
   {
      return _DeliveryList[index] == null ? defaultValue : _DeliveryList[index];
   }
    
   /**
    * Gets the array of Delivery List fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Delivery List values.
    */
   public final String[] getDeliveryListArray()
   {
      return _DeliveryList;
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
      
      _DocumentType = resizeArray( _DocumentType, _RepeatCount );
      _DeliveryList = resizeArray( _DeliveryList, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _DocumentType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DeliveryList[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
