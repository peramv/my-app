// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Account Mailing Info Maintenance request.
 * For additional view information see <A HREF="../../../../viewspecs/ShrMailUpd.doc">ShrMailUpd.doc</A>.
 * 
 * @author RTS Generated
 */
public class ShrMailUpdRequest extends IFastRequest implements Serializable
{

   /**
    * Session Id member variable.
    */
   private String _SessionId = "";
            
   /**
    * User Id member variable.
    */
   private String _User_Id = "";
            
   /**
    * Language Code member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * Company Id member variable.
    */
   private String _CompanyId = "";
            
   /**
    * Run Mode member variable.
    */
   private String _RunMode = "";
            
   /**
    * Registered Address member variable.
    */
   private String _RegAddr = "";
            
   /**
    * Dividend  Confirmation member variable.
    */
   private String _DivConfAddr = "";
            
   /**
    * Dividend Cheque member variable.
    */
   private String _DivChqAddr = "";
            
   /**
    * Transaction Confirmation member variable.
    */
   private String _TxnConfAddr = "";
            
   /**
    * Duplicate Transaction Confirmation member variable.
    */
   private String _DupConfAddr = "";
            
   /**
    * Statement member variable.
    */
   private String _StmtAddr = "";
            
   /**
    * Duplicate Statement member variable.
    */
   private String _DupStmtAddr = "";
            
   /**
    * Certificate member variable.
    */
   private String _CertAddr = "";
            
   /**
    * Tax Receipt member variable.
    */
   private String _TaxAddr = "";
            
   /**
    * Letters member variable.
    */
   private String _LetAddr = "";
            
   /**
    * Beneficial Owner member variable.
    */
   private String _BenAddr = "";
            
   /**
    * Number of Duplicate Confirms member variable.
    */
   private Integer _DupConfCopies = null;
            
   /**
    * Number of Duplicate Statements member variable.
    */
   private Integer _DupStmtCopies = null;
            
   /**
    * Registered Address Use on Hold member variable.
    */
   private Boolean _RegOnHold = new Boolean(false);
            
   /**
    * Dividend  Confirmation Addr Use on Hold member variable.
    */
   private Boolean _DivConfOnHold = new Boolean(false);
            
   /**
    * Dividend Cheque Addr Use On Hold member variable.
    */
   private Boolean _DivChqOnHold = new Boolean(false);
            
   /**
    * Transaction Confirm Addr Use on Hold member variable.
    */
   private Boolean _TxnConfOnHold = new Boolean(false);
            
   /**
    * Duplicate Confirm Addr Use On Hold member variable.
    */
   private Boolean _DupConfOnHold = new Boolean(false);
            
   /**
    * Statement Addr Use On Hold member variable.
    */
   private Boolean _StmtOnHold = new Boolean(false);
            
   /**
    * Duplicate Statement Addr Use on Hold member variable.
    */
   private Boolean _DupStmtOnHold = new Boolean(false);
            
   /**
    * Certifidate Addr Use On Hold member variable.
    */
   private Boolean _CertOnHold = new Boolean(false);
            
   /**
    * Tax Receipts Addr Use On Hold member variable.
    */
   private Boolean _TaxOnHold = new Boolean(false);
            
   /**
    * Letters Addr Use On Hold member variable.
    */
   private Boolean _LetOnHold = new Boolean(false);
            
   /**
    * Beneficial Addr Use On Hold member variable.
    */
   private Boolean _BenOnHold = new Boolean(false);
            
   /**
    * Servicing Agent for Transaction Confirms member variable.
    */
   private String _SATxnConfCode = "";
            
   /**
    * Servicing Agent for Dividend  Confirms member variable.
    */
   private String _SADivConfCode = "";
            
   /**
    * Servicing Agent for Letters member variable.
    */
   private String _SALettersCode = "";
            
   /**
    * Acct Table Version Number member variable.
    */
   private Integer _AcctMstrVer = null;
            
   /**
    * Non Financial  Address member variable.
    */
   private String _NFCAddr = "";
            
   /**
    * Non Financial Addr on Hold member variable.
    */
   private Boolean _NFConHold = new Boolean(false);
            
   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Acct-Mstr record id member variable.
    */
   private Integer _AcctMstrRid = null;
            
            
            
   /**
    * Contract Address Code member variable.
    */
   private String _ContrAddr = "";
            
   /**
    * Contract Address Use on Hold member variable.
    */
   private Boolean _ContrHold = new Boolean(false);
            
   /**
    * Annual Reports Address Code member variable.
    */
   private String _AnnlRptsAddr = "";
            
   /**
    * Annual Reports Address Use on Hold member variable.
    */
   private Boolean _AnnlRptsHold = new Boolean(false);
            
   /**
    * Prospectus Address Code member variable.
    */
   private String _ProspAddr = "";
            
   /**
    * Prospectus Address Use on Hold member variable.
    */
   private Boolean _ProspHold = new Boolean(false);
            
   /**
    * Tax Suppress member variable.
    */
   private Boolean _TaxSuppress = new Boolean(false);
            
   /**
    * Tax Waive member variable.
    */
   private Boolean _TaxWaive = new Boolean(false);
            
   /**
    * Tax Mail member variable.
    */
   private String _TaxMail = "";
            
   /**
    * Tax Fax member variable.
    */
   private String _TaxFax = "";
            
   /**
    * Tax CD member variable.
    */
   private String _TaxCD = "";
            
   /**
    * Tax Email member variable.
    */
   private String _TaxEmail = "";
            
   /**
    * Letter Suppress member variable.
    */
   private Boolean _LetSuppress = new Boolean(false);
            
   /**
    * Letter Waive member variable.
    */
   private Boolean _LetWaive = new Boolean(false);
            
   /**
    * Letter Mail member variable.
    */
   private String _LetMail = "";
            
   /**
    * Letter Fax member variable.
    */
   private String _LetFax = "";
            
   /**
    * Letter CD member variable.
    */
   private String _LetCD = "";
            
   /**
    * Letter Email member variable.
    */
   private String _LetEmail = "";
            
   /**
    * Cert Suppress member variable.
    */
   private Boolean _CertSuppress = new Boolean(false);
            
   /**
    * Cert Waive member variable.
    */
   private Boolean _CertWaive = new Boolean(false);
            
   /**
    * Cert Mail member variable.
    */
   private String _CertMail = "";
            
   /**
    * Cert CD member variable.
    */
   private String _CertCD = "";
            
   /**
    * Cert Email member variable.
    */
   private String _CertEmail = "";
            
   /**
    * Cert Fax member variable.
    */
   private String _CertFax = "";
            
   /**
    * Div Conf Suppress member variable.
    */
   private Boolean _DivConfSuppress = new Boolean(false);
            
   /**
    * Div Conf Waive member variable.
    */
   private Boolean _DivConfWaive = new Boolean(false);
            
   /**
    * Div Conf Mail member variable.
    */
   private String _DivConfMail = "";
            
   /**
    * Div Conf Fax member variable.
    */
   private String _DivConfFax = "";
            
   /**
    * Div Conf CD member variable.
    */
   private String _DivConfCD = "";
            
   /**
    * Div Conf Email member variable.
    */
   private String _DivConfEmail = "";
            
   /**
    * Div Chq Suppress member variable.
    */
   private Boolean _DivChqSuppress = new Boolean(false);
            
   /**
    * Div Chq Waive member variable.
    */
   private Boolean _DivChqWaive = new Boolean(false);
            
   /**
    * Div Chq Mail member variable.
    */
   private String _DivChqMail = "";
            
   /**
    * Div Chq Fax member variable.
    */
   private String _DivChqFax = "";
            
   /**
    * Div Chq CD member variable.
    */
   private String _DivChqCD = "";
            
   /**
    * Div Chq Email member variable.
    */
   private String _DivChqEmail = "";
            
   /**
    * Reg Suppress member variable.
    */
   private Boolean _RegSuppress = new Boolean(false);
            
   /**
    * Reg Waive member variable.
    */
   private Boolean _RegWaive = new Boolean(false);
            
   /**
    * Reg Mail member variable.
    */
   private String _RegMail = "";
            
   /**
    * Reg Fax member variable.
    */
   private String _RegFax = "";
            
   /**
    * Reg CD member variable.
    */
   private String _RegCd = "";
            
   /**
    * Reg Email member variable.
    */
   private String _RegEmail = "";
            
   /**
    * Annual Reports Suppress member variable.
    */
   private Boolean _AnnlRptsSuppress = new Boolean(false);
            
   /**
    * Annual Reports Waive member variable.
    */
   private Boolean _AnnlRptsWaive = new Boolean(false);
            
   /**
    * Annual Reports Mail member variable.
    */
   private String _AnnlRptsMail = "";
            
   /**
    * Annual Reports Fax member variable.
    */
   private String _AnnlRptsFax = "";
            
   /**
    * Annual Reports CD member variable.
    */
   private String _AnnlRptsCD = "";
            
   /**
    * Annual Reports Email member variable.
    */
   private String _AnnlRptsEmail = "";
            
   /**
    * Prosp Suppress member variable.
    */
   private Boolean _ProspSuppress = new Boolean(false);
            
   /**
    * Prosp Waive member variable.
    */
   private Boolean _ProspWaive = new Boolean(false);
            
   /**
    * Prosp Mail member variable.
    */
   private String _ProspMail = "";
            
   /**
    * Prosp Fax member variable.
    */
   private String _ProspFax = "";
            
   /**
    * Prosp CD member variable.
    */
   private String _ProspCd = "";
            
   /**
    * Prosp Email member variable.
    */
   private String _ProspEmail = "";
            
   /**
    * Ben Suppress member variable.
    */
   private Boolean _BenSuppress = new Boolean(false);
            
   /**
    * Ben Waive member variable.
    */
   private Boolean _BenWaive = new Boolean(false);
            
   /**
    * Ben Mail member variable.
    */
   private String _BenMail = "";
            
   /**
    * Ben Fax member variable.
    */
   private String _BenFax = "";
            
   /**
    * Ben CD member variable.
    */
   private String _BenCD = "";
            
   /**
    * Ben Email member variable.
    */
   private String _BenEmail = "";
            
   /**
    * Stmt Suppress member variable.
    */
   private Boolean _StmtSuppress = new Boolean(false);
            
   /**
    * Stmt Waive member variable.
    */
   private Boolean _StmtWaive = new Boolean(false);
            
   /**
    * Stmt Mail member variable.
    */
   private String _StmtMail = "";
            
   /**
    * Stmt Fax member variable.
    */
   private String _StmtFax = "";
            
   /**
    * Stmt Cd member variable.
    */
   private String _StmtCD = "";
            
   /**
    * Stmt Email member variable.
    */
   private String _StmtEmail = "";
            
