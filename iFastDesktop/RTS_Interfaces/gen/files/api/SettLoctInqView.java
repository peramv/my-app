
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Settlement Locations Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/SettLoctInq.doc">SettLoctInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class SettLoctInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Settlement Ccode member array.
    */
   private String[] _SettlLocCode = null;
   
   /**
    * Amount member array.
    */
   private String[] _Amount = null;
   
   /**
    * For Account member array.
    */
   private String[] _ForAccount = null;
   
   /**
    * TransClrSettle UUID member array.
    */
   private String[] _TransClrSettlUUID = null;
   
   /**
    * InFavourOf member array.
    */
   private String[] _InFavourOf = null;
   
   /**
    * DeliveryTo member array.
    */
   private String[] _DeliveryTo = null;
   

   /**
    * Constructs the SettLoctInqView object.
    * 
    */
   public SettLoctInqView()
   {
      super ( new SettLoctInqRequest() );
   }

   /**
    * Constructs the SettLoctInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public SettLoctInqView( String hostEncoding )
   {
      super ( new SettLoctInqRequest( hostEncoding ) );
   }

   /**
    * Gets the SettLoctInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The SettLoctInqRequest object.
    */
   public final SettLoctInqRequest getRequest()
   {
      return (SettLoctInqRequest)getIFastRequest();
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
    * Gets the Settlement Ccode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Settlement Ccode or null.
    */
   public final String getSettlLocCode( int index )
   {
      return _SettlLocCode[index];
   }
    
   /**
    * Gets the Settlement Ccode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settlement Ccode or the specified default value.
    */
   public final String getSettlLocCode( int index, String defaultValue )
   {
      return _SettlLocCode[index] == null ? defaultValue : _SettlLocCode[index];
   }
    
   /**
    * Gets the array of Settlement Ccode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Settlement Ccode values.
    */
   public final String[] getSettlLocCodeArray()
   {
      return _SettlLocCode;
   }
    
   /**
    * Gets the Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Amount or null.
    */
   public final String getAmount( int index )
   {
      return _Amount[index];
   }
    
   /**
    * Gets the Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Amount or the specified default value.
    */
   public final String getAmount( int index, String defaultValue )
   {
      return _Amount[index] == null ? defaultValue : _Amount[index];
   }
    
   /**
    * Gets the array of Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Amount values.
    */
   public final String[] getAmountArray()
   {
      return _Amount;
   }
    
   /**
    * Gets the For Account field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the For Account or null.
    */
   public final String getForAccount( int index )
   {
      return _ForAccount[index];
   }
    
   /**
    * Gets the For Account field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the For Account or the specified default value.
    */
   public final String getForAccount( int index, String defaultValue )
   {
      return _ForAccount[index] == null ? defaultValue : _ForAccount[index];
   }
    
   /**
    * Gets the array of For Account fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of For Account values.
    */
   public final String[] getForAccountArray()
   {
      return _ForAccount;
   }
    
   /**
    * Gets the TransClrSettle UUID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the TransClrSettle UUID or null.
    */
   public final String getTransClrSettlUUID( int index )
   {
      return _TransClrSettlUUID[index];
   }
    
   /**
    * Gets the TransClrSettle UUID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TransClrSettle UUID or the specified default value.
    */
   public final String getTransClrSettlUUID( int index, String defaultValue )
   {
      return _TransClrSettlUUID[index] == null ? defaultValue : _TransClrSettlUUID[index];
   }
    
   /**
    * Gets the array of TransClrSettle UUID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of TransClrSettle UUID values.
    */
   public final String[] getTransClrSettlUUIDArray()
   {
      return _TransClrSettlUUID;
   }
    
   /**
    * Gets the InFavourOf field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the InFavourOf or null.
    */
   public final String getInFavourOf( int index )
   {
      return _InFavourOf[index];
   }
    
   /**
    * Gets the InFavourOf field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the InFavourOf or the specified default value.
    */
   public final String getInFavourOf( int index, String defaultValue )
   {
      return _InFavourOf[index] == null ? defaultValue : _InFavourOf[index];
   }
    
   /**
    * Gets the array of InFavourOf fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of InFavourOf values.
    */
   public final String[] getInFavourOfArray()
   {
      return _InFavourOf;
   }
    
   /**
    * Gets the DeliveryTo field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the DeliveryTo or null.
    */
   public final String getDeliveryTo( int index )
   {
      return _DeliveryTo[index];
   }
    
   /**
    * Gets the DeliveryTo field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the DeliveryTo or the specified default value.
    */
   public final String getDeliveryTo( int index, String defaultValue )
   {
      return _DeliveryTo[index] == null ? defaultValue : _DeliveryTo[index];
   }
    
   /**
    * Gets the array of DeliveryTo fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of DeliveryTo values.
    */
   public final String[] getDeliveryToArray()
   {
      return _DeliveryTo;
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
      
      _SettlLocCode = resizeArray( _SettlLocCode, _RepeatCount );
      _Amount = resizeArray( _Amount, _RepeatCount );
      _ForAccount = resizeArray( _ForAccount, _RepeatCount );
      _TransClrSettlUUID = resizeArray( _TransClrSettlUUID, _RepeatCount );
      _InFavourOf = resizeArray( _InFavourOf, _RepeatCount );
      _DeliveryTo = resizeArray( _DeliveryTo, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _SettlLocCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Amount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ForAccount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TransClrSettlUUID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _InFavourOf[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DeliveryTo[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
