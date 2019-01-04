
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * FundCom Auto Activity Detail Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/AutoActivityDetail.doc">AutoActivityDetail.doc</A>.
 * 
 * @author RTS Generated
 */
public class AutoActivityDetailView extends IFastView implements Serializable
{

   /**
    * Intermediary Code member variable.
    */
   private String _IntermCode = null;
   
   /**
    * Auto Activity Status member variable.
    */
   private String _ActivityStatus = null;
   
   /**
    * Start Date of Systematic member variable.
    */
   private Date _EffectiveDate = null;
   
   /**
    * Frequency of Systematic member variable.
    */
   private Integer _SystematicFreq = null;
   
   /**
    * Stop Date member variable.
    */
   private Date _StopDate = null;
   
   /**
    * Restart Date member variable.
    */
   private Date _RestartDate = null;
   
   /**
    * Next Process Date member variable.
    */
   private Date _NextProcDate = null;
   
   /**
    * Fund Baycom Number member variable.
    */
   private String _Baycom = null;
   
   /**
    * Fund English Long Name member variable.
    */
   private String _ElongName1 = null;
   
   /**
    * Percentage, Dollars or Units member variable.
    */
   private String _AmountType = null;
   
   /**
    * Amount member variable.
    */
   private String _Amount = null;
   
   /**
    * Client Commission member variable.
    */
   private String _Fee = null;
   
   /**
    * Gross or Net member variable.
    */
   private Boolean _GrossOrNet = null;
   
   /**
    * Payee Indicator member variable.
    */
   private String _PayeeIndicator = null;
   
   /**
    * Bank Institution Code member variable.
    */
   private Integer _InstCode = null;
   
   /**
    * Bank Transit Number member variable.
    */
   private Integer _TransitNo = null;
   
   /**
    * Bank Account Number member variable.
    */
   private String _BankAcctNum = null;
   
   /**
    * Fund Currency member variable.
    */
   private String _Currency = null;
   
   /**
    * Transfer Fund Baycom Number member variable.
    */
   private String _BaycomTo = null;
   
   /**
    * English Long Name of Fund To member variable.
    */
   private String _ElongName2 = null;
   
   /**
    * Bank Account Type member variable.
    */
   private String _BankAcctType = null;
   
   /**
    * Bank Account Name member variable.
    */
   private String _BankAcctName = null;
   
   /**
    * Address Name 1 member variable.
    */
   private String _Name1 = null;
   
   /**
    * Address Name 2 member variable.
    */
   private String _Name2 = null;
   
   /**
    * Address Code member variable.
    */
   private String _AddrCode = null;
   
   /**
    * Address Line 1 member variable.
    */
   private String _AddrLine1 = null;
   
   /**
    * Address Line 2 member variable.
    */
   private String _AddrLine2 = null;
   
   /**
    * Address Line 3 member variable.
    */
   private String _AddrLine3 = null;
   
   /**
    * Address Line 4 member variable.
    */
   private String _AddrLine4 = null;
   
   /**
    * Address Line 5 member variable.
    */
   private String _AddrLine5 = null;
   
   /**
    * City member variable.
    */
   private String _City = null;
   
   /**
    * Country Code member variable.
    */
   private String _CountryCode = null;
   
   /**
    * Postal Code member variable.
    */
   private String _PostalCode = null;
   
   /**
    * Gross or Net - Purchase member variable.
    */
   private Boolean _GrossOrNetPurch = null;
   
   /**
    * Gross or Net - Redemption member variable.
    */
   private Boolean _GrossOrNetRed = null;
   
   /**
    * Commission Entity member variable.
    */
   private String _CommEntity = null;
   
   /**
    * Fee Type - Flat/ Percent member variable.
    */
   private Boolean _FlatPrcnt = null;
   
   /**
    * Transfer To Account member variable.
    */
   private String _AccountTo = null;
   
   /**
    * Country Description member variable.
    */
   private String _CountryDesc = null;
   

   /**
    * Constructs the AutoActivityDetailView object.
    * 
    */
   public AutoActivityDetailView()
   {
      super ( new AutoActivityDetailRequest() );
   }

   /**
    * Constructs the AutoActivityDetailView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AutoActivityDetailView( String hostEncoding )
   {
      super ( new AutoActivityDetailRequest( hostEncoding ) );
   }

   /**
    * Gets the AutoActivityDetailRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AutoActivityDetailRequest object.
    */
   public final AutoActivityDetailRequest getRequest()
   {
      return (AutoActivityDetailRequest)getIFastRequest();
   }
        
