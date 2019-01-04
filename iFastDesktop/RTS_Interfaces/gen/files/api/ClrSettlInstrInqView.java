
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Clearing Settlement Instructions Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/ClrSettlInstrInq.doc">ClrSettlInstrInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class ClrSettlInstrInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Settlement Instruction Code member array.
    */
   private String[] _rxSettlnstrCode = null;
   
   /**
    * Is Default Settlement Instruction member array.
    */
   private Boolean[] _IsDefault = null;
   
   /**
    * Delivery To member array.
    */
   private String[] _DeliveryTo = null;
   
   /**
    * For Account member array.
    */
   private String[] _ForAccount = null;
   
   /**
    * In Favour of member array.
    */
   private String[] _InFavourOf = null;
   
   /**
    * Process Date member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * User Name member array.
    */
   private String[] _UserName = null;
   
   /**
    * Date Modified member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * User who modified the record member array.
    */
   private String[] _ModUser = null;
   
   /**
    * Version member array.
    */
   private Integer[] _ClrSettlInstrVer = null;
   
   /**
    * Recid member array.
    */
   private Integer[] _ClrSettlInstrRid = null;
   
   /**
    * Fund Broker Code member array.
    */
   private String[] _rxFundBrokerCode = null;
   
   /**
    * Account member array.
    */
   private String[] _rxAccount = null;
   
   /**
    * Settlement Instruction ID member array.
    */
   private Integer[] _SettleInstrID = null;
   
   /**
    * Location Level member array.
    */
   private String[] _LocationLevel = null;
   
   /**
    * Effective Date member array.
    */
   private Date[] _Deff = null;
   
   /**
    * Stop Date member array.
    */
   private Date[] _StopDate = null;
   
   /**
    * Clear Settlement Method member array.
    */
   private String[] _ClrSettlMethod = null;
   
   /**
    * CashMsgType member array.
    */
   private String[] _CashMsgType = null;
   
   /**
    * IntermediaryBank member array.
    */
   private String[] _IntermediaryBank = null;
   
   /**
    * ReceivingBank member array.
    */
   private String[] _ReceivingBank = null;
   
   /**
    * Beneficiary member array.
    */
   private String[] _Beneficiary = null;
   
   /**
    * SpecialInstructions member array.
    */
   private String[] _SpecialInstructions = null;
   

   /**
    * Constructs the ClrSettlInstrInqView object.
    * 
    */
   public ClrSettlInstrInqView()
   {
      super ( new ClrSettlInstrInqRequest() );
   }

   /**
    * Constructs the ClrSettlInstrInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public ClrSettlInstrInqView( String hostEncoding )
   {
      super ( new ClrSettlInstrInqRequest( hostEncoding ) );
   }

   /**
    * Gets the ClrSettlInstrInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The ClrSettlInstrInqRequest object.
    */
   public final ClrSettlInstrInqRequest getRequest()
   {
      return (ClrSettlInstrInqRequest)getIFastRequest();
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
    * Gets the Settlement Instruction Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Settlement Instruction Code or null.
    */
   public final String getrxSettlnstrCode( int index )
   {
      return _rxSettlnstrCode[index];
   }
    
   /**
    * Gets the Settlement Instruction Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settlement Instruction Code or the specified default value.
    */
   public final String getrxSettlnstrCode( int index, String defaultValue )
   {
      return _rxSettlnstrCode[index] == null ? defaultValue : _rxSettlnstrCode[index];
   }
    
   /**
    * Gets the array of Settlement Instruction Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Settlement Instruction Code values.
    */
   public final String[] getrxSettlnstrCodeArray()
   {
      return _rxSettlnstrCode;
   }
    
   /**
    * Gets the Is Default Settlement Instruction field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Is Default Settlement Instruction or null.
    */
   public final Boolean getIsDefault( int index )
   {
      return _IsDefault[index];
   }
    
   /**
    * Gets the Is Default Settlement Instruction field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Is Default Settlement Instruction or the specified default value.
    */
   public final boolean getIsDefault( int index, boolean defaultValue )
   {
      return _IsDefault[index] == null ? defaultValue : _IsDefault[index].booleanValue();
   }
    
   /**
    * Gets the array of Is Default Settlement Instruction fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Is Default Settlement Instruction values.
    */
   public final Boolean[] getIsDefaultArray()
   {
      return _IsDefault;
   }
    
   /**
    * Gets the Delivery To field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Delivery To or null.
    */
   public final String getDeliveryTo( int index )
   {
      return _DeliveryTo[index];
   }
    
   /**
    * Gets the Delivery To field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Delivery To or the specified default value.
    */
   public final String getDeliveryTo( int index, String defaultValue )
   {
      return _DeliveryTo[index] == null ? defaultValue : _DeliveryTo[index];
   }
    
   /**
    * Gets the array of Delivery To fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Delivery To values.
    */
   public final String[] getDeliveryToArray()
   {
      return _DeliveryTo;
   }
    
   /**
    * Gets the For Account field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the For Account or null.
    */
   public final String getForAccount( int index )
   {
      return _ForAccount[index];
   }
    
   /**
    * Gets the For Account field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the For Account or the specified default value.
    */
   public final String getForAccount( int index, String defaultValue )
   {
      return _ForAccount[index] == null ? defaultValue : _ForAccount[index];
   }
    
   /**
    * Gets the array of For Account fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of For Account values.
    */
   public final String[] getForAccountArray()
   {
      return _ForAccount;
   }
    
   /**
    * Gets the In Favour of field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the In Favour of or null.
    */
   public final String getInFavourOf( int index )
   {
      return _InFavourOf[index];
   }
    
   /**
    * Gets the In Favour of field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the In Favour of or the specified default value.
    */
   public final String getInFavourOf( int index, String defaultValue )
   {
      return _InFavourOf[index] == null ? defaultValue : _InFavourOf[index];
   }
    
   /**
    * Gets the array of In Favour of fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of In Favour of values.
    */
   public final String[] getInFavourOfArray()
   {
      return _InFavourOf;
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
    * Gets the User who modified the record field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the User who modified the record or null.
    */
   public final String getModUser( int index )
   {
      return _ModUser[index];
   }
    
   /**
    * Gets the User who modified the record field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the User who modified the record or the specified default value.
    */
   public final String getModUser( int index, String defaultValue )
   {
      return _ModUser[index] == null ? defaultValue : _ModUser[index];
   }
    
   /**
    * Gets the array of User who modified the record fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of User who modified the record values.
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
   public final Integer getClrSettlInstrVer( int index )
   {
      return _ClrSettlInstrVer[index];
   }
    
   /**
    * Gets the Version field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Version or the specified default value.
    */
   public final int getClrSettlInstrVer( int index, int defaultValue )
   {
      return _ClrSettlInstrVer[index] == null ? defaultValue : _ClrSettlInstrVer[index].intValue();
   }
    
   /**
    * Gets the array of Version fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Version values.
    */
   public final Integer[] getClrSettlInstrVerArray()
   {
      return _ClrSettlInstrVer;
   }
    
   /**
    * Gets the Recid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Recid or null.
    */
   public final Integer getClrSettlInstrRid( int index )
   {
      return _ClrSettlInstrRid[index];
   }
    
   /**
    * Gets the Recid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Recid or the specified default value.
    */
   public final int getClrSettlInstrRid( int index, int defaultValue )
   {
      return _ClrSettlInstrRid[index] == null ? defaultValue : _ClrSettlInstrRid[index].intValue();
   }
    
   /**
    * Gets the array of Recid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Recid values.
    */
   public final Integer[] getClrSettlInstrRidArray()
   {
      return _ClrSettlInstrRid;
   }
    
   /**
    * Gets the Fund Broker Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Broker Code or null.
    */
   public final String getrxFundBrokerCode( int index )
   {
      return _rxFundBrokerCode[index];
   }
    
   /**
    * Gets the Fund Broker Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Broker Code or the specified default value.
    */
   public final String getrxFundBrokerCode( int index, String defaultValue )
   {
      return _rxFundBrokerCode[index] == null ? defaultValue : _rxFundBrokerCode[index];
   }
    
   /**
    * Gets the array of Fund Broker Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Broker Code values.
    */
   public final String[] getrxFundBrokerCodeArray()
   {
      return _rxFundBrokerCode;
   }
    
   /**
    * Gets the Account field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account or null.
    */
   public final String getrxAccount( int index )
   {
      return _rxAccount[index];
   }
    
   /**
    * Gets the Account field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account or the specified default value.
    */
   public final String getrxAccount( int index, String defaultValue )
   {
      return _rxAccount[index] == null ? defaultValue : _rxAccount[index];
   }
    
   /**
    * Gets the array of Account fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account values.
    */
   public final String[] getrxAccountArray()
   {
      return _rxAccount;
   }
    
   /**
    * Gets the Settlement Instruction ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Settlement Instruction ID or null.
    */
   public final Integer getSettleInstrID( int index )
   {
      return _SettleInstrID[index];
   }
    
   /**
    * Gets the Settlement Instruction ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settlement Instruction ID or the specified default value.
    */
   public final int getSettleInstrID( int index, int defaultValue )
   {
      return _SettleInstrID[index] == null ? defaultValue : _SettleInstrID[index].intValue();
   }
    
   /**
    * Gets the array of Settlement Instruction ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Settlement Instruction ID values.
    */
   public final Integer[] getSettleInstrIDArray()
   {
      return _SettleInstrID;
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
    * Gets the Effective Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Effective Date or null.
    */
   public final Date getDeff( int index )
   {
      return _Deff[index];
   }
    
   /**
    * Gets the Effective Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Effective Date or the specified default value.
    */
   public final Date getDeff( int index, Date defaultValue )
   {
      return _Deff[index] == null ? defaultValue : _Deff[index];
   }
    
   /**
    * Gets the array of Effective Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Effective Date values.
    */
   public final Date[] getDeffArray()
   {
      return _Deff;
   }
    
   /**
    * Gets the Stop Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stop Date or null.
    */
   public final Date getStopDate( int index )
   {
      return _StopDate[index];
   }
    
   /**
    * Gets the Stop Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Date or the specified default value.
    */
   public final Date getStopDate( int index, Date defaultValue )
   {
      return _StopDate[index] == null ? defaultValue : _StopDate[index];
   }
    
   /**
    * Gets the array of Stop Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stop Date values.
    */
   public final Date[] getStopDateArray()
   {
      return _StopDate;
   }
    
   /**
    * Gets the Clear Settlement Method field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Clear Settlement Method or null.
    */
   public final String getClrSettlMethod( int index )
   {
      return _ClrSettlMethod[index];
   }
    
   /**
    * Gets the Clear Settlement Method field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Clear Settlement Method or the specified default value.
    */
   public final String getClrSettlMethod( int index, String defaultValue )
   {
      return _ClrSettlMethod[index] == null ? defaultValue : _ClrSettlMethod[index];
   }
    
   /**
    * Gets the array of Clear Settlement Method fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Clear Settlement Method values.
    */
   public final String[] getClrSettlMethodArray()
   {
      return _ClrSettlMethod;
   }
    
   /**
    * Gets the CashMsgType field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the CashMsgType or null.
    */
   public final String getCashMsgType( int index )
   {
      return _CashMsgType[index];
   }
    
   /**
    * Gets the CashMsgType field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the CashMsgType or the specified default value.
    */
   public final String getCashMsgType( int index, String defaultValue )
   {
      return _CashMsgType[index] == null ? defaultValue : _CashMsgType[index];
   }
    
   /**
    * Gets the array of CashMsgType fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of CashMsgType values.
    */
   public final String[] getCashMsgTypeArray()
   {
      return _CashMsgType;
   }
    
   /**
    * Gets the IntermediaryBank field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the IntermediaryBank or null.
    */
   public final String getIntermediaryBank( int index )
   {
      return _IntermediaryBank[index];
   }
    
   /**
    * Gets the IntermediaryBank field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the IntermediaryBank or the specified default value.
    */
   public final String getIntermediaryBank( int index, String defaultValue )
   {
      return _IntermediaryBank[index] == null ? defaultValue : _IntermediaryBank[index];
   }
    
   /**
    * Gets the array of IntermediaryBank fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of IntermediaryBank values.
    */
   public final String[] getIntermediaryBankArray()
   {
      return _IntermediaryBank;
   }
    
   /**
    * Gets the ReceivingBank field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ReceivingBank or null.
    */
   public final String getReceivingBank( int index )
   {
      return _ReceivingBank[index];
   }
    
   /**
    * Gets the ReceivingBank field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ReceivingBank or the specified default value.
    */
   public final String getReceivingBank( int index, String defaultValue )
   {
      return _ReceivingBank[index] == null ? defaultValue : _ReceivingBank[index];
   }
    
   /**
    * Gets the array of ReceivingBank fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ReceivingBank values.
    */
   public final String[] getReceivingBankArray()
   {
      return _ReceivingBank;
   }
    
   /**
    * Gets the Beneficiary field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Beneficiary or null.
    */
   public final String getBeneficiary( int index )
   {
      return _Beneficiary[index];
   }
    
   /**
    * Gets the Beneficiary field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Beneficiary or the specified default value.
    */
   public final String getBeneficiary( int index, String defaultValue )
   {
      return _Beneficiary[index] == null ? defaultValue : _Beneficiary[index];
   }
    
   /**
    * Gets the array of Beneficiary fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Beneficiary values.
    */
   public final String[] getBeneficiaryArray()
   {
      return _Beneficiary;
   }
    
   /**
    * Gets the SpecialInstructions field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SpecialInstructions or null.
    */
   public final String getSpecialInstructions( int index )
   {
      return _SpecialInstructions[index];
   }
    
   /**
    * Gets the SpecialInstructions field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SpecialInstructions or the specified default value.
    */
   public final String getSpecialInstructions( int index, String defaultValue )
   {
      return _SpecialInstructions[index] == null ? defaultValue : _SpecialInstructions[index];
   }
    
   /**
    * Gets the array of SpecialInstructions fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SpecialInstructions values.
    */
   public final String[] getSpecialInstructionsArray()
   {
      return _SpecialInstructions;
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
      
      _rxSettlnstrCode = resizeArray( _rxSettlnstrCode, _RepeatCount );
      _IsDefault = resizeArray( _IsDefault, _RepeatCount );
      _DeliveryTo = resizeArray( _DeliveryTo, _RepeatCount );
      _ForAccount = resizeArray( _ForAccount, _RepeatCount );
      _InFavourOf = resizeArray( _InFavourOf, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _UserName = resizeArray( _UserName, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _ClrSettlInstrVer = resizeArray( _ClrSettlInstrVer, _RepeatCount );
      _ClrSettlInstrRid = resizeArray( _ClrSettlInstrRid, _RepeatCount );
      _rxFundBrokerCode = resizeArray( _rxFundBrokerCode, _RepeatCount );
      _rxAccount = resizeArray( _rxAccount, _RepeatCount );
      _SettleInstrID = resizeArray( _SettleInstrID, _RepeatCount );
      _LocationLevel = resizeArray( _LocationLevel, _RepeatCount );
      _Deff = resizeArray( _Deff, _RepeatCount );
      _StopDate = resizeArray( _StopDate, _RepeatCount );
      _ClrSettlMethod = resizeArray( _ClrSettlMethod, _RepeatCount );
      _CashMsgType = resizeArray( _CashMsgType, _RepeatCount );
      _IntermediaryBank = resizeArray( _IntermediaryBank, _RepeatCount );
      _ReceivingBank = resizeArray( _ReceivingBank, _RepeatCount );
      _Beneficiary = resizeArray( _Beneficiary, _RepeatCount );
      _SpecialInstructions = resizeArray( _SpecialInstructions, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxSettlnstrCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IsDefault[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _DeliveryTo[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ForAccount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _InFavourOf[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _UserName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClrSettlInstrVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ClrSettlInstrRid[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _rxFundBrokerCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxAccount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SettleInstrID[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _LocationLevel[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Deff[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _StopDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ClrSettlMethod[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CashMsgType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IntermediaryBank[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ReceivingBank[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Beneficiary[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SpecialInstructions[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
