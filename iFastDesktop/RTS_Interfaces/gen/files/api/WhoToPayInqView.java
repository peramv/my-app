
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Broker Who-To-Pay Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/WhoToPayInq.doc">WhoToPayInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class WhoToPayInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * AgencyCode in response member array.
    */
   private String[] _rxBrokerCode = null;
   
   /**
    * Payment For member array.
    */
   private String[] _PaymentFor = null;
   
   /**
    * Pay Entity member array.
    */
   private String[] _PayEntity = null;
   
   /**
    * Date Processed member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * User Name member array.
    */
   private String[] _UserName = null;
   
   /**
    * Date Modified member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * Mod User member array.
    */
   private String[] _ModUser = null;
   
   /**
    * PayEntity ID member array.
    */
   private String[] _PayEntityID = null;
   
   /**
    * Flag that indicates if PayInstruction exist for PayEntity member array.
    */
   private Boolean[] _PayInstructExists = null;
   
   /**
    * Menagement company code member array.
    */
   private String[] _CompanyCode = null;
   
   /**
    * Effective Date member array.
    */
   private Date[] _Deff = null;
   
   /**
    * Stop Date member array.
    */
   private Date[] _StopDate = null;
   

   /**
    * Constructs the WhoToPayInqView object.
    * 
    */
   public WhoToPayInqView()
   {
      super ( new WhoToPayInqRequest() );
   }

   /**
    * Constructs the WhoToPayInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public WhoToPayInqView( String hostEncoding )
   {
      super ( new WhoToPayInqRequest( hostEncoding ) );
   }

   /**
    * Gets the WhoToPayInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The WhoToPayInqRequest object.
    */
   public final WhoToPayInqRequest getRequest()
   {
      return (WhoToPayInqRequest)getIFastRequest();
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
    * Gets the AgencyCode in response field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AgencyCode in response or null.
    */
   public final String getrxBrokerCode( int index )
   {
      return _rxBrokerCode[index];
   }
    
   /**
    * Gets the AgencyCode in response field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AgencyCode in response or the specified default value.
    */
   public final String getrxBrokerCode( int index, String defaultValue )
   {
      return _rxBrokerCode[index] == null ? defaultValue : _rxBrokerCode[index];
   }
    
   /**
    * Gets the array of AgencyCode in response fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AgencyCode in response values.
    */
   public final String[] getrxBrokerCodeArray()
   {
      return _rxBrokerCode;
   }
    
   /**
    * Gets the Payment For field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Payment For or null.
    */
   public final String getPaymentFor( int index )
   {
      return _PaymentFor[index];
   }
    
   /**
    * Gets the Payment For field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payment For or the specified default value.
    */
   public final String getPaymentFor( int index, String defaultValue )
   {
      return _PaymentFor[index] == null ? defaultValue : _PaymentFor[index];
   }
    
   /**
    * Gets the array of Payment For fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Payment For values.
    */
   public final String[] getPaymentForArray()
   {
      return _PaymentFor;
   }
    
   /**
    * Gets the Pay Entity field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Pay Entity or null.
    */
   public final String getPayEntity( int index )
   {
      return _PayEntity[index];
   }
    
   /**
    * Gets the Pay Entity field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pay Entity or the specified default value.
    */
   public final String getPayEntity( int index, String defaultValue )
   {
      return _PayEntity[index] == null ? defaultValue : _PayEntity[index];
   }
    
   /**
    * Gets the array of Pay Entity fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Pay Entity values.
    */
   public final String[] getPayEntityArray()
   {
      return _PayEntity;
   }
    
   /**
    * Gets the Date Processed field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Date Processed or null.
    */
   public final Date getProcessDate( int index )
   {
      return _ProcessDate[index];
   }
    
   /**
    * Gets the Date Processed field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date Processed or the specified default value.
    */
   public final Date getProcessDate( int index, Date defaultValue )
   {
      return _ProcessDate[index] == null ? defaultValue : _ProcessDate[index];
   }
    
   /**
    * Gets the array of Date Processed fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Date Processed values.
    */
   public final Date[] getProcessDateArray()
   {
      return _ProcessDate;
   }
    
   /**
    * Gets the User Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the User Name or null.
    */
   public final String getUserName( int index )
   {
      return _UserName[index];
   }
    
   /**
    * Gets the User Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the User Name or the specified default value.
    */
   public final String getUserName( int index, String defaultValue )
   {
      return _UserName[index] == null ? defaultValue : _UserName[index];
   }
    
   /**
    * Gets the array of User Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of User Name values.
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
    * Gets the Mod User field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Mod User or null.
    */
   public final String getModUser( int index )
   {
      return _ModUser[index];
   }
    
   /**
    * Gets the Mod User field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Mod User or the specified default value.
    */
   public final String getModUser( int index, String defaultValue )
   {
      return _ModUser[index] == null ? defaultValue : _ModUser[index];
   }
    
   /**
    * Gets the array of Mod User fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Mod User values.
    */
   public final String[] getModUserArray()
   {
      return _ModUser;
   }
    
   /**
    * Gets the PayEntity ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the PayEntity ID or null.
    */
   public final String getPayEntityID( int index )
   {
      return _PayEntityID[index];
   }
    
   /**
    * Gets the PayEntity ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PayEntity ID or the specified default value.
    */
   public final String getPayEntityID( int index, String defaultValue )
   {
      return _PayEntityID[index] == null ? defaultValue : _PayEntityID[index];
   }
    
   /**
    * Gets the array of PayEntity ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of PayEntity ID values.
    */
   public final String[] getPayEntityIDArray()
   {
      return _PayEntityID;
   }
    
   /**
    * Gets the Flag that indicates if PayInstruction exist for PayEntity field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag that indicates if PayInstruction exist for PayEntity or null.
    */
   public final Boolean getPayInstructExists( int index )
   {
      return _PayInstructExists[index];
   }
    
   /**
    * Gets the Flag that indicates if PayInstruction exist for PayEntity field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag that indicates if PayInstruction exist for PayEntity or the specified default value.
    */
   public final boolean getPayInstructExists( int index, boolean defaultValue )
   {
      return _PayInstructExists[index] == null ? defaultValue : _PayInstructExists[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag that indicates if PayInstruction exist for PayEntity fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag that indicates if PayInstruction exist for PayEntity values.
    */
   public final Boolean[] getPayInstructExistsArray()
   {
      return _PayInstructExists;
   }
    
   /**
    * Gets the Menagement company code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Menagement company code or null.
    */
   public final String getCompanyCode( int index )
   {
      return _CompanyCode[index];
   }
    
   /**
    * Gets the Menagement company code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Menagement company code or the specified default value.
    */
   public final String getCompanyCode( int index, String defaultValue )
   {
      return _CompanyCode[index] == null ? defaultValue : _CompanyCode[index];
   }
    
   /**
    * Gets the array of Menagement company code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Menagement company code values.
    */
   public final String[] getCompanyCodeArray()
   {
      return _CompanyCode;
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
    * Gets the Stop Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stop Date or null.
    */
   public final Date getStopDate( int index )
   {
      return _StopDate[index];
   }
    
   /**
    * Gets the Stop Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Date or the specified default value.
    */
   public final Date getStopDate( int index, Date defaultValue )
   {
      return _StopDate[index] == null ? defaultValue : _StopDate[index];
   }
    
   /**
    * Gets the array of Stop Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stop Date values.
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
      
      _rxBrokerCode = resizeArray( _rxBrokerCode, _RepeatCount );
      _PaymentFor = resizeArray( _PaymentFor, _RepeatCount );
      _PayEntity = resizeArray( _PayEntity, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _UserName = resizeArray( _UserName, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _PayEntityID = resizeArray( _PayEntityID, _RepeatCount );
      _PayInstructExists = resizeArray( _PayInstructExists, _RepeatCount );
      _CompanyCode = resizeArray( _CompanyCode, _RepeatCount );
      _Deff = resizeArray( _Deff, _RepeatCount );
      _StopDate = resizeArray( _StopDate, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxBrokerCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PaymentFor[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PayEntity[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _UserName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PayEntityID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PayInstructExists[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _CompanyCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Deff[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _StopDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
      }
      

   }

}
      
