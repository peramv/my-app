
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Broker List Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/BrokerList.doc">BrokerList.doc</A>.
 * 
 * @author RTS Generated
 */
public class BrokerListView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * rxBrokerCode member array.
    */
   private String[] _rxBrokerCode = null;
   
   /**
    * Broker Name member array.
    */
   private String[] _BrokerName = null;
   
   /**
    * Broker Type member array.
    */
   private String[] _BrokerType = null;
   
   /**
    * Broker Type Description member array.
    */
   private String[] _BrokerTypeDesc = null;
   
   /**
    * Address Line 1 member array.
    */
   private String[] _AddrLine1 = null;
   
   /**
    * Address Line 2 member array.
    */
   private String[] _AddrLine2 = null;
   
   /**
    * Address Line 3 member array.
    */
   private String[] _AddrLine3 = null;
   
   /**
    * Address Line 4 member array.
    */
   private String[] _AddrLine4 = null;
   
   /**
    * Address Line 5 member array.
    */
   private String[] _AddrLine5 = null;
   
   /**
    * Country Code member array.
    */
   private String[] _AddrCntryCode = null;
   
   /**
    * PhoneNumber member array.
    */
   private String[] _PhoneNumber = null;
   
   /**
    * Settlement Days for Purchase member array.
    */
   private Integer[] _SettlePurDays = null;
   
   /**
    * Settlement Days for Redemption member array.
    */
   private Integer[] _SettleRedDays = null;
   
   /**
    * Net Allowed member array.
    */
   private Boolean[] _NetAllowed = null;
   
   /**
    * Broker Allowed to Deal in Fund member array.
    */
   private Boolean[] _FundAllowed = null;
   
   /**
    * Tax Forms for Nominee Accts member array.
    */
   private Boolean[] _TaxNominee = null;
   
   /**
    * Volume Settle Type member array.
    */
   private String[] _VolSettleType = null;
   
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = null;
   
   /**
    * Stop Date member array.
    */
   private Date[] _StopDate = null;
   
   /**
    * Add Permission member array.
    */
   private Boolean[] _AddPerm = null;
   
   /**
    * Payment Instructions for Trailers Avail member array.
    */
   private Boolean[] _PayInstrTrailer = null;
   
   /**
    * Payment Instructions for Comm Avail member array.
    */
   private Boolean[] _PayInstrComm = null;
   
   /**
    * Postal Code member array.
    */
   private String[] _PostalCode = null;
   
   /**
    * Flag indicating if broker requires KYC member array.
    */
   private Boolean[] _KYCRequired = null;
   
   /**
    * HouseBroker member array.
    */
   private Boolean[] _HouseBroker = null;
   
   /**
    * NSCCCompliant member array.
    */
   private Boolean[] _NSCCCompliant = null;
   
   /**
    * FileTypeD member array.
    */
   private Boolean[] _FileTypeD = null;
   
   /**
    * FileTypeJ member array.
    */
   private Boolean[] _FileTypeJ = null;
   
   /**
    * MMWire member array.
    */
   private Boolean[] _MMWire = null;
   
   /**
    * ConfClientNon member array.
    */
   private Boolean[] _ConfClientNom = null;
   
   /**
    * ConfClientOth member array.
    */
   private Boolean[] _ConfClientOth = null;
   
   /**
    * ConfClientCli member array.
    */
   private Boolean[] _ConfClientCli = null;
   
   /**
    * ConfBrkNom member array.
    */
   private Boolean[] _ConfBrkNom = null;
   
   /**
    * ConfBrkOth member array.
    */
   private Boolean[] _ConfBrkOth = null;
   
   /**
    * ConfBrkCli member array.
    */
   private Boolean[] _ConfBrkCli = null;
   
   /**
    * ConfRepNom member array.
    */
   private Boolean[] _ConfRepNom = null;
   
   /**
    * ConfRepOth member array.
    */
   private Boolean[] _ConfRepOth = null;
   
   /**
    * ConfRepCli member array.
    */
   private Boolean[] _ConfRepCli = null;
   
   /**
    * NSCPartId member array.
    */
   private String[] _NSCPartId = null;
   
   /**
    * flag indicating if nsc broker is also clearing firm member array.
    */
   private Boolean[] _RelatedToClrFirm = null;
   
   /**
    * Flag indicating if intermediary is eligible to settle SWP through FUNDServ member array.
    */
   private Boolean[] _SWPSettleESGElig = null;
   
   /**
    * Flag indicating if intermediary is eligible to settle Cash ID through FUNDServ member array.
    */
   private Boolean[] _CashIDSettleESGElig = null;
   
   /**
    * Non Financial Update member array.
    */
   private String[] _NFUpdate = null;
   
   /**
    * KYC Regulation member array.
    */
   private String[] _KYCRegulation = null;
   
   /**
    * AML Agreement member array.
    */
   private String[] _AMLAgreement = null;
   
   /**
    * KYC Signture Store Req member array.
    */
   private String[] _KYCSigntureStoreRe = null;
   
   /**
    * KYC Status member array.
    */
   private String[] _KYCStatus = null;
   
   /**
    * List of BrokerCategory member array.
    */
   private String[] _BrokerCategoryList = null;
   
   /**
    * Guard Option Client member array.
    */
   private String[] _BrokGuardOptClt = null;
   
   /**
    * Guard Option Nominee member array.
    */
   private String[] _BrokGuardOptNom = null;
   
   /**
    * Guard Option Intermediary member array.
    */
   private String[] _BrokGuardOptInt = null;
   
   /**
    * Flag that indicates if broker has EPA agreement member array.
    */
   private Boolean[] _EPABroker = null;
   
   /**
    * Flag that indicates if Fund Serv Broker member array.
    */
   private Boolean[] _FundServBroker = null;
   
   /**
    * Compliant Network member array.
    */
   private String[] _BrokCompliantNW = null;
   
   /**
    * CSS Clearing and Settlement member array.
    */
   private String[] _BrokCssStatus = null;
   

   /**
    * Constructs the BrokerListView object.
    * 
    */
   public BrokerListView()
   {
      super ( new BrokerListRequest() );
   }

   /**
    * Constructs the BrokerListView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public BrokerListView( String hostEncoding )
   {
      super ( new BrokerListRequest( hostEncoding ) );
   }

   /**
    * Gets the BrokerListRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The BrokerListRequest object.
    */
   public final BrokerListRequest getRequest()
   {
      return (BrokerListRequest)getIFastRequest();
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
    * Gets the rxBrokerCode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the rxBrokerCode or null.
    */
   public final String getrxBrokerCode( int index )
   {
      return _rxBrokerCode[index];
   }
    
   /**
    * Gets the rxBrokerCode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the rxBrokerCode or the specified default value.
    */
   public final String getrxBrokerCode( int index, String defaultValue )
   {
      return _rxBrokerCode[index] == null ? defaultValue : _rxBrokerCode[index];
   }
    
   /**
    * Gets the array of rxBrokerCode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of rxBrokerCode values.
    */
   public final String[] getrxBrokerCodeArray()
   {
      return _rxBrokerCode;
   }
    
   /**
    * Gets the Broker Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Broker Name or null.
    */
   public final String getBrokerName( int index )
   {
      return _BrokerName[index];
   }
    
   /**
    * Gets the Broker Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker Name or the specified default value.
    */
   public final String getBrokerName( int index, String defaultValue )
   {
      return _BrokerName[index] == null ? defaultValue : _BrokerName[index];
   }
    
   /**
    * Gets the array of Broker Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Broker Name values.
    */
   public final String[] getBrokerNameArray()
   {
      return _BrokerName;
   }
    
   /**
    * Gets the Broker Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Broker Type or null.
    */
   public final String getBrokerType( int index )
   {
      return _BrokerType[index];
   }
    
   /**
    * Gets the Broker Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker Type or the specified default value.
    */
   public final String getBrokerType( int index, String defaultValue )
   {
      return _BrokerType[index] == null ? defaultValue : _BrokerType[index];
   }
    
   /**
    * Gets the array of Broker Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Broker Type values.
    */
   public final String[] getBrokerTypeArray()
   {
      return _BrokerType;
   }
    
   /**
    * Gets the Broker Type Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Broker Type Description or null.
    */
   public final String getBrokerTypeDesc( int index )
   {
      return _BrokerTypeDesc[index];
   }
    
   /**
    * Gets the Broker Type Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker Type Description or the specified default value.
    */
   public final String getBrokerTypeDesc( int index, String defaultValue )
   {
      return _BrokerTypeDesc[index] == null ? defaultValue : _BrokerTypeDesc[index];
   }
    
   /**
    * Gets the array of Broker Type Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Broker Type Description values.
    */
   public final String[] getBrokerTypeDescArray()
   {
      return _BrokerTypeDesc;
   }
    
   /**
    * Gets the Address Line 1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Line 1 or null.
    */
   public final String getAddrLine1( int index )
   {
      return _AddrLine1[index];
   }
    
   /**
    * Gets the Address Line 1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line 1 or the specified default value.
    */
   public final String getAddrLine1( int index, String defaultValue )
   {
      return _AddrLine1[index] == null ? defaultValue : _AddrLine1[index];
   }
    
   /**
    * Gets the array of Address Line 1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Line 1 values.
    */
   public final String[] getAddrLine1Array()
   {
      return _AddrLine1;
   }
    
   /**
    * Gets the Address Line 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Line 2 or null.
    */
   public final String getAddrLine2( int index )
   {
      return _AddrLine2[index];
   }
    
   /**
    * Gets the Address Line 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line 2 or the specified default value.
    */
   public final String getAddrLine2( int index, String defaultValue )
   {
      return _AddrLine2[index] == null ? defaultValue : _AddrLine2[index];
   }
    
   /**
    * Gets the array of Address Line 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Line 2 values.
    */
   public final String[] getAddrLine2Array()
   {
      return _AddrLine2;
   }
    
   /**
    * Gets the Address Line 3 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Line 3 or null.
    */
   public final String getAddrLine3( int index )
   {
      return _AddrLine3[index];
   }
    
   /**
    * Gets the Address Line 3 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line 3 or the specified default value.
    */
   public final String getAddrLine3( int index, String defaultValue )
   {
      return _AddrLine3[index] == null ? defaultValue : _AddrLine3[index];
   }
    
   /**
    * Gets the array of Address Line 3 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Line 3 values.
    */
   public final String[] getAddrLine3Array()
   {
      return _AddrLine3;
   }
    
   /**
    * Gets the Address Line 4 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Line 4 or null.
    */
   public final String getAddrLine4( int index )
   {
      return _AddrLine4[index];
   }
    
   /**
    * Gets the Address Line 4 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line 4 or the specified default value.
    */
   public final String getAddrLine4( int index, String defaultValue )
   {
      return _AddrLine4[index] == null ? defaultValue : _AddrLine4[index];
   }
    
   /**
    * Gets the array of Address Line 4 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Line 4 values.
    */
   public final String[] getAddrLine4Array()
   {
      return _AddrLine4;
   }
    
   /**
    * Gets the Address Line 5 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Line 5 or null.
    */
   public final String getAddrLine5( int index )
   {
      return _AddrLine5[index];
   }
    
   /**
    * Gets the Address Line 5 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line 5 or the specified default value.
    */
   public final String getAddrLine5( int index, String defaultValue )
   {
      return _AddrLine5[index] == null ? defaultValue : _AddrLine5[index];
   }
    
   /**
    * Gets the array of Address Line 5 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Line 5 values.
    */
   public final String[] getAddrLine5Array()
   {
      return _AddrLine5;
   }
    
   /**
    * Gets the Country Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Country Code or null.
    */
   public final String getAddrCntryCode( int index )
   {
      return _AddrCntryCode[index];
   }
    
   /**
    * Gets the Country Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Country Code or the specified default value.
    */
   public final String getAddrCntryCode( int index, String defaultValue )
   {
      return _AddrCntryCode[index] == null ? defaultValue : _AddrCntryCode[index];
   }
    
   /**
    * Gets the array of Country Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Country Code values.
    */
   public final String[] getAddrCntryCodeArray()
   {
      return _AddrCntryCode;
   }
    
   /**
    * Gets the PhoneNumber field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the PhoneNumber or null.
    */
   public final String getPhoneNumber( int index )
   {
      return _PhoneNumber[index];
   }
    
   /**
    * Gets the PhoneNumber field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PhoneNumber or the specified default value.
    */
   public final String getPhoneNumber( int index, String defaultValue )
   {
      return _PhoneNumber[index] == null ? defaultValue : _PhoneNumber[index];
   }
    
   /**
    * Gets the array of PhoneNumber fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of PhoneNumber values.
    */
   public final String[] getPhoneNumberArray()
   {
      return _PhoneNumber;
   }
    
   /**
    * Gets the Settlement Days for Purchase field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Settlement Days for Purchase or null.
    */
   public final Integer getSettlePurDays( int index )
   {
      return _SettlePurDays[index];
   }
    
   /**
    * Gets the Settlement Days for Purchase field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settlement Days for Purchase or the specified default value.
    */
   public final int getSettlePurDays( int index, int defaultValue )
   {
      return _SettlePurDays[index] == null ? defaultValue : _SettlePurDays[index].intValue();
   }
    
   /**
    * Gets the array of Settlement Days for Purchase fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Settlement Days for Purchase values.
    */
   public final Integer[] getSettlePurDaysArray()
   {
      return _SettlePurDays;
   }
    
   /**
    * Gets the Settlement Days for Redemption field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Settlement Days for Redemption or null.
    */
   public final Integer getSettleRedDays( int index )
   {
      return _SettleRedDays[index];
   }
    
   /**
    * Gets the Settlement Days for Redemption field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settlement Days for Redemption or the specified default value.
    */
   public final int getSettleRedDays( int index, int defaultValue )
   {
      return _SettleRedDays[index] == null ? defaultValue : _SettleRedDays[index].intValue();
   }
    
   /**
    * Gets the array of Settlement Days for Redemption fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Settlement Days for Redemption values.
    */
   public final Integer[] getSettleRedDaysArray()
   {
      return _SettleRedDays;
   }
    
   /**
    * Gets the Net Allowed field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Net Allowed or null.
    */
   public final Boolean getNetAllowed( int index )
   {
      return _NetAllowed[index];
   }
    
   /**
    * Gets the Net Allowed field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Net Allowed or the specified default value.
    */
   public final boolean getNetAllowed( int index, boolean defaultValue )
   {
      return _NetAllowed[index] == null ? defaultValue : _NetAllowed[index].booleanValue();
   }
    
   /**
    * Gets the array of Net Allowed fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Net Allowed values.
    */
   public final Boolean[] getNetAllowedArray()
   {
      return _NetAllowed;
   }
    
   /**
    * Gets the Broker Allowed to Deal in Fund field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Broker Allowed to Deal in Fund or null.
    */
   public final Boolean getFundAllowed( int index )
   {
      return _FundAllowed[index];
   }
    
   /**
    * Gets the Broker Allowed to Deal in Fund field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker Allowed to Deal in Fund or the specified default value.
    */
   public final boolean getFundAllowed( int index, boolean defaultValue )
   {
      return _FundAllowed[index] == null ? defaultValue : _FundAllowed[index].booleanValue();
   }
    
   /**
    * Gets the array of Broker Allowed to Deal in Fund fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Broker Allowed to Deal in Fund values.
    */
   public final Boolean[] getFundAllowedArray()
   {
      return _FundAllowed;
   }
    
   /**
    * Gets the Tax Forms for Nominee Accts field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax Forms for Nominee Accts or null.
    */
   public final Boolean getTaxNominee( int index )
   {
      return _TaxNominee[index];
   }
    
   /**
    * Gets the Tax Forms for Nominee Accts field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Forms for Nominee Accts or the specified default value.
    */
   public final boolean getTaxNominee( int index, boolean defaultValue )
   {
      return _TaxNominee[index] == null ? defaultValue : _TaxNominee[index].booleanValue();
   }
    
   /**
    * Gets the array of Tax Forms for Nominee Accts fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax Forms for Nominee Accts values.
    */
   public final Boolean[] getTaxNomineeArray()
   {
      return _TaxNominee;
   }
    
   /**
    * Gets the Volume Settle Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Volume Settle Type or null.
    */
   public final String getVolSettleType( int index )
   {
      return _VolSettleType[index];
   }
    
   /**
    * Gets the Volume Settle Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Volume Settle Type or the specified default value.
    */
   public final String getVolSettleType( int index, String defaultValue )
   {
      return _VolSettleType[index] == null ? defaultValue : _VolSettleType[index];
   }
    
   /**
    * Gets the array of Volume Settle Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Volume Settle Type values.
    */
   public final String[] getVolSettleTypeArray()
   {
      return _VolSettleType;
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
    * Gets the Add Permission field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Add Permission or null.
    */
   public final Boolean getAddPerm( int index )
   {
      return _AddPerm[index];
   }
    
   /**
    * Gets the Add Permission field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Add Permission or the specified default value.
    */
   public final boolean getAddPerm( int index, boolean defaultValue )
   {
      return _AddPerm[index] == null ? defaultValue : _AddPerm[index].booleanValue();
   }
    
   /**
    * Gets the array of Add Permission fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Add Permission values.
    */
   public final Boolean[] getAddPermArray()
   {
      return _AddPerm;
   }
    
   /**
    * Gets the Payment Instructions for Trailers Avail field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Payment Instructions for Trailers Avail or null.
    */
   public final Boolean getPayInstrTrailer( int index )
   {
      return _PayInstrTrailer[index];
   }
    
   /**
    * Gets the Payment Instructions for Trailers Avail field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payment Instructions for Trailers Avail or the specified default value.
    */
   public final boolean getPayInstrTrailer( int index, boolean defaultValue )
   {
      return _PayInstrTrailer[index] == null ? defaultValue : _PayInstrTrailer[index].booleanValue();
   }
    
   /**
    * Gets the array of Payment Instructions for Trailers Avail fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Payment Instructions for Trailers Avail values.
    */
   public final Boolean[] getPayInstrTrailerArray()
   {
      return _PayInstrTrailer;
   }
    
   /**
    * Gets the Payment Instructions for Comm Avail field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Payment Instructions for Comm Avail or null.
    */
   public final Boolean getPayInstrComm( int index )
   {
      return _PayInstrComm[index];
   }
    
   /**
    * Gets the Payment Instructions for Comm Avail field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payment Instructions for Comm Avail or the specified default value.
    */
   public final boolean getPayInstrComm( int index, boolean defaultValue )
   {
      return _PayInstrComm[index] == null ? defaultValue : _PayInstrComm[index].booleanValue();
   }
    
   /**
    * Gets the array of Payment Instructions for Comm Avail fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Payment Instructions for Comm Avail values.
    */
   public final Boolean[] getPayInstrCommArray()
   {
      return _PayInstrComm;
   }
    
   /**
    * Gets the Postal Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Postal Code or null.
    */
   public final String getPostalCode( int index )
   {
      return _PostalCode[index];
   }
    
   /**
    * Gets the Postal Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Postal Code or the specified default value.
    */
   public final String getPostalCode( int index, String defaultValue )
   {
      return _PostalCode[index] == null ? defaultValue : _PostalCode[index];
   }
    
   /**
    * Gets the array of Postal Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Postal Code values.
    */
   public final String[] getPostalCodeArray()
   {
      return _PostalCode;
   }
    
   /**
    * Gets the Flag indicating if broker requires KYC field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicating if broker requires KYC or null.
    */
   public final Boolean getKYCRequired( int index )
   {
      return _KYCRequired[index];
   }
    
   /**
    * Gets the Flag indicating if broker requires KYC field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if broker requires KYC or the specified default value.
    */
   public final boolean getKYCRequired( int index, boolean defaultValue )
   {
      return _KYCRequired[index] == null ? defaultValue : _KYCRequired[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicating if broker requires KYC fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicating if broker requires KYC values.
    */
   public final Boolean[] getKYCRequiredArray()
   {
      return _KYCRequired;
   }
    
   /**
    * Gets the HouseBroker field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the HouseBroker or null.
    */
   public final Boolean getHouseBroker( int index )
   {
      return _HouseBroker[index];
   }
    
   /**
    * Gets the HouseBroker field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the HouseBroker or the specified default value.
    */
   public final boolean getHouseBroker( int index, boolean defaultValue )
   {
      return _HouseBroker[index] == null ? defaultValue : _HouseBroker[index].booleanValue();
   }
    
   /**
    * Gets the array of HouseBroker fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of HouseBroker values.
    */
   public final Boolean[] getHouseBrokerArray()
   {
      return _HouseBroker;
   }
    
   /**
    * Gets the NSCCCompliant field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the NSCCCompliant or null.
    */
   public final Boolean getNSCCCompliant( int index )
   {
      return _NSCCCompliant[index];
   }
    
   /**
    * Gets the NSCCCompliant field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the NSCCCompliant or the specified default value.
    */
   public final boolean getNSCCCompliant( int index, boolean defaultValue )
   {
      return _NSCCCompliant[index] == null ? defaultValue : _NSCCCompliant[index].booleanValue();
   }
    
   /**
    * Gets the array of NSCCCompliant fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of NSCCCompliant values.
    */
   public final Boolean[] getNSCCCompliantArray()
   {
      return _NSCCCompliant;
   }
    
   /**
    * Gets the FileTypeD field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FileTypeD or null.
    */
   public final Boolean getFileTypeD( int index )
   {
      return _FileTypeD[index];
   }
    
   /**
    * Gets the FileTypeD field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FileTypeD or the specified default value.
    */
   public final boolean getFileTypeD( int index, boolean defaultValue )
   {
      return _FileTypeD[index] == null ? defaultValue : _FileTypeD[index].booleanValue();
   }
    
   /**
    * Gets the array of FileTypeD fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FileTypeD values.
    */
   public final Boolean[] getFileTypeDArray()
   {
      return _FileTypeD;
   }
    
   /**
    * Gets the FileTypeJ field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FileTypeJ or null.
    */
   public final Boolean getFileTypeJ( int index )
   {
      return _FileTypeJ[index];
   }
    
   /**
    * Gets the FileTypeJ field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FileTypeJ or the specified default value.
    */
   public final boolean getFileTypeJ( int index, boolean defaultValue )
   {
      return _FileTypeJ[index] == null ? defaultValue : _FileTypeJ[index].booleanValue();
   }
    
   /**
    * Gets the array of FileTypeJ fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FileTypeJ values.
    */
   public final Boolean[] getFileTypeJArray()
   {
      return _FileTypeJ;
   }
    
   /**
    * Gets the MMWire field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the MMWire or null.
    */
   public final Boolean getMMWire( int index )
   {
      return _MMWire[index];
   }
    
   /**
    * Gets the MMWire field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the MMWire or the specified default value.
    */
   public final boolean getMMWire( int index, boolean defaultValue )
   {
      return _MMWire[index] == null ? defaultValue : _MMWire[index].booleanValue();
   }
    
   /**
    * Gets the array of MMWire fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of MMWire values.
    */
   public final Boolean[] getMMWireArray()
   {
      return _MMWire;
   }
    
   /**
    * Gets the ConfClientNon field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ConfClientNon or null.
    */
   public final Boolean getConfClientNom( int index )
   {
      return _ConfClientNom[index];
   }
    
   /**
    * Gets the ConfClientNon field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ConfClientNon or the specified default value.
    */
   public final boolean getConfClientNom( int index, boolean defaultValue )
   {
      return _ConfClientNom[index] == null ? defaultValue : _ConfClientNom[index].booleanValue();
   }
    
   /**
    * Gets the array of ConfClientNon fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ConfClientNon values.
    */
   public final Boolean[] getConfClientNomArray()
   {
      return _ConfClientNom;
   }
    
   /**
    * Gets the ConfClientOth field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ConfClientOth or null.
    */
   public final Boolean getConfClientOth( int index )
   {
      return _ConfClientOth[index];
   }
    
   /**
    * Gets the ConfClientOth field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ConfClientOth or the specified default value.
    */
   public final boolean getConfClientOth( int index, boolean defaultValue )
   {
      return _ConfClientOth[index] == null ? defaultValue : _ConfClientOth[index].booleanValue();
   }
    
   /**
    * Gets the array of ConfClientOth fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ConfClientOth values.
    */
   public final Boolean[] getConfClientOthArray()
   {
      return _ConfClientOth;
   }
    
   /**
    * Gets the ConfClientCli field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ConfClientCli or null.
    */
   public final Boolean getConfClientCli( int index )
   {
      return _ConfClientCli[index];
   }
    
   /**
    * Gets the ConfClientCli field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ConfClientCli or the specified default value.
    */
   public final boolean getConfClientCli( int index, boolean defaultValue )
   {
      return _ConfClientCli[index] == null ? defaultValue : _ConfClientCli[index].booleanValue();
   }
    
   /**
    * Gets the array of ConfClientCli fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ConfClientCli values.
    */
   public final Boolean[] getConfClientCliArray()
   {
      return _ConfClientCli;
   }
    
   /**
    * Gets the ConfBrkNom field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ConfBrkNom or null.
    */
   public final Boolean getConfBrkNom( int index )
   {
      return _ConfBrkNom[index];
   }
    
   /**
    * Gets the ConfBrkNom field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ConfBrkNom or the specified default value.
    */
   public final boolean getConfBrkNom( int index, boolean defaultValue )
   {
      return _ConfBrkNom[index] == null ? defaultValue : _ConfBrkNom[index].booleanValue();
   }
    
   /**
    * Gets the array of ConfBrkNom fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ConfBrkNom values.
    */
   public final Boolean[] getConfBrkNomArray()
   {
      return _ConfBrkNom;
   }
    
   /**
    * Gets the ConfBrkOth field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ConfBrkOth or null.
    */
   public final Boolean getConfBrkOth( int index )
   {
      return _ConfBrkOth[index];
   }
    
   /**
    * Gets the ConfBrkOth field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ConfBrkOth or the specified default value.
    */
   public final boolean getConfBrkOth( int index, boolean defaultValue )
   {
      return _ConfBrkOth[index] == null ? defaultValue : _ConfBrkOth[index].booleanValue();
   }
    
   /**
    * Gets the array of ConfBrkOth fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ConfBrkOth values.
    */
   public final Boolean[] getConfBrkOthArray()
   {
      return _ConfBrkOth;
   }
    
   /**
    * Gets the ConfBrkCli field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ConfBrkCli or null.
    */
   public final Boolean getConfBrkCli( int index )
   {
      return _ConfBrkCli[index];
   }
    
   /**
    * Gets the ConfBrkCli field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ConfBrkCli or the specified default value.
    */
   public final boolean getConfBrkCli( int index, boolean defaultValue )
   {
      return _ConfBrkCli[index] == null ? defaultValue : _ConfBrkCli[index].booleanValue();
   }
    
   /**
    * Gets the array of ConfBrkCli fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ConfBrkCli values.
    */
   public final Boolean[] getConfBrkCliArray()
   {
      return _ConfBrkCli;
   }
    
   /**
    * Gets the ConfRepNom field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ConfRepNom or null.
    */
   public final Boolean getConfRepNom( int index )
   {
      return _ConfRepNom[index];
   }
    
   /**
    * Gets the ConfRepNom field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ConfRepNom or the specified default value.
    */
   public final boolean getConfRepNom( int index, boolean defaultValue )
   {
      return _ConfRepNom[index] == null ? defaultValue : _ConfRepNom[index].booleanValue();
   }
    
   /**
    * Gets the array of ConfRepNom fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ConfRepNom values.
    */
   public final Boolean[] getConfRepNomArray()
   {
      return _ConfRepNom;
   }
    
   /**
    * Gets the ConfRepOth field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ConfRepOth or null.
    */
   public final Boolean getConfRepOth( int index )
   {
      return _ConfRepOth[index];
   }
    
   /**
    * Gets the ConfRepOth field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ConfRepOth or the specified default value.
    */
   public final boolean getConfRepOth( int index, boolean defaultValue )
   {
      return _ConfRepOth[index] == null ? defaultValue : _ConfRepOth[index].booleanValue();
   }
    
   /**
    * Gets the array of ConfRepOth fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ConfRepOth values.
    */
   public final Boolean[] getConfRepOthArray()
   {
      return _ConfRepOth;
   }
    
   /**
    * Gets the ConfRepCli field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ConfRepCli or null.
    */
   public final Boolean getConfRepCli( int index )
   {
      return _ConfRepCli[index];
   }
    
   /**
    * Gets the ConfRepCli field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ConfRepCli or the specified default value.
    */
   public final boolean getConfRepCli( int index, boolean defaultValue )
   {
      return _ConfRepCli[index] == null ? defaultValue : _ConfRepCli[index].booleanValue();
   }
    
   /**
    * Gets the array of ConfRepCli fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ConfRepCli values.
    */
   public final Boolean[] getConfRepCliArray()
   {
      return _ConfRepCli;
   }
    
   /**
    * Gets the NSCPartId field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the NSCPartId or null.
    */
   public final String getNSCPartId( int index )
   {
      return _NSCPartId[index];
   }
    
   /**
    * Gets the NSCPartId field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the NSCPartId or the specified default value.
    */
   public final String getNSCPartId( int index, String defaultValue )
   {
      return _NSCPartId[index] == null ? defaultValue : _NSCPartId[index];
   }
    
   /**
    * Gets the array of NSCPartId fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of NSCPartId values.
    */
   public final String[] getNSCPartIdArray()
   {
      return _NSCPartId;
   }
    
   /**
    * Gets the flag indicating if nsc broker is also clearing firm field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the flag indicating if nsc broker is also clearing firm or null.
    */
   public final Boolean getRelatedToClrFirm( int index )
   {
      return _RelatedToClrFirm[index];
   }
    
   /**
    * Gets the flag indicating if nsc broker is also clearing firm field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the flag indicating if nsc broker is also clearing firm or the specified default value.
    */
   public final boolean getRelatedToClrFirm( int index, boolean defaultValue )
   {
      return _RelatedToClrFirm[index] == null ? defaultValue : _RelatedToClrFirm[index].booleanValue();
   }
    
   /**
    * Gets the array of flag indicating if nsc broker is also clearing firm fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of flag indicating if nsc broker is also clearing firm values.
    */
   public final Boolean[] getRelatedToClrFirmArray()
   {
      return _RelatedToClrFirm;
   }
    
   /**
    * Gets the Flag indicating if intermediary is eligible to settle SWP through FUNDServ field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicating if intermediary is eligible to settle SWP through FUNDServ or null.
    */
   public final Boolean getSWPSettleESGElig( int index )
   {
      return _SWPSettleESGElig[index];
   }
    
   /**
    * Gets the Flag indicating if intermediary is eligible to settle SWP through FUNDServ field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if intermediary is eligible to settle SWP through FUNDServ or the specified default value.
    */
   public final boolean getSWPSettleESGElig( int index, boolean defaultValue )
   {
      return _SWPSettleESGElig[index] == null ? defaultValue : _SWPSettleESGElig[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicating if intermediary is eligible to settle SWP through FUNDServ fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicating if intermediary is eligible to settle SWP through FUNDServ values.
    */
   public final Boolean[] getSWPSettleESGEligArray()
   {
      return _SWPSettleESGElig;
   }
    
   /**
    * Gets the Flag indicating if intermediary is eligible to settle Cash ID through FUNDServ field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicating if intermediary is eligible to settle Cash ID through FUNDServ or null.
    */
   public final Boolean getCashIDSettleESGElig( int index )
   {
      return _CashIDSettleESGElig[index];
   }
    
   /**
    * Gets the Flag indicating if intermediary is eligible to settle Cash ID through FUNDServ field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if intermediary is eligible to settle Cash ID through FUNDServ or the specified default value.
    */
   public final boolean getCashIDSettleESGElig( int index, boolean defaultValue )
   {
      return _CashIDSettleESGElig[index] == null ? defaultValue : _CashIDSettleESGElig[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicating if intermediary is eligible to settle Cash ID through FUNDServ fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicating if intermediary is eligible to settle Cash ID through FUNDServ values.
    */
   public final Boolean[] getCashIDSettleESGEligArray()
   {
      return _CashIDSettleESGElig;
   }
    
   /**
    * Gets the Non Financial Update field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Non Financial Update or null.
    */
   public final String getNFUpdate( int index )
   {
      return _NFUpdate[index];
   }
    
   /**
    * Gets the Non Financial Update field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Non Financial Update or the specified default value.
    */
   public final String getNFUpdate( int index, String defaultValue )
   {
      return _NFUpdate[index] == null ? defaultValue : _NFUpdate[index];
   }
    
   /**
    * Gets the array of Non Financial Update fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Non Financial Update values.
    */
   public final String[] getNFUpdateArray()
   {
      return _NFUpdate;
   }
    
   /**
    * Gets the KYC Regulation field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the KYC Regulation or null.
    */
   public final String getKYCRegulation( int index )
   {
      return _KYCRegulation[index];
   }
    
   /**
    * Gets the KYC Regulation field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the KYC Regulation or the specified default value.
    */
   public final String getKYCRegulation( int index, String defaultValue )
   {
      return _KYCRegulation[index] == null ? defaultValue : _KYCRegulation[index];
   }
    
   /**
    * Gets the array of KYC Regulation fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of KYC Regulation values.
    */
   public final String[] getKYCRegulationArray()
   {
      return _KYCRegulation;
   }
    
   /**
    * Gets the AML Agreement field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AML Agreement or null.
    */
   public final String getAMLAgreement( int index )
   {
      return _AMLAgreement[index];
   }
    
   /**
    * Gets the AML Agreement field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AML Agreement or the specified default value.
    */
   public final String getAMLAgreement( int index, String defaultValue )
   {
      return _AMLAgreement[index] == null ? defaultValue : _AMLAgreement[index];
   }
    
   /**
    * Gets the array of AML Agreement fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AML Agreement values.
    */
   public final String[] getAMLAgreementArray()
   {
      return _AMLAgreement;
   }
    
   /**
    * Gets the KYC Signture Store Req field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the KYC Signture Store Req or null.
    */
   public final String getKYCSigntureStoreRe( int index )
   {
      return _KYCSigntureStoreRe[index];
   }
    
   /**
    * Gets the KYC Signture Store Req field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the KYC Signture Store Req or the specified default value.
    */
   public final String getKYCSigntureStoreRe( int index, String defaultValue )
   {
      return _KYCSigntureStoreRe[index] == null ? defaultValue : _KYCSigntureStoreRe[index];
   }
    
   /**
    * Gets the array of KYC Signture Store Req fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of KYC Signture Store Req values.
    */
   public final String[] getKYCSigntureStoreReArray()
   {
      return _KYCSigntureStoreRe;
   }
    
   /**
    * Gets the KYC Status field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the KYC Status or null.
    */
   public final String getKYCStatus( int index )
   {
      return _KYCStatus[index];
   }
    
   /**
    * Gets the KYC Status field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the KYC Status or the specified default value.
    */
   public final String getKYCStatus( int index, String defaultValue )
   {
      return _KYCStatus[index] == null ? defaultValue : _KYCStatus[index];
   }
    
   /**
    * Gets the array of KYC Status fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of KYC Status values.
    */
   public final String[] getKYCStatusArray()
   {
      return _KYCStatus;
   }
    
   /**
    * Gets the List of BrokerCategory field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the List of BrokerCategory or null.
    */
   public final String getBrokerCategoryList( int index )
   {
      return _BrokerCategoryList[index];
   }
    
   /**
    * Gets the List of BrokerCategory field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the List of BrokerCategory or the specified default value.
    */
   public final String getBrokerCategoryList( int index, String defaultValue )
   {
      return _BrokerCategoryList[index] == null ? defaultValue : _BrokerCategoryList[index];
   }
    
   /**
    * Gets the array of List of BrokerCategory fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of List of BrokerCategory values.
    */
   public final String[] getBrokerCategoryListArray()
   {
      return _BrokerCategoryList;
   }
    
   /**
    * Gets the Guard Option Client field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Guard Option Client or null.
    */
   public final String getBrokGuardOptClt( int index )
   {
      return _BrokGuardOptClt[index];
   }
    
   /**
    * Gets the Guard Option Client field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Guard Option Client or the specified default value.
    */
   public final String getBrokGuardOptClt( int index, String defaultValue )
   {
      return _BrokGuardOptClt[index] == null ? defaultValue : _BrokGuardOptClt[index];
   }
    
   /**
    * Gets the array of Guard Option Client fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Guard Option Client values.
    */
   public final String[] getBrokGuardOptCltArray()
   {
      return _BrokGuardOptClt;
   }
    
   /**
    * Gets the Guard Option Nominee field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Guard Option Nominee or null.
    */
   public final String getBrokGuardOptNom( int index )
   {
      return _BrokGuardOptNom[index];
   }
    
   /**
    * Gets the Guard Option Nominee field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Guard Option Nominee or the specified default value.
    */
   public final String getBrokGuardOptNom( int index, String defaultValue )
   {
      return _BrokGuardOptNom[index] == null ? defaultValue : _BrokGuardOptNom[index];
   }
    
   /**
    * Gets the array of Guard Option Nominee fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Guard Option Nominee values.
    */
   public final String[] getBrokGuardOptNomArray()
   {
      return _BrokGuardOptNom;
   }
    
   /**
    * Gets the Guard Option Intermediary field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Guard Option Intermediary or null.
    */
   public final String getBrokGuardOptInt( int index )
   {
      return _BrokGuardOptInt[index];
   }
    
   /**
    * Gets the Guard Option Intermediary field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Guard Option Intermediary or the specified default value.
    */
   public final String getBrokGuardOptInt( int index, String defaultValue )
   {
      return _BrokGuardOptInt[index] == null ? defaultValue : _BrokGuardOptInt[index];
   }
    
   /**
    * Gets the array of Guard Option Intermediary fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Guard Option Intermediary values.
    */
   public final String[] getBrokGuardOptIntArray()
   {
      return _BrokGuardOptInt;
   }
    
   /**
    * Gets the Flag that indicates if broker has EPA agreement field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag that indicates if broker has EPA agreement or null.
    */
   public final Boolean getEPABroker( int index )
   {
      return _EPABroker[index];
   }
    
   /**
    * Gets the Flag that indicates if broker has EPA agreement field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag that indicates if broker has EPA agreement or the specified default value.
    */
   public final boolean getEPABroker( int index, boolean defaultValue )
   {
      return _EPABroker[index] == null ? defaultValue : _EPABroker[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag that indicates if broker has EPA agreement fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag that indicates if broker has EPA agreement values.
    */
   public final Boolean[] getEPABrokerArray()
   {
      return _EPABroker;
   }
    
   /**
    * Gets the Flag that indicates if Fund Serv Broker field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag that indicates if Fund Serv Broker or null.
    */
   public final Boolean getFundServBroker( int index )
   {
      return _FundServBroker[index];
   }
    
   /**
    * Gets the Flag that indicates if Fund Serv Broker field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag that indicates if Fund Serv Broker or the specified default value.
    */
   public final boolean getFundServBroker( int index, boolean defaultValue )
   {
      return _FundServBroker[index] == null ? defaultValue : _FundServBroker[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag that indicates if Fund Serv Broker fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag that indicates if Fund Serv Broker values.
    */
   public final Boolean[] getFundServBrokerArray()
   {
      return _FundServBroker;
   }
    
   /**
    * Gets the Compliant Network field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Compliant Network or null.
    */
   public final String getBrokCompliantNW( int index )
   {
      return _BrokCompliantNW[index];
   }
    
   /**
    * Gets the Compliant Network field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Compliant Network or the specified default value.
    */
   public final String getBrokCompliantNW( int index, String defaultValue )
   {
      return _BrokCompliantNW[index] == null ? defaultValue : _BrokCompliantNW[index];
   }
    
   /**
    * Gets the array of Compliant Network fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Compliant Network values.
    */
   public final String[] getBrokCompliantNWArray()
   {
      return _BrokCompliantNW;
   }
    
   /**
    * Gets the CSS Clearing and Settlement field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the CSS Clearing and Settlement or null.
    */
   public final String getBrokCssStatus( int index )
   {
      return _BrokCssStatus[index];
   }
    
   /**
    * Gets the CSS Clearing and Settlement field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the CSS Clearing and Settlement or the specified default value.
    */
   public final String getBrokCssStatus( int index, String defaultValue )
   {
      return _BrokCssStatus[index] == null ? defaultValue : _BrokCssStatus[index];
   }
    
   /**
    * Gets the array of CSS Clearing and Settlement fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of CSS Clearing and Settlement values.
    */
   public final String[] getBrokCssStatusArray()
   {
      return _BrokCssStatus;
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
      
      _rxBrokerCode = resizeArray( _rxBrokerCode, _RepeatCount );
      _BrokerName = resizeArray( _BrokerName, _RepeatCount );
      _BrokerType = resizeArray( _BrokerType, _RepeatCount );
      _BrokerTypeDesc = resizeArray( _BrokerTypeDesc, _RepeatCount );
      _AddrLine1 = resizeArray( _AddrLine1, _RepeatCount );
      _AddrLine2 = resizeArray( _AddrLine2, _RepeatCount );
      _AddrLine3 = resizeArray( _AddrLine3, _RepeatCount );
      _AddrLine4 = resizeArray( _AddrLine4, _RepeatCount );
      _AddrLine5 = resizeArray( _AddrLine5, _RepeatCount );
      _AddrCntryCode = resizeArray( _AddrCntryCode, _RepeatCount );
      _PhoneNumber = resizeArray( _PhoneNumber, _RepeatCount );
      _SettlePurDays = resizeArray( _SettlePurDays, _RepeatCount );
      _SettleRedDays = resizeArray( _SettleRedDays, _RepeatCount );
      _NetAllowed = resizeArray( _NetAllowed, _RepeatCount );
      _FundAllowed = resizeArray( _FundAllowed, _RepeatCount );
      _TaxNominee = resizeArray( _TaxNominee, _RepeatCount );
      _VolSettleType = resizeArray( _VolSettleType, _RepeatCount );
      _EffectiveDate = resizeArray( _EffectiveDate, _RepeatCount );
      _StopDate = resizeArray( _StopDate, _RepeatCount );
      _AddPerm = resizeArray( _AddPerm, _RepeatCount );
      _PayInstrTrailer = resizeArray( _PayInstrTrailer, _RepeatCount );
      _PayInstrComm = resizeArray( _PayInstrComm, _RepeatCount );
      _PostalCode = resizeArray( _PostalCode, _RepeatCount );
      _KYCRequired = resizeArray( _KYCRequired, _RepeatCount );
      _HouseBroker = resizeArray( _HouseBroker, _RepeatCount );
      _NSCCCompliant = resizeArray( _NSCCCompliant, _RepeatCount );
      _FileTypeD = resizeArray( _FileTypeD, _RepeatCount );
      _FileTypeJ = resizeArray( _FileTypeJ, _RepeatCount );
      _MMWire = resizeArray( _MMWire, _RepeatCount );
      _ConfClientNom = resizeArray( _ConfClientNom, _RepeatCount );
      _ConfClientOth = resizeArray( _ConfClientOth, _RepeatCount );
      _ConfClientCli = resizeArray( _ConfClientCli, _RepeatCount );
      _ConfBrkNom = resizeArray( _ConfBrkNom, _RepeatCount );
      _ConfBrkOth = resizeArray( _ConfBrkOth, _RepeatCount );
      _ConfBrkCli = resizeArray( _ConfBrkCli, _RepeatCount );
      _ConfRepNom = resizeArray( _ConfRepNom, _RepeatCount );
      _ConfRepOth = resizeArray( _ConfRepOth, _RepeatCount );
      _ConfRepCli = resizeArray( _ConfRepCli, _RepeatCount );
      _NSCPartId = resizeArray( _NSCPartId, _RepeatCount );
      _RelatedToClrFirm = resizeArray( _RelatedToClrFirm, _RepeatCount );
      _SWPSettleESGElig = resizeArray( _SWPSettleESGElig, _RepeatCount );
      _CashIDSettleESGElig = resizeArray( _CashIDSettleESGElig, _RepeatCount );
      _NFUpdate = resizeArray( _NFUpdate, _RepeatCount );
      _KYCRegulation = resizeArray( _KYCRegulation, _RepeatCount );
      _AMLAgreement = resizeArray( _AMLAgreement, _RepeatCount );
      _KYCSigntureStoreRe = resizeArray( _KYCSigntureStoreRe, _RepeatCount );
      _KYCStatus = resizeArray( _KYCStatus, _RepeatCount );
      _BrokerCategoryList = resizeArray( _BrokerCategoryList, _RepeatCount );
      _BrokGuardOptClt = resizeArray( _BrokGuardOptClt, _RepeatCount );
      _BrokGuardOptNom = resizeArray( _BrokGuardOptNom, _RepeatCount );
      _BrokGuardOptInt = resizeArray( _BrokGuardOptInt, _RepeatCount );
      _EPABroker = resizeArray( _EPABroker, _RepeatCount );
      _FundServBroker = resizeArray( _FundServBroker, _RepeatCount );
      _BrokCompliantNW = resizeArray( _BrokCompliantNW, _RepeatCount );
      _BrokCssStatus = resizeArray( _BrokCssStatus, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxBrokerCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BrokerName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BrokerType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BrokerTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine3[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine4[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine5[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrCntryCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PhoneNumber[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SettlePurDays[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _SettleRedDays[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _NetAllowed[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FundAllowed[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TaxNominee[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _VolSettleType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _StopDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _AddPerm[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _PayInstrTrailer[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _PayInstrComm[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _PostalCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _KYCRequired[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _HouseBroker[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _NSCCCompliant[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FileTypeD[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FileTypeJ[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _MMWire[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ConfClientNom[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ConfClientOth[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ConfClientCli[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ConfBrkNom[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ConfBrkOth[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ConfBrkCli[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ConfRepNom[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ConfRepOth[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ConfRepCli[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _NSCPartId[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RelatedToClrFirm[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _SWPSettleESGElig[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _CashIDSettleESGElig[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _NFUpdate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _KYCRegulation[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AMLAgreement[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _KYCSigntureStoreRe[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _KYCStatus[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BrokerCategoryList[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BrokGuardOptClt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BrokGuardOptNom[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BrokGuardOptInt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EPABroker[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FundServBroker[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _BrokCompliantNW[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BrokCssStatus[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
