// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Account Commitment Maintenance request.
 * For additional view information see <A HREF="../../../../viewspecs/AcctComtMaint.doc">AcctComtMaint.doc</A>.
 * 
 * @author RTS Generated
 */
public class AcctComtMaintRequest extends IFastRequest implements Serializable
{

   /**
    * Session ID member variable.
    */
   private String _SessionID = "";
            
   /**
    * User ID member variable.
    */
   private String _User_ID = "";
            
   /**
    * Language Code member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * Company ID member variable.
    */
   private String _CompanyID = "";
            
            
            
   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Run Mode member variable.
    */
   private String _RunMode = "";
            
   /**
    * PAC Effective Date member variable.
    */
   private Date _PACDeff = null;
            
   /**
    * Account Commitment Master UUID member variable.
    */
   private String _AcctCommitMstrUUID = "";
            
   /**
    * Cmmitment UUID member variable.
    */
   private String _CommintmentUUID = "";
            
   /**
    * Commitment Code member variable.
    */
   private String _CommitmentCode = "";
            
   /**
    * Commitment Amount member variable.
    */
   private String _CommitAmt = "0";
            
   /**
    * Commitment Effective Date member variable.
    */
   private Date _CommitDeff = null;
            
   /**
    * Recid of Bank-Detl member variable.
    */
   private Integer _PACID = null;
            
   /**
    * Institution Code member variable.
    */
   private Integer _InstCode = null;
            
   /**
    * Swift Code member variable.
    */
   private Integer _SwiftCode = null;
            
   /**
    * Reference Number member variable.
    */
   private Integer _RefNumber = null;
            
   /**
    * Transit Number member variable.
    */
   private Integer _TransitNo = null;
            
   /**
    * Bank Account Number member variable.
    */
   private String _BankAcctNum = "";
            
   /**
    * Bank Account Name member variable.
    */
   private String _BankAcctName = "";
            
   /**
    * Source of Bank Account member variable.
    */
   private String _SourceOfBankAcct = "";
            
   /**
    * Bank Account Currency member variable.
    */
   private String _BankAcctCurrency = "";
            
   /**
    * Bank Account Type member variable.
    */
   private String _BankAcctType = "";
            
   /**
    * Bank Type member variable.
    */
   private String _BankType = "";
            
   /**
    * Bank ID Number member variable.
    */
   private String _BankIdNum = "";
            
   /**
    * ACH Processor member variable.
    */
   private String _ACHProcessor = "";
            
   /**
    * Bank ID member variable.
    */
   private Integer _BankId = null;
            
   /**
    * Credit Info Line 1 member variable.
    */
   private String _CreditInfoLine1 = "";
            
   /**
    * Credit Info Line 2 member variable.
    */
   private String _CreditInfoLine2 = "";
            
   /**
    * Institution Name member variable.
    */
   private String _InstName = "";
            
   /**
    * Bank Address Line 1 member variable.
    */
   private String _BankAddr1 = "";
            
   /**
    * Bank Address Line 2 member variable.
    */
   private String _BankAddr2 = "";
            
   /**
    * Bank Address Line 3 member variable.
    */
   private String _BankAddr3 = "";
            
   /**
    * Bank Address Line 4 member variable.
    */
   private String _BankAddr4 = "";
            
   /**
    * Bank Address Line 5 member variable.
    */
   private String _BankAddr5 = "";
            
   /**
    * Bank Contact Name member variable.
    */
   private String _BankContact = "";
            
   /**
    * Bank Country member variable.
    */
   private String _BankCntry = "";
            
   /**
    * Bank Postal member variable.
    */
   private String _BankPstl = "";
            
   /**
    * Pay Reason 1 member variable.
    */
   private String _PayReason1 = "";
            
   /**
    * Pay Reason 2 member variable.
    */
   private String _PayReason2 = "";
            
   /**
    * Payment Method member variable.
    */
   private String _Paymethod = "";
            
   /**
    * Bank-Acct Version number member variable.
    */
   private Integer _BankDetlVer = null;
            
   /**
    * AcctCommitMstr Version number member variable.
    */
   private Integer _CommitMstrVer = null;
            
   /**
    * PAC Draw Date member variable.
    */
   private Date _PACDrawDate = null;
            
