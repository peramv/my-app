
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Account/fund balances view.
 * For additional view information see <A HREF="../../../../viewspecs/AccountBalance.doc">AccountBalance.doc</A>.
 * 
 * @author RTS Generated
 */
public class AccountBalanceView extends IFastView implements Serializable
{

   /**
    * Account balance member variable.
    */
   private String _AccountBalance = null;
   
   /**
    * Foreign Content Holdings member variable.
    */
   private String _FrgnBalance = null;
   
   /**
    * Foreign content ACB in prcnt, settled + unsettled member variable.
    */
   private String _FrgnACBUnsettl = null;
   
   /**
    * Top up amt for foreign content member variable.
    */
   private String _FrgnExcsACBUnsettl = null;
   
   /**
    * Total account holdings in $ member variable.
    */
   private String _TotalValueAcctCurr = null;
   
   /**
    * Shareholder Settled Value member variable.
    */
   private String _ShrSettledValue = null;
   
   /**
    * Total ACB of settled units member variable.
    */
   private String _TotalACBSettl = null;
   
   /**
    * Total ACB of settled and unsettled units member variable.
    */
   private String _TotalACBUnsettl = null;
   
   /**
    * Ratio of foreign settled units ACB to total settled units of the account - % member variable.
    */
   private String _FrgnACBSettl = null;
   
   /**
    * Ratio of domestic settled units ACB to total settled units of the account - % member variable.
    */
   private String _DomesticACBSettl = null;
   
   /**
    * Ratio of domestic settled + unsettled member variable.
    */
   private String _DomesticACBUnsettl = null;
   
   /**
    * Foreign content %age allowed member variable.
    */
   private String _FrgnAllowPrcnt = null;
   
   /**
    * Foreign content allowable ACB based on  settled units member variable.
    */
   private String _FrgnAllowACBSettl = null;
   
   /**
    * Foreign content allowable ACB based on settled + unsettled units member variable.
    */
   private String _FrgnAllowACBUnsettl = null;
   
   /**
    * Excess %age amt allowable based on settled + unsettled units member variable.
    */
   private String _FrgnExcsPrcntUnsettl = null;
   
   /**
    * Excess %age amt allowable member variable.
    */
   private String _FrgnExcsPrcntSettl = null;
   
   /**
    * Top up amount for foreign content member variable.
    */
   private String _FrgnExcsACBSettl = null;
   
   /**
    * Account ACB Value Available member variable.
    */
   private Boolean _AcctACBAvail = null;
   
   /**
    * Tax On Full Redemption member variable.
    */
   private Boolean _TaxOnFullRed = null;
   
   /**
    * Has ERISA Prohibited Fund member variable.
    */
   private Boolean _hasERISAProhibitedFund = null;
   
   /**
    * Account Balance Units based on Mode member variable.
    */
   private String _AccBalUnits = null;
   
   private int _RepeatCount = 0;
   
   /**
    * Fund Code member array.
    */
   private String[] _rxFundCode = null;
   
   /**
    * Class Code member array.
    */
   private String[] _rxClassCode = null;
   
   /**
    * Settled Units Held member array.
    */
   private String[] _SettledUnits = null;
   
   /**
    * Settled Value member array.
    */
   private String[] _SettleValue = null;
   
   /**
    * Unsettled Units Held member array.
    */
   private String[] _UnsettledUnits = null;
   
   /**
    * Unsettled Value member array.
    */
   private String[] _UnsettledValue = null;
   
   /**
    * Fund NAV member array.
    */
   private String[] _FundNAV = null;
   
   /**
    * Previous Year End Units member array.
    */
   private String[] _PYEUnits = null;
   
   /**
    * Previous Year End Value member array.
    */
   private String[] _PYEValue = null;
   
   /**
    * As at Date member array.
    */
   private Date[] _AsAtDate = null;
   
   /**
    * Last Event on Account member array.
    */
   private Date[] _LastEvent = null;
   
   /**
    * Fund balance in account currency member array.
    */
   private String[] _SettledValueAcctCurr = null;
   
   /**
    * Fund Currency member array.
    */
   private String[] _FundCurrency = null;
   
   /**
    * Traded Units member array.
    */
   private String[] _TradedUnits = null;
   
   /**
    * Combined value in fund currency member array.
    */
   private String[] _CombValueFundCurr = null;
   
   /**
    * Combined value in account currency member array.
    */
   private String[] _CombValueAcctCurr = null;
   
   /**
    * Exchange Rate member array.
    */
   private String[] _ExchRate = null;
   
   /**
    * Pending trade exists flag member array.
    */
   private Boolean[] _PendingTradeExist = null;
   
   /**
    * ACB of settled units per fund/class member array.
    */
   private String[] _ACBSettl = null;
   
   /**
    * ACB of settled + unsettled units per fund member array.
    */
   private String[] _ACBUnsettl = null;
   
   /**
    * Baycom Number member array.
    */
   private String[] _Baycom = null;
   
   /**
    * Fund Group used to sort funds member array.
    */
   private String[] _FundGroup = null;
   
