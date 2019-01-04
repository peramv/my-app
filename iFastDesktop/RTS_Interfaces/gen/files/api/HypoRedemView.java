
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Hypothetical Redemption Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/HypoRedem.doc">HypoRedem.doc</A>.
 * 
 * @author RTS Generated
 */
public class HypoRedemView extends IFastView implements Serializable
{

   /**
    * Total Redemption Amount member variable.
    */
   private String _TotalRedAmt = null;
   
   /**
    * Total Deferred Sales Charge member variable.
    */
   private String _TotalDSC = null;
   
   /**
    * Fees member variable.
    */
   private String _Fee = null;
   
   /**
    * WithHolding Tax member variable.
    */
   private String _WithHoldTax = null;
   
   /**
    * Net Amount member variable.
    */
   private String _NetAmt = null;
   
   private int _RepeatCount = 0;
   
   /**
    * Fund Code member array.
    */
   private String[] _rxFundCode = null;
   
   /**
    * Class Code member array.
    */
   private String[] _rxClassCode = null;
   
   /**
    * Gross Amount member array.
    */
   private String[] _GrossAmt = null;
   
   /**
    * Units member array.
    */
   private String[] _Units = null;
   
   /**
    * Deferred Sales Charge member array.
    */
   private String[] _DSC = null;
   
   /**
    * Fee Free Amount member array.
    */
   private String[] _FeeFreeAmt = null;
   
   /**
    * Fee Free Units member array.
    */
   private String[] _FeeFreeUnits = null;
   
   /**
    * Fee Applicable Amount member array.
    */
   private String[] _FeeApplAmt = null;
   
   /**
    * Fee Applicable Units member array.
    */
   private String[] _FeeApplUnits = null;
   
   /**
    * Valuation date used in calculation member array.
    */
   private Date[] _ValueAsAt = null;
   
   /**
    * Fund valuation price used in calculation member array.
    */
   private String[] _FundNAV = null;
   
   /**
    * Baycom member array.
    */
   private String[] _rxBaycom = null;
   
   /**
    * English Long Name1 member array.
    */
   private String[] _ELongName1 = null;
   
   /**
    * Account Units member array.
    */
   private String[] _AcctUnits = null;
   
   /**
    * Federal Tax member array.
    */
   private String[] _FedTax = null;
   
   /**
    * Provincial Tax member array.
    */
   private String[] _ProvTax = null;
   
   /**
    * Federal Clawback member array.
    */
   private String[] _FedClawback = null;
   
   /**
    * Provincial Clawback member array.
    */
   private String[] _ProvClawback = null;
   
   /**
    * Additional Provincial Clawback member array.
    */
   private String[] _AddlProvClawback = null;
   

   /**
    * Constructs the HypoRedemView object.
    * 
    */
   public HypoRedemView()
   {
      super ( new HypoRedemRequest() );
   }

   /**
    * Constructs the HypoRedemView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public HypoRedemView( String hostEncoding )
   {
      super ( new HypoRedemRequest( hostEncoding ) );
   }

   /**
    * Gets the HypoRedemRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The HypoRedemRequest object.
    */
   public final HypoRedemRequest getRequest()
   {
      return (HypoRedemRequest)getIFastRequest();
   }
        
   /**
    * Gets the Total Redemption Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Total Redemption Amount or null.
    */
   public final String getTotalRedAmt()
   {
      return _TotalRedAmt;
   }
	
   /**
    * Gets the Total Redemption Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Total Redemption Amount or the specified default value.
    */
   public final String getTotalRedAmt( String defaultValue )
   {
      return _TotalRedAmt == null ? defaultValue : _TotalRedAmt;
   }
                  
   /**
    * Gets the Total Deferred Sales Charge field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Total Deferred Sales Charge or null.
    */
   public final String getTotalDSC()
   {
      return _TotalDSC;
   }
	
   /**
    * Gets the Total Deferred Sales Charge field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Total Deferred Sales Charge or the specified default value.
    */
   public final String getTotalDSC( String defaultValue )
   {
      return _TotalDSC == null ? defaultValue : _TotalDSC;
   }
                  
   /**
    * Gets the Fees field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Fees or null.
    */
   public final String getFee()
   {
      return _Fee;
   }
	
   /**
    * Gets the Fees field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fees or the specified default value.
    */
   public final String getFee( String defaultValue )
   {
      return _Fee == null ? defaultValue : _Fee;
   }
                  
   /**
    * Gets the WithHolding Tax field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the WithHolding Tax or null.
    */
   public final String getWithHoldTax()
   {
      return _WithHoldTax;
   }
	
