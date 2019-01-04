
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Account Details and Holdings view.
 * For additional view information see <A HREF="../../../../viewspecs/AccountDetailsAndHoldings.doc">AccountDetailsAndHoldings.doc</A>.
 * 
 * @author RTS Generated
 */
public class AccountDetailsAndHoldingsView extends IFastView implements Serializable
{

   /**
    * Beneficial Owner member variable.
    */
   private String _BeneficialOwner = null;
   
   /**
    * Alternate account number used by Broker/Dealer member variable.
    */
   private String _AltAccount = null;
   
   /**
    * Currency of the account (CDN, USA, etc.). member variable.
    */
   private String _Currency = null;
   
   /**
    * Account Currency Name member variable.
    */
   private String _CurrencyName = null;
   
   /**
    * Broker Code member variable.
    */
   private String _BrokerCode = null;
   
   /**
    * Branch Code member variable.
    */
   private String _BranchCode = null;
   
   /**
    * Sales Rep Code member variable.
    */
   private String _SlsRepCode = null;
   
   /**
    * Indicates status of the account member variable.
    */
   private String _AcctStat = null;
   
   /**
    * Date the client first registered their money with the fund company.                                  This date is used for GICs to calculate maturity dates. member variable.
    */
   private Date _DateOfReg = null;
   
   /**
    * Broker Name member variable.
    */
   private String _BrokerName = null;
   
   /**
    * Branch Name member variable.
    */
   private String _BranchName = null;
   
   /**
    * Sales Rep Name member variable.
    */
   private String _SlsRepName = null;
   
   /**
    * Shareholder Number member variable.
    */
   private String _ShrNum = null;
   
   /**
    * Effective Date member variable.
    */
   private Date _EffectiveDate = null;
   
   /**
    * Modify Date member variable.
    */
   private Date _ModDate = null;
   
   /**
    * Stop Purchase Flag member variable.
    */
   private Boolean _StopPurch = null;
   
   /**
    * Stop Redemption Flag member variable.
    */
   private Boolean _StopRed = null;
   
   /**
    * Stop Transfer Out Y/N member variable.
    */
   private Boolean _StopXferOut = null;
   
   /**
    * Stop Transfer in Y/N member variable.
    */
   private Boolean _StopXferIn = null;
   
   /**
    * First Name of Owner member variable.
    */
   private String _OwnerFirstName = null;
   
   /**
    * Last Name of Owner member variable.
    */
   private String _OwnerLastName = null;
   
   /**
    * Account Type member variable.
    */
   private String _AcctType = null;
   
   /**
    * Account Balance member variable.
    */
   private String _AccountBalance = null;
   
   /**
    * Total Value Account Curr member variable.
    */
   private String _TotalValueAcctCurr = null;
   
   /**
    * Taxation Type: RSP, RRIF, non-registered, etc. member variable.
    */
   private String _TaxType = null;
   
   /**
    * Tax Type Description member variable.
    */
   private String _TaxTypeDesc = null;
   
   /**
    * Account Status Description member variable.
    */
   private String _AcctStatDesc = null;
   
   /**
    * Account Type Description member variable.
    */
   private String _AcctTypeDesc = null;
   
   /**
    * Intermediary Account member variable.
    */
   private String _InterAccount = null;
   
   /**
    * Investment Objective Code member variable.
    */
   private String _InvObjCode = null;
   
   /**
    * Advisor Code member variable.
    */
   private String _AdvisorCode = null;
   
   /**
    * Advisor Description member variable.
    */
   private String _AdvisorDesc = null;
   
   /**
    * Investment Objective Description member variable.
    */
   private String _InvObjDesc = null;
   
   /**
    * Nominee Owner First Name member variable.
    */
   private String _NomineeOwnFirstN = null;
   
   /**
    * Nominee Owner Last Name member variable.
    */
   private String _NomineeOwnLastN = null;
   
   /**
    * AMS Code member variable.
    */
   private String _AMSCode = null;
   
   /**
    * Group Code member variable.
    */
   private String _AcctGroup = null;
   
   /**
    * Group Name member variable.
    */
   private String _AcctGroupName = null;
   
   private int _RepeatCount = 0;
   
   /**
    * Fund Code member array.
    */
   private String[] _FundCode = null;
   
   /**
    * Class Code member array.
    */
   private String[] _ClassCode = null;
   
   /**
    * Fund Currency member array.
    */
   private String[] _FundCurrency = null;
   
   /**
    * Settled Units member array.
    */
   private String[] _SettledUnits = null;
   
   /**
    * Settled Value member array.
    */
   private String[] _SettledValue = null;
   
