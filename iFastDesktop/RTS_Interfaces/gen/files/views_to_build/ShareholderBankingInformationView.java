
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Shareholder/Account Banking Information view.
 * For additional view information see <A HREF="../../../../viewspecs/ShareholderBankingInformation.doc">ShareholderBankingInformation.doc</A>.
 * 
 * @author RTS Generated
 */
public class ShareholderBankingInformationView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Shareholder Number member array.
    */
   private String[] _rxShrNumber = null;
   
   /**
    * Bank Account Usage Code member array.
    */
   private String[] _AcctUseCode = null;
   
   /**
    * Account Usage Description member array.
    */
   private String[] _AcctUseDesc = null;
   
   /**
    * Institution Name member array.
    */
   private String[] _InstName = null;
   
   /**
    * Swift Code member array.
    */
   private Integer[] _SwiftCode = null;
   
   /**
    * Reference Number member array.
    */
   private Integer[] _RefNumber = null;
   
   /**
    * Transit Number member array.
    */
   private Integer[] _TransitNo = null;
   
   /**
    * Bank Account Number member array.
    */
   private String[] _BankAcctNum = null;
   
   /**
    * Bank Accountholder Name member array.
    */
   private String[] _BankAcctName = null;
   
   /**
    * Bank Account Type member array.
    */
   private String[] _BankAcctType = null;
   
   /**
    * Bank Account Type Description member array.
    */
   private String[] _BankAcctTypeDesc = null;
   
   /**
    * Currency member array.
    */
   private String[] _BankAcctCurrency = null;
   
   /**
    * Currency Name member array.
    */
   private String[] _BankCurrDesc = null;
   
   /**
    * Pay Reason1 member array.
    */
   private String[] _PayReason1 = null;
   
   /**
    * Pay Reason2 member array.
    */
   private String[] _PayReason2 = null;
   
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = null;
   
   /**
    * Expire On member array.
    */
   private Date[] _StopDate = null;
   
   /**
    * Modified On member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * Created By member array.
    */
   private String[] _Username = null;
   
   /**
    * Modified By member array.
    */
   private String[] _ModUser = null;
   
   /**
    * Created On member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * Bank-Acct Version Number member array.
    */
   private Integer[] _BankAcctVer = null;
   
   /**
    * Bank-Acct Record Id member array.
    */
   private Integer[] _BankAcctRid = null;
   
   /**
    * Field linking Bank-Acct with Bank-Mstr.  It is a pointer to Correspondent Bank stored in Bank-Mstr Table member array.
    */
   private Integer[] _CorrespBankId = null;
   
   /**
    * Bank Type code to indicate what fields uniquely identify bank member array.
    */
   private String[] _BankType = null;
   
   /**
    * Corresponding Bank Type code to indicate what fields uniquely identify bank member array.
    */
   private String[] _CorrespBankType = null;
   
   /**
    * Bank ID Number member array.
    */
   private String[] _BankIDNum = null;
   
   /**
    * Bank ID number for corresponding Bank member array.
    */
   private String[] _CorrespBankIDNum = null;
   
   /**
    * For further credit instruction 1 member array.
    */
   private String[] _CreditInfoLine1 = null;
   
   /**
    * For further credit instruction 2 member array.
    */
   private String[] _CreditInfoLine2 = null;
   
   /**
    * Code to define processing location member array.
    */
   private String[] _ACHProcessor = null;
   
   /**
    * Bank contact person member array.
    */
   private String[] _CorrespBankContact = null;
   
   /**
    * Bank address country code member array.
    */
   private String[] _CorrespBankCntry = null;
   
   /**
    * Bank address postal code member array.
    */
   private String[] _CorrespBankPstl = null;
   
   /**
    * Corresp Bank Address line 1 member array.
    */
   private String[] _CorrespBankAddr1 = null;
   
   /**
    * Corresp Bank Address line 2 member array.
    */
   private String[] _CorrespBankAddr2 = null;
   
   /**
    * Corresp Bank Address line 3 member array.
    */
   private String[] _CorrespBankAddr3 = null;
   
   /**
    * Corresp Bank Address line 4 member array.
    */
   private String[] _CorrespBankAddr4 = null;
   
   /**
    * Corresp Bank Address line 5 member array.
    */
   private String[] _CorrespBankAddr5 = null;
   
   /**
    * Bank Address line 1 member array.
    */
   private String[] _BankAddr1 = null;
   
   /**
    * Bank Address line 2 member array.
    */
   private String[] _BankAddr2 = null;
   
   /**
    * Bank Address line 3 member array.
    */
   private String[] _BankAddr3 = null;
   
   /**
    * Bank Address line 4 member array.
    */
   private String[] _BankAddr4 = null;
   
   /**
    * Bank Address line 5 member array.
    */
   private String[] _BankAddr5 = null;
   
   /**
    * Bank contract person member array.
    */
   private String[] _BankContact = null;
   
   /**
    * Bank country member array.
    */
   private String[] _BankCntry = null;
   
   /**
    * Bank address postal code member array.
    */
   private String[] _BankPstl = null;
   
   /**
    * Correspondent Bank Name member array.
    */
   private String[] _CorrespInstName = null;
   
   /**
    * Transit Number of the correspondent bank member array.
    */
   private Integer[] _CorrespTransitNo = null;
   
   /**
    * Distrib-Detl record ID member array.
    */
   private Integer[] _DistribDetlRid = null;
   
   /**
    * PAC/SWP/Clan Record ID/AT member array.
    */
   private Integer[] _PACSWPID = null;
   
   /**
    * Link between Bank-Acct and Bank-Mstr  etween member array.
    */
   private Integer[] _BankId = null;
   
   /**
    * Indicates if record is verified member array.
    */
   private String[] _VerifyStat = null;
   
   /**
    * Bank-Acct record identifier member array.
    */
   private String[] _AcctID = null;
   
   /**
    * Flag indicating if has at least one pending or unsettled transaction with the Banking Instructions member array.
    */
   private Boolean[] _TradeExists = null;
   
   /**
    * rxAccountNum member array.
    */
   private String[] _rxAccountNum = null;
   
   /**
    * rxBankingEntity member array.
    */
   private String[] _rxBankingEntity = null;
   

   /**
    * Constructs the ShareholderBankingInformationView object.
    * 
    */
   public ShareholderBankingInformationView()
   {
      super ( new ShareholderBankingInformationRequest() );
   }

   /**
    * Constructs the ShareholderBankingInformationView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public ShareholderBankingInformationView( String hostEncoding )
   {
      super ( new ShareholderBankingInformationRequest( hostEncoding ) );
   }

   /**
    * Gets the ShareholderBankingInformationRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The ShareholderBankingInformationRequest object.
    */
   public final ShareholderBankingInformationRequest getRequest()
   {
      return (ShareholderBankingInformationRequest)getIFastRequest();
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
    * Gets the Shareholder Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Shareholder Number or null.
    */
   public final String getrxShrNumber( int index )
   {
      return _rxShrNumber[index];
   }
    
   /**
    * Gets the Shareholder Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Shareholder Number or the specified default value.
    */
   public final String getrxShrNumber( int index, String defaultValue )
   {
      return _rxShrNumber[index] == null ? defaultValue : _rxShrNumber[index];
   }
    
   /**
    * Gets the array of Shareholder Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Shareholder Number values.
    */
   public final String[] getrxShrNumberArray()
   {
      return _rxShrNumber;
   }
    
   /**
    * Gets the Bank Account Usage Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Account Usage Code or null.
    */
   public final String getAcctUseCode( int index )
   {
      return _AcctUseCode[index];
   }
    
   /**
    * Gets the Bank Account Usage Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Account Usage Code or the specified default value.
    */
   public final String getAcctUseCode( int index, String defaultValue )
   {
      return _AcctUseCode[index] == null ? defaultValue : _AcctUseCode[index];
   }
    
   /**
    * Gets the array of Bank Account Usage Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Account Usage Code values.
    */
   public final String[] getAcctUseCodeArray()
   {
      return _AcctUseCode;
   }
    
   /**
    * Gets the Account Usage Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Usage Description or null.
    */
   public final String getAcctUseDesc( int index )
   {
      return _AcctUseDesc[index];
   }
    
   /**
    * Gets the Account Usage Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Usage Description or the specified default value.
    */
   public final String getAcctUseDesc( int index, String defaultValue )
   {
      return _AcctUseDesc[index] == null ? defaultValue : _AcctUseDesc[index];
   }
    
   /**
    * Gets the array of Account Usage Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Usage Description values.
    */
   public final String[] getAcctUseDescArray()
   {
      return _AcctUseDesc;
   }
    
   /**
    * Gets the Institution Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Institution Name or null.
    */
   public final String getInstName( int index )
   {
      return _InstName[index];
   }
    
   /**
    * Gets the Institution Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Institution Name or the specified default value.
    */
   public final String getInstName( int index, String defaultValue )
   {
      return _InstName[index] == null ? defaultValue : _InstName[index];
   }
    
   /**
    * Gets the array of Institution Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Institution Name values.
    */
   public final String[] getInstNameArray()
   {
      return _InstName;
   }
    
   /**
    * Gets the Swift Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Swift Code or null.
    */
   public final Integer getSwiftCode( int index )
   {
      return _SwiftCode[index];
   }
    
   /**
    * Gets the Swift Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Swift Code or the specified default value.
    */
   public final int getSwiftCode( int index, int defaultValue )
   {
      return _SwiftCode[index] == null ? defaultValue : _SwiftCode[index].intValue();
   }
    
   /**
    * Gets the array of Swift Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Swift Code values.
    */
   public final Integer[] getSwiftCodeArray()
   {
      return _SwiftCode;
   }
    
   /**
    * Gets the Reference Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reference Number or null.
    */
   public final Integer getRefNumber( int index )
   {
      return _RefNumber[index];
   }
    
   /**
    * Gets the Reference Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reference Number or the specified default value.
    */
   public final int getRefNumber( int index, int defaultValue )
   {
      return _RefNumber[index] == null ? defaultValue : _RefNumber[index].intValue();
   }
    
   /**
    * Gets the array of Reference Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reference Number values.
    */
   public final Integer[] getRefNumberArray()
   {
      return _RefNumber;
   }
    
   /**
    * Gets the Transit Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transit Number or null.
    */
   public final Integer getTransitNo( int index )
   {
      return _TransitNo[index];
   }
    
   /**
    * Gets the Transit Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transit Number or the specified default value.
    */
   public final int getTransitNo( int index, int defaultValue )
   {
      return _TransitNo[index] == null ? defaultValue : _TransitNo[index].intValue();
   }
    
   /**
    * Gets the array of Transit Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transit Number values.
    */
   public final Integer[] getTransitNoArray()
   {
      return _TransitNo;
   }
    
   /**
    * Gets the Bank Account Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Account Number or null.
    */
   public final String getBankAcctNum( int index )
   {
      return _BankAcctNum[index];
   }
    
   /**
    * Gets the Bank Account Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Account Number or the specified default value.
    */
   public final String getBankAcctNum( int index, String defaultValue )
   {
      return _BankAcctNum[index] == null ? defaultValue : _BankAcctNum[index];
   }
    
   /**
    * Gets the array of Bank Account Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Account Number values.
    */
   public final String[] getBankAcctNumArray()
   {
      return _BankAcctNum;
   }
    
   /**
    * Gets the Bank Accountholder Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Accountholder Name or null.
    */
   public final String getBankAcctName( int index )
   {
      return _BankAcctName[index];
   }
    
   /**
    * Gets the Bank Accountholder Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Accountholder Name or the specified default value.
    */
   public final String getBankAcctName( int index, String defaultValue )
   {
      return _BankAcctName[index] == null ? defaultValue : _BankAcctName[index];
   }
    
   /**
    * Gets the array of Bank Accountholder Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Accountholder Name values.
    */
   public final String[] getBankAcctNameArray()
   {
      return _BankAcctName;
   }
    
   /**
    * Gets the Bank Account Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Account Type or null.
    */
   public final String getBankAcctType( int index )
   {
      return _BankAcctType[index];
   }
    
   /**
    * Gets the Bank Account Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Account Type or the specified default value.
    */
   public final String getBankAcctType( int index, String defaultValue )
   {
      return _BankAcctType[index] == null ? defaultValue : _BankAcctType[index];
   }
    
   /**
    * Gets the array of Bank Account Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Account Type values.
    */
   public final String[] getBankAcctTypeArray()
   {
      return _BankAcctType;
   }
    
   /**
    * Gets the Bank Account Type Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Account Type Description or null.
    */
   public final String getBankAcctTypeDesc( int index )
   {
      return _BankAcctTypeDesc[index];
   }
    
   /**
    * Gets the Bank Account Type Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Account Type Description or the specified default value.
    */
   public final String getBankAcctTypeDesc( int index, String defaultValue )
   {
      return _BankAcctTypeDesc[index] == null ? defaultValue : _BankAcctTypeDesc[index];
   }
    
   /**
    * Gets the array of Bank Account Type Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Account Type Description values.
    */
   public final String[] getBankAcctTypeDescArray()
   {
      return _BankAcctTypeDesc;
   }
    
   /**
    * Gets the Currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Currency or null.
    */
   public final String getBankAcctCurrency( int index )
   {
      return _BankAcctCurrency[index];
   }
    
   /**
    * Gets the Currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Currency or the specified default value.
    */
   public final String getBankAcctCurrency( int index, String defaultValue )
   {
      return _BankAcctCurrency[index] == null ? defaultValue : _BankAcctCurrency[index];
   }
    
   /**
    * Gets the array of Currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Currency values.
    */
   public final String[] getBankAcctCurrencyArray()
   {
      return _BankAcctCurrency;
   }
    
   /**
    * Gets the Currency Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Currency Name or null.
    */
   public final String getBankCurrDesc( int index )
   {
      return _BankCurrDesc[index];
   }
    
   /**
    * Gets the Currency Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Currency Name or the specified default value.
    */
   public final String getBankCurrDesc( int index, String defaultValue )
   {
      return _BankCurrDesc[index] == null ? defaultValue : _BankCurrDesc[index];
   }
    
   /**
    * Gets the array of Currency Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Currency Name values.
    */
   public final String[] getBankCurrDescArray()
   {
      return _BankCurrDesc;
   }
    
   /**
    * Gets the Pay Reason1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Pay Reason1 or null.
    */
   public final String getPayReason1( int index )
   {
      return _PayReason1[index];
   }
    
   /**
    * Gets the Pay Reason1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pay Reason1 or the specified default value.
    */
   public final String getPayReason1( int index, String defaultValue )
   {
      return _PayReason1[index] == null ? defaultValue : _PayReason1[index];
   }
    
   /**
    * Gets the array of Pay Reason1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Pay Reason1 values.
    */
   public final String[] getPayReason1Array()
   {
      return _PayReason1;
   }
    
   /**
    * Gets the Pay Reason2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Pay Reason2 or null.
    */
   public final String getPayReason2( int index )
   {
      return _PayReason2[index];
   }
    
   /**
    * Gets the Pay Reason2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pay Reason2 or the specified default value.
    */
   public final String getPayReason2( int index, String defaultValue )
   {
      return _PayReason2[index] == null ? defaultValue : _PayReason2[index];
   }
    
   /**
    * Gets the array of Pay Reason2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Pay Reason2 values.
    */
   public final String[] getPayReason2Array()
   {
      return _PayReason2;
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
    * Gets the Expire On field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Expire On or null.
    */
   public final Date getStopDate( int index )
   {
      return _StopDate[index];
   }
    
   /**
    * Gets the Expire On field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Expire On or the specified default value.
    */
   public final Date getStopDate( int index, Date defaultValue )
   {
      return _StopDate[index] == null ? defaultValue : _StopDate[index];
   }
    
   /**
    * Gets the array of Expire On fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Expire On values.
    */
   public final Date[] getStopDateArray()
   {
      return _StopDate;
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
    * Gets the Created By field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Created By or null.
    */
   public final String getUsername( int index )
   {
      return _Username[index];
   }
    
   /**
    * Gets the Created By field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Created By or the specified default value.
    */
   public final String getUsername( int index, String defaultValue )
   {
      return _Username[index] == null ? defaultValue : _Username[index];
   }
    
   /**
    * Gets the array of Created By fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Created By values.
    */
   public final String[] getUsernameArray()
   {
      return _Username;
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
    * Gets the Bank-Acct Version Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank-Acct Version Number or null.
    */
   public final Integer getBankAcctVer( int index )
   {
      return _BankAcctVer[index];
   }
    
   /**
    * Gets the Bank-Acct Version Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank-Acct Version Number or the specified default value.
    */
   public final int getBankAcctVer( int index, int defaultValue )
   {
      return _BankAcctVer[index] == null ? defaultValue : _BankAcctVer[index].intValue();
   }
    
   /**
    * Gets the array of Bank-Acct Version Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank-Acct Version Number values.
    */
   public final Integer[] getBankAcctVerArray()
   {
      return _BankAcctVer;
   }
    
   /**
    * Gets the Bank-Acct Record Id field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank-Acct Record Id or null.
    */
   public final Integer getBankAcctRid( int index )
   {
      return _BankAcctRid[index];
   }
    
   /**
    * Gets the Bank-Acct Record Id field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank-Acct Record Id or the specified default value.
    */
   public final int getBankAcctRid( int index, int defaultValue )
   {
      return _BankAcctRid[index] == null ? defaultValue : _BankAcctRid[index].intValue();
   }
    
   /**
    * Gets the array of Bank-Acct Record Id fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank-Acct Record Id values.
    */
   public final Integer[] getBankAcctRidArray()
   {
      return _BankAcctRid;
   }
    
   /**
    * Gets the Field linking Bank-Acct with Bank-Mstr.  It is a pointer to Correspondent Bank stored in Bank-Mstr Table field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Field linking Bank-Acct with Bank-Mstr.  It is a pointer to Correspondent Bank stored in Bank-Mstr Table or null.
    */
   public final Integer getCorrespBankId( int index )
   {
      return _CorrespBankId[index];
   }
    
   /**
    * Gets the Field linking Bank-Acct with Bank-Mstr.  It is a pointer to Correspondent Bank stored in Bank-Mstr Table field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Field linking Bank-Acct with Bank-Mstr.  It is a pointer to Correspondent Bank stored in Bank-Mstr Table or the specified default value.
    */
   public final int getCorrespBankId( int index, int defaultValue )
   {
      return _CorrespBankId[index] == null ? defaultValue : _CorrespBankId[index].intValue();
   }
    
   /**
    * Gets the array of Field linking Bank-Acct with Bank-Mstr.  It is a pointer to Correspondent Bank stored in Bank-Mstr Table fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Field linking Bank-Acct with Bank-Mstr.  It is a pointer to Correspondent Bank stored in Bank-Mstr Table values.
    */
   public final Integer[] getCorrespBankIdArray()
   {
      return _CorrespBankId;
   }
    
   /**
    * Gets the Bank Type code to indicate what fields uniquely identify bank field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Type code to indicate what fields uniquely identify bank or null.
    */
   public final String getBankType( int index )
   {
      return _BankType[index];
   }
    
   /**
    * Gets the Bank Type code to indicate what fields uniquely identify bank field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Type code to indicate what fields uniquely identify bank or the specified default value.
    */
   public final String getBankType( int index, String defaultValue )
   {
      return _BankType[index] == null ? defaultValue : _BankType[index];
   }
    
   /**
    * Gets the array of Bank Type code to indicate what fields uniquely identify bank fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Type code to indicate what fields uniquely identify bank values.
    */
   public final String[] getBankTypeArray()
   {
      return _BankType;
   }
    
   /**
    * Gets the Corresponding Bank Type code to indicate what fields uniquely identify bank field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Corresponding Bank Type code to indicate what fields uniquely identify bank or null.
    */
   public final String getCorrespBankType( int index )
   {
      return _CorrespBankType[index];
   }
    
   /**
    * Gets the Corresponding Bank Type code to indicate what fields uniquely identify bank field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Corresponding Bank Type code to indicate what fields uniquely identify bank or the specified default value.
    */
   public final String getCorrespBankType( int index, String defaultValue )
   {
      return _CorrespBankType[index] == null ? defaultValue : _CorrespBankType[index];
   }
    
   /**
    * Gets the array of Corresponding Bank Type code to indicate what fields uniquely identify bank fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Corresponding Bank Type code to indicate what fields uniquely identify bank values.
    */
   public final String[] getCorrespBankTypeArray()
   {
      return _CorrespBankType;
   }
    
   /**
    * Gets the Bank ID Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank ID Number or null.
    */
   public final String getBankIDNum( int index )
   {
      return _BankIDNum[index];
   }
    
   /**
    * Gets the Bank ID Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank ID Number or the specified default value.
    */
   public final String getBankIDNum( int index, String defaultValue )
   {
      return _BankIDNum[index] == null ? defaultValue : _BankIDNum[index];
   }
    
   /**
    * Gets the array of Bank ID Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank ID Number values.
    */
   public final String[] getBankIDNumArray()
   {
      return _BankIDNum;
   }
    
   /**
    * Gets the Bank ID number for corresponding Bank field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank ID number for corresponding Bank or null.
    */
   public final String getCorrespBankIDNum( int index )
   {
      return _CorrespBankIDNum[index];
   }
    
   /**
    * Gets the Bank ID number for corresponding Bank field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank ID number for corresponding Bank or the specified default value.
    */
   public final String getCorrespBankIDNum( int index, String defaultValue )
   {
      return _CorrespBankIDNum[index] == null ? defaultValue : _CorrespBankIDNum[index];
   }
    
   /**
    * Gets the array of Bank ID number for corresponding Bank fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank ID number for corresponding Bank values.
    */
   public final String[] getCorrespBankIDNumArray()
   {
      return _CorrespBankIDNum;
   }
    
   /**
    * Gets the For further credit instruction 1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the For further credit instruction 1 or null.
    */
   public final String getCreditInfoLine1( int index )
   {
      return _CreditInfoLine1[index];
   }
    
   /**
    * Gets the For further credit instruction 1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the For further credit instruction 1 or the specified default value.
    */
   public final String getCreditInfoLine1( int index, String defaultValue )
   {
      return _CreditInfoLine1[index] == null ? defaultValue : _CreditInfoLine1[index];
   }
    
   /**
    * Gets the array of For further credit instruction 1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of For further credit instruction 1 values.
    */
   public final String[] getCreditInfoLine1Array()
   {
      return _CreditInfoLine1;
   }
    
   /**
    * Gets the For further credit instruction 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the For further credit instruction 2 or null.
    */
   public final String getCreditInfoLine2( int index )
   {
      return _CreditInfoLine2[index];
   }
    
   /**
    * Gets the For further credit instruction 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the For further credit instruction 2 or the specified default value.
    */
   public final String getCreditInfoLine2( int index, String defaultValue )
   {
      return _CreditInfoLine2[index] == null ? defaultValue : _CreditInfoLine2[index];
   }
    
   /**
    * Gets the array of For further credit instruction 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of For further credit instruction 2 values.
    */
   public final String[] getCreditInfoLine2Array()
   {
      return _CreditInfoLine2;
   }
    
   /**
    * Gets the Code to define processing location field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Code to define processing location or null.
    */
   public final String getACHProcessor( int index )
   {
      return _ACHProcessor[index];
   }
    
   /**
    * Gets the Code to define processing location field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Code to define processing location or the specified default value.
    */
   public final String getACHProcessor( int index, String defaultValue )
   {
      return _ACHProcessor[index] == null ? defaultValue : _ACHProcessor[index];
   }
    
   /**
    * Gets the array of Code to define processing location fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Code to define processing location values.
    */
   public final String[] getACHProcessorArray()
   {
      return _ACHProcessor;
   }
    
   /**
    * Gets the Bank contact person field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank contact person or null.
    */
   public final String getCorrespBankContact( int index )
   {
      return _CorrespBankContact[index];
   }
    
   /**
    * Gets the Bank contact person field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank contact person or the specified default value.
    */
   public final String getCorrespBankContact( int index, String defaultValue )
   {
      return _CorrespBankContact[index] == null ? defaultValue : _CorrespBankContact[index];
   }
    
   /**
    * Gets the array of Bank contact person fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank contact person values.
    */
   public final String[] getCorrespBankContactArray()
   {
      return _CorrespBankContact;
   }
    
   /**
    * Gets the Bank address country code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank address country code or null.
    */
   public final String getCorrespBankCntry( int index )
   {
      return _CorrespBankCntry[index];
   }
    
   /**
    * Gets the Bank address country code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank address country code or the specified default value.
    */
   public final String getCorrespBankCntry( int index, String defaultValue )
   {
      return _CorrespBankCntry[index] == null ? defaultValue : _CorrespBankCntry[index];
   }
    
   /**
    * Gets the array of Bank address country code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank address country code values.
    */
   public final String[] getCorrespBankCntryArray()
   {
      return _CorrespBankCntry;
   }
    
   /**
    * Gets the Bank address postal code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank address postal code or null.
    */
   public final String getCorrespBankPstl( int index )
   {
      return _CorrespBankPstl[index];
   }
    
   /**
    * Gets the Bank address postal code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank address postal code or the specified default value.
    */
   public final String getCorrespBankPstl( int index, String defaultValue )
   {
      return _CorrespBankPstl[index] == null ? defaultValue : _CorrespBankPstl[index];
   }
    
   /**
    * Gets the array of Bank address postal code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank address postal code values.
    */
   public final String[] getCorrespBankPstlArray()
   {
      return _CorrespBankPstl;
   }
    
   /**
    * Gets the Corresp Bank Address line 1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Corresp Bank Address line 1 or null.
    */
   public final String getCorrespBankAddr1( int index )
   {
      return _CorrespBankAddr1[index];
   }
    
   /**
    * Gets the Corresp Bank Address line 1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Corresp Bank Address line 1 or the specified default value.
    */
   public final String getCorrespBankAddr1( int index, String defaultValue )
   {
      return _CorrespBankAddr1[index] == null ? defaultValue : _CorrespBankAddr1[index];
   }
    
   /**
    * Gets the array of Corresp Bank Address line 1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Corresp Bank Address line 1 values.
    */
   public final String[] getCorrespBankAddr1Array()
   {
      return _CorrespBankAddr1;
   }
    
   /**
    * Gets the Corresp Bank Address line 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Corresp Bank Address line 2 or null.
    */
   public final String getCorrespBankAddr2( int index )
   {
      return _CorrespBankAddr2[index];
   }
    
   /**
    * Gets the Corresp Bank Address line 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Corresp Bank Address line 2 or the specified default value.
    */
   public final String getCorrespBankAddr2( int index, String defaultValue )
   {
      return _CorrespBankAddr2[index] == null ? defaultValue : _CorrespBankAddr2[index];
   }
    
   /**
    * Gets the array of Corresp Bank Address line 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Corresp Bank Address line 2 values.
    */
   public final String[] getCorrespBankAddr2Array()
   {
      return _CorrespBankAddr2;
   }
    
   /**
    * Gets the Corresp Bank Address line 3 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Corresp Bank Address line 3 or null.
    */
   public final String getCorrespBankAddr3( int index )
   {
      return _CorrespBankAddr3[index];
   }
    
   /**
    * Gets the Corresp Bank Address line 3 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Corresp Bank Address line 3 or the specified default value.
    */
   public final String getCorrespBankAddr3( int index, String defaultValue )
   {
      return _CorrespBankAddr3[index] == null ? defaultValue : _CorrespBankAddr3[index];
   }
    
   /**
    * Gets the array of Corresp Bank Address line 3 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Corresp Bank Address line 3 values.
    */
   public final String[] getCorrespBankAddr3Array()
   {
      return _CorrespBankAddr3;
   }
    
   /**
    * Gets the Corresp Bank Address line 4 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Corresp Bank Address line 4 or null.
    */
   public final String getCorrespBankAddr4( int index )
   {
      return _CorrespBankAddr4[index];
   }
    
   /**
    * Gets the Corresp Bank Address line 4 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Corresp Bank Address line 4 or the specified default value.
    */
   public final String getCorrespBankAddr4( int index, String defaultValue )
   {
      return _CorrespBankAddr4[index] == null ? defaultValue : _CorrespBankAddr4[index];
   }
    
   /**
    * Gets the array of Corresp Bank Address line 4 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Corresp Bank Address line 4 values.
    */
   public final String[] getCorrespBankAddr4Array()
   {
      return _CorrespBankAddr4;
   }
    
   /**
    * Gets the Corresp Bank Address line 5 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Corresp Bank Address line 5 or null.
    */
   public final String getCorrespBankAddr5( int index )
   {
      return _CorrespBankAddr5[index];
   }
    
   /**
    * Gets the Corresp Bank Address line 5 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Corresp Bank Address line 5 or the specified default value.
    */
   public final String getCorrespBankAddr5( int index, String defaultValue )
   {
      return _CorrespBankAddr5[index] == null ? defaultValue : _CorrespBankAddr5[index];
   }
    
   /**
    * Gets the array of Corresp Bank Address line 5 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Corresp Bank Address line 5 values.
    */
   public final String[] getCorrespBankAddr5Array()
   {
      return _CorrespBankAddr5;
   }
    
   /**
    * Gets the Bank Address line 1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Address line 1 or null.
    */
   public final String getBankAddr1( int index )
   {
      return _BankAddr1[index];
   }
    
   /**
    * Gets the Bank Address line 1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Address line 1 or the specified default value.
    */
   public final String getBankAddr1( int index, String defaultValue )
   {
      return _BankAddr1[index] == null ? defaultValue : _BankAddr1[index];
   }
    
   /**
    * Gets the array of Bank Address line 1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Address line 1 values.
    */
   public final String[] getBankAddr1Array()
   {
      return _BankAddr1;
   }
    
   /**
    * Gets the Bank Address line 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Address line 2 or null.
    */
   public final String getBankAddr2( int index )
   {
      return _BankAddr2[index];
   }
    
   /**
    * Gets the Bank Address line 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Address line 2 or the specified default value.
    */
   public final String getBankAddr2( int index, String defaultValue )
   {
      return _BankAddr2[index] == null ? defaultValue : _BankAddr2[index];
   }
    
   /**
    * Gets the array of Bank Address line 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Address line 2 values.
    */
   public final String[] getBankAddr2Array()
   {
      return _BankAddr2;
   }
    
   /**
    * Gets the Bank Address line 3 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Address line 3 or null.
    */
   public final String getBankAddr3( int index )
   {
      return _BankAddr3[index];
   }
    
   /**
    * Gets the Bank Address line 3 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Address line 3 or the specified default value.
    */
   public final String getBankAddr3( int index, String defaultValue )
   {
      return _BankAddr3[index] == null ? defaultValue : _BankAddr3[index];
   }
    
   /**
    * Gets the array of Bank Address line 3 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Address line 3 values.
    */
   public final String[] getBankAddr3Array()
   {
      return _BankAddr3;
   }
    
   /**
    * Gets the Bank Address line 4 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Address line 4 or null.
    */
   public final String getBankAddr4( int index )
   {
      return _BankAddr4[index];
   }
    
   /**
    * Gets the Bank Address line 4 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Address line 4 or the specified default value.
    */
   public final String getBankAddr4( int index, String defaultValue )
   {
      return _BankAddr4[index] == null ? defaultValue : _BankAddr4[index];
   }
    
   /**
    * Gets the array of Bank Address line 4 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Address line 4 values.
    */
   public final String[] getBankAddr4Array()
   {
      return _BankAddr4;
   }
    
   /**
    * Gets the Bank Address line 5 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Address line 5 or null.
    */
   public final String getBankAddr5( int index )
   {
      return _BankAddr5[index];
   }
    
   /**
    * Gets the Bank Address line 5 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Address line 5 or the specified default value.
    */
   public final String getBankAddr5( int index, String defaultValue )
   {
      return _BankAddr5[index] == null ? defaultValue : _BankAddr5[index];
   }
    
   /**
    * Gets the array of Bank Address line 5 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Address line 5 values.
    */
   public final String[] getBankAddr5Array()
   {
      return _BankAddr5;
   }
    
   /**
    * Gets the Bank contract person field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank contract person or null.
    */
   public final String getBankContact( int index )
   {
      return _BankContact[index];
   }
    
   /**
    * Gets the Bank contract person field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank contract person or the specified default value.
    */
   public final String getBankContact( int index, String defaultValue )
   {
      return _BankContact[index] == null ? defaultValue : _BankContact[index];
   }
    
   /**
    * Gets the array of Bank contract person fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank contract person values.
    */
   public final String[] getBankContactArray()
   {
      return _BankContact;
   }
    
   /**
    * Gets the Bank country field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank country or null.
    */
   public final String getBankCntry( int index )
   {
      return _BankCntry[index];
   }
    
   /**
    * Gets the Bank country field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank country or the specified default value.
    */
   public final String getBankCntry( int index, String defaultValue )
   {
      return _BankCntry[index] == null ? defaultValue : _BankCntry[index];
   }
    
   /**
    * Gets the array of Bank country fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank country values.
    */
   public final String[] getBankCntryArray()
   {
      return _BankCntry;
   }
    
   /**
    * Gets the Bank address postal code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank address postal code or null.
    */
   public final String getBankPstl( int index )
   {
      return _BankPstl[index];
   }
    
   /**
    * Gets the Bank address postal code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank address postal code or the specified default value.
    */
   public final String getBankPstl( int index, String defaultValue )
   {
      return _BankPstl[index] == null ? defaultValue : _BankPstl[index];
   }
    
   /**
    * Gets the array of Bank address postal code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank address postal code values.
    */
   public final String[] getBankPstlArray()
   {
      return _BankPstl;
   }
    
   /**
    * Gets the Correspondent Bank Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Correspondent Bank Name or null.
    */
   public final String getCorrespInstName( int index )
   {
      return _CorrespInstName[index];
   }
    
   /**
    * Gets the Correspondent Bank Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Correspondent Bank Name or the specified default value.
    */
   public final String getCorrespInstName( int index, String defaultValue )
   {
      return _CorrespInstName[index] == null ? defaultValue : _CorrespInstName[index];
   }
    
   /**
    * Gets the array of Correspondent Bank Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Correspondent Bank Name values.
    */
   public final String[] getCorrespInstNameArray()
   {
      return _CorrespInstName;
   }
    
   /**
    * Gets the Transit Number of the correspondent bank field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transit Number of the correspondent bank or null.
    */
   public final Integer getCorrespTransitNo( int index )
   {
      return _CorrespTransitNo[index];
   }
    
   /**
    * Gets the Transit Number of the correspondent bank field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transit Number of the correspondent bank or the specified default value.
    */
   public final int getCorrespTransitNo( int index, int defaultValue )
   {
      return _CorrespTransitNo[index] == null ? defaultValue : _CorrespTransitNo[index].intValue();
   }
    
   /**
    * Gets the array of Transit Number of the correspondent bank fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transit Number of the correspondent bank values.
    */
   public final Integer[] getCorrespTransitNoArray()
   {
      return _CorrespTransitNo;
   }
    
   /**
    * Gets the Distrib-Detl record ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Distrib-Detl record ID or null.
    */
   public final Integer getDistribDetlRid( int index )
   {
      return _DistribDetlRid[index];
   }
    
   /**
    * Gets the Distrib-Detl record ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Distrib-Detl record ID or the specified default value.
    */
   public final int getDistribDetlRid( int index, int defaultValue )
   {
      return _DistribDetlRid[index] == null ? defaultValue : _DistribDetlRid[index].intValue();
   }
    
   /**
    * Gets the array of Distrib-Detl record ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Distrib-Detl record ID values.
    */
   public final Integer[] getDistribDetlRidArray()
   {
      return _DistribDetlRid;
   }
    
   /**
    * Gets the PAC/SWP/Clan Record ID/AT field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the PAC/SWP/Clan Record ID/AT or null.
    */
   public final Integer getPACSWPID( int index )
   {
      return _PACSWPID[index];
   }
    
   /**
    * Gets the PAC/SWP/Clan Record ID/AT field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PAC/SWP/Clan Record ID/AT or the specified default value.
    */
   public final int getPACSWPID( int index, int defaultValue )
   {
      return _PACSWPID[index] == null ? defaultValue : _PACSWPID[index].intValue();
   }
    
   /**
    * Gets the array of PAC/SWP/Clan Record ID/AT fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of PAC/SWP/Clan Record ID/AT values.
    */
   public final Integer[] getPACSWPIDArray()
   {
      return _PACSWPID;
   }
    
   /**
    * Gets the Link between Bank-Acct and Bank-Mstr  etween field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Link between Bank-Acct and Bank-Mstr  etween or null.
    */
   public final Integer getBankId( int index )
   {
      return _BankId[index];
   }
    
   /**
    * Gets the Link between Bank-Acct and Bank-Mstr  etween field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Link between Bank-Acct and Bank-Mstr  etween or the specified default value.
    */
   public final int getBankId( int index, int defaultValue )
   {
      return _BankId[index] == null ? defaultValue : _BankId[index].intValue();
   }
    
   /**
    * Gets the array of Link between Bank-Acct and Bank-Mstr  etween fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Link between Bank-Acct and Bank-Mstr  etween values.
    */
   public final Integer[] getBankIdArray()
   {
      return _BankId;
   }
    
   /**
    * Gets the Indicates if record is verified field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Indicates if record is verified or null.
    */
   public final String getVerifyStat( int index )
   {
      return _VerifyStat[index];
   }
    
   /**
    * Gets the Indicates if record is verified field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Indicates if record is verified or the specified default value.
    */
   public final String getVerifyStat( int index, String defaultValue )
   {
      return _VerifyStat[index] == null ? defaultValue : _VerifyStat[index];
   }
    
   /**
    * Gets the array of Indicates if record is verified fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Indicates if record is verified values.
    */
   public final String[] getVerifyStatArray()
   {
      return _VerifyStat;
   }
    
   /**
    * Gets the Bank-Acct record identifier field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank-Acct record identifier or null.
    */
   public final String getAcctID( int index )
   {
      return _AcctID[index];
   }
    
   /**
    * Gets the Bank-Acct record identifier field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank-Acct record identifier or the specified default value.
    */
   public final String getAcctID( int index, String defaultValue )
   {
      return _AcctID[index] == null ? defaultValue : _AcctID[index];
   }
    
   /**
    * Gets the array of Bank-Acct record identifier fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank-Acct record identifier values.
    */
   public final String[] getAcctIDArray()
   {
      return _AcctID;
   }
    
   /**
    * Gets the Flag indicating if has at least one pending or unsettled transaction with the Banking Instructions field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicating if has at least one pending or unsettled transaction with the Banking Instructions or null.
    */
   public final Boolean getTradeExists( int index )
   {
      return _TradeExists[index];
   }
    
   /**
    * Gets the Flag indicating if has at least one pending or unsettled transaction with the Banking Instructions field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if has at least one pending or unsettled transaction with the Banking Instructions or the specified default value.
    */
   public final boolean getTradeExists( int index, boolean defaultValue )
   {
      return _TradeExists[index] == null ? defaultValue : _TradeExists[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicating if has at least one pending or unsettled transaction with the Banking Instructions fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicating if has at least one pending or unsettled transaction with the Banking Instructions values.
    */
   public final Boolean[] getTradeExistsArray()
   {
      return _TradeExists;
   }
    
   /**
    * Gets the rxAccountNum field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the rxAccountNum or null.
    */
   public final String getrxAccountNum( int index )
   {
      return _rxAccountNum[index];
   }
    
   /**
    * Gets the rxAccountNum field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the rxAccountNum or the specified default value.
    */
   public final String getrxAccountNum( int index, String defaultValue )
   {
      return _rxAccountNum[index] == null ? defaultValue : _rxAccountNum[index];
   }
    
   /**
    * Gets the array of rxAccountNum fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of rxAccountNum values.
    */
   public final String[] getrxAccountNumArray()
   {
      return _rxAccountNum;
   }
    
   /**
    * Gets the rxBankingEntity field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the rxBankingEntity or null.
    */
   public final String getrxBankingEntity( int index )
   {
      return _rxBankingEntity[index];
   }
    
   /**
    * Gets the rxBankingEntity field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the rxBankingEntity or the specified default value.
    */
   public final String getrxBankingEntity( int index, String defaultValue )
   {
      return _rxBankingEntity[index] == null ? defaultValue : _rxBankingEntity[index];
   }
    
   /**
    * Gets the array of rxBankingEntity fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of rxBankingEntity values.
    */
   public final String[] getrxBankingEntityArray()
   {
      return _rxBankingEntity;
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
      
      _rxShrNumber = resizeArray( _rxShrNumber, _RepeatCount );
      _AcctUseCode = resizeArray( _AcctUseCode, _RepeatCount );
      _AcctUseDesc = resizeArray( _AcctUseDesc, _RepeatCount );
      _InstName = resizeArray( _InstName, _RepeatCount );
      _SwiftCode = resizeArray( _SwiftCode, _RepeatCount );
      _RefNumber = resizeArray( _RefNumber, _RepeatCount );
      _TransitNo = resizeArray( _TransitNo, _RepeatCount );
      _BankAcctNum = resizeArray( _BankAcctNum, _RepeatCount );
      _BankAcctName = resizeArray( _BankAcctName, _RepeatCount );
      _BankAcctType = resizeArray( _BankAcctType, _RepeatCount );
      _BankAcctTypeDesc = resizeArray( _BankAcctTypeDesc, _RepeatCount );
      _BankAcctCurrency = resizeArray( _BankAcctCurrency, _RepeatCount );
      _BankCurrDesc = resizeArray( _BankCurrDesc, _RepeatCount );
      _PayReason1 = resizeArray( _PayReason1, _RepeatCount );
      _PayReason2 = resizeArray( _PayReason2, _RepeatCount );
      _EffectiveDate = resizeArray( _EffectiveDate, _RepeatCount );
      _StopDate = resizeArray( _StopDate, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _Username = resizeArray( _Username, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _BankAcctVer = resizeArray( _BankAcctVer, _RepeatCount );
      _BankAcctRid = resizeArray( _BankAcctRid, _RepeatCount );
      _CorrespBankId = resizeArray( _CorrespBankId, _RepeatCount );
      _BankType = resizeArray( _BankType, _RepeatCount );
      _CorrespBankType = resizeArray( _CorrespBankType, _RepeatCount );
      _BankIDNum = resizeArray( _BankIDNum, _RepeatCount );
      _CorrespBankIDNum = resizeArray( _CorrespBankIDNum, _RepeatCount );
      _CreditInfoLine1 = resizeArray( _CreditInfoLine1, _RepeatCount );
      _CreditInfoLine2 = resizeArray( _CreditInfoLine2, _RepeatCount );
      _ACHProcessor = resizeArray( _ACHProcessor, _RepeatCount );
      _CorrespBankContact = resizeArray( _CorrespBankContact, _RepeatCount );
      _CorrespBankCntry = resizeArray( _CorrespBankCntry, _RepeatCount );
      _CorrespBankPstl = resizeArray( _CorrespBankPstl, _RepeatCount );
      _CorrespBankAddr1 = resizeArray( _CorrespBankAddr1, _RepeatCount );
      _CorrespBankAddr2 = resizeArray( _CorrespBankAddr2, _RepeatCount );
      _CorrespBankAddr3 = resizeArray( _CorrespBankAddr3, _RepeatCount );
      _CorrespBankAddr4 = resizeArray( _CorrespBankAddr4, _RepeatCount );
      _CorrespBankAddr5 = resizeArray( _CorrespBankAddr5, _RepeatCount );
      _BankAddr1 = resizeArray( _BankAddr1, _RepeatCount );
      _BankAddr2 = resizeArray( _BankAddr2, _RepeatCount );
      _BankAddr3 = resizeArray( _BankAddr3, _RepeatCount );
      _BankAddr4 = resizeArray( _BankAddr4, _RepeatCount );
      _BankAddr5 = resizeArray( _BankAddr5, _RepeatCount );
      _BankContact = resizeArray( _BankContact, _RepeatCount );
      _BankCntry = resizeArray( _BankCntry, _RepeatCount );
      _BankPstl = resizeArray( _BankPstl, _RepeatCount );
      _CorrespInstName = resizeArray( _CorrespInstName, _RepeatCount );
      _CorrespTransitNo = resizeArray( _CorrespTransitNo, _RepeatCount );
      _DistribDetlRid = resizeArray( _DistribDetlRid, _RepeatCount );
      _PACSWPID = resizeArray( _PACSWPID, _RepeatCount );
      _BankId = resizeArray( _BankId, _RepeatCount );
      _VerifyStat = resizeArray( _VerifyStat, _RepeatCount );
      _AcctID = resizeArray( _AcctID, _RepeatCount );
      _TradeExists = resizeArray( _TradeExists, _RepeatCount );
      _rxAccountNum = resizeArray( _rxAccountNum, _RepeatCount );
      _rxBankingEntity = resizeArray( _rxBankingEntity, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxShrNumber[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctUseCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctUseDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _InstName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SwiftCode[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _RefNumber[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _TransitNo[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _BankAcctNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAcctName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAcctType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAcctTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAcctCurrency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankCurrDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PayReason1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PayReason2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _StopDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _Username[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _BankAcctVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _BankAcctRid[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _CorrespBankId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _BankType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespBankType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankIDNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespBankIDNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CreditInfoLine1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CreditInfoLine2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ACHProcessor[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespBankContact[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespBankCntry[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespBankPstl[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespBankAddr1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespBankAddr2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespBankAddr3[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespBankAddr4[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespBankAddr5[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAddr1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAddr2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAddr3[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAddr4[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAddr5[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankContact[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankCntry[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankPstl[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespInstName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespTransitNo[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _DistribDetlRid[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _PACSWPID[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _BankId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _VerifyStat[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TradeExists[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _rxAccountNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxBankingEntity[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