   /**
    * Dup Stmt Suppress member variable.
    */
   private Boolean _DupStmtSuppress = new Boolean(false);
            
   /**
    * Dup Stmt Waive member variable.
    */
   private Boolean _DupStmtWaive = new Boolean(false);
            
   /**
    * Dup Stmt Mail member variable.
    */
   private String _DupStmtMail = "";
            
   /**
    * Dup Stmt Fax member variable.
    */
   private String _DupStmtFax = "";
            
   /**
    * Dup Stmt CD member variable.
    */
   private String _DupStmtCD = "";
            
   /**
    * Dup Stmt Email member variable.
    */
   private String _DupStmtEmail = "";
            
   /**
    * NF Conf Suppress member variable.
    */
   private Boolean _NFConfSuppress = new Boolean(false);
            
   /**
    * NF Conf Waive member variable.
    */
   private Boolean _NFConfWaive = new Boolean(false);
            
   /**
    * NF Conf Mail member variable.
    */
   private String _NFConfMail = "";
            
   /**
    * NF Conf Fax member variable.
    */
   private String _NFConfFax = "";
            
   /**
    * NF Conf CD member variable.
    */
   private String _NFConfCD = "";
            
   /**
    * NF Conf Email member variable.
    */
   private String _NFConfEmail = "";
            
   /**
    * Txn Conf Suppress member variable.
    */
   private Boolean _TxnConfSuppress = new Boolean(false);
            
   /**
    * Txn Conf Waive member variable.
    */
   private Boolean _TxnConfWaive = new Boolean(false);
            
   /**
    * Txn Conf Mail member variable.
    */
   private String _TxnConfMail = "";
            
   /**
    * Txn Conf Fax member variable.
    */
   private String _TxnConfFax = "";
            
   /**
    * Txn Conf CD member variable.
    */
   private String _TxnConfCD = "";
            
   /**
    * Txn Conf Email member variable.
    */
   private String _TxnConfEmail = "";
            
   /**
    * Dup Conf Suppress member variable.
    */
   private Boolean _DupConfSuppress = new Boolean(false);
            
   /**
    * Dup Conf Waive member variable.
    */
   private Boolean _DupConfWaive = new Boolean(false);
            
   /**
    * Dup Conf Mail member variable.
    */
   private String _DupConfMail = "";
            
   /**
    * Dup Conf Fax member variable.
    */
   private String _DupConfFax = "";
            
   /**
    * Dup Conf CD member variable.
    */
   private String _DupConfCd = "";
            
   /**
    * Dup Conf Email member variable.
    */
   private String _DupConfEmail = "";
            
   /**
    * ContrSuppress member variable.
    */
   private Boolean _ContrSuppress = new Boolean(false);
            
   /**
    * Contr Waive member variable.
    */
   private Boolean _ContrWaive = new Boolean(false);
            
   /**
    * Contr Mail member variable.
    */
   private String _ContrMail = "";
            
   /**
    * Contr Fax member variable.
    */
   private String _ContrFax = "";
            
   /**
    * Contr CD member variable.
    */
   private String _ContrCD = "";
            
   /**
    * Contr Email member variable.
    */
   private String _ContrEmail = "";
            
   /**
    * Semi Annual Report Suppress member variable.
    */
   private Boolean _SmAnnlRptSuppress = new Boolean(false);
            
   /**
    * Semi Annual Report Waive member variable.
    */
   private Boolean _SmAnnlRptWaive = new Boolean(false);
            
   /**
    * Semi Annual Report Mail member variable.
    */
   private String _SmAnnlRptMail = "";
            
   /**
    * Semi Annual Report Fax member variable.
    */
   private String _SmAnnlRptFax = "";
            
   /**
    * Semi Annual Report CD member variable.
    */
   private String _SmAnnlRptCD = "";
            
   /**
    * Semi Annual Report Email member variable.
    */
   private String _SmAnnlRptEmail = "";
            
   /**
    * Semi Annual Report Address Code member variable.
    */
   private String _SmAnnlRptAddr = "";
            
   /**
    * Semi Annual Report On hold member variable.
    */
   private Boolean _SmAnnlRptHold = new Boolean(false);
            
   /**
    * Tax EPost member variable.
    */
   private String _TaxEPost = "";
            
   /**
    * Letter EPost member variable.
    */
   private String _LetEPost = "";
            
   /**
    * Certificate EPost member variable.
    */
   private String _CertEPost = "";
            
   /**
    * Dividend Confirm EPost member variable.
    */
   private String _DivConfEPost = "";
            
   /**
    * Dividend Chq EPost member variable.
    */
   private String _DivChqEPost = "";
            
   /**
    * Contribution EPost member variable.
    */
   private String _ContrEPost = "";
            
   /**
    * Registered EPost member variable.
    */
   private String _RegEPost = "";
            
   /**
    * Annual Report EPost member variable.
    */
   private String _AnnlRptsEPost = "";
            
   /**
    * Prospectus EPost member variable.
    */
   private String _ProspEPost = "";
            
   /**
    * Beneficiary EPost member variable.
    */
   private String _BenEPost = "";
            
   /**
    * Statement EPost member variable.
    */
   private String _StmtEPost = "";
            
   /**
    * Duplicate Statement EPost member variable.
    */
   private String _DupStmtEPost = "";
            
   /**
    * NF Confirm EPost member variable.
    */
   private String _NFConfEPost = "";
            
   /**
    * Txn Confirm EPost member variable.
    */
   private String _TxnConfEPost = "";
            
   /**
    * Duplicate Confirm EPost member variable.
    */
   private String _DupConfEPost = "";
            
   /**
    * Semi Annual Report EPost member variable.
    */
   private String _SmAnnlRptEPost = "";
            
   /**
    * Contribution Receipt Suppress member variable.
    */
   private Boolean _ContrRSuppress = new Boolean(false);
            
   /**
    * Contribution Receipt  Waive member variable.
    */
   private Boolean _ContrRWaive = new Boolean(false);
            
   /**
    * Contribution Receipt Mail member variable.
    */
   private String _ContrRMail = "";
            
   /**
    * Contribution Receipt Fax member variable.
    */
   private String _ContrRFax = "";
            
   /**
    * Contribution Receipt CD member variable.
    */
   private String _ContrRCD = "";
            
   /**
    * Contribution Receipt Email member variable.
    */
   private String _ContrREmail = "";
            
   /**
    * Contribution Receipt EPost member variable.
    */
   private String _ContrREPost = "";
            
   /**
    * Contribution Receipt Address Code member variable.
    */
   private String _ContrRAddr = "";
            
   /**
    * Contribution Receipt On Hold member variable.
    */
   private Boolean _ContrRHold = new Boolean(false);
            
   /**
    * Semi-Annual MRFP Address Code member variable.
    */
   private String _SmAnnlMRFPAddr = "";
            
   /**
    * Semi-Annual MRFP Suppress member variable.
    */
   private Boolean _SmAnnlMRFPSuppress = new Boolean(false);
            
   /**
    * Semi-Annual MRFP Waive member variable.
    */
   private Boolean _SmAnnlMRFPWaive = new Boolean(false);
            
   /**
    * Semi-Annual MRFP Hold member variable.
    */
   private Boolean _SmAnnlMRFPHold = new Boolean(false);
            
   /**
    * Semi-Annual MRFP Mail member variable.
    */
   private String _SmAnnlMRFPMail = "";
            
   /**
    * Semi-Annual MRFP Fax member variable.
    */
   private String _SmAnnlMRFPFax = "";
            
   /**
    * Semi-Annual MRFP CD member variable.
    */
   private String _SmAnnlMRFPCD = "";
            
   /**
    * Semi-Annual MRFP Email member variable.
    */
   private String _SmAnnlMRFPEmail = "";
            
   /**
    * Semi-Annual MRFP ePost member variable.
    */
   private String _SmAnnlMRFPePost = "";
            
   /**
    * Semi-Annual MRFP Authorization member variable.
    */
   private String _SmAnnlMRFPAuth = "";
            
   /**
    * Annual MRFP Address Code member variable.
    */
   private String _AnnlMRFPAddr = "";
            
   /**
    * Annual MRFP Suppress member variable.
    */
   private Boolean _AnnlMRFPSuppress = new Boolean(false);
            
   /**
    * Annual MRFP Waive member variable.
    */
   private Boolean _AnnlMRFPWaive = new Boolean(false);
            
   /**
    * Annual MRFP Hold member variable.
    */
   private Boolean _AnnlMRFPHold = new Boolean(false);
            
   /**
    * Annual MRFP Mail member variable.
    */
   private String _AnnlMRFPMail = "";
            
   /**
    * Annual MRFP Fax member variable.
    */
   private String _AnnlMRFPFax = "";
            
   /**
    * Annual MRFP CD member variable.
    */
   private String _AnnlMRFPCD = "";
            
   /**
    * Annual MRFP Email member variable.
    */
   private String _AnnlMRFPEmail = "";
            
   /**
    * Annual MRFP ePost member variable.
    */
   private String _AnnlMRFPePost = "";
            
   /**
    * Annual MRFP Authorization member variable.
    */
   private String _AnnlMRFPAuth = "";
            
   /**
    * Tax Authorization member variable.
    */
   private String _TaxAuth = "";
            
   /**
    * Letter Authorization member variable.
    */
   private String _LetAuth = "";
            
   /**
    * Certificate Authorization member variable.
    */
   private String _CertAuth = "";
            
   /**
    * Dividend Confirm Authorization member variable.
    */
   private String _DivConfAuth = "";
            
   /**
    * Dividend Cheque Authorization member variable.
    */
   private String _DivChqAuth = "";
            
   /**
    * Contract Authorization member variable.
    */
   private String _ContrAuth = "";
            
   /**
    * Register Authorization member variable.
    */
   private String _RegAuth = "";
            
   /**
    * Annual Reports Authorization member variable.
    */
   private String _AnnlRptsAuth = "";
            
   /**
    * Prospectus Authorization member variable.
    */
   private String _ProspAuth = "";
            
   /**
    * Beneficial Authorization member variable.
    */
   private String _BenAuth = "";
            
   /**
    * Statement Authorization member variable.
    */
   private String _StmtAuth = "";
            
   /**
    * Duplicate Statement Authorization member variable.
    */
   private String _DupStmtAuth = "";
            
   /**
    * Non Financial Confirmation Authorization member variable.
    */
   private String _NFConfAuth = "";
            
   /**
    * Transaction Confirmation Authorization member variable.
    */
   private String _TxnConfAuth = "";
            
   /**
    * Duplicate Confirmation Authorization member variable.
    */
   private String _DupConfAuth = "";
            
   /**
    * Semi-Annual Report Authorization member variable.
    */
   private String _SmAnnlRptAuth = "";
            