   /**
    * Fund/ Class ACB Available member array.
    */
   private Boolean[] _FndClACBAvail = null;
   
   /**
    * Reporting Exchange Rate member array.
    */
   private String[] _ReportingExchRate = null;
   
   /**
    * NAV Date member array.
    */
   private Date[] _NAVDate = null;
   
   /**
    * Allocator Fund member array.
    */
   private Boolean[] _AllocatorFund = null;
   
   /**
    * ACB Settled Value member array.
    */
   private String[] _ACBSettledValue = null;
   
   /**
    * Active Certificates member array.
    */
   private Boolean[] _ActiveCert = null;
   
   /**
    * G1Balance member array.
    */
   private String[] _G1Balance = null;
   
   /**
    * G2Balance member array.
    */
   private String[] _G2Balance = null;
   

   /**
    * Constructs the AccountBalanceView object.
    * 
    */
   public AccountBalanceView()
   {
      super ( new AccountBalanceRequest() );
   }

   /**
    * Constructs the AccountBalanceView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AccountBalanceView( String hostEncoding )
   {
      super ( new AccountBalanceRequest( hostEncoding ) );
   }

   /**
    * Gets the AccountBalanceRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AccountBalanceRequest object.
    */
   public final AccountBalanceRequest getRequest()
   {
      return (AccountBalanceRequest)getIFastRequest();
   }
        
   /**
    * Gets the Account balance field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Account balance or null.
    */
   public final String getAccountBalance()
   {
      return _AccountBalance;
   }
	
   /**
    * Gets the Account balance field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account balance or the specified default value.
    */
   public final String getAccountBalance( String defaultValue )
   {
      return _AccountBalance == null ? defaultValue : _AccountBalance;
   }
                  
   /**
    * Gets the Foreign Content Holdings field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Foreign Content Holdings or null.
    */
   public final String getFrgnBalance()
   {
      return _FrgnBalance;
   }
	
   /**
    * Gets the Foreign Content Holdings field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Foreign Content Holdings or the specified default value.
    */
   public final String getFrgnBalance( String defaultValue )
   {
      return _FrgnBalance == null ? defaultValue : _FrgnBalance;
   }
                  
   /**
    * Gets the Foreign content ACB in prcnt, settled + unsettled field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Foreign content ACB in prcnt, settled + unsettled or null.
    */
   public final String getFrgnACBUnsettl()
   {
      return _FrgnACBUnsettl;
   }
	
   /**
    * Gets the Foreign content ACB in prcnt, settled + unsettled field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Foreign content ACB in prcnt, settled + unsettled or the specified default value.
    */
   public final String getFrgnACBUnsettl( String defaultValue )
   {
      return _FrgnACBUnsettl == null ? defaultValue : _FrgnACBUnsettl;
   }
                  
   /**
    * Gets the Top up amt for foreign content field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Top up amt for foreign content or null.
    */
   public final String getFrgnExcsACBUnsettl()
   {
      return _FrgnExcsACBUnsettl;
   }
	
   /**
    * Gets the Top up amt for foreign content field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Top up amt for foreign content or the specified default value.
    */
   public final String getFrgnExcsACBUnsettl( String defaultValue )
   {
      return _FrgnExcsACBUnsettl == null ? defaultValue : _FrgnExcsACBUnsettl;
   }
                  
   /**
    * Gets the Total account holdings in $ field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Total account holdings in $ or null.
    */
   public final String getTotalValueAcctCurr()
   {
      return _TotalValueAcctCurr;
   }
	
   /**
    * Gets the Total account holdings in $ field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Total account holdings in $ or the specified default value.
    */
   public final String getTotalValueAcctCurr( String defaultValue )
   {
      return _TotalValueAcctCurr == null ? defaultValue : _TotalValueAcctCurr;
   }
                  
   /**
    * Gets the Shareholder Settled Value field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Shareholder Settled Value or null.
    */
   public final String getShrSettledValue()
   {
      return _ShrSettledValue;
   }
	
   /**
    * Gets the Shareholder Settled Value field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Shareholder Settled Value or the specified default value.
    */
   public final String getShrSettledValue( String defaultValue )
   {
      return _ShrSettledValue == null ? defaultValue : _ShrSettledValue;
   }
                  
   /**
    * Gets the Total ACB of settled units field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Total ACB of settled units or null.
    */
   public final String getTotalACBSettl()
   {
      return _TotalACBSettl;
   }
	
   /**
    * Gets the Total ACB of settled units field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Total ACB of settled units or the specified default value.
    */
   public final String getTotalACBSettl( String defaultValue )
   {
      return _TotalACBSettl == null ? defaultValue : _TotalACBSettl;
   }
                  
   /**
    * Gets the Total ACB of settled and unsettled units field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Total ACB of settled and unsettled units or null.
    */
   public final String getTotalACBUnsettl()
   {
      return _TotalACBUnsettl;
   }
	
   /**
    * Gets the Total ACB of settled and unsettled units field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Total ACB of settled and unsettled units or the specified default value.
    */
   public final String getTotalACBUnsettl( String defaultValue )
   {
      return _TotalACBUnsettl == null ? defaultValue : _TotalACBUnsettl;
   }
                  
