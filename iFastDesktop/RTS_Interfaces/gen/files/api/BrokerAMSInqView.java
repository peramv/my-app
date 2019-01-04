
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Broker AMS Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/BrokerAMSInq.doc">BrokerAMSInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class BrokerAMSInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Return AMSCode member array.
    */
   private String[] _rxAMSCode = null;
   
   /**
    * AMS Name member array.
    */
   private String[] _AMSName = null;
   
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = null;
   
   /**
    * Process Date member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * User Name member array.
    */
   private String[] _UserName = null;
   
   /**
    * Modify Date member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * Modify User member array.
    */
   private String[] _ModUser = null;
   
   /**
    * Broker AMS Version member array.
    */
   private Integer[] _BrokerAMSVer = null;
   
   /**
    * Broker AMS RId member array.
    */
   private Integer[] _BrokerAMSRId = null;
   
   /**
    * GoodBad Code member array.
    */
   private Boolean[] _GoodBad = null;
   

   /**
    * Constructs the BrokerAMSInqView object.
    * 
    */
   public BrokerAMSInqView()
   {
      super ( new BrokerAMSInqRequest() );
   }

   /**
    * Constructs the BrokerAMSInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public BrokerAMSInqView( String hostEncoding )
   {
      super ( new BrokerAMSInqRequest( hostEncoding ) );
   }

   /**
    * Gets the BrokerAMSInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The BrokerAMSInqRequest object.
    */
   public final BrokerAMSInqRequest getRequest()
   {
      return (BrokerAMSInqRequest)getIFastRequest();
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
    * Gets the Return AMSCode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Return AMSCode or null.
    */
   public final String getrxAMSCode( int index )
   {
      return _rxAMSCode[index];
   }
    
   /**
    * Gets the Return AMSCode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Return AMSCode or the specified default value.
    */
   public final String getrxAMSCode( int index, String defaultValue )
   {
      return _rxAMSCode[index] == null ? defaultValue : _rxAMSCode[index];
   }
    
   /**
    * Gets the array of Return AMSCode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Return AMSCode values.
    */
   public final String[] getrxAMSCodeArray()
   {
      return _rxAMSCode;
   }
    
   /**
    * Gets the AMS Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AMS Name or null.
    */
   public final String getAMSName( int index )
   {
      return _AMSName[index];
   }
    
   /**
    * Gets the AMS Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AMS Name or the specified default value.
    */
   public final String getAMSName( int index, String defaultValue )
   {
      return _AMSName[index] == null ? defaultValue : _AMSName[index];
   }
    
   /**
    * Gets the array of AMS Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AMS Name values.
    */
   public final String[] getAMSNameArray()
   {
      return _AMSName;
   }
    
   /**
    * Gets the Effective Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Effective Date or null.
    */
   public final Date getEffectiveDate( int index )
   {
      return _EffectiveDate[index];
   }
    
   /**
    * Gets the Effective Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Effective Date or the specified default value.
    */
   public final Date getEffectiveDate( int index, Date defaultValue )
   {
      return _EffectiveDate[index] == null ? defaultValue : _EffectiveDate[index];
   }
    
   /**
    * Gets the array of Effective Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Effective Date values.
    */
   public final Date[] getEffectiveDateArray()
   {
      return _EffectiveDate;
   }
    
   /**
    * Gets the Process Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Process Date or null.
    */
   public final Date getProcessDate( int index )
   {
      return _ProcessDate[index];
   }
    
   /**
    * Gets the Process Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Process Date or the specified default value.
    */
   public final Date getProcessDate( int index, Date defaultValue )
   {
      return _ProcessDate[index] == null ? defaultValue : _ProcessDate[index];
   }
    
   /**
    * Gets the array of Process Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Process Date values.
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
    * Gets the Modify Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Modify Date or null.
    */
   public final Date getModDate( int index )
   {
      return _ModDate[index];
   }
    
   /**
    * Gets the Modify Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Modify Date or the specified default value.
    */
   public final Date getModDate( int index, Date defaultValue )
   {
      return _ModDate[index] == null ? defaultValue : _ModDate[index];
   }
    
   /**
    * Gets the array of Modify Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Modify Date values.
    */
   public final Date[] getModDateArray()
   {
      return _ModDate;
   }
    
   /**
    * Gets the Modify User field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Modify User or null.
    */
   public final String getModUser( int index )
   {
      return _ModUser[index];
   }
    
   /**
    * Gets the Modify User field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Modify User or the specified default value.
    */
   public final String getModUser( int index, String defaultValue )
   {
      return _ModUser[index] == null ? defaultValue : _ModUser[index];
   }
    
   /**
    * Gets the array of Modify User fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Modify User values.
    */
   public final String[] getModUserArray()
   {
      return _ModUser;
   }
    
   /**
    * Gets the Broker AMS Version field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Broker AMS Version or null.
    */
   public final Integer getBrokerAMSVer( int index )
   {
      return _BrokerAMSVer[index];
   }
    
   /**
    * Gets the Broker AMS Version field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker AMS Version or the specified default value.
    */
   public final int getBrokerAMSVer( int index, int defaultValue )
   {
      return _BrokerAMSVer[index] == null ? defaultValue : _BrokerAMSVer[index].intValue();
   }
    
   /**
    * Gets the array of Broker AMS Version fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Broker AMS Version values.
    */
   public final Integer[] getBrokerAMSVerArray()
   {
      return _BrokerAMSVer;
   }
    
   /**
    * Gets the Broker AMS RId field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Broker AMS RId or null.
    */
   public final Integer getBrokerAMSRId( int index )
   {
      return _BrokerAMSRId[index];
   }
    
   /**
    * Gets the Broker AMS RId field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker AMS RId or the specified default value.
    */
   public final int getBrokerAMSRId( int index, int defaultValue )
   {
      return _BrokerAMSRId[index] == null ? defaultValue : _BrokerAMSRId[index].intValue();
   }
    
   /**
    * Gets the array of Broker AMS RId fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Broker AMS RId values.
    */
   public final Integer[] getBrokerAMSRIdArray()
   {
      return _BrokerAMSRId;
   }
    
   /**
    * Gets the GoodBad Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the GoodBad Code or null.
    */
   public final Boolean getGoodBad( int index )
   {
      return _GoodBad[index];
   }
    
   /**
    * Gets the GoodBad Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the GoodBad Code or the specified default value.
    */
   public final boolean getGoodBad( int index, boolean defaultValue )
   {
      return _GoodBad[index] == null ? defaultValue : _GoodBad[index].booleanValue();
   }
    
   /**
    * Gets the array of GoodBad Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of GoodBad Code values.
    */
   public final Boolean[] getGoodBadArray()
   {
      return _GoodBad;
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
      
      _rxAMSCode = resizeArray( _rxAMSCode, _RepeatCount );
      _AMSName = resizeArray( _AMSName, _RepeatCount );
      _EffectiveDate = resizeArray( _EffectiveDate, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _UserName = resizeArray( _UserName, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _BrokerAMSVer = resizeArray( _BrokerAMSVer, _RepeatCount );
      _BrokerAMSRId = resizeArray( _BrokerAMSRId, _RepeatCount );
      _GoodBad = resizeArray( _GoodBad, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxAMSCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AMSName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _UserName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BrokerAMSVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _BrokerAMSRId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _GoodBad[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      }
      

   }

}
      
