
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Security Recon - System Level Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/SecReconInq.doc">SecReconInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class SecReconInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Settlement Location Code member array.
    */
   private String[] _rxSettlLocCode = null;
   
   /**
    * Settlement Location Description member array.
    */
   private String[] _SettlLocDesc = null;
   
   /**
    * Mgmt Comp Settlement Account Num member array.
    */
   private String[] _MgmtSettlAcctNum = null;
   
   /**
    * StatusType member array.
    */
   private Boolean[] _StatusType = null;
   
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
    * Settlement Location Version member array.
    */
   private Integer[] _SettlLocVersion = null;
   
   /**
    * In Use Flag member array.
    */
   private Boolean[] _InUseFlag = null;
   
   /**
    * Settlement Location recid member array.
    */
   private Integer[] _SettlLocRid = null;
   
   /**
    * In Use Trade member array.
    */
   private Boolean[] _InUseTrade = null;
   
   /**
    * 1	InternalSettlementAccount
1	InternalSettlementAccount
InternalSettlementAccount member array.
    */
   private String[] _InternalSettlementAccount = null;
   

   /**
    * Constructs the SecReconInqView object.
    * 
    */
   public SecReconInqView()
   {
      super ( new SecReconInqRequest() );
   }

   /**
    * Constructs the SecReconInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public SecReconInqView( String hostEncoding )
   {
      super ( new SecReconInqRequest( hostEncoding ) );
   }

   /**
    * Gets the SecReconInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The SecReconInqRequest object.
    */
   public final SecReconInqRequest getRequest()
   {
      return (SecReconInqRequest)getIFastRequest();
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
   public final String getSettlLocDesc( int index )
   {
      return _SettlLocDesc[index];
   }
    
   /**
    * Gets the Settlement Location Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settlement Location Description or the specified default value.
    */
   public final String getSettlLocDesc( int index, String defaultValue )
   {
      return _SettlLocDesc[index] == null ? defaultValue : _SettlLocDesc[index];
   }
    
   /**
    * Gets the array of Settlement Location Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Settlement Location Description values.
    */
   public final String[] getSettlLocDescArray()
   {
      return _SettlLocDesc;
   }
    
   /**
    * Gets the Mgmt Comp Settlement Account Num field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Mgmt Comp Settlement Account Num or null.
    */
   public final String getMgmtSettlAcctNum( int index )
   {
      return _MgmtSettlAcctNum[index];
   }
    
   /**
    * Gets the Mgmt Comp Settlement Account Num field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Mgmt Comp Settlement Account Num or the specified default value.
    */
   public final String getMgmtSettlAcctNum( int index, String defaultValue )
   {
      return _MgmtSettlAcctNum[index] == null ? defaultValue : _MgmtSettlAcctNum[index];
   }
    
   /**
    * Gets the array of Mgmt Comp Settlement Account Num fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Mgmt Comp Settlement Account Num values.
    */
   public final String[] getMgmtSettlAcctNumArray()
   {
      return _MgmtSettlAcctNum;
   }
    
   /**
    * Gets the StatusType field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the StatusType or null.
    */
   public final Boolean getStatusType( int index )
   {
      return _StatusType[index];
   }
    
   /**
    * Gets the StatusType field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the StatusType or the specified default value.
    */
   public final boolean getStatusType( int index, boolean defaultValue )
   {
      return _StatusType[index] == null ? defaultValue : _StatusType[index].booleanValue();
   }
    
   /**
    * Gets the array of StatusType fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of StatusType values.
    */
   public final Boolean[] getStatusTypeArray()
   {
      return _StatusType;
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
    * Gets the Settlement Location Version field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Settlement Location Version or null.
    */
   public final Integer getSettlLocVersion( int index )
   {
      return _SettlLocVersion[index];
   }
    
   /**
    * Gets the Settlement Location Version field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settlement Location Version or the specified default value.
    */
   public final int getSettlLocVersion( int index, int defaultValue )
   {
      return _SettlLocVersion[index] == null ? defaultValue : _SettlLocVersion[index].intValue();
   }
    
   /**
    * Gets the array of Settlement Location Version fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Settlement Location Version values.
    */
   public final Integer[] getSettlLocVersionArray()
   {
      return _SettlLocVersion;
   }
    
   /**
    * Gets the In Use Flag field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the In Use Flag or null.
    */
   public final Boolean getInUseFlag( int index )
   {
      return _InUseFlag[index];
   }
    
   /**
    * Gets the In Use Flag field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the In Use Flag or the specified default value.
    */
   public final boolean getInUseFlag( int index, boolean defaultValue )
   {
      return _InUseFlag[index] == null ? defaultValue : _InUseFlag[index].booleanValue();
   }
    
   /**
    * Gets the array of In Use Flag fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of In Use Flag values.
    */
   public final Boolean[] getInUseFlagArray()
   {
      return _InUseFlag;
   }
    
   /**
    * Gets the Settlement Location recid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Settlement Location recid or null.
    */
   public final Integer getSettlLocRid( int index )
   {
      return _SettlLocRid[index];
   }
    
   /**
    * Gets the Settlement Location recid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settlement Location recid or the specified default value.
    */
   public final int getSettlLocRid( int index, int defaultValue )
   {
      return _SettlLocRid[index] == null ? defaultValue : _SettlLocRid[index].intValue();
   }
    
   /**
    * Gets the array of Settlement Location recid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Settlement Location recid values.
    */
   public final Integer[] getSettlLocRidArray()
   {
      return _SettlLocRid;
   }
    
   /**
    * Gets the In Use Trade field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the In Use Trade or null.
    */
   public final Boolean getInUseTrade( int index )
   {
      return _InUseTrade[index];
   }
    
   /**
    * Gets the In Use Trade field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the In Use Trade or the specified default value.
    */
   public final boolean getInUseTrade( int index, boolean defaultValue )
   {
      return _InUseTrade[index] == null ? defaultValue : _InUseTrade[index].booleanValue();
   }
    
   /**
    * Gets the array of In Use Trade fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of In Use Trade values.
    */
   public final Boolean[] getInUseTradeArray()
   {
      return _InUseTrade;
   }
    
   /**
    * Gets the 1	InternalSettlementAccount
1	InternalSettlementAccount
InternalSettlementAccount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the 1	InternalSettlementAccount
1	InternalSettlementAccount
InternalSettlementAccount or null.
    */
   public final String getInternalSettlementAccount( int index )
   {
      return _InternalSettlementAccount[index];
   }
    
   /**
    * Gets the 1	InternalSettlementAccount
1	InternalSettlementAccount
InternalSettlementAccount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the 1	InternalSettlementAccount
1	InternalSettlementAccount
InternalSettlementAccount or the specified default value.
    */
   public final String getInternalSettlementAccount( int index, String defaultValue )
   {
      return _InternalSettlementAccount[index] == null ? defaultValue : _InternalSettlementAccount[index];
   }
    
   /**
    * Gets the array of 1	InternalSettlementAccount
1	InternalSettlementAccount
InternalSettlementAccount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of 1	InternalSettlementAccount
1	InternalSettlementAccount
InternalSettlementAccount values.
    */
   public final String[] getInternalSettlementAccountArray()
   {
      return _InternalSettlementAccount;
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
      _SettlLocDesc = resizeArray( _SettlLocDesc, _RepeatCount );
      _MgmtSettlAcctNum = resizeArray( _MgmtSettlAcctNum, _RepeatCount );
      _StatusType = resizeArray( _StatusType, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _UserName = resizeArray( _UserName, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _SettlLocVersion = resizeArray( _SettlLocVersion, _RepeatCount );
      _InUseFlag = resizeArray( _InUseFlag, _RepeatCount );
      _SettlLocRid = resizeArray( _SettlLocRid, _RepeatCount );
      _InUseTrade = resizeArray( _InUseTrade, _RepeatCount );
      _InternalSettlementAccount = resizeArray( _InternalSettlementAccount, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxSettlLocCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SettlLocDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MgmtSettlAcctNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _StatusType[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _UserName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SettlLocVersion[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _InUseFlag[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _SettlLocRid[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _InUseTrade[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _InternalSettlementAccount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