   /**
    * Gets the Intermediary Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Intermediary Code or null.
    */
   public final String getIntermCode()
   {
      return _IntermCode;
   }
	
   /**
    * Gets the Intermediary Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Intermediary Code or the specified default value.
    */
   public final String getIntermCode( String defaultValue )
   {
      return _IntermCode == null ? defaultValue : _IntermCode;
   }
                  
   /**
    * Gets the Auto Activity Status field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Auto Activity Status or null.
    */
   public final String getActivityStatus()
   {
      return _ActivityStatus;
   }
	
   /**
    * Gets the Auto Activity Status field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Auto Activity Status or the specified default value.
    */
   public final String getActivityStatus( String defaultValue )
   {
      return _ActivityStatus == null ? defaultValue : _ActivityStatus;
   }
                  
   /**
    * Gets the Start Date of Systematic field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Start Date of Systematic or null.
    */
   public final Date getEffectiveDate()
   {
      return _EffectiveDate;
   }
	
   /**
    * Gets the Start Date of Systematic field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Start Date of Systematic or the specified default value.
    */
   public final Date getEffectiveDate( Date defaultValue )
   {
      return _EffectiveDate == null ? defaultValue : _EffectiveDate;
   }
                  
   /**
    * Gets the Frequency of Systematic field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Frequency of Systematic or null.
    */
   public final Integer getSystematicFreq()
   {
      return _SystematicFreq;
   }
	
   /**
    * Gets the Frequency of Systematic field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Frequency of Systematic or the specified default value.
    */
   public final int getSystematicFreq( int defaultValue )
   {
      return _SystematicFreq == null ? defaultValue : _SystematicFreq.intValue();
   }
                  
   /**
    * Gets the Stop Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Stop Date or null.
    */
   public final Date getStopDate()
   {
      return _StopDate;
   }
	
   /**
    * Gets the Stop Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Date or the specified default value.
    */
   public final Date getStopDate( Date defaultValue )
   {
      return _StopDate == null ? defaultValue : _StopDate;
   }
                  
   /**
    * Gets the Restart Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Restart Date or null.
    */
   public final Date getRestartDate()
   {
      return _RestartDate;
   }
	
   /**
    * Gets the Restart Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Restart Date or the specified default value.
    */
   public final Date getRestartDate( Date defaultValue )
   {
      return _RestartDate == null ? defaultValue : _RestartDate;
   }
                  
   /**
    * Gets the Next Process Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Next Process Date or null.
    */
   public final Date getNextProcDate()
   {
      return _NextProcDate;
   }
	
   /**
    * Gets the Next Process Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Next Process Date or the specified default value.
    */
   public final Date getNextProcDate( Date defaultValue )
   {
      return _NextProcDate == null ? defaultValue : _NextProcDate;
   }
                  
   /**
    * Gets the Fund Baycom Number field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Fund Baycom Number or null.
    */
   public final String getBaycom()
   {
      return _Baycom;
   }
	
   /**
    * Gets the Fund Baycom Number field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Baycom Number or the specified default value.
    */
   public final String getBaycom( String defaultValue )
   {
      return _Baycom == null ? defaultValue : _Baycom;
   }
                  
   /**
    * Gets the Fund English Long Name field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Fund English Long Name or null.
    */
   public final String getElongName1()
   {
      return _ElongName1;
   }
	
   /**
    * Gets the Fund English Long Name field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund English Long Name or the specified default value.
    */
   public final String getElongName1( String defaultValue )
   {
      return _ElongName1 == null ? defaultValue : _ElongName1;
   }
                  
   /**
    * Gets the Percentage, Dollars or Units field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Percentage, Dollars or Units or null.
    */
   public final String getAmountType()
   {
      return _AmountType;
   }
	
   /**
    * Gets the Percentage, Dollars or Units field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Percentage, Dollars or Units or the specified default value.
    */
   public final String getAmountType( String defaultValue )
   {
      return _AmountType == null ? defaultValue : _AmountType;
   }
                  
   /**
    * Gets the Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Amount or null.
    */
   public final String getAmount()
   {
      return _Amount;
   }
	
   /**
    * Gets the Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Amount or the specified default value.
    */
   public final String getAmount( String defaultValue )
   {
      return _Amount == null ? defaultValue : _Amount;
   }
                  
   /**
    * Gets the Client Commission field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Client Commission or null.
    */
   public final String getFee()
   {
      return _Fee;
   }
	
