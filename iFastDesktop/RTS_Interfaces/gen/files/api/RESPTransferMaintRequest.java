// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * RESP Transfer Info Maint and Validation request.
 * For additional view information see <A HREF="../../../../viewspecs/RESPTransferMaint.doc">RESPTransferMaint.doc</A>.
 * 
 * @author RTS Generated
 */
public class RESPTransferMaintRequest extends IFastRequest implements Serializable
{

   /**
    * Session ID member variable.
    */
   private String _SessionId = "";
            
   /**
    * User ID member variable.
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
    * Call Type member variable.
    */
   private String _CallType = "";
            
   /**
    * Trade Type member variable.
    */
   private String _TradeType = "";
            
   /**
    * Transaction Number member variable.
    */
   private String _TransId = "0";
            
   /**
    * Transaction Type member variable.
    */
   private String _TransType = "";
            
   /**
    * Deposit Type member variable.
    */
   private Integer _DepositType = null;
            
   /**
    * Redemption Code member variable.
    */
   private String _RedCode = "";
            
   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Account To member variable.
    */
   private String _AccountTo = "0";
            
   /**
    * Effective Date member variable.
    */
   private Date _EffectiveDate = null;
            
   /**
    * Amount member variable.
    */
   private String _Amount = "0";
            
   /**
    * Flag indicating if RESP Transfer Info letter is required member variable.
    */
   private Boolean _RESPLetter = new Boolean(false);
            
   /**
    * Updatable for ExternalTrfIn and acct level member variable.
    */
   private Boolean _TranStatus = new Boolean(false);
            
   /**
    * Plan number1 for transaction type transfer member variable.
    */
   private String _PlanNum1 = "";
            
   /**
    * Contract Id 1 for transaction type transfer member variable.
    */
   private String _ContractId1 = "";
            
   /**
    * Plan number2 for transaction type transfer member variable.
    */
   private String _PlanNum2 = "";
            
   /**
    * Contract Id 2 for transaction type transfer member variable.
    */
   private String _ContractID2 = "";
            
   /**
    * NEQ number 1 member variable.
    */
   private String _NEQ1 = "";
            
   /**
    * NEQ number 2 member variable.
    */
   private String _NEQ2 = "";
            
   /**
    * Account Level Override member variable.
    */
   private Boolean _AcctLvlOverride = new Boolean(false);
            
   /**
    * Inception Date member variable.
    */
   private Date _InceptionDate = null;
            
   /**
    * Termination Date member variable.
    */
   private Date _TerminationDate = null;
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * Run Mode member array.
    */
   private String[] _RunMode = new String[25];
            
   /**
    * RecordLevel member array.
    */
   private String[] _RecordLevel = new String[25];
            
   /**
    * RESP Beneficiary ID member array.
    */
   private String[] _RESPBenefID = new String[25];
            
   /**
    * Entity Type member array.
    */
   private String[] _EntityType = new String[25];
            
   /**
    * Entity Type Sequnce member array.
    */
   private Integer[] _EntityTypeSeq = new Integer[25];
            
   /**
    * RESP Beneficiary ID To member array.
    */
   private String[] _RESPBenefIDTo = new String[25];
            
   /**
    * Entity Type To member array.
    */
   private String[] _EntityTypeTo = new String[25];
            
   /**
    * Entity Type Sequnce To member array.
    */
   private Integer[] _EntityTypeSeqTo = new Integer[25];
            
   /**
    * Year to Date Contributions member array.
    */
   private String[] _YTDContribution = new String[25];
            
   /**
    * Contributions made to date transferred into RESP member array.
    */
   private String[] _TDContribution = new String[25];
            
   /**
    * Grant Amount Awarded member array.
    */
   private String[] _GrantAmount = new String[25];
            
   /**
    * Additional CES Grant Amount member array.
    */
   private String[] _AdditionalGrant = new String[25];
            
   /**
    * CLB Amount of the trade member array.
    */
   private String[] _CLBAmount = new String[25];
            
