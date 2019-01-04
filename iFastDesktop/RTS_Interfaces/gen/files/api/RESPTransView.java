
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * RESP Transaction Hist/Pend Inquriy view.
 * For additional view information see <A HREF="../../../../viewspecs/RESPTrans.doc">RESPTrans.doc</A>.
 * 
 * @author RTS Generated
 */
public class RESPTransView extends IFastView implements Serializable
{

   /**
    * Account number member variable.
    */
   private String _rxAccountNum = null;
   
   private int _RepeatCount = 0;
   
   /**
    * Beneficiary Name member array.
    */
   private String[] _BeneName = null;
   
   /**
    * RESPDepositType member array.
    */
   private Integer[] _RESPDepositType = null;
   
   /**
    * RESPDepositTypeDesc member array.
    */
   private String[] _RESPDepositTypeDesc = null;
   
   /**
    * RedemptionCode member array.
    */
   private String[] _RedCode = null;
   
   /**
    * RedCodeDesc member array.
    */
   private String[] _RedCodeDesc = null;
   
   /**
    * TransId member array.
    */
   private String[] _TransId = null;
   
   /**
    * EffectiveDate member array.
    */
   private Date[] _EffectiveDate = null;
   
   /**
    * GrossAmount member array.
    */
   private String[] _GrossAmt = null;
   
   /**
    * HRDCTransId member array.
    */
   private String[] _HRDCTransId = null;
   
   /**
    * SettleDate member array.
    */
   private Date[] _SettleDate = null;
   
   /**
    * Assisted Capital Amt member array.
    */
   private String[] _ACAmt = null;
   
   /**
    * TerminateDate member array.
    */
   private Date[] _TerminateDate = null;
   
   /**
    * GrantAmount member array.
    */
   private String[] _GrantAmount = null;
   
   /**
    * Life (TD) Contribution member array.
    */
   private String[] _LifeContr = null;
   
   /**
    * GrantTransCode member array.
    */
   private String[] _GrantTransCode = null;
   
   /**
    * GrantTransLabel member array.
    */
   private String[] _GrantTransLabel = null;
   
   /**
    * GrantTransId member array.
    */
   private String[] _GrantTransId = null;
   
   /**
    * Red Life (TD) Contribution member array.
    */
   private String[] _RedLifeContr = null;
   
   /**
    * Unassisted Capital Amount member array.
    */
   private String[] _UCAmt = null;
   
   /**
    * Unassisted Capital Reason member array.
    */
   private String[] _UCReason = null;
   
   /**
    * OldContractId member array.
    */
   private String[] _OldContractId = null;
   
   /**
    * OldPlanId member array.
    */
   private String[] _OldPlanId = null;
   
   /**
    * RESPLetter member array.
    */
   private Boolean[] _RESPLetter = null;
   
   /**
    * HRDCReported member array.
    */
   private Boolean[] _HRDCReported = null;
   
   /**
    * RESPTransStat member array.
    */
   private String[] _RESPTransStat = null;
   
   /**
    * GrantRepayable member array.
    */
   private String[] _GrantRepayable = null;
   
   /**
    * Year To Date Contribution member array.
    */
   private String[] _YTDContr = null;
   
   /**
    * Reason Code for Additional CESG member array.
    */
   private String[] _AddlCESGRsnCode = null;
   
   /**
    * Reason Description for Additional CESG member array.
    */
   private String[] _AddlCESGRsnDesc = null;
   
   /**
    * CESG Amount member array.
    */
   private String[] _CESGAmount = null;
   
   /**
    * If it need to report this transaction to HRDC member array.
    */
   private Boolean[] _NeedRepHRDC = null;
   
   /**
    * CESGInDtl Error Description member array.
    */
   private String[] _CESGInDtlErrorDesc = null;
   
   /**
    * Beneficiary Tainted member array.
    */
   private Boolean[] _Tainted = null;
   
   /**
    * Year the overcontribution withdrawal member array.
    */
   private Integer[] _OCRdmYear = null;
   
   /**
    * Reason for this grant repayment to HRDC member array.
    */
   private String[] _GRRepayReason = null;
   
   /**
    * UC Reason Description member array.
    */
   private String[] _UCReasonDesc = null;
   
   /**
    * Transaction TransType member array.
    */
   private String[] _TradesTransType = null;
   
   /**
    * Amount Type member array.
    */
   private String[] _AmountType = null;
   
   /**
    * Cancelled flag member array.
    */
   private Boolean[] _Cancelled = null;
   
   /**
    * Reversal flag member array.
    */
   private Boolean[] _Reversal = null;
   
   /**
    * HRDCPending flag member array.
    */
   private Boolean[] _HRDCPending = null;
   
   /**
    * GrossNet member array.
    */
   private String[] _GrossNet = null;
   
   /**
    * The Gross Amount of the trade member array.
    */
   private String[] _TradeGrossAmt = null;
   
   /**
    * Transaction number member array.
    */
   private Integer[] _TransNum = null;
   
   /**
    * Tax Year member array.
    */
   private Integer[] _TaxYear = null;
   
   /**
    * Purchase Additional member array.
    */
   private String[] _PurAdd = null;
   
   /**
    * Purchase CLB member array.
    */
   private String[] _PurCLB = null;
   
   /**
    * Purchase Provincial Grant member array.
    */
   private String[] _PurPGrant = null;
   
   /**
    * Purchase QESI member array.
    */
   private String[] _PurQESI = null;
   
   /**
    * Redemption Income member array.
    */
   private String[] _RedIncome = null;
   
   /**
    * Redemption CESG member array.
    */
   private String[] _RedCESG = null;
   
   /**
    * Redemption CLB member array.
    */
   private String[] _RedCLB = null;
   
   /**
    * Redemption Provincial Grant member array.
    */
   private String[] _RedPGrant = null;
   
   /**
    * Redemption QESI member array.
    */
   private String[] _RedQESI = null;
   
   /**
    * Additional QESI Amount member array.
    */
   private String[] _AddtlQESI = null;
   
   /**
    * Account To member array.
    */
   private String[] _AccountTo = null;
   
   /**
    * AIP Accountholder Name member array.
    */
   private String[] _AIPAcctName = null;
   
   /**
    * Historical NOn Trustee Year member array.
    */
   private Integer[] _HistNonTrustYear = null;
   
   /**
    * IsResidualCESG member array.
    */
   private Boolean[] _IsResidualCESG = null;
   
   /**
    * SAGES Purchase Amount member array.
    */
   private String[] _SAGESPurAmt = null;
   
   /**
    * SAGES Redemption Amount member array.
    */
   private String[] _SAGESRedAmt = null;
   
   /**
    * SAGES unique ID member array.
    */
   private String[] _SAGESTransID = null;
   
   /**
    * SAGES Trans Orig Code member array.
    */
   private String[] _SAGESTransOrigCode = null;
   
   /**
    * SAGES Unassisted Reason member array.
    */
   private String[] _SAGESUCDesc = null;
   
   /**
    * SAGES Reject Reason member array.
    */
   private String[] _SAGESRejDesc = null;
   