   /**
    * Gets the Client Commission field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Client Commission or the specified default value.
    */
   public final String getFee( String defaultValue )
   {
      return _Fee == null ? defaultValue : _Fee;
   }
                  
   /**
    * Gets the Gross or Net field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Gross or Net or null.
    */
   public final Boolean getGrossOrNet()
   {
      return _GrossOrNet;
   }
	
   /**
    * Gets the Gross or Net field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Gross or Net or the specified default value.
    */
   public final boolean getGrossOrNet( boolean defaultValue )
   {
      return _GrossOrNet == null ? defaultValue : _GrossOrNet.booleanValue();
   }
                  
   /**
    * Gets the Payee Indicator field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Payee Indicator or null.
    */
   public final String getPayeeIndicator()
   {
      return _PayeeIndicator;
   }
	
   /**
    * Gets the Payee Indicator field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payee Indicator or the specified default value.
    */
   public final String getPayeeIndicator( String defaultValue )
   {
      return _PayeeIndicator == null ? defaultValue : _PayeeIndicator;
   }
                  
   /**
    * Gets the Bank Institution Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Bank Institution Code or null.
    */
   public final Integer getInstCode()
   {
      return _InstCode;
   }
	
   /**
    * Gets the Bank Institution Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Institution Code or the specified default value.
    */
   public final int getInstCode( int defaultValue )
   {
      return _InstCode == null ? defaultValue : _InstCode.intValue();
   }
                  
   /**
    * Gets the Bank Transit Number field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Bank Transit Number or null.
    */
   public final Integer getTransitNo()
   {
      return _TransitNo;
   }
	
   /**
    * Gets the Bank Transit Number field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Transit Number or the specified default value.
    */
   public final int getTransitNo( int defaultValue )
   {
      return _TransitNo == null ? defaultValue : _TransitNo.intValue();
   }
                  
   /**
    * Gets the Bank Account Number field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Bank Account Number or null.
    */
   public final String getBankAcctNum()
   {
      return _BankAcctNum;
   }
	
   /**
    * Gets the Bank Account Number field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Account Number or the specified default value.
    */
   public final String getBankAcctNum( String defaultValue )
   {
      return _BankAcctNum == null ? defaultValue : _BankAcctNum;
   }
                  
   /**
    * Gets the Fund Currency field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Fund Currency or null.
    */
   public final String getCurrency()
   {
      return _Currency;
   }
	
   /**
    * Gets the Fund Currency field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Currency or the specified default value.
    */
   public final String getCurrency( String defaultValue )
   {
      return _Currency == null ? defaultValue : _Currency;
   }
                  
   /**
    * Gets the Transfer Fund Baycom Number field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Transfer Fund Baycom Number or null.
    */
   public final String getBaycomTo()
   {
      return _BaycomTo;
   }
	
   /**
    * Gets the Transfer Fund Baycom Number field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transfer Fund Baycom Number or the specified default value.
    */
   public final String getBaycomTo( String defaultValue )
   {
      return _BaycomTo == null ? defaultValue : _BaycomTo;
   }
                  
   /**
    * Gets the English Long Name of Fund To field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the English Long Name of Fund To or null.
    */
   public final String getElongName2()
   {
      return _ElongName2;
   }
	
   /**
    * Gets the English Long Name of Fund To field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the English Long Name of Fund To or the specified default value.
    */
   public final String getElongName2( String defaultValue )
   {
      return _ElongName2 == null ? defaultValue : _ElongName2;
   }
                  
   /**
    * Gets the Bank Account Type field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Bank Account Type or null.
    */
   public final String getBankAcctType()
   {
      return _BankAcctType;
   }
	
   /**
    * Gets the Bank Account Type field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Account Type or the specified default value.
    */
   public final String getBankAcctType( String defaultValue )
   {
      return _BankAcctType == null ? defaultValue : _BankAcctType;
   }
                  
   /**
    * Gets the Bank Account Name field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Bank Account Name or null.
    */
   public final String getBankAcctName()
   {
      return _BankAcctName;
   }
	
   /**
    * Gets the Bank Account Name field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Account Name or the specified default value.
    */
   public final String getBankAcctName( String defaultValue )
   {
      return _BankAcctName == null ? defaultValue : _BankAcctName;
   }
                  
   /**
    * Gets the Address Name 1 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Address Name 1 or null.
    */
   public final String getName1()
   {
      return _Name1;
   }
	