   /**
    * Contribution Receipt Authorization member variable.
    */
   private String _ContrRAuth = "";
            
   /**
    * Statement Frequency member variable.
    */
   private String _StmtFrequency = "";
            

   /**
    * Constructs the ShrMailUpdRequest object.
    * 
    */
   ShrMailUpdRequest()
   {
      super ( 114 );
   }

   /**
    * Constructs the ShrMailUpdRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   ShrMailUpdRequest( String hostEncoding )
   {
      super ( 114, hostEncoding );
   }

   /**
    * Sets the Session Id field for the request.
    * 
    * @param value  Value that the Session Id will be set to.
    */
   public final void setSessionId( String value )
   {
      assertUnsent();
      _SessionId = value;
   }
	
   /**
    * Sets the User Id field for the request.
    * 
    * @param value  Value that the User Id will be set to.
    */
   public final void setUser_Id( String value )
   {
      assertUnsent();
      _User_Id = value;
   }
	
   /**
    * Sets the Language Code field for the request.
    * 
    * @param value  Value that the Language Code will be set to.
    */
   public final void setLanguageCode( String value )
   {
      assertUnsent();
      _LanguageCode = value;
   }
	
   /**
    * Sets the Company Id field for the request.
    * 
    * @param value  Value that the Company Id will be set to.
    */
   public final void setCompanyId( String value )
   {
      assertUnsent();
      _CompanyId = value;
   }
	
   /**
    * Sets the Run Mode field for the request.
    * 
    * @param value  Value that the Run Mode will be set to.
    */
   public final void setRunMode( String value )
   {
      assertUnsent();
      _RunMode = value;
   }
	
   /**
    * Sets the Registered Address field for the request.
    * 
    * @param value  Value that the Registered Address will be set to.
    */
   public final void setRegAddr( String value )
   {
      assertUnsent();
      _RegAddr = value;
   }
	
   /**
    * Sets the Dividend  Confirmation field for the request.
    * 
    * @param value  Value that the Dividend  Confirmation will be set to.
    */
   public final void setDivConfAddr( String value )
   {
      assertUnsent();
      _DivConfAddr = value;
   }
	
   /**
    * Sets the Dividend Cheque field for the request.
    * 
    * @param value  Value that the Dividend Cheque will be set to.
    */
   public final void setDivChqAddr( String value )
   {
      assertUnsent();
      _DivChqAddr = value;
   }
	
   /**
    * Sets the Transaction Confirmation field for the request.
    * 
    * @param value  Value that the Transaction Confirmation will be set to.
    */
   public final void setTxnConfAddr( String value )
   {
      assertUnsent();
      _TxnConfAddr = value;
   }
	
   /**
    * Sets the Duplicate Transaction Confirmation field for the request.
    * 
    * @param value  Value that the Duplicate Transaction Confirmation will be set to.
    */
   public final void setDupConfAddr( String value )
   {
      assertUnsent();
      _DupConfAddr = value;
   }
	
   /**
    * Sets the Statement field for the request.
    * 
    * @param value  Value that the Statement will be set to.
    */
   public final void setStmtAddr( String value )
   {
      assertUnsent();
      _StmtAddr = value;
   }
	
   /**
    * Sets the Duplicate Statement field for the request.
    * 
    * @param value  Value that the Duplicate Statement will be set to.
    */
   public final void setDupStmtAddr( String value )
   {
      assertUnsent();
      _DupStmtAddr = value;
   }
	
   /**
    * Sets the Certificate field for the request.
    * 
    * @param value  Value that the Certificate will be set to.
    */
   public final void setCertAddr( String value )
   {
      assertUnsent();
      _CertAddr = value;
   }
	
   /**
    * Sets the Tax Receipt field for the request.
    * 
    * @param value  Value that the Tax Receipt will be set to.
    */
   public final void setTaxAddr( String value )
   {
      assertUnsent();
      _TaxAddr = value;
   }
	
   /**
    * Sets the Letters field for the request.
    * 
    * @param value  Value that the Letters will be set to.
    */
   public final void setLetAddr( String value )
   {
      assertUnsent();
      _LetAddr = value;
   }
	
   /**
    * Sets the Beneficial Owner field for the request.
    * 
    * @param value  Value that the Beneficial Owner will be set to.
    */
   public final void setBenAddr( String value )
   {
      assertUnsent();
      _BenAddr = value;
   }
	
   /**
    * Sets the Number of Duplicate Confirms field for the request.
    * 
    * @param value  Value that the Number of Duplicate Confirms will be set to.
    */
   public final void setDupConfCopies( Integer value )
   {
      assertUnsent();
      _DupConfCopies = value;
   }
	
   /**
    * Sets the Number of Duplicate Statements field for the request.
    * 
    * @param value  Value that the Number of Duplicate Statements will be set to.
    */
   public final void setDupStmtCopies( Integer value )
   {
      assertUnsent();
      _DupStmtCopies = value;
   }
	
   /**
    * Sets the Registered Address Use on Hold field for the request.
    * 
    * @param value  Value that the Registered Address Use on Hold will be set to.
    */
   public final void setRegOnHold( Boolean value )
   {
      assertUnsent();
      _RegOnHold = value;
   }
	
   /**
    * Sets the Dividend  Confirmation Addr Use on Hold field for the request.
    * 
    * @param value  Value that the Dividend  Confirmation Addr Use on Hold will be set to.
    */
   public final void setDivConfOnHold( Boolean value )
   {
      assertUnsent();
      _DivConfOnHold = value;
   }
	
   /**
    * Sets the Dividend Cheque Addr Use On Hold field for the request.
    * 
    * @param value  Value that the Dividend Cheque Addr Use On Hold will be set to.
    */
   public final void setDivChqOnHold( Boolean value )
   {
      assertUnsent();
      _DivChqOnHold = value;
   }
	
   /**
    * Sets the Transaction Confirm Addr Use on Hold field for the request.
    * 
    * @param value  Value that the Transaction Confirm Addr Use on Hold will be set to.
    */
   public final void setTxnConfOnHold( Boolean value )
   {
      assertUnsent();
      _TxnConfOnHold = value;
   }
	
   /**
    * Sets the Duplicate Confirm Addr Use On Hold field for the request.
    * 
    * @param value  Value that the Duplicate Confirm Addr Use On Hold will be set to.
    */
   public final void setDupConfOnHold( Boolean value )
   {
      assertUnsent();
      _DupConfOnHold = value;
   }
	
   /**
    * Sets the Statement Addr Use On Hold field for the request.
    * 
    * @param value  Value that the Statement Addr Use On Hold will be set to.
    */
   public final void setStmtOnHold( Boolean value )
   {
      assertUnsent();
      _StmtOnHold = value;
   }
	
   /**
    * Sets the Duplicate Statement Addr Use on Hold field for the request.
    * 
    * @param value  Value that the Duplicate Statement Addr Use on Hold will be set to.
    */
   public final void setDupStmtOnHold( Boolean value )
   {
      assertUnsent();
      _DupStmtOnHold = value;
   }
	
   /**
    * Sets the Certifidate Addr Use On Hold field for the request.
    * 
    * @param value  Value that the Certifidate Addr Use On Hold will be set to.
    */
   public final void setCertOnHold( Boolean value )
   {
      assertUnsent();
      _CertOnHold = value;
   }
	
   /**
    * Sets the Tax Receipts Addr Use On Hold field for the request.
    * 
    * @param value  Value that the Tax Receipts Addr Use On Hold will be set to.
    */
   public final void setTaxOnHold( Boolean value )
   {
      assertUnsent();
      _TaxOnHold = value;
   }
	
   /**
    * Sets the Letters Addr Use On Hold field for the request.
    * 
    * @param value  Value that the Letters Addr Use On Hold will be set to.
    */
   public final void setLetOnHold( Boolean value )
   {
      assertUnsent();
      _LetOnHold = value;
   }
	
   /**
    * Sets the Beneficial Addr Use On Hold field for the request.
    * 
    * @param value  Value that the Beneficial Addr Use On Hold will be set to.
    */
   public final void setBenOnHold( Boolean value )
   {
      assertUnsent();
      _BenOnHold = value;
   }
	
   /**
    * Sets the Servicing Agent for Transaction Confirms field for the request.
    * 
    * @param value  Value that the Servicing Agent for Transaction Confirms will be set to.
    */
   public final void setSATxnConfCode( String value )
   {
      assertUnsent();
      _SATxnConfCode = value;
   }
	
   /**
    * Sets the Servicing Agent for Dividend  Confirms field for the request.
    * 
    * @param value  Value that the Servicing Agent for Dividend  Confirms will be set to.
    */
   public final void setSADivConfCode( String value )
   {
      assertUnsent();
      _SADivConfCode = value;
   }
	
   /**
    * Sets the Servicing Agent for Letters field for the request.
    * 
    * @param value  Value that the Servicing Agent for Letters will be set to.
    */
   public final void setSALettersCode( String value )
   {
      assertUnsent();
      _SALettersCode = value;
   }
	
   /**
    * Sets the Acct Table Version Number field for the request.
    * 
    * @param value  Value that the Acct Table Version Number will be set to.
    */
   public final void setAcctMstrVer( Integer value )
   {
      assertUnsent();
      _AcctMstrVer = value;
   }
	
   /**
    * Sets the Non Financial  Address field for the request.
    * 
    * @param value  Value that the Non Financial  Address will be set to.
    */
   public final void setNFCAddr( String value )
   {
      assertUnsent();
      _NFCAddr = value;
   }
	
   /**
    * Sets the Non Financial Addr on Hold field for the request.
    * 
    * @param value  Value that the Non Financial Addr on Hold will be set to.
    */
   public final void setNFConHold( Boolean value )
   {
      assertUnsent();
      _NFConHold = value;
   }
	
   /**
    * Sets the Account Number field for the request.
    * 
    * @param value  Value that the Account Number will be set to.
    */
   public final void setAccountNum( String value )
   {
      assertUnsent();
      _AccountNum = value;
   }
	
   /**
    * Sets the Acct-Mstr record id field for the request.
    * 
    * @param value  Value that the Acct-Mstr record id will be set to.
    */
   public final void setAcctMstrRid( Integer value )
   {
      assertUnsent();
      _AcctMstrRid = value;
   }
	
   /**
    * Sets the Contract Address Code field for the request.
    * 
    * @param value  Value that the Contract Address Code will be set to.
    */
   public final void setContrAddr( String value )
   {
      assertUnsent();
      _ContrAddr = value;
   }
	
   /**
    * Sets the Contract Address Use on Hold field for the request.
    * 
    * @param value  Value that the Contract Address Use on Hold will be set to.
    */
   public final void setContrHold( Boolean value )
   {
      assertUnsent();
      _ContrHold = value;
   }
	