   /**
    * SAGES reported to govt member array.
    */
   private String[] _SAGESReported = null;
   
   /**
    * SAGES Unassisted Amount member array.
    */
   private String[] _SAGESUCAmt = null;
   
   /**
    * SAGES Assisted Amount member array.
    */
   private String[] _SAGESACAmt = null;
   

   /**
    * Constructs the RESPTransView object.
    * 
    */
   public RESPTransView()
   {
      super ( new RESPTransRequest() );
   }

   /**
    * Constructs the RESPTransView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public RESPTransView( String hostEncoding )
   {
      super ( new RESPTransRequest( hostEncoding ) );
   }

   /**
    * Gets the RESPTransRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The RESPTransRequest object.
    */
   public final RESPTransRequest getRequest()
   {
      return (RESPTransRequest)getIFastRequest();
   }
        
   /**
    * Gets the Account number field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Account number or null.
    */
   public final String getrxAccountNum()
   {
      return _rxAccountNum;
   }
	
   /**
    * Gets the Account number field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account number or the specified default value.
    */
   public final String getrxAccountNum( String defaultValue )
   {
      return _rxAccountNum == null ? defaultValue : _rxAccountNum;
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
    * Gets the Beneficiary Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Beneficiary Name or null.
    */
   public final String getBeneName( int index )
   {
      return _BeneName[index];
   }
    
   /**
    * Gets the Beneficiary Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Beneficiary Name or the specified default value.
    */
   public final String getBeneName( int index, String defaultValue )
   {
      return _BeneName[index] == null ? defaultValue : _BeneName[index];
   }
    
   /**
    * Gets the array of Beneficiary Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Beneficiary Name values.
    */
   public final String[] getBeneNameArray()
   {
      return _BeneName;
   }
    
   /**
    * Gets the RESPDepositType field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RESPDepositType or null.
    */
   public final Integer getRESPDepositType( int index )
   {
      return _RESPDepositType[index];
   }
    
   /**
    * Gets the RESPDepositType field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RESPDepositType or the specified default value.
    */
   public final int getRESPDepositType( int index, int defaultValue )
   {
      return _RESPDepositType[index] == null ? defaultValue : _RESPDepositType[index].intValue();
   }
    
   /**
    * Gets the array of RESPDepositType fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RESPDepositType values.
    */
   public final Integer[] getRESPDepositTypeArray()
   {
      return _RESPDepositType;
   }
    
   /**
    * Gets the RESPDepositTypeDesc field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RESPDepositTypeDesc or null.
    */
   public final String getRESPDepositTypeDesc( int index )
   {
      return _RESPDepositTypeDesc[index];
   }
    
   /**
    * Gets the RESPDepositTypeDesc field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RESPDepositTypeDesc or the specified default value.
    */
   public final String getRESPDepositTypeDesc( int index, String defaultValue )
   {
      return _RESPDepositTypeDesc[index] == null ? defaultValue : _RESPDepositTypeDesc[index];
   }
    
   /**
    * Gets the array of RESPDepositTypeDesc fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RESPDepositTypeDesc values.
    */
   public final String[] getRESPDepositTypeDescArray()
   {
      return _RESPDepositTypeDesc;
   }
    
   /**
    * Gets the RedemptionCode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RedemptionCode or null.
    */
   public final String getRedCode( int index )
   {
      return _RedCode[index];
   }
    
   /**
    * Gets the RedemptionCode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RedemptionCode or the specified default value.
    */
   public final String getRedCode( int index, String defaultValue )
   {
      return _RedCode[index] == null ? defaultValue : _RedCode[index];
   }
    
   /**
    * Gets the array of RedemptionCode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RedemptionCode values.
    */
   public final String[] getRedCodeArray()
   {
      return _RedCode;
   }
    
   /**
    * Gets the RedCodeDesc field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RedCodeDesc or null.
    */
   public final String getRedCodeDesc( int index )
   {
      return _RedCodeDesc[index];
   }
    
   /**
    * Gets the RedCodeDesc field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RedCodeDesc or the specified default value.
    */
   public final String getRedCodeDesc( int index, String defaultValue )
   {
      return _RedCodeDesc[index] == null ? defaultValue : _RedCodeDesc[index];
   }
    
   /**
    * Gets the array of RedCodeDesc fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RedCodeDesc values.
    */
   public final String[] getRedCodeDescArray()
   {
      return _RedCodeDesc;
   }
    
   /**
    * Gets the TransId field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the TransId or null.
    */
   public final String getTransId( int index )
   {
      return _TransId[index];
   }
    
   /**
    * Gets the TransId field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TransId or the specified default value.
    */
   public final String getTransId( int index, String defaultValue )
   {
      return _TransId[index] == null ? defaultValue : _TransId[index];
   }
    
   /**
    * Gets the array of TransId fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of TransId values.
    */
   public final String[] getTransIdArray()
   {
      return _TransId;
   }
    
   /**
    * Gets the EffectiveDate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the EffectiveDate or null.
    */
   public final Date getEffectiveDate( int index )
   {
      return _EffectiveDate[index];
   }
    
   /**
    * Gets the EffectiveDate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the EffectiveDate or the specified default value.
    */
   public final Date getEffectiveDate( int index, Date defaultValue )
   {
      return _EffectiveDate[index] == null ? defaultValue : _EffectiveDate[index];
   }
    
   /**
    * Gets the array of EffectiveDate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of EffectiveDate values.
    */
   public final Date[] getEffectiveDateArray()
   {
      return _EffectiveDate;
   }
    
   /**
    * Gets the GrossAmount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the GrossAmount or null.
    */
   public final String getGrossAmt( int index )
   {
      return _GrossAmt[index];
   }
    
   /**
    * Gets the GrossAmount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the GrossAmount or the specified default value.
    */
   public final String getGrossAmt( int index, String defaultValue )
   {
      return _GrossAmt[index] == null ? defaultValue : _GrossAmt[index];
   }
    
   /**
    * Gets the array of GrossAmount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of GrossAmount values.
    */
   public final String[] getGrossAmtArray()
   {
      return _GrossAmt;
   }
    
   /**
    * Gets the HRDCTransId field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the HRDCTransId or null.
    */
   public final String getHRDCTransId( int index )
   {
      return _HRDCTransId[index];
   }
    
   /**
    * Gets the HRDCTransId field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the HRDCTransId or the specified default value.
    */
   public final String getHRDCTransId( int index, String defaultValue )
   {
      return _HRDCTransId[index] == null ? defaultValue : _HRDCTransId[index];
   }
    
   /**
    * Gets the array of HRDCTransId fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of HRDCTransId values.
    */
   public final String[] getHRDCTransIdArray()
   {
      return _HRDCTransId;
   }
    
   /**
    * Gets the SettleDate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SettleDate or null.
    */
   public final Date getSettleDate( int index )
   {
      return _SettleDate[index];
   }
    
   /**
    * Gets the SettleDate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SettleDate or the specified default value.
    */
   public final Date getSettleDate( int index, Date defaultValue )
   {
      return _SettleDate[index] == null ? defaultValue : _SettleDate[index];
   }
    
   /**
    * Gets the array of SettleDate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SettleDate values.
    */
   public final Date[] getSettleDateArray()
   {
      return _SettleDate;
   }
    
   /**
    * Gets the Assisted Capital Amt field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Assisted Capital Amt or null.
    */
   public final String getACAmt( int index )
   {
      return _ACAmt[index];
   }
    
   /**
    * Gets the Assisted Capital Amt field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Assisted Capital Amt or the specified default value.
    */
   public final String getACAmt( int index, String defaultValue )
   {
      return _ACAmt[index] == null ? defaultValue : _ACAmt[index];
   }
    
   /**
    * Gets the array of Assisted Capital Amt fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Assisted Capital Amt values.
    */
   public final String[] getACAmtArray()
   {
      return _ACAmt;
   }
    
   /**
    * Gets the TerminateDate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the TerminateDate or null.
    */
   public final Date getTerminateDate( int index )
   {
      return _TerminateDate[index];
   }
    
   /**
    * Gets the TerminateDate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TerminateDate or the specified default value.
    */
   public final Date getTerminateDate( int index, Date defaultValue )
   {
      return _TerminateDate[index] == null ? defaultValue : _TerminateDate[index];
   }
    
   /**
    * Gets the array of TerminateDate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of TerminateDate values.
    */
   public final Date[] getTerminateDateArray()
   {
      return _TerminateDate;
   }
    
   /**
    * Gets the GrantAmount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the GrantAmount or null.
    */
   public final String getGrantAmount( int index )
   {
      return _GrantAmount[index];
   }
    
   /**
    * Gets the GrantAmount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the GrantAmount or the specified default value.
    */
   public final String getGrantAmount( int index, String defaultValue )
   {
      return _GrantAmount[index] == null ? defaultValue : _GrantAmount[index];
   }
    
   /**
    * Gets the array of GrantAmount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of GrantAmount values.
    */
   public final String[] getGrantAmountArray()
   {
      return _GrantAmount;
   }
    
   /**
    * Gets the Life (TD) Contribution field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Life (TD) Contribution or null.
    */
   public final String getLifeContr( int index )
   {
      return _LifeContr[index];
   }
    
   /**
    * Gets the Life (TD) Contribution field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Life (TD) Contribution or the specified default value.
    */
   public final String getLifeContr( int index, String defaultValue )
   {
      return _LifeContr[index] == null ? defaultValue : _LifeContr[index];
   }
    
   /**
    * Gets the array of Life (TD) Contribution fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Life (TD) Contribution values.
    */
   public final String[] getLifeContrArray()
   {
      return _LifeContr;
   }
    
   /**
    * Gets the GrantTransCode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the GrantTransCode or null.
    */
   public final String getGrantTransCode( int index )
   {
      return _GrantTransCode[index];
   }
    
   /**
    * Gets the GrantTransCode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the GrantTransCode or the specified default value.
    */
   public final String getGrantTransCode( int index, String defaultValue )
   {
      return _GrantTransCode[index] == null ? defaultValue : _GrantTransCode[index];
   }
    
   /**
    * Gets the array of GrantTransCode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of GrantTransCode values.
    */
   public final String[] getGrantTransCodeArray()
   {
      return _GrantTransCode;
   }
    
   /**
    * Gets the GrantTransLabel field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the GrantTransLabel or null.
    */
   public final String getGrantTransLabel( int index )
   {
      return _GrantTransLabel[index];
   }
    
   /**
    * Gets the GrantTransLabel field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the GrantTransLabel or the specified default value.
    */
   public final String getGrantTransLabel( int index, String defaultValue )
   {
      return _GrantTransLabel[index] == null ? defaultValue : _GrantTransLabel[index];
   }
    
   /**
    * Gets the array of GrantTransLabel fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of GrantTransLabel values.
    */
   public final String[] getGrantTransLabelArray()
   {
      return _GrantTransLabel;
   }
    
   /**
    * Gets the GrantTransId field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the GrantTransId or null.
    */
   public final String getGrantTransId( int index )
   {
      return _GrantTransId[index];
   }
    
   /**
    * Gets the GrantTransId field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the GrantTransId or the specified default value.
    */
   public final String getGrantTransId( int index, String defaultValue )
   {
      return _GrantTransId[index] == null ? defaultValue : _GrantTransId[index];
   }
    
   /**
    * Gets the array of GrantTransId fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of GrantTransId values.
    */
   public final String[] getGrantTransIdArray()
   {
      return _GrantTransId;
   }
    
   /**
    * Gets the Red Life (TD) Contribution field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Red Life (TD) Contribution or null.
    */
   public final String getRedLifeContr( int index )
   {
      return _RedLifeContr[index];
   }
    
   /**
    * Gets the Red Life (TD) Contribution field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Red Life (TD) Contribution or the specified default value.
    */
   public final String getRedLifeContr( int index, String defaultValue )
   {
      return _RedLifeContr[index] == null ? defaultValue : _RedLifeContr[index];
   }
    
   /**
    * Gets the array of Red Life (TD) Contribution fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Red Life (TD) Contribution values.
    */
   public final String[] getRedLifeContrArray()
   {
      return _RedLifeContr;
   }
    
   /**
    * Gets the Unassisted Capital Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Unassisted Capital Amount or null.
    */
   public final String getUCAmt( int index )
   {
      return _UCAmt[index];
   }
    
   /**
    * Gets the Unassisted Capital Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Unassisted Capital Amount or the specified default value.
    */
   public final String getUCAmt( int index, String defaultValue )
   {
      return _UCAmt[index] == null ? defaultValue : _UCAmt[index];
   }
    
   /**
    * Gets the array of Unassisted Capital Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Unassisted Capital Amount values.
    */
   public final String[] getUCAmtArray()
   {
      return _UCAmt;
   }
    
   /**
    * Gets the Unassisted Capital Reason field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Unassisted Capital Reason or null.
    */
   public final String getUCReason( int index )
   {
      return _UCReason[index];
   }
    
   /**
    * Gets the Unassisted Capital Reason field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Unassisted Capital Reason or the specified default value.
    */
   public final String getUCReason( int index, String defaultValue )
   {
      return _UCReason[index] == null ? defaultValue : _UCReason[index];
   }
    
   /**
    * Gets the array of Unassisted Capital Reason fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Unassisted Capital Reason values.
    */
   public final String[] getUCReasonArray()
   {
      return _UCReason;
   }
    
   /**
    * Gets the OldContractId field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the OldContractId or null.
    */
   public final String getOldContractId( int index )
   {
      return _OldContractId[index];
   }
    
   /**
    * Gets the OldContractId field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the OldContractId or the specified default value.
    */
   public final String getOldContractId( int index, String defaultValue )
   {
      return _OldContractId[index] == null ? defaultValue : _OldContractId[index];
   }
    
   /**
    * Gets the array of OldContractId fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of OldContractId values.
    */
   public final String[] getOldContractIdArray()
   {
      return _OldContractId;
   }
    
   /**
    * Gets the OldPlanId field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the OldPlanId or null.
    */
   public final String getOldPlanId( int index )
   {
      return _OldPlanId[index];
   }
    
   /**
    * Gets the OldPlanId field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the OldPlanId or the specified default value.
    */
   public final String getOldPlanId( int index, String defaultValue )
   {
      return _OldPlanId[index] == null ? defaultValue : _OldPlanId[index];
   }
    
   /**
    * Gets the array of OldPlanId fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of OldPlanId values.
    */
   public final String[] getOldPlanIdArray()
   {
      return _OldPlanId;
   }
    
   /**
    * Gets the RESPLetter field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RESPLetter or null.
    */
   public final Boolean getRESPLetter( int index )
   {
      return _RESPLetter[index];
   }
    
   /**
    * Gets the RESPLetter field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RESPLetter or the specified default value.
    */
   public final boolean getRESPLetter( int index, boolean defaultValue )
   {
      return _RESPLetter[index] == null ? defaultValue : _RESPLetter[index].booleanValue();
   }
    
   /**
    * Gets the array of RESPLetter fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RESPLetter values.
    */
   public final Boolean[] getRESPLetterArray()
   {
      return _RESPLetter;
   }
    
   /**
    * Gets the HRDCReported field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the HRDCReported or null.
    */
   public final Boolean getHRDCReported( int index )
   {
      return _HRDCReported[index];
   }
    
   /**
    * Gets the HRDCReported field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the HRDCReported or the specified default value.
    */
   public final boolean getHRDCReported( int index, boolean defaultValue )
   {
      return _HRDCReported[index] == null ? defaultValue : _HRDCReported[index].booleanValue();
   }
    
   /**
    * Gets the array of HRDCReported fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of HRDCReported values.
    */
   public final Boolean[] getHRDCReportedArray()
   {
      return _HRDCReported;
   }
    
   /**
    * Gets the RESPTransStat field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RESPTransStat or null.
    */
   public final String getRESPTransStat( int index )
   {
      return _RESPTransStat[index];
   }
    
   /**
    * Gets the RESPTransStat field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RESPTransStat or the specified default value.
    */
   public final String getRESPTransStat( int index, String defaultValue )
   {
      return _RESPTransStat[index] == null ? defaultValue : _RESPTransStat[index];
   }
    
   /**
    * Gets the array of RESPTransStat fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RESPTransStat values.
    */
   public final String[] getRESPTransStatArray()
   {
      return _RESPTransStat;
   }
    
   /**
    * Gets the GrantRepayable field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the GrantRepayable or null.
    */
   public final String getGrantRepayable( int index )
   {
      return _GrantRepayable[index];
   }
    
   /**
    * Gets the GrantRepayable field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the GrantRepayable or the specified default value.
    */
   public final String getGrantRepayable( int index, String defaultValue )
   {
      return _GrantRepayable[index] == null ? defaultValue : _GrantRepayable[index];
   }
    
   /**
    * Gets the array of GrantRepayable fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of GrantRepayable values.
    */
   public final String[] getGrantRepayableArray()
   {
      return _GrantRepayable;
   }
    
   /**
    * Gets the Year To Date Contribution field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Year To Date Contribution or null.
    */
   public final String getYTDContr( int index )
   {
      return _YTDContr[index];
   }
    
   /**
    * Gets the Year To Date Contribution field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Year To Date Contribution or the specified default value.
    */
   public final String getYTDContr( int index, String defaultValue )
   {
      return _YTDContr[index] == null ? defaultValue : _YTDContr[index];
   }
    
   /**
    * Gets the array of Year To Date Contribution fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Year To Date Contribution values.
    */
   public final String[] getYTDContrArray()
   {
      return _YTDContr;
   }
    
   /**
    * Gets the Reason Code for Additional CESG field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reason Code for Additional CESG or null.
    */
   public final String getAddlCESGRsnCode( int index )
   {
      return _AddlCESGRsnCode[index];
   }
    
   /**
    * Gets the Reason Code for Additional CESG field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reason Code for Additional CESG or the specified default value.
    */
   public final String getAddlCESGRsnCode( int index, String defaultValue )
   {
      return _AddlCESGRsnCode[index] == null ? defaultValue : _AddlCESGRsnCode[index];
   }
    
   /**
    * Gets the array of Reason Code for Additional CESG fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reason Code for Additional CESG values.
    */
   public final String[] getAddlCESGRsnCodeArray()
   {
      return _AddlCESGRsnCode;
   }
    
   /**
    * Gets the Reason Description for Additional CESG field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reason Description for Additional CESG or null.
    */
   public final String getAddlCESGRsnDesc( int index )
   {
      return _AddlCESGRsnDesc[index];
   }
    
   /**
    * Gets the Reason Description for Additional CESG field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reason Description for Additional CESG or the specified default value.
    */
   public final String getAddlCESGRsnDesc( int index, String defaultValue )
   {
      return _AddlCESGRsnDesc[index] == null ? defaultValue : _AddlCESGRsnDesc[index];
   }
    
   /**
    * Gets the array of Reason Description for Additional CESG fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reason Description for Additional CESG values.
    */
   public final String[] getAddlCESGRsnDescArray()
   {
      return _AddlCESGRsnDesc;
   }
    
   /**
    * Gets the CESG Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the CESG Amount or null.
    */
   public final String getCESGAmount( int index )
   {
      return _CESGAmount[index];
   }
    
   /**
    * Gets the CESG Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the CESG Amount or the specified default value.
    */
   public final String getCESGAmount( int index, String defaultValue )
   {
      return _CESGAmount[index] == null ? defaultValue : _CESGAmount[index];
   }
    
   /**
    * Gets the array of CESG Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of CESG Amount values.
    */
   public final String[] getCESGAmountArray()
   {
      return _CESGAmount;
   }
    
   /**
    * Gets the If it need to report this transaction to HRDC field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the If it need to report this transaction to HRDC or null.
    */
   public final Boolean getNeedRepHRDC( int index )
   {
      return _NeedRepHRDC[index];
   }
    
   /**
    * Gets the If it need to report this transaction to HRDC field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the If it need to report this transaction to HRDC or the specified default value.
    */
   public final boolean getNeedRepHRDC( int index, boolean defaultValue )
   {
      return _NeedRepHRDC[index] == null ? defaultValue : _NeedRepHRDC[index].booleanValue();
   }
    
   /**
    * Gets the array of If it need to report this transaction to HRDC fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of If it need to report this transaction to HRDC values.
    */
   public final Boolean[] getNeedRepHRDCArray()
   {
      return _NeedRepHRDC;
   }
    
   /**
    * Gets the CESGInDtl Error Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the CESGInDtl Error Description or null.
    */
   public final String getCESGInDtlErrorDesc( int index )
   {
      return _CESGInDtlErrorDesc[index];
   }
    
   /**
    * Gets the CESGInDtl Error Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the CESGInDtl Error Description or the specified default value.
    */
   public final String getCESGInDtlErrorDesc( int index, String defaultValue )
   {
      return _CESGInDtlErrorDesc[index] == null ? defaultValue : _CESGInDtlErrorDesc[index];
   }
    
   /**
    * Gets the array of CESGInDtl Error Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of CESGInDtl Error Description values.
    */
   public final String[] getCESGInDtlErrorDescArray()
   {
      return _CESGInDtlErrorDesc;
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
    * Gets the Year the overcontribution withdrawal field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Year the overcontribution withdrawal or null.
    */
   public final Integer getOCRdmYear( int index )
   {
      return _OCRdmYear[index];
   }
    
   /**
    * Gets the Year the overcontribution withdrawal field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Year the overcontribution withdrawal or the specified default value.
    */
   public final int getOCRdmYear( int index, int defaultValue )
   {
      return _OCRdmYear[index] == null ? defaultValue : _OCRdmYear[index].intValue();
   }
    
   /**
    * Gets the array of Year the overcontribution withdrawal fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Year the overcontribution withdrawal values.
    */
   public final Integer[] getOCRdmYearArray()
   {
      return _OCRdmYear;
   }
    
   /**
    * Gets the Reason for this grant repayment to HRDC field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reason for this grant repayment to HRDC or null.
    */
   public final String getGRRepayReason( int index )
   {
      return _GRRepayReason[index];
   }
    
   /**
    * Gets the Reason for this grant repayment to HRDC field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reason for this grant repayment to HRDC or the specified default value.
    */
   public final String getGRRepayReason( int index, String defaultValue )
   {
      return _GRRepayReason[index] == null ? defaultValue : _GRRepayReason[index];
   }
    
   /**
    * Gets the array of Reason for this grant repayment to HRDC fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reason for this grant repayment to HRDC values.
    */
   public final String[] getGRRepayReasonArray()
   {
      return _GRRepayReason;
   }
    
   /**
    * Gets the UC Reason Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the UC Reason Description or null.
    */
   public final String getUCReasonDesc( int index )
   {
      return _UCReasonDesc[index];
   }
    
   /**
    * Gets the UC Reason Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the UC Reason Description or the specified default value.
    */
   public final String getUCReasonDesc( int index, String defaultValue )
   {
      return _UCReasonDesc[index] == null ? defaultValue : _UCReasonDesc[index];
   }
    
   /**
    * Gets the array of UC Reason Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of UC Reason Description values.
    */
   public final String[] getUCReasonDescArray()
   {
      return _UCReasonDesc;
   }
    
   /**
    * Gets the Transaction TransType field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transaction TransType or null.
    */
   public final String getTradesTransType( int index )
   {
      return _TradesTransType[index];
   }
    
   /**
    * Gets the Transaction TransType field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transaction TransType or the specified default value.
    */
   public final String getTradesTransType( int index, String defaultValue )
   {
      return _TradesTransType[index] == null ? defaultValue : _TradesTransType[index];
   }
    
   /**
    * Gets the array of Transaction TransType fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transaction TransType values.
    */
   public final String[] getTradesTransTypeArray()
   {
      return _TradesTransType;
   }
    
   /**
    * Gets the Amount Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Amount Type or null.
    */
   public final String getAmountType( int index )
   {
      return _AmountType[index];
   }
    
   /**
    * Gets the Amount Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Amount Type or the specified default value.
    */
   public final String getAmountType( int index, String defaultValue )
   {
      return _AmountType[index] == null ? defaultValue : _AmountType[index];
   }
    
   /**
    * Gets the array of Amount Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Amount Type values.
    */
   public final String[] getAmountTypeArray()
   {
      return _AmountType;
   }
    
   /**
    * Gets the Cancelled flag field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Cancelled flag or null.
    */
   public final Boolean getCancelled( int index )
   {
      return _Cancelled[index];
   }
    
   /**
    * Gets the Cancelled flag field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Cancelled flag or the specified default value.
    */
   public final boolean getCancelled( int index, boolean defaultValue )
   {
      return _Cancelled[index] == null ? defaultValue : _Cancelled[index].booleanValue();
   }
    
   /**
    * Gets the array of Cancelled flag fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Cancelled flag values.
    */
   public final Boolean[] getCancelledArray()
   {
      return _Cancelled;
   }
    
   /**
    * Gets the Reversal flag field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reversal flag or null.
    */
   public final Boolean getReversal( int index )
   {
      return _Reversal[index];
   }
    
   /**
    * Gets the Reversal flag field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reversal flag or the specified default value.
    */
   public final boolean getReversal( int index, boolean defaultValue )
   {
      return _Reversal[index] == null ? defaultValue : _Reversal[index].booleanValue();
   }
    
   /**
    * Gets the array of Reversal flag fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reversal flag values.
    */
   public final Boolean[] getReversalArray()
   {
      return _Reversal;
   }
    
   /**
    * Gets the HRDCPending flag field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the HRDCPending flag or null.
    */
   public final Boolean getHRDCPending( int index )
   {
      return _HRDCPending[index];
   }
    
   /**
    * Gets the HRDCPending flag field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the HRDCPending flag or the specified default value.
    */
   public final boolean getHRDCPending( int index, boolean defaultValue )
   {
      return _HRDCPending[index] == null ? defaultValue : _HRDCPending[index].booleanValue();
   }
    
   /**
    * Gets the array of HRDCPending flag fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of HRDCPending flag values.
    */
   public final Boolean[] getHRDCPendingArray()
   {
      return _HRDCPending;
   }
    
   /**
    * Gets the GrossNet field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the GrossNet or null.
    */
   public final String getGrossNet( int index )
   {
      return _GrossNet[index];
   }
    
   /**
    * Gets the GrossNet field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the GrossNet or the specified default value.
    */
   public final String getGrossNet( int index, String defaultValue )
   {
      return _GrossNet[index] == null ? defaultValue : _GrossNet[index];
   }
    
   /**
    * Gets the array of GrossNet fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of GrossNet values.
    */
   public final String[] getGrossNetArray()
   {
      return _GrossNet;
   }
    
   /**
    * Gets the The Gross Amount of the trade field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the The Gross Amount of the trade or null.
    */
   public final String getTradeGrossAmt( int index )
   {
      return _TradeGrossAmt[index];
   }
    
   /**
    * Gets the The Gross Amount of the trade field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the The Gross Amount of the trade or the specified default value.
    */
   public final String getTradeGrossAmt( int index, String defaultValue )
   {
      return _TradeGrossAmt[index] == null ? defaultValue : _TradeGrossAmt[index];
   }
    
   /**
    * Gets the array of The Gross Amount of the trade fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of The Gross Amount of the trade values.
    */
   public final String[] getTradeGrossAmtArray()
   {
      return _TradeGrossAmt;
   }
    
   /**
    * Gets the Transaction number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transaction number or null.
    */
   public final Integer getTransNum( int index )
   {
      return _TransNum[index];
   }
    
   /**
    * Gets the Transaction number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transaction number or the specified default value.
    */
   public final int getTransNum( int index, int defaultValue )
   {
      return _TransNum[index] == null ? defaultValue : _TransNum[index].intValue();
   }
    
   /**
    * Gets the array of Transaction number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transaction number values.
    */
   public final Integer[] getTransNumArray()
   {
      return _TransNum;
   }
    
   /**
    * Gets the Tax Year field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax Year or null.
    */
   public final Integer getTaxYear( int index )
   {
      return _TaxYear[index];
   }
    
   /**
    * Gets the Tax Year field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Year or the specified default value.
    */
   public final int getTaxYear( int index, int defaultValue )
   {
      return _TaxYear[index] == null ? defaultValue : _TaxYear[index].intValue();
   }
    
   /**
    * Gets the array of Tax Year fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax Year values.
    */
   public final Integer[] getTaxYearArray()
   {
      return _TaxYear;
   }
    
   /**
    * Gets the Purchase Additional field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Purchase Additional or null.
    */
   public final String getPurAdd( int index )
   {
      return _PurAdd[index];
   }
    
   /**
    * Gets the Purchase Additional field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Purchase Additional or the specified default value.
    */
   public final String getPurAdd( int index, String defaultValue )
   {
      return _PurAdd[index] == null ? defaultValue : _PurAdd[index];
   }
    
   /**
    * Gets the array of Purchase Additional fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Purchase Additional values.
    */
   public final String[] getPurAddArray()
   {
      return _PurAdd;
   }
    
   /**
    * Gets the Purchase CLB field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Purchase CLB or null.
    */
   public final String getPurCLB( int index )
   {
      return _PurCLB[index];
   }
    
   /**
    * Gets the Purchase CLB field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Purchase CLB or the specified default value.
    */
   public final String getPurCLB( int index, String defaultValue )
   {
      return _PurCLB[index] == null ? defaultValue : _PurCLB[index];
   }
    
   /**
    * Gets the array of Purchase CLB fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Purchase CLB values.
    */
   public final String[] getPurCLBArray()
   {
      return _PurCLB;
   }
    
   /**
    * Gets the Purchase Provincial Grant field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Purchase Provincial Grant or null.
    */
   public final String getPurPGrant( int index )
   {
      return _PurPGrant[index];
   }
    
   /**
    * Gets the Purchase Provincial Grant field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Purchase Provincial Grant or the specified default value.
    */
   public final String getPurPGrant( int index, String defaultValue )
   {
      return _PurPGrant[index] == null ? defaultValue : _PurPGrant[index];
   }
    
   /**
    * Gets the array of Purchase Provincial Grant fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Purchase Provincial Grant values.
    */
   public final String[] getPurPGrantArray()
   {
      return _PurPGrant;
   }
    
   /**
    * Gets the Purchase QESI field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Purchase QESI or null.
    */
   public final String getPurQESI( int index )
   {
      return _PurQESI[index];
   }
    
   /**
    * Gets the Purchase QESI field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Purchase QESI or the specified default value.
    */
   public final String getPurQESI( int index, String defaultValue )
   {
      return _PurQESI[index] == null ? defaultValue : _PurQESI[index];
   }
    
   /**
    * Gets the array of Purchase QESI fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Purchase QESI values.
    */
   public final String[] getPurQESIArray()
   {
      return _PurQESI;
   }
    
   /**
    * Gets the Redemption Income field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Redemption Income or null.
    */
   public final String getRedIncome( int index )
   {
      return _RedIncome[index];
   }
    
   /**
    * Gets the Redemption Income field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Redemption Income or the specified default value.
    */
   public final String getRedIncome( int index, String defaultValue )
   {
      return _RedIncome[index] == null ? defaultValue : _RedIncome[index];
   }
    
   /**
    * Gets the array of Redemption Income fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Redemption Income values.
    */
   public final String[] getRedIncomeArray()
   {
      return _RedIncome;
   }
    
   /**
    * Gets the Redemption CESG field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Redemption CESG or null.
    */
   public final String getRedCESG( int index )
   {
      return _RedCESG[index];
   }
    
   /**
    * Gets the Redemption CESG field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Redemption CESG or the specified default value.
    */
   public final String getRedCESG( int index, String defaultValue )
   {
      return _RedCESG[index] == null ? defaultValue : _RedCESG[index];
   }
    
   /**
    * Gets the array of Redemption CESG fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Redemption CESG values.
    */
   public final String[] getRedCESGArray()
   {
      return _RedCESG;
   }
    
   /**
    * Gets the Redemption CLB field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Redemption CLB or null.
    */
   public final String getRedCLB( int index )
   {
      return _RedCLB[index];
   }
    
   /**
    * Gets the Redemption CLB field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Redemption CLB or the specified default value.
    */
   public final String getRedCLB( int index, String defaultValue )
   {
      return _RedCLB[index] == null ? defaultValue : _RedCLB[index];
   }
    
   /**
    * Gets the array of Redemption CLB fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Redemption CLB values.
    */
   public final String[] getRedCLBArray()
   {
      return _RedCLB;
   }
    
   /**
    * Gets the Redemption Provincial Grant field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Redemption Provincial Grant or null.
    */
   public final String getRedPGrant( int index )
   {
      return _RedPGrant[index];
   }
    
   /**
    * Gets the Redemption Provincial Grant field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Redemption Provincial Grant or the specified default value.
    */
   public final String getRedPGrant( int index, String defaultValue )
   {
      return _RedPGrant[index] == null ? defaultValue : _RedPGrant[index];
   }
    
   /**
    * Gets the array of Redemption Provincial Grant fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Redemption Provincial Grant values.
    */
   public final String[] getRedPGrantArray()
   {
      return _RedPGrant;
   }
    
   /**
    * Gets the Redemption QESI field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Redemption QESI or null.
    */
   public final String getRedQESI( int index )
   {
      return _RedQESI[index];
   }
    
   /**
    * Gets the Redemption QESI field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Redemption QESI or the specified default value.
    */
   public final String getRedQESI( int index, String defaultValue )
   {
      return _RedQESI[index] == null ? defaultValue : _RedQESI[index];
   }
    
   /**
    * Gets the array of Redemption QESI fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Redemption QESI values.
    */
   public final String[] getRedQESIArray()
   {
      return _RedQESI;
   }
    
   /**
    * Gets the Additional QESI Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Additional QESI Amount or null.
    */
   public final String getAddtlQESI( int index )
   {
      return _AddtlQESI[index];
   }
    
   /**
    * Gets the Additional QESI Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Additional QESI Amount or the specified default value.
    */
   public final String getAddtlQESI( int index, String defaultValue )
   {
      return _AddtlQESI[index] == null ? defaultValue : _AddtlQESI[index];
   }
    
   /**
    * Gets the array of Additional QESI Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Additional QESI Amount values.
    */
   public final String[] getAddtlQESIArray()
   {
      return _AddtlQESI;
   }
    
   /**
    * Gets the Account To field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account To or null.
    */
   public final String getAccountTo( int index )
   {
      return _AccountTo[index];
   }
    
   /**
    * Gets the Account To field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account To or the specified default value.
    */
   public final String getAccountTo( int index, String defaultValue )
   {
      return _AccountTo[index] == null ? defaultValue : _AccountTo[index];
   }
    
   /**
    * Gets the array of Account To fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account To values.
    */
   public final String[] getAccountToArray()
   {
      return _AccountTo;
   }
    
   /**
    * Gets the AIP Accountholder Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AIP Accountholder Name or null.
    */
   public final String getAIPAcctName( int index )
   {
      return _AIPAcctName[index];
   }
    
   /**
    * Gets the AIP Accountholder Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AIP Accountholder Name or the specified default value.
    */
   public final String getAIPAcctName( int index, String defaultValue )
   {
      return _AIPAcctName[index] == null ? defaultValue : _AIPAcctName[index];
   }
    
   /**
    * Gets the array of AIP Accountholder Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AIP Accountholder Name values.
    */
   public final String[] getAIPAcctNameArray()
   {
      return _AIPAcctName;
   }
    
   /**
    * Gets the Historical NOn Trustee Year field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Historical NOn Trustee Year or null.
    */
   public final Integer getHistNonTrustYear( int index )
   {
      return _HistNonTrustYear[index];
   }
    
   /**
    * Gets the Historical NOn Trustee Year field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Historical NOn Trustee Year or the specified default value.
    */
   public final int getHistNonTrustYear( int index, int defaultValue )
   {
      return _HistNonTrustYear[index] == null ? defaultValue : _HistNonTrustYear[index].intValue();
   }
    
   /**
    * Gets the array of Historical NOn Trustee Year fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Historical NOn Trustee Year values.
    */
   public final Integer[] getHistNonTrustYearArray()
   {
      return _HistNonTrustYear;
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
    * Gets the SAGES Purchase Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SAGES Purchase Amount or null.
    */
   public final String getSAGESPurAmt( int index )
   {
      return _SAGESPurAmt[index];
   }
    
   /**
    * Gets the SAGES Purchase Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SAGES Purchase Amount or the specified default value.
    */
   public final String getSAGESPurAmt( int index, String defaultValue )
   {
      return _SAGESPurAmt[index] == null ? defaultValue : _SAGESPurAmt[index];
   }
    
   /**
    * Gets the array of SAGES Purchase Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SAGES Purchase Amount values.
    */
   public final String[] getSAGESPurAmtArray()
   {
      return _SAGESPurAmt;
   }
    
   /**
    * Gets the SAGES Redemption Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SAGES Redemption Amount or null.
    */
   public final String getSAGESRedAmt( int index )
   {
      return _SAGESRedAmt[index];
   }
    
   /**
    * Gets the SAGES Redemption Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SAGES Redemption Amount or the specified default value.
    */
   public final String getSAGESRedAmt( int index, String defaultValue )
   {
      return _SAGESRedAmt[index] == null ? defaultValue : _SAGESRedAmt[index];
   }
    
   /**
    * Gets the array of SAGES Redemption Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SAGES Redemption Amount values.
    */
   public final String[] getSAGESRedAmtArray()
   {
      return _SAGESRedAmt;
   }
    
   /**
    * Gets the SAGES unique ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SAGES unique ID or null.
    */
   public final String getSAGESTransID( int index )
   {
      return _SAGESTransID[index];
   }
    
   /**
    * Gets the SAGES unique ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SAGES unique ID or the specified default value.
    */
   public final String getSAGESTransID( int index, String defaultValue )
   {
      return _SAGESTransID[index] == null ? defaultValue : _SAGESTransID[index];
   }
    
   /**
    * Gets the array of SAGES unique ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SAGES unique ID values.
    */
   public final String[] getSAGESTransIDArray()
   {
      return _SAGESTransID;
   }
    
   /**
    * Gets the SAGES Trans Orig Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SAGES Trans Orig Code or null.
    */
   public final String getSAGESTransOrigCode( int index )
   {
      return _SAGESTransOrigCode[index];
   }
    
   /**
    * Gets the SAGES Trans Orig Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SAGES Trans Orig Code or the specified default value.
    */
   public final String getSAGESTransOrigCode( int index, String defaultValue )
   {
      return _SAGESTransOrigCode[index] == null ? defaultValue : _SAGESTransOrigCode[index];
   }
    
   /**
    * Gets the array of SAGES Trans Orig Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SAGES Trans Orig Code values.
    */
   public final String[] getSAGESTransOrigCodeArray()
   {
      return _SAGESTransOrigCode;
   }
    
   /**
    * Gets the SAGES Unassisted Reason field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SAGES Unassisted Reason or null.
    */
   public final String getSAGESUCDesc( int index )
   {
      return _SAGESUCDesc[index];
   }
    
   /**
    * Gets the SAGES Unassisted Reason field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SAGES Unassisted Reason or the specified default value.
    */
   public final String getSAGESUCDesc( int index, String defaultValue )
   {
      return _SAGESUCDesc[index] == null ? defaultValue : _SAGESUCDesc[index];
   }
    
   /**
    * Gets the array of SAGES Unassisted Reason fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SAGES Unassisted Reason values.
    */
   public final String[] getSAGESUCDescArray()
   {
      return _SAGESUCDesc;
   }
    
   /**
    * Gets the SAGES Reject Reason field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SAGES Reject Reason or null.
    */
   public final String getSAGESRejDesc( int index )
   {
      return _SAGESRejDesc[index];
   }
    
   /**
    * Gets the SAGES Reject Reason field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SAGES Reject Reason or the specified default value.
    */
   public final String getSAGESRejDesc( int index, String defaultValue )
   {
      return _SAGESRejDesc[index] == null ? defaultValue : _SAGESRejDesc[index];
   }
    
   /**
    * Gets the array of SAGES Reject Reason fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SAGES Reject Reason values.
    */
   public final String[] getSAGESRejDescArray()
   {
      return _SAGESRejDesc;
   }
    
   /**
    * Gets the SAGES reported to govt field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SAGES reported to govt or null.
    */
   public final String getSAGESReported( int index )
   {
      return _SAGESReported[index];
   }
    
   /**
    * Gets the SAGES reported to govt field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SAGES reported to govt or the specified default value.
    */
   public final String getSAGESReported( int index, String defaultValue )
   {
      return _SAGESReported[index] == null ? defaultValue : _SAGESReported[index];
   }
    
   /**
    * Gets the array of SAGES reported to govt fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SAGES reported to govt values.
    */
   public final String[] getSAGESReportedArray()
   {
      return _SAGESReported;
   }
    
   /**
    * Gets the SAGES Unassisted Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SAGES Unassisted Amount or null.
    */
   public final String getSAGESUCAmt( int index )
   {
      return _SAGESUCAmt[index];
   }
    
   /**
    * Gets the SAGES Unassisted Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SAGES Unassisted Amount or the specified default value.
    */
   public final String getSAGESUCAmt( int index, String defaultValue )
   {
      return _SAGESUCAmt[index] == null ? defaultValue : _SAGESUCAmt[index];
   }
    
   /**
    * Gets the array of SAGES Unassisted Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SAGES Unassisted Amount values.
    */
   public final String[] getSAGESUCAmtArray()
   {
      return _SAGESUCAmt;
   }
    
   /**
    * Gets the SAGES Assisted Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SAGES Assisted Amount or null.
    */
   public final String getSAGESACAmt( int index )
   {
      return _SAGESACAmt[index];
   }
    
   /**
    * Gets the SAGES Assisted Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SAGES Assisted Amount or the specified default value.
    */
   public final String getSAGESACAmt( int index, String defaultValue )
   {
      return _SAGESACAmt[index] == null ? defaultValue : _SAGESACAmt[index];
   }
    
   /**
    * Gets the array of SAGES Assisted Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SAGES Assisted Amount values.
    */
   public final String[] getSAGESACAmtArray()
   {
      return _SAGESACAmt;
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
      _rxAccountNum = responseBuffer.decodeString(responseBuffer.getNextField());
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _BeneName = resizeArray( _BeneName, _RepeatCount );
      _RESPDepositType = resizeArray( _RESPDepositType, _RepeatCount );
      _RESPDepositTypeDesc = resizeArray( _RESPDepositTypeDesc, _RepeatCount );
      _RedCode = resizeArray( _RedCode, _RepeatCount );
      _RedCodeDesc = resizeArray( _RedCodeDesc, _RepeatCount );
      _TransId = resizeArray( _TransId, _RepeatCount );
      _EffectiveDate = resizeArray( _EffectiveDate, _RepeatCount );
      _GrossAmt = resizeArray( _GrossAmt, _RepeatCount );
      _HRDCTransId = resizeArray( _HRDCTransId, _RepeatCount );
      _SettleDate = resizeArray( _SettleDate, _RepeatCount );
      _ACAmt = resizeArray( _ACAmt, _RepeatCount );
      _TerminateDate = resizeArray( _TerminateDate, _RepeatCount );
      _GrantAmount = resizeArray( _GrantAmount, _RepeatCount );
      _LifeContr = resizeArray( _LifeContr, _RepeatCount );
      _GrantTransCode = resizeArray( _GrantTransCode, _RepeatCount );
      _GrantTransLabel = resizeArray( _GrantTransLabel, _RepeatCount );
      _GrantTransId = resizeArray( _GrantTransId, _RepeatCount );
      _RedLifeContr = resizeArray( _RedLifeContr, _RepeatCount );
      _UCAmt = resizeArray( _UCAmt, _RepeatCount );
      _UCReason = resizeArray( _UCReason, _RepeatCount );
      _OldContractId = resizeArray( _OldContractId, _RepeatCount );
      _OldPlanId = resizeArray( _OldPlanId, _RepeatCount );
      _RESPLetter = resizeArray( _RESPLetter, _RepeatCount );
      _HRDCReported = resizeArray( _HRDCReported, _RepeatCount );
      _RESPTransStat = resizeArray( _RESPTransStat, _RepeatCount );
      _GrantRepayable = resizeArray( _GrantRepayable, _RepeatCount );
      _YTDContr = resizeArray( _YTDContr, _RepeatCount );
      _AddlCESGRsnCode = resizeArray( _AddlCESGRsnCode, _RepeatCount );
      _AddlCESGRsnDesc = resizeArray( _AddlCESGRsnDesc, _RepeatCount );
      _CESGAmount = resizeArray( _CESGAmount, _RepeatCount );
      _NeedRepHRDC = resizeArray( _NeedRepHRDC, _RepeatCount );
      _CESGInDtlErrorDesc = resizeArray( _CESGInDtlErrorDesc, _RepeatCount );
      _Tainted = resizeArray( _Tainted, _RepeatCount );
      _OCRdmYear = resizeArray( _OCRdmYear, _RepeatCount );
      _GRRepayReason = resizeArray( _GRRepayReason, _RepeatCount );
      _UCReasonDesc = resizeArray( _UCReasonDesc, _RepeatCount );
      _TradesTransType = resizeArray( _TradesTransType, _RepeatCount );
      _AmountType = resizeArray( _AmountType, _RepeatCount );
      _Cancelled = resizeArray( _Cancelled, _RepeatCount );
      _Reversal = resizeArray( _Reversal, _RepeatCount );
      _HRDCPending = resizeArray( _HRDCPending, _RepeatCount );
      _GrossNet = resizeArray( _GrossNet, _RepeatCount );
      _TradeGrossAmt = resizeArray( _TradeGrossAmt, _RepeatCount );
      _TransNum = resizeArray( _TransNum, _RepeatCount );
      _TaxYear = resizeArray( _TaxYear, _RepeatCount );
      _PurAdd = resizeArray( _PurAdd, _RepeatCount );
      _PurCLB = resizeArray( _PurCLB, _RepeatCount );
      _PurPGrant = resizeArray( _PurPGrant, _RepeatCount );
      _PurQESI = resizeArray( _PurQESI, _RepeatCount );
      _RedIncome = resizeArray( _RedIncome, _RepeatCount );
      _RedCESG = resizeArray( _RedCESG, _RepeatCount );
      _RedCLB = resizeArray( _RedCLB, _RepeatCount );
      _RedPGrant = resizeArray( _RedPGrant, _RepeatCount );
      _RedQESI = resizeArray( _RedQESI, _RepeatCount );
      _AddtlQESI = resizeArray( _AddtlQESI, _RepeatCount );
      _AccountTo = resizeArray( _AccountTo, _RepeatCount );
      _AIPAcctName = resizeArray( _AIPAcctName, _RepeatCount );
      _HistNonTrustYear = resizeArray( _HistNonTrustYear, _RepeatCount );
      _IsResidualCESG = resizeArray( _IsResidualCESG, _RepeatCount );
      _SAGESPurAmt = resizeArray( _SAGESPurAmt, _RepeatCount );
      _SAGESRedAmt = resizeArray( _SAGESRedAmt, _RepeatCount );
      _SAGESTransID = resizeArray( _SAGESTransID, _RepeatCount );
      _SAGESTransOrigCode = resizeArray( _SAGESTransOrigCode, _RepeatCount );
      _SAGESUCDesc = resizeArray( _SAGESUCDesc, _RepeatCount );
      _SAGESRejDesc = resizeArray( _SAGESRejDesc, _RepeatCount );
      _SAGESReported = resizeArray( _SAGESReported, _RepeatCount );
      _SAGESUCAmt = resizeArray( _SAGESUCAmt, _RepeatCount );
      _SAGESACAmt = resizeArray( _SAGESACAmt, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _BeneName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RESPDepositType[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _RESPDepositTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RedCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RedCodeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TransId[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _GrossAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _HRDCTransId[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SettleDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ACAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TerminateDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _GrantAmount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LifeContr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GrantTransCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GrantTransLabel[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GrantTransId[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RedLifeContr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UCAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UCReason[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _OldContractId[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _OldPlanId[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RESPLetter[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _HRDCReported[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _RESPTransStat[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GrantRepayable[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _YTDContr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddlCESGRsnCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddlCESGRsnDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CESGAmount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _NeedRepHRDC[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _CESGInDtlErrorDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Tainted[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _OCRdmYear[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _GRRepayReason[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UCReasonDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TradesTransType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AmountType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Cancelled[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _Reversal[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _HRDCPending[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _GrossNet[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TradeGrossAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TransNum[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _TaxYear[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _PurAdd[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PurCLB[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PurPGrant[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PurQESI[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RedIncome[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RedCESG[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RedCLB[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RedPGrant[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RedQESI[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddtlQESI[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AccountTo[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AIPAcctName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _HistNonTrustYear[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _IsResidualCESG[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _SAGESPurAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SAGESRedAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SAGESTransID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SAGESTransOrigCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SAGESUCDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SAGESRejDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SAGESReported[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SAGESUCAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SAGESACAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
