
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * FUNDCom Seg Guarantee Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/FundComSGInq.doc">FundComSGInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class FundComSGInqView extends IFastView implements Serializable
{

   /**
    * Total Guarantee Amount member variable.
    */
   private String _TotalGuarAmount = null;
   
   /**
    * Total DB Amount member variable.
    */
   private String _TotalDBAmount = null;
   
   /**
    * Total Deposit Mat Guarantee member variable.
    */
   private String _TotalDepMatGuar = null;
   
   /**
    * Total Quote Market Value member variable.
    */
   private String _TotalQuoteMktValue = null;
   
   private int _RepeatCount = 0;
   
   /**
    * Contract Type member array.
    */
   private String[] _ContractType = null;
   
   /**
    * EffectiveDate member array.
    */
   private Date[] _EffectiveDate = null;
   
   /**
    * Guarantee Amount member array.
    */
   private String[] _GuarAmount = null;
   
   /**
    * Maturity Date member array.
    */
   private Date[] _MaturDate = null;
   
   /**
    * DB Amount member array.
    */
   private String[] _DBAmount = null;
   
   /**
    * Deposit Maturity Guarantee member array.
    */
   private String[] _DepMatGuarantee = null;
   
   /**
    * Quote Market Value member array.
    */
   private String[] _QuoteMktValue = null;
   
   /**
    * Guarantee Information Level member array.
    */
   private String[] _GuaranteeLevel = null;
   
   /**
    * Base Guaranteed Amount member array.
    */
   private String[] _BaseGuarAmt = null;
   
   /**
    * Guarantee Minimum Withdrawal Amount member array.
    */
   private String[] _MinWithdrawalAmt = null;
   
   /**
    * Guarantee Minimum Withdrawal Amount Remaining member array.
    */
   private String[] _MWAremaining = null;
   
   /**
    * Guarantee Minimum Withdrawal Amount Exceeded member array.
    */
   private String[] _MWAexceeded = null;
   
   /**
    * Guarantee Minimum Withdrawal Amount Adjusted member array.
    */
   private String[] _MWAadjusted = null;
   
   /**
    * GMWB Bonus Amount member array.
    */
   private String[] _BonusBaseAmt = null;
   
   /**
    * GMWB Valuation Date member array.
    */
   private Date[] _AnnDate = null;
   
   /**
    * GMWB Period Indicator member array.
    */
   private String[] _PeriodIndc = null;
   
   /**
    * Lifetime Withdrawal Amount member array.
    */
   private String[] _LifeWithdrawalAmt = null;
   
   /**
    * Remaining Lifetime Withdrawal Amount member array.
    */
   private String[] _LWAremaining = null;
   
   /**
    * Lifetime Withdrawal Amount Exceeded member array.
    */
   private String[] _LWAexceeded = null;
   
   /**
    * Lifetime Withdrawal Amount Adjusted member array.
    */
   private String[] _LWAadjusted = null;
   

   /**
    * Constructs the FundComSGInqView object.
    * 
    */
   public FundComSGInqView()
   {
      super ( new FundComSGInqRequest() );
   }

   /**
    * Constructs the FundComSGInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public FundComSGInqView( String hostEncoding )
   {
      super ( new FundComSGInqRequest( hostEncoding ) );
   }

   /**
    * Gets the FundComSGInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The FundComSGInqRequest object.
    */
   public final FundComSGInqRequest getRequest()
   {
      return (FundComSGInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Total Guarantee Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Total Guarantee Amount or null.
    */
   public final String getTotalGuarAmount()
   {
      return _TotalGuarAmount;
   }
	
   /**
    * Gets the Total Guarantee Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Total Guarantee Amount or the specified default value.
    */
   public final String getTotalGuarAmount( String defaultValue )
   {
      return _TotalGuarAmount == null ? defaultValue : _TotalGuarAmount;
   }
                  
   /**
    * Gets the Total DB Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Total DB Amount or null.
    */
   public final String getTotalDBAmount()
   {
      return _TotalDBAmount;
   }
	
   /**
    * Gets the Total DB Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Total DB Amount or the specified default value.
    */
   public final String getTotalDBAmount( String defaultValue )
   {
      return _TotalDBAmount == null ? defaultValue : _TotalDBAmount;
   }
                  
   /**
    * Gets the Total Deposit Mat Guarantee field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Total Deposit Mat Guarantee or null.
    */
   public final String getTotalDepMatGuar()
   {
      return _TotalDepMatGuar;
   }
	
   /**
    * Gets the Total Deposit Mat Guarantee field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Total Deposit Mat Guarantee or the specified default value.
    */
   public final String getTotalDepMatGuar( String defaultValue )
   {
      return _TotalDepMatGuar == null ? defaultValue : _TotalDepMatGuar;
   }
                  
   /**
    * Gets the Total Quote Market Value field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Total Quote Market Value or null.
    */
   public final String getTotalQuoteMktValue()
   {
      return _TotalQuoteMktValue;
   }
	
   /**
    * Gets the Total Quote Market Value field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Total Quote Market Value or the specified default value.
    */
   public final String getTotalQuoteMktValue( String defaultValue )
   {
      return _TotalQuoteMktValue == null ? defaultValue : _TotalQuoteMktValue;
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
    * Gets the Contract Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contract Type or null.
    */
   public final String getContractType( int index )
   {
      return _ContractType[index];
   }
    
   /**
    * Gets the Contract Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contract Type or the specified default value.
    */
   public final String getContractType( int index, String defaultValue )
   {
      return _ContractType[index] == null ? defaultValue : _ContractType[index];
   }
    
   /**
    * Gets the array of Contract Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contract Type values.
    */
   public final String[] getContractTypeArray()
   {
      return _ContractType;
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
    * Gets the Guarantee Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Guarantee Amount or null.
    */
   public final String getGuarAmount( int index )
   {
      return _GuarAmount[index];
   }
    
   /**
    * Gets the Guarantee Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Guarantee Amount or the specified default value.
    */
   public final String getGuarAmount( int index, String defaultValue )
   {
      return _GuarAmount[index] == null ? defaultValue : _GuarAmount[index];
   }
    
   /**
    * Gets the array of Guarantee Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Guarantee Amount values.
    */
   public final String[] getGuarAmountArray()
   {
      return _GuarAmount;
   }
    
   /**
    * Gets the Maturity Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Maturity Date or null.
    */
   public final Date getMaturDate( int index )
   {
      return _MaturDate[index];
   }
    
   /**
    * Gets the Maturity Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Maturity Date or the specified default value.
    */
   public final Date getMaturDate( int index, Date defaultValue )
   {
      return _MaturDate[index] == null ? defaultValue : _MaturDate[index];
   }
    
   /**
    * Gets the array of Maturity Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Maturity Date values.
    */
   public final Date[] getMaturDateArray()
   {
      return _MaturDate;
   }
    
   /**
    * Gets the DB Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the DB Amount or null.
    */
   public final String getDBAmount( int index )
   {
      return _DBAmount[index];
   }
    
   /**
    * Gets the DB Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the DB Amount or the specified default value.
    */
   public final String getDBAmount( int index, String defaultValue )
   {
      return _DBAmount[index] == null ? defaultValue : _DBAmount[index];
   }
    
   /**
    * Gets the array of DB Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of DB Amount values.
    */
   public final String[] getDBAmountArray()
   {
      return _DBAmount;
   }
    
   /**
    * Gets the Deposit Maturity Guarantee field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Deposit Maturity Guarantee or null.
    */
   public final String getDepMatGuarantee( int index )
   {
      return _DepMatGuarantee[index];
   }
    
   /**
    * Gets the Deposit Maturity Guarantee field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Deposit Maturity Guarantee or the specified default value.
    */
   public final String getDepMatGuarantee( int index, String defaultValue )
   {
      return _DepMatGuarantee[index] == null ? defaultValue : _DepMatGuarantee[index];
   }
    
   /**
    * Gets the array of Deposit Maturity Guarantee fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Deposit Maturity Guarantee values.
    */
   public final String[] getDepMatGuaranteeArray()
   {
      return _DepMatGuarantee;
   }
    
   /**
    * Gets the Quote Market Value field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Quote Market Value or null.
    */
   public final String getQuoteMktValue( int index )
   {
      return _QuoteMktValue[index];
   }
    
   /**
    * Gets the Quote Market Value field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Quote Market Value or the specified default value.
    */
   public final String getQuoteMktValue( int index, String defaultValue )
   {
      return _QuoteMktValue[index] == null ? defaultValue : _QuoteMktValue[index];
   }
    
   /**
    * Gets the array of Quote Market Value fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Quote Market Value values.
    */
   public final String[] getQuoteMktValueArray()
   {
      return _QuoteMktValue;
   }
    
   /**
    * Gets the Guarantee Information Level field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Guarantee Information Level or null.
    */
   public final String getGuaranteeLevel( int index )
   {
      return _GuaranteeLevel[index];
   }
    
   /**
    * Gets the Guarantee Information Level field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Guarantee Information Level or the specified default value.
    */
   public final String getGuaranteeLevel( int index, String defaultValue )
   {
      return _GuaranteeLevel[index] == null ? defaultValue : _GuaranteeLevel[index];
   }
    
   /**
    * Gets the array of Guarantee Information Level fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Guarantee Information Level values.
    */
   public final String[] getGuaranteeLevelArray()
   {
      return _GuaranteeLevel;
   }
    
   /**
    * Gets the Base Guaranteed Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Base Guaranteed Amount or null.
    */
   public final String getBaseGuarAmt( int index )
   {
      return _BaseGuarAmt[index];
   }
    
   /**
    * Gets the Base Guaranteed Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Base Guaranteed Amount or the specified default value.
    */
   public final String getBaseGuarAmt( int index, String defaultValue )
   {
      return _BaseGuarAmt[index] == null ? defaultValue : _BaseGuarAmt[index];
   }
    
   /**
    * Gets the array of Base Guaranteed Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Base Guaranteed Amount values.
    */
   public final String[] getBaseGuarAmtArray()
   {
      return _BaseGuarAmt;
   }
    
   /**
    * Gets the Guarantee Minimum Withdrawal Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Guarantee Minimum Withdrawal Amount or null.
    */
   public final String getMinWithdrawalAmt( int index )
   {
      return _MinWithdrawalAmt[index];
   }
    
   /**
    * Gets the Guarantee Minimum Withdrawal Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Guarantee Minimum Withdrawal Amount or the specified default value.
    */
   public final String getMinWithdrawalAmt( int index, String defaultValue )
   {
      return _MinWithdrawalAmt[index] == null ? defaultValue : _MinWithdrawalAmt[index];
   }
    
   /**
    * Gets the array of Guarantee Minimum Withdrawal Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Guarantee Minimum Withdrawal Amount values.
    */
   public final String[] getMinWithdrawalAmtArray()
   {
      return _MinWithdrawalAmt;
   }
    
   /**
    * Gets the Guarantee Minimum Withdrawal Amount Remaining field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Guarantee Minimum Withdrawal Amount Remaining or null.
    */
   public final String getMWAremaining( int index )
   {
      return _MWAremaining[index];
   }
    
   /**
    * Gets the Guarantee Minimum Withdrawal Amount Remaining field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Guarantee Minimum Withdrawal Amount Remaining or the specified default value.
    */
   public final String getMWAremaining( int index, String defaultValue )
   {
      return _MWAremaining[index] == null ? defaultValue : _MWAremaining[index];
   }
    
   /**
    * Gets the array of Guarantee Minimum Withdrawal Amount Remaining fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Guarantee Minimum Withdrawal Amount Remaining values.
    */
   public final String[] getMWAremainingArray()
   {
      return _MWAremaining;
   }
    
   /**
    * Gets the Guarantee Minimum Withdrawal Amount Exceeded field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Guarantee Minimum Withdrawal Amount Exceeded or null.
    */
   public final String getMWAexceeded( int index )
   {
      return _MWAexceeded[index];
   }
    
   /**
    * Gets the Guarantee Minimum Withdrawal Amount Exceeded field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Guarantee Minimum Withdrawal Amount Exceeded or the specified default value.
    */
   public final String getMWAexceeded( int index, String defaultValue )
   {
      return _MWAexceeded[index] == null ? defaultValue : _MWAexceeded[index];
   }
    
   /**
    * Gets the array of Guarantee Minimum Withdrawal Amount Exceeded fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Guarantee Minimum Withdrawal Amount Exceeded values.
    */
   public final String[] getMWAexceededArray()
   {
      return _MWAexceeded;
   }
    
   /**
    * Gets the Guarantee Minimum Withdrawal Amount Adjusted field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Guarantee Minimum Withdrawal Amount Adjusted or null.
    */
   public final String getMWAadjusted( int index )
   {
      return _MWAadjusted[index];
   }
    
   /**
    * Gets the Guarantee Minimum Withdrawal Amount Adjusted field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Guarantee Minimum Withdrawal Amount Adjusted or the specified default value.
    */
   public final String getMWAadjusted( int index, String defaultValue )
   {
      return _MWAadjusted[index] == null ? defaultValue : _MWAadjusted[index];
   }
    
   /**
    * Gets the array of Guarantee Minimum Withdrawal Amount Adjusted fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Guarantee Minimum Withdrawal Amount Adjusted values.
    */
   public final String[] getMWAadjustedArray()
   {
      return _MWAadjusted;
   }
    
   /**
    * Gets the GMWB Bonus Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the GMWB Bonus Amount or null.
    */
   public final String getBonusBaseAmt( int index )
   {
      return _BonusBaseAmt[index];
   }
    
   /**
    * Gets the GMWB Bonus Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the GMWB Bonus Amount or the specified default value.
    */
   public final String getBonusBaseAmt( int index, String defaultValue )
   {
      return _BonusBaseAmt[index] == null ? defaultValue : _BonusBaseAmt[index];
   }
    
   /**
    * Gets the array of GMWB Bonus Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of GMWB Bonus Amount values.
    */
   public final String[] getBonusBaseAmtArray()
   {
      return _BonusBaseAmt;
   }
    
   /**
    * Gets the GMWB Valuation Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the GMWB Valuation Date or null.
    */
   public final Date getAnnDate( int index )
   {
      return _AnnDate[index];
   }
    
   /**
    * Gets the GMWB Valuation Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the GMWB Valuation Date or the specified default value.
    */
   public final Date getAnnDate( int index, Date defaultValue )
   {
      return _AnnDate[index] == null ? defaultValue : _AnnDate[index];
   }
    
   /**
    * Gets the array of GMWB Valuation Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of GMWB Valuation Date values.
    */
   public final Date[] getAnnDateArray()
   {
      return _AnnDate;
   }
    
   /**
    * Gets the GMWB Period Indicator field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the GMWB Period Indicator or null.
    */
   public final String getPeriodIndc( int index )
   {
      return _PeriodIndc[index];
   }
    
   /**
    * Gets the GMWB Period Indicator field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the GMWB Period Indicator or the specified default value.
    */
   public final String getPeriodIndc( int index, String defaultValue )
   {
      return _PeriodIndc[index] == null ? defaultValue : _PeriodIndc[index];
   }
    
   /**
    * Gets the array of GMWB Period Indicator fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of GMWB Period Indicator values.
    */
   public final String[] getPeriodIndcArray()
   {
      return _PeriodIndc;
   }
    
   /**
    * Gets the Lifetime Withdrawal Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Lifetime Withdrawal Amount or null.
    */
   public final String getLifeWithdrawalAmt( int index )
   {
      return _LifeWithdrawalAmt[index];
   }
    
   /**
    * Gets the Lifetime Withdrawal Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Lifetime Withdrawal Amount or the specified default value.
    */
   public final String getLifeWithdrawalAmt( int index, String defaultValue )
   {
      return _LifeWithdrawalAmt[index] == null ? defaultValue : _LifeWithdrawalAmt[index];
   }
    
   /**
    * Gets the array of Lifetime Withdrawal Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Lifetime Withdrawal Amount values.
    */
   public final String[] getLifeWithdrawalAmtArray()
   {
      return _LifeWithdrawalAmt;
   }
    
   /**
    * Gets the Remaining Lifetime Withdrawal Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Remaining Lifetime Withdrawal Amount or null.
    */
   public final String getLWAremaining( int index )
   {
      return _LWAremaining[index];
   }
    
   /**
    * Gets the Remaining Lifetime Withdrawal Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Remaining Lifetime Withdrawal Amount or the specified default value.
    */
   public final String getLWAremaining( int index, String defaultValue )
   {
      return _LWAremaining[index] == null ? defaultValue : _LWAremaining[index];
   }
    
   /**
    * Gets the array of Remaining Lifetime Withdrawal Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Remaining Lifetime Withdrawal Amount values.
    */
   public final String[] getLWAremainingArray()
   {
      return _LWAremaining;
   }
    
   /**
    * Gets the Lifetime Withdrawal Amount Exceeded field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Lifetime Withdrawal Amount Exceeded or null.
    */
   public final String getLWAexceeded( int index )
   {
      return _LWAexceeded[index];
   }
    
   /**
    * Gets the Lifetime Withdrawal Amount Exceeded field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Lifetime Withdrawal Amount Exceeded or the specified default value.
    */
   public final String getLWAexceeded( int index, String defaultValue )
   {
      return _LWAexceeded[index] == null ? defaultValue : _LWAexceeded[index];
   }
    
   /**
    * Gets the array of Lifetime Withdrawal Amount Exceeded fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Lifetime Withdrawal Amount Exceeded values.
    */
   public final String[] getLWAexceededArray()
   {
      return _LWAexceeded;
   }
    
   /**
    * Gets the Lifetime Withdrawal Amount Adjusted field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Lifetime Withdrawal Amount Adjusted or null.
    */
   public final String getLWAadjusted( int index )
   {
      return _LWAadjusted[index];
   }
    
   /**
    * Gets the Lifetime Withdrawal Amount Adjusted field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Lifetime Withdrawal Amount Adjusted or the specified default value.
    */
   public final String getLWAadjusted( int index, String defaultValue )
   {
      return _LWAadjusted[index] == null ? defaultValue : _LWAadjusted[index];
   }
    
   /**
    * Gets the array of Lifetime Withdrawal Amount Adjusted fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Lifetime Withdrawal Amount Adjusted values.
    */
   public final String[] getLWAadjustedArray()
   {
      return _LWAadjusted;
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
      _TotalGuarAmount = responseBuffer.decodeString(responseBuffer.getNextField());
      _TotalDBAmount = responseBuffer.decodeString(responseBuffer.getNextField());
      _TotalDepMatGuar = responseBuffer.decodeString(responseBuffer.getNextField());
      _TotalQuoteMktValue = responseBuffer.decodeString(responseBuffer.getNextField());
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _ContractType = resizeArray( _ContractType, _RepeatCount );
      _EffectiveDate = resizeArray( _EffectiveDate, _RepeatCount );
      _GuarAmount = resizeArray( _GuarAmount, _RepeatCount );
      _MaturDate = resizeArray( _MaturDate, _RepeatCount );
      _DBAmount = resizeArray( _DBAmount, _RepeatCount );
      _DepMatGuarantee = resizeArray( _DepMatGuarantee, _RepeatCount );
      _QuoteMktValue = resizeArray( _QuoteMktValue, _RepeatCount );
      _GuaranteeLevel = resizeArray( _GuaranteeLevel, _RepeatCount );
      _BaseGuarAmt = resizeArray( _BaseGuarAmt, _RepeatCount );
      _MinWithdrawalAmt = resizeArray( _MinWithdrawalAmt, _RepeatCount );
      _MWAremaining = resizeArray( _MWAremaining, _RepeatCount );
      _MWAexceeded = resizeArray( _MWAexceeded, _RepeatCount );
      _MWAadjusted = resizeArray( _MWAadjusted, _RepeatCount );
      _BonusBaseAmt = resizeArray( _BonusBaseAmt, _RepeatCount );
      _AnnDate = resizeArray( _AnnDate, _RepeatCount );
      _PeriodIndc = resizeArray( _PeriodIndc, _RepeatCount );
      _LifeWithdrawalAmt = resizeArray( _LifeWithdrawalAmt, _RepeatCount );
      _LWAremaining = resizeArray( _LWAremaining, _RepeatCount );
      _LWAexceeded = resizeArray( _LWAexceeded, _RepeatCount );
      _LWAadjusted = resizeArray( _LWAadjusted, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _ContractType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _GuarAmount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MaturDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _DBAmount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DepMatGuarantee[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _QuoteMktValue[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GuaranteeLevel[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BaseGuarAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MinWithdrawalAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MWAremaining[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MWAexceeded[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MWAadjusted[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BonusBaseAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AnnDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _PeriodIndc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LifeWithdrawalAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LWAremaining[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LWAexceeded[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LWAadjusted[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