   /**
    * Sets the Annual Reports Address Code field for the request.
    * 
    * @param value  Value that the Annual Reports Address Code will be set to.
    */
   public final void setAnnlRptsAddr( String value )
   {
      assertUnsent();
      _AnnlRptsAddr = value;
   }
	
   /**
    * Sets the Annual Reports Address Use on Hold field for the request.
    * 
    * @param value  Value that the Annual Reports Address Use on Hold will be set to.
    */
   public final void setAnnlRptsHold( Boolean value )
   {
      assertUnsent();
      _AnnlRptsHold = value;
   }
	
   /**
    * Sets the Prospectus Address Code field for the request.
    * 
    * @param value  Value that the Prospectus Address Code will be set to.
    */
   public final void setProspAddr( String value )
   {
      assertUnsent();
      _ProspAddr = value;
   }
	
   /**
    * Sets the Prospectus Address Use on Hold field for the request.
    * 
    * @param value  Value that the Prospectus Address Use on Hold will be set to.
    */
   public final void setProspHold( Boolean value )
   {
      assertUnsent();
      _ProspHold = value;
   }
	
   /**
    * Sets the Tax Suppress field for the request.
    * 
    * @param value  Value that the Tax Suppress will be set to.
    */
   public final void setTaxSuppress( Boolean value )
   {
      assertUnsent();
      _TaxSuppress = value;
   }
	
   /**
    * Sets the Tax Waive field for the request.
    * 
    * @param value  Value that the Tax Waive will be set to.
    */
   public final void setTaxWaive( Boolean value )
   {
      assertUnsent();
      _TaxWaive = value;
   }
	
   /**
    * Sets the Tax Mail field for the request.
    * 
    * @param value  Value that the Tax Mail will be set to.
    */
   public final void setTaxMail( String value )
   {
      assertUnsent();
      _TaxMail = value;
   }
	
   /**
    * Sets the Tax Fax field for the request.
    * 
    * @param value  Value that the Tax Fax will be set to.
    */
   public final void setTaxFax( String value )
   {
      assertUnsent();
      _TaxFax = value;
   }
	
   /**
    * Sets the Tax CD field for the request.
    * 
    * @param value  Value that the Tax CD will be set to.
    */
   public final void setTaxCD( String value )
   {
      assertUnsent();
      _TaxCD = value;
   }
	
   /**
    * Sets the Tax Email field for the request.
    * 
    * @param value  Value that the Tax Email will be set to.
    */
   public final void setTaxEmail( String value )
   {
      assertUnsent();
      _TaxEmail = value;
   }
	
   /**
    * Sets the Letter Suppress field for the request.
    * 
    * @param value  Value that the Letter Suppress will be set to.
    */
   public final void setLetSuppress( Boolean value )
   {
      assertUnsent();
      _LetSuppress = value;
   }
	
   /**
    * Sets the Letter Waive field for the request.
    * 
    * @param value  Value that the Letter Waive will be set to.
    */
   public final void setLetWaive( Boolean value )
   {
      assertUnsent();
      _LetWaive = value;
   }
	
   /**
    * Sets the Letter Mail field for the request.
    * 
    * @param value  Value that the Letter Mail will be set to.
    */
   public final void setLetMail( String value )
   {
      assertUnsent();
      _LetMail = value;
   }
	
   /**
    * Sets the Letter Fax field for the request.
    * 
    * @param value  Value that the Letter Fax will be set to.
    */
   public final void setLetFax( String value )
   {
      assertUnsent();
      _LetFax = value;
   }
	
   /**
    * Sets the Letter CD field for the request.
    * 
    * @param value  Value that the Letter CD will be set to.
    */
   public final void setLetCD( String value )
   {
      assertUnsent();
      _LetCD = value;
   }
	
   /**
    * Sets the Letter Email field for the request.
    * 
    * @param value  Value that the Letter Email will be set to.
    */
   public final void setLetEmail( String value )
   {
      assertUnsent();
      _LetEmail = value;
   }
	
   /**
    * Sets the Cert Suppress field for the request.
    * 
    * @param value  Value that the Cert Suppress will be set to.
    */
   public final void setCertSuppress( Boolean value )
   {
      assertUnsent();
      _CertSuppress = value;
   }
	
   /**
    * Sets the Cert Waive field for the request.
    * 
    * @param value  Value that the Cert Waive will be set to.
    */
   public final void setCertWaive( Boolean value )
   {
      assertUnsent();
      _CertWaive = value;
   }
	
   /**
    * Sets the Cert Mail field for the request.
    * 
    * @param value  Value that the Cert Mail will be set to.
    */
   public final void setCertMail( String value )
   {
      assertUnsent();
      _CertMail = value;
   }
	
   /**
    * Sets the Cert CD field for the request.
    * 
    * @param value  Value that the Cert CD will be set to.
    */
   public final void setCertCD( String value )
   {
      assertUnsent();
      _CertCD = value;
   }
	
   /**
    * Sets the Cert Email field for the request.
    * 
    * @param value  Value that the Cert Email will be set to.
    */
   public final void setCertEmail( String value )
   {
      assertUnsent();
      _CertEmail = value;
   }
	
   /**
    * Sets the Cert Fax field for the request.
    * 
    * @param value  Value that the Cert Fax will be set to.
    */
   public final void setCertFax( String value )
   {
      assertUnsent();
      _CertFax = value;
   }
	
   /**
    * Sets the Div Conf Suppress field for the request.
    * 
    * @param value  Value that the Div Conf Suppress will be set to.
    */
   public final void setDivConfSuppress( Boolean value )
   {
      assertUnsent();
      _DivConfSuppress = value;
   }
	
   /**
    * Sets the Div Conf Waive field for the request.
    * 
    * @param value  Value that the Div Conf Waive will be set to.
    */
   public final void setDivConfWaive( Boolean value )
   {
      assertUnsent();
      _DivConfWaive = value;
   }
	
   /**
    * Sets the Div Conf Mail field for the request.
    * 
    * @param value  Value that the Div Conf Mail will be set to.
    */
   public final void setDivConfMail( String value )
   {
      assertUnsent();
      _DivConfMail = value;
   }
	
   /**
    * Sets the Div Conf Fax field for the request.
    * 
    * @param value  Value that the Div Conf Fax will be set to.
    */
   public final void setDivConfFax( String value )
   {
      assertUnsent();
      _DivConfFax = value;
   }
	
   /**
    * Sets the Div Conf CD field for the request.
    * 
    * @param value  Value that the Div Conf CD will be set to.
    */
   public final void setDivConfCD( String value )
   {
      assertUnsent();
      _DivConfCD = value;
   }
	
   /**
    * Sets the Div Conf Email field for the request.
    * 
    * @param value  Value that the Div Conf Email will be set to.
    */
   public final void setDivConfEmail( String value )
   {
      assertUnsent();
      _DivConfEmail = value;
   }
	
   /**
    * Sets the Div Chq Suppress field for the request.
    * 
    * @param value  Value that the Div Chq Suppress will be set to.
    */
   public final void setDivChqSuppress( Boolean value )
   {
      assertUnsent();
      _DivChqSuppress = value;
   }
	
   /**
    * Sets the Div Chq Waive field for the request.
    * 
    * @param value  Value that the Div Chq Waive will be set to.
    */
   public final void setDivChqWaive( Boolean value )
   {
      assertUnsent();
      _DivChqWaive = value;
   }
	
   /**
    * Sets the Div Chq Mail field for the request.
    * 
    * @param value  Value that the Div Chq Mail will be set to.
    */
   public final void setDivChqMail( String value )
   {
      assertUnsent();
      _DivChqMail = value;
   }
	
   /**
    * Sets the Div Chq Fax field for the request.
    * 
    * @param value  Value that the Div Chq Fax will be set to.
    */
   public final void setDivChqFax( String value )
   {
      assertUnsent();
      _DivChqFax = value;
   }
	
   /**
    * Sets the Div Chq CD field for the request.
    * 
    * @param value  Value that the Div Chq CD will be set to.
    */
   public final void setDivChqCD( String value )
   {
      assertUnsent();
      _DivChqCD = value;
   }
	
   /**
    * Sets the Div Chq Email field for the request.
    * 
    * @param value  Value that the Div Chq Email will be set to.
    */
   public final void setDivChqEmail( String value )
   {
      assertUnsent();
      _DivChqEmail = value;
   }
	
   /**
    * Sets the Reg Suppress field for the request.
    * 
    * @param value  Value that the Reg Suppress will be set to.
    */
   public final void setRegSuppress( Boolean value )
   {
      assertUnsent();
      _RegSuppress = value;
   }
	
   /**
    * Sets the Reg Waive field for the request.
    * 
    * @param value  Value that the Reg Waive will be set to.
    */
   public final void setRegWaive( Boolean value )
   {
      assertUnsent();
      _RegWaive = value;
   }
	
   /**
    * Sets the Reg Mail field for the request.
    * 
    * @param value  Value that the Reg Mail will be set to.
    */
   public final void setRegMail( String value )
   {
      assertUnsent();
      _RegMail = value;
   }
	
   /**
    * Sets the Reg Fax field for the request.
    * 
    * @param value  Value that the Reg Fax will be set to.
    */
   public final void setRegFax( String value )
   {
      assertUnsent();
      _RegFax = value;
   }
	
   /**
    * Sets the Reg CD field for the request.
    * 
    * @param value  Value that the Reg CD will be set to.
    */
   public final void setRegCd( String value )
   {
      assertUnsent();
      _RegCd = value;
   }
	
   /**
    * Sets the Reg Email field for the request.
    * 
    * @param value  Value that the Reg Email will be set to.
    */
   public final void setRegEmail( String value )
   {
      assertUnsent();
      _RegEmail = value;
   }
	
   /**
    * Sets the Annual Reports Suppress field for the request.
    * 
    * @param value  Value that the Annual Reports Suppress will be set to.
    */
   public final void setAnnlRptsSuppress( Boolean value )
   {
      assertUnsent();
      _AnnlRptsSuppress = value;
   }
	
   /**
    * Sets the Annual Reports Waive field for the request.
    * 
    * @param value  Value that the Annual Reports Waive will be set to.
    */
   public final void setAnnlRptsWaive( Boolean value )
   {
      assertUnsent();
      _AnnlRptsWaive = value;
   }
	
   /**
    * Sets the Annual Reports Mail field for the request.
    * 
    * @param value  Value that the Annual Reports Mail will be set to.
    */
   public final void setAnnlRptsMail( String value )
   {
      assertUnsent();
      _AnnlRptsMail = value;
   }
	
   /**
    * Sets the Annual Reports Fax field for the request.
    * 
    * @param value  Value that the Annual Reports Fax will be set to.
    */
   public final void setAnnlRptsFax( String value )
   {
      assertUnsent();
      _AnnlRptsFax = value;
   }
	
