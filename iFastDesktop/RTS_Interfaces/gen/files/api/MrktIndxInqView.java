
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Market Index Master Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/MrktIndxInq.doc">MrktIndxInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class MrktIndxInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Standard Market Index Code member array.
    */
   private String[] _IndexCode = null;
   
   /**
    * Standard Market Index Name member array.
    */
   private String[] _IndexName = null;
   
   /**
    * Market Index RId member array.
    */
   private Integer[] _MktIndexRid = null;
   
   /**
    * Market Index Version member array.
    */
   private Integer[] _MktIndexVer = null;
   
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
    * Days Basis member array.
    */
   private String[] _DaysBasis = null;
   
   /**
    * Input Data Type member array.
    */
   private String[] _InputDataType = null;
   

   /**
    * Constructs the MrktIndxInqView object.
    * 
    */
   public MrktIndxInqView()
   {
      super ( new MrktIndxInqRequest() );
   }

   /**
    * Constructs the MrktIndxInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public MrktIndxInqView( String hostEncoding )
   {
      super ( new MrktIndxInqRequest( hostEncoding ) );
   }

   /**
    * Gets the MrktIndxInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The MrktIndxInqRequest object.
    */
   public final MrktIndxInqRequest getRequest()
   {
      return (MrktIndxInqRequest)getIFastRequest();
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
    * Gets the Standard Market Index Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Standard Market Index Code or null.
    */
   public final String getIndexCode( int index )
   {
      return _IndexCode[index];
   }
    
   /**
    * Gets the Standard Market Index Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Standard Market Index Code or the specified default value.
    */
   public final String getIndexCode( int index, String defaultValue )
   {
      return _IndexCode[index] == null ? defaultValue : _IndexCode[index];
   }
    
   /**
    * Gets the array of Standard Market Index Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Standard Market Index Code values.
    */
   public final String[] getIndexCodeArray()
   {
      return _IndexCode;
   }
    
   /**
    * Gets the Standard Market Index Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Standard Market Index Name or null.
    */
   public final String getIndexName( int index )
   {
      return _IndexName[index];
   }
    
   /**
    * Gets the Standard Market Index Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Standard Market Index Name or the specified default value.
    */
   public final String getIndexName( int index, String defaultValue )
   {
      return _IndexName[index] == null ? defaultValue : _IndexName[index];
   }
    
   /**
    * Gets the array of Standard Market Index Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Standard Market Index Name values.
    */
   public final String[] getIndexNameArray()
   {
      return _IndexName;
   }
    
   /**
    * Gets the Market Index RId field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Market Index RId or null.
    */
   public final Integer getMktIndexRid( int index )
   {
      return _MktIndexRid[index];
   }
    
   /**
    * Gets the Market Index RId field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Market Index RId or the specified default value.
    */
   public final int getMktIndexRid( int index, int defaultValue )
   {
      return _MktIndexRid[index] == null ? defaultValue : _MktIndexRid[index].intValue();
   }
    
   /**
    * Gets the array of Market Index RId fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Market Index RId values.
    */
   public final Integer[] getMktIndexRidArray()
   {
      return _MktIndexRid;
   }
    
   /**
    * Gets the Market Index Version field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Market Index Version or null.
    */
   public final Integer getMktIndexVer( int index )
   {
      return _MktIndexVer[index];
   }
    
   /**
    * Gets the Market Index Version field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Market Index Version or the specified default value.
    */
   public final int getMktIndexVer( int index, int defaultValue )
   {
      return _MktIndexVer[index] == null ? defaultValue : _MktIndexVer[index].intValue();
   }
    
   /**
    * Gets the array of Market Index Version fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Market Index Version values.
    */
   public final Integer[] getMktIndexVerArray()
   {
      return _MktIndexVer;
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
    * Gets the Days Basis field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Days Basis or null.
    */
   public final String getDaysBasis( int index )
   {
      return _DaysBasis[index];
   }
    
   /**
    * Gets the Days Basis field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Days Basis or the specified default value.
    */
   public final String getDaysBasis( int index, String defaultValue )
   {
      return _DaysBasis[index] == null ? defaultValue : _DaysBasis[index];
   }
    
   /**
    * Gets the array of Days Basis fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Days Basis values.
    */
   public final String[] getDaysBasisArray()
   {
      return _DaysBasis;
   }
    
   /**
    * Gets the Input Data Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Input Data Type or null.
    */
   public final String getInputDataType( int index )
   {
      return _InputDataType[index];
   }
    
   /**
    * Gets the Input Data Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Input Data Type or the specified default value.
    */
   public final String getInputDataType( int index, String defaultValue )
   {
      return _InputDataType[index] == null ? defaultValue : _InputDataType[index];
   }
    
   /**
    * Gets the array of Input Data Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Input Data Type values.
    */
   public final String[] getInputDataTypeArray()
   {
      return _InputDataType;
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
      
      _IndexCode = resizeArray( _IndexCode, _RepeatCount );
      _IndexName = resizeArray( _IndexName, _RepeatCount );
      _MktIndexRid = resizeArray( _MktIndexRid, _RepeatCount );
      _MktIndexVer = resizeArray( _MktIndexVer, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _UserName = resizeArray( _UserName, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _DaysBasis = resizeArray( _DaysBasis, _RepeatCount );
      _InputDataType = resizeArray( _InputDataType, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _IndexCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IndexName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MktIndexRid[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _MktIndexVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _UserName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DaysBasis[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _InputDataType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
