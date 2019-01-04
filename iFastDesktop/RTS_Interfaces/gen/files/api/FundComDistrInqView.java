
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * FundCom Distributionl Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/FundComDistrInq.doc">FundComDistrInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class FundComDistrInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Fund Baycom Number member array.
    */
   private String[] _rxBaycom = null;
   
   /**
    * English Fund Name member array.
    */
   private String[] _ELongName1 = null;
   
   /**
    * Dividend Option member array.
    */
   private Integer[] _DividendOption = null;
   
   /**
    * Payee Indicator member array.
    */
   private String[] _PayeeIndicator = null;
   
   /**
    * Holder member array.
    */
   private String[] _Holder = null;
   
   /**
    * Bank Institution Code member array.
    */
   private Integer[] _InstCode = null;
   
   /**
    * Bank Branch Number member array.
    */
   private Integer[] _BankBranchNum = null;
   
   /**
    * Bank Account Type member array.
    */
   private String[] _BankAcctType = null;
   
   /**
    * Bank Account Number member array.
    */
   private String[] _BankAcctNum = null;
   
   /**
    * Percentage, Dollars or Units member array.
    */
   private String[] _AmountType = null;
   
   /**
    * Amount member array.
    */
   private String[] _Amount = null;
   
   /**
    * Account To member array.
    */
   private String[] _AccountTo = null;
   
   /**
    * To-Fund Baycom Number member array.
    */
   private String[] _rxBaycomTo = null;
   
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
    * City member array.
    */
   private String[] _City = null;
   
   /**
    * Country Description member array.
    */
   private String[] _CountryDesc = null;
   
   /**
    * Country Code member array.
    */
   private String[] _CountryCode = null;
   
   /**
    * Postal Code member array.
    */
   private String[] _PostalCode = null;
   
   /**
    * Currency member array.
    */
   private String[] _Currency = null;
   
   /**
    * Long Name for FundTo member array.
    */
   private String[] _ELongName2 = null;
   
   /**
    * Alternate Payee name 1 member array.
    */
   private String[] _Name1 = null;
   
   /**
    * Alternate Payee Name 2 member array.
    */
   private String[] _Name2 = null;
   

   /**
    * Constructs the FundComDistrInqView object.
    * 
    */
   public FundComDistrInqView()
   {
      super ( new FundComDistrInqRequest() );
   }

   /**
    * Constructs the FundComDistrInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public FundComDistrInqView( String hostEncoding )
   {
      super ( new FundComDistrInqRequest( hostEncoding ) );
   }

   /**
    * Gets the FundComDistrInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The FundComDistrInqRequest object.
    */
   public final FundComDistrInqRequest getRequest()
   {
      return (FundComDistrInqRequest)getIFastRequest();
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
    * Gets the Fund Baycom Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Baycom Number or null.
    */
   public final String getrxBaycom( int index )
   {
      return _rxBaycom[index];
   }
    
   /**
    * Gets the Fund Baycom Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Baycom Number or the specified default value.
    */
   public final String getrxBaycom( int index, String defaultValue )
   {
      return _rxBaycom[index] == null ? defaultValue : _rxBaycom[index];
   }
    
   /**
    * Gets the array of Fund Baycom Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Baycom Number values.
    */
   public final String[] getrxBaycomArray()
   {
      return _rxBaycom;
   }
    
   /**
    * Gets the English Fund Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the English Fund Name or null.
    */
   public final String getELongName1( int index )
   {
      return _ELongName1[index];
   }
    
   /**
    * Gets the English Fund Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the English Fund Name or the specified default value.
    */
   public final String getELongName1( int index, String defaultValue )
   {
      return _ELongName1[index] == null ? defaultValue : _ELongName1[index];
   }
    
   /**
    * Gets the array of English Fund Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of English Fund Name values.
    */
   public final String[] getELongName1Array()
   {
      return _ELongName1;
   }
    
   /**
    * Gets the Dividend Option field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Dividend Option or null.
    */
   public final Integer getDividendOption( int index )
   {
      return _DividendOption[index];
   }
    
   /**
    * Gets the Dividend Option field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Dividend Option or the specified default value.
    */
   public final int getDividendOption( int index, int defaultValue )
   {
      return _DividendOption[index] == null ? defaultValue : _DividendOption[index].intValue();
   }
    
   /**
    * Gets the array of Dividend Option fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Dividend Option values.
    */
   public final Integer[] getDividendOptionArray()
   {
      return _DividendOption;
   }
    
   /**
    * Gets the Payee Indicator field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Payee Indicator or null.
    */
   public final String getPayeeIndicator( int index )
   {
      return _PayeeIndicator[index];
   }
    
   /**
    * Gets the Payee Indicator field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payee Indicator or the specified default value.
    */
   public final String getPayeeIndicator( int index, String defaultValue )
   {
      return _PayeeIndicator[index] == null ? defaultValue : _PayeeIndicator[index];
   }
    
   /**
    * Gets the array of Payee Indicator fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Payee Indicator values.
    */
   public final String[] getPayeeIndicatorArray()
   {
      return _PayeeIndicator;
   }
    
   /**
    * Gets the Holder field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Holder or null.
    */
   public final String getHolder( int index )
   {
      return _Holder[index];
   }
    
   /**
    * Gets the Holder field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Holder or the specified default value.
    */
   public final String getHolder( int index, String defaultValue )
   {
      return _Holder[index] == null ? defaultValue : _Holder[index];
   }
    
   /**
    * Gets the array of Holder fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Holder values.
    */
   public final String[] getHolderArray()
   {
      return _Holder;
   }
    
   /**
    * Gets the Bank Institution Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Institution Code or null.
    */
   public final Integer getInstCode( int index )
   {
      return _InstCode[index];
   }
    
   /**
    * Gets the Bank Institution Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Institution Code or the specified default value.
    */
   public final int getInstCode( int index, int defaultValue )
   {
      return _InstCode[index] == null ? defaultValue : _InstCode[index].intValue();
   }
    
   /**
    * Gets the array of Bank Institution Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Institution Code values.
    */
   public final Integer[] getInstCodeArray()
   {
      return _InstCode;
   }
    
   /**
    * Gets the Bank Branch Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Branch Number or null.
    */
   public final Integer getBankBranchNum( int index )
   {
      return _BankBranchNum[index];
   }
    
   /**
    * Gets the Bank Branch Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Branch Number or the specified default value.
    */
   public final int getBankBranchNum( int index, int defaultValue )
   {
      return _BankBranchNum[index] == null ? defaultValue : _BankBranchNum[index].intValue();
   }
    
   /**
    * Gets the array of Bank Branch Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Branch Number values.
    */
   public final Integer[] getBankBranchNumArray()
   {
      return _BankBranchNum;
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
    * Gets the Percentage, Dollars or Units field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Percentage, Dollars or Units or null.
    */
   public final String getAmountType( int index )
   {
      return _AmountType[index];
   }
    
   /**
    * Gets the Percentage, Dollars or Units field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Percentage, Dollars or Units or the specified default value.
    */
   public final String getAmountType( int index, String defaultValue )
   {
      return _AmountType[index] == null ? defaultValue : _AmountType[index];
   }
    
   /**
    * Gets the array of Percentage, Dollars or Units fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Percentage, Dollars or Units values.
    */
   public final String[] getAmountTypeArray()
   {
      return _AmountType;
   }
    
   /**
    * Gets the Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Amount or null.
    */
   public final String getAmount( int index )
   {
      return _Amount[index];
   }
    
   /**
    * Gets the Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Amount or the specified default value.
    */
   public final String getAmount( int index, String defaultValue )
   {
      return _Amount[index] == null ? defaultValue : _Amount[index];
   }
    
   /**
    * Gets the array of Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Amount values.
    */
   public final String[] getAmountArray()
   {
      return _Amount;
   }
    
   /**
    * Gets the Account To field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account To or null.
    */
   public final String getAccountTo( int index )
   {
      return _AccountTo[index];
   }
    
   /**
    * Gets the Account To field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account To or the specified default value.
    */
   public final String getAccountTo( int index, String defaultValue )
   {
      return _AccountTo[index] == null ? defaultValue : _AccountTo[index];
   }
    
   /**
    * Gets the array of Account To fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account To values.
    */
   public final String[] getAccountToArray()
   {
      return _AccountTo;
   }
    
   /**
    * Gets the To-Fund Baycom Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the To-Fund Baycom Number or null.
    */
   public final String getrxBaycomTo( int index )
   {
      return _rxBaycomTo[index];
   }
    
   /**
    * Gets the To-Fund Baycom Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the To-Fund Baycom Number or the specified default value.
    */
   public final String getrxBaycomTo( int index, String defaultValue )
   {
      return _rxBaycomTo[index] == null ? defaultValue : _rxBaycomTo[index];
   }
    
   /**
    * Gets the array of To-Fund Baycom Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of To-Fund Baycom Number values.
    */
   public final String[] getrxBaycomToArray()
   {
      return _rxBaycomTo;
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
    * Gets the City field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the City or null.
    */
   public final String getCity( int index )
   {
      return _City[index];
   }
    
   /**
    * Gets the City field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the City or the specified default value.
    */
   public final String getCity( int index, String defaultValue )
   {
      return _City[index] == null ? defaultValue : _City[index];
   }
    
   /**
    * Gets the array of City fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of City values.
    */
   public final String[] getCityArray()
   {
      return _City;
   }
    
   /**
    * Gets the Country Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Country Description or null.
    */
   public final String getCountryDesc( int index )
   {
      return _CountryDesc[index];
   }
    
   /**
    * Gets the Country Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Country Description or the specified default value.
    */
   public final String getCountryDesc( int index, String defaultValue )
   {
      return _CountryDesc[index] == null ? defaultValue : _CountryDesc[index];
   }
    
   /**
    * Gets the array of Country Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Country Description values.
    */
   public final String[] getCountryDescArray()
   {
      return _CountryDesc;
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
    * Gets the Long Name for FundTo field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Long Name for FundTo or null.
    */
   public final String getELongName2( int index )
   {
      return _ELongName2[index];
   }
    
   /**
    * Gets the Long Name for FundTo field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Long Name for FundTo or the specified default value.
    */
   public final String getELongName2( int index, String defaultValue )
   {
      return _ELongName2[index] == null ? defaultValue : _ELongName2[index];
   }
    
   /**
    * Gets the array of Long Name for FundTo fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Long Name for FundTo values.
    */
   public final String[] getELongName2Array()
   {
      return _ELongName2;
   }
    
   /**
    * Gets the Alternate Payee name 1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Alternate Payee name 1 or null.
    */
   public final String getName1( int index )
   {
      return _Name1[index];
   }
    
   /**
    * Gets the Alternate Payee name 1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Alternate Payee name 1 or the specified default value.
    */
   public final String getName1( int index, String defaultValue )
   {
      return _Name1[index] == null ? defaultValue : _Name1[index];
   }
    
   /**
    * Gets the array of Alternate Payee name 1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Alternate Payee name 1 values.
    */
   public final String[] getName1Array()
   {
      return _Name1;
   }
    
   /**
    * Gets the Alternate Payee Name 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Alternate Payee Name 2 or null.
    */
   public final String getName2( int index )
   {
      return _Name2[index];
   }
    
   /**
    * Gets the Alternate Payee Name 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Alternate Payee Name 2 or the specified default value.
    */
   public final String getName2( int index, String defaultValue )
   {
      return _Name2[index] == null ? defaultValue : _Name2[index];
   }
    
   /**
    * Gets the array of Alternate Payee Name 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Alternate Payee Name 2 values.
    */
   public final String[] getName2Array()
   {
      return _Name2;
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
      
      _rxBaycom = resizeArray( _rxBaycom, _RepeatCount );
      _ELongName1 = resizeArray( _ELongName1, _RepeatCount );
      _DividendOption = resizeArray( _DividendOption, _RepeatCount );
      _PayeeIndicator = resizeArray( _PayeeIndicator, _RepeatCount );
      _Holder = resizeArray( _Holder, _RepeatCount );
      _InstCode = resizeArray( _InstCode, _RepeatCount );
      _BankBranchNum = resizeArray( _BankBranchNum, _RepeatCount );
      _BankAcctType = resizeArray( _BankAcctType, _RepeatCount );
      _BankAcctNum = resizeArray( _BankAcctNum, _RepeatCount );
      _AmountType = resizeArray( _AmountType, _RepeatCount );
      _Amount = resizeArray( _Amount, _RepeatCount );
      _AccountTo = resizeArray( _AccountTo, _RepeatCount );
      _rxBaycomTo = resizeArray( _rxBaycomTo, _RepeatCount );
      _AddrLine1 = resizeArray( _AddrLine1, _RepeatCount );
      _AddrLine2 = resizeArray( _AddrLine2, _RepeatCount );
      _AddrLine3 = resizeArray( _AddrLine3, _RepeatCount );
      _AddrLine4 = resizeArray( _AddrLine4, _RepeatCount );
      _AddrLine5 = resizeArray( _AddrLine5, _RepeatCount );
      _City = resizeArray( _City, _RepeatCount );
      _CountryDesc = resizeArray( _CountryDesc, _RepeatCount );
      _CountryCode = resizeArray( _CountryCode, _RepeatCount );
      _PostalCode = resizeArray( _PostalCode, _RepeatCount );
      _Currency = resizeArray( _Currency, _RepeatCount );
      _ELongName2 = resizeArray( _ELongName2, _RepeatCount );
      _Name1 = resizeArray( _Name1, _RepeatCount );
      _Name2 = resizeArray( _Name2, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxBaycom[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ELongName1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DividendOption[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _PayeeIndicator[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Holder[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _InstCode[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _BankBranchNum[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _BankAcctType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAcctNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AmountType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Amount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AccountTo[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxBaycomTo[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine3[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine4[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine5[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _City[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CountryDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CountryCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PostalCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Currency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ELongName2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Name1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Name2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
