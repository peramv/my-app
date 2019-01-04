
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Dynamic Hypothetical Redemption Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/DynHypoRedem.doc">DynHypoRedem.doc</A>.
 * 
 * @author RTS Generated
 */
public class DynHypoRedemView extends IFastView implements Serializable
{

   private int _FCRepeatCount = 0;
   
   /**
    * Fund Code member array.
    */
   private String[] _RxFundCode = null;
   
   /**
    * Class Code member array.
    */
   private String[] _RxClassCode = null;
   
   /**
    * Fund Currency member array.
    */
   private String[] _FundCurrency = null;
   
   /**
    * Gross Amount member array.
    */
   private String[] _GrossAmt = null;
   
   /**
    * Units member array.
    */
   private String[] _Units = null;
   
   /**
    * DSC Fee Free Amount member array.
    */
   private String[] _FreeAmt = null;
   
   /**
    * DSC Fee Free Units member array.
    */
   private String[] _FreeUnits = null;
   
   /**
    * Fee Applicable Amount member array.
    */
   private String[] _FeeApplAmt = null;
   
   /**
    * Fee Applicable Units member array.
    */
   private String[] _FeeApplUnits = null;
   
   /**
    * DSC Amount member array.
    */
   private String[] _DSCAmt = null;
   
   /**
    * Fee member array.
    */
   private String[] _Fee = null;
   
   /**
    * WithholdingTax member array.
    */
   private String[] _WithholdingTax = null;
   
   /**
    * NetAmount member array.
    */
   private String[] _NetAmount = null;
   
   /**
    * FederalTax member array.
    */
   private String[] _FederalTax = null;
   
   /**
    * ProvincialTax member array.
    */
   private String[] _ProvincialTax = null;
   
   /**
    * ValuationDate member array.
    */
   private Date[] _ValuationDate = null;
   
   /**
    * ValuationPrice member array.
    */
   private String[] _ValuationPrice = null;
   
   /**
    * AccountUnits member array.
    */
   private String[] _AccountUnits = null;
   
   /**
    * MaturityDate member array.
    */
   private Date[] _MaturityDate = null;
   
   /**
    * FreeAmtRemain member array.
    */
   private String[] _FreeAmtRemain = null;
   
   /**
    * FreeUnitsRemain member array.
    */
   private String[] _FreeUnitsRemain = null;
   
   /**
    * Baycom member array.
    */
   private String[] _Baycom = null;
   
   /**
    * EnglishLong member array.
    */
   private String[] _EnglishLong = null;
   
   /**
    * FCErrorCode member array.
    */
   private Integer[] _FCErrorCode = null;
   
   /**
    * FCErrorDescription member array.
    */
   private String[] _FCErrorDescription = null;
   
   /**
    * DSC Fee Start Position member array.
    */
   private Integer[] _DSCFeeStartPos = null;
   
   /**
    * Fund balance amount left member array.
    */
   private String[] _FundBalAmtLeft = null;
   
   /**
    * Fund balance units left member array.
    */
   private String[] _FundBalUnitLeft = null;
   
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
   
   private int _RepeatCount = 0;
   
   /**
    * Fund Code member array.
    */
   private String[] _rxDetlFundCode = null;
   
   /**
    * Class Code member array.
    */
   private String[] _rxDetlClassCode = null;
   
   /**
    * Detail Fund Currency member array.
    */
   private String[] _DetlFundCurrency = null;
   
   /**
    * Portion of gross amt charded with DSC member array.
    */
   private String[] _DetlAmt = null;
   
   /**
    * Portion of gross units chared with DSC member array.
    */
   private String[] _DetlUnits = null;
   
   /**
    * DSC Fee % applied member array.
    */
   private String[] _FeePrcnt = null;
   
   /**
    * DSC Fee charged on specific amount member array.
    */
   private String[] _DetlDSCAmt = null;
   

   /**
    * Constructs the DynHypoRedemView object.
    * 
    */
   public DynHypoRedemView()
   {
      super ( new DynHypoRedemRequest() );
   }

