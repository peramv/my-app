
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Products List Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/ProdLstInq.doc">ProdLstInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class ProdLstInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Product Control Code member array.
    */
   private String[] _ProductCtrlCode = null;
   
   /**
    * Active Code member array.
    */
   private String[] _ActiveCode = null;
   

   /**
    * Constructs the ProdLstInqView object.
    * 
    */
   public ProdLstInqView()
   {
      super ( new ProdLstInqRequest() );
   }

   /**
    * Constructs the ProdLstInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public ProdLstInqView( String hostEncoding )
   {
      super ( new ProdLstInqRequest( hostEncoding ) );
   }

   /**
    * Gets the ProdLstInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The ProdLstInqRequest object.
    */
   public final ProdLstInqRequest getRequest()
   {
      return (ProdLstInqRequest)getIFastRequest();
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
    * Gets the Product Control Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Product Control Code or null.
    */
   public final String getProductCtrlCode( int index )
   {
      return _ProductCtrlCode[index];
   }
    
   /**
    * Gets the Product Control Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Product Control Code or the specified default value.
    */
   public final String getProductCtrlCode( int index, String defaultValue )
   {
      return _ProductCtrlCode[index] == null ? defaultValue : _ProductCtrlCode[index];
   }
    
   /**
    * Gets the array of Product Control Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Product Control Code values.
    */
   public final String[] getProductCtrlCodeArray()
   {
      return _ProductCtrlCode;
   }
    
   /**
    * Gets the Active Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Active Code or null.
    */
   public final String getActiveCode( int index )
   {
      return _ActiveCode[index];
   }
    
   /**
    * Gets the Active Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Active Code or the specified default value.
    */
   public final String getActiveCode( int index, String defaultValue )
   {
      return _ActiveCode[index] == null ? defaultValue : _ActiveCode[index];
   }
    
   /**
    * Gets the array of Active Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Active Code values.
    */
   public final String[] getActiveCodeArray()
   {
      return _ActiveCode;
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
      
      _ProductCtrlCode = resizeArray( _ProductCtrlCode, _RepeatCount );
      _ActiveCode = resizeArray( _ActiveCode, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _ProductCtrlCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ActiveCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
