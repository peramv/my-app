
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Transaction Link Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/TransLinkInq.doc">TransLinkInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class TransLinkInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * rxTransNumber member array.
    */
   private Integer[] _rxTransNumber = null;
   
   /**
    * Link Trans Number member array.
    */
   private Integer[] _LinkTransNumber = null;
   
   /**
    * Link Type member array.
    */
   private String[] _LinkType = null;
   

   /**
    * Constructs the TransLinkInqView object.
    * 
    */
   public TransLinkInqView()
   {
      super ( new TransLinkInqRequest() );
   }

   /**
    * Constructs the TransLinkInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public TransLinkInqView( String hostEncoding )
   {
      super ( new TransLinkInqRequest( hostEncoding ) );
   }

   /**
    * Gets the TransLinkInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The TransLinkInqRequest object.
    */
   public final TransLinkInqRequest getRequest()
   {
      return (TransLinkInqRequest)getIFastRequest();
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
    * Gets the rxTransNumber field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the rxTransNumber or null.
    */
   public final Integer getrxTransNumber( int index )
   {
      return _rxTransNumber[index];
   }
    
   /**
    * Gets the rxTransNumber field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the rxTransNumber or the specified default value.
    */
   public final int getrxTransNumber( int index, int defaultValue )
   {
      return _rxTransNumber[index] == null ? defaultValue : _rxTransNumber[index].intValue();
   }
    
   /**
    * Gets the array of rxTransNumber fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of rxTransNumber values.
    */
   public final Integer[] getrxTransNumberArray()
   {
      return _rxTransNumber;
   }
    
   /**
    * Gets the Link Trans Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Link Trans Number or null.
    */
   public final Integer getLinkTransNumber( int index )
   {
      return _LinkTransNumber[index];
   }
    
   /**
    * Gets the Link Trans Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Link Trans Number or the specified default value.
    */
   public final int getLinkTransNumber( int index, int defaultValue )
   {
      return _LinkTransNumber[index] == null ? defaultValue : _LinkTransNumber[index].intValue();
   }
    
   /**
    * Gets the array of Link Trans Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Link Trans Number values.
    */
   public final Integer[] getLinkTransNumberArray()
   {
      return _LinkTransNumber;
   }
    
   /**
    * Gets the Link Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Link Type or null.
    */
   public final String getLinkType( int index )
   {
      return _LinkType[index];
   }
    
   /**
    * Gets the Link Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Link Type or the specified default value.
    */
   public final String getLinkType( int index, String defaultValue )
   {
      return _LinkType[index] == null ? defaultValue : _LinkType[index];
   }
    
   /**
    * Gets the array of Link Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Link Type values.
    */
   public final String[] getLinkTypeArray()
   {
      return _LinkType;
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
      
      _rxTransNumber = resizeArray( _rxTransNumber, _RepeatCount );
      _LinkTransNumber = resizeArray( _LinkTransNumber, _RepeatCount );
      _LinkType = resizeArray( _LinkType, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxTransNumber[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _LinkTransNumber[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _LinkType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
