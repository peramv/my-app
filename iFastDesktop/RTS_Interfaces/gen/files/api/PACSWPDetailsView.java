
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Account PAC/SWP/AT details view.
 * For additional view information see <A HREF="../../../../viewspecs/PACSWPDetails.doc">PACSWPDetails.doc</A>.
 * 
 * @author RTS Generated
 */
public class PACSWPDetailsView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Broker Code member array.
    */
   private String[] _BrokerCode = null;
   
   /**
    * Branch Code member array.
    */
   private String[] _BranchCode = null;
   
   /**
    * SalesRep Code member array.
    */
   private String[] _SalesrepCode = null;
   
   /**
    * Broker's Name member array.
    */
   private String[] _BrokerName = null;
   
   /**
    * Branch's Name member array.
    */
   private String[] _BranchName = null;
   
   /**
    * Slsrep's Name member array.
    */
   private String[] _SlsrepName = null;
   
   /**
    * Amount to debit member array.
    */
   private String[] _Amount = null;
   
   /**
    * Amount Type Code member array.
    */
   private String[] _AmountType = null;
   
   /**
    * Amount type description member array.
    */
   private String[] _AmountTypeDesc = null;
   
   /**
    * Amount is expressed as Gross or Net member array.
    */
   private Boolean[] _GrossOrNet = null;
   
   /**
    * Flat amount or percent fee member array.
    */
   private String[] _Fee = null;
   
   /**
    * Percentage to charge as a fee member array.
    */
   private Boolean[] _FlatPercent = null;
   
   /**
    * Fee currency member array.
    */
   private String[] _FeeCurrency = null;
   
   /**
    * Fee Currency Description member array.
    */
   private String[] _FeeCurrDesc = null;
   
   /**
    * Adminstration Fee member array.
    */
   private String[] _AdminFeeAmt = null;
   
   /**
    * Admin fee currency member array.
    */
   private String[] _AdminFeeCurr = null;
   
   /**
    * Admin Fee Currency Name member array.
    */
   private String[] _AdminFeeCurrDesc = null;
   
   /**
    * Payment type code member array.
    */
   private String[] _PayType = null;
   
   /**
    * Pay type description member array.
    */
   private String[] _PayTypeDesc = null;
   
   /**
    * Instution code to debit member array.
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
    * Transit code member array.
    */
   private Integer[] _TransitNo = null;
   
   /**
    * Bank account to debit member array.
    */
   private String[] _BankAcctNum = null;
   
   /**
    * Name of the bank account member array.
    */
   private String[] _BankAcctName = null;
   
   /**
    * Source of the bank account member array.
    */
   private String[] _SourceOfBankAcct = null;
   
   /**
    * Currency of the bank account member array.
    */
   private String[] _BankAcctCurrency = null;
   
   /**
    * Bank Account Currency Description member array.
    */
   private String[] _BankCurrDesc = null;
   
   /**
    * Bank Acount Type member array.
    */
   private String[] _BankAcctType = null;
   
   /**
    * Bank Account Type Description member array.
    */
   private String[] _BankAcctTypeDesc = null;
   
   /**
    * Source of Fund member array.
    */
   private String[] _SrcOfFund = null;
   
   /**
    * Source of Fund Description member array.
    */
   private String[] _SrcOFFundDesc = null;
   
   /**
    * January member array.
    */
   private Boolean[] _January = null;
   
   /**
    * February member array.
    */
   private Boolean[] _February = null;
   
   /**
    * March member array.
    */
   private Boolean[] _March = null;
   
   /**
    * April member array.
    */
   private Boolean[] _April = null;
   
   /**
    * May member array.
    */
   private Boolean[] _May = null;
   
   /**
    * June member array.
    */
   private Boolean[] _June = null;
   
   /**
    * July member array.
    */
   private Boolean[] _July = null;
   
   /**
    * August member array.
    */
   private Boolean[] _August = null;
   
   /**
    * September member array.
    */
   private Boolean[] _September = null;
   
   /**
    * October member array.
    */
   private Boolean[] _October = null;
   
   /**
    * November member array.
    */
   private Boolean[] _November = null;
   
   /**
    * December member array.
    */
   private Boolean[] _December = null;
   
   /**
    * PAC/SWP occurs at end of month member array.
    */
   private Boolean[] _EndOfMonth = null;
   
   /**
    * Day of Week PAC occurs on member array.
    */
   private Integer[] _DayOfWeek = null;
   
   /**
    * Last Process Date member array.
    */
   private Date[] _LastProcessDate = null;
   
   /**
    * Address Code member array.
    */
   private String[] _AddrCode = null;
   
   /**
    * Record Active member array.
    */
   private Boolean[] _GoodBad = null;
   
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = null;
   
   /**
    * Created On member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * Modification Date member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * Stop Date member array.
    */
   private Date[] _StopDate = null;
   
   /**
    * Created by member array.
    */
   private String[] _Username = null;
   
   /**
    * Modified by member array.
    */
   private String[] _ModUser = null;
   
   /**
    * Address Line1 member array.
    */
   private String[] _AddrLine1 = null;
   
   /**
    * Address Line2 member array.
    */
   private String[] _AddrLine2 = null;
   
   /**
    * Address Line3 member array.
    */
   private String[] _AddrLine3 = null;
   
   /**
    * Address Line4 member array.
    */
   private String[] _AddrLine4 = null;
   
   /**
    * Address Line5 member array.
    */
   private String[] _AddrLine5 = null;
   
   /**
    * Postal Code member array.
    */
   private String[] _PostalCode = null;
   
   /**
    * Institution Name member array.
    */
   private String[] _InstName = null;
   
   /**
    * Salesrep Alternate Name member array.
    */
   private String[] _SlsrepAltName = null;
   
   /**
    * Fund Code member array.
    */
   private String[] _FundCode = null;
   
   /**
    * Class Code member array.
    */
   private String[] _ClassCode = null;
   
   /**
    * PAC/SWP Record ID member array.
    */
   private Integer[] _PACSWPId = null;
   
   /**
    * Transacion Type member array.
    */
   private String[] _TransType = null;
   
   /**
    * Bank-Detl/Recur-Detail Version member array.
    */
   private Integer[] _VersionNum = null;
   
   /**
    * Pay Reason 1 member array.
    */
   private String[] _PayReason1 = null;
   
   /**
    * Transfer To Fund member array.
    */
   private String[] _FundToCode = null;
   
   /**
    * Transfer To Class member array.
    */
   private String[] _ClassToCode = null;
   
   /**
    * Transfer To Account member array.
    */
   private String[] _AccountTo = null;
   
   /**
    * Back End Load Fee Applicable member array.
    */
   private Boolean[] _BELFee = null;
   
   /**
    * Batch User member array.
    */
   private String[] _BatchUser = null;
   
   /**
    * Batch Name member array.
    */
   private String[] _Batch = null;
   
   /**
    * Batch Trace member array.
    */
   private Integer[] _BatchTrace = null;
   
   /**
    * Batch Date member array.
    */
   private Date[] _BatchDate = null;
   
   /**
    * Transfer Type member array.
    */
   private String[] _TransferType = null;
   
   /**
    * Frequency Code member array.
    */
   private String[] _Frequency = null;
   
   /**
    * Flat Percent Description member array.
    */
   private String[] _FlatPercentDesc = null;
   
   /**
    * Frequency Type Description member array.
    */
   private String[] _FrequencyDesc = null;
   
   /**
    * Transfer Type Description member array.
    */
   private String[] _TransferTypeDesc = null;
   
   /**
    * Entity Type member array.
    */
   private String[] _EntityType = null;
   
   /**
    * Entity Type Sequence member array.
    */
   private Integer[] _EntityTypeSeq = null;
   
   /**
    * Transaction Number member array.
    */
   private Integer[] _TransNum = null;
   
   /**
    * Split Commissions Exist member array.
    */
   private Boolean[] _SplitComm = null;
   
   /**
    * Next Process Date member array.
    */
   private Date[] _NextProcessDate = null;
   
   /**
    * Bank Type member array.
    */
   private String[] _BankType = null;
   
   /**
    * Bank ID Number member array.
    */
   private String[] _BankIdNum = null;
   
   /**
    * ACH Processor member array.
    */
   private String[] _ACHProcessor = null;
   
   /**
    * Bank Id member array.
    */
   private Integer[] _BankId = null;
   
   /**
    * Credit Info Line1 member array.
    */
   private String[] _CreditInfoLine1 = null;
   
   /**
    * Credit Info Line 2 member array.
    */
   private String[] _CreditInfoLine2 = null;
   
   /**
    * Bank Address Line 1 member array.
    */
   private String[] _BankAddr1 = null;
   
   /**
    * Bank Address Line 2 member array.
    */
   private String[] _BankAddr2 = null;
   
   /**
    * Bank Address Line 3 member array.
    */
   private String[] _BankAddr3 = null;
   
   /**
    * Bank Address Line 4 member array.
    */
   private String[] _BankAddr4 = null;
   
   /**
    * Bank Address Line 5 member array.
    */
   private String[] _BankAddr5 = null;
   
   /**
    * Bank Contact Person member array.
    */
   private String[] _BankContact = null;
   
   /**
    * Bank Address Country Code member array.
    */
   private String[] _BankCntry = null;
   
   /**
    * Bank Address Postal Code member array.
    */
   private String[] _BankPstl = null;
   
   /**
    * Expected Fee member array.
    */
   private String[] _VUBExpectedAmt = null;
   
   /**
    * Collected Fee member array.
    */
   private String[] _VUBCollectedAmt = null;
   
   /**
    * Plan Code member array.
    */
   private String[] _PlanCode = null;
   
   /**
    * Indicates if PAC has indexing info member array.
    */
   private Boolean[] _IndexExist = null;
   
   /**
    * First Contribution member array.
    */
   private String[] _InitialAmt = null;
   
   /**
    * Inital, Monthly or Waived member array.
    */
   private String[] _VUBPayOption = null;
   
   /**
    * Annual Maintenance Fee Applies Y/N member array.
    */
   private Boolean[] _AnnualMaint = null;
   
   /**
    * Saving Plan Fee Type - P(ercent) or F(raction) member array.
    */
   private String[] _VUBFeeType = null;
   
   /**
    * Fraction Value 1 member array.
    */
   private Integer[] _VUBFeeFrac1 = null;
   
   /**
    * Fraction Value 2 member array.
    */
   private Integer[] _VUBFeeFrac2 = null;
   
   /**
    * Anniversary of Savings Plan member array.
    */
   private Date[] _AnnualFeeDate = null;
   
   /**
    * Percent Value member array.
    */
   private String[] _VUBFeeRate = null;
   
   /**
    * Fee on In side of Exchange member array.
    */
   private String[] _ExchInFee = null;
   
   /**
    * Fee on In side is Flat (Yes) member array.
    */
   private Boolean[] _ExchInFlatPercent = null;
   
   /**
    * flag indicating if record can be modified member array.
    */
   private Boolean[] _ModPerm = null;
   
   /**
    * Exchange Out Fee member array.
    */
   private String[] _ExchOutFee = null;
   
   /**
    * Exchange Out Flat/Prcnt member array.
    */
   private Boolean[] _ExchOutFlatPrcnt = null;
   
   /**
    * Payment Method member array.
    */
   private String[] _PayMethod = null;
   
   /**
    * Override Federal Tax PUD member array.
    */
   private String[] _FedTaxPUDOverride = null;
   
   /**
    * Federal Tax Rate member array.
    */
   private String[] _FedRate = null;
   
   /**
    * Override Provisional Tax PUD member array.
    */
   private String[] _ProvTaxPUDOverride = null;
   
   /**
    * Provisional Tax Rate member array.
    */
   private String[] _ProvRate = null;
   
   /**
    * Pay Reason 2 member array.
    */
   private String[] _PayReason2 = null;
   
   /**
    * Stop Reason member array.
    */
   private String[] _StopReason = null;
   
   /**
    * Non Financial Confirm member array.
    */
   private String[] _NonFinConfirm = null;
   
   /**
    * Verify Status member array.
    */
   private String[] _VerifyStat = null;
   
   /**
    * RDR Advice member array.
    */
   private String[] _RDRAdvice = null;
   
   /**
    * Event Receipt Date member array.
    */
   private Date[] _EventReceiptDate = null;
   
   /**
    * Event Receipt Time member array.
    */
   private String[] _EventReceiptTime = null;
   
   /**
    * SourceOfTrade member array.
    */
   private String[] _SourceOfTrade = null;
   
   /**
    * ChannelOfTrade member array.
    */
   private String[] _ChannelOfTrade = null;
   
   /**
    * Platform member array.
    */
   private String[] _Platform = null;
   
   /**
    * PSDAdvice member array.
    */
   private String[] _PSDAdvice = null;
   
   /**
    * SignatureDate member array.
    */
   private Date[] _SignatureDate = null;
   

   /**
    * Constructs the PACSWPDetailsView object.
    * 
    */
   public PACSWPDetailsView()
   {
      super ( new PACSWPDetailsRequest() );
   }

   /**
    * Constructs the PACSWPDetailsView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public PACSWPDetailsView( String hostEncoding )
   {
      super ( new PACSWPDetailsRequest( hostEncoding ) );
   }

   /**
    * Gets the PACSWPDetailsRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The PACSWPDetailsRequest object.
    */
   public final PACSWPDetailsRequest getRequest()
   {
      return (PACSWPDetailsRequest)getIFastRequest();
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
    * Gets the Broker Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Broker Code or null.
    */
   public final String getBrokerCode( int index )
   {
      return _BrokerCode[index];
   }
    
   /**
    * Gets the Broker Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker Code or the specified default value.
    */
   public final String getBrokerCode( int index, String defaultValue )
   {
      return _BrokerCode[index] == null ? defaultValue : _BrokerCode[index];
   }
    
   /**
    * Gets the array of Broker Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Broker Code values.
    */
   public final String[] getBrokerCodeArray()
   {
      return _BrokerCode;
   }
    
   /**
    * Gets the Branch Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Branch Code or null.
    */
   public final String getBranchCode( int index )
   {
      return _BranchCode[index];
   }
    
   /**
    * Gets the Branch Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Branch Code or the specified default value.
    */
   public final String getBranchCode( int index, String defaultValue )
   {
      return _BranchCode[index] == null ? defaultValue : _BranchCode[index];
   }
    
   /**
    * Gets the array of Branch Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Branch Code values.
    */
   public final String[] getBranchCodeArray()
   {
      return _BranchCode;
   }
    
   /**
    * Gets the SalesRep Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SalesRep Code or null.
    */
   public final String getSalesrepCode( int index )
   {
      return _SalesrepCode[index];
   }
    
   /**
    * Gets the SalesRep Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SalesRep Code or the specified default value.
    */
   public final String getSalesrepCode( int index, String defaultValue )
   {
      return _SalesrepCode[index] == null ? defaultValue : _SalesrepCode[index];
   }
    
   /**
    * Gets the array of SalesRep Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SalesRep Code values.
    */
   public final String[] getSalesrepCodeArray()
   {
      return _SalesrepCode;
   }
    
   /**
    * Gets the Broker's Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Broker's Name or null.
    */
   public final String getBrokerName( int index )
   {
      return _BrokerName[index];
   }
    
   /**
    * Gets the Broker's Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker's Name or the specified default value.
    */
   public final String getBrokerName( int index, String defaultValue )
   {
      return _BrokerName[index] == null ? defaultValue : _BrokerName[index];
   }
    
   /**
    * Gets the array of Broker's Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Broker's Name values.
    */
   public final String[] getBrokerNameArray()
   {
      return _BrokerName;
   }
    
   /**
    * Gets the Branch's Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Branch's Name or null.
    */
   public final String getBranchName( int index )
   {
      return _BranchName[index];
   }
    
   /**
    * Gets the Branch's Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Branch's Name or the specified default value.
    */
   public final String getBranchName( int index, String defaultValue )
   {
      return _BranchName[index] == null ? defaultValue : _BranchName[index];
   }
    
   /**
    * Gets the array of Branch's Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Branch's Name values.
    */
   public final String[] getBranchNameArray()
   {
      return _BranchName;
   }
    
   /**
    * Gets the Slsrep's Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Slsrep's Name or null.
    */
   public final String getSlsrepName( int index )
   {
      return _SlsrepName[index];
   }
    
   /**
    * Gets the Slsrep's Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Slsrep's Name or the specified default value.
    */
   public final String getSlsrepName( int index, String defaultValue )
   {
      return _SlsrepName[index] == null ? defaultValue : _SlsrepName[index];
   }
    
   /**
    * Gets the array of Slsrep's Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Slsrep's Name values.
    */
   public final String[] getSlsrepNameArray()
   {
      return _SlsrepName;
   }
    
   /**
    * Gets the Amount to debit field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Amount to debit or null.
    */
   public final String getAmount( int index )
   {
      return _Amount[index];
   }
    
   /**
    * Gets the Amount to debit field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Amount to debit or the specified default value.
    */
   public final String getAmount( int index, String defaultValue )
   {
      return _Amount[index] == null ? defaultValue : _Amount[index];
   }
    
   /**
    * Gets the array of Amount to debit fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Amount to debit values.
    */
   public final String[] getAmountArray()
   {
      return _Amount;
   }
    
   /**
    * Gets the Amount Type Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Amount Type Code or null.
    */
   public final String getAmountType( int index )
   {
      return _AmountType[index];
   }
    
   /**
    * Gets the Amount Type Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Amount Type Code or the specified default value.
    */
   public final String getAmountType( int index, String defaultValue )
   {
      return _AmountType[index] == null ? defaultValue : _AmountType[index];
   }
    
   /**
    * Gets the array of Amount Type Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Amount Type Code values.
    */
   public final String[] getAmountTypeArray()
   {
      return _AmountType;
   }
    
   /**
    * Gets the Amount type description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Amount type description or null.
    */
   public final String getAmountTypeDesc( int index )
   {
      return _AmountTypeDesc[index];
   }
    
   /**
    * Gets the Amount type description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Amount type description or the specified default value.
    */
   public final String getAmountTypeDesc( int index, String defaultValue )
   {
      return _AmountTypeDesc[index] == null ? defaultValue : _AmountTypeDesc[index];
   }
    
   /**
    * Gets the array of Amount type description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Amount type description values.
    */
   public final String[] getAmountTypeDescArray()
   {
      return _AmountTypeDesc;
   }
    
   /**
    * Gets the Amount is expressed as Gross or Net field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Amount is expressed as Gross or Net or null.
    */
   public final Boolean getGrossOrNet( int index )
   {
      return _GrossOrNet[index];
   }
    
   /**
    * Gets the Amount is expressed as Gross or Net field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Amount is expressed as Gross or Net or the specified default value.
    */
   public final boolean getGrossOrNet( int index, boolean defaultValue )
   {
      return _GrossOrNet[index] == null ? defaultValue : _GrossOrNet[index].booleanValue();
   }
    
   /**
    * Gets the array of Amount is expressed as Gross or Net fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Amount is expressed as Gross or Net values.
    */
   public final Boolean[] getGrossOrNetArray()
   {
      return _GrossOrNet;
   }
    
   /**
    * Gets the Flat amount or percent fee field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flat amount or percent fee or null.
    */
   public final String getFee( int index )
   {
      return _Fee[index];
   }
    
   /**
    * Gets the Flat amount or percent fee field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flat amount or percent fee or the specified default value.
    */
   public final String getFee( int index, String defaultValue )
   {
      return _Fee[index] == null ? defaultValue : _Fee[index];
   }
    
   /**
    * Gets the array of Flat amount or percent fee fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flat amount or percent fee values.
    */
   public final String[] getFeeArray()
   {
      return _Fee;
   }
    
   /**
    * Gets the Percentage to charge as a fee field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Percentage to charge as a fee or null.
    */
   public final Boolean getFlatPercent( int index )
   {
      return _FlatPercent[index];
   }
    
   /**
    * Gets the Percentage to charge as a fee field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Percentage to charge as a fee or the specified default value.
    */
   public final boolean getFlatPercent( int index, boolean defaultValue )
   {
      return _FlatPercent[index] == null ? defaultValue : _FlatPercent[index].booleanValue();
   }
    
   /**
    * Gets the array of Percentage to charge as a fee fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Percentage to charge as a fee values.
    */
   public final Boolean[] getFlatPercentArray()
   {
      return _FlatPercent;
   }
    
   /**
    * Gets the Fee currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fee currency or null.
    */
   public final String getFeeCurrency( int index )
   {
      return _FeeCurrency[index];
   }
    
   /**
    * Gets the Fee currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee currency or the specified default value.
    */
   public final String getFeeCurrency( int index, String defaultValue )
   {
      return _FeeCurrency[index] == null ? defaultValue : _FeeCurrency[index];
   }
    
   /**
    * Gets the array of Fee currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee currency values.
    */
   public final String[] getFeeCurrencyArray()
   {
      return _FeeCurrency;
   }
    
   /**
    * Gets the Fee Currency Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fee Currency Description or null.
    */
   public final String getFeeCurrDesc( int index )
   {
      return _FeeCurrDesc[index];
   }
    
   /**
    * Gets the Fee Currency Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee Currency Description or the specified default value.
    */
   public final String getFeeCurrDesc( int index, String defaultValue )
   {
      return _FeeCurrDesc[index] == null ? defaultValue : _FeeCurrDesc[index];
   }
    
   /**
    * Gets the array of Fee Currency Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee Currency Description values.
    */
   public final String[] getFeeCurrDescArray()
   {
      return _FeeCurrDesc;
   }
    
   /**
    * Gets the Adminstration Fee field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Adminstration Fee or null.
    */
   public final String getAdminFeeAmt( int index )
   {
      return _AdminFeeAmt[index];
   }
    
   /**
    * Gets the Adminstration Fee field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Adminstration Fee or the specified default value.
    */
   public final String getAdminFeeAmt( int index, String defaultValue )
   {
      return _AdminFeeAmt[index] == null ? defaultValue : _AdminFeeAmt[index];
   }
    
   /**
    * Gets the array of Adminstration Fee fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Adminstration Fee values.
    */
   public final String[] getAdminFeeAmtArray()
   {
      return _AdminFeeAmt;
   }
    
   /**
    * Gets the Admin fee currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Admin fee currency or null.
    */
   public final String getAdminFeeCurr( int index )
   {
      return _AdminFeeCurr[index];
   }
    
   /**
    * Gets the Admin fee currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Admin fee currency or the specified default value.
    */
   public final String getAdminFeeCurr( int index, String defaultValue )
   {
      return _AdminFeeCurr[index] == null ? defaultValue : _AdminFeeCurr[index];
   }
    
   /**
    * Gets the array of Admin fee currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Admin fee currency values.
    */
   public final String[] getAdminFeeCurrArray()
   {
      return _AdminFeeCurr;
   }
    
   /**
    * Gets the Admin Fee Currency Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Admin Fee Currency Name or null.
    */
   public final String getAdminFeeCurrDesc( int index )
   {
      return _AdminFeeCurrDesc[index];
   }
    
   /**
    * Gets the Admin Fee Currency Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Admin Fee Currency Name or the specified default value.
    */
   public final String getAdminFeeCurrDesc( int index, String defaultValue )
   {
      return _AdminFeeCurrDesc[index] == null ? defaultValue : _AdminFeeCurrDesc[index];
   }
    
   /**
    * Gets the array of Admin Fee Currency Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Admin Fee Currency Name values.
    */
   public final String[] getAdminFeeCurrDescArray()
   {
      return _AdminFeeCurrDesc;
   }
    
   /**
    * Gets the Payment type code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Payment type code or null.
    */
   public final String getPayType( int index )
   {
      return _PayType[index];
   }
    
   /**
    * Gets the Payment type code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payment type code or the specified default value.
    */
   public final String getPayType( int index, String defaultValue )
   {
      return _PayType[index] == null ? defaultValue : _PayType[index];
   }
    
   /**
    * Gets the array of Payment type code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Payment type code values.
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
    * Gets the Instution code to debit field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Instution code to debit or null.
    */
   public final Integer getInstCode( int index )
   {
      return _InstCode[index];
   }
    
   /**
    * Gets the Instution code to debit field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Instution code to debit or the specified default value.
    */
   public final int getInstCode( int index, int defaultValue )
   {
      return _InstCode[index] == null ? defaultValue : _InstCode[index].intValue();
   }
    
   /**
    * Gets the array of Instution code to debit fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Instution code to debit values.
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
    * Gets the Transit code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transit code or null.
    */
   public final Integer getTransitNo( int index )
   {
      return _TransitNo[index];
   }
    
   /**
    * Gets the Transit code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transit code or the specified default value.
    */
   public final int getTransitNo( int index, int defaultValue )
   {
      return _TransitNo[index] == null ? defaultValue : _TransitNo[index].intValue();
   }
    
   /**
    * Gets the array of Transit code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transit code values.
    */
   public final Integer[] getTransitNoArray()
   {
      return _TransitNo;
   }
    
   /**
    * Gets the Bank account to debit field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank account to debit or null.
    */
   public final String getBankAcctNum( int index )
   {
      return _BankAcctNum[index];
   }
    
   /**
    * Gets the Bank account to debit field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank account to debit or the specified default value.
    */
   public final String getBankAcctNum( int index, String defaultValue )
   {
      return _BankAcctNum[index] == null ? defaultValue : _BankAcctNum[index];
   }
    
   /**
    * Gets the array of Bank account to debit fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank account to debit values.
    */
   public final String[] getBankAcctNumArray()
   {
      return _BankAcctNum;
   }
    
   /**
    * Gets the Name of the bank account field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Name of the bank account or null.
    */
   public final String getBankAcctName( int index )
   {
      return _BankAcctName[index];
   }
    
   /**
    * Gets the Name of the bank account field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Name of the bank account or the specified default value.
    */
   public final String getBankAcctName( int index, String defaultValue )
   {
      return _BankAcctName[index] == null ? defaultValue : _BankAcctName[index];
   }
    
   /**
    * Gets the array of Name of the bank account fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Name of the bank account values.
    */
   public final String[] getBankAcctNameArray()
   {
      return _BankAcctName;
   }
    
   /**
    * Gets the Source of the bank account field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Source of the bank account or null.
    */
   public final String getSourceOfBankAcct( int index )
   {
      return _SourceOfBankAcct[index];
   }
    
   /**
    * Gets the Source of the bank account field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Source of the bank account or the specified default value.
    */
   public final String getSourceOfBankAcct( int index, String defaultValue )
   {
      return _SourceOfBankAcct[index] == null ? defaultValue : _SourceOfBankAcct[index];
   }
    
   /**
    * Gets the array of Source of the bank account fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Source of the bank account values.
    */
   public final String[] getSourceOfBankAcctArray()
   {
      return _SourceOfBankAcct;
   }
    
   /**
    * Gets the Currency of the bank account field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Currency of the bank account or null.
    */
   public final String getBankAcctCurrency( int index )
   {
      return _BankAcctCurrency[index];
   }
    
   /**
    * Gets the Currency of the bank account field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Currency of the bank account or the specified default value.
    */
   public final String getBankAcctCurrency( int index, String defaultValue )
   {
      return _BankAcctCurrency[index] == null ? defaultValue : _BankAcctCurrency[index];
   }
    
   /**
    * Gets the array of Currency of the bank account fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Currency of the bank account values.
    */
   public final String[] getBankAcctCurrencyArray()
   {
      return _BankAcctCurrency;
   }
    
   /**
    * Gets the Bank Account Currency Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Account Currency Description or null.
    */
   public final String getBankCurrDesc( int index )
   {
      return _BankCurrDesc[index];
   }
    
   /**
    * Gets the Bank Account Currency Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Account Currency Description or the specified default value.
    */
   public final String getBankCurrDesc( int index, String defaultValue )
   {
      return _BankCurrDesc[index] == null ? defaultValue : _BankCurrDesc[index];
   }
    
   /**
    * Gets the array of Bank Account Currency Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Account Currency Description values.
    */
   public final String[] getBankCurrDescArray()
   {
      return _BankCurrDesc;
   }
    
   /**
    * Gets the Bank Acount Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Acount Type or null.
    */
   public final String getBankAcctType( int index )
   {
      return _BankAcctType[index];
   }
    
   /**
    * Gets the Bank Acount Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Acount Type or the specified default value.
    */
   public final String getBankAcctType( int index, String defaultValue )
   {
      return _BankAcctType[index] == null ? defaultValue : _BankAcctType[index];
   }
    
   /**
    * Gets the array of Bank Acount Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Acount Type values.
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
    * Gets the Source of Fund field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Source of Fund or null.
    */
   public final String getSrcOfFund( int index )
   {
      return _SrcOfFund[index];
   }
    
   /**
    * Gets the Source of Fund field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Source of Fund or the specified default value.
    */
   public final String getSrcOfFund( int index, String defaultValue )
   {
      return _SrcOfFund[index] == null ? defaultValue : _SrcOfFund[index];
   }
    
   /**
    * Gets the array of Source of Fund fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Source of Fund values.
    */
   public final String[] getSrcOfFundArray()
   {
      return _SrcOfFund;
   }
    
   /**
    * Gets the Source of Fund Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Source of Fund Description or null.
    */
   public final String getSrcOFFundDesc( int index )
   {
      return _SrcOFFundDesc[index];
   }
    
   /**
    * Gets the Source of Fund Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Source of Fund Description or the specified default value.
    */
   public final String getSrcOFFundDesc( int index, String defaultValue )
   {
      return _SrcOFFundDesc[index] == null ? defaultValue : _SrcOFFundDesc[index];
   }
    
   /**
    * Gets the array of Source of Fund Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Source of Fund Description values.
    */
   public final String[] getSrcOFFundDescArray()
   {
      return _SrcOFFundDesc;
   }
    
   /**
    * Gets the January field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the January or null.
    */
   public final Boolean getJanuary( int index )
   {
      return _January[index];
   }
    
   /**
    * Gets the January field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the January or the specified default value.
    */
   public final boolean getJanuary( int index, boolean defaultValue )
   {
      return _January[index] == null ? defaultValue : _January[index].booleanValue();
   }
    
   /**
    * Gets the array of January fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of January values.
    */
   public final Boolean[] getJanuaryArray()
   {
      return _January;
   }
    
   /**
    * Gets the February field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the February or null.
    */
   public final Boolean getFebruary( int index )
   {
      return _February[index];
   }
    
   /**
    * Gets the February field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the February or the specified default value.
    */
   public final boolean getFebruary( int index, boolean defaultValue )
   {
      return _February[index] == null ? defaultValue : _February[index].booleanValue();
   }
    
   /**
    * Gets the array of February fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of February values.
    */
   public final Boolean[] getFebruaryArray()
   {
      return _February;
   }
    
   /**
    * Gets the March field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the March or null.
    */
   public final Boolean getMarch( int index )
   {
      return _March[index];
   }
    
   /**
    * Gets the March field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the March or the specified default value.
    */
   public final boolean getMarch( int index, boolean defaultValue )
   {
      return _March[index] == null ? defaultValue : _March[index].booleanValue();
   }
    
   /**
    * Gets the array of March fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of March values.
    */
   public final Boolean[] getMarchArray()
   {
      return _March;
   }
    
   /**
    * Gets the April field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the April or null.
    */
   public final Boolean getApril( int index )
   {
      return _April[index];
   }
    
   /**
    * Gets the April field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the April or the specified default value.
    */
   public final boolean getApril( int index, boolean defaultValue )
   {
      return _April[index] == null ? defaultValue : _April[index].booleanValue();
   }
    
   /**
    * Gets the array of April fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of April values.
    */
   public final Boolean[] getAprilArray()
   {
      return _April;
   }
    
   /**
    * Gets the May field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the May or null.
    */
   public final Boolean getMay( int index )
   {
      return _May[index];
   }
    
   /**
    * Gets the May field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the May or the specified default value.
    */
   public final boolean getMay( int index, boolean defaultValue )
   {
      return _May[index] == null ? defaultValue : _May[index].booleanValue();
   }
    
   /**
    * Gets the array of May fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of May values.
    */
   public final Boolean[] getMayArray()
   {
      return _May;
   }
    
   /**
    * Gets the June field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the June or null.
    */
   public final Boolean getJune( int index )
   {
      return _June[index];
   }
    
   /**
    * Gets the June field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the June or the specified default value.
    */
   public final boolean getJune( int index, boolean defaultValue )
   {
      return _June[index] == null ? defaultValue : _June[index].booleanValue();
   }
    
   /**
    * Gets the array of June fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of June values.
    */
   public final Boolean[] getJuneArray()
   {
      return _June;
   }
    
   /**
    * Gets the July field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the July or null.
    */
   public final Boolean getJuly( int index )
   {
      return _July[index];
   }
    
   /**
    * Gets the July field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the July or the specified default value.
    */
   public final boolean getJuly( int index, boolean defaultValue )
   {
      return _July[index] == null ? defaultValue : _July[index].booleanValue();
   }
    
   /**
    * Gets the array of July fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of July values.
    */
   public final Boolean[] getJulyArray()
   {
      return _July;
   }
    
   /**
    * Gets the August field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the August or null.
    */
   public final Boolean getAugust( int index )
   {
      return _August[index];
   }
    
   /**
    * Gets the August field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the August or the specified default value.
    */
   public final boolean getAugust( int index, boolean defaultValue )
   {
      return _August[index] == null ? defaultValue : _August[index].booleanValue();
   }
    
   /**
    * Gets the array of August fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of August values.
    */
   public final Boolean[] getAugustArray()
   {
      return _August;
   }
    
   /**
    * Gets the September field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the September or null.
    */
   public final Boolean getSeptember( int index )
   {
      return _September[index];
   }
    
   /**
    * Gets the September field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the September or the specified default value.
    */
   public final boolean getSeptember( int index, boolean defaultValue )
   {
      return _September[index] == null ? defaultValue : _September[index].booleanValue();
   }
    
   /**
    * Gets the array of September fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of September values.
    */
   public final Boolean[] getSeptemberArray()
   {
      return _September;
   }
    
   /**
    * Gets the October field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the October or null.
    */
   public final Boolean getOctober( int index )
   {
      return _October[index];
   }
    
   /**
    * Gets the October field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the October or the specified default value.
    */
   public final boolean getOctober( int index, boolean defaultValue )
   {
      return _October[index] == null ? defaultValue : _October[index].booleanValue();
   }
    
   /**
    * Gets the array of October fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of October values.
    */
   public final Boolean[] getOctoberArray()
   {
      return _October;
   }
    
   /**
    * Gets the November field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the November or null.
    */
   public final Boolean getNovember( int index )
   {
      return _November[index];
   }
    
   /**
    * Gets the November field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the November or the specified default value.
    */
   public final boolean getNovember( int index, boolean defaultValue )
   {
      return _November[index] == null ? defaultValue : _November[index].booleanValue();
   }
    
   /**
    * Gets the array of November fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of November values.
    */
   public final Boolean[] getNovemberArray()
   {
      return _November;
   }
    
   /**
    * Gets the December field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the December or null.
    */
   public final Boolean getDecember( int index )
   {
      return _December[index];
   }
    
   /**
    * Gets the December field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the December or the specified default value.
    */
   public final boolean getDecember( int index, boolean defaultValue )
   {
      return _December[index] == null ? defaultValue : _December[index].booleanValue();
   }
    
   /**
    * Gets the array of December fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of December values.
    */
   public final Boolean[] getDecemberArray()
   {
      return _December;
   }
    
   /**
    * Gets the PAC/SWP occurs at end of month field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the PAC/SWP occurs at end of month or null.
    */
   public final Boolean getEndOfMonth( int index )
   {
      return _EndOfMonth[index];
   }
    
   /**
    * Gets the PAC/SWP occurs at end of month field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PAC/SWP occurs at end of month or the specified default value.
    */
   public final boolean getEndOfMonth( int index, boolean defaultValue )
   {
      return _EndOfMonth[index] == null ? defaultValue : _EndOfMonth[index].booleanValue();
   }
    
   /**
    * Gets the array of PAC/SWP occurs at end of month fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of PAC/SWP occurs at end of month values.
    */
   public final Boolean[] getEndOfMonthArray()
   {
      return _EndOfMonth;
   }
    
   /**
    * Gets the Day of Week PAC occurs on field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Day of Week PAC occurs on or null.
    */
   public final Integer getDayOfWeek( int index )
   {
      return _DayOfWeek[index];
   }
    
   /**
    * Gets the Day of Week PAC occurs on field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Day of Week PAC occurs on or the specified default value.
    */
   public final int getDayOfWeek( int index, int defaultValue )
   {
      return _DayOfWeek[index] == null ? defaultValue : _DayOfWeek[index].intValue();
   }
    
   /**
    * Gets the array of Day of Week PAC occurs on fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Day of Week PAC occurs on values.
    */
   public final Integer[] getDayOfWeekArray()
   {
      return _DayOfWeek;
   }
    
   /**
    * Gets the Last Process Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Last Process Date or null.
    */
   public final Date getLastProcessDate( int index )
   {
      return _LastProcessDate[index];
   }
    
   /**
    * Gets the Last Process Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Last Process Date or the specified default value.
    */
   public final Date getLastProcessDate( int index, Date defaultValue )
   {
      return _LastProcessDate[index] == null ? defaultValue : _LastProcessDate[index];
   }
    
   /**
    * Gets the array of Last Process Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Last Process Date values.
    */
   public final Date[] getLastProcessDateArray()
   {
      return _LastProcessDate;
   }
    
   /**
    * Gets the Address Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Code or null.
    */
   public final String getAddrCode( int index )
   {
      return _AddrCode[index];
   }
    
   /**
    * Gets the Address Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Code or the specified default value.
    */
   public final String getAddrCode( int index, String defaultValue )
   {
      return _AddrCode[index] == null ? defaultValue : _AddrCode[index];
   }
    
   /**
    * Gets the array of Address Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Code values.
    */
   public final String[] getAddrCodeArray()
   {
      return _AddrCode;
   }
    
   /**
    * Gets the Record Active field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Record Active or null.
    */
   public final Boolean getGoodBad( int index )
   {
      return _GoodBad[index];
   }
    
   /**
    * Gets the Record Active field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Record Active or the specified default value.
    */
   public final boolean getGoodBad( int index, boolean defaultValue )
   {
      return _GoodBad[index] == null ? defaultValue : _GoodBad[index].booleanValue();
   }
    
   /**
    * Gets the array of Record Active fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Record Active values.
    */
   public final Boolean[] getGoodBadArray()
   {
      return _GoodBad;
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
    * Gets the Modification Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Modification Date or null.
    */
   public final Date getModDate( int index )
   {
      return _ModDate[index];
   }
    
   /**
    * Gets the Modification Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Modification Date or the specified default value.
    */
   public final Date getModDate( int index, Date defaultValue )
   {
      return _ModDate[index] == null ? defaultValue : _ModDate[index];
   }
    
   /**
    * Gets the array of Modification Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Modification Date values.
    */
   public final Date[] getModDateArray()
   {
      return _ModDate;
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
    * Gets the Created by field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Created by or null.
    */
   public final String getUsername( int index )
   {
      return _Username[index];
   }
    
   /**
    * Gets the Created by field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Created by or the specified default value.
    */
   public final String getUsername( int index, String defaultValue )
   {
      return _Username[index] == null ? defaultValue : _Username[index];
   }
    
   /**
    * Gets the array of Created by fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Created by values.
    */
   public final String[] getUsernameArray()
   {
      return _Username;
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
    * Gets the Address Line1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Line1 or null.
    */
   public final String getAddrLine1( int index )
   {
      return _AddrLine1[index];
   }
    
   /**
    * Gets the Address Line1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line1 or the specified default value.
    */
   public final String getAddrLine1( int index, String defaultValue )
   {
      return _AddrLine1[index] == null ? defaultValue : _AddrLine1[index];
   }
    
   /**
    * Gets the array of Address Line1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Line1 values.
    */
   public final String[] getAddrLine1Array()
   {
      return _AddrLine1;
   }
    
   /**
    * Gets the Address Line2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Line2 or null.
    */
   public final String getAddrLine2( int index )
   {
      return _AddrLine2[index];
   }
    
   /**
    * Gets the Address Line2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line2 or the specified default value.
    */
   public final String getAddrLine2( int index, String defaultValue )
   {
      return _AddrLine2[index] == null ? defaultValue : _AddrLine2[index];
   }
    
   /**
    * Gets the array of Address Line2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Line2 values.
    */
   public final String[] getAddrLine2Array()
   {
      return _AddrLine2;
   }
    
   /**
    * Gets the Address Line3 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Line3 or null.
    */
   public final String getAddrLine3( int index )
   {
      return _AddrLine3[index];
   }
    
   /**
    * Gets the Address Line3 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line3 or the specified default value.
    */
   public final String getAddrLine3( int index, String defaultValue )
   {
      return _AddrLine3[index] == null ? defaultValue : _AddrLine3[index];
   }
    
   /**
    * Gets the array of Address Line3 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Line3 values.
    */
   public final String[] getAddrLine3Array()
   {
      return _AddrLine3;
   }
    
   /**
    * Gets the Address Line4 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Line4 or null.
    */
   public final String getAddrLine4( int index )
   {
      return _AddrLine4[index];
   }
    
   /**
    * Gets the Address Line4 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line4 or the specified default value.
    */
   public final String getAddrLine4( int index, String defaultValue )
   {
      return _AddrLine4[index] == null ? defaultValue : _AddrLine4[index];
   }
    
   /**
    * Gets the array of Address Line4 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Line4 values.
    */
   public final String[] getAddrLine4Array()
   {
      return _AddrLine4;
   }
    
   /**
    * Gets the Address Line5 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Line5 or null.
    */
   public final String getAddrLine5( int index )
   {
      return _AddrLine5[index];
   }
    
   /**
    * Gets the Address Line5 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line5 or the specified default value.
    */
   public final String getAddrLine5( int index, String defaultValue )
   {
      return _AddrLine5[index] == null ? defaultValue : _AddrLine5[index];
   }
    
   /**
    * Gets the array of Address Line5 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Line5 values.
    */
   public final String[] getAddrLine5Array()
   {
      return _AddrLine5;
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
    * Gets the Salesrep Alternate Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Salesrep Alternate Name or null.
    */
   public final String getSlsrepAltName( int index )
   {
      return _SlsrepAltName[index];
   }
    
   /**
    * Gets the Salesrep Alternate Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Salesrep Alternate Name or the specified default value.
    */
   public final String getSlsrepAltName( int index, String defaultValue )
   {
      return _SlsrepAltName[index] == null ? defaultValue : _SlsrepAltName[index];
   }
    
   /**
    * Gets the array of Salesrep Alternate Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Salesrep Alternate Name values.
    */
   public final String[] getSlsrepAltNameArray()
   {
      return _SlsrepAltName;
   }
    
   /**
    * Gets the Fund Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Code or null.
    */
   public final String getFundCode( int index )
   {
      return _FundCode[index];
   }
    
   /**
    * Gets the Fund Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Code or the specified default value.
    */
   public final String getFundCode( int index, String defaultValue )
   {
      return _FundCode[index] == null ? defaultValue : _FundCode[index];
   }
    
   /**
    * Gets the array of Fund Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Code values.
    */
   public final String[] getFundCodeArray()
   {
      return _FundCode;
   }
    
   /**
    * Gets the Class Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Class Code or null.
    */
   public final String getClassCode( int index )
   {
      return _ClassCode[index];
   }
    
   /**
    * Gets the Class Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class Code or the specified default value.
    */
   public final String getClassCode( int index, String defaultValue )
   {
      return _ClassCode[index] == null ? defaultValue : _ClassCode[index];
   }
    
   /**
    * Gets the array of Class Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Class Code values.
    */
   public final String[] getClassCodeArray()
   {
      return _ClassCode;
   }
    
   /**
    * Gets the PAC/SWP Record ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the PAC/SWP Record ID or null.
    */
   public final Integer getPACSWPId( int index )
   {
      return _PACSWPId[index];
   }
    
   /**
    * Gets the PAC/SWP Record ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PAC/SWP Record ID or the specified default value.
    */
   public final int getPACSWPId( int index, int defaultValue )
   {
      return _PACSWPId[index] == null ? defaultValue : _PACSWPId[index].intValue();
   }
    
   /**
    * Gets the array of PAC/SWP Record ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of PAC/SWP Record ID values.
    */
   public final Integer[] getPACSWPIdArray()
   {
      return _PACSWPId;
   }
    
   /**
    * Gets the Transacion Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transacion Type or null.
    */
   public final String getTransType( int index )
   {
      return _TransType[index];
   }
    
   /**
    * Gets the Transacion Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transacion Type or the specified default value.
    */
   public final String getTransType( int index, String defaultValue )
   {
      return _TransType[index] == null ? defaultValue : _TransType[index];
   }
    
   /**
    * Gets the array of Transacion Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transacion Type values.
    */
   public final String[] getTransTypeArray()
   {
      return _TransType;
   }
    
   /**
    * Gets the Bank-Detl/Recur-Detail Version field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank-Detl/Recur-Detail Version or null.
    */
   public final Integer getVersionNum( int index )
   {
      return _VersionNum[index];
   }
    
   /**
    * Gets the Bank-Detl/Recur-Detail Version field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank-Detl/Recur-Detail Version or the specified default value.
    */
   public final int getVersionNum( int index, int defaultValue )
   {
      return _VersionNum[index] == null ? defaultValue : _VersionNum[index].intValue();
   }
    
   /**
    * Gets the array of Bank-Detl/Recur-Detail Version fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank-Detl/Recur-Detail Version values.
    */
   public final Integer[] getVersionNumArray()
   {
      return _VersionNum;
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
    * Gets the Transfer To Fund field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transfer To Fund or null.
    */
   public final String getFundToCode( int index )
   {
      return _FundToCode[index];
   }
    
   /**
    * Gets the Transfer To Fund field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transfer To Fund or the specified default value.
    */
   public final String getFundToCode( int index, String defaultValue )
   {
      return _FundToCode[index] == null ? defaultValue : _FundToCode[index];
   }
    
   /**
    * Gets the array of Transfer To Fund fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transfer To Fund values.
    */
   public final String[] getFundToCodeArray()
   {
      return _FundToCode;
   }
    
   /**
    * Gets the Transfer To Class field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transfer To Class or null.
    */
   public final String getClassToCode( int index )
   {
      return _ClassToCode[index];
   }
    
   /**
    * Gets the Transfer To Class field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transfer To Class or the specified default value.
    */
   public final String getClassToCode( int index, String defaultValue )
   {
      return _ClassToCode[index] == null ? defaultValue : _ClassToCode[index];
   }
    
   /**
    * Gets the array of Transfer To Class fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transfer To Class values.
    */
   public final String[] getClassToCodeArray()
   {
      return _ClassToCode;
   }
    
   /**
    * Gets the Transfer To Account field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transfer To Account or null.
    */
   public final String getAccountTo( int index )
   {
      return _AccountTo[index];
   }
    
   /**
    * Gets the Transfer To Account field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transfer To Account or the specified default value.
    */
   public final String getAccountTo( int index, String defaultValue )
   {
      return _AccountTo[index] == null ? defaultValue : _AccountTo[index];
   }
    
   /**
    * Gets the array of Transfer To Account fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transfer To Account values.
    */
   public final String[] getAccountToArray()
   {
      return _AccountTo;
   }
    
   /**
    * Gets the Back End Load Fee Applicable field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Back End Load Fee Applicable or null.
    */
   public final Boolean getBELFee( int index )
   {
      return _BELFee[index];
   }
    
   /**
    * Gets the Back End Load Fee Applicable field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Back End Load Fee Applicable or the specified default value.
    */
   public final boolean getBELFee( int index, boolean defaultValue )
   {
      return _BELFee[index] == null ? defaultValue : _BELFee[index].booleanValue();
   }
    
   /**
    * Gets the array of Back End Load Fee Applicable fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Back End Load Fee Applicable values.
    */
   public final Boolean[] getBELFeeArray()
   {
      return _BELFee;
   }
    
   /**
    * Gets the Batch User field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Batch User or null.
    */
   public final String getBatchUser( int index )
   {
      return _BatchUser[index];
   }
    
   /**
    * Gets the Batch User field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Batch User or the specified default value.
    */
   public final String getBatchUser( int index, String defaultValue )
   {
      return _BatchUser[index] == null ? defaultValue : _BatchUser[index];
   }
    
   /**
    * Gets the array of Batch User fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Batch User values.
    */
   public final String[] getBatchUserArray()
   {
      return _BatchUser;
   }
    
   /**
    * Gets the Batch Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Batch Name or null.
    */
   public final String getBatch( int index )
   {
      return _Batch[index];
   }
    
   /**
    * Gets the Batch Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Batch Name or the specified default value.
    */
   public final String getBatch( int index, String defaultValue )
   {
      return _Batch[index] == null ? defaultValue : _Batch[index];
   }
    
   /**
    * Gets the array of Batch Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Batch Name values.
    */
   public final String[] getBatchArray()
   {
      return _Batch;
   }
    
   /**
    * Gets the Batch Trace field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Batch Trace or null.
    */
   public final Integer getBatchTrace( int index )
   {
      return _BatchTrace[index];
   }
    
   /**
    * Gets the Batch Trace field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Batch Trace or the specified default value.
    */
   public final int getBatchTrace( int index, int defaultValue )
   {
      return _BatchTrace[index] == null ? defaultValue : _BatchTrace[index].intValue();
   }
    
   /**
    * Gets the array of Batch Trace fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Batch Trace values.
    */
   public final Integer[] getBatchTraceArray()
   {
      return _BatchTrace;
   }
    
   /**
    * Gets the Batch Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Batch Date or null.
    */
   public final Date getBatchDate( int index )
   {
      return _BatchDate[index];
   }
    
   /**
    * Gets the Batch Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Batch Date or the specified default value.
    */
   public final Date getBatchDate( int index, Date defaultValue )
   {
      return _BatchDate[index] == null ? defaultValue : _BatchDate[index];
   }
    
   /**
    * Gets the array of Batch Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Batch Date values.
    */
   public final Date[] getBatchDateArray()
   {
      return _BatchDate;
   }
    
   /**
    * Gets the Transfer Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transfer Type or null.
    */
   public final String getTransferType( int index )
   {
      return _TransferType[index];
   }
    
   /**
    * Gets the Transfer Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transfer Type or the specified default value.
    */
   public final String getTransferType( int index, String defaultValue )
   {
      return _TransferType[index] == null ? defaultValue : _TransferType[index];
   }
    
   /**
    * Gets the array of Transfer Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transfer Type values.
    */
   public final String[] getTransferTypeArray()
   {
      return _TransferType;
   }
    
   /**
    * Gets the Frequency Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Frequency Code or null.
    */
   public final String getFrequency( int index )
   {
      return _Frequency[index];
   }
    
   /**
    * Gets the Frequency Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Frequency Code or the specified default value.
    */
   public final String getFrequency( int index, String defaultValue )
   {
      return _Frequency[index] == null ? defaultValue : _Frequency[index];
   }
    
   /**
    * Gets the array of Frequency Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Frequency Code values.
    */
   public final String[] getFrequencyArray()
   {
      return _Frequency;
   }
    
   /**
    * Gets the Flat Percent Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flat Percent Description or null.
    */
   public final String getFlatPercentDesc( int index )
   {
      return _FlatPercentDesc[index];
   }
    
   /**
    * Gets the Flat Percent Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flat Percent Description or the specified default value.
    */
   public final String getFlatPercentDesc( int index, String defaultValue )
   {
      return _FlatPercentDesc[index] == null ? defaultValue : _FlatPercentDesc[index];
   }
    
   /**
    * Gets the array of Flat Percent Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flat Percent Description values.
    */
   public final String[] getFlatPercentDescArray()
   {
      return _FlatPercentDesc;
   }
    
   /**
    * Gets the Frequency Type Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Frequency Type Description or null.
    */
   public final String getFrequencyDesc( int index )
   {
      return _FrequencyDesc[index];
   }
    
   /**
    * Gets the Frequency Type Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Frequency Type Description or the specified default value.
    */
   public final String getFrequencyDesc( int index, String defaultValue )
   {
      return _FrequencyDesc[index] == null ? defaultValue : _FrequencyDesc[index];
   }
    
   /**
    * Gets the array of Frequency Type Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Frequency Type Description values.
    */
   public final String[] getFrequencyDescArray()
   {
      return _FrequencyDesc;
   }
    
   /**
    * Gets the Transfer Type Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transfer Type Description or null.
    */
   public final String getTransferTypeDesc( int index )
   {
      return _TransferTypeDesc[index];
   }
    
   /**
    * Gets the Transfer Type Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transfer Type Description or the specified default value.
    */
   public final String getTransferTypeDesc( int index, String defaultValue )
   {
      return _TransferTypeDesc[index] == null ? defaultValue : _TransferTypeDesc[index];
   }
    
   /**
    * Gets the array of Transfer Type Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transfer Type Description values.
    */
   public final String[] getTransferTypeDescArray()
   {
      return _TransferTypeDesc;
   }
    
   /**
    * Gets the Entity Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Entity Type or null.
    */
   public final String getEntityType( int index )
   {
      return _EntityType[index];
   }
    
   /**
    * Gets the Entity Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity Type or the specified default value.
    */
   public final String getEntityType( int index, String defaultValue )
   {
      return _EntityType[index] == null ? defaultValue : _EntityType[index];
   }
    
   /**
    * Gets the array of Entity Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Entity Type values.
    */
   public final String[] getEntityTypeArray()
   {
      return _EntityType;
   }
    
   /**
    * Gets the Entity Type Sequence field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Entity Type Sequence or null.
    */
   public final Integer getEntityTypeSeq( int index )
   {
      return _EntityTypeSeq[index];
   }
    
   /**
    * Gets the Entity Type Sequence field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity Type Sequence or the specified default value.
    */
   public final int getEntityTypeSeq( int index, int defaultValue )
   {
      return _EntityTypeSeq[index] == null ? defaultValue : _EntityTypeSeq[index].intValue();
   }
    
   /**
    * Gets the array of Entity Type Sequence fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Entity Type Sequence values.
    */
   public final Integer[] getEntityTypeSeqArray()
   {
      return _EntityTypeSeq;
   }
    
   /**
    * Gets the Transaction Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transaction Number or null.
    */
   public final Integer getTransNum( int index )
   {
      return _TransNum[index];
   }
    
   /**
    * Gets the Transaction Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transaction Number or the specified default value.
    */
   public final int getTransNum( int index, int defaultValue )
   {
      return _TransNum[index] == null ? defaultValue : _TransNum[index].intValue();
   }
    
   /**
    * Gets the array of Transaction Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transaction Number values.
    */
   public final Integer[] getTransNumArray()
   {
      return _TransNum;
   }
    
   /**
    * Gets the Split Commissions Exist field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Split Commissions Exist or null.
    */
   public final Boolean getSplitComm( int index )
   {
      return _SplitComm[index];
   }
    
   /**
    * Gets the Split Commissions Exist field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Split Commissions Exist or the specified default value.
    */
   public final boolean getSplitComm( int index, boolean defaultValue )
   {
      return _SplitComm[index] == null ? defaultValue : _SplitComm[index].booleanValue();
   }
    
   /**
    * Gets the array of Split Commissions Exist fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Split Commissions Exist values.
    */
   public final Boolean[] getSplitCommArray()
   {
      return _SplitComm;
   }
    
   /**
    * Gets the Next Process Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Next Process Date or null.
    */
   public final Date getNextProcessDate( int index )
   {
      return _NextProcessDate[index];
   }
    
   /**
    * Gets the Next Process Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Next Process Date or the specified default value.
    */
   public final Date getNextProcessDate( int index, Date defaultValue )
   {
      return _NextProcessDate[index] == null ? defaultValue : _NextProcessDate[index];
   }
    
   /**
    * Gets the array of Next Process Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Next Process Date values.
    */
   public final Date[] getNextProcessDateArray()
   {
      return _NextProcessDate;
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
    * Gets the Bank ID Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank ID Number or null.
    */
   public final String getBankIdNum( int index )
   {
      return _BankIdNum[index];
   }
    
   /**
    * Gets the Bank ID Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank ID Number or the specified default value.
    */
   public final String getBankIdNum( int index, String defaultValue )
   {
      return _BankIdNum[index] == null ? defaultValue : _BankIdNum[index];
   }
    
   /**
    * Gets the array of Bank ID Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank ID Number values.
    */
   public final String[] getBankIdNumArray()
   {
      return _BankIdNum;
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
    * Gets the Credit Info Line1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Credit Info Line1 or null.
    */
   public final String getCreditInfoLine1( int index )
   {
      return _CreditInfoLine1[index];
   }
    
   /**
    * Gets the Credit Info Line1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Credit Info Line1 or the specified default value.
    */
   public final String getCreditInfoLine1( int index, String defaultValue )
   {
      return _CreditInfoLine1[index] == null ? defaultValue : _CreditInfoLine1[index];
   }
    
   /**
    * Gets the array of Credit Info Line1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Credit Info Line1 values.
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
    * Gets the Bank Address Line 1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Address Line 1 or null.
    */
   public final String getBankAddr1( int index )
   {
      return _BankAddr1[index];
   }
    
   /**
    * Gets the Bank Address Line 1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Address Line 1 or the specified default value.
    */
   public final String getBankAddr1( int index, String defaultValue )
   {
      return _BankAddr1[index] == null ? defaultValue : _BankAddr1[index];
   }
    
   /**
    * Gets the array of Bank Address Line 1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Address Line 1 values.
    */
   public final String[] getBankAddr1Array()
   {
      return _BankAddr1;
   }
    
   /**
    * Gets the Bank Address Line 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Address Line 2 or null.
    */
   public final String getBankAddr2( int index )
   {
      return _BankAddr2[index];
   }
    
   /**
    * Gets the Bank Address Line 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Address Line 2 or the specified default value.
    */
   public final String getBankAddr2( int index, String defaultValue )
   {
      return _BankAddr2[index] == null ? defaultValue : _BankAddr2[index];
   }
    
   /**
    * Gets the array of Bank Address Line 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Address Line 2 values.
    */
   public final String[] getBankAddr2Array()
   {
      return _BankAddr2;
   }
    
   /**
    * Gets the Bank Address Line 3 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Address Line 3 or null.
    */
   public final String getBankAddr3( int index )
   {
      return _BankAddr3[index];
   }
    
   /**
    * Gets the Bank Address Line 3 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Address Line 3 or the specified default value.
    */
   public final String getBankAddr3( int index, String defaultValue )
   {
      return _BankAddr3[index] == null ? defaultValue : _BankAddr3[index];
   }
    
   /**
    * Gets the array of Bank Address Line 3 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Address Line 3 values.
    */
   public final String[] getBankAddr3Array()
   {
      return _BankAddr3;
   }
    
   /**
    * Gets the Bank Address Line 4 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Address Line 4 or null.
    */
   public final String getBankAddr4( int index )
   {
      return _BankAddr4[index];
   }
    
   /**
    * Gets the Bank Address Line 4 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Address Line 4 or the specified default value.
    */
   public final String getBankAddr4( int index, String defaultValue )
   {
      return _BankAddr4[index] == null ? defaultValue : _BankAddr4[index];
   }
    
   /**
    * Gets the array of Bank Address Line 4 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Address Line 4 values.
    */
   public final String[] getBankAddr4Array()
   {
      return _BankAddr4;
   }
    
   /**
    * Gets the Bank Address Line 5 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Address Line 5 or null.
    */
   public final String getBankAddr5( int index )
   {
      return _BankAddr5[index];
   }
    
   /**
    * Gets the Bank Address Line 5 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Address Line 5 or the specified default value.
    */
   public final String getBankAddr5( int index, String defaultValue )
   {
      return _BankAddr5[index] == null ? defaultValue : _BankAddr5[index];
   }
    
   /**
    * Gets the array of Bank Address Line 5 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Address Line 5 values.
    */
   public final String[] getBankAddr5Array()
   {
      return _BankAddr5;
   }
    
   /**
    * Gets the Bank Contact Person field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Contact Person or null.
    */
   public final String getBankContact( int index )
   {
      return _BankContact[index];
   }
    
   /**
    * Gets the Bank Contact Person field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Contact Person or the specified default value.
    */
   public final String getBankContact( int index, String defaultValue )
   {
      return _BankContact[index] == null ? defaultValue : _BankContact[index];
   }
    
   /**
    * Gets the array of Bank Contact Person fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Contact Person values.
    */
   public final String[] getBankContactArray()
   {
      return _BankContact;
   }
    
   /**
    * Gets the Bank Address Country Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Address Country Code or null.
    */
   public final String getBankCntry( int index )
   {
      return _BankCntry[index];
   }
    
   /**
    * Gets the Bank Address Country Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Address Country Code or the specified default value.
    */
   public final String getBankCntry( int index, String defaultValue )
   {
      return _BankCntry[index] == null ? defaultValue : _BankCntry[index];
   }
    
   /**
    * Gets the array of Bank Address Country Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Address Country Code values.
    */
   public final String[] getBankCntryArray()
   {
      return _BankCntry;
   }
    
   /**
    * Gets the Bank Address Postal Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Address Postal Code or null.
    */
   public final String getBankPstl( int index )
   {
      return _BankPstl[index];
   }
    
   /**
    * Gets the Bank Address Postal Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Address Postal Code or the specified default value.
    */
   public final String getBankPstl( int index, String defaultValue )
   {
      return _BankPstl[index] == null ? defaultValue : _BankPstl[index];
   }
    
   /**
    * Gets the array of Bank Address Postal Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Address Postal Code values.
    */
   public final String[] getBankPstlArray()
   {
      return _BankPstl;
   }
    
   /**
    * Gets the Expected Fee field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Expected Fee or null.
    */
   public final String getVUBExpectedAmt( int index )
   {
      return _VUBExpectedAmt[index];
   }
    
   /**
    * Gets the Expected Fee field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Expected Fee or the specified default value.
    */
   public final String getVUBExpectedAmt( int index, String defaultValue )
   {
      return _VUBExpectedAmt[index] == null ? defaultValue : _VUBExpectedAmt[index];
   }
    
   /**
    * Gets the array of Expected Fee fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Expected Fee values.
    */
   public final String[] getVUBExpectedAmtArray()
   {
      return _VUBExpectedAmt;
   }
    
   /**
    * Gets the Collected Fee field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Collected Fee or null.
    */
   public final String getVUBCollectedAmt( int index )
   {
      return _VUBCollectedAmt[index];
   }
    
   /**
    * Gets the Collected Fee field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Collected Fee or the specified default value.
    */
   public final String getVUBCollectedAmt( int index, String defaultValue )
   {
      return _VUBCollectedAmt[index] == null ? defaultValue : _VUBCollectedAmt[index];
   }
    
   /**
    * Gets the array of Collected Fee fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Collected Fee values.
    */
   public final String[] getVUBCollectedAmtArray()
   {
      return _VUBCollectedAmt;
   }
    
   /**
    * Gets the Plan Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Plan Code or null.
    */
   public final String getPlanCode( int index )
   {
      return _PlanCode[index];
   }
    
   /**
    * Gets the Plan Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Plan Code or the specified default value.
    */
   public final String getPlanCode( int index, String defaultValue )
   {
      return _PlanCode[index] == null ? defaultValue : _PlanCode[index];
   }
    
   /**
    * Gets the array of Plan Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Plan Code values.
    */
   public final String[] getPlanCodeArray()
   {
      return _PlanCode;
   }
    
   /**
    * Gets the Indicates if PAC has indexing info field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Indicates if PAC has indexing info or null.
    */
   public final Boolean getIndexExist( int index )
   {
      return _IndexExist[index];
   }
    
   /**
    * Gets the Indicates if PAC has indexing info field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Indicates if PAC has indexing info or the specified default value.
    */
   public final boolean getIndexExist( int index, boolean defaultValue )
   {
      return _IndexExist[index] == null ? defaultValue : _IndexExist[index].booleanValue();
   }
    
   /**
    * Gets the array of Indicates if PAC has indexing info fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Indicates if PAC has indexing info values.
    */
   public final Boolean[] getIndexExistArray()
   {
      return _IndexExist;
   }
    
   /**
    * Gets the First Contribution field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the First Contribution or null.
    */
   public final String getInitialAmt( int index )
   {
      return _InitialAmt[index];
   }
    
   /**
    * Gets the First Contribution field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the First Contribution or the specified default value.
    */
   public final String getInitialAmt( int index, String defaultValue )
   {
      return _InitialAmt[index] == null ? defaultValue : _InitialAmt[index];
   }
    
   /**
    * Gets the array of First Contribution fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of First Contribution values.
    */
   public final String[] getInitialAmtArray()
   {
      return _InitialAmt;
   }
    
   /**
    * Gets the Inital, Monthly or Waived field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Inital, Monthly or Waived or null.
    */
   public final String getVUBPayOption( int index )
   {
      return _VUBPayOption[index];
   }
    
   /**
    * Gets the Inital, Monthly or Waived field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Inital, Monthly or Waived or the specified default value.
    */
   public final String getVUBPayOption( int index, String defaultValue )
   {
      return _VUBPayOption[index] == null ? defaultValue : _VUBPayOption[index];
   }
    
   /**
    * Gets the array of Inital, Monthly or Waived fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Inital, Monthly or Waived values.
    */
   public final String[] getVUBPayOptionArray()
   {
      return _VUBPayOption;
   }
    
   /**
    * Gets the Annual Maintenance Fee Applies Y/N field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Annual Maintenance Fee Applies Y/N or null.
    */
   public final Boolean getAnnualMaint( int index )
   {
      return _AnnualMaint[index];
   }
    
   /**
    * Gets the Annual Maintenance Fee Applies Y/N field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Annual Maintenance Fee Applies Y/N or the specified default value.
    */
   public final boolean getAnnualMaint( int index, boolean defaultValue )
   {
      return _AnnualMaint[index] == null ? defaultValue : _AnnualMaint[index].booleanValue();
   }
    
   /**
    * Gets the array of Annual Maintenance Fee Applies Y/N fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Annual Maintenance Fee Applies Y/N values.
    */
   public final Boolean[] getAnnualMaintArray()
   {
      return _AnnualMaint;
   }
    
   /**
    * Gets the Saving Plan Fee Type - P(ercent) or F(raction) field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Saving Plan Fee Type - P(ercent) or F(raction) or null.
    */
   public final String getVUBFeeType( int index )
   {
      return _VUBFeeType[index];
   }
    
   /**
    * Gets the Saving Plan Fee Type - P(ercent) or F(raction) field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Saving Plan Fee Type - P(ercent) or F(raction) or the specified default value.
    */
   public final String getVUBFeeType( int index, String defaultValue )
   {
      return _VUBFeeType[index] == null ? defaultValue : _VUBFeeType[index];
   }
    
   /**
    * Gets the array of Saving Plan Fee Type - P(ercent) or F(raction) fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Saving Plan Fee Type - P(ercent) or F(raction) values.
    */
   public final String[] getVUBFeeTypeArray()
   {
      return _VUBFeeType;
   }
    
   /**
    * Gets the Fraction Value 1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fraction Value 1 or null.
    */
   public final Integer getVUBFeeFrac1( int index )
   {
      return _VUBFeeFrac1[index];
   }
    
   /**
    * Gets the Fraction Value 1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fraction Value 1 or the specified default value.
    */
   public final int getVUBFeeFrac1( int index, int defaultValue )
   {
      return _VUBFeeFrac1[index] == null ? defaultValue : _VUBFeeFrac1[index].intValue();
   }
    
   /**
    * Gets the array of Fraction Value 1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fraction Value 1 values.
    */
   public final Integer[] getVUBFeeFrac1Array()
   {
      return _VUBFeeFrac1;
   }
    
   /**
    * Gets the Fraction Value 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fraction Value 2 or null.
    */
   public final Integer getVUBFeeFrac2( int index )
   {
      return _VUBFeeFrac2[index];
   }
    
   /**
    * Gets the Fraction Value 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fraction Value 2 or the specified default value.
    */
   public final int getVUBFeeFrac2( int index, int defaultValue )
   {
      return _VUBFeeFrac2[index] == null ? defaultValue : _VUBFeeFrac2[index].intValue();
   }
    
   /**
    * Gets the array of Fraction Value 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fraction Value 2 values.
    */
   public final Integer[] getVUBFeeFrac2Array()
   {
      return _VUBFeeFrac2;
   }
    
   /**
    * Gets the Anniversary of Savings Plan field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Anniversary of Savings Plan or null.
    */
   public final Date getAnnualFeeDate( int index )
   {
      return _AnnualFeeDate[index];
   }
    
   /**
    * Gets the Anniversary of Savings Plan field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Anniversary of Savings Plan or the specified default value.
    */
   public final Date getAnnualFeeDate( int index, Date defaultValue )
   {
      return _AnnualFeeDate[index] == null ? defaultValue : _AnnualFeeDate[index];
   }
    
   /**
    * Gets the array of Anniversary of Savings Plan fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Anniversary of Savings Plan values.
    */
   public final Date[] getAnnualFeeDateArray()
   {
      return _AnnualFeeDate;
   }
    
   /**
    * Gets the Percent Value field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Percent Value or null.
    */
   public final String getVUBFeeRate( int index )
   {
      return _VUBFeeRate[index];
   }
    
   /**
    * Gets the Percent Value field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Percent Value or the specified default value.
    */
   public final String getVUBFeeRate( int index, String defaultValue )
   {
      return _VUBFeeRate[index] == null ? defaultValue : _VUBFeeRate[index];
   }
    
   /**
    * Gets the array of Percent Value fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Percent Value values.
    */
   public final String[] getVUBFeeRateArray()
   {
      return _VUBFeeRate;
   }
    
   /**
    * Gets the Fee on In side of Exchange field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fee on In side of Exchange or null.
    */
   public final String getExchInFee( int index )
   {
      return _ExchInFee[index];
   }
    
   /**
    * Gets the Fee on In side of Exchange field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee on In side of Exchange or the specified default value.
    */
   public final String getExchInFee( int index, String defaultValue )
   {
      return _ExchInFee[index] == null ? defaultValue : _ExchInFee[index];
   }
    
   /**
    * Gets the array of Fee on In side of Exchange fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee on In side of Exchange values.
    */
   public final String[] getExchInFeeArray()
   {
      return _ExchInFee;
   }
    
   /**
    * Gets the Fee on In side is Flat (Yes) field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fee on In side is Flat (Yes) or null.
    */
   public final Boolean getExchInFlatPercent( int index )
   {
      return _ExchInFlatPercent[index];
   }
    
   /**
    * Gets the Fee on In side is Flat (Yes) field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee on In side is Flat (Yes) or the specified default value.
    */
   public final boolean getExchInFlatPercent( int index, boolean defaultValue )
   {
      return _ExchInFlatPercent[index] == null ? defaultValue : _ExchInFlatPercent[index].booleanValue();
   }
    
   /**
    * Gets the array of Fee on In side is Flat (Yes) fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee on In side is Flat (Yes) values.
    */
   public final Boolean[] getExchInFlatPercentArray()
   {
      return _ExchInFlatPercent;
   }
    
   /**
    * Gets the flag indicating if record can be modified field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the flag indicating if record can be modified or null.
    */
   public final Boolean getModPerm( int index )
   {
      return _ModPerm[index];
   }
    
   /**
    * Gets the flag indicating if record can be modified field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the flag indicating if record can be modified or the specified default value.
    */
   public final boolean getModPerm( int index, boolean defaultValue )
   {
      return _ModPerm[index] == null ? defaultValue : _ModPerm[index].booleanValue();
   }
    
   /**
    * Gets the array of flag indicating if record can be modified fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of flag indicating if record can be modified values.
    */
   public final Boolean[] getModPermArray()
   {
      return _ModPerm;
   }
    
   /**
    * Gets the Exchange Out Fee field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Exchange Out Fee or null.
    */
   public final String getExchOutFee( int index )
   {
      return _ExchOutFee[index];
   }
    
   /**
    * Gets the Exchange Out Fee field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Exchange Out Fee or the specified default value.
    */
   public final String getExchOutFee( int index, String defaultValue )
   {
      return _ExchOutFee[index] == null ? defaultValue : _ExchOutFee[index];
   }
    
   /**
    * Gets the array of Exchange Out Fee fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Exchange Out Fee values.
    */
   public final String[] getExchOutFeeArray()
   {
      return _ExchOutFee;
   }
    
   /**
    * Gets the Exchange Out Flat/Prcnt field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Exchange Out Flat/Prcnt or null.
    */
   public final Boolean getExchOutFlatPrcnt( int index )
   {
      return _ExchOutFlatPrcnt[index];
   }
    
   /**
    * Gets the Exchange Out Flat/Prcnt field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Exchange Out Flat/Prcnt or the specified default value.
    */
   public final boolean getExchOutFlatPrcnt( int index, boolean defaultValue )
   {
      return _ExchOutFlatPrcnt[index] == null ? defaultValue : _ExchOutFlatPrcnt[index].booleanValue();
   }
    
   /**
    * Gets the array of Exchange Out Flat/Prcnt fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Exchange Out Flat/Prcnt values.
    */
   public final Boolean[] getExchOutFlatPrcntArray()
   {
      return _ExchOutFlatPrcnt;
   }
    
   /**
    * Gets the Payment Method field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Payment Method or null.
    */
   public final String getPayMethod( int index )
   {
      return _PayMethod[index];
   }
    
   /**
    * Gets the Payment Method field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payment Method or the specified default value.
    */
   public final String getPayMethod( int index, String defaultValue )
   {
      return _PayMethod[index] == null ? defaultValue : _PayMethod[index];
   }
    
   /**
    * Gets the array of Payment Method fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Payment Method values.
    */
   public final String[] getPayMethodArray()
   {
      return _PayMethod;
   }
    
   /**
    * Gets the Override Federal Tax PUD field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Override Federal Tax PUD or null.
    */
   public final String getFedTaxPUDOverride( int index )
   {
      return _FedTaxPUDOverride[index];
   }
    
   /**
    * Gets the Override Federal Tax PUD field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Override Federal Tax PUD or the specified default value.
    */
   public final String getFedTaxPUDOverride( int index, String defaultValue )
   {
      return _FedTaxPUDOverride[index] == null ? defaultValue : _FedTaxPUDOverride[index];
   }
    
   /**
    * Gets the array of Override Federal Tax PUD fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Override Federal Tax PUD values.
    */
   public final String[] getFedTaxPUDOverrideArray()
   {
      return _FedTaxPUDOverride;
   }
    
   /**
    * Gets the Federal Tax Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Federal Tax Rate or null.
    */
   public final String getFedRate( int index )
   {
      return _FedRate[index];
   }
    
   /**
    * Gets the Federal Tax Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Federal Tax Rate or the specified default value.
    */
   public final String getFedRate( int index, String defaultValue )
   {
      return _FedRate[index] == null ? defaultValue : _FedRate[index];
   }
    
   /**
    * Gets the array of Federal Tax Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Federal Tax Rate values.
    */
   public final String[] getFedRateArray()
   {
      return _FedRate;
   }
    
   /**
    * Gets the Override Provisional Tax PUD field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Override Provisional Tax PUD or null.
    */
   public final String getProvTaxPUDOverride( int index )
   {
      return _ProvTaxPUDOverride[index];
   }
    
   /**
    * Gets the Override Provisional Tax PUD field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Override Provisional Tax PUD or the specified default value.
    */
   public final String getProvTaxPUDOverride( int index, String defaultValue )
   {
      return _ProvTaxPUDOverride[index] == null ? defaultValue : _ProvTaxPUDOverride[index];
   }
    
   /**
    * Gets the array of Override Provisional Tax PUD fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Override Provisional Tax PUD values.
    */
   public final String[] getProvTaxPUDOverrideArray()
   {
      return _ProvTaxPUDOverride;
   }
    
   /**
    * Gets the Provisional Tax Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Provisional Tax Rate or null.
    */
   public final String getProvRate( int index )
   {
      return _ProvRate[index];
   }
    
   /**
    * Gets the Provisional Tax Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Provisional Tax Rate or the specified default value.
    */
   public final String getProvRate( int index, String defaultValue )
   {
      return _ProvRate[index] == null ? defaultValue : _ProvRate[index];
   }
    
   /**
    * Gets the array of Provisional Tax Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Provisional Tax Rate values.
    */
   public final String[] getProvRateArray()
   {
      return _ProvRate;
   }
    
   /**
    * Gets the Pay Reason 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Pay Reason 2 or null.
    */
   public final String getPayReason2( int index )
   {
      return _PayReason2[index];
   }
    
   /**
    * Gets the Pay Reason 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pay Reason 2 or the specified default value.
    */
   public final String getPayReason2( int index, String defaultValue )
   {
      return _PayReason2[index] == null ? defaultValue : _PayReason2[index];
   }
    
   /**
    * Gets the array of Pay Reason 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Pay Reason 2 values.
    */
   public final String[] getPayReason2Array()
   {
      return _PayReason2;
   }
    
   /**
    * Gets the Stop Reason field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stop Reason or null.
    */
   public final String getStopReason( int index )
   {
      return _StopReason[index];
   }
    
   /**
    * Gets the Stop Reason field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Reason or the specified default value.
    */
   public final String getStopReason( int index, String defaultValue )
   {
      return _StopReason[index] == null ? defaultValue : _StopReason[index];
   }
    
   /**
    * Gets the array of Stop Reason fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stop Reason values.
    */
   public final String[] getStopReasonArray()
   {
      return _StopReason;
   }
    
   /**
    * Gets the Non Financial Confirm field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Non Financial Confirm or null.
    */
   public final String getNonFinConfirm( int index )
   {
      return _NonFinConfirm[index];
   }
    
   /**
    * Gets the Non Financial Confirm field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Non Financial Confirm or the specified default value.
    */
   public final String getNonFinConfirm( int index, String defaultValue )
   {
      return _NonFinConfirm[index] == null ? defaultValue : _NonFinConfirm[index];
   }
    
   /**
    * Gets the array of Non Financial Confirm fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Non Financial Confirm values.
    */
   public final String[] getNonFinConfirmArray()
   {
      return _NonFinConfirm;
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
    * Gets the RDR Advice field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RDR Advice or null.
    */
   public final String getRDRAdvice( int index )
   {
      return _RDRAdvice[index];
   }
    
   /**
    * Gets the RDR Advice field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RDR Advice or the specified default value.
    */
   public final String getRDRAdvice( int index, String defaultValue )
   {
      return _RDRAdvice[index] == null ? defaultValue : _RDRAdvice[index];
   }
    
   /**
    * Gets the array of RDR Advice fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RDR Advice values.
    */
   public final String[] getRDRAdviceArray()
   {
      return _RDRAdvice;
   }
    
   /**
    * Gets the Event Receipt Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Event Receipt Date or null.
    */
   public final Date getEventReceiptDate( int index )
   {
      return _EventReceiptDate[index];
   }
    
   /**
    * Gets the Event Receipt Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Event Receipt Date or the specified default value.
    */
   public final Date getEventReceiptDate( int index, Date defaultValue )
   {
      return _EventReceiptDate[index] == null ? defaultValue : _EventReceiptDate[index];
   }
    
   /**
    * Gets the array of Event Receipt Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Event Receipt Date values.
    */
   public final Date[] getEventReceiptDateArray()
   {
      return _EventReceiptDate;
   }
    
   /**
    * Gets the Event Receipt Time field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Event Receipt Time or null.
    */
   public final String getEventReceiptTime( int index )
   {
      return _EventReceiptTime[index];
   }
    
   /**
    * Gets the Event Receipt Time field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Event Receipt Time or the specified default value.
    */
   public final String getEventReceiptTime( int index, String defaultValue )
   {
      return _EventReceiptTime[index] == null ? defaultValue : _EventReceiptTime[index];
   }
    
   /**
    * Gets the array of Event Receipt Time fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Event Receipt Time values.
    */
   public final String[] getEventReceiptTimeArray()
   {
      return _EventReceiptTime;
   }
    
   /**
    * Gets the SourceOfTrade field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SourceOfTrade or null.
    */
   public final String getSourceOfTrade( int index )
   {
      return _SourceOfTrade[index];
   }
    
   /**
    * Gets the SourceOfTrade field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SourceOfTrade or the specified default value.
    */
   public final String getSourceOfTrade( int index, String defaultValue )
   {
      return _SourceOfTrade[index] == null ? defaultValue : _SourceOfTrade[index];
   }
    
   /**
    * Gets the array of SourceOfTrade fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SourceOfTrade values.
    */
   public final String[] getSourceOfTradeArray()
   {
      return _SourceOfTrade;
   }
    
   /**
    * Gets the ChannelOfTrade field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ChannelOfTrade or null.
    */
   public final String getChannelOfTrade( int index )
   {
      return _ChannelOfTrade[index];
   }
    
   /**
    * Gets the ChannelOfTrade field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ChannelOfTrade or the specified default value.
    */
   public final String getChannelOfTrade( int index, String defaultValue )
   {
      return _ChannelOfTrade[index] == null ? defaultValue : _ChannelOfTrade[index];
   }
    
   /**
    * Gets the array of ChannelOfTrade fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ChannelOfTrade values.
    */
   public final String[] getChannelOfTradeArray()
   {
      return _ChannelOfTrade;
   }
    
   /**
    * Gets the Platform field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Platform or null.
    */
   public final String getPlatform( int index )
   {
      return _Platform[index];
   }
    
   /**
    * Gets the Platform field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Platform or the specified default value.
    */
   public final String getPlatform( int index, String defaultValue )
   {
      return _Platform[index] == null ? defaultValue : _Platform[index];
   }
    
   /**
    * Gets the array of Platform fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Platform values.
    */
   public final String[] getPlatformArray()
   {
      return _Platform;
   }
    
   /**
    * Gets the PSDAdvice field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the PSDAdvice or null.
    */
   public final String getPSDAdvice( int index )
   {
      return _PSDAdvice[index];
   }
    
   /**
    * Gets the PSDAdvice field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PSDAdvice or the specified default value.
    */
   public final String getPSDAdvice( int index, String defaultValue )
   {
      return _PSDAdvice[index] == null ? defaultValue : _PSDAdvice[index];
   }
    
   /**
    * Gets the array of PSDAdvice fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of PSDAdvice values.
    */
   public final String[] getPSDAdviceArray()
   {
      return _PSDAdvice;
   }
    
   /**
    * Gets the SignatureDate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SignatureDate or null.
    */
   public final Date getSignatureDate( int index )
   {
      return _SignatureDate[index];
   }
    
   /**
    * Gets the SignatureDate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SignatureDate or the specified default value.
    */
   public final Date getSignatureDate( int index, Date defaultValue )
   {
      return _SignatureDate[index] == null ? defaultValue : _SignatureDate[index];
   }
    
   /**
    * Gets the array of SignatureDate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SignatureDate values.
    */
   public final Date[] getSignatureDateArray()
   {
      return _SignatureDate;
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
      
      _BrokerCode = resizeArray( _BrokerCode, _RepeatCount );
      _BranchCode = resizeArray( _BranchCode, _RepeatCount );
      _SalesrepCode = resizeArray( _SalesrepCode, _RepeatCount );
      _BrokerName = resizeArray( _BrokerName, _RepeatCount );
      _BranchName = resizeArray( _BranchName, _RepeatCount );
      _SlsrepName = resizeArray( _SlsrepName, _RepeatCount );
      _Amount = resizeArray( _Amount, _RepeatCount );
      _AmountType = resizeArray( _AmountType, _RepeatCount );
      _AmountTypeDesc = resizeArray( _AmountTypeDesc, _RepeatCount );
      _GrossOrNet = resizeArray( _GrossOrNet, _RepeatCount );
      _Fee = resizeArray( _Fee, _RepeatCount );
      _FlatPercent = resizeArray( _FlatPercent, _RepeatCount );
      _FeeCurrency = resizeArray( _FeeCurrency, _RepeatCount );
      _FeeCurrDesc = resizeArray( _FeeCurrDesc, _RepeatCount );
      _AdminFeeAmt = resizeArray( _AdminFeeAmt, _RepeatCount );
      _AdminFeeCurr = resizeArray( _AdminFeeCurr, _RepeatCount );
      _AdminFeeCurrDesc = resizeArray( _AdminFeeCurrDesc, _RepeatCount );
      _PayType = resizeArray( _PayType, _RepeatCount );
      _PayTypeDesc = resizeArray( _PayTypeDesc, _RepeatCount );
      _InstCode = resizeArray( _InstCode, _RepeatCount );
      _SwiftCode = resizeArray( _SwiftCode, _RepeatCount );
      _RefNumber = resizeArray( _RefNumber, _RepeatCount );
      _TransitNo = resizeArray( _TransitNo, _RepeatCount );
      _BankAcctNum = resizeArray( _BankAcctNum, _RepeatCount );
      _BankAcctName = resizeArray( _BankAcctName, _RepeatCount );
      _SourceOfBankAcct = resizeArray( _SourceOfBankAcct, _RepeatCount );
      _BankAcctCurrency = resizeArray( _BankAcctCurrency, _RepeatCount );
      _BankCurrDesc = resizeArray( _BankCurrDesc, _RepeatCount );
      _BankAcctType = resizeArray( _BankAcctType, _RepeatCount );
      _BankAcctTypeDesc = resizeArray( _BankAcctTypeDesc, _RepeatCount );
      _SrcOfFund = resizeArray( _SrcOfFund, _RepeatCount );
      _SrcOFFundDesc = resizeArray( _SrcOFFundDesc, _RepeatCount );
      _January = resizeArray( _January, _RepeatCount );
      _February = resizeArray( _February, _RepeatCount );
      _March = resizeArray( _March, _RepeatCount );
      _April = resizeArray( _April, _RepeatCount );
      _May = resizeArray( _May, _RepeatCount );
      _June = resizeArray( _June, _RepeatCount );
      _July = resizeArray( _July, _RepeatCount );
      _August = resizeArray( _August, _RepeatCount );
      _September = resizeArray( _September, _RepeatCount );
      _October = resizeArray( _October, _RepeatCount );
      _November = resizeArray( _November, _RepeatCount );
      _December = resizeArray( _December, _RepeatCount );
      _EndOfMonth = resizeArray( _EndOfMonth, _RepeatCount );
      _DayOfWeek = resizeArray( _DayOfWeek, _RepeatCount );
      _LastProcessDate = resizeArray( _LastProcessDate, _RepeatCount );
      _AddrCode = resizeArray( _AddrCode, _RepeatCount );
      _GoodBad = resizeArray( _GoodBad, _RepeatCount );
      _EffectiveDate = resizeArray( _EffectiveDate, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _StopDate = resizeArray( _StopDate, _RepeatCount );
      _Username = resizeArray( _Username, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _AddrLine1 = resizeArray( _AddrLine1, _RepeatCount );
      _AddrLine2 = resizeArray( _AddrLine2, _RepeatCount );
      _AddrLine3 = resizeArray( _AddrLine3, _RepeatCount );
      _AddrLine4 = resizeArray( _AddrLine4, _RepeatCount );
      _AddrLine5 = resizeArray( _AddrLine5, _RepeatCount );
      _PostalCode = resizeArray( _PostalCode, _RepeatCount );
      _InstName = resizeArray( _InstName, _RepeatCount );
      _SlsrepAltName = resizeArray( _SlsrepAltName, _RepeatCount );
      _FundCode = resizeArray( _FundCode, _RepeatCount );
      _ClassCode = resizeArray( _ClassCode, _RepeatCount );
      _PACSWPId = resizeArray( _PACSWPId, _RepeatCount );
      _TransType = resizeArray( _TransType, _RepeatCount );
      _VersionNum = resizeArray( _VersionNum, _RepeatCount );
      _PayReason1 = resizeArray( _PayReason1, _RepeatCount );
      _FundToCode = resizeArray( _FundToCode, _RepeatCount );
      _ClassToCode = resizeArray( _ClassToCode, _RepeatCount );
      _AccountTo = resizeArray( _AccountTo, _RepeatCount );
      _BELFee = resizeArray( _BELFee, _RepeatCount );
      _BatchUser = resizeArray( _BatchUser, _RepeatCount );
      _Batch = resizeArray( _Batch, _RepeatCount );
      _BatchTrace = resizeArray( _BatchTrace, _RepeatCount );
      _BatchDate = resizeArray( _BatchDate, _RepeatCount );
      _TransferType = resizeArray( _TransferType, _RepeatCount );
      _Frequency = resizeArray( _Frequency, _RepeatCount );
      _FlatPercentDesc = resizeArray( _FlatPercentDesc, _RepeatCount );
      _FrequencyDesc = resizeArray( _FrequencyDesc, _RepeatCount );
      _TransferTypeDesc = resizeArray( _TransferTypeDesc, _RepeatCount );
      _EntityType = resizeArray( _EntityType, _RepeatCount );
      _EntityTypeSeq = resizeArray( _EntityTypeSeq, _RepeatCount );
      _TransNum = resizeArray( _TransNum, _RepeatCount );
      _SplitComm = resizeArray( _SplitComm, _RepeatCount );
      _NextProcessDate = resizeArray( _NextProcessDate, _RepeatCount );
      _BankType = resizeArray( _BankType, _RepeatCount );
      _BankIdNum = resizeArray( _BankIdNum, _RepeatCount );
      _ACHProcessor = resizeArray( _ACHProcessor, _RepeatCount );
      _BankId = resizeArray( _BankId, _RepeatCount );
      _CreditInfoLine1 = resizeArray( _CreditInfoLine1, _RepeatCount );
      _CreditInfoLine2 = resizeArray( _CreditInfoLine2, _RepeatCount );
      _BankAddr1 = resizeArray( _BankAddr1, _RepeatCount );
      _BankAddr2 = resizeArray( _BankAddr2, _RepeatCount );
      _BankAddr3 = resizeArray( _BankAddr3, _RepeatCount );
      _BankAddr4 = resizeArray( _BankAddr4, _RepeatCount );
      _BankAddr5 = resizeArray( _BankAddr5, _RepeatCount );
      _BankContact = resizeArray( _BankContact, _RepeatCount );
      _BankCntry = resizeArray( _BankCntry, _RepeatCount );
      _BankPstl = resizeArray( _BankPstl, _RepeatCount );
      _VUBExpectedAmt = resizeArray( _VUBExpectedAmt, _RepeatCount );
      _VUBCollectedAmt = resizeArray( _VUBCollectedAmt, _RepeatCount );
      _PlanCode = resizeArray( _PlanCode, _RepeatCount );
      _IndexExist = resizeArray( _IndexExist, _RepeatCount );
      _InitialAmt = resizeArray( _InitialAmt, _RepeatCount );
      _VUBPayOption = resizeArray( _VUBPayOption, _RepeatCount );
      _AnnualMaint = resizeArray( _AnnualMaint, _RepeatCount );
      _VUBFeeType = resizeArray( _VUBFeeType, _RepeatCount );
      _VUBFeeFrac1 = resizeArray( _VUBFeeFrac1, _RepeatCount );
      _VUBFeeFrac2 = resizeArray( _VUBFeeFrac2, _RepeatCount );
      _AnnualFeeDate = resizeArray( _AnnualFeeDate, _RepeatCount );
      _VUBFeeRate = resizeArray( _VUBFeeRate, _RepeatCount );
      _ExchInFee = resizeArray( _ExchInFee, _RepeatCount );
      _ExchInFlatPercent = resizeArray( _ExchInFlatPercent, _RepeatCount );
      _ModPerm = resizeArray( _ModPerm, _RepeatCount );
      _ExchOutFee = resizeArray( _ExchOutFee, _RepeatCount );
      _ExchOutFlatPrcnt = resizeArray( _ExchOutFlatPrcnt, _RepeatCount );
      _PayMethod = resizeArray( _PayMethod, _RepeatCount );
      _FedTaxPUDOverride = resizeArray( _FedTaxPUDOverride, _RepeatCount );
      _FedRate = resizeArray( _FedRate, _RepeatCount );
      _ProvTaxPUDOverride = resizeArray( _ProvTaxPUDOverride, _RepeatCount );
      _ProvRate = resizeArray( _ProvRate, _RepeatCount );
      _PayReason2 = resizeArray( _PayReason2, _RepeatCount );
      _StopReason = resizeArray( _StopReason, _RepeatCount );
      _NonFinConfirm = resizeArray( _NonFinConfirm, _RepeatCount );
      _VerifyStat = resizeArray( _VerifyStat, _RepeatCount );
      _RDRAdvice = resizeArray( _RDRAdvice, _RepeatCount );
      _EventReceiptDate = resizeArray( _EventReceiptDate, _RepeatCount );
      _EventReceiptTime = resizeArray( _EventReceiptTime, _RepeatCount );
      _SourceOfTrade = resizeArray( _SourceOfTrade, _RepeatCount );
      _ChannelOfTrade = resizeArray( _ChannelOfTrade, _RepeatCount );
      _Platform = resizeArray( _Platform, _RepeatCount );
      _PSDAdvice = resizeArray( _PSDAdvice, _RepeatCount );
      _SignatureDate = resizeArray( _SignatureDate, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _BrokerCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BranchCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SalesrepCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BrokerName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BranchName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SlsrepName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Amount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AmountType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AmountTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GrossOrNet[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _Fee[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FlatPercent[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FeeCurrency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FeeCurrDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AdminFeeAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AdminFeeCurr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AdminFeeCurrDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PayType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PayTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _InstCode[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _SwiftCode[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _RefNumber[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _TransitNo[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _BankAcctNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAcctName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SourceOfBankAcct[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAcctCurrency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankCurrDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAcctType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAcctTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SrcOfFund[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SrcOFFundDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _January[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _February[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _March[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _April[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _May[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _June[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _July[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _August[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _September[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _October[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _November[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _December[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _EndOfMonth[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _DayOfWeek[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _LastProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _AddrCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GoodBad[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _StopDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _Username[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine3[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine4[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine5[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PostalCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _InstName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SlsrepAltName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PACSWPId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _TransType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _VersionNum[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _PayReason1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundToCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClassToCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AccountTo[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BELFee[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _BatchUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Batch[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BatchTrace[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _BatchDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _TransferType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Frequency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FlatPercentDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FrequencyDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TransferTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EntityType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EntityTypeSeq[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _TransNum[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _SplitComm[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _NextProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _BankType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankIdNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ACHProcessor[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _CreditInfoLine1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CreditInfoLine2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAddr1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAddr2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAddr3[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAddr4[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAddr5[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankContact[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankCntry[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankPstl[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _VUBExpectedAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _VUBCollectedAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PlanCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IndexExist[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _InitialAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _VUBPayOption[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AnnualMaint[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _VUBFeeType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _VUBFeeFrac1[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _VUBFeeFrac2[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _AnnualFeeDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _VUBFeeRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ExchInFee[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ExchInFlatPercent[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ModPerm[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ExchOutFee[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ExchOutFlatPrcnt[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _PayMethod[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FedTaxPUDOverride[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FedRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProvTaxPUDOverride[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProvRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PayReason2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _StopReason[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _NonFinConfirm[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _VerifyStat[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RDRAdvice[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EventReceiptDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _EventReceiptTime[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SourceOfTrade[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ChannelOfTrade[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Platform[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PSDAdvice[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SignatureDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
      }
      

   }

}
      
