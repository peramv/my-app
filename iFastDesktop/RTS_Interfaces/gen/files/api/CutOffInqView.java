
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Account Level Cut Off Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/CutOffInq.doc">CutOffInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class CutOffInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Fund Group member array.
    */
   private String[] _FundGroup = null;
   
   /**
    * Cut Off Time Type member array.
    */
   private String[] _CutOffTimeType = null;
   
   /**
    * Cut Off Time member array.
    */
   private String[] _CutOffTime = null;
   
   /**
    * Process Date member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * Mod Date member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * User Name member array.
    */
   private String[] _UserName = null;
   
   /**
    * Mod User member array.
    */
   private String[] _ModUser = null;
   
   /**
    * Cut Off recid member array.
    */
   private Integer[] _CutOffRid = null;
   
   /**
    * Cut Off Version member array.
    */
   private Integer[] _CutOffVersion = null;
   
   /**
    * Cut Off Time ID member array.
    */
   private Integer[] _CutOffTimeID = null;
   
   /**
    * Cut Off Time Zone member array.
    */
   private String[] _CutOffTimeZone = null;
   
   /**
    * Trade Lead Days member array.
    */
   private Integer[] _TradeLeadDays = null;
   
   /**
    * Fund Code member array.
    */
   private String[] _FundCode = null;
   
   /**
    * Class Code member array.
    */
   private String[] _ClassCode = null;
   

   /**
    * Constructs the CutOffInqView object.
    * 
    */
   public CutOffInqView()
   {
      super ( new CutOffInqRequest() );
   }

   /**
    * Constructs the CutOffInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public CutOffInqView( String hostEncoding )
   {
      super ( new CutOffInqRequest( hostEncoding ) );
   }

   /**
    * Gets the CutOffInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The CutOffInqRequest object.
    */
   public final CutOffInqRequest getRequest()
   {
      return (CutOffInqRequest)getIFastRequest();
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
    * Gets the Fund Group field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Group or null.
    */
   public final String getFundGroup( int index )
   {
      return _FundGroup[index];
   }
    
   /**
    * Gets the Fund Group field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Group or the specified default value.
    */
   public final String getFundGroup( int index, String defaultValue )
   {
      return _FundGroup[index] == null ? defaultValue : _FundGroup[index];
   }
    
   /**
    * Gets the array of Fund Group fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Group values.
    */
   public final String[] getFundGroupArray()
   {
      return _FundGroup;
   }
    
   /**
    * Gets the Cut Off Time Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Cut Off Time Type or null.
    */
   public final String getCutOffTimeType( int index )
   {
      return _CutOffTimeType[index];
   }
    
   /**
    * Gets the Cut Off Time Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Cut Off Time Type or the specified default value.
    */
   public final String getCutOffTimeType( int index, String defaultValue )
   {
      return _CutOffTimeType[index] == null ? defaultValue : _CutOffTimeType[index];
   }
    
   /**
    * Gets the array of Cut Off Time Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Cut Off Time Type values.
    */
   public final String[] getCutOffTimeTypeArray()
   {
      return _CutOffTimeType;
   }
    
   /**
    * Gets the Cut Off Time field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Cut Off Time or null.
    */
   public final String getCutOffTime( int index )
   {
      return _CutOffTime[index];
   }
    
   /**
    * Gets the Cut Off Time field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Cut Off Time or the specified default value.
    */
   public final String getCutOffTime( int index, String defaultValue )
   {
      return _CutOffTime[index] == null ? defaultValue : _CutOffTime[index];
   }
    
   /**
    * Gets the array of Cut Off Time fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Cut Off Time values.
    */
   public final String[] getCutOffTimeArray()
   {
      return _CutOffTime;
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
    * Gets the Cut Off recid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Cut Off recid or null.
    */
   public final Integer getCutOffRid( int index )
   {
      return _CutOffRid[index];
   }
    
   /**
    * Gets the Cut Off recid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Cut Off recid or the specified default value.
    */
   public final int getCutOffRid( int index, int defaultValue )
   {
      return _CutOffRid[index] == null ? defaultValue : _CutOffRid[index].intValue();
   }
    
   /**
    * Gets the array of Cut Off recid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Cut Off recid values.
    */
   public final Integer[] getCutOffRidArray()
   {
      return _CutOffRid;
   }
    
   /**
    * Gets the Cut Off Version field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Cut Off Version or null.
    */
   public final Integer getCutOffVersion( int index )
   {
      return _CutOffVersion[index];
   }
    
   /**
    * Gets the Cut Off Version field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Cut Off Version or the specified default value.
    */
   public final int getCutOffVersion( int index, int defaultValue )
   {
      return _CutOffVersion[index] == null ? defaultValue : _CutOffVersion[index].intValue();
   }
    
   /**
    * Gets the array of Cut Off Version fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Cut Off Version values.
    */
   public final Integer[] getCutOffVersionArray()
   {
      return _CutOffVersion;
   }
    
   /**
    * Gets the Cut Off Time ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Cut Off Time ID or null.
    */
   public final Integer getCutOffTimeID( int index )
   {
      return _CutOffTimeID[index];
   }
    
   /**
    * Gets the Cut Off Time ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Cut Off Time ID or the specified default value.
    */
   public final int getCutOffTimeID( int index, int defaultValue )
   {
      return _CutOffTimeID[index] == null ? defaultValue : _CutOffTimeID[index].intValue();
   }
    
   /**
    * Gets the array of Cut Off Time ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Cut Off Time ID values.
    */
   public final Integer[] getCutOffTimeIDArray()
   {
      return _CutOffTimeID;
   }
    
   /**
    * Gets the Cut Off Time Zone field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Cut Off Time Zone or null.
    */
   public final String getCutOffTimeZone( int index )
   {
      return _CutOffTimeZone[index];
   }
    
   /**
    * Gets the Cut Off Time Zone field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Cut Off Time Zone or the specified default value.
    */
   public final String getCutOffTimeZone( int index, String defaultValue )
   {
      return _CutOffTimeZone[index] == null ? defaultValue : _CutOffTimeZone[index];
   }
    
   /**
    * Gets the array of Cut Off Time Zone fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Cut Off Time Zone values.
    */
   public final String[] getCutOffTimeZoneArray()
   {
      return _CutOffTimeZone;
   }
    
   /**
    * Gets the Trade Lead Days field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Trade Lead Days or null.
    */
   public final Integer getTradeLeadDays( int index )
   {
      return _TradeLeadDays[index];
   }
    
   /**
    * Gets the Trade Lead Days field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Trade Lead Days or the specified default value.
    */
   public final int getTradeLeadDays( int index, int defaultValue )
   {
      return _TradeLeadDays[index] == null ? defaultValue : _TradeLeadDays[index].intValue();
   }
    
   /**
    * Gets the array of Trade Lead Days fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Trade Lead Days values.
    */
   public final Integer[] getTradeLeadDaysArray()
   {
      return _TradeLeadDays;
   }
    
   /**
    * Gets the Fund Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Code or null.
    */
   public final String getFundCode( int index )
   {
      return _FundCode[index];
   }
    
   /**
    * Gets the Fund Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Code or the specified default value.
    */
   public final String getFundCode( int index, String defaultValue )
   {
      return _FundCode[index] == null ? defaultValue : _FundCode[index];
   }
    
   /**
    * Gets the array of Fund Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Code values.
    */
   public final String[] getFundCodeArray()
   {
      return _FundCode;
   }
    
   /**
    * Gets the Class Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Class Code or null.
    */
   public final String getClassCode( int index )
   {
      return _ClassCode[index];
   }
    
   /**
    * Gets the Class Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class Code or the specified default value.
    */
   public final String getClassCode( int index, String defaultValue )
   {
      return _ClassCode[index] == null ? defaultValue : _ClassCode[index];
   }
    
   /**
    * Gets the array of Class Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Class Code values.
    */
   public final String[] getClassCodeArray()
   {
      return _ClassCode;
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
      
      _FundGroup = resizeArray( _FundGroup, _RepeatCount );
      _CutOffTimeType = resizeArray( _CutOffTimeType, _RepeatCount );
      _CutOffTime = resizeArray( _CutOffTime, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _UserName = resizeArray( _UserName, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _CutOffRid = resizeArray( _CutOffRid, _RepeatCount );
      _CutOffVersion = resizeArray( _CutOffVersion, _RepeatCount );
      _CutOffTimeID = resizeArray( _CutOffTimeID, _RepeatCount );
      _CutOffTimeZone = resizeArray( _CutOffTimeZone, _RepeatCount );
      _TradeLeadDays = resizeArray( _TradeLeadDays, _RepeatCount );
      _FundCode = resizeArray( _FundCode, _RepeatCount );
      _ClassCode = resizeArray( _ClassCode, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _FundGroup[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CutOffTimeType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CutOffTime[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _UserName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CutOffRid[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _CutOffVersion[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _CutOffTimeID[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _CutOffTimeZone[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TradeLeadDays[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _FundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