   /**
    * P-Grant Amount of the Transaction member array.
    */
   private String[] _PGrantAmount = new String[25];
            
   /**
    * Withdrawal of COntributions transferred in member array.
    */
   private String[] _TDRedContrib = new String[25];
            
   /**
    * Redemptions of Earnings to date member array.
    */
   private String[] _TDRedEarnings = new String[25];
            
   /**
    * Redemption of CESG member array.
    */
   private String[] _RedCESG = new String[25];
            
   /**
    * Redemption of CLB member array.
    */
   private String[] _RedCLB = new String[25];
            
   /**
    * Redemption of P-Grant member array.
    */
   private String[] _RedPGrant = new String[25];
            
   /**
    * Contribution that does NOT attract CESG member array.
    */
   private String[] _UCAmount = new String[25];
            
   /**
    * Contribution that DOES attact CESG member array.
    */
   private String[] _ACAmount = new String[25];
            
   /**
    * Pre-1998 Contribution Amount member array.
    */
   private String[] _Pre98Contrib = new String[25];
            
   /**
    * Pre-1998 Redemption of Contribution Amount member array.
    */
   private String[] _Pre98RedContrib = new String[25];
            
   /**
    * Transfer Percent member array.
    */
   private String[] _TransferPercent = new String[25];
            
   /**
    * Unassisted Contribution member array.
    */
   private String[] _QESIUCAmount = new String[25];
            
   /**
    * Assisted Contribution member array.
    */
   private String[] _QESIACAmount = new String[25];
            
   /**
    * YTD Contribution member array.
    */
   private String[] _QESIYTDContribution = new String[25];
            
   /**
    * Basic Grant member array.
    */
   private String[] _QESIBasicGrant = new String[25];
            
   /**
    * Additional Grant member array.
    */
   private String[] _QESIIncreaseAmt = new String[25];
            
   /**
    * Pre98 Contribution member array.
    */
   private String[] _Pre98QESIContrib = new String[25];
            
   /**
    * Pre Contribution member array.
    */
   private String[] _Pre2007QESIContrib = new String[25];
            
   /**
    * RESP External Transfer Detail UUID member array.
    */
   private String[] _RESPExtTrDetlUUID = new String[25];
            
   /**
    * RESP External Transfer Detail Version member array.
    */
   private Integer[] _RESPExtTrDetlVer = new Integer[25];
            
   /**
    * RESP Contribution Detail UUID member array.
    */
   private String[] _RESPContrDetlUUID = new String[25];
            
   /**
    * RESP Contribution Detail Version member array.
    */
   private Integer[] _RESPContrDetlVer = new Integer[25];
            
   /**
    * Eligible Transfer member array.
    */
   private Boolean[] _EligTransfer = new Boolean[25];
            
   /**
    * Total Transfer Indicator member array.
    */
   private String[] _TotTransfINDC = new String[25];
            
   /**
    * Historical Non Trustee Year member array.
    */
   private Integer[] _HistNonTrustYear = new Integer[25];
            
   /**
    * CESG Paid member array.
    */
   private String[] _CESGPaid = new String[25];
            
   /**
    * QESI Paid member array.
    */
   private String[] _QESIPaid = new String[25];
            
   /**
    * SAGES Grant member array.
    */
   private String[] _SAGESGrant = new String[25];
            
   /**
    * SAGES UC Amount member array.
    */
   private String[] _SAGESUCAmount = new String[25];
            
   /**
    * SAGES AC Amount member array.
    */
   private String[] _SAGESACAmount = new String[25];
            

   /**
    * Constructs the RESPTransferMaintRequest object.
    * 
    */
   RESPTransferMaintRequest()
   {
      super ( 407 );
   }