   /**
    * Gets the Address Name 1 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Name 1 or the specified default value.
    */
   public final String getName1( String defaultValue )
   {
      return _Name1 == null ? defaultValue : _Name1;
   }
                  
   /**
    * Gets the Address Name 2 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Address Name 2 or null.
    */
   public final String getName2()
   {
      return _Name2;
   }
	
   /**
    * Gets the Address Name 2 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Name 2 or the specified default value.
    */
   public final String getName2( String defaultValue )
   {
      return _Name2 == null ? defaultValue : _Name2;
   }
                  
   /**
    * Gets the Address Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Address Code or null.
    */
   public final String getAddrCode()
   {
      return _AddrCode;
   }
	
   /**
    * Gets the Address Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Code or the specified default value.
    */
   public final String getAddrCode( String defaultValue )
   {
      return _AddrCode == null ? defaultValue : _AddrCode;
   }
                  
   /**
    * Gets the Address Line 1 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Address Line 1 or null.
    */
   public final String getAddrLine1()
   {
      return _AddrLine1;
   }
	
   /**
    * Gets the Address Line 1 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line 1 or the specified default value.
    */
   public final String getAddrLine1( String defaultValue )
   {
      return _AddrLine1 == null ? defaultValue : _AddrLine1;
   }
                  
   /**
    * Gets the Address Line 2 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Address Line 2 or null.
    */
   public final String getAddrLine2()
   {
      return _AddrLine2;
   }
	
   /**
    * Gets the Address Line 2 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line 2 or the specified default value.
    */
   public final String getAddrLine2( String defaultValue )
   {
      return _AddrLine2 == null ? defaultValue : _AddrLine2;
   }
                  
   /**
    * Gets the Address Line 3 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Address Line 3 or null.
    */
   public final String getAddrLine3()
   {
      return _AddrLine3;
   }
	
   /**
    * Gets the Address Line 3 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line 3 or the specified default value.
    */
   public final String getAddrLine3( String defaultValue )
   {
      return _AddrLine3 == null ? defaultValue : _AddrLine3;
   }
                  
   /**
    * Gets the Address Line 4 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Address Line 4 or null.
    */
   public final String getAddrLine4()
   {
      return _AddrLine4;
   }
	
   /**
    * Gets the Address Line 4 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line 4 or the specified default value.
    */
   public final String getAddrLine4( String defaultValue )
   {
      return _AddrLine4 == null ? defaultValue : _AddrLine4;
   }
                  
   /**
    * Gets the Address Line 5 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Address Line 5 or null.
    */
   public final String getAddrLine5()
   {
      return _AddrLine5;
   }
	
   /**
    * Gets the Address Line 5 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line 5 or the specified default value.
    */
   public final String getAddrLine5( String defaultValue )
   {
      return _AddrLine5 == null ? defaultValue : _AddrLine5;
   }
                  
   /**
    * Gets the City field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the City or null.
    */
   public final String getCity()
   {
      return _City;
   }
	
   /**
    * Gets the City field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the City or the specified default value.
    */
   public final String getCity( String defaultValue )
   {
      return _City == null ? defaultValue : _City;
   }
                  
   /**
    * Gets the Country Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Country Code or null.
    */
   public final String getCountryCode()
   {
      return _CountryCode;
   }
	
   /**
    * Gets the Country Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Country Code or the specified default value.
    */
   public final String getCountryCode( String defaultValue )
   {
      return _CountryCode == null ? defaultValue : _CountryCode;
   }
                  
   /**
    * Gets the Postal Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Postal Code or null.
    */
   public final String getPostalCode()
   {
      return _PostalCode;
   }
	
   /**
    * Gets the Postal Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Postal Code or the specified default value.
    */
   public final String getPostalCode( String defaultValue )
   {
      return _PostalCode == null ? defaultValue : _PostalCode;
   }
                  
   /**
    * Gets the Gross or Net - Purchase field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Gross or Net - Purchase or null.
    */
   public final Boolean getGrossOrNetPurch()
   {
      return _GrossOrNetPurch;
   }
	
   /**
    * Gets the Gross or Net - Purchase field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Gross or Net - Purchase or the specified default value.
    */
   public final boolean getGrossOrNetPurch( boolean defaultValue )
   {
      return _GrossOrNetPurch == null ? defaultValue : _GrossOrNetPurch.booleanValue();
   }
                  
