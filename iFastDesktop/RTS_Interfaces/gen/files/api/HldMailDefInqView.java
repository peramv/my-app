
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Hold-Mail Defaults view.
 * For additional view information see <A HREF="../../../../viewspecs/HldMailDefInq.doc">HldMailDefInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class HldMailDefInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Group Type member array.
    */
   private String[] _GroupType = null;
   
   /**
    * Fund Group member array.
    */
   private String[] _rxFundGroup = null;
   
   /**
    * Document Type member array.
    */
   private String[] _DocumentType = null;
   
   /**
    * Send mail information member array.
    */
   private Boolean[] _Hold = null;
   
   /**
    * Date Created member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * Who created the record member array.
    */
   private String[] _UserName = null;
   
   /**
    * Date Modified member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * Who modified member array.
    */
   private String[] _ModUser = null;
   
   /**
    * Delivery Option member array.
    */
   private String[] _DeliveryOption = null;
   

   /**
    * Constructs the HldMailDefInqView object.
    * 
    */
   public HldMailDefInqView()
   {
      super ( new HldMailDefInqRequest() );
   }

   /**
    * Constructs the HldMailDefInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public HldMailDefInqView( String hostEncoding )
   {
      super ( new HldMailDefInqRequest( hostEncoding ) );
   }

   /**
    * Gets the HldMailDefInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The HldMailDefInqRequest object.
    */
   public final HldMailDefInqRequest getRequest()
   {
      return (HldMailDefInqRequest)getIFastRequest();
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
    * Gets the Group Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Group Type or null.
    */
   public final String getGroupType( int index )
   {
      return _GroupType[index];
   }
    
   /**
    * Gets the Group Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Group Type or the specified default value.
    */
   public final String getGroupType( int index, String defaultValue )
   {
      return _GroupType[index] == null ? defaultValue : _GroupType[index];
   }
    
   /**
    * Gets the array of Group Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Group Type values.
    */
   public final String[] getGroupTypeArray()
   {
      return _GroupType;
   }
    
   /**
    * Gets the Fund Group field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Group or null.
    */
   public final String getrxFundGroup( int index )
   {
      return _rxFundGroup[index];
   }
    
   /**
    * Gets the Fund Group field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Group or the specified default value.
    */
   public final String getrxFundGroup( int index, String defaultValue )
   {
      return _rxFundGroup[index] == null ? defaultValue : _rxFundGroup[index];
   }
    
   /**
    * Gets the array of Fund Group fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Group values.
    */
   public final String[] getrxFundGroupArray()
   {
      return _rxFundGroup;
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
    * Gets the Send mail information field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Send mail information or null.
    */
   public final Boolean getHold( int index )
   {
      return _Hold[index];
   }
    
   /**
    * Gets the Send mail information field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Send mail information or the specified default value.
    */
   public final boolean getHold( int index, boolean defaultValue )
   {
      return _Hold[index] == null ? defaultValue : _Hold[index].booleanValue();
   }
    
   /**
    * Gets the array of Send mail information fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Send mail information values.
    */
   public final Boolean[] getHoldArray()
   {
      return _Hold;
   }
    
   /**
    * Gets the Date Created field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Date Created or null.
    */
   public final Date getProcessDate( int index )
   {
      return _ProcessDate[index];
   }
    
   /**
    * Gets the Date Created field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date Created or the specified default value.
    */
   public final Date getProcessDate( int index, Date defaultValue )
   {
      return _ProcessDate[index] == null ? defaultValue : _ProcessDate[index];
   }
    
   /**
    * Gets the array of Date Created fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Date Created values.
    */
   public final Date[] getProcessDateArray()
   {
      return _ProcessDate;
   }
    
   /**
    * Gets the Who created the record field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Who created the record or null.
    */
   public final String getUserName( int index )
   {
      return _UserName[index];
   }
    
   /**
    * Gets the Who created the record field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Who created the record or the specified default value.
    */
   public final String getUserName( int index, String defaultValue )
   {
      return _UserName[index] == null ? defaultValue : _UserName[index];
   }
    
   /**
    * Gets the array of Who created the record fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Who created the record values.
    */
   public final String[] getUserNameArray()
   {
      return _UserName;
   }
    
   /**
    * Gets the Date Modified field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Date Modified or null.
    */
   public final Date getModDate( int index )
   {
      return _ModDate[index];
   }
    
   /**
    * Gets the Date Modified field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date Modified or the specified default value.
    */
   public final Date getModDate( int index, Date defaultValue )
   {
      return _ModDate[index] == null ? defaultValue : _ModDate[index];
   }
    
   /**
    * Gets the array of Date Modified fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Date Modified values.
    */
   public final Date[] getModDateArray()
   {
      return _ModDate;
   }
    
   /**
    * Gets the Who modified field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Who modified or null.
    */
   public final String getModUser( int index )
   {
      return _ModUser[index];
   }
    
   /**
    * Gets the Who modified field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Who modified or the specified default value.
    */
   public final String getModUser( int index, String defaultValue )
   {
      return _ModUser[index] == null ? defaultValue : _ModUser[index];
   }
    
   /**
    * Gets the array of Who modified fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Who modified values.
    */
   public final String[] getModUserArray()
   {
      return _ModUser;
   }
    
   /**
    * Gets the Delivery Option field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Delivery Option or null.
    */
   public final String getDeliveryOption( int index )
   {
      return _DeliveryOption[index];
   }
    
   /**
    * Gets the Delivery Option field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Delivery Option or the specified default value.
    */
   public final String getDeliveryOption( int index, String defaultValue )
   {
      return _DeliveryOption[index] == null ? defaultValue : _DeliveryOption[index];
   }
    
   /**
    * Gets the array of Delivery Option fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Delivery Option values.
    */
   public final String[] getDeliveryOptionArray()
   {
      return _DeliveryOption;
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
      
      _GroupType = resizeArray( _GroupType, _RepeatCount );
      _rxFundGroup = resizeArray( _rxFundGroup, _RepeatCount );
      _DocumentType = resizeArray( _DocumentType, _RepeatCount );
      _Hold = resizeArray( _Hold, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _UserName = resizeArray( _UserName, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _DeliveryOption = resizeArray( _DeliveryOption, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _GroupType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxFundGroup[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DocumentType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Hold[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _UserName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DeliveryOption[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