   /**
    * Constructs the DynHypoRedemView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public DynHypoRedemView( String hostEncoding )
   {
      super ( new DynHypoRedemRequest( hostEncoding ) );
   }

   /**
    * Gets the DynHypoRedemRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The DynHypoRedemRequest object.
    */
   public final DynHypoRedemRequest getRequest()
   {
      return (DynHypoRedemRequest)getIFastRequest();
   }
        
   /**
    * Gets the Record Count for the repeatable response.
    * 
    * @return The number of records in the repeating fields.
    */
   public int getRecordCount()
   {
      return _FCRepeatCount;
   }

   /**
    * Gets the Record Count for the repeatable response.
    * 
    * @return The number of records in the repeating fields.
    */
   public final int getFCRepeatCount()
   {
      return _FCRepeatCount;
   }

   /**
    * Decodes the repeat count value from the host 
    * respones.
    * 
    * @param response Host formatted response object.
    * @exception ParseException
    */
   private final void decodeFCRepeatCount( RTSResponseDecodeBuffer responseBuffer ) throws ParseException, UnsupportedEncodingException
   {
      int receivedRecordCount = responseBuffer.decodeInteger(responseBuffer.getNextField()).intValue();
      _FCRepeatCount += receivedRecordCount;
   }

   /**
    * Gets the Fund Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Code or null.
    */
   public final String getRxFundCode( int index )
   {
      return _RxFundCode[index];
   }
    
   /**
    * Gets the Fund Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Code or the specified default value.
    */
   public final String getRxFundCode( int index, String defaultValue )
   {
      return _RxFundCode[index] == null ? defaultValue : _RxFundCode[index];
   }
    
   /**
    * Gets the array of Fund Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Code values.
    */
   public final String[] getRxFundCodeArray()
   {
      return _RxFundCode;
   }
    
   /**
    * Gets the Class Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Class Code or null.
    */
   public final String getRxClassCode( int index )
   {
      return _RxClassCode[index];
   }
    
   /**
    * Gets the Class Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class Code or the specified default value.
    */
   public final String getRxClassCode( int index, String defaultValue )
   {
      return _RxClassCode[index] == null ? defaultValue : _RxClassCode[index];
   }
    
   /**
    * Gets the array of Class Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Class Code values.
    */
   public final String[] getRxClassCodeArray()
   {
      return _RxClassCode;
   }
    
   /**
    * Gets the Fund Currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Currency or null.
    */
   public final String getFundCurrency( int index )
   {
      return _FundCurrency[index];
   }
    
   /**
    * Gets the Fund Currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Currency or the specified default value.
    */
   public final String getFundCurrency( int index, String defaultValue )
   {
      return _FundCurrency[index] == null ? defaultValue : _FundCurrency[index];
   }
    