   /**
    * Sets the Annual Reports CD field for the request.
    * 
    * @param value  Value that the Annual Reports CD will be set to.
    */
   public final void setAnnlRptsCD( String value )
   {
      assertUnsent();
      _AnnlRptsCD = value;
   }
	
   /**
    * Sets the Annual Reports Email field for the request.
    * 
    * @param value  Value that the Annual Reports Email will be set to.
    */
   public final void setAnnlRptsEmail( String value )
   {
      assertUnsent();
      _AnnlRptsEmail = value;
   }
	
   /**
    * Sets the Prosp Suppress field for the request.
    * 
    * @param value  Value that the Prosp Suppress will be set to.
    */
   public final void setProspSuppress( Boolean value )
   {
      assertUnsent();
      _ProspSuppress = value;
   }
	
   /**
    * Sets the Prosp Waive field for the request.
    * 
    * @param value  Value that the Prosp Waive will be set to.
    */
   public final void setProspWaive( Boolean value )
   {
      assertUnsent();
      _ProspWaive = value;
   }
	
   /**
    * Sets the Prosp Mail field for the request.
    * 
    * @param value  Value that the Prosp Mail will be set to.
    */
   public final void setProspMail( String value )
   {
      assertUnsent();
      _ProspMail = value;
   }
	
   /**
    * Sets the Prosp Fax field for the request.
    * 
    * @param value  Value that the Prosp Fax will be set to.
    */
   public final void setProspFax( String value )
   {
      assertUnsent();
      _ProspFax = value;
   }
	
   /**
    * Sets the Prosp CD field for the request.
    * 
    * @param value  Value that the Prosp CD will be set to.
    */
   public final void setProspCd( String value )
   {
      assertUnsent();
      _ProspCd = value;
   }
	
   /**
    * Sets the Prosp Email field for the request.
    * 
    * @param value  Value that the Prosp Email will be set to.
    */
   public final void setProspEmail( String value )
   {
      assertUnsent();
      _ProspEmail = value;
   }
	
   /**
    * Sets the Ben Suppress field for the request.
    * 
    * @param value  Value that the Ben Suppress will be set to.
    */
   public final void setBenSuppress( Boolean value )
   {
      assertUnsent();
      _BenSuppress = value;
   }
	
   /**
    * Sets the Ben Waive field for the request.
    * 
    * @param value  Value that the Ben Waive will be set to.
    */
   public final void setBenWaive( Boolean value )
   {
      assertUnsent();
      _BenWaive = value;
   }
	
   /**
    * Sets the Ben Mail field for the request.
    * 
    * @param value  Value that the Ben Mail will be set to.
    */
   public final void setBenMail( String value )
   {
      assertUnsent();
      _BenMail = value;
   }
	
   /**
    * Sets the Ben Fax field for the request.
    * 
    * @param value  Value that the Ben Fax will be set to.
    */
   public final void setBenFax( String value )
   {
      assertUnsent();
      _BenFax = value;
   }
	
   /**
    * Sets the Ben CD field for the request.
    * 
    * @param value  Value that the Ben CD will be set to.
    */
   public final void setBenCD( String value )
   {
      assertUnsent();
      _BenCD = value;
   }
	
   /**
    * Sets the Ben Email field for the request.
    * 
    * @param value  Value that the Ben Email will be set to.
    */
   public final void setBenEmail( String value )
   {
      assertUnsent();
      _BenEmail = value;
   }
	
   /**
    * Sets the Stmt Suppress field for the request.
    * 
    * @param value  Value that the Stmt Suppress will be set to.
    */
   public final void setStmtSuppress( Boolean value )
   {
      assertUnsent();
      _StmtSuppress = value;
   }
	
   /**
    * Sets the Stmt Waive field for the request.
    * 
    * @param value  Value that the Stmt Waive will be set to.
    */
   public final void setStmtWaive( Boolean value )
   {
      assertUnsent();
      _StmtWaive = value;
   }
	
   /**
    * Sets the Stmt Mail field for the request.
    * 
    * @param value  Value that the Stmt Mail will be set to.
    */
   public final void setStmtMail( String value )
   {
      assertUnsent();
      _StmtMail = value;
   }
	
   /**
    * Sets the Stmt Fax field for the request.
    * 
    * @param value  Value that the Stmt Fax will be set to.
    */
   public final void setStmtFax( String value )
   {
      assertUnsent();
      _StmtFax = value;
   }
	
   /**
    * Sets the Stmt Cd field for the request.
    * 
    * @param value  Value that the Stmt Cd will be set to.
    */
   public final void setStmtCD( String value )
   {
      assertUnsent();
      _StmtCD = value;
   }
	
   /**
    * Sets the Stmt Email field for the request.
    * 
    * @param value  Value that the Stmt Email will be set to.
    */
   public final void setStmtEmail( String value )
   {
      assertUnsent();
      _StmtEmail = value;
   }
	
   /**
    * Sets the Dup Stmt Suppress field for the request.
    * 
    * @param value  Value that the Dup Stmt Suppress will be set to.
    */
   public final void setDupStmtSuppress( Boolean value )
   {
      assertUnsent();
      _DupStmtSuppress = value;
   }
	
   /**
    * Sets the Dup Stmt Waive field for the request.
    * 
    * @param value  Value that the Dup Stmt Waive will be set to.
    */
   public final void setDupStmtWaive( Boolean value )
   {
      assertUnsent();
      _DupStmtWaive = value;
   }
	
   /**
    * Sets the Dup Stmt Mail field for the request.
    * 
    * @param value  Value that the Dup Stmt Mail will be set to.
    */
   public final void setDupStmtMail( String value )
   {
      assertUnsent();
      _DupStmtMail = value;
   }
	
   /**
    * Sets the Dup Stmt Fax field for the request.
    * 
    * @param value  Value that the Dup Stmt Fax will be set to.
    */
   public final void setDupStmtFax( String value )
   {
      assertUnsent();
      _DupStmtFax = value;
   }
	
   /**
    * Sets the Dup Stmt CD field for the request.
    * 
    * @param value  Value that the Dup Stmt CD will be set to.
    */
   public final void setDupStmtCD( String value )
   {
      assertUnsent();
      _DupStmtCD = value;
   }
	
   /**
    * Sets the Dup Stmt Email field for the request.
    * 
    * @param value  Value that the Dup Stmt Email will be set to.
    */
   public final void setDupStmtEmail( String value )
   {
      assertUnsent();
      _DupStmtEmail = value;
   }
	
   /**
    * Sets the NF Conf Suppress field for the request.
    * 
    * @param value  Value that the NF Conf Suppress will be set to.
    */
   public final void setNFConfSuppress( Boolean value )
   {
      assertUnsent();
      _NFConfSuppress = value;
   }
	
   /**
    * Sets the NF Conf Waive field for the request.
    * 
    * @param value  Value that the NF Conf Waive will be set to.
    */
   public final void setNFConfWaive( Boolean value )
   {
      assertUnsent();
      _NFConfWaive = value;
   }
	
   /**
    * Sets the NF Conf Mail field for the request.
    * 
    * @param value  Value that the NF Conf Mail will be set to.
    */
   public final void setNFConfMail( String value )
   {
      assertUnsent();
      _NFConfMail = value;
   }
	
   /**
    * Sets the NF Conf Fax field for the request.
    * 
    * @param value  Value that the NF Conf Fax will be set to.
    */
   public final void setNFConfFax( String value )
   {
      assertUnsent();
      _NFConfFax = value;
   }
	
   /**
    * Sets the NF Conf CD field for the request.
    * 
    * @param value  Value that the NF Conf CD will be set to.
    */
   public final void setNFConfCD( String value )
   {
      assertUnsent();
      _NFConfCD = value;
   }
	
   /**
    * Sets the NF Conf Email field for the request.
    * 
    * @param value  Value that the NF Conf Email will be set to.
    */
   public final void setNFConfEmail( String value )
   {
      assertUnsent();
      _NFConfEmail = value;
   }
	
   /**
    * Sets the Txn Conf Suppress field for the request.
    * 
    * @param value  Value that the Txn Conf Suppress will be set to.
    */
   public final void setTxnConfSuppress( Boolean value )
   {
      assertUnsent();
      _TxnConfSuppress = value;
   }
	
   /**
    * Sets the Txn Conf Waive field for the request.
    * 
    * @param value  Value that the Txn Conf Waive will be set to.
    */
   public final void setTxnConfWaive( Boolean value )
   {
      assertUnsent();
      _TxnConfWaive = value;
   }
	
   /**
    * Sets the Txn Conf Mail field for the request.
    * 
    * @param value  Value that the Txn Conf Mail will be set to.
    */
   public final void setTxnConfMail( String value )
   {
      assertUnsent();
      _TxnConfMail = value;
   }
	
   /**
    * Sets the Txn Conf Fax field for the request.
    * 
    * @param value  Value that the Txn Conf Fax will be set to.
    */
   public final void setTxnConfFax( String value )
   {
      assertUnsent();
      _TxnConfFax = value;
   }
	
   /**
    * Sets the Txn Conf CD field for the request.
    * 
    * @param value  Value that the Txn Conf CD will be set to.
    */
   public final void setTxnConfCD( String value )
   {
      assertUnsent();
      _TxnConfCD = value;
   }
	
   /**
    * Sets the Txn Conf Email field for the request.
    * 
    * @param value  Value that the Txn Conf Email will be set to.
    */
   public final void setTxnConfEmail( String value )
   {
      assertUnsent();
      _TxnConfEmail = value;
   }
	
   /**
    * Sets the Dup Conf Suppress field for the request.
    * 
    * @param value  Value that the Dup Conf Suppress will be set to.
    */
   public final void setDupConfSuppress( Boolean value )
   {
      assertUnsent();
      _DupConfSuppress = value;
   }
	
   /**
    * Sets the Dup Conf Waive field for the request.
    * 
    * @param value  Value that the Dup Conf Waive will be set to.
    */
   public final void setDupConfWaive( Boolean value )
   {
      assertUnsent();
      _DupConfWaive = value;
   }
	
   /**
    * Sets the Dup Conf Mail field for the request.
    * 
    * @param value  Value that the Dup Conf Mail will be set to.
    */
   public final void setDupConfMail( String value )
   {
      assertUnsent();
      _DupConfMail = value;
   }
	
   /**
    * Sets the Dup Conf Fax field for the request.
    * 
    * @param value  Value that the Dup Conf Fax will be set to.
    */
   public final void setDupConfFax( String value )
   {
      assertUnsent();
      _DupConfFax = value;
   }
	
   /**
    * Sets the Dup Conf CD field for the request.
    * 
    * @param value  Value that the Dup Conf CD will be set to.
    */
   public final void setDupConfCd( String value )
   {
      assertUnsent();
      _DupConfCd = value;
   }
	