   /**
    * Unsettled Units member array.
    */
   private String[] _UnsettledUnits = null;
   
   /**
    * Unsettled Value member array.
    */
   private String[] _UnsettledValue = null;
   
   /**
    * Settled Value Account Curr member array.
    */
   private String[] _SettledValueAcctCurr = null;
   
   /**
    * Traded Units member array.
    */
   private String[] _TradedUnits = null;
   
   /**
    * Combined Value Fund Curr member array.
    */
   private String[] _CombValueFundCurr = null;
   
   /**
    * Combined Value Acct Curr member array.
    */
   private String[] _CombValueAcctCurr = null;
   
   /**
    * Exchange Rate member array.
    */
   private String[] _ExchRate = null;
   
   /**
    * Pending Trade Exists Y/N member array.
    */
   private Boolean[] _PendingTradeExist = null;
   
   /**
    * Previous Year End Units member array.
    */
   private String[] _PYEUnits = null;
   
   /**
    * Previous Year End Value member array.
    */
   private String[] _PYEValue = null;
   
   /**
    * Last Event member array.
    */
   private Date[] _LastEvent = null;
   
   /**
    * As At Date member array.
    */
   private Date[] _AsAtDate = null;
   
   /**
    * Fund NAV member array.
    */
   private String[] _FundNAV = null;
   
   /**
    * Sponsor Name member array.
    */
   private String[] _SponsorName = null;
   
   /**
    * Sponsor Code member array.
    */
   private String[] _SponsorCode = null;
   
   /**
    * Fund Long Name member array.
    */
   private String[] _FundName = null;
   
   /**
    * Distribution Pay Type member array.
    */
   private String[] _DistribPayType = null;
   
   /**
    * Pending Trade Available Y/N member array.
    */
   private Boolean[] _PendingTradeAvail = null;
   
   /**
    * Reporting Exchange Rate member array.
    */
   private String[] _ReportingExchRate = null;
   

   /**
    * Constructs the AccountDetailsAndHoldingsView object.
    * 
    */
   public AccountDetailsAndHoldingsView()
   {
      super ( new AccountDetailsAndHoldingsRequest() );
   }

   /**
    * Constructs the AccountDetailsAndHoldingsView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AccountDetailsAndHoldingsView( String hostEncoding )
   {
      super ( new AccountDetailsAndHoldingsRequest( hostEncoding ) );
   }

   /**
    * Gets the AccountDetailsAndHoldingsRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AccountDetailsAndHoldingsRequest object.
    */
   public final AccountDetailsAndHoldingsRequest getRequest()
   {
      return (AccountDetailsAndHoldingsRequest)getIFastRequest();
   }
        
   /**
    * Gets the Beneficial Owner field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Beneficial Owner or null.
    */
   public final String getBeneficialOwner()
   {
      return _BeneficialOwner;
   }
	
   /**
    * Gets the Beneficial Owner field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Beneficial Owner or the specified default value.
    */
   public final String getBeneficialOwner( String defaultValue )
   {
      return _BeneficialOwner == null ? defaultValue : _BeneficialOwner;
   }
                  
   /**
    * Gets the Alternate account number used by Broker/Dealer field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Alternate account number used by Broker/Dealer or null.
    */
   public final String getAltAccount()
   {
      return _AltAccount;
   }
	
   /**
    * Gets the Alternate account number used by Broker/Dealer field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Alternate account number used by Broker/Dealer or the specified default value.
    */
   public final String getAltAccount( String defaultValue )
   {
      return _AltAccount == null ? defaultValue : _AltAccount;
   }
                  
   /**
    * Gets the Currency of the account (CDN, USA, etc.). field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Currency of the account (CDN, USA, etc.). or null.
    */
   public final String getCurrency()
   {
      return _Currency;
   }
	
   /**
    * Gets the Currency of the account (CDN, USA, etc.). field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Currency of the account (CDN, USA, etc.). or the specified default value.
    */
   public final String getCurrency( String defaultValue )
   {
      return _Currency == null ? defaultValue : _Currency;
   }
                  
   /**
    * Gets the Account Currency Name field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Account Currency Name or null.
    */
   public final String getCurrencyName()
   {
      return _CurrencyName;
   }
	
   /**
    * Gets the Account Currency Name field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Currency Name or the specified default value.
    */
   public final String getCurrencyName( String defaultValue )
   {
      return _CurrencyName == null ? defaultValue : _CurrencyName;
   }
                  
   /**
    * Gets the Broker Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Broker Code or null.
    */
   public final String getBrokerCode()
   {
      return _BrokerCode;
   }
	