   /**
    * Constructs the RESPTransferMaintRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   RESPTransferMaintRequest( String hostEncoding )
   {
      super ( 407, hostEncoding );
   }

   /**
    * Sets the Session ID field for the request.
    * 
    * @param value  Value that the Session ID will be set to.
    */
   public final void setSessionId( String value )
   {
      assertUnsent();
      _SessionId = value;
   }
	
   /**
    * Sets the User ID field for the request.
    * 
    * @param value  Value that the User ID will be set to.
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
    * Sets the Call Type field for the request.
    * 
    * @param value  Value that the Call Type will be set to.
    */
   public final void setCallType( String value )
   {
      assertUnsent();
      _CallType = value;
   }
	
   /**
    * Sets the Trade Type field for the request.
    * 
    * @param value  Value that the Trade Type will be set to.
    */
   public final void setTradeType( String value )
   {
      assertUnsent();
      _TradeType = value;
   }
	
   /**
    * Sets the Transaction Number field for the request.
    * 
    * @param value  Value that the Transaction Number will be set to.
    */
   public final void setTransId( String value )
   {
      assertUnsent();
      _TransId = value;
   }
	
   /**
    * Sets the Transaction Type field for the request.
    * 
    * @param value  Value that the Transaction Type will be set to.
    */
   public final void setTransType( String value )
   {
      assertUnsent();
      _TransType = value;
   }
	
   /**
    * Sets the Deposit Type field for the request.
    * 
    * @param value  Value that the Deposit Type will be set to.
    */
   public final void setDepositType( Integer value )
   {
      assertUnsent();
      _DepositType = value;
   }
	