   /**
    * Gets the Ratio of foreign settled units ACB to total settled units of the account - % field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Ratio of foreign settled units ACB to total settled units of the account - % or null.
    */
   public final String getFrgnACBSettl()
   {
      return _FrgnACBSettl;
   }
	
   /**
    * Gets the Ratio of foreign settled units ACB to total settled units of the account - % field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Ratio of foreign settled units ACB to total settled units of the account - % or the specified default value.
    */
   public final String getFrgnACBSettl( String defaultValue )
   {
      return _FrgnACBSettl == null ? defaultValue : _FrgnACBSettl;
   }
                  
   /**
    * Gets the Ratio of domestic settled units ACB to total settled units of the account - % field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Ratio of domestic settled units ACB to total settled units of the account - % or null.
    */
   public final String getDomesticACBSettl()
   {
      return _DomesticACBSettl;
   }
	
   /**
    * Gets the Ratio of domestic settled units ACB to total settled units of the account - % field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Ratio of domestic settled units ACB to total settled units of the account - % or the specified default value.
    */
   public final String getDomesticACBSettl( String defaultValue )
   {
      return _DomesticACBSettl == null ? defaultValue : _DomesticACBSettl;
   }
                  
   /**
    * Gets the Ratio of domestic settled + unsettled field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Ratio of domestic settled + unsettled or null.
    */
   public final String getDomesticACBUnsettl()
   {
      return _DomesticACBUnsettl;
   }
	
   /**
    * Gets the Ratio of domestic settled + unsettled field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Ratio of domestic settled + unsettled or the specified default value.
    */
   public final String getDomesticACBUnsettl( String defaultValue )
   {
      return _DomesticACBUnsettl == null ? defaultValue : _DomesticACBUnsettl;
   }
                  
   /**
    * Gets the Foreign content %age allowed field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Foreign content %age allowed or null.
    */
   public final String getFrgnAllowPrcnt()
   {
      return _FrgnAllowPrcnt;
   }
	
   /**
    * Gets the Foreign content %age allowed field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Foreign content %age allowed or the specified default value.
    */
   public final String getFrgnAllowPrcnt( String defaultValue )
   {
      return _FrgnAllowPrcnt == null ? defaultValue : _FrgnAllowPrcnt;
   }
                  
   /**
    * Gets the Foreign content allowable ACB based on  settled units field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Foreign content allowable ACB based on  settled units or null.
    */
   public final String getFrgnAllowACBSettl()
   {
      return _FrgnAllowACBSettl;
   }
	
   /**
    * Gets the Foreign content allowable ACB based on  settled units field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Foreign content allowable ACB based on  settled units or the specified default value.
    */
   public final String getFrgnAllowACBSettl( String defaultValue )
   {
      return _FrgnAllowACBSettl == null ? defaultValue : _FrgnAllowACBSettl;
   }
                  
   /**
    * Gets the Foreign content allowable ACB based on settled + unsettled units field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Foreign content allowable ACB based on settled + unsettled units or null.
    */
   public final String getFrgnAllowACBUnsettl()
   {
      return _FrgnAllowACBUnsettl;
   }
	
   /**
    * Gets the Foreign content allowable ACB based on settled + unsettled units field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Foreign content allowable ACB based on settled + unsettled units or the specified default value.
    */
   public final String getFrgnAllowACBUnsettl( String defaultValue )
   {
      return _FrgnAllowACBUnsettl == null ? defaultValue : _FrgnAllowACBUnsettl;
   }
                  
   /**
    * Gets the Excess %age amt allowable based on settled + unsettled units field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Excess %age amt allowable based on settled + unsettled units or null.
    */
   public final String getFrgnExcsPrcntUnsettl()
   {
      return _FrgnExcsPrcntUnsettl;
   }
	
   /**
    * Gets the Excess %age amt allowable based on settled + unsettled units field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Excess %age amt allowable based on settled + unsettled units or the specified default value.
    */
   public final String getFrgnExcsPrcntUnsettl( String defaultValue )
   {
      return _FrgnExcsPrcntUnsettl == null ? defaultValue : _FrgnExcsPrcntUnsettl;
   }
                  
   /**
    * Gets the Excess %age amt allowable field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Excess %age amt allowable or null.
    */
   public final String getFrgnExcsPrcntSettl()
   {
      return _FrgnExcsPrcntSettl;
   }
	
   /**
    * Gets the Excess %age amt allowable field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Excess %age amt allowable or the specified default value.
    */
   public final String getFrgnExcsPrcntSettl( String defaultValue )
   {
      return _FrgnExcsPrcntSettl == null ? defaultValue : _FrgnExcsPrcntSettl;
   }
                  
   /**
    * Gets the Top up amount for foreign content field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Top up amount for foreign content or null.
    */
   public final String getFrgnExcsACBSettl()
   {
      return _FrgnExcsACBSettl;
   }
	
   /**
    * Gets the Top up amount for foreign content field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Top up amount for foreign content or the specified default value.
    */
   public final String getFrgnExcsACBSettl( String defaultValue )
   {
      return _FrgnExcsACBSettl == null ? defaultValue : _FrgnExcsACBSettl;
   }
                  