   /**
    * Next Process Date member variable.
    */
   private Date _NextProcDate = null;
            

   /**
    * Constructs the AcctComtMaintRequest object.
    * 
    */
   AcctComtMaintRequest()
   {
      super ( 434 );
   }

   /**
    * Constructs the AcctComtMaintRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AcctComtMaintRequest( String hostEncoding )
   {
      super ( 434, hostEncoding );
   }

   /**
    * Sets the Session ID field for the request.
    * 
    * @param value  Value that the Session ID will be set to.
    */
   public final void setSessionID( String value )
   {
      assertUnsent();
      _SessionID = value;
   }
	
   /**
    * Sets the User ID field for the request.
    * 
    * @param value  Value that the User ID will be set to.
    */
   public final void setUser_ID( String value )
   {
      assertUnsent();
      _User_ID = value;
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
    * Sets the Company ID field for the request.
    * 
    * @param value  Value that the Company ID will be set to.
    */
   public final void setCompanyID( String value )
   {
      assertUnsent();
      _CompanyID = value;
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
    * Sets the PAC Effective Date field for the request.
    * 
    * @param value  Value that the PAC Effective Date will be set to.
    */
   public final void setPACDeff( Date value )
   {
      assertUnsent();
      _PACDeff = value;
   }
	
   /**
    * Sets the Account Commitment Master UUID field for the request.
    * 
    * @param value  Value that the Account Commitment Master UUID will be set to.
    */
   public final void setAcctCommitMstrUUID( String value )
   {
      assertUnsent();
      _AcctCommitMstrUUID = value;
   }
	
   /**
    * Sets the Cmmitment UUID field for the request.
    * 
    * @param value  Value that the Cmmitment UUID will be set to.
    */
   public final void setCommintmentUUID( String value )
   {
      assertUnsent();
      _CommintmentUUID = value;
   }
	
   /**
    * Sets the Commitment Code field for the request.
    * 
    * @param value  Value that the Commitment Code will be set to.
    */
   public final void setCommitmentCode( String value )
   {
      assertUnsent();
      _CommitmentCode = value;
   }
	
   /**
    * Sets the Commitment Amount field for the request.
    * 
    * @param value  Value that the Commitment Amount will be set to.
    */
   public final void setCommitAmt( String value )
   {
      assertUnsent();
      _CommitAmt = value;
   }
	
   /**
    * Sets the Commitment Effective Date field for the request.
    * 
    * @param value  Value that the Commitment Effective Date will be set to.
    */
   public final void setCommitDeff( Date value )
   {
      assertUnsent();
      _CommitDeff = value;
   }
	
   /**
    * Sets the Recid of Bank-Detl field for the request.
    * 
    * @param value  Value that the Recid of Bank-Detl will be set to.
    */
   public final void setPACID( Integer value )
   {
      assertUnsent();
      _PACID = value;
   }
	
   /**
    * Sets the Institution Code field for the request.
    * 
    * @param value  Value that the Institution Code will be set to.
    */
   public final void setInstCode( Integer value )
   {
      assertUnsent();
      _InstCode = value;
   }
	
   /**
    * Sets the Swift Code field for the request.
    * 
    * @param value  Value that the Swift Code will be set to.
    */
   public final void setSwiftCode( Integer value )
   {
      assertUnsent();
      _SwiftCode = value;
   }
	
   /**
    * Sets the Reference Number field for the request.
    * 
    * @param value  Value that the Reference Number will be set to.
    */
   public final void setRefNumber( Integer value )
   {
      assertUnsent();
      _RefNumber = value;
   }
	
   /**
    * Sets the Transit Number field for the request.
    * 
    * @param value  Value that the Transit Number will be set to.
    */
   public final void setTransitNo( Integer value )
   {
      assertUnsent();
      _TransitNo = value;
   }
	
   /**
    * Sets the Bank Account Number field for the request.
    * 
    * @param value  Value that the Bank Account Number will be set to.
    */
   public final void setBankAcctNum( String value )
   {
      assertUnsent();
      _BankAcctNum = value;
   }
	
   /**
    * Sets the Bank Account Name field for the request.
    * 
    * @param value  Value that the Bank Account Name will be set to.
    */
   public final void setBankAcctName( String value )
   {
      assertUnsent();
      _BankAcctName = value;
   }
	
   /**
    * Sets the Source of Bank Account field for the request.
    * 
    * @param value  Value that the Source of Bank Account will be set to.
    */
   public final void setSourceOfBankAcct( String value )
   {
      assertUnsent();
      _SourceOfBankAcct = value;
   }
	
   /**
    * Sets the Bank Account Currency field for the request.
    * 
    * @param value  Value that the Bank Account Currency will be set to.
    */
   public final void setBankAcctCurrency( String value )
   {
      assertUnsent();
      _BankAcctCurrency = value;
   }
	
   /**
    * Sets the Bank Account Type field for the request.
    * 
    * @param value  Value that the Bank Account Type will be set to.
    */
   public final void setBankAcctType( String value )
   {
      assertUnsent();
      _BankAcctType = value;
   }
	
   /**
    * Sets the Bank Type field for the request.
    * 
    * @param value  Value that the Bank Type will be set to.
    */
   public final void setBankType( String value )
   {
      assertUnsent();
      _BankType = value;
   }
	
   /**
    * Sets the Bank ID Number field for the request.
    * 
    * @param value  Value that the Bank ID Number will be set to.
    */
   public final void setBankIdNum( String value )
   {
      assertUnsent();
      _BankIdNum = value;
   }
	
   /**
    * Sets the ACH Processor field for the request.
    * 
    * @param value  Value that the ACH Processor will be set to.
    */
   public final void setACHProcessor( String value )
   {
      assertUnsent();
      _ACHProcessor = value;
   }
	
   /**
    * Sets the Bank ID field for the request.
    * 
    * @param value  Value that the Bank ID will be set to.
    */
   public final void setBankId( Integer value )
   {
      assertUnsent();
      _BankId = value;
   }
	
   /**
    * Sets the Credit Info Line 1 field for the request.
    * 
    * @param value  Value that the Credit Info Line 1 will be set to.
    */
   public final void setCreditInfoLine1( String value )
   {
      assertUnsent();
      _CreditInfoLine1 = value;
   }
	
   /**
    * Sets the Credit Info Line 2 field for the request.
    * 
    * @param value  Value that the Credit Info Line 2 will be set to.
    */
   public final void setCreditInfoLine2( String value )
   {
      assertUnsent();
      _CreditInfoLine2 = value;
   }
	
   /**
    * Sets the Institution Name field for the request.
    * 
    * @param value  Value that the Institution Name will be set to.
    */
   public final void setInstName( String value )
   {
      assertUnsent();
      _InstName = value;
   }
	
   /**
    * Sets the Bank Address Line 1 field for the request.
    * 
    * @param value  Value that the Bank Address Line 1 will be set to.
    */
   public final void setBankAddr1( String value )
   {
      assertUnsent();
      _BankAddr1 = value;
   }
	
   /**
    * Sets the Bank Address Line 2 field for the request.
    * 
    * @param value  Value that the Bank Address Line 2 will be set to.
    */
   public final void setBankAddr2( String value )
   {
      assertUnsent();
      _BankAddr2 = value;
   }
	
   /**
    * Sets the Bank Address Line 3 field for the request.
    * 
    * @param value  Value that the Bank Address Line 3 will be set to.
    */
   public final void setBankAddr3( String value )
   {
      assertUnsent();
      _BankAddr3 = value;
   }
	
   /**
    * Sets the Bank Address Line 4 field for the request.
    * 
    * @param value  Value that the Bank Address Line 4 will be set to.
    */
   public final void setBankAddr4( String value )
   {
      assertUnsent();
      _BankAddr4 = value;
   }
	
   /**
    * Sets the Bank Address Line 5 field for the request.
    * 
    * @param value  Value that the Bank Address Line 5 will be set to.
    */
   public final void setBankAddr5( String value )
   {
      assertUnsent();
      _BankAddr5 = value;
   }
	
   /**
    * Sets the Bank Contact Name field for the request.
    * 
    * @param value  Value that the Bank Contact Name will be set to.
    */
   public final void setBankContact( String value )
   {
      assertUnsent();
      _BankContact = value;
   }
	
   /**
    * Sets the Bank Country field for the request.
    * 
    * @param value  Value that the Bank Country will be set to.
    */
   public final void setBankCntry( String value )
   {
      assertUnsent();
      _BankCntry = value;
   }
	
   /**
    * Sets the Bank Postal field for the request.
    * 
    * @param value  Value that the Bank Postal will be set to.
    */
   public final void setBankPstl( String value )
   {
      assertUnsent();
      _BankPstl = value;
   }
	
   /**
    * Sets the Pay Reason 1 field for the request.
    * 
    * @param value  Value that the Pay Reason 1 will be set to.
    */
   public final void setPayReason1( String value )
   {
      assertUnsent();
      _PayReason1 = value;
   }
	
   /**
    * Sets the Pay Reason 2 field for the request.
    * 
    * @param value  Value that the Pay Reason 2 will be set to.
    */
   public final void setPayReason2( String value )
   {
      assertUnsent();
      _PayReason2 = value;
   }
	
   /**
    * Sets the Payment Method field for the request.
    * 
    * @param value  Value that the Payment Method will be set to.
    */
   public final void setPaymethod( String value )
   {
      assertUnsent();
      _Paymethod = value;
   }
	
   /**
    * Sets the Bank-Acct Version number field for the request.
    * 
    * @param value  Value that the Bank-Acct Version number will be set to.
    */
   public final void setBankDetlVer( Integer value )
   {
      assertUnsent();
      _BankDetlVer = value;
   }
	
   /**
    * Sets the AcctCommitMstr Version number field for the request.
    * 
    * @param value  Value that the AcctCommitMstr Version number will be set to.
    */
   public final void setCommitMstrVer( Integer value )
   {
      assertUnsent();
      _CommitMstrVer = value;
   }
	
   /**
    * Sets the PAC Draw Date field for the request.
    * 
    * @param value  Value that the PAC Draw Date will be set to.
    */
   public final void setPACDrawDate( Date value )
   {
      assertUnsent();
      _PACDrawDate = value;
   }
	
   /**
    * Sets the Next Process Date field for the request.
    * 
    * @param value  Value that the Next Process Date will be set to.
    */
   public final void setNextProcDate( Date value )
   {
      assertUnsent();
      _NextProcDate = value;
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
      requestBuffer.appendField( _SessionID );
      requestBuffer.appendField( _User_ID );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyID );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _RunMode );
      requestBuffer.appendField( _PACDeff );
      requestBuffer.appendField( _AcctCommitMstrUUID );
      requestBuffer.appendField( _CommintmentUUID );
      requestBuffer.appendField( _CommitmentCode );
      requestBuffer.appendField( _CommitAmt );
      requestBuffer.appendField( _CommitDeff );
      requestBuffer.appendField( _PACID );
      requestBuffer.appendField( _InstCode );
      requestBuffer.appendField( _SwiftCode );
      requestBuffer.appendField( _RefNumber );
      requestBuffer.appendField( _TransitNo );
      requestBuffer.appendField( _BankAcctNum );
      requestBuffer.appendField( _BankAcctName );
      requestBuffer.appendField( _SourceOfBankAcct );
      requestBuffer.appendField( _BankAcctCurrency );
      requestBuffer.appendField( _BankAcctType );
      requestBuffer.appendField( _BankType );
      requestBuffer.appendField( _BankIdNum );
      requestBuffer.appendField( _ACHProcessor );
      requestBuffer.appendField( _BankId );
      requestBuffer.appendField( _CreditInfoLine1 );
      requestBuffer.appendField( _CreditInfoLine2 );
      requestBuffer.appendField( _InstName );
      requestBuffer.appendField( _BankAddr1 );
      requestBuffer.appendField( _BankAddr2 );
      requestBuffer.appendField( _BankAddr3 );
      requestBuffer.appendField( _BankAddr4 );
      requestBuffer.appendField( _BankAddr5 );
      requestBuffer.appendField( _BankContact );
      requestBuffer.appendField( _BankCntry );
      requestBuffer.appendField( _BankPstl );
      requestBuffer.appendField( _PayReason1 );
      requestBuffer.appendField( _PayReason2 );
      requestBuffer.appendField( _Paymethod );
      requestBuffer.appendField( _BankDetlVer );
      requestBuffer.appendField( _CommitMstrVer );
      requestBuffer.appendField( _PACDrawDate );
      requestBuffer.appendField( _NextProcDate );
   }

}