   /**
    * Gets the Broker Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker Code or the specified default value.
    */
   public final String getBrokerCode( String defaultValue )
   {
      return _BrokerCode == null ? defaultValue : _BrokerCode;
   }
                  
   /**
    * Gets the Branch Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Branch Code or null.
    */
   public final String getBranchCode()
   {
      return _BranchCode;
   }
	
   /**
    * Gets the Branch Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Branch Code or the specified default value.
    */
   public final String getBranchCode( String defaultValue )
   {
      return _BranchCode == null ? defaultValue : _BranchCode;
   }
                  
   /**
    * Gets the Sales Rep Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Sales Rep Code or null.
    */
   public final String getSlsRepCode()
   {
      return _SlsRepCode;
   }
	
   /**
    * Gets the Sales Rep Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Sales Rep Code or the specified default value.
    */
   public final String getSlsRepCode( String defaultValue )
   {
      return _SlsRepCode == null ? defaultValue : _SlsRepCode;
   }
                  
   /**
    * Gets the Indicates status of the account field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Indicates status of the account or null.
    */
   public final String getAcctStat()
   {
      return _AcctStat;
   }
	
   /**
    * Gets the Indicates status of the account field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Indicates status of the account or the specified default value.
    */
   public final String getAcctStat( String defaultValue )
   {
      return _AcctStat == null ? defaultValue : _AcctStat;
   }
                  
   /**
    * Gets the Date the client first registered their money with the fund company.                                  This date is used for GICs to calculate maturity dates. field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Date the client first registered their money with the fund company.                                  This date is used for GICs to calculate maturity dates. or null.
    */
   public final Date getDateOfReg()
   {
      return _DateOfReg;
   }
	
   /**
    * Gets the Date the client first registered their money with the fund company.                                  This date is used for GICs to calculate maturity dates. field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date the client first registered their money with the fund company.                                  This date is used for GICs to calculate maturity dates. or the specified default value.
    */
   public final Date getDateOfReg( Date defaultValue )
   {
      return _DateOfReg == null ? defaultValue : _DateOfReg;
   }
                  
   /**
    * Gets the Broker Name field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Broker Name or null.
    */
   public final String getBrokerName()
   {
      return _BrokerName;
   }
	
   /**
    * Gets the Broker Name field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker Name or the specified default value.
    */
   public final String getBrokerName( String defaultValue )
   {
      return _BrokerName == null ? defaultValue : _BrokerName;
   }
                  
   /**
    * Gets the Branch Name field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Branch Name or null.
    */
   public final String getBranchName()
   {
      return _BranchName;
   }
	
   /**
    * Gets the Branch Name field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Branch Name or the specified default value.
    */
   public final String getBranchName( String defaultValue )
   {
      return _BranchName == null ? defaultValue : _BranchName;
   }
                  
   /**
    * Gets the Sales Rep Name field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Sales Rep Name or null.
    */
   public final String getSlsRepName()
   {
      return _SlsRepName;
   }
	
   /**
    * Gets the Sales Rep Name field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Sales Rep Name or the specified default value.
    */
   public final String getSlsRepName( String defaultValue )
   {
      return _SlsRepName == null ? defaultValue : _SlsRepName;
   }
                  
   /**
    * Gets the Shareholder Number field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Shareholder Number or null.
    */
   public final String getShrNum()
   {
      return _ShrNum;
   }
	
   /**
    * Gets the Shareholder Number field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Shareholder Number or the specified default value.
    */
   public final String getShrNum( String defaultValue )
   {
      return _ShrNum == null ? defaultValue : _ShrNum;
   }
                  
   /**
    * Gets the Effective Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Effective Date or null.
    */
   public final Date getEffectiveDate()
   {
      return _EffectiveDate;
   }
	
   /**
    * Gets the Effective Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Effective Date or the specified default value.
    */
   public final Date getEffectiveDate( Date defaultValue )
   {
      return _EffectiveDate == null ? defaultValue : _EffectiveDate;
   }
                  
   /**
    * Gets the Modify Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Modify Date or null.
    */
   public final Date getModDate()
   {
      return _ModDate;
   }
	
   /**
    * Gets the Modify Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Modify Date or the specified default value.
    */
   public final Date getModDate( Date defaultValue )
   {
      return _ModDate == null ? defaultValue : _ModDate;
   }
                  
   /**
    * Gets the Stop Purchase Flag field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Stop Purchase Flag or null.
    */
   public final Boolean getStopPurch()
   {
      return _StopPurch;
   }
	