   /**
    * Sets the Redemption Code field for the request.
    * 
    * @param value  Value that the Redemption Code will be set to.
    */
   public final void setRedCode( String value )
   {
      assertUnsent();
      _RedCode = value;
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
    * Sets the Account To field for the request.
    * 
    * @param value  Value that the Account To will be set to.
    */
   public final void setAccountTo( String value )
   {
      assertUnsent();
      _AccountTo = value;
   }
	
   /**
    * Sets the Effective Date field for the request.
    * 
    * @param value  Value that the Effective Date will be set to.
    */
   public final void setEffectiveDate( Date value )
   {
      assertUnsent();
      _EffectiveDate = value;
   }
	
   /**
    * Sets the Amount field for the request.
    * 
    * @param value  Value that the Amount will be set to.
    */
   public final void setAmount( String value )
   {
      assertUnsent();
      _Amount = value;
   }
	
   /**
    * Sets the Flag indicating if RESP Transfer Info letter is required field for the request.
    * 
    * @param value  Value that the Flag indicating if RESP Transfer Info letter is required will be set to.
    */
   public final void setRESPLetter( Boolean value )
   {
      assertUnsent();
      _RESPLetter = value;
   }
	
   /**
    * Sets the Updatable for ExternalTrfIn and acct level field for the request.
    * 
    * @param value  Value that the Updatable for ExternalTrfIn and acct level will be set to.
    */
   public final void setTranStatus( Boolean value )
   {
      assertUnsent();
      _TranStatus = value;
   }
	
   /**
    * Sets the Plan number1 for transaction type transfer field for the request.
    * 
    * @param value  Value that the Plan number1 for transaction type transfer will be set to.
    */
   public final void setPlanNum1( String value )
   {
      assertUnsent();
      _PlanNum1 = value;
   }
	
   /**
    * Sets the Contract Id 1 for transaction type transfer field for the request.
    * 
    * @param value  Value that the Contract Id 1 for transaction type transfer will be set to.
    */
   public final void setContractId1( String value )
   {
      assertUnsent();
      _ContractId1 = value;
   }
	
   /**
    * Sets the Plan number2 for transaction type transfer field for the request.
    * 
    * @param value  Value that the Plan number2 for transaction type transfer will be set to.
    */
   public final void setPlanNum2( String value )
   {
      assertUnsent();
      _PlanNum2 = value;
   }
	
   /**
    * Sets the Contract Id 2 for transaction type transfer field for the request.
    * 
    * @param value  Value that the Contract Id 2 for transaction type transfer will be set to.
    */
   public final void setContractID2( String value )
   {
      assertUnsent();
      _ContractID2 = value;
   }
	
   /**
    * Sets the NEQ number 1 field for the request.
    * 
    * @param value  Value that the NEQ number 1 will be set to.
    */
   public final void setNEQ1( String value )
   {
      assertUnsent();
      _NEQ1 = value;
   }
	
   /**
    * Sets the NEQ number 2 field for the request.
    * 
    * @param value  Value that the NEQ number 2 will be set to.
    */
   public final void setNEQ2( String value )
   {
      assertUnsent();
      _NEQ2 = value;
   }
	
   /**
    * Sets the Account Level Override field for the request.
    * 
    * @param value  Value that the Account Level Override will be set to.
    */
   public final void setAcctLvlOverride( Boolean value )
   {
      assertUnsent();
      _AcctLvlOverride = value;
   }
	
   /**
    * Sets the Inception Date field for the request.
    * 
    * @param value  Value that the Inception Date will be set to.
    */
   public final void setInceptionDate( Date value )
   {
      assertUnsent();
      _InceptionDate = value;
   }
	
   /**
    * Sets the Termination Date field for the request.
    * 
    * @param value  Value that the Termination Date will be set to.
    */
   public final void setTerminationDate( Date value )
   {
      assertUnsent();
      _TerminationDate = value;
   }
	
   /**
    * Sets the Record Count for the repeatable request.
    * 
    * @param value    Value that the Record Count will be set to.
    */
   public final void setRepeatCount( int value )
   {
      _RepeatCount = value;
   }
         
   /**
    * Sets the Run Mode field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Run Mode will be set to.
    */
   public final void setRunMode( int index, String value )
   {
      assertUnsent();
      _RunMode[index] = value;
   }
	
   /**
    * Sets the RecordLevel field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the RecordLevel will be set to.
    */
   public final void setRecordLevel( int index, String value )
   {
      assertUnsent();
      _RecordLevel[index] = value;
   }
	
   /**
    * Sets the RESP Beneficiary ID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the RESP Beneficiary ID will be set to.
    */
   public final void setRESPBenefID( int index, String value )
   {
      assertUnsent();
      _RESPBenefID[index] = value;
   }
	
   /**
    * Sets the Entity Type field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Entity Type will be set to.
    */
   public final void setEntityType( int index, String value )
   {
      assertUnsent();
      _EntityType[index] = value;
   }
	
   /**
    * Sets the Entity Type Sequnce field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Entity Type Sequnce will be set to.
    */
   public final void setEntityTypeSeq( int index, Integer value )
   {
      assertUnsent();
      _EntityTypeSeq[index] = value;
   }
	
   /**
    * Sets the RESP Beneficiary ID To field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the RESP Beneficiary ID To will be set to.
    */
   public final void setRESPBenefIDTo( int index, String value )
   {
      assertUnsent();
      _RESPBenefIDTo[index] = value;
   }
	
   /**
    * Sets the Entity Type To field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Entity Type To will be set to.
    */
   public final void setEntityTypeTo( int index, String value )
   {
      assertUnsent();
      _EntityTypeTo[index] = value;
   }
	
   /**
    * Sets the Entity Type Sequnce To field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Entity Type Sequnce To will be set to.
    */
   public final void setEntityTypeSeqTo( int index, Integer value )
   {
      assertUnsent();
      _EntityTypeSeqTo[index] = value;
   }
	
   /**
    * Sets the Year to Date Contributions field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Year to Date Contributions will be set to.
    */
   public final void setYTDContribution( int index, String value )
   {
      assertUnsent();
      _YTDContribution[index] = value;
   }
	
   /**
    * Sets the Contributions made to date transferred into RESP field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Contributions made to date transferred into RESP will be set to.
    */
   public final void setTDContribution( int index, String value )
   {
      assertUnsent();
      _TDContribution[index] = value;
   }
	
   /**
    * Sets the Grant Amount Awarded field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Grant Amount Awarded will be set to.
    */
   public final void setGrantAmount( int index, String value )
   {
      assertUnsent();
      _GrantAmount[index] = value;
   }
	
   /**
    * Sets the Additional CES Grant Amount field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Additional CES Grant Amount will be set to.
    */
   public final void setAdditionalGrant( int index, String value )
   {
      assertUnsent();
      _AdditionalGrant[index] = value;
   }
	
   /**
    * Sets the CLB Amount of the trade field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the CLB Amount of the trade will be set to.
    */
   public final void setCLBAmount( int index, String value )
   {
      assertUnsent();
      _CLBAmount[index] = value;
   }
	
   /**
    * Sets the P-Grant Amount of the Transaction field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the P-Grant Amount of the Transaction will be set to.
    */
   public final void setPGrantAmount( int index, String value )
   {
      assertUnsent();
      _PGrantAmount[index] = value;
   }
	
   /**
    * Sets the Withdrawal of COntributions transferred in field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Withdrawal of COntributions transferred in will be set to.
    */
   public final void setTDRedContrib( int index, String value )
   {
      assertUnsent();
      _TDRedContrib[index] = value;
   }
	
   /**
    * Sets the Redemptions of Earnings to date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Redemptions of Earnings to date will be set to.
    */
   public final void setTDRedEarnings( int index, String value )
   {
      assertUnsent();
      _TDRedEarnings[index] = value;
   }
	
   /**
    * Sets the Redemption of CESG field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Redemption of CESG will be set to.
    */
   public final void setRedCESG( int index, String value )
   {
      assertUnsent();
      _RedCESG[index] = value;
   }
	
   /**
    * Sets the Redemption of CLB field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Redemption of CLB will be set to.
    */
   public final void setRedCLB( int index, String value )
   {
      assertUnsent();
      _RedCLB[index] = value;
   }
	
   /**
    * Sets the Redemption of P-Grant field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Redemption of P-Grant will be set to.
    */
   public final void setRedPGrant( int index, String value )
   {
      assertUnsent();
      _RedPGrant[index] = value;
   }
	
   /**
    * Sets the Contribution that does NOT attract CESG field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Contribution that does NOT attract CESG will be set to.
    */
   public final void setUCAmount( int index, String value )
   {
      assertUnsent();
      _UCAmount[index] = value;
   }
	
   /**
    * Sets the Contribution that DOES attact CESG field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Contribution that DOES attact CESG will be set to.
    */
   public final void setACAmount( int index, String value )
   {
      assertUnsent();
      _ACAmount[index] = value;
   }
	
   /**
    * Sets the Pre-1998 Contribution Amount field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Pre-1998 Contribution Amount will be set to.
    */
   public final void setPre98Contrib( int index, String value )
   {
      assertUnsent();
      _Pre98Contrib[index] = value;
   }
	
   /**
    * Sets the Pre-1998 Redemption of Contribution Amount field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Pre-1998 Redemption of Contribution Amount will be set to.
    */
   public final void setPre98RedContrib( int index, String value )
   {
      assertUnsent();
      _Pre98RedContrib[index] = value;
   }
	
   /**
    * Sets the Transfer Percent field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Transfer Percent will be set to.
    */
   public final void setTransferPercent( int index, String value )
   {
      assertUnsent();
      _TransferPercent[index] = value;
   }
	
   /**
    * Sets the Unassisted Contribution field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Unassisted Contribution will be set to.
    */
   public final void setQESIUCAmount( int index, String value )
   {
      assertUnsent();
      _QESIUCAmount[index] = value;
   }
	
   /**
    * Sets the Assisted Contribution field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Assisted Contribution will be set to.
    */
   public final void setQESIACAmount( int index, String value )
   {
      assertUnsent();
      _QESIACAmount[index] = value;
   }
	
   /**
    * Sets the YTD Contribution field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the YTD Contribution will be set to.
    */
   public final void setQESIYTDContribution( int index, String value )
   {
      assertUnsent();
      _QESIYTDContribution[index] = value;
   }
	
   /**
    * Sets the Basic Grant field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Basic Grant will be set to.
    */
   public final void setQESIBasicGrant( int index, String value )
   {
      assertUnsent();
      _QESIBasicGrant[index] = value;
   }
	
   /**
    * Sets the Additional Grant field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Additional Grant will be set to.
    */
   public final void setQESIIncreaseAmt( int index, String value )
   {
      assertUnsent();
      _QESIIncreaseAmt[index] = value;
   }
	
   /**
    * Sets the Pre98 Contribution field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Pre98 Contribution will be set to.
    */
   public final void setPre98QESIContrib( int index, String value )
   {
      assertUnsent();
      _Pre98QESIContrib[index] = value;
   }
	
   /**
    * Sets the Pre Contribution field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Pre Contribution will be set to.
    */
   public final void setPre2007QESIContrib( int index, String value )
   {
      assertUnsent();
      _Pre2007QESIContrib[index] = value;
   }
	
   /**
    * Sets the RESP External Transfer Detail UUID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the RESP External Transfer Detail UUID will be set to.
    */
   public final void setRESPExtTrDetlUUID( int index, String value )
   {
      assertUnsent();
      _RESPExtTrDetlUUID[index] = value;
   }
	
   /**
    * Sets the RESP External Transfer Detail Version field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the RESP External Transfer Detail Version will be set to.
    */
   public final void setRESPExtTrDetlVer( int index, Integer value )
   {
      assertUnsent();
      _RESPExtTrDetlVer[index] = value;
   }
	
   /**
    * Sets the RESP Contribution Detail UUID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the RESP Contribution Detail UUID will be set to.
    */
   public final void setRESPContrDetlUUID( int index, String value )
   {
      assertUnsent();
      _RESPContrDetlUUID[index] = value;
   }
	
   /**
    * Sets the RESP Contribution Detail Version field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the RESP Contribution Detail Version will be set to.
    */
   public final void setRESPContrDetlVer( int index, Integer value )
   {
      assertUnsent();
      _RESPContrDetlVer[index] = value;
   }
	
   /**
    * Sets the Eligible Transfer field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Eligible Transfer will be set to.
    */
   public final void setEligTransfer( int index, Boolean value )
   {
      assertUnsent();
      _EligTransfer[index] = value;
   }
	
   /**
    * Sets the Total Transfer Indicator field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Total Transfer Indicator will be set to.
    */
   public final void setTotTransfINDC( int index, String value )
   {
      assertUnsent();
      _TotTransfINDC[index] = value;
   }
	
   /**
    * Sets the Historical Non Trustee Year field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Historical Non Trustee Year will be set to.
    */
   public final void setHistNonTrustYear( int index, Integer value )
   {
      assertUnsent();
      _HistNonTrustYear[index] = value;
   }
	
   /**
    * Sets the CESG Paid field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the CESG Paid will be set to.
    */
   public final void setCESGPaid( int index, String value )
   {
      assertUnsent();
      _CESGPaid[index] = value;
   }
	
   /**
    * Sets the QESI Paid field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the QESI Paid will be set to.
    */
   public final void setQESIPaid( int index, String value )
   {
      assertUnsent();
      _QESIPaid[index] = value;
   }
	
   /**
    * Sets the SAGES Grant field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the SAGES Grant will be set to.
    */
   public final void setSAGESGrant( int index, String value )
   {
      assertUnsent();
      _SAGESGrant[index] = value;
   }
	
   /**
    * Sets the SAGES UC Amount field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the SAGES UC Amount will be set to.
    */
   public final void setSAGESUCAmount( int index, String value )
   {
      assertUnsent();
      _SAGESUCAmount[index] = value;
   }
	
   /**
    * Sets the SAGES AC Amount field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the SAGES AC Amount will be set to.
    */
   public final void setSAGESACAmount( int index, String value )
   {
      assertUnsent();
      _SAGESACAmount[index] = value;
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
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _CallType );
      requestBuffer.appendField( _TradeType );
      requestBuffer.appendField( _TransId );
      requestBuffer.appendField( _TransType );
      requestBuffer.appendField( _DepositType );
      requestBuffer.appendField( _RedCode );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _AccountTo );
      requestBuffer.appendField( _EffectiveDate );
      requestBuffer.appendField( _Amount );
      requestBuffer.appendField( _RESPLetter );
      requestBuffer.appendField( _TranStatus );
      requestBuffer.appendField( _PlanNum1 );
      requestBuffer.appendField( _ContractId1 );
      requestBuffer.appendField( _PlanNum2 );
      requestBuffer.appendField( _ContractID2 );
      requestBuffer.appendField( _NEQ1 );
      requestBuffer.appendField( _NEQ2 );
      requestBuffer.appendField( _AcctLvlOverride );
      requestBuffer.appendField( _InceptionDate );
      requestBuffer.appendField( _TerminationDate );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _RunMode[x] );
         requestBuffer.appendField( _RecordLevel[x] );
         requestBuffer.appendField( _RESPBenefID[x] );
         requestBuffer.appendField( _EntityType[x] );
         requestBuffer.appendField( _EntityTypeSeq[x] );
         requestBuffer.appendField( _RESPBenefIDTo[x] );
         requestBuffer.appendField( _EntityTypeTo[x] );
         requestBuffer.appendField( _EntityTypeSeqTo[x] );
         requestBuffer.appendField( _YTDContribution[x] );
         requestBuffer.appendField( _TDContribution[x] );
         requestBuffer.appendField( _GrantAmount[x] );
         requestBuffer.appendField( _AdditionalGrant[x] );
         requestBuffer.appendField( _CLBAmount[x] );
         requestBuffer.appendField( _PGrantAmount[x] );
         requestBuffer.appendField( _TDRedContrib[x] );
         requestBuffer.appendField( _TDRedEarnings[x] );
         requestBuffer.appendField( _RedCESG[x] );
         requestBuffer.appendField( _RedCLB[x] );
         requestBuffer.appendField( _RedPGrant[x] );
         requestBuffer.appendField( _UCAmount[x] );
         requestBuffer.appendField( _ACAmount[x] );
         requestBuffer.appendField( _Pre98Contrib[x] );
         requestBuffer.appendField( _Pre98RedContrib[x] );
         requestBuffer.appendField( _TransferPercent[x] );
         requestBuffer.appendField( _QESIUCAmount[x] );
         requestBuffer.appendField( _QESIACAmount[x] );
         requestBuffer.appendField( _QESIYTDContribution[x] );
         requestBuffer.appendField( _QESIBasicGrant[x] );
         requestBuffer.appendField( _QESIIncreaseAmt[x] );
         requestBuffer.appendField( _Pre98QESIContrib[x] );
         requestBuffer.appendField( _Pre2007QESIContrib[x] );
         requestBuffer.appendField( _RESPExtTrDetlUUID[x] );
         requestBuffer.appendField( _RESPExtTrDetlVer[x] );
         requestBuffer.appendField( _RESPContrDetlUUID[x] );
         requestBuffer.appendField( _RESPContrDetlVer[x] );
         requestBuffer.appendField( _EligTransfer[x] );
         requestBuffer.appendField( _TotTransfINDC[x] );
         requestBuffer.appendField( _HistNonTrustYear[x] );
         requestBuffer.appendField( _CESGPaid[x] );
         requestBuffer.appendField( _QESIPaid[x] );
         requestBuffer.appendField( _SAGESGrant[x] );
         requestBuffer.appendField( _SAGESUCAmount[x] );
         requestBuffer.appendField( _SAGESACAmount[x] );
      }
   }

}

