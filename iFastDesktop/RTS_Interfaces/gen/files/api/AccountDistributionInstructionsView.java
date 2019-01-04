
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Account distribution instructions view.
 * For additional view information see <A HREF="../../../../viewspecs/AccountDistributionInstructions.doc">AccountDistributionInstructions.doc</A>.
 * 
 * @author RTS Generated
 */
public class AccountDistributionInstructionsView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * FundCode member array.
    */
   private String[] _FundCode = null;
   
   /**
    * ClassCode member array.
    */
   private String[] _ClassCode = null;
   
   /**
    * EffectiveFrom member array.
    */
   private Date[] _EffectiveDate = null;
   
   /**
    * FundToCode member array.
    */
   private String[] _FundToCode = null;
   
   /**
    * ClassToCode member array.
    */
   private String[] _ClassToCode = null;
   
   /**
    * AllocPercent member array.
    */
   private String[] _AllocPercent = null;
   
   /**
    * Record Creation Date member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * Created by User ID member array.
    */
   private String[] _Username = null;
   
   /**
    * PayType member array.
    */
   private String[] _PayType = null;
   
   /**
    * Pay type description member array.
    */
   private String[] _PayTypeDesc = null;
   
   /**
    * Currency member array.
    */
   private String[] _Currency = null;
   
   /**
    * Currency Name member array.
    */
   private String[] _CurrencyName = null;
   
   /**
    * Institution Code member array.
    */
   private Integer[] _InstCode = null;
   
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
    * Bank Account member array.
    */
   private String[] _BankAcctNum = null;
   
   /**
    * Bank Account Name member array.
    */
   private String[] _BankAcctName = null;
   
   /**
    * Pay Reason 1 member array.
    */
   private String[] _PayReason1 = null;
   
   /**
    * Bank Account Type member array.
    */
   private String[] _BankAcctType = null;
   
   /**
    * Bank Account Type Description member array.
    */
   private String[] _BankAcctTypeDesc = null;
   
   /**
    * Institution Name member array.
    */
   private String[] _InstName = null;
   
   /**
    * Bank-Detl VersionNum member array.
    */
   private Integer[] _BankDetlVer = null;
   
   /**
    * Bank-Detl Record Id member array.
    */
   private Integer[] _BankDetlRid = null;
   
   /**
    * Distrib-Detl VersionNum member array.
    */
   private Integer[] _DistribDetlVer = null;
   
   /**
    * Distrib-Detl Record Id member array.
    */
   private Integer[] _DistribDetlRid = null;
   
   /**
    * Distrib-Detl UserName2 member array.
    */
   private String[] _ModUser = null;
   
   /**
    * Distrib-Detl ModDate member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * Trans Type member array.
    */
   private String[] _TransType = null;
   
   /**
    * Trans Type Desc member array.
    */
   private String[] _TransTypeDesc = null;
   
   /**
    * Corresp Bank Id member array.
    */
   private Integer[] _CorrespBankId = null;
   
   /**
    * Bank Type member array.
    */
   private String[] _BankType = null;
   
   /**
    * Corresp Bank Type member array.
    */
   private String[] _CorrespBankType = null;
   
   /**
    * Bank Id Number member array.
    */
   private String[] _BankIdNum = null;
   
   /**
    * Correp Bank Id Number member array.
    */
   private String[] _CorrespBankIdNum = null;
   
   /**
    * Credit Info Line 1 member array.
    */
   private String[] _CreditInfoLine1 = null;
   
   /**
    * Credit Info Line 2 member array.
    */
   private String[] _CreditInfoLine2 = null;
   
   /**
    * ACH Processor member array.
    */
   private String[] _ACHProcessor = null;
   
   /**
    * Corresp Bank Contact member array.
    */
   private String[] _CorrespBankContact = null;
   
   /**
    * Corresp Bank Cntry member array.
    */
   private String[] _CorrespBankCntry = null;
   
   /**
    * Corresp Bank Pstl member array.
    */
   private String[] _CorrespBankPstl = null;
   
   /**
    * Corresp Bank Addr 1 member array.
    */
   private String[] _CorrespBankAddr1 = null;
   
   /**
    * Corresp Bank Addr 2 member array.
    */
   private String[] _CorrespBankAddr2 = null;
   
   /**
    * Corresp Bank Addr 3 member array.
    */
   private String[] _CorrespBankAddr3 = null;
   
   /**
    * Corresp Bank Addr 4 member array.
    */
   private String[] _CorrespBankAddr4 = null;
   
   /**
    * Corresp Bank Addr 5 member array.
    */
   private String[] _CorrespBankAddr5 = null;
   
   /**
    * Bank Addr 1 member array.
    */
   private String[] _BankAddr1 = null;
   
   /**
    * Bank Addr 2 member array.
    */
   private String[] _BankAddr2 = null;
   
   /**
    * Bank Addr 3 member array.
    */
   private String[] _BankAddr3 = null;
   
   /**
    * Bank Addr 4 member array.
    */
   private String[] _BankAddr4 = null;
   
   /**
    * Bank Addr 5 member array.
    */
   private String[] _BankAddr5 = null;
   
   /**
    * Bank Contact member array.
    */
   private String[] _BankContact = null;
   
   /**
    * Bank Postal member array.
    */
   private String[] _BankPstl = null;
   
   /**
    * Corresp Transit No member array.
    */
   private Integer[] _CorrespTransitNo = null;
   
   /**
    * Corresp Inst Name member array.
    */
   private String[] _CorrespInstName = null;
   
   /**
    * Bank Id member array.
    */
   private Integer[] _BankId = null;
   
   /**
    * Bank Country member array.
    */
   private String[] _BankCntry = null;
   
   /**
    * Address code member array.
    */
   private String[] _AddrCode = null;
   
   /**
    * Pay Method member array.
    */
   private String[] _PayMethod = null;
   
   /**
    * Payment Reason 2 member array.
    */
   private String[] _PayReason2 = null;
   
   /**
    * Distribution Option member array.
    */
   private String[] _DistribOpt = null;
   
   /**
    * Currency Option member array.
    */
   private String[] _CurrOption = null;
   
   /**
    * GBCD of Distrib-Detl member array.
    */
   private Boolean[] _DistribGBCD = null;
   
   /**
    * Verify Status member array.
    */
   private String[] _VerifyStat = null;
   
   /**
    * Distribution Rate member array.
    */
   private String[] _DistribRate = null;
   

   /**
    * Constructs the AccountDistributionInstructionsView object.
    * 
    */
   public AccountDistributionInstructionsView()
   {
      super ( new AccountDistributionInstructionsRequest() );
   }

   /**
    * Constructs the AccountDistributionInstructionsView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AccountDistributionInstructionsView( String hostEncoding )
   {
      super ( new AccountDistributionInstructionsRequest( hostEncoding ) );
   }

   /**
    * Gets the AccountDistributionInstructionsRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AccountDistributionInstructionsRequest object.
    */
   public final AccountDistributionInstructionsRequest getRequest()
   {
      return (AccountDistributionInstructionsRequest)getIFastRequest();
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
    * Gets the FundCode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FundCode or null.
    */
   public final String getFundCode( int index )
   {
      return _FundCode[index];
   }
    
   /**
    * Gets the FundCode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FundCode or the specified default value.
    */
   public final String getFundCode( int index, String defaultValue )
   {
      return _FundCode[index] == null ? defaultValue : _FundCode[index];
   }
    
   /**
    * Gets the array of FundCode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FundCode values.
    */
   public final String[] getFundCodeArray()
   {
      return _FundCode;
   }
    
   /**
    * Gets the ClassCode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ClassCode or null.
    */
   public final String getClassCode( int index )
   {
      return _ClassCode[index];
   }
    
   /**
    * Gets the ClassCode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ClassCode or the specified default value.
    */
   public final String getClassCode( int index, String defaultValue )
   {
      return _ClassCode[index] == null ? defaultValue : _ClassCode[index];
   }
    
   /**
    * Gets the array of ClassCode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ClassCode values.
    */
   public final String[] getClassCodeArray()
   {
      return _ClassCode;
   }
    
   /**
    * Gets the EffectiveFrom field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the EffectiveFrom or null.
    */
   public final Date getEffectiveDate( int index )
   {
      return _EffectiveDate[index];
   }
    
   /**
    * Gets the EffectiveFrom field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the EffectiveFrom or the specified default value.
    */
   public final Date getEffectiveDate( int index, Date defaultValue )
   {
      return _EffectiveDate[index] == null ? defaultValue : _EffectiveDate[index];
   }
    
   /**
    * Gets the array of EffectiveFrom fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of EffectiveFrom values.
    */
   public final Date[] getEffectiveDateArray()
   {
      return _EffectiveDate;
   }
    
   /**
    * Gets the FundToCode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FundToCode or null.
    */
   public final String getFundToCode( int index )
   {
      return _FundToCode[index];
   }
    
   /**
    * Gets the FundToCode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FundToCode or the specified default value.
    */
   public final String getFundToCode( int index, String defaultValue )
   {
      return _FundToCode[index] == null ? defaultValue : _FundToCode[index];
   }
    
   /**
    * Gets the array of FundToCode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FundToCode values.
    */
   public final String[] getFundToCodeArray()
   {
      return _FundToCode;
   }
    
   /**
    * Gets the ClassToCode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ClassToCode or null.
    */
   public final String getClassToCode( int index )
   {
      return _ClassToCode[index];
   }
    
   /**
    * Gets the ClassToCode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ClassToCode or the specified default value.
    */
   public final String getClassToCode( int index, String defaultValue )
   {
      return _ClassToCode[index] == null ? defaultValue : _ClassToCode[index];
   }
    
   /**
    * Gets the array of ClassToCode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ClassToCode values.
    */
   public final String[] getClassToCodeArray()
   {
      return _ClassToCode;
   }
    
   /**
    * Gets the AllocPercent field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AllocPercent or null.
    */
   public final String getAllocPercent( int index )
   {
      return _AllocPercent[index];
   }
    
   /**
    * Gets the AllocPercent field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AllocPercent or the specified default value.
    */
   public final String getAllocPercent( int index, String defaultValue )
   {
      return _AllocPercent[index] == null ? defaultValue : _AllocPercent[index];
   }
    
   /**
    * Gets the array of AllocPercent fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AllocPercent values.
    */
   public final String[] getAllocPercentArray()
   {
      return _AllocPercent;
   }
    
   /**
    * Gets the Record Creation Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Record Creation Date or null.
    */
   public final Date getProcessDate( int index )
   {
      return _ProcessDate[index];
   }
    
   /**
    * Gets the Record Creation Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Record Creation Date or the specified default value.
    */
   public final Date getProcessDate( int index, Date defaultValue )
   {
      return _ProcessDate[index] == null ? defaultValue : _ProcessDate[index];
   }
    
   /**
    * Gets the array of Record Creation Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Record Creation Date values.
    */
   public final Date[] getProcessDateArray()
   {
      return _ProcessDate;
   }
    
   /**
    * Gets the Created by User ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Created by User ID or null.
    */
   public final String getUsername( int index )
   {
      return _Username[index];
   }
    
   /**
    * Gets the Created by User ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Created by User ID or the specified default value.
    */
   public final String getUsername( int index, String defaultValue )
   {
      return _Username[index] == null ? defaultValue : _Username[index];
   }
    
   /**
    * Gets the array of Created by User ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Created by User ID values.
    */
   public final String[] getUsernameArray()
   {
      return _Username;
   }
    
   /**
    * Gets the PayType field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the PayType or null.
    */
   public final String getPayType( int index )
   {
      return _PayType[index];
   }
    
   /**
    * Gets the PayType field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PayType or the specified default value.
    */
   public final String getPayType( int index, String defaultValue )
   {
      return _PayType[index] == null ? defaultValue : _PayType[index];
   }
    
   /**
    * Gets the array of PayType fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of PayType values.
    */
   public final String[] getPayTypeArray()
   {
      return _PayType;
   }
    
   /**
    * Gets the Pay type description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Pay type description or null.
    */
   public final String getPayTypeDesc( int index )
   {
      return _PayTypeDesc[index];
   }
    
   /**
    * Gets the Pay type description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pay type description or the specified default value.
    */
   public final String getPayTypeDesc( int index, String defaultValue )
   {
      return _PayTypeDesc[index] == null ? defaultValue : _PayTypeDesc[index];
   }
    
   /**
    * Gets the array of Pay type description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Pay type description values.
    */
   public final String[] getPayTypeDescArray()
   {
      return _PayTypeDesc;
   }
    
   /**
    * Gets the Currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Currency or null.
    */
   public final String getCurrency( int index )
   {
      return _Currency[index];
   }
    
   /**
    * Gets the Currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Currency or the specified default value.
    */
   public final String getCurrency( int index, String defaultValue )
   {
      return _Currency[index] == null ? defaultValue : _Currency[index];
   }
    
   /**
    * Gets the array of Currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Currency values.
    */
   public final String[] getCurrencyArray()
   {
      return _Currency;
   }
    
   /**
    * Gets the Currency Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Currency Name or null.
    */
   public final String getCurrencyName( int index )
   {
      return _CurrencyName[index];
   }
    
   /**
    * Gets the Currency Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Currency Name or the specified default value.
    */
   public final String getCurrencyName( int index, String defaultValue )
   {
      return _CurrencyName[index] == null ? defaultValue : _CurrencyName[index];
   }
    
   /**
    * Gets the array of Currency Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Currency Name values.
    */
   public final String[] getCurrencyNameArray()
   {
      return _CurrencyName;
   }
    
   /**
    * Gets the Institution Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Institution Code or null.
    */
   public final Integer getInstCode( int index )
   {
      return _InstCode[index];
   }
    
   /**
    * Gets the Institution Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Institution Code or the specified default value.
    */
   public final int getInstCode( int index, int defaultValue )
   {
      return _InstCode[index] == null ? defaultValue : _InstCode[index].intValue();
   }
    
   /**
    * Gets the array of Institution Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Institution Code values.
    */
   public final Integer[] getInstCodeArray()
   {
      return _InstCode;
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
    * Gets the Bank Account field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Account or null.
    */
   public final String getBankAcctNum( int index )
   {
      return _BankAcctNum[index];
   }
    
   /**
    * Gets the Bank Account field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Account or the specified default value.
    */
   public final String getBankAcctNum( int index, String defaultValue )
   {
      return _BankAcctNum[index] == null ? defaultValue : _BankAcctNum[index];
   }
    
   /**
    * Gets the array of Bank Account fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Account values.
    */
   public final String[] getBankAcctNumArray()
   {
      return _BankAcctNum;
   }
    
   /**
    * Gets the Bank Account Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Account Name or null.
    */
   public final String getBankAcctName( int index )
   {
      return _BankAcctName[index];
   }
    
   /**
    * Gets the Bank Account Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Account Name or the specified default value.
    */
   public final String getBankAcctName( int index, String defaultValue )
   {
      return _BankAcctName[index] == null ? defaultValue : _BankAcctName[index];
   }
    
   /**
    * Gets the array of Bank Account Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Account Name values.
    */
   public final String[] getBankAcctNameArray()
   {
      return _BankAcctName;
   }
    
   /**
    * Gets the Pay Reason 1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Pay Reason 1 or null.
    */
   public final String getPayReason1( int index )
   {
      return _PayReason1[index];
   }
    
   /**
    * Gets the Pay Reason 1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pay Reason 1 or the specified default value.
    */
   public final String getPayReason1( int index, String defaultValue )
   {
      return _PayReason1[index] == null ? defaultValue : _PayReason1[index];
   }
    
   /**
    * Gets the array of Pay Reason 1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Pay Reason 1 values.
    */
   public final String[] getPayReason1Array()
   {
      return _PayReason1;
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
    * Gets the Bank-Detl VersionNum field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank-Detl VersionNum or null.
    */
   public final Integer getBankDetlVer( int index )
   {
      return _BankDetlVer[index];
   }
    
   /**
    * Gets the Bank-Detl VersionNum field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank-Detl VersionNum or the specified default value.
    */
   public final int getBankDetlVer( int index, int defaultValue )
   {
      return _BankDetlVer[index] == null ? defaultValue : _BankDetlVer[index].intValue();
   }
    
   /**
    * Gets the array of Bank-Detl VersionNum fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank-Detl VersionNum values.
    */
   public final Integer[] getBankDetlVerArray()
   {
      return _BankDetlVer;
   }
    
   /**
    * Gets the Bank-Detl Record Id field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank-Detl Record Id or null.
    */
   public final Integer getBankDetlRid( int index )
   {
      return _BankDetlRid[index];
   }
    
   /**
    * Gets the Bank-Detl Record Id field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank-Detl Record Id or the specified default value.
    */
   public final int getBankDetlRid( int index, int defaultValue )
   {
      return _BankDetlRid[index] == null ? defaultValue : _BankDetlRid[index].intValue();
   }
    
   /**
    * Gets the array of Bank-Detl Record Id fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank-Detl Record Id values.
    */
   public final Integer[] getBankDetlRidArray()
   {
      return _BankDetlRid;
   }
    
   /**
    * Gets the Distrib-Detl VersionNum field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Distrib-Detl VersionNum or null.
    */
   public final Integer getDistribDetlVer( int index )
   {
      return _DistribDetlVer[index];
   }
    
   /**
    * Gets the Distrib-Detl VersionNum field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Distrib-Detl VersionNum or the specified default value.
    */
   public final int getDistribDetlVer( int index, int defaultValue )
   {
      return _DistribDetlVer[index] == null ? defaultValue : _DistribDetlVer[index].intValue();
   }
    
   /**
    * Gets the array of Distrib-Detl VersionNum fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Distrib-Detl VersionNum values.
    */
   public final Integer[] getDistribDetlVerArray()
   {
      return _DistribDetlVer;
   }
    
   /**
    * Gets the Distrib-Detl Record Id field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Distrib-Detl Record Id or null.
    */
   public final Integer getDistribDetlRid( int index )
   {
      return _DistribDetlRid[index];
   }
    
   /**
    * Gets the Distrib-Detl Record Id field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Distrib-Detl Record Id or the specified default value.
    */
   public final int getDistribDetlRid( int index, int defaultValue )
   {
      return _DistribDetlRid[index] == null ? defaultValue : _DistribDetlRid[index].intValue();
   }
    
   /**
    * Gets the array of Distrib-Detl Record Id fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Distrib-Detl Record Id values.
    */
   public final Integer[] getDistribDetlRidArray()
   {
      return _DistribDetlRid;
   }
    
   /**
    * Gets the Distrib-Detl UserName2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Distrib-Detl UserName2 or null.
    */
   public final String getModUser( int index )
   {
      return _ModUser[index];
   }
    
   /**
    * Gets the Distrib-Detl UserName2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Distrib-Detl UserName2 or the specified default value.
    */
   public final String getModUser( int index, String defaultValue )
   {
      return _ModUser[index] == null ? defaultValue : _ModUser[index];
   }
    
   /**
    * Gets the array of Distrib-Detl UserName2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Distrib-Detl UserName2 values.
    */
   public final String[] getModUserArray()
   {
      return _ModUser;
   }
    
   /**
    * Gets the Distrib-Detl ModDate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Distrib-Detl ModDate or null.
    */
   public final Date getModDate( int index )
   {
      return _ModDate[index];
   }
    
   /**
    * Gets the Distrib-Detl ModDate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Distrib-Detl ModDate or the specified default value.
    */
   public final Date getModDate( int index, Date defaultValue )
   {
      return _ModDate[index] == null ? defaultValue : _ModDate[index];
   }
    
   /**
    * Gets the array of Distrib-Detl ModDate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Distrib-Detl ModDate values.
    */
   public final Date[] getModDateArray()
   {
      return _ModDate;
   }
    
   /**
    * Gets the Trans Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Trans Type or null.
    */
   public final String getTransType( int index )
   {
      return _TransType[index];
   }
    
   /**
    * Gets the Trans Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Trans Type or the specified default value.
    */
   public final String getTransType( int index, String defaultValue )
   {
      return _TransType[index] == null ? defaultValue : _TransType[index];
   }
    
   /**
    * Gets the array of Trans Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Trans Type values.
    */
   public final String[] getTransTypeArray()
   {
      return _TransType;
   }
    
   /**
    * Gets the Trans Type Desc field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Trans Type Desc or null.
    */
   public final String getTransTypeDesc( int index )
   {
      return _TransTypeDesc[index];
   }
    
   /**
    * Gets the Trans Type Desc field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Trans Type Desc or the specified default value.
    */
   public final String getTransTypeDesc( int index, String defaultValue )
   {
      return _TransTypeDesc[index] == null ? defaultValue : _TransTypeDesc[index];
   }
    
   /**
    * Gets the array of Trans Type Desc fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Trans Type Desc values.
    */
   public final String[] getTransTypeDescArray()
   {
      return _TransTypeDesc;
   }
    
   /**
    * Gets the Corresp Bank Id field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Corresp Bank Id or null.
    */
   public final Integer getCorrespBankId( int index )
   {
      return _CorrespBankId[index];
   }
    
   /**
    * Gets the Corresp Bank Id field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Corresp Bank Id or the specified default value.
    */
   public final int getCorrespBankId( int index, int defaultValue )
   {
      return _CorrespBankId[index] == null ? defaultValue : _CorrespBankId[index].intValue();
   }
    
   /**
    * Gets the array of Corresp Bank Id fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Corresp Bank Id values.
    */
   public final Integer[] getCorrespBankIdArray()
   {
      return _CorrespBankId;
   }
    
   /**
    * Gets the Bank Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Type or null.
    */
   public final String getBankType( int index )
   {
      return _BankType[index];
   }
    
   /**
    * Gets the Bank Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Type or the specified default value.
    */
   public final String getBankType( int index, String defaultValue )
   {
      return _BankType[index] == null ? defaultValue : _BankType[index];
   }
    
   /**
    * Gets the array of Bank Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Type values.
    */
   public final String[] getBankTypeArray()
   {
      return _BankType;
   }
    
   /**
    * Gets the Corresp Bank Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Corresp Bank Type or null.
    */
   public final String getCorrespBankType( int index )
   {
      return _CorrespBankType[index];
   }
    
   /**
    * Gets the Corresp Bank Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Corresp Bank Type or the specified default value.
    */
   public final String getCorrespBankType( int index, String defaultValue )
   {
      return _CorrespBankType[index] == null ? defaultValue : _CorrespBankType[index];
   }
    
   /**
    * Gets the array of Corresp Bank Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Corresp Bank Type values.
    */
   public final String[] getCorrespBankTypeArray()
   {
      return _CorrespBankType;
   }
    
   /**
    * Gets the Bank Id Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Id Number or null.
    */
   public final String getBankIdNum( int index )
   {
      return _BankIdNum[index];
   }
    
   /**
    * Gets the Bank Id Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Id Number or the specified default value.
    */
   public final String getBankIdNum( int index, String defaultValue )
   {
      return _BankIdNum[index] == null ? defaultValue : _BankIdNum[index];
   }
    
   /**
    * Gets the array of Bank Id Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Id Number values.
    */
   public final String[] getBankIdNumArray()
   {
      return _BankIdNum;
   }
    
   /**
    * Gets the Correp Bank Id Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Correp Bank Id Number or null.
    */
   public final String getCorrespBankIdNum( int index )
   {
      return _CorrespBankIdNum[index];
   }
    
   /**
    * Gets the Correp Bank Id Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Correp Bank Id Number or the specified default value.
    */
   public final String getCorrespBankIdNum( int index, String defaultValue )
   {
      return _CorrespBankIdNum[index] == null ? defaultValue : _CorrespBankIdNum[index];
   }
    
   /**
    * Gets the array of Correp Bank Id Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Correp Bank Id Number values.
    */
   public final String[] getCorrespBankIdNumArray()
   {
      return _CorrespBankIdNum;
   }
    
   /**
    * Gets the Credit Info Line 1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Credit Info Line 1 or null.
    */
   public final String getCreditInfoLine1( int index )
   {
      return _CreditInfoLine1[index];
   }
    
   /**
    * Gets the Credit Info Line 1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Credit Info Line 1 or the specified default value.
    */
   public final String getCreditInfoLine1( int index, String defaultValue )
   {
      return _CreditInfoLine1[index] == null ? defaultValue : _CreditInfoLine1[index];
   }
    
   /**
    * Gets the array of Credit Info Line 1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Credit Info Line 1 values.
    */
   public final String[] getCreditInfoLine1Array()
   {
      return _CreditInfoLine1;
   }
    
   /**
    * Gets the Credit Info Line 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Credit Info Line 2 or null.
    */
   public final String getCreditInfoLine2( int index )
   {
      return _CreditInfoLine2[index];
   }
    
   /**
    * Gets the Credit Info Line 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Credit Info Line 2 or the specified default value.
    */
   public final String getCreditInfoLine2( int index, String defaultValue )
   {
      return _CreditInfoLine2[index] == null ? defaultValue : _CreditInfoLine2[index];
   }
    
   /**
    * Gets the array of Credit Info Line 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Credit Info Line 2 values.
    */
   public final String[] getCreditInfoLine2Array()
   {
      return _CreditInfoLine2;
   }
    
   /**
    * Gets the ACH Processor field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ACH Processor or null.
    */
   public final String getACHProcessor( int index )
   {
      return _ACHProcessor[index];
   }
    
   /**
    * Gets the ACH Processor field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ACH Processor or the specified default value.
    */
   public final String getACHProcessor( int index, String defaultValue )
   {
      return _ACHProcessor[index] == null ? defaultValue : _ACHProcessor[index];
   }
    
   /**
    * Gets the array of ACH Processor fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ACH Processor values.
    */
   public final String[] getACHProcessorArray()
   {
      return _ACHProcessor;
   }
    
   /**
    * Gets the Corresp Bank Contact field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Corresp Bank Contact or null.
    */
   public final String getCorrespBankContact( int index )
   {
      return _CorrespBankContact[index];
   }
    
   /**
    * Gets the Corresp Bank Contact field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Corresp Bank Contact or the specified default value.
    */
   public final String getCorrespBankContact( int index, String defaultValue )
   {
      return _CorrespBankContact[index] == null ? defaultValue : _CorrespBankContact[index];
   }
    
   /**
    * Gets the array of Corresp Bank Contact fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Corresp Bank Contact values.
    */
   public final String[] getCorrespBankContactArray()
   {
      return _CorrespBankContact;
   }
    
   /**
    * Gets the Corresp Bank Cntry field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Corresp Bank Cntry or null.
    */
   public final String getCorrespBankCntry( int index )
   {
      return _CorrespBankCntry[index];
   }
    
   /**
    * Gets the Corresp Bank Cntry field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Corresp Bank Cntry or the specified default value.
    */
   public final String getCorrespBankCntry( int index, String defaultValue )
   {
      return _CorrespBankCntry[index] == null ? defaultValue : _CorrespBankCntry[index];
   }
    
   /**
    * Gets the array of Corresp Bank Cntry fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Corresp Bank Cntry values.
    */
   public final String[] getCorrespBankCntryArray()
   {
      return _CorrespBankCntry;
   }
    
   /**
    * Gets the Corresp Bank Pstl field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Corresp Bank Pstl or null.
    */
   public final String getCorrespBankPstl( int index )
   {
      return _CorrespBankPstl[index];
   }
    
   /**
    * Gets the Corresp Bank Pstl field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Corresp Bank Pstl or the specified default value.
    */
   public final String getCorrespBankPstl( int index, String defaultValue )
   {
      return _CorrespBankPstl[index] == null ? defaultValue : _CorrespBankPstl[index];
   }
    
   /**
    * Gets the array of Corresp Bank Pstl fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Corresp Bank Pstl values.
    */
   public final String[] getCorrespBankPstlArray()
   {
      return _CorrespBankPstl;
   }
    
   /**
    * Gets the Corresp Bank Addr 1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Corresp Bank Addr 1 or null.
    */
   public final String getCorrespBankAddr1( int index )
   {
      return _CorrespBankAddr1[index];
   }
    
   /**
    * Gets the Corresp Bank Addr 1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Corresp Bank Addr 1 or the specified default value.
    */
   public final String getCorrespBankAddr1( int index, String defaultValue )
   {
      return _CorrespBankAddr1[index] == null ? defaultValue : _CorrespBankAddr1[index];
   }
    
   /**
    * Gets the array of Corresp Bank Addr 1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Corresp Bank Addr 1 values.
    */
   public final String[] getCorrespBankAddr1Array()
   {
      return _CorrespBankAddr1;
   }
    
   /**
    * Gets the Corresp Bank Addr 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Corresp Bank Addr 2 or null.
    */
   public final String getCorrespBankAddr2( int index )
   {
      return _CorrespBankAddr2[index];
   }
    
   /**
    * Gets the Corresp Bank Addr 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Corresp Bank Addr 2 or the specified default value.
    */
   public final String getCorrespBankAddr2( int index, String defaultValue )
   {
      return _CorrespBankAddr2[index] == null ? defaultValue : _CorrespBankAddr2[index];
   }
    
   /**
    * Gets the array of Corresp Bank Addr 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Corresp Bank Addr 2 values.
    */
   public final String[] getCorrespBankAddr2Array()
   {
      return _CorrespBankAddr2;
   }
    
   /**
    * Gets the Corresp Bank Addr 3 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Corresp Bank Addr 3 or null.
    */
   public final String getCorrespBankAddr3( int index )
   {
      return _CorrespBankAddr3[index];
   }
    
   /**
    * Gets the Corresp Bank Addr 3 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Corresp Bank Addr 3 or the specified default value.
    */
   public final String getCorrespBankAddr3( int index, String defaultValue )
   {
      return _CorrespBankAddr3[index] == null ? defaultValue : _CorrespBankAddr3[index];
   }
    
   /**
    * Gets the array of Corresp Bank Addr 3 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Corresp Bank Addr 3 values.
    */
   public final String[] getCorrespBankAddr3Array()
   {
      return _CorrespBankAddr3;
   }
    
   /**
    * Gets the Corresp Bank Addr 4 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Corresp Bank Addr 4 or null.
    */
   public final String getCorrespBankAddr4( int index )
   {
      return _CorrespBankAddr4[index];
   }
    
   /**
    * Gets the Corresp Bank Addr 4 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Corresp Bank Addr 4 or the specified default value.
    */
   public final String getCorrespBankAddr4( int index, String defaultValue )
   {
      return _CorrespBankAddr4[index] == null ? defaultValue : _CorrespBankAddr4[index];
   }
    
   /**
    * Gets the array of Corresp Bank Addr 4 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Corresp Bank Addr 4 values.
    */
   public final String[] getCorrespBankAddr4Array()
   {
      return _CorrespBankAddr4;
   }
    
   /**
    * Gets the Corresp Bank Addr 5 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Corresp Bank Addr 5 or null.
    */
   public final String getCorrespBankAddr5( int index )
   {
      return _CorrespBankAddr5[index];
   }
    
   /**
    * Gets the Corresp Bank Addr 5 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Corresp Bank Addr 5 or the specified default value.
    */
   public final String getCorrespBankAddr5( int index, String defaultValue )
   {
      return _CorrespBankAddr5[index] == null ? defaultValue : _CorrespBankAddr5[index];
   }
    
   /**
    * Gets the array of Corresp Bank Addr 5 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Corresp Bank Addr 5 values.
    */
   public final String[] getCorrespBankAddr5Array()
   {
      return _CorrespBankAddr5;
   }
    
   /**
    * Gets the Bank Addr 1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Addr 1 or null.
    */
   public final String getBankAddr1( int index )
   {
      return _BankAddr1[index];
   }
    
   /**
    * Gets the Bank Addr 1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Addr 1 or the specified default value.
    */
   public final String getBankAddr1( int index, String defaultValue )
   {
      return _BankAddr1[index] == null ? defaultValue : _BankAddr1[index];
   }
    
   /**
    * Gets the array of Bank Addr 1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Addr 1 values.
    */
   public final String[] getBankAddr1Array()
   {
      return _BankAddr1;
   }
    
   /**
    * Gets the Bank Addr 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Addr 2 or null.
    */
   public final String getBankAddr2( int index )
   {
      return _BankAddr2[index];
   }
    
   /**
    * Gets the Bank Addr 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Addr 2 or the specified default value.
    */
   public final String getBankAddr2( int index, String defaultValue )
   {
      return _BankAddr2[index] == null ? defaultValue : _BankAddr2[index];
   }
    
   /**
    * Gets the array of Bank Addr 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Addr 2 values.
    */
   public final String[] getBankAddr2Array()
   {
      return _BankAddr2;
   }
    
   /**
    * Gets the Bank Addr 3 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Addr 3 or null.
    */
   public final String getBankAddr3( int index )
   {
      return _BankAddr3[index];
   }
    
   /**
    * Gets the Bank Addr 3 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Addr 3 or the specified default value.
    */
   public final String getBankAddr3( int index, String defaultValue )
   {
      return _BankAddr3[index] == null ? defaultValue : _BankAddr3[index];
   }
    
   /**
    * Gets the array of Bank Addr 3 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Addr 3 values.
    */
   public final String[] getBankAddr3Array()
   {
      return _BankAddr3;
   }
    
   /**
    * Gets the Bank Addr 4 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Addr 4 or null.
    */
   public final String getBankAddr4( int index )
   {
      return _BankAddr4[index];
   }
    
   /**
    * Gets the Bank Addr 4 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Addr 4 or the specified default value.
    */
   public final String getBankAddr4( int index, String defaultValue )
   {
      return _BankAddr4[index] == null ? defaultValue : _BankAddr4[index];
   }
    
   /**
    * Gets the array of Bank Addr 4 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Addr 4 values.
    */
   public final String[] getBankAddr4Array()
   {
      return _BankAddr4;
   }
    
   /**
    * Gets the Bank Addr 5 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Addr 5 or null.
    */
   public final String getBankAddr5( int index )
   {
      return _BankAddr5[index];
   }
    
   /**
    * Gets the Bank Addr 5 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Addr 5 or the specified default value.
    */
   public final String getBankAddr5( int index, String defaultValue )
   {
      return _BankAddr5[index] == null ? defaultValue : _BankAddr5[index];
   }
    
   /**
    * Gets the array of Bank Addr 5 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Addr 5 values.
    */
   public final String[] getBankAddr5Array()
   {
      return _BankAddr5;
   }
    
   /**
    * Gets the Bank Contact field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Contact or null.
    */
   public final String getBankContact( int index )
   {
      return _BankContact[index];
   }
    
   /**
    * Gets the Bank Contact field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Contact or the specified default value.
    */
   public final String getBankContact( int index, String defaultValue )
   {
      return _BankContact[index] == null ? defaultValue : _BankContact[index];
   }
    
   /**
    * Gets the array of Bank Contact fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Contact values.
    */
   public final String[] getBankContactArray()
   {
      return _BankContact;
   }
    
   /**
    * Gets the Bank Postal field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Postal or null.
    */
   public final String getBankPstl( int index )
   {
      return _BankPstl[index];
   }
    
   /**
    * Gets the Bank Postal field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Postal or the specified default value.
    */
   public final String getBankPstl( int index, String defaultValue )
   {
      return _BankPstl[index] == null ? defaultValue : _BankPstl[index];
   }
    
   /**
    * Gets the array of Bank Postal fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Postal values.
    */
   public final String[] getBankPstlArray()
   {
      return _BankPstl;
   }
    
   /**
    * Gets the Corresp Transit No field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Corresp Transit No or null.
    */
   public final Integer getCorrespTransitNo( int index )
   {
      return _CorrespTransitNo[index];
   }
    
   /**
    * Gets the Corresp Transit No field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Corresp Transit No or the specified default value.
    */
   public final int getCorrespTransitNo( int index, int defaultValue )
   {
      return _CorrespTransitNo[index] == null ? defaultValue : _CorrespTransitNo[index].intValue();
   }
    
   /**
    * Gets the array of Corresp Transit No fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Corresp Transit No values.
    */
   public final Integer[] getCorrespTransitNoArray()
   {
      return _CorrespTransitNo;
   }
    
   /**
    * Gets the Corresp Inst Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Corresp Inst Name or null.
    */
   public final String getCorrespInstName( int index )
   {
      return _CorrespInstName[index];
   }
    
   /**
    * Gets the Corresp Inst Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Corresp Inst Name or the specified default value.
    */
   public final String getCorrespInstName( int index, String defaultValue )
   {
      return _CorrespInstName[index] == null ? defaultValue : _CorrespInstName[index];
   }
    
   /**
    * Gets the array of Corresp Inst Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Corresp Inst Name values.
    */
   public final String[] getCorrespInstNameArray()
   {
      return _CorrespInstName;
   }
    
   /**
    * Gets the Bank Id field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Id or null.
    */
   public final Integer getBankId( int index )
   {
      return _BankId[index];
   }
    
   /**
    * Gets the Bank Id field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Id or the specified default value.
    */
   public final int getBankId( int index, int defaultValue )
   {
      return _BankId[index] == null ? defaultValue : _BankId[index].intValue();
   }
    
   /**
    * Gets the array of Bank Id fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Id values.
    */
   public final Integer[] getBankIdArray()
   {
      return _BankId;
   }
    
   /**
    * Gets the Bank Country field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Country or null.
    */
   public final String getBankCntry( int index )
   {
      return _BankCntry[index];
   }
    
   /**
    * Gets the Bank Country field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Country or the specified default value.
    */
   public final String getBankCntry( int index, String defaultValue )
   {
      return _BankCntry[index] == null ? defaultValue : _BankCntry[index];
   }
    
   /**
    * Gets the array of Bank Country fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Country values.
    */
   public final String[] getBankCntryArray()
   {
      return _BankCntry;
   }
    
   /**
    * Gets the Address code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address code or null.
    */
   public final String getAddrCode( int index )
   {
      return _AddrCode[index];
   }
    
   /**
    * Gets the Address code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address code or the specified default value.
    */
   public final String getAddrCode( int index, String defaultValue )
   {
      return _AddrCode[index] == null ? defaultValue : _AddrCode[index];
   }
    
   /**
    * Gets the array of Address code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address code values.
    */
   public final String[] getAddrCodeArray()
   {
      return _AddrCode;
   }
    
   /**
    * Gets the Pay Method field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Pay Method or null.
    */
   public final String getPayMethod( int index )
   {
      return _PayMethod[index];
   }
    
   /**
    * Gets the Pay Method field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pay Method or the specified default value.
    */
   public final String getPayMethod( int index, String defaultValue )
   {
      return _PayMethod[index] == null ? defaultValue : _PayMethod[index];
   }
    
   /**
    * Gets the array of Pay Method fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Pay Method values.
    */
   public final String[] getPayMethodArray()
   {
      return _PayMethod;
   }
    
   /**
    * Gets the Payment Reason 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Payment Reason 2 or null.
    */
   public final String getPayReason2( int index )
   {
      return _PayReason2[index];
   }
    
   /**
    * Gets the Payment Reason 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payment Reason 2 or the specified default value.
    */
   public final String getPayReason2( int index, String defaultValue )
   {
      return _PayReason2[index] == null ? defaultValue : _PayReason2[index];
   }
    
   /**
    * Gets the array of Payment Reason 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Payment Reason 2 values.
    */
   public final String[] getPayReason2Array()
   {
      return _PayReason2;
   }
    
   /**
    * Gets the Distribution Option field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Distribution Option or null.
    */
   public final String getDistribOpt( int index )
   {
      return _DistribOpt[index];
   }
    
   /**
    * Gets the Distribution Option field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Distribution Option or the specified default value.
    */
   public final String getDistribOpt( int index, String defaultValue )
   {
      return _DistribOpt[index] == null ? defaultValue : _DistribOpt[index];
   }
    
   /**
    * Gets the array of Distribution Option fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Distribution Option values.
    */
   public final String[] getDistribOptArray()
   {
      return _DistribOpt;
   }
    
   /**
    * Gets the Currency Option field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Currency Option or null.
    */
   public final String getCurrOption( int index )
   {
      return _CurrOption[index];
   }
    
   /**
    * Gets the Currency Option field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Currency Option or the specified default value.
    */
   public final String getCurrOption( int index, String defaultValue )
   {
      return _CurrOption[index] == null ? defaultValue : _CurrOption[index];
   }
    
   /**
    * Gets the array of Currency Option fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Currency Option values.
    */
   public final String[] getCurrOptionArray()
   {
      return _CurrOption;
   }
    
   /**
    * Gets the GBCD of Distrib-Detl field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the GBCD of Distrib-Detl or null.
    */
   public final Boolean getDistribGBCD( int index )
   {
      return _DistribGBCD[index];
   }
    
   /**
    * Gets the GBCD of Distrib-Detl field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the GBCD of Distrib-Detl or the specified default value.
    */
   public final boolean getDistribGBCD( int index, boolean defaultValue )
   {
      return _DistribGBCD[index] == null ? defaultValue : _DistribGBCD[index].booleanValue();
   }
    
   /**
    * Gets the array of GBCD of Distrib-Detl fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of GBCD of Distrib-Detl values.
    */
   public final Boolean[] getDistribGBCDArray()
   {
      return _DistribGBCD;
   }
    
   /**
    * Gets the Verify Status field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Verify Status or null.
    */
   public final String getVerifyStat( int index )
   {
      return _VerifyStat[index];
   }
    
   /**
    * Gets the Verify Status field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Verify Status or the specified default value.
    */
   public final String getVerifyStat( int index, String defaultValue )
   {
      return _VerifyStat[index] == null ? defaultValue : _VerifyStat[index];
   }
    
   /**
    * Gets the array of Verify Status fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Verify Status values.
    */
   public final String[] getVerifyStatArray()
   {
      return _VerifyStat;
   }
    
   /**
    * Gets the Distribution Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Distribution Rate or null.
    */
   public final String getDistribRate( int index )
   {
      return _DistribRate[index];
   }
    
   /**
    * Gets the Distribution Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Distribution Rate or the specified default value.
    */
   public final String getDistribRate( int index, String defaultValue )
   {
      return _DistribRate[index] == null ? defaultValue : _DistribRate[index];
   }
    
   /**
    * Gets the array of Distribution Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Distribution Rate values.
    */
   public final String[] getDistribRateArray()
   {
      return _DistribRate;
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
      
      _FundCode = resizeArray( _FundCode, _RepeatCount );
      _ClassCode = resizeArray( _ClassCode, _RepeatCount );
      _EffectiveDate = resizeArray( _EffectiveDate, _RepeatCount );
      _FundToCode = resizeArray( _FundToCode, _RepeatCount );
      _ClassToCode = resizeArray( _ClassToCode, _RepeatCount );
      _AllocPercent = resizeArray( _AllocPercent, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _Username = resizeArray( _Username, _RepeatCount );
      _PayType = resizeArray( _PayType, _RepeatCount );
      _PayTypeDesc = resizeArray( _PayTypeDesc, _RepeatCount );
      _Currency = resizeArray( _Currency, _RepeatCount );
      _CurrencyName = resizeArray( _CurrencyName, _RepeatCount );
      _InstCode = resizeArray( _InstCode, _RepeatCount );
      _SwiftCode = resizeArray( _SwiftCode, _RepeatCount );
      _RefNumber = resizeArray( _RefNumber, _RepeatCount );
      _TransitNo = resizeArray( _TransitNo, _RepeatCount );
      _BankAcctNum = resizeArray( _BankAcctNum, _RepeatCount );
      _BankAcctName = resizeArray( _BankAcctName, _RepeatCount );
      _PayReason1 = resizeArray( _PayReason1, _RepeatCount );
      _BankAcctType = resizeArray( _BankAcctType, _RepeatCount );
      _BankAcctTypeDesc = resizeArray( _BankAcctTypeDesc, _RepeatCount );
      _InstName = resizeArray( _InstName, _RepeatCount );
      _BankDetlVer = resizeArray( _BankDetlVer, _RepeatCount );
      _BankDetlRid = resizeArray( _BankDetlRid, _RepeatCount );
      _DistribDetlVer = resizeArray( _DistribDetlVer, _RepeatCount );
      _DistribDetlRid = resizeArray( _DistribDetlRid, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _TransType = resizeArray( _TransType, _RepeatCount );
      _TransTypeDesc = resizeArray( _TransTypeDesc, _RepeatCount );
      _CorrespBankId = resizeArray( _CorrespBankId, _RepeatCount );
      _BankType = resizeArray( _BankType, _RepeatCount );
      _CorrespBankType = resizeArray( _CorrespBankType, _RepeatCount );
      _BankIdNum = resizeArray( _BankIdNum, _RepeatCount );
      _CorrespBankIdNum = resizeArray( _CorrespBankIdNum, _RepeatCount );
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
      _BankPstl = resizeArray( _BankPstl, _RepeatCount );
      _CorrespTransitNo = resizeArray( _CorrespTransitNo, _RepeatCount );
      _CorrespInstName = resizeArray( _CorrespInstName, _RepeatCount );
      _BankId = resizeArray( _BankId, _RepeatCount );
      _BankCntry = resizeArray( _BankCntry, _RepeatCount );
      _AddrCode = resizeArray( _AddrCode, _RepeatCount );
      _PayMethod = resizeArray( _PayMethod, _RepeatCount );
      _PayReason2 = resizeArray( _PayReason2, _RepeatCount );
      _DistribOpt = resizeArray( _DistribOpt, _RepeatCount );
      _CurrOption = resizeArray( _CurrOption, _RepeatCount );
      _DistribGBCD = resizeArray( _DistribGBCD, _RepeatCount );
      _VerifyStat = resizeArray( _VerifyStat, _RepeatCount );
      _DistribRate = resizeArray( _DistribRate, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _FundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _FundToCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClassToCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AllocPercent[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _Username[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PayType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PayTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Currency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CurrencyName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _InstCode[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _SwiftCode[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _RefNumber[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _TransitNo[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _BankAcctNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAcctName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PayReason1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAcctType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAcctTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _InstName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankDetlVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _BankDetlRid[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _DistribDetlVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _DistribDetlRid[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _TransType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TransTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespBankId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _BankType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespBankType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankIdNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespBankIdNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
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
         _BankPstl[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespTransitNo[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _CorrespInstName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _BankCntry[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PayMethod[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PayReason2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DistribOpt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CurrOption[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DistribGBCD[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _VerifyStat[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DistribRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