   /**
    * Gets the WithHolding Tax field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the WithHolding Tax or the specified default value.
    */
   public final String getWithHoldTax( String defaultValue )
   {
      return _WithHoldTax == null ? defaultValue : _WithHoldTax;
   }
                  
   /**
    * Gets the Net Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Net Amount or null.
    */
   public final String getNetAmt()
   {
      return _NetAmt;
   }
	
   /**
    * Gets the Net Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Net Amount or the specified default value.
    */
   public final String getNetAmt( String defaultValue )
   {
      return _NetAmt == null ? defaultValue : _NetAmt;
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
    * Gets the Fund Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Code or null.
    */
   public final String getrxFundCode( int index )
   {
      return _rxFundCode[index];
   }
    
   /**
    * Gets the Fund Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Code or the specified default value.
    */
   public final String getrxFundCode( int index, String defaultValue )
   {
      return _rxFundCode[index] == null ? defaultValue : _rxFundCode[index];
   }
    
   /**
    * Gets the array of Fund Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Code values.
    */
   public final String[] getrxFundCodeArray()
   {
      return _rxFundCode;
   }
    
   /**
    * Gets the Class Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Class Code or null.
    */
   public final String getrxClassCode( int index )
   {
      return _rxClassCode[index];
   }
    
   /**
    * Gets the Class Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class Code or the specified default value.
    */
   public final String getrxClassCode( int index, String defaultValue )
   {
      return _rxClassCode[index] == null ? defaultValue : _rxClassCode[index];
   }
    
   /**
    * Gets the array of Class Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Class Code values.
    */
   public final String[] getrxClassCodeArray()
   {
      return _rxClassCode;
   }
    
   /**
    * Gets the Gross Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Gross Amount or null.
    */
   public final String getGrossAmt( int index )
   {
      return _GrossAmt[index];
   }
    
   /**
    * Gets the Gross Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Gross Amount or the specified default value.
    */
   public final String getGrossAmt( int index, String defaultValue )
   {
      return _GrossAmt[index] == null ? defaultValue : _GrossAmt[index];
   }
    
   /**
    * Gets the array of Gross Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Gross Amount values.
    */
   public final String[] getGrossAmtArray()
   {
      return _GrossAmt;
   }
    
   /**
    * Gets the Units field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Units or null.
    */
   public final String getUnits( int index )
   {
      return _Units[index];
   }
    
   /**
    * Gets the Units field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Units or the specified default value.
    */
   public final String getUnits( int index, String defaultValue )
   {
      return _Units[index] == null ? defaultValue : _Units[index];
   }
    
   /**
    * Gets the array of Units fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Units values.
    */
   public final String[] getUnitsArray()
   {
      return _Units;
   }
    
   /**
    * Gets the Deferred Sales Charge field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Deferred Sales Charge or null.
    */
   public final String getDSC( int index )
   {
      return _DSC[index];
   }
    
   /**
    * Gets the Deferred Sales Charge field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Deferred Sales Charge or the specified default value.
    */
   public final String getDSC( int index, String defaultValue )
   {
      return _DSC[index] == null ? defaultValue : _DSC[index];
   }
    
   /**
    * Gets the array of Deferred Sales Charge fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Deferred Sales Charge values.
    */
   public final String[] getDSCArray()
   {
      return _DSC;
   }
    
   /**
    * Gets the Fee Free Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fee Free Amount or null.
    */
   public final String getFeeFreeAmt( int index )
   {
      return _FeeFreeAmt[index];
   }
    
   /**
    * Gets the Fee Free Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee Free Amount or the specified default value.
    */
   public final String getFeeFreeAmt( int index, String defaultValue )
   {
      return _FeeFreeAmt[index] == null ? defaultValue : _FeeFreeAmt[index];
   }
    
   /**
    * Gets the array of Fee Free Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee Free Amount values.
    */
   public final String[] getFeeFreeAmtArray()
   {
      return _FeeFreeAmt;
   }
    
   /**
    * Gets the Fee Free Units field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fee Free Units or null.
    */
   public final String getFeeFreeUnits( int index )
   {
      return _FeeFreeUnits[index];
   }
    
   /**
    * Gets the Fee Free Units field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee Free Units or the specified default value.
    */
   public final String getFeeFreeUnits( int index, String defaultValue )
   {
      return _FeeFreeUnits[index] == null ? defaultValue : _FeeFreeUnits[index];
   }
    
   /**
    * Gets the array of Fee Free Units fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee Free Units values.
    */
   public final String[] getFeeFreeUnitsArray()
   {
      return _FeeFreeUnits;
   }
    
   /**
    * Gets the Fee Applicable Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fee Applicable Amount or null.
    */
   public final String getFeeApplAmt( int index )
   {
      return _FeeApplAmt[index];
   }
    
   /**
    * Gets the Fee Applicable Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee Applicable Amount or the specified default value.
    */
   public final String getFeeApplAmt( int index, String defaultValue )
   {
      return _FeeApplAmt[index] == null ? defaultValue : _FeeApplAmt[index];
   }
    
   /**
    * Gets the array of Fee Applicable Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee Applicable Amount values.
    */
   public final String[] getFeeApplAmtArray()
   {
      return _FeeApplAmt;
   }
    
   /**
    * Gets the Fee Applicable Units field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fee Applicable Units or null.
    */
   public final String getFeeApplUnits( int index )
   {
      return _FeeApplUnits[index];
   }
    
   /**
    * Gets the Fee Applicable Units field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee Applicable Units or the specified default value.
    */
   public final String getFeeApplUnits( int index, String defaultValue )
   {
      return _FeeApplUnits[index] == null ? defaultValue : _FeeApplUnits[index];
   }
    
   /**
    * Gets the array of Fee Applicable Units fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee Applicable Units values.
    */
   public final String[] getFeeApplUnitsArray()
   {
      return _FeeApplUnits;
   }
    
   /**
    * Gets the Valuation date used in calculation field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Valuation date used in calculation or null.
    */
   public final Date getValueAsAt( int index )
   {
      return _ValueAsAt[index];
   }
    
   /**
    * Gets the Valuation date used in calculation field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Valuation date used in calculation or the specified default value.
    */
   public final Date getValueAsAt( int index, Date defaultValue )
   {
      return _ValueAsAt[index] == null ? defaultValue : _ValueAsAt[index];
   }
    
   /**
    * Gets the array of Valuation date used in calculation fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Valuation date used in calculation values.
    */
   public final Date[] getValueAsAtArray()
   {
      return _ValueAsAt;
   }
    
   /**
    * Gets the Fund valuation price used in calculation field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund valuation price used in calculation or null.
    */
   public final String getFundNAV( int index )
   {
      return _FundNAV[index];
   }
    
   /**
    * Gets the Fund valuation price used in calculation field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund valuation price used in calculation or the specified default value.
    */
   public final String getFundNAV( int index, String defaultValue )
   {
      return _FundNAV[index] == null ? defaultValue : _FundNAV[index];
   }
    
   /**
    * Gets the array of Fund valuation price used in calculation fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund valuation price used in calculation values.
    */
   public final String[] getFundNAVArray()
   {
      return _FundNAV;
   }
    
   /**
    * Gets the Baycom field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Baycom or null.
    */
   public final String getrxBaycom( int index )
   {
      return _rxBaycom[index];
   }
    
   /**
    * Gets the Baycom field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Baycom or the specified default value.
    */
   public final String getrxBaycom( int index, String defaultValue )
   {
      return _rxBaycom[index] == null ? defaultValue : _rxBaycom[index];
   }
    
   /**
    * Gets the array of Baycom fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Baycom values.
    */
   public final String[] getrxBaycomArray()
   {
      return _rxBaycom;
   }
    
   /**
    * Gets the English Long Name1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the English Long Name1 or null.
    */
   public final String getELongName1( int index )
   {
      return _ELongName1[index];
   }
    
   /**
    * Gets the English Long Name1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the English Long Name1 or the specified default value.
    */
   public final String getELongName1( int index, String defaultValue )
   {
      return _ELongName1[index] == null ? defaultValue : _ELongName1[index];
   }
    
   /**
    * Gets the array of English Long Name1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of English Long Name1 values.
    */
   public final String[] getELongName1Array()
   {
      return _ELongName1;
   }
    
   /**
    * Gets the Account Units field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Units or null.
    */
   public final String getAcctUnits( int index )
   {
      return _AcctUnits[index];
   }
    
   /**
    * Gets the Account Units field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Units or the specified default value.
    */
   public final String getAcctUnits( int index, String defaultValue )
   {
      return _AcctUnits[index] == null ? defaultValue : _AcctUnits[index];
   }
    
   /**
    * Gets the array of Account Units fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Units values.
    */
   public final String[] getAcctUnitsArray()
   {
      return _AcctUnits;
   }
    
   /**
    * Gets the Federal Tax field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Federal Tax or null.
    */
   public final String getFedTax( int index )
   {
      return _FedTax[index];
   }
    
   /**
    * Gets the Federal Tax field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Federal Tax or the specified default value.
    */
   public final String getFedTax( int index, String defaultValue )
   {
      return _FedTax[index] == null ? defaultValue : _FedTax[index];
   }
    
   /**
    * Gets the array of Federal Tax fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Federal Tax values.
    */
   public final String[] getFedTaxArray()
   {
      return _FedTax;
   }
    
   /**
    * Gets the Provincial Tax field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Provincial Tax or null.
    */
   public final String getProvTax( int index )
   {
      return _ProvTax[index];
   }
    
   /**
    * Gets the Provincial Tax field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Provincial Tax or the specified default value.
    */
   public final String getProvTax( int index, String defaultValue )
   {
      return _ProvTax[index] == null ? defaultValue : _ProvTax[index];
   }
    
   /**
    * Gets the array of Provincial Tax fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Provincial Tax values.
    */
   public final String[] getProvTaxArray()
   {
      return _ProvTax;
   }
    
   /**
    * Gets the Federal Clawback field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Federal Clawback or null.
    */
   public final String getFedClawback( int index )
   {
      return _FedClawback[index];
   }
    
   /**
    * Gets the Federal Clawback field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Federal Clawback or the specified default value.
    */
   public final String getFedClawback( int index, String defaultValue )
   {
      return _FedClawback[index] == null ? defaultValue : _FedClawback[index];
   }
    
   /**
    * Gets the array of Federal Clawback fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Federal Clawback values.
    */
   public final String[] getFedClawbackArray()
   {
      return _FedClawback;
   }
    
   /**
    * Gets the Provincial Clawback field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Provincial Clawback or null.
    */
   public final String getProvClawback( int index )
   {
      return _ProvClawback[index];
   }
    
   /**
    * Gets the Provincial Clawback field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Provincial Clawback or the specified default value.
    */
   public final String getProvClawback( int index, String defaultValue )
   {
      return _ProvClawback[index] == null ? defaultValue : _ProvClawback[index];
   }
    
   /**
    * Gets the array of Provincial Clawback fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Provincial Clawback values.
    */
   public final String[] getProvClawbackArray()
   {
      return _ProvClawback;
   }
    
   /**
    * Gets the Additional Provincial Clawback field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Additional Provincial Clawback or null.
    */
   public final String getAddlProvClawback( int index )
   {
      return _AddlProvClawback[index];
   }
    
   /**
    * Gets the Additional Provincial Clawback field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Additional Provincial Clawback or the specified default value.
    */
   public final String getAddlProvClawback( int index, String defaultValue )
   {
      return _AddlProvClawback[index] == null ? defaultValue : _AddlProvClawback[index];
   }
    
   /**
    * Gets the array of Additional Provincial Clawback fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Additional Provincial Clawback values.
    */
   public final String[] getAddlProvClawbackArray()
   {
      return _AddlProvClawback;
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
      _TotalRedAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _TotalDSC = responseBuffer.decodeString(responseBuffer.getNextField());
      _Fee = responseBuffer.decodeString(responseBuffer.getNextField());
      _WithHoldTax = responseBuffer.decodeString(responseBuffer.getNextField());
      _NetAmt = responseBuffer.decodeString(responseBuffer.getNextField());
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _rxFundCode = resizeArray( _rxFundCode, _RepeatCount );
      _rxClassCode = resizeArray( _rxClassCode, _RepeatCount );
      _GrossAmt = resizeArray( _GrossAmt, _RepeatCount );
      _Units = resizeArray( _Units, _RepeatCount );
      _DSC = resizeArray( _DSC, _RepeatCount );
      _FeeFreeAmt = resizeArray( _FeeFreeAmt, _RepeatCount );
      _FeeFreeUnits = resizeArray( _FeeFreeUnits, _RepeatCount );
      _FeeApplAmt = resizeArray( _FeeApplAmt, _RepeatCount );
      _FeeApplUnits = resizeArray( _FeeApplUnits, _RepeatCount );
      _ValueAsAt = resizeArray( _ValueAsAt, _RepeatCount );
      _FundNAV = resizeArray( _FundNAV, _RepeatCount );
      _rxBaycom = resizeArray( _rxBaycom, _RepeatCount );
      _ELongName1 = resizeArray( _ELongName1, _RepeatCount );
      _AcctUnits = resizeArray( _AcctUnits, _RepeatCount );
      _FedTax = resizeArray( _FedTax, _RepeatCount );
      _ProvTax = resizeArray( _ProvTax, _RepeatCount );
      _FedClawback = resizeArray( _FedClawback, _RepeatCount );
      _ProvClawback = resizeArray( _ProvClawback, _RepeatCount );
      _AddlProvClawback = resizeArray( _AddlProvClawback, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxFundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GrossAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Units[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DSC[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FeeFreeAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FeeFreeUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FeeApplAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FeeApplUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ValueAsAt[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _FundNAV[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxBaycom[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ELongName1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FedTax[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProvTax[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FedClawback[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProvClawback[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddlProvClawback[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