   /**
    * Gets the Account ACB Value Available field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Account ACB Value Available or null.
    */
   public final Boolean getAcctACBAvail()
   {
      return _AcctACBAvail;
   }
	
   /**
    * Gets the Account ACB Value Available field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account ACB Value Available or the specified default value.
    */
   public final boolean getAcctACBAvail( boolean defaultValue )
   {
      return _AcctACBAvail == null ? defaultValue : _AcctACBAvail.booleanValue();
   }
                  
   /**
    * Gets the Tax On Full Redemption field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Tax On Full Redemption or null.
    */
   public final Boolean getTaxOnFullRed()
   {
      return _TaxOnFullRed;
   }
	
   /**
    * Gets the Tax On Full Redemption field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax On Full Redemption or the specified default value.
    */
   public final boolean getTaxOnFullRed( boolean defaultValue )
   {
      return _TaxOnFullRed == null ? defaultValue : _TaxOnFullRed.booleanValue();
   }
                  
   /**
    * Gets the Has ERISA Prohibited Fund field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Has ERISA Prohibited Fund or null.
    */
   public final Boolean gethasERISAProhibitedFund()
   {
      return _hasERISAProhibitedFund;
   }
	
   /**
    * Gets the Has ERISA Prohibited Fund field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Has ERISA Prohibited Fund or the specified default value.
    */
   public final boolean gethasERISAProhibitedFund( boolean defaultValue )
   {
      return _hasERISAProhibitedFund == null ? defaultValue : _hasERISAProhibitedFund.booleanValue();
   }
                  
   /**
    * Gets the Account Balance Units based on Mode field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Account Balance Units based on Mode or null.
    */
   public final String getAccBalUnits()
   {
      return _AccBalUnits;
   }
	