   /**
    * Sets the Dup Conf Email field for the request.
    * 
    * @param value  Value that the Dup Conf Email will be set to.
    */
   public final void setDupConfEmail( String value )
   {
      assertUnsent();
      _DupConfEmail = value;
   }
	
   /**
    * Sets the ContrSuppress field for the request.
    * 
    * @param value  Value that the ContrSuppress will be set to.
    */
   public final void setContrSuppress( Boolean value )
   {
      assertUnsent();
      _ContrSuppress = value;
   }
	
   /**
    * Sets the Contr Waive field for the request.
    * 
    * @param value  Value that the Contr Waive will be set to.
    */
   public final void setContrWaive( Boolean value )
   {
      assertUnsent();
      _ContrWaive = value;
   }
	
   /**
    * Sets the Contr Mail field for the request.
    * 
    * @param value  Value that the Contr Mail will be set to.
    */
   public final void setContrMail( String value )
   {
      assertUnsent();
      _ContrMail = value;
   }
	
   /**
    * Sets the Contr Fax field for the request.
    * 
    * @param value  Value that the Contr Fax will be set to.
    */
   public final void setContrFax( String value )
   {
      assertUnsent();
      _ContrFax = value;
   }
	
   /**
    * Sets the Contr CD field for the request.
    * 
    * @param value  Value that the Contr CD will be set to.
    */
   public final void setContrCD( String value )
   {
      assertUnsent();
      _ContrCD = value;
   }
	
   /**
    * Sets the Contr Email field for the request.
    * 
    * @param value  Value that the Contr Email will be set to.
    */
   public final void setContrEmail( String value )
   {
      assertUnsent();
      _ContrEmail = value;
   }
	
   /**
    * Sets the Semi Annual Report Suppress field for the request.
    * 
    * @param value  Value that the Semi Annual Report Suppress will be set to.
    */
   public final void setSmAnnlRptSuppress( Boolean value )
   {
      assertUnsent();
      _SmAnnlRptSuppress = value;
   }
	
   /**
    * Sets the Semi Annual Report Waive field for the request.
    * 
    * @param value  Value that the Semi Annual Report Waive will be set to.
    */
   public final void setSmAnnlRptWaive( Boolean value )
   {
      assertUnsent();
      _SmAnnlRptWaive = value;
   }
	
   /**
    * Sets the Semi Annual Report Mail field for the request.
    * 
    * @param value  Value that the Semi Annual Report Mail will be set to.
    */
   public final void setSmAnnlRptMail( String value )
   {
      assertUnsent();
      _SmAnnlRptMail = value;
   }
	
   /**
    * Sets the Semi Annual Report Fax field for the request.
    * 
    * @param value  Value that the Semi Annual Report Fax will be set to.
    */
   public final void setSmAnnlRptFax( String value )
   {
      assertUnsent();
      _SmAnnlRptFax = value;
   }
	
   /**
    * Sets the Semi Annual Report CD field for the request.
    * 
    * @param value  Value that the Semi Annual Report CD will be set to.
    */
   public final void setSmAnnlRptCD( String value )
   {
      assertUnsent();
      _SmAnnlRptCD = value;
   }
	
   /**
    * Sets the Semi Annual Report Email field for the request.
    * 
    * @param value  Value that the Semi Annual Report Email will be set to.
    */
   public final void setSmAnnlRptEmail( String value )
   {
      assertUnsent();
      _SmAnnlRptEmail = value;
   }
	
   /**
    * Sets the Semi Annual Report Address Code field for the request.
    * 
    * @param value  Value that the Semi Annual Report Address Code will be set to.
    */
   public final void setSmAnnlRptAddr( String value )
   {
      assertUnsent();
      _SmAnnlRptAddr = value;
   }
	
   /**
    * Sets the Semi Annual Report On hold field for the request.
    * 
    * @param value  Value that the Semi Annual Report On hold will be set to.
    */
   public final void setSmAnnlRptHold( Boolean value )
   {
      assertUnsent();
      _SmAnnlRptHold = value;
   }
	
   /**
    * Sets the Tax EPost field for the request.
    * 
    * @param value  Value that the Tax EPost will be set to.
    */
   public final void setTaxEPost( String value )
   {
      assertUnsent();
      _TaxEPost = value;
   }
	
   /**
    * Sets the Letter EPost field for the request.
    * 
    * @param value  Value that the Letter EPost will be set to.
    */
   public final void setLetEPost( String value )
   {
      assertUnsent();
      _LetEPost = value;
   }
	
   /**
    * Sets the Certificate EPost field for the request.
    * 
    * @param value  Value that the Certificate EPost will be set to.
    */
   public final void setCertEPost( String value )
   {
      assertUnsent();
      _CertEPost = value;
   }
	
   /**
    * Sets the Dividend Confirm EPost field for the request.
    * 
    * @param value  Value that the Dividend Confirm EPost will be set to.
    */
   public final void setDivConfEPost( String value )
   {
      assertUnsent();
      _DivConfEPost = value;
   }
	
   /**
    * Sets the Dividend Chq EPost field for the request.
    * 
    * @param value  Value that the Dividend Chq EPost will be set to.
    */
   public final void setDivChqEPost( String value )
   {
      assertUnsent();
      _DivChqEPost = value;
   }
	
   /**
    * Sets the Contribution EPost field for the request.
    * 
    * @param value  Value that the Contribution EPost will be set to.
    */
   public final void setContrEPost( String value )
   {
      assertUnsent();
      _ContrEPost = value;
   }
	
   /**
    * Sets the Registered EPost field for the request.
    * 
    * @param value  Value that the Registered EPost will be set to.
    */
   public final void setRegEPost( String value )
   {
      assertUnsent();
      _RegEPost = value;
   }
	
   /**
    * Sets the Annual Report EPost field for the request.
    * 
    * @param value  Value that the Annual Report EPost will be set to.
    */
   public final void setAnnlRptsEPost( String value )
   {
      assertUnsent();
      _AnnlRptsEPost = value;
   }
	
   /**
    * Sets the Prospectus EPost field for the request.
    * 
    * @param value  Value that the Prospectus EPost will be set to.
    */
   public final void setProspEPost( String value )
   {
      assertUnsent();
      _ProspEPost = value;
   }
	
   /**
    * Sets the Beneficiary EPost field for the request.
    * 
    * @param value  Value that the Beneficiary EPost will be set to.
    */
   public final void setBenEPost( String value )
   {
      assertUnsent();
      _BenEPost = value;
   }
	
   /**
    * Sets the Statement EPost field for the request.
    * 
    * @param value  Value that the Statement EPost will be set to.
    */
   public final void setStmtEPost( String value )
   {
      assertUnsent();
      _StmtEPost = value;
   }
	
   /**
    * Sets the Duplicate Statement EPost field for the request.
    * 
    * @param value  Value that the Duplicate Statement EPost will be set to.
    */
   public final void setDupStmtEPost( String value )
   {
      assertUnsent();
      _DupStmtEPost = value;
   }
	
   /**
    * Sets the NF Confirm EPost field for the request.
    * 
    * @param value  Value that the NF Confirm EPost will be set to.
    */
   public final void setNFConfEPost( String value )
   {
      assertUnsent();
      _NFConfEPost = value;
   }
	
   /**
    * Sets the Txn Confirm EPost field for the request.
    * 
    * @param value  Value that the Txn Confirm EPost will be set to.
    */
   public final void setTxnConfEPost( String value )
   {
      assertUnsent();
      _TxnConfEPost = value;
   }
	
   /**
    * Sets the Duplicate Confirm EPost field for the request.
    * 
    * @param value  Value that the Duplicate Confirm EPost will be set to.
    */
   public final void setDupConfEPost( String value )
   {
      assertUnsent();
      _DupConfEPost = value;
   }
	
   /**
    * Sets the Semi Annual Report EPost field for the request.
    * 
    * @param value  Value that the Semi Annual Report EPost will be set to.
    */
   public final void setSmAnnlRptEPost( String value )
   {
      assertUnsent();
      _SmAnnlRptEPost = value;
   }
	
   /**
    * Sets the Contribution Receipt Suppress field for the request.
    * 
    * @param value  Value that the Contribution Receipt Suppress will be set to.
    */
   public final void setContrRSuppress( Boolean value )
   {
      assertUnsent();
      _ContrRSuppress = value;
   }
	
   /**
    * Sets the Contribution Receipt  Waive field for the request.
    * 
    * @param value  Value that the Contribution Receipt  Waive will be set to.
    */
   public final void setContrRWaive( Boolean value )
   {
      assertUnsent();
      _ContrRWaive = value;
   }
	
   /**
    * Sets the Contribution Receipt Mail field for the request.
    * 
    * @param value  Value that the Contribution Receipt Mail will be set to.
    */
   public final void setContrRMail( String value )
   {
      assertUnsent();
      _ContrRMail = value;
   }
	
   /**
    * Sets the Contribution Receipt Fax field for the request.
    * 
    * @param value  Value that the Contribution Receipt Fax will be set to.
    */
   public final void setContrRFax( String value )
   {
      assertUnsent();
      _ContrRFax = value;
   }
	
   /**
    * Sets the Contribution Receipt CD field for the request.
    * 
    * @param value  Value that the Contribution Receipt CD will be set to.
    */
   public final void setContrRCD( String value )
   {
      assertUnsent();
      _ContrRCD = value;
   }
	
   /**
    * Sets the Contribution Receipt Email field for the request.
    * 
    * @param value  Value that the Contribution Receipt Email will be set to.
    */
   public final void setContrREmail( String value )
   {
      assertUnsent();
      _ContrREmail = value;
   }
	
   /**
    * Sets the Contribution Receipt EPost field for the request.
    * 
    * @param value  Value that the Contribution Receipt EPost will be set to.
    */
   public final void setContrREPost( String value )
   {
      assertUnsent();
      _ContrREPost = value;
   }
	
   /**
    * Sets the Contribution Receipt Address Code field for the request.
    * 
    * @param value  Value that the Contribution Receipt Address Code will be set to.
    */
   public final void setContrRAddr( String value )
   {
      assertUnsent();
      _ContrRAddr = value;
   }
	
   /**
    * Sets the Contribution Receipt On Hold field for the request.
    * 
    * @param value  Value that the Contribution Receipt On Hold will be set to.
    */
   public final void setContrRHold( Boolean value )
   {
      assertUnsent();
      _ContrRHold = value;
   }
	
   /**
    * Sets the Semi-Annual MRFP Address Code field for the request.
    * 
    * @param value  Value that the Semi-Annual MRFP Address Code will be set to.
    */
   public final void setSmAnnlMRFPAddr( String value )
   {
      assertUnsent();
      _SmAnnlMRFPAddr = value;
   }
	
