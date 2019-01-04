
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Security Recon - Account Level Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/SecAcctInq.doc">SecAcctInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class SecAcctInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Settlement Location Code member array.
    */
   private String[] _rxSettlLocCode = null;
   
   /**
    * Settlement Location Description member array.
    */
   private String[] _AcctSettlLocDesc = null;
   
   /**
    * Default  Settlement Location for Account member array.
    */
   private Boolean[] _DefaultSettlLoc = null;
   
   /**
    * Process Date member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * User Name member array.
    */
   private String[] _UserName = null;
   
   /**
    * Mod Date member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * Mod User member array.
    */
   private String[] _ModUser = null;
   
   /**
    * Version member array.
    */
   private Integer[] _AcctSettlLocVersion = null;
   
   /**
    * AcctSettlLoc record id member array.
    */
   private Integer[] _AcctSettlLocRID = null;
   
   /**
    * Location Level member array.
    */
   private String[] _LocationLevel = null;
   

   /**
    * Constructs the SecAcctInqView object.
    * 
    */
   public SecAcctInqView()
   {
      super ( new SecAcctInqRequest() );
   }

   /**
    * Constructs the SecAcctInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public SecAcctInqView( String hostEncoding )
   {
      super ( new SecAcctInqRequest( hostEncoding ) );
   }

   /**
    * Gets the SecAcctInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The SecAcctInqRequest object.
    */
   public final SecAcctInqRequest getRequest()
   {
      return (SecAcctInqRequest)getIFastRequest();
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
    * Gets the Settlement Location Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Settlement Location Code or null.
    */
   public final String getrxSettlLocCode( int index )
   {
      return _rxSettlLocCode[index];
   }
    
   /**
    * Gets the Settlement Location Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settlement Location Code or the specified default value.
    */
   public final String getrxSettlLocCode( int index, String defaultValue )
   {
      return _rxSettlLocCode[index] == null ? defaultValue : _rxSettlLocCode[index];
   }
    
   /**
    * Gets the array of Settlement Location Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Settlement Location Code values.
    */
   public final String[] getrxSettlLocCodeArray()
   {
      return _rxSettlLocCode;
   }
    
   /**
    * Gets the Settlement Location Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Settlement Location Description or null.
    */
   public final String getAcctSettlLocDesc( int index )
   {
      return _AcctSettlLocDesc[index];
   }
    
   /**
    * Gets the Settlement Location Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settlement Location Description or the specified default value.
    */
   public final String getAcctSettlLocDesc( int index, String defaultValue )
   {
      return _AcctSettlLocDesc[index] == null ? defaultValue : _AcctSettlLocDesc[index];
   }
    
   /**
    * Gets the array of Settlement Location Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Settlement Location Description values.
    */
   public final String[] getAcctSettlLocDescArray()
   {
      return _AcctSettlLocDesc;
   }
    
   /**
    * Gets the Default  Settlement Location for Account field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Default  Settlement Location for Account or null.
    */
   public final Boolean getDefaultSettlLoc( int index )
   {
      return _DefaultSettlLoc[index];
   }
    
   /**
    * Gets the Default  Settlement Location for Account field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Default  Settlement Location for Account or the specified default value.
    */
   public final boolean getDefaultSettlLoc( int index, boolean defaultValue )
   {
      return _DefaultSettlLoc[index] == null ? defaultValue : _DefaultSettlLoc[index].booleanValue();
   }
    
   /**
    * Gets the array of Default  Settlement Location for Account fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Default  Settlement Location for Account values.
    */
   public final Boolean[] getDefaultSettlLocArray()
   {
      return _DefaultSettlLoc;
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
    * Gets the Mod Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Mod Date or null.
    */
   public final Date getModDate( int index )
   {
      return _ModDate[index];
   }
    
   /**
    * Gets the Mod Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Mod Date or the specified default value.
    */
   public final Date getModDate( int index, Date defaultValue )
   {
      return _ModDate[index] == null ? defaultValue : _ModDate[index];
   }
    
   /**
    * Gets the array of Mod Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Mod Date values.
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
    * Gets the Version field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Version or null.
    */
   public final Integer getAcctSettlLocVersion( int index )
   {
      return _AcctSettlLocVersion[index];
   }
    
   /**
    * Gets the Version field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Version or the specified default value.
    */
   public final int getAcctSettlLocVersion( int index, int defaultValue )
   {
      return _AcctSettlLocVersion[index] == null ? defaultValue : _AcctSettlLocVersion[index].intValue();
   }
    
   /**
    * Gets the array of Version fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Version values.
    */
   public final Integer[] getAcctSettlLocVersionArray()
   {
      return _AcctSettlLocVersion;
   }
    
   /**
    * Gets the AcctSettlLoc record id field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AcctSettlLoc record id or null.
    */
   public final Integer getAcctSettlLocRID( int index )
   {
      return _AcctSettlLocRID[index];
   }
    
   /**
    * Gets the AcctSettlLoc record id field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AcctSettlLoc record id or the specified default value.
    */
   public final int getAcctSettlLocRID( int index, int defaultValue )
   {
      return _AcctSettlLocRID[index] == null ? defaultValue : _AcctSettlLocRID[index].intValue();
   }
    
   /**
    * Gets the array of AcctSettlLoc record id fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AcctSettlLoc record id values.
    */
   public final Integer[] getAcctSettlLocRIDArray()
   {
      return _AcctSettlLocRID;
   }
    
   /**
    * Gets the Location Level field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Location Level or null.
    */
   public final String getLocationLevel( int index )
   {
      return _LocationLevel[index];
   }
    
   /**
    * Gets the Location Level field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Location Level or the specified default value.
    */
   public final String getLocationLevel( int index, String defaultValue )
   {
      return _LocationLevel[index] == null ? defaultValue : _LocationLevel[index];
   }
    
   /**
    * Gets the array of Location Level fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Location Level values.
    */
   public final String[] getLocationLevelArray()
   {
      return _LocationLevel;
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
      
      _rxSettlLocCode = resizeArray( _rxSettlLocCode, _RepeatCount );
      _AcctSettlLocDesc = resizeArray( _AcctSettlLocDesc, _RepeatCount );
      _DefaultSettlLoc = resizeArray( _DefaultSettlLoc, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _UserName = resizeArray( _UserName, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _AcctSettlLocVersion = resizeArray( _AcctSettlLocVersion, _RepeatCount );
      _AcctSettlLocRID = resizeArray( _AcctSettlLocRID, _RepeatCount );
      _LocationLevel = resizeArray( _LocationLevel, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxSettlLocCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctSettlLocDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DefaultSettlLoc[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _UserName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctSettlLocVersion[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _AcctSettlLocRID[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _LocationLevel[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