   /**
    * Gets the Account Balance Units based on Mode field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Balance Units based on Mode or the specified default value.
    */
   public final String getAccBalUnits( String defaultValue )
   {
      return _AccBalUnits == null ? defaultValue : _AccBalUnits;
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
    * Gets the Fund Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Code or null.
    */
   public final String getrxFundCode( int index )
   {
      return _rxFundCode[index];
   }
    
   /**
    * Gets the Fund Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Code or the specified default value.
    */
   public final String getrxFundCode( int index, String defaultValue )
   {
      return _rxFundCode[index] == null ? defaultValue : _rxFundCode[index];
   }
    
   /**
    * Gets the array of Fund Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Code values.
    */
   public final String[] getrxFundCodeArray()
   {
      return _rxFundCode;
   }
    
   /**
    * Gets the Class Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Class Code or null.
    */
   public final String getrxClassCode( int index )
   {
      return _rxClassCode[index];
   }
    
   /**
    * Gets the Class Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class Code or the specified default value.
    */
   public final String getrxClassCode( int index, String defaultValue )
   {
      return _rxClassCode[index] == null ? defaultValue : _rxClassCode[index];
   }
    
   /**
    * Gets the array of Class Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Class Code values.
    */
   public final String[] getrxClassCodeArray()
   {
      return _rxClassCode;
   }
    
   /**
    * Gets the Settled Units Held field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Settled Units Held or null.
    */
   public final String getSettledUnits( int index )
   {
      return _SettledUnits[index];
   }
    
   /**
    * Gets the Settled Units Held field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settled Units Held or the specified default value.
    */
   public final String getSettledUnits( int index, String defaultValue )
   {
      return _SettledUnits[index] == null ? defaultValue : _SettledUnits[index];
   }
    
   /**
    * Gets the array of Settled Units Held fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Settled Units Held values.
    */
   public final String[] getSettledUnitsArray()
   {
      return _SettledUnits;
   }
    
   /**
    * Gets the Settled Value field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Settled Value or null.
    */
   public final String getSettleValue( int index )
   {
      return _SettleValue[index];
   }
    
   /**
    * Gets the Settled Value field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settled Value or the specified default value.
    */
   public final String getSettleValue( int index, String defaultValue )
   {
      return _SettleValue[index] == null ? defaultValue : _SettleValue[index];
   }
    
   /**
    * Gets the array of Settled Value fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Settled Value values.
    */
   public final String[] getSettleValueArray()
   {
      return _SettleValue;
   }
    
   /**
    * Gets the Unsettled Units Held field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Unsettled Units Held or null.
    */
   public final String getUnsettledUnits( int index )
   {
      return _UnsettledUnits[index];
   }
    
   /**
    * Gets the Unsettled Units Held field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Unsettled Units Held or the specified default value.
    */
   public final String getUnsettledUnits( int index, String defaultValue )
   {
      return _UnsettledUnits[index] == null ? defaultValue : _UnsettledUnits[index];
   }
    
   /**
    * Gets the array of Unsettled Units Held fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Unsettled Units Held values.
    */
   public final String[] getUnsettledUnitsArray()
   {
      return _UnsettledUnits;
   }
    
   /**
    * Gets the Unsettled Value field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Unsettled Value or null.
    */
   public final String getUnsettledValue( int index )
   {
      return _UnsettledValue[index];
   }
    
   /**
    * Gets the Unsettled Value field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Unsettled Value or the specified default value.
    */
   public final String getUnsettledValue( int index, String defaultValue )
   {
      return _UnsettledValue[index] == null ? defaultValue : _UnsettledValue[index];
   }
    
   /**
    * Gets the array of Unsettled Value fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Unsettled Value values.
    */
   public final String[] getUnsettledValueArray()
   {
      return _UnsettledValue;
   }
    
   /**
    * Gets the Fund NAV field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund NAV or null.
    */
   public final String getFundNAV( int index )
   {
      return _FundNAV[index];
   }
    
   /**
    * Gets the Fund NAV field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund NAV or the specified default value.
    */
   public final String getFundNAV( int index, String defaultValue )
   {
      return _FundNAV[index] == null ? defaultValue : _FundNAV[index];
   }
    
   /**
    * Gets the array of Fund NAV fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund NAV values.
    */
   public final String[] getFundNAVArray()
   {
      return _FundNAV;
   }
    
   /**
    * Gets the Previous Year End Units field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Previous Year End Units or null.
    */
   public final String getPYEUnits( int index )
   {
      return _PYEUnits[index];
   }
    
   /**
    * Gets the Previous Year End Units field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Previous Year End Units or the specified default value.
    */
   public final String getPYEUnits( int index, String defaultValue )
   {
      return _PYEUnits[index] == null ? defaultValue : _PYEUnits[index];
   }
    
   /**
    * Gets the array of Previous Year End Units fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Previous Year End Units values.
    */
   public final String[] getPYEUnitsArray()
   {
      return _PYEUnits;
   }
    
   /**
    * Gets the Previous Year End Value field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Previous Year End Value or null.
    */
   public final String getPYEValue( int index )
   {
      return _PYEValue[index];
   }
    
   /**
    * Gets the Previous Year End Value field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Previous Year End Value or the specified default value.
    */
   public final String getPYEValue( int index, String defaultValue )
   {
      return _PYEValue[index] == null ? defaultValue : _PYEValue[index];
   }
    
   /**
    * Gets the array of Previous Year End Value fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Previous Year End Value values.
    */
   public final String[] getPYEValueArray()
   {
      return _PYEValue;
   }
    
   /**
    * Gets the As at Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the As at Date or null.
    */
   public final Date getAsAtDate( int index )
   {
      return _AsAtDate[index];
   }
    
   /**
    * Gets the As at Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the As at Date or the specified default value.
    */
   public final Date getAsAtDate( int index, Date defaultValue )
   {
      return _AsAtDate[index] == null ? defaultValue : _AsAtDate[index];
   }
    
   /**
    * Gets the array of As at Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of As at Date values.
    */
   public final Date[] getAsAtDateArray()
   {
      return _AsAtDate;
   }
    
   /**
    * Gets the Last Event on Account field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Last Event on Account or null.
    */
   public final Date getLastEvent( int index )
   {
      return _LastEvent[index];
   }
    
   /**
    * Gets the Last Event on Account field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Last Event on Account or the specified default value.
    */
   public final Date getLastEvent( int index, Date defaultValue )
   {
      return _LastEvent[index] == null ? defaultValue : _LastEvent[index];
   }
    
   /**
    * Gets the array of Last Event on Account fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Last Event on Account values.
    */
   public final Date[] getLastEventArray()
   {
      return _LastEvent;
   }
    
   /**
    * Gets the Fund balance in account currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund balance in account currency or null.
    */
   public final String getSettledValueAcctCurr( int index )
   {
      return _SettledValueAcctCurr[index];
   }
    
   /**
    * Gets the Fund balance in account currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund balance in account currency or the specified default value.
    */
   public final String getSettledValueAcctCurr( int index, String defaultValue )
   {
      return _SettledValueAcctCurr[index] == null ? defaultValue : _SettledValueAcctCurr[index];
   }
    
   /**
    * Gets the array of Fund balance in account currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund balance in account currency values.
    */
   public final String[] getSettledValueAcctCurrArray()
   {
      return _SettledValueAcctCurr;
   }
    
   /**
    * Gets the Fund Currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Currency or null.
    */
   public final String getFundCurrency( int index )
   {
      return _FundCurrency[index];
   }
    
   /**
    * Gets the Fund Currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Currency or the specified default value.
    */
   public final String getFundCurrency( int index, String defaultValue )
   {
      return _FundCurrency[index] == null ? defaultValue : _FundCurrency[index];
   }
    
   /**
    * Gets the array of Fund Currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Currency values.
    */
   public final String[] getFundCurrencyArray()
   {
      return _FundCurrency;
   }
    
   /**
    * Gets the Traded Units field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Traded Units or null.
    */
   public final String getTradedUnits( int index )
   {
      return _TradedUnits[index];
   }
    
   /**
    * Gets the Traded Units field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Traded Units or the specified default value.
    */
   public final String getTradedUnits( int index, String defaultValue )
   {
      return _TradedUnits[index] == null ? defaultValue : _TradedUnits[index];
   }
    
   /**
    * Gets the array of Traded Units fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Traded Units values.
    */
   public final String[] getTradedUnitsArray()
   {
      return _TradedUnits;
   }
    
   /**
    * Gets the Combined value in fund currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Combined value in fund currency or null.
    */
   public final String getCombValueFundCurr( int index )
   {
      return _CombValueFundCurr[index];
   }
    
   /**
    * Gets the Combined value in fund currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Combined value in fund currency or the specified default value.
    */
   public final String getCombValueFundCurr( int index, String defaultValue )
   {
      return _CombValueFundCurr[index] == null ? defaultValue : _CombValueFundCurr[index];
   }
    
   /**
    * Gets the array of Combined value in fund currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Combined value in fund currency values.
    */
   public final String[] getCombValueFundCurrArray()
   {
      return _CombValueFundCurr;
   }
    
   /**
    * Gets the Combined value in account currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Combined value in account currency or null.
    */
   public final String getCombValueAcctCurr( int index )
   {
      return _CombValueAcctCurr[index];
   }
    
   /**
    * Gets the Combined value in account currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Combined value in account currency or the specified default value.
    */
   public final String getCombValueAcctCurr( int index, String defaultValue )
   {
      return _CombValueAcctCurr[index] == null ? defaultValue : _CombValueAcctCurr[index];
   }
    
   /**
    * Gets the array of Combined value in account currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Combined value in account currency values.
    */
   public final String[] getCombValueAcctCurrArray()
   {
      return _CombValueAcctCurr;
   }
    
   /**
    * Gets the Exchange Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Exchange Rate or null.
    */
   public final String getExchRate( int index )
   {
      return _ExchRate[index];
   }
    
   /**
    * Gets the Exchange Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Exchange Rate or the specified default value.
    */
   public final String getExchRate( int index, String defaultValue )
   {
      return _ExchRate[index] == null ? defaultValue : _ExchRate[index];
   }
    
   /**
    * Gets the array of Exchange Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Exchange Rate values.
    */
   public final String[] getExchRateArray()
   {
      return _ExchRate;
   }
    
   /**
    * Gets the Pending trade exists flag field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Pending trade exists flag or null.
    */
   public final Boolean getPendingTradeExist( int index )
   {
      return _PendingTradeExist[index];
   }
    
   /**
    * Gets the Pending trade exists flag field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pending trade exists flag or the specified default value.
    */
   public final boolean getPendingTradeExist( int index, boolean defaultValue )
   {
      return _PendingTradeExist[index] == null ? defaultValue : _PendingTradeExist[index].booleanValue();
   }
    
   /**
    * Gets the array of Pending trade exists flag fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Pending trade exists flag values.
    */
   public final Boolean[] getPendingTradeExistArray()
   {
      return _PendingTradeExist;
   }
    
   /**
    * Gets the ACB of settled units per fund/class field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ACB of settled units per fund/class or null.
    */
   public final String getACBSettl( int index )
   {
      return _ACBSettl[index];
   }
    
   /**
    * Gets the ACB of settled units per fund/class field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ACB of settled units per fund/class or the specified default value.
    */
   public final String getACBSettl( int index, String defaultValue )
   {
      return _ACBSettl[index] == null ? defaultValue : _ACBSettl[index];
   }
    
   /**
    * Gets the array of ACB of settled units per fund/class fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ACB of settled units per fund/class values.
    */
   public final String[] getACBSettlArray()
   {
      return _ACBSettl;
   }
    
   /**
    * Gets the ACB of settled + unsettled units per fund field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ACB of settled + unsettled units per fund or null.
    */
   public final String getACBUnsettl( int index )
   {
      return _ACBUnsettl[index];
   }
    
   /**
    * Gets the ACB of settled + unsettled units per fund field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ACB of settled + unsettled units per fund or the specified default value.
    */
   public final String getACBUnsettl( int index, String defaultValue )
   {
      return _ACBUnsettl[index] == null ? defaultValue : _ACBUnsettl[index];
   }
    
   /**
    * Gets the array of ACB of settled + unsettled units per fund fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ACB of settled + unsettled units per fund values.
    */
   public final String[] getACBUnsettlArray()
   {
      return _ACBUnsettl;
   }
    
   /**
    * Gets the Baycom Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Baycom Number or null.
    */
   public final String getBaycom( int index )
   {
      return _Baycom[index];
   }
    
   /**
    * Gets the Baycom Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Baycom Number or the specified default value.
    */
   public final String getBaycom( int index, String defaultValue )
   {
      return _Baycom[index] == null ? defaultValue : _Baycom[index];
   }
    
   /**
    * Gets the array of Baycom Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Baycom Number values.
    */
   public final String[] getBaycomArray()
   {
      return _Baycom;
   }
    
   /**
    * Gets the Fund Group used to sort funds field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Group used to sort funds or null.
    */
   public final String getFundGroup( int index )
   {
      return _FundGroup[index];
   }
    
   /**
    * Gets the Fund Group used to sort funds field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Group used to sort funds or the specified default value.
    */
   public final String getFundGroup( int index, String defaultValue )
   {
      return _FundGroup[index] == null ? defaultValue : _FundGroup[index];
   }
    
   /**
    * Gets the array of Fund Group used to sort funds fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Group used to sort funds values.
    */
   public final String[] getFundGroupArray()
   {
      return _FundGroup;
   }
    
   /**
    * Gets the Fund/ Class ACB Available field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund/ Class ACB Available or null.
    */
   public final Boolean getFndClACBAvail( int index )
   {
      return _FndClACBAvail[index];
   }
    
   /**
    * Gets the Fund/ Class ACB Available field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund/ Class ACB Available or the specified default value.
    */
   public final boolean getFndClACBAvail( int index, boolean defaultValue )
   {
      return _FndClACBAvail[index] == null ? defaultValue : _FndClACBAvail[index].booleanValue();
   }
    
   /**
    * Gets the array of Fund/ Class ACB Available fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund/ Class ACB Available values.
    */
   public final Boolean[] getFndClACBAvailArray()
   {
      return _FndClACBAvail;
   }
    
   /**
    * Gets the Reporting Exchange Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reporting Exchange Rate or null.
    */
   public final String getReportingExchRate( int index )
   {
      return _ReportingExchRate[index];
   }
    
   /**
    * Gets the Reporting Exchange Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reporting Exchange Rate or the specified default value.
    */
   public final String getReportingExchRate( int index, String defaultValue )
   {
      return _ReportingExchRate[index] == null ? defaultValue : _ReportingExchRate[index];
   }
    
   /**
    * Gets the array of Reporting Exchange Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reporting Exchange Rate values.
    */
   public final String[] getReportingExchRateArray()
   {
      return _ReportingExchRate;
   }
    
   /**
    * Gets the NAV Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the NAV Date or null.
    */
   public final Date getNAVDate( int index )
   {
      return _NAVDate[index];
   }
    
   /**
    * Gets the NAV Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the NAV Date or the specified default value.
    */
   public final Date getNAVDate( int index, Date defaultValue )
   {
      return _NAVDate[index] == null ? defaultValue : _NAVDate[index];
   }
    
   /**
    * Gets the array of NAV Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of NAV Date values.
    */
   public final Date[] getNAVDateArray()
   {
      return _NAVDate;
   }
    
   /**
    * Gets the Allocator Fund field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Allocator Fund or null.
    */
   public final Boolean getAllocatorFund( int index )
   {
      return _AllocatorFund[index];
   }
    
   /**
    * Gets the Allocator Fund field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Allocator Fund or the specified default value.
    */
   public final boolean getAllocatorFund( int index, boolean defaultValue )
   {
      return _AllocatorFund[index] == null ? defaultValue : _AllocatorFund[index].booleanValue();
   }
    
   /**
    * Gets the array of Allocator Fund fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Allocator Fund values.
    */
   public final Boolean[] getAllocatorFundArray()
   {
      return _AllocatorFund;
   }
    
   /**
    * Gets the ACB Settled Value field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ACB Settled Value or null.
    */
   public final String getACBSettledValue( int index )
   {
      return _ACBSettledValue[index];
   }
    
   /**
    * Gets the ACB Settled Value field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ACB Settled Value or the specified default value.
    */
   public final String getACBSettledValue( int index, String defaultValue )
   {
      return _ACBSettledValue[index] == null ? defaultValue : _ACBSettledValue[index];
   }
    
   /**
    * Gets the array of ACB Settled Value fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ACB Settled Value values.
    */
   public final String[] getACBSettledValueArray()
   {
      return _ACBSettledValue;
   }
    
   /**
    * Gets the Active Certificates field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Active Certificates or null.
    */
   public final Boolean getActiveCert( int index )
   {
      return _ActiveCert[index];
   }
    
   /**
    * Gets the Active Certificates field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Active Certificates or the specified default value.
    */
   public final boolean getActiveCert( int index, boolean defaultValue )
   {
      return _ActiveCert[index] == null ? defaultValue : _ActiveCert[index].booleanValue();
   }
    
   /**
    * Gets the array of Active Certificates fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Active Certificates values.
    */
   public final Boolean[] getActiveCertArray()
   {
      return _ActiveCert;
   }
    
   /**
    * Gets the G1Balance field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the G1Balance or null.
    */
   public final String getG1Balance( int index )
   {
      return _G1Balance[index];
   }
    
   /**
    * Gets the G1Balance field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the G1Balance or the specified default value.
    */
   public final String getG1Balance( int index, String defaultValue )
   {
      return _G1Balance[index] == null ? defaultValue : _G1Balance[index];
   }
    
   /**
    * Gets the array of G1Balance fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of G1Balance values.
    */
   public final String[] getG1BalanceArray()
   {
      return _G1Balance;
   }
    
   /**
    * Gets the G2Balance field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the G2Balance or null.
    */
   public final String getG2Balance( int index )
   {
      return _G2Balance[index];
   }
    
   /**
    * Gets the G2Balance field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the G2Balance or the specified default value.
    */
   public final String getG2Balance( int index, String defaultValue )
   {
      return _G2Balance[index] == null ? defaultValue : _G2Balance[index];
   }
    
   /**
    * Gets the array of G2Balance fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of G2Balance values.
    */
   public final String[] getG2BalanceArray()
   {
      return _G2Balance;
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
      _AccountBalance = responseBuffer.decodeString(responseBuffer.getNextField());
      _FrgnBalance = responseBuffer.decodeString(responseBuffer.getNextField());
      _FrgnACBUnsettl = responseBuffer.decodeString(responseBuffer.getNextField());
      _FrgnExcsACBUnsettl = responseBuffer.decodeString(responseBuffer.getNextField());
      _TotalValueAcctCurr = responseBuffer.decodeString(responseBuffer.getNextField());
      _ShrSettledValue = responseBuffer.decodeString(responseBuffer.getNextField());
      _TotalACBSettl = responseBuffer.decodeString(responseBuffer.getNextField());
      _TotalACBUnsettl = responseBuffer.decodeString(responseBuffer.getNextField());
      _FrgnACBSettl = responseBuffer.decodeString(responseBuffer.getNextField());
      _DomesticACBSettl = responseBuffer.decodeString(responseBuffer.getNextField());
      _DomesticACBUnsettl = responseBuffer.decodeString(responseBuffer.getNextField());
      _FrgnAllowPrcnt = responseBuffer.decodeString(responseBuffer.getNextField());
      _FrgnAllowACBSettl = responseBuffer.decodeString(responseBuffer.getNextField());
      _FrgnAllowACBUnsettl = responseBuffer.decodeString(responseBuffer.getNextField());
      _FrgnExcsPrcntUnsettl = responseBuffer.decodeString(responseBuffer.getNextField());
      _FrgnExcsPrcntSettl = responseBuffer.decodeString(responseBuffer.getNextField());
      _FrgnExcsACBSettl = responseBuffer.decodeString(responseBuffer.getNextField());
      _AcctACBAvail = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _TaxOnFullRed = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _hasERISAProhibitedFund = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _AccBalUnits = responseBuffer.decodeString(responseBuffer.getNextField());
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _rxFundCode = resizeArray( _rxFundCode, _RepeatCount );
      _rxClassCode = resizeArray( _rxClassCode, _RepeatCount );
      _SettledUnits = resizeArray( _SettledUnits, _RepeatCount );
      _SettleValue = resizeArray( _SettleValue, _RepeatCount );
      _UnsettledUnits = resizeArray( _UnsettledUnits, _RepeatCount );
      _UnsettledValue = resizeArray( _UnsettledValue, _RepeatCount );
      _FundNAV = resizeArray( _FundNAV, _RepeatCount );
      _PYEUnits = resizeArray( _PYEUnits, _RepeatCount );
      _PYEValue = resizeArray( _PYEValue, _RepeatCount );
      _AsAtDate = resizeArray( _AsAtDate, _RepeatCount );
      _LastEvent = resizeArray( _LastEvent, _RepeatCount );
      _SettledValueAcctCurr = resizeArray( _SettledValueAcctCurr, _RepeatCount );
      _FundCurrency = resizeArray( _FundCurrency, _RepeatCount );
      _TradedUnits = resizeArray( _TradedUnits, _RepeatCount );
      _CombValueFundCurr = resizeArray( _CombValueFundCurr, _RepeatCount );
      _CombValueAcctCurr = resizeArray( _CombValueAcctCurr, _RepeatCount );
      _ExchRate = resizeArray( _ExchRate, _RepeatCount );
      _PendingTradeExist = resizeArray( _PendingTradeExist, _RepeatCount );
      _ACBSettl = resizeArray( _ACBSettl, _RepeatCount );
      _ACBUnsettl = resizeArray( _ACBUnsettl, _RepeatCount );
      _Baycom = resizeArray( _Baycom, _RepeatCount );
      _FundGroup = resizeArray( _FundGroup, _RepeatCount );
      _FndClACBAvail = resizeArray( _FndClACBAvail, _RepeatCount );
      _ReportingExchRate = resizeArray( _ReportingExchRate, _RepeatCount );
      _NAVDate = resizeArray( _NAVDate, _RepeatCount );
      _AllocatorFund = resizeArray( _AllocatorFund, _RepeatCount );
      _ACBSettledValue = resizeArray( _ACBSettledValue, _RepeatCount );
      _ActiveCert = resizeArray( _ActiveCert, _RepeatCount );
      _G1Balance = resizeArray( _G1Balance, _RepeatCount );
      _G2Balance = resizeArray( _G2Balance, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxFundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SettledUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SettleValue[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UnsettledUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UnsettledValue[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundNAV[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PYEUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PYEValue[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AsAtDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _LastEvent[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _SettledValueAcctCurr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundCurrency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TradedUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CombValueFundCurr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CombValueAcctCurr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ExchRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PendingTradeExist[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ACBSettl[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ACBUnsettl[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Baycom[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundGroup[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FndClACBAvail[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ReportingExchRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _NAVDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _AllocatorFund[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ACBSettledValue[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ActiveCert[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _G1Balance[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _G2Balance[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