   /**
    * Gets the array of Fund Currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Currency values.
    */
   public final String[] getFundCurrencyArray()
   {
      return _FundCurrency;
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
    * Gets the DSC Fee Free Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the DSC Fee Free Amount or null.
    */
   public final String getFreeAmt( int index )
   {
      return _FreeAmt[index];
   }
    
   /**
    * Gets the DSC Fee Free Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the DSC Fee Free Amount or the specified default value.
    */
   public final String getFreeAmt( int index, String defaultValue )
   {
      return _FreeAmt[index] == null ? defaultValue : _FreeAmt[index];
   }
    
   /**
    * Gets the array of DSC Fee Free Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of DSC Fee Free Amount values.
    */
   public final String[] getFreeAmtArray()
   {
      return _FreeAmt;
   }
    
   /**
    * Gets the DSC Fee Free Units field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the DSC Fee Free Units or null.
    */
   public final String getFreeUnits( int index )
   {
      return _FreeUnits[index];
   }
    
   /**
    * Gets the DSC Fee Free Units field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the DSC Fee Free Units or the specified default value.
    */
   public final String getFreeUnits( int index, String defaultValue )
   {
      return _FreeUnits[index] == null ? defaultValue : _FreeUnits[index];
   }
    
   /**
    * Gets the array of DSC Fee Free Units fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of DSC Fee Free Units values.
    */
   public final String[] getFreeUnitsArray()
   {
      return _FreeUnits;
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
    * Gets the DSC Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the DSC Amount or null.
    */
   public final String getDSCAmt( int index )
   {
      return _DSCAmt[index];
   }
    
   /**
    * Gets the DSC Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the DSC Amount or the specified default value.
    */
   public final String getDSCAmt( int index, String defaultValue )
   {
      return _DSCAmt[index] == null ? defaultValue : _DSCAmt[index];
   }
    
   /**
    * Gets the array of DSC Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of DSC Amount values.
    */
   public final String[] getDSCAmtArray()
   {
      return _DSCAmt;
   }
    
   /**
    * Gets the Fee field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fee or null.
    */
   public final String getFee( int index )
   {
      return _Fee[index];
   }
    
   /**
    * Gets the Fee field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee or the specified default value.
    */
   public final String getFee( int index, String defaultValue )
   {
      return _Fee[index] == null ? defaultValue : _Fee[index];
   }
    
   /**
    * Gets the array of Fee fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee values.
    */
   public final String[] getFeeArray()
   {
      return _Fee;
   }
    
   /**
    * Gets the WithholdingTax field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the WithholdingTax or null.
    */
   public final String getWithholdingTax( int index )
   {
      return _WithholdingTax[index];
   }
    
   /**
    * Gets the WithholdingTax field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the WithholdingTax or the specified default value.
    */
   public final String getWithholdingTax( int index, String defaultValue )
   {
      return _WithholdingTax[index] == null ? defaultValue : _WithholdingTax[index];
   }
    
   /**
    * Gets the array of WithholdingTax fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of WithholdingTax values.
    */
   public final String[] getWithholdingTaxArray()
   {
      return _WithholdingTax;
   }
    
   /**
    * Gets the NetAmount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the NetAmount or null.
    */
   public final String getNetAmount( int index )
   {
      return _NetAmount[index];
   }
    
   /**
    * Gets the NetAmount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the NetAmount or the specified default value.
    */
   public final String getNetAmount( int index, String defaultValue )
   {
      return _NetAmount[index] == null ? defaultValue : _NetAmount[index];
   }
    
   /**
    * Gets the array of NetAmount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of NetAmount values.
    */
   public final String[] getNetAmountArray()
   {
      return _NetAmount;
   }
    
   /**
    * Gets the FederalTax field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FederalTax or null.
    */
   public final String getFederalTax( int index )
   {
      return _FederalTax[index];
   }
    
   /**
    * Gets the FederalTax field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FederalTax or the specified default value.
    */
   public final String getFederalTax( int index, String defaultValue )
   {
      return _FederalTax[index] == null ? defaultValue : _FederalTax[index];
   }
    
   /**
    * Gets the array of FederalTax fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FederalTax values.
    */
   public final String[] getFederalTaxArray()
   {
      return _FederalTax;
   }
    
   /**
    * Gets the ProvincialTax field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ProvincialTax or null.
    */
   public final String getProvincialTax( int index )
   {
      return _ProvincialTax[index];
   }
    
   /**
    * Gets the ProvincialTax field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ProvincialTax or the specified default value.
    */
   public final String getProvincialTax( int index, String defaultValue )
   {
      return _ProvincialTax[index] == null ? defaultValue : _ProvincialTax[index];
   }
    
   /**
    * Gets the array of ProvincialTax fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ProvincialTax values.
    */
   public final String[] getProvincialTaxArray()
   {
      return _ProvincialTax;
   }
    
   /**
    * Gets the ValuationDate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ValuationDate or null.
    */
   public final Date getValuationDate( int index )
   {
      return _ValuationDate[index];
   }
    
   /**
    * Gets the ValuationDate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ValuationDate or the specified default value.
    */
   public final Date getValuationDate( int index, Date defaultValue )
   {
      return _ValuationDate[index] == null ? defaultValue : _ValuationDate[index];
   }
    
   /**
    * Gets the array of ValuationDate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ValuationDate values.
    */
   public final Date[] getValuationDateArray()
   {
      return _ValuationDate;
   }
    
   /**
    * Gets the ValuationPrice field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ValuationPrice or null.
    */
   public final String getValuationPrice( int index )
   {
      return _ValuationPrice[index];
   }
    
   /**
    * Gets the ValuationPrice field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ValuationPrice or the specified default value.
    */
   public final String getValuationPrice( int index, String defaultValue )
   {
      return _ValuationPrice[index] == null ? defaultValue : _ValuationPrice[index];
   }
    
   /**
    * Gets the array of ValuationPrice fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ValuationPrice values.
    */
   public final String[] getValuationPriceArray()
   {
      return _ValuationPrice;
   }
    
   /**
    * Gets the AccountUnits field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AccountUnits or null.
    */
   public final String getAccountUnits( int index )
   {
      return _AccountUnits[index];
   }
    
   /**
    * Gets the AccountUnits field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AccountUnits or the specified default value.
    */
   public final String getAccountUnits( int index, String defaultValue )
   {
      return _AccountUnits[index] == null ? defaultValue : _AccountUnits[index];
   }
    
   /**
    * Gets the array of AccountUnits fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AccountUnits values.
    */
   public final String[] getAccountUnitsArray()
   {
      return _AccountUnits;
   }
    
   /**
    * Gets the MaturityDate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the MaturityDate or null.
    */
   public final Date getMaturityDate( int index )
   {
      return _MaturityDate[index];
   }
    
   /**
    * Gets the MaturityDate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the MaturityDate or the specified default value.
    */
   public final Date getMaturityDate( int index, Date defaultValue )
   {
      return _MaturityDate[index] == null ? defaultValue : _MaturityDate[index];
   }
    
   /**
    * Gets the array of MaturityDate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of MaturityDate values.
    */
   public final Date[] getMaturityDateArray()
   {
      return _MaturityDate;
   }
    
   /**
    * Gets the FreeAmtRemain field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FreeAmtRemain or null.
    */
   public final String getFreeAmtRemain( int index )
   {
      return _FreeAmtRemain[index];
   }
    
   /**
    * Gets the FreeAmtRemain field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FreeAmtRemain or the specified default value.
    */
   public final String getFreeAmtRemain( int index, String defaultValue )
   {
      return _FreeAmtRemain[index] == null ? defaultValue : _FreeAmtRemain[index];
   }
    
   /**
    * Gets the array of FreeAmtRemain fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FreeAmtRemain values.
    */
   public final String[] getFreeAmtRemainArray()
   {
      return _FreeAmtRemain;
   }
    
   /**
    * Gets the FreeUnitsRemain field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FreeUnitsRemain or null.
    */
   public final String getFreeUnitsRemain( int index )
   {
      return _FreeUnitsRemain[index];
   }
    
   /**
    * Gets the FreeUnitsRemain field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FreeUnitsRemain or the specified default value.
    */
   public final String getFreeUnitsRemain( int index, String defaultValue )
   {
      return _FreeUnitsRemain[index] == null ? defaultValue : _FreeUnitsRemain[index];
   }
    
   /**
    * Gets the array of FreeUnitsRemain fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FreeUnitsRemain values.
    */
   public final String[] getFreeUnitsRemainArray()
   {
      return _FreeUnitsRemain;
   }
    
   /**
    * Gets the Baycom field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Baycom or null.
    */
   public final String getBaycom( int index )
   {
      return _Baycom[index];
   }
    
   /**
    * Gets the Baycom field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Baycom or the specified default value.
    */
   public final String getBaycom( int index, String defaultValue )
   {
      return _Baycom[index] == null ? defaultValue : _Baycom[index];
   }
    
   /**
    * Gets the array of Baycom fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Baycom values.
    */
   public final String[] getBaycomArray()
   {
      return _Baycom;
   }
    
   /**
    * Gets the EnglishLong field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the EnglishLong or null.
    */
   public final String getEnglishLong( int index )
   {
      return _EnglishLong[index];
   }
    
   /**
    * Gets the EnglishLong field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the EnglishLong or the specified default value.
    */
   public final String getEnglishLong( int index, String defaultValue )
   {
      return _EnglishLong[index] == null ? defaultValue : _EnglishLong[index];
   }
    
   /**
    * Gets the array of EnglishLong fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of EnglishLong values.
    */
   public final String[] getEnglishLongArray()
   {
      return _EnglishLong;
   }
    
   /**
    * Gets the FCErrorCode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FCErrorCode or null.
    */
   public final Integer getFCErrorCode( int index )
   {
      return _FCErrorCode[index];
   }
    
   /**
    * Gets the FCErrorCode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FCErrorCode or the specified default value.
    */
   public final int getFCErrorCode( int index, int defaultValue )
   {
      return _FCErrorCode[index] == null ? defaultValue : _FCErrorCode[index].intValue();
   }
    
   /**
    * Gets the array of FCErrorCode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FCErrorCode values.
    */
   public final Integer[] getFCErrorCodeArray()
   {
      return _FCErrorCode;
   }
    
   /**
    * Gets the FCErrorDescription field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FCErrorDescription or null.
    */
   public final String getFCErrorDescription( int index )
   {
      return _FCErrorDescription[index];
   }
    
   /**
    * Gets the FCErrorDescription field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FCErrorDescription or the specified default value.
    */
   public final String getFCErrorDescription( int index, String defaultValue )
   {
      return _FCErrorDescription[index] == null ? defaultValue : _FCErrorDescription[index];
   }
    
   /**
    * Gets the array of FCErrorDescription fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FCErrorDescription values.
    */
   public final String[] getFCErrorDescriptionArray()
   {
      return _FCErrorDescription;
   }
    
   /**
    * Gets the DSC Fee Start Position field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the DSC Fee Start Position or null.
    */
   public final Integer getDSCFeeStartPos( int index )
   {
      return _DSCFeeStartPos[index];
   }
    
   /**
    * Gets the DSC Fee Start Position field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the DSC Fee Start Position or the specified default value.
    */
   public final int getDSCFeeStartPos( int index, int defaultValue )
   {
      return _DSCFeeStartPos[index] == null ? defaultValue : _DSCFeeStartPos[index].intValue();
   }
    
   /**
    * Gets the array of DSC Fee Start Position fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of DSC Fee Start Position values.
    */
   public final Integer[] getDSCFeeStartPosArray()
   {
      return _DSCFeeStartPos;
   }
    
   /**
    * Gets the Fund balance amount left field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund balance amount left or null.
    */
   public final String getFundBalAmtLeft( int index )
   {
      return _FundBalAmtLeft[index];
   }
    
   /**
    * Gets the Fund balance amount left field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund balance amount left or the specified default value.
    */
   public final String getFundBalAmtLeft( int index, String defaultValue )
   {
      return _FundBalAmtLeft[index] == null ? defaultValue : _FundBalAmtLeft[index];
   }
    
   /**
    * Gets the array of Fund balance amount left fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund balance amount left values.
    */
   public final String[] getFundBalAmtLeftArray()
   {
      return _FundBalAmtLeft;
   }
    
   /**
    * Gets the Fund balance units left field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund balance units left or null.
    */
   public final String getFundBalUnitLeft( int index )
   {
      return _FundBalUnitLeft[index];
   }
    
   /**
    * Gets the Fund balance units left field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund balance units left or the specified default value.
    */
   public final String getFundBalUnitLeft( int index, String defaultValue )
   {
      return _FundBalUnitLeft[index] == null ? defaultValue : _FundBalUnitLeft[index];
   }
    
   /**
    * Gets the array of Fund balance units left fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund balance units left values.
    */
   public final String[] getFundBalUnitLeftArray()
   {
      return _FundBalUnitLeft;
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
   public final String getrxDetlFundCode( int index )
   {
      return _rxDetlFundCode[index];
   }
    
   /**
    * Gets the Fund Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Code or the specified default value.
    */
   public final String getrxDetlFundCode( int index, String defaultValue )
   {
      return _rxDetlFundCode[index] == null ? defaultValue : _rxDetlFundCode[index];
   }
    
   /**
    * Gets the array of Fund Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Code values.
    */
   public final String[] getrxDetlFundCodeArray()
   {
      return _rxDetlFundCode;
   }
    
   /**
    * Gets the Class Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Class Code or null.
    */
   public final String getrxDetlClassCode( int index )
   {
      return _rxDetlClassCode[index];
   }
    
   /**
    * Gets the Class Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class Code or the specified default value.
    */
   public final String getrxDetlClassCode( int index, String defaultValue )
   {
      return _rxDetlClassCode[index] == null ? defaultValue : _rxDetlClassCode[index];
   }
    
   /**
    * Gets the array of Class Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Class Code values.
    */
   public final String[] getrxDetlClassCodeArray()
   {
      return _rxDetlClassCode;
   }
    
   /**
    * Gets the Detail Fund Currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Detail Fund Currency or null.
    */
   public final String getDetlFundCurrency( int index )
   {
      return _DetlFundCurrency[index];
   }
    
   /**
    * Gets the Detail Fund Currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Detail Fund Currency or the specified default value.
    */
   public final String getDetlFundCurrency( int index, String defaultValue )
   {
      return _DetlFundCurrency[index] == null ? defaultValue : _DetlFundCurrency[index];
   }
    
   /**
    * Gets the array of Detail Fund Currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Detail Fund Currency values.
    */
   public final String[] getDetlFundCurrencyArray()
   {
      return _DetlFundCurrency;
   }
    
   /**
    * Gets the Portion of gross amt charded with DSC field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Portion of gross amt charded with DSC or null.
    */
   public final String getDetlAmt( int index )
   {
      return _DetlAmt[index];
   }
    
   /**
    * Gets the Portion of gross amt charded with DSC field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Portion of gross amt charded with DSC or the specified default value.
    */
   public final String getDetlAmt( int index, String defaultValue )
   {
      return _DetlAmt[index] == null ? defaultValue : _DetlAmt[index];
   }
    
   /**
    * Gets the array of Portion of gross amt charded with DSC fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Portion of gross amt charded with DSC values.
    */
   public final String[] getDetlAmtArray()
   {
      return _DetlAmt;
   }
    
   /**
    * Gets the Portion of gross units chared with DSC field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Portion of gross units chared with DSC or null.
    */
   public final String getDetlUnits( int index )
   {
      return _DetlUnits[index];
   }
    
   /**
    * Gets the Portion of gross units chared with DSC field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Portion of gross units chared with DSC or the specified default value.
    */
   public final String getDetlUnits( int index, String defaultValue )
   {
      return _DetlUnits[index] == null ? defaultValue : _DetlUnits[index];
   }
    
   /**
    * Gets the array of Portion of gross units chared with DSC fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Portion of gross units chared with DSC values.
    */
   public final String[] getDetlUnitsArray()
   {
      return _DetlUnits;
   }
    
   /**
    * Gets the DSC Fee % applied field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the DSC Fee % applied or null.
    */
   public final String getFeePrcnt( int index )
   {
      return _FeePrcnt[index];
   }
    
   /**
    * Gets the DSC Fee % applied field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the DSC Fee % applied or the specified default value.
    */
   public final String getFeePrcnt( int index, String defaultValue )
   {
      return _FeePrcnt[index] == null ? defaultValue : _FeePrcnt[index];
   }
    
   /**
    * Gets the array of DSC Fee % applied fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of DSC Fee % applied values.
    */
   public final String[] getFeePrcntArray()
   {
      return _FeePrcnt;
   }
    
   /**
    * Gets the DSC Fee charged on specific amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the DSC Fee charged on specific amount or null.
    */
   public final String getDetlDSCAmt( int index )
   {
      return _DetlDSCAmt[index];
   }
    
   /**
    * Gets the DSC Fee charged on specific amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the DSC Fee charged on specific amount or the specified default value.
    */
   public final String getDetlDSCAmt( int index, String defaultValue )
   {
      return _DetlDSCAmt[index] == null ? defaultValue : _DetlDSCAmt[index];
   }
    
   /**
    * Gets the array of DSC Fee charged on specific amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of DSC Fee charged on specific amount values.
    */
   public final String[] getDetlDSCAmtArray()
   {
      return _DetlDSCAmt;
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
      int oldFCRepeatCount = _FCRepeatCount;
      decodeFCRepeatCount( responseBuffer );
      
      _RxFundCode = resizeArray( _RxFundCode, _FCRepeatCount );
      _RxClassCode = resizeArray( _RxClassCode, _FCRepeatCount );
      _FundCurrency = resizeArray( _FundCurrency, _FCRepeatCount );
      _GrossAmt = resizeArray( _GrossAmt, _FCRepeatCount );
      _Units = resizeArray( _Units, _FCRepeatCount );
      _FreeAmt = resizeArray( _FreeAmt, _FCRepeatCount );
      _FreeUnits = resizeArray( _FreeUnits, _FCRepeatCount );
      _FeeApplAmt = resizeArray( _FeeApplAmt, _FCRepeatCount );
      _FeeApplUnits = resizeArray( _FeeApplUnits, _FCRepeatCount );
      _DSCAmt = resizeArray( _DSCAmt, _FCRepeatCount );
      _Fee = resizeArray( _Fee, _FCRepeatCount );
      _WithholdingTax = resizeArray( _WithholdingTax, _FCRepeatCount );
      _NetAmount = resizeArray( _NetAmount, _FCRepeatCount );
      _FederalTax = resizeArray( _FederalTax, _FCRepeatCount );
      _ProvincialTax = resizeArray( _ProvincialTax, _FCRepeatCount );
      _ValuationDate = resizeArray( _ValuationDate, _FCRepeatCount );
      _ValuationPrice = resizeArray( _ValuationPrice, _FCRepeatCount );
      _AccountUnits = resizeArray( _AccountUnits, _FCRepeatCount );
      _MaturityDate = resizeArray( _MaturityDate, _FCRepeatCount );
      _FreeAmtRemain = resizeArray( _FreeAmtRemain, _FCRepeatCount );
      _FreeUnitsRemain = resizeArray( _FreeUnitsRemain, _FCRepeatCount );
      _Baycom = resizeArray( _Baycom, _FCRepeatCount );
      _EnglishLong = resizeArray( _EnglishLong, _FCRepeatCount );
      _FCErrorCode = resizeArray( _FCErrorCode, _FCRepeatCount );
      _FCErrorDescription = resizeArray( _FCErrorDescription, _FCRepeatCount );
      _DSCFeeStartPos = resizeArray( _DSCFeeStartPos, _FCRepeatCount );
      _FundBalAmtLeft = resizeArray( _FundBalAmtLeft, _FCRepeatCount );
      _FundBalUnitLeft = resizeArray( _FundBalUnitLeft, _FCRepeatCount );
      _FedClawback = resizeArray( _FedClawback, _FCRepeatCount );
      _ProvClawback = resizeArray( _ProvClawback, _FCRepeatCount );
      _AddlProvClawback = resizeArray( _AddlProvClawback, _FCRepeatCount );
        
      for (int x = oldFCRepeatCount ; x < _FCRepeatCount; x++)
      {
         _RxFundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RxClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundCurrency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GrossAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Units[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FreeAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FreeUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FeeApplAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FeeApplUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DSCAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Fee[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _WithholdingTax[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _NetAmount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FederalTax[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProvincialTax[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ValuationDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ValuationPrice[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AccountUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MaturityDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _FreeAmtRemain[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FreeUnitsRemain[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Baycom[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EnglishLong[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FCErrorCode[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _FCErrorDescription[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DSCFeeStartPos[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _FundBalAmtLeft[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundBalUnitLeft[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FedClawback[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProvClawback[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddlProvClawback[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _rxDetlFundCode = resizeArray( _rxDetlFundCode, _RepeatCount );
      _rxDetlClassCode = resizeArray( _rxDetlClassCode, _RepeatCount );
      _DetlFundCurrency = resizeArray( _DetlFundCurrency, _RepeatCount );
      _DetlAmt = resizeArray( _DetlAmt, _RepeatCount );
      _DetlUnits = resizeArray( _DetlUnits, _RepeatCount );
      _FeePrcnt = resizeArray( _FeePrcnt, _RepeatCount );
      _DetlDSCAmt = resizeArray( _DetlDSCAmt, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxDetlFundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxDetlClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DetlFundCurrency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DetlAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DetlUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FeePrcnt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DetlDSCAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
