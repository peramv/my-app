
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Account Search view.
 * For additional view information see <A HREF="../../../../viewspecs/AcctSrch.doc">AcctSrch.doc</A>.
 * 
 * @author RTS Generated
 */
public class AcctSrchView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Account Number member array.
    */
   private String[] _AccountNum = null;
   
   /**
    * Tax Type member array.
    */
   private String[] _TaxType = null;
   
   /**
    * Account Type member array.
    */
   private String[] _AcctType = null;
   
   /**
    * Social Code member array.
    */
   private String[] _SocialCode = null;
   
   /**
    * Account Designation member array.
    */
   private String[] _AcctDesignation = null;
   
   /**
    * Alternate Account member array.
    */
   private String[] _AltAccount = null;
   
   /**
    * Account Currency member array.
    */
   private String[] _AcctCurrency = null;
   
   /**
    * Broker Code member array.
    */
   private String[] _BrokerCode = null;
   
   /**
    * Branch Code member array.
    */
   private String[] _BranchCode = null;
   
   /**
    * Sales Rep Code member array.
    */
   private String[] _SlsRepCode = null;
   
   /**
    * Intermediary Account member array.
    */
   private String[] _InterAccount = null;
   
   /**
    * Date of Registration member array.
    */
   private Date[] _DateOfReg = null;
   
   /**
    * RRSP Fee member array.
    */
   private String[] _RRSPFee = null;
   
   /**
    * AMSCode member array.
    */
   private String[] _AMSCode = null;
   
   /**
    * Pension Jurisdiction member array.
    */
   private String[] _PensionJuris = null;
   
   /**
    * Stop Purchase member array.
    */
   private Boolean[] _StopPurchase = null;
   
   /**
    * Stop Transfer In member array.
    */
   private Boolean[] _StopXferIn = null;
   
   /**
    * Stop Transfer Out member array.
    */
   private Boolean[] _StopXferOut = null;
   
   /**
    * Stop Redemption member array.
    */
   private Boolean[] _StopRed = null;
   
   /**
    * Fee Waived member array.
    */
   private Boolean[] _FeeWaived = null;
   
   /**
    * Unseizable member array.
    */
   private Boolean[] _Unseizable = null;
   
   /**
    * Market Mailing member array.
    */
   private Boolean[] _MarketMail = null;
   
   /**
    * Sup Conf member array.
    */
   private Boolean[] _SupConf = null;
   
   /**
    * Sup Emp Conf member array.
    */
   private Boolean[] _SupEmpConf = null;
   
   /**
    * In Trust For member array.
    */
   private Boolean[] _InTrustFor = null;
   
   /**
    * Escrow member array.
    */
   private Boolean[] _Escrow = null;
   
   /**
    * Process Date member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * Mod User member array.
    */
   private String[] _ModUser = null;
   
   /**
    * UserName member array.
    */
   private String[] _UserName = null;
   
   /**
    * Account Group member array.
    */
   private String[] _AcctGroup = null;
   
   /**
    * Shareholder Number member array.
    */
   private String[] _ShrNum = null;
   
   /**
    * Acct Master Version member array.
    */
   private Integer[] _AcctMstrVer = null;
   
   /**
    * Acct Mstr Recid member array.
    */
   private Integer[] _AcctMstrRid = null;
   
   /**
    * Employee member array.
    */
   private String[] _Employee = null;
   
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = null;
   
   /**
    * Product Code member array.
    */
   private String[] _ProdCode = null;
   

   /**
    * Constructs the AcctSrchView object.
    * 
    */
   public AcctSrchView()
   {
      super ( new AcctSrchRequest() );
   }

   /**
    * Constructs the AcctSrchView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AcctSrchView( String hostEncoding )
   {
      super ( new AcctSrchRequest( hostEncoding ) );
   }

   /**
    * Gets the AcctSrchRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AcctSrchRequest object.
    */
   public final AcctSrchRequest getRequest()
   {
      return (AcctSrchRequest)getIFastRequest();
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
    * Gets the Account Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Number or null.
    */
   public final String getAccountNum( int index )
   {
      return _AccountNum[index];
   }
    
   /**
    * Gets the Account Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Number or the specified default value.
    */
   public final String getAccountNum( int index, String defaultValue )
   {
      return _AccountNum[index] == null ? defaultValue : _AccountNum[index];
   }
    
   /**
    * Gets the array of Account Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Number values.
    */
   public final String[] getAccountNumArray()
   {
      return _AccountNum;
   }
    
   /**
    * Gets the Tax Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax Type or null.
    */
   public final String getTaxType( int index )
   {
      return _TaxType[index];
   }
    
   /**
    * Gets the Tax Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Type or the specified default value.
    */
   public final String getTaxType( int index, String defaultValue )
   {
      return _TaxType[index] == null ? defaultValue : _TaxType[index];
   }
    
   /**
    * Gets the array of Tax Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax Type values.
    */
   public final String[] getTaxTypeArray()
   {
      return _TaxType;
   }
    
   /**
    * Gets the Account Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Type or null.
    */
   public final String getAcctType( int index )
   {
      return _AcctType[index];
   }
    
   /**
    * Gets the Account Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Type or the specified default value.
    */
   public final String getAcctType( int index, String defaultValue )
   {
      return _AcctType[index] == null ? defaultValue : _AcctType[index];
   }
    
   /**
    * Gets the array of Account Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Type values.
    */
   public final String[] getAcctTypeArray()
   {
      return _AcctType;
   }
    
   /**
    * Gets the Social Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Social Code or null.
    */
   public final String getSocialCode( int index )
   {
      return _SocialCode[index];
   }
    
   /**
    * Gets the Social Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Social Code or the specified default value.
    */
   public final String getSocialCode( int index, String defaultValue )
   {
      return _SocialCode[index] == null ? defaultValue : _SocialCode[index];
   }
    
   /**
    * Gets the array of Social Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Social Code values.
    */
   public final String[] getSocialCodeArray()
   {
      return _SocialCode;
   }
    
   /**
    * Gets the Account Designation field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Designation or null.
    */
   public final String getAcctDesignation( int index )
   {
      return _AcctDesignation[index];
   }
    
   /**
    * Gets the Account Designation field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Designation or the specified default value.
    */
   public final String getAcctDesignation( int index, String defaultValue )
   {
      return _AcctDesignation[index] == null ? defaultValue : _AcctDesignation[index];
   }
    
   /**
    * Gets the array of Account Designation fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Designation values.
    */
   public final String[] getAcctDesignationArray()
   {
      return _AcctDesignation;
   }
    
   /**
    * Gets the Alternate Account field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Alternate Account or null.
    */
   public final String getAltAccount( int index )
   {
      return _AltAccount[index];
   }
    
   /**
    * Gets the Alternate Account field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Alternate Account or the specified default value.
    */
   public final String getAltAccount( int index, String defaultValue )
   {
      return _AltAccount[index] == null ? defaultValue : _AltAccount[index];
   }
    
   /**
    * Gets the array of Alternate Account fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Alternate Account values.
    */
   public final String[] getAltAccountArray()
   {
      return _AltAccount;
   }
    
   /**
    * Gets the Account Currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Currency or null.
    */
   public final String getAcctCurrency( int index )
   {
      return _AcctCurrency[index];
   }
    
   /**
    * Gets the Account Currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Currency or the specified default value.
    */
   public final String getAcctCurrency( int index, String defaultValue )
   {
      return _AcctCurrency[index] == null ? defaultValue : _AcctCurrency[index];
   }
    
   /**
    * Gets the array of Account Currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Currency values.
    */
   public final String[] getAcctCurrencyArray()
   {
      return _AcctCurrency;
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
    * Gets the Sales Rep Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Sales Rep Code or null.
    */
   public final String getSlsRepCode( int index )
   {
      return _SlsRepCode[index];
   }
    
   /**
    * Gets the Sales Rep Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Sales Rep Code or the specified default value.
    */
   public final String getSlsRepCode( int index, String defaultValue )
   {
      return _SlsRepCode[index] == null ? defaultValue : _SlsRepCode[index];
   }
    
   /**
    * Gets the array of Sales Rep Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Sales Rep Code values.
    */
   public final String[] getSlsRepCodeArray()
   {
      return _SlsRepCode;
   }
    
   /**
    * Gets the Intermediary Account field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Intermediary Account or null.
    */
   public final String getInterAccount( int index )
   {
      return _InterAccount[index];
   }
    
   /**
    * Gets the Intermediary Account field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Intermediary Account or the specified default value.
    */
   public final String getInterAccount( int index, String defaultValue )
   {
      return _InterAccount[index] == null ? defaultValue : _InterAccount[index];
   }
    
   /**
    * Gets the array of Intermediary Account fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Intermediary Account values.
    */
   public final String[] getInterAccountArray()
   {
      return _InterAccount;
   }
    
   /**
    * Gets the Date of Registration field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Date of Registration or null.
    */
   public final Date getDateOfReg( int index )
   {
      return _DateOfReg[index];
   }
    
   /**
    * Gets the Date of Registration field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date of Registration or the specified default value.
    */
   public final Date getDateOfReg( int index, Date defaultValue )
   {
      return _DateOfReg[index] == null ? defaultValue : _DateOfReg[index];
   }
    
   /**
    * Gets the array of Date of Registration fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Date of Registration values.
    */
   public final Date[] getDateOfRegArray()
   {
      return _DateOfReg;
   }
    
   /**
    * Gets the RRSP Fee field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RRSP Fee or null.
    */
   public final String getRRSPFee( int index )
   {
      return _RRSPFee[index];
   }
    
   /**
    * Gets the RRSP Fee field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RRSP Fee or the specified default value.
    */
   public final String getRRSPFee( int index, String defaultValue )
   {
      return _RRSPFee[index] == null ? defaultValue : _RRSPFee[index];
   }
    
   /**
    * Gets the array of RRSP Fee fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RRSP Fee values.
    */
   public final String[] getRRSPFeeArray()
   {
      return _RRSPFee;
   }
    
   /**
    * Gets the AMSCode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AMSCode or null.
    */
   public final String getAMSCode( int index )
   {
      return _AMSCode[index];
   }
    
   /**
    * Gets the AMSCode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AMSCode or the specified default value.
    */
   public final String getAMSCode( int index, String defaultValue )
   {
      return _AMSCode[index] == null ? defaultValue : _AMSCode[index];
   }
    
   /**
    * Gets the array of AMSCode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AMSCode values.
    */
   public final String[] getAMSCodeArray()
   {
      return _AMSCode;
   }
    
   /**
    * Gets the Pension Jurisdiction field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Pension Jurisdiction or null.
    */
   public final String getPensionJuris( int index )
   {
      return _PensionJuris[index];
   }
    
   /**
    * Gets the Pension Jurisdiction field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pension Jurisdiction or the specified default value.
    */
   public final String getPensionJuris( int index, String defaultValue )
   {
      return _PensionJuris[index] == null ? defaultValue : _PensionJuris[index];
   }
    
   /**
    * Gets the array of Pension Jurisdiction fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Pension Jurisdiction values.
    */
   public final String[] getPensionJurisArray()
   {
      return _PensionJuris;
   }
    
   /**
    * Gets the Stop Purchase field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stop Purchase or null.
    */
   public final Boolean getStopPurchase( int index )
   {
      return _StopPurchase[index];
   }
    
   /**
    * Gets the Stop Purchase field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Purchase or the specified default value.
    */
   public final boolean getStopPurchase( int index, boolean defaultValue )
   {
      return _StopPurchase[index] == null ? defaultValue : _StopPurchase[index].booleanValue();
   }
    
   /**
    * Gets the array of Stop Purchase fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stop Purchase values.
    */
   public final Boolean[] getStopPurchaseArray()
   {
      return _StopPurchase;
   }
    
   /**
    * Gets the Stop Transfer In field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stop Transfer In or null.
    */
   public final Boolean getStopXferIn( int index )
   {
      return _StopXferIn[index];
   }
    
   /**
    * Gets the Stop Transfer In field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Transfer In or the specified default value.
    */
   public final boolean getStopXferIn( int index, boolean defaultValue )
   {
      return _StopXferIn[index] == null ? defaultValue : _StopXferIn[index].booleanValue();
   }
    
   /**
    * Gets the array of Stop Transfer In fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stop Transfer In values.
    */
   public final Boolean[] getStopXferInArray()
   {
      return _StopXferIn;
   }
    
   /**
    * Gets the Stop Transfer Out field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stop Transfer Out or null.
    */
   public final Boolean getStopXferOut( int index )
   {
      return _StopXferOut[index];
   }
    
   /**
    * Gets the Stop Transfer Out field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Transfer Out or the specified default value.
    */
   public final boolean getStopXferOut( int index, boolean defaultValue )
   {
      return _StopXferOut[index] == null ? defaultValue : _StopXferOut[index].booleanValue();
   }
    
   /**
    * Gets the array of Stop Transfer Out fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stop Transfer Out values.
    */
   public final Boolean[] getStopXferOutArray()
   {
      return _StopXferOut;
   }
    
   /**
    * Gets the Stop Redemption field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stop Redemption or null.
    */
   public final Boolean getStopRed( int index )
   {
      return _StopRed[index];
   }
    
   /**
    * Gets the Stop Redemption field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Redemption or the specified default value.
    */
   public final boolean getStopRed( int index, boolean defaultValue )
   {
      return _StopRed[index] == null ? defaultValue : _StopRed[index].booleanValue();
   }
    
   /**
    * Gets the array of Stop Redemption fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stop Redemption values.
    */
   public final Boolean[] getStopRedArray()
   {
      return _StopRed;
   }
    
   /**
    * Gets the Fee Waived field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fee Waived or null.
    */
   public final Boolean getFeeWaived( int index )
   {
      return _FeeWaived[index];
   }
    
   /**
    * Gets the Fee Waived field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee Waived or the specified default value.
    */
   public final boolean getFeeWaived( int index, boolean defaultValue )
   {
      return _FeeWaived[index] == null ? defaultValue : _FeeWaived[index].booleanValue();
   }
    
   /**
    * Gets the array of Fee Waived fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee Waived values.
    */
   public final Boolean[] getFeeWaivedArray()
   {
      return _FeeWaived;
   }
    
   /**
    * Gets the Unseizable field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Unseizable or null.
    */
   public final Boolean getUnseizable( int index )
   {
      return _Unseizable[index];
   }
    
   /**
    * Gets the Unseizable field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Unseizable or the specified default value.
    */
   public final boolean getUnseizable( int index, boolean defaultValue )
   {
      return _Unseizable[index] == null ? defaultValue : _Unseizable[index].booleanValue();
   }
    
   /**
    * Gets the array of Unseizable fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Unseizable values.
    */
   public final Boolean[] getUnseizableArray()
   {
      return _Unseizable;
   }
    
   /**
    * Gets the Market Mailing field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Market Mailing or null.
    */
   public final Boolean getMarketMail( int index )
   {
      return _MarketMail[index];
   }
    
   /**
    * Gets the Market Mailing field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Market Mailing or the specified default value.
    */
   public final boolean getMarketMail( int index, boolean defaultValue )
   {
      return _MarketMail[index] == null ? defaultValue : _MarketMail[index].booleanValue();
   }
    
   /**
    * Gets the array of Market Mailing fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Market Mailing values.
    */
   public final Boolean[] getMarketMailArray()
   {
      return _MarketMail;
   }
    
   /**
    * Gets the Sup Conf field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Sup Conf or null.
    */
   public final Boolean getSupConf( int index )
   {
      return _SupConf[index];
   }
    
   /**
    * Gets the Sup Conf field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Sup Conf or the specified default value.
    */
   public final boolean getSupConf( int index, boolean defaultValue )
   {
      return _SupConf[index] == null ? defaultValue : _SupConf[index].booleanValue();
   }
    
   /**
    * Gets the array of Sup Conf fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Sup Conf values.
    */
   public final Boolean[] getSupConfArray()
   {
      return _SupConf;
   }
    
   /**
    * Gets the Sup Emp Conf field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Sup Emp Conf or null.
    */
   public final Boolean getSupEmpConf( int index )
   {
      return _SupEmpConf[index];
   }
    
   /**
    * Gets the Sup Emp Conf field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Sup Emp Conf or the specified default value.
    */
   public final boolean getSupEmpConf( int index, boolean defaultValue )
   {
      return _SupEmpConf[index] == null ? defaultValue : _SupEmpConf[index].booleanValue();
   }
    
   /**
    * Gets the array of Sup Emp Conf fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Sup Emp Conf values.
    */
   public final Boolean[] getSupEmpConfArray()
   {
      return _SupEmpConf;
   }
    
   /**
    * Gets the In Trust For field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the In Trust For or null.
    */
   public final Boolean getInTrustFor( int index )
   {
      return _InTrustFor[index];
   }
    
   /**
    * Gets the In Trust For field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the In Trust For or the specified default value.
    */
   public final boolean getInTrustFor( int index, boolean defaultValue )
   {
      return _InTrustFor[index] == null ? defaultValue : _InTrustFor[index].booleanValue();
   }
    
   /**
    * Gets the array of In Trust For fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of In Trust For values.
    */
   public final Boolean[] getInTrustForArray()
   {
      return _InTrustFor;
   }
    
   /**
    * Gets the Escrow field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Escrow or null.
    */
   public final Boolean getEscrow( int index )
   {
      return _Escrow[index];
   }
    
   /**
    * Gets the Escrow field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Escrow or the specified default value.
    */
   public final boolean getEscrow( int index, boolean defaultValue )
   {
      return _Escrow[index] == null ? defaultValue : _Escrow[index].booleanValue();
   }
    
   /**
    * Gets the array of Escrow fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Escrow values.
    */
   public final Boolean[] getEscrowArray()
   {
      return _Escrow;
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
    * Gets the Mod User field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Mod User or null.
    */
   public final String getModUser( int index )
   {
      return _ModUser[index];
   }
    
   /**
    * Gets the Mod User field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Mod User or the specified default value.
    */
   public final String getModUser( int index, String defaultValue )
   {
      return _ModUser[index] == null ? defaultValue : _ModUser[index];
   }
    
   /**
    * Gets the array of Mod User fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Mod User values.
    */
   public final String[] getModUserArray()
   {
      return _ModUser;
   }
    
   /**
    * Gets the UserName field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the UserName or null.
    */
   public final String getUserName( int index )
   {
      return _UserName[index];
   }
    
   /**
    * Gets the UserName field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the UserName or the specified default value.
    */
   public final String getUserName( int index, String defaultValue )
   {
      return _UserName[index] == null ? defaultValue : _UserName[index];
   }
    
   /**
    * Gets the array of UserName fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of UserName values.
    */
   public final String[] getUserNameArray()
   {
      return _UserName;
   }
    
   /**
    * Gets the Account Group field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Group or null.
    */
   public final String getAcctGroup( int index )
   {
      return _AcctGroup[index];
   }
    
   /**
    * Gets the Account Group field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Group or the specified default value.
    */
   public final String getAcctGroup( int index, String defaultValue )
   {
      return _AcctGroup[index] == null ? defaultValue : _AcctGroup[index];
   }
    
   /**
    * Gets the array of Account Group fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Group values.
    */
   public final String[] getAcctGroupArray()
   {
      return _AcctGroup;
   }
    
   /**
    * Gets the Shareholder Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Shareholder Number or null.
    */
   public final String getShrNum( int index )
   {
      return _ShrNum[index];
   }
    
   /**
    * Gets the Shareholder Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Shareholder Number or the specified default value.
    */
   public final String getShrNum( int index, String defaultValue )
   {
      return _ShrNum[index] == null ? defaultValue : _ShrNum[index];
   }
    
   /**
    * Gets the array of Shareholder Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Shareholder Number values.
    */
   public final String[] getShrNumArray()
   {
      return _ShrNum;
   }
    
   /**
    * Gets the Acct Master Version field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Acct Master Version or null.
    */
   public final Integer getAcctMstrVer( int index )
   {
      return _AcctMstrVer[index];
   }
    
   /**
    * Gets the Acct Master Version field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Acct Master Version or the specified default value.
    */
   public final int getAcctMstrVer( int index, int defaultValue )
   {
      return _AcctMstrVer[index] == null ? defaultValue : _AcctMstrVer[index].intValue();
   }
    
   /**
    * Gets the array of Acct Master Version fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Acct Master Version values.
    */
   public final Integer[] getAcctMstrVerArray()
   {
      return _AcctMstrVer;
   }
    
   /**
    * Gets the Acct Mstr Recid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Acct Mstr Recid or null.
    */
   public final Integer getAcctMstrRid( int index )
   {
      return _AcctMstrRid[index];
   }
    
   /**
    * Gets the Acct Mstr Recid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Acct Mstr Recid or the specified default value.
    */
   public final int getAcctMstrRid( int index, int defaultValue )
   {
      return _AcctMstrRid[index] == null ? defaultValue : _AcctMstrRid[index].intValue();
   }
    
   /**
    * Gets the array of Acct Mstr Recid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Acct Mstr Recid values.
    */
   public final Integer[] getAcctMstrRidArray()
   {
      return _AcctMstrRid;
   }
    
   /**
    * Gets the Employee field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Employee or null.
    */
   public final String getEmployee( int index )
   {
      return _Employee[index];
   }
    
   /**
    * Gets the Employee field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Employee or the specified default value.
    */
   public final String getEmployee( int index, String defaultValue )
   {
      return _Employee[index] == null ? defaultValue : _Employee[index];
   }
    
   /**
    * Gets the array of Employee fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Employee values.
    */
   public final String[] getEmployeeArray()
   {
      return _Employee;
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
    * Gets the Product Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Product Code or null.
    */
   public final String getProdCode( int index )
   {
      return _ProdCode[index];
   }
    
   /**
    * Gets the Product Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Product Code or the specified default value.
    */
   public final String getProdCode( int index, String defaultValue )
   {
      return _ProdCode[index] == null ? defaultValue : _ProdCode[index];
   }
    
   /**
    * Gets the array of Product Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Product Code values.
    */
   public final String[] getProdCodeArray()
   {
      return _ProdCode;
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
      
      _AccountNum = resizeArray( _AccountNum, _RepeatCount );
      _TaxType = resizeArray( _TaxType, _RepeatCount );
      _AcctType = resizeArray( _AcctType, _RepeatCount );
      _SocialCode = resizeArray( _SocialCode, _RepeatCount );
      _AcctDesignation = resizeArray( _AcctDesignation, _RepeatCount );
      _AltAccount = resizeArray( _AltAccount, _RepeatCount );
      _AcctCurrency = resizeArray( _AcctCurrency, _RepeatCount );
      _BrokerCode = resizeArray( _BrokerCode, _RepeatCount );
      _BranchCode = resizeArray( _BranchCode, _RepeatCount );
      _SlsRepCode = resizeArray( _SlsRepCode, _RepeatCount );
      _InterAccount = resizeArray( _InterAccount, _RepeatCount );
      _DateOfReg = resizeArray( _DateOfReg, _RepeatCount );
      _RRSPFee = resizeArray( _RRSPFee, _RepeatCount );
      _AMSCode = resizeArray( _AMSCode, _RepeatCount );
      _PensionJuris = resizeArray( _PensionJuris, _RepeatCount );
      _StopPurchase = resizeArray( _StopPurchase, _RepeatCount );
      _StopXferIn = resizeArray( _StopXferIn, _RepeatCount );
      _StopXferOut = resizeArray( _StopXferOut, _RepeatCount );
      _StopRed = resizeArray( _StopRed, _RepeatCount );
      _FeeWaived = resizeArray( _FeeWaived, _RepeatCount );
      _Unseizable = resizeArray( _Unseizable, _RepeatCount );
      _MarketMail = resizeArray( _MarketMail, _RepeatCount );
      _SupConf = resizeArray( _SupConf, _RepeatCount );
      _SupEmpConf = resizeArray( _SupEmpConf, _RepeatCount );
      _InTrustFor = resizeArray( _InTrustFor, _RepeatCount );
      _Escrow = resizeArray( _Escrow, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _UserName = resizeArray( _UserName, _RepeatCount );
      _AcctGroup = resizeArray( _AcctGroup, _RepeatCount );
      _ShrNum = resizeArray( _ShrNum, _RepeatCount );
      _AcctMstrVer = resizeArray( _AcctMstrVer, _RepeatCount );
      _AcctMstrRid = resizeArray( _AcctMstrRid, _RepeatCount );
      _Employee = resizeArray( _Employee, _RepeatCount );
      _EffectiveDate = resizeArray( _EffectiveDate, _RepeatCount );
      _ProdCode = resizeArray( _ProdCode, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _AccountNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TaxType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SocialCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctDesignation[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AltAccount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctCurrency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BrokerCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BranchCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SlsRepCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _InterAccount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DateOfReg[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _RRSPFee[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AMSCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PensionJuris[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _StopPurchase[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _StopXferIn[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _StopXferOut[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _StopRed[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FeeWaived[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _Unseizable[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _MarketMail[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _SupConf[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _SupEmpConf[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _InTrustFor[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _Escrow[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UserName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctGroup[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ShrNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctMstrVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _AcctMstrRid[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _Employee[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ProdCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