   /**
    * Gets the Stop Purchase Flag field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Purchase Flag or the specified default value.
    */
   public final boolean getStopPurch( boolean defaultValue )
   {
      return _StopPurch == null ? defaultValue : _StopPurch.booleanValue();
   }
                  
   /**
    * Gets the Stop Redemption Flag field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Stop Redemption Flag or null.
    */
   public final Boolean getStopRed()
   {
      return _StopRed;
   }
	
   /**
    * Gets the Stop Redemption Flag field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Redemption Flag or the specified default value.
    */
   public final boolean getStopRed( boolean defaultValue )
   {
      return _StopRed == null ? defaultValue : _StopRed.booleanValue();
   }
                  
   /**
    * Gets the Stop Transfer Out Y/N field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Stop Transfer Out Y/N or null.
    */
   public final Boolean getStopXferOut()
   {
      return _StopXferOut;
   }
	
   /**
    * Gets the Stop Transfer Out Y/N field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Transfer Out Y/N or the specified default value.
    */
   public final boolean getStopXferOut( boolean defaultValue )
   {
      return _StopXferOut == null ? defaultValue : _StopXferOut.booleanValue();
   }
                  
   /**
    * Gets the Stop Transfer in Y/N field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Stop Transfer in Y/N or null.
    */
   public final Boolean getStopXferIn()
   {
      return _StopXferIn;
   }
	
   /**
    * Gets the Stop Transfer in Y/N field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Transfer in Y/N or the specified default value.
    */
   public final boolean getStopXferIn( boolean defaultValue )
   {
      return _StopXferIn == null ? defaultValue : _StopXferIn.booleanValue();
   }
                  
   /**
    * Gets the First Name of Owner field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the First Name of Owner or null.
    */
   public final String getOwnerFirstName()
   {
      return _OwnerFirstName;
   }
	
   /**
    * Gets the First Name of Owner field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the First Name of Owner or the specified default value.
    */
   public final String getOwnerFirstName( String defaultValue )
   {
      return _OwnerFirstName == null ? defaultValue : _OwnerFirstName;
   }
                  
   /**
    * Gets the Last Name of Owner field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Last Name of Owner or null.
    */
   public final String getOwnerLastName()
   {
      return _OwnerLastName;
   }
	
   /**
    * Gets the Last Name of Owner field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Last Name of Owner or the specified default value.
    */
   public final String getOwnerLastName( String defaultValue )
   {
      return _OwnerLastName == null ? defaultValue : _OwnerLastName;
   }
                  
   /**
    * Gets the Account Type field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Account Type or null.
    */
   public final String getAcctType()
   {
      return _AcctType;
   }
	
   /**
    * Gets the Account Type field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Type or the specified default value.
    */
   public final String getAcctType( String defaultValue )
   {
      return _AcctType == null ? defaultValue : _AcctType;
   }
                  
   /**
    * Gets the Account Balance field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Account Balance or null.
    */
   public final String getAccountBalance()
   {
      return _AccountBalance;
   }
	
   /**
    * Gets the Account Balance field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Balance or the specified default value.
    */
   public final String getAccountBalance( String defaultValue )
   {
      return _AccountBalance == null ? defaultValue : _AccountBalance;
   }
                  
   /**
    * Gets the Total Value Account Curr field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Total Value Account Curr or null.
    */
   public final String getTotalValueAcctCurr()
   {
      return _TotalValueAcctCurr;
   }
	
   /**
    * Gets the Total Value Account Curr field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Total Value Account Curr or the specified default value.
    */
   public final String getTotalValueAcctCurr( String defaultValue )
   {
      return _TotalValueAcctCurr == null ? defaultValue : _TotalValueAcctCurr;
   }
                  
   /**
    * Gets the Taxation Type: RSP, RRIF, non-registered, etc. field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Taxation Type: RSP, RRIF, non-registered, etc. or null.
    */
   public final String getTaxType()
   {
      return _TaxType;
   }
	
   /**
    * Gets the Taxation Type: RSP, RRIF, non-registered, etc. field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Taxation Type: RSP, RRIF, non-registered, etc. or the specified default value.
    */
   public final String getTaxType( String defaultValue )
   {
      return _TaxType == null ? defaultValue : _TaxType;
   }
                  
   /**
    * Gets the Tax Type Description field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Tax Type Description or null.
    */
   public final String getTaxTypeDesc()
   {
      return _TaxTypeDesc;
   }
	
   /**
    * Gets the Tax Type Description field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Type Description or the specified default value.
    */
   public final String getTaxTypeDesc( String defaultValue )
   {
      return _TaxTypeDesc == null ? defaultValue : _TaxTypeDesc;
   }
                  