   /**
    * Gets the Gross or Net - Redemption field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Gross or Net - Redemption or null.
    */
   public final Boolean getGrossOrNetRed()
   {
      return _GrossOrNetRed;
   }
	
   /**
    * Gets the Gross or Net - Redemption field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Gross or Net - Redemption or the specified default value.
    */
   public final boolean getGrossOrNetRed( boolean defaultValue )
   {
      return _GrossOrNetRed == null ? defaultValue : _GrossOrNetRed.booleanValue();
   }
                  
   /**
    * Gets the Commission Entity field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Commission Entity or null.
    */
   public final String getCommEntity()
   {
      return _CommEntity;
   }
	
   /**
    * Gets the Commission Entity field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commission Entity or the specified default value.
    */
   public final String getCommEntity( String defaultValue )
   {
      return _CommEntity == null ? defaultValue : _CommEntity;
   }
                  
   /**
    * Gets the Fee Type - Flat/ Percent field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Fee Type - Flat/ Percent or null.
    */
   public final Boolean getFlatPrcnt()
   {
      return _FlatPrcnt;
   }
	
   /**
    * Gets the Fee Type - Flat/ Percent field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee Type - Flat/ Percent or the specified default value.
    */
   public final boolean getFlatPrcnt( boolean defaultValue )
   {
      return _FlatPrcnt == null ? defaultValue : _FlatPrcnt.booleanValue();
   }
                  
   /**
    * Gets the Transfer To Account field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Transfer To Account or null.
    */
   public final String getAccountTo()
   {
      return _AccountTo;
   }
	
   /**
    * Gets the Transfer To Account field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transfer To Account or the specified default value.
    */
   public final String getAccountTo( String defaultValue )
   {
      return _AccountTo == null ? defaultValue : _AccountTo;
   }
                  
   /**
    * Gets the Country Description field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Country Description or null.
    */
   public final String getCountryDesc()
   {
      return _CountryDesc;
   }
	
   /**
    * Gets the Country Description field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Country Description or the specified default value.
    */
   public final String getCountryDesc( String defaultValue )
   {
      return _CountryDesc == null ? defaultValue : _CountryDesc;
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
      _IntermCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _ActivityStatus = responseBuffer.decodeString(responseBuffer.getNextField());
      _EffectiveDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _SystematicFreq = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _StopDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _RestartDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _NextProcDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _Baycom = responseBuffer.decodeString(responseBuffer.getNextField());
      _ElongName1 = responseBuffer.decodeString(responseBuffer.getNextField());
      _AmountType = responseBuffer.decodeString(responseBuffer.getNextField());
      _Amount = responseBuffer.decodeString(responseBuffer.getNextField());
      _Fee = responseBuffer.decodeString(responseBuffer.getNextField());
      _GrossOrNet = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _PayeeIndicator = responseBuffer.decodeString(responseBuffer.getNextField());
      _InstCode = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _TransitNo = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _BankAcctNum = responseBuffer.decodeString(responseBuffer.getNextField());
      _Currency = responseBuffer.decodeString(responseBuffer.getNextField());
      _BaycomTo = responseBuffer.decodeString(responseBuffer.getNextField());
      _ElongName2 = responseBuffer.decodeString(responseBuffer.getNextField());
      _BankAcctType = responseBuffer.decodeString(responseBuffer.getNextField());
      _BankAcctName = responseBuffer.decodeString(responseBuffer.getNextField());
      _Name1 = responseBuffer.decodeString(responseBuffer.getNextField());
      _Name2 = responseBuffer.decodeString(responseBuffer.getNextField());
      _AddrCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _AddrLine1 = responseBuffer.decodeString(responseBuffer.getNextField());
      _AddrLine2 = responseBuffer.decodeString(responseBuffer.getNextField());
      _AddrLine3 = responseBuffer.decodeString(responseBuffer.getNextField());
      _AddrLine4 = responseBuffer.decodeString(responseBuffer.getNextField());
      _AddrLine5 = responseBuffer.decodeString(responseBuffer.getNextField());
      _City = responseBuffer.decodeString(responseBuffer.getNextField());
      _CountryCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _PostalCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _GrossOrNetPurch = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _GrossOrNetRed = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _CommEntity = responseBuffer.decodeString(responseBuffer.getNextField());
      _FlatPrcnt = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _AccountTo = responseBuffer.decodeString(responseBuffer.getNextField());
      _CountryDesc = responseBuffer.decodeString(responseBuffer.getNextField());
                  

   }

}
      
