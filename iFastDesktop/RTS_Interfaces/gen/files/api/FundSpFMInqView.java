
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Fund Sponsor Fee Model Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/FundSpFMInq.doc">FundSpFMInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class FundSpFMInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Fund group member array.
    */
   private String[] _RxFundGroup = null;
   
   /**
    * Fee model code member array.
    */
   private String[] _RxFeeModelCode = null;
   
   /**
    * Fee model option member array.
    */
   private String[] _FeeModelOption = null;
   
   /**
    * Start date of fund sponsor fee model member array.
    */
   private Date[] _StartDate = null;
   
   /**
    * Stop date of fund sponsor fee model member array.
    */
   private Date[] _StopDate = null;
   
   /**
    * Process date of fund sponsor fee model member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * User who created the fund sponsor fee model member array.
    */
   private String[] _UserName = null;
   
   /**
    * The fee model modification date member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * The user who modified the fund sponsor fee model member array.
    */
   private String[] _ModUser = null;
   
   /**
    * RecID of the fund sponsor fee model record member array.
    */
   private Integer[] _FundSpFMRId = null;
   
   /**
    * Version of fund sponsor fee model reocord member array.
    */
   private Integer[] _FundSpFMVer = null;
   

   /**
    * Constructs the FundSpFMInqView object.
    * 
    */
   public FundSpFMInqView()
   {
      super ( new FundSpFMInqRequest() );
   }

   /**
    * Constructs the FundSpFMInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public FundSpFMInqView( String hostEncoding )
   {
      super ( new FundSpFMInqRequest( hostEncoding ) );
   }

   /**
    * Gets the FundSpFMInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The FundSpFMInqRequest object.
    */
   public final FundSpFMInqRequest getRequest()
   {
      return (FundSpFMInqRequest)getIFastRequest();
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
    * Gets the Fund group field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund group or null.
    */
   public final String getRxFundGroup( int index )
   {
      return _RxFundGroup[index];
   }
    
   /**
    * Gets the Fund group field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund group or the specified default value.
    */
   public final String getRxFundGroup( int index, String defaultValue )
   {
      return _RxFundGroup[index] == null ? defaultValue : _RxFundGroup[index];
   }
    
   /**
    * Gets the array of Fund group fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund group values.
    */
   public final String[] getRxFundGroupArray()
   {
      return _RxFundGroup;
   }
    
   /**
    * Gets the Fee model code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fee model code or null.
    */
   public final String getRxFeeModelCode( int index )
   {
      return _RxFeeModelCode[index];
   }
    
   /**
    * Gets the Fee model code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee model code or the specified default value.
    */
   public final String getRxFeeModelCode( int index, String defaultValue )
   {
      return _RxFeeModelCode[index] == null ? defaultValue : _RxFeeModelCode[index];
   }
    
   /**
    * Gets the array of Fee model code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee model code values.
    */
   public final String[] getRxFeeModelCodeArray()
   {
      return _RxFeeModelCode;
   }
    
   /**
    * Gets the Fee model option field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fee model option or null.
    */
   public final String getFeeModelOption( int index )
   {
      return _FeeModelOption[index];
   }
    
   /**
    * Gets the Fee model option field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee model option or the specified default value.
    */
   public final String getFeeModelOption( int index, String defaultValue )
   {
      return _FeeModelOption[index] == null ? defaultValue : _FeeModelOption[index];
   }
    
   /**
    * Gets the array of Fee model option fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee model option values.
    */
   public final String[] getFeeModelOptionArray()
   {
      return _FeeModelOption;
   }
    
   /**
    * Gets the Start date of fund sponsor fee model field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Start date of fund sponsor fee model or null.
    */
   public final Date getStartDate( int index )
   {
      return _StartDate[index];
   }
    
   /**
    * Gets the Start date of fund sponsor fee model field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Start date of fund sponsor fee model or the specified default value.
    */
   public final Date getStartDate( int index, Date defaultValue )
   {
      return _StartDate[index] == null ? defaultValue : _StartDate[index];
   }
    
   /**
    * Gets the array of Start date of fund sponsor fee model fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Start date of fund sponsor fee model values.
    */
   public final Date[] getStartDateArray()
   {
      return _StartDate;
   }
    
   /**
    * Gets the Stop date of fund sponsor fee model field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stop date of fund sponsor fee model or null.
    */
   public final Date getStopDate( int index )
   {
      return _StopDate[index];
   }
    
   /**
    * Gets the Stop date of fund sponsor fee model field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop date of fund sponsor fee model or the specified default value.
    */
   public final Date getStopDate( int index, Date defaultValue )
   {
      return _StopDate[index] == null ? defaultValue : _StopDate[index];
   }
    
   /**
    * Gets the array of Stop date of fund sponsor fee model fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stop date of fund sponsor fee model values.
    */
   public final Date[] getStopDateArray()
   {
      return _StopDate;
   }
    
   /**
    * Gets the Process date of fund sponsor fee model field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Process date of fund sponsor fee model or null.
    */
   public final Date getProcessDate( int index )
   {
      return _ProcessDate[index];
   }
    
   /**
    * Gets the Process date of fund sponsor fee model field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Process date of fund sponsor fee model or the specified default value.
    */
   public final Date getProcessDate( int index, Date defaultValue )
   {
      return _ProcessDate[index] == null ? defaultValue : _ProcessDate[index];
   }
    
   /**
    * Gets the array of Process date of fund sponsor fee model fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Process date of fund sponsor fee model values.
    */
   public final Date[] getProcessDateArray()
   {
      return _ProcessDate;
   }
    
   /**
    * Gets the User who created the fund sponsor fee model field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the User who created the fund sponsor fee model or null.
    */
   public final String getUserName( int index )
   {
      return _UserName[index];
   }
    
   /**
    * Gets the User who created the fund sponsor fee model field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the User who created the fund sponsor fee model or the specified default value.
    */
   public final String getUserName( int index, String defaultValue )
   {
      return _UserName[index] == null ? defaultValue : _UserName[index];
   }
    
   /**
    * Gets the array of User who created the fund sponsor fee model fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of User who created the fund sponsor fee model values.
    */
   public final String[] getUserNameArray()
   {
      return _UserName;
   }
    
   /**
    * Gets the The fee model modification date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the The fee model modification date or null.
    */
   public final Date getModDate( int index )
   {
      return _ModDate[index];
   }
    
   /**
    * Gets the The fee model modification date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the The fee model modification date or the specified default value.
    */
   public final Date getModDate( int index, Date defaultValue )
   {
      return _ModDate[index] == null ? defaultValue : _ModDate[index];
   }
    
   /**
    * Gets the array of The fee model modification date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of The fee model modification date values.
    */
   public final Date[] getModDateArray()
   {
      return _ModDate;
   }
    
   /**
    * Gets the The user who modified the fund sponsor fee model field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the The user who modified the fund sponsor fee model or null.
    */
   public final String getModUser( int index )
   {
      return _ModUser[index];
   }
    
   /**
    * Gets the The user who modified the fund sponsor fee model field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the The user who modified the fund sponsor fee model or the specified default value.
    */
   public final String getModUser( int index, String defaultValue )
   {
      return _ModUser[index] == null ? defaultValue : _ModUser[index];
   }
    
   /**
    * Gets the array of The user who modified the fund sponsor fee model fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of The user who modified the fund sponsor fee model values.
    */
   public final String[] getModUserArray()
   {
      return _ModUser;
   }
    
   /**
    * Gets the RecID of the fund sponsor fee model record field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RecID of the fund sponsor fee model record or null.
    */
   public final Integer getFundSpFMRId( int index )
   {
      return _FundSpFMRId[index];
   }
    
   /**
    * Gets the RecID of the fund sponsor fee model record field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RecID of the fund sponsor fee model record or the specified default value.
    */
   public final int getFundSpFMRId( int index, int defaultValue )
   {
      return _FundSpFMRId[index] == null ? defaultValue : _FundSpFMRId[index].intValue();
   }
    
   /**
    * Gets the array of RecID of the fund sponsor fee model record fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RecID of the fund sponsor fee model record values.
    */
   public final Integer[] getFundSpFMRIdArray()
   {
      return _FundSpFMRId;
   }
    
   /**
    * Gets the Version of fund sponsor fee model reocord field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Version of fund sponsor fee model reocord or null.
    */
   public final Integer getFundSpFMVer( int index )
   {
      return _FundSpFMVer[index];
   }
    
   /**
    * Gets the Version of fund sponsor fee model reocord field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Version of fund sponsor fee model reocord or the specified default value.
    */
   public final int getFundSpFMVer( int index, int defaultValue )
   {
      return _FundSpFMVer[index] == null ? defaultValue : _FundSpFMVer[index].intValue();
   }
    
   /**
    * Gets the array of Version of fund sponsor fee model reocord fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Version of fund sponsor fee model reocord values.
    */
   public final Integer[] getFundSpFMVerArray()
   {
      return _FundSpFMVer;
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
      
      _RxFundGroup = resizeArray( _RxFundGroup, _RepeatCount );
      _RxFeeModelCode = resizeArray( _RxFeeModelCode, _RepeatCount );
      _FeeModelOption = resizeArray( _FeeModelOption, _RepeatCount );
      _StartDate = resizeArray( _StartDate, _RepeatCount );
      _StopDate = resizeArray( _StopDate, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _UserName = resizeArray( _UserName, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _FundSpFMRId = resizeArray( _FundSpFMRId, _RepeatCount );
      _FundSpFMVer = resizeArray( _FundSpFMVer, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _RxFundGroup[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RxFeeModelCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FeeModelOption[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _StartDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _StopDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _UserName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundSpFMRId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _FundSpFMVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
      }
      

   }

}
      
