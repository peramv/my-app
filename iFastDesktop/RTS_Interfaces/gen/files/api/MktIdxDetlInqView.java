
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Market Index Details Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/MktIdxDetlInq.doc">MktIdxDetlInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class MktIdxDetlInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Market Index Detl Recid member array.
    */
   private Integer[] _MktIdxDetlRId = null;
   
   /**
    * Market Index Code member array.
    */
   private String[] _rxIndexCode = null;
   
   /**
    * Closing Value member array.
    */
   private String[] _ClosingValue = null;
   
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = null;
   
   /**
    * Good/ Bad  as yes/no member array.
    */
   private Boolean[] _GoodBad = null;
   
   /**
    * Version member array.
    */
   private Integer[] _Version = null;
   
   /**
    * Date Created member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * Created By member array.
    */
   private String[] _UserName = null;
   
   /**
    * Time Created member array.
    */
   private String[] _TimeStamp = null;
   
   /**
    * Date Modified member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * Modified By member array.
    */
   private String[] _ModUser = null;
   
   /**
    * % changed member array.
    */
   private String[] _PcntChange = null;
   
   /**
    * Hurdle Rate member array.
    */
   private String[] _HurdleRate = null;
   

   /**
    * Constructs the MktIdxDetlInqView object.
    * 
    */
   public MktIdxDetlInqView()
   {
      super ( new MktIdxDetlInqRequest() );
   }

   /**
    * Constructs the MktIdxDetlInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public MktIdxDetlInqView( String hostEncoding )
   {
      super ( new MktIdxDetlInqRequest( hostEncoding ) );
   }

   /**
    * Gets the MktIdxDetlInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The MktIdxDetlInqRequest object.
    */
   public final MktIdxDetlInqRequest getRequest()
   {
      return (MktIdxDetlInqRequest)getIFastRequest();
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
    * Gets the Market Index Detl Recid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Market Index Detl Recid or null.
    */
   public final Integer getMktIdxDetlRId( int index )
   {
      return _MktIdxDetlRId[index];
   }
    
   /**
    * Gets the Market Index Detl Recid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Market Index Detl Recid or the specified default value.
    */
   public final int getMktIdxDetlRId( int index, int defaultValue )
   {
      return _MktIdxDetlRId[index] == null ? defaultValue : _MktIdxDetlRId[index].intValue();
   }
    
   /**
    * Gets the array of Market Index Detl Recid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Market Index Detl Recid values.
    */
   public final Integer[] getMktIdxDetlRIdArray()
   {
      return _MktIdxDetlRId;
   }
    
   /**
    * Gets the Market Index Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Market Index Code or null.
    */
   public final String getrxIndexCode( int index )
   {
      return _rxIndexCode[index];
   }
    
   /**
    * Gets the Market Index Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Market Index Code or the specified default value.
    */
   public final String getrxIndexCode( int index, String defaultValue )
   {
      return _rxIndexCode[index] == null ? defaultValue : _rxIndexCode[index];
   }
    
   /**
    * Gets the array of Market Index Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Market Index Code values.
    */
   public final String[] getrxIndexCodeArray()
   {
      return _rxIndexCode;
   }
    
   /**
    * Gets the Closing Value field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Closing Value or null.
    */
   public final String getClosingValue( int index )
   {
      return _ClosingValue[index];
   }
    
   /**
    * Gets the Closing Value field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Closing Value or the specified default value.
    */
   public final String getClosingValue( int index, String defaultValue )
   {
      return _ClosingValue[index] == null ? defaultValue : _ClosingValue[index];
   }
    
   /**
    * Gets the array of Closing Value fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Closing Value values.
    */
   public final String[] getClosingValueArray()
   {
      return _ClosingValue;
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
    * Gets the Good/ Bad  as yes/no field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Good/ Bad  as yes/no or null.
    */
   public final Boolean getGoodBad( int index )
   {
      return _GoodBad[index];
   }
    
   /**
    * Gets the Good/ Bad  as yes/no field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Good/ Bad  as yes/no or the specified default value.
    */
   public final boolean getGoodBad( int index, boolean defaultValue )
   {
      return _GoodBad[index] == null ? defaultValue : _GoodBad[index].booleanValue();
   }
    
   /**
    * Gets the array of Good/ Bad  as yes/no fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Good/ Bad  as yes/no values.
    */
   public final Boolean[] getGoodBadArray()
   {
      return _GoodBad;
   }
    
   /**
    * Gets the Version field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Version or null.
    */
   public final Integer getVersion( int index )
   {
      return _Version[index];
   }
    
   /**
    * Gets the Version field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Version or the specified default value.
    */
   public final int getVersion( int index, int defaultValue )
   {
      return _Version[index] == null ? defaultValue : _Version[index].intValue();
   }
    
   /**
    * Gets the array of Version fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Version values.
    */
   public final Integer[] getVersionArray()
   {
      return _Version;
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
    * Gets the Created By field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Created By or null.
    */
   public final String getUserName( int index )
   {
      return _UserName[index];
   }
    
   /**
    * Gets the Created By field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Created By or the specified default value.
    */
   public final String getUserName( int index, String defaultValue )
   {
      return _UserName[index] == null ? defaultValue : _UserName[index];
   }
    
   /**
    * Gets the array of Created By fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Created By values.
    */
   public final String[] getUserNameArray()
   {
      return _UserName;
   }
    
   /**
    * Gets the Time Created field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Time Created or null.
    */
   public final String getTimeStamp( int index )
   {
      return _TimeStamp[index];
   }
    
   /**
    * Gets the Time Created field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Time Created or the specified default value.
    */
   public final String getTimeStamp( int index, String defaultValue )
   {
      return _TimeStamp[index] == null ? defaultValue : _TimeStamp[index];
   }
    
   /**
    * Gets the array of Time Created fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Time Created values.
    */
   public final String[] getTimeStampArray()
   {
      return _TimeStamp;
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
    * Gets the Modified By field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Modified By or null.
    */
   public final String getModUser( int index )
   {
      return _ModUser[index];
   }
    
   /**
    * Gets the Modified By field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Modified By or the specified default value.
    */
   public final String getModUser( int index, String defaultValue )
   {
      return _ModUser[index] == null ? defaultValue : _ModUser[index];
   }
    
   /**
    * Gets the array of Modified By fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Modified By values.
    */
   public final String[] getModUserArray()
   {
      return _ModUser;
   }
    
   /**
    * Gets the % changed field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the % changed or null.
    */
   public final String getPcntChange( int index )
   {
      return _PcntChange[index];
   }
    
   /**
    * Gets the % changed field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the % changed or the specified default value.
    */
   public final String getPcntChange( int index, String defaultValue )
   {
      return _PcntChange[index] == null ? defaultValue : _PcntChange[index];
   }
    
   /**
    * Gets the array of % changed fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of % changed values.
    */
   public final String[] getPcntChangeArray()
   {
      return _PcntChange;
   }
    
   /**
    * Gets the Hurdle Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Hurdle Rate or null.
    */
   public final String getHurdleRate( int index )
   {
      return _HurdleRate[index];
   }
    
   /**
    * Gets the Hurdle Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Hurdle Rate or the specified default value.
    */
   public final String getHurdleRate( int index, String defaultValue )
   {
      return _HurdleRate[index] == null ? defaultValue : _HurdleRate[index];
   }
    
   /**
    * Gets the array of Hurdle Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Hurdle Rate values.
    */
   public final String[] getHurdleRateArray()
   {
      return _HurdleRate;
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
      
      _MktIdxDetlRId = resizeArray( _MktIdxDetlRId, _RepeatCount );
      _rxIndexCode = resizeArray( _rxIndexCode, _RepeatCount );
      _ClosingValue = resizeArray( _ClosingValue, _RepeatCount );
      _EffectiveDate = resizeArray( _EffectiveDate, _RepeatCount );
      _GoodBad = resizeArray( _GoodBad, _RepeatCount );
      _Version = resizeArray( _Version, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _UserName = resizeArray( _UserName, _RepeatCount );
      _TimeStamp = resizeArray( _TimeStamp, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _PcntChange = resizeArray( _PcntChange, _RepeatCount );
      _HurdleRate = resizeArray( _HurdleRate, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _MktIdxDetlRId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _rxIndexCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClosingValue[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _GoodBad[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _Version[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _UserName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TimeStamp[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PcntChange[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _HurdleRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
