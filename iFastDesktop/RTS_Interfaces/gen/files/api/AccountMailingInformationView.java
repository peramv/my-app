
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Account  Mailing Info Inq view.
 * For additional view information see <A HREF="../../../../viewspecs/AccountMailingInformation.doc">AccountMailingInformation.doc</A>.
 * 
 * @author RTS Generated
 */
public class AccountMailingInformationView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Register Address member array.
    */
   private String[] _RegAddr = null;
   
   /**
    * Dividend Confirm member array.
    */
   private String[] _DivConfAddr = null;
   
   /**
    * Dividend Cheque member array.
    */
   private String[] _DivChqAddr = null;
   
   /**
    * Transaction Confirm member array.
    */
   private String[] _TxnConfAddr = null;
   
   /**
    * Duplicate Confirm member array.
    */
   private String[] _DupConfAddr = null;
   
   /**
    * Statement member array.
    */
   private String[] _StmtAddr = null;
   
   /**
    * Duplicate Statement member array.
    */
   private String[] _DupStmtAddr = null;
   
   /**
    * Certifiates member array.
    */
   private String[] _CertAddr = null;
   
   /**
    * Tax Receipts member array.
    */
   private String[] _TaxAddr = null;
   
   /**
    * Letters member array.
    */
   private String[] _LetAddr = null;
   
   /**
    * Beneficial Owner member array.
    */
   private String[] _BenAddr = null;
   
   /**
    * Copies for Duplicate Confirm member array.
    */
   private Integer[] _DupConfCopies = null;
   
   /**
    * Copies for Duplicate Statement member array.
    */
   private Integer[] _DupStmtCopies = null;
   
   /**
    * Hold mail for registered address member array.
    */
   private Boolean[] _RegOnHold = null;
   
   /**
    * Hold mail for dividend confirm member array.
    */
   private Boolean[] _DivConfOnHold = null;
   
   /**
    * Hold mail for dividend cheques member array.
    */
   private Boolean[] _DivChqOnHold = null;
   
   /**
    * Hold mail for confirmation member array.
    */
   private Boolean[] _TxnConfOnHold = null;
   
   /**
    * Hold mail for duplication confirm member array.
    */
   private Boolean[] _DupConfOnHold = null;
   
   /**
    * Hold mail for statement member array.
    */
   private Boolean[] _StmtOnHold = null;
   
   /**
    * Hold mail for duplication statement member array.
    */
   private Boolean[] _DupStmtOnHold = null;
   
   /**
    * Hold mail for certificates member array.
    */
   private Boolean[] _CertOnHold = null;
   
   /**
    * Hold mail for tax receipts member array.
    */
   private Boolean[] _TaxOnHold = null;
   
   /**
    * Hold mail for letters member array.
    */
   private Boolean[] _LetOnHold = null;
   
   /**
    * Hold mail for beneficial owner member array.
    */
   private Boolean[] _BenOnHold = null;
   
   /**
    * Servicing Agent code for Confirms member array.
    */
   private String[] _SATxnConfCode = null;
   
   /**
    * Servicing Agent Desc.  for Confirms member array.
    */
   private String[] _SATxnConfDesc = null;
   
   /**
    * Servicing Agent code for Div. Confirms member array.
    */
   private String[] _SADivConfCode = null;
   
   /**
    * Servicing Agent Desc.  for Div. Confirms member array.
    */
   private String[] _SADivConfDesc = null;
   
   /**
    * Servicing Agent Code for Letters member array.
    */
   private String[] _SALettersCode = null;
   
   /**
    * Servicing Agent Desc. for Letters member array.
    */
   private String[] _SALettersDesc = null;
   
   /**
    * Acct-Mstr Version Number member array.
    */
   private Integer[] _AcctMstrVer = null;
   
   /**
    * Acct-Mstr Record Id member array.
    */
   private Integer[] _AcctMstrRid = null;
   
   /**
    * Non Financial Confirmation member array.
    */
   private String[] _NFCAddr = null;
   
   /**
    * Non Financial Confirm on Hold member array.
    */
   private Boolean[] _NFConHold = null;
   
   /**
    * Account Number member array.
    */
   private String[] _AccountNum = null;
   
   /**
    * Contract Address Code member array.
    */
   private String[] _ContrAddr = null;
   
   /**
    * Contract Address Use on Hold member array.
    */
   private Boolean[] _ContrHold = null;
   
   /**
    * Annual Reports Address Code member array.
    */
   private String[] _AnnlRptsAddr = null;
   
   /**
    * Annual Reports Address Use on Hold member array.
    */
   private Boolean[] _AnnlRptsHold = null;
   
   /**
    * Prospectus Address Code member array.
    */
   private String[] _ProspAddr = null;
   
   /**
    * Prospectus Address Use on Hold member array.
    */
   private Boolean[] _ProspHold = null;
   
   /**
    * Tax Suppress member array.
    */
   private String[] _TaxSuppress = null;
   
   /**
    * Tax Waive member array.
    */
   private String[] _TaxWaive = null;
   
   /**
    * Tax Mail member array.
    */
   private String[] _TaxMail = null;
   
   /**
    * Tax Fax member array.
    */
   private String[] _TaxFax = null;
   
   /**
    * Tax CD member array.
    */
   private String[] _TaxCD = null;
   
   /**
    * Tax Email member array.
    */
   private String[] _TaxEmail = null;
   
   /**
    * Letter Suppress member array.
    */
   private String[] _LetSuppress = null;
   
   /**
    * Letter Waive member array.
    */
   private String[] _LetWaive = null;
   
   /**
    * Letter Mail member array.
    */
   private String[] _LetMail = null;
   
   /**
    * Letter Fax member array.
    */
   private String[] _LetFax = null;
   
   /**
    * Letter Cd member array.
    */
   private String[] _LetCD = null;
   
   /**
    * Letter Email member array.
    */
   private String[] _LetEmail = null;
   
   /**
    * Cert Suppress member array.
    */
   private String[] _CertSuppress = null;
   
   /**
    * Cert Waive member array.
    */
   private String[] _CertWaive = null;
   
   /**
    * Cert Mail member array.
    */
   private String[] _CertMail = null;
   
   /**
    * Cert Fax member array.
    */
   private String[] _CertFax = null;
   
   /**
    * Cert CD member array.
    */
   private String[] _CertCD = null;
   
   /**
    * Cert Email member array.
    */
   private String[] _CertEmail = null;
   
   /**
    * Div Confirm Suopress member array.
    */
   private String[] _DivConfSuppress = null;
   
   /**
    * Div Confirm Waive member array.
    */
   private String[] _DivConfWaive = null;
   
   /**
    * Div Confirm Mail member array.
    */
   private String[] _DivConfMail = null;
   
   /**
    * Div Confirm Fax member array.
    */
   private String[] _DivConfFax = null;
   
   /**
    * Div Confirm CD member array.
    */
   private String[] _DivConfCD = null;
   
   /**
    * Div Confirm Email member array.
    */
   private String[] _DivConfEmail = null;
   
   /**
    * Div Cheque Suppress member array.
    */
   private String[] _DivChqSuppress = null;
   
   /**
    * Div Cheque Waive member array.
    */
   private String[] _DivChqWaive = null;
   
   /**
    * Div Cheque Mail member array.
    */
   private String[] _DivChqMail = null;
   
   /**
    * Div Cheque Fax member array.
    */
   private String[] _DivChqFax = null;
   
   /**
    * Div Cheque CD member array.
    */
   private String[] _DivChqCD = null;
   
   /**
    * Div Cheque Email member array.
    */
   private String[] _DivChqEmail = null;
   
   /**
    * Contr Suppress member array.
    */
   private String[] _ContrSuppress = null;
   
   /**
    * Contr Waive member array.
    */
   private String[] _ContrWaive = null;
   
   /**
    * Contr Mail member array.
    */
   private String[] _ContrMail = null;
   
   /**
    * Contr Fax member array.
    */
   private String[] _ContrFax = null;
   
   /**
    * Contr CD member array.
    */
   private String[] _ContrCD = null;
   
   /**
    * Contr Email member array.
    */
   private String[] _ContrEmail = null;
   
   /**
    * Reg Suppress member array.
    */
   private String[] _RegSuppress = null;
   
   /**
    * Reg Waive member array.
    */
   private String[] _RegWaive = null;
   
   /**
    * Reg Mail member array.
    */
   private String[] _RegMail = null;
   
   /**
    * Reg Fax member array.
    */
   private String[] _RegFax = null;
   
   /**
    * Reg CD member array.
    */
   private String[] _RegCD = null;
   
   /**
    * Reg Email member array.
    */
   private String[] _RegEmail = null;
   
   /**
    * Annual Reports Suppress member array.
    */
   private String[] _AnnlRptsSuppress = null;
   
   /**
    * Annual Reports Waive member array.
    */
   private String[] _AnnlRptsWaive = null;
   
   /**
    * Annual Reports Mail member array.
    */
   private String[] _AnnlRptsMail = null;
   
   /**
    * Annual Reports Fax member array.
    */
   private String[] _AnnlRptsFax = null;
   
   /**
    * Annual Reports CD member array.
    */
   private String[] _AnnlRptsCd = null;
   
   /**
    * Annual Reports Email member array.
    */
   private String[] _AnnlRptsEmail = null;
   
   /**
    * Prosp Suppress member array.
    */
   private String[] _ProspSuppress = null;
   
   /**
    * Prosp Waive member array.
    */
   private String[] _ProspWaive = null;
   
   /**
    * Prosp Mail member array.
    */
   private String[] _ProspMail = null;
   
   /**
    * Prosp Fax member array.
    */
   private String[] _ProspFax = null;
   
   /**
    * Prosp CD member array.
    */
   private String[] _ProspCD = null;
   
   /**
    * Prosp Email member array.
    */
   private String[] _ProspEmail = null;
   
   /**
    * Ben Suppress member array.
    */
   private String[] _BenSuppress = null;
   
   /**
    * Ben Waive member array.
    */
   private String[] _BenWaive = null;
   
   /**
    * Ben Mail member array.
    */
   private String[] _BenMail = null;
   
   /**
    * Ben Fax member array.
    */
   private String[] _BenFax = null;
   
   /**
    * Ben CD member array.
    */
   private String[] _BenCD = null;
   
   /**
    * Ben Email member array.
    */
   private String[] _BenEmail = null;
   
   /**
    * Stmt Suppress member array.
    */
   private String[] _StmtSuppress = null;
   
   /**
    * Stmt Waive member array.
    */
   private String[] _StmtWaive = null;
   
   /**
    * Stmt Mail member array.
    */
   private String[] _StmtMail = null;
   
   /**
    * Stmt Fax member array.
    */
   private String[] _StmtFax = null;
   
   /**
    * Stmt CD member array.
    */
   private String[] _StmtCD = null;
   
   /**
    * Stmt Email member array.
    */
   private String[] _StmtEmail = null;
   
   /**
    * Dup Stmt Suppress member array.
    */
   private String[] _DupStmtSuppress = null;
   
   /**
    * Dup Stmt Waive member array.
    */
   private String[] _DupStmtWaive = null;
   
   /**
    * Dup Stmt Mail member array.
    */
   private String[] _DupStmtMail = null;
   
   /**
    * Dup Stmt Fax member array.
    */
   private String[] _DupStmtFax = null;
   
   /**
    * Dup Stmt CD member array.
    */
   private String[] _DupStmtCD = null;
   
   /**
    * Dup Stmt Email member array.
    */
   private String[] _DupStmtEmail = null;
   
   /**
    * NF Conf Suppress member array.
    */
   private String[] _NFConfSuppress = null;
   
   /**
    * NF Conf Waive member array.
    */
   private String[] _NFConfWaive = null;
   
   /**
    * NF Conf Mail member array.
    */
   private String[] _NFConfMail = null;
   
   /**
    * NF Conf Fax member array.
    */
   private String[] _NFConfFax = null;
   
   /**
    * NF Conf CD member array.
    */
   private String[] _NFConfCD = null;
   
   /**
    * NF Conf Email member array.
    */
   private String[] _NFConfEmail = null;
   
   /**
    * Txn Conf Suppress member array.
    */
   private String[] _TxnConfSuppress = null;
   
   /**
    * Txn Conf Waive member array.
    */
   private String[] _TxnConfWaive = null;
   
   /**
    * Txn Conf Mail member array.
    */
   private String[] _TxnConfMail = null;
   
   /**
    * Txn Conf Fax member array.
    */
   private String[] _TxnConfFax = null;
   
   /**
    * Txn Conf CD member array.
    */
   private String[] _TxnConfCD = null;
   
   /**
    * Txn Conf Email member array.
    */
   private String[] _TxnConfEmail = null;
   
   /**
    * Dup Conf Suppress member array.
    */
   private String[] _DupConfSuppress = null;
   
   /**
    * Dup Conf Waive member array.
    */
   private String[] _DupConfWaive = null;
   
   /**
    * Dup Conf Mail member array.
    */
   private String[] _DupConfMail = null;
   
   /**
    * Dup Conf Fax member array.
    */
   private String[] _DupConfFax = null;
   
   /**
    * Dup Conf CD member array.
    */
   private String[] _DupConfCD = null;
   
   /**
    * Dup Conf Email member array.
    */
   private String[] _DupConfEmail = null;
   
   /**
    * Semi Annual Report Suppress member array.
    */
   private String[] _SmAnnlRptSuppress = null;
   
   /**
    * Semi Annual Report Waive member array.
    */
   private String[] _SmAnnlRptWaive = null;
   
   /**
    * Semi Annual Report Mail member array.
    */
   private String[] _SmAnnlRptMail = null;
   
   /**
    * Semi Annual Report Fax member array.
    */
   private String[] _SmAnnlRptFax = null;
   
   /**
    * Semi Annual Report CD member array.
    */
   private String[] _SmAnnlRptCD = null;
   
   /**
    * Semi Annual Report Email member array.
    */
   private String[] _SmAnnlRptEmail = null;
   
   /**
    * Semi Annual Report Address Code member array.
    */
   private String[] _SmAnnlRptAddr = null;
   
   /**
    * Semi Annual Report On Hold member array.
    */
   private Boolean[] _SmAnnlRptHold = null;
   
   /**
    * Tax E-Post member array.
    */
   private String[] _TaxEPost = null;
   
   /**
    * Letter E-Post member array.
    */
   private String[] _LetEPost = null;
   
   /**
    * Certificate E-Post member array.
    */
   private String[] _CertEPost = null;
   
   /**
    * Dividend Confirm EPost member array.
    */
   private String[] _DivConfEPost = null;
   
   /**
    * Dividend Chq EPost member array.
    */
   private String[] _DivChqEPost = null;
   
   /**
    * Contribution EPost member array.
    */
   private String[] _ContrEPost = null;
   
   /**
    * Registered Mail EPost member array.
    */
   private String[] _RegEPost = null;
   
   /**
    * Annual Reports EPost member array.
    */
   private String[] _AnnlRptsEPost = null;
   
   /**
    * Prospectus EPost member array.
    */
   private String[] _ProspEPost = null;
   
   /**
    * Beneficiary EPost member array.
    */
   private String[] _BenEPost = null;
   
   /**
    * Statement EPost member array.
    */
   private String[] _StmtEPost = null;
   
   /**
    * Duplicate Statement EPost member array.
    */
   private String[] _DulStmtEPost = null;
   
   /**
    * NF Confirm EPost member array.
    */
   private String[] _NFConfEPost = null;
   
   /**
    * Txn Confirm EPost member array.
    */
   private String[] _TxnConfEPost = null;
   
   /**
    * Duplicate Confirm EPost member array.
    */
   private String[] _DupConfEPost = null;
   
   /**
    * Semi Annual Report EPost member array.
    */
   private String[] _SmAnnlRptEPost = null;
   
   /**
    * Contribution Receipt Suppress member array.
    */
   private String[] _ContrRSuppress = null;
   
   /**
    * Contribution Receipt Waive member array.
    */
   private String[] _ContrRWaive = null;
   
   /**
    * Contribution Receipt Mail member array.
    */
   private String[] _ContrRMail = null;
   
   /**
    * Contribution Receipt Fax member array.
    */
   private String[] _ContrRFax = null;
   
   /**
    * Contribution Receipt CD member array.
    */
   private String[] _ContrRCD = null;
   
   /**
    * Contribution Receipt EMail member array.
    */
   private String[] _ContrREmail = null;
   
   /**
    * Contribution Receipt EPost member array.
    */
   private String[] _ContrREPost = null;
   
   /**
    * Contribution Receipt Address Code member array.
    */
   private String[] _ContrRAddr = null;
   
   /**
    * Contribution Receipt On Hold member array.
    */
   private Boolean[] _ContrRHold = null;
   
   /**
    * Semi-Annual MRFP Address Code member array.
    */
   private String[] _SmAnnlMRFPAddr = null;
   
   /**
    * Semi-Annual MRFP Suppress member array.
    */
   private String[] _SmAnnlMRFPSuppress = null;
   
   /**
    * Semi-Annual MRFP Waive member array.
    */
   private String[] _SmAnnlMRFPWaive = null;
   
   /**
    * Semi-Annual MRFP Hold member array.
    */
   private Boolean[] _SmAnnlMRFPHold = null;
   
   /**
    * Semi-Annual MRFP Mail member array.
    */
   private String[] _SmAnnlMRFPMail = null;
   
   /**
    * Semi-Annual MRFP Fax member array.
    */
   private String[] _SmAnnlMRFPFax = null;
   
   /**
    * Semi-Annual MRFP CD member array.
    */
   private String[] _SmAnnlMRFPCD = null;
   
   /**
    * Semi-Annual MRFP Email member array.
    */
   private String[] _SmAnnlMRFPEmail = null;
   
   /**
    * Semi-Annual MRFP ePost member array.
    */
   private String[] _SmAnnlMRFPePost = null;
   
   /**
    * Semi-Annual MRFP Authorization member array.
    */
   private String[] _SmAnnlMRFPAuth = null;
   
   /**
    * Annual MRFP Address Code member array.
    */
   private String[] _AnnlMRFPAddr = null;
   
   /**
    * Annual MRFP Suppress member array.
    */
   private String[] _AnnlMRFPSuppress = null;
   
   /**
    * Annual MRFP Waive member array.
    */
   private String[] _AnnlMRFPWaive = null;
   
   /**
    * Annual MRFP Hold member array.
    */
   private Boolean[] _AnnlMRFPHold = null;
   
   /**
    * Annual MRFP Mail member array.
    */
   private String[] _AnnlMRFPMail = null;
   
   /**
    * Annual MRFP Fax member array.
    */
   private String[] _AnnLMRFPFax = null;
   
   /**
    * Annual MRFP CD member array.
    */
   private String[] _AnnlMRFPCD = null;
   
   /**
    * Annual MRFP Email member array.
    */
   private String[] _AnnlMRFPEmail = null;
   
   /**
    * Annual MRFP ePost member array.
    */
   private String[] _AnnlMRFPePost = null;
   
   /**
    * Annual MRFP Authorization member array.
    */
   private String[] _AnnlMRFPAuth = null;
   
   /**
    * Tax Receipts Authorization member array.
    */
   private String[] _TaxAuth = null;
   
   /**
    * Letter Authorization member array.
    */
   private String[] _LetAuth = null;
   
   /**
    * Certificate Authorization member array.
    */
   private String[] _CertAuth = null;
   
   /**
    * Dividend Confirm Authorization member array.
    */
   private String[] _DivConfAuth = null;
   
   /**
    * Dividend Cheque Authorization member array.
    */
   private String[] _DivChqAuth = null;
   
   /**
    * Contract Authorization member array.
    */
   private String[] _ContrAuth = null;
   
   /**
    * Register Authorization member array.
    */
   private String[] _RegAuth = null;
   
   /**
    * Annual Reports Authorization member array.
    */
   private String[] _AnnlRptsAuth = null;
   
   /**
    * Prospectus Authorization member array.
    */
   private String[] _ProspAuth = null;
   
   /**
    * Beneficial Authorization member array.
    */
   private String[] _BenAuth = null;
   
   /**
    * Statement Authorization member array.
    */
   private String[] _StmtAuth = null;
   
   /**
    * Duplicate Statement Authorization member array.
    */
   private String[] _DupStmtAuth = null;
   
   /**
    * Non Financial Confirmation Authorization member array.
    */
   private String[] _NFConfAuth = null;
   
   /**
    * Transaction Confirmation Authorization member array.
    */
   private String[] _TxnConfAuth = null;
   
   /**
    * Duplicate Confirmation Authorization member array.
    */
   private String[] _DupConfAuth = null;
   
   /**
    * Semi-Annual Report Authorization member array.
    */
   private String[] _SmAnnlRptAuth = null;
   
   /**
    * Contribution Receipt Authorization member array.
    */
   private String[] _ContrRAuth = null;
   
   /**
    * Statement Frequency member array.
    */
   private String[] _StmtFrequency = null;
   

   /**
    * Constructs the AccountMailingInformationView object.
    * 
    */
   public AccountMailingInformationView()
   {
      super ( new AccountMailingInformationRequest() );
   }

   /**
    * Constructs the AccountMailingInformationView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AccountMailingInformationView( String hostEncoding )
   {
      super ( new AccountMailingInformationRequest( hostEncoding ) );
   }

   /**
    * Gets the AccountMailingInformationRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AccountMailingInformationRequest object.
    */
   public final AccountMailingInformationRequest getRequest()
   {
      return (AccountMailingInformationRequest)getIFastRequest();
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
    * Gets the Register Address field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Register Address or null.
    */
   public final String getRegAddr( int index )
   {
      return _RegAddr[index];
   }
    
   /**
    * Gets the Register Address field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Register Address or the specified default value.
    */
   public final String getRegAddr( int index, String defaultValue )
   {
      return _RegAddr[index] == null ? defaultValue : _RegAddr[index];
   }
    
   /**
    * Gets the array of Register Address fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Register Address values.
    */
   public final String[] getRegAddrArray()
   {
      return _RegAddr;
   }
    
   /**
    * Gets the Dividend Confirm field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Dividend Confirm or null.
    */
   public final String getDivConfAddr( int index )
   {
      return _DivConfAddr[index];
   }
    
   /**
    * Gets the Dividend Confirm field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Dividend Confirm or the specified default value.
    */
   public final String getDivConfAddr( int index, String defaultValue )
   {
      return _DivConfAddr[index] == null ? defaultValue : _DivConfAddr[index];
   }
    
   /**
    * Gets the array of Dividend Confirm fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Dividend Confirm values.
    */
   public final String[] getDivConfAddrArray()
   {
      return _DivConfAddr;
   }
    
   /**
    * Gets the Dividend Cheque field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Dividend Cheque or null.
    */
   public final String getDivChqAddr( int index )
   {
      return _DivChqAddr[index];
   }
    
   /**
    * Gets the Dividend Cheque field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Dividend Cheque or the specified default value.
    */
   public final String getDivChqAddr( int index, String defaultValue )
   {
      return _DivChqAddr[index] == null ? defaultValue : _DivChqAddr[index];
   }
    
   /**
    * Gets the array of Dividend Cheque fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Dividend Cheque values.
    */
   public final String[] getDivChqAddrArray()
   {
      return _DivChqAddr;
   }
    
   /**
    * Gets the Transaction Confirm field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transaction Confirm or null.
    */
   public final String getTxnConfAddr( int index )
   {
      return _TxnConfAddr[index];
   }
    
   /**
    * Gets the Transaction Confirm field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transaction Confirm or the specified default value.
    */
   public final String getTxnConfAddr( int index, String defaultValue )
   {
      return _TxnConfAddr[index] == null ? defaultValue : _TxnConfAddr[index];
   }
    
   /**
    * Gets the array of Transaction Confirm fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transaction Confirm values.
    */
   public final String[] getTxnConfAddrArray()
   {
      return _TxnConfAddr;
   }
    
   /**
    * Gets the Duplicate Confirm field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Duplicate Confirm or null.
    */
   public final String getDupConfAddr( int index )
   {
      return _DupConfAddr[index];
   }
    
   /**
    * Gets the Duplicate Confirm field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Duplicate Confirm or the specified default value.
    */
   public final String getDupConfAddr( int index, String defaultValue )
   {
      return _DupConfAddr[index] == null ? defaultValue : _DupConfAddr[index];
   }
    
   /**
    * Gets the array of Duplicate Confirm fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Duplicate Confirm values.
    */
   public final String[] getDupConfAddrArray()
   {
      return _DupConfAddr;
   }
    
   /**
    * Gets the Statement field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Statement or null.
    */
   public final String getStmtAddr( int index )
   {
      return _StmtAddr[index];
   }
    
   /**
    * Gets the Statement field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Statement or the specified default value.
    */
   public final String getStmtAddr( int index, String defaultValue )
   {
      return _StmtAddr[index] == null ? defaultValue : _StmtAddr[index];
   }
    
   /**
    * Gets the array of Statement fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Statement values.
    */
   public final String[] getStmtAddrArray()
   {
      return _StmtAddr;
   }
    
   /**
    * Gets the Duplicate Statement field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Duplicate Statement or null.
    */
   public final String getDupStmtAddr( int index )
   {
      return _DupStmtAddr[index];
   }
    
   /**
    * Gets the Duplicate Statement field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Duplicate Statement or the specified default value.
    */
   public final String getDupStmtAddr( int index, String defaultValue )
   {
      return _DupStmtAddr[index] == null ? defaultValue : _DupStmtAddr[index];
   }
    
   /**
    * Gets the array of Duplicate Statement fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Duplicate Statement values.
    */
   public final String[] getDupStmtAddrArray()
   {
      return _DupStmtAddr;
   }
    
   /**
    * Gets the Certifiates field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Certifiates or null.
    */
   public final String getCertAddr( int index )
   {
      return _CertAddr[index];
   }
    
   /**
    * Gets the Certifiates field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Certifiates or the specified default value.
    */
   public final String getCertAddr( int index, String defaultValue )
   {
      return _CertAddr[index] == null ? defaultValue : _CertAddr[index];
   }
    
   /**
    * Gets the array of Certifiates fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Certifiates values.
    */
   public final String[] getCertAddrArray()
   {
      return _CertAddr;
   }
    
   /**
    * Gets the Tax Receipts field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax Receipts or null.
    */
   public final String getTaxAddr( int index )
   {
      return _TaxAddr[index];
   }
    
   /**
    * Gets the Tax Receipts field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Receipts or the specified default value.
    */
   public final String getTaxAddr( int index, String defaultValue )
   {
      return _TaxAddr[index] == null ? defaultValue : _TaxAddr[index];
   }
    
   /**
    * Gets the array of Tax Receipts fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax Receipts values.
    */
   public final String[] getTaxAddrArray()
   {
      return _TaxAddr;
   }
    
   /**
    * Gets the Letters field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Letters or null.
    */
   public final String getLetAddr( int index )
   {
      return _LetAddr[index];
   }
    
   /**
    * Gets the Letters field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Letters or the specified default value.
    */
   public final String getLetAddr( int index, String defaultValue )
   {
      return _LetAddr[index] == null ? defaultValue : _LetAddr[index];
   }
    
   /**
    * Gets the array of Letters fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Letters values.
    */
   public final String[] getLetAddrArray()
   {
      return _LetAddr;
   }
    
   /**
    * Gets the Beneficial Owner field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Beneficial Owner or null.
    */
   public final String getBenAddr( int index )
   {
      return _BenAddr[index];
   }
    
   /**
    * Gets the Beneficial Owner field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Beneficial Owner or the specified default value.
    */
   public final String getBenAddr( int index, String defaultValue )
   {
      return _BenAddr[index] == null ? defaultValue : _BenAddr[index];
   }
    
   /**
    * Gets the array of Beneficial Owner fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Beneficial Owner values.
    */
   public final String[] getBenAddrArray()
   {
      return _BenAddr;
   }
    
   /**
    * Gets the Copies for Duplicate Confirm field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Copies for Duplicate Confirm or null.
    */
   public final Integer getDupConfCopies( int index )
   {
      return _DupConfCopies[index];
   }
    
   /**
    * Gets the Copies for Duplicate Confirm field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Copies for Duplicate Confirm or the specified default value.
    */
   public final int getDupConfCopies( int index, int defaultValue )
   {
      return _DupConfCopies[index] == null ? defaultValue : _DupConfCopies[index].intValue();
   }
    
   /**
    * Gets the array of Copies for Duplicate Confirm fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Copies for Duplicate Confirm values.
    */
   public final Integer[] getDupConfCopiesArray()
   {
      return _DupConfCopies;
   }
    
   /**
    * Gets the Copies for Duplicate Statement field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Copies for Duplicate Statement or null.
    */
   public final Integer getDupStmtCopies( int index )
   {
      return _DupStmtCopies[index];
   }
    
   /**
    * Gets the Copies for Duplicate Statement field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Copies for Duplicate Statement or the specified default value.
    */
   public final int getDupStmtCopies( int index, int defaultValue )
   {
      return _DupStmtCopies[index] == null ? defaultValue : _DupStmtCopies[index].intValue();
   }
    
   /**
    * Gets the array of Copies for Duplicate Statement fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Copies for Duplicate Statement values.
    */
   public final Integer[] getDupStmtCopiesArray()
   {
      return _DupStmtCopies;
   }
    
   /**
    * Gets the Hold mail for registered address field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Hold mail for registered address or null.
    */
   public final Boolean getRegOnHold( int index )
   {
      return _RegOnHold[index];
   }
    
   /**
    * Gets the Hold mail for registered address field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Hold mail for registered address or the specified default value.
    */
   public final boolean getRegOnHold( int index, boolean defaultValue )
   {
      return _RegOnHold[index] == null ? defaultValue : _RegOnHold[index].booleanValue();
   }
    
   /**
    * Gets the array of Hold mail for registered address fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Hold mail for registered address values.
    */
   public final Boolean[] getRegOnHoldArray()
   {
      return _RegOnHold;
   }
    
   /**
    * Gets the Hold mail for dividend confirm field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Hold mail for dividend confirm or null.
    */
   public final Boolean getDivConfOnHold( int index )
   {
      return _DivConfOnHold[index];
   }
    
   /**
    * Gets the Hold mail for dividend confirm field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Hold mail for dividend confirm or the specified default value.
    */
   public final boolean getDivConfOnHold( int index, boolean defaultValue )
   {
      return _DivConfOnHold[index] == null ? defaultValue : _DivConfOnHold[index].booleanValue();
   }
    
   /**
    * Gets the array of Hold mail for dividend confirm fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Hold mail for dividend confirm values.
    */
   public final Boolean[] getDivConfOnHoldArray()
   {
      return _DivConfOnHold;
   }
    
   /**
    * Gets the Hold mail for dividend cheques field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Hold mail for dividend cheques or null.
    */
   public final Boolean getDivChqOnHold( int index )
   {
      return _DivChqOnHold[index];
   }
    
   /**
    * Gets the Hold mail for dividend cheques field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Hold mail for dividend cheques or the specified default value.
    */
   public final boolean getDivChqOnHold( int index, boolean defaultValue )
   {
      return _DivChqOnHold[index] == null ? defaultValue : _DivChqOnHold[index].booleanValue();
   }
    
   /**
    * Gets the array of Hold mail for dividend cheques fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Hold mail for dividend cheques values.
    */
   public final Boolean[] getDivChqOnHoldArray()
   {
      return _DivChqOnHold;
   }
    
   /**
    * Gets the Hold mail for confirmation field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Hold mail for confirmation or null.
    */
   public final Boolean getTxnConfOnHold( int index )
   {
      return _TxnConfOnHold[index];
   }
    
   /**
    * Gets the Hold mail for confirmation field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Hold mail for confirmation or the specified default value.
    */
   public final boolean getTxnConfOnHold( int index, boolean defaultValue )
   {
      return _TxnConfOnHold[index] == null ? defaultValue : _TxnConfOnHold[index].booleanValue();
   }
    
   /**
    * Gets the array of Hold mail for confirmation fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Hold mail for confirmation values.
    */
   public final Boolean[] getTxnConfOnHoldArray()
   {
      return _TxnConfOnHold;
   }
    
   /**
    * Gets the Hold mail for duplication confirm field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Hold mail for duplication confirm or null.
    */
   public final Boolean getDupConfOnHold( int index )
   {
      return _DupConfOnHold[index];
   }
    
   /**
    * Gets the Hold mail for duplication confirm field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Hold mail for duplication confirm or the specified default value.
    */
   public final boolean getDupConfOnHold( int index, boolean defaultValue )
   {
      return _DupConfOnHold[index] == null ? defaultValue : _DupConfOnHold[index].booleanValue();
   }
    
   /**
    * Gets the array of Hold mail for duplication confirm fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Hold mail for duplication confirm values.
    */
   public final Boolean[] getDupConfOnHoldArray()
   {
      return _DupConfOnHold;
   }
    
   /**
    * Gets the Hold mail for statement field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Hold mail for statement or null.
    */
   public final Boolean getStmtOnHold( int index )
   {
      return _StmtOnHold[index];
   }
    
   /**
    * Gets the Hold mail for statement field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Hold mail for statement or the specified default value.
    */
   public final boolean getStmtOnHold( int index, boolean defaultValue )
   {
      return _StmtOnHold[index] == null ? defaultValue : _StmtOnHold[index].booleanValue();
   }
    
   /**
    * Gets the array of Hold mail for statement fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Hold mail for statement values.
    */
   public final Boolean[] getStmtOnHoldArray()
   {
      return _StmtOnHold;
   }
    
   /**
    * Gets the Hold mail for duplication statement field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Hold mail for duplication statement or null.
    */
   public final Boolean getDupStmtOnHold( int index )
   {
      return _DupStmtOnHold[index];
   }
    
   /**
    * Gets the Hold mail for duplication statement field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Hold mail for duplication statement or the specified default value.
    */
   public final boolean getDupStmtOnHold( int index, boolean defaultValue )
   {
      return _DupStmtOnHold[index] == null ? defaultValue : _DupStmtOnHold[index].booleanValue();
   }
    
   /**
    * Gets the array of Hold mail for duplication statement fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Hold mail for duplication statement values.
    */
   public final Boolean[] getDupStmtOnHoldArray()
   {
      return _DupStmtOnHold;
   }
    
   /**
    * Gets the Hold mail for certificates field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Hold mail for certificates or null.
    */
   public final Boolean getCertOnHold( int index )
   {
      return _CertOnHold[index];
   }
    
   /**
    * Gets the Hold mail for certificates field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Hold mail for certificates or the specified default value.
    */
   public final boolean getCertOnHold( int index, boolean defaultValue )
   {
      return _CertOnHold[index] == null ? defaultValue : _CertOnHold[index].booleanValue();
   }
    
   /**
    * Gets the array of Hold mail for certificates fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Hold mail for certificates values.
    */
   public final Boolean[] getCertOnHoldArray()
   {
      return _CertOnHold;
   }
    
   /**
    * Gets the Hold mail for tax receipts field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Hold mail for tax receipts or null.
    */
   public final Boolean getTaxOnHold( int index )
   {
      return _TaxOnHold[index];
   }
    
   /**
    * Gets the Hold mail for tax receipts field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Hold mail for tax receipts or the specified default value.
    */
   public final boolean getTaxOnHold( int index, boolean defaultValue )
   {
      return _TaxOnHold[index] == null ? defaultValue : _TaxOnHold[index].booleanValue();
   }
    
   /**
    * Gets the array of Hold mail for tax receipts fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Hold mail for tax receipts values.
    */
   public final Boolean[] getTaxOnHoldArray()
   {
      return _TaxOnHold;
   }
    
   /**
    * Gets the Hold mail for letters field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Hold mail for letters or null.
    */
   public final Boolean getLetOnHold( int index )
   {
      return _LetOnHold[index];
   }
    
   /**
    * Gets the Hold mail for letters field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Hold mail for letters or the specified default value.
    */
   public final boolean getLetOnHold( int index, boolean defaultValue )
   {
      return _LetOnHold[index] == null ? defaultValue : _LetOnHold[index].booleanValue();
   }
    
   /**
    * Gets the array of Hold mail for letters fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Hold mail for letters values.
    */
   public final Boolean[] getLetOnHoldArray()
   {
      return _LetOnHold;
   }
    
   /**
    * Gets the Hold mail for beneficial owner field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Hold mail for beneficial owner or null.
    */
   public final Boolean getBenOnHold( int index )
   {
      return _BenOnHold[index];
   }
    
   /**
    * Gets the Hold mail for beneficial owner field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Hold mail for beneficial owner or the specified default value.
    */
   public final boolean getBenOnHold( int index, boolean defaultValue )
   {
      return _BenOnHold[index] == null ? defaultValue : _BenOnHold[index].booleanValue();
   }
    
   /**
    * Gets the array of Hold mail for beneficial owner fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Hold mail for beneficial owner values.
    */
   public final Boolean[] getBenOnHoldArray()
   {
      return _BenOnHold;
   }
    
   /**
    * Gets the Servicing Agent code for Confirms field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Servicing Agent code for Confirms or null.
    */
   public final String getSATxnConfCode( int index )
   {
      return _SATxnConfCode[index];
   }
    
   /**
    * Gets the Servicing Agent code for Confirms field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Servicing Agent code for Confirms or the specified default value.
    */
   public final String getSATxnConfCode( int index, String defaultValue )
   {
      return _SATxnConfCode[index] == null ? defaultValue : _SATxnConfCode[index];
   }
    
   /**
    * Gets the array of Servicing Agent code for Confirms fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Servicing Agent code for Confirms values.
    */
   public final String[] getSATxnConfCodeArray()
   {
      return _SATxnConfCode;
   }
    
   /**
    * Gets the Servicing Agent Desc.  for Confirms field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Servicing Agent Desc.  for Confirms or null.
    */
   public final String getSATxnConfDesc( int index )
   {
      return _SATxnConfDesc[index];
   }
    
   /**
    * Gets the Servicing Agent Desc.  for Confirms field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Servicing Agent Desc.  for Confirms or the specified default value.
    */
   public final String getSATxnConfDesc( int index, String defaultValue )
   {
      return _SATxnConfDesc[index] == null ? defaultValue : _SATxnConfDesc[index];
   }
    
   /**
    * Gets the array of Servicing Agent Desc.  for Confirms fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Servicing Agent Desc.  for Confirms values.
    */
   public final String[] getSATxnConfDescArray()
   {
      return _SATxnConfDesc;
   }
    
   /**
    * Gets the Servicing Agent code for Div. Confirms field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Servicing Agent code for Div. Confirms or null.
    */
   public final String getSADivConfCode( int index )
   {
      return _SADivConfCode[index];
   }
    
   /**
    * Gets the Servicing Agent code for Div. Confirms field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Servicing Agent code for Div. Confirms or the specified default value.
    */
   public final String getSADivConfCode( int index, String defaultValue )
   {
      return _SADivConfCode[index] == null ? defaultValue : _SADivConfCode[index];
   }
    
   /**
    * Gets the array of Servicing Agent code for Div. Confirms fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Servicing Agent code for Div. Confirms values.
    */
   public final String[] getSADivConfCodeArray()
   {
      return _SADivConfCode;
   }
    
   /**
    * Gets the Servicing Agent Desc.  for Div. Confirms field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Servicing Agent Desc.  for Div. Confirms or null.
    */
   public final String getSADivConfDesc( int index )
   {
      return _SADivConfDesc[index];
   }
    
   /**
    * Gets the Servicing Agent Desc.  for Div. Confirms field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Servicing Agent Desc.  for Div. Confirms or the specified default value.
    */
   public final String getSADivConfDesc( int index, String defaultValue )
   {
      return _SADivConfDesc[index] == null ? defaultValue : _SADivConfDesc[index];
   }
    
   /**
    * Gets the array of Servicing Agent Desc.  for Div. Confirms fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Servicing Agent Desc.  for Div. Confirms values.
    */
   public final String[] getSADivConfDescArray()
   {
      return _SADivConfDesc;
   }
    
   /**
    * Gets the Servicing Agent Code for Letters field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Servicing Agent Code for Letters or null.
    */
   public final String getSALettersCode( int index )
   {
      return _SALettersCode[index];
   }
    
   /**
    * Gets the Servicing Agent Code for Letters field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Servicing Agent Code for Letters or the specified default value.
    */
   public final String getSALettersCode( int index, String defaultValue )
   {
      return _SALettersCode[index] == null ? defaultValue : _SALettersCode[index];
   }
    
   /**
    * Gets the array of Servicing Agent Code for Letters fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Servicing Agent Code for Letters values.
    */
   public final String[] getSALettersCodeArray()
   {
      return _SALettersCode;
   }
    
   /**
    * Gets the Servicing Agent Desc. for Letters field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Servicing Agent Desc. for Letters or null.
    */
   public final String getSALettersDesc( int index )
   {
      return _SALettersDesc[index];
   }
    
   /**
    * Gets the Servicing Agent Desc. for Letters field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Servicing Agent Desc. for Letters or the specified default value.
    */
   public final String getSALettersDesc( int index, String defaultValue )
   {
      return _SALettersDesc[index] == null ? defaultValue : _SALettersDesc[index];
   }
    
   /**
    * Gets the array of Servicing Agent Desc. for Letters fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Servicing Agent Desc. for Letters values.
    */
   public final String[] getSALettersDescArray()
   {
      return _SALettersDesc;
   }
    
   /**
    * Gets the Acct-Mstr Version Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Acct-Mstr Version Number or null.
    */
   public final Integer getAcctMstrVer( int index )
   {
      return _AcctMstrVer[index];
   }
    
   /**
    * Gets the Acct-Mstr Version Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Acct-Mstr Version Number or the specified default value.
    */
   public final int getAcctMstrVer( int index, int defaultValue )
   {
      return _AcctMstrVer[index] == null ? defaultValue : _AcctMstrVer[index].intValue();
   }
    
   /**
    * Gets the array of Acct-Mstr Version Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Acct-Mstr Version Number values.
    */
   public final Integer[] getAcctMstrVerArray()
   {
      return _AcctMstrVer;
   }
    
   /**
    * Gets the Acct-Mstr Record Id field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Acct-Mstr Record Id or null.
    */
   public final Integer getAcctMstrRid( int index )
   {
      return _AcctMstrRid[index];
   }
    
   /**
    * Gets the Acct-Mstr Record Id field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Acct-Mstr Record Id or the specified default value.
    */
   public final int getAcctMstrRid( int index, int defaultValue )
   {
      return _AcctMstrRid[index] == null ? defaultValue : _AcctMstrRid[index].intValue();
   }
    
   /**
    * Gets the array of Acct-Mstr Record Id fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Acct-Mstr Record Id values.
    */
   public final Integer[] getAcctMstrRidArray()
   {
      return _AcctMstrRid;
   }
    
   /**
    * Gets the Non Financial Confirmation field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Non Financial Confirmation or null.
    */
   public final String getNFCAddr( int index )
   {
      return _NFCAddr[index];
   }
    
   /**
    * Gets the Non Financial Confirmation field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Non Financial Confirmation or the specified default value.
    */
   public final String getNFCAddr( int index, String defaultValue )
   {
      return _NFCAddr[index] == null ? defaultValue : _NFCAddr[index];
   }
    
   /**
    * Gets the array of Non Financial Confirmation fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Non Financial Confirmation values.
    */
   public final String[] getNFCAddrArray()
   {
      return _NFCAddr;
   }
    
   /**
    * Gets the Non Financial Confirm on Hold field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Non Financial Confirm on Hold or null.
    */
   public final Boolean getNFConHold( int index )
   {
      return _NFConHold[index];
   }
    
   /**
    * Gets the Non Financial Confirm on Hold field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Non Financial Confirm on Hold or the specified default value.
    */
   public final boolean getNFConHold( int index, boolean defaultValue )
   {
      return _NFConHold[index] == null ? defaultValue : _NFConHold[index].booleanValue();
   }
    
   /**
    * Gets the array of Non Financial Confirm on Hold fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Non Financial Confirm on Hold values.
    */
   public final Boolean[] getNFConHoldArray()
   {
      return _NFConHold;
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
    * Gets the Contract Address Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contract Address Code or null.
    */
   public final String getContrAddr( int index )
   {
      return _ContrAddr[index];
   }
    
   /**
    * Gets the Contract Address Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contract Address Code or the specified default value.
    */
   public final String getContrAddr( int index, String defaultValue )
   {
      return _ContrAddr[index] == null ? defaultValue : _ContrAddr[index];
   }
    
   /**
    * Gets the array of Contract Address Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contract Address Code values.
    */
   public final String[] getContrAddrArray()
   {
      return _ContrAddr;
   }
    
   /**
    * Gets the Contract Address Use on Hold field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contract Address Use on Hold or null.
    */
   public final Boolean getContrHold( int index )
   {
      return _ContrHold[index];
   }
    
   /**
    * Gets the Contract Address Use on Hold field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contract Address Use on Hold or the specified default value.
    */
   public final boolean getContrHold( int index, boolean defaultValue )
   {
      return _ContrHold[index] == null ? defaultValue : _ContrHold[index].booleanValue();
   }
    
   /**
    * Gets the array of Contract Address Use on Hold fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contract Address Use on Hold values.
    */
   public final Boolean[] getContrHoldArray()
   {
      return _ContrHold;
   }
    
   /**
    * Gets the Annual Reports Address Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Annual Reports Address Code or null.
    */
   public final String getAnnlRptsAddr( int index )
   {
      return _AnnlRptsAddr[index];
   }
    
   /**
    * Gets the Annual Reports Address Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Annual Reports Address Code or the specified default value.
    */
   public final String getAnnlRptsAddr( int index, String defaultValue )
   {
      return _AnnlRptsAddr[index] == null ? defaultValue : _AnnlRptsAddr[index];
   }
    
   /**
    * Gets the array of Annual Reports Address Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Annual Reports Address Code values.
    */
   public final String[] getAnnlRptsAddrArray()
   {
      return _AnnlRptsAddr;
   }
    
   /**
    * Gets the Annual Reports Address Use on Hold field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Annual Reports Address Use on Hold or null.
    */
   public final Boolean getAnnlRptsHold( int index )
   {
      return _AnnlRptsHold[index];
   }
    
   /**
    * Gets the Annual Reports Address Use on Hold field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Annual Reports Address Use on Hold or the specified default value.
    */
   public final boolean getAnnlRptsHold( int index, boolean defaultValue )
   {
      return _AnnlRptsHold[index] == null ? defaultValue : _AnnlRptsHold[index].booleanValue();
   }
    
   /**
    * Gets the array of Annual Reports Address Use on Hold fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Annual Reports Address Use on Hold values.
    */
   public final Boolean[] getAnnlRptsHoldArray()
   {
      return _AnnlRptsHold;
   }
    
   /**
    * Gets the Prospectus Address Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Prospectus Address Code or null.
    */
   public final String getProspAddr( int index )
   {
      return _ProspAddr[index];
   }
    
   /**
    * Gets the Prospectus Address Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Prospectus Address Code or the specified default value.
    */
   public final String getProspAddr( int index, String defaultValue )
   {
      return _ProspAddr[index] == null ? defaultValue : _ProspAddr[index];
   }
    
   /**
    * Gets the array of Prospectus Address Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Prospectus Address Code values.
    */
   public final String[] getProspAddrArray()
   {
      return _ProspAddr;
   }
    
   /**
    * Gets the Prospectus Address Use on Hold field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Prospectus Address Use on Hold or null.
    */
   public final Boolean getProspHold( int index )
   {
      return _ProspHold[index];
   }
    
   /**
    * Gets the Prospectus Address Use on Hold field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Prospectus Address Use on Hold or the specified default value.
    */
   public final boolean getProspHold( int index, boolean defaultValue )
   {
      return _ProspHold[index] == null ? defaultValue : _ProspHold[index].booleanValue();
   }
    
   /**
    * Gets the array of Prospectus Address Use on Hold fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Prospectus Address Use on Hold values.
    */
   public final Boolean[] getProspHoldArray()
   {
      return _ProspHold;
   }
    
   /**
    * Gets the Tax Suppress field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax Suppress or null.
    */
   public final String getTaxSuppress( int index )
   {
      return _TaxSuppress[index];
   }
    
   /**
    * Gets the Tax Suppress field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Suppress or the specified default value.
    */
   public final String getTaxSuppress( int index, String defaultValue )
   {
      return _TaxSuppress[index] == null ? defaultValue : _TaxSuppress[index];
   }
    
   /**
    * Gets the array of Tax Suppress fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax Suppress values.
    */
   public final String[] getTaxSuppressArray()
   {
      return _TaxSuppress;
   }
    
   /**
    * Gets the Tax Waive field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax Waive or null.
    */
   public final String getTaxWaive( int index )
   {
      return _TaxWaive[index];
   }
    
   /**
    * Gets the Tax Waive field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Waive or the specified default value.
    */
   public final String getTaxWaive( int index, String defaultValue )
   {
      return _TaxWaive[index] == null ? defaultValue : _TaxWaive[index];
   }
    
   /**
    * Gets the array of Tax Waive fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax Waive values.
    */
   public final String[] getTaxWaiveArray()
   {
      return _TaxWaive;
   }
    
   /**
    * Gets the Tax Mail field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax Mail or null.
    */
   public final String getTaxMail( int index )
   {
      return _TaxMail[index];
   }
    
   /**
    * Gets the Tax Mail field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Mail or the specified default value.
    */
   public final String getTaxMail( int index, String defaultValue )
   {
      return _TaxMail[index] == null ? defaultValue : _TaxMail[index];
   }
    
   /**
    * Gets the array of Tax Mail fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax Mail values.
    */
   public final String[] getTaxMailArray()
   {
      return _TaxMail;
   }
    
   /**
    * Gets the Tax Fax field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax Fax or null.
    */
   public final String getTaxFax( int index )
   {
      return _TaxFax[index];
   }
    
   /**
    * Gets the Tax Fax field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Fax or the specified default value.
    */
   public final String getTaxFax( int index, String defaultValue )
   {
      return _TaxFax[index] == null ? defaultValue : _TaxFax[index];
   }
    
   /**
    * Gets the array of Tax Fax fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax Fax values.
    */
   public final String[] getTaxFaxArray()
   {
      return _TaxFax;
   }
    
   /**
    * Gets the Tax CD field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax CD or null.
    */
   public final String getTaxCD( int index )
   {
      return _TaxCD[index];
   }
    
   /**
    * Gets the Tax CD field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax CD or the specified default value.
    */
   public final String getTaxCD( int index, String defaultValue )
   {
      return _TaxCD[index] == null ? defaultValue : _TaxCD[index];
   }
    
   /**
    * Gets the array of Tax CD fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax CD values.
    */
   public final String[] getTaxCDArray()
   {
      return _TaxCD;
   }
    
   /**
    * Gets the Tax Email field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax Email or null.
    */
   public final String getTaxEmail( int index )
   {
      return _TaxEmail[index];
   }
    
   /**
    * Gets the Tax Email field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Email or the specified default value.
    */
   public final String getTaxEmail( int index, String defaultValue )
   {
      return _TaxEmail[index] == null ? defaultValue : _TaxEmail[index];
   }
    
   /**
    * Gets the array of Tax Email fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax Email values.
    */
   public final String[] getTaxEmailArray()
   {
      return _TaxEmail;
   }
    
   /**
    * Gets the Letter Suppress field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Letter Suppress or null.
    */
   public final String getLetSuppress( int index )
   {
      return _LetSuppress[index];
   }
    
   /**
    * Gets the Letter Suppress field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Letter Suppress or the specified default value.
    */
   public final String getLetSuppress( int index, String defaultValue )
   {
      return _LetSuppress[index] == null ? defaultValue : _LetSuppress[index];
   }
    
   /**
    * Gets the array of Letter Suppress fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Letter Suppress values.
    */
   public final String[] getLetSuppressArray()
   {
      return _LetSuppress;
   }
    
   /**
    * Gets the Letter Waive field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Letter Waive or null.
    */
   public final String getLetWaive( int index )
   {
      return _LetWaive[index];
   }
    
   /**
    * Gets the Letter Waive field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Letter Waive or the specified default value.
    */
   public final String getLetWaive( int index, String defaultValue )
   {
      return _LetWaive[index] == null ? defaultValue : _LetWaive[index];
   }
    
   /**
    * Gets the array of Letter Waive fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Letter Waive values.
    */
   public final String[] getLetWaiveArray()
   {
      return _LetWaive;
   }
    
   /**
    * Gets the Letter Mail field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Letter Mail or null.
    */
   public final String getLetMail( int index )
   {
      return _LetMail[index];
   }
    
   /**
    * Gets the Letter Mail field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Letter Mail or the specified default value.
    */
   public final String getLetMail( int index, String defaultValue )
   {
      return _LetMail[index] == null ? defaultValue : _LetMail[index];
   }
    
   /**
    * Gets the array of Letter Mail fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Letter Mail values.
    */
   public final String[] getLetMailArray()
   {
      return _LetMail;
   }
    
   /**
    * Gets the Letter Fax field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Letter Fax or null.
    */
   public final String getLetFax( int index )
   {
      return _LetFax[index];
   }
    
   /**
    * Gets the Letter Fax field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Letter Fax or the specified default value.
    */
   public final String getLetFax( int index, String defaultValue )
   {
      return _LetFax[index] == null ? defaultValue : _LetFax[index];
   }
    
   /**
    * Gets the array of Letter Fax fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Letter Fax values.
    */
   public final String[] getLetFaxArray()
   {
      return _LetFax;
   }
    
   /**
    * Gets the Letter Cd field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Letter Cd or null.
    */
   public final String getLetCD( int index )
   {
      return _LetCD[index];
   }
    
   /**
    * Gets the Letter Cd field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Letter Cd or the specified default value.
    */
   public final String getLetCD( int index, String defaultValue )
   {
      return _LetCD[index] == null ? defaultValue : _LetCD[index];
   }
    
   /**
    * Gets the array of Letter Cd fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Letter Cd values.
    */
   public final String[] getLetCDArray()
   {
      return _LetCD;
   }
    
   /**
    * Gets the Letter Email field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Letter Email or null.
    */
   public final String getLetEmail( int index )
   {
      return _LetEmail[index];
   }
    
   /**
    * Gets the Letter Email field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Letter Email or the specified default value.
    */
   public final String getLetEmail( int index, String defaultValue )
   {
      return _LetEmail[index] == null ? defaultValue : _LetEmail[index];
   }
    
   /**
    * Gets the array of Letter Email fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Letter Email values.
    */
   public final String[] getLetEmailArray()
   {
      return _LetEmail;
   }
    
   /**
    * Gets the Cert Suppress field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Cert Suppress or null.
    */
   public final String getCertSuppress( int index )
   {
      return _CertSuppress[index];
   }
    
   /**
    * Gets the Cert Suppress field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Cert Suppress or the specified default value.
    */
   public final String getCertSuppress( int index, String defaultValue )
   {
      return _CertSuppress[index] == null ? defaultValue : _CertSuppress[index];
   }
    
   /**
    * Gets the array of Cert Suppress fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Cert Suppress values.
    */
   public final String[] getCertSuppressArray()
   {
      return _CertSuppress;
   }
    
   /**
    * Gets the Cert Waive field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Cert Waive or null.
    */
   public final String getCertWaive( int index )
   {
      return _CertWaive[index];
   }
    
   /**
    * Gets the Cert Waive field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Cert Waive or the specified default value.
    */
   public final String getCertWaive( int index, String defaultValue )
   {
      return _CertWaive[index] == null ? defaultValue : _CertWaive[index];
   }
    
   /**
    * Gets the array of Cert Waive fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Cert Waive values.
    */
   public final String[] getCertWaiveArray()
   {
      return _CertWaive;
   }
    
   /**
    * Gets the Cert Mail field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Cert Mail or null.
    */
   public final String getCertMail( int index )
   {
      return _CertMail[index];
   }
    
   /**
    * Gets the Cert Mail field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Cert Mail or the specified default value.
    */
   public final String getCertMail( int index, String defaultValue )
   {
      return _CertMail[index] == null ? defaultValue : _CertMail[index];
   }
    
   /**
    * Gets the array of Cert Mail fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Cert Mail values.
    */
   public final String[] getCertMailArray()
   {
      return _CertMail;
   }
    
   /**
    * Gets the Cert Fax field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Cert Fax or null.
    */
   public final String getCertFax( int index )
   {
      return _CertFax[index];
   }
    
   /**
    * Gets the Cert Fax field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Cert Fax or the specified default value.
    */
   public final String getCertFax( int index, String defaultValue )
   {
      return _CertFax[index] == null ? defaultValue : _CertFax[index];
   }
    
   /**
    * Gets the array of Cert Fax fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Cert Fax values.
    */
   public final String[] getCertFaxArray()
   {
      return _CertFax;
   }
    
   /**
    * Gets the Cert CD field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Cert CD or null.
    */
   public final String getCertCD( int index )
   {
      return _CertCD[index];
   }
    
   /**
    * Gets the Cert CD field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Cert CD or the specified default value.
    */
   public final String getCertCD( int index, String defaultValue )
   {
      return _CertCD[index] == null ? defaultValue : _CertCD[index];
   }
    
   /**
    * Gets the array of Cert CD fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Cert CD values.
    */
   public final String[] getCertCDArray()
   {
      return _CertCD;
   }
    
   /**
    * Gets the Cert Email field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Cert Email or null.
    */
   public final String getCertEmail( int index )
   {
      return _CertEmail[index];
   }
    
   /**
    * Gets the Cert Email field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Cert Email or the specified default value.
    */
   public final String getCertEmail( int index, String defaultValue )
   {
      return _CertEmail[index] == null ? defaultValue : _CertEmail[index];
   }
    
   /**
    * Gets the array of Cert Email fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Cert Email values.
    */
   public final String[] getCertEmailArray()
   {
      return _CertEmail;
   }
    
   /**
    * Gets the Div Confirm Suopress field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Div Confirm Suopress or null.
    */
   public final String getDivConfSuppress( int index )
   {
      return _DivConfSuppress[index];
   }
    
   /**
    * Gets the Div Confirm Suopress field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Div Confirm Suopress or the specified default value.
    */
   public final String getDivConfSuppress( int index, String defaultValue )
   {
      return _DivConfSuppress[index] == null ? defaultValue : _DivConfSuppress[index];
   }
    
   /**
    * Gets the array of Div Confirm Suopress fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Div Confirm Suopress values.
    */
   public final String[] getDivConfSuppressArray()
   {
      return _DivConfSuppress;
   }
    
   /**
    * Gets the Div Confirm Waive field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Div Confirm Waive or null.
    */
   public final String getDivConfWaive( int index )
   {
      return _DivConfWaive[index];
   }
    
   /**
    * Gets the Div Confirm Waive field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Div Confirm Waive or the specified default value.
    */
   public final String getDivConfWaive( int index, String defaultValue )
   {
      return _DivConfWaive[index] == null ? defaultValue : _DivConfWaive[index];
   }
    
   /**
    * Gets the array of Div Confirm Waive fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Div Confirm Waive values.
    */
   public final String[] getDivConfWaiveArray()
   {
      return _DivConfWaive;
   }
    
   /**
    * Gets the Div Confirm Mail field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Div Confirm Mail or null.
    */
   public final String getDivConfMail( int index )
   {
      return _DivConfMail[index];
   }
    
   /**
    * Gets the Div Confirm Mail field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Div Confirm Mail or the specified default value.
    */
   public final String getDivConfMail( int index, String defaultValue )
   {
      return _DivConfMail[index] == null ? defaultValue : _DivConfMail[index];
   }
    
   /**
    * Gets the array of Div Confirm Mail fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Div Confirm Mail values.
    */
   public final String[] getDivConfMailArray()
   {
      return _DivConfMail;
   }
    
   /**
    * Gets the Div Confirm Fax field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Div Confirm Fax or null.
    */
   public final String getDivConfFax( int index )
   {
      return _DivConfFax[index];
   }
    
   /**
    * Gets the Div Confirm Fax field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Div Confirm Fax or the specified default value.
    */
   public final String getDivConfFax( int index, String defaultValue )
   {
      return _DivConfFax[index] == null ? defaultValue : _DivConfFax[index];
   }
    
   /**
    * Gets the array of Div Confirm Fax fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Div Confirm Fax values.
    */
   public final String[] getDivConfFaxArray()
   {
      return _DivConfFax;
   }
    
   /**
    * Gets the Div Confirm CD field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Div Confirm CD or null.
    */
   public final String getDivConfCD( int index )
   {
      return _DivConfCD[index];
   }
    
   /**
    * Gets the Div Confirm CD field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Div Confirm CD or the specified default value.
    */
   public final String getDivConfCD( int index, String defaultValue )
   {
      return _DivConfCD[index] == null ? defaultValue : _DivConfCD[index];
   }
    
   /**
    * Gets the array of Div Confirm CD fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Div Confirm CD values.
    */
   public final String[] getDivConfCDArray()
   {
      return _DivConfCD;
   }
    
   /**
    * Gets the Div Confirm Email field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Div Confirm Email or null.
    */
   public final String getDivConfEmail( int index )
   {
      return _DivConfEmail[index];
   }
    
   /**
    * Gets the Div Confirm Email field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Div Confirm Email or the specified default value.
    */
   public final String getDivConfEmail( int index, String defaultValue )
   {
      return _DivConfEmail[index] == null ? defaultValue : _DivConfEmail[index];
   }
    
   /**
    * Gets the array of Div Confirm Email fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Div Confirm Email values.
    */
   public final String[] getDivConfEmailArray()
   {
      return _DivConfEmail;
   }
    
   /**
    * Gets the Div Cheque Suppress field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Div Cheque Suppress or null.
    */
   public final String getDivChqSuppress( int index )
   {
      return _DivChqSuppress[index];
   }
    
   /**
    * Gets the Div Cheque Suppress field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Div Cheque Suppress or the specified default value.
    */
   public final String getDivChqSuppress( int index, String defaultValue )
   {
      return _DivChqSuppress[index] == null ? defaultValue : _DivChqSuppress[index];
   }
    
   /**
    * Gets the array of Div Cheque Suppress fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Div Cheque Suppress values.
    */
   public final String[] getDivChqSuppressArray()
   {
      return _DivChqSuppress;
   }
    
   /**
    * Gets the Div Cheque Waive field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Div Cheque Waive or null.
    */
   public final String getDivChqWaive( int index )
   {
      return _DivChqWaive[index];
   }
    
   /**
    * Gets the Div Cheque Waive field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Div Cheque Waive or the specified default value.
    */
   public final String getDivChqWaive( int index, String defaultValue )
   {
      return _DivChqWaive[index] == null ? defaultValue : _DivChqWaive[index];
   }
    
   /**
    * Gets the array of Div Cheque Waive fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Div Cheque Waive values.
    */
   public final String[] getDivChqWaiveArray()
   {
      return _DivChqWaive;
   }
    
   /**
    * Gets the Div Cheque Mail field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Div Cheque Mail or null.
    */
   public final String getDivChqMail( int index )
   {
      return _DivChqMail[index];
   }
    
   /**
    * Gets the Div Cheque Mail field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Div Cheque Mail or the specified default value.
    */
   public final String getDivChqMail( int index, String defaultValue )
   {
      return _DivChqMail[index] == null ? defaultValue : _DivChqMail[index];
   }
    
   /**
    * Gets the array of Div Cheque Mail fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Div Cheque Mail values.
    */
   public final String[] getDivChqMailArray()
   {
      return _DivChqMail;
   }
    
   /**
    * Gets the Div Cheque Fax field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Div Cheque Fax or null.
    */
   public final String getDivChqFax( int index )
   {
      return _DivChqFax[index];
   }
    
   /**
    * Gets the Div Cheque Fax field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Div Cheque Fax or the specified default value.
    */
   public final String getDivChqFax( int index, String defaultValue )
   {
      return _DivChqFax[index] == null ? defaultValue : _DivChqFax[index];
   }
    
   /**
    * Gets the array of Div Cheque Fax fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Div Cheque Fax values.
    */
   public final String[] getDivChqFaxArray()
   {
      return _DivChqFax;
   }
    
   /**
    * Gets the Div Cheque CD field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Div Cheque CD or null.
    */
   public final String getDivChqCD( int index )
   {
      return _DivChqCD[index];
   }
    
   /**
    * Gets the Div Cheque CD field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Div Cheque CD or the specified default value.
    */
   public final String getDivChqCD( int index, String defaultValue )
   {
      return _DivChqCD[index] == null ? defaultValue : _DivChqCD[index];
   }
    
   /**
    * Gets the array of Div Cheque CD fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Div Cheque CD values.
    */
   public final String[] getDivChqCDArray()
   {
      return _DivChqCD;
   }
    
   /**
    * Gets the Div Cheque Email field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Div Cheque Email or null.
    */
   public final String getDivChqEmail( int index )
   {
      return _DivChqEmail[index];
   }
    
   /**
    * Gets the Div Cheque Email field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Div Cheque Email or the specified default value.
    */
   public final String getDivChqEmail( int index, String defaultValue )
   {
      return _DivChqEmail[index] == null ? defaultValue : _DivChqEmail[index];
   }
    
   /**
    * Gets the array of Div Cheque Email fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Div Cheque Email values.
    */
   public final String[] getDivChqEmailArray()
   {
      return _DivChqEmail;
   }
    
   /**
    * Gets the Contr Suppress field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contr Suppress or null.
    */
   public final String getContrSuppress( int index )
   {
      return _ContrSuppress[index];
   }
    
   /**
    * Gets the Contr Suppress field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contr Suppress or the specified default value.
    */
   public final String getContrSuppress( int index, String defaultValue )
   {
      return _ContrSuppress[index] == null ? defaultValue : _ContrSuppress[index];
   }
    
   /**
    * Gets the array of Contr Suppress fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contr Suppress values.
    */
   public final String[] getContrSuppressArray()
   {
      return _ContrSuppress;
   }
    
   /**
    * Gets the Contr Waive field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contr Waive or null.
    */
   public final String getContrWaive( int index )
   {
      return _ContrWaive[index];
   }
    
   /**
    * Gets the Contr Waive field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contr Waive or the specified default value.
    */
   public final String getContrWaive( int index, String defaultValue )
   {
      return _ContrWaive[index] == null ? defaultValue : _ContrWaive[index];
   }
    
   /**
    * Gets the array of Contr Waive fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contr Waive values.
    */
   public final String[] getContrWaiveArray()
   {
      return _ContrWaive;
   }
    
   /**
    * Gets the Contr Mail field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contr Mail or null.
    */
   public final String getContrMail( int index )
   {
      return _ContrMail[index];
   }
    
   /**
    * Gets the Contr Mail field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contr Mail or the specified default value.
    */
   public final String getContrMail( int index, String defaultValue )
   {
      return _ContrMail[index] == null ? defaultValue : _ContrMail[index];
   }
    
   /**
    * Gets the array of Contr Mail fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contr Mail values.
    */
   public final String[] getContrMailArray()
   {
      return _ContrMail;
   }
    
   /**
    * Gets the Contr Fax field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contr Fax or null.
    */
   public final String getContrFax( int index )
   {
      return _ContrFax[index];
   }
    
   /**
    * Gets the Contr Fax field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contr Fax or the specified default value.
    */
   public final String getContrFax( int index, String defaultValue )
   {
      return _ContrFax[index] == null ? defaultValue : _ContrFax[index];
   }
    
   /**
    * Gets the array of Contr Fax fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contr Fax values.
    */
   public final String[] getContrFaxArray()
   {
      return _ContrFax;
   }
    
   /**
    * Gets the Contr CD field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contr CD or null.
    */
   public final String getContrCD( int index )
   {
      return _ContrCD[index];
   }
    
   /**
    * Gets the Contr CD field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contr CD or the specified default value.
    */
   public final String getContrCD( int index, String defaultValue )
   {
      return _ContrCD[index] == null ? defaultValue : _ContrCD[index];
   }
    
   /**
    * Gets the array of Contr CD fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contr CD values.
    */
   public final String[] getContrCDArray()
   {
      return _ContrCD;
   }
    
   /**
    * Gets the Contr Email field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contr Email or null.
    */
   public final String getContrEmail( int index )
   {
      return _ContrEmail[index];
   }
    
   /**
    * Gets the Contr Email field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contr Email or the specified default value.
    */
   public final String getContrEmail( int index, String defaultValue )
   {
      return _ContrEmail[index] == null ? defaultValue : _ContrEmail[index];
   }
    
   /**
    * Gets the array of Contr Email fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contr Email values.
    */
   public final String[] getContrEmailArray()
   {
      return _ContrEmail;
   }
    
   /**
    * Gets the Reg Suppress field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reg Suppress or null.
    */
   public final String getRegSuppress( int index )
   {
      return _RegSuppress[index];
   }
    
   /**
    * Gets the Reg Suppress field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reg Suppress or the specified default value.
    */
   public final String getRegSuppress( int index, String defaultValue )
   {
      return _RegSuppress[index] == null ? defaultValue : _RegSuppress[index];
   }
    
   /**
    * Gets the array of Reg Suppress fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reg Suppress values.
    */
   public final String[] getRegSuppressArray()
   {
      return _RegSuppress;
   }
    
   /**
    * Gets the Reg Waive field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reg Waive or null.
    */
   public final String getRegWaive( int index )
   {
      return _RegWaive[index];
   }
    
   /**
    * Gets the Reg Waive field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reg Waive or the specified default value.
    */
   public final String getRegWaive( int index, String defaultValue )
   {
      return _RegWaive[index] == null ? defaultValue : _RegWaive[index];
   }
    
   /**
    * Gets the array of Reg Waive fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reg Waive values.
    */
   public final String[] getRegWaiveArray()
   {
      return _RegWaive;
   }
    
   /**
    * Gets the Reg Mail field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reg Mail or null.
    */
   public final String getRegMail( int index )
   {
      return _RegMail[index];
   }
    
   /**
    * Gets the Reg Mail field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reg Mail or the specified default value.
    */
   public final String getRegMail( int index, String defaultValue )
   {
      return _RegMail[index] == null ? defaultValue : _RegMail[index];
   }
    
   /**
    * Gets the array of Reg Mail fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reg Mail values.
    */
   public final String[] getRegMailArray()
   {
      return _RegMail;
   }
    
   /**
    * Gets the Reg Fax field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reg Fax or null.
    */
   public final String getRegFax( int index )
   {
      return _RegFax[index];
   }
    
   /**
    * Gets the Reg Fax field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reg Fax or the specified default value.
    */
   public final String getRegFax( int index, String defaultValue )
   {
      return _RegFax[index] == null ? defaultValue : _RegFax[index];
   }
    
   /**
    * Gets the array of Reg Fax fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reg Fax values.
    */
   public final String[] getRegFaxArray()
   {
      return _RegFax;
   }
    
   /**
    * Gets the Reg CD field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reg CD or null.
    */
   public final String getRegCD( int index )
   {
      return _RegCD[index];
   }
    
   /**
    * Gets the Reg CD field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reg CD or the specified default value.
    */
   public final String getRegCD( int index, String defaultValue )
   {
      return _RegCD[index] == null ? defaultValue : _RegCD[index];
   }
    
   /**
    * Gets the array of Reg CD fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reg CD values.
    */
   public final String[] getRegCDArray()
   {
      return _RegCD;
   }
    
   /**
    * Gets the Reg Email field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reg Email or null.
    */
   public final String getRegEmail( int index )
   {
      return _RegEmail[index];
   }
    
   /**
    * Gets the Reg Email field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reg Email or the specified default value.
    */
   public final String getRegEmail( int index, String defaultValue )
   {
      return _RegEmail[index] == null ? defaultValue : _RegEmail[index];
   }
    
   /**
    * Gets the array of Reg Email fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reg Email values.
    */
   public final String[] getRegEmailArray()
   {
      return _RegEmail;
   }
    
   /**
    * Gets the Annual Reports Suppress field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Annual Reports Suppress or null.
    */
   public final String getAnnlRptsSuppress( int index )
   {
      return _AnnlRptsSuppress[index];
   }
    
   /**
    * Gets the Annual Reports Suppress field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Annual Reports Suppress or the specified default value.
    */
   public final String getAnnlRptsSuppress( int index, String defaultValue )
   {
      return _AnnlRptsSuppress[index] == null ? defaultValue : _AnnlRptsSuppress[index];
   }
    
   /**
    * Gets the array of Annual Reports Suppress fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Annual Reports Suppress values.
    */
   public final String[] getAnnlRptsSuppressArray()
   {
      return _AnnlRptsSuppress;
   }
    
   /**
    * Gets the Annual Reports Waive field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Annual Reports Waive or null.
    */
   public final String getAnnlRptsWaive( int index )
   {
      return _AnnlRptsWaive[index];
   }
    
   /**
    * Gets the Annual Reports Waive field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Annual Reports Waive or the specified default value.
    */
   public final String getAnnlRptsWaive( int index, String defaultValue )
   {
      return _AnnlRptsWaive[index] == null ? defaultValue : _AnnlRptsWaive[index];
   }
    
   /**
    * Gets the array of Annual Reports Waive fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Annual Reports Waive values.
    */
   public final String[] getAnnlRptsWaiveArray()
   {
      return _AnnlRptsWaive;
   }
    
   /**
    * Gets the Annual Reports Mail field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Annual Reports Mail or null.
    */
   public final String getAnnlRptsMail( int index )
   {
      return _AnnlRptsMail[index];
   }
    
   /**
    * Gets the Annual Reports Mail field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Annual Reports Mail or the specified default value.
    */
   public final String getAnnlRptsMail( int index, String defaultValue )
   {
      return _AnnlRptsMail[index] == null ? defaultValue : _AnnlRptsMail[index];
   }
    
   /**
    * Gets the array of Annual Reports Mail fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Annual Reports Mail values.
    */
   public final String[] getAnnlRptsMailArray()
   {
      return _AnnlRptsMail;
   }
    
   /**
    * Gets the Annual Reports Fax field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Annual Reports Fax or null.
    */
   public final String getAnnlRptsFax( int index )
   {
      return _AnnlRptsFax[index];
   }
    
   /**
    * Gets the Annual Reports Fax field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Annual Reports Fax or the specified default value.
    */
   public final String getAnnlRptsFax( int index, String defaultValue )
   {
      return _AnnlRptsFax[index] == null ? defaultValue : _AnnlRptsFax[index];
   }
    
   /**
    * Gets the array of Annual Reports Fax fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Annual Reports Fax values.
    */
   public final String[] getAnnlRptsFaxArray()
   {
      return _AnnlRptsFax;
   }
    
   /**
    * Gets the Annual Reports CD field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Annual Reports CD or null.
    */
   public final String getAnnlRptsCd( int index )
   {
      return _AnnlRptsCd[index];
   }
    
   /**
    * Gets the Annual Reports CD field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Annual Reports CD or the specified default value.
    */
   public final String getAnnlRptsCd( int index, String defaultValue )
   {
      return _AnnlRptsCd[index] == null ? defaultValue : _AnnlRptsCd[index];
   }
    
   /**
    * Gets the array of Annual Reports CD fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Annual Reports CD values.
    */
   public final String[] getAnnlRptsCdArray()
   {
      return _AnnlRptsCd;
   }
    
   /**
    * Gets the Annual Reports Email field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Annual Reports Email or null.
    */
   public final String getAnnlRptsEmail( int index )
   {
      return _AnnlRptsEmail[index];
   }
    
   /**
    * Gets the Annual Reports Email field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Annual Reports Email or the specified default value.
    */
   public final String getAnnlRptsEmail( int index, String defaultValue )
   {
      return _AnnlRptsEmail[index] == null ? defaultValue : _AnnlRptsEmail[index];
   }
    
   /**
    * Gets the array of Annual Reports Email fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Annual Reports Email values.
    */
   public final String[] getAnnlRptsEmailArray()
   {
      return _AnnlRptsEmail;
   }
    
   /**
    * Gets the Prosp Suppress field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Prosp Suppress or null.
    */
   public final String getProspSuppress( int index )
   {
      return _ProspSuppress[index];
   }
    
   /**
    * Gets the Prosp Suppress field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Prosp Suppress or the specified default value.
    */
   public final String getProspSuppress( int index, String defaultValue )
   {
      return _ProspSuppress[index] == null ? defaultValue : _ProspSuppress[index];
   }
    
   /**
    * Gets the array of Prosp Suppress fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Prosp Suppress values.
    */
   public final String[] getProspSuppressArray()
   {
      return _ProspSuppress;
   }
    
   /**
    * Gets the Prosp Waive field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Prosp Waive or null.
    */
   public final String getProspWaive( int index )
   {
      return _ProspWaive[index];
   }
    
   /**
    * Gets the Prosp Waive field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Prosp Waive or the specified default value.
    */
   public final String getProspWaive( int index, String defaultValue )
   {
      return _ProspWaive[index] == null ? defaultValue : _ProspWaive[index];
   }
    
   /**
    * Gets the array of Prosp Waive fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Prosp Waive values.
    */
   public final String[] getProspWaiveArray()
   {
      return _ProspWaive;
   }
    
   /**
    * Gets the Prosp Mail field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Prosp Mail or null.
    */
   public final String getProspMail( int index )
   {
      return _ProspMail[index];
   }
    
   /**
    * Gets the Prosp Mail field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Prosp Mail or the specified default value.
    */
   public final String getProspMail( int index, String defaultValue )
   {
      return _ProspMail[index] == null ? defaultValue : _ProspMail[index];
   }
    
   /**
    * Gets the array of Prosp Mail fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Prosp Mail values.
    */
   public final String[] getProspMailArray()
   {
      return _ProspMail;
   }
    
   /**
    * Gets the Prosp Fax field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Prosp Fax or null.
    */
   public final String getProspFax( int index )
   {
      return _ProspFax[index];
   }
    
   /**
    * Gets the Prosp Fax field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Prosp Fax or the specified default value.
    */
   public final String getProspFax( int index, String defaultValue )
   {
      return _ProspFax[index] == null ? defaultValue : _ProspFax[index];
   }
    
   /**
    * Gets the array of Prosp Fax fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Prosp Fax values.
    */
   public final String[] getProspFaxArray()
   {
      return _ProspFax;
   }
    
   /**
    * Gets the Prosp CD field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Prosp CD or null.
    */
   public final String getProspCD( int index )
   {
      return _ProspCD[index];
   }
    
   /**
    * Gets the Prosp CD field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Prosp CD or the specified default value.
    */
   public final String getProspCD( int index, String defaultValue )
   {
      return _ProspCD[index] == null ? defaultValue : _ProspCD[index];
   }
    
   /**
    * Gets the array of Prosp CD fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Prosp CD values.
    */
   public final String[] getProspCDArray()
   {
      return _ProspCD;
   }
    
   /**
    * Gets the Prosp Email field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Prosp Email or null.
    */
   public final String getProspEmail( int index )
   {
      return _ProspEmail[index];
   }
    
   /**
    * Gets the Prosp Email field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Prosp Email or the specified default value.
    */
   public final String getProspEmail( int index, String defaultValue )
   {
      return _ProspEmail[index] == null ? defaultValue : _ProspEmail[index];
   }
    
   /**
    * Gets the array of Prosp Email fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Prosp Email values.
    */
   public final String[] getProspEmailArray()
   {
      return _ProspEmail;
   }
    
   /**
    * Gets the Ben Suppress field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Ben Suppress or null.
    */
   public final String getBenSuppress( int index )
   {
      return _BenSuppress[index];
   }
    
   /**
    * Gets the Ben Suppress field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Ben Suppress or the specified default value.
    */
   public final String getBenSuppress( int index, String defaultValue )
   {
      return _BenSuppress[index] == null ? defaultValue : _BenSuppress[index];
   }
    
   /**
    * Gets the array of Ben Suppress fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Ben Suppress values.
    */
   public final String[] getBenSuppressArray()
   {
      return _BenSuppress;
   }
    
   /**
    * Gets the Ben Waive field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Ben Waive or null.
    */
   public final String getBenWaive( int index )
   {
      return _BenWaive[index];
   }
    
   /**
    * Gets the Ben Waive field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Ben Waive or the specified default value.
    */
   public final String getBenWaive( int index, String defaultValue )
   {
      return _BenWaive[index] == null ? defaultValue : _BenWaive[index];
   }
    
   /**
    * Gets the array of Ben Waive fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Ben Waive values.
    */
   public final String[] getBenWaiveArray()
   {
      return _BenWaive;
   }
    
   /**
    * Gets the Ben Mail field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Ben Mail or null.
    */
   public final String getBenMail( int index )
   {
      return _BenMail[index];
   }
    
   /**
    * Gets the Ben Mail field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Ben Mail or the specified default value.
    */
   public final String getBenMail( int index, String defaultValue )
   {
      return _BenMail[index] == null ? defaultValue : _BenMail[index];
   }
    
   /**
    * Gets the array of Ben Mail fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Ben Mail values.
    */
   public final String[] getBenMailArray()
   {
      return _BenMail;
   }
    
   /**
    * Gets the Ben Fax field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Ben Fax or null.
    */
   public final String getBenFax( int index )
   {
      return _BenFax[index];
   }
    
   /**
    * Gets the Ben Fax field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Ben Fax or the specified default value.
    */
   public final String getBenFax( int index, String defaultValue )
   {
      return _BenFax[index] == null ? defaultValue : _BenFax[index];
   }
    
   /**
    * Gets the array of Ben Fax fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Ben Fax values.
    */
   public final String[] getBenFaxArray()
   {
      return _BenFax;
   }
    
   /**
    * Gets the Ben CD field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Ben CD or null.
    */
   public final String getBenCD( int index )
   {
      return _BenCD[index];
   }
    
   /**
    * Gets the Ben CD field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Ben CD or the specified default value.
    */
   public final String getBenCD( int index, String defaultValue )
   {
      return _BenCD[index] == null ? defaultValue : _BenCD[index];
   }
    
   /**
    * Gets the array of Ben CD fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Ben CD values.
    */
   public final String[] getBenCDArray()
   {
      return _BenCD;
   }
    
   /**
    * Gets the Ben Email field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Ben Email or null.
    */
   public final String getBenEmail( int index )
   {
      return _BenEmail[index];
   }
    
   /**
    * Gets the Ben Email field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Ben Email or the specified default value.
    */
   public final String getBenEmail( int index, String defaultValue )
   {
      return _BenEmail[index] == null ? defaultValue : _BenEmail[index];
   }
    
   /**
    * Gets the array of Ben Email fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Ben Email values.
    */
   public final String[] getBenEmailArray()
   {
      return _BenEmail;
   }
    
   /**
    * Gets the Stmt Suppress field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stmt Suppress or null.
    */
   public final String getStmtSuppress( int index )
   {
      return _StmtSuppress[index];
   }
    
   /**
    * Gets the Stmt Suppress field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stmt Suppress or the specified default value.
    */
   public final String getStmtSuppress( int index, String defaultValue )
   {
      return _StmtSuppress[index] == null ? defaultValue : _StmtSuppress[index];
   }
    
   /**
    * Gets the array of Stmt Suppress fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stmt Suppress values.
    */
   public final String[] getStmtSuppressArray()
   {
      return _StmtSuppress;
   }
    
   /**
    * Gets the Stmt Waive field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stmt Waive or null.
    */
   public final String getStmtWaive( int index )
   {
      return _StmtWaive[index];
   }
    
   /**
    * Gets the Stmt Waive field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stmt Waive or the specified default value.
    */
   public final String getStmtWaive( int index, String defaultValue )
   {
      return _StmtWaive[index] == null ? defaultValue : _StmtWaive[index];
   }
    
   /**
    * Gets the array of Stmt Waive fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stmt Waive values.
    */
   public final String[] getStmtWaiveArray()
   {
      return _StmtWaive;
   }
    
   /**
    * Gets the Stmt Mail field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stmt Mail or null.
    */
   public final String getStmtMail( int index )
   {
      return _StmtMail[index];
   }
    
   /**
    * Gets the Stmt Mail field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stmt Mail or the specified default value.
    */
   public final String getStmtMail( int index, String defaultValue )
   {
      return _StmtMail[index] == null ? defaultValue : _StmtMail[index];
   }
    
   /**
    * Gets the array of Stmt Mail fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stmt Mail values.
    */
   public final String[] getStmtMailArray()
   {
      return _StmtMail;
   }
    
   /**
    * Gets the Stmt Fax field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stmt Fax or null.
    */
   public final String getStmtFax( int index )
   {
      return _StmtFax[index];
   }
    
   /**
    * Gets the Stmt Fax field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stmt Fax or the specified default value.
    */
   public final String getStmtFax( int index, String defaultValue )
   {
      return _StmtFax[index] == null ? defaultValue : _StmtFax[index];
   }
    
   /**
    * Gets the array of Stmt Fax fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stmt Fax values.
    */
   public final String[] getStmtFaxArray()
   {
      return _StmtFax;
   }
    
   /**
    * Gets the Stmt CD field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stmt CD or null.
    */
   public final String getStmtCD( int index )
   {
      return _StmtCD[index];
   }
    
   /**
    * Gets the Stmt CD field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stmt CD or the specified default value.
    */
   public final String getStmtCD( int index, String defaultValue )
   {
      return _StmtCD[index] == null ? defaultValue : _StmtCD[index];
   }
    
   /**
    * Gets the array of Stmt CD fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stmt CD values.
    */
   public final String[] getStmtCDArray()
   {
      return _StmtCD;
   }
    
   /**
    * Gets the Stmt Email field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stmt Email or null.
    */
   public final String getStmtEmail( int index )
   {
      return _StmtEmail[index];
   }
    
   /**
    * Gets the Stmt Email field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stmt Email or the specified default value.
    */
   public final String getStmtEmail( int index, String defaultValue )
   {
      return _StmtEmail[index] == null ? defaultValue : _StmtEmail[index];
   }
    
   /**
    * Gets the array of Stmt Email fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stmt Email values.
    */
   public final String[] getStmtEmailArray()
   {
      return _StmtEmail;
   }
    
   /**
    * Gets the Dup Stmt Suppress field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Dup Stmt Suppress or null.
    */
   public final String getDupStmtSuppress( int index )
   {
      return _DupStmtSuppress[index];
   }
    
   /**
    * Gets the Dup Stmt Suppress field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Dup Stmt Suppress or the specified default value.
    */
   public final String getDupStmtSuppress( int index, String defaultValue )
   {
      return _DupStmtSuppress[index] == null ? defaultValue : _DupStmtSuppress[index];
   }
    
   /**
    * Gets the array of Dup Stmt Suppress fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Dup Stmt Suppress values.
    */
   public final String[] getDupStmtSuppressArray()
   {
      return _DupStmtSuppress;
   }
    
   /**
    * Gets the Dup Stmt Waive field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Dup Stmt Waive or null.
    */
   public final String getDupStmtWaive( int index )
   {
      return _DupStmtWaive[index];
   }
    
   /**
    * Gets the Dup Stmt Waive field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Dup Stmt Waive or the specified default value.
    */
   public final String getDupStmtWaive( int index, String defaultValue )
   {
      return _DupStmtWaive[index] == null ? defaultValue : _DupStmtWaive[index];
   }
    
   /**
    * Gets the array of Dup Stmt Waive fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Dup Stmt Waive values.
    */
   public final String[] getDupStmtWaiveArray()
   {
      return _DupStmtWaive;
   }
    
   /**
    * Gets the Dup Stmt Mail field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Dup Stmt Mail or null.
    */
   public final String getDupStmtMail( int index )
   {
      return _DupStmtMail[index];
   }
    
   /**
    * Gets the Dup Stmt Mail field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Dup Stmt Mail or the specified default value.
    */
   public final String getDupStmtMail( int index, String defaultValue )
   {
      return _DupStmtMail[index] == null ? defaultValue : _DupStmtMail[index];
   }
    
   /**
    * Gets the array of Dup Stmt Mail fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Dup Stmt Mail values.
    */
   public final String[] getDupStmtMailArray()
   {
      return _DupStmtMail;
   }
    
   /**
    * Gets the Dup Stmt Fax field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Dup Stmt Fax or null.
    */
   public final String getDupStmtFax( int index )
   {
      return _DupStmtFax[index];
   }
    
   /**
    * Gets the Dup Stmt Fax field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Dup Stmt Fax or the specified default value.
    */
   public final String getDupStmtFax( int index, String defaultValue )
   {
      return _DupStmtFax[index] == null ? defaultValue : _DupStmtFax[index];
   }
    
   /**
    * Gets the array of Dup Stmt Fax fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Dup Stmt Fax values.
    */
   public final String[] getDupStmtFaxArray()
   {
      return _DupStmtFax;
   }
    
   /**
    * Gets the Dup Stmt CD field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Dup Stmt CD or null.
    */
   public final String getDupStmtCD( int index )
   {
      return _DupStmtCD[index];
   }
    
   /**
    * Gets the Dup Stmt CD field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Dup Stmt CD or the specified default value.
    */
   public final String getDupStmtCD( int index, String defaultValue )
   {
      return _DupStmtCD[index] == null ? defaultValue : _DupStmtCD[index];
   }
    
   /**
    * Gets the array of Dup Stmt CD fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Dup Stmt CD values.
    */
   public final String[] getDupStmtCDArray()
   {
      return _DupStmtCD;
   }
    
   /**
    * Gets the Dup Stmt Email field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Dup Stmt Email or null.
    */
   public final String getDupStmtEmail( int index )
   {
      return _DupStmtEmail[index];
   }
    
   /**
    * Gets the Dup Stmt Email field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Dup Stmt Email or the specified default value.
    */
   public final String getDupStmtEmail( int index, String defaultValue )
   {
      return _DupStmtEmail[index] == null ? defaultValue : _DupStmtEmail[index];
   }
    
   /**
    * Gets the array of Dup Stmt Email fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Dup Stmt Email values.
    */
   public final String[] getDupStmtEmailArray()
   {
      return _DupStmtEmail;
   }
    
   /**
    * Gets the NF Conf Suppress field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the NF Conf Suppress or null.
    */
   public final String getNFConfSuppress( int index )
   {
      return _NFConfSuppress[index];
   }
    
   /**
    * Gets the NF Conf Suppress field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the NF Conf Suppress or the specified default value.
    */
   public final String getNFConfSuppress( int index, String defaultValue )
   {
      return _NFConfSuppress[index] == null ? defaultValue : _NFConfSuppress[index];
   }
    
   /**
    * Gets the array of NF Conf Suppress fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of NF Conf Suppress values.
    */
   public final String[] getNFConfSuppressArray()
   {
      return _NFConfSuppress;
   }
    
   /**
    * Gets the NF Conf Waive field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the NF Conf Waive or null.
    */
   public final String getNFConfWaive( int index )
   {
      return _NFConfWaive[index];
   }
    
   /**
    * Gets the NF Conf Waive field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the NF Conf Waive or the specified default value.
    */
   public final String getNFConfWaive( int index, String defaultValue )
   {
      return _NFConfWaive[index] == null ? defaultValue : _NFConfWaive[index];
   }
    
   /**
    * Gets the array of NF Conf Waive fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of NF Conf Waive values.
    */
   public final String[] getNFConfWaiveArray()
   {
      return _NFConfWaive;
   }
    
   /**
    * Gets the NF Conf Mail field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the NF Conf Mail or null.
    */
   public final String getNFConfMail( int index )
   {
      return _NFConfMail[index];
   }
    
   /**
    * Gets the NF Conf Mail field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the NF Conf Mail or the specified default value.
    */
   public final String getNFConfMail( int index, String defaultValue )
   {
      return _NFConfMail[index] == null ? defaultValue : _NFConfMail[index];
   }
    
   /**
    * Gets the array of NF Conf Mail fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of NF Conf Mail values.
    */
   public final String[] getNFConfMailArray()
   {
      return _NFConfMail;
   }
    
   /**
    * Gets the NF Conf Fax field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the NF Conf Fax or null.
    */
   public final String getNFConfFax( int index )
   {
      return _NFConfFax[index];
   }
    
   /**
    * Gets the NF Conf Fax field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the NF Conf Fax or the specified default value.
    */
   public final String getNFConfFax( int index, String defaultValue )
   {
      return _NFConfFax[index] == null ? defaultValue : _NFConfFax[index];
   }
    
   /**
    * Gets the array of NF Conf Fax fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of NF Conf Fax values.
    */
   public final String[] getNFConfFaxArray()
   {
      return _NFConfFax;
   }
    
   /**
    * Gets the NF Conf CD field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the NF Conf CD or null.
    */
   public final String getNFConfCD( int index )
   {
      return _NFConfCD[index];
   }
    
   /**
    * Gets the NF Conf CD field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the NF Conf CD or the specified default value.
    */
   public final String getNFConfCD( int index, String defaultValue )
   {
      return _NFConfCD[index] == null ? defaultValue : _NFConfCD[index];
   }
    
   /**
    * Gets the array of NF Conf CD fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of NF Conf CD values.
    */
   public final String[] getNFConfCDArray()
   {
      return _NFConfCD;
   }
    
   /**
    * Gets the NF Conf Email field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the NF Conf Email or null.
    */
   public final String getNFConfEmail( int index )
   {
      return _NFConfEmail[index];
   }
    
   /**
    * Gets the NF Conf Email field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the NF Conf Email or the specified default value.
    */
   public final String getNFConfEmail( int index, String defaultValue )
   {
      return _NFConfEmail[index] == null ? defaultValue : _NFConfEmail[index];
   }
    
   /**
    * Gets the array of NF Conf Email fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of NF Conf Email values.
    */
   public final String[] getNFConfEmailArray()
   {
      return _NFConfEmail;
   }
    
   /**
    * Gets the Txn Conf Suppress field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Txn Conf Suppress or null.
    */
   public final String getTxnConfSuppress( int index )
   {
      return _TxnConfSuppress[index];
   }
    
   /**
    * Gets the Txn Conf Suppress field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Txn Conf Suppress or the specified default value.
    */
   public final String getTxnConfSuppress( int index, String defaultValue )
   {
      return _TxnConfSuppress[index] == null ? defaultValue : _TxnConfSuppress[index];
   }
    
   /**
    * Gets the array of Txn Conf Suppress fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Txn Conf Suppress values.
    */
   public final String[] getTxnConfSuppressArray()
   {
      return _TxnConfSuppress;
   }
    
   /**
    * Gets the Txn Conf Waive field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Txn Conf Waive or null.
    */
   public final String getTxnConfWaive( int index )
   {
      return _TxnConfWaive[index];
   }
    
   /**
    * Gets the Txn Conf Waive field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Txn Conf Waive or the specified default value.
    */
   public final String getTxnConfWaive( int index, String defaultValue )
   {
      return _TxnConfWaive[index] == null ? defaultValue : _TxnConfWaive[index];
   }
    
   /**
    * Gets the array of Txn Conf Waive fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Txn Conf Waive values.
    */
   public final String[] getTxnConfWaiveArray()
   {
      return _TxnConfWaive;
   }
    
   /**
    * Gets the Txn Conf Mail field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Txn Conf Mail or null.
    */
   public final String getTxnConfMail( int index )
   {
      return _TxnConfMail[index];
   }
    
   /**
    * Gets the Txn Conf Mail field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Txn Conf Mail or the specified default value.
    */
   public final String getTxnConfMail( int index, String defaultValue )
   {
      return _TxnConfMail[index] == null ? defaultValue : _TxnConfMail[index];
   }
    
   /**
    * Gets the array of Txn Conf Mail fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Txn Conf Mail values.
    */
   public final String[] getTxnConfMailArray()
   {
      return _TxnConfMail;
   }
    
   /**
    * Gets the Txn Conf Fax field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Txn Conf Fax or null.
    */
   public final String getTxnConfFax( int index )
   {
      return _TxnConfFax[index];
   }
    
   /**
    * Gets the Txn Conf Fax field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Txn Conf Fax or the specified default value.
    */
   public final String getTxnConfFax( int index, String defaultValue )
   {
      return _TxnConfFax[index] == null ? defaultValue : _TxnConfFax[index];
   }
    
   /**
    * Gets the array of Txn Conf Fax fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Txn Conf Fax values.
    */
   public final String[] getTxnConfFaxArray()
   {
      return _TxnConfFax;
   }
    
   /**
    * Gets the Txn Conf CD field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Txn Conf CD or null.
    */
   public final String getTxnConfCD( int index )
   {
      return _TxnConfCD[index];
   }
    
   /**
    * Gets the Txn Conf CD field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Txn Conf CD or the specified default value.
    */
   public final String getTxnConfCD( int index, String defaultValue )
   {
      return _TxnConfCD[index] == null ? defaultValue : _TxnConfCD[index];
   }
    
   /**
    * Gets the array of Txn Conf CD fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Txn Conf CD values.
    */
   public final String[] getTxnConfCDArray()
   {
      return _TxnConfCD;
   }
    
   /**
    * Gets the Txn Conf Email field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Txn Conf Email or null.
    */
   public final String getTxnConfEmail( int index )
   {
      return _TxnConfEmail[index];
   }
    
   /**
    * Gets the Txn Conf Email field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Txn Conf Email or the specified default value.
    */
   public final String getTxnConfEmail( int index, String defaultValue )
   {
      return _TxnConfEmail[index] == null ? defaultValue : _TxnConfEmail[index];
   }
    
   /**
    * Gets the array of Txn Conf Email fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Txn Conf Email values.
    */
   public final String[] getTxnConfEmailArray()
   {
      return _TxnConfEmail;
   }
    
   /**
    * Gets the Dup Conf Suppress field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Dup Conf Suppress or null.
    */
   public final String getDupConfSuppress( int index )
   {
      return _DupConfSuppress[index];
   }
    
   /**
    * Gets the Dup Conf Suppress field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Dup Conf Suppress or the specified default value.
    */
   public final String getDupConfSuppress( int index, String defaultValue )
   {
      return _DupConfSuppress[index] == null ? defaultValue : _DupConfSuppress[index];
   }
    
   /**
    * Gets the array of Dup Conf Suppress fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Dup Conf Suppress values.
    */
   public final String[] getDupConfSuppressArray()
   {
      return _DupConfSuppress;
   }
    
   /**
    * Gets the Dup Conf Waive field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Dup Conf Waive or null.
    */
   public final String getDupConfWaive( int index )
   {
      return _DupConfWaive[index];
   }
    
   /**
    * Gets the Dup Conf Waive field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Dup Conf Waive or the specified default value.
    */
   public final String getDupConfWaive( int index, String defaultValue )
   {
      return _DupConfWaive[index] == null ? defaultValue : _DupConfWaive[index];
   }
    
   /**
    * Gets the array of Dup Conf Waive fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Dup Conf Waive values.
    */
   public final String[] getDupConfWaiveArray()
   {
      return _DupConfWaive;
   }
    
   /**
    * Gets the Dup Conf Mail field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Dup Conf Mail or null.
    */
   public final String getDupConfMail( int index )
   {
      return _DupConfMail[index];
   }
    
   /**
    * Gets the Dup Conf Mail field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Dup Conf Mail or the specified default value.
    */
   public final String getDupConfMail( int index, String defaultValue )
   {
      return _DupConfMail[index] == null ? defaultValue : _DupConfMail[index];
   }
    
   /**
    * Gets the array of Dup Conf Mail fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Dup Conf Mail values.
    */
   public final String[] getDupConfMailArray()
   {
      return _DupConfMail;
   }
    
   /**
    * Gets the Dup Conf Fax field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Dup Conf Fax or null.
    */
   public final String getDupConfFax( int index )
   {
      return _DupConfFax[index];
   }
    
   /**
    * Gets the Dup Conf Fax field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Dup Conf Fax or the specified default value.
    */
   public final String getDupConfFax( int index, String defaultValue )
   {
      return _DupConfFax[index] == null ? defaultValue : _DupConfFax[index];
   }
    
   /**
    * Gets the array of Dup Conf Fax fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Dup Conf Fax values.
    */
   public final String[] getDupConfFaxArray()
   {
      return _DupConfFax;
   }
    
   /**
    * Gets the Dup Conf CD field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Dup Conf CD or null.
    */
   public final String getDupConfCD( int index )
   {
      return _DupConfCD[index];
   }
    
   /**
    * Gets the Dup Conf CD field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Dup Conf CD or the specified default value.
    */
   public final String getDupConfCD( int index, String defaultValue )
   {
      return _DupConfCD[index] == null ? defaultValue : _DupConfCD[index];
   }
    
   /**
    * Gets the array of Dup Conf CD fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Dup Conf CD values.
    */
   public final String[] getDupConfCDArray()
   {
      return _DupConfCD;
   }
    
   /**
    * Gets the Dup Conf Email field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Dup Conf Email or null.
    */
   public final String getDupConfEmail( int index )
   {
      return _DupConfEmail[index];
   }
    
   /**
    * Gets the Dup Conf Email field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Dup Conf Email or the specified default value.
    */
   public final String getDupConfEmail( int index, String defaultValue )
   {
      return _DupConfEmail[index] == null ? defaultValue : _DupConfEmail[index];
   }
    
   /**
    * Gets the array of Dup Conf Email fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Dup Conf Email values.
    */
   public final String[] getDupConfEmailArray()
   {
      return _DupConfEmail;
   }
    
   /**
    * Gets the Semi Annual Report Suppress field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Semi Annual Report Suppress or null.
    */
   public final String getSmAnnlRptSuppress( int index )
   {
      return _SmAnnlRptSuppress[index];
   }
    
   /**
    * Gets the Semi Annual Report Suppress field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Semi Annual Report Suppress or the specified default value.
    */
   public final String getSmAnnlRptSuppress( int index, String defaultValue )
   {
      return _SmAnnlRptSuppress[index] == null ? defaultValue : _SmAnnlRptSuppress[index];
   }
    
   /**
    * Gets the array of Semi Annual Report Suppress fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Semi Annual Report Suppress values.
    */
   public final String[] getSmAnnlRptSuppressArray()
   {
      return _SmAnnlRptSuppress;
   }
    
   /**
    * Gets the Semi Annual Report Waive field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Semi Annual Report Waive or null.
    */
   public final String getSmAnnlRptWaive( int index )
   {
      return _SmAnnlRptWaive[index];
   }
    
   /**
    * Gets the Semi Annual Report Waive field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Semi Annual Report Waive or the specified default value.
    */
   public final String getSmAnnlRptWaive( int index, String defaultValue )
   {
      return _SmAnnlRptWaive[index] == null ? defaultValue : _SmAnnlRptWaive[index];
   }
    
   /**
    * Gets the array of Semi Annual Report Waive fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Semi Annual Report Waive values.
    */
   public final String[] getSmAnnlRptWaiveArray()
   {
      return _SmAnnlRptWaive;
   }
    
   /**
    * Gets the Semi Annual Report Mail field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Semi Annual Report Mail or null.
    */
   public final String getSmAnnlRptMail( int index )
   {
      return _SmAnnlRptMail[index];
   }
    
   /**
    * Gets the Semi Annual Report Mail field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Semi Annual Report Mail or the specified default value.
    */
   public final String getSmAnnlRptMail( int index, String defaultValue )
   {
      return _SmAnnlRptMail[index] == null ? defaultValue : _SmAnnlRptMail[index];
   }
    
   /**
    * Gets the array of Semi Annual Report Mail fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Semi Annual Report Mail values.
    */
   public final String[] getSmAnnlRptMailArray()
   {
      return _SmAnnlRptMail;
   }
    
   /**
    * Gets the Semi Annual Report Fax field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Semi Annual Report Fax or null.
    */
   public final String getSmAnnlRptFax( int index )
   {
      return _SmAnnlRptFax[index];
   }
    
   /**
    * Gets the Semi Annual Report Fax field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Semi Annual Report Fax or the specified default value.
    */
   public final String getSmAnnlRptFax( int index, String defaultValue )
   {
      return _SmAnnlRptFax[index] == null ? defaultValue : _SmAnnlRptFax[index];
   }
    
   /**
    * Gets the array of Semi Annual Report Fax fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Semi Annual Report Fax values.
    */
   public final String[] getSmAnnlRptFaxArray()
   {
      return _SmAnnlRptFax;
   }
    
   /**
    * Gets the Semi Annual Report CD field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Semi Annual Report CD or null.
    */
   public final String getSmAnnlRptCD( int index )
   {
      return _SmAnnlRptCD[index];
   }
    
   /**
    * Gets the Semi Annual Report CD field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Semi Annual Report CD or the specified default value.
    */
   public final String getSmAnnlRptCD( int index, String defaultValue )
   {
      return _SmAnnlRptCD[index] == null ? defaultValue : _SmAnnlRptCD[index];
   }
    
   /**
    * Gets the array of Semi Annual Report CD fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Semi Annual Report CD values.
    */
   public final String[] getSmAnnlRptCDArray()
   {
      return _SmAnnlRptCD;
   }
    
   /**
    * Gets the Semi Annual Report Email field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Semi Annual Report Email or null.
    */
   public final String getSmAnnlRptEmail( int index )
   {
      return _SmAnnlRptEmail[index];
   }
    
   /**
    * Gets the Semi Annual Report Email field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Semi Annual Report Email or the specified default value.
    */
   public final String getSmAnnlRptEmail( int index, String defaultValue )
   {
      return _SmAnnlRptEmail[index] == null ? defaultValue : _SmAnnlRptEmail[index];
   }
    
   /**
    * Gets the array of Semi Annual Report Email fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Semi Annual Report Email values.
    */
   public final String[] getSmAnnlRptEmailArray()
   {
      return _SmAnnlRptEmail;
   }
    
   /**
    * Gets the Semi Annual Report Address Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Semi Annual Report Address Code or null.
    */
   public final String getSmAnnlRptAddr( int index )
   {
      return _SmAnnlRptAddr[index];
   }
    
   /**
    * Gets the Semi Annual Report Address Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Semi Annual Report Address Code or the specified default value.
    */
   public final String getSmAnnlRptAddr( int index, String defaultValue )
   {
      return _SmAnnlRptAddr[index] == null ? defaultValue : _SmAnnlRptAddr[index];
   }
    
   /**
    * Gets the array of Semi Annual Report Address Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Semi Annual Report Address Code values.
    */
   public final String[] getSmAnnlRptAddrArray()
   {
      return _SmAnnlRptAddr;
   }
    
   /**
    * Gets the Semi Annual Report On Hold field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Semi Annual Report On Hold or null.
    */
   public final Boolean getSmAnnlRptHold( int index )
   {
      return _SmAnnlRptHold[index];
   }
    
   /**
    * Gets the Semi Annual Report On Hold field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Semi Annual Report On Hold or the specified default value.
    */
   public final boolean getSmAnnlRptHold( int index, boolean defaultValue )
   {
      return _SmAnnlRptHold[index] == null ? defaultValue : _SmAnnlRptHold[index].booleanValue();
   }
    
   /**
    * Gets the array of Semi Annual Report On Hold fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Semi Annual Report On Hold values.
    */
   public final Boolean[] getSmAnnlRptHoldArray()
   {
      return _SmAnnlRptHold;
   }
    
   /**
    * Gets the Tax E-Post field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax E-Post or null.
    */
   public final String getTaxEPost( int index )
   {
      return _TaxEPost[index];
   }
    
   /**
    * Gets the Tax E-Post field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax E-Post or the specified default value.
    */
   public final String getTaxEPost( int index, String defaultValue )
   {
      return _TaxEPost[index] == null ? defaultValue : _TaxEPost[index];
   }
    
   /**
    * Gets the array of Tax E-Post fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax E-Post values.
    */
   public final String[] getTaxEPostArray()
   {
      return _TaxEPost;
   }
    
   /**
    * Gets the Letter E-Post field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Letter E-Post or null.
    */
   public final String getLetEPost( int index )
   {
      return _LetEPost[index];
   }
    
   /**
    * Gets the Letter E-Post field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Letter E-Post or the specified default value.
    */
   public final String getLetEPost( int index, String defaultValue )
   {
      return _LetEPost[index] == null ? defaultValue : _LetEPost[index];
   }
    
   /**
    * Gets the array of Letter E-Post fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Letter E-Post values.
    */
   public final String[] getLetEPostArray()
   {
      return _LetEPost;
   }
    
   /**
    * Gets the Certificate E-Post field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Certificate E-Post or null.
    */
   public final String getCertEPost( int index )
   {
      return _CertEPost[index];
   }
    
   /**
    * Gets the Certificate E-Post field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Certificate E-Post or the specified default value.
    */
   public final String getCertEPost( int index, String defaultValue )
   {
      return _CertEPost[index] == null ? defaultValue : _CertEPost[index];
   }
    
   /**
    * Gets the array of Certificate E-Post fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Certificate E-Post values.
    */
   public final String[] getCertEPostArray()
   {
      return _CertEPost;
   }
    
   /**
    * Gets the Dividend Confirm EPost field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Dividend Confirm EPost or null.
    */
   public final String getDivConfEPost( int index )
   {
      return _DivConfEPost[index];
   }
    
   /**
    * Gets the Dividend Confirm EPost field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Dividend Confirm EPost or the specified default value.
    */
   public final String getDivConfEPost( int index, String defaultValue )
   {
      return _DivConfEPost[index] == null ? defaultValue : _DivConfEPost[index];
   }
    
   /**
    * Gets the array of Dividend Confirm EPost fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Dividend Confirm EPost values.
    */
   public final String[] getDivConfEPostArray()
   {
      return _DivConfEPost;
   }
    
   /**
    * Gets the Dividend Chq EPost field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Dividend Chq EPost or null.
    */
   public final String getDivChqEPost( int index )
   {
      return _DivChqEPost[index];
   }
    
   /**
    * Gets the Dividend Chq EPost field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Dividend Chq EPost or the specified default value.
    */
   public final String getDivChqEPost( int index, String defaultValue )
   {
      return _DivChqEPost[index] == null ? defaultValue : _DivChqEPost[index];
   }
    
   /**
    * Gets the array of Dividend Chq EPost fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Dividend Chq EPost values.
    */
   public final String[] getDivChqEPostArray()
   {
      return _DivChqEPost;
   }
    
   /**
    * Gets the Contribution EPost field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contribution EPost or null.
    */
   public final String getContrEPost( int index )
   {
      return _ContrEPost[index];
   }
    
   /**
    * Gets the Contribution EPost field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contribution EPost or the specified default value.
    */
   public final String getContrEPost( int index, String defaultValue )
   {
      return _ContrEPost[index] == null ? defaultValue : _ContrEPost[index];
   }
    
   /**
    * Gets the array of Contribution EPost fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contribution EPost values.
    */
   public final String[] getContrEPostArray()
   {
      return _ContrEPost;
   }
    
   /**
    * Gets the Registered Mail EPost field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Registered Mail EPost or null.
    */
   public final String getRegEPost( int index )
   {
      return _RegEPost[index];
   }
    
   /**
    * Gets the Registered Mail EPost field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Registered Mail EPost or the specified default value.
    */
   public final String getRegEPost( int index, String defaultValue )
   {
      return _RegEPost[index] == null ? defaultValue : _RegEPost[index];
   }
    
   /**
    * Gets the array of Registered Mail EPost fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Registered Mail EPost values.
    */
   public final String[] getRegEPostArray()
   {
      return _RegEPost;
   }
    
   /**
    * Gets the Annual Reports EPost field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Annual Reports EPost or null.
    */
   public final String getAnnlRptsEPost( int index )
   {
      return _AnnlRptsEPost[index];
   }
    
   /**
    * Gets the Annual Reports EPost field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Annual Reports EPost or the specified default value.
    */
   public final String getAnnlRptsEPost( int index, String defaultValue )
   {
      return _AnnlRptsEPost[index] == null ? defaultValue : _AnnlRptsEPost[index];
   }
    
   /**
    * Gets the array of Annual Reports EPost fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Annual Reports EPost values.
    */
   public final String[] getAnnlRptsEPostArray()
   {
      return _AnnlRptsEPost;
   }
    
   /**
    * Gets the Prospectus EPost field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Prospectus EPost or null.
    */
   public final String getProspEPost( int index )
   {
      return _ProspEPost[index];
   }
    
   /**
    * Gets the Prospectus EPost field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Prospectus EPost or the specified default value.
    */
   public final String getProspEPost( int index, String defaultValue )
   {
      return _ProspEPost[index] == null ? defaultValue : _ProspEPost[index];
   }
    
   /**
    * Gets the array of Prospectus EPost fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Prospectus EPost values.
    */
   public final String[] getProspEPostArray()
   {
      return _ProspEPost;
   }
    
   /**
    * Gets the Beneficiary EPost field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Beneficiary EPost or null.
    */
   public final String getBenEPost( int index )
   {
      return _BenEPost[index];
   }
    
   /**
    * Gets the Beneficiary EPost field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Beneficiary EPost or the specified default value.
    */
   public final String getBenEPost( int index, String defaultValue )
   {
      return _BenEPost[index] == null ? defaultValue : _BenEPost[index];
   }
    
   /**
    * Gets the array of Beneficiary EPost fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Beneficiary EPost values.
    */
   public final String[] getBenEPostArray()
   {
      return _BenEPost;
   }
    
   /**
    * Gets the Statement EPost field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Statement EPost or null.
    */
   public final String getStmtEPost( int index )
   {
      return _StmtEPost[index];
   }
    
   /**
    * Gets the Statement EPost field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Statement EPost or the specified default value.
    */
   public final String getStmtEPost( int index, String defaultValue )
   {
      return _StmtEPost[index] == null ? defaultValue : _StmtEPost[index];
   }
    
   /**
    * Gets the array of Statement EPost fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Statement EPost values.
    */
   public final String[] getStmtEPostArray()
   {
      return _StmtEPost;
   }
    
   /**
    * Gets the Duplicate Statement EPost field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Duplicate Statement EPost or null.
    */
   public final String getDulStmtEPost( int index )
   {
      return _DulStmtEPost[index];
   }
    
   /**
    * Gets the Duplicate Statement EPost field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Duplicate Statement EPost or the specified default value.
    */
   public final String getDulStmtEPost( int index, String defaultValue )
   {
      return _DulStmtEPost[index] == null ? defaultValue : _DulStmtEPost[index];
   }
    
   /**
    * Gets the array of Duplicate Statement EPost fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Duplicate Statement EPost values.
    */
   public final String[] getDulStmtEPostArray()
   {
      return _DulStmtEPost;
   }
    
   /**
    * Gets the NF Confirm EPost field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the NF Confirm EPost or null.
    */
   public final String getNFConfEPost( int index )
   {
      return _NFConfEPost[index];
   }
    
   /**
    * Gets the NF Confirm EPost field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the NF Confirm EPost or the specified default value.
    */
   public final String getNFConfEPost( int index, String defaultValue )
   {
      return _NFConfEPost[index] == null ? defaultValue : _NFConfEPost[index];
   }
    
   /**
    * Gets the array of NF Confirm EPost fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of NF Confirm EPost values.
    */
   public final String[] getNFConfEPostArray()
   {
      return _NFConfEPost;
   }
    
   /**
    * Gets the Txn Confirm EPost field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Txn Confirm EPost or null.
    */
   public final String getTxnConfEPost( int index )
   {
      return _TxnConfEPost[index];
   }
    
   /**
    * Gets the Txn Confirm EPost field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Txn Confirm EPost or the specified default value.
    */
   public final String getTxnConfEPost( int index, String defaultValue )
   {
      return _TxnConfEPost[index] == null ? defaultValue : _TxnConfEPost[index];
   }
    
   /**
    * Gets the array of Txn Confirm EPost fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Txn Confirm EPost values.
    */
   public final String[] getTxnConfEPostArray()
   {
      return _TxnConfEPost;
   }
    
   /**
    * Gets the Duplicate Confirm EPost field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Duplicate Confirm EPost or null.
    */
   public final String getDupConfEPost( int index )
   {
      return _DupConfEPost[index];
   }
    
   /**
    * Gets the Duplicate Confirm EPost field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Duplicate Confirm EPost or the specified default value.
    */
   public final String getDupConfEPost( int index, String defaultValue )
   {
      return _DupConfEPost[index] == null ? defaultValue : _DupConfEPost[index];
   }
    
   /**
    * Gets the array of Duplicate Confirm EPost fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Duplicate Confirm EPost values.
    */
   public final String[] getDupConfEPostArray()
   {
      return _DupConfEPost;
   }
    
   /**
    * Gets the Semi Annual Report EPost field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Semi Annual Report EPost or null.
    */
   public final String getSmAnnlRptEPost( int index )
   {
      return _SmAnnlRptEPost[index];
   }
    
   /**
    * Gets the Semi Annual Report EPost field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Semi Annual Report EPost or the specified default value.
    */
   public final String getSmAnnlRptEPost( int index, String defaultValue )
   {
      return _SmAnnlRptEPost[index] == null ? defaultValue : _SmAnnlRptEPost[index];
   }
    
   /**
    * Gets the array of Semi Annual Report EPost fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Semi Annual Report EPost values.
    */
   public final String[] getSmAnnlRptEPostArray()
   {
      return _SmAnnlRptEPost;
   }
    
   /**
    * Gets the Contribution Receipt Suppress field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contribution Receipt Suppress or null.
    */
   public final String getContrRSuppress( int index )
   {
      return _ContrRSuppress[index];
   }
    
   /**
    * Gets the Contribution Receipt Suppress field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contribution Receipt Suppress or the specified default value.
    */
   public final String getContrRSuppress( int index, String defaultValue )
   {
      return _ContrRSuppress[index] == null ? defaultValue : _ContrRSuppress[index];
   }
    
   /**
    * Gets the array of Contribution Receipt Suppress fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contribution Receipt Suppress values.
    */
   public final String[] getContrRSuppressArray()
   {
      return _ContrRSuppress;
   }
    
   /**
    * Gets the Contribution Receipt Waive field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contribution Receipt Waive or null.
    */
   public final String getContrRWaive( int index )
   {
      return _ContrRWaive[index];
   }
    
   /**
    * Gets the Contribution Receipt Waive field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contribution Receipt Waive or the specified default value.
    */
   public final String getContrRWaive( int index, String defaultValue )
   {
      return _ContrRWaive[index] == null ? defaultValue : _ContrRWaive[index];
   }
    
   /**
    * Gets the array of Contribution Receipt Waive fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contribution Receipt Waive values.
    */
   public final String[] getContrRWaiveArray()
   {
      return _ContrRWaive;
   }
    
   /**
    * Gets the Contribution Receipt Mail field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contribution Receipt Mail or null.
    */
   public final String getContrRMail( int index )
   {
      return _ContrRMail[index];
   }
    
   /**
    * Gets the Contribution Receipt Mail field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contribution Receipt Mail or the specified default value.
    */
   public final String getContrRMail( int index, String defaultValue )
   {
      return _ContrRMail[index] == null ? defaultValue : _ContrRMail[index];
   }
    
   /**
    * Gets the array of Contribution Receipt Mail fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contribution Receipt Mail values.
    */
   public final String[] getContrRMailArray()
   {
      return _ContrRMail;
   }
    
   /**
    * Gets the Contribution Receipt Fax field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contribution Receipt Fax or null.
    */
   public final String getContrRFax( int index )
   {
      return _ContrRFax[index];
   }
    
   /**
    * Gets the Contribution Receipt Fax field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contribution Receipt Fax or the specified default value.
    */
   public final String getContrRFax( int index, String defaultValue )
   {
      return _ContrRFax[index] == null ? defaultValue : _ContrRFax[index];
   }
    
   /**
    * Gets the array of Contribution Receipt Fax fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contribution Receipt Fax values.
    */
   public final String[] getContrRFaxArray()
   {
      return _ContrRFax;
   }
    
   /**
    * Gets the Contribution Receipt CD field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contribution Receipt CD or null.
    */
   public final String getContrRCD( int index )
   {
      return _ContrRCD[index];
   }
    
   /**
    * Gets the Contribution Receipt CD field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contribution Receipt CD or the specified default value.
    */
   public final String getContrRCD( int index, String defaultValue )
   {
      return _ContrRCD[index] == null ? defaultValue : _ContrRCD[index];
   }
    
   /**
    * Gets the array of Contribution Receipt CD fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contribution Receipt CD values.
    */
   public final String[] getContrRCDArray()
   {
      return _ContrRCD;
   }
    
   /**
    * Gets the Contribution Receipt EMail field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contribution Receipt EMail or null.
    */
   public final String getContrREmail( int index )
   {
      return _ContrREmail[index];
   }
    
   /**
    * Gets the Contribution Receipt EMail field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contribution Receipt EMail or the specified default value.
    */
   public final String getContrREmail( int index, String defaultValue )
   {
      return _ContrREmail[index] == null ? defaultValue : _ContrREmail[index];
   }
    
   /**
    * Gets the array of Contribution Receipt EMail fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contribution Receipt EMail values.
    */
   public final String[] getContrREmailArray()
   {
      return _ContrREmail;
   }
    
   /**
    * Gets the Contribution Receipt EPost field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contribution Receipt EPost or null.
    */
   public final String getContrREPost( int index )
   {
      return _ContrREPost[index];
   }
    
   /**
    * Gets the Contribution Receipt EPost field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contribution Receipt EPost or the specified default value.
    */
   public final String getContrREPost( int index, String defaultValue )
   {
      return _ContrREPost[index] == null ? defaultValue : _ContrREPost[index];
   }
    
   /**
    * Gets the array of Contribution Receipt EPost fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contribution Receipt EPost values.
    */
   public final String[] getContrREPostArray()
   {
      return _ContrREPost;
   }
    
   /**
    * Gets the Contribution Receipt Address Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contribution Receipt Address Code or null.
    */
   public final String getContrRAddr( int index )
   {
      return _ContrRAddr[index];
   }
    
   /**
    * Gets the Contribution Receipt Address Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contribution Receipt Address Code or the specified default value.
    */
   public final String getContrRAddr( int index, String defaultValue )
   {
      return _ContrRAddr[index] == null ? defaultValue : _ContrRAddr[index];
   }
    
   /**
    * Gets the array of Contribution Receipt Address Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contribution Receipt Address Code values.
    */
   public final String[] getContrRAddrArray()
   {
      return _ContrRAddr;
   }
    
   /**
    * Gets the Contribution Receipt On Hold field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contribution Receipt On Hold or null.
    */
   public final Boolean getContrRHold( int index )
   {
      return _ContrRHold[index];
   }
    
   /**
    * Gets the Contribution Receipt On Hold field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contribution Receipt On Hold or the specified default value.
    */
   public final boolean getContrRHold( int index, boolean defaultValue )
   {
      return _ContrRHold[index] == null ? defaultValue : _ContrRHold[index].booleanValue();
   }
    
   /**
    * Gets the array of Contribution Receipt On Hold fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contribution Receipt On Hold values.
    */
   public final Boolean[] getContrRHoldArray()
   {
      return _ContrRHold;
   }
    
   /**
    * Gets the Semi-Annual MRFP Address Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Semi-Annual MRFP Address Code or null.
    */
   public final String getSmAnnlMRFPAddr( int index )
   {
      return _SmAnnlMRFPAddr[index];
   }
    
   /**
    * Gets the Semi-Annual MRFP Address Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Semi-Annual MRFP Address Code or the specified default value.
    */
   public final String getSmAnnlMRFPAddr( int index, String defaultValue )
   {
      return _SmAnnlMRFPAddr[index] == null ? defaultValue : _SmAnnlMRFPAddr[index];
   }
    
   /**
    * Gets the array of Semi-Annual MRFP Address Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Semi-Annual MRFP Address Code values.
    */
   public final String[] getSmAnnlMRFPAddrArray()
   {
      return _SmAnnlMRFPAddr;
   }
    
   /**
    * Gets the Semi-Annual MRFP Suppress field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Semi-Annual MRFP Suppress or null.
    */
   public final String getSmAnnlMRFPSuppress( int index )
   {
      return _SmAnnlMRFPSuppress[index];
   }
    
   /**
    * Gets the Semi-Annual MRFP Suppress field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Semi-Annual MRFP Suppress or the specified default value.
    */
   public final String getSmAnnlMRFPSuppress( int index, String defaultValue )
   {
      return _SmAnnlMRFPSuppress[index] == null ? defaultValue : _SmAnnlMRFPSuppress[index];
   }
    
   /**
    * Gets the array of Semi-Annual MRFP Suppress fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Semi-Annual MRFP Suppress values.
    */
   public final String[] getSmAnnlMRFPSuppressArray()
   {
      return _SmAnnlMRFPSuppress;
   }
    
   /**
    * Gets the Semi-Annual MRFP Waive field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Semi-Annual MRFP Waive or null.
    */
   public final String getSmAnnlMRFPWaive( int index )
   {
      return _SmAnnlMRFPWaive[index];
   }
    
   /**
    * Gets the Semi-Annual MRFP Waive field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Semi-Annual MRFP Waive or the specified default value.
    */
   public final String getSmAnnlMRFPWaive( int index, String defaultValue )
   {
      return _SmAnnlMRFPWaive[index] == null ? defaultValue : _SmAnnlMRFPWaive[index];
   }
    
   /**
    * Gets the array of Semi-Annual MRFP Waive fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Semi-Annual MRFP Waive values.
    */
   public final String[] getSmAnnlMRFPWaiveArray()
   {
      return _SmAnnlMRFPWaive;
   }
    
   /**
    * Gets the Semi-Annual MRFP Hold field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Semi-Annual MRFP Hold or null.
    */
   public final Boolean getSmAnnlMRFPHold( int index )
   {
      return _SmAnnlMRFPHold[index];
   }
    
   /**
    * Gets the Semi-Annual MRFP Hold field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Semi-Annual MRFP Hold or the specified default value.
    */
   public final boolean getSmAnnlMRFPHold( int index, boolean defaultValue )
   {
      return _SmAnnlMRFPHold[index] == null ? defaultValue : _SmAnnlMRFPHold[index].booleanValue();
   }
    
   /**
    * Gets the array of Semi-Annual MRFP Hold fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Semi-Annual MRFP Hold values.
    */
   public final Boolean[] getSmAnnlMRFPHoldArray()
   {
      return _SmAnnlMRFPHold;
   }
    
   /**
    * Gets the Semi-Annual MRFP Mail field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Semi-Annual MRFP Mail or null.
    */
   public final String getSmAnnlMRFPMail( int index )
   {
      return _SmAnnlMRFPMail[index];
   }
    
   /**
    * Gets the Semi-Annual MRFP Mail field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Semi-Annual MRFP Mail or the specified default value.
    */
   public final String getSmAnnlMRFPMail( int index, String defaultValue )
   {
      return _SmAnnlMRFPMail[index] == null ? defaultValue : _SmAnnlMRFPMail[index];
   }
    
   /**
    * Gets the array of Semi-Annual MRFP Mail fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Semi-Annual MRFP Mail values.
    */
   public final String[] getSmAnnlMRFPMailArray()
   {
      return _SmAnnlMRFPMail;
   }
    
   /**
    * Gets the Semi-Annual MRFP Fax field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Semi-Annual MRFP Fax or null.
    */
   public final String getSmAnnlMRFPFax( int index )
   {
      return _SmAnnlMRFPFax[index];
   }
    
   /**
    * Gets the Semi-Annual MRFP Fax field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Semi-Annual MRFP Fax or the specified default value.
    */
   public final String getSmAnnlMRFPFax( int index, String defaultValue )
   {
      return _SmAnnlMRFPFax[index] == null ? defaultValue : _SmAnnlMRFPFax[index];
   }
    
   /**
    * Gets the array of Semi-Annual MRFP Fax fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Semi-Annual MRFP Fax values.
    */
   public final String[] getSmAnnlMRFPFaxArray()
   {
      return _SmAnnlMRFPFax;
   }
    
   /**
    * Gets the Semi-Annual MRFP CD field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Semi-Annual MRFP CD or null.
    */
   public final String getSmAnnlMRFPCD( int index )
   {
      return _SmAnnlMRFPCD[index];
   }
    
   /**
    * Gets the Semi-Annual MRFP CD field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Semi-Annual MRFP CD or the specified default value.
    */
   public final String getSmAnnlMRFPCD( int index, String defaultValue )
   {
      return _SmAnnlMRFPCD[index] == null ? defaultValue : _SmAnnlMRFPCD[index];
   }
    
   /**
    * Gets the array of Semi-Annual MRFP CD fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Semi-Annual MRFP CD values.
    */
   public final String[] getSmAnnlMRFPCDArray()
   {
      return _SmAnnlMRFPCD;
   }
    
   /**
    * Gets the Semi-Annual MRFP Email field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Semi-Annual MRFP Email or null.
    */
   public final String getSmAnnlMRFPEmail( int index )
   {
      return _SmAnnlMRFPEmail[index];
   }
    
   /**
    * Gets the Semi-Annual MRFP Email field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Semi-Annual MRFP Email or the specified default value.
    */
   public final String getSmAnnlMRFPEmail( int index, String defaultValue )
   {
      return _SmAnnlMRFPEmail[index] == null ? defaultValue : _SmAnnlMRFPEmail[index];
   }
    
   /**
    * Gets the array of Semi-Annual MRFP Email fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Semi-Annual MRFP Email values.
    */
   public final String[] getSmAnnlMRFPEmailArray()
   {
      return _SmAnnlMRFPEmail;
   }
    
   /**
    * Gets the Semi-Annual MRFP ePost field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Semi-Annual MRFP ePost or null.
    */
   public final String getSmAnnlMRFPePost( int index )
   {
      return _SmAnnlMRFPePost[index];
   }
    
   /**
    * Gets the Semi-Annual MRFP ePost field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Semi-Annual MRFP ePost or the specified default value.
    */
   public final String getSmAnnlMRFPePost( int index, String defaultValue )
   {
      return _SmAnnlMRFPePost[index] == null ? defaultValue : _SmAnnlMRFPePost[index];
   }
    
   /**
    * Gets the array of Semi-Annual MRFP ePost fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Semi-Annual MRFP ePost values.
    */
   public final String[] getSmAnnlMRFPePostArray()
   {
      return _SmAnnlMRFPePost;
   }
    
   /**
    * Gets the Semi-Annual MRFP Authorization field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Semi-Annual MRFP Authorization or null.
    */
   public final String getSmAnnlMRFPAuth( int index )
   {
      return _SmAnnlMRFPAuth[index];
   }
    
   /**
    * Gets the Semi-Annual MRFP Authorization field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Semi-Annual MRFP Authorization or the specified default value.
    */
   public final String getSmAnnlMRFPAuth( int index, String defaultValue )
   {
      return _SmAnnlMRFPAuth[index] == null ? defaultValue : _SmAnnlMRFPAuth[index];
   }
    
   /**
    * Gets the array of Semi-Annual MRFP Authorization fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Semi-Annual MRFP Authorization values.
    */
   public final String[] getSmAnnlMRFPAuthArray()
   {
      return _SmAnnlMRFPAuth;
   }
    
   /**
    * Gets the Annual MRFP Address Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Annual MRFP Address Code or null.
    */
   public final String getAnnlMRFPAddr( int index )
   {
      return _AnnlMRFPAddr[index];
   }
    
   /**
    * Gets the Annual MRFP Address Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Annual MRFP Address Code or the specified default value.
    */
   public final String getAnnlMRFPAddr( int index, String defaultValue )
   {
      return _AnnlMRFPAddr[index] == null ? defaultValue : _AnnlMRFPAddr[index];
   }
    
   /**
    * Gets the array of Annual MRFP Address Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Annual MRFP Address Code values.
    */
   public final String[] getAnnlMRFPAddrArray()
   {
      return _AnnlMRFPAddr;
   }
    
   /**
    * Gets the Annual MRFP Suppress field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Annual MRFP Suppress or null.
    */
   public final String getAnnlMRFPSuppress( int index )
   {
      return _AnnlMRFPSuppress[index];
   }
    
   /**
    * Gets the Annual MRFP Suppress field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Annual MRFP Suppress or the specified default value.
    */
   public final String getAnnlMRFPSuppress( int index, String defaultValue )
   {
      return _AnnlMRFPSuppress[index] == null ? defaultValue : _AnnlMRFPSuppress[index];
   }
    
   /**
    * Gets the array of Annual MRFP Suppress fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Annual MRFP Suppress values.
    */
   public final String[] getAnnlMRFPSuppressArray()
   {
      return _AnnlMRFPSuppress;
   }
    
   /**
    * Gets the Annual MRFP Waive field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Annual MRFP Waive or null.
    */
   public final String getAnnlMRFPWaive( int index )
   {
      return _AnnlMRFPWaive[index];
   }
    
   /**
    * Gets the Annual MRFP Waive field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Annual MRFP Waive or the specified default value.
    */
   public final String getAnnlMRFPWaive( int index, String defaultValue )
   {
      return _AnnlMRFPWaive[index] == null ? defaultValue : _AnnlMRFPWaive[index];
   }
    
   /**
    * Gets the array of Annual MRFP Waive fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Annual MRFP Waive values.
    */
   public final String[] getAnnlMRFPWaiveArray()
   {
      return _AnnlMRFPWaive;
   }
    
   /**
    * Gets the Annual MRFP Hold field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Annual MRFP Hold or null.
    */
   public final Boolean getAnnlMRFPHold( int index )
   {
      return _AnnlMRFPHold[index];
   }
    
   /**
    * Gets the Annual MRFP Hold field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Annual MRFP Hold or the specified default value.
    */
   public final boolean getAnnlMRFPHold( int index, boolean defaultValue )
   {
      return _AnnlMRFPHold[index] == null ? defaultValue : _AnnlMRFPHold[index].booleanValue();
   }
    
   /**
    * Gets the array of Annual MRFP Hold fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Annual MRFP Hold values.
    */
   public final Boolean[] getAnnlMRFPHoldArray()
   {
      return _AnnlMRFPHold;
   }
    
   /**
    * Gets the Annual MRFP Mail field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Annual MRFP Mail or null.
    */
   public final String getAnnlMRFPMail( int index )
   {
      return _AnnlMRFPMail[index];
   }
    
   /**
    * Gets the Annual MRFP Mail field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Annual MRFP Mail or the specified default value.
    */
   public final String getAnnlMRFPMail( int index, String defaultValue )
   {
      return _AnnlMRFPMail[index] == null ? defaultValue : _AnnlMRFPMail[index];
   }
    
   /**
    * Gets the array of Annual MRFP Mail fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Annual MRFP Mail values.
    */
   public final String[] getAnnlMRFPMailArray()
   {
      return _AnnlMRFPMail;
   }
    
   /**
    * Gets the Annual MRFP Fax field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Annual MRFP Fax or null.
    */
   public final String getAnnLMRFPFax( int index )
   {
      return _AnnLMRFPFax[index];
   }
    
   /**
    * Gets the Annual MRFP Fax field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Annual MRFP Fax or the specified default value.
    */
   public final String getAnnLMRFPFax( int index, String defaultValue )
   {
      return _AnnLMRFPFax[index] == null ? defaultValue : _AnnLMRFPFax[index];
   }
    
   /**
    * Gets the array of Annual MRFP Fax fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Annual MRFP Fax values.
    */
   public final String[] getAnnLMRFPFaxArray()
   {
      return _AnnLMRFPFax;
   }
    
   /**
    * Gets the Annual MRFP CD field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Annual MRFP CD or null.
    */
   public final String getAnnlMRFPCD( int index )
   {
      return _AnnlMRFPCD[index];
   }
    
   /**
    * Gets the Annual MRFP CD field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Annual MRFP CD or the specified default value.
    */
   public final String getAnnlMRFPCD( int index, String defaultValue )
   {
      return _AnnlMRFPCD[index] == null ? defaultValue : _AnnlMRFPCD[index];
   }
    
   /**
    * Gets the array of Annual MRFP CD fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Annual MRFP CD values.
    */
   public final String[] getAnnlMRFPCDArray()
   {
      return _AnnlMRFPCD;
   }
    
   /**
    * Gets the Annual MRFP Email field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Annual MRFP Email or null.
    */
   public final String getAnnlMRFPEmail( int index )
   {
      return _AnnlMRFPEmail[index];
   }
    
   /**
    * Gets the Annual MRFP Email field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Annual MRFP Email or the specified default value.
    */
   public final String getAnnlMRFPEmail( int index, String defaultValue )
   {
      return _AnnlMRFPEmail[index] == null ? defaultValue : _AnnlMRFPEmail[index];
   }
    
   /**
    * Gets the array of Annual MRFP Email fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Annual MRFP Email values.
    */
   public final String[] getAnnlMRFPEmailArray()
   {
      return _AnnlMRFPEmail;
   }
    
   /**
    * Gets the Annual MRFP ePost field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Annual MRFP ePost or null.
    */
   public final String getAnnlMRFPePost( int index )
   {
      return _AnnlMRFPePost[index];
   }
    
   /**
    * Gets the Annual MRFP ePost field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Annual MRFP ePost or the specified default value.
    */
   public final String getAnnlMRFPePost( int index, String defaultValue )
   {
      return _AnnlMRFPePost[index] == null ? defaultValue : _AnnlMRFPePost[index];
   }
    
   /**
    * Gets the array of Annual MRFP ePost fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Annual MRFP ePost values.
    */
   public final String[] getAnnlMRFPePostArray()
   {
      return _AnnlMRFPePost;
   }
    
   /**
    * Gets the Annual MRFP Authorization field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Annual MRFP Authorization or null.
    */
   public final String getAnnlMRFPAuth( int index )
   {
      return _AnnlMRFPAuth[index];
   }
    
   /**
    * Gets the Annual MRFP Authorization field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Annual MRFP Authorization or the specified default value.
    */
   public final String getAnnlMRFPAuth( int index, String defaultValue )
   {
      return _AnnlMRFPAuth[index] == null ? defaultValue : _AnnlMRFPAuth[index];
   }
    
   /**
    * Gets the array of Annual MRFP Authorization fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Annual MRFP Authorization values.
    */
   public final String[] getAnnlMRFPAuthArray()
   {
      return _AnnlMRFPAuth;
   }
    
   /**
    * Gets the Tax Receipts Authorization field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax Receipts Authorization or null.
    */
   public final String getTaxAuth( int index )
   {
      return _TaxAuth[index];
   }
    
   /**
    * Gets the Tax Receipts Authorization field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Receipts Authorization or the specified default value.
    */
   public final String getTaxAuth( int index, String defaultValue )
   {
      return _TaxAuth[index] == null ? defaultValue : _TaxAuth[index];
   }
    
   /**
    * Gets the array of Tax Receipts Authorization fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax Receipts Authorization values.
    */
   public final String[] getTaxAuthArray()
   {
      return _TaxAuth;
   }
    
   /**
    * Gets the Letter Authorization field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Letter Authorization or null.
    */
   public final String getLetAuth( int index )
   {
      return _LetAuth[index];
   }
    
   /**
    * Gets the Letter Authorization field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Letter Authorization or the specified default value.
    */
   public final String getLetAuth( int index, String defaultValue )
   {
      return _LetAuth[index] == null ? defaultValue : _LetAuth[index];
   }
    
   /**
    * Gets the array of Letter Authorization fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Letter Authorization values.
    */
   public final String[] getLetAuthArray()
   {
      return _LetAuth;
   }
    
   /**
    * Gets the Certificate Authorization field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Certificate Authorization or null.
    */
   public final String getCertAuth( int index )
   {
      return _CertAuth[index];
   }
    
   /**
    * Gets the Certificate Authorization field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Certificate Authorization or the specified default value.
    */
   public final String getCertAuth( int index, String defaultValue )
   {
      return _CertAuth[index] == null ? defaultValue : _CertAuth[index];
   }
    
   /**
    * Gets the array of Certificate Authorization fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Certificate Authorization values.
    */
   public final String[] getCertAuthArray()
   {
      return _CertAuth;
   }
    
   /**
    * Gets the Dividend Confirm Authorization field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Dividend Confirm Authorization or null.
    */
   public final String getDivConfAuth( int index )
   {
      return _DivConfAuth[index];
   }
    
   /**
    * Gets the Dividend Confirm Authorization field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Dividend Confirm Authorization or the specified default value.
    */
   public final String getDivConfAuth( int index, String defaultValue )
   {
      return _DivConfAuth[index] == null ? defaultValue : _DivConfAuth[index];
   }
    
   /**
    * Gets the array of Dividend Confirm Authorization fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Dividend Confirm Authorization values.
    */
   public final String[] getDivConfAuthArray()
   {
      return _DivConfAuth;
   }
    
   /**
    * Gets the Dividend Cheque Authorization field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Dividend Cheque Authorization or null.
    */
   public final String getDivChqAuth( int index )
   {
      return _DivChqAuth[index];
   }
    
   /**
    * Gets the Dividend Cheque Authorization field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Dividend Cheque Authorization or the specified default value.
    */
   public final String getDivChqAuth( int index, String defaultValue )
   {
      return _DivChqAuth[index] == null ? defaultValue : _DivChqAuth[index];
   }
    
   /**
    * Gets the array of Dividend Cheque Authorization fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Dividend Cheque Authorization values.
    */
   public final String[] getDivChqAuthArray()
   {
      return _DivChqAuth;
   }
    
   /**
    * Gets the Contract Authorization field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contract Authorization or null.
    */
   public final String getContrAuth( int index )
   {
      return _ContrAuth[index];
   }
    
   /**
    * Gets the Contract Authorization field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contract Authorization or the specified default value.
    */
   public final String getContrAuth( int index, String defaultValue )
   {
      return _ContrAuth[index] == null ? defaultValue : _ContrAuth[index];
   }
    
   /**
    * Gets the array of Contract Authorization fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contract Authorization values.
    */
   public final String[] getContrAuthArray()
   {
      return _ContrAuth;
   }
    
   /**
    * Gets the Register Authorization field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Register Authorization or null.
    */
   public final String getRegAuth( int index )
   {
      return _RegAuth[index];
   }
    
   /**
    * Gets the Register Authorization field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Register Authorization or the specified default value.
    */
   public final String getRegAuth( int index, String defaultValue )
   {
      return _RegAuth[index] == null ? defaultValue : _RegAuth[index];
   }
    
   /**
    * Gets the array of Register Authorization fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Register Authorization values.
    */
   public final String[] getRegAuthArray()
   {
      return _RegAuth;
   }
    
   /**
    * Gets the Annual Reports Authorization field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Annual Reports Authorization or null.
    */
   public final String getAnnlRptsAuth( int index )
   {
      return _AnnlRptsAuth[index];
   }
    
   /**
    * Gets the Annual Reports Authorization field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Annual Reports Authorization or the specified default value.
    */
   public final String getAnnlRptsAuth( int index, String defaultValue )
   {
      return _AnnlRptsAuth[index] == null ? defaultValue : _AnnlRptsAuth[index];
   }
    
   /**
    * Gets the array of Annual Reports Authorization fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Annual Reports Authorization values.
    */
   public final String[] getAnnlRptsAuthArray()
   {
      return _AnnlRptsAuth;
   }
    
   /**
    * Gets the Prospectus Authorization field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Prospectus Authorization or null.
    */
   public final String getProspAuth( int index )
   {
      return _ProspAuth[index];
   }
    
   /**
    * Gets the Prospectus Authorization field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Prospectus Authorization or the specified default value.
    */
   public final String getProspAuth( int index, String defaultValue )
   {
      return _ProspAuth[index] == null ? defaultValue : _ProspAuth[index];
   }
    
   /**
    * Gets the array of Prospectus Authorization fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Prospectus Authorization values.
    */
   public final String[] getProspAuthArray()
   {
      return _ProspAuth;
   }
    
   /**
    * Gets the Beneficial Authorization field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Beneficial Authorization or null.
    */
   public final String getBenAuth( int index )
   {
      return _BenAuth[index];
   }
    
   /**
    * Gets the Beneficial Authorization field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Beneficial Authorization or the specified default value.
    */
   public final String getBenAuth( int index, String defaultValue )
   {
      return _BenAuth[index] == null ? defaultValue : _BenAuth[index];
   }
    
   /**
    * Gets the array of Beneficial Authorization fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Beneficial Authorization values.
    */
   public final String[] getBenAuthArray()
   {
      return _BenAuth;
   }
    
   /**
    * Gets the Statement Authorization field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Statement Authorization or null.
    */
   public final String getStmtAuth( int index )
   {
      return _StmtAuth[index];
   }
    
   /**
    * Gets the Statement Authorization field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Statement Authorization or the specified default value.
    */
   public final String getStmtAuth( int index, String defaultValue )
   {
      return _StmtAuth[index] == null ? defaultValue : _StmtAuth[index];
   }
    
   /**
    * Gets the array of Statement Authorization fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Statement Authorization values.
    */
   public final String[] getStmtAuthArray()
   {
      return _StmtAuth;
   }
    
   /**
    * Gets the Duplicate Statement Authorization field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Duplicate Statement Authorization or null.
    */
   public final String getDupStmtAuth( int index )
   {
      return _DupStmtAuth[index];
   }
    
   /**
    * Gets the Duplicate Statement Authorization field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Duplicate Statement Authorization or the specified default value.
    */
   public final String getDupStmtAuth( int index, String defaultValue )
   {
      return _DupStmtAuth[index] == null ? defaultValue : _DupStmtAuth[index];
   }
    
   /**
    * Gets the array of Duplicate Statement Authorization fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Duplicate Statement Authorization values.
    */
   public final String[] getDupStmtAuthArray()
   {
      return _DupStmtAuth;
   }
    
   /**
    * Gets the Non Financial Confirmation Authorization field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Non Financial Confirmation Authorization or null.
    */
   public final String getNFConfAuth( int index )
   {
      return _NFConfAuth[index];
   }
    
   /**
    * Gets the Non Financial Confirmation Authorization field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Non Financial Confirmation Authorization or the specified default value.
    */
   public final String getNFConfAuth( int index, String defaultValue )
   {
      return _NFConfAuth[index] == null ? defaultValue : _NFConfAuth[index];
   }
    
   /**
    * Gets the array of Non Financial Confirmation Authorization fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Non Financial Confirmation Authorization values.
    */
   public final String[] getNFConfAuthArray()
   {
      return _NFConfAuth;
   }
    
   /**
    * Gets the Transaction Confirmation Authorization field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transaction Confirmation Authorization or null.
    */
   public final String getTxnConfAuth( int index )
   {
      return _TxnConfAuth[index];
   }
    
   /**
    * Gets the Transaction Confirmation Authorization field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transaction Confirmation Authorization or the specified default value.
    */
   public final String getTxnConfAuth( int index, String defaultValue )
   {
      return _TxnConfAuth[index] == null ? defaultValue : _TxnConfAuth[index];
   }
    
   /**
    * Gets the array of Transaction Confirmation Authorization fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transaction Confirmation Authorization values.
    */
   public final String[] getTxnConfAuthArray()
   {
      return _TxnConfAuth;
   }
    
   /**
    * Gets the Duplicate Confirmation Authorization field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Duplicate Confirmation Authorization or null.
    */
   public final String getDupConfAuth( int index )
   {
      return _DupConfAuth[index];
   }
    
   /**
    * Gets the Duplicate Confirmation Authorization field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Duplicate Confirmation Authorization or the specified default value.
    */
   public final String getDupConfAuth( int index, String defaultValue )
   {
      return _DupConfAuth[index] == null ? defaultValue : _DupConfAuth[index];
   }
    
   /**
    * Gets the array of Duplicate Confirmation Authorization fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Duplicate Confirmation Authorization values.
    */
   public final String[] getDupConfAuthArray()
   {
      return _DupConfAuth;
   }
    
   /**
    * Gets the Semi-Annual Report Authorization field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Semi-Annual Report Authorization or null.
    */
   public final String getSmAnnlRptAuth( int index )
   {
      return _SmAnnlRptAuth[index];
   }
    
   /**
    * Gets the Semi-Annual Report Authorization field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Semi-Annual Report Authorization or the specified default value.
    */
   public final String getSmAnnlRptAuth( int index, String defaultValue )
   {
      return _SmAnnlRptAuth[index] == null ? defaultValue : _SmAnnlRptAuth[index];
   }
    
   /**
    * Gets the array of Semi-Annual Report Authorization fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Semi-Annual Report Authorization values.
    */
   public final String[] getSmAnnlRptAuthArray()
   {
      return _SmAnnlRptAuth;
   }
    
   /**
    * Gets the Contribution Receipt Authorization field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contribution Receipt Authorization or null.
    */
   public final String getContrRAuth( int index )
   {
      return _ContrRAuth[index];
   }
    
   /**
    * Gets the Contribution Receipt Authorization field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contribution Receipt Authorization or the specified default value.
    */
   public final String getContrRAuth( int index, String defaultValue )
   {
      return _ContrRAuth[index] == null ? defaultValue : _ContrRAuth[index];
   }
    
   /**
    * Gets the array of Contribution Receipt Authorization fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contribution Receipt Authorization values.
    */
   public final String[] getContrRAuthArray()
   {
      return _ContrRAuth;
   }
    
   /**
    * Gets the Statement Frequency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Statement Frequency or null.
    */
   public final String getStmtFrequency( int index )
   {
      return _StmtFrequency[index];
   }
    
   /**
    * Gets the Statement Frequency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Statement Frequency or the specified default value.
    */
   public final String getStmtFrequency( int index, String defaultValue )
   {
      return _StmtFrequency[index] == null ? defaultValue : _StmtFrequency[index];
   }
    
   /**
    * Gets the array of Statement Frequency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Statement Frequency values.
    */
   public final String[] getStmtFrequencyArray()
   {
      return _StmtFrequency;
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
      
      _RegAddr = resizeArray( _RegAddr, _RepeatCount );
      _DivConfAddr = resizeArray( _DivConfAddr, _RepeatCount );
      _DivChqAddr = resizeArray( _DivChqAddr, _RepeatCount );
      _TxnConfAddr = resizeArray( _TxnConfAddr, _RepeatCount );
      _DupConfAddr = resizeArray( _DupConfAddr, _RepeatCount );
      _StmtAddr = resizeArray( _StmtAddr, _RepeatCount );
      _DupStmtAddr = resizeArray( _DupStmtAddr, _RepeatCount );
      _CertAddr = resizeArray( _CertAddr, _RepeatCount );
      _TaxAddr = resizeArray( _TaxAddr, _RepeatCount );
      _LetAddr = resizeArray( _LetAddr, _RepeatCount );
      _BenAddr = resizeArray( _BenAddr, _RepeatCount );
      _DupConfCopies = resizeArray( _DupConfCopies, _RepeatCount );
      _DupStmtCopies = resizeArray( _DupStmtCopies, _RepeatCount );
      _RegOnHold = resizeArray( _RegOnHold, _RepeatCount );
      _DivConfOnHold = resizeArray( _DivConfOnHold, _RepeatCount );
      _DivChqOnHold = resizeArray( _DivChqOnHold, _RepeatCount );
      _TxnConfOnHold = resizeArray( _TxnConfOnHold, _RepeatCount );
      _DupConfOnHold = resizeArray( _DupConfOnHold, _RepeatCount );
      _StmtOnHold = resizeArray( _StmtOnHold, _RepeatCount );
      _DupStmtOnHold = resizeArray( _DupStmtOnHold, _RepeatCount );
      _CertOnHold = resizeArray( _CertOnHold, _RepeatCount );
      _TaxOnHold = resizeArray( _TaxOnHold, _RepeatCount );
      _LetOnHold = resizeArray( _LetOnHold, _RepeatCount );
      _BenOnHold = resizeArray( _BenOnHold, _RepeatCount );
      _SATxnConfCode = resizeArray( _SATxnConfCode, _RepeatCount );
      _SATxnConfDesc = resizeArray( _SATxnConfDesc, _RepeatCount );
      _SADivConfCode = resizeArray( _SADivConfCode, _RepeatCount );
      _SADivConfDesc = resizeArray( _SADivConfDesc, _RepeatCount );
      _SALettersCode = resizeArray( _SALettersCode, _RepeatCount );
      _SALettersDesc = resizeArray( _SALettersDesc, _RepeatCount );
      _AcctMstrVer = resizeArray( _AcctMstrVer, _RepeatCount );
      _AcctMstrRid = resizeArray( _AcctMstrRid, _RepeatCount );
      _NFCAddr = resizeArray( _NFCAddr, _RepeatCount );
      _NFConHold = resizeArray( _NFConHold, _RepeatCount );
      _AccountNum = resizeArray( _AccountNum, _RepeatCount );
      _ContrAddr = resizeArray( _ContrAddr, _RepeatCount );
      _ContrHold = resizeArray( _ContrHold, _RepeatCount );
      _AnnlRptsAddr = resizeArray( _AnnlRptsAddr, _RepeatCount );
      _AnnlRptsHold = resizeArray( _AnnlRptsHold, _RepeatCount );
      _ProspAddr = resizeArray( _ProspAddr, _RepeatCount );
      _ProspHold = resizeArray( _ProspHold, _RepeatCount );
      _TaxSuppress = resizeArray( _TaxSuppress, _RepeatCount );
      _TaxWaive = resizeArray( _TaxWaive, _RepeatCount );
      _TaxMail = resizeArray( _TaxMail, _RepeatCount );
      _TaxFax = resizeArray( _TaxFax, _RepeatCount );
      _TaxCD = resizeArray( _TaxCD, _RepeatCount );
      _TaxEmail = resizeArray( _TaxEmail, _RepeatCount );
      _LetSuppress = resizeArray( _LetSuppress, _RepeatCount );
      _LetWaive = resizeArray( _LetWaive, _RepeatCount );
      _LetMail = resizeArray( _LetMail, _RepeatCount );
      _LetFax = resizeArray( _LetFax, _RepeatCount );
      _LetCD = resizeArray( _LetCD, _RepeatCount );
      _LetEmail = resizeArray( _LetEmail, _RepeatCount );
      _CertSuppress = resizeArray( _CertSuppress, _RepeatCount );
      _CertWaive = resizeArray( _CertWaive, _RepeatCount );
      _CertMail = resizeArray( _CertMail, _RepeatCount );
      _CertFax = resizeArray( _CertFax, _RepeatCount );
      _CertCD = resizeArray( _CertCD, _RepeatCount );
      _CertEmail = resizeArray( _CertEmail, _RepeatCount );
      _DivConfSuppress = resizeArray( _DivConfSuppress, _RepeatCount );
      _DivConfWaive = resizeArray( _DivConfWaive, _RepeatCount );
      _DivConfMail = resizeArray( _DivConfMail, _RepeatCount );
      _DivConfFax = resizeArray( _DivConfFax, _RepeatCount );
      _DivConfCD = resizeArray( _DivConfCD, _RepeatCount );
      _DivConfEmail = resizeArray( _DivConfEmail, _RepeatCount );
      _DivChqSuppress = resizeArray( _DivChqSuppress, _RepeatCount );
      _DivChqWaive = resizeArray( _DivChqWaive, _RepeatCount );
      _DivChqMail = resizeArray( _DivChqMail, _RepeatCount );
      _DivChqFax = resizeArray( _DivChqFax, _RepeatCount );
      _DivChqCD = resizeArray( _DivChqCD, _RepeatCount );
      _DivChqEmail = resizeArray( _DivChqEmail, _RepeatCount );
      _ContrSuppress = resizeArray( _ContrSuppress, _RepeatCount );
      _ContrWaive = resizeArray( _ContrWaive, _RepeatCount );
      _ContrMail = resizeArray( _ContrMail, _RepeatCount );
      _ContrFax = resizeArray( _ContrFax, _RepeatCount );
      _ContrCD = resizeArray( _ContrCD, _RepeatCount );
      _ContrEmail = resizeArray( _ContrEmail, _RepeatCount );
      _RegSuppress = resizeArray( _RegSuppress, _RepeatCount );
      _RegWaive = resizeArray( _RegWaive, _RepeatCount );
      _RegMail = resizeArray( _RegMail, _RepeatCount );
      _RegFax = resizeArray( _RegFax, _RepeatCount );
      _RegCD = resizeArray( _RegCD, _RepeatCount );
      _RegEmail = resizeArray( _RegEmail, _RepeatCount );
      _AnnlRptsSuppress = resizeArray( _AnnlRptsSuppress, _RepeatCount );
      _AnnlRptsWaive = resizeArray( _AnnlRptsWaive, _RepeatCount );
      _AnnlRptsMail = resizeArray( _AnnlRptsMail, _RepeatCount );
      _AnnlRptsFax = resizeArray( _AnnlRptsFax, _RepeatCount );
      _AnnlRptsCd = resizeArray( _AnnlRptsCd, _RepeatCount );
      _AnnlRptsEmail = resizeArray( _AnnlRptsEmail, _RepeatCount );
      _ProspSuppress = resizeArray( _ProspSuppress, _RepeatCount );
      _ProspWaive = resizeArray( _ProspWaive, _RepeatCount );
      _ProspMail = resizeArray( _ProspMail, _RepeatCount );
      _ProspFax = resizeArray( _ProspFax, _RepeatCount );
      _ProspCD = resizeArray( _ProspCD, _RepeatCount );
      _ProspEmail = resizeArray( _ProspEmail, _RepeatCount );
      _BenSuppress = resizeArray( _BenSuppress, _RepeatCount );
      _BenWaive = resizeArray( _BenWaive, _RepeatCount );
      _BenMail = resizeArray( _BenMail, _RepeatCount );
      _BenFax = resizeArray( _BenFax, _RepeatCount );
      _BenCD = resizeArray( _BenCD, _RepeatCount );
      _BenEmail = resizeArray( _BenEmail, _RepeatCount );
      _StmtSuppress = resizeArray( _StmtSuppress, _RepeatCount );
      _StmtWaive = resizeArray( _StmtWaive, _RepeatCount );
      _StmtMail = resizeArray( _StmtMail, _RepeatCount );
      _StmtFax = resizeArray( _StmtFax, _RepeatCount );
      _StmtCD = resizeArray( _StmtCD, _RepeatCount );
      _StmtEmail = resizeArray( _StmtEmail, _RepeatCount );
      _DupStmtSuppress = resizeArray( _DupStmtSuppress, _RepeatCount );
      _DupStmtWaive = resizeArray( _DupStmtWaive, _RepeatCount );
      _DupStmtMail = resizeArray( _DupStmtMail, _RepeatCount );
      _DupStmtFax = resizeArray( _DupStmtFax, _RepeatCount );
      _DupStmtCD = resizeArray( _DupStmtCD, _RepeatCount );
      _DupStmtEmail = resizeArray( _DupStmtEmail, _RepeatCount );
      _NFConfSuppress = resizeArray( _NFConfSuppress, _RepeatCount );
      _NFConfWaive = resizeArray( _NFConfWaive, _RepeatCount );
      _NFConfMail = resizeArray( _NFConfMail, _RepeatCount );
      _NFConfFax = resizeArray( _NFConfFax, _RepeatCount );
      _NFConfCD = resizeArray( _NFConfCD, _RepeatCount );
      _NFConfEmail = resizeArray( _NFConfEmail, _RepeatCount );
      _TxnConfSuppress = resizeArray( _TxnConfSuppress, _RepeatCount );
      _TxnConfWaive = resizeArray( _TxnConfWaive, _RepeatCount );
      _TxnConfMail = resizeArray( _TxnConfMail, _RepeatCount );
      _TxnConfFax = resizeArray( _TxnConfFax, _RepeatCount );
      _TxnConfCD = resizeArray( _TxnConfCD, _RepeatCount );
      _TxnConfEmail = resizeArray( _TxnConfEmail, _RepeatCount );
      _DupConfSuppress = resizeArray( _DupConfSuppress, _RepeatCount );
      _DupConfWaive = resizeArray( _DupConfWaive, _RepeatCount );
      _DupConfMail = resizeArray( _DupConfMail, _RepeatCount );
      _DupConfFax = resizeArray( _DupConfFax, _RepeatCount );
      _DupConfCD = resizeArray( _DupConfCD, _RepeatCount );
      _DupConfEmail = resizeArray( _DupConfEmail, _RepeatCount );
      _SmAnnlRptSuppress = resizeArray( _SmAnnlRptSuppress, _RepeatCount );
      _SmAnnlRptWaive = resizeArray( _SmAnnlRptWaive, _RepeatCount );
      _SmAnnlRptMail = resizeArray( _SmAnnlRptMail, _RepeatCount );
      _SmAnnlRptFax = resizeArray( _SmAnnlRptFax, _RepeatCount );
      _SmAnnlRptCD = resizeArray( _SmAnnlRptCD, _RepeatCount );
      _SmAnnlRptEmail = resizeArray( _SmAnnlRptEmail, _RepeatCount );
      _SmAnnlRptAddr = resizeArray( _SmAnnlRptAddr, _RepeatCount );
      _SmAnnlRptHold = resizeArray( _SmAnnlRptHold, _RepeatCount );
      _TaxEPost = resizeArray( _TaxEPost, _RepeatCount );
      _LetEPost = resizeArray( _LetEPost, _RepeatCount );
      _CertEPost = resizeArray( _CertEPost, _RepeatCount );
      _DivConfEPost = resizeArray( _DivConfEPost, _RepeatCount );
      _DivChqEPost = resizeArray( _DivChqEPost, _RepeatCount );
      _ContrEPost = resizeArray( _ContrEPost, _RepeatCount );
      _RegEPost = resizeArray( _RegEPost, _RepeatCount );
      _AnnlRptsEPost = resizeArray( _AnnlRptsEPost, _RepeatCount );
      _ProspEPost = resizeArray( _ProspEPost, _RepeatCount );
      _BenEPost = resizeArray( _BenEPost, _RepeatCount );
      _StmtEPost = resizeArray( _StmtEPost, _RepeatCount );
      _DulStmtEPost = resizeArray( _DulStmtEPost, _RepeatCount );
      _NFConfEPost = resizeArray( _NFConfEPost, _RepeatCount );
      _TxnConfEPost = resizeArray( _TxnConfEPost, _RepeatCount );
      _DupConfEPost = resizeArray( _DupConfEPost, _RepeatCount );
      _SmAnnlRptEPost = resizeArray( _SmAnnlRptEPost, _RepeatCount );
      _ContrRSuppress = resizeArray( _ContrRSuppress, _RepeatCount );
      _ContrRWaive = resizeArray( _ContrRWaive, _RepeatCount );
      _ContrRMail = resizeArray( _ContrRMail, _RepeatCount );
      _ContrRFax = resizeArray( _ContrRFax, _RepeatCount );
      _ContrRCD = resizeArray( _ContrRCD, _RepeatCount );
      _ContrREmail = resizeArray( _ContrREmail, _RepeatCount );
      _ContrREPost = resizeArray( _ContrREPost, _RepeatCount );
      _ContrRAddr = resizeArray( _ContrRAddr, _RepeatCount );
      _ContrRHold = resizeArray( _ContrRHold, _RepeatCount );
      _SmAnnlMRFPAddr = resizeArray( _SmAnnlMRFPAddr, _RepeatCount );
      _SmAnnlMRFPSuppress = resizeArray( _SmAnnlMRFPSuppress, _RepeatCount );
      _SmAnnlMRFPWaive = resizeArray( _SmAnnlMRFPWaive, _RepeatCount );
      _SmAnnlMRFPHold = resizeArray( _SmAnnlMRFPHold, _RepeatCount );
      _SmAnnlMRFPMail = resizeArray( _SmAnnlMRFPMail, _RepeatCount );
      _SmAnnlMRFPFax = resizeArray( _SmAnnlMRFPFax, _RepeatCount );
      _SmAnnlMRFPCD = resizeArray( _SmAnnlMRFPCD, _RepeatCount );
      _SmAnnlMRFPEmail = resizeArray( _SmAnnlMRFPEmail, _RepeatCount );
      _SmAnnlMRFPePost = resizeArray( _SmAnnlMRFPePost, _RepeatCount );
      _SmAnnlMRFPAuth = resizeArray( _SmAnnlMRFPAuth, _RepeatCount );
      _AnnlMRFPAddr = resizeArray( _AnnlMRFPAddr, _RepeatCount );
      _AnnlMRFPSuppress = resizeArray( _AnnlMRFPSuppress, _RepeatCount );
      _AnnlMRFPWaive = resizeArray( _AnnlMRFPWaive, _RepeatCount );
      _AnnlMRFPHold = resizeArray( _AnnlMRFPHold, _RepeatCount );
      _AnnlMRFPMail = resizeArray( _AnnlMRFPMail, _RepeatCount );
      _AnnLMRFPFax = resizeArray( _AnnLMRFPFax, _RepeatCount );
      _AnnlMRFPCD = resizeArray( _AnnlMRFPCD, _RepeatCount );
      _AnnlMRFPEmail = resizeArray( _AnnlMRFPEmail, _RepeatCount );
      _AnnlMRFPePost = resizeArray( _AnnlMRFPePost, _RepeatCount );
      _AnnlMRFPAuth = resizeArray( _AnnlMRFPAuth, _RepeatCount );
      _TaxAuth = resizeArray( _TaxAuth, _RepeatCount );
      _LetAuth = resizeArray( _LetAuth, _RepeatCount );
      _CertAuth = resizeArray( _CertAuth, _RepeatCount );
      _DivConfAuth = resizeArray( _DivConfAuth, _RepeatCount );
      _DivChqAuth = resizeArray( _DivChqAuth, _RepeatCount );
      _ContrAuth = resizeArray( _ContrAuth, _RepeatCount );
      _RegAuth = resizeArray( _RegAuth, _RepeatCount );
      _AnnlRptsAuth = resizeArray( _AnnlRptsAuth, _RepeatCount );
      _ProspAuth = resizeArray( _ProspAuth, _RepeatCount );
      _BenAuth = resizeArray( _BenAuth, _RepeatCount );
      _StmtAuth = resizeArray( _StmtAuth, _RepeatCount );
      _DupStmtAuth = resizeArray( _DupStmtAuth, _RepeatCount );
      _NFConfAuth = resizeArray( _NFConfAuth, _RepeatCount );
      _TxnConfAuth = resizeArray( _TxnConfAuth, _RepeatCount );
      _DupConfAuth = resizeArray( _DupConfAuth, _RepeatCount );
      _SmAnnlRptAuth = resizeArray( _SmAnnlRptAuth, _RepeatCount );
      _ContrRAuth = resizeArray( _ContrRAuth, _RepeatCount );
      _StmtFrequency = resizeArray( _StmtFrequency, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _RegAddr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DivConfAddr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DivChqAddr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TxnConfAddr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DupConfAddr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _StmtAddr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DupStmtAddr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CertAddr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TaxAddr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LetAddr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BenAddr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DupConfCopies[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _DupStmtCopies[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _RegOnHold[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _DivConfOnHold[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _DivChqOnHold[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TxnConfOnHold[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _DupConfOnHold[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _StmtOnHold[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _DupStmtOnHold[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _CertOnHold[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TaxOnHold[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _LetOnHold[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _BenOnHold[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _SATxnConfCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SATxnConfDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SADivConfCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SADivConfDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SALettersCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SALettersDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctMstrVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _AcctMstrRid[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _NFCAddr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _NFConHold[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _AccountNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ContrAddr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ContrHold[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _AnnlRptsAddr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AnnlRptsHold[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ProspAddr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProspHold[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TaxSuppress[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TaxWaive[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TaxMail[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TaxFax[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TaxCD[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TaxEmail[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LetSuppress[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LetWaive[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LetMail[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LetFax[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LetCD[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LetEmail[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CertSuppress[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CertWaive[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CertMail[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CertFax[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CertCD[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CertEmail[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DivConfSuppress[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DivConfWaive[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DivConfMail[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DivConfFax[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DivConfCD[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DivConfEmail[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DivChqSuppress[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DivChqWaive[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DivChqMail[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DivChqFax[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DivChqCD[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DivChqEmail[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ContrSuppress[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ContrWaive[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ContrMail[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ContrFax[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ContrCD[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ContrEmail[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RegSuppress[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RegWaive[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RegMail[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RegFax[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RegCD[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RegEmail[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AnnlRptsSuppress[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AnnlRptsWaive[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AnnlRptsMail[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AnnlRptsFax[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AnnlRptsCd[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AnnlRptsEmail[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProspSuppress[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProspWaive[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProspMail[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProspFax[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProspCD[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProspEmail[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BenSuppress[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BenWaive[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BenMail[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BenFax[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BenCD[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BenEmail[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _StmtSuppress[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _StmtWaive[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _StmtMail[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _StmtFax[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _StmtCD[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _StmtEmail[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DupStmtSuppress[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DupStmtWaive[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DupStmtMail[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DupStmtFax[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DupStmtCD[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DupStmtEmail[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _NFConfSuppress[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _NFConfWaive[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _NFConfMail[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _NFConfFax[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _NFConfCD[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _NFConfEmail[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TxnConfSuppress[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TxnConfWaive[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TxnConfMail[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TxnConfFax[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TxnConfCD[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TxnConfEmail[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DupConfSuppress[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DupConfWaive[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DupConfMail[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DupConfFax[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DupConfCD[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DupConfEmail[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SmAnnlRptSuppress[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SmAnnlRptWaive[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SmAnnlRptMail[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SmAnnlRptFax[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SmAnnlRptCD[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SmAnnlRptEmail[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SmAnnlRptAddr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SmAnnlRptHold[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TaxEPost[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LetEPost[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CertEPost[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DivConfEPost[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DivChqEPost[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ContrEPost[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RegEPost[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AnnlRptsEPost[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProspEPost[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BenEPost[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _StmtEPost[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DulStmtEPost[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _NFConfEPost[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TxnConfEPost[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DupConfEPost[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SmAnnlRptEPost[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ContrRSuppress[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ContrRWaive[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ContrRMail[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ContrRFax[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ContrRCD[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ContrREmail[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ContrREPost[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ContrRAddr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ContrRHold[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _SmAnnlMRFPAddr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SmAnnlMRFPSuppress[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SmAnnlMRFPWaive[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SmAnnlMRFPHold[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _SmAnnlMRFPMail[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SmAnnlMRFPFax[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SmAnnlMRFPCD[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SmAnnlMRFPEmail[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SmAnnlMRFPePost[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SmAnnlMRFPAuth[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AnnlMRFPAddr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AnnlMRFPSuppress[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AnnlMRFPWaive[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AnnlMRFPHold[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _AnnlMRFPMail[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AnnLMRFPFax[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AnnlMRFPCD[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AnnlMRFPEmail[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AnnlMRFPePost[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AnnlMRFPAuth[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TaxAuth[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LetAuth[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CertAuth[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DivConfAuth[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DivChqAuth[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ContrAuth[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RegAuth[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AnnlRptsAuth[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProspAuth[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BenAuth[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _StmtAuth[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DupStmtAuth[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _NFConfAuth[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TxnConfAuth[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DupConfAuth[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SmAnnlRptAuth[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ContrRAuth[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _StmtFrequency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
