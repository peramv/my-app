
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Shareholder - Fund Sponsor Agreement Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/ShrFndSpAgrInq.doc">ShrFndSpAgrInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class ShrFndSpAgrInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Fund Sponsor member array.
    */
   private String[] _rxFundGroup = null;
   
   /**
    * Distribution Cooperation Agreement member array.
    */
   private String[] _DistCoopAgrmnt = null;
   
   /**
    * Created by member array.
    */
   private String[] _UserName = null;
   
   /**
    * Date created member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * Modified by member array.
    */
   private String[] _ModUser = null;
   
   /**
    * Date modified member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = null;
   
   /**
    * Fund Sponsor Name member array.
    */
   private String[] _FndGrpName1 = null;
   
   /**
    * Record ID member array.
    */
   private Integer[] _ShrFndSpnRId = null;
   
   /**
    * Version number member array.
    */
   private Integer[] _ShrFndSpnVer = null;
   

   /**
    * Constructs the ShrFndSpAgrInqView object.
    * 
    */
   public ShrFndSpAgrInqView()
   {
      super ( new ShrFndSpAgrInqRequest() );
   }

   /**
    * Constructs the ShrFndSpAgrInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public ShrFndSpAgrInqView( String hostEncoding )
   {
      super ( new ShrFndSpAgrInqRequest( hostEncoding ) );
   }

   /**
    * Gets the ShrFndSpAgrInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The ShrFndSpAgrInqRequest object.
    */
   public final ShrFndSpAgrInqRequest getRequest()
   {
      return (ShrFndSpAgrInqRequest)getIFastRequest();
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
    * Gets the Fund Sponsor field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Sponsor or null.
    */
   public final String getrxFundGroup( int index )
   {
      return _rxFundGroup[index];
   }
    
   /**
    * Gets the Fund Sponsor field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Sponsor or the specified default value.
    */
   public final String getrxFundGroup( int index, String defaultValue )
   {
      return _rxFundGroup[index] == null ? defaultValue : _rxFundGroup[index];
   }
    
   /**
    * Gets the array of Fund Sponsor fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Sponsor values.
    */
   public final String[] getrxFundGroupArray()
   {
      return _rxFundGroup;
   }
    
   /**
    * Gets the Distribution Cooperation Agreement field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Distribution Cooperation Agreement or null.
    */
   public final String getDistCoopAgrmnt( int index )
   {
      return _DistCoopAgrmnt[index];
   }
    
   /**
    * Gets the Distribution Cooperation Agreement field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Distribution Cooperation Agreement or the specified default value.
    */
   public final String getDistCoopAgrmnt( int index, String defaultValue )
   {
      return _DistCoopAgrmnt[index] == null ? defaultValue : _DistCoopAgrmnt[index];
   }
    
   /**
    * Gets the array of Distribution Cooperation Agreement fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Distribution Cooperation Agreement values.
    */
   public final String[] getDistCoopAgrmntArray()
   {
      return _DistCoopAgrmnt;
   }
    
   /**
    * Gets the Created by field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Created by or null.
    */
   public final String getUserName( int index )
   {
      return _UserName[index];
   }
    
   /**
    * Gets the Created by field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Created by or the specified default value.
    */
   public final String getUserName( int index, String defaultValue )
   {
      return _UserName[index] == null ? defaultValue : _UserName[index];
   }
    
   /**
    * Gets the array of Created by fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Created by values.
    */
   public final String[] getUserNameArray()
   {
      return _UserName;
   }
    
   /**
    * Gets the Date created field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Date created or null.
    */
   public final Date getProcessDate( int index )
   {
      return _ProcessDate[index];
   }
    
   /**
    * Gets the Date created field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date created or the specified default value.
    */
   public final Date getProcessDate( int index, Date defaultValue )
   {
      return _ProcessDate[index] == null ? defaultValue : _ProcessDate[index];
   }
    
   /**
    * Gets the array of Date created fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Date created values.
    */
   public final Date[] getProcessDateArray()
   {
      return _ProcessDate;
   }
    
   /**
    * Gets the Modified by field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Modified by or null.
    */
   public final String getModUser( int index )
   {
      return _ModUser[index];
   }
    
   /**
    * Gets the Modified by field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Modified by or the specified default value.
    */
   public final String getModUser( int index, String defaultValue )
   {
      return _ModUser[index] == null ? defaultValue : _ModUser[index];
   }
    
   /**
    * Gets the array of Modified by fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Modified by values.
    */
   public final String[] getModUserArray()
   {
      return _ModUser;
   }
    
   /**
    * Gets the Date modified field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Date modified or null.
    */
   public final Date getModDate( int index )
   {
      return _ModDate[index];
   }
    
   /**
    * Gets the Date modified field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date modified or the specified default value.
    */
   public final Date getModDate( int index, Date defaultValue )
   {
      return _ModDate[index] == null ? defaultValue : _ModDate[index];
   }
    
   /**
    * Gets the array of Date modified fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Date modified values.
    */
   public final Date[] getModDateArray()
   {
      return _ModDate;
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
    * Gets the Fund Sponsor Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Sponsor Name or null.
    */
   public final String getFndGrpName1( int index )
   {
      return _FndGrpName1[index];
   }
    
   /**
    * Gets the Fund Sponsor Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Sponsor Name or the specified default value.
    */
   public final String getFndGrpName1( int index, String defaultValue )
   {
      return _FndGrpName1[index] == null ? defaultValue : _FndGrpName1[index];
   }
    
   /**
    * Gets the array of Fund Sponsor Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Sponsor Name values.
    */
   public final String[] getFndGrpName1Array()
   {
      return _FndGrpName1;
   }
    
   /**
    * Gets the Record ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Record ID or null.
    */
   public final Integer getShrFndSpnRId( int index )
   {
      return _ShrFndSpnRId[index];
   }
    
   /**
    * Gets the Record ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Record ID or the specified default value.
    */
   public final int getShrFndSpnRId( int index, int defaultValue )
   {
      return _ShrFndSpnRId[index] == null ? defaultValue : _ShrFndSpnRId[index].intValue();
   }
    
   /**
    * Gets the array of Record ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Record ID values.
    */
   public final Integer[] getShrFndSpnRIdArray()
   {
      return _ShrFndSpnRId;
   }
    
   /**
    * Gets the Version number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Version number or null.
    */
   public final Integer getShrFndSpnVer( int index )
   {
      return _ShrFndSpnVer[index];
   }
    
   /**
    * Gets the Version number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Version number or the specified default value.
    */
   public final int getShrFndSpnVer( int index, int defaultValue )
   {
      return _ShrFndSpnVer[index] == null ? defaultValue : _ShrFndSpnVer[index].intValue();
   }
    
   /**
    * Gets the array of Version number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Version number values.
    */
   public final Integer[] getShrFndSpnVerArray()
   {
      return _ShrFndSpnVer;
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
      
      _rxFundGroup = resizeArray( _rxFundGroup, _RepeatCount );
      _DistCoopAgrmnt = resizeArray( _DistCoopAgrmnt, _RepeatCount );
      _UserName = resizeArray( _UserName, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _EffectiveDate = resizeArray( _EffectiveDate, _RepeatCount );
      _FndGrpName1 = resizeArray( _FndGrpName1, _RepeatCount );
      _ShrFndSpnRId = resizeArray( _ShrFndSpnRId, _RepeatCount );
      _ShrFndSpnVer = resizeArray( _ShrFndSpnVer, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxFundGroup[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DistCoopAgrmnt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UserName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _FndGrpName1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ShrFndSpnRId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ShrFndSpnVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
      }
      

   }

}
      