   /**
    * Gets the Account Status Description field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Account Status Description or null.
    */
   public final String getAcctStatDesc()
   {
      return _AcctStatDesc;
   }
	
   /**
    * Gets the Account Status Description field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Status Description or the specified default value.
    */
   public final String getAcctStatDesc( String defaultValue )
   {
      return _AcctStatDesc == null ? defaultValue : _AcctStatDesc;
   }
                  
   /**
    * Gets the Account Type Description field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Account Type Description or null.
    */
   public final String getAcctTypeDesc()
   {
      return _AcctTypeDesc;
   }
	
   /**
    * Gets the Account Type Description field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Type Description or the specified default value.
    */
   public final String getAcctTypeDesc( String defaultValue )
   {
      return _AcctTypeDesc == null ? defaultValue : _AcctTypeDesc;
   }
                  
   /**
    * Gets the Intermediary Account field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Intermediary Account or null.
    */
   public final String getInterAccount()
   {
      return _InterAccount;
   }
	
   /**
    * Gets the Intermediary Account field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Intermediary Account or the specified default value.
    */
   public final String getInterAccount( String defaultValue )
   {
      return _InterAccount == null ? defaultValue : _InterAccount;
   }
                  
   /**
    * Gets the Investment Objective Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Investment Objective Code or null.
    */
   public final String getInvObjCode()
   {
      return _InvObjCode;
   }
	
   /**
    * Gets the Investment Objective Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Investment Objective Code or the specified default value.
    */
   public final String getInvObjCode( String defaultValue )
   {
      return _InvObjCode == null ? defaultValue : _InvObjCode;
   }
                  
   /**
    * Gets the Advisor Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Advisor Code or null.
    */
   public final String getAdvisorCode()
   {
      return _AdvisorCode;
   }
	
   /**
    * Gets the Advisor Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Advisor Code or the specified default value.
    */
   public final String getAdvisorCode( String defaultValue )
   {
      return _AdvisorCode == null ? defaultValue : _AdvisorCode;
   }
                  
   /**
    * Gets the Advisor Description field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Advisor Description or null.
    */
   public final String getAdvisorDesc()
   {
      return _AdvisorDesc;
   }
	
   /**
    * Gets the Advisor Description field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Advisor Description or the specified default value.
    */
   public final String getAdvisorDesc( String defaultValue )
   {
      return _AdvisorDesc == null ? defaultValue : _AdvisorDesc;
   }
                  
   /**
    * Gets the Investment Objective Description field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Investment Objective Description or null.
    */
   public final String getInvObjDesc()
   {
      return _InvObjDesc;
   }
	
   /**
    * Gets the Investment Objective Description field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Investment Objective Description or the specified default value.
    */
   public final String getInvObjDesc( String defaultValue )
   {
      return _InvObjDesc == null ? defaultValue : _InvObjDesc;
   }
                  
   /**
    * Gets the Nominee Owner First Name field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Nominee Owner First Name or null.
    */
   public final String getNomineeOwnFirstN()
   {
      return _NomineeOwnFirstN;
   }
	
   /**
    * Gets the Nominee Owner First Name field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Nominee Owner First Name or the specified default value.
    */
   public final String getNomineeOwnFirstN( String defaultValue )
   {
      return _NomineeOwnFirstN == null ? defaultValue : _NomineeOwnFirstN;
   }
                  
   /**
    * Gets the Nominee Owner Last Name field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Nominee Owner Last Name or null.
    */
   public final String getNomineeOwnLastN()
   {
      return _NomineeOwnLastN;
   }
	
   /**
    * Gets the Nominee Owner Last Name field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Nominee Owner Last Name or the specified default value.
    */
   public final String getNomineeOwnLastN( String defaultValue )
   {
      return _NomineeOwnLastN == null ? defaultValue : _NomineeOwnLastN;
   }
                  
   /**
    * Gets the AMS Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the AMS Code or null.
    */
   public final String getAMSCode()
   {
      return _AMSCode;
   }
	
   /**
    * Gets the AMS Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AMS Code or the specified default value.
    */
   public final String getAMSCode( String defaultValue )
   {
      return _AMSCode == null ? defaultValue : _AMSCode;
   }
                  
   /**
    * Gets the Group Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Group Code or null.
    */
   public final String getAcctGroup()
   {
      return _AcctGroup;
   }
	
   /**
    * Gets the Group Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Group Code or the specified default value.
    */
   public final String getAcctGroup( String defaultValue )
   {
      return _AcctGroup == null ? defaultValue : _AcctGroup;
   }
                  
