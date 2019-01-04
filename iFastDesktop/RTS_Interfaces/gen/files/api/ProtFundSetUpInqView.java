
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Protected Fund Set-Up view.
 * For additional view information see <A HREF="../../../../viewspecs/ProtFundSetUpInq.doc">ProtFundSetUpInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class ProtFundSetUpInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Protected Fund Recid member array.
    */
   private Integer[] _ProtectFundRId = null;
   
   /**
    * Fund member array.
    */
   private String[] _FundCode = null;
   
   /**
    * Class member array.
    */
   private String[] _ClassCode = null;
   
   /**
    * Start Date member array.
    */
   private Date[] _StartDate = null;
   
   /**
    * End Date member array.
    */
   private Date[] _EndDate = null;
   
   /**
    * Insurance Company Code member array.
    */
   private String[] _InsurCode = null;
   
   /**
    * Cost of Insurance member array.
    */
   private String[] _InsurCost = null;
   
   /**
    * Type of contract consolidation member array.
    */
   private Integer[] _ContractGapType = null;
   
   /**
    * Number of resets allowed member array.
    */
   private Integer[] _NumResets = null;
   
   /**
    * Number of years from deff to maturity member array.
    */
   private Integer[] _MaturityYears = null;
   
   /**
    * Modified On member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * Modified By member array.
    */
   private String[] _ModUser = null;
   
   /**
    * Created By member array.
    */
   private String[] _UserName = null;
   
   /**
    * Created On member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * Version member array.
    */
   private Integer[] _VersionNum = null;
   
   /**
    * Baycom member array.
    */
   private String[] _Baycom = null;
   

   /**
    * Constructs the ProtFundSetUpInqView object.
    * 
    */
   public ProtFundSetUpInqView()
   {
      super ( new ProtFundSetUpInqRequest() );
   }

   /**
    * Constructs the ProtFundSetUpInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public ProtFundSetUpInqView( String hostEncoding )
   {
      super ( new ProtFundSetUpInqRequest( hostEncoding ) );
   }

   /**
    * Gets the ProtFundSetUpInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The ProtFundSetUpInqRequest object.
    */
   public final ProtFundSetUpInqRequest getRequest()
   {
      return (ProtFundSetUpInqRequest)getIFastRequest();
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
    * Gets the Protected Fund Recid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Protected Fund Recid or null.
    */
   public final Integer getProtectFundRId( int index )
   {
      return _ProtectFundRId[index];
   }
    
   /**
    * Gets the Protected Fund Recid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Protected Fund Recid or the specified default value.
    */
   public final int getProtectFundRId( int index, int defaultValue )
   {
      return _ProtectFundRId[index] == null ? defaultValue : _ProtectFundRId[index].intValue();
   }
    
   /**
    * Gets the array of Protected Fund Recid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Protected Fund Recid values.
    */
   public final Integer[] getProtectFundRIdArray()
   {
      return _ProtectFundRId;
   }
    
   /**
    * Gets the Fund field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund or null.
    */
   public final String getFundCode( int index )
   {
      return _FundCode[index];
   }
    
   /**
    * Gets the Fund field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund or the specified default value.
    */
   public final String getFundCode( int index, String defaultValue )
   {
      return _FundCode[index] == null ? defaultValue : _FundCode[index];
   }
    
   /**
    * Gets the array of Fund fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund values.
    */
   public final String[] getFundCodeArray()
   {
      return _FundCode;
   }
    
   /**
    * Gets the Class field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Class or null.
    */
   public final String getClassCode( int index )
   {
      return _ClassCode[index];
   }
    
   /**
    * Gets the Class field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class or the specified default value.
    */
   public final String getClassCode( int index, String defaultValue )
   {
      return _ClassCode[index] == null ? defaultValue : _ClassCode[index];
   }
    
   /**
    * Gets the array of Class fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Class values.
    */
   public final String[] getClassCodeArray()
   {
      return _ClassCode;
   }
    
   /**
    * Gets the Start Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Start Date or null.
    */
   public final Date getStartDate( int index )
   {
      return _StartDate[index];
   }
    
   /**
    * Gets the Start Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Start Date or the specified default value.
    */
   public final Date getStartDate( int index, Date defaultValue )
   {
      return _StartDate[index] == null ? defaultValue : _StartDate[index];
   }
    
   /**
    * Gets the array of Start Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Start Date values.
    */
   public final Date[] getStartDateArray()
   {
      return _StartDate;
   }
    
   /**
    * Gets the End Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the End Date or null.
    */
   public final Date getEndDate( int index )
   {
      return _EndDate[index];
   }
    
   /**
    * Gets the End Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the End Date or the specified default value.
    */
   public final Date getEndDate( int index, Date defaultValue )
   {
      return _EndDate[index] == null ? defaultValue : _EndDate[index];
   }
    
   /**
    * Gets the array of End Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of End Date values.
    */
   public final Date[] getEndDateArray()
   {
      return _EndDate;
   }
    
   /**
    * Gets the Insurance Company Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Insurance Company Code or null.
    */
   public final String getInsurCode( int index )
   {
      return _InsurCode[index];
   }
    
   /**
    * Gets the Insurance Company Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Insurance Company Code or the specified default value.
    */
   public final String getInsurCode( int index, String defaultValue )
   {
      return _InsurCode[index] == null ? defaultValue : _InsurCode[index];
   }
    
   /**
    * Gets the array of Insurance Company Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Insurance Company Code values.
    */
   public final String[] getInsurCodeArray()
   {
      return _InsurCode;
   }
    
   /**
    * Gets the Cost of Insurance field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Cost of Insurance or null.
    */
   public final String getInsurCost( int index )
   {
      return _InsurCost[index];
   }
    
   /**
    * Gets the Cost of Insurance field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Cost of Insurance or the specified default value.
    */
   public final String getInsurCost( int index, String defaultValue )
   {
      return _InsurCost[index] == null ? defaultValue : _InsurCost[index];
   }
    
   /**
    * Gets the array of Cost of Insurance fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Cost of Insurance values.
    */
   public final String[] getInsurCostArray()
   {
      return _InsurCost;
   }
    
   /**
    * Gets the Type of contract consolidation field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Type of contract consolidation or null.
    */
   public final Integer getContractGapType( int index )
   {
      return _ContractGapType[index];
   }
    
   /**
    * Gets the Type of contract consolidation field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Type of contract consolidation or the specified default value.
    */
   public final int getContractGapType( int index, int defaultValue )
   {
      return _ContractGapType[index] == null ? defaultValue : _ContractGapType[index].intValue();
   }
    
   /**
    * Gets the array of Type of contract consolidation fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Type of contract consolidation values.
    */
   public final Integer[] getContractGapTypeArray()
   {
      return _ContractGapType;
   }
    
   /**
    * Gets the Number of resets allowed field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Number of resets allowed or null.
    */
   public final Integer getNumResets( int index )
   {
      return _NumResets[index];
   }
    
   /**
    * Gets the Number of resets allowed field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Number of resets allowed or the specified default value.
    */
   public final int getNumResets( int index, int defaultValue )
   {
      return _NumResets[index] == null ? defaultValue : _NumResets[index].intValue();
   }
    
   /**
    * Gets the array of Number of resets allowed fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Number of resets allowed values.
    */
   public final Integer[] getNumResetsArray()
   {
      return _NumResets;
   }
    
   /**
    * Gets the Number of years from deff to maturity field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Number of years from deff to maturity or null.
    */
   public final Integer getMaturityYears( int index )
   {
      return _MaturityYears[index];
   }
    
   /**
    * Gets the Number of years from deff to maturity field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Number of years from deff to maturity or the specified default value.
    */
   public final int getMaturityYears( int index, int defaultValue )
   {
      return _MaturityYears[index] == null ? defaultValue : _MaturityYears[index].intValue();
   }
    
   /**
    * Gets the array of Number of years from deff to maturity fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Number of years from deff to maturity values.
    */
   public final Integer[] getMaturityYearsArray()
   {
      return _MaturityYears;
   }
    
   /**
    * Gets the Modified On field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Modified On or null.
    */
   public final Date getModDate( int index )
   {
      return _ModDate[index];
   }
    
   /**
    * Gets the Modified On field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Modified On or the specified default value.
    */
   public final Date getModDate( int index, Date defaultValue )
   {
      return _ModDate[index] == null ? defaultValue : _ModDate[index];
   }
    
   /**
    * Gets the array of Modified On fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Modified On values.
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
    * Gets the Created On field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Created On or null.
    */
   public final Date getProcessDate( int index )
   {
      return _ProcessDate[index];
   }
    
   /**
    * Gets the Created On field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Created On or the specified default value.
    */
   public final Date getProcessDate( int index, Date defaultValue )
   {
      return _ProcessDate[index] == null ? defaultValue : _ProcessDate[index];
   }
    
   /**
    * Gets the array of Created On fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Created On values.
    */
   public final Date[] getProcessDateArray()
   {
      return _ProcessDate;
   }
    
   /**
    * Gets the Version field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Version or null.
    */
   public final Integer getVersionNum( int index )
   {
      return _VersionNum[index];
   }
    
   /**
    * Gets the Version field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Version or the specified default value.
    */
   public final int getVersionNum( int index, int defaultValue )
   {
      return _VersionNum[index] == null ? defaultValue : _VersionNum[index].intValue();
   }
    
   /**
    * Gets the array of Version fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Version values.
    */
   public final Integer[] getVersionNumArray()
   {
      return _VersionNum;
   }
    
   /**
    * Gets the Baycom field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Baycom or null.
    */
   public final String getBaycom( int index )
   {
      return _Baycom[index];
   }
    
   /**
    * Gets the Baycom field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Baycom or the specified default value.
    */
   public final String getBaycom( int index, String defaultValue )
   {
      return _Baycom[index] == null ? defaultValue : _Baycom[index];
   }
    
   /**
    * Gets the array of Baycom fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Baycom values.
    */
   public final String[] getBaycomArray()
   {
      return _Baycom;
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
      
      _ProtectFundRId = resizeArray( _ProtectFundRId, _RepeatCount );
      _FundCode = resizeArray( _FundCode, _RepeatCount );
      _ClassCode = resizeArray( _ClassCode, _RepeatCount );
      _StartDate = resizeArray( _StartDate, _RepeatCount );
      _EndDate = resizeArray( _EndDate, _RepeatCount );
      _InsurCode = resizeArray( _InsurCode, _RepeatCount );
      _InsurCost = resizeArray( _InsurCost, _RepeatCount );
      _ContractGapType = resizeArray( _ContractGapType, _RepeatCount );
      _NumResets = resizeArray( _NumResets, _RepeatCount );
      _MaturityYears = resizeArray( _MaturityYears, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _UserName = resizeArray( _UserName, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _VersionNum = resizeArray( _VersionNum, _RepeatCount );
      _Baycom = resizeArray( _Baycom, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _ProtectFundRId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _FundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _StartDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _EndDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _InsurCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _InsurCost[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ContractGapType[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _NumResets[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _MaturityYears[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UserName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _VersionNum[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _Baycom[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
