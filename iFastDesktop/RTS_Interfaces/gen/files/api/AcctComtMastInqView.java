
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Account Commitment Master Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/AcctComtMastInq.doc">AcctComtMastInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class AcctComtMastInqView extends IFastView implements Serializable
{

   /**
    * Account Commitment Master UUID member variable.
    */
   private String _AcctCommitMstrUUID = null;
   
   /**
    * Cmmitment UUID member variable.
    */
   private String _CommitmentUUID = null;
   
   /**
    * Commitment Code member variable.
    */
   private String _CommitmentCode = null;
   
   /**
    * Commitment Descrription member variable.
    */
   private String _CommitmentDesc = null;
   
   /**
    * Effective Date member variable.
    */
   private Date _CommitDeff = null;
   
   /**
    * Commitment End Date member variable.
    */
   private Date _CommitEndDate = null;
   
   /**
    * Beneficiary Name member variable.
    */
   private String _BeneName = null;
   
   /**
    * Original Beneficiary Name member variable.
    */
   private String _OrigBeneName = null;
   
   /**
    * Commitment Status member variable.
    */
   private String _CommitStatus = null;
   
   /**
    * Commitment Status Description member variable.
    */
   private String _CommitStatusDesc = null;
   
   /**
    * Commitment Amount member variable.
    */
   private String _CommitAmt = null;
   
   /**
    * Original Account Number member variable.
    */
   private String _OrigAccountNum = null;
   
   /**
    * Commission Paid member variable.
    */
   private String _CommissionPaid = null;
   
   /**
    * Surrender Charges Applied member variable.
    */
   private String _SurrChrgApplied = null;
   
   /**
    * Maximum Surrender Charges member variable.
    */
   private String _MaxSurrCharges = null;
   
   /**
    * Committed PACS member variable.
    */
   private Integer _CommittedPACS = null;
   
   /**
    * Paid PACS member variable.
    */
   private Integer _PaidPACS = null;
   
   /**
    * Number of missing PACS member variable.
    */
   private Integer _MissingPACS = null;
   
   /**
    * UserID that created AcctCommitMstr record member variable.
    */
   private String _Username = null;
   
   /**
    * Date AcctCommitMstr created member variable.
    */
   private Date _ProcessDate = null;
   
   /**
    * UserID that modified AcctCommitMstr record member variable.
    */
   private String _ModUser = null;
   
   /**
    * Date that AcctCommitMstr record was modified member variable.
    */
   private Date _ModDate = null;
   
   /**
    * Recid of Bank-Detl member variable.
    */
   private Integer _PACID = null;
   
   /**
    * PAC Effective Date member variable.
    */
   private Date _PACDeff = null;
   
   /**
    * PAC Amount member variable.
    */
   private String _PACAmt = null;
   
   /**
    * PAC Stop Date member variable.
    */
   private Date _PACStopDate = null;
   
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
   private String _BankAcctNum = null;
   
   /**
    * Bank Account Name member variable.
    */
   private String _BankAcctName = null;
   
   /**
    * Source of Bank Account member variable.
    */
   private String _SourceOfBankAcct = null;
   
   /**
    * Bank Account Currency member variable.
    */
   private String _BankAcctCurrency = null;
   
   /**
    * Bank Account Type member variable.
    */
   private String _BankAcctType = null;
   
   /**
    * Bank Type member variable.
    */
   private String _BankType = null;
   
   /**
    * Bank ID Number member variable.
    */
   private String _BankIdNum = null;
   
   /**
    * ACH Processor member variable.
    */
   private String _ACHProcessor = null;
   
   /**
    * Bank ID member variable.
    */
   private Integer _BankId = null;
   
   /**
    * Credit Info Line 1 member variable.
    */
   private String _CreditInfoLine1 = null;
   
   /**
    * Credit Info Line 2 member variable.
    */
   private String _CreditInfoLine2 = null;
   
   /**
    * Institution Name member variable.
    */
   private String _InstName = null;
   
   /**
    * Bank Address Line 1 member variable.
    */
   private String _BankAddr1 = null;
   
   /**
    * Bank Address Line 2 member variable.
    */
   private String _BankAddr2 = null;
   
   /**
    * Bank Address Line 3 member variable.
    */
   private String _BankAddr3 = null;
   
   /**
    * Bank Address Line 4 member variable.
    */
   private String _BankAddr4 = null;
   
   /**
    * Bank Address Line 5 member variable.
    */
   private String _BankAddr5 = null;
   
   /**
    * Bank Contact Name member variable.
    */
   private String _BankContact = null;
   
   /**
    * Bank Country member variable.
    */
   private String _BankCntry = null;
   
   /**
    * Bank Postal member variable.
    */
   private String _BankPstl = null;
   
   /**
    * Pay Reason 1 member variable.
    */
   private String _PayReason1 = null;
   
   /**
    * Pay Reason 2 member variable.
    */
   private String _PayReason2 = null;
   
   /**
    * Payment Method member variable.
    */
   private String _Paymethod = null;
   
   /**
    * Bank-Acct Version number member variable.
    */
   private Integer _BankDetlVer = null;
   
   /**
    * AcctCommitMstr Version number member variable.
    */
   private Integer _CommitMstrVer = null;
   
   /**
    * PACS Paid member variable.
    */
   private String _PaidPACSAmt = null;
   
   /**
    * Last Process Date member variable.
    */
   private Date _LastProcDate = null;
   
   /**
    * Next Process Date member variable.
    */
   private Date _NextProcDate = null;
   
   /**
    * Account has pac pending trade member variable.
    */
   private Boolean _hasPACPurchasePending = null;
   

   /**
    * Constructs the AcctComtMastInqView object.
    * 
    */
   public AcctComtMastInqView()
   {
      super ( new AcctComtMastInqRequest() );
   }

   /**
    * Constructs the AcctComtMastInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AcctComtMastInqView( String hostEncoding )
   {
      super ( new AcctComtMastInqRequest( hostEncoding ) );
   }

   /**
    * Gets the AcctComtMastInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AcctComtMastInqRequest object.
    */
   public final AcctComtMastInqRequest getRequest()
   {
      return (AcctComtMastInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Account Commitment Master UUID field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Account Commitment Master UUID or null.
    */
   public final String getAcctCommitMstrUUID()
   {
      return _AcctCommitMstrUUID;
   }
	
   /**
    * Gets the Account Commitment Master UUID field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Commitment Master UUID or the specified default value.
    */
   public final String getAcctCommitMstrUUID( String defaultValue )
   {
      return _AcctCommitMstrUUID == null ? defaultValue : _AcctCommitMstrUUID;
   }
                  
   /**
    * Gets the Cmmitment UUID field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Cmmitment UUID or null.
    */
   public final String getCommitmentUUID()
   {
      return _CommitmentUUID;
   }
	
   /**
    * Gets the Cmmitment UUID field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Cmmitment UUID or the specified default value.
    */
   public final String getCommitmentUUID( String defaultValue )
   {
      return _CommitmentUUID == null ? defaultValue : _CommitmentUUID;
   }
                  
   /**
    * Gets the Commitment Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Commitment Code or null.
    */
   public final String getCommitmentCode()
   {
      return _CommitmentCode;
   }
	
   /**
    * Gets the Commitment Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commitment Code or the specified default value.
    */
   public final String getCommitmentCode( String defaultValue )
   {
      return _CommitmentCode == null ? defaultValue : _CommitmentCode;
   }
                  
   /**
    * Gets the Commitment Descrription field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Commitment Descrription or null.
    */
   public final String getCommitmentDesc()
   {
      return _CommitmentDesc;
   }
	
   /**
    * Gets the Commitment Descrription field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commitment Descrription or the specified default value.
    */
   public final String getCommitmentDesc( String defaultValue )
   {
      return _CommitmentDesc == null ? defaultValue : _CommitmentDesc;
   }
                  
   /**
    * Gets the Effective Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Effective Date or null.
    */
   public final Date getCommitDeff()
   {
      return _CommitDeff;
   }
	
   /**
    * Gets the Effective Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Effective Date or the specified default value.
    */
   public final Date getCommitDeff( Date defaultValue )
   {
      return _CommitDeff == null ? defaultValue : _CommitDeff;
   }
                  
   /**
    * Gets the Commitment End Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Commitment End Date or null.
    */
   public final Date getCommitEndDate()
   {
      return _CommitEndDate;
   }
	
   /**
    * Gets the Commitment End Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commitment End Date or the specified default value.
    */
   public final Date getCommitEndDate( Date defaultValue )
   {
      return _CommitEndDate == null ? defaultValue : _CommitEndDate;
   }
                  
   /**
    * Gets the Beneficiary Name field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Beneficiary Name or null.
    */
   public final String getBeneName()
   {
      return _BeneName;
   }
	
   /**
    * Gets the Beneficiary Name field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Beneficiary Name or the specified default value.
    */
   public final String getBeneName( String defaultValue )
   {
      return _BeneName == null ? defaultValue : _BeneName;
   }
                  
   /**
    * Gets the Original Beneficiary Name field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Original Beneficiary Name or null.
    */
   public final String getOrigBeneName()
   {
      return _OrigBeneName;
   }
	
   /**
    * Gets the Original Beneficiary Name field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Original Beneficiary Name or the specified default value.
    */
   public final String getOrigBeneName( String defaultValue )
   {
      return _OrigBeneName == null ? defaultValue : _OrigBeneName;
   }
                  
   /**
    * Gets the Commitment Status field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Commitment Status or null.
    */
   public final String getCommitStatus()
   {
      return _CommitStatus;
   }
	
   /**
    * Gets the Commitment Status field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commitment Status or the specified default value.
    */
   public final String getCommitStatus( String defaultValue )
   {
      return _CommitStatus == null ? defaultValue : _CommitStatus;
   }
                  
   /**
    * Gets the Commitment Status Description field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Commitment Status Description or null.
    */
   public final String getCommitStatusDesc()
   {
      return _CommitStatusDesc;
   }
	
   /**
    * Gets the Commitment Status Description field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commitment Status Description or the specified default value.
    */
   public final String getCommitStatusDesc( String defaultValue )
   {
      return _CommitStatusDesc == null ? defaultValue : _CommitStatusDesc;
   }
                  
   /**
    * Gets the Commitment Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Commitment Amount or null.
    */
   public final String getCommitAmt()
   {
      return _CommitAmt;
   }
	
   /**
    * Gets the Commitment Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commitment Amount or the specified default value.
    */
   public final String getCommitAmt( String defaultValue )
   {
      return _CommitAmt == null ? defaultValue : _CommitAmt;
   }
                  
   /**
    * Gets the Original Account Number field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Original Account Number or null.
    */
   public final String getOrigAccountNum()
   {
      return _OrigAccountNum;
   }
	
   /**
    * Gets the Original Account Number field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Original Account Number or the specified default value.
    */
   public final String getOrigAccountNum( String defaultValue )
   {
      return _OrigAccountNum == null ? defaultValue : _OrigAccountNum;
   }
                  
   /**
    * Gets the Commission Paid field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Commission Paid or null.
    */
   public final String getCommissionPaid()
   {
      return _CommissionPaid;
   }
	
   /**
    * Gets the Commission Paid field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commission Paid or the specified default value.
    */
   public final String getCommissionPaid( String defaultValue )
   {
      return _CommissionPaid == null ? defaultValue : _CommissionPaid;
   }
                  
   /**
    * Gets the Surrender Charges Applied field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Surrender Charges Applied or null.
    */
   public final String getSurrChrgApplied()
   {
      return _SurrChrgApplied;
   }
	
   /**
    * Gets the Surrender Charges Applied field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Surrender Charges Applied or the specified default value.
    */
   public final String getSurrChrgApplied( String defaultValue )
   {
      return _SurrChrgApplied == null ? defaultValue : _SurrChrgApplied;
   }
                  
   /**
    * Gets the Maximum Surrender Charges field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Maximum Surrender Charges or null.
    */
   public final String getMaxSurrCharges()
   {
      return _MaxSurrCharges;
   }
	
   /**
    * Gets the Maximum Surrender Charges field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Maximum Surrender Charges or the specified default value.
    */
   public final String getMaxSurrCharges( String defaultValue )
   {
      return _MaxSurrCharges == null ? defaultValue : _MaxSurrCharges;
   }
                  
   /**
    * Gets the Committed PACS field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Committed PACS or null.
    */
   public final Integer getCommittedPACS()
   {
      return _CommittedPACS;
   }
	
   /**
    * Gets the Committed PACS field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Committed PACS or the specified default value.
    */
   public final int getCommittedPACS( int defaultValue )
   {
      return _CommittedPACS == null ? defaultValue : _CommittedPACS.intValue();
   }
                  
   /**
    * Gets the Paid PACS field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Paid PACS or null.
    */
   public final Integer getPaidPACS()
   {
      return _PaidPACS;
   }
	
   /**
    * Gets the Paid PACS field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Paid PACS or the specified default value.
    */
   public final int getPaidPACS( int defaultValue )
   {
      return _PaidPACS == null ? defaultValue : _PaidPACS.intValue();
   }
                  
   /**
    * Gets the Number of missing PACS field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Number of missing PACS or null.
    */
   public final Integer getMissingPACS()
   {
      return _MissingPACS;
   }
	
   /**
    * Gets the Number of missing PACS field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Number of missing PACS or the specified default value.
    */
   public final int getMissingPACS( int defaultValue )
   {
      return _MissingPACS == null ? defaultValue : _MissingPACS.intValue();
   }
                  
   /**
    * Gets the UserID that created AcctCommitMstr record field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the UserID that created AcctCommitMstr record or null.
    */
   public final String getUsername()
   {
      return _Username;
   }
	
   /**
    * Gets the UserID that created AcctCommitMstr record field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the UserID that created AcctCommitMstr record or the specified default value.
    */
   public final String getUsername( String defaultValue )
   {
      return _Username == null ? defaultValue : _Username;
   }
                  
   /**
    * Gets the Date AcctCommitMstr created field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Date AcctCommitMstr created or null.
    */
   public final Date getProcessDate()
   {
      return _ProcessDate;
   }
	
   /**
    * Gets the Date AcctCommitMstr created field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date AcctCommitMstr created or the specified default value.
    */
   public final Date getProcessDate( Date defaultValue )
   {
      return _ProcessDate == null ? defaultValue : _ProcessDate;
   }
                  
   /**
    * Gets the UserID that modified AcctCommitMstr record field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the UserID that modified AcctCommitMstr record or null.
    */
   public final String getModUser()
   {
      return _ModUser;
   }
	
   /**
    * Gets the UserID that modified AcctCommitMstr record field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the UserID that modified AcctCommitMstr record or the specified default value.
    */
   public final String getModUser( String defaultValue )
   {
      return _ModUser == null ? defaultValue : _ModUser;
   }
                  
   /**
    * Gets the Date that AcctCommitMstr record was modified field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Date that AcctCommitMstr record was modified or null.
    */
   public final Date getModDate()
   {
      return _ModDate;
   }
	
   /**
    * Gets the Date that AcctCommitMstr record was modified field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date that AcctCommitMstr record was modified or the specified default value.
    */
   public final Date getModDate( Date defaultValue )
   {
      return _ModDate == null ? defaultValue : _ModDate;
   }
                  
   /**
    * Gets the Recid of Bank-Detl field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Recid of Bank-Detl or null.
    */
   public final Integer getPACID()
   {
      return _PACID;
   }
	
   /**
    * Gets the Recid of Bank-Detl field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Recid of Bank-Detl or the specified default value.
    */
   public final int getPACID( int defaultValue )
   {
      return _PACID == null ? defaultValue : _PACID.intValue();
   }
                  
   /**
    * Gets the PAC Effective Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the PAC Effective Date or null.
    */
   public final Date getPACDeff()
   {
      return _PACDeff;
   }
	
   /**
    * Gets the PAC Effective Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PAC Effective Date or the specified default value.
    */
   public final Date getPACDeff( Date defaultValue )
   {
      return _PACDeff == null ? defaultValue : _PACDeff;
   }
                  
   /**
    * Gets the PAC Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the PAC Amount or null.
    */
   public final String getPACAmt()
   {
      return _PACAmt;
   }
	
   /**
    * Gets the PAC Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PAC Amount or the specified default value.
    */
   public final String getPACAmt( String defaultValue )
   {
      return _PACAmt == null ? defaultValue : _PACAmt;
   }
                  
   /**
    * Gets the PAC Stop Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the PAC Stop Date or null.
    */
   public final Date getPACStopDate()
   {
      return _PACStopDate;
   }
	
   /**
    * Gets the PAC Stop Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PAC Stop Date or the specified default value.
    */
   public final Date getPACStopDate( Date defaultValue )
   {
      return _PACStopDate == null ? defaultValue : _PACStopDate;
   }
                  
   /**
    * Gets the Institution Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Institution Code or null.
    */
   public final Integer getInstCode()
   {
      return _InstCode;
   }
	
   /**
    * Gets the Institution Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Institution Code or the specified default value.
    */
   public final int getInstCode( int defaultValue )
   {
      return _InstCode == null ? defaultValue : _InstCode.intValue();
   }
                  
   /**
    * Gets the Swift Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Swift Code or null.
    */
   public final Integer getSwiftCode()
   {
      return _SwiftCode;
   }
	
   /**
    * Gets the Swift Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Swift Code or the specified default value.
    */
   public final int getSwiftCode( int defaultValue )
   {
      return _SwiftCode == null ? defaultValue : _SwiftCode.intValue();
   }
                  
   /**
    * Gets the Reference Number field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Reference Number or null.
    */
   public final Integer getRefNumber()
   {
      return _RefNumber;
   }
	
   /**
    * Gets the Reference Number field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reference Number or the specified default value.
    */
   public final int getRefNumber( int defaultValue )
   {
      return _RefNumber == null ? defaultValue : _RefNumber.intValue();
   }
                  
   /**
    * Gets the Transit Number field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Transit Number or null.
    */
   public final Integer getTransitNo()
   {
      return _TransitNo;
   }
	
   /**
    * Gets the Transit Number field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transit Number or the specified default value.
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
    * Gets the Source of Bank Account field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Source of Bank Account or null.
    */
   public final String getSourceOfBankAcct()
   {
      return _SourceOfBankAcct;
   }
	
   /**
    * Gets the Source of Bank Account field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Source of Bank Account or the specified default value.
    */
   public final String getSourceOfBankAcct( String defaultValue )
   {
      return _SourceOfBankAcct == null ? defaultValue : _SourceOfBankAcct;
   }
                  
   /**
    * Gets the Bank Account Currency field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Bank Account Currency or null.
    */
   public final String getBankAcctCurrency()
   {
      return _BankAcctCurrency;
   }
	
   /**
    * Gets the Bank Account Currency field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Account Currency or the specified default value.
    */
   public final String getBankAcctCurrency( String defaultValue )
   {
      return _BankAcctCurrency == null ? defaultValue : _BankAcctCurrency;
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
    * Gets the Bank Type field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Bank Type or null.
    */
   public final String getBankType()
   {
      return _BankType;
   }
	
   /**
    * Gets the Bank Type field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Type or the specified default value.
    */
   public final String getBankType( String defaultValue )
   {
      return _BankType == null ? defaultValue : _BankType;
   }
                  
   /**
    * Gets the Bank ID Number field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Bank ID Number or null.
    */
   public final String getBankIdNum()
   {
      return _BankIdNum;
   }
	
   /**
    * Gets the Bank ID Number field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank ID Number or the specified default value.
    */
   public final String getBankIdNum( String defaultValue )
   {
      return _BankIdNum == null ? defaultValue : _BankIdNum;
   }
                  
   /**
    * Gets the ACH Processor field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the ACH Processor or null.
    */
   public final String getACHProcessor()
   {
      return _ACHProcessor;
   }
	
   /**
    * Gets the ACH Processor field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ACH Processor or the specified default value.
    */
   public final String getACHProcessor( String defaultValue )
   {
      return _ACHProcessor == null ? defaultValue : _ACHProcessor;
   }
                  
   /**
    * Gets the Bank ID field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Bank ID or null.
    */
   public final Integer getBankId()
   {
      return _BankId;
   }
	
   /**
    * Gets the Bank ID field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank ID or the specified default value.
    */
   public final int getBankId( int defaultValue )
   {
      return _BankId == null ? defaultValue : _BankId.intValue();
   }
                  
   /**
    * Gets the Credit Info Line 1 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Credit Info Line 1 or null.
    */
   public final String getCreditInfoLine1()
   {
      return _CreditInfoLine1;
   }
	
   /**
    * Gets the Credit Info Line 1 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Credit Info Line 1 or the specified default value.
    */
   public final String getCreditInfoLine1( String defaultValue )
   {
      return _CreditInfoLine1 == null ? defaultValue : _CreditInfoLine1;
   }
                  
   /**
    * Gets the Credit Info Line 2 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Credit Info Line 2 or null.
    */
   public final String getCreditInfoLine2()
   {
      return _CreditInfoLine2;
   }
	
   /**
    * Gets the Credit Info Line 2 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Credit Info Line 2 or the specified default value.
    */
   public final String getCreditInfoLine2( String defaultValue )
   {
      return _CreditInfoLine2 == null ? defaultValue : _CreditInfoLine2;
   }
                  
   /**
    * Gets the Institution Name field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Institution Name or null.
    */
   public final String getInstName()
   {
      return _InstName;
   }
	
   /**
    * Gets the Institution Name field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Institution Name or the specified default value.
    */
   public final String getInstName( String defaultValue )
   {
      return _InstName == null ? defaultValue : _InstName;
   }
                  
   /**
    * Gets the Bank Address Line 1 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Bank Address Line 1 or null.
    */
   public final String getBankAddr1()
   {
      return _BankAddr1;
   }
	
   /**
    * Gets the Bank Address Line 1 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Address Line 1 or the specified default value.
    */
   public final String getBankAddr1( String defaultValue )
   {
      return _BankAddr1 == null ? defaultValue : _BankAddr1;
   }
                  
   /**
    * Gets the Bank Address Line 2 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Bank Address Line 2 or null.
    */
   public final String getBankAddr2()
   {
      return _BankAddr2;
   }
	
   /**
    * Gets the Bank Address Line 2 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Address Line 2 or the specified default value.
    */
   public final String getBankAddr2( String defaultValue )
   {
      return _BankAddr2 == null ? defaultValue : _BankAddr2;
   }
                  
   /**
    * Gets the Bank Address Line 3 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Bank Address Line 3 or null.
    */
   public final String getBankAddr3()
   {
      return _BankAddr3;
   }
	
   /**
    * Gets the Bank Address Line 3 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Address Line 3 or the specified default value.
    */
   public final String getBankAddr3( String defaultValue )
   {
      return _BankAddr3 == null ? defaultValue : _BankAddr3;
   }
                  
   /**
    * Gets the Bank Address Line 4 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Bank Address Line 4 or null.
    */
   public final String getBankAddr4()
   {
      return _BankAddr4;
   }
	
   /**
    * Gets the Bank Address Line 4 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Address Line 4 or the specified default value.
    */
   public final String getBankAddr4( String defaultValue )
   {
      return _BankAddr4 == null ? defaultValue : _BankAddr4;
   }
                  
   /**
    * Gets the Bank Address Line 5 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Bank Address Line 5 or null.
    */
   public final String getBankAddr5()
   {
      return _BankAddr5;
   }
	
   /**
    * Gets the Bank Address Line 5 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Address Line 5 or the specified default value.
    */
   public final String getBankAddr5( String defaultValue )
   {
      return _BankAddr5 == null ? defaultValue : _BankAddr5;
   }
                  
   /**
    * Gets the Bank Contact Name field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Bank Contact Name or null.
    */
   public final String getBankContact()
   {
      return _BankContact;
   }
	
   /**
    * Gets the Bank Contact Name field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Contact Name or the specified default value.
    */
   public final String getBankContact( String defaultValue )
   {
      return _BankContact == null ? defaultValue : _BankContact;
   }
                  
   /**
    * Gets the Bank Country field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Bank Country or null.
    */
   public final String getBankCntry()
   {
      return _BankCntry;
   }
	
   /**
    * Gets the Bank Country field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Country or the specified default value.
    */
   public final String getBankCntry( String defaultValue )
   {
      return _BankCntry == null ? defaultValue : _BankCntry;
   }
                  
   /**
    * Gets the Bank Postal field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Bank Postal or null.
    */
   public final String getBankPstl()
   {
      return _BankPstl;
   }
	
   /**
    * Gets the Bank Postal field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Postal or the specified default value.
    */
   public final String getBankPstl( String defaultValue )
   {
      return _BankPstl == null ? defaultValue : _BankPstl;
   }
                  
   /**
    * Gets the Pay Reason 1 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Pay Reason 1 or null.
    */
   public final String getPayReason1()
   {
      return _PayReason1;
   }
	
   /**
    * Gets the Pay Reason 1 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pay Reason 1 or the specified default value.
    */
   public final String getPayReason1( String defaultValue )
   {
      return _PayReason1 == null ? defaultValue : _PayReason1;
   }
                  
   /**
    * Gets the Pay Reason 2 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Pay Reason 2 or null.
    */
   public final String getPayReason2()
   {
      return _PayReason2;
   }
	
   /**
    * Gets the Pay Reason 2 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pay Reason 2 or the specified default value.
    */
   public final String getPayReason2( String defaultValue )
   {
      return _PayReason2 == null ? defaultValue : _PayReason2;
   }
                  
   /**
    * Gets the Payment Method field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Payment Method or null.
    */
   public final String getPaymethod()
   {
      return _Paymethod;
   }
	
   /**
    * Gets the Payment Method field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payment Method or the specified default value.
    */
   public final String getPaymethod( String defaultValue )
   {
      return _Paymethod == null ? defaultValue : _Paymethod;
   }
                  
   /**
    * Gets the Bank-Acct Version number field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Bank-Acct Version number or null.
    */
   public final Integer getBankDetlVer()
   {
      return _BankDetlVer;
   }
	
   /**
    * Gets the Bank-Acct Version number field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank-Acct Version number or the specified default value.
    */
   public final int getBankDetlVer( int defaultValue )
   {
      return _BankDetlVer == null ? defaultValue : _BankDetlVer.intValue();
   }
                  
   /**
    * Gets the AcctCommitMstr Version number field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the AcctCommitMstr Version number or null.
    */
   public final Integer getCommitMstrVer()
   {
      return _CommitMstrVer;
   }
	
   /**
    * Gets the AcctCommitMstr Version number field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AcctCommitMstr Version number or the specified default value.
    */
   public final int getCommitMstrVer( int defaultValue )
   {
      return _CommitMstrVer == null ? defaultValue : _CommitMstrVer.intValue();
   }
                  
   /**
    * Gets the PACS Paid field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the PACS Paid or null.
    */
   public final String getPaidPACSAmt()
   {
      return _PaidPACSAmt;
   }
	
   /**
    * Gets the PACS Paid field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PACS Paid or the specified default value.
    */
   public final String getPaidPACSAmt( String defaultValue )
   {
      return _PaidPACSAmt == null ? defaultValue : _PaidPACSAmt;
   }
                  
   /**
    * Gets the Last Process Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Last Process Date or null.
    */
   public final Date getLastProcDate()
   {
      return _LastProcDate;
   }
	
   /**
    * Gets the Last Process Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Last Process Date or the specified default value.
    */
   public final Date getLastProcDate( Date defaultValue )
   {
      return _LastProcDate == null ? defaultValue : _LastProcDate;
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
    * Gets the Account has pac pending trade field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Account has pac pending trade or null.
    */
   public final Boolean gethasPACPurchasePending()
   {
      return _hasPACPurchasePending;
   }
	
   /**
    * Gets the Account has pac pending trade field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account has pac pending trade or the specified default value.
    */
   public final boolean gethasPACPurchasePending( boolean defaultValue )
   {
      return _hasPACPurchasePending == null ? defaultValue : _hasPACPurchasePending.booleanValue();
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
      _AcctCommitMstrUUID = responseBuffer.decodeString(responseBuffer.getNextField());
      _CommitmentUUID = responseBuffer.decodeString(responseBuffer.getNextField());
      _CommitmentCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _CommitmentDesc = responseBuffer.decodeString(responseBuffer.getNextField());
      _CommitDeff = responseBuffer.decodeDate(responseBuffer.getNextField());
      _CommitEndDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _BeneName = responseBuffer.decodeString(responseBuffer.getNextField());
      _OrigBeneName = responseBuffer.decodeString(responseBuffer.getNextField());
      _CommitStatus = responseBuffer.decodeString(responseBuffer.getNextField());
      _CommitStatusDesc = responseBuffer.decodeString(responseBuffer.getNextField());
      _CommitAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _OrigAccountNum = responseBuffer.decodeString(responseBuffer.getNextField());
      _CommissionPaid = responseBuffer.decodeString(responseBuffer.getNextField());
      _SurrChrgApplied = responseBuffer.decodeString(responseBuffer.getNextField());
      _MaxSurrCharges = responseBuffer.decodeString(responseBuffer.getNextField());
      _CommittedPACS = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _PaidPACS = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _MissingPACS = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _Username = responseBuffer.decodeString(responseBuffer.getNextField());
      _ProcessDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _ModUser = responseBuffer.decodeString(responseBuffer.getNextField());
      _ModDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _PACID = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _PACDeff = responseBuffer.decodeDate(responseBuffer.getNextField());
      _PACAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _PACStopDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _InstCode = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _SwiftCode = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _RefNumber = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _TransitNo = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _BankAcctNum = responseBuffer.decodeString(responseBuffer.getNextField());
      _BankAcctName = responseBuffer.decodeString(responseBuffer.getNextField());
      _SourceOfBankAcct = responseBuffer.decodeString(responseBuffer.getNextField());
      _BankAcctCurrency = responseBuffer.decodeString(responseBuffer.getNextField());
      _BankAcctType = responseBuffer.decodeString(responseBuffer.getNextField());
      _BankType = responseBuffer.decodeString(responseBuffer.getNextField());
      _BankIdNum = responseBuffer.decodeString(responseBuffer.getNextField());
      _ACHProcessor = responseBuffer.decodeString(responseBuffer.getNextField());
      _BankId = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _CreditInfoLine1 = responseBuffer.decodeString(responseBuffer.getNextField());
      _CreditInfoLine2 = responseBuffer.decodeString(responseBuffer.getNextField());
      _InstName = responseBuffer.decodeString(responseBuffer.getNextField());
      _BankAddr1 = responseBuffer.decodeString(responseBuffer.getNextField());
      _BankAddr2 = responseBuffer.decodeString(responseBuffer.getNextField());
      _BankAddr3 = responseBuffer.decodeString(responseBuffer.getNextField());
      _BankAddr4 = responseBuffer.decodeString(responseBuffer.getNextField());
      _BankAddr5 = responseBuffer.decodeString(responseBuffer.getNextField());
      _BankContact = responseBuffer.decodeString(responseBuffer.getNextField());
      _BankCntry = responseBuffer.decodeString(responseBuffer.getNextField());
      _BankPstl = responseBuffer.decodeString(responseBuffer.getNextField());
      _PayReason1 = responseBuffer.decodeString(responseBuffer.getNextField());
      _PayReason2 = responseBuffer.decodeString(responseBuffer.getNextField());
      _Paymethod = responseBuffer.decodeString(responseBuffer.getNextField());
      _BankDetlVer = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _CommitMstrVer = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _PaidPACSAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _LastProcDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _NextProcDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _hasPACPurchasePending = responseBuffer.decodeBoolean(responseBuffer.getNextField());
                  

   }

}
      