   /**
    * Gets the Group Name field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Group Name or null.
    */
   public final String getAcctGroupName()
   {
      return _AcctGroupName;
   }
	
   /**
    * Gets the Group Name field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Group Name or the specified default value.
    */
   public final String getAcctGroupName( String defaultValue )
   {
      return _AcctGroupName == null ? defaultValue : _AcctGroupName;
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
    * Gets the Settled Units field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Settled Units or null.
    */
   public final String getSettledUnits( int index )
   {
      return _SettledUnits[index];
   }
    
   /**
    * Gets the Settled Units field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settled Units or the specified default value.
    */
   public final String getSettledUnits( int index, String defaultValue )
   {
      return _SettledUnits[index] == null ? defaultValue : _SettledUnits[index];
   }
    
   /**
    * Gets the array of Settled Units fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Settled Units values.
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
   public final String getSettledValue( int index )
   {
      return _SettledValue[index];
   }
    
   /**
    * Gets the Settled Value field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settled Value or the specified default value.
    */
   public final String getSettledValue( int index, String defaultValue )
   {
      return _SettledValue[index] == null ? defaultValue : _SettledValue[index];
   }
    
   /**
    * Gets the array of Settled Value fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Settled Value values.
    */
   public final String[] getSettledValueArray()
   {
      return _SettledValue;
   }
    
   /**
    * Gets the Unsettled Units field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Unsettled Units or null.
    */
   public final String getUnsettledUnits( int index )
   {
      return _UnsettledUnits[index];
   }
    
   /**
    * Gets the Unsettled Units field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Unsettled Units or the specified default value.
    */
   public final String getUnsettledUnits( int index, String defaultValue )
   {
      return _UnsettledUnits[index] == null ? defaultValue : _UnsettledUnits[index];
   }
    
   /**
    * Gets the array of Unsettled Units fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Unsettled Units values.
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
    * Gets the Settled Value Account Curr field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Settled Value Account Curr or null.
    */
   public final String getSettledValueAcctCurr( int index )
   {
      return _SettledValueAcctCurr[index];
   }
    
   /**
    * Gets the Settled Value Account Curr field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settled Value Account Curr or the specified default value.
    */
   public final String getSettledValueAcctCurr( int index, String defaultValue )
   {
      return _SettledValueAcctCurr[index] == null ? defaultValue : _SettledValueAcctCurr[index];
   }
    
   /**
    * Gets the array of Settled Value Account Curr fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Settled Value Account Curr values.
    */
   public final String[] getSettledValueAcctCurrArray()
   {
      return _SettledValueAcctCurr;
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
    * Gets the Combined Value Fund Curr field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Combined Value Fund Curr or null.
    */
   public final String getCombValueFundCurr( int index )
   {
      return _CombValueFundCurr[index];
   }
    
   /**
    * Gets the Combined Value Fund Curr field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Combined Value Fund Curr or the specified default value.
    */
   public final String getCombValueFundCurr( int index, String defaultValue )
   {
      return _CombValueFundCurr[index] == null ? defaultValue : _CombValueFundCurr[index];
   }
    
   /**
    * Gets the array of Combined Value Fund Curr fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Combined Value Fund Curr values.
    */
   public final String[] getCombValueFundCurrArray()
   {
      return _CombValueFundCurr;
   }
    
   /**
    * Gets the Combined Value Acct Curr field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Combined Value Acct Curr or null.
    */
   public final String getCombValueAcctCurr( int index )
   {
      return _CombValueAcctCurr[index];
   }
    
   /**
    * Gets the Combined Value Acct Curr field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Combined Value Acct Curr or the specified default value.
    */
   public final String getCombValueAcctCurr( int index, String defaultValue )
   {
      return _CombValueAcctCurr[index] == null ? defaultValue : _CombValueAcctCurr[index];
   }
    
   /**
    * Gets the array of Combined Value Acct Curr fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Combined Value Acct Curr values.
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
    * Gets the Pending Trade Exists Y/N field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Pending Trade Exists Y/N or null.
    */
   public final Boolean getPendingTradeExist( int index )
   {
      return _PendingTradeExist[index];
   }
    
   /**
    * Gets the Pending Trade Exists Y/N field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pending Trade Exists Y/N or the specified default value.
    */
   public final boolean getPendingTradeExist( int index, boolean defaultValue )
   {
      return _PendingTradeExist[index] == null ? defaultValue : _PendingTradeExist[index].booleanValue();
   }
    
   /**
    * Gets the array of Pending Trade Exists Y/N fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Pending Trade Exists Y/N values.
    */
   public final Boolean[] getPendingTradeExistArray()
   {
      return _PendingTradeExist;
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
    * Gets the Last Event field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Last Event or null.
    */
   public final Date getLastEvent( int index )
   {
      return _LastEvent[index];
   }
    
   /**
    * Gets the Last Event field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Last Event or the specified default value.
    */
   public final Date getLastEvent( int index, Date defaultValue )
   {
      return _LastEvent[index] == null ? defaultValue : _LastEvent[index];
   }
    
   /**
    * Gets the array of Last Event fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Last Event values.
    */
   public final Date[] getLastEventArray()
   {
      return _LastEvent;
   }
    
   /**
    * Gets the As At Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the As At Date or null.
    */
   public final Date getAsAtDate( int index )
   {
      return _AsAtDate[index];
   }
    
   /**
    * Gets the As At Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the As At Date or the specified default value.
    */
   public final Date getAsAtDate( int index, Date defaultValue )
   {
      return _AsAtDate[index] == null ? defaultValue : _AsAtDate[index];
   }
    
   /**
    * Gets the array of As At Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of As At Date values.
    */
   public final Date[] getAsAtDateArray()
   {
      return _AsAtDate;
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
    * Gets the Sponsor Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Sponsor Name or null.
    */
   public final String getSponsorName( int index )
   {
      return _SponsorName[index];
   }
    
   /**
    * Gets the Sponsor Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Sponsor Name or the specified default value.
    */
   public final String getSponsorName( int index, String defaultValue )
   {
      return _SponsorName[index] == null ? defaultValue : _SponsorName[index];
   }
    
   /**
    * Gets the array of Sponsor Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Sponsor Name values.
    */
   public final String[] getSponsorNameArray()
   {
      return _SponsorName;
   }
    
   /**
    * Gets the Sponsor Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Sponsor Code or null.
    */
   public final String getSponsorCode( int index )
   {
      return _SponsorCode[index];
   }
    
   /**
    * Gets the Sponsor Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Sponsor Code or the specified default value.
    */
   public final String getSponsorCode( int index, String defaultValue )
   {
      return _SponsorCode[index] == null ? defaultValue : _SponsorCode[index];
   }
    
   /**
    * Gets the array of Sponsor Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Sponsor Code values.
    */
   public final String[] getSponsorCodeArray()
   {
      return _SponsorCode;
   }
    
   /**
    * Gets the Fund Long Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Long Name or null.
    */
   public final String getFundName( int index )
   {
      return _FundName[index];
   }
    
   /**
    * Gets the Fund Long Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Long Name or the specified default value.
    */
   public final String getFundName( int index, String defaultValue )
   {
      return _FundName[index] == null ? defaultValue : _FundName[index];
   }
    
   /**
    * Gets the array of Fund Long Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Long Name values.
    */
   public final String[] getFundNameArray()
   {
      return _FundName;
   }
    
   /**
    * Gets the Distribution Pay Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Distribution Pay Type or null.
    */
   public final String getDistribPayType( int index )
   {
      return _DistribPayType[index];
   }
    
   /**
    * Gets the Distribution Pay Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Distribution Pay Type or the specified default value.
    */
   public final String getDistribPayType( int index, String defaultValue )
   {
      return _DistribPayType[index] == null ? defaultValue : _DistribPayType[index];
   }
    
   /**
    * Gets the array of Distribution Pay Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Distribution Pay Type values.
    */
   public final String[] getDistribPayTypeArray()
   {
      return _DistribPayType;
   }
    
   /**
    * Gets the Pending Trade Available Y/N field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Pending Trade Available Y/N or null.
    */
   public final Boolean getPendingTradeAvail( int index )
   {
      return _PendingTradeAvail[index];
   }
    
   /**
    * Gets the Pending Trade Available Y/N field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pending Trade Available Y/N or the specified default value.
    */
   public final boolean getPendingTradeAvail( int index, boolean defaultValue )
   {
      return _PendingTradeAvail[index] == null ? defaultValue : _PendingTradeAvail[index].booleanValue();
   }
    
   /**
    * Gets the array of Pending Trade Available Y/N fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Pending Trade Available Y/N values.
    */
   public final Boolean[] getPendingTradeAvailArray()
   {
      return _PendingTradeAvail;
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
      _BeneficialOwner = responseBuffer.decodeString(responseBuffer.getNextField());
      _AltAccount = responseBuffer.decodeString(responseBuffer.getNextField());
      _Currency = responseBuffer.decodeString(responseBuffer.getNextField());
      _CurrencyName = responseBuffer.decodeString(responseBuffer.getNextField());
      _BrokerCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _BranchCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _SlsRepCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _AcctStat = responseBuffer.decodeString(responseBuffer.getNextField());
      _DateOfReg = responseBuffer.decodeDate(responseBuffer.getNextField());
      _BrokerName = responseBuffer.decodeString(responseBuffer.getNextField());
      _BranchName = responseBuffer.decodeString(responseBuffer.getNextField());
      _SlsRepName = responseBuffer.decodeString(responseBuffer.getNextField());
      _ShrNum = responseBuffer.decodeString(responseBuffer.getNextField());
      _EffectiveDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _ModDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _StopPurch = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _StopRed = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _StopXferOut = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _StopXferIn = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _OwnerFirstName = responseBuffer.decodeString(responseBuffer.getNextField());
      _OwnerLastName = responseBuffer.decodeString(responseBuffer.getNextField());
      _AcctType = responseBuffer.decodeString(responseBuffer.getNextField());
      _AccountBalance = responseBuffer.decodeString(responseBuffer.getNextField());
      _TotalValueAcctCurr = responseBuffer.decodeString(responseBuffer.getNextField());
      _TaxType = responseBuffer.decodeString(responseBuffer.getNextField());
      _TaxTypeDesc = responseBuffer.decodeString(responseBuffer.getNextField());
      _AcctStatDesc = responseBuffer.decodeString(responseBuffer.getNextField());
      _AcctTypeDesc = responseBuffer.decodeString(responseBuffer.getNextField());
      _InterAccount = responseBuffer.decodeString(responseBuffer.getNextField());
      _InvObjCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _AdvisorCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _AdvisorDesc = responseBuffer.decodeString(responseBuffer.getNextField());
      _InvObjDesc = responseBuffer.decodeString(responseBuffer.getNextField());
      _NomineeOwnFirstN = responseBuffer.decodeString(responseBuffer.getNextField());
      _NomineeOwnLastN = responseBuffer.decodeString(responseBuffer.getNextField());
      _AMSCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _AcctGroup = responseBuffer.decodeString(responseBuffer.getNextField());
      _AcctGroupName = responseBuffer.decodeString(responseBuffer.getNextField());
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _FundCode = resizeArray( _FundCode, _RepeatCount );
      _ClassCode = resizeArray( _ClassCode, _RepeatCount );
      _FundCurrency = resizeArray( _FundCurrency, _RepeatCount );
      _SettledUnits = resizeArray( _SettledUnits, _RepeatCount );
      _SettledValue = resizeArray( _SettledValue, _RepeatCount );
      _UnsettledUnits = resizeArray( _UnsettledUnits, _RepeatCount );
      _UnsettledValue = resizeArray( _UnsettledValue, _RepeatCount );
      _SettledValueAcctCurr = resizeArray( _SettledValueAcctCurr, _RepeatCount );
      _TradedUnits = resizeArray( _TradedUnits, _RepeatCount );
      _CombValueFundCurr = resizeArray( _CombValueFundCurr, _RepeatCount );
      _CombValueAcctCurr = resizeArray( _CombValueAcctCurr, _RepeatCount );
      _ExchRate = resizeArray( _ExchRate, _RepeatCount );
      _PendingTradeExist = resizeArray( _PendingTradeExist, _RepeatCount );
      _PYEUnits = resizeArray( _PYEUnits, _RepeatCount );
      _PYEValue = resizeArray( _PYEValue, _RepeatCount );
      _LastEvent = resizeArray( _LastEvent, _RepeatCount );
      _AsAtDate = resizeArray( _AsAtDate, _RepeatCount );
      _FundNAV = resizeArray( _FundNAV, _RepeatCount );
      _SponsorName = resizeArray( _SponsorName, _RepeatCount );
      _SponsorCode = resizeArray( _SponsorCode, _RepeatCount );
      _FundName = resizeArray( _FundName, _RepeatCount );
      _DistribPayType = resizeArray( _DistribPayType, _RepeatCount );
      _PendingTradeAvail = resizeArray( _PendingTradeAvail, _RepeatCount );
      _ReportingExchRate = resizeArray( _ReportingExchRate, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _FundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundCurrency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SettledUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SettledValue[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UnsettledUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UnsettledValue[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SettledValueAcctCurr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TradedUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CombValueFundCurr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CombValueAcctCurr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ExchRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PendingTradeExist[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _PYEUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PYEValue[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LastEvent[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _AsAtDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _FundNAV[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SponsorName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SponsorCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DistribPayType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PendingTradeAvail[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ReportingExchRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
