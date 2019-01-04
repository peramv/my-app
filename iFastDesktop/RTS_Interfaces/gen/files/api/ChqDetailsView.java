
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Cheque details view.
 * For additional view information see <A HREF="../../../../viewspecs/ChqDetails.doc">ChqDetails.doc</A>.
 * 
 * @author RTS Generated
 */
public class ChqDetailsView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Record Type member array.
    */
   private String[] _RecType = null;
   
   /**
    * ChequeNum member array.
    */
   private String[] _CheqNum = null;
   
   /**
    * Reference Number member array.
    */
   private Integer[] _RefNumber = null;
   
   /**
    * Fee Amount member array.
    */
   private String[] _Fee = null;
   
   /**
    * Federal Tax member array.
    */
   private String[] _FedTax = null;
   
   /**
    * Provincial Tax member array.
    */
   private String[] _ProvTax = null;
   
   /**
    * Amount on Cheque member array.
    */
   private String[] _Amount = null;
   
   /**
    * Fund Code member array.
    */
   private String[] _FundCode = null;
   
   /**
    * Class Code member array.
    */
   private String[] _ClassCode = null;
   
   /**
    * Transaction Number member array.
    */
   private Integer[] _TransNum = null;
   
   /**
    * Transaction Type member array.
    */
   private String[] _TransType = null;
   
   /**
    * Currency member array.
    */
   private String[] _Currency = null;
   
   /**
    * Salutation member array.
    */
   private String[] _Salutation = null;
   
   /**
    * Payee Name member array.
    */
   private String[] _PayeeName = null;
   
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
    * Broker Cheque member array.
    */
   private Boolean[] _BrokerChq = null;
   
   /**
    * Delivery Method member array.
    */
   private String[] _DeliveryCode = null;
   
   /**
    * Delivery Method Description member array.
    */
   private String[] _DeliveryCodeDesc = null;
   
   /**
    * Print Date member array.
    */
   private Date[] _PrintDate = null;
   
   /**
    * Age of Cheque member array.
    */
   private Integer[] _ChequeAge = null;
   
   /**
    * Bank Account Number member array.
    */
   private String[] _BankAcctNumt = null;
   
   /**
    * Bank Reconciliation Date member array.
    */
   private Date[] _BankRecDate = null;
   
   /**
    * Record Creation Date member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * Created by UserID member array.
    */
   private String[] _Username = null;
   
   /**
    * Modification Date member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * Modified by User member array.
    */
   private String[] _ModUser = null;
   
   /**
    * Cancelled Date member array.
    */
   private Date[] _CanDate = null;
   
   /**
    * Cancelled by User member array.
    */
   private String[] _CancelUser = null;
   
   /**
    * Cheque Status member array.
    */
   private String[] _ChqStatus = null;
   
   /**
    * Cheque Status Description member array.
    */
   private String[] _ChqStatDesc = null;
   
   /**
    * Account Number member array.
    */
   private String[] _rxAcctNum = null;
   
   /**
    * Memo1 member array.
    */
   private String[] _Memo1 = null;
   
   /**
    * Memo2 member array.
    */
   private String[] _Memo2 = null;
   
   /**
    * Country Code member array.
    */
   private String[] _CountryCode = null;
   
   /**
    * Country Name member array.
    */
   private String[] _CountryName = null;
   
   /**
    * Currency Name member array.
    */
   private String[] _CurrencyName = null;
   
   /**
    * Payment Type member array.
    */
   private String[] _PayType = null;
   
   /**
    * ClawBackTotal member array.
    */
   private String[] _ClawbackTotal = null;
   
   /**
    * Cheque Detl UUID member array.
    */
   private String[] _CheqDetlUUID = null;
   
   /**
    * Unclaim Stage member array.
    */
   private String[] _UnclmStage = null;
   
   /**
    * Stage Date member array.
    */
   private Date[] _StageDate = null;
   
   /**
    * Unclaim Remit Date member array.
    */
   private Date[] _UnclmRemitDate = null;
   
   /**
    * Comments member array.
    */
   private String[] _Comments = null;
   
   /**
    * Version Number member array.
    */
   private Integer[] _Version = null;
   
   /**
    * Indicates if stage was overridden member array.
    */
   private String[] _StageAssignBy = null;
   
   /**
    * Cheque Number of cheque remitted to the Government member array.
    */
   private String[] _GovtChqNo = null;
   
   /**
    * Issue Date of cheque remitted to the Government member array.
    */
   private Date[] _GovtChqIssueDate = null;
   
   /**
    * Currency of Cheque remitted to the Government member array.
    */
   private String[] _GovtChqCurrency = null;
   
   /**
    * Status of Cheque remitted to the Government member array.
    */
   private String[] _GovtChqStatus = null;
   

   /**
    * Constructs the ChqDetailsView object.
    * 
    */
   public ChqDetailsView()
   {
      super ( new ChqDetailsRequest() );
   }

   /**
    * Constructs the ChqDetailsView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public ChqDetailsView( String hostEncoding )
   {
      super ( new ChqDetailsRequest( hostEncoding ) );
   }

   /**
    * Gets the ChqDetailsRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The ChqDetailsRequest object.
    */
   public final ChqDetailsRequest getRequest()
   {
      return (ChqDetailsRequest)getIFastRequest();
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
    * Gets the Record Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Record Type or null.
    */
   public final String getRecType( int index )
   {
      return _RecType[index];
   }
    
   /**
    * Gets the Record Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Record Type or the specified default value.
    */
   public final String getRecType( int index, String defaultValue )
   {
      return _RecType[index] == null ? defaultValue : _RecType[index];
   }
    
   /**
    * Gets the array of Record Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Record Type values.
    */
   public final String[] getRecTypeArray()
   {
      return _RecType;
   }
    
   /**
    * Gets the ChequeNum field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ChequeNum or null.
    */
   public final String getCheqNum( int index )
   {
      return _CheqNum[index];
   }
    
   /**
    * Gets the ChequeNum field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ChequeNum or the specified default value.
    */
   public final String getCheqNum( int index, String defaultValue )
   {
      return _CheqNum[index] == null ? defaultValue : _CheqNum[index];
   }
    
   /**
    * Gets the array of ChequeNum fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ChequeNum values.
    */
   public final String[] getCheqNumArray()
   {
      return _CheqNum;
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
    * Gets the Fee Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fee Amount or null.
    */
   public final String getFee( int index )
   {
      return _Fee[index];
   }
    
   /**
    * Gets the Fee Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee Amount or the specified default value.
    */
   public final String getFee( int index, String defaultValue )
   {
      return _Fee[index] == null ? defaultValue : _Fee[index];
   }
    
   /**
    * Gets the array of Fee Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee Amount values.
    */
   public final String[] getFeeArray()
   {
      return _Fee;
   }
    
   /**
    * Gets the Federal Tax field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Federal Tax or null.
    */
   public final String getFedTax( int index )
   {
      return _FedTax[index];
   }
    
   /**
    * Gets the Federal Tax field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Federal Tax or the specified default value.
    */
   public final String getFedTax( int index, String defaultValue )
   {
      return _FedTax[index] == null ? defaultValue : _FedTax[index];
   }
    
   /**
    * Gets the array of Federal Tax fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Federal Tax values.
    */
   public final String[] getFedTaxArray()
   {
      return _FedTax;
   }
    
   /**
    * Gets the Provincial Tax field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Provincial Tax or null.
    */
   public final String getProvTax( int index )
   {
      return _ProvTax[index];
   }
    
   /**
    * Gets the Provincial Tax field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Provincial Tax or the specified default value.
    */
   public final String getProvTax( int index, String defaultValue )
   {
      return _ProvTax[index] == null ? defaultValue : _ProvTax[index];
   }
    
   /**
    * Gets the array of Provincial Tax fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Provincial Tax values.
    */
   public final String[] getProvTaxArray()
   {
      return _ProvTax;
   }
    
   /**
    * Gets the Amount on Cheque field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Amount on Cheque or null.
    */
   public final String getAmount( int index )
   {
      return _Amount[index];
   }
    
   /**
    * Gets the Amount on Cheque field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Amount on Cheque or the specified default value.
    */
   public final String getAmount( int index, String defaultValue )
   {
      return _Amount[index] == null ? defaultValue : _Amount[index];
   }
    
   /**
    * Gets the array of Amount on Cheque fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Amount on Cheque values.
    */
   public final String[] getAmountArray()
   {
      return _Amount;
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
    * Gets the Transaction Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transaction Type or null.
    */
   public final String getTransType( int index )
   {
      return _TransType[index];
   }
    
   /**
    * Gets the Transaction Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transaction Type or the specified default value.
    */
   public final String getTransType( int index, String defaultValue )
   {
      return _TransType[index] == null ? defaultValue : _TransType[index];
   }
    
   /**
    * Gets the array of Transaction Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transaction Type values.
    */
   public final String[] getTransTypeArray()
   {
      return _TransType;
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
    * Gets the Salutation field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Salutation or null.
    */
   public final String getSalutation( int index )
   {
      return _Salutation[index];
   }
    
   /**
    * Gets the Salutation field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Salutation or the specified default value.
    */
   public final String getSalutation( int index, String defaultValue )
   {
      return _Salutation[index] == null ? defaultValue : _Salutation[index];
   }
    
   /**
    * Gets the array of Salutation fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Salutation values.
    */
   public final String[] getSalutationArray()
   {
      return _Salutation;
   }
    
   /**
    * Gets the Payee Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Payee Name or null.
    */
   public final String getPayeeName( int index )
   {
      return _PayeeName[index];
   }
    
   /**
    * Gets the Payee Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payee Name or the specified default value.
    */
   public final String getPayeeName( int index, String defaultValue )
   {
      return _PayeeName[index] == null ? defaultValue : _PayeeName[index];
   }
    
   /**
    * Gets the array of Payee Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Payee Name values.
    */
   public final String[] getPayeeNameArray()
   {
      return _PayeeName;
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
    * Gets the Broker Cheque field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Broker Cheque or null.
    */
   public final Boolean getBrokerChq( int index )
   {
      return _BrokerChq[index];
   }
    
   /**
    * Gets the Broker Cheque field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker Cheque or the specified default value.
    */
   public final boolean getBrokerChq( int index, boolean defaultValue )
   {
      return _BrokerChq[index] == null ? defaultValue : _BrokerChq[index].booleanValue();
   }
    
   /**
    * Gets the array of Broker Cheque fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Broker Cheque values.
    */
   public final Boolean[] getBrokerChqArray()
   {
      return _BrokerChq;
   }
    
   /**
    * Gets the Delivery Method field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Delivery Method or null.
    */
   public final String getDeliveryCode( int index )
   {
      return _DeliveryCode[index];
   }
    
   /**
    * Gets the Delivery Method field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Delivery Method or the specified default value.
    */
   public final String getDeliveryCode( int index, String defaultValue )
   {
      return _DeliveryCode[index] == null ? defaultValue : _DeliveryCode[index];
   }
    
   /**
    * Gets the array of Delivery Method fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Delivery Method values.
    */
   public final String[] getDeliveryCodeArray()
   {
      return _DeliveryCode;
   }
    
   /**
    * Gets the Delivery Method Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Delivery Method Description or null.
    */
   public final String getDeliveryCodeDesc( int index )
   {
      return _DeliveryCodeDesc[index];
   }
    
   /**
    * Gets the Delivery Method Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Delivery Method Description or the specified default value.
    */
   public final String getDeliveryCodeDesc( int index, String defaultValue )
   {
      return _DeliveryCodeDesc[index] == null ? defaultValue : _DeliveryCodeDesc[index];
   }
    
   /**
    * Gets the array of Delivery Method Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Delivery Method Description values.
    */
   public final String[] getDeliveryCodeDescArray()
   {
      return _DeliveryCodeDesc;
   }
    
   /**
    * Gets the Print Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Print Date or null.
    */
   public final Date getPrintDate( int index )
   {
      return _PrintDate[index];
   }
    
   /**
    * Gets the Print Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Print Date or the specified default value.
    */
   public final Date getPrintDate( int index, Date defaultValue )
   {
      return _PrintDate[index] == null ? defaultValue : _PrintDate[index];
   }
    
   /**
    * Gets the array of Print Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Print Date values.
    */
   public final Date[] getPrintDateArray()
   {
      return _PrintDate;
   }
    
   /**
    * Gets the Age of Cheque field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Age of Cheque or null.
    */
   public final Integer getChequeAge( int index )
   {
      return _ChequeAge[index];
   }
    
   /**
    * Gets the Age of Cheque field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Age of Cheque or the specified default value.
    */
   public final int getChequeAge( int index, int defaultValue )
   {
      return _ChequeAge[index] == null ? defaultValue : _ChequeAge[index].intValue();
   }
    
   /**
    * Gets the array of Age of Cheque fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Age of Cheque values.
    */
   public final Integer[] getChequeAgeArray()
   {
      return _ChequeAge;
   }
    
   /**
    * Gets the Bank Account Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Account Number or null.
    */
   public final String getBankAcctNumt( int index )
   {
      return _BankAcctNumt[index];
   }
    
   /**
    * Gets the Bank Account Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Account Number or the specified default value.
    */
   public final String getBankAcctNumt( int index, String defaultValue )
   {
      return _BankAcctNumt[index] == null ? defaultValue : _BankAcctNumt[index];
   }
    
   /**
    * Gets the array of Bank Account Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Account Number values.
    */
   public final String[] getBankAcctNumtArray()
   {
      return _BankAcctNumt;
   }
    
   /**
    * Gets the Bank Reconciliation Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Reconciliation Date or null.
    */
   public final Date getBankRecDate( int index )
   {
      return _BankRecDate[index];
   }
    
   /**
    * Gets the Bank Reconciliation Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Reconciliation Date or the specified default value.
    */
   public final Date getBankRecDate( int index, Date defaultValue )
   {
      return _BankRecDate[index] == null ? defaultValue : _BankRecDate[index];
   }
    
   /**
    * Gets the array of Bank Reconciliation Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Reconciliation Date values.
    */
   public final Date[] getBankRecDateArray()
   {
      return _BankRecDate;
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
    * Gets the Created by UserID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Created by UserID or null.
    */
   public final String getUsername( int index )
   {
      return _Username[index];
   }
    
   /**
    * Gets the Created by UserID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Created by UserID or the specified default value.
    */
   public final String getUsername( int index, String defaultValue )
   {
      return _Username[index] == null ? defaultValue : _Username[index];
   }
    
   /**
    * Gets the array of Created by UserID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Created by UserID values.
    */
   public final String[] getUsernameArray()
   {
      return _Username;
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
    * Gets the Modified by User field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Modified by User or null.
    */
   public final String getModUser( int index )
   {
      return _ModUser[index];
   }
    
   /**
    * Gets the Modified by User field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Modified by User or the specified default value.
    */
   public final String getModUser( int index, String defaultValue )
   {
      return _ModUser[index] == null ? defaultValue : _ModUser[index];
   }
    
   /**
    * Gets the array of Modified by User fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Modified by User values.
    */
   public final String[] getModUserArray()
   {
      return _ModUser;
   }
    
   /**
    * Gets the Cancelled Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Cancelled Date or null.
    */
   public final Date getCanDate( int index )
   {
      return _CanDate[index];
   }
    
   /**
    * Gets the Cancelled Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Cancelled Date or the specified default value.
    */
   public final Date getCanDate( int index, Date defaultValue )
   {
      return _CanDate[index] == null ? defaultValue : _CanDate[index];
   }
    
   /**
    * Gets the array of Cancelled Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Cancelled Date values.
    */
   public final Date[] getCanDateArray()
   {
      return _CanDate;
   }
    
   /**
    * Gets the Cancelled by User field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Cancelled by User or null.
    */
   public final String getCancelUser( int index )
   {
      return _CancelUser[index];
   }
    
   /**
    * Gets the Cancelled by User field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Cancelled by User or the specified default value.
    */
   public final String getCancelUser( int index, String defaultValue )
   {
      return _CancelUser[index] == null ? defaultValue : _CancelUser[index];
   }
    
   /**
    * Gets the array of Cancelled by User fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Cancelled by User values.
    */
   public final String[] getCancelUserArray()
   {
      return _CancelUser;
   }
    
   /**
    * Gets the Cheque Status field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Cheque Status or null.
    */
   public final String getChqStatus( int index )
   {
      return _ChqStatus[index];
   }
    
   /**
    * Gets the Cheque Status field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Cheque Status or the specified default value.
    */
   public final String getChqStatus( int index, String defaultValue )
   {
      return _ChqStatus[index] == null ? defaultValue : _ChqStatus[index];
   }
    
   /**
    * Gets the array of Cheque Status fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Cheque Status values.
    */
   public final String[] getChqStatusArray()
   {
      return _ChqStatus;
   }
    
   /**
    * Gets the Cheque Status Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Cheque Status Description or null.
    */
   public final String getChqStatDesc( int index )
   {
      return _ChqStatDesc[index];
   }
    
   /**
    * Gets the Cheque Status Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Cheque Status Description or the specified default value.
    */
   public final String getChqStatDesc( int index, String defaultValue )
   {
      return _ChqStatDesc[index] == null ? defaultValue : _ChqStatDesc[index];
   }
    
   /**
    * Gets the array of Cheque Status Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Cheque Status Description values.
    */
   public final String[] getChqStatDescArray()
   {
      return _ChqStatDesc;
   }
    
   /**
    * Gets the Account Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Number or null.
    */
   public final String getrxAcctNum( int index )
   {
      return _rxAcctNum[index];
   }
    
   /**
    * Gets the Account Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Number or the specified default value.
    */
   public final String getrxAcctNum( int index, String defaultValue )
   {
      return _rxAcctNum[index] == null ? defaultValue : _rxAcctNum[index];
   }
    
   /**
    * Gets the array of Account Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Number values.
    */
   public final String[] getrxAcctNumArray()
   {
      return _rxAcctNum;
   }
    
   /**
    * Gets the Memo1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Memo1 or null.
    */
   public final String getMemo1( int index )
   {
      return _Memo1[index];
   }
    
   /**
    * Gets the Memo1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Memo1 or the specified default value.
    */
   public final String getMemo1( int index, String defaultValue )
   {
      return _Memo1[index] == null ? defaultValue : _Memo1[index];
   }
    
   /**
    * Gets the array of Memo1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Memo1 values.
    */
   public final String[] getMemo1Array()
   {
      return _Memo1;
   }
    
   /**
    * Gets the Memo2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Memo2 or null.
    */
   public final String getMemo2( int index )
   {
      return _Memo2[index];
   }
    
   /**
    * Gets the Memo2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Memo2 or the specified default value.
    */
   public final String getMemo2( int index, String defaultValue )
   {
      return _Memo2[index] == null ? defaultValue : _Memo2[index];
   }
    
   /**
    * Gets the array of Memo2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Memo2 values.
    */
   public final String[] getMemo2Array()
   {
      return _Memo2;
   }
    
   /**
    * Gets the Country Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Country Code or null.
    */
   public final String getCountryCode( int index )
   {
      return _CountryCode[index];
   }
    
   /**
    * Gets the Country Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Country Code or the specified default value.
    */
   public final String getCountryCode( int index, String defaultValue )
   {
      return _CountryCode[index] == null ? defaultValue : _CountryCode[index];
   }
    
   /**
    * Gets the array of Country Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Country Code values.
    */
   public final String[] getCountryCodeArray()
   {
      return _CountryCode;
   }
    
   /**
    * Gets the Country Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Country Name or null.
    */
   public final String getCountryName( int index )
   {
      return _CountryName[index];
   }
    
   /**
    * Gets the Country Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Country Name or the specified default value.
    */
   public final String getCountryName( int index, String defaultValue )
   {
      return _CountryName[index] == null ? defaultValue : _CountryName[index];
   }
    
   /**
    * Gets the array of Country Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Country Name values.
    */
   public final String[] getCountryNameArray()
   {
      return _CountryName;
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
    * Gets the Payment Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Payment Type or null.
    */
   public final String getPayType( int index )
   {
      return _PayType[index];
   }
    
   /**
    * Gets the Payment Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payment Type or the specified default value.
    */
   public final String getPayType( int index, String defaultValue )
   {
      return _PayType[index] == null ? defaultValue : _PayType[index];
   }
    
   /**
    * Gets the array of Payment Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Payment Type values.
    */
   public final String[] getPayTypeArray()
   {
      return _PayType;
   }
    
   /**
    * Gets the ClawBackTotal field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ClawBackTotal or null.
    */
   public final String getClawbackTotal( int index )
   {
      return _ClawbackTotal[index];
   }
    
   /**
    * Gets the ClawBackTotal field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ClawBackTotal or the specified default value.
    */
   public final String getClawbackTotal( int index, String defaultValue )
   {
      return _ClawbackTotal[index] == null ? defaultValue : _ClawbackTotal[index];
   }
    
   /**
    * Gets the array of ClawBackTotal fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ClawBackTotal values.
    */
   public final String[] getClawbackTotalArray()
   {
      return _ClawbackTotal;
   }
    
   /**
    * Gets the Cheque Detl UUID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Cheque Detl UUID or null.
    */
   public final String getCheqDetlUUID( int index )
   {
      return _CheqDetlUUID[index];
   }
    
   /**
    * Gets the Cheque Detl UUID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Cheque Detl UUID or the specified default value.
    */
   public final String getCheqDetlUUID( int index, String defaultValue )
   {
      return _CheqDetlUUID[index] == null ? defaultValue : _CheqDetlUUID[index];
   }
    
   /**
    * Gets the array of Cheque Detl UUID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Cheque Detl UUID values.
    */
   public final String[] getCheqDetlUUIDArray()
   {
      return _CheqDetlUUID;
   }
    
   /**
    * Gets the Unclaim Stage field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Unclaim Stage or null.
    */
   public final String getUnclmStage( int index )
   {
      return _UnclmStage[index];
   }
    
   /**
    * Gets the Unclaim Stage field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Unclaim Stage or the specified default value.
    */
   public final String getUnclmStage( int index, String defaultValue )
   {
      return _UnclmStage[index] == null ? defaultValue : _UnclmStage[index];
   }
    
   /**
    * Gets the array of Unclaim Stage fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Unclaim Stage values.
    */
   public final String[] getUnclmStageArray()
   {
      return _UnclmStage;
   }
    
   /**
    * Gets the Stage Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stage Date or null.
    */
   public final Date getStageDate( int index )
   {
      return _StageDate[index];
   }
    
   /**
    * Gets the Stage Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stage Date or the specified default value.
    */
   public final Date getStageDate( int index, Date defaultValue )
   {
      return _StageDate[index] == null ? defaultValue : _StageDate[index];
   }
    
   /**
    * Gets the array of Stage Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stage Date values.
    */
   public final Date[] getStageDateArray()
   {
      return _StageDate;
   }
    
   /**
    * Gets the Unclaim Remit Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Unclaim Remit Date or null.
    */
   public final Date getUnclmRemitDate( int index )
   {
      return _UnclmRemitDate[index];
   }
    
   /**
    * Gets the Unclaim Remit Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Unclaim Remit Date or the specified default value.
    */
   public final Date getUnclmRemitDate( int index, Date defaultValue )
   {
      return _UnclmRemitDate[index] == null ? defaultValue : _UnclmRemitDate[index];
   }
    
   /**
    * Gets the array of Unclaim Remit Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Unclaim Remit Date values.
    */
   public final Date[] getUnclmRemitDateArray()
   {
      return _UnclmRemitDate;
   }
    
   /**
    * Gets the Comments field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Comments or null.
    */
   public final String getComments( int index )
   {
      return _Comments[index];
   }
    
   /**
    * Gets the Comments field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Comments or the specified default value.
    */
   public final String getComments( int index, String defaultValue )
   {
      return _Comments[index] == null ? defaultValue : _Comments[index];
   }
    
   /**
    * Gets the array of Comments fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Comments values.
    */
   public final String[] getCommentsArray()
   {
      return _Comments;
   }
    
   /**
    * Gets the Version Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Version Number or null.
    */
   public final Integer getVersion( int index )
   {
      return _Version[index];
   }
    
   /**
    * Gets the Version Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Version Number or the specified default value.
    */
   public final int getVersion( int index, int defaultValue )
   {
      return _Version[index] == null ? defaultValue : _Version[index].intValue();
   }
    
   /**
    * Gets the array of Version Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Version Number values.
    */
   public final Integer[] getVersionArray()
   {
      return _Version;
   }
    
   /**
    * Gets the Indicates if stage was overridden field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Indicates if stage was overridden or null.
    */
   public final String getStageAssignBy( int index )
   {
      return _StageAssignBy[index];
   }
    
   /**
    * Gets the Indicates if stage was overridden field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Indicates if stage was overridden or the specified default value.
    */
   public final String getStageAssignBy( int index, String defaultValue )
   {
      return _StageAssignBy[index] == null ? defaultValue : _StageAssignBy[index];
   }
    
   /**
    * Gets the array of Indicates if stage was overridden fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Indicates if stage was overridden values.
    */
   public final String[] getStageAssignByArray()
   {
      return _StageAssignBy;
   }
    
   /**
    * Gets the Cheque Number of cheque remitted to the Government field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Cheque Number of cheque remitted to the Government or null.
    */
   public final String getGovtChqNo( int index )
   {
      return _GovtChqNo[index];
   }
    
   /**
    * Gets the Cheque Number of cheque remitted to the Government field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Cheque Number of cheque remitted to the Government or the specified default value.
    */
   public final String getGovtChqNo( int index, String defaultValue )
   {
      return _GovtChqNo[index] == null ? defaultValue : _GovtChqNo[index];
   }
    
   /**
    * Gets the array of Cheque Number of cheque remitted to the Government fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Cheque Number of cheque remitted to the Government values.
    */
   public final String[] getGovtChqNoArray()
   {
      return _GovtChqNo;
   }
    
   /**
    * Gets the Issue Date of cheque remitted to the Government field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Issue Date of cheque remitted to the Government or null.
    */
   public final Date getGovtChqIssueDate( int index )
   {
      return _GovtChqIssueDate[index];
   }
    
   /**
    * Gets the Issue Date of cheque remitted to the Government field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Issue Date of cheque remitted to the Government or the specified default value.
    */
   public final Date getGovtChqIssueDate( int index, Date defaultValue )
   {
      return _GovtChqIssueDate[index] == null ? defaultValue : _GovtChqIssueDate[index];
   }
    
   /**
    * Gets the array of Issue Date of cheque remitted to the Government fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Issue Date of cheque remitted to the Government values.
    */
   public final Date[] getGovtChqIssueDateArray()
   {
      return _GovtChqIssueDate;
   }
    
   /**
    * Gets the Currency of Cheque remitted to the Government field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Currency of Cheque remitted to the Government or null.
    */
   public final String getGovtChqCurrency( int index )
   {
      return _GovtChqCurrency[index];
   }
    
   /**
    * Gets the Currency of Cheque remitted to the Government field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Currency of Cheque remitted to the Government or the specified default value.
    */
   public final String getGovtChqCurrency( int index, String defaultValue )
   {
      return _GovtChqCurrency[index] == null ? defaultValue : _GovtChqCurrency[index];
   }
    
   /**
    * Gets the array of Currency of Cheque remitted to the Government fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Currency of Cheque remitted to the Government values.
    */
   public final String[] getGovtChqCurrencyArray()
   {
      return _GovtChqCurrency;
   }
    
   /**
    * Gets the Status of Cheque remitted to the Government field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Status of Cheque remitted to the Government or null.
    */
   public final String getGovtChqStatus( int index )
   {
      return _GovtChqStatus[index];
   }
    
   /**
    * Gets the Status of Cheque remitted to the Government field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Status of Cheque remitted to the Government or the specified default value.
    */
   public final String getGovtChqStatus( int index, String defaultValue )
   {
      return _GovtChqStatus[index] == null ? defaultValue : _GovtChqStatus[index];
   }
    
   /**
    * Gets the array of Status of Cheque remitted to the Government fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Status of Cheque remitted to the Government values.
    */
   public final String[] getGovtChqStatusArray()
   {
      return _GovtChqStatus;
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
      
      _RecType = resizeArray( _RecType, _RepeatCount );
      _CheqNum = resizeArray( _CheqNum, _RepeatCount );
      _RefNumber = resizeArray( _RefNumber, _RepeatCount );
      _Fee = resizeArray( _Fee, _RepeatCount );
      _FedTax = resizeArray( _FedTax, _RepeatCount );
      _ProvTax = resizeArray( _ProvTax, _RepeatCount );
      _Amount = resizeArray( _Amount, _RepeatCount );
      _FundCode = resizeArray( _FundCode, _RepeatCount );
      _ClassCode = resizeArray( _ClassCode, _RepeatCount );
      _TransNum = resizeArray( _TransNum, _RepeatCount );
      _TransType = resizeArray( _TransType, _RepeatCount );
      _Currency = resizeArray( _Currency, _RepeatCount );
      _Salutation = resizeArray( _Salutation, _RepeatCount );
      _PayeeName = resizeArray( _PayeeName, _RepeatCount );
      _AddrLine1 = resizeArray( _AddrLine1, _RepeatCount );
      _AddrLine2 = resizeArray( _AddrLine2, _RepeatCount );
      _AddrLine3 = resizeArray( _AddrLine3, _RepeatCount );
      _AddrLine4 = resizeArray( _AddrLine4, _RepeatCount );
      _AddrLine5 = resizeArray( _AddrLine5, _RepeatCount );
      _PostalCode = resizeArray( _PostalCode, _RepeatCount );
      _BrokerChq = resizeArray( _BrokerChq, _RepeatCount );
      _DeliveryCode = resizeArray( _DeliveryCode, _RepeatCount );
      _DeliveryCodeDesc = resizeArray( _DeliveryCodeDesc, _RepeatCount );
      _PrintDate = resizeArray( _PrintDate, _RepeatCount );
      _ChequeAge = resizeArray( _ChequeAge, _RepeatCount );
      _BankAcctNumt = resizeArray( _BankAcctNumt, _RepeatCount );
      _BankRecDate = resizeArray( _BankRecDate, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _Username = resizeArray( _Username, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _CanDate = resizeArray( _CanDate, _RepeatCount );
      _CancelUser = resizeArray( _CancelUser, _RepeatCount );
      _ChqStatus = resizeArray( _ChqStatus, _RepeatCount );
      _ChqStatDesc = resizeArray( _ChqStatDesc, _RepeatCount );
      _rxAcctNum = resizeArray( _rxAcctNum, _RepeatCount );
      _Memo1 = resizeArray( _Memo1, _RepeatCount );
      _Memo2 = resizeArray( _Memo2, _RepeatCount );
      _CountryCode = resizeArray( _CountryCode, _RepeatCount );
      _CountryName = resizeArray( _CountryName, _RepeatCount );
      _CurrencyName = resizeArray( _CurrencyName, _RepeatCount );
      _PayType = resizeArray( _PayType, _RepeatCount );
      _ClawbackTotal = resizeArray( _ClawbackTotal, _RepeatCount );
      _CheqDetlUUID = resizeArray( _CheqDetlUUID, _RepeatCount );
      _UnclmStage = resizeArray( _UnclmStage, _RepeatCount );
      _StageDate = resizeArray( _StageDate, _RepeatCount );
      _UnclmRemitDate = resizeArray( _UnclmRemitDate, _RepeatCount );
      _Comments = resizeArray( _Comments, _RepeatCount );
      _Version = resizeArray( _Version, _RepeatCount );
      _StageAssignBy = resizeArray( _StageAssignBy, _RepeatCount );
      _GovtChqNo = resizeArray( _GovtChqNo, _RepeatCount );
      _GovtChqIssueDate = resizeArray( _GovtChqIssueDate, _RepeatCount );
      _GovtChqCurrency = resizeArray( _GovtChqCurrency, _RepeatCount );
      _GovtChqStatus = resizeArray( _GovtChqStatus, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _RecType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CheqNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RefNumber[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _Fee[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FedTax[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProvTax[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Amount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TransNum[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _TransType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Currency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Salutation[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PayeeName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine3[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine4[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine5[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PostalCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BrokerChq[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _DeliveryCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DeliveryCodeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PrintDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ChequeAge[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _BankAcctNumt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankRecDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _Username[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CanDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _CancelUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ChqStatus[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ChqStatDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxAcctNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Memo1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Memo2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CountryCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CountryName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CurrencyName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PayType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClawbackTotal[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CheqDetlUUID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UnclmStage[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _StageDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _UnclmRemitDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _Comments[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Version[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _StageAssignBy[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GovtChqNo[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GovtChqIssueDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _GovtChqCurrency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GovtChqStatus[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