   /**
    * Sets the Semi-Annual MRFP Suppress field for the request.
    * 
    * @param value  Value that the Semi-Annual MRFP Suppress will be set to.
    */
   public final void setSmAnnlMRFPSuppress( Boolean value )
   {
      assertUnsent();
      _SmAnnlMRFPSuppress = value;
   }
	
   /**
    * Sets the Semi-Annual MRFP Waive field for the request.
    * 
    * @param value  Value that the Semi-Annual MRFP Waive will be set to.
    */
   public final void setSmAnnlMRFPWaive( Boolean value )
   {
      assertUnsent();
      _SmAnnlMRFPWaive = value;
   }
	
   /**
    * Sets the Semi-Annual MRFP Hold field for the request.
    * 
    * @param value  Value that the Semi-Annual MRFP Hold will be set to.
    */
   public final void setSmAnnlMRFPHold( Boolean value )
   {
      assertUnsent();
      _SmAnnlMRFPHold = value;
   }
	
   /**
    * Sets the Semi-Annual MRFP Mail field for the request.
    * 
    * @param value  Value that the Semi-Annual MRFP Mail will be set to.
    */
   public final void setSmAnnlMRFPMail( String value )
   {
      assertUnsent();
      _SmAnnlMRFPMail = value;
   }
	
   /**
    * Sets the Semi-Annual MRFP Fax field for the request.
    * 
    * @param value  Value that the Semi-Annual MRFP Fax will be set to.
    */
   public final void setSmAnnlMRFPFax( String value )
   {
      assertUnsent();
      _SmAnnlMRFPFax = value;
   }
	
   /**
    * Sets the Semi-Annual MRFP CD field for the request.
    * 
    * @param value  Value that the Semi-Annual MRFP CD will be set to.
    */
   public final void setSmAnnlMRFPCD( String value )
   {
      assertUnsent();
      _SmAnnlMRFPCD = value;
   }
	
   /**
    * Sets the Semi-Annual MRFP Email field for the request.
    * 
    * @param value  Value that the Semi-Annual MRFP Email will be set to.
    */
   public final void setSmAnnlMRFPEmail( String value )
   {
      assertUnsent();
      _SmAnnlMRFPEmail = value;
   }
	
   /**
    * Sets the Semi-Annual MRFP ePost field for the request.
    * 
    * @param value  Value that the Semi-Annual MRFP ePost will be set to.
    */
   public final void setSmAnnlMRFPePost( String value )
   {
      assertUnsent();
      _SmAnnlMRFPePost = value;
   }
	
   /**
    * Sets the Semi-Annual MRFP Authorization field for the request.
    * 
    * @param value  Value that the Semi-Annual MRFP Authorization will be set to.
    */
   public final void setSmAnnlMRFPAuth( String value )
   {
      assertUnsent();
      _SmAnnlMRFPAuth = value;
   }
	
   /**
    * Sets the Annual MRFP Address Code field for the request.
    * 
    * @param value  Value that the Annual MRFP Address Code will be set to.
    */
   public final void setAnnlMRFPAddr( String value )
   {
      assertUnsent();
      _AnnlMRFPAddr = value;
   }
	
   /**
    * Sets the Annual MRFP Suppress field for the request.
    * 
    * @param value  Value that the Annual MRFP Suppress will be set to.
    */
   public final void setAnnlMRFPSuppress( Boolean value )
   {
      assertUnsent();
      _AnnlMRFPSuppress = value;
   }
	
   /**
    * Sets the Annual MRFP Waive field for the request.
    * 
    * @param value  Value that the Annual MRFP Waive will be set to.
    */
   public final void setAnnlMRFPWaive( Boolean value )
   {
      assertUnsent();
      _AnnlMRFPWaive = value;
   }
	
   /**
    * Sets the Annual MRFP Hold field for the request.
    * 
    * @param value  Value that the Annual MRFP Hold will be set to.
    */
   public final void setAnnlMRFPHold( Boolean value )
   {
      assertUnsent();
      _AnnlMRFPHold = value;
   }
	
   /**
    * Sets the Annual MRFP Mail field for the request.
    * 
    * @param value  Value that the Annual MRFP Mail will be set to.
    */
   public final void setAnnlMRFPMail( String value )
   {
      assertUnsent();
      _AnnlMRFPMail = value;
   }
	
   /**
    * Sets the Annual MRFP Fax field for the request.
    * 
    * @param value  Value that the Annual MRFP Fax will be set to.
    */
   public final void setAnnlMRFPFax( String value )
   {
      assertUnsent();
      _AnnlMRFPFax = value;
   }
	
   /**
    * Sets the Annual MRFP CD field for the request.
    * 
    * @param value  Value that the Annual MRFP CD will be set to.
    */
   public final void setAnnlMRFPCD( String value )
   {
      assertUnsent();
      _AnnlMRFPCD = value;
   }
	
   /**
    * Sets the Annual MRFP Email field for the request.
    * 
    * @param value  Value that the Annual MRFP Email will be set to.
    */
   public final void setAnnlMRFPEmail( String value )
   {
      assertUnsent();
      _AnnlMRFPEmail = value;
   }
	
   /**
    * Sets the Annual MRFP ePost field for the request.
    * 
    * @param value  Value that the Annual MRFP ePost will be set to.
    */
   public final void setAnnlMRFPePost( String value )
   {
      assertUnsent();
      _AnnlMRFPePost = value;
   }
	
   /**
    * Sets the Annual MRFP Authorization field for the request.
    * 
    * @param value  Value that the Annual MRFP Authorization will be set to.
    */
   public final void setAnnlMRFPAuth( String value )
   {
      assertUnsent();
      _AnnlMRFPAuth = value;
   }
	
   /**
    * Sets the Tax Authorization field for the request.
    * 
    * @param value  Value that the Tax Authorization will be set to.
    */
   public final void setTaxAuth( String value )
   {
      assertUnsent();
      _TaxAuth = value;
   }
	
   /**
    * Sets the Letter Authorization field for the request.
    * 
    * @param value  Value that the Letter Authorization will be set to.
    */
   public final void setLetAuth( String value )
   {
      assertUnsent();
      _LetAuth = value;
   }
	
   /**
    * Sets the Certificate Authorization field for the request.
    * 
    * @param value  Value that the Certificate Authorization will be set to.
    */
   public final void setCertAuth( String value )
   {
      assertUnsent();
      _CertAuth = value;
   }
	
   /**
    * Sets the Dividend Confirm Authorization field for the request.
    * 
    * @param value  Value that the Dividend Confirm Authorization will be set to.
    */
   public final void setDivConfAuth( String value )
   {
      assertUnsent();
      _DivConfAuth = value;
   }
	
   /**
    * Sets the Dividend Cheque Authorization field for the request.
    * 
    * @param value  Value that the Dividend Cheque Authorization will be set to.
    */
   public final void setDivChqAuth( String value )
   {
      assertUnsent();
      _DivChqAuth = value;
   }
	
   /**
    * Sets the Contract Authorization field for the request.
    * 
    * @param value  Value that the Contract Authorization will be set to.
    */
   public final void setContrAuth( String value )
   {
      assertUnsent();
      _ContrAuth = value;
   }
	
   /**
    * Sets the Register Authorization field for the request.
    * 
    * @param value  Value that the Register Authorization will be set to.
    */
   public final void setRegAuth( String value )
   {
      assertUnsent();
      _RegAuth = value;
   }
	
   /**
    * Sets the Annual Reports Authorization field for the request.
    * 
    * @param value  Value that the Annual Reports Authorization will be set to.
    */
   public final void setAnnlRptsAuth( String value )
   {
      assertUnsent();
      _AnnlRptsAuth = value;
   }
	
   /**
    * Sets the Prospectus Authorization field for the request.
    * 
    * @param value  Value that the Prospectus Authorization will be set to.
    */
   public final void setProspAuth( String value )
   {
      assertUnsent();
      _ProspAuth = value;
   }
	
   /**
    * Sets the Beneficial Authorization field for the request.
    * 
    * @param value  Value that the Beneficial Authorization will be set to.
    */
   public final void setBenAuth( String value )
   {
      assertUnsent();
      _BenAuth = value;
   }
	
   /**
    * Sets the Statement Authorization field for the request.
    * 
    * @param value  Value that the Statement Authorization will be set to.
    */
   public final void setStmtAuth( String value )
   {
      assertUnsent();
      _StmtAuth = value;
   }
	
   /**
    * Sets the Duplicate Statement Authorization field for the request.
    * 
    * @param value  Value that the Duplicate Statement Authorization will be set to.
    */
   public final void setDupStmtAuth( String value )
   {
      assertUnsent();
      _DupStmtAuth = value;
   }
	
   /**
    * Sets the Non Financial Confirmation Authorization field for the request.
    * 
    * @param value  Value that the Non Financial Confirmation Authorization will be set to.
    */
   public final void setNFConfAuth( String value )
   {
      assertUnsent();
      _NFConfAuth = value;
   }
	
   /**
    * Sets the Transaction Confirmation Authorization field for the request.
    * 
    * @param value  Value that the Transaction Confirmation Authorization will be set to.
    */
   public final void setTxnConfAuth( String value )
   {
      assertUnsent();
      _TxnConfAuth = value;
   }
	
   /**
    * Sets the Duplicate Confirmation Authorization field for the request.
    * 
    * @param value  Value that the Duplicate Confirmation Authorization will be set to.
    */
   public final void setDupConfAuth( String value )
   {
      assertUnsent();
      _DupConfAuth = value;
   }
	
   /**
    * Sets the Semi-Annual Report Authorization field for the request.
    * 
    * @param value  Value that the Semi-Annual Report Authorization will be set to.
    */
   public final void setSmAnnlRptAuth( String value )
   {
      assertUnsent();
      _SmAnnlRptAuth = value;
   }
	
   /**
    * Sets the Contribution Receipt Authorization field for the request.
    * 
    * @param value  Value that the Contribution Receipt Authorization will be set to.
    */
   public final void setContrRAuth( String value )
   {
      assertUnsent();
      _ContrRAuth = value;
   }
	
   /**
    * Sets the Statement Frequency field for the request.
    * 
    * @param value  Value that the Statement Frequency will be set to.
    */
   public final void setStmtFrequency( String value )
   {
      assertUnsent();
      _StmtFrequency = value;
   }
	
