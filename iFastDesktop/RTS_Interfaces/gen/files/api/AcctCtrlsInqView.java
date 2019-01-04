
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Account Controls Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/AcctCtrlsInq.doc">AcctCtrlsInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class AcctCtrlsInqView extends IFastView implements Serializable
{

   /**
    * Duplicate Exist member variable.
    */
   private Boolean _DuplicateExist = null;
   
   private int _RepeatCount = 0;
   
   /**
    * Rule Type member array.
    */
   private String[] _rxRuleType = null;
   
   /**
    * Fund member array.
    */
   private String[] _rxFundCode = null;
   
   /**
    * Class member array.
    */
   private String[] _rxClassCode = null;
   
   /**
    * Start Date member array.
    */
   private Date[] _rxStartDate = null;
   
   /**
    * Stop Date member array.
    */
   private Date[] _rxStopDate = null;
   
   /**
    * Override Decimal member array.
    */
   private String[] _OverrideAmt = null;
   
   /**
    * Override Logical member array.
    */
   private Boolean[] _OverrideLog = null;
   
   /**
    * Override Character member array.
    */
   private String[] _OverrideChar = null;
   
   /**
    * ProcessDate member array.
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
    * AcctControlsId member array.
    */
   private Integer[] _AcctControlsID = null;
   
   /**
    * AcctControls version member array.
    */
   private Integer[] _AcctControlsVer = null;
   
   /**
    * AcctControlsRID member array.
    */
   private Integer[] _rxAcctControlsRID = null;
   

   /**
    * Constructs the AcctCtrlsInqView object.
    * 
    */
   public AcctCtrlsInqView()
   {
      super ( new AcctCtrlsInqRequest() );
   }

   /**
    * Constructs the AcctCtrlsInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AcctCtrlsInqView( String hostEncoding )
   {
      super ( new AcctCtrlsInqRequest( hostEncoding ) );
   }

   /**
    * Gets the AcctCtrlsInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AcctCtrlsInqRequest object.
    */
   public final AcctCtrlsInqRequest getRequest()
   {
      return (AcctCtrlsInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Duplicate Exist field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Duplicate Exist or null.
    */
   public final Boolean getDuplicateExist()
   {
      return _DuplicateExist;
   }
	
   /**
    * Gets the Duplicate Exist field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Duplicate Exist or the specified default value.
    */
   public final boolean getDuplicateExist( boolean defaultValue )
   {
      return _DuplicateExist == null ? defaultValue : _DuplicateExist.booleanValue();
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
    * Gets the Rule Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Rule Type or null.
    */
   public final String getrxRuleType( int index )
   {
      return _rxRuleType[index];
   }
    
   /**
    * Gets the Rule Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Rule Type or the specified default value.
    */
   public final String getrxRuleType( int index, String defaultValue )
   {
      return _rxRuleType[index] == null ? defaultValue : _rxRuleType[index];
   }
    
   /**
    * Gets the array of Rule Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Rule Type values.
    */
   public final String[] getrxRuleTypeArray()
   {
      return _rxRuleType;
   }
    
   /**
    * Gets the Fund field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund or null.
    */
   public final String getrxFundCode( int index )
   {
      return _rxFundCode[index];
   }
    
   /**
    * Gets the Fund field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund or the specified default value.
    */
   public final String getrxFundCode( int index, String defaultValue )
   {
      return _rxFundCode[index] == null ? defaultValue : _rxFundCode[index];
   }
    
   /**
    * Gets the array of Fund fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund values.
    */
   public final String[] getrxFundCodeArray()
   {
      return _rxFundCode;
   }
    
   /**
    * Gets the Class field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Class or null.
    */
   public final String getrxClassCode( int index )
   {
      return _rxClassCode[index];
   }
    
   /**
    * Gets the Class field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class or the specified default value.
    */
   public final String getrxClassCode( int index, String defaultValue )
   {
      return _rxClassCode[index] == null ? defaultValue : _rxClassCode[index];
   }
    
   /**
    * Gets the array of Class fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Class values.
    */
   public final String[] getrxClassCodeArray()
   {
      return _rxClassCode;
   }
    
   /**
    * Gets the Start Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Start Date or null.
    */
   public final Date getrxStartDate( int index )
   {
      return _rxStartDate[index];
   }
    
   /**
    * Gets the Start Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Start Date or the specified default value.
    */
   public final Date getrxStartDate( int index, Date defaultValue )
   {
      return _rxStartDate[index] == null ? defaultValue : _rxStartDate[index];
   }
    
   /**
    * Gets the array of Start Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Start Date values.
    */
   public final Date[] getrxStartDateArray()
   {
      return _rxStartDate;
   }
    
   /**
    * Gets the Stop Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stop Date or null.
    */
   public final Date getrxStopDate( int index )
   {
      return _rxStopDate[index];
   }
    
   /**
    * Gets the Stop Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Date or the specified default value.
    */
   public final Date getrxStopDate( int index, Date defaultValue )
   {
      return _rxStopDate[index] == null ? defaultValue : _rxStopDate[index];
   }
    
   /**
    * Gets the array of Stop Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stop Date values.
    */
   public final Date[] getrxStopDateArray()
   {
      return _rxStopDate;
   }
    
   /**
    * Gets the Override Decimal field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Override Decimal or null.
    */
   public final String getOverrideAmt( int index )
   {
      return _OverrideAmt[index];
   }
    
   /**
    * Gets the Override Decimal field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Override Decimal or the specified default value.
    */
   public final String getOverrideAmt( int index, String defaultValue )
   {
      return _OverrideAmt[index] == null ? defaultValue : _OverrideAmt[index];
   }
    
   /**
    * Gets the array of Override Decimal fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Override Decimal values.
    */
   public final String[] getOverrideAmtArray()
   {
      return _OverrideAmt;
   }
    
   /**
    * Gets the Override Logical field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Override Logical or null.
    */
   public final Boolean getOverrideLog( int index )
   {
      return _OverrideLog[index];
   }
    
   /**
    * Gets the Override Logical field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Override Logical or the specified default value.
    */
   public final boolean getOverrideLog( int index, boolean defaultValue )
   {
      return _OverrideLog[index] == null ? defaultValue : _OverrideLog[index].booleanValue();
   }
    
   /**
    * Gets the array of Override Logical fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Override Logical values.
    */
   public final Boolean[] getOverrideLogArray()
   {
      return _OverrideLog;
   }
    
   /**
    * Gets the Override Character field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Override Character or null.
    */
   public final String getOverrideChar( int index )
   {
      return _OverrideChar[index];
   }
    
   /**
    * Gets the Override Character field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Override Character or the specified default value.
    */
   public final String getOverrideChar( int index, String defaultValue )
   {
      return _OverrideChar[index] == null ? defaultValue : _OverrideChar[index];
   }
    
   /**
    * Gets the array of Override Character fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Override Character values.
    */
   public final String[] getOverrideCharArray()
   {
      return _OverrideChar;
   }
    
   /**
    * Gets the ProcessDate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ProcessDate or null.
    */
   public final Date getProcessDate( int index )
   {
      return _ProcessDate[index];
   }
    
   /**
    * Gets the ProcessDate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ProcessDate or the specified default value.
    */
   public final Date getProcessDate( int index, Date defaultValue )
   {
      return _ProcessDate[index] == null ? defaultValue : _ProcessDate[index];
   }
    
   /**
    * Gets the array of ProcessDate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ProcessDate values.
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
    * Gets the AcctControlsId field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AcctControlsId or null.
    */
   public final Integer getAcctControlsID( int index )
   {
      return _AcctControlsID[index];
   }
    
   /**
    * Gets the AcctControlsId field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AcctControlsId or the specified default value.
    */
   public final int getAcctControlsID( int index, int defaultValue )
   {
      return _AcctControlsID[index] == null ? defaultValue : _AcctControlsID[index].intValue();
   }
    
   /**
    * Gets the array of AcctControlsId fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AcctControlsId values.
    */
   public final Integer[] getAcctControlsIDArray()
   {
      return _AcctControlsID;
   }
    
   /**
    * Gets the AcctControls version field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AcctControls version or null.
    */
   public final Integer getAcctControlsVer( int index )
   {
      return _AcctControlsVer[index];
   }
    
   /**
    * Gets the AcctControls version field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AcctControls version or the specified default value.
    */
   public final int getAcctControlsVer( int index, int defaultValue )
   {
      return _AcctControlsVer[index] == null ? defaultValue : _AcctControlsVer[index].intValue();
   }
    
   /**
    * Gets the array of AcctControls version fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AcctControls version values.
    */
   public final Integer[] getAcctControlsVerArray()
   {
      return _AcctControlsVer;
   }
    
   /**
    * Gets the AcctControlsRID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AcctControlsRID or null.
    */
   public final Integer getrxAcctControlsRID( int index )
   {
      return _rxAcctControlsRID[index];
   }
    
   /**
    * Gets the AcctControlsRID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AcctControlsRID or the specified default value.
    */
   public final int getrxAcctControlsRID( int index, int defaultValue )
   {
      return _rxAcctControlsRID[index] == null ? defaultValue : _rxAcctControlsRID[index].intValue();
   }
    
   /**
    * Gets the array of AcctControlsRID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AcctControlsRID values.
    */
   public final Integer[] getrxAcctControlsRIDArray()
   {
      return _rxAcctControlsRID;
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
      _DuplicateExist = responseBuffer.decodeBoolean(responseBuffer.getNextField());
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _rxRuleType = resizeArray( _rxRuleType, _RepeatCount );
      _rxFundCode = resizeArray( _rxFundCode, _RepeatCount );
      _rxClassCode = resizeArray( _rxClassCode, _RepeatCount );
      _rxStartDate = resizeArray( _rxStartDate, _RepeatCount );
      _rxStopDate = resizeArray( _rxStopDate, _RepeatCount );
      _OverrideAmt = resizeArray( _OverrideAmt, _RepeatCount );
      _OverrideLog = resizeArray( _OverrideLog, _RepeatCount );
      _OverrideChar = resizeArray( _OverrideChar, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _UserName = resizeArray( _UserName, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _AcctControlsID = resizeArray( _AcctControlsID, _RepeatCount );
      _AcctControlsVer = resizeArray( _AcctControlsVer, _RepeatCount );
      _rxAcctControlsRID = resizeArray( _rxAcctControlsRID, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxRuleType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxFundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxStartDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _rxStopDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _OverrideAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _OverrideLog[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _OverrideChar[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _UserName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctControlsID[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _AcctControlsVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _rxAcctControlsRID[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
      }
      

   }

}
      
