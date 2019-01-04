
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * RESP Transfer Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/RESPTransferInq.doc">RESPTransferInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class RESPTransferInqView extends IFastView implements Serializable
{

   /**
    * Plan number1 for transaction type transfer member variable.
    */
   private String _PlanNum1 = null;
   
   /**
    * Contract Id 1 for transaction type transfer member variable.
    */
   private String _ContractId1 = null;
   
   /**
    * Plan number2 for transaction type transfer member variable.
    */
   private String _PlanNum2 = null;
   
   /**
    * Contract Id 2 for transaction type transfer member variable.
    */
   private String _ContractID2 = null;
   
   /**
    * Inception Date member variable.
    */
   private Date _InceptionDate = null;
   
   /**
    * Termination Date member variable.
    */
   private Date _TerminationDate = null;
   
   /**
    * NEQ number 1 member variable.
    */
   private String _NEQ1 = null;
   
   /**
    * NEQ number 2 member variable.
    */
   private String _NEQ2 = null;
   
   /**
    * Account Level Override member variable.
    */
   private Boolean _AcctLvlOverride = null;
   
   /**
    * RESP Letter member variable.
    */
   private Boolean _RESPLetter = null;
   
   /**
    * Transaction status member variable.
    */
   private Boolean _TranStatus = null;
   
   private int _RepeatCount = 0;
   
   /**
    * Record level member array.
    */
   private String[] _RecordLevel = null;
   
   /**
    * Year to Date Contributions member array.
    */
   private String[] _YTDContribution = null;
   
   /**
    * Contributions made to date transferred into RESP member array.
    */
   private String[] _TDContribution = null;
   
   /**
    * Grant Amount Awarded member array.
    */
   private String[] _GrantAmount = null;
   
   /**
    * Additional CES Grant Amount member array.
    */
   private String[] _AdditionalGrant = null;
   
   /**
    * CLB Amount of the trade member array.
    */
   private String[] _CLBAmount = null;
   
   /**
    * P-Grant Amount of the Transaction member array.
    */
   private String[] _PGrantAmount = null;
   
   /**
    * Withdrawal of COntributions transferred in member array.
    */
   private String[] _TDRedContrib = null;
   
   /**
    * Redemptions of Earnings to date member array.
    */
   private String[] _TDRedEarnings = null;
   
   /**
    * Redemption of CESG member array.
    */
   private String[] _RedCESG = null;
   
   /**
    * Redemption of CLB member array.
    */
   private String[] _RedCLB = null;
   
   /**
    * Redemption of P-Grant member array.
    */
   private String[] _RedPGrant = null;
   
   /**
    * Contribution that does NOT attract CESG member array.
    */
   private String[] _UCAmount = null;
   
   /**
    * Contribution that DOES attact CESG member array.
    */
   private String[] _ACAmount = null;
   
   /**
    * Pre-1998 Contribution Amount member array.
    */
   private String[] _Pre98Contrib = null;
   
   /**
    * Pre-1998 Redemption of Contribution Amount member array.
    */
   private String[] _Pre98RedContrib = null;
   
   /**
    * RESP Beneficiary Entity Id member array.
    */
   private String[] _RESPBenefID = null;
   
   /**
    * Entity Type member array.
    */
   private String[] _EntityType = null;
   
   /**
    * Entity Type Sequnce member array.
    */
   private Integer[] _EntityTypeSeq = null;
   
   /**
    * RESP Beneficiary Entity Id to member array.
    */
   private String[] _RESPBenefIDTo = null;
   
   /**
    * Entity Type To member array.
    */
   private String[] _EntityTypeTo = null;
   
   /**
    * Entity Type Sequnce To member array.
    */
   private Integer[] _EntityTypeSeqTo = null;
   
   /**
    * RESP Allocation Percent member array.
    */
   private String[] _RESPAllocPrcnt = null;
   
   /**
    * Beneficiary Tainted member array.
    */
   private Boolean[] _Tainted = null;
   
   /**
    * End Date of Tainting member array.
    */
   private Date[] _TaintEndDate = null;
   
   /**
    * Request Grant member array.
    */
   private Boolean[] _GrantRequest = null;
   
   /**
    * Beneficiary Date of Birth member array.
    */
   private Date[] _BenefDofB = null;
   
   /**
    * Tax Jurisdiction member array.
    */
   private String[] _TaxJuris = null;
   
   /**
    * Relationship member array.
    */
   private String[] _Relation = null;
   
   /**
    * Beneficiary Effective Date member array.
    */
   private Date[] _BenefEffectiveDate = null;
   
   /**
    * Transfer Percent member array.
    */
   private String[] _TransferPercent = null;
   
   /**
    * Unassisted Contribution member array.
    */
   private String[] _QESIUCAmount = null;
   
   /**
    * Assisted Contribution member array.
    */
   private String[] _QESIACAmount = null;
   
   /**
    * YTD Contribution member array.
    */
   private String[] _QESIYTDContribution = null;
   
   /**
    * Basic Grant member array.
    */
   private String[] _QESIBasicGrant = null;
   
   /**
    * Additional Grant member array.
    */
   private String[] _QESIIncreaseAmt = null;
   
   /**
    * Pre98 Contribution member array.
    */
   private String[] _Pre98QESIContrib = null;
   
   /**
    * Pre Contribution member array.
    */
   private String[] _Pre2007QESIContrib = null;
   
   /**
    * RESP External Transfer Detail UUID member array.
    */
   private String[] _RESPExtTrDetlUUID = null;
   
   /**
    * RESP External Transfer Detail Version member array.
    */
   private Integer[] _RESPExtTrDetlVer = null;
   
   /**
    * RESP Contribution Detail UUID member array.
    */
   private String[] _RESPContrDetlUUID = null;
   
   /**
    * RESP Contribution Detail Version member array.
    */
   private Integer[] _RESPContrDetlVer = null;
   
   /**
    * Eligible Transfer member array.
    */
   private Boolean[] _EligTransfer = null;
   
   /**
    * Total Transfer Indicator member array.
    */
   private String[] _TotTransfINDC = null;
   
   /**
    * Historical Non Trustee Year member array.
    */
   private Integer[] _HistNonTrustYear = null;
   
   /**
    * CESG Paid member array.
    */
   private String[] _CESGPaid = null;
   
   /**
    * QESI Paid member array.
    */
   private String[] _QESIPaid = null;
   
   /**
    * IsResidualCESG member array.
    */
   private Boolean[] _IsResidualCESG = null;
   
   /**
    * SAGES Grant member array.
    */
   private String[] _SAGESGrant = null;
   
   /**
    * SAGES UC Amount member array.
    */
   private String[] _SAGESUCAmount = null;
   
   /**
    * SAGES AC Amount member array.
    */
   private String[] _SAGESACAmount = null;
   

   /**
    * Constructs the RESPTransferInqView object.
    * 
    */
   public RESPTransferInqView()
   {
      super ( new RESPTransferInqRequest() );
   }

   /**
    * Constructs the RESPTransferInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public RESPTransferInqView( String hostEncoding )
   {
      super ( new RESPTransferInqRequest( hostEncoding ) );
   }

   /**
    * Gets the RESPTransferInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The RESPTransferInqRequest object.
    */
   public final RESPTransferInqRequest getRequest()
   {
      return (RESPTransferInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Plan number1 for transaction type transfer field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Plan number1 for transaction type transfer or null.
    */
   public final String getPlanNum1()
   {
      return _PlanNum1;
   }
	
   /**
    * Gets the Plan number1 for transaction type transfer field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Plan number1 for transaction type transfer or the specified default value.
    */
   public final String getPlanNum1( String defaultValue )
   {
      return _PlanNum1 == null ? defaultValue : _PlanNum1;
   }
                  
   /**
    * Gets the Contract Id 1 for transaction type transfer field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Contract Id 1 for transaction type transfer or null.
    */
   public final String getContractId1()
   {
      return _ContractId1;
   }
	
   /**
    * Gets the Contract Id 1 for transaction type transfer field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contract Id 1 for transaction type transfer or the specified default value.
    */
   public final String getContractId1( String defaultValue )
   {
      return _ContractId1 == null ? defaultValue : _ContractId1;
   }
                  
   /**
    * Gets the Plan number2 for transaction type transfer field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Plan number2 for transaction type transfer or null.
    */
   public final String getPlanNum2()
   {
      return _PlanNum2;
   }
	
   /**
    * Gets the Plan number2 for transaction type transfer field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Plan number2 for transaction type transfer or the specified default value.
    */
   public final String getPlanNum2( String defaultValue )
   {
      return _PlanNum2 == null ? defaultValue : _PlanNum2;
   }
                  
   /**
    * Gets the Contract Id 2 for transaction type transfer field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Contract Id 2 for transaction type transfer or null.
    */
   public final String getContractID2()
   {
      return _ContractID2;
   }
	
   /**
    * Gets the Contract Id 2 for transaction type transfer field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contract Id 2 for transaction type transfer or the specified default value.
    */
   public final String getContractID2( String defaultValue )
   {
      return _ContractID2 == null ? defaultValue : _ContractID2;
   }
                  
   /**
    * Gets the Inception Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Inception Date or null.
    */
   public final Date getInceptionDate()
   {
      return _InceptionDate;
   }
	
   /**
    * Gets the Inception Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Inception Date or the specified default value.
    */
   public final Date getInceptionDate( Date defaultValue )
   {
      return _InceptionDate == null ? defaultValue : _InceptionDate;
   }
                  
   /**
    * Gets the Termination Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Termination Date or null.
    */
   public final Date getTerminationDate()
   {
      return _TerminationDate;
   }
	
   /**
    * Gets the Termination Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Termination Date or the specified default value.
    */
   public final Date getTerminationDate( Date defaultValue )
   {
      return _TerminationDate == null ? defaultValue : _TerminationDate;
   }
                  
   /**
    * Gets the NEQ number 1 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the NEQ number 1 or null.
    */
   public final String getNEQ1()
   {
      return _NEQ1;
   }
	
   /**
    * Gets the NEQ number 1 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the NEQ number 1 or the specified default value.
    */
   public final String getNEQ1( String defaultValue )
   {
      return _NEQ1 == null ? defaultValue : _NEQ1;
   }
                  
   /**
    * Gets the NEQ number 2 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the NEQ number 2 or null.
    */
   public final String getNEQ2()
   {
      return _NEQ2;
   }
	
   /**
    * Gets the NEQ number 2 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the NEQ number 2 or the specified default value.
    */
   public final String getNEQ2( String defaultValue )
   {
      return _NEQ2 == null ? defaultValue : _NEQ2;
   }
                  
   /**
    * Gets the Account Level Override field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Account Level Override or null.
    */
   public final Boolean getAcctLvlOverride()
   {
      return _AcctLvlOverride;
   }
	
   /**
    * Gets the Account Level Override field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Level Override or the specified default value.
    */
   public final boolean getAcctLvlOverride( boolean defaultValue )
   {
      return _AcctLvlOverride == null ? defaultValue : _AcctLvlOverride.booleanValue();
   }
                  
   /**
    * Gets the RESP Letter field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the RESP Letter or null.
    */
   public final Boolean getRESPLetter()
   {
      return _RESPLetter;
   }
	
   /**
    * Gets the RESP Letter field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RESP Letter or the specified default value.
    */
   public final boolean getRESPLetter( boolean defaultValue )
   {
      return _RESPLetter == null ? defaultValue : _RESPLetter.booleanValue();
   }
                  
   /**
    * Gets the Transaction status field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Transaction status or null.
    */
   public final Boolean getTranStatus()
   {
      return _TranStatus;
   }
	
   /**
    * Gets the Transaction status field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transaction status or the specified default value.
    */
   public final boolean getTranStatus( boolean defaultValue )
   {
      return _TranStatus == null ? defaultValue : _TranStatus.booleanValue();
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
    * Gets the Record level field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Record level or null.
    */
   public final String getRecordLevel( int index )
   {
      return _RecordLevel[index];
   }
    
   /**
    * Gets the Record level field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Record level or the specified default value.
    */
   public final String getRecordLevel( int index, String defaultValue )
   {
      return _RecordLevel[index] == null ? defaultValue : _RecordLevel[index];
   }
    
   /**
    * Gets the array of Record level fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Record level values.
    */
   public final String[] getRecordLevelArray()
   {
      return _RecordLevel;
   }
    
   /**
    * Gets the Year to Date Contributions field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Year to Date Contributions or null.
    */
   public final String getYTDContribution( int index )
   {
      return _YTDContribution[index];
   }
    
   /**
    * Gets the Year to Date Contributions field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Year to Date Contributions or the specified default value.
    */
   public final String getYTDContribution( int index, String defaultValue )
   {
      return _YTDContribution[index] == null ? defaultValue : _YTDContribution[index];
   }
    
   /**
    * Gets the array of Year to Date Contributions fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Year to Date Contributions values.
    */
   public final String[] getYTDContributionArray()
   {
      return _YTDContribution;
   }
    
   /**
    * Gets the Contributions made to date transferred into RESP field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contributions made to date transferred into RESP or null.
    */
   public final String getTDContribution( int index )
   {
      return _TDContribution[index];
   }
    
   /**
    * Gets the Contributions made to date transferred into RESP field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contributions made to date transferred into RESP or the specified default value.
    */
   public final String getTDContribution( int index, String defaultValue )
   {
      return _TDContribution[index] == null ? defaultValue : _TDContribution[index];
   }
    
   /**
    * Gets the array of Contributions made to date transferred into RESP fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contributions made to date transferred into RESP values.
    */
   public final String[] getTDContributionArray()
   {
      return _TDContribution;
   }
    
   /**
    * Gets the Grant Amount Awarded field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Grant Amount Awarded or null.
    */
   public final String getGrantAmount( int index )
   {
      return _GrantAmount[index];
   }
    
   /**
    * Gets the Grant Amount Awarded field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Grant Amount Awarded or the specified default value.
    */
   public final String getGrantAmount( int index, String defaultValue )
   {
      return _GrantAmount[index] == null ? defaultValue : _GrantAmount[index];
   }
    
   /**
    * Gets the array of Grant Amount Awarded fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Grant Amount Awarded values.
    */
   public final String[] getGrantAmountArray()
   {
      return _GrantAmount;
   }
    
   /**
    * Gets the Additional CES Grant Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Additional CES Grant Amount or null.
    */
   public final String getAdditionalGrant( int index )
   {
      return _AdditionalGrant[index];
   }
    
   /**
    * Gets the Additional CES Grant Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Additional CES Grant Amount or the specified default value.
    */
   public final String getAdditionalGrant( int index, String defaultValue )
   {
      return _AdditionalGrant[index] == null ? defaultValue : _AdditionalGrant[index];
   }
    
   /**
    * Gets the array of Additional CES Grant Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Additional CES Grant Amount values.
    */
   public final String[] getAdditionalGrantArray()
   {
      return _AdditionalGrant;
   }
    
   /**
    * Gets the CLB Amount of the trade field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the CLB Amount of the trade or null.
    */
   public final String getCLBAmount( int index )
   {
      return _CLBAmount[index];
   }
    
   /**
    * Gets the CLB Amount of the trade field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the CLB Amount of the trade or the specified default value.
    */
   public final String getCLBAmount( int index, String defaultValue )
   {
      return _CLBAmount[index] == null ? defaultValue : _CLBAmount[index];
   }
    
   /**
    * Gets the array of CLB Amount of the trade fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of CLB Amount of the trade values.
    */
   public final String[] getCLBAmountArray()
   {
      return _CLBAmount;
   }
    
   /**
    * Gets the P-Grant Amount of the Transaction field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the P-Grant Amount of the Transaction or null.
    */
   public final String getPGrantAmount( int index )
   {
      return _PGrantAmount[index];
   }
    
   /**
    * Gets the P-Grant Amount of the Transaction field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the P-Grant Amount of the Transaction or the specified default value.
    */
   public final String getPGrantAmount( int index, String defaultValue )
   {
      return _PGrantAmount[index] == null ? defaultValue : _PGrantAmount[index];
   }
    
   /**
    * Gets the array of P-Grant Amount of the Transaction fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of P-Grant Amount of the Transaction values.
    */
   public final String[] getPGrantAmountArray()
   {
      return _PGrantAmount;
   }
    
   /**
    * Gets the Withdrawal of COntributions transferred in field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Withdrawal of COntributions transferred in or null.
    */
   public final String getTDRedContrib( int index )
   {
      return _TDRedContrib[index];
   }
    
   /**
    * Gets the Withdrawal of COntributions transferred in field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Withdrawal of COntributions transferred in or the specified default value.
    */
   public final String getTDRedContrib( int index, String defaultValue )
   {
      return _TDRedContrib[index] == null ? defaultValue : _TDRedContrib[index];
   }
    
   /**
    * Gets the array of Withdrawal of COntributions transferred in fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Withdrawal of COntributions transferred in values.
    */
   public final String[] getTDRedContribArray()
   {
      return _TDRedContrib;
   }
    
   /**
    * Gets the Redemptions of Earnings to date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Redemptions of Earnings to date or null.
    */
   public final String getTDRedEarnings( int index )
   {
      return _TDRedEarnings[index];
   }
    
   /**
    * Gets the Redemptions of Earnings to date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Redemptions of Earnings to date or the specified default value.
    */
   public final String getTDRedEarnings( int index, String defaultValue )
   {
      return _TDRedEarnings[index] == null ? defaultValue : _TDRedEarnings[index];
   }
    
   /**
    * Gets the array of Redemptions of Earnings to date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Redemptions of Earnings to date values.
    */
   public final String[] getTDRedEarningsArray()
   {
      return _TDRedEarnings;
   }
    
   /**
    * Gets the Redemption of CESG field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Redemption of CESG or null.
    */
   public final String getRedCESG( int index )
   {
      return _RedCESG[index];
   }
    
   /**
    * Gets the Redemption of CESG field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Redemption of CESG or the specified default value.
    */
   public final String getRedCESG( int index, String defaultValue )
   {
      return _RedCESG[index] == null ? defaultValue : _RedCESG[index];
   }
    
   /**
    * Gets the array of Redemption of CESG fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Redemption of CESG values.
    */
   public final String[] getRedCESGArray()
   {
      return _RedCESG;
   }
    
   /**
    * Gets the Redemption of CLB field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Redemption of CLB or null.
    */
   public final String getRedCLB( int index )
   {
      return _RedCLB[index];
   }
    
   /**
    * Gets the Redemption of CLB field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Redemption of CLB or the specified default value.
    */
   public final String getRedCLB( int index, String defaultValue )
   {
      return _RedCLB[index] == null ? defaultValue : _RedCLB[index];
   }
    
   /**
    * Gets the array of Redemption of CLB fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Redemption of CLB values.
    */
   public final String[] getRedCLBArray()
   {
      return _RedCLB;
   }
    
   /**
    * Gets the Redemption of P-Grant field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Redemption of P-Grant or null.
    */
   public final String getRedPGrant( int index )
   {
      return _RedPGrant[index];
   }
    
   /**
    * Gets the Redemption of P-Grant field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Redemption of P-Grant or the specified default value.
    */
   public final String getRedPGrant( int index, String defaultValue )
   {
      return _RedPGrant[index] == null ? defaultValue : _RedPGrant[index];
   }
    
   /**
    * Gets the array of Redemption of P-Grant fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Redemption of P-Grant values.
    */
   public final String[] getRedPGrantArray()
   {
      return _RedPGrant;
   }
    
   /**
    * Gets the Contribution that does NOT attract CESG field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contribution that does NOT attract CESG or null.
    */
   public final String getUCAmount( int index )
   {
      return _UCAmount[index];
   }
    
   /**
    * Gets the Contribution that does NOT attract CESG field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contribution that does NOT attract CESG or the specified default value.
    */
   public final String getUCAmount( int index, String defaultValue )
   {
      return _UCAmount[index] == null ? defaultValue : _UCAmount[index];
   }
    
   /**
    * Gets the array of Contribution that does NOT attract CESG fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contribution that does NOT attract CESG values.
    */
   public final String[] getUCAmountArray()
   {
      return _UCAmount;
   }
    
   /**
    * Gets the Contribution that DOES attact CESG field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contribution that DOES attact CESG or null.
    */
   public final String getACAmount( int index )
   {
      return _ACAmount[index];
   }
    
   /**
    * Gets the Contribution that DOES attact CESG field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contribution that DOES attact CESG or the specified default value.
    */
   public final String getACAmount( int index, String defaultValue )
   {
      return _ACAmount[index] == null ? defaultValue : _ACAmount[index];
   }
    
   /**
    * Gets the array of Contribution that DOES attact CESG fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contribution that DOES attact CESG values.
    */
   public final String[] getACAmountArray()
   {
      return _ACAmount;
   }
    
   /**
    * Gets the Pre-1998 Contribution Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Pre-1998 Contribution Amount or null.
    */
   public final String getPre98Contrib( int index )
   {
      return _Pre98Contrib[index];
   }
    
   /**
    * Gets the Pre-1998 Contribution Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pre-1998 Contribution Amount or the specified default value.
    */
   public final String getPre98Contrib( int index, String defaultValue )
   {
      return _Pre98Contrib[index] == null ? defaultValue : _Pre98Contrib[index];
   }
    
   /**
    * Gets the array of Pre-1998 Contribution Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Pre-1998 Contribution Amount values.
    */
   public final String[] getPre98ContribArray()
   {
      return _Pre98Contrib;
   }
    
   /**
    * Gets the Pre-1998 Redemption of Contribution Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Pre-1998 Redemption of Contribution Amount or null.
    */
   public final String getPre98RedContrib( int index )
   {
      return _Pre98RedContrib[index];
   }
    
   /**
    * Gets the Pre-1998 Redemption of Contribution Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pre-1998 Redemption of Contribution Amount or the specified default value.
    */
   public final String getPre98RedContrib( int index, String defaultValue )
   {
      return _Pre98RedContrib[index] == null ? defaultValue : _Pre98RedContrib[index];
   }
    
   /**
    * Gets the array of Pre-1998 Redemption of Contribution Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Pre-1998 Redemption of Contribution Amount values.
    */
   public final String[] getPre98RedContribArray()
   {
      return _Pre98RedContrib;
   }
    
   /**
    * Gets the RESP Beneficiary Entity Id field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RESP Beneficiary Entity Id or null.
    */
   public final String getRESPBenefID( int index )
   {
      return _RESPBenefID[index];
   }
    
   /**
    * Gets the RESP Beneficiary Entity Id field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RESP Beneficiary Entity Id or the specified default value.
    */
   public final String getRESPBenefID( int index, String defaultValue )
   {
      return _RESPBenefID[index] == null ? defaultValue : _RESPBenefID[index];
   }
    
   /**
    * Gets the array of RESP Beneficiary Entity Id fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RESP Beneficiary Entity Id values.
    */
   public final String[] getRESPBenefIDArray()
   {
      return _RESPBenefID;
   }
    
   /**
    * Gets the Entity Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Entity Type or null.
    */
   public final String getEntityType( int index )
   {
      return _EntityType[index];
   }
    
   /**
    * Gets the Entity Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity Type or the specified default value.
    */
   public final String getEntityType( int index, String defaultValue )
   {
      return _EntityType[index] == null ? defaultValue : _EntityType[index];
   }
    
   /**
    * Gets the array of Entity Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Entity Type values.
    */
   public final String[] getEntityTypeArray()
   {
      return _EntityType;
   }
    
   /**
    * Gets the Entity Type Sequnce field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Entity Type Sequnce or null.
    */
   public final Integer getEntityTypeSeq( int index )
   {
      return _EntityTypeSeq[index];
   }
    
   /**
    * Gets the Entity Type Sequnce field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity Type Sequnce or the specified default value.
    */
   public final int getEntityTypeSeq( int index, int defaultValue )
   {
      return _EntityTypeSeq[index] == null ? defaultValue : _EntityTypeSeq[index].intValue();
   }
    
   /**
    * Gets the array of Entity Type Sequnce fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Entity Type Sequnce values.
    */
   public final Integer[] getEntityTypeSeqArray()
   {
      return _EntityTypeSeq;
   }
    
   /**
    * Gets the RESP Beneficiary Entity Id to field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RESP Beneficiary Entity Id to or null.
    */
   public final String getRESPBenefIDTo( int index )
   {
      return _RESPBenefIDTo[index];
   }
    
   /**
    * Gets the RESP Beneficiary Entity Id to field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RESP Beneficiary Entity Id to or the specified default value.
    */
   public final String getRESPBenefIDTo( int index, String defaultValue )
   {
      return _RESPBenefIDTo[index] == null ? defaultValue : _RESPBenefIDTo[index];
   }
    
   /**
    * Gets the array of RESP Beneficiary Entity Id to fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RESP Beneficiary Entity Id to values.
    */
   public final String[] getRESPBenefIDToArray()
   {
      return _RESPBenefIDTo;
   }
    
   /**
    * Gets the Entity Type To field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Entity Type To or null.
    */
   public final String getEntityTypeTo( int index )
   {
      return _EntityTypeTo[index];
   }
    
   /**
    * Gets the Entity Type To field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity Type To or the specified default value.
    */
   public final String getEntityTypeTo( int index, String defaultValue )
   {
      return _EntityTypeTo[index] == null ? defaultValue : _EntityTypeTo[index];
   }
    
   /**
    * Gets the array of Entity Type To fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Entity Type To values.
    */
   public final String[] getEntityTypeToArray()
   {
      return _EntityTypeTo;
   }
    
   /**
    * Gets the Entity Type Sequnce To field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Entity Type Sequnce To or null.
    */
   public final Integer getEntityTypeSeqTo( int index )
   {
      return _EntityTypeSeqTo[index];
   }
    
   /**
    * Gets the Entity Type Sequnce To field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity Type Sequnce To or the specified default value.
    */
   public final int getEntityTypeSeqTo( int index, int defaultValue )
   {
      return _EntityTypeSeqTo[index] == null ? defaultValue : _EntityTypeSeqTo[index].intValue();
   }
    
   /**
    * Gets the array of Entity Type Sequnce To fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Entity Type Sequnce To values.
    */
   public final Integer[] getEntityTypeSeqToArray()
   {
      return _EntityTypeSeqTo;
   }
    
   /**
    * Gets the RESP Allocation Percent field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RESP Allocation Percent or null.
    */
   public final String getRESPAllocPrcnt( int index )
   {
      return _RESPAllocPrcnt[index];
   }
    
   /**
    * Gets the RESP Allocation Percent field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RESP Allocation Percent or the specified default value.
    */
   public final String getRESPAllocPrcnt( int index, String defaultValue )
   {
      return _RESPAllocPrcnt[index] == null ? defaultValue : _RESPAllocPrcnt[index];
   }
    
   /**
    * Gets the array of RESP Allocation Percent fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RESP Allocation Percent values.
    */
   public final String[] getRESPAllocPrcntArray()
   {
      return _RESPAllocPrcnt;
   }
    
   /**
    * Gets the Beneficiary Tainted field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Beneficiary Tainted or null.
    */
   public final Boolean getTainted( int index )
   {
      return _Tainted[index];
   }
    
   /**
    * Gets the Beneficiary Tainted field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Beneficiary Tainted or the specified default value.
    */
   public final boolean getTainted( int index, boolean defaultValue )
   {
      return _Tainted[index] == null ? defaultValue : _Tainted[index].booleanValue();
   }
    
   /**
    * Gets the array of Beneficiary Tainted fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Beneficiary Tainted values.
    */
   public final Boolean[] getTaintedArray()
   {
      return _Tainted;
   }
    
   /**
    * Gets the End Date of Tainting field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the End Date of Tainting or null.
    */
   public final Date getTaintEndDate( int index )
   {
      return _TaintEndDate[index];
   }
    
   /**
    * Gets the End Date of Tainting field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the End Date of Tainting or the specified default value.
    */
   public final Date getTaintEndDate( int index, Date defaultValue )
   {
      return _TaintEndDate[index] == null ? defaultValue : _TaintEndDate[index];
   }
    
   /**
    * Gets the array of End Date of Tainting fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of End Date of Tainting values.
    */
   public final Date[] getTaintEndDateArray()
   {
      return _TaintEndDate;
   }
    
   /**
    * Gets the Request Grant field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Request Grant or null.
    */
   public final Boolean getGrantRequest( int index )
   {
      return _GrantRequest[index];
   }
    
   /**
    * Gets the Request Grant field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Request Grant or the specified default value.
    */
   public final boolean getGrantRequest( int index, boolean defaultValue )
   {
      return _GrantRequest[index] == null ? defaultValue : _GrantRequest[index].booleanValue();
   }
    
   /**
    * Gets the array of Request Grant fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Request Grant values.
    */
   public final Boolean[] getGrantRequestArray()
   {
      return _GrantRequest;
   }
    
   /**
    * Gets the Beneficiary Date of Birth field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Beneficiary Date of Birth or null.
    */
   public final Date getBenefDofB( int index )
   {
      return _BenefDofB[index];
   }
    
   /**
    * Gets the Beneficiary Date of Birth field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Beneficiary Date of Birth or the specified default value.
    */
   public final Date getBenefDofB( int index, Date defaultValue )
   {
      return _BenefDofB[index] == null ? defaultValue : _BenefDofB[index];
   }
    
   /**
    * Gets the array of Beneficiary Date of Birth fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Beneficiary Date of Birth values.
    */
   public final Date[] getBenefDofBArray()
   {
      return _BenefDofB;
   }
    
   /**
    * Gets the Tax Jurisdiction field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax Jurisdiction or null.
    */
   public final String getTaxJuris( int index )
   {
      return _TaxJuris[index];
   }
    
   /**
    * Gets the Tax Jurisdiction field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Jurisdiction or the specified default value.
    */
   public final String getTaxJuris( int index, String defaultValue )
   {
      return _TaxJuris[index] == null ? defaultValue : _TaxJuris[index];
   }
    
   /**
    * Gets the array of Tax Jurisdiction fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax Jurisdiction values.
    */
   public final String[] getTaxJurisArray()
   {
      return _TaxJuris;
   }
    
   /**
    * Gets the Relationship field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Relationship or null.
    */
   public final String getRelation( int index )
   {
      return _Relation[index];
   }
    
   /**
    * Gets the Relationship field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Relationship or the specified default value.
    */
   public final String getRelation( int index, String defaultValue )
   {
      return _Relation[index] == null ? defaultValue : _Relation[index];
   }
    
   /**
    * Gets the array of Relationship fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Relationship values.
    */
   public final String[] getRelationArray()
   {
      return _Relation;
   }
    
   /**
    * Gets the Beneficiary Effective Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Beneficiary Effective Date or null.
    */
   public final Date getBenefEffectiveDate( int index )
   {
      return _BenefEffectiveDate[index];
   }
    
   /**
    * Gets the Beneficiary Effective Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Beneficiary Effective Date or the specified default value.
    */
   public final Date getBenefEffectiveDate( int index, Date defaultValue )
   {
      return _BenefEffectiveDate[index] == null ? defaultValue : _BenefEffectiveDate[index];
   }
    
   /**
    * Gets the array of Beneficiary Effective Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Beneficiary Effective Date values.
    */
   public final Date[] getBenefEffectiveDateArray()
   {
      return _BenefEffectiveDate;
   }
    
   /**
    * Gets the Transfer Percent field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transfer Percent or null.
    */
   public final String getTransferPercent( int index )
   {
      return _TransferPercent[index];
   }
    
   /**
    * Gets the Transfer Percent field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transfer Percent or the specified default value.
    */
   public final String getTransferPercent( int index, String defaultValue )
   {
      return _TransferPercent[index] == null ? defaultValue : _TransferPercent[index];
   }
    
   /**
    * Gets the array of Transfer Percent fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transfer Percent values.
    */
   public final String[] getTransferPercentArray()
   {
      return _TransferPercent;
   }
    
   /**
    * Gets the Unassisted Contribution field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Unassisted Contribution or null.
    */
   public final String getQESIUCAmount( int index )
   {
      return _QESIUCAmount[index];
   }
    
   /**
    * Gets the Unassisted Contribution field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Unassisted Contribution or the specified default value.
    */
   public final String getQESIUCAmount( int index, String defaultValue )
   {
      return _QESIUCAmount[index] == null ? defaultValue : _QESIUCAmount[index];
   }
    
   /**
    * Gets the array of Unassisted Contribution fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Unassisted Contribution values.
    */
   public final String[] getQESIUCAmountArray()
   {
      return _QESIUCAmount;
   }
    
   /**
    * Gets the Assisted Contribution field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Assisted Contribution or null.
    */
   public final String getQESIACAmount( int index )
   {
      return _QESIACAmount[index];
   }
    
   /**
    * Gets the Assisted Contribution field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Assisted Contribution or the specified default value.
    */
   public final String getQESIACAmount( int index, String defaultValue )
   {
      return _QESIACAmount[index] == null ? defaultValue : _QESIACAmount[index];
   }
    
   /**
    * Gets the array of Assisted Contribution fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Assisted Contribution values.
    */
   public final String[] getQESIACAmountArray()
   {
      return _QESIACAmount;
   }
    
   /**
    * Gets the YTD Contribution field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the YTD Contribution or null.
    */
   public final String getQESIYTDContribution( int index )
   {
      return _QESIYTDContribution[index];
   }
    
   /**
    * Gets the YTD Contribution field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the YTD Contribution or the specified default value.
    */
   public final String getQESIYTDContribution( int index, String defaultValue )
   {
      return _QESIYTDContribution[index] == null ? defaultValue : _QESIYTDContribution[index];
   }
    
   /**
    * Gets the array of YTD Contribution fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of YTD Contribution values.
    */
   public final String[] getQESIYTDContributionArray()
   {
      return _QESIYTDContribution;
   }
    
   /**
    * Gets the Basic Grant field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Basic Grant or null.
    */
   public final String getQESIBasicGrant( int index )
   {
      return _QESIBasicGrant[index];
   }
    
   /**
    * Gets the Basic Grant field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Basic Grant or the specified default value.
    */
   public final String getQESIBasicGrant( int index, String defaultValue )
   {
      return _QESIBasicGrant[index] == null ? defaultValue : _QESIBasicGrant[index];
   }
    
   /**
    * Gets the array of Basic Grant fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Basic Grant values.
    */
   public final String[] getQESIBasicGrantArray()
   {
      return _QESIBasicGrant;
   }
    
   /**
    * Gets the Additional Grant field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Additional Grant or null.
    */
   public final String getQESIIncreaseAmt( int index )
   {
      return _QESIIncreaseAmt[index];
   }
    
   /**
    * Gets the Additional Grant field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Additional Grant or the specified default value.
    */
   public final String getQESIIncreaseAmt( int index, String defaultValue )
   {
      return _QESIIncreaseAmt[index] == null ? defaultValue : _QESIIncreaseAmt[index];
   }
    
   /**
    * Gets the array of Additional Grant fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Additional Grant values.
    */
   public final String[] getQESIIncreaseAmtArray()
   {
      return _QESIIncreaseAmt;
   }
    
   /**
    * Gets the Pre98 Contribution field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Pre98 Contribution or null.
    */
   public final String getPre98QESIContrib( int index )
   {
      return _Pre98QESIContrib[index];
   }
    
   /**
    * Gets the Pre98 Contribution field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pre98 Contribution or the specified default value.
    */
   public final String getPre98QESIContrib( int index, String defaultValue )
   {
      return _Pre98QESIContrib[index] == null ? defaultValue : _Pre98QESIContrib[index];
   }
    
   /**
    * Gets the array of Pre98 Contribution fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Pre98 Contribution values.
    */
   public final String[] getPre98QESIContribArray()
   {
      return _Pre98QESIContrib;
   }
    
   /**
    * Gets the Pre Contribution field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Pre Contribution or null.
    */
   public final String getPre2007QESIContrib( int index )
   {
      return _Pre2007QESIContrib[index];
   }
    
   /**
    * Gets the Pre Contribution field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pre Contribution or the specified default value.
    */
   public final String getPre2007QESIContrib( int index, String defaultValue )
   {
      return _Pre2007QESIContrib[index] == null ? defaultValue : _Pre2007QESIContrib[index];
   }
    
   /**
    * Gets the array of Pre Contribution fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Pre Contribution values.
    */
   public final String[] getPre2007QESIContribArray()
   {
      return _Pre2007QESIContrib;
   }
    
   /**
    * Gets the RESP External Transfer Detail UUID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RESP External Transfer Detail UUID or null.
    */
   public final String getRESPExtTrDetlUUID( int index )
   {
      return _RESPExtTrDetlUUID[index];
   }
    
   /**
    * Gets the RESP External Transfer Detail UUID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RESP External Transfer Detail UUID or the specified default value.
    */
   public final String getRESPExtTrDetlUUID( int index, String defaultValue )
   {
      return _RESPExtTrDetlUUID[index] == null ? defaultValue : _RESPExtTrDetlUUID[index];
   }
    
   /**
    * Gets the array of RESP External Transfer Detail UUID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RESP External Transfer Detail UUID values.
    */
   public final String[] getRESPExtTrDetlUUIDArray()
   {
      return _RESPExtTrDetlUUID;
   }
    
   /**
    * Gets the RESP External Transfer Detail Version field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RESP External Transfer Detail Version or null.
    */
   public final Integer getRESPExtTrDetlVer( int index )
   {
      return _RESPExtTrDetlVer[index];
   }
    
   /**
    * Gets the RESP External Transfer Detail Version field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RESP External Transfer Detail Version or the specified default value.
    */
   public final int getRESPExtTrDetlVer( int index, int defaultValue )
   {
      return _RESPExtTrDetlVer[index] == null ? defaultValue : _RESPExtTrDetlVer[index].intValue();
   }
    
   /**
    * Gets the array of RESP External Transfer Detail Version fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RESP External Transfer Detail Version values.
    */
   public final Integer[] getRESPExtTrDetlVerArray()
   {
      return _RESPExtTrDetlVer;
   }
    
   /**
    * Gets the RESP Contribution Detail UUID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RESP Contribution Detail UUID or null.
    */
   public final String getRESPContrDetlUUID( int index )
   {
      return _RESPContrDetlUUID[index];
   }
    
   /**
    * Gets the RESP Contribution Detail UUID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RESP Contribution Detail UUID or the specified default value.
    */
   public final String getRESPContrDetlUUID( int index, String defaultValue )
   {
      return _RESPContrDetlUUID[index] == null ? defaultValue : _RESPContrDetlUUID[index];
   }
    
   /**
    * Gets the array of RESP Contribution Detail UUID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RESP Contribution Detail UUID values.
    */
   public final String[] getRESPContrDetlUUIDArray()
   {
      return _RESPContrDetlUUID;
   }
    
   /**
    * Gets the RESP Contribution Detail Version field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RESP Contribution Detail Version or null.
    */
   public final Integer getRESPContrDetlVer( int index )
   {
      return _RESPContrDetlVer[index];
   }
    
   /**
    * Gets the RESP Contribution Detail Version field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RESP Contribution Detail Version or the specified default value.
    */
   public final int getRESPContrDetlVer( int index, int defaultValue )
   {
      return _RESPContrDetlVer[index] == null ? defaultValue : _RESPContrDetlVer[index].intValue();
   }
    
   /**
    * Gets the array of RESP Contribution Detail Version fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RESP Contribution Detail Version values.
    */
   public final Integer[] getRESPContrDetlVerArray()
   {
      return _RESPContrDetlVer;
   }
    
   /**
    * Gets the Eligible Transfer field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Eligible Transfer or null.
    */
   public final Boolean getEligTransfer( int index )
   {
      return _EligTransfer[index];
   }
    
   /**
    * Gets the Eligible Transfer field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Eligible Transfer or the specified default value.
    */
   public final boolean getEligTransfer( int index, boolean defaultValue )
   {
      return _EligTransfer[index] == null ? defaultValue : _EligTransfer[index].booleanValue();
   }
    
   /**
    * Gets the array of Eligible Transfer fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Eligible Transfer values.
    */
   public final Boolean[] getEligTransferArray()
   {
      return _EligTransfer;
   }
    
   /**
    * Gets the Total Transfer Indicator field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Total Transfer Indicator or null.
    */
   public final String getTotTransfINDC( int index )
   {
      return _TotTransfINDC[index];
   }
    
   /**
    * Gets the Total Transfer Indicator field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Total Transfer Indicator or the specified default value.
    */
   public final String getTotTransfINDC( int index, String defaultValue )
   {
      return _TotTransfINDC[index] == null ? defaultValue : _TotTransfINDC[index];
   }
    
   /**
    * Gets the array of Total Transfer Indicator fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Total Transfer Indicator values.
    */
   public final String[] getTotTransfINDCArray()
   {
      return _TotTransfINDC;
   }
    
   /**
    * Gets the Historical Non Trustee Year field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Historical Non Trustee Year or null.
    */
   public final Integer getHistNonTrustYear( int index )
   {
      return _HistNonTrustYear[index];
   }
    
   /**
    * Gets the Historical Non Trustee Year field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Historical Non Trustee Year or the specified default value.
    */
   public final int getHistNonTrustYear( int index, int defaultValue )
   {
      return _HistNonTrustYear[index] == null ? defaultValue : _HistNonTrustYear[index].intValue();
   }
    
   /**
    * Gets the array of Historical Non Trustee Year fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Historical Non Trustee Year values.
    */
   public final Integer[] getHistNonTrustYearArray()
   {
      return _HistNonTrustYear;
   }
    
   /**
    * Gets the CESG Paid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the CESG Paid or null.
    */
   public final String getCESGPaid( int index )
   {
      return _CESGPaid[index];
   }
    
   /**
    * Gets the CESG Paid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the CESG Paid or the specified default value.
    */
   public final String getCESGPaid( int index, String defaultValue )
   {
      return _CESGPaid[index] == null ? defaultValue : _CESGPaid[index];
   }
    
   /**
    * Gets the array of CESG Paid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of CESG Paid values.
    */
   public final String[] getCESGPaidArray()
   {
      return _CESGPaid;
   }
    
   /**
    * Gets the QESI Paid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the QESI Paid or null.
    */
   public final String getQESIPaid( int index )
   {
      return _QESIPaid[index];
   }
    
   /**
    * Gets the QESI Paid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the QESI Paid or the specified default value.
    */
   public final String getQESIPaid( int index, String defaultValue )
   {
      return _QESIPaid[index] == null ? defaultValue : _QESIPaid[index];
   }
    
   /**
    * Gets the array of QESI Paid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of QESI Paid values.
    */
   public final String[] getQESIPaidArray()
   {
      return _QESIPaid;
   }
    
   /**
    * Gets the IsResidualCESG field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the IsResidualCESG or null.
    */
   public final Boolean getIsResidualCESG( int index )
   {
      return _IsResidualCESG[index];
   }
    
   /**
    * Gets the IsResidualCESG field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the IsResidualCESG or the specified default value.
    */
   public final boolean getIsResidualCESG( int index, boolean defaultValue )
   {
      return _IsResidualCESG[index] == null ? defaultValue : _IsResidualCESG[index].booleanValue();
   }
    
   /**
    * Gets the array of IsResidualCESG fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of IsResidualCESG values.
    */
   public final Boolean[] getIsResidualCESGArray()
   {
      return _IsResidualCESG;
   }
    
   /**
    * Gets the SAGES Grant field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SAGES Grant or null.
    */
   public final String getSAGESGrant( int index )
   {
      return _SAGESGrant[index];
   }
    
   /**
    * Gets the SAGES Grant field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SAGES Grant or the specified default value.
    */
   public final String getSAGESGrant( int index, String defaultValue )
   {
      return _SAGESGrant[index] == null ? defaultValue : _SAGESGrant[index];
   }
    
   /**
    * Gets the array of SAGES Grant fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SAGES Grant values.
    */
   public final String[] getSAGESGrantArray()
   {
      return _SAGESGrant;
   }
    
   /**
    * Gets the SAGES UC Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SAGES UC Amount or null.
    */
   public final String getSAGESUCAmount( int index )
   {
      return _SAGESUCAmount[index];
   }
    
   /**
    * Gets the SAGES UC Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SAGES UC Amount or the specified default value.
    */
   public final String getSAGESUCAmount( int index, String defaultValue )
   {
      return _SAGESUCAmount[index] == null ? defaultValue : _SAGESUCAmount[index];
   }
    
   /**
    * Gets the array of SAGES UC Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SAGES UC Amount values.
    */
   public final String[] getSAGESUCAmountArray()
   {
      return _SAGESUCAmount;
   }
    
   /**
    * Gets the SAGES AC Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SAGES AC Amount or null.
    */
   public final String getSAGESACAmount( int index )
   {
      return _SAGESACAmount[index];
   }
    
   /**
    * Gets the SAGES AC Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SAGES AC Amount or the specified default value.
    */
   public final String getSAGESACAmount( int index, String defaultValue )
   {
      return _SAGESACAmount[index] == null ? defaultValue : _SAGESACAmount[index];
   }
    
   /**
    * Gets the array of SAGES AC Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SAGES AC Amount values.
    */
   public final String[] getSAGESACAmountArray()
   {
      return _SAGESACAmount;
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
      _PlanNum1 = responseBuffer.decodeString(responseBuffer.getNextField());
      _ContractId1 = responseBuffer.decodeString(responseBuffer.getNextField());
      _PlanNum2 = responseBuffer.decodeString(responseBuffer.getNextField());
      _ContractID2 = responseBuffer.decodeString(responseBuffer.getNextField());
      _InceptionDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _TerminationDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _NEQ1 = responseBuffer.decodeString(responseBuffer.getNextField());
      _NEQ2 = responseBuffer.decodeString(responseBuffer.getNextField());
      _AcctLvlOverride = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _RESPLetter = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _TranStatus = responseBuffer.decodeBoolean(responseBuffer.getNextField());
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _RecordLevel = resizeArray( _RecordLevel, _RepeatCount );
      _YTDContribution = resizeArray( _YTDContribution, _RepeatCount );
      _TDContribution = resizeArray( _TDContribution, _RepeatCount );
      _GrantAmount = resizeArray( _GrantAmount, _RepeatCount );
      _AdditionalGrant = resizeArray( _AdditionalGrant, _RepeatCount );
      _CLBAmount = resizeArray( _CLBAmount, _RepeatCount );
      _PGrantAmount = resizeArray( _PGrantAmount, _RepeatCount );
      _TDRedContrib = resizeArray( _TDRedContrib, _RepeatCount );
      _TDRedEarnings = resizeArray( _TDRedEarnings, _RepeatCount );
      _RedCESG = resizeArray( _RedCESG, _RepeatCount );
      _RedCLB = resizeArray( _RedCLB, _RepeatCount );
      _RedPGrant = resizeArray( _RedPGrant, _RepeatCount );
      _UCAmount = resizeArray( _UCAmount, _RepeatCount );
      _ACAmount = resizeArray( _ACAmount, _RepeatCount );
      _Pre98Contrib = resizeArray( _Pre98Contrib, _RepeatCount );
      _Pre98RedContrib = resizeArray( _Pre98RedContrib, _RepeatCount );
      _RESPBenefID = resizeArray( _RESPBenefID, _RepeatCount );
      _EntityType = resizeArray( _EntityType, _RepeatCount );
      _EntityTypeSeq = resizeArray( _EntityTypeSeq, _RepeatCount );
      _RESPBenefIDTo = resizeArray( _RESPBenefIDTo, _RepeatCount );
      _EntityTypeTo = resizeArray( _EntityTypeTo, _RepeatCount );
      _EntityTypeSeqTo = resizeArray( _EntityTypeSeqTo, _RepeatCount );
      _RESPAllocPrcnt = resizeArray( _RESPAllocPrcnt, _RepeatCount );
      _Tainted = resizeArray( _Tainted, _RepeatCount );
      _TaintEndDate = resizeArray( _TaintEndDate, _RepeatCount );
      _GrantRequest = resizeArray( _GrantRequest, _RepeatCount );
      _BenefDofB = resizeArray( _BenefDofB, _RepeatCount );
      _TaxJuris = resizeArray( _TaxJuris, _RepeatCount );
      _Relation = resizeArray( _Relation, _RepeatCount );
      _BenefEffectiveDate = resizeArray( _BenefEffectiveDate, _RepeatCount );
      _TransferPercent = resizeArray( _TransferPercent, _RepeatCount );
      _QESIUCAmount = resizeArray( _QESIUCAmount, _RepeatCount );
      _QESIACAmount = resizeArray( _QESIACAmount, _RepeatCount );
      _QESIYTDContribution = resizeArray( _QESIYTDContribution, _RepeatCount );
      _QESIBasicGrant = resizeArray( _QESIBasicGrant, _RepeatCount );
      _QESIIncreaseAmt = resizeArray( _QESIIncreaseAmt, _RepeatCount );
      _Pre98QESIContrib = resizeArray( _Pre98QESIContrib, _RepeatCount );
      _Pre2007QESIContrib = resizeArray( _Pre2007QESIContrib, _RepeatCount );
      _RESPExtTrDetlUUID = resizeArray( _RESPExtTrDetlUUID, _RepeatCount );
      _RESPExtTrDetlVer = resizeArray( _RESPExtTrDetlVer, _RepeatCount );
      _RESPContrDetlUUID = resizeArray( _RESPContrDetlUUID, _RepeatCount );
      _RESPContrDetlVer = resizeArray( _RESPContrDetlVer, _RepeatCount );
      _EligTransfer = resizeArray( _EligTransfer, _RepeatCount );
      _TotTransfINDC = resizeArray( _TotTransfINDC, _RepeatCount );
      _HistNonTrustYear = resizeArray( _HistNonTrustYear, _RepeatCount );
      _CESGPaid = resizeArray( _CESGPaid, _RepeatCount );
      _QESIPaid = resizeArray( _QESIPaid, _RepeatCount );
      _IsResidualCESG = resizeArray( _IsResidualCESG, _RepeatCount );
      _SAGESGrant = resizeArray( _SAGESGrant, _RepeatCount );
      _SAGESUCAmount = resizeArray( _SAGESUCAmount, _RepeatCount );
      _SAGESACAmount = resizeArray( _SAGESACAmount, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _RecordLevel[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _YTDContribution[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TDContribution[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GrantAmount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AdditionalGrant[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CLBAmount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PGrantAmount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TDRedContrib[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TDRedEarnings[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RedCESG[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RedCLB[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RedPGrant[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UCAmount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ACAmount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Pre98Contrib[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Pre98RedContrib[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RESPBenefID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EntityType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EntityTypeSeq[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _RESPBenefIDTo[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EntityTypeTo[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EntityTypeSeqTo[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _RESPAllocPrcnt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Tainted[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TaintEndDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _GrantRequest[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _BenefDofB[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _TaxJuris[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Relation[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BenefEffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _TransferPercent[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _QESIUCAmount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _QESIACAmount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _QESIYTDContribution[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _QESIBasicGrant[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _QESIIncreaseAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Pre98QESIContrib[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Pre2007QESIContrib[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RESPExtTrDetlUUID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RESPExtTrDetlVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _RESPContrDetlUUID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RESPContrDetlVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _EligTransfer[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TotTransfINDC[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _HistNonTrustYear[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _CESGPaid[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _QESIPaid[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IsResidualCESG[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _SAGESGrant[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SAGESUCAmount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SAGESACAmount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