   /**
    * Implements the abstract base method to encode
    * the host formatted request.
    * 
    * @param transaction
    *               Host formatted request object.
    */
   protected final void encodeFields( RTSRequestEncodeBuffer requestBuffer ) throws UnsupportedEncodingException
   {
      requestBuffer.appendField( _SessionId );
      requestBuffer.appendField( _User_Id );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyId );
      requestBuffer.appendField( _RunMode );
      requestBuffer.appendField( _RegAddr );
      requestBuffer.appendField( _DivConfAddr );
      requestBuffer.appendField( _DivChqAddr );
      requestBuffer.appendField( _TxnConfAddr );
      requestBuffer.appendField( _DupConfAddr );
      requestBuffer.appendField( _StmtAddr );
      requestBuffer.appendField( _DupStmtAddr );
      requestBuffer.appendField( _CertAddr );
      requestBuffer.appendField( _TaxAddr );
      requestBuffer.appendField( _LetAddr );
      requestBuffer.appendField( _BenAddr );
      requestBuffer.appendField( _DupConfCopies );
      requestBuffer.appendField( _DupStmtCopies );
      requestBuffer.appendField( _RegOnHold );
      requestBuffer.appendField( _DivConfOnHold );
      requestBuffer.appendField( _DivChqOnHold );
      requestBuffer.appendField( _TxnConfOnHold );
      requestBuffer.appendField( _DupConfOnHold );
      requestBuffer.appendField( _StmtOnHold );
      requestBuffer.appendField( _DupStmtOnHold );
      requestBuffer.appendField( _CertOnHold );
      requestBuffer.appendField( _TaxOnHold );
      requestBuffer.appendField( _LetOnHold );
      requestBuffer.appendField( _BenOnHold );
      requestBuffer.appendField( _SATxnConfCode );
      requestBuffer.appendField( _SADivConfCode );
      requestBuffer.appendField( _SALettersCode );
      requestBuffer.appendField( _AcctMstrVer );
      requestBuffer.appendField( _NFCAddr );
      requestBuffer.appendField( _NFConHold );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _AcctMstrRid );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _ContrAddr );
      requestBuffer.appendField( _ContrHold );
      requestBuffer.appendField( _AnnlRptsAddr );
      requestBuffer.appendField( _AnnlRptsHold );
      requestBuffer.appendField( _ProspAddr );
      requestBuffer.appendField( _ProspHold );
      requestBuffer.appendField( _TaxSuppress );
      requestBuffer.appendField( _TaxWaive );
      requestBuffer.appendField( _TaxMail );
      requestBuffer.appendField( _TaxFax );
      requestBuffer.appendField( _TaxCD );
      requestBuffer.appendField( _TaxEmail );
      requestBuffer.appendField( _LetSuppress );
      requestBuffer.appendField( _LetWaive );
      requestBuffer.appendField( _LetMail );
      requestBuffer.appendField( _LetFax );
      requestBuffer.appendField( _LetCD );
      requestBuffer.appendField( _LetEmail );
      requestBuffer.appendField( _CertSuppress );
      requestBuffer.appendField( _CertWaive );
      requestBuffer.appendField( _CertMail );
      requestBuffer.appendField( _CertCD );
      requestBuffer.appendField( _CertEmail );
      requestBuffer.appendField( _CertFax );
      requestBuffer.appendField( _DivConfSuppress );
      requestBuffer.appendField( _DivConfWaive );
      requestBuffer.appendField( _DivConfMail );
      requestBuffer.appendField( _DivConfFax );
      requestBuffer.appendField( _DivConfCD );
      requestBuffer.appendField( _DivConfEmail );
      requestBuffer.appendField( _DivChqSuppress );
      requestBuffer.appendField( _DivChqWaive );
      requestBuffer.appendField( _DivChqMail );
      requestBuffer.appendField( _DivChqFax );
      requestBuffer.appendField( _DivChqCD );
      requestBuffer.appendField( _DivChqEmail );
      requestBuffer.appendField( _RegSuppress );
      requestBuffer.appendField( _RegWaive );
      requestBuffer.appendField( _RegMail );
      requestBuffer.appendField( _RegFax );
      requestBuffer.appendField( _RegCd );
      requestBuffer.appendField( _RegEmail );
      requestBuffer.appendField( _AnnlRptsSuppress );
      requestBuffer.appendField( _AnnlRptsWaive );
      requestBuffer.appendField( _AnnlRptsMail );
      requestBuffer.appendField( _AnnlRptsFax );
      requestBuffer.appendField( _AnnlRptsCD );
      requestBuffer.appendField( _AnnlRptsEmail );
      requestBuffer.appendField( _ProspSuppress );
      requestBuffer.appendField( _ProspWaive );
      requestBuffer.appendField( _ProspMail );
      requestBuffer.appendField( _ProspFax );
      requestBuffer.appendField( _ProspCd );
      requestBuffer.appendField( _ProspEmail );
      requestBuffer.appendField( _BenSuppress );
      requestBuffer.appendField( _BenWaive );
      requestBuffer.appendField( _BenMail );
      requestBuffer.appendField( _BenFax );
      requestBuffer.appendField( _BenCD );
      requestBuffer.appendField( _BenEmail );
      requestBuffer.appendField( _StmtSuppress );
      requestBuffer.appendField( _StmtWaive );
      requestBuffer.appendField( _StmtMail );
      requestBuffer.appendField( _StmtFax );
      requestBuffer.appendField( _StmtCD );
      requestBuffer.appendField( _StmtEmail );
      requestBuffer.appendField( _DupStmtSuppress );
      requestBuffer.appendField( _DupStmtWaive );
      requestBuffer.appendField( _DupStmtMail );
      requestBuffer.appendField( _DupStmtFax );
      requestBuffer.appendField( _DupStmtCD );
      requestBuffer.appendField( _DupStmtEmail );
      requestBuffer.appendField( _NFConfSuppress );
      requestBuffer.appendField( _NFConfWaive );
      requestBuffer.appendField( _NFConfMail );
      requestBuffer.appendField( _NFConfFax );
      requestBuffer.appendField( _NFConfCD );
      requestBuffer.appendField( _NFConfEmail );
      requestBuffer.appendField( _TxnConfSuppress );
      requestBuffer.appendField( _TxnConfWaive );
      requestBuffer.appendField( _TxnConfMail );
      requestBuffer.appendField( _TxnConfFax );
      requestBuffer.appendField( _TxnConfCD );
      requestBuffer.appendField( _TxnConfEmail );
      requestBuffer.appendField( _DupConfSuppress );
      requestBuffer.appendField( _DupConfWaive );
      requestBuffer.appendField( _DupConfMail );
      requestBuffer.appendField( _DupConfFax );
      requestBuffer.appendField( _DupConfCd );
      requestBuffer.appendField( _DupConfEmail );
      requestBuffer.appendField( _ContrSuppress );
      requestBuffer.appendField( _ContrWaive );
      requestBuffer.appendField( _ContrMail );
      requestBuffer.appendField( _ContrFax );
      requestBuffer.appendField( _ContrCD );
      requestBuffer.appendField( _ContrEmail );
      requestBuffer.appendField( _SmAnnlRptSuppress );
      requestBuffer.appendField( _SmAnnlRptWaive );
      requestBuffer.appendField( _SmAnnlRptMail );
      requestBuffer.appendField( _SmAnnlRptFax );
      requestBuffer.appendField( _SmAnnlRptCD );
      requestBuffer.appendField( _SmAnnlRptEmail );
      requestBuffer.appendField( _SmAnnlRptAddr );
      requestBuffer.appendField( _SmAnnlRptHold );
      requestBuffer.appendField( _TaxEPost );
      requestBuffer.appendField( _LetEPost );
      requestBuffer.appendField( _CertEPost );
      requestBuffer.appendField( _DivConfEPost );
      requestBuffer.appendField( _DivChqEPost );
      requestBuffer.appendField( _ContrEPost );
      requestBuffer.appendField( _RegEPost );
      requestBuffer.appendField( _AnnlRptsEPost );
      requestBuffer.appendField( _ProspEPost );
      requestBuffer.appendField( _BenEPost );
      requestBuffer.appendField( _StmtEPost );
      requestBuffer.appendField( _DupStmtEPost );
      requestBuffer.appendField( _NFConfEPost );
      requestBuffer.appendField( _TxnConfEPost );
      requestBuffer.appendField( _DupConfEPost );
      requestBuffer.appendField( _SmAnnlRptEPost );
      requestBuffer.appendField( _ContrRSuppress );
      requestBuffer.appendField( _ContrRWaive );
      requestBuffer.appendField( _ContrRMail );
      requestBuffer.appendField( _ContrRFax );
      requestBuffer.appendField( _ContrRCD );
      requestBuffer.appendField( _ContrREmail );
      requestBuffer.appendField( _ContrREPost );
      requestBuffer.appendField( _ContrRAddr );
      requestBuffer.appendField( _ContrRHold );
      requestBuffer.appendField( _SmAnnlMRFPAddr );
      requestBuffer.appendField( _SmAnnlMRFPSuppress );
      requestBuffer.appendField( _SmAnnlMRFPWaive );
      requestBuffer.appendField( _SmAnnlMRFPHold );
      requestBuffer.appendField( _SmAnnlMRFPMail );
      requestBuffer.appendField( _SmAnnlMRFPFax );
      requestBuffer.appendField( _SmAnnlMRFPCD );
      requestBuffer.appendField( _SmAnnlMRFPEmail );
      requestBuffer.appendField( _SmAnnlMRFPePost );
      requestBuffer.appendField( _SmAnnlMRFPAuth );
      requestBuffer.appendField( _AnnlMRFPAddr );
      requestBuffer.appendField( _AnnlMRFPSuppress );
      requestBuffer.appendField( _AnnlMRFPWaive );
      requestBuffer.appendField( _AnnlMRFPHold );
      requestBuffer.appendField( _AnnlMRFPMail );
      requestBuffer.appendField( _AnnlMRFPFax );
      requestBuffer.appendField( _AnnlMRFPCD );
      requestBuffer.appendField( _AnnlMRFPEmail );
      requestBuffer.appendField( _AnnlMRFPePost );
      requestBuffer.appendField( _AnnlMRFPAuth );
      requestBuffer.appendField( _TaxAuth );
      requestBuffer.appendField( _LetAuth );
      requestBuffer.appendField( _CertAuth );
      requestBuffer.appendField( _DivConfAuth );
      requestBuffer.appendField( _DivChqAuth );
      requestBuffer.appendField( _ContrAuth );
      requestBuffer.appendField( _RegAuth );
      requestBuffer.appendField( _AnnlRptsAuth );
      requestBuffer.appendField( _ProspAuth );
      requestBuffer.appendField( _BenAuth );
      requestBuffer.appendField( _StmtAuth );
      requestBuffer.appendField( _DupStmtAuth );
      requestBuffer.appendField( _NFConfAuth );
      requestBuffer.appendField( _TxnConfAuth );
      requestBuffer.appendField( _DupConfAuth );
      requestBuffer.appendField( _SmAnnlRptAuth );
      requestBuffer.appendField( _ContrRAuth );
      requestBuffer.appendField( _StmtFrequency );
   }

}

